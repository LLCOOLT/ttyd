// statuswindow.c: the field HUD of HP, FP, star power, coins and star points (StatusWindowWork).
#pragma once

#include <dolphin/mtx.h>

typedef struct StatusValue {
    s16 hp;         // 0x0
    s16 maxHp;      // 0x2
    s16 fp;         // 0x4
    s16 maxFp;      // 0x6
    s16 party;      // 0x8
    s16 partyHp;    // 0xA
    s16 partyMaxHp; // 0xC
    s16 starPoints; // 0xE
    s16 coins;      // 0x10
    s16 ap;         // 0x12
    s16 maxAp;      // 0x14
    s16 lastParty;  // 0x16, demo: the partner shown while Mario is in bg mode
} StatusValue;

// StatusWindowWork.flags. statusWinOpen/Close set the state bit with its request bit; statusWinMain starts the
// slide when it sees a request bit and clears it.
enum StatusWindowFlags {
    STATUSWIN_FLAG_OPEN = 0x1,             // open (statusWinCheck)
    STATUSWIN_FLAG_CLOSED = 0x2,           // closed
    STATUSWIN_FLAG_OPEN_REQ = 0x4,         // start sliding in (16 frames)
    STATUSWIN_FLAG_CLOSE_REQ = 0x8,        // start sliding out (28 frames)
    STATUSWIN_FLAG_FORCE_OPEN = 0x10,      // statusWinForceOpen: pinned open until statusWinForceOff
    STATUSWIN_FLAG_FORCE_CLOSE = 0x20,     // statusWinForceClose: kept closed until statusWinForceOff
    STATUSWIN_FLAG_FORCE_OPEN_REQ = 0x40,  // start sliding in for a forced open
    STATUSWIN_FLAG_FORCE_CLOSE_REQ = 0x80, // start sliding out for a forced close
    STATUSWIN_FLAG_MENU_HINTS = 0x100,     // the releases draw the menu button hints (opened by Z or idling); cleared once closed
    STATUSWIN_FLAG_DISP_OFF = 0x1000,      // statusWinDispOff: not drawn
};

typedef struct StatusWindowWork {
    u8 pad_0[0x4];    // 0x0
    u16 flags;        // 0x4, StatusWindowFlags
    u8 align_0x6[2];  // 0x6
    f32 timer;        // 0x8
    f32 duration;     // 0xC
    f32 t;            // 0x10
    f32 tStart;       // 0x14
    f32 tEnd;         // 0x18
    f32 speed;        // 0x1C
    f32 x;            // 0x20
    f32 y;            // 0x24
    u8 pad_28[0x8];   // 0x28
    f32 openX;        // 0x30
    f32 openY;        // 0x34
    u8 pad_38[0x8];   // 0x38
    f32 closeX;       // 0x40
    f32 closeY;       // 0x44
    u8 pad_48[0x8];   // 0x48
    StatusValue cur;  // 0x50
    Vec prevPos;      // 0x68
    s32 idle;         // 0x74
    s32 forceTimer;   // 0x78
    s32 forcedClose;  // 0x7C
    s32 blink;        // 0x80
    s32 pendingBlink; // 0x84
    s32 blinkTimer;   // 0x88
} StatusWindowWork;

void statusWinInit(void);
void statusWinReInit(void);
void statusWinMain(void);

void statusWinForceOff(void);
void statusWinForceOpen(void);

void statusWinDispOff(void);
void statusWinDispOn(void);
void statusWinForceUpdate(void);

void statusWinOpen(void);
void statusWinClose(void);
BOOL statusWinCheck(void);
void statusWinForceClose(void);
void statusWinForceCloseClear(void);
BOOL statusWinCheckUpdate(void);
void statusWinForceUpdateCoin(void);
Vec statusGetApPos(void);
void statusAPBlink(s32 frames);
void N_statusClearBlink(void);
void statusFPBlink(s32 frames);
void statusMarioHPBlink(s32 frames);
void statusPartyHPBlink(s32 frames);
