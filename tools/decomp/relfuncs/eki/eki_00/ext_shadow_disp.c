// include: dolphin/gx.h
// include: dolphin/mtx.h
// include: driver/camdrv.h
// include: driver/offscreendrv.h
// include: system.h
// decl: void extLoadShadowMtx(Mtx mtx);
// decl: void extLoadShadowRenderMode(void);
// decl: void extLoadShadowVertex(void);
// decl: void extLoadShadowTev(void);
// decl: void extDrawShadow(void);
// proto: static void ext_shadow_disp(CameraId camera, void* param);
static void ext_shadow_disp(CameraId camera, void* param) {
    static Mtx mt = {
        {8.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 8.0f, 0.0f, 0.5f},
        {0.0f, 0.0f, 8.0f, 0.0f},
    };
    u16 left, top, right, bottom;

    if (camera == CAMERA_OFFSCREEN2) {
        GXClearBoundingBox();
    }
    extLoadShadowMtx(mt);
    extLoadShadowRenderMode();
    extLoadShadowVertex();
    extLoadShadowTev();
    extDrawShadow();
    if (camera == CAMERA_OFFSCREEN2) {
        sysWaitDrawSync();
        GXReadBoundingBox(&left, &top, &right, &bottom);
        offscreenAddBoundingBox(offscreenNameToId("offscreen"), left, top, right, bottom);
    }
}
