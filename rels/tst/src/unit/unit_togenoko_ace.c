// Battle unit Dark Koopatrol (`togenoko_ace`): tst.rel's copy of rels/jon/src/unit/unit_togenoko_ace.c.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_sub.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_sub.h"
#include "evt/evt_eff.h"

// Unit work slots (btlevtcmd_SetUnitWork / GetUnitWork)
enum {
    UW_TOGENOKO_ACE_GUARDING = 0,   // 1 while it is withdrawn into its shell to guard
    UW_TOGENOKO_ACE_SPIN_STOP = 1,  // 1 stops the shell-spin loop of the shell attack
    UW_TOGENOKO_ACE_SPIN_SPEED = 2, // degrees per frame the shell spins during the shell attack
};

BattleUnitKind unit_togenoko_ace;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleUnitDefense defence_turn;
static BattleUnitDefenseAttr defence_attr_turn;
static StatusVulnerability regist_turn;
static BattleUnitDefense defence_guard;
static BattleUnitDefenseAttr defence_attr_guard;
static StatusVulnerability regist_guard;
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_turn[15];
static PoseTableEntry pose_table_guard[15];
static PoseTableEntry pose_table_guard_turn[15];
static BattleDataEntry data_table[4];
static BattleDataEntry data_table_turn[3];
static BattleDataEntry data_table_guard[4];
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_togenoko_normal_attack;
static BattleWeapon weapon_togenoko_shell_attack;
static BattleWeapon weapon_togenoko_charge;
static EvtWord init_event[37];
static EvtWord damage_event[10];
static EvtWord dmg_avoid_counter_thorn_head_event[61];
static EvtWord dmg_turn_event[116];
static BattleUnitSetup entry_togenoko;
static EvtWord attack_event[333];
static EvtWord normal_attack_event[406];
static EvtWord shell_attack_event[489];
static EvtWord charge_event[99];
static EvtWord guard_event[127];
static EvtWord guard_cancel_event[90];
static EvtWord friend_event[88];
static EvtWord wait_event[6];

/** Script helper: args[0] receives how many units of this Koopatrol kind are on the field. */
static USER_FUNC(togenoko_getnum) {
    EvtWord* args = event->args;
    s32 num = 0;
    s32 i;

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, i);
        if (unit != NULL && unit->currentKind == 0x3C) {
            num++;
        }
    }
    evtSetValue(event, args[0], num);
    return EVT_RETURN_DONE;
}

/**
 * Unit definition of the D. Koopatrol: its HP, level, sizes, sounds, status vulnerability,
 * parts and init script.
 */
BattleUnitKind unit_togenoko_ace = {
    60,
    "btl_un_togenoko_ace",
    25,
    0,
    1,
    1,
    30,
#if VERSION <= VERSION_DEMO_US
    0,
#else
    1,
#endif
    3,
    70,
    2,
    50,
    9999,
    36,
    50,
    -4,
    50,
    0.0f,
    25.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    18.0f,
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
    13.0f,
    32.0f,
    0.0f,
    0.0f,
    25.0f,
    0.0f,
    36.0f,
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
    "SFX_ENM_TOGENOKO_DAMAGED1",
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

/** Defence of the D. Koopatrol: 2 against every kind of hit. */
static BattleUnitDefense defence = {{2, 2, 2, 2, 2}};

/** Element modifiers of the D. Koopatrol: none, no element is special to it. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
/** Status vulnerability of the D. Koopatrol in the demo builds: resists most statuses. */
static StatusVulnerability regist = {40, 60, 50, 100, 50, 100, 100, 50, 100, 60, 100, 60, 100, 60, 60, 50, 50, 100, 50, 100, 100, 95};
#else
/** Status vulnerability of the D. Koopatrol in the retail builds: resists most statuses. */
static StatusVulnerability regist = {60, 65, 65, 100, 65, 100, 100, 60, 100, 85, 100, 85, 100, 90, 70, 60, 60, 100, 70, 100, 100, 95};
#endif

/** Defence of the D. Koopatrol while it is flipped on its back: none, every hit does its full damage. */
static BattleUnitDefense defence_turn = {0};

/**
 * Element modifiers of the D. Koopatrol while it is flipped on its back: none, no element is special to it.
 */
static BattleUnitDefenseAttr defence_attr_turn = {0};

/**
 * Status vulnerability of the D. Koopatrol while it is flipped on its back:
 * every status lands at the normal rate.
 */
static StatusVulnerability regist_turn = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

/**
 * Defence of the Dark Koopatrol while it is withdrawn into its shell:
 * defence 99 against every kind of hit, so no attack does damage.
 */
static BattleUnitDefense defence_guard = {{99, 99, 99, 99, 99}};

/**
 * Element modifiers of the D. Koopatrol while it is withdrawn into its shell:
 * normal, fire, ice, explosion and electric hits do no damage.
 */
static BattleUnitDefenseAttr defence_attr_guard = {{2, 2, 2, 2, 2}};

/**
 * Status vulnerability of the D. Koopatrol while it is withdrawn into its shell:
 * every status lands at the normal rate.
 */
static StatusVulnerability regist_guard = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

/** Pose table of the D. Koopatrol: maps each battle pose (waiting, hurt, running...) to an animation. */
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
    {31, "S_1"},
    {BTL_POSE_DAMAGE, "D_1"},
    {50, "A_1"},
    {BTL_POSE_RUN, "R_1"},
    {BTL_POSE_WALK, "W_1"},
    {BTL_POSE_DANGER, "X_1"},
    {BTL_POSE_PERIL, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

/**
 * Pose table of the D. Koopatrol while it is flipped on its back:
 * maps each battle pose (waiting, hurt, running...) to an animation.
 */
static PoseTableEntry pose_table_turn[] = {
    {1, "N_2"},
    {2, "Z_2"},
    {9, "Z_2"},
    {5, "K_2"},
    {4, "S_2"},
    {3, "S_2"},
    {BTL_POSE_NORMAL, "S_2"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "D_1"},
    {BTL_POSE_DAMAGE, "D_1"},
    {BTL_POSE_DANGER, "S_2"},
    {BTL_POSE_PERIL, "S_2"},
    {BTL_POSE_TALK, "S_2"},
    {BTL_POSE_STAY_DEFAULT, "S_2"},
};

/**
 * Pose table of the D. Koopatrol while it is withdrawn into its shell:
 * maps each battle pose (waiting, hurt, running...) to an animation.
 */
static PoseTableEntry pose_table_guard[] = {
    {1, "A_1"},
    {2, "A_1"},
    {9, "A_1"},
    {5, "A_1"},
    {4, "A_1"},
    {3, "A_1"},
    {BTL_POSE_NORMAL, "A_1"},
    {29, "A_1"},
    {30, "A_1"},
    {31, "A_1"},
    {BTL_POSE_DAMAGE, "A_1"},
    {BTL_POSE_DANGER, "A_1"},
    {BTL_POSE_PERIL, "A_1"},
    {BTL_POSE_TALK, "A_1"},
    {BTL_POSE_STAY_DEFAULT, "A_1"},
};

/**
 * Pose table of the D. Koopatrol while it is withdrawn into its shell and flipped:
 * maps each battle pose (waiting, hurt, running...) to an animation.
 */
static PoseTableEntry pose_table_guard_turn[] = {
    {1, "G_1"},
    {2, "G_1"},
    {9, "G_1"},
    {5, "G_1"},
    {4, "G_1"},
    {3, "G_1"},
    {BTL_POSE_NORMAL, "G_1"},
    {29, "G_1"},
    {30, "G_1"},
    {31, "G_1"},
    {BTL_POSE_DAMAGE, "G_1"},
    {BTL_POSE_DANGER, "G_1"},
    {BTL_POSE_PERIL, "G_1"},
    {BTL_POSE_TALK, "G_1"},
    {BTL_POSE_STAY_DEFAULT, "G_1"},
};

/**
 * Data table of the D. Koopatrol: reaction scripts for being flipped over and an attacker hurt by its spikes;
 * a First Strike on it triggers nothing special.
 */
static BattleDataEntry data_table[] = {
    {13, dmg_turn_event},
    {37, dmg_avoid_counter_thorn_head_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/**
 * Data table of the D. Koopatrol while it is flipped on its back: reaction scripts for being flipped over;
 * a First Strike on it triggers nothing special.
 */
static BattleDataEntry data_table_turn[] = {
    {13, dmg_turn_event},
    {48, btldefaultevt_Dummy},
    {0},
};

/**
 * Data table of the D. Koopatrol while it is withdrawn into its shell:
 * reaction scripts for an attacker hurt by its spikes and being flipped over;
 * a First Strike on it triggers nothing special.
 */
static BattleDataEntry data_table_guard[] = {
    {37, dmg_avoid_counter_thorn_head_event},
    {13, dmg_turn_event},
    {48, btldefaultevt_Dummy},
    {0},
};

/** Body part of the D. Koopatrol: a single part using the c_togenoko_b model. */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_togenoko_ace", "c_togenoko_b", 0.0f, 0.0f, 0.0f, 0.0f, 40.0f, 0.0f, 0.0f, 50.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_SHELLED, COUNTER_ATTR_TOP_SPIKY, pose_table},
};

/** Attack data of the D. Koopatrol's helmet charge: 5 damage. */
static BattleWeapon weapon_togenoko_normal_attack = {
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
    ELEMENT_NORMAL, // element
    8, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_TOP_SPIKY, // counterResistFlags
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

/** Attack data of the D. Koopatrol's shell attack: 4 damage; hits every target. */
static BattleWeapon weapon_togenoko_shell_attack = {
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
#if VERSION <= VERSION_DEMO_US
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#else
    {5, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#endif
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_SHELL_TOSS_LIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, // element
    8, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
#if VERSION <= VERSION_DEMO_US
    COUNTER_RESIST_ALL, // counterResistFlags
#else
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
#endif
    TARGET_WEIGHT_UNUSED_2000, // targetWeightFlags
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
 * Attack data of the D. Koopatrol's charge-up: no direct damage; used on itself; gives itself a Charge of 4.
 */
static BattleWeapon weapon_togenoko_charge = {
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
#if VERSION <= VERSION_DEMO_US
    4, // chargeStrength
#else
    5, // chargeStrength
#endif
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Init script of the Dark Koopatrol: registers its wait,
 * attack and damage scripts (confused, it runs the normal attack script),
 * sets its run and walk sounds and starts the wait script.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_MOVE3"), STRING("SFX_ENM_TOGENOKO_MOVE4"), 0, 3, 3)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_MOVE3"), STRING("SFX_ENM_TOGENOKO_MOVE4"), 0, 6, 6)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage reaction of the Dark Koopatrol: the default damage script. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Run when a stomp is stopped by the Dark Koopatrol's spiked helmet (data event 37):
 * after half a second it flashes toge_flush on the spike, placed higher when it is Huge and lower when Tiny.
 */
static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_HUGE, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 70)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_TINY, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 40)
        GOTO(90)
    END_IF
    ADD(LW(1), 55)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

/**
 * Flip-over reaction (data event 13): moves its hit point down, switches to the flipped defence,
 * defence-attribute, status-resistance and data tables
 * and the flipped poses (the guarding ones if it was in its shell), sets the flipped status flag,
 * turns its helmet spike off and sets an overturn count of 2, then bounces with SFX_ENM_INSIDE1.
 */
static EVT_BEGIN(dmg_turn_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetHitOffset, LW(10), LW(11), 0, -20, 0)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence_turn))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, LW(10), LW(11), PTR(&defence_attr_turn))
    CALL(btlevtcmd_SetRegistStatus, LW(10), PTR(&regist_turn))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_TOGENOKO_ACE_GUARDING, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_turn))
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
    ELSE
        CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_guard_turn))
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_STAY_DEFAULT)
    END_IF
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table_turn))
    CALL(btlevtcmd_OnStatusFlag, LW(10), STATUS_FLAG_FLIPPED)
    CALL(btlevtcmd_OffPartsCounterAttribute, LW(10), LW(11), COUNTER_ATTR_TOP_SPIKY)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), 2)
    WAIT_FRAMES(2)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_INSIDE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 15, -1)
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 10, -1)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_STAY_DEFAULT)
    RETURN
EVT_END()

/**
 * Run instead of an attack while flipped: counts the overturn count down and, when it reaches 0,
 * restores the normal tables and helmet spike, hops upright with SFX_ENM_INSIDE2
 * and clears unit work 0 (no longer guarding).
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
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table))
    CALL(btlevtcmd_OffStatusFlag, LW(10), STATUS_FLAG_FLIPPED)
    CALL(btlevtcmd_OnPartsCounterAttribute, LW(10), LW(11), COUNTER_ATTR_TOP_SPIKY)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_INSIDE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("S_1"))
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_SetHitOffset, LW(10), LW(11), 0, 0, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_TOGENOKO_ACE_GUARDING, 0)
    CALL(btlevtcmd_StartWaitEvent, LW(10))
    RETURN
EVT_END()

/**
 * Spawn setup for another D. Koopatrol, which the D. Koopatrol calls into the battle:
 * enemy side, acting in the enemy phase, placed far off-screen until the calling script moves it into position.
 */
static BattleUnitSetup entry_togenoko = {
    &unit_togenoko_ace, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Attack script of the Dark Koopatrol.
 * On a first strike it uses the normal attack; while flipped it tries to get up.
 * While guarding it leaves its shell 80% of the time and otherwise skips the turn.
 * When charged it picks the normal attack (50 in 85) or the shell attack.
 * Otherwise it may use an item; it never calls a friend (those chances are 0 here)
 * and picks the normal attack 50%, shell attack 35% or charge 15% (guard 0%).
 */
static EVT_BEGIN(attack_event)
    // In a first-strike battle it simply does the helmet charge.
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(9), PTR(&weapon_togenoko_normal_attack))
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetOverTurnCount, BTL_UNIT_SELF, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        // If it is flipped over it spends the turn getting up.
        CALL_CHILD(wakeup_event)
        RETURN
    END_IF
    // While it is guarding in its shell, 80% of the time it comes out; otherwise it skips the turn.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_TOGENOKO_ACE_GUARDING, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LW(0), 80)
        ADD(LW(0), 20)
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(1))
        IF_INT_LESS(LW(1), 80)
            CALL_CHILD(guard_cancel_event)
            GOTO(99)
        END_IF
        GOTO(99)
    ELSE
        // If it is charged up it picks the helmet charge or the shell attack, half each.
        CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_CHARGE, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SET_VALUE(LW(0), 0)
            ADD(LW(0), 50)
            ADD(LW(0), 35)
            SUBTRACT(LW(0), 1)
            CALL(evt_sub_random, LW(0), LW(1))
            SET_VALUE(LW(0), 50)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(&weapon_togenoko_normal_attack))
                CALL_CHILD(normal_attack_event)
                GOTO(99)
            END_IF
            SET_VALUE(LW(9), PTR(&weapon_togenoko_shell_attack))
            CALL_CHILD(shell_attack_event)
            GOTO(99)
        END_IF
        // It uses a held item if the AI wants to.
        CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(LW(0))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            RETURN
        END_IF
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        LOOP(0)
            CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 40)
            SET_VALUE(LW(4), LW(0))
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
            MULTIPLY(LW(4), LW(5))
            IF_INT_LESS(LW(4), 0)
                SUBTRACT(LW(2), 10)
                // It looks for a free spot in its row to call a friend into.
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                IF_INT_EQUAL(LW(3), -1)
                    GOTO(10)
                END_IF
            ELSE
                GOTO(9)
            END_IF
        END_LOOP
        LABEL(9)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        LOOP(0)
            CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
            IF_INT_LESS_OR_EQUAL(LW(0), 130)
                ADD(LW(2), 10)
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                IF_INT_EQUAL(LW(3), -1)
                    GOTO(10)
                END_IF
            ELSE
                GOTO(11)
            END_IF
        END_LOOP
        LABEL(10)
        // If there is room it may call friends: 40%, 20% or 10% for one, two or three Koopatrols.
        CALL(togenoko_getnum, LW(10))
        CALL(evt_sub_random, 99, LW(11))
        SWITCH(LW(10))
            CASE_EQUAL(1)
            IF_INT_LESS(LW(11), 0)
                CALL_CHILD(friend_event)
                GOTO(99)
            END_IF
            CASE_END
            CASE_EQUAL(2)
            IF_INT_LESS(LW(11), 0)
                CALL_CHILD(friend_event)
                GOTO(99)
            END_IF
            CASE_END
            CASE_EQUAL(3)
            IF_INT_LESS(LW(11), 0)
                CALL_CHILD(friend_event)
                GOTO(99)
            END_IF
            CASE_END
        END_SWITCH
        // Otherwise it picks at random: helmet charge, shell attack, charge-up or guard, 25% each.
        LABEL(11)
        SET_VALUE(LW(0), 0)
        ADD(LW(0), 50)
        ADD(LW(0), 35)
        ADD(LW(0), 15)
        ADD(LW(0), 0)
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(1))
        SET_VALUE(LW(0), 50)
        IF_INT_LESS(LW(1), LW(0))
            SET_VALUE(LW(9), PTR(&weapon_togenoko_normal_attack))
            CALL_CHILD(normal_attack_event)
            GOTO(99)
        END_IF
        ADD(LW(0), 35)
        IF_INT_LESS(LW(1), LW(0))
            SET_VALUE(LW(9), PTR(&weapon_togenoko_shell_attack))
            CALL_CHILD(shell_attack_event)
            GOTO(99)
        END_IF
        ADD(LW(0), 15)
        IF_INT_LESS(LW(1), LW(0))
            SET_VALUE(LW(9), PTR(&weapon_togenoko_charge))
            // Charge-up: it powers itself up for its next attack.
            CALL_CHILD(charge_event)
            GOTO(99)
        END_IF
        // Guard: it withdraws into its shell.
        CALL_CHILD(guard_event)
        GOTO(99)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Dark Koopatrol's helmet charge (weapon in LW(9)):
 * it revs up for a second (R_3) and dashes at the target head first (A_2, SFX_ENM_TOGENOKO_MOVE5).
 * A hit applies the guard result and damage and it hops back home in two bounces;
 * a miss carries it off the right edge and it runs back in to its home spot.
 */
static EVT_BEGIN(normal_attack_event)
    // First-strike battle: the target is already fixed; otherwise one is picked from the opposing party.
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        WAIT_MS(750)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    // No target to attack: a confused Dark Koopatrol just flusters about, otherwise it skips its turn.
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
    // The camera frames the Dark Koopatrol and its target.
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    BEGIN_SIBLING_EVENT
        LOOP(10)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(3)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_MOVE4"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(3)
        END_LOOP
    END_SIBLING_EVENT
    // The Dark Koopatrol revs up for a second.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_3"))
    WAIT_FRAMES(60)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_MOVE5"), EVT_NULLPTR, 0, EVT_NULLPTR)
    // It dashes at the target head first.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 10)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
    // Check whether the attack will connect; a miss sends the target into its dodge.
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
    END_SWITCH
    // A miss: it charges off the right edge of the screen and runs back in to its place.
    LABEL(90)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 500)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_1"))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, -1)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 300, LW(1), LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    GOTO(98)
    // A hit: the target takes the damage and the Dark Koopatrol hops back home in two bounces.
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(10), LW(11), LW(12))
    SUBTRACT_FLOAT(LW(10), LW(0))
    SUBTRACT_FLOAT(LW(11), LW(1))
    SUBTRACT_FLOAT(LW(12), LW(2))
    MULTIPLY_FLOAT(LW(10), FLOAT(0.75f))
    MULTIPLY_FLOAT(LW(11), FLOAT(0.75f))
    MULTIPLY_FLOAT(LW(12), FLOAT(0.75f))
    ADD_FLOAT(LW(0), LW(10))
    ADD_FLOAT(LW(1), LW(11))
    ADD_FLOAT(LW(2), LW(12))
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, 0, FLOAT(0.19921875f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_MOVE6"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, 0, FLOAT(0.19921875f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_MOVE6"), EVT_NULLPTR, 0, EVT_NULLPTR)
    GOTO(98)
    LABEL(98)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    WAIT_MS(500)
    RETURN
EVT_END()

/**
 * The Dark Koopatrol's shell attack (weapon in LW(9)):
 * it hops, withdraws into its spinning shell and slides along the ground through the target
 * and each further target in line (GetSelectNextEnemy), applying the guard result once and damage to each.
 * It then slides off-screen, comes back from the right and pops out of its shell at home.
 */
static EVT_BEGIN(shell_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // A target is picked from the opposing party.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    // No target to attack: a confused Dark Koopatrol just flusters about, otherwise it skips its turn.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    // The shell attack is declared.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(100)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_SHELL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    // It hops and withdraws into its shell, which starts to spin faster and faster.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_TOGENOKO_ACE_SPIN_STOP, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_TOGENOKO_ACE_SPIN_SPEED, 10)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_TOGENOKO_ACE_SPIN_STOP, LW(15))
            IF_INT_EQUAL(LW(15), 1)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_TOGENOKO_ACE_SPIN_SPEED, LW(14))
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(14), 0)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_MS(200)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_TOGENOKO_ACE_SPIN_SPEED, 20)
    WAIT_MS(200)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_TOGENOKO_ACE_SPIN_SPEED, 40)
    WAIT_MS(200)
    // It will slide through the first target and every target behind it in line.
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    // A smoke trail follows it as it slides.
    BEGIN_SIBLING_EVENT_GET_ID(LW(13))
        LOOP(0)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            ADD(LW(1), 10)
            CALL(evt_eff, STRING(""), STRING("kemuri_test"), 0, LW(0), LW(1), LW(2), FLOAT(0.2998047f), 0, 0, 0, 0, 0, 0, 0)
            WAIT_FRAMES(3)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(12.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(5), EVT_NULLPTR)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 0, 0, 0)
    SET_VALUE(LW(6), 0)
    LABEL(10)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(12.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(5), EVT_NULLPTR)
    // Check whether the attack will connect; a miss sends the target into its dodge.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // A miss: this target dodges as the shell slides through.
    LABEL(90)
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 100)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 0, 0, 0)
    GOTO(97)
    // A hit: this target takes the damage (the guard result is applied once).
    LABEL(91)
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
        SET_VALUE(LW(6), 1)
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(97)
    // On to the next target in line.
    LABEL(97)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 500)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(12.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0)
    WAIT_MS(500)
    // It slides off the screen and comes back in from the right.
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 250, LW(1), LW(2))
    LABEL(98)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(12.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0)
    DELETE_EVENT(LW(13))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_SHELL2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    // It pops out of its shell back at home.
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(10.0f), FLOAT(0.39941406f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_TOGENOKO_ACE_SPIN_STOP, 1)
    WAIT_FRAMES(3)
    // Turn finished: the Dark Koopatrol goes back to waiting.
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Dark Koopatrol charges itself up (weapon_togenoko_charge targets only itself, charge strength 2):
 * it revs in place for 48 frames with SFX_ENM_TOGENOKO_CHARGE1 while the camera zooms in.
 */
static EVT_BEGIN(charge_event)
    SET_VALUE(LW(3), -2)
    SET_VALUE(LW(4), 1)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_togenoko_charge))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_togenoko_charge))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        LOOP(8)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(3)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_MOVE4"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(3)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_3"))
    WAIT_FRAMES(48)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    BEGIN_INLINE_EVENT
        WAIT_FRAMES(60)
        CALL(evt_btl_camera_set_mode, 0, 0)
    END_INLINE_EVENT
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_togenoko_charge))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_togenoko_charge), DAMAGE_FLAG_LAST_HIT, LW(5))
    RETURN
EVT_END()

/**
 * The Dark Koopatrol withdraws into its shell to guard (SFX_ENM_TOGENOKO_SHELL1, A_1, a spinning hop):
 * switches to the guard defence, defence-attribute, status-resistance,
 * pose and data tables and sets unit work 0 to 1.
 */
static EVT_BEGIN(guard_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(10)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_SHELL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        WAIT_FRAMES(5)
        CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("A_1"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpSetting, LW(10), 20, 0, FLOAT(0.5f))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 20, -1)
    SET_FLOAT_VALUE(LW(12), FLOAT(30.0f))
    SET_FLOAT_VALUE(LW(13), FLOAT(0.0f))
    LOOP(15)
        CALL(evt_sub_get_sincos, LW(13), LW(14), LW(15))
        MULTIPLY_FLOAT(LW(14), LW(12))
        CALL(btlevtcmd_SetRotate, LW(10), 0, 0, LW(14))
        SUBTRACT_FLOAT(LW(12), FLOAT(2.0f))
        ADD_FLOAT(LW(13), FLOAT(30.0f))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetRotate, LW(10), 0, 0, 0)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence_guard))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, LW(10), LW(11), PTR(&defence_attr_guard))
    CALL(btlevtcmd_SetRegistStatus, LW(10), PTR(&regist_guard))
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_guard))
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table_guard))
    CALL(btlevtcmd_SetUnitWork, LW(10), UW_TOGENOKO_ACE_GUARDING, 1)
    CALL(btlevtcmd_SetHitOffset, LW(10), LW(11), 0, -20, 0)
    WAIT_MS(300)
    RETURN
EVT_END()

/**
 * The Dark Koopatrol comes out of its shell (SFX_ENM_TOGENOKO_SHELL2, S_1, a hop):
 * restores the normal defence, defence- attribute, status-resistance,
 * pose and data tables and clears unit work 0.
 */
static EVT_BEGIN(guard_cancel_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(10)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_SHELL2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        WAIT_FRAMES(5)
        CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("S_1"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpSetting, LW(10), 20, 0, FLOAT(0.5f))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_MOVE6"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, LW(10), LW(11), PTR(&defence_attr))
    CALL(btlevtcmd_SetRegistStatus, LW(10), PTR(&regist))
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table))
    CALL(btlevtcmd_SetUnitWork, LW(10), UW_TOGENOKO_ACE_GUARDING, 0)
    CALL(btlevtcmd_SetHitOffset, LW(10), LW(11), 0, 0, 0)
    WAIT_MS(300)
    RETURN
EVT_END()

/**
 * The Dark Koopatrol calls for help (SFX_ENM_TOGENOKO_CALL1, pose B_1):
 * a new Dark Koopatrol (entry_togenoko) is spawned off the right edge
 * and runs in to the free spot attack_event found (LW(0)..LW(2)), which becomes its home.
 */
static EVT_BEGIN(friend_event)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGENOKO_CALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("B_1"))
    WAIT_FRAMES(40)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_togenoko), 0)
    CALL(btlevtcmd_SetPos, LW(3), 300, LW(1), LW(2))
    WAIT_FRAMES(10)
    CALL(btlevtcmd_AnimeChangePose, LW(3), 1, STRING("R_1"))
    CALL(btlevtcmd_SetMoveSpeed, LW(3), 8)
    CALL(btlevtcmd_MovePosition, LW(3), LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_AnimeChangePose, LW(3), 1, STRING("S_1"))
    WAIT_MS(500)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(300)
    RETURN
EVT_END()

/** Wait script of the Dark Koopatrol: shows its idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
