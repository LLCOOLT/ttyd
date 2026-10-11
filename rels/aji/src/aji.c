#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "mario/mario.h"
#include "party.h"
#include "driver/swdrv.h"
#include "mario/mario_party.h"
#include "data/mapdata.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];
extern s32 aji_00_init_evt[];
extern s32 aji_01_init_evt[];
extern s32 aji_02_init_evt[];
extern s32 aji_03_init_evt[];
extern s32 aji_04_init_evt[];
extern s32 aji_05_init_evt[];
extern s32 aji_06_init_evt[];
extern s32 aji_07_init_evt[];
extern s32 aji_08_init_evt[];
extern s32 aji_09_init_evt[];
extern s32 aji_10_init_evt[];
extern s32 aji_11_init_evt[];
extern s32 aji_12_init_evt[];
extern s32 aji_13_init_evt[];
extern s32 aji_14_init_evt[];
extern s32 aji_15_init_evt[];
extern s32 aji_16_init_evt[];
extern s32 aji_17_init_evt[];
extern s32 aji_18_init_evt[];
extern s32 aji_19_init_evt[];
extern s32 btl_aji_setup_no_tbl[];
extern s32 btlsetup_aji_tbl[];
void partySetFamicomMode(PartyEntry* party, s32 mode);

void _unresolved(void);
void _epilog(void);
void _prolog(void);

__declspec(section ".data") u64 fd_aji_negone_one_374;
__declspec(section ".data") s32 fd_aji_neg_one_382[1];
__declspec(section ".data") s32 fd_aji___local_PI_383[1];
__declspec(section ".data") s32 fd_aji___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_aji_one_negone_373;
__declspec(section ".data") s32 fd_aji___local_PIO2_384[1];
__declspec(section ".data") s32 fd_aji_one_381[1];
__declspec(section ".data") u64 fd_aji_negone_one_360;
__declspec(section ".data") s32 fd_aji_neg_one_365[1];
__declspec(section ".data") s32 fd_aji___local_PI_366[1];
__declspec(section ".data") s32 fd_aji___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_aji_one_negone_359;
__declspec(section ".data") s32 fd_aji___local_PIO2_367[1];
__declspec(section ".data") s32 fd_aji_one_364[1];

void _unresolved(void) {
}

void _epilog(void) {
    voidfunctionptr* dtor;

    if (swGet(0x1079)) {
        marioSetFamicomMode(0);
        partySetFamicomMode(partyGetPtr(marioGetPartyId()), 0);
        swClear(0x1079);
    }
    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("aji_00", aji_00_init_evt);
    relSetEvtAddr("aji_01", aji_01_init_evt);
    relSetEvtAddr("aji_02", aji_02_init_evt);
    relSetEvtAddr("aji_03", aji_03_init_evt);
    relSetEvtAddr("aji_04", aji_04_init_evt);
    relSetEvtAddr("aji_05", aji_05_init_evt);
    relSetEvtAddr("aji_06", aji_06_init_evt);
    relSetEvtAddr("aji_07", aji_07_init_evt);
    relSetEvtAddr("aji_08", aji_08_init_evt);
    relSetEvtAddr("aji_09", aji_09_init_evt);
    relSetEvtAddr("aji_10", aji_10_init_evt);
    relSetEvtAddr("aji_11", aji_11_init_evt);
    relSetEvtAddr("aji_12", aji_12_init_evt);
    relSetEvtAddr("aji_13", aji_13_init_evt);
    relSetEvtAddr("aji_14", aji_14_init_evt);
    relSetEvtAddr("aji_15", aji_15_init_evt);
    relSetEvtAddr("aji_16", aji_16_init_evt);
    relSetEvtAddr("aji_17", aji_17_init_evt);
    relSetEvtAddr("aji_18", aji_18_init_evt);
    relSetEvtAddr("aji_19", aji_19_init_evt);
    relSetBtlAddr("aji", btlsetup_aji_tbl, btl_aji_setup_no_tbl);
}

__declspec(section ".data") u64 fd_aji_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_aji_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_one_364[] = {
    1065353216,
};

