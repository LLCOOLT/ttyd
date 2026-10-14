#include "battle/battle.h"
#include "battle/battle_database_common.h"
#include "battle/battle_stage.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "driver/msgdrv.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_party.h"
#include "system.h"
#include "driver/animdrv.h"
#include "pmario_sound.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_disp.h"


void _btlYoshiDisp(CameraId camera, f32* p);
void _yoshi_slide_move_sound(void* w, void* s);
static void __makeTechMenuFunc(BattleWorkCommand* command, s32* count);

typedef struct YoshiGundanPart {
    f32 x, y, z;
    f32 vx, vy, vz;
    u8 pad18[0xC];
    u8 frameCount;
    u8 frame;
    u8 pad26[2];
    s32 delay;
    s32 state;
} YoshiGundanPart;

typedef struct YoshiGundanWork {
    s32 state;
    YoshiGundanPart parts[256];
    s32 pad3004;
    f32 timer;
} YoshiGundanWork;

void psndSFX_pos(s32 id, Vec* position);
#include "eff/eff_kemu_test.h"
#include "eff/n64/eff_sweat_n64.h"
f32 sinfd(f32 degrees);
#define UF32(u, o) (*(f32*)((u8*)(u) + (o)))
#define US32(u, o) (*(s32*)((u8*)(u) + (o)))
typedef struct YoshiSweatWork {
    s32 pad0;
    f32 x;
    f32 y;
    f32 z;
} YoshiSweatWork;

typedef struct YoshiSlideW {
    u8 pad[0x224];
    s32 a;
    s32 b;
} YoshiSlideW;

typedef struct YoshiSlideS {
    u8 pad[0xC];
    const char* name;
} YoshiSlideS;


USER_FUNC(_attack_aud);
USER_FUNC(_get_attack_aud_no);
USER_FUNC(btlevtcmd_AddPartsRotate);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_AnimeWaitPlayComplete);
USER_FUNC(btlevtcmd_AudienceAppeal);
USER_FUNC(btlevtcmd_CalculateFaceDirection);
USER_FUNC(btlevtcmd_ChangeFaceDirection);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_DivePartsPosition);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetHitPos);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetMoveFrame);
USER_FUNC(btlevtcmd_GetPartsWork);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetStatusMg);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_OnPartsAttribute);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_RunDataEventChild);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetMoveSoundDataWork);
USER_FUNC(btlevtcmd_SetMoveSpeed);
USER_FUNC(btlevtcmd_SetPartsFallAccel);
USER_FUNC(btlevtcmd_SetPartsMoveSpeed);
USER_FUNC(btlevtcmd_SetPartsPos);
USER_FUNC(btlevtcmd_SetPartsRotateOffset);
USER_FUNC(btlevtcmd_SetPartsWork);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRotate);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitEventEnd);
USER_FUNC(evt_btl_camera_set_homing_unit_audience);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveSpeedLv);
USER_FUNC(evt_btl_camera_set_zoom);
USER_FUNC(evt_eff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_random);
USER_FUNC(yoshi_original_color_anim_set);
USER_FUNC(_gundan_yoshi_run_effect);
USER_FUNC(_wait_yoshig_complete);
USER_FUNC(_wait_yoshig_run);
USER_FUNC(_check_swallow_attribute);
USER_FUNC(_get_swallow_param);
USER_FUNC(_get_nomikomi_hit_position);
USER_FUNC(btl_yoshi_yoroyoro_jump_move);
USER_FUNC(btl_yoshi_yoroyoro_jump_calc_param);
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
extern s32 btlevtcmd_AcSetOutputParam[];
extern s32 btlevtcmd_AcSetParamAll[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AnimeSetPoseSoundTable[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_AudienceDeclareACResult[];
extern s32 btlevtcmd_AudienceDeclareAcrobatResult[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_CommandCheckDamage[];
extern s32 btlevtcmd_CommandGetWeaponActionLv[];
extern s32 btlevtcmd_CommandGetWeaponAddress[];
extern s32 btlevtcmd_CommandPayWeaponCost[];
extern s32 btlevtcmd_CommandPreCheckDamage[];
extern s32 btlevtcmd_DamageDirect[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetExp[];
extern s32 btlevtcmd_GetFaceDirection[];
extern s32 btlevtcmd_GetHeight[];
extern s32 btlevtcmd_GetPartyTechLv[];
extern s32 btlevtcmd_GetResultAC[];
extern s32 btlevtcmd_GetResultPrizeLv[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetTakeoffPosition[];
extern s32 btlevtcmd_GetUnitWork[];
extern s32 btlevtcmd_InviteApInfoReport[];
extern s32 btlevtcmd_JumpPartsPosition[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_OffAttribute[];
extern s32 btlevtcmd_OnAttribute[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResultAC[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetDispOffset[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetPartsDispOffset[];
extern s32 btlevtcmd_SetPartsRotate[];
extern s32 btlevtcmd_SetPartsScale[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SetupAC[];
extern s32 btlevtcmd_StartAC[];
extern s32 btlevtcmd_StopAC[];
extern s32 btlevtcmd_StoreExp[];
extern s32 btlevtcmd_TransStageFloorPosition[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_ac_timing_flag_onoff[];
extern s32 btlevtcmd_ftof[];
extern s32 btlevtcmd_ftomsec[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_audience_acrobat_notry[];
extern s32 evt_audience_ap_recovery[];
extern s32 evt_btl_camera_noshake[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_homing_unitparts[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_env_blur_on[];
extern s32 evt_sub_intpl_get_value[];
extern s32 evt_sub_intpl_init[];
extern s32 subset_attack_ready_jump_event[];
extern s32 weaponGetPowerDefault[];
extern s32 weaponGetPowerFromPartyAttackLv[];

__declspec(section ".data") u64 lbl_80379A00;
__declspec(section ".data") u64 fd_yoshi_negone_one_374;
__declspec(section ".data") u64 lbl_80379A10;
__declspec(section ".data") u64 fd_yoshi_one_negone_373;
__declspec(section ".data") u64 lbl_80379A20;
__declspec(section ".data") u64 fd_yoshi_negone_one_360;
__declspec(section ".data") u64 lbl_80379A30;
__declspec(section ".data") u64 fd_yoshi_one_negone_359;
PoseTableEntry pose_table_yoshi_stay[25];
static BattleDataEntry data_table[8];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
PoseTableEntry pose_table_egg_g[4];
PoseTableEntry pose_table_egg_y[4];
PoseTableEntry pose_table_egg_p[4];
BattleUnitKindPart unitpartsdata_Party_Yoshi[7];
BattleUnitKind unitdata_Party_Yoshi;
static s32 battle_entry_event[59];
static s32 init_event[54];
static s32 damage_event[16];
s32 partyWeapon_YoshiNormalAttack[48];
s32 partyWeapon_YoshiNomikomi_Shot[48];
s32 partyWeapon_YoshiNomikomi_Spew[48];
s32 partyWeapon_YoshiNomikomi_Dmg0[48];
s32 partyWeapon_YoshiNomikomi_Fire[48];
s32 partyWeapon_YoshiNomikomi_Involved[48];
s32 partyWeapon_YoshiEggAttack_Minimini[48];
s32 partyWeapon_YoshiCallGuard[48];
s32 posesound_normal_attack[75];
s32 partyYoshiAttack_NormalAttack[1025];
s32 partyYoshiAttack_Nomikomi[1000];
s32 partyYoshiAttack_EggAttack[1266];
s32 _egg_attack_event[195];
s32 partyYoshiAttack_CallGuard[553];
s32 yoshi_appeal_event[39];
static s32 party_win_reaction[25];
static s32 attack_audience_event[290];
static s32 attack_event[2];
static s32 wait_event[6];
s32 _yoshig_tpl_no_tbl[2];


__declspec(section ".data") u64 lbl_80379A00 = 0xBF8000003F800000;

__declspec(section ".data") u64 fd_yoshi_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") u64 lbl_80379A10 = 0x3F800000BF800000;

__declspec(section ".data") u64 fd_yoshi_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") u64 lbl_80379A20 = 0xBF8000003F800000;

__declspec(section ".data") u64 fd_yoshi_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") u64 lbl_80379A30 = 0x3F800000BF800000;

__declspec(section ".data") u64 fd_yoshi_one_negone_359 = 0x3F800000BF800000;

PoseTableEntry pose_table_yoshi_stay[] = {
    {9, "PYS_D_5"},
    {2, "PYS_D_5"},
    {3, "PYS_X_1"},
    {4, "PYS_D_2"},
    {5, "PYS_X_1"},
    {1, "PYS_N_1"},
    {27, "PYS_D_3"},
    {28, "PYS_S_1"},
    {37, "PYS_G_2"},
    {31, "PYS_G_1"},
    {39, "PYS_D_1"},
    {40, "PYS_W_1"},
    {42, "PYS_R_1"},
    {57, "PYS_D_2"},
    {56, "PYS_D_2"},
    {60, "PYS_D_4"},
    {61, "PYS_D_2"},
    {65, "PYS_T_1"},
    {52, "PYS_I_1"},
    {67, "PYS_C_1"},
    {66, "PYS_O_1"},
    {64, "PYS_F_1"},
    {49, "PYS_F_1"},
    {45, "PYS_G_1"},
    {69, "PYS_S_1"},
};

static BattleDataEntry data_table[] = {
    {5, yoshi_appeal_event},
    {6, attack_audience_event},
    {1, __makeTechMenuFunc},
    {48, btldefaultevt_Dummy},
    {64, party_win_reaction},
    {7, subset_attack_ready_jump_event},
    {47, btldefaultevt_avoid_counter_event},
    {0, NULL},
};

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static StatusVulnerability regist = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

PoseTableEntry pose_table_egg_g[] = {
    {28, "CHU_C_1"},
    {31, "CHU_C_1"},
    {39, "CHU_C_1"},
    {69, "CHU_C_1"},
};

PoseTableEntry pose_table_egg_y[] = {
    {28, "CHU_C_2"},
    {31, "CHU_C_2"},
    {39, "CHU_C_2"},
    {69, "CHU_C_2"},
};

PoseTableEntry pose_table_egg_p[] = {
    {28, "CHU_C_3"},
    {31, "CHU_C_3"},
    {39, "CHU_C_3"},
    {69, "CHU_C_3"},
};

BattleUnitKindPart unitpartsdata_Party_Yoshi[] = {
    {1, "btl_un_yoshi", "c_babyyoshi", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, 0x9, 0, pose_table_yoshi_stay},
    {2, "btl_un_yoshi", "c_tamago", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, 0x13010000, 0, pose_table_egg_g},
    {3, "btl_un_yoshi", "c_tamago", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, 0x13010000, 0, pose_table_egg_g},
    {4, "btl_un_yoshi", "c_tamago", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, 0x13010000, 0, pose_table_egg_g},
    {5, "btl_un_yoshi", "c_tamago", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, 0x13010000, 0, pose_table_egg_g},
    {6, "btl_un_yoshi", "c_tamago", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, 0x13010000, 0, pose_table_egg_g},
    {7, "btl_un_yoshi", "c_tamago", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, 0x13010000, 0, pose_table_egg_g},
};

BattleUnitKind unitdata_Party_Yoshi = {
    226,
    "btl_un_yoshi",
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
    8,
    28,
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
    7,
    unitpartsdata_Party_Yoshi,
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
    CALL(btlevtcmd_SetMoveSoundDataWork, -2, STRING("SFX_PARTY_BATTLE_SUBMOVE1L"), STRING("SFX_PARTY_BATTLE_SUBMOVE1R"), 0, 6, 6, 0, 0)
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -2, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 2, 0)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 15, 13)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 6, 6)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(yoshi_original_color_anim_set, -2)
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

s32 partyWeapon_YoshiNormalAttack[] = {
    (s32)"btl_wn_pys_normal", 22020096, 0, (s32)"msg_pys_hip_drop", 1677721600, 1065353216, 16868402, (s32)weaponGetPowerFromPartyAttackLv,
    1, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, (s32)"msg_ac_hip_drop", 217239, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyYoshiAttack_NormalAttack, 658020, 168101125, 84213760,
};

s32 partyWeapon_YoshiNomikomi_Shot[] = {
    (s32)"btl_wn_pys_lv1", 22085632, 0, (s32)"msg_pys_nomikomi", 1677983744, 1065353216, 17130546, (s32)weaponGetPowerFromPartyAttackLv,
    2, 4, 3, 5, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 393986, (s32)"msg_ac_nomikomi", 131143, 2043, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyYoshiAttack_Nomikomi, 100, 328960, 0,
};

s32 partyWeapon_YoshiNomikomi_Spew[] = {
    (s32)"btl_wn_pys_lv1", 22085632, 0, (s32)"msg_pys_nomikomi", 1677983744, 1065353216, 17130546, (s32)weaponGetPowerFromPartyAttackLv,
    2, 4, 3, 5, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 328450, (s32)"msg_ac_nomikomi", 131143, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyYoshiAttack_Nomikomi, 100, 328965, 0,
};

s32 partyWeapon_YoshiNomikomi_Dmg0[] = {
    (s32)"btl_wn_pys_lv1", 22085632, 0, (s32)"msg_pys_nomikomi", 1677852672, 1065353216, 17130546, (s32)weaponGetPowerDefault,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, (s32)"msg_ac_nomikomi", 131136, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyYoshiAttack_Nomikomi, 100, 0, 0,
};

s32 partyWeapon_YoshiNomikomi_Fire[] = {
    (s32)"btl_wn_pys_lv1", 22085632, 0, (s32)"msg_pys_nomikomi", 1677852672, 1065353216, 17130546, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 16777986, (s32)"msg_ac_nomikomi", 131136, 2047, -2147483644,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyYoshiAttack_Nomikomi, 100, 0, 0,
};

s32 partyWeapon_YoshiNomikomi_Involved[] = {
    0, 0, 0, 0, 1677721600, 0, 0, (s32)weaponGetPowerFromPartyAttackLv,
    1, 4, 2, 5, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603616, 537927680, 770, 0, 131136, 2047, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 partyWeapon_YoshiEggAttack_Minimini[] = {
    (s32)"btl_wn_pys_lv2", 22151168, 0, (s32)"msg_pys_wonder_egg", 1677918208, 1065353216, 33907762, (s32)weaponGetPowerDefault,
    1, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, (s32)"msg_ac_wonder_egg", 131075, 2047, -2147475456,
    0, 0, 0, 0, 100, 66977792, 0, 0,
    0, 0, 0, 0, (s32)partyYoshiAttack_EggAttack, 100, 197376, 0,
};

s32 partyWeapon_YoshiCallGuard[] = {
    (s32)"btl_wn_pys_lv3", 22216704, 0, (s32)"msg_pys_taigun_yoshi", 1678114816, 1065353216, 17130546, (s32)weaponGetPowerFromPartyAttackLv,
    1, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, (s32)"msg_ac_taigun_yoshi", 131095, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyYoshiAttack_CallGuard, 1315940, 336856325, 335872000,
};

s32 posesound_normal_attack[] = {
    (s32)"PYS_W_1", 1008981770, (s32)_yoshi_slide_move_sound, (s32)"SFX_PARTY_BATTLE_MOVE1L", 1, (s32)"PYS_W_1", 1048576000, (s32)_yoshi_slide_move_sound,
    (s32)"SFX_PARTY_BATTLE_MOVE1R", 1, (s32)"PYS_R_1", 1008981770, (s32)_yoshi_slide_move_sound, (s32)"SFX_PARTY_BATTLE_MOVE1L", 1, (s32)"PYS_R_1",
    1036831949, (s32)_yoshi_slide_move_sound, (s32)"SFX_PARTY_BATTLE_MOVE1R", 1, (s32)"PYS_R_4", 1008981770, (s32)_yoshi_slide_move_sound, (s32)"SFX_PARTY_BATTLE_MOVE1L",
    89391105, (s32)"PYS_R_4", 1028443341, (s32)_yoshi_slide_move_sound, (s32)"SFX_PARTY_BATTLE_MOVE1R", 89391105, (s32)"PYS_R_4", 1036831949,
    (s32)_yoshi_slide_move_sound, (s32)"SFX_PARTY_BATTLE_MOVE1L", 89391105, (s32)"PYS_R_4", 1041865114, (s32)_yoshi_slide_move_sound, (s32)"SFX_PARTY_BATTLE_MOVE1R", 89391105,
    (s32)"PYS_R_5", 1008981770, (s32)_yoshi_slide_move_sound, (s32)"SFX_PARTY_BATTLE_MOVE1L", 156434433, (s32)"PYS_R_5", 1023969417, (s32)_yoshi_slide_move_sound,
    (s32)"SFX_PARTY_BATTLE_MOVE1R", 156434433, (s32)"PYS_R_5", 1034594987, (s32)_yoshi_slide_move_sound, (s32)"SFX_PARTY_BATTLE_MOVE1L", 156434433, (s32)"PYS_R_5",
    1039068911, (s32)_yoshi_slide_move_sound, (s32)"SFX_PARTY_BATTLE_MOVE1R", 156434433, (s32)"PYS_A_3", 1008981770, (s32)_yoshi_slide_move_sound, (s32)"SFX_PARTY_BATTLE_MOVE1L",
    156434433, (s32)"PYS_A_3", 1034594987, (s32)_yoshi_slide_move_sound, (s32)"SFX_PARTY_BATTLE_MOVE1R", 156434433, 0, 0,
    (s32)_yoshi_slide_move_sound, 0, 1,
};

s32 partyYoshiAttack_NormalAttack[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    131163, (s32)btlevtcmd_CommandPayWeaponCost, -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699,
    (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -1,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 250,
    65545, 20, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 2, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3, -1,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 4, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    5, 100, 262235, (s32)btlevtcmd_AnimeSetPoseSoundTable, -2, 1, (s32)posesound_normal_attack, 196699,
    (s32)btlevtcmd_AcSetOutputParam, 1, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_W_1",
    110, 131122, -30000000, 0, 65541, 25, 131125, -30000000,
    4, 131122, -29999999, 2387, 131127, -29999999, -30000000, 131128,
    -29999999, 100, 262235, (s32)btlevtcmd_SetUnitWork, -2, 4, -29999999, 65545,
    1, 6, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_R_5",
    65545, 25, 196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts,
    0, -2, 1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    1, 196699, (s32)evt_btl_camera_set_zoom, 0, 350, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229995904, 458843, (s32)btlevtcmd_GetTakeoffPosition, -2, -29999997, -29999996, -30000000, -29999999,
    -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998, 1,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_J_1A", 196699, (s32)btlevtcmd_SetFallAccel,
    -2, -229999693, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 25, 131125, -29999999, 35,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_JUMP1", -250000000, 0, -250000000, 65647,
    -29999985, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -29999985, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -29999985,
    196699, (s32)btlevtcmd_GetPartyTechLv, -2, -30000000, 65570, -30000000, 65572, 2,
    589915, (s32)btlevtcmd_AcSetParamAll, 5, 180, 178, 23, 25, 20,
    61, 1, 327771, (s32)btlevtcmd_AcSetGaugeParam, 60, 80, 100, 100,
    65572, 1, 589915, (s32)btlevtcmd_AcSetParamAll, 5, 180, 178, 23,
    25, 25, 76, 1, 327771, (s32)btlevtcmd_AcSetGaugeParam, 75, 100,
    100, 100, 42, 589915, (s32)btlevtcmd_AcSetParamAll, 5, 180, 178,
    23, 25, 34, 100, 1, 327771, (s32)btlevtcmd_AcSetGaugeParam, 100,
    100, 100, 100, 49, 131163, (s32)btlevtcmd_AcSetFlag, 72, 327771,
    (s32)btlevtcmd_SetupAC, -2, 6, 1, 0, 112, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 25, -1, 131163, (s32)btlevtcmd_WaitEventEnd,
    -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_3", 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -29999994, -29999993, -29999992, 131125, -29999993, 40,
    131122, -29999990, -229998976, 65647, -29999985, 131163, (s32)btlevtcmd_StartAC, 1,
    65627, (s32)btlevtcmd_ResultAC, 112, 458843, (s32)btl_yoshi_yoroyoro_jump_calc_param, -2, -29999994, -29999993,
    -29999992, -29999990, -29999991, 458843, (s32)btl_yoshi_yoroyoro_jump_move, -2, -29999994, -29999993,
    -29999992, -29999990, -29999991, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 131122, -29999987,
    1, 196699, (s32)btlevtcmd_AcGetOutputParam, 2, -29999986, 65539, 50, 131101,
    -29999987, 2, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 1048832,
    -29999995, 32, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256,
    -29999995, 33, 65570, -29999995, 65579, 2, 65579, 3,
    65579, 6, 65579, 4, 46, 65572, 1, 42,
    49, 262235, (s32)btlevtcmd_AnimeSetPoseSoundTable, -2, 1, 0, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 2, 0, 131098, -29999987, 2, 393307, (s32)btlevtcmd_ACRStart,
    -2, 0, 20, 20, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994,
    -29999993, 32, 131122, -29999994, 1, 33, 131096, -29999987,
    1, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PYS_J_1B", 131096, -29999994, 2, 131122, -30000000, 3,
    131122, -29999999, 6, 131127, -29999985, -60, 32, 131122,
    -30000000, 1, 131122, -29999999, 9, 131127, -29999985, -40,
    33, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 12, 0, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 65545, 15, 131096,
    -29999994, 2, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, -60, -25,
    0, 33, 65541, -30000000, 131122, -29999998, -29999999, 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_BTL_YOSHI_ATTACK1", 0, 65541, -29999998, 327771, (s32)btlevtcmd_AddRotate, -2,
    0, 0, -29999985, 65545, 1, 6, 6, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2,
    0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_1",
    65545, 15, 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_1",
    33, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 4, 0,
    0, 0, -1, 131097, -29999995, 1, 65627, (s32)btlevtcmd_StopAC,
    131096, -29999995, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33,
    131096, -29999995, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33,
    131096, -29999995, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131122, -29999985,
    -29999999, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 131126, -29999985,
    -29999999, 131128, -29999985, 10, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000,
    -29999999, -29999998, -29999985, 0, 0, 0, -1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_D_1", 327771, (s32)btlevtcmd_SetDispOffset, -2, 0,
    -7, 0, 393307, (s32)evt_btl_camera_shake_h, 0, 4, 0, 10,
    13, 65545, 40, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_5",
    327771, (s32)btlevtcmd_SetDispOffset, -2, 0, 0, 0, 65545, 54,
    65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65540, 95, 33, 196699,
    (s32)btlevtcmd_ac_timing_flag_onoff, 1, 1, 65545, 2, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 0,
    1, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102, -30000000, 2, 131101,
    -29999987, -29999986, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131328,
    -29999995, 32, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131072,
    -29999995, 33, 196699, (s32)btlevtcmd_GetPartyTechLv, -2, -30000000, 65570, -30000000,
    65572, 2, 196699, (s32)btlevtcmd_AcGetOutputParam, 2, -30000000, 65570, -30000000,
    65577, 6, 131122, -30000000, 2, 65577, 4, 131122,
    -30000000, 1, 65577, 2, 131122, -30000000, 0, 42,
    131122, -30000000, -1, 49, 65572, 1, 196699, (s32)btlevtcmd_AcGetOutputParam,
    2, -30000000, 65570, -30000000, 65577, 4, 131122, -30000000,
    1, 65577, 2, 131122, -30000000, 0, 42, 131122,
    -30000000, -1, 49, 42, 196699, (s32)btlevtcmd_AcGetOutputParam, 2, -30000000,
    65570, -30000000, 65577, 4, 131122, -30000000, 1, 65577,
    2, 131122, -30000000, 0, 42, 131122, -30000000, -1,
    49, 49, 131101, -30000000, 0, 131122, -29999999, -30000000,
    131122, -29999998, -29999987, 131126, -29999998, 1, 131099, -29999999,
    -29999998, 131122, -29999999, -29999998, 33, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997,
    -29999999, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999991, -29999999,
    -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -29999991, -29999999, -29999998, 131122,
    -29999999, -29999987, 131125, -29999999, 1, 131099, -29999999, -29999986,
    262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, -30000000, -29999994, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988,
    -29999994, 33, 32, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 33,
    32, 131101, -29999987, -29999986, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997,
    -29999996, 256, -29999995, 32, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997,
    -29999996, 0, -29999995, 33, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1,
    33, 65539, 90, 131125, -29999987, 1, 131100, -29999987,
    -29999986, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999796, 131125, -29999999, 40, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 20, -1, 65540, 50,
    33, 65627, (s32)btlevtcmd_StopAC, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -250000000, -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1,
    110, 393307, (s32)btlevtcmd_ACRStart, -2, 0, 15, 15, 20,
    112, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 25, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 16, -1, 196699, (s32)btlevtcmd_ACRGetResult,
    -29999994, -29999993, 65570, -29999994, 65577, 2, 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000, 1, 0, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_Y_1", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete,
    -2, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_Y_1", 196699,
    (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 42, 65627, (s32)evt_audience_acrobat_notry, 49, 65627,
    (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65539, 95, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 65539, 99, 131163,
    (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    1,
};

s32 partyYoshiAttack_Nomikomi[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 0, 196699,
    (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235, (s32)btlevtcmd_AttackDeclare,
    -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost, -2,
    196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -29999985, 196699,
    (s32)btlevtcmd_AcSetDifficulty, -2, -29999985, 131163, (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126, -30000000,
    3, 65570, -30000000, 65576, -3, 131122, -30000000, 160,
    131122, -29999999, 40, 65572, -2, 131122, -30000000, 140,
    131122, -29999999, 30, 65572, -1, 131122, -30000000, 120,
    131122, -29999999, 25, 65572, 0, 131122, -30000000, 100,
    131122, -29999999, 20, 65572, 1, 131122, -30000000, 80,
    131122, -29999999, 10, 65572, 2, 131122, -30000000, 50,
    131122, -29999999, 5, 42, 131122, -30000000, 30, 131122,
    -29999999, 2, 49, 589915, (s32)btlevtcmd_AcSetParamAll, 3, -30000000, -29999999,
    0, 100, -250000000, -250000000, -250000000, 131163, (s32)btlevtcmd_AcSetFlag, 15,
    327771, (s32)btlevtcmd_SetupAC, -2, 15, 1, 0, 196699, (s32)evt_btl_camera_set_mode,
    0, 10, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -1,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    250, 65545, 22, 131163, (s32)btlevtcmd_StartAC, 1, 65539, 5,
    196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000, 131096, -30000000, 0, 65545,
    1, 65540, 5, 33, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997,
    -29999996, 256, -29999995, 131096, -29999995, 5, 196699, (s32)btlevtcmd_GetStatusMg,
    -2, -29999994, 131132, -29999994, 40, 458843, (s32)_get_nomikomi_hit_position, -2,
    -29999997, -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997,
    -30000000, -29999994, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 458843,
    (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998, 1, -29999985, 196699,
    (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 80, -1, 0, 393307, (s32)btlevtcmd_CommandCheckDamage, -2,
    -29999997, -29999996, 256, -29999995, 33, 196699, (s32)btlevtcmd_GetStatusMg, -2,
    -29999994, 131132, -29999994, 40, 458843, (s32)_get_nomikomi_hit_position, -2, -29999997,
    -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000,
    -29999994, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, 80, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    65627, (s32)btlevtcmd_ResultAC, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_2", 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_BTL_YOSHI_SWALLOW1", 0, 131097, -29999995, 1, 131096, -29999995,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33, 131096, -29999995,
    6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33, 131096, -29999995,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33, 65545, 50,
    65540, 90, 33, 65545, 7, 196699, (s32)_get_swallow_param, -29999997,
    -29999993, 131096, -29999993, -1, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, (s32)partyWeapon_YoshiNomikomi_Dmg0, -2147483392, -29999995, 65545, 43, 65540, 90,
    33, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131103, -30000000, 2, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)partyWeapon_YoshiNomikomi_Dmg0, -2147483392, -29999995, 65545,
    43, 65540, 90, 33, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_YOSHI_SWALLOW2", 0,
    262235, (s32)_check_swallow_attribute, -29999997, 8, -30000000, 131097, -30000000, 0,
    458843, (s32)btlevtcmd_DamageDirect, -29999997, -29999996, 0, 0, 7, 1,
    65545, 13, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_7", 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_BTL_YOSHI_SWALLOW5", 0, 65545, 34, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PYS_A_5", 65545, 54, 65540, 90, 33, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 350, 458843,
    (s32)btlevtcmd_DamageDirect, -29999997, -29999996, 0, 0, 2, 1, 65545,
    3, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 12, 655451, (s32)btlevtcmd_DivePosition, -29999997, -30000000,
    -29999999, -29999998, 5, 0, 0, 0, -1, 196699,
    (s32)btlevtcmd_OnAttribute, -29999997, 16777216, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_YOSHI_SWALLOW3", 0, 65545,
    6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_3", 65545, 7,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_sub_random, 99, -30000000, 131101, -30000000, -29999993, 107,
    196699, (s32)evt_env_blur_on, 0, 600, 109, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PYS_A_4", 196699, (s32)btlevtcmd_ftomsec, 22, -30000000, 65546, -30000000,
    65644, -29999985, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_YOSHI_NOMIKOMI6", 0, 196699, (s32)btlevtcmd_OffAttribute,
    -29999997, 16777216, 262235, (s32)_check_swallow_attribute, -29999997, 2, -30000000, 131096,
    -30000000, 0, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)partyWeapon_YoshiNomikomi_Spew,
    -2147483392, -29999995, 32, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    (s32)partyWeapon_YoshiNomikomi_Shot, -2147483392, -29999995, 33, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102,
    -30000000, 2, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect,
    -29999994, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994,
    32, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 33, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete,
    -2, 1, 393307, (s32)btlevtcmd_ACRStart, -2, 0, 15, 15,
    20, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 65570, -29999994, 65577,
    2, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000,
    1, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PYS_Y_1", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PYS_Y_1", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 42, 65627,
    (s32)evt_audience_acrobat_notry, 49, 109, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 65540, 90,
    33, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 1, 110, 262235,
    (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999,
    -29999998, 112, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_YOSHI_SWALLOW5", 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PYS_A_7", 65545, 26, 262235, (s32)_check_swallow_attribute, -29999997,
    1, -29999999, 262235, (s32)_check_swallow_attribute, -29999997, 4, -29999998, 196699,
    (s32)btlevtcmd_GetExp, -29999997, -30000000, 131163, (s32)btlevtcmd_StoreExp, -30000000, 196699, (s32)btlevtcmd_KillUnit,
    -29999997, 0, 65545, 8, 131097, -29999999, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_6", 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_YOSHI_SWALLOW7", 0,
    65545, 50, 65540, 90, 32, 131096, -29999998, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_5", 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_YOSHI_SWALLOW4",
    0, 65545, 54, 65540, 90, 33, 33, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_4", 65545, 22, 110, 65545,
    18, 112, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 15, 131125, -29999999, 15,
    131122, -29999997, -30000000, 131122, -29999996, -29999999, 131122, -29999995,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -29999997, 240, 983131, (s32)evt_eff,
    (s32)"eff", (s32)"breath_fire", 1, -30000000, -29999999, -29999998, -29999997, -29999996,
    -29999995, 1, 2, 60, -229999488, -229969280, 65545, 60,
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)partyWeapon_YoshiNomikomi_Fire, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999990, -29999989, 65539, 10, 131096,
    -29999990, -1, 65540, 90, 33, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999990, -29999989, (s32)partyWeapon_YoshiNomikomi_Fire, -2147483392, -29999995, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999990,
    -29999989, 65540, 10, 65539, 90, 65627, (s32)btlevtcmd_StopAC, 65627,
    (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65539, 95, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1,
    -29999995, 131096, -29999995, 0, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 65540, 99, 33,
    458843, (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998, -229995904, -29999995,
    131100, -29999995, 20, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, 0, -1, 0, 65540, 99, 33, 65647,
    -29999985, 131126, -29999995, 1, 131122, -29999994, -29999995, 131126,
    -29999994, 10, 393307, (s32)btlevtcmd_ACRStart, -2, -29999994, -29999995, -29999995,
    0, 112, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    -29999995, -1, 0, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 196699, (s32)btlevtcmd_ACRGetResult,
    -29999994, -29999993, 131096, -29999994, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PYS_O_1", 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0, 0,
    0, 65545, 20, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_J_1B",
    327771, (s32)evt_sub_intpl_init, 4, 0, 360, 30, 65541, 30,
    65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, 0, -30000000, 0,
    65545, 1, 6, 33, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 partyYoshiAttack_EggAttack[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -30000000, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    131163, (s32)btlevtcmd_CommandPayWeaponCost, -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)partyWeapon_YoshiEggAttack_Minimini,
    262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)partyWeapon_YoshiEggAttack_Minimini, -29999997, -29999996, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    2, 3, -29999997, 327771, (s32)btlevtcmd_SetPartsWork, -2, 2, 4,
    -29999996, 327771, (s32)btlevtcmd_SetPartsWork, -2, 2, 5, 0, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 2, 6, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    2, 7, 0, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)partyWeapon_YoshiEggAttack_Minimini, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)partyWeapon_YoshiEggAttack_Minimini, -29999990,
    -29999989, 327771, (s32)btlevtcmd_SetPartsWork, -2, 7, 3, -29999990, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 7, 4, -29999989, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    7, 5, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 7, 6,
    0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 7, 7, 0, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)partyWeapon_YoshiEggAttack_Minimini, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)partyWeapon_YoshiEggAttack_Minimini, -29999990,
    -29999989, 327771, (s32)btlevtcmd_SetPartsWork, -2, 6, 3, -29999990, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 6, 4, -29999989, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    6, 5, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 6, 6,
    0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 6, 7, 0, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)partyWeapon_YoshiEggAttack_Minimini, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)partyWeapon_YoshiEggAttack_Minimini, -29999990,
    -29999989, 327771, (s32)btlevtcmd_SetPartsWork, -2, 5, 3, -29999990, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 5, 4, -29999989, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    5, 5, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 5, 6,
    0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 5, 7, 0, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)partyWeapon_YoshiEggAttack_Minimini, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)partyWeapon_YoshiEggAttack_Minimini, -29999990,
    -29999989, 327771, (s32)btlevtcmd_SetPartsWork, -2, 4, 3, -29999990, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 4, 4, -29999989, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    4, 5, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 4, 6,
    0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 4, 7, 0, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)partyWeapon_YoshiEggAttack_Minimini, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)partyWeapon_YoshiEggAttack_Minimini, -29999990,
    -29999989, 327771, (s32)btlevtcmd_SetPartsWork, -2, 3, 3, -29999990, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 3, 4, -29999989, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    3, 5, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 3, 6,
    0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 3, 7, 0, 196699,
    (s32)evt_btl_camera_set_mode, 0, 10, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1,
    -1, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom,
    0, 300, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2,
    -30000000, 196699, (s32)btlevtcmd_GetPartyTechLv, -2, -30000000, 65570, -30000000, 65572,
    2, 131122, -29999999, 4, 42, 131122, -29999999, 3,
    49, 131163, (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126, -30000000, 3, 65570,
    -30000000, 65576, -3, 131122, -30000000, 480, 65572, -2,
    131122, -30000000, 360, 65572, -1, 131122, -30000000, 240,
    65572, 0, 131122, -30000000, 180, 65572, 1, 131122,
    -30000000, 150, 65572, 2, 131122, -30000000, 100, 42,
    131122, -30000000, 60, 49, 589915, (s32)btlevtcmd_AcSetParamAll, 0, -30000000,
    -29999999, 0, -250000000, -250000000, -250000000, -250000000, 131163, (s32)btlevtcmd_AcSetFlag,
    0, 196699, (s32)btlevtcmd_AcSetOutputParam, 1, 0, 327771, (s32)btlevtcmd_SetupAC, -2,
    20, 1, 60, 65545, 22, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 272, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 131163, (s32)btlevtcmd_StartAC, 1, 131122, -29999988, 2, 65539,
    5, 196699, (s32)btlevtcmd_AcGetOutputParam, 0, -29999987, 131125, -29999987, 1,
    131099, -29999988, -29999987, 196699, (s32)btlevtcmd_AcGetOutputParam, 1, -30000000, 131097,
    -30000000, 0, 65627, (s32)btlevtcmd_StopAC, 65546, 500, 196699, (s32)btlevtcmd_AcGetOutputParam,
    0, -29999987, 131101, -29999987, 1, 196699, (s32)btlevtcmd_AcGetOutputParam, 0,
    -29999987, 131125, -29999987, 1, 65540, 25, 32, 196699,
    (s32)btlevtcmd_AudienceDeclareACResult, (s32)partyWeapon_YoshiEggAttack_Minimini, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_5",
    65545, 54, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65540, 95,
    33, 33, 65545, 1, 65540, 5, 33, 131122,
    -30000000, -29999988, 131126, -30000000, 1, 65570, -30000000, 65576,
    2, 131122, -30000000, 0, 65576, 3, 131122, -30000000,
    1, 42, 131122, -30000000, 2, 49, 262235, (s32)btlevtcmd_GetResultPrizeLv,
    -5, -30000000, -29999994, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131125, -29999999, 40, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000,
    -29999999, -29999998, 196699, (s32)btlevtcmd_AudienceDeclareACResult, (s32)partyWeapon_YoshiEggAttack_Minimini, -29999994, 65539, 10,
    196699, (s32)evt_sub_random, 2, -30000000, 327771, (s32)btlevtcmd_SetPartsWork, -2, -29999988,
    0, -30000000, 65570, -30000000, 65572, 1, 262235, (s32)btlevtcmd_AnimeSetPoseTable,
    -2, -29999988, (s32)pose_table_egg_y, 65572, 2, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2,
    -29999988, (s32)pose_table_egg_p, 42, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, -29999988, (s32)pose_table_egg_g,
    49, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999988, 69, 327771, (s32)btlevtcmd_SetPartsWork,
    -2, -29999988, 1, 4, 327771, (s32)btlevtcmd_SetPartsWork, -2, -29999988,
    2, (s32)partyWeapon_YoshiEggAttack_Minimini, 65539, 20, 196699, (s32)btlevtcmd_GetStatusMg, -2, -29999994,
    393307, (s32)btlevtcmd_SetPartsScale, -2, -29999988, -229998976, -229998976, -229998976, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_8", 65545, 10, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PYS_A_12", 196699, (s32)btlevtcmd_GetStatusMg, -2, -29999995, 131132,
    -29999995, 10, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, -29999995, 131125, -29999999, -29999995,
    393307, (s32)btlevtcmd_SetPartsPos, -2, -29999988, -30000000, -29999999, -29999998, 393307,
    (s32)btlevtcmd_SetPartsDispOffset, -2, -29999988, 0, 0, 0, 393307, (s32)btlevtcmd_SetPartsRotate,
    -2, -29999988, 0, 0, 0, 393307, (s32)btlevtcmd_SetPartsRotateOffset, -2,
    -29999988, 0, 0, 0, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, -29999988,
    50331648, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_YOSHI_EGG1", 0, 131122, -29999985, 0,
    110, 393307, (s32)btlevtcmd_SetPartsRotateOffset, -2, -29999988, 0, 6, 0,
    65541, 30, 393307, (s32)btlevtcmd_AddPartsRotate, -2, -29999988, 0, 0,
    48, 65545, 1, 6, 393307, (s32)btlevtcmd_SetPartsRotate, -2, -29999988,
    0, 0, 0, 112, 110, 131122, -29999995, -29999988,
    131126, -29999995, 2, 131132, -29999995, 10, 131130, -29999995,
    15, 196699, (s32)btlevtcmd_GetStatusMg, -2, -30000000, 131132, -29999995, -30000000,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, -29999995, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_SetPartsFallAccel, -2, -29999988, -229999796, 524379, (s32)btlevtcmd_JumpPartsPosition, -2,
    -29999988, -30000000, -29999999, -29999998, 30, -1, 112, 65545,
    10, 131125, -29999988, 1, 65540, 5, 65539, 25,
    327771, (s32)btlevtcmd_SetPartsWork, -2, 2, 6, -1, 327771, (s32)btlevtcmd_SetPartsWork,
    -2, 3, 6, -1, 327771, (s32)btlevtcmd_SetPartsWork, -2, 4,
    6, -1, 327771, (s32)btlevtcmd_SetPartsWork, -2, 5, 6, -1,
    327771, (s32)btlevtcmd_SetPartsWork, -2, 6, 6, -1, 327771, (s32)btlevtcmd_SetPartsWork,
    -2, 7, 6, -1, 131122, -29999988, -29999987, 65539,
    26, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999988, 6, -30000000, 131096,
    -30000000, -1, 327771, (s32)btlevtcmd_SetPartsWork, -2, -29999988, 6, 1,
    131122, -29999986, -29999988, 65539, 27, 131126, -29999986, 1,
    131101, -29999986, 2, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999988, 3,
    -30000000, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999986, 3, -29999999, 131096,
    -30000000, -29999999, 327771, (s32)btlevtcmd_SetPartsWork, -2, -29999986, 6, 0,
    33, 65540, 27, 33, 33, 131126, -29999988, 1,
    131101, -29999988, 2, 65540, 26, 33, 131122, -29999988,
    2, 65539, 28, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999988, 6,
    -30000000, 65570, -30000000, 65572, 0, 327771, (s32)btlevtcmd_GetPartsWork, -2,
    -29999988, 3, -30000000, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999988, 4,
    -29999999, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -30000000, -29999999, 256, -29999994,
    327771, (s32)btlevtcmd_SetPartsWork, -2, -29999988, 5, -29999994, 131096, -29999994,
    1, 131122, -29999986, -29999988, 65539, 29, 131125, -29999986,
    1, 131100, -29999986, -29999987, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999988,
    3, -30000000, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999986, 3, -29999999,
    131096, -30000000, -29999999, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999986, 6,
    -30000000, 131097, -30000000, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2, -29999986,
    6, 2, 33, 33, 65540, 29, 33, 33,
    65572, 1, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999988, 3, -30000000,
    327771, (s32)btlevtcmd_GetPartsWork, -2, -29999988, 4, -29999999, 393307, (s32)btlevtcmd_CommandPreCheckDamage,
    -2, -30000000, -29999999, 256, -29999994, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    -29999988, 5, -29999994, 42, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999988,
    3, -30000000, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999988, 4, -29999999,
    393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -30000000, -29999999, 1048832, -29999994, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, -29999988, 5, -29999994, 49, 131098, -29999988,
    -29999987, 131125, -29999988, 1, 65540, 28, 33, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 131122,
    -29999988, 2, 65539, 30, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, -29999988, 50331648, 327771, (s32)btlevtcmd_GetPartsWork, -2,
    -29999988, 0, -30000000, 65570, -30000000, 65572, 1, 131122,
    -29999994, (s32)"PYS_A3_1", 131122, -29999993, (s32)"PYS_A3_2", 131122, -29999992, (s32)"PYS_A3_3",
    65572, 2, 131122, -29999994, (s32)"PYS_A4_1", 131122, -29999993, (s32)"PYS_A4_2",
    131122, -29999992, (s32)"PYS_A4_3", 42, 131122, -29999994, (s32)"PYS_A2_1", 131122,
    -29999993, (s32)"PYS_A2_2", 131122, -29999992, (s32)"PYS_A2_3", 49, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, -29999994, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, -29999992, 65545, 7, 65647, -29999985,
    65630, (s32)_egg_attack_event, 112, 327771, (s32)btlevtcmd_SetPartsWork, -2, -29999988, 7,
    -29999985, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 65545, 10, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 69, 65539, 90, 131097, -29999988,
    -29999987, 131125, -29999988, 1, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999988,
    3, -29999997, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999988, 4, -29999996,
    65540, 30, 33, 65627, (s32)btlevtcmd_StopAC, 393307, (s32)btlevtcmd_ACRStart, -2,
    0, 15, 15, 20, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993,
    65570, -29999994, 65577, 2, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000,
    393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000, 1, 0, 0, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_Y_1", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_Y_1", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2,
    1, 42, 65627, (s32)evt_audience_acrobat_notry, 49, 65627, (s32)evt_audience_ap_recovery, 65627,
    (s32)btlevtcmd_InviteApInfoReport, 65539, 95, 131122, -29999988, 2, 65539, 96,
    327771, (s32)btlevtcmd_GetPartsWork, -2, -29999988, 7, -29999985, 131097, -29999985,
    0, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 327771, (s32)btlevtcmd_SetPartsWork, -2, -29999988,
    7, 0, 33, 131125, -29999988, 1, 131100, -29999988,
    -29999987, 65540, 96, 33, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, 0, -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 65546, 2000, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

EVT_BEGIN(_egg_attack_event)
    CALL(btlevtcmd_GetStatusMg, -2, LW(6))
    MULTIPLY_FLOAT(LW(6), 10)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    ADD(LW(1), LW(6))
    CALL(btlevtcmd_SetPartsPos, -2, LW(12), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_OffPartsAttribute, -2, LW(12), 50331648)
    CALL(btlevtcmd_SetPartsMoveSpeed, -2, LW(12), FLOAT(5.0f))
    CALL(btlevtcmd_SetPartsFallAccel, -2, LW(12), FLOAT(0.099609375f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetMoveFrame, -2, LW(0), LW(1), LW(2), FLOAT(5.0f), LW(5))
        CALL(btlevtcmd_GetStatusMg, -2, LW(6))
        MULTIPLY_FLOAT(LW(6), 6)
        CALL(btlevtcmd_SetPartsRotateOffset, -2, LW(12), 0, LW(6), 0)
        LOOP(LW(5))
            CALL(btlevtcmd_AddPartsRotate, -2, LW(12), 0, 0, 48)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_EGG3"), 0)
    CALL(btlevtcmd_DivePartsPosition, -2, LW(12), LW(0), LW(1), LW(2), 0, 25, 0, 0, -1)
    CALL(btlevtcmd_OnPartsAttribute, -2, LW(12), 50331648)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_EGG2"), 0)
    CALL(evt_eff, STRING(""), STRING("bomb"), 0, LW(0), LW(1), LW(2), FLOAT(0.5996094f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_GetPartsWork, -2, LW(12), 5, LW(6))
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
        GOTO(89)
    END_IF
    CALL(btlevtcmd_GetPartsWork, -2, LW(12), 2, LW(0))
    CALL(btlevtcmd_GetPartsWork, -2, LW(12), 6, LW(1))
    IF_INT_EQUAL(LW(1), 0)
        CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(0), 1073872896, LW(5))
        ELSE
        CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(0), 1073873152, LW(5))
    END_IF
    LABEL(89)
    RETURN
EVT_END()

s32 partyYoshiAttack_CallGuard[] = {
    131122, -29999988, (s32)partyWeapon_YoshiCallGuard, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996,
    131096, -29999997, -1, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33,
    131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7,
    131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163,
    (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126, -30000000, 3, 65570, -30000000, 65576,
    -3, 131122, -30000000, 280, 131122, -29999999, 18, 131122,
    -29999998, 25, 65572, -2, 131122, -30000000, 250, 131122,
    -29999999, 17, 131122, -29999998, 27, 65572, -1, 131122,
    -30000000, 240, 131122, -29999999, 16, 131122, -29999998, 29,
    65572, 0, 131122, -30000000, 240, 131122, -29999999, 15,
    131122, -29999998, 30, 65572, 1, 131122, -30000000, 200,
    131122, -29999999, 15, 131122, -29999998, 30, 65572, 2,
    131122, -30000000, 180, 131122, -29999999, 15, 131122, -29999998,
    30, 42, 131122, -30000000, 150, 131122, -29999999, 14,
    131122, -29999998, 30, 49, 589915, (s32)btlevtcmd_AcSetParamAll, 15, -30000000,
    178, -29999999, -29999998, 20, 61, -250000000, 327771, (s32)btlevtcmd_AcSetGaugeParam,
    60, 80, 100, 100, 131163, (s32)btlevtcmd_AcSetFlag, 64, 327771,
    (s32)btlevtcmd_SetupAC, -2, 6, 1, 0, 196699, (s32)evt_btl_camera_set_mode, 0,
    7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, 1, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 4, 196699, (s32)evt_btl_camera_set_zoom, 0, 400, 65545, 20,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_10", 196699, (s32)btlevtcmd_ftof, 24,
    -30000000, 65545, -30000000, 131163, (s32)btlevtcmd_StartAC, 1, 65627, (s32)btlevtcmd_ResultAC,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_11", 196699, (s32)btlevtcmd_GetHeight, -2,
    -29999994, 196699, (s32)btlevtcmd_GetStatusMg, -2, -30000000, 131132, -29999994, -30000000,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -29999999,
    -29999994, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999995, 131127, -29999995, 30,
    983131, (s32)evt_eff, 0, (s32)"kiss", 3, -30000000, -29999999, -29999998,
    -29999995, 0, 0, 0, 0, 0, 0, 0,
    393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_ENM_TOGENOKO_CALL1", -30000000, -29999999, -29999998, 0, 196699,
    (s32)btlevtcmd_ftof, 33, -30000000, 65647, -29999985, 65545, -30000000, 112,
    393307, (s32)btlevtcmd_ACRStart, -2, 0, -30000000, -30000000, 20, 196699,
    (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 65570, -29999994, 65577, 2, 393307,
    (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PYS_Y_1", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_Y_1", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 42, 65627, (s32)evt_audience_acrobat_notry,
    131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 110, 65546, 166, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 43, 112, 49, 65644, -29999991, 65546,
    1000, 131163, (s32)_gundan_yoshi_run_effect, -2, 109, 65546, 166, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 393307,
    (s32)evt_btl_camera_shake_h, 0, 1, 0, 6000, 0, 65546, 1000,
    131163, (s32)_wait_yoshig_run, -2, 131122, -29999985, 0, 65539, 70,
    131096, -29999997, -1, 131097, -29999985, 0, 131163, (s32)btlevtcmd_WaitEventEnd,
    -29999985, 33, 131163, (s32)btlevtcmd_WaitEventEnd, -29999991, 65540, 90, 33,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988, 256, -29999994,
    131097, -29999994, 1, 131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 33, 131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 33, 131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 33, 65540, 75, 33, 196699, (s32)btlevtcmd_AcGetOutputParam,
    2, -29999986, 65647, -29999985, 65541, -29999986, 131101, -29999986,
    2, 196699, (s32)btlevtcmd_AcGetOutputParam, 2, -30000000, 131101, -30000000, 2,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 131072, -29999995,
    32, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 0,
    -29999995, 33, 32, 196699, (s32)btlevtcmd_AcGetOutputParam, 2, -30000000, 65570,
    -30000000, 65577, 6, 131122, -30000000, 2, 65577, 4,
    131122, -30000000, 1, 65577, 2, 131122, -30000000, 0,
    42, 131122, -30000000, -1, 49, 131101, -30000000, 0,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 131328, -29999995,
    262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, -30000000, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000,
    -29999999, -29999998, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994, 32, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 256, -29999995, 196699,
    (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 33, 33, 65545, 10, 6,
    112, 65539, 75, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 65540,
    70, 65539, 90, 131163, (s32)_wait_yoshig_complete, -2, 131163, (s32)evt_btl_camera_noshake,
    1, 65546, 500, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 131163,
    (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    1,
};

EVT_BEGIN(yoshi_appeal_event)
    CALL(btlevtcmd_RunDataEventChild, -2, 7)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 66)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MARIO_APPEAL1"), LW(0), LW(1), LW(2), 0)
    WAIT_FRAMES(40)
    CALL(btlevtcmd_AudienceAppeal, -2)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 43)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(party_win_reaction)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PYS_Y_1"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 1)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PYS_Y_1"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 1)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 43)
    RETURN
EVT_END()

static EVT_BEGIN(attack_audience_event)
    CALL(_get_attack_aud_no, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(15))
    SET_VALUE(LW(12), 2)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    ADD(LW(1), 10)
    CALL(btlevtcmd_SetPartsPos, -2, LW(12), LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        CALL(evt_btl_camera_set_mode, 0, 13)
        CALL(evt_btl_camera_set_homing_unit_audience, 0, -2, LW(12), LW(3))
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
        CALL(evt_btl_camera_set_zoom, 0, 200)
    END_SIBLING_EVENT
    CALL(evt_sub_random, 2, LW(0))
    CALL(btlevtcmd_SetPartsWork, -2, LW(12), 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(btlevtcmd_AnimeSetPoseTable, -2, LW(12), PTR(pose_table_egg_y))
        CASE_EQUAL(2)
        CALL(btlevtcmd_AnimeSetPoseTable, -2, LW(12), PTR(pose_table_egg_p))
        CASE_DEFAULT
        CALL(btlevtcmd_AnimeSetPoseTable, -2, LW(12), PTR(pose_table_egg_g))
    END_SWITCH
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(12), 69)
    CALL(btlevtcmd_SetPartsMoveSpeed, -2, LW(12), FLOAT(7.5f))
    CALL(btlevtcmd_SetPartsFallAccel, -2, LW(12), FLOAT(0.099609375f))
    CALL(btlevtcmd_OnPartsAttribute, -2, LW(12), 50331648)
    CALL(btlevtcmd_GetPartsWork, -2, LW(12), 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        SET_VALUE(LW(6), STRING("PYS_A3_1"))
        SET_VALUE(LW(7), STRING("PYS_A3_2"))
        SET_VALUE(LW(8), STRING("PYS_A3_3"))
        CASE_EQUAL(2)
        SET_VALUE(LW(6), STRING("PYS_A4_1"))
        SET_VALUE(LW(7), STRING("PYS_A4_2"))
        SET_VALUE(LW(8), STRING("PYS_A4_3"))
        CASE_DEFAULT
        SET_VALUE(LW(6), STRING("PYS_A2_1"))
        SET_VALUE(LW(7), STRING("PYS_A2_2"))
        SET_VALUE(LW(8), STRING("PYS_A2_3"))
    END_SWITCH
    CALL(btlevtcmd_AnimeChangePose, -2, 1, LW(6))
    CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 1)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, LW(8))
    BEGIN_SIBLING_EVENT
        WAIT_MS(1000)
        CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 43)
    END_SIBLING_EVENT
    WAIT_FRAMES(7)
    CALL(btlevtcmd_OffPartsAttribute, -2, LW(12), 50331648)
    CALL(_get_attack_aud_no, LW(3), LW(0), LW(1), LW(2))
    ADD(LW(1), 28)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetMoveFrame, -2, LW(0), LW(1), LW(2), FLOAT(5.0f), LW(5))
        CALL(btlevtcmd_SetPartsRotateOffset, -2, LW(12), 0, 6, 0)
        LOOP(LW(5))
            CALL(btlevtcmd_AddPartsRotate, -2, LW(12), 0, 0, 48)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_EGG3"), 0)
    CALL(btlevtcmd_DivePartsPosition, -2, LW(12), LW(0), LW(1), LW(2), 0, 25, 0, 0, -1)
    CALL(btlevtcmd_OnPartsAttribute, -2, LW(12), 50331648)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_EGG2"), 0)
    CALL(evt_eff, STRING(""), STRING("bomb"), 0, LW(0), LW(1), LW(2), FLOAT(0.5996094f), 0, 0, 0, 0, 0, 0, 0)
    CALL(_attack_aud, LW(3), 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        WAIT_MS(1500)
        CALL(evt_btl_camera_set_mode, 0, 0)
        WAIT_MS(500)
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

s32 _yoshig_tpl_no_tbl[] = {
    1179207494, 1246232576,
};

USER_FUNC(yoshi_original_color_anim_set) {
    BattleWork* wp = _battleWorkPointer;
    s32 id;
    BattleUnitPart* part;
    const char* name;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    BattleGetUnitPtr(wp, id);
    switch (pouchGetPartyColor(4)) {
    case 1:
        name = "c_babyyoshi2\0\0\0";
        break;
    case 2:
        name = "c_babyyoshi3\0\0\0";
        break;
    case 3:
        name = "c_babyyoshi4\0\0\0";
        break;
    case 4:
        name = "c_babyyoshi5\0\0\0";
        break;
    case 5:
        name = "c_babyyoshi6\0\0\0";
        break;
    case 6:
        name = "c_babyyoshi7\0\0\0";
        break;
    case 0:
    default:
        name = NULL;
        break;
    }
    if (isFirstCall) {
        if (name == NULL) {
            return EVT_RETURN_DONE;
        }
        part = BattleGetUnitPartsPtr(id, 1);
        animPoseGetAnimPosePtr(part->poseId);
        if (part->poseId != -1) {
            animPoseRelease(part->poseId);
            part->poseId = -1;
        }
    }
    if (animEffectAsync(name, 1)) {
        part = BattleGetUnitPartsPtr(id, 1);
        part->poseId = animPoseEntry(name, 1);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
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
    ADD_WEAPON(partyWeapon_YoshiNormalAttack)
    if (techLv >= 0) {
        ADD_WEAPON(partyWeapon_YoshiNomikomi_Shot)
    }
    if (techLv >= 1) {
        ADD_WEAPON(partyWeapon_YoshiEggAttack_Minimini)
    }
    if (techLv >= 2) {
        ADD_WEAPON(partyWeapon_YoshiCallGuard)
    }
}

USER_FUNC(btl_yoshi_yoroyoro_jump_calc_param) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    s32 id, outSpeed, outFrames;
    f32 tx, ty, tz, speed;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    tx = (f32)evtGetValue(event, args[1]);
    ty = (f32)evtGetValue(event, args[2]);
    tz = (f32)evtGetValue(event, args[3]);
    outSpeed = args[4];
    speed = evtGetFloat(event, outSpeed);
    unit = BattleGetUnitPtr(wp, id);
    outFrames = args[5];
    if (speed > 0.0f) {
        unit->mMoveSpeedXZ = speed;
    }
    if (unit->mMoveSpeedXZ <= 0.0f) {
        unit->mMoveSpeedXZ = 1.0f;
    }
    BtlUnit_SetMoveTargetPos(unit, tx, ty, tz);
    BtlUnit_GetPos(unit, &x, &y, &z);
    BtlUnit_SetMoveStartPos(unit, x, y, z);
    BtlUnit_SetMoveCurrentPos(unit, x, y, z);
    unit->mMoveDirection = angleABf(x, z, tx, tz);
    UF32(unit, 0x17C) = distABf(x, z, tx, tz);
    if (tx - x > 0.0f) {
        unit->moveDirection = 1;
    } else if (tx - x < 0.0f) {
        unit->moveDirection = -1;
    }
    UF32(unit, 0x17C) = __fabs(tx - x);
    US32(unit, 0x168) = 180;
    UF32(unit, 0x180) = (f32)US32(unit, 0x168);
    unit->mMoveSpeedY = 0.0f;
    unit->mMoveSpeedXZ = UF32(unit, 0x17C) / (f32)US32(unit, 0x168);
    evtSetFloat(event, outSpeed, unit->mMoveSpeedXZ);
    evtSetValue(event, outFrames, US32(unit, 0x168));
    return EVT_RETURN_DONE;
}

USER_FUNC(btl_yoshi_yoroyoro_jump_move) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    s32 id;
    f32 sweatAngle;
    EffectEntry* eff;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    evtGetValue(event, args[1]);
    evtGetValue(event, args[2]);
    evtGetValue(event, args[3]);
    evtGetFloat(event, args[4]);
    unit = BattleGetUnitPtr(wp, id);
    evtGetValue(event, args[5]);
    if (isFirstCall) {
        event->blocked = 1;
        event->userdata[1] = 20;
        event->userdata[2] = 0;
    }
    if (unit->mMoveCurrentPos.x != unit->mMoveTargetPos.x) {
        if (__fabs(unit->mMoveTargetPos.x - unit->mMoveCurrentPos.x) < unit->mMoveSpeedXZ) {
            unit->mMoveCurrentPos.x = unit->mMoveTargetPos.x;
        } else {
            unit->mMoveCurrentPos.x += unit->mMoveSpeedXZ * unit->moveDirection;
        }
    }
    if (unit->mMoveCurrentPos.z != unit->mMoveTargetPos.z) {
        if (__fabs(unit->mMoveTargetPos.z - unit->mMoveCurrentPos.z) < unit->mMoveSpeedXZ) {
            unit->mMoveCurrentPos.z = unit->mMoveTargetPos.z;
        } else if (unit->mMoveTargetPos.z - unit->mMoveStartPos.z > 0.0f) {
            unit->mMoveCurrentPos.z += unit->mMoveSpeedXZ;
        } else {
            unit->mMoveCurrentPos.z -= unit->mMoveSpeedXZ;
        }
    }
    sweatAngle = 10.0f * sinfd(180.0f + 360.0f * (UF32(unit, 0x180) - (f32)(US32(unit, 0x168) % 90)) / 90.0f);
    BtlUnit_GetPartsPtr(unit, 1);
    unit->mMoveCurrentPos.y = unit->mMoveSpeedY + (unit->mMoveStartPos.y + (unit->mMoveTargetPos.y - unit->mMoveStartPos.y) * (UF32(unit, 0x180) - (f32)US32(unit, 0x168)) / UF32(unit, 0x180));
    unit->mMoveSpeedY = sweatAngle;
    unit->work[5] = (s32)(75.0f - 25.0f * sinfd(360.0f * (UF32(unit, 0x180) - (f32)(US32(unit, 0x168) % 90)) / 90.0f));
    BtlUnit_SetPos(unit, unit->mMoveCurrentPos.x, unit->mMoveCurrentPos.y, unit->mMoveCurrentPos.z);
    event->userdata[1]++;
    if (event->userdata[1] > 20) {
        event->userdata[1] = 0;
        if (unit->moveDirection >= 0) {
            sweatAngle = -50.0f;
        } else {
            sweatAngle = 50.0f;
        }
        event->userdata[2] = (s32)effSweatN64Entry(1, 16, unit->mMoveCurrentPos.x, unit->mMoveCurrentPos.y + unit->mSizeMultiplier * (0.5f * BtlUnit_GetHeight(unit)), unit->mMoveCurrentPos.z, 5.0f * unit->mSizeMultiplier, sweatAngle);
    } else {
        eff = (EffectEntry*)event->userdata[2];
        if (event->userdata[1] < 16) {
            ((YoshiSweatWork*)eff->userdata)->x = unit->mMoveCurrentPos.x;
            ((YoshiSweatWork*)eff->userdata)->y = unit->mMoveCurrentPos.y + unit->mSizeMultiplier * (0.5f * BtlUnit_GetHeight(unit));
            ((YoshiSweatWork*)eff->userdata)->z = unit->mMoveCurrentPos.z;
        }
    }
    US32(unit, 0x168)--;
    if (US32(unit, 0x168) <= 0) {
        BtlUnit_SetPos(unit, unit->mMoveTargetPos.x, unit->mMoveTargetPos.y, unit->mMoveTargetPos.z);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

void _yoshi_slide_move_sound(void* w, void* s) {
    YoshiSlideW* ww = (YoshiSlideW*)w;
    YoshiSlideS* ss = (YoshiSlideS*)s;
    BtlUnit_snd_se((BattleUnit*)w, ss->name, -250000000, (s16)(ww->a * ww->b / 100));
}

USER_FUNC(_get_nomikomi_hit_position) {
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

USER_FUNC(_get_swallow_param) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    s32 id;
    s32 out;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    out = args[1];
    unit = BattleGetUnitPtr(wp, id);
    evtSetValue(event, out, unit->swallowRate);
    return EVT_RETURN_DONE;
}

USER_FUNC(_check_swallow_attribute) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    s32 id, out;
    u16 mask;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    mask = args[1];
    out = args[2];
    unit = BattleGetUnitPtr(wp, id);
    if ((u8)unit->swallowAttribute & mask) {
        evtSetValue(event, out, 1);
    } else {
        evtSetValue(event, out, 0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_wait_yoshig_run) {
    BattleUnit* unit;
    YoshiGundanWork* w;
    s32 id;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    w = (YoshiGundanWork*)unit->countersetWeapon;
    if (w == NULL) {
        return EVT_RETURN_BLOCK;
    }
    if (w->timer <= 0.0f) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_wait_yoshig_complete) {
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (unit->countersetWeapon) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

static inline s32 _gundan_part_update(YoshiGundanPart* p, s32 i) {
    switch (p->state) {
    case 0:
        p->state++;
        p->delay = irand(3);
        p->x = (f32)(-(i / 16 * 30 + 300) + irand(10));
        p->y = 0.0f;
        p->z = (f32)(i % 16 * 10 - 80);
        p->frame = irand(6);
        p->frameCount = irand(5);
        p->vx = 0.1f * (f32)irand(10) + 3.0f;
        p->vy = 0.0f;
        p->vz = 0.001f * (f32)(irand(2000) - 1000);
    case 1:
        if (p->delay > 0) {
            p->delay--;
            break;
        }
    case 2:
        p->z += p->vz;
        if (p->z >= 80.0f) {
            p->z = 80.0f;
            p->vz *= -1.0f;
        }
        if (p->z <= -80.0f) {
            p->z = -80.0f;
            p->vz *= -1.0f;
        }
        p->x += p->vx;
        if (p->x >= 300.0f) {
            p->x = 300.0f;
            p->vx = 0.0f;
            p->state = 999;
        }
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

USER_FUNC(_gundan_yoshi_run_effect) {
    BattleUnit* unit;
    YoshiGundanWork* w;
    YoshiGundanPart* p;
    s32 i;
    s32 allDone;
    Vec pos;
    s32 id;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        w = BattleAlloc(sizeof(YoshiGundanWork));
        unit->countersetWeapon = (BattleWeapon*)w;
        memset(w, 0, sizeof(YoshiGundanWork));
        w->state = 0;
        w->timer = 0.0f;
        event->userdata[0] = 0;
        event->userdata[1] = ((s32 (*)(const char*))psndSFXOn)("SFX_BTL_YOSHI_TAIGUN1\0\0");
    } else {
        w = (YoshiGundanWork*)unit->countersetWeapon;
    }
    switch (w->state) {
    case 0:
        w->state++;
    case 1:
        w->timer = 0.0f;
        allDone = TRUE;
        for (i = 0; i < 256; i++) {
            p = &w->parts[i];
            p->frameCount++;
            if (p->frameCount > 2) {
                p->frameCount = 0;
                p->frame++;
                if (p->frame >= 6) {
                    p->frame = 0;
                }
            }
            if (_gundan_part_update(p, i)) {
                allDone = FALSE;
            }
            w->timer += p->x;
        }
        if (event->userdata[0] > 0) {
            event->userdata[0]--;
        } else {
            f32 sc;
            p = &w->parts[irand(256)];
            sc = 1.0f + 0.05f * (f32)irand(20);
            effKemuTestEntry(0, p->x, 5.0f + p->y + (f32)irand(15), 65.0f, sc);
        }
        w->timer *= 0.00390625f;
        pos.x = w->timer;
        pos.y = 0.0f;
        pos.z = 0.0f;
        psndSFX_pos(event->userdata[1], &pos);
        if (allDone) {
            w->state = 999;
        }
        break;
    case 999:
        psndSFXOff(event->userdata[1]);
        BattleFree(unit->countersetWeapon);
        unit->countersetWeapon = NULL;
        return EVT_RETURN_DONE;
    }
    for (i = 0; i < 256; i++) {
        dispEntry(CAMERA_3D, dispCalcZ((Vec*)p), 2, (DispCallback)_btlYoshiDisp, &w->parts[i]);
    }
    return EVT_RETURN_BLOCK;
}
void _btlYoshiDisp(CameraId camera, f32* p) {
    f32* q;
    f32 s;

    if (p[3] < 0.0f) {
        s = 0.4f;
    } else {
        s = -0.4f;
    }
    ((void (*)(s32, GXColor, s32, f32, f32, f32, f32, f32))btlDispTexPlane)(((u8*)_yoshig_tpl_no_tbl)[((u8*)(q = p))[0x25]], (GXColor){255, 255, 255, 255}, 0, q[0], q[1] + 20.0f, q[2], s, 0.4f);
}
