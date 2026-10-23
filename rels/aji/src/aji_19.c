#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "party.h"
#include "driver/hitdrv.h"
#include "string.h"
#include "evt/evt_bero.h"

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

__declspec(section ".data") u64 fd_aji_19_negone_one_374;
__declspec(section ".data") s32 fd_aji_19_neg_one_382[1];
__declspec(section ".data") s32 fd_aji_19___local_PI_383[1];
__declspec(section ".data") s32 fd_aji_19___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_aji_19_one_negone_373;
__declspec(section ".data") s32 fd_aji_19___local_PIO2_384[1];
__declspec(section ".data") s32 fd_aji_19_one_381[1];
__declspec(section ".data") u64 fd_aji_19_negone_one_360;
__declspec(section ".data") s32 fd_aji_19_neg_one_365[1];
__declspec(section ".data") s32 fd_aji_19___local_PI_366[1];
__declspec(section ".data") s32 fd_aji_19___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_aji_19_one_negone_359;
__declspec(section ".data") s32 fd_aji_19___local_PIO2_367[1];
__declspec(section ".data") s32 fd_aji_19_one_364[1];
static s32 w_door_close[22];
static s32 w_door_open[22];
static s32 e_door_close[22];
static s32 e_door_open[22];
static s32 bero_entry_data[45];
s32 evt_hajimete[33];
s32 aji_19_init_evt[56];

__declspec(section ".data") u64 fd_aji_19_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_19_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_19___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_19___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_19_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_19___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_19_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_aji_19_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_19_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_19___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_19___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_19_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_19___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_19_one_364[] = {
    1065353216,
};

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

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65546, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"moo_02", (s32)"n_bero", 327685, (s32)w_door_close, (s32)w_door_open, (s32)"e_bero",
    65546, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"aji_00", (s32)"w_bero", 327685, (s32)e_door_close, (s32)e_door_open, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
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

static USER_FUNC(mario_chk) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;

    if (mario != NULL && mario->hitobjStandOn != NULL) {
        if (hitIsGroup(mario->hitobjStandOn, hitNameToPtr("A_b_ue"))) {
            mario->unk174.x = 1.0f;
        } else if (hitIsGroup(mario->hitobjStandOn, hitNameToPtr("A_b_shita"))) {
            mario->unk174.x = -1.0f;
        }
    }
    party = partyGetPtr(marioGetPartyId());
    if (party != NULL && party->field_138 != NULL) {
        if (hitIsGroup(party->field_138, hitNameToPtr("A_b_ue"))) {
            party->field_AC = 1.0f;
        }
        if (hitIsGroup(party->field_138, hitNameToPtr("A_b_shita"))) {
            party->field_AC = -1.0f;
        }
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party != NULL && party->field_138 != NULL) {
        if (hitIsGroup(party->field_138, hitNameToPtr("A_b_ue"))) {
            party->field_AC = 1.0f;
        }
        if (hitIsGroup(party->field_138, hitNameToPtr("A_b_shita"))) {
            party->field_AC = -1.0f;
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

