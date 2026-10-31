// Powan: a tst-only test unit, a c_kinopio rider (part 1) on a c_gazigazi body (parts 2 and 3). After each won
// battle the field battle's post-battle event respawns it, four times in all, with a new line each time.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "system.h"
#include "battle/battle.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"
#include "driver/animdrv.h"
#include "driver/npcdrv.h"
#include "manager/evtmgr_cmd.h"
#include "tst.h"
#include "battle/battle_sub.h"
#include "evt/evt_msg.h"

static USER_FUNC(powan_set_post_battle_mode);
static USER_FUNC(powan_set_post_battle_event);
static USER_FUNC(powan_rider_follow);

BattleUnitKind unit_powan;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table_kinopio[5];
static PoseTableEntry pose_table_gazigazi[4];
static BattleDataEntry data_table[2];
static BattleUnitKindPart parts[3];
static EvtWord init_event[26];
static EvtWord rider_follow_event[21];
static EvtWord damage_event[10];
static EvtWord phase_event[2];
static BattleWeapon weapon_powan_attack;
static EvtWord attack_event[193];
static EvtWord hit_event[154];
static EvtWord wait_event[6];
static BattleUnitSetup entry_powan;
static EvtWord post_battle_event_2[13];
static EvtWord post_battle_event_3[13];
static EvtWord post_battle_event_4[13];
static EvtWord post_battle_event_5[13];
static EvtWord respawn_event[111];
static EvtWord dead_event[116];

BattleUnitKind unit_powan = {
    209,
    "btl_un_powan",
    1,
    0,
    1,
    1,
    1,
    0,
    0,
    100,
    0,
    100,
    9,
    24,
    24,
    24,
    24,
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
    0,
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
    0,
    &regist,
    3,
    parts,
    init_event,
    data_table,
};

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static StatusVulnerability regist = {150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 0, 150, 150, 150, 150, 150, 150};

static PoseTableEntry pose_table_kinopio[] = {
    {28, "KNP_S_1"},
    {31, "KNP_S_1"},
    {39, "KNP_O_1"},
    {42, "KNP_R_1"},
    {BTL_POSE_STAY_DEFAULT, "KNP_S_1"},
};

static PoseTableEntry pose_table_gazigazi[] = {
    {28, "GAZ_S_1"},
    {31, "GAZ_A_1"},
    {39, "GAZ_A_1"},
    {BTL_POSE_STAY_DEFAULT, "GAZ_S_1"},
};

static BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_powan", "c_kinopio", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table_kinopio},
    {2, "btl_un_powan", "c_gazigazi", 0.0f, 10.0f, 6.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x2010000, 0, pose_table_gazigazi},
    {3, "btl_un_powan", "c_gazigazi", 0.0f, 10.0f, 6.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table_gazigazi},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(powan_set_post_battle_event, PTR(post_battle_event_2))
    SPAWN_EVENT(rider_follow_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

static EVT_BEGIN(rider_follow_event)
    LABEL(0)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        RETURN
    END_IF
    CALL(powan_rider_follow, BTL_UNIT_SELF, 2)
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

static BattleWeapon weapon_powan_attack = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, // baseFpCost..baseSpCost
    4, // superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
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

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_SetCounterAcCallBack, BTL_UNIT_SELF, PTR(hit_event))
    SET_VALUE(LW(12), PTR(&weapon_powan_attack))
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(3), LW(4))
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
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 100)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 20)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("GAZ_A_1"))
    WAIT_FRAMES(12)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    WAIT_FRAMES(30)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, -2, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

// On a hit the Toad is knocked off: the second body (part 3) flies out and lands while the rider runs away
// and comes back.
static EVT_BEGIN(hit_event)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 0x1000000)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 10)
    ADD(LW(2), 6)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 3, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 3, 0x1000000)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KNP_O_1"))
    CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 3, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageSize, LW(0), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 3, FLOAT(0.07f))
    BEGIN_SIBLING_EVENT
        LOOP(90)
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, 3, 0, 40, 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 3, LW(0), LW(1), LW(2), 90, -1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
    MULTIPLY(LW(5), -1)
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(5))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    MULTIPLY(LW(5), -1)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
    WAIT_FRAMES(30)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 3, 0x1000000)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, 0x1000000)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

static BattleUnitSetup entry_powan = {
    &unit_powan, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {1000.0f, 0.0f, 1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

// Post-battle events: each respawns the unit with the next counter value (unit work 0) and arms the next one.
static EVT_BEGIN(post_battle_event_2)
    SET_VALUE(LW(5), 2)
    CALL_CHILD(respawn_event)
    CALL(powan_set_post_battle_event, PTR(post_battle_event_3))
    CALL(powan_set_post_battle_mode, 1)
    RETURN
EVT_END()

static EVT_BEGIN(post_battle_event_3)
    SET_VALUE(LW(5), 3)
    CALL_CHILD(respawn_event)
    CALL(powan_set_post_battle_event, PTR(post_battle_event_4))
    CALL(powan_set_post_battle_mode, 1)
    RETURN
EVT_END()

static EVT_BEGIN(post_battle_event_4)
    SET_VALUE(LW(5), 4)
    CALL_CHILD(respawn_event)
    CALL(powan_set_post_battle_event, PTR(post_battle_event_5))
    CALL(powan_set_post_battle_mode, 1)
    RETURN
EVT_END()

static EVT_BEGIN(post_battle_event_5)
    SET_VALUE(LW(5), 5)
    CALL_CHILD(respawn_event)
    CALL(powan_set_post_battle_event, 0)
    CALL(powan_set_post_battle_mode, 1)
    RETURN
EVT_END()

static EVT_BEGIN(respawn_event)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_powan), 0)
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(5))
    SET_VALUE(LW(0), 80)
    SET_VALUE(LW(1), 240)
    SET_VALUE(LW(2), 0)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetFallAccel, LW(3), FLOAT(0.1f))
    CALL(btlevtcmd_JumpPosition, LW(3), LW(0), LW(1), LW(2), 120, -1)
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    WAIT_FRAMES(30)
    SWITCH(LW(5))
        CASE_EQUAL(2)
        CALL(evt_msg_print, 3, STRING("あいたた<key><scrl auto> \nひどいじゃないか\nでもいまのは　カゲムシャ<key>"), 0, LW(3))
        CASE_EQUAL(3)
        CALL(evt_msg_print, 3, STRING("あいたた<key>"), 0, LW(3))
        CALL(evt_msg_print, 3, STRING("もしかして<key>"), 0, LW(3))
        CALL(evt_msg_print, 3, STRING("このまえきみを\nはんにんあつかいしたことを\nうらんでいるのかね<key>"), 0, LW(3))
        CASE_EQUAL(4)
        CALL(evt_msg_print, 3, STRING("あいたた<key>"), 0, LW(3))
        CALL(evt_msg_print, 3, STRING("もうそろそろやばいって\nしゃれにならんて<key>"), 0, LW(3))
        CASE_EQUAL(5)
        CALL(evt_msg_print, 3, STRING("ぐふっ<key>"), 0, LW(3))
        CALL(evt_msg_print, 3, STRING("もうこれいじょうはあかんて。\nいや、ほんまに。<key>"), 0, LW(3))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(10))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(5))
    IF_INT_EQUAL(LW(5), 5)
        CALL(evt_msg_print, 3, STRING("もう\nからだもたんわー<key>"), 0, BTL_UNIT_SELF)
    END_IF
    SET_VALUE(LW(0), 48)
    LABEL(10)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_AddRotate, LW(10), 0, -15, 0)
    SUBTRACT(LW(0), 1)
    IF_INT_GREATER(LW(0), 0)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_SetRotate, LW(10), 0, 0, 0)
    CALL(btlevtcmd_GetCoin, LW(10), LW(0))
    CALL(btlevtcmd_StoreCoin, LW(0))
    CALL(btlevtcmd_GetExp, LW(10), LW(0))
    CALL(btlevtcmd_StoreExp, LW(0))
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
    CALL(btlevtcmd_CheckDamageCode, LW(10), 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_KillUnit, LW(10), 0)
    ELSE
        CALL(btlevtcmd_KillUnit, LW(10), 2)
    END_IF
    RETURN
EVT_END()

// arg 0: FieldBattleData.postBattleMode
static USER_FUNC(powan_set_post_battle_mode) {
    s32 mode = evtGetValue(event, event->args[0]);

    fbatGetPointer()->postBattleMode = mode;
    return EVT_RETURN_DONE;
}

// arg 0: the event FieldBattleData runs after a won battle
static USER_FUNC(powan_set_post_battle_event) {
    void* evt = (void*)evtGetValue(event, event->args[0]);

    fbatGetPointer()->postBattleEvent = evt;
    return EVT_RETURN_DONE;
}

// args: unit id, part id. Keeps the part on the "pPlane1" joint of the unit's body animation.
static USER_FUNC(powan_rider_follow) {
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 partId = evtGetValue(event, args[1]);
    BattleUnitPart* part;
    BattleWork* wp = _battleWorkPointer;
    const char* joint = "pPlane1";
    AnimationPose* pose;
    s32 idx;
    f32 x;
    f32 y;
    f32 z;

    part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(wp, BattleTransID(event, id)), partId);
    if (part->poseId == -1) {
        return EVT_RETURN_DONE;
    }
    idx = animPoseGetGroupIdx(part->poseId, joint);
    pose = animPoseGetAnimPosePtr(part->poseId);
    if (pose->worldPositions == NULL) {
        animPoseWorldPositionEvalOn(part->poseId);
        x = 0.0f;
        y = -1000.0f;
        z = 0.0f;
    } else {
        x = (*pose->worldPositions)[idx].x;
        y = (*pose->worldPositions)[idx].y;
        z = (*pose->worldPositions)[idx].z;
    }
    BtlUnit_SetPartsPos(part, x, y, z);
#if VERSION >= VERSION_JP // the demos do not print the position
    sysDebugReport("unit_powan.c", 275, "x:%f y:%f z:%f\n", x, y, z);
#endif
    return EVT_RETURN_DONE;
}
