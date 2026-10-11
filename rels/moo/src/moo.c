#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "data/mapdata.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];
extern s32 btl_moo_setup_no_tbl[];
extern s32 btlsetup_moo_tbl[];
extern s32 moo_00_init_evt[];
extern s32 moo_01_init_evt[];
extern s32 moo_02_init_evt[];
extern s32 moo_03_init_evt[];
extern s32 moo_04_init_evt[];
extern s32 moo_05_init_evt[];
extern s32 moo_06_init_evt[];
extern s32 moo_07_init_evt[];

void _unresolved(void);
void _epilog(void);
void _prolog(void);

__declspec(section ".data") u64 fd_moo_negone_one_374;
__declspec(section ".data") s32 fd_moo_neg_one_382[1];
__declspec(section ".data") s32 fd_moo___local_PI_383[1];
__declspec(section ".data") s32 fd_moo___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_moo_one_negone_373;
__declspec(section ".data") s32 fd_moo___local_PIO2_384[1];
__declspec(section ".data") s32 fd_moo_one_381[1];
__declspec(section ".data") u64 fd_moo_negone_one_360;
__declspec(section ".data") s32 fd_moo_neg_one_365[1];
__declspec(section ".data") s32 fd_moo___local_PI_366[1];
__declspec(section ".data") s32 fd_moo___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_moo_one_negone_359;
__declspec(section ".data") s32 fd_moo___local_PIO2_367[1];
__declspec(section ".data") s32 fd_moo_one_364[1];

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("moo_00", moo_00_init_evt);
    relSetEvtAddr("moo_01", moo_01_init_evt);
    relSetEvtAddr("moo_02", moo_02_init_evt);
    relSetEvtAddr("moo_03", moo_03_init_evt);
    relSetEvtAddr("moo_04", moo_04_init_evt);
    relSetEvtAddr("moo_05", moo_05_init_evt);
    relSetEvtAddr("moo_06", moo_06_init_evt);
    relSetEvtAddr("moo_07", moo_07_init_evt);
    relSetBtlAddr("moo", btlsetup_moo_tbl, btl_moo_setup_no_tbl);
}

__declspec(section ".data") u64 fd_moo_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_moo_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_moo___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_moo___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_moo_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_moo___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_moo_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_moo_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_moo_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_moo___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_moo___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_moo_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_moo___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_moo_one_364[] = {
    1065353216,
};

void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
void _unresolved(void) {
}
