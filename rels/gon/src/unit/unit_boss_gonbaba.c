#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle_unit.h"
#include "manager/evtmgr_cmd.h"
#include "system.h"
#include "stdlib.h"
#include "dolphin/mtx.h"
#include "battle/battle.h"
#include "battle/battle_sub.h"

f32 sinfd(f32 degrees);
f32 cosfd(f32 degrees);
u8* lightGetPaperCraft(void);

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_OnUnitFlag);
USER_FUNC(btlevtcmd_SetBaseScale);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetTalkBodyId);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_audience_base_flag_on);
USER_FUNC(evt_audience_delete);
USER_FUNC(evt_audience_entry);
USER_FUNC(evt_audience_flag_on);
USER_FUNC(evt_sub_random);
s32 weaponGetPower_Gonbaba(BattleUnit* unit, s32* weapon);
static USER_FUNC(_leg_smoke_effect);
USER_FUNC(_btlgon_get_escape_param);
USER_FUNC(_set_gonbaba_light);
USER_FUNC(_wait_damage_event_end);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_AnimeFlagOnOff[];
extern s32 btlevtcmd_AnimeSetPoseTable[];
extern s32 btlevtcmd_AnimeWaitPlayComplete[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckDamageCode[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_ClearAllStatus[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetBodyId[];
extern s32 btlevtcmd_GetDamage[];
extern s32 btlevtcmd_GetDamagePartsId[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetExp[];
extern s32 btlevtcmd_GetGuardKouraId[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetHp[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetStageAudienceAreaSize[];
extern s32 btlevtcmd_GetStageSize[];
extern s32 btlevtcmd_GetUnitKind[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_RunDataEventChild[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetHomePos[];
extern s32 btlevtcmd_SetHp[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetPos[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SetStayPose[];
extern s32 btlevtcmd_SetTalkPose[];
extern s32 btlevtcmd_SetTogeOffset[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_StatusWindowOnOff[];
extern s32 btlevtcmd_StoreExp[];
extern s32 btlevtcmd_WaitAttackEnd[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_ftomsec[];
extern s32 btlevtcmd_onoff_battleflag[];
extern s32 btlevtcmd_reset_move_color_lv_all[];
extern s32 btlevtcmd_reset_turn[];
extern s32 btlevtcmd_snd_se[];
extern s32 btlevtcmd_snd_se_offset[];
extern s32 evt_audience_flag_check[];
extern s32 evt_audience_flag_off[];
extern s32 evt_audience_get_position[];
extern s32 evt_audience_jump_position_firstsp[];
extern s32 evt_audience_move_position_speed[];
extern s32 evt_audience_num_updown_in_event[];
extern s32 evt_audience_set_animpose[];
extern s32 evt_audience_set_position[];
extern s32 evt_audience_set_rotate[];
extern s32 evt_audience_set_rotate_offset[];
extern s32 evt_batstage_set_aud_dark[];
extern s32 evt_batstage_set_aud_dark_base[];
extern s32 evt_btl_camera_noshake[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_moveto[];
extern s32 evt_btl_camera_set_prilimit[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_btl_camera_wait_move_end[];
extern s32 evt_eff[];
extern s32 evt_map_replayanim[];
extern s32 evt_msg_continue[];
extern s32 evt_msg_print[];
extern s32 evt_msg_select[];
extern s32 evt_msg_toge[];
extern s32 evt_snd_sfx_pos[];
extern s32 evt_snd_sfxoff[];
extern s32 evt_snd_sfxon[];
extern s32 evt_snd_sfxon_3d[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_boss_gonbaba_negone_one_374;
__declspec(section ".data") s32 fd_boss_gonbaba_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_gonbaba___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_gonbaba___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_gonbaba_one_negone_373;
__declspec(section ".data") s32 fd_boss_gonbaba___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_gonbaba_one_381[1];
__declspec(section ".data") u64 fd_boss_gonbaba_negone_one_360;
__declspec(section ".data") s32 fd_boss_gonbaba_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_gonbaba___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_gonbaba___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_gonbaba_one_negone_359;
__declspec(section ".data") s32 fd_boss_gonbaba___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_gonbaba_one_364[1];
s32 weapon_gonbaba_fumituke_attack[48];
s32 weapon_gonbaba_firebreath_attack[48];
s32 weapon_gonbaba_kamituki_attack[48];
BattleUnitKind unit_boss_gonbaba;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[9];
static PoseTableEntry pose_table_weak[9];
static __declspec(section ".data") BattleDataEntry data_table[3];
static BattleUnitKindPart parts[3];
static s32 battle_entry_event[375];
s32 negotiation_event[1786];
s32 gon_extra_eaten_event[389];
static __declspec(section ".data") s32 damage_event[10];
s32 gonbaba_damage_sub_event[574];
static s32 dead_event[283];
static s32 init_event[160];
static __declspec(section ".data") s32 phase_event[2];
static s32 attack_event[56];
static s32 fumituke_attack_event[386];
s32 firebreath_attack_event[261];
static __declspec(section ".data") s32 wait_event[6];

s32 weaponGetPower_Gonbaba(BattleUnit* unit, s32* weapon) {
    s32 power = weapon[8];

    power -= unit->work[0];
    if (power <= 0) {
        power = 1;
    }
    return power;
}

struct EffectEntry* effKemuri9N64Entry(s32 type, s32 arg1, s32 arg2, f32 x, f32 y, f32 z, f32 arg6, f32 arg7);

static USER_FUNC(_leg_smoke_effect) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    effKemuri9N64Entry(1, 18, 90, x, y, z, 60.0f, 0.0f);
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_boss_gonbaba_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_gonbaba_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_gonbaba___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_gonbaba___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_gonbaba_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_gonbaba___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_gonbaba_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_gonbaba_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_gonbaba_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_gonbaba___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_gonbaba___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_gonbaba_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_gonbaba___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_gonbaba_one_364[] = {
    1065353216,
};

s32 weapon_gonbaba_fumituke_attack[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPower_Gonbaba,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 721666, 0, 7, 2047, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 167772160,
};

s32 weapon_gonbaba_firebreath_attack[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPower_Gonbaba,
    4, 50, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 16777986, 0, 71, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_gonbaba_kamituki_attack[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 131080, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

BattleUnitKind unit_boss_gonbaba = {
    23,
    "btl_un_gonbaba",
    20,
    0,
    1,
    1,
    65,
    0,
    0,
    100,
    0,
    50,
    9,
    230,
    170,
    -210,
    45,
    0.0f,
    0.0f,
    0.0f,
    -250,
    0,
    280.0f,
    40.0f,
    0.0f,
    115.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    250.0f,
    0.0f,
    0.0f,
    115.0f,
    110.5f,
    0.0f,
    -290.0f,
    85.0f,
    0.0f,
    230.0f,
    170.0f,
    0,
    0,
    -1,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_GNB_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x200000,
    &regist,
    3,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {20, 0, 50, 0, 50, 10, 100, 0, 0, 0, 50, 0, 100, 0, 100, 0, 0, 100, 0, 0, 0, 0};

static PoseTableEntry pose_table[] = {
    {1, "GNB_N_1"},
    {5, "GNB_X_1"},
    {2, "GNB_Z_1"},
    {3, "GNB_X_1"},
    {28, "GNB_S_3"},
    {65, "GNB_T_3"},
    {31, "GNB_S_3"},
    {39, "GNB_D_1"},
    {69, "GNB_S_3"},
};

static PoseTableEntry pose_table_weak[] = {
    {1, "GNB_N_1"},
    {5, "GNB_X_1"},
    {2, "GNB_N_1"},
    {3, "GNB_X_1"},
    {28, "GNB_S_4"},
    {65, "GNB_T_4"},
    {31, "GNB_S_4"},
    {39, "GNB_V_1"},
    {69, "GNB_S_4"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {9, gonbaba_damage_sub_event},
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_gonbaba", "c_gonbaba", 0.0f, 0.0f, 0.0f, 230.0f, 36.0f, 60.0f, 230.0f, 36.0f, 60.0f, 20, 30, 255, &defence, &defence_attr, 0x22, 0, pose_table},
    {2, "btl_un_gonbaba", "c_gonbaba", 100.0f, 0.0f, 0.0f, 250.0f, 110.0f, 25.0f, 250.0f, 110.0f, 25.0f, 20, 30, 255, &defence, &defence_attr, 0x1600029, 0, pose_table},
    {3, "btl_un_gonbaba", "c_gonbaba4", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x1010000, 0, pose_table},
};

static s32 battle_entry_event[] = {
    131163, (s32)evt_btl_camera_set_prilimit, 1, 196699, (s32)evt_map_replayanim, 0, (s32)"dontyo", 196699,
    (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, 0, 110,
    1080, 0, 93, -2, 1, 0, 262235, (s32)btlevtcmd_GetStageSize,
    -29999994, -250000000, -250000000, 131127, -29999994, -1, 327771, (s32)btlevtcmd_GetHomePos,
    -3, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -4, -29999997,
    -29999996, -29999995, 327771, (s32)btlevtcmd_SetPos, -3, -29999994, -29999999, -29999998,
    327771, (s32)btlevtcmd_SetPos, -4, -29999994, -29999996, -29999995, 262235, (s32)btlevtcmd_GetStageSize,
    -250000000, -29999997, -250000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131125, -29999999, -29999997, 327771, (s32)btlevtcmd_SetPos, -2, -30000000,
    -29999999, -29999998, 65545, 60, 262235, (s32)btlevtcmd_AnimeChangePoseType, -3, 1,
    42, 196699, (s32)btlevtcmd_GetBodyId, -4, -30000000, 262235, (s32)btlevtcmd_AnimeChangePoseType, -4,
    -30000000, 42, 327771, (s32)btlevtcmd_GetHomePos, -3, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_GetHomePos, -4, -29999997, -29999996, -29999995, 131122, -29999992,
    -30000000, 131126, -29999992, -29999997, 131098, -29999992, 0, 131127,
    -29999992, -1, 33, 262235, (s32)btlevtcmd_GetStageSize, -29999994, -250000000, -250000000,
    131122, -29999993, -29999994, 131125, -29999993, -29999992, 131127, -29999994,
    -1, 131127, -29999993, -1, 327771, (s32)btlevtcmd_SetPos, -3, -29999994,
    -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -4, -29999993, -29999996, -29999995,
    110, 196699, (s32)btlevtcmd_SetMoveSpeed, -4, -229993856, 524379, (s32)btlevtcmd_MovePosition, -4,
    -29999997, -29999996, -29999995, 0, -1, 0, 196699, (s32)btlevtcmd_GetBodyId,
    -4, -30000000, 262235, (s32)btlevtcmd_AnimeChangePoseType, -4, -30000000, 43, 112,
    196699, (s32)btlevtcmd_SetMoveSpeed, -3, -229993856, 524379, (s32)btlevtcmd_MovePosition, -3, -30000000,
    -29999999, -29999998, 0, -1, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -3,
    1, (s32)"M_I_Y", 65545, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"GNB_F_3", 65545, 1, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_ftomsec, 10, -30000000, 65546, -30000000, 107, 196699, (s32)btlevtcmd_ftomsec,
    5, -30000000, 65546, -30000000, 262235, (s32)btlevtcmd_AnimeChangePose, -3, 1,
    (s32)"M_I_O", 196699, (s32)btlevtcmd_SetFallAccel, -3, -229999693, 327771, (s32)btlevtcmd_GetPos, -3,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_snd_se, -3, (s32)"SFX_VOICE_MARIO_SURPRISED2_2", -250000000,
    0, -250000000, 458843, (s32)btlevtcmd_JumpPosition, -3, -30000000, -29999999, -29999998,
    25, -1, 109, 107, 196699, (s32)btlevtcmd_ftomsec, 5, -30000000,
    65546, -30000000, 196699, (s32)btlevtcmd_SetFallAccel, -4, -229999693, 327771, (s32)btlevtcmd_GetPos,
    -4, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -4, -30000000,
    -29999999, -29999998, 25, -1, 196699, (s32)btlevtcmd_GetBodyId, -4, -30000000,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -4, -30000000, 5, 109, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_GNB_APPEAR1", -250000000, 0, -250000000, 393307, (s32)evt_btl_camera_shake_h, 1,
    8, 0, 20, 13, 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePose,
    -3, 1, (s32)"M_I_Y", 196699, (s32)btlevtcmd_GetBodyId, -4, -30000000, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -4, -30000000, 43, 196699, (s32)evt_btl_camera_set_mode, 1, 3,
    655451, (s32)evt_btl_camera_set_moveto, 1, -233, 45, 452, 56, 125,
    37, 60, 0, 65545, 60, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0,
    196699, (s32)btlevtcmd_SetTalkPose, -2, (s32)"GNB_T_3", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"GNB_S_3",
    327771, (s32)evt_msg_print, 2, (s32)"stg1_gon_20_3", 0, -2, 131163, (s32)btlevtcmd_StatusWindowOnOff,
    1, 131163, (s32)btlevtcmd_StartWaitEvent, -3, 131163, (s32)btlevtcmd_StartWaitEvent, -4, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 131163, (s32)evt_btl_camera_set_prilimit, 0, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 3, 2, 1,
};

USER_FUNC(_btlgon_get_escape_param) {
    s32* args = event->args;
    s32 x = evtGetValue(event, args[0]);
    s32 y = evtGetValue(event, args[1]);
    s32 dxVar = args[2];
    s32 dyVar = args[3];
    s32 speedVar = args[4];
    f32 angle = angleABf(100.0f, 205.0f, x, y);
    s32 dx;
    s32 dy;
    f32 speed;

    if (angle > 270.0f && angle < 360.0f) {
        angle = 270.0f;
    }
    if (angle < 90.0f) {
        angle = 90.0f;
    }
    dx = 500.0f * sinfd(angle);
    dy = 500.0f * -cosfd(angle);
    speed = 6.0f + rand() % 6;
    speed = 0.67f * speed;
    evtSetValue(event, dxVar, dx);
    evtSetValue(event, dyVar, dy);
    evtSetFloat(event, speedVar, speed);
    return EVT_RETURN_DONE;
}

s32 negotiation_event[] = {
    131163, (s32)evt_btl_camera_set_prilimit, 1, 65627, (s32)evt_btl_camera_wait_move_end, 131163, (s32)btlevtcmd_ClearAllStatus, -2,
    262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table, 196699, (s32)evt_btl_camera_set_mode, 1,
    3, 655451, (s32)evt_btl_camera_set_moveto, 1, 93, 160, 536, 93,
    123, 25, 20, 0, 65545, 20, 65627, (s32)btlevtcmd_reset_move_color_lv_all,
    131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 196699, (s32)btlevtcmd_SetTalkPose, -2, (s32)"GNB_T_4", 196699,
    (s32)btlevtcmd_SetStayPose, -2, (s32)"GNB_S_4", 327771, (s32)evt_msg_print, 2, (s32)"stg1_gon_23", 0,
    -2, 65539, 0, 327771, (s32)btlevtcmd_GetPos, -3, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_GetHomePos, -3, -29999997, -29999996, -29999995, 131097,
    -30000000, -29999997, 65545, 1, 65540, 0, 33, 196699,
    (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, -431, 10,
    735, 56, 125, 37, 1, 0, 65545, 5,
    131122, -29999990, 0, 327771, (s32)evt_msg_print, 2, (s32)"stg1_gon_24", 0,
    -2, 196699, (s32)evt_btl_camera_set_mode, 1, 0, 65545, 20, 196699,
    (s32)evt_msg_select, 0, (s32)"stg1_gon_24_yesno1", 65627, (s32)evt_msg_continue, 131096, -30000000, 0,
    131122, -29999995, 0, 327771, (s32)evt_msg_print, 2, (s32)"stg1_gon_25", 0,
    -2, 65540, 40, 33, 393307, (s32)btlevtcmd_snd_se, -3, (s32)"SFX_VOICE_MARIO_NO1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -3, 1, (s32)"M_N_C",
    327771, (s32)btlevtcmd_AnimeFlagOnOff, -3, 1, 512, 1, 65546, 667,
    196699, (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, 93,
    160, 536, 93, 123, 25, 1, 0, 65545,
    5, 131122, -29999990, 1, 327771, (s32)evt_msg_print, 2, (s32)"stg1_gon_26",
    0, -2, 196699, (s32)evt_btl_camera_set_mode, 1, 0, 65545, 20,
    196699, (s32)evt_msg_select, 0, (s32)"stg1_gon_26_yesno1", 65627, (s32)evt_msg_continue, 131096, -30000000,
    0, 131122, -29999995, 1, 327771, (s32)evt_msg_print, 2, (s32)"stg1_gon_27",
    0, -2, 65540, 40, 33, 393307, (s32)btlevtcmd_snd_se, -3,
    (s32)"SFX_VOICE_MARIO_NO1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -3, 1,
    (s32)"M_N_C", 327771, (s32)btlevtcmd_AnimeFlagOnOff, -3, 1, 512, 1, 65546,
    667, 196699, (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1,
    93, 160, 536, 93, 123, 25, 1, 0,
    65545, 5, 131122, -29999990, 2, 327771, (s32)evt_msg_print, 2,
    (s32)"stg1_gon_28", 0, -2, 196699, (s32)evt_btl_camera_set_mode, 1, 0, 65545,
    20, 196699, (s32)evt_msg_select, 0, (s32)"stg1_gon_28_yesno1", 65627, (s32)evt_msg_continue, 131096,
    -30000000, 0, 131122, -29999995, 2, 327771, (s32)evt_msg_print, 2,
    (s32)"stg1_gon_29", 0, -2, 65540, 40, 33, 393307, (s32)btlevtcmd_snd_se,
    -3, (s32)"SFX_VOICE_MARIO_NO2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -3,
    1, (s32)"M_N_C", 327771, (s32)btlevtcmd_AnimeFlagOnOff, -3, 1, 512, 1,
    65546, 1000, 196699, (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto,
    1, 93, 160, 536, 93, 123, 25, 15,
    0, 65545, 15, 327771, (s32)evt_msg_print, 2, (s32)"stg1_gon_31", 0,
    -2, 65540, 50, 65539, 40, 196699, (s32)btlevtcmd_GetGuardKouraId, -3,
    -29999997, 131097, -29999997, -1, 196699, (s32)btlevtcmd_RunDataEventChild, -29999997, 59,
    262235, (s32)btlevtcmd_SetUnitWork, -29999997, 2, 0, 33, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -3, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -3, -229996928, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, 400, 524379, (s32)btlevtcmd_MovePosition, -3, -30000000, 0, -29999998,
    0, -1, 0, 131096, -29999995, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -3, 1, (s32)"M_C_4", 32, 262235, (s32)btlevtcmd_AnimeChangePoseType, -3, 1,
    43, 33, 65546, 700, 107, 589915, (s32)btlevtcmd_snd_se_offset, -2,
    (s32)"SFX_BOSS_GNB_BITE1", -250000000, 0, -220, 80, 0, -250000000, 196699,
    (s32)btlevtcmd_ftomsec, 15, -30000000, 65546, -30000000, 589915, (s32)btlevtcmd_snd_se_offset, -2,
    (s32)"SFX_BOSS_GNB_BITE2", -250000000, 0, -260, 40, 0, -250000000, 109,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_A_2", 196699, (s32)btlevtcmd_ftomsec, 20,
    -30000000, 65546, -30000000, 196699, (s32)btlevtcmd_GetBodyId, -3, -29999996, 196699,
    (s32)btlevtcmd_ResultACDefence, -3, (s32)weapon_gonbaba_kamituki_attack, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -3, -29999996, (s32)weapon_gonbaba_kamituki_attack, 1048832, -29999995, 65546, 500,
    196699, (s32)btlevtcmd_GetHp, -3, -30000000, 131100, -30000000, 0, 262235,
    (s32)btlevtcmd_CheckDamageCode, -3, 2048, -30000000, 131096, -30000000, 0, 131163,
    (s32)evt_btl_camera_set_prilimit, 0, 2, 33, 65546, 1500, 131163, (s32)_wait_damage_event_end,
    -3, 32, 65546, 1500, 33, 327771, (s32)btlevtcmd_GetPos, -3,
    -30000000, -250000000, -250000000, 327771, (s32)btlevtcmd_GetHomePos, -3, -29999999, -250000000,
    -250000000, 65539, 41, 131097, -30000000, -29999999, 65545, 1,
    65540, 41, 33, 196699, (s32)btlevtcmd_GetGuardKouraId, -3, -29999997, 131097,
    -29999997, -1, 262235, (s32)btlevtcmd_SetUnitWork, -29999997, 2, 1, 33,
    196699, (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, -233,
    45, 452, 56, 125, 37, 1, 0, 65545,
    5, 327771, (s32)evt_msg_print, 2, (s32)"stg1_gon_30", 0, -2, 196699,
    (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, -115, 50,
    265, -115, 49, 170, 1, 0, 65545, 5,
    196699, (s32)btlevtcmd_GetUnitKind, -4, -30000000, 65570, -30000000, 65572, 224,
    327771, (s32)evt_msg_print, 2, (s32)"stg1_gon_30_01", 0, -4, 65572, 225,
    327771, (s32)evt_msg_print, 2, (s32)"stg1_gon_30_02", 0, -4, 49, 196699,
    (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, -431, 10,
    735, 56, 125, 37, 1, 0, 65545, 5,
    327771, (s32)evt_msg_print, 2, (s32)"stg1_gon_30_03", 0, -2, 196699, (s32)evt_btl_camera_set_mode,
    1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, -233, 45, 452,
    56, 125, 37, 20, 0, 65545, 20, 327771,
    (s32)evt_msg_print, 2, (s32)"stg1_gon_30_04", 0, -2, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0,
    65539, 50, 196699, (s32)evt_btl_camera_set_mode, 1, 0, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 3, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_W_4",
    196699, (s32)btlevtcmd_ftomsec, 35, -30000000, 65546, -30000000, 589915, (s32)btlevtcmd_snd_se_offset,
    -2, (s32)"SFX_BOSS_GNB_MOVE1", -250000000, 0, -75, 0, 30, -250000000,
    393307, (s32)evt_btl_camera_shake_h, 1, 2, 0, 10, 13, 196699,
    (s32)btlevtcmd_ftomsec, 23, -30000000, 65546, -30000000, 589915, (s32)btlevtcmd_snd_se_offset, -2,
    (s32)"SFX_BOSS_GNB_MOVE1", -250000000, 0, -12, 0, -30, -250000000, 393307,
    (s32)evt_btl_camera_shake_h, 1, 2, 0, 10, 13, 196699, (s32)btlevtcmd_ftomsec,
    34, -30000000, 65546, -30000000, 589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_MOVE1",
    -250000000, 0, -31, 0, 30, -250000000, 393307, (s32)evt_btl_camera_shake_h,
    1, 2, 0, 10, 13, 196699, (s32)btlevtcmd_ftomsec, 23,
    -30000000, 65546, -30000000, 589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_MOVE1", -250000000,
    0, 125, 0, -30, -250000000, 393307, (s32)evt_btl_camera_shake_h, 1,
    2, 0, 10, 13, 196699, (s32)btlevtcmd_ftomsec, 34, -30000000,
    65546, -30000000, 589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_MOVE1", -250000000, 0,
    137, 0, 30, -250000000, 393307, (s32)evt_btl_camera_shake_h, 1, 2,
    0, 10, 13, 196699, (s32)btlevtcmd_ftomsec, 17, -30000000, 65546,
    -30000000, 65545, 120, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_GetStageAudienceAreaSize, -250000000, -29999997, -250000000, 131125, -29999999,
    -29999997, 262235, (s32)btlevtcmd_GetStageSize, -250000000, -250000000, -29999997, 131125, -29999998,
    -29999997, 131125, -29999998, 80, 327771, (s32)btlevtcmd_SetPos, -2, -30000000,
    -29999999, -29999998, 131125, -30000000, 260, 327771, (s32)btlevtcmd_SetPos, -2,
    -30000000, -29999999, -29999998, 65627, (s32)_set_gonbaba_light, 393307, (s32)evt_btl_camera_shake_h, 1,
    7, 0, 6000, 0, 107, 65546, 600, 131163,
    (s32)evt_btl_camera_noshake, 1, 393307, (s32)evt_btl_camera_shake_h, 1, 7, 0, 30,
    12, 109, 262235, (s32)evt_batstage_set_aud_dark, 0, 24, 0, 262235,
    (s32)evt_batstage_set_aud_dark_base, 0, 24, 0, 107, 65545, 40, 262235,
    (s32)btlevtcmd_AnimeChangePose, -3, 1, (s32)"M_N_7", 196699, (s32)btlevtcmd_SetFallAccel, -3, -229999284,
    327771, (s32)btlevtcmd_GetPos, -3, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition,
    -3, -30000000, -29999999, -29999998, 20, -1, 65545, 60,
    262235, (s32)btlevtcmd_AnimeChangePose, -3, 1, (s32)"M_I_Y", 109, 107, 65545,
    40, 196699, (s32)btlevtcmd_SetFallAccel, -4, -229999284, 327771, (s32)btlevtcmd_GetPos, -4,
    -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -4, -30000000, -29999999,
    -29999998, 20, -1, 109, 131122, -30000000, 13, 65628,
    (s32)gon_extra_eaten_event, 131122, -30000000, 14, 65628, (s32)gon_extra_eaten_event, 131122, -30000000,
    32, 65628, (s32)gon_extra_eaten_event, 131122, -30000000, 33, 65628, (s32)gon_extra_eaten_event,
    131122, -30000000, 34, 65628, (s32)gon_extra_eaten_event, 131122, -30000000, 35,
    65628, (s32)gon_extra_eaten_event, 131122, -30000000, 53, 65628, (s32)gon_extra_eaten_event, 131122,
    -30000000, 54, 65628, (s32)gon_extra_eaten_event, 196699, (s32)btlevtcmd_SetHp, -2, 10,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131122, -30000000,
    40, 131125, -29999999, 180, 131125, -29999998, 70, 983131,
    (s32)evt_eff, 0, (s32)"recovery", 0, -30000000, -29999999, -29999998, 10,
    0, 0, 0, 0, 0, 0, 0, 107,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_E_1", 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_GNB_EAT_APPEAR1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 3,
    (s32)"GNB_P_1", 196699, (s32)btlevtcmd_ftomsec, 14, -30000000, 65546, -30000000, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, 3, 16777216, 196699, (s32)btlevtcmd_ftomsec, 56, -30000000,
    65546, -30000000, 109, 196699, (s32)btlevtcmd_ftomsec, 32, -30000000, 65546,
    -30000000, 196699, (s32)evt_snd_sfxon, (s32)"SFX_AUDIENCE_GNB_PANIC1", 0, 131122, -30000000, 0,
    65541, 100, 262235, (s32)evt_audience_flag_check, -30000000, 1, -29999996, 131096,
    -29999996, 0, 65540, 60, 33, 262235, (s32)evt_audience_flag_check, -30000000,
    16, -29999996, 131097, -29999996, 0, 65540, 60, 33,
    107, 196699, (s32)evt_audience_flag_on, -30000000, 18, 131098, -30000000, 40,
    262235, (s32)evt_audience_set_animpose, -30000000, 7, 0, 32, 262235, (s32)evt_audience_set_animpose,
    -30000000, 9, 0, 33, 327771, (s32)evt_audience_get_position, -30000000, -29999999,
    -29999998, -29999997, 196699, (s32)evt_sub_random, 5, -29999995, 131125, -29999995,
    17, 131125, -29999998, -29999995, 196699, (s32)evt_sub_random, 8, -29999994,
    131125, -29999994, 4, 131122, -29999989, -30000000, 131129, -29999989,
    10, 131097, -29999989, 0, 131122, -29999989, -1, 32,
    196699, (s32)evt_sub_random, 2, -29999989, 65570, -29999989, 65572, 0,
    65572, 1, 131122, -29999989, -1, 42, 131122, -29999989,
    -1, 49, 33, 458843, (s32)evt_audience_jump_position_firstsp, -30000000, -29999999, -29999998,
    -29999997, -29999994, -229999488, 196699, (s32)evt_sub_random, 11, -29999993, 65545,
    -29999993, 131126, -29999998, -29999995, 458843, (s32)evt_audience_jump_position_firstsp, -30000000, -29999999,
    -29999998, -29999997, -29999994, -230000000, 262235, (s32)evt_audience_set_animpose, -30000000, 7,
    0, 196699, (s32)evt_sub_random, 300, -29999994, 131125, -29999994, 400,
    65546, -29999994, 131096, -30000000, 43, 262235, (s32)evt_audience_set_animpose, -30000000,
    9, 0, 327771, (s32)evt_audience_set_rotate, -30000000, -90, 100, 0,
    327771, (s32)evt_audience_get_position, -30000000, -29999999, -29999998, -29999997, 131125, -29999998,
    2, 327771, (s32)evt_audience_set_position, -30000000, -29999999, -29999998, -29999997, 131097,
    -29999989, -1, 131163, (s32)evt_snd_sfxoff, -29999989, 33, 32, 327771,
    (s32)evt_audience_get_position, -30000000, -29999992, -29999991, -29999990, 131122, -29999988, -30000000,
    131129, -29999988, 10, 131097, -29999988, 0, 131122, -29999988,
    -1, 32, 196699, (s32)evt_sub_random, 1, -29999988, 131096, -29999988,
    0, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_AUDIENCE_PANIC_RUN1", -29999992, -29999991, -29999990, -29999988,
    32, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_AUDIENCE_PANIC_RUN2", -29999992, -29999991, -29999990, -29999988,
    33, 65647, -29999987, 65541, 1000, 327771, (s32)evt_audience_get_position, -30000000,
    -29999999, -29999998, -29999997, 327771, (s32)evt_snd_sfx_pos, -29999988, -29999999, -29999998,
    -29999997, 131097, -29999989, -1, 327771, (s32)evt_snd_sfx_pos, -29999989, -29999999,
    -29999998, -29999997, 33, 65545, 1, 6, 112, 33,
    262235, (s32)evt_audience_set_animpose, -30000000, 7, 0, 393307, (s32)_btlgon_get_escape_param, -29999999,
    -29999997, -29999995, -29999994, -29999993, 327771, (s32)evt_audience_get_position, -30000000, -29999992,
    -29999991, -29999990, 131125, -29999995, -29999992, 131125, -29999994, -29999990,
    393307, (s32)evt_audience_move_position_speed, -30000000, -29999995, -29999998, -29999994, -29999993, 131097,
    -29999989, -1, 131163, (s32)evt_snd_sfxoff, -29999989, 33, 131097, -29999988,
    -1, 65631, -29999987, 131163, (s32)evt_snd_sfxoff, -29999988, 33, 131163,
    (s32)evt_audience_delete, -30000000, 131163, (s32)evt_audience_num_updown_in_event, -230001024, 33, 109, 65539,
    60, 131125, -30000000, 1, 6, 65541, 100, 131163,
    (s32)evt_audience_delete, -30000000, 131163, (s32)evt_audience_num_updown_in_event, -230001024, 131125, -30000000, 1,
    6, 196699, (s32)btlevtcmd_ftomsec, 38, -30000000, 65546, -30000000, 110,
    196699, (s32)btlevtcmd_ftomsec, 4, -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_GNB_EAT1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_ftomsec, 45,
    -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GNB_EAT1", -250000000,
    0, -250000000, 196699, (s32)btlevtcmd_ftomsec, 46, -30000000, 65546, -30000000,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GNB_EAT1", -250000000, 0, -250000000, 196699,
    (s32)btlevtcmd_ftomsec, 46, -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_GNB_EAT1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_ftomsec, 46, -30000000,
    65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GNB_EAT1", -250000000, 0,
    -250000000, 196699, (s32)btlevtcmd_ftomsec, 44, -30000000, 65546, -30000000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GNB_EAT1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_ftomsec,
    46, -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GNB_EAT1",
    -250000000, 0, -250000000, 112, 196699, (s32)evt_btl_camera_set_mode, 1, 3,
    655451, (s32)evt_btl_camera_set_moveto, 1, 0, 140, 900, 0, 60,
    0, 30, 0, 196699, (s32)btlevtcmd_ftomsec, 284, -30000000, 65546,
    -30000000, 196699, (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1,
    -115, 50, 200, -115, -30, -670, 20, 0,
    65545, 25, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_S_5", 262235,
    (s32)btlevtcmd_OnPartsAttribute, -2, 3, 16777216, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 196699,
    (s32)btlevtcmd_GetUnitKind, -4, -30000000, 65570, -30000000, 65572, 224, 327771,
    (s32)evt_msg_print, 2, (s32)"stg1_gon_31_00_kur", 0, -4, 65572, 225, 327771,
    (s32)evt_msg_print, 2, (s32)"stg1_gon_31_00_nok", 0, -4, 49, 196699, (s32)evt_btl_camera_set_mode,
    1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, 40, 98, 686,
    57, 125, 182, 1, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetTogeOffset, -2, 310, 60, 0, 196699, (s32)btlevtcmd_SetTalkPose, -2,
    (s32)"GNB_T_5", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"GNB_S_5", 327771, (s32)evt_msg_print, 2,
    (s32)"stg1_gon_31_01", 0, -2, 327771, (s32)btlevtcmd_SetTogeOffset, -2, 0, 0,
    0, 196699, (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1,
    -115, 40, 200, -115, 39, 170, 1, 0,
    65545, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_S_3", 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131126, -30000000, 260,
    327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetHomePos,
    -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_AnimeChangePose, -3, 1,
    (s32)"M_I_Y", 196699, (s32)btlevtcmd_GetUnitKind, -4, -30000000, 65570, -30000000, 65572,
    224, 327771, (s32)evt_msg_print, 2, (s32)"stg1_gon_31_02", 0, -4, 65572,
    225, 327771, (s32)evt_msg_print, 2, (s32)"stg1_gon_31_03", 0, -4, 49,
    131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 196699, (s32)evt_btl_camera_set_mode, 1, 3, 655451,
    (s32)evt_btl_camera_set_moveto, 1, 0, 110, 860, 0, 60, 170,
    20, 0, 65545, 20, 196699, (s32)btlevtcmd_GetBodyId, -4, -29999994,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -4, -29999994, 42, 327771, (s32)btlevtcmd_GetHomePos, -3,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -4, -29999997, -29999996,
    -29999995, 262235, (s32)btlevtcmd_GetStageAudienceAreaSize, -250000000, -29999994, -250000000, 262235, (s32)btlevtcmd_GetStageSize,
    -250000000, -250000000, -29999993, 107, 131125, -29999996, -29999994, 131125,
    -29999995, -29999993, 131125, -29999995, 80, 196699, (s32)btlevtcmd_SetFallAccel, -4,
    -229999284, 458843, (s32)btlevtcmd_JumpPosition, -4, -29999997, -29999996, -29999995, 27,
    -1, 327771, (s32)btlevtcmd_SetHomePos, -4, -29999997, -29999996, -29999995, 109,
    131125, -29999999, -29999994, 131125, -29999998, -29999993, 131125, -29999998,
    80, 196699, (s32)btlevtcmd_SetFallAccel, -3, -229999284, 262235, (s32)btlevtcmd_AnimeChangePose, -3,
    1, (s32)"M_J_1B", 393307, (s32)btlevtcmd_snd_se, -3, (s32)"SFX_VOICE_MARIO_BATTLE_JUMP1", -250000000, 0,
    -250000000, 458843, (s32)btlevtcmd_JumpPosition, -3, -30000000, -29999999, -29999998, 27,
    0, 327771, (s32)btlevtcmd_SetHomePos, -3, -30000000, -29999999, -29999998, 393307,
    (s32)btlevtcmd_snd_se, -3, (s32)"SFX_MARIO_JUMP_LANDING1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_GetBodyId,
    -3, -29999997, 262235, (s32)btlevtcmd_AnimeChangePose, -3, -29999997, (s32)"M_I_Y", 196699,
    (s32)btlevtcmd_GetBodyId, -4, -29999996, 262235, (s32)btlevtcmd_AnimeChangePoseType, -4, -29999996, 69,
    65545, 30, 65627, (s32)btlevtcmd_reset_turn, 131163, (s32)evt_btl_camera_set_prilimit, 0, 196699,
    (s32)btlevtcmd_onoff_battleflag, 1, 256, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 131163,
    (s32)btlevtcmd_StartWaitEvent, -3, 131163, (s32)btlevtcmd_StartWaitEvent, -4, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

USER_FUNC(_set_gonbaba_light) {
    u8* light = lightGetPaperCraft();
    Mtx mtx;

    *(Vec*)(light + 0x24) = (Vec){-200.0f, 50.0f, 500.0f};
    PSMTXScale(mtx, 3.0f, 3.0f, 3.0f);
    PSMTXMultVec(mtx, (Vec*)(light + 0x24), (Vec*)(light + 0x24));
    return EVT_RETURN_DONE;
}

s32 gon_extra_eaten_event[] = {
    65545, 14, 262235, (s32)btlevtcmd_SetUnitWork, -2, 4, 6, 196699,
    (s32)evt_audience_flag_on, -30000000, 18, 196699, (s32)evt_audience_flag_off, -30000000, 4, 262235,
    (s32)evt_audience_set_animpose, -30000000, 9, 0, 327771, (s32)evt_audience_get_position, -30000000, -29999999,
    -29999998, -29999997, 131125, -29999998, 40, 327771, (s32)evt_audience_set_position, -30000000,
    -29999999, -29999998, -29999997, 65545, 1, 131125, -29999998, 80,
    131126, -29999999, 80, 393307, (s32)evt_audience_move_position_speed, -30000000, -29999999, -29999998,
    -29999997, -229989760, 131096, -30000000, 32, 196699, (s32)evt_audience_flag_on, -30000000,
    4, 107, 327771, (s32)evt_audience_set_rotate_offset, -30000000, 0, 18, 0,
    131122, -29999996, 0, 131122, -29999995, 0, 65541, 45,
    131125, -29999996, 2, 131125, -29999995, 15, 327771, (s32)evt_audience_set_rotate,
    -30000000, -29999996, -29999995, 0, 65545, 1, 6, 109,
    327771, (s32)evt_audience_get_position, -30000000, -29999999, -29999998, -29999997, 262235, (s32)btlevtcmd_GetStageAudienceAreaSize,
    -250000000, -29999998, -250000000, 131126, -29999999, 40, 131125, -29999998,
    1, 458843, (s32)evt_audience_jump_position_firstsp, -30000000, -29999999, -29999998, -29999997, 60,
    -229998976, 327771, (s32)evt_audience_set_rotate_offset, -30000000, 0, 0, 0, 327771,
    (s32)evt_audience_set_rotate, -30000000, 90, 0, 0, 65545, 30, 327771,
    (s32)evt_audience_set_rotate_offset, -30000000, 0, 0, 0, 131122, -29999999, 90,
    65541, 90, 131126, -29999999, 1, 327771, (s32)evt_audience_set_rotate, -30000000,
    -29999999, 0, 0, 65545, 1, 6, 327771, (s32)evt_audience_set_rotate,
    -30000000, 0, 0, 0, 262235, (s32)evt_audience_set_animpose, -30000000, 7,
    0, 65545, 10, 327771, (s32)evt_audience_get_position, -30000000, -29999999, -29999998,
    -29999997, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_AUDIENCE_PANIC_SCREAM2", -29999999, -29999998, -29999997, 0,
    393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_AUDIENCE_PANIC_RUN1", -29999999, -29999998, -29999997, -29999995, 65647,
    -29999994, 65541, 1000, 327771, (s32)evt_audience_get_position, -30000000, -29999999, -29999998,
    -29999997, 327771, (s32)evt_snd_sfx_pos, -29999995, -29999999, -29999998, -29999997, 65545,
    1, 6, 112, 393307, (s32)evt_audience_move_position_speed, -30000000, -300, -29999998,
    -29999997, -229995392, 65631, -29999994, 131163, (s32)evt_snd_sfxoff, -29999995, 131163,
    (s32)evt_audience_delete, -30000000, 2, 33, 131096, -30000000, 53, 196699,
    (s32)evt_audience_flag_on, -30000000, 4, 107, 131122, -29999996, 0, 65541,
    45, 131125, -29999996, 2, 327771, (s32)evt_audience_set_rotate, -30000000, -29999996,
    0, 0, 65545, 1, 6, 109, 327771, (s32)evt_audience_get_position,
    -30000000, -29999999, -29999998, -29999997, 262235, (s32)btlevtcmd_GetStageAudienceAreaSize, -250000000, -29999998,
    -250000000, 131125, -29999997, 40, 131125, -29999998, 1, 458843,
    (s32)evt_audience_jump_position_firstsp, -30000000, -29999999, -29999998, -29999997, 60, -229998976, 327771,
    (s32)evt_audience_set_rotate, -30000000, 90, 0, 0, 65545, 30, 327771,
    (s32)evt_audience_set_rotate, -30000000, 0, 0, 0, 327771, (s32)evt_audience_set_rotate_offset, -30000000,
    0, 0, 0, 131122, -29999999, 90, 65541, 90,
    131126, -29999999, 1, 327771, (s32)evt_audience_set_rotate, -30000000, -29999999, 0,
    0, 65545, 1, 6, 327771, (s32)evt_audience_set_rotate, -30000000, 0,
    0, 0, 262235, (s32)evt_audience_set_animpose, -30000000, 7, 0, 65545,
    10, 327771, (s32)evt_audience_get_position, -30000000, -29999999, -29999998, -29999997, 393307,
    (s32)evt_snd_sfxon_3d, (s32)"SFX_AUDIENCE_PANIC_SCREAM3", -29999999, -29999998, -29999997, 0, 393307, (s32)evt_snd_sfxon_3d,
    (s32)"SFX_AUDIENCE_PANIC_RUN2", -29999999, -29999998, -29999997, -29999995, 65647, -29999994, 65541,
    1000, 327771, (s32)evt_audience_get_position, -30000000, -29999999, -29999998, -29999997, 327771,
    (s32)evt_snd_sfx_pos, -29999995, -29999999, -29999998, -29999997, 65545, 1, 6,
    112, 393307, (s32)evt_audience_move_position_speed, -30000000, -300, -29999998, -29999997, -229995392,
    65631, -29999994, 131163, (s32)evt_snd_sfxoff, -29999995, 131163, (s32)evt_audience_delete, -30000000,
    131163, (s32)evt_audience_num_updown_in_event, -230001024, 2, 33, 131163, (s32)evt_audience_delete, -30000000,
    131163, (s32)evt_audience_num_updown_in_event, -230001024, 2, 1,
};

USER_FUNC(_wait_damage_event_end) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id;
    BattleUnit* unit;

    id = evtGetValue(event, *args++);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    if (unit == NULL) {
        return EVT_RETURN_DONE;
    }
    if (unit->damageEventId != 0 && evtCheckID(unit->damageEventId)) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

s32 gonbaba_damage_sub_event[] = {
    262235, (s32)btlevtcmd_CheckDamageCode, -2, 16777216, -30000000, 131097, -30000000, 0,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131098, -30000000, 20,
    131125, -30000000, 1, 33, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0,
    -30000000, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -30000000, 131099, -30000000,
    -2, 131126, -30000000, 1, 33, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    1, -30000000, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table_weak, 33,
    196699, (s32)btlevtcmd_GetDamage, -29999990, -30000000, 131096, -30000000, 0, 262235,
    (s32)btlevtcmd_CheckDamageCode, -2, 16777216, -30000000, 131096, -30000000, 0, 65540,
    90, 33, 33, 196699, (s32)btlevtcmd_GetDamagePartsId, -2, -29999989, 131096,
    -29999989, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999990, 1, (s32)"GNB_D_2", 32,
    262235, (s32)btlevtcmd_AnimeChangePose, -29999990, 1, (s32)"GNB_D_1", 262235, (s32)btlevtcmd_GetUnitWork, -2,
    4, -30000000, 131122, -29999991, -30000000, 131101, -30000000, 1,
    131126, -30000000, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 4, -30000000,
    107, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131126,
    -30000000, 350, 131125, -29999999, 20, 196699, (s32)evt_audience_entry, -29999991,
    0, 327771, (s32)evt_audience_set_position, -29999991, -30000000, -29999999, -29999998, 196699,
    (s32)evt_audience_flag_on, -29999991, 22, 262235, (s32)evt_audience_set_animpose, -29999991, 9, 0,
    262235, (s32)btlevtcmd_GetStageAudienceAreaSize, -250000000, -29999999, -250000000, 131126, -30000000, 50,
    458843, (s32)evt_audience_jump_position_firstsp, -29999991, -30000000, -29999999, -29999998, 60, -229998976,
    262235, (s32)evt_audience_set_animpose, -29999991, 7, 0, 327771, (s32)evt_audience_get_position, -29999991,
    -30000000, -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_AUDIENCE_RUN1", -30000000, -29999999,
    -29999998, -29999993, 393307, (s32)evt_audience_move_position_speed, -29999991, -300, -29999999, -29999998,
    -229995392, 131163, (s32)evt_snd_sfxoff, -29999993, 131163, (s32)evt_audience_delete, -29999991, 109,
    33, 262235, (s32)btlevtcmd_GetUnitWork, -2, 4, -30000000, 131122, -29999991,
    -30000000, 131101, -30000000, 1, 131126, -30000000, 1, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 4, -30000000, 107, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 131126, -30000000, 320, 131125, -29999999,
    30, 196699, (s32)evt_audience_entry, -29999991, 0, 327771, (s32)evt_audience_set_position, -29999991,
    -30000000, -29999999, -29999998, 196699, (s32)evt_audience_flag_on, -29999991, 22, 262235,
    (s32)evt_audience_set_animpose, -29999991, 9, 0, 262235, (s32)btlevtcmd_GetStageAudienceAreaSize, -250000000, -29999999,
    -250000000, 131126, -30000000, 10, 131125, -29999998, 30, 458843,
    (s32)evt_audience_jump_position_firstsp, -29999991, -30000000, -29999999, -29999998, 54, -229998976, 262235,
    (s32)evt_audience_set_animpose, -29999991, 7, 0, 327771, (s32)evt_audience_get_position, -29999991, -30000000,
    -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_AUDIENCE_RUN1", -30000000, -29999999, -29999998,
    -29999993, 393307, (s32)evt_audience_move_position_speed, -29999991, -300, -29999999, -29999998, -229995392,
    131163, (s32)evt_snd_sfxoff, -29999993, 131163, (s32)evt_audience_delete, -29999991, 109, 33,
    33, 65545, 30, 262235, (s32)btlevtcmd_CheckDamageCode, -2, 256, -30000000,
    131096, -30000000, 0, 2, 33, 262235, (s32)btlevtcmd_CheckDamageCode, -2,
    16777216, -30000000, 131096, -30000000, 0, 2, 33, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 3, -30000000, 131096, -30000000, 1, 65540,
    50, 33, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -30000000, 131101,
    -30000000, 2, 2, 33, 131096, -30000000, 1, 196699,
    (s32)btlevtcmd_GetHp, -2, -30000000, 131100, -30000000, 0, 2, 33,
    33, 65627, (s32)btlevtcmd_WaitAttackEnd, 196699, (s32)btlevtcmd_SetTalkPose, -2, (s32)"GNB_T_4", 196699,
    (s32)btlevtcmd_SetStayPose, -2, (s32)"GNB_S_4", 131163, (s32)evt_btl_camera_set_prilimit, 1, 65627, (s32)evt_btl_camera_wait_move_end,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -30000000, 65570, -30000000, 65572,
    0, 196699, (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1,
    93, 160, 536, 93, 123, 25, 20, 0,
    65545, 20, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 1, 327771,
    (s32)evt_msg_print, 2, (s32)"stg1_gon_21", 0, -2, 65572, 1, 196699,
    (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, 93, 160,
    536, 93, 123, 25, 20, 0, 65545, 20,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 2, 327771, (s32)evt_msg_print, 2,
    (s32)"stg1_gon_22", 0, -2, 49, 131163, (s32)evt_btl_camera_set_prilimit, 0, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 3, 196699,
    (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 2, 65539, 50, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 2, -30000000, 131101, -30000000, 3, 2, 33,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 3, 65627, (s32)btlevtcmd_WaitAttackEnd, 196699,
    (s32)btlevtcmd_SetTalkPose, -2, (s32)"GNB_T_4", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"GNB_S_4", 131163,
    (s32)evt_btl_camera_set_prilimit, 1, 65627, (s32)evt_btl_camera_wait_move_end, 196699, (s32)evt_btl_camera_set_mode, 1, 3,
    131122, -29999999, 160, 131122, -29999998, 536, 262235, (s32)btlevtcmd_GetStageAudienceAreaSize,
    -250000000, -29999995, -250000000, 131125, -29999999, -29999995, 262235, (s32)btlevtcmd_GetStageSize,
    -250000000, -250000000, -29999995, 131125, -29999998, -29999995, 131125, -29999998,
    80, 131122, -29999995, -29999999, 131126, -29999995, 37, 131122,
    -29999994, -29999998, 131126, -29999994, 511, 655451, (s32)evt_btl_camera_set_moveto, 1,
    93, -29999999, -29999998, 93, -29999995, -29999994, 20, 0,
    65545, 20, 327771, (s32)evt_msg_print, 2, (s32)"stg1_gon_31_04", 0, -2,
    131163, (s32)evt_btl_camera_set_prilimit, 0, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 3, 196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 2,
    65539, 90, 196699, (s32)btlevtcmd_GetDamagePartsId, -2, -30000000, 393307, (s32)btlevtcmd_GetHitPos,
    -2, -30000000, -30000000, -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_BTL_ATTACK_MISS2",
    -30000000, -29999999, -29999998, 0, 2, 1,
};

static s32 dead_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -30000000, 131096, -30000000, 0,
    65630, (s32)negotiation_event, 2, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"GNB_X_1", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GNB_DOWN1", -250000000, 0, -29999985,
    65627, (s32)btlevtcmd_WaitAttackEnd, 131163, (s32)evt_btl_camera_set_prilimit, 1, 65627, (s32)evt_btl_camera_wait_move_end, 196699,
    (s32)evt_btl_camera_set_mode, 1, 3, 131122, -29999999, 160, 131122, -29999998,
    536, 262235, (s32)btlevtcmd_GetStageAudienceAreaSize, -250000000, -29999995, -250000000, 131125, -29999999,
    -29999995, 262235, (s32)btlevtcmd_GetStageSize, -250000000, -250000000, -29999995, 131125, -29999998,
    -29999995, 131125, -29999998, 80, 131122, -29999995, -29999999, 131126,
    -29999995, 37, 131122, -29999994, -29999998, 131126, -29999994, 511,
    655451, (s32)evt_btl_camera_set_moveto, 1, 93, -29999999, -29999998, 93, -29999995,
    -29999994, 30, 0, 65546, 1500, 196699, (s32)btlevtcmd_SetTalkPose, -2,
    (s32)"GNB_X_1", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"GNB_X_1", 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 310,
    131125, -29999999, 60, 327771, (s32)evt_msg_toge, 2, 0, 0,
    0, 327771, (s32)evt_msg_print, 0, (s32)"stg1_gon_32", 0, 0, 196699,
    (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, -38, 33,
    1005, -38, 92, 13, 60, 0, 131163, (s32)evt_snd_sfxoff,
    -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GNB_DOWN2", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_D_3", 65545, 42, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_H_1", 65545, 1, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 131125, -30000000, 25, 327771,
    (s32)btlevtcmd_SetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"GNB_H_1", 107, 131122, -29999995, 100, 131122, -29999996,
    120, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, -29999995, 0, 65541,
    40, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, -29999996, 131126,
    -29999996, 3, 65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, 0, 109, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999796,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 300, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 90, -1, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BOSS_GNB_DOWN3", 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_H_2", 393307, (s32)evt_btl_camera_shake_h, 1, 8,
    0, 30, 13, 65545, 10, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"GNB_H_3", 196699, (s32)btlevtcmd_GetExp, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreExp,
    -30000000, 131101, -30000000, 1, 65541, -30000000, 6, 33,
    65545, 60, 196699, (s32)btlevtcmd_KillUnit, -2, 1, 131163, (s32)evt_btl_camera_set_prilimit,
    0, 2, 1,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_OnUnitFlag, -2, 16777216)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetTalkBodyId, -2, 1)
    CALL(evt_audience_delete, 13)
    CALL(evt_audience_entry, 13, 0)
    CALL(evt_audience_delete, 14)
    CALL(evt_audience_entry, 14, 0)
    CALL(evt_audience_delete, 32)
    CALL(evt_audience_entry, 32, 0)
    CALL(evt_audience_delete, 33)
    CALL(evt_audience_entry, 33, 0)
    CALL(evt_audience_delete, 34)
    CALL(evt_audience_entry, 34, 0)
    CALL(evt_audience_delete, 35)
    CALL(evt_audience_entry, 35, 0)
    CALL(evt_audience_delete, 53)
    CALL(evt_audience_entry, 53, 0)
    CALL(evt_audience_delete, 54)
    CALL(evt_audience_entry, 54, 0)
    CALL(evt_audience_flag_on, 13, 512)
    CALL(evt_audience_flag_on, 14, 512)
    CALL(evt_audience_flag_on, 32, 512)
    CALL(evt_audience_flag_on, 33, 512)
    CALL(evt_audience_flag_on, 34, 512)
    CALL(evt_audience_flag_on, 35, 512)
    CALL(evt_audience_flag_on, 53, 512)
    CALL(evt_audience_flag_on, 54, 512)
    CALL(evt_audience_base_flag_on, 16384)
    CALL(btlevtcmd_SetEventEntry, -2, PTR(battle_entry_event))
    CALL(btlevtcmd_SetBaseScale, -2, FLOAT(1.2998047f), FLOAT(1.2998047f), FLOAT(0.5f))
    CALL(btlevtcmd_SetUnitWork, -2, 3, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 2, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 4, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 5, 0)
    CALL(btlevtcmd_StartWaitEvent, -2)
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
    CALL(btlevtcmd_GetUnitWork, -2, 5, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_SetUnitWork, -2, 5, 1)
        CALL_CHILD(PTR(firebreath_attack_event))
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetUnitWork, -2, 5, 2)
        CALL_CHILD(PTR(fumituke_attack_event))
        CASE_DEFAULT
        CALL(evt_sub_random, 99, LW(0))
        IF_INT_LESS(LW(0), 50)
            CALL_CHILD(PTR(fumituke_attack_event))
            ELSE
            CALL_CHILD(PTR(firebreath_attack_event))
        END_IF
    END_SWITCH
    RETURN
EVT_END()

static s32 fumituke_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_gonbaba_fumituke_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_gonbaba_fumituke_attack, -29999997, -29999996, 131096, -29999997,
    -1, 65540, 99, 33, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997,
    -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_gonbaba_fumituke_attack, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_W_2", 196699, (s32)btlevtcmd_ftomsec, 56, -30000000,
    65546, -30000000, 110, 589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_MOVE1", -250000000,
    0, -300, 0, -30, -250000000, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 131125, -30000000, -300, 131125, -29999998,
    -30, 262235, (s32)_leg_smoke_effect, -30000000, -29999999, -29999998, 112, 393307,
    (s32)evt_btl_camera_shake_h, 0, 2, 0, 10, 13, 196699, (s32)btlevtcmd_ftomsec,
    46, -30000000, 65546, -30000000, 110, 589915, (s32)btlevtcmd_snd_se_offset, -2,
    (s32)"SFX_BOSS_GNB_MOVE1", -250000000, 0, -300, 0, 30, -250000000, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -30000000, -300,
    131125, -29999998, 30, 262235, (s32)_leg_smoke_effect, -30000000, -29999999, -29999998,
    112, 393307, (s32)evt_btl_camera_shake_h, 0, 2, 0, 10, 13,
    196699, (s32)btlevtcmd_ftomsec, 1, -30000000, 65546, -30000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"GNB_A_3", 107, 589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_ARM_UP1",
    -250000000, 0, -320, 30, 30, -250000000, 196699, (s32)btlevtcmd_ftomsec,
    42, -30000000, 65546, -30000000, 589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_ARM_DOWN1",
    -250000000, 0, -360, 50, 30, -250000000, 109, 196699,
    (s32)btlevtcmd_ftomsec, 47, -30000000, 65546, -30000000, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, (s32)weapon_gonbaba_fumituke_attack, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 65540, 90, 65572, 1, 65540, 91,
    42, 65540, 97, 49, 65539, 90, 65540, 97,
    65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_gonbaba_fumituke_attack, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -29999997, -29999996, (s32)weapon_gonbaba_fumituke_attack, 256, -29999995, 65540, 97,
    65539, 97, 110, 589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_MOVE1", -250000000,
    0, -400, 0, -5, -250000000, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 131125, -30000000, -400, 131125, -29999998,
    -5, 262235, (s32)_leg_smoke_effect, -30000000, -29999999, -29999998, 112, 65545,
    3, 393307, (s32)evt_btl_camera_shake_h, 0, 5, 0, 10, 13,
    65545, 7, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_gonbaba_fumituke_attack, 393307, (s32)evt_btl_camera_shake_h, 0,
    8, 0, 30, 13, 65545, 35, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"GNB_W_3", 196699, (s32)btlevtcmd_ftomsec, 51, -30000000, 65546,
    -30000000, 110, 589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_MOVE1", -250000000, 0,
    -180, 0, 30, -250000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131125, -30000000, -180, 131125, -29999998, 30,
    262235, (s32)_leg_smoke_effect, -30000000, -29999999, -29999998, 112, 393307, (s32)evt_btl_camera_shake_h,
    0, 2, 0, 10, 13, 196699, (s32)btlevtcmd_ftomsec, 46,
    -30000000, 65546, -30000000, 110, 589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_MOVE1",
    -250000000, 0, -100, 0, 30, -250000000, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 131125, -30000000, -100, 131125,
    -29999998, -30, 262235, (s32)_leg_smoke_effect, -30000000, -29999999, -29999998, 112,
    393307, (s32)evt_btl_camera_shake_h, 0, 2, 0, 10, 13, 196699,
    (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 65539, 99, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

s32 firebreath_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_gonbaba_firebreath_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_gonbaba_firebreath_attack, -29999997, -29999996, 131096, -29999997,
    -1, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_gonbaba_firebreath_attack, 131163,
    (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_gonbaba_firebreath_attack,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_A_1", 131122, -29999990, 120,
    131122, -29999989, 30, 327771, (s32)btlevtcmd_GetPos, -2, -29999994, -29999993,
    -29999992, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -29999994, 360, 131125, -29999993,
    30, 327771, (s32)btlevtcmd_GetPos, -2, -29999991, -250000000, -250000000, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -2, -29999991, 360, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -29999991,
    -29999990, 107, 196699, (s32)btlevtcmd_ftomsec, 30, -30000000, 65546, -30000000,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GNB_NECK_UP1", -250000000, 0, -250000000, 109,
    107, 196699, (s32)btlevtcmd_ftomsec, 105, -30000000, 65546, -30000000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GNB_BREATH_FIRE1", -250000000, 0, -250000000, 131125, -29999989,
    45, 131126, -29999992, 10, 983131, (s32)evt_eff, 0, (s32)"gonbaba_breath\0",
    0, -29999994, -29999993, -29999992, -229996928, -29999989, 0, 0,
    0, 0, 0, 0, 109, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -29999988, -250000000, -250000000, 131126, -29999988, -29999994, 131098,
    -29999988, 0, 131127, -29999988, -1, 33, 131125, -29999988,
    20, 131127, -29999988, -29999989, 131128, -29999988, -29999990, 131125,
    -29999988, 105, 65545, -29999988, 131122, -29999990, 0, 65539,
    10, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_gonbaba_firebreath_attack, 256,
    -29999995, 65570, -29999995, 65579, 4, 65540, 90, 46,
    65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90,
    46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540,
    90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540,
    90, 65572, 1, 65540, 91, 46, 42, 65540,
    98, 46, 49, 65539, 90, 65540, 97, 65539,
    91, 131096, -29999990, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_gonbaba_firebreath_attack,
    33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_gonbaba_firebreath_attack, 256,
    -29999995, 65540, 97, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997,
    -29999996, 131097, -29999997, -1, 65545, 20, 131125, -29999990,
    1, 65540, 10, 33, 65545, 84, 65539, 99,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

