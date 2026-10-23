#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "driver/camdrv.h"
#include "battle/battle_unit.h"
#include "driver/dispdrv.h"
#include "dolphin/mtx.h"

typedef struct AtmTeresa { u8 state; u8 flag; s32 anim; s32 wait; s32 timer; Vec vel; Vec start; Vec target; u8 mode; } AtmTeresa;
AtmTeresa* teresa;
#define ATMIC_TERESA_SCALE atmic_teresa_scale
s32 extGetPoseNum(void);
void extLoadRenderMode(void);
void extLoadVertex(void);
void extLoadTexture(void);
void extLoadTev(void);
void extDraw(void);
void extLoadTextureExit(void);
typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
s32 teresa_count;
ExtPose* extGetPosePtr(void);
s32 BtlUnit_snd_se_pos(BattleUnit* unit, const char* name, u32 flags, s32 arg3, Vec* pos);
s32 irand(s32 scalar);
f32 intplGetValue(s32 mode, f32 start, f32 end, s32 cur, s32 steps);
s32 irand(s32 scalar);
f32 intplGetValue(s32 mode, f32 start, f32 end, s32 cur, s32 steps);
double cos(double x);
double sin(double x);
void teresa_ext_disp(CameraId camera, void* param);

USER_FUNC(atmic_teresa_id_set);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_PreCheckDamage);
USER_FUNC(btlevtcmd_ResultACDefence);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_ext_entry);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_sub_random);
USER_FUNC(teresa_wait_breath2);
USER_FUNC(teresa_wait_breath);
USER_FUNC(teresa_appear_breath);
USER_FUNC(teresa_wait_bikkuri2);
USER_FUNC(teresa_wait_bikkuri);
USER_FUNC(teresa_appear_bikkuri);
USER_FUNC(target_id_set);
void teresa_ext_disp(CameraId camera, void* param);
void teresa_ext_main(void);
void teresa_ext_init(void);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddPartsRotate[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_AnimeSetPoseTable[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetPartsRotate[];
extern s32 btlevtcmd_SetScale[];
extern s32 btlevtcmd_SetUnitWork[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_btl_camera_shake_w[];
extern s32 evt_eff[];
extern s32 evt_snd_sfxoff[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_atmic_teresa_negone_one_374;
__declspec(section ".data") s32 fd_atmic_teresa_neg_one_382[1];
__declspec(section ".data") s32 fd_atmic_teresa___local_PI_383[1];
__declspec(section ".data") s32 fd_atmic_teresa___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_atmic_teresa_one_negone_373;
__declspec(section ".data") s32 fd_atmic_teresa___local_PIO2_384[1];
__declspec(section ".data") s32 fd_atmic_teresa_one_381[1];
__declspec(section ".data") u64 fd_atmic_teresa_negone_one_360;
__declspec(section ".data") s32 fd_atmic_teresa_neg_one_365[1];
__declspec(section ".data") s32 fd_atmic_teresa___local_PI_366[1];
__declspec(section ".data") s32 fd_atmic_teresa___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_atmic_teresa_one_negone_359;
__declspec(section ".data") s32 fd_atmic_teresa___local_PIO2_367[1];
__declspec(section ".data") s32 fd_atmic_teresa_one_364[1];
BattleUnitKind unit_atmic_teresa;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static PoseTableEntry pose_table[17];
PoseTableEntry pose_table_kaokakusi[17];
static __declspec(section ".data") BattleDataEntry data_table[1];
static BattleUnitKindPart parts[1];
static __declspec(section ".data") StatusVulnerability regist;
s32 weapon_atmic_teresa_press[48];
s32 weapon_atmic_teresa_bikkuri[48];
s32 weapon_atmic_teresa_surprise[48];
s32 weapon_atmic_teresa_breath[48];
static s32 init_event[26];
static __declspec(section ".data") s32 damage_event[10];
static s32 attack_event[101];
s32 kaokakusi_event[110];
s32 press_event[264];
s32 surprise_event[303];
s32 bikkuri_event[285];
static s32 breath_event[254];
s32 breath_event_sub[102];
static __declspec(section ".data") s32 wait_event[6];
__declspec(section ".data") s32 atmic_teresa_id[1];
__declspec(section ".data") s32 target_unit_id[1];
__declspec(section ".data") s32 target_parts_id[1];
__declspec(section ".data") f32 atmic_teresa_scale;
s32 teresa_ext_entry_data[51];
s32 teresa_entry[19];

__declspec(section ".data") u64 fd_atmic_teresa_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_atmic_teresa_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_atmic_teresa___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_atmic_teresa___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_atmic_teresa_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_atmic_teresa___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_atmic_teresa_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_atmic_teresa_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_atmic_teresa_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_atmic_teresa___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_atmic_teresa___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_atmic_teresa_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_atmic_teresa___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_atmic_teresa_one_364[] = {
    1065353216,
};

BattleUnitKind unit_atmic_teresa = {
    76,
    "btl_un_atmic_teresa",
    40,
    0,
    1,
    1,
    52,
    0,
    1,
    100,
    0,
    50,
#ifdef VERSION_G8ME01
    6,
#else
    9999,
#endif
    120,
    110,
    30,
    105,
    0.0f,
    55.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    60.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    60.0f,
    0.0f,
    0.0f,
    46.0f,
    71.5f,
    10.0f,
    0.0f,
    55.0f,
    0.0f,
    120.0f,
    110.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_ATMTLSA_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "S_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "S_1"},
    {39, "D_1"},
    {42, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_1"},
};

PoseTableEntry pose_table_kaokakusi[] = {
    {1, "A_1"},
    {2, "A_1"},
    {9, "A_1"},
    {5, "A_1"},
    {4, "A_1"},
    {3, "A_1"},
    {28, "A_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "A_1"},
    {39, "D_1"},
    {42, "A_1"},
    {40, "A_1"},
    {56, "A_1"},
    {57, "A_1"},
    {65, "T_1"},
    {69, "A_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_atmic_teresa", "c_atmic_trs", 0.0f, 0.0f, 0.0f, 10.0f, 80.0f, 0.0f, 0.0f, 110.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x600009, 0, pose_table},
};

static __declspec(section ".data") StatusVulnerability regist = {40, 40, 40, 100, 40, 100, 100, 30, 0, 0, 100, 0, 100, 80, 40, 0, 10, 100, 40, 100, 100, 5};

s32 weapon_atmic_teresa_press[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 4231, 108, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 3289700, 0, 0,
};

s32 weapon_atmic_teresa_bikkuri[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 71, 2047, 0,
    12803, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_atmic_teresa_surprise[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 103, 2047, 0,
    0, 0, 3277568, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_atmic_teresa_breath[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 151, 2047, -2147483644,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(atmic_teresa_id_set, -2)
    CALL_CHILD(PTR(teresa_entry))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        SET_VALUE(LW(1), 30)
        ADD(LW(1), 20)
        ADD(LW(1), 20)
        SUBTRACT(LW(1), 1)
        CALL(evt_sub_random, LW(1), LW(0))
        SET_VALUE(LW(1), 30)
        IF_INT_LESS(LW(0), LW(1))
            CALL_CHILD(PTR(kaokakusi_event))
            GOTO(99)
        END_IF
        ADD(LW(1), 20)
        IF_INT_LESS(LW(0), LW(1))
            CALL_CHILD(PTR(press_event))
            GOTO(99)
        END_IF
        CALL_CHILD(PTR(bikkuri_event))
        GOTO(99)
        ELSE
        SET_VALUE(LW(1), 50)
        ADD(LW(1), 50)
        SUBTRACT(LW(1), 1)
        CALL(evt_sub_random, LW(1), LW(0))
        SET_VALUE(LW(1), 50)
        IF_INT_LESS(LW(0), LW(1))
            CALL_CHILD(PTR(surprise_event))
            GOTO(99)
        END_IF
        CALL_CHILD(PTR(breath_event))
        GOTO(99)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 kaokakusi_event[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_ATMTLSA_MOVE2",
    -250000000, 0, -29999985, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -2, -30000000, 60, 131126, -29999999, 10, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 60, 10, 4, 0,
    -1, 65545, 20, 131163, (s32)evt_snd_sfxoff, -29999985, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_ATMTLSA_FACE_HIDE1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"A_1", 393307, (s32)btlevtcmd_SetPartsRotate, -2, 1, 0, 180,
    0, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 655451,
    (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 20, 0, 5,
    0, -1, 65545, 10, 65541, 15, 65545, 1,
    393307, (s32)btlevtcmd_AddPartsRotate, -2, 1, 0, 12, 0, 6,
    65545, 20, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 1, 262235,
    (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table_kaokakusi, 2, 1,
};

s32 press_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_atmic_teresa_press, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_atmic_teresa_press, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_atmic_teresa_press, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_atmic_teresa_press, 196699, (s32)evt_btl_camera_set_mode, 0, 7,
    262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_ATMTLSA_MOVE2", -250000000, 0, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"R_1", 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    131126, -29999998, 10, 655451, (s32)btlevtcmd_DivePosition, -2, -125, 100,
    -29999998, 120, 10, 4, 0, -1, 131163, (s32)evt_snd_sfxoff,
    -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"Z_1", 655451, (s32)btlevtcmd_DivePosition,
    -2, -125, 0, -29999998, 30, 0, 1, 0,
    -1, 393307, (s32)evt_btl_camera_shake_h, 0, 10, 0, 60, 0,
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131122, -29999990, 0, 65539,
    0, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_atmic_teresa_press, 0,
    -29999995, 65570, -29999995, 65579, 4, 65540, 90, 46,
    65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90,
    46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540,
    90, 46, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    65540, 90, 65572, 1, 65540, 91, 46, 42,
    65540, 98, 46, 49, 65539, 90, 65540, 97,
    65539, 91, 131096, -29999990, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    (s32)weapon_atmic_teresa_press, 33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_atmic_teresa_press,
    256, -29999995, 65540, 97, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy,
    -29999997, -29999996, 131097, -29999997, -1, 131125, -29999990, 1,
    65540, 0, 33, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65539,
    98, 65545, 60, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"W_1", 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    60, 50, 6, 0, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"S_1", 65546, 250, 65539, 99, 2, 1,
};

s32 surprise_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_atmic_teresa_surprise, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_atmic_teresa_surprise, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_atmic_teresa_surprise, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_atmic_teresa_surprise, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_ATMTLSA_FACE_HIDE1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40,
    393307, (s32)btlevtcmd_SetPartsRotate, -2, 1, 0, 180, 0, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 30, 131126, -29999999, 10, 655451, (s32)btlevtcmd_DivePosition, -2,
    -30000000, -29999999, -29999998, 60, 10, 4, 0, -1,
    196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 0, 262235, (s32)btlevtcmd_AnimeSetPoseTable,
    -2, 1, (s32)pose_table, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2",
    393307, (s32)btlevtcmd_SetPartsRotate, -2, 1, 0, 0, 0, 655451,
    (s32)btlevtcmd_DivePosition, -2, 0, -29999999, -29999998, 10, 0, 5,
    0, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_ATMTLSA_SURPRISED1", -250000000, 0,
    -250000000, 393307, (s32)evt_btl_camera_shake_w, 0, 10, 0, 60, 0,
    393307, (s32)evt_btl_camera_shake_h, 0, 10, 0, 60, 4, 196699,
    (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131122, -29999990, 0, 65539, 0,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_atmic_teresa_surprise, 0, -29999995,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    46, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540,
    90, 65572, 1, 65540, 91, 46, 42, 65540,
    98, 46, 49, 65539, 90, 65540, 97, 65539,
    91, 131096, -29999990, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_atmic_teresa_surprise,
    33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_atmic_teresa_surprise, 256,
    -29999995, 65540, 97, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997,
    -29999996, 131097, -29999997, -1, 131125, -29999990, 1, 65540,
    0, 33, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65539, 98,
    65545, 90, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"W_1", 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 60,
    -20, 6, 0, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"S_1", 65546, 250, 65539, 99, 2, 1,
};

s32 bikkuri_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_atmic_teresa_bikkuri, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_atmic_teresa_bikkuri, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_atmic_teresa_bikkuri, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_atmic_teresa_press, 65627, (s32)teresa_appear_bikkuri, 65545, 75,
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -29999997,
    -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 5, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 65545, 20, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_ATMTLSA_S_ROUND1", -250000000,
    0, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 65627,
    (s32)teresa_wait_bikkuri, 131163, (s32)evt_snd_sfxoff, -29999985, 65545, 30, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_ATMTLSA_SURPRISED2", -250000000, 0, -250000000, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 350, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997,
    -29999996, 131122, -29999990, 0, 65539, 0, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, (s32)weapon_atmic_teresa_bikkuri, 0, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 49,
    65539, 90, 65540, 97, 65539, 91, 131096, -29999990,
    0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_atmic_teresa_bikkuri, 33, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -29999997, -29999996, (s32)weapon_atmic_teresa_bikkuri, 256, -29999995, 65540, 97,
    65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131097, -29999997,
    -1, 131125, -29999990, 1, 65540, 0, 33, 65539,
    98, 65545, 30, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65545,
    60, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_ATMTLSA_WHISTLE1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_4", 65545, 30, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 65627, (s32)teresa_wait_bikkuri2, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_ATMTLSA_UNION1", -250000000, 0, -29999985, 65541, 3, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -29999999, 40,
    131125, -29999998, 1, 983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test", 8,
    -30000000, -29999999, -29999998, -229998720, 0, 0, 0, 0,
    0, 0, 0, 65545, 30, 6, 131163, (s32)evt_snd_sfxoff,
    -29999985, 65546, 250, 327771, (s32)btlevtcmd_SetScale, -2, -229998976, -229998976,
    -229998976, 65539, 99, 2, 1,
};

static s32 breath_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_atmic_teresa_breath, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_atmic_teresa_breath, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    196699, (s32)target_id_set, -29999997, -29999996, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_atmic_teresa_breath, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, (s32)weapon_atmic_teresa_breath, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_ATMTLSA_FACE_HIDE1", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 393307, (s32)btlevtcmd_SetPartsRotate,
    -2, 1, 0, 180, 0, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 30,
    131126, -29999999, 10, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, 60, 10, 4, 0, -1, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 0, 262235,
    (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_3", 393307, (s32)btlevtcmd_SetPartsRotate, -2, 1, 0, 0, 0,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 10, 0, 5, 0,
    -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_ATMTLSA_BLOW2", -250000000, 0, -29999985,
    131163, (s32)teresa_appear_breath, 0, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 65539,
    10, 131096, -29999997, -1, 65540, 20, 33, 65628,
    (s32)breath_event_sub, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 65540, 10, 65539,
    20, 65545, 120, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65627,
    (s32)teresa_wait_breath, 131163, (s32)evt_snd_sfxoff, -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_ATMTLSA_WHISTLE1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_4",
    65545, 30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 65627,
    (s32)teresa_wait_breath2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_ATMTLSA_UNION1", -250000000, 0, -29999985,
    65541, 3, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    131125, -29999999, 40, 131125, -29999998, 1, 983131, (s32)evt_eff,
    (s32)"", (s32)"kemuri_test", 8, -30000000, -29999999, -29999998, -229998720, 0,
    0, 0, 0, 0, 0, 0, 65545, 30,
    6, 131163, (s32)evt_snd_sfxoff, -29999985, 65546, 1500, 327771, (s32)btlevtcmd_SetScale,
    -2, -229998976, -229998976, -229998976, 2, 1,
};

EVT_BEGIN(breath_event_sub)
    CALL(btlevtcmd_PreCheckDamage, -2, LW(3), LW(4), PTR(weapon_atmic_teresa_breath), 0, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(90)
        CASE_END
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(90)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(90)
        CASE_EQUAL(1)
        GOTO(91)
        CASE_END
        CASE_DEFAULT
        GOTO(98)
        CASE_END
    END_SWITCH
    LABEL(90)
    GOTO(99)
    LABEL(91)
    WAIT_FRAMES(15)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(weapon_atmic_teresa_breath))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), PTR(weapon_atmic_teresa_breath), 0, LW(5))
    WAIT_FRAMES(30)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(weapon_atmic_teresa_breath))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), PTR(weapon_atmic_teresa_breath), 0, LW(5))
    WAIT_FRAMES(30)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(weapon_atmic_teresa_breath))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), PTR(weapon_atmic_teresa_breath), 256, LW(5))
    LABEL(99)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

__declspec(section ".data") s32 atmic_teresa_id[] = {
    -1,
};

__declspec(section ".data") s32 target_unit_id[] = {
    -1,
};

__declspec(section ".data") s32 target_parts_id[] = {
    -1,
};

__declspec(section ".data") f32 atmic_teresa_scale = 1.0f;

s32 teresa_ext_entry_data[] = {
    (s32)"c_teresa", (s32)"S_1", 0, (s32)"c_teresa", (s32)"S_1", 1073741824, (s32)"c_teresa", (s32)"S_1",
    1082130432, (s32)"c_teresa", (s32)"S_1", 1086324736, (s32)"c_teresa", (s32)"S_1", 1090519040, (s32)"c_teresa",
    (s32)"S_1", 1092616192, (s32)"c_teresa", (s32)"S_1", 1086324736, (s32)"c_teresa", (s32)"S_1", 1088421888,
    (s32)"c_teresa", (s32)"A_1", 0, (s32)"c_teresa", (s32)"A_2", 1086324736, (s32)"c_teresa", (s32)"A_2",
    1088421888, (s32)"c_teresa", (s32)"A_2", 1090519040, (s32)"c_teresa", (s32)"A_2", 1091567616, (s32)"c_teresa",
    (s32)"A_2", 1092616192, (s32)"c_teresa", (s32)"A_2", 1093664768, (s32)"c_teresa", (s32)"A_2", 1094713344,
    0, 0, 0,
};

EVT_BEGIN(teresa_entry)
    CALL(evt_npc_entry, STRING("ext_teresa"), STRING("c_teresa"))
    CALL(evt_npc_set_position, STRING("ext_teresa"), 0, -1000, 0)
    CALL(evt_ext_entry, 30, PTR(teresa_ext_entry_data), PTR(teresa_ext_init), PTR(teresa_ext_main), 0)
    RETURN
EVT_END()

void teresa_ext_init(void) {
    s32 i;
    ExtPose* pose = extGetPosePtr();

    teresa = BattleAlloc(sizeof(AtmTeresa) * 30);
    for (i = 0; i < extGetPoseNum(); i++, pose++) {
        pose->flags = 1;
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = 0.0f;
        pose->mtx[1][3] = -1000.0f;
        pose->mtx[2][3] = 0.0f;
        pose->rot = 90.0f;
        teresa[i].state = 0;
        teresa[i].flag = 0;
        teresa[i].anim = 0;
        {
            Vec zero = {0.0f, 0.0f, 0.0f};
            teresa[i].vel = zero;
        }
    }
}

void teresa_ext_main(void) {
    s32 i;
    s32 j;
    ExtPose* pose = extGetPosePtr();
    AtmTeresa* t;
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, atmic_teresa_id[0]);
    BattleUnit* target = BattleGetUnitPtr(_battleWorkPointer, target_unit_id[0]);
    s32 n;
    f32 angle;
    s32 waits[8] = {0, 2, 5, 7, 10, 12, 15, 17};
    f32 ofs[30][2] = {
        {-30.0f, 8.0f}, {-28.0f, 10.0f}, {-26.0f, 6.0f}, {-24.0f, 30.0f}, {-22.0f, 16.0f},
        {-20.0f, 50.0f}, {-18.0f, 14.0f}, {-16.0f, 18.0f}, {-14.0f, 60.0f}, {-12.0f, 34.0f},
        {-10.0f, 66.0f}, {-8.0f, 8.0f}, {-6.0f, 28.0f}, {-4.0f, 40.0f}, {-2.0f, 46.0f},
        {0.0f, 20.0f}, {2.0f, 26.0f}, {4.0f, 52.0f}, {6.0f, 74.0f}, {8.0f, 68.0f},
        {10.0f, 0.0f}, {12.0f, 28.0f}, {14.0f, 44.0f}, {16.0f, 72.0f}, {18.0f, 42.0f},
        {20.0f, 76.0f}, {22.0f, 56.0f}, {24.0f, 32.0f}, {26.0f, 4.0f}, {28.0f, 2.0f},
    };
    u8 modes[7] = {0, 1, 2, 3, 4, 5, 6};
    f32 x, y, z;
    f32 hx, hy, hz;
    f32 sx, sy, sz;

    if (++teresa_count >= 360) {
        teresa_count -= 360;
    }
    if (unit != NULL) {
        BtlUnit_GetPos(unit, &x, &y, &z);
        y += 40.0f;
        BtlUnit_GetScale(unit, &sx, &sy, &sz);
        if (sx > ATMIC_TERESA_SCALE) {
            sx -= 0.005f;
            if (sx <= ATMIC_TERESA_SCALE) {
                sx = ATMIC_TERESA_SCALE;
            }
            BtlUnit_SetScale(unit, sx, sx, sz);
        }
        if (sx < ATMIC_TERESA_SCALE) {
            sx += 0.005f;
            if (sx >= ATMIC_TERESA_SCALE) {
                sx = ATMIC_TERESA_SCALE;
            }
            BtlUnit_SetScale(unit, sx, sx, sz);
        }
    }
    if (target != NULL) {
        BattleUnitPart* part = BtlUnit_GetPartsPtr(target, target_parts_id[0]);
        BtlUnit_GetHitPos(target, part, &hx, &hy, &hz);
    }

    for (i = 0; i < extGetPoseNum(); i++, pose++) {
        t = &teresa[i];
        switch (t->flag) {
            case 1:
                t->anim++;
                if (t->anim <= 30) {
                    pose->frame = 8;
                } else if (t->anim < 44) {
                    pose->frame = (t->anim - 30) / 2 + 9;
                } else {
                    pose->frame = 15;
                }
                break;
            default:
                t->anim++;
                if (t->anim >= 24) {
                    t->anim -= 24;
                }
                pose->frame = t->anim / 3;
                break;
        }
        if (t->wait >= 1) {
            t->wait--;
            continue;
        }
        pose->mtx[0][3] += t->vel.x;
        pose->mtx[1][3] += t->vel.y;
        pose->mtx[2][3] += t->vel.z;
        if (pose->mtx[1][3] < 0.0f) {
            pose->mtx[1][3] = 0.0f;
        }

        switch (t->state) {
            case 0:
                pose->mtx[0][3] = 0.0f;
                pose->mtx[1][3] = -1000.0f;
                pose->mtx[2][3] = 0.0f;
                pose->rot = 90.0f;
                pose->mtx[1][1] = 1.0f;
                pose->mtx[0][0] = 1.0f;
                break;
            case 1:
                pose->flags &= ~2;
                pose->mtx[0][3] = x;
                pose->mtx[1][3] = y;
                pose->mtx[2][3] = z - 5.0f;
                pose->mtx[0][0] = 0.0f;
                pose->mtx[1][1] = 0.0f;
                angle = 0.785398f * i;
                t->vel.x = 2.0f * (f32)cos(angle);
                t->vel.y = 2.0f * (f32)sin(angle);
                t->vel.z = 0.0f;
                t->wait = waits[i];
                t->timer = 50;
                t->state = 5;
                break;
            case 5:
                t->timer--;
                if (t->timer == 25) {
                    ATMIC_TERESA_SCALE -= 0.05f;
                    if (i % 2 == 0) {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        pos.x = pose->mtx[0][3];
                        pos.y = pose->mtx[1][3];
                        pos.z = pose->mtx[2][3];
                        BtlUnit_snd_se_pos(unit, "SFX_BOSS_ATMTLSA_DIVIDE1", 0xF1194D80, 0, &pos);
                    }
                }
                pose->mtx[0][0] += 0.02f;
                pose->mtx[1][1] += 0.02f;
                if (t->timer <= 0) {
                    pose->flags |= 2;
                    t->state = 10;
                    t->timer = 150;
                    t->vel.x = 0.0f;
                    t->vel.y = 0.0f;
                    t->vel.z = 0.0f;
                    if (i % 2 == 0) {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        pos.x = pose->mtx[0][3];
                        pos.y = pose->mtx[1][3];
                        pos.z = pose->mtx[2][3];
                        BtlUnit_snd_se_pos(unit, "SFX_BOSS_ATMTLSA_S_MOVE1", 0xF1194D80, 0, &pos);
                    }
                }
                break;
            case 10:
                angle = 6.283184f * (0.125f * i + 2.0f * teresa_count / 360.0f);
                t->target.x = 90.0f * (f32)cos(angle) - 100.0f;
                t->target.y = 10.0f;
                t->target.z = 90.0f * (f32)sin(angle);
                if (pose->mtx[0][3] >= -100.0f) {
                    pose->rot = 90.0f;
                } else {
                    pose->rot = 270.0f;
                }
                t->vel.x = (t->target.x - pose->mtx[0][3]) / 20.0f;
                t->vel.y = (t->target.y - pose->mtx[1][3]) / 20.0f;
                t->vel.z = (t->target.z - pose->mtx[2][3]) / 20.0f;
                if (t->timer <= 0) {
                    t->state = 15;
                    t->vel.x = 0.0f;
                    t->vel.y = 0.0f;
                    t->vel.z = 0.0f;
                }
                t->timer--;
                break;
            case 15:
                angle = 6.283184f * (0.125f * i + 2.0f * teresa_count / 360.0f);
                t->target.x = 90.0f * (f32)cos(angle) - 100.0f;
                t->target.y = 10.0f;
                t->target.z = 90.0f * (f32)sin(angle);
                if (pose->mtx[0][3] >= -100.0f) {
                    pose->rot = 90.0f;
                } else {
                    pose->rot = 270.0f;
                }
                t->vel.x = (t->target.x - pose->mtx[0][3]) / 20.0f;
                t->vel.y = (t->target.y - pose->mtx[1][3]) / 20.0f;
                t->vel.z = (t->target.z - pose->mtx[2][3]) / 20.0f;
                n = 0;
                for (j = 0; j < 8; j++) {
                    if (teresa[j].state != 15) {
                        break;
                    }
                    n++;
                }
                if (n == 8) {
                    for (j = 0; j < 8; j++) {
                        AtmTeresa* p = &teresa[j];
                        p->state = 20;
                        p->flag = 1;
                        p->anim = 0;
                        p->vel.x = 0.0f;
                        p->vel.y = 0.0f;
                        p->vel.z = 0.0f;
                    }
                }
                break;
            case 20:
                if (t->anim >= 180) {
                    t->state = 23;
                    t->flag = 0;
                    t->anim = 0;
                    t->timer = 60;
                    t->wait = waits[i];
                    pose->rot = 90.0f;
                }
                break;
            case 23:
                t->target.x = (x - 35.0f) + irand(90);
                t->target.y = (y - 35.0f) + irand(90);
                t->target.z = (z - 30.0f) - 0.05f * i;
                t->timer = 60;
                t->state = 25;
                if (i % 2 == 0) {
                    Vec pos = {0.0f, 0.0f, 0.0f};
                    pos.x = pose->mtx[0][3];
                    pos.y = pose->mtx[1][3];
                    pos.z = pose->mtx[2][3];
                    BtlUnit_snd_se_pos(unit, "SFX_BOSS_ATMTLSA_S_MOVE1", 0xF1194D80, 0, &pos);
                }
                break;
            case 25:
                t->vel.x = (t->target.x - pose->mtx[0][3]) / 20.0f;
                t->vel.y = (t->target.y - pose->mtx[1][3]) / 20.0f;
                t->vel.z = (t->target.z - pose->mtx[2][3]) / 20.0f;
                if (t->timer <= 0) {
                    t->state = 30;
                    t->vel.x = 0.0f;
                    t->vel.y = 0.0f;
                    t->vel.z = 0.0f;
                    pose->flags &= ~2;
                }
                t->timer--;
                break;
            case 31:
                pose->mtx[0][0] -= 0.0125f;
                pose->mtx[1][1] = pose->mtx[0][0];
                if (pose->mtx[0][0] <= 0.0f) {
                    t->state = 0;
                }
                break;
            case 51:
            case 52:
                pose->flags &= ~2;
                pose->mtx[0][3] = x - 15.0f;
                pose->mtx[1][3] = y - 5.0f;
                pose->mtx[2][3] = 5.0f + z;
                pose->mtx[1][1] = 0.0f;
                pose->mtx[0][0] = 0.0f;
                t->vel.x = 0.0f;
                t->vel.y = 0.0f;
                t->vel.z = 0.0f;
                t->start.x = pose->mtx[0][3];
                t->start.y = pose->mtx[1][3];
                t->start.z = pose->mtx[2][3];
                if (t->state == 51) {
                    t->target.x = (hx + ofs[i][0]) - 200.0f;
                } else {
                    t->target.x = (hx + ofs[i][0]) - 200.0f;
                }
                if (t->state == 51) {
                    t->target.y = (hy + ofs[i][1]) - 50.0f;
                } else {
                    t->target.y = (hy + ofs[i][1]) - 50.0f;
                }
                t->target.z = (hz - 10.0f) - 0.05f * i;
                t->wait = i * 3;
                t->timer = 0;
                t->state = 53;
                t->mode = modes[irand(7)];
                break;
            case 53:
                ATMIC_TERESA_SCALE -= 0.015f;
                t->state = 55;
                break;
            case 55:
                pose->mtx[0][0] += 0.04f;
                if (pose->mtx[0][0] >= 1.0f) {
                    pose->mtx[0][0] = 1.0f;
                }
                pose->mtx[1][1] = pose->mtx[0][0];
                pose->mtx[0][3] = intplGetValue(t->mode, t->start.x, t->target.x, t->timer, 30);
                pose->mtx[1][3] = intplGetValue(t->mode, t->start.y, t->target.y, t->timer, 30);
                pose->mtx[2][3] = intplGetValue(t->mode, t->start.z, t->target.z, t->timer, 30);
                if (t->timer >= 30) {
                    t->state = 60;
                }
                t->timer++;
                break;
            case 63:
                t->target.x = (x - 35.0f) + irand(90);
                t->target.y = (y - 35.0f) + irand(90);
                t->target.z = (z - 30.0f) - 0.05f * i;
                t->timer = 60;
                t->state = 65;
                if (i % 2 == 0) {
                    Vec pos = {0.0f, 0.0f, 0.0f};
                    pos.x = pose->mtx[0][3];
                    pos.y = pose->mtx[1][3];
                    pos.z = pose->mtx[2][3];
                    BtlUnit_snd_se_pos(unit, "SFX_BOSS_ATMTLSA_S_MOVE1", 0xF1194D80, 0, &pos);
                }
                break;
            case 65:
                t->vel.x = (t->target.x - pose->mtx[0][3]) / 15.0f;
                t->vel.y = (t->target.y - pose->mtx[1][3]) / 15.0f;
                t->vel.z = (t->target.z - pose->mtx[2][3]) / 15.0f;
                if (t->timer <= 0) {
                    t->state = 70;
                    t->vel.x = 0.0f;
                    t->vel.y = 0.0f;
                    t->vel.z = 0.0f;
                }
                t->timer--;
                break;
            case 71:
                pose->mtx[0][0] -= 0.0125f;
                pose->mtx[1][1] = pose->mtx[0][0];
                if (pose->mtx[0][0] <= 0.0f) {
                    t->state = 0;
                }
                break;
        }
    }
    dispEntry(4, 0.0f, 1, teresa_ext_disp, NULL);
}

void teresa_ext_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}

USER_FUNC(atmic_teresa_id_set) {
    s32 id = evtGetValue(event, event->args[0]);

    atmic_teresa_id[0] = BattleTransID(event, id);
    return EVT_RETURN_DONE;
}

USER_FUNC(target_id_set) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 parts = evtGetValue(event, args[1]);

    target_unit_id[0] = BattleTransID(event, id);
    target_parts_id[0] = parts;
    return EVT_RETURN_DONE;
}

USER_FUNC(teresa_appear_bikkuri) {
    s32 i;

    for (i = 0; i < 8; i++) {
        teresa[i].state = 1;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(teresa_wait_bikkuri) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (teresa[i].state != 15) {
            return EVT_RETURN_BLOCK;
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(teresa_wait_bikkuri2) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (teresa[i].state != 30) {
            return EVT_RETURN_BLOCK;
        }
    }
    for (i = 0; i < 8; i++) {
        teresa[i].state = 31;
    }
    ATMIC_TERESA_SCALE = 1.0f;
    return EVT_RETURN_DONE;
}

USER_FUNC(teresa_appear_breath) {
    s32 type = evtGetValue(event, event->args[0]);
    s32 i;
    s32 state = (type == 1) ? 51 : 52;

    for (i = 0; i < extGetPoseNum(); i++) {
        teresa[i].state = state;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(teresa_wait_breath) {
    s32 i;

    for (i = 0; i < 30; i++) {
        if (teresa[i].state != 60) {
            return EVT_RETURN_BLOCK;
        }
    }
    for (i = 0; i < 30; i++) {
        AtmTeresa* t = &teresa[i];
        t->state = 63;
        t->wait = 30;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(teresa_wait_breath2) {
    s32 i;

    for (i = 0; i < 30; i++) {
        if (teresa[i].state != 70) {
            return EVT_RETURN_BLOCK;
        }
    }
    for (i = 0; i < 30; i++) {
        teresa[i].state = 71;
    }
    ATMIC_TERESA_SCALE = 1.0f;
    return EVT_RETURN_DONE;
}
