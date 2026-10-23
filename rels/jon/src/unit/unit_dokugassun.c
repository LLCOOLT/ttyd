#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "system.h"
#include "stdlib.h"

EffectEntry* effVaporN64Entry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 delay);

USER_FUNC(btlevtcmd_CheckPartsCounterAttribute);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventUnisonPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitAttackEnd);
static USER_FUNC(eff_poison_barrier);
USER_FUNC(evt_sub_random);
static USER_FUNC(eff_poison_breath);
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddScale[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeChangePoseFromTable[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckActStatus[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckPhase[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFirstAttackTarget[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetUnitWork[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_OffPartsCounterAttribute[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_OnPartsCounterAttribute[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetDispOffset[];
extern s32 btlevtcmd_SetHomePos[];
extern s32 btlevtcmd_SetScale[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_check_battleflag[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_add_zoom[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_snd_sfxoff[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_dokugassun_negone_one_374;
__declspec(section ".data") s32 fd_dokugassun_neg_one_382[1];
__declspec(section ".data") s32 fd_dokugassun___local_PI_383[1];
__declspec(section ".data") s32 fd_dokugassun___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_dokugassun_one_negone_373;
__declspec(section ".data") s32 fd_dokugassun___local_PIO2_384[1];
__declspec(section ".data") s32 fd_dokugassun_one_381[1];
__declspec(section ".data") u64 fd_dokugassun_negone_one_360;
__declspec(section ".data") s32 fd_dokugassun_neg_one_365[1];
__declspec(section ".data") s32 fd_dokugassun___local_PI_366[1];
__declspec(section ".data") s32 fd_dokugassun___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_dokugassun_one_negone_359;
__declspec(section ".data") s32 fd_dokugassun___local_PIO2_367[1];
__declspec(section ".data") s32 fd_dokugassun_one_364[1];
BattleUnitKind unit_dokugassun;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static s32 weapon_dokugassun_attack[48];
static s32 weapon_dokugassun_poisongas_attack[48];
static s32 attack_event[69];
static s32 poisongas_event[303];
static PoseTableEntry pose_table[17];
static __declspec(section ".data") BattleDataEntry data_table[3];
static s32 init_event[37];
static s32 barrier_event[33];
static s32 dmg_first_attack_pos[19];
static __declspec(section ".data") s32 damage_event[10];
static __declspec(section ".data") s32 counter_event[2];
static s32 unison_phase_event[140];
static s32 normal_attack_event[386];
static s32 charge_event[58];
static s32 wait_event[13];

__declspec(section ".data") u64 fd_dokugassun_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_dokugassun_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_dokugassun___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_dokugassun___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_dokugassun_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_dokugassun___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_dokugassun_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_dokugassun_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_dokugassun_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_dokugassun___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_dokugassun___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_dokugassun_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_dokugassun___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_dokugassun_one_364[] = {
    1065353216,
};

BattleUnitKind unit_dokugassun = {
    166,
    "btl_un_dokugassun",
    15,
    0,
    1,
    1,
    34,
    2,
    2,
    70,
    2,
    50,
    9999,
    35,
    30,
    4,
    30,
    0.0f,
    15.0f,
    0.0f,
    0,
    -3,
    0.0f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    17.5f,
    0.0f,
    0.0f,
    17.5f,
    19.5f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    35.0f,
    30.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_KUMO_DAMAGED1",
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

static __declspec(section ".data") StatusVulnerability regist = {65, 65, 90, 0, 60, 100, 100, 100, 100, 80, 100, 80, 100, 80, 50, 60, 85, 100, 60, 100, 100, 20};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_dokugassun", "c_kmoon_g", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 30, 30, 255, &defence, &defence_attr, 0x600009, 0, pose_table},
};

static s32 weapon_dokugassun_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 770, 0, 20615, 64, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_dokugassun_poisongas_attack[] = {
    0, 0, 0, 0,
#ifdef VERSION_G8ME01
    1677721602,
#else
    1677721600,
#endif
    1065353216, 16843009, (s32)weaponGetPowerDefault,
    10, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 71, 2047, -2147483644,
    0, 17930, 16777216, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_CheckPartsCounterAttribute, -2, 1, 512, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LW(9), PTR(weapon_dokugassun_poisongas_attack))
        CALL_CHILD(PTR(poisongas_event))
        GOTO(99)
    END_IF
    SET_VALUE(LW(0), 65)
    ADD(LW(0), 35)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    SET_VALUE(LW(0), 65)
    IF_INT_LESS(LW(1), LW(0))
        SET_VALUE(LW(9), PTR(weapon_dokugassun_attack))
        CALL_CHILD(PTR(normal_attack_event))
        GOTO(99)
    END_IF
    CALL_CHILD(PTR(charge_event))
    GOTO(99)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 poisongas_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"R_1", 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_KUMO_MOVE3", -250000000, 0, -29999985, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -40, -29999999, -29999998,
    30, 0, 4, 0, -1, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_DOKU_KUMO_CHARGE1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2B", 65545, 60, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_DOKU_KUMO_CHARGE_ATTACK1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"A_3A", 65545, 20, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"A_3B", 196699, (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_OffPartsCounterAttribute,
    -2, 1, 512, 110, 196699, (s32)btlevtcmd_GetEnemyBelong, -29999997, -29999990,
    131096, -29999990, 0, 65541, 20, 131163, (s32)eff_poison_breath, 1,
    65545, 3, 6, 32, 65541, 20, 131163, (s32)eff_poison_breath,
    0, 65545, 3, 6, 33, 112, 65545, 10,
    131122, -29999994, 0, 65539, 0, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 49, 65539,
    90, 65540, 97, 65539, 91, 131096, -29999994, 0,
    196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 131122, -29999994, 1, 33,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65540, 97, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996,
    131096, -29999997, -1, 65540, 98, 33, 65540, 0,
    65539, 98, 65545, 60, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"R_1", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KUMO_MOVE3", -250000000, 0, -29999985,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 30, 0, 4, 0,
    -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 65546, 250,
    65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
};

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
    {31, "A_1"},
    {39, "D_1"},
    {40, "W_1"},
    {42, "R_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {43, counter_event},
    {48, dmg_first_attack_pos},
    {0, NULL},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventUnisonPhase, -2, PTR(unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    SPAWN_EVENT(PTR(barrier_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(barrier_event)
    LABEL(0)
    WAIT_FRAMES(31)
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckPartsCounterAttribute, -2, 1, 512, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(eff_poison_barrier, -2)
    END_IF
    GOTO(0)
    LABEL(99)
    RETURN
EVT_END()

static EVT_BEGIN(dmg_first_attack_pos)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(counter_event)
    RETURN
EVT_END()

static s32 unison_phase_event[] = {
    196699, (s32)btlevtcmd_CheckPhase, -30000000, 67108865, 131096, -30000000, 0, 65540,
    99, 33, 196699, (s32)btlevtcmd_CheckActStatus, -2, -30000000, 131096, -30000000,
    0, 65540, 99, 33, 327771, (s32)btlevtcmd_CheckPartsCounterAttribute, -2, 1,
    512, -30000000, 131096, -30000000, 1, 65540, 99, 33,
    196699, (s32)evt_sub_random, 99, -30000000, 131098, -30000000, 25, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096, -30000000, 1, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KUMO_MOVE4", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 131122, -29999999, 40, 655451,
    (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 60, 10, 4,
    0, -1, 327771, (s32)btlevtcmd_SetHomePos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1, 6291456, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    0, 0, 32, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KUMO_MOVE5", -250000000,
    0, -250000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    131122, -29999999, 10, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, 60, -10, 4, 0, -1, 327771, (s32)btlevtcmd_SetHomePos,
    -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1,
    6291456, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 1, 33, 33,
    65539, 99, 2, 1,
};

static s32 normal_attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991,
    -29999997, -29999996, 33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699,
    (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KUMO_MOVE1", -250000000, 0, -250000000, 110,
    65541, 10, 327771, (s32)btlevtcmd_SetDispOffset, -2, 1, 0, 0,
    65545, 2, 327771, (s32)btlevtcmd_SetDispOffset, -2, -1, 0, 0,
    65545, 2, 6, 327771, (s32)btlevtcmd_SetDispOffset, -2, 0, 0,
    0, 112, 110, 65541, 40, 327771, (s32)btlevtcmd_AddScale, -2,
    -230000010, 0, 0, 65545, 1, 6, 112, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KUMO_ATTACK1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"A_2A", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, -40, 131122, -29999999,
    60, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 30,
    0, 4, 0, -1, 65545, 10, 327771, (s32)btlevtcmd_SetScale,
    -2, -229998976, -229998976, -229998976, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KUMO_MOVE2",
    -250000000, 0, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A",
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999990, -29999989, -29999988, 655451,
    (s32)btlevtcmd_DivePosition, -2, -29999990, -29999989, -29999988, 40, -40, 1,
    0, -1, 131163, (s32)evt_snd_sfxoff, -29999985, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 0, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 131122, -29999985, 1,
    46, 49, 65539, 90, 65540, 98, 65539, 91,
    393307, (s32)evt_btl_camera_shake_h, 0, 1, 1, 8, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_add_zoom, 0, -50, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999991, 256, -29999995, 65540, 98, 65539, 98, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -29999999, 40,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999990, -29999989, -29999988, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -2, -29999990, 40, 655451, (s32)btlevtcmd_DivePosition, -2, -29999990,
    -29999999, -29999988, 40, 0, 4, 0, -1, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KUMO_MOVE3", -250000000,
    0, -29999985, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 40, 40,
    4, 0, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1",
    131163, (s32)evt_snd_sfxoff, -29999985, 65546, 250, 327771, (s32)btlevtcmd_SetScale, -2,
    1, 1, 1, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2,
    2, 1,
};

static USER_FUNC(eff_poison_barrier) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    for (i = 0; i < 3; i++) {
        EffectEntry* eff;
        s32* wk;

        BtlUnit_GetPos(unit, &x, &y, &z);
        x += irand(20) - 10;
        y += irand(30);
        eff = effVaporN64Entry(2, x, y, z, 0.5f + 0.5f * rand() / 32767.0f, (i + 1) * 10);
        wk = eff->userdata;
        wk[6] = 32;
        wk[7] = 115;
        wk[8] = 100;
        wk[9] = 255;
        wk[10] = 32;
        wk[11] = 115;
        wk[12] = 100;
        wk[13] = 255;
        ((f32*)wk)[16] = unit->mSizeMultiplier;
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(eff_poison_breath) {
    f32 x;
    f32 y;
    f32 z;
    EffectEntry* eff;
    s32* wk;

    if (evtGetValue(event, event->args[0]) == 0) {
        x = -125.0f;
    } else {
        x = 125.0f;
    }
    x += irand(150) - 75;
    y = irand(70);
    z = irand(80) - 40;
    eff = effVaporN64Entry(0, x, y, z, 2.5f + rand() / 32767.0f, 15);
    wk = eff->userdata;
    wk[6] = 32;
    wk[7] = 115;
    wk[8] = 100;
    wk[9] = 255;
    wk[10] = 32;
    wk[11] = 115;
    wk[12] = 100;
    wk[13] = 255;
    return EVT_RETURN_DONE;
}

static s32 charge_event[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    300, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_DOKU_KUMO_CHARGE1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_OnPartsCounterAttribute, -2, 1, 512, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"A_2A", 65545, 20, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_2B", 65545, 60, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 65546, 600, 65539, 99,
    2, 1,
};

static s32 wait_event[] = {
    196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 327771, (s32)btlevtcmd_SetScale, -2, 1,
    1, 1, 2, 1, 0,
};

