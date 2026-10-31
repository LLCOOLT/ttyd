typedef int DSError;
typedef struct TRKBuffer TRKBuffer;

DSError TRKGetFreeBuffer(int* bufIdx, TRKBuffer** buf);
void TRKReleaseBuffer(int idx);
DSError TRKRequestSend(TRKBuffer* msg, int* bufIdx, unsigned int p1, unsigned int p2, int p3);
DSError TRKTargetAddStopInfo(TRKBuffer* msg);
void TRKTargetAddExceptionInfo(TRKBuffer* msg);

/**
 * Tells the host the game has stopped: fills a free buffer with the stop report (command 0x90)
 * or the exception report (any other value), sends it as a request and waits for the host's reply.
 * Returns the error, 0 on success.
 */
DSError TRKDoNotifyStopped(int cmd) {
    DSError err;
    int reqIdx;
    int bufIdx;
    TRKBuffer* msg;

    err = TRKGetFreeBuffer(&bufIdx, &msg);

    if (err == 0) {
        if (err == 0) {
            if (cmd == 0x90)
                TRKTargetAddStopInfo(msg);
            else
                TRKTargetAddExceptionInfo(msg);
        }

        err = TRKRequestSend(msg, &reqIdx, 2, 3, 1);

        if (err == 0)
            TRKReleaseBuffer(reqIdx);

        TRKReleaseBuffer(bufIdx);
    }

    return err;
}
