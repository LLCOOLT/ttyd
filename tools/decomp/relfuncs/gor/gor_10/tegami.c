// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// include: manager/filemgr.h
// include: memory.h
// include: system.h
// include: string.h
// decl: typedef struct TegamiWork { s32 alpha; FileEntry* tpl; } TegamiWork;
// decl: static TegamiWork* wp;
// decl: static void draw(CameraId camera, void* param);
// proto: USER_FUNC(tegami);
USER_FUNC(tegami) {
    if (isFirstCall) {
        wp = _mapAlloc(sizeof(TegamiWork));
        memset(wp, 0, sizeof(TegamiWork));
        wp->alpha = 0;
        wp->tpl = fileAllocf(4, "%s/mariost.tpl", getMarioStDvdRoot());
    }
    wp->alpha += 2;
    if (wp->alpha > 128) {
        wp->alpha = 128;
    }
    dispEntry(CAMERA_2D, 0.0f, 0, draw, wp);
    return EVT_RETURN_BLOCK;
}
