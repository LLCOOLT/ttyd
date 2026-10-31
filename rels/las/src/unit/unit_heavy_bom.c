// Palace of Shadow battle unit: the Bulky Bob-omb (`heavy_bom`): parts, stats, poses and AI scripts.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle_unit.h"
#include "driver/animdrv.h"
#include "string.h"
#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "battle/battle_database_common.h"
#include "evt/evt_snd.h"
#include "data_tables.h"
#include "version.h"

// Unit work slots (btlevtcmd_SetUnitWork / GetUnitWork)
enum {
    UW_HEAVY_BOM_FUSE_LIT = 0,    // nonzero once the fuse is lit (its first attack)
    UW_HEAVY_BOM_FUSE_LEFT = 1,   // fuse stages left, 3 down to 0; picks the pose tables and the spark locator
    UW_HEAVY_BOM_FUSE_SFX = 2,    // id of the looping fuse sound, -1 when none
    UW_HEAVY_BOM_GUARD_CYCLE = 3, // which guard weapon it uses next (0, 1, 2, then back to 0)
};

static USER_FUNC(_set_draw_callback);

static BattleUnitKind unit_heavy_bom;
static BattleWeapon weapon_heavy_bomb_super_explosion;
static BattleWeapon weapon_heavy_bomb_guard;
static BattleWeapon weapon_heavy_bomb_guard_2;
static BattleWeapon weapon_heavy_bomb_guard_3;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table_3[16];
static PoseTableEntry pose_table_3_fire[16];
static PoseTableEntry pose_table_2[16];
static PoseTableEntry pose_table_2_fire[16];
static PoseTableEntry pose_table_1[16];
static PoseTableEntry pose_table_1_fire[16];
static PoseTableEntry pose_table_0_fire[16];
static PoseTableEntry pose_table_0[16];
static PoseTableEntry pose_table_3_to_2[13];
static PoseTableEntry pose_table_2_to_1[13];
static PoseTableEntry pose_table_1_to_0[13];
static BattleDataEntry data_table[3];
static PoseSoundTiming pose_sound_timing_table[9];
static BattleUnitKindPart parts[2];
static EvtWord init_event[57];
static EvtWord damage_event[118];
static EvtWord phase_event[126];
static EvtWord attack_event[175];
static EvtWord wait_event[6];
static EvtWord dead_event[52];
#if VERSION >= VERSION_US
static EvtWord explosion_event[254];
#else
static EvtWord explosion_event[247];
#endif

/**
 * Unit data of the Bulky Bob-omb; ties together its sounds, parts, status vulnerability, init event
 * and event table.
 */
static BattleUnitKind unit_heavy_bom = {
    92, // unitType
    "btl_un_heavy_bom", // name
    6, // maxHp
    0, // maxFp
    1, // dangerHP
    1, // perilHP
    22, // level
    0, // bonusExp
    4, // bonusCoin
    70, // bonusCoinRate
    0, // baseCoin
    40, // runRate
    9999, // pbSoftCap
    54, // width
    70, // height
    {7, 70}, // hitOffset
    {0.0f, 35.0f, 0.0f}, // centerOffset
    {0}, // hpGaugeOffset
    {0}, // talkTogeBaseOffset
    {27.0f, 0.0f, -10.0f}, // heldItemBaseOffset
    {0}, // burnFlameOffset
    0.0f, 0.0f, // vivianOffsetX..vivianOffsetZ
    {27.0f, 0.0f, 0.0f}, // bintaHitOffset
    {27.0f, 45.5f, 0.0f}, // kissHitOffset
    {0.0f, 35.0f, 0.0f}, // cutBaseOffset
    54.0f, // cutWidth
    70.0f, // cutHeight
    0, 0, 0, // turnOrder..swallowChance
    2, // swallowAttributes
    100, // hammerKnockbackChance
    0, // itemStealParam
    {0}, // starPointDispOffset
    "SFX_ENM_HEAVYB_DAMAGED1", // damageSfxName
    "SFX_BTL_DAMAGE_FIRE1", // fireDamageSfxName
    "SFX_BTL_DAMAGE_ICE1", // iceDamageSfxName
    "SFX_BTL_DAMAGE_BIRIBIRI1", // explosionDamageSfxName
    0, // attributeFlags
    &regist, // statusVulnerability
    2, // numParts
    parts, // parts
    init_event, // initEventCode
    (BattleDataEntry*)data_table, // dataTable
};

/**
 * Weapon of the Bulky Bob-omb (super explosion): targets every unit for 2 damage, explosion element;
 * used by explosion_event.
 */
static BattleWeapon weapon_heavy_bomb_super_explosion = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_EXPLOSION, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_BOMB_FLIPPABLE | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 50, 50, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Weapon of the Bulky Bob-omb (guard): targets every unit, raises Defense (3 turns); used by attack_event.
 */
static BattleWeapon weapon_heavy_bomb_guard = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ONLY_SELF | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_UNGUARDABLE, // special
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

/**
 * Weapon of the Bulky Bob-omb (guard 2): targets every unit, raises Attack (2 turns); used by attack_event.
 */
static BattleWeapon weapon_heavy_bomb_guard_2 = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ONLY_SELF | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, // burnChance..sizeChangeStrength
    100, // atkChangeChance
#if VERSION <= VERSION_DEMO_US
    2, // atkChangeTime
#else
    3, // atkChangeTime
#endif
    3, // atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Weapon of the Bulky Bob-omb (guard 3): targets every unit; used by attack_event. */
static BattleWeapon weapon_heavy_bomb_guard_3 = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ONLY_SELF | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
#if VERSION <= VERSION_DEMO_US
    6, // chargeStrength
#else
    3, // chargeStrength
#endif
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Defence of the Bulky Bob-omb: 1 against every kind of hit. */
static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

/** Defence attributes of the Bulky Bob-omb: none, every element hits it normally. */
static BattleUnitDefenseAttr defence_attr = {0};

#if VERSION <= VERSION_DEMO_US
/**
 * Demo builds: Status vulnerability of the Bulky Bob-omb (percent chance each status takes hold):
 * immune to poison; resists sleep (70%), stop (50%), dizzy (70%), confusion (70%), freeze (70%),
 * Tiny (70%), Attack Down (70%), Defense Down (70%), allergic (70%), Gale Force (20%), Slow (70%);
 * the rest take hold at 80% or better.
 */
static StatusVulnerability regist = {70, 50, 70, 0, 70, 150, 100, 70, 100, 70, 100, 70, 100, 70, 70, 80, 20, 100, 70, 100, 100, 95};
#else
/**
 * Retail builds: Status vulnerability of the Bulky Bob-omb (percent chance each status takes hold):
 * immune to poison; resists stop (75%), dizzy (70%), confusion (70%), allergic (70%), Gale Force (20%),
 * Slow (70%); the rest take hold at 80% or better.
 */
static StatusVulnerability regist = {90, 75, 70, 0, 70, 150, 100, 100, 100, 80, 100, 80, 100, 95, 70, 80, 20, 100, 70, 100, 100, 95};
#endif

/** Poses of the Bulky Bob-omb with its fuse at length 3 and not lit (the full length it starts with). */
static PoseTableEntry pose_table_3[] = {
    {1, "N_1"},
    {9, "Y_1"},
    {2, "Y_1"},
    {3, "K_1"},
    {4, "X_1"},
    {5, "K_1"},
    {9, "Z_1"},
    {BTL_POSE_NORMAL, "S_1"},
    {29, "D_1"},
    {35, "S_1"},
    {31, "S_1"},
    {BTL_POSE_DAMAGE, "D_1"},
    {BTL_POSE_DANGER, "X_1"},
    {BTL_POSE_PERIL, "X_1"},
    {BTL_POSE_TALK, "S_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

/** Poses of the Bulky Bob-omb with its fuse at length 3, burning (lit). */
static PoseTableEntry pose_table_3_fire[] = {
    {1, "N_1"},
    {9, "Y_1"},
    {2, "Y_1"},
    {3, "K_1"},
    {4, "X_1"},
    {5, "K_1"},
    {9, "Z_1"},
    {BTL_POSE_NORMAL, "S_1"},
    {29, "D_1"},
    {35, "S_1"},
    {31, "S_1"},
    {BTL_POSE_DAMAGE, "D_1"},
    {BTL_POSE_DANGER, "X_1"},
    {BTL_POSE_PERIL, "X_1"},
    {BTL_POSE_TALK, "S_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

/** Poses of the Bulky Bob-omb with its fuse at length 2 and not lit. */
static PoseTableEntry pose_table_2[] = {
    {1, "N_2"},
    {9, "Y_2"},
    {2, "Y_2"},
    {3, "K_2"},
    {4, "X_2"},
    {5, "K_2"},
    {9, "Z_2B"},
    {BTL_POSE_NORMAL, "S_2B"},
    {29, "D_2"},
    {35, "S_2B"},
    {31, "S_2B"},
    {BTL_POSE_DAMAGE, "D_2"},
    {BTL_POSE_DANGER, "X_2"},
    {BTL_POSE_PERIL, "X_2"},
    {BTL_POSE_TALK, "S_2B"},
    {BTL_POSE_STAY_DEFAULT, "S_2B"},
};

/** Poses of the Bulky Bob-omb with its fuse at length 2, burning (lit). */
static PoseTableEntry pose_table_2_fire[] = {
    {1, "N_2"},
    {9, "Y_2"},
    {2, "Y_2"},
    {3, "K_2"},
    {4, "X_2"},
    {5, "K_2"},
    {9, "Z_2A"},
    {BTL_POSE_NORMAL, "S_2A"},
    {29, "D_2"},
    {35, "S_2A"},
    {31, "S_2A"},
    {BTL_POSE_DAMAGE, "D_2"},
    {BTL_POSE_DANGER, "X_2"},
    {BTL_POSE_PERIL, "X_2"},
    {BTL_POSE_TALK, "S_2A"},
    {BTL_POSE_STAY_DEFAULT, "S_2A"},
};

/** Poses of the Bulky Bob-omb with its fuse at length 1 and not lit. */
static PoseTableEntry pose_table_1[] = {
    {1, "N_3"},
    {9, "Y_3"},
    {2, "Y_3"},
    {3, "K_3"},
    {4, "X_3"},
    {5, "K_3"},
    {9, "Z_3B"},
    {BTL_POSE_NORMAL, "S_3B"},
    {29, "D_3"},
    {35, "S_3B"},
    {31, "S_3B"},
    {BTL_POSE_DAMAGE, "D_3"},
    {BTL_POSE_DANGER, "X_3"},
    {BTL_POSE_PERIL, "X_3"},
    {BTL_POSE_TALK, "S_3B"},
    {BTL_POSE_STAY_DEFAULT, "S_3B"},
};

/** Poses of the Bulky Bob-omb with its fuse at length 1, burning (lit). */
static PoseTableEntry pose_table_1_fire[] = {
    {1, "N_3"},
    {9, "Y_3"},
    {2, "Y_3"},
    {3, "K_3"},
    {4, "X_3"},
    {5, "K_3"},
    {9, "Z_3A"},
    {BTL_POSE_NORMAL, "S_3A"},
    {29, "D_3"},
    {35, "S_3A"},
    {31, "S_3A"},
    {BTL_POSE_DAMAGE, "D_3"},
    {BTL_POSE_DANGER, "X_3"},
    {BTL_POSE_PERIL, "X_3"},
    {BTL_POSE_TALK, "S_3A"},
    {BTL_POSE_STAY_DEFAULT, "S_3A"},
};

/** Poses of the Bulky Bob-omb with its fuse at length 0, burning (lit). */
static PoseTableEntry pose_table_0_fire[] = {
    {1, "N_4"},
    {9, "Y_4"},
    {2, "Y_4"},
    {3, "K_4"},
    {4, "X_4"},
    {5, "K_4"},
    {9, "Z_4A"},
    {BTL_POSE_NORMAL, "S_4A"},
    {29, "D_4"},
    {35, "S_4A"},
    {31, "S_4A"},
    {BTL_POSE_DAMAGE, "D_4"},
    {BTL_POSE_DANGER, "X_4"},
    {BTL_POSE_PERIL, "X_4"},
    {BTL_POSE_TALK, "S_4A"},
    {BTL_POSE_STAY_DEFAULT, "S_4A"},
};

/** Poses of the Bulky Bob-omb with its fuse at length 0 and not lit. */
static PoseTableEntry pose_table_0[] = {
    {1, "N_4"},
    {9, "Y_4"},
    {2, "Y_4"},
    {3, "K_4"},
    {4, "X_4"},
    {5, "K_4"},
    {9, "Z_4B"},
    {BTL_POSE_NORMAL, "S_4B"},
    {29, "D_4"},
    {35, "S_4B"},
    {31, "S_4B"},
    {BTL_POSE_DAMAGE, "D_4"},
    {BTL_POSE_DANGER, "X_4"},
    {BTL_POSE_PERIL, "X_4"},
    {BTL_POSE_TALK, "S_4B"},
    {BTL_POSE_STAY_DEFAULT, "S_4B"},
};

/** Poses played while the burning fuse of the Bulky Bob-omb shortens from length 3 to 2. */
static PoseTableEntry pose_table_3_to_2[] = {
    {1, "B_4"},
    {9, "B_1"},
    {2, "B_1"},
    {3, "B_7"},
    {4, "B_10"},
    {5, "B_7"},
    {BTL_POSE_NORMAL, "B_1"},
    {31, "B_1"},
    {BTL_POSE_DAMAGE, "B_1"},
    {BTL_POSE_DANGER, "B_10"},
    {BTL_POSE_PERIL, "B_10"},
    {BTL_POSE_TALK, "B_1"},
    {BTL_POSE_STAY_DEFAULT, "B_1"},
};

/** Poses played while the burning fuse of the Bulky Bob-omb shortens from length 2 to 1. */
static PoseTableEntry pose_table_2_to_1[] = {
    {1, "B_5"},
    {9, "B_2"},
    {2, "B_2"},
    {3, "B_8"},
    {4, "B_11"},
    {5, "B_8"},
    {BTL_POSE_NORMAL, "B_2"},
    {31, "B_2"},
    {BTL_POSE_DAMAGE, "B_2"},
    {BTL_POSE_DANGER, "B_11"},
    {BTL_POSE_PERIL, "B_11"},
    {BTL_POSE_TALK, "B_2"},
    {BTL_POSE_STAY_DEFAULT, "B_2"},
};

/** Poses played while the burning fuse of the Bulky Bob-omb shortens from length 1 to 0. */
static PoseTableEntry pose_table_1_to_0[] = {
    {1, "B_6"},
    {9, "B_3"},
    {2, "B_3"},
    {3, "B_9"},
    {4, "B_12"},
    {5, "B_9"},
    {BTL_POSE_NORMAL, "B_3"},
    {31, "B_3"},
    {BTL_POSE_DAMAGE, "B_3"},
    {BTL_POSE_DANGER, "B_12"},
    {BTL_POSE_PERIL, "B_12"},
    {BTL_POSE_TALK, "B_3"},
    {BTL_POSE_STAY_DEFAULT, "B_3"},
};

/** Event table of the Bulky Bob-omb: dead_event (tag 49), explosion_event (tag 52). */
static BattleDataEntry data_table[] = {
    {49, dead_event},
    {52, explosion_event},
    {0},
};

/**
 * Sound cues of the Bulky Bob-omb: SFX_ENM_HEAVYB_WAIT3 plays at fixed points of the animations S_3A, S_4A.
 */
static PoseSoundTiming pose_sound_timing_table[] = {
    {"S_3A", 0.01f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {"S_3A", 0.26666668f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {"S_3A", 0.53333336f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {"S_3A", 0.8f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {"S_4A", 0.01f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {"S_4A", 0.16666667f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {"S_4A", 0.33333334f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {"S_4A", 0.5f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {NULL, 0.0f, NULL, NULL, 0, 1},
};

/** Parts of the Bulky Bob-omb: 2 parts (model c_heavy). */
static BattleUnitKindPart parts[] = {
    {
        1, // partNum
        "btl_un_heavy_bom", // partName
        "c_heavy", // modelName
        {0}, // positionOffset
        {15.0f, 50.0f, 0.0f}, // hitBaseOffset
        {0.0f, 65.0f, 0.0f}, // hitCursorBaseOffset
        65, // shadowSize
        70, // hitHeight
        255, // baseAlpha
        &defence, // defense
        &defence_attr, // defenseAttr
        PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, // attributes
        0, // counterAttributes
        pose_table_3, // poseTable
    },
    {
        2, // partNum
        "ヘビーボム", // partName
        "c_heavy", // modelName
        {0.0f, 80.0f, 0.0f}, // positionOffset
        {0}, // hitBaseOffset
        {0}, // hitCursorBaseOffset
        15, // shadowSize
        15, // hitHeight
        255, // baseAlpha
        &defence, // defense
        &defence_attr, // defenseAttr
        PART_ATTR_NOT_TARGETABLE | PART_ATTR_NO_SHADOW, // attributes
        0, // counterAttributes
        pose_table_3, // poseTable
    },
};

/**
 * Init event of the Bulky Bob-omb: installs its wait, phase, attack,
 * damage and confusion events and sets its unit work:
 * 0 = fuse lit, 1 = fuse length left (starts at 3), 2 = the fuse sound handle (-1 for none),
 * 3 = which guard weapon is next. Part 2 gets the fuse flame pose F_1 and the draw callback is set up.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_LIT, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_LEFT, 3)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_SFX, -1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_GUARD_CYCLE, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("F_1"))
    CALL(btlevtcmd_AnimeSetPoseSoundTable, BTL_UNIT_SELF, 1, PTR(pose_sound_timing_table))
    CALL(_set_draw_callback)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage event of the Bulky Bob-omb: when it is Frozen (status 9) with the fuse lit, the fuse sound is stopped,
 * the fuse is put out and the pose table matching the remaining fuse length is restored.
 * On the last hit of a move, damage codes 0x18 fire, 0x19 explosion and 0x1B electric,
 * or the counters 0x2E fiery, 0x32 volatile explosive, 0x34 electrified and 0x36 Hold Fast,
 * make it detonate through dead_event instead; anything else is the default damage handling.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_FREEZE, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_LIT, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_SFX, LW(0))
            CALL(evt_snd_sfxoff, LW(0))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_SFX, -1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_LIT, 0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_LEFT, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(2)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_2))
                CASE_EQUAL(1)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_1))
                CASE_EQUAL(0)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_0))
            END_SWITCH
        END_IF
    END_IF
    CALL(btlevtcmd_CheckDamageCode, LW(10), DAMAGE_FLAG_LAST_HIT, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
        SWITCH(LW(0))
            CASE_OR_EQUAL(27)
            CASE_OR_EQUAL(24)
            CASE_OR_EQUAL(25)
            CASE_OR_EQUAL(52)
            CASE_OR_EQUAL(46)
            CASE_OR_EQUAL(50)
            CASE_OR_EQUAL(54)
            GOTO(50)
            CASE_END
        END_SWITCH
    END_IF
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
    LABEL(50)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 29)
    CALL_CHILD(dead_event)
    RETURN
EVT_END()

/**
 * Phase event of the Bulky Bob-omb: after the player phase, if the fuse is lit,
 * the fuse burns one step shorter (pose table changes 3 to 2, 2 to 1, 1 to 0,
 * with the sizzling sound and 40 frames wait).
 * When the fuse is already at length 0 it plays K_4 and queues the explosion (after-reaction event 52).
 */
static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_LIT, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_SELF)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_LEFT, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("K_4"))
                CALL(btlevtcmd_AfterReactionEntry, BTL_UNIT_SELF, 52)
                RETURN
            END_IF
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HEAVYB_WAIT2"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_LEFT, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(3)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_3_to_2))
                CASE_EQUAL(2)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_2_to_1))
                CASE_EQUAL(1)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_1_to_0))
            END_SWITCH
            CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
            WAIT_FRAMES(40)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_LEFT, LW(0))
            SUBTRACT(LW(0), 1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_LEFT, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(2)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_2_fire))
                CASE_EQUAL(1)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_1_fire))
                CASE_EQUAL(0)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_0_fire))
            END_SWITCH
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            RETURN
        END_IF
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * Attack event of the Bulky Bob-omb: it never hits anyone directly.
 * If the fuse is not lit it plays the guard pose for the current fuse length,
 * lights the fuse (unit work 0 = 1, the fuse sound handle in unit work 2) and sets unit flag 16.
 * If the fuse is already lit it just guards, rotating through three guard weapons (weapon_heavy_bomb_guard, _2,
 * _3) for the self-targeted damage check.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HEAVYB_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_LIT, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_LEFT, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(3)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_1"))
            CASE_EQUAL(2)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_2"))
            CASE_EQUAL(1)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_3"))
            CASE_EQUAL(0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_4"))
        END_SWITCH
        WAIT_FRAMES(40)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HEAVYB_WAIT1"), EVT_NULLPTR, 0, LW(0))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_SFX, LW(0))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HEAVYB_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_LIT, 1)
        CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_FUSE_LIT)
    ELSE
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_LEFT, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(3)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_1"))
            CASE_EQUAL(2)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_2"))
            CASE_EQUAL(1)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_3"))
            CASE_EQUAL(0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_4"))
        END_SWITCH
        WAIT_FRAMES(40)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_GUARD_CYCLE, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_VALUE(LW(12), PTR(&weapon_heavy_bomb_guard))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_GUARD_CYCLE, 1)
            CASE_EQUAL(1)
            SET_VALUE(LW(12), PTR(&weapon_heavy_bomb_guard_2))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_GUARD_CYCLE, 2)
            CASE_EQUAL(2)
            SET_VALUE(LW(12), PTR(&weapon_heavy_bomb_guard_3))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_GUARD_CYCLE, 0)
        END_SWITCH
        CALL(btlevtcmd_WeaponAftereffect, LW(12))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, BTL_UNIT_SELF, 1, LW(12), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_IF
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Wait event of the Bulky Bob-omb: plays its idle pose from the current pose table (the table is swapped as the
 * fuse
 * gets shorter).
 */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Dead event of the Bulky Bob-omb: stops the fuse sound.
 * For the blast damage codes it queues the explosion (after-reaction event 52) instead of dying normally;
 * any other kill runs the common death sequence.
 */
static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_SFX, LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
        CALL(evt_snd_sfxoff, LW(0))
    END_IF
    CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
    SWITCH(LW(0))
        CASE_OR_EQUAL(27)
        CASE_OR_EQUAL(24)
        CASE_OR_EQUAL(25)
        CASE_OR_EQUAL(52)
        CASE_OR_EQUAL(46)
        CASE_OR_EQUAL(50)
        CASE_OR_EQUAL(54)
        GOTO(50)
        CASE_END
    END_SWITCH
    LABEL(10)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(subsetevt_dead_core)
    RETURN
    LABEL(50)
    CALL(btlevtcmd_AfterReactionEntry, BTL_UNIT_SELF, 52)
    RETURN
EVT_END()

/**
 * After-reaction event 52 of the Bulky Bob-omb: the explosion.
 * The fuse sound is stopped, the camera shakes (US and later),
 * a big bomb effect and a series of smaller ones go off around it,
 * and weapon_heavy_bomb_super_explosion damages every target of the opposing side in turn (the "super
 * explosion"). Then the unit dies without a reward.
 */
static EVT_BEGIN(explosion_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_SFX, LW(0))
    CALL(evt_snd_sfxoff, LW(0))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HEAVY_BOM_FUSE_SFX, -1)
#if VERSION >= VERSION_US
    CALL(evt_btl_camera_shake_h, 0, 10, 0, 60, 4)
#endif
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HEAVYB_ATTACK3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(5))
    DIVIDE(LW(5), 2)
    CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
    MULTIPLY_FLOAT(LW(5), LW(6))
    ADD(LW(1), LW(5))
    CALL(evt_eff, 0, STRING("bomb"), 5, LW(0), LW(1), LW(2), FLOAT(2.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_StageDispellFog)
    WAIT_MS(300)
    CALL(evt_eff, 0, STRING("bomb"), 4, -40, 30, 20, FLOAT(2.0f), 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(125)
    CALL(evt_eff, 0, STRING("bomb"), 4, 40, 90, 20, FLOAT(2.0f), 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(125)
    CALL(evt_eff, 0, STRING("bomb"), 4, 40, 30, 20, FLOAT(2.0f), 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(125)
    CALL(evt_eff, 0, STRING("bomb"), 4, -40, 90, 20, FLOAT(2.0f), 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(125)
    CALL(evt_eff, 0, STRING("bomb"), 4, -100, 60, 20, FLOAT(2.0f), 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(125)
    CALL(evt_eff, 0, STRING("bomb"), 4, 100, 60, 20, FLOAT(2.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_heavy_bomb_super_explosion))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_heavy_bomb_super_explosion), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_heavy_bomb_super_explosion))
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_heavy_bomb_super_explosion))
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_heavy_bomb_super_explosion), DAMAGE_FLAG_LAST_HIT, LW(5))
    IF_INT_EQUAL(LW(5), 1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_heavy_bomb_super_explosion), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_IF
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    LABEL(99)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(subsetevt_dead_core)
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

void animPoseDrawShape(s32 poseId, s32 shapeIdx);

/**
 * Part draw callback for the Bulky Bob-omb's fuse: while unit->work[UW_HEAVY_BOM_FUSE_LIT] is set,
 * draws the fire plane shape (pPlaneShape3) of part 2 at the locator (locator11 down to locator8,
 * chosen by unit->work[UW_HEAVY_BOM_FUSE_LEFT]) that marks the burning fuse point.
 */
static void _fire_point_callback(BattleUnitPart* part, s32 group) {
    BattleUnit* unit = part->owner;
    const char* name;
    s32 poseId;

    if (unit->work[UW_HEAVY_BOM_FUSE_LIT] == 0) {
        return;
    }
    poseId = part->poseId;
    switch (unit->work[UW_HEAVY_BOM_FUSE_LEFT]) {
        case 0:
            name = "locator11";
            break;
        case 1:
            name = "locator10";
            break;
        case 2:
            name = "locator9";
            break;
        case 3:
        default:
            name = "locator8";
            break;
    }
    if (strcmp(name, animPoseGetGroupName(poseId, group)) == 0) {
        s32 shapePose = BtlUnit_GetPartsPtr(unit, 2)->poseId;
        s32 shape = animPoseGetShapeIdx(shapePose, "pPlaneShape3");
        animPoseDrawShape(shapePose, shape);
    }
}

/**
 * Script helper: attaches _fire_point_callback to the Bulky Bob-omb's body part
 * and hides part 2 (the fire shape drawn by the callback). Operates on the running unit (BTL_UNIT_SELF).
 */
static USER_FUNC(_set_draw_callback) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(wp, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);

    animPoseSetDispCallBack(part->poseId, _fire_point_callback, part);
    BtlUnit_GetPartsPtr(unit, 2)->attributes |= PART_ATTR_HIDDEN;
    return EVT_RETURN_DONE;
}
