// include: memory.h
// include: driver/dispdrv.h
// include: dolphin/gx.h
// decl: typedef struct ShadowWork { GXTexObj obj; smartEntry* tex; } ShadowWork;
// decl: void mapSetProjTexObj(GXTexObj* obj, smartEntry* tex);
// decl: void make_shadow_disp(CameraId camera, void* param);
// proto: USER_FUNC(make_shadow);
USER_FUNC(make_shadow) {
    ShadowWork* wp;

    if (isFirstCall) {
        wp = _mapAlloc(sizeof(ShadowWork));
        event->userdata[0] = (s32)wp;
        wp->tex = smartAlloc(GXGetTexBufferSize(128, 128, GX_TF_RGB5A3, GX_FALSE, 0), 1);
    }
    wp = (ShadowWork*)event->userdata[0];
    GXInitTexObj(&wp->obj, wp->tex->address, 128, 128, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&wp->obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    mapSetProjTexObj(&wp->obj, wp->tex);
    dispEntry(CAMERA_SHADOW, 0.0f, 3, make_shadow_disp, wp);
    return EVT_RETURN_BLOCK;
}
