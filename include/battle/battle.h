#pragma once

#include <dolphin/types.h>
#include "battle/battle_ac.h"
#include "battle/battle_audience.h"
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

typedef struct BattleWork BattleWork;
typedef struct BattleWorkCommand BattleWorkCommand;
typedef struct BattleAlliance BattleAlliance;
typedef struct BattleWorkCommandAction BattleWorkCommandAction;
typedef struct BattleWorkCommandWeapon BattleWorkCommandWeapon;
typedef struct BattleWorkCommandOperation BattleWorkCommandOperation;
typedef struct BattleWorkCommandParty BattleWorkCommandParty;
typedef struct BattleWorkCommandMultiItem BattleWorkCommandMultiItem;
typedef struct BattleWorkCommandCursor BattleWorkCommandCursor;
typedef struct BattleWorkCommandWindow BattleWorkCommandWindow;

typedef enum BattleFlags { BATTLE_SEQ_END = 0x80000000 } BattleFlags;

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

typedef struct BattleAnnounce {
    s16 x;                           // 0x0
    s16 y;                           // 0x2
    s32 params[4];                   // 0x4
    char text[0x18FD8 - 0x18C84];    // 0x14
    s32 field_368;                   // 0x368
    s32 field_36C;                   // 0x36C
} BattleAnnounce;

// deprecated ------------------------------------------------------------
struct BattleWorkCommandAction {
    u32 mType;      // 0x0
    BOOL mEnabled;  // 0x4
    char* mName;    // 0x8
    u16 mIcon;      // 0xC
    u8 pad_0xE[2];  // 0xE
    u32 field_0x10; // 0x10, mDisabled?
};

struct BattleWorkCommandWeapon {
    BattleWeapon* mWeaponParams; // 0x0
    u32 field_0x4;               // 0x4
    char* mName;                 // 0x8
    u16 mIcon;                   // 0xC
    u8 pad_0xE[2];               // 0xE
    u32 mIndex;                  // 0x10
    ItemType mItem;              // 0x14
    u32 field_0x18;              // 0x18
};

struct BattleWorkCommandOperation {
    u32 mType;          // 0x0
    BOOL mEnabled;      // 0x4
    u32 field_0x8;      // 0x8, mDisabled?
    char* mName;        // 0xC
    u16 mIcon;          // 0x10
    u8 pad_0x12[2];     // 0x12
    char* mDescription; // 0x14
    u32 mWeaponCost;    // 0x18
};

struct BattleWorkCommandParty {
    BattleUnitType mPartyId; // 0x0
    BOOL mEnabled;           // 0x4
    char* mName;             // 0x8
    u16 mIcon;               // 0xC
    u8 pad_0xE[2];           // 0xE
    char* mDescription;      // 0x10
    u16 mCurrentHP;          // 0x14
    u16 mMaxHP;              // 0x16
};

struct BattleWorkCommandMultiItem {
    BOOL mEnabled;      // 0x0
    char* mName;        // 0x4
    char* mDescription; // 0x8
    u16 mIcon;          // 0xC
    u8 pad_0xE[2];      // 0xE
    u32 mWeaponCost;    // 0x10
    u32 field_0x14;     // 0x14, mDisabled?
};

struct BattleWorkCommandCursor {
    u32 mAbsolutePos; // 0x0
    u32 mRelativePos; // 0x4
    u32 mNumOptions;  // 0x8
};

struct BattleWorkCommandWindow {
    u8 field_0x0[0x124 - 0]; // 0x0
};

// TODO: modularize for more actions/party members?
struct BattleWorkCommand {
    u32 mCurrentState;                             // 0x0
    u32 mCurrentMenu;                              // 0x4
    BattleWorkCommandAction mActionTable[6];       // 0x8
    BattleWorkCommandWeapon mWeaponTable[21];      // 0x80
    BattleWorkCommandOperation mOperationTable[7]; // 0x2CC
    BattleWorkCommandParty mPartyTable[8];         // 0x390
    BattleWorkCommandMultiItem mMultiItemTable[3]; // 0x450
    BattleWorkCommandCursor mCursors[14];          // 0x498
    u8 field_0x540[0x55C - 0x540];                 // 0x540
    BattleWorkCommandWindow* mWindowWork;          // 0x55C
    u8 field_0x560[0x574 - 0x560];                 // 0x560
};
// end deprecated ----------------------------------------------------

typedef struct BattleWorkActRecord {
    u8 field_0x0[0x24 - 0x0]; // 0x0
} BattleWorkActRecord;

struct BattleAlliance {
    u16 allianceId;     // 0x0
    s8 attackDirection; // 0x2
    // pad 1 byte
    u32 clearConditionMet; // 0x4
};

typedef struct BattleWorkPartyInfo {
    f32 field_0;              // 0x0
    u8 field_4[0x1E];         // 0x4
    u8 field_22[0x24 - 0x22]; // 0x22
    s32 field_24;             // 0x24
} BattleWorkPartyInfo;

typedef struct BattleWorkTarget {
    s16 unitIdx;                  // 0x0
    s16 partIdx;                  // 0x2
    u8 field_0x4[0x24 - 0x4];     // 0x4
} BattleWorkTarget;

typedef struct BattleWorkWeaponTargets {
    BattleWeapon* weapon;          // 0x0
    BattleWorkTarget targets[74];  // 0x4
    s8 numTargets;                 // 0xA6C
    s8 targetIndices[74];          // 0xA6D
    s8 currentTarget;              // 0xAB7
    u8 field_0xAB8[0xACC - 0xAB8]; // 0xAB8
} BattleWorkWeaponTargets;

typedef struct BattlePhaseEvtEntry {
    s32 unitId;   // 0x0
    s32 priority; // 0x4
} BattlePhaseEvtEntry;

struct BattleWork {
    s16 turnCount;                      // 0x0
    u16 turnSubSeq;                     // 0x2
    s32 seqUnknownValue;                // 0x4
    BattleAlliance alliances[3];        // 0x8
    BattleUnit* units[64];              // 0x20
    s32 movePriorityQueue[64];          // 0x120
    BattlePhaseEvtEntry phaseEvtTable[64]; // 0x220
    s32 activeUnitId;                   // 0x420
    s32 field_424;                      // 0x424
    BattleWorkWeaponTargets weaponTargets; // 0x428
    u32 flags;                          // 0xEF4
    s32 dispFlags;                      // 0xEF8
    s32 ruleDispTimer;                  // 0xEFC
    s32 stockExp;                       // 0xF00, BattleStoreExp/BattleGetStockExp
    s32 stockExpDisp;                   // 0xF04, counts up to stockExp in BattleStockExpDisp
    s32 stockExpTimer;                  // 0xF08, frame counter for that count-up
    s32 seqInitValue;                   // 0xF0C
    s32 seqFirstActValue;               // 0xF10
    s32 seqTurnValue;                   // 0xF14
    s32 seqPhaseValue;                  // 0xF18
    s32 seqMoveValue;                   // 0xF1C
    s32 seqActValue;                    // 0xF20
    s32 seqEndValue;                    // 0xF24
    BattleSeqEndWork* seqEndWork;       // 0xF28
    BattleWorkPad padWork[4];           // 0xF2C
    BattleCommand commandMenu;          // 0x171C
    BattleActions actionCommands;       // 0x1C90
    u8 field_1F9C[0x271C - 0x1F9C];     // 0x1F9C
    s32 mStylishCurFrame;               // 0x271C
    s32 mStylishWindowStart;            // 0x2720
    s32 mStylishWindowEnd;              // 0x2724
    s32 mStylishEndFrame;               // 0x2728
    s32 mStylishUnitId;                 // 0x272C
    s32 mStylishResult;                 // 0x2730
    s32 mStylishEarlyFrames;            // 0xA2734
    FieldBattleInfo* fbatInfo;          // 0x2738
    s32 statusWindowOff;                // 0x273C
    s32 lectureMode;                    // 0x2740
    s32 statusWindowSystemOn;           // 0x2744, BattleStatusWindowSystemOn/Off
    s32 statusWindowEventOn;            // 0x2748, BattleStatusWindowEventOn/Off
    s32 statusWindowAPRecoveryOn;       // 0x274C, BattleStatusWindowAPRecoveryOn/Off
    s32 field_2750;                     // 0x2750
    BattleCameraWork cameraWork;        // 0x2754
    BattleAudience audience;            // 0x2858
    u8 field_1616C[0x162A0 - 0x1616C];  // 0x1616C
    BattleWorkPartyInfo partyInfo[7];   // 0x162A0
    u32 tattledUnitTypeFlags[8];        // 0x163B8
    s32 badgeEquippedFlags;             // 0x163D8
    FileEntry* menuTex;                 // 0x163DC
    BattleStage stage;                  // 0x163E0
    u8 field_16F1C[0x16F3B - 0x16F1C];  // 0x16F1C
    u8 field_16F3B;                     // 0x16F3B
    u8 marioAcSuccess;                  // 0x16F3C
    u8 marioAcFailed;                   // 0x16F3D
    u8 field_16F3E[0x17140 - 0x16F3E];  // 0x16F3E
    BattleStageObject stageObjects[32]; // 0x17140
    u8 field_180C0[0x180DC - 0x180C0];  // 0x180C0
    u8 field_180DC;                     // 0x180DC, 0x20: stage has a ceiling
    u8 field_180DD[0x182B0 - 0x180DD];  // 0x180DD
    BattleIcon icons[16];               // 0x182B0
    BattleAnnounce announce;            // 0x18C70
    s8 alertTick;                       // 0x18FE0
    u8 majinaiState;                    // 0x18FE1
    u16 luckTimer;                      // 0x18FE2
    StarPowerInfo impendingBonuses;     // 0x18FE4
    const char* acHelpMsg;              // 0x18FF0
    s32 acHelpDispType;                 // 0x18FF4
    u8 field_18FF8[0x19038 - 0x18FF8];  // 0x18FF8
    s32 commandDisabled[5];             // 0x19038, set to 3 by Bowser's command-blocking attacks
    s32 luckEventId;                    // 0x1904C
    u32 reserveItems[4];                // 0x19050
    s32 field_19060;                    // 0x19060
    u8 field_19064[0x19088 - 0x19064];  // 0x19064
};
extern BattleWork* _battleWorkPointer;

void battleMain(void);

void battle_exit(void);
BOOL battle_init(void);
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
