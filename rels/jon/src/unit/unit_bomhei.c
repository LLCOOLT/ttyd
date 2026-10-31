// Pit of 100 Trials battle unit: the Bob-omb (`bomhei`): parts, stats, poses and AI scripts.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"

BattleUnitKind unit_bomhei;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_spark[18];
static BattleDataEntry data_table[2];
static BattleDataEntry data_table_spark[2];
static BattleUnitKindPart parts[1];
static StatusVulnerability regist;
static BattleWeapon weapon_bomhei_attack;
static BattleWeapon weapon_bomhei_bomb;
static EvtWord init_event[42];
static EvtWord damage_event[58];
static EvtWord change_spark_event[70];
static EvtWord attack_event[440];
static EvtWord wait_event[6];
static EvtWord damage_event_spark[25];
#if VERSION <= VERSION_DEMO_US
static EvtWord attack_event_spark[292];
#else
static EvtWord attack_event_spark[288];
#endif
static EvtWord wait_event_spark[27];

BattleUnitKind unit_bomhei = {
    43,
    "btl_un_bomhei",
    4,
    0,
    1,
    1,
    12,
    0,
    1,
    70,
    1,
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
    11.0f,
    16.0f,
    0.0f,
    2.0f,
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
    "SFX_ENM_BOMB_DAMAGED1",
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

static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static PoseTableEntry pose_table[] = {
    {1, "BOM_N_1"},
    {2, "BOM_Y_1"},
    {9, "BOM_Y_1"},
    {5, "BOM_K_1"},
    {4, "BOM_X_1"},
    {3, "BOM_X_1"},
    {28, "BOM_S_1"},
    {29, "BOM_Q_1"},
    {30, "BOM_Q_1"},
    {31, "BOM_S_1"},
    {39, "BOM_D_1"},
    {50, "BOM_A_1"},
    {42, "BOM_R_1"},
    {40, "BOM_W_1"},
    {56, "BOM_X_1"},
    {57, "BOM_X_1"},
    {BTL_POSE_TALK, "BOM_T_1"},
    {BTL_POSE_STAY_DEFAULT, "BOM_S_1"},
};

static PoseTableEntry pose_table_spark[] = {
    {1, "BOM_N_2"},
    {2, "BOM_Y_2"},
    {9, "BOM_Y_2"},
    {5, "BOM_K_2"},
    {4, "BOM_X_2"},
#if VERSION <= VERSION_DEMO_US
    {3, "BSA_X_2"},
#else
    {3, "BOM_X_2"},
#endif
    {28, "BOM_S_2"},
    {29, "BOM_Q_2"},
    {30, "BOM_Q_2"},
    {31, "BOM_S_2"},
    {39, "BOM_D_2"},
    {50, "BOM_A_2"},
    {42, "BOM_R_2"},
    {40, "BOM_W_2"},
    {56, "BOM_X_2"},
    {57, "BOM_X_2"},
    {BTL_POSE_TALK, "BOM_T_2"},
    {BTL_POSE_STAY_DEFAULT, "BOM_S_2"},
};

static BattleDataEntry data_table[] = {
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static BattleDataEntry data_table_spark[] = {
    {48, btldefaultevt_Dummy},
    {0},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_bomhei", "c_bomhey", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0x1000, pose_table},
};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {80, 80, 70, 0, 80, 150, 100, 70, 100, 80, 100, 80, 100, 80, 80, 90, 80, 100, 80, 100, 100, 95};
#else
static StatusVulnerability regist = {70, 100, 70, 0, 70, 150, 100, 100, 100, 90, 100, 90, 100, 95, 80, 90, 80, 100, 80, 100, 100, 95};
#endif

static BattleWeapon weapon_bomhei_attack = {
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
    {2, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_SHELL_TOSS_LIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    0, // counterResistFlags
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

static BattleWeapon weapon_bomhei_bomb = {
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
    TARGET_PROP_NO_CEILING | TARGET_PROP_SHELL_TOSS_LIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_BOMB_FLIPPABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 25, 25, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * The Bob-omb explodes: camera shake, the explosion flags are set, its fuse sound is stopped,
 * and it plays the blast sounds with the "sandars" effect while the stage fog is cleared.
 * It hands its coins and experience to the battle (StoreCoin/StoreExp) and, if LW(15) is 1,
 * waits for the current attack to end before removing itself from the battle.
 */
static EVT_BEGIN(bomb_event)
    CALL(evt_btl_camera_shake_w, 0, 5, 0, 15, 0)
    CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, 16777216)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 33554432)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
        CALL(evt_snd_sfxoff, LW(0))
    END_IF
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_ENEMY_DIE1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_ENM_BOMB_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("sandars"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_StageDispellFog)
    CALL(btlevtcmd_GetCoin, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_StoreCoin, LW(0))
    CALL(btlevtcmd_GetExp, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_StoreExp, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        LOOP(LW(0))
        END_LOOP
    END_IF
    WAIT_MS(1000)
    IF_INT_EQUAL(LW(15), 1)
        CALL(btlevtcmd_WaitAttackEnd)
    END_IF
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

/**
 * Init script of the Bob-omb: registers its wait, attack, damage and confusion handlers,
 * sets unit work 0 (the fuse sound id) to -1 and sets its run and walk sounds.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, -1)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE2"), STRING("SFX_ENM_BOMB_MOVE2"), 0, 4, 4)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE2"), STRING("SFX_ENM_BOMB_MOVE2"), 0, 10, 10)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage script of the Bob-omb.
 * A damaging hit (damage code 256) of kind 24, 25 or 27 sets it off at once (bomb_event;
 * Guess: these are the fire and explosion kinds).
 * Otherwise it takes the default damage and, if it is still able to act and not in status 27,
 * lights its fuse (change_spark_event).
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_CheckDamageCode, LW(10), 256, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
        SWITCH(LW(0))
            CASE_OR_EQUAL(24)
            CASE_OR_EQUAL(27)
            CASE_OR_EQUAL(25)
            SET_VALUE(LW(15), 1)
            CALL_CHILD(bomb_event)
            RETURN
            CASE_END
        END_SWITCH
    END_IF
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 27, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(change_spark_event)
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Lights the fuse after a damaging hit: if the hit took at least 1 HP it plays SFX_ENM_BOMB_SPARK1,
 * switches to the spark wait, attack and damage scripts, pose table and data table,
 * and sets counter attribute 8192 on part 1.
 */
static EVT_BEGIN(change_spark_event)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 39)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 256, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetHpDamage, BTL_UNIT_SELF, LW(15))
    IF_INT_GREATER_OR_EQUAL(LW(15), 1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_SPARK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event_spark))
        CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event_spark))
        CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event_spark))
        CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event_spark))
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_spark))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 39)
        CALL(btlevtcmd_OnPartsCounterAttribute, BTL_UNIT_SELF, 1, 8192)
        CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table_spark))
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * Attack script of the Bob-omb: a body bump.
 * After an item check it picks a target, hops twice, runs to it and, if the bump connects,
 * deals the damage and gets knocked back in two hops; a miss makes it circle the target and then it walks home.
 * When confused with no target it is flustered. The demo builds use longer waits and a slower walk home.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_bomhei_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_bomhei_attack), LW(3), LW(4))
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
#if VERSION <= VERSION_DEMO_US
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
#else
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
#endif
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_bomhei_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_bomhei_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 10)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_bomhei_attack), 256, LW(5))
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
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 30)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 1)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 60)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 90)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("BOM_N_1"))
#if VERSION <= VERSION_DEMO_US
    WAIT_MS(1000)
#else
    WAIT_MS(500)
#endif
    GOTO(98)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_bomhei_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_bomhei_attack), 256, LW(5))
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(2.0f), FLOAT(0.5f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 75)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(1.0f), FLOAT(0.5f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 100)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    GOTO(98)
    LABEL(98)
    CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE4"), STRING("SFX_ENM_BOMB_MOVE4"), 0, 10, 10, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
#if VERSION <= VERSION_DEMO_US
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
#else
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
#endif
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -2, 1)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait script: plays the Bob-omb's idle pose from its pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Damage script of the Bob-omb with its fuse lit:
 * a damaging hit (damage code 256) detonates it (bomb_event), otherwise the default damage handling runs.
 */
static EVT_BEGIN(damage_event_spark)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_CheckDamageCode, LW(10), 256, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LW(15), 1)
        CALL_CHILD(bomb_event)
    ELSE
        CALL_CHILD(btldefaultevt_Damage)
    END_IF
    RETURN
EVT_END()

/**
 * Attack script of the lit Bob-omb: it runs at its target like the normal attack,
 * then explodes (bomb_event) whether the blast hits or misses,
 * dealing the bomb weapon's damage to the target when it connects.
 */
static EVT_BEGIN(attack_event_spark)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_bomhei_bomb))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_bomhei_bomb), LW(3), LW(4))
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
#if VERSION <= VERSION_DEMO_US
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
#else
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
#endif
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_bomhei_bomb))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_bomhei_bomb))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 10)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_btl_camera_set_mode, 0, 0)
#endif
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_bomhei_bomb), 256, LW(5))
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
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 500)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    SET_VALUE(LW(15), 0)
    CALL_CHILD(bomb_event)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(1000)
    RETURN
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_bomhei_bomb))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_bomhei_bomb), 256, LW(5))
    SET_VALUE(LW(15), 0)
    CALL_CHILD(bomb_event)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(1000)
    RETURN
    LABEL(98)
    WAIT_MS(1000)
    LABEL(99)
    RETURN
EVT_END()

/**
 * Wait script of the lit Bob-omb: plays the idle pose and, if no fuse sound is playing yet (unit work 0 is -1),
 * starts the looping SFX_ENM_BOMB_WAIT1 and remembers its handle in unit work 0.
 */
static EVT_BEGIN(wait_event_spark)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(15))
    IF_INT_EQUAL(LW(15), -1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_WAIT1"), EVT_NULLPTR, 0, LW(15))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, LW(15))
    END_IF
    RETURN
EVT_END()
