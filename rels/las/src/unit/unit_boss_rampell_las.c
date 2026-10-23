#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "manager/evtmgr_cmd.h"
#include "driver/effdrv.h"
#include "mario/mario_pouch.h"
#include "system.h"

USER_FUNC(btlevtcmd_AddRotate);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_AttackDeclare);
USER_FUNC(btlevtcmd_CalculateFaceDirection);
USER_FUNC(btlevtcmd_ChangeDataTable);
USER_FUNC(btlevtcmd_ChangeFaceDirection);
USER_FUNC(btlevtcmd_ChangeKind);
USER_FUNC(btlevtcmd_CheckActStatus);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_ChoiceSamplingEnemy);
USER_FUNC(btlevtcmd_ClearAllStatus);
USER_FUNC(btlevtcmd_DrawLots);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetHeight);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetOverTurnCount);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetStatusMg);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_GetWidth);
USER_FUNC(btlevtcmd_JumpPosition);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_OffStatusFlag);
USER_FUNC(btlevtcmd_OnUnitFlag);
USER_FUNC(btlevtcmd_PayWeaponCost);
USER_FUNC(btlevtcmd_PhaseEventStartDeclare);
USER_FUNC(btlevtcmd_PreCheckDamage);
USER_FUNC(btlevtcmd_ReplaceParts);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_ResultACDefence);
USER_FUNC(btlevtcmd_RunDataEventChild);
USER_FUNC(btlevtcmd_SamplingEnemy);
USER_FUNC(btlevtcmd_SetDiveSound);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetFallAccel);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetMoveSoundDataWork);
USER_FUNC(btlevtcmd_SetMoveSpeed);
USER_FUNC(btlevtcmd_SetOverTurnCount);
USER_FUNC(btlevtcmd_SetPartsDefenceTable);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRegistStatus);
USER_FUNC(btlevtcmd_SetRotate);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_SortPhaseMoveTable);
USER_FUNC(btlevtcmd_SpawnUnit);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(btlevtcmd_TransStageFloorPosition);
USER_FUNC(btlevtcmd_WaitGuardMove);
USER_FUNC(btlevtcmd_WeaponAftereffect);
USER_FUNC(evt_btl_camera_set_homing_unitparts);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveSpeedLv);
USER_FUNC(evt_btl_camera_set_moveto);
USER_FUNC(evt_btl_camera_set_zoom);
USER_FUNC(evt_eff64);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_sub_random);
USER_FUNC(mario_shadow_guard_check);
USER_FUNC(yoshi_original_color_anim_set);
static USER_FUNC(_krb_get_dir);
static USER_FUNC(vivian_comeback);
static USER_FUNC(eff_scanning);
extern s32 battle_evt_majo_disp_off[];
extern s32 battle_evt_majo_disp_on[];
extern s32 btl_majolyne_zoom_17_data_5C2D4[];
extern s32 btl_marilyn_zoom_17_data_5C2B8[];
extern s32 btl_vivian_zoom_17_data_5C29C[];
extern s32 btl_yoshi_yoroyoro_jump_calc_param[];
extern s32 btl_yoshi_yoroyoro_jump_move[];
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddScale[];
extern s32 btlevtcmd_AnimeSetMotionSpeed[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_GetFaceDirection[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetMoveFrame[];
extern s32 btlevtcmd_GetPosFloat[];
extern s32 btlevtcmd_GetResultAC[];
extern s32 btlevtcmd_GetRotate[];
extern s32 btlevtcmd_GetScale[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetTakeoffPosition[];
extern s32 btlevtcmd_GetUnitKind[];
extern s32 btlevtcmd_JumpContinue[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MarioJumpPosition[];
extern s32 btlevtcmd_MoveDirectionAdd[];
extern s32 btlevtcmd_OnStatusFlag[];
extern s32 btlevtcmd_SetDispOffset[];
extern s32 btlevtcmd_SetRGB[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SetScale[];
extern s32 btlevtcmd_SetStayPose[];
extern s32 btlevtcmd_SetStayPoseType[];
extern s32 btlevtcmd_SetTalkPose[];
extern s32 btlevtcmd_SetTalkPoseType[];
extern s32 btlevtcmd_WaitAttackEnd[];
extern s32 btlevtcmd_WaitEventEnd[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_posoffset[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_eff[];
extern s32 evt_sub_intpl_get_float[];
extern s32 evt_sub_intpl_get_value[];
extern s32 evt_sub_intpl_get_value_para[];
extern s32 evt_sub_intpl_init[];
extern s32 evt_sub_intpl_init_float[];
extern s32 evt_sub_intpl_msec_get_value_para[];
extern s32 evt_sub_intpl_msec_init[];
extern s32 majo_unison_phase_event_17_data_5C5E4[];
extern s32 pose_table_christine_stay[];
extern s32 pose_table_chuchurina_stay[];
extern s32 pose_table_clauda_stay[];
extern s32 pose_table_nokotarou_stay[];
extern s32 pose_table_nokotarou_turn[];
extern s32 pose_table_sanders_stay[];
extern s32 pose_table_vivian_stay[];
extern s32 pose_table_yoshi_stay[];
extern s32 subsetevt_confuse_flustered[];
extern s32 subsetevt_dead_core_nospin_norotate[];
extern s32 unit_boss_majolyne_las[];
extern s32 unit_boss_marilyn_las[];
extern s32 vivian_shadow_tail_event[];
extern s32 weaponGetPowerDefault[];
extern s32 weaponGetPowerFromGulliblePartyAttackLv[];

__declspec(section ".data") u64 fd_boss_rampell_las_negone_one_374;
__declspec(section ".data") s32 fd_boss_rampell_las_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_rampell_las___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_rampell_las___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_rampell_las_one_negone_373;
__declspec(section ".data") s32 fd_boss_rampell_las___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_rampell_las_one_381[1];
__declspec(section ".data") u64 fd_boss_rampell_las_negone_one_360;
__declspec(section ".data") s32 fd_boss_rampell_las_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_rampell_las___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_rampell_las___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_rampell_las_one_negone_359;
__declspec(section ".data") s32 fd_boss_rampell_las___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_rampell_las_one_364[1];
BattleUnitKind unit_boss_rampell_las;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static __declspec(section ".data") BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
static s32 weapon_rampell_attack[48];
static __declspec(section ".data") s32 entry_marilyn[12];
static __declspec(section ".data") s32 entry_majolyne[12];
s32 mutate_event[584];
static s32 init_event[198];
static s32 entry_event[46];
static s32 damage_event[22];
static s32 dead_event[261];
static s32 unison_phase_event[87];
static s32 phase_event[68];
static s32 attack_event[29];
static s32 ogg_attack_event[491];
static __declspec(section ".data") s32 wait_event[6];
static __declspec(section ".data") s32 defence_fmario[2];
static __declspec(section ".data") s32 defence_attr_fmario[2];
static __declspec(section ".data") s32 regist_fmario[6];
static PoseTableEntry pose_table_fmario_stay[15];
static __declspec(section ".data") s32 data_table_fmario[4];
static s32 parts_fmario[19];
static s32 weapon_masao_jump[48];
static s32 weapon_masao_hammer[48];
static s32 weapon_masao_kururin_jump[48];
static s32 weapon_masao_kaiten_hammer[48];
static s32 mario_zoom[19];
static s32 enemy_zoom[19];
static s32 fmario_zoom[19];
static s32 gparty_zoom[19];
static s32 init_event_fmario[70];
static s32 dead_event_fmario[80];
static s32 attack_event_fmario[52];
static s32 jump_attack_voice[36];
static s32 marioAttackEvent_NormalJump[344];
static s32 marioAttackEvent_KururinJump[469];
static s32 marioAttackEvent_NormalHammer[299];
static s32 marioAttackEvent_KaitenHammer[299];
static __declspec(section ".data") s32 wait_event_fmario[6];
static s32 enemyWeapon_ChristineNormalAttack[48];
static __declspec(section ".data") s32 defence_christine[2];
static __declspec(section ".data") s32 defence_attr_christine[2];
static __declspec(section ".data") s32 regist_christine[6];
static __declspec(section ".data") s32 data_table_christine[4];
static s32 parts_christine[19];
static s32 fmario_zoom_christine[19];
static s32 gparty_zoom_christine[19];
static s32 init_event_christine[72];
static s32 dead_event_christine[80];
static s32 attack_event_christine[690];
static __declspec(section ".data") s32 wait_event_christine[6];
static s32 enemyWeapon_NokotarouKouraAttack[48];
static s32 enemyWeapon_NokotarouShubibinAttack[48];
static __declspec(section ".data") s32 defence_nokotarou[2];
static __declspec(section ".data") s32 defence_attr_nokotarou[2];
static __declspec(section ".data") s32 defence_turn_nokotarou[2];
static __declspec(section ".data") s32 regist_nokotarou[6];
static __declspec(section ".data") s32 data_table_nokotarou[6];
static s32 parts_nokotarou[19];
static s32 dmg_turn_event[64];
static s32 wakeup_event[67];
static s32 init_event_nokotarou[92];
static __declspec(section ".data") s32 damage_event_nokotarou[6];
static s32 dead_event_nokotarou[80];
static s32 _change_koura_pose[34];
static s32 _change_koura_pose_fast[34];
static s32 _restore_koura_pose[47];
static s32 _koura_rotate_start[99];
static s32 _koura_rotate_stop[13];
static s32 attack_event_nokotarou[33];
static s32 attack_event_nokotarou_koura[393];
static s32 attack_event_nokotarou_shubibin[339];
static __declspec(section ".data") s32 wait_event_nokotarou[6];
static s32 enemyWeapon_ClaudaNormalAttack[48];
static __declspec(section ".data") s32 defence_clauda[2];
static __declspec(section ".data") s32 defence_attr_clauda[2];
static __declspec(section ".data") s32 regist_clauda[6];
static __declspec(section ".data") s32 data_table_clauda[4];
static s32 parts_clauda[19];
static s32 init_event_clauda[80];
static s32 dead_event_clauda[80];
static s32 attack_event_clauda[393];
static __declspec(section ".data") s32 wait_event_clauda[6];
static s32 enemyWeapon_YoshiNormalAttack[48];
static __declspec(section ".data") s32 defence_yoshi[2];
static __declspec(section ".data") s32 defence_attr_yoshi[2];
static __declspec(section ".data") s32 regist_yoshi[6];
static __declspec(section ".data") s32 data_table_yoshi[4];
static s32 parts_yoshi[19];
static s32 init_event_yoshi[54];
static s32 dead_event_yoshi[80];
static s32 attack_event_yoshi[748];
static __declspec(section ".data") s32 wait_event_yoshi[6];
__declspec(section ".data") s32 defence_vivian[2];
__declspec(section ".data") s32 defence_attr_vivian[2];
__declspec(section ".data") s32 regist_vivian[6];
__declspec(section ".data") s32 data_table_vivian[4];
s32 parts_vivian[19];
s32 weapon_vivian_kagenuke_attack[48];
static s32 vivian_down[19];
static s32 vivian_up[27];
s32 init_event_vivian[64];
s32 dead_event_vivian[80];
s32 attack_event_vivian[222];
__declspec(section ".data") s32 wait_event_vivian[6];
__declspec(section ".data") s32 defence_sanders[2];
__declspec(section ".data") s32 defence_attr_sanders[2];
__declspec(section ".data") s32 regist_sanders[6];
__declspec(section ".data") s32 data_table_sanders[4];
s32 parts_sanders[19];
s32 enemyWeapon_SandersNormalAttack[48];
s32 init_event_sanders[51];
s32 dead_event_sanders[80];
s32 attack_event_sanders[24];
s32 attack_event_sanders_normal[325];
__declspec(section ".data") s32 wait_event_sanders[6];
__declspec(section ".data") s32 defence_chuchurina[2];
__declspec(section ".data") s32 defence_attr_chuchurina[2];
__declspec(section ".data") s32 regist_chuchurina[6];
__declspec(section ".data") s32 data_table_chuchurina[4];
s32 parts_chuchurina[19];
s32 enemyWeapon_ChuchurinaNormalAttackR[48];
s32 enemyWeapon_ChuchurinaNormalAttackL[48];
s32 enemyWeapon_ChuchurinaNormalAttackRlast[48];
s32 enemyWeapon_ChuchurinaNormalAttackLlast[48];
s32 init_event_chuchurina[51];
s32 dead_event_chuchurina[80];
s32 attack_event_chuchurina[24];
s32 attack_event_chuchurina_normal[831];
__declspec(section ".data") s32 wait_event_chuchurina[6];

__declspec(section ".data") u64 fd_boss_rampell_las_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_rampell_las_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_rampell_las___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_rampell_las___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_rampell_las_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_rampell_las___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_rampell_las_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_rampell_las_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_rampell_las_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_rampell_las___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_rampell_las___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_rampell_las_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_rampell_las___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_rampell_las_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_rampell_las = {
    135,
    "btl_un_rampell",
    40,
    0,
    1,
    1,
    57,
    0,
    0,
    100,
    0,
    50,
    7,
    50,
    48,
    4,
    48,
    0.0f,
    22.0f,
    0.0f,
    0,
    -3,
    0.0f,
    40.0f,
    0.0f,
    25.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    0.0f,
    12.0f,
    32.0f,
    0.0f,
    7.0f,
    20.0f,
    0.0f,
    50.0f,
    48.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_RNPL_DAMAGED1",
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

static __declspec(section ".data") StatusVulnerability regist = {40, 50, 40, 100, 40, 100, 100, 30, 100, 60, 100, 60, 100, 80, 40, 0, 0, 100, 40, 100, 100, 5};

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
    {31, "S_1"},
    {39, "D_1"},
    {50, "A_2"},
    {42, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_rampell", "c_ranpel", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

static s32 weapon_rampell_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 69639, 6, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") s32 entry_marilyn[] = {
    (s32)unit_boss_marilyn_las, 16777216, 67108868, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

static __declspec(section ".data") s32 entry_majolyne[] = {
    (s32)unit_boss_majolyne_las, 16777216, 67108868, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

s32 mutate_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 12, -30000000, 65570, -30000000, 65572,
    0, 196699, (s32)evt_sub_random, 1, -29999995, 65572, 1, 131122,
    -29999995, 1, 42, 196699, (s32)btlevtcmd_GetUnitKind, -4, -29999998, 65570,
    -29999998, 65572, 224, 131122, -29999999, 2, 65572, 225,
    131122, -29999999, 3, 65572, 226, 131122, -29999999, 4,
    65572, 227, 131122, -29999999, 5, 65572, 228, 131122,
    -29999999, 6, 65572, 229, 131122, -29999999, 7, 65572,
    230, 131122, -29999999, 8, 49, 131096, -30000000, -29999999,
    131122, -29999995, 0, 32, 196699, (s32)evt_sub_random, 1, -29999995,
    33, 49, 262235, (s32)btlevtcmd_GetUnitWork, -2, 14, -30000000, 131097,
    -30000000, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 14, 0, 65631,
    -30000000, 33, 196699, (s32)evt_btl_camera_set_mode, 0, 3, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999990, -250000000, -250000000, 655451, (s32)evt_btl_camera_set_moveto, 0, -29999990,
    65, 332, -29999990, 30, -340, 30, 11, 65545,
    37, 262235, (s32)btlevtcmd_GetUnitWork, -2, 12, -30000000, 131096, -30000000,
    0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_RNPL_ARM_UP1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3A", 65546, 600, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_RNPL_ARM_UP1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"A_3A", 65546, 600, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_RNPL_ARM_UP1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_3A", 65546, 200, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_RNPL_LAUGH1", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3B", 65546,
    800, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_RNPL_EYE_SHINE1", -250000000, 0, -250000000,
    196699, (s32)btlevtcmd_GetStatusMg, -2, -29999994, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131124, -29999993, -230006144, 131132, -29999993, -29999994,
    131130, -30000000, -29999993, 131124, -29999993, -229966208, 131132, -29999993,
    -29999994, 131130, -29999999, -29999993, 983131, (s32)evt_eff, (s32)"", (s32)"toge_flush",
    3, -30000000, -29999999, -29999998, 60, 0, 0, 0,
    0, 0, 0, 0, 131124, -29999993, -229992832, 131132,
    -29999993, -29999994, 131130, -30000000, -29999993, 131124, -29999993, -230001024,
    131132, -29999993, -29999994, 131130, -29999999, -29999993, 983131, (s32)evt_eff,
    (s32)"", (s32)"toge_flush", 3, -30000000, -29999999, -29999998, 60, 0,
    0, 0, 0, 0, 0, 0, 65546, 1000,
    33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_RNPL_TRANSFORM4", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -29999998,
    5, 983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test", 7, -30000000, -29999999,
    -29999998, -229997952, 0, 0, 0, 0, 0, 0,
    0, 65546, 200, 327771, (s32)btlevtcmd_SetPos, -2, -1000, -1000,
    0, 65546, 500, 196699, (s32)evt_btl_camera_set_mode, 0, 3, 655451,
    (s32)evt_btl_camera_set_moveto, 0, -110, 65, 332, -110, 30, -340,
    30, 11, 65545, 37, 65570, -29999995, 65572, 0,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 12, 1, 327771, (s32)btlevtcmd_GetPos, -3,
    -30000000, -29999999, -29999998, 131125, -30000000, 2, 131125, -29999999,
    -5, 131125, -29999998, 5, 327771, (s32)eff_scanning, -3, -30000000,
    -29999999, -29999998, 393307, (s32)btlevtcmd_snd_se, -3, (s32)"SFX_BOSS_RNPL_TRANSFORM2", -250000000, 0,
    -250000000, 65546, 200, 393307, (s32)btlevtcmd_snd_se, -3, (s32)"SFX_BOSS_RNPL_TRANSFORM1", -250000000,
    0, -250000000, 65546, 1300, 393307, (s32)btlevtcmd_snd_se, -3, (s32)"SFX_BOSS_RNPL_TRANSFORM3",
    -250000000, 0, -250000000, 65546, 500, 196699, (s32)evt_btl_camera_set_mode, 0,
    3, 655451, (s32)evt_btl_camera_set_moveto, 0, -29999990, 65, 332, -29999990,
    30, -340, 30, 11, 65545, 37, 65630, (s32)init_event_fmario,
    65572, 1, 327771, (s32)btlevtcmd_GetPos, -4, -30000000, -29999999, -29999998,
    131125, -30000000, 2, 131125, -29999999, -5, 131125, -29999998,
    5, 327771, (s32)eff_scanning, -4, -30000000, -29999999, -29999998, 393307,
    (s32)btlevtcmd_snd_se, -3, (s32)"SFX_BOSS_RNPL_TRANSFORM2", -250000000, 0, -250000000, 65546, 200,
    393307, (s32)btlevtcmd_snd_se, -3, (s32)"SFX_BOSS_RNPL_TRANSFORM1", -250000000, 0, -250000000, 65546,
    1300, 393307, (s32)btlevtcmd_snd_se, -3, (s32)"SFX_BOSS_RNPL_TRANSFORM3", -250000000, 0, -250000000,
    65546, 500, 196699, (s32)evt_btl_camera_set_mode, 0, 3, 655451, (s32)evt_btl_camera_set_moveto,
    0, -29999990, 65, 332, -29999990, 30, -340, 30,
    11, 65545, 37, 196699, (s32)btlevtcmd_GetUnitKind, -4, -30000000, 65570,
    -30000000, 65572, 224, 262235, (s32)btlevtcmd_SetUnitWork, -2, 12, 2,
    65630, (s32)init_event_christine, 65572, 225, 262235, (s32)btlevtcmd_SetUnitWork, -2, 12,
    3, 65630, (s32)init_event_nokotarou, 65572, 226, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    12, 4, 65630, (s32)init_event_yoshi, 65572, 227, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 12, 5, 65630, (s32)init_event_clauda, 65572, 228, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 12, 6, 65630, (s32)init_event_vivian, 65572, 229,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 12, 7, 65630, (s32)init_event_sanders, 65572,
    230, 262235, (s32)btlevtcmd_SetUnitWork, -2, 12, 8, 65630, (s32)init_event_chuchurina,
    49, 49, 327771, (s32)btlevtcmd_GetHomePos, -2, -29999995, -29999994, -29999993,
    327771, (s32)evt_sub_intpl_msec_init, 11, -50, 0, 1000, 65541, 0,
    196699, (s32)evt_sub_intpl_msec_get_value_para, -30000000, -29999999, 327771, (s32)btlevtcmd_SetPos, -2, -29999995,
    -30000000, -29999993, 131096, -29999999, 0, 7, 33, 65545,
    1, 6, 196699, (s32)btlevtcmd_SetTalkPoseType, -2, 65, 196699, (s32)btlevtcmd_SetStayPoseType,
    -2, 43, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 2, 1,
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
    CALL(btlevtcmd_SetUnitWork, -2, 12, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 13, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 14, 0)
    CALL(btlevtcmd_GetUnitId, -2, GW(10))
    CALL(btlevtcmd_SpawnUnit, GW(9), PTR(entry_marilyn), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 55)
    ADD(LW(2), 10)
    CALL(btlevtcmd_SetPos, GW(9), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, GW(9), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetUnitWork, GW(9), 4, 1)
    CALL(btlevtcmd_SetUnitWork, GW(9), 5, 1)
    CALL(btlevtcmd_SetUnitWork, GW(9), 6, 0)
    CALL(btlevtcmd_SetUnitWork, GW(9), 7, 0)
    CALL(btlevtcmd_SpawnUnit, GW(8), PTR(entry_majolyne), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 110)
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
    SET_VALUE(GW(14), 8)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_BOSS_RNPL_MOVE1L"), STRING("SFX_BOSS_RNPL_MOVE1R"), 0, 15, 15)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_BOSS_RNPL_MOVE1L"), STRING("SFX_BOSS_RNPL_MOVE1R"), 0, 8, 8)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(entry_event)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    WAIT_FRAMES(60)
    WAIT_FRAMES(60)
    CALL_CHILD(PTR(btl_majolyne_zoom_17_data_5C2D4))
    CALL(evt_msg_print, 2, STRING("btl_majo3_00"), 0, GW(8))
    WAIT_MS(300)
    CALL_CHILD(PTR(btl_marilyn_zoom_17_data_5C2B8))
    CALL(evt_msg_print, 2, STRING("btl_majo3_01"), 0, GW(9))
    WAIT_MS(300)
    CALL_CHILD(PTR(btl_vivian_zoom_17_data_5C29C))
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

static s32 dead_event[] = {
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999997, -29999996, -29999995, 131122, -29999994, 1, 131096,
    -30000000, -29999997, 131096, -29999999, -29999996, 131096, -29999998, -29999995,
    131122, -29999994, 0, 33, 33, 33, 131096, -29999994,
    1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 40, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 33, 65627,
    (s32)btlevtcmd_WaitAttackEnd, 65545, 1, 196699, (s32)btlevtcmd_GetUnitKind, -2, -30000000, 131097,
    -30000000, 135, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    131125, -29999998, 5, 983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test", 7,
    -30000000, -29999999, -29999998, -229997952, 0, 0, 0, 0,
    0, 0, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_RNPL_TRANSFORM4", -250000000,
    0, -250000000, 65546, 300, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, -29999989,
    (s32)pose_table, 196699, (s32)btlevtcmd_ChangeDataTable, -2, (s32)data_table, 327771, (s32)btlevtcmd_ReplaceParts, -2,
    -29999989, (s32)parts, 1, 196699, (s32)btlevtcmd_ChangeKind, -2, 135, 196699,
    (s32)btlevtcmd_SetRegistStatus, -2, (s32)&regist, 196699, (s32)btlevtcmd_SetEventWait, -2, (s32)wait_event, 196699,
    (s32)btlevtcmd_OnUnitFlag, -2, 4, 131163, (s32)btlevtcmd_ClearAllStatus, -2, 33, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"D_2", 196699, (s32)btlevtcmd_SetTalkPose, -2, (s32)"D_2",
    196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"D_2", 65627, (s32)btlevtcmd_WaitAttackEnd, 65570, -49999989,
    65572, 0, 65570, -49999988, 65572, 0, 65572, 1,
    65541, 0, 131096, -49999988, 2, 7, 33, 65545,
    1, 6, 65540, 99, 65572, 2, 49, 65572,
    1, 65541, 0, 131096, -49999989, 2, 7, 33,
    65545, 1, 6, 65540, 99, 65572, 2, 65570,
    -49999988, 65572, 0, 65572, 1, 65541, 0, 131096,
    -49999988, 2, 7, 33, 65545, 1, 6, 65540,
    99, 65572, 2, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 65630, (s32)btl_vivian_zoom_17_data_5C29C,
    327771, (s32)evt_msg_print, 2, (s32)"btl_majo3_13", 0, -2, 131163, (s32)btlevtcmd_StatusWindowOnOff,
    1, 65540, 90, 49, 49, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0,
    65630, (s32)btl_vivian_zoom_17_data_5C29C, 327771, (s32)evt_msg_print, 2, (s32)"btl_majo3_10", 0, -2,
    131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 65539, 90, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 65539, 99, 131122, -49999987, 2, 131122, -29999990,
    -2, 65630, (s32)subsetevt_dead_core_nospin_norotate, 2, 1,
};

static EVT_BEGIN(unison_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108867)
    IF_INT_NOT_EQUAL(LW(0), 0)
        DEBUG_PUT_MSG(STRING("ランペル　ユニゾンフェーズ"))
        CALL_CHILD(PTR(majo_unison_phase_event_17_data_5C5E4))
        CALL(btlevtcmd_GetUnitWork, -2, 4, LW(3))
        CALL(btlevtcmd_GetUnitWork, -2, 5, LW(4))
        IF_INT_NOT_EQUAL(LW(3), LW(4))
            CALL(btlevtcmd_SetUnitWork, -2, 4, LW(4))
            CALL(btlevtcmd_StartWaitEvent, -2)
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
            CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SortPhaseMoveTable)
            CALL(btlevtcmd_StartWaitEvent, -2)
        END_IF
        DEBUG_PUT_MSG(STRING("ランペル　ユニゾンフェーズ終了"))
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108867)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckActStatus, -2, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetUnitWork, -2, 13, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL(mario_shadow_guard_check, LW(0))
                IF_INT_EQUAL(LW(0), 0)
                    CALL(btlevtcmd_GetUnitWork, -2, 12, LW(0))
                    IF_INT_EQUAL(LW(0), 0)
                        CALL(btlevtcmd_PhaseEventStartDeclare, -2)
                        CALL_CHILD(PTR(mutate_event))
                        CALL(btlevtcmd_StartWaitEvent, -2)
                        ELSE
                        CALL(evt_sub_random, 10, LW(0))
                        IF_INT_LESS(LW(0), 3)
                            CALL(btlevtcmd_PhaseEventStartDeclare, -2)
                            CALL_CHILD(PTR(mutate_event))
                            CALL(btlevtcmd_StartWaitEvent, -2)
                        END_IF
                    END_IF
                END_IF
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_SetUnitWork, -2, 13, 1)
    SET_VALUE(LW(9), PTR(weapon_rampell_attack))
    CALL_CHILD(PTR(ogg_attack_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 ogg_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 8,
    262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"R_1", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 20, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229997952, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A", 65546,
    250, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B", 65546, 500,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2", 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 131125, -30000000, 120, 131125,
    -29999999, 70, 262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229997952, 110,
    65545, 10, 262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229998464, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_RNPL_FLY1", -250000000, 0, -250000000, 65545, 15,
    262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229998976, 112, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 50, 7, 4, 0,
    -1, 262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229999232, 65546, 200,
    110, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 15, 0, 327771,
    (s32)evt_sub_intpl_msec_init, 1, 0, 135, 200, 65541, 0, 196699,
    (s32)evt_sub_intpl_msec_get_value_para, -30000000, -29999999, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    -30000000, 131096, -29999999, 0, 7, 33, 65545, 1,
    6, 112, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_RNPL_FALL1", -250000000, 0,
    -250000000, 65546, 80, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998,
    1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 262235, (s32)btlevtcmd_AnimeSetMotionSpeed,
    -2, 1, -229997952, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999990, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 15, -1, 458843,
    (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995, 65570,
    -29999995, 65579, 4, 65540, 90, 46, 65572, 3,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572,
    6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572,
    1, 65540, 91, 46, 42, 65540, 98, 46,
    49, 65539, 90, 131163, (s32)btlevtcmd_JumpContinue, -2, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_RNPL_DOWN1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, 0, 262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229997952,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"D_2", 65546, 200, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"O_1", 65546, 800, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"R_2", 65540, 98, 65539, 91, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229998976,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229997952, 110, 327771, (s32)btlevtcmd_SetRotateOffset,
    -2, 0, 15, 0, 327771, (s32)evt_sub_intpl_init, 4, 135,
    0, 20, 65541, 0, 196699, (s32)evt_sub_intpl_get_value_para, -30000000, -29999999,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, -30000000, 131096, -29999999,
    0, 7, 33, 65545, 1, 6, 112, 262235,
    (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229998976, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"J_1B", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125,
    -30000000, 60, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999232, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, 0, -29999998, 20, -1, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_RNPL_LANDING1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"A_1A", 65546, 200, 262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1,
    -229997952, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"R_1", 65539, 98,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 0, 262235,
    (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229998976, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"S_1", 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static __declspec(section ".data") s32 defence_fmario[] = {
    0, 0,
};

static __declspec(section ".data") s32 defence_attr_fmario[] = {
    0, 0,
};

static __declspec(section ".data") s32 regist_fmario[] = {
    674375780, 677667870, 1681679420, 1682974720, 6563940, 1678049280,
};

static PoseTableEntry pose_table_fmario_stay[] = {
    {1, "EM_N_1"},
    {2, "EM_Y_2"},
    {9, "EM_Y_2"},
    {5, "EM_K_1"},
    {4, "EM_K_1"},
    {3, "EM_K_1"},
    {28, "EM_S_1"},
    {39, "EM_D_1"},
    {50, "EM_A_1"},
    {42, "EM_R_1"},
    {40, "EM_W_1"},
    {56, "EM_D_3"},
    {57, "EM_D_3"},
    {65, "EM_T_1"},
    {69, "EM_S_1"},
};

static __declspec(section ".data") s32 data_table_fmario[] = {
    49, (s32)dead_event_fmario, 0, 0,
};

static s32 parts_fmario[] = {
    1, (s32)"btl_un_rampell", (s32)"c_mario", 0, 0, 0, 1077936128, 1104674816,
    0, 0, 1106247680, 0, 1310750, 16711680, (s32)defence_fmario, (s32)defence_attr_fmario,
    9, 0, (s32)pose_table_fmario_stay,
};

static s32 weapon_masao_jump[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, 0, 88071, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_masao_hammer[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553656320, 770, 0, 67591, 524, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_masao_kururin_jump[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, 0, 88071, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_masao_kaiten_hammer[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553656320, 770, 0, 67591, 524, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(mario_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, -110, 65, 332, -110, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(enemy_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 115, 65, 332, 115, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(fmario_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 90, 65, 332, 90, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(gparty_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 130, 65, 332, 130, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(init_event_fmario)
    CALL(btlevtcmd_AnimeSetPoseTable, -2, LW(11), PTR(pose_table_fmario_stay))
    CALL(btlevtcmd_ChangeDataTable, -2, PTR(data_table_fmario))
    CALL(btlevtcmd_ReplaceParts, -2, LW(11), PTR(parts_fmario), 1)
    CALL(btlevtcmd_ChangeKind, -2, 136)
    CALL(btlevtcmd_SetRegistStatus, -2, PTR(regist_fmario))
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_fmario))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_fmario))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_OnUnitFlag, -2, 4)
    CALL(btlevtcmd_ClearAllStatus, -2)
    SET_VALUE(GW(17), -1)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_BOSS_NM_MOVE1L"), STRING("SFX_BOSS_NM_MOVE1R"), 0, 20, 20)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_BOSS_NM_MOVE1L"), STRING("SFX_BOSS_NM_MOVE1R"), 0, 10, 10)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 dead_event_fmario[] = {
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999997, -29999996, -29999995, 131122, -29999994, 1, 131096,
    -30000000, -29999997, 131096, -29999999, -29999996, 131096, -29999998, -29999995,
    131122, -29999994, 0, 33, 33, 33, 131096, -29999994,
    1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 40, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 33, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_K_1", 65545, 152, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_NM_DOWN2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_D_2", 65546, 500, 65630, (s32)dead_event, 2, 1,
};

static EVT_BEGIN(attack_event_fmario)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    SWITCH(LW(0))
        CASE_EQUAL(0)
        SET_VALUE(LW(9), PTR(weapon_masao_jump))
        CALL_CHILD(PTR(marioAttackEvent_NormalJump))
        CASE_EQUAL(1)
        SET_VALUE(LW(9), PTR(weapon_masao_hammer))
        CALL_CHILD(PTR(marioAttackEvent_NormalHammer))
        CASE_EQUAL(2)
        SET_VALUE(LW(9), PTR(weapon_masao_kururin_jump))
        CALL_CHILD(PTR(marioAttackEvent_KururinJump))
        CASE_EQUAL(3)
        SET_VALUE(LW(9), PTR(weapon_masao_kaiten_hammer))
        CALL_CHILD(PTR(marioAttackEvent_KaitenHammer))
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 jump_attack_voice[] = {
    196699, (s32)evt_sub_random, 2, -29999985, 65570, -29999985, 65572, 0,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_VOICE_NM_AC1_1", -250000000, 0, -250000000, 65572,
    1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_VOICE_NM_AC1_2", -250000000, 0, -250000000,
    65572, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_VOICE_NM_AC1_5", -250000000, 0,
    -250000000, 49, 2, 1,
};

static s32 marioAttackEvent_NormalJump[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997, -1, 262235,
    (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0, 65630,
    (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts,
    0, -2, 1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition,
    -2, -29999997, -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -30000000, -29999998, 1, -29999994, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999994, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125, -29999998,
    5, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_J_1B", 65630, (s32)jump_attack_voice,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_JUMP1", -250000000, 0, -250000000, 524379,
    (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, 36, 0, -1,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90,
    65572, 1, 65540, 91, 46, 42, 65540, 98,
    46, 49, 65539, 90, 131163, (s32)btlevtcmd_JumpContinue, -2, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_DOWN1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_D_2", 65545, 40, 65540, 98, 65539,
    91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000,
    -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12, -1,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 8, -1, 65539, 98, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_W_1",
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 marioAttackEvent_KururinJump[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997, -1, 262235,
    (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0, 65630,
    (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts,
    0, -2, 1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition,
    -2, -29999997, -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -30000000, -29999998, 1, -29999994, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999994, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125, -29999998,
    5, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_J_1B", 65630, (s32)jump_attack_voice,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_JUMP1", -250000000, 0, -250000000, 524379,
    (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, 36, 0, -1,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90,
    65572, 1, 65540, 91, 46, 42, 65540, 98,
    46, 49, 65539, 90, 131163, (s32)btlevtcmd_JumpContinue, -2, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_DOWN1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_D_2", 65545, 40, 65540, 98, 65539,
    91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65647, -29999986, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999488, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 131125, -29999998, 5, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_J_1B", 65630, (s32)jump_attack_voice, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000,
    -29999999, -29999998, 36, 0, -1, 112, 65545, 15,
    65631, -29999986, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999985, 131127, -29999985,
    -30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_Z_2", 327771, (s32)btlevtcmd_SetRotateOffset,
    -2, 0, 12, 0, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 65545, 15, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_JUMP_KURURIN1",
    -250000000, 0, -250000000, 65541, 12, 327771, (s32)btlevtcmd_AddRotate, -2,
    0, 0, -29999985, 65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0,
    0, 0, 65545, 15, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, 4, 0, 0, 0, -1, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_J_1B", 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000, -29999999, -250000000, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 27, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 20, -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    8, -1, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 marioAttackEvent_NormalHammer[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 11,
    393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 100, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999999,
    -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 24, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229996928, 131125, -29999998, 5, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_A_1A", 65546, 66, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_NM_HAMMER_FURU2", -250000000, 0, -250000000, 65546, 233, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_A_1B", 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_A_1C", 65546, 50, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_HAMMER_DON2",
    -250000000, 0, -250000000, 65546, 100, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 49, 65539,
    90, 65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256,
    -29999995, 65539, 98, 65546, 700, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_S_1", 65546, 200, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};

static s32 marioAttackEvent_KaitenHammer[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 11,
    393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 100, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999999,
    -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 24, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229996928, 131125, -29999998, 5, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_A_1A", 65546, 66, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_NM_HAMMER_FURU2", -250000000, 0, -250000000, 65546, 233, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_A_1B", 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_A_1C", 65546, 50, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_HAMMER_DON2",
    -250000000, 0, -250000000, 65546, 100, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 49, 65539,
    90, 65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256,
    -29999995, 65539, 98, 65546, 700, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_S_1", 65546, 200, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event_fmario)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static s32 enemyWeapon_ChristineNormalAttack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerFromGulliblePartyAttackLv,
    1, 2, 3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, 0, 86039, 12, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") s32 defence_christine[] = {
    0, 0,
};

static __declspec(section ".data") s32 defence_attr_christine[] = {
    0, 0,
};

static __declspec(section ".data") s32 regist_christine[] = {
    674375780, 677667870, 1681679420, 1682974720, 6563940, 1678049280,
};

static __declspec(section ".data") s32 data_table_christine[] = {
    49, (s32)dead_event_christine, 0, 0,
};

static s32 parts_christine[] = {
    1, (s32)"btl_un_rampell", (s32)"c_pkr", 0, 0, 0, 1097859072, 1103626240,
    0, 0, 1106247680, 0, 1310750, 16711680, (s32)defence_christine, (s32)defence_attr_christine,
    9, 0, (s32)pose_table_christine_stay,
};

static EVT_BEGIN(fmario_zoom_christine)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 90, 58, 228, 90, 38, -20, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(gparty_zoom_christine)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 130, 58, 228, 130, 38, -20, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(init_event_christine)
    CALL(btlevtcmd_AnimeSetPoseTable, -2, LW(11), PTR(pose_table_christine_stay))
    CALL(btlevtcmd_ChangeDataTable, -2, PTR(data_table_christine))
    CALL(btlevtcmd_ReplaceParts, -2, LW(11), PTR(parts_christine), 1)
    CALL(btlevtcmd_ChangeKind, -2, 137)
    CALL(btlevtcmd_SetRegistStatus, -2, PTR(regist_christine))
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_christine))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_christine))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_OnUnitFlag, -2, 4)
    CALL(btlevtcmd_ClearAllStatus, -2)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 6, 12, 16)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 9, 3)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 dead_event_christine[] = {
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999997, -29999996, -29999995, 131122, -29999994, 1, 131096,
    -30000000, -29999997, 131096, -29999999, -29999996, 131096, -29999998, -29999995,
    131122, -29999994, 0, 33, 33, 33, 131096, -29999994,
    1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 40, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 33, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_DOWN3", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PKR_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1", -250000000,
    0, -250000000, 65546, 500, 65630, (s32)dead_event, 2, 1,
};

static s32 attack_event_christine[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 131122, -29999988,
    (s32)enemyWeapon_ChristineNormalAttack, 327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988,
    262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997, -29999996, 131096, -29999997, -1,
    65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235, (s32)btlevtcmd_AttackDeclare,
    -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2,
    -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition, -2, -29999997, -29999996, -30000000, -29999999,
    -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998, 1,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 458843, (s32)btlevtcmd_GetMoveFrame, -2,
    -30000000, -29999999, -29999998, 0, -29999986, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, -29999986, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 327771, (s32)btlevtcmd_DrawLots, -30000000, 2, 50, 50,
    65570, -30000000, 65572, 0, 131122, -29999989, 0, 65572,
    1, 196699, (s32)evt_sub_random, 4, -29999989, 131125, -29999989, 1,
    49, 131122, -29999990, 0, 65539, 10, 131101, -29999990,
    1, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988, 1048832,
    -29999995, 32, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988,
    256, -29999995, 33, 65570, -29999995, 65579, 2, 65579,
    3, 65579, 6, 65579, 4, 46, 65572, 1,
    42, 65546, 1000, 49, 131100, -29999990, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_A_2B", 65545, 20, 33, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_J_1A", 107, 65545, 15, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_KURI_ATTACK1", -250000000, 0, -250000000, 109, 327771,
    (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 131101, -29999990, -29999989,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125,
    -29999998, 5, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 14, 0,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 110, 65545,
    15, 65541, 6, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000, 131127,
    -30000000, -30, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, -30000000,
    65545, 1, 6, 112, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000,
    -29999999, -29999998, 36, 3, -1, 32, 327771, (s32)btlevtcmd_SetRotateOffset,
    -2, 0, 14, 0, 110, 327771, (s32)btlevtcmd_GetPosFloat, -2,
    -29999995, -29999994, -29999993, 131122, -29999992, 0, 65541, 36,
    327771, (s32)btlevtcmd_GetPosFloat, -2, -29999988, -29999987, -29999986, 393307, (s32)_krb_get_dir,
    -29999995, -29999994, -29999988, -29999987, -29999992, 327771, (s32)btlevtcmd_GetRotate, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetRotate, -2, -30000000, -29999999,
    -29999992, 131124, -29999995, -29999988, 131124, -29999994, -29999987, 65545,
    1, 6, 112, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 131125, -29999998, 5, 524379, (s32)btlevtcmd_MarioJumpPosition, -2,
    -30000000, -29999999, -29999998, 36, 0, -1, 33, 131097,
    -29999995, 1, 131096, -29999995, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 33, 131096, -29999995, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 33, 131096, -29999995, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 33, 131163, (s32)btlevtcmd_JumpContinue, -2, 327771, (s32)btlevtcmd_SetRotateOffset, -2,
    0, 0, 0, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_S_1", 196699, (s32)btlevtcmd_SetFallAccel,
    -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_MoveDirectionAdd, -2, -30000000, 30, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 20, -1, 262235, (s32)btlevtcmd_MoveDirectionAdd, -2,
    -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    10, -1, 65546, 500, 65540, 95, 33, 327771,
    (s32)btlevtcmd_SetScale, -2, -229998976, -229998976, -229998976, 65541, 4, 327771,
    (s32)btlevtcmd_AddScale, -2, -229999919, -230000122, 0, 65545, 1, 6,
    327771, (s32)btlevtcmd_SetScale, -2, -229998976, -229998976, -229998976, 107, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 0, 196699, (s32)evt_btl_camera_set_zoom, 0, -229833600, 65545,
    10, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 109, 131098, -29999990, -29999989, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 0,
    -29999995, 131125, -29999990, 1, 65540, 10, 32, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999988, 256, -29999995, 33, 65539, 90, 110, 327771,
    (s32)btlevtcmd_GetRotate, -2, -250000000, -250000000, -29999994, 131098, -29999994, 0,
    131127, -29999994, -1, 33, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000,
    131127, -29999994, -30000000, 131128, -29999994, 15, 131122, -29999993,
    15, 65539, 20, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0,
    -29999994, 131126, -29999993, 1, 65545, 1, 131101, -29999993,
    1, 65540, 20, 33, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 112, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -250000000, -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12,
    -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 8, -1, 65539, 95,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event_christine)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static s32 enemyWeapon_NokotarouKouraAttack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerFromGulliblePartyAttackLv,
    2, 3, 5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553664516, 525058, 0, 65671, 1535, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 enemyWeapon_NokotarouShubibinAttack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerFromGulliblePartyAttackLv,
    2, 3, 5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536887300, 525058, 0, 65671, 1535, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") s32 defence_nokotarou[] = {
    16843009, 16777216,
};

static __declspec(section ".data") s32 defence_attr_nokotarou[] = {
    0, 0,
};

static __declspec(section ".data") s32 defence_turn_nokotarou[] = {
    0, 0,
};

static __declspec(section ".data") s32 regist_nokotarou[] = {
    674375780, 677667870, 1681679420, 1684285440, 6563940, 1678049280,
};

static __declspec(section ".data") s32 data_table_nokotarou[] = {
    49, (s32)dead_event_nokotarou, 13, (s32)dmg_turn_event, 0, 0,
};

static s32 parts_nokotarou[] = {
    1, (s32)"btl_un_rampell", (s32)"c_pnk", 0, 0, 0, 1097859072, 1103626240,
    0, 0, 1106247680, 0, 1310750, 16711680, (s32)defence_nokotarou, (s32)defence_attr_nokotarou,
    4105, 0, (s32)pose_table_nokotarou_stay,
};

static s32 dmg_turn_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 262235, (s32)btlevtcmd_SetPartsDefenceTable,
    -29999990, -29999989, (s32)defence_turn_nokotarou, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table_nokotarou_turn,
    196699, (s32)btlevtcmd_OnStatusFlag, -29999990, 1, 196699, (s32)btlevtcmd_SetOverTurnCount, -29999990, 2,
    262235, (s32)btlevtcmd_AnimeChangePose, -29999990, -29999989, (s32)"PNK_D_1", 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_INSIDE1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229998976,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 12, -1, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 6, -1, 2, 1,
};

static EVT_BEGIN(wakeup_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetOverTurnCount, LW(10), LW(0))
    SUBTRACT(LW(0), 1)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(defence_nokotarou))
    CALL(btlevtcmd_OffStatusFlag, LW(10), 1)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_nokotarou_stay))
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("PNK_S_1"))
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(init_event_nokotarou)
    CALL(btlevtcmd_AnimeSetPoseTable, -2, LW(11), PTR(pose_table_nokotarou_stay))
    CALL(btlevtcmd_ChangeDataTable, -2, PTR(data_table_nokotarou))
    CALL(btlevtcmd_ReplaceParts, -2, LW(11), PTR(parts_nokotarou), 1)
    CALL(btlevtcmd_ChangeKind, -2, 138)
    CALL(btlevtcmd_SetRegistStatus, -2, PTR(regist_nokotarou))
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_nokotarou))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_nokotarou))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event_nokotarou))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_OnUnitFlag, -2, 4)
    CALL(btlevtcmd_ClearAllStatus, -2)
    CALL(btlevtcmd_SetUnitWork, -2, 8, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 9, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 10, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 11, 0)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 6, 12, 16)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 9, 3)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event_nokotarou)
    CALL_CHILD(PTR(_koura_rotate_stop))
    CALL_CHILD(PTR(damage_event))
    RETURN
EVT_END()

static s32 dead_event_nokotarou[] = {
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999997, -29999996, -29999995, 131122, -29999994, 1, 131096,
    -30000000, -29999997, 131096, -29999999, -29999996, 131096, -29999998, -29999995,
    131122, -29999994, 0, 33, 33, 33, 131096, -29999994,
    1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229993856, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 33, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_DOWN3", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PNK_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1", -250000000,
    0, -250000000, 65546, 500, 65630, (s32)dead_event, 2, 1,
};

static EVT_BEGIN(_change_koura_pose)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PNK_K_2"))
    LOOP(18)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, -2, 0, 15, 0)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PNK_K_1"))
    LOOP(6)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, -2, 0, 15, 0)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(_change_koura_pose_fast)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PNK_K_2"))
    LOOP(10)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, -2, 0, 27, 0)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PNK_K_1"))
    LOOP(3)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, -2, 0, 30, 0)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(_restore_koura_pose)
    CALL(btlevtcmd_SetUnitWork, -2, 8, 0)
    CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PNK_K_1"))
    LOOP(6)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, -2, 0, 45, 0)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PNK_K_2"))
    LOOP(6)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, -2, 0, 15, 0)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(_koura_rotate_start)
    CALL(btlevtcmd_SetUnitWork, -2, 8, 1)
    CALL(btlevtcmd_SetUnitWork, -2, 10, 0)
    BEGIN_INLINE_EVENT
        LABEL(0)
        CALL(btlevtcmd_GetUnitWork, -2, 8, LW(1))
        IF_INT_EQUAL(LW(1), 0)
            GOTO(10)
        END_IF
        CALL(btlevtcmd_GetUnitWork, -2, 10, LW(11))
        IF_INT_NOT_EQUAL(LW(11), 0)
            CALL(btlevtcmd_SetUnitWork, -2, 10, 0)
            CALL(btlevtcmd_GetUnitWork, -2, 9, LW(10))
            MULTIPLY(LW(10), -1)
            MULTIPLY(LW(0), -1)
            CALL(btlevtcmd_SetUnitWork, -2, 9, LW(10))
        END_IF
        CALL(btlevtcmd_GetUnitWork, -2, 9, LW(10))
        IF_INT_GREATER_OR_EQUAL(LW(10), 0)
            ADD(LW(0), 1)
            IF_INT_GREATER(LW(0), LW(10))
                SET_VALUE(LW(0), LW(10))
            END_IF
            ELSE
            SUBTRACT(LW(0), 1)
            IF_INT_LESS(LW(0), LW(10))
                SET_VALUE(LW(0), LW(10))
            END_IF
        END_IF
        CALL(btlevtcmd_AddRotate, -2, 0, LW(0), 0)
        WAIT_FRAMES(1)
        GOTO(0)
        LABEL(10)
    END_INLINE_EVENT
    RETURN
EVT_END()

static EVT_BEGIN(_koura_rotate_stop)
    CALL(btlevtcmd_SetUnitWork, -2, 8, 0)
    CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event_nokotarou)
    CALL(btlevtcmd_GetOverTurnCount, -2, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(wakeup_event))
        RETURN
    END_IF
    CALL(btlevtcmd_DrawLots, LW(0), 2, 50, 50)
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL_CHILD(PTR(attack_event_nokotarou_koura))
        CASE_EQUAL(1)
        CALL_CHILD(PTR(attack_event_nokotarou_shubibin))
    END_SWITCH
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 attack_event_nokotarou_koura[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 131122, -29999988,
    (s32)enemyWeapon_NokotarouKouraAttack, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2,
    -30000000, -29999988, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997, -29999996, 131096,
    -29999997, -1, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699,
    (s32)evt_btl_camera_set_mode, 0, 10, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1,
    -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom,
    0, 100, 65545, 20, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    65630, (s32)_change_koura_pose, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_NOKO_ATTACK1", -250000000, 0, -29999987, 131122, -30000000,
    15, 262235, (s32)btlevtcmd_SetUnitWork, -2, 9, 45, 65630, (s32)_koura_rotate_start,
    65545, 30, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988,
    256, -29999994, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 4, 196699, (s32)evt_btl_camera_set_zoom,
    0, 400, 65545, 30, 131163, (s32)evt_snd_sfxoff, -29999987, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_NOKO_ATTACK2", -250000000, 0, -29999987, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 50, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229989760, 327771,
    (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999995, -29999998, 131125, -29999998, 5, 458843,
    (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998, 0, -29999987, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, -29999987, -1, 0,
    131097, -29999994, 1, 131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 33, 131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 33, 131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 33, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 40,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1,
    0, 65630, (s32)_koura_rotate_stop, 65630, (s32)_restore_koura_pose, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 43, 65545, 30, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, 0, -1, 0, 65540, 99, 33, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999988, 256, -29999995, 65539, 90, 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    30, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 18,
    -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 8, -1, 65630,
    (s32)_restore_koura_pose, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 65545, 30,
    65539, 95, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2,
    1,
};

static s32 attack_event_nokotarou_shubibin[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 131122, -29999988,
    (s32)enemyWeapon_NokotarouShubibinAttack, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2,
    -30000000, -29999988, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997, -29999996, 131096,
    -29999997, -1, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988,
    131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2,
    -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    10, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 100,
    65545, 20, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65630, (s32)_change_koura_pose,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BTL_NOKO_SHUBIBIN1", -250000000, 0, -29999987, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5,
    0, 131122, -30000000, 15, 262235, (s32)btlevtcmd_SetUnitWork, -2, 9,
    45, 65630, (s32)_koura_rotate_start, 65546, 500, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    4, 196699, (s32)evt_btl_camera_set_zoom, 0, 400, 65546, 500, 65631,
    -29999985, 131163, (s32)evt_snd_sfxoff, -29999987, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_NOKO_SHUBIBIN2",
    -250000000, 0, -29999987, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 327771, (s32)evt_btl_camera_set_posoffset, 0, 0, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 131122, -29999990,
    0, 65539, 10, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229989760, 327771,
    (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999995, -29999998, 131125, -29999998, 5, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988, 256, -29999994,
    131097, -29999994, 1, 131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 33, 131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 33, 131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 33, 65540, 50, 33, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 0, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988,
    256, -29999995, 65539, 50, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996,
    131097, -29999997, -1, 131125, -29999990, 1, 65540, 10,
    33, 65539, 80, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998,
    524379, (s32)btlevtcmd_MovePosition, -2, -400, -29999999, -29999998, 0, -1,
    0, 65539, 90, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131127, -30000000, -1, 327771, (s32)btlevtcmd_SetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1,
    0, 65630, (s32)_koura_rotate_stop, 65630, (s32)_restore_koura_pose, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 43, 65545, 30, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event_nokotarou)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static s32 enemyWeapon_ClaudaNormalAttack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerFromGulliblePartyAttackLv,
    2, 4, 6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 656130, 0, 82055, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") s32 defence_clauda[] = {
    0, 0,
};

static __declspec(section ".data") s32 defence_attr_clauda[] = {
    0, 0,
};

static __declspec(section ".data") s32 regist_clauda[] = {
    674391140, 677667870, 1681679420, 1682974720, 6563940, 1678049280,
};

static __declspec(section ".data") s32 data_table_clauda[] = {
    49, (s32)dead_event_clauda, 0, 0,
};

static s32 parts_clauda[] = {
    1, (s32)"btl_un_rampell", (s32)"c_windy", 0, 0, 0, 1097859072, 1103626240,
    0, 0, 1106247680, 0, 1310750, 16711680, (s32)defence_clauda, (s32)defence_attr_clauda,
    9, 0, (s32)pose_table_clauda_stay,
};

static EVT_BEGIN(init_event_clauda)
    CALL(btlevtcmd_AnimeSetPoseTable, -2, LW(11), PTR(pose_table_clauda_stay))
    CALL(btlevtcmd_ChangeDataTable, -2, PTR(data_table_clauda))
    CALL(btlevtcmd_ReplaceParts, -2, LW(11), PTR(parts_clauda), 1)
    CALL(btlevtcmd_ChangeKind, -2, 140)
    CALL(btlevtcmd_SetRegistStatus, -2, PTR(regist_clauda))
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_clauda))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_clauda))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_OnUnitFlag, -2, 4)
    CALL(btlevtcmd_ClearAllStatus, -2)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 6, 12, 16)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 0, 9, 3)
    CALL(btlevtcmd_SetDiveSound, -2, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 0, 9, 3)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 dead_event_clauda[] = {
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999997, -29999996, -29999995, 131122, -29999994, 1, 131096,
    -30000000, -29999997, 131096, -29999999, -29999996, 131096, -29999998, -29999995,
    131122, -29999994, 0, 33, 33, 33, 131096, -29999994,
    1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 40, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 33, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_DOWN3", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PWD_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1", -250000000,
    0, -250000000, 65546, 500, 65630, (s32)dead_event, 2, 1,
};

static s32 attack_event_clauda[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 131122, -29999988,
    (s32)enemyWeapon_ClaudaNormalAttack, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2,
    -30000000, -29999988, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997, -29999996, 131096,
    -29999997, -1, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699,
    (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1,
    -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom,
    0, 200, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65546, 400,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A1_1", 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BTL_CLAUD_ATTACK1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999796,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125,
    -29999998, 5, 131163, (s32)btlevtcmd_GetResultAC, -29999995, 131103, -29999995, 2,
    196699, (s32)evt_sub_random, 40, -29999995, 131126, -29999995, 20, 131125,
    -30000000, -29999995, 196699, (s32)evt_sub_random, 20, -29999995, 131126, -29999995,
    10, 131125, -29999999, -29999995, 33, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 60, -1, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999988, 256, -29999994, 131097, -29999994, 1,
    131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33,
    131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33,
    131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A1_2", 131163, (s32)btlevtcmd_JumpContinue, -2,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_D_3", 65545, 30, 65540,
    95, 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CLAUD_ATTACK2", -250000000, 0,
    -250000000, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999988, 256, -29999995, 131163, (s32)btlevtcmd_JumpContinue, -2,
    393307, (s32)evt_btl_camera_shake_h, 0, 8, 0, 30, 13, 65647,
    -29999985, 327771, (s32)evt_sub_intpl_init_float, 11, -229998976, -229999591, 10, 65541,
    10, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -30000000, -29999995,
    -29999998, 65545, 1, 6, 327771, (s32)evt_sub_intpl_init_float, 11, -229999591,
    -229998976, 6, 65541, 6, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000,
    327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale,
    -2, -30000000, -29999995, -29999998, 65545, 1, 6, 112,
    110, 327771, (s32)evt_sub_intpl_init_float, 11, -229998976, -229998464, 10, 65541,
    10, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -29999995, -29999999,
    -29999998, 65545, 1, 6, 327771, (s32)evt_sub_intpl_init_float, 11, -229998464,
    -229998976, 6, 65541, 6, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000,
    327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale,
    -2, -29999995, -29999999, -29999998, 65545, 1, 6, 112,
    131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 65546, 700, 65539, 95, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 0, 65539,
    99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event_clauda)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static s32 enemyWeapon_YoshiNormalAttack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerFromGulliblePartyAttackLv,
    1, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, 0, 86167, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") s32 defence_yoshi[] = {
    0, 0,
};

static __declspec(section ".data") s32 defence_attr_yoshi[] = {
    0, 0,
};

static __declspec(section ".data") s32 regist_yoshi[] = {
    674375780, 677667870, 1681679420, 1682974720, 6563940, 1678049280,
};

static __declspec(section ".data") s32 data_table_yoshi[] = {
    49, (s32)dead_event_yoshi, 0, 0,
};

static s32 parts_yoshi[] = {
    1, (s32)"btl_un_rampell", (s32)"c_babyyoshi", 0, 0, 0, 1097859072, 1103626240,
    0, 0, 1106247680, 0, 1310750, 16711680, (s32)defence_yoshi, (s32)defence_attr_yoshi,
    9, 0, (s32)pose_table_yoshi_stay,
};

static EVT_BEGIN(init_event_yoshi)
    CALL(btlevtcmd_AnimeSetPoseTable, -2, LW(11), PTR(pose_table_yoshi_stay))
    CALL(btlevtcmd_ChangeDataTable, -2, PTR(data_table_yoshi))
    CALL(btlevtcmd_ReplaceParts, -2, LW(11), PTR(parts_yoshi), 1)
    CALL(btlevtcmd_ChangeKind, -2, 139)
    CALL(btlevtcmd_SetRegistStatus, -2, PTR(regist_yoshi))
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_yoshi))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_yoshi))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(yoshi_original_color_anim_set, -2)
    CALL(btlevtcmd_OnUnitFlag, -2, 4)
    CALL(btlevtcmd_ClearAllStatus, -2)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 dead_event_yoshi[] = {
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999997, -29999996, -29999995, 131122, -29999994, 1, 131096,
    -30000000, -29999997, 131096, -29999999, -29999996, 131096, -29999998, -29999995,
    131122, -29999994, 0, 33, 33, 33, 131096, -29999994,
    1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 40, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 33, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_DOWN3", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PYS_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1", -250000000,
    0, -250000000, 65546, 500, 65630, (s32)dead_event, 2, 1,
};

static s32 attack_event_yoshi[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 131122, -29999988,
    (s32)enemyWeapon_YoshiNormalAttack, 327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988,
    262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997, -29999996, 131096, -29999997, -1,
    65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235, (s32)btlevtcmd_AttackDeclare,
    -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2,
    -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 65545, 20,
    196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2,
    1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 350, 65644, -29999987, 65541, 0, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1L", -250000000, 0, -250000000, 65545, 2,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1R", -250000000, 0, -250000000, 65545,
    3, 6, 109, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_R_5",
    65545, 25, 65631, -29999987, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_J_1A", 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999693, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 25, 131125, -29999999, 35, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_JUMP1", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 25, -1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PYS_A_3", 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999994,
    -29999993, -29999992, 131125, -29999993, 40, 131122, -29999990, -229998976,
    65644, -29999987, 65541, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1L",
    -250000000, 190, -250000000, 65545, 6, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_PARTY_BATTLE_MOVE1R", -250000000, 381, -250000000, 65545, 7, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_PARTY_BATTLE_MOVE1L", -250000000, 668, -250000000, 65545, 6, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1R", -250000000, 859, -250000000, 65545, 7,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1L", -250000000, 1145, -250000000, 65545,
    6, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1R", -250000000, 1241, -250000000,
    65545, 7, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1L", -250000000, 1527,
    -250000000, 65545, 6, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1R", -250000000,
    1814, -250000000, 65545, 7, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1L",
    -250000000, 2100, -250000000, 65545, 6, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_PARTY_BATTLE_MOVE1R", -250000000, 2196, -250000000, 65545, 7, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_PARTY_BATTLE_MOVE1L", -250000000, 1742, -250000000, 65545, 6, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1R", -250000000, 1527, -250000000, 65545, 7,
    6, 109, 458843, (s32)btl_yoshi_yoroyoro_jump_calc_param, -2, -29999994, -29999993, -29999992,
    -29999990, -29999991, 458843, (s32)btl_yoshi_yoroyoro_jump_move, -2, -29999994, -29999993, -29999992,
    -29999990, -29999991, 65631, -29999987, 196699, (s32)evt_sub_random, 4, -29999989,
    131125, -29999989, 1, 131122, -29999990, 0, 65539, 10,
    131101, -29999990, 1, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    -29999988, 1048832, -29999995, 32, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, -29999988, 256, -29999995, 33, 65570, -29999995, 65579,
    2, 65579, 3, 65579, 6, 65579, 4, 46,
    65572, 1, 42, 49, 131100, -29999990, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_A_2B", 65545, 20, 33, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_J_1A", 131096, -29999990, 0, 196699,
    (s32)btlevtcmd_GetFaceDirection, -2, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_J_1B",
    131122, -30000000, 1, 131122, -29999999, 9, 131127, -29999985,
    -40, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 12, 0, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 65545, 15, 65541,
    -30000000, 131122, -29999998, -29999999, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_YOSHI_ATTACK1",
    -250000000, 0, -250000000, 65541, -29999998, 327771, (s32)btlevtcmd_AddRotate, -2,
    0, 0, -29999985, 65545, 1, 6, 6, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2,
    0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_1",
    65545, 15, 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_1",
    33, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 4, 0,
    0, 0, -1, 131097, -29999995, 1, 131096, -29999995,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33, 131096, -29999995,
    6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33, 131096, -29999995,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 131122, -29999985, -29999999, 262235,
    (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 131126, -29999985, -29999999, 131128,
    -29999985, 10, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    -29999985, 0, 0, 0, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PYS_D_1", 327771, (s32)btlevtcmd_SetDispOffset, -2, 0, -7, 0,
    393307, (s32)evt_btl_camera_shake_h, 0, 4, 0, 10, 13, 65545,
    40, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_5", 327771, (s32)btlevtcmd_SetDispOffset,
    -2, 0, 0, 0, 65545, 54, 65540, 95,
    33, 131098, -29999990, -29999989, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 0, -29999995,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetFallAccel,
    -2, -229999796, 131125, -29999999, 40, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 20, -1, 131125, -29999990, 1,
    65540, 10, 32, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 256, -29999995, 33,
    65539, 90, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000,
    -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_D_1", 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    25, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 16,
    -1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 65545, 20,
    65539, 95, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event_yoshi)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

__declspec(section ".data") s32 defence_vivian[] = {
    0, 0,
};

__declspec(section ".data") s32 defence_attr_vivian[] = {
    0, 0,
};

__declspec(section ".data") s32 regist_vivian[] = {
    674375780, 677667870, 1681679420, 1682974720, 6563940, 1678049280,
};

__declspec(section ".data") s32 data_table_vivian[] = {
    49, (s32)dead_event_vivian, 0, 0,
};

s32 parts_vivian[] = {
    1, (s32)"btl_un_rampell", (s32)"c_vivian", 0, 0, 0, 1097859072, 1103626240,
    0, 0, 1106247680, 0, 1310750, 16711680, (s32)defence_vivian, (s32)defence_attr_vivian,
    9, 0, (s32)pose_table_vivian_stay,
};

s32 weapon_vivian_kagenuke_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerFromGulliblePartyAttackLv,
    3, 4, 5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 82055, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
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

EVT_BEGIN(init_event_vivian)
    CALL(btlevtcmd_AnimeSetPoseTable, -2, LW(11), PTR(pose_table_vivian_stay))
    CALL(btlevtcmd_ChangeDataTable, -2, PTR(data_table_vivian))
    CALL(btlevtcmd_ReplaceParts, -2, LW(11), PTR(parts_vivian), 1)
    CALL(btlevtcmd_ChangeKind, -2, 141)
    CALL(btlevtcmd_SetRegistStatus, -2, PTR(regist_vivian))
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_vivian))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_vivian))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 3, 0)
    SPAWN_EVENT_GET_ID(PTR(vivian_shadow_tail_event), LW(0))
    CALL(btlevtcmd_SetUnitWork, -2, 14, LW(0))
    CALL(btlevtcmd_OnUnitFlag, -2, 4)
    CALL(btlevtcmd_ClearAllStatus, -2)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 dead_event_vivian[] = {
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999997, -29999996, -29999995, 131122, -29999994, 1, 131096,
    -30000000, -29999997, 131096, -29999999, -29999996, 131096, -29999998, -29999995,
    131122, -29999994, 0, 33, 33, 33, 131096, -29999994,
    1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 40, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 33, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_DOWN3", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PTR_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1", -250000000,
    0, -250000000, 65546, 500, 65630, (s32)dead_event, 2, 1,
};

s32 attack_event_vivian[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 131122, -29999991,
    (s32)weapon_vivian_kagenuke_attack, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2,
    -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096,
    -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097,
    -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0,
    -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom,
    0, 200, 65630, (s32)vivian_down, 65546, 300, 327771, (s32)btlevtcmd_GetPos,
    -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000,
    30, 131122, -29999999, 0, 65630, (s32)vivian_up, 65546, 300,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PTR_A2_2", 65546, 300, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_VIVI_ATTACK4", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 49,
    65539, 90, 65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65539, 98, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    43, 65630, (s32)vivian_down, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546,
    200, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 65630,
    (s32)vivian_up, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

__declspec(section ".data") EVT_BEGIN(wait_event_vivian)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

__declspec(section ".data") s32 defence_sanders[] = {
    0, 0,
};

__declspec(section ".data") s32 defence_attr_sanders[] = {
    0, 0,
};

__declspec(section ".data") s32 regist_sanders[] = {
    674375780, 677667940, 1681679420, 1682974720, 6563940, 1678049280,
};

__declspec(section ".data") s32 data_table_sanders[] = {
    49, (s32)dead_event_sanders, 0, 0,
};

s32 parts_sanders[] = {
    1, (s32)"btl_un_rampell", (s32)"c_bomt_n", 0, 0, 0, 1098907648, 1103101952,
    1084227584, 0, 1103101952, 0, 1310744, 16711680, (s32)defence_sanders, (s32)defence_attr_sanders,
    9, 0, (s32)pose_table_sanders_stay,
};

s32 enemyWeapon_SandersNormalAttack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerFromGulliblePartyAttackLv,
    4, 5, 6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 50332418, 0, 82055, 2043, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

EVT_BEGIN(init_event_sanders)
    CALL(btlevtcmd_AnimeSetPoseTable, -2, LW(11), PTR(pose_table_sanders_stay))
    CALL(btlevtcmd_ChangeDataTable, -2, PTR(data_table_sanders))
    CALL(btlevtcmd_ReplaceParts, -2, LW(11), PTR(parts_sanders), 1)
    CALL(btlevtcmd_ChangeKind, -2, 142)
    CALL(btlevtcmd_SetRegistStatus, -2, PTR(regist_sanders))
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_sanders))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_sanders))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_OnUnitFlag, -2, 4)
    CALL(btlevtcmd_ClearAllStatus, -2)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 dead_event_sanders[] = {
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999997, -29999996, -29999995, 131122, -29999994, 1, 131096,
    -30000000, -29999997, 131096, -29999999, -29999996, 131096, -29999998, -29999995,
    131122, -29999994, 0, 33, 33, 33, 131096, -29999994,
    1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 40, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 33, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_DOWN3", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1", -250000000,
    0, -250000000, 65546, 500, 65630, (s32)dead_event, 2, 1,
};

EVT_BEGIN(attack_event_sanders)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    SET_VALUE(LW(12), PTR(enemyWeapon_SandersNormalAttack))
    CALL_CHILD(PTR(attack_event_sanders_normal))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(attack_event_sanders_normal)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(12))
    CALL(btlevtcmd_RunDataEventChild, -2, 7)
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, -2, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(15))
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("R_2"))
    CALL(btlevtcmd_GetStatusMg, -2, LW(15))
    CALL(btlevtcmd_GetWidth, LW(3), LW(6))
    MULTIPLY_FLOAT(LW(6), LW(15))
    DIVIDE(LW(6), 2)
    MULTIPLY_FLOAT(LW(15), 20)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(15))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSoundDataWork, -2, STRING("SFX_BTL_THUNDERS_ATTACK1"), 0, 0, -1, -1, 0, 0)
    ADD(LW(2), 5)
    CALL(btlevtcmd_MovePosition, -2, LW(0), 0, LW(2), 90, -2, 1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK2"), LW(14))
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("A_3"))
    WAIT_FRAMES(60)
    CALL(evt_snd_sfxoff, LW(14))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK3"), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, -2, LW(6))
    DIVIDE(LW(6), 2)
    ADD(LW(1), LW(6))
    CALL(evt_eff64, STRING(""), STRING("bomb_n64"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_PreCheckDamage, -2, LW(3), LW(4), LW(12), 256, LW(6))
    IF_INT_NOT_EQUAL(LW(6), 1)
        IF_INT_EQUAL(LW(6), 3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
        END_IF
        IF_INT_EQUAL(LW(6), 6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
        END_IF
        IF_INT_EQUAL(LW(6), 2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_IF
        GOTO(92)
    END_IF
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(12), 256, LW(5))
    LABEL(92)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("J_1A"))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(30)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("J_1B"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.39941406f))
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 90, -1)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 40)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(wait_event_sanders)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

__declspec(section ".data") s32 defence_chuchurina[] = {
    0, 0,
};

__declspec(section ".data") s32 defence_attr_chuchurina[] = {
    0, 0,
};

__declspec(section ".data") s32 regist_chuchurina[] = {
    674375780, 677667870, 1681679420, 1682974720, 6563940, 1678049280,
};

__declspec(section ".data") s32 data_table_chuchurina[] = {
    49, (s32)dead_event_chuchurina, 0, 0,
};

s32 parts_chuchurina[] = {
    1, (s32)"btl_un_rampell", (s32)"c_tyutyu", 0, 0, 0, 1098907648, 1103101952,
    1084227584, 0, 1103101952, 0, 1310744, 16711680, (s32)defence_chuchurina, (s32)defence_attr_chuchurina,
    9, 0, (s32)pose_table_chuchurina_stay,
};

s32 enemyWeapon_ChuchurinaNormalAttackR[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 1442562, 0, 82119, 524, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 enemyWeapon_ChuchurinaNormalAttackL[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 1377026, 0, 82119, 524, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 enemyWeapon_ChuchurinaNormalAttackRlast[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerFromGulliblePartyAttackLv,
    2, 3, 4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 1573634, 0, 82119, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 enemyWeapon_ChuchurinaNormalAttackLlast[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerFromGulliblePartyAttackLv,
    2, 3, 4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 1508098, 0, 82119, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

EVT_BEGIN(init_event_chuchurina)
    CALL(btlevtcmd_AnimeSetPoseTable, -2, LW(11), PTR(pose_table_chuchurina_stay))
    CALL(btlevtcmd_ChangeDataTable, -2, PTR(data_table_chuchurina))
    CALL(btlevtcmd_ReplaceParts, -2, LW(11), PTR(parts_chuchurina), 1)
    CALL(btlevtcmd_ChangeKind, -2, 143)
    CALL(btlevtcmd_SetRegistStatus, -2, PTR(regist_chuchurina))
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_chuchurina))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_chuchurina))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_OnUnitFlag, -2, 4)
    CALL(btlevtcmd_ClearAllStatus, -2)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 dead_event_chuchurina[] = {
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999997, -29999996, -29999995, 131122, -29999994, 1, 131096,
    -30000000, -29999997, 131096, -29999999, -29999996, 131096, -29999998, -29999995,
    131122, -29999994, 0, 33, 33, 33, 131096, -29999994,
    1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 40, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 33, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_DOWN3", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PCH_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1", -250000000,
    0, -250000000, 65546, 500, 65630, (s32)dead_event, 2, 1,
};

EVT_BEGIN(attack_event_chuchurina)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    SET_VALUE(LW(12), PTR(enemyWeapon_ChuchurinaNormalAttackR))
    CALL_CHILD(PTR(attack_event_chuchurina_normal))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 attack_event_chuchurina_normal[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999988, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997, -29999996, 131096, -29999997,
    -1, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode,
    0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997,
    -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)btlevtcmd_GetStatusMg, -2,
    -29999995, 196699, (s32)btlevtcmd_GetWidth, -29999997, -29999994, 131132, -29999994, -29999995,
    131128, -29999994, 2, 131132, -29999995, 12, 327771, (s32)btlevtcmd_GetPos,
    -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, -29999995, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -29999997, -30000000, -29999994, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000,
    -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928,
    131125, -29999998, 5, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, 0, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 350,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_A1_1", 65647, -29999986, 131122,
    -29999994, 0, 131122, -29999995, 5, 65541, -29999995, 131125,
    -29999994, 1, 131122, -30000000, -29999994, 131128, -30000000, 2,
    131129, -30000000, 2, 131096, -30000000, 0, 327771, (s32)btlevtcmd_SetScale,
    -2, -229998925, -229998925, -229998976, 32, 327771, (s32)btlevtcmd_SetScale, -2,
    -229998976, -229998976, -229998976, 33, 65545, 1, 131122, -29999995,
    5, 6, 112, 65647, -29999985, 131122, -29999995, 5,
    131122, -30000000, 0, 65541, -29999995, 131125, -30000000, 10,
    131122, -29999999, 255, 131122, -29999998, 190, 131127, -29999998,
    -30000000, 131128, -29999998, 100, 131126, -29999999, -29999998, 393307,
    (s32)btlevtcmd_SetRGB, -2, 1, 255, -29999999, -29999999, 65545, 1,
    131122, -29999995, 5, 6, 112, 65546, 1000, 65631,
    -29999986, 65631, -29999985, 131122, -29999985, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 300, 393307, (s32)btlevtcmd_SetRGB,
    -2, 1, 255, 255, 255, 65647, -29999986, 131122,
    -29999992, -75, 327771, (s32)btlevtcmd_GetRotate, -2, -250000000, -30000000, -250000000,
    131101, -30000000, 180, 131126, -30000000, 360, 33, 327771,
    (s32)evt_sub_intpl_init, 5, -30000000, -29999992, 8, 65541, 8, 65627,
    (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, 0, -30000000, 0, 65545,
    1, 6, 131122, -29999992, -60, 131122, -29999991, -75,
    327771, (s32)evt_sub_intpl_init, 11, -29999991, -29999992, 4, 65541, 4,
    65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, 0, -30000000, 0,
    65545, 1, 6, 112, 131163, (s32)btlevtcmd_WaitEventEnd, -29999986, 196699,
    (s32)evt_sub_random, 2, -29999986, 131125, -29999986, 2, 131122, -29999987,
    18, 131122, -29999990, 0, 65539, 10, 131125, -29999990,
    1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_A1_2", 131101, -29999990,
    2, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988, 1048832,
    -29999994, 32, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988,
    256, -29999994, 33, 131097, -29999994, 1, 131096, -29999994,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33, 131096, -29999994,
    6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33, 131096, -29999994,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33, 65541, 20,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 18, 0, 65545, 1,
    6, 65541, 36, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 10,
    0, 65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_A2_4", 65545,
    52, 65540, 95, 33, 131122, -30000000, -29999990, 131129,
    -30000000, 2, 131097, -30000000, 0, 131122, -29999988, (s32)enemyWeapon_ChuchurinaNormalAttackR,
    131096, -29999990, -29999986, 131122, -29999988, (s32)enemyWeapon_ChuchurinaNormalAttackRlast, 33, 32,
    131122, -29999988, (s32)enemyWeapon_ChuchurinaNormalAttackL, 131096, -29999990, -29999986, 131122, -29999988,
    (s32)enemyWeapon_ChuchurinaNormalAttackLlast, 33, 33, 131097, -29999985, 0, 65631, -29999985,
    131122, -29999985, 0, 33, 131101, -29999990, -29999986, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CHUCHURINA_ATTACK3", -250000000, 0, -250000000, 32, 131122,
    -30000000, -29999990, 131149, -30000000, 1, 131096, -30000000, 0,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CHUCHURINA_ATTACK2", -250000000, 0, -250000000, 32,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CHUCHURINA_ATTACK1", -250000000, 0, -250000000, 33,
    33, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999988, 256, -29999995, 65570, -29999990, 65576,
    2, 65647, -29999985, 131122, -29999993, -29999987, 131101, -29999993,
    0, 131122, -29999992, 75, 32, 131122, -29999992, -75,
    33, 327771, (s32)btlevtcmd_GetRotate, -2, -250000000, -30000000, -250000000, 131101,
    -30000000, 180, 131126, -30000000, 360, 33, 327771, (s32)evt_sub_intpl_init,
    5, -30000000, -29999992, 14, 65541, 14, 65627, (s32)evt_sub_intpl_get_value,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, -30000000, 0, 65545, 1,
    6, 131098, -29999990, -29999986, 131122, -29999993, -29999987, 131101,
    -29999993, 0, 131122, -29999992, 60, 131122, -29999991, 75,
    32, 131122, -29999992, -60, 131122, -29999991, -75, 33,
    327771, (s32)evt_sub_intpl_init, 11, -29999991, -29999992, 6, 65541, 6,
    65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, 0, -30000000, 0,
    65545, 1, 6, 32, 131122, -29999993, -29999987, 131101,
    -29999993, 0, 131122, -29999992, 0, 131122, -29999991, 75,
    32, 131122, -29999992, 0, 131122, -29999991, -75, 33,
    327771, (s32)evt_sub_intpl_init, 11, -29999991, -29999992, 12, 65541, 12,
    65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, 0, -30000000, 0,
    65545, 1, 6, 33, 112, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985,
    42, 65647, -29999985, 327771, (s32)btlevtcmd_GetRotate, -2, -250000000, -29999992,
    -250000000, 131122, -29999993, 360, 131101, -29999990, -29999986, 131122,
    -30000000, -29999992, 131101, -29999992, 180, 131126, -30000000, 360,
    33, 131101, -29999987, 0, 131126, -29999993, -30000000, 32,
    131125, -29999993, -30000000, 33, 32, 131125, -29999993, 60,
    131122, -30000000, -29999992, 131101, -29999992, 180, 131126, -30000000,
    360, 33, 131101, -29999987, 0, 131126, -29999993, -30000000,
    32, 131125, -29999993, -30000000, 33, 33, 131098, -29999987,
    0, 131127, -29999993, -1, 33, 327771, (s32)evt_sub_intpl_init, 5,
    0, -29999993, 20, 65541, 20, 65627, (s32)evt_sub_intpl_get_value, 131125,
    -30000000, -29999992, 327771, (s32)btlevtcmd_SetRotate, -2, 0, -30000000, 0,
    65545, 1, 6, 112, 65545, 10, 49, 131127,
    -29999987, -1, 131098, -29999990, -29999986, 65540, 10, 33,
    65539, 95, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
};

__declspec(section ".data") EVT_BEGIN(wait_event_chuchurina)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

EffectEntry* effScanningEntry(s32 type, f32 x, f32 y, f32 z);

static USER_FUNC(eff_scanning) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    EffectEntry* eff = effScanningEntry(0, x, y, z);

    ((f32*)eff->userdata)[4] = unit->mSizeMultiplier;
    return EVT_RETURN_DONE;
}
BOOL BtlUnit_CheckShadowGuard(BattleUnit* unit);

USER_FUNC(mario_shadow_guard_check) {
    s32* args = event->args;

    if (BtlUnit_CheckShadowGuard(BattleGetMarioPtr(_battleWorkPointer)) == 1) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
static USER_FUNC(vivian_comeback) {
    pouchGetPtr()->partyData[6].flags &= ~2;
    return 1;
}
static USER_FUNC(_krb_get_dir) {
    s32* args = event->args;
    f32 x1 = evtGetFloat(event, args[0]);
    f32 z1 = evtGetFloat(event, args[1]);
    f32 x2 = evtGetFloat(event, args[2]);
    f32 z2 = evtGetFloat(event, args[3]);
    s32 dir = evtGetValue(event, args[4]);
    f32 dx = x2 - x1;
    f32 dz = z2 - z1;

    if (dx == 0.0f && dz == 0.0f) {
        evtSetValue(event, args[4], dir);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[4], angleABf(dx, dz, 0.0f, 0.0f));
    return EVT_RETURN_DONE;
}
