#include <stdlib.h>
#include <dolphin.h>
#include <dolphin/os.h>

#include "__os.h"

__declspec(section ".ctors") extern void (* _ctors[])();
__declspec(section ".dtors") extern void (* _dtors[])();

static void __init_cpp(void);
static void __fini_cpp(void);

__declspec(section ".init") asm void __init_hardware(void)
{ // clang-format off
    nofralloc
    mfmsr r0
    ori  r0,r0,MSR_FP
    mtmsr r0
    mflr    r31
    bl      __OSPSInit
    bl      __OSFPRInit
    bl      __OSCacheInit
    mtlr    r31
    blr
}

__declspec(section ".init") asm void __flush_cache(void *address, unsigned int size)
{ // clang-format off
    nofralloc
    lis     r5, 0xffff
    ori     r5, r5, 0xfff1
    and     r5, r5, r3
    subf    r3, r5, r3
    add     r4, r4, r3
rept:
    dcbst   0,r5
    sync
    icbi    0,r5
    addic   r5,r5,0x8
    subic.  r4,r4,0x8
    bge     rept
    isync
    blr
}

/** User-level start-up hook called from __start before main; here it only runs the C++ static constructors. */
void __init_user(void) {
    __init_cpp();
}

/** Calls every function in the _ctors table (C++ static constructors) in order. */
static void __init_cpp(void) {
	void (* * constructor)();

	/*
	 *	call static initializers
	 */
	for (constructor = _ctors; *constructor; constructor++) {
		(*constructor)();
	}
}

/** Calls every function in the _dtors table (C++ static destructors); run from exit. */
static void __fini_cpp(void) {
    void (* * destructor)();

	/*
	 *	call destructors
	 */
    for (destructor = _dtors; *destructor; destructor++) {
        (*destructor)();
    }
}

__declspec(weak)
/** Standard C abort: ends the program through _ExitProcess. */
void abort(void) {
    _ExitProcess();
}

__declspec(weak)
/**
 * Standard C exit: runs the static destructors and then ends the program through _ExitProcess.
 * Weak, so a program can override it.
 */
void exit(int status) {
    __fini_cpp();
    _ExitProcess();
}

/** Halts the processor with PPCHalt; nothing returns from here. */
void _ExitProcess(void) {
    PPCHalt();
}
