#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "mario/mario.h"
#include "party.h"

double tan(double x);
double fmod(double x, double y);

USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_party_set_pose);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
static USER_FUNC(mario_kirimomi);
static USER_FUNC(z);

__declspec(section ".data") f32 fd_moo_03_negone_one_374[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_moo_03_neg_one_382;
__declspec(section ".data") f32 fd_moo_03___local_PI_383;
__declspec(section ".data") f32 fd_moo_03___local_3PIO2_385;
__declspec(section ".data") f32 fd_moo_03_one_negone_373[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_moo_03___local_PIO2_384;
__declspec(section ".data") f32 fd_moo_03_one_381;
__declspec(section ".data") f32 fd_moo_03_negone_one_360[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_moo_03_neg_one_365;
__declspec(section ".data") f32 fd_moo_03___local_PI_366;
__declspec(section ".data") f32 fd_moo_03___local_3PIO2_368;
__declspec(section ".data") f32 fd_moo_03_one_negone_359[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_moo_03___local_PIO2_367;
__declspec(section ".data") f32 fd_moo_03_one_364;
static s32 party_damage_pose[52];
static s32 mario_fly[203];
s32 moo_03_init_evt[35];

__declspec(section ".data") f32 fd_moo_03_negone_one_374[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_moo_03_neg_one_382 = -1.0f;

__declspec(section ".data") f32 fd_moo_03___local_PI_383 = 3.1415927f;

__declspec(section ".data") f32 fd_moo_03___local_3PIO2_385 = 4.712389f;

__declspec(section ".data") f32 fd_moo_03_one_negone_373[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_moo_03___local_PIO2_384 = 1.5707964f;

__declspec(section ".data") f32 fd_moo_03_one_381 = 1.0f;

__declspec(section ".data") f32 fd_moo_03_negone_one_360[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_moo_03_neg_one_365 = -1.0f;

__declspec(section ".data") f32 fd_moo_03___local_PI_366 = 3.1415927f;

__declspec(section ".data") f32 fd_moo_03___local_3PIO2_368 = 4.712389f;

__declspec(section ".data") f32 fd_moo_03_one_negone_359[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_moo_03___local_PIO2_367 = 1.5707964f;

__declspec(section ".data") f32 fd_moo_03_one_364 = 1.0f;

static EVT_BEGIN(party_damage_pose)
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        CALL(evt_party_set_pose, 0, STRING("PKR_D_1"))
        CASE_EQUAL(2)
        CALL(evt_party_set_pose, 0, STRING("PNK_D_1"))
        CASE_EQUAL(3)
        CALL(evt_party_set_pose, 0, STRING("D_1"))
        CASE_EQUAL(4)
        CALL(evt_party_set_pose, 0, STRING("PYS_D_1"))
        CASE_EQUAL(5)
        CALL(evt_party_set_pose, 0, STRING("PWD_D_1"))
        CASE_EQUAL(6)
        CALL(evt_party_set_pose, 0, STRING("PTR_D_1"))
        CASE_EQUAL(7)
        CALL(evt_party_set_pose, 0, STRING("PCH_D_1"))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(mario_fly)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    WAIT_FRAMES(1)
    CALL(evt_snd_sfxon, STRING("SFX_STG7_MARIO_FLY1"), LW(10))
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_set_pose, STRING("M_F_1"))
    CALL_CHILD(PTR(party_damage_pose))
    WAIT_FRAMES(1)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_dir, 0, 90, 0)
    CALL(evt_mario_set_pos, -300, -300, 0)
    CALL(evt_party_set_pos, 0, -300, -300, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 1, -304, 304, 3000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        SET_FLOAT_VALUE(LW(2), LW(0))
        MULTIPLY_FLOAT(LW(2), FLOAT(0.7890625f))
        ADD_FLOAT(LW(2), FLOAT(30.0f))
        CALL(evt_mario_set_pos, LW(0), LW(2), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 1, -304, 304, 3000)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        SET_FLOAT_VALUE(LW(2), LW(0))
        MULTIPLY_FLOAT(LW(2), FLOAT(0.7890625f))
        ADD_FLOAT(LW(2), FLOAT(-50.0f))
        CALL(evt_party_set_pos, 0, LW(0), LW(2), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
    END_INLINE_EVENT
    WAIT_MS(1000)
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        CALL(evt_msg_print, 0, STRING("stg7_moo_01_kur"), 0, 0)
        CASE_EQUAL(2)
        CALL(evt_msg_print, 0, STRING("stg7_moo_01_nok"), 0, 0)
        CASE_EQUAL(3)
        CALL(evt_msg_print, 0, STRING("stg7_moo_01_bom"), 0, 0)
        CASE_EQUAL(4)
        CALL(evt_msg_print, 0, STRING("stg7_moo_01_yos"), 0, 0)
        CASE_EQUAL(5)
        CALL(evt_msg_print, 0, STRING("stg7_moo_01_win"), 0, 0)
        CASE_EQUAL(6)
        CALL(evt_msg_print, 0, STRING("stg7_moo_01_viv"), 0, 0)
        CASE_EQUAL(7)
        CALL(evt_msg_print, 0, STRING("stg7_moo_01_chu"), 0, 0)
    END_SWITCH
    WAIT_MS(3000)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_snd_sfxoff, LW(10))
    END_INLINE_EVENT
    CALL(evt_bero_mapchange, STRING("moo_04"), 0)
    RETURN
EVT_END()

EVT_BEGIN(moo_03_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_MON1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_MOO3"))
    CALL(evt_map_playanim, STRING("hosi_01"), 1, 0)
    CALL(z)
    CALL(evt_cam3d_evt_set, 0, 0, LW(0), 0, 0, 0, 0, 11)
    SPAWN_EVENT(PTR(mario_fly))
    WAIT_FRAMES(10)
    BEGIN_INLINE_EVENT
        CALL(mario_kirimomi)
    END_INLINE_EVENT
    RETURN
EVT_END()

static USER_FUNC(z) {
    f32 t = tan(0.21816612780094147);
    // evt float encoding of the distance that fits 240 units in the fov
    event->lwData[0] = (s32)(1024.0f * (240.0f / t / 2)) - 230000000;
    return EVT_RETURN_DONE;
}

static USER_FUNC(mario_kirimomi) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);

    mario->field_0xB4 = mario->wPlayerCollisionBox.y / 2;
    mario->field_0xC4 -= 10.0f;
    mario->field_0xC4 = fmod(mario->field_0xC4, 360.0);
    if (party != NULL) {
        if (party->currentMemberId != 4) {
            party->field_8C = party->height / 2;
        } else {
            party->field_8C = (party->height - 10.0f) / 2;
        }
        party->field_8C *= party->scale.y;
        party->rotation -= 10.0f;
        party->rotation = fmod(party->rotation, 360.0);
    }
    return EVT_RETURN_BLOCK;
}

