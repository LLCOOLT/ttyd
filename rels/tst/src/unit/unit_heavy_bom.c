// Battle unit Bulky Bob-omb (`heavy_bom`): tst.rel's copy of rels/dou/src/unit/unit_heavy_bom.c.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_unit.h"
#include "driver/animdrv.h"
#include "string.h"
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
static void _fire_point_callback(BattleUnitPart* part, s32 group);

BattleUnitKind unit_heavy_bom;
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
 * Script helper: hooks _fire_point_callback onto the Bob-omb's body animation and hides part 2, the spark model,
 * which is then drawn only at the fuse.
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

/**
 * Unit kind of Bulky Bob-omb: 6 max HP, level 22. The battle engine reads it when the unit spawns:
 * size, offsets, sounds, status vulnerability, parts, init script and event table.
 */
BattleUnitKind unit_heavy_bom = {
    92,
    "btl_un_heavy_bom",
    6,
    0,
    1,
    1,
    22,
    0,
#if VERSION <= VERSION_DEMO_US
    3,
    70,
    3,
#else
    4,
    70,
    0,
#endif
    40,
    9999,
    54,
    70,
    7,
    70,
    0.0f,
    35.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    27.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    27.0f,
    0.0f,
    0.0f,
    27.0f,
    45.5f,
    0.0f,
    0.0f,
    35.0f,
    0.0f,
    54.0f,
    70.0f,
    0,
    0,
    0,
    2,
    100,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_HEAVYB_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    2,
    parts,
    init_event,
    data_table,
};

/** Attack data of Bulky Bob-omb's b super explosion attack: base damage 2, 100% accuracy. */
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

/** Attack data of Bulky Bob-omb's b guard attack: no damage, 100% accuracy; may inflict defense change 100%. */
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

/** Attack data of Bulky Bob-omb's b guard 2 attack: no damage, 100% accuracy; may inflict attack change 100%. */
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

/** Attack data of Bulky Bob-omb's b guard 3 attack: no damage, 100% accuracy. */
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

/**
 * Defence of Bulky Bob-omb per element (normal, fire, ice, explosion, electric),
 * subtracted from each hit: 1 against every element.
 */
static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

/** Element reactions of Bulky Bob-omb: none, every element hits normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
/**
 * Status vulnerability of Bulky Bob-omb (the demos), as the percent chance a status takes hold:
 * immune to Poison; always hit by Electric, Burn, Huge, Attack Up, Defense Up, Fast, Dodgy and Invisible;
 * otherwise Sleep 65, Stop 50, Dizzy 70, Confuse 70, Freeze 70, Tiny 70, Attack Down 70, Defense Down 70,
 * Allergic 70, Fright 80, Gale Force 20, Slow 70 and instant KO 95.
 */
static StatusVulnerability regist = {65, 50, 70, 0, 70, 150, 100, 70, 100, 70, 100, 70, 100, 70, 70, 80, 20, 100, 70, 100, 100, 95};
#else
/**
 * Status vulnerability of Bulky Bob-omb (the final versions), as the percent chance a status takes hold:
 * immune to Poison; always hit by Electric, Burn, Freeze, Huge, Attack Up, Defense Up, Fast,
 * Dodgy and Invisible; otherwise Sleep 90, Stop 75, Dizzy 70, Confuse 70, Tiny 80, Attack Down 80,
 * Defense Down 95, Allergic 70, Fright 80, Gale Force 20, Slow 70 and instant KO 95.
 */
static StatusVulnerability regist = {90, 75, 70, 0, 70, 150, 100, 100, 100, 80, 100, 80, 100, 95, 70, 80, 20, 100, 70, 100, 100, 95};
#endif

/**
 * Pose table of Bulky Bob-omb's fuse at length 3, not yet lit:
 * 16 poses, animations such as N_1, Y_1, K_1, X_1.
 */
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

/**
 * Pose table of Bulky Bob-omb's fuse at length 3, burning: 16 poses, animations such as N_1, Y_1, K_1,
 * X_1.
 */
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

/**
 * Pose table of Bulky Bob-omb's fuse at length 2, not yet lit:
 * 16 poses, animations such as N_2, Y_2, K_2, X_2.
 */
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

/**
 * Pose table of Bulky Bob-omb's fuse at length 2, burning: 16 poses, animations such as N_2, Y_2, K_2,
 * X_2.
 */
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

/**
 * Pose table of Bulky Bob-omb's fuse at length 1, not yet lit:
 * 16 poses, animations such as N_3, Y_3, K_3, X_3.
 */
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

/**
 * Pose table of Bulky Bob-omb's fuse at length 1, burning: 16 poses, animations such as N_3, Y_3, K_3,
 * X_3.
 */
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

/**
 * Pose table of Bulky Bob-omb's fuse at length 0, burning: 16 poses, animations such as N_4, Y_4, K_4,
 * X_4.
 */
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

/**
 * Pose table of Bulky Bob-omb's fuse at length 0, not yet lit:
 * 16 poses, animations such as N_4, Y_4, K_4, X_4.
 */
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

/**
 * Pose table of Bulky Bob-omb's fuse burning down one step, from length 3 to 2:
 * 13 poses, animations such as B_4, B_1, B_7, B_10.
 */
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

/**
 * Pose table of Bulky Bob-omb's fuse burning down one step, from length 2 to 1:
 * 13 poses, animations such as B_5, B_2, B_8, B_11.
 */
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

/**
 * Pose table of Bulky Bob-omb's fuse burning down one step, from length 1 to 0:
 * 13 poses, animations such as B_6, B_3, B_9, B_12.
 */
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

/**
 * Event table of Bulky Bob-omb: maps event tags to the scripts that react to them (dead_event and
 * explosion_event); tag 0 ends it.
 */
static BattleDataEntry data_table[] = {
    {49, dead_event},
    {52, explosion_event},
    {0, NULL},
};

/**
 * Sound cues of Bulky Bob-omb's animations: for each of its 9 animation names,
 * the sound effect that plays with it (SFX_ENM_HEAVYB_WAIT3).
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

/**
 * Body parts of Bulky Bob-omb: 2 parts (model c_heavy); the first is the body.
 * Each part names its defence tables and pose table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_heavy_bom", "c_heavy", 0.0f, 0.0f, 0.0f, 15.0f, 50.0f, 0.0f, 0.0f, 65.0f, 0.0f, 65, 70, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table_3},
    {2, "ヘビーボム", "c_heavy", 0.0f, 80.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 15, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_NO_SHADOW, 0, pose_table_3},
};

/**
 * Init script of the Bulky Bob-omb: installs the wait, phase,
 * attack and damage handlers (confusion uses the default Confuse script),
 * sets its work values (0 = fuse lit flag 0, 1 = fuse length 3, 2 = fuse sound -1, 3 = guard cycle 0),
 * poses part 2 as F_1 (the fuse), sets the pose sound table and the draw callback, and starts the wait event.
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
 * Damage handler of the Bulky Bob-omb.
 * If it is frozen with its fuse lit, the fuse is put out (sound stopped, flag cleared,
 * pose table for the remaining fuse length restored).
 * A knock-out hit by fire, explosion, electric or one of the counter damage codes (24, 25, 27, 46, 50, 52, 54)
 * makes it explode instead of dying normally (pose type 29, then dead_event);
 * anything else runs the default damage script.
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
 * Phase script run after the player's turn: if its fuse is lit, it burns one step.
 * With no fuse left it plays K_4 and queues the explosion reaction (52);
 * otherwise it plays the fuse sound and the pose table that shortens the fuse by one (3 to 2, 2 to 1, 1 to 0),
 * waits 40 frames, lowers the fuse length in unit work 1 and installs the matching burning pose table.
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
 * Attack script of the Bulky Bob-omb: it does no damage itself.
 * The first time it lights its fuse (G_n pose for the current fuse length, fuse and light sounds,
 * unit work 0 = 1).
 * Afterwards it just holds the G_n pose and cycles through its three guard weapons (weapon_heavy_bomb_guard, _2,
 * _3) with a self check.
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

/** Idle script: sets the standard waiting pose from the unit's pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Death script of the Bulky Bob-omb: stops the fuse sound, then if the killing blow was fire, explosion,
 * electric or one of the counter damage codes it queues the explosion reaction (52);
 * otherwise it runs the shared death script (subsetevt_dead_core).
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
 * The Bulky Bob-omb's big explosion (weapon_heavy_bomb_super_explosion):
 * stops the fuse sound, shakes the camera, spawns the bomb effects around the stage, clears the fog,
 * and applies the explosion to every target in turn (avoid check, then damage),
 * then runs the shared death script and removes the unit.
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
#if VERSION <= VERSION_DEMO_US
    MULTIPLY(LW(5), LW(6))
#else
    MULTIPLY_FLOAT(LW(5), LW(6))
#endif
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
 * Animation draw callback: when the fuse is lit (work[0] != 0),
 * draws the fuse's spark shape (pPlaneShape3 of part 2) at the locator picked by the fuse stage in work[1]
 * (locator11 down to locator8).
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
