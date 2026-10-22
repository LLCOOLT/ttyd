#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "data/mapdata.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];
extern s32 hom_00_init_evt[];
extern s32 hom_10_init_evt_13_data_3954[];
extern s32 hom_11_init_evt[];
extern s32 hom_12_init_evt[];

void _unresolved(void);
void _epilog(void);
void _prolog(void);

__declspec(section ".data") u64 fd_hom_negone_one_374;
__declspec(section ".data") s32 fd_hom_neg_one_382[1];
__declspec(section ".data") s32 fd_hom___local_PI_383[1];
__declspec(section ".data") s32 fd_hom___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_hom_one_negone_373;
__declspec(section ".data") s32 fd_hom___local_PIO2_384[1];
__declspec(section ".data") s32 fd_hom_one_381[1];
__declspec(section ".data") u64 fd_hom_negone_one_360;
__declspec(section ".data") s32 fd_hom_neg_one_365[1];
__declspec(section ".data") s32 fd_hom___local_PI_366[1];
__declspec(section ".data") s32 fd_hom___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_hom_one_negone_359;
__declspec(section ".data") s32 fd_hom___local_PIO2_367[1];
__declspec(section ".data") s32 fd_hom_one_364[1];
__declspec(section ".data") s32 fd_hom__three_localstatic4_sqrtf[2];
__declspec(section ".data") s32 fd_hom__half_localstatic3_sqrtf[2];

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("hom_00", hom_00_init_evt);
    relSetEvtAddr("hom_10", hom_10_init_evt_13_data_3954);
    relSetEvtAddr("hom_11", hom_11_init_evt);
    relSetEvtAddr("hom_12\0", hom_12_init_evt);
}

__declspec(section ".data") u64 fd_hom_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hom_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hom___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hom___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hom_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hom___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hom_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_hom_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hom_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hom___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hom___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hom_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hom___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hom_one_364[] = {
    1065353216,
};

__declspec(section ".data") s32 fd_hom__three_localstatic4_sqrtf[] = {
    1074266112, 0,
};

__declspec(section ".data") s32 fd_hom__half_localstatic3_sqrtf[] = {
    1071644672, 0,
};

void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
void _unresolved(void) {
}
