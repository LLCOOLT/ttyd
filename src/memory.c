// Memory: the OS heaps, the map heap allocator (_mapAlloc/_mapFree) and the smart heap (smartAlloc) used for loaded files.
#include "version.h"
#include "memory.h"
#include "system.h"
#include <dolphin/os.h>
#include <string.h>
#include "manager/dvdmgr.h"

// HEAP_MALLOC block is a series of these nodes
typedef struct MapAllocEntry MapAllocEntry;
struct MapAllocEntry {
    MapAllocEntry* next;   // 0x0
    u32 size;              // 0x4
    u16 inuse;             // 0x8
    u16 currId;            // 0xA
    u8 pad_0C[0x20 - 0xC]; // 0xC, pads the header to 32 bytes
};

//.bss
#if VERSION == VERSION_DEMO
// demo: smartWork is defined after the heap arrays (they share its .bss), so it is laid out first
extern SmartWork smartWork;
#else
SmartWork smartWork;
#endif

//.sdata
// flag, size / 0x400 (>> 10)
#if VERSION >= VERSION_US
// US: no fixed battle heap (battle maps use a map sub-heap); the smart heap is index 4
#define HEAP_COUNT 5
#define SMART_HEAP 4
s32 size_table[HEAP_COUNT][2] = {
    {1, 0x1C84},
    {1, 0xD90},
    {1, 0xE0},
    {1, 0x80},
    {0, 0x64}
};
#else
#define HEAP_COUNT 6
#define SMART_HEAP 5
s32 size_table[HEAP_COUNT][2] = {
#if VERSION == VERSION_DEMO
    {1, 0x3784}, //0xDE1000
#else
    {1, 0x1C84}, //0x721000, 7300 KiB/7.13 MiB
#endif
    {1, 0xD90}, //0x364000, 3472 KiB/3.39 MiB
    {1, 0xE0}, //0x38000, 224 KiB
    {1, 0x80}, //0x20000, 128 KiB
    {1, 0x100}, //0x40000, 256 KiB
    {0, 0x64}
};
#endif
static SmartWork* wp = &smartWork;

//.sbss
OSHeapHandle heapHandle[HEAP_COUNT];
void* heapStart[HEAP_COUNT];
void* heapEnd[HEAP_COUNT];
#if VERSION == VERSION_DEMO
SmartWork smartWork;
#endif
#if VERSION >= VERSION_US
// uninitialized .sbss is laid out in reverse definition order
u32 mapalloc_size;
u32 R_battlemapalloc_size;
BOOL g_bFirstSmartAlloc;
void* R_battlemapalloc_base_ptr;
void* mapalloc_base_ptr;
#else
void* mapalloc_base_ptr;
u32 mapalloc_size;
BOOL g_bFirstSmartAlloc;
#endif
#if VERSION <= VERSION_JP
static u16 count; // JP/demo: id stamped on each map heap allocation (MapAllocEntry.currId)
#endif

#if VERSION == VERSION_DEMO
// demo: the smart heap is a fixed 7 MiB block taken from the default heap
#define SMART_ALLOC_HEAP HEAP_DEFAULT
#else
#define SMART_ALLOC_HEAP SMART_HEAP
#endif

// local prototypes
void smartGarbage(void);

// Size of the smart heap's block: the demo takes a fixed 7 MiB, later versions use their whole heap minus 32 bytes.
static inline u32 smartHeapSize(void) {
#if VERSION == VERSION_DEMO
    return 0x700000;
#else
    return (u8*)heapEnd[SMART_HEAP] - (u8*)heapStart[SMART_HEAP] - 32;
#endif
}

void memInit(void) { // almost 1:1, stubborn regalloc at the end
    MapAllocEntry* entry;
    void* arenaLo;
    void* arenaHi;
    u32 restSize;
    int i;
    int size;
    u8* temp;

    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();
    arenaLo = OSInitAlloc(arenaLo, arenaHi, HEAP_COUNT);
    OSSetArenaLo(arenaLo);
    arenaLo = (void*)OSRoundUp32B(arenaLo);
    arenaHi = (void*)OSRoundDown32B(arenaHi);
    temp = arenaLo;

    for (i = 0; i < HEAP_COUNT; i++) {
        if (size_table[i][0] == 1) {
            heapStart[i] = temp;
            size = size_table[i][1] << 10;
            heapEnd[i] = temp + size;
            temp += size;
        }
    }

    restSize = (u8*)arenaHi - temp;
    for (i = 0; i < HEAP_COUNT; i++) {
        if (size_table[i][0] == 0) {
            size = (size_table[i][1] * (u64)restSize) / 100Ull;
            heapStart[i] = temp;
            size -= (size & 0x1F);
            heapEnd[i] = temp + size;
            temp += size;
        }
    }
    for (i = 0; i < HEAP_COUNT; i++) {
        heapHandle[i] = OSCreateHeap(heapStart[i], heapEnd[i]);
    }
    OSSetArenaLo((void*)arenaHi);
    for (i = 0; i < HEAP_COUNT; i++) {
        memClear(i);
    }
}

static inline void mapallocInit(void) {
    // the declaration order differs per version (it sets which callee-saved register holds each)
#if VERSION >= VERSION_US
    u32 size;
    MapAllocEntry* entry;
#else
    MapAllocEntry* entry;
    u32 size;
#endif
    u32 total;

    size = (u8*)heapEnd[HEAP_MALLOC] - (u8*)heapStart[HEAP_MALLOC] - sizeof(MapAllocEntry);
#if VERSION >= VERSION_US
    mapalloc_size = size;
#endif
    entry = OSAllocFromHeap(heapHandle[HEAP_MALLOC], size);
    if (entry) {
        memset(entry, 0, size);
        DCFlushRange(entry, size);
    }
#if VERSION >= VERSION_US
    // US re-reads the stored size and sets the base pointer before writing the first entry
    total = mapalloc_size;
    mapalloc_base_ptr = entry;
#else
    total = size;
#endif
    entry->next = NULL;
    entry->size = total - sizeof(MapAllocEntry);
    entry->inuse = 0;
#if VERSION <= VERSION_JP
    mapalloc_base_ptr = entry;
    mapalloc_size = size;
    count = 0;
#endif
}

void memClear(HEAP_TYPE heap) {
    OSDestroyHeap(heapHandle[heap]);
    OSCreateHeap(heapStart[heap], heapEnd[heap]);
    if (heap == HEAP_MALLOC) {
        mapallocInit();
    }
}

void* __memAlloc(HEAP_TYPE heap, u32 size) {
    void* ptr;

    ptr = OSAllocFromHeap(heapHandle[heap], size);
    if (ptr) {
        memset(ptr, 0, size);
        DCFlushRange(ptr, size);
    }
    return ptr;
}

void __memFree(HEAP_TYPE heap, void* ptr) {
    OSFreeToHeap(heapHandle[heap], ptr);
}

#if VERSION >= VERSION_US
void N_battleMapAlloc(void) {
    MapAllocEntry* entry;
    u32 size;

    R_battlemapalloc_size = 0x64000;
    entry = (_mapAlloc)(mapalloc_base_ptr, 0x64000);
    size = R_battlemapalloc_size;
    R_battlemapalloc_base_ptr = entry;
    entry->next = NULL;
    entry->size = size - sizeof(MapAllocEntry);
    entry->inuse = 0;
}

void N_battleMapFree(void) {
    (_mapFree)(mapalloc_base_ptr, R_battlemapalloc_base_ptr);
    R_battlemapalloc_base_ptr = NULL;
}
#endif

// US: the caller passes the heap (the map heap or the battle map sub-heap); JP and the demo have one map heap.
#if VERSION >= VERSION_US
void*(_mapAlloc)(void* base, u32 size) {
#else
void*(_mapAlloc)(u32 size) {
#endif
    MapAllocEntry* nextptr;   // shorthand to make sure regalloc is correct
    MapAllocEntry* entry;     // for our loop
    MapAllocEntry* tailEntry; // make sure we don't lose when inserting, might need better name
    MapAllocEntry* currEntry; // one we're allocating
    void* usableData;         // memory caller can actually use
    u32 usableSize;           // size minus the MapAllocEntry header
    u32 maxSize;              // used to update latest tail
    u32 fullSize;             // size including header

    usableSize = OSRoundUp32B(size);
    if (!usableSize) {
        return NULL;
    }
#if VERSION >= VERSION_US
    entry = base;
#else
    entry = mapalloc_base_ptr;
#endif
    fullSize = usableSize + sizeof(MapAllocEntry);
    maxSize = 0;
    tailEntry = 0;
    while (1) {
        if (!entry->inuse && entry->size >= fullSize) {
            if (maxSize > entry->size || !maxSize) {
                tailEntry = entry->next;
                currEntry = entry;
                maxSize = entry->size;
            }
        }
        if (!entry->next)
            break;
        entry = entry->next;
    }
    if (maxSize) {
        usableData = (void*)(currEntry + 1);

        currEntry->next = (void*)((u8*)currEntry + fullSize);
        currEntry->size = usableSize;
        currEntry->inuse = 1;
#if VERSION <= VERSION_JP
        currEntry->currId = count++;
#endif

        nextptr = currEntry->next;
        nextptr->next = tailEntry;
        nextptr->size = maxSize - fullSize;
        nextptr->inuse = 0;
#if VERSION <= VERSION_JP
        nextptr->currId = 0;
#endif

        memset(usableData, 0, usableSize);
        DCFlushRange(usableData, usableSize);
        return usableData;
    } else {
        return NULL;
    }
}

#if VERSION >= VERSION_US
void*(_mapAllocTail)(void* base, u32 size) {
#else
void*(_mapAllocTail)(u32 size) {
#endif
    MapAllocEntry* nextptr;   // shorthand to make sure regalloc is correct
    MapAllocEntry* entry;     // for our loop
    MapAllocEntry* tailEntry; // make sure we don't lose when inserting, might need better name
    MapAllocEntry* currEntry; // one we're allocating
    // void* usableData; //memory caller can actually use
    u32 maxSize;    // used to update latest tail
    u32 fullSize;   // size including header
    u32 usableSize; // size minus the MapAllocEntry header

    usableSize = OSRoundUp32B(size);
    if (!usableSize) {
        return NULL;
    }
#if VERSION >= VERSION_US
    entry = base;
#else
    entry = mapalloc_base_ptr;
#endif
    fullSize = usableSize + sizeof(MapAllocEntry);
    maxSize = 0;
    tailEntry = 0;
    while (1) {
        if (!entry->inuse && entry->size >= fullSize) {
            tailEntry = entry->next;
            currEntry = entry;
            maxSize = entry->size;
        }
        if (!entry->next)
            break;
        entry = entry->next;
    }
    if (maxSize) {
        memset(currEntry, 0, fullSize);
        DCFlushRange(currEntry, fullSize);

        currEntry->next = (MapAllocEntry*)(((u8*)currEntry + maxSize) - fullSize);
        currEntry->size = maxSize - fullSize;
        currEntry->inuse = 0;
#if VERSION <= VERSION_JP
        currEntry->currId = 0;
#endif

        nextptr = currEntry->next;
        nextptr->next = tailEntry;
        tailEntry = (void*)(nextptr + 1);
        nextptr->size = usableSize;
        nextptr->inuse = 1;
#if VERSION <= VERSION_JP
        nextptr->currId = count++;
#endif

        memset(tailEntry, 0, usableSize);
        DCFlushRange(tailEntry, usableSize);
        return tailEntry;
    } else {
        return NULL;
    }
}

#if VERSION >= VERSION_US
#pragma dont_inline on // US N_battleMapFree calls it
#endif
#if VERSION >= VERSION_US
void(_mapFree)(void* base, void* alloc) {
#else
void(_mapFree)(void* alloc) {
#endif
    MapAllocEntry* loopEntry;
    MapAllocEntry* nextEntry;
    u32 newSize;
    MapAllocEntry* entry;

    if (!alloc)
        return;
    entry = (MapAllocEntry*)alloc - 1;
    if (!entry->inuse)
        return;
    nextEntry = entry->next;
    newSize = entry->size;
    if (nextEntry && !nextEntry->inuse) {
        newSize += nextEntry->size + sizeof(MapAllocEntry);
        nextEntry = nextEntry->next;
    }
#if VERSION >= VERSION_US
    loopEntry = base;
#else
    loopEntry = mapalloc_base_ptr;
#endif
    while (1) {
        if (loopEntry->next == entry) {
            if (!loopEntry->inuse) {
                newSize += loopEntry->size + sizeof(MapAllocEntry);
                entry = loopEntry;
            }
            break;
        }
        if (loopEntry > entry || !loopEntry->next)
            break;
        loopEntry = loopEntry->next;
    }
    entry->next = nextEntry;
    entry->size = newSize;
    entry->inuse = 0;
}
#if VERSION >= VERSION_US
#pragma dont_inline reset
#endif

void smartInit(void) {
    smartEntry* e;
    u32 size;
    void* ptr;
    int i;

    size = smartHeapSize();
    ptr = OSAllocFromHeap(heapHandle[SMART_ALLOC_HEAP], size);
    if (ptr) {
        memset(ptr, 0, size);
        DCFlushRange(ptr, size);
    }
    wp->ptr = ptr;
    wp->allocHead = 0;
    wp->allocTail = 0;
    wp->bytesLeft = smartHeapSize();
    memset(wp->ptr, 0, smartHeapSize());
    memset(wp->work, 0, sizeof(wp->work));
    e = wp->work;
    for (i = 0; i < 0x800; i++, e++) {
        e->next = e + 1;
        e->prev = e - 1;
    }
    wp->head = &wp->work[0];
    wp->head->prev = NULL;
    wp->tail = &wp->work[0x7FF];
    wp->tail->next = NULL;
    wp->waitsync = 0;
    g_bFirstSmartAlloc = FALSE;
}

#if VERSION != VERSION_DEMO
void L_smartReInit(void) {
    smartEntry* e;
    int i;

    wp->allocHead = 0;
    wp->allocTail = 0;
    wp->bytesLeft = smartHeapSize();
    memset(wp->ptr, 0, smartHeapSize());
    memset(wp->work, 0, sizeof(wp->work));
    e = wp->work;
    for (i = 0; i < 0x800; i++, e++) {
        e->next = e + 1;
        e->prev = e - 1;
    }
    wp->head = &wp->work[0];
    wp->head->prev = NULL;
    wp->tail = &wp->work[0x7FF];
    wp->tail->next = NULL;
    g_bFirstSmartAlloc = 0;
}
#endif

// FAKE: #pragma dont_inline on: keeps smartAutoFree out of line as in the target; without it smartAutoFree is inlined into smartAlloc (206 -> 228 instructions)
#pragma dont_inline on
void smartAutoFree(s32 group) {
    smartEntry* entry;
    smartEntry* next;
    u16 type = group;

    for (entry = wp->allocHead; entry; entry = next) {
        next = entry->next;
        if (entry->type == type) {
            smartFree(entry);
        }
    }
    if (group == 3) {
        for (entry = wp->allocHead; entry; entry = next) {
            next = entry->next;
            if ((s32)entry->type == 4) {
                smartFree(entry);
            }
        }
    }
}

#pragma dont_inline reset
void smartFree(smartEntry* entry) {
    u32 total;

    if (entry->type == 4) {
        entry->type = 3;
        return;
    }
    if (!entry->prev) {
        wp->allocHead = entry->next;
        if (wp->allocHead) {
            wp->allocHead->prev = NULL;
        }
    } else {
        entry->prev->next = entry->next;
    }
    if (!entry->next) {
        wp->allocTail = entry->prev;
        if (wp->allocTail) {
            wp->allocTail->next = NULL;
        }
    } else {
        entry->next->prev = entry->prev;
    }
    total = entry->size + entry->spaceAfter;
    if (entry->prev) {
        entry->prev->spaceAfter += total;
    } else {
        wp->bytesLeft += total;
    }
    if (!wp->head) {
        wp->head = entry;
        entry->prev = NULL;
    } else {
        wp->tail->next = entry;
        entry->prev = wp->tail;
    }
    entry->inUse = 0;
    entry->next = NULL;
    entry->size = 0;
    entry->spaceAfter = 0;
    entry->file = NULL;
    wp->tail = entry;
    wp->waitsync++;
}

smartEntry* smartAlloc(u32 size, u8 type) {
    smartEntry* entry1;
    smartEntry* entry2;
    int i;
    u32 sz = size;

    if (!g_bFirstSmartAlloc) {
        g_bFirstSmartAlloc = TRUE;
        smartAutoFree(3);
    }

    if (wp->waitsync) {
        sysWaitDrawSync();
        wp->waitsync = 0;
    }

    entry2 = wp->head;

    if (!entry2->prev) {
        wp->head = entry2->next;
        if (wp->head) {
            wp->head->prev = NULL;
        }
    } else {
        entry2->prev->next = entry2->next;
    }

    if (!entry2->next) {
        wp->tail = entry2->prev;
        if (wp->tail) {
            wp->tail->next = NULL;
        }
    } else {
        entry2->next->prev = entry2->prev;
    }

    if (sz & 31) {
        sz += 32 - (sz & 31);
    }

    entry2->inUse = 1;
    entry2->type = type;
    entry2->size = sz;
    entry2->file = 0;
    if (wp->bytesLeft >= sz) {
        entry2->address = wp->ptr;
        entry2->spaceAfter = wp->bytesLeft - sz;
        entry2->next = wp->allocHead;
        entry2->prev = NULL;
        wp->bytesLeft = 0;
        if (wp->allocHead) {
            wp->allocHead->prev = entry2;
        }
        wp->allocHead = entry2;
        if (!entry2->next) {
            entry2->spaceAfter = smartHeapSize() + (u8*)wp->ptr - (u8*)entry2->address - entry2->size;
            wp->allocTail = entry2;
        }
        return entry2;
    } else {
        for (entry1 = wp->allocHead; entry1; entry1 = entry1->next) {
            if (entry1->spaceAfter >= sz) {
                entry2->address = (u8*)entry1->address + entry1->size;
                entry2->spaceAfter = entry1->spaceAfter - sz;
                entry2->next = entry1->next;
                entry2->prev = entry1;
                entry1->spaceAfter = 0;
                if (entry1->next) {
                    entry1->next->prev = entry2;
                } else {
                    wp->allocTail = entry2;
                }
                entry1->next = entry2;
                return entry2;
            }
        }
        for (i = 0; i < 3; i++) {
            switch (i) {
                case 0:
                    break;
                case 1:
                    _fileGarbage(1);
                    break;
                case 2:
                    _fileGarbage(0);
                    break;
            }
            smartGarbage();
            entry1 = wp->allocTail;
            if (entry1->spaceAfter >= sz) {
                entry2->address = (u8*)entry1->address + entry1->size;
                entry2->spaceAfter = entry1->spaceAfter - sz;
                entry2->next = entry1->next;
                entry2->prev = entry1;
                entry1->spaceAfter = 0;
                if (entry1->next) {
                    entry1->next->prev = entry2;
                } else {
                    wp->allocTail = entry2;
                }
                entry1->next = entry2;
                return entry2;
            }
        }
        return NULL;
    }
}

void smartGarbage(void) {
    u8* addr;
    u8* ptr;
    u32 total;
    smartEntry* entry;
    smartEntry* prev;

    sysWaitDrawSync();
    if (wp->allocHead) {
        wp->bytesLeft = 0;
    } else {
        wp->bytesLeft = smartHeapSize();
    }
    prev = NULL;
    ptr = wp->ptr;
    for (entry = wp->allocHead; entry; prev = entry, entry = entry->next) {
        addr = entry->address;
        if (addr != ptr) {
            if (entry->file) {
                if (entry->file->state == 3 && entry->file->entry && OSGetCurrentThread() != &dvdmgr_thread) {
                    if (prev) {
                        prev->spaceAfter = addr - ptr;
                    } else {
                        wp->bytesLeft = addr - ptr;
                    }
                    ptr = (u8*)entry->address + entry->size;
                    entry->spaceAfter = 0;
                    continue;
                }
                fileGarbageMoveMem(ptr, entry->file);
            } else {
                memmove(ptr, addr, entry->size);
                entry->address = ptr;
            }
        }
        entry->spaceAfter = 0;
        ptr = (u8*)entry->address + entry->size;
    }
    entry = wp->allocTail;
    if (entry) {
        entry->spaceAfter = smartHeapSize() + (u8*)wp->ptr - (u8*)entry->address - entry->size;
    }
    DCFlushRange(wp->ptr, smartHeapSize());
}

GXTexObj* smartTexObj(GXTexObj* obj, void** image_ptr) {
    if (image_ptr) {
        GXInitTexObjData(obj, *image_ptr);
    }
    return obj;
}
