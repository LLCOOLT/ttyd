// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: system.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct SlitWork { u32 flags; s32 phase; s32 coins; s32 result; s32 state; s32 timer; f32 rot1; f32 rot2; s32 monteCount; EventEntry* viewEvent; } SlitWork;
// decl: extern s32 minigame04_start[];
// decl: extern s32 minigame04_end[];
// decl: void mapObjRotate(const char* name, f32 x, f32 y, f32 z);
// decl: BOOL yuuminigame4_gamerule(EventEntry* event, BOOL isFirstCall, MiniGameWork* wp, SlitWork* data);
// proto: void yuuminigame_main_4slit(EventEntry* event, BOOL isFirstCall);
void yuuminigame_main_4slit(EventEntry* event, BOOL isFirstCall) {
    MiniGameWork* wp = (MiniGameWork*)event->lwData[0];
    SlitWork* data = wp->data;

    switch (data->phase) {
        case 0:
            break;
        case 5:
            data->phase = 1;
        case 1:
            wp->subEvent = evtEntry(minigame04_start, 0, 0);
            wp->subEvent->lwData[0] = event->lwData[0];
            data->phase++;
            break;
        case 2:
            data->state = 0;
            data->timer = (irand(3901) + 100) * 60 / 1000;
            data->result = 0;
            data->phase = 3;
        case 3:
            if (yuuminigame4_gamerule(event, isFirstCall, wp, data)) {
                data->phase++;
            }
            break;
        case 4:
            wp->subEvent = evtEntry(minigame04_end, 0, 0);
            wp->subEvent->lwData[0] = data->coins;
            switch (data->coins) {
                case 0:
                    data->result = 0x105;
                    break;
                case 1:
                    data->result = 0x103;
                    break;
                case 2:
                    data->result = 0x101;
                    break;
                case 10:
                case 21:
                case 32:
                case 43:
                case 54:
                case 65:
                case 76:
                case 87:
                case 98:
                case 110:
                case 221:
                case 332:
                case 443:
                case 554:
                case 665:
                case 776:
                case 887:
                case 998:
                case 1110:
                case 2221:
                case 3332:
                case 4443:
                case 5554:
                case 6665:
                case 7776:
                case 8887:
                case 9998:
                    data->result = 0x103;
                    break;
            }
            wp->subEvent->lwData[1] = data->result;
            data->phase++;
            break;
    }
    mapObjRotate("puro_1", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_2", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_3", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_4", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_5", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_6", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_7", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_8", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_9", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_10", 0.0f, 0.0f, data->rot1);
    mapObjRotate("pera_1", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_2", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_3", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_4", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_5", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_6", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_7", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_8", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_9", 0.0f, 0.0f, data->rot2);
}
