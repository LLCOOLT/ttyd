#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "data/mapdata.h"
#include "dig.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];
void dig_thpInit(void);
void dig_thpStop(void);

void _unresolved(void);
void _epilog(void);
void _prolog(void);

__declspec(section ".data") f32 fd_dig_negone_one_374[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_dig_neg_one_382;
__declspec(section ".data") f32 fd_dig___local_PI_383;
__declspec(section ".data") f32 fd_dig___local_3PIO2_385;
__declspec(section ".data") f32 fd_dig_one_negone_373[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_dig___local_PIO2_384;
__declspec(section ".data") f32 fd_dig_one_381;
__declspec(section ".data") f32 fd_dig_negone_one_360[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_dig_neg_one_365;
__declspec(section ".data") f32 fd_dig___local_PI_366;
__declspec(section ".data") f32 fd_dig___local_3PIO2_368;
__declspec(section ".data") f32 fd_dig_one_negone_359[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_dig___local_PIO2_367;
__declspec(section ".data") f32 fd_dig_one_364;
__declspec(section ".data") f64 fd_dig__three_localstatic4_sqrtf;
__declspec(section ".data") f64 fd_dig__half_localstatic3_sqrtf;

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("dig_00\0", dig_00_init_evt);
    dig_thpInit();
}

__declspec(section ".data") f32 fd_dig_negone_one_374[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_dig_neg_one_382 = -1.0f;

__declspec(section ".data") f32 fd_dig___local_PI_383 = 3.1415927f;

__declspec(section ".data") f32 fd_dig___local_3PIO2_385 = 4.712389f;

__declspec(section ".data") f32 fd_dig_one_negone_373[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_dig___local_PIO2_384 = 1.5707964f;

__declspec(section ".data") f32 fd_dig_one_381 = 1.0f;

__declspec(section ".data") f32 fd_dig_negone_one_360[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_dig_neg_one_365 = -1.0f;

__declspec(section ".data") f32 fd_dig___local_PI_366 = 3.1415927f;

__declspec(section ".data") f32 fd_dig___local_3PIO2_368 = 4.712389f;

__declspec(section ".data") f32 fd_dig_one_negone_359[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_dig___local_PIO2_367 = 1.5707964f;

__declspec(section ".data") f32 fd_dig_one_364 = 1.0f;

__declspec(section ".data") f64 fd_dig__three_localstatic4_sqrtf = 3.0;

__declspec(section ".data") f64 fd_dig__half_localstatic3_sqrtf = 0.5;

void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
    dig_thpStop();
}
void _unresolved(void) {
}
