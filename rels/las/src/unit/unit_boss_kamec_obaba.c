#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_sub.h"

EffectEntry* effStardustEntry(s32 type, s32 count, f32 x, f32 y, f32 z, f32 width, f32 height, s32 time);
EffectEntry* effMagic1N64Entry(s32 type, s32 arg1, f32 x, f32 y, f32 z, f32 arg5, f32 arg6, f32 arg7);
EffectEntry* effThunderflareN64Entry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_AttackDeclare);
USER_FUNC(btlevtcmd_CalculateFaceDirection);
USER_FUNC(btlevtcmd_ChangeFaceDirection);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_CheckToken);
USER_FUNC(btlevtcmd_ChoiceSamplingEnemy);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetHp);
USER_FUNC(btlevtcmd_GetMaxHp);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetTotalDamage);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_PayWeaponCost);
USER_FUNC(btlevtcmd_RecoverHp);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_ResultACDefence);
USER_FUNC(btlevtcmd_SamplingEnemy);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetStayPose);
USER_FUNC(btlevtcmd_SetTalkPose);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(btlevtcmd_StopWaitEvent);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(btlevtcmd_WaitGuardMove);
USER_FUNC(btlevtcmd_WeaponAftereffect);
USER_FUNC(btlevtcmd_get_turn);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveto);
USER_FUNC(evt_eff);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_sub_random);
USER_FUNC(eff_magic_support);
static USER_FUNC(eff_magic_get_posX);
static USER_FUNC(eff_magic);
static USER_FUNC(eff_staff);

__declspec(section ".data") u64 fd_boss_kamec_obaba_negone_one_374;
__declspec(section ".data") s32 fd_boss_kamec_obaba_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_kamec_obaba___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_kamec_obaba___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_kamec_obaba_one_negone_373;
__declspec(section ".data") s32 fd_boss_kamec_obaba___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_kamec_obaba_one_381[1];
__declspec(section ".data") u64 fd_boss_kamec_obaba_negone_one_360;
__declspec(section ".data") s32 fd_boss_kamec_obaba_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_kamec_obaba___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_kamec_obaba___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_kamec_obaba_one_negone_359;
__declspec(section ".data") s32 fd_boss_kamec_obaba___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_kamec_obaba_one_364[1];
s32 weapon_kamec_obaba_attack_magic[48];
s32 weapon_kamec_obaba_dekadeka_magic[48];
s32 weapon_kamec_obaba_biribiri_magic[48];
s32 weapon_kamec_obaba_katikati_magic[48];
s32 weapon_kamec_obaba_trans_magic[48];
s32 weapon_kamec_obaba_recover_magic[48];
BattleUnitKind unit_boss_kamec_obaba;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[17];
static PoseTableEntry pose_table_sky[17];
static __declspec(section ".data") PoseTableEntry pose_table_dead[3];
static __declspec(section ".data") BattleDataEntry data_table[2];
static BattleUnitKindPart parts[2];
static s32 kamec_obaba_zoom[40];
static s32 init_event[56];
static s32 damage_event[74];
static s32 dmg_fall_event[149];
static s32 dead_event[155];
static s32 phase_event[216];
static s32 attack_event[352];
static s32 ground_magic_common_event1[87];
static s32 ground_magic_common_event2[76];
static s32 sky_magic_common_event[76];
static s32 magic_common_event1[27];
static s32 magic_common_event2[16];
static s32 start_avoid[26];
static s32 attack_magic_event[269];
s32 magic_select_pri_obaba[52];
s32 magic_select_pri_koopa[52];
static s32 dekadeka_magic_event[73];
static __declspec(section ".data") s32 katikati_magic_event[4];
static __declspec(section ".data") s32 biribiri_magic_event[4];
static __declspec(section ".data") s32 trans_magic_event[4];
static s32 recover_magic_event[90];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_boss_kamec_obaba_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_kamec_obaba_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_kamec_obaba___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_kamec_obaba___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_kamec_obaba_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_kamec_obaba___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_kamec_obaba_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_kamec_obaba_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_kamec_obaba_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_kamec_obaba___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_kamec_obaba___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_kamec_obaba_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_kamec_obaba___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_kamec_obaba_one_364[] = {
    1065353216,
};

s32 weapon_kamec_obaba_attack_magic[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 71, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_kamec_obaba_dekadeka_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 8, 2047, -2147483648,
    0, 0, 0, 0, 100, 50462720, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_kamec_obaba_biribiri_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 8, 2047, -2147483648,
    0, 0, 100, 50331648, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_kamec_obaba_katikati_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 8, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 6554371, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_kamec_obaba_trans_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 8, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1677918208, 0, 0, 100, 0, 0,
};

s32 weapon_kamec_obaba_recover_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 8, 2047, 5376,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

BattleUnitKind unit_boss_kamec_obaba = {
    145,
    "btl_un_kamec_obaba",
    50,
    0,
    1,
    1,
    48,
    0,
    0,
    100,
    0,
    50,
    6,
    42,
    42,
    7,
    42,
    0.0f,
    21.0f,
    0.0f,
    0,
    0,
    20.0f,
    20.0f,
    0.0f,
    21.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    0.0f,
    21.0f,
    27.3f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    42.0f,
    42.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_KAMEBABA_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4,
    &regist,
    2,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {40, 40, 60, 100, 40, 100, 100, 40, 100, 60, 100, 60, 100, 80, 40, 0, 0, 100, 40, 100, 100, 5};

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
    {31, "D_1"},
    {39, "D_1"},
    {42, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static PoseTableEntry pose_table_sky[] = {
    {1, "N_2"},
    {2, "Y_2"},
    {9, "Y_2"},
    {5, "K_2"},
    {4, "X_2"},
    {3, "X_2"},
    {28, "S_2"},
    {29, "Q_2"},
    {30, "Q_2"},
    {31, "D_2"},
    {39, "D_2"},
    {42, "R_2"},
    {40, "W_2"},
    {56, "X_2"},
    {57, "X_2"},
    {65, "T_2"},
    {69, "S_2"},
};

static __declspec(section ".data") PoseTableEntry pose_table_dead[] = {
    {28, "D_3"},
    {39, "D_3"},
    {69, "D_3"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_kamec_obaba", "c_kamek_bb", 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 0.0f, 0.0f, 40.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x600009, 0, pose_table_sky},
    {2, "btl_un_kamec_obaba", "c_kamek_bb", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

static EVT_BEGIN(kamec_obaba_zoom)
    CALL(btlevtcmd_GetUnitWork, GW(9), 0, LW(1))
    CALL(evt_btl_camera_set_mode, 0, 3)
    IF_INT_EQUAL(LW(1), 1)
        CALL(evt_btl_camera_set_moveto, 0, 135, 106, 296, 135, 55, -402, 30, 11)
        ELSE
        CALL(evt_btl_camera_set_moveto, 0, 140, 34, 296, 140, 50, -402, 30, 11)
    END_IF
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 1)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 2, 0)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_BOSS_KAMEBABA_MOVE1L"), STRING("SFX_BOSS_KAMEBABA_MOVE1R"), 0, 15, 15)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_BOSS_KAMEBABA_MOVE1L"), STRING("SFX_BOSS_KAMEBABA_MOVE1R"), 0, 8, 8)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL(btlevtcmd_CheckStatus, -2, 27, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckDamageCode, -2, 256, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, LW(10), 0, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_GetTotalDamage, LW(10), LW(1))
        CALL(btlevtcmd_GetUnitWork, LW(10), 1, LW(0))
        ADD(LW(0), LW(1))
        CALL(btlevtcmd_SetUnitWork, LW(10), 1, LW(0))
        IF_INT_GREATER(LW(0), 1)
            CALL(btlevtcmd_WaitAttackEnd)
            CALL(btlevtcmd_StopWaitEvent, -2)
            CALL_CHILD(PTR(dmg_fall_event))
            CALL(btlevtcmd_StartWaitEvent, -2)
        END_IF
    END_IF
    LABEL(99)
    RETURN
EVT_END()

static s32 dmg_fall_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 196699, (s32)btlevtcmd_OffAttribute,
    -2, 4, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1, 2097152, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, 1, 4194304, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"D_2", 65546, 500, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table,
    196699, (s32)btlevtcmd_SetTalkPoseType, -2, 65, 196699, (s32)btlevtcmd_SetStayPoseType, -2, 43,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 39, 107, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_SetPartsPos, -2, 2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"H_1",
    262235, (s32)btlevtcmd_SetAlpha, -2, 2, 255, 262235, (s32)btlevtcmd_OffPartsAttribute, -2,
    2, 16777216, 65545, 80, 327771, (s32)evt_sub_intpl_init, 0, 255,
    0, 30, 65541, 30, 196699, (s32)evt_sub_intpl_get_value_para, -29999999, -29999998,
    262235, (s32)btlevtcmd_SetAlpha, -2, 2, -29999999, 65545, 1, 6,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, 2, 16777216, 109, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_FALL1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229998976, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 10, -1, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KAMEBABA_DOWN1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_SetHomePos,
    -2, -30000000, 0, -29999998, 65546, 500, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 0, 0, 2, 1,
};

static EVT_BEGIN(dead_event)
    DEBUG_PUT_MSG(STRING("カメックオババ　死亡"))
    SET_VALUE(GW(11), 1)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_WaitAttackEnd)
    DEBUG_PUT_MSG(STRING("カメックオババ　死亡イベント開始"))
    CALL(btlevtcmd_GetUnitWork, LW(10), 0, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(dmg_fall_event))
    END_IF
    SWITCH(GW(10))
        CASE_EQUAL(0)
        DEBUG_PUT_MSG(STRING("カメックオババ　死亡イベント　クッパ生存"))
        CALL(btlevtcmd_StatusWindowOnOff, 0)
        CALL_CHILD(PTR(kamec_obaba_zoom))
        CALL(btlevtcmd_SetTalkPose, -2, STRING("T_3"))
        CALL(btlevtcmd_SetStayPose, -2, STRING("D_3"))
        CALL(evt_msg_print, 2, STRING("stg8_las_100_01"), 0, -2)
        WAIT_MS(200)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("D_3"))
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_dead))
        SET_VALUE(GW(11), 2)
        SET_VALUE(LW(10), -2)
        CALL_CHILD(PTR(subsetevt_dead_core_nospin_norotate))
        CALL(btlevtcmd_StatusWindowOnOff, 1)
        CASE_EQUAL(1)
        DEBUG_PUT_MSG(STRING("カメックオババ　死亡イベント　同時に死亡"))
        LOOP(0)
            IF_INT_EQUAL(GW(10), 2)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("D_3"))
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_dead))
        SET_VALUE(GW(11), 2)
        SET_VALUE(LW(10), -2)
        CALL_CHILD(PTR(subsetevt_dead_core_nospin_norotate))
        CASE_EQUAL(2)
        DEBUG_PUT_MSG(STRING("カメックオババ　死亡イベント　クッパ死亡"))
        CALL(btlevtcmd_StatusWindowOnOff, 0)
        CALL_CHILD(PTR(kamec_obaba_zoom))
        CALL(btlevtcmd_SetTalkPose, -2, STRING("D_1"))
        CALL(btlevtcmd_SetStayPose, -2, STRING("D_1"))
        CALL(evt_msg_print, 2, STRING("stg8_las_100_03"), 0, -2)
        WAIT_MS(200)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("D_3"))
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_dead))
        SET_VALUE(GW(11), 2)
        SET_VALUE(LW(10), -2)
        CALL_CHILD(PTR(subsetevt_dead_core_nospin_norotate))
        CALL(btlevtcmd_StatusWindowOnOff, 1)
    END_SWITCH
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

static s32 phase_event[] = {
    196699, (s32)btlevtcmd_CheckPhase, -30000000, 67108865, 131096, -30000000, 0, 65540,
    99, 33, 131163, (s32)btlevtcmd_get_turn, -30000000, 131096, -30000000, 1,
    65540, 99, 33, 262235, (s32)btlevtcmd_CheckStatus, -2, 27, -30000000,
    131096, -30000000, 1, 65540, 99, 33, 196699, (s32)btlevtcmd_CheckActStatus,
    -2, -30000000, 131096, -30000000, 0, 65540, 99, 33,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096, -30000000, 1,
    65540, 99, 33, 262235, (s32)btlevtcmd_AddUnitWork, -2, 2, 1,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -30000000, 131098, -30000000, 3,
    65540, 99, 33, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, 1, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229994880, 524379, (s32)btlevtcmd_MovePosition, -2, 300, -29999999, -29999998, 0,
    -1, 0, 65545, 60, 196699, (s32)btlevtcmd_OnAttribute, -2, 4,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1, 2097152, 262235, (s32)btlevtcmd_OnPartsAttribute, -2,
    1, 4194304, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 65546,
    500, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table_sky, 196699, (s32)btlevtcmd_SetTalkPoseType,
    -2, 65, 196699, (s32)btlevtcmd_SetStayPoseType, -2, 43, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 40, 65647, -29999985, 65541, 0, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KAMEBABA_MOVE2", -250000000, 0, -250000000, 65546, 166,
    6, 112, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -1, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -2, -30000000,
    40, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, 40, -29999998, 60, 0,
    4, 0, -1, 327771, (s32)btlevtcmd_SetHomePos, -2, -30000000, 40,
    -29999998, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 69, 65631, -29999985,
    65546, 500, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 1, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 1, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2,
    0, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 65539, 99, 2, 1,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_get_turn, LW(0))
    DEBUG_PUT_REG(LW(0))
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LW(9), PTR(weapon_kamec_obaba_attack_magic))
        CALL_CHILD(PTR(attack_magic_event))
        GOTO(99)
    END_IF
    SET_VALUE(LW(5), 0)
    CALL(btlevtcmd_GetHp, -2, LW(0))
    CALL(btlevtcmd_GetMaxHp, -2, LW(1))
    MULTIPLY(LW(0), 100)
    DIVIDE(LW(0), LW(1))
    SWITCH(LW(0))
        CASE_LESS(25)
        SET_VALUE(LW(5), 25)
        CASE_LESS(50)
        SET_VALUE(LW(5), 10)
        CASE_LESS(75)
        SET_VALUE(LW(5), 5)
    END_SWITCH
    SET_VALUE(LW(6), 0)
    IF_INT_EQUAL(GW(10), 0)
        CALL(btlevtcmd_GetHp, GW(8), LW(0))
        CALL(btlevtcmd_GetMaxHp, GW(8), LW(1))
        MULTIPLY(LW(0), 100)
        DIVIDE(LW(0), LW(1))
        SWITCH(LW(0))
            CASE_LESS(25)
            SET_VALUE(LW(6), 25)
            CASE_LESS(50)
            SET_VALUE(LW(6), 10)
            CASE_LESS(75)
            SET_VALUE(LW(6), 5)
        END_SWITCH
    END_IF
    SET_VALUE(LW(7), 0)
    SET_VALUE(LW(8), 0)
    SET_VALUE(LW(10), 0)
    SET_VALUE(LW(11), 0)
    SET_VALUE(LW(9), PTR(weapon_kamec_obaba_dekadeka_magic))
    CALL_CHILD(PTR(magic_select_pri_obaba))
    IF_INT_NOT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckStatus, LW(3), 6, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            SET_VALUE(LW(8), 10)
        END_IF
        CALL(btlevtcmd_CheckStatus, LW(3), 18, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            SET_VALUE(LW(10), 10)
        END_IF
    END_IF
    SET_VALUE(LW(13), LW(3))
    SET_VALUE(LW(14), LW(4))
    CALL_CHILD(PTR(magic_select_pri_koopa))
    IF_INT_NOT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckStatus, LW(3), 14, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            SET_VALUE(LW(7), 10)
        END_IF
        SET_VALUE(LW(11), 10)
    END_IF
    LABEL(10)
    SET_VALUE(LW(1), LW(5))
    ADD(LW(1), LW(6))
    ADD(LW(1), LW(7))
    ADD(LW(1), LW(8))
    ADD(LW(1), LW(10))
    ADD(LW(1), LW(11))
    ADD(LW(1), 50)
    SUBTRACT(LW(1), 1)
    CALL(evt_sub_random, LW(1), LW(0))
    SET_VALUE(LW(1), LW(5))
    ADD(LW(1), LW(6))
    IF_INT_LESS(LW(0), LW(1))
        SET_VALUE(LW(9), PTR(weapon_kamec_obaba_recover_magic))
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
        CALL(btlevtcmd_GetHp, LW(3), LW(0))
        CALL(btlevtcmd_GetMaxHp, LW(3), LW(1))
        IF_INT_EQUAL(LW(0), LW(1))
            GOTO(10)
        END_IF
        CALL_CHILD(PTR(recover_magic_event))
        GOTO(99)
    END_IF
    ADD(LW(1), LW(7))
    IF_INT_LESS(LW(0), LW(1))
        SET_VALUE(LW(9), PTR(weapon_kamec_obaba_katikati_magic))
        CALL_CHILD(PTR(katikati_magic_event))
        GOTO(99)
    END_IF
    ADD(LW(1), LW(8))
    IF_INT_LESS(LW(0), LW(1))
        SET_VALUE(LW(9), PTR(weapon_kamec_obaba_biribiri_magic))
        SET_VALUE(LW(3), LW(13))
        SET_VALUE(LW(4), LW(14))
        CALL_CHILD(PTR(biribiri_magic_event))
        GOTO(99)
    END_IF
    ADD(LW(1), LW(10))
    IF_INT_LESS(LW(0), LW(1))
        SET_VALUE(LW(9), PTR(weapon_kamec_obaba_trans_magic))
        SET_VALUE(LW(3), LW(13))
        SET_VALUE(LW(4), LW(14))
        CALL_CHILD(PTR(trans_magic_event))
        GOTO(99)
    END_IF
    ADD(LW(1), LW(11))
    IF_INT_LESS(LW(0), LW(1))
        SET_VALUE(LW(9), PTR(weapon_kamec_obaba_dekadeka_magic))
        CALL_CHILD(PTR(dekadeka_magic_event))
        GOTO(99)
        ELSE
        SET_VALUE(LW(9), PTR(weapon_kamec_obaba_attack_magic))
        CALL_CHILD(PTR(attack_magic_event))
        GOTO(99)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 ground_magic_common_event1[] = {
    110, 65541, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KAMEBABA_MAGIC1", -250000000,
    0, -250000000, 65545, 40, 6, 112, 110, 131163,
    (s32)eff_staff, -2, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A",
    65545, 60, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KAMEBABA_MAGIC4", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B", 65545, 20,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1C", 65545, 30, 110,
    65545, 10, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KAMEBABA_MAGIC8", -250000000, 0,
    -250000000, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1D", 65545,
    20, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1E", 131097, -29999991,
    (s32)weapon_kamec_obaba_attack_magic, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KAMEBABA_MAGIC2", -250000000, 0, -250000000,
    196699, (s32)eff_magic_support, -2, 0, 33, 2, 1,
};

static s32 ground_magic_common_event2[] = {
    110, 65541, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KAMEBABA_MAGIC1", -250000000,
    0, -250000000, 65545, 40, 6, 112, 110, 131163,
    (s32)eff_staff, -2, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A",
    65545, 60, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KAMEBABA_MAGIC6", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2A", 65545, 40,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KAMEBABA_MAGIC7", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2B", 65545, 20, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"A_2C", 131097, -29999991, (s32)weapon_kamec_obaba_attack_magic, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_KAMEBABA_MAGIC2", -250000000, 0, -250000000, 196699, (s32)eff_magic_support, -2,
    1, 33, 2, 1,
};

static s32 sky_magic_common_event[] = {
    110, 65541, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KAMEBABA_MAGIC1", -250000000,
    0, -250000000, 65545, 40, 6, 112, 110, 131163,
    (s32)eff_staff, -2, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3A",
    65545, 60, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KAMEBABA_MAGIC8", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3B", 65545, 35,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KAMEBABA_MAGIC7", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3C", 65545, 15, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"A_3D", 131097, -29999991, (s32)weapon_kamec_obaba_attack_magic, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_KAMEBABA_MAGIC2", -250000000, 0, -250000000, 196699, (s32)eff_magic_support, -2,
    1, 33, 2, 1,
};

static EVT_BEGIN(magic_common_event1)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitId, -2, LW(13))
        IF_INT_NOT_EQUAL(LW(3), LW(13))
            CALL_CHILD(PTR(ground_magic_common_event1))
            ELSE
            CALL_CHILD(PTR(ground_magic_common_event2))
        END_IF
        ELSE
        CALL_CHILD(PTR(sky_magic_common_event))
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(magic_common_event2)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(ground_magic_common_event2))
        ELSE
        CALL_CHILD(PTR(sky_magic_common_event))
    END_IF
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

static s32 attack_magic_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996,
    65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 65630, (s32)magic_common_event1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KAMEBABA_MAGIC3_2",
    -250000000, 0, -250000000, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 458843,
    (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995, 65570,
    -29999995, 65579, 4, 65540, 90, 46, 65572, 3,
    65540, 90, 46, 65572, 6, 65540, 90, 65572,
    2, 65540, 90, 65572, 1, 65540, 91, 46,
    42, 65540, 98, 46, 65539, 90, 110, 65545,
    1, 65541, 0, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000, 131096,
    -30000000, -1, 196699, (s32)eff_magic_get_posX, -2, -30000000, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -29999994, -29999993, -29999992, 131100, -30000000, -29999994,
    65630, (s32)start_avoid, 7, 33, 32, 196699, (s32)eff_magic_get_posX, -2,
    -30000000, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999994, -29999993, -29999992,
    131101, -30000000, -29999994, 65630, (s32)start_avoid, 7, 33, 33,
    65545, 1, 6, 112, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131125, -30000000, -57, 131125, -29999999, 10,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999990, -29999989, -29999988, 262235,
    (s32)btlevtcmd_GetStageSize, -29999990, -250000000, -250000000, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000,
    131127, -29999990, -30000000, 131126, -29999989, 5, 393307, (s32)eff_magic,
    -2, -29999990, -29999989, -29999988, 60, 65545, 60, 65540,
    98, 65539, 91, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131125, -30000000, -57, 131125, -29999999, 10, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999990, -29999989, -29999988, 393307, (s32)eff_magic,
    -2, -29999990, -29999989, -29999988, 45, 65545, 45, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999991, 256, -29999995, 65540, 98, 65539, 98, 65545,
    30, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 65539, 99,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
};

EVT_BEGIN(magic_select_pri_obaba)
    SET_VALUE(LW(5), 0)
    SET_VALUE(LW(6), 0)
    IF_INT_EQUAL(GW(10), 0)
        SET_VALUE(LW(5), 25)
    END_IF
    IF_INT_EQUAL(GW(11), 0)
        SET_VALUE(LW(6), 75)
    END_IF
    SET_VALUE(LW(1), LW(5))
    ADD(LW(1), LW(6))
    SUBTRACT(LW(1), 1)
    CALL(evt_sub_random, LW(1), LW(0))
    IF_INT_LESS(LW(0), LW(5))
        SET_VALUE(LW(3), GW(8))
        SET_VALUE(LW(4), 1)
        ELSE
        SET_VALUE(LW(3), -2)
        SET_VALUE(LW(4), 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(magic_select_pri_koopa)
    SET_VALUE(LW(5), 0)
    SET_VALUE(LW(6), 0)
    IF_INT_EQUAL(GW(10), 0)
        SET_VALUE(LW(5), 75)
    END_IF
    IF_INT_EQUAL(GW(11), 0)
        SET_VALUE(LW(6), 25)
    END_IF
    SET_VALUE(LW(1), LW(5))
    ADD(LW(1), LW(6))
    SUBTRACT(LW(1), 1)
    CALL(evt_sub_random, LW(1), LW(0))
    IF_INT_LESS(LW(0), LW(5))
        SET_VALUE(LW(3), GW(8))
        SET_VALUE(LW(4), 1)
        ELSE
        SET_VALUE(LW(3), -2)
        SET_VALUE(LW(4), 1)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(dekadeka_magic_event)
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(15))
    CALL_CHILD(PTR(magic_common_event1))
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(5))
    WAIT_FRAMES(30)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(katikati_magic_event)
    CALL_CHILD(PTR(dekadeka_magic_event))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(biribiri_magic_event)
    CALL_CHILD(PTR(dekadeka_magic_event))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(trans_magic_event)
    CALL_CHILD(PTR(dekadeka_magic_event))
    RETURN
EVT_END()

static EVT_BEGIN(recover_magic_event)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(15))
    CALL_CHILD(PTR(magic_common_event1))
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_RecoverHp, LW(3), LW(4), 8)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    IF_INT_EQUAL(LW(3), GW(8))
        ADD(LW(0), -30)
        ADD(LW(1), 100)
        ADD(LW(2), 10)
        ELSE
        ADD(LW(1), 50)
        ADD(LW(2), 10)
    END_IF
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, LW(0), LW(1), LW(2), 8, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(40)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

USER_FUNC(eff_magic_support) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 type = evtGetValue(event, args[1]);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;

    BtlUnit_GetPos(unit, &x, &y, &z);
    switch (type) {
        case 0:
            x += 30.0f * unit->mSizeMultiplier * unit->faceDirection;
            y += 10.0f * unit->mSizeMultiplier;
            z += 5.0f;
            effStardustEntry(6, 5, x, y, z, 40.0f, 40.0f, 30);
            break;
        case 1:
            x += 30.0f * unit->mSizeMultiplier * unit->faceDirection;
            y += 50.0f * unit->mSizeMultiplier;
            z += 5.0f;
            effStardustEntry(6, 5, x, y, z, 40.0f, 40.0f, 30);
            break;
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(eff_magic_get_posX) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);

    evtSetFloat(event, args[1], ((f32*)((EffectEntry*)unit->work[4])->userdata)[4]);
    return EVT_RETURN_DONE;
}

static USER_FUNC(eff_magic) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 a = evtGetFloat(event, args[1]);
    f32 b = evtGetFloat(event, args[2]);
    f32 c = evtGetFloat(event, args[3]);
    s32 type = evtGetValue(event, args[4]);
    f32 x;
    f32 y;
    f32 z;
    EffectEntry* eff;

    BtlUnit_GetPos(unit, &x, &y, &z);
    // from the tip of the wand
    x += 28.0f * unit->mSizeMultiplier * unit->faceDirection;
    y += 20.0f * unit->mSizeMultiplier;
    z += 5.0f;
    eff = effMagic1N64Entry(0, type, x, y, z, a, b, c);
    unit->work[4] = (s32)eff;
    ((f32*)eff->userdata)[10] = unit->mSizeMultiplier;
    return EVT_RETURN_DONE;
}

static USER_FUNC(eff_staff) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;
    f32* wk;

    if (isFirstCall) {
        unit->work[3] = (s32)effThunderflareN64Entry(0, 0.0f, -1000.0f, 0.0f, 1.0f, 60);
    }
    if (!(((EffectEntry*)unit->work[3])->flags & 1)) {
        return EVT_RETURN_DONE;
    }
    wk = ((EffectEntry*)unit->work[3])->userdata;
    wk[10] = unit->mSizeMultiplier;
    BtlUnit_GetPos(unit, &x, &y, &z);
    wk[2] = x + 30.0f * unit->mSizeMultiplier * unit->faceDirection;
    wk[3] = y + 35.0f * unit->mSizeMultiplier;
    wk[4] = 5.0f + z;
    return EVT_RETURN_BLOCK;
}

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

