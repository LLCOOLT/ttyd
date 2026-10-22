#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_unit.h"
#include "driver/animdrv.h"
#include "string.h"

static USER_FUNC(_set_draw_callback);
USER_FUNC(btlevtcmd_AfterReactionEntry);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeSetPoseSoundTable);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_GetDamageCode);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_snd_sfxoff);
static void _fire_point_callback(BattleUnitPart* part, s32 group);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckPhase[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetHeight[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetStatusMg[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_OnUnitFlag[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PhaseEventStartDeclare[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_StageDispellFog[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_eff[];
extern s32 subsetevt_dead_core[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_heavy_bom_negone_one_374;
__declspec(section ".data") s32 fd_heavy_bom_neg_one_382[1];
__declspec(section ".data") s32 fd_heavy_bom___local_PI_383[1];
__declspec(section ".data") s32 fd_heavy_bom___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_heavy_bom_one_negone_373;
__declspec(section ".data") s32 fd_heavy_bom___local_PIO2_384[1];
__declspec(section ".data") s32 fd_heavy_bom_one_381[1];
__declspec(section ".data") u64 fd_heavy_bom_negone_one_360;
__declspec(section ".data") s32 fd_heavy_bom_neg_one_365[1];
__declspec(section ".data") s32 fd_heavy_bom___local_PI_366[1];
__declspec(section ".data") s32 fd_heavy_bom___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_heavy_bom_one_negone_359;
__declspec(section ".data") s32 fd_heavy_bom___local_PIO2_367[1];
__declspec(section ".data") s32 fd_heavy_bom_one_364[1];
BattleUnitKind unit_heavy_bom_6_data_15A08;
static s32 weapon_heavy_bomb_super_explosion[48];
static s32 weapon_heavy_bomb_guard[48];
static s32 weapon_heavy_bomb_guard_2[48];
static s32 weapon_heavy_bomb_guard_3[48];
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table_3[16];
static PoseTableEntry pose_table_3_fire[16];
static PoseTableEntry pose_table_2[16];
static PoseTableEntry pose_table_2_fire[16];
static PoseTableEntry pose_table_1[16];
static PoseTableEntry pose_table_1_fire[16];
static PoseTableEntry pose_table_0_fire[16];
static PoseTableEntry pose_table_0[16];
static PoseTableEntry pose_table_3_to_2[13];
static PoseTableEntry pose_table_2_to_1[13];
static PoseTableEntry pose_table_1_to_0[13];
static __declspec(section ".data") BattleDataEntry data_table[3];
static s32 pose_sound_timing_table[45];
static BattleUnitKindPart parts[2];
static s32 init_event[57];
static s32 damage_event[118];
static s32 phase_event[126];
static s32 attack_event[175];
static __declspec(section ".data") s32 wait_event[6];
static s32 dead_event[52];
static s32 explosion_event[247];

void animPoseSetDispCallBack(s32 poseId, void (*callback)(BattleUnitPart*, s32), void* userdata);

static USER_FUNC(_set_draw_callback) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(wp, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);

    animPoseSetDispCallBack(part->poseId, _fire_point_callback, part);
    BtlUnit_GetPartsPtr(unit, 2)->attributes |= 0x1000000;
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_heavy_bom_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_heavy_bom_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_heavy_bom___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_heavy_bom___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_heavy_bom_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_heavy_bom___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_heavy_bom_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_heavy_bom_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_heavy_bom_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_heavy_bom___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_heavy_bom___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_heavy_bom_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_heavy_bom___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_heavy_bom_one_364[] = {
    1065353216,
};

BattleUnitKind unit_heavy_bom_6_data_15A08 = {
    92,
    "btl_un_heavy_bom",
    6,
    0,
    1,
    1,
    22,
    0,
    4,
    70,
    0,
    40,
    9999,
    54,
    70,
    7,
    70,
    0.0f,
    35.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    27.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    27.0f,
    0.0f,
    0.0f,
    27.0f,
    45.5f,
    0.0f,
    0.0f,
    35.0f,
    0.0f,
    54.0f,
    70.0f,
    0,
    0,
    0,
    2,
    100,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_HEAVYB_DAMAGED1",
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

static s32 weapon_heavy_bomb_super_explosion[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607136, 536870912, 50332418, 0, 139399, 2047, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 3289700, 0, 0,
};

static s32 weapon_heavy_bomb_guard[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 33570848, 268435456, 770, 0, 131080, 2047, 0,
    0, 0, 0, 0, 0, 0, 6554371, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_heavy_bomb_guard_2[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 33570848, 268435456, 770, 0, 131080, 2047, 0,
    0, 0, 0, 0, 0, 25603, 50331648, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_heavy_bomb_guard_3[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 33570848, 268435456, 770, 0, 131080, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 3,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {90, 75, 70, 0, 70, 150, 100, 100, 100, 80, 100, 80, 100, 95, 70, 80, 20, 100, 70, 100, 100, 95};

static PoseTableEntry pose_table_3[] = {
    {1, "N_1"},
    {9, "Y_1"},
    {2, "Y_1"},
    {3, "K_1"},
    {4, "X_1"},
    {5, "K_1"},
    {9, "Z_1"},
    {28, "S_1"},
    {29, "D_1"},
    {35, "S_1"},
    {31, "S_1"},
    {39, "D_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "S_1"},
    {69, "S_1"},
};

static PoseTableEntry pose_table_3_fire[] = {
    {1, "N_1"},
    {9, "Y_1"},
    {2, "Y_1"},
    {3, "K_1"},
    {4, "X_1"},
    {5, "K_1"},
    {9, "Z_1"},
    {28, "S_1"},
    {29, "D_1"},
    {35, "S_1"},
    {31, "S_1"},
    {39, "D_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "S_1"},
    {69, "S_1"},
};

static PoseTableEntry pose_table_2[] = {
    {1, "N_2"},
    {9, "Y_2"},
    {2, "Y_2"},
    {3, "K_2"},
    {4, "X_2"},
    {5, "K_2"},
    {9, "Z_2B"},
    {28, "S_2B"},
    {29, "D_2"},
    {35, "S_2B"},
    {31, "S_2B"},
    {39, "D_2"},
    {56, "X_2"},
    {57, "X_2"},
    {65, "S_2B"},
    {69, "S_2B"},
};

static PoseTableEntry pose_table_2_fire[] = {
    {1, "N_2"},
    {9, "Y_2"},
    {2, "Y_2"},
    {3, "K_2"},
    {4, "X_2"},
    {5, "K_2"},
    {9, "Z_2A"},
    {28, "S_2A"},
    {29, "D_2"},
    {35, "S_2A"},
    {31, "S_2A"},
    {39, "D_2"},
    {56, "X_2"},
    {57, "X_2"},
    {65, "S_2A"},
    {69, "S_2A"},
};

static PoseTableEntry pose_table_1[] = {
    {1, "N_3"},
    {9, "Y_3"},
    {2, "Y_3"},
    {3, "K_3"},
    {4, "X_3"},
    {5, "K_3"},
    {9, "Z_3B"},
    {28, "S_3B"},
    {29, "D_3"},
    {35, "S_3B"},
    {31, "S_3B"},
    {39, "D_3"},
    {56, "X_3"},
    {57, "X_3"},
    {65, "S_3B"},
    {69, "S_3B"},
};

static PoseTableEntry pose_table_1_fire[] = {
    {1, "N_3"},
    {9, "Y_3"},
    {2, "Y_3"},
    {3, "K_3"},
    {4, "X_3"},
    {5, "K_3"},
    {9, "Z_3A"},
    {28, "S_3A"},
    {29, "D_3"},
    {35, "S_3A"},
    {31, "S_3A"},
    {39, "D_3"},
    {56, "X_3"},
    {57, "X_3"},
    {65, "S_3A"},
    {69, "S_3A"},
};

static PoseTableEntry pose_table_0_fire[] = {
    {1, "N_4"},
    {9, "Y_4"},
    {2, "Y_4"},
    {3, "K_4"},
    {4, "X_4"},
    {5, "K_4"},
    {9, "Z_4A"},
    {28, "S_4A"},
    {29, "D_4"},
    {35, "S_4A"},
    {31, "S_4A"},
    {39, "D_4"},
    {56, "X_4"},
    {57, "X_4"},
    {65, "S_4A"},
    {69, "S_4A"},
};

static PoseTableEntry pose_table_0[] = {
    {1, "N_4"},
    {9, "Y_4"},
    {2, "Y_4"},
    {3, "K_4"},
    {4, "X_4"},
    {5, "K_4"},
    {9, "Z_4B"},
    {28, "S_4B"},
    {29, "D_4"},
    {35, "S_4B"},
    {31, "S_4B"},
    {39, "D_4"},
    {56, "X_4"},
    {57, "X_4"},
    {65, "S_4B"},
    {69, "S_4B"},
};

static PoseTableEntry pose_table_3_to_2[] = {
    {1, "B_4"},
    {9, "B_1"},
    {2, "B_1"},
    {3, "B_7"},
    {4, "B_10"},
    {5, "B_7"},
    {28, "B_1"},
    {31, "B_1"},
    {39, "B_1"},
    {56, "B_10"},
    {57, "B_10"},
    {65, "B_1"},
    {69, "B_1"},
};

static PoseTableEntry pose_table_2_to_1[] = {
    {1, "B_5"},
    {9, "B_2"},
    {2, "B_2"},
    {3, "B_8"},
    {4, "B_11"},
    {5, "B_8"},
    {28, "B_2"},
    {31, "B_2"},
    {39, "B_2"},
    {56, "B_11"},
    {57, "B_11"},
    {65, "B_2"},
    {69, "B_2"},
};

static PoseTableEntry pose_table_1_to_0[] = {
    {1, "B_6"},
    {9, "B_3"},
    {2, "B_3"},
    {3, "B_9"},
    {4, "B_12"},
    {5, "B_9"},
    {28, "B_3"},
    {31, "B_3"},
    {39, "B_3"},
    {56, "B_12"},
    {57, "B_12"},
    {65, "B_3"},
    {69, "B_3"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {52, explosion_event},
    {0, NULL},
};

static s32 pose_sound_timing_table[] = {
    (s32)"S_3A", 1008981770, 0, (s32)"SFX_ENM_HEAVYB_WAIT3", 1, (s32)"S_3A", 1049135241, 0,
    (s32)"SFX_ENM_HEAVYB_WAIT3", 1, (s32)"S_3A", 1057523849, 0, (s32)"SFX_ENM_HEAVYB_WAIT3", 1, (s32)"S_3A",
    1061997773, 0, (s32)"SFX_ENM_HEAVYB_WAIT3", 1, (s32)"S_4A", 1008981770, 0, (s32)"SFX_ENM_HEAVYB_WAIT3",
    1, (s32)"S_4A", 1042983595, 0, (s32)"SFX_ENM_HEAVYB_WAIT3", 1, (s32)"S_4A", 1051372203,
    0, (s32)"SFX_ENM_HEAVYB_WAIT3", 1, (s32)"S_4A", 1056964608, 0, (s32)"SFX_ENM_HEAVYB_WAIT3", 1,
    0, 0, 0, 0, 1,
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_heavy_bom", "c_heavy", 0.0f, 0.0f, 0.0f, 15.0f, 50.0f, 0.0f, 0.0f, 65.0f, 0.0f, 65, 70, 255, &defence, &defence_attr, 0x9, 0, pose_table_3},
    {2, /*"ヘビーボム"*/"\x83\x77\x83\x72\x81\x5B\x83\x7B\x83\x80", "c_heavy", 0.0f, 80.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 15, 255, &defence, &defence_attr, 0x2010000, 0, pose_table_3},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 3)
    CALL(btlevtcmd_SetUnitWork, -2, 2, -1)
    CALL(btlevtcmd_SetUnitWork, -2, 3, 0)
    CALL(btlevtcmd_AnimeChangePose, -2, 2, STRING("F_1"))
    CALL(btlevtcmd_AnimeSetPoseSoundTable, -2, 1, PTR(pose_sound_timing_table))
    CALL(_set_draw_callback)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_CheckStatus, -2, 9, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetUnitWork, -2, 2, LW(0))
            CALL(evt_snd_sfxoff, LW(0))
            CALL(btlevtcmd_SetUnitWork, -2, 2, -1)
            CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
            CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(2)
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_2))
                CASE_EQUAL(1)
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_1))
                CASE_EQUAL(0)
                CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_0))
            END_SWITCH
        END_IF
    END_IF
    CALL(btlevtcmd_CheckDamageCode, LW(10), 256, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
        SWITCH(LW(0))
            CASE_OR_EQUAL(27)
            CASE_OR_EQUAL(24)
            CASE_OR_EQUAL(25)
            CASE_OR_EQUAL(52)
            CASE_OR_EQUAL(46)
            CASE_OR_EQUAL(50)
            CASE_OR_EQUAL(54)
            GOTO(50)
            CASE_END
        END_SWITCH
    END_IF
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
    LABEL(50)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 29)
    CALL_CHILD(PTR(dead_event))
    RETURN
EVT_END()

static s32 phase_event[] = {
    196699, (s32)btlevtcmd_CheckPhase, -30000000, 67108867, 131097, -30000000, 0, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131097, -30000000, 0, 131163,
    (s32)btlevtcmd_PhaseEventStartDeclare, -2, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -30000000, 131096,
    -30000000, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"K_4", 196699,
    (s32)btlevtcmd_AfterReactionEntry, -2, 52, 2, 33, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_HEAVYB_WAIT2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1,
    -30000000, 65570, -30000000, 65572, 3, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2,
    1, (s32)pose_table_3_to_2, 65572, 2, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1,
    (s32)pose_table_2_to_1, 65572, 1, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table_1_to_0,
    49, 196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 65545, 40, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 1, -30000000, 131126, -30000000, 1, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 1, -30000000, 65570, -30000000, 65572, 2,
    262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table_2_fire, 65572, 1, 262235,
    (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table_1_fire, 65572, 0, 262235, (s32)btlevtcmd_AnimeSetPoseTable,
    -2, 1, (s32)pose_table_0_fire, 49, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    33, 33, 65539, 99, 2, 1,
};

static s32 attack_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_HEAVYB_ATTACK1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096, -30000000, 0, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 1, -30000000, 65570, -30000000, 65572, 3,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"G_1", 65572, 2, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"G_2", 65572, 1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"G_3", 65572, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"G_4", 49, 65545, 40, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_HEAVYB_WAIT1", -250000000, 0, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2,
    -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_HEAVYB_ATTACK2", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 1, 196699, (s32)btlevtcmd_OnUnitFlag, -2,
    16, 32, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -30000000, 65570,
    -30000000, 65572, 3, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"G_1",
    65572, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"G_2", 65572,
    1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"G_3", 65572, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"G_4", 49, 65545, 40,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -30000000, 65570, -30000000, 65572,
    0, 131122, -29999988, (s32)weapon_heavy_bomb_guard, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3,
    1, 65572, 1, 131122, -29999988, (s32)weapon_heavy_bomb_guard_2, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 3, 2, 65572, 2, 131122, -29999988, (s32)weapon_heavy_bomb_guard_3,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 3, 0, 49, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2, -2, 1, -29999988, 256,
    -29999995, 33, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_GetUnitWork, -2, 2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
        CALL(evt_snd_sfxoff, LW(0))
    END_IF
    CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
    SWITCH(LW(0))
        CASE_OR_EQUAL(27)
        CASE_OR_EQUAL(24)
        CASE_OR_EQUAL(25)
        CASE_OR_EQUAL(52)
        CASE_OR_EQUAL(46)
        CASE_OR_EQUAL(50)
        CASE_OR_EQUAL(54)
        GOTO(50)
        CASE_END
    END_SWITCH
    LABEL(10)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(PTR(subsetevt_dead_core))
    RETURN
    LABEL(50)
    CALL(btlevtcmd_AfterReactionEntry, -2, 52)
    RETURN
EVT_END()

static s32 explosion_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -30000000, 131163, (s32)evt_snd_sfxoff, -30000000,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, -1, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_HEAVYB_ATTACK3", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 196699, (s32)btlevtcmd_GetHeight, -2, -29999995, 131128, -29999995,
    2, 196699, (s32)btlevtcmd_GetStatusMg, -2, -29999994, 131132, -29999995, -29999994,
    131125, -29999999, -29999995, 983131, (s32)evt_eff, 0, (s32)"bomb", 5,
    -30000000, -29999999, -29999998, -229997952, 0, 0, 0, 0,
    0, 0, 0, 65627, (s32)btlevtcmd_StageDispellFog, 65546, 300, 983131,
    (s32)evt_eff, 0, (s32)"bomb", 4, -40, 30, 20, -229997952,
    0, 0, 0, 0, 0, 0, 0, 65546,
    125, 983131, (s32)evt_eff, 0, (s32)"bomb", 4, 40, 90,
    20, -229997952, 0, 0, 0, 0, 0, 0,
    0, 65546, 125, 983131, (s32)evt_eff, 0, (s32)"bomb", 4,
    40, 30, 20, -229997952, 0, 0, 0, 0,
    0, 0, 0, 65546, 125, 983131, (s32)evt_eff, 0,
    (s32)"bomb", 4, -40, 90, 20, -229997952, 0, 0,
    0, 0, 0, 0, 0, 65546, 125, 983131,
    (s32)evt_eff, 0, (s32)"bomb", 4, -100, 60, 20, -229997952,
    0, 0, 0, 0, 0, 0, 0, 65546,
    125, 983131, (s32)evt_eff, 0, (s32)"bomb", 4, 100, 60,
    20, -229997952, 0, 0, 0, 0, 0, 0,
    0, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2,
    -30000000, (s32)weapon_heavy_bomb_super_explosion, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_heavy_bomb_super_explosion, -29999997, -29999996, 131096,
    -29999997, -1, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_heavy_bomb_super_explosion,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_heavy_bomb_super_explosion, 131122, -29999990, 0, 65539,
    10, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_heavy_bomb_super_explosion, 256,
    -29999995, 131096, -29999995, 1, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, (s32)weapon_heavy_bomb_super_explosion, 256, -29999995, 33, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997,
    -29999996, 131097, -29999997, -1, 131125, -29999990, 1, 65540,
    10, 33, 65539, 99, 131122, -29999990, -2, 65630,
    (s32)subsetevt_dead_core, 196699, (s32)btlevtcmd_KillUnit, -2, 0, 2, 1,
};

void animPoseDrawShape(s32 poseId, s32 shapeIdx);

static void _fire_point_callback(BattleUnitPart* part, s32 group) {
    BattleUnit* unit = part->mOwner;
    const char* name;
    s32 poseId;

    if (unit->work[0] == 0) {
        return;
    }
    poseId = part->poseId;
    switch (unit->work[1]) {
        case 0:
            name = "locator11";
            break;
        case 1:
            name = "locator10";
            break;
        case 2:
            name = "locator9";
            break;
        case 3:
        default:
            name = "locator8";
            break;
    }
    if (strcmp(name, animPoseGetGroupName(poseId, group)) == 0) {
        s32 shapePose = BtlUnit_GetPartsPtr(unit, 2)->poseId;
        s32 shape = animPoseGetShapeIdx(shapePose, "pPlaneShape3\0\0\0");
        animPoseDrawShape(shapePose, shape);
    }
}

