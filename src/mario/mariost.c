// Game start-up and the main loop: marioStInit initialises every driver, marioStMain/marioStDisp run them each
// frame; also the DVD error check thread and the rumble check.
#include "mario/mariost.h"

#include "battle/battle.h"

#include "driver/animdrv.h"
#include "driver/arcdrv.h"
#include "driver/bgdrv.h"
#include "driver/camdrv.h"
#include "driver/casedrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "driver/envdrv.h"
#include "driver/extdrv.h"
#include "driver/fadedrv.h"
#include "driver/hitdrv.h"
#include "driver/icondrv.h"
#include "driver/imgdrv.h"
#include "driver/itemdrv.h"
#include "driver/lightdrv.h"
#include "driver/mapdrv.h"
#include "driver/mobjdrv.h"
#include "driver/msgdrv.h"
#include "driver/npcdrv.h"
#include "driver/offscreendrv.h"
#include "driver/seqdrv.h"
#include "driver/shadowdrv.h"
#include "driver/swdrv.h"
#include "driver/windowdrv.h"

#include "evt/evt_badgeshop.h"
#include "evt/evt_johoya.h"
#include "evt/evt_yuugijou.h"

#include "mario/mario.h"

#include "manager/arammgr.h"
#include "manager/cardmgr.h"
#include "manager/dvdmgr.h"
#include "manager/evtmgr.h"
#include "manager/filemgr.h"
#include "manager/fontmgr.h"
#include "manager/winmgr.h"

#include "sdk/DEMOInit.h"

#include "win/win_main.h"

#include "countdown.h"
#include "sound.h"
#include "error_handler.h"
#include "memory.h"
#include "nameent.h"
#include "pmario_sound.h"
#include "romfont.h"
#include "statuswindow.h"
#include "system.h"

#include <dolphin/vi.h>
#include <string.h>
#include <demo/DEMOPad.h>
#include "version.h"

#define OSIsRestart() ((OSGetResetCode() & 0x80000000) ? TRUE : FALSE)

//.bss
GlobalWork marioSt;
OSThread DvdCheckThread;

//.sdata
GlobalWork* gp = &marioSt;

//.sbss
OSTime none_key;
s32 _mariostSystemLevel;
#if VERSION >= VERSION_US
BOOL R_bReset; // before DvdCheckTreadOn: .sbss is emitted in reverse
#endif
BOOL DvdCheckTreadOn;

//.data
#if VERSION == VERSION_EU
// PAL: the plain modes are 50Hz PAL interlaced, the _prog / Prog ones EURGB60 interlaced
/** Video mode of the boot logo screens (448 lines, 50Hz): seq_logo sets it on a cold start or restart. */
GXRenderModeObj sRMObjHReso = {
    VI_TVMODE_PAL_INT, //viTVmode
    0x260, //fbWidth
    0x1C0, //efbHeight
    0x212, //xfbHeight
    0x1B, //viXOrigin
    0x16, //viYOrigin
    0x29A, //viWidth
    0x212, //viHeight
    VI_XFBMODE_DF, //xFBmode
    0, //field_rendering
    0, //aa
    6, 6, 6, 6, 6, 6, //pix 0
    6, 6, 6, 6, 6, 6, //pix 1
    6, 6, 6, 6, 6, 6, //pix 2
    6, 6, 6, 6, 6, 6, //pix 3
    8, 8, 10, 12, 10, 8, 8, //vfilter
};

/** Video mode of the boot logo screens in 60Hz mode (EURGB60), set by seq_logo after a hot reset. */
GXRenderModeObj sRMObjHReso_prog = {
    VI_TVMODE_EURGB60_INT, //viTVmode
    0x260, //fbWidth
    0x1C0, //efbHeight
    0x1C0, //xfbHeight
    0x1B, //viXOrigin
    0x10, //viYOrigin
    0x29A, //viWidth
    0x1C0, //viHeight
    VI_XFBMODE_DF, //xFBmode
    0, //field_rendering
    0, //aa
    6, 6, 6, 6, 6, 6, //pix 0
    6, 6, 6, 6, 6, 6, //pix 1
    6, 6, 6, 6, 6, 6, //pix 2
    6, 6, 6, 6, 6, 6, //pix 3
    8, 8, 10, 12, 10, 8, 8, //vfilter
};

/** The game's main video mode (50Hz PAL, interlaced): marioStInit starts the game with it. */
GXRenderModeObj GXNtsc480IntDfMarioSt = {
    VI_TVMODE_PAL_INT, //viTVmode
    0x260, //fbWidth
    0x1E0, //efbHeight
    0x238, //xfbHeight
    0x1E, //viXOrigin
    0x6, //viYOrigin
    0x294, //viWidth
    0x238, //viHeight
    VI_XFBMODE_DF, //xFBmode
    0, //field_rendering
    0, //aa
    6, 6, 6, 6, 6, 6, //pix 0
    6, 6, 6, 6, 6, 6, //pix 1
    6, 6, 6, 6, 6, 6, //pix 2
    6, 6, 6, 6, 6, 6, //pix 3
    8, 8, 10, 12, 10, 8, 8, //vfilter
};

/** The game's main video mode in 60Hz (EURGB60), used by marioStInit after a hot reset. */
GXRenderModeObj GXNtsc480ProgMarioSt = {
    VI_TVMODE_EURGB60_INT, //viTVmode
    0x260, //fbWidth
    0x1E0, //efbHeight
    0x1E0, //xfbHeight
    0x1E, //viXOrigin
    0x0, //viYOrigin
    0x294, //viWidth
    0x1E0, //viHeight
    VI_XFBMODE_DF, //xFBmode
    0, //field_rendering
    0, //aa
    6, 6, 6, 6, 6, 6, //pix 0
    6, 6, 6, 6, 6, 6, //pix 1
    6, 6, 6, 6, 6, 6, //pix 2
    6, 6, 6, 6, 6, 6, //pix 3
    8, 8, 10, 12, 10, 8, 8, //vfilter
};
#else
/** Video mode of the boot logo screens (448 lines, interlaced): seq_logo sets it on a cold start or restart. */
GXRenderModeObj sRMObjHReso = {
    VI_TVMODE_NTSC_INT, //viTVmode
    0x260, //fbWidth
    0x1C0, //efbHeight
    0x1C0, //xfbHeight
    0x1B, //viXOrigin
    0x10, //viYOrigin
    0x29A, //viWidth
    0x1C0, //viHeight
    VI_XFBMODE_DF, //xFBmode
    0, //field_rendering
    0, //aa
    6, 6, 6, 6, 6, 6, //pix 0
    6, 6, 6, 6, 6, 6, //pix 1
    6, 6, 6, 6, 6, 6, //pix 2
    6, 6, 6, 6, 6, 6, //pix 3
    8, 8, 10, 12, 10, 8, 8, //vfilter
};

/** Video mode of the boot logo screens in progressive scan, set by seq_logo after a hot reset. */
GXRenderModeObj sRMObjHReso_prog = {
    VI_TVMODE_NTSC_PROG, //viTVmode
    0x260, //fbWidth
    0x1C0, //efbHeight
    0x1C0, //xfbHeight
    0x1B, //viXOrigin
    0x10, //viYOrigin
    0x29A, //viWidth
    0x1C0, //viHeight
    VI_XFBMODE_SF, //xFBmode
    0, //field_rendering
    0, //aa
    6, 6, 6, 6, 6, 6, //pix 0
    6, 6, 6, 6, 6, 6, //pix 1
    6, 6, 6, 6, 6, 6, //pix 2
    6, 6, 6, 6, 6, 6, //pix 3
    8, 8, 10, 12, 10, 8, 8, //vfilter
};

/** The game's main video mode (480 lines, interlaced): marioStInit starts the game with it. */
GXRenderModeObj GXNtsc480IntDfMarioSt = {
    VI_TVMODE_NTSC_INT, //viTVmode
    0x260, //fbWidth
    0x1E0, //efbHeight
    0x1E0, //xfbHeight
    0x1E, //viXOrigin
    0x0, //viYOrigin
    0x294, //viWidth
    0x1E0, //viHeight
    VI_XFBMODE_DF, //xFBmode
    0, //field_rendering
    0, //aa
    6, 6, 6, 6, 6, 6, //pix 0
    6, 6, 6, 6, 6, 6, //pix 1
    6, 6, 6, 6, 6, 6, //pix 2
    6, 6, 6, 6, 6, 6, //pix 3
    8, 8, 10, 12, 10, 8, 8, //vfilter
};

/** The game's main video mode in progressive scan, used by marioStInit after a hot reset. */
GXRenderModeObj GXNtsc480ProgMarioSt = {
    VI_TVMODE_NTSC_PROG, //viTVmode
    0x260, //fbWidth
    0x1E0, //efbHeight
    0x1E0, //xfbHeight
    0x1E, //viXOrigin
    0x0, //viYOrigin
    0x294, //viWidth
    0x1E0, //viHeight
    VI_XFBMODE_SF, //xFBmode
    0, //field_rendering
    0, //aa
    6, 6, 6, 6, 6, 6, //pix 0
    6, 6, 6, 6, 6, 6, //pix 1
    6, 6, 6, 6, 6, 6, //pix 2
    6, 6, 6, 6, 6, 6, //pix 3
    8, 8, 10, 12, 10, 8, 8, //vfilter
};
#endif

// local prototypes
static void viPostCallback(u32 retraceCount);
static void* gcDvdCheckThread(void* param);
void gcRumbleCheck(void);
#if VERSION <= VERSION_DEMO_US
static inline void L_gcResetCheck(void);
#else
void L_gcResetCheck(void);
#endif

/**
 * Start-up.
 * The demos have no error handler (they turn on the SDK's DVD fatal message instead),
 * show English (US demo) or Japanese (JP demo) text whatever the console font,
 * set flag 4 on a restart and always set flag 0x1000.
 */
void marioStInit(void) {
    static u8 stack[0x1000];
    // the releases also start cold after a shutdown reset
    if (!OSIsRestart()
#if VERSION >= VERSION_JP
        || (OSGetResetCode() & OS_RESET_SHUTDOWN)
#endif
    ) {
        DEMOInit(&GXNtsc480IntDfMarioSt);
    } else {
        switch (OSGetResetCode() & OS_RESET_HOTRESET) {
            case 0:
                DEMOInit(&GXNtsc480IntDfMarioSt);
                break;
            case 1:
                DEMOInit(&GXNtsc480ProgMarioSt);
                break;
        }
    }
    DEMOEnableGPHangWorkaround(5);
#if VERSION >= VERSION_JP
    N_setupErrorHandler();
#endif
    DEMOPadInit();
#if VERSION <= VERSION_DEMO_US
    DVDSetAutoFatalMessaging(TRUE); // the demo has no error handler: the SDK shows the DVD error message
#endif
    GXSetCopyClear((GXColor){0, 0, 0, 0}, 0xFFFFFF);
    __GXSetIndirectMask(0);
    memset(gp, 0, sizeof(GlobalWork));
    gp->fbWidth = DEMOGetRenderModeObj()->fbWidth;
    gp->efbHeight = DEMOGetRenderModeObj()->efbHeight;
#if VERSION <= VERSION_DEMO_US
    if (OSIsRestart()) {
        gp->flags |= GLOBAL_FLAG_VIDEO_MODE_SET;
    }
    gp->flags |= GLOBAL_FLAG_KIOSK;
#endif
    gp->rumbleEnabled = 1;
    gp->soundMode = 0;

    gp->retraceLocalTime = 0;
    gp->retraceDeltaTime = 0;
    gp->retraceTime = OSGetTime();

    gp->renderFieldTime = 0;
    gp->renderTime = 0;

    gp->systemLv3Time = 0;
    gp->systemLv2Time = 0;
    gp->systemLv1Time = 0;
    gp->systemLv0Time = 0;

    gp->mapFadeOutType = FADE_IN_BLACK;
    gp->mapFadeOutDuration = 300;
    gp->mapFadeInType = FADE_OUT_BLACK;
    gp->mapFadeInDuration = 300;
    gp->areaFadeOutType = FADE_IN_BLACK;
    gp->areaFadeOutDuration = 300;
    gp->areaFadeInType = FADE_OUT_BLACK;
    gp->areaFadeInDuration = 300;
#if VERSION == VERSION_EU
    if (VIGetTvFormat() == VI_NTSC)
        gp->framerate = 60;
    else if (VIGetTvFormat() == VI_EURGB60)
        gp->framerate = 60;
    else
        gp->framerate = 50;
    if ((OSGetFontEncode() == OS_FONT_ENCODE_SJIS) && !(gp->flags & GLOBAL_FLAG_KIOSK)) {
        gp->language = 0;
    } else {
        // game language: 1 English, 2 German, 3 French, 4 Spanish, 5 Italian
        gp->language = 1;
        switch (OSGetLanguage()) {
            case OS_LANG_ENGLISH:
                gp->language = 1;
                break;
            case OS_LANG_GERMAN:
                gp->language = 2;
                break;
            case OS_LANG_FRENCH:
                gp->language = 3;
                break;
            case OS_LANG_SPANISH:
                gp->language = 4;
                break;
            case OS_LANG_ITALIAN:
                gp->language = 5;
                break;
            case OS_LANG_DUTCH:
                gp->language = 1;
                break;
        }
    }
#elif VERSION >= VERSION_US
    if (VIGetTvFormat() == 0)
        gp->framerate = 60;
    else
        gp->framerate = 50;
    gp->language = 1;
#elif VERSION <= VERSION_DEMO_US
#if VERSION == VERSION_DEMO_JP
    gp->language = 0; // Japanese text whatever the console font
#else
    gp->language = 1; // English text whatever the console font
#endif
    gp->framerate = 60;
#else
    if ((OSGetFontEncode() == OS_FONT_ENCODE_SJIS) && !(gp->flags & GLOBAL_FLAG_KIOSK)) {
        gp->language = 0;
    } else {
        gp->language = 1;
    }
    gp->framerate = 60;
#endif
    gp->systemLevelFlags = 0;
    badgeShop_init(); // Badge Shop
    yuugijou_init();  // Pianta Parlor
    johoya_init();    // information seller
#if VERSION >= VERSION_US
    gp->mapAlloc = __memAlloc(HEAP_DEFAULT, 670 * 1024);
#else
    gp->mapAlloc = __memAlloc(HEAP_DEFAULT, 660 * 1024);
#endif
    VISetPostRetraceCallback(viPostCallback);
    romFontInit();
    OSCreateThread(&DvdCheckThread, gcDvdCheckThread, NULL, stack + sizeof(stack), sizeof(stack), 16, OS_THREAD_ATTR_DETACH);
    DvdCheckTreadOn = TRUE;
    OSResumeThread(&DvdCheckThread);
    DVDMgrInit();
    psndInit();
    aramMgrInit();
    fileInit();
    smartInit();
    dispInit();
    camInit();
    fontmgrInit();
    windowInit();
    mapInit();
    hitInit();
    itemInit();
    iconInit();
    fadeInit();
    bgInit();
    shadowInit();
    evtmgrInit();
    animInit();
    msgInit();
    npcInit();
    mobjInit();
    effInit();
    marioInit();
    caseInit();
    imgInit();
    lightInit();
    offscreenInit();
    arcInit();
    extInit();
    swInit();
    cardInit();
    winInit();
    statusWinInit();
    envInit();
    countDownInit();
    nameEntInit();
    winMgrInit();
    seqInit_MARIOSTORY();
    seqSetSeq(SEQ_LOGO, NULL, NULL);
    gp->soundMode = 0;
    if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
        SoundSetOutputMode(0);
    } else {
        SoundSetOutputMode(1);
    }
#if VERSION <= VERSION_DEMO_US
    none_key = OSGetTime();
#endif
}

/**
 * One frame of game logic, called from the main loop in main.c:
 * waits out a disc error, reads the pads, then runs every system's per-frame update in a fixed order
 * and checks for a reset.
 * In kiosk builds it also watches for idle pads
 * and raises GLOBAL_FLAG_KIOSK_TIMEOUT (the demos reset outside the field and battle instead).
 */
void marioStMain(void) {
    int i;

    while (gp->dvdError) {
        OSYieldThread();
    }
    makeKey();
    seqMain();
    cardMain();
    bgMain();
    shadowMain();
    animMain();
    battleMain();
    camMain();
    windowMain();
    mapMain();
    hitMain();
    evtmgrMain();
    mapDisp();
    marioMain();
    mobjMain();
    npcMain();
    fadeMain();
    imgMain();
    lightMain();
    offscreenMain();
    itemMain();
    caseMain();
    iconMain();
    extMain();
    psndMain();
    winMain();
    statusWinMain();
    envMain();
    countDownMain();
    nameEntMain();
    winMgrMain();
    effMain();
    L_gcResetCheck();
    if (gp->flags & GLOBAL_FLAG_KIOSK) {
        for (i = 0; i < 4; i++) {
            if (gp->dirs[i])
                break;
            if (gp->button[i])
                break;
            if (gp->stickX[i])
                break;
            if (gp->stickY[i])
                break;
            if (gp->substickX[i])
                break;
            if (gp->substickY[i])
                break;
            if (gp->triggerLeft[i])
                break;
            if (gp->triggerRight[i])
                break;
        }
        if (i >= 4) {
#if VERSION <= VERSION_DEMO_US
            // After a minute without input: in the field or in battle, raise the kiosk timeout flag
            // (seq_game and seq_battle then end the session through SEQ_GAME_OVER in kiosk mode);
            // anywhere else, reset the game. The US demo restarts the idle timer after raising the flag.
            if (OSTicksToSeconds(OSGetTime() - none_key) > 60) {
                if (seqGetSeq() == SEQ_GAME || seqGetSeq() == SEQ_BATTLE) {
                    gp->flags |= GLOBAL_FLAG_KIOSK_TIMEOUT;
#if VERSION == VERSION_DEMO_US
                    none_key = OSGetTime();
#endif
                } else {
                    gp->resetType = 1;
                }
            }
#else
            // After two minutes without input in the field or in battle, raise the kiosk timeout flag
            // (only read in kiosk mode, by seq_game and seq_battle).
            if (OSTicksToSeconds(OSGetTime() - none_key) > 120 && (seqGetSeq() == SEQ_GAME || seqGetSeq() == SEQ_BATTLE)) {
                gp->flags |= GLOBAL_FLAG_KIOSK_TIMEOUT;
            }
#endif
        } else {
            none_key = OSGetTime();
        }
    }
}

/** Draws the frame through the camera list (camDraw) and clears g_bFirstSmartAlloc after the first drawn frame. */
void marioStDisp(void) {
    camDraw();
    g_bFirstSmartAlloc = FALSE;
}

/**
 * Sets how much of the game is paused, 0 (nothing) to 4 (everything):
 * each level sets the matching low bits of gp->systemLevelFlags, which stop that level's play-time clock,
 * and stops or restarts events by type mask.
 * Used by item pickups (itemdrv.c), map objects (evt_mobj.c) and the evt_lecture script command.
 */
void marioStSystemLevel(s32 level) {
    switch (level) {
        case 0:
            _mariostSystemLevel = level;
            gp->systemLevelFlags &= ~0xF;
            evtStartAll(0xEF);
            break;
        case 1:
            _mariostSystemLevel = level;
            gp->systemLevelFlags &= ~0xE;
            gp->systemLevelFlags |= 1;
            evtStopAll(1);
            break;
        case 2:
            _mariostSystemLevel = level;
            gp->systemLevelFlags &= ~0xC;
            gp->systemLevelFlags |= 3;
            evtStopAll(2);
            break;
        case 3:
            _mariostSystemLevel = level;
            gp->systemLevelFlags &= ~8;
            gp->systemLevelFlags |= 7;
            evtStopAll(0x10);
            break;
        case 4:
            _mariostSystemLevel = level;
            gp->systemLevelFlags |= 0xF;
            evtStopAll(0xEF);
            break;
    }
}

/**
 * Returns the paused-level bit mask (gp->systemLevelFlags), not the level number;
 * 0 means the game is running freely.
 */
u32 marioStGetSystemLevel(void) {
    return gp->systemLevelFlags;
}

/**
 * Runs after every vertical retrace: advances the play-time clocks (each stops while its system level is
 * paused), records the retrace count, watches the console's Reset button
 * and the B+X+Start soft reset (held 0.5 s), then services rumble and the sound driver.
 * JP and later also reset when the drive reports a fatal status.
 */
static void viPostCallback(u32 retraceCount) {
    OSTime time;
    u32 reset = PAD_BUTTON_B | PAD_BUTTON_X | PAD_BUTTON_START;

    time = OSGetTime();
    gp->retraceDeltaTime = time - gp->retraceTime;
    gp->retraceLocalTime += gp->retraceDeltaTime;
    if (gp->retraceLocalTime > (OS_TIMER_CLOCK * (OSTime)359999999)) {
        gp->retraceLocalTime = (OS_TIMER_CLOCK * (OSTime)359999999);
    }
    // US and PAL also stop the system-level clocks during a disc error or while a window is open
#if VERSION >= VERSION_US
    if (!gp->dvdError && !winCheck()) {
        if (!(gp->systemLevelFlags & 8)) {
            gp->systemLv3Time += gp->retraceDeltaTime;
        }
        if (!(gp->systemLevelFlags & 4)) {
            gp->systemLv2Time += gp->retraceDeltaTime;
        }
        if (!(gp->systemLevelFlags & 2)) {
            gp->systemLv1Time += gp->retraceDeltaTime;
        }
        if (!(gp->systemLevelFlags & 1)) {
            gp->systemLv0Time += gp->retraceDeltaTime;
        }
        gp->renderTime += gp->retraceDeltaTime;
        if (!gp->inBattle) {
            gp->renderFieldTime += gp->retraceDeltaTime;
        }
    }
#else
    if (!(gp->systemLevelFlags & 8)) {
        gp->systemLv3Time += gp->retraceDeltaTime;
    }
    if (!(gp->systemLevelFlags & 4)) {
        gp->systemLv2Time += gp->retraceDeltaTime;
    }
    if (!(gp->systemLevelFlags & 2)) {
        gp->systemLv1Time += gp->retraceDeltaTime;
    }
    if (!(gp->systemLevelFlags & 1)) {
        gp->systemLv0Time += gp->retraceDeltaTime;
    }
    if (!gp->dvdError && !winCheck()) {
        gp->renderTime += gp->retraceDeltaTime;
        if (!gp->inBattle) {
            gp->renderFieldTime += gp->retraceDeltaTime;
        }
    }
#endif
    gp->retraceTime = time;
    gp->retraceCount = retraceCount;
    if (battleDisableHResetCheck()) {
        gp->resetButtonDown = FALSE;
    } else {
        if (!gp->resetButtonDown) {
            if (OSGetResetButtonState()) {
                gp->resetButtonDown = TRUE;
            }
        } else {
            if (!OSGetResetButtonState()) {
                gp->resetType = 1;
            }
        }
        if (gp->keyDataValid) {
            if (OSIsRestart() && !gp->restartChecked) {
                if ((keyGetButton(0) & reset) == reset) {
                    gp->resetType = 0;
                    goto exitcheck;
                } else {
                    gp->restartChecked = TRUE;
                }
            }
            if ((keyGetButton(0) & reset) == reset) {
                if (!gp->softResetWait) {
                    gp->softResetWait = TRUE;
                    gp->softResetTimeout = OSGetTime();
                }
                if (OSTicksToMilliseconds(OSGetTime() - gp->softResetTimeout) > 500) {
                    gp->resetType = 1;
                }
            } else {
                gp->softResetWait = FALSE;
            }
#if VERSION >= VERSION_JP
            if (DVDGetDriveStatus() == -1) {
                gp->resetType = 0;
            }
#endif
        }
    }
exitcheck:
    gcRumbleCheck();
    psndMainInt();
}

/**
 * Background thread started by marioStInit that polls the disc drive:
 * on cover open, no or wrong disc, retry or fatal error it sets gp->dvdError,
 * mutes sound and draws the ROM-font error message on its own, until the drive recovers.
 * US and PAL wait until the status has been steady for 10 frames before drawing.
 */
static void* gcDvdCheckThread(void* param) {
#if VERSION >= VERSION_US
    s32 prevStatus = 0;
    s32 stableCount = 0;
    u32 prevRetrace = 0;
#endif
    const char* message;
    s32 msgId;
    s32 width;
    f32 xpos;
    Mtx44 mtx;

    while (1) {
        msgId = 0;
        switch (DVDGetDriveStatus()) {
            case DVD_STATE_COVER_OPEN:
#if VERSION >= VERSION_US
                msgId = 10;
#else
                msgId = 5;
#endif
                gp->dvdError = TRUE;
                break;
            case DVD_STATE_NO_DISK:
#if VERSION >= VERSION_US
                msgId = 11;
#else
                msgId = 6;
#endif
                gp->dvdError = TRUE;
                break;
            case DVD_STATE_WRONG_DISK:
#if VERSION >= VERSION_US
                msgId = 11;
#else
                msgId = 6;
#endif
                gp->dvdError = TRUE;
                break;
            case DVD_STATE_RETRY:
#if VERSION >= VERSION_US
                msgId = 12;
#else
                msgId = 7;
#endif
                gp->dvdError = TRUE;
                break;
#if VERSION <= VERSION_DEMO_US
            // The demo has no message for a fatal error and leaves dvdError as it is.
            case DVD_RESULT_FATAL_ERROR:
                break;
#else
            case DVD_RESULT_FATAL_ERROR:
#if VERSION >= VERSION_US
                msgId = 13;
#else
                msgId = 8;
#endif
                gp->dvdError = TRUE;
                break;
#endif
            default:
                gp->dvdError = FALSE;
                break;
            case DVD_STATE_BUSY:
                break;
        }
#if VERSION >= VERSION_US
        if (DVDGetDriveStatus() != prevStatus) {
            prevStatus = DVDGetDriveStatus();
            stableCount = 0;
        } else if (VIGetRetraceCount() != prevRetrace) {
            prevRetrace = VIGetRetraceCount();
            stableCount++;
            if (stableCount > 100) {
                stableCount = 100;
            }
        }
#endif
        if (gp->dvdError) {
            SoundOpenCover();
        } else {
            SoundCloseCover();
        }
#if VERSION >= VERSION_JP
        if (gp->dvdError) {
            if (cardIsExec()) {
                gp->dvdError = FALSE;
            }
        }
#endif
#if VERSION >= VERSION_US
        if (gp->dvdError && stableCount > 10) {
#else
        if (gp->dvdError) {
#endif
            DEMOBeforeRender();
#if VERSION <= VERSION_DEMO_US
            // The demo draws the message at 0.8 scale, centred at height 0.
            if (msgId) {
                message = romFontGetMessage(msgId);
                width = 0.8f * romFontGetWidth(message);
                MTXPerspective(mtx, 25.0f, 1.2666667f, 1.0f, 10000.0f);
                GXSetProjection(mtx, GX_PERSPECTIVE);
                xpos = -width / 2.0f;
                romFontPrintGX(xpos, 0.0f, 0.8f, &(GXColor){0xFF, 0xFF, 0xFF, 0xFF}, message);
            }
#else
            if (msgId) {
                message = romFontGetMessage(msgId);
                width = (f32)romFontGetWidth(message);
                MTXPerspective(mtx, 25.0f, 1.2666667f, 1.0f, 10000.0f);
                GXSetProjection(mtx, GX_PERSPECTIVE);
                xpos = -width / 2.0f;
                romFontPrintGX(xpos, 60.0f, 1.0f, &(GXColor){0xFF, 0xFF, 0xFF, 0xFF}, message);
            }
#endif
            DEMODoneRender();
            makeKey();
            L_gcResetCheck();
        }
        OSYieldThread();
    }
}

/**
 * Rumble safety, run from viPostCallback: forces a pad's motor off for 30 seconds
 * after 30 seconds of continuous rumble, and hard-stops all rumble during a disc error or
 * while the game is paused at any system level.
 */
void gcRumbleCheck(void) {
    static BOOL off_trg[4] = {FALSE, FALSE, FALSE, FALSE};
    static OSTime off_time[4] = {0, 0, 0, 0};
    OSTime now;
    OSTime diff;
    BOOL array[4] = {0};
    int i;

    now = OSGetTime();
    for (i = 0; i < 4; i++) {
        if (!gp->rumbleForcedOff[i]) {
            if (padGetRumbleStatus(i) == 1) {
                if (!gp->rumbleStart[i]) {
                    gp->rumbleStart[i] = TRUE;
                    gp->rumbleStartTime[i] = now;
                }
                diff = (s32)now - (s32)gp->rumbleStartTime[i];
                if (OSTicksToMilliseconds(diff) > 30000) {
                    if (!gp->rumbleForcedOffLatch[i]) {
                        gp->rumbleForcedOffLatch[i] = TRUE;
                        gp->rumbleForcedOff[i] = TRUE;
                        gp->rumbleForcedOffTime[i] = now;
                    }
                }
                off_trg[i] = FALSE;
            } else if (gp->rumbleStart[i]) {
                if (!off_trg[i]) {
                    off_trg[i] = TRUE;
                    off_time[i] = now;
                }
                if (off_trg[i]) {
                    diff = (s32)now - (s32)off_time[i];
                    if (OSTicksToMilliseconds(diff) > 100) {
                        off_trg[i] = FALSE;
                        gp->rumbleStart[i] = FALSE;
                    }
                }
            }
        } else {
            diff = (s32)now - (s32)gp->rumbleForcedOffTime[i];
            if (OSTicksToMilliseconds(diff) > 30000) {
                gp->rumbleForcedOffLatch[i] = FALSE;
                gp->rumbleForcedOff[i] = FALSE;
                gp->rumbleStart[i] = FALSE;
            }
            array[i] = TRUE;
        }
        if (gp->dvdError) {
            array[i] = TRUE;
        }
        if (gp->systemLevelFlags != 0U) {
            array[i] = TRUE;
        }
        if (array[i]) {
            gp->rumbleHardStop[i] = TRUE;
        } else {
            gp->rumbleHardStop[i] = FALSE;
        }
    }
}

#if VERSION <= VERSION_DEMO_US
/**
 * The demos inline the reset check into its callers (the US demo also logs the reset);
 * their restart codes are only RESTART and HOTRESET.
 */
static inline void L_gcResetCheck(void) {
    u32 code;

    if (gp->resetType) {
#if VERSION == VERSION_DEMO_US
        OSReport("\x83\x8A\x83\x5A\x83\x62\x83\x67\x8F\x88\x97\x9D\x8A\x4A\x8E\x6E\n");
#endif
        VISetBlack(TRUE);
        VIFlush();
        VIWaitForRetrace();
        VIWaitForRetrace();
        VIWaitForRetrace();
        psndExit();
        DVDMgrDelete();
        if (DvdCheckTreadOn) {
            OSCancelThread(&DvdCheckThread);
            DvdCheckTreadOn = FALSE;
        }
        while (cardIsExec()) {
            cardMain();
            VIWaitForRetrace();
        }
        if (gp->resetType != 2) {
            if (!(gp->flags & GLOBAL_FLAG_VIDEO_MODE_SET)) {
                code = OS_RESET_RESTART;
            } else {
                if (!(gp->flags & GLOBAL_FLAG_PROGRESSIVE)) {
                    code = OS_RESET_RESTART;
                } else {
                    code = OS_RESET_HOTRESET;
                }
            }
            OSResetSystem(OS_RESET_RESTART, code, FALSE);
        } else {
            OSResetSystem(OS_RESET_HOTRESET, 0, TRUE);
        }
        while (1) {}
    }
}
#else
// FAKE: keeps the following function(s) out of line as in the target; removing it changes the code
#pragma dont_inline on
/**
 * Performs a requested reset (gp->resetType): blanks the screen, stops sound,
 * the disc thread and pending memory card work, then restarts the console.
 * Type 2 hot-resets to the IPL menu; otherwise the restart code carries the video mode (and, in US and PAL, the
 * language). US and PAL also wait for card access to finish first.
 */
void L_gcResetCheck(void) {
    u32 code;

#if VERSION >= VERSION_US
    if ((gp->resetType || R_bReset) && (R_bReset = TRUE, !cardIsExec())) {
#else
    if (gp->resetType) {
#endif
        VISetBlack(TRUE);
        VIFlush();
        VIWaitForRetrace();
        VIWaitForRetrace();
        VIWaitForRetrace();
        psndExit();
        DVDMgrDelete();
        if ((OSGetCurrentThread() != &DvdCheckThread) && DvdCheckTreadOn) {
            OSCancelThread(&DvdCheckThread);
            DvdCheckTreadOn = FALSE;
        }
        while (cardIsExec()) {
            cardMain();
            VIWaitForRetrace();
        }
        if (gp->resetType != 2) {
            if (!(gp->flags & GLOBAL_FLAG_VIDEO_MODE_SET)) {
                code = OS_RESET_SHUTDOWN;
            } else {
                if (!(gp->flags & GLOBAL_FLAG_PROGRESSIVE)) {
                    code = OS_RESET_RESTART;
                } else {
                    code = OS_RESET_HOTRESET;
                }
            }
#if VERSION >= VERSION_US
            code |= gp->language << 2;
#endif
            OSResetSystem(OS_RESET_RESTART, code, FALSE);
        } else {
            OSResetSystem(OS_RESET_HOTRESET, 0, TRUE);
        }
        while (1) {}
    }
}
#pragma dont_inline reset
#endif
