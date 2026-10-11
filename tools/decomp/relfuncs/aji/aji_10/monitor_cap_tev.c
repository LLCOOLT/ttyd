// include: driver/mapdrv.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// decl: typedef struct MonitorWork { void* buf; s32 ready; s32 kanbu; } MonitorWork;
// decl: static MonitorWork* monitor_wp;
// decl: void mapObjGetPos(const char* name, Vec* pos);
// proto: void monitor_cap_tev(MapTevCallbackInfo* info);
void monitor_cap_tev(MapTevCallbackInfo* info) {
    Mtx proj;
    Mtx view;
    GXTexObj tex;
    Vec camPos;
    Vec pos;

    if (monitor_wp->ready) {
        GXInitTexObj(&tex, monitor_wp->buf, 0x130, 0xF0, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&tex, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&tex, GX_TEXMAP0);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_HALF, GX_CC_RASC, GX_CC_TEXC);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
        mapObjGetPos("monitor_1", &pos);
        pos.y -= 70.0f;
        camPos = pos;
        camPos.z += 600.0f;
        {
            Vec up = {0.0f, -1.0f, 0.0f};

            C_MTXLightPerspective(proj, 25.0f, 1.2666667f, 0.5f, 0.5f, 0.5f, 0.5f);
            C_MTXLookAt(view, &camPos, &up, &pos);
        }
        PSMTXConcat(proj, view, proj);
        PSMTXConcat(proj, info->mtx, proj);
        GXLoadTexMtxImm(proj, GX_TEXMTX0, GX_MTX3x4);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
        info->tevStage = 1;
        info->texMap = 1;
        info->texCoord = 1;
    }
}
