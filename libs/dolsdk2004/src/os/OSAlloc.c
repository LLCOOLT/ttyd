#include <dolphin.h>
#include <dolphin/os.h>

#define ALIGNMENT 32

#define InRange(cell, arenaStart, arenaEnd) \
    ((u32) arenaStart <= (u32) cell) && ((u32) cell < (u32) arenaEnd)

#define HEADERSIZE 32u
#define MINOBJSIZE 64u

#ifdef DEBUG
#define ENABLE_HEAPDESC
#endif

typedef struct Cell Cell;
typedef struct HeapDesc HeapDesc;
struct Cell {
    Cell* prev;
    Cell* next;
    s32 size;
#ifdef ENABLE_HEAPDESC
    HeapDesc* hd;
    s32 requested;
#endif
};

struct HeapDesc {
    s32 size;
    Cell* free;
    Cell* allocated;
#ifdef ENABLE_HEAPDESC
    u32 paddingBytes;
    u32 headerBytes;
    u32 payloadBytes;
#endif
};

volatile int __OSCurrHeap = -1;

static HeapDesc* HeapArray;
static int NumHeaps;
static void* ArenaStart;
static void* ArenaEnd;

// prototypes
static Cell* DLAddFront(Cell* list, Cell* cell);
static Cell* DLLookup(Cell* list, Cell* cell);
static Cell* DLExtract(Cell* list, Cell* cell);
static Cell* DLInsert(Cell* list, Cell* cell);
static int DLOverlap(Cell* list, void* start, void* end);
static s32 DLSize(Cell* list);

/** Adds a cell to the front of a doubly linked cell list and returns the new head. */
static Cell* DLAddFront(Cell* list, Cell* cell) {
    cell->next = list;
    cell->prev = 0;
    if (list) {
        list->prev = cell;
    }
    return cell;
}

/** Returns the cell if it is in the list (compared by pointer), otherwise NULL. */
static Cell* DLLookup(Cell* list, Cell* cell) {
    for(; list; list = list->next) {
        if (list == cell) {
            return list;
        }
    }
    return NULL;
}

/** Unlinks a cell from a doubly linked list and returns the list's new head. */
static Cell* DLExtract(Cell* list, Cell* cell) {
    if (cell->next) {
        cell->next->prev = cell->prev;
    }
    if (cell->prev == NULL) {
        return cell->next;
    }
    cell->prev->next = cell->next;
    return list;
}

/**
 * Inserts a cell into a list sorted by address,
 * merging it with the adjoining previous and next cells when they touch; returns the head.
 */
static Cell* DLInsert(Cell* list, Cell* cell) {
    Cell* prev;
    Cell* next;

    for(next = list, prev = NULL; next != 0; prev = next, next = next->next) {
        if (cell <= next) {
            break;
        }
    }

    cell->next = next;
    cell->prev = prev;
    if (next) {
        next->prev = cell;
        if ((u8*)cell + cell->size == (u8*)next) {
            cell->size += next->size;
            next = next->next;
            cell->next = next;
            if (next) {
                next->prev = cell;
            }
        }
    }
    if (prev) {
        prev->next = cell;
        if ((u8*)prev + prev->size == (u8*)cell) {
            prev->size += cell->size;
            prev->next = next;
            if (next) {
                next->prev = prev;
            }
        }
        return list;
    }
    return cell;
}

/** Returns 1 if any cell in the list overlaps the address range [start, end). */
static int DLOverlap(Cell* list, void* start, void* end) {
    Cell* cell = list;

    while(cell) {
        if (((start <= cell) 
            && (cell < end)) 
            || ((start < (void* ) ((u8*)cell + cell->size)) 
            && ((void* ) ((u8*)cell + cell->size) <= end))) {
            return 1;
        }
        cell = cell->next;
    }
    return 0;
}

/** Returns the sum of the sizes of all cells in a list. */
static s32 DLSize(Cell* list) {
    Cell* cell;
    s32 size;

    size = 0;
    cell = list;

    while(cell) {
        size += cell->size;
        cell = cell->next;
    }

    return size;
}

/**
 * Allocates from a heap, first fit: adds a 32-byte header, rounds the size to 32 bytes,
 * and swallows the leftover when it is under 64 bytes.
 * Returns the block just past the header, or NULL if nothing fits.
 */
void* OSAllocFromHeap(int heap, u32 size) {
    HeapDesc* hd;
    Cell* cell;
    Cell* newCell;
    s32 leftoverSize;
    s32 requested;

    requested = size;
    ASSERTMSGLINE(337, HeapArray, "OSAllocFromHeap(): heap is not initialized.");
    ASSERTMSGLINE(338, (s32)size > 0, "OSAllocFromHeap(): invalid size.");
    ASSERTMSGLINE(339, heap >= 0 && heap < NumHeaps, "OSAllocFromHeap(): invalid heap handle.");
    ASSERTMSGLINE(340, HeapArray[heap].size >= 0, "OSAllocFromHeap(): invalid heap handle.");

    hd = &HeapArray[heap];
    size += 0x20;
    size = (size + 0x1F) & 0xFFFFFFE0;

    for(cell = hd->free; cell != NULL; cell = cell->next) {
        if ((signed)size <= (signed)cell->size) {
            break;
        }
    }

    if (cell == NULL) {
#if DEBUG
        OSReport("OSAllocFromHeap: Warning- failed to allocate %d bytes\n", size);
#endif
        return NULL;
    }
    ASSERTMSGLINE(364, !((s32)cell & 0x1F), "OSAllocFromHeap(): heap is broken.");
    ASSERTMSGLINE(365, cell->hd == NULL, "OSAllocFromHeap(): heap is broken.");

    leftoverSize = cell->size - size;
    if (leftoverSize < 0x40U) {
        hd->free = DLExtract(hd->free, cell);
    } else {
        cell->size = size;
        newCell = (void*)((u8*)cell + size);
        newCell->size = leftoverSize;
#ifdef ENABLE_HEAPDESC
        newCell->hd = 0;
#endif
        newCell->prev = cell->prev;
        newCell->next = cell->next;
        if (newCell->next != NULL) {
            newCell->next->prev = newCell; 
        }
        if (newCell->prev != NULL) {
            newCell->prev->next = newCell; 
        } else {
            ASSERTMSGLINE(394, hd->free == cell, "OSAllocFromHeap(): heap is broken.");
            hd->free = newCell;
        }
    }

    hd->allocated = DLAddFront(hd->allocated, cell);
#ifdef ENABLE_HEAPDESC
    cell->hd = hd;
    cell->requested = requested;
    hd->headerBytes += 0x20;
    hd->paddingBytes += (cell->size - (requested + 0x20));
    hd->payloadBytes += requested;
#endif
    return (u8*)cell + 0x20;
}

/**
 * Reserves the memory range at *rstart..*rend (rounded outward to 32 bytes) out of the free lists of all heaps,
 * so the caller can use a fixed address.
 * Updates the range to what was reserved and returns the start; NULL if the range overlaps an allocated block.
 */
void* OSAllocFixed(void* rstart, void* rend) {
    int i;
    Cell* cell;
    Cell* newCell;
    HeapDesc* hd;
    void* start;
    void* end;
    void* cellEnd;

    start = (void*)((*(u32*)rstart) & ~((32)-1));
    end = (void*)((*(u32*)rend + 0x1FU) & ~((32)-1));

    ASSERTMSGLINE(436, HeapArray, "OSAllocFixed(): heap is not initialized.");
    ASSERTMSGLINE(437, (u32)start < (u32)end, "OSAllocFixed(): invalid range.");
    ASSERTMSGLINE(439, ((u32) ArenaStart <= (u32) start) && ((u32) end <= (u32) ArenaEnd), "OSAllocFixed(): invalid range.");

    for(i = 0; i < NumHeaps; i++) {
        hd = &HeapArray[i];
        if(hd->size >= 0) {
            if (DLOverlap(hd->allocated, start, end)) {
#if DEBUG
                OSReport("OSAllocFixed: Warning - failed to allocate from %p to %p\n", start, end);
#endif
                return NULL;
            }
        }
    }

    for(i = 0; i < NumHeaps; i++) {
        hd = &HeapArray[i];
        if (hd->size >= 0) {
            for(cell = hd->free; cell; cell = cell->next) {
                cellEnd = ((u8*)cell + cell->size);
                if(cellEnd > start) {
                    if (end <= cell) {
                        break; 
                    }
                    if ((char*)start-0x20 <= (char*)cell && cell < end && (start <= cellEnd) && (cellEnd < ((char*)end + 0x40))) {
                        if (cell < start) {
                            start = cell;
                        }
                        if (end < cellEnd) {
                            end = cellEnd;
                        }
                        hd->free = DLExtract(hd->free, cell);
                        hd->size -= cell->size;
                    } else if((char*)start-0x20 <= (char*)cell && cell < end) {
                            if (cell < start) {
                                start = cell;
                            }
                            ASSERTLINE(503, MINOBJSIZE <= (char*) cellEnd - (char*) end);
                            newCell = (Cell*)end;

                            newCell->size = (s32) ((char*)cellEnd - (char*)end);
#ifdef ENABLE_HEAPDESC
                            newCell->hd = 0;
#endif
                            newCell->next = cell->next;
                            if (newCell->next) { 
                                newCell->next->prev = newCell;
                            }
                            newCell->prev = cell->prev;
                            if (newCell->prev) {
                                newCell->prev->next = newCell;
                            } else {
                                hd->free = newCell;
                            }
                            hd->size -= ((char*)end - (char*)cell);
                            break;
                    } else {
                        if ((start <= cellEnd) && (cellEnd < ((char*)end + 0x40U))) {
                            if (end < cellEnd) {
                                end = cellEnd;
                            }
                            ASSERTLINE(528, MINOBJSIZE <= (char*) start - (char*) cell);
                            hd->size -= ((char*)cellEnd - (char*)start);
                            cell->size = ((char*)start - (char*)cell);
                        } else {
                            ASSERTLINE(535, MINOBJSIZE <= (char*) cellEnd - (char*) end);
                            newCell = (Cell*)end;
                            newCell->size = ((char*)cellEnd - (char*)end);
#ifdef ENABLE_HEAPDESC
                            newCell->hd = 0;
#endif
                            newCell->next = cell->next;
                            if (newCell->next) {
                                newCell->next->prev = newCell;
                            }
                            newCell->prev = cell;
                            cell->next = newCell;
                            cell->size = ((char*)start - (char*)cell);
                            hd->size -= ((char*)end - (char*)start);
                            break;
                        }
                    }
                }
            }
            ASSERTLINE(550, 0 <= hd->size);
        }
    }
    ASSERTLINE(553, OFFSET(start, ALIGNMENT) == 0);
    ASSERTLINE(554, OFFSET(end, ALIGNMENT) == 0);
    ASSERTLINE(555, start < end);
    *(u32*)rstart = (u32)start;
    *(u32*)rend = (u32)end;
    return (void*)*(u32*)rstart;
}

/**
 * Frees a block from a heap: moves its cell from the allocated list to the address-ordered free list,
 * merging with neighbours.
 */
void OSFreeToHeap(int heap, void* ptr) {
    HeapDesc* hd;
    Cell* cell;

    ASSERTMSGLINE(577, HeapArray, "OSFreeToHeap(): heap is not initialized.");
    ASSERTMSGLINE(579, ((u32)ArenaStart+0x20) <= (u32)ptr && (u32)ptr < (u32)ArenaEnd, "OSFreeToHeap(): invalid pointer.");
    ASSERTMSGLINE(580, OFFSET(ptr, ALIGNMENT) == 0, "OSFreeToHeap(): invalid pointer.");
    ASSERTMSGLINE(581, HeapArray[heap].size >= 0, "OSFreeToHeap(): invalid heap handle.");
    cell = (void*)((u32)ptr-0x20);
    hd = &HeapArray[heap];
    ASSERTMSGLINE(586, cell->hd == hd, "OSFreeToHeap(): invalid pointer.");
    ASSERTMSGLINE(587, DLLookup(hd->allocated, cell), "OSFreeToHeap(): invalid pointer.");
#ifdef ENABLE_HEAPDESC
    cell->hd = 0;
    hd->headerBytes -= 0x20;
    hd->paddingBytes -= (cell->size - (cell->requested + 0x20));
    hd->payloadBytes -= cell->requested;
#endif
    hd->allocated = DLExtract(hd->allocated, cell);
    hd->free = DLInsert(hd->free, cell);
}

/** Sets the heap that plain OSAlloc calls use and returns the previously current one. */
int OSSetCurrentHeap(int heap) {
    int prev;

    ASSERTMSGLINE(619, HeapArray, "OSSetCurrentHeap(): heap is not initialized.");
    ASSERTMSGLINE(620, (heap >= 0) && (heap < NumHeaps), "OSSetCurrentHeap(): invalid heap handle.");
    ASSERTMSGLINE(621, HeapArray[heap].size >= 0, "OSSetCurrentHeap(): invalid heap handle.");
    prev = __OSCurrHeap;
    __OSCurrHeap = heap;
    return prev;
}

/**
 * Sets up the heap system: places the descriptor array for maxHeaps heaps at arenaStart,
 * marks all unused and returns the 32-byte aligned address after it, where the first heap can start.
 */
void* OSInitAlloc(void* arenaStart, void* arenaEnd, int maxHeaps) {
    u32 arraySize;
    int i;
    HeapDesc* hd;

    ASSERTMSGLINE(647, maxHeaps > 0, "OSInitAlloc(): invalid number of heaps.");
    ASSERTMSGLINE(649, (u32)arenaStart < (u32)arenaEnd, "OSInitAlloc(): invalid range.");
    ASSERTMSGLINE(652, maxHeaps <= (((u32)arenaEnd - (u32)arenaStart) / 24U), "OSInitAlloc(): too small range.");
    arraySize = maxHeaps * sizeof(HeapDesc);
    HeapArray = arenaStart;
    NumHeaps = maxHeaps;

    for(i = 0; i < NumHeaps; i++) {
        hd = &HeapArray[i];
        hd->size = -1;
        hd->free = hd->allocated = 0;
#ifdef ENABLE_HEAPDESC
        hd->paddingBytes = hd->headerBytes = hd->payloadBytes = 0;
#endif
    }
    __OSCurrHeap = -1;
    arenaStart = (void*) ((u32)((char*)HeapArray + arraySize));
    arenaStart = (void*) (((u32)arenaStart + 0x1F) & 0xFFFFFFE0);
    ArenaStart = arenaStart;
    ArenaEnd = (void*) ((u32)arenaEnd & 0xFFFFFFE0);
    ASSERTMSGLINE(680, ((u32)ArenaEnd - (u32)ArenaStart) >= 0x40U, "OSInitAlloc(): too small range.");
    return arenaStart;
}

/**
 * Creates a heap over [start, end) (aligned inward to 32 bytes) as one big free cell,
 * in the first unused descriptor; returns its id, or -1 if none is free.
 */
int OSCreateHeap(void* start, void* end) {
    int heap;
    HeapDesc* hd;
    Cell* cell;

    ASSERTMSGLINE(705, HeapArray, "OSCreateHeap(): heap is not initialized.");
    ASSERTMSGLINE(706, (u32)start < (u32)end, "OSCreateHeap(): invalid range.");

    start = (void*)(((u32)start + 0x1FU) & ~((32)-1));
    end = (void*)(((u32)end) & ~((32)-1));

    ASSERTMSGLINE(709, (u32)start < (u32)end, "OSCreateHeap(): invalid range.");
    ASSERTMSGLINE(711, (u32)ArenaStart <= (u32)start && (u32)end <= (u32)ArenaEnd, "OSCreateHeap(): invalid range.");
    ASSERTMSGLINE(713, ((u32)end - (u32)start) >= 0x40U, "OSCreateHeap(): too small range.");

#if DEBUG
    for(heap = 0; heap < NumHeaps; heap++) {
        if (HeapArray[heap].size >= 0) {
            ASSERTMSGLINE(723, !DLOverlap(HeapArray[heap].free, start, end), "OSCreateHeap(): invalid range.");
            ASSERTMSGLINE(725, !DLOverlap(HeapArray[heap].allocated, start, end), "OSCreateHeap(): invalid range.");
        }
    }
#endif

    for(heap = 0; heap < NumHeaps; heap++) {
        hd = &HeapArray[heap];
        if (hd->size < 0) {
            hd->size = (u32)end - (u32)start;
            cell = start;
            cell->prev = 0;
            cell->next = 0;
            cell->size = hd->size;
#ifdef ENABLE_HEAPDESC
            cell->hd = 0;
#endif
            hd->free = cell;
            hd->allocated = 0;
#ifdef ENABLE_HEAPDESC
            hd->paddingBytes = hd->headerBytes = hd->payloadBytes = 0;
#endif
            return heap;
        }
    }
#if DEBUG
    OSReport("OSCreateHeap: Warning - Failed to find free heap descriptor.");
#endif
    return -1;
}

/** Releases a heap descriptor so its slot can be reused; the memory is not touched. */
void OSDestroyHeap(int heap) {
    HeapDesc* hd;
    s32 size;

    ASSERTMSGLINE(782, HeapArray, "OSDestroyHeap(): heap is not initialized.");
    ASSERTMSGLINE(783, (heap >= 0) && (heap < NumHeaps), "OSDestroyHeap(): invalid heap handle.");
    ASSERTMSGLINE(784, HeapArray[heap].size >= 0, "OSDestroyHeap(): invalid heap handle.");

    hd = &HeapArray[heap];
#if DEBUG
    size = DLSize(hd->free);

    if (hd->size != size) {
        OSReport("OSDestroyHeap(%d): Warning - free list size %d, heap size %d\n", heap, size, hd->size);
    }
#endif
    
    hd->size = -1;
    hd->free = hd->allocated = 0;
#ifdef ENABLE_HEAPDESC
    hd->paddingBytes = hd->headerBytes = hd->payloadBytes = 0;
    if (__OSCurrHeap == heap) {
        __OSCurrHeap = -1;
    }
#endif
}

/** Adds the range [start, end) to a heap as a new free cell and grows the heap's size. */
void OSAddToHeap(int heap, void* start, void* end) {
    HeapDesc* hd;
    Cell* cell;
    int i;

    ASSERTMSGLINE(830, HeapArray, "OSAddToHeap(): heap is not initialized.");
    ASSERTMSGLINE(831, (heap >= 0) && (heap < NumHeaps), "OSAddToHeap(): invalid heap handle.");
    ASSERTMSGLINE(832, HeapArray[heap].size >= 0, "OSAddToHeap(): invalid heap handle.");

    hd = &HeapArray[heap];

    ASSERTMSGLINE(836, (u32)start < (u32)end, "OSAddToHeap(): invalid range.");

    start = (void*)(((u32)start + 0x1F) & ~((32)-1));
    end = (void*)(((u32)end) & ~((32)-1));

    ASSERTMSGLINE(840, ((u32)end - (u32)start) >= 0x40U, "OSAddToHeap(): too small range.");
    ASSERTMSGLINE(842, (u32)ArenaStart <= (u32)start && (u32)end <= (u32)ArenaEnd, "OSAddToHeap(): invalid range.");

#if DEBUG
    for(i = 0; i < NumHeaps; i++) {
        if (HeapArray[i].size >= 0) {
            ASSERTMSGLINE(852, !DLOverlap(HeapArray[i].free, start, end), "OSAddToHeap(): invalid range.");
            ASSERTMSGLINE(854, !DLOverlap(HeapArray[i].allocated, start, end), "OSAddToHeap(): invalid range.");
        }
    }
#endif
    cell = (Cell*)start;
    cell->size = ((char*)end - (char*)start);
#ifdef ENABLE_HEAPDESC
    cell->hd = 0;
#endif
    hd->size += cell->size;
    hd->free = DLInsert(hd->free, cell);
} 

// custom macro for OSCheckHeap
#define ASSERTREPORT(line, cond) \
    if (!(cond)) { OSReport("OSCheckHeap: Failed " #cond " in %d", line); return -1; }

/**
 * Walks a heap's allocated and free lists and returns the total free bytes,
 * net of per-block headers (debug builds also check list consistency and return -1 if it fails).
 */
s32 OSCheckHeap(int heap) {
    HeapDesc* hd;
    Cell* cell;
    s32 total = 0;
    s32 free = 0;

    ASSERTREPORT(898, HeapArray);
    ASSERTREPORT(899, 0 <= heap && heap < NumHeaps);
    hd = &HeapArray[heap];
    ASSERTREPORT(902, 0 <= hd->size);
    
    ASSERTREPORT(0x388, hd->allocated == NULL || hd->allocated->prev == NULL);

    for(cell = hd->allocated; cell; cell = cell->next) {
        ASSERTREPORT(907, InRange(cell, ArenaStart, ArenaEnd));
        ASSERTREPORT(908, OFFSET(cell, ALIGNMENT) == 0);
        ASSERTREPORT(909, cell->next == NULL || cell->next->prev == cell);
        ASSERTREPORT(910, MINOBJSIZE <= cell->size);
        ASSERTREPORT(911, OFFSET(cell->size, ALIGNMENT) == 0);
        total += cell->size;
        ASSERTREPORT(914, 0 < total && total <= hd->size);
#ifdef ENABLE_HEAPDESC
        ASSERTREPORT(917, cell->hd == hd);
        ASSERTREPORT(918, HEADERSIZE + cell->requested <= cell->size);
#endif
    }

    
    ASSERTREPORT(922, hd->free == NULL || hd->free->prev == NULL); 
    
    for(cell = hd->free; cell; cell = cell->next) {
        ASSERTREPORT(925, InRange(cell, ArenaStart, ArenaEnd));
        ASSERTREPORT(926, OFFSET(cell, ALIGNMENT) == 0);
        ASSERTREPORT(927, cell->next == NULL || cell->next->prev == cell);
        ASSERTREPORT(928, MINOBJSIZE <= cell->size);
        ASSERTREPORT(929, OFFSET(cell->size, ALIGNMENT) == 0);
        ASSERTREPORT(930, cell->next == NULL || (char*) cell + cell->size < (char*) cell->next);
        total += cell->size;
        free = (cell->size + free);
        free -= HEADERSIZE;
        ASSERTREPORT(934, 0 < total && total <= hd->size);
#ifdef ENABLE_HEAPDESC
        ASSERTREPORT(937, cell->hd == NULL);
#endif
    }
    ASSERTREPORT(941, total == hd->size);
    return free;
}

/** Returns the usable size of an allocated block: its cell size less the 32-byte header. */
u32 OSReferentSize(void* ptr) {
    Cell* cell;

    ASSERTMSGLINE(960, HeapArray, "OSReferentSize(): heap is not initialized.");
    ASSERTMSGLINE(962, InRange(ptr, ArenaStart+HEADERSIZE, ArenaEnd), "OSReferentSize(): invalid pointer.");
    ASSERTMSGLINE(963, !OFFSET(ptr, 32), "OSReferentSize(): invalid pointer.");
    cell = (void*)((u32)ptr-HEADERSIZE);
    ASSERTMSGLINE(967, cell->hd, "OSReferentSize(): invalid pointer.");
    ASSERTMSGLINE(969, !(((u32)cell->hd - (u32)HeapArray) % 24), "OSReferentSize(): invalid pointer.");
    ASSERTMSGLINE(971, ((u32)HeapArray <= (u32)cell->hd) && ((u32)cell->hd < (u32)((u32)HeapArray + (NumHeaps * 0x18))), "OSReferentSize(): invalid pointer.");
    ASSERTMSGLINE(972, cell->hd->size >= 0, "OSReferentSize(): invalid pointer.");
    ASSERTMSGLINE(974, DLLookup(cell->hd->allocated, cell), "OSReferentSize(): invalid pointer.");
    return (s32)((u32)cell->size-HEADERSIZE);
}

/** Prints a heap's usage and every allocated and free cell (address, size, end, prev, next) to the debug console. */
void OSDumpHeap(int heap) {
    HeapDesc* hd;
    Cell* cell;

    OSReport("\nOSDumpHeap(%d):\n", heap);
    ASSERTMSGLINE(995, HeapArray, "OSDumpHeap(): heap is not initialized.");
    ASSERTMSGLINE(996, (heap >= 0) && (heap < NumHeaps), "OSDumpHeap(): invalid heap handle.");
    hd = &HeapArray[heap];
    if (hd->size < 0) {
        OSReport("--------Inactive\n");
        return;
    }
    ASSERTMSGLINE(1005, OSCheckHeap(heap) >= 0, "OSDumpHeap(): heap is broken.");
#ifdef ENABLE_HEAPDESC
    OSReport("padding %d/(%f%%) header %d/(%f%%) payload %d/(%f%%)\n", 
        hd->paddingBytes, (100.0 * hd->paddingBytes / hd->size), hd->headerBytes, (100.0 * hd->headerBytes / hd->size), hd->payloadBytes,
        (100.0 * hd->payloadBytes / hd->size));
#endif
    OSReport("addr	size		end	prev	next\n");
    OSReport("--------Allocated\n");

    ASSERTMSGLINE(1018, hd->allocated == NULL || hd->allocated->prev == NULL, "OSDumpHeap(): heap is broken.");

    for(cell = hd->allocated; cell; cell = cell->next) {
        OSReport("%x	%d	%x	%x	%x\n", cell, cell->size, (char*)cell + cell->size, cell->prev, cell->next);
    }
    OSReport("--------Free\n");
    for(cell = hd->free; cell; cell = cell->next) {
        OSReport("%x	%d	%x	%x	%x\n", cell, cell->size, (char*)cell + cell->size, cell->prev, cell->next);
    }
}

/** Calls the visitor on every allocated block in every active heap, passing its address and cell size. */
void OSVisitAllocated(void (*visitor)(void*, u32)) {
    u32 heap;
    Cell* cell;

    for(heap = 0; heap < NumHeaps; heap++) {
        if (HeapArray[heap].size >= 0) {
            for(cell = HeapArray[heap].allocated; cell; cell = cell->next) {
                visitor((char*)cell+HEADERSIZE, cell->size);
            }
        }
    }
}
