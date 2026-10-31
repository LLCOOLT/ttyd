// The Great Tree (mri) battle unit: Magnus von Grapple (magnum_battender): its parts, defence/status tables, and attack
// events.
#include "eff/n64/eff_hokori_n64.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "manager/evtmgr_cmd.h"
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "eff/n64/eff_akari_charge_n64.h"
#include "driver/effdrv.h"
#include "manager/evtmgr.h"
#include "dolphin/mtx.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "unit/unit_boss_magnum_battender.h"
#include "eff/eff_batten.h"
#include "evt/evt_msg.h"
#include "evt/evt_sub.h"
#include "version.h"
#include "libc_decls.h"

// Unit work slots of Magnus von Grapple (btlevtcmd_SetUnitWork / GetUnitWork)
enum {
    UW_BOSS_MAGNUM_BATTENDER_ARMS_OUT = 0,          // 1 while his arms are fired off as rocket punch units
    UW_BOSS_MAGNUM_BATTENDER_ARM_RETURN_TIMER = 1,  // counts down on his turns once no fired arm is left; at 0 they return
    UW_BOSS_MAGNUM_BATTENDER_ARMS_FIRED_ONCE = 2,   // 1 after the first arm launch (its line is said only once)
    UW_BOSS_MAGNUM_BATTENDER_ARM_0 = 3,             // unit id of the rocket punch for arm 0
    UW_BOSS_MAGNUM_BATTENDER_ARM_1 = 4,             // unit id of the rocket punch for arm 1
    UW_BOSS_MAGNUM_BATTENDER_STAMP_SCENE_DONE = 5,  // 1 after the first stamp, which opens with a camera scene and a line
    UW_BOSS_MAGNUM_BATTENDER_LOW_HP_SCENE_DONE = 6, // 1 after his HP first drops to 7 or below (low-HP line) or he dies
};

// Unit work slots of a rocket punch (X-Fist), the arm unit Magnus fires off
enum {
    UW_ROCKET_PUNCH_ROLE = 0,       // 0 / 1: fired arm 0 / 1; 2 / 3: arm 0 / 1 flying back onto Magnus
    UW_ROCKET_PUNCH_WAIT_TURNS = 1, // counts down each turn; it attacks only when it reaches 0, then resets to 1
};

static EffectEntry* eff_charge;

static ArmWork* work[2];

static USER_FUNC(arm_check);
static USER_FUNC(arm_end);
static USER_FUNC(arm_init);
static USER_FUNC(arm_main);
static USER_FUNC(waku_main);
static USER_FUNC(eff_dead);
static USER_FUNC(eff_dead_delete);
static USER_FUNC(arm_init2);

BattleUnitKind unit_boss_magnum_battender;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[17];
static PoseTableEntry pose_table_no_arm[16];
static BattleDataEntry data_table[2];
static BattleUnitKindPart parts[3];
BattleWeapon weapon_batten_stamp_attack;
BattleWeapon weapon_batten_shake_attack;
static BattleUnitSetup entry_rocket_punch;
static EvtWord init_event[92];
static EvtWord waku_event[23];
static EvtWord damage_event[111];
#if VERSION <= VERSION_DEMO_JP
static EvtWord dead_event[216];
#else
static EvtWord dead_event[234];
#endif
static EvtWord entry_event[78];
static EvtWord attack_event[150];
extern EvtWord stamp_attack_event[];
static EvtWord shake_attack_event[324];
static EvtWord arm_bunri_event[199];
static EvtWord arm_return_event[151];
static EvtWord wait_event[6];
BattleUnitKind unit_boss_rocket_punch;
static BattleUnitDefense defence_r;
static BattleUnitDefenseAttr defence_attr_r;
static StatusVulnerability regist_r;
static PoseTableEntry pose_table_r[14];
static BattleDataEntry data_table_r[1];
static BattleUnitKindPart parts_r[1];
static BattleWeapon weapon_batten_rocket_attack;
static EvtWord init_event_r[191];
static EvtWord arm_event[59];
static EvtWord arm_event_end[35];
static EvtWord damage_event_r[30];
static EvtWord attack_event_r[368];
static EvtWord wait_event_r[18];

/**
 * Unit data of Magnus: 30 HP, 120x160 units in size; ties together its sounds, parts, status vulnerability,
 * init event and event table.
 */
BattleUnitKind unit_boss_magnum_battender = {
    34,
    "btl_un_magnum_battender",
    30,
    0,
    1,
    1,
    68,
    0,
    0,
    100,
    0,
    50,
    6,
    120,
    160,
    30,
    100,
    0.0f,
    80.0f,
    0.0f,
    0,
    0,
#if VERSION <= VERSION_DEMO_JP
    0.0f,
    0.0f,
#else
    30.0f,
    115.0f,
#endif
    0.0f,
    60.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    52.0f,
    0.0f,
    0.0f,
    30.0f,
    110.0f,
    20.0f,
    0.0f,
    80.0f,
    0.0f,
    120.0f,
    160.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_MBTN_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    3,
    parts,
    init_event,
    data_table,
};

/** Defence of Magnus: 1 against every kind of hit. */
static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

/** Defence attributes of Magnus: none, every element hits it normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Demo builds: Status vulnerability of Magnus (percent chance each status takes hold): immune to sleep,
 * poison, electrified, Huge, Tiny, Attack Down, fright, Gale Force, Dodgy, Invisible, instant KO;
 * resists stop (50%), dizzy (50%), confusion (50%), freeze (30%), Defense Down (50%), allergic (50%),
 * Slow (40%); the rest take hold at 80% or better.
 */
static StatusVulnerability regist = {0, 50, 50, 0, 50, 0, 100, 30, 0, 0, 100, 0, 100, 50, 50, 0, 0, 100, 40, 0, 0, 0};
#else
/**
 * Retail builds: Status vulnerability of Magnus (percent chance each status takes hold): immune to sleep,
 * poison, electrified, Huge, Tiny, Attack Down, fright, Gale Force, Dodgy, Invisible, instant KO;
 * resists stop (50%), dizzy (50%), confusion (50%), freeze (30%), allergic (50%), Slow (40%);
 * the rest take hold at 80% or better.
 */
static StatusVulnerability regist = {0, 50, 50, 0, 50, 0, 100, 30, 0, 0, 100, 0, 100, 90, 50, 0, 0, 100, 40, 0, 0, 0};
#endif

/** Pose table of Magnus: maps its battle poses to its animations (MGN_*). */
static PoseTableEntry pose_table[] = {
    {1, "MGN_S_1"},
    {2, "MGN_2D_1"},
    {9, "MGN_2D_1"},
    {5, "MGN_X_1"},
#if VERSION <= VERSION_DEMO_JP
    {4, "MGN_S_1"},
    {3, "MGN_S_1"},
#else
    {4, "MGN_X_1"},
    {3, "MGN_X_1"},
#endif
    {BTL_POSE_NORMAL, "MGN_S_1"},
    {29, "MGN_Q_1"},
    {30, "MGN_Q_1"},
    {31, "MGN_S_1"},
    {BTL_POSE_DAMAGE, "MGN_D_1"},
    {BTL_POSE_WALK, "MGN_W_1"},
    {41, "MGN_W_2"},
    {BTL_POSE_DANGER, "MGN_S_1"},
    {BTL_POSE_PERIL, "MGN_S_1"},
    {BTL_POSE_TALK, "MGN_T_1"},
    {BTL_POSE_STAY_DEFAULT, "MGN_S_1"},
};

/** Poses of Magnus after his arm has come off to be launched as the rocket fist. */
static PoseTableEntry pose_table_no_arm[] = {
    {1, "MGN_S_2"},
    {2, "MGN_2D_2"},
    {9, "MGN_2D_2"},
    {5, "MGN_X_2"},
#if VERSION <= VERSION_DEMO_JP
    {4, "MGN_S_2"},
    {3, "MGN_S_2"},
#else
    {4, "MGN_X_2"},
    {3, "MGN_X_2"},
#endif
    {BTL_POSE_NORMAL, "MGN_S_2"},
    {29, "MGN_Q_2"},
    {30, "MGN_Q_2"},
    {31, "MGN_S_2"},
    {BTL_POSE_DAMAGE, "MGN_D_2"},
    {BTL_POSE_WALK, "MGN_W_3"},
    {BTL_POSE_DANGER, "MGN_S_2"},
    {BTL_POSE_PERIL, "MGN_S_2"},
    {BTL_POSE_TALK, "MGN_T_2"},
    {BTL_POSE_STAY_DEFAULT, "MGN_S_2"},
};

/** Event table of Magnus: dead_event (tag 49). */
static BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

/** Parts of Magnus: 4 parts (model c_mb_robo_1b). */
static BattleUnitKindPart parts[] = {
#if VERSION >= VERSION_US
    {1, "btl_un_magnum_battender", "c_mb_robo_1b", 0.0f, 0.0f, 0.0f, 37.0f, 103.0f, 30.0f, 37.0f, 113.0f, 61.0f, 106, 174, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_NOT_ANY_PART_TARGET | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, 0, pose_table},
#else
    {1, "btl_un_magnum_battender", "c_mb_robo_1b", 0.0f, 0.0f, 0.0f, 37.0f, 103.0f, 30.0f, 37.0f, 113.0f, 61.0f, 106, 174, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, 0, pose_table},
#endif
    {2, "btl_un_magnum_battender", "c_mb_robo_1b", 0.0f, 0.0f, 0.0f, 10.0f, 10.0f, 30.0f, 10.0f, 20.0f, 61.0f, 106, 174, 255, &defence, &defence_attr, PART_ATTR_IMPORTANT | PART_ATTR_JUMPLIKE_CANNOT_TARGET | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, 0, pose_table},
    {3, "btl_un_magnum_battender", "c_mb_robo_1b", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
};

/**
 * Keeps the "waku" part (part 3, the frame or sign attached to Magnus von Grapple) fixed to the body:
 * every frame moves it to the position of locator17 in the body's animation
 * and turns it to face the camera (rotating by minus the camera yaw). args[0] is the unit.
 */
static USER_FUNC(waku_main) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit;
    BattleUnitPart* part;
    BattleUnitPart* waku;
    s32 poseId;
    AnimationPose* pose;
    s32 idx;
    f32 yaw;

    animGetPtr();
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    part = BtlUnit_GetPartsPtr(unit, 1);
    waku = BtlUnit_GetPartsPtr(unit, 3);
    poseId = part->poseId;
    animPoseWorldPositionEvalOn(poseId);
    animPoseGetAnimBaseDataPtr(poseId);
    pose = animPoseGetAnimPosePtr(poseId);
    idx = animPoseGetGroupIdx(poseId, "locator17");
    BtlUnit_SetPartsPos(waku, (*pose->worldPositions)[idx].x, (*pose->worldPositions)[idx].y,
                        (*pose->worldPositions)[idx].z);
    yaw = camGetPtr(CAMERA_3D)->viewYaw;
    BtlUnit_SetPartsRotate(waku, 0.0f, -yaw, 0.0f);
    return EVT_RETURN_DONE;
}

/**
 * Looks for a living rocket arm (X-Fist) on one side:
 * args[0] = 0 for the left (arm slot 0 or 2), 1 for the right (slot 1 or 3).
 * Writes the unit index of the first one found to args[1], or -1.
 */
static USER_FUNC(arm_check) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 side = evtGetValue(event, args[0]);
    s32 found = -1;
    BattleUnit* unit;
    s32 i;

    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && (unit->currentKind == UNIT_X_FIST || unit->currentKind == UNIT_X_PUNCH)) {
            if (side == 0 && (unit->work[UW_ROCKET_PUNCH_ROLE] == 0 || unit->work[UW_ROCKET_PUNCH_ROLE] == 2)) {
                found = i;
                break;
            }
            if (side == 1 && (unit->work[UW_ROCKET_PUNCH_ROLE] == 1 || unit->work[UW_ROCKET_PUNCH_ROLE] == 3)) {
                found = i;
                break;
            }
        }
    }
    evtSetValue(event, args[1], found);
    return EVT_RETURN_DONE;
}

/** Weapon of Magnus (batten stamp attack): targets one unit for 2 damage; used by stamp_attack_event. */
BattleWeapon weapon_batten_stamp_attack = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, // baseFpCost..baseSpCost
    1, // superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {2, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, // element
    12, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY, // counterResistFlags
    TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Weapon of Magnus (batten shake attack): targets every unit for 2 damage, ignores Defense;
 * used by shake_attack_event.
 */
BattleWeapon weapon_batten_shake_attack = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, // baseFpCost..baseSpCost
#if VERSION >= VERSION_US
    2, // superguardsAllowed
#else
    0, // superguardsAllowed
#endif
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {2, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_NO_FLOATING_2 | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_UNUSED_2000, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Spawn setup for Magnus' rocket fist (unit_boss_rocket_punch): enemy side, placed off-screen at first;
 * used by arm_bunri_event, arm_return_event.
 */
static BattleUnitSetup entry_rocket_punch = {
    &unit_boss_rocket_punch, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Init script of Magnus von Grapple: sets its wait, entry, attack, damage and confusion events,
 * puts the frame part in its pose, starts the frame-following event, creates the arm trail data,
 * clears its work values (arms attached, phase counters, the first stamp scene flag),
 * places it at x=125 turned 55 degrees and sets its walk and run sounds.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_NO_BACKFACE_FLIP)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(entry_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("MGN_L_1"))
    SPAWN_EVENT(waku_event)
    CALL(arm_init)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARMS_OUT, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARM_RETURN_TIMER, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARMS_FIRED_ONCE, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_STAMP_SCENE_DONE, 0)
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, 125, 0, 0)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 125, 0, 0)
    CALL(btlevtcmd_SetBaseRotate, BTL_UNIT_SELF, 0, -55, 0)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_MOVE1"), STRING("SFX_BOSS_MBTN_MOVE1"), 26, 26, 26)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_MOVE1"), STRING("SFX_BOSS_MBTN_MOVE1"), 20, 20, 20)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Per-frame loop that runs for as long as Magnus exists: moves the frame part to its place (waku_main). */
static EVT_BEGIN(waku_event)
    LABEL(0)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        GOTO(99)
    END_IF
    CALL(waku_main, BTL_UNIT_SELF)
    GOTO(0)
    LABEL(99)
    RETURN
EVT_END()

/**
 * Damage event of Magnus: marks the frame as non-targetable while a hit with damage pattern 10 is processed,
 * runs the default damage reaction, then the first time its HP drops to 7
 * or below (work 6) the status window closes, the camera moves in
 * and Magnus speaks his low-HP line (stg2_mri_e24_15) before the fight goes on.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_CheckDamagePattern, BTL_UNIT_SELF, 10, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 3, PART_ATTR_HIDDEN)
    END_IF
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 3, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_LOW_HP_SCENE_DONE, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 7)
            CALL(btlevtcmd_WaitAttackEnd)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_LOW_HP_SCENE_DONE, 1)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(evt_btl_camera_set_prilimit, 1)
            CALL(evt_btl_camera_set_mode, 1, 3)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            SUBTRACT(LW(0), 20)
            CALL(evt_btl_camera_set_moveto, 1, LW(0), 160, 600, LW(0), 110, -100, 20, 11)
            WAIT_FRAMES(20)
            CALL(btlevtcmd_SetTalkPoseType, BTL_UNIT_SELF, BTL_POSE_TALK)
            CALL(btlevtcmd_SetStayPoseType, BTL_UNIT_SELF, BTL_POSE_STAY_DEFAULT)
            CALL(evt_msg_print, 2, STRING("stg2_mri_e24_15"), 0, BTL_UNIT_SELF)
            CALL(evt_btl_camera_set_prilimit, 0)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            WAIT_MS(500)
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Starts the charging light effect (a glow of 1.5 scale) at x, y,
 * z (args[0] to args[2]) for Magnus's defeat scene and remembers it.
 */
static USER_FUNC(eff_dead) {
    EvtWord* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    eff_charge = effAkariChargeN64Entry(0, 1000, x, y, z, 1.5f);
    return EVT_RETURN_DONE;
}

/** Removes the defeat glow created by eff_dead. */
static USER_FUNC(eff_dead_delete) {
    effDelete(eff_charge);
    return EVT_RETURN_DONE;
}

/**
 * Creates a white dust puff (a vapor effect fading to black) at x, y,
 * z (args[0] to args[2]) with the lifetime given in args[3].
 */
static USER_FUNC(eff_hokori) {
    EvtWord* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    EffectEntry* eff = effHokoriN64Entry(0, evtGetValue(event, args[3]), x, y, z);

    ((EffHokoriN64Work*)eff->userdata)->r = 255;
    ((EffHokoriN64Work*)eff->userdata)->g = 255;
    ((EffHokoriN64Work*)eff->userdata)->b = 255;
    ((EffHokoriN64Work*)eff->userdata)->r2 = 0;
    ((EffHokoriN64Work*)eff->userdata)->g2 = 0;
    ((EffHokoriN64Work*)eff->userdata)->b2 = 0;
    return EVT_RETURN_DONE;
}

/**
 * Defeat event of Magnus: sets work 6, creates the glow above him,
 * closes the status window and moves the camera in; Magnus speaks his last line (stg2_mri_e24_16).
 * Any rocket arm still alive on either side (from JP,
 * only if its last hit did not already KO it, damage flag 0x200) is killed with the shared dead core
 * and its trail
 * removed. Magnus then plays the death sound, hands out coins, experience and star points,
 * and after 2 seconds drops his held item and is KO'd without being deleted (KILL_UNIT_KEEP);
 * the glow is removed.
 */
static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_LOW_HP_SCENE_DONE, 1)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 70)
    ADD(LW(2), 10)
    CALL(eff_dead, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_prilimit, 1)
    CALL(evt_btl_camera_set_mode, 1, 3)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SUBTRACT(LW(0), 20)
    CALL(evt_btl_camera_set_moveto, 1, LW(0), 160, 600, LW(0), 110, -100, 20, 11)
    WAIT_FRAMES(20)
    CALL(btlevtcmd_SetTalkPoseType, BTL_UNIT_SELF, BTL_POSE_DAMAGE)
    CALL(btlevtcmd_SetStayPoseType, BTL_UNIT_SELF, BTL_POSE_DAMAGE)
    CALL(evt_msg_print, 2, STRING("stg2_mri_e24_16"), 0, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_prilimit, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    WAIT_MS(500)
    CALL(arm_check, 0, LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
#if VERSION >= VERSION_JP
        CALL(btlevtcmd_CheckDamageCode, LW(0), DAMAGE_FLAG_KO, LW(1))
        IF_INT_EQUAL(LW(1), 0)
#endif
            SET_VALUE(LW(10), LW(0))
            BEGIN_INLINE_EVENT
                CALL_CHILD(subsetevt_dead_core)
                CALL(arm_end, 0)
                CALL(btlevtcmd_OnPartsAttribute, LW(10), 1, PART_ATTR_HIDDEN)
                CALL(btlevtcmd_OnPartsAttribute, LW(10), 1, PART_ATTR_NO_SHADOW)
            END_INLINE_EVENT
        END_IF
#if VERSION >= VERSION_JP
    END_IF
#endif
    CALL(arm_check, 1, LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
#if VERSION >= VERSION_JP
        CALL(btlevtcmd_CheckDamageCode, LW(0), DAMAGE_FLAG_KO, LW(1))
        IF_INT_EQUAL(LW(1), 0)
#endif
            SET_VALUE(LW(10), LW(0))
            BEGIN_INLINE_EVENT
                CALL_CHILD(subsetevt_dead_core)
                CALL(arm_end, 1)
                CALL(btlevtcmd_OnPartsAttribute, LW(10), 1, PART_ATTR_HIDDEN)
                CALL(btlevtcmd_OnPartsAttribute, LW(10), 1, PART_ATTR_NO_SHADOW)
            END_INLINE_EVENT
#if VERSION >= VERSION_JP
        END_IF
#endif
    END_IF
    SET_VALUE(LW(10), -2)
    CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_BTL_ENEMY_DIE1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetCoin, LW(10), LW(0))
    CALL(btlevtcmd_StoreCoin, LW(0))
    CALL(btlevtcmd_GetExp, LW(10), LW(0))
    CALL(btlevtcmd_StoreExp, LW(0))
    CALL(btlevtcmd_GetPos, LW(10), LW(3), LW(1), LW(2))
    ADD(LW(2), 50)
    ADD(LW(1), 30)
    CALL(_add_star_point_disp_offset, LW(10), LW(3), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("star_point"), 0, LW(3), LW(1), LW(2), LW(0), 0, 0, 0, 0, 0, 0, 0)
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        LOOP(LW(0))
        END_LOOP
    END_IF
    WAIT_FRAMES(120)
    CALL(btlevtcmd_GetBackItem, LW(10))
    CALL(btlevtcmd_KillUnit, LW(10), 1)
    CALL(eff_dead_delete)
    RETURN
EVT_END()

/**
 * Entry event: Magnus and Mario's partner exchange the lines of the boss's entrance (stg2_mri_e24_09 and 10),
 * then the partner returns to its pose.
 */
static EVT_BEGIN(entry_event)
    WAIT_FRAMES(120)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_prilimit, 1)
    CALL(evt_btl_camera_set_mode, 1, 3)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SUBTRACT(LW(0), 20)
    CALL(evt_btl_camera_set_moveto, 1, LW(0), 160, 600, LW(0), 110, -100, 20, 11)
    WAIT_FRAMES(20)
    CALL(evt_msg_print, 2, STRING("stg2_mri_e24_09"), 0, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_moveto, 1, -102, 83, 334, -102, 59, 0, 20, 11)
    WAIT_FRAMES(20)
    CALL(evt_msg_print_battle_party, STRING("stg2_mri_e24_10"))
    CALL(evt_btl_camera_set_prilimit, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    WAIT_MS(500)
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_PARTNER, LW(0))
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_PARTNER, LW(0))
    RETURN
EVT_END()

/**
 * Attack event of Magnus.
 * If the arms are out (work 0 = 1) and both have returned,
 * a counter counts down and when it is spent the arms are brought back (arm_return_event).
 * Then uses an enemy item if it has one.
 * With the arms on it uses the stamp (a stomp, always the first attack, with a line);
 * once the stamp scene has been done it rolls to either stamp again or shoot the arms off (arm_bunri_event);
 * with the arms out it does the shaking ceiling attack (shake_attack_event).
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARMS_OUT, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(arm_check, 0, LW(0))
        IF_INT_EQUAL(LW(0), -1)
            CALL(arm_check, 1, LW(0))
            IF_INT_EQUAL(LW(0), -1)
                CALL(btlevtcmd_AddUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARM_RETURN_TIMER, -1)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARM_RETURN_TIMER, LW(0))
                IF_INT_LESS_OR_EQUAL(LW(0), 0)
                    CALL_CHILD(arm_return_event)
                END_IF
            END_IF
        END_IF
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARMS_OUT, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_STAMP_SCENE_DONE, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL_CHILD(stamp_attack_event)
            GOTO(99)
        END_IF
        CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
        IF_INT_GREATER(LW(0), 20)
            CALL_CHILD(stamp_attack_event)
            GOTO(99)
        ELSE
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARMS_FIRED_ONCE, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL_CHILD(arm_bunri_event)
                GOTO(99)
            END_IF
            SET_VALUE(LW(0), 0)
            ADD(LW(0), 60)
            ADD(LW(0), 40)
            SUBTRACT(LW(0), 1)
            CALL(evt_sub_random, LW(0), LW(1))
            SET_VALUE(LW(0), 60)
            IF_INT_LESS(LW(1), LW(0))
                CALL_CHILD(stamp_attack_event)
                GOTO(99)
            ELSE
                CALL_CHILD(arm_bunri_event)
                GOTO(99)
            END_IF
        END_IF
    ELSE
        CALL_CHILD(shake_attack_event)
        GOTO(99)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The stamp attack: Magnus picks a target, the first time he says his line (stg2_mri_e24_11),
 * steps back 50 units, lifts a leg with the sounds and poses MGN_A2_1 to A2_4, and stamps the target;
 * the damage and result checks follow and he steps back to his place.
 */
EVT_BEGIN(stamp_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_batten_stamp_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_batten_stamp_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
        END_IF
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_STAMP_SCENE_DONE, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_STAMP_SCENE_DONE, 1)
        // The first time, the camera swings around and Magnus shouts out the name of his attack before it
        // starts.
        CALL(btlevtcmd_StatusWindowOnOff, 0)
        CALL(evt_btl_camera_set_prilimit, 1)
        CALL(evt_btl_camera_set_mode, 1, 3)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SUBTRACT(LW(0), 20)
        CALL(evt_btl_camera_set_moveto, 1, LW(0), 160, 600, LW(0), 110, -100, 20, 11)
        WAIT_FRAMES(20)
        CALL(evt_msg_print, 2, STRING("stg2_mri_e24_11"), 0, BTL_UNIT_SELF)
        CALL(evt_btl_camera_set_prilimit, 0)
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(btlevtcmd_StatusWindowOnOff, 1)
        WAIT_MS(500)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_batten_stamp_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_batten_stamp_attack))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 100)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    // He steps back 50 units to give himself room.
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, -50, 0, 0, 120, -1, 1)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    IF_INT_GREATER_OR_EQUAL(LW(0), -125)
        SET_VALUE(LW(15), 1)
    ELSE
        SET_VALUE(LW(15), 0)
    END_IF
    // He lifts a leg high (MGN_A2_1) with a hydraulic whine and the mechanism creaks (MGN_A2_2).
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_LEG_UP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_1"))
    WAIT_MS(450)
    BEGIN_SIBLING_EVENT
        LOOP(3)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_LEG_PERPLEX1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_MS(333)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_2"))
    // The leg comes slamming down on the target (MGN_A2_3 or A2_4, depending on how far away it is) and the
    // screen shakes.
    WAIT_MS(1000)
    IF_INT_EQUAL(LW(15), 1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_3"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_4"))
    END_IF
    WAIT_MS(150)
    CALL(evt_btl_camera_shake_h, 0, 5, 0, 60, 0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_batten_stamp_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(90)
        CASE_END
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(90)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(90)
        CASE_EQUAL(1)
        GOTO(91)
        CASE_END
        CASE_DEFAULT
        GOTO(98)
        CASE_END
    END_SWITCH
    // The stomp misses or is blocked: the target jumps clear.
    LABEL(90)
    GOTO(95)
    // The stomp lands: the Action Command defence result is applied and damage is dealt.
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_batten_stamp_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_batten_stamp_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(95)
    // After a pause he pulls the leg back up (MGN_A2_5 or A2_6) and returns to his place.
    LABEL(95)
    WAIT_MS(1000)
    IF_INT_EQUAL(LW(15), 1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_5"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_6"))
    END_IF
    WAIT_MS(1000)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(200)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 41)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, -2, 0)
    RETURN
EVT_END()

/**
 * The shake attack (weapon_batten_shake_attack, which hits every target on the other side):
 * Magnus pounds the ground (poses MGN_A3_3 and A3_4, quake sound, camera shake) and dust falls from the ceiling.
 * Mario, if he can act and is not Invisible, is put into his pose M_I_O while it runs;
 * then the damage check runs on each target in turn.
 */
static EVT_BEGIN(shake_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_batten_shake_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_batten_shake_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
        END_IF
        RETURN
    END_IF
    // Magnus raises himself (MGN_A3_3) to pound the ground.
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_batten_shake_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_batten_shake_attack))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A3_3"))
    WAIT_MS(900)
    CALL(btlevtcmd_CheckActStatus, BTL_UNIT_MARIO, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckStatus, BTL_UNIT_MARIO, STATUS_INVISIBLE, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_MARIO)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_I_O"))
        END_IF
    END_IF
    // He slams the floor (MGN_A3_4): a quake shakes the whole room and dust rains down from the ceiling.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_QUAKE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_CAILING1"), EVT_NULLPTR, 0, LW(15))
    CALL(evt_btl_camera_shake_h, 0, 7, 0, 30, 0)
    CALL(eff_hokori, 0, 250, 0, 80)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A3_4"))
    // Mario, if he can act, is put into his flinching pose while the quake runs.
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(20)
        CALL(eff_hokori, 100, 250, 0, 80)
        WAIT_FRAMES(20)
        CALL(eff_hokori, -100, 250, 0, 80)
        WAIT_FRAMES(20)
        CALL(eff_hokori, 50, 250, 0, 80)
        WAIT_FRAMES(20)
        CALL(eff_hokori, -100, 250, 0, 80)
        WAIT_FRAMES(20)
        CALL(evt_snd_sfxoff, LW(15))
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
        LOOP(12)
            WAIT_FRAMES(10)
            ADD_FLOAT(LW(0), FLOAT(0.69921875f))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_QUAKE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(evt_btl_camera_shake_h, 0, LW(0), 0, 10, 0)
        END_LOOP
        CALL(evt_btl_camera_shake_h, 0, 6, 0, 60, 0)
    END_SIBLING_EVENT
    // After the tremors die down he straightens up and the damage is worked out for each target in turn.
    WAIT_FRAMES(120)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    SET_VALUE(LW(6), 0)
    // For each target: a miss means they just recover, a hit applies the damage (the Action Command result is
    // applied once).
    LABEL(10)
    IF_INT_EQUAL(LW(3), -1)
        GOTO(95)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_batten_shake_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(90)
        CASE_END
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(90)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(90)
        CASE_EQUAL(1)
        GOTO(91)
        CASE_END
        CASE_DEFAULT
        GOTO(98)
        CASE_END
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_CheckActStatus, BTL_UNIT_MARIO, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckStatus, BTL_UNIT_MARIO, STATUS_INVISIBLE, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_MARIO)
            CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
        END_IF
    END_IF
    GOTO(93)
    LABEL(91)
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_batten_shake_attack))
        SET_VALUE(LW(6), 1)
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_batten_shake_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(93)
    LABEL(93)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    GOTO(10)
    // The camera resets after a one second pause.
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(1000)
    RETURN
EVT_END()

/**
 * The first time Magnus fires his arms off, he says a line (stg2_mri_e24_12),
 * then plays the arm launch poses (MGN_A1_1 to A1_3) and sounds.
 * Two rocket punch units are spawned (arms 0 and 1), linked to him through his unit work,
 * and he switches to the no-arm pose table.
 * Work 0 is set to 1 (arms out), work 2 to 1 and the counter in work 1 to 2.
 */
static EVT_BEGIN(arm_bunri_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARMS_FIRED_ONCE, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_StatusWindowOnOff, 0)
        CALL(evt_btl_camera_set_prilimit, 1)
        CALL(evt_btl_camera_set_mode, 1, 3)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SUBTRACT(LW(0), 20)
        CALL(evt_btl_camera_set_moveto, 1, LW(0), 160, 600, LW(0), 110, -100, 20, 11)
        WAIT_FRAMES(20)
        CALL(evt_msg_print, 2, STRING("stg2_mri_e24_12"), 0, BTL_UNIT_SELF)
        CALL(evt_btl_camera_set_prilimit, 0)
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(btlevtcmd_StatusWindowOnOff, 1)
        WAIT_MS(500)
    END_IF
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARMS_OUT, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARMS_FIRED_ONCE, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARM_RETURN_TIMER, 2)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_PUNCH_ACTIVE1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A1_1"))
    WAIT_MS(600)
    CALL(evt_snd_sfxoff, LW(15))
    WAIT_MS(200)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_PUNCH_STOP1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A1_2"))
    WAIT_MS(500)
    CALL(evt_snd_sfxoff, LW(15))
    WAIT_MS(100)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A1_3"))
    WAIT_MS(100)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_PUNCH_IGNITE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_btl_camera_shake_w, 0, 3, 0, 20, 0)
    WAIT_MS(100)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_rocket_punch), 0)
    CALL(btlevtcmd_SetUnitWork, LW(3), UW_ROCKET_PUNCH_ROLE, 0)
    CALL(btlevtcmd_SetUnitWork, LW(3), UW_ROCKET_PUNCH_WAIT_TURNS, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARM_0, LW(3))
    CALL(btlevtcmd_AnimeChangePoseType, LW(3), 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_SpawnUnit, LW(4), PTR(&entry_rocket_punch), 0)
    CALL(btlevtcmd_SetUnitWork, LW(4), UW_ROCKET_PUNCH_ROLE, 1)
    CALL(btlevtcmd_SetUnitWork, LW(4), UW_ROCKET_PUNCH_WAIT_TURNS, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARM_1, LW(4))
    CALL(btlevtcmd_AnimeChangePoseType, LW(4), 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_no_arm))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    WAIT_MS(1500)
    RETURN
EVT_END()

/**
 * Brings the arms back: the arms-out flag is cleared,
 * the arm return pose (MGN_A1_6) plays and two rocket punch units are spawned as the returning arms,
 * which fly in from the right with the fly sound and ease back onto the body;
 * the arm trails are removed, the reattach poses (MGN_A1_7 and A1_8) play and the normal pose table returns.
 */
static EVT_BEGIN(arm_return_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARMS_OUT, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A1_6"))
    WAIT_MS(600)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_rocket_punch), 0)
    CALL(btlevtcmd_SetUnitWork, LW(3), UW_ROCKET_PUNCH_ROLE, 2)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARM_0, LW(3))
    CALL(btlevtcmd_AnimeChangePoseType, LW(3), 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_SpawnUnit, LW(4), PTR(&entry_rocket_punch), 0)
    CALL(btlevtcmd_SetUnitWork, LW(4), UW_ROCKET_PUNCH_ROLE, 3)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_ARM_1, LW(4))
    CALL(btlevtcmd_AnimeChangePoseType, LW(4), 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_PUNCH_FLY1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetPos, LW(3), 300, 40, -100)
        CALL(btlevtcmd_DivePosition, LW(3), 30, 100, -40, 30, -10, 0, 0, -1)
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetPos, LW(4), 350, 40, 100)
    CALL(btlevtcmd_DivePosition, LW(4), 80, 100, 40, 30, -10, 0, 0, -1)
    CALL(arm_end, 0)
    CALL(arm_end, 1)
    CALL(btlevtcmd_KillUnit, LW(3), 0)
    CALL(btlevtcmd_KillUnit, LW(4), 0)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_PUNCH_IGNITE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_btl_camera_shake_w, 0, 3, 0, 20, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A1_7"))
    WAIT_MS(300)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A1_8"))
    WAIT_MS(600)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    WAIT_MS(500)
    RETURN
EVT_END()

/** Idle script of Magnus: plays its idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Unit data of Magnus' rocket fist: 2 HP, 50x34 units in size; ties together its sounds, parts,
 * status vulnerability, init event and event table.
 */
BattleUnitKind unit_boss_rocket_punch = {
    35,
    "btl_un_rocket_punch",
    2,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    10,
    50,
    34,
    0,
    15,
    0.0f,
    0.0f,
    0.0f,
    0,
    -20,
    0.0f,
    0.0f,
    0.0f,
    25.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    25.0f,
    0.0f,
    0.0f,
    24.0f,
    16.0f,
    0.0f,
    -5.0f,
    0.0f,
    0.0f,
    50.0f,
    34.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_MBTN_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_FLOATING,
    &regist_r,
    1,
    parts_r,
    init_event_r,
    data_table_r,
};

/** Defence of Magnus' rocket fist: 0 against every kind of hit. */
static BattleUnitDefense defence_r = {{0, 0, 0, 0, 0}};

/** Defence attributes of Magnus' rocket fist: none, every element hits it normally. */
static BattleUnitDefenseAttr defence_attr_r = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Demo builds: Status vulnerability of Magnus' rocket fist (percent chance each status takes hold):
 * immune to sleep, Huge, Tiny, Attack Down, fright, Dodgy, Invisible, instant KO; the rest take hold at 80%
 * or better.
 */
static StatusVulnerability regist_r = {0, 80, 80, 80, 80, 80, 100, 80, 0, 0, 100, 0, 100, 80, 80, 0, 110, 100, 80, 0, 0, 0};
#else
/**
 * Retail builds: Status vulnerability of Magnus' rocket fist (percent chance each status takes hold):
 * immune to sleep, Huge, Tiny, Attack Down, fright, Dodgy, Invisible, instant KO; the rest take hold at 80%
 * or better.
 */
static StatusVulnerability regist_r = {0, 80, 80, 100, 80, 100, 100, 80, 0, 0, 100, 0, 100, 95, 80, 0, 100, 100, 80, 0, 0, 0};
#endif

/** Pose table of Magnus' rocket fist: maps its battle poses to its animations (MGN_*). */
static PoseTableEntry pose_table_r[] = {
    {1, "MGN_A1_9"},
    {2, "MGN_A1_4"},
    {9, "MGN_A1_4"},
    {5, "MGN_A1_9"},
    {4, "MGN_A1_9"},
    {3, "MGN_A1_9"},
    {BTL_POSE_NORMAL, "MGN_A1_9"},
    {29, "MGN_A1_9"},
    {30, "MGN_A1_9"},
    {31, "MGN_A1_9"},
    {BTL_POSE_DAMAGE, "MGN_A1_9"},
    {BTL_POSE_DANGER, "MGN_A1_9"},
    {BTL_POSE_PERIL, "MGN_A1_9"},
    {BTL_POSE_STAY_DEFAULT, "MGN_A1_9"},
};

/** Event table of Magnus' rocket fist: it has no special event scripts. */
static BattleDataEntry data_table_r[] = {
    {0, NULL},
};

/** Parts of Magnus' rocket fist: 1 part (model c_mb_robo_1b). */
static BattleUnitKindPart parts_r[] = {
    {1, "btl_un_rocket_punch", "c_mb_robo_1b", 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 10.0f, 0.0f, 106, 174, 255, &defence_r, &defence_attr_r, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, 0, pose_table_r},
};

/**
 * Weapon of Magnus (batten rocket attack): targets one unit for 4 damage; used by attack_event_r.
 */
static BattleWeapon weapon_batten_rocket_attack = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, // baseFpCost..baseSpCost
    2, // superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
#if VERSION <= VERSION_DEMO_JP
    COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_PAYBACK | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
#else
    COUNTER_RESIST_ALL, // counterResistFlags
#endif
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Init script of a rocket arm (X-Fist), run when arm_bunri_event spawns it:
 * plays its pose, sets its base rotation, creates the trail effect for its side, starts the arm_event loop and,
 * depending on which arm it is, flies it out from beside Magnus with the fly sound
 * and settles it at its resting place: the flight of the arm being fired off.
 */
static EVT_BEGIN(init_event_r)
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_NO_BACKFACE_FLIP)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A1_4"))
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event_r))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event_r))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event_r))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetBaseRotate, BTL_UNIT_SELF, 0, -90, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_ROLE, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(arm_init2, 0)
    END_IF
    IF_INT_EQUAL(LW(0), 2)
        CALL(arm_init2, 0)
    END_IF
    IF_INT_EQUAL(LW(0), 1)
        CALL(arm_init2, 1)
    END_IF
    IF_INT_EQUAL(LW(0), 3)
        CALL(arm_init2, 1)
    END_IF
    SPAWN_EVENT(arm_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_ROLE, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 30, 100, -40)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, -100, 150, -60, 20, 0, 4, 0, -1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_PUNCH_FLY1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, 350, 110, -80, 30, 50, 0, 0, -1)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, 30, 60, -40, 25, -30, 4, 0, -1)
        CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, 30, 60, -40)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    END_IF
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 80, 100, 40)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, -50, 150, 60, 20, 0, 4, 0, -1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_PUNCH_FLY1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, 300, 120, 80, 30, 50, 0, 0, -1)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, 80, 60, 40, 30, -30, 4, 0, -1)
        CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, 80, 60, 40)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    END_IF
    RETURN
EVT_END()

/**
 * Loop that runs for as long as the arm exists: updates the arm trail every frame (arm_main) for its side;
 * ends the trail when the unit is gone.
 */
static EVT_BEGIN(arm_event)
    LABEL(0)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        CALL_CHILD(arm_event_end)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_ROLE, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(arm_main, BTL_UNIT_SELF, 0)
    END_IF
    IF_INT_EQUAL(LW(0), 2)
        CALL(arm_main, BTL_UNIT_SELF, 0)
    END_IF
    IF_INT_EQUAL(LW(0), 1)
        CALL(arm_main, BTL_UNIT_SELF, 1)
    END_IF
    IF_INT_EQUAL(LW(0), 3)
        CALL(arm_main, BTL_UNIT_SELF, 1)
    END_IF
    GOTO(0)
    LABEL(99)
    RETURN
EVT_END()

/** Ends the trail effects of arm slots 0 and 1 (each of the two arm units owns one). */
static EVT_BEGIN(arm_event_end)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_ROLE, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(arm_end, 0)
    END_IF
    IF_INT_EQUAL(LW(0), 2)
        CALL(arm_end, 0)
    END_IF
    IF_INT_EQUAL(LW(0), 1)
        CALL(arm_end, 1)
    END_IF
    IF_INT_EQUAL(LW(0), 3)
        CALL(arm_end, 1)
    END_IF
    RETURN
EVT_END()

/** Damage event of a rocket arm: runs the default damage reaction; when the arm dies its trail is ended. */
static EVT_BEGIN(damage_event_r)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, DAMAGE_FLAG_KO, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, DAMAGE_FLAG_LIFE_SHROOM, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL_CHILD(arm_event_end)
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Attack event of a rocket arm (weapon_batten_rocket_attack): it acts only every other turn (unit work 1 counts
 * down).
 * It picks a target and, by a coin flip, either swoops in low in front of it and shoots through it off the
 * left edge, or dives on it from high behind; the damage check runs as it passes the target.
 * It then re-enters from the right edge (x 300) and flies back to its resting place.
 */
static EVT_BEGIN(attack_event_r)
    // The rocket fist only acts every other turn (a counter in unit work 1 counts down).
    CALL(btlevtcmd_AddUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_WAIT_TURNS, -1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_WAIT_TURNS, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_WAIT_TURNS, 1)
    // It picks a target; a confused fist with no target is flustered.
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_batten_rocket_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_batten_rocket_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
        END_IF
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    // A coin flip decides whether it comes in low in front of its target or dives from high behind it.
    CALL(evt_sub_random, 1, LW(6))
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_batten_rocket_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_batten_rocket_attack))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    // The fist aims itself (MGN_A1_4).
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A1_4"))
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_batten_rocket_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(90)
        CASE_END
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(90)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(90)
        CASE_EQUAL(1)
        GOTO(91)
        CASE_END
        CASE_DEFAULT
        GOTO(98)
        CASE_END
    END_SWITCH
    LABEL(90)
    GOTO(95)
    // As the fist passes the target, the Action Command defence result and damage are applied and the screen
    // shakes.
    LABEL(91)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(10), LW(11), LW(12))
            IF_INT_LESS_OR_EQUAL(LW(10), LW(0))
                CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_batten_rocket_attack))
                CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_batten_rocket_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
                CALL(evt_btl_camera_shake_w, 0, 3, 0, 10, 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    GOTO(95)
    // The fist flies on past its target in one of two ways (low and straight through, or in a dive from
    // above) and off the left edge.
    LABEL(95)
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 110)
        SET_VALUE(LW(1), 120)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_PUNCH_FLY1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 10, 4, 0, -1)
        WAIT_FRAMES(5)
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), -20)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_PUNCH_FLY1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, -250, 0, LW(2), 20, -10, 0, 0, -1)
    ELSE
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), -200)
        ADD(LW(1), 140)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_PUNCH_FLY1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, -80, 1, 0, -1)
    END_IF
    WAIT_MS(250)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_ROLE, LW(10))
    IF_INT_EQUAL(LW(10), 0)
        // It reappears from the right edge of the screen (x 300).
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 300, LW(1), -100)
    ELSE
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 300, LW(1), 100)
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_PUNCH_FLY1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 0, 4, 0, -1)
    // The fist settles back at its resting place and the camera resets.
    LABEL(99)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Idle script of a rocket arm: resets its rotation and plays its idle pose. */
static EVT_BEGIN(wait_event_r)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    LABEL(0)
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

/** Allocates the trail data for the two arms (slots 0 and 1) and clears their positions. */
static USER_FUNC(arm_init) {
    s32 i;

    for (i = 0; i < 2; i++) {
        work[i] = BattleAlloc(sizeof(ArmWork));
        work[i]->prevPos = work[i]->pos = (Vec){0.0f, 0.0f, 0.0f};
    }
    return EVT_RETURN_DONE;
}

/** Creates the arm trail effect (a Batten-style streak) for arm slot args[0], hidden at y -1000 until it moves. */
static USER_FUNC(arm_init2) {
    s32 idx = evtGetValue(event, event->args[0]);
    ArmWork* arm = work[idx];

    arm->eff = effBattenEntry(3, 1000, 0.0f, -1000.0f, 0.0f, 1.0f);
    return EVT_RETURN_DONE;
}

/**
 * Per-frame update of an arm's trail: reads the arm's position,
 * turns the arm to the angle of its path (easing a third of the way each frame while its wait event is not
 * running), builds the arm's rotation matrix and puts the trail effect 18 units behind it, along its rotation.
 */
static USER_FUNC(arm_main) {
    EvtWord* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id = evtGetValue(event, args[0]);
    s32 idx = evtGetValue(event, args[1]);
    ArmWork* arm = work[idx];
    EffBattenWork* eff;
    f32 x, y, z;
    f32 rx, ry, rz;
    f32 bx, by, bz;
    Mtx m;
    Mtx rot;
    Vec ofs;
    f32 dx, dy;

    if (arm->eff == NULL) {
        return EVT_RETURN_DONE;
    }
    eff = arm->eff->userdata;
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    BtlUnit_GetPos(unit, &x, &y, &z);
    arm->prevPos = arm->pos;
    {
        Vec p = {0.0f, 0.0f, 0.0f};

        p.x = x;
        p.y = y;
        p.z = z;
        arm->pos = p;
    }
    if (evtCheckID(unit->waitEventId) != TRUE) {
        dx = arm->pos.x - arm->prevPos.x;
        dy = arm->pos.y - arm->prevPos.y;
        if (dx != 0.0f) {
            arm->targetRot = 360.0f * (f32)atan(dy / dx) / 6.283184f;
            arm->rot += (arm->targetRot - arm->rot) / 3.0f;
            BtlUnit_GetRotate(unit, &rx, &ry, &rz);
            BtlUnit_SetRotate(unit, rx, ry, arm->rot);
        } else {
            arm->targetRot = 0.0f;
        }
    }
    BtlUnit_GetBaseRotate(unit, &bx, &by, &bz);
    BtlUnit_GetRotate(unit, &rx, &ry, &rz);
    rx += bx;
    ry += by;
    rz += bz;
    PSMTXRotRad(m, 'x', 1.5707964f);
    PSMTXRotRad(rot, 'y', 0.017453292f * ry);
    PSMTXConcat(rot, m, m);
    PSMTXRotRad(rot, 'x', 0.017453292f * rx);
    PSMTXConcat(rot, m, m);
    PSMTXRotRad(rot, 'z', 0.017453292f * rz);
    PSMTXConcat(rot, m, m);
    PSMTXCopy(m, eff->mtx);
    ofs = (Vec){0.0f, -18.0f, 0.0f};
    PSMTXMultVec(m, &ofs, &ofs);
    eff->position.x = arm->pos.x + ofs.x;
    eff->position.y = arm->pos.y + ofs.y;
    eff->position.z = arm->pos.z + ofs.z;
    return EVT_RETURN_DONE;
}

/** Removes the trail effect of arm slot args[0]. */
static USER_FUNC(arm_end) {
    s32 idx = evtGetValue(event, event->args[0]);
    ArmWork* arm = work[idx];

    if (arm->eff != NULL) {
        effDelete(arm->eff);
        arm->eff = NULL;
    }
    return EVT_RETURN_DONE;
}
