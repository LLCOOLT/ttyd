// Rogueport Sewers (tik) battle unit: Blooper (gesso), the body: its parts, defence/status tables, and attack events.
#include "eff/n64/eff_opuku_jetw_n64.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "battle/battle_pad.h"
#include "system.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_msg.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"
#include "tik.h"
#include "version.h"

#if VERSION <= VERSION_JP
static USER_FUNC(_test_rtn);
#endif
static USER_FUNC(_ikasumi_effect);

BattleUnitKind unit_boss_gesso;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
BattleUnitDefense defence_ceil;
BattleUnitDefenseAttr defence_attr_ceil;
StatusVulnerability regist_ceil;
s32 gesso_defence_turn[2];
s32 gesso_defence_attr_turn[2];
s32 gesso_regist_turn[6];
static PoseTableEntry pose_table[11];
static PoseTableEntry pose_table_ceil[12];
PoseTableEntry gesso_pose_table_turn[10];
static BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
#if VERSION <= VERSION_JP
extern EvtWord test_event[];
#endif
static EvtWord init_event[121];
BattleUnitSetup entry_gesso_left_arm_entry_data;
BattleUnitSetup entry_gesso_right_arm_entry_data;
static EvtWord damage_event[34];
#if VERSION >= VERSION_US
static EvtWord phase_event[497];
#else
static EvtWord phase_event[488];
#endif
static EvtWord attack_event[48];
BattleWeapon weapon_gesso_ikasumi_attack;
extern EvtWord gesso_ikasumi_attack[];
static EvtWord wait_event[6];
extern EvtWord dead_subevent[];

BattleUnitKind unit_boss_gesso = {
    8,
    "btl_un_gesso",
    12,
    0,
    1,
    1,
    41,
    0,
    0,
    100,
    0,
    50,
    9,
    120,
    120,
    46,
    -75,
    0.0f,
    0.0f,
    0.0f,
    5,
    -175,
    0.0f,
    0.0f,
    0.0f,
    60.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    60.0f,
    0.0f,
    0.0f,
    60.0f,
    78.0f,
    0.0f,
    0.0f,
    120.0f,
    0.0f,
    120.0f,
    110.0f,
    0,
    0,
    -1,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_GESSO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x200000,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static StatusVulnerability regist = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 0, 0, 100, 100, 0, 0, 0};

BattleUnitDefense defence_ceil = {{2, 2, 2, 2, 2}};

BattleUnitDefenseAttr defence_attr_ceil = {0};

StatusVulnerability regist_ceil = {0};

s32 gesso_defence_turn[] = {
    0, 0,
};

s32 gesso_defence_attr_turn[] = {
    0, 0,
};

s32 gesso_regist_turn[] = {
#if VERSION <= VERSION_DEMO_US
    0, 0, 0, 0, 0, 0,
#else
    1684300900, 1684300900, 1684300900, 1684300800, 6579200, 0,
#endif
};

static PoseTableEntry pose_table[] = {
    {1, "GSO_N2_1"},
#if VERSION <= VERSION_DEMO_US
    {2, "GSO_K2_1"},
    {9, "GSO_K2_1"},
#else
    {2, "GSO_D2_2"},
    {9, "GSO_D2_2"},
#endif
    {5, "GSO_K2_1"},
    {4, "GSO_X2_1"},
    {3, "GSO_K2_1"},
    {28, "GSO_S2_1"},
    {29, "GSO_Q2_1"},
    {31, "GSO_S2_1"},
    {39, "GSO_D2_1"},
    {BTL_POSE_STAY_DEFAULT, "GSO_S2_1"},
};

static PoseTableEntry pose_table_ceil[] = {
    {1, "GSO_N1_1"},
#if VERSION <= VERSION_DEMO_US
    {2, "GSO_K1_1"},
    {9, "GSO_K1_1"},
#else
    {2, "GSO_D1_3"},
    {9, "GSO_D1_3"},
#endif
    {5, "GSO_K1_1"},
    {4, "GSO_X1_1"},
    {3, "GSO_K1_1"},
    {28, "GSO_S1_1"},
    {29, "GSO_Q1_2"},
    {31, "GSO_S1_1"},
    {39, "GSO_D1_2"},
    {BTL_POSE_TALK, "GSO_K1_1"},
    {BTL_POSE_STAY_DEFAULT, "GSO_S1_1"},
};

PoseTableEntry gesso_pose_table_turn[] = {
    {1, "GSO_N3_1"},
#if VERSION <= VERSION_DEMO_US
    {2, "GSO_K3_1"},
    {9, "GSO_K3_1"},
#else
    {2, "GSO_D3_2"},
    {9, "GSO_D3_2"},
#endif
    {5, "GSO_K3_1"},
    {4, "GSO_K3_1"},
    {3, "GSO_K3_1"},
    {28, "GSO_V_1"},
    {31, "GSO_D3_1"},
    {39, "GSO_D3_1"},
    {BTL_POSE_STAY_DEFAULT, "GSO_V_1"},
};

static BattleDataEntry data_table[] = {
    {50, dead_subevent},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_gesso", "c_gesso", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 103, -175, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

#if VERSION <= VERSION_JP
/** Debug event (JP and earlier): runs _test_rtn forever. Not referenced by the unit's normal scripts. */
EVT_BEGIN(test_event)
    CALL(_test_rtn)
    RETURN
EVT_END()
#endif

/**
 * Guess: Entrance of the Blooper (Gesso) boss.
 * The Blooper surfaces (SFX_BOSS_GESSO_APPEAR1), takes its talking and idle poses,
 * and the battle camera shows it while both tentacles (left and right arm units) are spawned
 * and linked to it through unit work 1 and 2.
 */
static EVT_BEGIN(battle_entry_event)
    CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, 16777216)
    WAIT_MS(1000)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_GESSO_APPEAR1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GSO_F_4"))
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, 16777216)
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("GSO_X1_1"))
    CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("GSO_X1_2"))
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 84, 177, 558, 84, 140, 10, 30, 11)
    WAIT_FRAMES(30)
    CALL(evt_msg_print, 2, STRING("tik_02_gs_01"), 0, BTL_UNIT_SELF)
    CALL(evt_snd_sfxon_3d, STRING("SFX_CONDITION_FIND1"), 95, 65, 0, 0)
    CALL(evt_eff_fukidashi, 2, STRING(""), 0, 0, 0, 95, 65, 0, 0, 135, 60)
    WAIT_FRAMES(60)
    CALL(evt_msg_print, 2, STRING("tik_02_gs_02"), 0, BTL_UNIT_SELF)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 63, 143, 646, 63, 100, 0, 30, 11)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(10))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_gesso_left_arm_entry_data), 0)
    CALL(btlevtcmd_StopWaitEvent, LW(3))
    CALL(btlevtcmd_OnAttribute, LW(3), 16777216)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, LW(3))
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(10))
    CALL(btlevtcmd_SetPos, LW(3), 320, 6, 53)
    CALL(btlevtcmd_SetHomePos, LW(3), 320, 6, 53)
    BEGIN_INLINE_EVENT_GET_ID(LW(14))
        WAIT_FRAMES(35)
        CALL(btlevtcmd_snd_se, LW(3), STRING("SFX_BOSS_GESSO_ARM_APPEAR1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, LW(3), 1, STRING("GSO_F2_1"))
        CALL(btlevtcmd_OffAttribute, LW(3), 16777216)
        CALL(btlevtcmd_AnimeWaitPlayComplete, LW(3), 1)
        CALL(btlevtcmd_StartWaitEvent, LW(3))
    END_INLINE_EVENT
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_gesso_right_arm_entry_data), 0)
    CALL(btlevtcmd_StopWaitEvent, LW(3))
    CALL(btlevtcmd_OnAttribute, LW(3), 16777216)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, LW(3))
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(10))
    CALL(btlevtcmd_SetPos, LW(3), 59, 166, -18)
    CALL(btlevtcmd_SetHomePos, LW(3), 59, 166, -18)
    BEGIN_INLINE_EVENT_GET_ID(LW(15))
        WAIT_FRAMES(5)
        CALL(btlevtcmd_snd_se, LW(3), STRING("SFX_BOSS_GESSO_ARM_APPEAR1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, LW(3), 1, STRING("GSO_F2_1"))
        CALL(btlevtcmd_OffAttribute, LW(3), 16777216)
        CALL(btlevtcmd_AnimeWaitPlayComplete, LW(3), 1)
        CALL(btlevtcmd_StartWaitEvent, LW(3))
    END_INLINE_EVENT
#if VERSION <= VERSION_JP
    SPAWN_EVENT(test_event)
#endif
    CALL(btlevtcmd_WaitEventEnd, LW(14))
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 84, 177, 558, 84, 140, 10, 30, 11)
    WAIT_FRAMES(30)
    CALL(evt_msg_print, 2, STRING("tik_02_gs_03"), 0, BTL_UNIT_SELF)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, -117, 62, 284, -115, 43, 0, 30, 11)
    WAIT_MS(500)
    CALL(btlevtcmd_SetTalkPose, BTL_UNIT_PARTNER, STRING("PKR_T_1"))
    CALL(btlevtcmd_SetStayPose, BTL_UNIT_PARTNER, STRING("PKR_S_1"))
    CALL(evt_msg_print, 2, STRING("tik_02_gs_03_01"), 0, BTL_UNIT_PARTNER)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_PARTNER)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/**
 * Init script of the Blooper body.
 * Registers the phase and entry scripts, clears its work flags (4 and 5)
 * and starts it in the ceiling pose table.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 220)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, 2)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 6291456)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_ceil))
    CALL(btlevtcmd_SetHpGaugeOffset, BTL_UNIT_SELF, 5, -175)
    CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 46, -75)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 9, -122, 30)
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 9, -122, 30)
    CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 1, PTR(&defence_ceil))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 1, PTR(&defence_attr_ceil))
    CALL(btlevtcmd_SetRegistStatus, BTL_UNIT_SELF, PTR(&regist_ceil))
    CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 46, -75)
    CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, 16777216)
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(battle_entry_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleUnitSetup entry_gesso_left_arm_entry_data = {
    &unit_boss_gesso_left_arm, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {0.0f, -1000.0f, 0.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

BattleUnitSetup entry_gesso_right_arm_entry_data = {
    &unit_boss_gesso_right_arm, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {0.0f, -1000.0f, 0.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Damage reaction of the Blooper body.
 * Marks the body as being hit in unit work 4 (1, or 3 for a special damage pattern),
 * runs the default damage script and clears the mark.
 */
static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, 1)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, 3)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, 0)
    RETURN
EVT_END()

/**
 * Phase script of the Blooper.
 * Before the player's turn and after the enemy's turn it counts turns in work 3;
 * after two it wakes up (GSO_U_1 with the wake sounds),
 * switches to the normal pose table and changes its state in work 0 (1 to 2, then on).
 */
static EVT_BEGIN(phase_event)
#if VERSION >= VERSION_US
    CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        RETURN
    END_IF
#endif
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 3, LW(0))
            ADD(LW(0), 1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, LW(0))
            IF_INT_GREATER_OR_EQUAL(LW(0), 2)
                CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_SELF)
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GSO_U_1"))
                CALL(btlevtcmd_ftof, 75, LW(0))
                WAIT_FRAMES(LW(0))
                CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_GESSO_WAKE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
                CALL(btlevtcmd_ftof, 45, LW(0))
                WAIT_FRAMES(LW(0))
                CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_GESSO_WAKE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
                CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
                CALL(btlevtcmd_SetHpGaugeOffset, BTL_UNIT_SELF, 0, 0)
                CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 46, 118)
                CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 1, PTR(&defence))
                CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 1, PTR(&defence_attr))
                CALL(btlevtcmd_SetRegistStatus, BTL_UNIT_SELF, PTR(&regist))
                CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 55, 113)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 2)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 0)
                CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
                RETURN
            END_IF
        END_IF
    END_IF
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_ENEMY)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
        IF_INT_EQUAL(LW(0), 2)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 3, LW(0))
            ADD(LW(0), 1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, LW(0))
            IF_INT_GREATER_OR_EQUAL(LW(0), 2)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 0)
                CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_SELF)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
                CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, 2)
                CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 6291456)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_ceil))
                CALL(btlevtcmd_SetHpGaugeOffset, BTL_UNIT_SELF, 5, -175)
                CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 46, -75)
                CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
                CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 9, -122, 30)
                CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 9, -122, 30)
                CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 1, PTR(&defence_ceil))
                CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 1, PTR(&defence_attr_ceil))
                CALL(btlevtcmd_SetRegistStatus, BTL_UNIT_SELF, PTR(&regist_ceil))
                CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 46, -75)
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GSO_J_1"))
                WAIT_FRAMES(48)
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GSO_J_2"))
                SET_VALUE(LW(5), 0)
                LOOP(4)
                    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                    SWITCH(LW(5))
                        CASE_EQUAL(0)
                        ADD(LW(1), 50)
                        CASE_EQUAL(1)
                        ADD(LW(1), 75)
                        CASE_DEFAULT
                        ADD(LW(1), 100)
                    END_SWITCH
                    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_GESSO_UP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
                    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 0, 5, 0, -1)
                    ADD(LW(5), 1)
                    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                    SUBTRACT(LW(1), 30)
                    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 16, 0, 11, 0, -1)
                END_LOOP
                CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                SET_VALUE(LW(1), 220)
                CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_GESSO_APPEAR1"), EVT_NULLPTR, 0, EVT_NULLPTR)
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GSO_F_4"))
                CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
                WAIT_MS(333)
                CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(10))
                CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_gesso_left_arm_entry_data), 0)
                CALL(btlevtcmd_StopWaitEvent, LW(3))
                CALL(btlevtcmd_OnAttribute, LW(3), 16777216)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, LW(3))
                CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(10))
                CALL(btlevtcmd_SetPos, LW(3), 320, 6, 53)
                CALL(btlevtcmd_SetHomePos, LW(3), 320, 6, 53)
                BEGIN_INLINE_EVENT_GET_ID(LW(14))
                    WAIT_FRAMES(35)
                    CALL(btlevtcmd_snd_se, LW(3), STRING("SFX_BOSS_GESSO_ARM_APPEAR1"), EVT_NULLPTR, 0, EVT_NULLPTR)
                    CALL(btlevtcmd_AnimeChangePose, LW(3), 1, STRING("GSO_F2_1"))
                    CALL(btlevtcmd_OffAttribute, LW(3), 16777216)
                    CALL(btlevtcmd_AnimeWaitPlayComplete, LW(3), 1)
                    CALL(btlevtcmd_StartWaitEvent, LW(3))
                END_INLINE_EVENT
                CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_gesso_right_arm_entry_data), 0)
                CALL(btlevtcmd_StopWaitEvent, LW(3))
                CALL(btlevtcmd_OnAttribute, LW(3), 16777216)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, LW(3))
                CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(10))
                CALL(btlevtcmd_SetPos, LW(3), 59, 166, -18)
                CALL(btlevtcmd_SetHomePos, LW(3), 59, 166, -18)
                BEGIN_INLINE_EVENT_GET_ID(LW(15))
                    WAIT_FRAMES(5)
                    CALL(btlevtcmd_snd_se, LW(3), STRING("SFX_BOSS_GESSO_ARM_APPEAR1"), EVT_NULLPTR, 0, EVT_NULLPTR)
                    CALL(btlevtcmd_AnimeChangePose, LW(3), 1, STRING("GSO_F2_1"))
                    CALL(btlevtcmd_OffAttribute, LW(3), 16777216)
                    CALL(btlevtcmd_AnimeWaitPlayComplete, LW(3), 1)
                    CALL(btlevtcmd_StartWaitEvent, LW(3))
                END_INLINE_EVENT
                CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
                CALL(btlevtcmd_WaitEventEnd, LW(14))
                CALL(btlevtcmd_WaitEventEnd, LW(15))
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Attack script of the Blooper body.
 * If it is not yet awake it does nothing or runs the queued script;
 * once awake (state 2) it uses the ink attack gesso_ikasumi_attack.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 2)
        GOTO(99)
    END_IF
    CALL_CHILD(gesso_ikasumi_attack)
    RETURN
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon weapon_gesso_ikasumi_attack = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, // baseFpCost..baseSpCost
#if VERSION >= VERSION_US
    2, // superguardsAllowed
#else
    0, // superguardsAllowed
#endif
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {1, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, // element
    13, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * The Blooper's ink attack (ikasumi = squid ink).
 * It picks the opposing side, aims at all targets, winds up with the GSO_A2_1 animation,
 * spits black ink (_ikasumi_effect with the ink sound) and deals damage to each target,
 * whose action command can reduce it; it ends by returning the Blooper to its wait pose.
 */
EVT_BEGIN(gesso_ikasumi_attack)
    SET_VALUE(LW(12), PTR(&weapon_gesso_ikasumi_attack))
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GSO_A2_1"))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_ftof, 16, LW(0))
        WAIT_FRAMES(LW(0))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_GESSO_UP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_ftof, 55, LW(0))
        WAIT_FRAMES(LW(0))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_GESSO_UP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    CALL(btlevtcmd_ftof, 120, LW(0))
    WAIT_FRAMES(LW(0))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_ftof, 90, LW(7))
    CALL(_ikasumi_effect, BTL_UNIT_SELF, LW(7))
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_GESSO_SUMI1"), EVT_NULLPTR, 0, LW(15))
        WAIT_FRAMES(LW(7))
        CALL(evt_snd_sfxoff, LW(15))
    END_INLINE_EVENT
    CALL(btlevtcmd_ftof, 10, LW(0))
    WAIT_FRAMES(LW(0))
    SET_VALUE(LW(10), 0)
    LABEL(50)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    IF_INT_NOT_EQUAL(LW(5), 1)
        SWITCH(LW(5))
            CASE_EQUAL(3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
            CASE_EQUAL(6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
            CASE_EQUAL(2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_SWITCH
    ELSE
        IF_INT_EQUAL(LW(10), 0)
            CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
        END_IF
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    END_IF
    ADD(LW(10), 1)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        GOTO(50)
    END_IF
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    LABEL(99)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Script helper.
 * Spawns the black ink spray (OpukuJetw effect) at 95 units left and 75 above the unit args[0],
 * lasting args[1] frames and rotated 135 degrees.
 */
static USER_FUNC(_ikasumi_effect) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 count = evtGetValue(event, args[1]);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    Vec pos;
    EffectEntry* eff;

    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x -= 95.0f;
    pos.y += 75.0f;
    eff = effOpukuJetwN64Entry(0, count, pos.x, pos.y, pos.z, 2.0f);
    ((EffOpukuJetwN64Work*)eff->userdata)->rotZ = 135.0f;
    ((EffOpukuJetwN64Work*)eff->userdata)->colorR = 0;
    ((EffOpukuJetwN64Work*)eff->userdata)->colorG = 0;
    ((EffOpukuJetwN64Work*)eff->userdata)->colorB = 0;
    ((EffOpukuJetwN64Work*)eff->userdata)->color2R = 0;
    ((EffOpukuJetwN64Work*)eff->userdata)->color2G = 0;
    ((EffOpukuJetwN64Work*)eff->userdata)->color2B = 0;
    return EVT_RETURN_DONE;
}

#if VERSION <= VERSION_JP
/**
 * Debug routine (JP and earlier).
 * Lets the d-pad select the Blooper or one of its two tentacles,
 * then resizes the unit with the buttons and moves it with the sticks, every frame.
 */
static USER_FUNC(_test_rtn) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit;
    BattleUnit* target;
    s32 targetId;

    if (id == -1) {
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    if (unit == NULL) {
        return EVT_RETURN_DONE;
    }
    if (isFirstCall) {
        event->userdata[0] = 0;
    }
    // debug: pick a unit with the d-pad, then scale and move it
    if (BattlePadMultiCheckTrigger(2, 1)) {
        event->userdata[0]++;
        if (event->userdata[0] >= 3) {
            event->userdata[0] = 0;
        }
    }
    if (BattlePadMultiCheckTrigger(2, 2)) {
        event->userdata[0]--;
        if (event->userdata[0] < 0) {
            event->userdata[0] = 2;
        }
    }
    switch (event->userdata[0]) {
        case 0:
            targetId = BattleTransID(event, -2);
            break;
        case 1:
            targetId = unit->work[1];
            break;
        case 2:
            targetId = unit->work[2];
            break;
    }
    target = BattleGetUnitPtr(wp, targetId);
    BattlePadMultiCheckTrigger(2, 3);
    if (BattlePadMultiCheckNow(2, 0x40)) {
        target->scale.x += 0.02f;
        target->scale.y += 0.02f;
        target->scale.z += 0.02f;
    }
    if (BattlePadMultiCheckNow(2, 0x20)) {
        target->scale.x -= 0.02f;
        target->scale.y -= 0.02f;
        target->scale.z -= 0.02f;
    }
    target->position.x += 0.1f * keyGetStickX(2);
    target->position.y += 0.1f * keyGetSubStickY(2);
    target->position.z -= 0.1f * keyGetStickY(2);
    BattlePadMultiCheckTrigger(2, 0x100);
    return EVT_RETURN_BLOCK;
}
#endif

/** Wait script of the Blooper body: shows its idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Runs when the Blooper dies.
 * It kills both tentacles (the units held in its work slots 1 and 2), each in a parallel event,
 * and waits for both to finish.
 */
EVT_BEGIN(dead_subevent)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(3))
    CALL(btlevtcmd_GetUnitId, LW(3), LW(3))
    BEGIN_SIBLING_EVENT_GET_ID(LW(1))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_KillUnit, LW(3), 0)
        END_IF
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 2, LW(3))
    CALL(btlevtcmd_GetUnitId, LW(3), LW(3))
    BEGIN_SIBLING_EVENT_GET_ID(LW(2))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_KillUnit, LW(3), 0)
        END_IF
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(1))
    CALL(btlevtcmd_WaitEventEnd, LW(2))
    RETURN
EVT_END()
