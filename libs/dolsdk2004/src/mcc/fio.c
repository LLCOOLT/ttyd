#include <dolphin.h>
#include <dolphin/mcc.h>

#ifdef DEBUG
const char* __FIOVersion = "<< Dolphin SDK - FIO\tdebug build: Apr  5 2004 03:57:07 (0x2301) >>";
#else
const char* __FIOVersion = "<< Dolphin SDK - FIO\trelease build: Apr  5 2004 04:15:50 (0x2301) >>";
#endif

static u8 gBuf[0x2000];
static u8 gPrintBuf[0x400];

static u8 gmSizeOfBlocks = 1;
static u8 gSizeOfBlocks = 1;
volatile static BOOL gProcDone = TRUE;

static MCC_CHANNEL gmChID;
static MCC_CHANNEL gChID;
static int gQuery;
volatile static int gProcBusy;
volatile static u32 gStreamReady;
static u8 gLastErr;
static BOOL bAsyncIsRead;
static FIO_ASYNC_STATE bAsyncBusy;
static void* bAsyncBuffer;
static u32 gAsyncDataSize;
static u32 gRequestSequenceNumber;

// prototypes
static BOOL fioIsInitialized(void);
static u16 EndianConvert16(u16 n);
static u32 EndianConvert32(u32 n);
static int MPDWaiting(int timeout, volatile int* flag, int value);
static void ShowChannelInfo(MCC_CHANNEL chID);
static void fioErrorReport(char* msg);
static void fioMccChannelEvent(MCC_CHANNEL chID, u32 event, u32 value);
static void* fioPacketMakeHeader(u32 fioCode, u32 dataSize, BOOL bEndianConvert);
static int fioPacketSendPacket(u8 sizeOfBlocks, void* pTopOfSecondBlockData);
static void* fioPacketReceiveResult(u32 fioCode, BOOL bDone);
static void fioPacketReceiveDone(void);
static int fioPacketRead(int fd, void* buffer, int size, int async);
static int fioPacketWrite(int fd, void* buffer, int size, int async);
static int fioPacketResultRead(void* buffer, u32 dataSize);
static int fioPacketResultWrite(void* buffer, u32 dataSize);

/** Returns whether the FIO channel is open (gChID is non-zero). */
static BOOL fioIsInitialized(void) {
    return !!gChID;
}

/** Byte-swaps a 16-bit value (the host PC is little-endian). */
static u16 EndianConvert16(u16 n) {
    return ((n & 0x00FF) << 8) | ((n & 0xFF00) >> 8);
}

/** Byte-swaps a 32-bit value (the host PC is little-endian). */
static u32 EndianConvert32(u32 n) {
    return EndianConvert16((n >> 16) & 0xFFFF) | (EndianConvert16(n & 0xFFFF) << 0x10);
}

/**
 * Spins until *flag equals value, giving up after timeout seconds;
 * prints an error and returns 0 on timeout, 1 otherwise.
 */
static int MPDWaiting(int timeout, volatile int* flag, int value) {
    OSTick tickStart;
    OSTick tickDist;

    tickStart = OSGetTick();
    while(*flag != value) {
        tickDist = OSGetTick() - tickStart;
        tickDist = (tickDist & 0x80000000) ? (0x80000000 - tickStart) + OSGetTick() : tickDist;
        if (OSTicksToSeconds(tickDist) >= timeout) {
            OSReport("Error:Time is over.\n");
            return 0;
        }
    }

    return 1;
}

/** Prints an MCC channel's first block, block count, connection state and lock state with OSReport. */
static void ShowChannelInfo(MCC_CHANNEL chID) {
    MCC_Info info;

    MCCGetChannelInfo(chID, &info);
    OSReport("%2d: FirstBlock:%02d,BlockLength:%02d,Connect:%s,Lock:%s.\n",
             chID, info.firstBlock, info.blockLength,
             (info.connect == MCC_CONNECT_DISCONNECT)   ? "DISCONNECT" : 
             (info.connect == MCC_CONNECT_HOST_OPEN)    ? "HOST_OPEN" : 
             (info.connect == MCC_CONNECT_TARGET_OPEN)  ? "TARGET_OPEN" : 
             (info.connect == MCC_CONNECT_CONNECTED)    ? "CONNECTED" : "UNKNOWN",
             (info.isLocked == FALSE)                   ? "UNLOCKED" : 
             (info.isLocked == TRUE)                    ? "LOCKED" : "UNKNOWN");
}

/** Prints "[fio] Error: <msg>" with OSReport. */
static void fioErrorReport(char* msg) {
    OSReport("[fio] Error: %s\n", msg);
}

/**
 * MCC event callback for the FIO channel: records the channel on connect and clears it on disconnect,
 * sets gQuery when the host answers a query (protocol 0x120),
 * and marks the packet exchange (and a pending async transfer) done when the host sends the 0xF00000 notify;
 * read and write events set gStreamReady to 0x10 and 0x20.
 */
static void fioMccChannelEvent(MCC_CHANNEL chID, u32 event, u32 value) {
    u32 notify;

    switch(event) {
    case MCC_EVENT_CONNECT:
        gChID = chID;
        return;
    case MCC_EVENT_DISCONNECT:
        gChID = 0;
        return;
    case MCC_EVENT_UNK_0x100:
        notify = value & 0xF00000;
        switch (notify) {                         
        case 0x200000:                              
            if ((u16)value == 0x120) {
                gQuery = 1;
            }
            return;
        case 0xF00000:                              
            gProcDone = TRUE;
            if (bAsyncBusy != 0) {
                bAsyncBusy = FIO_ASYNC_STATE_DONE;
                return;
            }
            break;
        }
        break;
    case MCC_EVENT_READ:
        gStreamReady = 0x10;
        return;
    case MCC_EVENT_WRITE:
        gStreamReady = 0x20;
        break;
    }
}

/**
 * Starts file I/O over the PC link: MCCInit with a 10 second timeout,
 * then MCCOpen of the given channel with blockSize 8 KB blocks, and resets the packet and async state.
 * Returns 1 when ready; the error is in FIOGetLastError.
 */
int FIOInit(MCC_EXI exiChannel, MCC_CHANNEL chID, u8 blockSize) {
    OSRegisterVersion(__FIOVersion);

    if (MCCInit(exiChannel, 10, NULL) == 0) {
        gLastErr = FIO_ERROR_MCC;
        goto exit;
    }
    if (MCCOpen(chID, blockSize, fioMccChannelEvent) == 0) {
        gLastErr = FIO_ERROR_MCC;
        goto exit;
    }

    gChID = chID;
    gmChID = chID;
    gSizeOfBlocks = blockSize;
    gmSizeOfBlocks = blockSize;
    gQuery = 0;
    gProcDone = TRUE;
    gProcBusy = FALSE;
    gLastErr = FIO_ERROR_NONE;
    bAsyncBusy = FIO_ASYNC_STATE_IDOL;
    bAsyncBuffer = NULL;
    bAsyncIsRead = FALSE;
    return 1;

exit:;
    return 0;
}

/** Closes the FIO channel and resets the packet and async state (does nothing further if MCCClose fails). */
void FIOExit(void) {
    if (MCCClose(gChID) == 0) {
        gLastErr = FIO_ERROR_MCC;
        return;
    }

    gmChID = gChID = 0;
    gmSizeOfBlocks = gSizeOfBlocks = 1;
    gQuery = 0;
    gProcDone = TRUE;
    gProcBusy = FALSE;
    gLastErr = FIO_ERROR_NONE;
    bAsyncBusy = FIO_ASYNC_STATE_IDOL;
    bAsyncBuffer = NULL;
    bAsyncIsRead = FALSE;
}

/**
 * Asks the host whether its file server is present:
 * sends notify 0x100120 and waits up to 10 seconds for the reply.
 * On failure it also stalls for 5 seconds before returning 0.
 */
int FIOQuery(void) {
    OSTick tick;

    if (fioIsInitialized()) {
        gQuery = 0;
        if (MCCNotify(gChID, 0x100120) == 0) {
            gLastErr = FIO_ERROR_MCC;
            goto exit;
        }
        if (MPDWaiting(10, &gQuery, 1) == 0) {
            gLastErr = FIO_ERROR_TIMEOUT;
            goto exit;
        }
        gLastErr = FIO_ERROR_NONE;
        return 1;
    }

exit:;
    tick = OSGetTick();
    do {} while(OSTicksToSeconds(OSGetTick() - tick) < 5);
    return 0;
}

/** Returns the error code of the last FIO call (FIO_ERROR_*; 0 means no error). */
u8 FIOGetLastError(void) {
    return gLastErr;
}

/**
 * Opens filename on the host PC with the mode flags (only bits 0xE03 are valid):
 * sends request 0 and returns the host's file descriptor, or -1 on error.
 */
int FIOFopen(const char* filename, u32 mode) {
    struct FIO_Code {
        /* 0x00 */ u32 flag;
        /* 0x04 */ s8 filename; // dynamic length
    } *code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
        /* 0x04 */ u32 descriptor;
    } *coder;

    if (filename == NULL) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (mode & ~0xE03) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (bAsyncBusy) {
        gLastErr = FIO_ERROR_ASYNC_BUSY;
        goto exit;
    }

    code = fioPacketMakeHeader(0, strlen(filename) + sizeof(u32) + sizeof(s8), FALSE);
    code->flag = mode;
    memcpy(&code->filename, filename, strlen(filename) + 1);

    if (fioPacketSendPacket(1, NULL)) {
        coder = fioPacketReceiveResult(1, TRUE);
        if (coder != NULL) {
            if (coder->result != 0) {
                gLastErr = coder->result;
                goto exit;
            }
            gLastErr = FIO_ERROR_NONE;
            return coder->descriptor;
        }
    }
exit:;
    return -1;
}

/**
 * Closes a host file descriptor (request 2); returns 1 once the host answered,
 * with the host's result in the last error.
 */
int FIOFclose(int handle) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
    } *code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
    } *coder;

    if (handle == 0) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (bAsyncBusy) {
        gLastErr = FIO_ERROR_ASYNC_BUSY;
        goto exit;
    }

    code = fioPacketMakeHeader(2, sizeof(struct FIO_Code), FALSE);
    code->descriptor = handle;

    if (fioPacketSendPacket(1, NULL)) {
        coder = fioPacketReceiveResult(3, TRUE);
        if (coder != NULL) {
            gLastErr = coder->result;
            return 1;
        }
    }

exit:;
    return 0;
}

/**
 * Reads size bytes from a host file into data (which must be 32-byte aligned) through fioPacketRead;
 * returns the byte count or -1.
 */
u32 FIOFread(int handle, void* data, u32 size) {
    char* pBuf;
    volatile int nSizeRemain;
    int nResult;
    int nReadSize;

    pBuf = data;
    nSizeRemain = size;
    nResult = -1;

    if (handle == 0) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (data == NULL || (u32)data & 0x1F) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (size == 0) {
        return 0;
    }
    if (bAsyncBusy) {
        gLastErr = FIO_ERROR_ASYNC_BUSY;
        goto exit;
    }

    nReadSize = fioPacketRead(handle, pBuf, nSizeRemain, 0);
    nSizeRemain = nSizeRemain - nReadSize;
    if (nReadSize < 0) {
        gLastErr = FIO_ERROR_PACKET_READ;
        return -1;
    }

    gLastErr = FIO_ERROR_NONE;
    return size - nSizeRemain;

exit:;
    return -1;
}

/**
 * Writes size bytes from data (32-byte aligned) to a host file through fioPacketWrite;
 * returns the byte count or -1.
 */
u32 FIOFwrite(int handle, void* data, u32 size) {
    volatile int nSizeRemain;
    int nResult;
    int nWriteSize;

    nSizeRemain = size;
    nResult = 0;

    if (handle == 0) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (data == NULL || (u32)data & 0x1F) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (size == 0) {
        return 0;
    }
    if (bAsyncBusy) {
        gLastErr = FIO_ERROR_ASYNC_BUSY;
        goto exit;
    }

    nWriteSize = fioPacketWrite(handle, data, nSizeRemain, 0);
    nSizeRemain -= nWriteSize;
    if (nWriteSize < 0) {
        gLastErr = FIO_ERROR_PACKET_WRITE;
        return -1;
    }

    gLastErr = FIO_ERROR_NONE;
    return size - nSizeRemain;

exit:;
    return -1;
}

/**
 * Seeks a host file (request 8): mode 0 from the start, 1 from the current position, 2 from the end;
 * rejects negative offsets from start and positive ones from end. Returns the new position or -1.
 */
u32 FIOFseek(int handle, s32 offset, u32 mode) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
        /* 0x04 */ u32 offset;
        /* 0x08 */ u32 base;
    } *code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
        /* 0x04 */ u32 pos;
    } *coder;

    if (handle == 0) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (!(mode == 0 || mode == 2 || mode == 1)) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (mode == 0 && offset < 0) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (mode == 2 && offset > 0) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (bAsyncBusy) {
        gLastErr = FIO_ERROR_ASYNC_BUSY;
        goto exit;
    }

    code = fioPacketMakeHeader(8, sizeof(struct FIO_Code), FALSE);
    code->descriptor = handle;
    code->offset = offset;
    code->base = mode;

    if (fioPacketSendPacket(1, NULL)) {
        coder = fioPacketReceiveResult(9, TRUE);
        if (coder != NULL && coder->result == 0) {
            gLastErr = FIO_ERROR_NONE;
            return coder->pos;
        }
    }

exit:
    return -1;
}

/**
 * printf into a host file: formats into a 256 byte buffer (truncating at 255 characters)
 * and writes the text with FIOFwrite.
 */
int FIOFprintf(int handle, const char* format, ...) {
    char* str;
    int length;
    int err;
    va_list argptr;

    if (handle == 0) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (format == NULL) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (bAsyncBusy) {
        gLastErr = FIO_ERROR_ASYNC_BUSY;
        goto exit;
    }

    str = (char*)gPrintBuf;
    va_start(argptr, format);
    err = vsprintf(str, format, argptr);
    if ((length = strlen(str)) < 0x100) {
        str[length] = 0;
    } else {
        str[0xFF] = 0;
    }

    length = strlen(str);
    if (err < 0) {
        gLastErr = FIO_ERROR_MSG_TOO_LONG;
        return -1;
    }

    gLastErr = FIO_ERROR_NONE;
    return FIOFwrite(handle, str, length + 0);

exit:;
    va_end(argptr);
    return -1;
}

/** Asks the host to flush a file to disk (request 10); returns 1 on success. */
int FIOFflush(int handle) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
    } *code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
    } *coder;

    if (handle == 0) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (bAsyncBusy) {
        gLastErr = FIO_ERROR_ASYNC_BUSY;
        goto exit;
    }

    code = fioPacketMakeHeader(10, 4, FALSE);
    code->descriptor = handle;

    if (fioPacketSendPacket(1, NULL)) {
        coder = fioPacketReceiveResult(11, TRUE);
        if (coder != NULL) {
            if (coder->result != 0) {
                gLastErr = coder->result;
                goto exit;
            }
            gLastErr = FIO_ERROR_NONE;
            return 1;
        }
    }
    
exit:
    return 0;
}

/** Fetches the host's FIO_Stat for an open file (request 12); returns 1 on success. */
int FIOFstat(int handle, FIO_Stat* stat) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
    } *code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
        /* 0x04 */ FIO_Stat stat;
    } *coder;
    
    if (handle == 0) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (stat == NULL) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (bAsyncBusy) {
        gLastErr = FIO_ERROR_ASYNC_BUSY;
        goto exit;
    }

    code = fioPacketMakeHeader(12, 4, FALSE);
    code->descriptor = handle;

    if (fioPacketSendPacket(1, NULL)) {
        coder = fioPacketReceiveResult(13, TRUE);
        if (coder != NULL) {
            if (stat) {
                memcpy(stat, &coder->stat, sizeof(FIO_Stat));
            }

            if (coder->result != 0) {
                gLastErr = coder->result;
                goto exit;
            }

            gLastErr = FIO_ERROR_NONE;
            return 1;
        }
    }

exit:;
    return 0;
}

/**
 * Asks the host for the error state of a file descriptor (request 14);
 * returns the error code, which is also stored as the last error.
 */
int FIOFerror(int handle) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
    } *code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
    } *coder;

    if (handle == 0) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (bAsyncBusy) {
        gLastErr = FIO_ERROR_ASYNC_BUSY;
        goto exit;
    }

    code = fioPacketMakeHeader(14, 4, FALSE);
    code->descriptor = handle;

    if (fioPacketSendPacket(1, NULL)) {
        coder = fioPacketReceiveResult(15, TRUE);
        if (coder != NULL) {
            if (coder->result != 0) {
                gLastErr = coder->result;
                goto exit;
            }
            gLastErr = FIO_ERROR_NONE;
            return gLastErr;
        }
    }

exit:;
    return gLastErr;
}

/**
 * Starts a directory search on the host for a path pattern (request 16) and copies the first FIO_Finddata;
 * returns 1 on success.
 */
int FIOFindFirst(const char* filename, FIO_Finddata* finddata) {
    struct FIO_Code {
        /* 0x00 */ u8 filename; // dynamic length
    } *code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
        /* 0x04 */ FIO_Finddata findData;
    } *coder;

    if (filename == NULL) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (finddata == NULL) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (bAsyncBusy) {
        gLastErr = FIO_ERROR_ASYNC_BUSY;
        goto exit;
    }

    code = fioPacketMakeHeader(16, strlen(filename) + 1, FALSE);
    strcpy((void*)&code->filename, filename);

    if (fioPacketSendPacket(1, NULL)) {
        coder = fioPacketReceiveResult(17, TRUE);
        if (coder != NULL) {
            if (finddata) {
                memcpy(finddata, &coder->findData, sizeof(FIO_Finddata));
            }

            if (coder->result != 0) {
                gLastErr = coder->result;
                goto exit;
            }

            gLastErr = FIO_ERROR_NONE;
            return 1;
        }
    }

exit:;
    return 0;
}

/** Fetches the next match of the search begun by FIOFindFirst (request 18). */
int FIOFindNext(FIO_Finddata* finddata) {
    struct FIO_Code {
        /* 0x00 */ u32 reserved;
    } *code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
        /* 0x04 */ FIO_Finddata findData;
    } *coder;

    if (finddata == NULL) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (bAsyncBusy) {
        gLastErr = FIO_ERROR_ASYNC_BUSY;
        goto exit;
    }

    code = fioPacketMakeHeader(18, 4, FALSE);
    code->reserved = 0;

    if (fioPacketSendPacket(1, NULL)) {
        coder = fioPacketReceiveResult(19, TRUE);
        if (coder != NULL) {
            if (finddata) {
                memcpy(finddata, &coder->findData, sizeof(FIO_Finddata));
            }

            if (coder->result) {
                gLastErr = coder->result;
                goto exit;
            }

            gLastErr = FIO_ERROR_NONE;
            return 1;
        }
    }

exit:;
    return 0;
}

/** Opens a directory on the host (request 20) and stores its descriptor in *dir; returns 1 on success. */
int FIOOpenDir(const char* dirname, int* dir) {
    struct FIO_Code {
        /* 0x00 */ s8 filename;
    } *code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
        /* 0x04 */ u32 descriptor;
    } *coder;

    if (dirname == NULL) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        return 0;
    }
    if (dir == NULL) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        return 0;
    }
    if (bAsyncBusy) {
        gLastErr = FIO_ERROR_ASYNC_BUSY;
        return 0;
    }

    code = fioPacketMakeHeader(20, strlen(dirname) + 1, FALSE);
    memcpy(&code->filename, dirname, strlen(dirname) + 1);

    if (fioPacketSendPacket(1, NULL)) {
        coder = fioPacketReceiveResult(21, TRUE);
        if (coder != NULL) {
            if (coder->result != 0) {
                gLastErr = coder->result;
                goto exit;
            }

            gLastErr = FIO_ERROR_NONE;
            *dir = coder->descriptor;
            return 1;
        }
    }

exit:;
    return 0;
}

/** Closes a host directory descriptor (request 22). */
int FIOCloseDir(int dir) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
    } *code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
    } *coder;

    if (dir == 0 || dir == -1) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        return 0;
    }
    if (bAsyncBusy) {
        gLastErr = FIO_ERROR_ASYNC_BUSY;
        return 0;
    }

    code = fioPacketMakeHeader(22, 4, FALSE);
    code->descriptor = dir;

    if (fioPacketSendPacket(1, NULL)) {
        coder = fioPacketReceiveResult(23, TRUE);
        if (coder != NULL) {
            gLastErr = coder->result;
            return 1;
        }
    }

    return 0;
}

/** Returns the number of entries in an open host directory (request 24), or -1. */
s32 FIOGetDirSize(int dir) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
    } *code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
        /* 0x04 */ u32 size;
    } *coder;

    if (dir == 0 || dir == -1) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        return -1;
    }
    if (bAsyncBusy) {
        gLastErr = FIO_ERROR_ASYNC_BUSY;
        return -1;
    }

    code = fioPacketMakeHeader(24, 4, FALSE);
    code->descriptor = dir;

    if (fioPacketSendPacket(1, NULL)) {
        coder = fioPacketReceiveResult(25, TRUE);
        if (coder != NULL) {
            gLastErr = coder->result;
            return coder->size;
        }
    }

    return -1;
}

/**
 * Reads up to numOfData directory entries (request 26):
 * the host returns the count and the FIO_Finddata records are
 * then read through FIOFread on the directory descriptor. Returns the count or -1.
 */
s32 FIOReadDir(int dir, FIO_Finddata* data, s32 numOfData) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
        /* 0x04 */ u32 size;
    } *code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
        /* 0x04 */ u32 readsize;
    } *coder;
    s32 readSize;
    u32 fReadSize;

    if (dir == 0 || dir == -1 || data == NULL || numOfData < 1) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        return -1;
    }

    if (bAsyncBusy) {
        gLastErr = FIO_ERROR_ASYNC_BUSY;
        return -1;
    }

    code = fioPacketMakeHeader(26, 8, FALSE);
    code->descriptor = dir;
    code->size = numOfData;

    if (fioPacketSendPacket(1, NULL)) {
        coder = fioPacketReceiveResult(27, TRUE);
        if (coder != NULL) {
            readSize = coder->readsize;
            fReadSize = readSize * sizeof(FIO_Finddata);
            gLastErr = coder->result;
    
            if (gLastErr == FIO_ERROR_NONE || gLastErr == FIO_ERROR_UNK_0x91) {
                if (FIOFread(dir, data, fReadSize) == 0) {
                    return -1;
                }
            } else {
                return -1;
            }

            return readSize;
        }        
    }

    return -1;
}

/**
 * Returns the largest transfer the async calls accept:
 * the channel's block size times 8 KB minus a 0x18 byte header,
 * rounded down to 32 bytes (0 if no channel is open).
 */
u32 FIOGetAsyncBufferSize(void) {
    int nPacketSize;
    int nHeaderSize;
    u32 nResult;

    if (gChID == 0) {
        return 0;
    }

    nPacketSize = gSizeOfBlocks << 0xD;
    nHeaderSize = 0x18;

    nResult = nPacketSize - nHeaderSize;
    return !(nResult & 0x1F) ? nResult : nResult & ~0x1F;
}

/**
 * Starts a non-blocking host file read (buffer 32-byte aligned, at most FIOGetAsyncBufferSize bytes);
 * poll FIOCheckAsyncDone for completion. Returns 1 if the request was sent.
 */
int FIOFreadAsync(int handle, void* data, u32 size) {
    if (handle == 0) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (data == NULL || (u32)data & 0x1F) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }

    if (size != 0) {
        if (size > FIOGetAsyncBufferSize()) {
            gLastErr = FIO_ERROR_ASYNC_SIZE_TOO_BIG;
            goto exit;
        }
        if (bAsyncBusy) {
            gLastErr = FIO_ERROR_ASYNC_BUSY;
            goto exit;
        }

        bAsyncBusy = TRUE;
        bAsyncBuffer = data;
        bAsyncIsRead = TRUE;
        if (fioPacketRead(handle, data, size, 1) >= 0) {
            return 1;
        }
    }

exit:;
    return 0;
}

/**
 * Starts a non-blocking host file write (buffer 32-byte aligned, at most FIOGetAsyncBufferSize bytes);
 * poll FIOCheckAsyncDone for completion. Returns 1 if the request was sent.
 */
int FIOFwriteAsync(int handle, void* data, u32 size) {
    if (handle == 0) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }
    if (data == NULL || (u32)data & 0x1F) {
        gLastErr = FIO_ERROR_INVALID_PARAMETERS;
        goto exit;
    }

    if (size != 0) {
        if (size > FIOGetAsyncBufferSize()) {
            gLastErr = FIO_ERROR_ASYNC_SIZE_TOO_BIG;
            goto exit;
        }
        if (bAsyncBusy) {
            gLastErr = FIO_ERROR_ASYNC_BUSY;
            goto exit;
        }
    
        bAsyncBusy = TRUE;
        bAsyncBuffer = data;
        bAsyncIsRead = FALSE;
        if (fioPacketWrite(handle, data, size, 1) >= 0) {
            return 1;
        }
    }

exit:
    return 0;
}

/**
 * Returns 1 and the byte count in *result once the pending async read
 * or write has finished (the host's 0xF00000 notify arrived); 0 while it is still running.
 */
int FIOCheckAsyncDone(u32* result) {
    if (bAsyncBusy) {
        if (bAsyncIsRead) {
            if (result) {
                *result = fioPacketResultRead(bAsyncBuffer, gAsyncDataSize);
            }
        } else if (result) {
            *result = fioPacketResultWrite(bAsyncBuffer, gAsyncDataSize);
        }

        bAsyncBusy = FALSE;
        return 1;
    }

    return 0;
}

/**
 * Fills the shared 8 KB buffer's header (protocol 0x120, length, the request code and a new sequence number)
 * and returns where the request payload goes.
 */
static void* fioPacketMakeHeader(u32 fioCode, u32 dataSize, BOOL bEndianConvert) {
    MCC_Hdr* hdrDpci;
    MCC_HdrFio* hdrFio;
    char* data;

    hdrDpci = (void*)&gBuf[0];
    hdrFio = (void*)((char*)hdrDpci + 0x8);
    data = (void*)((char*)hdrFio + 0x8);

    gRequestSequenceNumber += 1;
    hdrFio->code = fioCode;
    hdrFio->number = gRequestSequenceNumber;
    hdrDpci->length = dataSize + 0x10;
    hdrDpci->rsvd = 0;
    hdrDpci->protocol = 0x120;

    if (bEndianConvert) {
        hdrFio->code = EndianConvert32(hdrFio->code);
        hdrFio->number = EndianConvert32(hdrFio->number);
        hdrDpci->length = EndianConvert32(hdrDpci->length);
        hdrDpci->protocol = EndianConvert16(hdrDpci->protocol);
    }
    return data;
}

/**
 * Writes the request buffer to the host with MCCWrite (one 8 KB block, or more with the data following),
 * waiting for the previous exchange to finish, then notifies the host with 0xF00000.
 */
static int fioPacketSendPacket(u8 sizeOfBlocks, void* pTopOfSecondBlockData) {
    u32 oldMaskWrite;
    u8 indexOfBlocks;

    oldMaskWrite = MCCSetChannelEventMask(gChID, 0xA0);

    do {} while (gProcBusy);
    do {} while (!gProcDone);

    gProcDone = FALSE;
    gProcBusy = TRUE;

    for (indexOfBlocks = 0; indexOfBlocks < sizeOfBlocks; indexOfBlocks++) {
        if (MCCWrite(gChID, ((u8)indexOfBlocks << 0xD), &gBuf, 0x2000, 0) == 0) {
            gLastErr = FIO_ERROR_PACKET_WRITE;
            MCCSetChannelEventMask(gChID, oldMaskWrite);
            fioErrorReport("fioPacketSendPacket.MCCWrite.NG");
            return 0;
        }

        if (sizeOfBlocks > 1) {
            memcpy(&gBuf, pTopOfSecondBlockData, 0x2000);
            ((char*)pTopOfSecondBlockData) += 0x2000;
        }
    }

    MCCSetChannelEventMask(gChID, oldMaskWrite);
    if (MCCNotify(gChID, 0xF00000) == 0) {
        gLastErr = FIO_ERROR_MCC;
        fioErrorReport("fioPacketSendPacket.MCCNotify.NG");
        return 0;
    }

    gLastErr = FIO_ERROR_NONE;
    return 1;
}

/**
 * Waits up to 10 seconds for the host's reply, reads it into the buffer and checks the reply code
 * and sequence number; returns the payload pointer or NULL (and sets the last error).
 */
static void* fioPacketReceiveResult(u32 fioCode, BOOL bDone) {
    u32 oldMaskRead;
    MCC_Hdr* hdrDpci;
    MCC_HdrFio* hdrFio;
    char* data;

    if (MPDWaiting(10, &gProcDone, 1) == 0) {
        gLastErr = FIO_ERROR_TIMEOUT;
        goto exit;
    }

    oldMaskRead = MCCSetChannelEventMask(gChID, 0x50);
    if (MCCRead(gChID, 0, &gBuf, 0x2000, 0) == 0) {
        gLastErr = FIO_ERROR_PACKET_READ;
        MCCSetChannelEventMask(gChID, oldMaskRead);
        goto exit;
    }

    hdrDpci = (void*)((char*)&gBuf[0]);
    hdrFio = (void*)((char*)hdrDpci + 0x8);
    data = (void*)((char*)hdrFio + 0x8);
    MCCSetChannelEventMask(gChID, oldMaskRead);

    if (hdrFio->code != fioCode) {
        gLastErr = FIO_ERROR_WRONG_CODE;
        goto exit;
    }
    if (hdrFio->number != gRequestSequenceNumber) {
        gLastErr = FIO_ERROR_WRONG_SEQUENCE;
        goto exit;
    }

    if (bDone) {
        fioPacketReceiveDone();
    }

    gLastErr = FIO_ERROR_NONE;
    return data;

exit:;
    fioPacketReceiveDone();
    return NULL;
}

/** Clears gProcBusy so the next request may use the shared buffer. */
static void fioPacketReceiveDone(void) {
    gProcBusy = 0;
}

/**
 * Sends a read request (code 4) for nbytes of descriptor fd;
 * synchronously it then receives the data, asynchronously it only remembers the size.
 */
static int fioPacketRead(int fd, void* buffer, int size, int async) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
        /* 0x04 */ u32 nbytes;
    } *code;

    code = fioPacketMakeHeader(4, sizeof(struct FIO_Code), FALSE);
    code->descriptor = fd;
    code->nbytes = size;
    gStreamReady = 0;

    if (fioPacketSendPacket(1, NULL)) {
        if (async == 0) {
            return fioPacketResultRead(buffer, size);
        }
        gAsyncDataSize = size;
        return 0;
    }

    return -1;
}

/**
 * Sends a write request (code 6) for nbytes of descriptor fd;
 * synchronously it then sends the data, asynchronously it only remembers the size.
 */
static int fioPacketWrite(int fd, void* buffer, int size, int async) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
        /* 0x04 */ u32 nbytes;
    } *code;

    code = fioPacketMakeHeader(6, 0xC, FALSE);
    code->descriptor = fd;
    code->nbytes = size;

    if (fioPacketSendPacket(1, NULL)) {
        gStreamReady = 0;
        if (async == 0) {
            return fioPacketResultWrite(buffer, size);
        }
        gAsyncDataSize = size;
        return 0;
    }

    return -1;
}

/**
 * Receives the data of a read request: the sub-block part comes through MCCRead,
 * whole blocks through a temporary MCC stream (the channel is closed, reopened as a stream,
 * read with MCCStreamRead and reopened normally); then reads the reply code 5 and returns the byte count or -1.
 */
static int fioPacketResultRead(void* buffer, u32 dataSize) {
    int bResult;
    MCC_CHANNEL nChID;
    u8 nChannelBlocks;
    u32 dataBlockSize;
    u32 readDataBlocks;
    u32 nPacketSize;
    u32 nDataPacketSize;
    u32 nFraction;
    MCC_CONNECT state;
    BOOL bNeedWaitDisconnect;
    u32 oldMaskWrite;
    u8 err;
    char msg[256];

    bResult = 1;
    nChID = gmChID;
    nChannelBlocks = gmSizeOfBlocks;
    dataBlockSize = (u32) (dataSize + 0x1FFF) >> 0xDU;
    nPacketSize = ((u8)nChannelBlocks << 0xD);
    nDataPacketSize = dataSize / nPacketSize;
    nFraction = dataSize - (nDataPacketSize * nPacketSize);
    nFraction = OSRoundUp32B(nFraction) & ~1;

    if (nFraction != 0) {
        do {} while ((u32) gStreamReady != 0x20);
        MCCRead(nChID, 0, buffer, nFraction, 0);
        ((char*)buffer) += nFraction;
    }

    if (nDataPacketSize != 0) {
        bNeedWaitDisconnect = FALSE;
        oldMaskWrite = MCCSetChannelEventMask(nChID, 0);
        MCCSetChannelEventMask(nChID, oldMaskWrite);

        if (MCCClose(nChID) == 0) {
            fioErrorReport("fioPacketResultRead.MCCClose.NG");
            bResult = 0;
        } else {
            do {
                MCCGetConnectionStatus(nChID, &state);
            } while (state != 0);

            if (MCCStreamOpen(nChID, nChannelBlocks) == 0) {
                fioErrorReport("fioPacketResultRead.MCCStreamOpen.NG");
                bResult = 0;
            } else {
                do {
                    MCCGetConnectionStatus(nChID, &state);
                } while (state != 3);

                if ((nDataPacketSize * nChannelBlocks) != (readDataBlocks = MCCStreamRead(nChID, buffer))) {
                    err = MCCGetLastError();
                    sprintf(msg, "fioPacketResultRead.MCCStreamRead.NG(Err:%d)", err);
                    fioErrorReport(msg);
                    bResult = 0;
                }

                if (MCCStreamClose(nChID) == 0) {
                    OSReport("MCCStream:MCCStreamClose.NG\n");
                    bResult = 0;
                } else {
                    MCC_CONNECT state;
                    do {
                        MCCGetConnectionStatus(nChID, &state);
                    } while (state != 0);

                    if (MCCOpen(nChID, nChannelBlocks, fioMccChannelEvent) == 0) {
                        OSReport("MCCStream:MCCOpen.NG\n");
                        bResult = 0;
                    } else {
                        do {
                            MCCGetConnectionStatus(nChID, &state);
                        } while (state != 3);
                    }
                }
            }
        }

        MCCSetChannelEventMask(gChID, oldMaskWrite);
    }

    // scope for variable?
    {
        struct FIO_Coder {
            /* 0x00 */ u32 result;
            /* 0x04 */ u32 nbytes;
            /* 0x08 */ char data;
        } *coder;

        coder = fioPacketReceiveResult(5, FALSE);
        if (coder == NULL) {
            bResult = 0;
        } else if (coder->result != 0) {
            gLastErr = coder->result;
            bResult = 0;
        } else {
            gLastErr = FIO_ERROR_NONE;
        }

        fioPacketReceiveDone();
        if (bResult == 1) {
            return dataSize;
        }
        goto exit;
    }

exit:;
    return -1;
}

/**
 * Sends the data of a write request through a temporary MCC stream (channel closed, reopened as a stream,
 * MCCStreamWrite, reopened normally), then receives reply code 7 and returns the host's written byte count
 * or -1.
 */
static int fioPacketResultWrite(void* buffer, u32 dataSize) {
    register int nResult = 0;
    MCC_CHANNEL nChID;
    u8 nChannelBlocks = 0;
    u32 dataBlockSize;
    MCC_CONNECT state;
    BOOL bNeedWaitDisconnect;
    u32 oldMaskWrite;

    nChID = gmChID;
    nChannelBlocks = gmSizeOfBlocks;
    dataBlockSize = (dataSize + 0x1FFF) >> 0xD;
    bNeedWaitDisconnect = FALSE;
    oldMaskWrite = MCCSetChannelEventMask(nChID, 0);

    MCCSetChannelEventMask(nChID, oldMaskWrite);
    if (MCCClose(nChID) == 0) {
        fioErrorReport("fioPacketResultWrite.MCCClose.NG");
    } else {
loop:;
        MCCGetConnectionStatus(nChID, &state);
        if (state != 0) {
            goto loop;
        }

        if (MCCStreamOpen(nChID, nChannelBlocks) == 0) {
            fioErrorReport("fioPacketResultWrite.MCCStreamOpen.NG");
            goto loop;
        }
        
        do {
            MCCGetConnectionStatus(nChID, &state);
        } while (state != 3);

        if (MCCStreamWrite(nChID, buffer, dataBlockSize) == 0) {
            fioErrorReport("fioPacketResultWrite.MCCStreamWrite.NG");
        }

        {
            MCC_CONNECT state;
            do {
                MCCGetConnectionStatus(nChID, &state);
            } while (state == 3);

            if (MCCStreamClose(nChID) == 0) {
                OSReport("MCCStream:MCCStreamClose.NG\n");
            } else {
                do {
                    MCCGetConnectionStatus(nChID, &state);
                } while (state == 0);

                if (MCCOpen(nChID, nChannelBlocks, fioMccChannelEvent) == 0) {
                    OSReport("MCCStream:MCCOpen.NG\n");
                }
            }
        }
        goto exit_loop;
    }

exit_loop:;
    {
        struct FIO_Coder {
            /* 0x00 */ u32 result;
            /* 0x04 */ u32 nbytes;
        } *coder;
    
        oldMaskWrite = MCCSetChannelEventMask(gChID, oldMaskWrite);
        coder = fioPacketReceiveResult(7, TRUE);

        if (coder == NULL) {
            (void)0;
        } else {
            if (coder->result) {
                gLastErr = coder->result;
                goto exit;
            }
            gLastErr = FIO_ERROR_NONE;
            return coder->nbytes;
        }
    }

exit:
    return -1;
}
