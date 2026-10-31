// Battle unit for Mario (マリオ) acting in Flurrie's stage play in the epilogue (nok.rel); it only plays its
// scripted part.

#include "battle/battle_unit.h"
#include "eff/n64/eff_kumokumo_n64.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "evt/evt_msg.h"
#include "evt/evt_sub.h"
#include "unit/party/unit_party_christine.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_audience.h"
#include "evt/evt_eff.h"
#include "nok.h"
#include "version.h"

// Unit work slots of the Mario actor of the stage play (btlevtcmd_SetUnitWork / GetUnitWork).
enum {
    UW_ACT_MARIO_SELF = 0,       // its own unit id
    UW_ACT_MARIO_CLAUDA = 1,     // unit id of Clauda (Flurrie)
    UW_ACT_MARIO_BOO_1 = 2,      // unit id of the first Boo
    UW_ACT_MARIO_BOO_2 = 3,      // unit id of the second Boo
    UW_ACT_MARIO_ATOMIC_BOO = 4, // unit id of the Atomic Boo
    UW_ACT_MARIO_TOAD_1 = 5,     // unit id of the first Toad
    UW_ACT_MARIO_TOAD_2 = 6,     // unit id of the second Toad
    UW_ACT_MARIO_TOADETTE = 7,   // unit id of Toadette
    UW_ACT_MARIO_GOOMBELLA = 8   // unit id of Goombella
};

static USER_FUNC(_clauda_breath_effect_fire);
static USER_FUNC(_clauda_breath_effect_ready);
static USER_FUNC(_status_window_off);

BattleUnitKind unit_act_mario;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[7];
static BattleDataEntry data_table[1];
static BattleUnitKindPart parts[1];
static EvtWord init_event[15];
static EvtWord wait_event[6];
BattleUnitSetup entry_unit_data[8];
static EvtWord battle_entry_event[168];
extern EvtWord _battle_event[];
extern EvtWord _act_mario_jump_attack[];
extern EvtWord _act_clauda_press_attack[];
extern EvtWord _act_clauda_breath_attack[];
extern EvtWord _act_teresa_attack[];
extern EvtWord _act_atmic_teresa_press_attack[];

/**
 * Unit kind of the Mario actor (HP 10, level 1):
 * its size, offsets, damage sounds, status vulnerability, parts and init event.
 */
BattleUnitKind unit_act_mario = {
    181,
    "btl_un_act_mario",
    10,
    0,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    100,
    9,
    28,
    24,
    5,
    25,
    0.0f,
    14.0f,
    0.0f,
    0,
    0,
    0.0f,
    30.0f,
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
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BTL_DAMAGE1",
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

/** Defence of the Mario actor: no damage reduction. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Element reactions of the Mario actor: no special reaction to any element. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/**
 * Status vulnerability of the Mario actor (percent chance to take each status):
 * immune to sleep, stop, dizzy, poison, confusion, electric shock, burn, freeze, growing huge, shrinking,
 * attack up, attack down, defence up, defence down, allergy, fright, gale force, speed up, slow, dodgy,
 * invisibility and instant kill.
 */
static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/** Pose table of the Mario actor: maps each battle pose to the animation it plays (EM_* animations). */
static PoseTableEntry pose_table[] = {
    {28, "EM_S_1"},
    {31, "KNP_S_1"},
    {39, "EM_D_1"},
    {42, "EM_R_1"},
    {40, "EM_W_1"},
    {BTL_POSE_TALK, "EM_T_1"},
    {BTL_POSE_STAY_DEFAULT, "EM_S_1"},
};

/** Data table of the Mario actor: empty; it has no event hooks. */
static BattleDataEntry data_table[] = {
    {0, NULL},
};

/** Body part of the Mario actor (model c_mario): hit position, defences, attributes and pose table. */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_act_mario", "c_mario", 0.0f, 0.0f, 0.0f, -5.0f, 30.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

/**
 * Init event of the Mario stage actor: installs the wait event and battle_entry_event as the entry event,
 * hides the status window and starts the wait event. This unit runs the whole stage play.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(battle_entry_event))
    CALL(_status_window_off)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of the Mario stage actor: runs the default damage handling with LW(10) = -2 and LW(11) = 1. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/** Phase event of the Mario stage actor: does nothing. */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/** Attack event of the Mario stage actor: just restarts the wait event; the play is driven by _battle_event. */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Idle event of the Mario stage actor: shows the unit's table pose for state 1. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Cast of Flurrie's epilogue stage play: Flurrie as Clauda, two Boos, the Atomic Boo, two Toads,
 * Toadette and Goombella, with their starting spots.
 */
BattleUnitSetup entry_unit_data[] = {
    {
        &unit_act_clauda, // unitKindParams
        0, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {-140.0f, 0.0f, 5.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        NULL, // itemDropTable
    },
    {
        &unit_act_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {45.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        NULL, // itemDropTable
    },
    {
        &unit_act_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {85.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        NULL, // itemDropTable
    },
    {
        &unit_act_atmic_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        NULL, // itemDropTable
    },
    {
        &unit_act_kinopio, // unitKindParams
        2, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {-75.0f, 0.0f, -40.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        NULL, // itemDropTable
    },
    {
        &unit_act_kinopio, // unitKindParams
        2, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {-15.0f, 0.0f, -40.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        NULL, // itemDropTable
    },
    {
        &unit_act_kinopiko, // unitKindParams
        2, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {-45.0f, 0.0f, -40.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        NULL, // itemDropTable
    },
    {
        &unitdata_Party_Christine, // unitKindParams
        2, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {0.0f, -50.0f, 110.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        NULL, // itemDropTable
    },
};

/**
 * Entry of Flurrie's stage play "Paper Mario" (her epilogue):
 * hides the status window, places Mario's actor at Mario's spot
 * and moves the real Mario off the left edge of the stage, and keeps its own unit id in unit work 0.
 * It spawns the eight other actors of entry_unit_data (Flurrie as Clauda, two Boos, the Atomic Boo, two Toads,
 * Toadette and Goombella), keeping their unit ids in unit work 1 to 8, and starts _battle_event.
 * After two seconds the narration (ep_39) tells of Flurrie's hit play about the adventure,
 * with Doopliss in the troupe; then battle flag 32 is set.
 */
static EVT_BEGIN(battle_entry_event)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_MARIO, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_GetStageSize, LW(6), EVT_NULLPTR, EVT_NULLPTR)
    MULTIPLY(LW(6), -1)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_MARIO, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_MARIO, LW(6), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_SELF, LW(0))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_unit_data[0]), 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_CLAUDA, LW(3))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_unit_data[1]), 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_BOO_1, LW(3))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_unit_data[2]), 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_BOO_2, LW(3))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_unit_data[3]), 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_ATOMIC_BOO, LW(3))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_unit_data[4]), 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_TOAD_1, LW(3))
    CALL(btlevtcmd_ChangeFaceDirection, LW(3), 1)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_unit_data[5]), 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_TOAD_2, LW(3))
    CALL(btlevtcmd_ChangeFaceDirection, LW(3), 1)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_unit_data[6]), 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_TOADETTE, LW(3))
    CALL(btlevtcmd_ChangeFaceDirection, LW(3), 1)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_unit_data[7]), 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_GOOMBELLA, LW(3))
    CALL(btlevtcmd_ChangeFaceDirection, LW(3), 1)
    SPAWN_EVENT(_battle_event)
    WAIT_MS(2000)
    CALL(evt_msg_print, 2, STRING("ep_39"), 0, BTL_UNIT_SELF)
    WAIT_MS(1000)
    CALL(btlevtcmd_onoff_battleflag, 1, 32)
    RETURN
EVT_END()

/**
 * Looping stage-play script: Mario jumps on an enemy actor,
 * then Flurrie (Clauda) attacks (a body press or her breath, 50/50) and strikes a pose,
 * then the two Boos (Teresas) and the Atomic Boo each take a turn,
 * and a Toad and Toadette each say a line (talk pose).
 * It repeats forever; nothing in it ends the battle.
 */
EVT_BEGIN(_battle_event)
    LABEL(0)
    CALL_CHILD(_act_mario_jump_attack)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_CLAUDA, LW(5))
    CALL(btlevtcmd_GetBodyId, LW(5), LW(6))
    CALL(evt_sub_random, 1, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL_CHILD(_act_clauda_press_attack)
    ELSE
        CALL_CHILD(_act_clauda_breath_attack)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("PWD_A_7"))
    WAIT_MS(1000)
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_NORMAL)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_BOO_1, LW(5))
    CALL(btlevtcmd_GetBodyId, LW(5), LW(6))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_TALK)
    WAIT_MS(1000)
    CALL_CHILD(_act_teresa_attack)
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_NORMAL)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_BOO_2, LW(5))
    CALL(btlevtcmd_GetBodyId, LW(5), LW(6))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_TALK)
    WAIT_MS(1000)
    CALL_CHILD(_act_teresa_attack)
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_NORMAL)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_ATOMIC_BOO, LW(5))
    CALL(btlevtcmd_GetBodyId, LW(5), LW(6))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_TALK)
    WAIT_MS(1000)
    CALL_CHILD(_act_atmic_teresa_press_attack)
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_NORMAL)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_TOAD_1, LW(5))
    CALL(btlevtcmd_GetBodyId, LW(5), LW(6))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_TALK)
    WAIT_MS(1500)
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_NORMAL)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_TOADETTE, LW(5))
    CALL(btlevtcmd_GetBodyId, LW(5), LW(6))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_TALK)
    WAIT_MS(1500)
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_NORMAL)
    GOTO(0)
    RETURN
EVT_END()

/**
 * Picks a random enemy actor of the play (unit work 2, 3 or 4: the two Boos and the Atomic Boo) as the target:
 * returns its unit id in LW(3) and its body id in LW(4).
 */
EVT_BEGIN(_act_target_enemy)
    CALL(evt_sub_random, 2, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_BOO_1, LW(3))
        CASE_EQUAL(1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_BOO_2, LW(3))
        CASE_DEFAULT
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_ATOMIC_BOO, LW(3))
    END_SWITCH
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    RETURN
EVT_END()

/**
 * Picks Mario (unit work 0) or Clauda (unit work 1) as the target of a Boo attack:
 * returns the unit id in LW(3) and the body id in LW(4).
 */
EVT_BEGIN(_act_target_mario)
    CALL(evt_sub_random, 1, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_SELF, LW(3))
        CASE_DEFAULT
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_CLAUDA, LW(3))
    END_SWITCH
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    RETURN
EVT_END()

/**
 * Mario's part of the play: after a talk pose he runs up
 * and jumps on a random enemy actor (which gets a hit effect, a cheer from the audience and its hurt pose),
 * bounces back with a few smaller hops and runs to his home position.
 */
EVT_BEGIN(_act_mario_jump_attack)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_TALK)
    WAIT_MS(1000)
    CALL_CHILD(_act_target_enemy)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    SET_VALUE(LW(0), -20)
    SET_VALUE(LW(1), 0)
    SET_VALUE(LW(2), 0)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(6))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(6))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_J_1B"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    ADD(LW(2), 5)
    SET_VALUE(LW(6), 36)
    CALL(btlevtcmd_MarioJumpParam, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(6))
    CALL(btlevtcmd_MarioJumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(6), 3, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_J_1D"))
    WAIT_MS(50)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_StopWaitEvent, LW(3))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        ADD(LW(2), 5)
        CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
        CALL(evt_audience_joy_ending)
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), BTL_POSE_DAMAGE)
        WAIT_MS(1000)
        CALL(btlevtcmd_StartWaitEvent, LW(3))
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_J_1B"))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 27)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5996094f))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 8)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 8, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_R_1"))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    RETURN
EVT_END()

/**
 * Flurrie's (Clauda's) body press: Flurrie (unit in LW(5), body in LW(6)) leaps onto a random enemy actor
 * and squashes it flat while she squashes and stretches,
 * then bounces off and poses (PWD_Y_1) with the audience cheering and floats home; the victim springs back up.
 */
EVT_BEGIN(_act_clauda_press_attack)
    // Flurrie pauses on stage, picks a random actor to flatten and turns toward it.
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_TALK)
    WAIT_MS(1000)
    CALL_CHILD(_act_target_enemy)
    CALL(btlevtcmd_CalculateFaceDirection, LW(5), -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, LW(5), LW(15))
    // She leaps high over the stage and comes down on the victim.
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("PWD_A1_1"))
    CALL(btlevtcmd_SetFallAccel, LW(5), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    ADD(LW(2), 5)
    CALL(btlevtcmd_JumpPosition, LW(5), LW(0), LW(1), LW(2), 60, -1)
    // The victim is squashed flat, stays pressed for a moment, then springs back up to its full height.
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), BTL_POSE_DAMAGE)
        CALL(evt_sub_intpl_init_float, 5, FLOAT(1.0f), FLOAT(0.14941406f), 10)
        LOOP(11)
            CALL(evt_sub_intpl_get_float, LW(7), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, LW(3), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, LW(3), LW(0), LW(7), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
        WAIT_MS(1500)
        CALL(evt_sub_intpl_init_float, 5, FLOAT(0.14941406f), FLOAT(1.25f), 10)
        LOOP(11)
            CALL(evt_sub_intpl_get_float, LW(7), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, LW(3), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, LW(3), LW(0), LW(7), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_init_float, 7, FLOAT(1.25f), FLOAT(1.0f), 30)
        LOOP(31)
            CALL(evt_sub_intpl_get_float, LW(7), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, LW(3), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, LW(3), LW(0), LW(7), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
        WAIT_MS(500)
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), BTL_POSE_NORMAL)
    END_SIBLING_EVENT
    // Flurrie squashes on landing and stretches wide as she bounces off.
    CALL(btlevtcmd_JumpContinue, LW(5))
    BEGIN_SIBLING_EVENT_GET_ID(LW(14))
        CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(0.39941406f), 10)
        LOOP(10)
            CALL(evt_sub_intpl_get_float, LW(7), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, LW(5), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, LW(5), LW(0), LW(7), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_init_float, 11, FLOAT(0.39941406f), FLOAT(1.0f), 6)
        LOOP(6)
            CALL(evt_sub_intpl_get_float, LW(7), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, LW(5), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, LW(5), LW(0), LW(7), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(1.5f), 10)
        LOOP(10)
            CALL(evt_sub_intpl_get_float, LW(7), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, LW(5), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, LW(5), LW(7), LW(1), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_init_float, 11, FLOAT(1.5f), FLOAT(1.0f), 6)
        LOOP(6)
            CALL(evt_sub_intpl_get_float, LW(7), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, LW(5), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, LW(5), LW(7), LW(1), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    // She hops off the victim, strikes her victory pose and the audience cheers.
    CALL(btlevtcmd_GetPos, LW(5), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(5), LW(0), 20)
    ADD(LW(1), 20)
    CALL(btlevtcmd_SetRotate, LW(5), 0, 0, 0)
    CALL(btlevtcmd_SetFallAccel, LW(5), FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPosition, LW(5), LW(0), LW(1), LW(2), 18, -1)
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("PWD_Y_1"))
    CALL(evt_audience_joy_ending)
    WAIT_MS(500)
    CALL(btlevtcmd_WaitEventEnd, LW(14))
    // She floats back to her spot on stage.
    CALL(btlevtcmd_SetMoveSpeed, LW(5), FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_WALK)
    CALL(btlevtcmd_GetHomePos, LW(5), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetMoveFrame, LW(5), LW(0), LW(1), LW(2), FLOAT(6.0f), LW(9))
    CALL(btlevtcmd_DivePosition, LW(5), LW(0), LW(1), LW(2), LW(9), 0, 4, 0, -1)
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_NORMAL)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    RETURN
EVT_END()

/**
 * Flurrie's (Clauda's) breath: she winds up (blue-violet smoke puffs), breathes at all three enemy actors,
 * who each get a hit effect and a cheer and shake while the breath lasts, then the effect is removed,
 * she poses and the audience cheers.
 */
EVT_BEGIN(_act_clauda_breath_attack)
    CALL(btlevtcmd_JumpSetting, LW(5), 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_TALK)
    WAIT_MS(1000)
    CALL(_clauda_breath_effect_ready)
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("PWD_A2_1"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, LW(5), LW(6))
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("PWD_A2_2"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, LW(5), LW(6))
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("PWD_A2_3"))
    CALL(_clauda_breath_effect_fire, LW(12))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_BOO_1, LW(3))
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    BEGIN_SIBLING_EVENT_GET_ID(LW(13))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        ADD(LW(2), 5)
        CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
        CALL(evt_audience_joy_ending)
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), BTL_POSE_DAMAGE)
        LOOP(30)
            CALL(btlevtcmd_SetDispOffset, LW(3), 2, 0, 0)
            WAIT_FRAMES(2)
            CALL(btlevtcmd_SetDispOffset, LW(3), 0, 0, 0)
            WAIT_FRAMES(2)
        END_LOOP
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), BTL_POSE_NORMAL)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_BOO_2, LW(3))
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    BEGIN_SIBLING_EVENT_GET_ID(LW(14))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        ADD(LW(2), 5)
        CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
        CALL(evt_audience_joy_ending)
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), BTL_POSE_DAMAGE)
        LOOP(30)
            CALL(btlevtcmd_SetDispOffset, LW(3), 2, 0, 0)
            WAIT_FRAMES(2)
            CALL(btlevtcmd_SetDispOffset, LW(3), 0, 0, 0)
            WAIT_FRAMES(2)
        END_LOOP
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), BTL_POSE_NORMAL)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_ATOMIC_BOO, LW(3))
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        ADD(LW(2), 5)
        CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
        CALL(evt_audience_joy_ending)
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), BTL_POSE_DAMAGE)
        LOOP(30)
            CALL(btlevtcmd_SetDispOffset, LW(3), 2, 0, 0)
            WAIT_FRAMES(2)
            CALL(btlevtcmd_SetDispOffset, LW(3), 0, 0, 0)
            WAIT_FRAMES(2)
        END_LOOP
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), BTL_POSE_NORMAL)
    END_SIBLING_EVENT
    WAIT_FRAMES(120)
    CALL(evt_eff_delete_ptr, LW(12))
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("PWD_Y_1"))
    CALL(evt_audience_joy_ending)
    WAIT_MS(1000)
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_NORMAL)
    RETURN
EVT_END()

/**
 * A Boo's attack in the play: the Boo (unit in LW(5), body in LW(6)) fades out,
 * reappears beside Mario or Flurrie (picked at random), hits it, and floats back home;
 * the target gets a hit effect and its hurt pose and the audience cheers.
 */
EVT_BEGIN(_act_teresa_attack)
    CALL_CHILD(_act_target_mario)
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_RUN)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetAlpha, LW(5), LW(6), 255)
        SET_VALUE(LW(7), 256)
        LOOP(16)
            WAIT_FRAMES(1)
            SUBTRACT(LW(7), 16)
            CALL(btlevtcmd_SetAlpha, LW(5), LW(6), LW(7))
        END_LOOP
        WAIT_FRAMES(20)
        CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("A_1"))
        CALL(btlevtcmd_SetAlpha, LW(5), LW(6), 0)
        SET_VALUE(LW(7), -1)
        LOOP(8)
            WAIT_FRAMES(1)
            ADD(LW(7), 32)
            CALL(btlevtcmd_SetAlpha, LW(5), LW(6), LW(7))
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, LW(5), LW(0), 20)
    SUBTRACT(LW(1), 10)
    CALL(btlevtcmd_DivePosition, LW(5), LW(0), LW(1), LW(2), 60, -5, 4, 0, -1)
    CALL(btlevtcmd_SetAlpha, LW(5), LW(6), 255)
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("A_2"))
    WAIT_MS(250)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_StopWaitEvent, LW(3))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        ADD(LW(2), 5)
        CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
        CALL(evt_audience_joy_ending)
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), BTL_POSE_DAMAGE)
        WAIT_MS(1000)
        CALL(btlevtcmd_StartWaitEvent, LW(3))
    END_SIBLING_EVENT
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), BTL_POSE_RUN)
    CALL(btlevtcmd_AddPartsRotate, LW(5), LW(6), 0, 180, 0)
    CALL(btlevtcmd_GetHomePos, LW(5), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, LW(5), LW(0), LW(1), LW(2), 40, 0, 4, 0, -1)
    CALL(btlevtcmd_SetPartsRotate, LW(5), LW(6), 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), BTL_POSE_NORMAL)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    RETURN
EVT_END()

/**
 * The Atomic Boo's attack in the play: it rises above the left side of the stage and drops onto Mario
 * and Flurrie, both getting a hit effect, their hurt pose and a cheer, then it returns to its home position.
 */
EVT_BEGIN(_act_atmic_teresa_press_attack)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_SELF, LW(3))
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("R_1"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    SUBTRACT(LW(2), 10)
    CALL(btlevtcmd_DivePosition, LW(5), -125, 100, LW(2), 120, 10, 4, 0, -1)
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("Z_1"))
    CALL(btlevtcmd_DivePosition, LW(5), -125, 0, LW(2), 30, 0, 1, 0, -1)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_SELF, LW(3))
        CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
        CALL(btlevtcmd_StopWaitEvent, LW(3))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        ADD(LW(2), 5)
        CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
        CALL(evt_audience_joy_ending)
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), BTL_POSE_DAMAGE)
        WAIT_MS(1000)
        CALL(btlevtcmd_StartWaitEvent, LW(3))
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT_GET_ID(LW(14))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_ACT_MARIO_CLAUDA, LW(3))
        CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
        CALL(btlevtcmd_StopWaitEvent, LW(3))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        ADD(LW(2), 5)
        CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
        CALL(evt_audience_joy_ending)
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), BTL_POSE_DAMAGE)
        WAIT_MS(1000)
        CALL(btlevtcmd_StartWaitEvent, LW(3))
    END_SIBLING_EVENT
    WAIT_MS(1000)
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("W_1"))
    CALL(btlevtcmd_GetHomePos, LW(5), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, LW(5), LW(0), LW(1), LW(2), 60, 50, 6, 0, -1)
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("S_1"))
    RETURN
EVT_END()

/**
 * Script helper: spawns the smoke puff effect (effKumokumoN64Entry, blue-to-violet colours) in front of the
 * current battle unit that is about to breathe.
 * Stores the effect pointer in the script variable args[0] so the script can delete it later.
 */
static USER_FUNC(_clauda_breath_effect_fire) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id;
    BattleUnit* unit;
    s32 var;
    Vec pos;
    EffectEntry* eff;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    var = args[0];
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x += unit->sizeMultiplier * (unit->faceDirection * 25);
    pos.y += 15.0f * unit->sizeMultiplier;
    eff = effKumokumoN64Entry(0, 0, pos.x, pos.y, pos.z, 0.0f, -2.0f, 1.0f);
    ((EffKumokumoN64Particle*)eff->userdata)->r1 = 76;
    ((EffKumokumoN64Particle*)eff->userdata)->g1 = 167;
    ((EffKumokumoN64Particle*)eff->userdata)->b1 = 202;
    ((EffKumokumoN64Particle*)eff->userdata)->r2 = 125;
    ((EffKumokumoN64Particle*)eff->userdata)->g2 = 27;
    ((EffKumokumoN64Particle*)eff->userdata)->b2 = 245;
    ((EffKumokumoN64Particle*)eff->userdata)->rot = -10.0f;
    evtSetValue(event, var, (EvtWord)eff);
    return EVT_RETURN_DONE;
}

/** Script helper: spawns the smaller smoke puff effect in front of Clauda while she winds up her breath attack. */
static USER_FUNC(_clauda_breath_effect_ready) {
    BattleWork* wp = _battleWorkPointer;
    s32 id;
    BattleUnit* unit;
    Vec pos;
    EffectEntry* eff;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x += unit->sizeMultiplier * (unit->faceDirection * 20);
    pos.y += 25.0f * unit->sizeMultiplier;
    eff = effKumokumoN64Entry(0, 60, pos.x, pos.y, pos.z, 0.0f, 2.0f, 1.0f);
    ((EffKumokumoN64Particle*)eff->userdata)->r1 = 76;
    ((EffKumokumoN64Particle*)eff->userdata)->g1 = 167;
    ((EffKumokumoN64Particle*)eff->userdata)->b1 = 202;
    ((EffKumokumoN64Particle*)eff->userdata)->r2 = 125;
    ((EffKumokumoN64Particle*)eff->userdata)->g2 = 27;
    ((EffKumokumoN64Particle*)eff->userdata)->b2 = 245;
    return EVT_RETURN_DONE;
}

/**
 * Script helper: turns the battle status window off (statusWindowOff = 1)
 * so it does not show during the stage play.
 */
static USER_FUNC(_status_window_off) {
    _battleWorkPointer->statusWindowOff = 1;
    return EVT_RETURN_DONE;
}
