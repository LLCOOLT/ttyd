// include: memory.h
// include: driver/mapdrv.h
// include: dolphin/gx.h
// decl: typedef struct GansWork { smartEntry* buf; GXTexObj tex; s32 onoff; s32 alpha; s32 ready; } GansWork;
// decl: GansWork* gans_wp;
// proto: void monitor_tev(MapTevCallbackInfo* info);
void monitor_tev(MapTevCallbackInfo* info) {
    if (gans_wp->ready) {
        GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, GX_PTIDENTITY);
        GXLoadTexObj(smartTexObj(&gans_wp->tex, &gans_wp->buf->address), GX_TEXMAP1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_TEXC, GX_CC_CPREV, GX_CC_A0, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        {
            GXColor color = {0xFF, 0xFF, 0xFF, 0x00};
            GXColor tmp;

            color.a = gans_wp->alpha;
            tmp = color;
            GXSetTevColor(GX_TEVREG0, tmp);
        }
        info->tevStage = 2;
        info->texMap = 2;
        info->texCoord = 2;
    }
}
