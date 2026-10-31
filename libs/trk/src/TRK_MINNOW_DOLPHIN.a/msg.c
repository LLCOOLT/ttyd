typedef int DSError;

typedef struct MessageBuffer {
    unsigned int mutex;
    int fInUse;
    unsigned int fLength;
    unsigned int fPosition;
    unsigned char fData[0x880];
} MessageBuffer;

int TRKWriteUARTN(const void* bytes, unsigned int length);
void MWTRACE(unsigned char level, char* fmt, ...);

/**
 * Writes a message buffer's contents (fLength bytes) to the host through TRKWriteUARTN.
 * Always returns 0; the write status is only traced.
 */
DSError TRKMessageSend(MessageBuffer* b) {
    DSError write_err = TRKWriteUARTN(b->fData, b->fLength);
    MWTRACE(1, "MessageSend : cc_write returned %ld\n", write_err);
    return 0;
}
