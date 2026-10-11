// include: dolphin/mtx.h
// decl: void extLoadShadowMtx(Mtx mtx);
// decl: void extLoadShadowRenderMode(void);
// decl: void extLoadShadowVertex(void);
// decl: void extLoadShadowTev(void);
// decl: void extDrawShadow(void);
// proto: static void senteresa_ext_shadow_disp(void);
static void senteresa_ext_shadow_disp(void) {
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
