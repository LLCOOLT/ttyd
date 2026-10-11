#include "driver/envdrv.h"
#include "driver/arcdrv.h"
#include "driver/dispdrv.h"
#include "mario/mariost.h"
#include "manager/dvdmgr.h"
#include "system.h"
#include "texPalette.h"
#include <dolphin/dvd.h>
#include <string.h>

extern int sprintf(char* str, const char* format, ...);
extern GlobalWork* gp;

//.data
EnvironmentGlare envGlare0 = {
    GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_TEV_KCSEL_K1_A, GX_TEV_KCSEL_K0_A, 5.25f, 16,
    {
        {-1.0f, 0.0f}, {-3.0f, 0.0f}, {-5.0f, 0.0f}, {-7.0f, 0.0f},
    {1.0f, 0.0f}, {3.0f, 0.0f}, {5.0f, 0.0f}, {7.0f, 0.0f},
    {0.0f, -1.0f}, {0.0f, -3.0f}, {0.0f, -5.0f}, {0.0f, -7.0f},
    {0.0f, 1.0f}, {0.0f, 3.0f}, {0.0f, 5.0f}, {0.0f, 7.0f},
}
};

EnvironmentGlare envGlare1 = {
    GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_TEV_KCSEL_K1_A, GX_TEV_KCSEL_1, 3.5f, 8,
    {
        {-1.41419994831f, -1.41419994831f}, {0.0f, -1.0f}, {1.41419994831f, -1.41419994831f}, {-1.0f, 0.0f},
    {1.0f, 0.0f}, {-1.41419994831f, 1.41419994831f}, {0.0f, 1.0f}, {1.41419994831f, 1.41419994831f},
}
};

EnvironmentGlare envGlare2 = {
    GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_TEV_KCSEL_K1_A, GX_TEV_KCSEL_3_4, 3.5f, 52,
    {
        {0.0f, -5.0f}, {-1.0f, -4.0f}, {0.0f, -4.0f}, {1.0f, -4.0f},
    {-2.0f, -3.0f}, {-1.0f, -3.0f}, {0.0f, -3.0f}, {1.0f, -3.0f},
    {2.0f, -3.0f}, {-3.0f, -2.0f}, {-2.0f, -2.0f}, {-1.0f, -2.0f},
    {0.0f, -2.0f}, {1.0f, -2.0f}, {2.0f, -2.0f}, {3.0f, -2.0f},
    {-3.0f, -1.0f}, {-2.0f, -1.0f}, {-1.0f, -1.0f}, {0.0f, -1.0f},
    {1.0f, -1.0f}, {2.0f, -1.0f}, {3.0f, -1.0f}, {-3.0f, 0.0f},
    {-2.0f, 0.0f}, {-1.0f, 0.0f}, {3.0f, 0.0f}, {2.0f, 0.0f},
    {1.0f, 0.0f}, {-3.0f, 1.0f}, {-2.0f, 1.0f}, {-1.0f, 1.0f},
    {0.0f, 1.0f}, {1.0f, 1.0f}, {2.0f, 1.0f}, {3.0f, 1.0f},
    {-3.0f, 2.0f}, {-2.0f, 2.0f}, {-1.0f, 2.0f}, {0.0f, 2.0f},
    {1.0f, 2.0f}, {2.0f, 2.0f}, {3.0f, 2.0f}, {-2.0f, 3.0f},
    {-1.0f, 3.0f}, {0.0f, 3.0f}, {1.0f, 3.0f}, {2.0f, 3.0f},
    {-1.0f, 4.0f}, {0.0f, 4.0f}, {1.0f, 4.0f}, {0.0f, 5.0f},
}
};

EnvironmentGlare envGlare3 = {
    GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_TEV_KCSEL_K1_A, GX_TEV_KCSEL_1, 3.5f, 16,
    {
        {0.0f, -4.0f}, {-1.0f, -3.0f}, {1.0f, -3.0f}, {-2.0f, -2.0f},
    {2.0f, -2.0f}, {-3.0f, -1.0f}, {3.0f, -1.0f}, {-3.0f, 0.0f},
    {3.0f, 0.0f}, {-3.0f, 1.0f}, {3.0f, 1.0f}, {-2.0f, 2.0f},
    {2.0f, 2.0f}, {-1.0f, 3.0f}, {1.0f, 3.0f}, {0.0f, 4.0f},
}
};

//.bss
static EnvironmentWork work[2];

//.sbss
s32 v_count; //TODO: re-type all these
s32 u2;
s32 u1;
s32 a;
s32 frame_cnt;
s32 tpl_ok;
TEXPalette* env_tpl;

//local prototypes
void _callback(s32 result, DVDFileInfo* fileInfo);
void envCapture(CameraId camId, void* param);
void envCapture2(CameraId camId, void* param);
void envDisp(CameraId camId, void* param);
void envDisp2(CameraId camId, void* param);
void envDisp_DepthOfField(void);
void envDisp_Blur(void);

//there is no function so we'll make a macro
#define envGetWork() (gp->inBattle ? &work[1] : &work[0])

static void _callback(s32 result, DVDFileInfo* fileInfo) {
    DVDEntry* handle = fileInfo->cb.userData;

    UnpackTexPalette(env_tpl);
    DVDMgrClose(handle);
    tpl_ok = TRUE;
}

void envInit(void) {
    memset(&work[0], 0, sizeof(EnvironmentWork));
    memset(&work[1], 0, sizeof(EnvironmentWork));
    env_tpl = NULL;
    tpl_ok = FALSE;
}

void envReInit(void) {
    EnvironmentWork* wp = envGetWork();
    memset(wp, 0, sizeof(EnvironmentWork));
}

void envTexSetup(void) { //1:1
    DVDEntry* entry;
    TEXPalette* tpl;
    char path[128];
    u32 size;

    env_tpl = NULL;
    tpl = arcOpen("env.tpl", 0, 0);
    env_tpl = tpl;
    if (!tpl) {
        sprintf(path, "%s/env.tpl", getMarioStDvdRoot());
        entry = DVDMgrOpen(path, 2, 0);
        size = DVDMgrGetLength(entry);
        env_tpl = __memAlloc(HEAP_DEFAULT, OSRoundUp32B(size));
        entry->info.cb.userData = entry;
        DVDMgrReadAsync(entry, env_tpl, size, 0, _callback);
    }
    else {
        UnpackTexPalette(tpl);
        tpl_ok = 1;
    }
}

void envCapture(CameraId camId, void* param) { //1:1
    EnvironmentWork* wp = envGetWork();
    u16 var0, var1, var2, var3;
    u32 size;
    
    var0 = gp->fbWidth;
    var1 = gp->efbHeight;
    var2 = (u16)(((u32)var0 & 0xFFFF) / 2);
    var3 = (u16)(((u32)var1 & 0xFFFF) / 2);
    if (wp->flags & 1) {
        GXSetTexCopySrc(0, 0, gp->fbWidth, gp->efbHeight);
        GXSetTexCopyDst(var2, var3, GX_TF_RGBA8, GX_TRUE);
        size = GXGetTexBufferSize(var2, var3, GX_TF_RGBA8, GX_FALSE, 0);
        wp->capture = smartAlloc(size, 3);
        GXCopyTex(wp->capture->address, GX_FALSE);
        GXPixModeSync();
        GXInitTexObj(&wp->captureObj, wp->capture->address, var2, var3, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&wp->captureObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    }
    if (wp->flags & 2) {
        GXSetTexCopySrc(0, 0, var0, var1);
        GXSetTexCopyDst(var2, var3, GX_CTF_Z8M, GX_TRUE);
        size = GXGetTexBufferSize(var2, var3, GX_CTF_Z8M, GX_FALSE, 0);
        wp->capture2 = smartAlloc(size, 3);
        GXCopyTex(wp->capture2->address, 0);
        GXPixModeSync();
        GXInitTexObj(&wp->captureObj2, wp->capture2->address, var2, var3, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&wp->captureObj2, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    }
}

void envCapture2(CameraId camId, void* param) { //1:1
    EnvironmentWork* wp = envGetWork();
    u16 var0, var1;

    var0 = (u16)(((u32)gp->fbWidth & 0xFFFF) / 2);
    var1 = (u16)(((u32)gp->efbHeight & 0xFFFF) / 2);
    if (wp->flags & 4) {
        GXSetTexCopySrc(0, 0, gp->fbWidth, gp->efbHeight);
        GXSetTexCopyDst(var0, var1, GX_TF_RGB565, GX_TRUE);
        GXCopyTex(wp->envBlur, GX_FALSE);
        GXPixModeSync();
        GXInitTexObj(&wp->envBlurObj, wp->envBlur, var0, var1, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&wp->envBlurObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    }
    if (wp->flags & 0x40000000) {
        if ((wp->unk98 & 1) && (wp->flags & 8)) {
            wp->flags &= ~4;
        }
        wp->flags |= 8;
    }
}

void envDisp(CameraId camId, void *param) {
    f32 vp[GX_VIEWPORT_SZ];
    f32 pm[GX_PROJECTION_SZ];

    GXGetViewportv(vp);
    GXGetProjectionv(pm);
    //envDisp_DepthOfField();
    //envDisp_Blur();
    //envDisp_FF();
    GXSetViewport(vp[0], vp[1], vp[2], vp[3], vp[4], vp[5]);
    GXSetProjectionv(pm);
}

void envDisp2(CameraId camId, void *param) { //almost 1:1, needs extra addi
    f32 vp[GX_VIEWPORT_SZ];
    f32 pm[GX_PROJECTION_SZ];
    EnvironmentWork* wp;
    EnvironmentGlareFilter* filter;

    GXGetViewportv(vp);
    GXGetProjectionv(pm);
    wp = envGetWork();
    filter = &wp->filter; //CodeWarrior is very good compiler, yesyes
    if (wp->flags & 0x20000000) {
        switch (filter->type) {
            case 0:
                break;
            case 1:
                envGlare(&envGlare0);
                break;
            case 2:
                envGlare(&envGlare1);
                break;
            case 3:
                envGlare(&envGlare2);
                break;
            case 4:
                envGlare(&envGlare3);
                break;
        }
    }
    GXSetViewport(vp[0], vp[1], vp[2], vp[3], vp[4], vp[5]);
    GXSetProjectionv(pm);
}

void envMain(void) {
    dispEntry(CAMERA_3D, 20.0f, 7, envCapture, NULL);
    dispEntry(CAMERA_3D, 10.0f, 7, envDisp, NULL);
    dispEntry(CAMERA_3D, 0.0f, 7, envCapture2, NULL);
    dispEntry(CAMERA_3D, 5000.0f, 8, envDisp2, NULL);
}







#define PI 3.141592653589793f
#define TWO_PI 6.283185307179586f
const s32 texmtx_tbl[] = {30, 33, 36, 39, 42, 45, 48, 51, 54, 57};

static inline f32 env_sin(f32 x) {
    f32 a = 0.00761f;
    f32 b = 0.16605f;
    f32 c = 1.0f;
    f32 y;
    f32 x2;

    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
            a = a * x;
        }
        else {
            y = 1.5707964f - (x - 1.5707964f);
            x2 = y * y;
            a = a * x2 - b;
            a = a * x2 + c;
            a = a * y;
        }
    }
    else if (x < 4.712389f) {
        y = x - 3.1415927f;
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
        a = a * y;
        a = -a;
    }
    else {
        y = 1.5707964f - (x - 4.712389f);
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
        a = a * y;
        a = -a;
    }
    return a;
}

static inline f32 env_cos(f32 x) {
    f32 a = 0.03705f;
    f32 b = 0.4967f;
    f32 c = 1.0f;
    f32 y;
    f32 x2;

    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
        }
        else {
            y = 1.5707964f - (x - 1.5707964f);
            x2 = y * y;
            a = a * x2 - b;
            a = a * x2 + c;
            a = -a;
        }
    }
    else if (x < 4.712389f) {
        y = x - 3.1415927f;
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
        a = -a;
    }
    else {
        y = 1.5707964f - (x - 4.712389f);
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
    }
    return a;
}

#define WGPIPE_F32(x) (*(volatile f32*)0xCC008000 = (x))

#define DOF_QUAD(g, half)                                                               \
    GXPosition3f32(-(s32)(g)->fbWidth / (half), (g)->efbHeight / (half), 0.0f);         \
    GXTexCoord2f32(0.0f, 0.0f);                                                         \
    GXPosition3f32((g)->fbWidth / (half), (g)->efbHeight / (half), 0.0f);               \
    GXTexCoord2f32(1.0f, 0.0f);                                                         \
    GXPosition3f32((g)->fbWidth / (half), -(s32)(g)->efbHeight / (half), 0.0f);         \
    GXTexCoord2f32(1.0f, 1.0f);                                                         \
    GXPosition3f32(-(s32)(g)->fbWidth / (half), -(s32)(g)->efbHeight / (half), 0.0f);   \
    GXTexCoord2f32(0.0f, 1.0f)

static const GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};

#pragma opt_propagation off
#pragma opt_lifetimes off
void envDisp_DepthOfField(void) {
    CameraEntry* cam;
    s32 first2;
    s32 tc;
    const s32* tbl2;
    s32 i;
    s32 coord2;
    s32 first;
    const s32* tbl;
    s32 stage2;
    EnvironmentUnk88* dof;
    s32 stage;
    s32 i2;
    s32 tc2;
    s32 coord;
    EnvironmentWork* wp = envGetWork();
    GXTevColorArg cin;
    Mtx mtx;
    Mtx mtx2;
    GXColor color;

    dof = &wp->unk88;
    if (wp->flags & 0x80000000) {
        cam = camGetPtr(CAMERA_2D);
        GXSetProjection(camGetPtr(CAMERA_2D)->projection, cam->projType);
        GXLoadPosMtxImm(camGetPtr(CAMERA_2D)->view, 0);
        GXSetCurrentMtx(0);
        GXLoadTexObj(smartTexObj(&wp->captureObj, (void**)wp->capture), GX_TEXMAP0);
        GXLoadTexObj(smartTexObj(&wp->captureObj2, (void**)wp->capture2), GX_TEXMAP1);
        GXSetNumChans(0);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_OR);
        GXSetZCompLoc(GX_FALSE);
        GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetCullMode(GX_CULL_NONE);
        if ((dof->unk0 & 1) && dof->unk4) {
            tbl = texmtx_tbl;
            coord = 0;
            stage = 0;
            for (i = 0; i < 4; i++, tbl++, stage++, coord++) {
                PSMTXTrans(mtx, dof->unk4 * env_sin(6.2831855f * i / 4) / 100.0f, dof->unk4 * env_cos(6.2831855f * i / 4) / 100.0f, 0.0f);
                GXLoadTexMtxImm(mtx, *tbl, GX_MTX2x4);
                GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX2x4, GX_TG_TEX0, *tbl, GX_FALSE, GX_PTIDENTITY);
                GXSetTevKColorSel((GXTevStageID)stage, GX_TEV_KCSEL_1_4);
                GXSetTevKAlphaSel((GXTevStageID)stage, GX_TEV_KASEL_1_4);
                GXSetTevOrder((GXTevStageID)stage, (GXTexCoordID)coord, GX_TEXMAP0, GX_COLOR_NULL);
                GXSetTevColorOp((GXTevStageID)stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, (GXTevRegID)(i == 3));
                GXSetTevAlphaOp((GXTevStageID)stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, (GXTevRegID)(3 == i));
                cin = GX_CC_CPREV;
                if (first = (i == 0)) {
                    cin = GX_CC_ZERO;
                }
                GXSetTevColorIn((GXTevStageID)stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, cin);
                GXSetTevAlphaIn((GXTevStageID)stage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, first ? GX_CA_ZERO : GX_CA_APREV);
                GXSetTevSwapMode((GXTevStageID)stage, GX_TEV_SWAP0, GX_TEV_SWAP0);
            }
            color.r = dof->unk2;
            color.a = 0xFF;
            GXSetTevKColor(GX_KCOLOR0, color);
            GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            tc = coord++;
            GXSetTevKColorSel((GXTevStageID)stage, GX_TEV_KCSEL_K0);
            GXSetTevKAlphaSel((GXTevStageID)stage, GX_TEV_KASEL_K0_A);
            GXSetTevOrder((GXTevStageID)stage, (GXTexCoordID)tc, GX_TEXMAP1, GX_COLOR_NULL);
            GXSetTevColorOp((GXTevStageID)stage, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp((GXTevStageID)stage, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn((GXTevStageID)stage, GX_CC_TEXC, GX_CC_KONST, GX_CC_C0, GX_CC_ZERO);
            GXSetTevAlphaIn((GXTevStageID)stage, GX_CA_TEXA, GX_CA_KONST, GX_CA_A0, GX_CA_ZERO);
            GXSetTevSwapMode((GXTevStageID)stage, GX_TEV_SWAP0, GX_TEV_SWAP0);
            stage++;
            GXSetNumTexGens((u8)coord);
            GXSetNumTevStages((u8)stage);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            DOF_QUAD(gp, 2.0f);
        }
        if ((dof->unk0 & 2) && dof->unk8) {
            coord2 = stage2 = i2 = 0;
            tbl2 = texmtx_tbl;
            for (; i2 < 4; i2++, tbl2++, stage2++, coord2++) {
                PSMTXTrans(mtx2, dof->unk8 * env_sin(6.2831855f * i2 / 4) / 100.0f, dof->unk8 * env_cos(6.2831855f * i2 / 4) / 100.0f, 0.0f);
                GXLoadTexMtxImm(mtx2, *tbl2, GX_MTX2x4);
                GXSetTexCoordGen2((GXTexCoordID)coord2, GX_TG_MTX2x4, GX_TG_TEX0, *tbl2, GX_FALSE, GX_PTIDENTITY);
                GXSetTevKColorSel((GXTevStageID)stage2, GX_TEV_KCSEL_1_4);
                GXSetTevKAlphaSel((GXTevStageID)stage2, GX_TEV_KASEL_1_4);
                GXSetTevOrder((GXTevStageID)stage2, (GXTexCoordID)coord2, GX_TEXMAP0, GX_COLOR_NULL);
                GXSetTevColorOp((GXTevStageID)stage2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, (GXTevRegID)(i2 == 3));
                GXSetTevAlphaOp((GXTevStageID)stage2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, (GXTevRegID)(3 == i2));
                cin = GX_CC_CPREV;
                if (first2 = (i2 == 0)) {
                    cin = GX_CC_ZERO;
                }
                GXSetTevColorIn((GXTevStageID)stage2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, cin);
                GXSetTevAlphaIn((GXTevStageID)stage2, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, first2 ? GX_CA_ZERO : GX_CA_APREV);
                GXSetTevSwapMode((GXTevStageID)stage2, GX_TEV_SWAP0, GX_TEV_SWAP0);
            }
            color.r = dof->unk3;
            color.a = 0xFF;
            GXSetTevKColor(GX_KCOLOR0, color);
            GXSetTexCoordGen2((GXTexCoordID)coord2, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            tc2 = coord2++;
            GXSetTevColor(GX_TEVREG1, white);
            GXSetTevKColorSel((GXTevStageID)stage2, GX_TEV_KCSEL_K0);
            GXSetTevKAlphaSel((GXTevStageID)stage2, GX_TEV_KASEL_K0_A);
            GXSetTevOrder((GXTevStageID)stage2, (GXTexCoordID)tc2, GX_TEXMAP1, GX_COLOR_NULL);
            GXSetTevColorOp((GXTevStageID)stage2, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp((GXTevStageID)stage2, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn((GXTevStageID)stage2, GX_CC_TEXC, GX_CC_KONST, GX_CC_ONE, GX_CC_ZERO);
            GXSetTevAlphaIn((GXTevStageID)stage2, GX_CA_TEXA, GX_CA_KONST, GX_CA_A1, GX_CA_ZERO);
            GXSetTevSwapMode((GXTevStageID)stage2, GX_TEV_SWAP0, GX_TEV_SWAP0);
            GXSetTevOrder((GXTevStageID)(stage2 + 1), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
            GXSetTevColorOp((GXTevStageID)(stage2 + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp((GXTevStageID)(stage2 + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn((GXTevStageID)(stage2 + 1), GX_CC_C0, GX_CC_ZERO, GX_CC_APREV, GX_CC_ZERO);
            GXSetTevAlphaIn((GXTevStageID)(stage2 + 1), GX_CA_A0, GX_CA_ZERO, GX_CA_APREV, GX_CA_ZERO);
            GXSetTevSwapMode((GXTevStageID)(stage2 + 1), GX_TEV_SWAP0, GX_TEV_SWAP0);
            stage2 += 2;
            GXSetNumTexGens((u8)coord2);
            GXSetNumTevStages((u8)stage2);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            DOF_QUAD(gp, 2.0f);
        }
    }
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset

//almost 1:1, needs some regalloc work and type changes
void envGlare(EnvironmentGlare* glare) {
    EnvironmentWork* var_r4 = envGetWork();
    EnvironmentGlareFilter* temp_r30;
    void* temp_r19;
    u32 temp_r20;
    u32 temp_r21;
    u16 temp_r26;
    u16 temp_r27;
    EnvironmentGlare* var_r21;
    EnvironmentGlare* var_r22_3;
    s32 temp_r31;
    s32 temp_r30_2;

    s32 temp_r20_2;
    s32 temp_r21_2;
    s32 temp_r29;
    s32 var_r22;
    u32 var_r22_2;
    s32 var_r23;
    u32 var_r23_2;
    s32 var_r28;
    s32 var_r19_3;
    u16 temp_r0;
    u16 temp_r8;

    u32 size;
    Mtx44 sp88;
    Mtx sp58;
    Mtx sp28;
    GXTexObj sp8;

    int i;

    frame_cnt += 1.0f;
    temp_r30 = &var_r4->filter;
    temp_r27 = var_r4->filter.y0;
    temp_r26 = var_r4->filter.x0;
    temp_r0 = (u16)(var_r4->filter.y1 - temp_r27);
    temp_r8 = (u16)(var_r4->filter.x1 - temp_r26);
    temp_r20 = ((u32)temp_r0 & 0xFFFF) / 2;
    temp_r21 = ((u32)temp_r8 & 0xFFFF) / 2;
    size = GXGetTexBufferSize((u16)temp_r21, (u16)temp_r20, GX_TF_RGB565, GX_FALSE, 0);
    temp_r19 = smartAlloc(size, 3)->address;
    GXSetTexCopySrc(temp_r26, temp_r27, temp_r8, temp_r0);
    GXSetTexCopyDst((u16)temp_r21, (u16)temp_r20, GX_TF_RGB565, GX_TRUE);
    GXCopyTex(temp_r19, GX_FALSE);
    GXPixModeSync();
    GXInitTexObj(&sp8, temp_r19, (u16)temp_r21, (u16)temp_r20, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&sp8, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&sp8, GX_TEXMAP0);
    temp_r29 = glare->count;
    var_r28 = 0;
    temp_r20_2 = glare->unkC;
    temp_r21_2 = glare->unk10;
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG1);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_KONST, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevKColorSel(GX_TEVSTAGE0, temp_r20_2);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_C1, GX_CC_KONST, GX_CC_ZERO);
    GXSetTevKColorSel(GX_TEVSTAGE1, temp_r21_2);
    GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);

    i = 0;
    var_r23 = 2;
    var_r22 = 3;
    for (; i < 7; i++) {
        GXSetTevOrder(var_r23, i + 1, 0, 0xFF);
        GXSetTevColorOp(var_r23, 1, 0, 0, 1, 2);
        GXSetTevColorIn(var_r23, 0xE, 0xF, 0xF, 8);
        GXSetTevKColorSel(var_r23, temp_r20_2);
        GXSetTevSwapMode(var_r23, 0, 0);
        GXSetTevOrder(var_r22, 0xFF, 0xFF, 0xFF);
        GXSetTevColorOp(var_r22, 0, 0, 0, 1, 0);
        GXSetTevColorIn(var_r22, 0xF, 4, 0xE, 0);
        GXSetTevKColorSel(var_r22, temp_r21_2);
        GXSetTevSwapMode(var_r22, 0, 0);
        var_r22 += 2;
        var_r23 += 2;
    }

    for (i = 0, var_r22_2 = GX_TEXMTX0; i < 8; i++, var_r22_2 += 3) {
        GXSetTexCoordGen(i, GX_TG_MTX2x4, GX_TG_TEX0, var_r22_2);
    }

    if (temp_r30->flags & 1) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    } else {
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    }
    GXSetBlendMode(glare->mode, glare->srcFactor, glare->dstFactor, GX_LO_CLEAR);
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetViewport(0.0f, 0.0f, (f32)gp->fbWidth, (f32)gp->efbHeight, 0.0f, 1.0f);
    GXSetScissor(0, 0, gp->fbWidth, gp->efbHeight);
    MTXOrtho(sp88, 0.0f, (f32)gp->efbHeight, 0.0f, (f32)gp->fbWidth, 0.0f, -32767.0f);
    GXSetProjection(sp88, GX_ORTHOGRAPHIC);
    PSMTXIdentity(sp58);
    GXLoadPosMtxImm(sp58, 0);
    GXSetCurrentMtx(0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_TEX0, GX_TEX_ST, GX_U16, 0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetZScaleOffset(1.0f, temp_r30->zscale);
    temp_r30_2 = temp_r27 + temp_r0;
    temp_r31 = temp_r26 + temp_r8;
    var_r21 = glare;
    while (var_r28 < temp_r29) {
        var_r22_3 = var_r21;
        var_r19_3 = 0;
        var_r23_2 = 0x1E;
        while ((var_r19_3 < 8) && (var_r28 < temp_r29)) {
            MTXTrans(sp28, (glare->unk14 * var_r22_3->coords[0].unk0) / (f32) gp->fbWidth, (glare->unk14 * var_r22_3->coords[0].unk4) / (f32) gp->efbHeight, 0.0f); //temp_r4, temp_r5_3, as 2 3 and temp_f4 as last
            GXLoadTexMtxImm(sp28, var_r23_2, 1);
            var_r23_2 += 3;
            var_r19_3 += 1;
            var_r22_3 = (void*)((u32)var_r22_3 + 8);
            var_r21 = (void*)((u32)var_r21 + 8);
            var_r28 += 1;
        }
        GXSetNumTevStages((u8)(var_r19_3 * 2));
        GXSetNumTexGens((u8)var_r19_3);
        GXBegin(GX_QUADS, GX_VTXFMT7, 4);
        GXPosition3s16((s16)temp_r26, (s16)temp_r27, 0);
        GXTexCoord2u16(0, 0);
        GXPosition3s16((s16)temp_r31, (s16)temp_r27, 0);
        GXTexCoord2u16(1, 0);
        GXPosition3s16((s16)temp_r31, (s16)temp_r30_2, 0);
        GXTexCoord2u16(1, 1);
        GXPosition3s16((s16)temp_r26, (s16)temp_r30_2, 0);
        GXTexCoord2u16(0, 1);
    }
}
