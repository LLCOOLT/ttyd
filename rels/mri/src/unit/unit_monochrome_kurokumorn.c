#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckPartsCounterAttribute);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetStatusMg);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventUnisonPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetScale);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(evt_eff64);
USER_FUNC(evt_sub_random);
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddScale[];
extern s32 btlevtcmd_AnimeChangePose[];
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

__declspec(section ".data") u64 fd_monochrome_kurokumorn_negone_one_374;
__declspec(section ".data") s32 fd_monochrome_kurokumorn_neg_one_382[1];
__declspec(section ".data") s32 fd_monochrome_kurokumorn___local_PI_383[1];
__declspec(section ".data") s32 fd_monochrome_kurokumorn___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_monochrome_kurokumorn_one_negone_373;
__declspec(section ".data") s32 fd_monochrome_kurokumorn___local_PIO2_384[1];
__declspec(section ".data") s32 fd_monochrome_kurokumorn_one_381[1];
__declspec(section ".data") u64 fd_monochrome_kurokumorn_negone_one_360;
__declspec(section ".data") s32 fd_monochrome_kurokumorn_neg_one_365[1];
__declspec(section ".data") s32 fd_monochrome_kurokumorn___local_PI_366[1];
__declspec(section ".data") s32 fd_monochrome_kurokumorn___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_monochrome_kurokumorn_one_negone_359;
__declspec(section ".data") s32 fd_monochrome_kurokumorn___local_PIO2_367[1];
__declspec(section ".data") s32 fd_monochrome_kurokumorn_one_364[1];
static s32 unit_monochrome_kurokumorn[49];
static __declspec(section ".data") s32 defence[2];
static __declspec(section ".data") s32 defence_attr[2];
static __declspec(section ".data") s32 regist[6];
static s32 parts[19];
static s32 weapon_kurokumorn_attack[48];
static s32 weapon_kurokumorn_thunder_attack[48];
static s32 attack_event[69];
static s32 thunder_event[493];
static PoseTableEntry pose_table[17];
static __declspec(section ".data") s32 data_table[6];
static s32 init_event[37];
static s32 barrier_event[59];
static s32 dmg_first_attack_pos[19];
static __declspec(section ".data") s32 damage_event[10];
static __declspec(section ".data") s32 counter_event[2];
static s32 unison_phase_event[140];
static s32 normal_attack_event[386];
static s32 charge_event[58];
static __declspec(section ".data") s32 wait_event[12];

__declspec(section ".data") u64 fd_monochrome_kurokumorn_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_monochrome_kurokumorn_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_monochrome_kurokumorn___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_monochrome_kurokumorn___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_monochrome_kurokumorn_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_monochrome_kurokumorn___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_monochrome_kurokumorn_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_monochrome_kurokumorn_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_monochrome_kurokumorn_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_monochrome_kurokumorn___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_monochrome_kurokumorn___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_monochrome_kurokumorn_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_monochrome_kurokumorn___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_monochrome_kurokumorn_one_364[] = {
    1065353216,
};

static s32 unit_monochrome_kurokumorn[] = {
    24, (s32)"btl_un_monochrome_kurokumorn", 196608, 16845312, 21365052, 655294499, 1966084, 1966080,
    0, 1097859072, 0, 65533, 0, 0, 0, 1099956224,
    0, -1054867456, 0, 0, 0, 0, 0, 1099694080,
    0, 0, 1099694080, 1100742656, 0, 0, 1097859072, 0,
    1108082688, 1106247680, 2, 1679032320, 0, 0, 0, (s32)"SFX_ENM_KUMO_DAMAGED1",
    (s32)"SFX_BTL_DAMAGE_FIRE1", (s32)"SFX_BTL_DAMAGE_ICE1", (s32)"SFX_BTL_DAMAGE_BIRIBIRI1", 4, (s32)regist, 16777216, (s32)parts, (s32)init_event,
    (s32)data_table,
};

static __declspec(section ".data") s32 defence[] = {
    0, 0,
};

static __declspec(section ".data") s32 defence_attr[] = {
    0, 0,
};

static __declspec(section ".data") s32 regist[] = {
    1600088420, 1516528740, 1683973215, 1683968090, 1768184420, 1683947520,
};

static s32 parts[] = {
    1, (s32)"btl_un_monochrome_kurokumorn", (s32)"c_kmoon_wb", 0, 0, 0, 0, 1103626240,
    0, 0, 1106247680, 0, 1966110, 16711680, (s32)defence, (s32)defence_attr,
    6291465, 0, (s32)pose_table,
};

static s32 weapon_kurokumorn_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 20615, 1, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_kurokumorn_thunder_attack[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 67109634, 0, 71, 2047, -2147483644,
    0, 0, 0, 50331648, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_CheckPartsCounterAttribute, -2, 1, 1024, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LW(9), PTR(weapon_kurokumorn_thunder_attack))
        CALL_CHILD(PTR(thunder_event))
        GOTO(99)
    END_IF
    SET_VALUE(LW(0), 50)
    ADD(LW(0), 50)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    SET_VALUE(LW(0), 50)
    IF_INT_LESS(LW(1), LW(0))
        SET_VALUE(LW(9), PTR(weapon_kurokumorn_attack))
        CALL_CHILD(PTR(normal_attack_event))
        GOTO(99)
    END_IF
    CALL_CHILD(PTR(charge_event))
    GOTO(99)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 thunder_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996,
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KUMO_CHARGE1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2B",
    65545, 30, 65545, 30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_3A", 65545, 20, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3B",
    262235, (s32)btlevtcmd_OffPartsCounterAttribute, -2, 1, 1024, 110, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -29999997, -29999990, 131096, -29999990, 0, 131122, -29999990, 125,
    32, 131122, -29999990, -125, 33, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_KUMO_CHARGE_ATTACK1", -250000000, 0, -250000000, 131122, -30000000, -29999990, 131122,
    -29999998, 0, 131125, -30000000, -60, 131125, -29999998, -60,
    983131, (s32)evt_eff64, (s32)"", (s32)"pokopi_thunder_n64", 0, -30000000, 210, -29999998,
    -30000000, 0, -29999998, -229995904, 20, 0, 0, 0,
    131122, -30000000, -29999990, 131122, -29999998, 0, 131125, -30000000,
    60, 131125, -29999998, 60, 983131, (s32)evt_eff64, (s32)"", (s32)"pokopi_thunder_n64",
    0, -30000000, 210, -29999998, -30000000, 0, -29999998, -229995904,
    20, 0, 0, 0, 65545, 12, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_KUMO_CHARGE_ATTACK1", -250000000, 0, -250000000, 131122, -30000000, -29999990,
    131122, -29999998, 0, 131125, -30000000, 0, 131125, -29999998,
    -75, 983131, (s32)evt_eff64, (s32)"", (s32)"pokopi_thunder_n64", 0, -30000000, 210,
    -29999998, -30000000, 0, -29999998, -229995904, 20, 0, 0,
    0, 131122, -30000000, -29999990, 131122, -29999998, 0, 131125,
    -30000000, 0, 131125, -29999998, 75, 983131, (s32)evt_eff64, (s32)"",
    (s32)"pokopi_thunder_n64", 0, -30000000, 210, -29999998, -30000000, 0, -29999998,
    -229995904, 20, 0, 0, 0, 65545, 12, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KUMO_CHARGE_ATTACK1", -250000000, 0, -250000000, 131122, -30000000,
    -29999990, 131122, -29999998, 0, 131125, -30000000, 60, 131125,
    -29999998, -60, 983131, (s32)evt_eff64, (s32)"", (s32)"pokopi_thunder_n64", 0, -30000000,
    210, -29999998, -30000000, 0, -29999998, -229995904, 20, 0,
    0, 0, 131122, -30000000, -29999990, 131122, -29999998, 0,
    131125, -30000000, -60, 131125, -29999998, 60, 983131, (s32)evt_eff64,
    (s32)"", (s32)"pokopi_thunder_n64", 0, -30000000, 210, -29999998, -30000000, 0,
    -29999998, -229995904, 20, 0, 0, 0, 65545, 12,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KUMO_CHARGE_ATTACK1", -250000000, 0, -250000000, 131122,
    -30000000, -29999990, 131122, -29999998, 0, 131125, -30000000, 75,
    131125, -29999998, 0, 983131, (s32)evt_eff64, (s32)"", (s32)"pokopi_thunder_n64", 0,
    -30000000, 210, -29999998, -30000000, 0, -29999998, -229995904, 20,
    0, 0, 0, 131122, -30000000, -29999990, 131122, -29999998,
    0, 131125, -30000000, -75, 131125, -29999998, 0, 983131,
    (s32)evt_eff64, (s32)"", (s32)"pokopi_thunder_n64", 0, -30000000, 210, -29999998, -30000000,
    0, -29999998, -229995904, 20, 0, 0, 0, 65545,
    12, 112, 65545, 10, 393307, (s32)evt_btl_camera_shake_h, 0, 5,
    0, 30, 0, 131122, -29999994, 0, 65539, 0,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90,
    65572, 1, 65540, 91, 46, 42, 65540, 98,
    46, 49, 65539, 90, 65540, 97, 65539, 91,
    131096, -29999994, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 131122,
    -29999994, 1, 33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999991, 256, -29999995, 65540, 97, 65539, 97, 196699,
    (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540, 98,
    33, 65540, 0, 65539, 98, 65545, 30, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 65546, 250, 65539, 99,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
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

static __declspec(section ".data") s32 data_table[] = {
    42, (s32)counter_event, 48, (s32)dmg_first_attack_pos, 0, 0,
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
    CALL(btlevtcmd_CheckPartsCounterAttribute, -2, 1, 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        ADD(LW(1), 20)
        CALL(btlevtcmd_GetStatusMg, -2, LW(3))
        CALL(evt_eff64, STRING(""), STRING("akari_charge_n64"), 0, LW(0), LW(1), LW(2), LW(3), 30, 0, 0, 0, 0, 0, 0)
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
    1024, -30000000, 131096, -30000000, 1, 65540, 99, 33,
    196699, (s32)evt_sub_random, 99, -30000000, 131098, -30000000, 50, 262235,
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

static s32 charge_event[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    300, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KUMO_CHARGE1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_OnPartsCounterAttribute, -2, 1, 1024, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"A_2A", 65545, 20, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_2B", 65545, 60, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 65546, 600, 65539, 99,
    2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    CALL(btlevtcmd_SetScale, -2, 1, 1, 1)
    RETURN
EVT_END()

