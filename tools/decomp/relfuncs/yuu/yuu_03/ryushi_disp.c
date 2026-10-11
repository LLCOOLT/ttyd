// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// include: driver/effdrv.h
// decl: typedef struct RyushiWork { s32 flag; s32 mode; Vec base; Vec pos; s32 alpha; s32 count; f32 scale; s32 r; s32 g; s32 b; s32 r2; s32 g2; s32 b2; } RyushiWork;
// decl: RyushiWork* xwp;
// decl: s32 ryuwp;
// decl: extern f32 yuusintbl[];
// decl: static void polygon(f32 x, f32 y, f32 w, f32 h, f32 u, f32 v);
// proto: void ryushi_disp(CameraId camera, void* param);
void ryushi_disp(CameraId camera, void* param) {
    RyushiWork* hdr = xwp;
    s32 g = hdr->g;
    s32 b = hdr->b;
    RyushiWork* p;
    s32 i;
    s32 n;
    f32 deg;
    f32 scale;
    f32 amp;
    Mtx trans;
    Mtx rot;
    Mtx scl;
    Mtx out;
    Mtx base;
    GXTexObj tex;

    PSMTXScale(base, hdr->scale, hdr->scale, 1.0f);
    PSMTXTransApply(base, base, hdr->pos.x, hdr->pos.y, hdr->pos.z);
    PSMTXRotRad(rot, 'y', 0.017453292f * -camGetPtr(camera)->viewYaw);
    PSMTXConcat(base, rot, base);
    effGetTexObj(0x1E, &tex);
    GXLoadTexObj(&tex, GX_TEXMAP0);
    GXSetTevColor(GX_TEVREG1, (GXColor){hdr->r2, hdr->g2, hdr->b2});
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(2);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_C0, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_A0, GX_CA_APREV, GX_CA_ZERO);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    for (i = 1, p = hdr + 1; i < ryuwp; i++, p++) {
        scale = p->scale;
        if (scale) {
            GXSetTevColor(GX_TEVREG0, (GXColor){amp, g, b, p->alpha});
            deg = 180.0f * ((p->pos.z / 8.0f + 3.14f * i / 4.0f) / 3.14f);
            n = deg / 360.0f;
            if (deg < 0.0f) {
                n--;
            }
            deg -= n * 360;
            amp = 3.0f;
            PSMTXTrans(trans, p->pos.x + amp * yuusintbl[(s32)deg], p->pos.y, p->pos.z);
            PSMTXScale(scl, scale, scale, scale);
            PSMTXConcat(trans, scl, trans);
            PSMTXConcat(base, trans, trans);
            PSMTXConcat(camGetPtr(camera)->view, trans, out);
            GXLoadPosMtxImm(out, GX_PNMTX0);
            GXSetCurrentMtx(GX_PNMTX0);
            polygon(-8.0f, -8.0f, 16.0f, 16.0f, 1.0f, 1.0f);
        }
    }
}
