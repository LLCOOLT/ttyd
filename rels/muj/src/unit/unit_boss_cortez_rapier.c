#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeWaitPlayLoopTiming);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_GetDamage);
USER_FUNC(btlevtcmd_GetDamagePartsId);
USER_FUNC(btlevtcmd_GetHitPos);
USER_FUNC(btlevtcmd_OnUnitFlag);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventUnisonPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetMaxMoveCount);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_eff);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetMoveFrame[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetStageSize[];
extern s32 btlevtcmd_GetUnitWork[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetPos[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_TransStageFloorPosition[];
extern s32 btlevtcmd_WaitEventEnd[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 cortez_weapon_blow_dead_event[];
extern s32 cortez_weapon_break_event[];
extern s32 cortez_weapon_counter_damage_event[];
extern s32 cortez_weapon_dead_event[];
extern s32 cortez_weapon_phase_event[];
extern s32 cortez_weapon_unison_phase_event[];
extern s32 evt_snd_sfx_pos[];
extern s32 evt_snd_sfxoff[];
extern s32 evt_sub_intpl_get_value[];
extern s32 evt_sub_intpl_init[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_boss_cortez_rapier_negone_one_374;
__declspec(section ".data") s32 fd_boss_cortez_rapier_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_cortez_rapier___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_cortez_rapier___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_cortez_rapier_one_negone_373;
__declspec(section ".data") s32 fd_boss_cortez_rapier___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_cortez_rapier_one_381[1];
__declspec(section ".data") u64 fd_boss_cortez_rapier_negone_one_360;
__declspec(section ".data") s32 fd_boss_cortez_rapier_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_cortez_rapier___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_cortez_rapier___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_cortez_rapier_one_negone_359;
__declspec(section ".data") s32 fd_boss_cortez_rapier___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_cortez_rapier_one_364[1];
BattleUnitKind unit_boss_cortez_rapier;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
s32 weapon_cortez_rapier_float_attack[48];
static __declspec(section ".data") PoseTableEntry pose_table[6];
static BattleDataEntry data_table[21];
static BattleUnitKindPart parts[1];
static s32 init_event[47];
static __declspec(section ".data") s32 damage_event[10];
static s32 avoid_thorn_event[33];
static __declspec(section ".data") s32 phase_event[2];
static s32 attack_event[545];
static __declspec(section ".data") s32 wait_event[10];
static s32 cortez_damage_sub_event[25];

__declspec(section ".data") u64 fd_boss_cortez_rapier_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_cortez_rapier_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_cortez_rapier___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_cortez_rapier___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_cortez_rapier_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_cortez_rapier___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_cortez_rapier_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_cortez_rapier_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_cortez_rapier_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_cortez_rapier___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_cortez_rapier___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_cortez_rapier_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_cortez_rapier___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_cortez_rapier_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_cortez_rapier = {
    96,
    "btl_un_cortez_rapier",
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
    20,
    140,
    30,
    0,
    30,
    0.0f,
    15.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    70.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    70.0f,
    0.0f,
    0.0f,
    70.0f,
    19.5f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    140.0f,
    30.0f,
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
    0x2000004,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 80, 95, 100, 90, 100, 100, 85, 0, 0, 100, 0, 100, 90, 50, 0, 90, 100, 50, 0, 0, 0};

s32 weapon_cortez_rapier_float_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 199, 2047, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") PoseTableEntry pose_table[] = {
    {2, "KRT_Z_1"},
    {9, "KRT_Z_1"},
    {28, "KRT_S_1"},
    {31, "KRT_S_1"},
    {39, "KRT_S_1"},
    {69, "KRT_S_1"},
};

static BattleDataEntry data_table[] = {
    {9, cortez_damage_sub_event},
    {49, cortez_weapon_dead_event},
    {71, cortez_weapon_break_event},
    {58, cortez_weapon_blow_dead_event},
    {36, cortez_weapon_counter_damage_event},
    {24, cortez_weapon_counter_damage_event},
    {25, cortez_weapon_counter_damage_event},
    {26, cortez_weapon_counter_damage_event},
    {27, cortez_weapon_counter_damage_event},
    {28, cortez_weapon_counter_damage_event},
    {29, cortez_weapon_counter_damage_event},
    {30, cortez_weapon_counter_damage_event},
    {31, cortez_weapon_counter_damage_event},
    {32, cortez_weapon_counter_damage_event},
    {33, cortez_weapon_counter_damage_event},
    {34, cortez_weapon_counter_damage_event},
    {35, cortez_weapon_counter_damage_event},
    {39, avoid_thorn_event},
    {37, avoid_thorn_event},
    {38, avoid_thorn_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_cortez_rapier", "c_buki3", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x3010009, 0x6, pose_table},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_OnUnitFlag, -2, 16777216)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(cortez_weapon_phase_event))
    CALL(btlevtcmd_SetEventUnisonPhase, -2, PTR(cortez_weapon_unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 2, 3)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_SetMaxMoveCount, -2, 0)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(avoid_thorn_event)
    CALL(btlevtcmd_GetHitPos, -2, 1, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 40)
    ADD(LW(2), 5)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(phase_event)
    RETURN
EVT_END()

static s32 attack_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -30000000, 131097, -30000000, 0,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 131122, -29999988, (s32)weapon_cortez_rapier_float_attack,
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999988, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1,
    65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 131163, (s32)btlevtcmd_AttackDeclareAll,
    -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 196699,
    (s32)btlevtcmd_AnimeWaitPlayLoopTiming, -2, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRT_Z_1",
    110, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 13, 0, 327771,
    (s32)evt_sub_intpl_init, 0, 0, -2160, 60, 65541, 60, 65627,
    (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, -30000000, 0, 0, 65545,
    1, 6, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0,
    112, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -250000000, -250000000, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition,
    -30000000, -29999999, -29999998, 131122, -29999999, 20, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 60, 0, 4, 0,
    -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOR_SWORD_DANCE2", -250000000, 0, -29999991,
    65647, -29999987, 131122, -29999995, 5, 65541, -29999995, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)evt_snd_sfx_pos, -29999991,
    -30000000, -29999999, -29999998, 65545, 1, 131122, -29999995, 5,
    6, 112, 65647, -29999986, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0,
    13, 0, 131122, -30000000, 0, 131122, -29999995, 5,
    65541, -29999995, 131098, -30000000, 118, 131125, -30000000, 1,
    33, 131122, -29999999, -30000000, 131128, -29999999, 2, 327771,
    (s32)btlevtcmd_AddRotate, -2, -29999999, 0, 0, 131122, -29999995, 5,
    65545, 1, 6, 112, 65647, -29999985, 131122, -30000000,
    0, 262235, (s32)btlevtcmd_GetStageSize, -29999995, -250000000, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -29999997, -30000000, -29999995, 458843, (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999,
    -29999998, -229992832, -29999986, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, -29999986, 0, 1, 0, 0, 112, 131122,
    -29999990, 0, 65539, 10, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -250000000, -250000000, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999999, -250000000,
    -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -29999999, 40, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999998, 131101, -29999998,
    0, 131098, -30000000, -29999999, 65545, 1, 65540, 10,
    33, 32, 131099, -30000000, -29999999, 65545, 1, 65540,
    10, 33, 33, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    -29999988, 256, -29999995, 65570, -29999995, 65579, 4, 65540,
    90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    65540, 90, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    65540, 90, 65572, 1, 65540, 91, 42, 65540,
    97, 49, 65539, 90, 65540, 97, 65539, 91,
    131096, -29999990, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 33,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 256, -29999995,
    131096, -29999995, 21, 65631, -29999987, 131163, (s32)evt_snd_sfxoff, -29999991,
    65631, -29999986, 65631, -29999985, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 50, 131125, -29999999, 15,
    110, 327771, (s32)evt_sub_intpl_init, 5, 0, -30, 20, 65627,
    (s32)evt_sub_intpl_get_value, 65541, 21, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2,
    -250000000, -250000000, -30000000, 65545, 1, 6, 112, 655451,
    (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 21, 0, 5,
    0, -1, 110, 327771, (s32)evt_sub_intpl_init, 4, -30, 0,
    20, 65627, (s32)evt_sub_intpl_get_value, 65541, 21, 65627, (s32)evt_sub_intpl_get_value, 327771,
    (s32)btlevtcmd_SetRotate, -2, -250000000, -250000000, -30000000, 65545, 1, 6,
    112, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 655451,
    (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 40, 0, 4,
    0, -1, 2, 33, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy,
    -29999997, -29999996, 131097, -29999997, -1, 131125, -29999990, 1,
    65540, 10, 33, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 65631, -29999986,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize, -30000000, -250000000,
    -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, -30000000, 327771, (s32)btlevtcmd_SetPos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 458843, (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998,
    -229993856, -29999986, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    -29999986, 0, 5, 0, -1, 65631, -29999987, 131163,
    (s32)evt_snd_sfxoff, -29999991, 65539, 99, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeWaitPlayLoopTiming, -2, 1)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static EVT_BEGIN(cortez_damage_sub_event)
    CALL(btlevtcmd_GetDamage, LW(10), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_GetDamagePartsId, -2, LW(11))
    CALL(btlevtcmd_AnimeChangePose, LW(10), 1, STRING("KRT_Z_1"))
    WAIT_FRAMES(30)
    LABEL(90)
    RETURN
EVT_END()

