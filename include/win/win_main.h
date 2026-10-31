// win_main.c: the pause menu work block shared by win_root and the five pause windows.
#pragma once

#include <dolphin/types.h>
#include "evt/evt_cmd.h"
#include "sdk/texPalette.h"
#include "manager/filemgr.h"
#include "memory.h"
#include "version.h"

// Pause menu work (winGetPtr): one block shared by win_main, win_root and the five pause windows.
// 0x000-0x188 is the menu itself (input, tabs, help text, sort menu); each window keeps its own
// state in its sub-struct after that, in tab order. Windows also read each other's state
// (win_item reads party.count, win_badge rebuilds mario.poseId and log.pose, win_root sorts
// and draws the item, badge and log lists).
//
// The offset comments in the Win*State sub-structs below are WindowWork offsets (not offsets inside the
// sub-struct), for JP. The demo lacks texBuf/texBufValid (0x34-0x3B) and mario.f18C, so its offsets are 8 lower
// from currentEvent and 0xC lower from mario.f190 on. US and PAL add WinLogPage.page, so log.badgeIds and
// log.recipe are 4 higher there and everything after log.recipe is 8 higher.

// Directory of the window files on the disc (format prefix "%s/" is the DVD root); the demo uses "window".
#if VERSION == VERSION_DEMO
#define WIN_DIR "%s/window/"
#else
#define WIN_DIR "%s/w/"
#endif

// Cooked dishes in the recipe log: items WIN_RECIPE_MIN up to ITEM_MAX; log.recipeIds holds item - WIN_RECIPE_MIN.
#define WIN_RECIPE_MIN ITEM_SHROOM_FRY
// Switch set when a dish has been cooked (gor_01 cooking_flag: swSet(item - 114)); the log shows only those.
#define WIN_RECIPE_COOKED_SW(idx) (0x41 + (idx))

typedef struct WinTab {
    s32 id;          // 0x0
    f32 x;           // 0x4
    f32 y;           // 0x8
    s32 state;       // 0xC
    s32 timer;       // 0x10
    const char* msg; // 0x14
} WinTab;

// one per window (mario, party, item, badge, log); each window draws at menu[n].x/y
typedef struct WinMenu {
    s32 id;    // 0x0
    f32 x;     // 0x4
    f32 y;     // 0x8
    s32 state; // 0xC
    s32 timer; // 0x10
} WinMenu;

// sortable u8 pair: mail (receive order, mail id) and tattle log (sort key, enemy id)
typedef struct WinSortEnt {
    u8 kind; // 0x0
    u8 id;   // 0x1
} WinSortEnt;

typedef struct WinBadgeEnt {
    s32 equipped; // 0x0
    s32 idx;      // 0x4
    s32 id;       // 0x8
} WinBadgeEnt;

typedef struct WinMarioState {
    s32 poseId; // 0x188
#if VERSION != VERSION_DEMO
    s32 f18C; // 0x18C, not in the demo
#endif
    s32 f190; // 0x190
    s32 f194; // 0x194
    s32 f198; // 0x198
} WinMarioState;

typedef struct WinPartyState {
    s32 switchRequested;       // 0x19C, A pressed: switch to the selected partner
    s32 poseIds[7];            // 0x1A0
    s32 partyIds[7];           // 0x1BC
    s32 dtIdx;                 // 0x1D8
    s32 cursor;                // 0x1DC
    s32 count;                 // 0x1E0
    f32 angle;                 // 0x1E4
    f32 angleTarget;           // 0x1E8
    u8 pad_1EC[0x1FC - 0x1EC]; // 0x1EC
    s32 openCursor;            // 0x1FC, cursor when the menu opened
    s32 mode;                  // 0x200
    s32 wazaCount;             // 0x204
    s32 wazaCursor;            // 0x208
} WinPartyState;

typedef struct WinItemState {
    s32 state;                 // 0x20C
    s32 mode;                  // 0x210
    s32 cursor[2];             // 0x214
    s32 page[2];               // 0x21C
    f32 scroll[2];             // 0x224
    f32 scrollTgt[2];          // 0x22C
    f32 bookX;                 // 0x234
    f32 bookTgtX;              // 0x238
    f32 bookY;                 // 0x23C
    f32 bookTgtY;              // 0x240
    f32 mailX;                 // 0x244
    f32 mailTgtX;              // 0x248
    f32 mailY;                 // 0x24C
    f32 mailTgtY;              // 0x250
    s32 mailNum;               // 0x254
    s32 mailSel;               // 0x258
    s32 mailPage;              // 0x25C
    f32 mailScroll;            // 0x260
    f32 mailScrollTgt;         // 0x264
    s32 mailLine;              // 0x268
    u16 mailLines;             // 0x26C
    WinSortEnt mail[45];       // 0x26E
    s32 bookIdx;               // 0x2C8, luigi_book_list row
    s32 bookPages;             // 0x2CC
    s32 bookPage;              // 0x2D0
    s32 useItem;               // 0x2D4, item being used (itemUseFunc)
    s32 useIdx;                // 0x2D8, its pouch index
    s32 useTarget;             // 0x2DC, 0 = Mario, else party slot + 1
    s32 blink;                 // 0x2E0
    u8 pad_2E4[0x2E8 - 0x2E4]; // 0x2E4
    s16 skip[121];             // 0x2E8, important-item list (winMakeSkipList)
    s16 skipCount;             // 0x3DA
} WinItemState;

typedef struct WinBadgeState {
    s32 state;             // 0x3DC
    s32 tab;               // 0x3E0
    s32 sel[2];            // 0x3E4
    s32 page[2];           // 0x3EC
    f32 scroll[2];         // 0x3F4
    f32 scrollTgt[2];      // 0x3FC
    WinBadgeEnt list[200]; // 0x404, equipped badges (winMakeEquipList)
    s32 count;             // 0xD64
} WinBadgeState;

// header of one log list page (badge log, recipe log)
typedef struct WinLogPage {
    f32 x;   // 0x0
    f32 tx;  // 0x4
    f32 y;   // 0x8
    f32 ty;  // 0xC
    s32 num; // 0x10
#if VERSION >= VERSION_US
    s32 page; // US only: page shown in the "%d/%d" counter
#endif
    s32 cursor;    // 0x14
    s32 idx;       // 0x18, first row shown
    f32 scroll;    // 0x1C
    f32 scrollTgt; // 0x20
    f32 f24;       // 0x24
    f32 tf24;      // 0x28
    f32 f2C;       // 0x2C
    f32 tf2C;      // 0x30
} WinLogPage;

typedef struct WinLogMenu {
    s32 id;          // 0x0
    f32 x;           // 0x4
    f32 y;           // 0x8
    f32 tx;          // 0xC
    f32 ty;          // 0x10
    s32 state;       // 0x14
    s32 timer;       // 0x18
    const char* msg; // 0x1C
} WinLogMenu;

struct EffectEntry;
struct MonosiriWork;

typedef struct WinLogState {
    s32 fD68;                     // 0xD68
    s32 cursor;                   // 0xD6C
    s32 count;                    // 0xD70
    WinLogMenu menu[5];           // 0xD74
    s32 fE14;                     // 0xE14
    s32 mapIdx;                   // 0xE18
    s32 pose;                     // 0xE1C
    f32 mapX;                     // 0xE20
    f32 mapY;                     // 0xE24
    f32 fE28;                     // 0xE28
    f32 fE2C;                     // 0xE2C
    f32 fE30;                     // 0xE30
    f32 fE34;                     // 0xE34
    f32 scrollX;                  // 0xE38
    f32 scrollY;                  // 0xE3C
    s32 stoneNum;                 // 0xE40
    struct EffectEntry* eff[7];   // 0xE44
    s32 fE60;                     // 0xE60
    f32 fE64;                     // 0xE64
    f32 fE68;                     // 0xE68
    f32 fE6C;                     // 0xE6C
    f32 fE70;                     // 0xE70
    f32 fE74;                     // 0xE74
    f32 fE78;                     // 0xE78
    f32 fE7C;                     // 0xE7C
    f32 fE80;                     // 0xE80
    WinLogPage badge;             // 0xE84
    s16 badgeIds[100];            // 0xEB8, badge item ids - BADGE_MIN
    WinLogPage recipe;            // 0xF80 (US 0xF84)
    s16 recipeIds[58];            // 0xFB4, item ids - WIN_RECIPE_MIN
    f32 f1028;                    // 0x1028
    f32 f102C;                    // 0x102C
    f32 f1030;                    // 0x1030
    f32 f1034;                    // 0x1034
    s32 enemyNum;                 // 0x1038
    s32 enemyKnown;               // 0x103C
    s32 enemySel;                 // 0x1040
    s32 enemyPage;                // 0x1044
    f32 f1048;                    // 0x1048
    f32 f104C;                    // 0x104C
    WinSortEnt enemy[0xD8];       // 0x1050, tattle log
    struct MonosiriWork* mono;    // 0x1200
    u8 pad_1204[0x1208 - 0x1204]; // 0x1204
} WinLogState;

typedef struct WindowWork {
    u16 flags;                // 0x0
    u8 pad_2[2];              // 0x2
    s32 buttonTrg;            // 0x4
    s32 buttonRep;            // 0x8
    s32 dirTrg;               // 0xC
    s32 dirRep;               // 0x10
    s32 lectureStep;          // 0x14
    EventEntry* lectureEvent; // 0x18
    s32 menuSel;              // 0x1C, tab to open on
    s32 menuState;            // 0x20
    s32 active;               // 0x24
    FileEntry* res;           // 0x28, win.tpl
    FileEntry* mailRes;       // 0x2C, mail tpl
    FileEntry* mapRes;        // 0x30, log map tpl
#if VERSION != VERSION_DEMO
    // The demo has no background capture.
    smartEntry* texBuf; // 0x34, background capture texture
    s32 texBufValid;    // 0x38
#endif
    EventEntry* currentEvent; // 0x3C
    s32 tabSel;               // 0x40
    s32 tabNum;               // 0x44
    WinTab tab[5];            // 0x48
    WinMenu menu[5];          // 0xC0
    s32 savedState;           // 0x124, window state kept while the sort menu is up
    f32 msgOfsX;              // 0x128
    f32 msgOfsY;              // 0x12C
    s32 msgState;             // 0x130
    s32 msgTimer;             // 0x134
    s32 msgItem;              // 0x138, item icon id, or -1/-2 for a titled help box
    const char* msg;          // 0x13C
    const char* msgName;      // 0x140, help box title
    const char* lastMsg;      // 0x144
    s32 msgLine;              // 0x148
    s32 msgLines;             // 0x14C
    f32 helpX;                // 0x150
    f32 helpY;                // 0x154
    f32 helpTgtX;             // 0x158
    f32 helpTgtY;             // 0x15C
    s32 marioSel;             // 0x160, win_mario linkDt cursor
    f32 sortPosX;             // 0x164
    f32 sortPosY;             // 0x168
    f32 sortTgtX;             // 0x16C
    f32 sortTgtY;             // 0x170
    s32 sortSel;              // 0x174
    s32 sortNum;              // 0x178
    s32 sortActive;           // 0x17C
    s32 sortRev;              // 0x180
    s32 sortType;             // 0x184
    WinMarioState mario;      // 0x188
    WinPartyState party;      // 0x19C
    WinItemState item;        // 0x20C
    WinBadgeState badge;      // 0x3DC
    WinLogState log;          // 0xD68
    s32 useWin[2];            // 0x1208 (US 0x1210), item use windows (winMgr ids)
} WindowWork;                 // 0x1210 (US 0x1218, demo 0x1204)

struct BattleWeapon;

typedef struct WindowPartyDt {
    s32 partyId;                // 0x0
    s32 nameMsgId;              // 0x4
    const char* name;           // 0x8
    const char* msg;            // 0xC
    const char* poseName;       // 0x10
    const char* animName;       // 0x14
    const char* poseName2;      // 0x18
    const char* animName2;      // 0x1C
    struct BattleWeapon** waza; // 0x20
} WindowPartyDt;                // winPartyDt (win_party.c)

WindowWork* winGetPtr(void);
void winInit(void);
void winReInit(void);
BOOL winCheck(void);
void winOpenEnable(void);
void winOpenDisable(void);
USER_FUNC(itemUseFunc);

void winMain(void);

void winTexInit(TEXPalette* texture);
void winTexSet(u32 textureId, Vec translate, Vec scale, GXColor color);

void winTexSetNearest(u32 textureId, Vec translate, Vec scale, GXColor color);

// pause window helpers (win_root.c)
void winMsgEntry(WindowWork* wp, s32 item, const char* msg, const char* name);
void winBgGX(WindowWork* wp, s32 type, f32 x, f32 y);
void winKirinukiGX(WindowWork* wp, s32 type, f32 x, f32 y, f32 w, f32 h);
void winNameGX(WindowWork* wp, s32 type, f32 x, f32 y, f32 w, f32 h);
void winWazaGX(WindowWork* wp, s32 type, f32 x, f32 y, f32 w, f32 h);
void winKageGX(WindowWork* wp, GXColor color, f32 x, f32 y, f32 z, f32 scale);
void winBookGX(WindowWork* wp, s32 type, f32 x, f32 y);
void winHakoGX(WindowWork* wp, s32 type, f32 x, f32 y);
void winSortEntry(WindowWork* wp, s32 type, f32 x, f32 y);
BOOL winSortWait(WindowWork* wp);

extern const volatile f32 winConstHalf;

BOOL winGhostDiaryChk(void);
void winFontInit(void);
void winFontSet(Vec pos, Vec scale, GXColor color, const char* fmt, ...);
void winFontSetWidth(Vec pos, Vec scale, GXColor color, f32 width, const char* fmt, ...);
void winFontSetR(Vec pos, Vec scale, GXColor color, const char* fmt, ...);
void winFontSetRWidth(Vec pos, Vec scale, GXColor color, f32 width, const char* fmt, ...);
void winFontSetEdge(Vec pos, Vec scale, GXColor color, const char* fmt, ...);
void winFontSetEdgeWidth(Vec pos, Vec scale, GXColor color, f32 width, const char* fmt, ...);
void winFontSetLabel(Vec pos, Vec scale, GXColor color, const char* msg);
void winFontSetPitch(f32 pitch, Vec pos, Vec scale, GXColor color, const char* fmt, ...);
void winTexSetRot(u32 textureId, Vec translate, Vec scale, GXColor color, f32 rot);
void winTexInit_x2(TEXPalette* texture);
void winTexSet_x2(u32 textureId1, u32 textureId2, Vec translate, Vec scale, GXColor color);
void winIconInit(void);
void winIconGrayInit(void);
void winLectureOn(void);
BOOL winLectureCheck(void);
void winIconSet(s32 iconId, Vec translate, Vec scale, GXColor color);
