// include: driver/mapdrv.h
// include: dolphin/gx.h
// decl: s32 gans_alpha;
// proto: static inline void cb_set_color(u8 a) {
    GXColor color = {255, 255, 255, 0};

    color.a = a;
    GXSetTevColor(GX_TEVREG0, color);
}

static void callback(MapTevCallbackInfo* info) {
    s32 stage = info->tevStage;
    s32 texCoord = info->texCoord;
    s32 texMap = info->texMap;
    s32 field_0x18 = info->field_0x18;

    cb_set_color(gans_alpha);
    GXSetTevOrder(stage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(stage, GX_CC_CPREV, GX_CC_C0, GX_CC_A0, GX_CC_ZERO);
    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevSwapMode(stage, GX_TEV_SWAP0, GX_TEV_SWAP0);
    info->tevStage = stage + 1;
    info->texMap = texMap;
    info->field_0x18 = field_0x18;
    info->texCoord = texCoord;
}
