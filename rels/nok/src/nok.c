#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "data/mapdata.h"
#include "manager/evtmgr_cmd.h"
#include "dolphin/mtx.h"
#include "nok.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];

USER_FUNC(evt_nokonoko_urouro_check_func);
USER_FUNC(evt_npc_add_dirdist);
USER_FUNC(evt_npc_get_loiter_dir);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_reverse_ry);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_sub_get_dir);
USER_FUNC(evt_sub_random);
void _unresolved(void);
void _epilog(void);
void _prolog(void);

__declspec(section ".data") u64 fd_nok_negone_one_374;
__declspec(section ".data") s32 fd_nok_neg_one_382[1];
__declspec(section ".data") s32 fd_nok___local_PI_383[1];
__declspec(section ".data") s32 fd_nok___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_nok_one_negone_373;
__declspec(section ".data") s32 fd_nok___local_PIO2_384[1];
__declspec(section ".data") s32 fd_nok_one_381[1];
__declspec(section ".data") u64 fd_nok_negone_one_360;
__declspec(section ".data") s32 fd_nok_neg_one_365[1];
__declspec(section ".data") s32 fd_nok___local_PI_366[1];
__declspec(section ".data") s32 fd_nok___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_nok_one_negone_359;
__declspec(section ".data") s32 fd_nok___local_PIO2_367[1];
__declspec(section ".data") s32 fd_nok_one_364[1];
__declspec(section ".data") s32 fd_nok__three_localstatic4_sqrtf[2];
__declspec(section ".data") s32 fd_nok__half_localstatic3_sqrtf[2];
s32 nokonoko_urouro_regl[97];

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("nok_00", nok_00_init_evt);
    relSetEvtAddr("nok_01", nok_01_init_evt);
    relSetBtlAddr("nok", btlsetup_nok_tbl, btl_nok_setup_no_tbl);
}

void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}

void _unresolved(void) {
}

USER_FUNC(evt_nokonoko_urouro_check_func) {
    s32* args = event->args;
    s32 xVar = args[0];
    s32 zVar = args[1];
    f32 cx = evtGetFloat(event, args[2]);
    f32 cz = evtGetFloat(event, args[3]);
    f32 range = evtGetFloat(event, args[4]);
    f32 x = evtGetFloat(event, xVar);
    f32 z = evtGetFloat(event, zVar);
    Vec pos;
    Vec center;

    pos = (Vec){x, 0.0f, z};
    center = (Vec){cx, 0.0f, cz};
    if (PSVECDistance(&center, &pos) <= range) {
        return EVT_RETURN_DONE;
    }
    evtSetFloat(event, xVar, cx);
    evtSetFloat(event, zVar, cz);
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_nok_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_nok_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_nok___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_nok___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_nok_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_nok___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_nok_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_nok_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_nok_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_nok___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_nok___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_nok_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_nok___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_nok_one_364[] = {
    1065353216,
};

__declspec(section ".data") s32 fd_nok__three_localstatic4_sqrtf[] = {
    1074266112, 0,
};

__declspec(section ".data") s32 fd_nok__half_localstatic3_sqrtf[] = {
    1071644672, 0,
};

EVT_BEGIN(nokonoko_urouro_regl)
    CALL(evt_npc_get_position, STRING("me"), LW(6), LW(7), LW(8))
    CALL(evt_sub_random, 300, LW(0))
    ADD(LW(0), 300)
    WAIT_MS(LW(0))
    LOOP(0)
        CALL(evt_npc_reverse_ry, STRING("me"))
        CALL(evt_sub_random, 200, LW(0))
        ADD(LW(0), 400)
        WAIT_MS(LW(0))
        CALL(evt_npc_reverse_ry, STRING("me"))
        CALL(evt_sub_random, 200, LW(0))
        ADD(LW(0), 800)
        WAIT_MS(LW(0))
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(120.0f), FLOAT(240.0f))
        CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(50.0f))
        CALL(evt_nokonoko_urouro_check_func, LW(0), LW(2), LW(6), LW(8), FLOAT(70.0f))
        CALL(evt_npc_get_position, STRING("me"), LW(10), LW(11), LW(12))
        CALL(evt_sub_get_dir, LW(10), LW(12), LW(0), LW(2), LW(3))
        CALL(evt_npc_set_ry, STRING("me"), LW(3))
        WAIT_MS(500)
        CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(30.0f), 0)
        WAIT_MS(1000)
    END_LOOP
    RETURN
EVT_END()

