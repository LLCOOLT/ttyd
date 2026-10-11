// include: manager/evtmgr_cmd.h
// include: driver/mapdrv.h
// include: dolphin/gx.h
// proto: void map_color_tev(MapTevCallbackInfo* info);
void map_color_tev(MapTevCallbackInfo* info) {
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    if (evtGetValue(NULL, LSWF(10))) {
        GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};

        GXSetTevColor(GX_TEVREG0, color);
    } else {
        GXColor color = {0x00, 0x00, 0x00, 0xFF};

        GXSetTevColor(GX_TEVREG0, color);
    }
    info->tevStage = 1;
    info->texMap = 0;
    info->texCoord = 0;
}
