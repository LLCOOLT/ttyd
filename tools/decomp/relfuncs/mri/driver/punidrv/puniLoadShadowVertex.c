// include: driver/punidrv.h
// proto: void puniLoadShadowVertex(void);
void puniLoadShadowVertex(void) {
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetArray(GX_VA_POS, shadow_vtx, 12);
    GXSetCullMode(GX_CULL_NONE);
}
