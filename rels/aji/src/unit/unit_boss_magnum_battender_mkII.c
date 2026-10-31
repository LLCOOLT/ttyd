// X-Naut Fortress (aji) battle unit: Magnus von Grapple 2.0 (magnum_battender_mkII): its parts, defence/status tables,
// and attack events.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "manager/evtmgr_cmd.h"
#include "driver/effdrv.h"
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "manager/evtmgr.h"
#include "dolphin/mtx.h"
#include "eff/n64/eff_akari_charge_n64.h"
#include "battle/battle_audience.h"
#include "evt/evt_cmd.h"
#include "eff/eff_kemu_test.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_batstage.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "eff/eff_batten.h"
#include "eff/n64/eff_kameki_tornade_n64.h"
#include "eff/n64/eff_kumokumo_n64.h"
#include "evt/evt_audience.h"
#include "evt/evt_msg.h"
#include "evt/evt_sub.h"
#include "pmario_sound.h"
#include "unit/unit_boss_magnum_battender.h"
#include "system.h"
#include "version.h"
#include "libc_decls.h"

// Unit work slots of Magnus von Grapple 2.0 (btlevtcmd_SetUnitWork / GetUnitWork).
enum {
    UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT = 0,         // 1 while its fists are detached
    UW_BOSS_MAGNUM_BATTENDER_MKII_ARM_RETURN_TIMER = 1, // turns left before the fists are called back once both are gone
    UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_SEPARATED = 2,   // 1 once the arms have been split off (the close-up plays only the first time)
    UW_BOSS_MAGNUM_BATTENDER_MKII_LEFT_FIST = 3,        // unit id of the left rocket punch
    UW_BOSS_MAGNUM_BATTENDER_MKII_RIGHT_FIST = 4,       // unit id of the right rocket punch
    UW_BOSS_MAGNUM_BATTENDER_MKII_DRILL_USED = 5,       // 1 once the drill attack has been used
    UW_BOSS_MAGNUM_BATTENDER_MKII_LOW_HP_TALK_DONE = 6, // 1 once the 14 HP line has played, or once it is defeated
    UW_BOSS_MAGNUM_BATTENDER_MKII_AUD_ATTACK_USED = 7,  // 1 once the audience attack has been used
    UW_BOSS_MAGNUM_BATTENDER_MKII_AUD_ATTACK_HIT = 8,   // 1 once a round of the audience attack has hit
};

// Unit work slots of a rocket punch fist (unit_boss_rocket_punch_mkII).
enum {
    UW_ROCKET_PUNCH_MKII_SIDE = 0,      // 0 left, 1 right; 2 left and 3 right for fists that come back
    UW_ROCKET_PUNCH_MKII_TURN_WAIT = 1, // counts down each turn; it attacks only when this reaches 0 (every other turn)
};

typedef struct TargetWork {
    s32 state;
    s32 count;
    EffectEntry* eff;
} TargetWork;
extern EvtWord aud_hit_event[];
static void aud_get_pod_pos(BattleUnit* unit, f32* x, f32* y, f32* z);
static void aud_fire_eff(f32 x, f32 y, f32 z);
EffectEntry* eff_tor;
s32 torCount;
EffectEntry* eff_jet[2];
s32 jetCount;
static s32* list;
EffectEntry* eff_suikomi;
s32 screamId;
#if VERSION >= VERSION_JP
s32 scream_fade_timer;
u8 scream_fade_start_vol;
u8 scream_fade_vol;
#endif
TargetWork* wp_target;
s32 targetSoundId;
static EffectEntry* eff_charge;
static ArmWork* work[2];

static USER_FUNC(arm_check);
static USER_FUNC(arm_end);
static USER_FUNC(arm_init);
static USER_FUNC(arm_main);
static USER_FUNC(waku_main);
static USER_FUNC(arm_init2);
static USER_FUNC(eff_dead_delete);
static USER_FUNC(eff_dead);
static void aud_fire_eff(f32 x, f32 y, f32 z);
static void aud_get_pod_pos(BattleUnit* unit, f32* x, f32* y, f32* z);

BattleUnitKind unit_boss_magnum_battender_mkII;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[17];
static PoseTableEntry pose_table_no_arm[16];
static BattleDataEntry data_table[2];
static BattleUnitKindPart parts[4];
BattleWeapon weapon_batten_drill_attack;
BattleWeapon weapon_batten_boomerang_attack;
BattleWeapon weapon_batten_aud_attack;
static BattleUnitSetup entry_rocket_punch;
extern EvtWord aud_hit_event[];
extern EvtWord aud_no_hit_event[];
static EvtWord init_event[92];
static EvtWord waku_event[23];
static EvtWord damage_event[111];
#if VERSION <= VERSION_DEMO_US
static EvtWord dead_event[216];
#else
static EvtWord dead_event[234];
#endif
static EvtWord entry_event[78];
static EvtWord attack_event[320];
extern EvtWord drill_attack_event[];
extern EvtWord boomerang_attack_event[];
extern EvtWord aud_attack_event[];
extern EvtWord aud_attack_event_sub[];
static EvtWord arm_bunri_event[199];
static EvtWord arm_return_event[151];
static EvtWord wait_event[6];
BattleUnitKind unit_boss_rocket_punch_mkII;
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

/** Unit data of Magnus von Grapple 2.0: 70 HP, level 84; the battle starts it from init_event. */
BattleUnitKind unit_boss_magnum_battender_mkII = {
    121,
    "btl_un_magnum_battender_mkii",
    70,
    0,
    1,
    1,
    84,
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
#if VERSION <= VERSION_DEMO_US
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
    4,
    parts,
    init_event,
    data_table,
};

/** Defence of Magnus von Grapple 2.0: 2 against every element. */
static BattleUnitDefense defence = {{2, 2, 2, 2, 2}};

/** Elemental reactions of Magnus von Grapple 2.0: none, every element hurts it normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
/**
 * Status vulnerability of Magnus von Grapple 2.0 (percent, 100 is normal) in the demo builds: immune to
 * sleep, poison, electric, Huge, Tiny, Attack Down, fright, Gale Force, Dodgy, Invisible and instant KO;
 * resists most statuses (20-40%).
 */
static StatusVulnerability regist = {0, 40, 40, 0, 40, 0, 100, 20, 0, 0, 100, 0, 100, 40, 40, 0, 0, 100, 30, 0, 0, 0};
#else
/**
 * Status vulnerability of Magnus von Grapple 2.0 (percent, 100 is normal) in the retail builds: immune to
 * sleep, poison, electric, Huge, Tiny, Attack Down, fright, Gale Force, Dodgy, Invisible and instant KO;
 * resists most statuses (20-80%).
 */
static StatusVulnerability regist = {0, 40, 40, 0, 40, 0, 100, 20, 0, 0, 100, 0, 100, 80, 40, 0, 0, 100, 30, 0, 0, 0};
#endif

/**
 * Pose table of Magnus von Grapple 2.0: the animation each battle pose (idle, hurt, walk, attack and so on)
 * plays.
 */
static PoseTableEntry pose_table[] = {
    {1, "MGN_S_1"},
    {2, "MGN_2D_1"},
    {9, "MGN_2D_1"},
    {5, "MGN_X_1"},
#if VERSION <= VERSION_DEMO_US
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

/** Pose table of Magnus von Grapple 2.0 once his arms have split off (poses without the fists). */
static PoseTableEntry pose_table_no_arm[] = {
    {1, "MGN_S_2"},
    {2, "MGN_2D_2"},
    {9, "MGN_2D_2"},
    {5, "MGN_X_2"},
#if VERSION <= VERSION_DEMO_US
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

/** Event table of Magnus von Grapple 2.0: its defeat (dead_event, tag 49). */
static BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

/**
 * Parts of Magnus von Grapple 2.0: part 1 is his body (the target), part 2 an extra part, part 3 the frame
 * piece that follows the body's locator17 bone, and part 4 the boomerang that splits off his body.
 */
static BattleUnitKindPart parts[] = {
#if VERSION >= VERSION_US
    {1, "btl_un_magnum_battender_mkii", "c_mb_robo_2b", 0.0f, 0.0f, 0.0f, 37.0f, 103.0f, 30.0f, 37.0f, 113.0f, 61.0f, 106, 174, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_NOT_ANY_PART_TARGET | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, 0, pose_table},
#else
    {1, "btl_un_magnum_battender_mkii", "c_mb_robo_2b", 0.0f, 0.0f, 0.0f, 37.0f, 103.0f, 30.0f, 37.0f, 113.0f, 61.0f, 106, 174, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, 0, pose_table},
#endif
    {2, "btl_un_magnum_battender_mkii", "c_mb_robo_2b", 0.0f, 0.0f, 0.0f, 10.0f, 10.0f, 30.0f, 10.0f, 20.0f, 61.0f, 106, 174, 255, &defence, &defence_attr, PART_ATTR_IMPORTANT | PART_ATTR_JUMPLIKE_CANNOT_TARGET | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, 0, pose_table},
    {3, "btl_un_magnum_battender_mkii", "c_mb_robo_2b", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {4, "btl_un_magnum_battender_mkii", "c_mb_robo_2b", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
};

/** Weapon data for Magnus von Grapple 2.0's drill attack: 6 damage, a jump-type hit, one target. */
BattleWeapon weapon_batten_drill_attack = {
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
    {6, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
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

/** Weapon data for Magnus von Grapple 2.0's boomerang: 6 damage, every target. */
BattleWeapon weapon_batten_boomerang_attack = {
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
    {6, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
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

/** Weapon data for Magnus von Grapple 2.0's audience attack: 3 damage, one target. */
BattleWeapon weapon_batten_aud_attack = {
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
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
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

/** Setup for the X-Punch fists that Magnus von Grapple 2.0 spawns when he splits off his arms. */
static BattleUnitSetup entry_rocket_punch = {
    &unit_boss_rocket_punch_mkII, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Event run on a thrown audience member that hit its target in the Magnus von Grapple 2.0 audience attack:
 * moves it to the hit position over LW(5) frames, makes it jump away along an arc,
 * deletes it and lowers the audience size by one.
 */
EVT_BEGIN(aud_hit_event)
    CALL(evt_audience_move_position_frame, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5))
    CALL(evt_audience_jump_position_gravity, LW(0), LW(6), LW(7), LW(8), LW(9), LW(10))
    CALL(evt_audience_delete, LW(0))
    CALL(evt_audience_num_updown_in_event, FLOAT(-1.0f))
    RETURN
EVT_END()

/**
 * Event run on a thrown audience member that missed:
 * moves it over LW(5) frames to the miss position, deletes it and lowers the audience size by one.
 */
EVT_BEGIN(aud_no_hit_event)
    CALL(evt_audience_move_position_frame, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5))
    CALL(evt_audience_delete, LW(0))
    CALL(evt_audience_num_updown_in_event, FLOAT(-1.0f))
    RETURN
EVT_END()

/**
 * Script function: keeps the frame part (part 3) of the boss on the locator17 bone of its body part
 * and turns it to face the camera each frame; args[0] is the unit.
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
 * Script function: looks for one of the boss's two punching arms (UNIT_X_FIST or UNIT_X_PUNCH) by side,
 * args[0] = 0 for the arms with work[0] of 0 or 2 and 1 for those with 1 or 3.
 * Returns the unit ID in args[1], or -1 if there is none.
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
            if (side == 0 && (unit->work[UW_ROCKET_PUNCH_MKII_SIDE] == 0 || unit->work[UW_ROCKET_PUNCH_MKII_SIDE] == 2)) {
                found = i;
                break;
            }
            if (side == 1 && (unit->work[UW_ROCKET_PUNCH_MKII_SIDE] == 1 || unit->work[UW_ROCKET_PUNCH_MKII_SIDE] == 3)) {
                found = i;
                break;
            }
        }
    }
    evtSetValue(event, args[1], found);
    return EVT_RETURN_DONE;
}

/**
 * Script function that plays the tornado effect under the boss during the drill attack for 70 frames,
 * following the unit's X and Z and staying 240 units below it (only while it is below 300 high),
 * then deletes it.
 */
static USER_FUNC(drill_tor) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;

    BtlUnit_GetPos(unit, &x, &y, &z);
    if (isFirstCall) {
        eff_tor = effKamekiTornadeN64Entry(0, 1000, 0.0f, -1000.0f, 0.0f, 3.5f);
        torCount = 0;
    }
    if (y <= 300.0f) {
        ((EffBattenWork*)eff_tor->userdata)->position.x = x;
        ((EffBattenWork*)eff_tor->userdata)->position.y = y - 240.0f;
        ((EffBattenWork*)eff_tor->userdata)->position.z = z;
    }
    if (++torCount >= 70) {
        effDelete(eff_tor);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

/**
 * Script function that plays the drill attack's jet flames at two points next to the unit args[0] for 90 frames,
 * then deletes them.
 */
static USER_FUNC(drill_jet) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    EffBattenWork* ew;

    BtlUnit_GetPos(unit, &x, &y, &z);
    if (isFirstCall) {
        for (i = 0; i < 2; i++) {
            eff_jet[i] = effBattenEntry(3, 1000, 0.0f, -1000.0f, 0.0f, 3.0f);
        }
        jetCount = 0;
    }
    ew = eff_jet[0]->userdata;
    ew->position.x = x - 20.0f;
    ew->position.y = y;
    ew->position.z = z - 20.0f;
    ew = eff_jet[1]->userdata;
    ew->position.x = 20.0f + x;
    ew->position.y = y;
    ew->position.z = 20.0f + z;
    if (++jetCount >= 90) {
        for (i = 0; i < 2; i++) {
            effDelete(eff_jet[i]);
        }
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

/**
 * Script function that shows the two jet flames of the audience-attack pod at fixed offsets from the unit
 * args[0], tilted 20 degrees, until aud_jet_end sets jetCount to 1.
 */
static USER_FUNC(aud_jet) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    Mtx mtx;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    EffBattenWork* ew;

    BtlUnit_GetPos(unit, &x, &y, &z);
    if (isFirstCall) {
        for (i = 0; i < 2; i++) {
            eff_jet[i] = effBattenEntry(3, 1000, 0.0f, -1000.0f, 0.0f, 3.0f);
        }
        jetCount = 0;
    }
    PSMTXRotRad(mtx, 'z', -0.34906584f);
    ew = eff_jet[0]->userdata;
    ew->position.x = x - 60.0f;
    ew->position.y = 22.5f + y;
    ew->position.z = z;
    PSMTXCopy(mtx, ((EffBattenWork*)eff_jet[0]->userdata)->mtx);
    ew = eff_jet[1]->userdata;
    ew->position.x = x - 15.0f;
    ew->position.y = 22.5f + y;
    ew->position.z = 70.0f + z;
    PSMTXCopy(mtx, ((EffBattenWork*)eff_jet[1]->userdata)->mtx);
    if (jetCount == 1) {
        for (i = 0; i < 2; i++) {
            effDelete(eff_jet[i]);
        }
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

/** Script function: tells aud_jet to end by setting jetCount to 1. */
static USER_FUNC(aud_jet_end) {
    jetCount = 1;
    return EVT_RETURN_DONE;
}

/** Script function: returns the current number of audience members in args[0]. */
static USER_FUNC(get_aud_num) {
    EvtWord* args = event->args;

    evtSetValue(event, args[0], BattleAudience_GetAudienceNum());
    return EVT_RETURN_DONE;
}

/**
 * Script function for the audience attack's suction:
 * picks 20 random audience members, makes them spin
 * and fly toward the boss's pod (a dust-cloud effect and SFX_AUDIENCE_PANIC_SCREAM1 start),
 * and removes each when it arrives. The list of 20 is kept for the shots that follow.
 * Blocks until all 20 arrived.
 */
static USER_FUNC(aud_suikomi) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    s32 done = 0;
    BattleAudienceMember* mem;
    s32 i;
    s32 j;
    f32 x;
    f32 y;
    f32 z;
    f32 x2;
    f32 y2;
    f32 z2;
    s32 ids[200];

    if (isFirstCall) {
        s32 n = 0;

        if (list != NULL) {
            BattleFree(list);
        }
        list = BattleAlloc(sizeof(s32) * 20);
        for (i = 0; i < 200; i++) {
            if ((u8)BattleAudience_GetExist(i) == TRUE) {
                ids[n] = i;
                n++;
            }
        }
        for (i = 0; i < 1000; i++) {
            s32 a = irand(n);
            s32 b = irand(n);
            s32 tmp = ids[a];

            ids[a] = ids[b];
            ids[b] = tmp;
        }
        for (i = 0; i < 20; i++) {
            mem = BattleAudienceGetPtr(ids[i]);
            mem->flags |= MEMBER_FLAG_EVT_CTRL;
            BattleAudience_SetAnim(ids[i], 9, FALSE);
            mem->interpFramesTotal = i * 3 + 60;
            mem->counter = 0;
            mem->rotation.y = 0.0f;
            list[i] = ids[i];
        }
        BtlUnit_GetPos(BattleGetUnitPtr(_battleWorkPointer, id), &x, &y, &z);
        eff_suikomi = effKumokumoN64Entry(2, 120, x - 10.0f, 10.0f + y, z, -40.0f, 1.0f, 1.5f);
        screamId = psndSFXOn("SFX_AUDIENCE_PANIC_SCREAM1");
    }
    BtlUnit_GetPos(BattleGetUnitPtr(_battleWorkPointer, id), &x2, &y2, &z2);
    y2 += 5.0f;
    for (i = 0; i < 200; i++) {
        for (j = 0; j < 20; j++) {
            if (i == list[j]) {
                mem = BattleAudienceGetPtr(i);
                mem->rotation.y += 19.0f;
                if (mem->interpFramesLeft < mem->interpFramesTotal) {
                    mem->interpFramesLeft++;
                } else {
                    done++;
                    mem->flags &= ~MEMBER_FLAG_VISIBLE;
                    mem->flags |= MEMBER_FLAG_REMOVED;
                }
                mem->position.x = intplGetValue(4, mem->homePosition.x, x2, mem->interpFramesLeft, mem->interpFramesTotal);
                mem->position.y = intplGetValue(2, mem->homePosition.y, y2, mem->interpFramesLeft, mem->interpFramesTotal);
                mem->position.z = intplGetValue(4, mem->homePosition.z, z2, mem->interpFramesLeft, mem->interpFramesTotal);
                mem->baseScale.x = mem->baseScale.y = intplGetValue(4, 1.0f, 0.65f, mem->interpFramesLeft, mem->interpFramesTotal);
                break;
            }
        }
    }
#if VERSION <= VERSION_DEMO_US
    // The audience scream stops as soon as the last member is pulled in.
    if (done < 20) {
        return EVT_RETURN_BLOCK;
    }
    psndSFXOff(screamId);
    return EVT_RETURN_DONE;
#else
    return done < 20 ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
#endif
}

#if VERSION >= VERSION_JP
/** Script function (JP and later): fades the audience scream sound (screamId) out over 120 frames after the suction. */
static USER_FUNC(aud_scream_fadeout) {
    if (isFirstCall) {
        scream_fade_timer = 120;
        scream_fade_start_vol = psndSFX_get_vol(screamId);
    }
    scream_fade_timer--;
    scream_fade_vol = intplGetValue(0, scream_fade_start_vol, 0.0f, 120 - scream_fade_timer, 120);
    psndSFX_vol(screamId, scream_fade_vol);
    if (scream_fade_timer <= 0) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
#endif

/** Returns the position of the boss's pod, 10 units right of and 78 above the unit, for the audience cannon. */
static void aud_get_pod_pos(BattleUnit* unit, f32* x, f32* y, f32* z) {
    BtlUnit_GetPos(unit, x, y, z);
    *x += 10.0f;
    *y += 78.0f;
}

/** Starts the smoke puff (kemuri_test effect) at the pod's muzzle for each audience shot. */
static void aud_fire_eff(f32 x, f32 y, f32 z) {
    effKemuTestSetRxRz(effKemuTestEntry(11, x - 50.0f, 20.0f + y, 50.0f + z, 0.75f), 40.0f, 110.0f);
}

/**
 * Script function: fires two audience members from the pod at the target args[1] (the unit args[0] is the boss,
 * args[2] the first of the sucked-in members, list[start]):
 * each flies a throwing arc to the target's hit position with aud_hit_event; used when the shot hits.
 */
static USER_FUNC(aud_fire_hit) {
    EvtWord* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 target = BattleTransID(event, evtGetValue(event, args[1]));
    s32 start = evtGetValue(event, args[2]);
    BattleUnit* unit;
    BattleUnitPart* part;
    BattleAudienceMember* mem;
    EventEntry* evt;
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    f32 hx;
    f32 hy;
    f32 hz;

    if (isFirstCall) {
        aud_get_pod_pos(BattleGetUnitPtr(_battleWorkPointer, id), &x, &y, &z);
        aud_fire_eff(x, y, z);
        unit = BattleGetUnitPtr(_battleWorkPointer, target);
        part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
        BtlUnit_GetHitPos(unit, part, &hx, &hy, &hz);
        for (i = start; i < start + 2; i++) {
            mem = BattleAudienceGetPtr(list[i]);
            BattleAudience_SetAnim(list[i], 9, FALSE);
            mem->position = (Vec){x, y, z};
            mem->interpFramesTotal = 0;
            mem->counter = 0;
            mem->rotation.y = 0.0f;
            mem->baseScale.x = mem->baseScale.y = 1.0f;
            mem->flags |= MEMBER_FLAG_VISIBLE;
            evt = evtEntry(aud_hit_event, 0, 0x20);
            evt->lwData[0] = list[i];
            evt->lwData[1] = (s32)(1024.0f * hx) - EVTDAT_FLOAT_BASE;
            evt->lwData[2] = (s32)(1024.0f * hy) - EVTDAT_FLOAT_BASE;
            evt->lwData[3] = (s32)(1024.0f * hz) - EVTDAT_FLOAT_BASE;
            evt->lwData[4] = 0;
            evt->lwData[5] = irand(3) + 10;
            evt->lwData[6] = (s32)(1024.0f * (hx + 200.0f * rand() / 32767.0f - 100.0f)) - EVTDAT_FLOAT_BASE;
            evt->lwData[7] = FLOAT(-100.0f);
            evt->lwData[8] = (s32)(1024.0f * (hz + 100.0f * rand() / 32767.0f - 50.0f)) - EVTDAT_FLOAT_BASE;
            evt->lwData[9] = irand(30) + 30;
            evt->lwData[10] = FLOAT(-0.3f);
        }
    }
    return EVT_RETURN_DONE;
}

/**
 * Script function: like aud_fire_hit but for a shot that misses:
 * the audience members fly past the target to x = -275 (aud_hit_event).
 */
static USER_FUNC(aud_fire_no_hit) {
    EvtWord* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 target = BattleTransID(event, evtGetValue(event, args[1]));
    s32 start = evtGetValue(event, args[2]);
    BattleUnit* unit;
    BattleUnitPart* part;
    BattleAudienceMember* mem;
    EventEntry* evt;
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    f32 hx;
    f32 hy;
    f32 hz;

    if (isFirstCall) {
        aud_get_pod_pos(BattleGetUnitPtr(_battleWorkPointer, id), &x, &y, &z);
        aud_fire_eff(x, y, z);
        unit = BattleGetUnitPtr(_battleWorkPointer, target);
        part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
        BtlUnit_GetHitPos(unit, part, &hx, &hy, &hz);
        for (i = start; i < start + 2; i++) {
            mem = BattleAudienceGetPtr(list[i]);
            BattleAudience_SetAnim(list[i], 9, FALSE);
            mem->position = (Vec){x, y, z};
            mem->interpFramesTotal = 0;
            mem->counter = 0;
            mem->rotation.y = 0.0f;
            mem->baseScale.x = mem->baseScale.y = 1.0f;
            mem->flags |= MEMBER_FLAG_VISIBLE;
            evt = evtEntry(aud_hit_event, 0, 0x20);
            evt->lwData[0] = list[i];
            evt->lwData[1] = FLOAT(-275.0f);
            evt->lwData[2] = (s32)(1024.0f * (hy - 20.0f)) - EVTDAT_FLOAT_BASE;
            evt->lwData[3] = (s32)(1024.0f * hz) - EVTDAT_FLOAT_BASE;
            evt->lwData[4] = 0;
            evt->lwData[5] = irand(3) + 10;
        }
    }
    return EVT_RETURN_DONE;
}

/**
 * Script function that draws the targeting marker for the audience attack at the position given by args[0] to
 * args[2]: the reticle swoops in over 60, 40 and 20 frames with SFX_BOSS_MBTN_SEARCH1 and
 * then locks on with SFX_BOSS_MBTN_LOCKON1.
 */
static USER_FUNC(aud_target_mark) {
    EvtWord* args = event->args;
    f32 x = evtGetValue(event, args[0]);
    f32 y = evtGetValue(event, args[1]);
    f32 z = evtGetValue(event, args[2]);
    EffBattenWork* ew;

    if (isFirstCall) {
        wp_target = BattleAlloc(sizeof(TargetWork));
        wp_target->eff = effBattenEntry(1, 1000, 0.0f, -1000.0f, 0.0f, 1.0f);
        wp_target->state = 0;
        wp_target->count = 0;
        targetSoundId = psndSFXOn("SFX_BOSS_MBTN_SEARCH1");
    }
    ew = wp_target->eff->userdata;
    switch (wp_target->state) {
        case 0:
            wp_target->count++;
            ew->position.x = intplGetValue(4, 60.0f + x, x - 5.0f, wp_target->count, 60);
            ew->position.y = intplGetValue(4, 20.0f + y, 60.0f + y, wp_target->count, 60);
            ew->position.z = 20.0f + z;
            if (wp_target->count >= 60) {
                wp_target->state = 5;
                wp_target->count = 0;
            }
            break;
        case 5:
            wp_target->count++;
            ew->position.x = intplGetValue(4, x - 5.0f, x - 25.0f, wp_target->count, 40);
            ew->position.y = intplGetValue(4, 60.0f + y, 20.0f + y, wp_target->count, 40);
            ew->position.z = 20.0f + z;
            if (wp_target->count >= 40) {
                wp_target->state = 10;
                wp_target->count = 0;
            }
            break;
        case 10:
            wp_target->count++;
            ew->position.x = intplGetValue(4, x - 25.0f, x, wp_target->count, 20);
            ew->position.y = intplGetValue(4, 20.0f + y, y, wp_target->count, 20);
            ew->position.z = 20.0f + z;
            if (wp_target->count >= 20) {
                wp_target->state = 15;
                wp_target->count = 0;
                effDelete(wp_target->eff);
                wp_target->eff = effBattenEntry(2, 1000, x, y, 10.0f + z, 1.0f);
                psndSFXOff(targetSoundId);
                psndSFXOn("SFX_BOSS_MBTN_LOCKON1");
            }
            break;
        case 15:
            wp_target->count++;
            if (wp_target->count >= 90) {
                effDelete(wp_target->eff);
                BattleFree(wp_target);
                return EVT_RETURN_DONE;
            }
            break;
    }
    return EVT_RETURN_BLOCK;
}

/** Script function: starts the dying boss's charge-up effect (akari_charge_n64) at args[0] to args[2]. */
static USER_FUNC(eff_dead) {
    EvtWord* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    eff_charge = effAkariChargeN64Entry(0, 1000, x, y, z, 1.5f);
    return EVT_RETURN_DONE;
}

/** Script function: removes the charge-up effect started by eff_dead. */
static USER_FUNC(eff_dead_delete) {
    effDelete(eff_charge);
    return EVT_RETURN_DONE;
}

/**
 * Battle init for Magnus von Grapple 2.0: registers its wait, entry, attack, damage and confusion events,
 * sets the part 3 pose MGN_L_1, starts the frame event (waku_event) and the arm physics (arm_init)
 * and clears its unit work flags: 0 = arms detached, 1 = turns until the fists return,
 * 2 = arms have separated once, 5 and 6 are phase flags (6 is set when the boss is defeated).
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
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARM_RETURN_TIMER, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_SEPARATED, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_DRILL_USED, 0)
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, 125, 0, 0)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 125, 0, 0)
    CALL(btlevtcmd_SetBaseRotate, BTL_UNIT_SELF, 0, -55, 0)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_MOVE1"), STRING("SFX_BOSS_MBTN_MOVE1"), 26, 26, 26)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_MOVE1"), STRING("SFX_BOSS_MBTN_MOVE1"), 20, 20, 20)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Per-frame loop that calls waku_main for the boss (keeping the frame part, part 3, on the body's locator17 bone
 * and facing the camera) until the unit no longer exists.
 */
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
 * Damage event of Magnus von Grapple 2.0: marks part 3 with part attribute 0x1000000
 * while damage pattern 10 is processed, runs the default damage handler,
 * and the first time its HP drops to 14 or lower (and it is not already beaten) it waits for attacks to end,
 * zooms the camera on it and speaks stg7_aji_41_06.
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
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_LOW_HP_TALK_DONE, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 14)
            CALL(btlevtcmd_WaitAttackEnd)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_LOW_HP_TALK_DONE, 1)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(evt_btl_camera_set_prilimit, 1)
            CALL(evt_btl_camera_set_mode, 1, 3)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            SUBTRACT(LW(0), 20)
            CALL(evt_btl_camera_set_moveto, 1, LW(0), 160, 600, LW(0), 110, -100, 20, 11)
            WAIT_FRAMES(20)
            CALL(btlevtcmd_SetTalkPoseType, BTL_UNIT_SELF, BTL_POSE_TALK)
            CALL(btlevtcmd_SetStayPoseType, BTL_UNIT_SELF, BTL_POSE_STAY_DEFAULT)
            CALL(evt_msg_print, 2, STRING("stg7_aji_41_06"), 0, BTL_UNIT_SELF)
            CALL(evt_btl_camera_set_prilimit, 0)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            WAIT_MS(500)
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Defeat sequence of Magnus von Grapple 2.0: sets the defeated flag (unit work 6),
 * plays the explosion effect over the body, zooms the camera,
 * speaks stg7_aji_41_07 and runs the common defeat handling (subsetevt_dead_core).
 */
static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_LOW_HP_TALK_DONE, 1)
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
    CALL(evt_msg_print, 2, STRING("stg7_aji_41_07"), 0, BTL_UNIT_SELF)
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
#if VERSION >= VERSION_JP
        END_IF
#endif
    END_IF
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
 * Entrance of Magnus von Grapple 2.0 at the start of the fight:
 * waits 2 seconds, then a camera close-up on the boss with the opening lines stg7_aji_41_00
 * and stg7_aji_41_01 (the partner answers), after which the camera returns to normal.
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
    CALL(evt_msg_print, 2, STRING("stg7_aji_41_00"), 0, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_moveto, 1, -102, 83, 334, -102, 59, 0, 20, 11)
    WAIT_FRAMES(20)
    CALL(evt_msg_print_battle_party, STRING("stg7_aji_41_01"))
    CALL(evt_btl_camera_set_prilimit, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    WAIT_MS(500)
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_PARTNER, LW(0))
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_PARTNER, LW(0))
    RETURN
EVT_END()

/**
 * Attack choice of Magnus von Grapple 2.0.
 * When both detached fists are gone it counts unit work 1 down and, at 0, calls them back (arm_return_event).
 * With the arms on it uses the drill while its HP is above 63 or on its first attack,
 * splits its arms off (arm_bunri_event) the first time after that,
 * then picks drill 40 / arm separation 40 (above 35 HP)
 * or drill 40 / separation 40 / audience attack 25 (35 HP or less).
 * With the fists out it throws the boomerang above 35 HP,
 * and at 35 HP or less boomerang 75 / audience attack 20.
 * The audience attack (aud_attack_event) needs at least 20 audience members and is used first
 * when still unused (unit work 7).
 */
static EVT_BEGIN(attack_event)
    // If the fists are out (unit work 0 is 1), it counts down how long they stay away and calls them back
    // when none are left.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(arm_check, 0, LW(0))
        IF_INT_EQUAL(LW(0), -1)
            CALL(arm_check, 1, LW(0))
            IF_INT_EQUAL(LW(0), -1)
                CALL(btlevtcmd_AddUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARM_RETURN_TIMER, -1)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARM_RETURN_TIMER, LW(0))
                IF_INT_LESS_OR_EQUAL(LW(0), 0)
                    CALL_CHILD(arm_return_event)
                END_IF
            END_IF
        END_IF
    END_IF
    // It uses an item instead of attacking when one is ready.
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    // Arms on: it uses the drill on its first attack and while its HP is above 63.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_DRILL_USED, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL_CHILD(drill_attack_event)
            GOTO(99)
        END_IF
        CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
        IF_INT_GREATER(LW(0), 63)
            CALL_CHILD(drill_attack_event)
            GOTO(99)
        ELSE
            // After that the first thing it does is split its arms off into two fists (arm_bunri_event).
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_SEPARATED, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL_CHILD(arm_bunri_event)
                GOTO(99)
            END_IF
            CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
            // Above 35 HP: drill or splitting the arms off, 40 weight each.
            IF_INT_GREATER(LW(0), 35)
                SET_VALUE(LW(0), 0)
                ADD(LW(0), 40)
                ADD(LW(0), 40)
                SUBTRACT(LW(0), 1)
                CALL(evt_sub_random, LW(0), LW(1))
                SET_VALUE(LW(0), 40)
                IF_INT_LESS(LW(1), LW(0))
                    CALL_CHILD(drill_attack_event)
                    GOTO(99)
                ELSE
                    CALL_CHILD(arm_bunri_event)
                    GOTO(99)
                END_IF
            ELSE
                // 35 HP or less: the audience attack comes first if it is unused and there are 20 audience
                // members; then drill 40, separation 40, audience attack 25.
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_AUD_ATTACK_USED, LW(0))
                IF_INT_EQUAL(LW(0), 0)
                    CALL(get_aud_num, LW(0))
                    IF_INT_GREATER_OR_EQUAL(LW(0), 20)
                        CALL_CHILD(aud_attack_event)
                        GOTO(99)
                    END_IF
                END_IF
                LABEL(10)
                SET_VALUE(LW(0), 0)
                ADD(LW(0), 40)
                ADD(LW(0), 40)
                ADD(LW(0), 25)
                SUBTRACT(LW(0), 1)
                CALL(evt_sub_random, LW(0), LW(1))
                SET_VALUE(LW(0), 40)
                IF_INT_LESS(LW(1), LW(0))
                    CALL_CHILD(drill_attack_event)
                    GOTO(99)
                END_IF
                ADD(LW(0), 40)
                IF_INT_LESS(LW(1), LW(0))
                    CALL_CHILD(arm_bunri_event)
                    GOTO(99)
                END_IF
                ADD(LW(0), 25)
                IF_INT_LESS(LW(1), LW(0))
                    CALL(get_aud_num, LW(0))
                    IF_INT_GREATER_OR_EQUAL(LW(0), 20)
                        CALL_CHILD(aud_attack_event)
                        GOTO(99)
                    END_IF
                END_IF
                GOTO(10)
            END_IF
        END_IF
    ELSE
        // Fists out: above 35 HP it throws the boomerang.
        CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
        IF_INT_GREATER(LW(0), 35)
            CALL_CHILD(boomerang_attack_event)
            GOTO(99)
        ELSE
            // 35 HP or less: the audience attack first if unused, then boomerang 75 or audience attack 20.
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_AUD_ATTACK_USED, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(get_aud_num, LW(0))
                IF_INT_GREATER_OR_EQUAL(LW(0), 20)
                    CALL_CHILD(aud_attack_event)
                    GOTO(99)
                END_IF
            END_IF
            LABEL(20)
            SET_VALUE(LW(0), 0)
            ADD(LW(0), 75)
            ADD(LW(0), 20)
            SUBTRACT(LW(0), 1)
            CALL(evt_sub_random, LW(0), LW(1))
            SET_VALUE(LW(0), 75)
            IF_INT_LESS(LW(1), LW(0))
                CALL_CHILD(boomerang_attack_event)
                GOTO(99)
            END_IF
            ADD(LW(0), 20)
            IF_INT_LESS(LW(1), LW(0))
                CALL(get_aud_num, LW(0))
                IF_INT_GREATER_OR_EQUAL(LW(0), 20)
                    CALL_CHILD(aud_attack_event)
                    GOTO(99)
                END_IF
            END_IF
            GOTO(20)
        END_IF
    END_IF
    LABEL(99)
    // The facing is reset and it goes back to waiting.
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Magnus Drill Attack of Magnus von Grapple 2.0 (weapon_batten_drill_attack, one target): the first time
 * (unit work 5) Crump announces it (stg7_aji_41_02). The boss winds up (MGN_A3_1 to 3 with
 * SFX_BOSS_MBTN_DRILL_ATTACK1 to 3), jets up off screen,
 * comes down upside down over the party in a tornado effect
 * through the floor with a camera shake, deals the damage with the usual dodge and guard checks,
 * then reappears at the right edge and walks home.
 */
EVT_BEGIN(drill_attack_event)
    // Choose a target.
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_batten_drill_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_batten_drill_attack), LW(3), LW(4))
    // No valid target: a confused boss is flustered, otherwise the turn is skipped.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
        END_IF
        RETURN
    END_IF
    // The first time (unit work 5), Crump announces the drill attack over a close-up of the boss
    // (stg7_aji_41_02).
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_DRILL_USED, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_DRILL_USED, 1)
        CALL(btlevtcmd_StatusWindowOnOff, 0)
        CALL(evt_btl_camera_set_prilimit, 1)
        CALL(evt_btl_camera_set_mode, 1, 3)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SUBTRACT(LW(0), 20)
        CALL(evt_btl_camera_set_moveto, 1, LW(0), 160, 600, LW(0), 110, -100, 20, 11)
        WAIT_FRAMES(20)
        CALL(evt_msg_print, 2, STRING("stg7_aji_41_02"), 0, BTL_UNIT_SELF)
        CALL(evt_btl_camera_set_prilimit, 0)
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(btlevtcmd_StatusWindowOnOff, 1)
        WAIT_MS(500)
    END_IF
    // The attack is declared and the guard window opens.
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_batten_drill_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_batten_drill_attack))
    // Wind-up: it crouches and fires its jets (MGN_A3_1, MGN_A3_2).
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_DRILL_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A3_1"))
    WAIT_MS(800)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_DRILL_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A3_2"))
    BEGIN_SIBLING_EVENT
        CALL(drill_jet, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    WAIT_MS(300)
    // It jets straight up and off the top of the screen.
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 300)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, 0, 1, 0, -1)
    WAIT_MS(300)
    // It reappears high above the stage upside down and plunges back down in a tornado, drill first
    // (MGN_A3_3).
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, -125, 500, 0)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 180, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A3_3"))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_DRILL_ATTACK3"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, -125, -200, 0, 60, 0, 0, 0, -1)
    END_SIBLING_EVENT
    BEGIN_INLINE_EVENT
        CALL(drill_tor, BTL_UNIT_SELF)
    END_INLINE_EVENT
    LOOP(0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        IF_INT_LESS_OR_EQUAL(LW(1), 200)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    // The camera shakes as the drill bores through the floor.
    CALL(evt_btl_camera_shake_h, 0, 7, 0, 80, 0)
    SET_VALUE(LW(6), 0)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    LABEL(10)
    IF_INT_EQUAL(LW(3), -1)
        GOTO(97)
    END_IF
    // Each target in turn gets the hit check and then the damage; the action-command result is read once.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_batten_drill_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    LABEL(91)
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_batten_drill_attack))
        SET_VALUE(LW(6), 1)
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_batten_drill_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(95)
    LABEL(95)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    GOTO(10)
    LABEL(97)
    // It keeps drilling until it has passed below the floor out of sight.
    LOOP(0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        IF_INT_LESS_OR_EQUAL(LW(1), -200)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    // The camera returns to normal.
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(200)
    // It reappears upright at the right edge of the stage and walks back to its home position.
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 400, LW(1), LW(2))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, -1, 0)
    RETURN
EVT_END()

/**
 * Boomerang attack of Magnus von Grapple 2.0 (weapon_batten_boomerang_attack, which hits every target):
 * the boss splits off its boomerang part (part 4; poses MGN_A6_1, MGN_A4_2 and 3, SFX_BOSS_MBTN_BOOME_*),
 * which swings in two short arcs in front of it and then flies across the party to x = -400,
 * damaging each target
 * with the usual dodge and guard checks; the part is hidden again afterwards.
 */
EVT_BEGIN(boomerang_attack_event)
    // Choose a target; the boomerang flies across every target.
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_batten_boomerang_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_batten_boomerang_attack), LW(3), LW(4))
    // No valid target: a confused boss is flustered, otherwise the turn is skipped.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
        END_IF
        RETURN
    END_IF
    // The attack is declared and the guard window opens.
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_batten_boomerang_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_batten_boomerang_attack))
    // The boss splits its boomerang part (part 4) off its body (MGN_A6_1).
    BEGIN_SIBLING_EVENT
        WAIT_MS(900)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_BOOME_DIVIDE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A6_1"))
    WAIT_MS(1160)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_BOOME_ROUND1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 70)
    ADD(LW(1), 70)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 4, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, 4, 0, 55, 65)
    BEGIN_SIBLING_EVENT
        WAIT_MS(1600)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_BOOME_ACTIVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("MGN_A4_2"))
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 4, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 4, PART_ATTR_NO_SHADOW)
    BEGIN_SIBLING_EVENT
        WAIT_MS(2500)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("MGN_A4_3"))
    END_SIBLING_EVENT
    // The boomerang swings in two short arcs in front of the boss.
    CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 4, LW(0), LW(1), LW(2))
    ADD(LW(1), 30)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 25)
    CALL(btlevtcmd_DivePartsPosition, BTL_UNIT_SELF, 4, LW(0), LW(1), LW(2), 80, -40, 0, 0, -1)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 25)
    CALL(btlevtcmd_DivePartsPosition, BTL_UNIT_SELF, 4, LW(0), LW(1), LW(2), 80, 40, 0, 0, -1)
    // Then it sails across the whole party to the far side of the stage.
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_DivePartsPosition, BTL_UNIT_SELF, 4, -400, 120, LW(2), 40, -20, 1, 0, -1)
    END_SIBLING_EVENT
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_BOOME_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(20)
    SET_VALUE(LW(6), 0)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    LABEL(10)
    IF_INT_EQUAL(LW(3), -1)
        GOTO(97)
    END_IF
    // Each target in turn gets the hit check and then the damage as the boomerang passes; the action-command
    // result is read once.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_batten_boomerang_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    LABEL(91)
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_batten_boomerang_attack))
        SET_VALUE(LW(6), 1)
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_batten_boomerang_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(95)
    LABEL(95)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    GOTO(10)
    LABEL(97)
    WAIT_MS(700)
    // The boomerang part is hidden again and the camera returns to normal.
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 4, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 4, PART_ATTR_NO_SHADOW)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(200)
    RETURN
EVT_END()

/**
 * Audience attack of Magnus von Grapple 2.0 (weapon_batten_aud_attack, one target): the first time
 * (unit work 7) Crump talks in close-up before it (stg7_aji_41_04) and again before firing (stg7_aji_41_05).
 * The boss sucks 20 audience members into its pod (aud_suikomi), takes aim (aud_target_mark)
 * and fires them at the target in ten rounds of two (aud_attack_event_sub).
 */
EVT_BEGIN(aud_attack_event)
    // Choose a target.
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_batten_aud_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_batten_aud_attack), LW(3), LW(4))
    // No valid target: a confused boss is flustered, otherwise the turn is skipped.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
        END_IF
        RETURN
    END_IF
    // The first time (unit work 7), Crump talks over a close-up of the boss before the attack
    // (stg7_aji_41_04).
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_AUD_ATTACK_USED, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_StatusWindowOnOff, 0)
        CALL(evt_btl_camera_set_prilimit, 1)
        CALL(evt_btl_camera_set_mode, 1, 3)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SUBTRACT(LW(0), 20)
        CALL(evt_btl_camera_set_moveto, 1, LW(0), 160, 600, LW(0), 110, -100, 20, 11)
        WAIT_FRAMES(20)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("MGN_T_1"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("MGN_S_1"))
        ELSE
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("MGN_T_2"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("MGN_S_2"))
        END_IF
        CALL(evt_msg_print, 2, STRING("stg7_aji_41_04"), 0, BTL_UNIT_SELF)
        CALL(evt_btl_camera_set_prilimit, 0)
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(btlevtcmd_StatusWindowOnOff, 1)
        WAIT_MS(500)
    END_IF
    // The attack is declared and the guard window opens.
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_batten_aud_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_batten_aud_attack))
    WAIT_FRAMES(30)
    BEGIN_SIBLING_EVENT
        WAIT_MS(200)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_MOVE1"), EVT_NULLPTR, 0, LW(15))
        WAIT_MS(300)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_MOVE1"), EVT_NULLPTR, 0, LW(15))
        WAIT_MS(300)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_MOTOR_ACTIVE1"), EVT_NULLPTR, 0, LW(15))
        WAIT_MS(700)
        CALL(evt_snd_sfxoff, LW(15))
    END_SIBLING_EVENT
    // Wind-up: the boss opens its pod and fires its jets (a different pose set is used with the fists out).
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_1"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A5_1"))
    END_IF
    WAIT_MS(1600)
    BEGIN_SIBLING_EVENT
        CALL(drill_jet, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_2"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A5_2"))
    END_IF
    WAIT_MS(300)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    // It rises on its jets while the camera moves to the audience and the audience area darkens.
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 300)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, 0, 1, 0, -1)
    WAIT_MS(300)
    CALL(evt_btl_camera_set_mode, 0, 6)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_batstage_set_aud_dark, 0, 30, 0)
    BEGIN_SIBLING_EVENT
        CALL(aud_jet, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_7"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A5_7"))
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(2), 150)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 300)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), 25, LW(2), 60, 0, 4, 0, -1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_3"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A5_3"))
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_INHALE1"), EVT_NULLPTR, 0, LW(15))
    // It sucks 20 audience members into its pod.
    CALL(aud_suikomi, BTL_UNIT_SELF)
#if VERSION >= VERSION_JP
    BEGIN_SIBLING_EVENT
        CALL(aud_scream_fadeout)
    END_SIBLING_EVENT
#endif
    CALL(evt_snd_sfxoff, LW(15))
    // It sinks back down and the jets shut off.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_7"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A5_7"))
    END_IF
    WAIT_MS(300)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 300)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, 0, 1, 0, -1)
    CALL(aud_jet_end)
    WAIT_MS(300)
    // The audience lighting comes back, the camera returns and the boss goes back to its home position.
    CALL(evt_batstage_return_aud_dark_base, 30, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    BEGIN_SIBLING_EVENT
        CALL(drill_jet, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_2"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A5_2"))
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 300)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, 0, 4, 0, -1)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_MOTOR_ACTIVE1"), EVT_NULLPTR, 0, LW(15))
        WAIT_MS(600)
        CALL(evt_snd_sfxoff, LW(15))
        WAIT_MS(400)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_CHEST_OPEN1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_4"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A5_4"))
    END_IF
    WAIT_MS(1200)
    // The first time (unit work 7 is 0), Crump speaks again before the shots (stg7_aji_41_05).
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_AUD_ATTACK_USED, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_AUD_ATTACK_USED, 1)
        CALL(btlevtcmd_StatusWindowOnOff, 0)
        CALL(evt_btl_camera_set_prilimit, 1)
        CALL(evt_btl_camera_set_mode, 1, 3)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SUBTRACT(LW(0), 20)
        CALL(evt_btl_camera_set_moveto, 1, LW(0), 160, 600, LW(0), 110, -100, 20, 11)
        WAIT_FRAMES(20)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("MGN_T_3"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("MGN_A2_8"))
        ELSE
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("MGN_T_4"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("MGN_A5_8"))
        END_IF
        CALL(evt_msg_print, 2, STRING("stg7_aji_41_05"), 0, BTL_UNIT_SELF)
        CALL(btlevtcmd_SetTalkPoseType, BTL_UNIT_SELF, BTL_POSE_TALK)
        CALL(btlevtcmd_SetStayPoseType, BTL_UNIT_SELF, BTL_POSE_STAY_DEFAULT)
        CALL(evt_btl_camera_set_prilimit, 0)
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(btlevtcmd_StatusWindowOnOff, 1)
        WAIT_MS(500)
    END_IF
    // It takes aim at the target (aud_target_mark).
    CALL(btlevtcmd_GetPartsPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    ADD(LW(1), 20)
    CALL(aud_target_mark, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_5"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A5_5"))
    END_IF
    SET_VALUE(LW(10), 0)
    // It fires the audience members at the target in ten rounds of two (aud_attack_event_sub).
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_AUD_ATTACK_HIT, 0)
    LOOP(10)
        WAIT_MS(250)
        CALL_CHILD(aud_attack_event_sub)
    END_LOOP
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(0), -10)
    ADD(LW(1), 78)
    WAIT_MS(250)
    CALL(evt_eff, STRING(""), STRING("machingegun"), 0, LW(0), LW(1), LW(2), 180, FLOAT(8.0f), FLOAT(2.0996094f), 0, 0, 0, 0, 0)
    WAIT_MS(250)
    CALL(evt_eff, STRING(""), STRING("machingegun"), 0, LW(0), LW(1), LW(2), 170, FLOAT(8.0f), FLOAT(2.0996094f), 0, 0, 0, 0, 0)
    WAIT_MS(250)
    CALL(evt_eff, STRING(""), STRING("machingegun"), 0, LW(0), LW(1), LW(2), 185, FLOAT(8.0f), FLOAT(2.0996094f), 0, 0, 0, 0, 0)
    // The boss closes its pod again and the camera returns to normal.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_8"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A5_8"))
    END_IF
    WAIT_MS(1000)
    BEGIN_SIBLING_EVENT
        WAIT_MS(100)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_CHEST_OPEN1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        WAIT_MS(300)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        WAIT_MS(300)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A2_6"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A5_6"))
    END_IF
    WAIT_MS(1000)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(200)
    RETURN
EVT_END()

/**
 * One round (LW(10), 0 to 9) of the audience attack: plays SFX_BOSS_MBTN_MACHINEGUN1,
 * pre-checks the damage on the target (dodging, guarding or taking it), fires two audience members with
 * aud_fire_hit or aud_fire_no_hit, and on a hit applies the damage, with DAMAGE_FLAG_LAST_HIT only in the last
 * round. Once a round has hit (unit work 8), the last round hits without a new check.
 */
EVT_BEGIN(aud_attack_event_sub)
    IF_INT_EQUAL(LW(10), 9)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_AUD_ATTACK_HIT, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            GOTO(91)
        END_IF
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_MACHINEGUN1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_batten_aud_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    SET_VALUE(LW(11), LW(10))
    MULTIPLY(LW(11), 2)
    CALL(aud_fire_no_hit, BTL_UNIT_SELF, LW(3), LW(11))
    GOTO(95)
    LABEL(91)
    SET_VALUE(LW(11), LW(10))
    MULTIPLY(LW(11), 2)
    CALL(aud_fire_hit, BTL_UNIT_SELF, LW(3), LW(11))
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_batten_aud_attack))
    IF_INT_EQUAL(LW(10), 9)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_batten_aud_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_batten_aud_attack), 0, LW(5))
    END_IF
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_AUD_ATTACK_HIT, 1)
    GOTO(95)
    LABEL(95)
    ADD(LW(10), 1)
    RETURN
EVT_END()

/**
 * Separates the boss's arms (bunri = separation):
 * sets unit work 0 (arms detached), 2 (separated once) and 1 = 2,
 * shows a close-up with stg7_aji_41_03 the first time, plays poses MGN_A1_1 to 3,
 * spawns two rocket punch units (unit_boss_rocket_punch_mkII, left and right fists) whose ids go in unit work 3
 * and 4, and switches to the pose table without arms.
 */
static EVT_BEGIN(arm_bunri_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_SEPARATED, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_StatusWindowOnOff, 0)
        CALL(evt_btl_camera_set_prilimit, 1)
        CALL(evt_btl_camera_set_mode, 1, 3)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SUBTRACT(LW(0), 20)
        CALL(evt_btl_camera_set_moveto, 1, LW(0), 160, 600, LW(0), 110, -100, 20, 11)
        WAIT_FRAMES(20)
        CALL(evt_msg_print, 2, STRING("stg7_aji_41_03"), 0, BTL_UNIT_SELF)
        CALL(evt_btl_camera_set_prilimit, 0)
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(btlevtcmd_StatusWindowOnOff, 1)
        WAIT_MS(500)
    END_IF
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_SEPARATED, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARM_RETURN_TIMER, 2)
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
    CALL(btlevtcmd_SetUnitWork, LW(3), UW_ROCKET_PUNCH_MKII_SIDE, 0)
    CALL(btlevtcmd_SetUnitWork, LW(3), UW_ROCKET_PUNCH_MKII_TURN_WAIT, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_LEFT_FIST, LW(3))
    CALL(btlevtcmd_AnimeChangePoseType, LW(3), 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_SpawnUnit, LW(4), PTR(&entry_rocket_punch), 0)
    CALL(btlevtcmd_SetUnitWork, LW(4), UW_ROCKET_PUNCH_MKII_SIDE, 1)
    CALL(btlevtcmd_SetUnitWork, LW(4), UW_ROCKET_PUNCH_MKII_TURN_WAIT, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_RIGHT_FIST, LW(4))
    CALL(btlevtcmd_AnimeChangePoseType, LW(4), 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_no_arm))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    WAIT_MS(1500)
    RETURN
EVT_END()

/**
 * Calls the fists back: clears unit work 0, plays pose MGN_A1_6 for 0.6 seconds,
 * spawns two fresh rocket punch units (work 0 = 2 and 3, left and right) whose ids go in unit work 3 and 4
 * and switches back to the pose table with arms.
 */
static EVT_BEGIN(arm_return_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_ARMS_OUT, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A1_6"))
    WAIT_MS(600)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_rocket_punch), 0)
    CALL(btlevtcmd_SetUnitWork, LW(3), UW_ROCKET_PUNCH_MKII_SIDE, 2)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_LEFT_FIST, LW(3))
    CALL(btlevtcmd_AnimeChangePoseType, LW(3), 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_SpawnUnit, LW(4), PTR(&entry_rocket_punch), 0)
    CALL(btlevtcmd_SetUnitWork, LW(4), UW_ROCKET_PUNCH_MKII_SIDE, 3)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAGNUM_BATTENDER_MKII_RIGHT_FIST, LW(4))
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

/** Idle script of Magnus von Grapple 2.0: sets the idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Unit data of the X-Punch fist of Magnus von Grapple 2.0: 5 HP, level 0; the battle starts it from
 * init_event_r.
 */
BattleUnitKind unit_boss_rocket_punch_mkII = {
    122,
    "btl_un_rocket_punch_mkii",
    5,
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

/** Defence of the X-Punch fist of Magnus von Grapple 2.0: none against any element. */
static BattleUnitDefense defence_r = {{0, 0, 0, 0, 0}};

/**
 * Elemental reactions of the X-Punch fist of Magnus von Grapple 2.0: none, every element hurts it normally.
 */
static BattleUnitDefenseAttr defence_attr_r = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
/**
 * Status vulnerability of the X-Punch fist of Magnus von Grapple 2.0 (percent, 100 is normal) in the demo
 * builds: immune to sleep, Huge, Tiny, Attack Down, fright, Dodgy, Invisible and instant KO; resists most
 * statuses (70-90%).
 */
static StatusVulnerability regist_r = {0, 70, 70, 70, 70, 70, 100, 70, 0, 0, 100, 0, 100, 70, 70, 0, 90, 100, 70, 0, 0, 0};
#else
/**
 * Status vulnerability of the X-Punch fist of Magnus von Grapple 2.0 (percent, 100 is normal) in the retail
 * builds: immune to sleep, Huge, Tiny, Attack Down, fright, Dodgy, Invisible and instant KO; resists most
 * statuses (70-85%).
 */
static StatusVulnerability regist_r = {0, 70, 70, 100, 70, 100, 100, 70, 0, 0, 100, 0, 100, 85, 70, 0, 100, 100, 70, 0, 0, 0};
#endif

/** Pose table of the X-Punch fist: its flying and stay poses. */
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

/** Event table of the X-Punch fist of Magnus von Grapple 2.0: empty, it has no special reactions. */
static BattleDataEntry data_table_r[] = {
    {0, NULL},
};

/** Part of the X-Punch fist: its single flying fist part (the target). */
static BattleUnitKindPart parts_r[] = {
    {1, "btl_un_rocket_punch_mkii", "c_mb_robo_2b", 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 10.0f, 0.0f, 106, 174, 255, &defence_r, &defence_attr_r, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, COUNTER_ATTR_PREEMPTIVE_FRONT_SPIKY, pose_table_r},
};

/**
 * Weapon data for the X-Punch fist of Magnus von Grapple 2.0's rocket punch: 9 damage, a jump-type hit, one
 * target.
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
    {9, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
#if VERSION <= VERSION_DEMO_US
    COUNTER_RESIST_ALL & ~(COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_PREEMPTIVE_SPIKY), // counterResistFlags
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
 * Battle init for a rocket punch fist of Magnus von Grapple 2.0 (unit work 0: 0 and 2 are the left fist,
 * 1 and 3 the right): registers its wait, attack, damage and confusion events, turns it sideways,
 * sets up the arm physics (arm_init2), starts arm_event and, for the freshly separated fists (work 0 or 1),
 * makes it fly out in an arc with SFX_BOSS_MBTN_PUNCH_FLY1 and settle at its hovering home position.
 */
static EVT_BEGIN(init_event_r)
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_NO_BACKFACE_FLIP)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A1_4"))
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event_r))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event_r))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event_r))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetBaseRotate, BTL_UNIT_SELF, 0, -90, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_MKII_SIDE, LW(0))
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
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_MKII_SIDE, LW(0))
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
 * Per-frame loop for a fist: calls arm_main to animate its chain (left arm for work 0 and 2, right arm for 1 and
 * 3) until the unit is gone, then runs arm_event_end.
 */
static EVT_BEGIN(arm_event)
    LABEL(0)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        CALL_CHILD(arm_event_end)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_MKII_SIDE, LW(0))
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

/** Frees the arm physics of a fist (arm_end for the left or right arm, chosen by unit work 0). */
static EVT_BEGIN(arm_event_end)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_MKII_SIDE, LW(0))
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

/**
 * Damage event of a fist: runs the default damage handler and,
 * when the hit carries damage code 512 (and not 2048), ends the arm event.
 */
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
 * Attack script of a fist: acts only every other turn (unit work 1 counts down);
 * when it acts it picks a target for the rocket attack (weapon_batten_rocket_attack) and flies at it.
 */
static EVT_BEGIN(attack_event_r)
    // A fist only acts every other turn (unit work 1 counts down).
    CALL(btlevtcmd_AddUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_MKII_TURN_WAIT, -1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_MKII_TURN_WAIT, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    // When it acts it picks a target for the rocket punch.
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_MKII_TURN_WAIT, 1)
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
    // A coin flip decides how it flies on after the punch.
    CALL(evt_sub_random, 1, LW(6))
    // The attack is declared and the guard window opens.
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_batten_rocket_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_batten_rocket_attack))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    // Wind-up: the fist points at the target (MGN_A1_4).
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MGN_A1_4"))
    // Hit check: a miss or dodge flies past the target, a hit goes on to the damage.
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
    LABEL(91)
    // A side event watches the fist and deals the damage as it reaches the target's position, shaking the
    // camera.
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
    LABEL(95)
    // Depending on the coin flip it flies on through the target and off the far side of the stage, or
    // rebounds off it.
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
    // The fist reappears at the edge of the stage (a different spot for each fist) and flies back to its home
    // position.
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ROCKET_PUNCH_MKII_SIDE, LW(10))
    IF_INT_EQUAL(LW(10), 0)
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 300, LW(1), -100)
    ELSE
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 300, LW(1), 100)
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MBTN_PUNCH_FLY1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 0, 4, 0, -1)
    LABEL(99)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Idle script of a fist: resets its rotation, sets the idle pose from the pose table and then idles forever. */
static EVT_BEGIN(wait_event_r)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    LABEL(0)
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

/** Script function: allocates the work areas for the boss's two arms (position and previous position cleared). */
static USER_FUNC(arm_init) {
    s32 i;

    for (i = 0; i < 2; i++) {
        work[i] = BattleAlloc(sizeof(ArmWork));
        work[i]->prevPos = work[i]->pos = (Vec){0.0f, 0.0f, 0.0f};
    }
    return EVT_RETURN_DONE;
}

/** Script function: creates the arm effect (effBattenEntry type 3) for the arm args[0]. */
static USER_FUNC(arm_init2) {
    s32 idx = evtGetValue(event, event->args[0]);
    ArmWork* arm = work[idx];

    arm->eff = effBattenEntry(3, 1000, 0.0f, -1000.0f, 0.0f, 1.0f);
    return EVT_RETURN_DONE;
}

/**
 * Script function: each frame, places the arm effect for the arm args[1] on the unit args[0],
 * tilts it by the direction of travel (smoothed over three frames) and rotates it with the unit's rotation,
 * with a small offset (0, -18, 0) along its own axis.
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

/** Script function: removes the arm effect of arm args[0]. */
static USER_FUNC(arm_end) {
    s32 idx = evtGetValue(event, event->args[0]);
    ArmWork* arm = work[idx];

    if (arm->eff != NULL) {
        effDelete(arm->eff);
        arm->eff = NULL;
    }
    return EVT_RETURN_DONE;
}
