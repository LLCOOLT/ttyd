#include <dolphin/os.h>

// undefine the macros so they do not error the file.
#undef OSPhysicalToCached
#undef OSPhysicalToUncached
#undef OSCachedToPhysical
#undef OSUncachedToPhysical
#undef OSCachedToUncached
#undef OSUncachedToCached

/** Converts a physical address (below 0x10000000) to its cached mirror by adding 0x80000000. */
void* OSPhysicalToCached(u32 paddr) {
    ASSERTMSGLINE(47, paddr < 0x10000000U, "OSPhysicalToCached(): illegal address.");
    return (void*)(paddr + 0x80000000);
}

/** Converts a physical address (below 0x10000000) to its uncached mirror at 0xC0000000. */
void* OSPhysicalToUncached(u32 paddr) {
    ASSERTMSGLINE(62, paddr < 0x10000000U, "OSPhysicalToUncached(): illegal address.");
    return (void*)(paddr - 0x40000000);
}

/** Converts a cached 0x80000000-region address to its physical address. */
u32 OSCachedToPhysical(void* caddr) {
    ASSERTMSGLINE(77, 0x80000000U <= (u32)caddr && (u32)caddr < 0x90000000U, "OSCachedToPhysical(): illegal address.");
    return (u32)caddr + 0x80000000;
}

/** Converts an uncached 0xC0000000-region address to its physical address. */
u32 OSUncachedToPhysical(void* ucaddr) {
    ASSERTMSGLINE(92, 0xC0000000U <= (u32)ucaddr && (u32)ucaddr < 0xD0000000U, "OSUncachedToPhysical(): illegal address.");
    return (u32)ucaddr + 0x40000000;
}

/** Converts a cached address to the uncached mirror of the same memory by adding 0x40000000. */
void* OSCachedToUncached(void* caddr) {
    ASSERTMSGLINE(107, 0x80000000U <= (u32)caddr && (u32)caddr < 0x90000000U, "OSCachedToUncached(): illegal address.");
    return (void*)((u32)caddr + 0x40000000);
}

/** Converts an uncached address to the cached mirror of the same memory by subtracting 0x40000000. */
void* OSUncachedToCached(void* ucaddr) {
    ASSERTMSGLINE(122, 0xC0000000U <= (u32)ucaddr && (u32)ucaddr < 0xD0000000U, "OSUncachedToCached(): illegal address.");
    return (void*)((u32)ucaddr - 0x40000000);
}
