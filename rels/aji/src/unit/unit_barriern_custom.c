// X-Naut Fortress (aji) battle unit: X-Yux (barriern_custom), which creates Mini-X-Yux shields: its parts, defence/status
// tables, and attack events.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "eff/eff_syuryou.h"
#include "memory.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"
#include "unit/unit_barriern.h"
#include "eff/n64/eff_glass_n64.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"
#include "system.h"
#include "driver/mapdrv.h"

// Unit work slots of the X-Yux (btlevtcmd_SetUnitWork / GetUnitWork, unit->work)
enum {
    UW_BARRIERN_CUSTOM_SATELLITE_COUNT = 0, // Mini-X-Yux in orbit (starts from the battle setup; reset after each re-split)
    UW_BARRIERN_CUSTOM_COMBINED_ATTACK = 1, // 1 while the combined ring attack (wawawa) runs: rings fly blurred
    UW_BARRIERN_CUSTOM_RINGS_DONE = 2,      // rings of the combined attack that have finished their flight
    UW_BARRIERN_CUSTOM_BARRIER_EFFECT = 3,  // barrier effect (EffectEntry*) shown while a satellite is alive
    UW_BARRIERN_CUSTOM_SATELLITE_1 = 4,     // unit id of Mini-X-Yux 1, or -1 (slots 4-7 hold satellites 1-4)
    UW_BARRIERN_CUSTOM_SATELLITE_2 = 5,     // unit id of Mini-X-Yux 2, or -1
    UW_BARRIERN_CUSTOM_SATELLITE_3 = 6,     // unit id of Mini-X-Yux 3, or -1
    UW_BARRIERN_CUSTOM_SATELLITE_4 = 7,     // unit id of Mini-X-Yux 4, or -1
    UW_BARRIERN_CUSTOM_SPLINE_1 = 10,       // SatelliteSpline* of the move in progress for satellite 1 (slots 10-13 for 1-4)
    UW_BARRIERN_CUSTOM_SPLINE_2 = 11,       // SatelliteSpline* for satellite 2
    UW_BARRIERN_CUSTOM_SPLINE_3 = 12,       // SatelliteSpline* for satellite 3
    UW_BARRIERN_CUSTOM_SPLINE_4 = 13,       // SatelliteSpline* for satellite 4
};

static u8 barriernSatelliteTo_Init(BattleUnit* unit, s32 n, Vec* table);
static u8 barriernSatelliteTo_Main(BattleUnit* unit, s32 n);

static s32 zanzou_count[5];
static s32 barriern_satellite_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 n, s32 type);
static s32 barriern_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 type);

static USER_FUNC(_check_satellite);
static USER_FUNC(barriern_satellite_zanzou);
static USER_FUNC(barriern_satellite_zanzou2);
static USER_FUNC(battleGetBarriernSatelliteInitPos);
static USER_FUNC(outSplineTableSet);
static void barriern_wawawa_get_next_target(s32* unitIdx, s32* partIdx);
static void barriern_wawawa_get_target(s32* unitIdx, s32* partIdx);
static USER_FUNC(barriern_wawawa_set_target);
static void outSplineTableSet_Sub(BattleUnit* unit, s32 n, Vec* table);
static USER_FUNC(barriernSatelliteToOutside);
static USER_FUNC(barriernSatelliteToInside);
static u8 barriernSatelliteTo_Main(BattleUnit* unit, s32 n);
static u8 barriernSatelliteTo_Init(BattleUnit* unit, s32 n, Vec* table);
static s32 barriern_satellite_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 n, s32 type);
static s32 barriern_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 type);
static USER_FUNC(barriern_zanzou3);
static USER_FUNC(barriern_zanzou2);
static USER_FUNC(barriern_zanzou);
extern BattleUnitKind unit_barriern_custom_satellite;

BattleUnitKind unit_barriern_custom;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static BattleUnitKindPart parts[11];
static StatusVulnerability regist;
static BattleWeapon weapon_wakka_attack;
static BattleWeapon weapon_wawawa_attack;
static BattleUnitSetup entry_barriern_satellite;
static PoseTableEntry pose_table[18];
static BattleDataEntry data_table[2];
static Vec splineTableIn1_1[5];
static Vec splineTableIn2_1[5];
static Vec splineTableIn2_2[5];
static Vec splineTableIn3_1[5];
static Vec splineTableIn3_2[5];
static Vec splineTableIn3_3[5];
static Vec splineTableIn4_1[5];
static Vec splineTableIn4_2[5];
static Vec splineTableIn4_3[5];
static Vec splineTableIn4_4[5];
static Vec splineTableOut1_1[5];
static Vec splineTableOut2_1[5];
static Vec splineTableOut2_2[5];
static Vec splineTableOut3_1[5];
static Vec splineTableOut3_2[5];
static Vec splineTableOut3_3[5];
static Vec splineTableOut4_1[5];
static Vec splineTableOut4_2[5];
static Vec splineTableOut4_3[5];
static Vec splineTableOut4_4[5];
static EvtWord init_event[143];
static EvtWord damage_event[17];
static EvtWord barriern_dmg_first_attack_pos[19];
static EvtWord unison_phase_event[190];
static EvtWord attack_event[106];
static EvtWord recovery_event[69];
static EvtWord wakka_attack_event[255];
static EvtWord wawawa_attack_event[548];
static EvtWord wawawa_attack_event_sub[87];
static EvtWord wawawa_attack_event_sub_no_last[10];
static EvtWord wawawa_attack_event_sub_last[93];
static EvtWord wait_event[116];

/** Unit data of the X-Yux: 10 HP, level 32; the battle starts it from init_event. */
BattleUnitKind unit_barriern_custom = {
    117,
    "btl_un_barriern_custom",
    10,
    0,
    1,
    1,
    32,
    0,
    0,
    70,
    5,
    50,
    9999,
    50,
    50,
    0,
    25,
    0.0f,
    0.0f,
    0.0f,
    0,
    -40,
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
    10.0f,
    10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    50.0f,
    50.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_BARRI_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_FLOATING,
    &regist,
    11,
    parts,
    init_event,
    data_table,
};

/** Defence of the X-Yux: 1 against every element. */
static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

/** Elemental reactions of the X-Yux: none, every element hurts it normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/**
 * Parts of the X-Yux: part 1 is its body, parts 2 to 6 are the five ghost rings drawn as afterimages while it
 * spins, and parts 7 to 11 are the rings it launches at targets (wakka, "ring", in the code; hidden until
 * used).
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_barriern_custom", "c_baria_c", 0.0f, 0.0f, 0.0f, 0.0f, 12.0f, 0.0f, 0.0f, 22.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, 0, pose_table},
    {2, "btl_un_barriern_custom", "c_baria_c", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {3, "btl_un_barriern_custom", "c_baria_c", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {4, "btl_un_barriern_custom", "c_baria_c", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {5, "btl_un_barriern_custom", "c_baria_c", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {6, "btl_un_barriern_custom", "c_baria_c", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {7, "btl_un_barriern_custom", "c_baria_c", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10, 10, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {8, "btl_un_barriern_custom", "c_baria_c", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10, 10, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {9, "btl_un_barriern_custom", "c_baria_c", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10, 10, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {10, "btl_un_barriern_custom", "c_baria_c", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10, 10, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {11, "btl_un_barriern_custom", "c_baria_c", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10, 10, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the X-Yux (percent, 100 is normal) in the demo builds: immune to sleep, stop,
 * dizzy, poison, confusion, electric, burn, freeze, fright and Gale Force; resists most statuses (10-10%).
 */
static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 100, 10, 100, 10, 10, 0, 0, 100, 10, 100, 100, 10};
#else
/**
 * Status vulnerability of the X-Yux (percent, 100 is normal) in the retail builds: immune to sleep, stop,
 * dizzy, poison, confusion, electric, burn, freeze, Tiny, Attack Down, Defense Down, allergy, fright, Gale
 * Force and Slow; resists instant KO (10%).
 */
static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 100, 0, 100, 0, 100, 0, 0, 0, 0, 100, 0, 100, 100, 10};
#endif

/**
 * Weapon data for the X-Yux's single-ring attack: 3 damage, one target, may inflict stop (100%, differs in the
 * demo).
 */
static BattleWeapon weapon_wakka_attack = {
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
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000, // targetWeightFlags
    0, 0, // sleepChance..sleepTime
#if VERSION <= VERSION_DEMO_JP
    100, // stopChance
#else
    80, // stopChance
#endif
    3, // stopTime
    0, 0, 0, 0, 0, 0, 0, 0, // dizzyChance..electricChance
    0, 0, 0, 0, 0, 0, 0, 0, // electricTime..sizeChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeTime..defChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // allergicChance..slowTime
    0, 0, 0, 0, 0, 0, 0, 0, // frightChance..hpRegenStrength
    0, 0, // fpRegenTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Weapon data for the X-Yux's combined ring attack: 2 damage, every target, may inflict stop (100%, differs
 * in the demo).
 */
static BattleWeapon weapon_wawawa_attack = {
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
    {2, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, // sleepChance..sleepTime
#if VERSION <= VERSION_DEMO_JP
    100, // stopChance
#else
    80, // stopChance
#endif
    3, // stopTime
    0, 0, 0, 0, 0, 0, 0, 0, // dizzyChance..electricChance
    0, 0, 0, 0, 0, 0, 0, 0, // electricTime..sizeChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeTime..defChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // allergicChance..slowTime
    0, 0, 0, 0, 0, 0, 0, 0, // frightChance..hpRegenStrength
    0, 0, // fpRegenTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Setup for the Mini-X-Yux the X-Yux spawns when the battle starts; it is placed off-stage and then moved
 * around the X-Yux.
 */
static BattleUnitSetup entry_barriern_satellite = {
    &unit_barriern_custom_satellite, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {1000.0f, 0.0f, 1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/** Pose table of the X-Yux: the animation each battle pose (idle, hurt, walk, attack and so on) plays. */
static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "S_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "S_1"},
    {39, "D_1"},
    {42, "R_1"},
    {41, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

/** Event table of the X-Yux: the First Strike reaction (barriern_dmg_first_attack_pos, tag 48). */
static BattleDataEntry data_table[] = {
    {48, barriern_dmg_first_attack_pos},
    {0, NULL},
};

/**
 * Path (five spline points) that Mini-Yux number 1 of 1 follows when it moves back in to its shield position
 * at the X-Yux.
 */
static Vec splineTableIn1_1[] = {
    {25.0f, 0.0f, 0.0f},
    {20.0f, -30.0f, -1.0f},
    {12.5f, -40.0f, -1.0f},
    {5.0f, -30.0f, -1.0f},
    {0.0f, 0.0f, -1.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 1 of 2 follows when it moves back in to its shield position
 * at the X-Yux.
 */
static Vec splineTableIn2_1[] = {
    {25.0f, 0.0f, 0.0f},
    {20.0f, -30.0f, -1.0f},
    {12.5f, -40.0f, -1.0f},
    {5.0f, -30.0f, -1.0f},
    {0.0f, 0.0f, -1.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 2 of 2 follows when it moves back in to its shield position
 * at the X-Yux.
 */
static Vec splineTableIn2_2[] = {
    {-25.0f, 0.0f, 0.0f},
    {-20.0f, 30.0f, -1.0f},
    {-12.5f, 30.0f, -1.0f},
    {-5.0f, 30.0f, -1.0f},
    {0.0f, 0.0f, -1.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 1 of 3 follows when it moves back in to its shield position
 * at the X-Yux.
 */
static Vec splineTableIn3_1[] = {
    {0.0f, 25.0f, 0.0f},
    {0.0f, 45.0f, -1.0f},
    {0.0f, 50.0f, -1.0f},
    {0.0f, 25.0f, -1.0f},
    {0.0f, 0.0f, -1.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 2 of 3 follows when it moves back in to its shield position
 * at the X-Yux.
 */
static Vec splineTableIn3_2[] = {
    {25.0f, -25.0f, 0.0f},
    {40.0f, -40.0f, -1.0f},
    {30.0f, -35.0f, -1.0f},
    {20.0f, -25.0f, -1.0f},
    {0.0f, 0.0f, -1.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 3 of 3 follows when it moves back in to its shield position
 * at the X-Yux.
 */
static Vec splineTableIn3_3[] = {
    {-25.0f, -25.0f, 0.0f},
    {-40.0f, -40.0f, -1.0f},
    {-30.0f, -35.0f, -1.0f},
    {-20.0f, -25.0f, -1.0f},
    {-0.0f, 0.0f, -1.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 1 of 4 follows when it moves back in to its shield position
 * at the X-Yux.
 */
static Vec splineTableIn4_1[] = {
    {25.0f, 25.0f, 0.0f},
    {30.0f, 35.0f, -1.0f},
    {40.0f, 45.0f, -1.0f},
    {20.0f, 25.0f, -1.0f},
    {0.0f, 0.0f, -1.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 2 of 4 follows when it moves back in to its shield position
 * at the X-Yux.
 */
static Vec splineTableIn4_2[] = {
    {-25.0f, 25.0f, 0.0f},
    {-30.0f, 35.0f, -1.0f},
    {-40.0f, 45.0f, -1.0f},
    {-20.0f, 25.0f, -1.0f},
    {0.0f, 0.0f, -1.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 3 of 4 follows when it moves back in to its shield position
 * at the X-Yux.
 */
static Vec splineTableIn4_3[] = {
    {25.0f, -25.0f, 0.0f},
    {30.0f, -35.0f, -1.0f},
    {40.0f, -45.0f, -1.0f},
    {20.0f, -25.0f, -1.0f},
    {0.0f, 0.0f, -1.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 4 of 4 follows when it moves back in to its shield position
 * at the X-Yux.
 */
static Vec splineTableIn4_4[] = {
    {-25.0f, -25.0f, 0.0f},
    {-30.0f, -35.0f, -1.0f},
    {-40.0f, -45.0f, -1.0f},
    {-20.0f, -25.0f, -1.0f},
    {-0.0f, 0.0f, -1.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 1 of 1 follows when it moves out to its outer position
 * around the X-Yux.
 */
static Vec splineTableOut1_1[] = {
    {0.0f, 0.0f, -1.0f},
    {-35.0f, -35.0f, -1.0f},
    {-40.0f, 0.0f, -1.0f},
    {30.0f, 40.0f, -1.0f},
    {25.0f, 0.0f, 0.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 1 of 2 follows when it moves out to its outer position
 * around the X-Yux.
 */
static Vec splineTableOut2_1[] = {
    {0.0f, 0.0f, -1.0f},
    {5.0f, 30.0f, -1.0f},
    {12.5f, 40.0f, -1.0f},
    {20.0f, 30.0f, -1.0f},
    {25.0f, 0.0f, 0.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 2 of 2 follows when it moves out to its outer position
 * around the X-Yux.
 */
static Vec splineTableOut2_2[] = {
    {0.0f, 0.0f, -1.0f},
    {-5.0f, -30.0f, -1.0f},
    {-12.5f, -40.0f, -1.0f},
    {-20.0f, -30.0f, -1.0f},
    {-25.0f, 0.0f, 0.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 1 of 3 follows when it moves out to its outer position
 * around the X-Yux.
 */
static Vec splineTableOut3_1[] = {
    {0.0f, 0.0f, -1.0f},
    {0.0f, 25.0f, -1.0f},
    {0.0f, 50.0f, -1.0f},
    {0.0f, 45.0f, -1.0f},
    {0.0f, 25.0f, 0.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 2 of 3 follows when it moves out to its outer position
 * around the X-Yux.
 */
static Vec splineTableOut3_2[] = {
    {0.0f, 0.0f, -1.0f},
    {25.0f, -20.0f, -1.0f},
    {45.0f, -30.0f, -1.0f},
    {30.0f, -25.0f, -1.0f},
    {25.0f, -25.0f, 0.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 3 of 3 follows when it moves out to its outer position
 * around the X-Yux.
 */
static Vec splineTableOut3_3[] = {
    {0.0f, 0.0f, -1.0f},
    {-25.0f, -20.0f, -1.0f},
    {-45.0f, -30.0f, -1.0f},
    {-30.0f, -25.0f, -1.0f},
    {-25.0f, -25.0f, 0.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 1 of 4 follows when it moves out to its outer position
 * around the X-Yux.
 */
static Vec splineTableOut4_1[] = {
    {0.0f, 0.0f, -1.0f},
    {25.0f, 20.0f, -1.0f},
    {45.0f, 30.0f, -1.0f},
    {30.0f, 25.0f, -1.0f},
    {25.0f, 25.0f, 0.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 2 of 4 follows when it moves out to its outer position
 * around the X-Yux.
 */
static Vec splineTableOut4_2[] = {
    {0.0f, 0.0f, -1.0f},
    {-25.0f, 20.0f, -1.0f},
    {-45.0f, 30.0f, -1.0f},
    {-30.0f, 25.0f, -1.0f},
    {-25.0f, 25.0f, 0.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 3 of 4 follows when it moves out to its outer position
 * around the X-Yux.
 */
static Vec splineTableOut4_3[] = {
    {0.0f, 0.0f, -1.0f},
    {25.0f, -20.0f, -1.0f},
    {45.0f, -30.0f, -1.0f},
    {30.0f, -25.0f, -1.0f},
    {25.0f, -25.0f, 0.0f},
};

/**
 * Path (five spline points) that Mini-Yux number 4 of 4 follows when it moves out to its outer position
 * around the X-Yux.
 */
static Vec splineTableOut4_4[] = {
    {0.0f, 0.0f, -1.0f},
    {-25.0f, -20.0f, -1.0f},
    {-45.0f, -30.0f, -1.0f},
    {-30.0f, -25.0f, -1.0f},
    {-25.0f, -25.0f, 0.0f},
};

/**
 * Battle init for the X-Yux: registers its wait, unison-phase, attack, damage and confusion events,
 * scales its body part to 1.0, then spawns its 4 Mini-X-Yux satellites (unit_barriern_custom_satellite),
 * stores their unit ids in unit work 4 onward, links each back to the parent
 * and places them around it with battleGetBarriernSatelliteInitPos;
 * finally builds the out-spline tables for the current satellite count.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventUnisonPhase, BTL_UNIT_SELF, PTR(unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetPartsScale, BTL_UNIT_SELF, 1, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_FLOAT | UNIT_FLAG_FLOAT_ACTIVE)
    SET_VALUE(LW(0), UW_BARRIERN_CUSTOM_SATELLITE_1)
    LOOP(4)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, LW(0), -1)
        ADD(LW(0), 1)
    END_LOOP
    SET_VALUE(LW(6), 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BARRIERN_CUSTOM_SATELLITE_COUNT, LW(7))
    LABEL(0)
    IF_INT_LESS(LW(6), LW(7))
        CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(5))
        SET_VALUE(LW(8), LW(6))
        ADD(LW(8), UW_BARRIERN_CUSTOM_SATELLITE_1)
        CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_barriern_satellite), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, LW(8), LW(3))
        CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(5))
        CALL(btlevtcmd_SetUnitWork, LW(3), 1, 1)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(battleGetBarriernSatelliteInitPos, BTL_UNIT_SELF, LW(7), LW(6), LW(10), LW(11), LW(12))
        ADD(LW(0), LW(10))
        ADD(LW(1), LW(11))
        ADD(LW(2), LW(12))
        CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetScale, LW(3), FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
        ADD(LW(6), 1)
        GOTO(0)
    END_IF
    LABEL(10)
    CALL(outSplineTableSet, BTL_UNIT_SELF, LW(7))
    RETURN
EVT_END()

/** Damage event for the X-Yux: flashes the body white, then runs the default damage handler (btldefaultevt_Damage). */
static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_SetRGB, BTL_UNIT_SELF, 1, 255, 255, 255)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Data-table event 48, run when the battle opens with Mario's or his partner's First Strike on the X-Yux:
 * raises it to y=20 and waits for the attack to end.
 */
static EVT_BEGIN(barriern_dmg_first_attack_pos)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 20)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

/**
 * Switches on the afterimage blur on every living satellite of the X-Yux (unit work 4 onward)
 * and sets the blur part attribute 0x4000000.
 */
static EVT_BEGIN(satellite_blur_on)
    SET_VALUE(LW(2), UW_BARRIERN_CUSTOM_SATELLITE_1)
    LOOP(4)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(2), LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
            CALL(btlevtcmd_SetPartsBlur, LW(3), LW(4), 255, 255, 255, 255, 255, 255, 255, 100, 0)
            CALL(btlevtcmd_OnPartsAttribute, LW(3), LW(4), PART_ATTR_BLUR)
        END_IF
        ADD(LW(2), 1)
    END_LOOP
    RETURN
EVT_END()

/** Clears the blur part attribute 0x4000000 on every living satellite of the X-Yux. */
static EVT_BEGIN(satellite_blur_off)
    SET_VALUE(LW(2), UW_BARRIERN_CUSTOM_SATELLITE_1)
    LOOP(4)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(2), LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
            CALL(btlevtcmd_OffPartsAttribute, LW(3), LW(4), PART_ATTR_BLUR)
        END_IF
        ADD(LW(2), 1)
    END_LOOP
    RETURN
EVT_END()

/**
 * Script function: plays the Yux's afterimage effect of the barrier ring on the unit args[0] (type 0: the five
 * ghost- ring parts 2 to 6 start large at 1.7 to 4.5 times and shrink in toward the body over 36 frames
 * while fading in to alpha 64).
 */
static USER_FUNC(barriern_zanzou) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 scales[5] = {1.7f, 2.4f, 3.1f, 3.8f, 4.5f};

    return barriern_zanzou_sub(isFirstCall, unit, scales, 0);
}

/**
 * Script function: the second afterimage type on the unit args[0]:
 * the ghost rings (parts 2 to 6) expand outward from the body over 8 frames and fade out from alpha 64 to 0.
 */
static USER_FUNC(barriern_zanzou2) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 scales[5] = {1.7f, 2.4f, 3.1f, 3.8f, 4.5f};

    return barriern_zanzou_sub(isFirstCall, unit, scales, 1);
}

/**
 * Script function: the third afterimage type on the unit args[0]:
 * like barriern_zanzou2 but expanding over 36 frames.
 */
static USER_FUNC(barriern_zanzou3) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 scales[5] = {1.7f, 2.4f, 3.1f, 3.8f, 4.5f};

    return barriern_zanzou_sub(isFirstCall, unit, scales, 2);
}

/** Inline helper: interpolates from start to end with the easing mode over cur of total steps (intplGetValue). */
static inline f32 intpl_ff(f32 start, f32 end, s32 mode, s32 cur, s32 total) {
    return intplGetValue(mode, start, end, cur, total);
}

/**
 * Runs one frame of the Yux afterimage effect of the given type (0 shrinking in, 1 and 2 expanding out):
 * scales the body part and the five ghost rings (parts 2 to 6, offset in depth by 0.5 each)
 * and fades them with the frame count kept in zanzou_count[0].
 * Returns EVT_RETURN_BLOCK until the effect has run its frames,
 * then restores the body scale and hides the rings.
 */
static s32 barriern_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 type) {
    f32 start[5];
    f32 end[5];
    f32 x;
    f32 y;
    f32 z;
    BattleUnitPart* part;
    s32 frames;
    f32 scale;
    f32 ofs;
    u8 alphaStart;
    u8 alphaEnd;
    s32 mode = 4;
    s32 i;
    s32 j;

    switch (type) {
        case 0:
            scale = 0.75f;
            frames = 36;
            for (i = 0; i < 5; i++) {
                start[i] = scales[i];
                end[i] = scale;
            }
            ofs = 0.5f;
            alphaStart = 0;
            alphaEnd = 64;
            mode = 4;
            break;
        case 1:
        case 2:
            scale = 1.0f;
            frames = 8;
            for (i = 0; i < 5; i++) {
                start[i] = scale;
                end[i] = scales[i];
            }
            ofs = -0.5f;
            alphaStart = 64;
            alphaEnd = 0;
            mode = 1;
            break;
    }
    if (type == 2) {
        frames = 36;
    }
    if (isFirstCall) {
        zanzou_count[0] = 0;
        BtlUnit_GetPos(unit, &x, &y, &z);
        BtlUnit_SetPartsScale(BtlUnit_GetPartsPtr(unit, 1), 1.0f, 1.0f, 1.0f);
        for (i = 2, j = 0; i <= 6; i++, j++) {
            part = BtlUnit_GetPartsPtr(unit, i);
            BtlUnit_SetPartsPos(part, x, y, i * ofs + z);
            BtlUnit_SetPartsScale(part, start[j], start[j], 1.0f);
            part->color.a = alphaEnd;
            part->attributes &= ~PART_ATTR_HIDDEN;
        }
    }
    part = BtlUnit_GetPartsPtr(unit, 1);
    {
        f32 s = intplGetValue(mode, 1.0f, scale, zanzou_count[0], frames);
        BtlUnit_SetPartsScale(part, s, s, 1.0f);
    }
    for (i = 2, j = 0; i <= 6; i++, j++) {
        f32 s;

        part = BtlUnit_GetPartsPtr(unit, i);
        s = intpl_ff(start[j], end[j], mode, zanzou_count[0], frames);
        BtlUnit_SetPartsScale(part, s, s, 1.0f);
        part->color.a = intplGetValue(0, alphaStart, alphaEnd, zanzou_count[0], frames);
    }
    if (zanzou_count[0] >= frames) {
        part = BtlUnit_GetPartsPtr(unit, 1);
        BtlUnit_SetPartsScale(part, 1.0f, 1.0f, 1.0f);
        part->color.a = 255;
        for (i = 2; i <= 6; i++) {
            BtlUnit_GetPartsPtr(unit, i)->attributes |= PART_ATTR_HIDDEN;
        }
        return EVT_RETURN_DONE;
    }
    zanzou_count[0]++;
    return EVT_RETURN_BLOCK;
}

/**
 * Script function: the shrinking-in afterimage (type 0) for the satellite number args[1] of the unit args[0],
 * looked up from the unit's work[4 + n].
 */
static USER_FUNC(barriern_satellite_zanzou) {
    EvtWord* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 n = evtGetValue(event, args[1]);
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit = BattleGetUnitPtr(wp, id);
    BattleUnit* sat;
    f32 scales[5] = {1.7f, 2.4f, 3.1f, 3.8f, 4.5f};

    sat = BattleGetUnitPtr(wp, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_1 + n]);
    return barriern_satellite_zanzou_sub(isFirstCall, sat, scales, n, 0);
}

/** Script function: the expanding afterimage (type 1) for the satellite number args[1] of the unit args[0]. */
static USER_FUNC(barriern_satellite_zanzou2) {
    EvtWord* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 n = evtGetValue(event, args[1]);
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit = BattleGetUnitPtr(wp, id);
    BattleUnit* sat;
    f32 scales[5] = {1.7f, 2.4f, 3.1f, 3.8f, 4.5f};

    sat = BattleGetUnitPtr(wp, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_1 + n]);
    return barriern_satellite_zanzou_sub(isFirstCall, sat, scales, n, 1);
}

/**
 * Runs one frame of a Mini-X-Yux's afterimage effect (type 0 shrinking in over the effect's frames,
 * type 1 expanding out over 8) with its frame count in zanzou_count[n + 1];
 * the same ghost-ring scaling and fading as barriern_zanzou_sub.
 */
static s32 barriern_satellite_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 n, s32 type) {
    f32 start[5];
    f32 end[5];
    f32 x;
    f32 y;
    f32 z;
    BattleUnitPart* part;
    s32 frames;
    f32 scale;
    f32 ofs;
    u8 alphaStart;
    u8 alphaEnd;
    s32 mode = 4;
    s32 i;
    s32 j;

    switch (type) {
        case 0:
            scale = 0.75f;
            frames = 36;
            for (i = 0; i < 5; i++) {
                start[i] = scales[i];
                end[i] = scale;
            }
            ofs = 0.5f;
            alphaStart = 0;
            alphaEnd = 64;
            mode = 4;
            break;
        case 1:
            scale = 1.0f;
            frames = 8;
            for (i = 0; i < 5; i++) {
                start[i] = scale;
                end[i] = scales[i];
            }
            ofs = -0.5f;
            alphaStart = 64;
            alphaEnd = 0;
            mode = 1;
            break;
    }
    if (isFirstCall) {
        zanzou_count[(s32)(n + 1)] = 0;
        BtlUnit_GetPos(unit, &x, &y, &z);
        BtlUnit_SetPartsScale(BtlUnit_GetPartsPtr(unit, 1), 1.0f, 1.0f, 1.0f);
        for (i = 2, j = 0; i <= 6; i++, j++) {
            part = BtlUnit_GetPartsPtr(unit, i);
            BtlUnit_SetPartsPos(part, x, y, i * ofs + z);
            BtlUnit_SetPartsScale(part, start[j], start[j], 1.0f);
            BtlUnit_SetPartsRotate(part, 0.0f, 0.0f, 0.0f);
            part->color.a = alphaStart;
            BtlUnit_SetAnim(part, "Z_2");
            part->attributes &= ~PART_ATTR_HIDDEN;
        }
    }
    part = BtlUnit_GetPartsPtr(unit, 1);
    {
        f32 s = intplGetValue(4, 1.0f, scale, zanzou_count[0], frames);
        BtlUnit_SetPartsScale(part, s, s, 1.0f);
    }
    for (i = 2, j = 0; i <= 6; i++, j++) {
        f32 s;

        part = BtlUnit_GetPartsPtr(unit, i);
        s = intplGetValue(mode, start[j], end[j], zanzou_count[(s32)(n + 1)], frames);
        BtlUnit_SetPartsScale(part, s, s, 1.0f);
        part->color.a = intplGetValue(0, alphaStart, alphaEnd, zanzou_count[(s32)(n + 1)], frames);
    }
    if (zanzou_count[(s32)(n + 1)] >= frames) {
        part = BtlUnit_GetPartsPtr(unit, 1);
        BtlUnit_SetPartsScale(part, 1.0f, 1.0f, 1.0f);
        part->color.a = 255;
        for (i = 2; i <= 6; i++) {
            BtlUnit_GetPartsPtr(unit, i)->attributes |= PART_ATTR_HIDDEN;
        }
        return EVT_RETURN_DONE;
    }
    zanzou_count[(s32)(n + 1)]++;
    return EVT_RETURN_BLOCK;
}

/**
 * Unison phase script of the X-Yux, run before the player's phase:
 * skipped on turn 1 and when the X-Yux cannot act, and does nothing if all 4 satellites are alive.
 * After a short random delay it pulls its satellites into its body (SFX_ENM_BARRI_SPLIT1),
 * spawns 2 replacement Mini-X-Yux, sends the satellites back out to their orbit positions (SFX_ENM_BARRI_SPLIT2)
 * and restores the wait event.
 */
static EVT_BEGIN(unison_phase_event)
    CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_SELF)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_get_turn, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(evt_sub_random, 10, LW(0))
    WAIT_FRAMES(LW(0))
    SET_VALUE(LW(0), 0)
    SET_VALUE(LW(1), UW_BARRIERN_CUSTOM_SATELLITE_1)
    LOOP(4)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(1), LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            ADD(LW(0), 1)
        END_IF
        ADD(LW(1), 1)
    END_LOOP
    IF_INT_GREATER_OR_EQUAL(LW(0), 4)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BARRI_ATTACK9"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(barriern_zanzou3, BTL_UNIT_SELF)
    CALL_CHILD(satellite_blur_on)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BARRIERN_CUSTOM_SATELLITE_COUNT, LW(1))
    IF_INT_GREATER_OR_EQUAL(LW(1), 1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BARRI_SPLIT1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_IF
    CALL(barriernSatelliteToInside, BTL_UNIT_SELF, LW(1))
    CALL_CHILD(satellite_blur_off)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(4))
    SET_VALUE(LW(1), UW_BARRIERN_CUSTOM_SATELLITE_1)
    SET_VALUE(LW(5), 0)
    LOOP(4)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(1), LW(2))
        IF_INT_EQUAL(LW(2), -1)
            CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_barriern_satellite), 0)
            CALL(btlevtcmd_AddPos, LW(3), 0, 0, -1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, LW(1), LW(3))
            CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(4))
            ADD(LW(0), 1)
            ADD(LW(5), 1)
            IF_INT_GREATER_OR_EQUAL(LW(5), 2)
                BREAK_LOOP
            END_IF
        END_IF
        ADD(LW(1), 1)
    END_LOOP
    WAIT_FRAMES(5)
    CALL_CHILD(satellite_blur_on)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BARRI_SPLIT2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(barriernSatelliteToOutside, BTL_UNIT_SELF, LW(0))
    WAIT_FRAMES(60)
    CALL_CHILD(satellite_blur_off)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BARRIERN_CUSTOM_SATELLITE_COUNT, LW(0))
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Attack script of the X-Yux: if battle flag 2 is set it always uses the ring attack (wakka_attack_event);
 * otherwise it lets an enemy item be used if one is ready.
 * When all 4 satellites can act it does the combined attack wawawa_attack_event, otherwise the ring attack.
 * The 1-in-100 roll that would choose recovery_event can never fail (the roll is below 100),
 * so recovery_event is not reached from here.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_SetRGB, BTL_UNIT_SELF, 1, 255, 255, 255)
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(wakka_attack_event)
        RETURN
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(_check_satellite)
    SET_VALUE(LW(0), 0)
    SET_VALUE(LW(1), UW_BARRIERN_CUSTOM_SATELLITE_1)
    LOOP(4)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(1), LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_CheckActStatus, LW(3), LW(2))
            IF_INT_NOT_EQUAL(LW(2), 0)
                CALL(btlevtcmd_CheckStatus, LW(3), STATUS_CONFUSE, LW(2))
                IF_INT_EQUAL(LW(2), 0)
                    ADD(LW(0), 1)
                END_IF
            END_IF
        END_IF
        ADD(LW(1), 1)
    END_LOOP
    IF_INT_EQUAL(LW(0), 4)
        CALL_CHILD(wawawa_attack_event)
    ELSE
        SET_VALUE(LW(0), 100)
        ADD(LW(0), 0)
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(1))
        IF_INT_LESS(LW(1), 100)
            CALL_CHILD(wakka_attack_event)
        ELSE
            CALL_CHILD(recovery_event)
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * The X-Yux heals itself: the camera zooms on it, it plays the S_3 pose for 2 seconds,
 * calls btlevtcmd_RecoverHp with amount 0 and shows the recovery effect above its head.
 */
static EVT_BEGIN(recovery_event)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_3"))
    WAIT_FRAMES(120)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_RecoverHp, BTL_UNIT_SELF, 1, 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
    ADD(LW(6), 30)
    ADD(LW(7), 10)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, LW(5), LW(6), LW(7), 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(30)
    RETURN
EVT_END()

/**
 * Starts the target's avoid reaction (type 38, 39 or 40) for the pre-check result in LW(5) (3, 6 or 2),
 * so the target reacts as the ring passes it.
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
 * Flight of a launched ring (wakka) when it misses:
 * the ring part (LW(15)) appears at the unit launching it (LW(12)),
 * pulses while it crosses the stage past the target (slow wide pulses for the single ring attack,
 * fast ones with the blur during the combined attack) and triggers the target's avoid reaction
 * when it passes it; the part is moved off-screen at the end.
 */
static EVT_BEGIN(wakka_attack_common_event_no_hit)
    // The single-ring attack shows a plain ring; the combined attack shows a blurred, glowing one.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BARRIERN_CUSTOM_COMBINED_ATTACK, LW(6))
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_BLUR)
    ELSE
        CALL(btlevtcmd_SetPartsBlur, BTL_UNIT_SELF, LW(15), 255, 255, 255, 255, 255, 255, 255, 100, 0)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_BLUR)
    END_IF
    // The ring (part LW(15)) appears at the launching unit while the Yux plays pose A_5.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, LW(15), STRING("Z_3"))
    CALL(btlevtcmd_GetPos, LW(12), LW(6), LW(7), LW(8))
    ADD(LW(8), 1)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(15), LW(6), LW(7), LW(8))
    CALL(btlevtcmd_CheckPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_HIDDEN, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_HIDDEN)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_5"))
    // A side event watches the ring and makes the target dodge as the ring passes its position.
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(0))
            IF_INT_EQUAL(LW(0), -1)
                CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, LW(15), LW(0), LW(1), LW(2))
                CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
                IF_INT_LESS_OR_EQUAL(LW(0), LW(6))
                    CALL_CHILD(start_avoid)
                    BREAK_LOOP
                END_IF
            ELSE
                CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, LW(15), LW(0), LW(1), LW(2))
                CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
                IF_INT_GREATER_OR_EQUAL(LW(0), LW(6))
                    CALL_CHILD(start_avoid)
                    BREAK_LOOP
                END_IF
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    // The ring flies across the stage past the target, pulsing: slow wide pulses for the single-ring attack.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BARRIERN_CUSTOM_COMBINED_ATTACK, LW(6))
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
        CALL(btlevtcmd_GetStageSize, LW(6), EVT_NULLPTR, EVT_NULLPTR)
        MULTIPLY(LW(6), 1)
        CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(0))
        MULTIPLY(LW(6), LW(0))
        SUBTRACT(LW(7), 5)
        CALL(btlevtcmd_SetPartsScale, BTL_UNIT_SELF, LW(15), 1, 0, 1)
        BEGIN_SIBLING_EVENT
            LOOP(0)
                LOOP(10)
                    CALL(btlevtcmd_AddPartsScale, BTL_UNIT_SELF, LW(15), 0, FLOAT(0.125f), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                LOOP(10)
                    CALL(btlevtcmd_AddPartsScale, BTL_UNIT_SELF, LW(15), 0, FLOAT(-0.125f), 0)
                    WAIT_FRAMES(1)
                END_LOOP
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(15), 0, 4, 0)
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(6), LW(7), LW(8), 0, -1)
    ELSE
        // Combined attack: the ring pulses faster and flies quicker.
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
        CALL(btlevtcmd_GetStageSize, LW(6), EVT_NULLPTR, EVT_NULLPTR)
        MULTIPLY(LW(6), 1)
        CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(0))
        MULTIPLY(LW(6), LW(0))
        SUBTRACT(LW(7), 5)
        CALL(btlevtcmd_SetPartsScale, BTL_UNIT_SELF, LW(15), 1, 0, 1)
        BEGIN_SIBLING_EVENT
            LOOP(0)
                LOOP(5)
                    CALL(btlevtcmd_AddPartsScale, BTL_UNIT_SELF, LW(15), 0, FLOAT(0.25f), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                LOOP(5)
                    CALL(btlevtcmd_AddPartsScale, BTL_UNIT_SELF, LW(15), 0, FLOAT(-0.25f), 0)
                    WAIT_FRAMES(1)
                END_LOOP
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(15), 0, 7, 0)
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(6), LW(7), LW(8), 0, -1)
        // At the end the ring is moved off-screen.
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(15), 0, -1000, 0)
    END_IF
    RETURN
EVT_END()

/**
 * Flight of a launched ring (wakka) when it hits:
 * the ring part (LW(15)) appears at the unit launching it (LW(12)),
 * pulses while it flies to the target's hit position and stops there (the caller applies the damage).
 */
static EVT_BEGIN(wakka_attack_common_event_hit)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BARRIERN_CUSTOM_COMBINED_ATTACK, LW(6))
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_BLUR)
    ELSE
        CALL(btlevtcmd_SetPartsBlur, BTL_UNIT_SELF, LW(15), 255, 255, 255, 255, 255, 255, 255, 100, 0)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_BLUR)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, LW(15), STRING("Z_3"))
    CALL(btlevtcmd_GetPos, LW(12), LW(6), LW(7), LW(8))
    ADD(LW(8), 1)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(15), LW(6), LW(7), LW(8))
    CALL(btlevtcmd_CheckPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_HIDDEN, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_HIDDEN)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_5"))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BARRIERN_CUSTOM_COMBINED_ATTACK, LW(6))
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_SetPartsScale, BTL_UNIT_SELF, LW(15), 1, 0, 1)
        BEGIN_SIBLING_EVENT
            LOOP(0)
                LOOP(10)
                    CALL(btlevtcmd_AddPartsScale, BTL_UNIT_SELF, LW(15), 0, FLOAT(0.125f), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                LOOP(10)
                    CALL(btlevtcmd_AddPartsScale, BTL_UNIT_SELF, LW(15), 0, FLOAT(-0.125f), 0)
                    WAIT_FRAMES(1)
                END_LOOP
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
        CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(15), 0, 4, 0)
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(6), LW(7), LW(8), 0, -1)
    ELSE
        CALL(btlevtcmd_SetPartsScale, BTL_UNIT_SELF, LW(15), 1, 0, 1)
        BEGIN_SIBLING_EVENT
            LOOP(0)
                LOOP(5)
                    CALL(btlevtcmd_AddPartsScale, BTL_UNIT_SELF, LW(15), 0, FLOAT(0.25f), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                LOOP(5)
                    CALL(btlevtcmd_AddPartsScale, BTL_UNIT_SELF, LW(15), 0, FLOAT(-0.25f), 0)
                    WAIT_FRAMES(1)
                END_LOOP
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
        CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(15), 0, 7, 0)
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(6), LW(7), LW(8), 0, -1)
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(15), 0, -1000, 0)
    END_IF
    RETURN
EVT_END()

/**
 * Resolves one ring against a target (LW(3) unit, LW(4) part, LW(9) weapon): pre-checks the damage;
 * on a miss or guard (results 2, 3, 4 and 6) it flies the ring past with wakka_attack_common_event_no_hit,
 * on a hit (result 1) it records the target as hit,
 * flies the ring in and applies the damage (with damage flag 256 when LW(10) is 1).
 * The ring part is hidden afterwards.
 */
static EVT_BEGIN(damage_check_event_sub)
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
    END_SWITCH
    LABEL(90)
    CALL_CHILD(wakka_attack_common_event_no_hit)
    GOTO(98)
    LABEL(91)
    SET_VALUE(LW(13), 0)
    SET_VALUE(LW(14), 5)
    LOOP(0)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, 1, LW(13), LW(5))
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, 1, LW(14), LW(6))
        IF_INT_EQUAL(LW(3), LW(5))
            IF_INT_EQUAL(LW(4), LW(6))
                ADD(LW(13), 10)
                CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, LW(13), 1)
                BREAK_LOOP
            END_IF
        END_IF
        ADD(LW(13), 1)
        ADD(LW(14), 1)
    END_LOOP
    CALL_CHILD(wakka_attack_common_event_hit)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    IF_INT_EQUAL(LW(10), 1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 0, LW(5))
    END_IF
    GOTO(98)
    LABEL(98)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(15), 0, -1000, 0)
    RETURN
EVT_END()

/**
 * Ring attack (wakka) of the X-Yux: picks a target, declares the attack, spins up with afterimages,
 * plays its attack poses (A_1 to A_4), launches the ring at the target through damage_check_event_sub
 * and spins back; with no valid target it does nothing (or acts flustered when confused).
 */
static EVT_BEGIN(wakka_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_wakka_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_wakka_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BARRIERN_CUSTOM_COMBINED_ATTACK, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 0, LW(3))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 5, LW(4))
    SET_VALUE(LW(9), PTR(&weapon_wakka_attack))
    SET_VALUE(LW(10), 1)
    SET_VALUE(LW(12), -2)
    SET_VALUE(LW(15), 7)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_wakka_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_wakka_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(14))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(14))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BARRI_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(barriern_zanzou, BTL_UNIT_SELF)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BARRI_ATTACK9"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(barriern_zanzou2, BTL_UNIT_SELF)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    SET_VALUE(LW(0), 6)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(14))
    MULTIPLY(LW(0), LW(14))
    LOOP(10)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(0), 0)
    END_LOOP
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BARRI_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1"))
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2"))
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3"))
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(10)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_4"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BARRI_ATTACK3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BARRI_ATTACK7"), EVT_NULLPTR, 0, LW(0))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 7, 15, LW(0))
    CALL_CHILD(damage_check_event_sub)
    CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, 7, 15, LW(0))
    CALL(evt_snd_sfxoff, LW(0))
    SET_VALUE(LW(0), -6)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(14))
    MULTIPLY(LW(0), LW(14))
    LOOP(10)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(0), 0)
    END_LOOP
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Plays both afterimage effects (barriern_satellite_zanzou and zanzou2) for satellite number LW(0) during the
 * combined attack.
 */
static EVT_BEGIN(wawawa_attack_event_satellite_blur)
    CALL(barriern_satellite_zanzou, BTL_UNIT_SELF, LW(0))
    CALL(barriern_satellite_zanzou2, BTL_UNIT_SELF, LW(0))
    RETURN
EVT_END()

/**
 * Combined attack (wawawa) of the X-Yux with its satellites:
 * picks a first target, lets barriern_wawawa_set_target assign a target to every ring,
 * declares an all-target attack, spins the body and satellites with afterimages,
 * then fires a ring from the X-Yux and from each satellite (wawawa_attack_event_sub) and waits
 * until all of them have finished before spinning back.
 */
static EVT_BEGIN(wawawa_attack_event)
    // Choose a first target for the combined attack.
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_wawawa_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_wawawa_attack), LW(3), LW(4))
    // No valid target: a confused unit is flustered, otherwise the turn is skipped.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BARRIERN_CUSTOM_COMBINED_ATTACK, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BARRIERN_CUSTOM_RINGS_DONE, 0)
    // Every ring gets its own target: the Yux and each Mini-Yux are assigned targets, kept in the body part's
    // work slots.
    CALL(barriern_wawawa_set_target, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), LW(6), LW(7), LW(8), LW(9))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 0, LW(0))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 1, LW(2))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 2, LW(4))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 3, LW(6))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 4, LW(8))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 5, LW(1))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 6, LW(3))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 7, LW(5))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 8, LW(7))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 9, LW(9))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 10, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 11, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 12, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 13, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 14, 0)
    // The camera pulls back, the attack is declared on all targets and the guard window opens.
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_wawawa_attack))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_wawawa_attack))
    // The Yux turns to face its first target.
    CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, 1, 0, LW(3))
    CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, 1, 5, LW(4))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // It spins up with afterimages while the Mini-Yux join in.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BARRI_ATTACK5"), EVT_NULLPTR, 0, EVT_NULLPTR)
    SET_VALUE(LW(0), 0)
    LOOP(4)
        SPAWN_EVENT(wawawa_attack_event_satellite_blur)
        ADD(LW(0), 1)
        WAIT_FRAMES(10)
    END_LOOP
    CALL(barriern_zanzou, BTL_UNIT_SELF)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BARRI_ATTACK10"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(barriern_zanzou2, BTL_UNIT_SELF)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BARRI_ATTACK6"), EVT_NULLPTR, 0, EVT_NULLPTR)
    // Charge-up: the Yux holds its pose (F_1) while the Mini-Yux flash (F_2).
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("F_1"))
    WAIT_FRAMES(20)
    SET_VALUE(LW(11), UW_BARRIERN_CUSTOM_SATELLITE_1)
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(LW(11), 8)
            BREAK_LOOP
        END_IF
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(11), LW(12))
        CALL(btlevtcmd_GetBodyId, LW(12), LW(13))
        CALL(btlevtcmd_AnimeChangePose, LW(12), LW(13), STRING("F_2"))
        ADD(LW(11), 1)
    END_LOOP
    WAIT_FRAMES(20)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    SET_VALUE(LW(11), UW_BARRIERN_CUSTOM_SATELLITE_1)
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(LW(11), 8)
            BREAK_LOOP
        END_IF
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(11), LW(12))
        CALL(btlevtcmd_SetRotate, LW(12), 0, 0, 0)
        ADD(LW(11), 1)
    END_LOOP
    // They all spin together for a moment, then settle back into their stay poses.
    SET_VALUE(LW(0), 6)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(14))
    MULTIPLY(LW(0), LW(14))
    LOOP(10)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(0), 0)
        SET_VALUE(LW(11), UW_BARRIERN_CUSTOM_SATELLITE_1)
        LOOP(0)
            IF_INT_GREATER_OR_EQUAL(LW(11), 8)
                BREAK_LOOP
            END_IF
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(11), LW(12))
            CALL(btlevtcmd_AddRotate, LW(12), 0, LW(0), 0)
            ADD(LW(11), 1)
        END_LOOP
    END_LOOP
    SET_VALUE(LW(11), UW_BARRIERN_CUSTOM_SATELLITE_1)
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(LW(11), 8)
            BREAK_LOOP
        END_IF
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(11), LW(12))
        CALL(btlevtcmd_GetBodyId, LW(12), LW(13))
        CALL(btlevtcmd_AnimeChangePose, LW(12), LW(13), STRING("S_2"))
        ADD(LW(11), 1)
    END_LOOP
    // The Yux plays its attack poses A_1 to A_4 before the rings are launched.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BARRI_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1"))
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2"))
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3"))
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(10)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_4"))
    // The Yux launches its ring, then each Mini-Yux launches its own, one after another.
    SET_VALUE(LW(12), -2)
    SET_VALUE(LW(13), 0)
    SET_VALUE(LW(14), 5)
    SET_VALUE(LW(15), 7)
    SPAWN_EVENT(wawawa_attack_event_sub)
    WAIT_FRAMES(30)
    SET_VALUE(LW(11), UW_BARRIERN_CUSTOM_SATELLITE_1)
    ADD(LW(13), 1)
    ADD(LW(14), 1)
    ADD(LW(15), 1)
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(LW(11), 8)
            BREAK_LOOP
        END_IF
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(11), LW(12))
        SPAWN_EVENT(wawawa_attack_event_sub)
        WAIT_FRAMES(20)
        ADD(LW(11), 1)
        ADD(LW(13), 1)
        ADD(LW(14), 1)
        ADD(LW(15), 1)
    END_LOOP
    // It waits until every ring has finished its flight.
    LOOP(0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BARRIERN_CUSTOM_RINGS_DONE, LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 5)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_FRAMES(10)
    // The Mini-Yux return to their orbits and the group spins back the other way.
    CALL(_check_satellite)
    SET_VALUE(LW(0), -6)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(14))
    MULTIPLY(LW(0), LW(14))
    LOOP(10)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(0), 0)
        SET_VALUE(LW(11), UW_BARRIERN_CUSTOM_SATELLITE_1)
        LOOP(0)
            IF_INT_GREATER_OR_EQUAL(LW(11), 8)
                BREAK_LOOP
            END_IF
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(11), LW(12))
            CALL(btlevtcmd_AddRotate, LW(12), 0, LW(0), 0)
            ADD(LW(11), 1)
        END_LOOP
    END_LOOP
    LABEL(99)
    // It returns to its normal facing and goes back to waiting.
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * One ring of the combined attack: plays the ring sounds,
 * looks through the target list to decide whether this is the last ring aimed at its target
 * (wawawa_attack_event_sub_last) or an earlier one (wawawa_attack_event_sub_no_last),
 * then counts itself finished in unit work 2.
 */
static EVT_BEGIN(wawawa_attack_event_sub)
    CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, 1, LW(13), LW(3))
    CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, 1, LW(14), LW(4))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BARRI_ATTACK4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BARRI_ATTACK8"), EVT_NULLPTR, 0, LW(0))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(15), 15, LW(0))
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(LW(13), 3)
            CALL_CHILD(wawawa_attack_event_sub_last)
            BREAK_LOOP
        END_IF
        ADD(LW(13), 1)
        ADD(LW(14), 1)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, 1, LW(13), LW(5))
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, 1, LW(14), LW(6))
        IF_INT_EQUAL(LW(3), LW(5))
            IF_INT_EQUAL(LW(4), LW(6))
                CALL_CHILD(wawawa_attack_event_sub_no_last)
                BREAK_LOOP
            END_IF
        END_IF
    END_LOOP
    CALL(btlevtcmd_AddUnitWork, BTL_UNIT_SELF, UW_BARRIERN_CUSTOM_RINGS_DONE, 1)
    CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(15), 15, LW(0))
    CALL(evt_snd_sfxoff, LW(0))
    RETURN
EVT_END()

/**
 * A ring of the combined attack that is not the last one aimed at its target: resolves it with
 * damage_check_event_sub and the wawawa weapon but without DAMAGE_FLAG_LAST_HIT (LW(10) = 0), so a hit deals
 * damage and is recorded, but only the target's last ring (wawawa_attack_event_sub_last) can knock it out
 * or inflict status.
 */
static EVT_BEGIN(wawawa_attack_event_sub_no_last)
    SET_VALUE(LW(9), PTR(&weapon_wawawa_attack))
    SET_VALUE(LW(10), 0)
    CALL_CHILD(damage_check_event_sub)
    RETURN
EVT_END()

/**
 * The last ring of the combined attack on a target:
 * if an earlier ring of that target was recorded as a hit it flies this ring in,
 * applies the damage and hides the ring; otherwise it resolves like a normal ring (damage_check_event_sub).
 */
static EVT_BEGIN(wawawa_attack_event_sub_last)
    SET_VALUE(LW(13), 0)
    SET_VALUE(LW(14), 5)
    LOOP(0)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, 1, LW(13), LW(5))
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, 1, LW(14), LW(6))
        IF_INT_EQUAL(LW(3), LW(5))
            IF_INT_EQUAL(LW(4), LW(6))
                ADD(LW(13), 10)
                CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, 1, LW(13), LW(0))
                BREAK_LOOP
            END_IF
        END_IF
        ADD(LW(13), 1)
        ADD(LW(14), 1)
    END_LOOP
    IF_INT_EQUAL(LW(0), 1)
        CALL_CHILD(wakka_attack_common_event_hit)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_wawawa_attack))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_wawawa_attack), 256, LW(5))
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(15), 0, -1000, 0)
        WAIT_FRAMES(20)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_BLUR)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_HIDDEN)
    ELSE
        SET_VALUE(LW(9), PTR(&weapon_wawawa_attack))
        SET_VALUE(LW(10), 1)
        CALL_CHILD(damage_check_event_sub)
    END_IF
    RETURN
EVT_END()

/**
 * Idle script of the X-Yux: keeps the barrier in sync with its satellites (_check_satellite),
 * loops the idle pose, and every 0.5 to 2.5 seconds plays its short S_3 pose while it can act
 * and has no bad status.
 */
static EVT_BEGIN(wait_event)
    CALL(_check_satellite)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    SET_VALUE(LW(11), UW_BARRIERN_CUSTOM_SATELLITE_1)
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(LW(11), 8)
            BREAK_LOOP
        END_IF
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(11), LW(12))
        IF_INT_NOT_EQUAL(LW(12), -1)
            CALL(btlevtcmd_SetUnitWork, LW(12), 1, 1)
        END_IF
        ADD(LW(11), 1)
    END_LOOP
    BEGIN_SIBLING_EVENT
        SET_VALUE(LW(1), 255)
        SET_VALUE(LW(2), 255)
        SET_VALUE(LW(3), 255)
        SET_VALUE(LW(4), -8)
        LABEL(0)
        CALL(_check_satellite, LW(0))
        WAIT_FRAMES(1)
        GOTO(0)
    END_SIBLING_EVENT
    LABEL(1)
    CALL(evt_sub_random, 120, LW(0))
    ADD(LW(0), 30)
    WAIT_FRAMES(LW(0))
    CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_CONFUSE, LW(0))
        CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_DIZZY, LW(1))
        CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_POISON, LW(2))
        OR(LW(0), LW(1))
        OR(LW(0), LW(2))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_3"))
            WAIT_FRAMES(180)
            CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
        END_IF
    END_IF
    GOTO(1)
    RETURN
EVT_END()

/**
 * Prepares the move of satellite n of the Yux along the spline in table:
 * allocates a SatelliteSpline (5 points, frame 0),
 * builds its spline tables and records the table in the satellite's body part work[2].
 * Returns FALSE if the Yux has no satellite n.
 */
static u8 barriernSatelliteTo_Init(BattleUnit* unit, s32 n, Vec* table) {
    SatelliteSpline* sp;

    if (unit->work[UW_BARRIERN_CUSTOM_SATELLITE_1 + n] == -1) {
        return FALSE;
    }
    sp = BTL_ALLOC(sizeof(SatelliteSpline));
    unit->work[UW_BARRIERN_CUSTOM_SPLINE_1 + n] = (EvtWord)sp;
    sp->numPoints = 5;
    sp->points = table;
    sp->frame = 0;
    spline_maketable(5, sp->points, sp->knots, sp->curvature);
    BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_1 + n]), 1)->work[2] = (EvtWord)table;
    return TRUE;
}

/**
 * Moves satellite n one frame along its spline (60 frames, eased) around the Yux's position,
 * mirrored by the Yux's facing; sets both its position and home position.
 * Returns TRUE while moving and FALSE when done (and frees the spline) or if there is no satellite.
 */
static u8 barriernSatelliteTo_Main(BattleUnit* unit, s32 n) {
    SatelliteSpline* sp;
    BattleUnit* sat;
    Vec upos;
    Vec pos;

    if (unit->work[UW_BARRIERN_CUSTOM_SATELLITE_1 + n] == -1) {
        return FALSE;
    }
    sp = (SatelliteSpline*)unit->work[UW_BARRIERN_CUSTOM_SPLINE_1 + n];
    if (sp == NULL) {
        return FALSE;
    }
    if (sp->frame >= 60) {
        if (sp != NULL) {
            BTL_FREE(sp);
            unit->work[UW_BARRIERN_CUSTOM_SPLINE_1 + n] = 0;
        }
        return FALSE;
    }
    spline_getvalue(&pos, intplGetValue(4, 0.0f, 1.0f, sp->frame, 60), sp->numPoints, sp->points, sp->knots, sp->curvature);
    sat = BattleGetUnitPtr(_battleWorkPointer, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_1 + n]);
    if (sat == NULL) {
        return FALSE;
    }
    BtlUnit_GetPos(unit, &upos.x, &upos.y, &upos.z);
    BtlUnit_SetPos(sat, upos.x + pos.x * unit->faceDirection, upos.y + pos.y, upos.z + pos.z);
    BtlUnit_SetHomePos(sat, upos.x + pos.x * unit->faceDirection, upos.y + pos.y, upos.z + pos.z);
    sp->frame++;
    return TRUE;
}

/**
 * Script function: moves the Yux's satellites from their outer positions to the inner (shield) positions,
 * picking for each satellite the Inside spline matching its current Out spline.
 * Blocks until all satellites have arrived.
 */
static USER_FUNC(barriernSatelliteToInside) {
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 num = evtGetValue(event, args[1]);
    BattleUnit* unit;
    u8 moving;
    s32 i;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        for (i = 0; i < 4; i++) {
            if (unit->work[UW_BARRIERN_CUSTOM_SATELLITE_1 + i] != -1) {
                EvtWord table = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_1 + i]), 1)->work[2];

                if (table == (EvtWord)splineTableOut1_1) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn1_1);
                }
                if (table == (EvtWord)splineTableOut2_1) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn2_1);
                }
                if (table == (EvtWord)splineTableOut2_2) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn2_2);
                }
                if (table == (EvtWord)splineTableOut3_1) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn3_1);
                }
                if (table == (EvtWord)splineTableOut3_2) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn3_2);
                }
                if (table == (EvtWord)splineTableOut3_3) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn3_3);
                }
                if (table == (EvtWord)splineTableOut4_1) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn4_1);
                }
                if (table == (EvtWord)splineTableOut4_2) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn4_2);
                }
                if (table == (EvtWord)splineTableOut4_3) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn4_3);
                }
                if (table == (EvtWord)splineTableOut4_4) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn4_4);
                }
            }
        }
    }
    moving = FALSE;
    for (i = 0; i < 4; i++) {
        if (barriernSatelliteTo_Main(unit, i) == TRUE) {
            moving = TRUE;
        }
    }
    return moving == FALSE ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

/**
 * Script function: moves args[1] satellites (1 to 4) of the Yux args[0] out to their outer positions along the
 * splineTableOut tables. Blocks until all satellites have arrived.
 */
static USER_FUNC(barriernSatelliteToOutside) {
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 num = evtGetValue(event, args[1]);
    BattleUnit* unit;
    u8 moving;
    s32 i;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        switch (num) {
            case 1:
                i = 0;
                while (TRUE) {
                    if (barriernSatelliteTo_Init(unit, i, splineTableOut1_1) == TRUE) {
                        break;
                    }
                    i++;
                }
                break;
            case 2:
                i = 0;
                while (TRUE) {
                    if (barriernSatelliteTo_Init(unit, i, splineTableOut2_1) == TRUE) {
                        break;
                    }
                    i++;
                }
                i++;
                while (TRUE) {
                    if (barriernSatelliteTo_Init(unit, i, splineTableOut2_2) == TRUE) {
                        break;
                    }
                    i++;
                }
                break;
            case 3:
                i = 0;
                while (TRUE) {
                    if (barriernSatelliteTo_Init(unit, i, splineTableOut3_1) == TRUE) {
                        break;
                    }
                    i++;
                }
                i++;
                while (TRUE) {
                    if (barriernSatelliteTo_Init(unit, i, splineTableOut3_2) == TRUE) {
                        break;
                    }
                    i++;
                }
                i++;
                while (TRUE) {
                    if (barriernSatelliteTo_Init(unit, i, splineTableOut3_3) == TRUE) {
                        break;
                    }
                    i++;
                }
                break;
            case 4:
                i = 0;
                while (TRUE) {
                    if (barriernSatelliteTo_Init(unit, i, splineTableOut4_1) == TRUE) {
                        break;
                    }
                    i++;
                }
                i++;
                while (TRUE) {
                    if (barriernSatelliteTo_Init(unit, i, splineTableOut4_2) == TRUE) {
                        break;
                    }
                    i++;
                }
                i++;
                while (TRUE) {
                    if (barriernSatelliteTo_Init(unit, i, splineTableOut4_3) == TRUE) {
                        break;
                    }
                    i++;
                }
                i++;
                while (TRUE) {
                    if (barriernSatelliteTo_Init(unit, i, splineTableOut4_4) == TRUE) {
                        break;
                    }
                    i++;
                }
                break;
            default:
                return EVT_RETURN_DONE;
        }
    }
    moving = FALSE;
    for (i = 0; i < 4; i++) {
        if (barriernSatelliteTo_Main(unit, i) == TRUE) {
            moving = TRUE;
        }
    }
    return moving == FALSE ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

/**
 * Script function: tags the first args[1] satellites (1 to 4) of the unit args[0] with their outer spline tables
 * (splineTableOut1_1 to 4_4) by storing them in the satellite's body part work[2].
 */
static USER_FUNC(outSplineTableSet) {
    EvtWord* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part;

    switch (evtGetValue(event, args[1])) {
        case 1:
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_1]), 1);
            part->work[2] = (EvtWord)splineTableOut1_1;
            break;
        case 2:
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_1]), 1);
            part->work[2] = (EvtWord)splineTableOut2_1;
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_2]), 1);
            part->work[2] = (EvtWord)splineTableOut2_2;
            break;
        case 3:
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_1]), 1);
            part->work[2] = (EvtWord)splineTableOut3_1;
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_2]), 1);
            part->work[2] = (EvtWord)splineTableOut3_2;
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_3]), 1);
            part->work[2] = (EvtWord)splineTableOut3_3;
            break;
        case 4:
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_1]), 1);
            part->work[2] = (EvtWord)splineTableOut4_1;
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_2]), 1);
            part->work[2] = (EvtWord)splineTableOut4_2;
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_3]), 1);
            part->work[2] = (EvtWord)splineTableOut4_3;
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_4]), 1);
            part->work[2] = (EvtWord)splineTableOut4_4;
            break;
    }
    return EVT_RETURN_DONE;
}

/** Stores the spline table in the body part work[2] of satellite n of the unit. */
static void outSplineTableSet_Sub(BattleUnit* unit, s32 n, Vec* table) {
    BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[UW_BARRIERN_CUSTOM_SATELLITE_1 + n]), 1)->work[2] = (EvtWord)table;
}

/**
 * Script function: collects the targets the wawawa attack can hit (the weapon's target list)
 * and picks five at random, with repeats; returns the five (unit, part) pairs in the script's argument
 * variables.
 */
static USER_FUNC(barriern_wawawa_set_target) {
    EvtWord* args = event->args;
    s32 unitIdx[10];
    s32 partIdx[10];
    s32 i;
    s32 num;

    i = 0;
    _battleWorkPointer->weaponTargets.currentTarget = 0;
    barriern_wawawa_get_target(&unitIdx[0], &partIdx[0]);
    while (TRUE) {
        if (unitIdx[i] == -1) {
            num = i;
            break;
        }
        i++;
        barriern_wawawa_get_next_target(&unitIdx[i], &partIdx[i]);
    }
    for (i = 0; i < 5; i++) {
        s32 r = irand(num);
        evtSetValue(event, *args++, unitIdx[r]);
        evtSetValue(event, *args++, partIdx[r]);
    }
    return EVT_RETURN_DONE;
}

/** Returns the unit and part index of the current target of the weapon's target list. */
static void barriern_wawawa_get_target(s32* unitIdx, s32* partIdx) {
    BattleWorkWeaponTargets* wt = &_battleWorkPointer->weaponTargets;
    BattleWorkTarget* target = &wt->targets[wt->targetIndices[wt->currentTarget]];

    *unitIdx = target->unitIdx;
    *partIdx = target->partIdx;
}

/**
 * Steps to the next target in the weapon's target list and returns its unit and part index,
 * or -1 and 0 when the list is used up.
 */
static void barriern_wawawa_get_next_target(s32* unitIdx, s32* partIdx) {
    BattleWorkWeaponTargets* wt = &_battleWorkPointer->weaponTargets;

    wt->currentTarget++;
    if (wt->currentTarget < wt->numTargets) {
        BattleWorkTarget* target = &wt->targets[wt->targetIndices[wt->currentTarget]];
        *unitIdx = target->unitIdx;
        *partIdx = target->partIdx;
    } else {
        *unitIdx = -1;
        *partIdx = 0;
    }
}

/**
 * Script function: updates the Yux's barrier from its satellites.
 * If no satellite (work[4], work[5]) is left, the barrier breaks (SFX_ENM_BARRI_BARRIER_BREAK1, glass shards,
 * damage immunity of the body removed) and args[0] = 0;
 * while one is left, the body is immune to damage and status and the barrier effect (work[3]) follows the unit,
 * args[0] = 1.
 */
static USER_FUNC(_check_satellite) {
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    EvtWord* args = event->args;
    BattleUnitPart* part;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    BOOL alive;
    s32 j;

    alive = FALSE;
    if (unit == NULL) {
        return EVT_RETURN_DONE;
    }
    for (i = 4; i < 8; i++) {
        if (unit->work[i] != -1) {
            if (BattleGetUnitPtr(_battleWorkPointer, unit->work[i]) != NULL) {
                alive = TRUE;
            } else {
                unit->work[i] = -1;
            }
        }
    }
    if (!alive) {
        part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
        if (part->attributes & PART_ATTR_IMMUNE_TO_DAMAGE_OR_STATUS) {
            effDelete((EffectEntry*)unit->work[UW_BARRIERN_CUSTOM_BARRIER_EFFECT]);
            unit->work[UW_BARRIERN_CUSTOM_BARRIER_EFFECT] = 0;
            BtlUnit_snd_se(unit, "SFX_ENM_BARRI_BARRIER_BREAK1", 0xF1194D80, 0);
            BtlUnit_GetPos(unit, &x, &y, &z);
            for (j = 0; j < 20; j++) {
                s32 w = BtlUnit_GetWidth(unit) + 15;
                s32 h = BtlUnit_GetHeight(unit) + 15;
                s32 dx = irand(w) - w / 2;
                s32 dy = irand(h) - h / 2;

                effGlassN64Entry(2, 60, x + dx, y + dy, z, 1.0f);
            }
        }
        part->attributes &= ~PART_ATTR_IMMUNE_TO_DAMAGE_OR_STATUS;
        evtSetValue(event, args[0], 0);
    } else {
        part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
        if (!(part->attributes & PART_ATTR_IMMUNE_TO_DAMAGE_OR_STATUS)) {
            f32 px;
            f32 py;
            f32 pz;

            BtlUnit_snd_se(unit, "SFX_ENM_BARRI_BARRIER1", 0xF1194D80, 0);
            BtlUnit_GetPos(unit, &px, &py, &pz);
            unit->work[UW_BARRIERN_CUSTOM_BARRIER_EFFECT] = (EvtWord)effSyuryouEntry(1, 1000, 0.0f, -1000.0f, 0.0f);
        }
        part->attributes |= PART_ATTR_IMMUNE_TO_DAMAGE_OR_STATUS;
        evtSetValue(event, args[0], 1);
        if (unit->work[UW_BARRIERN_CUSTOM_BARRIER_EFFECT] != 0) {
            f32* ud = ((EffectEntry*)unit->work[UW_BARRIERN_CUSTOM_BARRIER_EFFECT])->userdata;

            BtlUnit_GetPos(unit, &x, &y, &z);
            ud[1] = x;
            ud[2] = y - 32.0f * unit->sizeMultiplier;
            ud[3] = 10.0f + z;
            ud[4] = 1.8f * unit->sizeMultiplier;
        }
    }
    return EVT_RETURN_DONE;
}

/**
 * Script function: returns the starting offset of satellite index args[2]
 * when the Yux has args[1] satellites (1 to 4 laid out as a fixed pattern 25 units apart,
 * mirrored by the facing direction) in the variables args[3] to args[5] as x, y and z.
 */
static USER_FUNC(battleGetBarriernSatelliteInitPos) {
    EvtWord* args = event->args;
    BattleUnit* unit;
    s32 max;
    s32 index;
    s32 id;
    s32 x;
    s32 y;
    s32 z;
    s32 i;
    s32 j;
    static const Vec VecData[] = {
        // 1 satellite
        {25.0f, 0.0f, 0.0f},
        // 2 satellites
        {25.0f, 0.0f, 0.0f},
        {-25.0f, 0.0f, 0.0f},
        // 3 satellites
        {0.0f, 25.0f, 0.0f},
        {25.0f, -25.0f, 0.0f},
        {-25.0f, -25.0f, 0.0f},
        // 4 satellites
        {25.0f, 25.0f, 0.0f},
        {-25.0f, 25.0f, 0.0f},
        {25.0f, -25.0f, 0.0f},
        {-25.0f, -25.0f, 0.0f},
    };
    const Vec* p;
    BattleWork* wp = _battleWorkPointer;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    max = evtGetValue(event, args[1]);
    index = evtGetValue(event, args[2]);
    x = args[3];
    y = args[4];
    z = args[5];
    p = VecData;
    for (i = 0; i < max; i++) {
        for (j = 0; j < i; j++) {
            p++;
        }
    }
    for (j = 0; j < index; j++) {
        p++;
    }
    evtSetValue(event, x, (s32)(p->x * unit->faceDirection));
    evtSetValue(event, y, (s32)p->y);
    evtSetValue(event, z, (s32)p->z);
    return EVT_RETURN_DONE;
}
