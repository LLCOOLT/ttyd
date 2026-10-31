// mri_09 (巨木の中, The Great Tree): the room with the four rolling wall panels (wall_roll), the slot
// switches, the breaking floor, and the blue jail key (get_blue_jail_key).
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_sub.h"
#include "evt/evt_cam.h"
#include "evt/evt_eff.h"
#include "evt/evt_fade.h"
#include "evt/evt_hit.h"
#include "evt/evt_img.h"
#include "evt/evt_item.h"
#include "driver/itemdrv.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "evt/evt_offscreen.h"
#include "evt/evt_paper.h"
#include "evt/evt_party.h"
#include "evt/evt_snd.h"
#include "party/party_motion.h"
#include "mri_puni.h"
#include "mri.h"
#include "data_tables.h"
#include "version.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"
#include "driver/camdrv.h"

BeroEntry bero_bluejail[1];
static BeroEntry bero_entry_data[5];
extern EvtWord wall_roll_sub[];
extern EvtWord wall_roll[];
static KusaAccess ueki_access_data[6];
extern EvtWord slot00_event[];
extern EvtWord slot01_event[];
extern EvtWord slot02_event[];
extern EvtWord slot03_event[];
extern EvtWord slot_event[];
extern EvtWord get_blue_jail_key[];

BeroEntry bero_bluejail[] = {
    {
        "w_bero", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "mri_03", // nextMapName
        "", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
};

static BeroEntry bero_entry_data[] = {
    {
        "w_bero", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "mri_08", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "n_bero", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "mri_10", // nextMapName
        "s_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan2", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan3", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan3", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_W, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        10, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan2", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

EVT_BEGIN(wall_roll_sub)
#if VERSION == VERSION_DEMO
    CALL(evt_paper_entry, LW(0))
#endif
    CALL(evt_img_entry, LW(2))
    CALL(evt_img_set_paper, LW(2), LW(0))
    CALL(evt_offscreen_entry, LW(3))
    CALL(evt_mapobj_set_offscreen, 1, LW(1), LW(3))
    CALL(evt_offscreen_get_boundingbox, LW(3), LW(10), LW(11), LW(12), LW(13))
    CALL(evt_img_alloc_capture, LW(2), 0, 0, 1, LW(10), LW(11), LW(12), LW(13))
    CALL(evt_img_clear_virtual_point, LW(2))
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_mapobj_get_position, LW(1), LW(10), LW(11), LW(12))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF2_SLOT_GOOUT1"), LW(10), LW(11), LW(12), LW(15))
        WAIT_MS(1800)
        CALL(evt_snd_sfxoff, LW(15))
    END_INLINE_EVENT
    CALL(evt_img_set_paper_anim, LW(2), STRING("A_1"))
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_HIDE)
    CALL(evt_img_wait_animend, LW(2))
    CALL(evt_img_free_capture, LW(2), 0)
    CALL(evt_img_free_capture, LW(2), 1)
    CALL(evt_img_onoff, LW(2), 0)
    CALL(evt_img_release, LW(2))
    CALL(evt_mapobj_clear_offscreen, 1, LW(1))
    CALL(evt_offscreen_delete, LW(3))
    RETURN
EVT_END()

EVT_BEGIN(wall_roll)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
#if VERSION >= VERSION_US
    CALL(N_evt_party_cloud_lock_animations_on_off, 0, 1)
#endif
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_sfxon, STRING("SFX_STG2_QUAKE2"), LW(10))
        CALL(evt_cam_shake, CAMERA_3D, FLOAT(0.01953125f), FLOAT(0.0f), 1000)
        CALL(evt_cam_shake, CAMERA_3D, FLOAT(0.009765625f), FLOAT(0.0f), 500)
        CALL(evt_snd_sfxoff, LW(10))
    END_INLINE_EVENT
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 159, 399, 0, 86, -18, 500, 11)
    WAIT_MS(1000)
    SET_VALUE(LW(0), STRING("OFF_d_roll_down"))
    SET_VALUE(LW(1), STRING("S_isk_01A01"))
    SET_VALUE(LW(2), STRING("img00"))
    SET_VALUE(LW(3), STRING("ofs00"))
    SPAWN_EVENT(PTR(wall_roll_sub))
    WAIT_MS(2000)
    SET_VALUE(LW(0), STRING("OFF_d_roll_left"))
    SET_VALUE(LW(1), STRING("S_isk_01A02"))
    SET_VALUE(LW(2), STRING("img01"))
    SET_VALUE(LW(3), STRING("ofs01"))
    SPAWN_EVENT(PTR(wall_roll_sub))
    WAIT_MS(2000)
    SET_VALUE(LW(0), STRING("OFF_d_roll_up"))
    SET_VALUE(LW(1), STRING("S_isk_01A03"))
    SET_VALUE(LW(2), STRING("img02"))
    SET_VALUE(LW(3), STRING("ofs02"))
    SPAWN_EVENT(PTR(wall_roll_sub))
    WAIT_MS(2000)
    BEGIN_INLINE_EVENT
        WAIT_MS(2000)
        CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
        CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_ENV_SUCCESS1"))
        WAIT_MS(2000)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    END_INLINE_EVENT
    SET_VALUE(LW(0), STRING("OFF_d_roll_right"))
    SET_VALUE(LW(1), STRING("S_isk_01A04"))
    SET_VALUE(LW(2), STRING("img03"))
    SET_VALUE(LW(3), STRING("ofs03"))
    CALL_CHILD(PTR(wall_roll_sub))
    CALL(evt_hitobj_onoff, STRING("A_isk_01A"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("A_f2_rak03"), 1, 1)
    CALL(evt_hitobj_onoff, STRING("A_f2_rak04"), 1, 0)
    SET_VALUE(GSWF(GSWF_MRI09_WALL_PANELS_ROLLED), 1)
#if VERSION != VERSION_DEMO
    WAIT_FRAMES(1)
#endif
    CALL(evt_puni_all_fall_check)
    CALL(evt_puni_set_maze)
    CALL(evt_cam3d_evt_off, 300, 11)
    WAIT_MS(500)
    CALL(evt_mobj_get_position, STRING("slot00"), LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("small_star"), 3, LW(0), LW(1), LW(2), 0, -20, 0, 3, 0, 0, 0, 0)
    CALL(evt_mobj_get_position, STRING("slot01"), LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("small_star"), 3, LW(0), LW(1), LW(2), 0, -20, 0, 3, 0, 0, 0, 0)
    CALL(evt_mobj_get_position, STRING("slot02"), LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("small_star"), 3, LW(0), LW(1), LW(2), 0, -20, 0, 3, 0, 0, 0, 0)
    CALL(evt_mobj_get_position, STRING("slot03"), LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("small_star"), 3, LW(0), LW(1), LW(2), 0, -20, 0, 3, 0, 0, 0, 0)
    CALL(evt_mobj_delete, STRING("slot00"))
    CALL(evt_mobj_delete, STRING("slot01"))
    CALL(evt_mobj_delete, STRING("slot02"))
    CALL(evt_mobj_delete, STRING("slot03"))
    WAIT_MS(500)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG2_21_02_MATCHING_THE_PATTERNS)
#if VERSION >= VERSION_US
    CALL(N_evt_party_cloud_lock_animations_on_off, 0, 0)
#endif
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(breakyuka_init)
#if VERSION == VERSION_DEMO
    // BUG: the demo tests the floor flag the other way round and has no ELSE (fixed in the later builds)
    IF_INT_EQUAL(GSWF(GSWF_MRI09_FLOOR_BROKEN), 1)
#else
    IF_INT_EQUAL(GSWF(GSWF_MRI09_FLOOR_BROKEN), 0)
#endif
        CALL(evt_hitobj_onoff, STRING("A_f2_rak_02"), 1, 0)
#if VERSION != VERSION_DEMO
    ELSE
        CALL(evt_hitobj_onoff, STRING("A_f2_rak_02"), 1, 1)
#endif
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(breakyuka_main)
    CALL(evt_hitobj_onoff, STRING("A_f2_rak_02"), 1, 1)
    CALL(evt_puni_all_fall_check)
    RETURN
EVT_END()

static KusaAccess ueki_access_data[] = {
    {1, "A_ueki_01", "S_ueki_01", NULL},
    {1, "A_ueki_02", "S_ueki_02", NULL},
    {1, "A_ueki_03", "S_ueki_03", NULL},
    {1, "A_ueki_04", "S_ueki_04", NULL},
    {1, "A_ueki_05", "S_ueki_05", NULL},
    {4, NULL, NULL, NULL},
};

EVT_BEGIN(slot00_event)
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG2_21_02_MATCHING_THE_PATTERNS)
        RETURN
    END_IF
    CALL(evt_mobj_hitevt_onoff, STRING("me"), 0)
    SET_VALUE(LW(10), GW(0))
    SET_VALUE(LW(11), GW(0))
    ADD(LW(11), 90)
    CALL(evt_sub_intpl_msec_init, 0, LW(10), LW(11), 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        SET_VALUE(GW(0), LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    IF_INT_GREATER_OR_EQUAL(GW(0), 360)
        SUBTRACT(GW(0), 360)
    END_IF
    CALL(evt_mobj_hitevt_onoff, STRING("me"), 1)
    RETURN
EVT_END()

EVT_BEGIN(slot01_event)
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG2_21_02_MATCHING_THE_PATTERNS)
        RETURN
    END_IF
    CALL(evt_mobj_hitevt_onoff, STRING("me"), 0)
    SET_VALUE(LW(10), GW(1))
    SET_VALUE(LW(11), GW(1))
    ADD(LW(11), 90)
    CALL(evt_sub_intpl_msec_init, 0, LW(10), LW(11), 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        SET_VALUE(GW(1), LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    IF_INT_GREATER_OR_EQUAL(GW(1), 360)
        SUBTRACT(GW(1), 360)
    END_IF
    CALL(evt_mobj_hitevt_onoff, STRING("me"), 1)
    RETURN
EVT_END()

EVT_BEGIN(slot02_event)
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG2_21_02_MATCHING_THE_PATTERNS)
        RETURN
    END_IF
    CALL(evt_mobj_hitevt_onoff, STRING("me"), 0)
    SET_VALUE(LW(10), GW(2))
    SET_VALUE(LW(11), GW(2))
    ADD(LW(11), 90)
    CALL(evt_sub_intpl_msec_init, 0, LW(10), LW(11), 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        SET_VALUE(GW(2), LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    IF_INT_GREATER_OR_EQUAL(GW(2), 360)
        SUBTRACT(GW(2), 360)
    END_IF
    CALL(evt_mobj_hitevt_onoff, STRING("me"), 1)
    RETURN
EVT_END()

EVT_BEGIN(slot03_event)
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG2_21_02_MATCHING_THE_PATTERNS)
        RETURN
    END_IF
    CALL(evt_mobj_hitevt_onoff, STRING("me"), 0)
    SET_VALUE(LW(10), GW(3))
    SET_VALUE(LW(11), GW(3))
    ADD(LW(11), 90)
    CALL(evt_sub_intpl_msec_init, 0, LW(10), LW(11), 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        SET_VALUE(GW(3), LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    IF_INT_GREATER_OR_EQUAL(GW(3), 360)
        SUBTRACT(GW(3), 360)
    END_IF
    CALL(evt_mobj_hitevt_onoff, STRING("me"), 1)
    RETURN
EVT_END()

EVT_BEGIN(slot_event)
    SET_VALUE(GW(0), 0)
#if VERSION >= VERSION_US
    SET_VALUE(GW(1), 90)
    SET_VALUE(GW(2), 180)
    SET_VALUE(GW(3), 270)
#else
    SET_VALUE(GW(1), 0)
    SET_VALUE(GW(2), 0)
    SET_VALUE(GW(3), 0)
#endif
    LOOP(0)
        CALL(evt_mapobj_rotate, 1, STRING("S_isk_01A01a"), GW(0), 0, 0)
        CALL(evt_mapobj_rotate, 1, STRING("S_isk_01A02a"), GW(1), 0, 0)
        CALL(evt_mapobj_rotate, 1, STRING("S_isk_01A03a"), GW(2), 0, 0)
        CALL(evt_mapobj_rotate, 1, STRING("S_isk_01A04a"), GW(3), 0, 0)
        IF_INT_EQUAL(GW(0), 270)
            IF_INT_EQUAL(GW(1), 180)
                IF_INT_EQUAL(GW(2), 0)
                    IF_INT_EQUAL(GW(3), 90)
                        BREAK_LOOP
                    END_IF
                END_IF
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SPAWN_EVENT(PTR(wall_roll))
    RETURN
EVT_END()

EVT_BEGIN(get_blue_jail_key)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
#if VERSION == VERSION_DEMO
    CALL(evt_item_entry, STRING("item00"), ITEM_BLUE_KEY, LW(0), LW(1), LW(2), 15, -1, 0)
#else
    CALL(evt_item_entry, STRING("item00"), ITEM_BLUE_KEY, LW(0), LW(1), LW(2), 16, -1, 0)
#endif
    CALL(evt_item_flag_on, STRING("item00"), ITEM_FLAG_NO_TOUCH)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box00"))
    CALL(evt_item_get_item, STRING("item00"))
    CALL_CHILD(PTR(mri_guide_goryu))
    CALL(evt_puni_flag_onoff, 1, 0, 262144)
    CALL(evt_puni_set_mode, 1, PUNI_MODE_INERT)
    CALL(evt_npc_flag_onoff, 1, STRING("ガイドsp"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_npc_get_position, STRING("ガイドsp"), LW(10), LW(11), LW(12))
        IF_INT_GREATER_OR_EQUAL(LW(10), LW(0))
            CALL(evt_mario_set_dir, 90, 200, 0)
        ELSE
            CALL(evt_mario_set_dir, 270, 200, 0)
        END_IF
    END_INLINE_EVENT
    CALL(evt_npc_get_position, STRING("ガイドsp"), LW(0), LW(1), LW(2))
    CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
    IF_INT_GREATER_OR_EQUAL(LW(10), LW(0))
        CALL(evt_npc_set_ry, STRING("ガイドsp"), 90)
    ELSE
        CALL(evt_npc_set_ry, STRING("ガイドsp"), 270)
    END_IF
    CALL(evt_msg_print, 0, STRING("stg2_mri_e18_00"), 0, STRING("ガイドsp"))
    CALL(evt_puni_flag_onoff, 1, 1, 262144)
    CALL(evt_puni_set_mode, 1, PUNI_MODE_JOIN)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG2_18_JABBLE)
    CALL(evt_fade_set_mapchange_type, 0, FADE_OUT_IRIS, 500, FADE_IN_IRIS, 500)
    SET_VALUE(LW(0), STRING("w_bero"))
    CALL_CHILD(PTR(bero_case_switch_off))
    CALL(evt_bero_overwrite, STRING("w_bero"), PTR(bero_bluejail))
    SET_VALUE(LW(0), STRING("w_bero"))
    CALL_CHILD(PTR(bero_case_switch_on))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(mri_09_init_evt)
    CALL(evt_puni_mem_init)
    CALL(evt_puni_set_yuka, 9, 100, 0, -310, -1000, 2, 2)
    CALL(evt_puni_set_hamari, -250, 100, 78, 102, -2, -230, -311)
    SET_VALUE(LW(6), 0)
    SET_VALUE(LW(7), 0)
    SET_VALUE(LW(8), 0)
    SET_VALUE(LW(9), 0)
    CALL_CHILD(PTR(mri_puni_init))
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    SPAWN_EVENT(PTR(puni_disp_info))
    SPAWN_EVENT(PTR(puni_piders_check))
    SET_VALUE(LW(0), PTR(ueki_access_data))
    CALL_CHILD(PTR(evt_sub_kusa_access_entry))
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG2_23_TIME_BOMB_ACTIVATED, STORY_STG2_23_01_X_NAUT_BATTLE)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_DANGER4"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG2_MRI9"))
        CASE_DEFAULT
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG2_MRI1"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG2_MRI1"))
    END_SWITCH
    CALL(evt_npc_change_fbat_mode, 1)
    CALL(evt_map_playanim, STRING("mizu_01"), 1, 0)
    CALL(evt_map_playanim, STRING("mizu_02"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_01"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_02"), 1, 0)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG2_21_01_MYSTERY_PILLAR)
        CALL(evt_hitobj_onoff, STRING("A_f2_rak03"), 1, 0)
#if VERSION >= VERSION_US
        SPAWN_EVENT(slot_event)
#endif
        CASE_EQUAL(STORY_STG2_21_01_MYSTERY_PILLAR)
        CALL(evt_hitobj_onoff, STRING("A_f2_rak03"), 1, 0)
        SPAWN_EVENT(PTR(slot_event))
        CALL(evt_mobj_switch_red, 1, STRING("slot00"), -80, 0, 135, PTR(slot00_event), 0)
        CALL(evt_mobj_switch_red, 1, STRING("slot01"), -30, 0, 135, PTR(slot01_event), 0)
        CALL(evt_mobj_switch_red, 1, STRING("slot02"), 30, 0, 135, PTR(slot02_event), 0)
        CALL(evt_mobj_switch_red, 1, STRING("slot03"), 80, 0, 135, PTR(slot03_event), 0)
#if VERSION != VERSION_DEMO
        CALL(evt_paper_entry, STRING("OFF_d_roll_down"))
        CALL(evt_paper_entry, STRING("OFF_d_roll_up"))
        CALL(evt_paper_entry, STRING("OFF_d_roll_left"))
        CALL(evt_paper_entry, STRING("OFF_d_roll_right"))
#endif
        CASE_GREATER_OR_EQUAL(STORY_STG2_21_02_MATCHING_THE_PATTERNS)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_isk_01A"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_isk_01A"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_f2_rak03"), 1, 1)
        CALL(evt_hitobj_onoff, STRING("A_f2_rak04"), 1, 0)
    END_SWITCH
    CALL(evt_mobj_itembox, STRING("mobj_box00"), 125, 0, 25, 0, 0, PTR(get_blue_jail_key), GSWF(GSWF_MRI09_BLUE_KEY_CHEST_OPENED))
#if VERSION == VERSION_DEMO
    CALL(evt_item_entry, STRING("item100"), ITEM_CHARGE, -250, -234, 75, 15, GSWF(GSWF_MRI09_CHARGE_TAKEN), 0)
#else
    CALL(evt_item_entry, STRING("item100"), ITEM_CHARGE, -250, -234, 75, 16, GSWF(GSWF_MRI09_CHARGE_TAKEN), 0)
#endif
    CALL(evt_mobj_powerupblk, STRING("pblk1"), 0, -174, -125, 0, GSWF(GSWF_MRI09_SHINE_SPRITE), 0)
    SPAWN_EVENT(PTR(breakyuka_init))
    CALL(evt_mobj_breaking_floor, STRING("mobj_bf00"), 0, 0, 75, 1, PTR(breakyuka_main), GSWF(GSWF_MRI09_FLOOR_BROKEN))
    RETURN
EVT_END()
