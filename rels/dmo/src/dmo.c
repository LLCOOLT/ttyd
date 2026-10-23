#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "data/mapdata.h"
#include "dmo.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];
void demo_exit(void);

void _unresolved(void);
void _epilog(void);
void _prolog(void);

__declspec(section ".data") u64 fd_dmo_negone_one_374;
__declspec(section ".data") s32 fd_dmo_neg_one_382[1];
__declspec(section ".data") s32 fd_dmo___local_PI_383[1];
__declspec(section ".data") s32 fd_dmo___local_3PIO2_385[2];
__declspec(section ".data") u64 fd_dmo_one_negone_373;
__declspec(section ".data") s32 fd_dmo___local_PIO2_384[1];
__declspec(section ".data") s32 fd_dmo_one_381[1];
__declspec(section ".data") u64 fd_dmo_negone_one_360;
__declspec(section ".data") s32 fd_dmo_neg_one_365[1];
__declspec(section ".data") s32 fd_dmo___local_PI_366[1];
__declspec(section ".data") s32 fd_dmo___local_3PIO2_368[2];
__declspec(section ".data") u64 fd_dmo_one_negone_359;
__declspec(section ".data") s32 fd_dmo___local_PIO2_367[1];
__declspec(section ".data") s32 fd_dmo_one_364[1];

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("dmo_00", dmo_00_init_evt);
}

__declspec(section ".data") u64 fd_dmo_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_dmo_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_dmo___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_dmo___local_3PIO2_385[] = {
    1083624420, 0,
};

__declspec(section ".data") u64 fd_dmo_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_dmo___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_dmo_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_dmo_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_dmo_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_dmo___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_dmo___local_3PIO2_368[] = {
    1083624420, 0,
};

__declspec(section ".data") u64 fd_dmo_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_dmo___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_dmo_one_364[] = {
    1065353216,
};

void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
    demo_exit();
}
void _unresolved(void) {
}
