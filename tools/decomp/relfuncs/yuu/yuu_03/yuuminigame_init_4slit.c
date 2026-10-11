// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: memory.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct SlitWork { u32 flags; s32 phase; s32 coins; s32 result; s32 state; s32 timer; f32 rot1; f32 rot2; s32 monteCount; EventEntry* viewEvent; } SlitWork;
// decl: typedef struct RyushiWork { s32 flag; s32 mode; Vec base; Vec pos; s32 alpha; s32 count; f32 scale; s32 r; s32 g; s32 b; s32 r2; s32 g2; s32 b2; } RyushiWork;
// decl: RyushiWork* xwp;
// decl: s32 ryuwp;
// decl: extern s32 unk_evt_yuu_00015fe0[];
// decl: USER_FUNC(evt_ryushi_init);
// proto: void yuuminigame_init_4slit(EventEntry* event, BOOL isFirstCall);
void yuuminigame_init_4slit(EventEntry* event, BOOL isFirstCall) {
    SlitWork* data = ((MiniGameWork*)event->lwData[0])->data;

    data->viewEvent = evtEntryType(unk_evt_yuu_00015fe0, 0, 0, 0);
    data->viewEvent->lwData[0] = event->lwData[0];
    data->flags |= 1;
    evt_ryushi_init(event, isFirstCall);
}
