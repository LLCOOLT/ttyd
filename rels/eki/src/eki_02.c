#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "mario/mario.h"
#include "driver/hitdrv.h"
#include "driver/mapdrv.h"
#include "system.h"
#include "dolphin/mtx.h"
#include "evt/evt_bero.h"

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(hit_move);

__declspec(section ".data") u64 fd_eki_02_negone_one_374;
__declspec(section ".data") s32 fd_eki_02_neg_one_382[1];
__declspec(section ".data") s32 fd_eki_02___local_PI_383[1];
__declspec(section ".data") s32 fd_eki_02___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_eki_02_one_negone_373;
__declspec(section ".data") s32 fd_eki_02___local_PIO2_384[1];
__declspec(section ".data") s32 fd_eki_02_one_381[1];
__declspec(section ".data") u64 fd_eki_02_negone_one_360;
__declspec(section ".data") s32 fd_eki_02_neg_one_365[1];
__declspec(section ".data") s32 fd_eki_02___local_PI_366[1];
__declspec(section ".data") s32 fd_eki_02___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_eki_02_one_negone_359;
__declspec(section ".data") s32 fd_eki_02___local_PIO2_367[1];
__declspec(section ".data") s32 fd_eki_02_one_364[1];
static __declspec(section ".data") s32 s_close[12];
static __declspec(section ".data") s32 s_open[12];
static s32 bero_data[30];
static __declspec(section ".data") s32 evt_key[5];
s32 eki_02_init_evt[54];

__declspec(section ".data") u64 fd_eki_02_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_eki_02_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_eki_02___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_eki_02___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_eki_02_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_eki_02___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_eki_02_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_eki_02_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_eki_02_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_eki_02___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_eki_02___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_eki_02_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_eki_02___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_eki_02_one_364[] = {
    1065353216,
};

static __declspec(section ".data") EVT_BEGIN(s_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(s_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_data[] = {
    (s32)"s_bero", 65539, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"eki_01", (s32)"n_bero", 327685, (s32)s_close, (s32)s_open, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

double sin(double x);
double cos(double x);

USER_FUNC(hit_move) {
    MarioWork* mario = marioGetPtr();
    HitEntry* hit = mario->hitobjStandOn;
    Mtx rot;
    Vec dir = {0.0f, 0.0f, -1.0f};
    Vec pos;
    f32 delta;
    f32 angle;
    f32 dist;
    f32 theta;

    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
    }
    if (hit == NULL) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
        return EVT_RETURN_BLOCK;
    }
    if (!(hit->flags & 0x30)) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
        return EVT_RETURN_BLOCK;
    }
    mtxGetRotationElement(hit->worldMtx, rot, 'x', 'z');
    PSMTXMultVec(rot, &dir, &dir);
    angle = angleABf(0.0f, 0.0f, dir.x, dir.z);
    delta = angle - event->userdataf[1];
    if (event->userdata[0] == 0) {
        event->userdata[0] = 1;
        event->userdataf[1] = angle;
        return EVT_RETURN_BLOCK;
    }
    hitObjGetPos(hit->joint->name, &pos);
    dist = distABf(mario->position.x, mario->position.z, pos.x, pos.z);
    theta = angleABf(pos.x, pos.z, mario->position.x, mario->position.z);
    theta = 6.2831855f * (theta + delta) / 360.0f;
    mario->unk174.x = pos.x + dist * (f32)sin(theta) - mario->position.x;
    mario->unk174.z = pos.z - dist * (f32)cos(theta) - mario->position.z;
    event->userdataf[1] = angle;
    return EVT_RETURN_BLOCK;
}

static __declspec(section ".data") EVT_BEGIN(evt_key)
    SET_VALUE(GSW(0), 314)
    RETURN
EVT_END()

EVT_BEGIN(eki_02_init_evt)
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG6_EKI3"))
#ifdef VERSION_G8ME01
    CALL(evt_map_playanim, STRING("anm_sikake_1"), 1, 1)
    CALL(evt_map_playanim, STRING("anm_sikake_2"), 1, 1)
#else
    CALL(evt_map_playanim, STRING("anm_sikake_1"), 1, 0)
    CALL(evt_map_playanim, STRING("anm_sikake_2"), 1, 0)
#endif
    IF_INT_LESS(GSW(0), 314)
        CALL(evt_item_entry, STRING("key"), 25, 525, 220, 29, 16, -1, PTR(evt_key))
    END_IF
    BEGIN_INLINE_EVENT
        CALL(hit_move)
    END_INLINE_EVENT
    CALL(evt_item_entry, STRING("item"), 125, 540, 140, -40, 16, GSWF(5653), 0)
    RETURN
EVT_END()

