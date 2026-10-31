typedef int BOOL;
typedef int DSError;
typedef unsigned long size_t;
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

#define TRKMSGBUF_SIZE 0x880

typedef struct TRKBuffer {
    unsigned int mutex;
    BOOL isInUse;
    u32 length;
    u32 position;
    u8 data[TRKMSGBUF_SIZE];
} TRKBuffer;

DSError TRKInitializeMutex(void* p);
DSError TRKAcquireMutex(void* p);
DSError TRKReleaseMutex(void* p);
void* TRK_memcpy(void* dst, const void* src, unsigned int n);
void* TRK_memset(void* dst, int val, unsigned int n);
BOOL usr_puts_serial(const char* msg);

extern BOOL gTRKBigEndian;

TRKBuffer gTRKMsgBufs[3];

/** Sets or clears the in-use flag of a message buffer. */
static inline void TRKSetBufferUsed(TRKBuffer* msg, BOOL state) {
    msg->isInUse = state;
}

void TRKResetBuffer(TRKBuffer* msg, BOOL keepData);

/** Initialises the mutex of each of the three message buffers and marks them all free. Returns 0. */
DSError TRKInitializeMessageBuffers(void) {
    int i;

    for (i = 0; i < 3; i++) {
        TRKInitializeMutex(&gTRKMsgBufs[i]);
        TRKAcquireMutex(&gTRKMsgBufs[i]);
        TRKSetBufferUsed(&gTRKMsgBufs[i], 0);
        TRKReleaseMutex(&gTRKMsgBufs[i]);
    }

    return 0;
}

void* TRKGetBuffer(int idx);

/**
 * Finds the first unused of the three message buffers, empties its length and position,
 * marks it used and returns its index and pointer. Returns 0x300 (and prints a message) if all three are busy.
 */
DSError TRKGetFreeBuffer(int* msgID, TRKBuffer** outMsg) {
    TRKBuffer* buf;
    DSError error = 0x300;
    int i;

    *outMsg = 0;

    for (i = 0; i < 3; i++) {
        buf = TRKGetBuffer(i);

        TRKAcquireMutex(buf);

        if (!buf->isInUse) {
            TRKResetBuffer(buf, 1);
            TRKSetBufferUsed(buf, 1);
            error = 0;
            *outMsg = buf;
            *msgID = i;
            i = 3;
        }

        TRKReleaseMutex(buf);
    }

    if (error == 0x300)
        usr_puts_serial("ERROR : No buffer available\n");

    return error;
}

/** Returns the message buffer with the given index (0-2), or null for an index out of range. */
void* TRKGetBuffer(int idx) {
    TRKBuffer* buf = 0;

    if (idx >= 0 && idx < 3)
        buf = &gTRKMsgBufs[idx];

    return buf;
}

/** Marks the message buffer with the given index as free; indexes out of range (including -1) are ignored. */
void TRKReleaseBuffer(int idx) {
    TRKBuffer* msg;

    if (idx != -1 && idx >= 0 && idx < 3) {
        msg = &gTRKMsgBufs[idx];
        TRKAcquireMutex(msg);
        TRKSetBufferUsed(msg, 0);
        TRKReleaseMutex(msg);
    }
}

/** Sets a message buffer's length and position back to 0; zeroes its data too unless keepData is set. */
void TRKResetBuffer(TRKBuffer* msg, BOOL keepData) {
    msg->length = 0;
    msg->position = 0;

    if (!keepData)
        TRK_memset(msg->data, 0, TRKMSGBUF_SIZE);
}

/**
 * Moves the buffer's cursor to pos, growing the length if pos is past it;
 * returns 0x301 if pos is beyond the 0x880-byte capacity.
 */
DSError TRKSetBufferPosition(TRKBuffer* msg, u32 pos) {
    DSError error = 0;

    if (pos > TRKMSGBUF_SIZE) {
        error = 0x301;
    } else {
        msg->position = pos;
        if (pos > msg->length)
            msg->length = pos;
    }

    return error;
}

/**
 * Appends length bytes at the cursor (truncating to what fits and returning 0x301 on overflow)
 * and sets the length to the new cursor position.
 */
DSError TRKAppendBuffer(TRKBuffer* msg, const void* data, size_t length) {
    DSError error = 0;
    u32 bytesLeft;

    if (length == 0)
        return 0;

    bytesLeft = TRKMSGBUF_SIZE - msg->position;

    if (bytesLeft < length) {
        error = 0x301;
        length = bytesLeft;
    }

    if (length == 1)
        msg->data[msg->position] = ((u8*)data)[0];
    else
        TRK_memcpy(msg->data + msg->position, data, length);

    msg->position += length;
    msg->length = msg->position;

    return error;
}

/**
 * Copies length bytes from the cursor into the caller's memory and advances the cursor;
 * if fewer bytes remain it copies those and returns 0x302.
 */
DSError TRKReadBuffer(TRKBuffer* msg, void* data, size_t length) {
    DSError error = 0;
    unsigned int bytesLeft;

    if (length == 0)
        return 0;

    bytesLeft = msg->length - msg->position;

    if (length > bytesLeft) {
        error = 0x302;
        length = bytesLeft;
    }

    TRK_memcpy(data, msg->data + msg->position, length);
    msg->position += length;
    return error;
}

/** Appends one 32-bit value in big-endian (network) order, byte-swapping it first if the target is little-endian. */
static inline DSError TRKAppendBuffer1_ui32(TRKBuffer* buffer, const u32 data) {
    u8* bigEndianData;
    u8* byteData;
    u8 swapBuffer[sizeof(data)];

    if (gTRKBigEndian) {
        bigEndianData = (u8*)&data;
    } else {
        byteData = (u8*)&data;
        bigEndianData = swapBuffer;

        bigEndianData[0] = byteData[3];
        bigEndianData[1] = byteData[2];
        bigEndianData[2] = byteData[1];
        bigEndianData[3] = byteData[0];
    }

    return TRKAppendBuffer(buffer, (const void*)bigEndianData, sizeof(data));
}

/** Appends one 64-bit value in big-endian order, byte-swapping it first if the target is little-endian. */
DSError TRKAppendBuffer1_ui64(TRKBuffer* buffer, const u64 data) {
    u8* bigEndianData;
    u8* byteData;
    u8 swapBuffer[sizeof(data)];

    if (gTRKBigEndian) {
        bigEndianData = (u8*)&data;
    } else {
        byteData = (u8*)&data;
        bigEndianData = swapBuffer;

        bigEndianData[0] = byteData[7];
        bigEndianData[1] = byteData[6];
        bigEndianData[2] = byteData[5];
        bigEndianData[3] = byteData[4];
        bigEndianData[4] = byteData[3];
        bigEndianData[5] = byteData[2];
        bigEndianData[6] = byteData[1];
        bigEndianData[7] = byteData[0];
    }

    return TRKAppendBuffer(buffer, (const void*)bigEndianData, sizeof(data));
}

/** Appends one byte at the cursor; returns 0x301 if the buffer is full. */
static inline DSError TRKAppendBuffer1_ui8(TRKBuffer* buffer, const u8 data) {
    if (buffer->position >= TRKMSGBUF_SIZE)
        return 0x301;

    buffer->data[buffer->position++] = data;
    buffer->length++;
    return 0;
}

/** Appends count bytes one at a time, stopping at the first error. */
DSError TRKAppendBuffer_ui8(TRKBuffer* buffer, const u8* data, int count) {
    DSError err;
    int i;

    for (i = 0, err = 0; err == 0 && i < count; i++)
        err = TRKAppendBuffer1_ui8(buffer, data[i]);

    return err;
}

/** Appends count 32-bit values with the endian handling of TRKAppendBuffer1_ui32, stopping at the first error. */
DSError TRKAppendBuffer_ui32(TRKBuffer* buffer, const u32* data, int count) {
    DSError err;
    int i;

    for (i = 0, err = 0; err == 0 && i < count; i++)
        err = TRKAppendBuffer1_ui32(buffer, data[i]);

    return err;
}

/** Reads one byte from the buffer's cursor. */
static inline DSError TRKReadBuffer1_ui8(TRKBuffer* buffer, u8* data) {
    return TRKReadBuffer(buffer, (void*)data, 1);
}

/** Reads one 32-bit value from the buffer, byte-swapping it from big-endian if the target is little-endian. */
static inline DSError TRKReadBuffer1_ui32(TRKBuffer* buffer, u32* data) {
    DSError err;
    u8* bigEndianData;
    u8* byteData;
    u8 swapBuffer[sizeof(*data)];

    if (gTRKBigEndian)
        bigEndianData = (u8*)data;
    else
        bigEndianData = swapBuffer;

    err = TRKReadBuffer(buffer, (void*)bigEndianData, sizeof(*data));

    if (!gTRKBigEndian && err == 0) {
        byteData = (u8*)data;

        byteData[0] = bigEndianData[3];
        byteData[1] = bigEndianData[2];
        byteData[2] = bigEndianData[1];
        byteData[3] = bigEndianData[0];
    }

    return err;
}

/** Reads one 64-bit value from the buffer, byte-swapping it from big-endian if the target is little-endian. */
DSError TRKReadBuffer1_ui64(TRKBuffer* buffer, u64* data) {
    DSError err;
    u8* bigEndianData;
    u8* byteData;
    u8 swapBuffer[sizeof(*data)];

    if (gTRKBigEndian)
        bigEndianData = (u8*)data;
    else
        bigEndianData = swapBuffer;

    err = TRKReadBuffer(buffer, (void*)bigEndianData, sizeof(*data));

    if (!gTRKBigEndian && err == 0) {
        byteData = (u8*)data;

        byteData[0] = bigEndianData[7];
        byteData[1] = bigEndianData[6];
        byteData[2] = bigEndianData[5];
        byteData[3] = bigEndianData[4];
        byteData[4] = bigEndianData[3];
        byteData[5] = bigEndianData[2];
        byteData[6] = bigEndianData[1];
        byteData[7] = bigEndianData[0];
    }

    return err;
}

/** Reads count bytes one at a time, stopping at the first error. */
DSError TRKReadBuffer_ui8(TRKBuffer* buffer, u8* data, int count) {
    DSError err;
    int i;

    for (i = 0, err = 0; err == 0 && i < count; i++)
        err = TRKReadBuffer1_ui8(buffer, &(data[i]));

    return err;
}

/** Reads count 32-bit values with the endian handling of TRKReadBuffer1_ui32, stopping at the first error. */
DSError TRKReadBuffer_ui32(TRKBuffer* buffer, u32* data, int count) {
    DSError err;
    int i;

    for (i = 0, err = 0; err == 0 && i < count; i++)
        err = TRKReadBuffer1_ui32(buffer, &(data[i]));

    return err;
}
