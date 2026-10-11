// include: driver/mapdrv.h
// include: dolphin/gx.h
// decl: #define KUSURI_COL (*(GXColor*)g_Kusuri_Col)
// decl: #define KUSURI_SRC ((GXColor*)g_Kusuri_Src_Col)
// decl: #define KUSURI4_NO g_Kusuri4_No[0]
// proto: void kusuri_4_color_tev(MapTevCallbackInfo* info);
void kusuri_4_color_tev(MapTevCallbackInfo* info) {
    GXTevStageID stage = info->tevStage;

    GXSetTevOrder(stage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(stage, GX_CC_C0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevAlphaIn(stage, GX_CA_APREV, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevColor(GX_TEVREG0, KUSURI_SRC[KUSURI4_NO]);
    info->tevStage++;
}
