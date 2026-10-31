// Pit of 100 Trials battle unit: the Pokey (`sambo`): parts, stats, poses and AI scripts.

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

// Unit work slots of the Pokey (btlevtcmd_SetUnitWork / GetUnitWork).
enum {
    UW_SAMBO_SEGMENTS = 0,       // body segments left (4 at the start); picks the target part and the height
    UW_SAMBO_FRIENDS_CALLED = 1, // Pokeys called in so far (call_friend_event); a new one inherits it
};

BattleUnitKind unit_sambo;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleWeapon weapon_sambo_head_attack_4;
static BattleWeapon weapon_sambo_head_attack_3;
static BattleWeapon weapon_sambo_head_attack_2;
static BattleWeapon weapon_sambo_head_attack_1;
static BattleWeapon weapon_sambo_spike_attack_4;
static BattleWeapon weapon_sambo_spike_attack_3;
static BattleWeapon weapon_sambo_spike_attack_2;
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
 * Unit data of the Pokey in the Pit of 100 Trials: 4 HP, level 11;
 * names its parts, status table and init script.
 */
BattleUnitKind unit_sambo = {
    39,
    "btl_un_sambo",
    4,
    0,
    1,
    1,
    11,
    0,
    1,
    70,
    1,
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
    10.0f,
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

/**
 * Defence of the Pokey against each element (normal, fire, ice, explosion, electric):
 * none, so every hit does its full damage.
 */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/**
 * Damage modifiers of the Pokey per element (normal, fire, ice, explosion, electric):
 * none, so no element is a weakness, an immunity or a heal.
 */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Demo values of the status vulnerability of the Pokey:
 * percent chance that each status takes hold (100 is normal).
 */
static StatusVulnerability regist = {90, 80, 80, 100, 90, 100, 100, 50, 100, 90, 100, 90, 100, 90, 90, 100, 90, 100, 90, 100, 100, 100};
#else
/**
 * JP, US and PAL values of the status vulnerability of the Pokey:
 * percent chance that each status takes hold (100 is normal).
 */
static StatusVulnerability regist = {95, 80, 80, 100, 90, 100, 100, 60, 100, 90, 100, 90, 100, 95, 90, 100, 90, 100, 90, 100, 100, 100};
#endif

/** Weapon of the Pokey's head attack with a stack of 4 segments: damage 2. */
static BattleWeapon weapon_sambo_head_attack_4 = {
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
    TARGET_PROP_NO_CEILING | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    0, // counterResistFlags
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

/** Weapon of the Pokey's head attack with a stack of 3 segments: damage 2. */
static BattleWeapon weapon_sambo_head_attack_3 = {
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
    TARGET_PROP_NO_CEILING | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    0, // counterResistFlags
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

/** Weapon of the Pokey's head attack with a stack of 2 segments: damage 2. */
static BattleWeapon weapon_sambo_head_attack_2 = {
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
    TARGET_PROP_NO_CEILING | TARGET_PROP_SHELL_TOSS_LIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    0, // counterResistFlags
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

/**
 * Weapon of the Pokey's hop-and-spin attack once only its head is left:
 * damage 3 in the demos, 4 in JP, US and PAL.
 */
static BattleWeapon weapon_sambo_head_attack_1 = {
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
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#else
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#endif
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

/** Weapon of the Pokey's thrown-segment attack with a stack of 4 segments: damage 3. */
static BattleWeapon weapon_sambo_spike_attack_4 = {
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

/** Weapon of the Pokey's thrown-segment attack with a stack of 3 segments: damage 3. */
static BattleWeapon weapon_sambo_spike_attack_3 = {
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

/** Weapon of the Pokey's thrown-segment attack with a stack of 2 segments: damage 3. */
static BattleWeapon weapon_sambo_spike_attack_2 = {
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

/** Pose table of the Pokey while its stack is 4 segments tall: animation names for each pose type. */
static PoseTableEntry pose_table_body4[] = {
    {1, "SNB_N_1"},
    {2, "SNB_Y_1"},
    {9, "SNB_Y_1"},
    {5, "SNB_K_1"},
    {4, "SNB_X_1"},
    {3, "SNB_X_1"},
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

/** Pose table of the Pokey while its stack is 3 segments tall: animation names for each pose type. */
static PoseTableEntry pose_table_body3[] = {
    {1, "SNB_N_2"},
    {2, "SNB_Y_2"},
    {9, "SNB_Y_2"},
    {5, "SNB_K_2"},
    {4, "SNB_X_2"},
    {3, "SNB_X_2"},
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

/** Pose table of the Pokey while its stack is 2 segments tall: animation names for each pose type. */
static PoseTableEntry pose_table_body2[] = {
    {1, "SNB_N_3"},
    {2, "SNB_Y_3"},
    {9, "SNB_Y_3"},
    {5, "SNB_K_3"},
    {4, "SNB_X_3"},
    {3, "SNB_X_3"},
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

/** Pose table of the Pokey while its stack is 1 segment tall: animation names for each pose type. */
static PoseTableEntry pose_table_body1[] = {
    {1, "SNB_N_4"},
    {2, "SNB_Y_4"},
    {9, "SNB_Y_4"},
    {5, "SNB_K_4"},
    {4, "SNB_X_4"},
    {3, "SNB_X_4"},
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

/** Pose table of the loose segment (part 5) of the Pokey: animation names for each pose type. */
static PoseTableEntry pose_table_parts[] = {
    {BTL_POSE_NORMAL, "SNB_B_1"},
    {BTL_POSE_DAMAGE, "SNB_B_1"},
    {BTL_POSE_STAY_DEFAULT, "SNB_B_1"},
};

/**
 * Data table of the Pokey: event scripts and values the battle looks up by tag (damage reactions, dodge,
 * first strike and so on).
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
 * Parts of the Pokey: the four body segments (parts 1 to 4, tallest first)
 * and the loose segment (part 5) it throws or loses.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_sambo", "c_sanbo", 0.0f, 0.0f, 0.0f, 0.0f, 84.0f, 0.0f, 0.0f, 90.0f, 0.0f, 20, 90, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, COUNTER_ATTR_TOP_SPIKY | COUNTER_ATTR_FRONT_SPIKY, pose_table_body4},
    {2, "btl_un_sambo", "c_sanbo", 0.0f, 0.0f, 0.0f, 0.0f, 64.0f, 0.0f, 0.0f, 70.0f, 0.0f, 20, 70, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, COUNTER_ATTR_TOP_SPIKY | COUNTER_ATTR_FRONT_SPIKY, pose_table_body3},
    {3, "btl_un_sambo", "c_sanbo", 0.0f, 0.0f, 0.0f, 0.0f, 44.0f, 0.0f, 0.0f, 50.0f, 0.0f, 20, 50, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, COUNTER_ATTR_TOP_SPIKY | COUNTER_ATTR_FRONT_SPIKY, pose_table_body2},
    {4, "btl_un_sambo", "c_sanbo", 0.0f, 0.0f, 0.0f, 0.0f, 24.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, COUNTER_ATTR_TOP_SPIKY | COUNTER_ATTR_FRONT_SPIKY, pose_table_body1},
    {5, "btl_un_sambo", "c_sanbo", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table_parts},
};

/**
 * Init event of the Pokey: installs its wait, attack, damage and confusion events,
 * sets unit work 0 (its body length, in segments) to 4, applies the matching height (_body_param_set),
 * clears unit work 1 (how many Pokeys it has called) and sets its run and walk sounds.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_SAMBO_SEGMENTS, 4)
    CALL_CHILD(_body_param_set)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_SAMBO_FRIENDS_CALLED, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 5, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_MOVE1"), STRING("SFX_ENM_SAMBO_MOVE1"), 0, 6, 6)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_MOVE1"), STRING("SFX_ENM_SAMBO_MOVE1"), 0, 6, 6)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Reaction of a Pokey whose spines counter an attack: data table tags 37 and 39, which btldefaultevt_Damage
 * runs for the top-spike and front-spike counter hit events (damage codes 0x1F and 0x21):
 * it shows pose type 47 on the unit in LW(10), part LW(11),
 * and flashes a toge_flush spike effect above it for 60 frames.
 */
static EVT_BEGIN(dmg_avoid_counter_thorn_side_event)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 47)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, LW(10), LW(3))
    CALL(btlevtcmd_GetStatusMg, LW(10), LW(4))
    MULTIPLY_FLOAT(LW(3), LW(4))
    ADD(LW(1), LW(3))
    ADD(LW(1), 5)
    ADD(LW(2), 10)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

/**
 * Damage event of the Pokey: runs the default damage handling for the segment that is currently on top,
 * picked from the body length in unit work 0 (1 to 4 gives part 4 to 1).
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_SEGMENTS, LW(0))
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
 * Damage event of the Pokey that loses its top segment when a hit does damage:
 * plays the damage pose, takes one off the body length (unit work 0), re-applies the height and the status icon,
 * cut and kiss offsets for the shorter stack, and drops the old top as a loose head (part 5) that falls to the
 * floor and bounces.
 */
static EVT_BEGIN(damage_event_bodylost)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_SEGMENTS, LW(0))
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
        CALL(btlevtcmd_GetUnitWork, LW(10), UW_SAMBO_SEGMENTS, LW(0))
        SUBTRACT(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, LW(10), UW_SAMBO_SEGMENTS, LW(0))
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
 * Part of the Pokey losing a segment, run by its segment-losing damage events: plays pose type LW(14), lifts the
 * stack by 18 and lets it drop back over 11 frames with a small bounce, ending where it started.
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
 * Damage event of the Pokey for a hammer blow-away hit (data table tag 18,
 * damage patterns 14 and 16: Super and Ultra Hammer). With
 * only its head left (unit work 0 = 1) it takes the shot-away damage.
 * Otherwise it loses a segment: the loose segment
 * (part 5) is knocked through each ally after it in turn, hitting them with marioWeapon_KaitenHammerInvolved
 * (pattern 15) or marioWeapon_UltraHammerInvolved, then flies off the stage edge; with pattern 16 the
 * marioWeapon_UltraHammerFinish hit then lands on the Pokey itself.
 */
static EVT_BEGIN(damage_event_bodylost_blow)
    // With only its head left, the hammer blow just does its damage (or nothing, if it deals none).
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_SEGMENTS, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_GetDamage, LW(10), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL_CHILD(subsetevt_shot_damage)
        ELSE
            CALL_CHILD(subsetevt_nodamage_motion)
        END_IF
    ELSE
        // Otherwise it loses its top segment, and the loose segment starts to fall.
        SET_VALUE(LW(12), LW(11))
        CALL(btlevtcmd_GetUnitWork, LW(10), UW_SAMBO_SEGMENTS, LW(0))
        SUBTRACT(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, LW(10), UW_SAMBO_SEGMENTS, LW(0))
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
        // The loose segment is knocked along the Pokey's own side, hitting each ally in turn.
        CALL(btlevtcmd_CheckDamagePattern, LW(10), 15, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SET_VALUE(LW(13), PTR(&marioWeapon_KaitenHammerInvolved))
        ELSE
            SET_VALUE(LW(13), PTR(&marioWeapon_UltraHammerInvolved))
        END_IF
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
        CALL(btlevtcmd_CheckDamage, LW(10), LW(3), LW(4), LW(13), DAMAGE_FLAG_LAST_HIT, LW(5))
        GOTO(10)
        // The segment flies off the edge of the stage.
        LABEL(50)
        CALL(btlevtcmd_GetStageSize, LW(5), EVT_NULLPTR, EVT_NULLPTR)
        SET_VALUE(LW(0), 0)
        CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), LW(5))
        CALL(btlevtcmd_GetPos, LW(10), EVT_NULLPTR, LW(1), EVT_NULLPTR)
        CALL(btlevtcmd_JumpPartsSetting, LW(10), 5, 0, FLOAT(5.0f), FLOAT(0.009765625f))
        CALL(btlevtcmd_JumpPartsPosition, LW(10), 5, LW(0), LW(1), LW(2), 0, -1)
        CALL(btlevtcmd_OnPartsAttribute, LW(10), 5, PART_ATTR_HIDDEN)
        // An Ultra Hammer blow also lands its finishing hit on the Pokey itself.
        CALL(btlevtcmd_CheckDamagePattern, LW(10), 16, LW(5))
        IF_INT_NOT_EQUAL(LW(5), 0)
            CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), PTR(marioWeapon_UltraHammerFinish), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_AC_SUCCESS, LW(5))
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Data table tag 54, run by btldefaultevt_Damage on a hit with damage pattern 7 (Yoshi's Gulp).
 * With only its head left it plays
 * the hurt pose (39). Otherwise one segment is taken off the body length, the offsets are updated, the part is
 * hidden while the rest of the stack drops by one segment, and the loose segment (part 5) slides out along the
 * floor; when one segment remains it also sets swallow parameter 50 and swallow attribute 2.
 */
static EVT_BEGIN(damage_swallow_body)
    SET_VALUE(LW(14), 39)
    SET_VALUE(LW(15), -1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_SEGMENTS, LW(0))
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
        CALL(btlevtcmd_GetUnitWork, LW(10), UW_SAMBO_SEGMENTS, LW(0))
        SUBTRACT(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, LW(10), UW_SAMBO_SEGMENTS, LW(0))
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
 * Attack event of the Pokey: uses an enemy item if it has one.
 * A full-length Pokey (4 segments) that has called at most one friend has a 30 percent chance to call another
 * Pokey (call_friend_event) when there is a free spot to its side.
 * Otherwise, with two or more segments it does the head attack of its length (attack_head_2_event, about 30 in
 * 70) or else the spike attack, and a lone head does attack_head_1_event.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_SEGMENTS, LW(10))
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
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_FRIENDS_CALLED, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 1)
            CALL(evt_sub_random, 99, LW(0))
            IF_INT_LESS(LW(0), 30)
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
                CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_head_attack_4))
                CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_head_attack_4), LW(3), LW(4))
                CASE_EQUAL(3)
                CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
                CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_head_attack_3))
                CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_head_attack_3), LW(3), LW(4))
                CASE_EQUAL(2)
                CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
                CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_head_attack_2))
                CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_head_attack_2), LW(3), LW(4))
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
 * The Pokey's head attack for a stack of two to four segments:
 * it winds up by tilting back, leans over at the target
 * and brings the whole stack down on it (rotating z with the attack sounds), then straightens up and walks back.
 * The weapon used is weapon_sambo_head_attack_2 to 4 according to the body length (unit work 0).
 */
static EVT_BEGIN(attack_head_2_event)
    // Choose a target with the weapon that matches the stack height (2 to 4 segments).
    SET_VALUE(LW(6), LW(11))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_TINY, LW(5))
    SWITCH(LW(10))
        CASE_EQUAL(4)
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        // Pick a target for the attack; a confused unit that has none flusters.
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_head_attack_4))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_head_attack_4), LW(3), LW(4))
        CASE_EQUAL(3)
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_head_attack_3))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_head_attack_3), LW(3), LW(4))
        CASE_EQUAL(2)
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_head_attack_2))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_head_attack_2), LW(3), LW(4))
    END_SWITCH
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // Announce the attack; the camera swings to follow it.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    SWITCH(LW(10))
        CASE_EQUAL(4)
        CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_sambo_head_attack_4))
        CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_sambo_head_attack_4))
        CASE_EQUAL(3)
        CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_sambo_head_attack_3))
        CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_sambo_head_attack_3))
        CASE_EQUAL(2)
        CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_sambo_head_attack_2))
        CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_sambo_head_attack_2))
    END_SWITCH
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    // Walk up beside the target.
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
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), BTL_POSE_WALK)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(2.0f))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    // Wind-up: the stack tilts back, away from the target.
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
    CALL(evt_sub_intpl_init, 11, 0, LW(14), 40)
    LABEL(0)
    CALL(evt_sub_intpl_get_value)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    // The whole stack topples over at the target in a smashing swing.
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    SET_VALUE(LW(13), 40)
    SET_VALUE(LW(14), -90)
    IF_INT_EQUAL(LW(15), -1)
        SET_VALUE(LW(13), -40)
        SET_VALUE(LW(14), 90)
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_ATTACK4"), EVT_NULLPTR, 0, EVT_NULLPTR)
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
        // Find out whether the attack will connect or miss.
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_4), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_3), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(2)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_2), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // The attack misses or is dodged.
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
    // The attack connects.
    LABEL(91)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    SWITCH(LW(10))
        CASE_EQUAL(4)
        // Deal the damage, reduced by the action command defence.
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_sambo_head_attack_4))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_4), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_sambo_head_attack_3))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_3), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(2)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_sambo_head_attack_2))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_2), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_SWITCH
    // Straighten up again after the blow.
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
    // Return to its place.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), 41)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    // The attack is over; back to waiting.
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The attack of a Pokey that is down to its head:
 * it hops (sambo_rabbit_move, 35 units a hop) beside the target,
 * spins forward on a jump over it with the attack sound, then lands with a few shrinking bounces and hops home.
 * The weapon is weapon_sambo_head_attack_1.
 */
static EVT_BEGIN(attack_head_1_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // Pick a target for the attack; a confused unit that has none flusters.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_head_attack_1))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_head_attack_1), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_sambo_head_attack_1))
    // Announce the attack; the camera swings to follow it.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_sambo_head_attack_1))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    // Hop up beside the target.
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(2.0f))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5996094f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(5), LW(6), LW(7))
    CALL(btlevtcmd_TransStageFloorPosition, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(5), 50)
    SET_VALUE(LW(8), 35)
    CALL_CHILD(sambo_rabbit_move)
    WAIT_FRAMES(10)
    // Find out whether the attack will connect or miss.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_1), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.2998047f))
    // Spin forward in a jump that carries it over and past the target.
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
    // Land a little way beyond the target.
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 30)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(30)
    CALL(evt_btl_camera_set_mode, 0, 0)
    GOTO(98)
    LABEL(91)
    // Spin forward in a jump onto the target.
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
    // Land on the target with a crash and a camera shake.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_ATTACK6"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    WAIT_FRAMES(2)
    // Deal the damage, reduced by the action command defence.
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_sambo_head_attack_1))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_1), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.89941406f))
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    // Bounce on the spot with shrinking hops.
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
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
    // Return to its place.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 4, 41)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
    SET_VALUE(LW(8), 35)
    CALL_CHILD(sambo_rabbit_move)
    // The attack is over; back to waiting.
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Pokey's spike throw (it lobs a part of its body):
 * it chooses a target with weapon_sambo_spike_attack_2 to 4 according to its
 * body length, shrinks by one segment and throws that top segment (part 5, pose SNB_B_1) in a rising arc at the
 * target, the hit or the miss deciding where it lands.
 * The segment then drops to the floor, bounces three times and is lost.
 */
static EVT_BEGIN(attack_spike_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_SEGMENTS, LW(10))
    SWITCH(LW(10))
        CASE_EQUAL(4)
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        // Pick a target for the attack; a confused unit that has none flusters.
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_spike_attack_4))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_spike_attack_4), LW(3), LW(4))
        CASE_EQUAL(3)
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_spike_attack_3))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_spike_attack_3), LW(3), LW(4))
        CASE_EQUAL(2)
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_spike_attack_2))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_spike_attack_2), LW(3), LW(4))
    END_SWITCH
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // Announce the attack; the camera swings to follow it.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    SWITCH(LW(10))
        CASE_EQUAL(4)
        CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_sambo_spike_attack_4))
        CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_sambo_spike_attack_4))
        CASE_EQUAL(3)
        CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_sambo_spike_attack_3))
        CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_sambo_spike_attack_3))
        CASE_EQUAL(2)
        CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_sambo_spike_attack_2))
        CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_sambo_spike_attack_2))
    END_SWITCH
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // The Pokey pulls its top segment off the stack, so the stack is one segment shorter.
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_TINY, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetPartsScale, BTL_UNIT_SELF, 5, FLOAT(0.69921875f), FLOAT(0.69921875f), FLOAT(1.0f))
    ELSE
        CALL(btlevtcmd_SetPartsScale, BTL_UNIT_SELF, 5, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_SEGMENTS, LW(10))
    SUBTRACT(LW(10), 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_SAMBO_SEGMENTS, LW(10))
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
        // The loose segment is lifted above the stack, ready to be thrown.
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 5, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 5, FLOAT(0.5996094f))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("SNB_B_1"))
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2), 30, -1)
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_ATTACK3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    // The Pokey throws the segment in a rising arc toward the target.
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), 50)
    WAIT_FRAMES(24)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_ATTACK4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_ATTACK5"), EVT_NULLPTR, 0, LW(14))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), 51)
    WAIT_FRAMES(2)
    WAIT_FRAMES(5)
    SWITCH(LW(10))
        CASE_EQUAL(3)
        // Find out whether the attack will connect or miss.
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_spike_attack_4), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(2)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_spike_attack_3), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(1)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_spike_attack_2), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // The attack misses or is dodged.
    LABEL(90)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageSize, LW(0), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(9))
    MULTIPLY(LW(0), LW(9))
    SUBTRACT(LW(1), 5)
    // The segment sails past the target and drops to the floor.
    CALL(btlevtcmd_SetPartsMoveSpeed, BTL_UNIT_SELF, 5, FLOAT(10.0f))
    CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 5, FLOAT(0.099609375f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2), 0, -1)
    CALL(evt_snd_sfxoff, LW(14))
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 5, PART_ATTR_HIDDEN)
    GOTO(99)
    LABEL(91)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    // The segment comes down on the target.
    CALL(btlevtcmd_SetPartsMoveSpeed, BTL_UNIT_SELF, 5, FLOAT(10.0f))
    CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 5, FLOAT(0.099609375f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2), 0, -1)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    SWITCH(LW(10))
        CASE_EQUAL(3)
        SET_VALUE(LW(12), PTR(&weapon_sambo_spike_attack_4))
        CASE_EQUAL(2)
        SET_VALUE(LW(12), PTR(&weapon_sambo_spike_attack_3))
        CASE_EQUAL(1)
        SET_VALUE(LW(12), PTR(&weapon_sambo_spike_attack_2))
    END_SWITCH
    // Deal the damage, reduced by the action command defence.
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), BTL_POSE_STAY)
    IF_INT_EQUAL(LW(5), 21)
        CALL(evt_snd_sfxoff, LW(14))
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(11))
        CALL(btlevtcmd_GetHitPos, BTL_UNIT_SELF, LW(11), LW(0), LW(1), LW(2))
        // The segment bounces off the target and drops to the floor with three bounces, then is lost.
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
    // Wrap up the attack.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    // The attack is over; back to waiting.
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Pokey calls another Pokey: it sways back and forth with the SEND_GROUP sounds,
 * then spawns entry_sambo at the free spot found by attack_event (LW(6) to LW(8)) as a short Pokey (pose
 * SNB_D_1) that drops in through a smoke puff, and adds one to the new unit's count of called friends (unit work
 * 1).
 */
static EVT_BEGIN(call_friend_event)
    // The Pokey sways back and forth, calling to a friend.
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
    // The camera shakes as the new Pokey is summoned.
    WAIT_FRAMES(40)
    BEGIN_INLINE_EVENT
        CALL(evt_btl_camera_shake_h, 0, 2, 0, 10, 13)
    END_INLINE_EVENT
    // The new, short Pokey drops in through a smoke puff at the free spot.
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_sambo), 0)
    SET_VALUE(LW(0), LW(6))
    SET_VALUE(LW(1), LW(7))
    SET_VALUE(LW(2), LW(8))
    SUBTRACT(LW(1), 80)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
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
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_FRIENDS_CALLED, LW(4))
    ADD(LW(4), 1)
    // Count one more called friend on the new Pokey.
    CALL(btlevtcmd_SetUnitWork, LW(3), UW_SAMBO_FRIENDS_CALLED, LW(4))
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
 * Setup used to spawn a short Pokey (called by another Pokey): unit kind, alliance, position and turn phase.
 */
static BattleUnitSetup entry_sambo = {
    &unit_sambo, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Idle event: shows the pose table entry for the segment currently on top (unit work 0 of 1 to 4 gives part 4 to
 * 1).
 */
static EVT_BEGIN(wait_event)
    SET_VALUE(LW(10), -2)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_SEGMENTS, LW(0))
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
 * Helper of attack_head_1_event: hops the unit along x toward LW(5) in steps of at most LW(8) units
 * (JumpPosition with a jump height of 0, y = LW(6)) until it is within one step, then lands at LW(5), LW(6),
 * LW(7).
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

/**
 * Sets the unit's height and cut height from its body length in unit work 0:
 * 20 per segment (1 to 4 segments gives 20, 40, 60 and 80).
 */
static EVT_BEGIN(_body_param_set)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_SEGMENTS, LW(0))
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
