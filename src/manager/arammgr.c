// ARAM manager: allocates auxiliary RAM, copies data between main memory and ARAM with ARQ, and
// collects the space of freed entries.
#include "manager/arammgr.h"
#include "memory.h"
#include <dolphin/os.h>
#include <string.h>

#define ARAM_OWNER 0x19751128

//.bss
static ARAMWork work;

//.sdata
static ARAMWork* wp = &work;

// local prototypes
static void aramCallbackGarbage(u32 request);
static void arqCallbackToAram(u32 request);
static void arqCallbackToMram(u32 request);

/**
 * Boot-time setup from mariost.c: starts AR/ARQ, claims a 0x3FC000-byte ARAM region and a table of 64 entries.
 * mapdrv parks map data, textures and archives there between areas.
 */
void aramMgrInit(void) {
    memset(wp, 0, sizeof(ARAMWork));
    if (!ARCheckInit()) {
        ARInit(wp->arStack, 8);
    }
    ARQInit();
    wp->size = 0x3FC000;
    wp->count = 64;
    wp->baseAddr = ARAlloc(wp->size);
    wp->nextAddr = wp->baseAddr;
    wp->entries = __memAlloc(HEAP_DEFAULT, wp->count * sizeof(ARAMEntry));
    memset(wp->entries, 0, wp->count * sizeof(ARAMEntry));
    wp->head = NULL;
    wp->tail = NULL;
}

/**
 * ARQ completion for the compaction copies: clears the busy flag the copy loop spins on
 * and invalidates the bounce buffer.
 */
static void aramCallbackGarbage(u32 request) {
    wp->busy = 0;
    DCInvalidateRange(wp->buffer, wp->bufferSize);
    ICInvalidateRange(wp->buffer, wp->bufferSize);
}

/**
 * Compacts ARAM when the bump allocator runs off the end:
 * waits for transfers in flight, unlinks entries already copied back to main RAM (flag 0x20),
 * then slides the live ones down through a 32 KB main-RAM bounce buffer.
 */
static void aramMgrGarbage(void) {
    ARAMEntry* head;
    ARAMEntry* entry;
    ARAMEntry* prev;
    ARAMEntry* first;
    u32 offset;
    u32 addr;
    ARAMEntry* curr;
    int i, n;

    head = wp->head;
    for (entry = head; entry != NULL; entry = entry->next) {
        if (entry->flags & ARAM_ENTRY_TO_ARAM) {
            while (!(entry->flags & ARAM_ENTRY_TO_ARAM_DONE)) {}
        }
        if (entry->flags & ARAM_ENTRY_TO_MRAM) {
            while (!(entry->flags & ARAM_ENTRY_TO_MRAM_DONE)) {}
        }
    }

    entry = head;
    prev = NULL;
    first = NULL;
    while (entry != NULL) {
        if (entry->flags & ARAM_ENTRY_SPENT) {
            entry->flags = 0;
            if (prev != NULL) {
                prev->next = entry->next;
            }
            entry = entry->next;
        } else {
            if (prev == NULL) {
                first = entry;
            }
            prev = entry;
            entry = entry->next;
        }
    }
    wp->head = first;
    wp->tail = prev;

    addr = wp->baseAddr;
    for (curr = wp->head; curr != NULL; curr = curr->next) {
        if (curr->aramAddr != addr) {
            wp->bufferSize = 0x8000;
            wp->buffer = __memAlloc(HEAP_DEFAULT, wp->bufferSize);
            n = (curr->size + (wp->bufferSize - 1)) / wp->bufferSize;
            for (i = 0, offset = 0; i < n; i++, offset += 0x8000) {
                wp->busy = 1;
                ARQPostRequest(&wp->request, ARAM_OWNER, ARQ_TYPE_ARAM_TO_MRAM, ARQ_PRIORITY_LOW,
                               curr->aramAddr + offset, (u32)wp->buffer, wp->bufferSize, aramCallbackGarbage);
                while (wp->busy) {}
                wp->busy = 1;
                ARQPostRequest(&wp->request, ARAM_OWNER, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_LOW,
                               (u32)wp->buffer, addr + offset, wp->bufferSize, aramCallbackGarbage);
                while (wp->busy) {}
            }
            __memFree(HEAP_DEFAULT, wp->buffer);
            wp->buffer = NULL;
        }
        curr->aramAddr = addr;
        addr = curr->aramAddr + curr->size;
    }
    wp->nextAddr = addr;
}

/** ARQ completion for an upload: marks the matching entry's copy to ARAM as finished (ARAM_ENTRY_TO_ARAM_DONE). */
static void arqCallbackToAram(u32 request) {
    ARAMEntry* entry;

    for (entry = wp->head; entry != NULL; entry = entry->next) {
        if (request == (u32)&entry->request)
            break;
    }
    entry->flags |= ARAM_ENTRY_TO_ARAM_DONE;
}

/**
 * Starts copying size bytes (rounded up to 32) from main RAM to the next free ARAM space
 * and returns the entry tracking it; compacts ARAM first if the region is full.
 * Does not check for a free entry slot.
 */
ARAMEntry* aramMgrToAramAsync(void* src, u32 size) {
    ARAMEntry* entry = NULL;
    ARAMEntry* curr;
    u32 addr;
    int i;

    for (i = 0, curr = wp->entries; i < wp->count; i++, curr++) {
        if (!(curr->flags & ARAM_ENTRY_IN_USE)) {
            entry = curr;
            break;
        }
    }
    memset(entry, 0, sizeof(ARAMEntry));
    size = (size + 31) & ~31;
    addr = wp->nextAddr;
    wp->nextAddr += size;
    if (wp->nextAddr >= wp->baseAddr + wp->size) {
        aramMgrGarbage();
        addr = wp->nextAddr;
        wp->nextAddr += size;
    }
    DCStoreRange(src, size);
    ARQPostRequest(&entry->request, ARAM_OWNER, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_LOW,
                   (u32)src, addr, size, arqCallbackToAram);
    entry->flags |= ARAM_ENTRY_IN_USE;
    entry->flags |= ARAM_ENTRY_TO_ARAM;
    entry->mramAddr = src;
    entry->size = size;
    entry->aramAddr = addr;
    entry->next = NULL;
    if (wp->head == NULL) {
        wp->head = entry;
        wp->tail = entry;
    } else {
        wp->tail->next = entry;
        wp->tail = entry;
    }
    return entry;
}

/** Copies a block to ARAM and spins until the transfer is done; mapdrv uses it to stash the previous map's data. */
ARAMEntry* aramMgrToAram(void* src, u32 size) {
    ARAMEntry* entry = aramMgrToAramAsync(src, size);
    while (!(entry->flags & ARAM_ENTRY_TO_ARAM_DONE)) {}
    return entry;
}

/**
 * ARQ completion for a download: marks the entry as back in main RAM and spent (ARAM_ENTRY_TO_MRAM_DONE and ARAM_ENTRY_SPENT,
 * so the next compaction frees it), then invalidates the caches over the destination.
 */
static void arqCallbackToMram(u32 request) {
    ARAMEntry* entry;

    for (entry = wp->head; entry != NULL; entry = entry->next) {
        if (request == (u32)&entry->request)
            break;
    }
    entry->flags |= ARAM_ENTRY_TO_MRAM_DONE;
    entry->flags |= ARAM_ENTRY_SPENT;
    DCInvalidateRange(entry->dest, entry->size);
    ICInvalidateRange(entry->dest, entry->size);
}

/**
 * Copies an entry back from ARAM to dest, waiting for its upload to finish first and then for the copy itself.
 * Each entry is read back once; mapdrv restores a stashed map with it.
 */
void aramMgrToMram(ARAMEntry* entry, void* dest) {
    while (!(entry->flags & ARAM_ENTRY_TO_ARAM_DONE)) {}
    ARQPostRequest(&entry->request, ARAM_OWNER, ARQ_TYPE_ARAM_TO_MRAM, ARQ_PRIORITY_LOW,
                   entry->aramAddr, (u32)dest, entry->size, arqCallbackToMram);
    entry->flags |= ARAM_ENTRY_TO_MRAM;
    entry->dest = dest;
    while (!(entry->flags & ARAM_ENTRY_TO_MRAM_DONE)) {}
}
