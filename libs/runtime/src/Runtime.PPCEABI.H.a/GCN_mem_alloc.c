typedef int OSHeapHandle;

extern volatile OSHeapHandle __OSCurrHeap;

void OSReport(const char* msg, ...);
void* OSGetArenaLo(void);
void* OSGetArenaHi(void);
void* OSInitAlloc(void* arenaStart, void* arenaEnd, int maxHeaps);
void OSSetArenaLo(void* newLo);
OSHeapHandle OSCreateHeap(void* start, void* end);
OSHeapHandle OSSetCurrentHeap(OSHeapHandle heap);
void OSFreeToHeap(OSHeapHandle heap, void* ptr);

#define OSRoundUp32B(x) (((unsigned long)(x) + 32 - 1) & ~(32 - 1))
#define OSRoundDown32B(x) (((unsigned long)(x)) & ~(32 - 1))

/**
 * Fallback for programs that never created an OS heap:
 * prints a notice, then builds one heap over the whole remaining arena (rounded to 32 bytes)
 * and makes it current, so malloc/free have somewhere to work.
 */
static inline void InitDefaultHeap(void) {
    void* arenaLo;
    void* arenaHi;

    OSReport("GCN_Mem_Alloc.c : InitDefaultHeap. No Heap Available\n");
    OSReport("Metrowerks CW runtime library initializing default heap\n");

    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();

    arenaLo = OSInitAlloc(arenaLo, arenaHi, 1);
    OSSetArenaLo(arenaLo);

    arenaLo = (void*)OSRoundUp32B(arenaLo);
    arenaHi = (void*)OSRoundDown32B(arenaHi);

    OSSetCurrentHeap(OSCreateHeap(arenaLo, arenaHi));
    OSSetArenaLo(arenaLo = arenaHi);
}

/**
 * Metrowerks runtime back end of free(): releases the block to the current OS heap,
 * creating the default heap first if none has been set up yet.
 */
void __sys_free(void* ptr) {
    if (__OSCurrHeap == -1)
        InitDefaultHeap();

    OSFreeToHeap(__OSCurrHeap, ptr);
}
