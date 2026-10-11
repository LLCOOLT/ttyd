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
// proto: USER_FUNC(adjust);
USER_FUNC(adjust) {
    s32* args = event->args;
    Mtx trans;
    Mtx scale;
    ImageEntry* img;
    f32 v;
    f32 s;

    v = evtGetFloat(event, args[0]);
    img = imgNameToPtr("img4", gp->inBattle != 0);
    wp->fade = v;
    s = (f32)sin(1.5707964f * wp->fade);
    wp->scale = 1.5f * s + 1.5f;
    wp->y = -105.0f * (f32)sin(1.5707964f * wp->fade);
    PSMTXTrans(trans, wp->x / 10.0f, wp->y / 10.0f, 0.0f);
    PSMTXScale(scale, wp->scale / 1.5f, wp->scale / 1.5f, wp->scale / 1.5f);
    PSMTXConcat(trans, scale, img->field_0x120);
    return EVT_RETURN_DONE;
}
