// Battle unit Sky-Blue Spiny (`hyper_togezo`): tst.rel's copy of rels/jon/src/unit/unit_hyper_togezo.c.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "evt/evt_snd.h"

// Unit work slots of the Sky-Blue Spiny (btlevtcmd_SetUnitWork / GetUnitWork).
enum {
    UW_HYPER_TOGEZO_GUARDING = 0,   // 1 while curled up in its guard
    UW_HYPER_TOGEZO_SPINNING = 1,   // 1 while the spin loop of its attacks runs
    UW_HYPER_TOGEZO_SPIN_SPEED = 2, // rotation per frame of that spin
    UW_HYPER_TOGEZO_CHARGED = 3     // 1 after a charge-up: the next attack is the normal one
};

BattleUnitKind unit_hyper_togezo;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleUnitDefense defence_turn;
static BattleUnitDefenseAttr defence_attr_turn;
static StatusVulnerability regist_turn;
static BattleUnitDefense defence_guard;
static BattleUnitDefenseAttr defence_attr_guard;
static StatusVulnerability regist_guard;
static PoseTableEntry pose_table[15];
#if VERSION <= VERSION_DEMO_US
static PoseTableEntry pose_table_turn[12];
#else
static PoseTableEntry pose_table_turn[14];
#endif
static PoseTableEntry pose_table_guard[12];
static BattleDataEntry data_table[5];
static BattleDataEntry data_table_turn[3];
static BattleDataEntry data_table_guard[4];
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_togezo_attack;
static BattleWeapon weapon_togezo_charge;
static EvtWord init_event[52];
static EvtWord dmg_avoid_counter_thorn_event[61];
static EvtWord damage_event[10];
static EvtWord dmg_turn_event[84];
static EvtWord attack_event[109];
static EvtWord normal_attack_event[813];
static EvtWord guard_event[95];
static EvtWord guard_cancel_event[89];
static EvtWord charge_event[102];
static EvtWord wait_event[6];

/**
 * Unit definition of the Sky-Blue Spiny: 6 HP, level 22, 1 part, with its sounds, init script and data table.
 */
BattleUnitKind unit_hyper_togezo = {
    160,
    "btl_un_hyper_togezo",
    6,
    0,
    1,
    1,
    22,
    0,
    1,
    70,
#if VERSION <= VERSION_DEMO_US
    3,
#else
    0,
#endif
    50,
    9999,
    32,
    30,
    4,
    30,
    0.0f,
    15.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    0.0f,
    12.0f,
    16.0f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    32.0f,
    30.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_TOGEZO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/** Defence of the Sky-Blue Spiny: 4 against every kind of attack. */
static BattleUnitDefense defence = {{4, 4, 4, 4, 4}};

/** Damage-type modifiers of the Sky-Blue Spiny: none, no special weakness or immunity. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
/**
 * Status vulnerability of the Sky-Blue Spiny (100% is the normal chance): resists Sleep 70%, Stop 70%, Dizzy
 * 70%, Confusion 70%, Freeze 60%, Tiny 70%, Attack Down 70%, Defense Down 70%, Allergic 70%, Fright 80%, Gale
 * Force 60%, Slow 70% and instant KO 50%.
 */
static StatusVulnerability regist = {70, 70, 70, 100, 70, 100, 100, 60, 100, 70, 100, 70, 100, 70, 70, 80, 60, 100, 70, 100, 100, 50};
#else
static StatusVulnerability regist = {60, 70, 60, 100, 60, 100, 100, 50, 100, 85, 100, 85, 100, 90, 70, 80, 10, 100, 70, 100, 100, 50};
#endif

/**
 * Defence of the Sky-Blue Spiny while it is flipped onto its back: none, so it takes full damage from every
 * kind of attack.
 */
static BattleUnitDefense defence_turn = {0};

/**
 * Damage-type modifiers of the Sky-Blue Spiny while it is flipped onto its back: none, no special weakness or
 * immunity.
 */
static BattleUnitDefenseAttr defence_attr_turn = {0};

/**
 * Status vulnerability of the Sky-Blue Spiny while it is flipped onto its back (100% is the normal chance):
 * takes every status at the normal rate.
 */
static StatusVulnerability regist_turn = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

/**
 * Defence of the Sky-Blue Spiny while it is curled up guarding:
 * defence 99 against every kind of hit, so no attack does damage.
 */
static BattleUnitDefense defence_guard = {{99, 99, 99, 99, 99}};

/**
 * Damage-type modifiers of the Sky-Blue Spiny while it is curled up guarding: it is immune to every kind of
 * attack.
 */
static BattleUnitDefenseAttr defence_attr_guard = {{2, 2, 2, 2, 2}};

/**
 * Status vulnerability of the Sky-Blue Spiny while it is curled up guarding (100% is the normal chance):
 * takes every status at the normal rate.
 */
static StatusVulnerability regist_guard = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

/**
 * Pose table of the Sky-Blue Spiny: its 15 battle poses (status, hurt and action) and the animation each one
 * plays; the idle animation is `TGZ_S_1`.
 */
static PoseTableEntry pose_table[] = {
    {1, "TGZ_N_1"},
    {2, "TGZ_Y_1"},
    {9, "TGZ_Y_1"},
    {5, "TGZ_K_1"},
    {4, "TGZ_X_1"},
    {3, "TGZ_X_1"},
    {28, "TGZ_S_1"},
    {29, "TGZ_Q_1"},
    {30, "TGZ_Q_1"},
    {31, "TGZ_A_1"},
    {39, "TGZ_D_1"},
    {40, "TGZ_W_1"},
    {42, "TGZ_R_1"},
    {BTL_POSE_TALK, "TGZ_T_1"},
    {BTL_POSE_STAY_DEFAULT, "TGZ_S_1"},
};

/**
 * Pose table of the Sky-Blue Spiny while it is flipped onto its back: its 14 battle poses (status, hurt and
 * action) and the animation each one plays; the idle animation is `TGZ_S_2`.
 */
static PoseTableEntry pose_table_turn[] = {
    {1, "TGZ_N_2"},
    {2, "TGZ_Y_2"},
    {9, "TGZ_Y_2"},
    {5, "TGZ_K_2"},
    {4, "TGZ_X_2"},
    {3, "TGZ_X_2"},
    {28, "TGZ_S_2"},
    {29, "TGZ_Q_2"},
    {30, "TGZ_Q_2"},
    {31, "TGZ_S_1"},
    {39, "TGZ_D_3"},
#if VERSION >= VERSION_JP
    {40, "TGZ_W_1"},
    {42, "TGZ_R_1"},
#endif
    {BTL_POSE_STAY_DEFAULT, "TGZ_S_2"},
};

/**
 * Pose table of the Sky-Blue Spiny while it is curled up guarding: its 12 battle poses (status, hurt and
 * action) and the animation each one plays; the idle animation is `TGZ_P_1`.
 */
static PoseTableEntry pose_table_guard[] = {
    {1, "TGZ_P_1"},
    {2, "TGZ_P_1"},
    {9, "TGZ_P_1"},
    {5, "TGZ_P_1"},
    {4, "TGZ_P_1"},
    {3, "TGZ_P_1"},
    {28, "TGZ_P_1"},
    {29, "TGZ_P_1"},
    {30, "TGZ_P_1"},
    {31, "TGZ_P_1"},
    {39, "TGZ_P_1"},
    {BTL_POSE_STAY_DEFAULT, "TGZ_P_1"},
};

/**
 * Data table of the Sky-Blue Spiny: event 13 runs dmg_turn_event; events 37, 39 run
 * dmg_avoid_counter_thorn_event when an attacker is hurt by its spikes; event 48 does nothing
 * (btldefaultevt_Dummy).
 */
static BattleDataEntry data_table[] = {
    {13, dmg_turn_event},
    {37, dmg_avoid_counter_thorn_event},
    {39, dmg_avoid_counter_thorn_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/**
 * Data table of the Sky-Blue Spiny while it is flipped onto its back: event 13 runs dmg_turn_event; event 48
 * does nothing (btldefaultevt_Dummy).
 */
static BattleDataEntry data_table_turn[] = {
    {13, dmg_turn_event},
    {48, btldefaultevt_Dummy},
    {0},
};

/**
 * Data table of the Sky-Blue Spiny while it is curled up guarding: events 37, 39 run
 * dmg_avoid_counter_thorn_event when an attacker is hurt by its spikes; event 48 does nothing
 * (btldefaultevt_Dummy).
 */
static BattleDataEntry data_table_guard[] = {
    {37, dmg_avoid_counter_thorn_event},
    {39, dmg_avoid_counter_thorn_event},
    {48, btldefaultevt_Dummy},
    {0},
};

/**
 * Body of the Sky-Blue Spiny: one targetable part, the model `c_togezo_b`, with its hit box, defence tables
 * and pose table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_hyper_togezo", "c_togezo_b", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x1009, 0x5, pose_table},
};

/** Attack data of the Sky-Blue Spiny's rolling attack: hits one opposing unit for 6 damage. */
static BattleWeapon weapon_togezo_attack = {
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
    {6, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
#if VERSION <= VERSION_DEMO_US
    COUNTER_RESIST_ALL, // counterResistFlags
#else
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
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

/** Attack data of the Sky-Blue Spiny's charge-up: powers up its next attack by 6. */
static BattleWeapon weapon_togezo_charge = {
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
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    6, // chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Init script of the Sky-Blue Spiny: installs the wait, attack,
 * damage and confusion handlers (confusion reuses the attack), clears unit work 0 (guarding) and 3,
 * sets its run, walk and jump sounds and starts the wait event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_GUARDING, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_CHARGED, 0)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEZO_MOVE1L"), STRING("SFX_ENM_TOGEZO_MOVE1R"), 0, 10, 10)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEZO_MOVE1L"), STRING("SFX_ENM_TOGEZO_MOVE1R"), 0, 6, 6)
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("SFX_ENM_KURI_JUMP1"), STRING("SFX_ENM_KURI_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Spike spark shown when an attacker is hurt by (or avoids) the spiked head:
 * waits 30 frames, then spawns the toge_flush effect above the unit (45 up when Huge, 25 when Tiny, else 35).
 */
static EVT_BEGIN(dmg_avoid_counter_thorn_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_HUGE, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 45)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_TINY, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 25)
        GOTO(90)
    END_IF
    ADD(LW(1), 35)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

/**
 * Damage handler: runs the shared default damage script (btldefaultevt_Damage) with its default parameters
 * (LW(10) = -2, LW(11) = 1).
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Flips the Sky-Blue Spiny onto its back: swaps in the flipped defence, resistance, pose and data tables,
 * marks status flag 1 (flipped) with a flipped-over count of 1, turns off its spike counters on part 1,
 * plays the flip sound and drops it in two bounces.
 */
static EVT_BEGIN(dmg_turn_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence_turn))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, LW(10), LW(11), PTR(&defence_attr_turn))
    CALL(btlevtcmd_SetRegistStatus, LW(10), PTR(&regist_turn))
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_turn))
    CALL(btlevtcmd_OnStatusFlag, LW(10), STATUS_FLAG_FLIPPED)
    CALL(btlevtcmd_OffPartsCounterAttribute, LW(10), LW(11), COUNTER_ATTR_TOP_SPIKY)
    CALL(btlevtcmd_OffPartsCounterAttribute, LW(10), LW(11), COUNTER_ATTR_FRONT_SPIKY)
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table_turn))
    CALL(btlevtcmd_SetOverTurnCount, LW(10), 1)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
    CALL(evt_snd_sfxon, STRING("SFX_CONDITION_INSIDE"), 0)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 18, -1)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    RETURN
EVT_END()

/**
 * Turn-over recovery of the Sky-Blue Spiny: counts down the flipped-over count;
 * at 0 it restores the normal defence, resistance, pose and data tables, clears status flag 1,
 * turns the spike counters on part 1 back on and hops to the ground.
 */
static EVT_BEGIN(wakeup_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetOverTurnCount, LW(10), LW(0))
    SUBTRACT(LW(0), 1)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_StartWaitEvent, LW(10))
        RETURN
    END_IF
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, LW(10), LW(11), PTR(&defence_attr))
    CALL(btlevtcmd_SetRegistStatus, LW(10), PTR(&regist))
    CALL(btlevtcmd_OffStatusFlag, LW(10), STATUS_FLAG_FLIPPED)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    CALL(btlevtcmd_OnPartsCounterAttribute, LW(10), LW(11), COUNTER_ATTR_TOP_SPIKY)
    CALL(btlevtcmd_OnPartsCounterAttribute, LW(10), LW(11), COUNTER_ATTR_FRONT_SPIKY)
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table))
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 18, -1)
    CALL(btlevtcmd_StartWaitEvent, LW(10))
    RETURN
EVT_END()

/**
 * Attack script of the Sky-Blue Spiny: if it is flipped it gets up (wakeup_event);
 * after the item-use check, if it is curled up (unit work 0 = 1) it uncurls (guard_cancel_event)
 * and its turn ends.
 * If it charged on its last turn (unit work 3 = 1) it clears that and attacks (normal_attack_event).
 * Otherwise it draws lots between attacking (40),
 * curling up (guard_event, 40) and charging up (charge_event with weapon_togezo_charge, which sets unit work 3;
 * weight 20 on turn 1, else 6).
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_GetOverTurnCount, BTL_UNIT_SELF, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(wakeup_event)
        RETURN
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_GUARDING, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL_CHILD(guard_cancel_event)
        GOTO(99)
    ELSE
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_CHARGED, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_CHARGED, 0)
            CALL_CHILD(normal_attack_event)
            GOTO(99)
        END_IF
        CALL(btlevtcmd_get_turn, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_DrawLots, LW(0), 3, 40, 40, 20)
        ELSE
            CALL(btlevtcmd_DrawLots, LW(0), 3, 40, 40, 6)
        END_IF
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL_CHILD(normal_attack_event)
            CASE_EQUAL(1)
            CALL_CHILD(guard_event)
            CASE_EQUAL(2)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_CHARGED, 1)
            SET_VALUE(LW(9), PTR(&weapon_togezo_charge))
            CALL_CHILD(charge_event)
        END_SWITCH
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Sky-Blue Spiny's rolling attack (weapon_togezo_attack) at the First Strike target in a battle-flag-2
 * battle, else a sampled enemy: it curls into a ball (TGZ_P_1),
 * spins up with a hop and rolls at the target at speed 9 (the spin runs in a sibling event while unit work 1 is
 * 1, at the rate in unit work 2).
 * A miss slows it down past the target; a hit shakes the camera, applies the guard result and the damage,
 * and it bounces back in two hops.
 * After a miss, or on half of the hits, it uncurls (TGZ_S_1) and walks home;
 * on the other hits it rolls home and stays curled up in its guard stance (guard defence 99, so no hit hurts it;
 * guard tables,
 * shelled part attribute off, unit work 0 = 1).
 */
static EVT_BEGIN(normal_attack_event)
    // Picks the target: the preset first-attack target when battle flag 2 is set, otherwise a random opposing unit;
    // with no target it does nothing (or is flustered when confused).
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_togezo_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_togezo_attack), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // Declares the attack and pays its cost while the camera zooms in on the target.
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_togezo_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_togezo_attack))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(14))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(14))
    // Wind-up: it rolls up into a spiked ball (TGZ_P_1), spinning faster as it does.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEZO_TURN1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 15, 0)
    LOOP(5)
        SET_VALUE(LW(0), -36)
        MULTIPLY(LW(0), LW(14))
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, LW(0))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGZ_P_1"))
    LOOP(5)
        SET_VALUE(LW(0), -36)
        MULTIPLY(LW(0), LW(14))
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, LW(0))
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_FRAMES(5)
    // The ball keeps spinning (unit work 1 and 2 carry the spin) while it hops once, rolls on the ground (roll
    // sounds) and then speeds along the ground into the target.
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPINNING, 1)
    SET_VALUE(LW(0), -36)
    MULTIPLY(LW(0), LW(14))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPIN_SPEED, LW(0))
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPINNING, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                BREAK_LOOP
            END_IF
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPIN_SPEED, LW(0))
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_FRAMES(10)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEZO_ROLL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 30, 0, FLOAT(0.14941406f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEZO_ROLL2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(9.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, 0, 1)
    // Checks the outcome of the hit: a miss, dodge or guard goes to the no-damage branch; a connecting hit applies
    // the Action Command defence result and deals the damage.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_togezo_attack), 0, LW(5))
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
    // Miss branch: it rolls on past the target, slowing down as the spin dies away.
    LABEL(90)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEZO_ROLL5"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        SET_VALUE(LW(0), -18)
        MULTIPLY(LW(0), LW(14))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPIN_SPEED, LW(0))
        SET_VALUE(LW(0), 1)
        MULTIPLY(LW(0), LW(14))
        LOOP(18)
            CALL(btlevtcmd_AddUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPIN_SPEED, LW(0))
            WAIT_FRAMES(3)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 50)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(2.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, 0, 1)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 26)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, 0, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPINNING, 0)
    WAIT_FRAMES(10)
    GOTO(97)
    // Hit branch: the camera shakes and pulls in, the defence result is read and the damage is applied, and it
    // bounces back off the target in two hops while the spin reverses.
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEZO_ROLL4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_togezo_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_togezo_attack), 256, LW(5))
    SET_VALUE(LW(0), 36)
    MULTIPLY(LW(0), LW(14))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPIN_SPEED, -36)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 30)
    ADD(LW(2), 10)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 30, 0, FLOAT(0.5f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 30, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEZO_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 30)
    ADD(LW(2), 5)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 15, 0, FLOAT(0.5f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 15, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEZO_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        SET_VALUE(LW(0), 18)
        MULTIPLY(LW(0), LW(14))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPIN_SPEED, LW(0))
        SET_VALUE(LW(0), -1)
        MULTIPLY(LW(0), LW(14))
        LOOP(18)
            CALL(btlevtcmd_AddUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPIN_SPEED, LW(0))
            WAIT_FRAMES(2)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 18)
    ADD(LW(2), 10)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, 0, 1)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 9)
    ADD(LW(2), 5)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(0.5f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, 0, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPINNING, 0)
    WAIT_FRAMES(3)
    // Half the time it then rolls straight to the guard stance below; otherwise it unrolls here.
    CALL(evt_sub_random, 99, LW(0))
    IF_INT_LESS(LW(0), 50)
        GOTO(98)
    ELSE
        GOTO(97)
    END_IF
    // Unrolls (TGZ_S_1) with a turn sound and runs back to its home position.
    LABEL(97)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEZO_TURN2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 15, 0)
    LOOP(5)
        SET_VALUE(LW(0), 36)
        MULTIPLY(LW(0), LW(14))
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, LW(0))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGZ_S_1"))
    LOOP(5)
        SET_VALUE(LW(0), 36)
        MULTIPLY(LW(0), LW(14))
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, LW(0))
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_FRAMES(5)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGZ_S_1"))
    WAIT_MS(250)
    GOTO(99)
    // Guard stance: it stays curled up and spinning, rolls back home, then switches to its rolled-up defence,
    // vulnerability, pose and data tables (a spiky ball that hurts attackers).
    LABEL(98)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEZO_ROLL3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPINNING, 1)
    SET_VALUE(LW(0), 36)
    MULTIPLY(LW(0), LW(14))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPIN_SPEED, LW(0))
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPINNING, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
                BREAK_LOOP
            END_IF
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPIN_SPEED, LW(0))
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_SPINNING, 0)
    CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 1, PTR(&defence_guard))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 1, PTR(&defence_attr_guard))
    CALL(btlevtcmd_SetRegistStatus, BTL_UNIT_SELF, PTR(&regist_guard))
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_guard))
    CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table_guard))
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_SHELLED)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_TOGEZO_GUARDING, 1)
    WAIT_MS(250)
    GOTO(99)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Sky-Blue Spiny curls up into its guard stance:
 * plays the curl sound and a half-spin into TGZ_P_1,
 * then swaps in the guarding defence (99 to every element, so no hit hurts it),
 * defence attributes, status resistances, pose and data tables,
 * clears the shelled part attribute (0x1000) and sets unit work 0 to 1.
 */
static EVT_BEGIN(guard_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEZO_TURN1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 15, 0)
    LOOP(5)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, 36)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGZ_P_1"))
    LOOP(5)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, 36)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    WAIT_FRAMES(5)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence_guard))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, LW(10), LW(11), PTR(&defence_attr_guard))
    CALL(btlevtcmd_SetRegistStatus, LW(10), PTR(&regist_guard))
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_guard))
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table_guard))
    CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(11), PART_ATTR_SHELLED)
    CALL(btlevtcmd_SetUnitWork, LW(10), UW_HYPER_TOGEZO_GUARDING, 1)
    RETURN
EVT_END()

/**
 * The Sky-Blue Spiny uncurls from its guard stance:
 * plays the uncurl sound and a half-spin into TGZ_S_1, restores the normal defence (4), defence attributes,
 * status resistances, pose and data tables, sets the shelled part attribute (0x1000) again
 * and clears unit work 0.
 */
static EVT_BEGIN(guard_cancel_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEZO_TURN2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 15, 0)
    LOOP(5)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, -36)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGZ_S_1"))
    LOOP(5)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, -36)
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_FRAMES(5)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, LW(10), LW(11), PTR(&defence_attr))
    CALL(btlevtcmd_SetRegistStatus, LW(10), PTR(&regist))
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table))
    CALL(btlevtcmd_OnPartsAttribute, LW(10), LW(11), PART_ATTR_SHELLED)
    CALL(btlevtcmd_SetUnitWork, LW(10), UW_HYPER_TOGEZO_GUARDING, 0)
    RETURN
EVT_END()

/**
 * The Sky-Blue Spiny charges up: plays the charge sound and a crystal effect, waits a second while it hops up,
 * then applies the charge weapon (LW(9)) to itself with the guard-timing result.
 */
static EVT_BEGIN(charge_event)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    WAIT_FRAMES(40)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 15)
    ADD(LW(2), 10)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_eff64, STRING(""), STRING("crystal_n64"), 7, LW(0), LW(1), LW(2), FLOAT(1.5f), 60, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_btl_camera_set_mode, 0, 3)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, 0, FLOAT(1.0f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
        WAIT_MS(500)
        CALL(evt_btl_camera_set_mode, 0, 0)
    END_INLINE_EVENT
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, BTL_UNIT_SELF, 1, LW(9), 256, LW(5))
    RETURN
EVT_END()

/** Idle script: sets the standard waiting pose from the unit's pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
