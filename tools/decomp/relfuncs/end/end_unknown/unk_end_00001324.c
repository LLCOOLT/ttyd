// include: driver/animdrv.h
// include: driver/npcdrv.h
// include: driver/dispdrv.h
// include: driver/camdrv.h
// include: driver/mapdrv.h
// include: driver/msgdrv.h
// include: driver/windowdrv.h
// include: driver/swdrv.h
// include: manager/evtmgr.h
// include: manager/evtmgr_cmd.h
// include: manager/filemgr.h
// include: manager/fontmgr.h
// include: mario/mariost.h
// include: memory.h
// include: string.h
// include: stdio.h
// include: pmario_sound.h
// include: system.h
// include: sdk/texPalette.h
// include: data/mapdata.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// decl: #define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct EndMoa { Vec pos; s32 chain; s32 idx; } EndMoa;
// decl: typedef struct EndExtData { const char* anim; const char* pose; f32 speed; } EndExtData;
// decl: typedef struct EndWork { FileEntry* tpl; s32 mode; s32 alpha; s32 alpha2; s32 tevAlpha; s32 win1[3]; s32 win2[3]; s32 field_0x2c; s32 pos; EventEntry* evt; } EndWork;
// decl: typedef struct CreditMsg { s32 field_0x0; s32 pos; s32 type; const char* msg1[3]; const char* msg2[3]; } CreditMsg;
// decl: typedef struct CreditNpc { const char* agb; const char* anim; s32* evt; } CreditNpc;
// decl: typedef struct CreditActor { s32 state; s32 poseId; f32 angle; f32 limit; s32 pos; Mtx mtx; } CreditActor;
// decl: EndWork unk_end_bss00000010;
// decl: s32 (*unk_end_bss0000000c)[2];
// decl: s32* unk_end_bss00000008;
// decl: EndExtData* unk_end_bss00000004;
// decl: EndMoa* unk_end_bss00000000;
// decl: extern EndWork* dat_ptr_end_00003218;
// decl: extern CreditMsg unk_end_0000321c[50];
// decl: extern CreditNpc R_credits_npc_info[152];
// decl: extern const char* dat_ptr_end_00005034;
// decl: extern const char* dat_ptr_end_00005038;
// decl: extern const char* g_moamoa_chain_tbl[][2];
// decl: extern const s32 dat_80419a28;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: void extReset(void);
// decl: void extLoadRenderMode(void);
// decl: void extLoadVertex(void);
// decl: void extLoadTexture(void);
// decl: void extLoadTev(void);
// decl: void extDraw(void);
// decl: void extLoadTextureExit(void);
// decl: int rand(void);
// decl: double tan(double x);
// decl: static inline f32 tanf(f32 x) { return tan(x); }
// decl: s32 EXIGetType(s32 chan, u32 dev, u32* type);
// decl: void L_animPoseWorldPositionEvalOff(s32 poseId);
// decl: void animPoseVivianMain(s32 poseId, Vec* pos);
// decl: s32 msgWindow_Entry(const char* msg, s32 a, s32 b);
// decl: void msgWindow_Continue(s32 id);
// decl: void JUTFont_Free(void);
// decl: void JUTFontSetup(s32 mode);
// proto: void unk_end_00001324(CameraId cameraId, void* param);
void unk_end_00001324(CameraId cameraId, void* param) {
    s32 i;
    f32 w;
    f32 h;
    CameraEntry* cam = camGetPtr(cameraId);
    s32 id = evtGetValue(NULL, GW(11));
    s32 pos = evtGetValue(NULL, GW(12));
    Vec camPos;
    Vec up;
    Vec target;
    GXTexObj obj;
    Mtx mtx;
    Mtx scale;
    Mtx lookAt;

    if (dat_ptr_end_00003218->tpl == NULL) {
        return;
    }
    if (id >= ((TEXPalette*)*dat_ptr_end_00003218->tpl->data)->numDescriptors) {
        return;
    }
    if (id == 9 && swGet(0x5E7)) {
        id = 53;
    }
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, (GXColor){0xFF, 0xFF, 0xFF, dat_ptr_end_00003218->alpha});
    switch (dat_ptr_end_00003218->mode) {
        case 0:
            TEXGetGXTexObjFromPalette(*dat_ptr_end_00003218->tpl->data, &obj, id);
            GXLoadTexObj(&obj, GX_TEXMAP0);
            break;
        case 1:
            GXSetTevColor(GX_TEVREG0, (GXColor){0, 0, 0, dat_ptr_end_00003218->tevAlpha});
            TEXGetGXTexObjFromPalette(*dat_ptr_end_00003218->tpl->data, &obj, 49);
            GXLoadTexObj(&obj, GX_TEXMAP0);
            TEXGetGXTexObjFromPalette(*dat_ptr_end_00003218->tpl->data, &obj, 50);
            GXLoadTexObj(&obj, GX_TEXMAP1);
            break;
        case 2:
            GXSetTevColor(GX_TEVREG0, (GXColor){0, 0, 0, dat_ptr_end_00003218->tevAlpha});
            TEXGetGXTexObjFromPalette(*dat_ptr_end_00003218->tpl->data, &obj, 50);
            GXLoadTexObj(&obj, GX_TEXMAP0);
            TEXGetGXTexObjFromPalette(*dat_ptr_end_00003218->tpl->data, &obj, 51);
            GXLoadTexObj(&obj, GX_TEXMAP1);
            break;
    }
    switch (dat_ptr_end_00003218->mode) {
        case 0:
            GXSetNumTevStages(1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
            GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
            break;
        default:
            GXSetNumTevStages(2);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);
            GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            break;
    }
    switch (pos) {
        case 0:
            PSMTXTrans(mtx, 51.0f, 30.0f, -30.0f);
            break;
        case 1:
            PSMTXTrans(mtx, -51.0f, -30.0f, -30.0f);
            break;
        case 2:
            PSMTXTrans(mtx, -51.0f, 30.0f, -30.0f);
            break;
        case 3:
            PSMTXTrans(mtx, 51.0f, -30.0f, -30.0f);
            break;
        case 4:
            PSMTXTrans(mtx, 0.0f, 30.0f, -30.0f);
            break;
    }
    PSMTXScale(scale, 0.6f, 0.6f, 1.0f);
    PSMTXConcat(mtx, scale, mtx);
    PSMTXConcat(cam->view, mtx, mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            GXSetChanMatColor(GX_COLOR0A0, (GXColor){0xFF, 0xFF, 0xFF, dat_ptr_end_00003218->alpha});
            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        } else {
            GXSetChanMatColor(GX_COLOR0A0, (GXColor){0, 0, 0, dat_ptr_end_00003218->alpha});
            GXSetZMode(GX_TRUE, GX_GREATER, GX_FALSE);
        }
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        w = GXGetTexObjWidth(&obj);
        h = GXGetTexObjHeight(&obj);
        GXPosition3f32(-w / 2.0f, h / 2.0f, 0.0f);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(w / 2.0f, h / 2.0f, 0.0f);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(w / 2.0f, -h / 2.0f, 0.0f);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(-w / 2.0f, -h / 2.0f, 0.0f);
        GXTexCoord2f32(0.0f, 1.0f);
        GXEnd();
    }
    if (dat_ptr_end_00003218->alpha2 > 0) {
        f32 w2;
        f32 h2;

        camPos = (Vec){0.0f, 0.0f, 240.0f / tanf(0.21816616f)};
        up = (Vec){0.0f, 1.0f, 0.0f};
        target = (Vec){0.0f, 0.0f, 0.0f};
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        TEXGetGXTexObjFromPalette(*dat_ptr_end_00003218->tpl->data, &obj, 52);
        GXLoadTexObj(&obj, GX_TEXMAP0);
        GXSetChanMatColor(GX_COLOR0A0, (GXColor){0xFF, 0xFF, 0xFF, dat_ptr_end_00003218->alpha2});
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        C_MTXLookAt(lookAt, &camPos, &up, &target);
        PSMTXTrans(mtx, 0.0f, -138.0f, 0.0f);
        PSMTXScale(scale, 1.0f, 1.0f, 1.0f);
        PSMTXConcat(lookAt, mtx, mtx);
        PSMTXConcat(mtx, scale, mtx);
        GXLoadPosMtxImm(mtx, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        w2 = GXGetTexObjWidth(&obj);
        h2 = GXGetTexObjHeight(&obj);
        GXPosition3f32(-w2 / 2.0f, h2 / 2.0f, 0.0f);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(w2 / 2.0f, h2 / 2.0f, 0.0f);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(w2 / 2.0f, -h2 / 2.0f, 0.0f);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(-w2 / 2.0f, -h2 / 2.0f, 0.0f);
        GXTexCoord2f32(0.0f, 1.0f);
        GXEnd();
    }
}
