// include: manager/evtmgr.h
// include: manager/evtmgr_cmd.h
// include: mario/mariost.h
// include: driver/camdrv.h
// include: driver/dispdrv.h
// include: driver/effdrv.h
// include: driver/imgdrv.h
// include: manager/filemgr.h
// include: manager/fontmgr.h
// include: driver/msgdrv.h
// include: pmario_sound.h
// include: system.h
// include: sdk/texPalette.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// include: dolphin/os.h
// include: string.h
// include: stdio.h
// decl: typedef struct DemoWork { s32 field_0x0; f32 bookRot; s32 page; s32 captured; f32 fade; f32 scale; f32 x; f32 y; void** capBuf; FileEntry* tpl; s32 winOn; s32 winAlpha; } DemoWork;
// decl: static DemoWork work;
// decl: char buf[0x200];
// decl: static DemoWork* wp = &work;
// decl: double sin(double x);
// decl: void demo_img(CameraId cameraId, void* param);
// decl: void demo_book(CameraId cameraId, void* param);
// decl: void demo_desk(CameraId cameraId, void* param);
// decl: void demo_window(CameraId cameraId, void* param);
// proto: void demo_book(CameraId cameraId, void* param);
void demo_book(CameraId cameraId, void* param) {
    CameraEntry* cam = camGetPtr(8);
    GXTexObj obj;
    Mtx mtx;
    Mtx scale;
    Mtx rot;
    f32 w;
    f32 h;
    f32 pw;
    f32 ph;

    GXSetProjection(cam->projection, cam->projType);
    GXSetViewport(0.0f, 0.0f, 608.0f, 480.0f, 0.0f, 1.0f);
    TEXGetGXTexObjFromPalette(*wp->tpl->data, &obj, 2);
    w = GXGetTexObjWidth(&obj);
    PSMTXTrans(mtx, wp->x, wp->y, 0.0f);
    PSMTXScale(scale, wp->scale, wp->scale, wp->scale);
    PSMTXConcat(mtx, scale, mtx);
    PSMTXConcat(cam->view, mtx, scale);
    PSMTXTrans(mtx, -w / 2 + 8.0f, 0.0f, 0.0f);
    PSMTXConcat(scale, mtx, mtx);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, (GXColor){0xFF, 0xFF, 0xFF, 255.0f * (1.0f - wp->fade)});
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    TEXGetGXTexObjFromPalette(*wp->tpl->data, &obj, 1);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetCullMode(GX_CULL_BACK);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    TEXGetGXTexObjFromPalette(*wp->tpl->data, &obj, 2);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    w = GXGetTexObjWidth(&obj);
    h = GXGetTexObjHeight(&obj);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, h / 2, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(w, h / 2, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(w, -h / 2, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(0.0f, -h / 2, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXEnd();
    w = GXGetTexObjWidth(&obj);
    h = GXGetTexObjHeight(&obj);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    if (wp->page >= 0) {
        TEXGetGXTexObjFromPalette(*wp->tpl->data, &obj, wp->page + 3);
        GXLoadTexObj(&obj, GX_TEXMAP0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        ph = 0.95f * h;
        pw = 0.95f * w;
        GXPosition3f32(0.0f, ph / 2, 0.0f);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(pw, ph / 2, 0.0f);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(pw, -ph / 2, 0.0f);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(0.0f, -ph / 2, 0.0f);
        GXTexCoord2f32(0.0f, 1.0f);
        GXEnd();
        demo_img(cameraId, param);
    }
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_OR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    PSMTXRotRad(rot, 'y', 0.017453292f * -wp->bookRot);
    PSMTXConcat(mtx, rot, rot);
    GXLoadPosMtxImm(rot, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    TEXGetGXTexObjFromPalette(*wp->tpl->data, &obj, 1);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, h / 2, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(w, h / 2, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(w, -h / 2, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(0.0f, -h / 2, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
    GXSetCullMode(GX_CULL_FRONT);
    TEXGetGXTexObjFromPalette(*wp->tpl->data, &obj, 2);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, h / 2, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(w, h / 2, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(w, -h / 2, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(0.0f, -h / 2, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXEnd();
}
