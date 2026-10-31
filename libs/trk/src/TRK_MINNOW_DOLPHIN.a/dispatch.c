typedef int DSError;

typedef struct TRKBuffer {
    unsigned int mutex;
    int fInUse;
    unsigned int length;
    unsigned int position;
    unsigned char data[0x880];
} TRKBuffer;

void MWTRACE(unsigned char level, char* fmt, ...);
DSError TRKSetBufferPosition(TRKBuffer* msg, unsigned int pos);
DSError TRKDoConnect(TRKBuffer* b);
DSError TRKDoDisconnect(TRKBuffer* b);
DSError TRKDoReset(TRKBuffer* b);
DSError TRKDoOverride(TRKBuffer* b);
DSError TRKDoVersions(TRKBuffer* b);
DSError TRKDoSupportMask(TRKBuffer* b);
DSError TRKDoReadMemory(TRKBuffer* b);
DSError TRKDoWriteMemory(TRKBuffer* b);
DSError TRKDoReadRegisters(TRKBuffer* b);
DSError TRKDoWriteRegisters(TRKBuffer* b);
DSError TRKDoContinue(TRKBuffer* b);
DSError TRKDoStep(TRKBuffer* b);
DSError TRKDoStop(TRKBuffer* b);
DSError TRKDoSetOption(TRKBuffer* b);

/** Dispatcher start-up hook; there is no state to set up, so it returns 0. */
DSError TRKInitializeDispatcher(void) {
    return 0;
}

/**
 * Rewinds the message buffer, reads the command byte (data[4]) and calls the matching handler:
 * 0x01 connect, 0x02 disconnect, 0x03 reset, 0x04 versions, 0x05 support mask, 0x07 override,
 * 0x10/0x11 read/write memory, 0x12/0x13 read/write registers, 0x17 set option, 0x18 continue, 0x19 step,
 * 0x1A stop. An unknown command returns 0x500.
 */
DSError TRKDispatchMessage(TRKBuffer* buffer) {
    DSError error = 0x500;

    TRKSetBufferPosition(buffer, 0);
    MWTRACE(1, "Dispatch command 0x%08x\n", buffer->data[4]);

    switch (buffer->data[4]) {
    case 0x01:
        error = TRKDoConnect(buffer);
        break;
    case 0x02:
        error = TRKDoDisconnect(buffer);
        break;
    case 0x03:
        error = TRKDoReset(buffer);
        break;
    case 0x07:
        error = TRKDoOverride(buffer);
        break;
    case 0x04:
        error = TRKDoVersions(buffer);
        break;
    case 0x05:
        error = TRKDoSupportMask(buffer);
        break;
    case 0x10:
        error = TRKDoReadMemory(buffer);
        break;
    case 0x11:
        error = TRKDoWriteMemory(buffer);
        break;
    case 0x12:
        error = TRKDoReadRegisters(buffer);
        break;
    case 0x13:
        error = TRKDoWriteRegisters(buffer);
        break;
    case 0x18:
        error = TRKDoContinue(buffer);
        break;
    case 0x19:
        error = TRKDoStep(buffer);
        break;
    case 0x1A:
        error = TRKDoStop(buffer);
        break;
    case 0x17:
        error = TRKDoSetOption(buffer);
        break;
    }

    MWTRACE(1, "Dispatch complete err = %ld\n", error);
    return error;
}
