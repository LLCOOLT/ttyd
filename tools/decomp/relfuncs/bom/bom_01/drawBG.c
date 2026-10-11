// include: memory.h
// include: string.h
// include: stdlib.h
// include: system.h
// include: manager/filemgr.h
// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// include: driver/camdrv.h
// decl: typedef struct SightWork { FileEntry* tpl; s32 level[5]; f32 rot; s32 dir; s32 count1; s32 count2; } SightWork;
// decl: SightWork* sight_wp;
// include: sdk/texPalette.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// proto: void drawBG(s32 id, f32 x, f32 y, f32 sx, f32 sy, f32 rot);
void drawBG(s32 id, f32 x, f32 y, f32 sx, f32 sy, f32 rot) {
    CameraEntry* cam = camGetPtr(CAMERA_2D);
    Mtx trans;
    Mtx rotm;
    Mtx scale;
    GXTexObj obj;
    s16 w;
    u16 h;

    TEXGetGXTexObjFromPalette(*sight_wp->tpl->data, &obj, id);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    if (id == 0) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_TEXA, GX_CA_ZERO);
        GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_1);
    }
    PSMTXTrans(trans, x, y, 0.0f);
    PSMTXScale(scale, sx, sy, 1.0f);
    PSMTXRotRad(rotm, 'z', MTXDegToRad(rot));
    PSMTXConcat(trans, scale, scale);
    PSMTXConcat(scale, rotm, trans);
    PSMTXConcat(cam->view, trans, trans);
    GXLoadPosMtxImm(trans, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    w = GXGetTexObjWidth(&obj);
    h = GXGetTexObjHeight(&obj);
    GXPosition3s16(-w, h, 0);
    GXTexCoord2s16(0, 0);
    GXPosition3s16(0, h, 0);
    GXTexCoord2s16(1, 0);
    GXPosition3s16(0, 0, 0);
    GXTexCoord2s16(1, 1);
    GXPosition3s16(-w, 0, 0);
    GXTexCoord2s16(0, 1);
    GXEnd();
}
