// include: driver/punidrv.h
// proto: void puniLoadVertex(void);
void puniLoadVertex(void) {
    PunidrvWork* wp = work;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetArray(GX_VA_POS, wp->vtx, 12);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetArray(GX_VA_TEX0, wp->uvs, 8);
    GXSetCullMode(GX_CULL_NONE);
}
