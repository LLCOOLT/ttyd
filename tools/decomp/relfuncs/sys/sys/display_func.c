// include: dolphin/gx.h
// include: dolphin/mtx.h
// include: sdk/texPalette.h
// include: manager/fontmgr.h
// include: driver/msgdrv.h
// decl: double tan(double x);
// decl: static inline void setChanMatColor(GXColor init, s32 c) { GXColor color = init; color.r = c; color.g = c; color.b = c; GXSetChanMatColor(GX_COLOR0A0, color); }
// decl: static inline void setTevColor(GXColor init) { GXColor color = init; GXSetTevColor(GX_TEVREG0, color); }
// decl: double fmod(double x, double y);
// proto: void display_func(CameraId cameraId, void* param);
void display_func(CameraId cameraId, void* param) {
    SysWork* wp = param;
    CameraEntry* camera = camGetPtr(cameraId);
    s32 i;
    s32 scroll;
    SysChar* chr;
    GXLightObj light;
    Vec lightPos;
    GXTexObj tex;
    Mtx mtx;
    Mtx scale;
    Mtx rot;
    Mtx proj;
    Mtx view;
    Vec eye;
    Vec up;
    Vec target;
    f32 w;
    f32 h;
    f32 size;
    const char* msg;
    char buf[3];
    s32 full;
    s32 rem;

    scroll = wp->scroll;
    wp->scroll++;
    if (scroll > 0x500) {
        scroll -= 0x500;
    }

    {
        GXColor amb = {0x80, 0x80, 0x80, 0xFF};
        GXSetChanAmbColor(GX_COLOR0A0, amb);
    }
    {
        Vec pos = {0.0f, 0.0f, 300.0f};
        lightPos = pos;
    }
    PSMTXMultVec(camera->view, &lightPos, &lightPos);
    GXInitLightPos(&light, lightPos.x, lightPos.y, lightPos.z);
    {
        GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
        GXInitLightColor(&light, white);
    }
    GXInitLightAttn(&light, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    GXLoadLightObjImm(&light, GX_LIGHT0);

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    wp->rot += 2.5f;
    if (wp->rot > 180.0f) {
        wp->rot = 0.0f;
        wp->frame++;
        wp->frame %= 4;
    }
    setChanMatColor((GXColor){0x00, 0x00, 0x00, 0xFF}, getLightColor(90.0f + wp->rot));
    PSMTXTrans(mtx, 0.0f, -40.0f, 0.0f);
    PSMTXRotRad(rot, 'y', 0.017453292f * (90.0f + wp->rot));
    PSMTXConcat(mtx, rot, mtx);
    PSMTXConcat(camera->view, mtx, mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    PSMTXInvXpose(mtx, mtx);
    GXLoadNrmMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    TEXGetGXTexObjFromPalette(*wp->file->data, &tex, (u16)wp->frame);
    GXLoadTexObj(&tex, GX_TEXMAP0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    w = (f32)GXGetTexObjWidth(&tex) / 2;
    h = (f32)GXGetTexObjHeight(&tex) / 2;
    GXPosition3f32(-w / 2, h / 2, 0.0f);
    GXNormal3f32(0.0f, 0.0f, 1.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(w / 2, h / 2, 0.0f);
    GXNormal3f32(0.0f, 0.0f, 1.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(w / 2, -h / 2, 0.0f);
    GXNormal3f32(0.0f, 0.0f, 1.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(-w / 2, -h / 2, 0.0f);
    GXNormal3f32(0.0f, 0.0f, 1.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();

    msg = msgSearch(msg_tbl[wp->type]);
    FontDrawStart();
    full = wp->alpha / 256;
    rem = wp->alpha % 256;
    for (i = 0; i < 44; i += 2) {
        if (i >= strlen(msg)) {
            break;
        }
        *(u16*)buf = *(u16*)&msg[i];
        buf[2] = 0;
        PSMTXTrans(mtx, 0.0f, -40.0f, 0.0f);
        PSMTXRotRad(rot, 'z', 0.017453292f * (-8.181818f * i + wp->angle));
        PSMTXConcat(mtx, rot, rot);
        PSMTXTrans(mtx, 0.0f, 57.5f, 0.0f);
        PSMTXConcat(rot, mtx, mtx);
        PSMTXScale(scale, 0.6f, 0.6f, 0.6f);
        PSMTXConcat(mtx, scale, mtx);
        if (i / 2 < full) {
            FontDrawStart_alpha(0xFF);
            FontDrawStringMtx(mtx, buf);
        } else {
            FontDrawStart_alpha(rem);
            FontDrawStringMtx(mtx, buf);
            break;
        }
    }

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetNumTevStages(4);

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_COMP_RGB8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_COMP_A8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_RED);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP1, GX_TEV_SWAP1);

    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);

    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C0, GX_CC_CPREV, GX_CC_APREV, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    setTevColor((GXColor){0x36, 0x36, 0x36, 0xFF});
    GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);

    GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_ZERO, GX_CC_RASC, GX_CC_CPREV, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_RASA, GX_CA_APREV, GX_CA_ZERO);
    GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);

    size = 44.0f;
    for (i = 0; i < wp->count; i++) {
        chr = &wp->chars[i];
        if (chr->state == 0) {
            break;
        }
        TEXGetGXTexObjFromPalette(*wp->file->data, &tex, (u16)chr->texid);
        GXLoadTexObj(&tex, GX_TEXMAP0);
        TEXGetGXTexObjFromPalette(*wp->file->data, &tex, (u16)niji_tbl[gp->language]);
        GXLoadTexObj(&tex, GX_TEXMAP1);
        setChanMatColor((GXColor){0x00, 0x00, 0x00, 0xFF}, getLightColor(chr->rot));
        if ((u32)gp->language != 0) {
            PSMTXScale(scale, 0.8f, 0.8f, 0.8f);
        } else {
            PSMTXScale(scale, 1.0f, 1.0f, 1.0f);
        }
        PSMTXTrans(mtx, chr->x, chr->y, chr->z);
        PSMTXRotRad(rot, 'y', 0.017453292f * chr->rot);
        PSMTXConcat(scale, mtx, mtx);
        PSMTXConcat(mtx, rot, mtx);
        PSMTXConcat(camera->view, mtx, mtx);
        GXLoadPosMtxImm(mtx, GX_PNMTX0);
        PSMTXInvXpose(mtx, mtx);
        GXLoadNrmMtxImm(mtx, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.z = 1.0f / (f32)tan(MTXDegToRad(25.0f) * 0.5f);
            eye = pos;
        }
        {
            Vec u = {0.0f, 1.0f, 0.0f};
            up = u;
        }
        {
            Vec t = {0.0f, 0.0f, 0.0f};
            target = t;
        }
        C_MTXLightPerspective(proj, 25.0f, 640.0f, 0.5f, 0.5f, 0.5f, 0.5f);
        C_MTXLookAt(view, &eye, &up, &target);
        PSMTXConcat(proj, view, proj);
        if ((u32)gp->language != 0) {
            PSMTXScale(scale, 0.5f, 0.5f, 0.5f);
        } else {
            PSMTXScale(scale, 1.0f, 1.0f, 1.0f);
        }
        PSMTXTrans(mtx, chr->x, chr->y, chr->z);
        PSMTXConcat(scale, mtx, mtx);
        PSMTXConcat(proj, mtx, mtx);
        PSMTXTrans(scale, -scroll, 0.0f, 0.0f);
        PSMTXConcat(mtx, scale, mtx);
        GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(-size / 2, size / 2, 0.0f);
        GXNormal3f32(0.0f, 0.0f, 1.0f);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(size / 2, size / 2, 0.0f);
        GXNormal3f32(0.0f, 0.0f, 1.0f);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(size / 2, -size / 2, 0.0f);
        GXNormal3f32(0.0f, 0.0f, 1.0f);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(-size / 2, -size / 2, 0.0f);
        GXNormal3f32(0.0f, 0.0f, 1.0f);
        GXTexCoord2f32(0.0f, 1.0f);
        GXEnd();
    }
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
}
