// unit_hennya: hennya battle unit, one of the three spinning spiked enemies (hannya, hennya, hinnya).

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "evt/evt_eff.h"

static BattleUnitKind unit_hennya;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleDataEntry data_table[3];
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_hannya_attack;
static PoseTableEntry pose_table[18];
static EvtWord init_event[25];
static EvtWord dmg_avoid_counter_thorn_head_event[68];
static EvtWord damage_event[10];
static EvtWord attack_event[455];
static EvtWord wait_event[6];

static BattleUnitKind unit_hennya = {
    163, // unitType
    "btl_un_hennya", // name
    12, // maxHp
    0, // maxFp
    1, // dangerHP
    1, // perilHP
    33, // level
    1, // bonusExp
    3, // bonusCoin
    70, // bonusCoinRate
    1, // baseCoin
    50, // runRate
    9999, // pbSoftCap
    26, // width
    40, // height
    {3, 35}, // hitOffset
    {0.0f, 20.0f, 0.0f}, // centerOffset
    {0}, // hpGaugeOffset
    {0}, // talkTogeBaseOffset
    {13.0f, 0.0f, -10.0f}, // heldItemBaseOffset
    {0}, // burnFlameOffset
    0.0f, 0.0f, // vivianOffsetX..vivianOffsetZ
    {13.0f, 0.0f, 0.0f}, // bintaHitOffset
    {13.0f, 20.0f, 0.0f}, // kissHitOffset
    {0.0f, 20.0f, 0.0f}, // cutBaseOffset
    26.0f, // cutWidth
    40.0f, // cutHeight
    0, 0, 0, // turnOrder..swallowChance
    2, // swallowAttributes
    100, // hammerKnockbackChance
    20, // itemStealParam
    {0}, // starPointDispOffset
    "SFX_ENM_HANNYA_DAMAGED1", // damageSfxName
    "SFX_BTL_DAMAGE_FIRE1", // fireDamageSfxName
    "SFX_BTL_DAMAGE_ICE1", // iceDamageSfxName
    "SFX_BTL_DAMAGE_BIRIBIRI1", // explosionDamageSfxName
    0, // attributeFlags
    &regist, // statusVulnerability
    1, // numParts
    parts, // parts
    init_event, // initEventCode
    (BattleDataEntry*)data_table, // dataTable
};

static BattleUnitDefense defence = {{2, 2, 2, 2, 2}};

static BattleUnitDefenseAttr defence_attr = {0};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {70, 90, 70, 150, 70, 150, 150, 70, 150, 70, 150, 70, 150, 70, 70, 90, 90, 150, 70, 0, 0, 30};
#else
static StatusVulnerability regist = {70, 90, 70, 150, 70, 150, 150, 70, 150, 90, 150, 90, 150, 90, 70, 80, 80, 150, 70, 0, 0, 30};
#endif

static BattleDataEntry data_table[] = {
    {37, dmg_avoid_counter_thorn_head_event},
    {48, btldefaultevt_Dummy},
    {0},
};

static BattleUnitKindPart parts[] = {
    {
        1, // partNum
        "btl_un_hennya", // partName
        "c_hannya_t", // modelName
        {0}, // positionOffset
        {0.0f, 27.0f, 0.0f}, // hitBaseOffset
        {0.0f, 37.0f, 0.0f}, // hitCursorBaseOffset
        20, // shadowSize
        30, // hitHeight
        255, // baseAlpha
        &defence, // defense
        &defence_attr, // defenseAttr
        PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, // attributes
        1, // counterAttributes
        pose_table, // poseTable
    },
};

static BattleWeapon weapon_hannya_attack = {
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
    {7, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
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
    {31, "A_3"},
    {39, "D_1"},
    {50, "A_1"},
    {40, "W_1"},
    {42, "R_1"},
    {56, "X_1"},
    {57, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

/**
 * Guess: init event of the Spania-type spinning spiked enemy:
 * sets unit flag 0x1000000 and registers its wait, attack, damage and confusion events,
 * then starts the wait event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, 16777216)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Data event 37 (the thorn-head counter, run when a player attack is bounced off its spiked head):
 * plays pose type 31, waits 30 frames, then flashes the "toge_flush" spike effect above the unit for 60 frames.
 * The effect sits 53 units up when the unit is Huge (status 10), 33 when Tiny (status 11) and 43 otherwise.
 */
static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 31)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 53)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 33)
        GOTO(90)
    END_IF
    ADD(LW(1), 43)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

/** Damage event: runs the default battle damage reaction on the unit itself (part 1). */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Guess: attack event of the Spania-type spiked enemy, a single charge.
 * It uses an enemy item if one fits (or picks a target with btlevtcmd_ChoiceSamplingEnemy),
 * shakes in place for 20 frames while the charge sound plays,
 * then rushes along the floor to the target (the avoid animation or the ResultACDefence/CheckDamage hit decide
 * the outcome) and carries on 500 units past it.
 * It then reappears at x=300 and glides back to its home position in four slowing steps.
 * A flustered (confused) unit with no target runs subsetevt_confuse_flustered.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        WAIT_FRAMES(30)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(LW(0))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            RETURN
        END_IF
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_hannya_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_hannya_attack), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_hannya_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_hannya_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(14))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HANNYA_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1"))
    SET_VALUE(LW(15), 0)
    LOOP(0)
        WAIT_FRAMES(2)
        CALL(btlevtcmd_AddPos, BTL_UNIT_SELF, 1, 0, 0)
        WAIT_FRAMES(2)
        CALL(btlevtcmd_AddPos, BTL_UNIT_SELF, -1, 0, 0)
        ADD(LW(15), 1)
        IF_INT_GREATER_OR_EQUAL(LW(15), 10)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HANNYA_MOVE1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3"))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_hannya_attack), 256, LW(5))
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
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    MULTIPLY(LW(14), 500)
    ADD(LW(0), LW(14))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
    GOTO(98)
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_hannya_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_hannya_attack), 256, LW(5))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    MULTIPLY(LW(14), 500)
    ADD(LW(0), LW(14))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
    GOTO(98)
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HANNYA_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 300, LW(1), LW(2))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3"))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 50)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HANNYA_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 30)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(2.0f))
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 10)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    WAIT_MS(300)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait event: sets the idle animation from the unit's pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
