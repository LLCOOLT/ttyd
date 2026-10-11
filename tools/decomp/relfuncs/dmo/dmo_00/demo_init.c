// include: manager/evtmgr.h
// include: manager/evtmgr_cmd.h
// include: mario/mariost.h
// include: driver/camdrv.h
// include: driver/dispdrv.h
// include: driver/effdrv.h
// include: driver/imgdrv.h
// include: manager/filemgr.h
// include: manager/fontmgr.h
// include: driver/msgdrv.h
// include: pmario_sound.h
// include: system.h
// include: sdk/texPalette.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// include: dolphin/os.h
// include: string.h
// include: stdio.h
// decl: typedef struct DemoWork { s32 field_0x0; f32 bookRot; s32 page; s32 captured; f32 fade; f32 scale; f32 x; f32 y; void** capBuf; FileEntry* tpl; s32 winOn; s32 winAlpha; } DemoWork;
// decl: static DemoWork work;
// decl: char buf[0x200];
// decl: static DemoWork* wp = &work;
// decl: double sin(double x);
// decl: void demo_img(CameraId cameraId, void* param);
// decl: void demo_book(CameraId cameraId, void* param);
// decl: void demo_desk(CameraId cameraId, void* param);
// decl: void demo_window(CameraId cameraId, void* param);
// proto: USER_FUNC(demo_init);
USER_FUNC(demo_init) {
    if (isFirstCall) {
        memset(wp, 0, sizeof(DemoWork));
        wp->bookRot = 0.0f;
        wp->page = -1;
        wp->captured = 0;
        wp->fade = 0.0f;
        wp->scale = 1.0f;
        wp->x = 0.0f;
        wp->y = 0.0f;
        statusWinDispOff();
        psndSetFlag(4);
    }
    if (fileAsyncf(4, NULL, "%s/demo.tpl", getMarioStDvdRoot()) != 0U) {
        wp->tpl = fileAllocf(4, "%s/demo.tpl", getMarioStDvdRoot());
        gp->areaFadeOutType = 9;
        gp->areaFadeOutDuration = 500;
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
