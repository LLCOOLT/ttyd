#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "party/party_motion.h"

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AttackDeclare);
USER_FUNC(btlevtcmd_CalculateFaceDirection);
USER_FUNC(btlevtcmd_ChangeFaceDirection);
USER_FUNC(btlevtcmd_CheckSpace);
USER_FUNC(btlevtcmd_CheckToken);
USER_FUNC(btlevtcmd_ChoiceSamplingEnemy);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetFaceDirection);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_PayWeaponCost);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_SamplingEnemy);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetRotate);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitGuardMove);
USER_FUNC(btlevtcmd_WeaponAftereffect);
USER_FUNC(btlevtcmd_check_battleflag);
USER_FUNC(evt_sub_random);
static USER_FUNC(honenoko_copy_status);

__declspec(section ".data") u64 fd_karon_negone_one_374;
__declspec(section ".data") s32 fd_karon_neg_one_382[1];
__declspec(section ".data") s32 fd_karon___local_PI_383[1];
__declspec(section ".data") s32 fd_karon___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_karon_one_negone_373;
__declspec(section ".data") s32 fd_karon___local_PIO2_384[1];
__declspec(section ".data") s32 fd_karon_one_381[1];
__declspec(section ".data") u64 fd_karon_negone_one_360;
__declspec(section ".data") s32 fd_karon_neg_one_365[1];
__declspec(section ".data") s32 fd_karon___local_PI_366[1];
__declspec(section ".data") s32 fd_karon___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_karon_one_negone_359;
__declspec(section ".data") s32 fd_karon___local_PIO2_367[1];
__declspec(section ".data") s32 fd_karon_one_364[1];
BattleUnitKind unit_karon;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static BattleUnitKindPart parts[6];
static s32 weapon_honenoko_attack[48];
static s32 weapon_honenoko_link_attack[48];
static __declspec(section ".data") s32 entry_honenoko[12];
static PoseTableEntry pose_table[19];
static __declspec(section ".data") BattleDataEntry data_table[4];
static s32 init_event[46];
static __declspec(section ".data") s32 damage_event[10];
static s32 dead_event[190];
static s32 fake_dead_event[165];
static s32 rebirth_event[67];
static s32 attack_event[196];
static s32 start_avoid[26];
static s32 normal_attack_event[428];
static s32 start_avoid2[26];
static s32 link_attack_event[111];
static s32 link_attack_event_sub[402];
static s32 call_friend_event[311];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_karon_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_karon_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_karon___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_karon___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_karon_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_karon___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_karon_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_karon_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_karon_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_karon___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_karon___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_karon_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_karon___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_karon_one_364[] = {
    1065353216,
};

BattleUnitKind unit_karon = {
    130,
    "btl_un_karon",
    8,
    0,
    1,
    1,
    30,
    0,
    2,
    70,
    2,
    50,
    9999,
    36,
    40,
    -4,
    40,
    0.0f,
    20.0f,
    0.0f,
    0,
    0,
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
    15.0f,
    0.0f,
    0.0f,
    9.0f,
    24.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    36.0f,
    40.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_HONENOKO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x10000,
    &regist,
    6,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{2, 2, 2, 2, 2}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 75, 30, 0, 30, 100, 100, 70, 100, 90, 100, 90, 100, 85, 70, 0, 70, 100, 70, 100, 100, 90};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_karon", "c_karon_h", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 45.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
    {2, "btl_un_karon", "c_karon_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {3, "btl_un_karon", "c_karon_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {4, "btl_un_karon", "c_karon_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {5, "btl_un_karon", "c_nagehone", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {6, "btl_un_karon", "c_karon_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

static s32 weapon_honenoko_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_honenoko_link_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") s32 entry_honenoko[] = {
    (s32)&unit_karon, 16777216, 67108868, -998637568, -998637568, -998637568, 0, 0,
    0, 0, 0, 0,
};

static PoseTableEntry pose_table[] = {
    {1, "KRN_N_1"},
    {2, "KRN_Y_1"},
    {9, "KRN_Y_1"},
    {5, "KRN_K_1"},
    {4, "KRN_X_1"},
    {3, "KRN_X_1"},
    {27, "KRN_Z_2"},
    {28, "KRN_S_1"},
    {29, "KRN_Q_1"},
    {30, "KRN_Q_1"},
    {31, "KRN_S_1"},
    {39, "KRN_D_1"},
    {50, "KRN_A_1"},
    {42, "KRN_R_1"},
    {40, "KRN_W_1"},
    {56, "KRN_X_1"},
    {57, "KRN_X_1"},
    {65, "KRN_T_1"},
    {69, "KRN_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {15, fake_dead_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_AnimeChangePose, -2, 2, STRING("KRN_H_1"))
    CALL(btlevtcmd_AnimeChangePose, -2, 3, STRING("KRN_H_1"))
    CALL(btlevtcmd_AnimeChangePose, -2, 4, STRING("KRN_H_1"))
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("0"), STRING("SFX_ENM_HONENOKO_LANDING1"))
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
    131122, -29999990, -2, 131122, -30000000, 48, 393307, (s32)btlevtcmd_snd_se,
    -29999990, (s32)"SFX_BTL_ENEMY_DIE1_1", -250000000, 0, -250000000, 65539, 10, 65545,
    1, 327771, (s32)btlevtcmd_AddRotate, -29999990, 0, -15, 0, 131126,
    -30000000, 1, 131099, -30000000, 0, 65540, 10, 33,
    327771, (s32)btlevtcmd_SetRotate, -29999990, 0, 0, 0, 393307, (s32)btlevtcmd_snd_se,
    -29999990, (s32)"SFX_BTL_ENEMY_DIE1_2", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos, -29999990,
    -30000000, -29999999, -29999998, 131125, -29999998, 10, 983131, (s32)evt_eff,
    0, (s32)"kemuri_test", 4, -30000000, -29999999, -29999998, -229999181, 0,
    0, 0, 0, 0, 0, 0, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 1, -30000000, 131096, -30000000, 0, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 1, 1, 196699, (s32)btlevtcmd_GetCoin, -29999990, -30000000, 131163,
    (s32)btlevtcmd_StoreCoin, -30000000, 196699, (s32)btlevtcmd_GetExp, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreExp,
    -30000000, 327771, (s32)btlevtcmd_GetPos, -29999990, -29999997, -29999999, -29999998, 131125,
    -29999998, 10, 131125, -29999999, 30, 327771, (s32)_add_star_point_disp_offset, -29999990,
    -29999997, -29999999, -29999998, 983131, (s32)evt_eff, (s32)"", (s32)"star_point", 0,
    -29999997, -29999999, -29999998, -30000000, 0, 0, 0, 0,
    0, 0, 0, 131101, -30000000, 1, 65541, -30000000,
    6, 33, 33, 327771, (s32)btlevtcmd_SetRotateOffset, -29999990, 0, 0,
    0, 131122, -30000000, 30, 65539, 20, 65545, 1,
    327771, (s32)btlevtcmd_AddRotate, -29999990, 3, 0, 0, 131126, -30000000,
    1, 131099, -30000000, 0, 65540, 20, 33, 131163,
    (s32)btlevtcmd_GetBackItem, -29999990, 262235, (s32)btlevtcmd_CheckDamageCode, -29999990, 1024, -30000000, 131097,
    -30000000, 0, 196699, (s32)btlevtcmd_KillUnit, -29999990, 0, 32, 196699,
    (s32)btlevtcmd_KillUnit, -29999990, 2, 33, 2, 1,
};

static s32 fake_dead_event[] = {
    327771, (s32)btlevtcmd_GetHomePos, -2, -29999998, -29999997, -29999996, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229995904, 524379, (s32)btlevtcmd_MovePosition, -2, -29999998, -29999997, -29999996,
    0, -1, 0, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -30000000,
    131096, -30000000, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 1,
    131122, -29999990, -2, 393307, (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_BTL_ENEMY_DIE1_2", -250000000,
    0, -250000000, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999, -29999998,
    131125, -29999998, 10, 983131, (s32)evt_eff, 0, (s32)"kemuri_test", 4,
    -30000000, -29999999, -29999998, -229999181, 0, 0, 0, 0,
    0, 0, 0, 196699, (s32)btlevtcmd_GetCoin, -29999990, -30000000, 131163,
    (s32)btlevtcmd_StoreCoin, -30000000, 196699, (s32)btlevtcmd_GetExp, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreExp,
    -30000000, 327771, (s32)btlevtcmd_GetPos, -29999990, -29999997, -29999999, -29999998, 131125,
    -29999998, 10, 131125, -29999999, 30, 327771, (s32)_add_star_point_disp_offset, -29999990,
    -29999997, -29999999, -29999998, 983131, (s32)evt_eff, (s32)"", (s32)"star_point", 0,
    -29999997, -29999999, -29999998, -30000000, 0, 0, 0, 0,
    0, 0, 0, 131101, -30000000, 1, 65541, -30000000,
    6, 33, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRN_D_2",
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_HONENOKO_CRUMBLE1", -250000000, 0, -250000000, 65546,
    1000, 196699, (s32)btlevtcmd_KillUnit, -2, 2, 196699, (s32)evt_sub_random, 2,
    -30000000, 131125, -30000000, 2, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2,
    -30000000, 393307, (s32)btlevtcmd_SetHitOffset, -29999990, -29999989, 0, -20, 0,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 rebirth_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -30000000, 131126, -30000000, 1,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, -30000000, 131101, -30000000, 1,
    2, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRN_D_3", 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_HONENOKO_UNITE1", -250000000, 0, -250000000, 65545, 60,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRN_D_4", 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_HONENOKO_UNITE2", -250000000, 0, -250000000, 65545, 30, 196699, (s32)btlevtcmd_OffAttribute,
    -2, 131072, 196699, (s32)btlevtcmd_GetMaxHp, -2, -30000000, 196699, (s32)btlevtcmd_SetHp,
    -2, -30000000, 393307, (s32)btlevtcmd_SetHitOffset, -2, 1, 0, 0,
    0, 2, 1,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(normal_attack_event))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 2, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(rebirth_event))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    LABEL(0)
    SET_VALUE(LW(0), 50)
    ADD(LW(0), 30)
    ADD(LW(0), 20)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    SET_VALUE(LW(0), 50)
    IF_INT_LESS(LW(1), LW(0))
        CALL_CHILD(PTR(normal_attack_event))
        GOTO(99)
    END_IF
    ADD(LW(0), 30)
    IF_INT_LESS(LW(1), LW(0))
        CALL_CHILD(PTR(link_attack_event))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 40)
        SET_VALUE(LW(4), LW(0))
        CALL(btlevtcmd_GetFaceDirection, -2, LW(5))
        MULTIPLY(LW(4), LW(5))
        IF_INT_LESS(LW(4), 0)
            SUBTRACT(LW(2), 10)
            CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
            IF_INT_EQUAL(LW(3), -1)
                CALL_CHILD(PTR(call_friend_event))
                WAIT_MS(500)
                GOTO(99)
            END_IF
            ELSE
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 40)
        IF_INT_LESS_OR_EQUAL(LW(0), 170)
            ADD(LW(2), 10)
            CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
            IF_INT_EQUAL(LW(3), -1)
                CALL(btlevtcmd_SetRotate, -2, 0, 180, 0)
                CALL_CHILD(PTR(call_friend_event))
                CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
                WAIT_MS(500)
                GOTO(99)
            END_IF
            ELSE
            BREAK_LOOP
        END_IF
    END_LOOP
    GOTO(0)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(start_avoid)
    IF_INT_EQUAL(LW(5), 3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
    END_IF
    IF_INT_EQUAL(LW(5), 6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
    END_IF
    IF_INT_EQUAL(LW(5), 2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
    END_IF
    RETURN
EVT_END()

static s32 normal_attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 65546,
    750, 196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_honenoko_attack, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_honenoko_attack, -29999997, -29999996, 33, 131096, -29999997, -1,
    262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0,
    65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33, 131163,
    (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_honenoko_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_honenoko_attack, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRN_A_1",
    65546, 250, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRN_A_2", 65546,
    250, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_HONENOKO_SEND_GROUP1", -250000000, 0, -250000000,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_HONENOKO_BONE_THROW2", -250000000, 0, -29999985, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"KRN_H_1", 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 2,
    16777216, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 2, 33554432, 393307, (s32)btlevtcmd_GetPartsPos,
    -2, 1, -30000000, -29999999, -29999998, 110, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 0, 0, 65541, 0, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    0, -29999986, 131096, -29999986, 1, 7, 33, 393307,
    (s32)btlevtcmd_AddPartsRotate, -2, 2, 0, 0, 25, 65545, 1,
    6, 112, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_honenoko_attack,
    256, -29999995, 65570, -29999995, 65579, 4, 65540, 90,
    46, 65572, 3, 65540, 90, 46, 65572, 6,
    65540, 90, 65572, 2, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 49,
    65539, 90, 110, 65541, 0, 196699, (s32)btlevtcmd_GetFaceDirection, -2,
    -30000000, 131096, -30000000, -1, 393307, (s32)btlevtcmd_GetPartsPos, -2, 2,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999994,
    -29999993, -29999992, 131100, -30000000, -29999994, 65630, (s32)start_avoid, 7,
    33, 32, 393307, (s32)btlevtcmd_GetPartsPos, -2, 2, -30000000, -29999999,
    -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999994, -29999993, -29999992,
    131101, -30000000, -29999994, 65630, (s32)start_avoid, 7, 33, 33,
    65545, 1, 6, 112, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    15, 131125, -29999999, 14, 393307, (s32)btlevtcmd_SetPartsPos, -2, 2,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize, -30000000, -250000000, -250000000, 196699,
    (s32)btlevtcmd_GetFaceDirection, -2, -29999991, 131127, -30000000, -29999991, 393307, (s32)btlevtcmd_JumpPartsSetting,
    -2, 2, 0, -229991808, -229999949, 524379, (s32)btlevtcmd_JumpPartsPosition, -2,
    2, -30000000, -29999999, -29999998, 0, 0, 131163, (s32)evt_snd_sfxoff,
    -29999985, 65540, 98, 65539, 91, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, 15, 131125, -29999999, 14, 393307, (s32)btlevtcmd_SetPartsPos, -2,
    2, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, 2, 0,
    -229991808, -229999796, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 2, -30000000, -29999999,
    -29999998, 0, 0, 131163, (s32)evt_snd_sfxoff, -29999985, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_honenoko_attack, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -29999997, -29999996, (s32)weapon_honenoko_attack, 256, -29999995, 327771, (s32)btlevtcmd_GetPos,
    -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    -50, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, 2, 0, -229997952, -229999693,
    524379, (s32)btlevtcmd_JumpPartsPosition, -2, 2, -30000000, -29999999, -29999998, 0,
    0, 65540, 98, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 1, 262235, (s32)btlevtcmd_OnPartsAttribute,
    -2, 2, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 2, 33554432,
    65545, 10, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static EVT_BEGIN(start_avoid2)
    IF_INT_EQUAL(LW(11), 3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
    END_IF
    IF_INT_EQUAL(LW(11), 6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
    END_IF
    IF_INT_EQUAL(LW(11), 2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(link_attack_event)
    CALL(btlevtcmd_SetUnitWork, -2, 3, 0)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), PTR(weapon_honenoko_link_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(weapon_honenoko_link_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_SetUnitWork, -2, 4, 0)
    CALL(btlevtcmd_WeaponAftereffect, PTR(weapon_honenoko_link_attack))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, PTR(weapon_honenoko_link_attack))
    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(15))
    SET_VALUE(LW(12), 2)
    SPAWN_EVENT(PTR(link_attack_event_sub))
    WAIT_FRAMES(40)
    SET_VALUE(LW(12), 3)
    SPAWN_EVENT(PTR(link_attack_event_sub))
    WAIT_FRAMES(35)
    SET_VALUE(LW(12), 4)
    SPAWN_EVENT(PTR(link_attack_event_sub))
    LOOP(0)
        CALL(btlevtcmd_GetUnitWork, -2, 4, LW(0))
        IF_INT_EQUAL(LW(0), -1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    WAIT_MS(300)
    RETURN
EVT_END()

static s32 link_attack_event_sub[] = {
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRN_A_1", 65546, 250, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRN_A_2", 65546, 250, 262235, (s32)btlevtcmd_AddUnitWork,
    -2, 4, 1, 262235, (s32)btlevtcmd_GetUnitWork, -2, 4, -29999987,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_HONENOKO_SEND_GROUP1", -250000000, 0, -250000000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_HONENOKO_BONE_THROW3", -250000000, 0, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, -29999988, (s32)"KRN_H_1", 262235, (s32)btlevtcmd_OffPartsAttribute, -2, -29999988, 16777216,
    262235, (s32)btlevtcmd_OffPartsAttribute, -2, -29999988, 33554432, 393307, (s32)btlevtcmd_GetPartsPos, -2,
    1, -30000000, -29999999, -29999998, 110, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    0, 0, 65541, 0, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0,
    -29999986, 131096, -29999986, 1, 7, 33, 393307, (s32)btlevtcmd_AddPartsRotate,
    -2, -29999988, 0, 0, 25, 65545, 1, 6,
    112, 131096, -29999987, 3, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, (s32)weapon_honenoko_link_attack, 256, -29999989, 32, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, (s32)weapon_honenoko_link_attack, 256, -29999989, 33, 131096, -29999987,
    3, 262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -29999986, 131096, -29999986,
    1, 65540, 91, 33, 33, 65570, -29999989, 65579,
    4, 65540, 90, 46, 65572, 3, 65540, 90,
    46, 65572, 6, 65540, 90, 65572, 2, 65540,
    90, 65572, 1, 65540, 91, 46, 42, 65540,
    98, 46, 49, 65539, 90, 110, 65541, 0,
    196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000, 131096, -30000000, -1, 393307,
    (s32)btlevtcmd_GetPartsPos, -2, -29999988, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -29999994, -29999993, -29999992, 131100, -30000000, -29999994,
    65630, (s32)start_avoid2, 7, 33, 32, 393307, (s32)btlevtcmd_GetPartsPos, -2,
    -29999988, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -29999994, -29999993, -29999992, 131101, -30000000, -29999994, 65630, (s32)start_avoid2,
    7, 33, 33, 65545, 1, 6, 112, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 15, 131125, -29999999, 14, 393307,
    (s32)btlevtcmd_SetPartsPos, -2, -29999988, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize, -30000000,
    -250000000, -250000000, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999991, 131127, -30000000,
    -29999991, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, -29999988, 0, -229991808, -229999949,
    524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999988, -30000000, -29999999, -29999998, 0,
    0, 131163, (s32)evt_snd_sfxoff, -29999985, 65540, 98, 65539, 91,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 3, 1, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, 15, 131125, -29999999, 14, 393307, (s32)btlevtcmd_SetPartsPos, -2,
    -29999988, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, -29999988, 0,
    -229991808, -229999796, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999988, -30000000, -29999999,
    -29999998, 0, 0, 131163, (s32)evt_snd_sfxoff, -29999985, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, (s32)weapon_honenoko_link_attack, 131096, -29999987, 3, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, (s32)weapon_honenoko_link_attack, 256, -29999995, 32, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -29999997, -29999996, (s32)weapon_honenoko_link_attack, 0, -29999995, 33, 327771,
    (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, -50, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, -29999988, 0, -229997952,
    -229999693, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999988, -30000000, -29999999, -29999998,
    0, 0, 65540, 98, 65539, 98, 131096, -29999987,
    3, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 1, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 4, -1, 33, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, -29999988,
    16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, -29999988, 33554432, 65539, 99,
    2, 1,
};

static s32 call_friend_event[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 131122, -29999990, 0, 65541, 6, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KRN_A_3", 65545, 5, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KRN_A_4", 65545, 15, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_HONENOKO_SEND_GROUP1",
    -250000000, 0, -250000000, 65570, -29999990, 65572, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 5, (s32)"KRN_H_4", 65572, 1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 5, (s32)"KRN_H_5", 65572, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    5, (s32)"KRN_H_5", 65572, 3, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 5,
    (s32)"KRN_H_3", 65572, 4, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 5, (s32)"KRN_H_3",
    42, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 5, (s32)"KRN_H_2", 49, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, 5, 50331648, 393307, (s32)btlevtcmd_GetPartsPos, -2, 1,
    -29999996, -29999995, -29999994, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -29999996, 15,
    131125, -29999995, 14, 393307, (s32)btlevtcmd_SetPartsPos, -2, 5, -29999996,
    -29999995, -29999994, 110, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 0,
    131122, -29999985, 0, 65541, 0, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    0, -29999986, 131096, -29999986, 1, 7, 33, 393307,
    (s32)btlevtcmd_SetPartsRotate, -2, 5, 0, 0, -29999985, 131125, -29999985,
    25, 65545, 1, 6, 112, 393307, (s32)btlevtcmd_JumpPartsSetting, -2,
    5, 0, -229993856, -229998976, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 5,
    -30000000, -29999999, -29999998, 20, 0, 393307, (s32)btlevtcmd_GetPartsPos, -2,
    5, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_SetPartsPos, -2, 6,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_HONENOKO_SEND_GROUP2", -250000000,
    0, -250000000, 65570, -29999990, 65572, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 6, (s32)"KRN_C_5", 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 6, 50331648,
    65572, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 6, (s32)"KRN_C_4", 65572,
    2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 6, (s32)"KRN_C_3", 65572, 3,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 6, (s32)"KRN_C_2", 65572, 4, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 6, (s32)"KRN_C_1", 42, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    6, (s32)"KRN_Z_2", 49, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 5, 50331648,
    131125, -29999990, 1, 6, 65545, 15, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 6, (s32)"KRN_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_HONENOKO_UNITE1", -250000000,
    0, -250000000, 65545, 60, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 6,
    (s32)"KRN_D_4", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_HONENOKO_UNITE2", -250000000, 0, -250000000,
    65545, 30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KRN_S_1", 262235,
    (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_honenoko, 0, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 6,
    50331648, 327771, (s32)btlevtcmd_SetPos, -29999997, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_SetHomePos, -29999997, -30000000, -29999999, -29999998, 196699, (s32)honenoko_copy_status, -2,
    -29999997, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static USER_FUNC(honenoko_copy_status) {
    s32* args = event->args;
    s32 id1 = BattleTransID(event, evtGetValue(event, args[0]));
    s32 id2 = BattleTransID(event, evtGetValue(event, args[1]));
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit1 = BattleGetUnitPtr(wp, id1);
    BattleUnit* unit2 = BattleGetUnitPtr(wp, id2);

    unit2->mSizeChangeTurns = unit1->mSizeChangeTurns;
    unit2->mSizeChangeStrength = unit1->mSizeChangeStrength;
    return EVT_RETURN_DONE;
}
