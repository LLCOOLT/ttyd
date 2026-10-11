// include: dolphin/gx.h
// proto: void senteresa_loadRenderMode(void);
void senteresa_loadRenderMode(void) {
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_FALSE);
    GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
}
