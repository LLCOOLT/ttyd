// aji_19 (敵のアジト, X-Naut Fortress): the room reached from the Moon (moo_02), with the first-visit scene
// (evt_hajimete).
#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "mario/mario.h"
#include "mario/mario_party.h"
#include "party.h"
#include "driver/hitdrv.h"
#include "string.h"
#include "evt/evt_bero.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_party.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "evt/evt_telop.h"
#include "aji.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"
#if VERSION == VERSION_EU
#include "mario/mariost.h"
#endif

static BOOL _hitIsGroupSub(HitEntry* target, HitEntry* node, BOOL checkSibling);

static USER_FUNC(mario_chk);
static BOOL hitIsGroup(HitEntry* target, HitEntry* group);
static BOOL _hitIsGroupSub(HitEntry* target, HitEntry* node, BOOL checkSibling);

static BeroEntry bero_entry_data[3];
extern EvtWord evt_hajimete[];

static EVT_BEGIN(w_door_close)
#if VERSION <= VERSION_DEMO_US
    MULTIPLY_FLOAT(LW(0), FLOAT(0.22167969f))
#else
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
#endif
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(w_door_open)
#if VERSION <= VERSION_DEMO_US
    MULTIPLY_FLOAT(LW(0), FLOAT(0.22167969f))
#else
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
#endif
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(e_door_close)
#if VERSION <= VERSION_DEMO_US
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.22167969f))
#else
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.25f))
#endif
    CALL(evt_mapobj_trans, 0, STRING("S_door2_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
#if VERSION <= VERSION_DEMO_US
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.22167969f))
#else
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.25f))
#endif
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
        "moo_02", // nextMapName
        "n_bero", // nextBeroName
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
        "aji_00", // nextMapName
        "w_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        e_door_close, // enterAnimeArg
        e_door_open, // exitAnimeArg
    },
    {0},
};

EVT_BEGIN(evt_hajimete)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    WAIT_MS(1000)
    CALL(evt_party_stop, 0)
    WAIT_MS(200)
    CALL(evt_msg_print_party, STRING("stg7_aji_00_00_01"))
    CALL(evt_party_run, 0)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG7_07_01_INSIDE_THE_BUILDING)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_telop_entry, 15)
    RETURN
EVT_END()

EVT_BEGIN(aji_19_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG7_DUN1"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG7_AJI1"))
#if VERSION >= VERSION_JP
    CALL(evt_snd_set_rev_mode, 1)
#endif
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL(evt_map_playanim, STRING("hosi_01"), 1, 0)
    CALL(evt_map_playanim, STRING("hosi_02"), 1, 0)
    CALL(evt_map_playanim, STRING("hosi_03"), 1, 0)
    CALL(evt_map_playanim, STRING("yuka"), 1, 0)
    BEGIN_INLINE_EVENT
        CALL(mario_chk)
    END_INLINE_EVENT
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG7_07_01_INSIDE_THE_BUILDING)
        SPAWN_EVENT(evt_hajimete)
    END_IF
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("kanaami2"), MAPOBJ_FLAG_BBOX_CULL)
    RETURN
EVT_END()

// Conveyor push per frame: PAL scales the 60 Hz speed to the frame rate
static inline f32 beltSpeed(void) {
#if VERSION == VERSION_EU
    return 60.0f / gp->framerate;
#else
    return 1.0f;
#endif
}

static USER_FUNC(mario_chk) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;

    if (mario != NULL && mario->hitobjStandOn != NULL) {
        if (hitIsGroup(mario->hitobjStandOn, hitNameToPtr("A_b_ue"))) {
            mario->floorMove.x = beltSpeed();
        } else if (hitIsGroup(mario->hitobjStandOn, hitNameToPtr("A_b_shita"))) {
            mario->floorMove.x = -beltSpeed();
        }
    }
    party = partyGetPtr(marioGetPartyId());
    if (party != NULL && party->hitobjStandOn != NULL) {
        if (hitIsGroup(party->hitobjStandOn, hitNameToPtr("A_b_ue"))) {
            party->floorMoveX = beltSpeed();
        }
        if (hitIsGroup(party->hitobjStandOn, hitNameToPtr("A_b_shita"))) {
            party->floorMoveX = -beltSpeed();
        }
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party != NULL && party->hitobjStandOn != NULL) {
        if (hitIsGroup(party->hitobjStandOn, hitNameToPtr("A_b_ue"))) {
            party->floorMoveX = beltSpeed();
        }
        if (hitIsGroup(party->hitobjStandOn, hitNameToPtr("A_b_shita"))) {
            party->floorMoveX = -beltSpeed();
        }
    }
    return EVT_RETURN_BLOCK;
}

static BOOL hitIsGroup(HitEntry* target, HitEntry* group) {
    // whether target is group or one of its descendants
    return _hitIsGroupSub(target, group, FALSE);
}

static BOOL _hitIsGroupSub(HitEntry* target, HitEntry* node, BOOL checkSibling) {
    if (strcmp(target->joint->name, node->joint->name) == 0) {
        return TRUE;
    }
    if (node->child != NULL) {
        return _hitIsGroupSub(target, node->child, TRUE);
    }
    if (checkSibling && node->sibling != NULL) {
        return _hitIsGroupSub(target, node->sibling, TRUE);
    }
    return FALSE;
}
