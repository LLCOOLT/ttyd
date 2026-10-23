#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "data/mapdata.h"
#include "qiz.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];

void _unresolved(void);
void _epilog(void);
void _prolog(void);

__declspec(section ".data") f32 fd_qiz_negone_one_374[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_qiz_neg_one_382;
__declspec(section ".data") f32 fd_qiz___local_PI_383;
__declspec(section ".data") f32 fd_qiz___local_3PIO2_385;
__declspec(section ".data") f32 fd_qiz_one_negone_373[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_qiz___local_PIO2_384;
__declspec(section ".data") f32 fd_qiz_one_381;
__declspec(section ".data") f32 fd_qiz_negone_one_360[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_qiz_neg_one_365;
__declspec(section ".data") f32 fd_qiz___local_PI_366;
__declspec(section ".data") f32 fd_qiz___local_3PIO2_368;
__declspec(section ".data") f32 fd_qiz_one_negone_359[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_qiz___local_PIO2_367;
__declspec(section ".data") f32 fd_qiz_one_364;

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("qiz_00", qiz_00_init_evt);
}

__declspec(section ".data") f32 fd_qiz_negone_one_374[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_qiz_neg_one_382 = -1.0f;

__declspec(section ".data") f32 fd_qiz___local_PI_383 = 3.1415927f;

__declspec(section ".data") f32 fd_qiz___local_3PIO2_385 = 4.712389f;

__declspec(section ".data") f32 fd_qiz_one_negone_373[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_qiz___local_PIO2_384 = 1.5707964f;

__declspec(section ".data") f32 fd_qiz_one_381 = 1.0f;

__declspec(section ".data") f32 fd_qiz_negone_one_360[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_qiz_neg_one_365 = -1.0f;

__declspec(section ".data") f32 fd_qiz___local_PI_366 = 3.1415927f;

__declspec(section ".data") f32 fd_qiz___local_3PIO2_368 = 4.712389f;

__declspec(section ".data") f32 fd_qiz_one_negone_359[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_qiz___local_PIO2_367 = 1.5707964f;

__declspec(section ".data") f32 fd_qiz_one_364 = 1.0f;

void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
void _unresolved(void) {
}
