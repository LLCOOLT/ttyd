#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHpGaugeOffset);
USER_FUNC(btlevtcmd_StartWaitEvent);
extern s32 boss_moamoa_check_zenei_kouei[];
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeSetPoseTable[];
extern s32 btlevtcmd_AnimeWaitPlayComplete[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetHitCursorOffset[];
extern s32 btlevtcmd_SetHitOffset[];
extern s32 btlevtcmd_SetPartsDefenceTable[];
extern s32 btlevtcmd_SetUnitWork[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_snd_sfxoff[];
extern s32 moamoa1_weakness_pose_table[];
extern s32 moamoa_defence_no_parts[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_boss_moamoa_tentacle_c_negone_one_374;
__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_moamoa_tentacle_c_one_negone_373;
__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c_one_381[1];
__declspec(section ".data") u64 fd_boss_moamoa_tentacle_c_negone_one_360;
__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_moamoa_tentacle_c_one_negone_359;
__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c_one_364[1];
BattleUnitKind unit_boss_moamoa_tentacle_c;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") PoseTableEntry pose_table[4];
static __declspec(section ".data") BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
static s32 weapon_moamoa_attack[48];
static s32 init_event[26];
static __declspec(section ".data") s32 damage_event[10];
static s32 dead_event[115];
static __declspec(section ".data") s32 phase_event[2];
static s32 attack_event[21];
static s32 evt_attack_other_arm[81];
__declspec(section ".data") s32 A_of_C_Attack[3];
__declspec(section ".data") s32 B_of_C_Attack[3];
__declspec(section ".data") s32 C_of_C_Attack_front[8];
__declspec(section ".data") s32 C_of_C_Attack_back[8];
static s32 evt_attack[387];
static s32 wait_event[32];

__declspec(section ".data") u64 fd_boss_moamoa_tentacle_c_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_moamoa_tentacle_c_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_moamoa_tentacle_c_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_moamoa_tentacle_c_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_moamoa_tentacle_c_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_moamoa_tentacle_c = {
    108,
    "btl_un_moamoa_tentacle_a",
    4,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    10,
    110,
    70,
    -50,
    70,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    280.0f,
    40.0f,
    0.0f,
    55.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    55.0f,
    0.0f,
    0.0f,
    55.0f,
    45.5f,
    20.0f,
    -90.0f,
    100.0f,
    0.0f,
    110.0f,
    70.0f,
    0,
    0,
    -1,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_MOA_G_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x200000,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static __declspec(section ".data") PoseTableEntry pose_table[] = {
    {28, "S_1C_1"},
    {31, "D_1C_1"},
    {39, "D_1C_1"},
    {69, "S_1C_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_moamoa_tentacle_c", "c_g_moamoa_b", 0.0f, 0.0f, 0.0f, 88.0f, 88.0f, 10.0f, 93.0f, 93.0f, 10.0f, 20, 30, 255, &defence, &defence_attr, 0x600001, 0, pose_table},
};

static s32 weapon_moamoa_attack[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetHpGaugeOffset, -2, -56, 63)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static s32 dead_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_ARM_DOWN1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"R_1C", 65545, 1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete,
    -2, 1, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -29999999, 262235,
    (s32)btlevtcmd_SetUnitWork, -29999999, 3, -1, 262235, (s32)btlevtcmd_GetUnitWork, -29999999, 5,
    -30000000, 131096, -30000000, -1, 262235, (s32)btlevtcmd_GetUnitWork, -29999999, 4,
    -30000000, 131096, -30000000, -1, 262235, (s32)btlevtcmd_GetUnitWork, -29999999, 3,
    -30000000, 131096, -30000000, -1, 262235, (s32)btlevtcmd_SetPartsDefenceTable, -29999999, 1,
    (s32)moamoa_defence_no_parts, 262235, (s32)btlevtcmd_OffPartsAttribute, -29999999, 1, 536870912, 262235, (s32)btlevtcmd_AnimeSetPoseTable,
    -29999999, 1, (s32)moamoa1_weakness_pose_table, 393307, (s32)btlevtcmd_SetHitOffset, -29999999, 1, 0,
    32, 0, 393307, (s32)btlevtcmd_SetHitCursorOffset, -29999999, 1, 0, 41,
    0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_BIG1", -250000000, 0, -250000000,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_BIG2", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -29999999, 1, (s32)"V_1", 65545, 1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete,
    -29999999, 1, 33, 33, 33, 196699, (s32)btlevtcmd_KillUnit, -2,
    0, 2, 1,
};

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
    CALL_CHILD(PTR(evt_attack))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 evt_attack_other_arm[] = {
    65598, -29999999, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_ARM_MOVE1", -250000000, 0,
    -29999985, 65541, 0, 65599, -29999998, 131096, -29999998, 0,
    7, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -30000000, -29999995, -29999998, 65545,
    1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -30000000, -29999995, 6, 131163, (s32)evt_snd_sfxoff,
    -29999985, 65541, 0, 262235, (s32)btlevtcmd_GetUnitWork, -29999994, 0, -29999990,
    131097, -29999990, 0, 7, 33, 65545, 1, 6,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_ARM_MOVE1", -250000000, 0, -29999985, 65541,
    0, 65599, -29999998, 131096, -29999998, 0, 7, 33,
    262235, (s32)btlevtcmd_AnimeChangePose, -30000000, -29999995, -29999998, 65545, 1, 196699,
    (s32)btlevtcmd_AnimeWaitPlayComplete, -30000000, -29999995, 6, 131163, (s32)evt_snd_sfxoff, -29999985, 2,
    1,
};

__declspec(section ".data") s32 A_of_C_Attack[] = {
    (s32)"S_1A_1", 0, 0,
};

__declspec(section ".data") s32 B_of_C_Attack[] = {
    (s32)"S_1B_1", 0, 0,
};

__declspec(section ".data") s32 C_of_C_Attack_front[] = {
    (s32)"A_1C_1", (s32)"A_1C_2", 0, (s32)"A_1C_3", 0, (s32)"A_1C_4", (s32)"S_1C_1", 0,
};

__declspec(section ".data") s32 C_of_C_Attack_back[] = {
    (s32)"A_1C_5", (s32)"A_1C_6", 0, (s32)"A_1C_7", 0, (s32)"A_1C_8", (s32)"S_1C_1", 0,
};

static s32 evt_attack[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_moamoa_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_moamoa_attack, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 2, 33, 196699,
    (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 100,
    131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_moamoa_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996,
    65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_moamoa_attack, 196699, (s32)boss_moamoa_check_zenei_kouei,
    -29999997, -29999999, 131096, -29999999, 0, 131122, -70000000, 0,
    32, 131122, -70000000, 1, 33, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    0, -29999994, 262235, (s32)btlevtcmd_SetUnitWork, -29999994, 0, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -29999994, 1, (s32)"S_1_1", 131122, -29999985, 0, 262235,
    (s32)btlevtcmd_GetUnitWork, -29999994, 5, -30000000, 131097, -30000000, -1, 131122,
    -29999999, (s32)A_of_C_Attack, 131122, -29999995, 1, 65628, (s32)evt_attack_other_arm, 33,
    262235, (s32)btlevtcmd_GetUnitWork, -29999994, 4, -30000000, 131097, -30000000, -1,
    131122, -29999999, (s32)B_of_C_Attack, 131122, -29999995, 1, 65628, (s32)evt_attack_other_arm,
    33, 131096, -70000000, 0, 65598, (s32)C_of_C_Attack_front, 131122, -29999985,
    1, 110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_ARM_MOVE1", -250000000, 0,
    -29999986, 65546, 600, 131163, (s32)evt_snd_sfxoff, -29999986, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_MOA_G_ARM_MOVE2", -250000000, 0, -250000000, 112, 32, 65598,
    (s32)C_of_C_Attack_back, 110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_ARM_MOVE1", -250000000, 0,
    -29999986, 65546, 900, 131163, (s32)evt_snd_sfxoff, -29999986, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_MOA_G_ARM_MOVE2_2", -250000000, 0, -250000000, 112, 33, 65541,
    0, 65599, -29999998, 131096, -29999998, 0, 7, 33,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, -29999998, 65545, 1, 196699,
    (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 6, 65546, 1000, 131096, -70000000,
    0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_ARM_MOVE3", -250000000, 0, -250000000,
    32, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_ARM_MOVE3_2\0", -250000000, 0, -250000000,
    33, 131096, -29999985, 0, 65541, 0, 65599, -29999998,
    131096, -29999998, 0, 7, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, -29999998, 65545, 1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1,
    6, 32, 110, 65541, 0, 65599, -29999998, 131096,
    -29999998, 0, 7, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    -29999998, 65545, 1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 6,
    65541, 0, 65599, -29999998, 131096, -29999998, 0, 7,
    33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, -29999998, 65545, 1,
    196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 6, 131122, -89999991, 0,
    112, 65546, 70, 33, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, (s32)weapon_moamoa_attack, 256, -29999995, 65570, -29999995, 65572, 1,
    196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_moamoa_attack, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, (s32)weapon_moamoa_attack, 256, -29999995, 65572, 4, 65572, 3,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    49, 262235, (s32)btlevtcmd_SetUnitWork, -29999994, 0, 1, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 131096, -29999985, 0, 65541, 0, 65599,
    -29999998, 131096, -29999998, 0, 7, 33, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, -29999998, 65545, 1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2,
    1, 6, 32, 131122, -89999991, 1, 65547, -89999991,
    33, 2, 1,
};

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    CALL(btlevtcmd_GetUnitWork, LW(6), 5, LW(10))
    IF_INT_NOT_EQUAL(LW(10), -1)
        CALL(btlevtcmd_AnimeChangePoseFromTable, LW(10), 1)
    END_IF
    CALL(btlevtcmd_GetUnitWork, LW(6), 4, LW(10))
    IF_INT_NOT_EQUAL(LW(10), -1)
        CALL(btlevtcmd_AnimeChangePoseFromTable, LW(10), 1)
    END_IF
    RETURN
EVT_END()

