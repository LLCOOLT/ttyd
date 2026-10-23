#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "manager/evtmgr_cmd.h"

static s32 x_flag_data[2];
f32 intplGetValue(s32 mode, s32 currStep, f32 start, f32 end, s32 steps);

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_DrawLots);
USER_FUNC(btlevtcmd_GetHpGaugeOffset);
USER_FUNC(btlevtcmd_GetStatusMg);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_GetUnitWorkFloat);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHitCursorOffset);
USER_FUNC(btlevtcmd_SetHitOffset);
USER_FUNC(btlevtcmd_SetHpGaugeOffset);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetUnitWorkFloat);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveSpeedLv);
USER_FUNC(evt_btl_camera_set_moveto);
USER_FUNC(evt_env_blur_on);
static USER_FUNC(x_flag_wait);
static USER_FUNC(x_flag_get);
static USER_FUNC(x_flag_add);
static USER_FUNC(x_flag_set);
static USER_FUNC(wariai_enzan_0f);
static USER_FUNC(wariai_enzan_0);
USER_FUNC(wariai_enzan_1f_intpl_w);
static USER_FUNC(wariai_enzan_1f_intpl);
static USER_FUNC(wariai_enzan_1f);
static USER_FUNC(wariai_enzan_1);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_AnimeSetPoseTable[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckActStatus[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckPhase[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetBodyId[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetHp[];
extern s32 btlevtcmd_GetMaxHp[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_GetPosFloat[];
extern s32 btlevtcmd_GetRotate[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetUnitKind[];
extern s32 btlevtcmd_JumpContinue[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MoveDirectionAdd[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_OnUnitFlag[];
extern s32 btlevtcmd_PartsFaceDirectionSub[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_RunDataEventChild[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetBaseScale[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SetStayPose[];
extern s32 btlevtcmd_SetStayPoseType[];
extern s32 btlevtcmd_SetTalkPose[];
extern s32 btlevtcmd_SetTalkPoseType[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_StatusWindowOnOff[];
extern s32 btlevtcmd_StopWaitEvent[];
extern s32 btlevtcmd_TransStageFloorPosition[];
extern s32 btlevtcmd_WaitAttackEnd[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_cam_shake[];
extern s32 evt_eff64[];
extern s32 evt_eff_delete[];
extern s32 evt_msg_print[];
extern s32 evt_msg_print_battle_party[];
extern s32 evt_snd_sfxoff[];
extern s32 evt_snd_sfxon[];
extern s32 evt_snd_sfxon_3d[];
extern s32 subsetevt_confuse_flustered[];
extern s32 subsetevt_dead_core_nospin_norotate[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_boss_macho_gance_negone_one_374;
__declspec(section ".data") s32 fd_boss_macho_gance_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_macho_gance___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_macho_gance___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_macho_gance_one_negone_373;
__declspec(section ".data") s32 fd_boss_macho_gance___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_macho_gance_one_381[1];
__declspec(section ".data") u64 fd_boss_macho_gance_negone_one_360;
__declspec(section ".data") s32 fd_boss_macho_gance_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_macho_gance___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_macho_gance___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_macho_gance_one_negone_359;
__declspec(section ".data") s32 fd_boss_macho_gance___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_macho_gance_one_364[1];
BattleUnitKind unit_boss_macho_gance;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_furafura[18];
static BattleDataEntry data_table[15];
static BattleUnitKindPart parts[1];
s32 weapon_gance_macho_speed[48];
s32 weapon_gance_build_up[48];
s32 weapon_gance_body[48];
s32 weapon_gance_footwork[48];
s32 weapon_gance_attack[48];
s32 weapon_gance_posing[48];
s32 weapon_gance_rariat_attack[48];
s32 weapon_gance_body_attack[48];
s32 macho_gance_zoom[65];
s32 macho_gance_blur_zoom[46];
static s32 mario_party_zoom[34];
static s32 init_event[79];
static s32 entry_event[62];
static s32 damage_event[97];
s32 base_size_change[99];
static s32 phase_event[482];
static s32 dead_event[64];
s32 macho_gance_damage_event[238];
static s32 attack_event[151];
s32 gance_macho_speed_attack_event[119];
s32 gance_build_up_attack_event[119];
s32 gance_body_attack_event[126];
s32 gance_footwork_attack_event[119];
s32 gance_attack_attack_event[541];
s32 gance_posing_attack_event[129];
s32 gance_rariat_attack_attack_event[446];
s32 gance_body_attack_attack_event[515];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_boss_macho_gance_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_macho_gance_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_macho_gance___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_macho_gance___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_macho_gance_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_macho_gance___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_macho_gance_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_macho_gance_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_macho_gance_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_macho_gance___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_macho_gance___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_macho_gance_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_macho_gance___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_macho_gance_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_macho_gance = {
    65,
    "btl_un_macho_gance",
    60,
    0,
    1,
    1,
    71,
    0,
    0,
    100,
    0,
    50,
    6,
    116,
    124,
    30,
    100,
    0.0f,
    62.0f,
    0.0f,
    0,
    -3,
    40.0f,
    80.0f,
    0.0f,
    58.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    58.0f,
    0.0f,
    0.0f,
    42.0f,
    80.0f,
    0.0f,
    0.0f,
    62.0f,
    0.0f,
    116.0f,
    124.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_GANSU_DAMAGED1",
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

static __declspec(section ".data") StatusVulnerability regist = {50, 40, 50, 100, 50, 100, 100, 30, 0, 75, 100, 75, 100, 90, 60, 0, 0, 100, 60, 100, 100, 0};

static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "K_1"},
    {28, "S_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "D_1"},
    {39, "D_1"},
    {50, "E_1A"},
    {42, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static PoseTableEntry pose_table_furafura[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "K_1"},
    {28, "X_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "D_1"},
    {39, "D_1"},
    {50, "E_1A"},
    {42, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "X_1"},
};

static BattleDataEntry data_table[] = {
    {49, dead_event},
    {36, macho_gance_damage_event},
    {24, macho_gance_damage_event},
    {25, macho_gance_damage_event},
    {26, macho_gance_damage_event},
    {27, macho_gance_damage_event},
    {28, macho_gance_damage_event},
    {29, macho_gance_damage_event},
    {30, macho_gance_damage_event},
    {31, macho_gance_damage_event},
    {32, macho_gance_damage_event},
    {33, macho_gance_damage_event},
    {34, macho_gance_damage_event},
    {35, macho_gance_damage_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_macho_gance", "c_m_gansu", 0.0f, 0.0f, 0.0f, 26.0f, 77.0f, 0.0f, 25.0f, 81.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

s32 weapon_gance_macho_speed[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 135, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    1677983744, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_gance_build_up[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 135, 0, -2147475452,
    0, 0, 0, 0, 0, 25601, 50331648, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_gance_body[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 135, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 6554115, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_gance_footwork[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 135, 0, -2147475452,
    0, 0, 0, 6554112, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_gance_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 770, 0, 4231, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_gance_posing[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 136, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 4,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_gance_rariat_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 4231, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_gance_body_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 656130, 0, 4231, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1644900, 0, 0,
};

EVT_BEGIN(macho_gance_zoom)
    CALL(btlevtcmd_GetStatusMg, -2, LW(2))
    MULTIPLY_FLOAT(LW(2), FLOAT(10.0f))
    CALL(btlevtcmd_GetUnitWorkFloat, -2, 3, LW(1))
    MULTIPLY_FLOAT(LW(2), LW(1))
    CALL(evt_btl_camera_set_mode, 0, 3)
    IF_INT_NOT_EQUAL(LW(0), 2)
        SET_VALUE(LW(1), 30)
        ELSE
        SET_VALUE(LW(1), 1)
    END_IF
    IF_INT_LESS_OR_EQUAL(LW(2), FLOAT(10.0f))
        CALL(evt_btl_camera_set_moveto, 0, 83, 124, 512, 83, 89, 0, LW(1), 11)
        ELSE
        CALL(evt_btl_camera_set_moveto, 0, 71, 159, 609, 71, 118, 0, LW(1), 11)
    END_IF
    IF_INT_EQUAL(LW(0), 1)
        WAIT_MS(600)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(macho_gance_blur_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    IF_INT_NOT_EQUAL(LW(0), 2)
        SET_VALUE(LW(1), 48)
        SET_VALUE(LW(2), 800)
        ELSE
        SET_VALUE(LW(1), 1)
        SET_VALUE(LW(2), 16)
    END_IF
    CALL(evt_btl_camera_set_moveto, 0, 83, 137, 701, 83, 89, 0, LW(1), 11)
    BEGIN_INLINE_EVENT
        CALL(evt_env_blur_on, 0, LW(2))
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(0), 1)
        WAIT_MS(900)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(mario_party_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    IF_INT_NOT_EQUAL(LW(0), 2)
        SET_VALUE(LW(1), 30)
        ELSE
        SET_VALUE(LW(1), 1)
    END_IF
    CALL(evt_btl_camera_set_moveto, 0, -111, 67, 275, -111, 49, 0, LW(1), 11)
    IF_INT_EQUAL(LW(0), 1)
        WAIT_MS(600)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_BOSS_GANSU_MOVE1L"), STRING("SFX_BOSS_GANSU_MOVE1R"), 0, 10, 10)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_BOSS_GANSU_MOVE1L"), STRING("SFX_BOSS_GANSU_MOVE1R"), 0, 20, 20)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetEventEntry, -2, PTR(entry_event))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 2, 0)
    CALL(btlevtcmd_SetUnitWorkFloat, -2, 3, FLOAT(1.0f))
    CALL(btlevtcmd_SetHitOffset, -2, 1, 0, 0, 0)
    CALL(btlevtcmd_SetHitCursorOffset, -2, 1, 0, 0, 0)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 entry_event[] = {
    131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 131122, -30000000, 2, 65630, (s32)macho_gance_zoom,
    65546, 1000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING1", -250000000, 0,
    -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"E_1A", 65546, 1500,
    131163, (s32)evt_snd_sfxoff, -29999985, 327771, (s32)evt_msg_print, 2, (s32)"stg3_tou_469", 0,
    -2, 65546, 300, 131122, -30000000, 2, 65630, (s32)mario_party_zoom,
    131163, (s32)evt_msg_print_battle_party, (s32)"stg3_tou_470", 65546, 300, 196699, (s32)btlevtcmd_GetBodyId, -4,
    -30000000, 196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -4, -30000000, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 2, 1,
};

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL(btlevtcmd_GetUnitWork, -2, 2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SWITCH(LW(0))
            CASE_EQUAL(1)
            WAIT_MS(250)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
            WAIT_MS(300)
            CASE_EQUAL(2)
            WAIT_MS(250)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
            WAIT_MS(300)
            CASE_EQUAL(3)
            WAIT_MS(250)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
            WAIT_MS(300)
            CASE_EQUAL(4)
            WAIT_MS(250)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
            WAIT_MS(300)
            CASE_EQUAL(6)
            WAIT_MS(250)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
            WAIT_MS(300)
        END_SWITCH
        CALL(btlevtcmd_SetUnitWork, -2, 2, 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(base_size_change)
    CALL(btlevtcmd_GetUnitWorkFloat, -2, 3, LW(1))
    CALL(btlevtcmd_SetUnitWorkFloat, -2, 3, LW(0))
    DIVIDE_FLOAT(LW(0), LW(1))
    SET_FLOAT_VALUE(LW(5), LW(0))
    MULTIPLY_FLOAT(LW(5), FLOAT(26.0f))
    SUBTRACT_FLOAT(LW(5), FLOAT(26.0f))
    SET_FLOAT_VALUE(LW(6), LW(0))
    MULTIPLY_FLOAT(LW(6), FLOAT(77.0f))
    SUBTRACT_FLOAT(LW(6), FLOAT(77.0f))
    SET_FLOAT_VALUE(LW(7), LW(0))
    MULTIPLY_FLOAT(LW(7), FLOAT(0.0f))
    SUBTRACT_FLOAT(LW(7), FLOAT(0.0f))
    CALL(btlevtcmd_SetHitOffset, -2, 1, LW(5), LW(6), LW(7))
    SET_FLOAT_VALUE(LW(5), LW(0))
    MULTIPLY_FLOAT(LW(5), FLOAT(25.0f))
    SUBTRACT_FLOAT(LW(5), FLOAT(25.0f))
    SET_FLOAT_VALUE(LW(6), LW(0))
    MULTIPLY_FLOAT(LW(6), FLOAT(81.0f))
    SUBTRACT_FLOAT(LW(6), FLOAT(81.0f))
    SET_FLOAT_VALUE(LW(7), LW(0))
    MULTIPLY_FLOAT(LW(7), FLOAT(0.0f))
    SUBTRACT_FLOAT(LW(7), FLOAT(0.0f))
    CALL(btlevtcmd_SetHitCursorOffset, -2, 1, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_GetHpGaugeOffset, -2, LW(5), LW(6))
    MULTIPLY_FLOAT(LW(5), LW(0))
    MULTIPLY_FLOAT(LW(6), LW(0))
    CALL(btlevtcmd_SetHpGaugeOffset, -2, LW(5), LW(6))
    RETURN
EVT_END()

static s32 phase_event[] = {
    196699, (s32)btlevtcmd_CheckPhase, -30000000, 67108867, 131096, -30000000, 0, 65540,
    0, 33, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 0, 196699,
    (s32)btlevtcmd_CheckActStatus, -2, -30000000, 131096, -30000000, 0, 65540, 0,
    33, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -30000000, 65570, -30000000,
    65572, 0, 196699, (s32)btlevtcmd_GetMaxHp, -2, -30000000, 131127, -30000000,
    75, 131128, -30000000, 100, 196699, (s32)btlevtcmd_GetHp, -2, -29999999,
    131100, -29999999, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 1,
    131163, (s32)btlevtcmd_StopWaitEvent, -2, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 131122, -30000000,
    0, 65630, (s32)macho_gance_zoom, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING1", -250000000,
    0, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"E_1A", 65546,
    1500, 131163, (s32)evt_snd_sfxoff, -29999985, 131122, -30000000, -900, 131099,
    -30000000, 0, 65546, -30000000, 33, 327771, (s32)evt_msg_print, 2,
    (s32)"stg3_tou_471_17", 0, -2, 65546, 300, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546, 1000, 33, 65572,
    1, 196699, (s32)btlevtcmd_GetMaxHp, -2, -30000000, 131127, -30000000, 50,
    131128, -30000000, 100, 196699, (s32)btlevtcmd_GetHp, -2, -29999999, 131100,
    -29999999, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 2, 131163,
    (s32)btlevtcmd_StopWaitEvent, -2, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 131122, -30000000, 1,
    65630, (s32)macho_gance_zoom, 327771, (s32)evt_msg_print, 2, (s32)"stg3_tou_471_18", 0, -2,
    65546, 300, 131122, -30000000, 0, 65630, (s32)macho_gance_blur_zoom, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_BIG3", -250000000, 0, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_1", 65546, 800, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_GANSU_BIG1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetRotate, -2, -30000000,
    -29999999, -29999998, 131122, -29999995, 36, 65541, -29999995, 393307,
    (s32)wariai_enzan_1f, -29999995, 36, -230000000, -229815680, -29999994, 393307, (s32)wariai_enzan_1f,
    -29999995, 36, -229998976, -229998823, -29999993, 327771, (s32)btlevtcmd_SetBaseScale, -2,
    -29999993, -29999993, 1, 131125, -29999994, -29999999, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, -29999994, 0, 65545, 1, 6, 196699,
    (s32)btlevtcmd_ChangeFaceDirection, -2, 1, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 65546, 400, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_BIG2", -250000000,
    0, -250000000, 327771, (s32)btlevtcmd_GetRotate, -2, -30000000, -29999999, -29999998,
    131122, -29999995, 36, 65541, -29999995, 393307, (s32)wariai_enzan_1f, -29999995,
    36, -230000000, -230184320, -29999994, 393307, (s32)wariai_enzan_1f, -29999995, 36,
    -229998823, -229998669, -29999993, 327771, (s32)btlevtcmd_SetBaseScale, -2, -29999993, -29999993,
    1, 131125, -29999994, -29999999, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    -29999994, 0, 65545, 1, 6, 131163, (s32)btlevtcmd_ResetFaceDirection, -2,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 131124, -30000000,
    -229998669, 65630, (s32)base_size_change, 65546, 400, 131163, (s32)evt_snd_sfxoff, -29999985,
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999386, 131122, -29999992,
    2, 65541, -29999992, 110, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"J_1A", 327771, (s32)btlevtcmd_GetPosFloat, -2, -29999995, -29999994, -29999993, 65541,
    0, 327771, (s32)btlevtcmd_GetPosFloat, -2, -29999991, -29999990, -29999989, 131131,
    -29999994, -29999990, 131099, -29999994, -230000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"J_1B", 7, 33, 131124, -29999994, -29999990, 65545,
    1, 6, 112, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_JUMP1", -250000000, 0, -250000000,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 36, -1,
    110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_HIPDROP1", -250000000, 0, -250000000,
    327771, (s32)evt_cam_shake, 4, -230000000, -229999980, 800, 112, 65546,
    200, 6, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 69, 65546,
    400, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    65546, 1000, 33, 65572, 2, 196699, (s32)btlevtcmd_GetMaxHp, -2,
    -30000000, 131127, -30000000, 25, 131128, -30000000, 100, 196699,
    (s32)btlevtcmd_GetHp, -2, -29999999, 131100, -29999999, -30000000, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 1, 3, 131163, (s32)btlevtcmd_StopWaitEvent, -2, 262235, (s32)btlevtcmd_AnimeSetPoseTable,
    -2, 1, (s32)pose_table_furafura, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 131122, -30000000,
    1, 65630, (s32)macho_gance_zoom, 196699, (s32)btlevtcmd_SetTalkPoseType, -2, 65, 196699,
    (s32)btlevtcmd_SetStayPoseType, -2, 43, 327771, (s32)evt_msg_print, 2, (s32)"stg3_tou_471_19", 0,
    -2, 65546, 300, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 65546, 1000, 33, 49, 65539, 0,
    2, 1,
};

static s32 dead_event[] = {
    65627, (s32)btlevtcmd_WaitAttackEnd, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 131122, -30000000, 1,
    65630, (s32)macho_gance_zoom, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"D_2", 65546,
    170, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_DOWN1", -250000000, 0, -250000000,
    327771, (s32)evt_cam_shake, 4, -229999980, -230000000, 500, 65546, 200,
    196699, (s32)btlevtcmd_SetTalkPose, -2, (s32)"T_2", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"S_2",
    327771, (s32)evt_msg_print, 2, (s32)"stg3_tou_471_20", 0, -2, 65546, 300,
    131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546,
    500, 131122, -29999990, -2, 65630, (s32)subsetevt_dead_core_nospin_norotate, 2, 1,
};

s32 macho_gance_damage_event[] = {
    131163, (s32)btlevtcmd_ResetFaceDirection, -29999990, 196699, (s32)btlevtcmd_OnUnitFlag, -29999990, 1, 110,
    65570, -30000000, 65579, 43, 65579, 44, 65579, 45,
    196699, (s32)btlevtcmd_GetUnitKind, -29999990, -29999998, 131096, -29999998, 222, 327771,
    (s32)btlevtcmd_GetPos, -29999990, -29999998, -29999997, -29999996, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_VOICE_MARIO_DAMAGED1",
    -29999998, -29999997, -29999996, 0, 33, 46, 49, 112,
    65570, -30000000, 65572, 43, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_ATTACK_MISS3", 0,
    131122, -29999986, 36, 65572, 46, 196699, (s32)btlevtcmd_GetUnitKind, -29999990,
    -29999998, 131096, -29999998, 222, 393307, (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_VOICE_MARIO_DAMAGED1",
    -250000000, 0, -250000000, 33, 131122, -29999986, 29, 65579,
    49, 65579, 50, 65579, 54, 131122, -29999986, 29,
    46, 42, 131122, -29999986, 39, 49, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -29999990, -29999989, -29999986, 110, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 10,
    112, 196699, (s32)btlevtcmd_SetFallAccel, -29999990, -229998976, 327771, (s32)btlevtcmd_GetPos, -29999990,
    -29999998, -29999997, -29999996, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999990, -29999998, 25,
    131125, -29999997, 25, 655451, (s32)btlevtcmd_DivePosition, -29999990, -29999998, -29999997,
    -29999996, 10, 0, 0, 0, -1, 65546, 500,
    196699, (s32)btlevtcmd_SetFallAccel, -29999990, -229998976, 327771, (s32)btlevtcmd_GetPos, -29999990, -29999998,
    -29999997, -29999996, 327771, (s32)btlevtcmd_GetHomePos, -29999990, -29999995, -29999994, -29999993,
    131127, -29999998, 3, 131127, -29999995, 4, 131125, -29999998,
    -29999995, 131128, -29999998, 7, 262235, (s32)btlevtcmd_TransStageFloorPosition, -29999998, -29999997,
    -29999996, 458843, (s32)btlevtcmd_JumpPosition, -29999990, -29999998, -29999997, -29999996, 40,
    -1, 110, 327771, (s32)evt_cam_shake, 4, -230000000, -229999980, 250,
    112, 327771, (s32)btlevtcmd_GetHomePos, -29999990, -29999995, -29999994, -29999993, 131127,
    -29999995, 2, 131125, -29999998, -29999995, 131128, -29999998, 3,
    458843, (s32)btlevtcmd_JumpPosition, -29999990, -29999998, -29999997, -29999996, 20, -1,
    110, 327771, (s32)evt_cam_shake, 4, -230000000, -229999980, 166, 112,
    327771, (s32)btlevtcmd_GetHomePos, -29999990, -29999998, -29999997, -29999996, 458843, (s32)btlevtcmd_JumpPosition,
    -29999990, -29999998, -29999997, -29999996, 10, -1, 110, 327771,
    (s32)evt_cam_shake, 4, -230000000, -229999980, 116, 112, 65545, 30,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 2, 1,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(1))
    ADD(LW(1), 1)
    CALL(btlevtcmd_SetUnitWork, -2, 0, LW(1))
    CALL(btlevtcmd_CheckStatus, -2, 19, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        SET_VALUE(LW(9), PTR(weapon_gance_macho_speed))
        CALL_CHILD(PTR(gance_macho_speed_attack_event))
        ELSE
        CALL(btlevtcmd_GetUnitWork, -2, 1, LW(2))
        IF_INT_LESS(LW(2), 2)
            IF_INT_LESS_OR_EQUAL(LW(1), 1)
                CALL(btlevtcmd_DrawLots, LW(0), 3, 30, 20, 10)
                SWITCH(LW(0))
                    CASE_EQUAL(0)
                    SET_VALUE(LW(9), PTR(weapon_gance_build_up))
                    CALL_CHILD(PTR(gance_build_up_attack_event))
                    CASE_EQUAL(1)
                    SET_VALUE(LW(9), PTR(weapon_gance_body))
                    CALL_CHILD(PTR(gance_body_attack_event))
                    CASE_EQUAL(2)
                    SET_VALUE(LW(9), PTR(weapon_gance_footwork))
                    CALL_CHILD(PTR(gance_footwork_attack_event))
                END_SWITCH
                ELSE
                SET_VALUE(LW(9), PTR(weapon_gance_attack))
                CALL_CHILD(PTR(gance_attack_attack_event))
            END_IF
            ELSE
            IF_INT_LESS_OR_EQUAL(LW(1), 1)
                CALL(btlevtcmd_DrawLots, LW(0), 4, 25, 20, 10, 10)
                SWITCH(LW(0))
                    CASE_EQUAL(0)
                    SET_VALUE(LW(9), PTR(weapon_gance_build_up))
                    CALL_CHILD(PTR(gance_build_up_attack_event))
                    CASE_EQUAL(1)
                    SET_VALUE(LW(9), PTR(weapon_gance_body))
                    CALL_CHILD(PTR(gance_body_attack_event))
                    CASE_EQUAL(2)
                    SET_VALUE(LW(9), PTR(weapon_gance_footwork))
                    CALL_CHILD(PTR(gance_footwork_attack_event))
                    CASE_EQUAL(3)
                    SET_VALUE(LW(9), PTR(weapon_gance_posing))
                    CALL_CHILD(PTR(gance_posing_attack_event))
                END_SWITCH
                ELSE
                CALL(btlevtcmd_DrawLots, LW(0), 2, 10, 10)
                SWITCH(LW(0))
                    CASE_EQUAL(0)
                    SET_VALUE(LW(9), PTR(weapon_gance_rariat_attack))
                    CALL_CHILD(PTR(gance_rariat_attack_attack_event))
                    CASE_EQUAL(1)
                    SET_VALUE(LW(9), PTR(weapon_gance_body_attack))
                    CALL_CHILD(PTR(gance_body_attack_attack_event))
                END_SWITCH
            END_IF
        END_IF
    END_IF
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 gance_macho_speed_attack_event[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    300, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING1", -250000000, 0, -29999985,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"E_1A", 65546, 1500, 131163,
    (s32)evt_snd_sfxoff, -29999985, 327771, (s32)btlevtcmd_GetPosFloat, -2, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_GetStatusMg, -2, -29999995, 262235, (s32)btlevtcmd_GetUnitWorkFloat, -2, 3,
    -29999994, 131132, -29999995, -29999994, 131124, -29999994, -229938560, 131132,
    -29999994, -29999995, 131130, -29999999, -29999994, 131131, -29999998, -229959040,
    983131, (s32)evt_eff64, (s32)"hikari", (s32)"radiation_n64", 2, -30000000, -29999999, -29999998,
    -229998976, 0, 0, 0, 0, 0, 0, 0,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING2", -250000000, 0, -29999985, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_3", 65546, 1000, 131163, (s32)evt_snd_sfxoff,
    -29999985, 131163, (s32)evt_eff_delete, (s32)"hikari", 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 1, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -2, 1, -29999991, 256, -29999995, 2, 1,
};

s32 gance_build_up_attack_event[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    300, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING1", -250000000, 0, -29999985,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"E_1A", 65546, 1500, 131163,
    (s32)evt_snd_sfxoff, -29999985, 327771, (s32)btlevtcmd_GetPosFloat, -2, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_GetStatusMg, -2, -29999995, 262235, (s32)btlevtcmd_GetUnitWorkFloat, -2, 3,
    -29999994, 131132, -29999995, -29999994, 131124, -29999994, -229948800, 131132,
    -29999994, -29999995, 131130, -29999999, -29999994, 131131, -29999998, -229959040,
    983131, (s32)evt_eff64, (s32)"hikari", (s32)"radiation_n64", 2, -30000000, -29999999, -29999998,
    -229998976, 0, 0, 0, 0, 0, 0, 0,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING3", -250000000, 0, -29999985, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_5", 65546, 1000, 131163, (s32)evt_snd_sfxoff,
    -29999985, 131163, (s32)evt_eff_delete, (s32)"hikari", 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 2, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -2, 1, -29999991, 256, -29999995, 2, 1,
};

s32 gance_body_attack_event[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    300, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING1", -250000000, 0, -29999985,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"E_1A", 65546, 1500, 131163,
    (s32)evt_snd_sfxoff, -29999985, 327771, (s32)btlevtcmd_GetPosFloat, -2, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_GetStatusMg, -2, -29999995, 262235, (s32)btlevtcmd_GetUnitWorkFloat, -2, 3,
    -29999994, 131132, -29999995, -29999994, 131124, -29999994, -229948800, 131132,
    -29999994, -29999995, 131130, -29999999, -29999994, 131131, -29999998, -229959040,
    983131, (s32)evt_eff64, (s32)"hikari", (s32)"radiation_n64", 2, -30000000, -29999999, -29999998,
    -229998976, 0, 0, 0, 0, 0, 0, 0,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING4", -250000000, 0, -29999985, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_4", 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_7", 65546, 500, 131163, (s32)evt_snd_sfxoff, -29999985,
    131163, (s32)evt_eff_delete, (s32)"hikari", 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 2, 3, 458843, (s32)btlevtcmd_CheckDamage, -2, -2,
    1, -29999991, 256, -29999995, 2, 1,
};

s32 gance_footwork_attack_event[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    300, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING1", -250000000, 0, -29999985,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"E_1A", 65546, 1500, 131163,
    (s32)evt_snd_sfxoff, -29999985, 327771, (s32)btlevtcmd_GetPosFloat, -2, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_GetStatusMg, -2, -29999995, 262235, (s32)btlevtcmd_GetUnitWorkFloat, -2, 3,
    -29999994, 131132, -29999995, -29999994, 131124, -29999994, -229948800, 131132,
    -29999994, -29999995, 131130, -29999999, -29999994, 131131, -29999998, -229959040,
    983131, (s32)evt_eff64, (s32)"hikari", (s32)"radiation_n64", 2, -30000000, -29999999, -29999998,
    -229998976, 0, 0, 0, 0, 0, 0, 0,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING5", -250000000, 0, -29999985, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_6", 65546, 1000, 131163, (s32)evt_snd_sfxoff,
    -29999985, 131163, (s32)evt_eff_delete, (s32)"hikari", 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 4, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -2, 1, -29999991, 256, -29999995, 2, 1,
};

s32 gance_attack_attack_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING1", -250000000, 0, -29999985, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"E_1A", 65546, 1500, 131163, (s32)evt_snd_sfxoff,
    -29999985, 327771, (s32)btlevtcmd_GetPosFloat, -2, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_GetStatusMg, -2, -29999995, 262235, (s32)btlevtcmd_GetUnitWorkFloat, -2, 3, -29999994,
    131132, -29999995, -29999994, 131124, -29999994, -229948800, 131132, -29999994,
    -29999995, 131130, -29999999, -29999994, 131131, -29999998, -229959040, 983131,
    (s32)evt_eff64, (s32)"hikari", (s32)"radiation_n64", 2, -30000000, -29999999, -29999998, -229998976,
    0, 0, 0, 0, 0, 0, 0, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING7", -250000000, 0, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"E_1B", 65546, 1000, 131163, (s32)evt_snd_sfxoff, -29999985,
    131163, (s32)evt_eff_delete, (s32)"hikari", 327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000,
    -229999386, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2,
    -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096,
    -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097,
    -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_PartsFaceDirectionSub, -2, 1, -30000000,
    250, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 196699, (s32)x_flag_set,
    0, 1, 110, 327771, (s32)evt_cam_shake, 4, -229999996, -230000000,
    1166, 196699, (s32)x_flag_set, 0, 0, 112, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, 70, -1, 1, 196699,
    (s32)x_flag_wait, 0, 0, 65546, 500, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42,
    110, 327771, (s32)evt_cam_shake, 4, -229999996, -230000000, 500, 112,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 30, -1,
    0, 110, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1A", 327771,
    (s32)btlevtcmd_GetPosFloat, -2, -29999995, -29999994, -29999993, 65541, 0, 327771,
    (s32)btlevtcmd_GetPosFloat, -2, -29999991, -29999990, -29999989, 131131, -29999994, -29999990,
    131099, -29999994, -230000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1B",
    7, 33, 131124, -29999994, -29999990, 65545, 1, 6,
    112, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_JUMP1", -250000000, 0, -250000000, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 36, -1, 196699,
    (s32)x_flag_set, 0, 0, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    -29999991, 256, -29999995, 65570, -29999995, 65579, 4, 65540,
    90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 65540, 90, 65572, 1, 65540, 91, 46,
    42, 65540, 98, 46, 49, 65539, 90, 131163,
    (s32)btlevtcmd_JumpContinue, -2, 196699, (s32)x_flag_set, 0, 1, 110, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_HIPDROP1", -250000000, 0, -250000000, 327771, (s32)evt_cam_shake,
    4, -230000000, -229999980, 800, 196699, (s32)x_flag_set, 0, 0,
    112, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_MoveDirectionAdd, -2, -30000000, 30, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 18, -1, 262235, (s32)btlevtcmd_MoveDirectionAdd, -2, -30000000,
    18, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 9,
    -1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 69, 65546, 300,
    65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991,
    196699, (s32)x_flag_set, 0, 1, 110, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_GANSU_HIPDROP1", -250000000, 0, -250000000, 327771, (s32)evt_cam_shake, 4, -230000000,
    -229999980, 800, 196699, (s32)x_flag_set, 0, 0, 112, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131122, -29999999, 0,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 48, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 30, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 24, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 12, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 6, -1, 65539,
    98, 196699, (s32)x_flag_wait, 0, 0, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229995904, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 69, 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 42, 196699, (s32)x_flag_set, 0, 1, 110,
    327771, (s32)evt_cam_shake, 4, -229999996, -230000000, 666, 196699, (s32)x_flag_set,
    0, 0, 112, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, 40, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 196699,
    (s32)x_flag_wait, 0, 0, 2, 1,
};

s32 gance_posing_attack_event[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    300, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING1", -250000000, 0, -29999985,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"E_1A", 65546, 1500, 131163,
    (s32)evt_snd_sfxoff, -29999985, 327771, (s32)btlevtcmd_GetPosFloat, -2, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_GetStatusMg, -2, -29999995, 262235, (s32)btlevtcmd_GetUnitWorkFloat, -2, 3,
    -29999994, 131132, -29999995, -29999994, 131124, -29999994, -229948800, 131132,
    -29999994, -29999995, 131130, -29999999, -29999994, 131131, -29999998, -229959040,
    983131, (s32)evt_eff64, (s32)"hikari", (s32)"radiation_n64", 2, -30000000, -29999999, -29999998,
    -229998976, 0, 0, 0, 0, 0, 0, 0,
    110, 65546, 50, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_FIST1", -250000000,
    0, -250000000, 65546, 180, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_FIST1",
    -250000000, 0, -250000000, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"M_8", 65546, 1000, 131163, (s32)evt_eff_delete, (s32)"hikari", 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999991, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 6, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -2, 1, -29999991, 256, -29999995, 2,
    1,
};

s32 gance_rariat_attack_attack_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING1", -250000000, 0, -29999985, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"E_1A", 65546, 1500, 131163, (s32)evt_snd_sfxoff,
    -29999985, 327771, (s32)btlevtcmd_GetPosFloat, -2, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_GetStatusMg, -2, -29999995, 262235, (s32)btlevtcmd_GetUnitWorkFloat, -2, 3, -29999994,
    131132, -29999995, -29999994, 131124, -29999994, -229907840, 131132, -29999994,
    -29999995, 131130, -29999999, -29999994, 131124, -29999994, -229979520, 131132,
    -29999994, -29999995, 131130, -30000000, -29999994, 131131, -29999998, -229959040,
    983131, (s32)evt_eff64, (s32)"hikari", (s32)"radiation_n64", 2, -30000000, -29999999, -29999998,
    -229998976, 0, 0, 0, 0, 0, 0, 0,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING8", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_2", 65546, 1000, 131163, (s32)evt_eff_delete,
    (s32)"hikari", 327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999386, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991,
    131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000,
    131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33,
    131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_2A", 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229991808, 110, 327771, (s32)evt_cam_shake,
    4, -229999996, -230000000, 200, 112, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997,
    -29999996, 131122, -29999990, 0, 131122, -29999989, 0, 196699,
    (s32)x_flag_set, 0, 0, 196699, (s32)x_flag_set, 1, 0, 65541,
    0, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_GetStatusMg, -2, -29999993, 131132, -29999993, 35, 262235, (s32)btlevtcmd_GetUnitWorkFloat,
    -2, 3, -29999994, 131132, -29999993, -29999994, 131130, -29999993,
    15, 131125, -30000000, -29999993, 131125, -29999998, 6, 131096,
    -29999989, 0, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2B",
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 32, 196699, (s32)x_flag_set, 1,
    1, 110, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 196699, (s32)x_flag_set, 1, 0, 112,
    33, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256,
    -29999995, 65570, -29999995, 65579, 4, 131122, -29999994, 90,
    46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 131122,
    -29999994, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 131122, -29999994, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 131122, -29999994, 90, 65572, 1, 131122,
    -29999994, 91, 46, 42, 131122, -29999994, 97, 46,
    49, 65540, -29999994, 65539, 90, 65540, 97, 65539,
    91, 131096, -29999989, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991,
    33, 131096, -29999990, 0, 131122, -29999990, 1, 196699,
    (s32)x_flag_set, 0, 1, 110, 327771, (s32)evt_cam_shake, 4, -229999980,
    -230000000, 800, 196699, (s32)x_flag_set, 0, 0, 112, 33,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65539, 97, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998,
    131125, -29999989, 1, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131096,
    -29999997, -1, 7, 33, 6, 196699, (s32)x_flag_wait, 1,
    0, 131126, -30000000, -29999993, 131125, -29999998, 6, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    65546, 500, 196699, (s32)x_flag_wait, 0, 0, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229995904, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 69, 65546, 500, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)x_flag_set, 0, 1,
    110, 327771, (s32)evt_cam_shake, 4, -229999996, -230000000, 666, 196699,
    (s32)x_flag_set, 0, 0, 112, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 40, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2,
    196699, (s32)x_flag_wait, 0, 0, 2, 1,
};

s32 gance_body_attack_attack_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING1", -250000000, 0, -29999985, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"E_1A", 65546, 1500, 131163, (s32)evt_snd_sfxoff,
    -29999985, 327771, (s32)btlevtcmd_GetPosFloat, -2, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_GetStatusMg, -2, -29999995, 262235, (s32)btlevtcmd_GetUnitWorkFloat, -2, 3, -29999994,
    131132, -29999995, -29999994, 131124, -29999994, -229948800, 131132, -29999994,
    -29999995, 131130, -29999999, -29999994, 131131, -29999998, -229959040, 983131,
    (s32)evt_eff64, (s32)"hikari", (s32)"radiation_n64", 2, -30000000, -29999999, -29999998, -229998976,
    0, 0, 0, 0, 0, 0, 0, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_PAUSING9", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_1", 65546, 1000, 131163, (s32)evt_eff_delete, (s32)"hikari",
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 69, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_GANSU_ATTACK1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetRotate, -2, -30000000,
    -29999999, -29999998, 131122, -29999995, 12, 65541, -29999995, 393307,
    (s32)wariai_enzan_1f, -29999995, 12, -230000000, -229815680, -29999994, 131125, -29999994,
    -29999999, 327771, (s32)btlevtcmd_SetRotate, -2, 0, -29999994, 0, 65545,
    1, 6, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, 1, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 0, 0, 65546, 500, 327771, (s32)btlevtcmd_JumpSetting,
    -2, 20, -230000000, -229999386, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991,
    -29999997, -29999996, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2,
    16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 33,
    2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2,
    -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A", 65546, 300, 110,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B", 196699, (s32)btlevtcmd_GetStatusMg, -2,
    -30000000, 131132, -30000000, -229928320, 262235, (s32)btlevtcmd_GetUnitWorkFloat, -2, 3,
    -29999999, 131132, -30000000, -29999999, 327771, (s32)btlevtcmd_SetRotateOffset, -2, -230000000,
    -30000000, -230000000, 131122, -29999995, -229970509, 65541, -29999995, 458843,
    (s32)wariai_enzan_1f_intpl, -29999995, -229970509, -230000000, -229672320, -29999994, 5, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, -29999994, 65545, 1, 6,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1C", 65545, 1, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2,
    -230000000, -230000000, -230000000, 112, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_JUMP1", -250000000,
    0, -250000000, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    36, -1, 196699, (s32)x_flag_set, 0, 0, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 49,
    65539, 90, 131163, (s32)btlevtcmd_JumpContinue, -2, 196699, (s32)x_flag_set, 0,
    1, 110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_HIPDROP1", -250000000, 0,
    -250000000, 327771, (s32)evt_cam_shake, 4, -230000000, -229999980, 800, 196699,
    (s32)x_flag_set, 0, 0, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_1D", 65546, 300, 65540, 98, 65539, 91, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 196699, (s32)x_flag_set, 0, 1, 110,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GANSU_HIPDROP1", -250000000, 0, -250000000, 327771,
    (s32)evt_cam_shake, 4, -230000000, -229999980, 800, 196699, (s32)x_flag_set, 0,
    0, 112, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1D", 131163,
    (s32)btlevtcmd_JumpContinue, -2, 65539, 98, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_MoveDirectionAdd, -2, -30000000, 30, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 18, -1, 262235,
    (s32)btlevtcmd_MoveDirectionAdd, -2, -30000000, 18, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 9, -1, 196699, (s32)x_flag_wait, 0, 0,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 69, 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 196699, (s32)x_flag_set, 0, 1, 110, 327771, (s32)evt_cam_shake,
    4, -229999996, -230000000, 666, 196699, (s32)x_flag_set, 0, 0,
    112, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 40,
    -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 196699, (s32)x_flag_wait, 0,
    0, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static USER_FUNC(x_flag_wait) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    s32 value = evtGetValue(event, args[1]);

    if (value == x_flag_data[index]) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

static USER_FUNC(x_flag_get) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    evtSetValue(event, args[1], x_flag_data[index]);
    return EVT_RETURN_DONE;
}

static USER_FUNC(x_flag_add) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    x_flag_data[index] += evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}

static USER_FUNC(x_flag_set) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    x_flag_data[index] = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}

static USER_FUNC(wariai_enzan_0f) {
    s32* args = event->args;
    f32 a = evtGetFloat(event, args[0]) - 1.0f;
    f32 b = evtGetFloat(event, args[1]) - 1.0f;
    f32 c = evtGetFloat(event, args[2]);
    f32 d = evtGetFloat(event, args[3]);

    evtSetFloat(event, args[4], (a * c + d * (b - a)) / b);
    return EVT_RETURN_DONE;
}

static USER_FUNC(wariai_enzan_0) {
    s32* args = event->args;
    f32 a = evtGetFloat(event, args[0]) - 1.0f;
    f32 b = evtGetFloat(event, args[1]) - 1.0f;
    f32 c = evtGetFloat(event, args[2]);
    f32 d = evtGetFloat(event, args[3]);

    evtSetValue(event, args[4], (a * c + d * (b - a)) / b);
    return EVT_RETURN_DONE;
}

USER_FUNC(wariai_enzan_1f_intpl_w) {
    s32* args = event->args;
    f32 a = evtGetFloat(event, args[0]) - 1.0f;
    f32 b = evtGetFloat(event, args[1]);
    f32 c = evtGetFloat(event, args[2]);
    f32 d = evtGetFloat(event, args[3]);
    s32 out = args[4];
    f32 t1 = evtGetFloat(event, args[5]);
    f32 t2 = evtGetFloat(event, args[6]);
    f32 r1;
    f32 r2;
    f32 w;

    if (t1 >= 14.0f) {
        t1 -= 14.0f;
        if (t1 >= 14.0f) {
            evtSetFloat(event, out, c);
            return EVT_RETURN_DONE;
        }
        r1 = 1.0f - intplGetValue(t1, b - a, 1.0f, 0.0f, b);
    } else {
        r1 = intplGetValue(t1, b - a, 0.0f, 1.0f, b);
    }
    if (t2 >= 14.0f) {
        t2 = t1 - 14.0f;
        if (t2 >= 14.0f) {
            evtSetFloat(event, out, c);
            return EVT_RETURN_DONE;
        }
        r2 = 1.0f - intplGetValue(t2, b - a, 1.0f, 0.0f, b);
    } else {
        r2 = intplGetValue(t2, b - a, 0.0f, 1.0f, b);
    }
    w = r1 * r2;
    evtSetFloat(event, out, c * (1.0f - w) + d * w);
    return EVT_RETURN_DONE;
}

static USER_FUNC(wariai_enzan_1f_intpl) {
    s32* args = event->args;
    f32 a = evtGetFloat(event, args[0]) - 1.0f;
    f32 b = evtGetFloat(event, args[1]);
    f32 c = evtGetFloat(event, args[2]);
    f32 d = evtGetFloat(event, args[3]);
    s32 out = args[4];
    f32 t = evtGetFloat(event, args[5]);
    f32 r;

    if (t >= 14.0f) {
        t -= 14.0f;
        if (t >= 14.0f) {
            evtSetFloat(event, out, c);
            return EVT_RETURN_DONE;
        }
        r = 1.0f - intplGetValue(t, b - a, 1.0f, 0.0f, b);
    } else {
        r = intplGetValue(t, b - a, 0.0f, 1.0f, b);
    }
    evtSetFloat(event, out, (1.0f - r) * c + r * d);
    return EVT_RETURN_DONE;
}

static USER_FUNC(wariai_enzan_1f) {
    s32* args = event->args;
    f32 a = evtGetFloat(event, args[0]) - 1.0f;
    f32 b = evtGetFloat(event, args[1]);
    f32 c = evtGetFloat(event, args[2]);
    f32 d = evtGetFloat(event, args[3]);

    evtSetFloat(event, args[4], (a * c + d * (b - a)) / b);
    return EVT_RETURN_DONE;
}

static USER_FUNC(wariai_enzan_1) {
    s32* args = event->args;
    f32 a = evtGetFloat(event, args[0]) - 1.0f;
    f32 b = evtGetFloat(event, args[1]);
    f32 c = evtGetFloat(event, args[2]);
    f32 d = evtGetFloat(event, args[3]);

    evtSetValue(event, args[4], (a * c + d * (b - a)) / b);
    return EVT_RETURN_DONE;
}
