#include <dolphin.h>
#include <dolphin/os.h>

#include "__os.h"
#include "__dvd.h"

extern volatile u32 BOOT_REGION_START AT_ADDRESS(0x812FDFF0);
extern volatile u32 BOOT_REGION_END AT_ADDRESS(0x812FDFEC);
extern volatile u8 g_unk_800030E2 AT_ADDRESS(0x800030E2);

static int Prepared;

/**
 * Builds the 0x2000-byte argument block a launched DOL reads:
 * argument strings packed at the end, then the argv pointer list (as offsets within the block) and argc,
 * with the offset of argc stored at +8.
 */
static int PackArgs(void* addr, s32 argc, char** argv) {
    s32 numArgs;
    char* bootInfo2;
    char* ptr;
    char** list;
    u32 i;

    bootInfo2 = (char*)addr;
    memset(bootInfo2, 0, 0x2000);

    if (argc == 0) {
        *(u32*)(bootInfo2 + 8) = 0;
    } else {
        numArgs = argc;
        ptr = bootInfo2 + 0x2000;
        while (--argc >= 0) {
            ptr -= strlen(argv[argc]) + 1;
            strcpy(ptr, argv[argc]);
            argv[argc] = (char*)(ptr - bootInfo2);
        }

        ptr = bootInfo2 + ((ptr - bootInfo2) & ~0x3);
        ptr -= ((numArgs + 1) * 4);
        list = (char**)ptr;

        for (i = 0; i < numArgs + 1; i++) {
            list[i] = argv[i];
        }

        ptr -= 4;
        *(u32*)ptr = numArgs;

        ASSERTMSGLINE(LINE(129, 138, 140), ptr - bootInfo2 >= 0x1000U, "OSExec: Argument list is too long");

        *(u32*)(bootInfo2 + 8) = (ptr - bootInfo2);
    }

    return 1;
}

/** Assembly: invalidates the instruction cache and jumps to the entry point (it never returns). */
#ifdef __GEKKO__
static asm void Run(register void* entryPoint) {
    nofralloc

    mflr r0
    stw r0, 4(r1)
    stwu r1, -0x18(r1)
    stw r31, 0x14(r1)
    mr r31, entryPoint
    bl ICFlashInvalidate
    sync
    isync 
    mtlr r31
    blr

    lwz r0, 0x1c(r1)
    lwz r31, 0x14(r1)
    addi r1, r1, 0x18
    mtlr r0
    blr
}
#endif

/**
 * Stores the exec parameters in the arena, writes 7 to PI register 9,
 * disables interrupts and jumps to the loaded DOL's entry point.
 */
static void StartDol(const OSExecParams* params, void* entry) {
    OSExecParams* paramsWork = OSAllocFromArenaLo(sizeof(OSExecParams), 1);

    __OSSetExecParams(params, paramsWork);
    __PIRegs[9] = 7;

    OSDisableInterrupts();
    Run(entry);
}

/**
 * Reads length bytes at a disc offset into memory with an asynchronous DVD read, polling until it finishes;
 * if the disc is removed it triggers a hot reset.
 */
static void ReadDisc(void* addr, s32 length, s32 offset) {
    DVDCommandBlock block;
#if SDK_REVISION < 1
    OSTime start;
#endif

    DVDReadAbsAsyncPrio(&block, addr, length, offset, NULL, 0);

#if SDK_REVISION < 1    
    start = OSGetTime();
#endif

    while (DVDGetCommandBlockStatus(&block)) {
#if SDK_REVISION < 1
        if (!DVDCheckDisk() || OS_TIMER_CLOCK < (OSGetTime() - start))
#else
        if (!DVDCheckDisk())
#endif
        {
            __OSDoHotReset(0);
        }
    }
}

/** DVD callback for __DVDPrepareResetAsync; sets Prepared so __OSBootDolSimple knows the drive is ready. */
static void Callback(s32, DVDCommandBlock*) {
    Prepared = TRUE;
}

/** Returns whether the current disc's ID has audio streaming enabled. */
static int IsStreamEnabled() {
    if (DVDGetCurrentDiskID()->streaming) {
        return TRUE;
    }

    return FALSE;
}

/**
 * Copies the exec parameters left by the previous program into the caller's structure,
 * or marks it invalid if none were stored.
 */
void __OSGetExecParams(OSExecParams* params) {
    if (0x80000000 <= (u32)__OSExecParams) {
        memcpy(params, __OSExecParams, sizeof(OSExecParams));
    } else {
        params->valid = FALSE;
    }
}

/** Copies exec parameters to addr and remembers that address in low memory for the next program to find. */
void __OSSetExecParams(const OSExecParams* params, OSExecParams* addr) {
    memcpy(addr, params, sizeof(OSExecParams));
    __OSExecParams = addr;
}

/**
 * If the disc has audio streaming on (and this is not an arcade board), mutes the AI stream,
 * cancels the DVD stream and stops AI stream playback so the drive is free to load a program.
 */
static void StopStreaming() {
    DVDCommandBlock block;
#if SDK_REVISION < 1
    OSTime start;
#endif

    if (!__OSIsGcam && IsStreamEnabled()) {
        AISetStreamVolLeft(0);
        AISetStreamVolRight(0);
        DVDCancelStreamAsync(&block, NULL);

#if SDK_REVISION < 1
        start = OSGetTime();
#endif

        while (DVDGetCommandBlockStatus(&block)) {
#if SDK_REVISION < 1
            if (!DVDCheckDisk() || OS_TIMER_CLOCK < (OSGetTime() - start))
#else
            if (!DVDCheckDisk())
#endif
            {
                __OSDoHotReset(0);
            }
        }

        AISetStreamPlayState(0);
    }
}

/**
 * Returns the disc offset of the apploader: 0x2440 on a normal disc, or, for a TGC image,
 * the apploader offset in its TGC header plus the image offset. Cached after the first call.
 */
static int GetApploaderPosition(void) {
    static s32 apploaderPosition;

    u32* tgcHeader;
    s32 apploaderOffsetInTGC;

    if (apploaderPosition != 0) {
        return apploaderPosition;
    }

    if (__OSAppLoaderOffset != 0) {
        tgcHeader = OSAllocFromArenaLo(0x40, DOLPHIN_ALIGNMENT);
        ReadDisc(tgcHeader, 0x40, __OSAppLoaderOffset);
        apploaderOffsetInTGC = tgcHeader[14];
        ASSERTMSGLINE(LINE(370, 376, 378), apploaderOffsetInTGC != 0, "OSExec() or OSResetSystem(): Wrong apploader offset. Maybe converted by an\nolder version of gcm2tgc. Use gcm2tgc v.1.20 or later.");

        apploaderPosition = __OSAppLoaderOffset + apploaderOffsetInTGC;
    } else {
        apploaderPosition = 0x2440;
    }
    return apploaderPosition;
}

typedef struct {
    char date[16];
    u32 entry;
    u32 size;
    u32 rebootSize;
    u32 reserved2;
} AppLoaderStruct;

/**
 * Reads the apploader header from the disc, loads its body to 0x81200000,
 * invalidates the instruction cache there and returns the header.
 */
static AppLoaderStruct* LoadApploader() {
    AppLoaderStruct* header;

    header = (AppLoaderStruct*)OSAllocFromArenaLo(sizeof(AppLoaderStruct), DOLPHIN_ALIGNMENT);
    ReadDisc(header, sizeof(AppLoaderStruct), GetApploaderPosition());
    ASSERTMSGLINE(LINE(401, 407, 409), header->rebootSize != 0, "OSResetSystem(): old apploader");

    ReadDisc((void*)0x81200000, OSRoundUp32B(header->size), GetApploaderPosition() + 0x20);
    ICInvalidateRange((void*)0x81200000, OSRoundUp32B(header->size));
    return header;
}

/**
 * Gets the apploader's init, get-next and get-entry callbacks, saves the exec parameters, runs init,
 * then reads every chunk of the DOL that the apploader asks for and returns the DOL entry point.
 */
static void* LoadDol(const OSExecParams* params, AppLoaderCallback getInterface) {
    appInitCallback appInit;
    appGetNextCallback appGetNext;
    appGetEntryCallback appGetEntry;
    void* addr;
    u32 length;
    u32 offset;
    OSExecParams* paramsWork;

    getInterface(&appInit, &appGetNext, &appGetEntry);
    paramsWork = (OSExecParams*)OSAllocFromArenaLo(sizeof(OSExecParams), 1);
    __OSSetExecParams(params, paramsWork);
    appInit((void(*)(char*))OSReport);
    OSSetArenaLo(paramsWork);

    while (appGetNext(&addr, &length, &offset) != 0) {
        ReadDisc(addr, length, offset);
    }

    return appGetEntry();
}

/**
 * Returns whether the apploader's build date is later than 2004/02/01;
 * newer apploaders can load the DOL themselves.
 */
static BOOL IsNewApploader(AppLoaderStruct* header) {
    return strncmp(header->date, "2004/02/01", 10) > 0 ? TRUE : FALSE;
}

/**
 * Quits the running program and boots a DOL from the disc:
 * prepares the DVD drive, stops audio streaming,
 * loads the apploader and starts the DOL at the given offset (-1 means just after the apploader),
 * passing the restart code, preserved memory region and arguments.
 * With an older apploader it loads a reboot stub to 0x81300000 and jumps there.
 */
void __OSBootDolSimple(u32 doloffset, u32 restartCode, void* regionStart, void* regionEnd, BOOL argsUseDefault, s32 argc, char** argv) {
    OSExecParams* params;
    void* dolEntry;
    AppLoaderStruct* header;

#if SDK_REVISION < 1
    OSTime start;
#endif

    OSDisableInterrupts();
    params = (OSExecParams*)OSAllocFromArenaLo(sizeof(OSExecParams), 1);
    params->valid = TRUE;
    params->restartCode = restartCode;
    params->regionStart = regionStart;
    params->regionEnd = regionEnd;
    params->argsUseDefault = argsUseDefault;

    if (!argsUseDefault) {
        params->argsAddr = OSAllocFromArenaLo(0x2000, 1);
        PackArgs(params->argsAddr, argc, argv);
    }

    DVDInit();
    DVDSetAutoInvalidation(TRUE);
    DVDResume();

    Prepared = FALSE;

    __DVDPrepareResetAsync(Callback);
    __OSMaskInterrupts(0xFFFFFFE0);
    __OSUnmaskInterrupts(0x400);
    OSEnableInterrupts();

#if SDK_REVISION < 1
    start = OSGetTime();
#endif

    while (Prepared != TRUE) {
#if SDK_REVISION < 1
        if (!DVDCheckDisk() || OS_TIMER_CLOCK < (OSGetTime() - start))
#else
        if (!DVDCheckDisk())
#endif
        {
            __OSDoHotReset(0);
        }
    }

    StopStreaming();

    header = LoadApploader();
    if (IsNewApploader(header)) {
        if (doloffset == 0xFFFFFFFF) {
            doloffset = (GetApploaderPosition() + 0x20) + header->size;
        }

        params->bootDol = doloffset;
        dolEntry = LoadDol(params, (AppLoaderCallback)header->entry);
        StartDol(params, dolEntry);
    } else {
        BOOT_REGION_START = (u32)regionStart;
        BOOT_REGION_END = (u32)regionEnd;
        g_unk_800030E2 = 1;

        ReadDisc((void*)0x81300000, OSRoundUp32B(header->rebootSize), (GetApploaderPosition() + 0x20) + header->size);
        ICInvalidateRange((void*)0x81300000, OSRoundUp32B(header->rebootSize));
        OSDisableInterrupts();
        ICFlashInvalidate();
        Run((void*)0x81300000);
    }
}

/**
 * Boots a DOL by disc offset: passes the offset as argv[0] followed by the given arguments,
 * with the saved memory region, to __OSBootDolSimple.
 */
void __OSBootDol(u32 doloffset, u32 restartCode, const char** argv) {
    char doloffInString[20];
    s32 argvlen;
    char** argvToPass;
    s32 i;
    void* saveStart;
    void* saveEnd;

    OSGetSaveRegion(&saveStart, &saveEnd);
    sprintf(doloffInString, "%d", doloffset);
    argvlen = 0;

    if (argv != 0) {
        while (argv[argvlen] != 0) {
            argvlen++;
        }
    }

    argvlen++;
    argvToPass = OSAllocFromArenaLo((argvlen + 1) * 4, 1);
    *argvToPass = doloffInString;

    for (i = 1; i < argvlen; i++) {
        argvToPass[i] = (char*)argv[i - 1];
    }

    __OSBootDolSimple(-1, restartCode, saveStart, saveEnd, FALSE, argvlen, argvToPass);
}

/**
 * Opens the named DOL file on the disc (an empty name means disc offset 0)
 * and boots it with restart code 0xC0000000; returns quietly if the file cannot be opened.
 */
static void ExecCommon(const char* dolfile, const char** argv) {
    DVDFileInfo fileInfo;
    u32 doloff;

    if ((s8)*dolfile == '\0') {
        doloff = 0;
    } else if (DVDOpen((char*)dolfile, &fileInfo)) {
        doloff = fileInfo.startAddr;
    } else {
        ASSERTMSGLINE(LINE(689, 695, 697), 0, "OSExec(): The specified file doesn't exist");
        return;
    }

    __OSBootDol(doloff, 0xC0000000, argv);
}

/**
 * Launches another DOL from the disc with an argument vector:
 * shuts the devices down, resets the arena to a fixed range at 0x81280000 and boots it.
 */
void OSExecv(const char* dolfile, const char** argv) {
    ASSERTMSGLINE(LINE(718, 724, 726), dolfile != 0, "OSExecv(): null pointer was specified for the dol file name.");
    ASSERTMSGLINE(LINE(719, 725, 727), argv != 0, "OSExecv(): null pointer was specified for argv.");

    OSDisableScheduler();
    __OSShutdownDevices(FALSE);
    OSEnableScheduler();
    OSSetArenaLo((void*)0x81280000);
    OSSetArenaHi((void*)0x812F0000);
    ExecCommon(dolfile, argv);
}

/**
 * Launches another DOL from the disc with a NULL-terminated list of arguments:
 * shuts devices down, resets the arena, builds the argv and boots it.
 */
void OSExecl(const char* dolfile, const char* arg0, ...) {
    va_list vl;
    char* ptr;
    s32 i;
    char** argv;

    ASSERTMSGLINE(LINE(759, 765, 767), dolfile != 0, "OSExecl(): null pointer was specified for the dol file name.");

    OSDisableScheduler();
    __OSShutdownDevices(FALSE);
    OSEnableScheduler();
    OSSetArenaLo((void*)0x81280000);
    OSSetArenaHi((void*)0x812F0000);

    argv = OSAllocFromArenaLo(4, 0x1000);
    va_start(vl, arg0);
#if SDK_REVISION < 2
    *argv = (char*)arg0;

    i = 1;
    do {
        ptr = va_arg(vl, char*);
        argv[i++] = ptr;
    } while (ptr != 0);
#else
    i = 0;
    ptr = (char*)arg0;
    goto setarg;

    do {
        ptr = va_arg(vl, char*);
setarg:
        argv[i++] = ptr;
    } while (ptr != 0);
#endif
    va_end(vl);
    ASSERTMSGLINE(LINE(787, 793, 794), i < 0x400U, "OSExecl(): Arguments too long");

    ExecCommon(dolfile, argv);
}
