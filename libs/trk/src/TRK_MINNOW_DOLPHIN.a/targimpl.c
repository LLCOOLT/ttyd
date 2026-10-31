typedef int BOOL;
typedef int DSError;
typedef unsigned long size_t;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct TRKBuffer TRKBuffer;

typedef struct TRKEvent {
    int eventType;
    int eventID;
    int msgBufID;
} TRKEvent;

typedef struct memRange {
    u8* start;
    u8* end;
    BOOL readable;
    BOOL writeable;
} memRange;

typedef struct StopInfo_PPC {
    u32 PC;
    u32 PCInstruction;
    u16 exceptionID;
} StopInfo_PPC;

typedef struct TRKExceptionStatus {
    StopInfo_PPC exceptionInfo;
    u8 inTRK;
    u8 exceptionDetected;
} TRKExceptionStatus;

typedef struct TRKStepStatus {
    BOOL active;
    int type;
    u32 count;
    u32 rangeStart;
    u32 rangeEnd;
} TRKStepStatus;

typedef struct TRKRestoreFlags_PPC {
    u8 TBR;
    u8 DEC;
    u8 linker_padding[10];
} TRKRestoreFlags_PPC;

typedef struct Default_PPC {
    u32 GPR[32];
    u32 PC;
    u32 LR;
    u32 CR;
    u32 CTR;
    u32 XER;
} Default_PPC;

typedef struct Extended1_PPC {
    u32 SR[16];
    u32 TBL;
    u32 TBU;
    u32 HID0;
    u32 HID1;
    u32 MSR;
    u32 PVR;
    u32 IBAT[8];
    u32 DBAT[8];
    u32 SDR1;
    u32 SPRG[4];
    u32 DAR;
    u32 DSISR;
    u32 pad_b4[7];
    u32 DEC;
    u32 pad_d4[31];
    u32 exceptionID;
    u32 pad_154[47];
} Extended1_PPC;

typedef struct ProcessorState_PPC {
    Default_PPC Default;
    u8 Float[0x1A8 - 0x94];
    Extended1_PPC Extended1;
    u8 Extended2[0x430 - 0x1A8 - 0x210];
} ProcessorState_PPC;

typedef struct TRKState_PPC {
    u32 GPR[32];
    u32 LR;
    u32 CTR;
    u32 XER;
    u32 MSR;
    u32 DAR;
    u32 DSISR;
    BOOL isStopped;
    BOOL inputActivated;
    void* inputPendingPtr;
} TRKState_PPC;

void* memset(void* dst, int val, size_t n);
void MWTRACE(u8 level, char* fmt, ...);
void TRK_flush_cache(u32 addr, u32 length);
u32 TRKTargetTranslate(u32 addr);
void TRK__read_aram(void* dst, u32 src, size_t* n);
void TRK__write_aram(void* src, u32 dst, size_t* n);
DSError TRKAppendBuffer_ui32(TRKBuffer* buffer, const u32* data, int count);
DSError TRKReadBuffer_ui32(TRKBuffer* buffer, u32* data, int count);
DSError TRKAppendBuffer_ui8(TRKBuffer* buffer, const u8* data, int count);
DSError TRKAppendBuffer1_ui64(TRKBuffer* buffer, const u64 data);
DSError TRKReadBuffer1_ui64(TRKBuffer* buffer, u64* data);
void TRKConstructEvent(TRKEvent* event, int eventType);
DSError TRKPostEvent(TRKEvent* event);
DSError TRKDoNotifyStopped(int cmd);
DSError HandleOpenFileSupportRequest(const char* path, u8 replyError, u32* param_3, u32* ioResult);
DSError HandleCloseFileSupportRequest(int file_handle, u32* ioResult);
DSError HandlePositionFileSupportRequest(u32 file_handle, u32* position, u8 whence, u32* ioResult);
DSError TRKSuppAccessFile(u32 file_handle, u8* data, size_t* count, u32* io_result, BOOL need_reply, BOOL read);
void TRKSaveExtended1Block(void);
void TRKRestoreExtended1Block(void);
void TRKUARTInterruptHandler(void);


u16 TRK_saved_exceptionID = 0;
TRKState_PPC gTRKState;
ProcessorState_PPC gTRKCPUState;
u8 gTRKSaveState[0x94];
u8 TRKvalue128_temp[0x10];

TRKRestoreFlags_PPC gTRKRestoreFlags = {0, 0};
TRKExceptionStatus gTRKExceptionStatus = {{0, 0, 0}, 1, 0};
TRKStepStatus gTRKStepStatus = {0};

const memRange gTRKMemMap[1] = {{(u8*)0, (u8*)0xFFFFFFFF, 1, 1}};

#define INSTR_NOP 0x60000000
#define INSTR_BLR 0x4E800020
#define INSTR_PSQ_ST(psr, offset, rDest, w, gqr) \
    (0xF0000000 | (psr << 21) | (rDest << 16) | (w << 15) | (gqr << 12) | offset)
#define INSTR_PSQ_L(psr, offset, rSrc, w, gqr) \
    (0xE0000000 | (psr << 21) | (rSrc << 16) | (w << 15) | (gqr << 12) | offset)
#define INSTR_STW(rSrc, offset, rDest) (0x90000000 | (rSrc << 21) | (rDest << 16) | offset)
#define INSTR_LWZ(rDest, offset, rSrc) (0x80000000 | (rDest << 21) | (rSrc << 16) | offset)
#define INSTR_STFD(fprSrc, offset, rDest) (0xD8000000 | (fprSrc << 21) | (rDest << 16) | offset)
#define INSTR_LFD(fprDest, offset, rSrc) (0xC8000000 | (fprDest << 21) | (rSrc << 16) | offset)
#define INSTR_MFSPR(rDest, spr) \
    (0x7C000000 | (rDest << 21) | ((spr & 0xFE0) << 6) | ((spr & 0x1F) << 16) | 0x2A6)
#define INSTR_MTSPR(spr, rSrc) \
    (0x7C000000 | (rSrc << 21) | ((spr & 0xFE0) << 6) | ((spr & 0x1F) << 16) | 0x3A6)

#define SPR_GQR0 912
#define SPR_HID2 920
#define SPR_FPECR 1022

void TRKPostInterruptEvent(void);
void TRKInterruptHandler(void);
void TRKExceptionHandler(void);
void TRKSwapAndGo(void);
void TRKInterruptHandlerEnableInterrupts(void);
u32 __TRK_get_MSR(void);
void __TRK_set_MSR(u32 msr);
void TRK_ppc_memcpy(void* dest, const void* src, int n, u32 param_4, u32 param_5);
void ReadFPSCR(void* data);
void WriteFPSCR(void* data);

/** Assembly: returns the CPU's machine state register. */
asm u32 __TRK_get_MSR(void) {
    nofralloc
    mfmsr r3
    blr
}

/** Assembly: writes the CPU's machine state register. */
asm void __TRK_set_MSR(register u32 msr) {
    nofralloc
    mtmsr r3
    blr
}

/**
 * Assembly: copies n bytes one byte at a time, switching the MSR to param_5 around each load
 * and to param_4 around each store, so source and destination can use different address translation;
 * restores the MSR when done.
 */
asm void TRK_ppc_memcpy(register void* dest, register const void* src, register int n, register u32 param_4, register u32 param_5) {
    nofralloc
    mfmsr r8
    li r10, 0x0
L_8025B07C:
    cmpw r10, r5
    beq L_8025B0A4
    mtmsr r7
    sync
    lbzx r9, r10, r4
    mtmsr r6
    sync
    stbx r9, r10, r3
    addi r10, r10, 0x1
    b L_8025B07C
L_8025B0A4:
    mtmsr r8
    sync
    blr
}

/**
 * Assembly entry for exceptions that reach the stub:
 * saves SRR0/SRR1 and CR scratch, switches to the stub's MSR and records the exception id.
 * For an external interrupt (0x500) it first runs TRKUARTInterruptHandler and returns to the game
 * if no debug input is pending.
 * Otherwise it saves the game's registers into gTRKCPUState and posts an interrupt event.
 */
asm void TRKInterruptHandler(void) {
    nofralloc
    mtspr 26, r2
    mtspr 27, r4
    mfspr r4, 275
    mfcr r2
    mtspr 275, r2
    lis r2, gTRKState@h
    ori r2, r2, gTRKState@l
    lwz r2, 0x8c(r2)
    ori r2, r2, 0x8002
    xori r2, r2, 0x8002
    sync
    mtmsr r2
    sync
    lis r2, TRK_saved_exceptionID@h
    ori r2, r2, TRK_saved_exceptionID@l
    sth r3, 0x0(r2)
    cmpwi r3, 0x500
    bne L_8025B178
    lis r2, gTRKCPUState@h
    ori r2, r2, gTRKCPUState@l
    mfspr r3, 8
    stw r3, 0x42c(r2)
    bl TRKUARTInterruptHandler
    lis r2, gTRKCPUState@h
    ori r2, r2, gTRKCPUState@l
    lwz r3, 0x42c(r2)
    mtspr 8, r3
    lis r2, gTRKState@h
    ori r2, r2, gTRKState@l
    lwz r2, 0xa0(r2)
    lbz r2, 0x0(r2)
    cmpwi r2, 0x0
    beq L_8025B15C
    lis r2, gTRKExceptionStatus@h
    ori r2, r2, gTRKExceptionStatus@l
    lbz r2, 0xc(r2)
    cmpwi r2, 0x1
    beq L_8025B15C
    lis r2, gTRKState@h
    ori r2, r2, gTRKState@l
    li r3, 0x1
    stb r3, 0x9c(r2)
    b L_8025B178
L_8025B15C:
    lis r2, gTRKSaveState@h
    ori r2, r2, gTRKSaveState@l
    lwz r3, 0x88(r2)
    mtcrf 255, r3
    lwz r3, 0xc(r2)
    lwz r2, 0x8(r2)
    rfi
L_8025B178:
    lis r2, TRK_saved_exceptionID@h
    ori r2, r2, TRK_saved_exceptionID@l
    lhz r3, 0x0(r2)
    lis r2, gTRKExceptionStatus@h
    ori r2, r2, gTRKExceptionStatus@l
    lbz r2, 0xc(r2)
    cmpwi r2, 0x0
    bne TRKExceptionHandler
    lis r2, gTRKCPUState@h
    ori r2, r2, gTRKCPUState@l
    stw r0, 0x0(r2)
    stw r1, 0x4(r2)
    mfspr r0, 273
    stw r0, 0x8(r2)
    sth r3, 0x2f8(r2)
    sth r3, 0x2fa(r2)
    mfspr r0, 274
    stw r0, 0xc(r2)
    stmw r4, 0x10(r2)
    mfspr r27, 26
    mfspr r28, 8
    mfspr r29, 275
    mfspr r30, 9
    mfspr r31, 1
    stmw r27, 0x80(r2)
    bl TRKSaveExtended1Block
    lis r2, gTRKExceptionStatus@h
    ori r2, r2, gTRKExceptionStatus@l
    li r3, 0x1
    stb r3, 0xc(r2)
    lis r2, gTRKState@h
    ori r2, r2, gTRKState@l
    lwz r0, 0x8c(r2)
    sync
    mtmsr r0
    sync
    lwz r0, 0x80(r2)
    mtspr 8, r0
    lwz r0, 0x84(r2)
    mtspr 9, r0
    lwz r0, 0x88(r2)
    mtspr 1, r0
    lwz r0, 0x94(r2)
    mtspr 18, r0
    lwz r0, 0x90(r2)
    mtspr 19, r0
    lmw r3, 0xc(r2)
    lwz r0, 0x0(r2)
    lwz r1, 0x4(r2)
    lwz r2, 0x8(r2)
    b TRKPostInterruptEvent
}

/**
 * Assembly: handles an exception that happens inside the stub itself (such as a bad memory access):
 * records the id and PC in gTRKExceptionStatus,
 * steps the PC past the faulting instruction for the data/instruction fault types and returns,
 * leaving exceptionDetected set so the memory/register accessors report error 0x702.
 */
asm void TRKExceptionHandler(void) {
    nofralloc
    lis r2, gTRKExceptionStatus@h
    ori r2, r2, gTRKExceptionStatus@l
    sth r3, 0x8(r2)
    mfspr r3, 26
    stw r3, 0x0(r2)
    lhz r3, 0x8(r2)
    cmpwi r3, 0x200
    beq L_8025B2B0
    cmpwi r3, 0x300
    beq L_8025B2B0
    cmpwi r3, 0x400
    beq L_8025B2B0
    cmpwi r3, 0x600
    beq L_8025B2B0
    cmpwi r3, 0x700
    beq L_8025B2B0
    cmpwi r3, 0x800
    beq L_8025B2B0
    cmpwi r3, 0x1000
    beq L_8025B2B0
    cmpwi r3, 0x1100
    beq L_8025B2B0
    cmpwi r3, 0x1200
    beq L_8025B2B0
    cmpwi r3, 0x1300
    beq L_8025B2B0
    b L_8025B2BC
L_8025B2B0:
    mfspr r3, 26
    addi r3, r3, 0x4
    mtspr 26, r3
L_8025B2BC:
    lis r2, gTRKExceptionStatus@h
    ori r2, r2, gTRKExceptionStatus@l
    li r3, 0x1
    stb r3, 0xd(r2)
    mfspr r3, 275
    mtcrf 255, r3
    mfspr r2, 273
    mfspr r3, 274
    rfi
}

/**
 * Assembly: saves the stub's own registers into gTRKState,
 * restores the game's context from gTRKCPUState (including the extended block)
 * and returns into the game with rfi. If input is pending when it starts it goes back to post an event.
 */
asm void TRKSwapAndGo(void) {
    nofralloc
    lis r3, gTRKState@h
    ori r3, r3, gTRKState@l
    stmw r0, 0x0(r3)
    mfmsr r0
    stw r0, 0x8c(r3)
    mfspr r0, 8
    stw r0, 0x80(r3)
    mfspr r0, 9
    stw r0, 0x84(r3)
    mfspr r0, 1
    stw r0, 0x88(r3)
    mfspr r0, 18
    stw r0, 0x94(r3)
    mfspr r0, 19
    stw r0, 0x90(r3)
    li r1, -0x7ffe
    nor r1, r1, r1
    mfmsr r3
    and r3, r3, r1
    mtmsr r3
    lis r2, gTRKState@h
    ori r2, r2, gTRKState@l
    lwz r2, 0xa0(r2)
    lbz r2, 0x0(r2)
    cmpwi r2, 0x0
    beq L_8025B35C
    lis r2, gTRKState@h
    ori r2, r2, gTRKState@l
    li r3, 0x1
    stb r3, 0x9c(r2)
    b TRKInterruptHandlerEnableInterrupts
L_8025B35C:
    lis r2, gTRKExceptionStatus@h
    ori r2, r2, gTRKExceptionStatus@l
    li r3, 0x0
    stb r3, 0xc(r2)
    bl TRKRestoreExtended1Block
    lis r2, gTRKCPUState@h
    ori r2, r2, gTRKCPUState@l
    lmw r27, 0x80(r2)
    mtspr 26, r27
    mtspr 8, r28
    mtcrf 255, r29
    mtspr 9, r30
    mtspr 1, r31
    lmw r3, 0xc(r2)
    lwz r0, 0x0(r2)
    lwz r1, 0x4(r2)
    lwz r2, 0x8(r2)
    rfi
}

/**
 * Assembly: the tail used by TRKSwapAndGo when debug input is pending:
 * restores the stub's registers, saved SRRs and CR and jumps to TRKPostInterruptEvent.
 */
asm void TRKInterruptHandlerEnableInterrupts(void) {
    nofralloc
    lis r2, gTRKState@h
    ori r2, r2, gTRKState@l
    lwz r0, 0x8c(r2)
    sync
    mtmsr r0
    sync
    lwz r0, 0x80(r2)
    mtspr 8, r0
    lwz r0, 0x84(r2)
    mtspr 9, r0
    lwz r0, 0x88(r2)
    mtspr 1, r0
    lwz r0, 0x94(r2)
    mtspr 18, r0
    lwz r0, 0x90(r2)
    mtspr 19, r0
    lmw r3, 0xc(r2)
    lwz r0, 0x0(r2)
    lwz r1, 0x4(r2)
    lwz r2, 0x8(r2)
    b TRKPostInterruptEvent
}

/** Assembly: stores the FPSCR (via mffs) as a double at data, preserving f31. */
asm void ReadFPSCR(register void* data) {
    nofralloc
    stwu r1, -0x40(r1)
    stfd f31, 0x10(r1)
    psq_st f31, 0x20(r1), 0, 0
    mffs f31
    stfd f31, 0x0(r3)
    psq_l f31, 0x20(r1), 0, 0
    lfd f31, 0x10(r1)
    addi r1, r1, 0x40
    blr
}

/** Assembly: loads a double from data and writes it to the FPSCR (mtfsf), preserving f31. */
asm void WriteFPSCR(register void* data) {
    nofralloc
    stwu r1, -0x40(r1)
    stfd f31, 0x10(r1)
    psq_st f31, 0x20(r1), 0, 0
    lfd f31, 0x0(r3)
    mtfsf 255, f31
    psq_l f31, 0x20(r1), 0, 0
    lfd f31, 0x10(r1)
    addi r1, r1, 0x40
    blr
}


/**
 * Checks that [addr, addr+length) lies in readable (readWriteable 0)
 * or writeable (1) memory according to gTRKMemMap, which covers the whole 32-bit space.
 * Returns 0 if valid, 0x700 if not.
 */
DSError TRKValidMemory32(const void* addr, size_t length, int readWriteable) {
    DSError err = 0x700;
    const u8* start;
    const u8* end;
    int i;

    start = (const u8*)addr;
    end = ((const u8*)addr + (length - 1));

    if (end < start)
        return 0x700;

    for (i = 0; i < (int)(sizeof(gTRKMemMap) / sizeof(memRange)); i++) {
        if ((start <= (const u8*)gTRKMemMap[i].end) && (end >= (const u8*)gTRKMemMap[i].start)) {
            if (((readWriteable == 0) && !gTRKMemMap[i].readable) ||
                ((readWriteable == 1) && !gTRKMemMap[i].writeable)) {
                err = 0x700;
            } else {
                err = 0;

                if (start < (const u8*)gTRKMemMap[i].start)
                    err = TRKValidMemory32(start, (u32)((const u8*)gTRKMemMap[i].start - start), readWriteable);

                if ((err == 0) && (end > (const u8*)gTRKMemMap[i].end))
                    err = TRKValidMemory32((const u8*)gTRKMemMap[i].end, (u32)(end - (const u8*)gTRKMemMap[i].end),
                                           readWriteable);
            }
            break;
        }
    }

    return err;
}

/**
 * Reads or writes target memory for the debugger:
 * translates the address, validates it, copies with TRK_ppc_memcpy under the right MSR and, after a write,
 * flushes the caches. A fault while copying gives 0x702; *length is set to 0 on failure.
 */
DSError TRKTargetAccessMemory(void* data, u32 start, size_t* length, int accessOptions, BOOL read) {
    DSError error;
    u32 target_msr;
    u32 trans_start;
    TRKExceptionStatus tempExceptionStatus = gTRKExceptionStatus;

    gTRKExceptionStatus.exceptionDetected = 0;

    trans_start = TRKTargetTranslate(start);
    error = TRKValidMemory32((void*)trans_start, *length, read ? 0 : 1);

    if (error != 0) {
        *length = 0;
    } else {
        u32 external_msr;

        target_msr = __TRK_get_MSR();
        external_msr = target_msr | (gTRKCPUState.Extended1.MSR & 0x10);

        if (read) {
            TRK_ppc_memcpy(data, (void*)trans_start, *length, target_msr, external_msr);
        } else {
            TRK_ppc_memcpy((void*)trans_start, data, *length, external_msr, target_msr);
            TRK_flush_cache(trans_start, *length);
            if (start != trans_start)
                TRK_flush_cache(start, *length);
        }
    }

    if (gTRKExceptionStatus.exceptionDetected) {
        error = 0x702;
        *length = 0;
    }

    gTRKExceptionStatus = tempExceptionStatus;
    return error;
}

/** Reads one 4-byte instruction word at start into *data; returns 0x700 if the read fails or comes up short. */
DSError TRKTargetReadInstruction(void* data, u32 start) {
    DSError error;
    size_t registersLength = 4;

    error = TRKTargetAccessMemory(data, start, &registersLength, 0, 1);

    if (error == 0 && registersLength != 4)
        error = 0x700;

    return error;
}

/**
 * Reads or writes the debugger's "default" register block (GPR0-31 plus the next few registers,
 * up to index 0x24) in the saved CPU state, moving the words to or from the message buffer.
 * Error 0x701 means the range is out of bounds and 0x702 means a memory exception happened during the access.
 */
DSError TRKTargetAccessDefault(u32 firstRegister, u32 lastRegister, TRKBuffer* b, size_t* registersLengthPtr,
                               BOOL read) {
    DSError error;
    u32 count;
    u32* data;
    TRKExceptionStatus tempExceptionStatus;

    if (lastRegister > 0x24)
        return 0x701;

    tempExceptionStatus = gTRKExceptionStatus;
    gTRKExceptionStatus.exceptionDetected = 0;
    data = gTRKCPUState.Default.GPR + firstRegister;
    count = (lastRegister - firstRegister) + 1;
    *registersLengthPtr = count * sizeof(u32);

    if (read)
        error = TRKAppendBuffer_ui32(b, data, count);
    else
        error = TRKReadBuffer_ui32(b, data, count);

    if (gTRKExceptionStatus.exceptionDetected) {
        *registersLengthPtr = 0;
        error = 0x702;
    }

    gTRKExceptionStatus = tempExceptionStatus;
    return error;
}

/**
 * Runs a tiny instruction sequence (built in a stack array,
 * flushed to the instruction cache) that moves a register to or from memory at the given pointer;
 * the shared back end of the SPR, floating point and paired-single accessors.
 */
static inline DSError TRKPPCAccessSpecialReg(void* value, u32* access_func, BOOL read) {
    typedef void (*asm_access_type)(void*, void*);
    asm_access_type asm_access;

    access_func[9] = INSTR_BLR;
    asm_access = (asm_access_type)access_func;
    TRK_flush_cache((u32)access_func, 0x28);
    (*asm_access)(value, (void*)&TRKvalue128_temp);
    return 0;
}

/**
 * Reads or writes the special-purpose register with the given number by assembling mfspr+stw or lwz+mtspr
 * and running it.
 */
static inline DSError TRKPPCAccessSPR(void* value, u32 spr_register_num, BOOL read) {
    u32 access_func[10] = {INSTR_NOP, INSTR_NOP, INSTR_NOP, INSTR_NOP, INSTR_NOP,
                           INSTR_NOP, INSTR_NOP, INSTR_NOP, INSTR_NOP, INSTR_NOP};

    if (read) {
        access_func[0] = INSTR_MFSPR(4, spr_register_num);
        access_func[1] = INSTR_STW(4, 0, 3);
    } else {
        access_func[0] = INSTR_LWZ(4, 0, 3);
        access_func[1] = INSTR_MTSPR(spr_register_num, 4);
    }

    return TRKPPCAccessSpecialReg(value, access_func, read);
}

/** Reads or writes one Gekko paired-single register by assembling a psq_st or psq_l for it and running it. */
static inline DSError TRKPPCAccessPairedSingleRegister(void* srcDestPtr, u32 psr, BOOL read) {
    u32 access_func[10] = {INSTR_NOP, INSTR_NOP, INSTR_NOP, INSTR_NOP, INSTR_NOP,
                           INSTR_NOP, INSTR_NOP, INSTR_NOP, INSTR_NOP, INSTR_NOP};

    if (read)
        access_func[0] = INSTR_PSQ_ST(psr, 0, 3, 0, 0);
    else
        access_func[0] = INSTR_PSQ_L(psr, 0, 3, 0, 0);

    return TRKPPCAccessSpecialReg(srcDestPtr, access_func, read);
}

/**
 * Reads or writes floating point register 0-31 by assembling stfd/lfd;
 * index 0x20 is the FPSCR and 0x21 is the FPECR (SPR 1022),
 * both returned as 64-bit values with the upper half zero.
 */
static inline DSError TRKPPCAccessFPRegister(void* srcDestPtr, u32 fpr, BOOL read) {
    DSError error = 0;
    u32 access_func[10] = {INSTR_NOP, INSTR_NOP, INSTR_NOP, INSTR_NOP, INSTR_NOP,
                           INSTR_NOP, INSTR_NOP, INSTR_NOP, INSTR_NOP, INSTR_NOP};

    if (fpr < 0x20) {
        if (read)
            access_func[0] = INSTR_STFD(fpr, 0, 3);
        else
            access_func[0] = INSTR_LFD(fpr, 0, 3);

        error = TRKPPCAccessSpecialReg(srcDestPtr, access_func, read);
    } else if (fpr == 0x20) {
        if (read)
            ReadFPSCR(srcDestPtr);
        else
            WriteFPSCR(srcDestPtr);

        *(u64*)srcDestPtr &= 0xFFFFFFFF;
    } else if (fpr == 0x21) {
        if (!read)
            *(u32*)srcDestPtr = *((u32*)(srcDestPtr) + 1);

        error = TRKPPCAccessSPR(srcDestPtr, SPR_FPECR, read);

        if (read)
            *(u64*)srcDestPtr = *(u32*)srcDestPtr & 0xFFFFFFFFULL;
    }

    return error;
}

/**
 * Reads or writes floating point registers firstRegister to lastRegister (up to 0x21: f0-f31, FPSCR, FPECR) as
 * 64-bit values, after enabling the FPU in the MSR; 0x701 for a bad range, 0x702 on a fault.
 */
DSError TRKTargetAccessFP(u32 firstRegister, u32 lastRegister, TRKBuffer* b, size_t* registerStorageSize, BOOL read) {
    u64 temp;
    DSError error;
    TRKExceptionStatus tempExceptionStatus;
    u32 current;

    if (lastRegister > 0x21)
        return 0x701;

    tempExceptionStatus = gTRKExceptionStatus;
    gTRKExceptionStatus.exceptionDetected = 0;

    __TRK_set_MSR(__TRK_get_MSR() | 0x2000);

    *registerStorageSize = 0;
    error = 0;

    for (current = firstRegister; (current <= lastRegister) && (error == 0);
         current++, *registerStorageSize += sizeof(u64)) {
        if (read) {
            TRKPPCAccessFPRegister(&temp, current, read);
            error = TRKAppendBuffer1_ui64(b, temp);
        } else {
            TRKReadBuffer1_ui64(b, &temp);
            error = TRKPPCAccessFPRegister(&temp, current, read);
        }
    }

    if (gTRKExceptionStatus.exceptionDetected) {
        *registerStorageSize = 0;
        error = 0x702;
    }

    gTRKExceptionStatus = tempExceptionStatus;
    return error;
}

/**
 * Reads or writes the "extended 1" register block (special-purpose registers, indices 0-0x60) in the saved CPU
 * state.
 * Writes that touch the time base or the decrementer set a restore flag so the value is applied
 * when the game resumes. Errors: 0x701 out of range, 0x702 exception during access.
 */
DSError TRKTargetAccessExtended1(u32 firstRegister, u32 lastRegister, TRKBuffer* b, size_t* registersLengthPtr,
                                 BOOL read) {
    TRKExceptionStatus tempExceptionStatus;
    u32* data;
    DSError error;
    u32 count;

    if (lastRegister > 0x60)
        return 0x701;

    tempExceptionStatus = gTRKExceptionStatus;
    gTRKExceptionStatus.exceptionDetected = 0;

    *registersLengthPtr = 0;

    if (firstRegister <= lastRegister) {
        data = (u32*)&gTRKCPUState.Extended1 + firstRegister;
        count = lastRegister - firstRegister + 1;
        *registersLengthPtr += count * sizeof(u32);

        if (read) {
            error = TRKAppendBuffer_ui32(b, data, count);
        } else {
            if (data <= &gTRKCPUState.Extended1.TBU && (data + count - 1) >= &gTRKCPUState.Extended1.TBL)
                gTRKRestoreFlags.TBR = 1;

            if (data <= &gTRKCPUState.Extended1.DEC && (data + count - 1) >= &gTRKCPUState.Extended1.DEC)
                gTRKRestoreFlags.DEC = 1;

            error = TRKReadBuffer_ui32(b, data, count);
        }
    }

    if (gTRKExceptionStatus.exceptionDetected) {
        *registersLengthPtr = 0;
        error = 0x702;
    }

    gTRKExceptionStatus = tempExceptionStatus;
    return error;
}

/**
 * Reads or writes the Gekko paired-single registers ps0-ps31 (64 bits each, indices 0-0x1F):
 * it first enables paired-single quantized load/store through HID2 and clears GQR0,
 * then moves each register through the message buffer.
 * Errors: 0x701 out of range, 0x702 exception during access.
 */
DSError TRKTargetAccessExtended2(u32 firstRegister, u32 lastRegister, TRKBuffer* b, size_t* registerStorageSize,
                                 BOOL read) {
    TRKExceptionStatus tempExceptionStatus;
    u32 value_buf0[1];
    u32 value_buf[2];
    DSError error;
    u32 current;

    if (lastRegister > 0x1F)
        return 0x701;

    tempExceptionStatus = gTRKExceptionStatus;
    gTRKExceptionStatus.exceptionDetected = 0;

    TRKPPCAccessSPR(value_buf0, SPR_HID2, 1);
    value_buf0[0] |= 0xA0000000;
    TRKPPCAccessSPR(value_buf0, SPR_HID2, 0);
    value_buf0[0] = 0;
    TRKPPCAccessSPR(value_buf0, SPR_GQR0, 0);

    *registerStorageSize = 0;
    error = 0;

    for (current = firstRegister; (current <= lastRegister) && (error == 0);
         current++, *registerStorageSize += sizeof(u64)) {
        if (read) {
            TRKPPCAccessPairedSingleRegister((u64*)value_buf, current, read);
            error = TRKAppendBuffer1_ui64(b, *(u64*)value_buf);
        } else {
            TRKReadBuffer1_ui64(b, (u64*)value_buf);
            error = TRKPPCAccessPairedSingleRegister((u64*)value_buf, current, read);
        }
    }

    if (gTRKExceptionStatus.exceptionDetected) {
        *registerStorageSize = 0;
        error = 0x702;
    }

    gTRKExceptionStatus = tempExceptionStatus;
    return error;
}

/**
 * Called after the game's context is saved: if the stub itself caused the interrupt (inputActivated) it just
 * clears that; otherwise posts an event, type 5 for the support-request instruction 0x0FE00000 at a program
 * or trace exception, type 3 for other program/trace exceptions and type 4 for the rest.
 */
void TRKPostInterruptEvent(void) {
    int eventType;
    u32 inst;
    TRKEvent event;

    if (gTRKState.inputActivated) {
        gTRKState.inputActivated = 0;
    } else {
        switch (gTRKCPUState.Extended1.exceptionID & 0xFFFF) {
        case 0x700:
        case 0xD00:
            TRKTargetReadInstruction(&inst, gTRKCPUState.Default.PC);

            if (inst == 0x0FE00000)
                eventType = 5;
            else
                eventType = 3;
            break;
        default:
            eventType = 4;
            break;
        }

        TRKConstructEvent(&event, eventType);
        TRKPostEvent(&event);
    }
}

/** Sets the stub's stopped flag (the inline form of TRKTargetSetStopped). */
static inline void TRKTargetSetStopped_inline(u32 stopped) {
    gTRKState.isStopped = stopped;
}

/**
 * Decides whether a step is finished: not done while a single-step still has instructions left,
 * or while a range- step's PC is still inside the range;
 * also true when no step is active or the trap was not a trace exception (0xD00).
 */
static inline BOOL TRKTargetStepDone(void) {
    BOOL result = 1;

    if (gTRKStepStatus.active && ((u16)gTRKCPUState.Extended1.exceptionID) == 0xD00) {
        switch (gTRKStepStatus.type) {
        case 0:
            if (gTRKStepStatus.count > 0)
                result = 0;
            break;
        case 1:
            if (gTRKCPUState.Default.PC >= gTRKStepStatus.rangeStart &&
                gTRKCPUState.Default.PC <= gTRKStepStatus.rangeEnd)
                result = 0;
            break;
        default:
            break;
        }
    }

    return result;
}

/**
 * Starts one step: sets the trace-enable bit (0x400) in the saved MSR,
 * counts down a single-step's instructions and marks the game as running.
 */
static inline DSError TRKTargetDoStep(void) {
    gTRKStepStatus.active = 1;
    MWTRACE(1, "TargetDoStep()\n");
    gTRKCPUState.Extended1.MSR |= 0x400;

    if (gTRKStepStatus.type == 0 || gTRKStepStatus.type == 0x10)
        gTRKStepStatus.count--;

    TRKTargetSetStopped_inline(0);
    return 0;
}

/**
 * Called when a trap arrives during a step: clears the trace bit,
 * then ends the step if it is done or restarts it if not. Returns whether a step is still active.
 */
static inline BOOL TRKTargetCheckStep(void) {
    if (gTRKStepStatus.active) {
        gTRKCPUState.Extended1.MSR &= ~0x400;

        if (TRKTargetStepDone())
            gTRKStepStatus.active = 0;
        else
            TRKTargetDoStep();
    }

    return gTRKStepStatus.active;
}

/**
 * Handles an interrupt event (types 3 and 4): unless it is the middle of a step,
 * marks the game stopped and notifies the host with a stop report. Returns the notification status.
 */
DSError TRKTargetInterrupt(TRKEvent* event) {
    DSError result = 0;

    switch (event->eventType) {
    case 3:
    case 4:
        if (!TRKTargetCheckStep()) {
            TRKTargetSetStopped_inline(1);
            result = TRKDoNotifyStopped(0x90);
        }
        break;
    default:
        break;
    }

    return result;
}

typedef struct NotifyInfo {
    u32 length;
    u8 commandID;
    u8 pad5[3];
    u32 PC;
    u32 instruction;
    u32 exceptionID;
    u8 pad14[0x2C];
} NotifyInfo;

/** Appends a stop notification (command 0x90: PC, the instruction at the PC, exception id) to a message buffer. */
void TRKTargetAddStopInfo(TRKBuffer* buffer) {
    u32 instruction;
    NotifyInfo info;

    memset(&info, 0, sizeof(NotifyInfo));
    info.length = sizeof(NotifyInfo);
    info.commandID = 0x90;
    info.PC = gTRKCPUState.Default.PC;
    TRKTargetReadInstruction(&instruction, gTRKCPUState.Default.PC);
    info.instruction = instruction;
    info.exceptionID = (u16)gTRKCPUState.Extended1.exceptionID;
    TRKAppendBuffer_ui8(buffer, (u8*)&info, sizeof(NotifyInfo));
}

/** Appends an exception notification (command 0x91) using the PC and exception id recorded in gTRKExceptionStatus. */
void TRKTargetAddExceptionInfo(TRKBuffer* buffer) {
    u32 instruction;
    NotifyInfo info;

    memset(&info, 0, sizeof(NotifyInfo));
    info.length = sizeof(NotifyInfo);
    info.commandID = 0x91;
    info.PC = gTRKExceptionStatus.exceptionInfo.PC;
    TRKTargetReadInstruction(&instruction, gTRKExceptionStatus.exceptionInfo.PC);
    info.instruction = instruction;
    info.exceptionID = gTRKExceptionStatus.exceptionInfo.exceptionID;
    TRKAppendBuffer_ui8(buffer, (u8*)&info, sizeof(NotifyInfo));
}

/** Starts a single-step of count instructions; step-over is not supported and returns 0x703. */
DSError TRKTargetSingleStep(u32 count, BOOL stepOver) {
    if (stepOver)
        return 0x703;

    gTRKStepStatus.count = count;
    gTRKStepStatus.type = 0;
    TRKTargetDoStep();
    return 0;
}

/** Starts a step that runs until the PC leaves [rangeStart, rangeEnd]; step-over is not supported and returns 0x703. */
DSError TRKTargetStepOutOfRange(u32 rangeStart, u32 rangeEnd, BOOL stepOver) {
    if (stepOver)
        return 0x703;

    gTRKStepStatus.rangeStart = rangeStart;
    gTRKStepStatus.rangeEnd = rangeEnd;
    gTRKStepStatus.type = 1;
    TRKTargetDoStep();
    return 0;
}

/** Returns the stopped game's saved program counter. */
u32 TRKTargetGetPC(void) {
    return gTRKCPUState.Default.PC;
}

/**
 * Handles a request the game raised through the support instruction:
 * GPR3 holds the command (0xD0 write, 0xD1 read, 0xD2 open, 0xD3 close, 0xD4 position),
 * the other GPRs its arguments.
 * It forwards it to the host, puts the result in GPR3 and skips the trap instruction;
 * an unknown command is turned into an ordinary interrupt event.
 */
DSError TRKTargetSupportRequest(void) {
    DSError error;
    size_t* length;
    int io_result;
    u32 spec;
    int cmd;
    TRKEvent event;

    cmd = gTRKCPUState.Default.GPR[3];

    if (cmd != 0xD1 && cmd != 0xD0 && cmd != 0xD2 && cmd != 0xD3 && cmd != 0xD4) {
        TRKConstructEvent(&event, 4);
        TRKPostEvent(&event);
        return 0;
    }

    if (cmd == 0xD2) {
        error = HandleOpenFileSupportRequest((char*)gTRKCPUState.Default.GPR[4], gTRKCPUState.Default.GPR[5],
                                             (u32*)gTRKCPUState.Default.GPR[6], (u32*)&io_result);
        if (io_result == 0 && error != 0)
            io_result = 1;
        gTRKCPUState.Default.GPR[3] = io_result;
    } else if (cmd == 0xD3) {
        error = HandleCloseFileSupportRequest(gTRKCPUState.Default.GPR[4], (u32*)&io_result);
        if (io_result == 0 && error != 0)
            io_result = 1;
        gTRKCPUState.Default.GPR[3] = io_result;
    } else if (cmd == 0xD4) {
        spec = *((u32*)gTRKCPUState.Default.GPR[5]);
        error = HandlePositionFileSupportRequest(gTRKCPUState.Default.GPR[4], &spec, gTRKCPUState.Default.GPR[6],
                                                 (u32*)&io_result);
        if (io_result == 0 && error != 0)
            io_result = 1;
        gTRKCPUState.Default.GPR[3] = io_result;
        *((u32*)gTRKCPUState.Default.GPR[5]) = spec;
    } else {
        length = (size_t*)gTRKCPUState.Default.GPR[5];
        error = TRKSuppAccessFile(gTRKCPUState.Default.GPR[4], (u8*)gTRKCPUState.Default.GPR[6], length, (u32*)&io_result, 1,
                                  cmd == 0xD1);
        if (io_result == 0 && error != 0)
            io_result = 1;
        gTRKCPUState.Default.GPR[3] = io_result;
        if (cmd == 0xD1)
            TRK_flush_cache(gTRKCPUState.Default.GPR[6], *length);
    }

    gTRKCPUState.Default.PC += 4;
    return error;
}

/** Returns whether the game is currently stopped under the debugger. */
BOOL TRKTargetStopped(void) {
    return gTRKState.isStopped;
}

/** Sets or clears the stopped flag. */
void TRKTargetSetStopped(u32 stopped) {
    gTRKState.isStopped = stopped;
}

/** Marks the game stopped; always returns 0. */
DSError TRKTargetStop(void) {
    gTRKState.isStopped = 1;
    return 0;
}

/** Remembers the pointer to the flag byte that says debug input is pending. */
void TRKTargetSetInputPendingPtr(void* ptr) {
    gTRKState.inputPendingPtr = ptr;
}

/**
 * Reads or writes auxiliary RAM for the debugger via TRK__read_aram / TRK__write_aram;
 * a fault gives 0x702 with length 0.
 */
DSError TRKTargetAccessARAM(void* data, u32 start, size_t* length, BOOL read) {
    DSError error = 0;
    TRKExceptionStatus tempExceptionStatus = gTRKExceptionStatus;

    gTRKExceptionStatus.exceptionDetected = 0;

    if (read)
        TRK__read_aram(data, start, length);
    else
        TRK__write_aram(data, start, length);

    if (gTRKExceptionStatus.exceptionDetected) {
        error = 0x702;
        *length = 0;
    }

    gTRKExceptionStatus = tempExceptionStatus;
    return error;
}
