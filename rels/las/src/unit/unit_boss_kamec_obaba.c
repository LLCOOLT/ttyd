// Palace of Shadow battle unit: Kammy Koopa (fought with Bowser) (`boss_kamec_obaba`): parts, stats, poses and AI scripts.

#include "battle/battle_unit.h"
#include "eff/n64/eff_magic1_n64.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_sub.h"
#include "battle/battle_database_common.h"
#include "evt/evt_eff.h"
#include "evt/evt_msg.h"
#include "eff/eff_stardust.h"
#include "eff/n64/eff_thunderflare_n64.h"

// Unit work slots of Kammy Koopa (btlevtcmd_SetUnitWork / GetUnitWork / AddUnitWork; eff_* use 3 and 4).
enum {
    UW_BOSS_KAMEC_OBABA_FLYING = 0,         // 1 while she is on her broom
    UW_BOSS_KAMEC_OBABA_FLYING_DAMAGE = 1,  // damage taken on the broom; above 1 she falls off
    UW_BOSS_KAMEC_OBABA_GROUNDED_TURNS = 2, // turns on the ground; at 3 she gets back on her broom
    UW_BOSS_KAMEC_OBABA_STAFF_EFFECT = 3,   // EffectEntry of the Thunder Flare charge on her staff (eff_staff)
    UW_BOSS_KAMEC_OBABA_MAGIC_EFFECT = 4,   // EffectEntry of her magic bolt (eff_magic)
};

// The callers of effThunderflareN64Entry pass a sixth argument (scale) that the five-parameter definition in
// eff_thunderflare_n64.h does not take (header request P13 4).

static USER_FUNC(eff_magic_support);
static USER_FUNC(eff_magic_get_posX);
static USER_FUNC(eff_magic);
static USER_FUNC(eff_staff);

BattleWeapon weapon_kamec_obaba_attack_magic;
BattleWeapon weapon_kamec_obaba_dekadeka_magic;
BattleWeapon weapon_kamec_obaba_biribiri_magic;
BattleWeapon weapon_kamec_obaba_katikati_magic;
BattleWeapon weapon_kamec_obaba_trans_magic;
BattleWeapon weapon_kamec_obaba_recover_magic;
BattleUnitKind unit_boss_kamec_obaba;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[17];
static PoseTableEntry pose_table_sky[17];
static PoseTableEntry pose_table_dead[3];
static BattleDataEntry data_table[2];
static BattleUnitKindPart parts[2];
static EvtWord init_event[56];
static EvtWord damage_event[74];
static EvtWord dmg_fall_event[149];
static EvtWord dead_event[155];
static EvtWord phase_event[216];
static EvtWord attack_event[352];
static EvtWord attack_magic_event[269];
extern EvtWord magic_select_pri_obaba[];
extern EvtWord magic_select_pri_koopa[];
static EvtWord dekadeka_magic_event[73];
static EvtWord katikati_magic_event[4];
static EvtWord biribiri_magic_event[4];
static EvtWord trans_magic_event[4];
static EvtWord recover_magic_event[90];
static EvtWord wait_event[6];

/** Weapon of Kammy Koopa's magic blast: damage 5. */
BattleWeapon weapon_kamec_obaba_attack_magic = {
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
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
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

/** Weapon of Kammy Koopa's spell that makes a unit huge: inflicts a size change. */
BattleWeapon weapon_kamec_obaba_dekadeka_magic = {
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
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS, // special
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

/** Weapon of Kammy Koopa's spell that electrifies a unit: inflicts Electrified. */
BattleWeapon weapon_kamec_obaba_biribiri_magic = {
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
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS, // special
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

/** Weapon of Kammy Koopa's spell that raises Defense: inflicts a defense change. */
BattleWeapon weapon_kamec_obaba_katikati_magic = {
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
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS, // special
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

/** Weapon of Kammy Koopa's spell that turns a unit invisible: inflicts Invisible. */
BattleWeapon weapon_kamec_obaba_trans_magic = {
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
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS, // special
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

/** Weapon of Kammy Koopa's healing spell. */
BattleWeapon weapon_kamec_obaba_recover_magic = {
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
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS, // special
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
 * Unit data of Kammy Koopa in the Palace of Shadow: 50 HP, level 48;
 * names its parts, status table and init script.
 */
BattleUnitKind unit_boss_kamec_obaba = {
    145,
    "btl_un_kamec_obaba",
    50,
    0,
    1,
    1,
    48,
    0,
    0,
    100,
    0,
    50,
    6,
    42,
    42,
    7,
    42,
    0.0f,
    21.0f,
    0.0f,
    0,
    0,
    20.0f,
    20.0f,
    0.0f,
    21.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    18.0f,
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
    "SFX_BOSS_KAMEBABA_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_FLOATING,
    &regist,
    2,
    parts,
    init_event,
    data_table,
};

/**
 * Defence of Kammy Koopa against each element (normal, fire, ice, explosion, electric):
 * none, so every hit does its full damage.
 */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/**
 * Damage modifiers of Kammy Koopa per element (normal, fire, ice, explosion, electric):
 * none, so no element is a weakness, an immunity or a heal.
 */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Demo values of the status vulnerability of Kammy Koopa:
 * percent chance that each status takes hold (100 is normal); immune to Fright, Gale Force;
 * strongly resistant to Sleep, Stop, Dizzy, Confuse, Frozen, Tiny, Attack Down, Defense Down, Allergic,
 * Slow, Instant KO.
 */
static StatusVulnerability regist = {40, 40, 40, 100, 40, 100, 100, 40, 100, 40, 100, 40, 100, 40, 40, 0, 0, 100, 40, 100, 100, 5};
#else
/**
 * JP, US and PAL values of the status vulnerability of Kammy Koopa:
 * percent chance that each status takes hold (100 is normal); immune to Fright, Gale Force;
 * strongly resistant to Sleep, Stop, Confuse, Frozen, Allergic, Slow, Instant KO.
 */
static StatusVulnerability regist = {40, 40, 60, 100, 40, 100, 100, 40, 100, 60, 100, 60, 100, 80, 40, 0, 0, 100, 40, 100, 100, 5};
#endif

/** Pose table of Kammy Koopa: animation names for each pose type (idle, walk, hurt, attack and so on). */
static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {BTL_POSE_NORMAL, "S_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "D_1"},
    {BTL_POSE_DAMAGE, "D_1"},
    {BTL_POSE_RUN, "R_1"},
    {BTL_POSE_WALK, "W_1"},
    {BTL_POSE_DANGER, "X_1"},
    {BTL_POSE_PERIL, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

/**
 * Pose table of Kammy Koopa while in the air: animation names for each pose type (idle, walk, hurt, attack
 * and so on).
 */
static PoseTableEntry pose_table_sky[] = {
    {1, "N_2"},
    {2, "Y_2"},
    {9, "Y_2"},
    {5, "K_2"},
    {4, "X_2"},
    {3, "X_2"},
    {BTL_POSE_NORMAL, "S_2"},
    {29, "Q_2"},
    {30, "Q_2"},
    {31, "D_2"},
    {BTL_POSE_DAMAGE, "D_2"},
    {BTL_POSE_RUN, "R_2"},
    {BTL_POSE_WALK, "W_2"},
    {BTL_POSE_DANGER, "X_2"},
    {BTL_POSE_PERIL, "X_2"},
    {BTL_POSE_TALK, "T_2"},
    {BTL_POSE_STAY_DEFAULT, "S_2"},
};

/**
 * Pose table of Kammy Koopa once defeated: animation names for each pose type (idle, walk, hurt, attack and
 * so on).
 */
static PoseTableEntry pose_table_dead[] = {
    {BTL_POSE_NORMAL, "D_3"},
    {BTL_POSE_DAMAGE, "D_3"},
    {BTL_POSE_STAY_DEFAULT, "D_3"},
};

/**
 * Data table of Kammy Koopa: event scripts and values the battle looks up by tag (damage reactions, dodge,
 * first strike and so on).
 */
static BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

/** Parts of Kammy Koopa: 2 parts with their hit boxes, defence tables and pose tables. */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_kamec_obaba", "c_kamek_bb", 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 0.0f, 0.0f, 40.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, 0, pose_table_sky},
    {2, "btl_un_kamec_obaba", "c_kamek_bb", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
};

/**
 * Camera helper of the Bowser fight: moves the battle camera to a close view of Kammy Koopa (the unit in GW(9));
 * the view is higher when her unit work 0 is 1 (she is flying on her broom).
 */
static EVT_BEGIN(kamec_obaba_zoom)
    CALL(btlevtcmd_GetUnitWork, GW(9), UW_BOSS_KAMEC_OBABA_FLYING, LW(1))
    CALL(evt_btl_camera_set_mode, 0, 3)
    IF_INT_EQUAL(LW(1), 1)
        CALL(evt_btl_camera_set_moveto, 0, 135, 106, 296, 135, 55, -402, 30, 11)
    ELSE
        CALL(evt_btl_camera_set_moveto, 0, 140, 34, 296, 140, 50, -402, 30, 11)
    END_IF
    WAIT_FRAMES(37)
    RETURN
EVT_END()

/**
 * Init event of Kammy Koopa: installs her wait, phase, attack,
 * damage and confusion events and sets her unit work: 0 = 1 (flying), 1 and 2 = 0 (turn counters).
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_KAMEC_OBABA_FLYING, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_KAMEC_OBABA_FLYING_DAMAGE, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_KAMEC_OBABA_GROUNDED_TURNS, 0)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MOVE1L"), STRING("SFX_BOSS_KAMEBABA_MOVE1R"), 0, 15, 15)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MOVE1L"), STRING("SFX_BOSS_KAMEBABA_MOVE1R"), 0, 8, 8)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage event of Kammy Koopa: default damage handling,
 * then if she is flying and the hit is strong enough (total damage compared to a limit) she is knocked off her
 * broom and dmg_fall_event runs.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_INSTANT_KILL, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, DAMAGE_FLAG_LAST_HIT, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, LW(10), UW_BOSS_KAMEC_OBABA_FLYING, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_GetTotalDamage, LW(10), LW(1))
        CALL(btlevtcmd_GetUnitWork, LW(10), UW_BOSS_KAMEC_OBABA_FLYING_DAMAGE, LW(0))
        ADD(LW(0), LW(1))
        CALL(btlevtcmd_SetUnitWork, LW(10), UW_BOSS_KAMEC_OBABA_FLYING_DAMAGE, LW(0))
        IF_INT_GREATER(LW(0), 1)
            CALL(btlevtcmd_WaitAttackEnd)
            CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_SELF)
            CALL_CHILD(dmg_fall_event)
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        END_IF
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * Event run when Kammy Koopa is knocked off her broom:
 * she falls to the ground (D_2) and her broom (part 2) drops separately,
 * then she stands on the ground (unit work 0 = 0) and can be hit normally.
 */
static EVT_BEGIN(dmg_fall_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_FLOATING)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("D_2"))
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
    CALL(btlevtcmd_SetTalkPoseType, BTL_UNIT_SELF, BTL_POSE_TALK)
    CALL(btlevtcmd_SetStayPoseType, BTL_UNIT_SELF, BTL_POSE_STAY)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_DAMAGE)
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("H_1"))
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 2, 255)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
        WAIT_FRAMES(80)
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
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_DOWN1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 0, LW(2))
    WAIT_MS(500)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_KAMEC_OBABA_FLYING, 0)
    RETURN
EVT_END()

/**
 * Dead event of Kammy Koopa: if she was still flying she first falls.
 * Depending on how far the fight has gone (GW(10)), she says stg8_las_100_01 or stg8_las_100_03,
 * sets GW(11) so Bowser reacts to it, and the common slow death sequence runs.
 */
static EVT_BEGIN(dead_event)
    DEBUG_PUT_MSG(STRING("カメックオババ　死亡"))
    SET_VALUE(GW(11), 1)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_WaitAttackEnd)
    DEBUG_PUT_MSG(STRING("カメックオババ　死亡イベント開始"))
    CALL(btlevtcmd_GetUnitWork, LW(10), UW_BOSS_KAMEC_OBABA_FLYING, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL_CHILD(dmg_fall_event)
    END_IF
    SWITCH(GW(10))
        CASE_EQUAL(0)
        DEBUG_PUT_MSG(STRING("カメックオババ　死亡イベント　クッパ生存"))
        CALL(btlevtcmd_StatusWindowOnOff, 0)
        CALL_CHILD(kamec_obaba_zoom)
        CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("T_3"))
        CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("D_3"))
        CALL(evt_msg_print, 2, STRING("stg8_las_100_01"), 0, BTL_UNIT_SELF)
        WAIT_MS(200)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("D_3"))
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_dead))
        SET_VALUE(GW(11), 2)
        SET_VALUE(LW(10), -2)
        CALL_CHILD(subsetevt_dead_core_nospin_norotate)
        CALL(btlevtcmd_StatusWindowOnOff, 1)
        CASE_EQUAL(1)
        DEBUG_PUT_MSG(STRING("カメックオババ　死亡イベント　同時に死亡"))
        LOOP(0)
            IF_INT_EQUAL(GW(10), 2)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("D_3"))
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_dead))
        SET_VALUE(GW(11), 2)
        SET_VALUE(LW(10), -2)
        CALL_CHILD(subsetevt_dead_core_nospin_norotate)
        CASE_EQUAL(2)
        DEBUG_PUT_MSG(STRING("カメックオババ　死亡イベント　クッパ死亡"))
        CALL(btlevtcmd_StatusWindowOnOff, 0)
        CALL_CHILD(kamec_obaba_zoom)
        CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("D_1"))
        CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("D_1"))
        CALL(evt_msg_print, 2, STRING("stg8_las_100_03"), 0, BTL_UNIT_SELF)
        WAIT_MS(200)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("D_3"))
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_dead))
        SET_VALUE(GW(11), 2)
        SET_VALUE(LW(10), -2)
        CALL_CHILD(subsetevt_dead_core_nospin_norotate)
        CALL(btlevtcmd_StatusWindowOnOff, 1)
    END_SWITCH
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/**
 * Phase event of Kammy Koopa: before the player phase, if she is not in a state that stops her acting,
 * it manages her flying state (unit work 0) and counters, getting back on her broom after a few turns.
 */
static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_get_turn, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_INSTANT_KILL, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_KAMEC_OBABA_FLYING, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_AddUnitWork, BTL_UNIT_SELF, UW_BOSS_KAMEC_OBABA_GROUNDED_TURNS, 1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_KAMEC_OBABA_GROUNDED_TURNS, LW(0))
    IF_INT_LESS(LW(0), 3)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, 300, LW(1), LW(2), 0, -1, 0)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, UNIT_ATTR_FLOATING)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_sky))
    CALL(btlevtcmd_SetTalkPoseType, BTL_UNIT_SELF, BTL_POSE_TALK)
    CALL(btlevtcmd_SetStayPoseType, BTL_UNIT_SELF, BTL_POSE_STAY)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        LOOP(0)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_MS(166)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, -1)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), 40, LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), 40, LW(2), 60, 0, 4, 0, -1)
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 40, LW(2))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    DELETE_EVENT(LW(15))
    WAIT_MS(500)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_KAMEC_OBABA_FLYING, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_KAMEC_OBABA_FLYING_DAMAGE, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_KAMEC_OBABA_GROUNDED_TURNS, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    LABEL(99)
    RETURN
EVT_END()

/**
 * Attack event of Kammy Koopa: can use an item;
 * otherwise draws a number to pick her action, preferring support spells for Bowser (magic_select_pri_koopa)
 * or herself (magic_select_pri_obaba): Dekadeka, Katikati, Biribiri, Trans, Recover,
 * or the magic attack on the party.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        // Kammy uses an enemy item if she has one.
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_get_turn, LW(0))
    DEBUG_PUT_REG(LW(0))
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LW(9), PTR(&weapon_kamec_obaba_attack_magic))
        CALL_CHILD(attack_magic_event)
        GOTO(99)
    END_IF
    SET_VALUE(LW(5), 0)
    CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(1))
    MULTIPLY(LW(0), 100)
    DIVIDE(LW(0), LW(1))
    SWITCH(LW(0))
        CASE_LESS(25)
        SET_VALUE(LW(5), 25)
        CASE_LESS(50)
        SET_VALUE(LW(5), 10)
        CASE_LESS(75)
        SET_VALUE(LW(5), 5)
    END_SWITCH
    SET_VALUE(LW(6), 0)
    IF_INT_EQUAL(GW(10), 0)
        CALL(btlevtcmd_GetHp, GW(8), LW(0))
        CALL(btlevtcmd_GetMaxHp, GW(8), LW(1))
        MULTIPLY(LW(0), 100)
        DIVIDE(LW(0), LW(1))
        SWITCH(LW(0))
            CASE_LESS(25)
            SET_VALUE(LW(6), 25)
            CASE_LESS(50)
            SET_VALUE(LW(6), 10)
            CASE_LESS(75)
            SET_VALUE(LW(6), 5)
        END_SWITCH
    END_IF
    SET_VALUE(LW(7), 0)
    SET_VALUE(LW(8), 0)
    SET_VALUE(LW(10), 0)
    SET_VALUE(LW(11), 0)
    SET_VALUE(LW(9), PTR(&weapon_kamec_obaba_dekadeka_magic))
    // She looks for a support spell to cast on herself.
    CALL_CHILD(magic_select_pri_obaba)
    IF_INT_NOT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckStatus, LW(3), STATUS_ELECTRIC, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            SET_VALUE(LW(8), 10)
        END_IF
        CALL(btlevtcmd_CheckStatus, LW(3), STATUS_INVISIBLE, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            SET_VALUE(LW(10), 10)
        END_IF
    END_IF
    SET_VALUE(LW(13), LW(3))
    SET_VALUE(LW(14), LW(4))
    // Or she looks for one to cast on Bowser.
    CALL_CHILD(magic_select_pri_koopa)
    IF_INT_NOT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckStatus, LW(3), STATUS_DEFENSE_UP, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            SET_VALUE(LW(7), 10)
        END_IF
        SET_VALUE(LW(11), 10)
    END_IF
    LABEL(10)
    SET_VALUE(LW(1), LW(5))
    ADD(LW(1), LW(6))
    ADD(LW(1), LW(7))
    ADD(LW(1), LW(8))
    ADD(LW(1), LW(10))
    ADD(LW(1), LW(11))
    ADD(LW(1), 50)
    SUBTRACT(LW(1), 1)
    CALL(evt_sub_random, LW(1), LW(0))
    SET_VALUE(LW(1), LW(5))
    ADD(LW(1), LW(6))
    IF_INT_LESS(LW(0), LW(1))
        SET_VALUE(LW(9), PTR(&weapon_kamec_obaba_recover_magic))
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
        IF_INT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL_CHILD(subsetevt_confuse_flustered)
                RETURN
            END_IF
            GOTO(99)
        END_IF
        CALL(btlevtcmd_GetHp, LW(3), LW(0))
        CALL(btlevtcmd_GetMaxHp, LW(3), LW(1))
        IF_INT_EQUAL(LW(0), LW(1))
            GOTO(10)
        END_IF
        // She casts the chosen spell (heal, Defense up, electric charge, invisibility or growth).
        CALL_CHILD(recover_magic_event)
        GOTO(99)
    END_IF
    ADD(LW(1), LW(7))
    IF_INT_LESS(LW(0), LW(1))
        SET_VALUE(LW(9), PTR(&weapon_kamec_obaba_katikati_magic))
        CALL_CHILD(katikati_magic_event)
        GOTO(99)
    END_IF
    ADD(LW(1), LW(8))
    IF_INT_LESS(LW(0), LW(1))
        SET_VALUE(LW(9), PTR(&weapon_kamec_obaba_biribiri_magic))
        SET_VALUE(LW(3), LW(13))
        SET_VALUE(LW(4), LW(14))
        CALL_CHILD(biribiri_magic_event)
        GOTO(99)
    END_IF
    ADD(LW(1), LW(10))
    IF_INT_LESS(LW(0), LW(1))
        SET_VALUE(LW(9), PTR(&weapon_kamec_obaba_trans_magic))
        SET_VALUE(LW(3), LW(13))
        SET_VALUE(LW(4), LW(14))
        CALL_CHILD(trans_magic_event)
        GOTO(99)
    END_IF
    ADD(LW(1), LW(11))
    IF_INT_LESS(LW(0), LW(1))
        SET_VALUE(LW(9), PTR(&weapon_kamec_obaba_dekadeka_magic))
        CALL_CHILD(dekadeka_magic_event)
        GOTO(99)
    ELSE
        SET_VALUE(LW(9), PTR(&weapon_kamec_obaba_attack_magic))
        // Otherwise she casts the magic attack at the party.
        CALL_CHILD(attack_magic_event)
        GOTO(99)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Casting animation, ground version, first half:
 * Kammy raises her wand through the A_1A to A_1E poses with the spell sparkles,
 * and a different effect is shown when the spell is the attack magic.
 */
static EVT_BEGIN(ground_magic_common_event1)
    BEGIN_SIBLING_EVENT
        LOOP(2)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MAGIC1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(40)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(eff_staff, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1A"))
    WAIT_FRAMES(60)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MAGIC4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1B"))
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1C"))
    WAIT_FRAMES(30)
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(10)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MAGIC8"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1D"))
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1E"))
    IF_INT_NOT_EQUAL(LW(9), PTR(&weapon_kamec_obaba_attack_magic))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MAGIC2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(eff_magic_support, BTL_UNIT_SELF, 0)
    END_IF
    RETURN
EVT_END()

/** Casting animation, ground version, second half (A_2A to A_2C). */
static EVT_BEGIN(ground_magic_common_event2)
    BEGIN_SIBLING_EVENT
        LOOP(2)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MAGIC1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(40)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(eff_staff, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1A"))
    WAIT_FRAMES(60)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MAGIC6"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2A"))
    WAIT_FRAMES(40)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MAGIC7"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2B"))
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2C"))
    IF_INT_NOT_EQUAL(LW(9), PTR(&weapon_kamec_obaba_attack_magic))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MAGIC2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(eff_magic_support, BTL_UNIT_SELF, 1)
    END_IF
    RETURN
EVT_END()

/** Casting animation in the air (A_3A to A_3D) when she is flying on her broom. */
static EVT_BEGIN(sky_magic_common_event)
    BEGIN_SIBLING_EVENT
        LOOP(2)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MAGIC1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(40)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(eff_staff, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3A"))
    WAIT_FRAMES(60)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MAGIC8"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3B"))
    WAIT_FRAMES(35)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MAGIC7"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3C"))
    WAIT_FRAMES(15)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3D"))
    IF_INT_NOT_EQUAL(LW(9), PTR(&weapon_kamec_obaba_attack_magic))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MAGIC2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(eff_magic_support, BTL_UNIT_SELF, 1)
    END_IF
    RETURN
EVT_END()

/**
 * Common casting script of Kammy Koopa when the target is a different unit than the caster:
 * runs the ground or the air animation depending on whether she is flying (unit work 0).
 */
static EVT_BEGIN(magic_common_event1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_KAMEC_OBABA_FLYING, LW(0))
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
 * Common casting script of Kammy Koopa for the second half of a spell:
 * runs the ground or air second half depending on whether she is flying.
 */
static EVT_BEGIN(magic_common_event2)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_KAMEC_OBABA_FLYING, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL_CHILD(ground_magic_common_event2)
    ELSE
        CALL_CHILD(sky_magic_common_event)
    END_IF
    RETURN
EVT_END()

/**
 * Helper child script of the Kammy attacks: given the pre-check result in LW(5),
 * makes the target start its dodge reaction (avoid type 38, 39 or 40).
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
 * Magic attack of Kammy Koopa (weapon_kamec_obaba_attack_magic):
 * she casts a blast at one party member, who can dodge it
 * or takes the damage with the action command defence check.
 */
static EVT_BEGIN(attack_magic_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // Pick a target for the attack; a confused unit that has none flusters.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    // Announce the attack; the camera swings to follow it.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // She conjures a magic blast and sends it at one party member.
    CALL_CHILD(magic_common_event1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KAMEBABA_MAGIC3_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_btl_camera_set_mode, 0, 0)
    // Find out whether the attack will connect or miss.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
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
        // The attack misses or is dodged.
        LABEL(90)
        BEGIN_SIBLING_EVENT
            WAIT_FRAMES(1)
            LOOP(0)
                CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(0))
                IF_INT_EQUAL(LW(0), -1)
                    CALL(eff_magic_get_posX, BTL_UNIT_SELF, LW(0))
                    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
                    IF_INT_LESS_OR_EQUAL(LW(0), LW(6))
                        // The party member can dodge it as it passes.
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
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(0), -57)
        ADD(LW(1), 10)
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
        CALL(btlevtcmd_GetStageSize, LW(10), EVT_NULLPTR, EVT_NULLPTR)
        CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(0))
        MULTIPLY(LW(10), LW(0))
        SUBTRACT(LW(11), 5)
        CALL(eff_magic, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 60)
        WAIT_FRAMES(60)
        GOTO(98)
        // The attack connects.
        LABEL(91)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(0), -57)
        ADD(LW(1), 10)
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
        CALL(eff_magic, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 45)
        WAIT_FRAMES(45)
        // Deal the damage, reduced by the action command defence.
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
        GOTO(98)
        // Wrap up the attack.
        LABEL(98)
        WAIT_FRAMES(30)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY)
        // The attack is over; back to waiting.
        LABEL(99)
        CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
        RETURN
EVT_END()

/**
 * Event script: Kammy Koopa picks the target of her support magic in her own favour.
 * Bowser (unit GW(8), eligible while GW(10) is 0) gets weight 25
 * and Kammy herself (-2, eligible while GW(11) is 0) weight 75.
 * Returns the target unit in LW(3) and the part 1 in LW(4).
 */
EVT_BEGIN(magic_select_pri_obaba)
    SET_VALUE(LW(5), 0)
    SET_VALUE(LW(6), 0)
    IF_INT_EQUAL(GW(10), 0)
        SET_VALUE(LW(5), 25)
    END_IF
    IF_INT_EQUAL(GW(11), 0)
        SET_VALUE(LW(6), 75)
    END_IF
    SET_VALUE(LW(1), LW(5))
    ADD(LW(1), LW(6))
    SUBTRACT(LW(1), 1)
    CALL(evt_sub_random, LW(1), LW(0))
    IF_INT_LESS(LW(0), LW(5))
        SET_VALUE(LW(3), GW(8))
        SET_VALUE(LW(4), 1)
    ELSE
        SET_VALUE(LW(3), -2)
        SET_VALUE(LW(4), 1)
    END_IF
    RETURN
EVT_END()

/**
 * Event script: the same choice weighted in Bowser's favour:
 * Bowser (GW(8)) has weight 75 and Kammy herself (-2) weight 25, each only while GW(10) / GW(11) is 0.
 * Returns the target unit in LW(3) and the part 1 in LW(4).
 */
EVT_BEGIN(magic_select_pri_koopa)
    SET_VALUE(LW(5), 0)
    SET_VALUE(LW(6), 0)
    IF_INT_EQUAL(GW(10), 0)
        SET_VALUE(LW(5), 75)
    END_IF
    IF_INT_EQUAL(GW(11), 0)
        SET_VALUE(LW(6), 25)
    END_IF
    SET_VALUE(LW(1), LW(5))
    ADD(LW(1), LW(6))
    SUBTRACT(LW(1), 1)
    CALL(evt_sub_random, LW(1), LW(0))
    IF_INT_LESS(LW(0), LW(5))
        SET_VALUE(LW(3), GW(8))
        SET_VALUE(LW(4), 1)
    ELSE
        SET_VALUE(LW(3), -2)
        SET_VALUE(LW(4), 1)
    END_IF
    RETURN
EVT_END()

/**
 * Dekadeka spell of Kammy Koopa (weapon_kamec_obaba_dekadeka_magic):
 * she casts it on one ally, Bowser or herself: Huge (size +2) for 3 turns.
 */
static EVT_BEGIN(dekadeka_magic_event)
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
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
    CALL_CHILD(magic_common_event1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    WAIT_FRAMES(30)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Katikati spell of Kammy Koopa: uses the same casting script as dekadeka_magic_event with
 * weapon_kamec_obaba_katikati_magic: Defense +3 for 3 turns on one ally.
 */
static EVT_BEGIN(katikati_magic_event)
    CALL_CHILD(dekadeka_magic_event)
    RETURN
EVT_END()

/**
 * Biribiri spell of Kammy Koopa: uses the same casting script as dekadeka_magic_event with
 * weapon_kamec_obaba_biribiri_magic: Electrified for 3 turns on one ally.
 */
static EVT_BEGIN(biribiri_magic_event)
    CALL_CHILD(dekadeka_magic_event)
    RETURN
EVT_END()

/**
 * Trans spell of Kammy Koopa: uses the same casting script as dekadeka_magic_event with
 * weapon_kamec_obaba_trans_magic: Invisible for 3 turns on one ally.
 */
static EVT_BEGIN(trans_magic_event)
    CALL_CHILD(dekadeka_magic_event)
    RETURN
EVT_END()

/**
 * Recover spell of Kammy Koopa: she heals the target by 8 HP with the recovery effect;
 * if the target is the unit in GW(8) (Bowser) the effect is shown on him.
 */
static EVT_BEGIN(recover_magic_event)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL_CHILD(magic_common_event1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_RecoverHp, LW(3), LW(4), 8)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    IF_INT_EQUAL(LW(3), GW(8))
        ADD(LW(0), -30)
        ADD(LW(1), 100)
        ADD(LW(2), 10)
    ELSE
        ADD(LW(1), 50)
        ADD(LW(2), 10)
    END_IF
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, LW(0), LW(1), LW(2), 8, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(40)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Script helper: plays a ring of stardust sparkles near the unit args[0] on a support cast:
 * type 0 at 10 units high and type 1 at 50 units high, 30 units in front of it.
 */
static USER_FUNC(eff_magic_support) {
    EvtWord* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 type = evtGetValue(event, args[1]);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;

    BtlUnit_GetPos(unit, &x, &y, &z);
    switch (type) {
        case 0:
            x += 30.0f * unit->sizeMultiplier * unit->faceDirection;
            y += 10.0f * unit->sizeMultiplier;
            z += 5.0f;
            effStardustEntry(6, 5, 30, x, y, z, 40.0f, 40.0f);
            break;
        case 1:
            x += 30.0f * unit->sizeMultiplier * unit->faceDirection;
            y += 50.0f * unit->sizeMultiplier;
            z += 5.0f;
            effStardustEntry(6, 5, 30, x, y, z, 40.0f, 40.0f);
            break;
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper: returns in args[1] the current X offset of the magic effect stored in the unit args[0]
 * (unit->work[UW_BOSS_KAMEC_OBABA_MAGIC_EFFECT]), so the script can wait for the spell to reach a position.
 */
static USER_FUNC(eff_magic_get_posX) {
    EvtWord* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);

    evtSetFloat(event, args[1], ((EffMagic1N64Work*)((EffectEntry*)unit->work[UW_BOSS_KAMEC_OBABA_MAGIC_EFFECT])->userdata)->offset.x);
    return EVT_RETURN_DONE;
}

/**
 * Script helper: fires Kammy's magic bolt (effMagic1N64, type 0) from the tip of her wand towards
 * the point (args[1], args[2], args[3]), lasting args[4] frames, and stores it in unit->work[UW_BOSS_KAMEC_OBABA_MAGIC_EFFECT].
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
    x += 28.0f * unit->sizeMultiplier * unit->faceDirection;
    y += 20.0f * unit->sizeMultiplier;
    z += 5.0f;
    eff = effMagic1N64Entry(0, type, x, y, z, a, b, c);
    unit->work[UW_BOSS_KAMEC_OBABA_MAGIC_EFFECT] = (EvtWord)eff;
    ((EffMagic1N64Work*)eff->userdata)->scale = unit->sizeMultiplier;
    return EVT_RETURN_DONE;
}

/**
 * Script helper (runs every frame while blocked):
 * keeps a Thunder Flare charging effect on the tip of Kammy's staff, following her position and size,
 * until the effect ends.
 */
static USER_FUNC(eff_staff) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;
    f32* wk;

    if (isFirstCall) {
        unit->work[UW_BOSS_KAMEC_OBABA_STAFF_EFFECT] = (EvtWord)effThunderflareN64Entry(0, 60, 0.0f, -1000.0f, 0.0f, 1.0f);
    }
    if (!(((EffectEntry*)unit->work[UW_BOSS_KAMEC_OBABA_STAFF_EFFECT])->flags & EFFECT_FLAG_IN_USE)) {
        return EVT_RETURN_DONE;
    }
    wk = ((EffectEntry*)unit->work[UW_BOSS_KAMEC_OBABA_STAFF_EFFECT])->userdata;
    wk[10] = unit->sizeMultiplier;
    BtlUnit_GetPos(unit, &x, &y, &z);
    wk[2] = x + 30.0f * unit->sizeMultiplier * unit->faceDirection;
    wk[3] = y + 35.0f * unit->sizeMultiplier;
    wk[4] = 5.0f + z;
    return EVT_RETURN_BLOCK;
}

/** Wait event of Kammy Koopa: plays her idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
