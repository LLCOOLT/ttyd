// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct FuneWork { u32 flags; s32 phase; s32 coins; s32 result; s32 index; s32 state; f32 dist; Vec dir; s32 timer; f32 y; f32 x; s32 monteCount; EventEntry* viewEvent; } FuneWork;
// decl: extern s32 minigame_view_monte[];
// decl: void marioChgShipMotion(void);
// proto: void yuuminigame_init_2fune(EventEntry* event, BOOL isFirstCall);
void yuuminigame_init_2fune(EventEntry* event, BOOL isFirstCall) {
    FuneWork* data = ((MiniGameWork*)event->lwData[0])->data;

    data->viewEvent = evtEntryType(minigame_view_monte, 0, 0, 0);
    data->viewEvent->lwData[0] = event->lwData[0];
    data->flags |= 1;
    marioChgShipMotion();
}
