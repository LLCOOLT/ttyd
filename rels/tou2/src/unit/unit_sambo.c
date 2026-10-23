#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_CheckSpace);
USER_FUNC(btlevtcmd_ChoiceSamplingEnemy);
USER_FUNC(btlevtcmd_DivePartsPosition);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetDamage);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetHeight);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetStatusMg);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_JumpPartsPosition);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_OnPartsAttribute);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_SamplingEnemy);
USER_FUNC(btlevtcmd_SetCutBaseOffset);
USER_FUNC(btlevtcmd_SetCutHeight);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHeight);
USER_FUNC(btlevtcmd_SetKissHitOffset);
USER_FUNC(btlevtcmd_SetPartsFallAccel);
USER_FUNC(btlevtcmd_SetPartsPos);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRotateOffset);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetStatusIconOffset);
USER_FUNC(btlevtcmd_SetSwallowAttribute);
USER_FUNC(btlevtcmd_SetSwallowParam);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_TransStageFloorPosition);
USER_FUNC(evt_eff);
USER_FUNC(evt_sub_random);
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckDamagePattern[];
extern s32 btlevtcmd_CheckStatus[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_GetBodyId[];
extern s32 btlevtcmd_GetFaceDirection[];
extern s32 btlevtcmd_GetFriendBelong[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetPartsPos[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetStageSize[];
extern s32 btlevtcmd_GetUnitId[];
extern s32 btlevtcmd_JumpPartsSetting[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetHomePos[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetPartsMoveSpeed[];
extern s32 btlevtcmd_SetPartsScale[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SpawnUnit[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_add_zoom[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_snd_sfxoff[];
extern s32 evt_sub_intpl_get_value[];
extern s32 evt_sub_intpl_init[];
extern s32 marioWeapon_KaitenHammerInvolved[];
extern s32 marioWeapon_UltraHammerFinish[];
extern s32 marioWeapon_UltraHammerInvolved[];
extern s32 subsetevt_confuse_flustered[];
extern s32 subsetevt_nodamage_motion[];
extern s32 subsetevt_shot_damage[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_sambo_negone_one_374;
__declspec(section ".data") s32 fd_sambo_neg_one_382[1];
__declspec(section ".data") s32 fd_sambo___local_PI_383[1];
__declspec(section ".data") s32 fd_sambo___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_sambo_one_negone_373;
__declspec(section ".data") s32 fd_sambo___local_PIO2_384[1];
__declspec(section ".data") s32 fd_sambo_one_381[1];
__declspec(section ".data") u64 fd_sambo_negone_one_360;
__declspec(section ".data") s32 fd_sambo_neg_one_365[1];
__declspec(section ".data") s32 fd_sambo___local_PI_366[1];
__declspec(section ".data") s32 fd_sambo___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_sambo_one_negone_359;
__declspec(section ".data") s32 fd_sambo___local_PIO2_367[1];
__declspec(section ".data") s32 fd_sambo_one_364[1];
BattleUnitKind unit_sambo;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static s32 weapon_sambo_head_attack_4[48];
static s32 weapon_sambo_head_attack_3[48];
static s32 weapon_sambo_head_attack_2[48];
static s32 weapon_sambo_head_attack_1[48];
static s32 weapon_sambo_spike_attack_4[48];
static s32 weapon_sambo_spike_attack_3[48];
static s32 weapon_sambo_spike_attack_2[48];
static PoseTableEntry pose_table_body4[18];
static PoseTableEntry pose_table_body3[20];
static PoseTableEntry pose_table_body2[20];
static PoseTableEntry pose_table_body1[20];
static __declspec(section ".data") PoseTableEntry pose_table_parts[3];
static BattleDataEntry data_table[8];
static BattleUnitKindPart parts[5];
static s32 init_event[54];
static s32 dmg_avoid_counter_thorn_side_event[51];
static s32 damage_event[34];
static s32 damage_event_bodylost[273];
static s32 subset_dmg_sambo_fall[152];
static s32 damage_event_bodylost_blow[354];
static s32 damage_swallow_body[256];
static s32 attack_event[189];
static s32 attack_head_2_event[613];
static s32 attack_head_1_event[587];
static s32 attack_spike_event[824];
static s32 call_friend_event[304];
static __declspec(section ".data") s32 entry_sambo[12];
static s32 wait_event[36];
static s32 sambo_rabbit_move[74];
static s32 _body_param_set[49];

__declspec(section ".data") u64 fd_sambo_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_sambo_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_sambo___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_sambo___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_sambo_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_sambo___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_sambo_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_sambo_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_sambo_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_sambo___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_sambo___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_sambo_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_sambo___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_sambo_one_364[] = {
    1065353216,
};

BattleUnitKind unit_sambo = {
    39,
    "btl_un_sambo",
    4,
    0,
    1,
    1,
    11,
    0,
    1,
    70,
    1,
    50,
    9999,
    26,
    80,
    14,
    80,
    0.0f,
    40.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
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
    10.0f,
    52.0f,
    0.0f,
    0.0f,
    40.0f,
    0.0f,
    26.0f,
    80.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_SAMBO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    5,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {95, 80, 80, 100, 90, 100, 100, 60, 100, 90, 100, 90, 100, 95, 90, 100, 90, 100, 90, 100, 100, 100};

static s32 weapon_sambo_head_attack_4[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553648132, 770, 0, 135, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_sambo_head_attack_3[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553648132, 770, 0, 135, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_sambo_head_attack_2[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553664516, 770, 0, 135, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_sambo_head_attack_1[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553664516, 770, 0, 4231, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_sambo_spike_attack_4[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_sambo_spike_attack_3[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_sambo_spike_attack_2[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static PoseTableEntry pose_table_body4[] = {
    {1, "SNB_N_1"},
    {2, "SNB_Y_1"},
    {9, "SNB_Y_1"},
    {5, "SNB_K_1"},
    {4, "SNB_X_1"},
    {3, "SNB_X_1"},
    {28, "SNB_S_1"},
    {29, "SNB_Q_1"},
    {30, "SNB_Q_1"},
    {31, "SNB_S_1"},
    {39, "SNB_D_1"},
    {47, "SNB_W_1"},
    {42, "SNB_W_1"},
    {40, "SNB_W_1"},
    {56, "SNB_X_1"},
    {57, "SNB_X_1"},
    {65, "SNB_T_1"},
    {69, "SNB_S_1"},
};

static PoseTableEntry pose_table_body3[] = {
    {1, "SNB_N_2"},
    {2, "SNB_Y_2"},
    {9, "SNB_Y_2"},
    {5, "SNB_K_2"},
    {4, "SNB_X_2"},
    {3, "SNB_X_2"},
    {28, "SNB_S_2"},
    {29, "SNB_Q_2"},
    {30, "SNB_Q_2"},
    {31, "SNB_S_2"},
    {39, "SNB_D_2"},
    {47, "SNB_W_2"},
    {50, "SNB_A_1A"},
    {51, "SNB_A_1B"},
    {42, "SNB_W_2"},
    {40, "SNB_W_2"},
    {56, "SNB_X_2"},
    {57, "SNB_X_2"},
    {65, "SNB_T_2"},
    {69, "SNB_S_2"},
};

static PoseTableEntry pose_table_body2[] = {
    {1, "SNB_N_3"},
    {2, "SNB_Y_3"},
    {9, "SNB_Y_3"},
    {5, "SNB_K_3"},
    {4, "SNB_X_3"},
    {3, "SNB_X_3"},
    {28, "SNB_S_3"},
    {29, "SNB_Q_3"},
    {30, "SNB_Q_3"},
    {31, "SNB_S_3"},
    {39, "SNB_D_3"},
    {47, "SNB_W_3"},
    {50, "SNB_A_2A"},
    {51, "SNB_A_2B"},
    {42, "SNB_W_3"},
    {40, "SNB_W_3"},
    {56, "SNB_X_3"},
    {57, "SNB_X_3"},
    {65, "SNB_T_3"},
    {69, "SNB_S_3"},
};

static PoseTableEntry pose_table_body1[] = {
    {1, "SNB_N_4"},
    {2, "SNB_Y_4"},
    {9, "SNB_Y_4"},
    {5, "SNB_K_4"},
    {4, "SNB_X_4"},
    {3, "SNB_X_4"},
    {28, "SNB_S_4"},
    {29, "SNB_Q_4"},
    {30, "SNB_Q_4"},
    {31, "SNB_S_4"},
    {39, "SNB_D_4"},
    {47, "SNB_W_4"},
    {50, "SNB_A_3A"},
    {51, "SNB_A_3B"},
    {42, "SNB_W_4"},
    {40, "SNB_W_4"},
    {56, "SNB_X_4"},
    {57, "SNB_X_4"},
    {65, "SNB_T_4"},
    {69, "SNB_S_4"},
};

static __declspec(section ".data") PoseTableEntry pose_table_parts[] = {
    {28, "SNB_B_1"},
    {39, "SNB_B_1"},
    {69, "SNB_B_1"},
};

static BattleDataEntry data_table[] = {
    {37, dmg_avoid_counter_thorn_side_event},
    {39, dmg_avoid_counter_thorn_side_event},
    {19, damage_event_bodylost},
    {18, damage_event_bodylost_blow},
    {16, damage_event_bodylost},
    {48, btldefaultevt_Dummy},
    {54, damage_swallow_body},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_sambo", "c_sanbo", 0.0f, 0.0f, 0.0f, 0.0f, 84.0f, 0.0f, 0.0f, 90.0f, 0.0f, 20, 90, 255, &defence, &defence_attr, 0x9, 0x5, pose_table_body4},
    {2, "btl_un_sambo", "c_sanbo", 0.0f, 0.0f, 0.0f, 0.0f, 64.0f, 0.0f, 0.0f, 70.0f, 0.0f, 20, 70, 255, &defence, &defence_attr, 0x3010000, 0x5, pose_table_body3},
    {3, "btl_un_sambo", "c_sanbo", 0.0f, 0.0f, 0.0f, 0.0f, 44.0f, 0.0f, 0.0f, 50.0f, 0.0f, 20, 50, 255, &defence, &defence_attr, 0x3010000, 0x5, pose_table_body2},
    {4, "btl_un_sambo", "c_sanbo", 0.0f, 0.0f, 0.0f, 0.0f, 24.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x3010000, 0x5, pose_table_body1},
    {5, "btl_un_sambo", "c_sanbo", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table_parts},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 4)
    CALL_CHILD(PTR(_body_param_set))
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 5, 69)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_ENM_SAMBO_MOVE1"), STRING("SFX_ENM_SAMBO_MOVE1"), 0, 6, 6)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_ENM_SAMBO_MOVE1"), STRING("SFX_ENM_SAMBO_MOVE1"), 0, 6, 6)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(dmg_avoid_counter_thorn_side_event)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 47)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, LW(10), LW(3))
    CALL(btlevtcmd_GetStatusMg, LW(10), LW(4))
    MULTIPLY_FLOAT(LW(3), LW(4))
    ADD(LW(1), LW(3))
    ADD(LW(1), 5)
    ADD(LW(2), 10)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        SET_VALUE(LW(11), 4)
        CASE_EQUAL(2)
        SET_VALUE(LW(11), 3)
        CASE_EQUAL(3)
        SET_VALUE(LW(11), 2)
        CASE_DEFAULT
        SET_VALUE(LW(11), 1)
    END_SWITCH
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(damage_event_bodylost)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_GetDamage, LW(10), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
            WAIT_FRAMES(30)
            IF_INT_NOT_EQUAL(LW(15), -1)
                CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(15))
                WAIT_FRAMES(30)
            END_IF
            ELSE
            CALL_CHILD(PTR(subsetevt_nodamage_motion))
        END_IF
        ELSE
        SET_VALUE(LW(12), LW(11))
        CALL(btlevtcmd_GetUnitWork, LW(10), 0, LW(0))
        SUBTRACT(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, LW(10), 0, LW(0))
        CALL_CHILD(PTR(_body_param_set))
        SWITCH(LW(0))
            CASE_EQUAL(1)
            SET_VALUE(LW(11), 4)
            CALL(btlevtcmd_SetSwallowParam, -2, 50)
            CALL(btlevtcmd_SetSwallowAttribute, -2, 2)
            CALL(btlevtcmd_SetStatusIconOffset, -2, 14, 20)
            CALL(btlevtcmd_SetCutBaseOffset, -2, 0, 10, 0)
            CALL(btlevtcmd_SetKissHitOffset, -2, 10, 16, 0)
            CASE_EQUAL(2)
            SET_VALUE(LW(11), 3)
            CALL(btlevtcmd_SetStatusIconOffset, -2, 14, 40)
            CALL(btlevtcmd_SetCutBaseOffset, -2, 0, 20, 0)
            CALL(btlevtcmd_SetKissHitOffset, -2, 10, 26, 0)
            CASE_EQUAL(3)
            SET_VALUE(LW(11), 2)
            CALL(btlevtcmd_SetStatusIconOffset, -2, 14, 60)
            CALL(btlevtcmd_SetCutBaseOffset, -2, 0, 30, 0)
            CALL(btlevtcmd_SetKissHitOffset, -2, 10, 36, 0)
            CASE_DEFAULT
            SET_VALUE(LW(11), 1)
            CALL(btlevtcmd_SetStatusIconOffset, -2, 14, 80)
            CALL(btlevtcmd_SetCutBaseOffset, -2, 0, 40, 0)
            CALL(btlevtcmd_SetKissHitOffset, -2, 10, 52, 0)
        END_SWITCH
        CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(12), 9)
        CALL(btlevtcmd_OnPartsAttribute, LW(10), LW(12), 50397184)
        CALL(btlevtcmd_OnPartsAttribute, LW(10), LW(11), 9)
        CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(11), 16842752)
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        BEGIN_SIBLING_EVENT
            WAIT_FRAMES(4)
            CALL_CHILD(PTR(subset_dmg_sambo_fall))
        END_SIBLING_EVENT
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPartsPos, LW(10), 5, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_OffPartsAttribute, LW(10), 5, 16777216)
        CALL(btlevtcmd_SetPartsFallAccel, LW(10), 5, FLOAT(0.39941406f))
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), 25)
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpPartsPosition, LW(10), 5, LW(0), LW(1), LW(2), 16, -1)
        CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), 16)
        CALL(btlevtcmd_JumpPartsPosition, LW(10), 5, LW(0), LW(1), LW(2), 12, -1)
        LOOP(40)
            CALL(btlevtcmd_OnPartsAttribute, LW(10), 5, 16777216)
            WAIT_FRAMES(1)
            CALL(btlevtcmd_OffPartsAttribute, LW(10), 5, 16777216)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_OnPartsAttribute, LW(10), 5, 16777216)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(subset_dmg_sambo_fall)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    ADD(LW(1), 18)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    SET_VALUE(LW(3), LW(1))
    WAIT_FRAMES(2)
    SUBTRACT(LW(3), 1)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(3)
    SUBTRACT(LW(3), 2)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(2)
    SUBTRACT(LW(3), 3)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    SUBTRACT(LW(3), 5)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    SUBTRACT(LW(3), 7)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    ADD(LW(3), 2)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    ADD(LW(3), 3)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    ADD(LW(3), 3)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    SUBTRACT(LW(3), 3)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    SUBTRACT(LW(3), 3)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    WAIT_FRAMES(1)
    SUBTRACT(LW(3), 2)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(3), LW(2))
    RETURN
EVT_END()

static s32 damage_event_bodylost_blow[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096, -30000000, 1,
    196699, (s32)btlevtcmd_GetDamage, -29999990, -30000000, 131101, -30000000, 1, 65630,
    (s32)subsetevt_shot_damage, 32, 65630, (s32)subsetevt_nodamage_motion, 33, 32, 131122, -29999988,
    -29999989, 262235, (s32)btlevtcmd_GetUnitWork, -29999990, 0, -30000000, 131126, -30000000,
    1, 262235, (s32)btlevtcmd_SetUnitWork, -29999990, 0, -30000000, 65630, (s32)_body_param_set,
    65570, -30000000, 65572, 1, 131122, -29999989, 4, 196699,
    (s32)btlevtcmd_SetSwallowParam, -2, 50, 196699, (s32)btlevtcmd_SetSwallowAttribute, -2, 2, 262235,
    (s32)btlevtcmd_SetStatusIconOffset, -2, 14, 20, 327771, (s32)btlevtcmd_SetCutBaseOffset, -2, 0,
    10, 0, 327771, (s32)btlevtcmd_SetKissHitOffset, -2, 10, 16, 0,
    65572, 2, 131122, -29999989, 3, 262235, (s32)btlevtcmd_SetStatusIconOffset, -2,
    14, 40, 327771, (s32)btlevtcmd_SetCutBaseOffset, -2, 0, 20, 0,
    327771, (s32)btlevtcmd_SetKissHitOffset, -2, 10, 26, 0, 65572, 3,
    131122, -29999989, 2, 262235, (s32)btlevtcmd_SetStatusIconOffset, -2, 14, 60,
    327771, (s32)btlevtcmd_SetCutBaseOffset, -2, 0, 30, 0, 327771, (s32)btlevtcmd_SetKissHitOffset,
    -2, 10, 36, 0, 42, 131122, -29999989, 1,
    262235, (s32)btlevtcmd_SetStatusIconOffset, -2, 14, 80, 327771, (s32)btlevtcmd_SetCutBaseOffset, -2,
    0, 40, 0, 327771, (s32)btlevtcmd_SetKissHitOffset, -2, 10, 52,
    0, 49, 262235, (s32)btlevtcmd_OffPartsAttribute, -29999990, -29999988, 9, 262235,
    (s32)btlevtcmd_OnPartsAttribute, -29999990, -29999988, 50397184, 262235, (s32)btlevtcmd_OnPartsAttribute, -29999990, -29999989,
    9, 262235, (s32)btlevtcmd_OffPartsAttribute, -29999990, -29999989, 16842752, 327771, (s32)btlevtcmd_GetPos,
    -29999990, -30000000, -29999999, -29999998, 110, 65545, 4, 65630,
    (s32)subset_dmg_sambo_fall, 112, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999, -29999998,
    393307, (s32)btlevtcmd_SetPartsPos, -29999990, 5, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -29999990, 5, 16777216, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 15,
    -30000000, 131097, -30000000, 0, 131122, -29999987, (s32)marioWeapon_KaitenHammerInvolved, 32,
    131122, -29999987, (s32)marioWeapon_UltraHammerInvolved, 33, 196699, (s32)btlevtcmd_GetFriendBelong, -29999990, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -29999990, -30000000, -29999987, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997,
    -29999996, 65539, 0, 131096, -29999997, -1, 65540, 50,
    33, 196699, (s32)btlevtcmd_GetUnitId, -2, -29999990, 131097, -29999990, -29999997,
    196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 65540, 0, 33, 65539,
    10, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131096, -29999997, -1,
    65540, 50, 33, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_GetHomePos, -29999990, -250000000, -29999999, -250000000, 131125,
    -29999999, 15, 393307, (s32)btlevtcmd_JumpPartsSetting, -29999990, 5, 0, -229994880,
    -229999990, 524379, (s32)btlevtcmd_JumpPartsPosition, -29999990, 5, -30000000, -29999999, -29999998,
    0, -1, 458843, (s32)btlevtcmd_CheckDamage, -29999990, -29999997, -29999996, -29999987,
    256, -29999995, 65540, 10, 65539, 50, 262235, (s32)btlevtcmd_GetStageSize,
    -29999995, -250000000, -250000000, 131122, -30000000, 0, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -29999990, -30000000, -29999995, 327771, (s32)btlevtcmd_GetPos, -29999990, -250000000, -29999999,
    -250000000, 393307, (s32)btlevtcmd_JumpPartsSetting, -29999990, 5, 0, -229994880, -229999990,
    524379, (s32)btlevtcmd_JumpPartsPosition, -29999990, 5, -30000000, -29999999, -29999998, 0,
    -1, 262235, (s32)btlevtcmd_OnPartsAttribute, -29999990, 5, 16777216, 262235, (s32)btlevtcmd_CheckDamagePattern,
    -29999990, 16, -29999995, 131097, -29999995, 0, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -29999990, -29999989, (s32)marioWeapon_UltraHammerFinish, 131328, -29999995, 33, 33,
    2, 1,
};

static EVT_BEGIN(damage_swallow_body)
    SET_VALUE(LW(14), 39)
    SET_VALUE(LW(15), -1)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_GetDamage, LW(10), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
            WAIT_FRAMES(30)
            IF_INT_NOT_EQUAL(LW(15), -1)
                CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(15))
                WAIT_FRAMES(30)
            END_IF
            ELSE
            CALL_CHILD(PTR(subsetevt_nodamage_motion))
        END_IF
        ELSE
        WAIT_FRAMES(3)
        SET_VALUE(LW(12), LW(11))
        CALL(btlevtcmd_GetUnitWork, LW(10), 0, LW(0))
        SUBTRACT(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, LW(10), 0, LW(0))
        CALL_CHILD(PTR(_body_param_set))
        SWITCH(LW(0))
            CASE_EQUAL(1)
            SET_VALUE(LW(11), 4)
            CALL(btlevtcmd_SetSwallowParam, -2, 50)
            CALL(btlevtcmd_SetSwallowAttribute, -2, 2)
            CALL(btlevtcmd_SetStatusIconOffset, -2, 14, 20)
            CALL(btlevtcmd_SetCutBaseOffset, -2, 0, 10, 0)
            CALL(btlevtcmd_SetKissHitOffset, -2, 10, 16, 0)
            CASE_EQUAL(2)
            SET_VALUE(LW(11), 3)
            CALL(btlevtcmd_SetStatusIconOffset, -2, 14, 40)
            CALL(btlevtcmd_SetCutBaseOffset, -2, 0, 20, 0)
            CALL(btlevtcmd_SetKissHitOffset, -2, 10, 26, 0)
            CASE_EQUAL(3)
            SET_VALUE(LW(11), 2)
            CALL(btlevtcmd_SetStatusIconOffset, -2, 14, 60)
            CALL(btlevtcmd_SetCutBaseOffset, -2, 0, 30, 0)
            CALL(btlevtcmd_SetKissHitOffset, -2, 10, 36, 0)
            CASE_DEFAULT
            SET_VALUE(LW(11), 1)
            CALL(btlevtcmd_SetStatusIconOffset, -2, 14, 80)
            CALL(btlevtcmd_SetCutBaseOffset, -2, 0, 40, 0)
            CALL(btlevtcmd_SetKissHitOffset, -2, 10, 52, 0)
        END_SWITCH
        BEGIN_SIBLING_EVENT
            WAIT_FRAMES(3)
            CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(12), 9)
            CALL(btlevtcmd_OnPartsAttribute, LW(10), LW(12), 50397184)
            CALL(btlevtcmd_OnPartsAttribute, LW(10), LW(11), 9)
            CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(11), 16842752)
            CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
            WAIT_FRAMES(1)
            CALL_CHILD(PTR(subset_dmg_sambo_fall))
        END_SIBLING_EVENT
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPartsPos, LW(10), 5, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_OffPartsAttribute, LW(10), 5, 16777216)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 25)
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_DivePartsPosition, -2, 5, LW(0), LW(1), LW(2), 5, 0, 0, 0, -1)
        CALL(btlevtcmd_OnPartsAttribute, LW(10), 5, 16777216)
        WAIT_FRAMES(20)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_SetRotateOffset, -2, 0, 0, 0)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(10))
    SWITCH(LW(10))
        CASE_EQUAL(1)
        SET_VALUE(LW(11), 4)
        CASE_EQUAL(2)
        SET_VALUE(LW(11), 3)
        CASE_EQUAL(3)
        SET_VALUE(LW(11), 2)
        CASE_DEFAULT
        SET_VALUE(LW(11), 1)
    END_SWITCH
    IF_INT_EQUAL(LW(10), 4)
        CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 1)
            CALL(evt_sub_random, 99, LW(0))
            IF_INT_LESS(LW(0), 30)
                CALL(btlevtcmd_GetPos, -2, LW(6), LW(7), LW(8))
                CALL(btlevtcmd_FaceDirectionAdd, -2, LW(6), 40)
                SUBTRACT(LW(8), 10)
                CALL(btlevtcmd_CheckSpace, LW(3), LW(6), LW(7), LW(8), 40, 0, 0, 0)
                IF_INT_EQUAL(LW(3), -1)
                    IF_INT_GREATER(LW(6), 0)
                        CALL_CHILD(PTR(call_friend_event))
                        GOTO(99)
                    END_IF
                END_IF
            END_IF
        END_IF
    END_IF
    IF_INT_GREATER_OR_EQUAL(LW(10), 2)
        CALL(evt_sub_random, 69, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 30)
            SWITCH(LW(10))
                CASE_EQUAL(4)
                CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
                CALL(btlevtcmd_SamplingEnemy, -2, LW(0), PTR(weapon_sambo_head_attack_4))
                CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(weapon_sambo_head_attack_4), LW(3), LW(4))
                CASE_EQUAL(3)
                CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
                CALL(btlevtcmd_SamplingEnemy, -2, LW(0), PTR(weapon_sambo_head_attack_3))
                CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(weapon_sambo_head_attack_3), LW(3), LW(4))
                CASE_EQUAL(2)
                CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
                CALL(btlevtcmd_SamplingEnemy, -2, LW(0), PTR(weapon_sambo_head_attack_2))
                CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(weapon_sambo_head_attack_2), LW(3), LW(4))
            END_SWITCH
            IF_INT_NOT_EQUAL(LW(3), -1)
                CALL_CHILD(PTR(attack_head_2_event))
                RETURN
            END_IF
        END_IF
        CALL_CHILD(PTR(attack_spike_event))
        RETURN
    END_IF
    CALL_CHILD(PTR(attack_head_1_event))
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 attack_head_2_event[] = {
    131122, -29999994, -29999989, 262235, (s32)btlevtcmd_CheckStatus, -2, 11, -29999995,
    65570, -29999990, 65572, 4, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_sambo_head_attack_4, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_sambo_head_attack_4,
    -29999997, -29999996, 65572, 3, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_sambo_head_attack_3, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_sambo_head_attack_3,
    -29999997, -29999996, 65572, 2, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_sambo_head_attack_2, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_sambo_head_attack_2,
    -29999997, -29999996, 49, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 262235, (s32)btlevtcmd_AttackDeclare, -2,
    -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 65570, -29999990, 65572, 4,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_sambo_head_attack_4, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_sambo_head_attack_4, 65572,
    3, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_sambo_head_attack_3, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_sambo_head_attack_3,
    65572, 2, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_sambo_head_attack_2, 131163, (s32)btlevtcmd_WeaponAftereffect,
    (s32)weapon_sambo_head_attack_2, 49, 196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit,
    0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 200, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 65570, -29999990, 65572, 4, 131096, -29999995,
    0, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 60, 32, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 42, 33, 65572, 3, 131096,
    -29999995, 0, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 40, 32,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 28, 33, 65572, 2,
    131096, -29999995, 0, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 20,
    32, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 14, 33, 49,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999994, 40, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229997952, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 0, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, -29999994, 43, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985,
    131122, -29999986, 40, 131096, -29999985, -1, 131122, -29999986,
    -40, 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_ATTACK1", -250000000, 0,
    -250000000, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 0, 0, 327771,
    (s32)evt_sub_intpl_init, 11, 0, -29999986, 40, 65539, 0, 65627,
    (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, -30000000, 65545,
    1, 131096, -29999999, 1, 65540, 0, 33, 458843,
    (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985, 131122,
    -29999987, 40, 131122, -29999986, -90, 131096, -29999985, -1,
    131122, -29999987, -40, 131122, -29999986, 90, 33, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_ATTACK4", -250000000, 0, -250000000, 327771, (s32)evt_sub_intpl_init,
    1, -29999987, -29999986, 10, 65539, 3, 65627, (s32)evt_sub_intpl_get_value,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, -30000000, 65545, 1,
    131096, -29999999, 1, 65540, 3, 33, 65570, -29999990,
    65572, 4, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_sambo_head_attack_4,
    256, -29999995, 65572, 3, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, (s32)weapon_sambo_head_attack_3, 256, -29999995, 65572, 2, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, (s32)weapon_sambo_head_attack_2, 256, -29999995, 49, 65570,
    -29999995, 65579, 4, 65540, 90, 46, 65572, 3,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572,
    6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572,
    1, 65540, 91, 46, 42, 65540, 98, 46,
    49, 65539, 90, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 131122, -29999986, -90, 131096, -29999985,
    -1, 131122, -29999986, 90, 33, 327771, (s32)evt_sub_intpl_init, 0,
    -29999986, 0, 10, 65539, 4, 65627, (s32)evt_sub_intpl_get_value, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, -30000000, 65545, 1, 131096,
    -29999999, 1, 65540, 4, 33, 65540, 98, 65539,
    91, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 65570,
    -29999990, 65572, 4, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_sambo_head_attack_4, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_sambo_head_attack_4, 256, -29999995, 65572,
    3, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_sambo_head_attack_3, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, (s32)weapon_sambo_head_attack_3, 256, -29999995, 65572, 2, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_sambo_head_attack_2, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    (s32)weapon_sambo_head_attack_2, 256, -29999995, 49, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 90, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999994, 43, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 131122, -29999986, -90, 131096, -29999985,
    -1, 131122, -29999986, 90, 33, 327771, (s32)evt_sub_intpl_init, 0,
    -29999986, 0, 20, 65539, 5, 65627, (s32)evt_sub_intpl_get_value, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, -30000000, 65545, 1, 131096,
    -29999999, 1, 65540, 5, 33, 65539, 98, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999994, 41,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 attack_head_1_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_sambo_head_attack_1, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_sambo_head_attack_1, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_sambo_head_attack_1, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996,
    65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_sambo_head_attack_1, 196699, (s32)evt_btl_camera_set_mode,
    0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229997952, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999995, -29999994, -29999993, 262235, (s32)btlevtcmd_TransStageFloorPosition,
    -29999995, -29999994, -29999993, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -29999995, 50,
    131122, -29999992, 35, 65630, (s32)sambo_rabbit_move, 65545, 10, 458843,
    (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_sambo_head_attack_1, 256, -29999995, 65570,
    -29999995, 65579, 4, 65540, 90, 46, 65572, 3,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572,
    6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572,
    1, 65540, 91, 46, 42, 65540, 98, 46,
    49, 65539, 90, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999693, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -29999997, -30000000, 5, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998,
    131125, -29999999, 10, 110, 65545, 2, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999985, 131122, -29999986,
    -10, 131096, -29999985, -1, 131122, -29999986, 10, 33,
    131122, -30000000, 0, 65541, 15, 131125, -30000000, -29999986,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, -30000000, 65545, 1,
    6, 112, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_MOVE3", -250000000, 0,
    -250000000, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 44,
    -1, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 10, 0, 110,
    65545, 2, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 131122, -30000000, 180, 65541, 12, 131096,
    -29999985, -1, 131125, -30000000, 15, 131096, -30000000, 360,
    131122, -30000000, 0, 33, 32, 131126, -30000000, 15,
    131096, -30000000, 0, 131122, -30000000, 360, 33, 33,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, -30000000, 65545, 1,
    6, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 0, 0, 112,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229998976, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -30000000, 30, 262235,
    (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 12, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_MOVE2",
    -250000000, 0, -250000000, 65545, 30, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 65540, 98, 65539, 91, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 131125, -29999999, 10, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999693, 110, 65545, 2, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999985, 131122, -29999986,
    -10, 131096, -29999985, -1, 131122, -29999986, 10, 33,
    131122, -30000000, 0, 65541, 15, 131125, -30000000, -29999986,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, -30000000, 65545, 1,
    6, 112, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_MOVE3", -250000000, 0,
    -250000000, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 36,
    -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_ATTACK6", -250000000, 0, -250000000,
    393307, (s32)evt_btl_camera_shake_h, 0, 1, 1, 8, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_add_zoom, 0, -50, 65545,
    2, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_sambo_head_attack_1, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, (s32)weapon_sambo_head_attack_1, 256, -29999995, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999079, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 40, 262235, (s32)btlevtcmd_TransStageFloorPosition,
    -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 20, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_MOVE2", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 30, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 16, -1, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_MOVE2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 12, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_MOVE2", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 10, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 8, -1, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_MOVE2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 4, 43, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 4, 41, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229996928, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999488, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -29999995, -29999994, -29999993, 131122, -29999992, 35, 65630,
    (s32)sambo_rabbit_move, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};

static s32 attack_spike_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -29999990, 65570, -29999990, 65572,
    4, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2,
    -30000000, (s32)weapon_sambo_spike_attack_4, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_sambo_spike_attack_4, -29999997, -29999996, 65572,
    3, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2,
    -30000000, (s32)weapon_sambo_spike_attack_3, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_sambo_spike_attack_3, -29999997, -29999996, 65572,
    2, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2,
    -30000000, (s32)weapon_sambo_spike_attack_2, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_sambo_spike_attack_2, -29999997, -29999996, 49,
    131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000,
    131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540,
    99, 33, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 65570, -29999990, 65572, 4, 196699, (s32)btlevtcmd_PayWeaponCost, -2,
    (s32)weapon_sambo_spike_attack_4, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_sambo_spike_attack_4, 65572, 3, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, (s32)weapon_sambo_spike_attack_3, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_sambo_spike_attack_3, 65572, 2, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_sambo_spike_attack_2, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_sambo_spike_attack_2, 49, 458843,
    (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985, 196699,
    (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 262235, (s32)btlevtcmd_CheckStatus, -2, 11, -30000000,
    131097, -30000000, 0, 393307, (s32)btlevtcmd_SetPartsScale, -2, 5, -229999284,
    -229999284, -229998976, 32, 393307, (s32)btlevtcmd_SetPartsScale, -2, 5, -229998976,
    -229998976, -229998976, 33, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -29999990,
    131126, -29999990, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, -29999990,
    65630, (s32)_body_param_set, 65570, -29999990, 65572, 3, 131122, -29999993,
    1, 131122, -29999994, 2, 262235, (s32)btlevtcmd_SetStatusIconOffset, -2, 14,
    60, 327771, (s32)btlevtcmd_SetCutBaseOffset, -2, 0, 30, 0, 327771,
    (s32)btlevtcmd_SetKissHitOffset, -2, 10, 36, 0, 65572, 2, 131122,
    -29999993, 2, 131122, -29999994, 3, 262235, (s32)btlevtcmd_SetStatusIconOffset, -2,
    14, 40, 327771, (s32)btlevtcmd_SetCutBaseOffset, -2, 0, 20, 0,
    327771, (s32)btlevtcmd_SetKissHitOffset, -2, 10, 26, 0, 65572, 1,
    131122, -29999993, 3, 131122, -29999994, 4, 196699, (s32)btlevtcmd_SetSwallowParam,
    -2, 50, 196699, (s32)btlevtcmd_SetSwallowAttribute, -2, 2, 262235, (s32)btlevtcmd_SetStatusIconOffset,
    -2, 14, 20, 327771, (s32)btlevtcmd_SetCutBaseOffset, -2, 0, 10,
    0, 327771, (s32)btlevtcmd_SetKissHitOffset, -2, 10, 16, 0, 49,
    262235, (s32)btlevtcmd_OffPartsAttribute, -2, -29999993, 9, 262235, (s32)btlevtcmd_OnPartsAttribute, -2,
    -29999993, 50397184, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, -29999994, 9, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, -29999994, 16842752, 262235, (s32)btlevtcmd_CheckStatus, -2, 11,
    -29999995, 110, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    131096, -29999995, 0, 131122, -29999991, 20, 131122, -29999989,
    20, 32, 131122, -29999991, 14, 131122, -29999989, 14,
    33, 131127, -29999991, -29999990, 131126, -29999991, -29999989, 131125,
    -29999999, -29999991, 393307, (s32)btlevtcmd_SetPartsPos, -2, 5, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 5, 16777216, 262235, (s32)btlevtcmd_SetPartsFallAccel,
    -2, 5, -229999386, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 5, (s32)"SNB_B_1",
    524379, (s32)btlevtcmd_JumpPartsPosition, -2, 5, -30000000, -29999999, -29999998, 30,
    -1, 112, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_ATTACK3", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999994, 50, 65545, 24,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_ATTACK4", -250000000, 0, -250000000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_ATTACK5", -250000000, 0, -29999986, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, -29999994, 51, 65545, 2, 65545, 5, 65570,
    -29999990, 65572, 3, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    (s32)weapon_sambo_spike_attack_4, 256, -29999995, 65572, 2, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, (s32)weapon_sambo_spike_attack_3, 256, -29999995, 65572, 1, 458843,
    (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_sambo_spike_attack_2, 256, -29999995, 49,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90,
    65572, 1, 65540, 91, 46, 42, 65540, 98,
    46, 49, 65539, 90, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize, -30000000, -250000000, -250000000,
    196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999991, 131127, -30000000, -29999991, 131126,
    -29999999, 5, 262235, (s32)btlevtcmd_SetPartsMoveSpeed, -2, 5, -229989760, 262235,
    (s32)btlevtcmd_SetPartsFallAccel, -2, 5, -229999898, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 5,
    -30000000, -29999999, -29999998, 0, -1, 131163, (s32)evt_snd_sfxoff, -29999986,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, 5, 16777216, 65540, 99, 65539,
    91, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_SetPartsMoveSpeed, -2, 5, -229989760, 262235, (s32)btlevtcmd_SetPartsFallAccel, -2,
    5, -229999898, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 5, -30000000, -29999999,
    -29999998, 0, -1, 393307, (s32)evt_btl_camera_shake_h, 0, 1, 1,
    8, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_add_zoom,
    0, -50, 65570, -29999990, 65572, 3, 131122, -29999988,
    (s32)weapon_sambo_spike_attack_4, 65572, 2, 131122, -29999988, (s32)weapon_sambo_spike_attack_3, 65572, 1,
    131122, -29999988, (s32)weapon_sambo_spike_attack_2, 49, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 256, -29999995,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999994, 43, 131096, -29999995, 21,
    131163, (s32)evt_snd_sfxoff, -29999986, 196699, (s32)btlevtcmd_GetBodyId, -2, -29999989, 393307,
    (s32)btlevtcmd_GetHitPos, -2, -29999989, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_SetPartsMoveSpeed,
    -2, 5, -229995392, 262235, (s32)btlevtcmd_SetPartsFallAccel, -2, 5, -229999591,
    524379, (s32)btlevtcmd_JumpPartsPosition, -2, 5, -30000000, -29999999, -29999998, 40,
    -1, 107, 393307, (s32)btlevtcmd_GetPartsPos, -2, 5, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 55, 262235, (s32)btlevtcmd_TransStageFloorPosition,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_SetPartsMoveSpeed, -2, 5, -229996928,
    262235, (s32)btlevtcmd_SetPartsFallAccel, -2, 5, -229999898, 720987, (s32)btlevtcmd_DivePartsPosition, -2,
    5, -30000000, -29999999, -29999998, 0, 25, 0, 0,
    -1, 262235, (s32)btlevtcmd_SetPartsMoveSpeed, -2, 5, -229997952, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 24, 720987, (s32)btlevtcmd_DivePartsPosition, -2, 5, -30000000,
    -29999999, -29999998, 0, 21, 0, 0, -1, 262235,
    (s32)btlevtcmd_SetPartsMoveSpeed, -2, 5, -229998464, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    20, 720987, (s32)btlevtcmd_DivePartsPosition, -2, 5, -30000000, -29999999, -29999998,
    0, 20, 0, 0, -1, 262235, (s32)btlevtcmd_OnPartsAttribute, -2,
    5, 16777216, 109, 458843, (s32)btlevtcmd_CheckDamage, -2, -2, -29999989,
    -29999988, 256, -29999995, 2, 33, 131163, (s32)evt_snd_sfxoff, -29999986,
    393307, (s32)btlevtcmd_GetPartsPos, -2, 5, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -29999997, -30000000, 55, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_SetPartsMoveSpeed, -2, 5, -229996928, 262235, (s32)btlevtcmd_SetPartsFallAccel,
    -2, 5, -229999898, 720987, (s32)btlevtcmd_DivePartsPosition, -2, 5, -30000000,
    -29999999, -29999998, 0, 25, 0, 0, -1, 262235,
    (s32)btlevtcmd_SetPartsMoveSpeed, -2, 5, -229997952, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -30000000,
    24, 720987, (s32)btlevtcmd_DivePartsPosition, -2, 5, -30000000, -29999999, -29999998,
    0, 21, 0, 0, -1, 262235, (s32)btlevtcmd_SetPartsMoveSpeed, -2,
    5, -229998464, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -30000000, 20, 720987,
    (s32)btlevtcmd_DivePartsPosition, -2, 5, -30000000, -29999999, -29999998, 0, 20,
    0, 0, -1, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 5, 16777216,
    65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65539, 99,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 call_friend_event[] = {
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"SNB_S_1", 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_SAMBO_SEND_GROUP1_3", -250000000, 0, -250000000, 327771, (s32)evt_sub_intpl_init, 11, 0,
    -20, 40, 65539, 0, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 0, -30000000, 65545, 1, 131096, -29999999,
    1, 65540, 0, 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_SEND_GROUP1_2",
    -250000000, 0, -250000000, 327771, (s32)evt_sub_intpl_init, 11, -20, 30,
    40, 65539, 1, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, -30000000, 65545, 1, 131096, -29999999, 1,
    65540, 1, 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_SEND_GROUP1_1", -250000000,
    0, -250000000, 327771, (s32)evt_sub_intpl_init, 11, 30, -40, 40,
    65539, 2, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, -30000000, 65545, 1, 131096, -29999999, 1, 65540,
    2, 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_SEND_GROUP2", -250000000, 0,
    -250000000, 327771, (s32)evt_sub_intpl_init, 11, -40, 90, 20, 65539,
    3, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    -30000000, 65545, 1, 131096, -29999999, 1, 65540, 3,
    33, 65545, 40, 107, 393307, (s32)evt_btl_camera_shake_h, 0, 2,
    0, 10, 13, 109, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_sambo,
    0, 131122, -30000000, -29999994, 131122, -29999999, -29999993, 131122,
    -29999998, -29999992, 131126, -29999999, 80, 327771, (s32)btlevtcmd_SetPos, -29999997,
    -30000000, -29999999, -29999998, 110, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 983131,
    (s32)evt_eff, 0, (s32)"kemuri_test", 14, -30000000, -29999999, -29999998, -229998464,
    0, 0, 0, 0, 0, 0, 0, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_SEND_GROUP3\0\0", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -29999997, 1, (s32)"SNB_D_1", 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999,
    -29999998, 196699, (s32)btlevtcmd_SetFallAccel, -29999997, -229999284, 458843, (s32)btlevtcmd_JumpPosition, -29999997,
    -29999994, -29999993, -29999992, 20, -1, 327771, (s32)btlevtcmd_SetHomePos, -29999997,
    -29999994, -29999993, -29999992, 65545, 40, 131163, (s32)btlevtcmd_StartWaitEvent, -29999997,
    112, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -29999996, 131125, -29999996,
    1, 262235, (s32)btlevtcmd_SetUnitWork, -29999997, 1, -29999996, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 327771, (s32)evt_sub_intpl_init, 4, 90, -30, 14,
    65539, 4, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, -30000000, 65545, 1, 131096, -29999999, 1, 65540,
    4, 33, 65545, 40, 327771, (s32)evt_sub_intpl_init, 11, -30,
    0, 20, 65539, 5, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 0, -30000000, 65545, 1, 131096, -29999999,
    1, 65540, 5, 33, 65545, 40, 2, 1,
};

static __declspec(section ".data") s32 entry_sambo[] = {
    (s32)&unit_sambo, 16777216, 67108868, -998637568, -998637568, -998637568, 0, 0,
    0, 0, 0, 0,
};

static EVT_BEGIN(wait_event)
    SET_VALUE(LW(10), -2)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        SET_VALUE(LW(11), 4)
        CASE_EQUAL(2)
        SET_VALUE(LW(11), 3)
        CASE_EQUAL(3)
        SET_VALUE(LW(11), 2)
        CASE_DEFAULT
        SET_VALUE(LW(11), 1)
    END_SWITCH
    CALL(btlevtcmd_AnimeChangePoseFromTable, LW(10), LW(11))
    RETURN
EVT_END()

static s32 sambo_rabbit_move[] = {
    65539, 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    131122, -29999989, -29999995, 131126, -29999989, -30000000, 131122, -29999988,
    -29999989, 131098, -29999988, 0, 131127, -29999988, -1, 33,
    131099, -29999988, -29999992, 131101, -29999989, 0, 131125, -30000000,
    -29999992, 32, 131126, -30000000, -29999992, 33, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_SAMBO_MOVE2", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999994, -29999998, 0, -1, 65540, 0, 32,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_SAMBO_MOVE2", -250000000, 0, -250000000, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -29999995, -29999994, -29999993, 0, -1, 33,
    2, 1,
};

static EVT_BEGIN(_body_param_set)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetHeight, -2, 20)
        CALL(btlevtcmd_SetCutHeight, -2, 20)
        CASE_EQUAL(2)
        CALL(btlevtcmd_SetHeight, -2, 40)
        CALL(btlevtcmd_SetCutHeight, -2, 40)
        CASE_EQUAL(3)
        CALL(btlevtcmd_SetHeight, -2, 60)
        CALL(btlevtcmd_SetCutHeight, -2, 60)
        CASE_DEFAULT
        CALL(btlevtcmd_SetHeight, -2, 80)
        CALL(btlevtcmd_SetCutHeight, -2, 80)
    END_SWITCH
    RETURN
EVT_END()

