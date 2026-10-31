// Declares the battle work structure, battle flags and the top-level battle functions.
#pragma once

#include <dolphin/types.h>
#include "battle/battle_ac.h"
#include "battle/battle_audience.h"
#include "battle/battle_break_slot.h"
#include "battle/battle_camera.h"
#include "battle/battle_database_common.h"
#include "battle/battle_icon.h"
#include "battle/battle_information.h"
#include "battle/battle_pad.h"
#include "battle/battle_seq_command.h"
#include "battle/battle_stage.h"
#include "battle/battle_stage_object.h"
#include "battle/battle_unit.h"
#include "battle/battle_seq_end.h"
#include "mario/mario_pouch.h"
#include "version.h"

typedef struct BattleAlliance BattleAlliance;

#define BATTLE_UNIT_MAX 64         // BattleWork.units, movePriorityQueue and phaseEvtTable
#define BATTLE_STAGE_OBJECT_MAX 32 // BattleWork.stageObjects

// BattleWork.flags.
typedef enum BattleFlags {
    BATTLE_FLAG_GUARD_MOVE = 0x1,                // a protecting unit is moving in (btlevtcmd_GuardMoveEnd clears it)
    BATTLE_FLAG_FIRST_ATTACK = 0x2,              // the first-strike sequence; no action-command help
    BATTLE_FLAG_ACT_DECIDED = 0x4,               // the target is confirmed / an action is under way
    BATTLE_FLAG_ESCAPED = 0x10,                  // ends the battle with result 4 (Run Away)
    BATTLE_FLAG_INTERRUPTED = 0x20,              // a script stopped the battle (result 5)
    BATTLE_FLAG_RESET_ABORT = 0x40,              // set with INTERRUPTED by the reset button combination (result 4)
    BATTLE_FLAG_COMMAND_INPUT = 0x80,            // the command menu is open
    BATTLE_FLAG_WIDE_STAGE = 0x100,              // zoomed-out stage (set by Hooktail's script): camera, audience, end camera
    BATTLE_FLAG_SINGLE_JUMP = 0x200,             // Mario has only the basic jump (no weapon sub-menu)
    BATTLE_FLAG_SINGLE_HAMMER = 0x400,           // Mario has only the basic hammer (no weapon sub-menu)
    BATTLE_FLAG_NO_OBJECT_FALL = 0x1000,         // no falling stage objects
    BATTLE_FLAG_RESET_TURN = 0x2000,             // btlevtcmd_reset_turn: end the phase now
    BATTLE_FLAG_SHOW_ALL_STATUS_ICONS = 0x10000, // one frame: status icons drawn with the wider filter; nothing sets it
    BATTLE_FLAG_SHOW_HELD_ITEMS = 0x20000,       // one frame: draw the held items
    BATTLE_FLAG_MAJINAI_END = 0x400000,          // Merlee's spells are used up (_event_MajinaiEnd)
    BATTLE_FLAG_LECTURE_LOCK_ALL = 0x800000,     // tutorial: every command disabled
    BATTLE_FLAG_LECTURE_JUMP = 0x1000000,        // tutorial: only Jump, with the lecture jump weapon
    BATTLE_FLAG_LECTURE_HAMMER = 0x2000000,      // tutorial: no Jump, the lecture hammer weapon
    BATTLE_FLAG_LECTURE_SPECIAL = 0x4000000,     // tutorial: only the Special menu
    BATTLE_FLAG_LECTURE_MENU = 0x8000000,        // tutorial: "lecture end" replaces the operation entry
    BATTLE_FLAG_LECTURE_STEP2 = 0x10000000,      // tutorial: items, Special, operation and lecture end disabled
    BATTLE_FLAG_NO_HARD_RESET = 0x20000000,      // battleDisableHResetCheck
    BATTLE_FLAG_ZERO_GRAVITY = 0x40000000,       // units bob and can't move unless UNIT_ATTR_ACTS_IN_ZERO_GRAVITY
    BATTLE_SEQ_END = 0x80000000                  // BattleMain finished
} BattleFlags;

typedef enum BattleSequence {
    SEQ_UNKNOWN = 0,
    SEQ_INIT = 1,
    SEQ_FIRST_ACT = 2,
    SEQ_TURN = 3,
    SEQ_PHASE = 4,
    SEQ_MOVE = 5,
    SEQ_ACT = 6,
    SEQ_END = 7
} BattleSequence;

// BattleDebugCtrl.flags: debug overrides (read only; nothing in the game sets them).
typedef enum BattleDebugFlags {
    BATTLE_DEBUG_FORCE_OBJECT_FALL = 0x1,
    BATTLE_DEBUG_FORCE_FALL_ON_AUDIENCE = 0x2,
    BATTLE_DEBUG_FORCE_DESTROY_BG_A1 = 0x10,
    BATTLE_DEBUG_FORCE_DESTROY_BG_A2 = 0x20,
    BATTLE_DEBUG_FORCE_DESTROY_BG_B = 0x40,
    BATTLE_DEBUG_FORCE_IRON_FRAME_FALL = 0x80,
    BATTLE_DEBUG_FORCE_NOZZLE_WORK = 0x100,
    BATTLE_DEBUG_FORCE_NOZZLE_TURN = 0x200,
    BATTLE_DEBUG_FORCE_AUDIENCE_NUM = 0x10000, // audienceNum replaces the audience count
    BATTLE_DEBUG_FORCE_AUDIENCE_ITEM_THROW = 0x20000,
    BATTLE_DEBUG_FORCE_RARE_AUDIENCE = 0x40000,
    BATTLE_DEBUG_FORCE_SLOT_ITEM = 0x80000,
} BattleDebugFlags;

// BattleWork.badgeEquippedFlags: badges Mario has on, collected at the start of the battle (BattleInit).
typedef enum BattleBadgeFlags {
    BADGE_FLAG_QUICK_CHANGE = 1 << 0,
    BADGE_FLAG_PEEKABOO = 1 << 1,
    BADGE_FLAG_TIMING_TUTOR = 1 << 2,
    BADGE_FLAG_HEART_FINDER = 1 << 3,
    BADGE_FLAG_FLOWER_FINDER = 1 << 4,
    BADGE_FLAG_MONEY_MONEY = 1 << 7,
    BADGE_FLAG_ATTACK_FX_R = 1 << 8,
    BADGE_FLAG_ATTACK_FX_Y = 1 << 9,
    BADGE_FLAG_ATTACK_FX_B = 1 << 10,
    BADGE_FLAG_ATTACK_FX_G = 1 << 11,
    BADGE_FLAG_ATTACK_FX_P = 1 << 12,
} BattleBadgeFlags;

typedef struct BattleDebugCtrl {
    s32 flags;        // 0x0, BattleDebugFlags
    s32 reserved_04;  // 0x4, never accessed
    s32 reserved_08;  // 0x8, never accessed
    s32 audienceNum;  // 0xC, targetAudienceCount when flags & 0x10000
    s32 audienceKind; // 0x10, 1..: forced audience kind
    s32 slotItem;     // 0x14, item_appear_force when flags & 0x80000
} BattleDebugCtrl;

typedef struct BattleActRecord { // u8 counters for the battle-condition rules (BtlActRec_*)
    u8 marioJumpMoves;           // 0x00, weapon class 0 (cond 1/2)
    u8 marioHammerMoves;         // 0x01, class 1 (cond 3/4)
    u8 marioSpecialAttacks;      // 0x02, class 4, attacking (cond 5/6)
    u8 marioSpecialSupports;     // 0x03, class 4, non-attacking
    u8 marioDamageTaken;         // 0x04, BtlActRec_AddPoint (cond 7/8)
    u8 partnerDamageTaken;       // 0x05, cond 9/10
    u8 marioHitsTaken;           // 0x06, cond 13/14
    u8 partnerHitsTaken;         // 0x07, cond 15/16
    u8 powerBounceCombo;         // 0x08, cond 21
    u8 marioAttackItems;         // 0x09, class 2, attacking (cond 22/23)
    u8 marioSupportItems;        // 0x0A, class 2, non-attacking
    u8 partnerAttackItems;       // 0x0B, cond 24/25
    u8 partnerSupportItems;      // 0x0C
    u8 marioPartyChanges;        // 0x0D, tactics 0 (cond 28/29)
    u8 partnerPartyChanges;      // 0x0E, cond 30/31
    u8 marioAudienceAttacks;     // 0x0F, cond 34/35
    u8 partnerAudienceAttacks;   // 0x10, cond 36/37
    u8 marioAppeals;             // 0x11, tactics 5/7 (cond 38/39)
    u8 partnerAppeals;           // 0x12, cond 40/41
    u8 marioFpSpent;             // 0x13, cond 44/45
    u8 marioFpMoves;             // 0x14, cond 50/51
    u8 partnerFpSpent;           // 0x15, cond 46/47
    u8 partnerFpMoves;           // 0x16, cond 52/53
    u8 marioCharges;             // 0x17, tactics entry 1: Charge
    u8 partnerCharges;           // 0x18
    u8 marioSuperCharges;        // 0x19, tactics entry 2: Super Charge
    u8 partnerSuperCharges;      // 0x1A
    u8 marioEscapes;             // 0x1B, tactics entry 3: Escape
    u8 partnerEscapes;           // 0x1C
    u8 partnerAttackMoves;       // 0x1D, weapon class 6, attacking
    u8 partnerSupportMoves;      // 0x1E, class 6, non-attacking
    u8 turnCount;                // 0x1F, cond 58/59
} BattleActRecord;

typedef struct StChgMsg {
    s8 type;     // 0x0, -1 = free
    u8 flags;    // 0x1
    u8 timer;    // 0x2, frames left on screen; a 0x300 press clears it
    s32 unitId;  // 0x4
    s32 changed; // 0x8, 1: strength changed / newly inflicted (selects msg1), as StChgInfo.changed
} StChgMsg;

typedef struct StChgWork {
    StChgMsg msg[28]; // 0x0
    char text[0x100]; // 0x150
    s32 maskHi;       // 0x250 (BattleAnnounce 0x368): 64-bit message mask, read as s64 (the US BattleAnnounce is only 4-aligned); all set when the luck event starts
    s32 maskLo;       // 0x254
} StChgWork;

typedef struct BattleAnnounce {
    s16 x;         // 0x0
    s16 y;         // 0x2
    s32 params[4]; // 0x4
#if VERSION == VERSION_DEMO || VERSION >= VERSION_US
    char text[0x100]; // 0x14 (US and demo 4 shorter)
#else
    char text[0x104]; // 0x14
#endif
    StChgWork stChg; // 0x118, status-change message queue (battle_status_effect)
} BattleAnnounce;

struct BattleAlliance {
    u16 allianceId;     // 0x0
    s8 attackDirection; // 0x2
    // pad 1 byte
    BOOL clearConditionMet; // 0x4
};

typedef struct BattleWorkPartyInfo {
    f32 sizeMultiplier;        // 0x0, saved BattleUnit.sizeMultiplier
    BtlStatusCopy statusTurns; // 0x4, saved from BattleUnit.sleepTurns
    s32 statusFlags;           // 0x24, saved BattleUnit.statusFlags
#if VERSION >= VERSION_US
    u16 usCommandDisabled[2]; // US only: saved BattleUnit usCommandDisabled
#endif
} BattleWorkPartyInfo;

typedef struct BattleWorkTarget {
    s16 unitIdx;     // 0x0
    s16 partIdx;     // 0x2
    s16 posX;        // 0x4, cursor point (_btlSamplingEnemy)
    s16 posY;        // 0x6
    s16 posZ;        // 0x8
    s32 x;           // 0xC
    s32 y;           // 0x10
    s32 z;           // 0x14
    s32 score;       // 0x18
    u8 forwardLv;    // 0x1C
    s8 side;         // 0x1D
    s32 reserved_20; // 0x20, only set to -1
} BattleWorkTarget;

typedef struct BattleWorkWeaponTargets {
    BattleWeapon* weapon;         // 0x0
    BattleWorkTarget targets[74]; // 0x4
    s8 numTargets;                // 0xA6C
    s8 targetIndices[74];         // 0xA6D
    s8 currentTarget;             // 0xAB7
    s32 unitId;                   // 0xAB8, BattleSamplingEnemy args
    s8 belong;                    // 0xABC
    u32 classFlags;               // 0xAC0
    u32 propFlags;                // 0xAC4
    s8 direction;                 // 0xAC8
} BattleWorkWeaponTargets;

typedef struct BattlePhaseEvtEntry {
    s32 unitId;   // 0x0
    s32 priority; // 0x4
} BattlePhaseEvtEntry;

typedef struct BattleAfterReaction {
    s32 unitId; // 0x0, -1 = free slot
    s32 tag;    // 0x4
} BattleAfterReaction;

struct BattleWork {
    s16 turnCount;                                           // 0x0
    u16 turnSubSeq;                                          // 0x2
    s32 seqUnknownValue;                                     // 0x4
    BattleAlliance alliances[3];                             // 0x8
    BattleUnit* units[BATTLE_UNIT_MAX];                      // 0x20
    s32 movePriorityQueue[BATTLE_UNIT_MAX];                  // 0x120
    BattlePhaseEvtEntry phaseEvtTable[BATTLE_UNIT_MAX];      // 0x220
    s32 activeUnitId;                                        // 0x420
    s32 lectureUnitId;                                       // 0x424, unit id -6 resolves to (_battle_set_lecture_unit_id); its weapons replace the menu weapons, -1 = none
    BattleWorkWeaponTargets weaponTargets;                   // 0x428
    u32 flags;                                               // 0xEF4
    s32 dispFlags;                                           // 0xEF8
    s32 ruleDispTimer;                                       // 0xEFC
    s32 stockExp;                                            // 0xF00, BattleStoreExp/BattleGetStockExp
    s32 stockExpDisp;                                        // 0xF04, counts up to stockExp in BattleStockExpDisp
    s32 stockExpTimer;                                       // 0xF08, frame counter for that count-up
    s32 seqInitValue;                                        // 0xF0C
    s32 seqFirstActValue;                                    // 0xF10
    s32 seqTurnValue;                                        // 0xF14
    s32 seqPhaseValue;                                       // 0xF18
    s32 seqMoveValue;                                        // 0xF1C
    s32 seqActValue;                                         // 0xF20
    s32 seqEndValue;                                         // 0xF24
    BattleSeqEndWork* seqEndWork;                            // 0xF28
    BattleWorkPad padWork[4];                                // 0xF2C
    BattleCommand commandMenu;                               // 0x171C
    BattleActions actionCommands;                            // 0x1C90
    u8 reserved_1F9C[0x271C - 0x1F9C];                       // 0x1F9C, never accessed
    s32 stylishCurFrame;                                     // 0x271C
    s32 stylishWindowStart;                                  // 0x2720
    s32 stylishWindowEnd;                                    // 0x2724
    s32 stylishEndFrame;                                     // 0x2728
    s32 stylishUnitId;                                       // 0x272C
    s32 stylishResult;                                       // 0x2730
    s32 stylishEarlyFrames;                                  // 0x2734
    FieldBattleInfo* fbatInfo;                               // 0x2738
    s32 statusWindowOff;                                     // 0x273C
    s32 lectureMode;                                         // 0x2740
    s32 statusWindowSystemOn;                                // 0x2744, BattleStatusWindowSystemOn/Off
    s32 statusWindowEventOn;                                 // 0x2748, BattleStatusWindowEventOn/Off
    s32 statusWindowAPRecoveryOn;                            // 0x274C, BattleStatusWindowAPRecoveryOn/Off
    s32 reserved_2750;                                       // 0x2750, never accessed
    BattleCameraWork cameraWork;                             // 0x2754
    BattleAudience audience;                                 // 0x2858
    BreakSlotWork breakSlot;                                 // 0x1616C, battle_break_slot.c
    BattleWorkPartyInfo partyInfo[7];                        // 0x162A0
    u32 tattledUnitTypeFlags[8];                             // 0x163B8
    s32 badgeEquippedFlags;                                  // 0x163D8, BattleBadgeFlags
    FileEntry* menuTex;                                      // 0x163DC
    BattleStage stage;                                       // 0x163E0
    BattleActRecord actRecord;                               // 0x16F1C, battle condition counters (battle_actrecord)
    u8 marioAcSuccess;                                       // 0x16F3C
    u8 marioAcFailed;                                        // 0x16F3D
    BattleAfterReaction afterReactions[64];                  // 0x16F40 (US 0x16F5C), BattleAfterReactionEntry/Release/Main queue
    BattleStageObject stageObjects[BATTLE_STAGE_OBJECT_MAX]; // 0x17140
    BattleStageObjectWork stageObjectWork;                   // 0x180C0, battle_stage_object.c
    BattleIcon icons[16];                                    // 0x182B0
    BattleAnnounce announce;                                 // 0x18C70
    s8 alertTick;                                            // 0x18FE0
    u8 majinaiState;                                         // 0x18FE1
    u16 luckTimer;                                           // 0x18FE2
    StarPowerInfo impendingBonuses;                          // 0x18FE4
    const char* acHelpMsg;                                   // 0x18FF0
    s32 acHelpDispType;                                      // 0x18FF4
    u8 reserved_18FF8[0x19038 - 0x18FF8];                    // 0x18FF8, never accessed
#if VERSION >= VERSION_US
    s32 commandDisabled[3]; // US
#else
    s32 commandDisabled[5]; // 0x19038, set to 3 by Bowser's command-blocking attacks
#endif
    s32 luckEventId;       // 0x1904C
    u32 reserveItems[4];   // 0x19050
    s32 curtainSfxId;      // 0x19060
    u8 lastAcSuccess;      // 0x19064 (US 0x19074), 1 after a successful action command (btlevtcmd_ResultACDefence)
    BattleDebugCtrl debug; // 0x19068 (US 0x19078), debug overrides read by the audience and break slot
    u32 lectureFlags;      // 0x19080 (US 0x19090), bit 0 set by the Frankly lecture (aud_attack_init/end); continues msgWindow lectureWindowId
    s32 lectureWindowId;   // 0x19084 (US 0x19094)
};
extern BattleWork* _battleWorkPointer;

void battleMain(void);

void battle_exit(void);
#if VERSION == VERSION_DEMO
void battle_init(void);
#else
BOOL battle_init(void);
#endif
void BattleAfterReactionQueueInit(void);

BattleUnit* BattleGetPartnerPtr(BattleWork* work, BattleUnit* unit);
BattleUnit* BattleGetPartyPtr(BattleWork* wp);
BattleUnit* BattleGetMarioPtr(BattleWork* work);
BattleUnit* BattleGetSystemPtr(BattleWork* work);
BattleUnitPart* BattleGetUnitPartsPtr(s32 index, s32 partNum);
void BattleSetUnitPtr(BattleWork* wp, s32 index, BattleUnit* unit);
BattleUnit* BattleGetUnitPtr(BattleWork* wp, s32 index);
void BattleFree(void* ptr);
void* BattleAlloc(u32 size);
f32 BattleGetFloorHeight(BattleWork* wp, f32 x, f32 y, f32 z); // wp is not read

// BTL_ALLOC/BTL_FREE: US routes these battle-heap sites through BattleAlloc/BattleFree; JP calls the heap directly.
#if VERSION >= VERSION_US
#define BTL_ALLOC(size) BattleAlloc(size)
#define BTL_FREE(ptr) BattleFree(ptr)
#else
#define BTL_ALLOC(size) __memAlloc(HEAP_BATTLE, size)
#define BTL_FREE(ptr) __memFree(HEAP_BATTLE, ptr)
#endif
void BattleIncSeq(BattleWork* wp, BattleSequence seq);
s32 BattleGetSeq(BattleWork* wp, BattleSequence seq);
void BattleSetSeq(BattleWork* wp, BattleSequence seq, u32 value);
void BattleSetMarioParamToFieldBattle(BattleWork* work);
BOOL Btl_UnitSetup(BattleWork* work);
void BattleEnd(void);
void BattleInit(FieldBattleInfo* info);
BOOL battleSeqEndCheck(void);

struct BattleUnit* BattleChangeParty(BattleWork* wp);
s32 BattleTransPartyId(BattleUnitType kind);

BOOL battleDisableHResetCheck(void);

void BattleConsumeReserveItem(void);
s32 BattleGetStockExp(BattleWork* wp);
void BattleMajinaiDone(void);
void BattleMajinaiEndCheck(void);
void BattleStatusWindowAPRecoveryOff(void);
void BattleStatusWindowEventOn(void);
void BattleStatusWindowSystemOff(void);
void BattleStatusWindowSystemOn(void);

BattleUnitType BattleTransPartyIdToUnitKind(s32 partyId);
void BattleStoreCoin(BattleWork* wp, s32 coin);
void BattleStoreExp(BattleWork* wp, s32 exp);
void BattleAfterReactionEntry(s32 a, s32 b);
BOOL BattleAfterReactionMain(void);
void BattleStatusWindowAPRecoveryOn(void);
void BattleStatusWindowEventOff(void);
u8 BattleMajinaiCheck(void);
BOOL BattleStatusWindowCheck(void);
void BattlePartyAnimeLoad(s32 partyId);
