// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: mario/mario.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct RollWork { u32 flags; s32 phase; s32 coins; s32 result; s32 index; EventEntry* jumpEvent; Vec pos; s32 monteCount; EventEntry* viewEvent; } RollWork;
// decl: extern s32 minigame03_start[];
// decl: extern s32 minigame03_end[];
// proto: void yuuminigame_main_3roll(EventEntry* event, BOOL isFirstCall);
void yuuminigame_main_3roll(EventEntry* event, BOOL isFirstCall) {
    MiniGameWork* wp = (MiniGameWork*)event->lwData[0];
    RollWork* data = wp->data;
    MarioWork* mario = marioGetPtr();

    switch (data->phase) {
        case 0:
            break;
        case 5:
            data->phase = 1;
        case 1:
            wp->subEvent = evtEntry(minigame03_start, 0, 0);
            wp->subEvent->lwData[0] = event->lwData[0];
            data->phase++;
            break;
        case 2:
            data->pos = mario->position;
            data->phase = 3;
            data->result = 0;
        case 3:
            if (yuuminigame3_gamerule(event, isFirstCall, wp, data)) {
                data->phase++;
            }
            break;
        case 4:
            wp->subEvent = evtEntry(minigame03_end, 0, 0);
            wp->subEvent->lwData[0] = data->coins;
            if (data->result + 5 <= 0) {
                data->result = 1;
            } else {
                data->result += 261;
            }
            wp->subEvent->lwData[1] = data->result;
            wp->subEvent->lwData[2] = data->monteCount;
            data->phase++;
            break;
    }
}
