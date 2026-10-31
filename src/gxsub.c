#include "gxsub.h"
#ifdef VERSION_G8ME01_DEMO
#include "driver/camdrv.h"
#endif

//.sdata
f32 queen_uv[4] = {0.0f, -0.0016000001f, 0.0f, -0.00080000004f};

#ifdef VERSION_G8ME01_DEMO
// The demo still has the 2D textured-quad helpers seq_demo draws with (cut from retail).

//.sdata
static s32 gxsubMode ATTRIBUTE_ALIGN(32) = 8; // last GX setup applied by gxsubChgMode
static u8 gxsubWhiteTex[4] ATTRIBUTE_ALIGN(32) = {0xFF, 0xFF, 0x00, 0x00}; // 1x1 I4 texel used when no texture is set

//.sbss
static BOOL gxsubAlphaTest;
static BOOL gxsubTexAlphaOff;
static GXTexObj* gxsubTexObj;

BOOL gxsubChgMode(s32 mode) {
    if (mode != gxsubMode) {
        gxsubMode = mode;
        return TRUE;
    }
    return FALSE;
}

void gxsubDrawQuad(s32 x, s32 y, s32 w, s32 h, GXColor* color) {
    Mtx mtx;
    GXTexObj obj;
    GXColor c;
    CameraEntry* cam = camGetCurPtr();

    PSMTXIdentity(mtx);
    PSMTXConcat(cam->view, mtx, mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    if (gxsubChgMode(5)) {
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C0, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
        GXSetZCompLoc(GX_TRUE);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
        GXSetCullMode(GX_CULL_NONE);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    }
    if (gxsubTexObj) {
        GXLoadTexObj(gxsubTexObj, GX_TEXMAP0);
    } else {
        GXInitTexObj(&obj, gxsubWhiteTex, 1, 1, GX_TF_I4, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXLoadTexObj(&obj, GX_TEXMAP0);
    }
    if (gxsubTexAlphaOff) {
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    }
    if (gxsubAlphaTest) {
        GXSetZCompLoc(GX_FALSE);
        GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
        GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
    }
    c = *color;
    GXSetTevColor(GX_TEVREG0, c);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    if (camGetCurPtr() == camGetPtr(CAMERA_2D)) {
        h *= -1;
    }
    GXPosition3s16(x, y, 0);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3s16(x + w, y, 0);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3s16(x + w, y + h, 0);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3s16(x, y + h, 0);
    GXTexCoord2f32(0.0f, 1.0f);
}

void gxsubSetTexObj(GXTexObj* obj) {
    gxsubTexObj = obj;
}
#endif
