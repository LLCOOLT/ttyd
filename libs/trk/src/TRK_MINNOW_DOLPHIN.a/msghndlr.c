typedef int BOOL;
typedef int DSError;
typedef unsigned long size_t;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TRKBuffer {
    unsigned int mutex;
    BOOL isInUse;
    u32 length;
    u32 position;
    u8 data[0x880];
} TRKBuffer;

typedef struct CommandReply {
    u32 length;
    u8 commandID;
    u8 pad5[3];
    u8 replyError;
    u8 pad9[0x37];
} CommandReply;

typedef struct TRKEvent {
    int eventType;
    int eventID;
    int msgBufID;
} TRKEvent;

void* memset(void* dst, int val, size_t n);
void MWTRACE(u8 level, char* fmt, ...);
BOOL usr_puts_serial(const char* msg);
void SetUseSerialIO(u8 sio);
int TRKWriteUARTN(const void* bytes, u32 length);
DSError TRKMessageSend(TRKBuffer* b);
void TRKResetBuffer(TRKBuffer* msg, BOOL keepData);
DSError TRKSetBufferPosition(TRKBuffer* msg, u32 pos);
DSError TRKAppendBuffer(TRKBuffer* msg, const void* data, size_t length);
DSError TRKReadBuffer(TRKBuffer* msg, void* data, size_t length);
DSError TRKAppendBuffer_ui8(TRKBuffer* buffer, const u8* data, int count);
void TRKConstructEvent(TRKEvent* event, int eventType);
DSError TRKPostEvent(TRKEvent* event);
void __TRK_reset(void);
void __TRK_copy_vectors(void);
DSError TRKTargetAccessARAM(void* data, u32 start, u32* length, BOOL read);
DSError TRKTargetAccessMemory(void* data, u32 start, u32* length, int accessType, BOOL read);
DSError TRKTargetAccessDefault(u32 firstRegister, u32 lastRegister, TRKBuffer* b, u32* registersLengthPtr, BOOL read);
DSError TRKTargetAccessFP(u32 firstRegister, u32 lastRegister, TRKBuffer* b, u32* registersLengthPtr, BOOL read);
DSError TRKTargetAccessExtended1(u32 firstRegister, u32 lastRegister, TRKBuffer* b, u32* registersLengthPtr, BOOL read);
DSError TRKTargetAccessExtended2(u32 firstRegister, u32 lastRegister, TRKBuffer* b, u32* registersLengthPtr, BOOL read);
BOOL TRKTargetStopped(void);
DSError TRKTargetContinue(void);
DSError TRKTargetStop(void);
u32 TRKTargetGetPC(void);
DSError TRKTargetSingleStep(u32 count, BOOL stepOver);
DSError TRKTargetStepOutOfRange(u32 rangeStart, u32 rangeEnd, BOOL stepOver);

static BOOL IsTRKConnected;

/**
 * Builds a 0x40-byte reply header (command 0x80, the given error byte) and writes it straight to the host link;
 * the reply tells the debugger whether its command succeeded.
 */
static inline void TRKSendReply(u8 replyError) {
    CommandReply reply;

    memset(&reply, 0, sizeof(CommandReply));
    reply.commandID = 0x80;
    reply.length = sizeof(CommandReply);
    reply.replyError = replyError;
    TRKWriteUARTN(&reply, sizeof(CommandReply));
}

/** Sends the already filled message buffer to the host as the reply and returns the send status. */
static inline DSError TRKSendACK(TRKBuffer* buffer) {
    DSError err;

    MWTRACE(1, "SendACK : Calling MessageSend\n");
    err = TRKMessageSend(buffer);
    MWTRACE(1, "MessageSend err : %ld\n", err);
    return err;
}

/** Trace helper that dumps a block of bytes as hex, 16 per line, through MWTRACE (compiled out here). */
void OutputData(u8* data, int length) {
    int i;

    for (i = 0; i < length; i++) {
        MWTRACE(8, "%02x ", data[i]);
        if (i % 16 == 15)
            MWTRACE(8, "\n");
    }

    MWTRACE(8, "\n");
}

/** Returns whether a debugger has sent a connect command and not yet disconnected. */
BOOL GetTRKConnected(void) {
    return IsTRKConnected;
}

/** Sets the connected flag; usr_puts_serial clears it temporarily so its text is not sent over the debug link. */
void SetTRKConnected(BOOL connected) {
    IsTRKConnected = connected;
}

/** Handles the connect command (0x01): marks the stub connected and replies OK. */
DSError TRKDoConnect(TRKBuffer* buffer) {
    IsTRKConnected = 1;
    TRKSendReply(0);
    return 0;
}

/**
 * Handles the disconnect command (0x02): marks the stub disconnected,
 * replies OK and posts a shutdown event so the main loop ends.
 */
DSError TRKDoDisconnect(TRKBuffer* buffer) {
    TRKEvent event;

    IsTRKConnected = 0;
    TRKSendReply(0);
    TRKConstructEvent(&event, 1);
    TRKPostEvent(&event);
    return 0;
}

/** Handles the reset command (0x03): replies OK, then resets the whole system through OSResetSystem. */
DSError TRKDoReset(TRKBuffer* buffer) {
    TRKSendReply(0);
    __TRK_reset();
    return 0;
}

/**
 * Handles the override command (0x07): replies OK,
 * then installs the stub's handlers over the game's exception vectors.
 */
DSError TRKDoOverride(TRKBuffer* buffer) {
    TRKSendReply(0);
    __TRK_copy_vectors();
    return 0;
}

/** Handler for the versions command (0x04); does nothing here (no reply is sent) and returns 0. */
DSError TRKDoVersions(TRKBuffer* buffer) {
    return 0;
}

/** Handler for the support-mask command (0x05); does nothing here (no reply is sent) and returns 0. */
DSError TRKDoSupportMask(TRKBuffer* buffer) {
    return 0;
}

/**
 * Handles the read-memory command (0x10): reads the requested length from the start address (main memory, or
 * ARAM when option bit 0x40 is set) into the reply after a 0x40-byte header.
 * Failures are mapped to protocol error codes.
 */
DSError TRKDoReadMemory(TRKBuffer* buffer) {
    DSError error;
    u8 replyError;
    u8 tempBuf[0x820] __attribute__((aligned(32)));
    u32 length;
    u16 msg_length;
    u32 msg_start;
    u8 msg_options;
    CommandReply reply;

    msg_start = *(u32*)(buffer->data + 0x10);
    msg_length = *(u16*)(buffer->data + 0xC);
    msg_options = buffer->data[8];

    MWTRACE(1, "ReadMemory (0x%02x) : 0x%08x 0x%08x 0x%08x\n", buffer->data[4], msg_start, msg_length, msg_options);

    if (msg_options & 2) {
        TRKSendReply(0x12);
        return 0;
    }

    length = msg_length;

    if (msg_options & 0x40)
        error = TRKTargetAccessARAM(tempBuf, msg_start, &length, 1);
    else
        error = TRKTargetAccessMemory(tempBuf, msg_start, &length, (msg_options & 8) ? 0 : 1, 1);

    TRKResetBuffer(buffer, 0);

    if (error == 0) {
        memset(&reply, 0, sizeof(CommandReply));
        reply.replyError = error;
        reply.length = length + sizeof(CommandReply);
        reply.commandID = 0x80;
        TRKAppendBuffer(buffer, &reply, sizeof(CommandReply));

        if (msg_options & 0x40)
            error = TRKAppendBuffer(buffer, tempBuf + (msg_start & 31), length);
        else
            error = TRKAppendBuffer(buffer, tempBuf, length);
    }

    if (error != 0) {
        switch (error) {
        case 0x702:
            replyError = 0x15;
            break;
        case 0x700:
            replyError = 0x13;
            break;
        case 0x704:
            replyError = 0x21;
            break;
        case 0x705:
            replyError = 0x22;
            break;
        case 0x706:
            replyError = 0x20;
            break;
        case 0x701:
        case 0x703:
        default:
            replyError = 3;
            break;
        }

        TRKSendReply(replyError);
        return 0;
    }

    return TRKSendACK(buffer);
}

/**
 * Handles the write-memory command (0x11): copies the bytes that follow the header to the start address (main
 * memory or ARAM) and replies OK or with the mapped error code.
 */
DSError TRKDoWriteMemory(TRKBuffer* buffer) {
    DSError error;
    u8 replyError;
    u8 tempBuf[0x820] __attribute__((aligned(32)));
    u32 length;
    u16 msg_length;
    u32 msg_start;
    u8 msg_options;
    CommandReply reply;

    msg_start = *(u32*)(buffer->data + 0x10);
    msg_length = *(u16*)(buffer->data + 0xC);
    msg_options = buffer->data[8];

    MWTRACE(1, "WriteMemory (0x%02x) : 0x%08x 0x%08x 0x%08x\n", buffer->data[4], msg_start, msg_length, msg_options);

    if (msg_options & 2) {
        TRKSendReply(0x12);
        return 0;
    }

    length = msg_length;
    TRKSetBufferPosition(buffer, sizeof(CommandReply));

    if (msg_options & 0x40) {
        TRKReadBuffer(buffer, tempBuf + (msg_start & 31), length);
        error = TRKTargetAccessARAM(tempBuf, msg_start, &length, 0);
    } else {
        TRKReadBuffer(buffer, tempBuf, length);
        error = TRKTargetAccessMemory(tempBuf, msg_start, &length, (msg_options & 8) ? 0 : 1, 0);
    }

    TRKResetBuffer(buffer, 0);

    if (error == 0) {
        memset(&reply, 0, sizeof(CommandReply));
        reply.length = sizeof(CommandReply);
        reply.commandID = 0x80;
        reply.replyError = error;
        error = TRKAppendBuffer(buffer, &reply, sizeof(CommandReply));
    }

    if (error != 0) {
        switch (error) {
        case 0x702:
            replyError = 0x15;
            break;
        case 0x700:
            replyError = 0x13;
            break;
        case 0x704:
            replyError = 0x21;
            break;
        case 0x705:
            replyError = 0x22;
            break;
        case 0x706:
            replyError = 0x20;
            break;
        case 0x701:
        case 0x703:
        default:
            replyError = 3;
            break;
        }

        TRKSendReply(replyError);
        return 0;
    }

    return TRKSendACK(buffer);
}

/**
 * Handles the read-registers command (0x12): replies with all default (GPR/PC/LR/CR/CTR/XER), floating point,
 * extended 1 and paired-single register groups, in that order.
 * Rejects a first register past the last with error 0x14.
 */
DSError TRKDoReadRegisters(TRKBuffer* buffer) {
    DSError error;
    u8 replyError;
    u32 registerDataLength;
    u16 msg_firstRegister;
    u16 msg_lastRegister;
    CommandReply reply;

    msg_firstRegister = *(u16*)(buffer->data + 0xC);
    msg_lastRegister = *(u16*)(buffer->data + 0x10);

    if (msg_firstRegister > msg_lastRegister) {
        TRKSendReply(0x14);
        return 0;
    }

    reply.commandID = 0x80;
    reply.length = 0x468;

    TRKResetBuffer(buffer, 0);
    MWTRACE(4, "DoReadRegisters : Buffer length 0x%08x\n", buffer->length);
    TRKAppendBuffer_ui8(buffer, (u8*)&reply, sizeof(CommandReply));
    MWTRACE(4, "DoReadRegisters : Buffer length 0x%08x\n", buffer->length);

    error = TRKTargetAccessDefault(0, 0x24, buffer, &registerDataLength, 1);
    MWTRACE(4, "DoReadRegisters : Error reading  default regs 0x%08x\n", error);
    MWTRACE(4, "DoReadRegisters : Buffer length 0x%08x\n", buffer->length);

    if (error == 0)
        error = TRKTargetAccessFP(0, 0x21, buffer, &registerDataLength, 1);
    MWTRACE(4, "DoReadRegisters : Error FP regs 0x%08x\n", error);
    MWTRACE(4, "DoReadRegisters : Buffer length 0x%08x\n", buffer->length);

    if (error == 0)
        error = TRKTargetAccessExtended1(0, 0x60, buffer, &registerDataLength, 1);
    MWTRACE(4, "DoReadRegisters : Error extended1 regs 0x%08x\n", error);
    MWTRACE(4, "DoReadRegisters : Buffer length 0x%08x\n", buffer->length);

    if (error == 0)
        error = TRKTargetAccessExtended2(0, 0x1F, buffer, &registerDataLength, 1);
    MWTRACE(4, "DoReadRegisters : Error extended2 regs 0x%08x\n", error);
    MWTRACE(4, "DoReadRegisters : Buffer length 0x%08x\n", buffer->length);

    if (error != 0) {
        switch (error) {
        case 0x703:
            replyError = 0x12;
            break;
        case 0x701:
            replyError = 0x14;
            break;
        case 0x702:
            replyError = 0x15;
            break;
        case 0x704:
            replyError = 0x21;
            break;
        case 0x705:
            replyError = 0x22;
            break;
        case 0x706:
            replyError = 0x20;
            break;
        default:
            replyError = 3;
            break;
        }

        TRKSendReply(replyError);
        return 0;
    }

    return TRKSendACK(buffer);
}

/**
 * Handles the write-registers command (0x13): the option byte selects the group (0 default, 1 floating point,
 * 2 extended 1, 3 extended 2) and the values after the header are stored into the saved context.
 */
DSError TRKDoWriteRegisters(TRKBuffer* buffer) {
    DSError error;
    u8 replyError;
    u32 registerDataLength;
    u8 msg_options;
    u16 msg_firstRegister;
    u16 msg_lastRegister;
    CommandReply reply;

    msg_options = buffer->data[8];
    msg_firstRegister = *(u16*)(buffer->data + 0xC);
    msg_lastRegister = *(u16*)(buffer->data + 0x10);

    TRKSetBufferPosition(buffer, 0);

    if (msg_firstRegister > msg_lastRegister) {
        TRKSendReply(0x14);
        return 0;
    }

    TRKSetBufferPosition(buffer, sizeof(CommandReply));

    switch (msg_options) {
    case 0:
        error = TRKTargetAccessDefault(msg_firstRegister, msg_lastRegister, buffer, &registerDataLength, 0);
        break;
    case 1:
        error = TRKTargetAccessFP(msg_firstRegister, msg_lastRegister, buffer, &registerDataLength, 0);
        break;
    case 2:
        error = TRKTargetAccessExtended1(msg_firstRegister, msg_lastRegister, buffer, &registerDataLength, 0);
        break;
    case 3:
        error = TRKTargetAccessExtended2(msg_firstRegister, msg_lastRegister, buffer, &registerDataLength, 0);
        break;
    default:
        error = 0x703;
        break;
    }

    TRKResetBuffer(buffer, 0);

    if (error == 0) {
        memset(&reply, 0, sizeof(CommandReply));
        reply.length = sizeof(CommandReply);
        reply.commandID = 0x80;
        reply.replyError = error;
        error = TRKAppendBuffer(buffer, &reply, sizeof(CommandReply));
    }

    if (error != 0) {
        switch (error) {
        case 0x703:
            replyError = 0x12;
            break;
        case 0x701:
            replyError = 0x14;
            break;
        case 0x302:
            replyError = 0x2;
            break;
        case 0x702:
            replyError = 0x15;
            break;
        case 0x704:
            replyError = 0x21;
            break;
        case 0x705:
            replyError = 0x22;
            break;
        case 0x706:
            replyError = 0x20;
            break;
        default:
            replyError = 3;
            break;
        }

        TRKSendReply(replyError);
        return 0;
    }

    return TRKSendACK(buffer);
}

/**
 * Handler for a flush-cache command; unimplemented here (prints a message and replies with error 0x12).
 * It is not in the dispatcher's table.
 */
DSError TRKDoFlushCache(TRKBuffer* buffer) {
    MWTRACE(8, "DoFlushCache unimplemented!!!\n");
    TRKSendReply(0x12);
    return 0;
}

/**
 * Handles the continue command (0x18): if the game is stopped, replies OK and resumes it;
 * otherwise replies error 0x16.
 */
DSError TRKDoContinue(TRKBuffer* buffer) {
    MWTRACE(1, "DoContinue\n");

    if (!TRKTargetStopped()) {
        TRKSendReply(0x16);
        return 0;
    }

    TRKSendReply(0);
    return TRKTargetContinue();
}

/**
 * Handles the step command (0x19): option 0/0x10 steps a count of instructions,
 * 1/0x11 steps until the PC leaves a range (0x10/0x11 mean step over, which the target rejects).
 * Replies OK then starts the step; errors if the game is not stopped.
 */
DSError TRKDoStep(TRKBuffer* buffer) {
    DSError error;
    u8 options;
    u8 count;
    u32 rangeStart;
    u32 rangeEnd;
    u32 pc;

    TRKSetBufferPosition(buffer, 0);

    options = buffer->data[8];
    rangeStart = *(u32*)(buffer->data + 0x10);
    rangeEnd = *(u32*)(buffer->data + 0x14);

    switch (options) {
    case 0:
    case 0x10:
        count = buffer->data[0xC];
        if (count >= 1)
            break;
        TRKSendReply(0x11);
        return 0;
    case 1:
    case 0x11:
        pc = TRKTargetGetPC();
        if (pc >= rangeStart && pc <= rangeEnd)
            break;
        TRKSendReply(0x11);
        return 0;
    default:
        TRKSendReply(0x12);
        return 0;
    }

    if (!TRKTargetStopped()) {
        TRKSendReply(0x16);
        return 0;
    }

    TRKSendReply(0);

    error = 0;

    switch (options) {
    case 0:
    case 0x10:
        error = TRKTargetSingleStep(count, options == 0x10);
        break;
    case 1:
    case 0x11:
        error = TRKTargetStepOutOfRange(rangeStart, rangeEnd, options == 0x11);
        break;
    }

    return error;
}

/** Handles the stop command (0x1A): marks the game stopped and replies OK (or a mapped error). */
DSError TRKDoStop(TRKBuffer* buffer) {
    u8 replyError;

    switch (TRKTargetStop()) {
    case 0:
        replyError = 0;
        break;
    case 0x704:
        replyError = 0x21;
        break;
    case 0x705:
        replyError = 0x22;
        break;
    case 0x706:
        replyError = 0x20;
        break;
    default:
        replyError = 1;
        break;
    }

    TRKSendReply(replyError);
    return 0;
}

/**
 * Handles the set-option command (0x17): option 1 turns console I/O over the host link on or off (prints which),
 * then replies OK.
 */
DSError TRKDoSetOption(TRKBuffer* buffer) {
    u8 spID = buffer->data[8];
    u8 mask = buffer->data[0xC];

    if (spID == 1) {
        usr_puts_serial("\nMetroTRK Option : SerialIO - ");
        if (mask)
            usr_puts_serial("Enable\n");
        else
            usr_puts_serial("Disable\n");
        SetUseSerialIO(mask);
    }

    TRKSendReply(0);
    return 0;
}
