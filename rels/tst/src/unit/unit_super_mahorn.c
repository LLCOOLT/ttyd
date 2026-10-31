// Battle unit Elite Wizzerd (`super_mahorn`): tst.rel's copy of rels/jon/src/unit/unit_super_mahorn.c.
#include "version.h"
#include "eff/eff_mahorn2.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "manager/evtmgr_cmd.h"
#include "string.h"
#include "system.h"
#include "memory.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"

double __fabs(double x);
/** Absolute value of a double (__fabs), kept as an inline helper for eff_magic's speed calculation. */
static inline double mahorn_fabs(double x) {
    return __fabs(x);
}

static USER_FUNC(hand_ctrl);
static USER_FUNC(hand_init);
static USER_FUNC(mahorn_copy_status);
static USER_FUNC(mahorn_get_bunsin);
static USER_FUNC(mahorn_get_live_num);
static USER_FUNC(set_hand_dest);
static USER_FUNC(eff_magic_get_posX);
static USER_FUNC(eff_magic);
static USER_FUNC(mahorn_shuffle);

BattleUnitKind unit_super_mahorn;
static BattleUnitKind unit_super_mahorn_bunsin;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static StatusVulnerability regist_bunsin;
static BattleUnitKindPart parts[5];
static BattleWeapon weapon_mahorn_attack_magic;
static BattleWeapon weapon_mahorn_all_attack_magic;
static BattleWeapon weapon_mahorn_attack_punch;
static BattleWeapon weapon_mahorn_trans_magic;
static BattleWeapon weapon_mahorn_yokeyoke_magic;
static BattleWeapon weapon_mahorn_dekadeka_magic;
static BattleWeapon weapon_mahorn_katikati_magic;
static BattleWeapon weapon_mahorn_recover_magic;
static BattleUnitSetup entry_mahorn;
static PoseTableEntry pose_table[17];
static BattleDataEntry data_table[5];
static BattleDataEntry data_table_bunsin[3];
static EvtWord init_event[88];
static EvtWord hand_ctrl_event[23];
static EvtWord damage_event[66];
static EvtWord mahorn_subset_bunsin_all_kill[68];
static EvtWord mahorn_subset_dead_event[203];
static EvtWord mahorn_subset_blow_dead_event[78];
static EvtWord avoid_miss_event[16];
static EvtWord bunsin_kill_event[37];
static EvtWord attack_punch_event[429];
static EvtWord attack_enemy_common_event_sub1[90];
static EvtWord attack_enemy_common_event_sub2[231];
static EvtWord attack_enemy_common_event_sub_no_hit[65];
static EvtWord attack_enemy_common_event_sub_hit[50];
static EvtWord attack_magic_event[54];
static EvtWord all_attack_magic_event[41];
static EvtWord dekadeka_magic_event[49];
static EvtWord katikati_magic_event[49];
static EvtWord trans_magic_event[49];
static EvtWord yokeyoke_magic_event[49];
static EvtWord recover_magic_event[70];
static EvtWord bunsin_event[152];
#if VERSION <= VERSION_DEMO_US
static EvtWord spawn_event[72];
#else
static EvtWord spawn_event[76];
#endif
static EvtWord wait_event[386];

BattleUnitKind unit_super_mahorn = {
    128,
    "btl_un_super_mahorn",
    10,
    0,
    1,
    1,
    33,
    0,
#if VERSION <= VERSION_DEMO_US
    3,
#else
    2,
#endif
    70,
    2,
    50,
    9999,
    48,
    44,
    0,
    44,
    0.0f,
    22.0f,
    0.0f,
    0,
    -9,
    0.0f,
    0.0f,
    0.0f,
    24.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    24.0f,
    0.0f,
    0.0f,
    16.0f,
    28.6f,
    10.0f,
    0.0f,
    22.0f,
    0.0f,
    48.0f,
    44.0f,
    0,
    0,
    0,
    2,
    0,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_MAHO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4,
    &regist,
    5,
    parts,
    init_event,
    data_table,
};

static BattleUnitKind unit_super_mahorn_bunsin = {
    129, // unitType
    "btl_un_super_mahorn_bunsin", // name
    10, // maxHp
    0, // maxFp
    1, // dangerHP
    1, // perilHP
    1, // level
    0, 0, // bonusExp..bonusCoin
    70, // bonusCoinRate
    0, // baseCoin
    50, // runRate
    9999, // pbSoftCap
    48, // width
    44, // height
    {0, 44}, // hitOffset
    {0.0f, 22.0f, 0.0f}, // centerOffset
    {0, -9}, // hpGaugeOffset
    {0}, // talkTogeBaseOffset
    {24.0f, 0.0f, -10.0f}, // heldItemBaseOffset
    {0}, // burnFlameOffset
    0.0f, 0.0f, // vivianOffsetX..vivianOffsetZ
    {24.0f, 0.0f, 0.0f}, // bintaHitOffset
    {16.0f, 28.6f, 10.0f}, // kissHitOffset
    {0.0f, 22.0f, 0.0f}, // cutBaseOffset
    48.0f, // cutWidth
    44.0f, // cutHeight
    0, 0, 0, // turnOrder..swallowChance
    2, // swallowAttributes
    0, // hammerKnockbackChance
    20, // itemStealParam
    {0}, // starPointDispOffset
    "SFX_ENM_MAHO_DAMAGED1", // damageSfxName
    "SFX_BTL_DAMAGE_FIRE1", // fireDamageSfxName
    "SFX_BTL_DAMAGE_ICE1", // iceDamageSfxName
    "SFX_BTL_DAMAGE_BIRIBIRI1", // explosionDamageSfxName
    UNIT_ATTR_FLOATING | UNIT_ATTR_NO_DAMAGE_NUMBER, // attributeFlags
    &regist, // statusVulnerability
    5, // numParts
    parts, // parts
    init_event, // initEventCode
    (BattleDataEntry*)data_table_bunsin, // dataTable
};

static BattleUnitDefense defence = {{2, 2, 2, 2, 2}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {10, 50, 50, 100, 40, 100, 100, 40, 100, 40, 100, 40, 100, 40, 40, 30, 75, 100, 40, 100, 100, 90};
#else
static StatusVulnerability regist = {10, 50, 90, 100, 40, 100, 100, 50, 100, 85, 100, 85, 100, 90, 40, 30, 85, 100, 40, 100, 100, 90};
#endif

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist_bunsin = {0, 0, 0, 100, 0, 100, 100, 0, 100, 0, 100, 0, 100, 0, 0, 0, 0, 100, 0, 100, 100, 90};
#else
static StatusVulnerability regist_bunsin = {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif

static BattleUnitKindPart parts[] = {
    {1, "btl_un_super_mahorn", "c_maho_b", 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 0.0f, 0.0f, 40.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
    {2, "btl_un_super_mahorn", "c_maho_b", 0.0f, 0.0f, 0.0f, 5.0f, 30.0f, 0.0f, 0.0f, 35.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x2010009, 0, pose_table},
    {3, "btl_un_super_mahorn", "c_maho_b", 0.0f, 0.0f, 0.0f, 5.0f, 30.0f, 0.0f, 0.0f, 35.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x2010009, 0, pose_table},
    {4, "btl_un_super_mahorn", "c_maho_b", 0.0f, 0.0f, 0.0f, 5.0f, 30.0f, 0.0f, 0.0f, 35.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x2010009, 0, pose_table},
    {5, "btl_un_super_mahorn", "c_maho_b", 0.0f, 0.0f, 0.0f, 5.0f, 30.0f, 0.0f, 0.0f, 35.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x2010009, 0, pose_table},
};

static BattleWeapon weapon_mahorn_attack_magic = {
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
    {5, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
#if VERSION <= VERSION_DEMO_US
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_SHATTERS_FREEZE | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
#else
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_SHATTERS_FREEZE, // special
#endif
    COUNTER_RESIST_ALL, // counterResistFlags
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

static BattleWeapon weapon_mahorn_all_attack_magic = {
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
#if VERSION <= VERSION_DEMO_US
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#else
    {5, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#endif
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    4, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
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

static BattleWeapon weapon_mahorn_attack_punch = {
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
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_TOP_SPIKY, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT, // targetWeightFlags
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

static BattleWeapon weapon_mahorn_trans_magic = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ONLY_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    0, 0, 0, 0, 0, 0, 0, 0, // chargeStrength..paybackTime
    0, // holdFastTime
    100, // invisibleChance
    3, // invisibleTime
    0, 0, 0, 0, // hpRegenTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

static BattleWeapon weapon_mahorn_yokeyoke_magic = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ONLY_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, // poisonTime..electricTime
    100, // dodgyChance
    3, // dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    0, 0, 0, 0, 0, 0, 0, 0, // chargeStrength..paybackTime
    0, 0, 0, 0, 0, 0, 0, // holdFastTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

static BattleWeapon weapon_mahorn_dekadeka_magic = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ONLY_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, // burnChance..freezeTime
    100, // sizeChangeChance
    3, // sizeChangeTime
    2, // sizeChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeChance..allergicTime
    0, 0, 0, 0, 0, 0, 0, 0, // ohkoChance..galeForceChance
    0, 0, 0, 0, 0, 0, 0, 0, // paybackTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

static BattleWeapon weapon_mahorn_katikati_magic = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ONLY_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, // atkChangeTime..atkChangeStrength
    100, // defChangeChance
    3, // defChangeTime
    3, // defChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // allergicChance..slowTime
    0, 0, 0, 0, 0, 0, 0, 0, // frightChance..hpRegenStrength
    0, 0, // fpRegenTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

static BattleWeapon weapon_mahorn_recover_magic = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, 0, // acHelpMsg..special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_LOW_HP_RATIO | TARGET_WEIGHT_PREFER_LOW_HP | TARGET_WEIGHT_PREFER_IN_PERIL, // targetWeightFlags
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

static BattleUnitSetup entry_mahorn = {
    &unit_super_mahorn_bunsin, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * The Elite Wizzerd's turn (also used when confused). A first strike is a punch.
 * Copies (unit work 4 set) do nothing.
 * Otherwise it uses a held item if the AI wants to;
 * when it is the only enemy left alive it splits into copies (bunsin_event);
 * while it has copies they all cast the spell together (attack_magic_event),
 * or it does the flustered act if token 16 is set.
 * Otherwise it picks by weight: punch 60 / single spell 40 in the demos (30 / 60 in retail),
 * a thunder spell on everyone 10, and 8 each for Huge, Defense up, invisibility, Dodgy and healing itself.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(9), PTR(&weapon_mahorn_attack_punch))
        CALL_CHILD(attack_punch_event)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 4, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(mahorn_get_live_num, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL_CHILD(bunsin_event)
        RETURN
    ELSE
        CALL(mahorn_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL_CHILD(subsetevt_confuse_flustered)
                GOTO(99)
            END_IF
            SET_VALUE(LW(9), PTR(&weapon_mahorn_attack_magic))
            CALL_CHILD(attack_magic_event)
            GOTO(99)
        ELSE
            LABEL(10)
            SET_VALUE(LW(0), 0)
#if VERSION <= VERSION_DEMO_US
            ADD(LW(0), 60)
#else
            ADD(LW(0), 30)
#endif
#if VERSION <= VERSION_DEMO_US
            ADD(LW(0), 40)
#else
            ADD(LW(0), 60)
#endif
            ADD(LW(0), 10)
            ADD(LW(0), 8)
            ADD(LW(0), 8)
            ADD(LW(0), 8)
            ADD(LW(0), 8)
            ADD(LW(0), 8)
            SUBTRACT(LW(0), 1)
            CALL(evt_sub_random, LW(0), LW(1))
#if VERSION <= VERSION_DEMO_US
            SET_VALUE(LW(0), 60)
#else
            SET_VALUE(LW(0), 30)
#endif
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(&weapon_mahorn_attack_punch))
                CALL_CHILD(attack_punch_event)
                GOTO(99)
            END_IF
#if VERSION <= VERSION_DEMO_US
            ADD(LW(0), 40)
#else
            ADD(LW(0), 60)
#endif
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(&weapon_mahorn_attack_magic))
                CALL_CHILD(attack_magic_event)
                GOTO(99)
            END_IF
            ADD(LW(0), 10)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(&weapon_mahorn_all_attack_magic))
                CALL_CHILD(all_attack_magic_event)
                GOTO(99)
            END_IF
            ADD(LW(0), 8)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(&weapon_mahorn_dekadeka_magic))
                CALL_CHILD(dekadeka_magic_event)
                GOTO(99)
            END_IF
            ADD(LW(0), 8)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(&weapon_mahorn_katikati_magic))
                CALL_CHILD(katikati_magic_event)
                GOTO(99)
            END_IF
            ADD(LW(0), 8)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(&weapon_mahorn_trans_magic))
                CALL_CHILD(trans_magic_event)
                GOTO(99)
            END_IF
            ADD(LW(0), 8)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(&weapon_mahorn_yokeyoke_magic))
                CALL_CHILD(yokeyoke_magic_event)
                GOTO(99)
            END_IF
            ADD(LW(0), 8)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(&weapon_mahorn_recover_magic))
                CALL_CHILD(recover_magic_event)
                GOTO(99)
            END_IF
            GOTO(10)
        END_IF
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Attack event given to the copies by spawn_event: they take no action and just restart their idle loop. */
static EVT_BEGIN(attack_event_bunsin)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

static PoseTableEntry pose_table[] = {
    {1, "MAH_N_1"},
    {2, "MAH_Y_1"},
    {9, "MAH_Y_1"},
    {5, "MAH_K_1"},
    {4, "MAH_X_1"},
    {3, "MAH_X_1"},
    {28, "MAH_S_1"},
    {29, "MAH_Q_1"},
    {30, "MAH_Q_1"},
    {31, "MAH_A_1"},
    {39, "MAH_D_1"},
    {40, "MAH_W_1"},
    {42, "MAH_R_1"},
    {56, "MAH_X_1"},
    {57, "MAH_X_1"},
    {BTL_POSE_TALK, "MAH_T_1"},
    {BTL_POSE_STAY_DEFAULT, "MAH_S_1"},
};

static BattleDataEntry data_table[] = {
    {49, mahorn_subset_dead_event},
    {58, mahorn_subset_blow_dead_event},
    {46, avoid_miss_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static BattleDataEntry data_table_bunsin[] = {
    {46, avoid_miss_event},
    {48, btldefaultevt_Dummy},
    {0},
};

/**
 * Registers the Wizzerd's wait, attack and damage events (confusion reuses the attack event),
 * puts it 20 units up, sets up its four floating hands (parts 2-5) at their resting offsets
 * and starts hand_ctrl_event to move them. Clears unit work 4 (is a copy) and 6 (copy being removed).
 * Copies spawned by spawn_event run this too.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 20, LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(hand_init, BTL_UNIT_SELF)
    CALL(set_hand_dest, BTL_UNIT_SELF, 2, FLOAT(-25.0f), FLOAT(30.0f), FLOAT(-10.0f))
    CALL(set_hand_dest, BTL_UNIT_SELF, 3, FLOAT(25.0f), FLOAT(30.0f), FLOAT(10.0f))
    CALL(set_hand_dest, BTL_UNIT_SELF, 4, FLOAT(-25.0f), FLOAT(10.0f), FLOAT(-10.0f))
    CALL(set_hand_dest, BTL_UNIT_SELF, 5, FLOAT(25.0f), FLOAT(10.0f), FLOAT(10.0f))
    SPAWN_EVENT(hand_ctrl_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 6, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Fades the unit in LW(0) out over 30 frames (all five parts), then makes it shadowless and fully transparent.
 * LW(0) = -1 does nothing.
 */
static EVT_BEGIN(alpha_down_event)
    IF_INT_EQUAL(LW(0), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_SetAlpha, LW(0), 1, 254)
    CALL(btlevtcmd_AnimeFlagOnOff, LW(0), 1, 1, 1)
    WAIT_FRAMES(1)
    CALL(evt_sub_intpl_init, 0, 255, 0, 30)
    LOOP(30)
        CALL(evt_sub_intpl_get_value_para, LW(1), LW(2))
        CALL(btlevtcmd_SetAlpha, LW(0), 1, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 2, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 3, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 4, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 5, LW(1))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_OnPartsAttribute, LW(0), 1, 33554432)
    CALL(btlevtcmd_OnPartsAttribute, LW(0), 2, 33554432)
    CALL(btlevtcmd_OnPartsAttribute, LW(0), 3, 33554432)
    CALL(btlevtcmd_OnPartsAttribute, LW(0), 4, 33554432)
    CALL(btlevtcmd_OnPartsAttribute, LW(0), 5, 33554432)
    CALL(btlevtcmd_SetAlpha, LW(0), 1, 0)
    CALL(btlevtcmd_AnimeFlagOnOff, LW(0), 1, 1, 1)
    WAIT_FRAMES(1)
    RETURN
EVT_END()

/**
 * Opposite of alpha_down_event: gives the unit in LW(0) its shadows back
 * and fades all five parts in over 30 frames. LW(0) = -1 does nothing.
 */
static EVT_BEGIN(alpha_up_event)
    IF_INT_EQUAL(LW(0), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_OffPartsAttribute, LW(0), 1, 33554432)
    CALL(btlevtcmd_OffPartsAttribute, LW(0), 2, 33554432)
    CALL(btlevtcmd_OffPartsAttribute, LW(0), 3, 33554432)
    CALL(btlevtcmd_OffPartsAttribute, LW(0), 4, 33554432)
    CALL(btlevtcmd_OffPartsAttribute, LW(0), 5, 33554432)
    CALL(btlevtcmd_SetAlpha, LW(0), 1, 0)
    CALL(btlevtcmd_AnimeFlagOnOff, LW(0), 1, 1, 1)
    WAIT_FRAMES(1)
    CALL(evt_sub_intpl_init, 0, 0, 254, 30)
    LOOP(30)
        CALL(evt_sub_intpl_get_value_para, LW(1), LW(2))
        CALL(btlevtcmd_SetAlpha, LW(0), 1, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 2, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 3, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 4, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 5, LW(1))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetAlpha, LW(0), 1, 255)
    CALL(btlevtcmd_SetAlpha, LW(0), 2, 255)
    CALL(btlevtcmd_SetAlpha, LW(0), 3, 255)
    CALL(btlevtcmd_SetAlpha, LW(0), 4, 255)
    CALL(btlevtcmd_SetAlpha, LW(0), 5, 255)
    CALL(btlevtcmd_AnimeFlagOnOff, LW(0), 1, 1, 1)
    WAIT_FRAMES(1)
    RETURN
EVT_END()

/**
 * Runs for the Wizzerd's whole life: calls hand_ctrl every frame to ease the hands toward their set offsets,
 * and stops once the unit no longer exists.
 */
static EVT_BEGIN(hand_ctrl_event)
    LABEL(0)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        GOTO(99)
    END_IF
    CALL(hand_ctrl, BTL_UNIT_SELF)
    GOTO(0)
    LABEL(99)
    RETURN
EVT_END()

/**
 * Hit reaction. A copy that is hit just fades away (bunsin_kill_event).
 * The real Wizzerd runs btldefaultevt_Damage, and if it had copies
 * when it was hit (noted in unit work 5) all of them then vanish (mahorn_subset_bunsin_all_kill),
 * so hitting the real one breaks the illusion.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 4, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(mahorn_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 1)
        END_IF
    ELSE
        SET_VALUE(LW(0), -2)
        CALL_CHILD(bunsin_kill_event)
        RETURN
    END_IF
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL_CHILD(mahorn_subset_bunsin_all_kill)
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * On the real Wizzerd, if it has copies: waits for the attack to end,
 * starts bunsin_kill_event on each copy and waits until all of them are gone.
 */
static EVT_BEGIN(mahorn_subset_bunsin_all_kill)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 4, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(mahorn_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_WaitAttackEnd)
            CALL(mahorn_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
            SET_VALUE(LW(0), LW(1))
            SPAWN_EVENT(bunsin_kill_event)
            SET_VALUE(LW(0), LW(2))
            SPAWN_EVENT(bunsin_kill_event)
            SET_VALUE(LW(0), LW(3))
            SPAWN_EVENT(bunsin_kill_event)
            SET_VALUE(LW(0), LW(4))
            SPAWN_EVENT(bunsin_kill_event)
            LOOP(0)
                CALL(mahorn_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
                IF_INT_EQUAL(LW(0), 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Data-table event 49, the Wizzerd's death: runs data event 50 if there is one, spins with the death sounds,
 * puffs into smoke and pays out its coins and Star Points, tilts over,
 * drops its held item and clears its status, hides,
 * removes all its copies and is removed from battle (KillUnit mode 0 when the hit had damage code 0x400,
 * else mode 2).
 */
static EVT_BEGIN(mahorn_subset_dead_event)
    CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(0), 50)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_RunDataEventChild, LW(10), 50)
    END_IF
    SET_VALUE(LW(0), 48)
    CALL(btlevtcmd_OnUnitFlag, LW(10), 134217728)
    CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_BTL_ENEMY_DIE1_1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    LABEL(10)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_AddRotate, LW(10), 0, -15, 0)
    SUBTRACT(LW(0), 1)
    IF_INT_GREATER(LW(0), 0)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_SetRotate, LW(10), 0, 0, 0)
    CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_BTL_ENEMY_DIE1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    ADD(LW(2), 10)
    CALL(evt_eff, 0, STRING("kemuri_test"), 4, LW(0), LW(1), LW(2), FLOAT(0.7998047f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_GetCoin, LW(10), LW(0))
    CALL(btlevtcmd_StoreCoin, LW(0))
    CALL(btlevtcmd_GetExp, LW(10), LW(0))
    CALL(btlevtcmd_StoreExp, LW(0))
    CALL(btlevtcmd_GetPos, LW(10), LW(3), LW(1), LW(2))
    ADD(LW(2), 10)
    ADD(LW(1), 30)
    CALL(_add_star_point_disp_offset, LW(10), LW(3), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("star_point"), 0, LW(3), LW(1), LW(2), LW(0), 0, 0, 0, 0, 0, 0, 0)
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        LOOP(LW(0))
        END_LOOP
    END_IF
    CALL(btlevtcmd_SetRotateOffset, LW(10), 0, 0, 0)
    SET_VALUE(LW(0), 30)
    LABEL(20)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_AddRotate, LW(10), 3, 0, 0)
    SUBTRACT(LW(0), 1)
    IF_INT_GREATER(LW(0), 0)
        GOTO(20)
    END_IF
    CALL(btlevtcmd_GetBackItem, LW(10))
    CALL(btlevtcmd_ClearAllStatus, LW(10))
    CALL(btlevtcmd_OnAttribute, LW(10), 16777216)
    CALL(btlevtcmd_OnAttribute, LW(10), 536870912)
    CALL_CHILD(mahorn_subset_bunsin_all_kill)
    CALL(btlevtcmd_CheckDamageCode, LW(10), 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_KillUnit, LW(10), 0)
    ELSE
        CALL(btlevtcmd_KillUnit, LW(10), 2)
    END_IF
    RETURN
EVT_END()

/**
 * Data-table event 58 (run for damage code 29; Guess: blown away by Flurrie's Gale Force):
 * spins in the hurt pose while flying up and off stage, pays out its coins and Star Points,
 * removes its copies and is removed from battle.
 */
static EVT_BEGIN(mahorn_subset_blow_dead_event)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_CLAUD_BREATH3"), 0)
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(0), 39)
    BEGIN_SIBLING_EVENT
        LABEL(0)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 20, 0)
        WAIT_FRAMES(1)
        GOTO(0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(2.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageSize, LW(0), EVT_NULLPTR, EVT_NULLPTR)
    ADD(LW(1), 40)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -10, 2, 0, -1)
    CALL(btlevtcmd_GetCoin, LW(10), LW(0))
    CALL(btlevtcmd_StoreCoin, LW(0))
    CALL(btlevtcmd_GetExp, LW(10), LW(0))
    CALL(btlevtcmd_StoreExp, LW(0))
    CALL_CHILD(mahorn_subset_bunsin_all_kill)
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

/**
 * Data-table event 46 (run for damage code 40, an attack on an evasive part, which copies have):
 * if this unit is a copy, it fades away.
 */
static EVT_BEGIN(avoid_miss_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 4, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(0), -2)
        CALL_CHILD(bunsin_kill_event)
    END_IF
    RETURN
EVT_END()

/**
 * Removes the copy in LW(0): fades it out (only once, guarded by its unit work 6),
 * waits for the current attack to end and kills the unit. Does nothing if the unit is already gone.
 */
static EVT_BEGIN(bunsin_kill_event)
    CALL(btlevtcmd_GetUnitId, LW(0), LW(0))
    IF_INT_EQUAL(LW(0), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, LW(0), 6, LW(1))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_SetUnitWork, LW(0), 6, 1)
    CALL_CHILD(alpha_down_event)
    LABEL(10)
    CALL(btlevtcmd_WaitAttackEnd)
    CALL(btlevtcmd_KillUnit, LW(0), 0)
    RETURN
EVT_END()

/**
 * Punch with the attack weapon in LW(9) (5 damage):
 * floats up to the target, pummels it with blurred hands flailing for about 50 frames,
 * then deals the damage on a hit (the target may dodge) and floats home.
 */
static EVT_BEGIN(attack_punch_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(set_hand_dest, BTL_UNIT_SELF, 2, FLOAT(-16.0f), FLOAT(29.0f), FLOAT(-5.0f))
    CALL(set_hand_dest, BTL_UNIT_SELF, 3, FLOAT(16.0f), FLOAT(29.0f), FLOAT(5.0f))
    CALL(set_hand_dest, BTL_UNIT_SELF, 4, FLOAT(-16.0f), FLOAT(11.0f), FLOAT(-5.0f))
    CALL(set_hand_dest, BTL_UNIT_SELF, 5, FLOAT(16.0f), FLOAT(11.0f), FLOAT(5.0f))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    IF_INT_EQUAL(LW(15), -1)
        ADD(LW(0), 35)
    ELSE
        SUBTRACT(LW(0), 35)
    END_IF
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, 4, FLOAT(0.0009765625f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 20, LW(2), 0, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MAH_S_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("MAH_Z_2"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("MAH_Z_2"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("MAH_Z_2"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("MAH_Z_2"))
    SET_VALUE(LW(10), 2)
    LOOP(4)
        CALL(btlevtcmd_SetPartsBlur, BTL_UNIT_SELF, LW(10), 255, 255, 255, 255, 255, 255, 255, 100, 0)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(10), 67108864)
        ADD(LW(10), 1)
    END_LOOP
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    LOOP(25)
        SET_VALUE(LW(10), 2)
        LOOP(4)
            CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, LW(10), LW(0), LW(1), LW(2))
            IF_INT_EQUAL(LW(15), -1)
                CALL(evt_sub_random, 120, LW(11))
                ADD(LW(11), -90)
            ELSE
                CALL(evt_sub_random, 120, LW(11))
                MULTIPLY(LW(11), -1)
                ADD(LW(11), 90)
            END_IF
            CALL(evt_sub_random, 60, LW(12))
            ADD(LW(12), -20)
            CALL(set_hand_dest, BTL_UNIT_SELF, LW(10), LW(11), LW(12), LW(2))
            ADD(LW(10), 1)
        END_LOOP
        WAIT_FRAMES(2)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MAH_S_1"))
    CALL(set_hand_dest, BTL_UNIT_SELF, 2, FLOAT(-16.0f), FLOAT(29.0f), FLOAT(-5.0f))
    CALL(set_hand_dest, BTL_UNIT_SELF, 3, FLOAT(16.0f), FLOAT(29.0f), FLOAT(5.0f))
    CALL(set_hand_dest, BTL_UNIT_SELF, 4, FLOAT(-16.0f), FLOAT(11.0f), FLOAT(-5.0f))
    CALL(set_hand_dest, BTL_UNIT_SELF, 5, FLOAT(16.0f), FLOAT(11.0f), FLOAT(5.0f))
    SET_VALUE(LW(10), 2)
    LOOP(4)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(10), 67108864)
        ADD(LW(10), 1)
    END_LOOP
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 0, LW(5))
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
        LABEL(90)
        WAIT_FRAMES(30)
        GOTO(98)
        LABEL(91)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
        WAIT_FRAMES(30)
        GOTO(98)
        LABEL(98)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_ATTACK1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, 6, FLOAT(0.0009765625f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
        WAIT_FRAMES(45)
        LABEL(99)
        CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
        RETURN
EVT_END()

/**
 * Makes the target in LW(3) play its dodge reaction for the precheck result in LW(5) (3, 6 and 2 map to avoid
 * poses 38, 39 and 40); other results do nothing.
 */
static EVT_BEGIN(start_avoid)
    IF_INT_EQUAL(LW(5), 3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
    END_IF
    IF_INT_EQUAL(LW(5), 6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
    END_IF
    IF_INT_EQUAL(LW(5), 2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
    END_IF
    RETURN
EVT_END()

/**
 * Single-target spell with the weapon in LW(9):
 * the Wizzerd and all its copies charge up (sub1) and each fires an orb (sub_hit/sub_no_hit).
 * On a hit the real one deals the damage; on a miss the orbs fly past and the target dodges as they reach it.
 * The copies then go back to idling.
 */
static EVT_BEGIN(attack_enemy_common_event)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(mahorn_get_bunsin, LW(11), LW(12), LW(13), LW(14), LW(0))
    SET_VALUE(LW(15), LW(11))
    SPAWN_EVENT(attack_enemy_common_event_sub1)
    SET_VALUE(LW(15), LW(12))
    SPAWN_EVENT(attack_enemy_common_event_sub1)
    SET_VALUE(LW(15), LW(13))
    SPAWN_EVENT(attack_enemy_common_event_sub1)
    SET_VALUE(LW(15), LW(14))
    SPAWN_EVENT(attack_enemy_common_event_sub1)
    SET_VALUE(LW(15), -2)
    CALL_CHILD(attack_enemy_common_event_sub1)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_MAGIC2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        WAIT_FRAMES(25)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_MAGIC2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 0, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        GOTO(90)
        CASE_END
        CASE_EQUAL(6)
        GOTO(90)
        CASE_EQUAL(2)
        GOTO(90)
        CASE_EQUAL(1)
        GOTO(91)
        CASE_END
        CASE_DEFAULT
        GOTO(98)
        CASE_END
        LABEL(90)
        BEGIN_SIBLING_EVENT
            WAIT_FRAMES(60)
            LOOP(0)
                CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(0))
                IF_INT_EQUAL(LW(0), -1)
                    CALL(eff_magic_get_posX, BTL_UNIT_SELF, LW(0))
                    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
                    IF_INT_LESS_OR_EQUAL(LW(0), LW(6))
                        CALL_CHILD(start_avoid)
                        BREAK_LOOP
                    END_IF
                ELSE
                    CALL(eff_magic_get_posX, BTL_UNIT_SELF, LW(0))
                    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
                    IF_INT_GREATER_OR_EQUAL(LW(0), LW(6))
                        CALL_CHILD(start_avoid)
                        BREAK_LOOP
                    END_IF
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        CALL(mahorn_get_bunsin, LW(11), LW(12), LW(13), LW(14), LW(0))
        SET_VALUE(LW(15), LW(11))
        SPAWN_EVENT(attack_enemy_common_event_sub_no_hit)
        SET_VALUE(LW(15), LW(12))
        SPAWN_EVENT(attack_enemy_common_event_sub_no_hit)
        SET_VALUE(LW(15), LW(13))
        SPAWN_EVENT(attack_enemy_common_event_sub_no_hit)
        SET_VALUE(LW(15), LW(14))
        SPAWN_EVENT(attack_enemy_common_event_sub_no_hit)
        SET_VALUE(LW(15), -2)
        CALL_CHILD(attack_enemy_common_event_sub_no_hit)
        GOTO(98)
        LABEL(91)
        CALL(mahorn_get_bunsin, LW(11), LW(12), LW(13), LW(14), LW(0))
        SET_VALUE(LW(15), LW(11))
        SPAWN_EVENT(attack_enemy_common_event_sub_hit)
        SET_VALUE(LW(15), LW(12))
        SPAWN_EVENT(attack_enemy_common_event_sub_hit)
        SET_VALUE(LW(15), LW(13))
        SPAWN_EVENT(attack_enemy_common_event_sub_hit)
        SET_VALUE(LW(15), LW(14))
        SPAWN_EVENT(attack_enemy_common_event_sub_hit)
        SET_VALUE(LW(15), -2)
        CALL_CHILD(attack_enemy_common_event_sub_hit)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
        GOTO(98)
        LABEL(98)
        CALL(mahorn_get_bunsin, LW(11), LW(12), LW(13), LW(14), LW(0))
        IF_INT_NOT_EQUAL(LW(11), -1)
            CALL(btlevtcmd_StartWaitEvent, LW(11))
        END_IF
        IF_INT_NOT_EQUAL(LW(12), -1)
            CALL(btlevtcmd_StartWaitEvent, LW(12))
        END_IF
        IF_INT_NOT_EQUAL(LW(13), -1)
            CALL(btlevtcmd_StartWaitEvent, LW(13))
        END_IF
        IF_INT_NOT_EQUAL(LW(14), -1)
            CALL(btlevtcmd_StartWaitEvent, LW(14))
        END_IF
        WAIT_FRAMES(30)
        RETURN
EVT_END()

/**
 * Spell on every target with the weapon in LW(9) (element 4, 3 damage in the demos, 5 in retail):
 * charges up, waves its hands, then strikes each target with thunder_n64 in turn;
 * the action command result is only taken for the first hit.
 */
static EVT_BEGIN(attack_enemy_all_common_event)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    SET_VALUE(LW(15), -2)
    CALL_CHILD(attack_enemy_common_event_sub1)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_MAGIC2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        WAIT_FRAMES(25)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_MAGIC2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    SET_VALUE(LW(15), -2)
    CALL_CHILD(attack_enemy_common_event_sub2)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    SET_VALUE(LW(6), 0)
    LABEL(10)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 0, LW(5))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(evt_eff64, STRING(""), STRING("thunder_n64"), 4, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
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
        LABEL(90)
        GOTO(97)
        LABEL(91)
        IF_INT_EQUAL(LW(6), 0)
            CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
            SET_VALUE(LW(6), 1)
        END_IF
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
        GOTO(97)
        LABEL(97)
        CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
        IF_INT_EQUAL(LW(3), -1)
            GOTO(98)
        END_IF
        GOTO(10)
        LABEL(98)
        WAIT_FRAMES(30)
        RETURN
EVT_END()

/**
 * Charge-up for the unit in LW(15) (-1 does nothing):
 * stops its idle loop, shows akari_charge_n64 above it,
 * takes the casting pose with its hands drawn in and waits 50 frames.
 */
static EVT_BEGIN(attack_enemy_common_event_sub1)
    IF_INT_EQUAL(LW(15), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_StopWaitEvent, LW(15))
    CALL(btlevtcmd_GetPos, LW(15), LW(0), LW(1), LW(2))
    ADD(LW(1), 40)
    CALL(evt_eff64, STRING(""), STRING("akari_charge_n64"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 70, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, LW(15), 1, STRING("MAH_A_4"))
    CALL(btlevtcmd_AnimeChangePose, LW(15), 2, STRING("MAH_S_5A"))
    CALL(btlevtcmd_AnimeChangePose, LW(15), 3, STRING("MAH_S_5A"))
    CALL(btlevtcmd_AnimeChangePose, LW(15), 4, STRING("MAH_S_5A"))
    CALL(btlevtcmd_AnimeChangePose, LW(15), 5, STRING("MAH_S_5A"))
    CALL(set_hand_dest, LW(15), 2, FLOAT(-16.0f), FLOAT(29.0f), FLOAT(-5.0f))
    CALL(set_hand_dest, LW(15), 3, FLOAT(16.0f), FLOAT(29.0f), FLOAT(5.0f))
    CALL(set_hand_dest, LW(15), 4, FLOAT(-16.0f), FLOAT(11.0f), FLOAT(-5.0f))
    CALL(set_hand_dest, LW(15), 5, FLOAT(16.0f), FLOAT(11.0f), FLOAT(5.0f))
    WAIT_FRAMES(50)
    RETURN
EVT_END()

/**
 * Casting gesture for the unit in LW(15) (-1 does nothing):
 * stops its idle loop and swings each of its four hands twice, staggered, with the MAH_S_2A/2B hand poses,
 * then waits 55 frames.
 */
static EVT_BEGIN(attack_enemy_common_event_sub2)
    IF_INT_EQUAL(LW(15), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_StopWaitEvent, LW(15))
    CALL(btlevtcmd_AnimeChangePose, LW(15), 1, STRING("MAH_A_1"))
    BEGIN_INLINE_EVENT
        LOOP(2)
            SET_FLOAT_VALUE(LW(0), FLOAT(-16.0f))
            SET_FLOAT_VALUE(LW(1), FLOAT(20.0f))
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(2))
            MULTIPLY_FLOAT(LW(1), LW(2))
            CALL(btlevtcmd_AnimeChangePose, LW(15), 2, STRING("MAH_S_2B"))
            ADD(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 2, LW(0), FLOAT(29.0f), FLOAT(-5.0f))
            WAIT_FRAMES(20)
            CALL(btlevtcmd_AnimeChangePose, LW(15), 2, STRING("MAH_S_2A"))
            SUBTRACT(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 2, LW(0), FLOAT(29.0f), FLOAT(-5.0f))
            WAIT_FRAMES(20)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_FRAMES(7)
        LOOP(2)
            SET_FLOAT_VALUE(LW(0), FLOAT(16.0f))
            SET_FLOAT_VALUE(LW(1), FLOAT(20.0f))
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(2))
            MULTIPLY_FLOAT(LW(1), LW(2))
            CALL(btlevtcmd_AnimeChangePose, LW(15), 5, STRING("MAH_S_2B"))
            ADD(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 5, LW(0), FLOAT(11.0f), FLOAT(5.0f))
            WAIT_FRAMES(20)
            CALL(btlevtcmd_AnimeChangePose, LW(15), 5, STRING("MAH_S_2A"))
            SUBTRACT(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 5, LW(0), FLOAT(11.0f), FLOAT(5.0f))
            WAIT_FRAMES(20)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_FRAMES(10)
        LOOP(2)
            SET_FLOAT_VALUE(LW(0), FLOAT(-16.0f))
            SET_FLOAT_VALUE(LW(1), FLOAT(20.0f))
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(2))
            MULTIPLY_FLOAT(LW(1), LW(2))
            CALL(btlevtcmd_AnimeChangePose, LW(15), 4, STRING("MAH_S_2B"))
            ADD(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 4, LW(0), FLOAT(11.0f), FLOAT(-5.0f))
            WAIT_FRAMES(20)
            CALL(btlevtcmd_AnimeChangePose, LW(15), 4, STRING("MAH_S_2A"))
            SUBTRACT(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 4, LW(0), FLOAT(11.0f), FLOAT(-5.0f))
            WAIT_FRAMES(20)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_FRAMES(15)
        LOOP(2)
            SET_FLOAT_VALUE(LW(0), FLOAT(16.0f))
            SET_FLOAT_VALUE(LW(1), FLOAT(20.0f))
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(2))
            MULTIPLY_FLOAT(LW(1), LW(2))
            CALL(btlevtcmd_AnimeChangePose, LW(15), 3, STRING("MAH_S_2B"))
            ADD(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 3, LW(0), FLOAT(29.0f), FLOAT(5.0f))
            WAIT_FRAMES(20)
            CALL(btlevtcmd_AnimeChangePose, LW(15), 3, STRING("MAH_S_2A"))
            SUBTRACT(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 3, LW(0), FLOAT(29.0f), FLOAT(5.0f))
            WAIT_FRAMES(20)
        END_LOOP
    END_INLINE_EVENT
    WAIT_FRAMES(55)
    RETURN
EVT_END()

/**
 * Missed spell for the unit in LW(15) (-1 does nothing):
 * fires an eff_magic orb from it to the stage edge behind the target over 40 frames
 * while doing the casting gesture, with the magic sounds.
 */
static EVT_BEGIN(attack_enemy_common_event_sub_no_hit)
    IF_INT_EQUAL(LW(15), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetPos, LW(15), LW(0), LW(1), LW(2))
    ADD(LW(1), 10)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
    CALL(btlevtcmd_GetStageSize, LW(10), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetFaceDirection, LW(15), LW(13))
    MULTIPLY(LW(10), LW(13))
    SUBTRACT(LW(11), 5)
    CALL(eff_magic, LW(15), LW(10), LW(11), LW(12), 40)
    CALL_CHILD(attack_enemy_common_event_sub2)
    WAIT_FRAMES(5)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_MAGIC1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_MAGIC3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(40)
    RETURN
EVT_END()

/**
 * Spell that connects for the unit in LW(15) (-1 does nothing):
 * fires an eff_magic orb from it to the target over 20 frames while doing the casting gesture,
 * with the magic sounds.
 */
static EVT_BEGIN(attack_enemy_common_event_sub_hit)
    IF_INT_EQUAL(LW(15), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetPos, LW(15), LW(0), LW(1), LW(2))
    ADD(LW(1), 10)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
    CALL(eff_magic, LW(15), LW(10), LW(11), LW(12), 20)
    CALL_CHILD(attack_enemy_common_event_sub2)
    WAIT_FRAMES(5)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_MAGIC1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_MAGIC3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(20)
    RETURN
EVT_END()

/**
 * Single-target spell (weapon in LW(9), weapon_mahorn_attack_magic: 5 damage, pierces defence):
 * picks the first-strike target or samples a target, or does the flustered act when confused without one,
 * then runs attack_enemy_common_event.
 */
static EVT_BEGIN(attack_magic_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL_CHILD(attack_enemy_common_event)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Same as attack_magic_event without the first-strike case. Nothing in this unit references it. */
static EVT_BEGIN(confuse_magic_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL_CHILD(attack_enemy_common_event)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Spell on every target (weapon in LW(9), weapon_mahorn_all_attack_magic):
 * samples the targets, or does the flustered act when confused without any,
 * then runs attack_enemy_all_common_event.
 */
static EVT_BEGIN(all_attack_magic_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL_CHILD(attack_enemy_all_common_event)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Casting animation for the support spells on the unit in LW(3)/LW(4):
 * charges up (akari_charge_n64), raises its hands and shows the mahorn spell effect first on itself,
 * then on the target.
 */
static EVT_BEGIN(support_friend_common_event)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 40)
    CALL(evt_eff64, STRING(""), STRING("akari_charge_n64"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 70, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MAH_A_4"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("MAH_S_5A"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("MAH_S_5A"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("MAH_S_5A"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("MAH_S_5A"))
    CALL(set_hand_dest, BTL_UNIT_SELF, 2, FLOAT(-16.0f), FLOAT(29.0f), FLOAT(-5.0f))
    CALL(set_hand_dest, BTL_UNIT_SELF, 3, FLOAT(16.0f), FLOAT(29.0f), FLOAT(5.0f))
    CALL(set_hand_dest, BTL_UNIT_SELF, 4, FLOAT(-16.0f), FLOAT(11.0f), FLOAT(-5.0f))
    CALL(set_hand_dest, BTL_UNIT_SELF, 5, FLOAT(16.0f), FLOAT(11.0f), FLOAT(5.0f))
    WAIT_FRAMES(50)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MAH_A_2A"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("MAH_S_4A"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("MAH_S_4A"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("MAH_S_4A"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("MAH_S_4A"))
    CALL(set_hand_dest, BTL_UNIT_SELF, 2, FLOAT(-20.0f), FLOAT(40.0f), FLOAT(-15.0f))
    CALL(set_hand_dest, BTL_UNIT_SELF, 3, FLOAT(20.0f), FLOAT(40.0f), FLOAT(15.0f))
    CALL(set_hand_dest, BTL_UNIT_SELF, 4, FLOAT(-20.0f), FLOAT(0.0f), FLOAT(-15.0f))
    CALL(set_hand_dest, BTL_UNIT_SELF, 5, FLOAT(20.0f), FLOAT(0.0f), FLOAT(15.0f))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_MAGIC4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 15)
    CALL(evt_eff, STRING(""), STRING("mahorn"), 0, LW(0), LW(1), LW(2), FLOAT(1.3994141f), 2, 30, 0, 0, 0, 0, 0)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_MAGIC4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    ADD(LW(1), 15)
    CALL(evt_eff, STRING(""), STRING("mahorn"), 0, LW(0), LW(1), LW(2), FLOAT(1.3994141f), 2, 30, 0, 0, 0, 0, 0)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MAH_A_2C"))
    RETURN
EVT_END()

/** Casts Huge on itself (weapon_mahorn_dekadeka_magic: size up by 2 for 3 turns) after the support-spell animation. */
static EVT_BEGIN(dekadeka_magic_event)
    SET_VALUE(LW(3), -2)
    SET_VALUE(LW(4), 1)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL_CHILD(support_friend_common_event)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    WAIT_FRAMES(10)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Casts a defence boost on itself (weapon_mahorn_katikati_magic: Defense +3 for 3 turns)
 * after the support-spell animation.
 */
static EVT_BEGIN(katikati_magic_event)
    SET_VALUE(LW(3), -2)
    SET_VALUE(LW(4), 1)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL_CHILD(support_friend_common_event)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    WAIT_FRAMES(10)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Makes itself invisible (weapon_mahorn_trans_magic: 3 turns) after the support-spell animation. */
static EVT_BEGIN(trans_magic_event)
    SET_VALUE(LW(3), -2)
    SET_VALUE(LW(4), 1)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL_CHILD(support_friend_common_event)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    WAIT_FRAMES(10)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Makes itself Dodgy (weapon_mahorn_yokeyoke_magic: 3 turns) after the support-spell animation. */
static EVT_BEGIN(yokeyoke_magic_event)
    SET_VALUE(LW(3), -2)
    SET_VALUE(LW(4), 1)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL_CHILD(support_friend_common_event)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    WAIT_FRAMES(10)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Heals itself 10 HP after the support-spell animation, with the recovery effect. */
static EVT_BEGIN(recover_magic_event)
    SET_VALUE(LW(3), -2)
    SET_VALUE(LW(4), 1)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL_CHILD(support_friend_common_event)
    CALL(btlevtcmd_RecoverHp, LW(3), LW(4), 10)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    ADD(LW(1), 30)
    ADD(LW(2), 10)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, LW(0), LW(1), LW(2), 10, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(10)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Splits into copies when the Wizzerd is the last enemy:
 * after the support-spell animation it fades out,
 * spawns a copy (spawn_event) at every free spot 40 units apart in front of
 * and behind it (staying inside x 0-170), shuffles everyone's positions (mahorn_shuffle)
 * and fades them all back in, so the player cannot tell which is real.
 */
static EVT_BEGIN(bunsin_event)
    SET_VALUE(LW(3), -2)
    SET_VALUE(LW(4), 1)
    CALL_CHILD(support_friend_common_event)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_OFFSHOOT1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    SET_VALUE(LW(0), -2)
    CALL_CHILD(alpha_down_event)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 40)
        SET_VALUE(LW(4), LW(0))
        IF_INT_GREATER(LW(4), 0)
            SUBTRACT(LW(2), 10)
            CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
            IF_INT_EQUAL(LW(3), -1)
                CALL_CHILD(spawn_event)
            END_IF
        ELSE
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
        IF_INT_LESS_OR_EQUAL(LW(0), 170)
            ADD(LW(2), 10)
            CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
            IF_INT_EQUAL(LW(3), -1)
                CALL_CHILD(spawn_event)
            END_IF
        ELSE
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(mahorn_shuffle)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MAHO_OFFSHOOT2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    SET_VALUE(LW(0), -2)
    SPAWN_EVENT(alpha_up_event)
    CALL(mahorn_get_bunsin, LW(1), LW(2), LW(3), LW(4))
    SET_VALUE(LW(0), LW(1))
    SPAWN_EVENT(alpha_up_event)
    SET_VALUE(LW(0), LW(2))
    SPAWN_EVENT(alpha_up_event)
    SET_VALUE(LW(0), LW(3))
    SPAWN_EVENT(alpha_up_event)
    SET_VALUE(LW(0), LW(4))
    SPAWN_EVENT(alpha_up_event)
    WAIT_FRAMES(60)
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/**
 * Spawns one copy (entry_mahorn, the bunsin kind) at LW(0)-LW(2), invisible at first,
 * with the real Wizzerd's HP and statuses (mahorn_copy_status).
 * The copy is marked in unit work 4, gets attack_event_bunsin and the copy status table,
 * and its body is evasive so any hit makes it vanish. Retail also shows its HP gauge.
 */
static EVT_BEGIN(spawn_event)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_mahorn), 0)
    CALL(btlevtcmd_SetAlpha, LW(3), 1, 0)
    CALL(btlevtcmd_SetAlpha, LW(3), 2, 0)
    CALL(btlevtcmd_SetAlpha, LW(3), 3, 0)
    CALL(btlevtcmd_SetAlpha, LW(3), 4, 0)
    CALL(btlevtcmd_SetAlpha, LW(3), 5, 0)
    WAIT_FRAMES(2)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(13))
    CALL(mahorn_copy_status, LW(13), LW(3))
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_OffAttribute, LW(3), 33554432)
#endif
    CALL(btlevtcmd_SetUnitWork, LW(3), 4, 1)
    CALL(btlevtcmd_SetEventAttack, LW(3), PTR(attack_event_bunsin))
    CALL(btlevtcmd_SetRegistStatus, LW(3), PTR(&regist_bunsin))
    CALL(btlevtcmd_OnPartsAttribute, LW(3), 1, 16384)
    RETURN
EVT_END()

/**
 * Idle loop. The real Wizzerd also puts its copies in their stand pose.
 * While frozen, stopped or asleep its hands keep the MAH_Z_2 pose;
 * otherwise each hand flips between two poses at random.
 * Its hands bob between two offsets every 15-30 frames, forever.
 */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 4, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(mahorn_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
        CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
        IF_INT_NOT_EQUAL(LW(1), -1)
            CALL(btlevtcmd_AnimeChangePoseFromTable, LW(1), 1)
        END_IF
        IF_INT_NOT_EQUAL(LW(2), -1)
            CALL(btlevtcmd_AnimeChangePoseFromTable, LW(2), 1)
        END_IF
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_AnimeChangePoseFromTable, LW(3), 1)
        END_IF
        IF_INT_NOT_EQUAL(LW(4), -1)
            CALL(btlevtcmd_AnimeChangePoseFromTable, LW(4), 1)
        END_IF
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 9, LW(13))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 1, LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 2, LW(15))
    OR(LW(15), LW(13))
    OR(LW(15), LW(14))
    IF_INT_NOT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("MAH_Z_2"))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("MAH_Z_2"))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("MAH_Z_2"))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("MAH_Z_2"))
    ELSE
        BEGIN_SIBLING_EVENT
            LABEL(10)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("MAH_S_4A"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("MAH_S_4B"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            GOTO(10)
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            LABEL(11)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("MAH_S_4A"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("MAH_S_4B"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            GOTO(11)
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            LABEL(12)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("MAH_S_4A"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("MAH_S_4B"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            GOTO(12)
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            LABEL(13)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("MAH_S_4A"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("MAH_S_4B"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            GOTO(13)
        END_SIBLING_EVENT
    END_IF
    BEGIN_SIBLING_EVENT
        LABEL(0)
        CALL(set_hand_dest, BTL_UNIT_SELF, 2, FLOAT(-25.0f), FLOAT(30.0f), FLOAT(-10.0f))
        CALL(evt_sub_random, 15, LW(0))
        ADD(LW(0), 15)
        WAIT_FRAMES(LW(0))
        CALL(set_hand_dest, BTL_UNIT_SELF, 2, FLOAT(-15.0f), FLOAT(40.0f), FLOAT(-10.0f))
        CALL(evt_sub_random, 15, LW(0))
        ADD(LW(0), 15)
        WAIT_FRAMES(LW(0))
        GOTO(0)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LABEL(1)
        CALL(set_hand_dest, BTL_UNIT_SELF, 3, FLOAT(25.0f), FLOAT(30.0f), FLOAT(10.0f))
        CALL(evt_sub_random, 15, LW(0))
        ADD(LW(0), 15)
        WAIT_FRAMES(LW(0))
        CALL(set_hand_dest, BTL_UNIT_SELF, 3, FLOAT(15.0f), FLOAT(40.0f), FLOAT(10.0f))
        CALL(evt_sub_random, 15, LW(0))
        ADD(LW(0), 15)
        WAIT_FRAMES(LW(0))
        GOTO(1)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LABEL(2)
        CALL(set_hand_dest, BTL_UNIT_SELF, 4, FLOAT(-25.0f), FLOAT(10.0f), FLOAT(-10.0f))
        CALL(evt_sub_random, 15, LW(0))
        ADD(LW(0), 15)
        WAIT_FRAMES(LW(0))
        CALL(set_hand_dest, BTL_UNIT_SELF, 4, FLOAT(-15.0f), FLOAT(0.0f), FLOAT(-10.0f))
        CALL(evt_sub_random, 15, LW(0))
        ADD(LW(0), 15)
        WAIT_FRAMES(LW(0))
        GOTO(2)
    END_SIBLING_EVENT
    LABEL(3)
    CALL(set_hand_dest, BTL_UNIT_SELF, 5, FLOAT(25.0f), FLOAT(10.0f), FLOAT(10.0f))
    CALL(evt_sub_random, 15, LW(0))
    ADD(LW(0), 15)
    WAIT_FRAMES(LW(0))
    CALL(set_hand_dest, BTL_UNIT_SELF, 5, FLOAT(15.0f), FLOAT(0.0f), FLOAT(10.0f))
    CALL(evt_sub_random, 15, LW(0))
    ADD(LW(0), 15)
    WAIT_FRAMES(LW(0))
    GOTO(3)
    RETURN
EVT_END()

/**
 * Script helper: args[0] is the Wizzerd, args[1] receives the x position of the part of its spell effect (type
 * 3, the main orb) stored in work[7] by eff_magic, or 0 when there is none.
 */
static USER_FUNC(eff_magic_get_posX) {
    EvtWord* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, *args++));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    EffectEntry* eff = (EffectEntry*)unit->work[7];
    effMahorn2Data* work = eff->userdata;
    s32 i;

    for (i = 0; i < eff->count; i++, work++) {
        if (work->type == 3) {
            evtSetFloat(event, *args++, work->position.x);
            break;
        }
    }
    if (i == eff->count) {
        evtSetFloat(event, *args++, 0.0f);
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper: casts the Wizzerd's spell (effMahorn2).
 * args[0] is the caster, args[1] the target x (args[2], args[3] are read but unused),
 * args[4] the flight time in frames.
 * The effect starts at the caster's wand height and travels horizontally to the target x;
 * its handle is kept in work[7] for eff_magic_get_posX.
 */
static USER_FUNC(eff_magic) {
    EvtWord* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 a = evtGetFloat(event, args[1]);
    f32 b = evtGetFloat(event, args[2]);
    f32 c = evtGetFloat(event, args[3]);
    s32 time = evtGetValue(event, args[4]);
    f32 x;
    f32 y;
    f32 z;

    BtlUnit_GetPos(unit, &x, &y, &z);
    x += unit->sizeMultiplier * unit->faceDirection;
    y += 18.0f * unit->sizeMultiplier;
    z += 5.0f;
    unit->work[7] = (EvtWord)effMahorn2Entry(0, x, y, z, a, y, z, unit->sizeMultiplier, mahorn_fabs((a - x) / time));
    return EVT_RETURN_DONE;
}

/**
 * Script helper: args[0] is the real caster and args[1] one of its copies.
 * The copy takes over the real one's current HP
 * and its block of status-effect counters (0x1E bytes from sleepTurns), and its HP gauge is reset to match,
 * so every decoy shows the same health and status.
 */
static USER_FUNC(mahorn_copy_status) {
    EvtWord* args = event->args;
    s32 id1 = evtGetValue(event, args[0]);
    s32 id2 = evtGetValue(event, args[1]);
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit1 = BattleGetUnitPtr(wp, id1);
    BattleUnit* unit2 = BattleGetUnitPtr(wp, id2);

    unit2->currentHp = unit1->currentHp;
    memcpy(&unit2->sleepTurns, &unit1->sleepTurns, 0x1E);
    unit2->hpGauge.prevHp = unit2->currentHp;
    unit2->hpGauge.targetHp = unit2->currentHp;
    unit2->hpGauge.barRatio = unit2->hpGauge.trailRatio = (f32)unit2->currentHp / unit2->maxHp;
    return EVT_RETURN_DONE;
}

/**
 * Script helper: ten times swaps, at random, the x/z positions
 * and home positions of two of the Wizzerds on the field (the real one and its copies, kinds 0x80, 0x81,
 * 0xA9 and 0xAA), so the player cannot tell which one is real.
 */
static USER_FUNC(mahorn_shuffle) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* kamecs[6];
    s32 n = 0;
    s32 i;

    // the real wizzerd and its copies
    for (i = 0; i < 64; i++) {
        kamecs[n] = wp->units[i];
        if (kamecs[n] != NULL && (kamecs[n]->currentKind == 0x80 || kamecs[n]->currentKind == 0x81 || kamecs[n]->currentKind == 0xA9 || kamecs[n]->currentKind == 0xAA)) {
            n++;
        }
    }
    for (i = 0; i < 10; i++) {
        s32 a = irand(n);
        s32 b = irand(n);
        BattleUnit* ua = kamecs[a];
        BattleUnit* ub = kamecs[b];
        f32 tmp;

        tmp = ua->position.x;
        ua->position.x = ub->position.x;
        ub->position.x = tmp;
        tmp = ua->homePosition.x;
        ua->homePosition.x = ub->homePosition.x;
        ub->homePosition.x = tmp;
        tmp = ua->position.z;
        ua->position.z = ub->position.z;
        ub->position.z = tmp;
        tmp = ua->homePosition.z;
        ua->homePosition.z = ub->homePosition.z;
        ub->homePosition.z = tmp;
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper: lists the Wizzerd's copies ('bunsin' = clone, kinds 0x81 and 0xAA).
 * args[0]-args[3] receive the unit indices of up to four copies (-1 for unused slots)
 * and args[4] receives how many copies exist.
 */
static USER_FUNC(mahorn_get_bunsin) {
    EvtWord* args = event->args;
    s32 copies[4];
    s32 n = 0;
    s32 i;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;

    // indices of the wizzerd's copies
    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && (unit->currentKind == 0x81 || unit->currentKind == 0xAA)) {
            copies[n] = i;
            n++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (i < n) {
            evtSetValue(event, *args++, copies[i]);
        } else {
            evtSetValue(event, *args++, -1);
        }
    }
    evtSetValue(event, *args, n);
    return EVT_RETURN_DONE;
}

/**
 * Script helper: moves one of the Wizzerd's floating hands to a new resting offset.
 * args[0] is the unit, args[1] the hand (part 2-5), args[2]-args[4] the x, y, z offset (x is mirrored);
 * the offset is scaled by 1.25 while the Wizzerd is Mega (status 10) and by 0.75 while Mini (status 11).
 * hand_ctrl then eases the hand to it.
 */
static USER_FUNC(set_hand_dest) {
    s32 hand;
    BattleUnit* unit;
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id;
    f32* dest;
    f32 x;
    f32 y;
    f32 z;

    id = evtGetValue(event, args[0]);
    hand = evtGetValue(event, args[1]);
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    if (unit == NULL) {
        return EVT_RETURN_BLOCK;
    }
    hand -= 2;
    dest = (f32*)unit->work[hand];
    if (BtlUnit_CheckStatus(unit, 10)) {
        dest[0] = 1.25f * -x;
        dest[1] = 1.25f * y;
        dest[2] = 1.25f * z;
    } else if (BtlUnit_CheckStatus(unit, 11)) {
        dest[0] = 0.75f * -x;
        dest[1] = 0.75f * y;
        dest[2] = 0.75f * z;
    } else {
        dest[0] = -x;
        dest[1] = y;
        dest[2] = z;
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper called every frame: eases each of the Wizzerd's four hands (parts 2-5) a tenth of the way toward
 * the offset set by set_hand_dest.
 * Does nothing while the unit is asleep, stopped or frozen (statuses 2, 9 or 1 with turns left).
 */
static USER_FUNC(hand_ctrl) {
    EvtWord* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    s8 turns;
    s8 strength;
    BattleUnitPart* part;
    f32* dest;
    Vec* scale;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 j;

    if (unit == NULL) {
        return EVT_RETURN_BLOCK;
    }
    BtlUnit_GetStatus(unit, 2, &turns, &strength);
    if (turns > 0) {
        return EVT_RETURN_DONE;
    }
    BtlUnit_GetStatus(unit, 9, &turns, &strength);
    if (turns > 0) {
        return EVT_RETURN_DONE;
    }
    BtlUnit_GetStatus(unit, 1, &turns, &strength);
    if (turns > 0) {
        return EVT_RETURN_DONE;
    }
    for (j = 0, i = 2; i <= 5; i++, j++) {
        part = BtlUnit_GetPartsPtr(unit, i);
        dest = (f32*)unit->work[j];
        scale = &part->baseScale;
        x = part->positionOffset.x * scale->x;
        y = part->positionOffset.y * scale->y;
        z = part->positionOffset.z * scale->z;
        x += (dest[0] - x) / 10.0f;
        y += (dest[1] - y) / 10.0f;
        z += (dest[2] - z) / 10.0f;
        part->positionOffset.x = x;
        part->positionOffset.y = y;
        part->positionOffset.z = z;
    }
    return EVT_RETURN_DONE;
}

/** Script helper: frees the four hand offset buffers hand_init allocated in the Wizzerd's work[0]-work[3]. */
static USER_FUNC(hand_end) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    s32 i;
    s32 j;

    for (i = 2, j = 0; i <= 5; i++, j++) {
        if ((void*)unit->work[j] != NULL) {
            BattleFree((void*)unit->work[j]);
            unit->work[j] = 0;
        }
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper: sets the Wizzerd's four hands (parts 2-5) to the MAH_Z_2 animation
 * and allocates a zeroed offset buffer for each in work[0]-work[3]; set_hand_dest and hand_ctrl use them.
 */
static USER_FUNC(hand_init) {
    EvtWord* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    f32 x;
    f32 y;
    f32 z;
    f32* dest;
    s32 i;
    s32 j;

    BtlUnit_GetPos(unit, &x, &y, &z);
    for (j = 0, i = 2; i <= 5; i++, j++) {
        BtlUnit_SetAnim(BtlUnit_GetPartsPtr(unit, i), "MAH_Z_2");
        dest = BTL_ALLOC(12);
        unit->work[j] = (EvtWord)dest;
        dest[0] = 0.0f;
        dest[1] = 0.0f;
        dest[2] = 0.0f;
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper: args[0] receives the number of enemy-side units (alliance 1) that are still alive,
 * i.e. do not have status 0x1B. The scripts use it to see whether any Magikoopa or Wizzerd is left.
 */
static USER_FUNC(mahorn_get_live_num) {
    s32 i;
    EvtWord* args = event->args;
    s32 num = 0;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;

    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && unit->alliance == 1 && !BtlUnit_CheckStatus(unit, 0x1B)) {
            num++;
        }
    }
    evtSetValue(event, args[0], num);
    return EVT_RETURN_DONE;
}
