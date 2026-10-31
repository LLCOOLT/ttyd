// Battle unit Bullet Bill (`killer`): tst.rel's copy of rels/dou/src/unit/unit_killer.c.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"

BattleUnitKind unit_killer;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_killer_charge_attack;
static PoseTableEntry pose_table[18];
static BattleDataEntry data_table[2];
static EvtWord init_event[39];
static EvtWord damage_event[10];
static EvtWord attack_event[407];
static EvtWord wait_event[6];

/** Unit definition of the Bullet Bill: 2 HP, level 1, 1 part, with its sounds, init script and data table. */
BattleUnitKind unit_killer = {
    UNIT_BULLET_BILL,
    "btl_un_killer",
    2,
    0,
    1,
    1,
    1,
    0,
    0,
    70,
    0,
    50,
    9999,
    32,
    26,
    3,
    26,
    0.0f,
    13.0f,
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
    16.0f,
    16.9f,
    0.0f,
    0.0f,
    13.0f,
    0.0f,
    32.0f,
    26.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_KILLER_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_FLOATING,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/** Defence of the Bullet Bill: 1 against every kind of attack. */
static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

/** Damage-type modifiers of the Bullet Bill: none, no special weakness or immunity. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Bullet Bill (100% is the normal chance): immune to Sleep, Stop, Poison and
 * Fright; resists Confusion 50%, Freeze 75%, Tiny 75%, Attack Down 75%, Defense Down 75%, Allergic 75%, Slow
 * 75% and instant KO 95%; weak to Electrified 150%.
 */
static StatusVulnerability regist = {0, 0, 100, 0, 50, 150, 100, 75, 100, 75, 100, 75, 100, 75, 75, 0, 100, 100, 75, 100, 100, 95};
#else
static StatusVulnerability regist = {0, 0, 105, 0, 50, 150, 100, 70, 100, 95, 100, 95, 100, 95, 75, 0, 100, 100, 75, 100, 100, 95};
#endif

/**
 * Body of the Bullet Bill: one targetable part, the model `c_kilr`, with its hit box, defence tables and pose
 * table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_killer", "c_kilr", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table},
};

/**
 * Attack data of the Bullet Bill's suicide charge: hits one opposing unit for 4 damage; flips shelled enemies
 * over.
 */
static BattleWeapon weapon_killer_charge_attack = {
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
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED, // special
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

/**
 * Pose table of the Bullet Bill: its 18 battle poses (status, hurt and action) and the animation each one
 * plays; the idle animation is `KIL_S_1`.
 */
static PoseTableEntry pose_table[] = {
    {STATUS_SLEEP, "KIL_N_1"},
    {STATUS_STOP, "KIL_D_1"},
    {STATUS_FREEZE, "KIL_D_1"},
    {STATUS_CONFUSE, "KIL_K_1"},
    {STATUS_POISON, "KIL_X_1"},
    {STATUS_DIZZY, "KIL_X_1"},
    {BTL_POSE_NORMAL, "KIL_S_1"},
    {29, "KIL_Q_1"},
    {30, "KIL_Q_1"},
    {31, "KIL_A_1"},
    {BTL_POSE_DAMAGE, "KIL_D_1"},
    {50, "KIL_A_1"},
    {BTL_POSE_WALK, "KIL_W_1"},
    {BTL_POSE_RUN, "KIL_R_1"},
    {BTL_POSE_DANGER, "KIL_X_1"},
    {BTL_POSE_PERIL, "KIL_X_1"},
    {BTL_POSE_TALK, "KIL_T_1"},
    {BTL_POSE_STAY_DEFAULT, "KIL_S_1"},
};

/** Data table of the Bullet Bill: event 48 does nothing (btldefaultevt_Dummy). */
static BattleDataEntry data_table[] = {
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/**
 * Battle init script for the Bullet Bill: installs the wait, attack, damage and confusion handlers,
 * starts the wait event and lifts the unit and its home position to y = 10 so it floats above the ground.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), 10, LW(2))
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 10, LW(2))
    RETURN
EVT_END()

/**
 * Damage handler: selects this unit (-2) and its part 1
 * and runs the shared default damage reaction (btldefaultevt_Damage).
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Starts the avoid animation of the target LW(3) for the pre-damage check result in LW(5):
 * 3, 6 and 2 select avoid types 38, 39 and 40.
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
 * Attack of the Bullet Bill: picks a target (the fixed first target in a flag-2 battle,
 * otherwise a sampled enemy; uses an enemy item first if it has one), zooms the camera on it,
 * charges for 30 frames and then flies into it.
 * The Bill always ends up removed from the battle:
 * after a miss it flies past the target and off, after a hit it explodes in smoke, banks its coins,
 * experience and star points and is killed (KillUnit) once the damage has been dealt.
 */
static EVT_BEGIN(attack_event)
    // Picks the target: the preset first-attack target (after a short pause) when battle flag 2 is set; otherwise it
    // uses a held item if it has one, or picks a random opposing unit. With none it does nothing (or is flustered
    // when confused).
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        WAIT_MS(750)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(LW(0))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            RETURN
        END_IF
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_killer_charge_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_killer_charge_attack), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // Declares the attack and pays its cost while the camera follows the target.
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_killer_charge_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_killer_charge_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // Wind-up: the Bullet Bill revs up (charge sound, pose 50) for about half a second, then launches with a rushing
    // sound.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KILLER_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KILLER_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    // Checks the outcome of the hit: a miss, dodge or guard goes to the no-damage branch; a connecting hit applies
    // the Action Command defence result and deals the damage.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_killer_charge_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // Miss branch: it streaks past the target, the target dodges, and the Bill slams into the far edge of the stage
    // with a camera shake, ending up disabled there.
    LABEL(90)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 10, LW(2), 0, -1)
    CALL_CHILD(start_avoid)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 500)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 10, LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KILLER_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_btl_camera_shake_w, 0, 5, 0, 15, 0)
    WAIT_MS(300)
    CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, UNIT_ATTR_HIDDEN)
    WAIT_MS(500)
    GOTO(98)
    // Hit branch: it rams the target, the defence result is read and the damage is applied; the Bill blows itself up
    // in a puff of smoke, and the party is awarded its coins, experience and star points.
    LABEL(91)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 10, LW(2), 0, -1)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_killer_charge_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_killer_charge_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(evt_btl_camera_shake_w, 0, 5, 0, 15, 0)
    CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, UNIT_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KILLER_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_ENEMY_DIE1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(2), 10)
    ADD(LW(1), 20)
    CALL(evt_eff, STRING(""), STRING("kemuri_test"), 17, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_GetCoin, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_StoreCoin, LW(0))
    CALL(btlevtcmd_GetExp, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_StoreExp, LW(0))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(3), LW(1), LW(2))
    ADD(LW(2), 10)
    ADD(LW(1), 30)
    CALL(_add_star_point_disp_offset, LW(10), LW(3), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("star_point"), 0, LW(3), LW(1), LW(2), LW(0), 0, 0, 0, 0, 0, 0, 0)
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        LOOP(LW(0))
        END_LOOP
    END_IF
    WAIT_MS(500)
    GOTO(98)
    // Either way the Bullet Bill is spent and removes itself from the battle.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(200)
    LABEL(99)
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

/**
 * Wait (idle) event: refreshes the body animation (part 1) from the unit's pose table
 * so it matches the current state, then returns; the battle system runs it whenever the unit is idle.
 */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
