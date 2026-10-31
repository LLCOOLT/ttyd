#include <dolphin/os.h>
#include <macros.h>

typedef void (*InterruptHandlerLike)(s32, OSContext*);

u8 EXIInputFlag;
u8* pEXIInputFlag;
s32 RecvDataLeng;
u32 SendMailData;
InterruptHandlerLike DBGCallback;
InterruptHandlerLike MTRCallback;

/** Running count of messages sent to the debugger host, folded into each message header; starts at 0x80. */
u8 SendCount = 0x80;

static void DBGHandler(__OSInterrupt interrupt, OSContext* context);
static void MWCallback(s32 interrupt, OSContext* context);
static void DBGEXIInit(void);
static BOOL DBGEXISelect(u32);
static BOOL DBGEXIDeselect(void);
static BOOL DBGReadStatus(void*);
static BOOL DBGWrite(u32, u32*, s32);
static BOOL DBGRead(u32, u32*, s32);
static BOOL DBGWriteMailbox(u32);
static BOOL DBGReadMailbox(void*);
static BOOL DBGEXIImm(void*, s32, u32);

/**
 * Masks the EXI channel 2 interrupts (mask 0x18000) and clears the channel 2 control/status register,
 * preparing the debugger link.
 */
static void DBGEXIInit(void)
{
	__OSMaskInterrupts(0x18000);
	__EXIRegs[10] = 0;
}

/**
 * Selects device v on EXI channel 2 by writing the chip-select bits
 * and a clock field (0x80) into the channel 2 control register, keeping only bits 0x405 of the old value.
 */
static BOOL DBGEXISelect(u32 v)
{
	u32 regs = __EXIRegs[10];
	regs &= 0x405;
	regs |= 0x80 | (v << 4);
	__EXIRegs[10] = regs;
	return TRUE;
}

/** Deselects the EXI channel 2 device by clearing everything but bits 0x405 of the control register. */
static BOOL DBGEXIDeselect(void)
{
	__EXIRegs[10] &= 0x405;
	return TRUE;
}

/** Busy-waits until the EXI channel 2 transfer-in-progress bit clears. */
static BOOL DBGEXISync(void)
{
	while (__EXIRegs[13] & 1)
		;
	return TRUE;
}

/**
 * Performs an immediate (single-word) transfer of 1 to 4 bytes on EXI channel 2:
 * for a write it packs the bytes big-endian into the data register, starts the transfer and waits;
 * for a read it unpacks the data register into the buffer afterwards.
 */
static BOOL DBGEXIImm(void* data, s32 byte_size, u32 write)
{
	u32 writeVal;
	u32 readVal;
	int i;

	if (write) {
		writeVal = 0;
		for (i = 0; i < byte_size; ++i) {
			u8* nextWordPtr = (u8*)data + i;
			writeVal |= *nextWordPtr << ((3 - i) << 3);
		}
		__EXIRegs[14] = writeVal;
	}

	__EXIRegs[13] = 1 | (write << 2) | ((byte_size - 1U) << 4);

	DBGEXISync();
	if (!write) {
		u8* dataPtr = (u8*)data;
		readVal     = __EXIRegs[14];
		for (i = 0; i < byte_size; ++i) {
			*dataPtr++ = readVal >> ((3 - i) << 3);
		}
	}

	return TRUE;
}

/**
 * Reads the debugger host's mailbox word over EXI channel 2: sends the command 0x6000 and reads the reply.
 * Returns TRUE on success.
 */
static BOOL DBGReadMailbox(void* param1)
{
	BOOL error = FALSE;
	u32 local_c;

	if (!DBGEXISelect(4)) {
		return FALSE;
	}

	local_c = 0x60000000;
	error |= !DBGEXIImm((u8*)&local_c, 2, 1);
	error |= !DBGEXISync();
	error |= !DBGEXIImm(param1, sizeof(param1), 0);
	error |= !DBGEXISync();
	error |= !DBGEXIDeselect();

	return !error;
}

/**
 * Writes a 29-bit value into the host mailbox (command 0xC0000000 plus the value) to tell the debugger host that
 * data is waiting. Returns TRUE on success.
 */
static BOOL DBGWriteMailbox(u32 param_1)
{
	BOOL error = FALSE;
	u32 value;

	if (!DBGEXISelect(4)) {
		return FALSE;
	}

	value = (param_1 & 0x1fffffff) | 0xc0000000;
	error |= !DBGEXIImm((u8*)&value, sizeof(value), 1);
	error |= !DBGEXISync();
	error |= !DBGEXIDeselect();

	return !error;
}

/**
 * Reads byte_size bytes (in 4-byte words, rounded up) from the host's shared buffer at offset param1 into data,
 * using command 0x20000000 and consecutive immediate reads. Returns TRUE if every EXI step succeeded.
 */
static BOOL DBGRead(u32 param1, u32* data, s32 byte_size)
{
	BOOL error   = FALSE;
	u32* dataPtr = (u32*)data;
	u32 writeValue;
	u32 readValue;

	if (!DBGEXISelect(4)) {
		return FALSE;
	}

	writeValue = (u32)(param1 << 8) & 0x1fffc00 | 0x20000000;
	error |= !DBGEXIImm((u8*)&writeValue, sizeof(writeValue), 1);
	error |= !DBGEXISync();

	while (byte_size != 0) {
		error |= !DBGEXIImm((u8*)&readValue, sizeof(readValue), 0);
		error |= !DBGEXISync();

		*dataPtr++ = readValue;

		byte_size -= 4;
		if (byte_size < 0) {
			byte_size = 0;
		}
	}
	error |= !DBGEXIDeselect();

	return !error;
}

/**
 * Writes byte_size bytes (in 4-byte words, rounded up) from data into the host's shared buffer at offset param1,
 * using command 0xA0000000 and consecutive immediate writes. Returns TRUE if every EXI step succeeded.
 */
static BOOL DBGWrite(u32 param1, u32* data, s32 byte_size)
{
	BOOL error   = FALSE;
	u32* dataPtr = (u32*)data;
	u32 value;
	u32 nextWord;

	if (!DBGEXISelect(4)) {
		return FALSE;
	}

	value = (param1 & 0x1fffc) << 8 | 0xa0000000;
	error = !DBGEXIImm((u8*)&value, sizeof(value), 1);
	error |= !DBGEXISync();

	while (byte_size != 0) {
		nextWord = *dataPtr++;

		error |= !DBGEXIImm((u8*)&nextWord, sizeof(nextWord), 1);
		error |= !DBGEXISync();

		byte_size -= 4;
		if (byte_size < 0)
			byte_size = 0;
	}

	error |= !DBGEXIDeselect();

	return !error;
}

/**
 * Reads the host's status word over EXI channel 2 (command 0x4000);
 * bit 1 means the host has a mailbox message, bit 2 means it is busy. Returns TRUE on success.
 */
static BOOL DBGReadStatus(void* param_1)
{
	BOOL error = FALSE;
	u32 value;

	if (!DBGEXISelect(4)) {
		return FALSE;
	}

	value = 0x40000000;
	error |= !DBGEXIImm((u8*)&value, 2, 1);
	error |= !DBGEXISync();
	error |= !DBGEXIImm(param_1, sizeof(param_1), 0);
	error |= !DBGEXISync();
	error |= !DBGEXIDeselect();

	return !error;
}

/**
 * Default debugger interrupt callback: sets EXIInputFlag to tell the debug monitor that input arrived,
 * then calls the monitor's own callback (MTRCallback) if one was registered by DBInitComm.
 */
static void MWCallback(s32 interrupt, OSContext* context)
{
	EXIInputFlag = 1;
	if (MTRCallback) {
		(*MTRCallback)(0, context);
	}
}

/**
 * Interrupt handler installed for the EXI debug interrupt (0x19):
 * acknowledges it in the processor-interface register and calls DBGCallback.
 */
static void DBGHandler(__OSInterrupt interrupt, OSContext* context)
{
	__PIRegs[0] = 0x1000;
	if (DBGCallback) {
		(*DBGCallback)(interrupt, context);
	}
}

/**
 * Polls the host: if the status says a mailbox message is pending, reads it,
 * and if it is a data-ready message (0x1F in the top byte after masking) records the message in SendMailData,
 * the received length in RecvDataLeng and sets EXIInputFlag.
 */
static void CheckMailBox(void)
{
	u32 local_8[2];

	DBGReadStatus(local_8);
	if (local_8[0] & 1) {
		DBGReadMailbox(local_8);
		local_8[0] &= ~0xE0000000;
		if ((local_8[0] & 0x1f000000) == 0x1f000000) {
			SendMailData = local_8[0];
			RecvDataLeng = local_8[0] & 0x7fff;
			EXIInputFlag = 1;
		}
	}
}

/**
 * Initialises debugger communication: hands the caller a pointer to the input-ready flag,
 * stores the monitor's callback, and initialises EXI channel 2 with interrupts disabled around it.
 */
void DBInitComm(u8** param_1, InterruptHandlerLike param_2)
{
	BOOL enabled;

	enabled       = OSDisableInterrupts();
	pEXIInputFlag = &EXIInputFlag;
	*param_1      = pEXIInputFlag;
	MTRCallback   = param_2;
	DBGEXIInit();
	OSRestoreInterrupts(enabled);
}

/**
 * Installs DBGHandler as the handler for the EXI debug interrupt (0x19) with MWCallback as its callback,
 * masking and then unmasking the interrupt around the change.
 */
void DBInitInterrupts(void)
{
	__OSMaskInterrupts(0x18000);
	__OSMaskInterrupts(0x40);
	DBGCallback = MWCallback;
	__OSSetInterruptHandler(0x19, DBGHandler);
	__OSUnmaskInterrupts(0x40);
}

/**
 * Clears the input flag and, if no received data is pending, polls the host mailbox;
 * returns the number of bytes waiting for DBRead (0 if none).
 */
u32 DBQueryData(void)
{
	BOOL enable;

	EXIInputFlag = 0;
	if (RecvDataLeng == 0) {
		enable = OSDisableInterrupts();
		CheckMailBox();
		OSRestoreInterrupts(enable);
	}
	return RecvDataLeng;
}

/**
 * Reads the pending received bytes (length rounded up to 4) from the host's receive buffer into param1 (the
 * buffer used depends on bit 0x10000 of the last mail), then marks the data as consumed. Always returns 0.
 */
u32 DBRead(u32* param1, s32 param2)
{
	BOOL enabled;
	u32 lVar3;

	enabled = OSDisableInterrupts();
	if (SendMailData & 0x10000) {
		lVar3 = 0x1000;
	} else {
		lVar3 = 0;
	}
	DBGRead(lVar3 + 0x1e000, param1, param2 + 3U & 0xfffffffc);
	RecvDataLeng = 0;
	EXIInputFlag = 0;
	OSRestoreInterrupts(enabled);
	return 0;
}

/**
 * Sends size bytes to the debugger host: waits until the host is not busy,
 * writes the data into the alternating transmit buffer,
 * then posts a mailbox message with a sequence number and the length, waiting for the host to accept it.
 * Always returns 0.
 */
BOOL DBWrite(void* data, u32 size)
{
	u32 value;
	u32 busyFlag;
	BOOL enabled;

	enabled = OSDisableInterrupts();
	do {
		DBGReadStatus(&busyFlag);
	} while (busyFlag & 2);

	++SendCount;

	value = ((SendCount & 1) ? 0x1000 : 0);
	while (!DBGWrite(value | 0x1c000, data, ALIGN_NEXT(size, 4)))
		;

	do {
		DBGReadStatus(&busyFlag);
	} while (busyFlag & 2);

	value = (SendCount << 0x10) | 0x1f000000 | size;
	while (!DBGWriteMailbox(value))
		;

	do {
		while (!DBGReadStatus(&busyFlag))
			;
	} while (busyFlag & 2);

	OSRestoreInterrupts(enabled);

	return 0;
}

/** Empty; the debugger link needs no explicit open. */
void DBOpen(void) { }

/** Empty; the debugger link needs no explicit close. */
void DBClose(void) { }
