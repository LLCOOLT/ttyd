// include: driver/camdrv.h
// include: driver/dispdrv.h
// include: manager/filemgr.h
// include: mario/mariost.h
// include: memory.h
// include: string.h
// include: system.h
// decl: typedef struct LogoWork { FileEntry* tpl; f32 y; s32 alpha; s32 state; s32 counter; } LogoWork;
// decl: static void draw(CameraId camera, void* param);
// proto: USER_FUNC(logo);
USER_FUNC(logo) {
    LogoWork* wp;

    if (isFirstCall) {
        wp = _mapAlloc(sizeof(LogoWork));
        memset(wp, 0, sizeof(LogoWork));
        event->userdatap[0] = wp;
    }
    wp = event->userdatap[0];
    if ((u32)fileAsyncf(4, NULL, "%s/mariost.tpl", getMarioStDvdRoot()) == 0) {
        return EVT_RETURN_BLOCK;
    }
    switch (wp->state) {
        case 0:
            wp->tpl = fileAllocf(4, "%s/mariost.tpl", getMarioStDvdRoot());
            wp->alpha = 0;
            wp->y = 0.0f;
            wp->counter = 0;
            wp->state++;
            break;
        case 1:
            if (wp->counter < 180) {
                wp->alpha = intplGetValue(11, ++wp->counter, 180, 0.0f, 255.0f);
                wp->y = intplGetValue(11, ++wp->counter, 180, -50.0f, 0.0f);
            } else if (gp->retraceCount % 15 == 0) {
                wp->state++;
            }
            break;
        case 2:
            if (evtGetValue(event, GF(0)) && (keyGetButtonTrg(0) & 0x1300)) {
                wp->counter = 0;
                wp->state++;
                evtSetValue(event, GF(1), 1);
            }
            break;
        case 3:
            if (wp->counter < 120) {
                wp->alpha = intplGetValue(11, ++wp->counter, 120, 255.0f, 0.0f);
                wp->y = intplGetValue(11, ++wp->counter, 120, 0.0f, 100.0f);
            } else {
                wp->state++;
            }
            break;
        case 4:
            fileFree(wp->tpl);
            wp->tpl = NULL;
            _mapFree(wp);
            evtSetValue(event, GF(2), 1);
            return EVT_RETURN_DONE;
    }
    if (wp->tpl) {
        dispEntry(CAMERA_2D, 1000.0f, 0, draw, wp);
    }
    return EVT_RETURN_BLOCK;
}
