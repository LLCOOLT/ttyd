// include: dolphin/gx.h
// include: dolphin/mtx.h
// include: driver/camdrv.h
// decl: f32 point[4];
// decl: s32 darkCount;
// decl: u8 dark;
// proto: void Quads2D(f32 x0, f32 y0, f32 x1, f32 y1);
// proto: void spot_square_disp(CameraId cameraId, void* param);
void spot_square_disp(CameraId cameraId, void* param) {
    CameraEntry* cam;
    Mtx mtx;

    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, (GXColor){0, 0, 0, dark});
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    cam = camGetPtr(CAMERA_2D);
    PSMTXIdentity(mtx);
    PSMTXConcat(cam->view, mtx, mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    Quads2D(-320.0f, 240.0f, 320.0f, point[1]);
    Quads2D(-320.0f, point[1], point[0], point[3]);
    Quads2D(point[2], point[1], 320.0f, point[3]);
    Quads2D(-320.0f, point[3], 320.0f, -240.0f);
}
