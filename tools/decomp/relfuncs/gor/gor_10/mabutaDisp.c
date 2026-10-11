// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: evt/evt_cmd.h
// include: dolphin/gx.h
// proto: void mabutaDisp(CameraId camera, void* param);
void mabutaDisp(CameraId camera, void* param) {
    f32 h = evtGetFloat(NULL, GW(1));
    CameraEntry* cam = camGetPtr(camera);

    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, (GXColor){0x00, 0x00, 0x00, 0xFF});
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetCullMode(GX_CULL_BACK);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 8);
    GXPosition3s16(-304, 240, 0);
    GXPosition3s16(304, 240, 0);
    GXPosition3s16(304, (s16)(240.0f - h), 0);
    GXPosition3s16(-304, (s16)(240.0f - h), 0);
    GXPosition3s16(-304, (s16)(-240.0f + h), 0);
    GXPosition3s16(304, (s16)(-240.0f + h), 0);
    GXPosition3s16(304, -240, 0);
    GXPosition3s16(-304, -240, 0);
    GXEnd();
}
