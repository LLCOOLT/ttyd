#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_sub.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_AnimeWaitPlayLoopTiming);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_ClearAllStatus);
USER_FUNC(btlevtcmd_DivePosition);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetDamage);
USER_FUNC(btlevtcmd_GetDamagePartsId);
USER_FUNC(btlevtcmd_GetHitPos);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetMaxHp);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_JumpPosition);
USER_FUNC(btlevtcmd_OffAttribute);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_OnUnitFlag);
USER_FUNC(btlevtcmd_PhaseEventStartDeclare);
USER_FUNC(btlevtcmd_RunDataEventChild);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventUnisonPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetFallAccel);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetHp);
USER_FUNC(btlevtcmd_SetMaxMoveCount);
USER_FUNC(btlevtcmd_SetRotate);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_TransStageFloorPosition);
USER_FUNC(btlevtcmd_WaitEventEnd);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_eff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_sub_intpl_get_value);
USER_FUNC(evt_sub_intpl_init);

__declspec(section ".data") u64 fd_boss_cortez_sword_negone_one_374;
__declspec(section ".data") s32 fd_boss_cortez_sword_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_cortez_sword___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_cortez_sword___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_cortez_sword_one_negone_373;
__declspec(section ".data") s32 fd_boss_cortez_sword___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_cortez_sword_one_381[1];
__declspec(section ".data") u64 fd_boss_cortez_sword_negone_one_360;
__declspec(section ".data") s32 fd_boss_cortez_sword_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_cortez_sword___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_cortez_sword___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_cortez_sword_one_negone_359;
__declspec(section ".data") s32 fd_boss_cortez_sword___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_cortez_sword_one_364[1];
BattleUnitKind unit_boss_cortez_sword;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
s32 weapon_cortez_sword_float_attack[48];
static __declspec(section ".data") PoseTableEntry pose_table[6];
__declspec(section ".data") PoseTableEntry pose_table_otitabuki[4];
static __declspec(section ".data") PoseTableEntry pose_table_break[4];
static BattleDataEntry data_table[21];
static BattleUnitKindPart parts[1];
static s32 init_event[47];
static __declspec(section ".data") s32 damage_event[10];
static s32 avoid_thorn_event[33];
s32 cortez_weapon_get_home_height[144];
s32 cortez_weapon_set_formation_attribute[27];
s32 cortez_weapon_unison_phase_event[79];
s32 cortez_weapon_phase_event[115];
static s32 attack_event[862];
static __declspec(section ".data") s32 wait_event[10];
static s32 cortez_damage_sub_event[25];
s32 cortez_weapon_counter_damage_event[113];
static __declspec(section ".data") s32 dead_event[2];
s32 cortez_weapon_dead_event[100];
s32 cortez_weapon_break_event[88];
s32 cortez_weapon_blow_dead_event[121];

__declspec(section ".data") u64 fd_boss_cortez_sword_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_cortez_sword_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_cortez_sword___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_cortez_sword___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_cortez_sword_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_cortez_sword___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_cortez_sword_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_cortez_sword_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_cortez_sword_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_cortez_sword___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_cortez_sword___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_cortez_sword_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_cortez_sword___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_cortez_sword_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_cortez_sword = {
    97,
    "btl_un_cortez_sword",
    4,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    20,
    130,
    30,
    0,
    30,
    0.0f,
    15.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    65.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    65.0f,
    0.0f,
    0.0f,
    65.0f,
    19.5f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    130.0f,
    30.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_KOR_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x2000004,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 80, 95, 100, 90, 100, 100, 85, 0, 0, 100, 0, 100, 90, 50, 0, 90, 100, 50, 0, 0, 0};

s32 weapon_cortez_sword_float_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") PoseTableEntry pose_table[] = {
    {2, "KRT_Z_1"},
    {9, "KRT_Z_1"},
    {28, "KRT_S_1"},
    {31, "KRT_S_1"},
    {39, "KRT_S_1"},
    {69, "KRT_S_1"},
};

__declspec(section ".data") PoseTableEntry pose_table_otitabuki[] = {
    {28, "KRT_Z_1"},
    {31, "KRT_Z_1"},
    {39, "KRT_Z_1"},
    {69, "KRT_Z_1"},
};

static __declspec(section ".data") PoseTableEntry pose_table_break[] = {
    {28, "KRT_Z_1"},
    {31, "KRT_Z_1"},
    {39, "KRT_Z_1"},
    {69, "KRT_Z_1"},
};

static BattleDataEntry data_table[] = {
    {9, cortez_damage_sub_event},
    {49, cortez_weapon_dead_event},
    {71, cortez_weapon_break_event},
    {58, cortez_weapon_blow_dead_event},
    {36, cortez_weapon_counter_damage_event},
    {24, cortez_weapon_counter_damage_event},
    {25, cortez_weapon_counter_damage_event},
    {26, cortez_weapon_counter_damage_event},
    {27, cortez_weapon_counter_damage_event},
    {28, cortez_weapon_counter_damage_event},
    {29, cortez_weapon_counter_damage_event},
    {30, cortez_weapon_counter_damage_event},
    {31, cortez_weapon_counter_damage_event},
    {32, cortez_weapon_counter_damage_event},
    {33, cortez_weapon_counter_damage_event},
    {34, cortez_weapon_counter_damage_event},
    {35, cortez_weapon_counter_damage_event},
    {39, avoid_thorn_event},
    {37, avoid_thorn_event},
    {38, avoid_thorn_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_cortez_sword", "c_buki2", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x3010009, 0x7, pose_table},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_OnUnitFlag, -2, 16777216)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(cortez_weapon_phase_event))
    CALL(btlevtcmd_SetEventUnisonPhase, -2, PTR(cortez_weapon_unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 2, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_SetMaxMoveCount, -2, 0)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(avoid_thorn_event)
    CALL(btlevtcmd_GetHitPos, -2, 1, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 40)
    ADD(LW(2), 5)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(cortez_weapon_get_home_height)
    SET_VALUE(LW(5), 0)
    CALL(btlevtcmd_GetPos, LW(9), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitWork, LW(9), 0, LW(3))
    CALL(btlevtcmd_GetUnitWork, LW(3), 8, LW(4))
    SWITCH(LW(4))
        CASE_EQUAL(0)
        CALL(btlevtcmd_GetUnitWork, LW(9), 2, LW(6))
        SWITCH(LW(6))
            CASE_EQUAL(0)
            ADD(LW(5), 20)
            CASE_EQUAL(1)
            ADD(LW(5), 60)
            CASE_EQUAL(2)
            ADD(LW(5), 60)
            CASE_EQUAL(3)
            ADD(LW(5), 20)
        END_SWITCH
        CASE_EQUAL(1)
        CALL(btlevtcmd_GetUnitWork, LW(9), 2, LW(6))
        SWITCH(LW(6))
            CASE_EQUAL(0)
            ADD(LW(5), 20)
            CASE_EQUAL(1)
            ADD(LW(5), 20)
            CASE_EQUAL(2)
            ADD(LW(5), 60)
            CASE_EQUAL(3)
            ADD(LW(5), 60)
        END_SWITCH
        CASE_EQUAL(2)
        CALL(btlevtcmd_GetUnitWork, LW(9), 2, LW(6))
        SWITCH(LW(6))
            CASE_EQUAL(0)
            ADD(LW(5), 60)
            CASE_EQUAL(1)
            ADD(LW(5), 20)
            CASE_EQUAL(2)
            ADD(LW(5), 60)
            CASE_EQUAL(3)
            ADD(LW(5), 20)
        END_SWITCH
        CASE_EQUAL(3)
        CALL(btlevtcmd_GetUnitWork, LW(9), 2, LW(6))
        SWITCH(LW(6))
            CASE_EQUAL(0)
            ADD(LW(5), 60)
            CASE_EQUAL(1)
            ADD(LW(5), 20)
            CASE_EQUAL(2)
            ADD(LW(5), 20)
            CASE_EQUAL(3)
            ADD(LW(5), 60)
        END_SWITCH
    END_SWITCH
    RETURN
EVT_END()

s32 cortez_weapon_set_formation_attribute[] = {
    196699, (s32)btlevtcmd_GetBodyId, -29999991, -30000000, 327771, (s32)btlevtcmd_GetHomePos, -29999991, -250000000,
    -29999999, -250000000, 131101, -29999999, 40, 262235, (s32)btlevtcmd_OnPartsAttribute, -29999991,
    -30000000, 6291456, 32, 262235, (s32)btlevtcmd_OffPartsAttribute, -29999991, -30000000, 6291456,
    33, 2, 1,
};

EVT_BEGIN(cortez_weapon_unison_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108865)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
        IF_INT_EQUAL(LW(0), -1)
            RETURN
        END_IF
        CALL(btlevtcmd_GetUnitWork, LW(0), 5, LW(1))
        IF_INT_GREATER_OR_EQUAL(LW(1), 4)
            CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_GetUnitId, -2, LW(9))
                IF_INT_EQUAL(LW(9), -1)
                    RETURN
                END_IF
                CALL_CHILD(PTR(cortez_weapon_get_home_height))
                IF_INT_NOT_EQUAL(LW(1), LW(5))
                    CALL(btlevtcmd_PhaseEventStartDeclare, -2)
                    CALL(btlevtcmd_DivePosition, -2, LW(0), LW(5), LW(2), 60, 0, 4, 0, -1)
                    CALL(btlevtcmd_SetHomePos, -2, LW(0), LW(5), LW(2))
                    CALL_CHILD(PTR(cortez_weapon_set_formation_attribute))
                    CALL(btlevtcmd_StartWaitEvent, -2)
                    RETURN
                END_IF
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(cortez_weapon_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108865)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            SUBTRACT(LW(0), 1)
            CALL(btlevtcmd_SetUnitWork, -2, 1, LW(0))
            IF_INT_LESS_OR_EQUAL(LW(0), 0)
                CALL(btlevtcmd_PhaseEventStartDeclare, -2)
                BEGIN_SIBLING_EVENT_GET_ID(LW(0))
                    CALL(evt_sub_intpl_init, 5, -90, 0, 20)
                    CALL(evt_sub_intpl_get_value)
                    LOOP(20)
                        CALL(evt_sub_intpl_get_value)
                        CALL(btlevtcmd_SetRotate, -2, LW(0), 0, 0)
                        WAIT_FRAMES(1)
                    END_LOOP
                END_SIBLING_EVENT
                CALL(btlevtcmd_WaitEventEnd, LW(0))
                CALL(btlevtcmd_GetUnitId, -2, LW(9))
                CALL_CHILD(PTR(cortez_weapon_get_home_height))
                CALL(btlevtcmd_DivePosition, -2, LW(0), LW(5), LW(2), 60, 0, 4, 0, -1)
                CALL(btlevtcmd_SetHomePos, -2, LW(0), LW(5), LW(2))
                CALL_CHILD(PTR(cortez_weapon_set_formation_attribute))
                CALL(btlevtcmd_GetMaxHp, -2, LW(0))
                CALL(btlevtcmd_SetHp, -2, LW(0))
                CALL(btlevtcmd_ClearAllStatus, -2)
                CALL(btlevtcmd_OffPartsAttribute, -2, 1, 65536)
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table))
                CALL(btlevtcmd_OffAttribute, -2, 33554432)
                CALL(btlevtcmd_StartWaitEvent, -2)
                RETURN
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

static s32 attack_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -30000000, 131097, -30000000, 0,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 131122, -29999988, (s32)weapon_cortez_sword_float_attack,
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999988, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997, -29999996, 131096, -29999997,
    -1, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999988, 196699, (s32)btlevtcmd_AnimeWaitPlayLoopTiming, -2, 1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KRT_Z_1", 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 48, 19, 0, 110,
    327771, (s32)evt_sub_intpl_init, 0, 0, -30, 30, 65627, (s32)evt_sub_intpl_get_value,
    65541, 30, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, -30000000,
    -250000000, -250000000, 65545, 1, 6, 112, 110, 65545,
    10, 327771, (s32)evt_sub_intpl_init, 2, 0, -55, 30, 65627,
    (s32)evt_sub_intpl_get_value, 65541, 30, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2,
    -250000000, -250000000, -30000000, 65545, 1, 6, 112, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125, -29999999,
    -20, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 105, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 40, -10, 4, 0,
    0, 65647, -29999985, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 20, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 52, 0, 1, 0,
    0, 112, 196699, (s32)evt_sub_random, 40, -29999995, 131125, -29999995,
    12, 65545, -29999995, 65631, -29999985, 65647, -29999985, 327771,
    (s32)evt_sub_intpl_init, 2, 0, 475, 30, 65627, (s32)evt_sub_intpl_get_value, 65541,
    30, 65627, (s32)evt_sub_intpl_get_value, 131125, -30000000, -55, 327771, (s32)btlevtcmd_SetRotate,
    -2, -250000000, -250000000, -30000000, 65545, 1, 6, 112,
    110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_SWORD_DANCE1", -250000000, 0, -250000000,
    112, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    131125, -29999999, -20, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 45,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 28, 0,
    0, 0, 0, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    -29999988, 256, -29999995, 65570, -29999995, 65579, 4, 65540,
    40, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    65540, 40, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    65540, 40, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    65540, 40, 42, 65540, 41, 49, 65539, 40,
    196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 65540, 45, 65539, 41,
    196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999988, 0, -29999994, 131096, -29999994, 21, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 50, 131125, -29999999, 15, 110, 327771, (s32)evt_sub_intpl_init,
    5, -30, 0, 20, 65627, (s32)evt_sub_intpl_get_value, 65541, 21,
    65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, -30000000, -250000000, -250000000,
    65545, 1, 6, 112, 110, 327771, (s32)evt_sub_intpl_init, 5,
    0, -30, 20, 65627, (s32)evt_sub_intpl_get_value, 65541, 21, 65627,
    (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, -250000000, -250000000, -30000000, 65545,
    1, 6, 112, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, 21, 0, 5, 0, -1, 110, 327771,
    (s32)evt_sub_intpl_init, 4, -30, 0, 20, 65627, (s32)evt_sub_intpl_get_value, 65541,
    21, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, -250000000, -250000000,
    -30000000, 65545, 1, 6, 112, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, 40, 0, 4, 0, -1, 2, 33,
    65539, 45, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 65546, 800, 65539,
    50, 110, 327771, (s32)evt_sub_intpl_init, 2, 60, -225, 30,
    65627, (s32)evt_sub_intpl_get_value, 65541, 30, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate,
    -2, -250000000, -250000000, -30000000, 65545, 1, 6, 112,
    110, 327771, (s32)evt_sub_intpl_init, 2, -30, -90, 20, 65627,
    (s32)evt_sub_intpl_get_value, 65541, 20, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2,
    -30000000, -250000000, -250000000, 65545, 1, 6, 112, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 35, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    30, -15, 5, 0, -1, 65546, 300, 65647,
    -29999986, 327771, (s32)evt_sub_intpl_init, 5, -225, 180, 30, 65627,
    (s32)evt_sub_intpl_get_value, 65541, 30, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2,
    -250000000, -250000000, -30000000, 65545, 1, 6, 112, 65647,
    -29999985, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    131125, -29999999, -20, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -30000000, 60,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 30, 0,
    6, 0, 0, 112, 110, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_KOR_SWORD_DANCE3", -250000000, 0, -250000000, 112, 65545, 7, 65570,
    -29999995, 65579, 4, 65540, 90, 46, 65572, 3,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 42, 65540,
    91, 49, 65539, 90, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1,
    65540, 95, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 256, -29999994,
    131096, -29999994, 21, 65631, -29999986, 65631, -29999985, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 50,
    131125, -29999999, 15, 110, 327771, (s32)evt_sub_intpl_init, 5, 0,
    -30, 20, 65627, (s32)evt_sub_intpl_get_value, 65541, 21, 65627, (s32)evt_sub_intpl_get_value,
    327771, (s32)btlevtcmd_SetRotate, -2, -250000000, -250000000, -30000000, 65545, 1,
    6, 112, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    21, 0, 5, 0, -1, 110, 327771, (s32)evt_sub_intpl_init,
    4, -30, 0, 20, 65627, (s32)evt_sub_intpl_get_value, 65541, 21,
    65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, -250000000, -250000000, -30000000,
    65545, 1, 6, 112, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    40, 0, 4, 0, -1, 2, 33, 65539,
    95, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 65546, 300, 65647, -29999985,
    327771, (s32)evt_sub_intpl_init, 11, -90, 0, 10, 65627, (s32)evt_sub_intpl_get_value,
    65541, 10, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, -30000000,
    -250000000, -250000000, 65545, 1, 6, 112, 131163, (s32)btlevtcmd_WaitEventEnd,
    -29999985, 262235, (s32)btlevtcmd_GetStageSize, -29999999, -250000000, -250000000, 131125, -29999999,
    80, 131122, -30000000, 0, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    -29999999, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999999, -29999998, 458843,
    (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998, -229994880, -29999987, 655451,
    (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, -29999987, 0, 1,
    0, -1, 65546, 500, 262235, (s32)btlevtcmd_GetStageSize, -29999999, -250000000,
    -250000000, 131125, -29999999, 80, 131122, -30000000, 0, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, -29999999, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000,
    -29999999, -29999998, 40, 0, 4, 0, -1, 65539,
    99, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeWaitPlayLoopTiming, -2, 1)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static EVT_BEGIN(cortez_damage_sub_event)
    CALL(btlevtcmd_GetDamage, LW(10), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_GetDamagePartsId, -2, LW(11))
    CALL(btlevtcmd_AnimeChangePose, LW(10), 1, STRING("KRT_Z_1"))
    WAIT_FRAMES(30)
    LABEL(90)
    RETURN
EVT_END()

EVT_BEGIN(cortez_weapon_counter_damage_event)
    CALL(btlevtcmd_OnUnitFlag, LW(10), 1)
    SWITCH(LW(0))
        CASE_EQUAL(43)
        CALL(evt_snd_sfxon, STRING("SFX_BTL_ATTACK_MISS3"), 0)
        SET_VALUE(LW(14), 36)
        CASE_OR_EQUAL(46)
        CASE_OR_EQUAL(49)
        CASE_OR_EQUAL(50)
        CASE_OR_EQUAL(54)
        SET_VALUE(LW(14), 29)
        CASE_END
        CASE_DEFAULT
        SET_VALUE(LW(14), 39)
    END_SWITCH
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_RunDataEventChild, LW(10), 10)
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, LW(10), LW(2), LW(3), LW(4))
    CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(2), 25)
    ADD(LW(3), 25)
    CALL(btlevtcmd_DivePosition, LW(10), LW(2), LW(3), LW(4), 5, 0, 0, 0, -1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(1.0f))
    CALL(btlevtcmd_GetHomePos, LW(10), LW(2), LW(3), LW(4))
    CALL(btlevtcmd_TransStageFloorPosition, LW(2), LW(3), LW(4))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(2), LW(3), LW(4), 20, -1)
    CALL(btlevtcmd_JumpPosition, LW(10), LW(2), LW(3), LW(4), 10, -1)
    WAIT_FRAMES(30)
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(dead_event)
    RETURN
EVT_END()

s32 cortez_weapon_dead_event[] = {
    327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 0, 0, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999,
    -29999998, 131125, -29999999, 1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999591,
    393307, (s32)btlevtcmd_FallPosition, -2, -30000000, -29999999, -29999998, 30, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_SWORD_FALL1", -250000000, 0, -250000000, 110, 327771,
    (s32)evt_sub_intpl_init, 0, 0, -90, 15, 65627, (s32)evt_sub_intpl_get_value, 65541,
    15, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, -30000000, 0,
    0, 65545, 1, 6, 112, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 15, -1, 327771, (s32)btlevtcmd_SetHomePos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 2,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1, 65536, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2,
    1, (s32)pose_table_break, 196699, (s32)btlevtcmd_OnAttribute, -2, 33554432, 196699, (s32)btlevtcmd_KillUnit,
    -2, 1, 2, 1,
};

s32 cortez_weapon_break_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131097, -30000000, -1,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -29999999, 65570, -29999999, 65572,
    0, 262235, (s32)btlevtcmd_SetUnitWork, -30000000, 1, -1, 65572, 1,
    262235, (s32)btlevtcmd_SetUnitWork, -30000000, 2, -1, 65572, 2, 262235,
    (s32)btlevtcmd_SetUnitWork, -30000000, 3, -1, 65572, 3, 262235, (s32)btlevtcmd_SetUnitWork,
    -30000000, 4, -1, 49, 33, 262235, (s32)btlevtcmd_OnPartsAttribute, -2,
    1, 50331648, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_ENEMY_DIE1_2", -250000000, 0,
    -250000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125,
    -29999998, 10, 983131, (s32)evt_eff, 0, (s32)"kemuri_test", 4, -30000000,
    -29999999, -29999998, -229998976, 0, 0, 0, 0, 0,
    0, 0, 196699, (s32)btlevtcmd_KillUnit, -2, 1, 2, 1,
};

s32 cortez_weapon_blow_dead_event[] = {
    196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_CLAUD_BREATH3\0\0", 0, 196699, (s32)btlevtcmd_GetBodyId, -2, -30000000,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -30000000, 39, 110, 65539, 0,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 20, 0, 65545, 1,
    65540, 0, 112, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229997952, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize, -30000000,
    -250000000, -250000000, 131125, -29999999, 40, 655451, (s32)btlevtcmd_DivePosition, -2,
    -30000000, -29999999, -29999998, 0, -10, 2, 0, -1,
    196699, (s32)btlevtcmd_GetCoin, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreCoin, -30000000, 196699,
    (s32)btlevtcmd_GetExp, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreExp, -30000000, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 0, -30000000, 131097, -30000000, -1, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 2, -29999999, 65570, -29999999, 65572, 0, 262235,
    (s32)btlevtcmd_SetUnitWork, -30000000, 1, -1, 65572, 1, 262235, (s32)btlevtcmd_SetUnitWork,
    -30000000, 2, -1, 65572, 2, 262235, (s32)btlevtcmd_SetUnitWork, -30000000,
    3, -1, 65572, 3, 262235, (s32)btlevtcmd_SetUnitWork, -30000000, 4,
    -1, 49, 33, 196699, (s32)btlevtcmd_KillUnit, -2, 0, 2,
    1,
};

