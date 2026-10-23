#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "data/mapdata.h"
#include "memory.h"
#include "string.h"
#include "data/party_data.h"
#include "jin.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];
static void* pose_buf;

void _unresolved(void);
void _epilog(void);
void _prolog(void);
USER_FUNC(evt_jin_vivian_pose_set);

__declspec(section ".data") u64 fd_jin_negone_one_374;
__declspec(section ".data") s32 fd_jin_neg_one_382[1];
__declspec(section ".data") s32 fd_jin___local_PI_383[1];
__declspec(section ".data") s32 fd_jin___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_jin_one_negone_373;
__declspec(section ".data") s32 fd_jin___local_PIO2_384[1];
__declspec(section ".data") s32 fd_jin_one_381[1];
__declspec(section ".data") u64 fd_jin_negone_one_360;
__declspec(section ".data") s32 fd_jin_neg_one_365[1];
__declspec(section ".data") s32 fd_jin___local_PI_366[1];
__declspec(section ".data") s32 fd_jin___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_jin_one_negone_359;
__declspec(section ".data") s32 fd_jin___local_PIO2_367[1];
__declspec(section ".data") s32 fd_jin_one_364[1];
__declspec(section ".data") s32 fd_jin__three_localstatic4_sqrtf[2];
__declspec(section ".data") s32 fd_jin__half_localstatic3_sqrtf[2];

USER_FUNC(evt_jin_vivian_pose_set) {
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
    relSetEvtAddr("jin_00", jin_00_init_evt);
    relSetEvtAddr("jin_01", jin_01_init_evt);
    relSetEvtAddr("jin_02", jin_02_init_evt);
    relSetEvtAddr("jin_03", jin_03_init_evt);
    relSetEvtAddr("jin_04", jin_04_init_evt);
    relSetEvtAddr("jin_05", jin_05_init_evt);
    relSetEvtAddr("jin_06", jin_06_init_evt);
    relSetEvtAddr("jin_07", jin_07_init_evt);
    relSetEvtAddr("jin_08", jin_08_init_evt);
    relSetEvtAddr("jin_09", jin_09_init_evt);
    relSetEvtAddr("jin_10", jin_10_init_evt);
    relSetEvtAddr("jin_11", jin_11_init_evt);
    relSetBtlAddr("jin", btlsetup_jin_tbl, btl_jin_setup_no_tbl);
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

__declspec(section ".data") u64 fd_jin_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_jin_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_one_364[] = {
    1065353216,
};

__declspec(section ".data") s32 fd_jin__three_localstatic4_sqrtf[] = {
    1074266112, 0,
};

__declspec(section ".data") s32 fd_jin__half_localstatic3_sqrtf[] = {
    1071644672, 0,
};

