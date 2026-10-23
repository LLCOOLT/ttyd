#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "manager/evtmgr_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_map.h"
#include "evt/evt_msg.h"
#include "party/party_motion.h"

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckActStatus);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_DrawLots);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetDamage);
USER_FUNC(btlevtcmd_GetDamagePartsId);
USER_FUNC(btlevtcmd_GetHitPos);
USER_FUNC(btlevtcmd_GetHp);
USER_FUNC(btlevtcmd_GetMaxHp);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_OnUnitFlag);
USER_FUNC(btlevtcmd_PayWeaponCost);
USER_FUNC(btlevtcmd_RecoverHp);
USER_FUNC(btlevtcmd_SetBaseScale);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetTalkBodyId);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(evt_eff);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_snd_sfxon_3d);
static USER_FUNC(_leg_smoke_effect);

__declspec(section ".data") u64 fd_boss_zonbaba_negone_one_374;
__declspec(section ".data") s32 fd_boss_zonbaba_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_zonbaba___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_zonbaba___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_zonbaba_one_negone_373;
__declspec(section ".data") s32 fd_boss_zonbaba___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_zonbaba_one_381[1];
__declspec(section ".data") u64 fd_boss_zonbaba_negone_one_360;
__declspec(section ".data") s32 fd_boss_zonbaba_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_zonbaba___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_zonbaba___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_zonbaba_one_negone_359;
__declspec(section ".data") s32 fd_boss_zonbaba___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_zonbaba_one_364[1];
BattleUnitKind unit_boss_zonbaba;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[9];
static PoseTableEntry pose_table_weak[9];
static __declspec(section ".data") BattleDataEntry data_table[3];
static BattleUnitKindPart parts[2];
s32 weapon_zonbaba_fumituke_attack[48];
s32 weapon_zonbaba_kamituki_attack[48];
s32 weapon_zonbaba_cold_attack[48];
s32 weapon_zonbaba_confuze_attack[48];
s32 weapon_zonbaba_sleep_attack[48];
s32 weapon_zonbaba_minimini_attack[48];
s32 weapon_zonbaba_recover[48];
static s32 battle_entry_event[357];
static s32 init_event[58];
static __declspec(section ".data") s32 damage_event[10];
s32 zonbaba_damage_sub_event[45];
static s32 dead_event[264];
static s32 phase_event[94];
static s32 fumituke_attack_event[356];
static s32 kamituki_attack_event[141];
s32 breath1_attack_event[315];
s32 breath2_attack_event[320];
s32 recover_event[88];
static s32 attack_event[282];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_boss_zonbaba_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_zonbaba_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_zonbaba___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_zonbaba___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_zonbaba_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_zonbaba___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_zonbaba_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_zonbaba_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_zonbaba_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_zonbaba___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_zonbaba___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_zonbaba_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_zonbaba___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_zonbaba_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_zonbaba = {
    171,
    "btl_un_zonbaba",
    200,
    0,
    1,
    1,
    0,
    99,
    0,
    100,
    0,
    50,
#ifdef VERSION_G8ME01
    5,
#else
    7,
#endif
    230,
    170,
    -210,
    45,
    0.0f,
    0.0f,
    0.0f,
    -250,
    0,
    280.0f,
    40.0f,
    0.0f,
    115.0f,
    0.0f,
    -10.0f,
#ifdef VERSION_G8ME01
    115.0f,
#else
    0.0f,
#endif
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    250.0f,
    0.0f,
    50.0f,
    380.0f,
    110.0f,
    50.0f,
    -290.0f,
    85.0f,
    0.0f,
    230.0f,
    170.0f,
    0,
    0,
    -1,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_GNB_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x200000,
    &regist,
    2,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{2, 2, 2, 2, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 0, 0, 100, 0, 100, 100, 0, 0, 0, 100, 0, 100, 0, 0, 0, 0, 100, 0, 0, 0, 0};

static PoseTableEntry pose_table[] = {
    {1, "GNB_N_1"},
    {5, "GNB_X_1"},
    {3, "GNB_X_1"},
    {2, "GNB_Z_1"},
    {28, "GNB_S_3"},
    {65, "GNB_T_3"},
    {31, "GNB_S_3"},
    {39, "GNB_D_1"},
    {69, "GNB_S_3"},
};

static PoseTableEntry pose_table_weak[] = {
    {1, "GNB_N_1"},
    {5, "GNB_X_1"},
    {3, "GNB_X_1"},
    {2, "GNB_N_1"},
    {28, "GNB_S_4"},
    {65, "GNB_T_4"},
    {31, "GNB_S_4"},
    {39, "GNB_V_1"},
    {69, "GNB_S_4"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {9, zonbaba_damage_sub_event},
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_zonbaba", "c_gonbaba_z", 0.0f, 0.0f, 0.0f, 230.0f, 36.0f, 60.0f, 230.0f, 36.0f, 60.0f, 20, 30, 255, &defence, &defence_attr, 0x2, 0, pose_table},
    {2, "btl_un_zonbaba", "c_gonbaba_z", 100.0f, 0.0f, 0.0f, 250.0f, 110.0f, 25.0f, 250.0f, 110.0f, 25.0f, 20, 30, 255, &defence, &defence_attr, 0x1600009, 0, pose_table},
};

s32 weapon_zonbaba_fumituke_attack[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 721666, 0, 7, 2047, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 167772160,
};

s32 weapon_zonbaba_kamituki_attack[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 131079, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_zonbaba_cold_attack[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 71, 2047, 0,
    0, 0, 0, 0, 1966848, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_zonbaba_confuze_attack[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 71, 2047, 0,
    0, 0, 1966848, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_zonbaba_sleep_attack[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 71, 2047, 0,
    503644160, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_zonbaba_minimini_attack[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 71, 2047, 0,
    0, 0, 0, 0, 30, 66977792, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_zonbaba_recover[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 7, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 battle_entry_event[] = {
    131163, (s32)evt_btl_camera_set_prilimit, 1, 196699, (s32)evt_map_replayanim, 0, (s32)"dontyo", 196699,
    (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, 0, 110,
    1080, 0, 93, -2, 1, 0, 262235, (s32)btlevtcmd_GetStageSize,
    -29999994, -250000000, -250000000, 131127, -29999994, -1, 327771, (s32)btlevtcmd_GetHomePos,
    -3, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -4, -29999997,
    -29999996, -29999995, 327771, (s32)btlevtcmd_SetPos, -3, -29999994, -29999999, -29999998,
    327771, (s32)btlevtcmd_SetPos, -4, -29999994, -29999996, -29999995, 262235, (s32)btlevtcmd_GetStageSize,
    -250000000, -29999997, -250000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131125, -29999999, -29999997, 327771, (s32)btlevtcmd_SetPos, -2, -30000000,
    -29999999, -29999998, 65545, 60, 262235, (s32)btlevtcmd_AnimeChangePoseType, -3, 1,
    42, 196699, (s32)btlevtcmd_GetBodyId, -4, -30000000, 262235, (s32)btlevtcmd_AnimeChangePoseType, -4,
    -30000000, 42, 327771, (s32)btlevtcmd_GetHomePos, -3, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_GetHomePos, -4, -29999997, -29999996, -29999995, 131122, -29999992,
    -30000000, 131126, -29999992, -29999997, 131098, -29999992, 0, 131127,
    -29999992, -1, 33, 262235, (s32)btlevtcmd_GetStageSize, -29999994, -250000000, -250000000,
    131122, -29999993, -29999994, 131125, -29999993, -29999992, 131127, -29999994,
    -1, 131127, -29999993, -1, 327771, (s32)btlevtcmd_SetPos, -3, -29999994,
    -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -4, -29999993, -29999996, -29999995,
    110, 196699, (s32)btlevtcmd_SetMoveSpeed, -4, -229993856, 524379, (s32)btlevtcmd_MovePosition, -4,
    -29999997, -29999996, -29999995, 0, -1, 0, 196699, (s32)btlevtcmd_GetBodyId,
    -4, -30000000, 262235, (s32)btlevtcmd_AnimeChangePoseType, -4, -30000000, 43, 112,
    196699, (s32)btlevtcmd_SetMoveSpeed, -3, -229993856, 524379, (s32)btlevtcmd_MovePosition, -3, -30000000,
    -29999999, -29999998, 0, -1, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -3,
    1, (s32)"M_I_Y", 65545, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"GNB_F_3", 65545, 1, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999, -29999998, 65545,
    10, 107, 65545, 5, 262235, (s32)btlevtcmd_AnimeChangePose, -3, 1,
    (s32)"M_I_O", 196699, (s32)btlevtcmd_SetFallAccel, -3, -229999693, 327771, (s32)btlevtcmd_GetPos, -3,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_snd_se, -3, (s32)"SFX_VOICE_MARIO_SURPRISED2_2", -250000000,
    0, -250000000, 458843, (s32)btlevtcmd_JumpPosition, -3, -30000000, -29999999, -29999998,
    25, -1, 109, 107, 65545, 5, 196699, (s32)btlevtcmd_SetFallAccel,
    -4, -229999693, 327771, (s32)btlevtcmd_GetPos, -4, -30000000, -29999999, -29999998,
    458843, (s32)btlevtcmd_JumpPosition, -4, -30000000, -29999999, -29999998, 25, -1,
    196699, (s32)btlevtcmd_GetBodyId, -4, -30000000, 262235, (s32)btlevtcmd_AnimeChangePoseType, -4, -30000000,
    5, 109, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BOSS_GNB_APPEAR1", 0, 393307, (s32)evt_btl_camera_shake_h,
    1, 8, 0, 20, 13, 65545, 30, 262235,
    (s32)btlevtcmd_AnimeChangePose, -3, 1, (s32)"M_I_Y", 196699, (s32)btlevtcmd_GetBodyId, -4, -30000000,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -4, -30000000, 43, 196699, (s32)evt_btl_camera_set_mode, 1,
    3, 655451, (s32)evt_btl_camera_set_moveto, 1, -233, 45, 452, 56,
    125, 37, 60, 0, 65545, 60, 131163, (s32)btlevtcmd_StatusWindowOnOff,
    0, 327771, (s32)evt_msg_print, 2, (s32)"tik_boss_12", 0, -2, 65546,
    300, 131163, (s32)evt_msg_print_battle_party, (s32)"tik_boss_13", 131163, (s32)btlevtcmd_StartWaitEvent, -3, 131163,
    (s32)btlevtcmd_StartWaitEvent, -4, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1,
    131163, (s32)evt_btl_camera_set_prilimit, 0, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 3, 2, 1,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_OnUnitFlag, -2, 16777216)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetTalkBodyId, -2, 1)
    CALL(btlevtcmd_SetBaseScale, -2, FLOAT(1.2998047f), FLOAT(1.2998047f), FLOAT(0.5f))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 2)
    CALL(btlevtcmd_SetUnitWork, -2, 2, 0)
    CALL(btlevtcmd_SetEventEntry, -2, PTR(battle_entry_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

EVT_BEGIN(zonbaba_damage_sub_event)
    CALL(btlevtcmd_GetDamagePartsId, -2, LW(11))
    IF_INT_EQUAL(LW(11), 1)
        CALL(btlevtcmd_AnimeChangePose, LW(10), 1, STRING("GNB_D_2"))
        ELSE
        CALL(btlevtcmd_AnimeChangePose, LW(10), 1, STRING("GNB_D_1"))
    END_IF
    CALL(btlevtcmd_GetDamage, LW(10), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetHitPos, LW(10), LW(11), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_BTL_ATTACK_MISS2"), LW(0), LW(1), LW(2), 0)
    END_IF
    WAIT_MS(1000)
    RETURN
EVT_END()

static s32 dead_event[] = {
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_X_1", 589915, (s32)btlevtcmd_snd_se_offset, -2,
    (s32)"SFX_BOSS_GNB_DOWN1", -250000000, 0, -250, 0, 0, -29999985, 65627,
    (s32)btlevtcmd_WaitAttackEnd, 131163, (s32)evt_btl_camera_set_prilimit, 1, 65627, (s32)evt_btl_camera_wait_move_end, 196699, (s32)evt_btl_camera_set_mode,
    1, 3, 131122, -29999999, 160, 131122, -29999998, 536,
    262235, (s32)btlevtcmd_GetStageAudienceAreaSize, -250000000, -29999995, -250000000, 131125, -29999999, -29999995,
    262235, (s32)btlevtcmd_GetStageSize, -250000000, -250000000, -29999995, 131125, -29999998, -29999995,
    131125, -29999998, 80, 131122, -29999995, -29999999, 131126, -29999995,
    37, 131122, -29999994, -29999998, 131126, -29999994, 511, 655451,
    (s32)evt_btl_camera_set_moveto, 1, 93, -29999999, -29999998, 93, -29999995, -29999994,
    30, 0, 65545, 90, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 196699,
    (s32)btlevtcmd_SetTalkPose, -2, (s32)"GNB_X_1", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"GNB_X_1", 327771,
    (s32)evt_msg_print, 2, (s32)"tik_boss_16", 0, -2, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1,
    196699, (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, -38,
    33, 1005, -38, 92, 13, 60, 0, 131163,
    (s32)evt_snd_sfxoff, -29999985, 589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_DOWN2", -250000000, 0,
    -250, 0, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"GNB_D_3", 65545, 42, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_H_1",
    65545, 1, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    131125, -30000000, 25, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_H_1", 107, 131122,
    -29999995, 100, 131122, -29999996, 120, 327771, (s32)btlevtcmd_SetRotateOffset, -2,
    0, -29999995, 0, 65541, 40, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, -29999996, 131126, -29999996, 3, 65545, 1,
    6, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 109,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999796, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131126, -30000000, 20, 131126, -29999998, 20,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 90, -1,
    196699, (s32)evt_snd_sfxon, (s32)"SFX_BOSS_GNB_DOWN3", 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"GNB_H_2", 393307, (s32)evt_btl_camera_shake_h, 1, 8, 0, 30, 13,
    65545, 10, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_H_3", 196699,
    (s32)btlevtcmd_GetExp, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreExp, -30000000, 131101, -30000000,
    1, 65541, -30000000, 6, 33, 65545, 60, 196699,
    (s32)btlevtcmd_KillUnit, -2, 1, 131163, (s32)evt_btl_camera_set_prilimit, 0, 2, 1,
};

static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108867)
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckActStatus, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_GetMaxHp, -2, LW(0))
        MULTIPLY(LW(0), 50)
        DIVIDE(LW(0), 100)
        CALL(btlevtcmd_GetHp, -2, LW(1))
        IF_INT_LESS_OR_EQUAL(LW(1), LW(0))
            CALL(btlevtcmd_SetUnitWork, -2, 0, 1)
        END_IF
        CASE_EQUAL(1)
        CALL(btlevtcmd_GetMaxHp, -2, LW(0))
        MULTIPLY(LW(0), 25)
        DIVIDE(LW(0), 100)
        CALL(btlevtcmd_GetHp, -2, LW(1))
        IF_INT_LESS_OR_EQUAL(LW(1), LW(0))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_SetUnitWork, -2, 0, 2)
            CALL(evt_msg_print, 2, STRING("tik_boss_15"), 0, -2)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
        END_IF
    END_SWITCH
    LABEL(99)
    RETURN
EVT_END()

static s32 fumituke_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 65540, 99, 33, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997,
    -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_W_2", 65545, 57, 110, 589915,
    (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_MOVE1", -250000000, 0, -300, 0, -30,
    -250000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125,
    -30000000, -300, 131125, -29999998, -30, 262235, (s32)_leg_smoke_effect, -30000000,
    -29999999, -29999998, 112, 393307, (s32)evt_btl_camera_shake_h, 0, 2, 0,
    10, 13, 65545, 46, 110, 589915, (s32)btlevtcmd_snd_se_offset, -2,
    (s32)"SFX_BOSS_GNB_MOVE1", -250000000, 0, -300, 0, 30, -250000000, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -30000000, -300,
    131125, -29999998, 30, 262235, (s32)_leg_smoke_effect, -30000000, -29999999, -29999998,
    112, 393307, (s32)evt_btl_camera_shake_h, 0, 2, 0, 10, 13,
    65545, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_A_3", 107,
    589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_ARM_UP1", -250000000, 0, -320, 30,
    30, -250000000, 65546, 700, 589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_ARM_DOWN1",
    -250000000, 0, -360, 50, 30, -250000000, 109, 65545,
    45, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256,
    -29999995, 65570, -29999995, 65579, 4, 65540, 90, 46,
    65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90,
    46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540,
    90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540,
    90, 65572, 1, 65540, 91, 46, 42, 65540,
    98, 46, 49, 65539, 90, 65540, 97, 65539,
    91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65540, 97, 65539,
    97, 110, 589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_MOVE1", -250000000, 0,
    -400, 0, -5, -250000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131125, -30000000, -400, 131125, -29999998, -5,
    262235, (s32)_leg_smoke_effect, -30000000, -29999999, -29999998, 112, 65545, 3,
    393307, (s32)evt_btl_camera_shake_h, 0, 2, 0, 10, 13, 65545,
    7, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 393307, (s32)evt_btl_camera_shake_h, 0, 8,
    0, 30, 13, 65545, 35, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"GNB_W_3", 65545, 51, 110, 589915, (s32)btlevtcmd_snd_se_offset, -2,
    (s32)"SFX_BOSS_GNB_MOVE1", -250000000, 0, -180, 0, 30, -250000000, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -30000000, -180,
    131125, -29999998, 30, 262235, (s32)_leg_smoke_effect, -30000000, -29999999, -29999998,
    112, 393307, (s32)evt_btl_camera_shake_h, 0, 2, 0, 10, 13,
    65545, 46, 110, 589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_MOVE1", -250000000,
    0, -100, 0, 30, -250000000, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 131125, -30000000, -100, 131125, -29999998,
    -30, 262235, (s32)_leg_smoke_effect, -30000000, -29999999, -29999998, 112, 393307,
    (s32)evt_btl_camera_shake_h, 0, 2, 0, 10, 13, 65545, 7,
    65539, 99, 2, 1,
};

static s32 kamituki_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 65540, 99, 33, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997,
    -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 107,
    589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_BITE1", -250000000, 0, -220, 80,
    0, -250000000, 65546, 250, 589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_BITE2",
    -250000000, 0, -260, 40, 0, -250000000, 109, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_A_2", 65545, 20, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 99, 46, 49,
    65539, 90, 65540, 97, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65539, 97, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 65539,
    99, 65545, 20, 2, 1,
};

s32 breath1_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 131163,
    (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_A_1", 131122, -29999990, 120,
    131122, -29999989, 30, 327771, (s32)btlevtcmd_GetPos, -2, -29999994, -29999993,
    -29999992, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -29999994, 360, 131125, -29999993,
    30, 327771, (s32)btlevtcmd_GetPos, -2, -29999988, -250000000, -250000000, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -2, -29999988, 360, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -29999988,
    -29999990, 107, 65546, 500, 589915, (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_NECK_UP1",
    -250000000, 0, -250, 0, 0, -250000000, 109, 107,
    65545, 105, 589915, (s32)btlevtcmd_snd_se_offset, -2, -29999987, -250000000, 0,
    -300, 0, 0, -250000000, 131125, -29999989, 45, 131126,
    -29999992, 10, 65570, -29999991, 65572, (s32)weapon_zonbaba_cold_attack, 983131, (s32)evt_eff,
    0, (s32)"gonbaba_breath", 3, -29999994, -29999993, -29999992, -229996928, -29999989,
    0, 0, 0, 0, 0, 0, 65572, (s32)weapon_zonbaba_confuze_attack,
    983131, (s32)evt_eff, 0, (s32)"gonbaba_breath", 4, -29999994, -29999993, -29999992,
    -229996928, -29999989, 0, 0, 0, 0, 0, 0,
    65572, (s32)weapon_zonbaba_sleep_attack, 983131, (s32)evt_eff, 0, (s32)"gonbaba_breath", 5, -29999994,
    -29999993, -29999992, -229996928, -29999989, 0, 0, 0, 0,
    0, 0, 65572, (s32)weapon_zonbaba_minimini_attack, 983131, (s32)evt_eff, 0, (s32)"gonbaba_breath",
    6, -29999994, -29999993, -29999992, -229996928, -29999989, 0, 0,
    0, 0, 0, 0, 49, 109, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -29999988, -250000000, -250000000, 131126, -29999988, -29999994,
    131098, -29999988, 0, 131127, -29999988, -1, 33, 131125,
    -29999988, 20, 131127, -29999988, -29999989, 131128, -29999988, -29999990,
    131125, -29999988, 105, 65545, -29999988, 131122, -29999990, 0,
    65539, 10, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65570, -29999995, 65579, 4, 65540, 90,
    46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540,
    90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    65540, 90, 65572, 1, 65540, 91, 46, 42,
    65540, 98, 46, 49, 65539, 90, 65540, 97,
    65539, 91, 131096, -29999990, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65540, 97, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy,
    -29999997, -29999996, 131097, -29999997, -1, 65545, 20, 131125,
    -29999990, 1, 65540, 10, 33, 65545, 84, 65539,
    99, 2, 1,
};

s32 breath2_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 131163,
    (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_A2_1", 65546, 833, 589915,
    (s32)btlevtcmd_snd_se_offset, -2, (s32)"SFX_BOSS_GNB_NECK_UP1", -250000000, 0, -250, 0, 0,
    -250000000, 65546, 1000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GNB_A2_3",
    589915, (s32)btlevtcmd_snd_se_offset, -2, -29999987, -250000000, 0, -300, 0,
    0, -250000000, 131122, -29999990, 120, 131122, -29999989, 30,
    327771, (s32)btlevtcmd_GetPos, -2, -29999994, -29999993, -29999992, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -2, -29999994, 360, 131125, -29999993, 30, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999988, -250000000, -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -29999988,
    360, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -29999988, -29999990, 107, 65545,
    20, 131125, -29999989, 45, 131126, -29999992, 10, 65570,
    -29999991, 65572, (s32)weapon_zonbaba_cold_attack, 983131, (s32)evt_eff, 0, (s32)"gonbaba_breath", 3,
    -29999994, -29999993, -29999992, -229996928, -29999989, 0, 0, 0,
    0, 0, 0, 65572, (s32)weapon_zonbaba_confuze_attack, 983131, (s32)evt_eff, 0,
    (s32)"gonbaba_breath", 4, -29999994, -29999993, -29999992, -229996928, -29999989, 0,
    0, 0, 0, 0, 0, 65572, (s32)weapon_zonbaba_sleep_attack, 983131,
    (s32)evt_eff, 0, (s32)"gonbaba_breath", 5, -29999994, -29999993, -29999992, -229996928,
    -29999989, 0, 0, 0, 0, 0, 0, 65572,
    (s32)weapon_zonbaba_minimini_attack, 983131, (s32)evt_eff, 0, (s32)"gonbaba_breath", 6, -29999994, -29999993,
    -29999992, -229996928, -29999989, 0, 0, 0, 0, 0,
    0, 49, 109, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999988,
    -250000000, -250000000, 131126, -29999988, -29999994, 131098, -29999988, 0,
    131127, -29999988, -1, 33, 131125, -29999988, 20, 131127,
    -29999988, -29999989, 131128, -29999988, -29999990, 131125, -29999988, 20,
    65545, -29999988, 131122, -29999990, 0, 65539, 10, 458843,
    (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995, 65570,
    -29999995, 65579, 4, 65540, 90, 46, 65572, 3,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572,
    6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572,
    1, 65540, 91, 46, 42, 65540, 98, 46,
    49, 65539, 90, 65540, 97, 65539, 91, 131096,
    -29999990, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 33, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995, 65540,
    97, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131097,
    -29999997, -1, 65545, 20, 131125, -29999990, 1, 65540,
    10, 33, 65545, 84, 65539, 99, 2, 1,
};

EVT_BEGIN(recover_event)
    CALL(btlevtcmd_GetUnitWork, -2, 2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_StatusWindowOnOff, 0)
        CALL(btlevtcmd_GetUnitWork, -2, 2, 1)
        CALL(evt_msg_print, 2, STRING("tik_boss_14"), 0, -2)
        CALL(btlevtcmd_StatusWindowOnOff, 1)
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SUBTRACT(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, -2, 1, LW(0))
    END_IF
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    CALL(btlevtcmd_RecoverHp, -2, 1, 20)
    CALL(btlevtcmd_GetHitPos, -2, 1, LW(0), LW(1), LW(2))
    ADD(LW(0), -27)
    ADD(LW(1), 15)
    ADD(LW(2), 10)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, LW(0), LW(1), LW(2), 20, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(40)
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
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_DrawLots, LW(0), 6, 25, 20, 10, 10, 10, 10)
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_VALUE(LW(9), PTR(weapon_zonbaba_fumituke_attack))
            CALL_CHILD(PTR(fumituke_attack_event))
            CASE_EQUAL(1)
            SET_VALUE(LW(9), PTR(weapon_zonbaba_kamituki_attack))
            CALL_CHILD(PTR(kamituki_attack_event))
            CASE_EQUAL(2)
            SET_VALUE(LW(13), STRING("SFX_BOSS_GNB_BREATH_COLD1"))
            SET_VALUE(LW(9), PTR(weapon_zonbaba_cold_attack))
            CALL_CHILD(PTR(breath2_attack_event))
            CASE_EQUAL(3)
            SET_VALUE(LW(13), STRING("SFX_BOSS_GNB_BREATH_CHANGE1"))
            SET_VALUE(LW(9), PTR(weapon_zonbaba_confuze_attack))
            CALL_CHILD(PTR(breath1_attack_event))
            CASE_EQUAL(4)
            SET_VALUE(LW(13), STRING("SFX_BOSS_GNB_BREATH_CHANGE1"))
            SET_VALUE(LW(9), PTR(weapon_zonbaba_sleep_attack))
            CALL_CHILD(PTR(breath2_attack_event))
            CASE_EQUAL(5)
            SET_VALUE(LW(13), STRING("SFX_BOSS_GNB_BREATH_CHANGE1"))
            SET_VALUE(LW(9), PTR(weapon_zonbaba_minimini_attack))
            CALL_CHILD(PTR(breath1_attack_event))
        END_SWITCH
        CASE_EQUAL(1)
        SET_VALUE(LW(1), 0)
        CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SET_VALUE(LW(1), 20)
        END_IF
        CALL(btlevtcmd_DrawLots, LW(0), 7, 25, 20, 10, 10, 10, 10, LW(1))
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_VALUE(LW(9), PTR(weapon_zonbaba_fumituke_attack))
            CALL_CHILD(PTR(fumituke_attack_event))
            CASE_EQUAL(1)
            SET_VALUE(LW(9), PTR(weapon_zonbaba_kamituki_attack))
            CALL_CHILD(PTR(kamituki_attack_event))
            CASE_EQUAL(2)
            SET_VALUE(LW(13), STRING("SFX_BOSS_GNB_BREATH_COLD1"))
            SET_VALUE(LW(9), PTR(weapon_zonbaba_cold_attack))
            CALL_CHILD(PTR(breath2_attack_event))
            CASE_EQUAL(3)
            SET_VALUE(LW(13), STRING("SFX_BOSS_GNB_BREATH_CHANGE1"))
            SET_VALUE(LW(9), PTR(weapon_zonbaba_confuze_attack))
            CALL_CHILD(PTR(breath1_attack_event))
            CASE_EQUAL(4)
            SET_VALUE(LW(13), STRING("SFX_BOSS_GNB_BREATH_CHANGE1"))
            SET_VALUE(LW(9), PTR(weapon_zonbaba_sleep_attack))
            CALL_CHILD(PTR(breath2_attack_event))
            CASE_EQUAL(5)
            SET_VALUE(LW(13), STRING("SFX_BOSS_GNB_BREATH_CHANGE1"))
            SET_VALUE(LW(9), PTR(weapon_zonbaba_minimini_attack))
            CALL_CHILD(PTR(breath1_attack_event))
            CASE_EQUAL(6)
            SET_VALUE(LW(9), PTR(weapon_zonbaba_recover))
            CALL_CHILD(PTR(recover_event))
        END_SWITCH
        CASE_EQUAL(2)
        SET_VALUE(LW(1), 0)
        CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SET_VALUE(LW(1), 50)
        END_IF
        CALL(btlevtcmd_DrawLots, LW(0), 7, 25, 20, 10, 10, 10, 10, LW(1))
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_VALUE(LW(9), PTR(weapon_zonbaba_fumituke_attack))
            CALL_CHILD(PTR(fumituke_attack_event))
            CASE_EQUAL(1)
            SET_VALUE(LW(9), PTR(weapon_zonbaba_kamituki_attack))
            CALL_CHILD(PTR(kamituki_attack_event))
            CASE_EQUAL(2)
            SET_VALUE(LW(13), STRING("SFX_BOSS_GNB_BREATH_COLD1"))
            SET_VALUE(LW(9), PTR(weapon_zonbaba_cold_attack))
            CALL_CHILD(PTR(breath2_attack_event))
            CASE_EQUAL(3)
            SET_VALUE(LW(13), STRING("SFX_BOSS_GNB_BREATH_CHANGE1"))
            SET_VALUE(LW(9), PTR(weapon_zonbaba_confuze_attack))
            CALL_CHILD(PTR(breath1_attack_event))
            CASE_EQUAL(4)
            SET_VALUE(LW(13), STRING("SFX_BOSS_GNB_BREATH_CHANGE1"))
            SET_VALUE(LW(9), PTR(weapon_zonbaba_sleep_attack))
            CALL_CHILD(PTR(breath2_attack_event))
            CASE_EQUAL(5)
            SET_VALUE(LW(13), STRING("SFX_BOSS_GNB_BREATH_CHANGE1"))
            SET_VALUE(LW(9), PTR(weapon_zonbaba_minimini_attack))
            CALL_CHILD(PTR(breath1_attack_event))
            CASE_EQUAL(6)
            SET_VALUE(LW(9), PTR(weapon_zonbaba_recover))
            CALL_CHILD(PTR(recover_event))
        END_SWITCH
    END_SWITCH
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

struct EffectEntry* effKemuri9N64Entry(s32 type, s32 arg1, s32 arg2, f32 x, f32 y, f32 z, f32 arg6, f32 arg7);

static USER_FUNC(_leg_smoke_effect) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    effKemuri9N64Entry(1, 18, 90, x, y, z, 60.0f, 0.0f);
    return EVT_RETURN_DONE;
}
