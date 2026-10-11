#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "stdlib.h"

f32 intplGetValue(f32 start, f32 end, s32 mode, s32 currStep, s32 steps);
s32 irand(s32 scalar);
EffectEntry* effVaporN64Entry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 delay);

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHitCursorOffset);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_check_battleflag);
USER_FUNC(evt_eff);
USER_FUNC(evt_sub_random);
static USER_FUNC(shadow_scale_memory);
static USER_FUNC(shadow_scale_return);
static USER_FUNC(shadow_scale_small);
static USER_FUNC(pakkun_ceil_exist);
static USER_FUNC(eff_poison_breath);
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AnimeSetPoseTable[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckAttribute[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFirstAttackTarget[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_OffAttribute[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_OnAttribute[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetEventCeilFall[];
extern s32 btlevtcmd_SetHitOffset[];
extern s32 btlevtcmd_SetHomePos[];
extern s32 btlevtcmd_SetKissHitOffset[];
extern s32 btlevtcmd_SetPos[];
extern s32 btlevtcmd_SetStatusIconOffset[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_add_zoom[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_h[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_poison_pakkun_negone_one_374;
__declspec(section ".data") s32 fd_poison_pakkun_neg_one_382[1];
__declspec(section ".data") s32 fd_poison_pakkun___local_PI_383[1];
__declspec(section ".data") s32 fd_poison_pakkun___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_poison_pakkun_one_negone_373;
__declspec(section ".data") s32 fd_poison_pakkun___local_PIO2_384[1];
__declspec(section ".data") s32 fd_poison_pakkun_one_381[1];
__declspec(section ".data") u64 fd_poison_pakkun_negone_one_360;
__declspec(section ".data") s32 fd_poison_pakkun_neg_one_365[1];
__declspec(section ".data") s32 fd_poison_pakkun___local_PI_366[1];
__declspec(section ".data") s32 fd_poison_pakkun___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_poison_pakkun_one_negone_359;
__declspec(section ".data") s32 fd_poison_pakkun___local_PIO2_367[1];
__declspec(section ".data") s32 fd_poison_pakkun_one_364[1];
BattleUnitKind unit_poison_pakkun;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static BattleUnitKindPart parts[1];
s32 weapon_poison_pakkun_attack[48];
s32 weapon_poison_pakkun_breath_attack[48];
static s32 attack_event[79];
static s32 breath_event[369];
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_ceil[18];
static BattleDataEntry data_table[15];
static s32 init_event[31];
static s32 dmg_avoid_counter_thorn_head_event[71];
static __declspec(section ".data") s32 damage_event[10];
static s32 counter_damage_event[30];
static s32 ceil_fall_ready_event[131];
static s32 return_event[256];
static s32 normal_attack_event[311];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_poison_pakkun_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_poison_pakkun_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_poison_pakkun___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_poison_pakkun___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_poison_pakkun_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_poison_pakkun___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_poison_pakkun_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_poison_pakkun_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_poison_pakkun_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_poison_pakkun___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_poison_pakkun___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_poison_pakkun_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_poison_pakkun___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_poison_pakkun_one_364[] = {
    1065353216,
};

BattleUnitKind unit_poison_pakkun = {
    88,
    "btl_un_poison_pakkun",
    8,
    0,
    1,
    1,
    20,
    0,
    3,
    70,
    0,
    60,
    9999,
    40,
    48,
    4,
    48,
    0.0f,
    24.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    0.0f,
    16.0f,
    32.0f,
    0.0f,
    0.0f,
    24.0f,
    0.0f,
    40.0f,
    48.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_PAKKUN_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {105, 80, 50, 0, 95, 100, 100, 70, 100, 90, 100, 90, 100, 95, 80, 20, 40, 100, 80, 100, 100, 95};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_poison_pakkun", "c_pakflwr_p", 0.0f, 0.0f, 0.0f, 0.0f, 40.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0x1, pose_table},
};

s32 weapon_poison_pakkun_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 135, 2, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_poison_pakkun_breath_attack[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 770, 0, 71, 2047, 0,
    0, 12810, 16777216, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(9), PTR(weapon_poison_pakkun_attack))
        CALL_CHILD(PTR(normal_attack_event))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(9), PTR(weapon_poison_pakkun_attack))
        CALL_CHILD(PTR(normal_attack_event))
        GOTO(99)
        ELSE
        CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(LW(0))
            CALL(btlevtcmd_StartWaitEvent, -2)
            RETURN
        END_IF
        SET_VALUE(LW(0), 60)
        ADD(LW(0), 40)
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(1))
        IF_INT_LESS(LW(1), 60)
            SET_VALUE(LW(9), PTR(weapon_poison_pakkun_attack))
            CALL_CHILD(PTR(normal_attack_event))
            GOTO(99)
        END_IF
        CALL_CHILD(PTR(breath_event))
        GOTO(99)
        LABEL(99)
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
EVT_END()

static s32 breath_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_poison_pakkun_breath_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_poison_pakkun_breath_attack,
    -29999997, -29999996, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2,
    16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 2,
    33, 65540, 99, 33, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_poison_pakkun_breath_attack, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_poison_pakkun_breath_attack, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAKKUN_MOVE1",
    -250000000, 0, -250000000, 110, 131163, (s32)shadow_scale_small, -2, 112,
    262235, (s32)btlevtcmd_CheckAttribute, -2, 2, -29999985, 131096, -29999985, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKF_E_2", 32, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PKF_E_4", 33, 65546, 300, 196699, (s32)btlevtcmd_OnAttribute,
    -2, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1, 33554432, 327771,
    (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -2,
    -40, 0, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65546,
    500, 196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0,
    -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom,
    0, 200, 393307, (s32)btlevtcmd_SetHitOffset, -2, 1, 0, 0,
    0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAKKUN_MOVE2", -250000000, 0, -250000000,
    110, 131163, (s32)shadow_scale_return, -2, 112, 196699, (s32)btlevtcmd_OffAttribute, -2,
    16777216, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1, 33554432, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PKF_E_1", 65546, 500, 110, 65541, 3,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAKKUN_MOUTH1", -250000000, 0, -250000000, 65545,
    20, 6, 112, 262235, (s32)btlevtcmd_CheckAttribute, -2, 2, -29999985,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKF_S_2", 65546, 1000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAKKUN_POISON1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PKF_A_3A", 65546, 300, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PKF_A_3B", 65546, 300, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    110, 196699, (s32)btlevtcmd_GetEnemyBelong, -29999997, -29999990, 131096, -29999990, 0,
    65541, 20, 131163, (s32)eff_poison_breath, 1, 65545, 3, 6,
    32, 65541, 20, 131163, (s32)eff_poison_breath, 0, 65545, 3,
    6, 33, 112, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131122,
    -29999990, 0, 65539, 10, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, (s32)weapon_poison_pakkun_breath_attack, 256, -29999995, 65570, -29999995, 65579, 4,
    65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 65540, 90, 65572, 1, 65540, 91,
    46, 42, 65540, 98, 46, 49, 65539, 90,
    65540, 97, 65539, 91, 131096, -29999990, 0, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_poison_pakkun_breath_attack, 33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, (s32)weapon_poison_pakkun_breath_attack, 256, -29999995, 65540, 97, 65539, 97,
    196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131097, -29999997, -1, 131125,
    -29999990, 1, 65540, 10, 33, 65546, 1000, 262235,
    (s32)btlevtcmd_CheckAttribute, -2, 2, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PKF_A_3C", 65546, 200, 65630, (s32)return_event, 65539, 99, 2,
    1,
};

static PoseTableEntry pose_table[] = {
    {1, "PKF_N_1"},
    {2, "PKF_Y_1"},
    {9, "PKF_Y_1"},
    {5, "PKF_K_1"},
    {4, "PKF_X_1"},
    {3, "PKF_X_1"},
    {28, "PKF_S_1"},
    {29, "PKF_Q_1"},
    {30, "PKF_Q_1"},
    {31, "PKF_S_2"},
    {39, "PKF_D_1"},
    {50, "PKF_A_1B"},
    {40, "PKF_S_1"},
    {42, "PKF_S_1"},
    {56, "PKF_X_1"},
    {57, "PKF_X_1"},
    {65, "PKF_T_1"},
    {69, "PKF_S_1"},
};

static PoseTableEntry pose_table_ceil[] = {
    {1, "PKF_N_2"},
    {2, "PKF_Y_2"},
    {9, "PKF_Y_2"},
    {5, "PKF_K_2"},
    {4, "PKF_X_2"},
    {3, "PKF_X_2"},
    {28, "PKF_S_3"},
    {29, "PKF_Q_2"},
    {30, "PKF_Q_2"},
    {31, "PKF_S_4"},
    {39, "PKF_D_2"},
    {50, "PKF_A_5"},
    {40, "PKF_S_3"},
    {42, "PKF_S_3"},
    {56, "PKF_X_2"},
    {57, "PKF_X_2"},
    {65, "PKF_S_3"},
    {69, "PKF_S_3"},
};

static BattleDataEntry data_table[] = {
    {37, dmg_avoid_counter_thorn_head_event},
    {26, counter_damage_event},
    {25, counter_damage_event},
    {27, counter_damage_event},
    {28, counter_damage_event},
    {29, counter_damage_event},
    {30, counter_damage_event},
    {31, counter_damage_event},
    {32, counter_damage_event},
    {33, counter_damage_event},
    {34, counter_damage_event},
    {35, counter_damage_event},
    {36, counter_damage_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetHitCursorOffset, -2, 1, 0, 50, 0)
    CALL(shadow_scale_memory, -2)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 31)
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PKF_S_1"))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, -2, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 63)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 37)
        GOTO(90)
    END_IF
    ADD(LW(1), 50)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(counter_damage_event)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PKF_D_1"))
    WAIT_MS(1000)
    CALL(btlevtcmd_CheckDamageCode, -2, 512, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDamageCode, -2, 2048, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            RETURN
        END_IF
    END_IF
    CALL_CHILD(PTR(return_event))
    RETURN
EVT_END()

static s32 ceil_fall_ready_event[] = {
    196699, (s32)btlevtcmd_SetEventCeilFall, -2, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAKKUN_MOVE1",
    -250000000, 0, -250000000, 110, 131163, (s32)shadow_scale_small, -2, 112,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKF_E_4", 65546, 300, 196699,
    (s32)btlevtcmd_OnAttribute, -2, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1, 33554432,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos,
    -2, -30000000, 0, -29999998, 327771, (s32)btlevtcmd_SetHomePos, -2, -30000000,
    0, -29999998, 65546, 500, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAKKUN_MOVE2",
    -250000000, 0, -250000000, 110, 131163, (s32)shadow_scale_return, -2, 112,
    196699, (s32)btlevtcmd_OffAttribute, -2, 16777216, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1,
    33554432, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKF_E_1", 393307, (s32)btlevtcmd_SetHitOffset,
    -2, 1, 0, 0, 0, 393307, (s32)btlevtcmd_SetHitCursorOffset, -2,
    1, 0, 50, 0, 262235, (s32)btlevtcmd_SetStatusIconOffset, -2, 4,
    48, 327771, (s32)btlevtcmd_SetKissHitOffset, -2, 16, 32, 0, 196699,
    (s32)btlevtcmd_OffAttribute, -2, 2, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1, 4194304,
    262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1, 2097152, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2,
    1, (s32)pose_table, 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PKF_S_1", 2, 1,
};

static s32 return_event[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 131163, (s32)pakkun_ceil_exist, -30000000, 131096,
    -30000000, 1, 196699, (s32)evt_sub_random, 1, -29999985, 32, 131122,
    -29999985, 0, 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAKKUN_MOVE1", -250000000,
    0, -250000000, 110, 131163, (s32)shadow_scale_small, -2, 112, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKF_E_2", 65546, 300, 196699, (s32)btlevtcmd_OnAttribute,
    -2, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1, 33554432, 131096,
    -29999985, 0, 196699, (s32)btlevtcmd_SetEventCeilFall, -2, 0, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -2, -30000000,
    0, -29999998, 327771, (s32)btlevtcmd_SetHomePos, -2, -30000000, 0, -29999998,
    65546, 500, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAKKUN_MOVE2", -250000000, 0,
    -250000000, 110, 131163, (s32)shadow_scale_return, -2, 112, 196699, (s32)btlevtcmd_OffAttribute,
    -2, 16777216, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1, 33554432, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKF_E_1", 393307, (s32)btlevtcmd_SetHitOffset, -2, 1,
    0, 0, 0, 393307, (s32)btlevtcmd_SetHitCursorOffset, -2, 1, 0,
    50, 0, 262235, (s32)btlevtcmd_SetStatusIconOffset, -2, 4, 48, 327771,
    (s32)btlevtcmd_SetKissHitOffset, -2, 16, 32, 0, 196699, (s32)btlevtcmd_OffAttribute, -2,
    2, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1, 4194304, 262235, (s32)btlevtcmd_OffPartsAttribute,
    -2, 1, 2097152, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table,
    65546, 500, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKF_S_1", 32,
    196699, (s32)btlevtcmd_SetEventCeilFall, -2, (s32)ceil_fall_ready_event, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, 130, -29999998,
    327771, (s32)btlevtcmd_SetHomePos, -2, -30000000, 130, -29999998, 65546, 500,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAKKUN_MOVE2", -250000000, 0, -250000000, 110,
    131163, (s32)shadow_scale_return, -2, 112, 196699, (s32)btlevtcmd_OffAttribute, -2, 16777216,
    262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1, 33554432, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PKF_E_3", 393307, (s32)btlevtcmd_SetHitOffset, -2, 1, 0, -80,
    0, 393307, (s32)btlevtcmd_SetHitCursorOffset, -2, 1, 0, -50, 0,
    262235, (s32)btlevtcmd_SetStatusIconOffset, -2, 4, 10, 327771, (s32)btlevtcmd_SetKissHitOffset, -2,
    16, -32, 0, 196699, (s32)btlevtcmd_OnAttribute, -2, 2, 262235,
    (s32)btlevtcmd_OnPartsAttribute, -2, 1, 4194304, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1,
    2097152, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table_ceil, 65546, 500,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKF_S_3", 33, 2, 1,
};

static s32 normal_attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 65546,
    750, 196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 33, 131096, -29999997, -1,
    262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0,
    65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_PAKKUN_MOVE1", -250000000, 0, -250000000, 110, 131163, (s32)shadow_scale_small, -2,
    112, 262235, (s32)btlevtcmd_CheckAttribute, -2, 2, -29999985, 131096, -29999985,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKF_E_2", 32, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKF_E_4", 33, 65546, 300, 196699,
    (s32)btlevtcmd_OnAttribute, -2, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1, 33554432,
    327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -29999997, -30000000, 45, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, 0,
    -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65546, 500, 196699,
    (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250,
    393307, (s32)btlevtcmd_SetHitOffset, -2, 1, 0, 0, 0, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAKKUN_MOVE2", -250000000, 0, -250000000, 110, 131163,
    (s32)shadow_scale_return, -2, 112, 196699, (s32)btlevtcmd_OffAttribute, -2, 16777216, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, 1, 33554432, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PKF_E_1", 65546, 150, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKF_A_1A",
    65546, 200, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAKKUN_ATTACK1", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKF_A_1B", 65546, 200,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKF_A_1C", 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 49, 65539,
    90, 65540, 98, 65539, 91, 393307, (s32)evt_btl_camera_shake_h, 0,
    1, 1, 8, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_btl_camera_add_zoom, 0, -50, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65540, 98, 65539, 98, 65546, 500, 65630, (s32)return_event,
    65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static USER_FUNC(shadow_scale_return) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);

    if (isFirstCall) {
        unit->work[1] = 0;
    }
    part->field_0x78 = intplGetValue(0.0f, unit->work[0], 0, unit->work[1], 15);
    if (unit->work[1] >= 15) {
        return EVT_RETURN_DONE;
    }
    unit->work[1]++;
    return EVT_RETURN_BLOCK;
}

static USER_FUNC(shadow_scale_small) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);

    if (isFirstCall) {
        unit->work[1] = 0;
    }
    part->field_0x78 = intplGetValue(unit->work[0], 0.0f, 0, unit->work[1], 15);
    if (unit->work[1] >= 15) {
        return EVT_RETURN_DONE;
    }
    unit->work[1]++;
    return EVT_RETURN_BLOCK;
}

static USER_FUNC(shadow_scale_memory) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);

    unit->work[0] = part->field_0x78;
    return EVT_RETURN_DONE;
}

static USER_FUNC(pakkun_ceil_exist) {
    s32* args = event->args;

    if (_battleWorkPointer->field_180DC & 0x20) {
        evtSetValue(event, args[0], 0);
    } else {
        evtSetValue(event, args[0], 1);
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
