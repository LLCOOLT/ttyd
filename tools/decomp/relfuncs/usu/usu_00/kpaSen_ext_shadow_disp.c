// include: dolphin/mtx.h
// include: driver/camdrv.h
// decl: void extLoadShadowMtx(Mtx mtx);
// decl: void extLoadShadowRenderMode(void);
// decl: void extLoadShadowVertex(void);
// decl: void extLoadShadowTev(void);
// decl: void extDrawShadow(void);
// proto: void kpaSen_ext_shadow_disp(CameraId camera, void* param);
void kpaSen_ext_shadow_disp(CameraId camera, void* param) {
    static Mtx mt = {
        {10.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 10.0f, 0.0f, 0.1f},
        {0.0f, 0.0f, 10.0f, 0.0f},
    };

    extLoadShadowMtx(mt);
    extLoadShadowRenderMode();
    extLoadShadowVertex();
    extLoadShadowTev();
    extDrawShadow();
}
