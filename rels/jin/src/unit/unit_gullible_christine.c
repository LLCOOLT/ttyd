#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "system.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_msg.h"
#include "evt/evt_sub.h"
#include "unit/party/unit_party_christine.h"

USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveto);
static USER_FUNC(_krb_get_dir);

__declspec(section ".data") u64 fd_gullible_christine_negone_one_374;
__declspec(section ".data") s32 fd_gullible_christine_neg_one_382[1];
__declspec(section ".data") s32 fd_gullible_christine___local_PI_383[1];
__declspec(section ".data") s32 fd_gullible_christine___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gullible_christine_one_negone_373;
__declspec(section ".data") s32 fd_gullible_christine___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gullible_christine_one_381[1];
__declspec(section ".data") u64 fd_gullible_christine_negone_one_360;
__declspec(section ".data") s32 fd_gullible_christine_neg_one_365[1];
__declspec(section ".data") s32 fd_gullible_christine___local_PI_366[1];
__declspec(section ".data") s32 fd_gullible_christine___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gullible_christine_one_negone_359;
__declspec(section ".data") s32 fd_gullible_christine___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gullible_christine_one_364[1];
BattleUnitKind unit_gullible_christine;
static s32 enemyWeapon_ChristineNormalAttack[48];
static __declspec(section ".data") BattleUnitDefense defence_christine;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_christine;
static __declspec(section ".data") StatusVulnerability regist_christine;
static __declspec(section ".data") BattleDataEntry data_table_christine[2];
static BattleUnitKindPart parts_christine[1];
static s32 fmario_zoom_christine[19];
static s32 gparty_zoom_christine[19];
static s32 init_event_christine[42];
s32 damage_event_christine[22];
static s32 dead_event_christine[147];
static s32 attack_event_christine[690];
static __declspec(section ".data") s32 wait_event_christine[7];

__declspec(section ".data") u64 fd_gullible_christine_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gullible_christine_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gullible_christine___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gullible_christine___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gullible_christine_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gullible_christine___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gullible_christine_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gullible_christine_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gullible_christine_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gullible_christine___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gullible_christine___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gullible_christine_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gullible_christine___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gullible_christine_one_364[] = {
    1065353216,
};

BattleUnitKind unit_gullible_christine = {
    80,
    "btl_un_gullible_christine",
    10,
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
    28,
    24,
    8,
    24,
    0.0f,
    14.0f,
    0.0f,
    0,
    0,
    0.0f,
    40.0f,
    0.0f,
    14.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    14.0f,
    0.0f,
    0.0f,
    14.0f,
    15.6f,
    0.0f,
    0.0f,
    14.0f,
    0.0f,
    28.0f,
    28.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_PARTY_DAMAGE1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x10000000,
    &regist_christine,
    1,
    parts_christine,
    init_event_christine,
    data_table_christine,
};

static s32 enemyWeapon_ChristineNormalAttack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerFromGulliblePartyAttackLv,
    1, 2, 3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, 0, 86023, 12, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") BattleUnitDefense defence_christine = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_christine = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist_christine = {60, 80, 70, 100, 70, 100, 100, 70, 100, 70, 100, 70, 100, 90, 70, 0, 0, 100, 70, 100, 100, 0};

static __declspec(section ".data") BattleDataEntry data_table_christine[] = {
    {49, dead_event_christine},
    {0, NULL},
};

static BattleUnitKindPart parts_christine[] = {
    {1, "btl_un_christine", "c_pkr", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence_christine, &defence_attr_christine, 0x9, 0, pose_table_christine_stay},
};

static EVT_BEGIN(fmario_zoom_christine)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 90, 58, 228, 90, 38, -20, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(gparty_zoom_christine)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 130, 58, 228, 130, 38, -20, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(init_event_christine)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_christine))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_christine))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event_christine))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 6, 12, 16)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 9, 3)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(damage_event_christine)
    CALL(btlevtcmd_CheckDamageCode, -2, 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GW(20), 1)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static s32 dead_event_christine[] = {
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999997, -29999996, -29999995, 131122, -29999994, 1, 131096,
    -30000000, -29999997, 131096, -29999999, -29999996, 131096, -29999998, -29999995,
    131122, -29999994, 0, 33, 33, 33, 131096, -29999994,
    1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 40, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 33, 65545,
    1, 65627, (s32)btlevtcmd_WaitAttackEnd, 65570, -49999981, 65572, 0, 65630,
    (s32)gparty_zoom_christine, 327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_26_03_kur", 0, -2, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1",
    -250000000, 0, -250000000, 65546, 500, 65630, (s32)fmario_zoom_christine, 327771,
    (s32)evt_msg_print, 2, (s32)"stg4_jin_26_04", 0, -49999984, 65546, 200, 65572,
    1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_D_3", 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_PARTY_BATTLE_DIE1", -250000000, 0, -250000000, 65541, 0, 131096,
    -49999981, 2, 7, 33, 65545, 1, 6, 65572,
    2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_D_3", 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_PARTY_BATTLE_DIE1", -250000000, 0, -250000000, 49, 196699, (s32)btlevtcmd_KillUnit,
    -2, 1, 131122, -49999980, 2, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 2, 1,
};

static s32 attack_event_christine[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 131122, -29999988,
    (s32)enemyWeapon_ChristineNormalAttack, 327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988,
    262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997, -29999996, 131096, -29999997, -1,
    65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235, (s32)btlevtcmd_AttackDeclare,
    -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2,
    -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition, -2, -29999997, -29999996, -30000000, -29999999,
    -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998, 1,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 458843, (s32)btlevtcmd_GetMoveFrame, -2,
    -30000000, -29999999, -29999998, 0, -29999986, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, -29999986, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 327771, (s32)btlevtcmd_DrawLots, -30000000, 2, 80, 20,
    65570, -30000000, 65572, 0, 131122, -29999989, 0, 65572,
    1, 196699, (s32)evt_sub_random, 4, -29999989, 131125, -29999989, 1,
    49, 131122, -29999990, 0, 65539, 10, 131101, -29999990,
    1, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988, 1048832,
    -29999995, 32, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988,
    256, -29999995, 33, 65570, -29999995, 65579, 2, 65579,
    3, 65579, 6, 65579, 4, 46, 65572, 1,
    42, 65546, 1000, 49, 131100, -29999990, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_A_2B", 65545, 20, 33, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_J_1A", 107, 65545, 15, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_KURI_ATTACK1", -250000000, 0, -250000000, 109, 327771,
    (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 131101, -29999990, -29999989,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125,
    -29999998, 5, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 14, 0,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 110, 65545,
    15, 65541, 6, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000, 131127,
    -30000000, -30, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, -30000000,
    65545, 1, 6, 112, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000,
    -29999999, -29999998, 36, 3, -1, 32, 327771, (s32)btlevtcmd_SetRotateOffset,
    -2, 0, 14, 0, 110, 327771, (s32)btlevtcmd_GetPosFloat, -2,
    -29999995, -29999994, -29999993, 131122, -29999992, 0, 65541, 36,
    327771, (s32)btlevtcmd_GetPosFloat, -2, -29999988, -29999987, -29999986, 393307, (s32)_krb_get_dir,
    -29999995, -29999994, -29999988, -29999987, -29999992, 327771, (s32)btlevtcmd_GetRotate, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetRotate, -2, -30000000, -29999999,
    -29999992, 131124, -29999995, -29999988, 131124, -29999994, -29999987, 65545,
    1, 6, 112, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 131125, -29999998, 5, 524379, (s32)btlevtcmd_MarioJumpPosition, -2,
    -30000000, -29999999, -29999998, 36, 0, -1, 33, 131097,
    -29999995, 1, 131096, -29999995, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 33, 131096, -29999995, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 33, 131096, -29999995, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 33, 131163, (s32)btlevtcmd_JumpContinue, -2, 327771, (s32)btlevtcmd_SetRotateOffset, -2,
    0, 0, 0, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_S_1", 196699, (s32)btlevtcmd_SetFallAccel,
    -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_MoveDirectionAdd, -2, -30000000, 30, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 20, -1, 262235, (s32)btlevtcmd_MoveDirectionAdd, -2,
    -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    10, -1, 65546, 500, 65540, 95, 33, 327771,
    (s32)btlevtcmd_SetScale, -2, -229998976, -229998976, -229998976, 65541, 4, 327771,
    (s32)btlevtcmd_AddScale, -2, -229999919, -230000122, 0, 65545, 1, 6,
    327771, (s32)btlevtcmd_SetScale, -2, -229998976, -229998976, -229998976, 107, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 0, 196699, (s32)evt_btl_camera_set_zoom, 0, -229833600, 65545,
    10, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 109, 131098, -29999990, -29999989, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 0,
    -29999995, 131125, -29999990, 1, 65540, 10, 32, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999988, 256, -29999995, 33, 65539, 90, 110, 327771,
    (s32)btlevtcmd_GetRotate, -2, -250000000, -250000000, -29999994, 131098, -29999994, 0,
    131127, -29999994, -1, 33, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000,
    131127, -29999994, -30000000, 131128, -29999994, 15, 131122, -29999993,
    15, 65539, 20, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0,
    -29999994, 131126, -29999993, 1, 65545, 1, 131101, -29999993,
    1, 65540, 20, 33, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 112, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -250000000, -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12,
    -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 8, -1, 65539, 95,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

static USER_FUNC(_krb_get_dir) {
    s32* args = event->args;
    f32 x1 = evtGetFloat(event, args[0]);
    f32 z1 = evtGetFloat(event, args[1]);
    f32 x2 = evtGetFloat(event, args[2]);
    f32 z2 = evtGetFloat(event, args[3]);
    s32 dir = evtGetValue(event, args[4]);
    f32 dx = x2 - x1;
    f32 dz = z2 - z1;

    if (dx == 0.0f && dz == 0.0f) {
        evtSetValue(event, args[4], dir);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[4], angleABf(dx, dz, 0.0f, 0.0f));
    return EVT_RETURN_DONE;
}

static __declspec(section ".data") s32 wait_event_christine[] = {
    196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 2, 1, 0,
};

