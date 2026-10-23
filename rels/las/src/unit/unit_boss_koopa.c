#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/icondrv.h"
#include "driver/camdrv.h"
#include "battle/battle.h"
#include "manager/evtmgr_cmd.h"
#include "driver/dispdrv.h"
#include "system.h"
#include "battle/battle_event_default.h"
#include "battle/battle_message.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "party/party_motion.h"

void btlMovePos(f32 speed, f32 angle, f32* x, f32* z);
typedef struct IconJumpWork { Vec start; Vec pos; Vec end; s32 frames; f32 speed; f32 gravity; f32 vy; u8 pad[0x7C - 0x34]; } IconJumpWork;
static void _disp_icon(CameraId camera, void* param);

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_CheckActStatus);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_DrawLots);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetHp);
USER_FUNC(btlevtcmd_GetMaxHp);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetTotalDamage);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_OffPartsCounterAttribute);
USER_FUNC(btlevtcmd_OnPartsCounterAttribute);
USER_FUNC(btlevtcmd_PhaseEventStartDeclare);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetStayPose);
USER_FUNC(btlevtcmd_SetTalkPose);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_SpawnUnit);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(btlevtcmd_get_turn);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveto);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_sub_random);
static void _disp_icon(CameraId camera, void* param);
static USER_FUNC(_icon_jump_icon);
static USER_FUNC(party_cannot_use_command);
static USER_FUNC(mario_cannot_use_command);
extern s32 unit_boss_kamec_obaba[];

__declspec(section ".data") u64 fd_boss_koopa_negone_one_374;
__declspec(section ".data") s32 fd_boss_koopa_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_koopa___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_koopa___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_koopa_one_negone_373;
__declspec(section ".data") s32 fd_boss_koopa___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_koopa_one_381[1];
__declspec(section ".data") u64 fd_boss_koopa_negone_one_360;
__declspec(section ".data") s32 fd_boss_koopa_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_koopa___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_koopa___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_koopa_one_negone_359;
__declspec(section ".data") s32 fd_boss_koopa___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_koopa_one_364[1];
BattleUnitKind unit_boss_koopa;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_forward_leaning[18];
static __declspec(section ".data") PoseTableEntry pose_table_dead[3];
static __declspec(section ".data") BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
static s32 weapon_koopa_hip_attack[48];
static s32 weapon_koopa_bite_attack[48];
static s32 weapon_koopa_critical_bite_attack[48];
static s32 weapon_koopa_fire_attack[48];
__declspec(section ".data") s32 entry_kamec_obaba[12];
static s32 koopa_zoom[25];
static s32 kamec_obaba_zoom[40];
static s32 init_event[124];
static s32 entry_event[55];
static s32 damage_event[22];
static s32 dead_event[172];
static s32 phase_event[134];
static s32 harf_hp_event[94];
static s32 attack_event[110];
static s32 hip_attack_event[VERSION_PICK(431, 432)];
static s32 bite_attack_event[278];
static s32 critical_bite_attack_event[261];
static s32 fire_attack_event[356];
s32 first_mario_damage_check[33];
s32 first_mario_damage_event[114];
static __declspec(section ".data") s32 wait_event[6];
static __declspec(section ".data") s32 cmd_disable_string[5];

__declspec(section ".data") u64 fd_boss_koopa_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_koopa_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_koopa___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_koopa___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_koopa_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_koopa___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_koopa_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_koopa_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_koopa_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_koopa___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_koopa___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_koopa_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_koopa___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_koopa_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_koopa = {
    144,
    "btl_un_koopa",
    70,
    0,
    1,
    1,
    68,
    0,
    0,
    100,
    0,
    50,
    6,
    86,
    80,
    0,
    70,
    0.0f,
    40.0f,
    0.0f,
    0,
    0,
    40.0f,
    40.0f,
    0.0f,
    43.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    0.0f,
    36.0f,
    72.0f,
    0.0f,
    0.0f,
    40.0f,
    0.0f,
    86.0f,
    80.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_KOOPA_DAMAGED1",
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

static __declspec(section ".data") BattleUnitDefense defence = {{2, 2, 2, 2, 2}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {30, 30, 30, 100, 40, 100, 100, 25, 100, 75, 100, 75, 100, 80, 30, 0, 0, 100, 30, 100, 100, 5};

static PoseTableEntry pose_table[] = {
    {1, "KPA_N_3"},
    {2, "KPA_Z_6"},
    {9, "KPA_Z_6"},
    {5, "KPA_K_2"},
    {4, "KPA_S_2"},
    {3, "KPA_S_2"},
    {28, "KPA_S_1"},
    {29, "KPA_Q_2"},
    {30, "KPA_Q_2"},
    {31, "KPA_D_1"},
    {39, "KPA_D_1"},
    {50, "KPA_S_1"},
    {42, "KPA_R_1"},
    {40, "KPA_W_1"},
    {56, "KPA_S_1"},
    {57, "KPA_S_1"},
    {65, "KPA_T_1"},
    {69, "KPA_S_1"},
};

static PoseTableEntry pose_table_forward_leaning[] = {
    {1, "KPA_N_2"},
    {2, "KPA_Z_5"},
    {9, "KPA_Z_5"},
    {5, "KPA_K_1"},
    {4, "KPA_X_1"},
    {3, "KPA_X_1"},
    {28, "KPA_S_8"},
    {29, "KPA_D_4"},
    {30, "KPA_D_4"},
    {31, "KPA_D_4"},
    {39, "KPA_D_4"},
    {50, "KPA_S_8"},
    {42, "KPA_R_1"},
    {40, "KPA_W_1"},
    {56, "KPA_S_8"},
    {57, "KPA_S_8"},
    {65, "KPA_T_9"},
    {69, "KPA_S_8"},
};

static __declspec(section ".data") PoseTableEntry pose_table_dead[] = {
    {28, "KPA_Z_3"},
    {39, "KPA_Z_3"},
    {69, "KPA_Z_3"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_koopa", "c_koopa", 0.0f, 0.0f, 0.0f, 34.0f, 62.0f, 0.0f, 22.0f, 78.0f, 0.0f, 70, 80, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

static s32 weapon_koopa_hip_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875012, 656130, 0, 4231, 12, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_koopa_bite_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 135, 2, 4,
    0, 7690, 16777216, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_koopa_critical_bite_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 135, 2, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_koopa_fire_attack[] = {
    0, 0, 0, 0, VERSION_PICK(1677721600, 1677721602), 1065353216, 16843009, (s32)weaponGetPowerDefault,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 16777986, 0, 71, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

__declspec(section ".data") s32 entry_kamec_obaba[] = {
    (s32)unit_boss_kamec_obaba, 16777216, 67108868, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

static EVT_BEGIN(koopa_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(evt_btl_camera_set_moveto, 0, LW(0), 95, 350, LW(0), 45, -300, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

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
    CALL(btlevtcmd_SetEventEntry, -2, PTR(entry_event))
    CALL(btlevtcmd_SpawnUnit, GW(9), PTR(entry_kamec_obaba), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 60)
    ADD(LW(1), 40)
    ADD(LW(2), 10)
    CALL(btlevtcmd_SetPos, GW(9), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, GW(9), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    SET_VALUE(GW(8), LW(0))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_GetMaxHp, -2, LW(0))
    DIVIDE(LW(0), 2)
    CALL(btlevtcmd_SetUnitWork, -2, 2, LW(0))
    CALL(btlevtcmd_SetUnitWork, -2, 3, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 4, 0)
    SET_VALUE(GW(10), 0)
    SET_VALUE(GW(11), 0)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_BOSS_KOOPA_MOVE1L"), STRING("SFX_BOSS_KOOPA_MOVE1R"), 0, 15, 15)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_BOSS_KOOPA_MOVE1L"), STRING("SFX_BOSS_KOOPA_MOVE1R"), 0, 8, 8)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 entry_event[] = {
    131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 65545, 60, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KPA_S_1", 65545, 60, 65630, (s32)koopa_zoom, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_VOICE_KOOPA_LAUGH2_1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KPA_Y_2", 65546, 1000, 327771, (s32)evt_msg_print, 2, (s32)"stg8_las_96",
    0, -2, 65546, 300, 65630, (s32)kamec_obaba_zoom, 327771, (s32)evt_msg_print,
    2, (s32)"stg8_las_97", 0, -49999991, 65546, 300, 131163, (s32)btlevtcmd_StatusWindowOnOff,
    1, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 2, 1,
};

static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_CheckDamageCode, -2, 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GW(10), 1)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static s32 dead_event[] = {
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999997, -29999996, -29999995, 131122, -29999994, 1, 131096,
    -30000000, -29999997, 131096, -29999999, -29999996, 131096, -29999998, -29999995,
    131122, -29999994, 0, 33, 33, 33, 131096, -29999994,
    1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 33, 65545, 1, 65627, (s32)btlevtcmd_WaitAttackEnd,
    65627, (s32)btlevtcmd_WaitAttackEnd, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 65630, (s32)koopa_zoom, 65570,
    -49999989, 65572, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_KOOPA_SATIATED2_2", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_D_2", 65546,
    200, 196699, (s32)btlevtcmd_SetTalkPose, -2, (s32)"KPA_T_8", 196699, (s32)btlevtcmd_SetStayPose, -2,
    (s32)"KPA_Z_3", 327771, (s32)evt_msg_print, 2, (s32)"stg8_las_100_02", 0, -2, 65546,
    300, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table_dead, 131122, -49999990,
    2, 131122, -29999990, -2, 65630, (s32)subsetevt_dead_core_nospin_norotate, 42, 196699,
    (s32)btlevtcmd_SetTalkPose, -2, (s32)"KPA_D_1", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"KPA_D_1", 327771,
    (s32)evt_msg_print, 2, (s32)"stg8_las_100_04", 0, -2, 65546, 300, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_KOOPA_SATIATED2_2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KPA_D_2", 65546, 700, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2,
    1, (s32)pose_table_dead, 131122, -49999990, 2, 131122, -29999990, -2,
    65630, (s32)subsetevt_dead_core_nospin_norotate, 49, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 2, 1,
};

static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckStatus, -2, 27, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_get_turn, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckPhase, LW(0), 67108865)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckActStatus, -2, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_PhaseEventStartDeclare, -2)
            CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_sub_random, 99, LW(1))
                IF_INT_LESS(LW(1), 0)
                    CALL(btlevtcmd_SetUnitWork, -2, 0, 1)
                    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("KPA_U_2"))
                    WAIT_MS(200)
                    CALL(btlevtcmd_OnPartsCounterAttribute, -2, 1, 1)
                    CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_forward_leaning))
                END_IF
                ELSE
                CALL(evt_sub_random, 99, LW(1))
                IF_INT_LESS(LW(1), 100)
                    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
                    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("KPA_U_3"))
                    WAIT_MS(200)
                    CALL(btlevtcmd_OffPartsCounterAttribute, -2, 1, 1)
                    CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table))
                END_IF
            END_IF
            CALL(btlevtcmd_StartWaitEvent, -2)
        END_IF
    END_IF
    LABEL(90)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108867)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_PhaseEventStartDeclare, -2)
        CALL_CHILD(PTR(harf_hp_event))
        CALL(btlevtcmd_StartWaitEvent, -2)
    END_IF
    LABEL(99)
    RETURN
EVT_END()

static EVT_BEGIN(harf_hp_event)
    CALL(btlevtcmd_GetUnitWork, -2, 3, LW(1))
    IF_INT_EQUAL(LW(1), 0)
        CALL(btlevtcmd_GetHp, -2, LW(0))
        CALL(btlevtcmd_GetUnitWork, -2, 2, LW(1))
        IF_INT_LESS(LW(0), LW(1))
            CALL(btlevtcmd_SetUnitWork, -2, 3, 1)
            CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
            IF_INT_EQUAL(LW(0), 1)
                CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("KPA_U_3"))
                WAIT_MS(200)
            END_IF
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL_CHILD(PTR(koopa_zoom))
            CALL(btlevtcmd_SetTalkPose, -2, STRING("KPA_T_3"))
            CALL(btlevtcmd_SetStayPose, -2, STRING("KPA_S_4"))
            CALL(evt_msg_print, 2, STRING("stg8_las_100"), 0, -2)
            WAIT_MS(300)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
            IF_INT_EQUAL(LW(0), 1)
                CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("KPA_U_2"))
                WAIT_MS(200)
            END_IF
            CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 43)
        END_IF
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 4, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        SET_VALUE(LW(9), PTR(weapon_koopa_fire_attack))
        CALL_CHILD(PTR(fire_attack_event))
        CALL(btlevtcmd_SetUnitWork, -2, 4, 1)
        CASE_EQUAL(1)
        SET_VALUE(LW(9), PTR(weapon_koopa_bite_attack))
        CALL_CHILD(PTR(bite_attack_event))
        CALL(btlevtcmd_SetUnitWork, -2, 4, 2)
        CASE_EQUAL(2)
        SET_VALUE(LW(9), PTR(weapon_koopa_hip_attack))
        CALL_CHILD(PTR(hip_attack_event))
        CALL(btlevtcmd_SetUnitWork, -2, 4, 3)
        CASE_DEFAULT
        CALL(btlevtcmd_DrawLots, LW(0), 4, 20, 20, 0, 40)
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_VALUE(LW(9), PTR(weapon_koopa_hip_attack))
            CALL_CHILD(PTR(hip_attack_event))
            CASE_EQUAL(1)
            SET_VALUE(LW(9), PTR(weapon_koopa_bite_attack))
            CALL_CHILD(PTR(bite_attack_event))
            CASE_EQUAL(2)
            SET_VALUE(LW(9), PTR(weapon_koopa_critical_bite_attack))
            CALL_CHILD(PTR(critical_bite_attack_event))
            CASE_EQUAL(3)
            SET_VALUE(LW(9), PTR(weapon_koopa_fire_attack))
            CALL_CHILD(PTR(fire_attack_event))
        END_SWITCH
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    CALL_CHILD(PTR(first_mario_damage_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

#ifdef VERSION_G8ME01
static s32 hip_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 196699, (s32)btlevtcmd_GetUnitKind,
    -29999997, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, -30000000, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    40, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229997952, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, 0, -1, 0, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_KOOPA_JUMP1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KPA_A_2A", 65546, 300, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"KPA_A_2B", 110, 65545, 25, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"KPA_A_2C", 65545, 15, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_A_2D",
    112, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999744, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 131126, -29999998, 20, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 50, -1, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOOPA_HIP_ATTACK1", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 49,
    65539, 90, 131163, (s32)btlevtcmd_JumpContinue, -2, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KPA_A_2E", 65546, 500, 65540, 98, 65539, 91,
    196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999991, 256, -29999995, 393307, (s32)evt_btl_camera_shake_h, 0, 3,
    0, 50, 13, 131163, (s32)btlevtcmd_JumpContinue, -2, 65546, 500,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_A_2E", 65546, 300, 131163,
    (s32)btlevtcmd_GetResultACDefence, -29999993, 131100, -29999993, 3, 131122, -29999985, 0,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000, 65570, -30000000, 65572,
    222, 131163, (s32)mario_cannot_use_command, -29999985, 131119, 224, 230, 196699,
    (s32)party_cannot_use_command, -29999985, -29999997, 42, 131122, -30000000, -1, 49,
    131097, -30000000, -1, 131097, -29999985, 0, 107, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2,
    -29999995, -29999994, -29999993, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -29999995, 60,
    262235, (s32)btlevtcmd_TransStageFloorPosition, -29999995, -29999994, -29999993, 655451, (s32)_icon_jump_icon, -29999985,
    -30000000, -29999999, -29999998, -29999995, -29999994, -29999993, -229999488, 30,
    131122, -30000000, -29999995, 131122, -29999999, -29999994, 131122, -29999998,
    -29999993, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -29999995, 40, 655451, (s32)_icon_jump_icon,
    -29999985, -30000000, -29999999, -29999998, -29999995, -29999994, -29999993, -229999488,
    20, 131122, -30000000, -29999995, 131122, -29999999, -29999994, 131122,
    -29999998, -29999993, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -29999995, 25, 655451,
    (s32)_icon_jump_icon, -29999985, -30000000, -29999999, -29999998, -29999995, -29999994, -29999993,
    -229999488, 12, 109, 33, 110, 393307, (s32)btlevtcmd_AnnounceMessage, 0,
    0, 0, -30000000, 120, 112, 33, 33, 65539,
    98, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546, 250, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_R_1", 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_S_1", 65630, (s32)first_mario_damage_check, 2, 1,
};
#else
static s32 hip_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 196699, (s32)btlevtcmd_GetUnitKind,
    -29999997, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, -30000000, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    40, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229997952, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, 0, -1, 0, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_KOOPA_JUMP1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KPA_A_2A", 65546, 300, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"KPA_A_2B", 110, 65545, 25, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"KPA_A_2C", 65545, 15, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_A_2D",
    112, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999744, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 131126, -29999998, 20, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 50, -1, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOOPA_HIP_ATTACK1", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 49,
    65539, 90, 131163, (s32)btlevtcmd_JumpContinue, -2, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KPA_A_2E", 65546, 500, 65540, 98, 65539, 91,
    196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999991, 256, -29999995, 393307, (s32)evt_btl_camera_shake_h, 0, 3,
    0, 50, 13, 131163, (s32)btlevtcmd_JumpContinue, -2, 65546, 500,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_A_2E", 65546, 300, 131163,
    (s32)btlevtcmd_GetResultACDefence, -29999993, 131100, -29999993, 3, 131122, -29999985, 0,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 5, -30000000, 65570, -30000000, 65572,
    222, 131163, (s32)mario_cannot_use_command, -29999985, 131119, 224, 230, 131163,
    (s32)party_cannot_use_command, -29999985, 42, 131122, -30000000, -1, 49, 131097,
    -30000000, -1, 131097, -29999985, 0, 107, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -29999995,
    -29999994, -29999993, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -29999995, 60, 262235,
    (s32)btlevtcmd_TransStageFloorPosition, -29999995, -29999994, -29999993, 655451, (s32)_icon_jump_icon, -29999985, -30000000,
    -29999999, -29999998, -29999995, -29999994, -29999993, -229999488, 30, 131122,
    -30000000, -29999995, 131122, -29999999, -29999994, 131122, -29999998, -29999993,
    262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -29999995, 40, 655451, (s32)_icon_jump_icon, -29999985,
    -30000000, -29999999, -29999998, -29999995, -29999994, -29999993, -229999488, 20,
    131122, -30000000, -29999995, 131122, -29999999, -29999994, 131122, -29999998,
    -29999993, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -29999995, 25, 655451, (s32)_icon_jump_icon,
    -29999985, -30000000, -29999999, -29999998, -29999995, -29999994, -29999993, -229999488,
    12, 109, 33, 110, 393307, (s32)btlevtcmd_AnnounceMessage, 0, 0,
    0, -30000000, 120, 112, 33, 33, 65539, 98,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546, 250, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KPA_R_1", 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, 0, -1, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KPA_S_1", 65630, (s32)first_mario_damage_check, 2, 1,
};
#endif

static s32 bite_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 196699, (s32)btlevtcmd_GetUnitKind,
    -29999997, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, -30000000, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0,
    8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KPA_R_1", 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 65, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, 0, -29999998, 0, -1, 1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_A_3A", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOOPA_BITE1",
    -250000000, 0, -250000000, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65546,
    170, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_A_3B", 65546, 150,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOOPA_BITE2", -250000000, 0, -250000000, 458843,
    (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995, 65570,
    -29999995, 65579, 4, 65540, 90, 46, 65572, 3,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572,
    6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572,
    1, 65540, 91, 46, 42, 65540, 98, 46,
    49, 65539, 90, 65546, 100, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KPA_A_3C", 65546, 150, 65540, 98, 65539, 91,
    65546, 100, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -29999997, -29999996, -29999991, 256, -29999995, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KPA_A_3C", 65546, 150, 65539, 98, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 65546, 250, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KPA_R_1", 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KPA_S_1", 65630, (s32)first_mario_damage_check, 2, 1,
};

static s32 critical_bite_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 196699, (s32)btlevtcmd_GetUnitKind,
    -29999997, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, -30000000, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KPA_R_1", 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 65, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, 0, -29999998, 0, -1, 1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KPA_A_3A", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOOPA_BITE1", -250000000,
    0, -250000000, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65546, 170,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_A_3B", 65546, 150, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOOPA_BITE3", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 49,
    65539, 90, 65546, 100, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"KPA_A_3C", 65546, 150, 65540, 98, 65539, 91, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_A_4", 65546, 1500, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_A_3C", 65546,
    150, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546,
    250, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_R_1", 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1,
    0, 65630, (s32)first_mario_damage_check, 2, 1,
};

static s32 fire_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 196699, (s32)btlevtcmd_GetUnitKind,
    -29999997, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, -30000000, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999991, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_R_1",
    327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -29999997, -30000000, 120, 196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235,
    (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_btl_camera_set_zoom, 0, 200, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    0, -29999998, 0, -1, 1, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 65546, 170, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_A_1A",
    65546, 300, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_KOOPA_FIRE1", -250000000, 0,
    -250000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KOOPA_FIRE_BREATH1", -250000000, 0, -29999985,
    107, 65546, 1500, 131163, (s32)evt_snd_sfxoff, -29999985, 109, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_A_1B", 65546, 300, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_GetStatusMg, -2, -29999995,
    131124, -29999994, -229938560, 131132, -29999994, -29999995, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -2, -30000000, -29999994, 131124, -29999994, -229976960, 131132, -29999994,
    -29999995, 131130, -29999999, -29999994, 131126, -29999998, 5, 131132,
    -29999995, -229996416, 983131, (s32)evt_eff, (s32)"", (s32)"gonbaba_breath", 7, -30000000,
    -29999999, -29999998, -29999995, 90, 0, 0, 0, 0,
    0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_A_1C", 65546,
    300, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131122, -29999990, 0,
    65539, 10, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65570, -29999995, 65579, 4, 65540, 90,
    46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540,
    90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    65540, 90, 65572, 1, 65540, 91, 46, 42,
    65540, 98, 46, 49, 65539, 90, 65540, 97,
    65539, 91, 131096, -29999990, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65539, 97, 65630, (s32)first_mario_damage_check, 196699, (s32)btlevtcmd_GetSelectNextEnemy,
    -29999997, -29999996, 131097, -29999997, -1, 131125, -29999990, 1,
    65540, 10, 33, 65539, 98, 65546, 1200, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_A_1D", 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    65546, 250, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_R_1", 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229995904, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 2, 1,
};

EVT_BEGIN(first_mario_damage_check)
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, -2, 5, LW(0))
        IF_INT_EQUAL(LW(0), 222)
            CALL(btlevtcmd_GetTotalDamage, LW(3), LW(1))
            IF_INT_NOT_EQUAL(LW(1), 0)
                CALL(btlevtcmd_SetUnitWork, -2, 1, 1)
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

s32 first_mario_damage_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -30000000, 131096, -30000000, 1,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KPA_S_1", 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 65630, (s32)koopa_zoom, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096, -30000000, 1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_U_3", 65546, 200, 33, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_KOOPA_LAUGH2_1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KPA_Y_2", 65546, 1000, 196699, (s32)btlevtcmd_SetTalkPose, -2,
    (s32)"KPA_T_2", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"KPA_S_3", 327771, (s32)evt_msg_print, 2,
    (s32)"stg8_las_98", 0, -2, 65546, 300, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KPA_S_1", 131096, -49999989, 0, 65630, (s32)kamec_obaba_zoom, 327771,
    (s32)evt_msg_print, 2, (s32)"stg8_las_99", 0, -49999991, 65546, 300, 33,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096, -30000000, 1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KPA_U_2", 65546, 200, 33,
    131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 33,
    2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static __declspec(section ".data") s32 cmd_disable_string[] = {
    (s32)"btl_jump_cmd_disable", (s32)"btl_hammer_cmd_disable", (s32)"btl_item_cmd_disable", (s32)"btl_party_tech_cmd_disable", (s32)"btl_party_item_cmd_disable",
};

static void _disp_icon(CameraId camera, void* param) {
    EventEntry* event = param;

    iconDispGx((Vec*)((u8*)event->userdatap[0] + 0xC), 0, event->userdata[1], 1.0f);
}

static USER_FUNC(_icon_jump_icon) {
    s32* args = event->args;
    s32 icon = evtGetValue(event, args[0]);
    f32 x0 = evtGetFloat(event, args[1]);
    f32 y0 = evtGetFloat(event, args[2]);
    f32 z0 = evtGetFloat(event, args[3]);
    f32 x1 = evtGetFloat(event, args[4]);
    f32 y1 = evtGetFloat(event, args[5]);
    f32 z1 = evtGetFloat(event, args[6]);
    f32 gravity = evtGetFloat(event, args[7]);
    s32 frames = evtGetValue(event, args[8]);
    IconJumpWork* wk;

    if (isFirstCall) {
        Vec start;

        event->userdatap[0] = BattleAlloc(sizeof(IconJumpWork));
        wk = event->userdatap[0];
        wk->end.x = x1;
        wk->end.y = y1;
        wk->end.z = z1;
        start.x = x0;
        start.y = y0;
        start.z = z0;
        wk->pos = start;
        wk->start = start;
        wk->gravity = gravity;
        wk->frames = frames;
        wk->vy = (wk->end.y - wk->start.y) / wk->frames + wk->gravity * wk->frames / 2;
        wk->speed = distABf(wk->start.x, wk->start.z, wk->end.x, wk->end.z) / wk->frames;
        event->userdata[1] = icon;
        event->userdata[2] = 0;
    }
    wk = event->userdatap[0];
    if (event->userdata[2]) {
        BattleFree(wk);
        return EVT_RETURN_DONE;
    }
    wk->pos.y += wk->vy;
    wk->vy -= wk->gravity;
    if (wk->vy < 0.0f && wk->pos.y < wk->end.y) {
        wk->pos.y = wk->end.y;
    }
    btlMovePos(wk->speed, angleABf(wk->start.x, wk->start.z, wk->end.x, wk->end.z), &wk->pos.x, &wk->pos.z);
    wk->frames--;
    if (wk->frames <= 0) {
        event->userdata[2] = 1;
        wk->pos = wk->end;
    }
    dispEntry(CAMERA_3D, 900.0f, 1, _disp_icon, event);
    return EVT_RETURN_BLOCK;
}

static USER_FUNC(party_cannot_use_command) {
    BattleWork* wp = _battleWorkPointer;
    s32 r = irand(1);
    s32 var = event->args[0];
#ifdef VERSION_G8ME01
    s32 id = evtGetValue(event, event->args[1]);
    s32 weapon = 0;
    BattleUnit* unit;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
#else
    s32 weapon = 0;
#endif
#ifdef VERSION_G8ME01

    switch (r) {
        case 0:
            if (unit != NULL) {
                *(s16*)((u8*)unit + 0x13C) = 3;
            }
            weapon = 344;
            break;
        case 1:
            if (unit != NULL) {
                *(s16*)((u8*)unit + 0x13E) = 3;
            }
            weapon = 340;
            break;
    }
#else
    switch (r) {
        case 0:
            wp->commandDisabled[3] = 3;
            weapon = 336;
            break;
        case 1:
            wp->commandDisabled[4] = 3;
            weapon = 332;
            break;
    }
#endif
    event->lwData[0] = (s32)cmd_disable_string[r + 3];
    evtSetValue(event, var, weapon);
    return EVT_RETURN_DONE;
}

static USER_FUNC(mario_cannot_use_command) {
    BattleWork* wp = _battleWorkPointer;
    s32 r = irand(2);
    s32 var = event->args[0];
    s32 weapon = 0;

    switch (r) {
        case 0:
            wp->commandDisabled[0] = 3;
#ifdef VERSION_G8ME01
            weapon = 334;
#else
            weapon = 326;
#endif
            break;
        case 1:
            wp->commandDisabled[1] = 3;
#ifdef VERSION_G8ME01
            weapon = 337;
#else
            weapon = 329;
#endif
            break;
        case 2:
            wp->commandDisabled[2] = 3;
#ifdef VERSION_G8ME01
            weapon = 340;
#else
            weapon = 332;
#endif
            break;
    }
    event->lwData[0] = (s32)cmd_disable_string[r];
    evtSetValue(event, var, weapon);
    return EVT_RETURN_DONE;
}

