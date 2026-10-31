// kpa_04 (クッパ編, Bowser's interludes): the end of the second side-scrolling stage; it ends in Rogueport (gor_00).

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "kpa.h"
#include "evt/evt_npc.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_mario.h"
#include "evt/evt_sub.h"
#include "evt/evt_snd.h"
#include "kpa_stage_data.h"
#include "mario/mariost.h"
#include "evt/evt_story.h"

static EvtWord kpa_act_stg2_mobj[80];
static EvtWord kpa_goal[22];
static NpcSetupInfo npcEnt[1];

/** Blocks, pipes and obstacle blocks of the second half of stage 2, ending at the goal pole. */
static EvtWord kpa_act_stg2_mobj[] = {
    KPA_OBJ_DOKAN_0(-225.0f, 0.0f), KPA_OBJ_BRICK_2(-175.0f, -50.0f), KPA_OBJ_BRICK_2(-175.0f, 0.0f),
    KPA_OBJ_BRICK_2(-125.0f, -50.0f), KPA_OBJ_BRICK_2(-125.0f, 0.0f), KPA_OBJ_BRICK_2(-125.0f, 50.0f),
    KPA_OBJ_BRICK_2(-75.0f, 0.0f), KPA_OBJ_BRICK_2(-75.0f, 50.0f), KPA_OBJ_BRICK_2(-75.0f, 100.0f),
    KPA_OBJ_BRICK_2(-25.0f, 0.0f), KPA_OBJ_BRICK_2(-25.0f, 50.0f), KPA_OBJ_BRICK_2(-25.0f, 100.0f),
    KPA_OBJ_BRICK_2(-25.0f, 150.0f), KPA_OBJ_BRICK_2(25.0f, -50.0f), KPA_OBJ_BRICK_2(25.0f, 0.0f),
    KPA_OBJ_BRICK_2(25.0f, 50.0f), KPA_OBJ_BRICK_2(25.0f, 100.0f), KPA_OBJ_BRICK_2(25.0f, 150.0f),
    KPA_OBJ_BRICK_2(25.0f, 200.0f), KPA_OBJ_BRICK_2(75.0f, -50.0f), KPA_OBJ_BRICK_2(75.0f, 0.0f),
    KPA_OBJ_BRICK_2(75.0f, 50.0f), KPA_OBJ_BRICK_2(75.0f, 100.0f), KPA_OBJ_BRICK_2(75.0f, 150.0f),
    KPA_OBJ_BRICK_2(75.0f, 200.0f), KPA_OBJ_POLE(262.5f, 0.0f, kpa_goal), KPA_OBJ_END,
};

/**
 * Watches Bowser in the stage: each frame it checks whether he is dead (evt_koopa_chk_dead)
 * or has fallen below y = -20, then runs the death handler (kpa_dead) if he died,
 * or the pit fall handler (kpa_fall_sub) if he fell.
 */
static EVT_BEGIN(kpa_fall)
    SET_VALUE(LF(0), 0)
    LOOP(0)
        CALL(evt_koopa_chk_dead, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SET_VALUE(LF(0), 1)
            BREAK_LOOP
        END_IF
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_LESS(LW(1), -20)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    IF_INT_EQUAL(LF(0), 0)
        CALL_CHILD(kpa_fall_sub)
    ELSE
        CALL_CHILD(kpa_dead)
    END_IF
    RETURN
EVT_END()

/**
 * Goal of the second Bowser stage: locks the controls,
 * sets the story progress to STORY_STG4_15_07_BOWSER_ACTION_STAGE and changes the map to Rogueport (gor_00)
 * after a 300 ms pause that also removes the letterbox.
 */
static EVT_BEGIN(kpa_goal)
    CALL(evt_mario_key_onoff, 0)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG4_15_07_BOWSER_ACTION_STAGE)
    BEGIN_INLINE_EVENT
        WAIT_MS(300)
        CALL(evt_cam_letter_box_disable, 0)
    END_INLINE_EVENT
    CALL(evt_bero_mapchange, STRING("gor_00"), STRING(""))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/** No NPCs: the side-scrolling stage is built from the block, pipe and item lists instead. */
static NpcSetupInfo npcEnt[] = {
    {0},
};

/**
 * Map init for kpa_04, the second half of stage 2:
 * Bowser arrives at the top left, the blocks come from kpa_act_stg2_mobj,
 * and the clock and music controller run. Reads Bowser's power level from GSW_KPA_BOWSER_POWER.
 * The goal leads to Rogueport (gor_00).
 */
EVT_BEGIN(kpa_04_init_evt)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL_CHILD(kpa_init)
    CALL(evt_mario_set_pos, -400, 500, -5)
    CALL(evt_mario_set_dir, 90, 0, 0)
    SET_VALUE(LW(0), PTR(kpa_act_stg2_mobj))
    CALL_CHILD(kpa_read_mobj)
    SPAWN_EVENT(kpa_fall)
    CALL(kpa_status_init, 2, GSW(GSW_KPA_LIVES), GSW(GSW_KPA_TIME_LEFT))
    DEBUG_PUT_REG(GSW(GSW_KPA_TIME_LEFT))
    SET_VALUE(LSW(1), 0)
    SET_VALUE(LSWF(2), 1)
    SPAWN_EVENT(kpa_bgm_change)
    CALL(evt_snd_envoff, PSND_FADE_OUT)
    SPAWN_EVENT(kpa_time)
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), GLOBAL_FLAG_SKIP_MAP_EVENTS)
        RETURN
    END_IF
    CALL(evt_koopa_set_level, GSW(GSW_KPA_BOWSER_POWER))
    RETURN
EVT_END()
