// Saved work driver: the event flags and words kept in the save file: the global ones (GSW/GSWF)
// and the area-local ones (LSW/LSWF).
#include "driver/swdrv.h"
#include "mario/mariost.h"
#include <string.h>

/**
 * Clears all saved work: the global flags (GSWF) and words (GSW, including GSW0)
 * and the area-local ones (LSWF, LSW). Runs at boot, on a new or loaded file (seq_load) and in the E3 demo.
 */
void swInit(void) {
    memset(gp->gswf, 0, sizeof(gp->gswf));
    memset(gp->gsw, 0, sizeof(gp->gsw));
    memset(gp->lswf, 0, sizeof(gp->lswf));
    memset(gp->lsw, 0, sizeof(gp->lsw));
    gp->gsw0 = 0;
}

/**
 * Clears only the area-local flags (LSWF) and words (LSW);
 * the map-change sequence calls it when Mario enters a different area.
 */
void swReInit(void) {
    memset(gp->lswf, 0, sizeof(gp->lswf));
    memset(gp->lsw, 0, sizeof(gp->lsw));
}

/** Global Saved Work Flags -------------------------------------- */
void swSet(s32 index) { // set specific bit
    gp->gswf[index / 32] |= (1 << (index % 32));
}

/** Returns whether global saved flag GSWF(index) is set. */
BOOL swGet(s32 index) { // get specific bit
    return (gp->gswf[index / 32] & (1 << (index % 32))) != 0;
}

/** Clears global saved flag GSWF(index). */
void swClear(s32 index) { // clear specific bit
    gp->gswf[index / 32] &= ~(1 << (index % 32));
}

/** Global Saved Work -------------------------------------------- */
void swByteSet(s32 index, s32 value) {
    if (index == 0) {
        gp->gsw0 = value;
    } else {
        gp->gsw[index] = (u8)value;
    }
}

/** Returns global saved word GSW(index). GSW(0), the story progress, is a full 32-bit value; the others are bytes. */
s32 swByteGet(s32 index) {
    if (index == 0) {
        return gp->gsw0;
    } else {
        return gp->gsw[index];
    }
}

/** Local Saved Work Flags --------------------------------------- */
void _swSet(s32 index) { // set specific bit
    gp->lswf[index / 32] |= (1 << (index % 32));
}

/** Returns whether area-local saved flag LSWF(index) is set. */
BOOL _swGet(s32 index) { // get specific bit
    return (gp->lswf[index / 32] & (1 << (index % 32))) != 0;
}

/** Clears area-local saved flag LSWF(index). */
void _swClear(s32 index) { // clear specific bit
    gp->lswf[index / 32] &= ~(1 << (index % 32));
}

/** Local Saved Work --------------------------------------------- */
void _swByteSet(s32 index, u8 value) {
    gp->lsw[index] = value;
}

/** Returns area-local saved byte LSW(index). */
s32 _swByteGet(s32 index) {
    return gp->lsw[index];
}
