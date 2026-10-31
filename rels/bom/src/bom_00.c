// bom_00 (ボム村, Fahr Outpost): the snowfield with the pipe from Rogueport Sewers (tik_07); path to bom_03.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_sub.h"
#include "evt/evt_cam.h"
#include "evt/evt_eff.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_msg.h"
#include "evt/evt_party.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "party/party_motion.h"
#include "bom.h"
#include "data_tables.h"
#include "evt/evt_story.h"

static TreeAccess tree_tbl[4];
static BeroEntry bero_entry_data[3];

EVT_BEGIN(evt_bom_snowfall)
    CALL(evt_eff64, 0, STRING("snowfall_n64"), 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

static TreeAccess tree_tbl[] = {
    {3, "A_ki1", "S_ki_1", "S_ha_1", 0, NULL},
    {3, "A_ki2", "S_ki_2", "S_ha_2", 0, NULL},
    {3, "A_ki3", "S_ki_3", "S_ha_3", 0, NULL},
    {7, NULL, NULL, NULL, 0, NULL},
};

static EVT_BEGIN(evt_tree)
    SET_VALUE(LW(0), PTR(tree_tbl))
    CALL_CHILD(PTR(evt_sub_tree_access_entry))
    RETURN
EVT_END()

static EVT_BEGIN(first_evt_dokan)
    IF_INT_EQUAL(GSWF(GSWF_BOM_FAHR_REACHED), 1)
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_mario_dispflag_onoff, 1, 1)
    CALL(evt_party_dispflg_onoff, 0, PARTY_DISP_FLAG_HIDDEN, 1)
    SET_VALUE(GF(0), 1)
    WAIT_WHILE(GF(0))
    CALL(evt_mario_dispflag_onoff, 0, 1)
    CALL(evt_party_dispflg_onoff, 0, PARTY_DISP_FLAG_HIDDEN, 0)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static BeroEntry bero_entry_data[] = {
    {
        "dokan", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        (s32*)first_evt_dokan, // enterEvent
        6, // caseType
        NULL, // exitEvent
        "tik_07", // nextMapName
        "dokan__1", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "e_bero", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "bom_03", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

static EVT_BEGIN(first_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_cam_letter_box_onoff, 1, 0)
    CALL(evt_cam3d_evt_set, -176, 567, 533, -176, 471, -9, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_cam3d_evt_set, -176, 183, 533, -176, 87, -9, 6000, 11)
    WAIT_MS(6000)
    SET_VALUE(GF(0), 0)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_mario_mov_pos2, -155, 31, FLOAT(60.0f))
    CALL(evt_mario_set_dir, 270, 300, 0)
    CALL(evt_party_move_pos2, 0, -188, 31, FLOAT(60.0f))
    CALL(evt_party_set_dir, 0, 90, 300)
    CALL(evt_cam3d_evt_set, -175, 90, 295, -175, 35, 0, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_party_stop, 0)
    WAIT_MS(200)
    CALL(evt_msg_print_party, STRING("stg7_bom_01"))
    CALL(evt_cam3d_evt_off, 500, 11)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG7_00_START)
    SET_VALUE(GSWF(GSWF_BOM_FAHR_REACHED), 1)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    CALL(evt_snd_bgm_scope, 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(first_evt2)
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_cam3d_evt_set, -176, 567, 533, -176, 471, -9, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_cam3d_evt_set, -176, 183, 533, -176, 87, -9, 6000, 11)
    WAIT_MS(6000)
    SET_VALUE(GF(0), 0)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_mario_mov_pos2, -155, 31, FLOAT(60.0f))
    CALL(evt_mario_set_dir, 270, 300, 0)
    CALL(evt_party_move_pos2, 0, -188, 31, FLOAT(60.0f))
    CALL(evt_party_set_dir, 0, 90, 300)
    CALL(evt_cam3d_evt_set, -175, 90, 295, -175, 35, 0, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_party_stop, 0)
    WAIT_MS(200)
    CALL(evt_msg_print_party, STRING("stg7_bom_01_00"))
    CALL(evt_cam3d_evt_off, 500, 11)
    SET_VALUE(GSWF(GSWF_BOM_FAHR_REACHED), 1)
    CALL(evt_snd_bgm_scope, 0, 0)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

EVT_BEGIN(bom_00_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG7_BOM1"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG7_BOM1"))
    CALL_CHILD(PTR(evt_bom_snowfall))
    CALL_CHILD(PTR(evt_tree))
    CALL(evt_mobj_brick, STRING("mobj_badge_gat2"), 215, 65, -75, ITEM_DOUBLE_DIP_P, 12, 0, GSWF(GSWF_BOM00_DOUBLE_DIP_P_BLOCK_HIT))
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), -300, 5, 0, STRING("S_gra02_dai"), 125, GSWF(GSWF_BOM00_STAR_PIECE_PANEL))
    IF_INT_EQUAL(GSWF(GSWF_BOM_FAHR_REACHED), 0)
        SWITCH(GSW(GSW_STORY_PROGRESS))
            CASE_LESS(STORY_STG6_71_01)
            SPAWN_EVENT(PTR(first_evt2))
            CASE_DEFAULT
            SPAWN_EVENT(PTR(first_evt))
        END_SWITCH
    ELSE
        IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_71_01)
            IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG7_00_START)
                SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG7_00_START)
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()
