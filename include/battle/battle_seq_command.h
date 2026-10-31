// Declares the battle command menu structures (weapon and party tables).
#pragma once

#include <dolphin/types.h>

struct BattleWeapon;

typedef struct BattleCommandCursor {
    s32 absPos; // 0x0, absolute cursor index
    s32 relPos; // 0x4, first visible row
    int count;  // 0x8, number of options
} BattleCursor;

typedef struct BattleCommandAct {
    s32 type;          // 0x0
    s32 enabled;       // 0x4
    const char* name;  // 0x8
    u16 icon;          // 0xC
    s32 disableReason; // 0x10
} BattleCommandAct;

typedef struct BattleCommandWeapon {
    struct BattleWeapon* weapon; // 0x0
    s32 enabled;                 // 0x4
    const char* name;            // 0x8
    u16 icon;                    // 0xC
    s32 index;                   // 0x10
    s32 itemId;                  // 0x14
    s32 disableReason;           // 0x18
} BattleCommandWeapon;

typedef struct BattleCommandOperation {
    s32 type;          // 0x0
    s32 enabled;       // 0x4
    s32 disableReason; // 0x8
    const char* name;  // 0xC
    u16 icon;          // 0x10
    const char* help;  // 0x14
    s32 cost;          // 0x18
} BattleCommandOperation;

typedef struct BattleCommandParty {
    s32 kind;         // 0x0
    s32 enabled;      // 0x4
    const char* name; // 0x8
    u16 icon;         // 0xC
    const char* help; // 0x10
    s16 hp;           // 0x14
    s16 maxHp;        // 0x16
} BattleCommandParty;

typedef struct BattleCommandMultiItem {
    s32 enabled;       // 0x0
    const char* name;  // 0x4
    const char* help;  // 0x8
    u16 icon;          // 0xC
    u8 dipCount;       // 0xE, items used per turn: 1, 2 (Double Dip), 3 (Triple Dip); copied to BattleCommand.dipMode
    s32 cost;          // 0x10
    s32 disableReason; // 0x14
} BattleCommandMultiItem;

typedef struct BattleSubMenu {
    BattleCursor* cursor;         // 0x0
    BattleCommandAct* acts;       // 0x4
    BattleCommandWeapon* weapons; // 0x8
    s32 scrollState;              // 0xC
    s32 scrollTimer;              // 0x10, reset with each new scrollState; never advanced (rowTimer drives the scroll)
    u8 shown;                     // 0x14
    s32 prevAbsPos;               // 0x18
    s32 iconsArrived;             // 0x1C
    s32 iconFlags[5];             // 0x20
    s32 iconState[5];             // 0x34
    s32 iconTimer[15];            // 0x48
    s32 iconSlot[5];              // 0x84
    f32 scrollPos;                // 0x98
    f32 scrollFrom;               // 0x9C
    f32 scrollTo;                 // 0xA0
    s32 rowFlags[7];              // 0xA4
    s32 rowState[7];              // 0xC0
    s32 rowTimer[7];              // 0xDC
    s32 reserved_F8[7];           // 0xF8
    u8 reserved_114[8];
    s32 bobTimer;      // 0x11C
    f32 partyBtnAngle; // 0x120
} BattleSubMenu;

// BattleCommand.flags: which command menus are shown (each ...MenuSetup sets its bit, ...MenuEnd clears it).
typedef enum BattleCommandFlags {
    CMD_MENU_FLAG_ACT = 0x1, // the main ring menu
    CMD_MENU_FLAG_WEAPON_SELECT = 0x10,
    CMD_MENU_FLAG_MULTI_ITEM = 0x20, // Double/Triple Dip
    CMD_MENU_FLAG_OPERATION = 0x100, // Tactics
    CMD_MENU_FLAG_CHANGE_PARTY = 0x1000,
    CMD_MENU_FLAG_TARGET_SELECT = 0x10000,
    CMD_MENU_FLAG_PROTECT_PARTNER = 0x100000,
    CMD_MENU_FLAG_SHOW_ALL_ENEMY_HP = 0x1000000, // BattleDrawEnemyHP draws every tattled enemy
} BattleCommandFlags;

typedef struct BattleCommand {
    s32 state;                           // 0x0, command menu state (switch in the main loop)
    s32 flags;                           // 0x4, BattleCommandFlags
    BattleCommandAct act[6];             // 0x8
    BattleCommandWeapon weapon[21];      // 0x80
    BattleCommandOperation operation[7]; // 0x2CC
    BattleCommandParty party[8];         // 0x390
    BattleCommandMultiItem multiItem[3]; // 0x450
    BattleCursor cursor[14];             // 0x498
    s32 actType;                         // 0x540, type of the chosen act (act[cursor].type); 9 on cancel
    s32 prevActType;                     // 0x544, actType saved before it is forced to 12
    s32 operationType;                   // 0x548, BattleCommandOperation.type of the chosen tactic
    s32 partyKind;                       // 0x54C, party kind chosen in the change-partner menu
    u8 dipMode;                          // 0x550, Double/Triple Dip count (2/3), 1 while picking
    u8 cancelled;                        // 0x551, command cancelled: the unit just waits
    s32 recCommand;                      // 0x554, state recorded by _commandRestoreRec (0 = none)
    u8 attackAudience;                   // 0x558, 1: BattleCommandAttackAudienceCheck fired, 2: reset pending
    BattleSubMenu* subMenu;              // 0x55C, battle_menu_disp.c
    s32 idleTimer;                       // 0x560, frames without input; idle camera at 900
    s32 disableReason;                   // 0x564, disableReason of the greyed-out option, picks the error message
    s32 errorEvtId;                      // 0x568, error message event id
    u8 reserved_56C[0x574 - 0x56C];      // 0x56C, never accessed
} BattleCommand;

struct BattleWork;
struct BattleUnit;

void BattleCommandInit(struct BattleWork* wp);
void BattleCommandDisplay(struct BattleWork* wp);
BOOL BattleCommandCheckChangePositionEnable(struct BattleWork* wp);
struct BattleWeapon* BattleGetSelectWeapon(struct BattleWork* wp);
void* BattleSetConfuseAct(struct BattleWork* wp, struct BattleUnit* unit);
s32 BattleCommandInput(void* work);
