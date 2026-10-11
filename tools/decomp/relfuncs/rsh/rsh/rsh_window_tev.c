// include: dolphin/gx.h
// include: dolphin/mtx.h
// include: memory.h
// include: driver/mapdrv.h
// include: driver/camdrv.h
// include: mario/mariost.h
// decl: double tan(double x);
// proto: void rsh_window_tev(MapTevCallbackInfo* info);
void rsh_window_tev(MapTevCallbackInfo* info) {
    s32 tevStage = info->tevStage;
    s32 texMap = info->texCoord;
    s32 texCoord = info->texMap;
    s32 field_0x18 = info->field_0x18;
    MapObject* obj = *(MapObject**)info->field_0x0;
    u16 x0, y0, x1, y1;
    s32 height, width;
    s32 halfHeight, halfWidth;
    void* buf;
    GXTexObj tex;
    Mtx mtx;
    f32 t;

    if (obj->flags & 0x20) {
        while ((obj = obj->parent) != NULL) {
            if (obj->flags & 0x10) {
                if (!(obj->flags & 0x20000000)) {
                    obj->flags |= 0x20000000;
                    return;
                }
                x0 = obj->screenRect[0];
                y0 = obj->screenRect[1];
                x1 = obj->screenRect[2];
                y1 = obj->screenRect[3];
                break;
            }
        }
    } else {
        if (!(obj->flags & 0x20000000)) {
            obj->flags |= 0x20000000;
            return;
        }
        x0 = obj->screenRect[0];
        y0 = obj->screenRect[1];
        x1 = obj->screenRect[2];
        y1 = obj->screenRect[3];
    }
    if (x0 == 0x3FF || y0 == 0x3FF || x1 == 0x3FF || y1 == 0x3FF) {
        return;
    }
    if (x0 == 0 && y0 == 0 && x1 == 0 && y1 == 0) {
        return;
    }
    x0 -= x0 & 1;
    y0 -= y0 & 1;
    x1 += x1 & 1;
    y1 += y1 & 1;
    if (x1 > gp->fbWidth) {
        x1 = gp->fbWidth;
    }
    if (y1 > gp->efbHeight) {
        y1 = gp->efbHeight;
    }
    width = x1 - x0;
    height = y1 - y0;
    halfWidth = width / 2;
    halfHeight = height / 2;
    buf = smartAlloc(GXGetTexBufferSize(halfWidth, halfHeight, GX_TF_RGB5A3, GX_FALSE, 0), 3)->address;
    GXSetTexCopySrc(x0, y0, width, height);
    GXSetTexCopyDst(halfWidth, halfHeight, GX_TF_RGB5A3, GX_TRUE);
    GXCopyTex(buf, GX_FALSE);
    GXInvalidateTexAll();
    GXPixModeSync();
    GXTexModeSync();
    GXInitTexObj(&tex, buf, halfWidth, halfHeight, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&tex, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    t = tan(6.2831855f * (camGetPtr(4)->fovY / 2.0f) / 360.0f);
    C_MTXLightFrustum(mtx, gp->efbHeight / 2 - y1, gp->efbHeight / 2 - y0, x0 - gp->fbWidth / 2,
                      x1 - gp->fbWidth / 2, gp->efbHeight / 2.0f / t, 0.5f, 0.5f, 0.4f, 0.6f);
    PSMTXConcat(mtx, camGetCurPtr()->view, mtx);
    PSMTXConcat(mtx, info->mtx, mtx);
    GXSetTexCoordGen2(texCoord, GX_TG_MTX3x4, GX_TG_POS, rsh_texmtx_tbl[texMap], GX_FALSE, GX_PTIDENTITY);
    GXLoadTexMtxImm(mtx, rsh_texmtx_tbl[texMap], GX_MTX3x4);
    GXLoadTexObj(&tex, texMap);
    GXSetTevOrder(tevStage, texCoord, texMap, GX_COLOR_NULL);
    GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
    GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevKColorSel(tevStage, GX_TEV_KCSEL_3_4);
    tevStage++;
    texMap++;
    texCoord++;
    info->tevStage = tevStage;
    info->texMap = texCoord;
    info->field_0x18 = field_0x18;
    info->texCoord = texMap;
}
