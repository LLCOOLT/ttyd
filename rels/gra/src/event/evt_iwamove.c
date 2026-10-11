#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "mario/mario.h"
#include "driver/hitdrv.h"
#include "system.h"

typedef struct IwaMoveWork { s32 init; s32 timer; s32 state; EventEntry* event; s32* script; } IwaMoveWork;
IwaMoveWork iwamove;
void partyKeyOn(void);
void partyKeyOff(void);
void statusWinForceOpen(void);
void statusWinForceOff(void);

USER_FUNC(evt_iwamove_main);
USER_FUNC(evt_iwamove_ent);
USER_FUNC(evt_iwamove_init);

__declspec(section ".data") u64 fd_evt_iwamove_negone_one_374;
__declspec(section ".data") s32 fd_evt_iwamove_neg_one_382[1];
__declspec(section ".data") s32 fd_evt_iwamove___local_PI_383[1];
__declspec(section ".data") s32 fd_evt_iwamove___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_evt_iwamove_one_negone_373;
__declspec(section ".data") s32 fd_evt_iwamove___local_PIO2_384[1];
__declspec(section ".data") s32 fd_evt_iwamove_one_381[1];
__declspec(section ".data") u64 fd_evt_iwamove_negone_one_360;
__declspec(section ".data") s32 fd_evt_iwamove_neg_one_365[1];
__declspec(section ".data") s32 fd_evt_iwamove___local_PI_366[1];
__declspec(section ".data") s32 fd_evt_iwamove___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_evt_iwamove_one_negone_359;
__declspec(section ".data") s32 fd_evt_iwamove___local_PIO2_367[1];
__declspec(section ".data") s32 fd_evt_iwamove_one_364[1];
__declspec(section ".data") s32 evt_iwamove_main_evt[4];

USER_FUNC(evt_iwamove_ent) {
    IwaMoveWork* wk = &iwamove;

    wk->script = (s32*)event->args[0];
    wk->state = 0;
    wk->event = evtEntry(evt_iwamove_main_evt, 0, 0);
    wk->event->lwData[0] = (s32)&iwamove;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_iwamove_init) {
    iwamove.init = 0;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_iwamove_main) {
    IwaMoveWork* wk = (IwaMoveWork*)event->lwData[0];
    MarioWork* mario = marioGetPtr();

    if (isFirstCall) {
        return EVT_RETURN_BLOCK;
    }
    switch (wk->state) {
        case 0:
            if (mario->hitobjPush == hitNameToPtr("A_h_iwa")) {
                wk->timer = 80;
                wk->state++;
                marioKeyOff();
                partyKeyOff();
                marioChgPose("M_O_1");
                mario->dispFlags |= 2;
                statusWinForceOpen();
            }
            break;
        case 1:
            if (keyGetStickX(0) > 10) {
                if (wk->timer-- == 0) {
                    wk->state++;
                }
            } else {
                wk->state--;
                mario->dispFlags &= ~2;
                marioChgPose("M_S_1");
                marioKeyOn();
                partyKeyOn();
                statusWinForceOff();
            }
            break;
        case 2:
            if (wk->script != NULL) {
                evtEntry(wk->script, 0, 0);
            }
            statusWinForceOff();
            wk->state++;
            break;
        case 3:
            break;
    }
    return EVT_RETURN_BLOCK;
}

__declspec(section ".data") u64 fd_evt_iwamove_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_evt_iwamove_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_evt_iwamove___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_evt_iwamove___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_evt_iwamove_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_evt_iwamove___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_evt_iwamove_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_evt_iwamove_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_evt_iwamove_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_evt_iwamove___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_evt_iwamove___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_evt_iwamove_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_evt_iwamove___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_evt_iwamove_one_364[] = {
    1065353216,
};

__declspec(section ".data") EVT_BEGIN(evt_iwamove_main_evt)
    CALL(evt_iwamove_main)
    RETURN
EVT_END()

