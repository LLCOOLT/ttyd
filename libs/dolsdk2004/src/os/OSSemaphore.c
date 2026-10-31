#include <dolphin.h>
#include <dolphin/os.h>

/** Initialises a counting semaphore with the given starting count and an empty wait queue. */
void OSInitSemaphore(OSSemaphore* sem, s32 count) {
    BOOL enabled = OSDisableInterrupts();

    OSInitThreadQueue(&sem->queue);
    sem->count = count;
    OSRestoreInterrupts(enabled);
}

/**
 * Decrements the semaphore, putting the calling thread to sleep while the count is zero.
 * Returns the count before the decrement.
 */
s32 OSWaitSemaphore(OSSemaphore* sem) {
    BOOL enabled;
    s32 count;

    enabled = OSDisableInterrupts();

    while((sem->count = (count = sem->count)) <= 0) {
        OSSleepThread(&sem->queue);
    }

    sem->count--;
    OSRestoreInterrupts(enabled);
    return count;
}

/**
 * Non-blocking version of OSWaitSemaphore: decrements and returns the old count if positive,
 * otherwise returns the zero count without waiting.
 */
s32 OSTryWaitSemaphore(OSSemaphore* sem) {
    BOOL enabled;
    s32 count;

    enabled = OSDisableInterrupts();
    count = sem->count;
    if (sem->count > 0) {
        sem->count = sem->count - 1;
    }

    OSRestoreInterrupts(enabled);
    return count;
}

/** Increments the semaphore and wakes one waiting thread. Returns the count before the increment. */
s32 OSSignalSemaphore(OSSemaphore* sem) {
    BOOL enabled;
    s32 count;

    enabled = OSDisableInterrupts();
    count = sem->count;
    sem->count++;

    OSWakeupThread(&sem->queue);
    OSRestoreInterrupts(enabled);
    return count;
}

/** Returns the semaphore's current count. */
s32 OSGetSemaphoreCount(OSSemaphore* sem) {
    return sem->count;
}
