#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"

double sqrt(double x);
void BtlUnit_SetAnim(BattleUnitPart* part, const char* anim);

USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_DivePartsPosition);
USER_FUNC(btlevtcmd_GetPartsPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_OffAttribute);
USER_FUNC(btlevtcmd_OnAttribute);
USER_FUNC(btlevtcmd_PartsFaceDirectionSub);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetPartsFallAccel);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
static USER_FUNC(chain_init);
static USER_FUNC(chain_main);
USER_FUNC(evt_btl_camera_set_mode);

__declspec(section ".data") u64 fd_burst_wanwan_negone_one_374;
__declspec(section ".data") s32 fd_burst_wanwan_neg_one_382[1];
__declspec(section ".data") s32 fd_burst_wanwan___local_PI_383[1];
__declspec(section ".data") s32 fd_burst_wanwan___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_burst_wanwan_one_negone_373;
__declspec(section ".data") s32 fd_burst_wanwan___local_PIO2_384[1];
__declspec(section ".data") s32 fd_burst_wanwan_one_381[1];
__declspec(section ".data") u64 fd_burst_wanwan_negone_one_360;
__declspec(section ".data") s32 fd_burst_wanwan_neg_one_365[1];
__declspec(section ".data") s32 fd_burst_wanwan___local_PI_366[1];
__declspec(section ".data") s32 fd_burst_wanwan___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_burst_wanwan_one_negone_359;
__declspec(section ".data") s32 fd_burst_wanwan___local_PIO2_367[1];
__declspec(section ".data") s32 fd_burst_wanwan_one_364[1];
BattleUnitKind unit_burst_wanwan;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[19];
static BattleDataEntry data_table[15];
static BattleUnitKindPart parts[9];
static s32 weapon_wanwan_attack[48];
static s32 init_event[41];
static s32 chain_event[23];
static s32 damage_event[33];
static s32 counter_damage_event[68];
static s32 dead_event[200];
static s32 attack_event[452];
static s32 wait_event[476];
static s32 sound_gensui_event[22];
static s32 wait_sound_event1[25];
static __declspec(section ".data") s32 wait_sound_event2[12];

__declspec(section ".data") u64 fd_burst_wanwan_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_burst_wanwan_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_burst_wanwan___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_burst_wanwan___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_burst_wanwan_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_burst_wanwan___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_burst_wanwan_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_burst_wanwan_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_burst_wanwan_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_burst_wanwan___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_burst_wanwan___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_burst_wanwan_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_burst_wanwan___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_burst_wanwan_one_364[] = {
    1065353216,
};

BattleUnitKind unit_burst_wanwan = {
    59,
    "btl_un_burst_wanwan",
    6,
    0,
    1,
    1,
    24,
    0,
    1,
    70,
    3,
    50,
    9999,
    34,
    36,
    6,
    44,
    0.0f,
    20.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    17.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    17.0f,
    0.0f,
    0.0f,
    17.0f,
    23.4f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    34.0f,
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
    "SFX_ENM_WAN_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    9,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{3, 99, 99, 3, 3}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 2, 2, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 70, 65, 100, 65, 100, 0, 70, 100, 90, 100, 90, 100, 95, 65, 45, 30, 100, 65, 100, 100, 95};

static PoseTableEntry pose_table[] = {
    {1, "WAN_N_1"},
    {2, "WAN_Y_1"},
    {9, "WAN_Y_1"},
    {5, "WAN_K_1"},
    {4, "WAN_X_1"},
    {3, "WAN_X_1"},
    {27, "WAN_Z_1"},
    {28, "WAN_S_1A"},
    {29, "WAN_D_1"},
    {30, "WAN_D_1"},
    {31, "WAN_A_1"},
    {39, "WAN_D_1"},
    {50, "WAN_A_1"},
    {42, "WAN_R_1"},
    {40, "WAN_W_1"},
    {56, "WAN_X_1"},
    {57, "WAN_X_1"},
    {65, "WAN_S_1A"},
    {69, "WAN_S_1A"},
};

static BattleDataEntry data_table[] = {
    {49, dead_event},
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

static BattleUnitKindPart parts[] = {
    {1, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 5.0f, 30.0f, 0.0f, 0.0f, 40.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x10000009, 0, pose_table},
    {2, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x12010000, 0, pose_table},
    {3, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x12010000, 0, pose_table},
    {4, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x12010000, 0, pose_table},
    {5, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x12010000, 0, pose_table},
    {6, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x12010000, 0, pose_table},
    {7, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x12010000, 0, pose_table},
    {8, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x12010000, 0, pose_table},
    {9, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x12010000, 0, pose_table},
};

static s32 weapon_wanwan_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 135, 114, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 1)
    CALL(chain_init, -2)
    SPAWN_EVENT(PTR(chain_event))
    CALL(btlevtcmd_SetJumpSound, -2, STRING("0"), STRING("SFX_ENM_WAN_LANDING1"))
    CALL(btlevtcmd_SetUnitWork, -2, 1, 127)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(chain_event)
    LABEL(0)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        GOTO(99)
    END_IF
    CALL(chain_main, -2)
    GOTO(0)
    LABEL(99)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetUnitWork, -2, 0, 1)
    CALL(btlevtcmd_SetUnitWork, -2, 2, 2)
    CALL(btlevtcmd_OnAttribute, LW(10), 4)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL(btlevtcmd_OffAttribute, LW(10), 4)
    CALL(btlevtcmd_SetUnitWork, -2, 2, 0)
    RETURN
EVT_END()

static EVT_BEGIN(counter_damage_event)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 39)
    CALL(btlevtcmd_SetPartsFallAccel, LW(10), 1, FLOAT(1.0f))
    CALL(btlevtcmd_GetPartsPos, LW(10), 1, LW(2), LW(3), LW(4))
    CALL(btlevtcmd_PartsFaceDirectionSub, LW(10), 1, LW(2), 25)
    ADD(LW(3), 25)
    CALL(btlevtcmd_DivePartsPosition, LW(10), 1, LW(2), LW(3), LW(4), 5, 0, 0, 0, -1)
    WAIT_FRAMES(30)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_CheckDamageCode, -2, 512, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDamageCode, -2, 2048, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            RETURN
        END_IF
    END_IF
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 dead_event[] = {
    131122, -30000000, 48, 393307, (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_BTL_ENEMY_DIE1_1", -250000000,
    0, -250000000, 65539, 10, 65545, 1, 131122, -29999989,
    1, 65541, 9, 393307, (s32)btlevtcmd_AddPartsRotate, -29999990, -29999989, 0,
    -8, 0, 131125, -29999989, 1, 6, 131126, -30000000,
    1, 131099, -30000000, 0, 65540, 10, 33, 131122,
    -29999989, 1, 65541, 9, 393307, (s32)btlevtcmd_SetPartsRotate, -29999990, -29999989,
    0, 0, 0, 131125, -29999989, 1, 6, 393307,
    (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_BTL_ENEMY_DIE1_2", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos,
    -29999990, -30000000, -29999999, -29999998, 131125, -29999998, 10, 983131,
    (s32)evt_eff, 0, (s32)"kemuri_test", 4, -30000000, -29999999, -29999998, -229999181,
    0, 0, 0, 0, 0, 0, 0, 196699,
    (s32)btlevtcmd_GetCoin, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreCoin, -30000000, 196699, (s32)btlevtcmd_GetExp,
    -29999990, -30000000, 131163, (s32)btlevtcmd_StoreExp, -30000000, 327771, (s32)btlevtcmd_GetPos, -29999990,
    -29999997, -29999999, -29999998, 131125, -29999998, 10, 131125, -29999999,
    30, 983131, (s32)evt_eff, (s32)"", (s32)"star_point", 0, -29999997, -29999999,
    -29999998, -30000000, 0, 0, 0, 0, 0, 0,
    0, 131122, -29999989, 1, 65541, 9, 393307, (s32)btlevtcmd_SetPartsRotateOffset,
    -29999990, -29999989, 0, 0, 0, 131125, -29999989, 1,
    6, 131122, -30000000, 30, 65539, 20, 65545, 1,
    131122, -29999989, 1, 65541, 9, 393307, (s32)btlevtcmd_AddPartsRotate, -29999990,
    -29999989, 3, 0, 0, 131125, -29999989, 1, 6,
    131126, -30000000, 1, 131099, -30000000, 0, 65540, 20,
    33, 131163, (s32)btlevtcmd_GetBackItem, -29999990, 262235, (s32)btlevtcmd_CheckDamageCode, -29999990, 1024,
    -30000000, 131097, -30000000, 0, 196699, (s32)btlevtcmd_KillUnit, -29999990, 0,
    32, 196699, (s32)btlevtcmd_KillUnit, -29999990, 2, 33, 2, 1,
};

static s32 attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 65546,
    750, 196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_EnemyItemUseCheck,
    -2, -30000000, 131097, -30000000, 0, 65630, -30000000, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_wanwan_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_wanwan_attack,
    -29999997, -29999996, 33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    1, 127, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -29999986, 131163,
    (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_wanwan_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_wanwan_attack, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 262235, (s32)btlevtcmd_ChangePartsFaceDirection, -2,
    1, -29999985, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 0, 131163,
    (s32)btlevtcmd_StopWaitEvent, -2, 196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts,
    0, -2, 1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"WAN_A_1", 65541, 2, 393307, (s32)btlevtcmd_GetPartsPos, -2, 1,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, 1, 20,
    0, -229999284, 110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_WAIT1", -29999986,
    0, -250000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_WAIT3", -29999986, 0,
    -250000000, 65545, 10, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_WAIT2", -29999986,
    0, -250000000, 112, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 1, -30000000,
    0, -29999998, 20, -1, 6, 110, 65545, 20,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"WAN_S_1A", 112, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_WAN_ATTACK1", -29999986, 0, -250000000, 393307, (s32)btlevtcmd_GetPartsPos, -2,
    1, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    40, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, 1, 30, 0, -229999693,
    524379, (s32)btlevtcmd_JumpPartsPosition, -2, 1, -30000000, 0, -29999998, 30,
    -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"WAN_A_1", 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_WAN_ATTACK2", -29999986, 0, -250000000, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 131126, -29999999, 10, 131098,
    -29999999, 0, 131122, -29999999, 0, 33, 393307, (s32)btlevtcmd_JumpPartsSetting,
    -2, 1, 0, -229983616, -230000000, 524379, (s32)btlevtcmd_JumpPartsPosition, -2,
    1, -30000000, -29999999, 10, 0, -1, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, (s32)weapon_wanwan_attack, 0, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 49,
    65539, 90, 65545, 30, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_WAIT1",
    -29999986, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"WAN_S_1A",
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_JumpPartsSetting,
    -2, 1, 0, -229991808, -230000000, 524379, (s32)btlevtcmd_JumpPartsPosition, -2,
    1, -30000000, -29999999, -29999998, 0, -1, 65540, 98,
    65539, 91, 393307, (s32)evt_btl_camera_shake_h, 0, 1, 1, 8,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_add_zoom, 0,
    -50, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_wanwan_attack, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, (s32)weapon_wanwan_attack, 256, -29999995, 65545, 30, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_WAIT1", -29999986, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"WAN_S_1A", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, 1, 0, -229991808, -229999744,
    524379, (s32)btlevtcmd_JumpPartsPosition, -2, 1, -30000000, -29999999, -29999998, 0,
    -1, 65540, 98, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 65546, 250, 65539, 99, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    0, 1, 262235, (s32)btlevtcmd_ChangePartsFaceDirection, -2, 1, -1, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 wait_event[] = {
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 0, 262235, (s32)btlevtcmd_CheckStatus, -2,
    1, -29999985, 131097, -29999985, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    2, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"WAN_N_1", 393307,
    (s32)btlevtcmd_SetPartsRotateOffset, -2, 1, 0, 10, 0, 110, 65539,
    1, 65630, (s32)sound_gensui_event, 393307, (s32)btlevtcmd_SetPartsRotate, -2, 1, 0,
    0, 0, 65545, 20, 65541, 10, 65545, 4,
    393307, (s32)btlevtcmd_AddPartsRotate, -2, 1, 0, 0, 1, 6,
    65541, 10, 65545, 4, 393307, (s32)btlevtcmd_AddPartsRotate, -2, 1,
    0, 0, -1, 6, 65540, 1, 112, 65540,
    98, 33, 262235, (s32)btlevtcmd_CheckStatus, -2, 2, -29999986, 262235,
    (s32)btlevtcmd_CheckStatus, -2, 9, -29999985, 131151, -29999985, -29999986, 131097,
    -29999985, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 2, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"WAN_Y_1", 110, 65539, 5, 65630,
    (s32)sound_gensui_event, 196699, (s32)evt_sub_random, 20, -30000000, 65545, -30000000, 65540,
    5, 112, 65540, 98, 33, 262235, (s32)btlevtcmd_CheckStatus, -2,
    5, -29999987, 262235, (s32)btlevtcmd_CheckStatus, -2, 4, -29999986, 262235,
    (s32)btlevtcmd_CheckStatus, -2, 3, -29999985, 131151, -29999985, -29999987, 131151,
    -29999985, -29999986, 131097, -29999985, 0, 110, 65539, 3,
    65630, (s32)sound_gensui_event, 196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 196699, (s32)evt_sub_random,
    20, -30000000, 65545, -30000000, 131122, -29999990, 15, 65628,
    (s32)wait_sound_event1, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 393307,
    (s32)btlevtcmd_JumpPartsSetting, -2, 1, 30, 0, -229999744, 524379, (s32)btlevtcmd_JumpPartsPosition,
    -2, 1, -30000000, 0, -29999998, 30, 0, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_LANDING1", -29999989, 0, -250000000, 131122, -29999990,
    10, 65628, (s32)wait_sound_event2, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 5,
    393307, (s32)btlevtcmd_JumpPartsSetting, -2, 1, 20, 0, -229999796, 524379,
    (s32)btlevtcmd_JumpPartsPosition, -2, 1, -30000000, 0, -29999998, 20, 0,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_LANDING1", -29999989, 0, -250000000, 131122,
    -29999990, 7, 65628, (s32)wait_sound_event2, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    20, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, 1, 15, 0, -229999591,
    524379, (s32)btlevtcmd_JumpPartsPosition, -2, 1, -30000000, 0, -29999998, 15,
    0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_LANDING1", -29999989, 0, -250000000,
    131122, -29999990, 7, 65628, (s32)wait_sound_event2, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, 1, 15,
    0, -229999796, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 1, -30000000, -29999999,
    -29999998, 15, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_LANDING1", -29999989,
    0, -250000000, 65540, 3, 112, 65540, 98, 33,
    110, 65539, 4, 65630, (s32)sound_gensui_event, 196699, (s32)evt_sub_random, 20,
    -30000000, 65545, -30000000, 131122, -29999990, 15, 65628, (s32)wait_sound_event1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"WAN_A_1", 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, 1, 30,
    0, -229999744, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 1, -30000000, 0,
    -29999998, 30, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_LANDING1", -29999989,
    0, -250000000, 131122, -29999990, 10, 65628, (s32)wait_sound_event2, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"WAN_S_1A", 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    5, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, 1, 20, 0, -229999796,
    524379, (s32)btlevtcmd_JumpPartsPosition, -2, 1, -30000000, 0, -29999998, 20,
    0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_LANDING1", -29999989, 0, -250000000,
    131122, -29999990, 7, 65628, (s32)wait_sound_event2, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"WAN_A_1", 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 393307,
    (s32)btlevtcmd_JumpPartsSetting, -2, 1, 15, 0, -229999591, 524379, (s32)btlevtcmd_JumpPartsPosition,
    -2, 1, -30000000, 0, -29999998, 15, 0, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_LANDING1", -29999989, 0, -250000000, 131122, -29999990,
    7, 65628, (s32)wait_sound_event2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"WAN_S_1A",
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_JumpPartsSetting,
    -2, 1, 15, 0, -229999796, 524379, (s32)btlevtcmd_JumpPartsPosition, -2,
    1, -30000000, -29999999, -29999998, 15, 0, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_WAN_LANDING1", -29999989, 0, -250000000, 65540, 4, 112,
    65540, 98, 65539, 98, 65539, 99, 65545, 1,
    65540, 99, 2, 1,
};

static EVT_BEGIN(sound_gensui_event)
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(11))
    MULTIPLY_FLOAT(LW(11), FLOAT(0.69921875f))
    IF_INT_LESS(LW(11), 32)
        SET_VALUE(LW(11), 32)
    END_IF
    CALL(btlevtcmd_SetUnitWork, -2, 1, LW(11))
    RETURN
EVT_END()

static s32 wait_sound_event1[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_WAIT1", -29999989, 0, -250000000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_WAIT3", -29999989, 0, -250000000, 65545, -29999990,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_WAIT2", -29999989, 0, -250000000, 2,
    1,
};

static __declspec(section ".data") s32 wait_sound_event2[] = {
    65545, -29999990, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_WAN_WAIT4", -29999989, 0,
    -250000000, 2, 1, 0,
};

static USER_FUNC(chain_main) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id;
    BattleUnit* unit;
    BattleUnitPart* part;
    f32 x;
    f32 y;
    f32 z;
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x2;
    f32 y2;
    f32 z2;
    f32 len;
    f32 sag;
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 t;

    id = evtGetValue(event, *args++);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    if (unit == NULL) {
        return EVT_RETURN_BLOCK;
    }
    part = BtlUnit_GetPartsPtr(unit, 1);
    unit = BattleGetUnitPtr(wp, id);
    BtlUnit_GetPos(unit, &x, &y, &z);
    BtlUnit_SetPartsPos(BtlUnit_GetPartsPtr(unit, 9), x - 20.0f * unit->faceDirection, y, z);
    // 2: remember the chain's shape relative to the stake
    if (unit->work[2] == 2) {
        BtlUnit_GetPartsPos(BtlUnit_GetPartsPtr(unit, 9), &x, &y, &z);
        for (i = 8; i >= 1; i--) {
            part = BtlUnit_GetPartsPtr(unit, i);
            BtlUnit_GetPartsPos(part, &x2, &y2, &z2);
            part->work[0] = x2 - x;
            part->work[1] = y2 - y;
        }
        unit->work[2] = 1;
    }
    // 1: keep that shape
    if (unit->work[2] == 1) {
        BtlUnit_GetPartsPos(BtlUnit_GetPartsPtr(unit, 9), &x, &y, &z);
        for (i = 8; i >= 1; i--) {
            part = BtlUnit_GetPartsPtr(unit, i);
            BtlUnit_SetPartsPos(part, x + part->work[0], y + part->work[1], z);
        }
        return EVT_RETURN_DONE;
    }
    // otherwise hang the links between the chomp and the stake
    BtlUnit_GetPartsPos(BtlUnit_GetPartsPtr(unit, 1), &x1, &y1, &z1);
    BtlUnit_GetPartsPos(BtlUnit_GetPartsPtr(unit, 9), &x2, &y2, &z2);
    dx = x1 - x2;
    dy = y1 - y2;
    dz = z1 - z2;
    len = (f32)sqrt(dx * dx + dy * dy + dz * dz) / 8;
    if (len < 10.0f) {
        len = 10.0f;
    }
    sag = 300.0f / (len * len);
    part = BtlUnit_GetPartsPtr(unit, 1);
    BtlUnit_GetPartsPos(part, &x, &y, &z);
    if (y > 110.0f) {
        y = 110.0f;
    }
    BtlUnit_SetPartsPos(part, x, y, z);
    BtlUnit_GetPartsPos(BtlUnit_GetPartsPtr(unit, 1), &x, &y, &z);
    x += -(unit->faceDirection * 16);
    y += 16.0f;
    BtlUnit_SetPartsPos(BtlUnit_GetPartsPtr(unit, 2), x, y, z);
    for (i = 2; i <= 7; i++) {
        BtlUnit_GetPartsPos(BtlUnit_GetPartsPtr(unit, i), &x1, &y1, &z1);
        part = BtlUnit_GetPartsPtr(unit, i + 1);
        BtlUnit_GetPartsPos(part, &x2, &y2, &z2);
        y2 -= sag;
        dx = x1 - x2;
        dy = y1 - y2;
        dz = z1 - z2;
        t = 1.0f - len / (f32)sqrt(dx * dx + dy * dy + dz * dz);
        x2 += dx * t;
        y2 += dy * t;
        z2 += dz * t;
        if (y2 < 0.0f) {
            y2 = 0.0f;
        }
        BtlUnit_SetPartsPos(part, x2, y2, z2);
    }
    for (i = 9; i >= 3; i--) {
        BtlUnit_GetPartsPos(BtlUnit_GetPartsPtr(unit, i), &x1, &y1, &z1);
        part = BtlUnit_GetPartsPtr(unit, i - 1);
        BtlUnit_GetPartsPos(part, &x2, &y2, &z2);
        y2 -= sag;
        dx = x1 - x2;
        dy = y1 - y2;
        dz = z1 - z2;
        t = 1.0f - len / (f32)sqrt(dx * dx + dy * dy + dz * dz);
        x2 += dx * t;
        y2 += dy * t;
        z2 += dz * t;
        if (y2 < 0.0f) {
            y2 = 0.0f;
        }
        BtlUnit_SetPartsPos(part, x2, y2, z2);
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(chain_init) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id;
    BattleUnit* unit;
    BattleUnitPart* part;
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    id = evtGetValue(event, *args++);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    BtlUnit_GetPos(unit, &x, &y, &z);
    // the chain links all start at the chomp
    for (i = 2; i <= 7; i++) {
        part = BtlUnit_GetPartsPtr(unit, i);
        BtlUnit_SetPartsPos(part, x, y, z);
        BtlUnit_SetAnim(part, "WAN_S_1B");
    }
    part = BtlUnit_GetPartsPtr(unit, 8);
    BtlUnit_SetPartsPos(part, x - 20.0f * unit->faceDirection, y, z);
    BtlUnit_SetAnim(part, "WAN_S_1B");
    part = BtlUnit_GetPartsPtr(unit, 9);
    BtlUnit_SetPartsPos(part, x - 20.0f * unit->faceDirection, y, z);
    BtlUnit_SetAnim(part, "WAN_Z_2");
    return EVT_RETURN_DONE;
}

