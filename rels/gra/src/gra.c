#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "data/mapdata.h"
#include "memory.h"
#include "string.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];
extern s32 btl_gra_setup_no_tbl[];
extern s32 btlsetup_gra_tbl[];
extern s32 gra_00_init_evt[];
extern s32 gra_01_init_evt[];
extern s32 gra_02_init_evt[];
extern s32 gra_03_init_evt[];
extern s32 gra_04_init_evt[];
extern s32 gra_05_init_evt[];
extern s32 gra_06_init_evt[];
extern char* partyPoseTbl[20][15];
static void* pose_buf;

void _unresolved(void);
void _epilog(void);
void _prolog(void);
USER_FUNC(evt_gra_vivian_pose_set);

__declspec(section ".data") u64 fd_gra_negone_one_374;
__declspec(section ".data") s32 fd_gra_neg_one_382[1];
__declspec(section ".data") s32 fd_gra___local_PI_383[1];
__declspec(section ".data") s32 fd_gra___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gra_one_negone_373;
__declspec(section ".data") s32 fd_gra___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gra_one_381[1];
__declspec(section ".data") u64 fd_gra_negone_one_360;
__declspec(section ".data") s32 fd_gra_neg_one_365[1];
__declspec(section ".data") s32 fd_gra___local_PI_366[1];
__declspec(section ".data") s32 fd_gra___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gra_one_negone_359;
__declspec(section ".data") s32 fd_gra___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gra_one_364[1];

USER_FUNC(evt_gra_vivian_pose_set) {
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
    relSetEvtAddr("gra_00", gra_00_init_evt);
    relSetEvtAddr("gra_01", gra_01_init_evt);
    relSetEvtAddr("gra_02", gra_02_init_evt);
    relSetEvtAddr("gra_03", gra_03_init_evt);
    relSetEvtAddr("gra_04", gra_04_init_evt);
    relSetEvtAddr("gra_05", gra_05_init_evt);
    relSetEvtAddr("gra_06", gra_06_init_evt);
    relSetBtlAddr("gra", btlsetup_gra_tbl, btl_gra_setup_no_tbl);
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

__declspec(section ".data") u64 fd_gra_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gra_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gra___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gra___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gra_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gra___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gra_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gra_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gra_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gra___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gra___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gra_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gra___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gra_one_364[] = {
    1065353216,
};

