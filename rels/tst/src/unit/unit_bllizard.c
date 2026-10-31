// Battle unit Ice Puff (`bllizard`): tst.rel's copy of rels/bom/src/unit/unit_bllizard.c.
#include "battle/battle_unit.h"
#include "eff/n64/eff_kumokumo_n64.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_sub.h"
#include "version.h"

static USER_FUNC(eff_ice_barrier);

BattleUnitKind unit_bllizard;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_bllizard_attack;
static BattleWeapon weapon_bllizard_bllizard_attack;
static EvtWord bllizard_event[361];
static PoseTableEntry pose_table[17];
static BattleDataEntry data_table[3];
static EvtWord init_event[37];
static EvtWord barrier_event[37];
static EvtWord dmg_first_attack_pos[19];
static EvtWord damage_event[36];
static EvtWord counter_event[2];
static EvtWord unison_phase_event[140];
static EvtWord normal_attack_event[386];
static EvtWord charge_event[58];
static EvtWord wait_event[12];

/** Script helper: deletes the icy cloud effect eff_ice_barrier left in work[1]. */
static USER_FUNC(eff_ice_barrier_end) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);

    if (unit->work[1] != 0) {
        effDelete((EffectEntry*)unit->work[1]);
        unit->work[1] = 0;
    }
    return EVT_RETURN_DONE;
}

BattleUnitKind unit_bllizard = {
    112,
    "btl_un_bllizard",
    9,
    0,
    1,
    1,
    25,
    0,
#if VERSION <= VERSION_DEMO_US
    2,
    70,
    2,
#else
    4,
    70,
    0,
#endif
    50,
    9999,
    35,
    30,
    4,
    30,
    0.0f,
    15.0f,
    0.0f,
    0,
    -3,
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
    17.5f,
    0.0f,
    0.0f,
    17.5f,
    19.5f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    35.0f,
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
    "SFX_ENM_KUMO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 1, 3, 0, 0}};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {50, 70, 70, 100, 60, 0, 100, 0, 100, 60, 100, 60, 100, 70, 60, 70, 80, 100, 60, 100, 100, 95};
#else
static StatusVulnerability regist = {65, 65, 95, 100, 60, 0, 100, 0, 100, 75, 100, 75, 100, 90, 65, 70, 85, 100, 65, 100, 100, 95};
#endif

static BattleUnitKindPart parts[] = {
    {1, "btl_un_bllizard", "c_kmoon_b", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 30, 30, 255, &defence, &defence_attr, 0x600009, 0, pose_table},
};

static BattleWeapon weapon_bllizard_attack = {
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
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED, // special
    COUNTER_RESIST_ICY, // counterResistFlags
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

static BattleWeapon weapon_bllizard_bllizard_attack = {
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
    {5, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    2, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, // burnTime
#if VERSION >= VERSION_US
    60, // freezeChance
#else
    30, // freezeChance
#endif
    2, // freezeTime
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeChance..defChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeStrength..slowChance
    0, 0, 0, 0, 0, 0, 0, 0, // slowTime..hpRegenTime
    0, 0, 0, // hpRegenStrength..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Attack script of the Ice Puff: item use first;
 * if it is charged (part counter attribute 64) it fires the blizzard (bllizard_event);
 * otherwise 70% of the time it uses its normal attack (normal_attack_event) and
 * otherwise it charges up (charge_event).
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_CheckPartsCounterAttribute, BTL_UNIT_SELF, 1, 64, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LW(9), PTR(&weapon_bllizard_bllizard_attack))
        CALL_CHILD(bllizard_event)
        GOTO(99)
    END_IF
    SET_VALUE(LW(0), 70)
    ADD(LW(0), 30)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    SET_VALUE(LW(0), 70)
    IF_INT_LESS(LW(1), LW(0))
        SET_VALUE(LW(9), PTR(&weapon_bllizard_attack))
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    END_IF
    CALL_CHILD(charge_event)
    GOTO(99)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Ice Puff's charged blizzard attack with the weapon in LW(9):
 * it clears the charged flag, blows kumokumo_n64 clouds at the target (mirrored when facing the other way) and
 * then runs the pre-damage and damage checks on each target in turn before returning to its rest pose.
 */
static EVT_BEGIN(bllizard_event)
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
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_OffPartsCounterAttribute, BTL_UNIT_SELF, 1, 64)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE3"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, -40, 15, LW(2), 30, 0, 4, 0, -1)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BLIZ_KUMO_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2B"))
    WAIT_FRAMES(60)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BLIZ_KUMO_CHARGE_ATTACK1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(5))
    SET_VALUE(LW(6), LW(5))
    MULTIPLY_FLOAT(LW(6), FLOAT(5.0f))
    ADD(LW(1), LW(6))
    MULTIPLY_FLOAT(LW(5), FLOAT(2.0f))
    CALL(btlevtcmd_GetEnemyBelong, LW(3), LW(10))
    IF_INT_EQUAL(LW(10), 0)
        CALL(evt_eff64, STRING(""), STRING("kumokumo_n64"), 4, LW(0), LW(1), LW(2), 0, 0, LW(5), 140, 0, 0, 0, 0)
    ELSE
        CALL(evt_eff64, STRING(""), STRING("kumokumo_n64"), 4, LW(0), LW(1), LW(2), 180, 0, LW(5), 140, 0, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3A"))
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3B"))
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(20)
    SET_VALUE(LW(6), 0)
    LABEL(0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
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
    GOTO(0)
    LABEL(98)
    WAIT_FRAMES(60)
    CALL(evt_snd_sfxoff, LW(15))
    WAIT_FRAMES(60)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE3"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 0, 4, 0, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    WAIT_MS(250)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

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
    {31, "A_1"},
    {39, "D_1"},
    {40, "W_1"},
    {42, "R_1"},
    {56, "X_1"},
    {57, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

static BattleDataEntry data_table[] = {
    {41, counter_event},
    {48, dmg_first_attack_pos},
    {0, NULL},
};

/**
 * Init script of a Puff: registers its wait, unison-phase, attack, damage and confusion handlers,
 * clears unit work 0 and 1, spawns barrier_event to show its charged state and starts the idle event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventUnisonPhase, BTL_UNIT_SELF, PTR(unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    SPAWN_EVENT(barrier_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Loops every frame while the Ice Puff exists: shows the ice barrier effect
 * while it is charged (part counter attribute 64) and ends the effect when it is not.
 */
static EVT_BEGIN(barrier_event)
    LABEL(0)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckPartsCounterAttribute, BTL_UNIT_SELF, 1, 64, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(eff_ice_barrier, BTL_UNIT_SELF)
    ELSE
        CALL(eff_ice_barrier_end, BTL_UNIT_SELF)
    END_IF
    GOTO(0)
    LABEL(99)
    RETURN
EVT_END()

/** Position event for a first strike on this unit: sets its height to 10 and waits for the attack to finish. */
static EVT_BEGIN(dmg_first_attack_pos)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

/**
 * Damage reaction of the Ice Puff: if the hit has damage code bit 512 and not bit 2048,
 * its charge is lost (part counter attribute 64 off, ice barrier effect ended);
 * then the default damage handling runs.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 512, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 2048, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_OffPartsCounterAttribute, BTL_UNIT_SELF, 1, 64)
            CALL(eff_ice_barrier_end, BTL_UNIT_SELF)
        END_IF
    END_IF
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/** Counter event of the Puff: empty, it does nothing. */
static EVT_BEGIN(counter_event)
    RETURN
EVT_END()

/**
 * Start-of-turn event of the Ice Puff (not while it is charged or unable to act):
 * 50% of the time it toggles between two states,
 * switching the attribute bits 0x600000 of its body part off with SFX_ENM_KUMO_MOVE5 (unit work 0 = 1)
 * or back on with SFX_ENM_KUMO_MOVE4 (work 0 = 0).
 * Guess: this makes the Puff drift out of and back into range of ground attacks.
 */
static EVT_BEGIN(unison_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckPartsCounterAttribute, BTL_UNIT_SELF, 1, 64, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(evt_sub_random, 99, LW(0))
    IF_INT_LESS(LW(0), 50)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE4"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            SET_VALUE(LW(1), 40)
            CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, 10, 4, 0, -1)
            CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 6291456)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
        ELSE
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE5"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            SET_VALUE(LW(1), 10)
            CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, -10, 4, 0, -1)
            CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, 6291456)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 1)
        END_IF
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * The Puff's plain attack with the weapon in LW(9):
 * picks a target and plays the A_2A and A_1A attack poses with SFX_ENM_KUMO_MOVE1 to 3 without leaving its spot;
 * the damage check decides between a miss and a hit, then it returns to S_1.
 */
static EVT_BEGIN(normal_attack_event)
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
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        LOOP(10)
            CALL(btlevtcmd_SetDispOffset, BTL_UNIT_SELF, 1, 0, 0)
            WAIT_FRAMES(2)
            CALL(btlevtcmd_SetDispOffset, BTL_UNIT_SELF, -1, 0, 0)
            WAIT_FRAMES(2)
        END_LOOP
        CALL(btlevtcmd_SetDispOffset, BTL_UNIT_SELF, 0, 0, 0)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LOOP(40)
            CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(-0.009765625f), 0, 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2A"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), -40)
    SET_VALUE(LW(1), 60)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 0, 4, 0, -1)
    WAIT_FRAMES(10)
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE2"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1A"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 40, -40, 1, 0, -1)
    CALL(evt_snd_sfxoff, LW(15))
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
        SET_VALUE(LW(15), 1)
        CASE_END
    END_SWITCH
    LABEL(90)
    GOTO(98)
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    GOTO(98)
    LABEL(98)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 40)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(10), 40)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(10), LW(1), LW(12), 40, 0, 4, 0, -1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE3"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, 40, 4, 0, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    CALL(evt_snd_sfxoff, LW(15))
    WAIT_MS(250)
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, 1, 1, 1)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Script helper: keeps an icy cloud effect (effKumokumoN64) around the Ice Puff,
 * creating it on the first call and tracking the unit's position and size each call.
 */
static USER_FUNC(eff_ice_barrier) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    EffectEntry* eff;
    f32 x, y, z;

    if (isFirstCall && unit->work[1] == 0) {
        unit->work[1] = (EvtWord)effKumokumoN64Entry(3, 1000, 0.0f, -1000.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    }
    eff = (EffectEntry*)unit->work[1];
    BtlUnit_GetPos(unit, &x, &y, &z);
    ((EffKumokumoN64Particle*)eff->userdata)->x = x;
    ((EffKumokumoN64Particle*)eff->userdata)->y = 10.0f * unit->sizeMultiplier + y;
    ((EffKumokumoN64Particle*)eff->userdata)->z = z;
    ((EffKumokumoN64Particle*)eff->userdata)->scale = unit->sizeMultiplier;
    return EVT_RETURN_DONE;
}

/**
 * Charges the Ice Puff: zooms the camera onto it,
 * sets the charged flag (part counter attribute 64) with SFX_ENM_BLIZ_KUMO_CHARGE1 and the A_2A/A_2B poses,
 * so its next attack is the blizzard.
 */
static EVT_BEGIN(charge_event)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BLIZ_KUMO_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_OnPartsCounterAttribute, BTL_UNIT_SELF, 1, 64)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2A"))
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2B"))
    WAIT_FRAMES(60)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    WAIT_MS(600)
    LABEL(99)
    RETURN
EVT_END()

/** Idle event of the Puff: sets the pose from the pose table and resets its scale to 1. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, 1, 1, 1)
    RETURN
EVT_END()
