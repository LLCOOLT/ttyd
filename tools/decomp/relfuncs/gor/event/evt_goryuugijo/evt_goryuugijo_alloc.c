// include: memory.h
// include: string.h
// decl: s32 goryuugijo_init_montemedal(EventEntry* event, BOOL isFirstCall);
// decl: s32 goryuugijo_main_montemedal(EventEntry* event, BOOL isFirstCall);
// decl: void goryuugijo_disp_montemedal(CameraId camera, void* param);
// decl: s32 goryuugijo_init_slot(EventEntry* event, BOOL isFirstCall);
// decl: s32 goryuugijo_main_slot(EventEntry* event, BOOL isFirstCall);
// decl: void goryuugijo_disp_slot(CameraId camera, void* param);
// proto: USER_FUNC(evt_goryuugijo_alloc);
USER_FUNC(evt_goryuugijo_alloc) {
    s32* args = event->args;
    GoryuuWork* wp = _mapAlloc(sizeof(GoryuuWork));

    memset(wp, 0, sizeof(GoryuuWork));
    evtSetValue(event, args[0], (s32)wp);
    wp->type = evtGetValue(event, args[1]);
    wp->event = evtEntry(main_evt, 0, 0);
    wp->event->lwData[0] = (s32)wp;
    wp->subEvent = NULL;
    switch (wp->type) {
        case 0:
            wp->init = goryuugijo_init_montemedal;
            wp->main = goryuugijo_main_montemedal;
            wp->disp = goryuugijo_disp_montemedal;
            wp->data = _mapAlloc(4);
            memset(wp->data, 0, 4);
            break;
        case 1:
            wp->init = goryuugijo_init_slot;
            wp->main = goryuugijo_main_slot;
            wp->disp = goryuugijo_disp_slot;
            wp->data = _mapAlloc(0x78);
            memset(wp->data, 0, 0x78);
            break;
    }
    wp->init(event, isFirstCall);
    return EVT_RETURN_DONE;
}
