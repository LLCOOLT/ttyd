// unit_lecture_frankli_sac: Professor Frankly in the special-action-command (star power) tutorial battle.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "driver/camdrv.h"
#include "manager/evtmgr_cmd.h"
#include "driver/dispdrv.h"
#include "system.h"
#include "battle/battle.h"
#include "battle/battle_audience.h"
#include "battle/battle_unit.h"
#include "battle/battle_event_default.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_cmd.h"
#include "evt/evt_msg.h"
#include "statuswindow.h"

// Unit work slots of Professor Frankly in the Star Power lesson (btlevtcmd_SetUnitWork / GetUnitWork).
enum {
    UW_LECTURE_FRANKLI_SAC_STEP = 0,         // lesson step (0 to 3)
    UW_LECTURE_FRANKLI_SAC_GOOD_RESULTS = 1, // good action command results he has commented on
    UW_LECTURE_FRANKLI_SAC_BAD_RESULTS = 2   // missed action commands he has commented on
};

u8 dark;
s32 darkCount;
f32 point[4];
#include "battle/battle_break_slot.h"

static USER_FUNC(_battle_set_lecture_unit_id);
static USER_FUNC(_set_actend_event);
static USER_FUNC(lecture_init);
static void spot_square_disp(CameraId cameraId, void* param);

BattleUnitKind unit_lecture_frankli_sac;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleDataEntry data_table[1];
static BattleUnitKindPart parts[1];
static EvtWord init_event[61];
static EvtWord phase_event[105];
extern EvtWord actend_event[];
static EvtWord damage_event[75];
static EvtWord wait_event[6];

/**
 * Unit kind of Prof. Frankly:
 * 10 HP, level 1, with its size, sounds and the links to its parts, status vulnerability and scripts.
 */
BattleUnitKind unit_lecture_frankli_sac = {
    179,
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
    "SFX_ENM_KURI_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x2000000,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/** Defence of Prof. Frankly's body per damage type: 0 against every damage type. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Defence attributes of Prof. Frankly's body: none, so every damage type is dealt normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/** Status vulnerability of Prof. Frankly: immune to every status. */
static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/**
 * Pose table of Prof. Frankly:
 * the animation played for each pose type (idle, hurt, walk, run, attack and so on).
 */
static PoseTableEntry pose_table[] = {
    {27, "D_1"},
    {28, "S_1"},
    {31, "D_2"},
    {39, "D_2"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

/** Event table of Prof. Frankly: empty, so it has no special reactions. */
static BattleDataEntry data_table[] = {
    {0, NULL},
};

/** Body part of Prof. Frankly: a single part using the model "c_kuri_h". */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_frankli", "c_kuri_h", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x880009, 0, pose_table},
};

/**
 * Test event: Frankly's lecture intro (mac_0_b_t3_000) and sets the act-end event of Mario to none.
 * Not used by the rest of the file.
 */
EVT_BEGIN(_test_event)
    CALL(btlevtcmd_SetTalkPose, BTL_UNIT_LECTURE, STRING("T_1"))
    CALL(btlevtcmd_SetStayPose, BTL_UNIT_LECTURE, STRING("S_1"))
    CALL(evt_msg_print, 2, STRING("mac_0_b_t3_000"), 0, BTL_UNIT_SELF)
    CALL(_set_actend_event, BTL_UNIT_MARIO, 0)
    RETURN
EVT_END()

/** Script helper that sets the act-end event script (args[1]) of the battle unit args[0]. */
static USER_FUNC(_set_actend_event) {
    EvtWord* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id = evtGetValue(event, args[0]);
    EvtWord* evt = (EvtWord*)evtGetValue(event, args[1]);
    BattleUnit* unit;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    unit->actEndEvent = evt;
    return EVT_RETURN_DONE;
}

/** Script helper that sets the battle's lecture unit id to args[0], the unit that the tutorial messages come from. */
static USER_FUNC(_battle_set_lecture_unit_id) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 value;

    value = evtGetValue(event, *args++);
    wp->lectureUnitId = value;
    return EVT_RETURN_DONE;
}

/**
 * Script helper run by Professor Frankly's init_event to set up the Star Power lecture's audience:
 * sets BREAK_SLOT_FLAG_LECTURE
 * (the bingo reels always show card 3), freezes the audience,
 * removes everyone and seats ten Toads in seats
 * 5 to 14 and a Hammer Bro in seat 48 that never runs away (the one who later threatens to throw his hammer).
 */
static USER_FUNC(lecture_init) {
    BreakSlotWork* slot = BattleBreakSlotGetPtr();
    BattleAudience* aud = BattleAudienceBaseGetPtr();
    s32 seats[11] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 48};
    s32 seat;
    s32 i;

    slot->flags |= BREAK_SLOT_FLAG_LECTURE;
    aud->flags |= AUDIENCE_FLAG_FROZEN;
    for (i = 0; i < 200; i++) {
        BattleAudience_Delete(i);
    }
    for (i = 0; i < 11; i++) {
        if ((seat = seats[i]) != 48) {
            BattleAudience_Entry(seat, 0, 0);
        } else {
            BattleAudience_Entry(seat, 3, 0);
            BattleAudienceGetPtr(seats[i])->flags |= MEMBER_FLAG_NO_ESCAPE;
        }
    }
    return EVT_RETURN_DONE;
}

/** Script helper that stores the kind of action Mario chose in the command menu (actType) in args[0]. */
static USER_FUNC(get_actkind) {
    evtSetValue(event, event->args[0], _battleWorkPointer->commandMenu.actType);
    return EVT_RETURN_DONE;
}

/** Script helper that stores the success of the last action command in args[0]. */
static USER_FUNC(get_ac_result) {
    evtSetValue(event, event->args[0], _battleWorkPointer->lastAcSuccess);
    return EVT_RETURN_DONE;
}

/** Script helper that makes the audience cheer as in the Star Power lecture. */
static USER_FUNC(aud_joy) {
    BattleAudienceJoySACLecture();
    return EVT_RETURN_DONE;
}

/** Script helper that adds 5 audience members. */
static USER_FUNC(aud_inc) {
    BattleAudienceAddAudienceNum(5);
    return EVT_RETURN_DONE;
}

/** Script helper that removes 5 audience members. */
static USER_FUNC(aud_dec) {
    BattleAudienceAddAudienceNum(-5);
    return EVT_RETURN_DONE;
}

/**
 * Script helper that lets audience seat 48 throw a hammer (item 0xEF) onto the stage;
 * blocks until it has been thrown, then freezes the audience again.
 */
static USER_FUNC(hammer_on) {
    BattleAudience* aud = BattleAudienceBaseGetPtr();
    BattleAudienceMember* member = BattleAudienceGetPtr(48);

    aud->flags &= ~AUDIENCE_FLAG_FROZEN;
    if (BattleAudienceItemOn(48, 0xEF, 1) == TRUE) {
        member->flags &= ~MEMBER_FLAG_NO_ESCAPE;
        aud->flags |= AUDIENCE_FLAG_FROZEN;
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

/**
 * Script helper that starts the audience attack part of the lecture:
 * sets the lecture flag and remembers the message window id.
 */
static USER_FUNC(aud_attack_init) {
    BattleWork* wp = _battleWorkPointer;

    wp->lectureFlags |= LECTURE_FLAG_CONTINUE_WINDOW;
    wp->lectureWindowId = event->printWindowId;
    return EVT_RETURN_DONE;
}

/** Script helper that ends the audience attack part: sets the lecture flag. */
static USER_FUNC(aud_attack_end) {
    _battleWorkPointer->lectureFlags |= LECTURE_FLAG_CONTINUE_WINDOW;
    return EVT_RETURN_DONE;
}

/** Script helper that makes the AP (Star Power) gauge in the status window blink for 160 frames. */
static USER_FUNC(blinkAP) {
    statusAPBlink(160);
    return EVT_RETURN_DONE;
}

/**
 * Script helper that dims the screen except for a rectangle:
 * args[0..3] are the left, top, right and bottom of the lit area,
 * args[4] the fade time and args[5] the hold time (frames). Used to point at the gauge.
 */
static USER_FUNC(spot_square) {
    EvtWord* args = event->args;
    s32 time;
    s32 wait;

    point[0] = evtGetFloat(event, args[0]);
    point[1] = evtGetFloat(event, args[1]);
    point[2] = evtGetFloat(event, args[2]);
    point[3] = evtGetFloat(event, args[3]);
    time = evtGetValue(event, args[4]);
    wait = evtGetValue(event, args[5]);
    if (isFirstCall) {
        dark = 0;
        darkCount = 0;
    }
    darkCount++;
    if (darkCount >= 0 && darkCount <= time) {
        dark = intplGetValue(0, 0.0f, 192.0f, darkCount, time);
    }
    if (darkCount >= time + wait && darkCount <= wait + time * 2) {
        dark = intplGetValue(0, 192.0f, 0.0f, darkCount - (time + wait), time);
    }
    dispEntry(CAMERA_2D, 500.0f, 2, spot_square_disp, NULL);
    return darkCount >= wait + time * 2 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

/** Draws one axis-aligned black quad in 2D from (x0, y0) to (x1, y1). */
static void Quads2D(f32 x0, f32 y0, f32 x1, f32 y1) {
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x0, y0, 0.0f);
    GXPosition3f32(x1, y0, 0.0f);
    GXPosition3f32(x1, y1, 0.0f);
    GXPosition3f32(x0, y1, 0.0f);
}

/** Draw callback of spot_square: fills the screen with translucent black in four quads around the lit rectangle. */
static void spot_square_disp(CameraId cameraId, void* param) {
    CameraEntry* cam;
    Mtx mtx;

    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, (GXColor){0, 0, 0, dark});
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    cam = camGetPtr(CAMERA_2D);
    PSMTXIdentity(mtx);
    PSMTXConcat(cam->view, mtx, mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    Quads2D(-320.0f, 240.0f, 320.0f, point[1]);
    Quads2D(-320.0f, point[1], point[0], point[3]);
    Quads2D(point[2], point[1], 320.0f, point[3]);
    Quads2D(-320.0f, point[3], 320.0f, -240.0f);
}

/**
 * Stops the idle events of Mario and his partner and puts both into their normal standing pose,
 * ready for the next lecture step.
 */
EVT_BEGIN(stop_wait_event)
    CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_MARIO)
#if VERSION <= VERSION_DEMO_JP
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_S_1"))
#else
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_MARIO, 1)
#endif
    CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_PARTNER)
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_PARTNER, LW(0))
#if VERSION <= VERSION_DEMO_JP
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_PARTNER, LW(0), BTL_POSE_STAY)
#else
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_PARTNER, LW(0))
#endif
    RETURN
EVT_END()

/**
 * Init event of Professor Frankly in the special-action-command tutorial:
 * starts lecture mode, registers himself as the lecture unit, hooks actend_event on Mario and the partner,
 * clears work 0 to 2 and forbids movement.
 */
static EVT_BEGIN(init_event)
    CALL(lecture_init)
    CALL(btlevtcmd_onoff_battleflag, 1, 4096)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    CALL(_battle_set_lecture_unit_id, LW(0))
    CALL(_set_actend_event, BTL_UNIT_MARIO, PTR(actend_event))
    CALL(_set_actend_event, BTL_UNIT_PARTNER, PTR(actend_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_SAC_STEP, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_SAC_GOOD_RESULTS, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_SAC_BAD_RESULTS, 0)
    CALL(btlevtcmd_SetMaxMoveCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Phase event that scripts the Star Power lesson: unit work 0 is the lesson step.
 * On turn 1 he introduces the AP gauge (mac_0_b_t3_000, 001) with a spotlight on it (spot_square),
 * then later steps explain the special action command, branching on unit work 1 and 2.
 */
static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_get_turn, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL_CHILD(stop_wait_event)
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("S_1"))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(evt_msg_print, 2, STRING("mac_0_b_t3_000"), 0, BTL_UNIT_SELF)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(evt_btl_camera_set_mode, 0, 0)
            WAIT_FRAMES(60)
            CALL(blinkAP)
            CALL(spot_square, -105, 172, 206, 128, 20, 120)
            WAIT_FRAMES(30)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            WAIT_MS(500)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, 92, 94, 320, 92, 44, 13, 1, 11)
            WAIT_MS(500)
            CALL(evt_msg_print, 2, STRING("mac_0_b_t3_001"), 0, BTL_UNIT_SELF)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(btlevtcmd_onoff_battleflag, 1, 67108864)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_SAC_STEP, 1)
            GOTO(99)
        END_IF
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * Act-end event of Mario and his partner in the Star Power lecture (hooked by init_event): after each action it
 * moves the lecture along by the lecture unit's work 0.
 * After the first special move (act type 4) Frankly shows the
 * emptied gauge and asks to be attacked (mac_0_b_t3_003 to 005);
 * after each attack he praises or scolds the action
 * command result (006 to 010, the audience growing or shrinking) and, once the icons match,
 * explains the bingo and
 * the hammer-throwing audience member (013 to 014_3); at step 3 he ends the lecture (014_4, 015).
 */
EVT_BEGIN(actend_event)
#if VERSION >= VERSION_JP
    CALL_CHILD(stop_wait_event)
#endif
    // After a special move: Frankly points to the emptied Star Power gauge and says it can be filled again.
    CALL(get_actkind, LW(0))
    IF_INT_EQUAL(LW(0), 4)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_SAC_STEP, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            WAIT_MS(1000)
            CALL_CHILD(stop_wait_event)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            WAIT_MS(500)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, 92, 94, 320, 92, 44, 13, 1, 11)
            WAIT_MS(500)
            // Frankly shows the emptied gauge and the audience,
            // and explains how a lively crowd builds Star Power.
            CALL(evt_msg_print, 2, STRING("mac_0_b_t3_003"), 0, BTL_UNIT_LECTURE)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(evt_btl_camera_set_mode, 0, 0)
            WAIT_FRAMES(60)
            CALL(blinkAP)
            CALL(spot_square, -105, 172, 206, 128, 20, 120)
            WAIT_FRAMES(30)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            WAIT_MS(500)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, 92, 94, 320, 92, 44, 13, 1, 11)
            WAIT_MS(500)
            CALL(evt_msg_print, 2, STRING("mac_0_b_t3_004"), 0, BTL_UNIT_LECTURE)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, 0, 40, 590, 0, 15, 60, 30, 11)
            WAIT_FRAMES(30)
            CALL(aud_joy)
            WAIT_FRAMES(60)
            CALL(aud_joy)
            WAIT_FRAMES(30)
            WAIT_MS(500)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, 92, 94, 320, 92, 44, 13, 1, 11)
            WAIT_MS(30)
            CALL(evt_msg_print, 2, STRING("mac_0_b_t3_005"), 0, BTL_UNIT_LECTURE)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(evt_btl_camera_set_mode, 0, 0)
            // Now he asks Mario and Goombella to attack and get the audience excited.
            CALL(btlevtcmd_onoff_battleflag, 0, 67108864)
            CALL(btlevtcmd_onoff_battleflag, 1, 268435456)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_SAC_STEP, 2)
            GOTO(99)
        END_IF
    END_IF
    IF_INT_NOT_EQUAL(LW(0), 9)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_SAC_STEP, LW(0))
        IF_INT_EQUAL(LW(0), 2)
            WAIT_MS(200)
            CALL_CHILD(stop_wait_event)
            // After their attacks: the action command result is judged.
            CALL(get_ac_result, LW(0))
            IF_INT_EQUAL(LW(0), 1)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_SAC_GOOD_RESULTS, LW(0))
                IF_INT_EQUAL(LW(0), 0)
                    WAIT_MS(2000)
                    // Good result: the audience cheers and fills part of the gauge; Frankly praises it.
                    CALL(btlevtcmd_StatusWindowOnOff, 0)
                    CALL(evt_msg_print, 2, STRING("mac_0_b_t3_006"), 0, BTL_UNIT_LECTURE)
                    CALL(btlevtcmd_StatusWindowOnOff, 1)
                    CALL(evt_btl_camera_set_mode, 0, 0)
                    WAIT_FRAMES(60)
                    CALL(blinkAP)
                    CALL(spot_square, -105, 172, 206, 128, 20, 120)
                    WAIT_FRAMES(30)
                    CALL(btlevtcmd_AddUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_SAC_GOOD_RESULTS, 1)
                    GOTO(99)
                END_IF
                IF_INT_EQUAL(LW(0), 1)
                    CALL(aud_inc)
                    WAIT_MS(2000)
                    CALL(btlevtcmd_StatusWindowOnOff, 0)
                    // Frankly adds that livelier battles draw bigger crowds.
                    CALL(evt_msg_print, 2, STRING("mac_0_b_t3_007"), 0, BTL_UNIT_LECTURE)
                    CALL(evt_btl_camera_set_mode, 0, 0)
                    WAIT_FRAMES(60)
                    CALL(spot_square, -295, -145, -175, -215, 20, 120)
                    WAIT_FRAMES(30)
                    CALL(btlevtcmd_StatusWindowOnOff, 1)
                    CALL(btlevtcmd_AddUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_SAC_GOOD_RESULTS, 1)
                    GOTO(99)
                END_IF
                IF_INT_EQUAL(LW(0), 2)
                    // Three matching icons: the crowd goes wild; Frankly explains the bingo
                    // and the Appeal command.
                    CALL(btlevtcmd_StatusWindowOnOff, 0)
                    CALL(evt_msg_print, 2, STRING("mac_0_b_t3_013"), 0, BTL_UNIT_LECTURE)
                    CALL(evt_btl_camera_set_mode, 0, 3)
                    CALL(evt_btl_camera_set_moveto, 0, 92, 94, 320, 92, 44, 13, 30, 11)
                    WAIT_FRAMES(30)
                    CALL(evt_msg_print, 2, STRING("mac_0_b_t3_014"), 0, BTL_UNIT_LECTURE)
                    CALL(evt_btl_camera_set_mode, 0, 0)
                    // A member of the audience pulls out a hammer and Frankly warns Mario about it.
                    WAIT_MS(1600)
                    CALL(hammer_on)
                    WAIT_MS(1000)
                    CALL(evt_msg_print, 2, STRING("mac_0_b_t3_014_1"), 0, BTL_UNIT_LECTURE)
                    CALL(evt_btl_camera_set_mode, 0, 3)
                    CALL(evt_btl_camera_set_moveto, 0, -30, 29, 499, -30, -3, 5, 30, 11)
                    WAIT_FRAMES(120)
#if VERSION >= VERSION_JP
                    CALL(evt_msg_toge, 1, 0, 0, 0)
#endif
                    CALL(evt_msg_print, 2, STRING("mac_0_b_t3_014_2"), 0, BTL_UNIT_LECTURE)
                    CALL(evt_btl_camera_set_mode, 0, 0)
                    CALL(evt_btl_camera_set_moveSpeedLv, 0, 3)
                    WAIT_FRAMES(30)
                    CALL(evt_msg_print, 2, STRING("mac_0_b_t3_014_3"), 0, BTL_UNIT_LECTURE)
                    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_SAC_STEP, 3)
                    // Frankly explains that audience throws can be stopped with a button press.
                    CALL(aud_attack_init)
                    CALL(btlevtcmd_onoff_battleflag, 0, 268435456)
                    CALL(btlevtcmd_onoff_battleflag, 1, 8388608)
                    GOTO(99)
                END_IF
            ELSE
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_SAC_BAD_RESULTS, LW(0))
                IF_INT_EQUAL(LW(0), 0)
                    // Bad result: the audience feels cheated and shrinks; Frankly scolds the miss.
                    CALL(btlevtcmd_StatusWindowOnOff, 0)
                    CALL(evt_msg_print, 2, STRING("mac_0_b_t3_008"), 0, BTL_UNIT_LECTURE)
                    CALL(btlevtcmd_StatusWindowOnOff, 1)
                    CALL(evt_btl_camera_set_mode, 0, 0)
                    CALL(btlevtcmd_AddUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_SAC_BAD_RESULTS, 1)
                    GOTO(99)
                END_IF
                IF_INT_EQUAL(LW(0), 1)
                    CALL(aud_dec)
                    WAIT_MS(750)
                    CALL(btlevtcmd_StatusWindowOnOff, 0)
                    CALL(evt_msg_print, 2, STRING("mac_0_b_t3_009"), 0, BTL_UNIT_LECTURE)
                    CALL(btlevtcmd_StatusWindowOnOff, 1)
                    CALL(evt_btl_camera_set_mode, 0, 0)
                    CALL(btlevtcmd_AddUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_SAC_BAD_RESULTS, 1)
                    GOTO(99)
                END_IF
                IF_INT_EQUAL(LW(0), 2)
                    CALL(btlevtcmd_StatusWindowOnOff, 0)
                    CALL(evt_msg_print, 2, STRING("mac_0_b_t3_010"), 0, BTL_UNIT_LECTURE)
                    CALL(btlevtcmd_StatusWindowOnOff, 1)
                    GOTO(99)
                END_IF
            END_IF
        END_IF
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_SAC_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 3)
        WAIT_MS(200)
        CALL(aud_attack_end)
        CALL_CHILD(stop_wait_event)
        // Frankly sums up the defence against thrown objects and ends the lecture.
        CALL(evt_msg_print, 2, STRING("mac_0_b_t3_014_4"), 0, BTL_UNIT_LECTURE)
        CALL(evt_btl_camera_set_mode, 0, 3)
        CALL(evt_btl_camera_set_moveto, 0, 92, 94, 320, 92, 44, 13, 30, 11)
        WAIT_FRAMES(30)
        CALL(evt_msg_print, 2, STRING("mac_0_b_t3_015"), 0, BTL_UNIT_LECTURE)
        WAIT_MS(1000)
        CALL(btlevtcmd_onoff_battleflag, 1, 32)
        GOTO(99)
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * Damage event of Professor Frankly in the Star Power tutorial:
 * runs the default damage handling, then, once the lesson is at step 2
 * and the action command result (get_ac_result) is 1,
 * he comments mac_0_b_t3_011 and 012 with a spotlight on the area.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_SAC_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 2)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_SAC_GOOD_RESULTS, LW(0))
        IF_INT_EQUAL(LW(0), 2)
            WAIT_MS(1000)
            CALL(get_ac_result, LW(0))
            IF_INT_EQUAL(LW(0), 1)
                CALL(btlevtcmd_StatusWindowOnOff, 0)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t3_011"), 0, BTL_UNIT_SELF)
                CALL(btlevtcmd_StatusWindowOnOff, 1)
                WAIT_FRAMES(60)
                CALL(spot_square, 198, 169, 294, 117, 20, 120)
                WAIT_FRAMES(30)
                CALL(btlevtcmd_StatusWindowOnOff, 0)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t3_012"), 0, BTL_UNIT_SELF)
                CALL(btlevtcmd_StatusWindowOnOff, 1)
                WAIT_MS(500)
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

/** Wait (idle) event of Professor Frankly in the Star Power tutorial: shows the idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
