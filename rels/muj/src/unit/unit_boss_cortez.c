#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_unit.h"
#include "battle/battle_audience.h"
#include "system.h"
#include "driver/effdrv.h"

typedef struct CortezWork { s16 state; s16 count; s16 audienceId[100]; s16 wait[100]; s16 timer[100]; s16 seq[100]; void* eff[100]; Vec srcPos[100]; Vec dstPos[100]; } CortezWork;
void BattleAudienceAddTargetNum(f32 a, f32 b);
void* effSpiritEntry(s32 type, s32 time, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, f32 scale);
void* effKumokumoN64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 a, f32 b, f32 c);
u8 psndSFX_get_vol(s32 id);
s32 entry_honeduka[12];

USER_FUNC(_cortez_check_drain_audience);
USER_FUNC(_make_cortez_work_area);
USER_FUNC(btlevtcmd_AddPartsRotate);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_DivePosition);
USER_FUNC(btlevtcmd_DrawLots);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetDamage);
USER_FUNC(btlevtcmd_GetDamagePartsId);
USER_FUNC(btlevtcmd_GetHitPos);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetHp);
USER_FUNC(btlevtcmd_GetMaxHp);
USER_FUNC(btlevtcmd_GetMoveFrame);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_JumpPartsPosition);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_OnAttribute);
USER_FUNC(btlevtcmd_OnPartsAttribute);
USER_FUNC(btlevtcmd_OnUnitFlag);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHitCursorOffset);
USER_FUNC(btlevtcmd_SetHitOffset);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetKissHitOffset);
USER_FUNC(btlevtcmd_SetPartsDefenceAttrTable);
USER_FUNC(btlevtcmd_SetPartsDefenceTable);
USER_FUNC(btlevtcmd_SetPartsDispOffset);
USER_FUNC(btlevtcmd_SetPartsFallAccel);
USER_FUNC(btlevtcmd_SetPartsPos);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SpawnUnit);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_TransStageFloorPosition);
USER_FUNC(btlevtcmd_WaitEventEnd);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_intpl_get_value);
USER_FUNC(evt_sub_intpl_init);
USER_FUNC(evt_sub_random);
static USER_FUNC(_check_zenei_kouei);
USER_FUNC(_cortez_recovery_audience);
USER_FUNC(_cortez_drain_energy);
USER_FUNC(_cortez_collect_energy);
USER_FUNC(_cortez_get_sfx_vol);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AnimeChangeGroup[];
extern s32 btlevtcmd_AnimeSetPoseSoundTable[];
extern s32 btlevtcmd_AnimeWaitPlayComplete[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckPhase[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_ClearAllStatus[];
extern s32 btlevtcmd_GetCoin[];
extern s32 btlevtcmd_GetDataFromDataTable[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetExp[];
extern s32 btlevtcmd_GetPartsPos[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_JumpPartsContinue[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_OffAttribute[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PhaseEventStartDeclare[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_RecoverHp[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_RunHitEventDirect[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetCutBaseOffset[];
extern s32 btlevtcmd_SetCutHeight[];
extern s32 btlevtcmd_SetCutWidth[];
extern s32 btlevtcmd_SetDiveSound[];
extern s32 btlevtcmd_SetHp[];
extern s32 btlevtcmd_SetMaxMoveCount[];
extern s32 btlevtcmd_SetPartsRotateOffset[];
extern s32 btlevtcmd_SetStayPose[];
extern s32 btlevtcmd_SetTalkPose[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_StatusWindowOnOff[];
extern s32 btlevtcmd_StopWaitEvent[];
extern s32 btlevtcmd_StoreCoin[];
extern s32 btlevtcmd_StoreExp[];
extern s32 btlevtcmd_WaitAttackEnd[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_ftomsec[];
extern s32 btlevtcmd_reset_turn[];
extern s32 btlevtcmd_snd_se[];
extern s32 cortez_weapon_get_home_height[];
extern s32 cortez_weapon_set_formation_attribute[];
extern s32 evt_batstage_return_aud_dark_base[];
extern s32 evt_batstage_set_aud_dark[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveto[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_eff[];
extern s32 evt_fade_end_wait[];
extern s32 evt_fade_entry[];
extern s32 evt_fade_set_anim_ofs_pos[];
extern s32 evt_fade_set_anim_virtual_pos[];
extern s32 evt_msg_print[];
extern s32 evt_snd_sfx_vol[];
extern s32 evt_snd_sfxoff[];
extern s32 evt_snd_sfxon[];
extern s32 unit_boss_cortez_claw[];
extern s32 unit_boss_cortez_rapier[];
extern s32 unit_boss_cortez_saber[];
extern s32 unit_boss_cortez_sword[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_boss_cortez_negone_one_374;
__declspec(section ".data") s32 fd_boss_cortez_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_cortez___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_cortez___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_cortez_one_negone_373;
__declspec(section ".data") s32 fd_boss_cortez___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_cortez_one_381[1];
__declspec(section ".data") u64 fd_boss_cortez_negone_one_360;
__declspec(section ".data") s32 fd_boss_cortez_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_cortez___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_cortez___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_cortez_one_negone_359;
__declspec(section ".data") s32 fd_boss_cortez___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_cortez_one_364[1];
BattleUnitKind unit_boss_cortez;
static __declspec(section ".data") StatusVulnerability regist;
__declspec(section ".data") BattleUnitDefense defence_mode1;
__declspec(section ".data") BattleUnitDefenseAttr defence_attr_mode1;
__declspec(section ".data") s32 defence_mode2_upper_head[2];
__declspec(section ".data") s32 defence_attr_mode2_upper_head[2];
__declspec(section ".data") s32 defence_mode2_upper_rib_open[2];
__declspec(section ".data") s32 defence_attr_mode2_upper_rib_open[2];
__declspec(section ".data") BattleUnitDefense defence_mode2_upper_rib_close;
__declspec(section ".data") BattleUnitDefenseAttr defence_attr_mode2_upper_rib_close;
__declspec(section ".data") s32 defence_mode2_middle_head[2];
__declspec(section ".data") s32 defence_attr_mode2_middle_head[2];
__declspec(section ".data") s32 defence_mode2_middle_rib_open[2];
__declspec(section ".data") s32 defence_attr_mode2_middle_rib_open[2];
__declspec(section ".data") s32 defence_mode2_middle_rib_close[2];
__declspec(section ".data") s32 defence_attr_mode2_middle_rib_close[2];
__declspec(section ".data") s32 defence_mode2_lower_head[2];
__declspec(section ".data") s32 defence_attr_mode2_lower_head[2];
__declspec(section ".data") s32 defence_mode2_lower_rib_open[2];
__declspec(section ".data") s32 defence_attr_mode2_lower_rib_open[2];
__declspec(section ".data") s32 defence_mode2_lower_rib_close[2];
__declspec(section ".data") s32 defence_attr_mode2_lower_rib_close[2];
__declspec(section ".data") s32 defence_mode3[2];
__declspec(section ".data") s32 defence_attr_mode3[2];
__declspec(section ".data") BattleUnitDefense defence_honeduka;
__declspec(section ".data") BattleUnitDefenseAttr defence_honeduka_attr;
s32 weapon_cortez_normal_front_attack[48];
s32 weapon_cortez_normal_rear_attack[48];
s32 weapon_cortez_midaregiri_attack[48];
s32 weapon_cortez_mode2_head_attack[48];
s32 weapon_cortez_mode2_charge[48];
s32 weapon_cortez_mode2_bone_attack[48];
s32 weapon_cortez_mode3_kamitsuki_attack[48];
static s32 pose_sound_timing_table[365];
PoseTableEntry pose_table_mode_1[10];
PoseTableEntry pose_table_mode_1_hone[10];
__declspec(section ".data") PoseTableEntry pose_table_mode_2_normal[4];
__declspec(section ".data") PoseTableEntry pose_table_mode_2_upper_normal[4];
__declspec(section ".data") PoseTableEntry pose_table_mode_2_upper_normal_counter[4];
__declspec(section ".data") PoseTableEntry pose_table_mode_2_upper_charge[4];
__declspec(section ".data") PoseTableEntry pose_table_mode_2_upper_charge_counter[4];
__declspec(section ".data") PoseTableEntry pose_table_mode_2_middle_normal[4];
__declspec(section ".data") PoseTableEntry pose_table_mode_2_middle_normal_counter[4];
__declspec(section ".data") PoseTableEntry pose_table_mode_2_middle_charge[4];
__declspec(section ".data") PoseTableEntry pose_table_mode_2_middle_charge_counter[4];
__declspec(section ".data") PoseTableEntry pose_table_mode_2_lower_normal[4];
__declspec(section ".data") PoseTableEntry pose_table_mode_2_lower_normal_counter[4];
__declspec(section ".data") PoseTableEntry pose_table_mode_2_lower_charge[4];
__declspec(section ".data") PoseTableEntry pose_table_mode_2_lower_charge_counter[4];
__declspec(section ".data") PoseTableEntry pose_table_fly_bone[4];
PoseTableEntry pose_table_mode_3[12];
__declspec(section ".data") PoseTableEntry pose_table_honeduka[4];
static BattleDataEntry data_table[7];
static BattleUnitKindPart parts[19];
static s32 init_event[260];
static s32 damage_event[70];
s32 cortez_ac_counter_damage_event[98];
static s32 avoid_thorn_event[89];
static s32 phase_event[196];
s32 attack_event_mode1[44];
s32 attack_event_mode2[47];
s32 at2_head_bat_event[202];
s32 at2_hone_charge_event[146];
s32 at2_hone_rain_attack_event[605];
s32 _bone_rain_event[114];
s32 attack_event_mode3[52];
static s32 attack_audience_event[247];
s32 at3_kamitsuki_attack[264];
s32 at1_normal_attack[205];
s32 at1_midaregiri_attack[251];
static __declspec(section ".data") s32 wait_event[6];
__declspec(section ".data") s32 entry_claw[12];
__declspec(section ".data") s32 entry_rapier[12];
__declspec(section ".data") s32 entry_sword[12];
__declspec(section ".data") s32 entry_saber[12];
s32 cortez_reset_pose_table[450];
static s32 cortez_damage_sub_event[153];
static s32 dead_event[1033];
s32 mode2_rib_open_event[54];
s32 mode2_rib_close_event[54];
s32 mode2_honeduka_damage_event[76];
s32 mode_change_event[111];

__declspec(section ".data") u64 fd_boss_cortez_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_cortez_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_cortez___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_cortez___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_cortez_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_cortez___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_cortez_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_cortez_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_cortez_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_cortez___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_cortez___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_cortez_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_cortez___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_cortez_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_cortez = {
    93,
    "btl_un_cortez",
    20,
    0,
    1,
    1,
    77,
    0,
    0,
    100,
    0,
    50,
    6,
    250,
    170,
    -10,
    90,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    125.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    25.0f,
    0.0f,
    0.0f,
    32.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    -70.0f,
    65.0f,
    0.0f,
    180.0f,
    130.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_KOR_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x200000,
    &regist,
    19,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") StatusVulnerability regist = {40, 40, 50, 100, 50, 100, 100, 25, 0, 0, 100, 0, 100, 90, 50, 0, 0, 100, 50, 0, 0, 0};

__declspec(section ".data") BattleUnitDefense defence_mode1 = {{1, 1, 1, 1, 1}};

__declspec(section ".data") BattleUnitDefenseAttr defence_attr_mode1 = {{0, 0, 0, 0, 0}};

__declspec(section ".data") s32 defence_mode2_upper_head[] = {
    16843009, 16777216,
};

__declspec(section ".data") s32 defence_attr_mode2_upper_head[] = {
    0, 0,
};

__declspec(section ".data") s32 defence_mode2_upper_rib_open[] = {
    0, 0,
};

__declspec(section ".data") s32 defence_attr_mode2_upper_rib_open[] = {
    16843009, 16777216,
};

__declspec(section ".data") BattleUnitDefense defence_mode2_upper_rib_close = {{3, 3, 3, 3, 3}};

__declspec(section ".data") BattleUnitDefenseAttr defence_attr_mode2_upper_rib_close = {{0, 0, 0, 0, 0}};

__declspec(section ".data") s32 defence_mode2_middle_head[] = {
    16843009, 16777216,
};

__declspec(section ".data") s32 defence_attr_mode2_middle_head[] = {
    0, 0,
};

__declspec(section ".data") s32 defence_mode2_middle_rib_open[] = {
    0, 0,
};

__declspec(section ".data") s32 defence_attr_mode2_middle_rib_open[] = {
    16843009, 16777216,
};

__declspec(section ".data") s32 defence_mode2_middle_rib_close[] = {
    50529027, 50331648,
};

__declspec(section ".data") s32 defence_attr_mode2_middle_rib_close[] = {
    0, 0,
};

__declspec(section ".data") s32 defence_mode2_lower_head[] = {
    16843009, 16777216,
};

__declspec(section ".data") s32 defence_attr_mode2_lower_head[] = {
    0, 0,
};

__declspec(section ".data") s32 defence_mode2_lower_rib_open[] = {
    0, 0,
};

__declspec(section ".data") s32 defence_attr_mode2_lower_rib_open[] = {
    16843009, 16777216,
};

__declspec(section ".data") s32 defence_mode2_lower_rib_close[] = {
    50529027, 50331648,
};

__declspec(section ".data") s32 defence_attr_mode2_lower_rib_close[] = {
    0, 0,
};

__declspec(section ".data") s32 defence_mode3[] = {
    16843009, 16777216,
};

__declspec(section ".data") s32 defence_attr_mode3[] = {
    0, 0,
};

__declspec(section ".data") BattleUnitDefense defence_honeduka = {{1, 1, 1, 1, 1}};

__declspec(section ".data") BattleUnitDefenseAttr defence_honeduka_attr = {{0, 0, 0, 0, 0}};

s32 weapon_cortez_normal_front_attack[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_cortez_normal_rear_attack[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, 8,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_cortez_midaregiri_attack[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_cortez_mode2_head_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 4231, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_cortez_mode2_charge[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 8, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 4,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_cortez_mode2_bone_attack[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 135, 2047, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_cortez_mode3_kamitsuki_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 pose_sound_timing_table[] = {
    (s32)"KRT_1S_1", 1008981770, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S_1", 1045220557, 0,
    (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S_1", 1053609165, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S_1",
    1058642330, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S_1", 1061997773, 0, (s32)"SFX_BOSS_KOR_WAIT1",
    1, (s32)"KRT_1S_1", 1065353216, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S2_1", 1008981770,
    0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S2_1", 1045220557, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1,
    (s32)"KRT_1S2_1", 1053609165, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S2_1", 1058642330, 0,
    (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S2_1", 1061997773, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S2_1",
    1065353216, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S_2", 1008981770, 0, (s32)"SFX_BOSS_KOR_WAIT1",
    1, (s32)"KRT_1S_2", 1045220557, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S_2", 1053609165,
    0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S_2", 1058642330, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1,
    (s32)"KRT_1S_2", 1061997773, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S_2", 1065353216, 0,
    (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S2_2", 1008981770, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S2_2",
    1045220557, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S2_2", 1053609165, 0, (s32)"SFX_BOSS_KOR_WAIT1",
    1, (s32)"KRT_1S2_2", 1058642330, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S2_2", 1061997773,
    0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_1S2_2", 1065353216, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1,
    (s32)"KRT_2S_1", 1008981770, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S_1", 1045220557, 0,
    (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S_1", 1053609165, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S_1",
    1058642330, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S_1", 1061997773, 0, (s32)"SFX_BOSS_KOR_WAIT1",
    1, (s32)"KRT_2S_1", 1065353216, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S2_1", 1008981770,
    0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S2_1", 1045220557, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1,
    (s32)"KRT_2S2_1", 1053609165, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S2_1", 1058642330, 0,
    (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S2_1", 1061997773, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S2_1",
    1065353216, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S_2", 1008981770, 0, (s32)"SFX_BOSS_KOR_WAIT1",
    1, (s32)"KRT_2S_2", 1045220557, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S_2", 1053609165,
    0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S_2", 1058642330, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1,
    (s32)"KRT_2S_2", 1061997773, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S_2", 1065353216, 0,
    (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S2_2", 1008981770, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S2_2",
    1045220557, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S2_2", 1053609165, 0, (s32)"SFX_BOSS_KOR_WAIT1",
    1, (s32)"KRT_2S2_2", 1058642330, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S2_2", 1061997773,
    0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_2S2_2", 1065353216, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1,
    (s32)"KRT_3S_1", 1008981770, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S_1", 1045220557, 0,
    (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S_1", 1053609165, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S_1",
    1058642330, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S_1", 1061997773, 0, (s32)"SFX_BOSS_KOR_WAIT1",
    1, (s32)"KRT_3S_1", 1065353216, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S3_1", 1008981770,
    0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S3_1", 1045220557, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1,
    (s32)"KRT_3S3_1", 1053609165, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S3_1", 1058642330, 0,
    (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S3_1", 1061997773, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S3_1",
    1065353216, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S_2", 1008981770, 0, (s32)"SFX_BOSS_KOR_WAIT1",
    1, (s32)"KRT_3S_2", 1045220557, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S_2", 1053609165,
    0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S_2", 1058642330, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1,
    (s32)"KRT_3S_2", 1061997773, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S_2", 1065353216, 0,
    (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S3_2", 1008981770, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S3_2",
    1045220557, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S3_2", 1053609165, 0, (s32)"SFX_BOSS_KOR_WAIT1",
    1, (s32)"KRT_3S3_2", 1058642330, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S3_2", 1061997773,
    0, (s32)"SFX_BOSS_KOR_WAIT1", 1, (s32)"KRT_3S3_2", 1065353216, 0, (s32)"SFX_BOSS_KOR_WAIT1", 1,
    0, 0, 0, 0, 1,
};

PoseTableEntry pose_table_mode_1[] = {
    {1, "KRT_N_1"},
    {5, "KRT_K_1"},
    {2, "KRT_Z_1"},
    {9, "KRT_Z_1"},
    {4, "KRT_X_1"},
    {3, "KRT_K_1"},
    {28, "KRT_S_1"},
    {31, "KRT_S_1"},
    {39, "KRT_D1_1"},
    {69, "KRT_S_1"},
};

PoseTableEntry pose_table_mode_1_hone[] = {
    {1, "KRT_N_1"},
    {5, "KRT_K_1"},
    {2, "KRT_Z_1"},
    {9, "KRT_Z_1"},
    {4, "KRT_X_1"},
    {3, "KRT_K_1"},
    {28, "KRT_S_1"},
    {31, "KRT_S_1"},
    {39, "KRT_D1_2"},
    {69, "KRT_S_1"},
};

__declspec(section ".data") PoseTableEntry pose_table_mode_2_normal[] = {
    {28, "KRT_1S_1"},
    {31, "KRT_1S_1"},
    {39, "KRT_1D_1"},
    {69, "KRT_1S_1"},
};

__declspec(section ".data") PoseTableEntry pose_table_mode_2_upper_normal[] = {
    {28, "KRT_1S_1"},
    {31, "KRT_1S_1"},
    {39, "KRT_1D_1"},
    {69, "KRT_1S_1"},
};

__declspec(section ".data") PoseTableEntry pose_table_mode_2_upper_normal_counter[] = {
    {28, "KRT_1S2_1"},
    {31, "KRT_1S2_1"},
    {39, "KRT_1D2_1"},
    {69, "KRT_1S2_1"},
};

__declspec(section ".data") PoseTableEntry pose_table_mode_2_upper_charge[] = {
    {28, "KRT_1S_2"},
    {31, "KRT_1S_2"},
    {39, "KRT_1D_2"},
    {69, "KRT_1S_2"},
};

__declspec(section ".data") PoseTableEntry pose_table_mode_2_upper_charge_counter[] = {
    {28, "KRT_1S2_2"},
    {31, "KRT_1S2_2"},
    {39, "KRT_1D2_2"},
    {69, "KRT_1S2_2"},
};

__declspec(section ".data") PoseTableEntry pose_table_mode_2_middle_normal[] = {
    {28, "KRT_2S_1"},
    {31, "KRT_2S_1"},
    {39, "KRT_2D_1"},
    {69, "KRT_2S_1"},
};

__declspec(section ".data") PoseTableEntry pose_table_mode_2_middle_normal_counter[] = {
    {28, "KRT_2S2_1"},
    {31, "KRT_2S2_1"},
    {39, "KRT_2D2_1"},
    {69, "KRT_2S2_1"},
};

__declspec(section ".data") PoseTableEntry pose_table_mode_2_middle_charge[] = {
    {28, "KRT_2S_2"},
    {31, "KRT_2S_2"},
    {39, "KRT_2D_2"},
    {69, "KRT_2S_2"},
};

__declspec(section ".data") PoseTableEntry pose_table_mode_2_middle_charge_counter[] = {
    {28, "KRT_2S2_2"},
    {31, "KRT_2S2_2"},
    {39, "KRT_2D2_2"},
    {69, "KRT_2S2_2"},
};

__declspec(section ".data") PoseTableEntry pose_table_mode_2_lower_normal[] = {
    {28, "KRT_3S_1"},
    {31, "KRT_3S_1"},
    {39, "KRT_3D_2"},
    {69, "KRT_3S_1"},
};

__declspec(section ".data") PoseTableEntry pose_table_mode_2_lower_normal_counter[] = {
    {28, "KRT_3S3_1"},
    {31, "KRT_3S3_1"},
    {39, "KRT_3D3_2"},
    {69, "KRT_3S3_1"},
};

__declspec(section ".data") PoseTableEntry pose_table_mode_2_lower_charge[] = {
    {28, "KRT_3S_2"},
    {31, "KRT_3S_2"},
    {39, "KRT_3D_2"},
    {69, "KRT_3S_2"},
};

__declspec(section ".data") PoseTableEntry pose_table_mode_2_lower_charge_counter[] = {
    {28, "KRT_3S3_2"},
    {31, "KRT_3S3_2"},
    {39, "KRT_3D3_2"},
    {69, "KRT_3S3_2"},
};

__declspec(section ".data") PoseTableEntry pose_table_fly_bone[] = {
    {28, "KRT_Z_1"},
    {31, "KRT_Z_1"},
    {39, "KRT_Z_1"},
    {69, "KRT_Z_1"},
};

PoseTableEntry pose_table_mode_3[] = {
    {1, "KRT_N_1"},
    {2, "KRT_Z_1"},
    {9, "KRT_Z_1"},
    {5, "KRT_K_1"},
    {4, "KRT_X_1"},
    {3, "KRT_K_1"},
    {28, "KRT_S_1"},
    {29, "KRT_D_2"},
    {30, "KRT_D_2"},
    {31, "KRT_S_1"},
    {39, "KRT_D_1"},
    {69, "KRT_S_1"},
};

__declspec(section ".data") PoseTableEntry pose_table_honeduka[] = {
    {28, "KRT_Z_1"},
    {31, "KRT_Z_1"},
    {39, "KRT_Z_1"},
    {69, "KRT_Z_1"},
};

static BattleDataEntry data_table[] = {
    {9, cortez_damage_sub_event},
    {49, dead_event},
    {71, mode2_honeduka_damage_event},
    {36, cortez_ac_counter_damage_event},
    {39, avoid_thorn_event},
    {37, avoid_thorn_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_cortez", "c_korutesu1", 0.0f, 0.0f, 0.0f, 145.0f, 90.0f, 30.0f, 145.0f, 90.0f, 30.0f, 20, 30, 255, &defence_honeduka, &defence_honeduka_attr, 0x600009, 0, pose_table_mode_1},
    {2, "btl_un_cortez", NULL, 0.0f, 0.0f, 0.0f, 60.0f, 110.0f, 20.0f, 60.0f, 110.0f, 20.0f, 20, 30, 255, &defence_mode2_upper_rib_close, &defence_attr_mode2_upper_rib_close, 0x3310004, 0, pose_table_mode_1},
    {3, "btl_un_cortez", "c_otitabuki", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x3010000, 0, pose_table_mode_1},
    {4, "btl_un_honeduka", "c_honezuka", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 10.0f, 0.0f, 30.0f, 10.0f, 45, 30, 255, &defence_mode1, &defence_attr_mode1, 0x2000006, 0x1, pose_table_honeduka},
    {5, "btl_un_honeduka", "c_hone2", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x3010000, 0, pose_table_fly_bone},
    {6, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {7, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {8, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {9, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {10, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {11, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {12, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {13, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {14, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {15, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {16, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {17, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {18, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {19, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
};

static EVT_BEGIN(init_event)
    CALL(_make_cortez_work_area, -2)
    CALL(btlevtcmd_OnUnitFlag, -2, 16777216)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_mode1))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 5, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 6, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 7, 1)
    CALL(btlevtcmd_SetUnitWork, -2, 9, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 10, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 11, 0)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(entry_claw), 0)
    CALL(btlevtcmd_SetUnitWork, -2, 3, LW(3))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 39)
    ADD(LW(1), 41)
    SUBTRACT(LW(2), 45)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(0))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(entry_rapier), 0)
    CALL(btlevtcmd_SetUnitWork, -2, 4, LW(3))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 2)
    ADD(LW(1), 6)
    ADD(LW(2), 60)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(0))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(entry_sword), 0)
    CALL(btlevtcmd_SetUnitWork, -2, 1, LW(3))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 154)
    ADD(LW(1), 11)
    SUBTRACT(LW(2), 65)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(0))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(entry_saber), 0)
    CALL(btlevtcmd_SetUnitWork, -2, 2, LW(3))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 116)
    ADD(LW(1), 28)
    ADD(LW(2), 73)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(0))
    CALL(btlevtcmd_SetKissHitOffset, -2, 160, 85, 50)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetUnitWork, -2, 5, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetDamagePartsId, -2, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 4)
            CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_1))
            CALL_CHILD(PTR(btldefaultevt_Damage))
            ELSE
            CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_1_hone))
            CALL_CHILD(PTR(btldefaultevt_Damage))
        END_IF
        RETURN
    END_IF
    CALL(btlevtcmd_GetDamagePartsId, -2, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL_CHILD(PTR(btldefaultevt_Damage))
        CASE_EQUAL(2)
        CALL(btlevtcmd_SetUnitWork, -2, 7, 1)
        CALL(btlevtcmd_SetUnitWork, -2, 11, 2)
        CALL_CHILD(PTR(btldefaultevt_Damage))
        CASE_EQUAL(4)
        CALL_CHILD(PTR(mode2_honeduka_damage_event))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(cortez_ac_counter_damage_event)
    CALL(btlevtcmd_GetUnitWork, -2, 5, LW(0))
    IF_INT_LESS(LW(0), 4)
        CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 39)
        WAIT_MS(500)
        RETURN
    END_IF
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("KRT_A3_1"))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 50)
    ADD(LW(1), 10)
    CALL(btlevtcmd_DivePosition, -2, LW(0), LW(1), LW(2), 30, 0, 2, 0, -1)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("KRT_S_1"))
    CALL(btlevtcmd_CheckDamageCode, -2, 512, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDamageCode, -2, 2048, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            RETURN
        END_IF
    END_IF
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetMoveFrame, -2, LW(0), LW(1), LW(2), FLOAT(6.0f), LW(15))
    CALL(btlevtcmd_DivePosition, -2, LW(0), LW(1), LW(2), LW(15), 15, 11, 0, -1)
    RETURN
EVT_END()

static s32 avoid_thorn_event[] = {
    196699, (s32)btlevtcmd_GetDamagePartsId, -2, -30000000, 131096, -30000000, 4, 393307,
    (s32)btlevtcmd_GetHitPos, -2, 4, -30000000, -29999999, -29999998, 983131, (s32)evt_eff,
    (s32)"", (s32)"toge_flush", 0, -30000000, -29999999, -29999998, 60, 0,
    0, 0, 0, 0, 0, 0, 32, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_RIB_COUNTER1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 5, -30000000, 65570, -30000000, 65572, 1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_1C_3", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1,
    65572, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_2C_3", 196699,
    (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 65572, 3, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KRT_3C_3", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 49, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 11, 0, 65630, (s32)cortez_reset_pose_table, 33, 2,
    1,
};

static s32 phase_event[] = {
    196699, (s32)btlevtcmd_CheckPhase, -30000000, 67108869, 131097, -30000000, 0, 196699,
    (s32)evt_sub_random, 3, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 8, -30000000,
    33, 196699, (s32)btlevtcmd_CheckPhase, -30000000, 67108865, 131096, -30000000, 0,
    65540, 50, 33, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000,
    65570, -30000000, 65579, 2, 65579, 3, 46, 42,
    65540, 50, 49, 262235, (s32)btlevtcmd_GetUnitWork, -2, 7, -30000000,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 7, 0, 131097, -30000000, 0,
    65540, 50, 33, 131163, (s32)btlevtcmd_StopWaitEvent, -2, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 11, -30000000, 131097, -30000000, 0, 65630, (s32)mode2_rib_close_event,
    33, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000, 65647, -29999985,
    131122, -29999985, -1, 65570, -30000000, 65572, 2, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_2B_1", 196699, (s32)btlevtcmd_ftomsec, 80, -30000000,
    65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_MOVE2", -250000000, 0,
    -29999985, 65572, 3, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_3B_1",
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_MOVE2", -250000000, 0, -29999985, 49,
    196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 131097, -29999985, -1, 131163,
    (s32)evt_snd_sfxoff, -29999985, 33, 112, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 5, 1, 65630, (s32)cortez_reset_pose_table, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 65539, 50, 196699, (s32)btlevtcmd_CheckPhase, -30000000, 67108865,
    131096, -30000000, 0, 65540, 99, 33, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 11, -30000000, 131096, -30000000, 0, 65540, 99,
    33, 131126, -30000000, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 11,
    -30000000, 131097, -30000000, 0, 65540, 99, 33, 131163,
    (s32)btlevtcmd_StopWaitEvent, -2, 65630, (s32)mode2_rib_close_event, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    65539, 99, 2, 1,
};

EVT_BEGIN(attack_event_mode1)
    CALL(btlevtcmd_GetUnitWork, -2, 6, LW(0))
    IF_INT_LESS(LW(0), 3)
        SET_VALUE(LW(1), LW(0))
        ADD(LW(1), 1)
        IF_INT_GREATER_OR_EQUAL(LW(1), 3)
            SET_VALUE(LW(1), 0)
        END_IF
        CALL(btlevtcmd_SetUnitWork, -2, 6, LW(1))
    END_IF
    SWITCH(LW(0))
        CASE_OR_EQUAL(0)
        CASE_OR_EQUAL(1)
        CALL_CHILD(PTR(at1_normal_attack))
        CASE_END
        CASE_EQUAL(2)
        CALL_CHILD(PTR(at1_midaregiri_attack))
        CASE_DEFAULT
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(attack_event_mode2)
    CALL(btlevtcmd_GetUnitWork, -2, 10, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(at2_hone_rain_attack_event))
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 5, LW(0))
    SWITCH(LW(0))
        CASE_OR_EQUAL(2)
        CASE_OR_EQUAL(3)
        CALL_CHILD(PTR(at2_hone_charge_event))
        RETURN
        CASE_END
    END_SWITCH
    CALL(btlevtcmd_DrawLots, LW(0), 2, 25, 75)
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL_CHILD(PTR(at2_hone_charge_event))
        CASE_EQUAL(1)
        CALL_CHILD(PTR(at2_head_bat_event))
    END_SWITCH
    RETURN
EVT_END()

s32 at2_head_bat_event[] = {
    131122, -29999988, (s32)weapon_cortez_mode2_head_attack, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997,
    -29999996, 131096, -29999997, -1, 65540, 99, 33, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 196699, (s32)_check_zenei_kouei, -29999997,
    -29999987, 131096, -29999987, 0, 262235, (s32)btlevtcmd_GetUnitWork, -2, 11,
    -30000000, 131096, -30000000, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"KRT_1A_1", 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_1A_3", 33,
    32, 262235, (s32)btlevtcmd_GetUnitWork, -2, 11, -30000000, 131096, -30000000,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_1A_2", 32, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_1A_4", 33, 33, 107, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_HEAD_ATTACK1", -250000000, 0, -29999985, 65546, 667,
    131163, (s32)evt_snd_sfxoff, -29999985, 109, 107, 196699, (s32)btlevtcmd_ftomsec, 50,
    -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_HEAD_ATTACK2", -250000000,
    0, -29999985, 196699, (s32)btlevtcmd_ftomsec, 18, -30000000, 65546, -30000000,
    131163, (s32)evt_snd_sfxoff, -29999985, 109, 65546, 1116, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999988, 256, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 42, 65540, 91,
    49, 65539, 90, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 65540,
    99, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 256, -29999995, 196699,
    (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 65539, 99, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

s32 at2_hone_charge_event[] = {
    262235, (s32)btlevtcmd_SetUnitWork, -2, 10, 1, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    11, -29999999, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000, 65570,
    -30000000, 65572, 1, 196699, (s32)evt_btl_camera_set_mode, 0, 3, 655451,
    (s32)evt_btl_camera_set_moveto, 0, 50, 140, 520, 50, 90, -260,
    60, 4, 131096, -29999999, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KRT_2A_1", 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_2A1_1",
    33, 65572, 2, 196699, (s32)evt_btl_camera_set_mode, 0, 3, 655451,
    (s32)evt_btl_camera_set_moveto, 0, 50, 140, 520, 50, 90, -260,
    60, 4, 131096, -29999999, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KRT_2A_2", 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_2A2_2",
    33, 65572, 3, 196699, (s32)evt_btl_camera_set_mode, 0, 3, 655451,
    (s32)evt_btl_camera_set_moveto, 0, 50, 140, 520, 50, 90, -260,
    60, 4, 131096, -29999999, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KRT_2A_3", 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_2A3_3",
    33, 49, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_INHALE1", -250000000, 0,
    -250000000, 65546, 2000, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 65630, (s32)cortez_reset_pose_table, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -2, 1, (s32)weapon_cortez_mode2_charge, 256, -29999995, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

s32 at2_hone_rain_attack_event[] = {
    262235, (s32)btlevtcmd_SetUnitWork, -2, 10, 0, 131122, -29999988, (s32)weapon_cortez_mode2_bone_attack,
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999988, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1,
    65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 131163, (s32)btlevtcmd_AttackDeclareAll,
    -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000, 65570, -30000000, 65572, 1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_3A_1", 65572, 2, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_3A_2", 65572, 3, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KRT_3A_3", 49, 65546, 1700, 110, 196699,
    (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 112,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_BONE_FLY1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, 5, 16777216, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 5,
    (s32)"KRT_A_1", 107, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 5, 65546, 500,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, 5, 16777216, 109, 131122, -29999995,
    12, 65628, (s32)_bone_rain_event, 131122, -29999995, 13, 65628, (s32)_bone_rain_event,
    131122, -29999995, 14, 65628, (s32)_bone_rain_event, 131122, -29999995, 15,
    65628, (s32)_bone_rain_event, 131122, -29999995, 16, 65628, (s32)_bone_rain_event, 131122,
    -29999995, 17, 65628, (s32)_bone_rain_event, 131122, -29999995, 18, 65628,
    (s32)_bone_rain_event, 131122, -29999995, 19, 65628, (s32)_bone_rain_event, 65644, -29999985,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_SetPartsPos,
    -2, 6, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_OffPartsAttribute, -2,
    6, 16777216, 262235, (s32)btlevtcmd_SetPartsFallAccel, -2, 6, -229999079, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_JumpPartsPosition,
    -2, 6, -30000000, -29999999, -29999998, 30, -1, 109,
    107, 393307, (s32)btlevtcmd_SetPartsRotateOffset, -2, 6, 0, 0, 0,
    65541, 30, 393307, (s32)btlevtcmd_AddPartsRotate, -2, 6, 0, 0,
    30, 65545, 1, 6, 109, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997,
    -29999996, 131097, -29999997, -1, 107, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_SetPartsPos, -2, 9, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 9, 16777216, 262235,
    (s32)btlevtcmd_SetPartsFallAccel, -2, 9, -229999079, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 9, -30000000,
    -29999999, -29999998, 30, -1, 109, 107, 393307, (s32)btlevtcmd_SetPartsRotateOffset,
    -2, 9, 0, 0, 0, 65541, 30, 393307,
    (s32)btlevtcmd_AddPartsRotate, -2, 9, 0, 0, 30, 65545, 1,
    6, 109, 33, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988, 196699,
    (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131122, -29999990, 0, 65539, 10,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988, 256, -29999995,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 65572,
    6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572,
    1, 65540, 91, 42, 65540, 90, 49, 65539,
    90, 131096, -29999990, 0, 107, 196699, (s32)btlevtcmd_JumpPartsContinue, -2,
    6, 393307, (s32)btlevtcmd_GetPartsPos, -2, 6, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 40, 262235, (s32)btlevtcmd_SetPartsFallAccel, -2,
    6, -229999284, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 6, -30000000, -29999999,
    -29999998, 24, -1, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 6, 16777216,
    109, 107, 65541, 24, 393307, (s32)btlevtcmd_AddPartsRotate, -2, 6,
    0, 0, 30, 65545, 1, 6, 109, 32,
    107, 196699, (s32)btlevtcmd_JumpPartsContinue, -2, 9, 393307, (s32)btlevtcmd_GetPartsPos, -2,
    9, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    40, 262235, (s32)btlevtcmd_SetPartsFallAccel, -2, 9, -229999284, 524379, (s32)btlevtcmd_JumpPartsPosition,
    -2, 9, -30000000, -29999999, -29999998, 24, -1, 262235,
    (s32)btlevtcmd_OnPartsAttribute, -2, 9, 16777216, 109, 107, 65541, 24,
    393307, (s32)btlevtcmd_AddPartsRotate, -2, 9, 0, 0, 30, 65545,
    1, 6, 109, 33, 65540, 97, 65539, 91,
    131096, -29999990, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 33,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 256, -29999995,
    131096, -29999990, 0, 107, 393307, (s32)btlevtcmd_GetPartsPos, -2, 6,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 80,
    262235, (s32)btlevtcmd_SetPartsFallAccel, -2, 6, -229999386, 524379, (s32)btlevtcmd_JumpPartsPosition, -2,
    6, -30000000, -29999999, -29999998, 26, -1, 262235, (s32)btlevtcmd_OnPartsAttribute,
    -2, 6, 16777216, 109, 107, 65541, 26, 393307,
    (s32)btlevtcmd_AddPartsRotate, -2, 6, 0, 0, 30, 65545, 1,
    6, 109, 32, 107, 393307, (s32)btlevtcmd_GetPartsPos, -2, 9,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 80,
    262235, (s32)btlevtcmd_SetPartsFallAccel, -2, 9, -229999386, 524379, (s32)btlevtcmd_JumpPartsPosition, -2,
    9, -30000000, -29999999, -29999998, 26, -1, 262235, (s32)btlevtcmd_OnPartsAttribute,
    -2, 9, 16777216, 109, 107, 65541, 26, 393307,
    (s32)btlevtcmd_AddPartsRotate, -2, 9, 0, 0, 30, 65545, 1,
    6, 109, 33, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997,
    -29999996, 131097, -29999997, -1, 65546, 60, 131125, -29999990,
    1, 65540, 10, 33, 65545, 84, 65539, 99,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

EVT_BEGIN(_bone_rain_event)
    CALL(evt_sub_random, 20, LW(10))
    ADD(LW(10), 20)
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(evt_sub_random, 90, LW(7))
        SUBTRACT(LW(7), 45)
        ADD(LW(0), LW(7))
        CALL(evt_sub_random, 60, LW(7))
        SUBTRACT(LW(7), 30)
        ADD(LW(2), LW(7))
        CALL(btlevtcmd_SetPartsPos, -2, LW(5), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_OffPartsAttribute, -2, LW(5), 16777216)
        CALL(btlevtcmd_SetPartsFallAccel, -2, LW(5), FLOAT(1.3994141f))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(evt_sub_random, 120, LW(7))
        SUBTRACT(LW(7), 60)
        ADD(LW(0), LW(7))
        CALL(evt_sub_random, 60, LW(7))
        SUBTRACT(LW(7), 30)
        ADD(LW(2), LW(7))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpPartsPosition, -2, LW(5), LW(0), LW(1), LW(2), LW(10), -1)
        CALL(btlevtcmd_OnPartsAttribute, -2, LW(5), 16777216)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(LW(10))
            CALL(btlevtcmd_AddPartsRotate, -2, LW(5), 0, 0, 30)
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    RETURN
EVT_END()

EVT_BEGIN(attack_event_mode3)
    CALL(btlevtcmd_GetUnitWork, -2, 9, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetMaxHp, -2, LW(1))
        DIVIDE(LW(1), 2)
        CALL(btlevtcmd_GetHp, -2, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), LW(1))
            CALL(_cortez_check_drain_audience, -2, LW(0))
            IF_INT_GREATER_OR_EQUAL(LW(0), 1)
                CALL(btlevtcmd_GetUnitWork, -2, 9, LW(0))
                ADD(LW(0), 1)
                CALL(btlevtcmd_SetUnitWork, -2, 9, LW(0))
                CALL_CHILD(PTR(attack_audience_event))
                RETURN
            END_IF
        END_IF
    END_IF
    CALL_CHILD(PTR(at3_kamitsuki_attack))
    RETURN
EVT_END()

static s32 attack_audience_event[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 3, 655451, (s32)evt_btl_camera_set_moveto, 0, 140,
    120, 500, 140, 85, 9, 60, 11, 65545,
    60, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 196699, (s32)btlevtcmd_SetTalkPose, -2, (s32)"KRT_T_1",
    196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"KRT_S_1", 327771, (s32)evt_msg_print, 2, (s32)"stg5_dou_24_bt01",
    0, -2, 196699, (s32)evt_btl_camera_set_mode, 0, 3, 655451, (s32)evt_btl_camera_set_moveto,
    0, 80, 115, 820, 80, 60, 6, 60,
    11, 262235, (s32)evt_batstage_set_aud_dark, 0, 60, 0, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000,
    -29999999, 120, 60, -10, 4, 0, -1, 327771,
    (s32)evt_msg_print, 2, (s32)"stg5_dou_24_bt02", 0, -2, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KRT_A2_1", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_KOR_INHALE2", -250000000, 0, -250000000, 110, 196699, (s32)evt_snd_sfxon,
    (s32)"SFX_AUDIENCE_PANIC_SCREAM1", -29999985, 65545, 120, 196699, (s32)_cortez_get_sfx_vol, -29999985, -29999986,
    131122, -29999987, 120, 65541, 120, 65545, 1, 131099,
    -29999987, 0, 131126, -29999987, 1, 33, 131122, -30000000,
    -29999986, 131127, -30000000, -29999987, 131128, -30000000, 120, 196699,
    (s32)evt_snd_sfx_vol, -29999985, -30000000, 65651, -29999986, 65651, -30000000, 6,
    131163, (s32)evt_snd_sfxoff, -29999985, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"KRT_A2_2", 131163, (s32)_cortez_collect_energy, -2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"KRT_A2_3", 110, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KRT_S_1", 112, 65546, 125, 196699, (s32)_cortez_drain_energy,
    -2, -29999995, 262235, (s32)btlevtcmd_RecoverHp, -2, 1, -29999995, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -29999999, 100,
    131125, -29999998, 10, 983131, (s32)evt_eff, 0, (s32)"recovery", 0,
    -30000000, -29999999, -29999998, -29999995, 0, 0, 0, 0,
    0, 0, 0, 65546, 1500, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 65644, -29999985, 131163, (s32)_cortez_recovery_audience, -2, 109, 196699,
    (s32)evt_batstage_return_aud_dark_base, 60, 0, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 60,
    -10, 4, 0, -1, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 131163,
    (s32)btlevtcmd_StatusWindowOnOff, 1, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 at3_kamitsuki_attack[] = {
    131122, -29999988, (s32)weapon_cortez_mode3_kamitsuki_attack, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997,
    -29999996, 131096, -29999997, -1, 65540, 99, 33, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KRT_W_1", 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 40, 458843, (s32)btlevtcmd_GetMoveFrame,
    -2, -30000000, -29999999, -29999998, -229993856, -29999985, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, -29999985, -12, 5, 0,
    -1, 110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_ROUND1", -250000000, 0,
    -29999985, 196699, (s32)btlevtcmd_ftomsec, 32, -30000000, 65546, -30000000, 131163,
    (s32)evt_snd_sfxoff, -29999985, 112, 110, 196699, (s32)btlevtcmd_ftomsec, 46, -30000000,
    65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_BITE1", -250000000, 0,
    -250000000, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_A3_3", 196699,
    (s32)btlevtcmd_ftomsec, 50, -30000000, 65546, -30000000, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999988, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 65540, 90, 42, 65540, 91, 49,
    65539, 90, 65540, 97, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988,
    256, -29999995, 131096, -29999995, 21, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KRT_A3_1", 65540, 98, 33, 65539, 97, 196699,
    (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_Z_1",
    65539, 98, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 50, 131125, -29999999, 10,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 30, -10,
    2, 0, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_S_1",
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_GetMoveFrame,
    -2, -30000000, -29999999, -29999998, -229993856, -29999985, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, -29999985, 15, 11, 0,
    -1, 65539, 99, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 at1_normal_attack[] = {
    131096, -30000000, 0, 131122, -29999988, (s32)weapon_cortez_normal_front_attack, 32, 131122,
    -29999988, (s32)weapon_cortez_normal_rear_attack, 33, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997,
    -29999996, 131096, -29999997, -1, 65540, 99, 33, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_KOR_SWORD_READY1", -250000000, 0, -250000000, 196699, (s32)_check_zenei_kouei, -29999997, -29999987,
    131096, -29999987, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_A1_1",
    110, 196699, (s32)btlevtcmd_ftomsec, 95, -30000000, 65546, -30000000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_SWORD_STICK1", -250000000, 0, -250000000, 112, 196699,
    (s32)btlevtcmd_ftomsec, 99, -30000000, 65546, -30000000, 32, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KRT_A1_2", 110, 196699, (s32)btlevtcmd_ftomsec, 95, -30000000,
    65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_SWORD_STICK1", -250000000, 0,
    -250000000, 112, 196699, (s32)btlevtcmd_ftomsec, 100, -30000000, 65546, -30000000,
    33, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988, 256,
    -29999995, 65570, -29999995, 65579, 4, 65540, 90, 46,
    65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90,
    42, 65540, 91, 49, 65539, 90, 65540, 97,
    65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -29999997, -29999996, -29999988, 256, -29999995, 65539, 97,
    65545, 3, 393307, (s32)evt_btl_camera_shake_h, 0, 2, 0, 10,
    13, 65545, 7, 393307, (s32)evt_btl_camera_shake_h, 0, 8, 0,
    30, 13, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 65539, 99,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 at1_midaregiri_attack[] = {
    131122, -29999988, (s32)weapon_cortez_midaregiri_attack, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997,
    -29999996, 131096, -29999997, -1, 65540, 99, 33, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 196699, (s32)_check_zenei_kouei, -29999997,
    -29999987, 131096, -29999987, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"KRT_A2_1", 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_A2_2", 33,
    131122, -30000000, 0, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    -29999988, 256, -29999995, 110, 196699, (s32)btlevtcmd_ftomsec, 33, -30000000,
    65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_SWORD_SHAKE1", -250000000, 0,
    -250000000, 112, 110, 196699, (s32)btlevtcmd_ftomsec, 84, -30000000, 65546,
    -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_SWORD_SHAKE1", -250000000, 0, -250000000,
    112, 110, 196699, (s32)btlevtcmd_ftomsec, 145, -30000000, 65546, -30000000,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_SWORD_SHAKE1", -250000000, 0, -250000000, 112,
    110, 196699, (s32)btlevtcmd_ftomsec, 198, -30000000, 65546, -30000000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_SWORD_SHAKE1", -250000000, 0, -250000000, 112, 65539,
    10, 65570, -29999990, 65572, 0, 196699, (s32)btlevtcmd_ftomsec, 38,
    -30000000, 65546, -30000000, 65572, 1, 196699, (s32)btlevtcmd_ftomsec, 60,
    -30000000, 65546, -30000000, 65572, 2, 196699, (s32)btlevtcmd_ftomsec, 54,
    -30000000, 65546, -30000000, 42, 196699, (s32)btlevtcmd_ftomsec, 56, -30000000,
    65546, -30000000, 49, 65570, -29999995, 65579, 4, 65540,
    90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    65540, 90, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    65540, 90, 42, 65540, 91, 49, 65539, 90,
    65540, 97, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988,
    131101, -29999990, 3, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999988, 256, -29999995, 32, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999988, 0, -29999995, 33, 65539, 97, 131125,
    -29999990, 1, 131100, -29999990, 3, 65540, 10, 33,
    65539, 99, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

__declspec(section ".data") s32 entry_claw[] = {
    (s32)unit_boss_cortez_claw, 16777216, 67108868, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 entry_rapier[] = {
    (s32)unit_boss_cortez_rapier, 16777216, 67108868, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 entry_sword[] = {
    (s32)unit_boss_cortez_sword, 16777216, 67108868, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 entry_saber[] = {
    (s32)unit_boss_cortez_saber, 16777216, 67108868, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

EVT_BEGIN(cortez_reset_pose_table)
    CALL(btlevtcmd_GetUnitWork, -2, 5, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_1))
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetKissHitOffset, -2, 160, 120, 50)
        CALL(btlevtcmd_GetUnitWork, -2, 11, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetUnitWork, -2, 10, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_2_upper_normal))
                ELSE
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_2_upper_charge))
            END_IF
            CALL(btlevtcmd_SetPartsDefenceTable, -2, 2, PTR(&defence_mode2_upper_rib_close))
            CALL(btlevtcmd_SetPartsDefenceAttrTable, -2, 2, PTR(&defence_attr_mode2_upper_rib_close))
            ELSE
            CALL(btlevtcmd_GetUnitWork, -2, 10, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_2_upper_normal_counter))
                ELSE
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_2_upper_charge_counter))
            END_IF
            CALL(btlevtcmd_SetPartsDefenceTable, -2, 2, PTR(defence_mode2_upper_rib_open))
            CALL(btlevtcmd_SetPartsDefenceAttrTable, -2, 2, PTR(defence_attr_mode2_upper_rib_open))
        END_IF
        CALL(btlevtcmd_SetPartsDefenceTable, -2, 1, PTR(defence_mode2_upper_head))
        CALL(btlevtcmd_SetPartsDefenceAttrTable, -2, 1, PTR(defence_attr_mode2_upper_head))
        CALL(btlevtcmd_OnPartsAttribute, -2, 1, 6291456)
        CALL(btlevtcmd_OnPartsAttribute, -2, 2, 7340032)
        CALL(btlevtcmd_SetHitOffset, -2, 1, 20, 15, 0)
        CALL(btlevtcmd_SetHitCursorOffset, -2, 1, 20, 15, 0)
        CALL(btlevtcmd_SetHitOffset, -2, 2, 0, 0, 0)
        CALL(btlevtcmd_SetHitCursorOffset, -2, 2, 0, 0, 0)
        CASE_EQUAL(2)
        CALL(btlevtcmd_SetKissHitOffset, -2, 160, 85, 50)
        CALL(btlevtcmd_GetUnitWork, -2, 11, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetUnitWork, -2, 10, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_2_middle_normal))
                ELSE
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_2_middle_charge))
            END_IF
            CALL(btlevtcmd_SetPartsDefenceTable, -2, 2, PTR(defence_mode2_middle_rib_close))
            CALL(btlevtcmd_SetPartsDefenceAttrTable, -2, 2, PTR(defence_attr_mode2_middle_rib_close))
            ELSE
            CALL(btlevtcmd_GetUnitWork, -2, 10, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_2_middle_normal_counter))
                ELSE
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_2_middle_charge_counter))
            END_IF
            CALL(btlevtcmd_SetPartsDefenceTable, -2, 2, PTR(defence_mode2_middle_rib_open))
            CALL(btlevtcmd_SetPartsDefenceAttrTable, -2, 2, PTR(defence_attr_mode2_middle_rib_open))
        END_IF
        CALL(btlevtcmd_SetPartsDefenceTable, -2, 1, PTR(defence_mode2_middle_head))
        CALL(btlevtcmd_SetPartsDefenceAttrTable, -2, 1, PTR(defence_attr_mode2_middle_head))
        CALL(btlevtcmd_OnPartsAttribute, -2, 1, 6291456)
        CALL(btlevtcmd_OnPartsAttribute, -2, 2, 7340032)
        CALL(btlevtcmd_SetHitOffset, -2, 1, 10, 10, 0)
        CALL(btlevtcmd_SetHitCursorOffset, -2, 1, 10, 10, 0)
        CALL(btlevtcmd_SetHitOffset, -2, 2, -7, -20, 0)
        CALL(btlevtcmd_SetHitCursorOffset, -2, 2, -7, -20, 0)
        CASE_EQUAL(3)
        CALL(btlevtcmd_SetKissHitOffset, -2, 150, 85, 50)
        CALL(btlevtcmd_GetUnitWork, -2, 11, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetUnitWork, -2, 10, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_2_lower_normal))
                ELSE
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_2_lower_charge))
            END_IF
            CALL(btlevtcmd_SetPartsDefenceTable, -2, 2, PTR(defence_mode2_lower_rib_close))
            CALL(btlevtcmd_SetPartsDefenceAttrTable, -2, 2, PTR(defence_attr_mode2_lower_rib_close))
            ELSE
            CALL(btlevtcmd_GetUnitWork, -2, 10, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_2_lower_normal_counter))
                ELSE
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_2_lower_charge_counter))
            END_IF
            CALL(btlevtcmd_SetPartsDefenceTable, -2, 2, PTR(defence_mode2_lower_rib_open))
            CALL(btlevtcmd_SetPartsDefenceAttrTable, -2, 2, PTR(defence_attr_mode2_lower_rib_open))
            CALL(btlevtcmd_OnPartsAttribute, -2, 2, 6291456)
        END_IF
        CALL(btlevtcmd_SetPartsDefenceTable, -2, 1, PTR(defence_mode2_lower_head))
        CALL(btlevtcmd_SetPartsDefenceAttrTable, -2, 1, PTR(defence_attr_mode2_lower_head))
        CALL(btlevtcmd_OnPartsAttribute, -2, 1, 6291456)
        CALL(btlevtcmd_OnPartsAttribute, -2, 2, 6291456)
        CALL(btlevtcmd_OffPartsAttribute, -2, 2, 1048576)
        CALL(btlevtcmd_SetHitOffset, -2, 1, -15, -5, 0)
        CALL(btlevtcmd_SetHitCursorOffset, -2, 1, -15, -5, 0)
        CALL(btlevtcmd_SetHitOffset, -2, 2, -20, -35, 0)
        CALL(btlevtcmd_SetHitCursorOffset, -2, 2, -20, -35, 0)
        CASE_DEFAULT
        CALL(btlevtcmd_SetKissHitOffset, -2, 30, 50, 50)
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_mode_3))
        CALL(btlevtcmd_SetPartsDefenceTable, -2, 1, PTR(defence_mode3))
        CALL(btlevtcmd_SetPartsDefenceAttrTable, -2, 1, PTR(defence_attr_mode3))
        CALL(btlevtcmd_OnPartsAttribute, -2, 1, 6291456)
        CALL(btlevtcmd_OnAttribute, -2, 4)
        CALL(btlevtcmd_SetHitOffset, -2, 1, -135, -64, 0)
        CALL(btlevtcmd_SetHitCursorOffset, -2, 1, -135, -65, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(cortez_damage_sub_event)
    CALL_CHILD(PTR(cortez_reset_pose_table))
    CALL(btlevtcmd_GetDamage, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetDamagePartsId, -2, LW(0))
        CALL(btlevtcmd_GetHitPos, -2, LW(0), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_BTL_ATTACK_MISS2"), LW(0), LW(1), LW(2), 0)
        GOTO(50)
    END_IF
    CALL(btlevtcmd_GetDamagePartsId, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 2)
        CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 39)
        ELSE
        CALL(btlevtcmd_GetUnitWork, -2, 5, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(1)
            CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("KRT_1D_3"))
            CASE_EQUAL(2)
            CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("KRT_2D_3"))
            CASE_EQUAL(3)
            CALL(btlevtcmd_GetUnitWork, -2, 11, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("KRT_3D_3"))
                ELSE
                CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("KRT_3D3_1"))
            END_IF
        END_SWITCH
    END_IF
    WAIT_FRAMES(30)
    GOTO(60)
    LABEL(50)
    LABEL(60)
    CALL(btlevtcmd_GetDamagePartsId, -2, LW(0))
    IF_INT_EQUAL(LW(0), 2)
        CALL(btlevtcmd_CheckDamageCode, -2, 256, LW(1))
        IF_INT_NOT_EQUAL(LW(1), 0)
            CALL(btlevtcmd_CheckDamageCode, -2, 1024, LW(1))
            IF_INT_EQUAL(LW(1), 0)
                CALL(btlevtcmd_GetUnitWork, -2, 5, LW(0))
                SWITCH(LW(0))
                    CASE_OR_EQUAL(1)
                    CASE_OR_EQUAL(2)
                    CASE_OR_EQUAL(3)
                    CALL(btlevtcmd_GetUnitWork, -2, 11, LW(0))
                    IF_INT_EQUAL(LW(0), 0)
                        CALL_CHILD(PTR(mode2_rib_open_event))
                    END_IF
                    CASE_END
                END_SWITCH
            END_IF
        END_IF
    END_IF
END_IF
LABEL(99)
RETURN
EVT_END()

static s32 dead_event[] = {
    131163, (s32)btlevtcmd_ClearAllStatus, -2, 65627, (s32)btlevtcmd_WaitAttackEnd, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    5, -30000000, 65570, -30000000, 65572, 0, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 5, 1, 196699, (s32)btlevtcmd_SetEventAttack, -2, (s32)attack_event_mode2, 262235,
    (s32)btlevtcmd_RecoverHp, -2, 1, 999, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 4,
    65536, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_D2_1", 110, 196699,
    (s32)btlevtcmd_ftomsec, 125, -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_KOR_SWORD_FALL1", -250000000, 0, -250000000, 112, 110, 196699, (s32)btlevtcmd_ftomsec,
    120, -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_SWORD_FALL1",
    -250000000, 0, -250000000, 112, 110, 196699, (s32)btlevtcmd_ftomsec, 118,
    -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_SWORD_FALL1", -250000000,
    0, -250000000, 112, 110, 196699, (s32)btlevtcmd_ftomsec, 117, -30000000,
    65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_SWORD_FALL1", -250000000, 0,
    -250000000, 112, 110, 65546, 2000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    3, (s32)"KRT_Z_1", 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 3, 16777216, 112,
    196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"KRT_D2_2", 110, 196699, (s32)btlevtcmd_ftomsec, 33, -30000000, 65546, -30000000,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_MOVE2", -250000000, 0, -29999993, 196699,
    (s32)btlevtcmd_ftomsec, 36, -30000000, 65546, -30000000, 131163, (s32)evt_snd_sfxoff, -29999993,
    112, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 196699, (s32)btlevtcmd_GetMaxHp, -2,
    -30000000, 196699, (s32)btlevtcmd_SetHp, -2, -30000000, 393307, (s32)evt_fade_entry, 24,
    1000, 0, 0, 0, 196699, (s32)evt_fade_set_anim_ofs_pos, 0, 130,
    262235, (s32)evt_fade_set_anim_virtual_pos, 0, 0, 80, 65627, (s32)evt_fade_end_wait, 262235,
    (s32)btlevtcmd_AnimeChangeGroup, -2, 1, (s32)"c_korutesu2", 65630, (s32)cortez_reset_pose_table, 262235, (s32)btlevtcmd_AnimeSetPoseSoundTable,
    -2, 1, (s32)pose_sound_timing_table, 196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 393307,
    (s32)evt_fade_entry, 25, 1000, 0, 0, 0, 196699, (s32)evt_fade_set_anim_ofs_pos,
    0, 130, 262235, (s32)evt_fade_set_anim_virtual_pos, 0, 0, 80, 65627,
    (s32)evt_fade_end_wait, 327771, (s32)btlevtcmd_SetCutBaseOffset, -2, -80, 120, 0, 196699,
    (s32)btlevtcmd_SetCutWidth, -2, 200, 196699, (s32)btlevtcmd_SetCutHeight, -2, 100, 65627,
    (s32)btlevtcmd_reset_turn, 65579, 1, 65579, 2, 65579, 3, 196699,
    (s32)btlevtcmd_SetEventAttack, -2, (s32)attack_event_mode3, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_BONE_FALL1", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000, 65570,
    -30000000, 65572, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_1B_1",
    65572, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_2B_1", 196699,
    (s32)btlevtcmd_ftomsec, 80, -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_KOR_MOVE2", -250000000, 0, -29999985, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1,
    131163, (s32)evt_snd_sfxoff, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_1B_1",
    65572, 3, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_MOVE2", -250000000, 0,
    -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_3B_1", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete,
    -2, 1, 131163, (s32)evt_snd_sfxoff, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KRT_1B_1", 49, 110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_BONE_FALL1",
    -250000000, 0, -250000000, 196699, (s32)btlevtcmd_ftomsec, 7, -30000000, 65546,
    -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_BONE_FALL1", -250000000, 0, -250000000,
    196699, (s32)btlevtcmd_ftomsec, 8, -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_KOR_BONE_FALL1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_ftomsec, 4,
    -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_BONE_FALL1", -250000000,
    0, -250000000, 196699, (s32)btlevtcmd_ftomsec, 6, -30000000, 65546, -30000000,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_BONE_FALL1", -250000000, 0, -250000000, 196699,
    (s32)btlevtcmd_ftomsec, 7, -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_KOR_BONE_FALL1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_ftomsec, 8, -30000000,
    65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_BONE_FALL1", -250000000, 0,
    -250000000, 196699, (s32)btlevtcmd_ftomsec, 8, -30000000, 65546, -30000000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_BONE_FALL1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_ftomsec,
    5, -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_BONE_FALL1",
    -250000000, 0, -250000000, 196699, (s32)btlevtcmd_ftomsec, 7, -30000000, 65546,
    -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_BONE_FALL1", -250000000, 0, -250000000,
    196699, (s32)btlevtcmd_ftomsec, 5, -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_KOR_BONE_FALL1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_ftomsec, 7,
    -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_BONE_FALL1", -250000000,
    0, -250000000, 196699, (s32)btlevtcmd_ftomsec, 14, -30000000, 65546, -30000000,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_BONE_FALL1", -250000000, 0, -250000000, 196699,
    (s32)btlevtcmd_ftomsec, 30, -30000000, 65546, -30000000, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_KOR_BONE_FALL1", -250000000, 0, -250000000, 112, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2,
    1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, 4, 65546, 1000,
    262235, (s32)btlevtcmd_AnimeSetPoseSoundTable, -2, 1, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    3, (s32)"KRT_A_1", 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 3, 16777216, 196699,
    (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 3, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -29999997,
    196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -29999997, 1, 262235, (s32)btlevtcmd_OffPartsAttribute, -29999997, 1,
    50397184, 196699, (s32)btlevtcmd_OffAttribute, -29999997, 33554432, 196699, (s32)btlevtcmd_SetMaxMoveCount, -29999997,
    1, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -29999997, 196699, (s32)btlevtcmd_AnimeChangePoseFromTable,
    -29999997, 1, 262235, (s32)btlevtcmd_OffPartsAttribute, -29999997, 1, 50397184, 196699,
    (s32)btlevtcmd_OffAttribute, -29999997, 33554432, 196699, (s32)btlevtcmd_SetMaxMoveCount, -29999997, 1, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 4, -29999997, 196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -29999997, 1,
    262235, (s32)btlevtcmd_OffPartsAttribute, -29999997, 1, 50397184, 196699, (s32)btlevtcmd_OffAttribute, -29999997,
    33554432, 196699, (s32)btlevtcmd_SetMaxMoveCount, -29999997, 1, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    3, -29999997, 196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -29999997, 1, 262235, (s32)btlevtcmd_OffPartsAttribute,
    -29999997, 1, 50397184, 196699, (s32)btlevtcmd_OffAttribute, -29999997, 33554432, 196699,
    (s32)btlevtcmd_SetMaxMoveCount, -29999997, 1, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 3, 50331648,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, 4, 50397184, 262235, (s32)btlevtcmd_OnPartsAttribute, -2,
    2, 65536, 131122, -29999989, 1, 65541, 4, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, -29999989, -29999991, 107, 65630, (s32)cortez_weapon_get_home_height, 262235,
    (s32)btlevtcmd_GetUnitWork, -29999991, 2, -29999994, 131096, -29999994, 2, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -29999991, -30000000, 15, 33, 131163, (s32)btlevtcmd_PhaseEventStartDeclare, -29999991,
    655451, (s32)btlevtcmd_DivePosition, -29999991, -30000000, -29999995, -29999998, 60, 0,
    5, 0, -1, 327771, (s32)btlevtcmd_SetHomePos, -29999991, -30000000, -29999995,
    -29999998, 65630, (s32)cortez_weapon_set_formation_attribute, 131163, (s32)btlevtcmd_StartWaitEvent, -29999991, 109, 131125,
    -29999989, 1, 6, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131125, -29999999, 40, 327771, (s32)btlevtcmd_SetHomePos, -2, -30000000,
    -29999999, -29999998, 393307, (s32)evt_fade_entry, 24, 1000, 0, 0,
    0, 196699, (s32)evt_fade_set_anim_ofs_pos, 0, 130, 262235, (s32)evt_fade_set_anim_virtual_pos, 0,
    0, 80, 65627, (s32)evt_fade_end_wait, 262235, (s32)btlevtcmd_AnimeChangeGroup, -2, 1,
    (s32)"c_korutesu3", 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table_mode_3, 196699, (s32)btlevtcmd_AnimeChangePoseFromTable,
    -2, 1, 458843, (s32)btlevtcmd_SetDiveSound, -2, (s32)"SFX_BOSS_KOR_MOVE3", 0, 0,
    0, 0, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999, -29999998, 393307, (s32)evt_fade_entry,
    25, 1000, 0, 0, 0, 196699, (s32)evt_fade_set_anim_ofs_pos, 0,
    130, 262235, (s32)evt_fade_set_anim_virtual_pos, 0, 0, 80, 65627, (s32)evt_fade_end_wait,
    196699, (s32)btlevtcmd_GetMaxHp, -2, -30000000, 196699, (s32)btlevtcmd_SetHp, -2, -30000000,
    65630, (s32)cortez_reset_pose_table, 327771, (s32)btlevtcmd_SetCutBaseOffset, -2, 0, 48, 0,
    196699, (s32)btlevtcmd_SetCutWidth, -2, 90, 196699, (s32)btlevtcmd_SetCutHeight, -2, 96,
    65627, (s32)btlevtcmd_reset_turn, 196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 46, 42,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -29999997, 131097, -29999997, -1,
    262235, (s32)btlevtcmd_SetUnitWork, -29999997, 0, -1, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    1, -1, 262235, (s32)btlevtcmd_GetDataFromDataTable, -29999997, -30000000, 71, 327771,
    (s32)btlevtcmd_RunHitEventDirect, -29999997, 0, -30000000, 0, 33, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 2, -29999997, 131097, -29999997, -1, 262235, (s32)btlevtcmd_SetUnitWork,
    -29999997, 0, -1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2, -1,
    262235, (s32)btlevtcmd_GetDataFromDataTable, -29999997, -30000000, 71, 327771, (s32)btlevtcmd_RunHitEventDirect, -29999997,
    0, -30000000, 0, 33, 262235, (s32)btlevtcmd_GetUnitWork, -2, 3,
    -29999997, 131097, -29999997, -1, 262235, (s32)btlevtcmd_SetUnitWork, -29999997, 0,
    -1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3, -1, 262235, (s32)btlevtcmd_GetDataFromDataTable,
    -29999997, -30000000, 71, 327771, (s32)btlevtcmd_RunHitEventDirect, -29999997, 0, -30000000,
    0, 33, 262235, (s32)btlevtcmd_GetUnitWork, -2, 4, -29999997, 131097,
    -29999997, -1, 262235, (s32)btlevtcmd_SetUnitWork, -29999997, 0, -1, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 4, -1, 262235, (s32)btlevtcmd_GetDataFromDataTable, -29999997, -30000000,
    71, 327771, (s32)btlevtcmd_RunHitEventDirect, -29999997, 0, -30000000, 0, 33,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_D_3", 110, 65546, 1500,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_BONE_FALL1", -250000000, 0, -250000000, 112,
    196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1,
    50331648, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_ENEMY_DIE1_2", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition,
    -30000000, -29999999, -29999998, 131125, -29999998, 10, 983131, (s32)evt_eff,
    0, (s32)"kemuri_test", 4, -30000000, -29999999, -29999998, -229998976, 0,
    0, 0, 0, 0, 0, 0, 196699, (s32)btlevtcmd_GetCoin,
    -2, -30000000, 131163, (s32)btlevtcmd_StoreCoin, -30000000, 196699, (s32)btlevtcmd_GetExp, -2,
    -30000000, 131163, (s32)btlevtcmd_StoreExp, -30000000, 327771, (s32)btlevtcmd_GetPos, -2, -29999997,
    -29999999, -29999998, 131125, -29999998, 10, 131125, -29999999, 30,
    983131, (s32)evt_eff, (s32)"", (s32)"star_point", 0, -29999997, -29999999, -29999998,
    -30000000, 0, 0, 0, 0, 0, 0, 0,
    65546, 1000, 196699, (s32)btlevtcmd_KillUnit, -2, 1, 49, 2,
    1,
};

s32 mode2_rib_open_event[] = {
    262235, (s32)btlevtcmd_SetUnitWork, -2, 11, 2, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    5, -30000000, 65570, -30000000, 65572, 1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KRT_1D2_3", 65572, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KRT_2D2_3", 65572, 3, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"KRT_3D3_3", 49, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_INHALE1", -250000000, 0,
    -250000000, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 262235, (s32)btlevtcmd_OffPartsAttribute, -2,
    2, 65536, 65630, (s32)cortez_reset_pose_table, 2, 1,
};

s32 mode2_rib_close_event[] = {
    262235, (s32)btlevtcmd_SetUnitWork, -2, 11, 0, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    5, -30000000, 65570, -30000000, 65572, 1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KRT_1D2_4", 65572, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KRT_2D2_4", 65572, 3, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"KRT_3D3_4", 49, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_RIB_COUNTER1", -250000000, 0,
    -250000000, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 262235, (s32)btlevtcmd_OnPartsAttribute, -2,
    2, 65536, 65630, (s32)cortez_reset_pose_table, 2, 1,
};

EVT_BEGIN(mode2_honeduka_damage_event)
    CALL(btlevtcmd_OnUnitFlag, -2, 1)
    SET_VALUE(LW(8), 0)
    CALL(btlevtcmd_SetUnitWork, -2, 7, 1)
    CALL(btlevtcmd_CheckDamageCode, -2, 256, LW(1))
    IF_INT_NOT_EQUAL(LW(1), 0)
        BEGIN_SIBLING_EVENT_GET_ID(LW(8))
            CALL_CHILD(PTR(mode_change_event))
        END_SIBLING_EVENT
    END_IF
    BEGIN_SIBLING_EVENT_GET_ID(LW(9))
        CALL(evt_sub_intpl_init, 8, 6, 0, 30)
        LOOP(30)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetPartsDispOffset, -2, 4, 0, LW(0), 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(9))
    IF_INT_NOT_EQUAL(LW(8), 0)
        CALL(btlevtcmd_WaitEventEnd, LW(8))
    END_IF
    CALL(btlevtcmd_CheckDamageCode, LW(10), 1024, LW(1))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL_CHILD(PTR(dead_event))
        RETURN
    END_IF
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 mode_change_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000, 65570, -30000000, 65572,
    1, 262235, (s32)btlevtcmd_GetUnitWork, -2, 11, -30000000, 131096, -30000000,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_1H_1", 32, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_1H2_1", 33, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_KOR_MOVE2", -250000000, 0, -29999985, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1,
    131163, (s32)evt_snd_sfxoff, -29999985, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, 2,
    65630, (s32)cortez_reset_pose_table, 65572, 2, 262235, (s32)btlevtcmd_GetUnitWork, -2, 11,
    -30000000, 131096, -30000000, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"KRT_2H_1", 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_2H2_1", 33,
    65647, -29999985, 196699, (s32)btlevtcmd_ftomsec, 80, -30000000, 65546, -30000000,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_MOVE2", -250000000, 0, -29999985, 196699,
    (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 131163, (s32)evt_snd_sfxoff, -29999985, 112, 131163,
    (s32)btlevtcmd_WaitEventEnd, -29999985, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, 3, 65630,
    (s32)cortez_reset_pose_table, 65630, (s32)mode2_rib_open_event, 42, 49, 2, 1,
};

static USER_FUNC(_check_zenei_kouei) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];
    f32 x, y, z;

    id = BattleTransID(event, id);
    BtlUnit_GetPos(BattleGetUnitPtr(wp, id), &x, &y, &z);
    if (x >= -120.0f) {
        evtSetValue(event, out, 0);
    } else {
        evtSetValue(event, out, 1);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_cortez_recovery_audience) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, *args++);
    CortezWork* work;
    BOOL done;
    s32 i;
    s32 aid;

    id = BattleTransID(event, id);
    work = (CortezWork*)BattleGetUnitPtr(wp, id)->countersetWeapon;
    if (isFirstCall) {
        work->state = 0;
    }
    switch (work->state) {
        case 0:
            for (i = 0; i < 100; i++) {
                if (work->audienceId[i] != -1) {
                    work->seq[i] = 0;
                }
            }
            work->state++;
        case 1:
            done = TRUE;
            for (i = 0; i < 100; i++) {
                if (work->audienceId[i] != -1) {
                    switch (work->seq[i]) {
                        case 0:
                            work->seq[i]++;
                            work->timer[i] = 0;
                        case 1:
                            work->timer[i]++;
                            done = TRUE;
                            break;
                    }
                }
            }
            if (!done) {
                break;
            }
            work->state++;
        case 2:
            for (i = 0; i < 100; i++) {
                aid = work->audienceId[i];
                if (aid != -1) {
                    BattleAudience_Delete(aid);
                    BattleAudienceAddTargetNum(0.0f, -1.0f);
                }
            }
            work->state++;
            return EVT_RETURN_DONE;
        default:
            return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(_cortez_drain_energy) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];
    CortezWork* work;
    s32 i;

    id = BattleTransID(event, id);
    work = (CortezWork*)BattleGetUnitPtr(wp, id)->countersetWeapon;
    for (i = 0; i < 100; i++) {
        if (work->eff[i] != NULL) {
            effDelete(work->eff[i]);
            work->eff[i] = NULL;
        }
    }
    evtSetValue(event, out, work->count);
    return EVT_RETURN_DONE;
}

USER_FUNC(_cortez_collect_energy) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit;
    CortezWork* work;
    BattleAudienceMember* member;
    BOOL done;
    s32 aid;
    s32 i;
    BOOL kumo;
    f32 x, y, z;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    work = (CortezWork*)unit->countersetWeapon;
    if (isFirstCall) {
        work->state = 0;
    }
    switch (work->state) {
        case 0:
            kumo = FALSE;
            for (i = 0; i < 100; i++) {
                aid = work->audienceId[i];
                if (aid != -1) {
                    member = BattleAudienceGetPtr(aid);
                    member->flags |= 0x12;
                    BattleAudience_SetAnim(aid, 9, TRUE);
                    work->wait[i] = irand(60) + 30;
                    work->srcPos[i] = member->position;
                    BtlUnit_GetPos(unit, &work->dstPos[i].x, &work->dstPos[i].y, &work->dstPos[i].z);
                    work->dstPos[i].y += 20.0f;
                    effSpiritEntry(0, work->wait[i] + 60, work->srcPos[i].x, work->srcPos[i].y, work->srcPos[i].z,
                                   work->dstPos[i].x, work->dstPos[i].y, work->dstPos[i].z, 2.0f);
                    if (!kumo) {
                        kumo = TRUE;
                        effKumokumoN64Entry(1, 60, work->dstPos[i].x, work->dstPos[i].y, work->dstPos[i].z, 180.0f,
                                            -1.0f, 1.0f);
                    }
                }
            }
            work->state++;
        case 1:
            done = TRUE;
            for (i = 0; i < 100; i++) {
                aid = work->audienceId[i];
                if (aid != -1) {
                    switch (work->seq[i]) {
                        case 0:
                            if (work->wait[i] > 0) {
                                work->wait[i]--;
                                done = FALSE;
                                break;
                            }
                            work->seq[i]++;
                            work->timer[i] = 0;
                        case 1:
                            work->timer[i]++;
                            BattleAudience_GetRotate(aid, &x, &y, &z);
                            x = intplGetValue(0, work->timer[i], 30, 0.0f, -90.0f);
                            BattleAudience_SetRotate(aid, x, y, z);
                            if (work->timer[i] >= 30) {
                                work->seq[i]++;
                            } else {
                                done = FALSE;
                                break;
                            }
                        case 2:
                            work->timer[i] = 0;
                            work->seq[i]++;
                        case 3:
                            work->timer[i]++;
                            if (work->timer[i] >= 60) {
                                work->seq[i]++;
                            }
                            done = FALSE;
                            break;
                        case 4:
                            break;
                    }
                }
            }
            if (!done) {
                break;
            }
        default:
            return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(_cortez_check_drain_audience) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];
    s32 seat;
    CortezWork* work;
    s32 i;

    id = BattleTransID(event, id);
    work = (CortezWork*)BattleGetUnitPtr(wp, id)->countersetWeapon;
    work->count = 0;
    for (i = 0; i < 100; i++) {
        work->audienceId[i] = -1;
        work->eff[i] = NULL;
        work->seq[i] = 0;
        seat = 10 + (i / 10) * 20 + i % 10;
        if ((u8)BattleAudience_GetExist(seat)) {
            work->audienceId[i] = seat;
            work->count++;
        }
    }
    evtSetValue(event, out, work->count);
    return EVT_RETURN_DONE;
}

USER_FUNC(_cortez_get_sfx_vol) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];

    evtSetValue(event, out, psndSFX_get_vol(id));
    return EVT_RETURN_DONE;
}

USER_FUNC(_make_cortez_work_area) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, *args++);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    unit->countersetWeapon = BattleAlloc(sizeof(CortezWork));
    return EVT_RETURN_DONE;
}
