#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "data/mapdata.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];
extern s32 btl_hei_setup_no_tbl[];
extern s32 btlsetup_hei_tbl[];
extern s32 hei_00_init_evt[];
extern s32 hei_01_init_evt[];
extern s32 hei_02_init_evt[];
extern s32 hei_03_init_evt[];
extern s32 hei_04_init_evt[];
extern s32 hei_05_init_evt[];
extern s32 hei_06_init_evt[];
extern s32 hei_07_init_evt[];
extern s32 hei_08_init_evt[];
extern s32 hei_09_init_evt[];
extern s32 hei_10_init_evt[];
extern s32 hei_11_init_evt[];
extern s32 hei_12_init_evt[];
extern s32 hei_13_init_evt[];
extern s32 hei_bt00_init_evt[];

void _unresolved(void);
void _epilog(void);
void _prolog(void);

__declspec(section ".data") u64 fd_hei_negone_one_374;
__declspec(section ".data") s32 fd_hei_neg_one_382[1];
__declspec(section ".data") s32 fd_hei___local_PI_383[1];
__declspec(section ".data") s32 fd_hei___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_hei_one_negone_373;
__declspec(section ".data") s32 fd_hei___local_PIO2_384[1];
__declspec(section ".data") s32 fd_hei_one_381[1];
__declspec(section ".data") u64 fd_hei_negone_one_360;
__declspec(section ".data") s32 fd_hei_neg_one_365[1];
__declspec(section ".data") s32 fd_hei___local_PI_366[1];
__declspec(section ".data") s32 fd_hei___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_hei_one_negone_359;
__declspec(section ".data") s32 fd_hei___local_PIO2_367[1];
__declspec(section ".data") s32 fd_hei_one_364[1];
__declspec(section ".data") s32 fd_hei__three_localstatic4_sqrtf[2];
__declspec(section ".data") s32 fd_hei__half_localstatic3_sqrtf[2];

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("hei_00", hei_00_init_evt);
    relSetEvtAddr("hei_01", hei_01_init_evt);
    relSetEvtAddr("hei_02", hei_02_init_evt);
    relSetEvtAddr("hei_03", hei_03_init_evt);
    relSetEvtAddr("hei_04", hei_04_init_evt);
    relSetEvtAddr("hei_05", hei_05_init_evt);
    relSetEvtAddr("hei_06", hei_06_init_evt);
    relSetEvtAddr("hei_07", hei_07_init_evt);
    relSetEvtAddr("hei_08", hei_08_init_evt);
    relSetEvtAddr("hei_09", hei_09_init_evt);
    relSetEvtAddr("hei_10", hei_10_init_evt);
    relSetEvtAddr("hei_11", hei_11_init_evt);
    relSetEvtAddr("hei_12", hei_12_init_evt);
    relSetEvtAddr("hei_13", hei_13_init_evt);
    relSetEvtAddr("hei_bt00", hei_bt00_init_evt);
    relSetBtlAddr("hei", btlsetup_hei_tbl, btl_hei_setup_no_tbl);
}

__declspec(section ".data") u64 fd_hei_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hei_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hei___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hei___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hei_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hei___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hei_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_hei_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hei_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hei___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hei___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hei_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hei___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hei_one_364[] = {
    1065353216,
};

__declspec(section ".data") s32 fd_hei__three_localstatic4_sqrtf[] = {
    1074266112, 0,
};

__declspec(section ".data") s32 fd_hei__half_localstatic3_sqrtf[] = {
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
