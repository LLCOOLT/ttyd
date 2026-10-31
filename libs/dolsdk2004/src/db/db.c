#include <dolphin/base/PPCArch.h>
#include <dolphin/db.h>
#include <dolphin/os.h>

u8 DBStack[0x1000];
/** Top of DBStack, the stack the debugger exception handler runs on (8 bytes below the end of the array). */
u8* DBStackEnd = DBStack + (sizeof(DBStack) - 8);
BOOL DBVerbose;
DBInterface* __DBInterface;

/**
 * Sets up the debugger interface block at physical address 0x40 (low memory shared with a host debugger),
 * points its exception destination at __DBExceptionDestination and turns on verbose mode.
 */
void DBInit(void) {
    __DBInterface = OSPhysicalToCached(0x40);
    __DBInterface->ExceptionDestination = (void *)OSCachedToPhysical(__DBExceptionDestination);
    DBVerbose = TRUE;
}

/** Returns the "debugger present" flag the host debugger writes into the interface block, or FALSE before DBInit. */
BOOL DBIsDebuggerPresent(void) {
    if (__DBInterface == NULL)
        return FALSE;
    return __DBInterface->bPresent;
}

/**
 * C part of the exception destination: takes the saved OSContext whose physical address is stored at 0xC0,
 * prints "DBExceptionDestination" and the register dump, then halts the CPU with PPCHalt.
 */
void __DBExceptionDestinationAux(void) {
    u32* contextAddr;
    OSContext* context;

    contextAddr = (void*)0xC0;
    context = OSPhysicalToCached(*contextAddr);
    OSReport("DBExceptionDestination\n");
    OSDumpContext(context);
    PPCHalt();
}

/**
 * Exception entry installed in the interface block:
 * sets two MSR bits (0x30, data and instruction address translation) and jumps to __DBExceptionDestinationAux.
 * Original assembly.
 */
asm void __DBExceptionDestination(void) {
    nofralloc
    mfmsr r3
    ori r3, r3, 0x30
    mtmsr r3
    b __DBExceptionDestinationAux
}

/**
 * Returns nonzero if the given exception number is flagged in the interface block's exception mask (marking it
 * as handled by the debugger).
 */
BOOL __DBIsExceptionMarked(__OSException exception) {
    u32 mask = (1 << exception);
    return __DBInterface->exceptionMask & mask;
}

/** Sets or clears the given exception number's bit in the interface block's exception mask. */
void __DBMarkException(__OSException exception, int value) {
    u32 mask = (1 << exception);

    if (value != 0)
        __DBInterface->exceptionMask = __DBInterface->exceptionMask | mask;
    else
        __DBInterface->exceptionMask = __DBInterface->exceptionMask & ~mask;
}

/** Writes the "debugger present" flag in the interface block. */
void __DBSetPresent(u32 value) {
    __DBInterface->bPresent = value;
}

/** Debug print that does nothing in this build. */
void DBPrintf(char* str, ...) {}
