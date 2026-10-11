// include: memory.h
// include: mario/mariost.h
// include: driver/camdrv.h
// include: manager/evtmgr.h
// include: dolphin/gx.h
// include: dolphin/os.h
// decl: double sin(double x);
// decl: inline s32 ia8_ofs(s32 x, s32 y) { s32 off = ((y / 4) << 5) + ((x / 4) << 9); off += ((y % 4) + ((x % 4) << 2)) * 2; return off; }
// proto: void raster_disp(CameraId cameraId, void* param);
void raster_disp(CameraId cameraId, void* param) {
    EventEntry* event = param;
    CameraEntry* cam = camGetPtr(cameraId);
    f32 amp = ((f32*)event->lwData)[0];
    f32 phase = ((f32*)event->lwData)[1];
    f32 mtx[2][3];
    GXTexObj obj;
    void* copyBuf;
    u8* buf;
    s32 i;
    s32 j;
    f32 w;
    f32 h;

    if (amp > 127.0f) {
        amp = 127.0f;
    }
    copyBuf = smartAlloc(GXGetTexBufferSize(608, 480, GX_TF_RGBA8, GX_FALSE, 0), 3)->address;
    buf = smartAlloc(GXGetTexBufferSize(64, 64, GX_TF_IA8, GX_FALSE, 0), 3)->address;
    phase = 6.2831855f * phase;
    for (i = 0; i < 64; i++) {
        for (j = 0; j < 64; j++) {
            f32 v = sin(j + (gp->retraceCount / 4.0f + phase));
            u8* p = buf + ia8_ofs(j, i);

            p[0] = amp * v + 128.0f;
            p[1] = 0x80;
        }
    }
    DCFlushRange(buf, 0x2000);
    GXSetTexCopySrc(0, 0, 608, 480);
    GXSetTexCopyDst(608, 480, GX_TF_RGBA8, GX_FALSE);
    GXCopyTex(copyBuf, GX_FALSE);
    GXPixModeSync();
    GXInitTexObj(&obj, copyBuf, 608, 480, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    GXInitTexObj(&obj, buf, 64, 64, GX_TF_IA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(&obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP1);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_OR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    mtx[0][0] = 0.5f;
    mtx[0][1] = 0.0f;
    mtx[0][2] = 0.0f;
    mtx[1][0] = 0.0f;
    mtx[1][1] = 0.5f;
    mtx[1][2] = 0.0f;
    GXSetIndTexMtx(GX_ITM_0, mtx, 1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_8, GX_ITS_8);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXSetNumIndStages(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    w = 608.0f;
    h = 480.0f;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-w / 2, h / 2, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(w / 2, h / 2, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(w / 2, -h / 2, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(-w / 2, -h / 2, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
}
