// include: memory.h
// include: mario/mariost.h
// include: driver/mapdrv.h
// include: dolphin/gx.h
// include: dolphin/os.h
// decl: double sin(double x);
// decl: static smartEntry* ind_lp;
// proto: void sun_tev(MapTevCallbackInfo* info);
void sun_tev(MapTevCallbackInfo* info) {
    s32 stage = info->tevStage;
    s32 texMap = info->texCoord;
    s32 texCoord = info->texMap;
    s32 indStage = info->field_0x18;
    GXTexObj obj;
    f32 mtx[2][3];
    u8* buf;
    s32 i;
    s32 j;

    // a scrolling sine-wave warp texture for the sun's heat haze
    if (ind_lp == NULL) {
        ind_lp = smartAlloc(GXGetTexBufferSize(64, 64, GX_TF_IA8, GX_FALSE, 0), 1);
    }
    buf = ind_lp->address;
    for (i = 0; i < 64; i++) {
        for (j = 0; j < 64; j++) {
            f32 v = sin(31.41592f * j / 64 - gp->retraceCount / 8.0f);
            u8* p = &buf[((i / 4) << 5) + ((j / 4) << 9) + (((i % 4) + ((j % 4) << 2)) << 1)];

            p[0] = 3.0f * v + 128.0f;
            p[1] = 0x80;
        }
    }
    DCFlushRange(buf, 0x2000);
    GXInitTexObj(&obj, buf, 64, 64, GX_TF_IA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(&obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, texMap);
    mtx[0][0] = 0.5f;
    mtx[0][1] = 0.0f;
    mtx[0][2] = 0.0f;
    mtx[1][0] = 0.0f;
    mtx[1][1] = 0.5f;
    mtx[1][2] = 0.0f;
    GXSetIndTexMtx(GX_ITM_0, mtx, 1);
    GXSetIndTexOrder(indStage, GX_TEXCOORD0, texMap);
    GXSetIndTexCoordScale(indStage, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, indStage, GX_TRUE, GX_FALSE, GX_ITM_0);
    info->tevStage = stage;
    info->texMap = texCoord;
    info->field_0x18 = indStage + 1;
    info->texCoord = texMap + 1;
}
