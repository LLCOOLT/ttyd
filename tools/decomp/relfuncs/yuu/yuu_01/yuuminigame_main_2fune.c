// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct FuneWork { u32 flags; s32 phase; s32 coins; s32 result; s32 index; s32 state; f32 dist; Vec dir; s32 timer; f32 y; f32 x; s32 monteCount; EventEntry* viewEvent; } FuneWork;
// decl: extern s32 minigame02_start[];
// decl: extern s32 minigame02_end[];
// proto: void yuuminigame_main_2fune(EventEntry* event, BOOL isFirstCall);
void yuuminigame_main_2fune(EventEntry* event, BOOL isFirstCall) {
    MiniGameWork* wp = (MiniGameWork*)event->lwData[0];
    FuneWork* data = wp->data;

    switch (data->phase) {
        case 0:
            break;
        case 5:
            data->phase = 1;
        case 1:
            wp->subEvent = evtEntry(minigame02_start, 0, 0);
            wp->subEvent->lwData[0] = event->lwData[0];
            data->phase++;
            break;
        case 2:
            data->index = 0x15;
            data->phase = 3;
            data->result = 0;
        case 3:
            if (yuuminigame2_gamerule(event, isFirstCall, wp, data)) {
                data->phase++;
            }
            break;
        case 4:
            wp->subEvent = evtEntry(minigame02_end, 0, 0);
            wp->subEvent->lwData[0] = data->coins;
            if (data->result + 5 <= 0) {
                data->result = 1;
            } else {
                data->result += 0x105;
            }
            wp->subEvent->lwData[1] = data->result;
            wp->subEvent->lwData[2] = data->monteCount;
            data->phase++;
            break;
    }
}
