#include "battle/battle.h"
#include "battle/battle_database_common.h"
#include "battle/battle_stage.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "driver/msgdrv.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_party.h"
#include "system.h"
#include <string.h>

f32 BattleGetFloorHeight(BattleWork* wp, f32 x, f32 y, f32 z);
EffectEntry* effKumokumoN64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 arg5, f32 arg6, f32 scale);
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

USER_FUNC(_check_aud_item_type);
USER_FUNC(_clauda_make_extra_work_area);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeWaitPlayComplete);
USER_FUNC(btlevtcmd_AudienceAppeal);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetFaceDirection);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_OnUnitFlag);
USER_FUNC(btlevtcmd_RunDataEventChild);
USER_FUNC(btlevtcmd_SetDiveSound);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetMoveSoundDataWork);
USER_FUNC(btlevtcmd_SetMoveSpeed);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRotate);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_eff);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(_make_kumoguard_weapon);
USER_FUNC(_get_clauda_kiss_hit_position);
USER_FUNC(_make_kiss_weapon);
USER_FUNC(_make_breath_weapon);
static USER_FUNC(_clauda_breath_effect_fire);
static USER_FUNC(_clauda_breath_effect_ready);
USER_FUNC(_check_blow_rate);
static void __makeTechMenuFunc(BattleWorkCommand* command, s32* count);
extern s32 _attack_aud[];
extern s32 _get_attack_aud_no[];
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btldefaultevt_SuitoruBadgeEffect[];
extern s32 btldefaultevt_avoid_counter_event[];
extern s32 btlevtcmd_ACRGetResult[];
extern s32 btlevtcmd_ACRStart[];
extern s32 btlevtcmd_ACSuccessEffect[];
extern s32 btlevtcmd_AcGetDifficulty[];
extern s32 btlevtcmd_AcGetOutputParam[];
extern s32 btlevtcmd_AcSetDifficulty[];
extern s32 btlevtcmd_AcSetFlag[];
extern s32 btlevtcmd_AcSetGaugeParam[];
extern s32 btlevtcmd_AcSetParamAll[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_AudienceDeclareACResult[];
extern s32 btlevtcmd_AudienceDeclareAcrobatResult[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CommandCheckDamage[];
extern s32 btlevtcmd_CommandGetWeaponActionLv[];
extern s32 btlevtcmd_CommandGetWeaponAddress[];
extern s32 btlevtcmd_CommandPayWeaponCost[];
extern s32 btlevtcmd_CommandPreCheckCounter[];
extern s32 btlevtcmd_CommandPreCheckDamage[];
extern s32 btlevtcmd_DamageDirect[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_GetDamageCode[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetHeight[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHpDamage[];
extern s32 btlevtcmd_GetMoveFrame[];
extern s32 btlevtcmd_GetPartyTechLv[];
extern s32 btlevtcmd_GetRGB[];
extern s32 btlevtcmd_GetResultAC[];
extern s32 btlevtcmd_GetResultPrizeLv[];
extern s32 btlevtcmd_GetScale[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetStatusMg[];
extern s32 btlevtcmd_InviteApInfoReport[];
extern s32 btlevtcmd_JumpContinue[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MarioJumpParam[];
extern s32 btlevtcmd_MarioJumpPosition[];
extern s32 btlevtcmd_OffUnitFlag[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_RecoverHp[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultAC[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetDispOffset[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetRGB[];
extern s32 btlevtcmd_SetScale[];
extern s32 btlevtcmd_SetupAC[];
extern s32 btlevtcmd_StageDispellFog[];
extern s32 btlevtcmd_StartAC[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_StopAC[];
extern s32 btlevtcmd_TransStageFloorPosition[];
extern s32 btlevtcmd_WaitEventEnd[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_audience_acrobat_notry[];
extern s32 evt_audience_ap_recovery[];
extern s32 evt_btl_camera_nomove_x_onoff[];
extern s32 evt_btl_camera_nomove_y_onoff[];
extern s32 evt_btl_camera_nomove_z_onoff[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_homing_unit_audience[];
extern s32 evt_btl_camera_set_homing_unitparts[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_moveto[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_eff_delete_ptr[];
extern s32 evt_snd_sfxoff[];
extern s32 evt_sub_intpl_get_float[];
extern s32 evt_sub_intpl_init_float[];
extern s32 evt_sub_random[];
extern s32 subset_attack_ready_jump_event[];
extern s32 weaponGetACOutputParam[];
extern s32 weaponGetPowerFromPartyAttackLv[];

__declspec(section ".data") u64 lbl_80376320;
__declspec(section ".data") u64 fd_clauda_negone_one_374;
__declspec(section ".data") u64 lbl_80376330;
__declspec(section ".data") u64 fd_clauda_one_negone_373;
__declspec(section ".data") u64 lbl_80376340;
__declspec(section ".data") u64 fd_clauda_negone_one_360;
__declspec(section ".data") u64 lbl_80376350;
__declspec(section ".data") u64 fd_clauda_one_negone_359;
s32 partyWeapon_ClaudaNormalAttack[48];
s32 partyWeapon_ClaudaBreathAttack[48];
s32 partyWeapon_ClaudaPredationAttack[48];
s32 partyWeapon_ClaudaKumogakureAttack[48];
PoseTableEntry pose_table_clauda_stay[25];
static BattleDataEntry data_table[8];
BattleUnitKindPart unitpartsdata_Party_Clauda[1];
BattleUnitKind unitdata_Party_Clauda;
static s32 battle_entry_event[59];
static s32 init_event[60];
static s32 damage_event[16];
s32 partyClaudaAttack_NormalAttack[700];
s32 partyClaudaAttack_BreathAttack[520];
s32 partyClaudaAttack_PredationAttack[875];
s32 partyClaudaAttack_KumoGuard[290];
s32 clauda_appeal_event[71];
static s32 attack_audience_event[15];
s32 attack_bad_audience_event[348];
s32 attack_good_audience_event[216];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static s32 attack_event[2];
static s32 wait_event[6];
static s32 party_win_reaction[11];










__declspec(section ".data") u64 lbl_80376320 = 0xBF8000003F800000;

__declspec(section ".data") u64 fd_clauda_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") u64 lbl_80376330 = 0x3F800000BF800000;

__declspec(section ".data") u64 fd_clauda_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") u64 lbl_80376340 = 0xBF8000003F800000;

__declspec(section ".data") u64 fd_clauda_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") u64 lbl_80376350 = 0x3F800000BF800000;

__declspec(section ".data") u64 fd_clauda_one_negone_359 = 0x3F800000BF800000;

s32 partyWeapon_ClaudaNormalAttack[] = {
    (s32)"btl_wn_pwd_normal", 22020096, 0, (s32)"msg_pwd_body_press", 1677721600, 1065353216, 16868402, (s32)weaponGetPowerFromPartyAttackLv,
    1, 2, 2, 4, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536870912, 656130, (s32)"msg_ac_body_press", 217223, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyClaudaAttack_NormalAttack, 1315940, 336200197, 167772160,
};

s32 partyWeapon_ClaudaBreathAttack[] = {
    (s32)"btl_wn_pwd_lv1", 22085632, 0, (s32)"msg_pwd_breath", 1677983744, 1065353216, 17130546, 0,
    1, 2, 2, 3, 3, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 1639170, (s32)"msg_ac_breath", 131719, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 6553600, 0, 0, (s32)partyClaudaAttack_BreathAttack, 100, 328960, 0,
};

s32 partyWeapon_ClaudaPredationAttack[] = {
    (s32)"btl_wn_pwd_lv2", 22151168, 0, (s32)"msg_pwd_sexy_kiss", 1677918208, 1065353216, 33907762, (s32)weaponGetACOutputParam,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 3, 3, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, (s32)"msg_ac_sexy_kiss", 131271, 2, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyClaudaAttack_PredationAttack, 100, 1280, 0,
};

s32 partyWeapon_ClaudaKumogakureAttack[] = {
    (s32)"btl_wn_pwd_lv3", 22216704, 0, (s32)"msg_pwd_kumogakure", 1677983744, 1065353216, 17130546, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830240, 268435456, 770, (s32)"msg_ac_kumogakure", 131080, 2047, -2147475452,
    0, 0, 0, 6554112, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyClaudaAttack_KumoGuard, 100, 1280, 0,
};

PoseTableEntry pose_table_clauda_stay[] = {
    {9, "PWD_D_5"},
    {2, "PWD_D_5"},
    {3, "PWD_X_1"},
    {4, "PWD_D_2"},
    {5, "PWD_X_1"},
    {1, "PWD_N_1"},
    {27, "PWD_D_3"},
    {28, "PWD_S_1"},
    {37, "PWD_G_2"},
    {31, "PWD_G_1"},
    {39, "PWD_D_1"},
    {40, "PWD_W_1"},
    {42, "PWD_R_1"},
    {57, "PWD_D_2"},
    {56, "PWD_D_2"},
    {60, "PWD_D_3"},
    {61, "PWD_D_2"},
    {65, "PWD_T_1"},
    {52, "PWD_I_1"},
    {67, "PWD_C_1"},
    {66, "PWD_O_1"},
    {64, "PWD_X_1"},
    {49, "PWD_A4_3"},
    {45, "PWD_G_1"},
    {69, "PWD_S_1"},
};

static BattleDataEntry data_table[] = {
    {5, clauda_appeal_event},
    {6, attack_audience_event},
    {1, __makeTechMenuFunc},
    {48, btldefaultevt_Dummy},
    {64, party_win_reaction},
    {7, subset_attack_ready_jump_event},
    {47, btldefaultevt_avoid_counter_event},
    {0, NULL},
};

BattleUnitKindPart unitpartsdata_Party_Clauda[] = {
    {1, "btl_un_clauda", "c_windy", 0.0f, 0.0f, 0.0f, 16.0f, 44.0f, 5.0f, 0.0f, 44.0f, 0.0f, 26, 50, 255, &defence, &defence_attr, 0x9, 0, pose_table_clauda_stay},
};

BattleUnitKind unitdata_Party_Clauda = {
    227,
    "btl_un_clauda",
    10,
    5,
    5,
    1,
    1,
    0,
    0,
    0,
    0,
    100,
    9,
    20,
    50,
    16,
    44,
    0.0f,
    12.0f,
    0.0f,
    0,
    0,
    0.0f,
    40.0f,
    0.0f,
    0.0f,
    40.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    10.0f,
    0.0f,
    0.0f,
    10.0f,
    32.5f,
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
    "SFX_PARTY_DAMAGE1",
    "SFX_MARIO_DAMAGE_FIRE1",
    "SFX_MARIO_DAMAGE_ICE1",
    "SFX_MARIO_DAMAGE_BIRIBIRI1",
    0x2000004,
    &regist,
    1,
    unitpartsdata_Party_Clauda,
    init_event,
    data_table,
};

static EVT_BEGIN(battle_entry_event)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 250)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    WAIT_FRAMES(40)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 42)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(4.0f))
    CALL(btlevtcmd_SetMoveSoundDataWork, -2, STRING("SFX_PARTY_BATTLE_SUBHANG1"), STRING("SFX_PARTY_BATTLE_SUBHANG1"), 0, 9, 3, 0, 0)
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -2, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static EVT_BEGIN(init_event)
    CALL(_clauda_make_extra_work_area)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 6, 12, 16)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 0, 9, 8)
    CALL(btlevtcmd_SetDiveSound, -2, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 0, 9, 8)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_SetEventEntry, -2, PTR(battle_entry_event))
    CALL(btlevtcmd_OnUnitFlag, -2, 3145728)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

s32 partyClaudaAttack_NormalAttack[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 200,
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699,
    (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163, (s32)btlevtcmd_AcGetDifficulty, -30000000, 589915, (s32)btlevtcmd_AcSetParamAll,
    -29999997, -29999996, 180, -30000000, -250000000, -250000000, -250000000, -250000000,
    131163, (s32)btlevtcmd_AcSetFlag, 0, 327771, (s32)btlevtcmd_SetupAC, -2, 8, 1,
    0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 65545, 20,
    131163, (s32)btlevtcmd_StartAC, 1, 65627, (s32)btlevtcmd_ResultAC, 65627, (s32)btlevtcmd_StopAC, 196699,
    (s32)btlevtcmd_OffUnitFlag, -2, 2097152, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A1_1",
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CLAUD_ATTACK1", -250000000, 0, -250000000, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999796, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 131125, -29999998, 5, 131163, (s32)btlevtcmd_GetResultAC, -29999995,
    131103, -29999995, 2, 196699, (s32)evt_sub_random, 40, -29999995, 131126,
    -29999995, 20, 131125, -30000000, -29999995, 196699, (s32)evt_sub_random, 20,
    -29999995, 131126, -29999995, 10, 131125, -29999999, -29999995, 33,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 60, -1,
    196699, (s32)btlevtcmd_OnUnitFlag, -2, 2097152, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997,
    -29999996, 256, -29999995, 131097, -29999995, 1, 65540, 10,
    33, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102, -30000000, 2, 65540,
    20, 33, 131122, -29999995, 1, 65539, 10, 131097,
    -29999995, 1, 131096, -29999995, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 33, 131096, -29999995, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 33, 131096, -29999995, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 33, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A1_2",
    131163, (s32)btlevtcmd_JumpContinue, -2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_D_3",
    196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 65647, -29999985, 327771, (s32)evt_sub_intpl_init_float,
    11, -229998976, -229999591, 10, 65541, 10, 196699, (s32)evt_sub_intpl_get_float,
    -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_SetScale, -2, -30000000, -29999995, -29999998, 65545, 1,
    6, 327771, (s32)evt_sub_intpl_init_float, 11, -229999591, -229998976, 6, 65541,
    6, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -30000000, -29999995,
    -29999998, 65545, 1, 6, 112, 110, 327771, (s32)evt_sub_intpl_init_float,
    11, -229998976, -229998464, 10, 65541, 10, 196699, (s32)evt_sub_intpl_get_float,
    -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_SetScale, -2, -29999995, -29999999, -29999998, 65545, 1,
    6, 327771, (s32)evt_sub_intpl_init_float, 11, -229998464, -229998976, 6, 65541,
    6, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -29999995, -29999999,
    -29999998, 65545, 1, 6, 112, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985,
    65545, 30, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65540, 95,
    65539, 20, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CLAUD_ATT2", -250000000, 0,
    -250000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CLAUD_ATTACK2", -250000000, 0, -250000000,
    131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102, -30000000, 2, 393307, (s32)btlevtcmd_CommandCheckDamage,
    -2, -29999997, -29999996, 131328, -29999995, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997,
    0, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994, 32, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997,
    -29999996, 256, -29999995, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 33,
    131163, (s32)btlevtcmd_JumpContinue, -2, 65647, -29999986, 393307, (s32)btlevtcmd_ACRStart, -2,
    0, 16, 16, 20, 112, 393307, (s32)evt_btl_camera_shake_h, 0,
    8, 0, 30, 13, 65647, -29999985, 327771, (s32)evt_sub_intpl_init_float,
    11, -229998976, -229999591, 10, 65541, 10, 196699, (s32)evt_sub_intpl_get_float,
    -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_SetScale, -2, -30000000, -29999995, -29999998, 65545, 1,
    6, 327771, (s32)evt_sub_intpl_init_float, 11, -229999591, -229998976, 6, 65541,
    6, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -30000000, -29999995,
    -29999998, 65545, 1, 6, 112, 110, 327771, (s32)evt_sub_intpl_init_float,
    11, -229998976, -229998464, 10, 65541, 10, 196699, (s32)evt_sub_intpl_get_float,
    -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_SetScale, -2, -29999995, -29999999, -29999998, 65545, 1,
    6, 327771, (s32)evt_sub_intpl_init_float, 11, -229998464, -229998976, 6, 65541,
    6, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -29999995, -29999999,
    -29999998, 65545, 1, 6, 112, 131163, (s32)btlevtcmd_WaitEventEnd, -29999986,
    196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131097, -29999994, 2, 131163,
    (s32)btlevtcmd_WaitEventEnd, -29999985, 65627, (s32)evt_audience_acrobat_notry, 65540, 95, 33, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, 20, 131125, -29999999, 20, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, 0, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999693, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 18, -1, 393307,
    (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, -230061440, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PWD_Y_1", 65546, 500, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985,
    65539, 95, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 458843, (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998, -229993856,
    -29999985, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, -29999985,
    0, 4, 0, -1, 65539, 99, 65627, (s32)evt_audience_ap_recovery,
    65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 partyClaudaAttack_BreathAttack[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 65545, 20,
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -2, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    300, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000,
    131163, (s32)btlevtcmd_AcGetDifficulty, -29999999, 131126, -29999999, 3, 65570, -29999999,
    65576, -3, 131122, -30000000, 300, 65572, -2, 131122,
    -30000000, 300, 65572, -1, 131122, -30000000, 300, 65572,
    0, 131122, -30000000, 300, 65572, 1, 131122, -30000000,
    300, 65572, 2, 131122, -30000000, 300, 42, 131122,
    -30000000, 300, 49, 131163, (s32)btlevtcmd_AcGetDifficulty, -29999999, 589915, (s32)btlevtcmd_AcSetParamAll,
    1, -30000000, 4, 40, 60, 80, 100, -29999999,
    327771, (s32)btlevtcmd_SetupAC, -2, 14, 1, 0, 65627, (s32)_clauda_breath_effect_ready,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A2_1", 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BTL_CLAUD_BREATH1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A2_2", 196699, (s32)evt_btl_camera_nomove_x_onoff, 0,
    1, 196699, (s32)evt_btl_camera_nomove_y_onoff, 0, 1, 196699, (s32)evt_btl_camera_nomove_z_onoff, 0,
    1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    0, 196699, (s32)evt_btl_camera_nomove_x_onoff, 0, 0, 196699, (s32)evt_btl_camera_nomove_y_onoff, 0,
    0, 196699, (s32)evt_btl_camera_nomove_z_onoff, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PWD_A2_3", 107, 65546, 500, 65627, (s32)btlevtcmd_StageDispellFog, 109,
    131163, (s32)_clauda_breath_effect_fire, -29999987, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CLAUD_BREATH2", -250000000,
    0, -29999986, 65647, -29999985, 131122, -29999986, -1, 65539,
    5, 196699, (s32)btlevtcmd_AcGetOutputParam, 1, -30000000, 65545, 1, 65540,
    5, 112, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy,
    -2, -30000000, -29999988, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 65539,
    8, 131097, -29999997, -1, 196699, (s32)_check_blow_rate, -29999997, -30000000,
    131101, -30000000, 1, 458843, (s32)btlevtcmd_DamageDirect, -29999997, -29999996, 0,
    0, 3, 1, 33, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996,
    65540, 8, 33, 131163, (s32)btlevtcmd_StartAC, 1, 65627, (s32)btlevtcmd_ResultAC,
    65631, -29999985, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0,
    65627, (s32)btlevtcmd_StopAC, 131122, -29999989, 99, 131122, -29999988, (s32)partyWeapon_ClaudaBreathAttack,
    196699, (s32)btlevtcmd_AcGetOutputParam, 2, -30000000, 196699, (s32)_make_breath_weapon, -29999988, -30000000,
    65545, 60, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy,
    -2, -30000000, -29999988, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131122,
    -29999990, 0, 65539, 10, 327771, (s32)btlevtcmd_SetDispOffset, -29999997, 0,
    0, 0, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988,
    256, -29999994, 131097, -29999994, 1, 131096, -29999994, 3,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 51, 33, 131096,
    -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 51,
    33, 131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    65540, 51, 33, 65540, 50, 33, 131163, (s32)btlevtcmd_GetResultAC,
    -30000000, 131102, -30000000, 2, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999988, 131328, -29999995, 196699, (s32)btlevtcmd_GetDamageCode, -29999997, -30000000,
    131096, -30000000, 29, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988,
    -29999994, 33, 32, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999988, 256, -29999995, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 33,
    65539, 50, 65546, 300, 65539, 51, 131126, -29999989,
    1, 131101, -29999989, 1, 65539, 52, 196699, (s32)btlevtcmd_GetSelectNextEnemy,
    -29999997, -29999996, 131097, -29999997, -1, 131125, -29999990, 1,
    65540, 10, 33, 33, 65539, 80, 65546, 1500,
    65539, 90, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 131163, (s32)evt_snd_sfxoff, -29999986, 131163, (s32)evt_eff_delete_ptr, -29999987,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 393307, (s32)btlevtcmd_ACRStart, -2,
    0, 25, 25, 20, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993,
    131097, -29999994, 2, 65627, (s32)evt_audience_acrobat_notry, 65546, 500, 65540,
    99, 33, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_Y_1", 65546, 1000,
    65539, 99, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 partyClaudaAttack_PredationAttack[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 300,
    131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 196699,
    (s32)btlevtcmd_GetPartyTechLv, -2, -30000000, 65570, -30000000, 65572, 2, 131163,
    (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126, -30000000, 3, 65570, -30000000, 65576,
    -3, 131122, -30000000, 120, 131122, -29999999, 0, 65572,
    -2, 131122, -30000000, 100, 131122, -29999999, 0, 65572,
    -1, 131122, -30000000, 80, 131122, -29999999, 1, 65572,
    0, 131122, -30000000, 70, 131122, -29999999, 2, 65572,
    1, 131122, -30000000, 66, 131122, -29999999, 2, 65572,
    2, 131122, -30000000, 62, 131122, -29999999, 2, 42,
    131122, -30000000, 58, 131122, -29999999, 2, 49, 589915,
    (s32)btlevtcmd_AcSetParamAll, 0, -30000000, -29999999, 5, 3, -250000000, -250000000,
    -250000000, 327771, (s32)btlevtcmd_AcSetGaugeParam, 60, 80, 100, 100, 42,
    131163, (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126, -30000000, 3, 65570, -30000000,
    65576, -3, 131122, -30000000, 120, 131122, -29999999, 0,
    65572, -2, 131122, -30000000, 100, 131122, -29999999, 0,
    65572, -1, 131122, -30000000, 80, 131122, -29999999, 1,
    65572, 0, 131122, -30000000, 70, 131122, -29999999, 2,
    65572, 1, 131122, -30000000, 66, 131122, -29999999, 2,
    65572, 2, 131122, -30000000, 62, 131122, -29999999, 2,
    42, 131122, -30000000, 58, 131122, -29999999, 2, 49,
    589915, (s32)btlevtcmd_AcSetParamAll, 0, -30000000, -29999999, 3, 2, -250000000,
    -250000000, -250000000, 327771, (s32)btlevtcmd_AcSetGaugeParam, 34, 68, 100, 100,
    49, 131163, (s32)btlevtcmd_AcSetFlag, 0, 327771, (s32)btlevtcmd_SetupAC, -2, 17,
    1, 60, 65545, 22, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997,
    -29999996, 256, -29999995, 131096, -29999995, 5, 196699, (s32)btlevtcmd_GetStatusMg,
    -29999997, -29999994, 131132, -29999994, 40, 327771, (s32)btlevtcmd_GetPos, -29999997,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, -29999994, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229996928, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    40, 0, 5, 0, -1, 393307, (s32)btlevtcmd_CommandCheckDamage, -2,
    -29999997, -29999996, 256, -29999995, 33, 458843, (s32)_get_clauda_kiss_hit_position, -2,
    -29999997, -29999996, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_GetStatusMg, -2,
    -29999994, 131132, -29999994, 20, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000,
    -29999994, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998, 1,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 131125, -29999998, 5,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 40, 0,
    5, 0, -1, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A3_1", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1,
    393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256, -29999995, 65570,
    -29999995, 65579, 2, 65579, 3, 65579, 6, 65579,
    4, 46, 65572, 1, 42, 49, 131097, -29999995,
    1, 131096, -29999995, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    33, 131096, -29999995, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    33, 131096, -29999995, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A3_2", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete,
    -2, 1, 65540, 90, 33, 393307, (s32)btlevtcmd_CommandPreCheckCounter, -2,
    -29999997, -29999996, 256, -30000000, 65570, -30000000, 65579, 7,
    65579, 8, 65579, 9, 65579, 10, 65579, 11,
    65579, 12, 65579, 13, 65579, 14, 65579, 15,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A3_2", 393307, (s32)btlevtcmd_CommandCheckDamage, -2,
    -29999997, -29999996, 256, -29999995, 46, 49, 196699, (s32)btlevtcmd_OffUnitFlag,
    -2, 2097152, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CLAUD_KISS1", -250000000, 0,
    -29999986, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A3_2", 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -30000000, -29999999, -29999998, 983131, (s32)evt_eff, (s32)"",
    (s32)"kiss", 2, -30000000, -29999999, -29999998, -29999994, 0, 0,
    0, 0, 0, 0, 0, 458843, (s32)btlevtcmd_DamageDirect, -29999997,
    -29999996, 0, 0, 2, 1, 131163, (s32)btlevtcmd_StartAC, 1,
    65647, -29999985, 393307, (s32)btlevtcmd_SetRGB, -29999997, -29999996, 255, 255,
    255, 65541, 45, 393307, (s32)btlevtcmd_GetRGB, -29999997, -29999996, -30000000,
    -29999999, -29999998, 131126, -29999999, 2, 131098, -29999999, 190,
    131122, -29999999, 190, 33, 131126, -29999998, 4, 393307,
    (s32)btlevtcmd_SetRGB, -29999997, -29999996, -30000000, -29999999, -29999998, 65545, 1,
    6, 65541, 45, 393307, (s32)btlevtcmd_GetRGB, -29999997, -29999996, -30000000,
    -29999999, -29999998, 131126, -30000000, 2, 131126, -29999999, 2,
    131125, -29999998, 3, 131098, -29999999, 0, 131122, -29999999,
    0, 33, 393307, (s32)btlevtcmd_SetRGB, -29999997, -29999996, -30000000, -29999999,
    -29999998, 65545, 1, 6, 112, 65627, (s32)btlevtcmd_ResultAC, 131163,
    (s32)evt_snd_sfxoff, -29999986, 65631, -29999985, 131163, (s32)btlevtcmd_GetResultAC, -29999991, 131102,
    -29999991, 2, 196699, (s32)btlevtcmd_GetPartyTechLv, -2, -30000000, 65570, -30000000,
    65572, 2, 131122, -29999993, 3, 42, 131122, -29999993,
    2, 49, 196699, (s32)btlevtcmd_AcGetOutputParam, 0, -29999992, 131101, -29999992,
    -29999993, 131126, -29999992, -29999993, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, -29999992,
    -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_AudienceDeclareACResult,
    -29999988, -29999994, 32, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 33,
    32, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 33, 196699, (s32)btlevtcmd_OnUnitFlag,
    -2, 2097152, 393307, (s32)btlevtcmd_SetRGB, -29999997, -29999996, 255, 255,
    255, 196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000, 196699, (s32)_make_kiss_weapon, -29999988,
    -30000000, 131102, -29999991, 2, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999988, 131328, -29999995, 32, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999988, 256, -29999995, 33, 110, 196699,
    (s32)btlevtcmd_GetHpDamage, -29999997, -30000000, 65545, 50, 131101, -30000000, 1,
    327771, (s32)btlevtcmd_GetPos, -2, -29999995, -29999994, -29999993, 196699, (s32)btlevtcmd_GetStatusMg,
    -2, -29999992, 131132, -29999992, 40, 131125, -29999994, -29999992,
    262235, (s32)btlevtcmd_RecoverHp, -2, 1, -30000000, 983131, (s32)evt_eff, (s32)"",
    (s32)"recovery", 7, -29999995, -29999994, -29999993, -30000000, 0, 0,
    0, 0, 0, 0, 0, 33, 112, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CLAUD_KISS2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PWD_A3_3", 65545, 5, 393307, (s32)btlevtcmd_ACRStart, -2,
    0, 29, 29, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993,
    131096, -29999994, 2, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0,
    0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A_7", 65545,
    56, 32, 65627, (s32)evt_audience_acrobat_notry, 65545, 60, 33, 65539,
    90, 65627, (s32)btlevtcmd_StopAC, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65539,
    95, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000,
    -29999999, -29999998, 40, 0, 5, 0, -1, 65539,
    99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};

s32 partyClaudaAttack_KumoGuard[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -250000000, -250000000, 327771,
    (s32)btlevtcmd_GetPos, -29999997, -29999999, -250000000, -250000000, 131125, -30000000, -29999999,
    131128, -30000000, 2, 196699, (s32)evt_btl_camera_set_mode, 0, 3, 655451,
    (s32)evt_btl_camera_set_moveto, 1, -30000000, 72, 400, -30000000, 42, 0,
    30, 5, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2,
    -30000000, 589915, (s32)btlevtcmd_AcSetParamAll, 3, 0, 40, 0, 1,
    1, 2, 8, 131163, (s32)btlevtcmd_AcSetFlag, 5, 327771, (s32)btlevtcmd_SetupAC,
    -2, 18, 1, 0, 65545, 1, 65545, 30,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A4_2", 131163, (s32)btlevtcmd_StartAC, 1,
    65627, (s32)btlevtcmd_ResultAC, 65545, 60, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PWD_A4_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CLAUD_HIDE2", -250000000, 0, -250000000,
    65546, 150, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 65627, (s32)btlevtcmd_StopAC, 327771,
    (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_GetHeight, -29999997,
    -29999993, 131128, -29999993, 2, 131125, -29999999, -29999993, 131125,
    -29999998, 20, 983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test", 8, -30000000,
    -29999999, -29999998, -229998976, 0, 0, 0, 0, 0,
    0, 0, 196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000, 131125, -30000000,
    1, 196699, (s32)_make_kumoguard_weapon, -29999988, -30000000, 196699, (s32)btlevtcmd_AcGetOutputParam, 0,
    -30000000, 131101, -30000000, 1, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999988, 131328, -29999995, 131126, -30000000, 1, 262235,
    (s32)btlevtcmd_GetResultPrizeLv, -2, -30000000, -29999994, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994, 32, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999988, 256, -29999995, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988,
    -1, 33, 393307, (s32)btlevtcmd_ACRStart, -2, 0, 29, 29,
    20, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131096, -29999994, 2,
    393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0, 0, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A_7", 65546, 1000, 32, 65627,
    (s32)evt_audience_acrobat_notry, 65546, 1000, 33, 65539, 99, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 65627, (s32)evt_audience_ap_recovery,
    65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

EVT_BEGIN(clauda_appeal_event)
    CALL(btlevtcmd_RunDataEventChild, -2, 7)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 66)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MARIO_APPEAL1"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 15)
    ADD(LW(1), 30)
    CALL(btlevtcmd_GetFaceDirection, -2, LW(14))
    MULTIPLY(LW(14), 45)
    CALL(evt_eff, STRING(""), STRING("kiss"), 2, LW(0), LW(1), LW(2), LW(14), 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AudienceAppeal, -2)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(attack_audience_event)
    CALL(_check_aud_item_type, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL_CHILD(PTR(attack_bad_audience_event))
        CASE_DEFAULT
        CALL_CHILD(PTR(attack_good_audience_event))
    END_SWITCH
    RETURN
EVT_END()

s32 attack_bad_audience_event[] = {
    196699, (s32)btlevtcmd_OffUnitFlag, -2, 2097152, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PWD_A1_1", 327771, (s32)_get_attack_aud_no, -29999997, -30000000, -29999999, -29999998, 110,
    65545, 15, 196699, (s32)evt_btl_camera_set_mode, 0, 13, 327771, (s32)evt_btl_camera_set_homing_unit_audience,
    0, -2, 1, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_btl_camera_set_zoom, 0, 200, 112, 131122, -29999995, -29999999,
    131125, -29999999, 28, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 5,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386,
    131122, -29999994, 36, 393307, (s32)btlevtcmd_MarioJumpParam, -2, -30000000, -29999999,
    -29999998, -29999994, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A1_1", 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CLAUD_ATTACK1", -250000000, 0, -250000000, 110, 131128,
    -29999994, 2, 65545, -29999994, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PWD_A1_2", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CLAUD_ATTACK1", -250000000, 0, -250000000,
    112, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, -29999994,
    0, 0, 196699, (s32)_attack_aud, -29999997, 0, 196699, (s32)evt_btl_camera_set_mode,
    0, 3, 131163, (s32)btlevtcmd_JumpContinue, -2, 393307, (s32)evt_btl_camera_shake_h, 0,
    8, 0, 30, 13, 65647, -29999985, 65546, 1500,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546, 1000, 112, 65647,
    -29999986, 327771, (s32)evt_sub_intpl_init_float, 11, -229998976, -229999591, 10, 65541,
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
    131163, (s32)btlevtcmd_WaitEventEnd, -29999986, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 20, 131125, -29999999,
    20, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999693, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 18, -1, 196699, (s32)btlevtcmd_OnUnitFlag, -2, 2097152, 65546,
    400, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000,
    0, -29999998, 16, 0, 4, 0, 0, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 458843, (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998, -229993856,
    -29999985, 131125, -29999985, 30, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000,
    -29999999, -29999998, -29999985, 20, 4, 0, -1, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 attack_good_audience_event[] = {
    196699, (s32)btlevtcmd_OffUnitFlag, -2, 2097152, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PWD_A1_1", 327771, (s32)_get_attack_aud_no, -29999997, -30000000, -29999999, -29999998, 110,
    196699, (s32)evt_btl_camera_set_mode, 0, 13, 327771, (s32)evt_btl_camera_set_homing_unit_audience, 0, -2,
    1, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom,
    0, 200, 112, 131122, -29999995, -29999999, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 30, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999386, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, 0,
    -29999998, 40, 15, 4, 0, 0, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 20, 0, 4, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A3_1", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete,
    -2, 1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CLAUD_KISS1", -250000000, 0,
    -29999986, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A3_2", 327771, (s32)_get_attack_aud_no,
    -29999997, -30000000, -29999999, -29999998, 131125, -29999999, 25, 983131,
    (s32)evt_eff, (s32)"", (s32)"kiss", 2, -30000000, -29999999, -29999998, -29999994,
    0, 0, 0, 0, 0, 0, 0, 196699,
    (s32)_attack_aud, -29999997, 1, 65647, -29999985, 65546, 1500, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 65546, 1000, 112, 65546, 500,
    131163, (s32)evt_snd_sfxoff, -29999986, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CLAUD_KISS2", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A3_3", 196699,
    (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 65546, 300, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 40, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, 0, -29999998, 16, 0,
    4, 0, 0, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_GetMoveFrame, -2,
    -30000000, -29999999, -29999998, -229993856, -29999985, 131125, -29999985, 30,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, -29999985, 20,
    4, 0, -1, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static StatusVulnerability regist = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static EVT_BEGIN(party_win_reaction)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PWD_Y_1"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 1)
    RETURN
EVT_END()

#pragma force_active on
#pragma force_active reset


USER_FUNC(_clauda_make_extra_work_area) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    unit->countersetWeapon = BattleAlloc(sizeof(BattleWeapon));
    return EVT_RETURN_DONE;
}

static void __makeTechMenuFunc(BattleWorkCommand* command, s32* count) {
    s32 techLv;

    techLv = partyGetTechLv(BattleTransPartyId(BattleGetPartyPtr(_battleWorkPointer)->currentKind));

    command->mWeaponTable[*count].mIndex = -1;
    command->mWeaponTable[*count].mItem = 0;
    command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_ClaudaNormalAttack;
    command->mWeaponTable[*count].field_0x4 = 0;
    command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;
    command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
    (*count)++;

    if (techLv >= 0) {
        command->mWeaponTable[*count].mIndex = -1;
        command->mWeaponTable[*count].mItem = 0;
        command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_ClaudaBreathAttack;
        command->mWeaponTable[*count].field_0x4 = 0;
        command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;
        command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
        (*count)++;
    }
    if (techLv >= 1) {
        command->mWeaponTable[*count].mIndex = -1;
        command->mWeaponTable[*count].mItem = 0;
        command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_ClaudaPredationAttack;
        command->mWeaponTable[*count].field_0x4 = 0;
        command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;
        command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
        (*count)++;
    }
    if (techLv >= 2) {
        command->mWeaponTable[*count].mIndex = -1;
        command->mWeaponTable[*count].mItem = 0;
        command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_ClaudaKumogakureAttack;
        command->mWeaponTable[*count].field_0x4 = 0;
        command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;
        command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
        (*count)++;
    }
}

USER_FUNC(_check_blow_rate) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id, out;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    out = args[1];
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    evtSetValue(event, out, unit->vulnStatus->galeForceRate);
    return EVT_RETURN_DONE;
}

static USER_FUNC(_clauda_breath_effect_ready) {
    BattleWork* wp = _battleWorkPointer;
    s32 id;
    BattleUnit* unit;
    Vec pos;
    EffectEntry* eff;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x += unit->mSizeMultiplier * (unit->faceDirection * 20);
    pos.y += 25.0f * unit->mSizeMultiplier;
    if (unit->faceDirection >= 0) {
        eff = effKumokumoN64Entry(0, 60, pos.x, pos.y, pos.z, 0.0f, 2.0f, 1.0f);
    } else {
        eff = effKumokumoN64Entry(0, 60, pos.x, pos.y, pos.z, 180.0f, 2.0f, 1.0f);
    }
    ((s32*)eff->userdata)[6] = 76;
    ((s32*)eff->userdata)[7] = 167;
    ((s32*)eff->userdata)[8] = 202;
    ((s32*)eff->userdata)[10] = 125;
    ((s32*)eff->userdata)[11] = 27;
    ((s32*)eff->userdata)[12] = 245;
    return EVT_RETURN_DONE;
}

static USER_FUNC(_clauda_breath_effect_fire) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id;
    BattleUnit* unit;
    s32 var;
    Vec pos;
    EffectEntry* eff;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    var = args[0];
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x += unit->mSizeMultiplier * (unit->faceDirection * 25);
    pos.y += 15.0f * unit->mSizeMultiplier;
    if (unit->faceDirection >= 0) {
        eff = effKumokumoN64Entry(0, 0, pos.x, pos.y, pos.z, 0.0f, -2.0f, 1.0f);
    } else {
        eff = effKumokumoN64Entry(0, 0, pos.x, pos.y, pos.z, 180.0f, -2.0f, 1.0f);
    }
    ((s32*)eff->userdata)[6] = 76;
    ((s32*)eff->userdata)[7] = 167;
    ((s32*)eff->userdata)[8] = 202;
    ((s32*)eff->userdata)[10] = 125;
    ((s32*)eff->userdata)[11] = 27;
    ((s32*)eff->userdata)[12] = 245;
    ((f32*)eff->userdata)[22] = -10.0f;
    evtSetValue(event, var, (s32)eff);
    return EVT_RETURN_DONE;
}

USER_FUNC(_make_breath_weapon) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    s32 index;
    BattleWeapon* weapon;
    void* src;
    s32 id, value;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    index = args[0];
    weapon = unit->countersetWeapon;
    src = (void*)evtGetValue(event, index);
    value = evtGetValue(event, args[1]);
    memcpy(weapon, src, sizeof(BattleWeapon));
    ((u8*)weapon)[0xA5] = value;
    evtSetValue(event, index, (s32)weapon);
    return EVT_RETURN_DONE;
}

USER_FUNC(_make_kiss_weapon) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    s32 index;
    BattleWeapon* weapon;
    void* src;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    index = args[0];
    weapon = unit->countersetWeapon;
    src = (void*)evtGetValue(event, index);
    evtGetValue(event, args[1]);
    memcpy(weapon, src, sizeof(BattleWeapon));
    evtSetValue(event, index, (s32)weapon);
    return EVT_RETURN_DONE;
}

USER_FUNC(_get_clauda_kiss_hit_position) {
    s32* args = event->args;
    Vec pos, tmp;
    s32 dir;
    BattleUnit* target;
    BattleWork* wp = _battleWorkPointer;
    s32 targetId;
    s32 outX;
    s32 outY;
    BattleUnit* unit;
    s32 outZ;
    s32 id;

    id = evtGetValue(event, args[0]);
    targetId = evtGetValue(event, args[1]);
    evtGetValue(event, args[2]);
    outX = args[3];
    outY = args[4];
    outZ = args[5];
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    target = BattleGetUnitPtr(wp, BattleTransID(event, targetId));
    dir = target->faceDirection;
    BtlUnit_GetPos(target, &pos.x, &pos.y, &pos.z);
    pos.x += dir * (target->kissHitOffset.x * target->mSizeMultiplier);
    pos.y += target->kissHitOffset.y * target->mSizeMultiplier;
    pos.z += target->kissHitOffset.z * target->mSizeMultiplier;
    pos.y -= 30.0f * unit->mSizeMultiplier;
    tmp = pos;
    tmp.y = BattleGetFloorHeight(wp, tmp.x, tmp.y, tmp.z);
    if (tmp.y > pos.y) {
        pos.y = tmp.y;
    }
    evtSetFloat(event, outX, pos.x);
    evtSetFloat(event, outY, pos.y);
    evtSetFloat(event, outZ, pos.z);
    return EVT_RETURN_DONE;
}

USER_FUNC(_make_kumoguard_weapon) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    s32 index;
    BattleWeapon* weapon;
    void* src;
    s32 id, value;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    index = args[0];
    weapon = unit->countersetWeapon;
    src = (void*)evtGetValue(event, index);
    value = evtGetValue(event, args[1]);
    memcpy(weapon, src, sizeof(BattleWeapon));
    weapon->dodgyTime = value;
    evtSetValue(event, index, (s32)weapon);
    return EVT_RETURN_DONE;
}
