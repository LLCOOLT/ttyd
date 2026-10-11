// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct RollWork { u32 flags; s32 phase; s32 coins; s32 result; s32 index; EventEntry* jumpEvent; Vec pos; s32 monteCount; EventEntry* viewEvent; } RollWork;
// decl: extern s32 minigame_view_monte[];
// decl: extern s32 unk_evt_yuu_000152bc[];
// decl: void marioChgRollMotion(void);
// proto: void yuuminigame_init_3roll(EventEntry* event, BOOL isFirstCall);
void yuuminigame_init_3roll(EventEntry* event, BOOL isFirstCall) {
    RollWork* data = ((MiniGameWork*)event->lwData[0])->data;
    EventEntry* e;

    e = evtEntryType(unk_evt_yuu_000152bc, 0, 0, 0xEF);
    e->lwData[0] = event->lwData[0];
    data->viewEvent = evtEntryType(minigame_view_monte, 0, 0, 0);
    data->viewEvent->lwData[0] = event->lwData[0];
    data->flags |= 1;
    marioChgRollMotion();
}
