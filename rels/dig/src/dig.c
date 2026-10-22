#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "data/mapdata.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];
extern s32 dig_00_init_evt[];
void dig_thpInit(void);
void dig_thpStop(void);

void _unresolved(void);
void _epilog(void);
void _prolog(void);

__declspec(section ".data") u64 fd_dig_negone_one_374;
__declspec(section ".data") s32 fd_dig_neg_one_382[1];
__declspec(section ".data") s32 fd_dig___local_PI_383[1];
__declspec(section ".data") s32 fd_dig___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_dig_one_negone_373;
__declspec(section ".data") s32 fd_dig___local_PIO2_384[1];
__declspec(section ".data") s32 fd_dig_one_381[1];
__declspec(section ".data") u64 fd_dig_negone_one_360;
__declspec(section ".data") s32 fd_dig_neg_one_365[1];
__declspec(section ".data") s32 fd_dig___local_PI_366[1];
__declspec(section ".data") s32 fd_dig___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_dig_one_negone_359;
__declspec(section ".data") s32 fd_dig___local_PIO2_367[1];
__declspec(section ".data") s32 fd_dig_one_364[1];
__declspec(section ".data") s32 fd_dig__three_localstatic4_sqrtf[2];
__declspec(section ".data") s32 fd_dig__half_localstatic3_sqrtf[2];

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("dig_00\0", dig_00_init_evt);
    dig_thpInit();
}

__declspec(section ".data") u64 fd_dig_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_dig_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_dig___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_dig___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_dig_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_dig___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_dig_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_dig_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_dig_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_dig___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_dig___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_dig_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_dig___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_dig_one_364[] = {
    1065353216,
};

__declspec(section ".data") s32 fd_dig__three_localstatic4_sqrtf[] = {
    1074266112, 0,
};

__declspec(section ".data") s32 fd_dig__half_localstatic3_sqrtf[] = {
    1071644672, 0,
};

void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
    dig_thpStop();
}
void _unresolved(void) {
}
