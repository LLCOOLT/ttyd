#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "mario/mario.h"
#include "mario/mario_party.h"
#include "party.h"
#include "driver/hitdrv.h"
#include "string.h"
#include "evt/evt_bero.h"
#ifdef VERSION_G8MP01
#include "mario/mariost.h"
#endif

BOOL hitIsGroup(HitEntry* target, HitEntry* group);
static BOOL _hitIsGroupSub(HitEntry* target, HitEntry* node, BOOL checkSibling);

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_telop_entry);
static USER_FUNC(mario_chk);
static BOOL hitIsGroup(HitEntry* target, HitEntry* group);
static BOOL _hitIsGroupSub(HitEntry* target, HitEntry* node, BOOL checkSibling);

static BeroEntry bero_entry_data[3];
extern EvtWord evt_hajimete[];
extern EvtWord aji_19_init_evt[];

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
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.25f))
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
        20000, // directionId
        100000, // centerPosition
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
        20000, // directionId
        100000, // centerPosition
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
    SET_VALUE(GSW(0), 360)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_telop_entry, 15)
    RETURN
EVT_END()

EVT_BEGIN(aji_19_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_DUN1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI1"))
    CALL(evt_snd_set_rev_mode, 1)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_map_playanim, STRING("hosi_01"), 1, 0)
    CALL(evt_map_playanim, STRING("hosi_02"), 1, 0)
    CALL(evt_map_playanim, STRING("hosi_03"), 1, 0)
    CALL(evt_map_playanim, STRING("yuka"), 1, 0)
    BEGIN_INLINE_EVENT
        CALL(mario_chk)
    END_INLINE_EVENT
    IF_INT_LESS(GSW(0), 360)
        SPAWN_EVENT(PTR(evt_hajimete))
    END_IF
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("kanaami2"), 2)
    RETURN
EVT_END()

// Conveyor push per frame: PAL scales the 60 Hz speed to the frame rate
#ifdef VERSION_G8MP01
#define BELT_SPEED (60.0f / gp->framerate)
#else
#define BELT_SPEED 1.0f
#endif

static USER_FUNC(mario_chk) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;

    if (mario != NULL && mario->hitobjStandOn != NULL) {
        if (hitIsGroup(mario->hitobjStandOn, hitNameToPtr("A_b_ue"))) {
            mario->floorMove.x = BELT_SPEED;
        } else if (hitIsGroup(mario->hitobjStandOn, hitNameToPtr("A_b_shita"))) {
            mario->floorMove.x = -BELT_SPEED;
        }
    }
    party = partyGetPtr(marioGetPartyId());
    if (party != NULL && party->hitobjStandOn != NULL) {
        if (hitIsGroup(party->hitobjStandOn, hitNameToPtr("A_b_ue"))) {
            party->floorMoveX = BELT_SPEED;
        }
        if (hitIsGroup(party->hitobjStandOn, hitNameToPtr("A_b_shita"))) {
            party->floorMoveX = -BELT_SPEED;
        }
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party != NULL && party->hitobjStandOn != NULL) {
        if (hitIsGroup(party->hitobjStandOn, hitNameToPtr("A_b_ue"))) {
            party->floorMoveX = BELT_SPEED;
        }
        if (hitIsGroup(party->hitobjStandOn, hitNameToPtr("A_b_shita"))) {
            party->floorMoveX = -BELT_SPEED;
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

