// aji_18 (敵のアジト, X-Naut Fortress): the door with three key locks (key_lock_koujyou) and the machine.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "driver/fadedrv.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_fade.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_party.h"
#include "evt/evt_pouch.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "evt/evt_window.h"
#include "party/party_motion.h"
#include "aji.h"
#include "version.h"
#include "evt/evt_story.h"
#include "evt/evt_sub.h"
#include "driver/mapdrv.h"
#include "driver/casedrv.h"

s32 key_list[4];

static USER_FUNC(make_list);
static USER_FUNC(sysflag);

static BeroEntry bero_entry_data[3];
extern EvtWord evt_machine[];
extern EvtWord key_lock_koujyou[];

static USER_FUNC(make_list) {
    s32 n = 0;

    if ((s32)pouchCheckItem(0x1D) > 0) {
        key_list[n++] = 0x1D;
    }
    if ((s32)pouchCheckItem(0x1E) > 0) {
        key_list[n++] = 0x1E;
    }
    if ((s32)pouchCheckItem(0x1F) > 0) {
        key_list[n++] = 0x1F;
    }
    key_list[n] = -1;
    return EVT_RETURN_DONE;
}

static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static BeroEntry bero_entry_data[] = {
    {
        "w_bero", // hitName
        1, // type
        10, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "aji_01", // nextMapName
        "e_bero_4", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        w_door_close, // enterAnimeArg
        w_door_open, // exitAnimeArg
    },
    {
        "e_bero", // hitName
        1, // type
        10, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "aji_13", // nextMapName
        "w_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        e_door_close, // enterAnimeArg
        e_door_open, // exitAnimeArg
    },
    {0},
};

EVT_BEGIN(evt_machine)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg7_aji_67"), 0, 0)
    SET_VALUE(LW(10), 0)
    CALL(evt_pouch_check_item, ITEM_CARD_KEY_0x1D, LW(11))
    ADD(LW(10), LW(11))
    CALL(evt_pouch_check_item, ITEM_CARD_KEY_0x1E, LW(11))
    ADD(LW(10), LW(11))
    CALL(evt_pouch_check_item, ITEM_CARD_KEY_0x1F, LW(11))
    ADD(LW(10), LW(11))
    IF_INT_EQUAL(LW(10), 0)
        CALL(evt_mario_key_onoff, 1)
        RETURN
    END_IF
    CALL(make_list)
    CALL(evt_win_item_select, 0, PTR(key_list), LW(10), 0)
    SWITCH(LW(10))
        CASE_EQUAL(29)
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_kagi1_aka"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_kagi1_mid"), MAPOBJ_FLAG_HIDE)
            SET_VALUE(GSWF(GSWF_AJI18_CARD_KEY_SLOT_1), 1)
            CALL(evt_pouch_remove_item, LW(10), LW(1))
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_DOOR_UNLOCK1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_exit_case_evt)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg7_aji_67_01"), 0, 0)
        END_IF
        CASE_EQUAL(30)
        IF_INT_EQUAL(LW(0), 1)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_kagi2_aka"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_kagi2_mid"), MAPOBJ_FLAG_HIDE)
            SET_VALUE(GSWF(GSWF_AJI18_CARD_KEY_SLOT_2), 1)
            CALL(evt_pouch_remove_item, LW(10), LW(1))
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_DOOR_UNLOCK1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_exit_case_evt)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg7_aji_67_01"), 0, 0)
        END_IF
        CASE_EQUAL(31)
        IF_INT_EQUAL(LW(0), 2)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_kagi3_aka"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_kagi3_mid"), MAPOBJ_FLAG_HIDE)
            SET_VALUE(GSWF(GSWF_AJI18_CARD_KEY_SLOT_3), 1)
            CALL(evt_pouch_remove_item, LW(10), LW(1))
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_DOOR_UNLOCK1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_exit_case_evt)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg7_aji_67_01"), 0, 0)
        END_IF
        CASE_DEFAULT
    END_SWITCH
    IF_INT_EQUAL(GSWF(GSWF_AJI18_CARD_KEY_SLOT_1), 1)
        IF_INT_EQUAL(GSWF(GSWF_AJI18_CARD_KEY_SLOT_2), 1)
            IF_INT_EQUAL(GSWF(GSWF_AJI18_CARD_KEY_SLOT_3), 1)
                SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG7_16_FACTORY_DOOR)
                CALL(evt_del_case_evt, 0, GW(10))
                SET_VALUE(LW(0), STRING("e_bero"))
                CALL_CHILD(PTR(bero_case_switch_on))
                CALL(evt_cam3d_evt_set, -140, 90, 369, 150, 60, -98, 500, 11)
                WAIT_MS(1200)
                CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_lights1_m"), MAPOBJ_FLAG_HIDE)
                CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_lights1_r"), MAPOBJ_FLAG_HIDE)
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_DOOR_LAMP1"), LW(0), LW(1), LW(2), 0)
                WAIT_MS(700)
                CALL(evt_cam3d_evt_off, 11, 0)
            END_IF
        END_IF
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(key_lock_koujyou)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg7_aji_67_02"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_koopa_after)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, 75, 0, FLOAT(80.0f))
    END_INLINE_EVENT
    CALL(evt_party_move_pos2, 0, 115, 0, FLOAT(80.0f))
    CALL(evt_party_set_dir, 0, 270, 200)
    WAIT_MS(500)
    CALL(evt_fade_end_wait)
    CALL(evt_party_stop, 0)
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 90, 200, 0)
    END_INLINE_EVENT
    CALL(evt_msg_print_party, STRING("stg7_aji_43"))
    CALL(evt_cam3d_evt_set, 95, 55, 292, 95, 41, -8, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("stg7_aji_44"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_THINK1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_I_Z"))
    WAIT_MS(1500)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print_party, STRING("stg7_aji_45"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

static USER_FUNC(sysflag) {
    if (gp->flags & GLOBAL_FLAG_LOADED) {
        gp->flags &= ~GLOBAL_FLAG_LOADED;
        fadeEntry(FADE_CURTAIN_SIDES_A2, 0, (GXColor){0, 0, 0, 0});
    }
    return EVT_RETURN_DONE;
}

EVT_BEGIN(aji_18_init_evt)
    CALL(sysflag)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG7_DUN2"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG7_AJI1"))
    CALL(evt_snd_set_rev_mode, 1)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG7_16_FACTORY_DOOR)
        SET_VALUE(GSWF(GSWF_AJI18_CARD_KEY_SLOT_1), 1)
        SET_VALUE(GSWF(GSWF_AJI18_CARD_KEY_SLOT_2), 1)
        SET_VALUE(GSWF(GSWF_AJI18_CARD_KEY_SLOT_3), 1)
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI18_CARD_KEY_SLOT_1), 1)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_kagi1_aka"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_kagi1_mid"), MAPOBJ_FLAG_HIDE)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_kagi1_aka"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_kagi1_mid"), MAPOBJ_FLAG_HIDE)
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI18_CARD_KEY_SLOT_2), 1)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_kagi2_aka"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_kagi2_mid"), MAPOBJ_FLAG_HIDE)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_kagi2_aka"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_kagi2_mid"), MAPOBJ_FLAG_HIDE)
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI18_CARD_KEY_SLOT_3), 1)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_kagi3_aka"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_kagi3_mid"), MAPOBJ_FLAG_HIDE)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_kagi3_aka"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_kagi3_mid"), MAPOBJ_FLAG_HIDE)
    END_IF
    SET_VALUE(LW(0), 0)
    CALL(evt_pouch_check_item, ITEM_CARD_KEY_0x1D, LW(1))
    ADD(LW(0), LW(1))
    CALL(evt_pouch_check_item, ITEM_CARD_KEY_0x1E, LW(1))
    ADD(LW(0), LW(1))
    CALL(evt_pouch_check_item, ITEM_CARD_KEY_0x1F, LW(1))
    ADD(LW(0), LW(1))
    IF_INT_EQUAL(GSWF(GSWF_AJI18_CARD_KEY_SLOT_1), 0)
        SET_VALUE(LW(0), 0)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_kagi1"), 0, PTR(evt_machine), 0)
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI18_CARD_KEY_SLOT_2), 0)
        SET_VALUE(LW(0), 1)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_kagi2"), 0, PTR(evt_machine), 0)
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI18_CARD_KEY_SLOT_3), 0)
        SET_VALUE(LW(0), 2)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_kagi3"), 0, PTR(evt_machine), 0)
    END_IF
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG7_16_FACTORY_DOOR)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("e_bero"), 0, PTR(key_lock_koujyou), GW(10))
        SET_VALUE(LW(0), STRING("e_bero"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_lights1_m"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_lights1_r"), MAPOBJ_FLAG_HIDE)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_lights1_m"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_lights1_r"), MAPOBJ_FLAG_HIDE)
    END_IF
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG7_20_LORD_CRUMP_DEFEATED, STORY_STG7_25_00_1_BOWSER_POSHLEY_SANCTUM)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("e_bero"), 0, PTR(key_lock_koujyou), 0)
        SET_VALUE(LW(0), STRING("e_bero"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_lights1_m"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_lights1_r"), MAPOBJ_FLAG_HIDE)
    END_SWITCH
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG7_20_LORD_CRUMP_DEFEATED, STORY_STG7_25_00_1_BOWSER_POSHLEY_SANCTUM)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_EQUAL(LW(0), STRING("e_bero"))
            CALL(evt_mario_get_party, LW(15))
            IF_INT_EQUAL(LW(15), 0)
                CALL(evt_mario_set_party, 0, 1)
                CALL(evt_party_run, 0)
#if VERSION >= VERSION_US
            END_IF
#endif
                CALL(evt_pouch_mario_recovery)
                CALL(evt_pouch_all_party_recovery)
#if VERSION >= VERSION_US
            CALL(N_evt_sub_status_gauge_force_update)
#else
            END_IF
#endif
            SPAWN_EVENT(PTR(evt_koopa_after))
        END_IF
    END_SWITCH
    SPAWN_EVENT(PTR(evt_emergency))
    RETURN
EVT_END()
