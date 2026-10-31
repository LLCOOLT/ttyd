#include <dolphin.h>
#include <dolphin/os.h>

#include "__os.h"

static void* SaveStart;
static void* SaveEnd;

/**
 * Restarts into a DOL on the disc: disables interrupts, fixes the arena at 0x81280000-0x812F0000,
 * clears the current context and calls __OSBootDol with the reset code tagged with 0x80000000.
 */
void __OSReboot(u32 resetCode, u32 bootDol) {
    OSContext exceptionContext;
    char* argvToPass;

	OSDisableInterrupts();
    OSSetArenaLo((void*)0x81280000);
    OSSetArenaHi((void*)0x812f0000);
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    argvToPass = NULL;
    __OSBootDol(bootDol, resetCode | 0x80000000, &argvToPass);
}

/**
 * Registers a memory range that the next boot should leave untouched (for example,
 * data to hand to the program booted next).
 */
void OSSetSaveRegion(void* start, void* end) {
    ASSERTMSGLINE(134, (u32)start >= 0x80700000 || start == NULL, "OSSetSaveRegion(): start address should be NULL or higher than 0x80700000\n");
    ASSERTMSGLINE(135, 0x81200000 >= (u32)end || end == NULL, "OSSetSaveRegion(): end address should be NULL or lower than 0x81200000\n");
    ASSERTMSGLINE(136, ((start == NULL) ^ (end == NULL)) == 0, "OSSetSaveRegion(): if either start or end is NULL, both should be NULL\n");

    SaveStart = start;
    SaveEnd = end;
}

/** Returns the range registered with OSSetSaveRegion. */
void OSGetSaveRegion(void** start, void** end) {
    *start = SaveStart;
    *end = SaveEnd;
}

/**
 * Returns the range that the previous program asked to keep,
 * as stored in the reboot parameters this program was started with.
 */
void OSGetSavedRegion(void** start, void** end) {
    *start = __OSRebootParams.regionStart;
    *end = __OSRebootParams.regionEnd;
}
