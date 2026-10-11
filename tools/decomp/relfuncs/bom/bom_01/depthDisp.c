// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: evt/evt_cmd.h
// include: memory.h
// include: system.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// proto: static void depthDisp(CameraId camera, void* param);
static inline f32 dd_sin(f32 x) {
    f32 a = 0.00761f;
    f32 b = 0.16605f;
    f32 c = 1.0f;
    f32 y;
    f32 x2;
    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x;
        } else {
            y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y;
        }
    } else if (x < 4.712389f) {
        y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a;
    } else {
        y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a;
    }
    return a;
}

static inline f32 dd_cos(f32 x) {
    f32 a = 0.03705f;
    f32 b = 0.4967f;
    f32 c = 1.0f;
    f32 y;
    f32 x2;
    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x; a = a * x2 - b; a = a * x2 + c;
        } else {
            y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a;
        }
    } else if (x < 4.712389f) {
        y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a;
    } else {
        y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c;
    }
    return a;
}

#pragma opt_propagation off
#pragma opt_lifetimes off
static void depthDisp(CameraId camera, void* param) {
    f32 amp = evtGetValue(NULL, GW(5)) / 100.0f;
    CameraEntry* cam = camGetPtr(camera);
    smartEntry* buf = smartAlloc(GXGetTexBufferSize(608, 480, GX_TF_RGB565, GX_FALSE, 0), 3);
    GXTexObj obj;
    Mtx mtx;
    f32 a;
    f32 s;
    f32 c;
    s32 i;
    BOOL first;
    GXTevColorArg carg;

    GXSetTexCopySrc(0, 0, 608, 480);
    GXSetTexCopyDst(608, 480, GX_TF_RGB565, GX_FALSE);
    GXCopyTex(buf->address, GX_FALSE);
    GXPixModeSync();
    GXInitTexObj(&obj, buf->address, 608, 480, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(8);
    GXSetNumTevStages(8);
    for (i = 0; i < 8; i++) {
        a = 6.2831855f * i / 8.0f;
        s = dd_sin(a);
        c = dd_cos(a);
        MTXTrans(mtx, (amp * s) / 100.0f, (amp * c) / 100.0f, 0.0f);
        GXLoadTexMtxImm(mtx, GX_TEXMTX0 + i * 3, GX_MTX2x4);
        GXSetTexCoordGen2((GXTexCoordID)i, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0 + i * 3, GX_FALSE, GX_PTIDENTITY);
        GXSetTevKColorSel((GXTevStageID)i, GX_TEV_KCSEL_1_8);
        GXSetTevKAlphaSel((GXTevStageID)i, GX_TEV_KASEL_1_8);
        GXSetTevOrder((GXTevStageID)i, (GXTexCoordID)i, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorOp((GXTevStageID)i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp((GXTevStageID)i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        first = !i;
        carg = first ? GX_CC_ZERO : GX_CC_CPREV;
        GXSetTevColorIn((GXTevStageID)i, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, carg);
        GXSetTevAlphaIn((GXTevStageID)i, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, first ? GX_CA_ZERO : GX_CA_APREV);
        GXSetTevSwapMode((GXTevStageID)i, GX_TEV_SWAP0, GX_TEV_SWAP0);
    }
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetCullMode(GX_CULL_BACK);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3s16(-304, 240, 0);
    GXTexCoord2s16(0, 0);
    GXPosition3s16(304, 240, 0);
    GXTexCoord2s16(1, 0);
    GXPosition3s16(304, -240, 0);
    GXTexCoord2s16(1, 1);
    GXPosition3s16(-304, -240, 0);
    GXTexCoord2s16(0, 1);
    GXEnd();
    sysWaitDrawSync();
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
