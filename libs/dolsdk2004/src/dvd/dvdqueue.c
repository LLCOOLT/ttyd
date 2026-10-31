#include <dolphin.h>
#include <dolphin/dvd.h>

#include "__dvd.h"

static struct {
    /* 0x00 */ DVDCommandBlock* next;
    /* 0x04 */ DVDCommandBlock* prev;
} WaitingQueue[4];

// prototypes
static DVDCommandBlock* PopWaitingQueuePrio(s32 prio);

/** Makes all four priority queues of waiting command blocks empty (each list head points at itself). */
void __DVDClearWaitingQueue(void) {
    u32 i;
    DVDCommandBlock* q;

    for(i = 0; i < 4; i++) {
        q = (DVDCommandBlock*)&WaitingQueue[i].next;
        q->next = q;
        q->prev = q;
    }
}

/**
 * Appends a command block to the tail of the waiting queue for priority prio (0 to 3), with interrupts off.
 * Always returns 1.
 */
int __DVDPushWaitingQueue(s32 prio, DVDCommandBlock* block) {
    BOOL enabled = OSDisableInterrupts();
    DVDCommandBlock* q = (DVDCommandBlock*)&WaitingQueue[prio];

    q->prev->next = block;
    block->prev = q->prev;
    block->next = q;
    q->prev = block;
    OSRestoreInterrupts(enabled);
    return 1;
}

/** Unlinks and returns the first command block of one priority queue, which must not be empty. */
static DVDCommandBlock* PopWaitingQueuePrio(s32 prio) {
    DVDCommandBlock* tmp;
    BOOL enabled;
    DVDCommandBlock* q;

    enabled = OSDisableInterrupts();
    q = (DVDCommandBlock*)&WaitingQueue[prio];
    ASSERTLINE(87, q->next != q);

    tmp = q->next;
    q->next = tmp->next;
    tmp->next->prev = q;
    OSRestoreInterrupts(enabled);
    tmp->next = 0;
    tmp->prev = 0;
    return tmp;
}

/** Removes and returns the first waiting command block, highest priority first, or NULL if none. */
DVDCommandBlock* __DVDPopWaitingQueue(void) {
    u32 i;
    BOOL enabled;
    DVDCommandBlock* q;

    enabled = OSDisableInterrupts();
    for (i = 0; i < 4; i++) {
        q = (DVDCommandBlock*)&WaitingQueue[i];
        if (q->next != q) {
            OSRestoreInterrupts(enabled);
            return PopWaitingQueuePrio(i);
        }
    }

    OSRestoreInterrupts(enabled);
    return NULL;
}

/** Returns whether any command block is waiting. */
int __DVDCheckWaitingQueue(void) {
    u32 i;
    BOOL enabled;
    DVDCommandBlock* q;

    enabled = OSDisableInterrupts();
    for (i = 0; i < 4; i++) {
        q = (DVDCommandBlock*)&WaitingQueue[i];
        if (q->next != q) {
            OSRestoreInterrupts(enabled);
            return 1;
        }
    }

    OSRestoreInterrupts(enabled);
    return 0;
}

/**
 * Unlinks a command block from the queue it is waiting in.
 * Returns 0 if the block is not linked into a queue, 1 otherwise.
 */
int __DVDDequeueWaitingQueue(DVDCommandBlock* block) {
    BOOL enabled;
    DVDCommandBlock* prev;
    DVDCommandBlock* next;

    enabled = OSDisableInterrupts();
    prev = block->prev;
    next = block->next;
    if (prev == NULL || next == NULL) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    prev->next = next;
    next->prev = prev;
    OSRestoreInterrupts(enabled);
    return 1;
}

/** Returns whether a given command block is waiting in a queue. */
int __DVDIsBlockInWaitingQueue(DVDCommandBlock* block) {
    u32 i;
    DVDCommandBlock* start;
    DVDCommandBlock* q;

    for (i = 0; i < 4; i++) {
        start = (DVDCommandBlock*)&WaitingQueue[i];
        if (start->next == start) {
            continue;
        }

        for (q = start->next; q != start; q = q->next) {
            if (q == block) {
                return 1;
            }
        }
    }

    return 0;
}

/** Names of the DVD command codes (index = the block's command), printed by DVDDumpWaitingQueue. */
static char* CommandNames[16] = {
    "",
    "READ",
    "SEEK",
    "CHANGE_DISK",
    "BSREAD",
    "READID",
    "INITSTREAM",
    "CANCELSTREAM",
    "STOP_STREAM_AT_END",
    "REQUEST_AUDIO_ERROR",
    "REQUEST_PLAY_ADDR",
    "REQUEST_START_ADDR",
    "REQUEST_LENGTH",
    "AUDIO_BUFFER_CONFIG",
    "INQUIRY",
    "BS_CHANGE_DISK",
};

/**
 * Debug helper: OSReports each of the four queues,
 * and for every waiting block its command name (and, for reads, the disc offset,
 * length and destination address).
 */
void DVDDumpWaitingQueue(void) {
    u32 i;
    DVDCommandBlock* start;
    DVDCommandBlock* q;

    OSReport("==== DVD Waiting Queue Status ====\n");
    for (i = 0; i < 4; i++) {
        OSReport("< Queue #%d > ", i);
        start = (DVDCommandBlock*)&WaitingQueue[i];
        if (start->next == start) {
            OSReport("None\n");
        } else {
            OSReport("\n");
            for (q = start->next; q != start; q = q->next) {
                OSReport("0x%08x: Command: %s ", q, CommandNames[q->command]);
                if (q->command == 1) {
                    OSReport("Disk offset: %d, Length: %d, Addr: 0x%08x\n", q->offset, q->length, q->addr);
                } else {
                    OSReport("\n");
                }
            }
        }
    }
}
