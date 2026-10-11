// include: dolphin/gx.h
// include: dolphin/mtx.h
// decl: double tan(double x);
// proto: void make_shadow_disp(CameraId camera, void* param);
void make_shadow_disp(CameraId camera, void* param) {
    ShadowWork* wp = param;
    Mtx44 proj;
    Mtx view;
    Mtx mtx;
    f32 viewport[6];
    f32 projv[7];
    u32 left;
    u32 top;
    u32 width;
    u32 height;
    f32 t;

    GXGetViewportv(viewport);
    GXGetProjectionv(projv);
    GXGetScissor(&left, &top, &width, &height);
    GXSetViewport(0.0f, 0.0f, 256.0f, 256.0f, 0.0f, 1.0f);
    GXSetScissor(1, 1, 254, 254);
    C_MTXPerspective(proj, 25.0f, 1.2666667f, 1.0f, 1000.0f);
    GXSetProjection(proj, GX_PERSPECTIVE);
    C_MTXLookAt(view, &(Vec){0.0f, (t = tan(0.21816615760326385), 128.0f / t), 0.0f}, &(Vec){0.0f, 0.0f, -1.0f},
                &(Vec){0.0f, 0.0f, 0.0f});
    PSMTXScale(mtx, 128.0f, 64.0f, 64.0f);
    PSMTXConcat(view, mtx, mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetNumChans(1);
    GXSetChanMatColor(GX_COLOR0A0, (GXColor){0x80, 0x80, 0x80, 0x40});
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXDrawSphere(16, 8);
    GXSetTexCopySrc(0, 0, 256, 256);
    GXSetTexCopyDst(128, 128, GX_TF_RGB5A3, GX_TRUE);
    GXCopyTex(wp->tex->address, GX_TRUE);
    GXInvalidateTexAll();
    GXPixModeSync();
    GXTexModeSync();
    GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
    GXSetProjectionv(projv);
    GXSetScissor(left, top, width, height);
}
