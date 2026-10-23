#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

typedef struct MajoSortEntry { s32 id; s32 value; } MajoSortEntry;

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_CalculateFaceDirection);
USER_FUNC(btlevtcmd_ChangeFaceDirection);
USER_FUNC(btlevtcmd_CheckActStatus);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_ChoiceSamplingEnemy);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetHp);
USER_FUNC(btlevtcmd_GetMaxHp);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_SamplingEnemy);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetMoveSpeed);
USER_FUNC(btlevtcmd_SetStayPose);
USER_FUNC(btlevtcmd_SetTalkPose);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SortPhaseMoveTable);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(btlevtcmd_TransStageFloorPosition);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_sub_random);
static USER_FUNC(majo3_sort);
extern s32 battle_evt_majo_disp_off[];
extern s32 battle_evt_majo_disp_on[];
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_GetFaceDirection[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SetPos[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_moveto[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_eff[];
extern s32 evt_snd_sfxoff[];
extern s32 subsetevt_confuse_flustered[];
extern s32 subsetevt_dead_core_nospin_norotate[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_boss_majolyne_negone_one_374;
__declspec(section ".data") s32 fd_boss_majolyne_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_majolyne___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_majolyne___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_majolyne_one_negone_373;
__declspec(section ".data") s32 fd_boss_majolyne___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_majolyne_one_381[1];
__declspec(section ".data") u64 fd_boss_majolyne_negone_one_360;
__declspec(section ".data") s32 fd_boss_majolyne_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_majolyne___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_majolyne___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_majolyne_one_negone_359;
__declspec(section ".data") s32 fd_boss_majolyne___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_majolyne_one_364[1];
BattleUnitKind unit_boss_majolyne;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static __declspec(section ".data") BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
static s32 weapon_majolyne_kagenuke_attack1[48];
static s32 weapon_majolyne_blizzard_attack1[48];
static s32 weapon_majolyne_powder_attack1[48];
static s32 weapon_majolyne_powder_attack2[48];
static s32 majolyne_down[19];
static s32 majolyne_up[27];
static s32 majo3_zoom[25];
__declspec(section ".data") s32 btl_vivian_zoom[7];
__declspec(section ".data") s32 btl_marilyn_zoom[7];
__declspec(section ".data") s32 btl_majolyne_zoom[7];
static s32 init_event[45];
static s32 damage_event[22];
static s32 dead_event[122];
s32 majo_unison_phase_event[238];
static s32 unison_phase_event[83];
static s32 phase_event[337];
static s32 attack_event[241];
#ifdef VERSION_G8ME01
static s32 kagenuke_attack_event[225];
#else
static s32 kagenuke_attack_event[222];
#endif
static s32 blizzard_attack_event[243];
static s32 powder_attack_check[16];
static s32 powder_attack_event[179];
static __declspec(section ".data") s32 wait_event[6];
#ifdef VERSION_G8ME01
s32 majo3_shadow_tail_event[79];
#else
s32 majo3_shadow_tail_event[78];
#endif

__declspec(section ".data") u64 fd_boss_majolyne_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_majolyne_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_majolyne___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_majolyne___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_majolyne_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_majolyne___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_majolyne_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_majolyne_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_majolyne_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_majolyne___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_majolyne___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_majolyne_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_majolyne___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_majolyne_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_majolyne = {
    31,
    "btl_un_majolyne1",
    9,
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
    26,
    34,
    0,
    34,
    0.0f,
    17.0f,
    0.0f,
    0,
    0,
    6.0f,
    2.0f,
    0.0f,
    13.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    13.0f,
    0.0f,
    0.0f,
    8.0f,
    22.1f,
    0.0f,
    0.0f,
    17.0f,
    0.0f,
    26.0f,
    34.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_MAJO_DAMAGED1",
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
    {1, "MJR_N_1"},
    {2, "MJR_Z_1"},
    {9, "MJR_Z_1"},
    {5, "MJR_X_1"},
    {4, "MJR_X_1"},
    {3, "MJR_X_1"},
    {28, "MJR_S_1"},
    {29, "MJR_Q_1"},
    {30, "MJR_Q_1"},
    {31, "MJR_D_1"},
    {39, "MJR_D_1"},
    {50, "MJR_S_1"},
    {42, "MJR_R_1"},
    {40, "MJR_W_1"},
    {56, "MJR_S_1"},
    {57, "MJR_S_1"},
    {65, "MJR_T_1"},
    {69, "MJR_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_majolyne1", "c_majyorin", 0.0f, 0.0f, 0.0f, 5.0f, 20.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

static s32 weapon_majolyne_kagenuke_attack1[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 33555202, 0, 7, 2, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_majolyne_blizzard_attack1[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 33555202, 0, 67, 2047, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_majolyne_powder_attack1[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 2, 2, 3, 3, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 143, 2047, -2147475456,
    0, 0, 0, 0, 100, 50462720, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_majolyne_powder_attack2[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, 0,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
#endif
    0, 2, 2, 3, 3, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, -2147475456,
    0, 0, 0, 0, 100, 66977792, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

#ifdef VERSION_G8ME01
static EVT_BEGIN(majolyne_down)
    BEGIN_INLINE_EVENT
        WAIT_MS(250)
        CALL(btlevtcmd_snd_se, -2, STRING("SFX_BOSS_MAJO_SHADOW1"), -250000000, 0, -250000000)
    END_INLINE_EVENT
    CALL(battle_evt_majo_disp_off, -2, 1, 0, 0)
    RETURN
EVT_END()
#else
static s32 majolyne_down[] = {
    107, 65546, 250, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MAJO_SHADOW1", -250000000,
    0, -250000000, 109, 327771, (s32)battle_evt_majo_disp_off, -2, 1, 0,
    0, 2, 1,
};
#endif

#ifdef VERSION_G8ME01
static EVT_BEGIN(majolyne_up)
    BEGIN_INLINE_EVENT
        WAIT_MS(250)
        CALL(btlevtcmd_snd_se, -2, STRING("SFX_BOSS_MAJO_SHADOW2"), -250000000, 0, -250000000)
    END_INLINE_EVENT
    CALL(battle_evt_majo_disp_on, -2, 1, LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    RETURN
EVT_END()
#else
static s32 majolyne_up[] = {
    107, 65546, 250, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MAJO_SHADOW2", -250000000,
    0, -250000000, 109, 458843, (s32)battle_evt_majo_disp_on, -2, 1, -30000000,
    -29999999, -29999998, 0, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999,
    -29999998, 2, 1,
};
#endif

static s32 majo3_zoom[] = {
    327771, (s32)btlevtcmd_GetPos, -30000000, -30000000, -250000000, -250000000, 196699, (s32)evt_btl_camera_set_mode,
    0, 3, 655451, (s32)evt_btl_camera_set_moveto, 0, -30000000, 65, 332,
    -30000000, 30, -340, 30, 11, 65545, 37, 2,
    1,
};

__declspec(section ".data") EVT_BEGIN(btl_vivian_zoom)
    SET_VALUE(LW(0), GW(10))
    CALL_CHILD(PTR(majo3_zoom))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(btl_marilyn_zoom)
    SET_VALUE(LW(0), GW(9))
    CALL_CHILD(PTR(majo3_zoom))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(btl_majolyne_zoom)
    SET_VALUE(LW(0), GW(8))
    CALL_CHILD(PTR(majo3_zoom))
    RETURN
EVT_END()

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 8, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 9, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 3, 0)
    SPAWN_EVENT(PTR(majo3_shadow_tail_event))
    ALLOCATE_UW(10, GW(15))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_CheckDamageCode, -2, 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GW(11), 1)
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
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL_CHILD(PTR(btl_majolyne_zoom))
    WAIT_MS(500)
    CALL(btlevtcmd_SetTalkPose, -2, STRING("MJR_D_1"))
    CALL(btlevtcmd_SetStayPose, -2, STRING("MJR_D_1"))
    IF_INT_NOT_EQUAL(GW(12), 0)
        IF_INT_NOT_EQUAL(GW(13), 0)
            CALL(evt_msg_print, 2, STRING("btl_majo3_11"), 0, -2)
            GOTO(90)
        END_IF
    END_IF
    CALL(evt_msg_print, 2, STRING("btl_majo3_08"), 0, -2)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("MJR_D_3"))
    LABEL(90)
    WAIT_MS(300)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    SET_VALUE(GW(11), 2)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(PTR(subsetevt_dead_core_nospin_norotate))
    RETURN
EVT_END()

EVT_BEGIN(majo_unison_phase_event)
    SET_VALUE(LW(0), -1)
    SET_VALUE(LW(1), -1)
    SET_VALUE(LW(2), -1)
    IF_INT_EQUAL(GW(13), 0)
        CALL(btlevtcmd_GetUnitWork, GW(10), 5, LW(6))
        SWITCH(LW(6))
            CASE_EQUAL(0)
            CALL(btlevtcmd_GetHp, GW(10), LW(0))
            SET_VALUE(LW(3), 1)
            CASE_EQUAL(1)
            CALL(btlevtcmd_GetHp, GW(10), LW(1))
            SET_VALUE(LW(4), 1)
            CASE_EQUAL(2)
            CALL(btlevtcmd_GetHp, GW(10), LW(2))
            SET_VALUE(LW(5), 1)
        END_SWITCH
    END_IF
    IF_INT_EQUAL(GW(12), 0)
        CALL(btlevtcmd_GetUnitWork, GW(9), 5, LW(6))
        SWITCH(LW(6))
            CASE_EQUAL(0)
            CALL(btlevtcmd_GetHp, GW(9), LW(0))
            SET_VALUE(LW(3), 2)
            CASE_EQUAL(1)
            CALL(btlevtcmd_GetHp, GW(9), LW(1))
            SET_VALUE(LW(4), 2)
            CASE_EQUAL(2)
            CALL(btlevtcmd_GetHp, GW(9), LW(2))
            SET_VALUE(LW(5), 2)
        END_SWITCH
    END_IF
    IF_INT_EQUAL(GW(11), 0)
        CALL(btlevtcmd_GetUnitWork, GW(8), 5, LW(6))
        SWITCH(LW(6))
            CASE_EQUAL(0)
            CALL(btlevtcmd_GetHp, GW(8), LW(0))
            SET_VALUE(LW(3), 3)
            CASE_EQUAL(1)
            CALL(btlevtcmd_GetHp, GW(8), LW(1))
            SET_VALUE(LW(4), 3)
            CASE_EQUAL(2)
            CALL(btlevtcmd_GetHp, GW(8), LW(2))
            SET_VALUE(LW(5), 3)
        END_SWITCH
    END_IF
    CALL(majo3_sort)
    SWITCH(LW(0))
        CASE_EQUAL(1)
        IF_INT_EQUAL(GW(13), 0)
            CALL(btlevtcmd_SetUnitWork, GW(10), 5, 0)
        END_IF
        CASE_EQUAL(2)
        IF_INT_EQUAL(GW(12), 0)
            CALL(btlevtcmd_SetUnitWork, GW(9), 5, 0)
        END_IF
        CASE_EQUAL(3)
        IF_INT_EQUAL(GW(11), 0)
            CALL(btlevtcmd_SetUnitWork, GW(8), 5, 0)
        END_IF
    END_SWITCH
    SWITCH(LW(1))
        CASE_EQUAL(1)
        IF_INT_EQUAL(GW(13), 0)
            CALL(btlevtcmd_SetUnitWork, GW(10), 5, 1)
        END_IF
        CASE_EQUAL(2)
        IF_INT_EQUAL(GW(12), 0)
            CALL(btlevtcmd_SetUnitWork, GW(9), 5, 1)
        END_IF
        CASE_EQUAL(3)
        IF_INT_EQUAL(GW(11), 0)
            CALL(btlevtcmd_SetUnitWork, GW(8), 5, 1)
        END_IF
    END_SWITCH
    SWITCH(LW(2))
        CASE_EQUAL(1)
        IF_INT_EQUAL(GW(13), 0)
            CALL(btlevtcmd_SetUnitWork, GW(10), 5, 2)
        END_IF
        CASE_EQUAL(2)
        IF_INT_EQUAL(GW(12), 0)
            CALL(btlevtcmd_SetUnitWork, GW(9), 5, 2)
        END_IF
        CASE_EQUAL(3)
        IF_INT_EQUAL(GW(11), 0)
            CALL(btlevtcmd_SetUnitWork, GW(8), 5, 2)
        END_IF
    END_SWITCH
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
            WAIT_MS(400)
            CALL_CHILD(PTR(majolyne_down))
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
            CALL_CHILD(PTR(majolyne_up))
            CALL(btlevtcmd_SortPhaseMoveTable)
            CALL(btlevtcmd_StartWaitEvent, -2)
        END_IF
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108867)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, -2, 9, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SUBTRACT(LW(0), 1)
            CALL(btlevtcmd_SetUnitWork, -2, 9, LW(0))
        END_IF
        CALL(btlevtcmd_CheckActStatus, -2, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            GOTO(90)
        END_IF
        CALL(btlevtcmd_GetUnitWork, -2, 6, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetMaxHp, -2, LW(0))
            DEBUG_PUT_REG(LW(0))
            MULTIPLY(LW(0), 66)
            DEBUG_PUT_REG(LW(0))
            DIVIDE(LW(0), 100)
            DEBUG_PUT_REG(LW(0))
            CALL(btlevtcmd_GetHp, -2, LW(1))
            DEBUG_PUT_REG(LW(1))
            IF_INT_LESS(LW(1), LW(0))
                CALL(btlevtcmd_SetUnitWork, -2, 6, 1)
                CALL(btlevtcmd_StatusWindowOnOff, 0)
                CALL_CHILD(PTR(btl_majolyne_zoom))
                CALL(evt_msg_print, 2, STRING("btl_majo3_03"), 0, -2)
                WAIT_MS(200)
                CALL(btlevtcmd_GetUnitWork, -2, 7, LW(0))
                IF_INT_EQUAL(LW(0), 0)
                    CALL(btlevtcmd_SetUnitWork, -2, 7, 1)
                    CALL(btlevtcmd_SetUnitWork, -2, 8, 3)
                END_IF
                IF_INT_EQUAL(GW(12), 0)
                    CALL(btlevtcmd_SetUnitWork, GW(9), 7, 1)
                END_IF
                IF_INT_EQUAL(GW(13), 0)
                    CALL(btlevtcmd_SetUnitWork, GW(10), 7, 1)
                END_IF
                CALL(btlevtcmd_StatusWindowOnOff, 1)
                CALL(evt_btl_camera_set_mode, 0, 0)
                CALL(btlevtcmd_StartWaitEvent, -2)
            END_IF
        END_IF
        IF_INT_EQUAL(GW(12), 0)
            CALL(btlevtcmd_GetUnitWork, GW(9), 6, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_GetMaxHp, GW(9), LW(0))
                MULTIPLY(LW(0), 50)
                DIVIDE(LW(0), 100)
                CALL(btlevtcmd_GetHp, GW(9), LW(1))
                IF_INT_LESS(LW(1), LW(0))
                    CALL(btlevtcmd_SetUnitWork, GW(9), 6, 1)
                    CALL(btlevtcmd_StatusWindowOnOff, 0)
                    CALL_CHILD(PTR(btl_majolyne_zoom))
                    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, GW(9), -1, 16, LW(15))
                    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(15))
                    WAIT_MS(200)
                    CALL(evt_msg_print, 2, STRING("btl_majo3_04"), 0, -2)
                    WAIT_MS(200)
                    CALL(btlevtcmd_SetUnitWork, GW(9), 7, 1)
                    CALL(btlevtcmd_CheckActStatus, GW(9), LW(0))
                    IF_INT_NOT_EQUAL(LW(0), 0)
                        CALL_CHILD(PTR(btl_marilyn_zoom))
                        CALL(evt_msg_print, 2, STRING("btl_majo3_05"), 0, GW(9))
                        WAIT_MS(200)
                    END_IF
                    CALL(btlevtcmd_ResetFaceDirection, -2)
                    CALL(btlevtcmd_StatusWindowOnOff, 1)
                    CALL(evt_btl_camera_set_mode, 0, 0)
                    CALL(btlevtcmd_StartWaitEvent, -2)
                END_IF
            END_IF
        END_IF
        IF_INT_EQUAL(GW(13), 0)
            CALL(btlevtcmd_GetUnitWork, GW(10), 6, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_GetMaxHp, GW(10), LW(0))
                MULTIPLY(LW(0), 50)
                DIVIDE(LW(0), 100)
                CALL(btlevtcmd_GetHp, GW(10), LW(1))
                IF_INT_LESS(LW(1), LW(0))
                    CALL(btlevtcmd_SetUnitWork, GW(10), 6, 1)
                    CALL(btlevtcmd_StatusWindowOnOff, 0)
                    CALL_CHILD(PTR(btl_majolyne_zoom))
                    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, GW(10), -1, 16, LW(15))
                    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(15))
                    WAIT_MS(200)
                    CALL(evt_msg_print, 2, STRING("btl_majo3_06"), 0, -2)
                    WAIT_MS(200)
                    CALL(btlevtcmd_SetUnitWork, GW(10), 7, 1)
                    CALL(btlevtcmd_CheckActStatus, GW(10), LW(0))
                    IF_INT_NOT_EQUAL(LW(0), 0)
                        CALL_CHILD(PTR(btl_vivian_zoom))
                        CALL(evt_msg_print, 2, STRING("btl_majo3_07"), 0, GW(10))
                        WAIT_MS(200)
                    END_IF
                    CALL(btlevtcmd_ResetFaceDirection, -2)
                    CALL(btlevtcmd_StatusWindowOnOff, 1)
                    CALL(evt_btl_camera_set_mode, 0, 0)
                    CALL(btlevtcmd_StartWaitEvent, -2)
                END_IF
            END_IF
        END_IF
    END_IF
    LABEL(90)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 8, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_SetUnitWork, -2, 8, 1)
        SET_VALUE(LW(9), PTR(weapon_majolyne_kagenuke_attack1))
        CALL_CHILD(PTR(kagenuke_attack_event))
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetUnitWork, -2, 8, 2)
        SET_VALUE(LW(9), PTR(weapon_majolyne_powder_attack2))
        CALL_CHILD(PTR(powder_attack_check))
        CALL_CHILD(PTR(powder_attack_event))
        CASE_EQUAL(2)
        CALL(btlevtcmd_SetUnitWork, -2, 8, 4)
        SET_VALUE(LW(9), PTR(weapon_majolyne_powder_attack1))
        CALL_CHILD(PTR(powder_attack_check))
        CALL_CHILD(PTR(powder_attack_event))
        CASE_EQUAL(3)
        CALL(btlevtcmd_SetUnitWork, -2, 8, 4)
        CALL(btlevtcmd_SetUnitWork, -2, 9, 2)
        SET_VALUE(LW(9), PTR(weapon_majolyne_blizzard_attack1))
        CALL_CHILD(PTR(blizzard_attack_event))
        CASE_EQUAL(4)
        SET_VALUE(LW(14), 40)
        SET_VALUE(LW(9), PTR(weapon_majolyne_powder_attack1))
        CALL_CHILD(PTR(powder_attack_check))
        IF_INT_NOT_EQUAL(LW(3), -1)
            SET_VALUE(LW(10), LW(3))
            SET_VALUE(LW(11), LW(4))
            CALL(btlevtcmd_CheckStatus, LW(3), 10, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                ADD(LW(14), 20)
            END_IF
        END_IF
        SET_VALUE(LW(9), PTR(weapon_majolyne_powder_attack2))
        CALL_CHILD(PTR(powder_attack_check))
        IF_INT_NOT_EQUAL(LW(3), -1)
            SET_VALUE(LW(12), LW(3))
            SET_VALUE(LW(13), LW(4))
            CALL(btlevtcmd_CheckStatus, LW(3), 11, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                ADD(LW(14), 20)
            END_IF
        END_IF
        CALL(btlevtcmd_GetUnitWork, -2, 7, LW(2))
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_GetUnitWork, -2, 9, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                ADD(LW(14), 20)
            END_IF
        END_IF
        SUBTRACT(LW(14), 1)
        CALL(evt_sub_random, LW(14), LW(0))
        SET_VALUE(LW(1), 40)
        IF_INT_LESS(LW(0), LW(1))
            SET_VALUE(LW(9), PTR(weapon_majolyne_kagenuke_attack1))
            CALL_CHILD(PTR(kagenuke_attack_event))
            GOTO(90)
        END_IF
        ADD(LW(1), 20)
        IF_INT_LESS(LW(0), LW(1))
            SET_VALUE(LW(9), PTR(weapon_majolyne_powder_attack1))
            SET_VALUE(LW(3), LW(10))
            SET_VALUE(LW(4), LW(11))
            CALL_CHILD(PTR(powder_attack_event))
            GOTO(90)
        END_IF
        ADD(LW(1), 20)
        IF_INT_LESS(LW(0), LW(1))
            SET_VALUE(LW(9), PTR(weapon_majolyne_powder_attack2))
            SET_VALUE(LW(3), LW(12))
            SET_VALUE(LW(4), LW(13))
            CALL_CHILD(PTR(powder_attack_event))
            GOTO(90)
            ELSE
            CALL(btlevtcmd_SetUnitWork, -2, 9, 2)
            SET_VALUE(LW(9), PTR(weapon_majolyne_blizzard_attack1))
            CALL_CHILD(PTR(blizzard_attack_event))
        END_IF
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

#ifdef VERSION_G8ME01
static EVT_BEGIN(kagenuke_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
        END_IF
        RETURN
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("MJR_A1_1"))
    CALL_CHILD(majolyne_down)
    WAIT_MS(300)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    ADD(LW(2), 5)
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 30)
    SET_VALUE(LW(1), 0)
    CALL_CHILD(majolyne_up)
    CALL(btlevtcmd_snd_se, -2, STRING("SFX_BOSS_MAJO_PUSH1"), -250000000, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("MJR_A1_2"))
    WAIT_FRAMES(25)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("MJR_A1_3"))
    WAIT_MS(350)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("MJR_A1_4"))
    WAIT_MS(200)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_PreCheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(5))
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
    GOTO(98)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(5))
    LABEL(98)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("MJR_A1_1"))
    CALL_CHILD(majolyne_down)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(200)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL_CHILD(majolyne_up)
    RETURN
EVT_END()
#else
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
    200, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MJR_A1_1", 65630, (s32)majolyne_down,
    65546, 300, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 30, 131122, -29999999, 0,
    65630, (s32)majolyne_up, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MAJO_PUSH1", -250000000, 0,
    -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MJR_A1_2", 65545, 25,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MJR_A1_3", 65546, 350, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MJR_A1_4", 65546, 200, 131163, (s32)evt_snd_sfxoff,
    -29999985, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256,
    -29999995, 65570, -29999995, 65579, 4, 65540, 90, 46,
    65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90,
    46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540,
    90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540,
    90, 65572, 1, 65540, 91, 46, 42, 65540,
    98, 46, 49, 65539, 90, 65540, 98, 65539,
    91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65539, 98, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MJR_A1_1", 65630, (s32)majolyne_down, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 65546, 200, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 65630, (s32)majolyne_up, 2, 1,
};
#endif

#ifdef VERSION_G8ME01
static EVT_BEGIN(blizzard_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
        END_IF
        RETURN
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclareAll, -2)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    CALL(btlevtcmd_snd_se, -2, STRING("SFX_BOSS_MAJO_HAND_OPEN1"), -250000000, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("MJR_A1_2"))
    WAIT_FRAMES(25)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("MJR_A1_3"))
    WAIT_MS(700)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("MJR_A1_4"))
    WAIT_MS(200)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    SET_VALUE(LW(10), 0)
    CALL(btlevtcmd_snd_se, -2, STRING("SFX_BOSS_MAJO_ATTACK_ICE1"), -250000000, 0, LW(15))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetFaceDirection, -2, LW(5))
    IF_INT_GREATER_OR_EQUAL(LW(5), 0)
        CALL(evt_eff, 0, STRING("ibuki"), 0, LW(0), LW(1), LW(2), 180, 0, 0, 0, 0, 0, 0, 0)
        ELSE
        CALL(evt_eff, 0, STRING("ibuki"), 1, LW(0), LW(1), LW(2), 180, 0, 0, 0, 0, 0, 0, 0)
    END_IF
    WAIT_FRAMES(150)
    CALL(evt_snd_sfxoff, LW(15))
    LABEL(10)
    CALL(btlevtcmd_PreCheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(5))
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
    IF_INT_EQUAL(LW(10), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    END_IF
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(5))
    LABEL(97)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(1000)
    RETURN
EVT_END()
#else
static s32 blizzard_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999991, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MAJO_HAND_OPEN1", -250000000, 0,
    -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MJR_A1_2", 65545, 25,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MJR_A1_3", 65546, 700, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MJR_A1_4", 65546, 200, 131163, (s32)evt_snd_sfxoff,
    -29999985, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131122, -29999990, 0,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MAJO_ATTACK_ICE1", -250000000, 0, -29999985, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000,
    -29999999, -29999998, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999995, 131101, -29999995,
    0, 983131, (s32)evt_eff, 0, (s32)"ibuki", 0, -30000000, -29999999,
    -29999998, 180, 0, 0, 0, 0, 0, 0,
    0, 32, 983131, (s32)evt_eff, 0, (s32)"ibuki", 1, -30000000,
    -29999999, -29999998, 180, 0, 0, 0, 0, 0,
    0, 0, 33, 65545, 150, 131163, (s32)evt_snd_sfxoff, -29999985,
    65539, 10, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65570, -29999995, 65579, 4, 65540, 90,
    46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540,
    90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    65540, 90, 65572, 1, 65540, 91, 46, 42,
    65540, 98, 46, 49, 65539, 90, 65540, 97,
    65539, 91, 131096, -29999990, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996,
    131097, -29999997, -1, 131125, -29999990, 1, 65540, 10,
    33, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546,
    1000, 2, 1,
};
#endif

static EVT_BEGIN(powder_attack_check)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    RETURN
EVT_END()

#ifdef VERSION_G8ME01
static EVT_BEGIN(powder_attack_event)
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    IF_INT_EQUAL(LW(9), PTR(weapon_majolyne_powder_attack1))
        CALL(evt_btl_camera_set_mode, 0, 9)
        CALL(evt_btl_camera_set_homing_unit, 0, -2, LW(3))
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
        CALL(evt_btl_camera_set_zoom, 0, 200)
    END_IF
    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(15))
    CALL(btlevtcmd_snd_se, -2, STRING("SFX_BOSS_MAJO_HAND_OPEN1"), -250000000, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("MJR_A2_1"))
    WAIT_MS(700)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("MJR_A2_2"))
    WAIT_MS(100)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("MJR_A2_3"))
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_PreCheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(5))
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
    GOTO(99)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(5))
    WAIT_FRAMES(30)
    GOTO(99)
    LABEL(99)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(250)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()
#else
static s32 powder_attack_event[] = {
    131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000,
    131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540,
    99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2,
    -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991,
    131096, -29999991, (s32)weapon_majolyne_powder_attack1, 196699, (s32)evt_btl_camera_set_mode, 0, 9, 262235,
    (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_btl_camera_set_zoom, 0, 200, 33, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MAJO_HAND_OPEN1", -250000000, 0, -29999985,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MJR_A2_1", 65546, 700, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MJR_A2_2", 65546, 100, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"MJR_A2_3\0\0\0", 131163, (s32)evt_snd_sfxoff, -29999985, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 49,
    65539, 90, 65540, 99, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65545, 30, 65540, 99, 65539, 99,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546, 250, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -2, 2, 1,
};
#endif

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

EVT_BEGIN(majo3_shadow_tail_event)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetUnitWork, -2, 0, LW(0))
    CALL(btlevtcmd_SetUnitWork, -2, 1, LW(1))
    CALL(btlevtcmd_SetUnitWork, -2, 2, LW(2))
    LABEL(0)
    CALL(btlevtcmd_GetUnitId, -2, LW(5))
    IF_INT_EQUAL(LW(5), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 3, LW(5))
    IF_INT_EQUAL(LW(5), 0)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetUnitWork, -2, 0, LW(0))
        CALL(btlevtcmd_SetUnitWork, -2, 1, LW(1))
        CALL(btlevtcmd_SetUnitWork, -2, 2, LW(2))
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

static USER_FUNC(majo3_sort) {
    MajoSortEntry tbl[3];
    MajoSortEntry tmp1;
    MajoSortEntry tmp3;
    MajoSortEntry tmp2;
    s32 i;

    for (i = 0; i < 3; i++) {
        tbl[i].id = event->lwData[3 + i];
        tbl[i].value = event->lwData[i];
    }
    if (tbl[0].value < tbl[1].value) {
        tmp1 = tbl[0];
        tbl[0] = tbl[1];
        tbl[1] = tmp1;
    }
    if (tbl[1].value < tbl[2].value) {
        tmp2 = tbl[1];
        tbl[1] = tbl[2];
        tbl[2] = tmp2;
    }
    if (tbl[0].value < tbl[1].value) {
        tmp3 = tbl[0];
        tbl[0] = tbl[1];
        tbl[1] = tmp3;
    }
    for (i = 0; i < 3; i++) {
        event->lwData[i] = tbl[i].id;
    }
    return EVT_RETURN_DONE;
}
