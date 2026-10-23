#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_CheckToken);
USER_FUNC(btlevtcmd_ChoiceSamplingEnemy);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetFirstAttackTarget);
USER_FUNC(btlevtcmd_SamplingEnemy);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_check_battleflag);
USER_FUNC(evt_sub_random);
static USER_FUNC(kanbu_get_id);

__declspec(section ".data") u64 fd_gundan_zako_magician_negone_one_374;
__declspec(section ".data") s32 fd_gundan_zako_magician_neg_one_382[1];
__declspec(section ".data") s32 fd_gundan_zako_magician___local_PI_383[1];
__declspec(section ".data") s32 fd_gundan_zako_magician___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gundan_zako_magician_one_negone_373;
__declspec(section ".data") s32 fd_gundan_zako_magician___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gundan_zako_magician_one_381[1];
__declspec(section ".data") u64 fd_gundan_zako_magician_negone_one_360;
__declspec(section ".data") s32 fd_gundan_zako_magician_neg_one_365[1];
__declspec(section ".data") s32 fd_gundan_zako_magician___local_PI_366[1];
__declspec(section ".data") s32 fd_gundan_zako_magician___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gundan_zako_magician_one_negone_359;
__declspec(section ".data") s32 fd_gundan_zako_magician___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gundan_zako_magician_one_364[1];
BattleUnitKind unit_gundan_zako_magician;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[16];
static __declspec(section ".data") BattleDataEntry data_table[1];
static BattleUnitKindPart parts[2];
static s32 weapon_gundan_zako_magician_fire_bottle[48];
static s32 weapon_gundan_zako_magician_hunyahunya_bottle[48];
static s32 weapon_gundan_zako_magician_yokeyoke_bottle[48];
static s32 weapon_gundan_zako_magician_minimini_bottle[48];
static s32 weapon_gundan_zako_magician_one_recover[48];
static s32 weapon_gundan_zako_magician_all_recover[48];
static s32 weapon_gundan_zako_magician_ziwaziwa_bottle[48];
static s32 init_event[21];
static __declspec(section ".data") s32 damage_event[10];
static s32 attack_event[235];
static s32 attack_common_event1[141];
static s32 attack_common_event2[332];
static s32 attack_common_event3[251];
static s32 fire_bottle_event[56];
static s32 hunyahunya_bottle_event[43];
static s32 yokeyoke_bottle_event[74];
static s32 minimini_bottle_event[314];
static s32 one_recover_event[128];
static s32 all_recover_event[155];
static s32 yokeyoke_bottle_event_with_kanbu[15];
static s32 ziwaziwa_bottle_event[15];
static __declspec(section ".data") s32 wait_event[6];

static USER_FUNC(kanbu_get_id) {
    s32* args = event->args;
    s32 id = -1;
    s32 i;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;

    for (i = 0; i < 64; i++) {
        unit = BattleGetUnitPtr(wp, i);
        if (unit != NULL && unit->initialKind == 99) {
            id = i;
            break;
        }
    }
    evtSetValue(event, args[0], id);
    if (id != -1) {
        evtSetValue(event, args[1], BtlUnit_GetBodyPartsId(unit));
    } else {
        evtSetValue(event, args[1], 0);
    }
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_gundan_zako_magician_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gundan_zako_magician_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gundan_zako_magician___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gundan_zako_magician___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gundan_zako_magician_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gundan_zako_magician___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gundan_zako_magician_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gundan_zako_magician_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gundan_zako_magician_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gundan_zako_magician___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gundan_zako_magician___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gundan_zako_magician_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gundan_zako_magician___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gundan_zako_magician_one_364[] = {
    1065353216,
};

BattleUnitKind unit_gundan_zako_magician = {
    119,
    "btl_un_gundan_zako_magician",
    9,
    0,
    1,
    1,
    27,
    0,
    3,
    70,
    1,
    50,
    9999,
    30,
    36,
    0,
    36,
    0.0f,
    18.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    0.0f,
    12.0f,
    27.0f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    30.0f,
    36.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_3RD2_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    2,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {80, 80, 80, 100, 80, 100, 100, 70, 100, 90, 100, 90, 100, 90, 70, 90, 70, 100, 70, 100, 100, 95};

static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {27, "Z_1"},
    {28, "S_1"},
    {29, "D_1"},
    {30, "D_1"},
    {31, "S_1"},
    {39, "D_1"},
    {42, "R_1"},
    {40, "W_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_gundan_zako_magician", "c_zako_m", 0.0f, 0.0f, 0.0f, 0.0f, 28.0f, 0.0f, 0.0f, 38.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
    {2, "btl_un_gundan_zako_magician", "c_zako_m", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13018000, 0, pose_table},
};

static s32 weapon_gundan_zako_magician_fire_bottle[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 16777986, 0, 135, 2047, -2147475456,
    0, 0, 0, 75, 50331648, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_gundan_zako_magician_hunyahunya_bottle[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 770, 0, 135, 2047, -2147475456,
    0, 0, 0, 0, 0, 0, 4916221, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_gundan_zako_magician_yokeyoke_bottle[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 536870912, 770, 0, 264, 2047, 0,
    0, 0, 0, 6554368, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_gundan_zako_magician_minimini_bottle[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 7, 2047, -2147483648,
    0, 0, 0, 0, 75, 66977792, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_gundan_zako_magician_one_recover[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 536870912, 770, 0, 0, 2047, -2147478272,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_gundan_zako_magician_all_recover[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603360, 536870912, 770, 0, 0, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_gundan_zako_magician_ziwaziwa_bottle[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 536870912, 770, 0, 8, 2047, -2147478272,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1282, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
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
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(fire_bottle_event))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(kanbu_get_id, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(10)
        ELSE
        GOTO(20)
    END_IF
    LABEL(10)
    SET_VALUE(LW(0), 0)
    ADD(LW(0), 20)
    ADD(LW(0), 10)
    ADD(LW(0), 10)
    ADD(LW(0), 20)
    ADD(LW(0), 10)
    ADD(LW(0), 5)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    SET_VALUE(LW(0), 20)
    IF_INT_LESS(LW(1), LW(0))
        CALL_CHILD(PTR(fire_bottle_event))
        GOTO(99)
    END_IF
    ADD(LW(0), 10)
    IF_INT_LESS(LW(1), LW(0))
        CALL_CHILD(PTR(hunyahunya_bottle_event))
        GOTO(99)
    END_IF
    ADD(LW(0), 10)
    IF_INT_LESS(LW(1), LW(0))
        CALL(btlevtcmd_CheckStatus, -2, 7, LW(2))
        IF_INT_EQUAL(LW(2), 0)
            CALL_CHILD(PTR(yokeyoke_bottle_event))
            GOTO(99)
        END_IF
    END_IF
    ADD(LW(0), 20)
    IF_INT_LESS(LW(1), LW(0))
        CALL_CHILD(PTR(minimini_bottle_event))
        GOTO(99)
    END_IF
    ADD(LW(0), 10)
    IF_INT_LESS(LW(1), LW(0))
        CALL_CHILD(PTR(one_recover_event))
        GOTO(99)
    END_IF
    ADD(LW(0), 5)
    IF_INT_LESS(LW(1), LW(0))
        CALL_CHILD(PTR(all_recover_event))
        GOTO(99)
    END_IF
    GOTO(10)
    LABEL(20)
    SET_VALUE(LW(0), 0)
    ADD(LW(0), 60)
    ADD(LW(0), 20)
    ADD(LW(0), 20)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    SET_VALUE(LW(0), 60)
    IF_INT_LESS(LW(1), LW(0))
        CALL_CHILD(PTR(fire_bottle_event))
        GOTO(99)
    END_IF
    ADD(LW(0), 20)
    IF_INT_LESS(LW(1), LW(0))
        CALL(kanbu_get_id, LW(3), LW(4))
        CALL(btlevtcmd_CheckStatus, LW(3), 7, LW(2))
        IF_INT_EQUAL(LW(2), 0)
            CALL_CHILD(PTR(yokeyoke_bottle_event_with_kanbu))
            GOTO(99)
        END_IF
    END_IF
    ADD(LW(0), 20)
    IF_INT_LESS(LW(1), LW(0))
        CALL(kanbu_get_id, LW(3), LW(4))
        CALL(btlevtcmd_CheckStatus, LW(3), 23, LW(2))
        IF_INT_EQUAL(LW(2), 0)
            CALL_CHILD(PTR(ziwaziwa_bottle_event))
            GOTO(99)
        END_IF
    END_IF
    GOTO(20)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 attack_common_event1[] = {
    131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 131096, -29999991, (s32)weapon_gundan_zako_magician_minimini_bottle, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -29999997, -29999990, 131096, -29999990, 0, 131122, -29999990,
    125, 32, 131122, -29999990, -125, 33, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999990, 0, 1, -29999986, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999986, 32, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999986, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999986, 33,
    110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_ATTACK1", -250000000, 0, -250000000,
    65545, 40, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_ATTACK2", -250000000, 0,
    -250000000, 112, 131096, -29999991, (s32)weapon_gundan_zako_magician_fire_bottle, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"A_1A", 33, 131096, -29999991, (s32)weapon_gundan_zako_magician_hunyahunya_bottle, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"A_2A", 33, 131096, -29999991, (s32)weapon_gundan_zako_magician_minimini_bottle, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3A", 33, 131096, -29999991, (s32)weapon_gundan_zako_magician_yokeyoke_bottle,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_5A", 33, 131096, -29999991,
    (s32)weapon_gundan_zako_magician_one_recover, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_4A", 33, 131096,
    -29999991, (s32)weapon_gundan_zako_magician_all_recover, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_4A", 33,
    131096, -29999991, (s32)weapon_gundan_zako_magician_ziwaziwa_bottle, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_4A",
    33, 65545, 80, 2, 1,
};

static s32 attack_common_event2[] = {
    131096, -29999991, (s32)weapon_gundan_zako_magician_fire_bottle, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"B_1A",
    33, 131096, -29999991, (s32)weapon_gundan_zako_magician_hunyahunya_bottle, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 2,
    (s32)"B_1B", 33, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 10, 131125, -29999999, 20,
    393307, (s32)btlevtcmd_SetPartsPos, -2, 2, -30000000, -29999999, -29999998, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_ATTACK3", -250000000, 0, -250000000, 131096, -29999991,
    (s32)weapon_gundan_zako_magician_fire_bottle, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B", 33, 131096,
    -29999991, (s32)weapon_gundan_zako_magician_hunyahunya_bottle, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2B", 33,
    65545, 24, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_ATTACK4", -250000000, 0,
    -250000000, 110, 65545, 24, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"S_1", 112, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 2, 16777216, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, 2, 33554432, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, 2, 0,
    -229993856, -229999693, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 2, -30000000, -29999999,
    -29999998, 0, -1, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    -29999991, 0, -29999995, 65570, -29999995, 65579, 4, 65540,
    90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 65540, 90, 65572, 1, 65540, 91, 46,
    42, 65540, 98, 46, 65539, 90, 196699, (s32)btlevtcmd_JumpPartsContinue,
    -2, 2, 393307, (s32)btlevtcmd_GetPartsPos, -2, 2, -30000000, -29999999,
    -29999998, 65541, 12, 983131, (s32)evt_eff64, (s32)"", (s32)"glass_n64", 0,
    -30000000, -29999999, -29999998, -229998976, 30, 0, 0, 0,
    0, 0, 0, 6, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_CRASH1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"B_2",
    65545, 8, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 2, 16777216, 262235,
    (s32)btlevtcmd_OnPartsAttribute, -2, 2, 33554432, 65540, 98, 65539, 91,
    131096, -29999991, (s32)weapon_gundan_zako_magician_fire_bottle, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test", 16, -30000000,
    -29999999, -29999998, -229998976, 0, 0, 0, 0, 0,
    0, 0, 33, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 65541, 12, 983131, (s32)evt_eff64, (s32)"", (s32)"glass_n64",
    0, -30000000, -29999999, -29999998, -229998976, 30, 0, 0,
    0, 0, 0, 0, 6, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256,
    -29999995, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_CRASH1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"B_2", 65545, 8, 262235,
    (s32)btlevtcmd_OnPartsAttribute, -2, 2, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 2,
    33554432, 65540, 98, 65539, 98, 65545, 10, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 65545, 30, 65539, 99, 131163,
    (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
};

static s32 attack_common_event3[] = {
    131096, -29999991, (s32)weapon_gundan_zako_magician_yokeyoke_bottle, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"B_1D",
    33, 131096, -29999991, (s32)weapon_gundan_zako_magician_ziwaziwa_bottle, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 2,
    (s32)"B_1C", 33, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 10, 131125, -29999999, 20,
    393307, (s32)btlevtcmd_SetPartsPos, -2, 2, -30000000, -29999999, -29999998, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_ATTACK3", -250000000, 0, -250000000, 131096, -29999991,
    (s32)weapon_gundan_zako_magician_yokeyoke_bottle, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_5C", 33, 131096,
    -29999991, (s32)weapon_gundan_zako_magician_ziwaziwa_bottle, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_4C", 33,
    65545, 24, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_ATTACK4", -250000000, 0,
    -250000000, 110, 65545, 24, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"S_1", 112, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 2, 16777216, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, 2, 33554432, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, 2, 0,
    -229998976, -229999488, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 2, -30000000, 0,
    -29999998, 0, -1, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 65541, 12, 983131, (s32)evt_eff64, (s32)"", (s32)"glass_n64",
    0, -30000000, 0, -29999998, -229998976, 30, 0, 0,
    0, 0, 0, 0, 6, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 0, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 65539, 90,
    65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65540, 98, 65539, 98, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_CRASH1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"B_2",
    65545, 8, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 2, 16777216, 262235,
    (s32)btlevtcmd_OnPartsAttribute, -2, 2, 33554432, 65545, 10, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 65545, 30, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -2, 2, 1,
};

static EVT_BEGIN(fire_bottle_event)
    SET_VALUE(LW(9), PTR(weapon_gundan_zako_magician_fire_bottle))
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
        ELSE
        CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
        CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL_CHILD(PTR(attack_common_event1))
    CALL_CHILD(PTR(attack_common_event2))
    LABEL(99)
    RETURN
EVT_END()

static EVT_BEGIN(hunyahunya_bottle_event)
    SET_VALUE(LW(9), PTR(weapon_gundan_zako_magician_hunyahunya_bottle))
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL_CHILD(PTR(attack_common_event1))
    CALL_CHILD(PTR(attack_common_event2))
    LABEL(99)
    RETURN
EVT_END()

static s32 yokeyoke_bottle_event[] = {
    131122, -29999997, -2, 131122, -29999996, 1, 131122, -29999991,
    (s32)weapon_gundan_zako_magician_yokeyoke_bottle, 65630, (s32)attack_common_event1, 110, 65545, 10, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_3RD2_BOTTLE3", -250000000, 0, -250000000, 65545, 30, 65541,
    3, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_BOTTLE4", -250000000, 0, -250000000,
    65545, 20, 6, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_5B", 65545, 120, 107, 65545, 5, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_3RD2_BOTTLE5", -250000000, 0, -250000000, 65545, 55, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 109, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    2, 1,
};

static s32 minimini_bottle_event[] = {
    131122, -29999991, (s32)weapon_gundan_zako_magician_minimini_bottle, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997,
    -29999996, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16,
    -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 2, 33,
    65540, 99, 33, 65630, (s32)attack_common_event1, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    2, (s32)"B_1E", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 10, 131125, -29999999, 20,
    393307, (s32)btlevtcmd_SetPartsPos, -2, 2, -30000000, -29999999, -29999998, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_ATTACK3", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"A_3C", 65545, 24, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_3RD2_ATTACK4", -250000000, 0, -250000000, 110, 65545, 24, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 112, 262235, (s32)btlevtcmd_OffPartsAttribute, -2,
    2, 16777216, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 2, 33554432, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -29999997, -29999990, 131096, -29999990, 0, 131122, -29999990,
    125, 32, 131122, -29999990, -125, 33, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_JumpPartsSetting, -2,
    2, 0, -229993856, -229999693, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 2,
    -29999990, 0, 0, 0, -1, 983131, (s32)evt_eff, (s32)"",
    (s32)"kemuri_test", 20, -29999990, 50, 0, -229997543, 0, 0,
    0, 0, 0, 0, 0, 65541, 12, 983131,
    (s32)evt_eff64, (s32)"", (s32)"glass_n64", 0, -29999990, 0, 0, -229998976,
    30, 0, 0, 0, 0, 0, 0, 6,
    107, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_CRASH1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"B_2", 65545, 8, 262235,
    (s32)btlevtcmd_OnPartsAttribute, -2, 2, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 2,
    33554432, 109, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131122, -29999990,
    0, 65539, 0, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    -29999991, 0, -29999995, 65570, -29999995, 65579, 4, 65540,
    90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 65540, 90, 65572, 1, 65540, 91, 46,
    42, 65540, 98, 46, 65539, 90, 65540, 97,
    65539, 91, 131096, -29999990, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65540, 97, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy,
    -29999997, -29999996, 131097, -29999997, -1, 131125, -29999990, 1,
    65540, 0, 33, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 65545, 60, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2,
    2, 1,
};

static s32 one_recover_event[] = {
    131122, -29999991, (s32)weapon_gundan_zako_magician_one_recover, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997,
    -29999996, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16,
    -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 2, 33,
    65540, 99, 33, 65630, (s32)attack_common_event1, 110, 65545, 10,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_SHAKE1", -250000000, 0, -250000000, 65545,
    30, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_SHAKE1", -250000000, 0, -250000000,
    65545, 30, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_SHAKE1", -250000000, 0,
    -250000000, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_4B", 65545,
    80, 262235, (s32)btlevtcmd_RecoverHp, -29999997, -29999996, 10, 393307, (s32)btlevtcmd_GetPartsPos,
    -29999997, -29999996, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_GetHeight, -29999997,
    -29999995, 196699, (s32)btlevtcmd_GetStatusMg, -29999997, -29999994, 131132, -29999995, -29999994,
    131125, -29999999, -29999995, 983131, (s32)evt_eff, (s32)"", (s32)"recovery\0\0\0", 0,
    -30000000, -29999999, -29999998, 10, 0, 0, 0, 0,
    0, 0, 0, 65545, 30, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 65545, 60, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
};

static s32 all_recover_event[] = {
    131122, -29999991, (s32)weapon_gundan_zako_magician_all_recover, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997,
    -29999996, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16,
    -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 2, 33,
    65540, 99, 33, 65630, (s32)attack_common_event1, 110, 65545, 10,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_SHAKE1", -250000000, 0, -250000000, 65545,
    30, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_SHAKE1", -250000000, 0, -250000000,
    65545, 30, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD2_SHAKE1", -250000000, 0,
    -250000000, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_4B", 65545,
    80, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 65539, 0, 110,
    196699, (s32)evt_sub_random, 10, -29999990, 131125, -29999990, 5, 65545,
    -29999990, 262235, (s32)btlevtcmd_RecoverHp, -29999997, -29999996, 5, 393307, (s32)btlevtcmd_GetPartsPos,
    -29999997, -29999996, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_GetHeight, -29999997,
    -29999995, 196699, (s32)btlevtcmd_GetStatusMg, -29999997, -29999994, 131132, -29999995, -29999994,
    131125, -29999999, -29999995, 983131, (s32)evt_eff, (s32)"", (s32)"recovery\0\0\0", 0,
    -30000000, -29999999, -29999998, 5, 0, 0, 0, 0,
    0, 0, 0, 112, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996,
    131097, -29999997, -1, 65540, 0, 33, 65545, 90,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 65545, 60, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -2, 2, 1,
};

static EVT_BEGIN(yokeyoke_bottle_event_with_kanbu)
    SET_VALUE(LW(9), PTR(weapon_gundan_zako_magician_yokeyoke_bottle))
    CALL(kanbu_get_id, LW(3), LW(4))
    CALL_CHILD(PTR(attack_common_event1))
    CALL_CHILD(PTR(attack_common_event3))
    LABEL(99)
    RETURN
EVT_END()

static EVT_BEGIN(ziwaziwa_bottle_event)
    SET_VALUE(LW(9), PTR(weapon_gundan_zako_magician_ziwaziwa_bottle))
    CALL(kanbu_get_id, LW(3), LW(4))
    CALL_CHILD(PTR(attack_common_event1))
    CALL_CHILD(PTR(attack_common_event3))
    LABEL(99)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

