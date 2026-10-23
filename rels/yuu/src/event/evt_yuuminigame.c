#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "manager/evtmgr_cmd.h"
#include "memory.h"
#include "driver/camdrv.h"
#include "string.h"
#include "driver/dispdrv.h"
#include "yuu.h"

static s32 dataadr[32];
s32 stackt[4];
s32 stackp;
void* effMiniGameEntry(s32 type, f32 x, f32 y, f32 z);
typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
s32 yuuminigame_init_1hikoki(EventEntry* event, BOOL isFirstCall);
s32 yuuminigame_main_1hikoki(EventEntry* event, BOOL isFirstCall);
void yuuminigame_disp_1hikoki(CameraId camera, void* param);
s32 yuuminigame_init_2fune(EventEntry* event, BOOL isFirstCall);
s32 yuuminigame_main_2fune(EventEntry* event, BOOL isFirstCall);
void yuuminigame_disp_2fune(CameraId camera, void* param);
s32 yuuminigame_init_3roll(EventEntry* event, BOOL isFirstCall);
s32 yuuminigame_main_3roll(EventEntry* event, BOOL isFirstCall);
void yuuminigame_disp_3roll(CameraId camera, void* param);
s32 yuuminigame_init_4slit(EventEntry* event, BOOL isFirstCall);
s32 yuuminigame_main_4slit(EventEntry* event, BOOL isFirstCall);
void yuuminigame_disp_4slit(CameraId camera, void* param);
void evt_yuuminigame_disp_func(CameraId camera, void* param);

USER_FUNC(evt_yuuminigame_main_func);
USER_FUNC(yuu_atai_init);
USER_FUNC(yuu_atai_pop);
USER_FUNC(yuu_atai_push);
USER_FUNC(eff_call_minigame);
USER_FUNC(yuuminigame_set_dataadr);
USER_FUNC(yuuminigame_get_dataadr);
USER_FUNC(evt_yuuminigame_free);
USER_FUNC(evt_yuuminigame_alloc);
void evt_yuuminigame_disp_func(CameraId camera, void* param);

__declspec(section ".data") f32 fd_evt_yuuminigame_negone_one_374[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_evt_yuuminigame_neg_one_382;
__declspec(section ".data") f32 fd_evt_yuuminigame___local_PI_383;
__declspec(section ".data") f32 fd_evt_yuuminigame___local_3PIO2_385;
__declspec(section ".data") f32 fd_evt_yuuminigame_one_negone_373[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_evt_yuuminigame___local_PIO2_384;
__declspec(section ".data") f32 fd_evt_yuuminigame_one_381;
__declspec(section ".data") f32 fd_evt_yuuminigame_negone_one_360[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_evt_yuuminigame_neg_one_365;
__declspec(section ".data") f32 fd_evt_yuuminigame___local_PI_366;
__declspec(section ".data") f32 fd_evt_yuuminigame___local_3PIO2_368;
__declspec(section ".data") f32 fd_evt_yuuminigame_one_negone_359[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_evt_yuuminigame___local_PIO2_367;
__declspec(section ".data") f32 fd_evt_yuuminigame_one_364;
static __declspec(section ".data") s32 main_evt[4];

USER_FUNC(yuu_atai_init) {
    stackp = 0;
    return EVT_RETURN_DONE;
}

USER_FUNC(yuu_atai_pop) {
    s32* args = event->args;

    if (stackp > 0) {
        stackp--;
        evtSetValue(event, args[0], stackt[stackp]);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(yuu_atai_push) {
    s32* args = event->args;

    if (stackp < 4) {
        stackt[stackp] = evtGetValue(event, args[0]);
        stackp++;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(eff_call_minigame) {
    s32* args = event->args;
    s32 type = evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);

    effMiniGameEntry(type, x, y, z);
    return EVT_RETURN_DONE;
}

USER_FUNC(yuuminigame_set_dataadr) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    if (index < 32) {
        dataadr[index] = evtGetValue(event, args[1]);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(yuuminigame_get_dataadr) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    if (index >= 32) {
        evtSetValue(event, args[1], 0);
    } else {
        evtSetValue(event, args[1], dataadr[index]);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_yuuminigame_free) {
    s32* args = event->args;
    MiniGameWork* wp = (MiniGameWork*)evtGetValue(event, args[0]);

    if (wp == NULL) {
        return EVT_RETURN_DONE;
    }
    if (isFirstCall) {
        wp->flags |= 1;
    }
    if (!(wp->flags & 2)) {
        return EVT_RETURN_BLOCK;
    }
    switch (wp->type) {
        case 3:
            yuunpc_yuuminigame4_ptr = NULL;
            break;
    }
    if (wp->data != NULL) {
        _mapFree(wp->data);
    }
    _mapFree(wp);
    evtSetValue(event, args[0], 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_yuuminigame_alloc) {
    s32* args = event->args;
    MiniGameWork* wp = _mapAlloc(sizeof(MiniGameWork));

    memset(wp, 0, sizeof(MiniGameWork));
    evtSetValue(event, args[0], (s32)wp);
    wp->type = evtGetValue(event, args[1]);
    wp->event = evtEntry(main_evt, 0, 0);
    wp->event->lwData[0] = (s32)wp;
    wp->subEvent = NULL;
    switch (wp->type) {
        case 0:
            wp->init = yuuminigame_init_1hikoki;
            wp->main = yuuminigame_main_1hikoki;
            wp->disp = yuuminigame_disp_1hikoki;
            wp->data = _mapAlloc(0x18);
            memset(wp->data, 0, 0x18);
            break;
        case 1:
            wp->init = yuuminigame_init_2fune;
            wp->main = yuuminigame_main_2fune;
            wp->disp = yuuminigame_disp_2fune;
            wp->data = _mapAlloc(0x3C);
            memset(wp->data, 0, 0x3C);
            break;
        case 2:
            wp->init = yuuminigame_init_3roll;
            wp->main = yuuminigame_main_3roll;
            wp->disp = yuuminigame_disp_3roll;
            wp->data = _mapAlloc(0x2C);
            memset(wp->data, 0, 0x2C);
            break;
        case 3:
            wp->init = yuuminigame_init_4slit;
            wp->main = yuuminigame_main_4slit;
            wp->disp = yuuminigame_disp_4slit;
            wp->data = _mapAlloc(0x28);
            memset(wp->data, 0, 0x28);
            yuunpc_yuuminigame4_ptr = wp;
            break;
    }
    wp->init(event, isFirstCall);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_yuuminigame_main_func) {
    MiniGameWork* wp = (MiniGameWork*)event->lwData[0];

    if (wp->flags & 1) {
        wp->flags |= 2;
        return EVT_RETURN_DONE;
    }
    if (wp->subEvent != NULL) {
        if (evtCheckID(wp->subEvent->eventId)) {
            goto disp;
        }
        wp->subEvent = NULL;
    }
    wp->main(event, isFirstCall);
disp:
    dispEntry(CAMERA_2D, 1000.0f, 0, evt_yuuminigame_disp_func, wp);
    return EVT_RETURN_BLOCK;
}

void evt_yuuminigame_disp_func(CameraId camera, void* param) {
    ((MiniGameWork*)param)->disp(camera, param);
}

__declspec(section ".data") f32 fd_evt_yuuminigame_negone_one_374[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_evt_yuuminigame_neg_one_382 = -1.0f;

__declspec(section ".data") f32 fd_evt_yuuminigame___local_PI_383 = 3.1415927f;

__declspec(section ".data") f32 fd_evt_yuuminigame___local_3PIO2_385 = 4.712389f;

__declspec(section ".data") f32 fd_evt_yuuminigame_one_negone_373[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_evt_yuuminigame___local_PIO2_384 = 1.5707964f;

__declspec(section ".data") f32 fd_evt_yuuminigame_one_381 = 1.0f;

__declspec(section ".data") f32 fd_evt_yuuminigame_negone_one_360[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_evt_yuuminigame_neg_one_365 = -1.0f;

__declspec(section ".data") f32 fd_evt_yuuminigame___local_PI_366 = 3.1415927f;

__declspec(section ".data") f32 fd_evt_yuuminigame___local_3PIO2_368 = 4.712389f;

__declspec(section ".data") f32 fd_evt_yuuminigame_one_negone_359[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_evt_yuuminigame___local_PIO2_367 = 1.5707964f;

__declspec(section ".data") f32 fd_evt_yuuminigame_one_364 = 1.0f;

static __declspec(section ".data") EVT_BEGIN(main_evt)
    CALL(evt_yuuminigame_main_func)
    RETURN
EVT_END()

