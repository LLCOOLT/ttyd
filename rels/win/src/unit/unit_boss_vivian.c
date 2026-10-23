#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "unit/party/unit_party_vivian.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetMoveSpeed);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetStayPose);
USER_FUNC(btlevtcmd_SetTalkPose);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SortPhaseMoveTable);
USER_FUNC(btlevtcmd_SpawnUnit);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_sub_random);
extern s32 btl_majolyne_zoom[];
extern s32 btl_marilyn_zoom[];
extern s32 btl_vivian_zoom[];
extern s32 majo3_shadow_tail_event[];
extern s32 majo_unison_phase_event[];
extern s32 unit_boss_majolyne[];
extern s32 unit_boss_marilyn[];

__declspec(section ".data") u64 fd_boss_vivian_negone_one_374;
__declspec(section ".data") s32 fd_boss_vivian_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_vivian___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_vivian___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_vivian_one_negone_373;
__declspec(section ".data") s32 fd_boss_vivian___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_vivian_one_381[1];
__declspec(section ".data") u64 fd_boss_vivian_negone_one_360;
__declspec(section ".data") s32 fd_boss_vivian_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_vivian___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_vivian___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_vivian_one_negone_359;
__declspec(section ".data") s32 fd_boss_vivian___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_vivian_one_364[1];
BattleUnitKind unit_boss_vivian;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static __declspec(section ".data") BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
s32 weapon_vivian_kagenuke_attack1[48];
s32 weapon_vivian_flame_attack1[48];
static __declspec(section ".data") s32 entry_marilyn[12];
static __declspec(section ".data") s32 entry_majolyne[12];
static s32 vivian_down[19];
static s32 vivian_up[27];
static s32 init_event[179];
static s32 entry_event[46];
static s32 damage_event[22];
static s32 dead_event[189];
static s32 unison_phase_event[81];
static __declspec(section ".data") s32 phase_event[2];
static s32 attack_event[98];
#ifdef VERSION_G8ME01
static s32 kagenuke_attack_event[207];
#else
static s32 kagenuke_attack_event[204];
#endif
s32 flame_attack_event[185];
#ifdef VERSION_G8ME01
static __declspec(section ".data") s32 wait_event[7];
#else
static __declspec(section ".data") s32 wait_event[6];
#endif

__declspec(section ".data") u64 fd_boss_vivian_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_vivian_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_vivian___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_vivian___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_vivian_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_vivian___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_vivian_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_vivian_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_vivian_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_vivian___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_vivian___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_vivian_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_vivian___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_vivian_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_vivian = {
    33,
    "btl_un_vivian1",
    10,
    0,
    1,
    1,
    26,
    0,
    0,
    100,
    0,
    50,
    9,
    30,
    40,
    0,
    40,
    0.0f,
    20.0f,
    0.0f,
    0,
    0,
    6.0f,
    16.0f,
    0.0f,
    15.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    0.0f,
    11.0f,
    26.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    30.0f,
    40.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_VIVI_DAMAGED1",
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

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {70, 80, 70, 100, 70, 100, 100, 50, 100, 80, 100, 80, 100, 95, 70, 0, 0, 100, 70, 100, 100, 0};

static PoseTableEntry pose_table[] = {
    {1, "PTR_N_1"},
    {2, "PTR_Z_1"},
    {9, "PTR_Z_1"},
    {5, "PTR_X_1"},
    {4, "PTR_X_1"},
    {3, "PTR_X_1"},
    {28, "PTR_S_4"},
    {29, "PTR_Q_1"},
    {30, "PTR_Q_1"},
    {31, "PTR_D_1"},
    {39, "PTR_D_1"},
    {50, "PTR_S_4"},
    {42, "PTR_R_1"},
    {40, "PTR_W_1"},
    {56, "PTR_D_2"},
    {57, "PTR_D_2"},
    {65, "PTR_T_5"},
    {69, "PTR_S_4"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_vivian", "c_vivian", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

s32 weapon_vivian_kagenuke_attack1[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_vivian_flame_attack1[] = {
    0, 0, 0, 0,
#ifdef VERSION_G8ME01
    1677721602,
#else
    1677721600,
#endif
    1065353216, 16843009, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 16777986, 0, 131136, 2047, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") s32 entry_marilyn[] = {
    (s32)unit_boss_marilyn, 16777216, 67108868, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

static __declspec(section ".data") s32 entry_majolyne[] = {
    (s32)unit_boss_majolyne, 16777216, 67108868, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

static s32 vivian_down[] = {
    107, 65546, 250, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_VIVI_SHADOW1", -250000000,
    0, -250000000, 109, 327771, (s32)battle_evt_majo_disp_off, -2, 1, 0,
    0, 2, 1,
};

static s32 vivian_up[] = {
    107, 65546, 250, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_VIVI_SHADOW2", -250000000,
    0, -250000000, 109, 458843, (s32)battle_evt_majo_disp_on, -2, 1, -30000000,
    -29999999, -29999998, 0, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999,
    -29999998, 2, 1,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetEventEntry, -2, PTR(entry_event))
    CALL(btlevtcmd_SetUnitWork, -2, 4, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 5, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 6, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 7, 0)
    CALL(btlevtcmd_GetUnitId, -2, GW(10))
    CALL(btlevtcmd_SpawnUnit, GW(9), PTR(entry_marilyn), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 50)
    ADD(LW(2), 10)
    CALL(btlevtcmd_SetPos, GW(9), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, GW(9), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetUnitWork, GW(9), 4, 1)
    CALL(btlevtcmd_SetUnitWork, GW(9), 5, 1)
    CALL(btlevtcmd_SetUnitWork, GW(9), 6, 0)
    CALL(btlevtcmd_SetUnitWork, GW(9), 7, 0)
    CALL(btlevtcmd_SpawnUnit, GW(8), PTR(entry_majolyne), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 100)
    ADD(LW(2), 20)
    CALL(btlevtcmd_SetPos, GW(8), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, GW(8), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetUnitWork, GW(8), 4, 2)
    CALL(btlevtcmd_SetUnitWork, GW(8), 5, 2)
    CALL(btlevtcmd_SetUnitWork, GW(8), 6, 0)
    CALL(btlevtcmd_SetUnitWork, GW(8), 7, 0)
    SET_VALUE(GW(13), 0)
    SET_VALUE(GW(12), 0)
    SET_VALUE(GW(11), 0)
    SET_VALUE(GW(14), 2)
    CALL(btlevtcmd_SetUnitWork, -2, 8, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 3, 0)
    SPAWN_EVENT(PTR(majo3_shadow_tail_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(entry_event)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    WAIT_FRAMES(60)
    WAIT_FRAMES(60)
    CALL_CHILD(PTR(btl_majolyne_zoom))
    CALL(evt_msg_print, 2, STRING("btl_majo3_00"), 0, GW(8))
    WAIT_MS(300)
    CALL_CHILD(PTR(btl_marilyn_zoom))
    CALL(evt_msg_print, 2, STRING("btl_majo3_01"), 0, GW(9))
    WAIT_MS(300)
    CALL_CHILD(PTR(btl_vivian_zoom))
    CALL(evt_msg_print, 2, STRING("btl_majo3_02"), 0, -2)
    WAIT_MS(300)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_CheckDamageCode, -2, 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GW(13), 1)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, -2, LW(3), LW(4), LW(5))
    SET_VALUE(LW(6), 1)
    IF_INT_EQUAL(LW(0), LW(3))
        IF_INT_EQUAL(LW(1), LW(4))
            IF_INT_EQUAL(LW(2), LW(5))
                SET_VALUE(LW(6), 0)
            END_IF
        END_IF
    END_IF
    IF_INT_EQUAL(LW(6), 1)
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(6.0f))
        CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 40)
        CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -1, 0)
        CALL(btlevtcmd_ResetFaceDirection, -2)
    END_IF
    WAIT_FRAMES(1)
    CALL(btlevtcmd_WaitAttackEnd)
    SWITCH(GW(11))
        CASE_EQUAL(0)
        SWITCH(GW(12))
            CASE_EQUAL(0)
            CASE_EQUAL(1)
            LOOP(0)
                IF_INT_EQUAL(GW(12), 2)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            GOTO(99)
            CASE_EQUAL(2)
        END_SWITCH
        CASE_EQUAL(1)
        LOOP(0)
            IF_INT_EQUAL(GW(11), 2)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        GOTO(99)
        CASE_EQUAL(2)
        SWITCH(GW(12))
            CASE_EQUAL(0)
            CASE_EQUAL(1)
            LOOP(0)
                IF_INT_EQUAL(GW(12), 2)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            GOTO(99)
            CASE_EQUAL(2)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL_CHILD(PTR(btl_vivian_zoom))
            CALL(evt_msg_print, 2, STRING("btl_majo3_13"), 0, -2)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            GOTO(90)
        END_SWITCH
        SWITCH(GW(12))
            CASE_EQUAL(0)
            CASE_DEFAULT
        END_SWITCH
    END_SWITCH
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(btlevtcmd_SetTalkPose, -2, STRING("PTR_D_1"))
    CALL(btlevtcmd_SetStayPose, -2, STRING("PTR_D_1"))
    CALL_CHILD(PTR(btl_vivian_zoom))
    CALL(evt_msg_print, 2, STRING("btl_majo3_10"), 0, -2)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    LABEL(90)
    CALL(evt_btl_camera_set_mode, 0, 0)
    LABEL(99)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PTR_D_3"))
    SET_VALUE(GW(13), 2)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(PTR(subsetevt_dead_core_nospin_norotate))
    RETURN
EVT_END()

static EVT_BEGIN(unison_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108867)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(majo_unison_phase_event))
        CALL(btlevtcmd_GetUnitWork, -2, 4, LW(3))
        CALL(btlevtcmd_GetUnitWork, -2, 5, LW(4))
        IF_INT_NOT_EQUAL(LW(3), LW(4))
            CALL(btlevtcmd_SetUnitWork, -2, 4, LW(4))
            CALL(btlevtcmd_StartWaitEvent, -2)
            CALL_CHILD(PTR(vivian_down))
            WAIT_MS(500)
            SWITCH(LW(4))
                CASE_EQUAL(0)
                SET_VALUE(LW(0), 55)
                SET_VALUE(LW(2), 0)
                CASE_EQUAL(1)
                SET_VALUE(LW(0), 105)
                SET_VALUE(LW(2), 10)
                CASE_EQUAL(2)
                SET_VALUE(LW(0), 155)
                SET_VALUE(LW(2), 20)
            END_SWITCH
            SET_VALUE(LW(1), 0)
            CALL(btlevtcmd_SetHomePos, -2, LW(0), LW(1), LW(2))
            CALL_CHILD(PTR(vivian_up))
            CALL(btlevtcmd_SortPhaseMoveTable)
            CALL(btlevtcmd_StartWaitEvent, -2)
        END_IF
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(phase_event)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 7, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, -2, 8, 1)
        CALL(btlevtcmd_SetUnitWork, -2, 7, 2)
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 8, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        SET_VALUE(LW(9), PTR(weapon_vivian_kagenuke_attack1))
        CALL_CHILD(PTR(kagenuke_attack_event))
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetUnitWork, -2, 8, 2)
        SET_VALUE(LW(9), PTR(weapon_vivian_flame_attack1))
        CALL_CHILD(PTR(flame_attack_event))
        CASE_EQUAL(2)
        SET_VALUE(LW(1), 70)
        ADD(LW(1), 30)
        SUBTRACT(LW(1), 1)
        CALL(evt_sub_random, LW(1), LW(0))
        IF_INT_LESS(LW(0), 70)
            SET_VALUE(LW(9), PTR(weapon_vivian_kagenuke_attack1))
            CALL_CHILD(PTR(kagenuke_attack_event))
            ELSE
            SET_VALUE(LW(9), PTR(weapon_vivian_flame_attack1))
            CALL_CHILD(PTR(flame_attack_event))
        END_IF
    END_SWITCH
    CALL(btlevtcmd_ResetFaceDirection, -2)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 kagenuke_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 65630, (s32)vivian_down, 65546, 300, 327771, (s32)btlevtcmd_GetPos, -29999997,
    -30000000, -29999999, -29999998,
#ifdef VERSION_G8ME01
    131125, -29999998, 5,
#endif
    262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 30,
    131122, -29999999, 0, 65630, (s32)vivian_up, 65546, 300, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PTR_A1_2", 65546, 70, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_VIVI_ATTACK4", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 49, 65539,
    90, 65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256,
    -29999995, 65539, 98, 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 43, 65630, (s32)vivian_down, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    65546, 200, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    65630, (s32)vivian_up, 2, 1,
};

s32 flame_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999991, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PTR_A3_1", 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_VIVI_MAGIC1", -250000000, 0, -250000000, 65546, 1000,
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131122, -29999990, 0, 65539,
    10, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test", 6, -30000000, -29999999, -29999998,
    -229998976, 0, 0, 0, 0, 0, 0, 0,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90,
    65572, 1, 65540, 91, 46, 42, 65540, 98,
    46, 49, 65539, 90, 65540, 97, 65539, 91,
    131096, -29999990, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 33,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131097, -29999997,
    -1, 131125, -29999990, 1, 65540, 10, 33, 65539,
    98, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546, 1000, 2,
    1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

