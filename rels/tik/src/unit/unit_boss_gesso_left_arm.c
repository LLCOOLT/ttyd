#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckDamagePattern);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_OnAttribute);
USER_FUNC(btlevtcmd_OnUnitFlag);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_RunDataEventChild);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitAttackEnd);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeWaitPlayComplete[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckWeaponPluralTarget[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_EnemyItemUseCheck[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_ftof[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_mode[];
extern s32 gesso_arm_damage_pose_event[];
extern s32 gesso_arm_dead_event[];
extern s32 subsetevt_damage[];
extern s32 subsetevt_dead[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 boss_gesso_left_arm_negone_one_374;
__declspec(section ".data") s32 boss_gesso_left_arm_neg_one_382[1];
__declspec(section ".data") s32 boss_gesso_left_arm___local_PI_383[1];
__declspec(section ".data") s32 boss_gesso_left_arm___local_3PIO2_385[1];
__declspec(section ".data") u64 boss_gesso_left_arm_one_negone_373;
__declspec(section ".data") s32 boss_gesso_left_arm___local_PIO2_384[1];
__declspec(section ".data") s32 boss_gesso_left_arm_one_381[1];
__declspec(section ".data") u64 boss_gesso_left_arm_negone_one_360;
__declspec(section ".data") s32 boss_gesso_left_arm_neg_one_365[1];
__declspec(section ".data") s32 boss_gesso_left_arm___local_PI_366[1];
__declspec(section ".data") s32 boss_gesso_left_arm___local_3PIO2_368[1];
__declspec(section ".data") u64 boss_gesso_left_arm_one_negone_359;
__declspec(section ".data") s32 boss_gesso_left_arm___local_PIO2_367[1];
__declspec(section ".data") s32 boss_gesso_left_arm_one_364[1];
BattleUnitKind unit_boss_gesso_left_arm;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") PoseTableEntry pose_table[4];
BattleDataEntry gesso_left_arm_data_table[13];
static __declspec(section ".data") s32 data_table[6];
static BattleUnitKindPart parts[1];
static s32 init_event[25];
static s32 damage_event[31];
s32 gesso_left_arm_damage_event[93];
static __declspec(section ".data") s32 phase_event[2];
s32 weapon_gesso_left_arm_attack[48];
static s32 attack_event[171];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 boss_gesso_left_arm_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 boss_gesso_left_arm_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 boss_gesso_left_arm___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 boss_gesso_left_arm___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 boss_gesso_left_arm_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 boss_gesso_left_arm___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 boss_gesso_left_arm_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 boss_gesso_left_arm_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 boss_gesso_left_arm_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 boss_gesso_left_arm___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 boss_gesso_left_arm___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 boss_gesso_left_arm_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 boss_gesso_left_arm___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 boss_gesso_left_arm_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_gesso_left_arm = {
    9,
    "btl_un_gesso_left_arm",
    3,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    9,
    150,
    40,
    -240,
    36,
    0.0f,
    0.0f,
    0.0f,
    -255,
    -5,
    0.0f,
    0.0f,
    0.0f,
    75.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    75.0f,
    0.0f,
    0.0f,
    75.0f,
    26.0f,
    0.0f,
    -215.0f,
    20.0f,
    0.0f,
    150.0f,
    40.0f,
    0,
    0,
    -1,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_GESSO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x200000,
    &regist,
    1,
    parts,
    init_event,
    gesso_left_arm_data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static __declspec(section ".data") PoseTableEntry pose_table[] = {
    {28, "GSO_S1_1"},
    {31, "GSO_S1_1"},
    {39, "GSO_D1_1"},
    {69, "GSO_S1_1"},
};

BattleDataEntry gesso_left_arm_data_table[] = {
    {24, gesso_left_arm_damage_event},
    {25, gesso_left_arm_damage_event},
    {26, gesso_left_arm_damage_event},
    {27, gesso_left_arm_damage_event},
    {28, gesso_left_arm_damage_event},
    {29, gesso_left_arm_damage_event},
    {30, gesso_left_arm_damage_event},
    {31, gesso_left_arm_damage_event},
    {32, gesso_left_arm_damage_event},
    {33, gesso_left_arm_damage_event},
    {34, gesso_left_arm_damage_event},
    {35, gesso_left_arm_damage_event},
    {36, gesso_left_arm_damage_event},
};

static __declspec(section ".data") s32 data_table[] = {
    10, (s32)gesso_arm_damage_pose_event, 49, (s32)gesso_arm_dead_event, 0, 0,
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_gesso_left_arm", "c_gesso3", 0.0f, 0.0f, 0.0f, 270.0f, 20.0f, 0.0f, 270.0f, 20.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, VERSION_PICK(0x80009, 0x2080009), 0, pose_table},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_OnAttribute, -2, 16777216)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(3))
    IF_INT_NOT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_GetUnitWork, LW(3), 4, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            CALL(btlevtcmd_StartWaitEvent, LW(3))
        END_IF
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(gesso_left_arm_damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_OnUnitFlag, LW(10), 1)
    SET_VALUE(LW(14), 39)
    SET_VALUE(LW(15), -1)
    CALL(btlevtcmd_CheckDamagePattern, LW(10), 1, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(14), 38)
    END_IF
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_RunDataEventChild, LW(10), 10)
    END_SIBLING_EVENT
    CALL_CHILD(PTR(subsetevt_damage))
    CALL(btlevtcmd_CheckDamageCode, LW(10), 1024, LW(1))
    IF_INT_NOT_EQUAL(LW(1), 0)
        WAIT_FRAMES(30)
        CALL_CHILD(PTR(subsetevt_dead))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckDamageCode, LW(10), 256, LW(1))
    IF_INT_EQUAL(LW(1), 0)
        CALL(btlevtcmd_WaitAttackEnd)
    END_IF
    CALL(btlevtcmd_ResetFaceDirection, LW(10))
    CALL(btlevtcmd_StartWaitEvent, LW(10))
    LABEL(99)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(3))
    IF_INT_NOT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_GetUnitWork, LW(3), 4, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            CALL(btlevtcmd_StartWaitEvent, LW(3))
        END_IF
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(phase_event)
    RETURN
EVT_END()

s32 weapon_gesso_left_arm_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 attack_event[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 131122, -29999988,
    (s32)weapon_gesso_left_arm_attack, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2,
    -30000000, -29999988, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997, -29999996, 131096,
    -29999997, -1, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GSO_A1_1",
    110, 196699, (s32)btlevtcmd_ftof, 16, -30000000, 65545, -30000000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GESSO_ARM_MOVE1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_ftof,
    44, -30000000, 65545, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GESSO_ATTACK2\0",
    -250000000, 0, -250000000, 112, 196699, (s32)btlevtcmd_ftof,
#ifdef VERSION_G8ME01
    67,
#else
    64,
#endif
    -30000000,
    65545, -30000000, 65539, 50, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, -29999988, 256, -29999995, 131097, -29999995, 1, 65570,
    -29999995, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65572,
    6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 49, 32, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 256,
    -29999995, 33, 196699, (s32)btlevtcmd_CheckWeaponPluralTarget, -29999988, -30000000, 131097, -30000000,
    0, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131097, -29999997, -1,
    65540, 50, 33, 33, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1,
    65539, 99, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

