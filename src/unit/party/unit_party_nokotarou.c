#include "version.h"
#include "icon_ids.h"
#include "battle/battle.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "driver/msgdrv.h"
#include "eff/eff_nokotarou.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_party.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

USER_FUNC(btlevtcmd_AddRotate);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_AudienceAppeal);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetFirstAttackTarget);
USER_FUNC(btlevtcmd_GetHitPos);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetOverTurnCount);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_InviteApInfoReport);
USER_FUNC(btlevtcmd_JumpPosition);
USER_FUNC(btlevtcmd_JumpSetting);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_OffStatusFlag);
USER_FUNC(btlevtcmd_OnStatusFlag);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_ResultACDefence);
USER_FUNC(btlevtcmd_RunDataEventChild);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetFallAccel);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetMoveSoundDataWork);
USER_FUNC(btlevtcmd_SetMoveSpeed);
USER_FUNC(btlevtcmd_SetOverTurnCount);
USER_FUNC(btlevtcmd_SetPartsDefenceTable);
USER_FUNC(btlevtcmd_SetPartsWork);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRotate);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WeaponAftereffect);
USER_FUNC(evt_audience_ap_recovery);
USER_FUNC(evt_btl_camera_set_homing_unit);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveSpeedLv);
USER_FUNC(evt_btl_camera_set_zoom);
USER_FUNC(evt_eff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_snd_sfxon_3d);
static USER_FUNC(_check_guard_koura);
USER_FUNC(_tsuranuki_effect_control);
USER_FUNC(_color_lv_set);
USER_FUNC(_check_mario_move_count);
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
extern s32 btlevtcmd_AddPartsRotate[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_AudienceDeclareACResult[];
extern s32 btlevtcmd_AudienceDeclareAcrobatResult[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CommandCheckDamage[];
extern s32 btlevtcmd_CommandGetWeaponActionLv[];
extern s32 btlevtcmd_CommandGetWeaponAddress[];
extern s32 btlevtcmd_CommandPayWeaponCost[];
extern s32 btlevtcmd_CommandPreCheckCounter[];
extern s32 btlevtcmd_CommandPreCheckDamage[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FallPosition[];
extern s32 btlevtcmd_GetBodyId[];
extern s32 btlevtcmd_GetFaceDirection[];
extern s32 btlevtcmd_GetMoveFrame[];
extern s32 btlevtcmd_GetPartsWork[];
extern s32 btlevtcmd_GetResultAC[];
extern s32 btlevtcmd_GetResultPrizeLv[];
extern s32 btlevtcmd_GetRotate[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetStageAudienceAreaSize[];
extern s32 btlevtcmd_GetStageSize[];
extern s32 btlevtcmd_GetUnitId[];
extern s32 btlevtcmd_GetUnitWork[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_OffAttribute[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_OnAttribute[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_ResultAC[];
extern s32 btlevtcmd_SetHomePos[];
extern s32 btlevtcmd_SetHp[];
extern s32 btlevtcmd_SetPartsRotateOffset[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SetupAC[];
extern s32 btlevtcmd_SpawnUnit[];
extern s32 btlevtcmd_StartAC[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_StopAC[];
extern s32 btlevtcmd_TransStageFloorPosition[];
extern s32 btlevtcmd_WaitEventEnd[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_audience_acrobat_notry[];
extern s32 evt_btl_camera_off_posoffset_manual[];
extern s32 evt_btl_camera_set_homing_unit_audience[];
extern s32 evt_btl_camera_set_posoffset[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_snd_sfx_pit[];
extern s32 evt_snd_sfxoff[];
extern s32 evt_sub_intpl_get_value_para[];
extern s32 evt_sub_intpl_init[];
extern s32 subset_attack_ready_jump_event[];
extern s32 unit_koura[];
extern s32 weaponGetACOutputParam[];
extern s32 weaponGetPowerFromPartyAttackLv[];

__declspec(section ".data") s32 unit_party_nokotarou_negone_one_a[2];
__declspec(section ".data") s32 nokotarou_negone_one_374[2];
__declspec(section ".data") s32 unit_party_nokotarou_one_negone_a[2];
__declspec(section ".data") s32 nokotarou_one_negone_373[2];
__declspec(section ".data") s32 unit_party_nokotarou_negone_one_b[2];
__declspec(section ".data") s32 nokotarou_negone_one_360[2];
__declspec(section ".data") s32 unit_party_nokotarou_one_negone_b[2];
__declspec(section ".data") s32 nokotarou_one_negone_359[2];
PoseTableEntry pose_table_nokotarou_stay[26];
PoseTableEntry pose_table_nokotarou_turn[12];
static BattleDataEntry data_table[12];
BattleUnitKindPart unitpartsdata_Party_Nokotarou[1];
BattleUnitKind unitdata_Party_Nokotarou;
static s32 battle_entry_event[59];
static s32 init_event[78];
s32 change_party_spawn_init_event[28];
static s32 dmg_turn_event[65];
static s32 wakeup_event[67];
s32 partyWeapon_NokotarouFirstAttack[48];
s32 partyWeapon_NokotarouKouraAttack[48];
s32 partyWeapon_NokotarouSyubibinKoura[48];
s32 partyWeapon_NokotarouKouraGuard[48];
s32 partyWeapon_NokotarouTsuranukiKoura[48];
static s32 _change_koura_pose[34];
static s32 _change_koura_pose_fast[78];
static s32 _restore_koura_pose[47];
static s32 _koura_rotate_start[199];
static s32 _koura_rotate_stop[13];
s32 partyNokotarouAttack_FirstAttack[236];
s32 partyNokotarouAttack_NormalAttack[VERSION_PICK(793, 804)];
s32 partyNokotarouAttack_SyubibinKoura[VERSION_PICK(691, 702)];
s32 partyNokotarouAttack_KouraGuard[838];
s32 partyNokotarouAttack_TsuranukiKoura[VERSION_PICK(931, 942)];
s32 nokotarou_appeal_event[34];
static s32 party_win_reaction[16];
static s32 attack_audience_event[263];
s32 nokotarou_revive_event[16];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static s32 defence_turn[2];
static StatusVulnerability regist;
static s32 damage_event[10];
static s32 attack_event[2];
static s32 wait_event[6];
s32 entry_koura[12];

__declspec(section ".data") s32 unit_party_nokotarou_negone_one_a[] = {
    -1082130432, 1065353216,
};

__declspec(section ".data") s32 nokotarou_negone_one_374[] = {
    -1082130432, 1065353216,
};

__declspec(section ".data") s32 unit_party_nokotarou_one_negone_a[] = {
    1065353216, -1082130432,
};

__declspec(section ".data") s32 nokotarou_one_negone_373[] = {
    1065353216, -1082130432,
};

__declspec(section ".data") s32 unit_party_nokotarou_negone_one_b[] = {
    -1082130432, 1065353216,
};

__declspec(section ".data") s32 nokotarou_negone_one_360[] = {
    -1082130432, 1065353216,
};

__declspec(section ".data") s32 unit_party_nokotarou_one_negone_b[] = {
    1065353216, -1082130432,
};

__declspec(section ".data") s32 nokotarou_one_negone_359[] = {
    1065353216, -1082130432,
};

PoseTableEntry pose_table_nokotarou_stay[] = {
    {9, "PNK_D_5"},
    {2, "PNK_D_5"},
    {3, "PNK_X_1"},
    {4, "PNK_D_2"},
    {5, "PNK_X_1"},
    {1, "PNK_N_1"},
    {27, "PNK_D_3"},
    {28, "PNK_S_1"},
    {37, "PNK_G_2"},
    {31, "PNK_G_1"},
    {39, "PNK_D_1"},
    {40, "PNK_W_1"},
    {42, "PNK_R_1"},
    {50, "PNK_A_1"},
    {57, "PNK_D_2"},
    {56, "PNK_D_2"},
    {60, "PNK_D_4"},
    {61, "PNK_X_1"},
    {65, "PNK_T_1"},
    {52, "PNK_I_1"},
    {67, "PNK_C_1"},
    {66, "PNK_O_1"},
    {64, "PNK_X_1"},
    {49, "PNK_A_1"},
    {45, "PNK_G_1"},
    {69, "PNK_S_1"},
};

PoseTableEntry pose_table_nokotarou_turn[] = {
    {9, "PNK_D_5"},
    {2, "PNK_D_5"},
    {1, "PNK_N_2"},
    {27, "PNK_D_3"},
    {28, "PNK_H_1"},
    {31, "PNK_D_1"},
    {39, "PNK_D_1"},
    {57, "PNK_H_1"},
    {56, "PNK_H_1"},
    {64, "PNK_H_1"},
    {45, "PNK_H_1"},
    {69, "PNK_H_1"},
};

static BattleDataEntry data_table[] = {
    {5, nokotarou_appeal_event},
    {6, attack_audience_event},
    {4, change_party_spawn_init_event},
    {13, dmg_turn_event},
    {1, __makeTechMenuFunc},
    {2, wakeup_event},
    {48, btldefaultevt_Dummy},
    {64, party_win_reaction},
    {7, subset_attack_ready_jump_event},
    {67, nokotarou_revive_event},
    {47, btldefaultevt_avoid_counter_event},
    {0, NULL},
};

BattleUnitKindPart unitpartsdata_Party_Nokotarou[] = {
    {1, "btl_un_nokotarou", "c_pnk", 0.0f, 0.0f, 0.0f, 12.0f, 30.0f, 5.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x1009, 0, pose_table_nokotarou_stay},
};

BattleUnitKind unitdata_Party_Nokotarou = {
    225,
    "btl_un_nokotarou",
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
    14,
    36,
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
    1,
    unitpartsdata_Party_Nokotarou,
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
    CALL(btlevtcmd_SetMoveSoundDataWork, -2, STRING("SFX_PARTY_BATTLE_SUBMOVE1L"), STRING("SFX_PARTY_BATTLE_SUBMOVE1R"), 0, 9, 9, 0, 0)
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -2, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 4, 3410)
    CALL(btlevtcmd_SetUnitWork, -2, 5, 0)
    CALL(btlevtcmd_SetPartsWork, -2, 1, 0, 0)
    CALL(btlevtcmd_SetPartsWork, -2, 1, 2, 0)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 6, 12, 16)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 9, 3)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_SetEventEntry, -2, PTR(battle_entry_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(change_party_spawn_init_event)
    CALL(btlevtcmd_GetOverTurnCount, -4, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL(btlevtcmd_SetPartsDefenceTable, -4, 1, PTR(defence_turn))
        CALL(btlevtcmd_AnimeSetPoseTable, -4, 1, PTR(pose_table_nokotarou_turn))
        CALL(btlevtcmd_OnStatusFlag, -4, 1)
    END_IF
    CALL(btlevtcmd_AnimeChangePoseFromTable, -4, 1)
    RETURN
EVT_END()

static EVT_BEGIN(dmg_turn_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(defence_turn))
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_nokotarou_turn))
    CALL(btlevtcmd_OnStatusFlag, LW(10), 1)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), 2)
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("PNK_D_1"))
    CALL(btlevtcmd_OffStatusFlag, LW(10), 16777216)
    CALL(evt_snd_sfxon, STRING("SFX_CONDITION_INSIDE"), 0)
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 6, -1)
    RETURN
EVT_END()

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
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence))
    CALL(btlevtcmd_OffStatusFlag, LW(10), 1)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_nokotarou_stay))
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("PNK_S_1"))
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 partyWeapon_NokotarouFirstAttack[] = {
    0, VERSION_PICK(22020096, 22544384), 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerFromPartyAttackLv,
    2, 2, 3, 3, 5, 5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553664516, 525058, 0, 131215, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyNokotarouAttack_FirstAttack, 100, 0, 0,
};

s32 partyWeapon_NokotarouKouraAttack[] = {
    (s32)"btl_wn_pnk_normal", VERSION_PICK(22020096, 22544384), 0, (s32)"msg_pnk_normal_attack", 1677721600, 1065353216, 16868402, (s32)weaponGetPowerFromPartyAttackLv,
    1, 2, 2, 3, 3, 5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553664516, 525058, (s32)"msg_ac_hammer", 196743, 1535, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyNokotarouAttack_NormalAttack, 100, VERSION_PICK(131584, 262656), 0,
};

s32 partyWeapon_NokotarouSyubibinKoura[] = {
    (s32)"btl_wn_pnk_lv1", VERSION_PICK(22085632, 22609920), 0, (s32)"msg_pnk_syubibin_koura", 1677918208, 1065353216, VERSION_PICK(33907762, 17130546), (s32)weaponGetPowerFromPartyAttackLv,
    1, 2, 2, 3, 3, 5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536887300, 525058, (s32)"msg_ac_koura_shubibin", 131207, 1535, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyNokotarouAttack_SyubibinKoura, 100, VERSION_PICK(328960, 656640), 0,
};

s32 partyWeapon_NokotarouKouraGuard[] = {
    (s32)"btl_wn_pnk_lv2", VERSION_PICK(22151168, 22675456), 0, (s32)"msg_pnk_koura_no_mamori", 1677983744, 1065353216, 17130546, 0,
    0, 2, 2, 3, 3, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17891360, 268435456, 770, (s32)"msg_ac_koura_no_mamori", 131072, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyNokotarouAttack_KouraGuard, 100, 0, 0,
};

s32 partyWeapon_NokotarouTsuranukiKoura[] = {
    (s32)"btl_wn_pnk_lv3_tsuranuki", VERSION_PICK(22216704, 22740992), 0, (s32)"msg_pnk_koura_tsuranuki", 1678114816, 1065353216, VERSION_PICK(50684978, 17130546), (s32)weaponGetACOutputParam,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536887300, 770, (s32)"msg_ac_tsuranuki_koura", 131271, 1535, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyNokotarouAttack_TsuranukiKoura, 100, VERSION_PICK(328960, 656640), 0,
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
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(evt_eff, 0, STRING("kemuri_test"), 5, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
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
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(evt_eff, 0, STRING("kemuri_test"), 5, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(_restore_koura_pose)
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
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

static s32 _koura_rotate_start[] = {
    262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    2, 0, 107, 65539, 0, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    0, -29999999, 131096, -29999999, 0, 65540, 10, 33,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -29999989, 131097, -29999989, 0,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 0, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    1, -29999990, 131127, -29999990, -1, 131127, -30000000, -1,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 1, -29999990, 33, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 1, -29999990, 131101, -29999990, 0, 131125, -30000000,
    1, 131099, -30000000, -29999990, 131122, -30000000, -29999990, 33,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, -30000000, 0, 327771, (s32)btlevtcmd_GetRotate,
    -2, -250000000, -29999999, -250000000, 131098, -29999999, -30000000, 327771,
    (s32)btlevtcmd_GetPartsWork, -2, 1, 0, -29999999, 131097, -29999999, 0,
    110, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 983131,
    (s32)evt_eff, 0, (s32)"kemuri_test", 5, -30000000, -29999999, -29999998, -229998976,
    0, 0, 0, 0, 0, 0, 0, 112,
    33, 33, 32, 131126, -30000000, 1, 131098, -30000000,
    -29999990, 131122, -30000000, -29999990, 33, 327771, (s32)btlevtcmd_AddRotate, -2,
    0, -30000000, 0, 327771, (s32)btlevtcmd_GetPartsWork, -2, 1, 0,
    -29999999, 131097, -29999999, 0, 110, 131127, -30000000, -1,
    327771, (s32)btlevtcmd_GetRotate, -2, -250000000, -29999999, -250000000, 131125, -29999999,
    360, 131098, -29999999, -30000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 983131, (s32)evt_eff, 0, (s32)"kemuri_test", 5, -30000000,
    -29999999, -29999998, -229998976, 0, 0, 0, 0, 0,
    0, 0, 33, 112, 33, 33, 65545, 1,
    65540, 0, 65539, 10, 109, 2, 1,
};

static EVT_BEGIN(_koura_rotate_stop)
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(partyNokotarouAttack_FirstAttack)
    CALL(btlevtcmd_JumpSetting, -2, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, PTR(partyWeapon_NokotarouFirstAttack))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, LW(3), -1)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    SET_VALUE(LW(0), 45)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 45)
    CALL_CHILD(PTR(_koura_rotate_start))
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 250)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    WAIT_FRAMES(50)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 50)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(5), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(6.0f))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_NOKO_ATTACK2"), 0)
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, 0, 0)
    CALL_CHILD(PTR(_koura_rotate_stop))
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(partyWeapon_NokotarouFirstAttack))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), PTR(partyWeapon_NokotarouFirstAttack), 131328, LW(5))
    SET_VALUE(LW(0), 45)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 45)
    CALL_CHILD(PTR(_koura_rotate_start))
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 0)
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 30)
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 18, -1)
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.5996094f))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 20)
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 8)
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 8, -1)
    CALL_CHILD(PTR(_koura_rotate_stop))
    CALL_CHILD(PTR(_restore_koura_pose))
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 40)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    CALL_CHILD(PTR(btldefaultevt_SuitoruBadgeEffect))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

#ifdef VERSION_G8ME01
s32 partyNokotarouAttack_NormalAttack[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    131163, (s32)btlevtcmd_CommandPayWeaponCost, -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699,
    (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, 1,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200,
    327771, (s32)evt_btl_camera_set_posoffset, 0, 20, 0, 0, 65545, 20,
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65630, (s32)_change_koura_pose, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 50, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_NOKO_ATTACK1", -29999987, 131122,
    -30000000, 15, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 45, 65630,
    (s32)_koura_rotate_start, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000,
    131163, (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126, -30000000, 3, 65570, -30000000,
    65576, -3, 131122, -30000000, 360, 131122, -29999999, 100,
    65572, -2, 131122, -30000000, 280, 131122, -29999999, 150,
    65572, -1, 131122, -30000000, 240, 131122, -29999999, 200,
    65572, 0, 131122, -30000000, 200, 131122, -29999999, 250,
    65572, 1, 131122, -30000000, 200, 131122, -29999999, 360,
    65572, 2, 131122, -30000000, 200, 131122, -29999999, 600,
    42, 131122, -30000000, 200, 131122, -29999999, 960, 49,
    589915, (s32)btlevtcmd_AcSetParamAll, 2, -30000000, 0, 1, -29999999, -250000000,
    -250000000, -250000000, 131163, (s32)btlevtcmd_AcSetFlag, 3, 327771, (s32)btlevtcmd_SetupAC, -2,
    19, 1, 60, 65545, 22, 65647, -29999985, 65541,
    10000, 196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000, 131097, -30000000, 0,
    7, 33, 65545, 1, 6, 131122, -29999994, 0,
    65541, 10000, 131125, -29999994, 1, 131099, -29999994, 100,
    131122, -29999994, 100, 33, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5,
    -29999994, 262235, (s32)btlevtcmd_GetUnitWork, -2, 4, -30000000, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 5, -29999999, 131127, -30000000, -29999999, 131128, -30000000,
    100, 196699, (s32)evt_snd_sfx_pit, -29999987, -30000000, 65545, 1, 6,
    112, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256, -29999994,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 4, 196699, (s32)evt_btl_camera_set_zoom, 0, 400,
    131163, (s32)btlevtcmd_StartAC, 1, 65627, (s32)btlevtcmd_ResultAC, 65631, -29999985, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 5, 0, 131163, (s32)evt_snd_sfxoff, -29999987, 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_BTL_NOKO_ATTACK2", 0, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 327771, (s32)evt_btl_camera_set_posoffset, 0, 0, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229989760, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125,
    -29999998, 5, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 458843,
    (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998, 0, -29999987, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, -29999987, 0, 0,
    131097, -29999994, 1, 131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 33, 131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 33, 131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 33, 65627, (s32)btlevtcmd_StopAC, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, 40, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 65630, (s32)_koura_rotate_stop, 65630, (s32)_restore_koura_pose, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 65545, 30, 65627, (s32)evt_audience_ap_recovery,
    65627, (s32)btlevtcmd_InviteApInfoReport, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 65540, 99, 33, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 393307, (s32)btlevtcmd_CommandPreCheckCounter, -2, -29999997, -29999996, 256, -30000000,
    131097, -30000000, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 0,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 65630, (s32)_koura_rotate_stop,
    33, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102, -30000000, 2, 393307,
    (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131328, -29999995, 262235, (s32)btlevtcmd_GetResultPrizeLv,
    -29999997, 0, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994,
    32, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256, -29999995,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1,
    33, 65539, 90, 65627, (s32)btlevtcmd_StopAC, 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    30, 110, 393307, (s32)btlevtcmd_ACRStart, -2, 0, 17, 17,
    0, 112, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    18, -1, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131096, -29999994,
    2, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000,
    1, 0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0,
    10, 0, 65541, 9, 327771, (s32)btlevtcmd_AddRotate, -2, 0,
    0, 20, 65545, 1, 6, 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999284, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 180, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_E_2", 110, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    1, 45, 65539, 91, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1,
    -30000000, 131100, -30000000, 0, 65540, 92, 33, 131126,
    -30000000, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, -30000000, 65545,
    2, 65540, 91, 65539, 92, 112, 393307, (s32)btlevtcmd_ACRStart,
    -2, 60, 90, 90, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994,
    -29999993, 131096, -29999994, 1, 65540, 94, 33, 131097,
    -29999994, 2, 65540, 94, 33, 65630, (s32)_koura_rotate_stop, 65541,
    6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 45,
    0, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_E_3", 65541,
    6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 15,
    0, 6, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult,
    -30000000, 1, 0, 0, 0, 65545, 60, 65540,
    95, 65539, 94, 65630, (s32)_koura_rotate_stop, 65627, (s32)evt_audience_acrobat_notry, 65630,
    (s32)_restore_koura_pose, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 65545, 30,
    65540, 95, 33, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    8, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 8,
    -1, 65630, (s32)_restore_koura_pose, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43,
    65545, 30, 65539, 95, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229993856, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};
#else
s32 partyNokotarouAttack_NormalAttack[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    131163, (s32)btlevtcmd_CommandPayWeaponCost, -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699,
    (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, 1,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200,
    327771, (s32)evt_btl_camera_set_posoffset, 0, 20, 0, 0, 65545, 20,
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65630, (s32)_change_koura_pose, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 50, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_NOKO_ATTACK1", -29999987, 131122,
    -30000000, 15, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 45, 65630,
    (s32)_koura_rotate_start, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000,
    131163, (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126, -30000000, 3, 65570, -30000000,
    65576, -3, 131122, -30000000, 360, 131122, -29999999, 100,
    65572, -2, 131122, -30000000, 280, 131122, -29999999, 150,
    65572, -1, 131122, -30000000, 240, 131122, -29999999, 200,
    65572, 0, 131122, -30000000, 200, 131122, -29999999, 250,
    65572, 1, 131122, -30000000, 200, 131122, -29999999, 360,
    65572, 2, 131122, -30000000, 200, 131122, -29999999, 600,
    42, 131122, -30000000, 200, 131122, -29999999, 960, 49,
    589915, (s32)btlevtcmd_AcSetParamAll, 2, -30000000, 0, 1, -29999999, -250000000,
    -250000000, -250000000, 131163, (s32)btlevtcmd_AcSetFlag, 3, 327771, (s32)btlevtcmd_SetupAC, -2,
    19, 1, 60, 65545, 22, 65647, -29999985, 65541,
    10000, 196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000, 131097, -30000000, 0,
    7, 33, 65545, 1, 6, 131122, -29999994, 0,
    65541, 10000, 131125, -29999994, 1, 131099, -29999994, 100,
    131122, -29999994, 100, 33, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5,
    -29999994, 262235, (s32)btlevtcmd_GetUnitWork, -2, 4, -30000000, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 5, -29999999, 131127, -30000000, -29999999, 131128, -30000000,
    100, 196699, (s32)evt_snd_sfx_pit, -29999987, -30000000, 65545, 1, 6,
    112, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256, -29999994,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 4, 196699, (s32)evt_btl_camera_set_zoom, 0, 400,
    131163, (s32)btlevtcmd_StartAC, 1, 65627, (s32)btlevtcmd_ResultAC, 65631, -29999985, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 5, 0, 131163, (s32)evt_snd_sfxoff, -29999987, 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_BTL_NOKO_ATTACK2", 0, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 327771, (s32)evt_btl_camera_set_posoffset, 0, 0, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229989760, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125,
    -29999998, 5, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 458843,
    (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998, 0, -29999987, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, -29999987, 0, 0,
    131097, -29999994, 1, 131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 33, 131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 33, 131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 33, 65627, (s32)btlevtcmd_StopAC, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, 40, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 65630, (s32)_koura_rotate_stop, 65630, (s32)_restore_koura_pose, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 65545, 30, 65627, (s32)evt_audience_ap_recovery,
    65627, (s32)btlevtcmd_InviteApInfoReport, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 65540, 99, 33, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 393307, (s32)btlevtcmd_CommandPreCheckCounter, -2, -29999997, -29999996, 256, -30000000,
    131097, -30000000, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 0,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 65630, (s32)_koura_rotate_stop,
    33, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102, -30000000, 2, 393307,
    (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131328, -29999995, 262235, (s32)btlevtcmd_GetResultPrizeLv,
    -29999997, 0, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994,
    32, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256, -29999995,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1,
    33, 65539, 90, 65627, (s32)btlevtcmd_StopAC, 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    30, 110, 393307, (s32)btlevtcmd_ACRStart, -2, 0, 17, 17,
    0, 112, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    18, -1, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131096, -29999994,
    2, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 10, 0, 65541,
    9, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, 20, 65545,
    1, 6, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 180, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PNK_E_2", 110, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 45, 65539,
    91, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -30000000, 131100, -30000000,
    0, 65540, 92, 33, 131126, -30000000, 1, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 1, -30000000, 65545, 2, 65540, 91,
    65539, 92, 112, 393307, (s32)btlevtcmd_ACRStart, -2, 60, 90,
    90, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131096, -29999994,
    1, 65540, 94, 33, 131097, -29999994, 2, 65540,
    94, 33, 65630, (s32)_koura_rotate_stop, 65541, 6, 65545, 1,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 45, 0, 6, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_E_3", 65541, 6, 65545, 1,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 15, 0, 6, 196699,
    (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000, 1, 0,
    0, 0, 65545, 60, 65540, 95, 65539, 94,
    65630, (s32)_koura_rotate_stop, 65627, (s32)evt_audience_acrobat_notry, 65630, (s32)_restore_koura_pose, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 43, 65545, 30, 65540, 95, 33,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12,
    -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 8, -1, 65630, (s32)_restore_koura_pose,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 65545, 30, 65539,
    95, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 65539, 99, 131163,
    (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    1,
};
#endif

#ifdef VERSION_G8ME01
s32 partyNokotarouAttack_SyubibinKoura[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, 1, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 327771, (s32)evt_btl_camera_set_posoffset,
    0, 20, 0, 0, 65545, 20, 65630, (s32)_change_koura_pose,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_NOKO_SHUBIBIN1",
    -29999987, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, 0, 131122, -30000000,
    15, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 45, 65630, (s32)_koura_rotate_start,
    131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163,
    (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126, -30000000, 3, 65570, -30000000, 65576,
    -3, 131122, -30000000, 480, 131122, -29999999, 240, 65572,
    -2, 131122, -30000000, 300, 131122, -29999999, 180, 65572,
    -1, 131122, -30000000, 240, 131122, -29999999, 120, 65572,
    0, 131122, -30000000, 180, 131122, -29999999, 105, 65572,
    1, 131122, -30000000, 150, 131122, -29999999, 90, 65572,
    2, 131122, -30000000, 120, 131122, -29999999, 60, 42,
    131122, -30000000, 100, 131122, -29999999, 30, 49, 589915,
    (s32)btlevtcmd_AcSetParamAll, 2, -30000000, 1, 95, -29999999, -250000000, -250000000,
    -250000000, 131163, (s32)btlevtcmd_AcSetFlag, 3, 327771, (s32)btlevtcmd_SetupAC, -2, 19,
    1, 60, 65545, 22, 65647, -29999985, 65541, 10000,
    196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000, 131097, -30000000, 0, 7,
    33, 65545, 1, 6, 131122, -29999994, 0, 65541,
    10000, 131125, -29999994, 1, 131099, -29999994, 200, 131122,
    -29999994, 200, 33, 131122, -29999993, -29999994, 131128, -29999993,
    2, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, -29999993, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 4, -30000000, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -29999999,
    131127, -30000000, -29999999, 131128, -30000000, 100, 196699, (s32)evt_snd_sfx_pit,
    -29999987, -30000000, 65545, 1, 6, 112, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 4, 196699, (s32)evt_btl_camera_set_zoom, 0, 400, 131163, (s32)btlevtcmd_StartAC,
    1, 65627, (s32)btlevtcmd_ResultAC, 65627, (s32)btlevtcmd_StopAC, 65631, -29999985, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 5, 0, 131163, (s32)evt_snd_sfxoff, -29999987, 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_BTL_NOKO_SHUBIBIN2", 0, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 327771, (s32)evt_btl_camera_set_posoffset, 0, 0, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 131122, -29999990,
    0, 65539, 10, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229989760, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999995, -29999995, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, 0, 0, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2,
    -29999997, -29999996, 256, -29999994, 131097, -29999994, 1, 131096,
    -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33, 131096,
    -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33, 131096,
    -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33, 65540,
    50, 33, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 0, 393307, (s32)btlevtcmd_CommandPreCheckCounter, -2, -29999997, -29999996, 256,
    -30000000, 131097, -30000000, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1,
    0, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 65630,
    (s32)_koura_rotate_stop, 33, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102, -30000000, 2,
    393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131328, -29999995, 262235,
    (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999,
    -29999998, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000,
    -29999994, 32, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256,
    -29999995, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000,
    -1, 33, 65539, 50, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996,
    131097, -29999997, -1, 131125, -29999990, 1, 65540, 10,
    33, 65539, 80, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998,
    524379, (s32)btlevtcmd_MovePosition, -2, 400, -29999999, -29999998, 0, 0,
    0, 65539, 90, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131127, -30000000, -1, 327771, (s32)btlevtcmd_SetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, 0,
    0, 393307, (s32)btlevtcmd_ACRStart, -2, 0, 9, 9, 0,
    196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131096, -29999994, 2, 196699,
    (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000, 1, 0,
    0, 0, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 12, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999693, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_E_1", 65545, 10, 393307, (s32)btlevtcmd_ACRStart,
    -2, 49, 79, 79, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994,
    -29999993, 131097, -29999994, 2, 65630, (s32)_koura_rotate_stop, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PNK_E_2", 65541, 6, 65545, 1, 327771,
    (s32)btlevtcmd_AddRotate, -2, 0, 45, 0, 6, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PNK_S_1", 65541, 6, 65545, 1, 327771,
    (s32)btlevtcmd_AddRotate, -2, 0, 15, 0, 6, 65627, (s32)evt_audience_acrobat_notry,
    65540, 99, 33, 65630, (s32)_koura_rotate_stop, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PNK_E_2", 65541, 6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate,
    -2, 0, 45, 0, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PNK_E_3", 65541, 6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate,
    -2, 0, 15, 0, 6, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2,
    -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000, 1, 0, 0, 0,
    65545, 60, 65540, 99, 33, 65630, (s32)_restore_koura_pose, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 65545, 30, 65539, 99,
    65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630,
    (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};
#else
s32 partyNokotarouAttack_SyubibinKoura[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, 1, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 327771, (s32)evt_btl_camera_set_posoffset,
    0, 20, 0, 0, 65545, 20, 65630, (s32)_change_koura_pose,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_NOKO_SHUBIBIN1",
    -29999987, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, 0, 131122, -30000000,
    15, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 45, 65630, (s32)_koura_rotate_start,
    131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163,
    (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126, -30000000, 3, 65570, -30000000, 65576,
    -3, 131122, -30000000, 480, 131122, -29999999, 240, 65572,
    -2, 131122, -30000000, 300, 131122, -29999999, 180, 65572,
    -1, 131122, -30000000, 240, 131122, -29999999, 120, 65572,
    0, 131122, -30000000, 180, 131122, -29999999, 105, 65572,
    1, 131122, -30000000, 150, 131122, -29999999, 90, 65572,
    2, 131122, -30000000, 120, 131122, -29999999, 60, 42,
    131122, -30000000, 100, 131122, -29999999, 30, 49, 589915,
    (s32)btlevtcmd_AcSetParamAll, 2, -30000000, 1, 95, -29999999, -250000000, -250000000,
    -250000000, 131163, (s32)btlevtcmd_AcSetFlag, 3, 327771, (s32)btlevtcmd_SetupAC, -2, 19,
    1, 60, 65545, 22, 65647, -29999985, 65541, 10000,
    196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000, 131097, -30000000, 0, 7,
    33, 65545, 1, 6, 131122, -29999994, 0, 65541,
    10000, 131125, -29999994, 1, 131099, -29999994, 200, 131122,
    -29999994, 200, 33, 131122, -29999993, -29999994, 131128, -29999993,
    2, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, -29999993, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 4, -30000000, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -29999999,
    131127, -30000000, -29999999, 131128, -30000000, 100, 196699, (s32)evt_snd_sfx_pit,
    -29999987, -30000000, 65545, 1, 6, 112, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 4, 196699, (s32)evt_btl_camera_set_zoom, 0, 400, 131163, (s32)btlevtcmd_StartAC,
    1, 65627, (s32)btlevtcmd_ResultAC, 65627, (s32)btlevtcmd_StopAC, 65631, -29999985, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 5, 0, 131163, (s32)evt_snd_sfxoff, -29999987, 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_BTL_NOKO_SHUBIBIN2", 0, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 327771, (s32)evt_btl_camera_set_posoffset, 0, 0, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 131122, -29999990,
    0, 65539, 10, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229989760, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999995, -29999995, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, 0, 0, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2,
    -29999997, -29999996, 256, -29999994, 131097, -29999994, 1, 131096,
    -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33, 131096,
    -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33, 131096,
    -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33, 65540,
    50, 33, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 0, 393307, (s32)btlevtcmd_CommandPreCheckCounter, -2, -29999997, -29999996, 256,
    -30000000, 131097, -30000000, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1,
    0, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 65630,
    (s32)_koura_rotate_stop, 33, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102, -30000000, 2,
    393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131328, -29999995, 262235,
    (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999,
    -29999998, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000,
    -29999994, 32, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256,
    -29999995, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000,
    -1, 33, 65539, 50, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996,
    131097, -29999997, -1, 131125, -29999990, 1, 65540, 10,
    33, 65539, 80, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998,
    524379, (s32)btlevtcmd_MovePosition, -2, 400, -29999999, -29999998, 0, 0,
    0, 65539, 90, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131127, -30000000, -1, 327771, (s32)btlevtcmd_SetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, 0,
    0, 393307, (s32)btlevtcmd_ACRStart, -2, 0, 9, 9, 0,
    196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131096, -29999994, 2, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    1, 12, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999693, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 30, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PNK_E_1", 65545, 10, 393307, (s32)btlevtcmd_ACRStart, -2, 49, 79,
    79, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131097, -29999994,
    2, 65630, (s32)_koura_rotate_stop, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_E_2",
    65541, 6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -2, 0,
    45, 0, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_S_1",
    65541, 6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -2, 0,
    15, 0, 6, 65627, (s32)evt_audience_acrobat_notry, 65540, 99, 33,
    65630, (s32)_koura_rotate_stop, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_E_2", 65541,
    6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 45,
    0, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_E_3", 65541,
    6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 15,
    0, 6, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult,
    -30000000, 1, 0, 0, 0, 65545, 60, 65540,
    99, 33, 65630, (s32)_restore_koura_pose, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    43, 65545, 30, 65539, 99, 65627, (s32)evt_audience_ap_recovery, 65627,
    (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};
#endif

s32 partyNokotarouAttack_KouraGuard[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0,
    -2, -2, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom,
    0, 200, 327771, (s32)evt_btl_camera_set_posoffset, 0, 20, 0, 0,
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)_check_guard_koura, -3, -29999990,
    131097, -29999990, -1, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 62, 33,
    262235, (s32)_color_lv_set, -3, 0, -29999986, 262235, (s32)_color_lv_set, -3,
    1, 255, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_A_2", 65545,
    30, 262235, (s32)btlevtcmd_SpawnUnit, -29999990, (s32)entry_koura, 0, 196699, (s32)btlevtcmd_OnAttribute,
    -29999990, 16777216, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998,
    131125, -29999998, 5, 131125, -29999999, 240, 327771, (s32)btlevtcmd_SetPos,
    -29999990, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_OffAttribute, -29999990, 16777216,
    131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 196699,
    (s32)btlevtcmd_GetBodyId, -29999990, -29999989, 131163, (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126, -30000000,
    3, 65570, -30000000, 65576, -3, 131122, -30000000, 360,
    131122, -29999999, 480, 65572, -2, 131122, -30000000, 180,
    131122, -29999999, 360, 65572, -1, 131122, -30000000, 120,
    131122, -29999999, 300, 65572, 0, 131122, -30000000, 90,
    131122, -29999999, 240, 65572, 1, 131122, -30000000, 70,
    131122, -29999999, 200, 65572, 2, 131122, -30000000, 40,
    131122, -29999999, 120, 42, 131122, -30000000, 20, 131122,
    -29999999, 80, 49, 589915, (s32)btlevtcmd_AcSetParamAll, 1, -29999990, -29999989,
    30, -30000000, -29999999, -250000000, -250000000, 131163, (s32)btlevtcmd_AcSetFlag, 0,
    327771, (s32)btlevtcmd_SetupAC, -2, 12, 1, 0, 327771, (s32)btlevtcmd_GetPos,
    -29999990, -30000000, -29999999, -29999998, 131122, -29999999, 125, 655451,
    (s32)btlevtcmd_DivePosition, -29999990, -30000000, -29999999, -29999998, 60, 0, 13,
    0, -1, 131163, (s32)btlevtcmd_StartAC, 1, 65627, (s32)btlevtcmd_ResultAC, 131163,
    (s32)btlevtcmd_GetResultAC, -29999994, 131096, 0, 0, 110, 65545, 10,
    262235, (s32)btlevtcmd_AnimeChangePose, -3, 1, (s32)"M_N_7", 65545, 35, 262235,
    (s32)btlevtcmd_AnimeChangePose, -3, 1, (s32)"M_B_1", 65545, 15, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -3, 1, 43, 112, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    196699, (s32)evt_btl_camera_set_zoom, 0, 400, 327771, (s32)evt_btl_camera_set_posoffset, 0, 0,
    0, 0, 196699, (s32)btlevtcmd_SetFallAccel, -29999990, -229999591, 327771, (s32)btlevtcmd_GetPos,
    -29999997, -30000000, -29999999, -29999998, 131125, -29999998, 5, 327771,
    (s32)btlevtcmd_GetPos, -29999990, -30000000, -250000000, -250000000, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000,
    -29999999, -29999998, 393307, (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_BTL_NOKO_GUARD2", -250000000, 0,
    -29999995, 110, 65545, 2, 393307, (s32)btlevtcmd_ACRStart, -2, 48,
    67, 67, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131096,
    -29999994, 2, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult,
    -30000000, 1, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PNK_O_1", 65546, 1000, 32, 65627, (s32)evt_audience_acrobat_notry, 33,
    112, 393307, (s32)btlevtcmd_FallPosition, -29999990, -30000000, -29999999, -29999998, 60,
    131163, (s32)evt_snd_sfxoff, -29999995, 327771, (s32)btlevtcmd_SetHomePos, -29999990, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_AnimeChangePose, -29999990, 1, (s32)"PKO_F_1", 393307, (s32)btlevtcmd_snd_se,
    -29999990, (s32)"SFX_BTL_NOKO_GUARD1", -250000000, 0, -250000000, 393307, (s32)evt_btl_camera_shake_h, 0,
    2, 0, 10, 13, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988,
    131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 110, 131122, -29999991, -29999990, 327771,
    (s32)btlevtcmd_GetRotate, -29999991, -250000000, -250000000, -29999992, 131098, -29999992, 180,
    327771, (s32)evt_sub_intpl_init, 11, -29999992, 0, 50, 32, 327771,
    (s32)evt_sub_intpl_init, 11, -29999992, 360, 50, 33, 65541, 50,
    196699, (s32)evt_sub_intpl_get_value_para, -29999999, -29999998, 327771, (s32)btlevtcmd_SetRotate, -29999991, -250000000,
    -250000000, -29999999, 65545, 1, 6, 112, 131102, -29999994,
    2, 196699, (s32)btlevtcmd_AcGetOutputParam, 1, -30000000, 65570, -30000000, 65577,
    8, 131122, -30000000, 2, 65577, 6, 131122, -30000000,
    1, 65577, 4, 131122, -30000000, 0, 42, 131122,
    -30000000, -1, 49, 131101, -30000000, 0, 262235, (s32)btlevtcmd_GetResultPrizeLv,
    -29999997, -30000000, -29999993, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999993, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999993, 32, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1,
    33, 32, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 33, 65545,
    50, 196699, (s32)btlevtcmd_OnAttribute, -29999997, 32, 196699, (s32)btlevtcmd_GetUnitId, -29999997,
    -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -29999990, 0, -30000000, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 43, 262235, (s32)btlevtcmd_SetUnitWork, -29999990, 2, 3,
    65647, -29999985, 131122, -29999995, 5, 65541, -29999995, 262235,
    (s32)btlevtcmd_GetUnitWork, -29999990, 2, -29999990, 131097, -30000000, 3, 7,
    33, 65545, 1, 131122, -29999995, 5, 6, 112,
    131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 262235, (s32)btlevtcmd_SetUnitWork, -29999990, 2, 0,
    131102, -29999994, 2, 196699, (s32)btlevtcmd_AcGetOutputParam, 1, -30000000, 32,
    196699, (s32)btlevtcmd_AcGetOutputParam, 2, -30000000, 33, 196699, (s32)btlevtcmd_SetHp, -29999990,
    -30000000, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 61, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990,
    1, 43, 262235, (s32)btlevtcmd_OnPartsAttribute, -29999997, 1, 16777216, 196699,
    (s32)btlevtcmd_OnAttribute, -29999997, 96, 131163, (s32)btlevtcmd_StartWaitEvent, -29999997, 131163, (s32)_check_mario_move_count,
    -30000000, 131101, -30000000, 1, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 131163, (s32)evt_btl_camera_off_posoffset_manual, 0, 65546,
    500, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 59, 65545, 60, 33,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 131163, (s32)evt_btl_camera_off_posoffset_manual, 0, 2, 33, 65647,
    -29999985, 65545, 10, 262235, (s32)btlevtcmd_AnimeChangePose, -3, 1, (s32)"M_N_7",
    65545, 35, 262235, (s32)btlevtcmd_AnimeChangePose, -3, 1, (s32)"M_B_1", 65545,
    150, 262235, (s32)btlevtcmd_AnimeChangePoseType, -3, 1, 43, 112, 393307,
    (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_BTL_NOKO_GUARD2", -250000000, 0, -29999995, 196699, (s32)btlevtcmd_SetFallAccel,
    -29999990, -229999591, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998,
    131125, -29999998, 5, 393307, (s32)btlevtcmd_FallPosition, -29999990, -30000000, -29999999,
    -29999998, 60, 327771, (s32)btlevtcmd_SetHomePos, -29999990, -30000000, -29999999, -29999998,
    131163, (s32)evt_snd_sfxoff, -29999995, 393307, (s32)evt_btl_camera_shake_h, 0, 2, 0,
    10, 13, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 327771, (s32)btlevtcmd_SetRotate, -29999990, 0, 0, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -29999990, 1, (s32)"PKO_F_1", 65545, 50, 262235, (s32)btlevtcmd_AnimeChangePose,
    -29999990, 1, (s32)"PKO_H_1", 262235, (s32)btlevtcmd_AnimeChangePose, -29999990, 2, (s32)"PKO_H_2",
    262235, (s32)btlevtcmd_OffPartsAttribute, -29999990, 2, 16777216, 393307, (s32)btlevtcmd_SetPartsRotateOffset, -29999990,
    1, 20, 0, 0, 393307, (s32)btlevtcmd_SetPartsRotateOffset, -29999990, 2,
    -20, 0, 0, 65541, 20, 393307, (s32)btlevtcmd_AddPartsRotate, -29999990,
    1, 0, 0, 2, 393307, (s32)btlevtcmd_AddPartsRotate, -29999990, 2,
    0, 0, -2, 65545, 1, 6, 65541, 10,
    262235, (s32)btlevtcmd_OnPartsAttribute, -29999990, 1, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -29999990,
    2, 16777216, 65545, 2, 262235, (s32)btlevtcmd_OffPartsAttribute, -29999990, 1,
    16777216, 262235, (s32)btlevtcmd_OffPartsAttribute, -29999990, 2, 16777216, 65545, 2,
    6, 196699, (s32)btlevtcmd_KillUnit, -29999990, 0, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985,
    65539, 99, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 131163, (s32)evt_btl_camera_off_posoffset_manual, 0, 262235, (s32)_color_lv_set, -3,
    1, -29999986, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

#ifdef VERSION_G8ME01
s32 partyNokotarouAttack_TsuranukiKoura[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, 1, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 327771, (s32)evt_btl_camera_set_posoffset,
    0, 20, 0, 0, 65545, 20, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 4, 196699, (s32)evt_btl_camera_set_zoom, 0, 400, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv,
    -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163, (s32)btlevtcmd_AcGetDifficulty, -30000000,
    131126, -30000000, 3, 65570, -30000000, 65576, -3, 131122,
    -30000000, 25, 131122, -29999999, 15, 65572, -2, 131122,
    -30000000, 24, 131122, -29999999, 21, 65572, -1, 131122,
    -30000000, 22, 131122, -29999999, 24, 65572, 0, 131122,
    -30000000, 20, 131122, -29999999, 25, 65572, 1, 131122,
    -30000000, 17, 131122, -29999999, 27, 65572, 2, 131122,
    -30000000, 15, 131122, -29999999, 30, 42, 131122, -30000000,
    12, 131122, -29999999, 30, 49, 589915, (s32)btlevtcmd_AcSetParamAll, 7,
    200, 178, -30000000, -29999999, 20, 61, -250000000, 327771,
    (s32)btlevtcmd_AcSetGaugeParam, 60, 80, 100, 100, 131163, (s32)btlevtcmd_AcSetFlag, 0,
    327771, (s32)btlevtcmd_SetupAC, -2, 6, 1, 0, 65545, 22,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 3, -1, 65647, -29999985, 65539,
    5, 196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000, 131096, -30000000, 0,
    65545, 1, 65540, 5, 33, 65630, (s32)_change_koura_pose_fast, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 1, 0, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 50, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_NOKO_IPPATSU1", -29999987, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 3, -29999987, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, 0,
    131122, -30000000, 15, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 15,
    65630, (s32)_koura_rotate_start, 112, 110, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 131163,
    (s32)_tsuranuki_effect_control, -2, 112, 131163, (s32)btlevtcmd_StartAC, 1, 65647, -29999986,
    131122, -29999995, 5, 65541, -29999995, 196699, (s32)btlevtcmd_AcGetOutputParam, 2,
    -30000000, 65570, -30000000, 65576, 1, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    1, 1, 0, 65572, 2, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    1, 1, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 24,
    65572, 3, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 1, 2,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 36, 65572, 4, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 1, 1, 3, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    1, 45, 49, 262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -29999987,
    131097, -29999987, -1, 196699, (s32)btlevtcmd_AcGetOutputParam, 1, -29999999, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 5, -29999999, 262235, (s32)btlevtcmd_GetUnitWork, -2, 4,
    -30000000, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -29999999, 131127, -30000000,
    -29999999, 131128, -30000000, 100, 196699, (s32)evt_snd_sfx_pit, -29999987, -30000000,
    33, 65545, 1, 131122, -29999995, 5, 6, 112,
    65627, (s32)btlevtcmd_ResultAC, 65631, -29999986, 196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000,
    131096, -30000000, 0, 65631, -29999985, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    1, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_K_2",
    65541, 10, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 12, 0,
    65545, 1, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_K_1",
    65541, 16, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 20, 0,
    65545, 1, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_H_1",
    65541, 14, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 20, 0,
    65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_ACROBAT_SHAKE1", 0, 65545, 40, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 1, 2, 1, 65630, (s32)_restore_koura_pose, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 65545, 30, 65540, 99,
    33, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1,
    0, 0, 262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -29999987, 131163,
    (s32)evt_snd_sfxoff, -29999987, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_NOKO_IPPATSU2", 0, 65627, (s32)btlevtcmd_StopAC,
    65631, -29999985, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, 0, 131163,
    (s32)evt_snd_sfxoff, -29999987, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_NOKO_SHUBIBIN2", 0, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 327771, (s32)evt_btl_camera_set_posoffset,
    0, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    50, 131122, -29999990, 0, 65539, 10, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229989760, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -250000000, -250000000, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, 0, 0,
    393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256, -29999994, 131097,
    -29999994, 1, 131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 33, 131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 33, 131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 33, 65540, 50, 33, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 0, 393307, (s32)btlevtcmd_CommandPreCheckCounter, -2,
    -29999997, -29999996, 256, -30000000, 131097, -30000000, 0, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 1, 2, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    1, 0, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0,
    65630, (s32)_koura_rotate_stop, 33, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102, -30000000,
    2, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131328, -29999995,
    196699, (s32)btlevtcmd_AcGetOutputParam, 2, -29999991, 131101, -29999991, 4, 131126,
    -29999991, 4, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, -29999991, -29999994, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect,
    -29999994, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000,
    196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994, 32, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2,
    -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1, 33, 32, 393307,
    (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256, -29999995, 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1, 33, 65539,
    50, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131097, -29999997, -1,
    131125, -29999990, 1, 65540, 10, 33, 65539, 80,
    262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2,
    400, -29999999, -29999998, 0, 0, 0, 327771, (s32)btlevtcmd_SetPartsWork,
    -2, 1, 2, 1, 65546, 100, 65539, 90,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131127, -30000000,
    -1, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, 0, 0, 0, 393307, (s32)btlevtcmd_ACRStart,
    -2, 0, 9, 9, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994,
    -29999993, 131096, -29999994, 2, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000,
    393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000, 1, 0, 0, 0, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    1, 12, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999693, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 30, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PNK_E_1", 65545, 10, 393307, (s32)btlevtcmd_ACRStart, -2, 49, 79,
    79, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131097, -29999994,
    2, 65627, (s32)evt_audience_acrobat_notry, 65630, (s32)_koura_rotate_stop, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PNK_E_2", 65541, 6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate,
    -2, 0, 45, 0, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PNK_S_1", 65541, 6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate,
    -2, 0, 15, 0, 6, 65540, 99, 33,
    65630, (s32)_koura_rotate_stop, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_E_2", 65541,
    6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 45,
    0, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_E_3", 65541,
    6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 15,
    0, 6, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult,
    -30000000, 1, 0, 0, 0, 65545, 60, 65540,
    99, 32, 65627, (s32)evt_audience_acrobat_notry, 33, 65630, (s32)_restore_koura_pose, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 65545, 30, 65539, 99,
    65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630,
    (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};
#else
s32 partyNokotarouAttack_TsuranukiKoura[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, 1, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 327771, (s32)evt_btl_camera_set_posoffset,
    0, 20, 0, 0, 65545, 20, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 4, 196699, (s32)evt_btl_camera_set_zoom, 0, 400, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv,
    -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163, (s32)btlevtcmd_AcGetDifficulty, -30000000,
    131126, -30000000, 3, 65570, -30000000, 65576, -3, 131122,
    -30000000, 25, 131122, -29999999, 15, 65572, -2, 131122,
    -30000000, 24, 131122, -29999999, 21, 65572, -1, 131122,
    -30000000, 22, 131122, -29999999, 24, 65572, 0, 131122,
    -30000000, 20, 131122, -29999999, 25, 65572, 1, 131122,
    -30000000, 17, 131122, -29999999, 27, 65572, 2, 131122,
    -30000000, 15, 131122, -29999999, 30, 42, 131122, -30000000,
    12, 131122, -29999999, 30, 49, 589915, (s32)btlevtcmd_AcSetParamAll, 7,
    200, 178, -30000000, -29999999, 20, 61, -250000000, 327771,
    (s32)btlevtcmd_AcSetGaugeParam, 60, 80, 100, 100, 131163, (s32)btlevtcmd_AcSetFlag, 0,
    327771, (s32)btlevtcmd_SetupAC, -2, 6, 1, 0, 65545, 22,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 3, -1, 65647, -29999985, 65539,
    5, 196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000, 131096, -30000000, 0,
    65545, 1, 65540, 5, 33, 65630, (s32)_change_koura_pose_fast, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 1, 0, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 50, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_NOKO_IPPATSU1", -29999987, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 3, -29999987, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, 0,
    131122, -30000000, 15, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 15,
    65630, (s32)_koura_rotate_start, 112, 110, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 131163,
    (s32)_tsuranuki_effect_control, -2, 112, 131163, (s32)btlevtcmd_StartAC, 1, 65647, -29999986,
    131122, -29999995, 5, 65541, -29999995, 196699, (s32)btlevtcmd_AcGetOutputParam, 2,
    -30000000, 65570, -30000000, 65576, 1, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    1, 1, 0, 65572, 2, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    1, 1, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 24,
    65572, 3, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 1, 2,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 36, 65572, 4, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 1, 1, 3, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    1, 45, 49, 262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -29999987,
    131097, -29999987, -1, 196699, (s32)btlevtcmd_AcGetOutputParam, 1, -29999999, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 5, -29999999, 262235, (s32)btlevtcmd_GetUnitWork, -2, 4,
    -30000000, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -29999999, 131127, -30000000,
    -29999999, 131128, -30000000, 100, 196699, (s32)evt_snd_sfx_pit, -29999987, -30000000,
    33, 65545, 1, 131122, -29999995, 5, 6, 112,
    65627, (s32)btlevtcmd_ResultAC, 65631, -29999986, 196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000,
    131096, -30000000, 0, 65631, -29999985, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    1, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_K_2",
    65541, 10, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 12, 0,
    65545, 1, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_K_1",
    65541, 16, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 20, 0,
    65545, 1, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_H_1",
    65541, 14, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 20, 0,
    65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_ACROBAT_SHAKE1", 0, 65545, 40, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 1, 2, 1, 65630, (s32)_restore_koura_pose, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 65545, 30, 65540, 99,
    33, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1,
    0, 0, 262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -29999987, 131163,
    (s32)evt_snd_sfxoff, -29999987, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_NOKO_IPPATSU2", 0, 65627, (s32)btlevtcmd_StopAC,
    65631, -29999985, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, 0, 131163,
    (s32)evt_snd_sfxoff, -29999987, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_NOKO_SHUBIBIN2", 0, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 327771, (s32)evt_btl_camera_set_posoffset,
    0, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    50, 131122, -29999990, 0, 65539, 10, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229989760, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -250000000, -250000000, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, 0, 0,
    393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256, -29999994, 131097,
    -29999994, 1, 131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 33, 131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 33, 131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 33, 65540, 50, 33, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 0, 393307, (s32)btlevtcmd_CommandPreCheckCounter, -2,
    -29999997, -29999996, 256, -30000000, 131097, -30000000, 0, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 1, 2, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    1, 0, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0,
    65630, (s32)_koura_rotate_stop, 33, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102, -30000000,
    2, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131328, -29999995,
    196699, (s32)btlevtcmd_AcGetOutputParam, 2, -29999991, 131101, -29999991, 4, 131126,
    -29999991, 4, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, -29999991, -29999994, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect,
    -29999994, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000,
    196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994, 32, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2,
    -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1, 33, 32, 393307,
    (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256, -29999995, 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1, 33, 65539,
    50, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131097, -29999997, -1,
    131125, -29999990, 1, 65540, 10, 33, 65539, 80,
    262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2,
    400, -29999999, -29999998, 0, 0, 0, 327771, (s32)btlevtcmd_SetPartsWork,
    -2, 1, 2, 1, 65546, 100, 65539, 90,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131127, -30000000,
    -1, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, 0, 0, 0, 393307, (s32)btlevtcmd_ACRStart,
    -2, 0, 9, 9, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994,
    -29999993, 131096, -29999994, 2, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 12, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999693, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30,
    -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_E_1", 65545, 10,
    393307, (s32)btlevtcmd_ACRStart, -2, 49, 79, 79, 0, 196699,
    (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131097, -29999994, 2, 65627, (s32)evt_audience_acrobat_notry,
    65630, (s32)_koura_rotate_stop, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_E_2", 65541,
    6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 45,
    0, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_S_1", 65541,
    6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 15,
    0, 6, 65540, 99, 33, 65630, (s32)_koura_rotate_stop, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_E_2", 65541, 6, 65545, 1,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 45, 0, 6, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_E_3", 65541, 6, 65545, 1,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 15, 0, 6, 196699,
    (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000, 1, 0,
    0, 0, 65545, 60, 65540, 99, 32, 65627,
    (s32)evt_audience_acrobat_notry, 33, 65630, (s32)_restore_koura_pose, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    43, 65545, 30, 65539, 99, 65627, (s32)evt_audience_ap_recovery, 65627,
    (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};
#endif

EVT_BEGIN(nokotarou_appeal_event)
    CALL(btlevtcmd_RunDataEventChild, -2, 7)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 66)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MARIO_APPEAL1"), LW(0), LW(1), LW(2), 0)
    WAIT_FRAMES(58)
    CALL(btlevtcmd_AudienceAppeal, -2)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(party_win_reaction)
    CALL(btlevtcmd_CheckStatus, -2, 17, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PNK_Y_1"))
    END_IF
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
    -29999999, -29999998, 196699, (s32)evt_btl_camera_set_mode, 0, 12, 327771, (s32)evt_btl_camera_set_homing_unit_audience,
    0, -2, 1, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_btl_camera_set_zoom, 0, 100, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    50, 65647, -29999985, 131122, -30000000, 15, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 1, 45, 65630, (s32)_koura_rotate_start, 112, 131163, (s32)btlevtcmd_WaitEventEnd,
    -29999985, 65546, 1000, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_NOKO_ATTACK2", 0, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229991808, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 15,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, 0,
    0, 196699, (s32)_attack_aud, -29999997, 0, 196699, (s32)evt_btl_camera_set_mode, 0,
    3, 65647, -29999985, 65546, 1500, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 65546, 1000, 112, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 30,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 18, -1,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12,
    -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 8, -1, 65630, (s32)_restore_koura_pose,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229995904, 524379, (s32)btlevtcmd_MovePosition, -2, -29999994, -29999999, -29999998, 0,
    -1, 0, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_SetPos, -2, -29999992, -29999999, -29999998, 131163, (s32)btlevtcmd_WaitEventEnd,
    -29999985, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 nokotarou_revive_event[] = {
    262235, (s32)btlevtcmd_SetPartsDefenceTable, -29999990, -29999989, (s32)&defence, 196699, (s32)btlevtcmd_OffStatusFlag, -29999990,
    1, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table_nokotarou_stay, 2, 1,
};

static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static s32 defence_turn[] = {
    0, 0,
};

static StatusVulnerability regist = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

s32 entry_koura[] = {
    (s32)unit_koura, 0, 67108865, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

static void __makeTechMenuFunc(BattleWorkCommand* command, s32* count) {
    s32 techLv;

    techLv = partyGetTechLv(BattleTransPartyId(BattleGetPartyPtr(_battleWorkPointer)->currentKind));

    command->mWeaponTable[*count].mIndex = -1;
    command->mWeaponTable[*count].mItem = 0;
    command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_NokotarouKouraAttack;
    command->mWeaponTable[*count].field_0x4 = 0;
    command->mWeaponTable[*count].mIcon = ICON_150;
    command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
    (*count)++;

    if (techLv >= 0) {
        command->mWeaponTable[*count].mIndex = -1;
        command->mWeaponTable[*count].mItem = 0;
        command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_NokotarouSyubibinKoura;
        command->mWeaponTable[*count].field_0x4 = 0;
        command->mWeaponTable[*count].mIcon = ICON_151;
        command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
        (*count)++;
    }
    if (techLv >= 1) {
        command->mWeaponTable[*count].mIndex = -1;
        command->mWeaponTable[*count].mItem = 0;
        command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_NokotarouKouraGuard;
        command->mWeaponTable[*count].field_0x4 = 0;
        command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;
        command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
        (*count)++;
    }
    if (techLv >= 2) {
        command->mWeaponTable[*count].mIndex = -1;
        command->mWeaponTable[*count].mItem = 0;
        command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_NokotarouTsuranukiKoura;
        command->mWeaponTable[*count].field_0x4 = 0;
        command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;
        command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
        (*count)++;
    }
}

USER_FUNC(_check_mario_move_count) {
    s32 index = event->args[0];
    BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);

    evtSetValue(event, index, mario->movesRemaining);
    return EVT_RETURN_DONE;
}

USER_FUNC(_color_lv_set) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id, index, set, value;

    id = evtGetValue(event, args[0]);
    set = evtGetValue(event, args[1]);
    index = args[2];
    value = evtGetValue(event, index);
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    if (set) {
        unit->mMoveColorLv = value;
    } else {
        evtSetValue(event, index, unit->mMoveColorLv);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_tsuranuki_effect_control) {
    BattleWork* wp;
    BattleUnit* unit;
    BattleUnitPart* part;
    EffectEntry* effect;
    Vec pos;
    s32 id, target;

    id = evtGetValue(event, event->args[0]);
    wp = _battleWorkPointer;
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    part = BtlUnit_GetPartsPtr(unit, 1);
    if (isFirstCall) {
        event->userdatap[0] = effNokotarouEntry(0, 1000, pos.x, pos.y, pos.z, unit->mSizeMultiplier);
        part->work[2] = 0;
        part->work[1] = 0;
        event->userdata[1] = 0;
    }
    target = part->work[1] * 100;
    if (event->userdata[1] != target) {
        if (event->userdata[1] < target) {
            event->userdata[1] += 10;
            if (event->userdata[1] > target) {
                event->userdata[1] = target;
            }
        } else {
            event->userdata[1] -= 10;
            if (event->userdata[1] < target) {
                event->userdata[1] = target;
            }
        }
    }
    {
        f32 size = (2.0f + 0.006f * event->userdata[1]);

        size *= unit->mSizeMultiplier;
        effect = event->userdatap[0];
        ((EffNokotarouWork*)effect->userdata)->position.x = pos.x;
        ((EffNokotarouWork*)effect->userdata)->position.y = pos.y;
        ((EffNokotarouWork*)effect->userdata)->position.z = pos.z;
        ((EffNokotarouWork*)effect->userdata)->size = size;
    }
    if (part->work[2]) {
        part->work[2] = 0;
        effSoftDelete(effect);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

static USER_FUNC(_check_guard_koura) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    BattleUnit* koura;
    s32 id, index;

    id = evtGetValue(event, args[0]);
    index = args[1];
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    if (!(unit->mAttributeFlags & 0x20)) {
        evtSetValue(event, index, -1);
        return EVT_RETURN_DONE;
    }
    koura = BtlUnit_GetGuardKouraPtr(unit);
    if (!koura) {
        evtSetValue(event, index, -1);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, index, koura->unitId);
    return EVT_RETURN_DONE;
}
