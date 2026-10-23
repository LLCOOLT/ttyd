#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "manager/evtmgr_cmd.h"
#include "driver/effdrv.h"
#include "dolphin/mtx.h"
#include "system.h"
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "eff/eff_syuryou.h"
#include "driver/animdrv.h"
#include "string.h"
#include "memory.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_cam.h"
#include "evt/evt_eff.h"
#include "party/party_motion.h"

EffectEntry* effPokopiThunderN64Entry(s32 type, s32 time, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, f32 scale);
int rand(void);
Vec nowv;
f32 maer;
s32 irand(s32 scalar);
EffectEntry* effGlassN64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 scale);
static s32 xlw[16];
s32 xlw2[16];
char xmemo[20];
EventEntry* xevt;
void animPoseSetDispCallBack(s32 poseId, void (*callback)(BattleUnitPart*, s32), void* userdata);
void _light_point_callback(BattleUnitPart* part, s32 group);
void animPoseDrawShape(s32 poseId, s32 shapeIdx);
typedef struct BattenSpline { s32 n; s32* table; f32 a[5]; f32 b[15]; s32 count; } BattenSpline;
void spline_maketable(s32 n, s32* table, f32* a, f32* b);
void spline_getvalue(f32 t, Vec* out, s32 n, s32* table, f32* a, f32* b);
u8 battenSatelliteTo_Init(BattleUnit* unit, s32 n, s32* table);
u8 battenSatelliteTo_Main(BattleUnit* unit, s32 n);

static USER_FUNC(_set_draw_callback);
USER_FUNC(btl_hitoffsetx);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeGetPose);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_AnimeWaitPlayComplete);
USER_FUNC(btlevtcmd_CheckActStatus);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_DrawLots);
USER_FUNC(btlevtcmd_GetBodyId);
USER_FUNC(btlevtcmd_GetDamage);
USER_FUNC(btlevtcmd_GetDamagePartsId);
USER_FUNC(btlevtcmd_GetHitPos);
USER_FUNC(btlevtcmd_GetHp);
USER_FUNC(btlevtcmd_GetMaxHp);
USER_FUNC(btlevtcmd_GetTotalDamage);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_OnPartsAttribute);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHpGaugeOffset);
USER_FUNC(btlevtcmd_SetPartsBlur);
USER_FUNC(btlevtcmd_SetStayPose);
USER_FUNC(btlevtcmd_SetStayPoseType);
USER_FUNC(btlevtcmd_SetTalkPose);
USER_FUNC(btlevtcmd_SetTalkPoseType);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(btlevtcmd_StopWaitEvent);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(btlevtcmd_get_turn);
USER_FUNC(datastrcopy);
static USER_FUNC(enzan_lw_load);
USER_FUNC(enzan_lw_load2);
static USER_FUNC(enzan_lw_save);
USER_FUNC(enzan_lw_save2);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveto);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_random);
USER_FUNC(pose_check_evt_run);
USER_FUNC(pose_check_evt_stop);
USER_FUNC(_hp_gauge_flag_on);
USER_FUNC(battenSatelliteToOutside);
USER_FUNC(battenSatelliteToInside);
u8 battenSatelliteTo_Main(BattleUnit* unit, s32 n);
u8 battenSatelliteTo_Init(BattleUnit* unit, s32 n, s32* table);
void _light_point_callback(BattleUnitPart* part, s32 group);
USER_FUNC(battleGetBattenSatelliteInitPos);
USER_FUNC(check_satellite);
static USER_FUNC(eff_staff);
USER_FUNC(evt_eff_firechange00);
USER_FUNC(evt_eff_barriersizechange);
USER_FUNC(evt_eff_colorchange00);
USER_FUNC(evt_eff_pokopi_thunder);
extern s32 bts_x_flag_add[];
extern s32 bts_x_flag_set[];
extern s32 bts_x_flag_wait[];
extern s32 unit_boss_batten_satellite[];

__declspec(section ".data") u64 fd_boss_batten_leader_negone_one_374;
__declspec(section ".data") s32 fd_boss_batten_leader_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_batten_leader___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_batten_leader___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_batten_leader_one_negone_373;
__declspec(section ".data") s32 fd_boss_batten_leader___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_batten_leader_one_381[1];
__declspec(section ".data") u64 fd_boss_batten_leader_negone_one_360;
__declspec(section ".data") s32 fd_boss_batten_leader_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_batten_leader___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_batten_leader___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_batten_leader_one_negone_359;
__declspec(section ".data") s32 fd_boss_batten_leader___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_batten_leader_one_364[1];
s32 batten_leader_zoom[34];
static s32 mario_party_zoom[34];
s32 weapon_batten_leader_thunder[48];
s32 weapon_batten_leader_fire[48];
s32 weapon_batten_leader_ice[48];
s32 weapon_batten_leader_shikaeshi[48];
s32 weapon_batten_leader_yokeyoke[48];
s32 weapon_batten_leader_stop[48];
BattleUnitKind unit_boss_batten_leader;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
__declspec(section ".data") s32 defence_attr_muteki[2];
static __declspec(section ".data") StatusVulnerability regist;
__declspec(section ".data") s32 defencecopy[2];
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_furafura[18];
static __declspec(section ".data") BattleDataEntry data_table[3];
static BattleUnitKindPart parts[7];
__declspec(section ".data") s32 hakai_snd_event[9];
__declspec(section ".data") s32 entry_batten_satellite[12];
__declspec(section ".data") s32 btl_shuryolight_pow_normal[7];
__declspec(section ".data") s32 btl_shuryolight_pow_tenmetu2[3];
__declspec(section ".data") s32 btl_shuryolight_pow_tenmetu[5];
__declspec(section ".data") s32 btl_shuryolight_head_1_normal[9];
__declspec(section ".data") s32 btl_shuryolight_head_2_normal[9];
__declspec(section ".data") s32 btl_shuryolight_head_3_normal[9];
__declspec(section ".data") s32 btl_shuryolight_head_1_quick[9];
__declspec(section ".data") s32 btl_shuryolight_head_2_quick[9];
__declspec(section ".data") s32 btl_shuryolight_head_3_quick[9];
__declspec(section ".data") s32 btl_shuryolight_head_1_random[5];
__declspec(section ".data") s32 btl_shuryolight_head_2_random[5];
__declspec(section ".data") s32 btl_shuryolight_head_3_random[5];
__declspec(section ".data") s32 btl_shuryolight_head_1_tenmetu[3];
__declspec(section ".data") s32 btl_shuryolight_head_2_tenmetu[3];
__declspec(section ".data") s32 btl_shuryolight_head_3_tenmetu[3];
__declspec(section ".data") s32 btl_shuryolight_head_1_off[3];
__declspec(section ".data") s32 btl_shuryolight_head_2_off[3];
__declspec(section ".data") s32 btl_shuryolight_head_3_off[3];
__declspec(section ".data") s32 btl_shuryolight_head_1_on[3];
__declspec(section ".data") s32 btl_shuryolight_head_2_on[3];
__declspec(section ".data") s32 btl_shuryolight_head_3_on[3];
__declspec(section ".data") s32 btl_shuryolight_rod_normal[9];
__declspec(section ".data") s32 btl_shuryolight_rod_off[3];
s32 light_anim_rtn[488];
s32 light_rod_anim_rtn[122];
s32 light_pose_change[314];
s32 maiframeanimcheck[21];
static s32 init_event[149];
static s32 entry_event[94];
static s32 damage_event[47];
s32 damage_sub_event[148];
static s32 phase_event[28];
s32 monster_before_phase_event[195];
static s32 dead_event[165];
static s32 splineTableIn1_1[15];
static s32 splineTableIn2_1[15];
static s32 splineTableIn2_2[15];
static s32 splineTableIn3_1[15];
static s32 splineTableIn3_2[15];
static s32 splineTableIn3_3[15];
static s32 splineTableIn4_1[15];
static s32 splineTableIn4_2[15];
static s32 splineTableIn4_3[15];
static s32 splineTableIn4_4[15];
static s32 splineTableOut1_1[15];
static s32 splineTableOut2_1[15];
static s32 splineTableOut2_2[15];
static s32 splineTableOut3_1[15];
static s32 splineTableOut3_2[15];
static s32 splineTableOut3_3[15];
static s32 splineTableOut4_1[15];
static s32 splineTableOut4_2[15];
static s32 splineTableOut4_3[15];
static s32 splineTableOut4_4[15];
static s32 satellite_blur_on[42];
static s32 satellite_blur_off[29];
s32 sub_call_satellite[87];
s32 player_before_phase_event[170];
static s32 attack_event[141];
s32 batten_leader_thunder_attack_event[377];
s32 batten_leader_fire_attack_event[376];
s32 batten_leader_ice_attack_event[321];
s32 batten_leader_shikaeshi_attack_event[176];
s32 batten_leader_yokeyoke_attack_event[176];
s32 batten_leader_stop_attack_event[328];
static s32 wait_event[16];

__declspec(section ".data") u64 fd_boss_batten_leader_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_batten_leader_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_batten_leader___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_batten_leader___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_batten_leader_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_batten_leader___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_batten_leader_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_batten_leader_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_batten_leader_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_batten_leader___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_batten_leader___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_batten_leader_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_batten_leader___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_batten_leader_one_364[] = {
    1065353216,
};

EVT_BEGIN(batten_leader_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    IF_INT_NOT_EQUAL(LW(0), 2)
        SET_VALUE(LW(1), 30)
        ELSE
        SET_VALUE(LW(1), 1)
    END_IF
    CALL(evt_btl_camera_set_moveto, 0, 83, 84, 349, 83, 60, 0, LW(1), 11)
    IF_INT_EQUAL(LW(0), 1)
        WAIT_MS(600)
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
    CALL(evt_btl_camera_set_moveto, 0, -120, 58, 257, -120, 40, 0, LW(1), 11)
    IF_INT_EQUAL(LW(0), 1)
        WAIT_MS(600)
    END_IF
    RETURN
EVT_END()

s32 weapon_batten_leader_thunder[] = {
    0, 0, 0, 0, VERSION_PICK(1677721600, 1677721602), 1065353216, 16843009, (s32)weaponGetPowerDefault,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 67109634, 0, 71, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_batten_leader_fire[] = {
    0, 0, 0, 0, VERSION_PICK(1677721600, 1677721602), 1065353216, 16843009, (s32)weaponGetPowerDefault,
    6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 16777986, 0, 71, 2047, -2147475456,
    0, 0, 0, VERSION_PICK(20, 75), 50331648, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_batten_leader_ice[] = {
    0, 0, 0, 0, VERSION_PICK(1677721600, 1677721602), 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 33555202, 0, 71, 2047, -2147475456,
    0, 0, 0, 0, 1966592, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_batten_leader_shikaeshi[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 8, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 768, 0, 0, 0, 100, 0, 0,
};

s32 weapon_batten_leader_yokeyoke[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 8, 2047, -2147475452,
    0, 0, 0, 6554368, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_batten_leader_stop[] = {
    0, 0, 0, 0, VERSION_PICK(1677721600, 1677721602), 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 7, 2047, 0,
    7682, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

BattleUnitKind unit_boss_batten_leader = {
    146,
    "btl_un_batten_leader",
    50,
    0,
    1,
    1,
    87,
    0,
    0,
    100,
    0,
    50,
    6,
    68,
    66,
    7,
    70,
    0.0f,
    33.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    34.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    34.0f,
    0.0f,
    0.0f,
    20.0f,
    42.9f,
    10.0f,
    0.0f,
    33.0f,
    0.0f,
    68.0f,
    66.0f,
    1,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_SRYO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    7,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

__declspec(section ".data") s32 defence_attr_muteki[] = {
    33686018, 33554432,
};

static __declspec(section ".data") StatusVulnerability regist = {30, 30, 30, 100, 30, 100, 100, 30, 100, 60, 100, 60, 100, 75, 30, 0, 0, 100, 30, 100, 100, 1};

__declspec(section ".data") s32 defencecopy[] = {
    16843009, 16777216,
};

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
    {50, "A_2"},
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
    {50, "A_2"},
    {42, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_3"},
    {69, "X_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {9, damage_sub_event},
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_batten_leader", "c_shuryo", 0.0f, 0.0f, 0.0f, 0.0f, 56.0f, 0.0f, -6.0f, 55.0f, 0.0f, 53, 69, 255, &defence, &defence_attr, 0x9, 0, pose_table},
    {2, "btl_un_batten_leader", "c_shuryo", 0.0f, 0.0f, 0.0f, 18.0f, 9.0f, 0.0f, 16.0f, 15.0f, 0.0f, 64, 36, 255, &defence, &defence_attr, 0x80800000, 0, NULL},
    {3, /*"電源ランプ"*/"\x93\x64\x8C\xB9\x83\x89\x83\x93\x83\x76", "c_shuryo", 0.0f, 80.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 15, 255, &defence, &defence_attr, 0x2010000, 0, pose_table},
    {4, /*"頭のランプ１"*/"\x93\xAA\x82\xCC\x83\x89\x83\x93\x83\x76\x82\x50", "c_shuryo", 0.0f, 80.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 15, 255, &defence, &defence_attr, 0x2010000, 0, pose_table},
    {5, /*"頭のランプ２"*/"\x93\xAA\x82\xCC\x83\x89\x83\x93\x83\x76\x82\x51", "c_shuryo", 0.0f, 80.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 15, 255, &defence, &defence_attr, 0x2010000, 0, pose_table},
    {6, /*"頭のランプ３"*/"\x93\xAA\x82\xCC\x83\x89\x83\x93\x83\x76\x82\x52", "c_shuryo", 0.0f, 80.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 15, 255, &defence, &defence_attr, 0x2010000, 0, pose_table},
    {7, /*"杖のランプ１"*/"\x8F\xF1\x82\xCC\x83\x89\x83\x93\x83\x76\x82\x50", "c_shuryo", 0.0f, 80.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 15, 255, &defence, &defence_attr, 0x2010000, 0, pose_table},
};

__declspec(section ".data") s32 hakai_snd_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_BARRIER_BREAK1", -250000000, 0, -250000000, 2,
    1,
};

USER_FUNC(evt_eff_pokopi_thunder) {
    f32 top;
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    top = 250.0f + y;

    effPokopiThunderN64Entry(0, 30, x, top, z, x, y, z, 1.0f);
    effPokopiThunderN64Entry(1, 30, x, top, z, x, y, z, 1.0f);
    effPokopiThunderN64Entry(1, 30, x, top, z, x, y, z, 1.0f);
    return EVT_RETURN_DONE;
}
USER_FUNC(evt_eff_colorchange00) {
    EffectEntry* eff = effNameToPtr((const char*)evtGetValue(event, event->args[0]));

    ((s32*)eff->userdata)[6] = 255;
    ((s32*)eff->userdata)[7] = 255;
    ((s32*)eff->userdata)[8] = 255;
    ((s32*)eff->userdata)[10] = 255;
    ((s32*)eff->userdata)[11] = 245;
    ((s32*)eff->userdata)[12] = 0;
    ((f32*)eff->userdata)[2] = 65.0f + ((f32*)eff->userdata)[2];
    ((f32*)eff->userdata)[3] = 10.0f + ((f32*)eff->userdata)[3];

    return EVT_RETURN_DONE;
}
USER_FUNC(evt_eff_barriersizechange) {
    s32* args = event->args;
    EffectEntry* eff = effNameToPtr((const char*)evtGetValue(event, args[0]));

    ((f32*)eff->userdata)[4] = evtGetFloat(event, args[1]);
    return EVT_RETURN_DONE;
}
USER_FUNC(evt_eff_firechange00) {
    Mtx m;
    Vec target;
    Vec pos;
    Vec dir;
    s32* args = event->args;
    EffectEntry* eff = effNameToPtr((const char*)evtGetValue(event, args[0]));
    s32 mode = evtGetValue(event, args[1]);
    BOOL reset;
    f32 a;
    f32 d;

    target.x = evtGetValue(event, args[2]);
    target.y = evtGetValue(event, args[3]);
    target.z = 0.0f;
    pos.x = ((f32*)eff->userdata)[14];
    pos.y = ((f32*)eff->userdata)[15];
    pos.z = 0.0f;
    if (isFirstCall) {
        event->userdata3 = 0;
        if (mode == 0) {
            PSVECSubtract(&target, &pos, &nowv);
            PSVECNormalize(&nowv, &nowv);
            maer = rand() % 60 - 30;
            maer += (maer < 0.0f) ? -30 : 31;
            ((s32*)eff->userdata)[6] = 255;
            ((s32*)eff->userdata)[7] = 255;
            ((s32*)eff->userdata)[8] = 255;
            ((s32*)eff->userdata)[10] = 255;
            ((s32*)eff->userdata)[11] = 65;
            ((s32*)eff->userdata)[12] = 20;
        }
    }
    switch (event->userdata3) {
        case 0:
            break;
        case 1:
            target.x = -2700.0f;
            break;
    }
    PSVECSubtract(&target, &pos, &dir);
    reset = FALSE;
    if (PSVECSquareMag(&dir) > 2500.0f) {
        maer += rand() % 41 - 20;
        if (maer > 80.0f || maer < -80.0f || (maer < 20.0f && maer > -20.0f)) {
            maer = rand() % 60 - 30;
            maer += (maer < 0.0f) ? -30 : 31;
            reset = TRUE;
        }
        PSMTXRotRad(m, 'Z', 0.017453292f * maer);
        PSMTXMultVec(m, &dir, &dir);
    } else {
        reset = TRUE;
    }
    PSVECNormalize(&dir, &dir);
    a = angleABf(0.0f, 0.0f, nowv.x, nowv.y);
    d = angleABf(0.0f, 0.0f, dir.x, dir.y);
    d = compAngle(a, d);
    if (!reset) {
        if ((d >= 0.0f ? d : -d) > 15.0f) {
            d = (d > 0.0f) ? 15.0f : -15.0f;
        }
    }
    PSMTXRotRad(m, 'Z', 0.017453292f * d);
    PSMTXMultVec(m, &nowv, &nowv);
    PSVECScale(&nowv, &dir, 15.0f);
    PSVECAdd(&pos, &dir, &pos);
    if (pos.y < 10.0f) {
        if (((f32*)eff->userdata)[15] >= 10.0f) {
            nowv.y = -nowv.y;
        } else if (nowv.y < 0.0f) {
            nowv.y = -nowv.y;
        }
    }
    ((f32*)eff->userdata)[14] = pos.x;
    ((f32*)eff->userdata)[15] = pos.y;
    switch (event->userdata3) {
        case 0:
            if (PSVECSquareDistance(&pos, &target) < 225.0f) {
                if (mode) {
                    event->userdata3 = 1;
                } else {
                    return 1;
                }
            }
            break;
        case 1:
            if (pos.x <= -270.0f) {
                effSoftDelete(eff);
                return 1;
            }
            break;
    }
    return 0;
}
static USER_FUNC(eff_staff) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;
    f32* wk;

    wk = effSyuryouEntry(0, 90, 0.0f, -1000.0f, 0.0f)->userdata;
    BtlUnit_GetPos(unit, &x, &y, &z);
    wk[1] = x + 6.0f * (unit->mSizeMultiplier * unit->faceDirection);
    wk[2] = y + 68.0f * unit->mSizeMultiplier;
    wk[3] = 5.0f + z;
    wk[4] = unit->mSizeMultiplier;
    return EVT_RETURN_DONE;
}
USER_FUNC(check_satellite) {
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part;
    BattleUnitPart* part2;
    EventEntry* evt;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 count;
    BOOL all;

    count = 0;
    all = FALSE;
    if (unit == NULL) {
        return EVT_RETURN_DONE;
    }
    for (i = 9; i < 13; i++) {
        if (unit->work[i] != -1) {
            if (BattleGetUnitPtr(_battleWorkPointer, unit->work[i]) != NULL) {
                count++;
            } else {
                unit->work[i] = -1;
            }
        }
    }
    if (count >= 4) {
        all = TRUE;
    }
    if (!all) {
        part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
        part2 = BtlUnit_GetPartsPtr(unit, 2);
        if (part->attributes & 0x40000000) {
            evt = evtEntryType(hakai_snd_event, event->priority, 0, event->type);
            evt->unitId = event->unitId;
            evt->ownerNPC = event->ownerNPC;
            for (i = 0; i < 16; i++) {
                evt->lwData[i] = event->lwData[i];
            }
            for (i = 0; i < 3; i++) {
                evt->lfData[i] = event->lfData[i];
            }
            evt->uwBase = event->uwBase;
            evt->ufBase = event->ufBase;
            effDelete((EffectEntry*)unit->work[8]);
            unit->work[8] = 0;
            BtlUnit_GetPos(unit, &x, &y, &z);
            for (i = 0; i < 20; i++) {
                s32 w = BtlUnit_GetWidth(unit) + 15;
                s32 h = BtlUnit_GetHeight(unit) + 15;
                s32 dx = irand(w) - w / 2;
                s32 dy = irand(h) - h / 2;

                effGlassN64Entry(2, 60, x + dx, y + dy, z, 1.0f);
            }
        }
        part->attributes &= ~0x40000000;
        part2->attributes &= ~0x20000000;
        part->defenseAttr = &defence_attr;
        for (i = 0; i < 5; i++) {
            part->defense->defenses[i] = ((u8*)defencecopy)[i];
        }
        part->defense->defenses[0] += count;
    } else {
        part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
        part2 = BtlUnit_GetPartsPtr(unit, 2);
        if (!(part->attributes & 0x40000000)) {
            f32 px;
            f32 py;
            f32 pz;

            BtlUnit_snd_se(unit, "SFX_BOSS_SRYO_LIGHT_ROUND1", 0xF1194D80, 0);
            BtlUnit_GetPos(unit, &px, &py, &pz);
            unit->work[8] = (s32)effSyuryouEntry(1, 1000, 0.0f, -1000.0f, 0.0f);
        }
        if (unit->work[8] != 0) {
            f32* ud = ((EffectEntry*)unit->work[8])->userdata;
            f32 ex;
            f32 ey;
            f32 ez;

            BtlUnit_GetPos(unit, &ex, &ey, &ez);
            ud[1] = ex;
            ud[2] = ey - 12.5f * unit->mSizeMultiplier;
            ud[3] = 10.0f + ez;

            ud[4] = 2.5f * unit->mSizeMultiplier;
        }
        part->attributes |= 0x40000000;
        part2->attributes |= 0x20000000;
        part->defenseAttr = (BattleUnitDefenseAttr*)defence_attr_muteki;
        for (i = 0; i < 5; i++) {
            part->defense->defenses[i] = ((u8*)defencecopy)[i];
        }
        part->defense->defenses[0] += count;
    }
    return EVT_RETURN_DONE;
}
USER_FUNC(battleGetBattenSatelliteInitPos) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 num;
    s32 index;
    s32 id;
    s32 x;
    s32 y;
    s32 z;
    s32 i;
    s32 j;
    static const Vec VecData[] = {
        // 1 satellite
        {38.0f, 45.0f, 5.0f},
        // 2 satellites
        {38.0f, 45.0f, 5.0f},
        {-38.0f, 45.0f, 5.0f},
        // 3 satellites
        {0.0f, 83.0f, 5.0f},
        {38.0f, 7.0f, 5.0f},
        {-38.0f, 7.0f, 5.0f},
        // 4 satellites
        {38.0f, 83.0f, 5.0f},
        {-38.0f, 83.0f, 5.0f},
        {38.0f, 7.0f, 5.0f},
        {-38.0f, 7.0f, 5.0f},
    };
    const Vec* p;
    BattleWork* wp = _battleWorkPointer;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    num = evtGetValue(event, args[1]);
    index = evtGetValue(event, args[2]);
    x = args[3];
    y = args[4];
    z = args[5];
    p = VecData;
    for (i = 0; i < num; i++) {
        for (j = 0; j < i; j++) {
            p++;
        }
    }
    for (j = 0; j < index; j++) {
        p++;
    }
    evtSetValue(event, x, (s32)(p->x * unit->faceDirection));
    evtSetValue(event, y, (s32)p->y);
    evtSetValue(event, z, (s32)p->z);
    return EVT_RETURN_DONE;
}

__declspec(section ".data") s32 entry_batten_satellite[] = {
    (s32)unit_boss_batten_satellite, 16777216, 67108868, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btl_shuryolight_pow_normal[] = {
    (s32)"L_1B", -2, (s32)"L_1A", 80, (s32)"L_1B", 80, 0,
};

__declspec(section ".data") s32 btl_shuryolight_pow_tenmetu2[] = {
    (s32)"L_4E", 0, 0,
};

__declspec(section ".data") s32 btl_shuryolight_pow_tenmetu[] = {
    (s32)"L_1B", -3, (s32)"L_1A", 200, 0,
};

__declspec(section ".data") s32 btl_shuryolight_head_1_normal[] = {
    (s32)"L_4A", 400, (s32)"L_4A", 400, (s32)"L_4B", 400, (s32)"L_4A", 400,
    0,
};

__declspec(section ".data") s32 btl_shuryolight_head_2_normal[] = {
    (s32)"L_3A", 400, (s32)"L_3B", 400, (s32)"L_3A", 400, (s32)"L_3A", 400,
    0,
};

__declspec(section ".data") s32 btl_shuryolight_head_3_normal[] = {
    (s32)"L_2B", 400, (s32)"L_2A", 400, (s32)"L_2A", 400, (s32)"L_2A", 400,
    0,
};

__declspec(section ".data") s32 btl_shuryolight_head_1_quick[] = {
    (s32)"L_4A", 200, (s32)"L_4A", 200, (s32)"L_4B", 200, (s32)"L_4A", 200,
    0,
};

__declspec(section ".data") s32 btl_shuryolight_head_2_quick[] = {
    (s32)"L_3A", 200, (s32)"L_3B", 200, (s32)"L_3A", 200, (s32)"L_3A", 200,
    0,
};

__declspec(section ".data") s32 btl_shuryolight_head_3_quick[] = {
    (s32)"L_2B", 200, (s32)"L_2A", 200, (s32)"L_2A", 200, (s32)"L_2A", 200,
    0,
};

__declspec(section ".data") s32 btl_shuryolight_head_1_random[] = {
    (s32)"L_4A", -4, (s32)"L_4B", -4, 0,
};

__declspec(section ".data") s32 btl_shuryolight_head_2_random[] = {
    (s32)"L_3A", -4, (s32)"L_3B", -4, 0,
};

__declspec(section ".data") s32 btl_shuryolight_head_3_random[] = {
    (s32)"L_2B", -4, (s32)"L_2A", -4, 0,
};

__declspec(section ".data") s32 btl_shuryolight_head_1_tenmetu[] = {
    (s32)"L_4E", 0, 0,
};

__declspec(section ".data") s32 btl_shuryolight_head_2_tenmetu[] = {
    (s32)"L_3E", 0, 0,
};

__declspec(section ".data") s32 btl_shuryolight_head_3_tenmetu[] = {
    (s32)"L_2E", 0, 0,
};

__declspec(section ".data") s32 btl_shuryolight_head_1_off[] = {
    (s32)"L_4A", -1, 0,
};

__declspec(section ".data") s32 btl_shuryolight_head_2_off[] = {
    (s32)"L_3A", -1, 0,
};

__declspec(section ".data") s32 btl_shuryolight_head_3_off[] = {
    (s32)"L_2A", -1, 0,
};

__declspec(section ".data") s32 btl_shuryolight_head_1_on[] = {
    (s32)"L_4B", -1, 0,
};

__declspec(section ".data") s32 btl_shuryolight_head_2_on[] = {
    (s32)"L_3B", -1, 0,
};

__declspec(section ".data") s32 btl_shuryolight_head_3_on[] = {
    (s32)"L_2B", -1, 0,
};

__declspec(section ".data") s32 btl_shuryolight_rod_normal[] = {
    (s32)"L_3C", 0, (s32)"L_3B", 1000, (s32)"L_3D", 0, (s32)"L_3A", 1000,
    0,
};

__declspec(section ".data") s32 btl_shuryolight_rod_off[] = {
    (s32)"L_3A", -1, 0,
};

EVT_BEGIN(light_anim_rtn)
    BEGIN_SIBLING_EVENT
        SET_INT_READ_ADDR(LW(6))
        LOOP(0)
            READ_INT(LW(1))
            IF_INT_EQUAL(LW(1), 0)
                SET_INT_READ_ADDR(LW(6))
                READ_INT(LW(1))
            END_IF
            CALL(btlevtcmd_AnimeChangePose, -2, 4, LW(1))
            READ_INT(LW(1))
            IF_INT_GREATER(LW(1), 0)
                WAIT_MS(LW(1))
                ELSE
                SWITCH(LW(1))
                    CASE_EQUAL(0)
                    WAIT_FRAMES(1)
                    CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 4)
                    CASE_EQUAL(-1)
                    BREAK_LOOP
                    CASE_EQUAL(-2)
                    LOOP(0)
                        CALL(evt_sub_random, 3000, LW(0))
                        ADD(LW(0), 3000)
                        WAIT_MS(LW(0))
                        CALL(evt_sub_random, 100, LW(0))
                        DIVIDE(LW(0), 30)
                        IF_INT_GREATER(LW(0), 0)
                            BREAK_LOOP
                        END_IF
                    END_LOOP
                    READ_INT4(LW(1), LW(2), LW(3), LW(4))
                    LOOP(LW(0))
                        CALL(btlevtcmd_AnimeChangePose, -2, 4, LW(1))
                        WAIT_MS(LW(2))
                        CALL(btlevtcmd_AnimeChangePose, -2, 4, LW(3))
                        WAIT_MS(LW(4))
                    END_LOOP
                    CASE_EQUAL(-3)
                    CALL(evt_sub_random, 3000, LW(0))
                    CALL(evt_sub_random, 1000, LW(2))
                    ADD(LW(0), LW(2))
                    ADD(LW(0), 700)
                    WAIT_MS(LW(0))
                    CASE_EQUAL(-4)
                    CALL(evt_sub_random, 300, LW(0))
                    ADD(LW(0), 100)
                    WAIT_MS(LW(0))
                END_SWITCH
            END_IF
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        SET_INT_READ_ADDR(LW(7))
        LOOP(0)
            READ_INT(LW(1))
            IF_INT_EQUAL(LW(1), 0)
                SET_INT_READ_ADDR(LW(7))
                READ_INT(LW(1))
            END_IF
            CALL(btlevtcmd_AnimeChangePose, -2, 5, LW(1))
            READ_INT(LW(1))
            IF_INT_GREATER(LW(1), 0)
                WAIT_MS(LW(1))
                ELSE
                SWITCH(LW(1))
                    CASE_EQUAL(0)
                    WAIT_FRAMES(1)
                    CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 5)
                    CASE_EQUAL(-1)
                    BREAK_LOOP
                    CASE_EQUAL(-2)
                    LOOP(0)
                        CALL(evt_sub_random, 3000, LW(0))
                        ADD(LW(0), 3000)
                        WAIT_MS(LW(0))
                        CALL(evt_sub_random, 100, LW(0))
                        DIVIDE(LW(0), 30)
                        IF_INT_GREATER(LW(0), 0)
                            BREAK_LOOP
                        END_IF
                    END_LOOP
                    READ_INT4(LW(1), LW(2), LW(3), LW(4))
                    LOOP(LW(0))
                        CALL(btlevtcmd_AnimeChangePose, -2, 5, LW(1))
                        WAIT_MS(LW(2))
                        CALL(btlevtcmd_AnimeChangePose, -2, 5, LW(3))
                        WAIT_MS(LW(4))
                    END_LOOP
                    CASE_EQUAL(-3)
                    CALL(evt_sub_random, 3000, LW(0))
                    CALL(evt_sub_random, 1000, LW(2))
                    ADD(LW(0), LW(2))
                    ADD(LW(0), 700)
                    WAIT_MS(LW(0))
                    CASE_EQUAL(-4)
                    CALL(evt_sub_random, 300, LW(0))
                    ADD(LW(0), 100)
                    WAIT_MS(LW(0))
                END_SWITCH
            END_IF
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        SET_INT_READ_ADDR(LW(8))
        LOOP(0)
            READ_INT(LW(1))
            IF_INT_EQUAL(LW(1), 0)
                SET_INT_READ_ADDR(LW(8))
                READ_INT(LW(1))
            END_IF
            CALL(btlevtcmd_AnimeChangePose, -2, 6, LW(1))
            READ_INT(LW(1))
            IF_INT_GREATER(LW(1), 0)
                WAIT_MS(LW(1))
                ELSE
                SWITCH(LW(1))
                    CASE_EQUAL(0)
                    WAIT_FRAMES(1)
                    CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 6)
                    CASE_EQUAL(-1)
                    BREAK_LOOP
                    CASE_EQUAL(-2)
                    LOOP(0)
                        CALL(evt_sub_random, 3000, LW(0))
                        ADD(LW(0), 3000)
                        WAIT_MS(LW(0))
                        CALL(evt_sub_random, 100, LW(0))
                        DIVIDE(LW(0), 30)
                        IF_INT_GREATER(LW(0), 0)
                            BREAK_LOOP
                        END_IF
                    END_LOOP
                    READ_INT4(LW(1), LW(2), LW(3), LW(4))
                    LOOP(LW(0))
                        CALL(btlevtcmd_AnimeChangePose, -2, 6, LW(1))
                        WAIT_MS(LW(2))
                        CALL(btlevtcmd_AnimeChangePose, -2, 6, LW(3))
                        WAIT_MS(LW(4))
                    END_LOOP
                    CASE_EQUAL(-3)
                    CALL(evt_sub_random, 3000, LW(0))
                    CALL(evt_sub_random, 1000, LW(2))
                    ADD(LW(0), LW(2))
                    ADD(LW(0), 700)
                    WAIT_MS(LW(0))
                    CASE_EQUAL(-4)
                    CALL(evt_sub_random, 300, LW(0))
                    ADD(LW(0), 100)
                    WAIT_MS(LW(0))
                END_SWITCH
            END_IF
        END_LOOP
    END_SIBLING_EVENT
    SET_INT_READ_ADDR(LW(5))
    LOOP(0)
        READ_INT(LW(1))
        IF_INT_EQUAL(LW(1), 0)
            SET_INT_READ_ADDR(LW(5))
            READ_INT(LW(1))
        END_IF
        CALL(btlevtcmd_AnimeChangePose, -2, 3, LW(1))
        READ_INT(LW(1))
        IF_INT_GREATER(LW(1), 0)
            WAIT_MS(LW(1))
            ELSE
            SWITCH(LW(1))
                CASE_EQUAL(0)
                WAIT_FRAMES(1)
                CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 3)
                CASE_EQUAL(-1)
                BREAK_LOOP
                CASE_EQUAL(-2)
                LOOP(0)
                    CALL(evt_sub_random, 3000, LW(0))
                    ADD(LW(0), 3000)
                    WAIT_MS(LW(0))
                    CALL(evt_sub_random, 100, LW(0))
                    DIVIDE(LW(0), 30)
                    IF_INT_GREATER(LW(0), 0)
                        BREAK_LOOP
                    END_IF
                END_LOOP
                READ_INT4(LW(1), LW(2), LW(3), LW(4))
                LOOP(LW(0))
                    CALL(btlevtcmd_AnimeChangePose, -2, 3, LW(1))
                    WAIT_MS(LW(2))
                    CALL(btlevtcmd_AnimeChangePose, -2, 3, LW(3))
                    WAIT_MS(LW(4))
                END_LOOP
                CASE_EQUAL(-3)
                CALL(evt_sub_random, 3000, LW(0))
                CALL(evt_sub_random, 1000, LW(2))
                ADD(LW(0), LW(2))
                ADD(LW(0), 700)
                WAIT_MS(LW(0))
                CASE_EQUAL(-4)
                CALL(evt_sub_random, 300, LW(0))
                ADD(LW(0), 100)
                WAIT_MS(LW(0))
            END_SWITCH
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(light_rod_anim_rtn)
    SET_INT_READ_ADDR(LW(9))
    LOOP(0)
        READ_INT(LW(1))
        IF_INT_EQUAL(LW(1), 0)
            SET_INT_READ_ADDR(LW(9))
            READ_INT(LW(1))
        END_IF
        CALL(btlevtcmd_AnimeChangePose, -2, 7, LW(1))
        READ_INT(LW(1))
        IF_INT_GREATER(LW(1), 0)
            WAIT_MS(LW(1))
            ELSE
            SWITCH(LW(1))
                CASE_EQUAL(0)
                WAIT_FRAMES(1)
                CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 7)
                CASE_EQUAL(-1)
                BREAK_LOOP
                CASE_EQUAL(-2)
                LOOP(0)
                    CALL(evt_sub_random, 3000, LW(0))
                    ADD(LW(0), 3000)
                    WAIT_MS(LW(0))
                    CALL(evt_sub_random, 100, LW(0))
                    DIVIDE(LW(0), 30)
                    IF_INT_GREATER(LW(0), 0)
                        BREAK_LOOP
                    END_IF
                END_LOOP
                READ_INT4(LW(1), LW(2), LW(3), LW(4))
                LOOP(LW(0))
                    CALL(btlevtcmd_AnimeChangePose, -2, 7, LW(1))
                    WAIT_MS(LW(2))
                    CALL(btlevtcmd_AnimeChangePose, -2, 7, LW(3))
                    WAIT_MS(LW(4))
                END_LOOP
                CASE_EQUAL(-3)
                CALL(evt_sub_random, 3000, LW(0))
                CALL(evt_sub_random, 1000, LW(2))
                ADD(LW(0), LW(2))
                ADD(LW(0), 700)
                WAIT_MS(LW(0))
                CASE_EQUAL(-4)
                CALL(evt_sub_random, 300, LW(0))
                ADD(LW(0), 100)
                WAIT_MS(LW(0))
            END_SWITCH
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(light_pose_change)
    CALL(enzan_lw_save2)
    CALL(btlevtcmd_AnimeGetPose, -2, 1, LW(0))
    IF_STR_EQUAL(LW(0), STRING("A_1B"))
        CALL(enzan_lw_save)
        SET_VALUE(LW(5), PTR(btl_shuryolight_pow_normal))
        SET_VALUE(LW(6), PTR(btl_shuryolight_head_1_tenmetu))
        SET_VALUE(LW(7), PTR(btl_shuryolight_head_2_tenmetu))
        SET_VALUE(LW(8), PTR(btl_shuryolight_head_3_tenmetu))
        SET_VALUE(LW(0), 2)
        GOTO(0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("A_1C"))
        CALL(enzan_lw_save)
        SET_VALUE(LW(5), PTR(btl_shuryolight_pow_normal))
        SET_VALUE(LW(6), PTR(btl_shuryolight_head_1_tenmetu))
        SET_VALUE(LW(7), PTR(btl_shuryolight_head_2_tenmetu))
        SET_VALUE(LW(8), PTR(btl_shuryolight_head_3_tenmetu))
        SET_VALUE(LW(0), 2)
        GOTO(0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("A_2"))
        CALL(enzan_lw_save)
        SET_VALUE(LW(5), PTR(btl_shuryolight_pow_normal))
        SET_VALUE(LW(6), PTR(btl_shuryolight_head_1_tenmetu))
        SET_VALUE(LW(7), PTR(btl_shuryolight_head_2_tenmetu))
        SET_VALUE(LW(8), PTR(btl_shuryolight_head_3_tenmetu))
        SET_VALUE(LW(0), 2)
        GOTO(0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("H_1"))
        CALL(enzan_lw_save)
        SET_VALUE(LW(5), PTR(btl_shuryolight_pow_normal))
        SET_VALUE(LW(6), PTR(btl_shuryolight_head_1_quick))
        SET_VALUE(LW(7), PTR(btl_shuryolight_head_2_quick))
        SET_VALUE(LW(8), PTR(btl_shuryolight_head_3_quick))
        SET_VALUE(LW(0), 1)
        GOTO(0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("D_1"))
        CALL(enzan_lw_save)
        SET_VALUE(LW(5), PTR(btl_shuryolight_pow_tenmetu2))
        SET_VALUE(LW(6), PTR(btl_shuryolight_head_1_tenmetu))
        SET_VALUE(LW(7), PTR(btl_shuryolight_head_2_tenmetu))
        SET_VALUE(LW(8), PTR(btl_shuryolight_head_3_tenmetu))
        SET_VALUE(LW(0), 3)
        GOTO(0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("N_1"))
        CALL(enzan_lw_save)
        SET_VALUE(LW(5), PTR(btl_shuryolight_pow_normal))
        SET_VALUE(LW(6), PTR(btl_shuryolight_head_1_off))
        SET_VALUE(LW(7), PTR(btl_shuryolight_head_2_off))
        SET_VALUE(LW(8), PTR(btl_shuryolight_head_3_off))
        SET_VALUE(LW(0), 6)
        GOTO(0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("K_1"))
        CALL(enzan_lw_save)
        SET_VALUE(LW(5), PTR(btl_shuryolight_pow_normal))
        SET_VALUE(LW(6), PTR(btl_shuryolight_head_1_random))
        SET_VALUE(LW(7), PTR(btl_shuryolight_head_2_random))
        SET_VALUE(LW(8), PTR(btl_shuryolight_head_3_random))
        SET_VALUE(LW(0), 4)
        GOTO(0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("Q_1"))
        CALL(enzan_lw_save)
        SET_VALUE(LW(5), PTR(btl_shuryolight_pow_tenmetu2))
        SET_VALUE(LW(6), PTR(btl_shuryolight_head_1_tenmetu))
        SET_VALUE(LW(7), PTR(btl_shuryolight_head_2_tenmetu))
        SET_VALUE(LW(8), PTR(btl_shuryolight_head_3_tenmetu))
        SET_VALUE(LW(0), 3)
        GOTO(0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("X_1"))
        CALL(enzan_lw_save)
        SET_VALUE(LW(5), PTR(btl_shuryolight_pow_tenmetu2))
        SET_VALUE(LW(6), PTR(btl_shuryolight_head_1_tenmetu))
        SET_VALUE(LW(7), PTR(btl_shuryolight_head_2_tenmetu))
        SET_VALUE(LW(8), PTR(btl_shuryolight_head_3_tenmetu))
        SET_VALUE(LW(0), 3)
        GOTO(0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("Y_1"))
        CALL(enzan_lw_save)
        SET_VALUE(LW(5), PTR(btl_shuryolight_pow_normal))
        SET_VALUE(LW(6), PTR(btl_shuryolight_head_1_on))
        SET_VALUE(LW(7), PTR(btl_shuryolight_head_2_on))
        SET_VALUE(LW(8), PTR(btl_shuryolight_head_3_on))
        SET_VALUE(LW(0), 5)
        GOTO(0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("D_2"))
        CALL(enzan_lw_save)
        SET_VALUE(LW(5), PTR(btl_shuryolight_pow_normal))
        SET_VALUE(LW(6), PTR(btl_shuryolight_head_1_tenmetu))
        SET_VALUE(LW(7), PTR(btl_shuryolight_head_2_tenmetu))
        SET_VALUE(LW(8), PTR(btl_shuryolight_head_3_tenmetu))
        SET_VALUE(LW(0), 2)
        GOTO(0)
    END_IF
    CALL(enzan_lw_save)
    SET_VALUE(LW(5), PTR(btl_shuryolight_pow_normal))
    SET_VALUE(LW(6), PTR(btl_shuryolight_head_1_normal))
    SET_VALUE(LW(7), PTR(btl_shuryolight_head_2_normal))
    SET_VALUE(LW(8), PTR(btl_shuryolight_head_3_normal))
    SET_VALUE(LW(0), 0)
    LABEL(0)
    CALL(btlevtcmd_GetUnitWork, -2, 6, LW(1))
    IF_INT_NOT_EQUAL(LW(0), LW(1))
        CALL(btlevtcmd_SetUnitWork, -2, 6, LW(0))
        CALL(btlevtcmd_GetUnitWork, -2, 4, LW(0))
        DELETE_EVENT(LW(0))
        SPAWN_EVENT_GET_ID(PTR(light_anim_rtn), LW(0))
        CALL(btlevtcmd_SetUnitWork, -2, 4, LW(0))
    END_IF
    CALL(enzan_lw_load)
    CALL(enzan_lw_load2)
    RETURN
EVT_END()

EVT_BEGIN(maiframeanimcheck)
    LOOP(0)
        CALL(btlevtcmd_AnimeGetPose, -2, 1, LW(1))
        IF_STR_NOT_EQUAL(LW(0), LW(1))
            CALL(datastrcopy, LW(1))
            CALL_CHILD(PTR(light_pose_change))
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetEventEntry, -2, PTR(entry_event))
    CALL(btl_hitoffsetx, -2, 2, -3)
    CALL(btlevtcmd_SetHpGaugeOffset, -2, -2, -6)
    CALL(btlevtcmd_AnimeChangePose, -2, 3, STRING("L_1B"))
    CALL(btlevtcmd_AnimeChangePose, -2, 4, STRING("L_4B"))
    CALL(btlevtcmd_AnimeChangePose, -2, 5, STRING("L_3B"))
    CALL(btlevtcmd_AnimeChangePose, -2, 6, STRING("L_2B"))
    CALL(btlevtcmd_AnimeChangePose, -2, 7, STRING("L_3B"))
    CALL(_set_draw_callback)
    CALL(enzan_lw_save)
    SET_VALUE(LW(5), PTR(btl_shuryolight_pow_normal))
    SET_VALUE(LW(6), PTR(btl_shuryolight_head_1_normal))
    SET_VALUE(LW(7), PTR(btl_shuryolight_head_2_normal))
    SET_VALUE(LW(8), PTR(btl_shuryolight_head_3_normal))
    SET_VALUE(LW(0), 0)
    CALL(btlevtcmd_SetUnitWork, -2, 6, LW(0))
    SPAWN_EVENT_GET_ID(PTR(light_anim_rtn), LW(0))
    CALL(btlevtcmd_SetUnitWork, -2, 4, LW(0))
    CALL(enzan_lw_load)
    CALL(enzan_lw_save)
    SET_VALUE(LW(9), PTR(btl_shuryolight_rod_normal))
    SET_VALUE(LW(0), 8)
    CALL(btlevtcmd_SetUnitWork, -2, 7, LW(0))
    SPAWN_EVENT_GET_ID(PTR(light_rod_anim_rtn), LW(0))
    CALL(btlevtcmd_SetUnitWork, -2, 5, LW(0))
    CALL(enzan_lw_load)
    CALL(pose_check_evt_run)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 3, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 2, -1)
    SET_VALUE(LW(0), 9)
    LOOP(4)
        CALL(btlevtcmd_SetUnitWork, -2, LW(0), -1)
        ADD(LW(0), 1)
    END_LOOP
    RETURN
EVT_END()

static s32 entry_event[] = {
    131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 131122, -30000000, 2, 65630, (s32)batten_leader_zoom,
    65546, 1000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"E_1", 65546,
    1000, 327771, (s32)evt_msg_print, 2, (s32)"stg8_las_65", 0, -2, 65546,
    300, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STUFF_PUTOUT1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A", 65546, 1000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STUFF_PUTOUT2", -250000000, 0, -250000000, 131163, (s32)eff_staff,
    -2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B", 65546, 2000,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STUFF_PISECE1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2", 65546, 270, 131122, -30000000,
    0, 131122, -29999994, 4, 65630, (s32)sub_call_satellite, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 69, 65627, (s32)check_satellite, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 2, 1,
};

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL(btlevtcmd_GetUnitWork, -2, 3, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SWITCH(LW(0))
            CASE_EQUAL(4)
            WAIT_MS(1500)
            CALL(evt_btl_camera_set_mode, 0, 0)
            WAIT_MS(300)
            CASE_EQUAL(5)
            WAIT_MS(1500)
            CALL(evt_btl_camera_set_mode, 0, 0)
            WAIT_MS(300)
        END_SWITCH
        CALL(btlevtcmd_SetUnitWork, -2, 3, 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(damage_sub_event)
    CALL(btlevtcmd_CheckDamageCode, LW(10), 256, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(_hp_gauge_flag_on, LW(10))
    END_IF
    CALL(btlevtcmd_GetDamage, LW(10), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetHitPos, LW(10), LW(11), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_BTL_ATTACK_MISS2"), LW(0), LW(1), LW(2), 0)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_GetDamagePartsId, LW(10), LW(11))
    IF_INT_EQUAL(LW(11), 1)
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), 1, 39)
        ELSE
        CALL(enzan_lw_save)
        SET_VALUE(LW(9), PTR(btl_shuryolight_rod_off))
        SET_VALUE(LW(0), 9)
        CALL(btlevtcmd_GetUnitWork, -2, 7, LW(1))
        IF_INT_NOT_EQUAL(LW(0), LW(1))
            CALL(btlevtcmd_SetUnitWork, -2, 7, LW(0))
            CALL(btlevtcmd_GetUnitWork, -2, 5, LW(0))
            DELETE_EVENT(LW(0))
            SPAWN_EVENT_GET_ID(PTR(light_rod_anim_rtn), LW(0))
            CALL(btlevtcmd_SetUnitWork, -2, 5, LW(0))
        END_IF
        CALL(enzan_lw_load)
        CALL(btlevtcmd_AnimeChangePose, LW(10), 1, STRING("D_2"))
    END_IF
    LABEL(90)
    CALL(btlevtcmd_CheckDamageCode, LW(10), 256, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        IF_INT_NOT_EQUAL(LW(11), 1)
            CALL(btlevtcmd_GetTotalDamage, LW(10), LW(0))
            CALL(btlevtcmd_GetUnitWork, -2, 2, LW(1))
            IF_INT_LESS(LW(1), 0)
                SET_VALUE(LW(1), 100)
                ELSE
                MULTIPLY(LW(0), 10)
                ADD(LW(1), LW(0))
                IF_INT_GREATER(LW(1), 100)
                    SET_VALUE(LW(1), 100)
                END_IF
            END_IF
            CALL(btlevtcmd_SetUnitWork, -2, 2, LW(1))
        END_IF
    END_IF
    WAIT_MS(500)
    RETURN
EVT_END()

static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108865)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(player_before_phase_event))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckPhase, LW(0), 67108867)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(monster_before_phase_event))
        GOTO(99)
    END_IF
    LABEL(99)
    RETURN
EVT_END()

EVT_BEGIN(monster_before_phase_event)
    CALL(btlevtcmd_CheckActStatus, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(0)
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_GetMaxHp, -2, LW(0))
        MULTIPLY(LW(0), 75)
        DIVIDE(LW(0), 100)
        CALL(btlevtcmd_GetHp, -2, LW(1))
        IF_INT_LESS_OR_EQUAL(LW(1), LW(0))
            CALL(btlevtcmd_SetUnitWork, -2, 1, 1)
            CALL(btlevtcmd_StopWaitEvent, -2)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            SET_VALUE(LW(0), 1)
            CALL_CHILD(PTR(batten_leader_zoom))
            CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("E_1"))
            WAIT_MS(1000)
            CALL(evt_msg_print, 2, STRING("stg8_las_66"), 0, -2)
            WAIT_MS(300)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(evt_btl_camera_set_mode, 0, 0)
        END_IF
        CASE_EQUAL(1)
        CALL(btlevtcmd_GetMaxHp, -2, LW(0))
        MULTIPLY(LW(0), 50)
        DIVIDE(LW(0), 100)
        CALL(btlevtcmd_GetHp, -2, LW(1))
        IF_INT_LESS_OR_EQUAL(LW(1), LW(0))
            CALL(btlevtcmd_SetUnitWork, -2, 1, 2)
            CALL(btlevtcmd_StopWaitEvent, -2)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            SET_VALUE(LW(0), 1)
            CALL_CHILD(PTR(batten_leader_zoom))
            CALL(evt_msg_print, 2, STRING("stg8_las_67"), 0, -2)
            WAIT_MS(300)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(evt_btl_camera_set_mode, 0, 0)
        END_IF
        CASE_EQUAL(2)
        CALL(btlevtcmd_GetMaxHp, -2, LW(0))
        MULTIPLY(LW(0), 25)
        DIVIDE(LW(0), 100)
        CALL(btlevtcmd_GetHp, -2, LW(1))
        IF_INT_LESS_OR_EQUAL(LW(1), LW(0))
            CALL(btlevtcmd_SetUnitWork, -2, 1, 3)
            CALL(btlevtcmd_StopWaitEvent, -2)
            CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_furafura))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            SET_VALUE(LW(0), 1)
            CALL_CHILD(PTR(batten_leader_zoom))
            CALL(btlevtcmd_SetTalkPoseType, -2, 65)
            CALL(btlevtcmd_SetStayPoseType, -2, 43)
            CALL(evt_msg_print, 2, STRING("stg8_las_68"), 0, -2)
            WAIT_MS(300)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(evt_btl_camera_set_mode, 0, 0)
        END_IF
    END_SWITCH
    LABEL(0)
    RETURN
EVT_END()

static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_WaitAttackEnd)
    SET_VALUE(LW(0), 9)
    LOOP(4)
        CALL(btlevtcmd_GetUnitWork, -2, LW(0), LW(1))
        CALL(btlevtcmd_GetUnitId, LW(1), LW(1))
        IF_INT_NOT_EQUAL(LW(1), -1)
            CALL(btlevtcmd_CheckDamageCode, LW(1), 512, LW(2))
            IF_INT_EQUAL(LW(2), 0)
                SET_VALUE(LW(10), LW(1))
                BEGIN_INLINE_EVENT
                    CALL_CHILD(PTR(subsetevt_dead_core))
                    CALL(btlevtcmd_GetBodyId, LW(10), LW(11))
                    CALL(btlevtcmd_OnPartsAttribute, LW(10), LW(11), 16777216)
                    CALL(btlevtcmd_OnPartsAttribute, LW(10), LW(11), 33554432)
                END_INLINE_EVENT
                WAIT_MS(200)
            END_IF
        END_IF
        ADD(LW(0), 1)
    END_LOOP
    WAIT_MS(1000)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(pose_check_evt_stop)
    CALL(enzan_lw_save)
    SET_VALUE(LW(5), PTR(btl_shuryolight_pow_tenmetu))
    SET_VALUE(LW(6), PTR(btl_shuryolight_head_1_off))
    SET_VALUE(LW(7), PTR(btl_shuryolight_head_2_off))
    SET_VALUE(LW(8), PTR(btl_shuryolight_head_3_off))
    SET_VALUE(LW(0), 7)
    CALL(btlevtcmd_GetUnitWork, -2, 6, LW(1))
    IF_INT_NOT_EQUAL(LW(0), LW(1))
        CALL(btlevtcmd_SetUnitWork, -2, 6, LW(0))
        CALL(btlevtcmd_GetUnitWork, -2, 4, LW(0))
        DELETE_EVENT(LW(0))
        SPAWN_EVENT_GET_ID(PTR(light_anim_rtn), LW(0))
        CALL(btlevtcmd_SetUnitWork, -2, 4, LW(0))
    END_IF
    CALL(enzan_lw_load)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("D_3"))
    WAIT_MS(750)
    CALL(btlevtcmd_SetTalkPose, -2, STRING("T_5"))
    CALL(btlevtcmd_SetStayPose, -2, STRING("D_4"))
    CALL(evt_msg_print, 2, STRING("stg8_las_69"), 0, -2)
    WAIT_MS(300)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("D_4"))
    WAIT_MS(500)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(btlevtcmd_GetUnitWork, -2, 4, LW(0))
    DELETE_EVENT(LW(0))
    CALL(btlevtcmd_GetUnitWork, -2, 5, LW(0))
    DELETE_EVENT(LW(0))
    SET_VALUE(LW(10), -2)
    CALL_CHILD(PTR(subsetevt_dead_core_nospin_norotate))
    RETURN
EVT_END()

static s32 splineTableIn1_1[] = {
    1108869120, 1110704128, 1084227584, 1106457395, -1088841280, -1063256064, 1100480512, -1048785716,
    -1063256064, 1089680179, -1088841280, -1063256064, 0, 1110704128, -1063256064,
};

static s32 splineTableIn2_1[] = {
    1108869120, 1110704128, 1084227584, 1106457395, -1088841280, -1063256064, 1100480512, -1048785716,
    -1063256064, 1089680179, -1088841280, -1063256064, 0, 1110704128, -1063256064,
};

static s32 splineTableIn2_2[] = {
    -1038614528, 1110704128, 1084227584, -1041026253, 1119171380, -1063256064, -1047003136, 1119171380,
    -1063256064, -1057803469, 1119171380, -1063256064, 0, 1110704128, -1063256064,
};

static s32 splineTableIn3_1[] = {
    0, 1118175232, 1084227584, 0, 1122159821, -1063256064, 0, 1123155968,
    -1063256064, 0, 1118175232, -1063256064, 0, 1110704128, -1063256064,
};

static s32 splineTableIn3_2[] = {
    1108869120, 1088421888, 1084227584, 1114846003, -1048785716, -1063256064, 1110861415, -1056754892,
    -1063256064, 1106457395, 1088421888, -1063256064, 0, 1110704128, -1063256064,
};

static s32 splineTableIn3_3[] = {
    -1038614528, 1088421888, 1084227584, -1032637645, -1048785716, -1063256064, -1036622233, -1056754892,
    -1063256064, -1041026253, 1088421888, -1063256064, 0, 1110704128, -1063256064,
};

static s32 splineTableIn4_1[] = {
    1108869120, 1118175232, 1084227584, 1110861415, 1120167526, -1063256064, 1114846003, 1122159821,
    -1063256064, 1106457395, 1118175232, -1063256064, 0, 1110704128, -1063256064,
};

static s32 splineTableIn4_2[] = {
    -1038614528, 1118175232, 1084227584, -1036622233, 1120167526, -1063256064, -1032637645, 1122159821,
    -1063256064, -1041026253, 1118175232, -1063256064, 0, 1110704128, -1063256064,
};

static s32 splineTableIn4_3[] = {
    1108869120, 1088421888, 1084227584, 1110861415, -1056754892, -1063256064, 1114846003, -1044696268,
    -1063256064, 1106457395, 1088421888, -1063256064, 0, 1110704128, -1063256064,
};

static s32 splineTableIn4_4[] = {
    -1038614528, 1088421888, 1084227584, -1036622233, -1056754892, -1063256064, -1032637645, -1044696268,
    -1063256064, -1041026253, 1088421888, -1063256064, 0, 1110704128, -1063256064,
};

static s32 splineTableOut1_1[] = {
    0, 1110704128, -1063256064, -1034629939, -1056754892, -1063256064, -1032637645, 1110704128,
    -1063256064, 1110861415, 1121163674, -1063256064, 1108869120, 1110704128, 1084227584,
};

static s32 splineTableOut2_1[] = {
    0, 1110704128, -1063256064, 1089680179, 1119171380, -1063256064, 1100480512, 1121163674,
    -1063256064, 1106457395, 1119171380, -1063256064, 1108869120, 1110704128, 1084227584,
};

static s32 splineTableOut2_2[] = {
    0, 1110704128, -1063256064, -1057803469, -1088841280, -1063256064, -1047003136, -1048785716,
    -1063256064, -1041026253, -1088841280, -1063256064, -1038614528, 1110704128, 1084227584,
};

static s32 splineTableOut3_1[] = {
    0, 1110704128, -1063256064, 0, 1118175232, -1063256064, 0, 1123155968,
    -1063256064, 0, 1122159821, -1063256064, 0, 1118175232, 1084227584,
};

static s32 splineTableOut3_2[] = {
    0, 1110704128, -1063256064, 1108869120, 1097439642, -1063256064, 1116261581, -1088841280,
    -1063256064, 1110861415, 1088421888, -1063256064, 1108869120, 1088421888, 1084227584,
};

static s32 splineTableOut3_3[] = {
    0, 1110704128, -1063256064, -1038614528, 1097439642, -1063256064, -1031222067, -1088841280,
    -1063256064, -1036622233, 1088421888, -1063256064, -1038614528, 1088421888, 1084227584,
};

static s32 splineTableOut4_1[] = {
    0, 1110704128, -1063256064, 1108869120, 1117179085, -1063256064, 1116261581, 1119171380,
    -1063256064, 1110861415, 1118175232, -1063256064, 1108869120, 1118175232, 1084227584,
};

static s32 splineTableOut4_2[] = {
    0, 1110704128, -1063256064, -1038614528, 1117179085, -1063256064, -1031222067, 1119171380,
    -1063256064, -1036622233, 1118175232, -1063256064, -1038614528, 1118175232, 1084227584,
};

static s32 splineTableOut4_3[] = {
    0, 1110704128, -1063256064, 1108869120, 1097439642, -1063256064, 1116261581, -1088841280,
    -1063256064, 1110861415, 1088421888, -1063256064, 1108869120, 1088421888, 1084227584,
};

static s32 splineTableOut4_4[] = {
    0, 1110704128, -1063256064, -1038614528, 1097439642, -1063256064, -1031222067, -1088841280,
    -1063256064, -1036622233, 1088421888, -1063256064, -1038614528, 1088421888, 1084227584,
};

static EVT_BEGIN(satellite_blur_on)
    SET_VALUE(LW(2), 9)
    LOOP(4)
        CALL(btlevtcmd_GetUnitWork, -2, LW(2), LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
            CALL(btlevtcmd_SetPartsBlur, LW(3), LW(4), 255, 255, 255, 255, 255, 255, 255, 100, 0)
            CALL(btlevtcmd_OnPartsAttribute, LW(3), LW(4), 67108864)
        END_IF
        ADD(LW(2), 1)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(satellite_blur_off)
    SET_VALUE(LW(2), 9)
    LOOP(4)
        CALL(btlevtcmd_GetUnitWork, -2, LW(2), LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
            CALL(btlevtcmd_OffPartsAttribute, LW(3), LW(4), 67108864)
        END_IF
        ADD(LW(2), 1)
    END_LOOP
    RETURN
EVT_END()

s32 sub_call_satellite[] = {
    196699, (s32)btlevtcmd_GetUnitId, -2, -29999996, 131122, -29999999, 9, 131122,
    -29999995, 0, 65541, 4, 262235, (s32)btlevtcmd_GetUnitWork, -2, -29999999,
    -29999998, 131096, -29999998, -1, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_batten_satellite,
    0, 327771, (s32)btlevtcmd_AddPos, -29999997, 0, 45, -5, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, -29999999, -29999997, 262235, (s32)btlevtcmd_SetUnitWork, -29999997, 0,
    -29999996, 131125, -30000000, 1, 131125, -29999995, 1, 131101,
    -29999995, -29999994, 7, 33, 33, 131125, -29999999, 1,
    6, 65545, 5, 65630, (s32)satellite_blur_on, 131097, -30000000, 0,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_SPLIT2", -250000000, 0, -250000000, 33,
    196699, (s32)battenSatelliteToOutside, -2, -30000000, 65546, 1000, 65630, (s32)satellite_blur_off,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 0, -30000000, 2, 1,
};

s32 player_before_phase_event[] = {
    131163, (s32)btlevtcmd_StopWaitEvent, -2, 131163, (s32)btlevtcmd_get_turn, -30000000, 131100, -30000000,
    1, 65540, 99, 33, 196699, (s32)btlevtcmd_CheckActStatus, -2, -30000000,
    131096, -30000000, 0, 65540, 99, 33, 196699, (s32)evt_sub_random,
    10, -30000000, 65545, -30000000, 131122, -30000000, 0, 131122,
    -29999999, 9, 65541, 4, 262235, (s32)btlevtcmd_GetUnitWork, -2, -29999999,
    -29999997, 131097, -29999997, -1, 131125, -30000000, 1, 33,
    131125, -29999999, 1, 6, 131101, -30000000, 4, 65540,
    99, 33, 65630, (s32)satellite_blur_on, 131097, -29999999, 0, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_SPLIT1", -250000000, 0, -250000000, 33, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 0, -29999999, 196699, (s32)battenSatelliteToInside, -2, -29999999,
    65630, (s32)satellite_blur_off, 131122, -29999999, 9, 65541, 3, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, -29999999, -29999998, 131096, -29999998, -1, 131122,
    -29999996, -29999999, 131122, -29999997, 999999999, 65541, 0, 131096,
    -29999997, 999999999, 131122, -29999997, -29999999, 131125, -29999997, 1,
    32, 131125, -29999997, 1, 131125, -29999997, 0, 33,
    131126, -29999997, 0, 131099, -29999997, 12, 131125, -29999997,
    0, 7, 33, 131125, -29999997, 0, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, -29999997, -29999998, 262235, (s32)btlevtcmd_SetUnitWork, -2, -29999996, -29999998,
    131122, -29999996, -29999997, 6, 262235, (s32)btlevtcmd_SetUnitWork, -2, -29999996,
    -1, 33, 131125, -29999999, 1, 6, 131122, -29999994,
    2, 65630, (s32)sub_call_satellite, 65539, 99, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_get_turn, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 1)
        SET_VALUE(LW(9), PTR(weapon_batten_leader_thunder))
        CALL_CHILD(PTR(batten_leader_thunder_attack_event))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(2))
    IF_INT_LESS(LW(2), 2)
        CALL(btlevtcmd_DrawLots, LW(0), 6, 60, 40, 30, 20, 20, 20)
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_VALUE(LW(9), PTR(weapon_batten_leader_thunder))
            CALL_CHILD(PTR(batten_leader_thunder_attack_event))
            CASE_EQUAL(1)
            SET_VALUE(LW(9), PTR(weapon_batten_leader_fire))
            CALL_CHILD(PTR(batten_leader_fire_attack_event))
            CASE_EQUAL(2)
            SET_VALUE(LW(9), PTR(weapon_batten_leader_ice))
            CALL_CHILD(PTR(batten_leader_ice_attack_event))
            CASE_EQUAL(3)
            SET_VALUE(LW(9), PTR(weapon_batten_leader_shikaeshi))
            CALL_CHILD(PTR(batten_leader_shikaeshi_attack_event))
            CASE_EQUAL(4)
            SET_VALUE(LW(9), PTR(weapon_batten_leader_yokeyoke))
            CALL_CHILD(PTR(batten_leader_yokeyoke_attack_event))
            CASE_EQUAL(5)
            SET_VALUE(LW(9), PTR(weapon_batten_leader_stop))
            CALL_CHILD(PTR(batten_leader_stop_attack_event))
        END_SWITCH
        ELSE
        CALL(btlevtcmd_DrawLots, LW(0), 6, 60, 40, 30, 20, 20, 20)
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_VALUE(LW(9), PTR(weapon_batten_leader_thunder))
            CALL_CHILD(PTR(batten_leader_thunder_attack_event))
            CASE_EQUAL(1)
            SET_VALUE(LW(9), PTR(weapon_batten_leader_fire))
            CALL_CHILD(PTR(batten_leader_fire_attack_event))
            CASE_EQUAL(2)
            SET_VALUE(LW(9), PTR(weapon_batten_leader_ice))
            CALL_CHILD(PTR(batten_leader_ice_attack_event))
            CASE_EQUAL(3)
            SET_VALUE(LW(9), PTR(weapon_batten_leader_shikaeshi))
            CALL_CHILD(PTR(batten_leader_shikaeshi_attack_event))
            CASE_EQUAL(4)
            SET_VALUE(LW(9), PTR(weapon_batten_leader_yokeyoke))
            CALL_CHILD(PTR(batten_leader_yokeyoke_attack_event))
            CASE_EQUAL(5)
            SET_VALUE(LW(9), PTR(weapon_batten_leader_stop))
            CALL_CHILD(PTR(batten_leader_stop_attack_event))
        END_SWITCH
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 batten_leader_thunder_attack_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STUFF_PUTOUT1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A", 65546, 170, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_SRYO_STUFF_PUTOUT2", -250000000, 0, -250000000, 131163, (s32)eff_staff, -2,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B", 65546, 2000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STUFF_PISECE1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"A_2", 65546, 270, 65627, (s32)enzan_lw_save, 131122,
    -29999991, (s32)btl_shuryolight_rod_normal, 131122, -30000000, 8, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    7, -29999999, 131097, -30000000, -29999999, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    7, -30000000, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000, 65631,
    -30000000, 131165, (s32)light_rod_anim_rtn, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5,
    -30000000, 33, 65627, (s32)enzan_lw_load, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2,
    -29999999, 131099, -29999999, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2,
    0, 196699, (s32)btlevtcmd_GetRandomValue, 100, -29999998, 131098, -29999998, -29999999,
    327771, (s32)btlevtcmd_GetPosFloat, -2, -30000000, -29999999, -29999998, 131130, -30000000,
    -230053248, 131130, -29999999, -229938560, 131130, -29999998, -229979520, 983131,
    (s32)evt_eff, (s32)"KEMURI_EFF_00", (s32)"kemuri_test", 19, -30000000, -29999999, -29999998, -229998976,
    0, 0, 0, 0, 0, 0, 0, 65546,
    600, 2, 33, 33, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 131096, -29999997, -1,
    262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0,
    65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 65546, 500, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_SRYO_THUNDER1", -250000000, 0, -250000000, 262235, (s32)evt_eff_pokopi_thunder, -80, 0,
    25, 262235, (s32)evt_eff_pokopi_thunder, -160, 0, -25, 65546, 100,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_THUNDER1", -250000000, 0, -250000000, 262235,
    (s32)evt_eff_pokopi_thunder, -100, 0, 35, 262235, (s32)evt_eff_pokopi_thunder, -140, 0,
    -35, 65546, 100, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_THUNDER1", -250000000,
    0, -250000000, 262235, (s32)evt_eff_pokopi_thunder, -120, 0, 25, 262235,
    (s32)evt_eff_pokopi_thunder, -120, 0, -25, 65546, 100, 107, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_THUNDER1", -250000000, 0, -250000000, 262235, (s32)evt_eff_pokopi_thunder,
    -140, 0, 35, 262235, (s32)evt_eff_pokopi_thunder, -100, 0, -35,
    65546, 100, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_THUNDER1", -250000000, 0,
    -250000000, 262235, (s32)evt_eff_pokopi_thunder, -160, 0, 25, 262235, (s32)evt_eff_pokopi_thunder,
    -80, 0, -25, 109, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996,
    131122, -29999990, 0, 65541, 0, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 49, 65539,
    90, 65540, 98, 65539, 91, 131096, -29999990, 0,
    131122, -29999990, 1, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 33,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65539, 98, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131096, -29999997,
    -1, 7, 33, 6, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2,
    1,
};

s32 batten_leader_fire_attack_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STUFF_PUTOUT1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A", 65546, 170, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_SRYO_STUFF_PUTOUT2", -250000000, 0, -250000000, 131163, (s32)eff_staff, -2,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B", 65546, 2000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STUFF_PISECE1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"A_2", 65546, 270, 65627, (s32)enzan_lw_save, 131122,
    -29999991, (s32)btl_shuryolight_rod_normal, 131122, -30000000, 8, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    7, -29999999, 131097, -30000000, -29999999, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    7, -30000000, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000, 65631,
    -30000000, 131165, (s32)light_rod_anim_rtn, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5,
    -30000000, 33, 65627, (s32)enzan_lw_load, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2,
    -29999999, 131099, -29999999, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2,
    0, 196699, (s32)btlevtcmd_GetRandomValue, 100, -29999998, 131098, -29999998, -29999999,
    327771, (s32)btlevtcmd_GetPosFloat, -2, -30000000, -29999999, -29999998, 131130, -30000000,
    -230053248, 131130, -29999999, -229938560, 131130, -29999998, -229979520, 983131,
    (s32)evt_eff, (s32)"KEMURI_EFF_00", (s32)"kemuri_test", 19, -30000000, -29999999, -29999998, -229998976,
    0, 0, 0, 0, 0, 0, 0, 65546,
    600, 2, 33, 33, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 131096, -29999997, -1,
    262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0,
    65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991,
    131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2,
    -29999991, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_FIRE1", -250000000, 0, -29999985,
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 327771, (s32)btlevtcmd_GetPosFloat, -2, -30000000,
    -29999999, -29999998, 131124, -29999995, -30000000, 131130, -30000000, -40,
    131130, -29999995, -400, 983131, (s32)evt_eff, (s32)"", (s32)"hibashira", 4,
    -30000000, -29999999, -29999998, -29999995, -29999999, -29999998, 20, -229998976,
    60, 0, 0, 107, 65546, 1000, 131163, (s32)evt_snd_sfxoff,
    -29999985, 109, 131163, (s32)bts_x_flag_set, 0, 131122, -29999993, 1,
    110, 131163, (s32)bts_x_flag_add, 1, 112, 65546, 600, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991,
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131122, -29999990, 0, 65541,
    0, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256,
    -29999995, 65570, -29999995, 65579, 4, 131122, -29999994, 90,
    46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 131122,
    -29999994, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 131122, -29999994, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 131122, -29999994, 90, 65572, 1, 131122,
    -29999994, 91, 46, 42, 131122, -29999994, 97, 46,
    49, 65540, -29999994, 65539, 90, 65540, 97, 65539,
    91, 131096, -29999990, 0, 131122, -29999990, 1, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 131125, -29999993, 1, 110, 327771,
    (s32)evt_cam_shake, 4, -229999994, -230000000, 500, 131163, (s32)bts_x_flag_add, 1,
    112, 33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65539, 97, 65546, 150, 196699, (s32)btlevtcmd_GetSelectNextEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 7, 33, 6,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)bts_x_flag_wait, -29999993, 2, 1,
};

s32 batten_leader_ice_attack_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STUFF_PUTOUT1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A", 65546, 170, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_SRYO_STUFF_PUTOUT2", -250000000, 0, -250000000, 131163, (s32)eff_staff, -2,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B", 65546, 2000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STUFF_PISECE1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"A_2", 65546, 270, 65627, (s32)enzan_lw_save, 131122,
    -29999991, (s32)btl_shuryolight_rod_normal, 131122, -30000000, 8, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    7, -29999999, 131097, -30000000, -29999999, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    7, -30000000, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000, 65631,
    -30000000, 131165, (s32)light_rod_anim_rtn, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5,
    -30000000, 33, 65627, (s32)enzan_lw_load, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2,
    -29999999, 131099, -29999999, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2,
    0, 196699, (s32)btlevtcmd_GetRandomValue, 100, -29999998, 131098, -29999998, -29999999,
    327771, (s32)btlevtcmd_GetPosFloat, -2, -30000000, -29999999, -29999998, 131130, -30000000,
    -230053248, 131130, -29999999, -229938560, 131130, -29999998, -229979520, 983131,
    (s32)evt_eff, (s32)"KEMURI_EFF_00", (s32)"kemuri_test", 19, -30000000, -29999999, -29999998, -229998976,
    0, 0, 0, 0, 0, 0, 0, 65546,
    600, 2, 33, 33, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991,
    -29999997, -29999996, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2,
    16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 33,
    2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2,
    -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_ICE1", -250000000, 0, -250000000, 327771,
    (s32)btlevtcmd_GetPosFloat, -2, -30000000, -29999999, -29999998, 131130, -30000000, -230053248,
    131130, -29999999, -229938560, 131130, -29999998, -229989760, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -29999995, -29999994, -29999993, 131130, -29999993, -229989760,
    983131, (s32)evt_eff64, (s32)"ICE_EFF_00", (s32)"opuku_wgun_n64", 0, -30000000, -29999999, -29999998,
    -29999995, -29999994, -29999993, -229998976, 9, 0, 0, 0,
    65546, 150, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65570, -29999995, 65579, 4, 65540, 90,
    46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540,
    90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    65540, 90, 65572, 1, 65540, 91, 46, 42,
    65540, 98, 46, 49, 65539, 90, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 69, 65546, 300, 65540, 98, 65539,
    91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 69, 65539, 98, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2,
    1,
};

s32 batten_leader_shikaeshi_attack_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STUFF_PUTOUT1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A", 65546, 170, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_SRYO_STUFF_PUTOUT2", -250000000, 0, -250000000, 131163, (s32)eff_staff, -2,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B", 65546, 2000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STUFF_PISECE1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"A_1C", 65546, 140, 65627, (s32)enzan_lw_save, 131122,
    -29999991, (s32)btl_shuryolight_rod_normal, 131122, -30000000, 8, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    7, -29999999, 131097, -30000000, -29999999, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    7, -30000000, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000, 65631,
    -30000000, 131165, (s32)light_rod_anim_rtn, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5,
    -30000000, 33, 65627, (s32)enzan_lw_load, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2,
    -29999999, 131099, -29999999, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2,
    0, 196699, (s32)btlevtcmd_GetRandomValue, 100, -29999998, 131098, -29999998, -29999999,
    327771, (s32)btlevtcmd_GetPosFloat, -2, -30000000, -29999999, -29999998, 131130, -30000000,
    -230025600, 131130, -29999999, -229918080, 131130, -29999998, -229979520, 983131,
    (s32)evt_eff, (s32)"KEMURI_EFF_00", (s32)"kemuri_test", 19, -30000000, -29999999, -29999998, -229998976,
    0, 0, 0, 0, 0, 0, 0, 65546,
    600, 2, 33, 33, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991,
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    400, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3, 4, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -2, 1, -29999991, 256, -29999995, 2, 1,
};

s32 batten_leader_yokeyoke_attack_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STUFF_PUTOUT1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A", 65546, 170, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_SRYO_STUFF_PUTOUT2", -250000000, 0, -250000000, 131163, (s32)eff_staff, -2,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B", 65546, 2000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STUFF_PISECE1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"A_1C", 65546, 140, 65627, (s32)enzan_lw_save, 131122,
    -29999991, (s32)btl_shuryolight_rod_normal, 131122, -30000000, 8, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    7, -29999999, 131097, -30000000, -29999999, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    7, -30000000, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000, 65631,
    -30000000, 131165, (s32)light_rod_anim_rtn, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5,
    -30000000, 33, 65627, (s32)enzan_lw_load, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2,
    -29999999, 131099, -29999999, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2,
    0, 196699, (s32)btlevtcmd_GetRandomValue, 100, -29999998, 131098, -29999998, -29999999,
    327771, (s32)btlevtcmd_GetPosFloat, -2, -30000000, -29999999, -29999998, 131130, -30000000,
    -230025600, 131130, -29999999, -229918080, 131130, -29999998, -229979520, 983131,
    (s32)evt_eff, (s32)"KEMURI_EFF_00", (s32)"kemuri_test", 19, -30000000, -29999999, -29999998, -229998976,
    0, 0, 0, 0, 0, 0, 0, 65546,
    600, 2, 33, 33, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991,
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    400, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3, 5, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -2, 1, -29999991, 256, -29999995, 2, 1,
};

s32 batten_leader_stop_attack_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STUFF_PUTOUT1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A", 65546, 170, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_SRYO_STUFF_PUTOUT2", -250000000, 0, -250000000, 131163, (s32)eff_staff, -2,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B", 65546, 2000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STUFF_PISECE1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"A_2", 65546, 270, 65627, (s32)enzan_lw_save, 131122,
    -29999991, (s32)btl_shuryolight_rod_normal, 131122, -30000000, 8, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    7, -29999999, 131097, -30000000, -29999999, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    7, -30000000, 262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000, 65631,
    -30000000, 131165, (s32)light_rod_anim_rtn, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5,
    -30000000, 33, 65627, (s32)enzan_lw_load, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2,
    -29999999, 131099, -29999999, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2,
    0, 196699, (s32)btlevtcmd_GetRandomValue, 100, -29999998, 131098, -29999998, -29999999,
    327771, (s32)btlevtcmd_GetPosFloat, -2, -30000000, -29999999, -29999998, 131130, -30000000,
    -230053248, 131130, -29999999, -229938560, 131130, -29999998, -229979520, 983131,
    (s32)evt_eff, (s32)"KEMURI_EFF_00", (s32)"kemuri_test", 19, -30000000, -29999999, -29999998, -229998976,
    0, 0, 0, 0, 0, 0, 0, 65546,
    600, 2, 33, 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SRYO_STOP1",
    -250000000, 0, -250000000, 327771, (s32)evt_cam_get_at, 4, -30000000, -29999999,
    -29999998, 131130, -30000000, -230025600, 131124, -29999998, -229897600, 983131,
    (s32)evt_eff64, (s32)"TIMESTOP_EFF_00", (s32)"timestamp_n64", 0, -30000000, -29999999, -29999998, -229998976,
    150, 0, 0, 0, 0, 0, 0, 65546,
    2500, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2,
    -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096,
    -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097,
    -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999991, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131122,
    -29999990, 0, 65541, 0, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, -29999991, 256, -29999995, 65570, -29999995, 65579, 4,
    131122, -29999994, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 131122, -29999994, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 131122, -29999994, 90, 65572,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 131122, -29999994, 90,
    65572, 1, 131122, -29999994, 91, 46, 42, 131122,
    -29999994, 97, 46, 49, 65540, -29999994, 65539, 90,
    65540, 97, 65539, 91, 131096, -29999990, 0, 131122,
    -29999990, 1, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 33, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995, 65539,
    97, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131096, -29999997, -1,
    7, 33, 6, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
};

static s32 wait_event[] = {
    65627, (s32)check_satellite, 196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 65541, 0,
    65545, 1, 65627, (s32)check_satellite, 6, 2, 1, 0,
};

USER_FUNC(btlevtcmd_AnimeGetPose) {
    s32 id;
    s32* args = event->args;
    s32 partNo;
    BattleUnitPart* part;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    partNo = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, partNo);


    evtSetValue(event, args[2], (s32)animPoseGetCurrentAnim(part->poseId));
    return EVT_RETURN_DONE;
}
static USER_FUNC(enzan_lw_save) {
    s32 i;

    for (i = 0; i < 16; i++) {
        xlw[i] = event->lwData[i];
    }
    return EVT_RETURN_DONE;
}
static USER_FUNC(enzan_lw_load) {
    s32 i;

    for (i = 0; i < 16; i++) {
        event->lwData[i] = xlw[i];
    }
    return EVT_RETURN_DONE;
}
USER_FUNC(enzan_lw_save2) {
    s32 i;

    for (i = 0; i < 16; i++) {
        xlw2[i] = event->lwData[i];
    }
    return EVT_RETURN_DONE;
}
USER_FUNC(enzan_lw_load2) {
    s32 i;

    for (i = 0; i < 16; i++) {
        event->lwData[i] = xlw2[i];
    }
    return EVT_RETURN_DONE;
}
USER_FUNC(datastrcopy) {
    s8* s = (s8*)evtGetValue(event, event->args[0]);
    s32 i;

    for (i = 0; i < 16 && s[i] != 0; i++) {
        xmemo[i] = s[i];
    }
    xmemo[i] = 0;
    return EVT_RETURN_DONE;
}
USER_FUNC(pose_check_evt_run) {
    xevt = evtEntryType(maiframeanimcheck, event->priority, 0, event->type);
    xevt->unitId = event->unitId;
    xevt->ownerNPC = event->ownerNPC;
    xmemo[0] = 0;
    xevt->lwData[0] = (s32)xmemo;
    xevt->uwBase = event->uwBase;
    xevt->ufBase = event->ufBase;
    return EVT_RETURN_DONE;
}
USER_FUNC(pose_check_evt_stop) {
    evtDeleteID(xevt->eventId);
    return EVT_RETURN_DONE;
}
USER_FUNC(btl_hitoffsetx) {
    s32 id;
    s32* args = event->args;
    s32 partNo;
    BattleUnitPart* part;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    partNo = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, partNo);


    part->hitOffsetX = evtGetValue(event, args[2]);
    return EVT_RETURN_DONE;
}
static USER_FUNC(_set_draw_callback) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(wp, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);
    BattleUnitPart* p3;
    BattleUnitPart* p4;
    BattleUnitPart* p5;
    BattleUnitPart* p6;
    BattleUnitPart* p7;

    animPoseSetDispCallBack(part->poseId, _light_point_callback, part);
    p3 = BtlUnit_GetPartsPtr(unit, 3);
    p4 = BtlUnit_GetPartsPtr(unit, 4);
    p5 = BtlUnit_GetPartsPtr(unit, 5);
    p6 = BtlUnit_GetPartsPtr(unit, 6);
    p7 = BtlUnit_GetPartsPtr(unit, 7);
    p3->attributes |= 0x1000000;
    p4->attributes |= 0x1000000;
    p5->attributes |= 0x1000000;
    p6->attributes |= 0x1000000;
    p7->attributes |= 0x1000000;
    return EVT_RETURN_DONE;
}
void _light_point_callback(BattleUnitPart* part, s32 group) {
    BattleUnit* unit;
    s32 poseId;
    s32 idx;
    s32 shape;


    poseId = part->poseId;
    unit = part->mOwner;


    if (strcmp("locator6", animPoseGetGroupName(poseId, group)) == 0) {
        idx = 0;
    } else if (strcmp("locator9", animPoseGetGroupName(poseId, group)) == 0) {
        idx = 1;
    } else if (strcmp("locator8", animPoseGetGroupName(poseId, group)) == 0) {
        idx = 2;
    } else if (strcmp("locator7", animPoseGetGroupName(poseId, group)) == 0) {
        idx = 3;
    } else if (strcmp("locator5", animPoseGetGroupName(poseId, group)) == 0) {
        idx = 4;
    } else {
        idx = -1;
    }
    switch (idx) {
        case 0:
            {
                s32 pose = BtlUnit_GetPartsPtr(unit, 3)->poseId;
                s32 sh = animPoseGetShapeIdx(pose, "pPlaneShape34");
                animPoseDrawShape(pose, sh);
            }
            break;
        case 1:
            {
                s32 pose = BtlUnit_GetPartsPtr(unit, 4)->poseId;
                s32 sh = animPoseGetShapeIdx(pose, "pPlaneShape37");
                animPoseDrawShape(pose, sh);
            }
            break;
        case 2:
            {
                s32 pose = BtlUnit_GetPartsPtr(unit, 5)->poseId;
                s32 sh = animPoseGetShapeIdx(pose, "pPlaneShape36");
                animPoseDrawShape(pose, sh);
            }
            break;
        case 3:
            {
                s32 pose = BtlUnit_GetPartsPtr(unit, 6)->poseId;
                s32 sh = animPoseGetShapeIdx(pose, "pPlaneShape35");
                animPoseDrawShape(pose, sh);
            }
            break;
        case 4:
            {
                s32 pose = BtlUnit_GetPartsPtr(unit, 7)->poseId;
                s32 sh = animPoseGetShapeIdx(pose, "pPlaneShape36");
                animPoseDrawShape(pose, sh);
            }
            break;
    }
}
USER_FUNC(_hp_gauge_flag_on) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    if (unit != NULL) {
        unit->hpGauge.field_0x2 |= 1;
    }
    return EVT_RETURN_DONE;
}
u8 battenSatelliteTo_Init(BattleUnit* unit, s32 n, s32* table) {
    BattenSpline* sp;

    sp = BTL_ALLOC(sizeof(BattenSpline));
    if (unit->work[9 + n] == -1) {
        return FALSE;
    }
    unit->work[13 + n] = (s32)sp;
    sp->n = 5;
    sp->table = table;
    sp->count = 0;
    spline_maketable(5, sp->table, sp->a, sp->b);
    BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[9 + n]), 1)->work[1] = (s32)table;
    return TRUE;
}
u8 battenSatelliteTo_Main(BattleUnit* unit, s32 n) {
    BattenSpline* sp;
    BattleUnit* sat;
    Vec upos;
    Vec pos;

    if (unit->work[9 + n] == -1) {
        return FALSE;
    }
    sp = (BattenSpline*)unit->work[13 + n];
    if (sp == NULL) {
        return FALSE;
    }
    if (sp->count >= 60) {
        if (sp != NULL) {
            BTL_FREE(sp);
            unit->work[13 + n] = 0;
        }
        return FALSE;
    }
    spline_getvalue(intplGetValue(4, sp->count, 60, 0.0f, 1.0f), &pos, sp->n, sp->table, sp->a, sp->b);
    sat = BattleGetUnitPtr(_battleWorkPointer, unit->work[9 + n]);
    if (sat == NULL) {
        return FALSE;
    }
    BtlUnit_GetPos(unit, &upos.x, &upos.y, &upos.z);
    BtlUnit_SetPos(sat, upos.x + pos.x * unit->faceDirection, 5.0f + (upos.y + pos.y), upos.z + pos.z);
    BtlUnit_SetHomePos(sat, upos.x + pos.x * unit->faceDirection, 5.0f + (upos.y + pos.y), upos.z + pos.z);
    sp->count++;
    return TRUE;
}
USER_FUNC(battenSatelliteToInside) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 num = evtGetValue(event, args[1]);
    BattleUnit* unit;
    u8 moving;
    s32 i;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        for (i = 0; i < 4; i++) {
            if (unit->work[9 + i] != -1) {
                s32 table = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[9 + i]), 1)->work[1];

                if (table == (s32)splineTableOut1_1) {
                    battenSatelliteTo_Init(unit, i, splineTableIn1_1);
                }
                if (table == (s32)splineTableOut2_1) {
                    battenSatelliteTo_Init(unit, i, splineTableIn2_1);
                }
                if (table == (s32)splineTableOut2_2) {
                    battenSatelliteTo_Init(unit, i, splineTableIn2_2);
                }
                if (table == (s32)splineTableOut3_1) {
                    battenSatelliteTo_Init(unit, i, splineTableIn3_1);
                }
                if (table == (s32)splineTableOut3_2) {
                    battenSatelliteTo_Init(unit, i, splineTableIn3_2);
                }
                if (table == (s32)splineTableOut3_3) {
                    battenSatelliteTo_Init(unit, i, splineTableIn3_3);
                }
                if (table == (s32)splineTableOut4_1) {
                    battenSatelliteTo_Init(unit, i, splineTableIn4_1);
                }
                if (table == (s32)splineTableOut4_2) {
                    battenSatelliteTo_Init(unit, i, splineTableIn4_2);
                }
                if (table == (s32)splineTableOut4_3) {
                    battenSatelliteTo_Init(unit, i, splineTableIn4_3);
                }
                if (table == (s32)splineTableOut4_4) {
                    battenSatelliteTo_Init(unit, i, splineTableIn4_4);
                }
            }
        }
    }
    moving = FALSE;
    for (i = 0; i < 4; i++) {
        if (battenSatelliteTo_Main(unit, i) == TRUE) {
            moving = TRUE;
        }
    }
    return moving == FALSE ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
USER_FUNC(battenSatelliteToOutside) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 num = evtGetValue(event, args[1]);
    BattleUnit* unit;
    u8 moving;
    s32 i;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        switch (num) {
        case 1:
            i = 0;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut1_1) == TRUE) {
                    break;
                }
                i++;
            }
            break;
        case 2:
            i = 0;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut2_1) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut2_2) == TRUE) {
                    break;
                }
                i++;
            }
            break;
        case 3:
            i = 0;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut3_1) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut3_2) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut3_3) == TRUE) {
                    break;
                }
                i++;
            }
            break;
        case 4:
            i = 0;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut4_1) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut4_2) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut4_3) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut4_4) == TRUE) {
                    break;
                }
                i++;
            }
            break;
        default:
            return EVT_RETURN_DONE;
        }
    }
    moving = FALSE;
    for (i = 0; i < 4; i++) {
        if (battenSatelliteTo_Main(unit, i) == TRUE) {
            moving = TRUE;
        }
    }
    return moving == FALSE ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
