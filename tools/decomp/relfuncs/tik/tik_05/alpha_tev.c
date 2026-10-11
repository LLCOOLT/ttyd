// include: driver/mapdrv.h
// include: dolphin/gx.h
// decl: static u8* _ap;
// proto: void alpha_tev(MapTevCallbackInfo* info);
void alpha_tev(MapTevCallbackInfo* info) {
    s32 stage = info->tevStage;
    u8* alpha = _ap;

    GXSetTevOrder(stage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColor(GX_TEVREG0, (GXColor){0, 0, 0, *alpha});
    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
    info->tevStage++;
}
