// include: memory.h
// include: driver/dispdrv.h
// include: dolphin/gx.h
// decl: typedef struct GonbabaProj { GXTexObj obj; smartEntry* tex; } GonbabaProj;
// decl: void mapSetProjTexObj(GXTexObj* obj, smartEntry* tex);
// decl: void make_gonbaba_projection(CameraId camera, void* param);
// proto: USER_FUNC(make_gonbaba_projection_evt);
USER_FUNC(make_gonbaba_projection_evt) {
    GonbabaProj* wp;

    if (isFirstCall) {
        event->userdata[0] = (s32)_mapAlloc(sizeof(GonbabaProj));
    }
    wp = (GonbabaProj*)event->userdata[0];
    wp->tex = smartAlloc(GXGetTexBufferSize(608, 480, GX_TF_RGBA8, GX_FALSE, 0), 3);
    GXInitTexObj(&wp->obj, wp->tex->address, 608, 480, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&wp->obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    mapSetProjTexObj(&wp->obj, wp->tex);
    dispEntry(CAMERA_SHADOW, 0.0f, 3, make_gonbaba_projection, wp);
    return EVT_RETURN_BLOCK;
}
