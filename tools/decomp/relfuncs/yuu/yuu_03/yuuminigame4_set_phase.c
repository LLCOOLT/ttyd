// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct SlitWork { u32 flags; s32 phase; s32 coins; s32 result; s32 state; s32 timer; f32 rot1; f32 rot2; s32 monteCount; EventEntry* viewEvent; } SlitWork;
// proto: USER_FUNC(yuuminigame4_set_phase);
USER_FUNC(yuuminigame4_set_phase) {
    s32* args = event->args;
    SlitWork* data = ((MiniGameWork*)evtGetValue(event, args[0]))->data;

    data->phase = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}
