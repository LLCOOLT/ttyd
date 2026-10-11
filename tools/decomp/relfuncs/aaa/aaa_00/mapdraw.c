// include: manager/filemgr.h
// include: memory.h
// include: system.h
// include: string.h
// include: driver/dispdrv.h
// include: driver/camdrv.h
// decl: static void draw(CameraId camera, void* param);
// proto: USER_FUNC(mapdraw);
USER_FUNC(mapdraw) {
    if (isFirstCall) {
        wp = _mapAlloc(sizeof(AaaWork));
        memset(wp, 0, sizeof(AaaWork));
        wp->tpl = fileAllocf(4, "%s/mariost.tpl", getMarioStDvdRoot());
        wp->alpha = 0;
    }
    wp->alpha += 2;
    if (wp->alpha > 255) {
        wp->alpha = 255;
        evtSetValue(event, GF(0), 1);
    }
    dispEntry(CAMERA_3D, 1000.0f, 7, draw, wp);
    return EVT_RETURN_BLOCK;
}
