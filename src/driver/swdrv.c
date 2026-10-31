// Saved work driver: the event flags and words kept in the save file: the global ones (GSW/GSWF)
// and the area-local ones (LSW/LSWF).
#include "driver/swdrv.h"
#include "mario/mariost.h"
#include <string.h>

void swInit(void) {
    memset(gp->gswf, 0, sizeof(gp->gswf));
    memset(gp->gsw, 0, sizeof(gp->gsw));
    memset(gp->lswf, 0, sizeof(gp->lswf));
    memset(gp->lsw, 0, sizeof(gp->lsw));
    gp->gsw0 = 0;
}

void swReInit(void) {
    memset(gp->lswf, 0, sizeof(gp->lswf));
    memset(gp->lsw, 0, sizeof(gp->lsw));
}

// Global Saved Work Flags --------------------------------------
void swSet(s32 index) { // set specific bit
    gp->gswf[index / 32] |= (1 << (index % 32));
}

BOOL swGet(s32 index) { // get specific bit
    return (gp->gswf[index / 32] & (1 << (index % 32))) != 0;
}

void swClear(s32 index) { // clear specific bit
    gp->gswf[index / 32] &= ~(1 << (index % 32));
}

// Global Saved Work --------------------------------------------
void swByteSet(s32 index, s32 value) {
    if (index == 0) {
        gp->gsw0 = value;
    } else {
        gp->gsw[index] = (u8)value;
    }
}

s32 swByteGet(s32 index) {
    if (index == 0) {
        return gp->gsw0;
    } else {
        return gp->gsw[index];
    }
}

// Local Saved Work Flags ---------------------------------------
void _swSet(s32 index) { // set specific bit
    gp->lswf[index / 32] |= (1 << (index % 32));
}

BOOL _swGet(s32 index) { // get specific bit
    return (gp->lswf[index / 32] & (1 << (index % 32))) != 0;
}

void _swClear(s32 index) { // clear specific bit
    gp->lswf[index / 32] &= ~(1 << (index % 32));
}

// Local Saved Work ---------------------------------------------
void _swByteSet(s32 index, u8 value) {
    gp->lsw[index] = value;
}

s32 _swByteGet(s32 index) {
    return gp->lsw[index];
}
