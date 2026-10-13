#include "battle/battle.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/msgdrv.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_party.h"
#include "memory.h"
#include "system.h"
#include <string.h>
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
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
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AnimeFlagOnOff[];
extern s32 btlevtcmd_AnnounceMessage[];
extern s32 btlevtcmd_AnnounceSetParam[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_AudienceAppeal[];
extern s32 btlevtcmd_AudienceDeclareACResult[];
extern s32 btlevtcmd_AudienceDeclareAcrobatResult[];
extern s32 btlevtcmd_BtlIconDelete[];
extern s32 btlevtcmd_BtlIconEntryItemId[];
extern s32 btlevtcmd_BtlIconSetPosition[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CommandCheckDamage[];
extern s32 btlevtcmd_CommandGetWeaponActionLv[];
extern s32 btlevtcmd_CommandGetWeaponAddress[];
extern s32 btlevtcmd_CommandPayWeaponCost[];
extern s32 btlevtcmd_CommandPreCheckDamage[];
extern s32 btlevtcmd_DivePartsPosition[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FallPartsPosition[];
extern s32 btlevtcmd_GetFaceDirection[];
extern s32 btlevtcmd_GetHeight[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetMoveFrame[];
extern s32 btlevtcmd_GetPartsPos[];
extern s32 btlevtcmd_GetPartyTechLv[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_GetResultAC[];
extern s32 btlevtcmd_GetResultPrizeLv[];
extern s32 btlevtcmd_GetRotate[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetStageAudienceAreaSize[];
extern s32 btlevtcmd_GetStageSize[];
extern s32 btlevtcmd_GetStatusMg[];
extern s32 btlevtcmd_GetUnitId[];
extern s32 btlevtcmd_GetUnitWork[];
extern s32 btlevtcmd_GetWidth[];
extern s32 btlevtcmd_InviteApInfoReport[];
extern s32 btlevtcmd_JumpContinue[];
extern s32 btlevtcmd_JumpPartsPosition[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_OffUnitFlag[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_OnUnitFlag[];
extern s32 btlevtcmd_PreCheckCounter[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_RecoverHp[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultAC[];
extern s32 btlevtcmd_RunDataEventChild[];
extern s32 btlevtcmd_SetDiveSound[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetHomePos[];
extern s32 btlevtcmd_SetPartsBlur[];
extern s32 btlevtcmd_SetPartsDiveSound[];
extern s32 btlevtcmd_SetPartsFallAccel[];
extern s32 btlevtcmd_SetPartsJumpSound[];
extern s32 btlevtcmd_SetPartsMoveSpeed[];
extern s32 btlevtcmd_SetPartsPos[];
extern s32 btlevtcmd_SetPartsRotate[];
extern s32 btlevtcmd_SetPartsRunSound[];
extern s32 btlevtcmd_SetPartsWalkSound[];
extern s32 btlevtcmd_SetRGB[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SetScale[];
extern s32 btlevtcmd_SetUnitWork[];
extern s32 btlevtcmd_SetupAC[];
extern s32 btlevtcmd_StartAC[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_StopAC[];
extern s32 btlevtcmd_TransStageFloorPosition[];
extern s32 btlevtcmd_WaitEventEnd[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_ftof[];
extern s32 btlevtcmd_ftomsec[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_audience_acrobat_notry[];
extern s32 evt_audience_ap_recovery[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_homing_unit_audience[];
extern s32 evt_btl_camera_set_homing_unitparts[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_moveto[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_eff[];
extern s32 evt_snd_sfxon[];
extern s32 evt_snd_sfxon_3d[];
extern s32 evt_sub_intpl_get_value[];
extern s32 evt_sub_intpl_init[];
extern s32 lbl_80003500[];
extern s32 subset_attack_ready_jump_event[];
extern s32 unk_evt_803510ec[];
extern s32 weaponGetACOutputParam[];

void btlUnitPartsDisp(CameraId camId, BattleUnitPart* parts);
void BtlUnit_EquipItem(BattleUnit* unit, s32 flags, ItemType type);

PoseTableEntry pose_table_chuchurina_stay[24];
static BattleDataEntry data_table[8];
BattleUnitKindPart unitpartsdata_Party_Chuchurina[4];
BattleUnitKind unitdata_Party_Chuchurina;
static s32 battle_entry_event[59];
static s32 init_event[48];
static s32 damage_event[16];
s32 partyWeapon_ChuchurinaNormalAttackLeft[48];
s32 partyWeapon_ChuchurinaNormalAttackRight[48];
s32 partyWeapon_ChuchurinaNormalAttackLeftLast[48];
s32 partyWeapon_ChuchurinaNormalAttackRightLast[48];
s32 partyWeapon_ChuchurinaMadowaseAttack[48];
s32 partyWeapon_ChuchurinaItemSteal[48];
s32 partyWeapon_ChuchurinaKiss[48];
s32 partyChuchurinaAttack_NormalAttack[1590];
s32 partyChuchurinaAttack_MadowaseAttack[2020];
s32 partyChuchurinaAttack_ItemSteal[788];
s32 partyChuchurinaAttack_Kiss[568];
s32 chuchurina_appeal_event[86];
static s32 party_win_reaction[18];
static s32 attack_audience_event[204];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static s32 attack_event[2];
static s32 wait_event[6];
static s32 main_evt[4];

USER_FUNC(_chuchu_make_extra_work_area);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeWaitPlayComplete);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_MovePosition);
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
USER_FUNC(mono_main);
USER_FUNC(mono_off);
USER_FUNC(mono_on);
USER_FUNC(mono_capture_event);
USER_FUNC(_chuchu_item_steal);
USER_FUNC(_get_itemsteal_param);
USER_FUNC(_make_madowase_weapon);
USER_FUNC(_get_binta_hit_position);
USER_FUNC(mono_off);
USER_FUNC(mono_on);
USER_FUNC(mono_capture_event);
USER_FUNC(mono_main);
USER_FUNC(_chuchu_item_steal);
USER_FUNC(_get_itemsteal_param);
USER_FUNC(_make_madowase_weapon);
USER_FUNC(_get_binta_hit_position);
USER_FUNC(_chuchu_make_extra_work_area);
static void __makeTechMenuFunc(BattleWorkCommand* command, s32* count);

__declspec(section ".data") u64 lbl_8037EC10 = 0xBF8000003F800000;

__declspec(section ".data") u64 fd_chuchurina_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") u64 lbl_8037EC20 = 0x3F800000BF800000;

__declspec(section ".data") u64 fd_chuchurina_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") u64 lbl_8037EC30 = 0xBF8000003F800000;

__declspec(section ".data") u64 fd_chuchurina_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") u64 lbl_8037EC40 = 0x3F800000BF800000;

__declspec(section ".data") u64 fd_chuchurina_one_negone_359 = 0x3F800000BF800000;

PoseTableEntry pose_table_chuchurina_stay[] = {
    {9, "PCH_D_4"},
    {2, "PCH_D_4"},
    {3, "PCH_X_1"},
    {4, "PCH_D_2"},
    {5, "PCH_X_1"},
    {1, "PCH_N_1"},
    {27, "PCH_D_3"},
    {28, "PCH_S_1"},
    {37, "PCH_G_1"},
    {31, "PCH_G_1"},
    {39, "PCH_D_1"},
    {40, "PCH_W_1"},
    {42, "PCH_R_1"},
    {57, "PCH_D_2"},
    {56, "PCH_D_2"},
    {60, "PCH_D_4"},
    {61, "PCH_D_2"},
    {65, "PCH_T_1"},
    {52, "PCH_I_1"},
    {67, "PCH_C_1"},
    {64, "PCH_X_1"},
    {49, "PCH_O_1"},
    {45, "PCH_G_1"},
    {69, "PCH_S_1"},
};

static BattleDataEntry data_table[] = {
    {5, chuchurina_appeal_event},
    {6, attack_audience_event},
    {1, __makeTechMenuFunc},
    {48, btldefaultevt_Dummy},
    {64, party_win_reaction},
    {7, subset_attack_ready_jump_event},
    {47, btldefaultevt_avoid_counter_event},
    {0, NULL},
};

BattleUnitKindPart unitpartsdata_Party_Chuchurina[] = {
    {1, "btl_un_chuchurina", "c_tyutyu", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, 0x9, 0, pose_table_chuchurina_stay},
    {2, "btl_un_chuchurina", "c_tyutyu", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, 0x13010000, 0, pose_table_chuchurina_stay},
    {3, "btl_un_chuchurina", "c_tyutyu", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, 0x13010000, 0, pose_table_chuchurina_stay},
    {4, "btl_un_chuchurina", "c_tyutyu", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, 0x13010000, 0, pose_table_chuchurina_stay},
};

BattleUnitKind unitdata_Party_Chuchurina = {
    230,
    "btl_un_chuchurina",
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
    33,
    10,
    22,
    0.0f,
    12.0f,
    0.0f,
    0,
    0,
    0.0f,
    30.0f,
    0.0f,
    0.0f,
    30.0f,
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
    21.45f,
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
    0x2000000,
    &regist,
    4,
    unitpartsdata_Party_Chuchurina,
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
    CALL(btlevtcmd_SetMoveSoundDataWork, -2, STRING("SFX_PARTY_BATTLE_SUBMOVE1L"), STRING("SFX_PARTY_BATTLE_SUBMOVE1R"), 0, 7, 7, 0, 0)
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -2, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static EVT_BEGIN(init_event)
    CALL(_chuchu_make_extra_work_area)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 15, 13)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 7, 7)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_SetEventEntry, -2, PTR(battle_entry_event))
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

s32 partyWeapon_ChuchurinaNormalAttackLeft[] = {
    (s32)"btl_wn_pcr_normal", 22020096, 0, (s32)"msg_pch_binta", 1677721600, 1065353216, 16868402, 0,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 1377026, (s32)"msg_ac_binta", 213063, 514, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyChuchurinaAttack_NormalAttack, 100, 131840, 0,
};

s32 partyWeapon_ChuchurinaNormalAttackRight[] = {
    (s32)"btl_wn_pcr_normal", 22020096, 0, (s32)"msg_pch_binta", 1677721600, 1065353216, 16868402, 0,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 1442562, (s32)"msg_ac_binta", 213063, 514, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyChuchurinaAttack_NormalAttack, 100, 131840, 0,
};

s32 partyWeapon_ChuchurinaNormalAttackLeftLast[] = {
    (s32)"btl_wn_pcr_normal", 22020096, 0, (s32)"msg_pch_binta", 1677721600, 1065353216, 16868402, (s32)weaponGetACOutputParam,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 1508098, (s32)"msg_ac_binta", 213063, 2, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyChuchurinaAttack_NormalAttack, 100, 131584, 0,
};

s32 partyWeapon_ChuchurinaNormalAttackRightLast[] = {
    (s32)"btl_wn_pcr_normal", 22020096, 0, (s32)"msg_pch_binta", 1677721600, 1065353216, 16868402, (s32)weaponGetACOutputParam,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 1573634, (s32)"msg_ac_binta", 213063, 2, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyChuchurinaAttack_NormalAttack, 100, 131584, 0,
};

s32 partyWeapon_ChuchurinaMadowaseAttack[] = {
    (s32)"btl_wn_pcr_madowase", 22151168, 0, (s32)"msg_pch_madowaseru", 1677918208, 1065353216, 50684978, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, (s32)"msg_ac_madowaseru", 131072, 2047, -2147475452,
    0, 1677918208, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyChuchurinaAttack_MadowaseAttack, 100, 1280, 0,
};

s32 partyWeapon_ChuchurinaItemSteal[] = {
    (s32)"btl_wn_pcr_steal", 22085632, 0, (s32)"msg_pch_heart_catch", 1677852672, 1065353216, 17130546, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 1311490, (s32)"msg_ac_heart_catch", 131072, 514, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyChuchurinaAttack_ItemSteal, 100, 1280, 0,
};

s32 partyWeapon_ChuchurinaKiss[] = {
    (s32)"btl_wn_pcr_kiss", 22216704, 0, (s32)"msg_pch_kiss", 1678376960, 1065353216, 17130546, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830240, 268435456, 770, (s32)"msg_ac_chuchurina_kiss", 131080, 2047, (s32)lbl_80003500,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyChuchurinaAttack_Kiss, 100, 1280, 0,
};

s32 partyChuchurinaAttack_NormalAttack[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200,
    393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256, -29999995, 131096,
    -29999995, 5, 196699, (s32)btlevtcmd_GetStatusMg, -29999997, -29999994, 131132, -29999994,
    40, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000,
    -29999994, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998, 1,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 40, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 0, 393307,
    (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256, -29999995, 33, 196699,
    (s32)btlevtcmd_GetStatusMg, -2, -29999995, 131132, -29999995, 12, 458843, (s32)_get_binta_hit_position,
    -2, -29999997, -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -29999997, -30000000, -29999995, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998,
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998, 1, -29999985,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    40, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 131125, -29999998, 5,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1,
    0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 350, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PCH_A1_1", 65647, -30000000, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699,
    (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163, (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126, -30000000,
    3, 65570, -30000000, 65576, -3, 131122, -29999999, 25,
    131122, -29999998, 30, 65572, -2, 131122, -29999999, 20,
    131122, -29999998, 30, 65572, -1, 131122, -29999999, 17,
    131122, -29999998, 30, 65572, 0, 131122, -29999999, 15,
    131122, -29999998, 30, 65572, 1, 131122, -29999999, 14,
    131122, -29999998, 30, 65572, 2, 131122, -29999999, 13,
    131122, -29999998, 30, 42, 131122, -29999999, 12, 131122,
    -29999998, 30, 49, 196699, (s32)btlevtcmd_GetPartyTechLv, -2, -30000000, 65570,
    -30000000, 65572, 2, 589915, (s32)btlevtcmd_AcSetParamAll, 14, 210, 178,
    -29999999, -29999998, 34, 35, -250000000, 327771, (s32)btlevtcmd_AcSetGaugeParam, 34,
    68, 100, 100, 131163, (s32)btlevtcmd_AcSetFlag, 64, 65572, 1,
    589915, (s32)btlevtcmd_AcSetParamAll, 14, 210, 178, -29999999, -29999998, 50,
    51, -250000000, 327771, (s32)btlevtcmd_AcSetGaugeParam, 34, 68, 100, 100,
    131163, (s32)btlevtcmd_AcSetFlag, 64, 42, 589915, (s32)btlevtcmd_AcSetParamAll, 14, 210,
    178, -29999999, -29999998, 100, 100, -250000000, 327771, (s32)btlevtcmd_AcSetGaugeParam,
    100, 100, 100, 100, 131163, (s32)btlevtcmd_AcSetFlag, 64, 49,
    327771, (s32)btlevtcmd_SetupAC, -2, 6, 1, 0, 65545, 1,
    131163, (s32)btlevtcmd_StartAC, 1, 112, 131163, (s32)btlevtcmd_WaitEventEnd, -30000000, 65647,
    -29999986, 131122, -29999994, 0, 131122, -29999995, 5, 65541,
    -29999995, 131125, -29999994, 1, 131122, -30000000, -29999994, 131128,
    -30000000, 2, 131129, -30000000, 2, 131096, -30000000, 0,
    327771, (s32)btlevtcmd_SetScale, -2, -229998925, -229998925, -229998976, 32, 327771,
    (s32)btlevtcmd_SetScale, -2, -229998976, -229998976, -229998976, 33, 65545, 1,
    131122, -29999995, 5, 6, 112, 65647, -29999985, 131122,
    -29999995, 5, 65541, -29999995, 196699, (s32)btlevtcmd_AcGetOutputParam, 1, -30000000,
    131122, -29999999, 255, 131122, -29999998, 190, 131127, -29999998,
    -30000000, 131128, -29999998, 100, 131126, -29999999, -29999998, 393307,
    (s32)btlevtcmd_SetRGB, -2, 1, 255, -29999999, -29999999, 65545, 1,
    131122, -29999995, 5, 6, 112, 65627, (s32)btlevtcmd_ResultAC, 65631,
    -29999986, 65631, -29999985, 196699, (s32)btlevtcmd_GetPartyTechLv, -2, -30000000, 65570,
    -30000000, 65572, 2, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, 4,
    65572, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, 3, 42,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 5, 2, 49, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 300, 393307, (s32)btlevtcmd_SetRGB,
    -2, 1, 255, 255, 255, 65647, -29999986, 131122,
    -29999992, -75, 327771, (s32)btlevtcmd_GetRotate, -2, -250000000, -30000000, -250000000,
    131101, -30000000, 180, 131126, -30000000, 360, 33, 327771,
    (s32)evt_sub_intpl_init, 5, -30000000, -29999992, 8, 65541, 8, 65627,
    (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, 0, -30000000, 0, 65545,
    1, 6, 131122, -29999992, -60, 131122, -29999991, -75,
    327771, (s32)evt_sub_intpl_init, 11, -29999991, -29999992, 4, 65541, 4,
    65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, 0, -30000000, 0,
    65545, 1, 6, 112, 131163, (s32)btlevtcmd_WaitEventEnd, -29999986, 131122,
    -29999987, 18, 131122, -29999990, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    4, 0, 65539, 10, 131125, -29999990, 1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_A1_2", 131101, -29999990, 2, 393307,
    (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 1048832, -29999995, 32, 393307,
    (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256, -29999995, 33, 65570,
    -29999995, 65579, 2, 65579, 3, 65579, 6, 65579,
    4, 46, 65572, 1, 42, 65546, 1000, 49,
    131097, -29999995, 1, 65631, -29999986, 131122, -29999986, 0,
    65627, (s32)btlevtcmd_StopAC, 131096, -29999995, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 33, 131096, -29999995, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 33, 131096, -29999995, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 33, 65541, 20, 327771, (s32)btlevtcmd_AddRotate, -2, 0,
    18, 0, 65545, 1, 6, 65541, 36, 327771,
    (s32)btlevtcmd_AddRotate, -2, 0, 10, 0, 65545, 1, 6,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PCH_A2_4", 65545, 52, 65627, (s32)evt_audience_ap_recovery, 65627,
    (s32)btlevtcmd_InviteApInfoReport, 65540, 95, 33, 131122, -30000000, -29999990, 131129,
    -30000000, 2, 131097, -30000000, 0, 131122, -29999988, (s32)partyWeapon_ChuchurinaNormalAttackRight,
    32, 131122, -29999988, (s32)partyWeapon_ChuchurinaNormalAttackLeft, 33, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    4, -29999985, 131097, -29999985, 0, 65631, -29999985, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 4, 0, 33, 131097, -29999986, 0,
    65631, -29999986, 131122, -29999986, 0, 33, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 5, -30000000, 131101, -29999990, -30000000, 65540, 20,
    32, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 131103, -29999994, 2, 65540,
    20, 33, 33, 65540, 21, 65539, 20, 131096,
    -29999988, (s32)partyWeapon_ChuchurinaNormalAttackLeft, 131122, -29999988, (s32)partyWeapon_ChuchurinaNormalAttackLeftLast, 32, 131122, -29999988,
    (s32)partyWeapon_ChuchurinaNormalAttackRightLast, 33, 65539, 21, 458843, (s32)btlevtcmd_PreCheckCounter, -2, -29999997,
    -29999996, -29999988, 256, -30000000, 65570, -30000000, 65579, 7,
    65579, 8, 65579, 9, 65579, 10, 65579, 11,
    65579, 12, 65579, 13, 65579, 14, 65579, 15,
    65579, 16, 65579, 17, 131096, -29999988, (s32)partyWeapon_ChuchurinaNormalAttackLeft, 131122,
    -29999988, (s32)partyWeapon_ChuchurinaNormalAttackLeftLast, 32, 131122, -29999988, (s32)partyWeapon_ChuchurinaNormalAttackRightLast, 33, 65647,
    -29999985, 131122, -29999993, -29999987, 327771, (s32)btlevtcmd_GetRotate, -2, -250000000,
    -30000000, -250000000, 131101, -30000000, 180, 131126, -30000000, 360,
    327771, (s32)evt_sub_intpl_init, 11, -30000000, 0, 4, 65541, 4,
    65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, -30000000,
    65545, 1, 131096, -29999999, 1, 7, 33, 6,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 112, 131163,
    (s32)btlevtcmd_WaitEventEnd, -29999985, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 131102, -29999994, 2,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 131328, -29999995,
    32, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 256,
    -29999995, 33, 2, 46, 49, 393307, (s32)evt_btl_camera_shake_h, 0,
    2, 0, 12, 13, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5,
    -30000000, 131101, -29999990, -30000000, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_CHUCHURINA_ATTACK3", 0,
    131102, -29999994, 2, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999988, 131328, -29999995, 32, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999988, 256, -29999995, 33, 32, 131122, -30000000,
    -29999990, 131149, -30000000, 1, 131096, -30000000, 0, 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_BTL_CHUCHURINA_ATTACK2", 0, 32, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_CHUCHURINA_ATTACK1", 0,
    33, 131102, -29999994, 2, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999988, 131072, -29999995, 32, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999988, 256, -29999995, 33, 33, 131163,
    (s32)btlevtcmd_GetResultAC, -29999994, 131102, -29999994, 2, 196699, (s32)btlevtcmd_AcGetOutputParam, 2,
    -30000000, 131126, -30000000, 2, 131101, -30000000, 0, 262235,
    (s32)btlevtcmd_GetResultPrizeLv, -29999997, -30000000, -29999989, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999989, -30000000, -29999999,
    -29999998, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999989, 32, 196699, (s32)btlevtcmd_AudienceDeclareACResult,
    -29999988, -1, 33, 32, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1,
    33, 131102, -29999994, 2, 65570, -29999990, 65576, 2,
    65647, -29999985, 131122, -29999993, -29999987, 131101, -29999993, 0,
    131122, -29999992, 75, 32, 131122, -29999992, -75, 33,
    327771, (s32)btlevtcmd_GetRotate, -2, -250000000, -30000000, -250000000, 131101, -30000000,
    180, 131126, -30000000, 360, 33, 327771, (s32)evt_sub_intpl_init, 5,
    -30000000, -29999992, 14, 65541, 14, 65627, (s32)evt_sub_intpl_get_value, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, -30000000, 0, 65545, 1, 6,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000, 131098, -29999990, -30000000,
    131122, -29999993, -29999987, 131101, -29999993, 0, 131122, -29999992,
    75, 131122, -29999991, 75, 32, 131122, -29999992, -75,
    131122, -29999991, -75, 33, 327771, (s32)evt_sub_intpl_init, 11, -29999991,
    -29999992, 6, 65541, 6, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, -30000000, 0, 65545, 1, 6, 32,
    131122, -29999993, -29999987, 131101, -29999993, 0, 131122, -29999992,
    0, 131122, -29999991, 75, 32, 131122, -29999992, 0,
    131122, -29999991, -75, 33, 327771, (s32)evt_sub_intpl_init, 11, -29999991,
    -29999992, 12, 65541, 12, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, -30000000, 0, 65545, 1, 6, 33,
    112, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 42, 65647, -29999985, 327771,
    (s32)btlevtcmd_GetRotate, -2, -250000000, -29999992, -250000000, 131122, -29999993, 360,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000, 131101, -29999990, -30000000,
    131122, -30000000, -29999992, 131101, -29999992, 180, 131126, -30000000,
    360, 33, 131101, -29999987, 0, 131126, -29999993, -30000000,
    32, 131125, -29999993, -30000000, 33, 32, 131125, -29999993,
    60, 131122, -30000000, -29999992, 131101, -29999992, 180, 131126,
    -30000000, 360, 33, 131101, -29999987, 0, 131126, -29999993,
    -30000000, 32, 131125, -29999993, -30000000, 33, 33, 131098,
    -29999987, 0, 131127, -29999993, -1, 33, 327771, (s32)evt_sub_intpl_init,
    5, 0, -29999993, 20, 65541, 20, 65627, (s32)evt_sub_intpl_get_value,
    131125, -30000000, -29999992, 327771, (s32)btlevtcmd_SetRotate, -2, 0, -30000000,
    0, 65545, 1, 6, 112, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    4, -29999985, 65545, 10, 49, 32, 65647, -29999985,
    327771, (s32)btlevtcmd_GetRotate, -2, -250000000, -29999992, -250000000, 131122, -29999993,
    720, 131101, -29999990, 1, 131122, -30000000, -29999992, 131101,
    -29999992, 180, 131126, -30000000, 360, 33, 131126, -29999993,
    -30000000, 33, 131098, -29999987, 0, 131127, -29999993, -1,
    33, 327771, (s32)evt_sub_intpl_init, 0, 0, -29999993, 60, 65541,
    60, 65627, (s32)evt_sub_intpl_get_value, 131125, -30000000, -29999992, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, -30000000, 0, 65545, 1, 6, 112,
    131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_X_1", 65545, 60,
    65627, (s32)btlevtcmd_StopAC, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65540, 95,
    33, 131127, -29999987, -1, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5,
    -30000000, 131098, -29999990, -30000000, 65540, 10, 33, 65539,
    90, 65627, (s32)btlevtcmd_StopAC, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_A1_3", 65545, 40, 65539, 95,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 458843, (s32)btlevtcmd_GetMoveFrame,
    -2, -30000000, -29999999, -29999998, 0, -29999986, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 42, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 65647, -29999985, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, -29999986, -1, 0, 112, 131122, -29999989, -29999986,
    131126, -29999989, 11, 131126, -29999986, 1, 131099, -29999986,
    -29999989, 131122, -29999987, -29999986, 131126, -29999987, 10, 131102,
    -29999994, 2, 393307, (s32)btlevtcmd_ACRStart, -2, 0, -29999987, -29999986,
    0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131101, -29999994, 2,
    65631, -29999985, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999488, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_O_1", 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult,
    -29999988, 1, 0, 0, 0, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 20, -1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 327771, (s32)btlevtcmd_SetHomePos, -2,
    -30000000, -29999999, -29999998, 32, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 33,
    32, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 33, 32, 131163, (s32)btlevtcmd_WaitEventEnd,
    -29999985, 33, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630,
    (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 partyChuchurinaAttack_MadowaseAttack[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000,
    196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163, (s32)btlevtcmd_AcSetFlag, 41, 131163,
    (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126, -30000000, 3, 65570, -30000000, 65576,
    -3, 131122, -30000000, 3, 131122, -29999999, 50, 65572,
    -2, 131122, -30000000, 4, 131122, -29999999, 80, 65572,
    -1, 131122, -30000000, 5, 131122, -29999999, 100, 65572,
    0, 131122, -30000000, 7, 131122, -29999999, 100, 65572,
    1, 131122, -30000000, 8, 131122, -29999999, 110, 131163,
    (s32)btlevtcmd_AcSetFlag, 49, 65572, 2, 131122, -30000000, 10, 131122,
    -29999999, 120, 131163, (s32)btlevtcmd_AcSetFlag, 49, 42, 131122, -30000000,
    12, 131122, -29999999, 130, 131163, (s32)btlevtcmd_AcSetFlag, 49, 49,
    589915, (s32)btlevtcmd_AcSetParamAll, 1, 240, 178, -30000000, -29999999, 100,
    1, -250000000, 327771, (s32)btlevtcmd_AcSetGaugeParam, 34, 68, 100, 100,
    327771, (s32)btlevtcmd_SetupAC, -2, 6, 1, 0, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -250000000, -250000000, 196699, (s32)evt_btl_camera_set_mode, 0, 3,
    655451, (s32)evt_btl_camera_set_moveto, 1, -30000000, 73, 400, -30000000, 43,
    0, 40, 5, 65545, 22, 131163, (s32)btlevtcmd_StartAC, 1,
    65627, (s32)btlevtcmd_ResultAC, 65627, (s32)btlevtcmd_StopAC, 65545, 20, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PCH_I_1", 65541, 40, 327771, (s32)btlevtcmd_AddRotate, -2,
    0, 36, 0, 65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PCH_A4_1", 458843, (s32)btlevtcmd_SetWalkSound, -2, (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1L", (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1R", 0, 15,
    13, 458843, (s32)btlevtcmd_SetRunSound, -2, (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1L", (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1R", 0, 7,
    7, 458843, (s32)btlevtcmd_SetDiveSound, -2, (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1L", (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1R", 0, 7,
    7, 262235, (s32)btlevtcmd_SetJumpSound, -2, (s32)"SFX_BTL_CHURINA_CONFUSE_JUMP1", (s32)"SFX_BTL_CHURINA_CONFUSE_LANDING1", 524379, (s32)btlevtcmd_SetPartsWalkSound,
    -2, 2, (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1L", (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1R", 0, 15, 13, 524379,
    (s32)btlevtcmd_SetPartsRunSound, -2, 2, (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1L", (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1R", 0, 7, 7,
    524379, (s32)btlevtcmd_SetPartsDiveSound, -2, 2, (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1L", (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1R", 0, 7,
    7, 327771, (s32)btlevtcmd_SetPartsJumpSound, -2, 2, (s32)"SFX_BTL_CHURINA_CONFUSE_JUMP1", (s32)"SFX_BTL_CHURINA_CONFUSE_LANDING1", 524379,
    (s32)btlevtcmd_SetPartsWalkSound, -2, 3, (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1L", (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1R", 0, 15, 13,
    524379, (s32)btlevtcmd_SetPartsRunSound, -2, 3, (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1L", (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1R", 0, 7,
    7, 524379, (s32)btlevtcmd_SetPartsDiveSound, -2, 3, (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1L", (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1R", 0,
    7, 7, 327771, (s32)btlevtcmd_SetPartsJumpSound, -2, 3, (s32)"SFX_BTL_CHURINA_CONFUSE_JUMP1", (s32)"SFX_BTL_CHURINA_CONFUSE_LANDING1",
    524379, (s32)btlevtcmd_SetPartsWalkSound, -2, 4, (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1L", (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1R", 0, 15,
    13, 524379, (s32)btlevtcmd_SetPartsRunSound, -2, 4, (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1L", (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1R", 0,
    7, 7, 524379, (s32)btlevtcmd_SetPartsDiveSound, -2, 4, (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1L", (s32)"SFX_BTL_CHURINA_CONFUSE_MOVE1R",
    0, 7, 7, 327771, (s32)btlevtcmd_SetPartsJumpSound, -2, 4, (s32)"SFX_BTL_CHURINA_CONFUSE_JUMP1",
    (s32)"SFX_BTL_CHURINA_CONFUSE_LANDING1", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125,
    -29999999, 40, 131126, -29999998, 20, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, 20, 393307, (s32)btlevtcmd_SetPartsPos, -2, 2, -30000000, -29999999,
    -29999998, 393307, (s32)btlevtcmd_SetPartsRotate, -2, 2, 0, 180, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"PCH_A3_1", 262235, (s32)btlevtcmd_OffPartsAttribute, -2,
    2, 50331648, 983131, (s32)evt_eff, (s32)"", (s32)"bomb", 0, -30000000,
    -29999999, -29999998, -229998976, 0, 0, 0, 0, 0,
    0, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CHURINA_CONFUSE1", -250000000, 0,
    -250000000, 110, 65545, 30, 262235, (s32)btlevtcmd_SetPartsFallAccel, -2, 2,
    -229999693, 393307, (s32)btlevtcmd_GetPartsPos, -2, 2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_FallPartsPosition, -2,
    2, -30000000, -29999999, -29999998, 25, 393307, (s32)btlevtcmd_SetPartsRotate, -2,
    2, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 2,
    43, 112, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    131125, -29999999, 20, 131126, -29999998, 10, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -2, -30000000, 10, 393307, (s32)btlevtcmd_SetPartsPos, -2, 3, -30000000,
    -29999999, -29999998, 393307, (s32)btlevtcmd_SetPartsRotate, -2, 3, 0, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 3, (s32)"PCH_A3_2", 262235, (s32)btlevtcmd_OffPartsAttribute,
    -2, 3, 50331648, 983131, (s32)evt_eff, (s32)"", (s32)"bomb", 0,
    -30000000, -29999999, -29999998, -229998976, 0, 0, 0, 0,
    0, 0, 0, 110, 65545, 30, 262235, (s32)btlevtcmd_SetPartsFallAccel,
    -2, 3, -229999693, 393307, (s32)btlevtcmd_GetPartsPos, -2, 3, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 458843,
    (s32)btlevtcmd_FallPartsPosition, -2, 3, -30000000, -29999999, -29999998, 25, 393307,
    (s32)btlevtcmd_SetPartsRotate, -2, 3, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 3, 43, 112, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131125, -29999999, 30, 131125, -29999998, 10,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, -10, 393307, (s32)btlevtcmd_SetPartsPos, -2,
    4, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_SetPartsRotate, -2, 4,
    0, 180, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 4, (s32)"PCH_A3_3",
    262235, (s32)btlevtcmd_OffPartsAttribute, -2, 4, 50331648, 983131, (s32)evt_eff, (s32)"",
    (s32)"bomb", 0, -30000000, -29999999, -29999998, -229998976, 0, 0,
    0, 0, 0, 0, 0, 110, 65545, 30,
    262235, (s32)btlevtcmd_SetPartsFallAccel, -2, 4, -229999693, 393307, (s32)btlevtcmd_GetPartsPos, -2,
    4, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999,
    -29999998, 458843, (s32)btlevtcmd_FallPartsPosition, -2, 4, -30000000, -29999999, -29999998,
    25, 393307, (s32)btlevtcmd_SetPartsRotate, -2, 4, 0, 0, 0,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 4, 43, 112, 65545, 85,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    0, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 1, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 2, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3,
    1, 786523, (s32)btlevtcmd_SetPartsBlur, -2, 1, 255, 255, 255,
    255, 100, 100, 100, 50, 1, 262235, (s32)btlevtcmd_OnPartsAttribute,
    -2, 1, 67108864, 786523, (s32)btlevtcmd_SetPartsBlur, -2, 2, 255,
    255, 255, 255, 100, 100, 100, 50, 1,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, 2, 67108864, 786523, (s32)btlevtcmd_SetPartsBlur, -2,
    3, 255, 255, 255, 255, 100, 100, 100,
    50, 1, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 3, 67108864, 786523,
    (s32)btlevtcmd_SetPartsBlur, -2, 4, 255, 255, 255, 255, 100,
    100, 100, 50, 1, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 4,
    67108864, 110, 65545, 40, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_GetStageSize, -29999995, -250000000, -250000000, 131128, -29999995, 3, 131122,
    -30000000, 0, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, -29999995, 458843,
    (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998, -229996928, -29999993, 196699,
    (s32)evt_btl_camera_set_mode, 0, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, -30000000, 90,
    500, -30000000, 60, 0, -29999993, 0, 112, 110,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 65545, 40, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 42, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_GetStageSize, -29999995, -250000000, -250000000, 131128, -29999995,
    3, 131122, -30000000, 0, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    -29999995, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 655451, (s32)btlevtcmd_DivePosition, -2,
    -30000000, -29999999, -29999998, 0, 0, 2, 0, -1,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -30000000,
    40, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 20,
    -1, 131126, -30000000, 60, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    180, 0, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    20, -1, 131125, -30000000, 40, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, 0, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 20, -1, 131126, -30000000, 60, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 180, 0, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 20, -1, 131125, -30000000, 40, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 20, -1, 983131, (s32)evt_eff, (s32)"",
    (s32)"bomb", 0, -30000000, -29999999, -29999998, -229998976, 0, 0,
    0, 0, 0, 0, 0, 262235, (s32)btlevtcmd_OffPartsAttribute, -2,
    1, 67108864, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 0, 112,
    110, 131122, -29999994, 2, 262235, (s32)btlevtcmd_SetPartsFallAccel, -2, -29999994,
    -229999284, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999994, 42, 393307, (s32)btlevtcmd_GetPartsPos,
    -2, -29999994, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize, -29999995,
    -250000000, -250000000, 131128, -29999995, 3, 131122, -30000000, 0,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, -29999995, 262235, (s32)btlevtcmd_SetPartsMoveSpeed, -2,
    -29999994, -229996928, 720987, (s32)btlevtcmd_DivePartsPosition, -2, -29999994, -30000000, -29999999,
    -29999998, 0, 0, 2, 0, -1, 393307, (s32)btlevtcmd_GetPartsPos,
    -2, -29999994, -30000000, -29999999, -29999998, 131125, -30000000, 60,
    524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999994, -30000000, -29999999, -29999998, 25,
    -1, 131126, -30000000, 90, 393307, (s32)btlevtcmd_SetPartsRotate, -2, -29999994,
    0, 180, 0, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999994, -30000000,
    -29999999, -29999998, 25, -1, 131125, -30000000, 60, 393307,
    (s32)btlevtcmd_SetPartsRotate, -2, -29999994, 0, 0, 0, 524379, (s32)btlevtcmd_JumpPartsPosition,
    -2, -29999994, -30000000, -29999999, -29999998, 25, -1, 131126,
    -30000000, 90, 393307, (s32)btlevtcmd_SetPartsRotate, -2, -29999994, 0, 180,
    0, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999994, -30000000, -29999999, -29999998,
    25, -1, 131126, -30000000, 30, 393307, (s32)btlevtcmd_SetPartsRotate, -2,
    -29999994, 0, 180, 0, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999994,
    -30000000, -29999999, -29999998, 25, -1, 131125, -30000000, 30,
    393307, (s32)btlevtcmd_SetPartsRotate, -2, -29999994, 0, 0, 0, 524379,
    (s32)btlevtcmd_JumpPartsPosition, -2, -29999994, -30000000, -29999999, -29999998, 25, -1,
    983131, (s32)evt_eff, (s32)"", (s32)"bomb", 0, -30000000, -29999999, -29999998,
    -229998976, 0, 0, 0, 0, 0, 0, 0,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, 2, 50331648, 262235, (s32)btlevtcmd_OffPartsAttribute, -2,
    2, 67108864, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 0, 112,
    110, 131122, -29999994, 3, 262235, (s32)btlevtcmd_SetPartsFallAccel, -2, -29999994,
    -229999284, 65545, 20, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999994, 42,
    393307, (s32)btlevtcmd_GetPartsPos, -2, -29999994, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_GetStageSize, -29999995, -250000000, -250000000, 131128, -29999995, 3, 131122,
    -30000000, 0, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, -29999995, 262235,
    (s32)btlevtcmd_SetPartsMoveSpeed, -2, -29999994, -229996928, 720987, (s32)btlevtcmd_DivePartsPosition, -2, -29999994,
    -30000000, -29999999, -29999998, 0, 0, 2, 0, -1,
    393307, (s32)btlevtcmd_GetPartsPos, -2, -29999994, -30000000, -29999999, -29999998, 131126,
    -30000000, 80, 393307, (s32)btlevtcmd_SetPartsRotate, -2, -29999994, 0, 180,
    0, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999994, -30000000, -29999999, -29999998,
    25, -1, 131125, -30000000, 160, 393307, (s32)btlevtcmd_SetPartsRotate, -2,
    -29999994, 0, 0, 0, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999994,
    -30000000, -29999999, -29999998, 40, -1, 131126, -30000000, 40,
    393307, (s32)btlevtcmd_SetPartsRotate, -2, -29999994, 0, 180, 0, 524379,
    (s32)btlevtcmd_JumpPartsPosition, -2, -29999994, -30000000, -29999999, -29999998, 15, -1,
    131126, -30000000, 60, 393307, (s32)btlevtcmd_SetPartsRotate, -2, -29999994, 0,
    180, 0, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999994, -30000000, -29999999,
    -29999998, 20, -1, 131125, -30000000, 20, 393307, (s32)btlevtcmd_SetPartsRotate,
    -2, -29999994, 0, 0, 0, 524379, (s32)btlevtcmd_JumpPartsPosition, -2,
    -29999994, -30000000, -29999999, -29999998, 20, -1, 983131, (s32)evt_eff,
    (s32)"", (s32)"bomb", 0, -30000000, -29999999, -29999998, -229998976, 0,
    0, 0, 0, 0, 0, 0, 262235, (s32)btlevtcmd_OnPartsAttribute,
    -2, 3, 50331648, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 3, 67108864,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 0, 112, 110, 131122,
    -29999994, 4, 262235, (s32)btlevtcmd_SetPartsFallAccel, -2, -29999994, -229999284, 65545,
    60, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999994, 42, 393307, (s32)btlevtcmd_GetPartsPos,
    -2, -29999994, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize, -29999995,
    -250000000, -250000000, 131128, -29999995, 3, 131122, -30000000, 0,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, -29999995, 262235, (s32)btlevtcmd_SetPartsMoveSpeed, -2,
    -29999994, -229996928, 720987, (s32)btlevtcmd_DivePartsPosition, -2, -29999994, -30000000, -29999999,
    -29999998, 0, 0, 2, 0, -1, 393307, (s32)btlevtcmd_GetPartsPos,
    -2, -29999994, -30000000, -29999999, -29999998, 131125, -30000000, 30,
    524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999994, -30000000, -29999999, -29999998, 10,
    -1, 131125, -30000000, 30, 393307, (s32)btlevtcmd_SetPartsRotate, -2, -29999994,
    0, 0, 0, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999994, -30000000,
    -29999999, -29999998, 10, -1, 131126, -30000000, 30, 393307,
    (s32)btlevtcmd_SetPartsRotate, -2, -29999994, 0, 180, 0, 524379, (s32)btlevtcmd_JumpPartsPosition,
    -2, -29999994, -30000000, -29999999, -29999998, 10, -1, 131126,
    -30000000, 30, 393307, (s32)btlevtcmd_SetPartsRotate, -2, -29999994, 0, 180,
    0, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999994, -30000000, -29999999, -29999998,
    10, -1, 131126, -30000000, 30, 393307, (s32)btlevtcmd_SetPartsRotate, -2,
    -29999994, 0, 180, 0, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999994,
    -30000000, -29999999, -29999998, 10, -1, 131126, -30000000, 30,
    393307, (s32)btlevtcmd_SetPartsRotate, -2, -29999994, 0, 180, 0, 524379,
    (s32)btlevtcmd_JumpPartsPosition, -2, -29999994, -30000000, -29999999, -29999998, 10, -1,
    131125, -30000000, 30, 393307, (s32)btlevtcmd_SetPartsRotate, -2, -29999994, 0,
    0, 0, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999994, -30000000, -29999999,
    -29999998, 10, -1, 131126, -30000000, 30, 393307, (s32)btlevtcmd_SetPartsRotate,
    -2, -29999994, 0, 180, 0, 524379, (s32)btlevtcmd_JumpPartsPosition, -2,
    -29999994, -30000000, -29999999, -29999998, 10, -1, 983131, (s32)evt_eff,
    (s32)"", (s32)"bomb", 0, -30000000, -29999999, -29999998, -229998976, 0,
    0, 0, 0, 0, 0, 0, 262235, (s32)btlevtcmd_OnPartsAttribute,
    -2, 4, 50331648, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 4, 67108864,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 3, 0, 112, 65539, 9,
    131122, -30000000, 0, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -29999999,
    131125, -30000000, -29999999, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -29999999,
    131125, -30000000, -29999999, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -29999999,
    131125, -30000000, -29999999, 262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -29999999,
    131125, -30000000, -29999999, 131097, -30000000, 0, 65545, 1,
    65540, 9, 33, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_CHURINA_CONFUSE1", 0, 131122,
    -29999990, 0, 131122, -29999985, 0, 65539, 10, 393307,
    (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256, -29999994, 131097, -29999994,
    1, 131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    33, 131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    33, 131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    33, 65540, 50, 33, 196699, (s32)btlevtcmd_AcGetOutputParam, 1, -30000000,
    196699, (s32)_make_madowase_weapon, -29999988, -30000000, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102,
    -30000000, 2, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988,
    131328, -29999995, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131101, -29999994,
    0, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 131125,
    -29999985, 1, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994, 33, 32,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 256, -29999995,
    33, 65539, 50, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131097,
    -29999997, -1, 131125, -29999990, 1, 65540, 10, 33,
    131096, -29999985, 0, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 33,
    65539, 80, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PCH_B_1", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 80, 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999847, 110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CHURINA_CONFUSE1_2", -250000000, 0,
    -250000000, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 5, 0, 196699,
    (s32)btlevtcmd_GetFaceDirection, -2, -29999995, 131127, -29999995, 9, 65541, 40,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, -29999995, 65545, 1,
    6, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999995, 131127, -29999995, 36,
    65541, 20, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, -29999995,
    65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 112, 110, 393307, (s32)btlevtcmd_ACRStart, -2, 45, 59,
    59, 0, 112, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 60, -1, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 65570,
    -29999994, 65577, 2, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0,
    0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_Y_1", 196699,
    (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 65546, 300, 65627, (s32)evt_audience_ap_recovery, 65627,
    (s32)btlevtcmd_InviteApInfoReport, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 327771, (s32)btlevtcmd_AddRotate,
    -2, 0, 180, 0, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    0, 0, 2, 0, -1, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, 0, 42, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 65627, (s32)evt_audience_acrobat_notry, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_R_2", 327771, (s32)btlevtcmd_AddRotate, -2,
    0, 180, 0, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 0,
    0, 2, 0, -1, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 49, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2,
    65630, (s32)btldefaultevt_SuitoruBadgeEffect, 458843, (s32)btlevtcmd_SetWalkSound, -2, (s32)"SFX_PARTY_BATTLE_MOVE1L", (s32)"SFX_PARTY_BATTLE_MOVE1R", 0,
    15, 13, 458843, (s32)btlevtcmd_SetRunSound, -2, (s32)"SFX_PARTY_BATTLE_MOVE1L", (s32)"SFX_PARTY_BATTLE_MOVE1R", 0,
    7, 7, 458843, (s32)btlevtcmd_SetDiveSound, -2, (s32)"SFX_PARTY_BATTLE_MOVE1L", (s32)"SFX_PARTY_BATTLE_MOVE1R", 0,
    7, 7, 262235, (s32)btlevtcmd_SetJumpSound, -2, (s32)"SFX_PARTY_BATTLE_JUMP1", (s32)"SFX_PARTY_BATTLE_LANDING1", 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 partyChuchurinaAttack_ItemSteal[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 131122, -29999986, 0,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)partyWeapon_ChuchurinaItemSteal, 256, -29999995,
    131096, -29999995, 5, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 196699, (s32)btlevtcmd_GetWidth, -29999997, -29999985,
    131128, -29999985, 2, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, -29999985, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 20, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999,
    -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)partyWeapon_ChuchurinaItemSteal,
    256, -29999995, 2, 33, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 196699, (s32)btlevtcmd_GetWidth, -29999997,
    -29999985, 131127, -29999985, 2, 131128, -29999985, 3, 131125,
    -29999985, 10, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, -29999985, 131125, -29999998,
    8, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 0, 196699,
    (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, 1,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 350,
    65546, 200, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_K_1", 65545,
    6, 131097, -29999995, 1, 65545, 20, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 43, 65570, -29999995, 65579, 4, 46,
    65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 65572, 1, 42, 49, 65545, 30,
    65627, (s32)btlevtcmd_StopAC, 65540, 90, 33, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 350, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, (s32)partyWeapon_ChuchurinaItemSteal, 256, -29999995, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_GetHeight, -2, -29999985, 131127,
    -29999985, 2, 131128, -29999985, 3, 131125, -29999999, -29999985,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 20, 983131, (s32)evt_eff, (s32)"",
    (s32)"kiss", 0, -30000000, -29999999, -29999998, 1, 0, 0,
    0, 0, 0, 0, 0, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BTL_CHURINA_KISS1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_OnUnitFlag, -29999997, 33554432,
    65545, 20, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_Z_1", 196699,
    (s32)evt_btl_camera_set_mode, 0, 3, 327771, (s32)btlevtcmd_AnimeFlagOnOff, -2, 1, 256,
    1, 65545, 1, 65627, (s32)mono_capture_event, 131165, (s32)main_evt, -29999987,
    107, 65627, (s32)mono_on, 109, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699,
    (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 262235, (s32)_get_itemsteal_param, -29999997, -30000000, -29999999,
    589915, (s32)btlevtcmd_AcSetParamAll, 1, -30000000, 2, 2, -29999999, -250000000,
    -250000000, -250000000, 131163, (s32)btlevtcmd_AcSetFlag, 0, 327771, (s32)btlevtcmd_SetupAC, -2,
    15, 1, 0, 65545, 22, 131163, (s32)btlevtcmd_StartAC, 1,
    65627, (s32)btlevtcmd_ResultAC, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 131102, -29999994, 2,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_A4_1", 33, 65545, 35,
    196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_CHURINA_EYE1", 0, 65545, 47, 327771, (s32)btlevtcmd_GetPos,
    -29999997, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_GetWidth, -29999997, -29999985,
    131128, -29999985, 2, 131125, -30000000, -29999985, 196699, (s32)btlevtcmd_GetHeight,
    -29999997, -29999985, 131125, -29999999, -29999985, 131125, -29999999, 5,
    131125, -29999998, 8, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 16, -1, 131163,
    (s32)btlevtcmd_GetResultAC, -29999994, 262235, (s32)_chuchu_item_steal, -29999997, -29999986, -29999994, 131096,
    -29999986, 0, 131163, (s32)btlevtcmd_JumpContinue, -2, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PCH_F_1", 65545, 22, 107, 65627, (s32)mono_off, 65631,
    -29999987, 109, 65545, 20, 196699, (s32)btlevtcmd_OffUnitFlag, -29999997, 33554432,
    196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_R_2", 327771, (s32)btlevtcmd_AddRotate, -2,
    0, 180, 0, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 0,
    0, 2, 0, -1, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 65540, 99, 33, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997,
    0, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_CHURINA_HEARTCATCH1", 0, 196699,
    (s32)btlevtcmd_OffUnitFlag, -29999997, 33554432, 107, 65627, (s32)mono_off, 65631, -29999987,
    109, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 50, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999,
    -29999998, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999693, 107, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PCH_A3_1", 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 10,
    0, 65541, 18, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0,
    20, 65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 0, 0,
    109, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30,
    -1, 65539, 90, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 131097, -29999986, 0, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_GetHeight, -2, -29999995,
    131125, -29999999, -29999995, 131125, -29999999, 5, 393307, (s32)btlevtcmd_BtlIconEntryItemId,
    -29999986, -30000000, -29999999, -29999998, -29999992, 65647, -29999985, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 180, 0, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000,
    -29999999, -29999998, 0, 0, 2, 0, -1, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 112, 65539, 91,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_GetHeight,
    -2, -29999995, 131125, -29999999, -29999995, 131125, -29999999, 5,
    327771, (s32)btlevtcmd_BtlIconSetPosition, -29999992, -30000000, -29999999, -29999998, 131178, -29999985,
    -30000000, 131097, -30000000, 0, 65545, 1, 65540, 91,
    33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_A2_2", 65545, 4,
    196699, (s32)btlevtcmd_AnnounceSetParam, 0, -29999986, 393307, (s32)btlevtcmd_AnnounceMessage, 1, 0,
    0, (s32)"btl_msg_steal_item_get", 90, 131163, (s32)btlevtcmd_BtlIconDelete, -29999992, 32, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 180, 0, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000,
    -29999999, -29999998, 0, 0, 2, 0, -1, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 33, 65539, 99,
    65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 partyChuchurinaAttack_Kiss[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 131163, (s32)btlevtcmd_CommandPayWeaponCost, -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7,
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -2, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    250, 196699, (s32)btlevtcmd_GetUnitId, -2, -30000000, 131097, -30000000, -29999997,
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 33, 65630, (s32)unk_evt_803510ec, 131097,
    -30000000, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -29999997, -29999996, -2, -1,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -29999997, -29999985, 33, 131163,
    (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163, (s32)btlevtcmd_AcGetDifficulty,
    -30000000, 131126, -30000000, 3, 65570, -30000000, 65576, -3,
    131122, -30000000, 300, 131122, -29999999, 20, 131122, -29999998,
    20, 65572, -2, 131122, -30000000, 270, 131122, -29999999,
    18, 131122, -29999998, 22, 65572, -1, 131122, -30000000,
    240, 131122, -29999999, 17, 131122, -29999998, 24, 65572,
    0, 131122, -30000000, 210, 131122, -29999999, 16, 131122,
    -29999998, 25, 65572, 1, 131122, -30000000, 195, 131122,
    -29999999, 14, 131122, -29999998, 26, 65572, 2, 131122,
    -30000000, 180, 131122, -29999999, 13, 131122, -29999998, 27,
    42, 131122, -30000000, 150, 131122, -29999999, 12, 131122,
    -29999998, 30, 49, 589915, (s32)btlevtcmd_AcSetParamAll, 11, -30000000, 178,
    -29999999, -29999998, 12, 37, -250000000, 327771, (s32)btlevtcmd_AcSetGaugeParam, 36,
    72, 100, 100, 131163, (s32)btlevtcmd_AcSetFlag, 64, 327771, (s32)btlevtcmd_SetupAC,
    -2, 6, 1, 0, 65545, 22, 131163, (s32)btlevtcmd_StartAC,
    1, 110, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 196699,
    (s32)btlevtcmd_GetStatusMg, -2, -29999994, 196699, (s32)btlevtcmd_GetStatusMg, -29999997, -29999993, 131132,
    -29999994, 12, 131132, -29999993, 7, 327771, (s32)btlevtcmd_GetPos, -29999997,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, -29999994,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, -29999993, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, 235, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 112, 65627, (s32)btlevtcmd_ResultAC, 196699, (s32)btlevtcmd_AcGetOutputParam, 2,
    -29999995, 65570, -29999995, 65577, 10, 131122, -29999995, 2,
    65577, 7, 131122, -29999995, 1, 65577, 4, 131122,
    -29999995, 0, 42, 131122, -29999995, -1, 49, 131101,
    -29999995, 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_GetResultPrizeLv, -5, -29999995, -29999994, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994,
    -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994, 32,
    196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 33, 131163, (s32)btlevtcmd_GetResultAC, -29999994,
    65627, (s32)btlevtcmd_StopAC, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom,
    0, 350, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_K_1", 65545,
    6, 131101, -29999995, 0, 65630, (s32)unk_evt_803510ec, 131097, -30000000,
    0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999997, -29999996, 59, 33, 33,
    196699, (s32)btlevtcmd_GetStatusMg, -2, -29999994, 131132, -29999994, 16, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, -29999994, 196699, (s32)btlevtcmd_GetStatusMg, -2, -29999994, 131132, -29999994,
    40, 131125, -29999999, -29999994, 196699, (s32)btlevtcmd_GetFaceDirection, -29999997, -29999994,
    131127, -29999994, 45, 983131, (s32)evt_eff, 0, (s32)"kiss", 0,
    -30000000, -29999999, -29999998, -29999994, 0, 0, 0, 0,
    0, 0, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CHURINA_KISS1", -250000000,
    0, -250000000, 65545, 40, 393307, (s32)btlevtcmd_GetPartsPos, -29999997, -29999996,
    -29999988, -29999987, -29999986, 196699, (s32)btlevtcmd_GetHeight, -29999997, -29999995, 196699,
    (s32)btlevtcmd_GetStatusMg, -29999997, -29999994, 131132, -29999995, -29999994, 131125, -29999987,
    -29999995, 196699, (s32)btlevtcmd_AcGetOutputParam, 2, -29999995, 983131, (s32)evt_eff, (s32)"eff",
    (s32)"recovery", 0, -29999988, -29999987, -29999986, -29999995, 0, 0,
    0, 0, 0, 0, 0, 65644, -29999985, 65545,
    120, 262235, (s32)btlevtcmd_RecoverHp, -29999997, -29999996, -29999995, 109, 393307,
    (s32)btlevtcmd_ACRStart, -2, 0, 15, 15, 20, 196699, (s32)btlevtcmd_ACRGetResult,
    -29999994, -29999993, 65570, -29999994, 65577, 2, 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -29999988, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_Y_1", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete,
    -2, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 65546,
    300, 42, 65627, (s32)evt_audience_acrobat_notry, 49, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65630, (s32)unk_evt_803510ec, 131097, -30000000,
    0, 131163, (s32)btlevtcmd_ResetFaceDirection, -29999997, 131163, (s32)btlevtcmd_StartWaitEvent, -29999997, 33,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 chuchurina_appeal_event[] = {
    196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_MARIO_APPEAL1", -30000000, -29999999, -29999998,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_O_3", 131163, (s32)btlevtcmd_AudienceAppeal,
    -2, 196699, (s32)btlevtcmd_ftomsec, 45, -30000000, 65546, -30000000, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, 15, 131125, -29999999, 30, 196699, (s32)btlevtcmd_GetFaceDirection, -2,
    -29999986, 131127, -29999986, 45, 983131, (s32)evt_eff, (s32)"", (s32)"kiss",
    0, -30000000, -29999999, -29999998, -29999986, 0, 0, 0,
    0, 0, 0, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CHURINA_KISS1",
    -250000000, 0, -250000000, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 65545,
    30, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static EVT_BEGIN(party_win_reaction)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PCH_Y_1"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 1)
    WAIT_MS(333)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 43)
    RETURN
EVT_END()

static s32 attack_audience_event[] = {
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize,
    -29999997, -250000000, -250000000, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999996, 131122,
    -29999992, -29999997, 131127, -29999992, -29999996, 131127, -29999992, -1,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 524379, (s32)btlevtcmd_MovePosition, -2, -29999992, -29999999, -29999998, 0,
    -1, 0, 65545, 20, 327771, (s32)_get_attack_aud_no, -29999997, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageAudienceAreaSize, -29999996, -250000000, -250000000, 196699,
    (s32)btlevtcmd_GetFaceDirection, -2, -29999995, 131122, -29999994, -29999996, 131127, -29999994,
    -29999995, 131127, -29999994, -1, 327771, (s32)btlevtcmd_SetPos, -2, -29999994,
    -29999999, -29999998, 196699, (s32)evt_btl_camera_set_mode, 0, 13, 327771, (s32)evt_btl_camera_set_homing_unit_audience,
    0, -2, 1, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_btl_camera_set_zoom, 0, 100, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    24, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PCH_A4_1", 196699, (s32)btlevtcmd_ftof, 52, -30000000, 65545,
    -30000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PCH_Y_1", 196699, (s32)btlevtcmd_ftof,
    7, -30000000, 65545, -30000000, 196699, (s32)_attack_aud, -29999997, 0,
    196699, (s32)evt_btl_camera_set_mode, 0, 3, 65647, -29999985, 65546, 1500,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546, 1000, 112, 196699,
    (s32)btlevtcmd_ftof, 35, -30000000, 65545, -30000000, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379, (s32)btlevtcmd_MovePosition,
    -2, -29999994, -29999999, -29999998, 0, -1, 0, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -2,
    -29999992, -29999999, -29999998, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 0, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
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

static EVT_BEGIN(main_evt)
    CALL(mono_main)
    RETURN
EVT_END()

#define UNIT_TEX(u) (*(smartEntry**)((u8*)(u) + 0x318))

s32 mono_alpha;

USER_FUNC(_chuchu_make_extra_work_area) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    unit->countersetWeapon = BattleAlloc(sizeof(BattleWeapon));
    return EVT_RETURN_DONE;
}

#define ADD_WEAPON(w)                                                                              \
    command->mWeaponTable[*count].mIndex = -1;                                                     \
    command->mWeaponTable[*count].mItem = 0;                                                       \
    command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)(w);                              \
    command->mWeaponTable[*count].field_0x4 = 0;                                                   \
    command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;       \
    command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name); \
    (*count)++;

static void __makeTechMenuFunc(BattleWorkCommand* command, s32* count) {
    s32 techLv;

    techLv = partyGetTechLv(BattleTransPartyId(BattleGetPartyPtr(_battleWorkPointer)->currentKind));
    ADD_WEAPON(partyWeapon_ChuchurinaNormalAttackLeftLast)
    if (techLv >= 0) {
        ADD_WEAPON(partyWeapon_ChuchurinaItemSteal)
    }
    if (techLv >= 1) {
        ADD_WEAPON(partyWeapon_ChuchurinaMadowaseAttack)
    }
    if (techLv >= 2) {
        ADD_WEAPON(partyWeapon_ChuchurinaKiss)
    }
}

USER_FUNC(_get_binta_hit_position) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    Vec pos;
    s32 id, targetId, dir;
    s32 outZ, outX, outY;

    id = evtGetValue(event, args[0]);
    targetId = evtGetValue(event, args[1]);
    evtGetValue(event, args[2]);
    outX = args[3];
    outY = args[4];
    outZ = args[5];
    BattleGetUnitPtr(wp, BattleTransID(event, id));
    unit = BattleGetUnitPtr(wp, BattleTransID(event, targetId));
    dir = unit->faceDirection;
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x += dir * (unit->bintaHitOffset.x * unit->mSizeMultiplier);
    pos.y += unit->bintaHitOffset.y * unit->mSizeMultiplier;
    pos.z += unit->bintaHitOffset.z * unit->mSizeMultiplier;
    evtSetFloat(event, outX, pos.x);
    evtSetFloat(event, outY, pos.y);
    evtSetFloat(event, outZ, pos.z);
    return EVT_RETURN_DONE;
}

USER_FUNC(_make_madowase_weapon) {
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
    ((u8*)weapon)[0x84] = value;
    evtSetValue(event, index, (s32)weapon);
    return EVT_RETURN_DONE;
}

USER_FUNC(_get_itemsteal_param) {
    BattleWork* wp;
    s32* args = event->args;
    BattleUnit* unit;
    s32 id, out1, out2, rate, resist;

    id = evtGetValue(event, args[0]);
    out1 = args[1];
    wp = _battleWorkPointer;
    out2 = args[2];
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    rate = 80 - (*(u8*)((u8*)wp + 0x1CBD) - 3) * 20;
    if (rate <= 5) {
        rate = 5;
    }
    resist = 100 - unit->mKindParams->itemStealParam;
    evtSetValue(event, out1, rate);
    evtSetValue(event, out2, resist);
    return EVT_RETURN_DONE;
}

USER_FUNC(_chuchu_item_steal) {
    ItemDropData* table;
    BattleWork* wp;
    s32 flag;
    s32 out;
    BattleUnit* unit;
    s32 id;
    u16 item;
    s32* args;

    args = event->args;
    wp = _battleWorkPointer;
    id = evtGetValue(event, args[0]);
    out = args[1];
    flag = evtGetValue(event, args[2]);
    unit = BattleGetUnitPtr(_battleWorkPointer, BattleTransID(event, id));
    item = unit->heldItem;
    if (item == 0) {
        s32 total, r;
        u32 pick;
        if (unit->dropTable != NULL) {
            irand(100);
        }
        table = unit->dropTable;
        if (table == NULL) {
            pick = 0;
        } else {
            ItemDropData* p;
            if (table != NULL) {
                s32 i;
                total = 0;
                for (i = 0; table[i].holdWeight > 0 || table[i].type != 0; i++) {
                    total += table[i].holdWeight;
                }
                if (total > 0) {
                    r = irand(total);
                    for (;; table++) {
                        r -= table->holdWeight;
                        if (r < 0) {
                            pick = table->type;
                            goto done;
                        }
                    }
                }
            }
            pick = 0;
        }
    done:
        item = pick;
        if (item == 0) {
            item = 0x79;
        }
    }
    if (!(flag & 2)) {
        evtSetValue(event, out, 0);
        return EVT_RETURN_DONE;
    }
    if (pouchGetItem((u16)item) == 0) {
        evtSetValue(event, out, 0);
        return EVT_RETURN_DONE;
    }
    unit->heldItem = 0;
    if (BtlUnit_CheckUnitFlag(unit, 0x40000000)) {
        BtlUnit_OffUnitFlag(unit, 0x40000000);
        if (unit->groupSetupId >= 0) {
            s32* arr = *(s32**)((u8*)wp->fbatInfo + 0xC);
            arr[unit->groupSetupId + 7] = 0;
            arr[unit->groupSetupId + 0x17] = 0;
        }
    } else if (unit->groupSetupId >= 0) {
        s32* arr = *(s32**)((u8*)wp->fbatInfo + 0xC);
        arr[unit->groupSetupId + 7] = 0;
    }
    if ((u16)(s32)item >= 0xF0 && (u16)(s32)item < 0x153) {
        if (unit->currentKind == 0xDE) {
            BtlUnit_EquipItem(unit, 3, 0);
        } else if (unit->currentKind >= 0xE0 && unit->currentKind < 0xE7) {
            BtlUnit_EquipItem(unit, 5, 0);
        } else {
            BtlUnit_EquipItem(unit, 1, 0);
        }
    }
    evtSetValue(event, out, (u16)item);
    return EVT_RETURN_DONE;
}

void mono_capture(CameraId camId, void* param) {
    BattleUnit* unit = param;
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);
    UNIT_TEX(unit) = smartAlloc(GXGetTexBufferSize(0x260, 0x1E0, 1, 0, 0), 1);
    GXSetTexCopySrc(0, 0, 0x260, 0x1E0);
    GXSetTexCopyDst(0x260, 0x1E0, 1, 0);
    GXCopyTex(UNIT_TEX(unit)->address, 0);
    GXPixModeSync();
    *(u32*)((u8*)part + 0x204) &= ~0x100;
}

void mono_disp(CameraId camId, BattleUnit* unit) {
    CameraEntry* cam = camGetPtr(camId);
    smartEntry* e = UNIT_TEX(unit);
    void* buf = NULL;
    GXTexObj tex;
    if (e != NULL) {
        buf = e->address;
    }
    if (buf != NULL) {
        GXInitTexObj(&tex, buf, 0x260, 0x1E0, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&tex, GX_TEXMAP0);
        GXLoadPosMtxImm(cam->view, 0);
        GXSetCurrentMtx(0);
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
        GXSetTevColor(GX_TEVREG0, (GXColor){0xFF, 0xFF, 0xFF, mono_alpha});
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetZCompLoc(GX_TRUE);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(-304.0f, 240.0f, 0.0f);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(304.0f, 240.0f, 0.0f);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(304.0f, -240.0f, 0.0f);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(-304.0f, -240.0f, 0.0f);
        GXTexCoord2f32(0.0f, 1.0f);
        {
            BattleUnit* party = BattleGetPartyPtr(_battleWorkPointer);
            if (party != NULL) {
                BattleUnitPart* p = BtlUnit_GetPartsPtr(party, 1);
                CameraId cur = camGetCurNo();
                camSetCurNo(CAMERA_3D);
                btlUnitPartsDisp(CAMERA_3D, p);
                camSetCurNo(cur);
            }
        }
    }
}

USER_FUNC(mono_main) {
    BattleUnit* unit;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    dispEntry(CAMERA_2D, 910.0f, 0, (DispCallback)mono_disp, unit);
    return EVT_RETURN_BLOCK;
}

USER_FUNC(mono_capture_event) {
    BattleUnit* unit;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BtlUnit_GetPartsPtr(unit, 1);
    dispEntry(CAMERA_2D, 910.0f, 0, (DispCallback)mono_capture, unit);
    return EVT_RETURN_DONE;
}

USER_FUNC(mono_on) {
    if (isFirstCall) {
        mono_alpha = 0;
    }
    mono_alpha += 10;
    if (mono_alpha > 255) {
        mono_alpha = 255;
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(mono_off) {
    BattleUnit* unit;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    mono_alpha -= 10;
    if (mono_alpha < 0) {
        mono_alpha = 0;
        BtlUnit_GetPartsPtr(unit, 1);
        if (UNIT_TEX(unit) != NULL) {
            smartFree(UNIT_TEX(unit));
        }
        UNIT_TEX(unit) = NULL;
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

// TODO: USER_FUNC(_chuchu_make_extra_work_area) { }

