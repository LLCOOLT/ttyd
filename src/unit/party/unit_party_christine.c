#include "battle/battle.h"
#include "battle/battle_database_common.h"
#include "battle/battle_monosiri.h"
#include "battle/battle_sub.h"
#include "driver/msgdrv.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_party.h"
#include "system.h"

void* monosiriInit(BattleUnitType kind, f32 x, f32 y);
void monosiriMain(void* work);
void monosiriClose(void* work);
BOOL monosiriCloseWait(void* work);
void monosiriExit(void* work);
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

USER_FUNC(_dictionary);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetUnitWork);
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
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(_set_hustle);
USER_FUNC(_monosiri_flag_on);
USER_FUNC(btlevtcmd_get_monosiri_msg_no);
static void __makeTechMenuFunc(BattleWorkCommand* command, s32* count);
static USER_FUNC(krb_get_dir);
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
extern s32 btlevtcmd_AcSetDifficulty[];
extern s32 btlevtcmd_AcSetFlag[];
extern s32 btlevtcmd_AcSetParamAll[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AnnounceMessage[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AudienceAppeal[];
extern s32 btlevtcmd_AudienceDeclareACResult[];
extern s32 btlevtcmd_AudienceDeclareAcrobatResult[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CommandCheckDamage[];
extern s32 btlevtcmd_CommandGetWeaponActionLv[];
extern s32 btlevtcmd_CommandGetWeaponAddress[];
extern s32 btlevtcmd_CommandPayWeaponCost[];
extern s32 btlevtcmd_CommandPreCheckDamage[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_GetBodyId[];
extern s32 btlevtcmd_GetFaceDirection[];
extern s32 btlevtcmd_GetHeight[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetMoveFrame[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_GetPosFloat[];
extern s32 btlevtcmd_GetResultAC[];
extern s32 btlevtcmd_GetResultCountAC[];
extern s32 btlevtcmd_GetResultPrizeLv[];
extern s32 btlevtcmd_GetRotate[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetStageAudienceAreaSize[];
extern s32 btlevtcmd_GetStageSize[];
extern s32 btlevtcmd_GetStatusMg[];
extern s32 btlevtcmd_GetTakeoffPosition[];
extern s32 btlevtcmd_InviteApInfoReport[];
extern s32 btlevtcmd_JumpContinue[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MarioJumpParam[];
extern s32 btlevtcmd_MarioJumpPosition[];
extern s32 btlevtcmd_MoveDirectionAdd[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultAC[];
extern s32 btlevtcmd_RunDataEventChild[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SetScale[];
extern s32 btlevtcmd_SetStayPose[];
extern s32 btlevtcmd_SetTalkPose[];
extern s32 btlevtcmd_SetupAC[];
extern s32 btlevtcmd_StartAC[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_StopAC[];
extern s32 btlevtcmd_TransStageFloorPosition[];
extern s32 btlevtcmd_WaitEventEnd[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_ac_timing_flag_onoff[];
extern s32 btlevtcmd_ac_timing_get_success_frame[];
extern s32 btlevtcmd_ftof[];
extern s32 btlevtcmd_ftomsec[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_audience_acrobat_notry[];
extern s32 evt_audience_ap_recovery[];
extern s32 evt_btl_camera_off_posoffset_manual[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_homing_unit_audience[];
extern s32 evt_btl_camera_set_homing_unitparts[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_posoffset[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_eff[];
extern s32 evt_eff64[];
extern s32 evt_eff_fukidashi[];
extern s32 evt_msg_print[];
extern s32 evt_snd_sfxon_3d[];
extern s32 mario_get_renzoku_count_max[];
extern s32 subset_attack_ready_jump_event[];
extern s32 unk_evt_803510ec[];
extern s32 weaponGetPowerFromPartyAttackLv[];

__declspec(section ".data") s32 lbl_80390B70[2];
__declspec(section ".data") s32 christine_negone_one_374[2];
__declspec(section ".data") s32 lbl_80390B80[2];
__declspec(section ".data") s32 christine_one_negone_373[2];
__declspec(section ".data") s32 lbl_80390B90[2];
__declspec(section ".data") s32 christine_negone_one_360[2];
__declspec(section ".data") s32 lbl_80390BA0[2];
__declspec(section ".data") s32 christine_one_negone_359[2];
PoseTableEntry pose_table_christine_stay[25];
static BattleDataEntry data_table[8];
BattleUnitKindPart unitpartsdata_Party_Christine[1];
BattleUnitKind unitdata_Party_Christine;
static s32 battle_entry_event[59];
static s32 init_event[51];
static s32 damage_event[16];
s32 partyWeapon_ChristineNormalAttack[48];
s32 partyWeapon_ChristineMonosiri[48];
s32 partyWeapon_ChristineRenzokuAttack[48];
s32 partyWeapon_ChristineKiss[48];
s32 partyChristineAttack_NormalAttack[824];
s32 christine_dictionary_event[26];
s32 partyChristineAttack_Monosiri[397];
s32 partyChristineAttack_RenzokuAttack[1071];
s32 partyChristineAttack_Kiss[546];
s32 christine_appeal_event[71];
static s32 party_win_reaction[14];
static s32 attack_audience_event[392];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static s32 attack_event[2];
static s32 wait_event[6];

__declspec(section ".data") s32 lbl_80390B70[] = {
    -1082130432, 1065353216,
};

__declspec(section ".data") s32 christine_negone_one_374[] = {
    -1082130432, 1065353216,
};

__declspec(section ".data") s32 lbl_80390B80[] = {
    1065353216, -1082130432,
};

__declspec(section ".data") s32 christine_one_negone_373[] = {
    1065353216, -1082130432,
};

__declspec(section ".data") s32 lbl_80390B90[] = {
    -1082130432, 1065353216,
};

__declspec(section ".data") s32 christine_negone_one_360[] = {
    -1082130432, 1065353216,
};

__declspec(section ".data") s32 lbl_80390BA0[] = {
    1065353216, -1082130432,
};

__declspec(section ".data") s32 christine_one_negone_359[] = {
    1065353216, -1082130432,
};

PoseTableEntry pose_table_christine_stay[] = {
    {9, "PKR_D_5"},
    {2, "PKR_D_5"},
    {3, "PKR_X_1"},
    {4, "PKR_D_2"},
    {5, "PKR_X_1"},
    {1, "PKR_N_1"},
    {27, "PKR_D_3"},
    {28, "PKR_S_1"},
    {37, "PKR_G_2"},
    {31, "PKR_G_1"},
    {39, "PKR_D_1"},
    {40, "PKR_W_1"},
    {42, "PKR_R_1"},
    {57, "PKR_D_2"},
    {56, "PKR_D_2"},
    {60, "PKR_D_4"},
    {61, "PKR_D_2"},
    {65, "PKR_T_1"},
    {52, "PKR_I_1"},
    {67, "PKR_C_1"},
    {66, "PKR_O_1"},
    {64, "PKR_X_1"},
    {49, "PKR_A_1"},
    {45, "PKR_G_1"},
    {69, "PKR_S_1"},
};

static BattleDataEntry data_table[] = {
    {5, christine_appeal_event},
    {6, attack_audience_event},
    {1, __makeTechMenuFunc},
    {48, btldefaultevt_Dummy},
    {64, party_win_reaction},
    {7, subset_attack_ready_jump_event},
    {47, btldefaultevt_avoid_counter_event},
    {0, NULL},
};

BattleUnitKindPart unitpartsdata_Party_Christine[] = {
    {1, "btl_un_christine", "c_pkr", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, 0x9, 0, pose_table_christine_stay},
};

BattleUnitKind unitdata_Party_Christine = {
    224,
    "btl_un_christine",
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
    20,
    10,
    24,
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
    13.0f,
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
    1,
    unitpartsdata_Party_Christine,
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
    CALL(btlevtcmd_SetMoveSoundDataWork, -2, STRING("SFX_PARTY_BATTLE_SUBMOVE1L"), STRING("SFX_PARTY_BATTLE_SUBMOVE1R"), 0, 9, 3, 0, 0)
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -2, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 6, 12, 16)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 9, 3)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
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

s32 partyWeapon_ChristineNormalAttack[] = {
    (s32)"btl_wn_pkr_normal", 22020096, 0, (s32)"msg_pkr_normal_jump", 1677721600, 1065353216, 16868402, (s32)weaponGetPowerFromPartyAttackLv,
    1, 1, 2, 2, 3, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, (s32)"msg_ac_zutsuki", 217095, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyChristineAttack_NormalAttack, 100, 131584, 0,
};

s32 partyWeapon_ChristineMonosiri[] = {
    (s32)"btl_wn_pkr_lv1", 22085632, 0, (s32)"msg_pkr_monosiri", 1677721600, 1065353216, 17130546, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870913, 770, (s32)"msg_ac_monoshiri", 131080, 2047, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyChristineAttack_Monosiri, 100, 0, 0,
};

s32 partyWeapon_ChristineRenzokuAttack[] = {
    (s32)"btl_wn_pkr_lv2", 22151168, 0, (s32)"msg_pkr_renzoku_zutsuki", 1677918208, 1065353216, 33907762, (s32)weaponGetPowerFromPartyAttackLv,
    1, 1, 2, 2, 3, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, (s32)"msg_ac_zutsuki", 151575, 12, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyChristineAttack_RenzokuAttack, 100, 328960, 327680,
};

s32 partyWeapon_ChristineKiss[] = {
    (s32)"btl_wn_pkr_lv3", 22216704, 0, (s32)"msg_pkr_nage_kiss", 1677983744, 1065353216, 17130546, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830240, 268435456, 770, (s32)"msg_ac_kiss", 131336, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1677852672, 0, 0, 0, (s32)partyChristineAttack_Kiss, 100, 328960, 0,
};

s32 partyChristineAttack_NormalAttack[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250,
    131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 327771,
    (s32)btlevtcmd_SetupAC, -2, 1, 1, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition,
    -2, -29999997, -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 458843, (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998,
    0, -29999986, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    -29999986, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 131163,
    (s32)btlevtcmd_StartAC, 1, 131122, -29999990, 0, 65539, 10, 131101,
    -29999990, 1, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 1048832,
    -29999995, 32, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256,
    -29999995, 33, 65570, -29999995, 65579, 2, 65579, 3,
    65579, 6, 65579, 4, 46, 65572, 1, 42,
    65546, 1000, 49, 131100, -29999990, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PKR_A_2B", 110, 65545, 5, 393307, (s32)btlevtcmd_ACRStart,
    -2, 0, 4, 4, 0, 112, 65545, 10,
    33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_J_1A", 107, 65545,
    15, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_KURI_ATTACK1", -250000000, 0, -250000000,
    109, 327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 131101,
    -29999990, 1, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 131125, -29999998, 5, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0,
    14, 0, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0,
    110, 65545, 15, 65541, 6, 196699, (s32)btlevtcmd_GetFaceDirection, -2,
    -30000000, 131127, -30000000, -30, 327771, (s32)btlevtcmd_AddRotate, -2, 0,
    0, -30000000, 65545, 1, 6, 112, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_PARTY_BATTLE_JUMP1", -250000000, 0, -250000000, 524379, (s32)btlevtcmd_MarioJumpPosition, -2,
    -30000000, -29999999, -29999998, 36, 3, 0, 32, 327771,
    (s32)btlevtcmd_SetRotateOffset, -2, 0, 14, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994,
    -29999993, 131096, -29999994, 2, 110, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2,
    -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000, 1, 0, 0, 0,
    112, 110, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 131096, -29999985, 1, 131122, -29999991, -15,
    32, 131122, -29999991, 15, 33, 327771, (s32)btlevtcmd_GetPosFloat, -2,
    -29999995, -29999994, -29999993, 131122, -29999992, 0, 65541, 36,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, -29999991, 65545, 1,
    6, 112, 32, 110, 327771, (s32)btlevtcmd_GetPosFloat, -2, -29999995,
    -29999994, -29999993, 131122, -29999992, 0, 65541, 36, 327771,
    (s32)btlevtcmd_GetPosFloat, -2, -29999988, -29999987, -29999986, 393307, (s32)krb_get_dir, -29999995,
    -29999994, -29999988, -29999987, -29999992, 327771, (s32)btlevtcmd_GetRotate, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_SetRotate, -2, -30000000, -29999999, -29999992,
    131124, -29999995, -29999988, 131124, -29999994, -29999987, 65545, 1,
    6, 112, 33, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 131125, -29999998, 5, 131122, -29999992, 36,
    393307, (s32)btlevtcmd_MarioJumpParam, -2, -30000000, -29999999, -29999998, -29999992, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_JUMP1", -250000000, 0, -250000000, 524379, (s32)btlevtcmd_MarioJumpPosition,
    -2, -30000000, -29999999, -29999998, -29999992, 0, 0, 33,
    131097, -29999995, 1, 131096, -29999995, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 33, 131096, -29999995, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 33, 131096, -29999995, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 33, 65627, (s32)btlevtcmd_StopAC, 131163, (s32)btlevtcmd_JumpContinue, -2,
    327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 0, 0, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PKR_S_1", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_MoveDirectionAdd, -2, -30000000, 30,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 20, -1,
    262235, (s32)btlevtcmd_MoveDirectionAdd, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 10, -1, 65546, 500, 65540,
    95, 33, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 1, 1, 131163, (s32)btlevtcmd_ac_timing_get_success_frame,
    -30000000, 131128, -30000000, 2, 65545, -30000000, 196699, (s32)btlevtcmd_ac_timing_flag_onoff,
    0, 1, 65627, (s32)btlevtcmd_ResultAC, 327771, (s32)btlevtcmd_SetScale, -2, -229998976,
    -229998976, -229998976, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 131103, -29999994, 2,
    393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256, -29999995, 131096,
    -29999990, 0, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult,
    -30000000, -1, 33, 65540, 90, 33, 131163, (s32)btlevtcmd_GetResultCountAC,
    -29999994, 131100, -29999994, 1, 107, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    0, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 65545, 10, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 109,
    393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131072, -29999995, 262235,
    (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999,
    -29999998, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000,
    -29999994, 131125, -29999990, 1, 65540, 10, 32, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996,
    131328, -29999995, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 33, 65539, 90,
    65627, (s32)btlevtcmd_StopAC, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65627, (s32)evt_audience_ap_recovery,
    65627, (s32)btlevtcmd_InviteApInfoReport, 110, 327771, (s32)btlevtcmd_GetRotate, -2, -250000000, -250000000,
    -29999994, 131098, -29999994, 0, 131127, -29999994, -1, 33,
    196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000, 131127, -29999994, -30000000, 131128,
    -29999994, 15, 131122, -29999993, 15, 65539, 20, 327771,
    (s32)btlevtcmd_AddRotate, -2, 0, 0, -29999994, 131126, -29999993, 1,
    65545, 1, 131101, -29999993, 1, 65540, 20, 33,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 112, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000, -29999999, -250000000, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 30, -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    8, -1, 65539, 95, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, 0, -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

EVT_BEGIN(christine_dictionary_event)
    LABEL(0)
    CALL(_dictionary, LW(3), LW(4))
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 6)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    RETURN
EVT_END()

s32 partyChristineAttack_Monosiri[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 131163,
    (s32)btlevtcmd_CommandPayWeaponCost, -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode,
    0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -2, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 350, 327771,
    (s32)evt_btl_camera_set_posoffset, 0, 40, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PKR_2A_1", 65546, 500, 65541, 2, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PKR_2A_2", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_KURI_LEARNED1", -250000000,
    0, -250000000, 65546, 400, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PKR_2A_3", 65546, 350, 6, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699,
    (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 589915, (s32)btlevtcmd_AcSetParamAll, -29999997, -29999996, -250000000,
    -250000000, -250000000, -250000000, -250000000, -250000000, 131163, (s32)btlevtcmd_AcSetFlag, 0,
    327771, (s32)btlevtcmd_SetupAC, -2, 21, 1, 0, 110, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 327771, (s32)evt_btl_camera_set_posoffset, 0, 0, 0,
    0, 112, 65545, 22, 131163, (s32)btlevtcmd_StartAC, 1, 65627,
    (s32)btlevtcmd_ResultAC, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 131102, -29999994, 2, 262235,
    (s32)btlevtcmd_GetResultPrizeLv, -5, 0, -29999994, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000,
    196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999,
    -29999998, 32, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult,
    -30000000, -1, 33, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 131103, -29999994,
    2, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 786523,
    (s32)evt_eff_fukidashi, 2, (s32)"", 0, 2, 0, -30000000, -29999999,
    -29999998, 30, 0, 56, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_KURI_FAIL_LEARNED1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_2A_4",
    65545, 56, 65540, 90, 33, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BTL_KURI_LEARNED2", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_2A_4", 65545,
    3, 65647, -29999985, 65545, 53, 112, 196699, (s32)btlevtcmd_ftof,
    0, -30000000, 196699, (s32)btlevtcmd_ftof, 53, -29999999, 393307, (s32)btlevtcmd_ACRStart,
    -2, -30000000, -29999999, -29999999, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994,
    -29999993, 131101, -29999994, 2, 65631, -29999985, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult,
    -29999988, 1, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PKR_Y_1", 196699, (s32)btlevtcmd_ftomsec, 28, -30000000, 65546, -30000000,
    32, 65627, (s32)evt_audience_acrobat_notry, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 33, 196699,
    (s32)btlevtcmd_SetTalkPose, -2, (s32)"PKR_2A_5", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"PKR_2A_5", 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 0, 0, 65628, (s32)christine_dictionary_event, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 0, 1, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 131163, (s32)evt_btl_camera_off_posoffset_manual, 0, 65539, 10,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131097, -30000000, 3,
    65545, 1, 65540, 10, 33, 262235, (s32)btlevtcmd_get_monosiri_msg_no, -29999997,
    -29999996, -30000000, 327771, (s32)evt_msg_print, 2, -30000000, 0, -2,
    131163, (s32)_monosiri_flag_on, -29999997, 196699, (s32)btlevtcmd_SetTalkPose, -2, (s32)"PKR_T_1", 196699,
    (s32)btlevtcmd_SetStayPose, -2, (s32)"PKR_S_1", 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 4,
    65539, 20, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131097,
    -30000000, 0, 65545, 1, 65540, 20, 33, 65539,
    90, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    1, 131163, (s32)evt_btl_camera_off_posoffset_manual, 0, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 partyChristineAttack_RenzokuAttack[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250,
    131163, (s32)evt_btl_camera_off_posoffset_manual, 0, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty,
    -2, -30000000, 327771, (s32)btlevtcmd_SetupAC, -2, 1, 1, 0,
    196699, (s32)btlevtcmd_ac_timing_flag_onoff, 1, 2, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition, -2,
    -29999997, -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_A_2B", 393307,
    (s32)btlevtcmd_ACRStart, -2, 0, 10, 10, 0, 65545, 10,
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 131163, (s32)btlevtcmd_StartAC, 1, 131122,
    -29999990, 0, 65539, 10, 131101, -29999990, 1, 393307,
    (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 1048832, -29999995, 32, 393307,
    (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256, -29999995, 33, 65570,
    -29999995, 65579, 2, 65579, 3, 65579, 6, 65579,
    4, 46, 65572, 1, 42, 65546, 1000, 49,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_J_1A", 262235, (s32)btlevtcmd_SetUnitWork, -2,
    3, 0, 131101, -29999990, 1, 327771, (s32)btlevtcmd_SetRotateOffset, -2,
    0, 14, 0, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 110, 65545, 15, 65541, 6, 196699, (s32)btlevtcmd_GetFaceDirection,
    -2, -30000000, 131127, -30000000, -30, 327771, (s32)btlevtcmd_AddRotate, -2,
    0, 0, -30000000, 65545, 1, 6, 112, 107,
    65545, 15, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_KURI_ATTACK2", -250000000, 0,
    -250000000, 109, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 131125, -29999998, 5, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_JUMP1",
    -250000000, 0, -250000000, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999,
    -29999998, 36, 3, 0, 32, 196699, (s32)btlevtcmd_ACRGetResult, -29999994,
    -29999993, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    131125, -29999998, 5, 131122, -29999992, 40, 393307, (s32)btlevtcmd_MarioJumpParam,
    -2, -30000000, -29999999, -29999998, -29999992, 327771, (s32)btlevtcmd_SetRotateOffset, -2,
    0, 14, 0, 110, 131101, -29999994, 2, 65545,
    20, 33, 327771, (s32)btlevtcmd_GetPosFloat, -2, -29999995, -29999994, -29999993,
    131122, -29999985, 0, 65541, -29999992, 327771, (s32)btlevtcmd_GetPosFloat, -2,
    -29999988, -29999987, -29999986, 393307, (s32)krb_get_dir, -29999995, -29999994, -29999988,
    -29999987, -29999985, 327771, (s32)btlevtcmd_GetRotate, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -29999991, 131125, -29999985, -29999991,
    327771, (s32)btlevtcmd_SetRotate, -2, -30000000, -29999999, -29999985, 131124, -29999995,
    -29999988, 131124, -29999994, -29999987, 65545, 1, 6, 112,
    107, 131101, -29999994, 2, 65545, 20, 33, 65545,
    15, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_KURI_ATTACK2", -250000000, 0, -250000000,
    109, 131101, -29999994, 2, 110, 196699, (s32)btlevtcmd_GetFaceDirection, -2,
    -29999995, 131127, -29999995, -18, 65541, 20, 327771, (s32)btlevtcmd_AddRotate,
    -2, 0, 0, -29999995, 65545, 1, 6, 112,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 20, 0, 110, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 983131, (s32)evt_eff64, (s32)"",
    (s32)"kemuri2_n64", 2, -30000000, -29999999, -29999998, 0, 0, 0,
    0, 0, 0, 0, 0, 112, 131122, -29999991,
    -29999992, 131126, -29999991, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2,
    -29999991, 110, 65541, -29999991, 65545, 1, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 2, -30000000, 131126, -30000000, 1, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 2, -30000000, 6, 112, 65647, -29999985, 65541,
    1, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -30000000, 131099, -30000000,
    15, 131126, -30000000, 15, 393307, (s32)btlevtcmd_ACRStart, -2, 0,
    -30000000, -30000000, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 65570,
    -29999994, 65577, 2, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307,
    (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000, 1, 0, 0, 0, 65541, 15,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 24, 0, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 3, -30000000, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999999, 131101, -29999999, 0, 131125, -30000000,
    -24, 32, 131125, -30000000, 24, 33, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 3, -30000000, 65545, 1, 6, 42, 49,
    33, 6, 112, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 131125, -29999998, 5, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_PARTY_BATTLE_JUMP1", -250000000, 0, -250000000, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000,
    -29999999, -29999998, -29999992, 0, 0, 65631, 15, 32,
    110, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 983131,
    (s32)evt_eff64, (s32)"", (s32)"kemuri2_n64", 2, -30000000, -29999999, -29999998, 0,
    0, 0, 0, 0, 0, 0, 0, 112,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125,
    -29999998, 5, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_JUMP1", -250000000, 0,
    -250000000, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, -29999992,
    0, 0, 33, 33, 131097, -29999995, 1, 131096,
    -29999995, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33, 131096,
    -29999995, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33, 131096,
    -29999995, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33, 65627,
    (s32)btlevtcmd_StopAC, 131163, (s32)btlevtcmd_JumpContinue, -2, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0,
    0, 0, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_S_1", 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_MoveDirectionAdd, -2, -30000000, 30, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 20, -1, 262235, (s32)btlevtcmd_MoveDirectionAdd, -2, -30000000,
    20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 10,
    -1, 65546, 500, 65540, 95, 33, 196699, (s32)btlevtcmd_ac_timing_flag_onoff,
    1, 1, 131163, (s32)btlevtcmd_ac_timing_get_success_frame, -30000000, 131128, -30000000, 2,
    65545, -30000000, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 0, 1, 65627, (s32)btlevtcmd_ResultAC,
    327771, (s32)btlevtcmd_SetScale, -2, -229998976, -229998976, -229998976, 131163, (s32)btlevtcmd_GetResultAC,
    -29999994, 131103, -29999994, 2, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997,
    -29999996, 256, -29999995, 131100, -29999990, 0, 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1, 32, 131122,
    -29999994, -29999990, 131126, -29999994, 1, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997,
    -29999994, -29999994, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult,
    -30000000, -29999994, 33, 65540, 90, 33, 131163, (s32)btlevtcmd_GetResultCountAC,
    -29999994, 262235, (s32)mario_get_renzoku_count_max, -29999997, -29999994, -29999993, 131098, -29999994,
    -29999993, 107, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 0, 196699, (s32)evt_btl_camera_set_zoom,
    0, 200, 65545, 10, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_btl_camera_set_zoom, 0, 250, 109, 393307, (s32)btlevtcmd_CommandCheckDamage, -2,
    -29999997, -29999996, 131072, -29999995, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, -29999990,
    -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 131125, -29999990,
    1, 131163, (s32)btlevtcmd_StartAC, 0, 65540, 10, 32, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996,
    131328, -29999995, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, -29999990, -29999994, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect,
    -29999994, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000,
    196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994, 33, 65539, 90, 65627,
    (s32)btlevtcmd_StopAC, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 110, 327771, (s32)btlevtcmd_GetRotate,
    -2, -250000000, -250000000, -29999994, 131098, -29999994, 0, 131127,
    -29999994, -1, 33, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000, 131127,
    -29999994, -30000000, 131128, -29999994, 15, 131122, -29999993, 15,
    65539, 20, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, -29999994,
    131126, -29999993, 1, 65545, 1, 131101, -29999993, 1,
    65540, 20, 33, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 112, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000,
    -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12, -1,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 8, -1, 65539, 95, 65627,
    (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2,
    65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 partyChristineAttack_Kiss[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 131163,
    (s32)btlevtcmd_CommandPayWeaponCost, -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode,
    0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -2, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 458843,
    (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985, 196699,
    (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65630, (s32)unk_evt_803510ec, 131097, -30000000, 0,
    458843, (s32)btlevtcmd_CalculateFaceDirection, -29999997, -29999996, -2, -1, 16, -29999985,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -29999997, -29999985, 33, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000,
    196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163, (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126,
    -30000000, 3, 65570, -30000000, 65576, -3, 131122, -30000000,
    27, 131122, -29999999, 20, 65572, -2, 131122, -30000000,
    25, 131122, -29999999, 28, 65572, -1, 131122, -30000000,
    23, 131122, -29999999, 30, 65572, 0, 131122, -30000000,
    23, 131122, -29999999, 30, 65572, 1, 131122, -30000000,
    23, 131122, -29999999, 30, 65572, 2, 131122, -30000000,
    23, 131122, -29999999, 30, 42, 131122, -30000000, 23,
    131122, -29999999, 32, 49, 589915, (s32)btlevtcmd_AcSetParamAll, 16, 220,
    70, 0, 0, -30000000, -29999999, 0, 131163, (s32)btlevtcmd_AcSetFlag,
    0, 327771, (s32)btlevtcmd_SetupAC, -2, 5, 3, 60, 65545,
    22, 131163, (s32)btlevtcmd_StartAC, 1, 196699, (s32)btlevtcmd_GetStatusMg, -2, -29999994,
    131132, -29999994, 12, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, -29999994, 196699, (s32)btlevtcmd_GetStatusMg,
    -29999997, -29999994, 131132, -29999994, 12, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997,
    -30000000, -29999994, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    200, -1, 0, 65627, (s32)btlevtcmd_ResultAC, 131163, (s32)btlevtcmd_GetResultAC, -30000000,
    131102, -30000000, 2, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 196699, (s32)btlevtcmd_GetHeight, -2, -29999994, 131125, -29999999, -29999994,
    262235, (s32)btlevtcmd_GetResultPrizeLv, -5, 0, -29999994, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994,
    -30000000, -29999999, -29999998, 33, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 65627,
    (s32)btlevtcmd_StopAC, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 350, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BTL_KURI_KISS1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_GetBodyId, -2, -29999991,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, -29999991, (s32)"PKR_O_1", 65546, 200, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, 15, 131125, -29999999, 30, 196699, (s32)btlevtcmd_GetFaceDirection, -2,
    -29999986, 131127, -29999986, 45, 983131, (s32)evt_eff, (s32)"", (s32)"kiss",
    1, -30000000, -29999999, -29999998, -29999986, 0, 0, 0,
    0, 0, 0, 0, 65644, -29999985, 131102, -29999994,
    2, 65630, (s32)unk_evt_803510ec, 131097, -30000000, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -29999997, -29999996, 58, 33, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000,
    -29999999, -29999998, 131125, -29999998, 15, 196699, (s32)btlevtcmd_GetHeight, -29999997,
    -29999985, 196699, (s32)btlevtcmd_GetStatusMg, -29999997, -29999986, 131132, -29999985, -29999986,
    131128, -29999985, 2, 131125, -29999999, -29999985, 983131, (s32)evt_eff,
    0, (s32)"recovery", 6, -30000000, -29999999, -29999998, 0, 0,
    0, 0, 0, 0, 0, 0, 393307, (s32)evt_snd_sfxon_3d,
    (s32)"SFX_BTL_KURI_CHEER_KISS1", -30000000, -29999999, -29999998, 0, 65545, 40, 262235,
    (s32)btlevtcmd_GetResultPrizeLv, -5, 0, -29999994, 196699, (s32)btlevtcmd_AudienceDeclareACResult, (s32)partyWeapon_ChristineKiss, -29999994,
    131163, (s32)_set_hustle, -29999997, 32, 65545, 40, 196699, (s32)btlevtcmd_AudienceDeclareACResult,
    (s32)partyWeapon_ChristineKiss, -1, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)partyWeapon_ChristineKiss,
    536871168, -29999995, 33, 109, 196699, (s32)btlevtcmd_ftof, 24, -30000000,
    196699, (s32)btlevtcmd_ftof, 48, -29999999, 393307, (s32)btlevtcmd_ACRStart, -2, -30000000,
    -29999999, -29999999, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999993, -29999992, 131101,
    -29999993, 2, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult,
    -30000000, 1, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PKR_J_1B", 65546, 166, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PKR_Y_1", 65546, 167, 32, 65627, (s32)evt_audience_acrobat_notry, 65545, 20,
    33, 131102, -29999994, 2, 393307, (s32)btlevtcmd_AnnounceMessage, 0, 0,
    0, (s32)"msg_st_chg_mario_quick", 60, 32, 65546, 500, 33, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 131163,
    (s32)btlevtcmd_WaitEventEnd, -29999985, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65627, (s32)evt_audience_ap_recovery, 65627,
    (s32)btlevtcmd_InviteApInfoReport, 65630, (s32)unk_evt_803510ec, 131097, -30000000, 0, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -29999997, 131163, (s32)btlevtcmd_StartWaitEvent, -29999997, 33, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

s32 christine_appeal_event[] = {
    196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    66, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_APPEAL1\0\0", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    15, 131125, -29999999, 30, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999986,
    131127, -29999986, 45, 983131, (s32)evt_eff, (s32)"", (s32)"kiss", 1,
    -30000000, -29999999, -29999998, -29999986, 0, 0, 0, 0,
    0, 0, 0, 65546, 667, 131163, (s32)btlevtcmd_AudienceAppeal, -2,
    65545, 30, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static EVT_BEGIN(party_win_reaction)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PKR_Y_1"))
    WAIT_FRAMES(64)
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
    50, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PKR_A_2B", 65545, 20, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PKR_J_1A", 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 14, 0,
    110, 327771, (s32)btlevtcmd_GetPosFloat, -2, -29999995, -29999994, -29999993, 131122,
    -29999992, 0, 65541, 36, 327771, (s32)btlevtcmd_GetPosFloat, -2, -29999988,
    -29999987, -29999986, 393307, (s32)krb_get_dir, -29999995, -29999994, -29999988, -29999987,
    -29999992, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, -29999992, 131124,
    -29999995, -29999988, 131124, -29999994, -29999987, 65545, 1, 6,
    112, 107, 65545, 15, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_KURI_ATTACK2",
    -250000000, 0, -250000000, 109, 327771, (s32)_get_attack_aud_no, -29999997, -30000000,
    -29999999, -29999998, 131125, -29999999, 28, 131125, -29999998, 5,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_JUMP1", -250000000, 0, -250000000, 524379,
    (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, 36, 0, 0,
    65545, 2, 196699, (s32)_attack_aud, -29999997, 0, 196699, (s32)evt_btl_camera_set_mode,
    0, 3, 327771, (s32)btlevtcmd_SetScale, -2, -229998976, -229998976, -229998976,
    65647, -29999985, 65546, 1500, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    65546, 1000, 112, 110, 327771, (s32)btlevtcmd_GetRotate, -2, -250000000,
    -250000000, -29999994, 131098, -29999994, 0, 131127, -29999994, -1,
    33, 131128, -29999994, 15, 131122, -29999993, 15, 65539,
    20, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, -29999994, 131126,
    -29999993, 1, 65545, 1, 131101, -29999993, 1, 65540,
    20, 33, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0,
    112, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000, -29999999,
    -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60, 262235, (s32)btlevtcmd_TransStageFloorPosition,
    -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 30, -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    8, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 8,
    -1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229995904, 524379, (s32)btlevtcmd_MovePosition, -2, -29999994, -29999999, -29999998,
    0, -1, 0, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_SetPos, -2, -29999992, -29999999, -29999998, 131163,
    (s32)btlevtcmd_WaitEventEnd, -29999985, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
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

static USER_FUNC(krb_get_dir) {
    s32* args = event->args;
    f32 x1, y1, x2, y2;
    f32 dx, dy;
    s32 value;

    x1 = evtGetFloat(event, args[0]);
    y1 = evtGetFloat(event, args[1]);
    x2 = evtGetFloat(event, args[2]);
    y2 = evtGetFloat(event, args[3]);
    value = evtGetValue(event, args[4]);
    dx = x2 - x1;
    dy = y2 - y1;
    if (dx == 0.0f && dy == 0.0f) {
        evtSetValue(event, args[4], value);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[4], angleABf(dx, dy, 0.0f, 0.0f));
    return EVT_RETURN_DONE;
}

static void __makeTechMenuFunc(BattleWorkCommand* command, s32* count) {
    s32 techLv;

    techLv = partyGetTechLv(BattleTransPartyId(BattleGetPartyPtr(_battleWorkPointer)->currentKind));

    command->mWeaponTable[*count].mIndex = -1;
    command->mWeaponTable[*count].mItem = 0;
    command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_ChristineNormalAttack;
    command->mWeaponTable[*count].field_0x4 = 0;
    command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;
    command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
    (*count)++;

    if (techLv >= 0) {
        command->mWeaponTable[*count].mIndex = -1;
        command->mWeaponTable[*count].mItem = 0;
        command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_ChristineMonosiri;
        command->mWeaponTable[*count].field_0x4 = 0;
        command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;
        command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
        (*count)++;
    }
    if (techLv >= 1) {
        command->mWeaponTable[*count].mIndex = -1;
        command->mWeaponTable[*count].mItem = 0;
        command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_ChristineRenzokuAttack;
        command->mWeaponTable[*count].field_0x4 = 0;
        command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;
        command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
        (*count)++;
    }
    if (techLv >= 2) {
        command->mWeaponTable[*count].mIndex = -1;
        command->mWeaponTable[*count].mItem = 0;
        command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_ChristineKiss;
        command->mWeaponTable[*count].field_0x4 = 0;
        command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;
        command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
        (*count)++;
    }
}

USER_FUNC(btlevtcmd_get_monosiri_msg_no) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id, index;

    id = evtGetValue(event, args[0]);
    evtGetValue(event, args[1]);
    index = args[2];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    evtSetValue(event, index, (s32)battleGetUnitMonosiriPtr(unit->currentKind)->tattleBtlTag);
    return EVT_RETURN_DONE;
}

USER_FUNC(_monosiri_flag_on) {
    s32 id = evtGetValue(event, event->args[0]);

    battleSetUnitMonosiriFlag(BattleGetUnitPtr(_battleWorkPointer, id)->currentKind);
    return EVT_RETURN_DONE;
}

USER_FUNC(_dictionary) {
    s32* args = event->args;
    s32 state;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 selfId, targetId;
    void* work;

    selfId = (0, BattleTransID(event, -2)); // FAKE: comma expression; plain call changes codegen
    targetId = evtGetValue(event, args[0]);
    targetId = BattleTransID(event, targetId);
    evtGetValue(event, args[1]);
    unit = BattleGetUnitPtr(wp, selfId);
    state = unit->work[0];
    work = (void*)unit->work[1];
    switch (state) {
        case 0:
            break;
        case 1:
            work = monosiriInit(BattleGetUnitPtr(wp, targetId)->currentKind, -50.0f, 50.0f);
            state = 2;
            break;
        case 2:
            monosiriMain(work);
            state = 3;
            break;
        case 3:
            monosiriMain(work);
            break;
        case 4:
            monosiriClose(work);
            monosiriMain(work);
            state = 5;
            break;
        case 5:
            if (monosiriCloseWait(work)) {
                monosiriExit(work);
                state = 6;
            } else {
                monosiriMain(work);
            }
            break;
        case 6:
            break;
    }
    unit->work[0] = state;
    unit->work[1] = (s32)work;
    return EVT_RETURN_DONE;
}

USER_FUNC(_set_hustle) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, event->args[0]);
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    if (unit) {
        if (unit->movesRemaining <= 0) {
            unit->movesRemaining++;
            unit->moveState = 0;
            unit->mMoveColorLv = 0xFF;
            if (unit->maxMovesThisTurn <= 0) {
                unit->maxMovesThisTurn = 1;
                if (BtlUnit_CheckStatus(unit, 0x14)) {
                    unit->mTokenFlags |= 0x2000;
                }
            }
        } else {
            BtlUnit_OnStatusFlag(unit, 0x2000000);
        }
    }
    return EVT_RETURN_DONE;
}
