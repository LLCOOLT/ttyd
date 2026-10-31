#include <dolphin/gd.h>
#include <dolphin/os.h>

/** The display list being written by the GD functions, and the callback run when it runs out of room. */
GDLObj* __GDCurrentDL = NULL;
static GDOverflowCb overflowcb = NULL;

/**
 * Sets up a display list object over a buffer: start, current write pointer (at the start),
 * end (start + length) and length.
 */
void GDInitGDLObj(GDLObj* dl, void* start, u32 length) {
    ASSERTMSGLINE(40, !((u32)start & 0x1F), "start must be aligned to 32 bytes");
    ASSERTMSGLINE(41, !((u32)length & 0x1F), "length must be aligned to 32 bytes");
    dl->start = start;
    dl->ptr = start;
    dl->top = (u8*)start + length;
    dl->length = length;
}

/** Flushes the data cache over the current display list (__GDCurrentDL) so the GPU sees what was written. */
void GDFlushCurrToMem(void) {
    DCFlushRange(__GDCurrentDL->start, __GDCurrentDL->length);
}

/** Writes zero bytes (GX no-ops) until the current display list's write pointer is 32 byte aligned. */
void GDPadCurr32(void) {
    u32 n;

    n = (u32)__GDCurrentDL->ptr & 0x1F;
    if (n != 0) {
        for (; n < 32; n = n + 1) {
            __GDWrite(0);
        }
    }
}

/**
 * Called when a write runs past the end of the current list;
 * calls the overflow callback if one is set, otherwise does nothing.
 */
void GDOverflowed(void) {
    if (overflowcb) {
        (*overflowcb)();
    } else {
        ASSERTMSGLINE(77, 0, "GDWrite: display list overflowed");
    }
}

/** Sets the function GDOverflowed calls. */
void GDSetOverflowCallback(GDOverflowCb callback) {
    overflowcb = callback;
}

/** Returns the function set with GDSetOverflowCallback (NULL if none). */
GDOverflowCb GDGetOverflowCallback(void) {
    return overflowcb;
}
