#include <dolphin.h>
#include <dolphin/os.h>

/**
 * Initializes a message queue over a caller-provided array of msgCount message slots,
 * with empty send and receive thread queues.
 */
void OSInitMessageQueue(OSMessageQueue* mq, void* msgArray, s32 msgCount) {
    OSInitThreadQueue(&mq->queueSend);
    OSInitThreadQueue(&mq->queueReceive);
    mq->msgArray = msgArray;
    mq->msgCount = msgCount;
    mq->firstIndex = 0;
    mq->usedCount = 0;
}

/**
 * Appends a message to the back of the queue and wakes a waiting receiver.
 * If the queue is full it sleeps until there is room when flags has bit 0 set (blocking), otherwise returns 0;
 * returns 1 on success.
 */
int OSSendMessage(OSMessageQueue* mq, void* msg, s32 flags) {
    BOOL enabled;
    s32 lastIndex;

    enabled = OSDisableInterrupts();
    while(mq->msgCount <= mq->usedCount) {
        if (!(flags & 1)) {
            OSRestoreInterrupts(enabled);
            return 0;
        }
        OSSleepThread(&mq->queueSend);
    }
    lastIndex = (mq->firstIndex + mq->usedCount) % mq->msgCount;
    ((u32*)mq->msgArray)[lastIndex] = (u32)msg;
    mq->usedCount++;
    OSWakeupThread(&mq->queueReceive);
    OSRestoreInterrupts(enabled);
    return 1;
}

/**
 * Takes the oldest message from the queue, storing it in *msg, and wakes a waiting sender.
 * If the queue is empty it sleeps until a message arrives when flags has bit 0 set, otherwise returns 0;
 * returns 1 on success.
 */
int OSReceiveMessage(OSMessageQueue* mq, void* msg, s32 flags) {
    BOOL enabled = OSDisableInterrupts();

    while(mq->usedCount == 0) {
        if (!(flags & 1)) {
            OSRestoreInterrupts(enabled);
            return 0;
        }
        OSSleepThread(&mq->queueReceive);
    }
    if(msg != NULL) {
       *(u32*)msg = ((u32*)mq->msgArray)[mq->firstIndex];
    }
    
    mq->firstIndex = (mq->firstIndex + 1) % mq->msgCount;
    mq->usedCount--;
    OSWakeupThread(&mq->queueSend);
    OSRestoreInterrupts(enabled);
    return 1;
}

/** Like OSSendMessage but puts the message at the front of the queue so it is received next. */
int OSJamMessage(OSMessageQueue* mq, void* msg, s32 flags) {
    BOOL enabled = OSDisableInterrupts();

    while(mq->msgCount <= mq->usedCount) {
        if(!(flags & 1)) {
            OSRestoreInterrupts(enabled);
            return 0;
        }
        OSSleepThread(&mq->queueSend);
    }
    mq->firstIndex = (mq->firstIndex + mq->msgCount - 1) % mq->msgCount;
    ((u32*)mq->msgArray)[mq->firstIndex] = (u32)msg;
    mq->usedCount++;
    OSWakeupThread(&mq->queueReceive);
    OSRestoreInterrupts(enabled);
    return 1;
}
