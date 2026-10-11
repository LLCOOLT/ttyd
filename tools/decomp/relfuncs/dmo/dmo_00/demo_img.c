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
// proto: void demo_img(CameraId cameraId, void* param);
void demo_img(CameraId cameraId, void* param) {
    CameraEntry* cam = camGetPtr(8);
    CameraEntry* cam2;
    Mtx mtx;
    Mtx scale;
    GXTexObj obj;
    f32 proj[7];
    f32 vp[6];
    Vec p0;
    Vec p1;
    Vec p2;
    Vec p3;
    f32 w;
    f32 h;

    if (wp->page != -1) {
        GXSetProjection(cam->projection, cam->projType);
        GXSetViewport(0.0f, 0.0f, 608.0f, 480.0f, 0.0f, 1.0f);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetZCompLoc(GX_TRUE);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetChanMatColor(GX_COLOR0A0, (GXColor){0xFF, 0xFF, 0xFF, 255.0f * (1.0f - wp->fade)});
        TEXGetGXTexObjFromPalette(*wp->tpl->data, &obj, wp->page + 8);
        GXLoadTexObj(&obj, GX_TEXMAP0);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        PSMTXTrans(mtx, wp->x, wp->y, 0.0f);
        PSMTXScale(scale, wp->scale, wp->scale, wp->scale);
        PSMTXConcat(mtx, scale, mtx);
        PSMTXConcat(cam->view, mtx, mtx);
        GXLoadPosMtxImm(mtx, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        GXSetCullMode(GX_CULL_BACK);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXGetViewportv(vp);
        GXGetProjectionv(proj);
        w = 202.66667f;
        h = 160.0f;
        GXProject(-w / 2, h / 2 + 35.0f, 0.0f, mtx, proj, vp, &p0.x, &p0.y, &p0.z);
        GXProject(w / 2, h / 2 + 35.0f, 0.0f, mtx, proj, vp, &p1.x, &p1.y, &p1.z);
        GXProject(w / 2, -h / 2 + 35.0f, 0.0f, mtx, proj, vp, &p2.x, &p2.y, &p2.z);
        GXProject(-w / 2, -h / 2 + 35.0f, 0.0f, mtx, proj, vp, &p3.x, &p3.y, &p3.z);
        cam2 = camGetPtr(4);
        cam2->viewport[0] = p0.x;
        cam2->viewport[1] = p0.y;
        cam2->viewport[2] = p2.x - p0.x;
        cam2->viewport[3] = p2.y - p0.y;
        cam2 = camGetPtr(6);
        cam2->viewport[0] = 0.0f;
        cam2->viewport[1] = 0.0f;
        cam2->viewport[2] = 608.0f;
        cam2->viewport[3] = 480.0f;
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(-w / 2, h / 2 + 35.0f, 0.0f);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(w / 2, h / 2 + 35.0f, 0.0f);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(w / 2, -h / 2 + 35.0f, 0.0f);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(-w / 2, -h / 2 + 35.0f, 0.0f);
        GXTexCoord2f32(0.0f, 1.0f);
        GXEnd();
    }
}
