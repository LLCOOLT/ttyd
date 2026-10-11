// include: driver/camdrv.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// proto: void tiz_broken_draw(CameraId cameraId, void* param);
void tiz_broken_draw(CameraId cameraId, void* param) {
    GXTexObj tex;
    Mtx ident;
    Mtx rot;
    Mtx scale;
    Mtx mtx;
    CameraEntry* cam = camGetPtr(cameraId);
    BrokenPiece* p;
    s32 x;
    s32 y;
    s32 xo;
    s32 yo;
    f32 py;
    f32 rz;

    if (broken_wp->copied == 0) {
        GXSetTexCopySrc(0, 0, 608, 480);
        GXSetTexCopyDst(304, 240, GX_TF_RGB565, GX_TRUE);
        GXCopyTex(broken_wp->tex->address, GX_FALSE);
        GXPixModeSync();
        broken_wp->copied = 1;
    }
    GXSetNumChans(0);
    GXInitTexObj(&tex, broken_wp->tex->address, 304, 240, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&tex, GX_TEXMAP0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetCurrentMtx(0);
    PSMTXIdentity(ident);
    p = broken_wp->pieces->address;
    for (y = 0, yo = 0; y < 30; y++, yo += 16) {
        py = 232.0f - yo;
        for (x = 0, xo = 0; x < 38; x++, xo += 16) {
            if (p->delay == 0) {
                PSMTXScale(scale, 1.0f / 38.0f, 1.0f / 30.0f, 1.0f);
                PSMTXTrans(mtx, x, y, 0.0f);
                PSMTXConcat(scale, mtx, mtx);
                GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
                PSMTXTrans(mtx, -296.0f + xo, py, 0.0f);
                switch (p->dir) {
                    case 0:
                        rz = -45.0f;
                        break;
                    case 1:
                        rz = 45.0f;
                        break;
                    case 2:
                        rz = 225.0f;
                        break;
                    case 3:
                        rz = 135.0f;
                        break;
                }
                PSMTXTrans(rot, p->pos.x, p->pos.y, p->pos.z);
                PSMTXConcat(mtx, rot, mtx);
                PSMTXRotRad(rot, 'z', 0.017453292f * rz);
                PSMTXConcat(mtx, rot, mtx);
                PSMTXRotRad(rot, 'y', 0.017453292f * p->rot);
                PSMTXConcat(mtx, rot, mtx);
                PSMTXRotRad(rot, 'z', 0.017453292f * -rz);
                PSMTXConcat(mtx, rot, mtx);
                PSMTXConcat(cam->view, mtx, mtx);
                GXLoadPosMtxImm(mtx, GX_PNMTX0);
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition3f32(-8.0f, 8.0f, 0.0f);
                GXTexCoord2f32(0.0f, 0.0f);
                GXPosition3f32(8.0f, 8.0f, 0.0f);
                GXTexCoord2f32(1.0f, 0.0f);
                GXPosition3f32(8.0f, -8.0f, 0.0f);
                GXTexCoord2f32(1.0f, 1.0f);
                GXPosition3f32(-8.0f, -8.0f, 0.0f);
                GXTexCoord2f32(0.0f, 1.0f);
            }
            p++;
        }
        p++;
    }
}
