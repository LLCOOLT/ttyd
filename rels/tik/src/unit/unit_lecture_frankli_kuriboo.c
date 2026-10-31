// Rogueport Sewers (tik) battle unit: Professor Frankly (frankli) in his lecture battle: its parts, defence/status
// tables, and the lecture events.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_event_default.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_cmd.h"
#include "evt/evt_msg.h"

// Unit work slots of the Goomba in Professor Frankly's lecture.
enum {
    UW_LECTURE_FRANKLI_KURIBOO_SPIKE_TIP_GIVEN = 0, // 1 once Frankly explained the spiky Goomba's spike (set by unit_togekuri)
};

static USER_FUNC(_battle_set_lecture_unit_id);
static USER_FUNC(lecture_init);

BattleUnitKind unit_lecture_frankli_kuriboo;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[5];
static BattleDataEntry data_table[1];
static BattleUnitKindPart parts[1];
static EvtWord init_event[53];
static EvtWord entry_event[29];
#if VERSION <= VERSION_DEMO_US
static EvtWord phase_event[148];
#else
static EvtWord phase_event[160];
#endif
static EvtWord damage_event[10];
static EvtWord wait_event[6];

/** Script helper for the lecture Goomba's init script; does nothing. */
static USER_FUNC(lecture_init) {
    return EVT_RETURN_DONE;
}

/** Script helper. Stores args[0] in the battle's lectureUnitId, the unit that the lecture is aimed at. */
static USER_FUNC(_battle_set_lecture_unit_id) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 value;

    value = evtGetValue(event, *args++);
    wp->lectureUnitId = value;
    return EVT_RETURN_DONE;
}

/**
 * Unit kind of the Goomba in Prof.
 * Frankly's lecture (HP 10, level 1): its size, offsets, damage sounds, status vulnerability,
 * parts and init event.
 */
BattleUnitKind unit_lecture_frankli_kuriboo = {
    180,
    "btl_un_frankli",
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
    "SFX_ENM_KURI_DAMAGED11",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_NO_HP_GAUGE | UNIT_ATTR_IGNORE_FOR_CLEAR,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/** Defence of the Goomba in Prof. Frankly's lecture: no damage reduction. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Element reactions of the Goomba in Prof. Frankly's lecture: no special reaction to any element. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/**
 * Status vulnerability of the Goomba in Prof.
 * Frankly's lecture (percent chance to take each status):
 * immune to sleep, stop, dizzy, poison, confusion, electric shock, burn, freeze, growing huge, shrinking,
 * attack up, attack down, defence up, defence down, allergy, fright, gale force, speed up, slow, dodgy,
 * invisibility and instant kill.
 */
static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/**
 * Pose table of the Goomba in Prof.
 * Frankly's lecture: maps each battle pose to the animation it plays (D_* animations).
 */
static PoseTableEntry pose_table[] = {
    {27, "D_1"},
    {BTL_POSE_NORMAL, "S_1"},
    {31, "D_2"},
    {BTL_POSE_DAMAGE, "D_2"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

/** Data table of the Goomba in Prof. Frankly's lecture: empty; it has no event hooks. */
static BattleDataEntry data_table[] = {
    {0, NULL},
};

/**
 * Body part of the Goomba in Prof.
 * Frankly's lecture (model c_kuri_h): hit position, defences, attributes and pose table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_frankli", "c_kuri_h", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_NOT_TARGETABLE | PART_ATTR_UNTATTLEABLE | PART_ATTR_NO_HP_LOSS, 0, pose_table},
};

/**
 * Init script of the Goomba in Professor Frankly's lecture battle.
 * It uses the default confusion script, clears its work flag and starts waiting.
 */
static EVT_BEGIN(init_event)
    CALL(lecture_init)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(entry_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    CALL(_battle_set_lecture_unit_id, LW(0))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_KURIBOO_SPIKE_TIP_GIVEN, 0)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 0, -1000, 0)
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_SetMaxMoveCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Entrance of the lecture Goomba: it runs in (R_1) and settles into its idle pose (S_1). */
static EVT_BEGIN(entry_event)
    WAIT_MS(900)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, -250, 0, -30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_1"))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, -60, 0, -30, 45, -1, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    RETURN
EVT_END()

/** Phase script of the lecture Goomba: puts Mario back in his idle pose (M_S_1) during the lecture's phases. */
static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_get_turn, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_MARIO)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_S_1"))
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("S_1"))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(evt_msg_print, 2, STRING("mac_0_092_01"), 0, BTL_UNIT_SELF)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, 71, 49, 213, 71, 35, 0, 30, 11)
            WAIT_FRAMES(30)
#if VERSION >= VERSION_JP
            CALL(evt_msg_toge, 1, 0, 0, 0)
#endif
            CALL(evt_msg_print, 2, STRING("mac_0_092_02"), 0, BTL_UNIT_SELF)
            CALL(evt_btl_camera_set_moveto, 0, 111, 85, 213, 111, 71, 0, 30, 11)
            WAIT_FRAMES(30)
#if VERSION >= VERSION_JP
            CALL(evt_msg_toge, 1, 0, 0, 0)
#endif
            CALL(evt_msg_print, 2, STRING("mac_0_092_03"), 0, BTL_UNIT_SELF)
            CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, -1)
            CALL(evt_btl_camera_set_mode, 0, 0)
            WAIT_FRAMES(60)
            CALL(evt_msg_print, 2, STRING("mac_0_092_04"), 0, BTL_UNIT_SELF)
            CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, 1)
            WAIT_MS(1500)
            CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, -1)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, -60, 82, 340, -60, 60, 13, 30, 11)
            WAIT_FRAMES(30)
            CALL(evt_msg_print, 2, STRING("mac_0_092_05"), 0, BTL_UNIT_SELF)
            CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, 1)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(evt_btl_camera_set_mode, 0, 0)
            GOTO(99)
        END_IF
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/** Damage reaction of the lecture Goomba: the default damage script. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/** Wait script of the lecture Goomba: shows its idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
