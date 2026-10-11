typedef int BOOL;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct CircleBuffer {
    u8* read_ptr;
    u8* write_ptr;
    u8* start_ptr;
    u32 size;
    u32 mBytesToRead;
    u32 mBytesToWrite;
    unsigned int mCriticalSection;
} CircleBuffer;

void MWTRACE(u8 level, char* fmt, ...);
u32 CBGetBytesAvailableForRead(CircleBuffer* cb);
void CircleBufferInitialize(CircleBuffer* cb, u8* buf, u32 size);
int CircleBufferWriteBytes(CircleBuffer* cb, u8* buf, u32 size);
int CircleBufferReadBytes(CircleBuffer* cb, u8* buf, u32 size);
void DBInitComm(void* inputPendingPtrRef, void* monitorCallback);
void DBInitInterrupts(void);
u32 DBQueryData(void);
int DBRead(void* data, u32 size);
int DBWrite(const void* data, u32 size);
void DBOpen(void);
void DBClose(void);

#define GDEV_BUF_SIZE 0x500

static CircleBuffer gRecvCB;
static u8 gRecvBuf[GDEV_BUF_SIZE];
static BOOL gIsInitialized;

int gdev_cc_initialize(void* inputPendingPtrRef, void* monitorCallback) {
    MWTRACE(1, "CALLING EXI2_Init\n");
    DBInitComm(inputPendingPtrRef, monitorCallback);
    MWTRACE(1, "DONE CALLING EXI2_Init\n");
    CircleBufferInitialize(&gRecvCB, gRecvBuf, GDEV_BUF_SIZE);
    return 0;
}

int gdev_cc_shutdown(void) {
    return 0;
}

int gdev_cc_open(void) {
    if (gIsInitialized)
        return -10005;

    gIsInitialized = 1;
    return 0;
}

int gdev_cc_close(void) {
    return 0;
}

int gdev_cc_read(u8* dest, int size) {
    u8 buff[GDEV_BUF_SIZE];
    u32 p1;
    int r3;
    int p2;
    int poll;

    p1 = 0;

    if (!gIsInitialized)
        return -10001;

    r3 = size;
    MWTRACE(1, "Expected packet size : 0x%08x (%ld)\n", size, size);

    p2 = size;

    while (CBGetBytesAvailableForRead(&gRecvCB) < p2) {
        p1 = 0;
        poll = DBQueryData();
        if (poll != 0) {
            p1 = DBRead(buff, p2);
            if (p1 == 0)
                CircleBufferWriteBytes(&gRecvCB, buff, poll);
        }
    }

    if (p1 == 0)
        CircleBufferReadBytes(&gRecvCB, dest, r3);
    else
        MWTRACE(8, "cc_read : error reading bytes from EXI2 %ld\n", p1);

    return p1;
}

int gdev_cc_write(const u8* bytes, int length) {
    int exi2Len;
    int n_copy;
    u32 hexCopy;

    hexCopy = (u32)bytes;
    n_copy = length;

    if (gIsInitialized == 0) {
        MWTRACE(8, "cc not initialized\n");
        return -10001;
    }

    MWTRACE(8, "cc_write : Output data 0x%08x %ld bytes\n", bytes, length);

    while (n_copy > 0) {
        MWTRACE(1, "cc_write sending %ld bytes\n", n_copy);
        exi2Len = DBWrite((const void*)hexCopy, n_copy);

        if (exi2Len == 0)
            break;

        hexCopy += exi2Len;
        n_copy -= exi2Len;
    }

    return 0;
}

int gdev_cc_pre_continue(void) {
    DBClose();
    return 0;
}

int gdev_cc_post_stop(void) {
    DBOpen();
    return 0;
}

int gdev_cc_peek(void) {
    int poll;
    u8 buff[GDEV_BUF_SIZE];

    poll = DBQueryData();

    if (poll <= 0)
        return 0;

    if (DBRead(buff, poll) == 0)
        CircleBufferWriteBytes(&gRecvCB, buff, poll);
    else
        return -10009;

    return poll;
}

int gdev_cc_initinterrupts(void) {
    DBInitInterrupts();
    return 0;
}
