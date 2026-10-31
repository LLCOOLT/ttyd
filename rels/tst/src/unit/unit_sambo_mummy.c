// Battle unit Poison Pokey (`sambo_mummy`): tst.rel's copy of rels/eki/src/unit/unit_sambo_mummy.c.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_mario.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_sub.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "evt/evt_eff.h"

// Unit work slots of the Dry Pokey (LW(10) in the damage scripts and the summoned LW(3) are Dry Pokeys too).
enum {
    UW_SAMBO_MUMMY_SEGMENTS = 0,   // body segments left, 4 down to 1; sets its height (_body_param_set)
    UW_SAMBO_MUMMY_GENERATION = 1, // 0 for a Dry Pokey that starts the battle, the caller's plus one when summoned; only 0 and 1 call friends
};

BattleUnitKind unit_sambo_mummy;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleWeapon weapon_sambo_mummy_head_attack_4;
static BattleWeapon weapon_sambo_mummy_head_attack_3;
static BattleWeapon weapon_sambo_mummy_head_attack_2;
static BattleWeapon weapon_sambo_mummy_head_attack_1;
static BattleWeapon weapon_sambo_mummy_spike_attack_4;
static BattleWeapon weapon_sambo_mummy_spike_attack_3;
static BattleWeapon weapon_sambo_mummy_spike_attack_2;
static PoseTableEntry pose_table_body4[18];
static PoseTableEntry pose_table_body3[20];
static PoseTableEntry pose_table_body2[20];
static PoseTableEntry pose_table_body1[20];
static PoseTableEntry pose_table_parts[3];
static BattleDataEntry data_table[8];
static BattleUnitKindPart parts[5];
static EvtWord init_event[54];
static EvtWord dmg_avoid_counter_thorn_side_event[51];
static EvtWord damage_event[34];
static EvtWord damage_event_bodylost[273];
static EvtWord subset_dmg_sambo_fall[152];
static EvtWord damage_event_bodylost_blow[354];
static EvtWord damage_swallow_body[256];
static EvtWord attack_event[189];
static EvtWord attack_head_2_event[613];
static EvtWord attack_head_1_event[587];
static EvtWord attack_spike_event[824];
static EvtWord call_friend_event[304];
static BattleUnitSetup entry_sambo;
static EvtWord wait_event[36];
static EvtWord sambo_rabbit_move[74];
static EvtWord _body_param_set[49];

/**
 * Unit definition of the Poison Pokey: its HP, level, sizes, sounds, status vulnerability,
 * parts and init script.
 */
BattleUnitKind unit_sambo_mummy = {
    UNIT_POISON_POKEY,
    "btl_un_sambo_mummy",
    8,
    0,
    1,
    1,
    23,
    0,
#if VERSION <= VERSION_DEMO_JP
    1,
#else
    2,
#endif
    70,
#if VERSION <= VERSION_DEMO_JP
    2,
#else
    1,
#endif
    50,
    9999,
    26,
    80,
    14,
    80,
    0.0f,
    40.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    13.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    13.0f,
    0.0f,
    0.0f,
    13.0f,
    52.0f,
    0.0f,
    0.0f,
    40.0f,
    0.0f,
    26.0f,
    80.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_SAMBO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    5,
    parts,
    init_event,
    data_table,
};

/** Defence of the Poison Pokey: none, every hit does its full damage. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Element modifiers of the Poison Pokey: none, no element is special to it. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/** Status vulnerability of the Poison Pokey in the demo builds: resists most statuses. */
static StatusVulnerability regist = {70, 60, 70, 100, 70, 100, 100, 30, 100, 70, 100, 70, 100, 70, 70, 80, 70, 100, 70, 100, 100, 95};
#else
/** Status vulnerability of the Poison Pokey in the retail builds: resists most statuses. */
static StatusVulnerability regist = {75, 60, 60, 100, 70, 100, 100, 40, 100, 85, 100, 85, 100, 90, 70, 80, 70, 100, 70, 100, 100, 95};
#endif

/**
 * Attack data of the Poison Pokey's headbutt with 4 segments: 4 damage; 60% chance of poison for 10 turns.
 */
static BattleWeapon weapon_sambo_mummy_head_attack_4 = {
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
#if VERSION <= VERSION_DEMO_JP
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#else
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#endif
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    0, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, // sleepChance..dizzyTime
    60, // poisonChance
    10, // poisonTime
    1, // poisonStrength
    0, 0, 0, 0, 0, 0, 0, 0, // confuseChance..burnTime
    0, 0, 0, 0, 0, 0, 0, 0, // freezeChance..atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Attack data of the Poison Pokey's headbutt with 3 segments: 4 damage; 60% chance of poison for 10 turns.
 */
static BattleWeapon weapon_sambo_mummy_head_attack_3 = {
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
#if VERSION <= VERSION_DEMO_JP
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#else
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#endif
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    0, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, // sleepChance..dizzyTime
    60, // poisonChance
    10, // poisonTime
    1, // poisonStrength
    0, 0, 0, 0, 0, 0, 0, 0, // confuseChance..burnTime
    0, 0, 0, 0, 0, 0, 0, 0, // freezeChance..atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Attack data of the Poison Pokey's headbutt with 2 segments: 4 damage; 60% chance of poison for 10 turns.
 */
static BattleWeapon weapon_sambo_mummy_head_attack_2 = {
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
#if VERSION <= VERSION_DEMO_JP
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#else
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#endif
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_SHELL_TOSS_LIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    0, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, // sleepChance..dizzyTime
    60, // poisonChance
    10, // poisonTime
    1, // poisonStrength
    0, 0, 0, 0, 0, 0, 0, 0, // confuseChance..burnTime
    0, 0, 0, 0, 0, 0, 0, 0, // freezeChance..atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Attack data of the Poison Pokey's headbutt with 1 segment: 5 damage; 60% chance of poison for 10 turns.
 */
static BattleWeapon weapon_sambo_mummy_head_attack_1 = {
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
    {5, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_SHELL_TOSS_LIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED, // special
    0, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, // sleepChance..dizzyTime
    60, // poisonChance
    10, // poisonTime
    1, // poisonStrength
    0, 0, 0, 0, 0, 0, 0, 0, // confuseChance..burnTime
    0, 0, 0, 0, 0, 0, 0, 0, // freezeChance..atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Attack data of the Poison Pokey's segment throw with 4 segments: 3 damage. */
static BattleWeapon weapon_sambo_mummy_spike_attack_4 = {
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
#if VERSION <= VERSION_DEMO_JP
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#else
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#endif
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
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
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

/** Attack data of the Poison Pokey's segment throw with 3 segments: 3 damage. */
static BattleWeapon weapon_sambo_mummy_spike_attack_3 = {
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
#if VERSION <= VERSION_DEMO_JP
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#else
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#endif
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
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
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

/** Attack data of the Poison Pokey's segment throw with 2 segments: 3 damage. */
static BattleWeapon weapon_sambo_mummy_spike_attack_2 = {
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
#if VERSION <= VERSION_DEMO_JP
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#else
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#endif
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
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
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

/** Pose table of the Poison Pokey as a full stack of four segments (the main part 1). */
static PoseTableEntry pose_table_body4[] = {
    {STATUS_SLEEP, "SNB_N_1"},
    {STATUS_STOP, "SNB_Y_1"},
    {STATUS_FREEZE, "SNB_Y_1"},
    {STATUS_CONFUSE, "SNB_K_1"},
    {STATUS_POISON, "SNB_X_1"},
    {STATUS_DIZZY, "SNB_X_1"},
    {BTL_POSE_NORMAL, "SNB_S_1"},
    {29, "SNB_Q_1"},
    {30, "SNB_Q_1"},
    {31, "SNB_S_1"},
    {BTL_POSE_DAMAGE, "SNB_D_1"},
    {47, "SNB_W_1"},
    {BTL_POSE_RUN, "SNB_W_1"},
    {BTL_POSE_WALK, "SNB_W_1"},
    {BTL_POSE_DANGER, "SNB_X_1"},
    {BTL_POSE_PERIL, "SNB_X_1"},
    {BTL_POSE_TALK, "SNB_T_1"},
    {BTL_POSE_STAY_DEFAULT, "SNB_S_1"},
};

/** Pose table of the Poison Pokey once it is down to three segments (part 2). */
static PoseTableEntry pose_table_body3[] = {
    {STATUS_SLEEP, "SNB_N_2"},
    {STATUS_STOP, "SNB_Y_2"},
    {STATUS_FREEZE, "SNB_Y_2"},
    {STATUS_CONFUSE, "SNB_K_2"},
    {STATUS_POISON, "SNB_X_2"},
    {STATUS_DIZZY, "SNB_X_2"},
    {BTL_POSE_NORMAL, "SNB_S_2"},
    {29, "SNB_Q_2"},
    {30, "SNB_Q_2"},
    {31, "SNB_S_2"},
    {BTL_POSE_DAMAGE, "SNB_D_2"},
    {47, "SNB_W_2"},
    {50, "SNB_A_1A"},
    {51, "SNB_A_1B"},
    {BTL_POSE_RUN, "SNB_W_2"},
    {BTL_POSE_WALK, "SNB_W_2"},
    {BTL_POSE_DANGER, "SNB_X_2"},
    {BTL_POSE_PERIL, "SNB_X_2"},
    {BTL_POSE_TALK, "SNB_T_2"},
    {BTL_POSE_STAY_DEFAULT, "SNB_S_2"},
};

/** Pose table of the Poison Pokey once it is down to two segments (part 3). */
static PoseTableEntry pose_table_body2[] = {
    {STATUS_SLEEP, "SNB_N_3"},
    {STATUS_STOP, "SNB_Y_3"},
    {STATUS_FREEZE, "SNB_Y_3"},
    {STATUS_CONFUSE, "SNB_K_3"},
    {STATUS_POISON, "SNB_X_3"},
    {STATUS_DIZZY, "SNB_X_3"},
    {BTL_POSE_NORMAL, "SNB_S_3"},
    {29, "SNB_Q_3"},
    {30, "SNB_Q_3"},
    {31, "SNB_S_3"},
    {BTL_POSE_DAMAGE, "SNB_D_3"},
    {47, "SNB_W_3"},
    {50, "SNB_A_2A"},
    {51, "SNB_A_2B"},
    {BTL_POSE_RUN, "SNB_W_3"},
    {BTL_POSE_WALK, "SNB_W_3"},
    {BTL_POSE_DANGER, "SNB_X_3"},
    {BTL_POSE_PERIL, "SNB_X_3"},
    {BTL_POSE_TALK, "SNB_T_3"},
    {BTL_POSE_STAY_DEFAULT, "SNB_S_3"},
};

/** Pose table of the Poison Pokey once only its head is left (part 4). */
static PoseTableEntry pose_table_body1[] = {
    {STATUS_SLEEP, "SNB_N_4"},
    {STATUS_STOP, "SNB_Y_4"},
    {STATUS_FREEZE, "SNB_Y_4"},
    {STATUS_CONFUSE, "SNB_K_4"},
    {STATUS_POISON, "SNB_X_4"},
    {STATUS_DIZZY, "SNB_X_4"},
    {BTL_POSE_NORMAL, "SNB_S_4"},
    {29, "SNB_Q_4"},
    {30, "SNB_Q_4"},
    {31, "SNB_S_4"},
    {BTL_POSE_DAMAGE, "SNB_D_4"},
    {47, "SNB_W_4"},
    {50, "SNB_A_3A"},
    {51, "SNB_A_3B"},
    {BTL_POSE_RUN, "SNB_W_4"},
    {BTL_POSE_WALK, "SNB_W_4"},
    {BTL_POSE_DANGER, "SNB_X_4"},
    {BTL_POSE_PERIL, "SNB_X_4"},
    {BTL_POSE_TALK, "SNB_T_4"},
    {BTL_POSE_STAY_DEFAULT, "SNB_S_4"},
};

/** Pose table of the loose segment the Poison Pokey throws or sheds (part 5). */
static PoseTableEntry pose_table_parts[] = {
    {BTL_POSE_NORMAL, "SNB_B_1"},
    {BTL_POSE_DAMAGE, "SNB_B_1"},
    {BTL_POSE_STAY_DEFAULT, "SNB_B_1"},
};

/**
 * Data table of the Poison Pokey: reaction scripts for an attacker hurt by its spikes, losing a body segment,
 * losing a body segment to a hammer blow and being swallowed; a First Strike on it triggers nothing special.
 */
static BattleDataEntry data_table[] = {
    {37, dmg_avoid_counter_thorn_side_event},
    {39, dmg_avoid_counter_thorn_side_event},
    {19, damage_event_bodylost},
    {18, damage_event_bodylost_blow},
    {16, damage_event_bodylost},
    {48, btldefaultevt_Dummy},
    {54, damage_swallow_body},
    {0, NULL},
};

/**
 * Parts of the Poison Pokey: part 1 is the full four-segment body,
 * parts 2 to 4 are the shorter stacks it shrinks to (hidden until needed)
 * and part 5 is the loose segment it throws.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_sambo_mummy", "c_sanbo_m", 0.0f, 0.0f, 0.0f, 0.0f, 84.0f, 0.0f, 0.0f, 90.0f, 0.0f, 20, 90, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, COUNTER_ATTR_TOP_SPIKY | COUNTER_ATTR_FRONT_SPIKY, pose_table_body4},
    {2, "btl_un_sambo_mummy", "c_sanbo_m", 0.0f, 0.0f, 0.0f, 0.0f, 64.0f, 0.0f, 0.0f, 70.0f, 0.0f, 20, 70, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, COUNTER_ATTR_TOP_SPIKY | COUNTER_ATTR_FRONT_SPIKY, pose_table_body3},
    {3, "btl_un_sambo_mummy", "c_sanbo_m", 0.0f, 0.0f, 0.0f, 0.0f, 44.0f, 0.0f, 0.0f, 50.0f, 0.0f, 20, 50, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, COUNTER_ATTR_TOP_SPIKY | COUNTER_ATTR_FRONT_SPIKY, pose_table_body2},
    {4, "btl_un_sambo_mummy", "c_sanbo_m", 0.0f, 0.0f, 0.0f, 0.0f, 24.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, COUNTER_ATTR_TOP_SPIKY | COUNTER_ATTR_FRONT_SPIKY, pose_table_body1},
    {5, "btl_un_sambo_mummy", "c_sanbo_m", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table_parts},
};

/**
 * Registers the Poison Pokey's wait, attack and damage events (confusion reuses the attack event),
 * sets unit work 0 (segments left) to 4 and sizes the body to match, clears unit work 1 (its summon generation),
 * shows the loose segment part 5 in its stay pose and sets its walk and run sounds.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_SAMBO_MUMMY_SEGMENTS, 4)
    CALL_CHILD(_body_param_set)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_SAMBO_MUMMY_GENERATION, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 5, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_MOVE1"), STRING("SFX_ENM_SAMBO_MOVE1"), 0, 6, 6)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_MOVE1"), STRING("SFX_ENM_SAMBO_MOVE1"), 0, 6, 6)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Data-table events 37 and 39, run by btldefaultevt_Damage for damage codes 31 and 33,
 * which BattleCheckCounter gives the Poison Pokey when its top or front spikes hurt the attacker:
 * it takes pose type 47 and shows a toge_flush spark just above its top (height scaled by its size),
 * then waits 60 frames.
 */
static EVT_BEGIN(dmg_avoid_counter_thorn_side_event)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 47)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, LW(10), LW(3))
    CALL(btlevtcmd_GetStatusMg, LW(10), LW(4))
#if VERSION <= VERSION_DEMO_JP
    MULTIPLY(LW(3), LW(4))
#else
    MULTIPLY_FLOAT(LW(3), LW(4))
#endif
    ADD(LW(1), LW(3))
    ADD(LW(1), 5)
    ADD(LW(2), 10)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

/**
 * Hit reaction: picks the part that is the visible body for the current segment count (part 1 at 4 segments down
 * to part 4 at 1) and runs btldefaultevt_Damage on it.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_MUMMY_SEGMENTS, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        SET_VALUE(LW(11), 4)
        CASE_EQUAL(2)
        SET_VALUE(LW(11), 3)
        CASE_EQUAL(3)
        SET_VALUE(LW(11), 2)
        CASE_DEFAULT
        SET_VALUE(LW(11), 1)
    END_SWITCH
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Data-table events 16 and 19: Koops' shell hits (damage pattern 8) and being hit by a unit flung by the Super
 * Hammer or Ultra Hammer (15, 17).
 * With one segment left it just flinches; otherwise it loses a segment:
 * the shorter body part takes over (with one left Yoshi can swallow it),
 * the body drops into place and the knocked-off segment bounces away, blinks and vanishes.
 */
static EVT_BEGIN(damage_event_bodylost)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_MUMMY_SEGMENTS, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_GetDamage, LW(10), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
            WAIT_FRAMES(30)
            IF_INT_NOT_EQUAL(LW(15), -1)
                CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(15))
                WAIT_FRAMES(30)
            END_IF
        ELSE
            CALL_CHILD(subsetevt_nodamage_motion)
        END_IF
    ELSE
        SET_VALUE(LW(12), LW(11))
        CALL(btlevtcmd_GetUnitWork, LW(10), UW_SAMBO_MUMMY_SEGMENTS, LW(0))
        SUBTRACT(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, LW(10), UW_SAMBO_MUMMY_SEGMENTS, LW(0))
        CALL_CHILD(_body_param_set)
        SWITCH(LW(0))
            CASE_EQUAL(1)
            SET_VALUE(LW(11), 4)
            CALL(btlevtcmd_SetSwallowParam, BTL_UNIT_SELF, 50)
            CALL(btlevtcmd_SetSwallowAttribute, BTL_UNIT_SELF, 2)
            CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 14, 20)
            CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 10, 0)
            CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 10, 16, 0)
            CASE_EQUAL(2)
            SET_VALUE(LW(11), 3)
            CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 14, 40)
            CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 20, 0)
            CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 10, 26, 0)
            CASE_EQUAL(3)
            SET_VALUE(LW(11), 2)
            CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 14, 60)
            CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 30, 0)
            CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 10, 36, 0)
            CASE_DEFAULT
            SET_VALUE(LW(11), 1)
            CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 14, 80)
            CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 40, 0)
            CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 10, 52, 0)
        END_SWITCH
        CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(12), PART_ATTR_MAIN | PART_ATTR_GUARD_COVER)
        CALL(btlevtcmd_OnPartsAttribute, LW(10), LW(12), PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
        CALL(btlevtcmd_OnPartsAttribute, LW(10), LW(11), PART_ATTR_MAIN | PART_ATTR_GUARD_COVER)
        CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(11), PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN)
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        BEGIN_SIBLING_EVENT
            WAIT_FRAMES(4)
            CALL_CHILD(subset_dmg_sambo_fall)
        END_SIBLING_EVENT
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPartsPos, LW(10), 5, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_OffPartsAttribute, LW(10), 5, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_SetPartsFallAccel, LW(10), 5, FLOAT(0.39941406f))
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), 25)
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpPartsPosition, LW(10), 5, LW(0), LW(1), LW(2), 16, -1)
        CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), 16)
        CALL(btlevtcmd_JumpPartsPosition, LW(10), 5, LW(0), LW(1), LW(2), 12, -1)
        LOOP(40)
            CALL(btlevtcmd_OnPartsAttribute, LW(10), 5, PART_ATTR_HIDDEN)
            WAIT_FRAMES(1)
            CALL(btlevtcmd_OffPartsAttribute, LW(10), 5, PART_ATTR_HIDDEN)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_OnPartsAttribute, LW(10), 5, PART_ATTR_HIDDEN)
    END_IF
    RETURN
EVT_END()

/**
 * Run while a segment is lost: the body (LW(10), part LW(11)) takes the hurt pose LW(14),
 * pops up 18 units and settles down in a few bouncing steps, so the stack looks one segment shorter.
 */
static EVT_BEGIN(subset_dmg_sambo_fall)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    ADD(LW(1), 18)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    SET_VALUE(LW(3), LW(1))
    WAIT_FRAMES(2)
    SUBTRACT(LW(3), 1)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(3)
    SUBTRACT(LW(3), 2)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(2)
    SUBTRACT(LW(3), 3)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    SUBTRACT(LW(3), 5)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    SUBTRACT(LW(3), 7)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    ADD(LW(3), 2)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    ADD(LW(3), 3)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    ADD(LW(3), 3)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    SUBTRACT(LW(3), 3)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    SUBTRACT(LW(3), 3)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    SUBTRACT(LW(3), 2)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    RETURN
EVT_END()

/**
 * Data-table event 18: a Super Hammer or Ultra Hammer hit (damage patterns 14, 16).
 * With one segment left it takes the shot reaction;
 * otherwise it loses a segment as in damage_event_bodylost,
 * but the knocked-off segment flies off stage through the allies behind it,
 * hitting each as a Super/Ultra Hammer "involved" unit.
 * After an Ultra Hammer hit the Pokey also takes the Ultra Hammer finishing hit.
 */
static EVT_BEGIN(damage_event_bodylost_blow)
    // With only the head left there is nothing to knock off: just the knock-back or no-damage reaction plays.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_MUMMY_SEGMENTS, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_GetDamage, LW(10), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL_CHILD(subsetevt_shot_damage)
        ELSE
            CALL_CHILD(subsetevt_nodamage_motion)
        END_IF
    ELSE
        SET_VALUE(LW(12), LW(11))
        CALL(btlevtcmd_GetUnitWork, LW(10), UW_SAMBO_MUMMY_SEGMENTS, LW(0))
        SUBTRACT(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, LW(10), UW_SAMBO_MUMMY_SEGMENTS, LW(0))
        // The Poison Pokey loses a segment: the stack gets one shorter and its sizes and hit positions are
        // adjusted.
        CALL_CHILD(_body_param_set)
        SWITCH(LW(0))
            CASE_EQUAL(1)
            SET_VALUE(LW(11), 4)
            CALL(btlevtcmd_SetSwallowParam, BTL_UNIT_SELF, 50)
            CALL(btlevtcmd_SetSwallowAttribute, BTL_UNIT_SELF, 2)
            CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 14, 20)
            CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 10, 0)
            CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 10, 16, 0)
            CASE_EQUAL(2)
            SET_VALUE(LW(11), 3)
            CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 14, 40)
            CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 20, 0)
            CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 10, 26, 0)
            CASE_EQUAL(3)
            SET_VALUE(LW(11), 2)
            CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 14, 60)
            CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 30, 0)
            CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 10, 36, 0)
            CASE_DEFAULT
            SET_VALUE(LW(11), 1)
            CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 14, 80)
            CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 40, 0)
            CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 10, 52, 0)
        END_SWITCH
        CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(12), PART_ATTR_MAIN | PART_ATTR_GUARD_COVER)
        CALL(btlevtcmd_OnPartsAttribute, LW(10), LW(12), PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
        CALL(btlevtcmd_OnPartsAttribute, LW(10), LW(11), PART_ATTR_MAIN | PART_ATTR_GUARD_COVER)
        CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(11), PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN)
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        BEGIN_SIBLING_EVENT
            WAIT_FRAMES(4)
            // The knocked-off segment (part 5) is thrown aside while the rest of the stack drops into place.
            CALL_CHILD(subset_dmg_sambo_fall)
        END_SIBLING_EVENT
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPartsPos, LW(10), 5, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_OffPartsAttribute, LW(10), 5, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_CheckDamagePattern, LW(10), 15, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SET_VALUE(LW(13), PTR(&marioWeapon_KaitenHammerInvolved))
        ELSE
            SET_VALUE(LW(13), PTR(&marioWeapon_UltraHammerInvolved))
        END_IF
        // It flies along the Poison Pokey's side and hits each unit behind it in turn.
        CALL(btlevtcmd_GetFriendBelong, LW(10), LW(0))
        CALL(btlevtcmd_SamplingEnemy, LW(10), LW(0), LW(13))
        CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
        LABEL(0)
        IF_INT_EQUAL(LW(3), -1)
            GOTO(50)
        END_IF
        CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(10))
        IF_INT_NOT_EQUAL(LW(10), LW(3))
            CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
            GOTO(0)
        END_IF
        LABEL(10)
        CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
        IF_INT_EQUAL(LW(3), -1)
            GOTO(50)
        END_IF
        CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetHomePos, LW(10), EVT_NULLPTR, LW(1), EVT_NULLPTR)
        ADD(LW(1), 15)
        CALL(btlevtcmd_JumpPartsSetting, LW(10), 5, 0, FLOAT(5.0f), FLOAT(0.009765625f))
        CALL(btlevtcmd_JumpPartsPosition, LW(10), 5, LW(0), LW(1), LW(2), 0, -1)
        // That unit takes the segment as a hit.
        CALL(btlevtcmd_CheckDamage, LW(10), LW(3), LW(4), LW(13), DAMAGE_FLAG_LAST_HIT, LW(5))
        GOTO(10)
        LABEL(50)
        // The segment keeps going until it flies off the edge of the stage.
        CALL(btlevtcmd_GetStageSize, LW(5), EVT_NULLPTR, EVT_NULLPTR)
        SET_VALUE(LW(0), 0)
        CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), LW(5))
        CALL(btlevtcmd_GetPos, LW(10), EVT_NULLPTR, LW(1), EVT_NULLPTR)
        CALL(btlevtcmd_JumpPartsSetting, LW(10), 5, 0, FLOAT(5.0f), FLOAT(0.009765625f))
        CALL(btlevtcmd_JumpPartsPosition, LW(10), 5, LW(0), LW(1), LW(2), 0, -1)
        CALL(btlevtcmd_OnPartsAttribute, LW(10), 5, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_CheckDamagePattern, LW(10), 16, LW(5))
        IF_INT_NOT_EQUAL(LW(5), 0)
            // After an Ultra Hammer hit the Poison Pokey also takes the finishing blow.
            CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), PTR(marioWeapon_UltraHammerFinish), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_AC_SUCCESS, LW(5))
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Data-table event 54, Yoshi's Gulp.
 * With one segment left it just plays the hurt pose;
 * otherwise it loses a segment: the shorter body settles and the loose segment slides 25 units forward
 * and vanishes.
 */
static EVT_BEGIN(damage_swallow_body)
    SET_VALUE(LW(14), 39)
    SET_VALUE(LW(15), -1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_MUMMY_SEGMENTS, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_GetDamage, LW(10), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
            WAIT_FRAMES(30)
            IF_INT_NOT_EQUAL(LW(15), -1)
                CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(15))
                WAIT_FRAMES(30)
            END_IF
        ELSE
            CALL_CHILD(subsetevt_nodamage_motion)
        END_IF
    ELSE
        WAIT_FRAMES(3)
        SET_VALUE(LW(12), LW(11))
        CALL(btlevtcmd_GetUnitWork, LW(10), UW_SAMBO_MUMMY_SEGMENTS, LW(0))
        SUBTRACT(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, LW(10), UW_SAMBO_MUMMY_SEGMENTS, LW(0))
        CALL_CHILD(_body_param_set)
        SWITCH(LW(0))
            CASE_EQUAL(1)
            SET_VALUE(LW(11), 4)
            CALL(btlevtcmd_SetSwallowParam, BTL_UNIT_SELF, 50)
            CALL(btlevtcmd_SetSwallowAttribute, BTL_UNIT_SELF, 2)
            CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 14, 20)
            CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 10, 0)
            CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 10, 16, 0)
            CASE_EQUAL(2)
            SET_VALUE(LW(11), 3)
            CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 14, 40)
            CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 20, 0)
            CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 10, 26, 0)
            CASE_EQUAL(3)
            SET_VALUE(LW(11), 2)
            CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 14, 60)
            CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 30, 0)
            CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 10, 36, 0)
            CASE_DEFAULT
            SET_VALUE(LW(11), 1)
            CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 14, 80)
            CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 40, 0)
            CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 10, 52, 0)
        END_SWITCH
        BEGIN_SIBLING_EVENT
            WAIT_FRAMES(3)
            CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(12), PART_ATTR_MAIN | PART_ATTR_GUARD_COVER)
            CALL(btlevtcmd_OnPartsAttribute, LW(10), LW(12), PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
            CALL(btlevtcmd_OnPartsAttribute, LW(10), LW(11), PART_ATTR_MAIN | PART_ATTR_GUARD_COVER)
            CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(11), PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN)
            CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
            WAIT_FRAMES(1)
            CALL_CHILD(subset_dmg_sambo_fall)
        END_SIBLING_EVENT
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPartsPos, LW(10), 5, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_OffPartsAttribute, LW(10), 5, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 25)
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_DivePartsPosition, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2), 5, 0, 0, 0, -1)
        CALL(btlevtcmd_OnPartsAttribute, LW(10), 5, PART_ATTR_HIDDEN)
        WAIT_FRAMES(20)
    END_IF
    RETURN
EVT_END()

/**
 * The Poison Pokey's turn (also used when confused): uses a held item if the AI wants to.
 * At full height, if it is not already a second-generation summon,
 * there is a 20% chance to call another Poison Pokey into the free spot 40 units in front of it.
 * With 2 or more segments it head-bashes the frontmost target 31 times in 70 (if one is in reach),
 * else throws one of its segments; with one segment left it hops over and stomps.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_MUMMY_SEGMENTS, LW(10))
    SWITCH(LW(10))
        CASE_EQUAL(1)
        SET_VALUE(LW(11), 4)
        CASE_EQUAL(2)
        SET_VALUE(LW(11), 3)
        CASE_EQUAL(3)
        SET_VALUE(LW(11), 2)
        CASE_DEFAULT
        SET_VALUE(LW(11), 1)
    END_SWITCH
    IF_INT_EQUAL(LW(10), 4)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_MUMMY_GENERATION, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 1)
            CALL(evt_sub_random, 99, LW(0))
            IF_INT_LESS(LW(0), 20)
                CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(6), LW(7), LW(8))
                CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(6), 40)
                SUBTRACT(LW(8), 10)
                CALL(btlevtcmd_CheckSpace, LW(3), LW(6), LW(7), LW(8), 40, 0, 0, 0)
                IF_INT_EQUAL(LW(3), -1)
                    IF_INT_GREATER(LW(6), 0)
                        CALL_CHILD(call_friend_event)
                        GOTO(99)
                    END_IF
                END_IF
            END_IF
        END_IF
    END_IF
    IF_INT_GREATER_OR_EQUAL(LW(10), 2)
        CALL(evt_sub_random, 69, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 30)
            SWITCH(LW(10))
                CASE_EQUAL(4)
                CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
                CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_mummy_head_attack_4))
                CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_mummy_head_attack_4), LW(3), LW(4))
                CASE_EQUAL(3)
                CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
                CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_mummy_head_attack_3))
                CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_mummy_head_attack_3), LW(3), LW(4))
                CASE_EQUAL(2)
                CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
                CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_mummy_head_attack_2))
                CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_mummy_head_attack_2), LW(3), LW(4))
            END_SWITCH
            IF_INT_NOT_EQUAL(LW(3), -1)
                CALL_CHILD(attack_head_2_event)
                RETURN
            END_IF
        END_IF
        CALL_CHILD(attack_spike_event)
        RETURN
    END_IF
    CALL_CHILD(attack_head_1_event)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Head bash with 2-4 segments: walks up to the frontmost target (closer when Tiny), leans back,
 * then topples its body onto it for 4 damage (3 in the retail releases; one weapon per height) with a 60% chance
 * of 10 turns of Poison. It swings back upright and walks home.
 */
static EVT_BEGIN(attack_head_2_event)
    SET_VALUE(LW(6), LW(11))
    // A Tiny Poison Pokey stands closer to its target.
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_TINY, LW(5))
    SWITCH(LW(10))
        CASE_EQUAL(4)
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        // A target is picked using the weapon for the stack height (4, 3 or 2 segments).
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_mummy_head_attack_4))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_mummy_head_attack_4), LW(3), LW(4))
        CASE_EQUAL(3)
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_mummy_head_attack_3))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_mummy_head_attack_3), LW(3), LW(4))
        CASE_EQUAL(2)
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_mummy_head_attack_2))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_mummy_head_attack_2), LW(3), LW(4))
    END_SWITCH
    // No target to attack: a confused Poison Pokey just flusters about, otherwise it skips its turn.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // The headbutt is declared.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    SWITCH(LW(10))
        CASE_EQUAL(4)
        CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_sambo_mummy_head_attack_4))
        CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_sambo_mummy_head_attack_4))
        CASE_EQUAL(3)
        CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_sambo_mummy_head_attack_3))
        CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_sambo_mummy_head_attack_3))
        CASE_EQUAL(2)
        CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_sambo_mummy_head_attack_2))
        CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_sambo_mummy_head_attack_2))
    END_SWITCH
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    SWITCH(LW(10))
        CASE_EQUAL(4)
        IF_INT_EQUAL(LW(5), 0)
            CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 60)
        ELSE
            CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 42)
        END_IF
        CASE_EQUAL(3)
        IF_INT_EQUAL(LW(5), 0)
            CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 40)
        ELSE
            CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 28)
        END_IF
        CASE_EQUAL(2)
        IF_INT_EQUAL(LW(5), 0)
            CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 20)
        ELSE
            CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 14)
        END_IF
    END_SWITCH
    // The whole stack walks up to the target.
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), BTL_POSE_WALK)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(2.0f))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), BTL_POSE_STAY)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    SET_VALUE(LW(14), 40)
    IF_INT_EQUAL(LW(15), -1)
        SET_VALUE(LW(14), -40)
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 0, 0)
    // It leans back 40 degrees to wind up.
    CALL(evt_sub_intpl_init, 11, 0, LW(14), 40)
    LABEL(0)
    CALL(evt_sub_intpl_get_value)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    SET_VALUE(LW(13), 40)
    SET_VALUE(LW(14), -90)
    IF_INT_EQUAL(LW(15), -1)
        SET_VALUE(LW(13), -40)
        SET_VALUE(LW(14), 90)
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_ATTACK4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    // Then it swings the whole stack forward onto the target.
    CALL(evt_sub_intpl_init, 1, LW(13), LW(14), 10)
    LABEL(3)
    CALL(evt_sub_intpl_get_value)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(3)
    END_IF
    SWITCH(LW(10))
        CASE_EQUAL(4)
        // Check whether the attack will connect; a miss sends the target into its dodge.
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_mummy_head_attack_4), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_mummy_head_attack_3), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(2)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_mummy_head_attack_2), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_SWITCH
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
    // A miss: the target dodges and the stack swings back upright.
    LABEL(90)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    SET_VALUE(LW(14), -90)
    IF_INT_EQUAL(LW(15), -1)
        SET_VALUE(LW(14), 90)
    END_IF
    CALL(evt_sub_intpl_init, 0, LW(14), 0, 10)
    LABEL(4)
    CALL(evt_sub_intpl_get_value)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(4)
    END_IF
    GOTO(98)
    // A hit: the target takes the damage and the stack straightens up.
    LABEL(91)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    SWITCH(LW(10))
        CASE_EQUAL(4)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_sambo_mummy_head_attack_4))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_mummy_head_attack_4), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_sambo_mummy_head_attack_3))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_mummy_head_attack_3), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(2)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_sambo_mummy_head_attack_2))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_mummy_head_attack_2), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_SWITCH
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 90)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), BTL_POSE_STAY)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    SET_VALUE(LW(14), -90)
    IF_INT_EQUAL(LW(15), -1)
        SET_VALUE(LW(14), 90)
    END_IF
    CALL(evt_sub_intpl_init, 0, LW(14), 0, 20)
    LABEL(5)
    CALL(evt_sub_intpl_get_value)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(5)
    END_IF
    // The headbutt is over: the stack walks back to its place.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), 41)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    // Turn finished: the Poison Pokey goes back to waiting.
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Attack with a single segment: hops up to the target (sambo_rabbit_move),
 * then leaps onto it spinning for 5 damage with a 60% chance of Poison and bounces back in hops;
 * on a miss or dodge it flips over the target and lands behind it. Then it hops home.
 */
static EVT_BEGIN(attack_head_1_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_mummy_head_attack_1))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_mummy_head_attack_1), LW(3), LW(4))
    // No target to attack: a confused Poison Pokey just flusters about, otherwise it skips its turn.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_sambo_mummy_head_attack_1))
    // The lone segment announces its attack.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_sambo_mummy_head_attack_1))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(2.0f))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5996094f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(5), LW(6), LW(7))
    CALL(btlevtcmd_TransStageFloorPosition, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(5), 50)
    SET_VALUE(LW(8), 35)
    // It hops up to 50 units in front of the target, 35 units at a time.
    CALL_CHILD(sambo_rabbit_move)
    WAIT_FRAMES(10)
    // Check whether the attack will connect; a miss sends the target into its dodge.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_mummy_head_attack_1), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // A miss: it leaps right over the target, tilting forward, and lands beyond it.
    LABEL(90)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.2998047f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 5)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    ADD(LW(1), 10)
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(2)
        CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
        SET_VALUE(LW(14), -10)
        IF_INT_EQUAL(LW(15), -1)
            SET_VALUE(LW(14), 10)
        END_IF
        SET_VALUE(LW(0), 0)
        LOOP(15)
            ADD(LW(0), LW(14))
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 44, -1)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 10, 0)
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(2)
        CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
        SET_VALUE(LW(0), 180)
        LOOP(12)
            IF_INT_EQUAL(LW(15), -1)
                ADD(LW(0), 15)
                IF_INT_EQUAL(LW(0), 360)
                    SET_VALUE(LW(0), 0)
                END_IF
            ELSE
                SUBTRACT(LW(0), 15)
                IF_INT_EQUAL(LW(0), 0)
                    SET_VALUE(LW(0), 360)
                END_IF
            END_IF
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 0, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 30)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(30)
    CALL(evt_btl_camera_set_mode, 0, 0)
    GOTO(98)
    // A hit: it leaps onto the target, tilting forward, and the target takes the damage.
    LABEL(91)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    ADD(LW(1), 10)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.2998047f))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(2)
        CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
        SET_VALUE(LW(14), -10)
        IF_INT_EQUAL(LW(15), -1)
            SET_VALUE(LW(14), 10)
        END_IF
        SET_VALUE(LW(0), 0)
        LOOP(15)
            ADD(LW(0), LW(14))
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 36, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_ATTACK6"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    WAIT_FRAMES(2)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_sambo_mummy_head_attack_1))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_mummy_head_attack_1), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.89941406f))
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    // It bounces off the target in four shrinking hops.
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 30)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 16, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 10)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 8, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 4, BTL_POSE_STAY)
    // It hops back to its place.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 4, 41)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
    SET_VALUE(LW(8), 35)
    CALL_CHILD(sambo_rabbit_move)
    // Turn finished: the Poison Pokey goes back to waiting.
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Throws one of its own segments at the target:
 * the Pokey loses a segment (shorter body, at one segment Yoshi can swallow it) and the loose segment pops up
 * and flies at the target. On a miss it flies off stage; on a hit it bounces away (4 damage, 3 in the demos).
 * Result 21 (a Superguard) sends the segment back to hit the Pokey itself.
 */
static EVT_BEGIN(attack_spike_event)
    // The weapon depends on how many segments the stack has (4, 3 or 2).
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_MUMMY_SEGMENTS, LW(10))
    SWITCH(LW(10))
        CASE_EQUAL(4)
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_mummy_spike_attack_4))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_mummy_spike_attack_4), LW(3), LW(4))
        CASE_EQUAL(3)
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_mummy_spike_attack_3))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_mummy_spike_attack_3), LW(3), LW(4))
        CASE_EQUAL(2)
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_mummy_spike_attack_2))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_mummy_spike_attack_2), LW(3), LW(4))
    END_SWITCH
    // No target to attack: a confused Poison Pokey just flusters about, otherwise it skips its turn.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // The throw is declared.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    SWITCH(LW(10))
        CASE_EQUAL(4)
        CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_sambo_mummy_spike_attack_4))
        CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_sambo_mummy_spike_attack_4))
        CASE_EQUAL(3)
        CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_sambo_mummy_spike_attack_3))
        CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_sambo_mummy_spike_attack_3))
        CASE_EQUAL(2)
        CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_sambo_mummy_spike_attack_2))
        CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_sambo_mummy_spike_attack_2))
    END_SWITCH
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_TINY, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        // The segment about to be thrown (part 5) is smaller when the Poison Pokey is Tiny.
        CALL(btlevtcmd_SetPartsScale, BTL_UNIT_SELF, 5, FLOAT(0.69921875f), FLOAT(0.69921875f), FLOAT(1.0f))
    ELSE
        CALL(btlevtcmd_SetPartsScale, BTL_UNIT_SELF, 5, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_MUMMY_SEGMENTS, LW(10))
    SUBTRACT(LW(10), 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_SAMBO_MUMMY_SEGMENTS, LW(10))
    // The stack loses a segment, as when it is knocked off.
    CALL_CHILD(_body_param_set)
    SWITCH(LW(10))
        CASE_EQUAL(3)
        SET_VALUE(LW(7), 1)
        SET_VALUE(LW(6), 2)
        CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 14, 60)
        CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 30, 0)
        CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 10, 36, 0)
        CASE_EQUAL(2)
        SET_VALUE(LW(7), 2)
        SET_VALUE(LW(6), 3)
        CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 14, 40)
        CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 20, 0)
        CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 10, 26, 0)
        CASE_EQUAL(1)
        SET_VALUE(LW(7), 3)
        SET_VALUE(LW(6), 4)
        CALL(btlevtcmd_SetSwallowParam, BTL_UNIT_SELF, 50)
        CALL(btlevtcmd_SetSwallowAttribute, BTL_UNIT_SELF, 2)
        CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 14, 20)
        CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 10, 0)
        CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 10, 16, 0)
    END_SWITCH
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(7), PART_ATTR_MAIN | PART_ATTR_GUARD_COVER)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(7), PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(6), PART_ATTR_MAIN | PART_ATTR_GUARD_COVER)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(6), PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN)
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_TINY, LW(5))
    // The loose segment pops up and flies toward the target.
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        IF_INT_EQUAL(LW(5), 0)
            SET_VALUE(LW(9), 20)
            SET_VALUE(LW(11), 20)
        ELSE
            SET_VALUE(LW(9), 14)
            SET_VALUE(LW(11), 14)
        END_IF
        MULTIPLY(LW(9), LW(10))
        SUBTRACT(LW(9), LW(11))
        ADD(LW(1), LW(9))
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 5, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 5, FLOAT(0.5996094f))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("SNB_B_1"))
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2), 30, -1)
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_ATTACK3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    // The Poison Pokey rears back and throws it.
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), 50)
    WAIT_FRAMES(24)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_ATTACK4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_ATTACK5"), EVT_NULLPTR, 0, LW(14))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), 51)
    WAIT_FRAMES(2)
    WAIT_FRAMES(5)
    SWITCH(LW(10))
        CASE_EQUAL(3)
        // Check whether the attack will connect; a miss sends the target into its dodge.
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_mummy_spike_attack_4), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(2)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_mummy_spike_attack_3), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(1)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_mummy_spike_attack_2), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_SWITCH
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
    // A miss: the segment flies off the stage while the target dodges.
    LABEL(90)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageSize, LW(0), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(9))
    MULTIPLY(LW(0), LW(9))
    SUBTRACT(LW(1), 5)
    CALL(btlevtcmd_SetPartsMoveSpeed, BTL_UNIT_SELF, 5, FLOAT(10.0f))
    CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 5, FLOAT(0.099609375f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2), 0, -1)
    CALL(evt_snd_sfxoff, LW(14))
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 5, PART_ATTR_HIDDEN)
    GOTO(99)
    // A hit: the target takes the damage and the segment bounces away across the floor and vanishes.
    LABEL(91)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPartsMoveSpeed, BTL_UNIT_SELF, 5, FLOAT(10.0f))
    CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 5, FLOAT(0.099609375f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2), 0, -1)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    SWITCH(LW(10))
        CASE_EQUAL(3)
        SET_VALUE(LW(12), PTR(&weapon_sambo_mummy_spike_attack_4))
        CASE_EQUAL(2)
        SET_VALUE(LW(12), PTR(&weapon_sambo_mummy_spike_attack_3))
        CASE_EQUAL(1)
        SET_VALUE(LW(12), PTR(&weapon_sambo_mummy_spike_attack_2))
    END_SWITCH
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), BTL_POSE_STAY)
    // Superguard: the segment flies back and hits the Poison Pokey itself.
    IF_INT_EQUAL(LW(5), 21)
        CALL(evt_snd_sfxoff, LW(14))
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(11))
        CALL(btlevtcmd_GetHitPos, BTL_UNIT_SELF, LW(11), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPartsMoveSpeed, BTL_UNIT_SELF, 5, FLOAT(4.5f))
        CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 5, FLOAT(0.39941406f))
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2), 40, -1)
        BEGIN_INLINE_EVENT
            CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 55)
            CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetPartsMoveSpeed, BTL_UNIT_SELF, 5, FLOAT(3.0f))
            CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 5, FLOAT(0.099609375f))
            CALL(btlevtcmd_DivePartsPosition, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2), 0, 25, 0, 0, -1)
            CALL(btlevtcmd_SetPartsMoveSpeed, BTL_UNIT_SELF, 5, FLOAT(2.0f))
            CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 24)
            CALL(btlevtcmd_DivePartsPosition, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2), 0, 21, 0, 0, -1)
            CALL(btlevtcmd_SetPartsMoveSpeed, BTL_UNIT_SELF, 5, FLOAT(1.5f))
            CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
            CALL(btlevtcmd_DivePartsPosition, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2), 0, 20, 0, 0, -1)
            CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 5, PART_ATTR_HIDDEN)
        END_INLINE_EVENT
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, BTL_UNIT_SELF, LW(11), LW(12), DAMAGE_FLAG_LAST_HIT, LW(5))
        RETURN
    END_IF
    CALL(evt_snd_sfxoff, LW(14))
    CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 55)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPartsMoveSpeed, BTL_UNIT_SELF, 5, FLOAT(3.0f))
    CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 5, FLOAT(0.099609375f))
    CALL(btlevtcmd_DivePartsPosition, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2), 0, 25, 0, 0, -1)
    CALL(btlevtcmd_SetPartsMoveSpeed, BTL_UNIT_SELF, 5, FLOAT(2.0f))
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 24)
    CALL(btlevtcmd_DivePartsPosition, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2), 0, 21, 0, 0, -1)
    CALL(btlevtcmd_SetPartsMoveSpeed, BTL_UNIT_SELF, 5, FLOAT(1.5f))
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 20)
    CALL(btlevtcmd_DivePartsPosition, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2), 0, 20, 0, 0, -1)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 5, PART_ATTR_HIDDEN)
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    // Turn finished: the Poison Pokey goes back to waiting.
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Summons another Poison Pokey: sways back and forth with the summon sounds,
 * then spawns entry_sambo below the free spot LW(6)-LW(8),
 * which pops out of the ground in smoke and makes the spot its home.
 * The new Pokey's unit work 1 is the caller's plus one, which limits how many generations can summon.
 */
static EVT_BEGIN(call_friend_event)
    // The Poison Pokey sways left and right in widening arcs.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("SNB_S_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_SEND_GROUP1_3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_sub_intpl_init, 11, 0, -20, 40)
    LABEL(0)
    CALL(evt_sub_intpl_get_value)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_SEND_GROUP1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_sub_intpl_init, 11, -20, 30, 40)
    LABEL(1)
    CALL(evt_sub_intpl_get_value)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_SEND_GROUP1_1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_sub_intpl_init, 11, 30, -40, 40)
    LABEL(2)
    CALL(evt_sub_intpl_get_value)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(2)
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_SEND_GROUP2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_sub_intpl_init, 11, -40, 90, 20)
    LABEL(3)
    CALL(evt_sub_intpl_get_value)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(3)
    END_IF
    WAIT_FRAMES(40)
    BEGIN_INLINE_EVENT
        CALL(evt_btl_camera_shake_h, 0, 2, 0, 10, 13)
    END_INLINE_EVENT
    // A new Poison Pokey is spawned beneath the floor beside it.
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_sambo), 0)
    SET_VALUE(LW(0), LW(6))
    SET_VALUE(LW(1), LW(7))
    SET_VALUE(LW(2), LW(8))
    SUBTRACT(LW(1), 80)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        // A puff of smoke goes up as the new one rises out of the floor.
        CALL(evt_eff, 0, STRING("kemuri_test"), 14, LW(0), LW(1), LW(2), FLOAT(1.5f), 0, 0, 0, 0, 0, 0, 0)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_SEND_GROUP3"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, LW(3), 1, STRING("SNB_D_1"))
        CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetFallAccel, LW(3), FLOAT(0.69921875f))
        CALL(btlevtcmd_JumpPosition, LW(3), LW(6), LW(7), LW(8), 20, -1)
        CALL(btlevtcmd_SetHomePos, LW(3), LW(6), LW(7), LW(8))
        WAIT_FRAMES(40)
        CALL(btlevtcmd_StartWaitEvent, LW(3))
    END_SIBLING_EVENT
    // The new one counts one call deeper than the caller, which caps how many may call friends.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_MUMMY_GENERATION, LW(4))
    ADD(LW(4), 1)
    CALL(btlevtcmd_SetUnitWork, LW(3), UW_SAMBO_MUMMY_GENERATION, LW(4))
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_sub_intpl_init, 4, 90, -30, 14)
    LABEL(4)
    CALL(evt_sub_intpl_get_value)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(4)
    END_IF
    WAIT_FRAMES(40)
    // The caller settles back upright.
    CALL(evt_sub_intpl_init, 11, -30, 0, 20)
    LABEL(5)
    CALL(evt_sub_intpl_get_value)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(5)
    END_IF
    WAIT_FRAMES(40)
    RETURN
EVT_END()

/**
 * Spawn setup for another Poison Pokey, which the Poison Pokey calls into the battle:
 * enemy side, acting in the enemy phase, placed far off-screen until the calling script moves it into position.
 */
static BattleUnitSetup entry_sambo = {
    &unit_sambo_mummy, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/** Idle: plays the stand pose of whichever body part matches the current segment count. */
static EVT_BEGIN(wait_event)
    SET_VALUE(LW(10), -2)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_MUMMY_SEGMENTS, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        SET_VALUE(LW(11), 4)
        CASE_EQUAL(2)
        SET_VALUE(LW(11), 3)
        CASE_EQUAL(3)
        SET_VALUE(LW(11), 2)
        CASE_DEFAULT
        SET_VALUE(LW(11), 1)
    END_SWITCH
    CALL(btlevtcmd_AnimeChangePoseFromTable, LW(10), LW(11))
    RETURN
EVT_END()

/**
 * Moves the Pokey in hops toward x = LW(5): hops of LW(8) units at height LW(6) while farther away than that,
 * then a last hop onto LW(5)/LW(6)/LW(7), each with SFX_ENM_SAMBO_MOVE2.
 */
static EVT_BEGIN(sambo_rabbit_move)
    LABEL(0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(11), LW(5))
    SUBTRACT(LW(11), LW(0))
    SET_VALUE(LW(12), LW(11))
    IF_INT_LESS(LW(12), 0)
        MULTIPLY(LW(12), -1)
    END_IF
    IF_INT_GREATER(LW(12), LW(8))
        IF_INT_GREATER_OR_EQUAL(LW(11), 0)
            ADD(LW(0), LW(8))
        ELSE
            SUBTRACT(LW(0), LW(8))
        END_IF
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(6), LW(2), 0, -1)
        GOTO(0)
    ELSE
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(5), LW(6), LW(7), 0, -1)
    END_IF
    RETURN
EVT_END()

/** Sets the Pokey's height and cut height to 20 per segment left (unit work 0): 20, 40, 60, or 80 at full height. */
static EVT_BEGIN(_body_param_set)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_MUMMY_SEGMENTS, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetHeight, BTL_UNIT_SELF, 20)
        CALL(btlevtcmd_SetCutHeight, BTL_UNIT_SELF, 20)
        CASE_EQUAL(2)
        CALL(btlevtcmd_SetHeight, BTL_UNIT_SELF, 40)
        CALL(btlevtcmd_SetCutHeight, BTL_UNIT_SELF, 40)
        CASE_EQUAL(3)
        CALL(btlevtcmd_SetHeight, BTL_UNIT_SELF, 60)
        CALL(btlevtcmd_SetCutHeight, BTL_UNIT_SELF, 60)
        CASE_DEFAULT
        CALL(btlevtcmd_SetHeight, BTL_UNIT_SELF, 80)
        CALL(btlevtcmd_SetCutHeight, BTL_UNIT_SELF, 80)
    END_SWITCH
    RETURN
EVT_END()
