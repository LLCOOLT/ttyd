// mariost.c: the global work struct (GlobalWork, gp), its GLOBAL_FLAG_* bits and the main loop entry points.
#pragma once

#include <dolphin/os.h>
#include "driver/fadedrv.h"
#include "driver/npcdrv.h"
#include "evt/evt_lottery.h"
#include "countdown.h"

// GlobalWork.flags bits named so far. 0x40 is still raw: no C code sets it; gor_03's debug_event clears it and
// aji_11's peach_evt_stg5 sets Peach's condition when it is on (scripts read the flags with evt_sub_get_system_flag).
typedef enum GlobalWorkFlags {
    GLOBAL_FLAG_LOADED = 0x1,           // set when a save is loaded (seq_load), cleared when the game is saved (cardmgr); BGM dips keep their flag 0x40
    GLOBAL_FLAG_SKIP_MAP_EVENTS = 0x2,  // nothing in the game sets it (presumably a debug switch): map init scripts take a debug path (gor_10/11/12, jon,
                                        // kpa_04/06, pik_00, rsh_01/02/06, tou_01/03/05/06) and evt_bero enters by the first entrance when no entrance
                                        // is named; title, seq_game exit, seq_e3 and saving clear it
    GLOBAL_FLAG_VIDEO_MODE_SET = 0x4,   // the progressive/interlaced choice is made (seq_logo; the demo sets it on a restart)
    GLOBAL_FLAG_PROGRESSIVE = 0x8,      // progressive scan chosen: a reset goes through OS_RESET_HOTRESET to keep it
    GLOBAL_FLAG_CURTAIN_OPEN = 0x10,    // seq_game opens the next map with the stage-curtain fade (maku_spread), then clears it; set by the sys REL's `start` (rels/sys/src/sys.c)
    GLOBAL_FLAG_SAVE_BLOCKS_OFF = 0x20, // save blocks do nothing (set by seq_e3, the show build)
    GLOBAL_FLAG_KIOSK = 0x1000,         // show/kiosk build (the demo's marioStInit, seq_e3): kiosk timeout, English text
    // Kiosk timeout, despite the name: set by marioStMain after 60 s (demo) or 120 s (retail) without input in SEQ_GAME or
    // SEQ_BATTLE (the demo resets instead in any other sequence), and by seq_e3's play-time alarm. Only kiosk mode
    // (GLOBAL_FLAG_KIOSK) acts on it: seq_game and seq_battle clear it and go to SEQ_GAME_OVER. No attract demo is played.
    GLOBAL_FLAG_KIOSK_TIMEOUT = 0x2000,
    GLOBAL_FLAG_NO_LETTER_BOX = 0x8000 // nothing in the game sets it (presumably a debug switch): camLetterBoxDraw skips the letter box
} GlobalWorkFlags;

// GlobalWork.systemLevelFlags bits. marioStSystemLevel(n) sets the low n bits; each one stops one play-time clock.
enum SystemLevelFlags {
    SYSTEM_LEVEL_FLAG_STOP_LV0 = 0x1,   // systemLv0Time stops (level 1 and up)
    SYSTEM_LEVEL_FLAG_STOP_LV1 = 0x2,   // systemLv1Time stops (level 2 and up)
    SYSTEM_LEVEL_FLAG_STOP_LV2 = 0x4,   // systemLv2Time stops (level 3 and up)
    SYSTEM_LEVEL_FLAG_STOP_LV3 = 0x8,   // systemLv3Time stops (level 4)
    SYSTEM_LEVEL_FLAG_NO_BATTLE = 0x10, // Mario is launched by a jump stand or spring (evt_mario, evt_mobj): a field battle does not start; seq_game clears it
};

typedef struct GlobalWork {
    s32 flags;                      // 0x0, GlobalWorkFlags
    s32 framerate;                  // 0x4
    s32 debugFlag;                  // 0x8
    s32 debugBattle;                // 0xC
    BOOL dvdError;                  // 0x10
    s32 inBattle;                   // 0x14, verified s32
    s32 systemLevelFlags;           // 0x18
    u32 retraceCount;               // 0x1C
    OSTime retraceLocalTime;        // 0x20
    OSTime retraceDeltaTime;        // 0x28
    OSTime retraceTime;             // 0x30
    OSTime renderTime;              // 0x38, time since boot, minus menus
    OSTime renderFieldTime;         // 0x40, time outside battle, minus menus
    OSTime systemLv0Time;           // 0x48
    OSTime systemLv1Time;           // 0x50
    OSTime systemLv2Time;           // 0x58
    OSTime systemLv3Time;           // 0x60
    CountdownWork countdown;        // 0x68
    lottery_info lotteryInfo;       // 0xA8
    u8 pad_E8[0xF8 - 0xE8];         // 0xE8
    FadeType mapFadeOutType;        // 0xF8
    s32 mapFadeOutDuration;         // 0xFC
    FadeType mapFadeInType;         // 0x100
    s32 mapFadeInDuration;          // 0x104
    FadeType areaFadeOutType;       // 0x108
    s32 areaFadeOutDuration;        // 0x10C
    FadeType areaFadeInType;        // 0x110
    s32 areaFadeInDuration;         // 0x114
    BOOL didAreaChange;             // 0x118
    char beroEnterName[0x10];       // 0x11C
    char currentMapName[0x10];      // 0x12C
    char currentAreaName[0x20];     // 0x13C
    void* relocationBase;           // 0x15C
    void* mapAlloc;                 // 0x160
    s32 mapEventId;                 // 0x164, map init event id (seq_mapchange.c)
    FieldBattleData* fbatData;      // 0x168
    s32 language;                   // 0x16C
    u16 fbWidth;                    // 0x170
    u16 efbHeight;                  // 0x172
    s32 gsw0;                       // 0x174
    u32 gswf[0x100];                // 0x178, global saved work flags (GSWF)
    u8 gsw[0x800];                  // 0x578
    u32 lswf[0x10];                 // 0xD78
    u8 lsw[0x400];                  // 0xDB8
    s32 lastSlot;                   // 0x11B8, last used save slot, start cursor on load screen
    u8 playerName[0x11D0 - 0x11BC]; // 0x11BC
    s32 saveSlot;                   // 0x11D0
    Vec savePlayerPos;              // 0x11D4
    s32 savePartyId[2];             // 0x11E0
    OSTime saveTime;                // 0x11E8
    s32 saveCount;                  // 0x11F0
    u8 pad_11F4[0x1274 - 0x11F4];   // 0x11F4
    s32 soundMode;                  // 0x1274
    s32 resetType;                  // 0x1278, 0 = no reset, 1 = soft reset, 2 = menu
    BOOL resetButtonDown;           // 0x127C, reset button was down (mariost.c)
    BOOL softResetWait;             // 0x1280
    u8 pad_1284[0x1288 - 0x1284];   // 0x1284
    OSTime softResetTimeout;        // 0x1288
    BOOL restartChecked;            // 0x1290, restart reset-combo check done
    BOOL rumbleEnabled;             // 0x1294, rumble option, 0 = off
    u8 pad_1298[0x12C0 - 0x1298];   // 0x1298
    u8 rumbleStart[4];              // 0x12C0
    u8 pad_12C4[4];                 // 0x12C4
    OSTime rumbleStartTime[4];      // 0x12C8
    u8 rumbleForcedOff[4];          // 0x12E8, rumble cut after 30 s
    u8 rumbleForcedOffLatch[4];     // 0x12EC, rumble cut latch
    OSTime rumbleForcedOffTime[4];  // 0x12F0, time rumble was cut
    u8 rumbleHardStop[4];           // 0x1310, stop motor hard (PADControlMotor 2)
    OSTick deltaGame;               // 0x1314
    OSTick deltaRender;             // 0x1318
    u8 pad_131C[0x1324 - 0x131C];   // 0x131C
    // system.c "key" controller data
    BOOL keyDataValid;        // 0x1324, key data valid (system.c)
    u32 button[4];            // 0x1328
    u32 buttonNew[4];         // 0x1338
    u32 buttonRepeat[4];      // 0x1348
    u32 buttonRepeatDelay[4]; // 0x1358,
    u32 buttonUp[4];          // 0x1368
    u32 dirs[4];              // 0x1378
    u32 dirsNew[4];           // 0x1388
    u32 dirsRepeat[4];        // 0x1398
    u32 dirsRepeatDelay[4];   // 0x13A8
    s8 stickX[4];             // 0x13B8
    s8 stickY[4];             // 0x13BC
    s8 substickX[4];          // 0x13C0
    s8 substickY[4];          // 0x13C4
    u8 triggerLeft[4];        // 0x13C8
    u8 triggerRight[4];       // 0x13CC
    u8 rumbleStatus[4];       // 0x13D0
    u8 prevRumbleStatus[4];   // 0x13D4
} GlobalWork;
extern GlobalWork* gp;

void marioStInit(void);
void marioStMain(void);
void marioStDisp(void);
void marioStSystemLevel(s32 level);
u32 marioStGetSystemLevel(void);

extern GXRenderModeObj GXNtsc480IntDfMarioSt;
extern GXRenderModeObj GXNtsc480ProgMarioSt;
extern s32 _mariostSystemLevel;
extern GXRenderModeObj sRMObjHReso;
extern GXRenderModeObj sRMObjHReso_prog;
