// include: driver/mapdrv.h
// include: dolphin/gx.h
// decl: typedef struct DoorColorWork { GXColor color; GXColor color2; } DoorColorWork;
// decl: DoorColorWork* _door;
// proto: void _door_color2_tev(MapTevCallbackInfo* info);
void _door_color2_tev(MapTevCallbackInfo* info) {
    GXTevStageID stage = info->tevStage;
    DoorColorWork* door = _door;

    GXSetTevOrder(stage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColor(GX_TEVREG0, door->color2);
    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_CPREV, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
    info->tevStage++;
}
