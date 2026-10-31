// unit_kamec_red: Red Magikoopa with its clone (bunsin), battle unit.

#include "battle/battle_unit.h"
#include "eff/n64/eff_magic1_n64.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "manager/evtmgr_cmd.h"
#include "string.h"
#include "system.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"
#include "eff/n64/eff_pokopi_pcharge_n64.h"
#include "eff/n64/eff_thunderflare_n64.h"

// Unit work slots of the Red Magikoopa.
enum {
    UW_KAMEC_RED_FLYING = 0,       // nonzero while it flies on its broom; clones copy it
    UW_KAMEC_RED_IS_CLONE = 1,     // 1 for a clone made by its clone magic, 0 for the real one
    UW_KAMEC_RED_KILL_CLONES = 2,  // 1 when the real one is hit with clones out: they vanish after the damage
    UW_KAMEC_RED_VANISHING = 3,    // 1 once a clone has started fading out (bunsin_kill_event)
    UW_KAMEC_RED_STAFF_EFFECT = 4, // the wand-tip effect while casting (EffectEntry*, eff_staff1 and eff_staff2)
    UW_KAMEC_RED_MAGIC_EFFECT = 5, // the magic shot effect (EffectEntry*, eff_magic)
};

static USER_FUNC(eff_magic);
static USER_FUNC(kamec_copy_status);
static USER_FUNC(kamec_get_bunsin);
static USER_FUNC(kamec_get_live_num);
static USER_FUNC(eff_magic_get_posX);
static USER_FUNC(eff_staff2);
static USER_FUNC(eff_staff1);
static USER_FUNC(kamec_shuffle);

BattleUnitKind unit_kamec_red;
BattleUnitKind unit_kamec_red_bunsin;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static StatusVulnerability regist_bunsin;
static BattleDataEntry data_table[5];
static BattleDataEntry data_table_bunsin[3];
static BattleUnitKindPart parts[2];
static BattleWeapon weapon_kamec_attack_magic;
static BattleWeapon weapon_kamec_dekadeka_magic;
static BattleWeapon weapon_kamec_biribiri_magic;
static BattleWeapon weapon_kamec_trans_magic;
static BattleWeapon weapon_kamec_katikati_magic;
static BattleWeapon weapon_kamec_recover_magic;
static BattleWeapon weapon_kamec_all_recover_magic;
static BattleUnitSetup entry_kamec;
static EvtWord init_event[22];
static EvtWord init_event2[87];
static EvtWord damage_event[66];
static EvtWord kamec_subset_bunsin_all_kill[68];
static EvtWord kamec_subset_dead_event[203];
static EvtWord kamec_subset_blow_dead_event[78];
static EvtWord avoid_miss_event[16];
static EvtWord bunsin_kill_event[37];
static EvtWord dmg_fall_event[159];
static EvtWord dmg_first_attack_pos[19];
static EvtWord attack_event[296];
static EvtWord attack_magic_event[325];
static EvtWord attack_magic_event_sub_no_hit[45];
static EvtWord attack_magic_event_sub_hit[30];
static EvtWord dekadeka_magic_event[7];
static EvtWord katikati_magic_event[7];
static EvtWord biribiri_magic_event[7];
static EvtWord trans_magic_event[7];
static EvtWord recover_magic_event[142];
static EvtWord all_recover_magic_event[180];
static EvtWord bunsin_magic_event[160];
#if VERSION <= VERSION_DEMO_JP
static EvtWord spawn_event[62];
#else
static EvtWord spawn_event[66];
#endif
static EvtWord wait_event[55];

/**
 * Script helper: arg0 = Magikoopa unit; arg1 receives the current x offset of its magic shot effect (stored in
 * unit work 5).
 */
static USER_FUNC(eff_magic_get_posX) {
    EvtWord* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);

    evtSetFloat(event, args[1], ((EffMagic1N64Work*)((EffectEntry*)unit->work[UW_KAMEC_RED_MAGIC_EFFECT])->userdata)->offset.x);
    return EVT_RETURN_DONE;
}

/**
 * Unit data of the Red Magikoopa: 7 HP and level 17, with its parts, status vulnerability, init event and
 * event data table.
 */
BattleUnitKind unit_kamec_red = {
    49,
    "btl_un_kamec_red",
    7,
    0,
    1,
    1,
    17,
    0,
    2,
    70,
    2,
    50,
    9999,
    42,
    42,
    0,
    42,
    0.0f,
    21.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    0.0f,
    21.0f,
    27.3f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    42.0f,
    42.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_KAMEKU_DAMAGED1",
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

/**
 * Unit data of the clone a Red Magikoopa conjures up: 7 HP and level 0, with its parts, status
 * vulnerability, init event and event data table.
 */
BattleUnitKind unit_kamec_red_bunsin = {
    50,
    "btl_un_kamec_red_bunsin",
    7,
    0,
    1,
    1,
    0,
    0,
    0,
    70,
    0,
    50,
    9999,
    42,
    42,
    0,
    42,
    0.0f,
    21.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    0.0f,
    21.0f,
    27.3f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    42.0f,
    42.0f,
    0,
    0,
    0,
    2,
    0,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_KAMEKU_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_NO_DAMAGE_NUMBER,
    &regist,
    2,
    parts,
    init_event,
    data_table_bunsin,
};

/**
 * Defense of the Red Magikoopa against normal, fire, ice, explosion and electric attacks: none, so it
 * takes full damage from every element.
 */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Damage-type reactions of the Red Magikoopa: none, so every element hurts it normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Red Magikoopa (both early demos), as the percent chance each status takes hold:
 * resists 13 statuses (down to 40% of the normal chance).
 */
static StatusVulnerability regist = {70, 70, 60, 100, 60, 100, 100, 60, 100, 50, 100, 50, 100, 50, 50, 40, 70, 100, 60, 100, 100, 95};
#else
/**
 * Status vulnerability of the Red Magikoopa (the retail releases), as the percent chance each status takes
 * hold: resists 13 statuses (down to 70% of the normal chance).
 */
static StatusVulnerability regist = {70, 75, 80, 100, 70, 100, 100, 70, 100, 90, 100, 90, 100, 95, 80, 70, 80, 100, 80, 100, 100, 95};
#endif

/** Status vulnerability of the Red Magikoopa for its clones: immune to every status effect. */
static StatusVulnerability regist_bunsin = {0};

/**
 * Pose table of the Red Magikoopa: maps each battle pose (idle, hurt, attacking and so on) to its
 * animation, named KMR_*.
 */
static PoseTableEntry pose_table[] = {
    {1, "KMR_N_1"},
    {2, "KMR_Y_1"},
    {9, "KMR_Y_1"},
    {5, "KMR_K_1"},
    {4, "KMR_X_1"},
    {3, "KMR_X_1"},
    {BTL_POSE_NORMAL, "KMR_S_1"},
    {29, "KMR_Q_1"},
    {30, "KMR_Q_1"},
    {31, "KMR_S_1"},
    {BTL_POSE_DAMAGE, "KMR_D_1"},
    {BTL_POSE_RUN, "KMR_R_1"},
    {BTL_POSE_WALK, "KMR_W_1"},
    {BTL_POSE_DANGER, "KMR_X_1"},
    {BTL_POSE_PERIL, "KMR_X_1"},
    {BTL_POSE_TALK, "KMR_T_1"},
    {BTL_POSE_STAY_DEFAULT, "KMR_S_1"},
};

/**
 * Pose table of the Red Magikoopa while it is flying: maps each battle pose (idle, hurt, attacking and so
 * on) to its animation, named KMR_*.
 */
static PoseTableEntry pose_table_sky[] = {
    {1, "KMR_N_2"},
    {2, "KMR_Y_2"},
    {9, "KMR_Y_2"},
    {5, "KMR_K_2"},
    {4, "KMR_X_2"},
    {3, "KMR_X_2"},
    {BTL_POSE_NORMAL, "KMR_S_2"},
    {29, "KMR_Q_2"},
    {30, "KMR_Q_2"},
    {31, "KMR_S_2"},
    {BTL_POSE_DAMAGE, "KMR_D_2"},
    {BTL_POSE_RUN, "KMR_R_2"},
    {BTL_POSE_WALK, "KMR_W_2"},
    {BTL_POSE_DANGER, "KMR_X_2"},
    {BTL_POSE_PERIL, "KMR_X_2"},
    {BTL_POSE_TALK, "KMR_T_2"},
    {BTL_POSE_STAY_DEFAULT, "KMR_S_2"},
};

/**
 * Event data table of the Red Magikoopa: scripts that replace the standard handling for its defeat (tag
 * 49), being blown away (tag 58) and an attack missing it (tag 46).
 */
static BattleDataEntry data_table[] = {
    {49, kamec_subset_dead_event},
    {58, kamec_subset_blow_dead_event},
    {46, avoid_miss_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/**
 * Event data table of the Red Magikoopa while it is flying: scripts that replace the standard handling for
 * its defeat (tag 49), being blown away (tag 58), an attack missing it (tag 46), being knocked out of the
 * air (tag 14) and the battle opening with a First Strike on it (tag 48).
 */
static BattleDataEntry data_table_sky[] = {
    {49, kamec_subset_dead_event},
    {58, kamec_subset_blow_dead_event},
    {46, avoid_miss_event},
    {14, dmg_fall_event},
    {48, dmg_first_attack_pos},
    {0},
};

/**
 * Event data table of the Red Magikoopa for its clones: scripts that replace the standard handling for an
 * attack missing it (tag 46).
 */
static BattleDataEntry data_table_bunsin[] = {
    {46, avoid_miss_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/**
 * Event data table of the Red Magikoopa for its clones while flying: scripts that replace the standard
 * handling for an attack missing it (tag 46), being knocked out of the air (tag 14) and the battle opening
 * with a First Strike on it (tag 48).
 */
static BattleDataEntry data_table_sky_bunsin[] = {
    {46, avoid_miss_event},
    {14, dmg_fall_event},
    {48, dmg_first_attack_pos},
    {0},
};

/**
 * Parts of the Red Magikoopa: 2 parts: parts 1 and 2 (model c_kamek_r), each with its defense tables,
 * attributes and pose table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_kamec_red", "c_kamek_r", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 45.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table},
    {2, "btl_un_kamec_red", "c_kamek_r", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
};

/** Weapon record of the Red Magikoopa's attack spell: 4 damage and ignores Defense. */
static BattleWeapon weapon_kamec_attack_magic = {
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
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
#if VERSION <= VERSION_DEMO_JP
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_SHATTERS_FREEZE | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
#else
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_SHATTERS_FREEZE, // special
#endif
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
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

/** Weapon record of the Red Magikoopa's Huge spell: no HP damage and inflicts Huge. */
static BattleWeapon weapon_kamec_dekadeka_magic = {
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
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, // burnTime..freezeTime
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

/** Weapon record of the Red Magikoopa's Electric spell: no HP damage and inflicts shock. */
static BattleWeapon weapon_kamec_biribiri_magic = {
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
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, // poisonStrength..confuseTime
    100, // electricChance
    3, // electricTime
    0, 0, 0, 0, 0, 0, 0, 0, // dodgyChance..sizeChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeStrength..allergicChance
    0, 0, 0, 0, 0, 0, 0, 0, // allergicTime..frightChance
    0, 0, 0, 0, 0, 0, 0, 0, // galeForceChance..fpRegenTime
    0, // fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Weapon record of the Red Magikoopa's Invisible spell: no HP damage and inflicts Invisible. */
static BattleWeapon weapon_kamec_trans_magic = {
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
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    100, // invisibleChance
    3, // invisibleTime
    0, 0, 0, 0, // hpRegenTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Weapon record of the Red Magikoopa's defense spell: no HP damage and inflicts Defense Up. */
static BattleWeapon weapon_kamec_katikati_magic = {
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
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, // atkChangeStrength
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

/** Weapon record of the Red Magikoopa's healing spell: no HP damage. */
static BattleWeapon weapon_kamec_recover_magic = {
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
    ELEMENT_NORMAL, 0, // element..damagePattern
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

/**
 * Weapon record of the Red Magikoopa's healing spell for all allies: no HP damage and can hit several
 * targets.
 */
static BattleWeapon weapon_kamec_all_recover_magic = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, 0, // acHelpMsg..special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    0, 0, 0, 0, 0, 0, 0, 0, // chargeStrength..paybackTime
    0, 0, 0, 0, 0, 0, 0, // holdFastTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Setup of the clone that spawn_event creates for the Magikoopa's clone spell: unit kind, side, turn phase
 * and starting position.
 */
static BattleUnitSetup entry_kamec = {
    &unit_kamec_red_bunsin, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/** Init script of the real Magikoopa. Registers its wait, attack, damage and other scripts and starts it waiting. */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_IS_CLONE, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_VANISHING, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_STAFF_EFFECT, 0)
    CALL_CHILD(init_event2)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Init script of a Magikoopa clone (bunsin). Same as init_event but the clone uses the sky data table (it floats). */
static EVT_BEGIN(init_event2)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_FLYING, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_sky))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_IS_CLONE, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table_sky))
        ELSE
            CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table_sky_bunsin))
        END_IF
        CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, UNIT_ATTR_FLOATING)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_WINGED)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), 40, LW(2))
        CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 40, LW(2))
    END_IF
    RETURN
EVT_END()

/**
 * Fades the unit whose id is in LW(0) out over 30 frames (alpha 254 down to 0),
 * then hides its body part (0x2000000, PART_ATTR_NO_SHADOW) so no shadow is left; LW(0) = -1 does nothing.
 * bunsin_magic_event uses it on the Magikoopa before it splits.
 */
static EVT_BEGIN(alpha_down_event)
    IF_INT_EQUAL(LW(0), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_SetAlpha, LW(0), 1, 254)
    CALL(btlevtcmd_AnimeFlagOnOff, LW(0), 1, PART_ANIM_CHANGE, 1)
    WAIT_FRAMES(1)
    CALL(evt_sub_intpl_init, 0, 254, 0, 30)
    LOOP(30)
        CALL(evt_sub_intpl_get_value_para, LW(1), LW(2))
        CALL(btlevtcmd_SetAlpha, LW(0), 1, LW(1))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_OnPartsAttribute, LW(0), 1, PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_SetAlpha, LW(0), 1, 0)
    CALL(btlevtcmd_AnimeFlagOnOff, LW(0), 1, PART_ANIM_CHANGE, 1)
    WAIT_FRAMES(1)
    RETURN
EVT_END()

/**
 * Fades the unit whose id is in LW(0) back in over 30 frames (alpha 0 up to 255),
 * first clearing the 0x2000000 part attribute (PART_ATTR_NO_SHADOW) that alpha_down_event set;
 * LW(0) = -1 does nothing.
 */
static EVT_BEGIN(alpha_up_event)
    IF_INT_EQUAL(LW(0), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_OffPartsAttribute, LW(0), 1, PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_SetAlpha, LW(0), 1, 0)
    CALL(btlevtcmd_AnimeFlagOnOff, LW(0), 1, PART_ANIM_CHANGE, 1)
    WAIT_FRAMES(1)
    CALL(evt_sub_intpl_init, 0, 0, 254, 30)
    LOOP(30)
        CALL(evt_sub_intpl_get_value_para, LW(1), LW(2))
        CALL(btlevtcmd_SetAlpha, LW(0), 1, LW(1))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetAlpha, LW(0), 1, 255)
    CALL(btlevtcmd_AnimeFlagOnOff, LW(0), 1, PART_ANIM_CHANGE, 1)
    WAIT_FRAMES(1)
    RETURN
EVT_END()

/**
 * Damage reaction of the Magikoopa.
 * Runs the default damage; if it is a clone that was hit, or the real one died,
 * it kills the clones (bunsin_kill_event, kamec_subset_bunsin_all_kill).
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_KILL_CLONES, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_IS_CLONE, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(kamec_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_KILL_CLONES, 1)
        END_IF
    ELSE
        SET_VALUE(LW(0), -2)
        CALL_CHILD(bunsin_kill_event)
        RETURN
    END_IF
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_KILL_CLONES, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL_CHILD(kamec_subset_bunsin_all_kill)
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Kills all four of the Magikoopa's clones: fetches their unit ids with kamec_get_bunsin
 * and spawns bunsin_kill_event for each existing one.
 */
static EVT_BEGIN(kamec_subset_bunsin_all_kill)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_IS_CLONE, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(kamec_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_WaitAttackEnd)
            CALL(kamec_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
            SET_VALUE(LW(0), LW(1))
            SPAWN_EVENT(bunsin_kill_event)
            SET_VALUE(LW(0), LW(2))
            SPAWN_EVENT(bunsin_kill_event)
            SET_VALUE(LW(0), LW(3))
            SPAWN_EVENT(bunsin_kill_event)
            SET_VALUE(LW(0), LW(4))
            SPAWN_EVENT(bunsin_kill_event)
            LOOP(0)
                CALL(kamec_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
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
 * Death script of the real Magikoopa (data event 49; the clone tables have none), for the unit in LW(10):
 * runs its data event 50 if it has one, hides its held item, spins round for 48 frames with the death sounds,
 * then pays out its coins, experience and star points with a smoke puff and tips over.
 * It then drops its back item, clears its statuses,
 * becomes hidden with no shadow (UNIT_ATTR_HIDDEN, UNIT_ATTR_NO_SHADOW),
 * removes every clone (kamec_subset_bunsin_all_kill) and is killed:
 * KillUnit mode 0 when the damage code has DAMAGE_FLAG_DEFEATED (0x400), otherwise mode 2 (KILL_UNIT_INACTIVE).
 */
static EVT_BEGIN(kamec_subset_dead_event)
    CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(0), 50)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_RunDataEventChild, LW(10), 50)
    END_IF
    SET_VALUE(LW(0), 48)
    CALL(btlevtcmd_OnUnitFlag, LW(10), UNIT_FLAG_HIDE_HELD_ITEM)
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
    CALL(btlevtcmd_OnAttribute, LW(10), UNIT_ATTR_HIDDEN)
    CALL(btlevtcmd_OnAttribute, LW(10), UNIT_ATTR_NO_SHADOW)
    CALL_CHILD(kamec_subset_bunsin_all_kill)
    CALL(btlevtcmd_CheckDamageCode, LW(10), DAMAGE_FLAG_DEFEATED, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_KillUnit, LW(10), 0)
    ELSE
        CALL(btlevtcmd_KillUnit, LW(10), 2)
    END_IF
    RETURN
EVT_END()

/**
 * Death script when the Magikoopa is blown away (Flurrie's gust):
 * plays SFX_BTL_CLAUD_BREATH3, kills all its clones and removes the unit.
 */
static EVT_BEGIN(kamec_subset_blow_dead_event)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_CLAUD_BREATH3"), 0)
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(0), BTL_POSE_DAMAGE)
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
    CALL_CHILD(kamec_subset_bunsin_all_kill)
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

/**
 * Data event 46, run when an attack misses this unit:
 * a clone (unit work 1 set) vanishes on the spot (bunsin_kill_event); the real Magikoopa is unaffected.
 */
static EVT_BEGIN(avoid_miss_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_IS_CLONE, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(0), -2)
        CALL_CHILD(bunsin_kill_event)
    END_IF
    RETURN
EVT_END()

/** Removes the clone whose unit id is in LW(0). */
static EVT_BEGIN(bunsin_kill_event)
    CALL(btlevtcmd_GetUnitId, LW(0), LW(0))
    IF_INT_EQUAL(LW(0), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, LW(0), UW_KAMEC_RED_VANISHING, LW(1))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_SetUnitWork, LW(0), UW_KAMEC_RED_VANISHING, 1)
    CALL_CHILD(alpha_down_event)
    LABEL(10)
    CALL(btlevtcmd_WaitAttackEnd)
    CALL(btlevtcmd_KillUnit, LW(0), 0)
    RETURN
EVT_END()

/** Phase script of the Magikoopa; does nothing. */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/**
 * Data event 14, run when a hit knocks the flying Magikoopa out of the air:
 * it clears its flying attributes (UNIT_ATTR_FLOATING, PART_ATTR_WINGED and the two cannot-target part flags),
 * shows the hurt pose, goes back to the ground pose table and the real or clone data table (unit work 1),
 * and drops to the floor (SFX_ENM_FALL1), which becomes its home,
 * while part 2 (KMR_H_1, Guess: the broom it rode) appears at its old spot and fades out.
 * Unit work 0 (flying) is cleared and init_event2 sets it up as a grounded unit.
 */
static EVT_BEGIN(dmg_fall_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_FLOATING)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_WINGED)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_DAMAGE)
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_IS_CLONE, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table))
    ELSE
        CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table_bunsin))
    END_IF
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_DAMAGE)
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("KMR_H_1"))
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
        WAIT_FRAMES(20)
        CALL(evt_sub_intpl_init, 0, 255, 0, 30)
        LOOP(30)
            CALL(evt_sub_intpl_get_value_para, LW(1), LW(2))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 2, LW(1))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
    END_INLINE_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 10, -1)
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 0, LW(2))
    WAIT_MS(500)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_FLYING, 0)
    CALL_CHILD(init_event2)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_DAMAGE)
    RETURN
EVT_END()

/**
 * Data event 48, run (damage code 57) when the battle opens with Mario's
 * or his partner's First Strike on the flying Magikoopa: it is set to height 10 and waits for the attack to end.
 */
static EVT_BEGIN(dmg_first_attack_pos)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

/**
 * Attack script of the Magikoopa.
 * Chooses a spell: usually the attack magic (weapon_kamec_attack_magic), or the heal, buff, Huge, Electric,
 * Invisible or defence spells for its allies, or creates its clones (bunsin_magic_event) depending on how many
 * clones exist and on random chances.
 */
static EVT_BEGIN(attack_event)
    // At the start of a first strike the Magikoopa goes straight into its attack spell.
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(9), PTR(&weapon_kamec_attack_magic))
        CALL_CHILD(attack_magic_event)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_IS_CLONE, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    // Use an enemy item if one fits.
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        GOTO(99)
    END_IF
    // Alone on the stage (no clones), it casts the attack spell, heals itself or makes clones of itself.
    CALL(kamec_get_live_num, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        LABEL(10)
        SET_VALUE(LW(1), 40)
        ADD(LW(1), 0)
        ADD(LW(1), 40)
        SUBTRACT(LW(1), 1)
        CALL(evt_sub_random, LW(1), LW(0))
        SET_VALUE(LW(1), 40)
        IF_INT_LESS(LW(0), LW(1))
            SET_VALUE(LW(9), PTR(&weapon_kamec_attack_magic))
            CALL_CHILD(attack_magic_event)
            GOTO(99)
        END_IF
        ADD(LW(1), 0)
        IF_INT_LESS(LW(0), LW(1))
            SET_VALUE(LW(9), PTR(&weapon_kamec_recover_magic))
            CALL_CHILD(recover_magic_event)
            IF_INT_EQUAL(LW(0), 0)
                GOTO(10)
            END_IF
            GOTO(99)
        ELSE
            CALL_CHILD(bunsin_magic_event)
            GOTO(99)
        END_IF
    ELSE
        // With clones about, it rolls for its spell: the attack spell first,
        CALL(kamec_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL_CHILD(subsetevt_confuse_flustered)
                GOTO(99)
            END_IF
            SET_VALUE(LW(9), PTR(&weapon_kamec_attack_magic))
            CALL_CHILD(attack_magic_event)
            GOTO(99)
        ELSE
            LABEL(20)
            SET_VALUE(LW(1), 50)
            ADD(LW(1), 20)
            ADD(LW(1), 20)
            ADD(LW(1), 0)
            ADD(LW(1), 0)
            ADD(LW(1), 0)
            ADD(LW(1), 0)
            CALL(evt_sub_random, LW(1), LW(0))
            SET_VALUE(LW(1), 50)
            IF_INT_LESS(LW(0), LW(1))
                SET_VALUE(LW(9), PTR(&weapon_kamec_attack_magic))
                CALL_CHILD(attack_magic_event)
                GOTO(99)
            END_IF
            ADD(LW(1), 20)
            IF_INT_LESS(LW(0), LW(1))
                SET_VALUE(LW(9), PTR(&weapon_kamec_dekadeka_magic))
                // the Huge spell on an ally,
                CALL_CHILD(dekadeka_magic_event)
                IF_INT_EQUAL(LW(0), 0)
                    GOTO(20)
                END_IF
                GOTO(99)
            END_IF
            ADD(LW(1), 20)
            IF_INT_LESS(LW(0), LW(1))
                SET_VALUE(LW(9), PTR(&weapon_kamec_katikati_magic))
                // the defense-boosting spell,
                CALL_CHILD(katikati_magic_event)
                IF_INT_EQUAL(LW(0), 0)
                    GOTO(20)
                END_IF
                GOTO(99)
            END_IF
            ADD(LW(1), 0)
            IF_INT_LESS(LW(0), LW(1))
                SET_VALUE(LW(9), PTR(&weapon_kamec_biribiri_magic))
                // the Electric spell,
                CALL_CHILD(biribiri_magic_event)
                IF_INT_EQUAL(LW(0), 0)
                    GOTO(20)
                END_IF
                GOTO(99)
            END_IF
            ADD(LW(1), 0)
            IF_INT_LESS(LW(0), LW(1))
                SET_VALUE(LW(9), PTR(&weapon_kamec_trans_magic))
                // the Invisible spell,
                CALL_CHILD(trans_magic_event)
                IF_INT_EQUAL(LW(0), 0)
                    GOTO(20)
                END_IF
                GOTO(99)
            END_IF
            ADD(LW(1), 0)
            IF_INT_LESS(LW(0), LW(1))
                SET_VALUE(LW(9), PTR(&weapon_kamec_recover_magic))
                // and the healing spells, for one ally or for all.
                CALL_CHILD(recover_magic_event)
                IF_INT_EQUAL(LW(0), 0)
                    GOTO(20)
                END_IF
                GOTO(99)
            ELSE
                SET_VALUE(LW(9), PTR(&weapon_kamec_all_recover_magic))
                CALL_CHILD(all_recover_magic_event)
                IF_INT_EQUAL(LW(0), 0)
                    GOTO(20)
                END_IF
                GOTO(99)
            END_IF
        END_IF
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Casting animation on the ground, shared with the clones:
 * a staff glow (eff_staff1) on the caster and on each clone,
 * or only the larger glow (eff_staff2) on the caster when LW(15) is nonzero,
 * the KMR_A_1A to KMR_A_1E poses played in step on all of them,
 * and the magic sounds (SFX_ENM_KAMEKU_MAGIC1, 4 and 8).
 */
static EVT_BEGIN(ground_magic_common_event1)
    // Casting begins on the ground: the casting sound repeats while the staff glows on the caster and each clone.
    BEGIN_SIBLING_EVENT
        LOOP(2)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KAMEKU_MAGIC1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(40)
        END_LOOP
    END_SIBLING_EVENT
    CALL(kamec_get_bunsin, LW(11), LW(12), LW(13), LW(14), LW(0))
    IF_INT_EQUAL(LW(15), 0)
        BEGIN_SIBLING_EVENT
            CALL(eff_staff1, BTL_UNIT_SELF)
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            IF_INT_NOT_EQUAL(LW(11), -1)
                CALL(eff_staff1, LW(11))
            END_IF
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            IF_INT_NOT_EQUAL(LW(12), -1)
                CALL(eff_staff1, LW(12))
            END_IF
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            IF_INT_NOT_EQUAL(LW(13), -1)
                CALL(eff_staff1, LW(13))
            END_IF
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            IF_INT_NOT_EQUAL(LW(14), -1)
                CALL(eff_staff1, LW(14))
            END_IF
        END_SIBLING_EVENT
    ELSE
        BEGIN_SIBLING_EVENT
            CALL(eff_staff2, BTL_UNIT_SELF)
        END_SIBLING_EVENT
    END_IF
    // The caster and every clone raise their staffs together.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KMR_A_1A"))
    IF_INT_NOT_EQUAL(LW(11), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(11), 1, STRING("KMR_A_1A"))
    END_IF
    IF_INT_NOT_EQUAL(LW(12), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(12), 1, STRING("KMR_A_1A"))
    END_IF
    IF_INT_NOT_EQUAL(LW(13), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(13), 1, STRING("KMR_A_1A"))
    END_IF
    IF_INT_NOT_EQUAL(LW(14), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(14), 1, STRING("KMR_A_1A"))
    END_IF
    WAIT_FRAMES(60)
    // The staffs wave and the magic gathers.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KAMEKU_MAGIC4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KMR_A_1B"))
    IF_INT_NOT_EQUAL(LW(11), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(11), 1, STRING("KMR_A_1B"))
    END_IF
    IF_INT_NOT_EQUAL(LW(12), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(12), 1, STRING("KMR_A_1B"))
    END_IF
    IF_INT_NOT_EQUAL(LW(13), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(13), 1, STRING("KMR_A_1B"))
    END_IF
    IF_INT_NOT_EQUAL(LW(14), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(14), 1, STRING("KMR_A_1B"))
    END_IF
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KMR_A_1C"))
    IF_INT_NOT_EQUAL(LW(11), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(11), 1, STRING("KMR_A_1C"))
    END_IF
    IF_INT_NOT_EQUAL(LW(12), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(12), 1, STRING("KMR_A_1C"))
    END_IF
    IF_INT_NOT_EQUAL(LW(13), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(13), 1, STRING("KMR_A_1C"))
    END_IF
    IF_INT_NOT_EQUAL(LW(14), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(14), 1, STRING("KMR_A_1C"))
    END_IF
    WAIT_FRAMES(30)
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(10)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KAMEKU_MAGIC8"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    // The staffs are thrust forward to release the spell.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KMR_A_1D"))
    IF_INT_NOT_EQUAL(LW(11), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(11), 1, STRING("KMR_A_1D"))
    END_IF
    IF_INT_NOT_EQUAL(LW(12), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(12), 1, STRING("KMR_A_1D"))
    END_IF
    IF_INT_NOT_EQUAL(LW(13), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(13), 1, STRING("KMR_A_1D"))
    END_IF
    IF_INT_NOT_EQUAL(LW(14), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(14), 1, STRING("KMR_A_1D"))
    END_IF
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KMR_A_1E"))
    IF_INT_NOT_EQUAL(LW(11), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(11), 1, STRING("KMR_A_1E"))
    END_IF
    IF_INT_NOT_EQUAL(LW(12), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(12), 1, STRING("KMR_A_1E"))
    END_IF
    IF_INT_NOT_EQUAL(LW(13), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(13), 1, STRING("KMR_A_1E"))
    END_IF
    IF_INT_NOT_EQUAL(LW(14), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(14), 1, STRING("KMR_A_1E"))
    END_IF
    RETURN
EVT_END()

/**
 * Casting animation on the ground for the caster alone:
 * a staff glow, the KMR_A_1A, 2A, 2B and 2C poses and the magic sounds (SFX_ENM_KAMEKU_MAGIC1, 6 and 7).
 */
static EVT_BEGIN(ground_magic_common_event2)
    BEGIN_SIBLING_EVENT
        LOOP(2)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KAMEKU_MAGIC1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(40)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(eff_staff1, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KMR_A_1A"))
    WAIT_FRAMES(60)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KAMEKU_MAGIC6"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KMR_A_2A"))
    WAIT_FRAMES(40)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KAMEKU_MAGIC7"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KMR_A_2B"))
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KMR_A_2C"))
    RETURN
EVT_END()

/**
 * Casting animation while flying: a staff glow on the caster
 * and on each clone (only on the caster when LW(15) is nonzero),
 * the KMR_A_3A to KMR_A_3D poses played in step on all of them, and the magic sounds.
 */
static EVT_BEGIN(sky_magic_common_event)
    // Casting begins in the air: the casting sound repeats while the staff glows on the caster and each clone.
    BEGIN_SIBLING_EVENT
        LOOP(2)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KAMEKU_MAGIC1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(40)
        END_LOOP
    END_SIBLING_EVENT
    CALL(kamec_get_bunsin, LW(11), LW(12), LW(13), LW(14), LW(0))
    IF_INT_EQUAL(LW(15), 0)
        BEGIN_SIBLING_EVENT
            CALL(eff_staff1, BTL_UNIT_SELF)
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            IF_INT_NOT_EQUAL(LW(11), -1)
                CALL(eff_staff1, LW(11))
            END_IF
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            IF_INT_NOT_EQUAL(LW(12), -1)
                CALL(eff_staff1, LW(12))
            END_IF
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            IF_INT_NOT_EQUAL(LW(13), -1)
                CALL(eff_staff1, LW(13))
            END_IF
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            IF_INT_NOT_EQUAL(LW(14), -1)
                CALL(eff_staff1, LW(14))
            END_IF
        END_SIBLING_EVENT
    ELSE
        BEGIN_SIBLING_EVENT
            CALL(eff_staff2, BTL_UNIT_SELF)
        END_SIBLING_EVENT
    END_IF
    // The caster and every clone raise their staffs together.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KMR_A_3A"))
    IF_INT_NOT_EQUAL(LW(11), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(11), 1, STRING("KMR_A_3A"))
    END_IF
    IF_INT_NOT_EQUAL(LW(12), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(12), 1, STRING("KMR_A_3A"))
    END_IF
    IF_INT_NOT_EQUAL(LW(13), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(13), 1, STRING("KMR_A_3A"))
    END_IF
    IF_INT_NOT_EQUAL(LW(14), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(14), 1, STRING("KMR_A_3A"))
    END_IF
    WAIT_FRAMES(60)
    // The staffs wave and the magic gathers.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KAMEKU_MAGIC8"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KMR_A_3B"))
    IF_INT_NOT_EQUAL(LW(11), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(11), 1, STRING("KMR_A_3B"))
    END_IF
    IF_INT_NOT_EQUAL(LW(12), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(12), 1, STRING("KMR_A_3B"))
    END_IF
    IF_INT_NOT_EQUAL(LW(13), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(13), 1, STRING("KMR_A_3B"))
    END_IF
    IF_INT_NOT_EQUAL(LW(14), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(14), 1, STRING("KMR_A_3B"))
    END_IF
    WAIT_FRAMES(35)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KAMEKU_MAGIC7"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KMR_A_3C"))
    IF_INT_NOT_EQUAL(LW(11), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(11), 1, STRING("KMR_A_3C"))
    END_IF
    IF_INT_NOT_EQUAL(LW(12), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(12), 1, STRING("KMR_A_3C"))
    END_IF
    IF_INT_NOT_EQUAL(LW(13), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(13), 1, STRING("KMR_A_3C"))
    END_IF
    IF_INT_NOT_EQUAL(LW(14), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(14), 1, STRING("KMR_A_3C"))
    END_IF
    WAIT_FRAMES(15)
    // The staffs are thrust forward to release the spell.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KMR_A_3D"))
    IF_INT_NOT_EQUAL(LW(11), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(11), 1, STRING("KMR_A_3D"))
    END_IF
    IF_INT_NOT_EQUAL(LW(12), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(12), 1, STRING("KMR_A_3D"))
    END_IF
    IF_INT_NOT_EQUAL(LW(13), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(13), 1, STRING("KMR_A_3D"))
    END_IF
    IF_INT_NOT_EQUAL(LW(14), -1)
        CALL(btlevtcmd_AnimeChangePose, LW(14), 1, STRING("KMR_A_3D"))
    END_IF
    RETURN
EVT_END()

/**
 * Plays the casting animation: while flying (unit work 0 set) the sky version;
 * on the ground, the version shared with the clones unless the target in LW(3) is the caster's own id,
 * which gets the solo version (ground_magic_common_event2).
 */
static EVT_BEGIN(magic_common_event1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_FLYING, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(13))
        IF_INT_NOT_EQUAL(LW(3), LW(13))
            CALL_CHILD(ground_magic_common_event1)
        ELSE
            CALL_CHILD(ground_magic_common_event2)
        END_IF
    ELSE
        CALL_CHILD(sky_magic_common_event)
    END_IF
    RETURN
EVT_END()

/**
 * Plays the casting animation for the caster alone:
 * ground_magic_common_event2 on the ground, the sky version while flying.
 */
static EVT_BEGIN(magic_common_event2)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_FLYING, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL_CHILD(ground_magic_common_event2)
    ELSE
        CALL_CHILD(sky_magic_common_event)
    END_IF
    RETURN
EVT_END()

/**
 * Starts the target's avoid animation for the result of a pre-damage check (3, 6 or 2 select the three avoid
 * types).
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
 * The Magikoopa's attack spell (weapon in LW(9)):
 * it picks the target (the first-strike target during a first strike, otherwise a sampled enemy;
 * flustered when confused with none), declares the attack and casts with its clones,
 * then fires a magic shot (SFX_ENM_KAMEKU_MAGIC3_2) from itself and every clone.
 * On a miss the shots fly past to the stage edge while a sibling event starts the target's avoid reaction
 * when the caster's shot reaches it; on a hit all shots land on the target after 45 frames and the guard result
 * and damage are applied. Then all of them return to their normal pose.
 */
static EVT_BEGIN(attack_magic_event)
    // Use the target of the opening first attack if there was one, otherwise choose a target.
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    // The attack is announced.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    SET_VALUE(LW(15), 0)
    // The Magikoopa and its clones go through the casting motions.
    CALL_CHILD(magic_common_event1)
    // Magic bolts shoot toward the target.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KAMEKU_MAGIC3_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_btl_camera_set_mode, 0, 0)
    // Find out how the target reacts to the bolts.
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
        // The spell missed: the bolts fly on past the target, which gets out of their way.
        LABEL(90)
        BEGIN_SIBLING_EVENT
            WAIT_FRAMES(1)
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
        CALL(kamec_get_bunsin, LW(6), LW(7), LW(8), LW(13), LW(0))
        SET_VALUE(LW(14), -2)
        CALL_CHILD(attack_magic_event_sub_no_hit)
        SET_VALUE(LW(14), LW(6))
        CALL_CHILD(attack_magic_event_sub_no_hit)
        SET_VALUE(LW(14), LW(7))
        CALL_CHILD(attack_magic_event_sub_no_hit)
        SET_VALUE(LW(14), LW(8))
        CALL_CHILD(attack_magic_event_sub_no_hit)
        SET_VALUE(LW(14), LW(13))
        CALL_CHILD(attack_magic_event_sub_no_hit)
        WAIT_FRAMES(60)
        GOTO(98)
        // The bolts hit: the damage is applied.
        LABEL(91)
        CALL(kamec_get_bunsin, LW(6), LW(7), LW(8), LW(13), LW(0))
        SET_VALUE(LW(14), -2)
        CALL_CHILD(attack_magic_event_sub_hit)
        SET_VALUE(LW(14), LW(6))
        CALL_CHILD(attack_magic_event_sub_hit)
        SET_VALUE(LW(14), LW(7))
        CALL_CHILD(attack_magic_event_sub_hit)
        SET_VALUE(LW(14), LW(8))
        CALL_CHILD(attack_magic_event_sub_hit)
        SET_VALUE(LW(14), LW(13))
        CALL_CHILD(attack_magic_event_sub_hit)
        WAIT_FRAMES(45)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
        GOTO(98)
        // The Magikoopa and its clones lower their staffs.
        LABEL(98)
        WAIT_FRAMES(30)
        CALL(kamec_get_bunsin, LW(6), LW(7), LW(8), LW(9), LW(0))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY)
        IF_INT_NOT_EQUAL(LW(6), -1)
            CALL(btlevtcmd_AnimeChangePoseType, LW(6), 1, BTL_POSE_STAY)
        END_IF
        IF_INT_NOT_EQUAL(LW(7), -1)
            CALL(btlevtcmd_AnimeChangePoseType, LW(7), 1, BTL_POSE_STAY)
        END_IF
        IF_INT_NOT_EQUAL(LW(8), -1)
            CALL(btlevtcmd_AnimeChangePoseType, LW(8), 1, BTL_POSE_STAY)
        END_IF
        IF_INT_NOT_EQUAL(LW(9), -1)
            CALL(btlevtcmd_AnimeChangePoseType, LW(9), 1, BTL_POSE_STAY)
        END_IF
        LABEL(99)
        CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
        RETURN
EVT_END()

/**
 * Fires one magic shot from the unit in LW(14) past the target in LW(3)/LW(4),
 * at the stage edge at the target's height, lasting 60 frames; LW(14) = -1 does nothing.
 */
static EVT_BEGIN(attack_magic_event_sub_no_hit)
    IF_INT_EQUAL(LW(14), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetPos, LW(14), LW(0), LW(1), LW(2))
    ADD(LW(1), 10)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
    CALL(btlevtcmd_GetStageSize, LW(10), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetFaceDirection, LW(14), LW(0))
    MULTIPLY(LW(10), LW(0))
    SUBTRACT(LW(11), 5)
    CALL(eff_magic, LW(14), LW(10), LW(11), LW(12), 60)
    RETURN
EVT_END()

/**
 * Fires one magic shot from the unit in LW(14) at the hit position of the target in LW(3)/LW(4),
 * reaching it in 45 frames; LW(14) = -1 does nothing.
 */
static EVT_BEGIN(attack_magic_event_sub_hit)
    IF_INT_EQUAL(LW(14), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetPos, LW(14), LW(0), LW(1), LW(2))
    ADD(LW(1), 10)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
    CALL(eff_magic, LW(14), LW(10), LW(11), LW(12), 45)
    RETURN
EVT_END()

/**
 * Shared part of the four support spells (weapon in LW(9), status to give in LW(15): 10 Huge, 14 defense up,
 * 6 electrified, 18 invisible): it picks an ally,
 * and if the ally already has that status it returns LW(0) = 0 so the caller can choose again.
 * Otherwise it declares the spell, casts, and after 30 frames applies the weapon to the ally;
 * LW(0) is 1 on return.
 */
static EVT_BEGIN(support_magic_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            SET_VALUE(LW(0), 1)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    IF_INT_EQUAL(LW(15), 10)
        CALL(btlevtcmd_CheckStatus, LW(3), STATUS_HUGE, LW(0))
    END_IF
    IF_INT_EQUAL(LW(15), 14)
        CALL(btlevtcmd_CheckStatus, LW(3), STATUS_DEFENSE_UP, LW(0))
    END_IF
    IF_INT_EQUAL(LW(15), 6)
        CALL(btlevtcmd_CheckStatus, LW(3), STATUS_ELECTRIC, LW(0))
    END_IF
    IF_INT_EQUAL(LW(15), 18)
        CALL(btlevtcmd_CheckStatus, LW(3), STATUS_INVISIBLE, LW(0))
    END_IF
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    SET_VALUE(LW(15), 0)
    CALL_CHILD(magic_common_event1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    WAIT_FRAMES(30)
    LABEL(99)
    SET_VALUE(LW(0), 1)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Casts the size-up spell (dekadeka = huge) on an ally: makes it Huge (size change strength 2) for three turns. */
static EVT_BEGIN(dekadeka_magic_event)
    SET_VALUE(LW(15), 10)
    CALL_CHILD(support_magic_event)
    RETURN
EVT_END()

/** Casts the hardening spell (katikati = rock-hard) on an ally: raises its defence by 3 for three turns. */
static EVT_BEGIN(katikati_magic_event)
    SET_VALUE(LW(15), 14)
    CALL_CHILD(support_magic_event)
    RETURN
EVT_END()

/** Casts the electric spell (biribiri = tingling) on an ally: it becomes Electrified for three turns. */
static EVT_BEGIN(biribiri_magic_event)
    SET_VALUE(LW(15), 6)
    CALL_CHILD(support_magic_event)
    RETURN
EVT_END()

/** Casts the transparency spell on an ally: it becomes Invisible for three turns. */
static EVT_BEGIN(trans_magic_event)
    SET_VALUE(LW(15), 18)
    CALL_CHILD(support_magic_event)
    RETURN
EVT_END()

/** Heal spell on one ally: restores up to 8 HP. */
static EVT_BEGIN(recover_magic_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            SET_VALUE(LW(0), 1)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetHp, LW(3), LW(0))
    CALL(btlevtcmd_GetMaxHp, LW(3), LW(1))
    IF_INT_EQUAL(LW(0), LW(1))
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    SET_VALUE(LW(15), 0)
    CALL_CHILD(magic_common_event1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_RecoverHp, LW(3), LW(4), 8)
    CALL(btlevtcmd_GetPartsPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, LW(3), LW(5))
    CALL(btlevtcmd_GetStatusMg, LW(3), LW(6))
    MULTIPLY_FLOAT(LW(5), LW(6))
    ADD(LW(1), LW(5))
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, LW(0), LW(1), LW(2), 8, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(40)
    LABEL(99)
    SET_VALUE(LW(0), 1)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Heal spell on all allies: restores up to 4 HP each.
 * Only the first target's missing HP is checked, so it may heal nobody when only that one is at full HP.
 */
static EVT_BEGIN(all_recover_magic_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            SET_VALUE(LW(0), 1)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    LABEL(5)
    CALL(btlevtcmd_GetHp, LW(3), LW(0))
    CALL(btlevtcmd_GetMaxHp, LW(3), LW(1))
    IF_INT_LESS(LW(0), LW(1))
        GOTO(8)
    END_IF
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    // BUG: inverted check. This should give up when there is no next enemy (LW(3) == -1); as written it
    // gives up whenever there is one, so only the first enemy is checked for missing HP, and if the
    // first is the only one and at full HP, the loop runs again with LW(3) == -1.
    IF_INT_NOT_EQUAL(LW(3), -1)
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    GOTO(5)
    LABEL(8)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL_CHILD(magic_common_event2)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    LABEL(10)
    BEGIN_SIBLING_EVENT
        CALL(evt_sub_random, 10, LW(0))
        WAIT_FRAMES(LW(0))
        CALL(btlevtcmd_RecoverHp, LW(3), LW(4), 4)
        CALL(btlevtcmd_GetPartsPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetHeight, LW(3), LW(5))
        CALL(btlevtcmd_GetStatusMg, LW(3), LW(6))
        MULTIPLY_FLOAT(LW(5), LW(6))
        ADD(LW(1), LW(5))
        CALL(evt_eff, STRING(""), STRING("recovery"), 0, LW(0), LW(1), LW(2), 4, 0, 0, 0, 0, 0, 0, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        GOTO(10)
    END_IF
    SET_VALUE(LW(0), 1)
    WAIT_FRAMES(120)
    RETURN
EVT_END()

/**
 * The Magikoopa's clone spell: it casts (SFX_ENM_KAMEKU_OFFSHOOT1), fades out,
 * and spawns a clone (spawn_event) at every free spot in 40-unit steps from its own position,
 * first toward the front up to the middle of the stage, then back up to x 170.
 * kamec_shuffle mixes up the positions, and the Magikoopa
 * and up to four clones fade back in together (SFX_ENM_KAMEKU_OFFSHOOT2).
 */
static EVT_BEGIN(bunsin_magic_event)
    SET_VALUE(LW(3), -2)
    SET_VALUE(LW(4), 1)
    SET_VALUE(LW(15), 1)
    CALL_CHILD(magic_common_event1)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KAMEKU_OFFSHOOT1"), EVT_NULLPTR, 0, EVT_NULLPTR)
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
    CALL(kamec_shuffle)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KAMEKU_OFFSHOOT2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    SET_VALUE(LW(0), -2)
    SPAWN_EVENT(alpha_up_event)
    CALL(kamec_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
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
 * Script helper that fires a Magikoopa's magic shot:
 * args[0] is the caster, args[1] to args[3] the target point
 * and args[4] the lifetime in frames (effMagic1N64Entry type 0 flies from the start to the target over that
 * time).
 * It starts at the wand tip (25 units ahead, 20 up, scaled by size, 5 toward the camera);
 * the effect is kept in the caster's work[5] for eff_magic_get_posX and scaled to the caster's size.
 */
static USER_FUNC(eff_magic) {
    EvtWord* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 a = evtGetFloat(event, args[1]);
    f32 b = evtGetFloat(event, args[2]);
    f32 c = evtGetFloat(event, args[3]);
    s32 type = evtGetValue(event, args[4]);
    f32 x;
    f32 y;
    f32 z;
    EffectEntry* eff;

    BtlUnit_GetPos(unit, &x, &y, &z);
    // from the tip of the wand
    x += 25.0f * unit->sizeMultiplier * unit->faceDirection;
    y += 20.0f * unit->sizeMultiplier;
    z += 5.0f;
    eff = effMagic1N64Entry(0, type, x, y, z, a, b, c);
    unit->work[UW_KAMEC_RED_MAGIC_EFFECT] = (EvtWord)eff;
    ((EffMagic1N64Work*)eff->userdata)->scale = unit->sizeMultiplier;
    return EVT_RETURN_DONE;
}

/** Script helper that shows the staff charge sparkle at the wand tip while casting; blocks until the effect ends. */
static USER_FUNC(eff_staff2) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;
    f32* wk;

    if (isFirstCall) {
        unit->work[UW_KAMEC_RED_STAFF_EFFECT] = (EvtWord)effPokopiPchargeN64Entry(0, 60, 0.0f, -1000.0f, 0.0f, 1.0f);
    }
    if (!(((EffectEntry*)unit->work[UW_KAMEC_RED_STAFF_EFFECT])->flags & 1)) {
        return EVT_RETURN_DONE;
    }
    wk = ((EffectEntry*)unit->work[UW_KAMEC_RED_STAFF_EFFECT])->userdata;
    wk[13] = unit->sizeMultiplier;
    BtlUnit_GetPos(unit, &x, &y, &z);
    wk[1] = x + 22.5f * unit->sizeMultiplier * unit->faceDirection;
    wk[2] = y + 40.0f * unit->sizeMultiplier;
    wk[3] = 5.0f + z;
    return EVT_RETURN_BLOCK;
}

/** Script helper that shows the staff thunder flare at the wand tip while casting; blocks until the effect ends. */
static USER_FUNC(eff_staff1) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;
    f32* wk;

    if (isFirstCall) {
        unit->work[UW_KAMEC_RED_STAFF_EFFECT] = (EvtWord)effThunderflareN64Entry(0, 60, 0.0f, -1000.0f, 0.0f, 1.0f);
    }
    if (!(((EffectEntry*)unit->work[UW_KAMEC_RED_STAFF_EFFECT])->flags & 1)) {
        return EVT_RETURN_DONE;
    }
    wk = ((EffectEntry*)unit->work[UW_KAMEC_RED_STAFF_EFFECT])->userdata;
    wk[10] = unit->sizeMultiplier;
    BtlUnit_GetPos(unit, &x, &y, &z);
    wk[2] = x + 22.5f * unit->sizeMultiplier * unit->faceDirection;
    wk[3] = y + 40.0f * unit->sizeMultiplier;
    wk[4] = 5.0f + z;
    return EVT_RETURN_BLOCK;
}

/**
 * Script helper: arg0 = source unit, arg1 = destination unit;
 * the clone (bunsin) gets the real Magikoopa's HP and status turns so they stay in step.
 */
static USER_FUNC(kamec_copy_status) {
    EvtWord* args = event->args;
    s32 id1 = evtGetValue(event, args[0]);
    s32 id2 = evtGetValue(event, args[1]);
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit1 = BattleGetUnitPtr(wp, id1);
    BattleUnit* unit2 = BattleGetUnitPtr(wp, id2);

    // the copy shares the real magikoopa's hp and status
    unit2->currentHp = unit1->currentHp;
    memcpy(&unit2->sleepTurns, &unit1->sleepTurns, 0x1E);
    unit2->hpGauge.prevHp = unit2->currentHp;
    unit2->hpGauge.targetHp = unit2->currentHp;
    unit2->hpGauge.barRatio = unit2->hpGauge.trailRatio = (f32)unit2->currentHp / unit2->maxHp;
    return EVT_RETURN_DONE;
}

/**
 * Script helper: ten times swaps, at random, the x and z positions
 * and home positions of two of the Red Magikoopas on the field (the real one, kind 0x31, and its clones,
 * kind 0x32), so the player cannot tell which one is real.
 */
static USER_FUNC(kamec_shuffle) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* kamecs[6];
    s32 n = 0;
    s32 i;

    // the real magikoopa and its copies
    for (i = 0; i < 64; i++) {
        kamecs[n] = wp->units[i];
        if (kamecs[n] != NULL && (kamecs[n]->currentKind == 0x31 || kamecs[n]->currentKind == 0x32)) {
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
 * Script helper: writes the unit ids of the red Magikoopa's clones (up to four, -1 for unused slots) to the
 * first four arguments and their count to the fifth.
 */
static USER_FUNC(kamec_get_bunsin) {
    EvtWord* args = event->args;
    s32 copies[4];
    s32 n = 0;
    s32 i;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;

    // indices of the magikoopa's copies
    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && unit->currentKind == 0x32) {
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

/** Script helper: arg0 receives how many units on alliance 1 (the enemy side) are still alive. */
static USER_FUNC(kamec_get_live_num) {
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

/**
 * Spawns one clone (entry_kamec) into LW(3) at the position in LW(0) to LW(2), which becomes its home:
 * it starts invisible (alpha 0, until alpha_up_event),
 * copies the flying flag (unit work 0) and the statuses of the real unit (kamec_copy_status),
 * and from JP on gets its HP gauge back.
 * It is marked as a clone (unit work 1 = 1) with the clone attack event and resistances,
 * and its body part becomes evasive (PART_ATTR_EVASIVE).
 */
static EVT_BEGIN(spawn_event)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_kamec), 0)
    CALL(btlevtcmd_SetAlpha, LW(3), 1, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_FLYING, LW(10))
    CALL(btlevtcmd_SetUnitWork, LW(3), UW_KAMEC_RED_FLYING, LW(10))
    WAIT_FRAMES(2)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(13))
    CALL(kamec_copy_status, LW(13), LW(3))
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_OffAttribute, LW(3), UNIT_ATTR_NO_HP_GAUGE)
#endif
    CALL(btlevtcmd_SetUnitWork, LW(3), UW_KAMEC_RED_IS_CLONE, 1)
    CALL(btlevtcmd_SetEventAttack, LW(3), PTR(attack_event))
    CALL(btlevtcmd_SetRegistStatus, LW(3), PTR(&regist_bunsin))
    CALL(btlevtcmd_OnPartsAttribute, LW(3), 1, PART_ATTR_EVASIVE)
    RETURN
EVT_END()

/** Wait script of the Magikoopa: shows its idle pose (and the clones' poses) from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_KAMEC_RED_IS_CLONE, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(kamec_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
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
    RETURN
EVT_END()
