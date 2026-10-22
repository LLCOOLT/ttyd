#pragma once

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include "battle/battle_unit.h"
#include "mario/mario_pouch.h"

#define NPC_FIELD_MAX_COUNT 36
#define NPC_BATTLE_MAX_COUNT 16

typedef enum NpcTerritoryType {
    NPC_TERRITORY_TYPE_NOTHING = 0,
    NPC_TERRITORY_TYPE_CIRCLE = 1,
    NPC_TERRITORY_TYPE_SQUARE = 2
} NpcTerritoryType;

typedef struct NpcTerritoryInfo {
    const char* description; // 0x0
    NpcTerritoryType type;   // 0x4
} NpcTerritoryInfo;

typedef struct NpcDeadInfo {
    char mapName[16]; // 0x0
    s32 mask;         // 0x10
} NpcDeadInfo;

// TODO: move this somewhere better?
typedef struct PointDropData {
    s32 maxStatPercent;    // 0x0, 0 terminates the table
    s32 overallDropChance; // 0x4
    s32 numDrops;          // 0x8
    s32 dropChance;        // 0xC
} PointDropData;

typedef struct BattleGroupSetup {
    s32 numEnemies;              // 0x0
    BattleUnitSetup* enemyData;  // 0x4
    s32 heldItemWeight;          // 0x8
    s32 randomItemWeight;        // 0xC
    s32 noItemWeight;            // 0x10
    PointDropData* hpDropTable;  // 0x14
    PointDropData* fpDropTable;  // 0x18
    u8 field_1C[0x20 - 0x1C];    // 0x1C
} BattleGroupSetup;

typedef struct NpcBattleSelect {
    s32 weight;                  // 0x0, 0 terminates the table
    BattleGroupSetup* groupSetup; // 0x4
    struct BattleStageData* stageData; // 0x8
} NpcBattleSelect;

typedef struct NpcSetupBattleInfo {
    const char* name;            // 0x0
    s32 field_4;                 // 0x4
    ItemType fixedItem;          // 0x8
    s32 swFlag;                  // 0xC
    NpcBattleSelect* altSelect;  // 0x10, used when swFlag is set
    NpcBattleSelect* select;     // 0x14
    s32 field_18;                // 0x18
    s32 field_1C;                // 0x1C
    s8 field_20[16][2];          // 0x20, {min, max}
    s32 field_40;                // 0x40
} NpcSetupBattleInfo;

typedef struct NpcBattleInfo {
    struct BattleStageData* stageData; // 0x0
    s32 field_4;                    // 0x4
    ItemType fixedItem;             // 0x8
    ItemType itemDropped;           // 0xC
    s32 heartsDropped;              // 0x10
    s32 flowersDropped;             // 0x14
    BattleGroupSetup* groupSetup;   // 0x18
    ItemType heldItems[8];          // 0x1C
    ItemDropData* itemDropLists[8]; // 0x3C
    ItemType stolenItems[8];        // 0x5C
    ItemType recoveredItems[8];     // 0x7C
    union {
        s32 btlSetupWork[10];       // 0x9C
        struct {
            s32 field_9C[4];        // 0x9C
            s32 field_AC;           // 0xAC
            u8 field_B0[16];        // 0xB0
            s32 field_C0;           // 0xC0
        };
    };
    u8 battleRule[3];               // 0xC4
    u8 field_C7;                    // 0xC7
} NpcBattleInfo;

typedef struct NpcTribeInfo {
    const char* nameJp;           // 0x0
    const char* modelName;        // 0x4
    const char* initialAnim;      // 0x8
    const char* stopAnimation;    // 0xC
    const char* stayAnim;         // 0x10
    const char* talkAnim;         // 0x14
    const char* walkAnimation;    // 0x18
    const char* runAnimation;     // 0x1C
    const char* damageAnimation;  // 0x20
    const char* confuseAnimation; // 0x24
    f32 width;                    // 0x28, TODO double check
    f32 height;                   // 0x2C
    f32 shadowOffsetX;            // 0x30
    f32 shadowOffsetY;            // 0x34
    f32 shadowOffsetZ;            // 0x38
    f32 runStartSpeed;            // 0x3C
    const char* footstepSfxA;     // 0x40
    const char* footstepSfxB;     // 0x44
    u16 footstepStride;           // 0x48
    const char* jumpSfx;          // 0x4C
    const char* landSfx;          // 0x50
} NpcTribeInfo;

typedef struct NpcEntry {
    s32 flags;                      // 0x0
    u32 reactionFlags;              // 0x4
    char description[32];           // 0x8
    NpcTribeInfo* tribe;            // 0x28
    char currentAnim[32];           // 0x2C
    char stayAnim[32];              // 0x4C
    char talkAnim[32];              // 0x6C
    Vec position;                   // 0x8C, verified
    Vec prevPosition;               // 0x98
    Vec positionHistory[5];         // 0xA4
    Vec scale;                      // 0xE0
    Vec rotation;                   // 0xEC
    Vec rotationOffset;             // 0xF8
    s32 poseId;                     // 0x104
    s32 field_108;                  // 0x108
    const char* field_10C;          // 0x10C
    s32 offscreenId;                // 0x110
    GXColor color;                  // 0x114
    s32 initEvtId;                  // 0x118
    s32 regularEvtId;               // 0x11C
    void* initEvent;                // 0x120, verified
    void* moveEvent;                // 0x124, verified
    void* talkEvt;                  // 0x128
    void* deadEvent;                // 0x12C, verified
    void* findEvent;                // 0x130, verified
    void* lostEvent;                // 0x134, verified
    void* returnEvent;              // 0x138, verified
    void* blowEvent;                // 0x13C, verified
    u32 interruptFlags;             // 0x140, why the regular event was interrupted (blow/find/...)
    f32 direction;                  // 0x144, angle we're facing at, verified
    f32 savedDirection;             // 0x148, saved during field battle
    f32 width;                      // 0x14C
    f32 height;                     // 0x150
    f32 shadowScale;                // 0x154
    Vec jumpStartPos;               // 0x158
    Vec jumpTargetPos;              // 0x164
    u8 field_170[0x178 - 0x170];    // 0x170
    OSTime field_178;               // 0x178
    f32 field_180;                  // 0x180
    u8 field_184[0x188 - 0x184];    // 0x184
    OSTime field_188;               // 0x188
    OSTime field_190;               // 0x190
    OSTime field_198;               // 0x198
    f32 field_1A0;                  // 0x1A0
    f32 moveDt;                     // 0x1A4
    f32 field_1A8;                  // 0x1A8
    f32 moveDir;                    // 0x1AC
    f32 moveSpeed;                  // 0x1B0
    Vec moveOffset;                 // 0x1B4
    f32 moveTime;                   // 0x1C0
    f32 jumpVelY;                   // 0x1C4
    f32 jumpYScale;                 // 0x1C8
    f32 jumpGravity;                // 0x1CC
    f32 field_1D0;                  // 0x1D0
    u32 jumpFlags;                  // 0x1D4, TODO verify
    s16 footstepToggle;             // 0x1D8
    f32 footstepAccum;              // 0x1DC
    const char* footstepSfxA;       // 0x1E0
    const char* footstepSfxB;       // 0x1E4
    u16 footstepStride;             // 0x1E8
    const char* jumpSfx;            // 0x1EC
    const char* landSfx;            // 0x1F0
    s32 cameraId;                   // 0x1F4, CameraId
    NpcTerritoryType territoryType; // 0x1F8, verified, TODO: create territory substruct?
    Vec territoryBase;              // 0x1FC, verified
    Vec territoryLoiter;            // 0x208, verified
    Vec territoryHoming;            // 0x214, verified
    f32 searchRange;                // 0x220, verified
    f32 searchAngle;                // 0x224, verified
    f32 homingRange;                // 0x228, verified
    f32 homingAngle;                // 0x22C, verified
    NpcBattleInfo battleInfo;       // 0x230
    s32 field_2F8;                  // 0x2F8
    u32 wallHit;                    // 0x2FC, npcHitCheckSide result (HitEntry*)
    struct HitEntry* field_0x300;   // 0x300, hit object
    void* unitWork[4];              // 0x304
    u8 setupIndex;                  // 0x314, slot in the setup list (dead-mask bit)
    u8 btlCoinDropCount;            // 0x315
    u8 baseCoinCount;               // 0x316
    u8 balloonType;                 // 0x317
    u8 field_318[0x31C - 0x318];    // 0x318
    u16 koopaEncounterType;         // 0x31C
    u16 field_31E;                  // 0x31E
    s16 wFbatHitCheckRelated;       // 0x320
    u8 pad_322[2];                  // 0x322
    struct NpcEntry* prev;          // 0x324
    struct NpcEntry* next;          // 0x328
    struct NpcEntry* master;        // 0x32C
    struct NpcEntry* slaves[4];     // 0x330
} NpcEntry;

typedef struct NpcFieldEntry {
    char mModelName[64];                // 0x0
    char mAnimName[64];                 // 0x40
    u32 mFlags;                         // 0x80
    f32 wCurrentRenderRotationMinus90Y; // 0x84, TODO better name
    f32 wRotationY;                     // 0x88, TODO better name
    f32 wScaleZ_flip;                   // 0x8C, TODO better name
    f32 wInitToZero4;                   // 0x90, TODO better name
} NpcFieldEntry;

typedef struct NpcWork {
    s32 count;            // 0x0, currently allocated
    s32 total;            // 0x4, maximum allowed
    s32 flags;            // 0x8
    NpcEntry* entries;    // 0xC
    NpcEntry* talkTarget; // 0x10, NPC that A would talk to this frame
} NpcWork;

typedef struct FirstStrikeInfo {
    BOOL enabled;        // 0x0
    u32 field_0x4;       // 0x4
    u32 type;            // 0x8
    u32 field_0xC;       // 0xC
    f32 field_0x10;      // 0x10
    f32 field_0x14;      // 0x14
    const char* msg_tag; // 0x18
    GXColor color;       // 0x1C
} FirstStrikeInfo;

typedef struct FieldBattleInfo {
	u32 mode; //0x0, unused
	BattleUnitType party; //0x4
	u32 partyId; //0x8
	NpcBattleInfo* setup; //0xC
	u32 result; //0x10
	u32 coins; //0x14, BattleStoreCoin
	u8 field_0x18; //0x18
	u8 ruleKeepResult; //0x19
	u8 field_0x1A; //0x1A
	u8 field_0x1B; //0x1B
} FieldBattleInfo;

typedef struct FieldBattleData {
    s16 mode;                    // 0x0
    u8 field_2[0x8 - 0x2];       // 0x2
    NpcEntry* target;            // 0x8
    u8 field_C[0x20 - 0xC];      // 0xC
    FieldBattleInfo info;        // 0x20
    u8 field_3C[0x4C - 0x3C];    // 0x3C
    NpcDeadInfo deadInfo[64];    // 0x4C
    u8 field_54C;                // 0x54C
    u8 sandersBombTrigger;       // 0x54D
    u8 field_54E[0x550 - 0x54E]; // 0x54E
    FirstStrikeInfo firstStrike; // 0x550
    u8 field_570[0x574 - 0x570]; // 0x570
    s32 field_574;               // 0x574
    s32 field_578;               // 0x578
    s32 field_57C;               // 0x57C
} FieldBattleData;

NpcWork* npcGetWorkPtr(void);
void npcReleaseFieldNpc(void);
void npcRecoveryFieldNpc(void);
void npcInit(void);
void npcReset(BOOL inBattle);
s32 npcGetReactionOfLivingBody(BOOL inBattle);
s32 npcEntry(const char* a1, const char* animName);
NpcTribeInfo* npcGetTribe(const char* tribeName);
void npcDelete(NpcEntry* entry);
void npcDeleteGroup(NpcEntry* entry);
void npcMain(void);
NpcEntry* npcNameToPtr(const char* name);
NpcEntry* npcNameToPtr_NoAssert(const char* name);
void npcSetLink(NpcEntry* npc, NpcEntry* other);
void npcSetBtlSetupWork(NpcEntry* npc, s32 index, s32 value);
s32 npcGetBtlSetupWork(NpcEntry* npc, s32 index);
void npcBlurOff(const char* name);
void npcBlurOn(const char* name);
void npcSetColor(const char* name, GXColor color);
void npcStartForOneEvent(NpcEntry* npc);
void npcStartForEvent(void);
void npcStopForOneEvent(NpcEntry* npc);
void npcStopForEvent(void);
void npcCheckInterrupt(NpcEntry* npc);
void npcGroupDead(NpcEntry* npc, BOOL arg1);
f32 npcTransRytoFaceDir(NpcEntry* npc);

FieldBattleData* fbatGetPointer(void);

void npcSetSlave(NpcEntry* npc, NpcEntry* slave, s32 id);
void npcSetBattleInfo(NpcEntry* npc, s32 battleInfoId);
void fbatChangeMode(s16 mode);

NpcTerritoryType dbGetDefData(NpcTerritoryInfo* info, const char* description);
