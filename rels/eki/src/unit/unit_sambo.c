// Pokey (sambo): enemy battle unit data and scripts, Riverside Station's copy (the Pokey Mummy is in unit_sambo_mummy.c).
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

static BattleUnitKind unit_sambo;
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

/** Unit data of the Pokey: 4 HP, level 11; the battle starts it from init_event. */
static BattleUnitKind unit_sambo = {
    39, // unitType
    "btl_un_sambo", // name
    4, // maxHp
    0, // maxFp
    1, // dangerHP
    1, // perilHP
    11, // level
    0, // bonusExp
    1, // bonusCoin
    70, // bonusCoinRate
    1, // baseCoin
    50, // runRate
    9999, // pbSoftCap
    26, // width
    80, // height
    {14, 80}, // hitOffset
    {0.0f, 40.0f, 0.0f}, // centerOffset
    {0}, // hpGaugeOffset
    {0}, // talkTogeBaseOffset
    {13.0f, 0.0f, -10.0f}, // heldItemBaseOffset
    {0}, // burnFlameOffset
    0.0f, 0.0f, // vivianOffsetX..vivianOffsetZ
    {13.0f, 0.0f, 0.0f}, // bintaHitOffset
    {10.0f, 52.0f, 0.0f}, // kissHitOffset
    {0.0f, 40.0f, 0.0f}, // cutBaseOffset
    26.0f, // cutWidth
    80.0f, // cutHeight
    0, 0, 0, // turnOrder..swallowChance
    2, // swallowAttributes
    100, // hammerKnockbackChance
    20, // itemStealParam
    {0}, // starPointDispOffset
    "SFX_ENM_SAMBO_DAMAGED1", // damageSfxName
    "SFX_BTL_DAMAGE_FIRE1", // fireDamageSfxName
    "SFX_BTL_DAMAGE_ICE1", // iceDamageSfxName
    "SFX_BTL_DAMAGE_BIRIBIRI1", // explosionDamageSfxName
    0, // attributeFlags
    &regist, // statusVulnerability
    5, // numParts
    parts, // parts
    init_event, // initEventCode
    (BattleDataEntry*)data_table, // dataTable
};

/** Defence of the Pokey: none against any element. */
static BattleUnitDefense defence = {0};

/** Elemental reactions of the Pokey: none, every element hurts it normally. */
static BattleUnitDefenseAttr defence_attr = {0};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Pokey (percent, 100 is normal) in the demo builds: resists most statuses
 * (50-90%).
 */
static StatusVulnerability regist = {90, 80, 80, 100, 90, 100, 100, 50, 100, 90, 100, 90, 100, 90, 90, 100, 90, 100, 90, 100, 100, 100};
#else
/**
 * Status vulnerability of the Pokey (percent, 100 is normal) in the retail builds: resists most statuses
 * (60-95%).
 */
static StatusVulnerability regist = {95, 80, 80, 100, 90, 100, 100, 60, 100, 90, 100, 90, 100, 95, 90, 100, 90, 100, 90, 100, 100, 100};
#endif

/** Weapon data for the Pokey's head slam when it has 4 segments: 2 damage, one target. */
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

/** Weapon data for the Pokey's head slam when it has 3 segments: 2 damage, one target. */
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

/**
 * Weapon data for the Pokey's head slam when it has 2 segments: 2 damage, a shell-toss-type hit, one target.
 */
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
 * Weapon data for the Pokey's lone-head hop attack, used when it has one segment left: 3 damage, a
 * shell-toss-type hit, one target.
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

/** Weapon data for the Pokey's segment throw when it has 4 segments: 3 damage, one target. */
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

/** Weapon data for the Pokey's segment throw when it has 3 segments: 3 damage, one target. */
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

/** Weapon data for the Pokey's segment throw when it has 2 segments: 3 damage, one target. */
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

/** Pose table of the Pokey while it stands with 4 segments. */
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

/** Pose table of the Pokey while it stands with 3 segments. */
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

/** Pose table of the Pokey while it stands with 2 segments. */
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

/** Pose table of the Pokey while it stands with 1 segment. */
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

/**
 * Pose table of the Pokey's hidden body parts and the thrown segment: they all just show the segment pose
 * (SNB_B_1).
 */
static PoseTableEntry pose_table_parts[] = {
    {BTL_POSE_NORMAL, "SNB_B_1"},
    {BTL_POSE_DAMAGE, "SNB_B_1"},
    {BTL_POSE_STAY_DEFAULT, "SNB_B_1"},
};

/**
 * Event table of the Pokey: the spike counters (tags 37 and 39, dmg_avoid_counter_thorn_side_event),
 * knockback hits (damage patterns 15 and 17) (damage_event_bodylost, tag 19), Super Hammer and Ultra Hammer
 * knockback (damage_event_bodylost_blow, tag 18), Koops' shell hits (damage_event_bodylost, tag 16), the
 * First Strike reaction (does nothing) and Yoshi's Gulp (damage_swallow_body, tag 54).
 */
static BattleDataEntry data_table[] = {
    {37, dmg_avoid_counter_thorn_side_event},
    {39, dmg_avoid_counter_thorn_side_event},
    {19, damage_event_bodylost},
    {18, damage_event_bodylost_blow},
    {16, damage_event_bodylost},
    {48, btldefaultevt_Dummy},
    {54, damage_swallow_body},
    {0},
};

/**
 * Parts of the Pokey: parts 1 to 4 are its body as it stands with 4, 3, 2 and 1 segments (only the current
 * one can be targeted) and part 5 is the segment it throws or loses.
 */
static BattleUnitKindPart parts[] = {
    {
        1, // partNum
        "btl_un_sambo", // partName
        "c_sanbo", // modelName
        {0}, // positionOffset
        {0.0f, 84.0f, 0.0f}, // hitBaseOffset
        {0.0f, 90.0f, 0.0f}, // hitCursorBaseOffset
        20, // shadowSize
        90, // hitHeight
        255, // baseAlpha
        &defence, // defense
        &defence_attr, // defenseAttr
        PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, // attributes
        COUNTER_ATTR_TOP_SPIKY | COUNTER_ATTR_FRONT_SPIKY, // counterAttributes
        pose_table_body4, // poseTable
    },
    {
        2, // partNum
        "btl_un_sambo", // partName
        "c_sanbo", // modelName
        {0}, // positionOffset
        {0.0f, 64.0f, 0.0f}, // hitBaseOffset
        {0.0f, 70.0f, 0.0f}, // hitCursorBaseOffset
        20, // shadowSize
        70, // hitHeight
        255, // baseAlpha
        &defence, // defense
        &defence_attr, // defenseAttr
        PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, // attributes
        COUNTER_ATTR_TOP_SPIKY | COUNTER_ATTR_FRONT_SPIKY, // counterAttributes
        pose_table_body3, // poseTable
    },
    {
        3, // partNum
        "btl_un_sambo", // partName
        "c_sanbo", // modelName
        {0}, // positionOffset
        {0.0f, 44.0f, 0.0f}, // hitBaseOffset
        {0.0f, 50.0f, 0.0f}, // hitCursorBaseOffset
        20, // shadowSize
        50, // hitHeight
        255, // baseAlpha
        &defence, // defense
        &defence_attr, // defenseAttr
        PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, // attributes
        COUNTER_ATTR_TOP_SPIKY | COUNTER_ATTR_FRONT_SPIKY, // counterAttributes
        pose_table_body2, // poseTable
    },
    {
        4, // partNum
        "btl_un_sambo", // partName
        "c_sanbo", // modelName
        {0}, // positionOffset
        {0.0f, 24.0f, 0.0f}, // hitBaseOffset
        {0.0f, 30.0f, 0.0f}, // hitCursorBaseOffset
        20, // shadowSize
        30, // hitHeight
        255, // baseAlpha
        &defence, // defense
        &defence_attr, // defenseAttr
        PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, // attributes
        COUNTER_ATTR_TOP_SPIKY | COUNTER_ATTR_FRONT_SPIKY, // counterAttributes
        pose_table_body1, // poseTable
    },
    {
        5, // partNum
        "btl_un_sambo", // partName
        "c_sanbo", // modelName
        {0}, // positionOffset
        {0}, // hitBaseOffset
        {0}, // hitCursorBaseOffset
        20, // shadowSize
        30, // hitHeight
        255, // baseAlpha
        &defence, // defense
        &defence_attr, // defenseAttr
        PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, // attributes
        0, // counterAttributes
        pose_table_parts, // poseTable
    },
};

/**
 * Init script of the Pokey.
 * Registers its wait, attack, damage and confusion scripts, starts it with 4 body segments (unit work 0),
 * sets its height from that count through _body_param_set,
 * clears unit work 1 (the number of friends it has called), and sets its run and walk sounds.
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
 * Data-table events 37 and 39, which the default damage event runs when an attacker was hurt by the Pokey's
 * top or front spikes (counter hits 0x1F and 0x21):
 * plays the side-hit pose 47 and flashes the toge_flush thorn effect at the height of the stack (unit height
 * scaled by its status scale), then waits 60 frames.
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
 * Damage reaction of the Pokey: picks the part index to damage from the number of body segments left (unit work
 * 0: 1 segment is part 4, 2 is 3, 3 is 2, otherwise 1) and runs the default damage script.
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
 * Damage reaction that knocks a segment off the Pokey's stack.
 * With one segment left (unit work 0 is 1) it only plays the damage pose;
 * otherwise it drops one segment (unit work 0 minus 1), recomputes the height with _body_param_set,
 * moves the status icon, cut and kiss offsets for the shorter stack and hands the hit to the next part down.
 * The lost segment (part 5) hops to the floor twice and blinks 40 times before disappearing.
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
 * Shared helper for the Pokey's segment loss: plays the hurt pose (LW(14)),
 * lifts the unit 18 units and lets it drop and wobble back to its height over about 20 frames in small SetPos
 * steps.
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
 * Data-table event 18, which the damage subset runs for a Super Hammer (damage pattern 14) or Ultra Hammer
 * (pattern 16) hit: like damage_event_bodylost, but the segment is knocked away.
 * With one segment left it plays the shot-damage subscript;
 * otherwise it removes a segment as before, then sends the lost segment (part 5) bouncing from enemy to enemy,
 * damaging each with marioWeapon_UltraHammerInvolved (marioWeapon_KaitenHammerInvolved, the Super Hammer's
 * knock-on weapon, when the damage pattern is 15), until it lands off the stage; after an Ultra Hammer hit
 * the Pokey also takes marioWeapon_UltraHammerFinish.
 */
static EVT_BEGIN(damage_event_bodylost_blow)
    // With only the head left (unit work 0 is 1) the hit just plays the shot reaction, or the no-damage
    // flinch.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_SEGMENTS, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_GetDamage, LW(10), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL_CHILD(subsetevt_shot_damage)
        ELSE
            CALL_CHILD(subsetevt_nodamage_motion)
        END_IF
    ELSE
        // Otherwise the Pokey loses its top segment: its segment count drops by one.
        SET_VALUE(LW(12), LW(11))
        CALL(btlevtcmd_GetUnitWork, LW(10), UW_SAMBO_SEGMENTS, LW(0))
        SUBTRACT(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, LW(10), UW_SAMBO_SEGMENTS, LW(0))
        CALL_CHILD(_body_param_set)
        // The shorter stack gets its own status icon, cut and kiss offsets, and the next segment down becomes
        // the top.
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
        // The remaining segments drop down a level.
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        BEGIN_SIBLING_EVENT
            WAIT_FRAMES(4)
            CALL_CHILD(subset_dmg_sambo_fall)
        END_SIBLING_EVENT
        // The knocked-off segment (part 5) starts flying from the Pokey, hit by the hammer.
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPartsPos, LW(10), 5, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_OffPartsAttribute, LW(10), 5, PART_ATTR_HIDDEN)
        // A Super Hammer hit (damage pattern 15) uses the Super Hammer knock-on weapon; an Ultra Hammer hit
        // uses the Ultra Hammer one.
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
        // The segment flies from unit to unit, damaging each one it lands on.
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
        // It finally sails off the stage and lands out of sight.
        LABEL(50)
        CALL(btlevtcmd_GetStageSize, LW(5), EVT_NULLPTR, EVT_NULLPTR)
        SET_VALUE(LW(0), 0)
        CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), LW(5))
        CALL(btlevtcmd_GetPos, LW(10), EVT_NULLPTR, LW(1), EVT_NULLPTR)
        CALL(btlevtcmd_JumpPartsSetting, LW(10), 5, 0, FLOAT(5.0f), FLOAT(0.009765625f))
        CALL(btlevtcmd_JumpPartsPosition, LW(10), 5, LW(0), LW(1), LW(2), 0, -1)
        CALL(btlevtcmd_OnPartsAttribute, LW(10), 5, PART_ATTR_HIDDEN)
        // After an Ultra Hammer hit the Pokey itself also takes the finishing hit.
        CALL(btlevtcmd_CheckDamagePattern, LW(10), 16, LW(5))
        IF_INT_NOT_EQUAL(LW(5), 0)
            CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), PTR(marioWeapon_UltraHammerFinish), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_AC_SUCCESS, LW(5))
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Damage reaction when the Pokey is swallowed (Yoshi's Gulp):
 * with one segment left it plays the hurt pose 39,
 * otherwise the segment handling of damage_event_bodylost applies (a segment is dropped,
 * the height and hit offsets shrink to the shorter stack,
 * the lost segment hops and blinks away) after a 3-frame wait.
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
 * Turn script of the Pokey. After an item-use check it works from the segment count (unit work 0).
 * With a full stack of 4 and at most one friend called so far,
 * it has a 30 percent chance to call a friend (call_friend_event) if there is room beside it.
 * With 2 or more segments it then rolls 0 to 69 and, on 30 or less,
 * throws its head segments (attack_head_2_event) if a target is available;
 * otherwise it uses the spike attack (attack_spike_event). A single segment always uses attack_head_1_event.
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
 * The Pokey's attack with its top segments.
 * It picks the weapon for the current segment count (weapon_sambo_head_attack_2 to _4),
 * samples a target and attacks it, with the avoid,
 * hit and guard results taken from the pre-damage check and the action command defence.
 */
static EVT_BEGIN(attack_head_2_event)
    SET_VALUE(LW(6), LW(11))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_TINY, LW(5))
    // The attack depends on how many segments the Pokey has (4, 3 or 2): pick the weapon and a target.
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
    // No valid target: a confused Pokey is flustered, otherwise the turn is skipped.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // The attack is declared and the guard window opens; the weapon cost is paid.
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
    // The camera follows the Pokey.
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    // It walks up to the target; the taller the stack, the farther back it stops.
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
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), BTL_POSE_STAY)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    // Wind-up: it leans back, away from the target.
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
    // It whips its stack forward, slamming its top segments down toward the target.
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
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_4), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_3), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(2)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_2), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_SWITCH
    // Hit check: a miss lets the target avoid, a hit goes on to the damage.
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
    // The stack swings back up toward upright.
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
    LABEL(91)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    // The damage is dealt with the action-command result.
    SWITCH(LW(10))
        CASE_EQUAL(4)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_sambo_head_attack_4))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_4), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_sambo_head_attack_3))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_3), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(2)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_sambo_head_attack_2))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_2), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_SWITCH
    // It flops over, then slowly pulls itself upright again.
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
    LABEL(98)
    // Retreat: it walks back to its home position.
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), 41)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The attack of a Pokey with a single segment left (weapon_sambo_head_attack_1):
 * it hops toward its target with sambo_rabbit_move, then hits it, with avoid,
 * guard and hit results from the pre-damage check and the action command defence, and hops home.
 */
static EVT_BEGIN(attack_head_1_event)
    // A Pokey reduced to a single segment attacks alone: it chooses a target.
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_sambo_head_attack_1))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_sambo_head_attack_1), LW(3), LW(4))
    // No valid target: a confused Pokey is flustered, otherwise the turn is skipped.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // The attack is declared and the guard window opens; the camera follows the Pokey.
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_sambo_head_attack_1))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_sambo_head_attack_1))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    // Wind-up: the head hops across the floor toward the target in short bounces.
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(2.0f))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5996094f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(5), LW(6), LW(7))
    CALL(btlevtcmd_TransStageFloorPosition, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(5), 50)
    SET_VALUE(LW(8), 35)
    CALL_CHILD(sambo_rabbit_move)
    WAIT_FRAMES(10)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_1), DAMAGE_FLAG_LAST_HIT, LW(5))
    // Hit check: a miss lets the target avoid, a hit goes on to the damage.
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
    // Miss: the head springs over the target, somersaulting, and lands behind it.
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
    LABEL(91)
    // Hit: the head leaps at the target and butts into it; the camera shakes and the damage is dealt.
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
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_sambo_head_attack_1))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_head_attack_1), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(evt_btl_camera_set_mode, 0, 0)
    // It lands and bounces back in four shrinking hops.
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.89941406f))
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
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
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    // Retreat: it hops back to its home position.
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 4, 41)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
    SET_VALUE(LW(8), 35)
    CALL_CHILD(sambo_rabbit_move)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Spike attack of the Pokey (weapon_sambo_spike_attack_2 to _4, by segment count).
 * The Pokey throws one of its segments: it loses a segment (unit work 0 drops by one, the body is resized by
 * _body_param_set), and the thrown segment (part 5, pose SNB_B_1) hops off its top and flies at the target,
 * which dodges, guards or takes the hit (pre-damage check and action-command defence). On a hit the segment
 * bounces back and rolls away; on a miss it flies on off the stage. It is hidden afterwards.
 */
static EVT_BEGIN(attack_spike_event)
    // The throw depends on how many segments the Pokey has left (unit work 0): pick the weapon and a target.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_SAMBO_SEGMENTS, LW(10))
    SWITCH(LW(10))
        CASE_EQUAL(4)
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
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
    // No valid target: a confused Pokey is flustered, otherwise the turn is skipped.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // The attack is declared and the guard window opens; the weapon cost is paid.
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
    // The thrown segment is drawn smaller when the Pokey is shrunk.
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_TINY, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetPartsScale, BTL_UNIT_SELF, 5, FLOAT(0.69921875f), FLOAT(0.69921875f), FLOAT(1.0f))
    ELSE
        CALL(btlevtcmd_SetPartsScale, BTL_UNIT_SELF, 5, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    END_IF
    // The Pokey gives up its top segment: the stack shrinks by one and its parts, icons and hit offsets are
    // resized.
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
    // The segment (part 5) hops off the top of the stack.
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
    // The Pokey winds up and hurls the segment at the target.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_ATTACK3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), 50)
    WAIT_FRAMES(24)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_ATTACK4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_SAMBO_ATTACK5"), EVT_NULLPTR, 0, LW(14))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), 51)
    WAIT_FRAMES(2)
    WAIT_FRAMES(5)
    SWITCH(LW(10))
        CASE_EQUAL(3)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_spike_attack_4), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(2)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_spike_attack_3), DAMAGE_FLAG_LAST_HIT, LW(5))
        CASE_EQUAL(1)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_sambo_spike_attack_2), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_SWITCH
    // Hit check: a miss lets the target avoid, a hit goes on to the damage.
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
    // Miss: the segment sails past the target and off the edge of the stage, then is hidden.
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
    LABEL(91)
    // Hit: the segment crashes into the target, the camera shakes and the damage is dealt.
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
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
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(6), BTL_POSE_STAY)
    // On a Superguard the segment ricochets back and hits the Pokey itself.
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
    // Otherwise the segment bounces off the target and rolls away across the floor, then is hidden.
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
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Pokey calls a friend: it sways its stack in several rotation steps with SFX_ENM_SAMBO_SEND_GROUP sounds,
 * shakes the camera, spawns a new Pokey beside it with SpawnUnit,
 * adds one to its own called-friends counter (unit work 1) and settles back upright.
 */
static EVT_BEGIN(call_friend_event)
    // The Pokey rocks its stack from side to side, with a calling sound for each swing.
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
    // A new Pokey pops up out of the ground beside the caller in a puff of smoke, and the caller counts one
    // more friend called (unit work 1).
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
    CALL(btlevtcmd_SetUnitWork, LW(3), UW_SAMBO_FRIENDS_CALLED, LW(4))
    // The caller straightens back up.
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

/** Setup for the new Pokey a Pokey calls in with its call-for-help move. */
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
 * Wait script of the Pokey: shows the idle pose that matches its remaining body segments (unit work 0 picks the
 * part index 1 to 4).
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
 * Script helper for the Pokey's hopping approach.
 * Hops toward the x position in LW(5) in steps of LW(8) units, playing SFX_ENM_SAMBO_MOVE2 on every hop,
 * then makes the final hop onto (LW(5), LW(6), LW(7)).
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

/** Sets the Pokey's height and cut height to 20, 40, 60 or 80 units for 1, 2, 3 or 4 body segments (unit work 0). */
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
