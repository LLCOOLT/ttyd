// include: driver/camdrv.h
// include: memory.h
// include: mario/mariost.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// include: dolphin/os.h
// decl: int rand(void);
// decl: const GXColor noise_color = {0, 0, 0, 0};
// proto: void noiseDisp(CameraId cameraId, void* param);
void noiseDisp(CameraId cameraId, void* param) {
    GXTexObj tex;
    Mtx mtx;
    CameraEntry* cam = camGetPtr(cameraId);
    u8* buf = smartAlloc(GXGetTexBufferSize(64, 64, GX_TF_I8, GX_FALSE, 0), 3)->address;
    s32 y, x, i, n, len, start;
    s32 by, ry, off;
    u8 col;

    for (y = 0; y < 64; y++) {
        by = y / 4;
        ry = y % 4;
        for (x = 0; x < 64; x++) {
            off = (x / 8) * 32 + by * 256;
            off += x % 8;
            off += ry * 8;
            buf[off] = (y & 1) ? 0xFF : 0;
        }
        n = rand() % 100 + 100;
        for (i = 0; i < n; i++) {
            len = rand() % 4 + 2;
            start = rand() % (65 - len);
            col = rand() % 255;
            for (x = start; x < start + len; x++) {
                off = (x / 8) * 32 + by * 256;
                off += x % 8;
                off += ry * 8;
                buf[off] = col;
            }
        }
    }
    DCFlushRange(buf, 0x1000);
    GXInitTexObj(&tex, buf, 64, 64, GX_TF_I8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(&tex, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&tex, GX_TEXMAP0);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    PSMTXScale(mtx, 9.5f, 7.5f, 0.0f);
    GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    {
        GXColor c = noise_color;
        c.a = (u8)(s32)param;
        GXSetTevColor(GX_TEVREG0, c);
    }
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXSetCurrentMtx(0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3s16(-gp->fbWidth / 2, gp->efbHeight / 2, 0);
    GXTexCoord2s16(0, 1);
    GXPosition3s16(gp->fbWidth / 2, gp->efbHeight / 2, 0);
    GXTexCoord2s16(1, 1);
    GXPosition3s16(gp->fbWidth / 2, -gp->efbHeight / 2, 0);
    GXTexCoord2s16(1, 0);
    GXPosition3s16(-gp->fbWidth / 2, -gp->efbHeight / 2, 0);
    GXTexCoord2s16(0, 0);
}
