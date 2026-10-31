typedef int BOOL;
typedef int DSError;

typedef struct TRKEvent {
    int eventType;
    int eventID;
    int msgBufID;
} TRKEvent;

typedef struct TRKEventQueue {
    unsigned int mutex;
    int count;
    int next;
    TRKEvent events[2];
    unsigned int eventID;
} TRKEventQueue;

DSError TRKInitializeMutex(void* p);
DSError TRKAcquireMutex(void* p);
DSError TRKReleaseMutex(void* p);
void* TRK_memcpy(void* dst, const void* src, unsigned int n);
void TRKReleaseBuffer(int idx);

TRKEventQueue gTRKEventQueue;

/** Clears the (two-slot) event queue and starts event ids at 0x100. */
DSError TRKInitializeEventQueue(void) {
    TRKInitializeMutex(&gTRKEventQueue);
    TRKAcquireMutex(&gTRKEventQueue);
    gTRKEventQueue.count = 0;
    gTRKEventQueue.next = 0;
    gTRKEventQueue.eventID = 0x100;
    TRKReleaseMutex(&gTRKEventQueue);
    return 0;
}

/** Takes the oldest event off the queue into *event; returns 1 if there was one, 0 if the queue is empty. */
BOOL TRKGetNextEvent(TRKEvent* event) {
    BOOL status = 0;

    TRKAcquireMutex(&gTRKEventQueue);

    if (0 < gTRKEventQueue.count) {
        TRK_memcpy(event, &gTRKEventQueue.events[gTRKEventQueue.next], sizeof(TRKEvent));
        gTRKEventQueue.count--;

        if (++gTRKEventQueue.next == 2)
            gTRKEventQueue.next = 0;

        status = 1;
    }

    TRKReleaseMutex(&gTRKEventQueue);
    return status;
}

/** Adds an event to the queue and gives it the next event id; returns 0x100 if both slots are taken. */
DSError TRKPostEvent(TRKEvent* event) {
    DSError ret = 0;
    int nextEventID;

    TRKAcquireMutex(&gTRKEventQueue);

    if (gTRKEventQueue.count == 2) {
        ret = 0x100;
    } else {
        nextEventID = (gTRKEventQueue.next + gTRKEventQueue.count) % 2;
        TRK_memcpy(&gTRKEventQueue.events[nextEventID], event, sizeof(TRKEvent));
        gTRKEventQueue.events[nextEventID].eventID = gTRKEventQueue.eventID;
        gTRKEventQueue.eventID++;

        if (gTRKEventQueue.eventID < 0x100)
            gTRKEventQueue.eventID = 0x100;

        gTRKEventQueue.count++;
    }

    TRKReleaseMutex(&gTRKEventQueue);
    return ret;
}

/** Fills in an event with the given type, id 0 and no message buffer (-1). */
void TRKConstructEvent(TRKEvent* event, int eventType) {
    event->eventType = eventType;
    event->eventID = 0;
    event->msgBufID = -1;
}

/** Frees the message buffer the event refers to (a no-op for buffer -1). */
void TRKDestructEvent(TRKEvent* event) {
    TRKReleaseBuffer(event->msgBufID);
}
