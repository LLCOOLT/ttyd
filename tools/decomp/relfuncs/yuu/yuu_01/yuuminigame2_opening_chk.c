// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct FuneWork { u32 flags; s32 phase; s32 coins; s32 result; s32 index; s32 state; f32 dist; Vec dir; s32 timer; f32 y; f32 x; s32 monteCount; EventEntry* viewEvent; } FuneWork;
// proto: USER_FUNC(yuuminigame2_opening_chk);
USER_FUNC(yuuminigame2_opening_chk) {
    s32* args = event->args;
    MiniGameWork* wp = (MiniGameWork*)evtGetValue(event, args[0]);

    if (((FuneWork*)wp->data)->flags & 1) {
        evtSetValue(event, args[1], 1);
    } else {
        evtSetValue(event, args[1], 0);
    }
    return EVT_RETURN_DONE;
}
