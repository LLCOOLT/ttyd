// eki_05 (駅, Riverside Station): room with a treasure chest holding Ultra Boots and an elevator key item; doors to eki_04 and eki_06.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_case.h"
#include "evt/evt_hit.h"
#include "evt/evt_item.h"
#include "driver/itemdrv.h"
#include "evt/evt_lecture.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "party/party_motion.h"
#include "eki.h"
#include "version.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"
#include "driver/casedrv.h"

static BeroEntry bero_data[4];
extern EvtWord grass_open_1[];
extern EvtWord grass_open_2[];
extern EvtWord evt_boots[];
extern EvtWord evt_elvkey[];

static EVT_BEGIN(n_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door_1"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(n_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door_1"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door_2"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door_2"), 0, LW(0), 0)
    RETURN
EVT_END()

static BeroEntry bero_data[] = {
    {
        "n_bero", // hitName
        1, // type
        3, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "eki_04", // nextMapName
        "s_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        n_close, // enterAnimeArg
        n_open, // exitAnimeArg
    },
    {
        "w_bero_1", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "eki_06", // nextMapName
        "e_bero_2", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "w_bero_2", // hitName
        1, // type
        3, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "eki_06", // nextMapName
        "e_bero_1", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        w_close, // enterAnimeArg
        w_open, // exitAnimeArg
    },
    {0},
};

EVT_BEGIN(grass_open_1)
    IF_INT_EQUAL(GF(0), 1)
        CALL(evt_map_playanim, STRING("anm_nata"), 0, 0)
        SET_VALUE(GF(0), 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(grass_open_2)
    IF_INT_EQUAL(GF(0), 0)
        CALL(evt_map_playanim, STRING("anm_tana"), 0, 0)
        SET_VALUE(GF(0), 1)
    ELSE
        CALL(evt_map_playanim, STRING("anm_nata"), 0, 0)
        SET_VALUE(GF(0), 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_boots)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("tbox"), LW(0), LW(1), LW(2))
    CALL(lect_juyoitem_rel_set, PTR(all_juyoitem_lecture_rel))
    CALL(evt_item_entry, STRING("boots"), ITEM_ULTRA_BOOTS, LW(0), LW(1), LW(2), 17, -1, 0)
    CALL(evt_mobj_wait_animation_end, STRING("tbox"))
    CALL(evt_item_get_important_item, STRING("boots"))
    CALL(evt_item_get_item, STRING("boots"))
    CALL(evt_item_get_item_end_wait, STRING("boots"))
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_36_SPRING_JUMP)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_elvkey)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_37_ELEVATOR_KEY)
    RETURN
EVT_END()

static EVT_BEGIN(evt_head)
    CALL(evt_item_delete, STRING("elvkey"))
    CALL(evt_item_entry, STRING("elvkey"), ITEM_ELEVATOR_KEY_0x1A, -135, 166, -70, 4, -1, PTR(evt_elvkey))
    CALL(evt_item_set_move_dir_speed, STRING("elvkey"), FLOAT(135.0f), FLOAT(90.0f))
    CALL(evt_item_set_gravity, STRING("elvkey"), FLOAT(1.0f))
    CALL(evt_item_set_bound_rate, STRING("elvkey"), FLOAT(0.5996094f))
    CALL(evt_item_set_jump_power, STRING("elvkey"), FLOAT(500.0f))
    CALL(evt_item_status_on, STRING("elvkey"), ITEM_STATUS_CUSTOM_LAUNCH)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

EVT_BEGIN(eki_05_init_evt)
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmoff, PSND_FADE_OUT)
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_EKI2"))
    SET_VALUE(GF(0), 0)
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("a_garasu_1"), 0, PTR(grass_open_1), 0)
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("a_garasu_2"), 0, PTR(grass_open_2), 0)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_36_SPRING_JUMP)
        CALL(evt_mobj_itembox, STRING("tbox"), -85, 295, 0, 1, 0, PTR(evt_boots), GSWF(GSWF_EKI05_ULTRA_BOOTS_CHEST_OPENED))
    END_IF
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_37_ELEVATOR_KEY)
        CALL(evt_item_entry, STRING("elvkey"), ITEM_ELEVATOR_KEY_0x1A, -135, 136, -70, 17, -1, PTR(evt_elvkey))
        CALL(evt_run_case_evt, CASE_COND_HEAD, 1, STRING("a_t_2"), 0, PTR(evt_head), 0)
    END_IF
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_map_playanim, STRING("anm_mizu"), 0, 0)
            CALL(evt_map_checkanim, STRING("anm_mizu"), LW(0), LW(1))
            WAIT_MS(700)
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_AMB_WATERDROP1"), -129, 295, -17, 0)
            WAIT_MS(100)
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_AMB_WATERDROP1"), 179, 295, -17, 0)
            WAIT_MS(100)
        END_LOOP
    END_INLINE_EVENT
#if VERSION >= VERSION_US
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S"), MAPOBJ_FLAG_BBOX_CULL)
#endif
#if VERSION == VERSION_EU
    BEGIN_INLINE_EVENT
        CALL(evt_seq_wait, 2)
        CALL(evt_bero_exec_wait, 65536)
        SET_VALUE(LW(0), STRING("w_bero_1"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_hitobj_attr_onoff, 0, 0, STRING("w_bero_1"), 8388612)
    END_INLINE_EVENT
#endif
    RETURN
EVT_END()
