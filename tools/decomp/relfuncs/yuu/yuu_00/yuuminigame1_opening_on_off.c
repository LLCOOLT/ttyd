// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct HikokiWork { u32 flags; s32 phase; s32 coins; s32 result; s32 monteCount; EventEntry* viewEvent; } HikokiWork;
// proto: USER_FUNC(yuuminigame1_opening_on_off);
USER_FUNC(yuuminigame1_opening_on_off) {
    s32* args = event->args;
    HikokiWork* data = ((MiniGameWork*)evtGetValue(event, args[0]))->data;

    if (evtGetValue(event, args[1])) {
        data->flags |= 1;
    } else {
        data->flags &= ~1;
    }
    return EVT_RETURN_DONE;
}
