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
// proto: USER_FUNC(demo_scale);
USER_FUNC(demo_scale) {
    OSTime now = event->lifetime;
    f32 t;

    if (isFirstCall) {
        event->savedTime = now;
    }
    t = (s32)OSTicksToMilliseconds((u64)(s32)((u32)now - (u32)event->savedTime)) / 12000.0f;
    wp->scale = 600.0f * (1.0f - t) + 1500.0f * t;
    wp->scale /= 1000.0f;
    if (wp->scale >= 1.5f) {
        wp->scale = 1.5f;
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
