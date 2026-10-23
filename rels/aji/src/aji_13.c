#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/hitdrv.h"
#include "string.h"
#include "mario/mario.h"
#include "party.h"
#include "driver/mapdrv.h"
#include "system.h"
#include "dolphin/mtx.h"
#include "driver/camdrv.h"

static BOOL _hitIsGroupSub(HitEntry* target, HitEntry* node, BOOL checkSibling);
BOOL hitIsGroup(HitEntry* target, HitEntry* group);
void* _mapAlloc(u32 size);
double sin(double x);
double cos(double x);
typedef struct { Vec pos; Vec delta; } BeltWork;
void camFollowYOn(void);

USER_FUNC(bg_cam_chk);
USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_hit_bind_mapobj);
USER_FUNC(evt_hit_bind_update);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_img_alloc_capture);
USER_FUNC(evt_img_clear_virtual_point);
USER_FUNC(evt_img_entry);
USER_FUNC(evt_img_onoff);
USER_FUNC(evt_img_release);
USER_FUNC(evt_img_set_paper);
USER_FUNC(evt_img_set_paper_anim);
USER_FUNC(evt_img_wait_animend);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_set_scale);
USER_FUNC(evt_map_entry_airport_harbor);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_clear_offscreen);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mapobj_set_offscreen);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_cam_keep_off);
USER_FUNC(evt_mario_cam_y_on);
USER_FUNC(evt_mario_get_name_hitobj_head);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_recovery_blk);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_mobj_switch_blue);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_npc_check_delete);
USER_FUNC(evt_offscreen_delete);
USER_FUNC(evt_offscreen_entry);
USER_FUNC(evt_offscreen_get_boundingbox);
USER_FUNC(evt_paper_entry);
USER_FUNC(evt_pouch_check_item);
USER_FUNC(evt_pouch_remove_item);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_sub_random);
USER_FUNC(evt_win_item_select);
static USER_FUNC(mario_chk);
USER_FUNC(hit_group_chk);
static BOOL hitIsGroup(HitEntry* target, HitEntry* group);
static BOOL _hitIsGroupSub(HitEntry* target, HitEntry* node, BOOL checkSibling);
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 evt_bero_info_run[];
extern s32 evt_emergency[];

__declspec(section ".data") u64 fd_aji_13_negone_one_374;
__declspec(section ".data") s32 fd_aji_13_neg_one_382[1];
__declspec(section ".data") s32 fd_aji_13___local_PI_383[1];
__declspec(section ".data") s32 fd_aji_13___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_aji_13_one_negone_373;
__declspec(section ".data") s32 fd_aji_13___local_PIO2_384[1];
__declspec(section ".data") s32 fd_aji_13_one_381[1];
__declspec(section ".data") u64 fd_aji_13_negone_one_360;
__declspec(section ".data") s32 fd_aji_13_neg_one_365[1];
__declspec(section ".data") s32 fd_aji_13___local_PI_366[1];
__declspec(section ".data") s32 fd_aji_13___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_aji_13_one_negone_359;
__declspec(section ".data") s32 fd_aji_13___local_PIO2_367[1];
__declspec(section ".data") s32 fd_aji_13_one_364[1];
static s32 w_door_close[22];
static s32 w_door_open[22];
static s32 e_door_close[22];
static s32 e_door_open[22];
__declspec(section ".data") s32 evt_snd_stop[12];
static s32 evt_haikei_in[16];
static s32 bero_entry_data[225];
static s32 name_tbl[13];
__declspec(section ".data") s32 name_tbl2[6];
s32 move_left_right[128];
s32 move_up_down[226];
s32 move_r[84];
s32 left_right_tbl[37];
s32 up_down_tbl[32];
s32 r_tbl[77];
s32 shikake_init[66];
static s32 evt_sw[134];
static s32 evt_hari[70];
static s32 evt_ramp[68];
s32 evt_bcv_sw[99];
__declspec(section ".data") s32 evt_key_get[5];
static __declspec(section ".data") s32 key_tbl[2];
static s32 evt_door_msg[87];
s32 aji_13_init_evt[295];

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

static BOOL hitIsGroup(HitEntry* target, HitEntry* group) {
    // whether target is group or one of its descendants
    return _hitIsGroupSub(target, group, FALSE);
}

__declspec(section ".data") u64 fd_aji_13_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_13_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_13___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_13___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_13_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_13___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_13_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_aji_13_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_13_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_13___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_13___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_13_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_13___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_13_one_364[] = {
    1065353216,
};

static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_snd_stop)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 370)
        CALL(evt_snd_sfxoff, GW(11))
    END_IF
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(evt_haikei_in)
    BEGIN_INLINE_EVENT
        CALL(evt_bero_exec_wait, 65536)
        WAIT_FRAMES(10)
        CALL(evt_mario_cam_keep_off)
        CALL(evt_mario_cam_y_on)
    END_INLINE_EVENT
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65546, 20000, 100000, 0, 0, -1, 0,
    -1, (s32)evt_snd_stop, (s32)"aji_18", (s32)"e_bero", 327685, (s32)w_door_close, (s32)w_door_open, (s32)"e_bero",
    65546, 20000, 100000, 0, 0, -1, 0, -1,
    (s32)evt_snd_stop, (s32)"aji_14", (s32)"w_bero", 327685, (s32)e_door_close, (s32)e_door_open, (s32)"dokan_1", 131072,
    9, 100000, 0, 0, -1, 0, 6, 0,
    0, (s32)"dokan_6", 65537, 0, 0, (s32)"dokan_2", 131072, 9,
    100000, 0, 0, -1, 0, 6, 0, 0,
    (s32)"dokan_7", 65537, 0, 0, (s32)"dokan_3", 131072, 9, 100000,
    0, 0, -1, 0, 6, 0, 0, (s32)"dokan_8",
    65537, 0, 0, (s32)"dokan_4", 131072, 9, 100000, 0,
    0, -1, 0, 6, 0, 0, (s32)"dokan_9", 65537,
    0, 0, (s32)"dokan_5", 131072, 9, 100000, 0, 0,
    -1, 0, 6, 0, 0, (s32)"dokan_10", 65537, 0,
    0, (s32)"dokan_6", 268566528, 9, 100000, 0, 0, -1,
    (s32)evt_haikei_in, 6, 0, 0, (s32)"dokan_1", 65537, 0, 0,
    (s32)"dokan_7", 268566528, 9, 100000, 0, 0, -1, (s32)evt_haikei_in,
    6, 0, 0, (s32)"dokan_2", 65537, 0, 0, (s32)"dokan_8",
    268566528, 9, 100000, 0, 0, -1, (s32)evt_haikei_in, 6,
    0, 0, (s32)"dokan_3", 65537, 0, 0, (s32)"dokan_9", 268566528,
    9, 100000, 0, 0, -1, (s32)evt_haikei_in, 6, 0,
    0, (s32)"dokan_4", 65537, 0, 0, (s32)"dokan_10", 268566528, 9,
    100000, 0, 0, -1, (s32)evt_haikei_in, 6, 0, 0,
    (s32)"dokan_5", 65537, 0, 0, (s32)"dokan_c", 131072, 9, 100000,
    0, 0, -1, 0, 6, 0, 0, (s32)"dokan_d",
    65537, 0, 0, (s32)"dokan_d", 131072, 9, 100000, 0,
    0, -1, 0, 6, 0, 0, (s32)"dokan_c", 65537,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0,
};

static s32 name_tbl[] = {
    (s32)"A_ugoku_1", (s32)"A_ugoku_2", (s32)"A_ugoku_3", (s32)"A_ugoku_4", (s32)"A_ugoku_h_1", (s32)"A_ugoku_h_2", (s32)"A_ugoku_h_3", (s32)"A_ugoku_h_4",
    (s32)"A_ugoku_h_5", (s32)"A_ugoku_h_6", (s32)"A_ugoku_h_7", (s32)"A_ugoku_h_8", (s32)"A_ugoku_h_9",
};

__declspec(section ".data") s32 name_tbl2[] = {
    (s32)"A_zenmai1", (s32)"A_zenmai2", (s32)"A_zenmai3", (s32)"A__zenmai4", (s32)"A_zenmai5", (s32)"A_zenmai6",
};

static USER_FUNC(mario_chk) {
    BeltWork* work;
    s32 i;
    f32 angle;
    f32 delta;
    f32 dist;
    f32 rot;

    if (isFirstCall) {
        work = _mapAlloc(sizeof(BeltWork) * 13);
        for (i = 0; i < 13; i++) {
            work[i].pos = (Vec){0.0f, 0.0f, 0.0f};
            work[i].delta = (Vec){0.0f, 0.0f, 0.0f};
        }
        event->userdata[0] = (s32)work;
        *(f32*)&event->userdata[1] = 0.0f;
        event->userdata[2] = 0;
    }
    work = (BeltWork*)event->userdata[0];
    for (i = 0; i < 13; i++) {
        HitEntry* hit = hitNameToPtr((const char*)name_tbl[i]);
        if (hit != NULL && hit->mapObj != NULL) {
            Vec pos = (Vec){hit->mapObj->unkAC[0][3], hit->mapObj->unkAC[1][3], hit->mapObj->unkAC[2][3]};
            PSVECSubtract(&pos, &work[i].pos, &work[i].delta);
            work[i].pos = pos;
        }
    }
    for (i = 0; i < 13; i++) {
        HitEntry* hit = hitNameToPtr((const char*)name_tbl[i]);
        MarioWork* mario = marioGetPtr();
        if (hit != NULL && mario != NULL && mario->hitobjStandOn != NULL && hitIsGroup(mario->hitobjStandOn, hit)) {
            mario->unk174.x = 10.0f * work[i].delta.x;
            mario->unk174.z = 10.0f * work[i].delta.z;
            break;
        }
    }
    for (i = 0; i < 13; i++) {
        HitEntry* hit = hitNameToPtr((const char*)name_tbl[i]);
        PartyEntry* party = partyGetPtr(0);
        if (hit != NULL && party != NULL && party->field_138 != NULL && hitIsGroup(party->field_138, hit)) {
            party->field_AC = 10.0f * work[i].delta.x;
            party->field_B4 = 10.0f * work[i].delta.z;
            break;
        }
    }
    if (evtGetValue(event, GSW(0)) >= 370) {
        MarioWork* mario = marioGetPtr();
        PartyEntry* party = partyGetPtr(0);
        if (mario != NULL && mario->hitobjStandOn != NULL && hitIsGroup(mario->hitobjStandOn, hitNameToPtr("A_bel"))) {
            mario->unk174.x = 0.6f;
        }
        if (party != NULL && party->field_144 != NULL && hitIsGroup(party->field_138, hitNameToPtr("A_bel"))) {
            party->field_AC = 0.6f;
        }
    }
    for (i = 0; i < 6; i++) {
        HitEntry* hit = hitNameToPtr((const char*)name_tbl2[i]);
        MarioWork* mario = marioGetPtr();
        if (hit == NULL) {
            continue;
        }
        if (mario->hitobjStandOn == NULL) {
            *(f32*)&event->userdata[1] = 0.0f;
            event->userdata[2] = 0;
            continue;
        }
        if (hitIsGroup(mario->hitobjStandOn, hit)) {
            Vec v = (Vec){0.0f, 1.0f, 0.0f};
            Mtx m;
            mtxGetRotationElement(hit->mapObj->unkAC, m, 'x', 'y');
            PSMTXMultVec(m, &v, &v);
            angle = angleABf(0.0f, 0.0f, v.x, v.y);
            delta = angle - *(f32*)&event->userdata[1];
            hitObjGetPos((const char*)name_tbl2[i], &v);
            dist = distABf(mario->position.x, mario->position.y, v.x, v.y);
            rot = angleABf(v.x, v.y, mario->position.x, mario->position.y);
            if ((HitEntry*)event->userdata[2] != NULL && strcmp(hit->joint->name, ((HitEntry*)event->userdata[2])->joint->name) == 0) {
                rot = 6.2831855f * (rot + delta) / 360.0f;
                mario->unk174.x = (v.x + dist * (f32)sin(rot)) - mario->position.x;
                mario->unk174.y = (v.y - dist * (f32)cos(rot)) - mario->position.y;
            }
            *(f32*)&event->userdata[1] = angle;
            event->userdata[2] = (s32)hit;
            break;
        }
    }
    return EVT_RETURN_BLOCK;
}

EVT_BEGIN(move_left_right)
    SET_VALUE(LW(5), LW(0))
    SET_VALUE(LW(6), LW(1))
    SET_VALUE(LW(7), LW(2))
    SET_VALUE(LW(8), LW(3))
    SET_VALUE(LW(9), LW(4))
    IF_INT_NOT_EQUAL(LW(5), 0)
        CALL(evt_hit_bind_mapobj, LW(5), LW(6))
    END_IF
    MULTIPLY(LW(7), 100)
    MULTIPLY(LW(8), 100)
    LOOP(0)
        CALL(evt_sub_intpl_msec_init, 11, LW(7), LW(8), LW(9))
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        CALL(evt_mapobj_trans, 1, LW(6), LW(0), 0, 0)
        IF_INT_NOT_EQUAL(LW(5), 0)
            CALL(evt_hit_bind_update, LW(5))
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        WAIT_MS(300)
        LOOP(0)
            IF_INT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_msec_init, 11, LW(8), LW(7), LW(9))
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        CALL(evt_mapobj_trans, 1, LW(6), LW(0), 0, 0)
        IF_INT_NOT_EQUAL(LW(5), 0)
            CALL(evt_hit_bind_update, LW(5))
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
        WAIT_MS(300)
        LOOP(0)
            IF_INT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(move_up_down)
    SET_VALUE(LW(5), LW(0))
    SET_VALUE(LW(6), LW(1))
    SET_VALUE(LW(7), LW(2))
    SET_VALUE(LW(8), LW(3))
    SET_VALUE(LW(9), LW(4))
    IF_INT_NOT_EQUAL(LW(5), 0)
        CALL(evt_hit_bind_mapobj, LW(5), LW(6))
    END_IF
    MULTIPLY(LW(7), 100)
    MULTIPLY(LW(8), 100)
    SET_VALUE(LW(4), LW(8))
    IF_STR_EQUAL(LW(5), STRING("A_ugoku_2"))
        SET_VALUE(LW(3), 1)
        SET_VALUE(GF(1), 0)
        BEGIN_SIBLING_EVENT
            LOOP(0)
                CALL(evt_mario_get_name_hitobj_head, LW(10))
                CALL(hit_group_chk, LW(10), LW(5), LW(10))
                IF_INT_NOT_EQUAL(LW(10), 0)
                    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                    IF_FLOAT_GREATER(LW(1), FLOAT(0.099609375f))
                        SET_VALUE(GF(1), 1)
                    END_IF
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        ELSE
        SET_VALUE(LW(3), 0)
    END_IF
    LOOP(0)
        CALL(evt_sub_intpl_msec_init, 11, LW(7), LW(8), LW(9))
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        CALL(evt_mapobj_trans, 1, LW(6), 0, LW(0), 0)
        IF_INT_NOT_EQUAL(LW(5), 0)
            CALL(evt_hit_bind_update, LW(5))
        END_IF
        IF_INT_NOT_EQUAL(LW(3), 0)
            IF_INT_NOT_EQUAL(GF(1), 0)
                MULTIPLY_FLOAT(LW(0), FLOAT(100.0f))
                GOTO(5)
            END_IF
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        LABEL(5)
        IF_INT_NOT_EQUAL(LW(3), 0)
            IF_INT_EQUAL(GF(1), 0)
                SET_VALUE(LW(8), LW(4))
                ELSE
                SET_VALUE(LW(8), LW(0))
            END_IF
            WAIT_MS(300)
            LOOP(0)
                IF_INT_EQUAL(GF(1), 0)
                    BREAK_LOOP
                END_IF
                SET_VALUE(GF(1), 0)
                WAIT_MS(1000)
            END_LOOP
            ELSE
            WAIT_MS(300)
        END_IF
        LOOP(0)
            IF_INT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_msec_init, 11, LW(8), LW(7), LW(9))
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        CALL(evt_mapobj_trans, 1, LW(6), 0, LW(0), 0)
        IF_INT_NOT_EQUAL(LW(5), 0)
            CALL(evt_hit_bind_update, LW(5))
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
        SET_VALUE(LW(8), LW(4))
        WAIT_MS(300)
        LOOP(0)
            IF_INT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(move_r)
    SET_VALUE(LW(5), LW(0))
    SET_VALUE(LW(6), LW(1))
    SET_VALUE(LW(7), LW(2))
    SET_VALUE(LW(8), LW(3))
    SET_VALUE(LW(9), LW(4))
    IF_INT_NOT_EQUAL(LW(5), 0)
        CALL(evt_hit_bind_mapobj, LW(5), LW(6))
    END_IF
    MULTIPLY(LW(7), 100)
    MULTIPLY(LW(8), 100)
    LOOP(0)
        CALL(evt_sub_intpl_msec_init, 0, LW(7), LW(8), LW(9))
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            CALL(evt_mapobj_rotate, 1, LW(6), 0, 0, LW(0))
            IF_INT_NOT_EQUAL(LW(5), 0)
                CALL(evt_hit_bind_update, LW(5))
            END_IF
            IF_INT_EQUAL(GF(0), 1)
                BREAK_LOOP
            END_IF
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(0)
            IF_INT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

s32 left_right_tbl[] = {
    (s32)"A_ugoku_1", (s32)"S_ugoku_1", 0, -150, 3000, (s32)"A_ugoku_3", (s32)"S_ugoku_3", 0,
    100, 1500, (s32)"A_ugoku_4", (s32)"S_ugoku_4", 0, -100, 1500, (s32)"A_ugoku_h_1",
    (s32)"S_ugoku_h_1", -30, 200, 3000, (s32)"A_ugoku_h_2", (s32)"S_ugoku_h_2", -50, 50,
    3000, (s32)"A_ugoku_h_3", (s32)"S_ugoku_h_3", 50, -50, 3000, (s32)"A_ugoku_h_7", (s32)"S_ugoku_h_7",
    -50, 80, 4500, 0, 0,
};

s32 up_down_tbl[] = {
    (s32)"A_ugoku_2", (s32)"S_ugoku_2", 0, -150, 2800, (s32)"A_ugoku_h_4", (s32)"S_ugoku_h_4", 0,
    100, 3000, (s32)"A_ugoku_h_5", (s32)"S_ugoku_h_5", 0, -200, 4000, (s32)"A_ugoku_h_6",
    (s32)"S_ugoku_h_6", 40, -150, 3000, (s32)"A_ugoku_h_8", (s32)"S_ugoku_h_8", 20, -100,
    2000, (s32)"A_ugoku_h_9", (s32)"S_ugoku_h_9", -100, 20, 2000, 0, 0,
};

s32 r_tbl[] = {
    (s32)"A_zenmai1", (s32)"S_zenmai1", 0, 360, 6000, (s32)"A_zenmai2", (s32)"S_zenmai2", 0,
    -360, 6000, (s32)"A_zenmai3", (s32)"S_zenmai3", 0, 360, 3000, (s32)"A__zenmai4",
    (s32)"S_zenmai4", 0, 360, 9000, (s32)"A_zenmai5", (s32)"S_zenmai5", 0, -360,
    6000, (s32)"A_zenmai6", (s32)"S_zenmai6", 0, -360, 3000, 0, (s32)"S_zen1",
    0, 360, 6000, 0, (s32)"S_zen2", 0, -360, 3000,
    0, (s32)"S_zen3", 0, -360, 6000, 0, (s32)"S_zen4", 0,
    360, 6000, 0, (s32)"S_zen5", 0, 360, 6000, 0,
    (s32)"S_zen6", 0, -360, 3000, 0, (s32)"S_zen7", 0, 360,
    6000, 0, (s32)"S_zen8", 0, -360, 6000, 0, (s32)"S_zen9",
    0, 360, 3000, 0, 0,
};

EVT_BEGIN(shikake_init)
    SET_VALUE(GF(0), 0)
    SET_INT_READ_ADDR(PTR(left_right_tbl))
    LOOP(0)
        READ_INT2(LW(0), LW(1))
        READ_INT3(LW(2), LW(3), LW(4))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        SPAWN_EVENT(PTR(move_left_right))
    END_LOOP
    SET_INT_READ_ADDR(PTR(up_down_tbl))
    LOOP(0)
        READ_INT2(LW(0), LW(1))
        READ_INT3(LW(2), LW(3), LW(4))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        SPAWN_EVENT(PTR(move_up_down))
    END_LOOP
    SET_INT_READ_ADDR(PTR(r_tbl))
    LOOP(0)
        READ_INT2(LW(0), LW(1))
        READ_INT3(LW(2), LW(3), LW(4))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        SPAWN_EVENT(PTR(move_r))
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(mario_chk)
    END_INLINE_EVENT
    RETURN
EVT_END()

static EVT_BEGIN(evt_sw)
    CALL(evt_mario_key_onoff, 0)
    SET_VALUE(GF(0), 1)
    CALL(evt_cam3d_evt_set, 475, 425, 743, 475, 325, 0, 1000, 11)
    WAIT_MS(2500)
    CALL(evt_paper_entry, STRING("OFF_hei_07"))
    CALL(evt_img_entry, STRING("img"))
    CALL(evt_img_set_paper, STRING("img"), STRING("OFF_hei_07"))
    CALL(evt_offscreen_entry, STRING("ofs"))
    CALL(evt_img_onoff, STRING("img"), 0)
    CALL(evt_mapobj_set_offscreen, 1, STRING("S_kaidan"), STRING("ofs"))
    CALL(evt_offscreen_get_boundingbox, STRING("ofs"), LW(10), LW(11), LW(12), LW(13))
    CALL(evt_img_alloc_capture, STRING("img"), 0, 0, 1, LW(10), LW(11), LW(12), LW(13))
    WAIT_FRAMES(1)
    CALL(evt_img_clear_virtual_point, STRING("img"))
    CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_1"))
    CALL(evt_img_onoff, STRING("img"), 1)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_OFF7_KAIDAN_APPEAR1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kaidan"), 1)
    CALL(evt_hitobj_onoff, STRING("A_kaidan"), 1, 1)
    WAIT_MS(1800)
    CALL(evt_img_wait_animend, STRING("img"))
    CALL(evt_img_onoff, STRING("img"), 0)
    CALL(evt_img_release, STRING("img"))
    CALL(evt_mapobj_clear_offscreen, 1, STRING("S_kaidan"))
    CALL(evt_offscreen_delete, STRING("ofs"))
    SET_VALUE(GSW(0), 371)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_off, 1000, 11)
    WAIT_MS(500)
    SET_VALUE(GF(0), 0)
    WAIT_MS(500)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_hari)
    SET_VALUE(LW(8), LW(0))
    SET_VALUE(LW(2), 0)
    SET_VALUE(LF(0), 0)
    LOOP(0)
        CALL(evt_sub_random, 900, LW(3))
        IF_INT_EQUAL(LF(0), 0)
            MULTIPLY(LW(3), -1)
            SET_VALUE(LF(0), 1)
            ELSE
            SET_VALUE(LF(0), 0)
        END_IF
        CALL(evt_sub_random, 1500, LW(9))
        ADD(LW(9), 1500)
        CALL(evt_sub_intpl_msec_init, 11, LW(2), LW(3), LW(9))
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        CALL(evt_mapobj_rotate, 1, LW(8), 0, 0, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        SET_VALUE(LW(2), LW(3))
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(evt_ramp)
    CALL(evt_mapobj_get_position, STRING("S_bel"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_CONVEYER_MOVE1"), LW(0), LW(1), LW(2), GW(11))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_pato1"), 1)
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
        LOOP(0)
            CALL(evt_mapobj_rotate, 1, STRING("S_pato1"), 0, LW(0), 0)
            ADD_FLOAT(LW(0), FLOAT(10.0f))
            IF_FLOAT_GREATER(LW(0), FLOAT(360.0f))
                SUBTRACT_FLOAT(LW(0), FLOAT(360.0f))
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    SET_VALUE(LW(0), STRING("S_hari01"))
    SPAWN_EVENT(PTR(evt_hari))
    SET_VALUE(LW(0), STRING("S_hari02"))
    SPAWN_EVENT(PTR(evt_hari))
    SET_VALUE(LW(0), STRING("S_hari03"))
    SPAWN_EVENT(PTR(evt_hari))
    SET_VALUE(LW(0), STRING("S_hari04"))
    SPAWN_EVENT(PTR(evt_hari))
    RETURN
EVT_END()

EVT_BEGIN(evt_bcv_sw)
    SET_VALUE(GSW(0), 370)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam3d_evt_set, -575, 152, 578, -575, 57, 37, 1000, 11)
    WAIT_MS(1000)
    WAIT_MS(1000)
    CALL(evt_mapobj_get_position, STRING("S_bel"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_CONVEYER_ACTIVE1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("meta_1_1"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("meta_2_1"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("meta_3_1"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("meta_4_1"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("meta_1_2"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("meta_2_2"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("meta_3_2"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("meta_4_2"), 1)
    CALL(evt_map_playanim, STRING("kon"), 1, 0)
    SPAWN_EVENT(PTR(evt_ramp))
    WAIT_MS(3000)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_key_get)
    SET_VALUE(GSWF(4181), 1)
    RETURN
EVT_END()

static __declspec(section ".data") s32 key_tbl[] = {
    32, -1,
};

static EVT_BEGIN(evt_door_msg)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_pouch_check_item, 32, LW(0))
    IF_INT_LESS(LW(0), 1)
        CALL(evt_msg_print, 0, STRING("stg7_aji_67"), 0, 0)
        CALL(evt_mario_key_onoff, 1)
        RETURN
    END_IF
    CALL(evt_win_item_select, 0, PTR(key_tbl), LW(0), 0)
    IF_INT_NOT_EQUAL(LW(0), -1)
        CALL(evt_pouch_remove_item, LW(0), LW(1))
        SET_VALUE(LW(0), STRING("e_bero"))
        CALL_CHILD(PTR(bero_case_switch_on))
        SET_VALUE(GSW(0), 372)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kagi1_mid"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kagi1_aka"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_lights1_m"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_lights1_r"), 1)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_DOOR_UNLOCK1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_exit_case_evt)
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(aji_13_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_DUN2"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI7"))
    CALL(evt_snd_set_rev_mode, 1)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(shikake_init))
    CALL(evt_map_entry_airport_harbor, 0, STRING("hikou1"), STRING("A_hikou1"))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_ami2"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_dai5"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_dai3"), 2)
    IF_INT_LESS(GSW(0), 370)
        CALL(evt_mobj_switch_blue, 0, STRING("bcv_sw"), -150, 0, 100, PTR(evt_bcv_sw), GSWF(4185))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_pato1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("meta_1_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("meta_2_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("meta_3_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("meta_4_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("meta_1_2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("meta_2_2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("meta_3_2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("meta_4_2"), 1)
        ELSE
        CALL(evt_map_playanim, STRING("kon"), 1, 0)
        CALL_CHILD(PTR(evt_ramp))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("meta_1_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("meta_2_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("meta_3_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("meta_4_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("meta_1_2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("meta_2_2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("meta_3_2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("meta_4_2"), 1)
    END_IF
    IF_INT_EQUAL(GSWF(4181), 0)
        CALL(evt_item_entry, STRING("key"), 32, -50, 100, 100, 16, -1, PTR(evt_key_get))
    END_IF
    IF_INT_LESS(GSW(0), 371)
        CALL(evt_mobj_switch_blue, 0, STRING("sw"), 650, 200, 100, PTR(evt_sw), GSWF(4184))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kaidan"), 1)
        CALL(evt_hitobj_onoff, STRING("A_kaidan"), 1, 0)
    END_IF
    IF_INT_LESS(GSW(0), 372)
        SET_VALUE(LW(0), STRING("e_bero"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_run_case_evt, 9, 1, STRING("A_kagi1"), 0, PTR(evt_door_msg), 0)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kagi1_mid"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_lights1_m"), 1)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kagi1_aka"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_lights1_r"), 1)
    END_IF
    CALL(evt_mobj_save_blk, STRING("mobj_save"), 200, 60, 100, 0, 0)
    CALL(evt_mobj_recovery_blk, STRING("mobj_recover"), 10, 300, 60, 100, 0, 0)
    CALL(evt_item_entry, STRING("item00"), 150, -670, 320, -450, 16, GSWF(4215), 0)
    CALL(evt_item_set_scale, STRING("item00"), FLOAT(0.5996094f))
    IF_INT_GREATER_OR_EQUAL(GSW(0), 373)
        CALL(evt_npc_check_delete, STRING("軍団ザコ魔法使い"))
        CALL(evt_npc_check_delete, STRING("バリアーンＺ"))
    END_IF
    SPAWN_EVENT(PTR(evt_emergency))
    BEGIN_INLINE_EVENT
        CALL(bg_cam_chk)
    END_INLINE_EVENT
    RETURN
EVT_END()


USER_FUNC(hit_group_chk) {
    s32* args = event->args;
    const char* name1 = (const char*)evtGetValue(event, args[0]);
    const char* name2 = (const char*)evtGetValue(event, args[1]);
    HitEntry* hit1 = name1 != NULL ? hitNameToPtr(name1) : NULL;
    HitEntry* hit2 = name2 != NULL ? hitNameToPtr(name2) : NULL;

    if (hit1 != NULL && hit2 != NULL && hitIsGroup(hit1, hit2)) {
        evtSetValue(event, args[2], TRUE);
    } else {
        evtSetValue(event, args[2], FALSE);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(bg_cam_chk) {
    CameraEntry* camera = camGetPtr(4);

    if (marioBgmodeChk() && (camera->flags & 0x10) && marioGetPtr()->airTimer == 0) {
        camFollowYOn();
    }
    return EVT_RETURN_BLOCK;
}

