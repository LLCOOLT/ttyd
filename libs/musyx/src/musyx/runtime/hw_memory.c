#include "musyx/hardware.h"

/** Allocates len bytes with the malloc hook given to sndSetHooks. */
void* salMalloc(u32 len) { return salHooks.malloc(len); }

#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 3)
/** Allocates len bytes with the physical-memory hook (the AI buffers and the ARAM zero-buffer staging area). */
void* salMallocPhysical(u32 len) { return salHooks.mallocPhysical(len); }
#endif

/** Frees memory with the free hook given to sndSetHooks. */
void salFree(void* addr) { salHooks.free(addr); }
