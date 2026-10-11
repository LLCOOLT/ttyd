#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "data/mapdata.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];
extern s32 btl_gon_setup_no_tbl[];
extern s32 btlsetup_gon_tbl[];
extern s32 gon_00_init_evt[];
extern s32 gon_01_init_evt[];
extern s32 gon_02_init_evt[];
extern s32 gon_03_init_evt[];
extern s32 gon_04_init_evt[];
extern s32 gon_05_init_evt[];
extern s32 gon_06_init_evt[];
extern s32 gon_07_init_evt[];
extern s32 gon_08_init_evt[];
extern s32 gon_09_init_evt[];
extern s32 gon_10_init_evt[];
extern s32 gon_11_init_evt[];
extern s32 gon_12_init_evt[];
extern s32 gon_13_init_evt[];
extern s32 gon_bt00_init_evt[];

void _prolog(void);
void _epilog(void);
void _unresolved(void);

__declspec(section ".data") u64 fd_gon_negone_one_374;
__declspec(section ".data") s32 fd_gon_neg_one_382[1];
__declspec(section ".data") s32 fd_gon___local_PI_383[1];
__declspec(section ".data") s32 fd_gon___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gon_one_negone_373;
__declspec(section ".data") s32 fd_gon___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gon_one_381[1];
__declspec(section ".data") u64 fd_gon_negone_one_360;
__declspec(section ".data") s32 fd_gon_neg_one_365[1];
__declspec(section ".data") s32 fd_gon___local_PI_366[1];
__declspec(section ".data") s32 fd_gon___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gon_one_negone_359;
__declspec(section ".data") s32 fd_gon___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gon_one_364[1];
__declspec(section ".data") s32 fd_gon__three_localstatic4_sqrtf[2];
__declspec(section ".data") s32 fd_gon__half_localstatic3_sqrtf[2];

void _unresolved(void) {
}

void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("gon_00", gon_00_init_evt);
    relSetEvtAddr("gon_01", gon_01_init_evt);
    relSetEvtAddr("gon_02", gon_02_init_evt);
    relSetEvtAddr("gon_03", gon_03_init_evt);
    relSetEvtAddr("gon_04", gon_04_init_evt);
    relSetEvtAddr("gon_05", gon_05_init_evt);
    relSetEvtAddr("gon_06", gon_06_init_evt);
    relSetEvtAddr("gon_07", gon_07_init_evt);
    relSetEvtAddr("gon_08", gon_08_init_evt);
    relSetEvtAddr("gon_09", gon_09_init_evt);
    relSetEvtAddr("gon_10", gon_10_init_evt);
    relSetEvtAddr("gon_11", gon_11_init_evt);
    relSetEvtAddr("gon_12", gon_12_init_evt);
    relSetEvtAddr("gon_13", gon_13_init_evt);
    relSetEvtAddr("gon_bt00", gon_bt00_init_evt);
    relSetBtlAddr("gon", btlsetup_gon_tbl, btl_gon_setup_no_tbl);
}

__declspec(section ".data") u64 fd_gon_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gon_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gon___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gon___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gon_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gon___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gon_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gon_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gon_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gon___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gon___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gon_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gon___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gon_one_364[] = {
    1065353216,
};

__declspec(section ".data") s32 fd_gon__three_localstatic4_sqrtf[] = {
    1074266112, 0,
};

__declspec(section ".data") s32 fd_gon__half_localstatic3_sqrtf[] = {
    1071644672, 0,
};

