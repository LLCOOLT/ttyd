// npcdrv.c: the field NPC system (NpcEntry, NpcWork, npcEntry/npcMain) and the NPC_FLAG_* bits.
#pragma once

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include "battle/battle_unit.h"
#include "mario/mario_pouch.h"
#include "evt/evt_word.h"
#include "version.h"

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

typedef struct PointDropData {
    s32 maxStatPercent;    // 0x0, 0 terminates the table
    s32 overallDropChance; // 0x4
    s32 numDrops;          // 0x8
    s32 dropChance;        // 0xC
} PointDropData;

typedef struct BattleGroupSetup {
    s32 numEnemies;             // 0x0
    BattleUnitSetup* enemyData; // 0x4
    s32 heldItemWeight;         // 0x8
    s32 randomItemWeight;       // 0xC
    s32 noItemWeight;           // 0x10
    PointDropData* hpDropTable; // 0x14
    PointDropData* fpDropTable; // 0x18
    s32 reserved_1C;            // 0x1C, never read
} BattleGroupSetup;

typedef struct NpcBattleSelect {
    s32 weight;                        // 0x0, 0 terminates the table
    BattleGroupSetup* groupSetup;      // 0x4
    struct BattleStageData* stageData; // 0x8
} NpcBattleSelect;

typedef struct NpcSetupBattleInfo {
    const char* name;           // 0x0
    const char* mapName;        // 0x4, never read; map the battle is set on
    ItemType fixedItem;         // 0x8
    s32 swFlag;                 // 0xC
    NpcBattleSelect* altSelect; // 0x10, used when swFlag is set
    NpcBattleSelect* select;    // 0x14
    s32 battleFlags;            // 0x18, NPC_BATTLE_* flags, -> NpcBattleInfo.battleFlags
    s32 randomMode;             // 0x1C, -> NpcBattleInfo.randomMode; 0 rolls randomValues from randomRanges
    s8 randomRanges[16][2];     // 0x20, {min, max} per NpcBattleInfo.randomValues byte
    const char* bgmName;        // 0x40, -> NpcBattleInfo.bgmName, played by seq_battle
} NpcSetupBattleInfo;

// audience/reward rolls made when the battle is set up (npcSetupBattleInfo), read by BattleAudience
typedef struct NpcBattleRandom {
    s32 mode;      // 0x0, from NpcSetupBattleInfo.randomMode
    s8 values[16]; // 0x4, rolled from NpcSetupBattleInfo.randomRanges (read as s8 weights)
} NpcBattleRandom;

// NpcSetupBattleInfo.battleFlags / NpcBattleInfo.battleFlags (copied by npcSetupBattleInfo; maps also set them on
// the NPC before the battle). The comment names the reader.
#define NPC_BATTLE_NO_COINS 0x1                  // evt_npc_get_drop_coin returns 0
#define NPC_BATTLE_NO_HEARTS 0x2                 // evt_npc_get_drop_heart returns 0
#define NPC_BATTLE_NO_FLOWERS 0x4                // evt_npc_get_drop_flower returns 0
#define NPC_BATTLE_NO_ITEM 0x8                   // evt_npc_get_drop_item returns 0
#define NPC_BATTLE_NO_ESCAPE 0x10                // battle_seq_command: Run Away disabled; battle_seq: stage walls close
#define NPC_BATTLE_MERLEE_NO_CURSE_4 0x20        // BattleMajinaiCheck rolls curse types 1-3 only (45/45/10, not 30/30/20/20)
#define NPC_BATTLE_LOSS_OK 0x40                  // battle_seq_end: losing does not end the game; Mario keeps at least 1 HP
#define NPC_BATTLE_FIRST_STRIKE_BONUS 0x100      // npcdrv: a first-strike win adds 1 to the multiplier
#define NPC_BATTLE_NO_PLAYER_ENTRY 0x100000      // battle_seq: Mario's and the partners' entry events are not run
#define NPC_BATTLE_NO_JUMP 0x1000000             // battle_seq_command: Jump disabled
#define NPC_BATTLE_NO_HAMMER 0x2000000           // battle_seq_command: Hammer disabled
#define NPC_BATTLE_NO_PARTY_CHANGE 0x4000000     // battle_seq_command: Change Partner disabled
#define NPC_BATTLE_NO_BUMP_ATTACK 0x10000000     // npcdrv: the Bump Attack badge cannot win the encounter outright
#define NPC_BATTLE_MARIO_PAUSE3_VOICE 0x20000000 // battle_seq_end: victory voice SFX_VOICE_MARIO_PAUSE3, not PAUSE1

typedef struct NpcBattleInfo {
    struct BattleStageData* stageData; // 0x0
    s32 battleFlags;                   // 0x4, NPC_BATTLE_* flags
    ItemType fixedItem;                // 0x8
    ItemType itemDropped;              // 0xC
    s32 heartsDropped;                 // 0x10
    s32 flowersDropped;                // 0x14
    BattleGroupSetup* groupSetup;      // 0x18
    ItemType heldItems[8];             // 0x1C
    ItemDropData* itemDropLists[8];    // 0x3C
    ItemType stolenItems[8];           // 0x5C
    ItemType recoveredItems[8];        // 0x7C
    union {
        s32 btlSetupWork[10]; // 0x9C
        struct {
            s32 scriptWork[4];      // 0x9C, btlSetupWork[0..3] (npcGet/SetBtlSetupWork)
            NpcBattleRandom random; // 0xAC, btlSetupWork[4..8]
            const char* bgmName;    // 0xC0, btlSetupWork[9], battle BGM played by seq_battle
        };
    };
    u8 battleRule[3]; // 0xC4
    u8 pad_C7;        // 0xC7, never accessed
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
    f32 width;                    // 0x28
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

// NpcEntry.flags bits (the 0x40000600 family in NPC setup data), named from their uses in
// npcdrv.c. 0x1000 and 0x80000000 are not tested there.
enum NpcFlags {
    NPC_FLAG_USED = 0x1,                    // slot is allocated (npcEntry)
    NPC_FLAG_ACTIVE = 0x2,                  // init event finished: updated, drawn and hit-checked
    NPC_FLAG_RECORD_DEFEAT = 0x4,           // _npcDead records the defeat in FieldBattleData.deadInfo
    NPC_FLAG_ENEMY = 0x8,                   // only the encounter hit check (kind 0x1000) sees it; never talkable
    NPC_FLAG_LAND_ON_FLOOR = 0x10,          // npcMoveG: downward motion stops on the floor (raycast, snaps to hitY); without it y moves freely
    NPC_FLAG_INTANGIBLE = 0x20,             // skipped by the Mario hit checks, blow checks and side collision
    NPC_FLAG_ALWAYS_VISIBLE = 0x40,         // drawn even when the position is outside the camera frustum
    NPC_FLAG_HIDDEN = 0x80,                 // model, shadow and blur are not drawn (offscreen pass still is)
    NPC_FLAG_BLUR = 0x100,                  // npcBlurOn: keeps a position history and draws the motion blur
    NPC_FLAG_TALK_ANIM = 0x200,             // npcSetTalkPose/npcSetStayPose play the NPC's talk and stay animations
    NPC_FLAG_MOVE_ANIM = 0x400,             // stay/walk/run animation chosen from the movement speed every frame
    NPC_FLAG_NO_DISPLAY = 0x800,            // no projection, colour update or display entries at all
    NPC_FLAG_SKIP_HIT_ATTR4 = 0x2000,       // side collision ignores hit surfaces with attribute 0x4
    NPC_FLAG_NO_MARIO_SIDE_HIT = 0x4000,    // npcCheckHitMarioSide is skipped
    NPC_FLAG_INSTANT_TURN = 0x8000,         // the paper pose turns at once (animation pose flag 0x100)
    NPC_FLAG_WALL_BOUNCE = 0x10000,         // a side hit reflects the movement angle off the wall
    NPC_FLAG_JUMPING = 0x20000,             // jump clock runs; npcMoveG follows the jump arc
    NPC_FLAG_NO_SHADOW = 0x40000,           // no shadowEntry
    NPC_FLAG_SHADOW_NO_COLLISION = 0x80000, // shadow is not projected onto the map (shadowSetCollision off)
    NPC_FLAG_NO_AUTO_UPDATE = 0x100000,     // movement clock only advances when the update bit is set from outside
    NPC_FLAG_NO_FIND_EVENTS = 0x200000,     // find/lost/return interrupt events are not raised
    NPC_FLAG_RESUME_ON_LEAVE = 0x400000,    // Mario leaving talk range restarts the regular event (no move interrupt)
    NPC_FLAG_LUIGI = 0x800000,              // "c_luigi" model: pose flipped by npcLuigiPoseFlip
    NPC_FLAG_NO_TURN_TO_MARIO = 0x1000000,  // keeps its direction when Mario comes to talk
    NPC_FLAG_NO_BILLBOARD = 0x2000000,      // mtx_setup does not turn the model toward the camera
    NPC_FLAG_VIVIAN_TYPE = 0x4000000,       // shadow-type model (animPoseGetVivianType): drawn by animPoseVivianMain
    NPC_FLAG_KOOPA_MODE = 0x8000000,        // Bowser side-scrolling stage NPC: X-only movement, own encounter check
    NPC_FLAG_HAS_BATTLE_INFO = 0x10000000,  // npcSetupBattleInfo ran; frozen while another NPC's battle starts
    NPC_FLAG_NO_FIELD_ATTACK = 0x20000000,  // cannot be hit by field attacks or blown away
    NPC_FLAG_NO_WALL_HIT = 0x40000000,      // moves without side (wall) collision
};

// NpcEntry.jumpFlags bits, the NPC status set by evt_npc_status_onoff and read by
// evt_npc_status_check; named from their uses in npcdrv.c and evt_npc.c.
enum NpcStatusFlags {
    NPC_STATUS_AIRBORNE = 0x1,            // npcMoveG: off the floor this frame (NPC_FLAG_LAND_ON_FLOOR); evt_npc moves stop re-aiming, evt_npc_jump waits
    NPC_STATUS_FACE_MOVE_DIR = 0x2,       // the evt_npc moves turn the body toward the travel direction (npcTuningRy)
    NPC_STATUS_DEAD = 0x4,                // _npcDead; the Bowser stage hit checks skip it
    NPC_STATUS_CLOCK_RUNNING = 0x10,      // the movement clock advances this frame (set each frame without NPC_FLAG_NO_AUTO_UPDATE, and by the evt_npc moves)
    NPC_STATUS_NO_FIND_EVENT = 0x1000,    // npcCheckInterrupt raises no find/lost/return event, then clears it (evt_npc moves set it)
    NPC_STATUS_FROZEN = 0x10000,          // npcStopForOneEvent: the movement clock and move offset stop
    NPC_STATUS_IN_LAVA = 0x100000,        // in kpa_03's lava this frame: slowed, fall speed capped
    NPC_STATUS_WAS_IN_LAVA = 0x200000,    // in the lava last frame: no splash sound
    NPC_STATUS_DIM_COLOR = 0x400000,      // the colour is halved before it is applied (npcDimColor)
    NPC_STATUS_LAVA_NO_SLOW = 0x10000000, // the lava does not slow the movement
    NPC_STATUS_MARIO_NEAR = 0x20000000,   // Mario is in talk range: the regular event is stopped and the NPC faces him
};

// NpcEntry.interruptFlags bits: why the regular event is replaced, read by npcCheckInterrupt to pick the event to run.
enum NpcInterruptFlags {
    NPC_INTERRUPT_FIND = 0x1,        // Mario found: findEvent
    NPC_INTERRUPT_LOST = 0x2,        // Mario lost: lostEvent
    NPC_INTERRUPT_RETURN = 0x4,      // back in its territory: returnEvent
    NPC_INTERRUPT_BLOW = 0x8,        // blown away (npcCheckBlow): blowEvent
    NPC_INTERRUPT_DEAD = 0x10,       // defeated (_npcDead): deadEvent
    NPC_INTERRUPT_NO_FIND = 0x100,   // JP and later: set as a field battle ends (battle_seq_end), find interrupts are ignored
    NPC_INTERRUPT_KEEP_MASK = 0xF00, // JP and later: bits that npcCheckInterrupt keeps
    NPC_INTERRUPT_MOVE = 0x10000000, // restart the move event (evt_npc_return_interrupt, after a battle or the hit cooldown)
};

// NpcEntry.hazardFlags bits: the Bowser stage hazards (npcKoopaModeEncountCheck, npcKoopaModeMobjBoundDeadCheck)
// that do not kill the NPC; npcGroupDead gets the matching bit as its reason.
enum NpcHazardFlags {
    NPC_HAZARD_NO_STOMP = 0x1, // stomped by Bowser (kpaEnemyHitChk 1); also set every frame the NPC is in kpa_03's lava
    NPC_HAZARD_NO_FIRE = 0x2,  // Bowser's fire (kpaEnemyHitChk 2)
    NPC_HAZARD_NO_STAR = 0x4,  // touching Bowser while he is invincible (kpaEnemyHitChk 3)
    NPC_HAZARD_NO_BUMP = 0x8,  // a block bumped from below (npcKoopaModeMobjBoundDeadCheck)
    NPC_HAZARD_NO_LAVA = 0x10, // standing on the "a_magu" lava
};

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
    s32 moveAnimState;              // 0x108, 1 stay, 2 walk, 3 run anim currently set by npcMain
    const char* checkPose;          // 0x10C, anim name, "M_I_2" by default (tik_02 geso_set_checkpose sets "M_S_1")
    s32 offscreenId;                // 0x110
    GXColor color;                  // 0x114
    s32 initEvtId;                  // 0x118
    s32 regularEvtId;               // 0x11C
    EvtWord* initEvent;             // 0x120, verified
    EvtWord* moveEvent;             // 0x124, verified
    EvtWord* talkEvt;               // 0x128
    EvtWord* deadEvent;             // 0x12C, verified
    EvtWord* findEvent;             // 0x130, verified
    EvtWord* lostEvent;             // 0x134, verified
    EvtWord* returnEvent;           // 0x138, verified
    EvtWord* blowEvent;             // 0x13C, verified
    u32 interruptFlags;             // 0x140, NPC_INTERRUPT_*: why the regular event was interrupted
    f32 direction;                  // 0x144, angle we're facing at, verified
    f32 savedDirection;             // 0x148, saved during field battle
    f32 width;                      // 0x14C
    f32 height;                     // 0x150
    f32 shadowScale;                // 0x154
    Vec jumpStartPos;               // 0x158
    Vec jumpTargetPos;              // 0x164
    u8 pad_170[0x178 - 0x170];      // 0x170
    OSTime jumpTicks;               // 0x178, OSTime accumulated while jumping/falling, 0 on landing
    f32 jumpElapsed;                // 0x180, jumpTicks in seconds
    u8 pad_184[0x188 - 0x184];      // 0x184
    OSTime moveTicks;               // 0x188, OSTime accumulated since the current evt move started
    OSTime dtTicks;                 // 0x190, frame delta (capped to 16 ms after a >500 ms gap)
    OSTime lastUpdateTicks;         // 0x198, gp->renderTime of the last update
    f32 moveElapsed;                // 0x1A0, moveTicks in seconds (compared with moveTime)
    f32 moveDt;                     // 0x1A4
    f32 lastUpdateTime;             // 0x1A8, lastUpdateTicks in seconds
    f32 moveDir;                    // 0x1AC
    f32 moveSpeed;                  // 0x1B0
    Vec moveOffset;                 // 0x1B4
    f32 moveTime;                   // 0x1C0
    f32 jumpVelY;                   // 0x1C4
    f32 jumpYScale;                 // 0x1C8
    f32 jumpGravity;                // 0x1CC
    f32 maxFallSpeed;               // 0x1D0, fall speed limit, 100 in kpa_03 lava
    u32 jumpFlags;                  // 0x1D4
    s16 footstepToggle;             // 0x1D8
    f32 footstepAccum;              // 0x1DC
    const char* footstepSfxA;       // 0x1E0
    const char* footstepSfxB;       // 0x1E4
    u16 footstepStride;             // 0x1E8
    const char* jumpSfx;            // 0x1EC
    const char* landSfx;            // 0x1F0
    s32 cameraId;                   // 0x1F4, CameraId
    NpcTerritoryType territoryType; // 0x1F8
    Vec territoryBase;              // 0x1FC, verified
    Vec territoryLoiter;            // 0x208, verified
    Vec territoryHoming;            // 0x214, verified
    f32 searchRange;                // 0x220, verified
    f32 searchAngle;                // 0x224, verified
    f32 homingRange;                // 0x228, verified
    f32 homingAngle;                // 0x22C, verified
    NpcBattleInfo battleInfo;       // 0x230
    s32 attackMode;                 // 0x2F8, evt_npc_set_attack_mode
    struct HitEntry* wallHit;       // 0x2FC, npcHitCheckSide result
    struct HitEntry* groundHit;     // 0x300, hit object found by the fall/landing checks
    void* unitWork[4];              // 0x304
    u8 setupIndex;                  // 0x314, slot in the setup list (dead-mask bit)
    u8 btlCoinDropCount;            // 0x315
    u8 baseCoinCount;               // 0x316
    s8 balloonType;                 // 0x317
    u32 fbatHitKind;                // 0x318, kind from fbatHitCheck when this NPC triggered the battle
    u16 koopaEncounterType;         // 0x31C
    u16 hazardFlags;                // 0x31E, NPC_KOOPA_DEATH_*: Bowser-stage deaths it is immune to
    u16 fbatHitCooldown;            // 0x320
    u8 pad_322[2];                  // 0x322
    struct NpcEntry* prev;          // 0x324
    struct NpcEntry* next;          // 0x328
    struct NpcEntry* master;        // 0x32C
    struct NpcEntry* slaves[4];     // 0x330
} NpcEntry;

typedef struct NpcFieldEntry {
    char modelName[64];      // 0x0
    char animName[64];       // 0x40
    u32 flags;               // 0x80
    f32 savedPeraRotY;       // 0x84, AnimationPose state saved across a pose reload
    f32 savedRotationY;      // 0x88
    f32 savedScaleZFlip;     // 0x8C
    f32 savedPeraTargetRotY; // 0x90
} NpcFieldEntry;

// NpcWork.flags bits.
enum NpcWorkFlags {
    NPC_WORK_RELEASE_FIELD = 0x2, // evt_npc_release_filednpc: the next battle start frees the field NPCs' poses (npcReleaseFiledNpc)
};

typedef struct NpcWork {
    s32 count;            // 0x0, currently allocated
    s32 total;            // 0x4, maximum allowed
    s32 flags;            // 0x8
    NpcEntry* entries;    // 0xC
    NpcEntry* talkTarget; // 0x10, NPC that A would talk to this frame
} NpcWork;

// NpcWork.flags
#define NPC_WORK_FLAG_CTRL_OFF_OK 0x1   // talk targets and field hits are checked even with Mario's keys or control off (gor_01)
#define NPC_WORK_FLAG_RELEASE_POSES 0x2 // evt_npc_release_filednpc: the field NPC poses are freed for the battle and rebuilt after

// fbatHitCheck flags: which hits to look for
#define FBAT_CHECK_LIVE_ATTACK 0x1  // the attacks are live: the hammer's current frame, Koops's shell, Bobbery's blast
#define FBAT_CHECK_CONTACT 0x10     // enemy contact too (and no checks while Mario is invincible)
#define FBAT_CHECK_JUMP 0x20        // touch and jump
#define FBAT_CHECK_HAMMER 0x40      // hammer
#define FBAT_CHECK_SPIN_HAMMER 0x80 // spin hammer
#define FBAT_CHECK_SHELL 0x100      // Koops's shell
#define FBAT_CHECK_BOMB 0x200       // Bobbery's bomb
#define FBAT_CHECK_ENEMIES 0x1000   // test enemies (NPC_FLAG_ENEMY) instead of the other NPCs
#define FBAT_CHECK_QUERY 0x2000     // only NPCs whose reactionFlags allow it, without the attack banner

// NpcEntry.hazardFlags: Bowser-stage deaths the NPC is immune to; also the reason passed to npcGroupDead
#define NPC_KOOPA_DEATH_STOMP 0x1 // stomped by Bowser (kpaEnemyHitChk 1); also set while the NPC is in lava
#define NPC_KOOPA_DEATH_FIRE 0x2  // burnt by Bowser's fire (kpaEnemyHitChk 2)
#define NPC_KOOPA_DEATH_STAR 0x4  // touched while Bowser is invincible (kpaEnemyHitChk 3)
#define NPC_KOOPA_DEATH_BLOCK 0x8 // standing on a block bumped from below (npcKoopaModeMobjBoundDeadCheck)
#define NPC_KOOPA_DEATH_LAVA 0x10 // standing on the lava floor "a_magu"

// What fbatHitCheck found (FieldBattleData.hitKind, FirstStrikeInfo.hitKind). Every kind but
// FBAT_HIT_CONTACT and FBAT_HIT_ENEMY_FIRST is a first strike by Mario or the partner.
enum FbatHitKind {
    FBAT_HIT_CONTACT = 0x10000,            // touched an enemy: no first strike
    FBAT_HIT_JUMP = 0x20000,               // jumped on it (also the spring jump)
    FBAT_HIT_SPIN_JUMP = 0x40000,          // jumped on it in the spin jump (MARIO_MOTION_HIP)
    FBAT_HIT_JUMP_UNUSED = 0x80000,        // announced and handled like a jump, but nothing produces it
    FBAT_HIT_HAMMER = 0x100000,            // hammer
    FBAT_HIT_SPIN_HAMMER = 0x200000,       // spin hammer, hammer level below 3
    FBAT_HIT_ULTRA_SPIN_HAMMER = 0x400000, // spin hammer, hammer level 3
    FBAT_HIT_SHELL = 0x800000,             // Koops' shell
    FBAT_HIT_BOMB = 0x1000000,             // Bobbery's bomb
    FBAT_HIT_ENEMY_FIRST = 0x10000000,     // the enemy struck first (its attackMode event runs)
};

typedef struct FirstStrikeInfo {
    BOOL enabled;        // 0x0
    u32 hitKind;         // 0x4, FbatHitKind passed to fbatSetAttackAnnounce, 0 when done
    u32 type;            // 0x8
    s32 timer;           // 0xC, frames into the announce slide (0..100)
    f32 x;               // 0x10, announce x, slides -600 -> 0 -> 600
    f32 y;               // 0x14, announce y
    const char* msg_tag; // 0x18
    GXColor color;       // 0x1C
} FirstStrikeInfo;

typedef struct FieldBattleInfo {
    u32 mode;             // 0x0, unused
    BattleUnitType party; // 0x4
    u32 partyId;          // 0x8
    NpcBattleInfo* setup; // 0xC
    u32 result;           // 0x10
    u32 coins;            // 0x14, BattleStoreCoin
    u8 ruleType;          // 0x18, NpcBattleInfo.battleRule[0], index into the _rule_msg tables
    u8 ruleKeepResult;    // 0x19
    u8 ruleParam;         // 0x1A, battleRule[1], printed in the rule message
    u8 ruleParam2;        // 0x1B, battleRule[2], turn limit for the rule check (battle_actrecord; 0xFF = none)
} FieldBattleInfo;

typedef struct FieldBattleData {
    s16 mode;                    // 0x0
    u8 subState;                 // 0x2
    u8 pad_03;                   // 0x3, never accessed
    NpcEntry* npc;               // 0x4, encounter npc
    NpcEntry* target;            // 0x8
    s32 evtId;                   // 0xC
    s32 hitKind;                 // 0x10, FbatHitKind from fbatHitCheck (tou_03 forces FBAT_HIT_ENEMY_FIRST)
    s32 firstAttackParam;        // 0x14, set to 0x10 by tou_03 _firstattack_setting; passed to BattleInformationSetFirstAttack (seq_battle)
    u8 pad_18[0x1C - 0x18];      // 0x18, never accessed
    u32 firstAttackFlags;        // 0x1C, bit 0: no first attack for either side (seq_battle); cleared by tou_03 _firstattack_setting
    FieldBattleInfo info;        // 0x20
    EvtWord* postBattleEvent;    // 0x3C, evt run after a won battle (battle_seq_end)
    s32 postBattleEventId;       // 0x40
    s32 postBattleMode;          // 0x44, nonzero: battle_seq_end skips to sequence 3 / 0x3000001
    u32 merleeEvtId;             // 0x48, _evt_majinai_coin_up_effect id
    NpcDeadInfo deadInfo[64];    // 0x4C
    u8 merleeCoinBonus;          // 0x54C, Merlee coin curse fired: coin drops x3
    u8 sandersBombTrigger;       // 0x54D
    u8 pad_54E[0x550 - 0x54E];   // 0x54E, never accessed
    FirstStrikeInfo firstStrike; // 0x550
#if VERSION >= VERSION_JP
    s32 battleWait; // 0x570, frames seq_battle has waited for the first-strike announce (gives up at 200)
#endif
    s32 kpaComboCount; // 0x574 (demo 0x570), Bowser stomp combo, score multiplier
    s32 kpaJumpKills;  // 0x578 (demo 0x574), Bowser kills during one jump
    s32 kpaJumpScore;  // 0x57C (demo 0x578), score banked during one jump, shown on landing
} FieldBattleData;     // size 0x580 (demo 0x57C)

NpcWork* npcGetWorkPtr(void);
void npcReleaseFiledNpc(void);
void npcRecoveryFiledNpc(void);
void npcInit(void);
void npcReset(BOOL inBattle);
s32 npcGetReactionOfLivingBody(BOOL inBattle);
s32 npcEntry(const char* name, const char* animName);
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
BOOL npcCheckInterrupt(NpcEntry* npc); // TRUE when an interrupt event was started
void npcGroupDead(NpcEntry* npc, u16 reason);
f32 npcTransRytoFaceDir(NpcEntry* npc);

FieldBattleData* fbatGetPointer(void);
NpcEntry* fbatNpcTalkCheck(void); // the NPC Mario can talk to now, or NULL
// The NPC found by the field hit checks that flags selects (talk, encounter, attacks), or NULL; when a1 is
// not NULL it receives the hit kind, event id and distance.
NpcEntry* fbatHitCheck(u32 flags, void* unused);
NpcEntry* fbatHitCheckAll(void); // fbatHitCheck(0x13F1, NULL)

void npcSetSlave(NpcEntry* npc, NpcEntry* slave, s32 id);
void npcSetBattleInfo(NpcEntry* npc, s32 battleInfoId);
void fbatChangeMode(s16 mode);

NpcTerritoryType dbGetDefData(NpcTerritoryInfo* info, const char* description);

BOOL N_fbatPreventMarioEventChk(void);

extern EvtWord evt_majinai_effect_se_btl[];
void fbatSandersBombTriggerOn(void);

extern EvtWord _evt_majinai_coin_up_effect[];

s32 npcCalcScore(NpcEntry* npc);
void npcGetBackItemEntry(NpcEntry* npc);
void npcSetMarioAutoTalkPose(const char* stayPose, const char* talkPose);
void npcTuningRy(NpcEntry* npc, f32 angle);

BOOL npcCheckBlow(NpcEntry* npc);
void fbatSetAttackAnnounce(s32 kind);
void fbatSetAttackAnnounceEnable(void);
void npcExecAllInitEvt(void);
BOOL npcWaitAllInitEvtEnd(void);
void npcExecAllReglEvt(void);
void npcClearDeadInfo(void);
s32 npcKoopaModeMobjBoundDeadCheck(struct HitEntry* hit);
NpcEntry* npcNearDistCheck(f32 x, f32 y, f32 z, f32 range);
void npcSetStayPose(char* name);
void npcSetTalkPose(char* name);
