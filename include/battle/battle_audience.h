// Declares the audience member types and the battle audience control functions.
#pragma once

#include <dolphin/types.h>
#include "version.h"
#include <dolphin/mtx.h>
#include "manager/evtmgr.h"
#include "manager/filemgr.h"
#include "mario/mario_pouch.h"
#include "battle/battle_database_common.h"

#pragma enumsalwaysint off
typedef enum AudienceMemberType {
    AUDIENCE_TOAD,          // 0x0, 0
    AUDIENCE_XNAUT,         // 0x1, 1
    AUDIENCE_BOO,           // 0x2, 2
    AUDIENCE_HAMMER_BRO,    // 0x3, 3
    AUDIENCE_DULL_BONES,    // 0x4, 4
    AUDIENCE_SHY_GUY,       // 0x5, 5
    AUDIENCE_CRAZY_DAYZEE,  // 0x6, 6
    AUDIENCE_PUNI,          // 0x7, 7
    AUDIENCE_KOOPA,         // 0x8, 8
    AUDIENCE_BULKY_BOBOMB,  // 0x9, 9
    AUDIENCE_GOOMBA,        // 0xA, 10
    AUDIENCE_PIRANHA_PLANT, // 0xB, 11
    AUDIENCE_LUIGI,         // 0xC, 12
    AUDIENCE_MAX            // 0xD, 13
} AudienceMemberType;
#pragma enumsalwaysint on

typedef struct StarPowerInfo {
    struct BattleWeapon* weapon; // 0x0
    f32 spAcSuccessMultiplier;   // 0x4
    u8 stylishCommandMultiplier; // 0x8
    s8 reserved_09;              // 0x9, copied from BattleWeapon.reserved_19, never read
    s8 bingoSlotChance;          // 0xA
    s8 pad_0B;                   // 0xB, never accessed
} StarPowerInfo;

// BattleAudienceMember.flags.
typedef enum BattleAudienceMemberFlags {
    MEMBER_FLAG_ACTIVE = 0x1,      // the seat is in use
    MEMBER_FLAG_REMOVED = 0x2,     // taken by a boss (Cortez, Magnus, Hooktail): keeps the seat, not counted
    MEMBER_FLAG_VISIBLE = 0x4,     // animated and drawn
    MEMBER_FLAG_CENTER_SEAT = 0x8, // a middle seat: phase events and item throws
    MEMBER_FLAG_EVT_CTRL = 0x10,   // under script control (BattleAudience_GetSysCtrl is false)
    MEMBER_FLAG_TARGETED = 0x20,   // the player targeted this item holder
    MEMBER_FLAG_ATTACKED = 0x40,   // the player hit it: it drops its item
    MEMBER_FLAG_WIDE = 0x80,       // a two-seat member, left seat
    MEMBER_FLAG_WIDE_TAIL = 0x100, // the right seat of a two-seat member (calls go to index - 1)
    MEMBER_FLAG_NO_ESCAPE = 0x200, // never runs away
} BattleAudienceMemberFlags;

typedef struct BattleAudienceMember {
    s32 flags;                     // 0x0
    s32 step;                      // 0x4, sub-step of the current status handler
    s32 counter;                   // 0x8, per-status counter
    f32 counterF;                  // 0xC, per-status float counter
    f32 workF1;                    // 0x10, per-status float, cleared on status change
    f32 workF2;                    // 0x14, per-status float, cleared on status change
    s8 colorStep;                  // 0x18, added to colorB each frame (+-4)
    u8 status;                     // 0x19
    u8 texId;                      // 0x1A, palette texture index for the member quad
    u8 type;                       // 0x1B, AudienceMemberType
    s16 itemId;                    // 0x1C, -1 is invalid
    s32** animTable;               // 0x20, set in BattleAudience_Entry_Sub
    s32* animStart;                // 0x24, current anim script (animTable entry); -3 jumps back here
    s32* animPc;                   // 0x28, anim script read pointer (BattleAudienceAnimProcess)
    s32 animWait;                  // 0x2C, frames left before the next script op
    s32 timer;                     // 0x30, per-status frame timer
    s32 animLoop[3];               // 0x34, loop counters for script ops -6/-7
    u8 animDepth;                  // 0x40, loop nesting depth
    u8 colorR;                     // 0x41, draw colour (read with G/B/A in the member draw)
    u8 colorG;                     // 0x42
    u8 colorB;                     // 0x43
    u8 colorA;                     // 0x44, 0xFF = opaque (separate draw pass)
    Vec position;                  // 0x48
    Vec scale;                     // 0x54, final draw scale: baseScale * kind texture size (PSMTXScale in the member draw)
    Vec baseScale;                 // 0x60
    Vec dispOffset;                // 0x6C, added to position for the drawn quad
    Vec velocity;                  // 0x78, added to position each frame
    Vec accel;                     // 0x84, added to velocity
    Vec facingDir;                 // 0x90, (0,0,-1) rotated by the member matrix; dot-product facing test
    Vec rotation;                  // 0x9C
    Vec rotationOffset;            // 0xA8
    Vec homePosition;              // 0xB4
    f32 drawPosX;                  // 0xC0, position + hop (+ bob), used as the thrown-item origin
    f32 drawPosY;                  // 0xC4
    f32 drawPosZ;                  // 0xC8
    f32 hopX;                      // 0xCC, hop offset added in the draw
    f32 hopY;                      // 0xD0, hop height, += hopSpeed, stops at 0
    f32 hopZ;                      // 0xD4
    u8 reserved_D8[0xDC - 0xD8];   // 0xD8, never accessed
    f32 hopSpeed;                  // 0xDC, += hopAccel per frame
    u8 reserved_E0[0xE4 - 0xE0];   // 0xE0, never accessed
    f32 hopAccel;                  // 0xE4, hop gravity (0 = hop finished)
    f32 angle;                     // 0xE8, init 270, wrapped to 0..360
    struct BattleUnit* targetUnit; // 0xEC, the unit the member targets
    s16 targetMemberId;            // 0xF0, index of another member it interacts with
    s32 statusDelay;               // 0xF4, countdown before status 13 -> 3
    s32 interpFramesLeft;          // 0xF8
    s32 interpFramesTotal;         // 0xFC
    f32 startPosX;                 // 0x100
    f32 targetPosX;                // 0x104
    f32 startPosY;                 // 0x108
    f32 targetPosY;                // 0x10C
    f32 startPosZ;                 // 0x110
    f32 targetPosZ;                // 0x114
    Vec interpDelta;               // 0x118
    f32 interpGravity;             // 0x124
    s32 interpType;                // 0x128
    union {
        s32 statusTimer; // 0x12C, set to 5 and counted down while status == 18
        f32 bobAngle;    // 0x12C, kinopio bob phase (radians)
    };
    f32 bobOffset; // 0x130, type 2: 5 * sin(phase) added to the drawn y
} BattleAudienceMember;

typedef struct BattleAudienceItem {
    u32 flags;                 // 0x0
    s32 state;                 // 0x4
    s32 timer;                 // 0x8, per-state frame timer
    s32 audienceId;            // 0xC, member that threw it
    ItemType itemType;         // 0x10
    Vec position;              // 0x14
    f32 scale;                 // 0x20
    f32 rotZ;                  // 0x24
    Vec velocity;              // 0x28
    Vec accel;                 // 0x34, added to velocity each frame
    struct BattleUnit* target; // 0x40, unit the item is thrown at
    s32 mode;                  // 0x44, nonzero once it is a hazard (lands on a unit)
} BattleAudienceItem;

typedef struct BattleAudienceStar {
    s32 flags;       // 0x0
    s32 state;       // 0x4, 0 spawn, 5 rise, 10 wait, 15 spiral to the AP gauge, 20 fade
    Vec position;    // 0x8
    f32 reserved_14; // 0x14, random -20..20 at spawn, never read
    f32 reserved_18; // 0x18, random 0..10 at spawn, never read
    f32 reserved_1C; // 0x1C, 0 at spawn, never read
    Vec startPos;    // 0x20, interpolation start
    Vec targetPos;   // 0x2C, interpolation target / spiral centre
    Vec scale;       // 0x38
    s32 timer;       // 0x44, frames in the current state
    s32 duration;    // 0x48, frames for the current state
    f32 radius;      // 0x4C, spiral radius
    f32 startRadius; // 0x50, spiral radius at the start of state 15
    f32 angle;       // 0x54, spiral angle (radians)
    f32 angleSpeed;  // 0x58, spiral angle step per frame
    u8 alpha;        // 0x5C
} BattleAudienceStar;

// member names are inferred from use
typedef struct BattleAudienceSound {
    u8 header[0x10 - 0x0];        // 0x0, raw head (AudSound view in battle_audience.c)
    s32 fadeoutTime;              // 0x10
    s32 forceFadeTimer;           // 0x14
    s32 forceFadeLength;          // 0x18
    u8 baseSfxVolume;             // 0x1C
    u8 currentBaseSfxVolume;      // 0x1D
    u8 volumeMultiplier;          // 0x1E
    u8 fadeStartVolumeMultiplier; // 0x1F
    u8 fadeEndVolumeMultiplier;   // 0x20
} BattleAudienceSound;

typedef struct BattleAudienceWindow {
    u8 active;                 // 0x0, nonzero while the window is shown
    u8 reserved_01[0x8 - 0x1]; // 0x1, never accessed
    f32 x;                     // 0x8, window x
    f32 y;                     // 0xC, window y
    f32 z;                     // 0x10, window z
    s32 slideTimer;            // 0x14, 0..15 slide-in frames
    f32 count;                 // 0x18, number to display for audience count
} BattleAudienceWindow;

#define AUDIENCE_MEMBER_MAX 200 // BattleAudience.members
#define AUDIENCE_ITEM_MAX 100   // BattleAudience.items and .starpower

// BattleAudience.flags. The demo has one more flag at 0x400 (STYLISH_MISSED), so every flag after it sits one
// bit higher there. 0x1 and 0x4 are never used.
typedef enum BattleAudienceFlags {
    AUDIENCE_FLAG_SP_GAINED = 0x2,      // the crowd gave star power this cheer (set, never read)
    AUDIENCE_FLAG_PHASE_REACTION = 0x8, // run the per-phase audience reactions this phase
    AUDIENCE_FLAG_AC_GOOD = 0x10,       // an action command succeeded this action
    AUDIENCE_FLAG_AC_BAD = 0x20,        // an action command failed this action
    AUDIENCE_FLAG_GUARD_GOOD = 0x40,    // a guard or superguard succeeded
    AUDIENCE_FLAG_GUARD_BAD = 0x80,     // a guard failed
    AUDIENCE_FLAG_STYLISH_GOOD = 0x100, // a stylish move landed
    AUDIENCE_FLAG_STYLISH_BAD = 0x200,  // a stylish move was tried and failed
#if VERSION <= VERSION_DEMO_US
    AUDIENCE_FLAG_STYLISH_MISSED = 0x400, // the last stylish try missed; a later success or no-try clears it
    AUDIENCE_FLAG_ENEMY_DAMAGED = 0x800,
#else
    AUDIENCE_FLAG_ENEMY_DAMAGED = 0x400,
#endif
    // the flags below sit one bit higher in the demo
    AUDIENCE_FLAG_ENEMY_NO_DAMAGE = AUDIENCE_FLAG_ENEMY_DAMAGED << 1, // an attack hit an enemy for no damage
    AUDIENCE_FLAG_ENEMY_KILLED = AUDIENCE_FLAG_ENEMY_DAMAGED << 2,    // the action defeated an enemy
    AUDIENCE_FLAG_NOISE_STARTED = AUDIENCE_FLAG_ENEMY_DAMAGED << 3,   // the crowd-noise loop has started
    AUDIENCE_FLAG_NO_HAZARDS = AUDIENCE_FLAG_ENEMY_DAMAGED << 4,      // no audience hazards (set by Hooktail's script)
    AUDIENCE_FLAG_PUNI_ESCAPE = AUDIENCE_FLAG_ENEMY_DAMAGED << 5,     // the Punies fled; msg_puni_all_escape pending
    AUDIENCE_FLAG_COMMAND_MENU = AUDIENCE_FLAG_ENEMY_DAMAGED << 6,    // last frame's copy of BattleWork.flags 0x80
    AUDIENCE_FLAG_HIDDEN = AUDIENCE_FLAG_ENEMY_DAMAGED << 7,          // audience, items and AP sources not drawn
    AUDIENCE_FLAG_FROZEN = AUDIENCE_FLAG_ENEMY_DAMAGED << 8,          // scripted: no reactions, size changes or throws
} BattleAudienceFlags;

typedef struct BattleAudience {
    s32 flags;                                         // 0x0
    EventEntry* event;                                 // 0x4
    s32 apStarSfxId;                                   // 0x8, SFX_BTL_SYS_AP_STAR1 handle
    FileEntry* normalTex;                              // 0xC
    FileEntry* guestTex[2];                            // 0x10
    AudienceMemberType guestType[2];                   // 0x18
    u8 reserved_1A[0x1BC - 0x1A];                      // 0x1A, never accessed (guestType is 2 bytes: AudienceMemberType is under enumsalwaysint off)
    BattleAudienceMember members[AUDIENCE_MEMBER_MAX]; // 0x1BC
    BattleAudienceItem items[AUDIENCE_ITEM_MAX];       // 0xF25C
    BattleAudienceStar starpower[AUDIENCE_ITEM_MAX];   // 0x10E7C
#if VERSION <= VERSION_DEMO_US
    // the demo keeps the counters before the sounds and window, with a few more of them
    f32 audienceDeltaMultiplier;          // 0x133FC
    f32 targetAudienceCount;              // 0x13400
    f32 addedAudienceCount;               // 0x13404
    s32 currentAudienceIntCount;          // 0x13408
    s32 currentAudienceIntCountRight;     // 0x1340C
    s32 currentAudienceIntCountLeft;      // 0x13410
    s32 presentCount;                     // 0x13414, members that exist and are not in status 12 (BattleAudienceNumToTargetSub)
    s32 maxAudience;                      // 0x13418
    s32 typeWeights[12];                  // 0x1341C
    s32 starPowerGain;                    // 0x1344C
    s32 numStylishCommandsThisAttack;     // 0x13450
    s32 stylishTotal;                     // 0x13454, stylish commands summed over the battle, capped at 100
    s32 crowdPleasedStreak;               // 0x13458
    s32 crowdDispleasedStreak;            // 0x1345C
    s32 acStreak;                         // 0x13460, capped at 2, indexes the weapon's per-streak table
    StarPowerInfo* impendingBonuses;      // 0x13464
    u8 reserved_13468[0x1346C - 0x13468]; // 0x13468, never accessed
    s32 checkPhaseReactionState;          // 0x1346C
    s32 phaseSub;                         // 0x13470
    s32 joyLevel;                         // 0x13474
    s32 presentItemNo;                    // 0x13478
    s32 presentItemType;                  // 0x1347C
    s32 presentTargetUnitId;              // 0x13480
    s32 itemThrowCount;                   // 0x13484
    s32 itemThrowMax;                     // 0x13488
    s32 presentHitCount;                  // 0x1348C
    BattleWeapon presentWeapon;           // 0x13490
    s32 itemHolderId;                     // 0x13550
    Vec itemHolderPos;                    // 0x13554
    s32 phaseList[14];                    // 0x13560
    s32 phaseListCount;                   // 0x13598
    s32 turnEndPhaseEventChance;          // 0x1359C
    BattleAudienceSound sounds[24];       // 0x135A0
    BattleAudienceWindow window;          // 0x13900
    BOOL excited;                         // 0x1391C
} BattleAudience;
#else
    BattleAudienceSound sounds[24];       // 0x133FC
    BattleAudienceWindow window;          // 0x1375C
    f32 audienceDeltaMultiplier;          // 0x13778
    f32 targetAudienceCount;              // 0x1377C
    f32 addedAudienceCount;               // 013780
    s32 currentAudienceIntCount;          // 0x13784
    s32 currentAudienceIntCountRight;     // 0x13788
    s32 currentAudienceIntCountLeft;      // 0x1378C
    s32 maxAudience;                      // 0x13790
    s32 typeWeights[12];                  // 0x13794, per-type audience weights (BattleAudienceSettingAudience)
    s32 starPowerGain;                    // 0x137C4, star power gained this action
    StarPowerInfo* impendingBonuses;      // 0x137C8, copy of the last StarPowerInfo (BattleAudience_ApRecoveryBuild)
    s32 crowdPleasedStreak;               // 0x137CC, consecutive good actions, capped at 2
    s32 crowdDispleasedStreak;            // 0x137D0, consecutive bad actions, capped at 5
    s32 numStylishCommandsThisAttack;     // 0x137D4
    u8 reserved_137D8[0x137DC - 0x137D8]; // 0x137D8, never accessed
    s32 checkPhaseReactionState;          // 0x137DC
    s32 phaseSub;                         // 0x137E0, phase sub-state
    s32 presentItemNo;                    // 0x137E4
    s32 presentItemType;                  // 0x137E8
    s32 presentTargetUnitId;              // 0x137EC
    s32 itemThrowCount;                   // 0x137F0, audience item throws this battle
    s32 itemThrowMax;                     // 0x137F4, throw limit rolled at battle start (0-3; 10000 when forced)
    s32 presentHitCount;                  // 0x137F8, thrown items that landed, capped at 3; adds to presentWeapon damage
    BattleWeapon presentWeapon;           // 0x137FC, BattleWeapon copy (0xC0) for a thrown hazard item, passed to BattleCheckDamage
    s32 itemHolderId;                     // 0x138BC, member holding an item (BattleAudience_GetItemOn)
    Vec itemHolderPos;                    // 0x138C0
    s32 phaseList[14];                    // 0x138CC
    s32 phaseListCount;                   // 0x13904
    s32 turnEndPhaseEventChance;          // 0x13908
    s32 joyLevel;                         // 0x1390C, audience joy level
    BOOL excited;                         // 0x13910, if toads are cheering
} BattleAudience;
#endif

BattleAudience* BattleAudienceBaseGetPtr(void);
BattleAudienceMember* BattleAudienceGetPtr(s32 id);
BattleAudienceItem* BattleAudienceItemGetPtr(s32 id);
BattleAudienceWindow* BattleAudienceWinGetPtr(void);
BattleAudienceSound* BattleAudienceSoundGetPtr(s32 id);
void BattleAudience_Init(void);
void BattleAudience_Main(void);
void BattleAudience_ActInit(void);
void BattleAudience_PerAct(void);
BOOL BattleAudience_CheckReaction(void);
void BattleAudience_PerPhase(u32 value);
BOOL BattleAudience_CheckReactionPerPhase(void);
void BattleAudience_Disp(void);
void BattleAudience_End(void);
BOOL BattleAudience_Entry(s32 index, AudienceMemberType type, u8 status);
void BattleAudience_Delete(s32 index);
void BattleAudience_SetAnim(s32 id, s32 animId, BOOL force);
void BattleAudience_GetPosition(s32 index, f32* x, f32* y, f32* z);
void BattleAudience_GetHomePosition(s32 index, f32* x, f32* y, f32* z);
void BattleAudience_GetRotate(s32 index, f32* x, f32* y, f32* z);
void BattleAudience_SetPosition(s32 index, f32 x, f32 y, f32 z);
void BattleAudience_SetRotate(s32 index, f32 x, f32 y, f32 z);
void BattleAudience_SetRotateOffset(s32 index, f32 x, f32 y, f32 z);
void BattleAudience_GetItemOn(s32* memberId, f32* x, f32* y, f32* z, ItemType* itemType);
void BattleAudience_GetItemOn2(s32* memberId, f32* x, f32* y, f32* z, ItemType* itemType);
void BattleAudience_SetTarget(s32 index);
void BattleAudience_Attack(s32 index);
void BattleAudience_ChangeStatus(s32 index, s32 status);
BOOL BattleAudience_GetExist(s32 index);
BOOL BattleAudience_GetSysCtrl(s32 index);
u8 BattleAudience_GetWaiting(s32 index);
s32 BattleAudience_HaitiRandForFallObject(void);
s32 BattleAudience_GetAudienceNum(void);
void BattleAudience_WinSetActive(u8 active);

void BattleAudienceAddTargetNum(f32 value, f32 value2);
void BattleAudienceJoyEnding(void);
void BattleAudienceSoundCheer(s32 duration, s32 fade);
void BattleAudience_Case_AcrobatNoTry(void);
s32 BattleAudience_GetPresentItemNo(void);
s32 BattleAudience_GetPresentItemType(void);
s32 BattleAudience_GetPresentTargetUnitId(void);
void BattleAudience_SetPresentItemNo(s32 no);

void BattleAudience_SetPresentItemType(s32 type);
void BattleAudience_SetPresentTargetUnitId(s32 unitId);

void BattleAudienceSoundClap(s32 duration, s32 fade);
void BattleAudienceSoundSetVolAll(u8 vol, s32 length);
void BattleAudienceSoundStop(s32 index);
void BattleAudienceSoundWhistle(void);

BOOL BattleAudienceItemOn(s32 index, u16 itemId, s32 numItems);
BattleUnit* BattleAudienceDetectTargetAll(void);
BOOL BattleAudience_GetAnimEnd(s32 index);
BOOL BattleAudience_GetFront(s32 index);
s32 BattleAudience_GetAudienceNoFromOffset(s32 index, s32 column, s32 row);
void BattleAudience_ApRecoveryBuild(StarPowerInfo* info);
void BattleAudienceNumToTarget(void);
void BattleAudienceAddTargetNum(f32 value, f32 value2);
void BattleAudiencePuniAllEscape(void);
void BattleAudienceJoySACLecture(void);
s32 BattleAudienceDetectPakkunEatTarget(s32 index);
void BattleAudienceSoundBooing(void);
void BattleAudienceSoundBooingKind(s32 kind);
void BattleAudienceSoundClap(s32 duration, s32 fade);
void BattleAudienceSoundCheer(s32 duration, s32 fade);
void BattleAudienceSoundCheerKind(s32 kind, s32 duration, s32 fade);
void BattleAudienceSoundWhistleKind(s32 kind);
void BattleAudienceSoundCallKind(s32 kind);
void BattleAudienceSoundHandBeat(void);
void BattleAudienceSoundItemThrow(s32 kind, s32 index);
void BattleAudienceSoundRun(s32 kind);
void BattleAudienceSoundSleep(s32 index);
void BattleAudienceSoundZZZ(s32 index);
void BattleAudienceSoundSing(s32 index);
void BattleAudienceSoundShell(s32 index);
void BattleAudienceSoundBombIgnite(s32 index, s32 duration, s32 fade);
void BattleAudienceSoundBombFire(s32 index);
void BattleAudienceSoundPakkunEat(s32 index);
void BattleAudienceSoundStop(s32 index);
void BattleAudience_Disp(void);
void BattleAudience_Case_ActionCommandGood(BattleWeapon* weapon);
void BattleAudience_Case_ActionCommandBad(BattleWeapon* weapon);
void BattleAudience_Case_KillEnemy(s32 level);
void BattleAudience_Case_MarioBigDamage(s32 damage);
void BattleAudience_Case_EnemyDamage(s32 damage);
void BattleAudience_Case_GuardGood(void);
void BattleAudience_Case_GuardBad(void);
void BattleAudience_Case_AcrobatGood(void);
void BattleAudience_Case_AcrobatBad(void);
void BattleAudience_Case_MarioPinch(void);
void BattleAudience_Case_MarioDanger(void);
void BattleAudience_Case_PartyDown(void);
void BattleAudience_Case_JumpNewRecord(void);
void BattleAudience_Case_FinalAttack(void);
void BattleAudience_Case_TurnEnd(void);
void BattleAudience_Case_Appeal(BattleUnit* unit);
void BattleAudience_Case_Escape(void);
void BattleAudience_Case_Escape_Good(void);
void BattleAudience_Case_Escape_Bad(void);
void BattleAudience_Case_EnemyNoDamage(void);
void BattleAudience_Case_Countered(void);
void BattleAudience_Case_HaikeiSet(void);
void BattleAudience_Case_GreatVictory(void);
void BattleAudience_Case_FastVictory(f32 rate);
void BattleAudience_Case_FallObject_Stage(void);
void BattleAudience_Case_FallObject_Aud(s32 index, u8 type);
void BattleAudience_Case_FirstAttack_Good(void);
void BattleAudience_Case_FirstAttack_Bad(void);
s32 BattleAudienceAddAudienceNum(s32 num);
void BattleAudienceSoundSetVol(s32 index, u8 a2, s32 a3);
s32 BattleAudienceSoundCheck(s32 index);
BOOL BattleAudience_GetEscapeChangeOK(s32 index);
