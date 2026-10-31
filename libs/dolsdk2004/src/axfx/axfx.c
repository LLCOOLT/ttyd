#include <dolphin.h>
#include <dolphin/ax.h>

/** Default AXFX allocator: forwards to OSAlloc. */
static void* __AXFXAllocFunction(u32 bytes) {
    return OSAlloc(bytes);
}

/** Default AXFX deallocator: forwards to OSFree. */
static void __AXFXFreeFunction(void* p) {
    OSFree(p);
}

void* (*__AXFXAlloc)(u32) = __AXFXAllocFunction;
void (*__AXFXFree)(void*) = __AXFXFreeFunction;

/**
 * Replaces the allocator and deallocator that the AXFX effects (reverb, chorus, delay) use for their delay-line
 * buffers.
 */
void AXFXSetHooks(void* (*alloc)(u32), void (*free)(void*)) {
    ASSERTLINE(46, alloc && free);

    __AXFXAlloc = alloc;
    __AXFXFree = free;
}
