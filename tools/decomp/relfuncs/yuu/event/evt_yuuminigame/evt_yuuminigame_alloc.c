// include: memory.h
// include: string.h
// decl: s32 yuuminigame_init_1hikoki(EventEntry* event, BOOL isFirstCall);
// decl: s32 yuuminigame_main_1hikoki(EventEntry* event, BOOL isFirstCall);
// decl: void yuuminigame_disp_1hikoki(CameraId camera, void* param);
// decl: s32 yuuminigame_init_2fune(EventEntry* event, BOOL isFirstCall);
// decl: s32 yuuminigame_main_2fune(EventEntry* event, BOOL isFirstCall);
// decl: void yuuminigame_disp_2fune(CameraId camera, void* param);
// decl: s32 yuuminigame_init_3roll(EventEntry* event, BOOL isFirstCall);
// decl: s32 yuuminigame_main_3roll(EventEntry* event, BOOL isFirstCall);
// decl: void yuuminigame_disp_3roll(CameraId camera, void* param);
// decl: s32 yuuminigame_init_4slit(EventEntry* event, BOOL isFirstCall);
// decl: s32 yuuminigame_main_4slit(EventEntry* event, BOOL isFirstCall);
// decl: void yuuminigame_disp_4slit(CameraId camera, void* param);
// proto: USER_FUNC(evt_yuuminigame_alloc);
USER_FUNC(evt_yuuminigame_alloc) {
    s32* args = event->args;
    MiniGameWork* wp = _mapAlloc(sizeof(MiniGameWork));

    memset(wp, 0, sizeof(MiniGameWork));
    evtSetValue(event, args[0], (s32)wp);
    wp->type = evtGetValue(event, args[1]);
    wp->event = evtEntry(main_evt, 0, 0);
    wp->event->lwData[0] = (s32)wp;
    wp->subEvent = NULL;
    switch (wp->type) {
        case 0:
            wp->init = yuuminigame_init_1hikoki;
            wp->main = yuuminigame_main_1hikoki;
            wp->disp = yuuminigame_disp_1hikoki;
            wp->data = _mapAlloc(0x18);
            memset(wp->data, 0, 0x18);
            break;
        case 1:
            wp->init = yuuminigame_init_2fune;
            wp->main = yuuminigame_main_2fune;
            wp->disp = yuuminigame_disp_2fune;
            wp->data = _mapAlloc(0x3C);
            memset(wp->data, 0, 0x3C);
            break;
        case 2:
            wp->init = yuuminigame_init_3roll;
            wp->main = yuuminigame_main_3roll;
            wp->disp = yuuminigame_disp_3roll;
            wp->data = _mapAlloc(0x2C);
            memset(wp->data, 0, 0x2C);
            break;
        case 3:
            wp->init = yuuminigame_init_4slit;
            wp->main = yuuminigame_main_4slit;
            wp->disp = yuuminigame_disp_4slit;
            wp->data = _mapAlloc(0x28);
            memset(wp->data, 0, 0x28);
            yuunpc_yuuminigame4_ptr = wp;
            break;
    }
    wp->init(event, isFirstCall);
    return EVT_RETURN_DONE;
}
