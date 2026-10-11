// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct HikokiWork { u32 flags; s32 phase; s32 coins; s32 result; s32 monteCount; EventEntry* viewEvent; } HikokiWork;
// decl: extern s32 minigame01_start[];
// decl: extern s32 minigame01_end[];
// proto: void yuuminigame_main_1hikoki(EventEntry* event, BOOL isFirstCall);
void yuuminigame_main_1hikoki(EventEntry* event, BOOL isFirstCall) {
    MiniGameWork* wp = (MiniGameWork*)event->lwData[0];
    HikokiWork* data = wp->data;

    switch (data->phase) {
        case 0:
            break;
        case 4:
            data->phase = 1;
        case 1:
            wp->subEvent = evtEntry(minigame01_start, 0, 0);
            wp->subEvent->lwData[0] = event->lwData[0];
            data->phase++;
            break;
        case 2:
            if (yuuminigame1_gamerule(event, isFirstCall, wp, data)) {
                data->phase++;
            }
            break;
        case 3:
            wp->subEvent = evtEntry(minigame01_end, 0, 0);
            wp->subEvent->lwData[0] = data->coins;
            wp->subEvent->lwData[1] = data->result;
            wp->subEvent->lwData[2] = data->monteCount;
            data->phase++;
            break;
    }
}
