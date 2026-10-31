#include <dolphin.h>
#include <dolphin/ax.h>

#include "__ax.h"

#ifdef DEBUG
const char* __AXVersion = "<< Dolphin SDK - AX\tdebug build: Apr  5 2004 03:56:21 (0x2301) >>";
#else
const char* __AXVersion = "<< Dolphin SDK - AX\trelease build: Apr  5 2004 04:15:05 (0x2301) >>";
#endif

/** Initialises the AX audio library with the default output buffer mode (0). */
void AXInit(void) {
    AXInitEx(0);
}

/**
 * Initialises the AX audio library: registers the SDK version
 * and initialises its modules in turn (voice allocation, voice parameter blocks, studio, auxiliary buses,
 * command list, and the output/DMA buffers with the given buffer mode).
 */
void AXInitEx(u32 outputBufferMode) {
#ifdef DEBUG
    OSReport("Initializing AX\n");
#endif
    OSRegisterVersion(__AXVersion);

    __AXAllocInit();
    __AXVPBInit();
    __AXSPBInit();
    __AXAuxInit();
    __AXClInit();
    __AXOutInit(outputBufferMode);
}

/** Shuts the AX library down by shutting down each module that AXInitEx started. */
void AXQuit(void) {
#ifdef DEBUG
    OSReport("Shutting down AX\n");
#endif
    __AXAllocQuit();
    __AXVPBQuit();
    __AXSPBQuit();
    __AXAuxQuit();
    __AXClQuit();
    __AXOutQuit();
}
