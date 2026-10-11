#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "data/mapdata.h"
#include "memory.h"
#include "string.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];
extern s32 usu_00_init_evt[];
extern s32 usu_01_init_evt[];
extern char* partyPoseTbl[20][15];
static void* pose_buf;

void _unresolved(void);
void _epilog(void);
void _prolog(void);
USER_FUNC(evt_usu_vivian_pose_set);

__declspec(section ".data") u64 fd_usu_negone_one_374;
__declspec(section ".data") s32 fd_usu_neg_one_382[1];
__declspec(section ".data") s32 fd_usu___local_PI_383[1];
__declspec(section ".data") s32 fd_usu___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_usu_one_negone_373;
__declspec(section ".data") s32 fd_usu___local_PIO2_384[1];
__declspec(section ".data") s32 fd_usu_one_381[1];
__declspec(section ".data") u64 fd_usu_negone_one_360;
__declspec(section ".data") s32 fd_usu_neg_one_365[1];
__declspec(section ".data") s32 fd_usu___local_PI_366[1];
__declspec(section ".data") s32 fd_usu___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_usu_one_negone_359;
__declspec(section ".data") s32 fd_usu___local_PIO2_367[1];
__declspec(section ".data") s32 fd_usu_one_364[1];
__declspec(section ".data") s32 fd_usu__three_localstatic4_sqrtf[2];
__declspec(section ".data") s32 fd_usu__half_localstatic3_sqrtf[2];

USER_FUNC(evt_usu_vivian_pose_set) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    partyPoseTbl[6][index] = (char*)evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("usu_00", usu_00_init_evt);
    relSetEvtAddr("usu_01", usu_01_init_evt);
    pose_buf = _mapAlloc(sizeof(partyPoseTbl[6]));
    memcpy(pose_buf, partyPoseTbl[6], sizeof(partyPoseTbl[6]));
}

void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
    memcpy(partyPoseTbl[6], pose_buf, sizeof(partyPoseTbl[6]));
    _mapFree(pose_buf);
}

void _unresolved(void) {
}

__declspec(section ".data") u64 fd_usu_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_usu_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_usu___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_usu___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_usu_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_usu___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_usu_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_usu_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_usu_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_usu___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_usu___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_usu_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_usu___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_usu_one_364[] = {
    1065353216,
};

__declspec(section ".data") s32 fd_usu__three_localstatic4_sqrtf[] = {
    1074266112, 0,
};

__declspec(section ".data") s32 fd_usu__half_localstatic3_sqrtf[] = {
    1071644672, 0,
};

