// Battle unit data for the Bob-omb bomb (unit_bomzou) and its explosion weapon, used by Bobbery.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "evt/evt_sub.h"
#include "party/party_motion.h"
#include "version.h"

static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
BattleUnitKind unit_bomzou;
BattleWeapon weapon_bomzou_explosion;
static StatusVulnerability regist;
static PoseTableEntry pose_table_3[4];
static PoseTableEntry pose_table_2[4];
static PoseTableEntry pose_table_1[4];
static BattleDataEntry data_table[4];
static BattleUnitKindPart parts[1];
static EvtWord init_event[70];
static EvtWord damage_event[10];
static EvtWord phase_event[67];
static EvtWord attack_event[5];
static EvtWord wait_event[57];
static EvtWord dead_event[6];
extern EvtWord end_battle_evt[];
#if VERSION == VERSION_DEMO
static EvtWord explosion_event[172];
#else
static EvtWord explosion_event[173];
#endif

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

BattleUnitKind unit_bomzou = {
    219,
    "btl_un_bomzou",
    1,
    0,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    100,
    9,
    24,
    24,
    0,
    20,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    12.0f,
    0.0f,
    0.0f,
    12.0f,
    15.6f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BTL_DAMAGE1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_NO_DAMAGE_NUMBER | UNIT_ATTR_NO_HP_GAUGE | UNIT_ATTR_IGNORE_FOR_CLEAR,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

BattleWeapon weapon_bomzou_explosion = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, 0, 0.0f, 0, 0, 0, 0, // baseFpCost..reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ANY_PART | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    3, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_SHATTERS_FREEZE | SPECIAL_UNGUARDABLE, // special
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
    {0, 10, 10, 100, 30, 5, 5, 5, 5, 0, 0, 0}, // stageEffectRates
};

static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static PoseTableEntry pose_table_3[] = {
    {28, "B_2"},
    {31, "B_2"},
    {39, "B_2"},
#if VERSION == VERSION_DEMO
    {67, "B_2"},
#else
    {69, "B_2"},
#endif
};

static PoseTableEntry pose_table_2[] = {
    {28, "B_3"},
    {31, "B_3"},
    {39, "B_3"},
#if VERSION == VERSION_DEMO
    {67, "B_3"},
#else
    {69, "B_3"},
#endif
};

static PoseTableEntry pose_table_1[] = {
    {28, "B_4"},
    {31, "B_4"},
    {39, "B_4"},
#if VERSION == VERSION_DEMO
    {67, "B_4"},
#else
    {69, "B_4"},
#endif
};

static BattleDataEntry data_table[] = {
    {49, dead_event},
    {53, explosion_event},
    {63, end_battle_evt},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_bomzou", "c_bakudan", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_UNTATTLEABLE, 0, pose_table_3},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 2)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    CALL(btlevtcmd_SetMaxMoveCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    SWITCH(LW(0))
        CASE_GREATER_OR_EQUAL(3)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_3))
        CASE_GREATER_OR_EQUAL(2)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_2))
        CASE_GREATER_OR_EQUAL(1)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_1))
    END_SWITCH
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("B_1"))
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
        SUBTRACT(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, LW(0))
        SWITCH(LW(0))
            CASE_GREATER_OR_EQUAL(3)
            CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_3))
            CASE_GREATER_OR_EQUAL(2)
            CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_2))
            CASE_GREATER_OR_EQUAL(1)
            CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_1))
        END_SWITCH
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_SELF)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("B_2"))
            WAIT_FRAMES(36)
            CALL_CHILD(PTR(explosion_event))
        ELSE
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        END_IF
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    LABEL(0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    IF_INT_GREATER(LW(0), 1)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 10)
    CALL(evt_eff64, 0, STRING("sweat_n64"), 1, LW(0), LW(1), LW(2), 15, -45, 15, 0, 0, 0, 0, 0)
    CALL(evt_sub_random, 45, LW(0))
    ADD(LW(0), 45)
    WAIT_FRAMES(LW(0))
    GOTO(0)
    RETURN
EVT_END()

static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_AfterReactionEntry, BTL_UNIT_SELF, 53)
    RETURN
EVT_END()

EVT_BEGIN(end_battle_evt)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_snd_sfxoff, LW(0))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(explosion_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_snd_sfxoff, LW(0))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    END_IF
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("hibashira"), 2, LW(0), LW(1), LW(2), LW(0), LW(1), LW(2), 1, FLOAT(1.0f), 60, 0, 0)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_THUNDERS_BOMB2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_StageDispellFog)
    CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, UNIT_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
    CALL(evt_btl_camera_shake_h, 0, 10, 0, 60, 4)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("B_2"))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, 1, PTR(&weapon_bomzou_explosion))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_bomzou_explosion), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), LW(3))
        GOTO(80)
    END_IF
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(1), EVT_NULLPTR, EVT_NULLPTR)
    SUBTRACT(LW(0), LW(1))
    IF_INT_LESS_OR_EQUAL(LW(0), -1)
        MULTIPLY(LW(0), -1)
    END_IF
    IF_INT_GREATER(LW(0), 50)
        GOTO(80)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_bomzou_explosion), 256, LW(5))
    IF_INT_EQUAL(LW(5), 1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_bomzou_explosion), 256, LW(5))
    END_IF
    LABEL(80)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    RETURN
#if VERSION == VERSION_DEMO
EVT_END()
#else
EVT_END_PAD()
#endif
