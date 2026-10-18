// FAKE: whole unit as G5 asm stopgap (force_active + fixbase); C under #ifdef NONMATCHING.
#include "driver/envdrv.h"
#include "driver/arcdrv.h"
#include "driver/dispdrv.h"
#include "driver/mapdrv.h"
#include "mario/mariost.h"
#include "manager/dvdmgr.h"
#include "system.h"
#include "texPalette.h"
#include <dolphin/dvd.h>
#include <string.h>
#pragma force_active on // FAKE: keep asm-only-referenced data from being dead-stripped
__declspec(section ".rodata") const u32 dat_802f9338[10] = { 0x0000001E, 0x00000021, 0x00000024, 0x00000027, 0x0000002A, 0x0000002D, 0x00000030, 0x00000033, 0x00000036, 0x00000039 };
__declspec(section ".rodata") const f32 vec3_802f9360[3] = { 0.0f, 0.0f, -1.0f };
__declspec(section ".rodata") const f32 vec3_802f936c[3] = { 0.0f, 0.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f9378[3] = { 0.0f, 100.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f9384[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f9390[3] = { 0.0f, 0.0f, -1.0f };
__declspec(section ".rodata") const f64 double_to_int_802f93a0 = 4503601774854144;
__declspec(section ".rodata") const f64 double_to_int_mask_802f93a8 = 4503599627370496;
__declspec(section ".rodata") const f64 double_0p5_802f93b0 = 0.5;
__declspec(section ".rodata") const f64 double_3_802f93b8 = 3;
__declspec(section ".rodata") const f64 double_0_802f93c0 = 0;
__declspec(section ".rodata") const char str_802F93C8[8] = "\145\156\166\056\164\160\154";
__declspec(section ".rodata") const char str_802F93D0[12] = "\045\163\057\145\156\166\056\164\160\154\000";
__declspec(section ".rodata") const u32 gap_04_802F93DC_rodata[1] = { 0x00000000 };


#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
extern const f32 float_10_8041e524;
extern const f32 float_0_8041e53c;
extern const f32 float_5000_8041e5cc;
extern const f32 float_20_8041e588;
#endif

extern int sprintf(char* str, const char* format, ...);
extern GlobalWork* gp;

//.data
// static data from an inlined header function
#pragma force_active on // FAKE: keep asm-only-referenced data from being dead-stripped
__declspec(section ".data") s32 lbl_80398960[] = {-1082130432, 1065353216};
__declspec(section ".data") s32 env_negone_one_374[] = {-1082130432, 1065353216};
__declspec(section ".data") s32 lbl_80398970[] = {1065353216, -1082130432};
__declspec(section ".data") s32 env_one_negone_373[] = {1065353216, -1082130432};
__declspec(section ".data") s32 lbl_80398980[] = {-1082130432, 1065353216};
__declspec(section ".data") s32 env_negone_one_360[] = {-1082130432, 1065353216};
__declspec(section ".data") s32 lbl_80398990[] = {1065353216, -1082130432};
__declspec(section ".data") s32 env_one_negone_359[] = {1065353216, -1082130432};

EnvironmentGlare envGlare0 = {
    GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, (GXTevKColorSel)1, (GXTevKColorSel)0, 5.25f, 16,
    {
        {-1.0f, 0.0f}, {-3.0f, 0.0f}, {-5.0f, 0.0f}, {-7.0f, 0.0f},
    {1.0f, 0.0f}, {3.0f, 0.0f}, {5.0f, 0.0f}, {7.0f, 0.0f},
    {0.0f, -1.0f}, {0.0f, -3.0f}, {0.0f, -5.0f}, {0.0f, -7.0f},
    {0.0f, 1.0f}, {0.0f, 3.0f}, {0.0f, 5.0f}, {0.0f, 7.0f},
}
};

EnvironmentGlare envGlare1 = {
    GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, (GXTevKColorSel)1, (GXTevKColorSel)4, 3.5f, 8,
    {
        {-1.41419994831f, -1.41419994831f}, {0.0f, -1.0f}, {1.41419994831f, -1.41419994831f}, {-1.0f, 0.0f},
    {1.0f, 0.0f}, {-1.41419994831f, 1.41419994831f}, {0.0f, 1.0f}, {1.41419994831f, 1.41419994831f},
}
};

EnvironmentGlare envGlare2 = {
    GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, (GXTevKColorSel)1, (GXTevKColorSel)6, 3.5f, 52,
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
    GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, (GXTevKColorSel)1, (GXTevKColorSel)4, 3.5f, 16,
    {
        {0.0f, -4.0f}, {-1.0f, -3.0f}, {1.0f, -3.0f}, {-2.0f, -2.0f},
    {2.0f, -2.0f}, {-3.0f, -1.0f}, {3.0f, -1.0f}, {-3.0f, 0.0f},
    {3.0f, 0.0f}, {-3.0f, 1.0f}, {3.0f, 1.0f}, {-2.0f, 2.0f},
    {2.0f, 2.0f}, {-1.0f, 3.0f}, {1.0f, 3.0f}, {0.0f, 4.0f},
}
};

//.bss
__declspec(section ".data") u32 gap_06_803E10D8_bss[2];
static EnvironmentWork work[2];

//.sbss
TEXPalette* env_tpl = NULL;
s32 tpl_ok = 0;

//local prototypes
void _callback(s32 result, DVDFileInfo* fileInfo);
void envCapture(CameraId camId, void* param);
void envCapture2(CameraId camId, void* param);
void envDisp(CameraId camId, void* param);
void envDisp2(CameraId camId, void* param);
void envDisp_DepthOfField(void);
void envDisp_Blur(void);
void envDisp_FF(void);

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
    tpl = arcOpen(str_802F93C8, 0, 0);
    env_tpl = tpl;
    if (!tpl) {
        sprintf(path, EXT_LIT(str_802F93D0, "%s/env.tpl\0\0\0\0\0"), getMarioStDvdRoot());
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
        GXInitTexObjLOD(&wp->captureObj, GX_LINEAR, GX_LINEAR, EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f), GX_FALSE, GX_FALSE, GX_ANISO_1);
    }
    if (wp->flags & 2) {
        GXSetTexCopySrc(0, 0, var0, var1);
        GXSetTexCopyDst(var2, var3, GX_CTF_Z8M, GX_TRUE);
        size = GXGetTexBufferSize(var2, var3, GX_CTF_Z8M, GX_FALSE, 0);
        wp->capture2 = smartAlloc(size, 3);
        GXCopyTex(wp->capture2->address, 0);
        GXPixModeSync();
        GXInitTexObj(&wp->captureObj2, wp->capture2->address, var2, var3, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&wp->captureObj2, GX_LINEAR, GX_LINEAR, EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f), GX_FALSE, GX_FALSE, GX_ANISO_1);
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
        GXInitTexObjLOD(&wp->envBlurObj, GX_LINEAR, GX_LINEAR, EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f), GX_FALSE, GX_FALSE, GX_ANISO_1);
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
    envDisp_DepthOfField();
    envDisp_Blur();
    envDisp_FF();
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
    dispEntry(CAMERA_3D, EXT_LIT(float_20_8041e588, 20.0f), 7, envCapture, NULL);
    dispEntry(CAMERA_3D, EXT_LIT(float_10_8041e524, 10.0f), 7, envDisp, NULL);
    dispEntry(CAMERA_3D, EXT_LIT(float_0_8041e53c, 0.0f), 7, envCapture2, NULL);
    dispEntry(CAMERA_3D, EXT_LIT(float_5000_8041e5cc, 5000.0f), 8, envDisp2, NULL);
}







#define PI 3.141592653589793f
#define TWO_PI 6.283185307179586f
#ifdef NONMATCHING
static const s32 texmtx_tbl[] = {30, 33, 36, 39, 42, 45, 48, 51, 54, 57};
#endif

static inline f32
env_sin(f32 x) {
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

static inline f32
env_cos(f32 x) {
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

#ifdef NONMATCHING
static const GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
#endif

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING
void envDisp_DepthOfField(void) {
    EnvironmentWork* wp = envGetWork();
    EnvironmentDof* dof;
    CameraEntry* cam;
    s32 i;
    s32 stage;
    s32 coord;
    s32 tc;
    BOOL first;
    GXColor color;

    dof = &wp->dof;
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
        if ((dof->flags & 1) && dof->radius1) {
            Mtx mtx;

            coord = 0;
            stage = 0;
            for (i = 0; i < 4; i++, stage++, coord++) {
                PSMTXTrans(mtx, dof->radius1 * env_sin(6.2831855f * i / 4.0f) / 100.0f, dof->radius1 * env_cos(6.2831855f * i / 4.0f) / 100.0f, 0.0f);
                GXLoadTexMtxImm(mtx, texmtx_tbl[coord], GX_MTX2x4);
                GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX2x4, GX_TG_TEX0, texmtx_tbl[coord], GX_FALSE, GX_PTIDENTITY);
                GXSetTevKColorSel((GXTevStageID)stage, GX_TEV_KCSEL_1_4);
                GXSetTevKAlphaSel((GXTevStageID)stage, GX_TEV_KASEL_1_4);
                GXSetTevOrder((GXTevStageID)stage, (GXTexCoordID)coord, GX_TEXMAP0, GX_COLOR_NULL);
                GXSetTevColorOp((GXTevStageID)stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, (GXTevRegID)(i == 3));
                GXSetTevAlphaOp((GXTevStageID)stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, (GXTevRegID)(i == 3));
                first = i == 0;
                GXSetTevColorIn((GXTevStageID)stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, first ? GX_CC_ZERO : GX_CC_CPREV);
                GXSetTevAlphaIn((GXTevStageID)stage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, first ? GX_CA_ZERO : GX_CA_APREV);
                GXSetTevSwapMode((GXTevStageID)stage, GX_TEV_SWAP0, GX_TEV_SWAP0);
            }
            color.r = dof->level1;
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
        if ((dof->flags & 2) && dof->radius2) {
            Mtx mtx;

            coord = 0;
            stage = 0;
            for (i = 0; i < 4; i++, stage++, coord++) {
                PSMTXTrans(mtx, dof->radius2 * env_sin(6.2831855f * i / 4.0f) / 100.0f, dof->radius2 * env_cos(6.2831855f * i / 4.0f) / 100.0f, 0.0f);
                GXLoadTexMtxImm(mtx, texmtx_tbl[i], GX_MTX2x4);
                GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX2x4, GX_TG_TEX0, texmtx_tbl[i], GX_FALSE, GX_PTIDENTITY);
                GXSetTevKColorSel((GXTevStageID)stage, GX_TEV_KCSEL_1_4);
                GXSetTevKAlphaSel((GXTevStageID)stage, GX_TEV_KASEL_1_4);
                GXSetTevOrder((GXTevStageID)stage, (GXTexCoordID)coord, GX_TEXMAP0, GX_COLOR_NULL);
                GXSetTevColorOp((GXTevStageID)stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, (GXTevRegID)(i == 3));
                GXSetTevAlphaOp((GXTevStageID)stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, (GXTevRegID)(i == 3));
                first = i == 0;
                GXSetTevColorIn((GXTevStageID)stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, first ? GX_CC_ZERO : GX_CC_CPREV);
                GXSetTevAlphaIn((GXTevStageID)stage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, first ? GX_CA_ZERO : GX_CA_APREV);
                GXSetTevSwapMode((GXTevStageID)stage, GX_TEV_SWAP0, GX_TEV_SWAP0);
            }
            color.r = dof->level2;
            color.a = 0xFF;
            GXSetTevKColor(GX_KCOLOR0, color);
            GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            tc = coord++;
            GXSetTevColor(GX_TEVREG1, white);
            GXSetTevKColorSel((GXTevStageID)stage, GX_TEV_KCSEL_K0);
            GXSetTevKAlphaSel((GXTevStageID)stage, GX_TEV_KASEL_K0_A);
            GXSetTevOrder((GXTevStageID)stage, (GXTexCoordID)tc, GX_TEXMAP1, GX_COLOR_NULL);
            GXSetTevColorOp((GXTevStageID)stage, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp((GXTevStageID)stage, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn((GXTevStageID)stage, GX_CC_TEXC, GX_CC_KONST, GX_CC_ONE, GX_CC_ZERO);
            GXSetTevAlphaIn((GXTevStageID)stage, GX_CA_TEXA, GX_CA_KONST, GX_CA_A1, GX_CA_ZERO);
            GXSetTevSwapMode((GXTevStageID)stage, GX_TEV_SWAP0, GX_TEV_SWAP0);
            GXSetTevOrder((GXTevStageID)(stage + 1), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
            GXSetTevColorOp((GXTevStageID)(stage + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp((GXTevStageID)(stage + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn((GXTevStageID)(stage + 1), GX_CC_C0, GX_CC_ZERO, GX_CC_APREV, GX_CC_ZERO);
            GXSetTevAlphaIn((GXTevStageID)(stage + 1), GX_CA_A0, GX_CA_ZERO, GX_CA_APREV, GX_CA_ZERO);
            GXSetTevSwapMode((GXTevStageID)(stage + 1), GX_TEV_SWAP0, GX_TEV_SWAP0);
            stage += 2;
            GXSetNumTexGens((u8)coord);
            GXSetNumTevStages((u8)stage);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            DOF_QUAD(gp, 2.0f);
        }
    }
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

typedef struct EnvBlurWork {
    u16 flags; //0x0
    u8 pad2[6]; //0x2
    OSTime time; //0x8
    s32 msec; //0x10
    u8 pad14[4]; //0x14
} EnvBlurWork;

#ifdef NONMATCHING
void envDisp_Blur(void) {
    EnvironmentWork* wp = envGetWork();
    EnvBlurWork* blur = (EnvBlurWork*)&wp->unk98;
    CameraEntry* cam;
    s32 msec;
    f32 t;
    u8 alpha;
    GXColor c;

    if ((wp->flags & 0x40000000) && (wp->flags & 8)) {
        cam = camGetPtr(CAMERA_2D);
        GXSetProjection(camGetPtr(CAMERA_2D)->projection, cam->projType);
        GXLoadPosMtxImm(camGetPtr(CAMERA_2D)->view, 0);
        GXSetCurrentMtx(0);
        GXSetNumChans(0);
        GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K0);
        GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
        msec = blur->msec;
        if (msec) {
            t = (f32)OSTicksToMilliseconds((u64)(gp->renderTime - blur->time)) / (f32)msec;
            if (t > 1.0f) {
                t = 1.0f;
            }
            if (blur->flags & 1) {
                alpha = 255.0f * (1.0f - t);
            }
            else {
                alpha = 120.0f * (1.0f - t) + 128.0f;
            }
            GXSetTevKColor(GX_KCOLOR0, (GXColor){0xFF, 0xFF, 0xFF, alpha});
        }
        else {
            GXSetTevKColor(GX_KCOLOR0, (GXColor){0xFF, 0xFF, 0xFF, 0xA0});
        }
        GXLoadTexObj(&wp->envBlurObj, GX_TEXMAP0);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetZCompLoc(GX_TRUE);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        DOF_QUAD(gp, 2.0f);
    }
}
#endif

#ifdef NONMATCHING
void envBlurOn(s32 type, s32 msec) {
    EnvironmentWork* wp = envGetWork();
    EnvBlurWork* blur = (EnvBlurWork*)&wp->unk98;

    wp->flags |= 0x40000000;
    wp->flags |= 4;
    wp->flags &= ~8;
    memset(blur, 0, sizeof(EnvBlurWork));
    blur->time = gp->renderTime;
    blur->msec = msec;
    if (type) {
        blur->flags |= 1;
    }
    wp->envBlur = _mapAlloc(GXGetTexBufferSize(gp->fbWidth / 2,
        gp->efbHeight / 2, GX_TF_RGB565, GX_FALSE, 0));
}
#endif

#ifdef NONMATCHING
void envBlurOff(void) {
    EnvironmentWork* wp = envGetWork();

    wp->flags &= ~4;
    wp->flags &= ~0x40000000;
    _mapFree(wp->envBlur);
}
#endif


//almost 1:1, needs some regalloc work and type changes
#ifdef NONMATCHING
void envGlare(EnvironmentGlare* glare) {
    static f32 frame_cnt = 0.0f;
    EnvironmentWork* wp = envGetWork();
    EnvironmentGlareFilter* filter;
    u16 x0, y0;
    s32 x1, y1;
    u16 w, h;
    u32 hw, hh;
    s32 count;
    s32 done;
    s32 n;
    s32 i;
    s32 stageA;
    s32 stageB;
    u32 texMtx;
    GXTevKColorSel kc0, kc1;
    void* buf;
    Mtx44 proj;
    Mtx view;
    Mtx texm;
    GXTexObj tex;

    frame_cnt += 1.0f;
    filter = &wp->filter;
    y0 = filter->y0;
    x0 = filter->x0;
    w = filter->x1 - x0;
    h = filter->y1 - y0;
    hh = h >> 1;
    hw = w >> 1;
    buf = smartAlloc(GXGetTexBufferSize((u16)hw, (u16)hh, GX_TF_RGB565, GX_FALSE, 0), 3)->address;
    GXSetTexCopySrc(x0, y0, w, h);
    GXSetTexCopyDst((u16)hw, (u16)hh, GX_TF_RGB565, GX_TRUE);
    GXCopyTex(buf, GX_FALSE);
    GXPixModeSync();
    GXInitTexObj(&tex, buf, (u16)hw, (u16)hh, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&tex, GX_TEXMAP0);
    count = glare->count;
    kc0 = glare->kcolorSel0;
    kc1 = glare->kcolorSel1;
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG1);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_KONST, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevKColorSel(GX_TEVSTAGE0, kc0);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_C1, GX_CC_KONST, GX_CC_ZERO);
    GXSetTevKColorSel(GX_TEVSTAGE1, kc1);
    GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);

    for (i = 0, stageA = GX_TEVSTAGE2, stageB = GX_TEVSTAGE3; i < 7; i++, stageA += 2, stageB += 2) {
        GXSetTevOrder((GXTevStageID)stageA, (GXTexCoordID)(i + 1), GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorOp((GXTevStageID)stageA, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG1);
        GXSetTevColorIn((GXTevStageID)stageA, GX_CC_KONST, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevKColorSel((GXTevStageID)stageA, kc0);
        GXSetTevSwapMode((GXTevStageID)stageA, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevOrder((GXTevStageID)stageB, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetTevColorOp((GXTevStageID)stageB, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn((GXTevStageID)stageB, GX_CC_ZERO, GX_CC_C1, GX_CC_KONST, GX_CC_CPREV);
        GXSetTevKColorSel((GXTevStageID)stageB, kc1);
        GXSetTevSwapMode((GXTevStageID)stageB, GX_TEV_SWAP0, GX_TEV_SWAP0);
    }

    for (i = 0, texMtx = GX_TEXMTX0; i < 8; i++, texMtx += 3) {
        GXSetTexCoordGen((GXTexCoordID)i, GX_TG_MTX2x4, GX_TG_TEX0, texMtx);
    }

    if (filter->flags & 1) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    } else {
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    }
    GXSetBlendMode(glare->mode, glare->srcFactor, glare->dstFactor, GX_LO_CLEAR);
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetViewport(0.0f, 0.0f, (f32)gp->fbWidth, (f32)gp->efbHeight, 0.0f, 1.0f);
    GXSetScissor(0, 0, gp->fbWidth, gp->efbHeight);
    MTXOrtho(proj, 0.0f, (f32)gp->efbHeight, 0.0f, (f32)gp->fbWidth, 0.0f, -32767.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    PSMTXIdentity(view);
    GXLoadPosMtxImm(view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_TEX0, GX_TEX_ST, GX_U16, 0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetZScaleOffset(1.0f, filter->zscale);
    y1 = y0 + h;
    x1 = x0 + w;
    for (done = 0; done < count;) {
        for (n = 0, texMtx = GX_TEXMTX0; n < 8 && done < count; n++, texMtx += 3, done++) {
            MTXTrans(texm, glare->coordScale * glare->coords[done].x / (f32)gp->fbWidth,
                     glare->coordScale * glare->coords[done].y / (f32)gp->efbHeight, 0.0f);
            GXLoadTexMtxImm(texm, texMtx, GX_MTX2x4);
        }
        GXSetNumTevStages((u8)(n * 2));
        GXSetNumTexGens((u8)n);
        GXBegin(GX_QUADS, GX_VTXFMT7, 4);
        GXPosition3s16((s16)x0, (s16)y0, 0);
        GXTexCoord2u16(0, 0);
        GXPosition3s16((s16)x1, (s16)y0, 0);
        GXTexCoord2u16(1, 0);
        GXPosition3s16((s16)x1, (s16)y1, 0);
        GXTexCoord2u16(1, 1);
        GXPosition3s16((s16)x0, (s16)y1, 0);
        GXTexCoord2u16(0, 1);
    }
}
#endif


#ifdef NONMATCHING
void envGlareFilter(s32 type, s32 y0, s32 x0, s32 y1, s32 x1) {
    EnvironmentWork* wp = envGetWork();
    EnvironmentGlareFilter* f = &wp->filter;
    s16 sx1, sy1, sx0, sy0;

    if (type == 0) {
        f->type = 0;
        f->x1 = 0;
        f->y1 = 0;
        f->x0 = 0;
        f->y0 = 0;
        wp->flags &= ~0x20000000;
        return;
    }
    sx0 = x0 - (x0 & 1);
    sy0 = y0 - (y0 & 1);
    sx1 = x1 + (x1 & 1);
    sy1 = y1 + (y1 & 1);
    if (sx0 < 0) {
        sx0 = 0;
    }
    if (sy0 < 0) {
        sy0 = 0;
    }
    if (sx1 > gp->fbWidth) {
        sx1 = gp->fbWidth;
    }
    if (sy1 > gp->efbHeight) {
        sy1 = gp->efbHeight;
    }
    f->type = type;
    f->y0 = sy0;
    f->x0 = sx0;
    f->y1 = sy1;
    f->x1 = sx1;
    f->zscale = 0.0f;
    f->flags &= ~1;
    wp->flags |= 0x20000000;
}
#endif

#ifdef NONMATCHING
void envGlareFilterZ(f32 zscale) {
    EnvironmentWork* wp = envGetWork();
    EnvironmentGlareFilter* f = &wp->filter;

    f->zscale = zscale;
    f->flags |= 1;
}
#endif

extern int __float_nan[];
int rand(void);
static inline s32
env_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32
env_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * (0.5 * guess * (3.0 - guess * guess * x)); } else if (x < 0.0) { return *(f32*)__float_nan; } else if (env_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING
void envDisp_FF(void) {
    EnvironmentWork* wp = envGetWork();
    f32 r;
    f32 angle;
    f32 c;
    f32 s;
    f32 ofs;
    s32 i;

    if (wp->flags & 0x10000000) {
        GXSetNumChans(0);
        GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXLoadTexObj(&wp->captureObj, GX_TEXMAP0);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetZCompLoc(GX_TRUE);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
        GXSetLineWidth(16, GX_TO_ZERO);
        GXLoadPosMtxImm(camGetPtr(CAMERA_2D)->view, 0);
        GXSetCurrentMtx(0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        r = env_sqrtf(gp->fbWidth / 2 * gp->fbWidth / 2 + gp->efbHeight / 2 * gp->efbHeight / 2);
        GXBegin(GX_LINES, GX_VTXFMT0, 2000);
        for (i = 0; i < 1000; i++) {
            angle = 6.2831855f * i / 1000.0f;
            c = env_cos(angle);
            s = env_sin(angle);
            ofs = (rand() % 10) / 100.0f;
            GXPosition3f32(s * r, c * r, 0.0f);
            GXTexCoord2f32(s / 2.0f + 0.5f + ofs, -c / 2.0f + 0.5f + ofs);
            GXPosition3f32(0.0f, 0.0f, 0.0f);
            GXTexCoord2f32(0.5f, 0.5f);
        }
    }
}
#endif

#pragma opt_propagation reset
#pragma opt_lifetimes reset

typedef struct EnvTexMtxWork {
    MtxPtr view; //0x70
    MtxPtr mtx; //0x74
    MtxPtr model; //0x78
    f32 scale; //0x7C
    f32 rotY; //0x80
    f32 rotX; //0x84
} EnvTexMtxWork;
#define tw ((EnvTexMtxWork*)wp->unk70)

double sin(double);
double cos(double);
double acos(double);

#ifdef NONMATCHING
void envTevLoadTexMtxImm(s32 type, GXTexMtx id, GXTexMtx id2, GXTexMtxType mtxType) {
    static f32 a = 0.0f;
    EnvironmentWork* wp = envGetWork();
    Mtx m0, m2, m1, m3, m4, m5, m6, m7;
    Mtx44 m9;
    Mtx m10, m11, m8;
    f32 s, dot;

    switch (type) {
        case 0:
            PSMTXRotRad(m0, 'Y', 0.017453292f * tw->rotY);
            PSMTXRotRad(m1, 'Z', 0.017453292f * -tw->rotX);
            PSMTXConcat(m0, m1, m0);
            PSMTXInvXpose(m0, m0);
            PSVECNormalize((Vec*)m0[0], (Vec*)m0[0]);
            PSVECNormalize((Vec*)m0[1], (Vec*)m0[1]);
            PSVECNormalize((Vec*)m0[2], (Vec*)m0[2]);
            PSMTXScale(m2, 0.5f, 0.5f, 1.0f);
            PSMTXConcat(m2, m0, m0);
            PSMTXTrans(m2, 0.5f, 0.5f, 0.0f);
            PSMTXConcat(m2, m0, m0);
            GXLoadTexMtxImm(m0, id, mtxType);
            break;
        case 1:
            PSMTXRotRad(m0, 'Y', -1.5707964f);
            PSMTXConcat(m0, tw->model, m0);
            PSMTXInvXpose(m0, m0);
            PSVECNormalize((Vec*)m0[0], (Vec*)m0[0]);
            PSVECNormalize((Vec*)m0[1], (Vec*)m0[1]);
            PSVECNormalize((Vec*)m0[2], (Vec*)m0[2]);
            PSMTXScale(m3, 0.5f - 0.25f * tw->scale, 0.5f, 1.0f);
            PSMTXConcat(m3, m0, m0);
            PSMTXTrans(m3, 0.5f, 0.5f, 0.0f);
            PSMTXConcat(m3, m0, m0);
            GXLoadTexMtxImm(m0, id, mtxType);
            break;
        case 2: {
            Vec v = {0.0f, 0.0f, -1.0f};
            Vec light;
            Vec half;
            f32 ry2, rx2, s2;

            ry2 = 3.1415927f * tw->rotY / 180.0f;
            rx2 = 3.1415927f * tw->rotX / 180.0f;
            light.x = -(f32)cos(rx2) * (f32)sin(ry2);
            light.y = -(f32)sin(rx2);
            light.z = -(f32)cos(rx2) * (f32)cos(ry2);
            PSMTXMultVecSR(tw->view, &light, &light);
            C_VECHalfAngle(&light, &v, &half);
            PSMTXInvXpose(tw->model, m0);
            PSVECNormalize((Vec*)m0[0], (Vec*)m0[0]);
            PSVECNormalize((Vec*)m0[1], (Vec*)m0[1]);
            PSVECNormalize((Vec*)m0[2], (Vec*)m0[2]);
            PSMTXIdentity(m4);
            m4[0][0] = half.x;
            m4[0][1] = half.y;
            m4[0][2] = half.z;
            PSMTXConcat(m4, m0, m0);
            s2 = 20.0f * tw->scale;
            PSMTXScale(m4, s2, 1.0f, 1.0f);
            PSMTXConcat(m4, m0, m0);
            PSMTXTrans(m4, 1.0f - s2, 0.0f, 0.0f);
            PSMTXConcat(m4, m0, m0);
            GXLoadTexMtxImm(m0, id, mtxType);
            break;
        }
        case 3: {
            Vec light2;
            Vec h;
            Vec axis;
            Vec v2 = {0.0f, 0.0f, 1.0f};
            f32 ry, rx;

            ry = 3.1415927f * tw->rotY / 180.0f;
            rx = 3.1415927f * tw->rotX / 180.0f;
            light2.x = (f32)cos(rx) * (f32)sin(ry);
            light2.y = (f32)sin(rx);
            light2.z = (f32)cos(rx) * (f32)cos(ry);
            PSMTXMultVecSR(tw->view, &light2, &light2);
            dot = PSVECDotProduct(&light2, &v2);
            if (dot == -1.0f) {
                PSMTXScale(m0, 0.0f, 0.0f, 0.0f);
                GXLoadTexMtxImm(m0, id, GX_MTX2x4);
                break;
            }
            C_VECHalfAngle(&light2, &v2, &h);
            h.x = -h.x;
            h.y = -h.y;
            h.z = -h.z;
            PSMTXInvXpose(tw->model, m5);
            PSVECNormalize((Vec*)m5[0], (Vec*)m5[0]);
            PSVECNormalize((Vec*)m5[1], (Vec*)m5[1]);
            PSVECNormalize((Vec*)m5[2], (Vec*)m5[2]);
            if (dot == 1.0f) {
                PSMTXIdentity(m6);
            }
            else {
                PSVECCrossProduct(&h, &v2, &axis);
                PSMTXRotAxisRad(m6, &axis, (f32)acos(PSVECDotProduct(&v2, &h)));
            }
            PSMTXConcat(m6, m5, m0);
            PSMTXScale(m6, 2.0f * tw->scale, 2.0f * tw->scale, 1.0f);
            PSMTXConcat(m6, m0, m0);
            PSMTXTrans(m6, 0.5f, 0.5f, 0.0f);
            PSMTXConcat(m6, m0, m0);
            GXLoadTexMtxImm(m0, id, mtxType);
            break;
        }
        case 4:
            PSMTXInvXpose(tw->model, m0);
            PSVECNormalize((Vec*)m0[0], (Vec*)m0[0]);
            PSVECNormalize((Vec*)m0[1], (Vec*)m0[1]);
            PSVECNormalize((Vec*)m0[2], (Vec*)m0[2]);
            GXLoadTexMtxImm(m0, id, GX_MTX2x4);
            PSMTXScale(m7, 0.5f, 0.5f, 0.0f);
            PSMTXTrans(m0, 0.5f, 0.5f, 1.0f);
            PSMTXConcat(m0, m7, m0);
            GXLoadTexMtxImm(m0, id2, mtxType);
            break;
        case 5: {
            Vec camPos;
            Vec target;
            Vec up;

            a += 0.0001f;
            camPos = (Vec){10.0f * (f32)sin(a), 100.0f, 10.0f * (f32)cos(a)};
            target = (Vec){10.0f * (f32)sin(a), 0.0f, 10.0f * (f32)cos(a)};
            up = (Vec){0.0f, 0.0f, -1.0f};
            C_MTXLookAt(m8, &camPos, &up, &target);
            C_MTXLightFrustum((MtxPtr)m9, -32.0f, 32.0f, -32.0f, 32.0f, 300.0f, 0.5f, 0.5f, 0.5f, 0.5f);
            PSMTXInverse(tw->view, m10);
            PSMTXConcat(m8, m10, m11);
            PSMTXConcat((MtxPtr)m9, m11, m0);
            GXLoadTexMtxImm(m0, id2, mtxType);
            break;
        }
    }
}
#endif


static inline void
envTexObj(TEXPalette* pal, GXTexObj* to, u32 id) {
    GXBool mipMap;
    TEXDescriptor* tdp;

    tdp = TEXGet(pal, id);
    if (tdp->textureHeader->minLOD == tdp->textureHeader->maxLOD) {
        mipMap = GX_FALSE;
    } else {
        mipMap = GX_TRUE;
    }
    GXInitTexObj(to, tdp->textureHeader->data, tdp->textureHeader->width, tdp->textureHeader->height, (GXTexFmt)tdp->textureHeader->format, GX_CLAMP, GX_CLAMP, mipMap);
    GXInitTexObjLOD(to, tdp->textureHeader->minFilter, tdp->textureHeader->magFilter, tdp->textureHeader->minLOD, tdp->textureHeader->maxLOD, tdp->textureHeader->LODBias, GX_DISABLE, tdp->textureHeader->edgeLODEnable, GX_ANISO_1);
}

static inline void
envTexObjCI(TEXPalette* pal, GXTexObj* to, GXTlutObj* tlo, GXTlut tluts, u32 id) {
    GXBool mipMap;
    TEXDescriptor* tdp;

    tdp = TEXGet(pal, id);
    if (tdp->textureHeader->minLOD == tdp->textureHeader->maxLOD) {
        mipMap = GX_FALSE;
    } else {
        mipMap = GX_TRUE;
    }
    GXInitTlutObj(tlo, tdp->CLUTHeader->data, tdp->CLUTHeader->format, tdp->CLUTHeader->numEntries);
    GXInitTexObjCI(to, tdp->textureHeader->data, tdp->textureHeader->width, tdp->textureHeader->height, (GXCITexFmt)tdp->textureHeader->format, GX_CLAMP, GX_CLAMP, mipMap, tluts);
    GXInitTexObjLOD(to, tdp->textureHeader->minFilter, tdp->textureHeader->magFilter, tdp->textureHeader->minLOD, tdp->textureHeader->maxLOD, tdp->textureHeader->LODBias, GX_DISABLE, tdp->textureHeader->edgeLODEnable, GX_ANISO_1);
}

static inline void
envLoadTex(u32 id, s32 map) {
    GXTexObj obj;
    GXTlutObj tlut;

    if (TEXGet(env_tpl, id)->CLUTHeader) {
        envTexObjCI(env_tpl, &obj, &tlut, GX_TLUT0, id);
        GXLoadTlut(&tlut, GX_TLUT0);
        GXLoadTexObj(&obj, (GXTexMapID)map);
    } else {
        envTexObj(env_tpl, &obj, id);
        GXLoadTexObj(&obj, (GXTexMapID)map);
    }
}

#define ENV_TEX_TAIL(t, mtxType, gentype, mtxsrc) \
    GXSetTexCoordGen2((GXTexCoordID)coord, gentype, GX_TG_NRM, texmtx_tbl[map], GX_FALSE, mtxsrc); \
    envTevLoadTexMtxImm(t, (GXTexMtx)texmtx_tbl[map], GX_PTTEXMTX0, mtxType)

#ifdef NONMATCHING
void envAddTev(s32 type, MapTevCallbackInfo *info)
{
  s32 stage;
  int map;
  int coord;
  EnvironmentWork *wp = (gp->inBattle) ? (&work[1]) : (&work[0]);
  s32 indStage;
  Mtx mtx;
  stage = info->tevStage;
  map = info->texCoord; // MapTevCallbackInfo's texCoord/texMap fields are filled the other way round by mapdrv
  coord = info->texMap;
  indStage = info->indStage;
  if (type == 0)
  {
    return;
  }
  PSMTXConcat(camGetCurPtr()->view, info->mtx, mtx);
  ((EnvTexMtxWork *) wp->unk70)->view = camGetCurPtr()->view;
  ((EnvTexMtxWork *) wp->unk70)->mtx = info->mtx;
  ((EnvTexMtxWork *) wp->unk70)->model = mtx;
  GXSetTevOrder((GXTevStageID) stage,  coord, (GXTexMapID) map, GX_COLOR_NULL);
  GXSetTevColorOp((GXTevStageID) stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, (GXBool) 1, GX_TEVPREV);
  GXSetTevAlphaOp((GXTevStageID) stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, (GXBool) 1, GX_TEVPREV);
  GXSetTevSwapMode((GXTevStageID) stage, GX_TEV_SWAP0, GX_TEV_SWAP0);
  switch (type)
  {
    case 0:
      break;

    case 1:
      GXSetTevColorIn((GXTevStageID) stage, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
      GXSetTevAlphaIn((GXTevStageID) stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
      ((EnvTexMtxWork *) wp->unk70)->rotY = 10.0f;
      ((EnvTexMtxWork *) wp->unk70)->rotX = gp->retraceCount + 45;
      ((EnvTexMtxWork *) wp->unk70)->scale = 0.5f;
      envLoadTex(6, map);
      GXSetTexCoordGen2((GXTexCoordID) coord, GX_TG_MTX2x4, GX_TG_NRM, texmtx_tbl[map], (GXBool) 0, GX_PTIDENTITY);
      envTevLoadTexMtxImm(0, (GXTexMtx) texmtx_tbl[map], GX_PTTEXMTX0, GX_MTX2x4);
      stage++;
      coord++;
      map++;
      break;

    case 2:
      GXSetTevColorIn((GXTevStageID) stage, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA);
      GXSetTevAlphaIn((GXTevStageID) stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
      ((EnvTexMtxWork *) wp->unk70)->rotY = 10.0f;
      ((EnvTexMtxWork *) wp->unk70)->rotX = gp->retraceCount + 45;
      ((EnvTexMtxWork *) wp->unk70)->scale = 0.5f;
      envLoadTex(8, map);
      GXSetTexCoordGen2((GXTexCoordID) coord, GX_TG_MTX2x4, GX_TG_NRM, texmtx_tbl[map], (GXBool) 0, GX_PTIDENTITY);
      envTevLoadTexMtxImm(0, (GXTexMtx) texmtx_tbl[map], GX_PTTEXMTX0, GX_MTX2x4);
      stage++;
      coord++;
      map++;
      break;

    case 3:
      GXSetTevColorIn((GXTevStageID) stage, GX_CC_CPREV, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ZERO);
      GXSetTevAlphaIn((0, (GXTevStageID) stage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
      ((EnvTexMtxWork *) wp->unk70)->scale = 0.5f;
      envLoadTex(0, map);
      GXSetTexCoordGen2((GXTexCoordID) coord, GX_TG_MTX2x4, GX_TG_NRM, texmtx_tbl[map], (GXBool) 0, GX_PTIDENTITY);
      envTevLoadTexMtxImm(1, (GXTexMtx) texmtx_tbl[map], GX_PTTEXMTX0, GX_MTX2x4);
      stage++;
      map++;
      coord++;
      break;

    case 4:
      GXSetTevColorIn((GXTevStageID) stage, GX_CC_CPREV, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
      GXSetTevAlphaIn((GXTevStageID) stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
      ((EnvTexMtxWork *) wp->unk70)->scale = (0, 0.5f);
      ((EnvTexMtxWork *) wp->unk70)->rotY = 45.0f;
      ((EnvTexMtxWork *) wp->unk70)->rotX = 45.0f;
      envLoadTex(1, map);
      GXSetTexCoordGen2((GXTexCoordID) coord, GX_TG_MTX2x4, GX_TG_NRM, texmtx_tbl[map], (GXBool) 0, GX_PTIDENTITY);
      envTevLoadTexMtxImm(2, (GXTexMtx) texmtx_tbl[map], GX_PTTEXMTX0, GX_MTX2x4);
      stage++;
      map++;
      coord++;
      break;

    case 5:
      GXSetTevColorIn((GXTevStageID) stage, GX_CC_CPREV, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
      GXSetTevAlphaIn((GXTevStageID) stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
      ((EnvTexMtxWork *) wp->unk70)->scale = 0.5f;
      ((EnvTexMtxWork *) wp->unk70)->rotY = 45.0f;
      ((EnvTexMtxWork *) wp->unk70)->rotX = 45.0f;
      envLoadTex(2, map);
      GXSetTexCoordGen2((GXTexCoordID) coord, GX_TG_MTX2x4, GX_TG_NRM, texmtx_tbl[map], (GXBool) 0, GX_PTIDENTITY);
      envTevLoadTexMtxImm(3, (GXTexMtx) texmtx_tbl[map], GX_PTTEXMTX0, GX_MTX2x4);
      stage++;
      map++;
      coord++;
      break;

    case 6:
      GXSetTevColorIn((GXTevStageID) stage, GX_CC_CPREV, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
      GXSetTevAlphaIn((GXTevStageID) stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
      ((EnvTexMtxWork *) wp->unk70)->scale = 0.15f;
      ((EnvTexMtxWork *) wp->unk70)->rotY = 0.0f;
      ((EnvTexMtxWork *) wp->unk70)->rotX = 90.0f;
      envLoadTex(4, map);
      GXSetTexCoordGen2((GXTexCoordID) coord, GX_TG_MTX2x4, GX_TG_NRM, texmtx_tbl[map], (GXBool) 0, GX_PTIDENTITY);
      envTevLoadTexMtxImm(2, (GXTexMtx) texmtx_tbl[map], GX_PTTEXMTX0, GX_MTX2x4);
      stage++;
      map++;
      coord++;
      break;

    case 7:
      GXSetTevColorIn((GXTevStageID) stage, GX_CC_CPREV, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
      GXSetTevAlphaIn((GXTevStageID) stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
      ((EnvTexMtxWork *) wp->unk70)->scale = 0.3f;
      ((EnvTexMtxWork *) wp->unk70)->rotY = 0.0f;
      ((EnvTexMtxWork *) wp->unk70)->rotX = 90.0f;
      envLoadTex(5, map);
      GXSetTexCoordGen2((GXTexCoordID) coord, GX_TG_MTX2x4, GX_TG_NRM, texmtx_tbl[map], (GXBool) 0, GX_PTIDENTITY);
      envTevLoadTexMtxImm(3, (GXTexMtx) texmtx_tbl[map], GX_PTTEXMTX0, GX_MTX2x4);
      stage++;
      map++;
      coord++;
      break;

    case 8:
      GXSetTevColorIn((GXTevStageID) stage, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
      GXSetTevAlphaIn((GXTevStageID) stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
      ((EnvTexMtxWork *) wp->unk70)->scale = 0.5f;
      ((EnvTexMtxWork *) wp->unk70)->rotY = 10.0f;
      ((EnvTexMtxWork *) wp->unk70)->rotX = 45.0f;
      envLoadTex(10, map);
      GXSetTexCoordGen2((GXTexCoordID) coord, GX_TG_MTX2x4, GX_TG_NRM, texmtx_tbl[map], (GXBool) 0, GX_PTIDENTITY);
      envTevLoadTexMtxImm(0, (GXTexMtx) texmtx_tbl[map], GX_PTTEXMTX0, GX_MTX2x4);
      stage++;
      map++;
      coord++;
      break;

    case 9:
      break;

    case 10:
      GXSetTevColorIn((GXTevStageID) stage, GX_CC_CPREV, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
      GXSetTevAlphaIn((GXTevStageID) stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
      GXSetTevKColorSel((GXTevStageID) stage, GX_TEV_KCSEL_K1);
      GXSetTevKColor(GX_KCOLOR1, (GXColor){0x7F, 0x7F, 0x7F, 0x00});
      envLoadTex(9, map);
      GXSetTexCoordGen2((GXTexCoordID) coord, GX_TG_MTX3x4, GX_TG_NRM, texmtx_tbl[map], (GXBool) 0, GX_PTTEXMTX0);
      envTevLoadTexMtxImm(4, (GXTexMtx) texmtx_tbl[map], GX_PTTEXMTX0, GX_MTX3x4);
      stage++;
      map++;
      coord++;
      break;

  }

  info->tevStage = stage;
  info->texMap = coord;
  info->indStage = indStage;
  info->texCoord = map;
}
#endif

#undef ENV_TEX_TAIL

#undef tw

double tan(double);

#ifdef NONMATCHING
void envSetWater(MapTevCallbackInfo* info) {
    MapObject* obj;
    GXTevStageID stage;
    GXTexMapID map;
    GXTexCoordID coord;
    GXIndTexStageID ind;
    u8* buf2;
    s32 i;
    s32 j;
    s32 h;
    s32 w;
    s32 hh;
    s32 hw;
    void* buf;
    f32 scale;
    f32 t;
    Mtx mtx;
    GXTexObj obj1;
    GXTexObj obj2;
    f32 indMtx[2][3];
    Vec pos;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;

    obj = *(MapObject**)info->field_0x0;
    stage = info->tevStage;
    map = info->texCoord;
    coord = info->texMap;
    ind = info->indStage;
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
    if (x0 < 0) {
        x0 = 0;
    }
    if (y0 < 0) {
        y0 = 0;
    }
    if (x1 > gp->fbWidth) {
        x1 = gp->fbWidth;
    }
    if (y1 > gp->efbHeight) {
        y1 = gp->efbHeight;
    }
    h = y1 - y0;
    w = x1 - x0;
    hw = w / 2;
    hh = h / 2;
    buf = smartAlloc(GXGetTexBufferSize((u16)hw, (u16)hh, GX_TF_RGB565, GX_FALSE, 0), 3)->address;
    GXSetTexCopySrc((u16)x0, (u16)y0, (u16)w, (u16)h);
    GXSetTexCopyDst((u16)hw, (u16)hh, GX_TF_RGB565, GX_TRUE);
    GXCopyTex(buf, GX_FALSE);
    GXPixModeSync();
    GXTexModeSync();
    GXInitTexObj(&obj1, buf, (u16)hw, (u16)hh, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&obj1, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    PSMTXMultVec(info->mtx, &(*(MapObject**)info->field_0x0)->center, &pos);
    scale = 1000.0f / PSVECDistance(&camGetCurPtr()->cameraPos, &pos);
    if (scale < 0.0f) {
        scale = 0.0f;
    }
    if (scale > 127.0f) {
        scale = 127.0f;
    }
    buf2 = smartAlloc(GXGetTexBufferSize(64, 64, GX_TF_IA8, GX_FALSE, 0), 3)->address;
    for (i = 0; i < 64; i++) {
        for (j = 0; j < 64; j++) {
            f32 s = sin((f32)gp->retraceCount / 10.0f + (18.849552f * j) / 64.0f);
            u8* p = buf2 + ((i / 4) * 32 + (j / 4) * 512) + ((i % 4) + (j % 4) * 4) * 2;
            p[0] = 0.6f + (scale * s + 128.0f);
            p[1] = 0x80;
        }
    }
    DCFlushRange(buf2, 0x2000);
    GXInitTexObj(&obj2, buf2, 64, 64, GX_TF_IA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(&obj2, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    t = tan(6.2831855f * (camGetPtr(4)->fovY / 2.0f) / 360.0f);
    C_MTXLightFrustum(mtx, gp->efbHeight / 2 - y1, gp->efbHeight / 2 - y0, x0 - gp->fbWidth / 2, x1 - gp->fbWidth / 2,
                      gp->efbHeight / 2.0f / t, 0.5f, 0.5f, 0.5f, 0.5f);
    PSMTXConcat(mtx, camGetCurPtr()->view, mtx);
    PSMTXConcat(mtx, info->mtx, mtx);
    GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
    GXLoadTexMtxImm(mtx, texmtx_tbl[map], GX_MTX3x4);
    GXLoadTexObj(&obj1, (GXTexMapID)map);
    GXLoadTexObj(&obj2, (GXTexMapID)(map + 1U));
    GXSetTevOrder((GXTevStageID)stage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
    GXSetTevColorOp((GXTevStageID)stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp((GXTevStageID)stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn((GXTevStageID)stage, GX_CC_TEXC, GX_CC_CPREV, GX_CC_APREV, GX_CC_ZERO);
    GXSetTevAlphaIn((GXTevStageID)stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevSwapMode((GXTevStageID)stage, GX_TEV_SWAP0, GX_TEV_SWAP0);
    indMtx[0][0] = 0.5f;
    indMtx[0][1] = 0.0f;
    indMtx[0][2] = 0.0f;
    indMtx[1][0] = 0.0f;
    indMtx[1][1] = 0.5f;
    indMtx[1][2] = 0.0f;
    GXSetIndTexMtx(GX_ITM_0, indMtx, 1);
    GXSetIndTexOrder((GXIndTexStageID)ind, (GXTexCoordID)coord, (GXTexMapID)(1 + map));
    GXSetIndTexCoordScale((GXIndTexStageID)ind, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp((GXTevStageID)stage, (GXIndTexStageID)ind, GX_TRUE, GX_FALSE, GX_ITM_0);
    stage++;
    coord++;
    ind++;
    map += 2;
    info->tevStage = stage;
    info->texMap = coord;
    info->indStage = ind;
    info->texCoord = map;
}
#endif

#ifdef NONMATCHING
void envSetYamiView(Mtx view) {
    EnvironmentWork* wp = envGetWork();

    PSMTXCopy(view, (MtxPtr)((u8*)wp + 0xC0));
}
#endif

#ifdef NONMATCHING
void envSetYami(MapTevCallbackInfo* info) {
    static s32 gap_08_80418A8C_sbss = 0;
    static f32 u1 = 0.0f;
    static f32 u2 = 0.0f;
    static u32 v_count = 0;
    EnvironmentWork* wp;
    GXTevStageID stage;
    GXTexMapID map;
    GXTexCoordID coord;
    s32 unk18;
    GXTexObj obj;
    Mtx mtx;
    u32 rc;

    wp = envGetWork();
    stage = info->tevStage;
    map = info->texCoord;
    coord = info->texMap;
    unk18 = info->indStage;


    if (v_count != (rc = gp->retraceCount)) {
        u1 += 0.004f;
        u2 -= 0.004f;
        v_count = rc;
        if (u1 > 10.0f) {
            u1 -= 10.0f;
        }
        if (u2 < 10.0f) {
            u2 += 10.0f;
        }
    }
    GXSetTevColorOp(stage - 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    GXSetTevAlphaOp(stage - 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    C_MTXLightOrtho(mtx, 72.0f, -72.0f, -96.0f, 96.0f, 0.5f, 0.5f, u1, 0.5f);
    PSMTXConcat(mtx, (MtxPtr)wp->unkC0, mtx);
    PSMTXConcat(mtx, info->mtx, mtx);
    GXLoadTexMtxImm(mtx, texmtx_tbl[map], GX_MTX3x4);
    GXSetTexCoordGen2(coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
    C_MTXLightOrtho(mtx, 72.0f, -72.0f, -96.0f, 96.0f, 0.5f, 0.5f, u2, 0.5f);
    PSMTXConcat(mtx, (MtxPtr)wp->unkC0, mtx);
    PSMTXConcat(mtx, info->mtx, mtx);
    GXLoadTexMtxImm(mtx, texmtx_tbl[map + 1], GX_MTX3x4);
    GXSetTexCoordGen2(coord + 1, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map + 1], GX_FALSE, GX_PTIDENTITY);
    TEXGetGXTexObjFromPalette(env_tpl, &obj, 9);
    GXLoadTexObj(&obj, map);
    TEXGetGXTexObjFromPalette(env_tpl, &obj, 10);
    GXLoadTexObj(&obj, map + 1);

    GXSetTevOrder(stage, coord, map, GX_COLOR_NULL);
    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevSwapMode(stage, GX_TEV_SWAP0, GX_TEV_SWAP0);

    GXSetTevOrder(stage + 1, coord + 1, map + 1, GX_COLOR_NULL);
    GXSetTevColorOp(stage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(stage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(stage + 1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXA, GX_CC_ZERO);
    GXSetTevAlphaIn(stage + 1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevSwapMode(stage + 1, GX_TEV_SWAP0, GX_TEV_SWAP0);

    GXSetTevOrder(stage + 2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColorOp(stage + 2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(stage + 2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(stage + 2, GX_CC_C0, GX_CC_ZERO, GX_CC_APREV, GX_CC_ZERO);
    GXSetTevAlphaIn(stage + 2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevSwapMode(stage + 2, GX_TEV_SWAP0, GX_TEV_SWAP0);

    stage += 3;
    coord += 2;
    map += 2;
    info->tevStage = stage;
    info->texMap = coord;
    info->indStage = unk18;
    info->texCoord = map;
}
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: envDisp_DepthOfField (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".sdata2") const u32 dat_8041e510 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041e514 = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_8041e518 = 0xFFFFFFA0;
__declspec(section ".sdata2") const u32 dat_8041e51c = 0x7F7F7F00;
__declspec(section ".sdata2") const f32 float_0p004_8041e520 = 0.004f;
__declspec(section ".sdata2") const f32 float_10_8041e524 = 10.0f;
__declspec(section ".sdata2") const f32 float_72_8041e528 = 72.0f;
__declspec(section ".sdata2") const f32 float_neg72_8041e52c = -72.0f;
__declspec(section ".sdata2") const f32 float_neg96_8041e530 = -96.0f;
__declspec(section ".sdata2") const f32 float_96_8041e534 = 96.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041e538 = 0.5f;
__declspec(section ".sdata2") const f32 float_0_8041e53c = 0.0f;
__declspec(section ".sdata2") const f32 float_1000_8041e540 = 1000.0f;
__declspec(section ".sdata2") const f32 float_127_8041e544 = 127.0f;
__declspec(section ".sdata2") const f32 float_18p85_8041e548 = 18.849552f;
__declspec(section ".sdata2") const f32 float_0p015625_8041e54c = 0.015625f;
__declspec(section ".sdata2") const f32 float_0p6_8041e550 = 0.6f;
__declspec(section ".sdata2") const f32 float_128_8041e554 = 128.0f;
__declspec(section ".sdata2") const f32 float_6p2832_8041e558 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_360_8041e55c = 360.0f;
__declspec(section ".sdata2") const f32 float_45_8041e560 = 45.0f;
__declspec(section ".sdata2") const f32 float_0p15_8041e564 = 0.15f;
__declspec(section ".sdata2") const f32 float_90_8041e568 = 90.0f;
__declspec(section ".sdata2") const f32 float_0p3_8041e56c = 0.3f;
__declspec(section ".sdata2") const f32 float_deg2rad_8041e570 = 0.017453292f;
__declspec(section ".sdata2") const f32 float_1_8041e574 = 1.0f;
__declspec(section ".sdata2") const f32 float_neg1p5708_8041e578 = -1.5707964f;
__declspec(section ".sdata2") const f32 float_0p25_8041e57c = 0.25f;
__declspec(section ".sdata2") const f32 float_3p1416_8041e580 = 3.1415927f;
__declspec(section ".sdata2") const f32 float_180_8041e584 = 180.0f;
__declspec(section ".sdata2") const f32 float_20_8041e588 = 20.0f;
__declspec(section ".sdata2") const f32 float_neg1_8041e58c = -1.0f;
__declspec(section ".sdata2") const f32 float_2_8041e590 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p0001_8041e594 = 0.0001f;
__declspec(section ".sdata2") const f32 float_neg32_8041e598 = -32.0f;
__declspec(section ".sdata2") const f32 float_32_8041e59c = 32.0f;
__declspec(section ".sdata2") const f32 float_300_8041e5a0 = 300.0f;
__declspec(section ".sdata2") const f32 float_0p03705_8041e5a4 = 0.03705f;
__declspec(section ".sdata2") const f32 float_0p4967_8041e5a8 = 0.4967f;
__declspec(section ".sdata2") const f32 float_1p5708_8041e5ac = 1.5707964f;
__declspec(section ".sdata2") const f32 float_4p7124_8041e5b0 = 4.712389f;
__declspec(section ".sdata2") const f32 float_0p00761_8041e5b4 = 0.00761f;
__declspec(section ".sdata2") const f32 float_0p16605_8041e5b8 = 0.16605f;
__declspec(section ".sdata2") const f32 float_100_8041e5bc = 100.0f;
__declspec(section ".sdata2") const f32 float_neg32767_8041e5c0 = -32767.0f;
__declspec(section ".sdata2") const f32 float_255_8041e5c4 = 255.0f;
__declspec(section ".sdata2") const f32 float_120_8041e5c8 = 120.0f;
__declspec(section ".sdata2") const f32 float_5000_8041e5cc = 5000.0f;

void envAddTev(s32 type, MapTevCallbackInfo *info);
__declspec(section ".data") static void* jumptable_80398CF0[] = {
    (char*)envAddTev + 0x1620,
    (char*)envAddTev + 0xF8,
    (char*)envAddTev + 0x370,
    (char*)envAddTev + 0x5E8,
    (char*)envAddTev + 0x82C,
    (char*)envAddTev + 0xA7C,
    (char*)envAddTev + 0xCCC,
    (char*)envAddTev + 0xF20,
    (char*)envAddTev + 0x1174,
    (char*)envAddTev + 0x1620,
    (char*)envAddTev + 0x13C8,
};
void C_MTXLightFrustum(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 scaleS, f32 scaleT, f32 transS, f32 transT);
void C_MTXLightOrtho(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 scaleS, f32 scaleT, f32 transS, f32 transT);
void C_MTXLookAt(Mtx m, const Point3d* camPos, const Vec* camUp, const Point3d* target);
void C_MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void C_VECHalfAngle(const Vec* a, const Vec* b, Vec* half);
void DCFlushRange(void* addr, u32 nBytes);
void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXClearVtxDesc(void);
void GXCopyTex(void* dest, GXBool clear);
u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, u8 mipmap, u8 max_lod);
void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap);
void GXInitTexObjCI(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXCITexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap, u32 tlut_name);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
    f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
    GXBool do_edge_lod, GXAnisotropy max_aniso);
void GXInitTlutObj(GXTlutObj* tlut_obj, void* lut, GXTlutFmt fmt, u16 n_entries);
void GXLoadPosMtxImm(const f32 mtx[3][4], u32 id);
void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXLoadTlut(GXTlutObj* tlut_obj, u32 tlut_name);
void GXPixModeSync(void);
void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op);
void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn);
void GXSetCullMode(GXCullMode mode);
void GXSetCurrentMtx(u32 id);
void GXSetIndTexCoordScale(GXIndTexStageID ind_state, GXIndTexScale scale_s, GXIndTexScale scale_t);
void GXSetIndTexMtx(GXIndTexMtxID mtx_id, const f32 offset[2][3], s8 scale_exp);
void GXSetIndTexOrder(GXIndTexStageID ind_stage, GXTexCoordID tex_coord, GXTexMapID tex_map);
void GXSetLineWidth(u8 width, GXTexOffset texOffsets);
void GXSetNumChans(u8 nChans);
void GXSetNumTevStages(u8 nStages);
void GXSetNumTexGens(u8 nTexGens);
void GXSetProjection(const f32 mtx[4][4], GXProjectionType type);
void GXSetScissor(u32 left, u32 top, u32 wd, u32 ht);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColor(GXTevRegID id, GXColor color);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevIndWarp(GXTevStageID tev_stage, GXIndTexStageID ind_stage, u8 signed_offset, u8 replace_mode, GXIndTexMtxID matrix_sel);
void GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel sel);
void GXSetTevKColor(GXTevKColorID id, GXColor color);
void GXSetTevKColorSel(GXTevStageID stage, GXTevKColorSel sel);
void GXSetTevOp(GXTevStageID id, GXTevMode mode);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras_sel, GXTevSwapSel tex_sel);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx);
void GXSetTexCopyDst(u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap);
void GXSetTexCopySrc(u16 left, u16 top, u16 wd, u16 ht);
void GXSetViewport(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz);
void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac);
void GXSetVtxDesc(GXAttr attr, GXAttrType type);
void GXSetZCompLoc(GXBool before_tex);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
void GXSetZScaleOffset(f32 scale, f32 offset);
void GXTexModeSync(void);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXCopy(const Mtx src, Mtx dst);
void PSMTXIdentity(Mtx m);
u32 PSMTXInvXpose(const Mtx src, Mtx invX);
u32 PSMTXInverse(const Mtx src, Mtx inv);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXMultVecSR(const Mtx m, const Vec* src, Vec* dst);
void PSMTXRotAxisRad(Mtx m, const Vec* axis, f32 rad);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void PSVECCrossProduct(const Vec* a, const Vec* b, Vec* axb);
f32 PSVECDistance(const Vec* a, const Vec* b);
f32 PSVECDotProduct(const Vec* a, const Vec* b);
void PSVECNormalize(const Vec* src, Vec* dst);
TEXDescriptor* TEXGet(TEXPalette* pal, u32 id);
void TEXGetGXTexObjFromPalette(TEXPalette* pal, GXTexObj* to, u32 id);
void __cvt_ull_flt();
void __div2u();
void* _mapAlloc(u32 size);
void _mapFree(void* alloc);
CameraEntry* camGetCurPtr(void);
CameraEntry* camGetPtr(CameraId cameraId);
void envTevLoadTexMtxImm(s32 type, GXTexMtx id, GXTexMtx id2, GXTexMtxType mtxType);
void *memset(void *dest, int ch, size_t count);
smartEntry* smartAlloc(u32 size, u8 type);
static u32 gap_08_80418A8C_sbss_pad[1]; // FAKE: target .sbss pad after v_count (reverse emit order)
GXTexObj* smartTexObj(GXTexObj* obj, void** image_ptr);
static u32 g5_v_count_s761[1];
static u32 g5_u2_s760[1];
static u32 g5_u1_s759[1];
static u32 g5_a_s655[1];
static u32 g5_frame_cnt_s541[1];
asm void envSetYami(MapTevCallbackInfo* info) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	lis r4, work@ha
	stw r0, 0x84(r1)
	stmw r24, 0x60(r1)
	addi r30, r4, work@l
	mr r24, r3
	lwz r5, gp(r13)
	lwz r0, 0x14(r5)
	cmpwi r0, 0x0
	beq @1
	addi r30, r30, 0xf0
	@1:
	lwz r0, g5_v_count_s761(r13)
	lwz r3, 0x1c(r5)
	lwz r28, 0xc(r24)
	cmplw r0, r3
	lwz r27, 0x10(r24)
	lwz r26, 0x14(r24)
	lwz r25, 0x18(r24)
	beq @2
	lfs f0, g5_u1_s759(r13)
	lfs f3, float_0p004_8041e520(r2)
	lfs f1, g5_u2_s760(r13)
	fadds f2, f0, f3
	lfs f0, float_10_8041e524(r2)
	fsubs f1, f1, f3
	stw r3, g5_v_count_s761(r13)
	fcmpo cr0, f2, f0
	stfs f2, g5_u1_s759(r13)
	stfs f1, g5_u2_s760(r13)
	ble @3
	fsubs f0, f2, f0
	stfs f0, g5_u1_s759(r13)
	@3:
	lfs f1, g5_u2_s760(r13)
	lfs f0, float_10_8041e524(r2)
	fcmpo cr0, f1, f0
	bge @2
	fadds f0, f1, f0
	stfs f0, g5_u2_s760(r13)
	@2:
	subi r3, r28, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x1
	bl GXSetTevColorOp
	subi r3, r28, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x1
	bl GXSetTevAlphaOp
	lfs f5, float_0p5_8041e538(r2)
	addi r3, r1, 0x28
	lfs f1, float_72_8041e528(r2)
	fmr f6, f5
	lfs f2, float_neg72_8041e52c(r2)
	fmr f8, f5
	lfs f3, float_neg96_8041e530(r2)
	lfs f4, float_96_8041e534(r2)
	lfs f7, g5_u1_s759(r13)
	bl C_MTXLightOrtho
	addi r3, r1, 0x28
	addi r4, r30, 0xc0
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x28
	lwz r4, 0x4(r24)
	mr r5, r3
	bl PSMTXConcat
	lis r3, dat_802f9338@ha
	slwi r29, r27, 2
	addi r31, r3, dat_802f9338@l
	addi r3, r1, 0x28
	lwzx r4, r31, r29
	li r5, 0x0
	bl GXLoadTexMtxImm
	lwzx r6, r31, r29
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lfs f5, float_0p5_8041e538(r2)
	addi r3, r1, 0x28
	lfs f1, float_72_8041e528(r2)
	fmr f6, f5
	lfs f2, float_neg72_8041e52c(r2)
	fmr f8, f5
	lfs f3, float_neg96_8041e530(r2)
	lfs f4, float_96_8041e534(r2)
	lfs f7, g5_u2_s760(r13)
	bl C_MTXLightOrtho
	addi r3, r1, 0x28
	addi r4, r30, 0xc0
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x28
	lwz r4, 0x4(r24)
	mr r5, r3
	bl PSMTXConcat
	lis r4, dat_802f9338@ha
	addi r3, r1, 0x28
	addi r0, r4, dat_802f9338@l
	li r5, 0x0
	add r29, r0, r29
	lwzu r4, 0x4(r29)
	bl GXLoadTexMtxImm
	lwz r6, 0x0(r29)
	addi r3, r26, 0x1
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwz r3, env_tpl(r13)
	addi r4, r1, 0x8
	li r5, 0x9
	bl TEXGetGXTexObjFromPalette
	mr r4, r27
	addi r3, r1, 0x8
	bl GXLoadTexObj
	lwz r3, env_tpl(r13)
	addi r4, r1, 0x8
	li r5, 0xa
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x8
	addi r4, r27, 0x1
	bl GXLoadTexObj
	mr r3, r28
	mr r4, r26
	mr r5, r27
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r28
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r28
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r28
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	mr r3, r28
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x4
	bl GXSetTevAlphaIn
	mr r3, r28
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	addi r3, r28, 0x1
	addi r4, r26, 0x1
	addi r5, r27, 0x1
	li r6, 0xff
	bl GXSetTevOrder
	addi r3, r28, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	addi r3, r28, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	addi r3, r28, 0x1
	li r4, 0xf
	li r5, 0x0
	li r6, 0x9
	li r7, 0xf
	bl GXSetTevColorIn
	addi r3, r28, 0x1
	li r4, 0x7
	li r5, 0x0
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	addi r3, r28, 0x1
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	addi r3, r28, 0x2
	li r4, 0xff
	li r5, 0xff
	li r6, 0xff
	bl GXSetTevOrder
	addi r3, r28, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	addi r3, r28, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	addi r3, r28, 0x2
	li r4, 0x2
	li r5, 0xf
	li r6, 0x1
	li r7, 0xf
	bl GXSetTevColorIn
	addi r3, r28, 0x2
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x1
	bl GXSetTevAlphaIn
	addi r3, r28, 0x2
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	addi r28, r28, 0x3
	addi r26, r26, 0x2
	stw r28, 0xc(r24)
	addi r27, r27, 0x2
	stw r26, 0x14(r24)
	stw r25, 0x18(r24)
	stw r27, 0x10(r24)
	lmw r24, 0x60(r1)
	lwz r0, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm void envSetYamiView(Mtx view) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, work@ha
	stw r0, 0x14(r1)
	addi r4, r4, work@l
	lwz r5, gp(r13)
	lwz r0, 0x14(r5)
	cmpwi r0, 0x0
	beq @1
	addi r4, r4, 0xf0
	@1:
	addi r4, r4, 0xc0
	bl PSMTXCopy
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void envSetWater(MapTevCallbackInfo* info) {
	nofralloc
	stwu r1, -0x190(r1)
	mflr r0
	stw r0, 0x194(r1)
	stfd f31, 0x180(r1)
	psq_st f31, 0x188(r1), 0, 0
	stfd f30, 0x170(r1)
	psq_st f30, 0x178(r1), 0, 0
	stfd f29, 0x160(r1)
	psq_st f29, 0x168(r1), 0, 0
	stfd f28, 0x150(r1)
	psq_st f28, 0x158(r1), 0, 0
	stfd f27, 0x140(r1)
	psq_st f27, 0x148(r1), 0, 0
	stfd f26, 0x130(r1)
	psq_st f26, 0x138(r1), 0, 0
	stfd f25, 0x120(r1)
	psq_st f25, 0x128(r1), 0, 0
	stfd f24, 0x110(r1)
	psq_st f24, 0x118(r1), 0, 0
	stmw r17, 0xd4(r1)
	mr r17, r3
	lwz r3, 0x0(r3)
	lwz r28, 0xc(r17)
	lwz r4, 0x0(r3)
	lwz r27, 0x10(r17)
	rlwinm. r0, r4, 0, 26, 26
	lwz r26, 0x14(r17)
	lwz r25, 0x18(r17)
	beq @1
	b @2
	@3:
	lwz r4, 0x0(r3)
	rlwinm. r0, r4, 0, 27, 27
	beq @2
	rlwinm. r0, r4, 0, 2, 2
	bne @4
	oris r0, r4, 0x2000
	stw r0, 0x0(r3)
	b @5
	@4:
	lhz r21, 0xec(r3)
	lhz r20, 0xee(r3)
	lhz r19, 0xf0(r3)
	lhz r18, 0xf2(r3)
	b @6
	@2:
	lwz r3, 0xe0(r3)
	cmplwi r3, 0x0
	bne @3
	b @6
	@1:
	rlwinm. r0, r4, 0, 2, 2
	bne @7
	oris r0, r4, 0x2000
	stw r0, 0x0(r3)
	b @5
	@7:
	lhz r21, 0xec(r3)
	lhz r20, 0xee(r3)
	lhz r19, 0xf0(r3)
	lhz r18, 0xf2(r3)
	@6:
	cmpwi r21, 0x3ff
	beq @5
	cmpwi r20, 0x3ff
	beq @5
	cmpwi r19, 0x3ff
	beq @5
	cmpwi r18, 0x3ff
	bne @8
	b @5
	@8:
	cmpwi r21, 0x0
	bne @9
	cmpwi r20, 0x0
	bne @9
	cmpwi r19, 0x0
	bne @9
	cmpwi r18, 0x0
	beq @5
	@9:
	clrlwi r0, r21, 31
	clrlwi r4, r20, 31
	subf. r21, r0, r21
	clrlwi r3, r19, 31
	clrlwi r0, r18, 31
	subf r20, r4, r20
	add r19, r19, r3
	add r18, r18, r0
	bge @10
	li r21, 0x0
	@10:
	cmpwi r20, 0x0
	bge @11
	li r20, 0x0
	@11:
	lwz r3, gp(r13)
	lhz r0, 0x170(r3)
	cmpw r19, r0
	ble @12
	mr r19, r0
	@12:
	lhz r0, 0x172(r3)
	cmpw r18, r0
	ble @13
	mr r18, r0
	@13:
	subf r23, r21, r19
	subf r22, r20, r18
	srwi r0, r23, 31
	li r5, 0x4
	add r3, r0, r23
	srwi r0, r22, 31
	srawi r29, r3, 1
	li r6, 0x0
	add r0, r0, r22
	li r7, 0x0
	srawi r24, r0, 1
	clrlwi r3, r29, 16
	clrlwi r4, r24, 16
	bl GXGetTexBufferSize
	li r4, 0x3
	bl smartAlloc
	lwz r30, 0x0(r3)
	clrlwi r3, r21, 16
	clrlwi r4, r20, 16
	clrlwi r5, r23, 16
	clrlwi r6, r22, 16
	bl GXSetTexCopySrc
	clrlwi r3, r29, 16
	clrlwi r4, r24, 16
	li r5, 0x4
	li r6, 0x1
	bl GXSetTexCopyDst
	mr r3, r30
	li r4, 0x0
	bl GXCopyTex
	bl GXPixModeSync
	bl GXTexModeSync
	mr r4, r30
	addi r3, r1, 0x54
	clrlwi r5, r29, 16
	clrlwi r6, r24, 16
	li r7, 0x4
	li r8, 0x0
	li r9, 0x0
	li r10, 0x0
	bl GXInitTexObj
	lfs f1, float_0_8041e53c(r2)
	addi r3, r1, 0x54
	li r4, 0x0
	li r5, 0x0
	fmr f2, f1
	li r6, 0x0
	fmr f3, f1
	li r7, 0x0
	li r8, 0x0
	bl GXInitTexObjLOD
	lwz r4, 0x0(r17)
	addi r5, r1, 0x10
	lwz r3, 0x4(r17)
	addi r4, r4, 0x10
	bl PSMTXMultVec
	bl camGetCurPtr
	addi r3, r3, 0xc
	addi r4, r1, 0x10
	bl PSVECDistance
	lfs f2, float_1000_8041e540(r2)
	lfs f0, float_0_8041e53c(r2)
	fdivs f31, f2, f1
	fcmpo cr0, f31, f0
	bge @14
	fmr f31, f0
	@14:
	lfs f0, float_127_8041e544(r2)
	fcmpo cr0, f31, f0
	ble @15
	fmr f31, f0
	@15:
	li r3, 0x40
	li r4, 0x40
	li r5, 0x3
	li r6, 0x0
	li r7, 0x0
	bl GXGetTexBufferSize
	li r4, 0x3
	bl smartAlloc
	lis r5, double_to_int_802f93a0@ha
	lis r4, double_to_int_mask_802f93a8@ha
	lwz r24, 0x0(r3)
	li r23, 0x0
	lfs f24, float_18p85_8041e548(r2)
	lis r30, 0x4330
	lfd f25, double_to_int_802f93a0@l(r5)
	lfs f26, float_0p015625_8041e54c(r2)
	lfd f27, double_to_int_mask_802f93a8@l(r4)
	lfs f28, float_10_8041e524(r2)
	lfs f29, float_0p6_8041e550(r2)
	lfs f30, float_128_8041e554(r2)
	@16:
	slwi r0, r23, 30
	srwi r3, r23, 31
	srawi r4, r23, 2
	li r22, 0x0
	subf r0, r3, r0
	addze r4, r4
	rotlwi r0, r0, 2
	add r29, r0, r3
	slwi r31, r4, 5
	@17:
	lwz r3, gp(r13)
	xoris r4, r22, 0x8000
	stw r30, 0xb0(r1)
	lwz r0, 0x1c(r3)
	stw r4, 0xac(r1)
	stw r0, 0xb4(r1)
	lfd f0, 0xb0(r1)
	stw r30, 0xa8(r1)
	fsubs f0, f0, f27
	lfd f1, 0xa8(r1)
	fdivs f0, f0, f28
	fsubs f1, f1, f25
	fmuls f1, f24, f1
	fmadds f1, f1, f26, f0
	bl sin
	frsp f0, f1
	srawi r0, r22, 2
	addze r4, r0
	srwi r3, r22, 31
	slwi r0, r22, 30
	addi r22, r22, 0x1
	fmadds f0, f31, f0, f30
	subf r0, r3, r0
	rotlwi r0, r0, 2
	slwi r4, r4, 9
	add r0, r0, r3
	cmpwi r22, 0x40
	fadds f0, f29, f0
	slwi r0, r0, 2
	add r0, r29, r0
	add r4, r31, r4
	slwi r3, r0, 1
	fctiwz f0, f0
	add r4, r4, r3
	li r0, 0x80
	add r4, r24, r4
	stfd f0, 0xb8(r1)
	lwz r3, 0xbc(r1)
	stb r3, 0x0(r4)
	stb r0, 0x1(r4)
	blt @17
	addi r23, r23, 0x1
	cmpwi r23, 0x40
	blt @16
	mr r3, r24
	li r4, 0x2000
	bl DCFlushRange
	mr r4, r24
	addi r3, r1, 0x34
	li r5, 0x40
	li r6, 0x40
	li r7, 0x3
	li r8, 0x1
	li r9, 0x1
	li r10, 0x0
	bl GXInitTexObj
	lfs f1, float_0_8041e53c(r2)
	addi r3, r1, 0x34
	li r4, 0x1
	li r5, 0x1
	fmr f2, f1
	li r6, 0x0
	fmr f3, f1
	li r7, 0x0
	li r8, 0x0
	bl GXInitTexObjLOD
	li r3, 0x4
	bl camGetPtr
	lfs f2, 0x38(r3)
	lfs f0, float_0p5_8041e538(r2)
	lfs f1, float_6p2832_8041e558(r2)
	fmuls f2, f2, f0
	lfs f0, float_360_8041e55c(r2)
	fmuls f1, f1, f2
	fdivs f1, f1, f0
	bl tan
	lwz r4, gp(r13)
	lis r6, 0x4330
	lfs f6, float_0p5_8041e538(r2)
	lis r3, double_to_int_mask_802f93a8@ha
	lhz r5, 0x172(r4)
	lhz r0, 0x170(r4)
	lis r4, double_to_int_802f93a0@ha
	stw r5, 0xcc(r1)
	extrwi r7, r5, 15, 16
	addi r8, r4, double_to_int_802f93a0@l
	lfd f2, double_to_int_mask_802f93a8@l(r3)
	stw r6, 0xc8(r1)
	srwi r0, r0, 1
	subf r3, r0, r21
	subf r5, r18, r7
	lfd f0, 0xc8(r1)
	subf r4, r20, r7
	xoris r7, r5, 0x8000
	subf r0, r0, r19
	fsubs f0, f0, f2
	xoris r5, r4, 0x8000
	frsp f2, f1
	xoris r4, r3, 0x8000
	xoris r0, r0, 0x8000
	stw r4, 0xac(r1)
	fmuls f0, f0, f6
	stw r6, 0xa8(r1)
	lfd f4, 0x0(r8)
	fmr f7, f6
	stw r7, 0xbc(r1)
	fmr f8, f6
	fdivs f5, f0, f2
	stw r6, 0xb8(r1)
	lfd f0, 0xa8(r1)
	addi r3, r1, 0x74
	lfd f1, 0xb8(r1)
	stw r5, 0xb4(r1)
	stw r6, 0xb0(r1)
	fsubs f3, f0, f4
	fsubs f1, f1, f4
	lfd f2, 0xb0(r1)
	stw r0, 0xc4(r1)
	fsubs f2, f2, f4
	stw r6, 0xc0(r1)
	lfd f0, 0xc0(r1)
	stfs f6, 0x8(r1)
	fsubs f4, f0, f4
	bl C_MTXLightFrustum
	bl camGetCurPtr
	mr r4, r3
	addi r3, r1, 0x74
	mr r5, r3
	addi r4, r4, 0x11c
	bl PSMTXConcat
	addi r3, r1, 0x74
	lwz r4, 0x4(r17)
	mr r5, r3
	bl PSMTXConcat
	lis r3, dat_802f9338@ha
	slwi r19, r27, 2
	addi r18, r3, dat_802f9338@l
	mr r3, r26
	lwzx r6, r18, r19
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwzx r4, r18, r19
	addi r3, r1, 0x74
	li r5, 0x0
	bl GXLoadTexMtxImm
	mr r4, r27
	addi r3, r1, 0x54
	bl GXLoadTexObj
	addi r3, r1, 0x34
	addi r4, r27, 0x1
	bl GXLoadTexObj
	mr r3, r28
	mr r4, r26
	mr r5, r27
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r28
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r28
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r28
	li r4, 0x8
	li r5, 0x0
	li r6, 0x1
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r28
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x4
	bl GXSetTevAlphaIn
	mr r3, r28
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	lfs f0, float_0_8041e53c(r2)
	addi r4, r1, 0x1c
	lfs f1, float_0p5_8041e538(r2)
	li r3, 0x1
	stfs f0, 0x20(r1)
	li r5, 0x1
	stfs f1, 0x1c(r1)
	stfs f0, 0x24(r1)
	stfs f0, 0x28(r1)
	stfs f1, 0x2c(r1)
	stfs f0, 0x30(r1)
	bl GXSetIndTexMtx
	mr r3, r25
	mr r4, r26
	addi r5, r27, 0x1
	bl GXSetIndTexOrder
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	bl GXSetIndTexCoordScale
	mr r3, r28
	mr r4, r25
	li r5, 0x1
	li r6, 0x0
	li r7, 0x1
	bl GXSetTevIndWarp
	addi r28, r28, 0x1
	addi r26, r26, 0x1
	stw r28, 0xc(r17)
	addi r25, r25, 0x1
	addi r27, r27, 0x2
	stw r26, 0x14(r17)
	stw r25, 0x18(r17)
	stw r27, 0x10(r17)
	@5:
	psq_l f31, 0x188(r1), 0, 0
	lfd f31, 0x180(r1)
	psq_l f30, 0x178(r1), 0, 0
	lfd f30, 0x170(r1)
	psq_l f29, 0x168(r1), 0, 0
	lfd f29, 0x160(r1)
	psq_l f28, 0x158(r1), 0, 0
	lfd f28, 0x150(r1)
	psq_l f27, 0x148(r1), 0, 0
	lfd f27, 0x140(r1)
	psq_l f26, 0x138(r1), 0, 0
	lfd f26, 0x130(r1)
	psq_l f25, 0x128(r1), 0, 0
	lfd f25, 0x120(r1)
	psq_l f24, 0x118(r1), 0, 0
	lfd f24, 0x110(r1)
	lmw r17, 0xd4(r1)
	lwz r0, 0x194(r1)
	mtlr r0
	addi r1, r1, 0x190
	blr
}

asm void envAddTev(s32 type, MapTevCallbackInfo *info) {
	nofralloc
	stwu r1, -0x200(r1)
	mflr r0
	lis r5, work@ha
	stw r0, 0x204(r1)
	stmw r25, 0x1e4(r1)
	addi r31, r5, work@l
	mr r25, r3
	mr r26, r4
	lwz r6, gp(r13)
	lwz r0, 0x14(r6)
	cmpwi r0, 0x0
	beq @1
	addi r31, r31, 0xf0
	@1:
	cmpwi r25, 0x0
	lwz r30, 0xc(r26)
	lwz r29, 0x10(r26)
	lwz r28, 0x14(r26)
	lwz r27, 0x18(r26)
	beq @2
	bl camGetCurPtr
	lwz r4, 0x4(r26)
	addi r5, r1, 0x1a0
	addi r3, r3, 0x11c
	bl PSMTXConcat
	bl camGetCurPtr
	addi r3, r3, 0x11c
	addi r0, r1, 0x1a0
	stw r3, 0x70(r31)
	mr r3, r30
	mr r4, r28
	mr r5, r29
	lwz r7, 0x4(r26)
	li r6, 0xff
	stw r7, 0x74(r31)
	stw r0, 0x78(r31)
	bl GXSetTevOrder
	mr r3, r30
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r30
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r30
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	cmplwi r25, 0xa
	bgt @3
	lis r3, jumptable_80398CF0@ha
	slwi r0, r25, 2
	addi r3, r3, jumptable_80398CF0@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@4:
	mr r3, r30
	li r4, 0xf
	li r5, 0x0
	li r6, 0x8
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r30
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	lfs f0, float_10_8041e524(r2)
	lis r3, double_to_int_mask_802f93a8@ha
	lis r0, 0x4330
	lwz r5, gp(r13)
	stfs f0, 0x80(r31)
	li r4, 0x6
	lfd f2, double_to_int_mask_802f93a8@l(r3)
	lwz r3, 0x1c(r5)
	stw r0, 0x1d0(r1)
	addi r0, r3, 0x2d
	lfs f0, float_0p5_8041e538(r2)
	stw r0, 0x1d4(r1)
	lwz r3, env_tpl(r13)
	lfd f1, 0x1d0(r1)
	fsubs f1, f1, f2
	stfs f1, 0x84(r31)
	stfs f0, 0x7c(r31)
	bl TEXGet
	lwz r0, 0x4(r3)
	cmplwi r0, 0x0
	beq @5
	lwz r3, env_tpl(r13)
	li r4, 0x6
	bl TEXGet
	mr r25, r3
	lwz r4, 0x0(r3)
	lbz r3, 0x21(r4)
	lbz r0, 0x22(r4)
	cmplw r3, r0
	bne @6
	li r31, 0x0
	b @7
	@6:
	li r31, 0x1
	@7:
	lwz r6, 0x4(r25)
	addi r3, r1, 0x74
	lwz r4, 0x8(r6)
	lwz r5, 0x4(r6)
	lhz r6, 0x0(r6)
	bl GXInitTlutObj
	lwz r7, 0x0(r25)
	li r0, 0x0
	mr r10, r31
	addi r3, r1, 0x180
	stw r0, 0x8(r1)
	li r8, 0x0
	li r9, 0x0
	lwz r4, 0x8(r7)
	lhz r5, 0x2(r7)
	lhz r6, 0x0(r7)
	lwz r7, 0x4(r7)
	bl GXInitTexObjCI
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d0(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0x180
	stw r6, 0x1d4(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d0(r1)
	stw r0, 0x1dc(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d8(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d8(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	addi r3, r1, 0x74
	li r4, 0x0
	bl GXLoadTlut
	mr r4, r29
	addi r3, r1, 0x180
	bl GXLoadTexObj
	b @8
	@5:
	lwz r3, env_tpl(r13)
	li r4, 0x6
	bl TEXGet
	mr r25, r3
	lwz r7, 0x0(r3)
	lbz r3, 0x21(r7)
	lbz r0, 0x22(r7)
	cmplw r3, r0
	bne @9
	li r10, 0x0
	b @10
	@9:
	li r10, 0x1
	@10:
	lwz r4, 0x8(r7)
	addi r3, r1, 0x180
	lhz r5, 0x2(r7)
	li r8, 0x0
	lhz r6, 0x0(r7)
	li r9, 0x0
	lwz r7, 0x4(r7)
	bl GXInitTexObj
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0x180
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	mr r4, r29
	addi r3, r1, 0x180
	bl GXLoadTexObj
	@8:
	lis r3, dat_802f9338@ha
	slwi r31, r29, 2
	addi r25, r3, dat_802f9338@l
	mr r3, r28
	lwzx r6, r25, r31
	li r4, 0x1
	li r5, 0x1
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwzx r4, r25, r31
	li r3, 0x0
	li r5, 0x40
	li r6, 0x1
	bl envTevLoadTexMtxImm
	addi r30, r30, 0x1
	addi r28, r28, 0x1
	addi r29, r29, 0x1
	b @3
	@11:
	mr r3, r30
	li r4, 0xf
	li r5, 0x0
	li r6, 0x8
	li r7, 0x9
	bl GXSetTevColorIn
	mr r3, r30
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	lfs f0, float_10_8041e524(r2)
	lis r3, double_to_int_mask_802f93a8@ha
	lis r0, 0x4330
	lwz r5, gp(r13)
	stfs f0, 0x80(r31)
	li r4, 0x8
	lfd f2, double_to_int_mask_802f93a8@l(r3)
	lwz r3, 0x1c(r5)
	stw r0, 0x1d8(r1)
	addi r0, r3, 0x2d
	lfs f0, float_0p5_8041e538(r2)
	stw r0, 0x1dc(r1)
	lwz r3, env_tpl(r13)
	lfd f1, 0x1d8(r1)
	fsubs f1, f1, f2
	stfs f1, 0x84(r31)
	stfs f0, 0x7c(r31)
	bl TEXGet
	lwz r0, 0x4(r3)
	cmplwi r0, 0x0
	beq @12
	lwz r3, env_tpl(r13)
	li r4, 0x8
	bl TEXGet
	mr r25, r3
	lwz r4, 0x0(r3)
	lbz r3, 0x21(r4)
	lbz r0, 0x22(r4)
	cmplw r3, r0
	bne @13
	li r31, 0x0
	b @14
	@13:
	li r31, 0x1
	@14:
	lwz r6, 0x4(r25)
	addi r3, r1, 0x68
	lwz r4, 0x8(r6)
	lwz r5, 0x4(r6)
	lhz r6, 0x0(r6)
	bl GXInitTlutObj
	lwz r7, 0x0(r25)
	li r0, 0x0
	mr r10, r31
	addi r3, r1, 0x160
	stw r0, 0x8(r1)
	li r8, 0x0
	li r9, 0x0
	lwz r4, 0x8(r7)
	lhz r5, 0x2(r7)
	lhz r6, 0x0(r7)
	lwz r7, 0x4(r7)
	bl GXInitTexObjCI
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0x160
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	addi r3, r1, 0x68
	li r4, 0x0
	bl GXLoadTlut
	mr r4, r29
	addi r3, r1, 0x160
	bl GXLoadTexObj
	b @15
	@12:
	lwz r3, env_tpl(r13)
	li r4, 0x8
	bl TEXGet
	mr r25, r3
	lwz r7, 0x0(r3)
	lbz r3, 0x21(r7)
	lbz r0, 0x22(r7)
	cmplw r3, r0
	bne @16
	li r10, 0x0
	b @17
	@16:
	li r10, 0x1
	@17:
	lwz r4, 0x8(r7)
	addi r3, r1, 0x160
	lhz r5, 0x2(r7)
	li r8, 0x0
	lhz r6, 0x0(r7)
	li r9, 0x0
	lwz r7, 0x4(r7)
	bl GXInitTexObj
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0x160
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	mr r4, r29
	addi r3, r1, 0x160
	bl GXLoadTexObj
	@15:
	lis r3, dat_802f9338@ha
	slwi r31, r29, 2
	addi r25, r3, dat_802f9338@l
	mr r3, r28
	lwzx r6, r25, r31
	li r4, 0x1
	li r5, 0x1
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwzx r4, r25, r31
	li r3, 0x0
	li r5, 0x40
	li r6, 0x1
	bl envTevLoadTexMtxImm
	addi r30, r30, 0x1
	addi r28, r28, 0x1
	addi r29, r29, 0x1
	b @3
	@18:
	mr r3, r30
	li r4, 0x0
	li r5, 0xf
	li r6, 0x8
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r30
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	lfs f0, float_0p5_8041e538(r2)
	li r4, 0x0
	lwz r3, env_tpl(r13)
	stfs f0, 0x7c(r31)
	bl TEXGet
	lwz r0, 0x4(r3)
	cmplwi r0, 0x0
	beq @19
	lwz r3, env_tpl(r13)
	li r4, 0x0
	bl TEXGet
	mr r25, r3
	lwz r4, 0x0(r3)
	lbz r3, 0x21(r4)
	lbz r0, 0x22(r4)
	cmplw r3, r0
	bne @20
	li r31, 0x0
	b @21
	@20:
	li r31, 0x1
	@21:
	lwz r6, 0x4(r25)
	addi r3, r1, 0x5c
	lwz r4, 0x8(r6)
	lwz r5, 0x4(r6)
	lhz r6, 0x0(r6)
	bl GXInitTlutObj
	lwz r7, 0x0(r25)
	li r0, 0x0
	mr r10, r31
	addi r3, r1, 0x140
	stw r0, 0x8(r1)
	li r8, 0x0
	li r9, 0x0
	lwz r4, 0x8(r7)
	lhz r5, 0x2(r7)
	lhz r6, 0x0(r7)
	lwz r7, 0x4(r7)
	bl GXInitTexObjCI
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0x140
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	addi r3, r1, 0x5c
	li r4, 0x0
	bl GXLoadTlut
	mr r4, r29
	addi r3, r1, 0x140
	bl GXLoadTexObj
	b @22
	@19:
	lwz r3, env_tpl(r13)
	li r4, 0x0
	bl TEXGet
	mr r25, r3
	lwz r7, 0x0(r3)
	lbz r3, 0x21(r7)
	lbz r0, 0x22(r7)
	cmplw r3, r0
	bne @23
	li r10, 0x0
	b @24
	@23:
	li r10, 0x1
	@24:
	lwz r4, 0x8(r7)
	addi r3, r1, 0x140
	lhz r5, 0x2(r7)
	li r8, 0x0
	lhz r6, 0x0(r7)
	li r9, 0x0
	lwz r7, 0x4(r7)
	bl GXInitTexObj
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0x140
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	mr r4, r29
	addi r3, r1, 0x140
	bl GXLoadTexObj
	@22:
	lis r3, dat_802f9338@ha
	slwi r31, r29, 2
	addi r25, r3, dat_802f9338@l
	mr r3, r28
	lwzx r6, r25, r31
	li r4, 0x1
	li r5, 0x1
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwzx r4, r25, r31
	li r3, 0x1
	li r5, 0x40
	li r6, 0x1
	bl envTevLoadTexMtxImm
	addi r30, r30, 0x1
	addi r29, r29, 0x1
	addi r28, r28, 0x1
	b @3
	@25:
	mr r3, r30
	li r4, 0x0
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	mr r3, r30
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	lfs f1, float_0p5_8041e538(r2)
	li r4, 0x1
	lfs f0, float_45_8041e560(r2)
	stfs f1, 0x7c(r31)
	lwz r3, env_tpl(r13)
	stfs f0, 0x80(r31)
	stfs f0, 0x84(r31)
	bl TEXGet
	lwz r0, 0x4(r3)
	cmplwi r0, 0x0
	beq @26
	lwz r3, env_tpl(r13)
	li r4, 0x1
	bl TEXGet
	mr r25, r3
	lwz r4, 0x0(r3)
	lbz r3, 0x21(r4)
	lbz r0, 0x22(r4)
	cmplw r3, r0
	bne @27
	li r31, 0x0
	b @28
	@27:
	li r31, 0x1
	@28:
	lwz r6, 0x4(r25)
	addi r3, r1, 0x50
	lwz r4, 0x8(r6)
	lwz r5, 0x4(r6)
	lhz r6, 0x0(r6)
	bl GXInitTlutObj
	lwz r7, 0x0(r25)
	li r0, 0x0
	mr r10, r31
	addi r3, r1, 0x120
	stw r0, 0x8(r1)
	li r8, 0x0
	li r9, 0x0
	lwz r4, 0x8(r7)
	lhz r5, 0x2(r7)
	lhz r6, 0x0(r7)
	lwz r7, 0x4(r7)
	bl GXInitTexObjCI
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0x120
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	addi r3, r1, 0x50
	li r4, 0x0
	bl GXLoadTlut
	mr r4, r29
	addi r3, r1, 0x120
	bl GXLoadTexObj
	b @29
	@26:
	lwz r3, env_tpl(r13)
	li r4, 0x1
	bl TEXGet
	mr r25, r3
	lwz r7, 0x0(r3)
	lbz r3, 0x21(r7)
	lbz r0, 0x22(r7)
	cmplw r3, r0
	bne @30
	li r10, 0x0
	b @31
	@30:
	li r10, 0x1
	@31:
	lwz r4, 0x8(r7)
	addi r3, r1, 0x120
	lhz r5, 0x2(r7)
	li r8, 0x0
	lhz r6, 0x0(r7)
	li r9, 0x0
	lwz r7, 0x4(r7)
	bl GXInitTexObj
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0x120
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	mr r4, r29
	addi r3, r1, 0x120
	bl GXLoadTexObj
	@29:
	lis r3, dat_802f9338@ha
	slwi r31, r29, 2
	addi r25, r3, dat_802f9338@l
	mr r3, r28
	lwzx r6, r25, r31
	li r4, 0x1
	li r5, 0x1
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwzx r4, r25, r31
	li r3, 0x2
	li r5, 0x40
	li r6, 0x1
	bl envTevLoadTexMtxImm
	addi r30, r30, 0x1
	addi r29, r29, 0x1
	addi r28, r28, 0x1
	b @3
	@32:
	mr r3, r30
	li r4, 0x0
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	mr r3, r30
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	lfs f1, float_0p5_8041e538(r2)
	li r4, 0x2
	lfs f0, float_45_8041e560(r2)
	stfs f1, 0x7c(r31)
	lwz r3, env_tpl(r13)
	stfs f0, 0x80(r31)
	stfs f0, 0x84(r31)
	bl TEXGet
	lwz r0, 0x4(r3)
	cmplwi r0, 0x0
	beq @33
	lwz r3, env_tpl(r13)
	li r4, 0x2
	bl TEXGet
	mr r25, r3
	lwz r4, 0x0(r3)
	lbz r3, 0x21(r4)
	lbz r0, 0x22(r4)
	cmplw r3, r0
	bne @34
	li r31, 0x0
	b @35
	@34:
	li r31, 0x1
	@35:
	lwz r6, 0x4(r25)
	addi r3, r1, 0x44
	lwz r4, 0x8(r6)
	lwz r5, 0x4(r6)
	lhz r6, 0x0(r6)
	bl GXInitTlutObj
	lwz r7, 0x0(r25)
	li r0, 0x0
	mr r10, r31
	addi r3, r1, 0x100
	stw r0, 0x8(r1)
	li r8, 0x0
	li r9, 0x0
	lwz r4, 0x8(r7)
	lhz r5, 0x2(r7)
	lhz r6, 0x0(r7)
	lwz r7, 0x4(r7)
	bl GXInitTexObjCI
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0x100
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	addi r3, r1, 0x44
	li r4, 0x0
	bl GXLoadTlut
	mr r4, r29
	addi r3, r1, 0x100
	bl GXLoadTexObj
	b @36
	@33:
	lwz r3, env_tpl(r13)
	li r4, 0x2
	bl TEXGet
	mr r25, r3
	lwz r7, 0x0(r3)
	lbz r3, 0x21(r7)
	lbz r0, 0x22(r7)
	cmplw r3, r0
	bne @37
	li r10, 0x0
	b @38
	@37:
	li r10, 0x1
	@38:
	lwz r4, 0x8(r7)
	addi r3, r1, 0x100
	lhz r5, 0x2(r7)
	li r8, 0x0
	lhz r6, 0x0(r7)
	li r9, 0x0
	lwz r7, 0x4(r7)
	bl GXInitTexObj
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0x100
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	mr r4, r29
	addi r3, r1, 0x100
	bl GXLoadTexObj
	@36:
	lis r3, dat_802f9338@ha
	slwi r31, r29, 2
	addi r25, r3, dat_802f9338@l
	mr r3, r28
	lwzx r6, r25, r31
	li r4, 0x1
	li r5, 0x1
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwzx r4, r25, r31
	li r3, 0x3
	li r5, 0x40
	li r6, 0x1
	bl envTevLoadTexMtxImm
	addi r30, r30, 0x1
	addi r29, r29, 0x1
	addi r28, r28, 0x1
	b @3
	@39:
	mr r3, r30
	li r4, 0x0
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	mr r3, r30
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	lfs f0, float_0p15_8041e564(r2)
	li r4, 0x4
	lfs f1, float_0_8041e53c(r2)
	stfs f0, 0x7c(r31)
	lfs f0, float_90_8041e568(r2)
	stfs f1, 0x80(r31)
	lwz r3, env_tpl(r13)
	stfs f0, 0x84(r31)
	bl TEXGet
	lwz r0, 0x4(r3)
	cmplwi r0, 0x0
	beq @40
	lwz r3, env_tpl(r13)
	li r4, 0x4
	bl TEXGet
	mr r25, r3
	lwz r4, 0x0(r3)
	lbz r3, 0x21(r4)
	lbz r0, 0x22(r4)
	cmplw r3, r0
	bne @41
	li r31, 0x0
	b @42
	@41:
	li r31, 0x1
	@42:
	lwz r6, 0x4(r25)
	addi r3, r1, 0x38
	lwz r4, 0x8(r6)
	lwz r5, 0x4(r6)
	lhz r6, 0x0(r6)
	bl GXInitTlutObj
	lwz r7, 0x0(r25)
	li r0, 0x0
	mr r10, r31
	addi r3, r1, 0xe0
	stw r0, 0x8(r1)
	li r8, 0x0
	li r9, 0x0
	lwz r4, 0x8(r7)
	lhz r5, 0x2(r7)
	lhz r6, 0x0(r7)
	lwz r7, 0x4(r7)
	bl GXInitTexObjCI
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0xe0
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	addi r3, r1, 0x38
	li r4, 0x0
	bl GXLoadTlut
	mr r4, r29
	addi r3, r1, 0xe0
	bl GXLoadTexObj
	b @43
	@40:
	lwz r3, env_tpl(r13)
	li r4, 0x4
	bl TEXGet
	mr r25, r3
	lwz r7, 0x0(r3)
	lbz r3, 0x21(r7)
	lbz r0, 0x22(r7)
	cmplw r3, r0
	bne @44
	li r10, 0x0
	b @45
	@44:
	li r10, 0x1
	@45:
	lwz r4, 0x8(r7)
	addi r3, r1, 0xe0
	lhz r5, 0x2(r7)
	li r8, 0x0
	lhz r6, 0x0(r7)
	li r9, 0x0
	lwz r7, 0x4(r7)
	bl GXInitTexObj
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0xe0
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	mr r4, r29
	addi r3, r1, 0xe0
	bl GXLoadTexObj
	@43:
	lis r3, dat_802f9338@ha
	slwi r31, r29, 2
	addi r25, r3, dat_802f9338@l
	mr r3, r28
	lwzx r6, r25, r31
	li r4, 0x1
	li r5, 0x1
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwzx r4, r25, r31
	li r3, 0x2
	li r5, 0x40
	li r6, 0x1
	bl envTevLoadTexMtxImm
	addi r30, r30, 0x1
	addi r29, r29, 0x1
	addi r28, r28, 0x1
	b @3
	@46:
	mr r3, r30
	li r4, 0x0
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	mr r3, r30
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	lfs f0, float_0p3_8041e56c(r2)
	li r4, 0x5
	lfs f1, float_0_8041e53c(r2)
	stfs f0, 0x7c(r31)
	lfs f0, float_90_8041e568(r2)
	stfs f1, 0x80(r31)
	lwz r3, env_tpl(r13)
	stfs f0, 0x84(r31)
	bl TEXGet
	lwz r0, 0x4(r3)
	cmplwi r0, 0x0
	beq @47
	lwz r3, env_tpl(r13)
	li r4, 0x5
	bl TEXGet
	mr r25, r3
	lwz r4, 0x0(r3)
	lbz r3, 0x21(r4)
	lbz r0, 0x22(r4)
	cmplw r3, r0
	bne @48
	li r31, 0x0
	b @49
	@48:
	li r31, 0x1
	@49:
	lwz r6, 0x4(r25)
	addi r3, r1, 0x2c
	lwz r4, 0x8(r6)
	lwz r5, 0x4(r6)
	lhz r6, 0x0(r6)
	bl GXInitTlutObj
	lwz r7, 0x0(r25)
	li r0, 0x0
	mr r10, r31
	addi r3, r1, 0xc0
	stw r0, 0x8(r1)
	li r8, 0x0
	li r9, 0x0
	lwz r4, 0x8(r7)
	lhz r5, 0x2(r7)
	lhz r6, 0x0(r7)
	lwz r7, 0x4(r7)
	bl GXInitTexObjCI
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0xc0
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	addi r3, r1, 0x2c
	li r4, 0x0
	bl GXLoadTlut
	mr r4, r29
	addi r3, r1, 0xc0
	bl GXLoadTexObj
	b @50
	@47:
	lwz r3, env_tpl(r13)
	li r4, 0x5
	bl TEXGet
	mr r25, r3
	lwz r7, 0x0(r3)
	lbz r3, 0x21(r7)
	lbz r0, 0x22(r7)
	cmplw r3, r0
	bne @51
	li r10, 0x0
	b @52
	@51:
	li r10, 0x1
	@52:
	lwz r4, 0x8(r7)
	addi r3, r1, 0xc0
	lhz r5, 0x2(r7)
	li r8, 0x0
	lhz r6, 0x0(r7)
	li r9, 0x0
	lwz r7, 0x4(r7)
	bl GXInitTexObj
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0xc0
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	mr r4, r29
	addi r3, r1, 0xc0
	bl GXLoadTexObj
	@50:
	lis r3, dat_802f9338@ha
	slwi r31, r29, 2
	addi r25, r3, dat_802f9338@l
	mr r3, r28
	lwzx r6, r25, r31
	li r4, 0x1
	li r5, 0x1
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwzx r4, r25, r31
	li r3, 0x3
	li r5, 0x40
	li r6, 0x1
	bl envTevLoadTexMtxImm
	addi r30, r30, 0x1
	addi r29, r29, 0x1
	addi r28, r28, 0x1
	b @3
	@53:
	mr r3, r30
	li r4, 0xf
	li r5, 0x0
	li r6, 0x8
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r30
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	lfs f0, float_0p5_8041e538(r2)
	li r4, 0xa
	lfs f1, float_10_8041e524(r2)
	stfs f0, 0x7c(r31)
	lfs f0, float_45_8041e560(r2)
	stfs f1, 0x80(r31)
	lwz r3, env_tpl(r13)
	stfs f0, 0x84(r31)
	bl TEXGet
	lwz r0, 0x4(r3)
	cmplwi r0, 0x0
	beq @54
	lwz r3, env_tpl(r13)
	li r4, 0xa
	bl TEXGet
	mr r25, r3
	lwz r4, 0x0(r3)
	lbz r3, 0x21(r4)
	lbz r0, 0x22(r4)
	cmplw r3, r0
	bne @55
	li r31, 0x0
	b @56
	@55:
	li r31, 0x1
	@56:
	lwz r6, 0x4(r25)
	addi r3, r1, 0x20
	lwz r4, 0x8(r6)
	lwz r5, 0x4(r6)
	lhz r6, 0x0(r6)
	bl GXInitTlutObj
	lwz r7, 0x0(r25)
	li r0, 0x0
	mr r10, r31
	addi r3, r1, 0xa0
	stw r0, 0x8(r1)
	li r8, 0x0
	li r9, 0x0
	lwz r4, 0x8(r7)
	lhz r5, 0x2(r7)
	lhz r6, 0x0(r7)
	lwz r7, 0x4(r7)
	bl GXInitTexObjCI
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0xa0
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	addi r3, r1, 0x20
	li r4, 0x0
	bl GXLoadTlut
	mr r4, r29
	addi r3, r1, 0xa0
	bl GXLoadTexObj
	b @57
	@54:
	lwz r3, env_tpl(r13)
	li r4, 0xa
	bl TEXGet
	mr r25, r3
	lwz r7, 0x0(r3)
	lbz r3, 0x21(r7)
	lbz r0, 0x22(r7)
	cmplw r3, r0
	bne @58
	li r10, 0x0
	b @59
	@58:
	li r10, 0x1
	@59:
	lwz r4, 0x8(r7)
	addi r3, r1, 0xa0
	lhz r5, 0x2(r7)
	li r8, 0x0
	lhz r6, 0x0(r7)
	li r9, 0x0
	lwz r7, 0x4(r7)
	bl GXInitTexObj
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0xa0
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	mr r4, r29
	addi r3, r1, 0xa0
	bl GXLoadTexObj
	@57:
	lis r3, dat_802f9338@ha
	slwi r31, r29, 2
	addi r25, r3, dat_802f9338@l
	mr r3, r28
	lwzx r6, r25, r31
	li r4, 0x1
	li r5, 0x1
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwzx r4, r25, r31
	li r3, 0x0
	li r5, 0x40
	li r6, 0x1
	bl envTevLoadTexMtxImm
	addi r30, r30, 0x1
	addi r29, r29, 0x1
	addi r28, r28, 0x1
	b @3
	@60:
	mr r3, r30
	li r4, 0x0
	li r5, 0x8
	li r6, 0xe
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r30
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	mr r3, r30
	li r4, 0xd
	bl GXSetTevKColorSel
	lwz r0, dat_8041e51c(r2)
	addi r4, r1, 0x10
	li r3, 0x1
	stw r0, 0x10(r1)
	bl GXSetTevKColor
	lwz r3, env_tpl(r13)
	li r4, 0x9
	bl TEXGet
	lwz r0, 0x4(r3)
	cmplwi r0, 0x0
	beq @61
	lwz r3, env_tpl(r13)
	li r4, 0x9
	bl TEXGet
	mr r25, r3
	lwz r4, 0x0(r3)
	lbz r3, 0x21(r4)
	lbz r0, 0x22(r4)
	cmplw r3, r0
	bne @62
	li r31, 0x0
	b @63
	@62:
	li r31, 0x1
	@63:
	lwz r6, 0x4(r25)
	addi r3, r1, 0x14
	lwz r4, 0x8(r6)
	lwz r5, 0x4(r6)
	lhz r6, 0x0(r6)
	bl GXInitTlutObj
	lwz r7, 0x0(r25)
	li r0, 0x0
	mr r10, r31
	addi r3, r1, 0x80
	stw r0, 0x8(r1)
	li r8, 0x0
	li r9, 0x0
	lwz r4, 0x8(r7)
	lhz r5, 0x2(r7)
	lhz r6, 0x0(r7)
	lwz r7, 0x4(r7)
	bl GXInitTexObjCI
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0x80
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	addi r3, r1, 0x14
	li r4, 0x0
	bl GXLoadTlut
	mr r4, r29
	addi r3, r1, 0x80
	bl GXLoadTexObj
	b @64
	@61:
	lwz r3, env_tpl(r13)
	li r4, 0x9
	bl TEXGet
	mr r25, r3
	lwz r7, 0x0(r3)
	lbz r3, 0x21(r7)
	lbz r0, 0x22(r7)
	cmplw r3, r0
	bne @65
	li r10, 0x0
	b @66
	@65:
	li r10, 0x1
	@66:
	lwz r4, 0x8(r7)
	addi r3, r1, 0x80
	lhz r5, 0x2(r7)
	li r8, 0x0
	lhz r6, 0x0(r7)
	li r9, 0x0
	lwz r7, 0x4(r7)
	bl GXInitTexObj
	lwz r7, 0x0(r25)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802f93a8@ha
	stw r5, 0x1d8(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802f93a8@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0x80
	stw r6, 0x1dc(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x1d8(r1)
	stw r0, 0x1d4(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x1d0(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x1d0(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	mr r4, r29
	addi r3, r1, 0x80
	bl GXLoadTexObj
	@64:
	lis r3, dat_802f9338@ha
	slwi r25, r29, 2
	addi r31, r3, dat_802f9338@l
	mr r3, r28
	lwzx r6, r31, r25
	li r4, 0x0
	li r5, 0x1
	li r7, 0x0
	li r8, 0x40
	bl GXSetTexCoordGen2
	lwzx r4, r31, r25
	li r3, 0x4
	li r5, 0x40
	li r6, 0x0
	bl envTevLoadTexMtxImm
	addi r30, r30, 0x1
	addi r29, r29, 0x1
	addi r28, r28, 0x1
	@3:
	stw r30, 0xc(r26)
	stw r28, 0x14(r26)
	stw r27, 0x18(r26)
	stw r29, 0x10(r26)
	@2:
	lmw r25, 0x1e4(r1)
	lwz r0, 0x204(r1)
	mtlr r0
	addi r1, r1, 0x200
	blr
}

asm void envTevLoadTexMtxImm(s32 type, GXTexMtx id, GXTexMtx id2, GXTexMtxType mtxType) {
	nofralloc
	stwu r1, -0x340(r1)
	mflr r0
	stw r0, 0x344(r1)
	stfd f31, 0x330(r1)
	psq_st f31, 0x338(r1), 0, 0
	stfd f30, 0x320(r1)
	psq_st f30, 0x328(r1), 0, 0
	stfd f29, 0x310(r1)
	psq_st f29, 0x318(r1), 0, 0
	stmw r27, 0x2fc(r1)
	lwz r8, gp(r13)
	lis r7, work@ha
	addi r31, r7, work@l
	mr r27, r4
	lwz r0, 0x14(r8)
	lis r7, dat_802f9338@ha
	mr r28, r5
	mr r29, r6
	cmpwi r0, 0x0
	addi r30, r7, dat_802f9338@l
	beq @1
	addi r31, r31, 0xf0
	@1:
	cmpwi r3, 0x3
	beq @2
	bge @3
	cmpwi r3, 0x1
	beq @4
	bge @5
	cmpwi r3, 0x0
	bge @6
	b @7
	@3:
	cmpwi r3, 0x5
	beq @8
	bge @7
	b @9
	@6:
	lfs f1, float_deg2rad_8041e570(r2)
	addi r3, r1, 0x2c0
	lfs f0, 0x80(r31)
	li r4, 0x59
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lfs f0, 0x84(r31)
	addi r3, r1, 0x260
	lfs f1, float_deg2rad_8041e570(r2)
	li r4, 0x5a
	fneg f0, f0
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r3, r1, 0x2c0
	addi r4, r1, 0x260
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x2c0
	mr r4, r3
	bl PSMTXInvXpose
	addi r3, r1, 0x2c0
	mr r4, r3
	bl PSVECNormalize
	addi r3, r1, 0x2d0
	mr r4, r3
	bl PSVECNormalize
	addi r3, r1, 0x2e0
	mr r4, r3
	bl PSVECNormalize
	lfs f1, float_0p5_8041e538(r2)
	addi r3, r1, 0x290
	lfs f3, float_1_8041e574(r2)
	fmr f2, f1
	bl PSMTXScale
	addi r4, r1, 0x2c0
	addi r3, r1, 0x290
	mr r5, r4
	bl PSMTXConcat
	lfs f1, float_0p5_8041e538(r2)
	addi r3, r1, 0x290
	lfs f3, float_0_8041e53c(r2)
	fmr f2, f1
	bl PSMTXTrans
	addi r4, r1, 0x2c0
	addi r3, r1, 0x290
	mr r5, r4
	bl PSMTXConcat
	mr r4, r27
	mr r5, r29
	addi r3, r1, 0x2c0
	bl GXLoadTexMtxImm
	b @7
	@4:
	lfs f1, float_neg1p5708_8041e578(r2)
	addi r3, r1, 0x2c0
	li r4, 0x59
	bl PSMTXRotRad
	addi r3, r1, 0x2c0
	lwz r4, 0x78(r31)
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x2c0
	mr r4, r3
	bl PSMTXInvXpose
	addi r3, r1, 0x2c0
	mr r4, r3
	bl PSVECNormalize
	addi r3, r1, 0x2d0
	mr r4, r3
	bl PSVECNormalize
	addi r3, r1, 0x2e0
	mr r4, r3
	bl PSVECNormalize
	lfs f2, float_0p5_8041e538(r2)
	addi r3, r1, 0x230
	lfs f1, float_0p25_8041e57c(r2)
	lfs f0, 0x7c(r31)
	lfs f3, float_1_8041e574(r2)
	fnmsubs f1, f1, f0, f2
	bl PSMTXScale
	addi r4, r1, 0x2c0
	addi r3, r1, 0x230
	mr r5, r4
	bl PSMTXConcat
	lfs f1, float_0p5_8041e538(r2)
	addi r3, r1, 0x230
	lfs f3, float_0_8041e53c(r2)
	fmr f2, f1
	bl PSMTXTrans
	addi r4, r1, 0x2c0
	addi r3, r1, 0x230
	mr r5, r4
	bl PSMTXConcat
	mr r4, r27
	mr r5, r29
	addi r3, r1, 0x2c0
	bl GXLoadTexMtxImm
	b @7
	@5:
	lfs f3, float_3p1416_8041e580(r2)
	lfs f1, 0x80(r31)
	lfs f0, 0x84(r31)
	fmuls f2, f3, f1
	lfs f1, float_180_8041e584(r2)
	fmuls f0, f3, f0
	lwz r4, 0x28(r30)
	lwz r3, 0x2c(r30)
	fdivs f30, f2, f1
	lwz r0, 0x30(r30)
	stw r4, 0x94(r1)
	stw r3, 0x98(r1)
	stw r0, 0x9c(r1)
	fdivs f29, f0, f1
	fmr f1, f30
	bl sin
	frsp f31, f1
	fmr f1, f29
	bl cos
	frsp f0, f1
	fmr f1, f29
	fneg f0, f0
	fmuls f0, f0, f31
	stfs f0, 0x88(r1)
	bl sin
	frsp f0, f1
	fmr f1, f30
	fneg f0, f0
	stfs f0, 0x8c(r1)
	bl cos
	frsp f31, f1
	fmr f1, f29
	bl cos
	frsp f0, f1
	addi r4, r1, 0x88
	lwz r3, 0x70(r31)
	mr r5, r4
	fneg f0, f0
	fmuls f0, f0, f31
	stfs f0, 0x90(r1)
	bl PSMTXMultVecSR
	addi r3, r1, 0x88
	addi r4, r1, 0x94
	addi r5, r1, 0x7c
	bl C_VECHalfAngle
	lwz r3, 0x78(r31)
	addi r4, r1, 0x2c0
	bl PSMTXInvXpose
	addi r3, r1, 0x2c0
	mr r4, r3
	bl PSVECNormalize
	addi r3, r1, 0x2d0
	mr r4, r3
	bl PSVECNormalize
	addi r3, r1, 0x2e0
	mr r4, r3
	bl PSVECNormalize
	addi r3, r1, 0x200
	bl PSMTXIdentity
	lfs f2, 0x7c(r1)
	addi r4, r1, 0x2c0
	lfs f1, 0x80(r1)
	mr r5, r4
	lfs f0, 0x84(r1)
	addi r3, r1, 0x200
	stfs f2, 0x200(r1)
	stfs f1, 0x204(r1)
	stfs f0, 0x208(r1)
	bl PSMTXConcat
	lfs f1, float_20_8041e588(r2)
	addi r3, r1, 0x200
	lfs f0, 0x7c(r31)
	lfs f2, float_1_8041e574(r2)
	fmuls f29, f1, f0
	fmr f3, f2
	fmr f1, f29
	bl PSMTXScale
	addi r4, r1, 0x2c0
	addi r3, r1, 0x200
	mr r5, r4
	bl PSMTXConcat
	lfs f0, float_1_8041e574(r2)
	addi r3, r1, 0x200
	lfs f2, float_0_8041e53c(r2)
	fsubs f1, f0, f29
	fmr f3, f2
	bl PSMTXTrans
	addi r4, r1, 0x2c0
	addi r3, r1, 0x200
	mr r5, r4
	bl PSMTXConcat
	mr r4, r27
	mr r5, r29
	addi r3, r1, 0x2c0
	bl GXLoadTexMtxImm
	b @7
	@2:
	lfs f3, float_3p1416_8041e580(r2)
	lfs f1, 0x80(r31)
	lfs f0, 0x84(r31)
	fmuls f2, f3, f1
	lfs f1, float_180_8041e584(r2)
	fmuls f0, f3, f0
	lwz r4, 0x34(r30)
	lwz r3, 0x38(r30)
	fdivs f29, f2, f1
	lwz r0, 0x3c(r30)
	stw r4, 0x4c(r1)
	stw r3, 0x50(r1)
	stw r0, 0x54(r1)
	fdivs f30, f0, f1
	fmr f1, f29
	bl sin
	frsp f31, f1
	fmr f1, f30
	bl cos
	frsp f0, f1
	fmr f1, f30
	fmuls f0, f0, f31
	stfs f0, 0x70(r1)
	bl sin
	frsp f0, f1
	fmr f1, f29
	stfs f0, 0x74(r1)
	bl cos
	frsp f31, f1
	fmr f1, f30
	bl cos
	frsp f0, f1
	addi r4, r1, 0x70
	lwz r3, 0x70(r31)
	mr r5, r4
	fmuls f0, f0, f31
	stfs f0, 0x78(r1)
	bl PSMTXMultVecSR
	addi r3, r1, 0x70
	addi r4, r1, 0x4c
	bl PSVECDotProduct
	fmr f31, f1
	lfs f0, float_neg1_8041e58c(r2)
	fcmpu cr0, f0, f31
	bne @10
	lfs f1, float_0_8041e53c(r2)
	addi r3, r1, 0x2c0
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	mr r4, r27
	addi r3, r1, 0x2c0
	li r5, 0x1
	bl GXLoadTexMtxImm
	b @7
	@10:
	addi r3, r1, 0x70
	addi r4, r1, 0x4c
	addi r5, r1, 0x64
	bl C_VECHalfAngle
	lfs f2, 0x64(r1)
	addi r4, r1, 0x1d0
	lfs f1, 0x68(r1)
	lfs f0, 0x6c(r1)
	fneg f2, f2
	fneg f1, f1
	lwz r3, 0x78(r31)
	fneg f0, f0
	stfs f2, 0x64(r1)
	stfs f1, 0x68(r1)
	stfs f0, 0x6c(r1)
	bl PSMTXInvXpose
	addi r3, r1, 0x1d0
	mr r4, r3
	bl PSVECNormalize
	addi r3, r1, 0x1e0
	mr r4, r3
	bl PSVECNormalize
	addi r3, r1, 0x1f0
	mr r4, r3
	bl PSVECNormalize
	lfs f0, float_1_8041e574(r2)
	fcmpu cr0, f0, f31
	bne @11
	addi r3, r1, 0x1a0
	bl PSMTXIdentity
	b @12
	@11:
	addi r3, r1, 0x64
	addi r4, r1, 0x4c
	addi r5, r1, 0x58
	bl PSVECCrossProduct
	addi r3, r1, 0x4c
	addi r4, r1, 0x64
	bl PSVECDotProduct
	bl acos
	frsp f1, f1
	addi r3, r1, 0x1a0
	addi r4, r1, 0x58
	bl PSMTXRotAxisRad
	@12:
	addi r3, r1, 0x1a0
	addi r4, r1, 0x1d0
	addi r5, r1, 0x2c0
	bl PSMTXConcat
	lfs f1, float_2_8041e590(r2)
	addi r3, r1, 0x1a0
	lfs f0, 0x7c(r31)
	lfs f3, float_1_8041e574(r2)
	fmuls f1, f1, f0
	fmr f2, f1
	bl PSMTXScale
	addi r4, r1, 0x2c0
	addi r3, r1, 0x1a0
	mr r5, r4
	bl PSMTXConcat
	lfs f1, float_0p5_8041e538(r2)
	addi r3, r1, 0x1a0
	lfs f3, float_0_8041e53c(r2)
	fmr f2, f1
	bl PSMTXTrans
	addi r4, r1, 0x2c0
	addi r3, r1, 0x1a0
	mr r5, r4
	bl PSMTXConcat
	mr r4, r27
	mr r5, r29
	addi r3, r1, 0x2c0
	bl GXLoadTexMtxImm
	b @7
	@9:
	lwz r3, 0x78(r31)
	addi r4, r1, 0x2c0
	bl PSMTXInvXpose
	addi r3, r1, 0x2c0
	mr r4, r3
	bl PSVECNormalize
	addi r3, r1, 0x2d0
	mr r4, r3
	bl PSVECNormalize
	addi r3, r1, 0x2e0
	mr r4, r3
	bl PSVECNormalize
	mr r4, r27
	addi r3, r1, 0x2c0
	li r5, 0x1
	bl GXLoadTexMtxImm
	lfs f1, float_0p5_8041e538(r2)
	addi r3, r1, 0x170
	lfs f3, float_0_8041e53c(r2)
	fmr f2, f1
	bl PSMTXScale
	lfs f1, float_0p5_8041e538(r2)
	addi r3, r1, 0x2c0
	lfs f3, float_1_8041e574(r2)
	fmr f2, f1
	bl PSMTXTrans
	addi r3, r1, 0x2c0
	addi r4, r1, 0x170
	mr r5, r3
	bl PSMTXConcat
	mr r4, r28
	mr r5, r29
	addi r3, r1, 0x2c0
	bl GXLoadTexMtxImm
	b @7
	@8:
	lfs f1, g5_a_s655(r13)
	lfs f0, float_0p0001_8041e594(r2)
	lwz r4, 0x40(r30)
	fadds f1, f1, f0
	lwz r3, 0x44(r30)
	lwz r0, 0x48(r30)
	stw r4, 0x1c(r1)
	stfs f1, g5_a_s655(r13)
	stw r3, 0x20(r1)
	stw r0, 0x24(r1)
	bl sin
	frsp f2, f1
	lfs f0, float_10_8041e524(r2)
	lfs f1, g5_a_s655(r13)
	fmuls f0, f0, f2
	stfs f0, 0x1c(r1)
	bl cos
	frsp f1, f1
	lfs f0, float_10_8041e524(r2)
	lwz r7, 0x1c(r1)
	lwz r6, 0x20(r1)
	fmuls f0, f0, f1
	lwz r4, 0x4c(r30)
	lwz r3, 0x50(r30)
	lwz r0, 0x54(r30)
	stfs f0, 0x24(r1)
	lfs f1, g5_a_s655(r13)
	lwz r5, 0x24(r1)
	stw r7, 0x40(r1)
	stw r6, 0x44(r1)
	stw r5, 0x48(r1)
	stw r4, 0x10(r1)
	stw r3, 0x14(r1)
	stw r0, 0x18(r1)
	bl sin
	frsp f2, f1
	lfs f0, float_10_8041e524(r2)
	lfs f1, g5_a_s655(r13)
	fmuls f0, f0, f2
	stfs f0, 0x10(r1)
	bl cos
	frsp f1, f1
	lfs f0, float_10_8041e524(r2)
	lwz r11, 0x10(r1)
	addi r3, r1, 0xa0
	lwz r10, 0x14(r1)
	addi r4, r1, 0x40
	fmuls f0, f0, f1
	lwz r8, 0x58(r30)
	lwz r7, 0x5c(r30)
	addi r5, r1, 0x28
	lwz r0, 0x60(r30)
	addi r6, r1, 0x34
	stfs f0, 0x18(r1)
	lwz r9, 0x18(r1)
	stw r11, 0x34(r1)
	stw r10, 0x38(r1)
	stw r9, 0x3c(r1)
	stw r8, 0x28(r1)
	stw r7, 0x2c(r1)
	stw r0, 0x30(r1)
	bl C_MTXLookAt
	lfs f6, float_0p5_8041e538(r2)
	addi r3, r1, 0x130
	lfs f1, float_neg32_8041e598(r2)
	lfs f2, float_32_8041e59c(r2)
	fmr f7, f6
	fmr f3, f1
	stfs f6, 0x8(r1)
	fmr f4, f2
	lfs f5, float_300_8041e5a0(r2)
	fmr f8, f6
	bl C_MTXLightFrustum
	lwz r3, 0x70(r31)
	addi r4, r1, 0x100
	bl PSMTXInverse
	addi r3, r1, 0xa0
	addi r4, r1, 0x100
	addi r5, r1, 0xd0
	bl PSMTXConcat
	addi r3, r1, 0x130
	addi r4, r1, 0xd0
	addi r5, r1, 0x2c0
	bl PSMTXConcat
	mr r4, r28
	mr r5, r29
	addi r3, r1, 0x2c0
	bl GXLoadTexMtxImm
	@7:
	psq_l f31, 0x338(r1), 0, 0
	lfd f31, 0x330(r1)
	psq_l f30, 0x328(r1), 0, 0
	lfd f30, 0x320(r1)
	psq_l f29, 0x318(r1), 0, 0
	lfd f29, 0x310(r1)
	lmw r27, 0x2fc(r1)
	lwz r0, 0x344(r1)
	mtlr r0
	addi r1, r1, 0x340
	blr
}

asm void envDisp_FF(void) {
	nofralloc
	stwu r1, -0xf0(r1)
	mflr r0
	stw r0, 0xf4(r1)
	stfd f31, 0xe0(r1)
	psq_st f31, 0xe8(r1), 0, 0
	stfd f30, 0xd0(r1)
	psq_st f30, 0xd8(r1), 0, 0
	stfd f29, 0xc0(r1)
	psq_st f29, 0xc8(r1), 0, 0
	stfd f28, 0xb0(r1)
	psq_st f28, 0xb8(r1), 0, 0
	stfd f27, 0xa0(r1)
	psq_st f27, 0xa8(r1), 0, 0
	stfd f26, 0x90(r1)
	psq_st f26, 0x98(r1), 0, 0
	stfd f25, 0x80(r1)
	psq_st f25, 0x88(r1), 0, 0
	stfd f24, 0x70(r1)
	psq_st f24, 0x78(r1), 0, 0
	stfd f23, 0x60(r1)
	psq_st f23, 0x68(r1), 0, 0
	stfd f22, 0x50(r1)
	psq_st f22, 0x58(r1), 0, 0
	stfd f21, 0x40(r1)
	psq_st f21, 0x48(r1), 0, 0
	stfd f20, 0x30(r1)
	psq_st f20, 0x38(r1), 0, 0
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	stw r29, 0x24(r1)
	stw r28, 0x20(r1)
	lwz r4, gp(r13)
	lis r3, work@ha
	addi r29, r3, work@l
	lwz r0, 0x14(r4)
	lis r3, dat_802f9338@ha
	addi r31, r3, dat_802f9338@l
	cmpwi r0, 0x0
	beq @1
	addi r29, r29, 0xf0
	@1:
	lwz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 3, 3
	beq @2
	li r3, 0x0
	bl GXSetNumChans
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x1
	bl GXSetNumTexGens
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x3c
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x3
	bl GXSetTevOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	addi r3, r29, 0xc
	li r4, 0x0
	bl GXLoadTexObj
	li r3, 0x1
	li r4, 0x4
	li r5, 0x5
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x1
	bl GXSetZCompLoc
	li r3, 0x7
	li r4, 0x0
	li r5, 0x0
	li r6, 0x7
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x0
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	li r3, 0x10
	li r4, 0x0
	bl GXSetLineWidth
	li r3, 0x8
	bl camGetPtr
	li r4, 0x0
	addi r3, r3, 0x11c
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xd
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	lwz r3, gp(r13)
	lis r0, 0x4330
	stw r0, 0x10(r1)
	lhz r4, 0x170(r3)
	lhz r3, 0x172(r3)
	extrwi r0, r4, 15, 16
	lfd f2, 0x68(r31)
	mullw r4, r0, r4
	extrwi r0, r3, 15, 16
	lfs f0, float_0_8041e53c(r2)
	mullw r3, r0, r3
	srwi r0, r4, 31
	add r4, r0, r4
	srwi r0, r3, 31
	srawi r4, r4, 1
	add r0, r0, r3
	srawi r0, r0, 1
	add r0, r4, r0
	xoris r0, r0, 0x8000
	stw r0, 0x14(r1)
	lfd f1, 0x10(r1)
	fsubs f25, f1, f2
	fcmpo cr0, f25, f0
	ble @3
	frsqrte f1, f25
	lfd f3, 0x78(r31)
	lfd f2, 0x80(r31)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f25, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f25, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f25, f0, f2
	fmul f0, f1, f0
	fmul f25, f25, f0
	frsp f25, f25
	b @4
	@3:
	lfd f0, 0x88(r31)
	fcmpo cr0, f25, f0
	bge @5
	lis r3, __float_nan@ha
	lfs f25, __float_nan@l(r3)
	b @4
	@5:
	stfs f25, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @6
	bge @7
	cmpwi r3, 0x0
	beq @8
	b @7
	@6:
	clrlwi. r0, r4, 9
	beq @9
	li r0, 0x1
	b @10
	@9:
	li r0, 0x2
	b @10
	@8:
	clrlwi. r0, r4, 9
	beq @11
	li r0, 0x5
	b @10
	@11:
	li r0, 0x3
	b @10
	@7:
	li r0, 0x4
	@10:
	cmpwi r0, 0x1
	bne @4
	lis r3, __float_nan@ha
	lfs f25, __float_nan@l(r3)
	@4:
	li r3, 0xa8
	li r4, 0x0
	li r5, 0x7d0
	bl GXBegin
	lis r3, 0x6666
	lfs f26, float_6p2832_8041e558(r2)
	lfd f27, 0x68(r31)
	addi r30, r3, 0x6667
	lfs f28, float_1000_8041e540(r2)
	li r28, 0x0
	lfs f23, float_0p4967_8041e5a8(r2)
	lis r29, 0x4330
	lfs f24, float_1_8041e574(r2)
	lis r31, 0xcc01
	lfs f29, float_3p1416_8041e580(r2)
	lfs f21, float_0p16605_8041e5b8(r2)
	lfs f30, float_100_8041e5bc(r2)
	lfs f31, float_0p5_8041e538(r2)
	@12:
	xoris r0, r28, 0x8000
	stw r29, 0x10(r1)
	lfs f22, float_0p03705_8041e5a4(r2)
	stw r0, 0x14(r1)
	lfd f0, 0x10(r1)
	fsubs f0, f0, f27
	fmuls f0, f26, f0
	fdivs f2, f0, f28
	fcmpo cr0, f2, f29
	cror eq, lt, eq
	bne @13
	lfs f1, float_1p5708_8041e5ac(r2)
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @14
	fmuls f0, f2, f2
	fmsubs f22, f22, f0, f23
	fmadds f22, f22, f0, f24
	b @15
	@14:
	fsubs f0, f2, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f22, f22, f0, f23
	fmadds f22, f22, f0, f24
	fneg f22, f22
	b @15
	@13:
	lfs f0, float_4p7124_8041e5b0(r2)
	fcmpo cr0, f2, f0
	bge @16
	fsubs f0, f2, f29
	fmuls f0, f0, f0
	fmsubs f22, f22, f0, f23
	fmadds f22, f22, f0, f24
	fneg f22, f22
	b @15
	@16:
	fsubs f0, f2, f0
	lfs f1, float_1p5708_8041e5ac(r2)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f22, f22, f0, f23
	fmadds f22, f22, f0, f24
	@15:
	fcmpo cr0, f2, f29
	lfs f20, float_0p00761_8041e5b4(r2)
	cror eq, lt, eq
	bne @17
	lfs f1, float_1p5708_8041e5ac(r2)
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @18
	fmuls f0, f2, f2
	fmsubs f20, f20, f0, f21
	fmadds f20, f20, f0, f24
	fmuls f20, f20, f2
	b @19
	@18:
	fsubs f0, f2, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f20, f20, f0, f21
	fmadds f20, f20, f0, f24
	fmuls f20, f20, f1
	b @19
	@17:
	lfs f0, float_4p7124_8041e5b0(r2)
	fcmpo cr0, f2, f0
	bge @20
	fsubs f1, f2, f29
	fmuls f0, f1, f1
	fmsubs f20, f20, f0, f21
	fmadds f20, f20, f0, f24
	fmuls f20, f20, f1
	fneg f20, f20
	b @19
	@20:
	fsubs f0, f2, f0
	lfs f1, float_1p5708_8041e5ac(r2)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f20, f20, f0, f21
	fmadds f20, f20, f0, f24
	fmuls f20, f20, f1
	fneg f20, f20
	@19:
	bl rand
	mulhw r0, r30, r3
	fmuls f1, f20, f25
	fneg f0, f22
	addi r28, r28, 0x1
	fmuls f2, f22, f25
	stw r29, 0x10(r1)
	srawi r0, r0, 2
	stfs f1, -0x8000(r31)
	srwi r4, r0, 31
	fmadds f1, f20, f31, f31
	add r0, r0, r4
	stfs f2, -0x8000(r31)
	mulli r0, r0, 0xa
	lfs f2, float_0_8041e53c(r2)
	fmadds f0, f0, f31, f31
	stfs f2, -0x8000(r31)
	cmpwi r28, 0x3e8
	subf r0, r0, r3
	xoris r0, r0, 0x8000
	stw r0, 0x14(r1)
	lfd f2, 0x10(r1)
	fsubs f2, f2, f27
	fdivs f2, f2, f30
	fadds f1, f1, f2
	fadds f0, f0, f2
	stfs f1, -0x8000(r31)
	stfs f0, -0x8000(r31)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_0p5_8041e538(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_0p5_8041e538(r2)
	stfs f0, -0x8000(r31)
	blt @12
	@2:
	psq_l f31, 0xe8(r1), 0, 0
	lfd f31, 0xe0(r1)
	psq_l f30, 0xd8(r1), 0, 0
	lfd f30, 0xd0(r1)
	psq_l f29, 0xc8(r1), 0, 0
	lfd f29, 0xc0(r1)
	psq_l f28, 0xb8(r1), 0, 0
	lfd f28, 0xb0(r1)
	psq_l f27, 0xa8(r1), 0, 0
	lfd f27, 0xa0(r1)
	psq_l f26, 0x98(r1), 0, 0
	lfd f26, 0x90(r1)
	psq_l f25, 0x88(r1), 0, 0
	lfd f25, 0x80(r1)
	psq_l f24, 0x78(r1), 0, 0
	lfd f24, 0x70(r1)
	psq_l f23, 0x68(r1), 0, 0
	lfd f23, 0x60(r1)
	psq_l f22, 0x58(r1), 0, 0
	lfd f22, 0x50(r1)
	psq_l f21, 0x48(r1), 0, 0
	lfd f21, 0x40(r1)
	psq_l f20, 0x38(r1), 0, 0
	lfd f20, 0x30(r1)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	lwz r0, 0xf4(r1)
	lwz r28, 0x20(r1)
	mtlr r0
	addi r1, r1, 0xf0
	blr
}

asm void envGlareFilterZ(f32 zscale) {
	nofralloc
	lwz r4, gp(r13)
	lis r3, work@ha
	addi r3, r3, work@l
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @1
	addi r3, r3, 0xf0
	@1:
	addi r3, r3, 0xb0
	stfs f1, 0xc(r3)
	lhz r0, 0x0(r3)
	ori r0, r0, 0x1
	sth r0, 0x0(r3)
	blr
}

asm void envGlareFilter(s32 type, s32 y0, s32 x0, s32 y1, s32 x1) {
	nofralloc
	lwz r11, gp(r13)
	lis r8, work@ha
	addi r10, r8, work@l
	lwz r0, 0x14(r11)
	cmpwi r0, 0x0
	beq @1
	addi r10, r10, 0xf0
	@1:
	cmpwi r3, 0x0
	addi r12, r10, 0xb0
	bne @2
	li r0, 0x0
	sth r0, 0x2(r12)
	sth r0, 0xa(r12)
	sth r0, 0x6(r12)
	sth r0, 0x8(r12)
	sth r0, 0x4(r12)
	lwz r0, 0x0(r10)
	rlwinm r0, r0, 0, 3, 1
	stw r0, 0x0(r10)
	blr
	@2:
	clrlwi r0, r5, 31
	clrlwi r8, r4, 31
	subf r9, r0, r5
	clrlwi r5, r7, 31
	clrlwi r0, r6, 31
	subf r8, r8, r4
	add r4, r7, r5
	extsh. r7, r9
	add r0, r6, r0
	extsh r6, r8
	extsh r4, r4
	extsh r5, r0
	bge @3
	li r7, 0x0
	@3:
	extsh. r0, r6
	bge @4
	li r6, 0x0
	@4:
	lhz r0, 0x170(r11)
	cmpw r4, r0
	ble @5
	extsh r4, r0
	@5:
	lhz r0, 0x172(r11)
	cmpw r5, r0
	ble @6
	extsh r5, r0
	@6:
	sth r3, 0x2(r12)
	lfs f0, float_0_8041e53c(r2)
	sth r6, 0x4(r12)
	sth r7, 0x8(r12)
	sth r5, 0x6(r12)
	sth r4, 0xa(r12)
	stfs f0, 0xc(r12)
	lhz r0, 0x0(r12)
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r12)
	lwz r0, 0x0(r10)
	oris r0, r0, 0x2000
	stw r0, 0x0(r10)
	blr
}

asm void envGlare(EnvironmentGlare* glare) {
	nofralloc
	stwu r1, -0x130(r1)
	mflr r0
	stw r0, 0x134(r1)
	stfd f31, 0x120(r1)
	psq_st f31, 0x128(r1), 0, 0
	stmw r19, 0xec(r1)
	lwz r5, gp(r13)
	lis r4, work@ha
	addi r4, r4, work@l
	mr r24, r3
	lwz r0, 0x14(r5)
	cmpwi r0, 0x0
	beq @1
	addi r4, r4, 0xf0
	@1:
	lfs f1, g5_frame_cnt_s541(r13)
	addi r30, r4, 0xb0
	lfs f0, float_1_8041e574(r2)
	li r5, 0x4
	lhz r27, 0xb4(r4)
	li r6, 0x0
	fadds f0, f1, f0
	lhz r0, 0xb6(r4)
	lhz r26, 0xb8(r4)
	li r7, 0x0
	subf r0, r27, r0
	lhz r3, 0xba(r4)
	subf r8, r26, r3
	extrwi r20, r0, 15, 16
	extrwi r21, r8, 15, 16
	stfs f0, g5_frame_cnt_s541(r13)
	mr r3, r21
	mr r4, r20
	clrlwi r31, r8, 16
	clrlwi r25, r0, 16
	bl GXGetTexBufferSize
	li r4, 0x3
	bl smartAlloc
	lwz r19, 0x0(r3)
	mr r3, r26
	mr r4, r27
	mr r5, r31
	mr r6, r25
	bl GXSetTexCopySrc
	clrlwi r3, r21, 16
	clrlwi r4, r20, 16
	li r5, 0x4
	li r6, 0x1
	bl GXSetTexCopyDst
	mr r3, r19
	li r4, 0x0
	bl GXCopyTex
	bl GXPixModeSync
	mr r4, r19
	addi r3, r1, 0x8
	clrlwi r5, r21, 16
	clrlwi r6, r20, 16
	li r7, 0x4
	li r8, 0x0
	li r9, 0x0
	li r10, 0x0
	bl GXInitTexObj
	lfs f1, float_0_8041e53c(r2)
	addi r3, r1, 0x8
	li r4, 0x1
	li r5, 0x1
	fmr f2, f1
	li r6, 0x0
	fmr f3, f1
	li r7, 0x0
	li r8, 0x0
	bl GXInitTexObjLOD
	addi r3, r1, 0x8
	li r4, 0x0
	bl GXLoadTexObj
	lwz r29, 0x18(r24)
	li r28, 0x0
	lwz r20, 0xc(r24)
	li r3, 0x0
	lwz r21, 0x10(r24)
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x1
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x2
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0xe
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	mr r4, r20
	li r3, 0x0
	bl GXSetTevKColorSel
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x1
	li r4, 0xff
	li r5, 0xff
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x1
	li r4, 0xf
	li r5, 0x4
	li r6, 0xe
	li r7, 0xf
	bl GXSetTevColorIn
	mr r4, r21
	li r3, 0x1
	bl GXSetTevKColorSel
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r19, 0x0
	li r23, 0x2
	li r22, 0x3
	@2:
	mr r3, r23
	addi r4, r19, 0x1
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r23
	li r4, 0x1
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x2
	bl GXSetTevColorOp
	mr r3, r23
	li r4, 0xe
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	mr r3, r23
	mr r4, r20
	bl GXSetTevKColorSel
	mr r3, r23
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	mr r3, r22
	li r4, 0xff
	li r5, 0xff
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r22
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r22
	li r4, 0xf
	li r5, 0x4
	li r6, 0xe
	li r7, 0x0
	bl GXSetTevColorIn
	mr r3, r22
	mr r4, r21
	bl GXSetTevKColorSel
	mr r3, r22
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	addi r19, r19, 0x1
	addi r22, r22, 0x2
	cmpwi r19, 0x7
	addi r23, r23, 0x2
	blt @2
	li r19, 0x0
	li r22, 0x1e
	@3:
	mr r3, r19
	mr r6, r22
	li r4, 0x1
	li r5, 0x4
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	addi r19, r19, 0x1
	addi r22, r22, 0x3
	cmpwi r19, 0x8
	blt @3
	lhz r0, 0x0(r30)
	clrlwi. r0, r0, 31
	beq @4
	li r3, 0x1
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	b @5
	@4:
	li r3, 0x0
	li r4, 0x7
	li r5, 0x0
	bl GXSetZMode
	@5:
	lwz r3, 0x0(r24)
	li r6, 0x0
	lwz r4, 0x4(r24)
	lwz r5, 0x8(r24)
	bl GXSetBlendMode
	li r3, 0x0
	bl GXSetNumChans
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	lwz r6, gp(r13)
	lis r3, 0x4330
	lfs f1, float_0_8041e53c(r2)
	lis r4, double_to_int_mask_802f93a8@ha
	lhz r5, 0x170(r6)
	lhz r0, 0x172(r6)
	fmr f2, f1
	stw r5, 0xcc(r1)
	fmr f5, f1
	lfd f4, double_to_int_mask_802f93a8@l(r4)
	stw r3, 0xc8(r1)
	lfs f6, float_1_8041e574(r2)
	lfd f0, 0xc8(r1)
	stw r0, 0xd4(r1)
	fsubs f3, f0, f4
	stw r3, 0xd0(r1)
	lfd f0, 0xd0(r1)
	fsubs f4, f0, f4
	bl GXSetViewport
	lwz r6, gp(r13)
	li r3, 0x0
	li r4, 0x0
	lhz r5, 0x170(r6)
	lhz r6, 0x172(r6)
	bl GXSetScissor
	lwz r6, gp(r13)
	lis r4, 0x4330
	lfs f1, float_0_8041e53c(r2)
	lis r3, double_to_int_mask_802f93a8@ha
	lhz r5, 0x172(r6)
	lhz r0, 0x170(r6)
	fmr f3, f1
	stw r5, 0xdc(r1)
	fmr f5, f1
	lfd f4, double_to_int_mask_802f93a8@l(r3)
	addi r3, r1, 0x88
	stw r4, 0xd8(r1)
	lfs f6, float_neg32767_8041e5c0(r2)
	lfd f0, 0xd8(r1)
	stw r0, 0xe4(r1)
	fsubs f2, f0, f4
	stw r4, 0xe0(r1)
	lfd f0, 0xe0(r1)
	fsubs f4, f0, f4
	bl C_MTXOrtho
	addi r3, r1, 0x88
	li r4, 0x1
	bl GXSetProjection
	addi r3, r1, 0x58
	bl PSMTXIdentity
	addi r3, r1, 0x58
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xd
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x7
	li r4, 0x9
	li r5, 0x1
	li r6, 0x3
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x7
	li r4, 0xd
	li r5, 0x1
	li r6, 0x2
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x2
	bl GXSetCullMode
	lfs f1, float_1_8041e574(r2)
	lfs f2, 0xc(r30)
	bl GXSetZScaleOffset
	lis r3, double_to_int_mask_802f93a8@ha
	add r30, r27, r25
	lfd f31, double_to_int_mask_802f93a8@l(r3)
	add r31, r26, r31
	extsh r20, r26
	mr r21, r24
	extsh r27, r27
	lis r26, 0x4330
	lis r25, 0xcc01
	b @6
	@7:
	mr r22, r21
	li r19, 0x0
	li r23, 0x1e
	b @8
	@9:
	lwz r5, gp(r13)
	addi r3, r1, 0x28
	stw r26, 0xe0(r1)
	lhz r4, 0x170(r5)
	lhz r0, 0x172(r5)
	stw r4, 0xe4(r1)
	lfs f3, 0x14(r24)
	lfs f2, 0x1c(r22)
	lfd f1, 0xe0(r1)
	lfs f0, 0x20(r22)
	fmuls f4, f3, f2
	fsubs f1, f1, f31
	stw r0, 0xdc(r1)
	fmuls f2, f3, f0
	lfs f3, float_0_8041e53c(r2)
	stw r26, 0xd8(r1)
	fdivs f1, f4, f1
	lfd f0, 0xd8(r1)
	fsubs f0, f0, f31
	fdivs f2, f2, f0
	bl PSMTXTrans
	mr r4, r23
	addi r3, r1, 0x28
	li r5, 0x1
	bl GXLoadTexMtxImm
	addi r23, r23, 0x3
	addi r19, r19, 0x1
	addi r22, r22, 0x8
	addi r21, r21, 0x8
	addi r28, r28, 0x1
	@8:
	cmpwi r19, 0x8
	bge @10
	cmpw r28, r29
	blt @9
	@10:
	clrlslwi r3, r19, 25, 1
	bl GXSetNumTevStages
	clrlwi r3, r19, 24
	bl GXSetNumTexGens
	li r3, 0x80
	li r4, 0x7
	li r5, 0x4
	bl GXBegin
	sth r20, -0x8000(r25)
	li r3, 0x0
	li r0, 0x1
	sth r27, -0x8000(r25)
	sth r3, -0x8000(r25)
	sth r3, -0x8000(r25)
	sth r3, -0x8000(r25)
	sth r31, -0x8000(r25)
	sth r27, -0x8000(r25)
	sth r3, -0x8000(r25)
	sth r0, -0x8000(r25)
	sth r3, -0x8000(r25)
	sth r31, -0x8000(r25)
	sth r30, -0x8000(r25)
	sth r3, -0x8000(r25)
	sth r0, -0x8000(r25)
	sth r0, -0x8000(r25)
	sth r20, -0x8000(r25)
	sth r30, -0x8000(r25)
	sth r3, -0x8000(r25)
	sth r3, -0x8000(r25)
	sth r0, -0x8000(r25)
	@6:
	cmpw r28, r29
	blt @7
	psq_l f31, 0x128(r1), 0, 0
	lfd f31, 0x120(r1)
	lmw r19, 0xec(r1)
	lwz r0, 0x134(r1)
	mtlr r0
	addi r1, r1, 0x130
	blr
}

asm void envBlurOff(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, work@ha
	stw r0, 0x14(r1)
	addi r3, r3, work@l
	lwz r4, gp(r13)
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @1
	addi r3, r3, 0xf0
	@1:
	lwz r0, 0x0(r3)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x0(r3)
	lwz r0, 0x0(r3)
	rlwinm r0, r0, 0, 2, 0
	stw r0, 0x0(r3)
	lwz r3, 0x4c(r3)
	bl _mapFree
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void envBlurOn(s32 type, s32 msec) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r5, work@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	addi r31, r5, work@l
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r4
	stw r28, 0x10(r1)
	mr r28, r3
	lwz r6, gp(r13)
	lwz r0, 0x14(r6)
	cmpwi r0, 0x0
	beq @1
	addi r31, r31, 0xf0
	@1:
	lwz r0, 0x0(r31)
	addi r30, r31, 0x98
	mr r3, r30
	li r4, 0x0
	oris r0, r0, 0x4000
	li r5, 0x18
	stw r0, 0x0(r31)
	lwz r0, 0x0(r31)
	ori r0, r0, 0x4
	stw r0, 0x0(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	bl memset
	lwz r3, gp(r13)
	cmpwi r28, 0x0
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0xc(r30)
	stw r0, 0x8(r30)
	stw r29, 0x10(r30)
	beq @2
	lhz r0, 0x0(r30)
	ori r0, r0, 0x1
	sth r0, 0x0(r30)
	@2:
	lwz r4, gp(r13)
	li r5, 0x4
	li r6, 0x0
	li r7, 0x0
	lhz r3, 0x170(r4)
	lhz r0, 0x172(r4)
	extrwi r3, r3, 16, 15
	extrwi r4, r0, 16, 15
	bl GXGetTexBufferSize
	bl _mapAlloc
	stw r3, 0x4c(r31)
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void envDisp_Blur(void) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	lis r3, work@ha
	stw r0, 0x74(r1)
	stw r31, 0x6c(r1)
	addi r31, r3, work@l
	stw r30, 0x68(r1)
	stw r29, 0x64(r1)
	lwz r4, gp(r13)
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @1
	addi r31, r31, 0xf0
	@1:
	lwz r3, 0x0(r31)
	addi r30, r31, 0x98
	rlwinm. r0, r3, 0, 1, 1
	beq @2
	rlwinm. r0, r3, 0, 28, 28
	beq @2
	li r3, 0x8
	bl camGetPtr
	mr r29, r3
	li r3, 0x8
	bl camGetPtr
	lwz r4, 0x19c(r29)
	addi r3, r3, 0x15c
	bl GXSetProjection
	li r3, 0x8
	bl camGetPtr
	li r4, 0x0
	addi r3, r3, 0x11c
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	li r3, 0x0
	bl GXSetNumChans
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x1
	bl GXSetNumTexGens
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x3c
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x6
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x0
	li r4, 0xc
	bl GXSetTevKColorSel
	li r3, 0x0
	li r4, 0x1c
	bl GXSetTevKAlphaSel
	lwz r29, 0x10(r30)
	cmpwi r29, 0x0
	beq @3
	lis r3, 0x8000
	lwz r6, gp(r13)
	lwz r0, 0xf8(r3)
	lis r3, 0x1062
	lwz r5, 0x3c(r6)
	addi r3, r3, 0x4dd3
	srwi r0, r0, 2
	lwz r4, 0xc(r30)
	mulhwu r0, r3, r0
	lwz r6, 0x38(r6)
	subfc r4, r4, r5
	lwz r3, 0x8(r30)
	li r5, 0x0
	subfe r3, r3, r6
	srwi r6, r0, 6
	bl __div2u
	bl __cvt_ull_flt
	xoris r3, r29, 0x8000
	lis r0, 0x4330
	stw r3, 0x1c(r1)
	lis r4, double_to_int_802f93a0@ha
	lfd f3, double_to_int_802f93a0@l(r4)
	stw r0, 0x18(r1)
	lfs f0, float_1_8041e574(r2)
	lfd f2, 0x18(r1)
	fsubs f2, f2, f3
	fdivs f3, f1, f2
	fcmpo cr0, f3, f0
	ble @4
	fmr f3, f0
	@4:
	lhz r0, 0x0(r30)
	clrlwi. r0, r0, 31
	beq @5
	lfs f0, float_1_8041e574(r2)
	lfs f1, float_255_8041e5c4(r2)
	fsubs f0, f0, f3
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x20(r1)
	lwz r5, 0x24(r1)
	b @6
	@5:
	lfs f0, float_1_8041e574(r2)
	lfs f2, float_120_8041e5c8(r2)
	fsubs f1, f0, f3
	lfs f0, float_128_8041e554(r2)
	fmadds f0, f2, f1, f0
	fctiwz f0, f0
	stfd f0, 0x28(r1)
	lwz r5, 0x2c(r1)
	@6:
	lwz r0, dat_8041e514(r2)
	addi r4, r1, 0x10
	li r3, 0x0
	stw r0, 0xc(r1)
	stb r5, 0xf(r1)
	lwz r0, 0xc(r1)
	stw r0, 0x10(r1)
	bl GXSetTevKColor
	b @7
	@3:
	lwz r0, dat_8041e518(r2)
	addi r4, r1, 0x8
	li r3, 0x0
	stw r0, 0x8(r1)
	bl GXSetTevKColor
	@7:
	addi r3, r31, 0x50
	li r4, 0x0
	bl GXLoadTexObj
	li r3, 0x1
	li r4, 0x4
	li r5, 0x5
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x1
	bl GXSetZCompLoc
	li r3, 0x7
	li r4, 0x0
	li r5, 0x0
	li r6, 0x7
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x0
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xd
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	lwz r8, gp(r13)
	lis r5, 0x4330
	lis r3, double_to_int_802f93a0@ha
	lis r4, double_to_int_mask_802f93a8@ha
	lhz r0, 0x170(r8)
	addi r6, r4, double_to_int_mask_802f93a8@l
	lhz r7, 0x172(r8)
	lis r4, 0xcc01
	neg r0, r0
	stw r5, 0x20(r1)
	xoris r0, r0, 0x8000
	lfd f2, double_to_int_802f93a0@l(r3)
	stw r0, 0x24(r1)
	lfd f4, 0x0(r6)
	lfd f0, 0x20(r1)
	stw r7, 0x2c(r1)
	fsubs f0, f0, f2
	lfs f3, float_0p5_8041e538(r2)
	stw r5, 0x28(r1)
	lfd f1, 0x28(r1)
	fmuls f0, f0, f3
	stw r5, 0x30(r1)
	fsubs f1, f1, f4
	stfs f0, -0x8000(r4)
	fmuls f0, f1, f3
	stw r5, 0x18(r1)
	stw r5, 0x40(r1)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stw r5, 0x38(r1)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stw r5, 0x50(r1)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stw r5, 0x48(r1)
	stfs f0, -0x8000(r4)
	lhz r0, 0x170(r8)
	lhz r3, 0x172(r8)
	stw r0, 0x34(r1)
	stw r3, 0x1c(r1)
	lfd f0, 0x30(r1)
	lfd f1, 0x18(r1)
	fsubs f0, f0, f4
	fsubs f1, f1, f4
	fmuls f0, f0, f3
	fmuls f1, f1, f3
	stfs f0, -0x8000(r4)
	stfs f1, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041e574(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r4)
	lhz r3, 0x172(r8)
	lhz r0, 0x170(r8)
	neg r3, r3
	stw r0, 0x44(r1)
	xoris r0, r3, 0x8000
	stw r0, 0x3c(r1)
	lfd f0, 0x40(r1)
	lfd f1, 0x38(r1)
	fsubs f0, f0, f4
	fsubs f1, f1, f2
	fmuls f0, f0, f3
	fmuls f1, f1, f3
	stfs f0, -0x8000(r4)
	stfs f1, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041e574(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041e574(r2)
	stfs f0, -0x8000(r4)
	lhz r0, 0x170(r8)
	lhz r3, 0x172(r8)
	neg r0, r0
	xoris r0, r0, 0x8000
	neg r3, r3
	stw r0, 0x54(r1)
	xoris r0, r3, 0x8000
	stw r0, 0x4c(r1)
	lfd f0, 0x50(r1)
	lfd f1, 0x48(r1)
	fsubs f0, f0, f2
	fsubs f1, f1, f2
	fmuls f0, f0, f3
	fmuls f1, f1, f3
	stfs f0, -0x8000(r4)
	stfs f1, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041e574(r2)
	stfs f0, -0x8000(r4)
	@2:
	lwz r0, 0x74(r1)
	lwz r31, 0x6c(r1)
	lwz r30, 0x68(r1)
	lwz r29, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void envDisp_DepthOfField(void) {
	nofralloc
	stwu r1, -0x160(r1)
	mflr r0
	stw r0, 0x164(r1)
	stfd f31, 0x150(r1)
	psq_st f31, 0x158(r1), 0, 0
	stfd f30, 0x140(r1)
	psq_st f30, 0x148(r1), 0, 0
	stfd f29, 0x130(r1)
	psq_st f29, 0x138(r1), 0, 0
	stfd f28, 0x120(r1)
	psq_st f28, 0x128(r1), 0, 0
	stfd f27, 0x110(r1)
	psq_st f27, 0x118(r1), 0, 0
	stfd f26, 0x100(r1)
	psq_st f26, 0x108(r1), 0, 0
	stfd f25, 0xf0(r1)
	psq_st f25, 0xf8(r1), 0, 0
	stfd f24, 0xe0(r1)
	psq_st f24, 0xe8(r1), 0, 0
	stmw r25, 0xc4(r1)
	lwz r4, gp(r13)
	lis r3, work@ha
	addi r28, r3, work@l
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @1
	addi r28, r28, 0xf0
	@1:
	lwz r0, 0x0(r28)
	addi r29, r28, 0x88
	clrrwi. r0, r0, 31
	beq @2
	li r3, 0x8
	bl camGetPtr
	mr r27, r3
	li r3, 0x8
	bl camGetPtr
	lwz r4, 0x19c(r27)
	addi r3, r3, 0x15c
	bl GXSetProjection
	li r3, 0x8
	bl camGetPtr
	li r4, 0x0
	addi r3, r3, 0x11c
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	lwz r4, 0x4(r28)
	addi r3, r28, 0xc
	bl smartTexObj
	li r4, 0x0
	bl GXLoadTexObj
	lwz r4, 0x8(r28)
	addi r3, r28, 0x2c
	bl smartTexObj
	li r4, 0x1
	bl GXLoadTexObj
	li r3, 0x0
	bl GXSetNumChans
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x0
	li r4, 0x1
	li r5, 0x0
	li r6, 0x7
	bl GXSetBlendMode
	li r3, 0x0
	bl GXSetZCompLoc
	li r3, 0x6
	li r4, 0x80
	li r5, 0x1
	li r6, 0x0
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x0
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xd
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	bl GXSetCullMode
	lhz r0, 0x0(r29)
	clrlwi. r0, r0, 31
	beq @3
	lfs f1, 0x4(r29)
	lfs f0, float_0_8041e53c(r2)
	fcmpu cr0, f1, f0
	beq @3
	lis r3, double_to_int_802f93a0@ha
	lis r4, dat_802f9338@ha
	lfs f31, float_6p2832_8041e558(r2)
	addi r30, r4, dat_802f9338@l
	lfd f30, double_to_int_802f93a0@l(r3)
	li r25, 0x0
	lfs f29, float_0p25_8041e57c(r2)
	li r26, 0x0
	lfs f26, float_0p16605_8041e5b8(r2)
	li r31, 0x0
	lfs f27, float_1_8041e574(r2)
	lis r28, 0x4330
	lfs f28, float_3p1416_8041e580(r2)
	lfs f25, float_0p4967_8041e5a8(r2)
	lfs f24, float_100_8041e5bc(r2)
	@4:
	xoris r0, r31, 0x8000
	stw r28, 0x78(r1)
	lfs f2, float_0p00761_8041e5b4(r2)
	stw r0, 0x7c(r1)
	lfd f0, 0x78(r1)
	fsubs f0, f0, f30
	fmuls f0, f31, f0
	fmuls f3, f0, f29
	fcmpo cr0, f3, f28
	cror eq, lt, eq
	bne @5
	lfs f1, float_1p5708_8041e5ac(r2)
	fcmpo cr0, f3, f1
	cror eq, lt, eq
	bne @6
	fmuls f0, f3, f3
	fmsubs f2, f2, f0, f26
	fmadds f2, f2, f0, f27
	fmuls f2, f2, f3
	b @7
	@6:
	fsubs f0, f3, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f2, f2, f0, f26
	fmadds f2, f2, f0, f27
	fmuls f2, f2, f1
	b @7
	@5:
	lfs f0, float_4p7124_8041e5b0(r2)
	fcmpo cr0, f3, f0
	bge @8
	fsubs f1, f3, f28
	fmuls f0, f1, f1
	fmsubs f2, f2, f0, f26
	fmadds f2, f2, f0, f27
	fmuls f2, f2, f1
	fneg f2, f2
	b @7
	@8:
	fsubs f0, f3, f0
	lfs f1, float_1p5708_8041e5ac(r2)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f2, f2, f0, f26
	fmadds f2, f2, f0, f27
	fmuls f2, f2, f1
	fneg f2, f2
	@7:
	fcmpo cr0, f3, f28
	lfs f4, float_0p03705_8041e5a4(r2)
	cror eq, lt, eq
	bne @9
	lfs f1, float_1p5708_8041e5ac(r2)
	fcmpo cr0, f3, f1
	cror eq, lt, eq
	bne @10
	fmuls f0, f3, f3
	fmsubs f4, f4, f0, f25
	fmadds f4, f4, f0, f27
	b @11
	@10:
	fsubs f0, f3, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f25
	fmadds f4, f4, f0, f27
	fneg f4, f4
	b @11
	@9:
	lfs f0, float_4p7124_8041e5b0(r2)
	fcmpo cr0, f3, f0
	bge @12
	fsubs f0, f3, f28
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f25
	fmadds f4, f4, f0, f27
	fneg f4, f4
	b @11
	@12:
	fsubs f0, f3, f0
	lfs f1, float_1p5708_8041e5ac(r2)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f25
	fmadds f4, f4, f0, f27
	@11:
	lfs f0, 0x4(r29)
	addi r3, r1, 0x48
	lfs f3, float_0_8041e53c(r2)
	fmuls f1, f0, f2
	fmuls f0, f0, f4
	fdivs f1, f1, f24
	fdivs f2, f0, f24
	bl PSMTXTrans
	lwz r4, 0x0(r30)
	addi r3, r1, 0x48
	li r5, 0x1
	bl GXLoadTexMtxImm
	lwz r6, 0x0(r30)
	mr r3, r25
	li r4, 0x1
	li r5, 0x4
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	mr r3, r26
	li r4, 0x6
	bl GXSetTevKColorSel
	mr r3, r26
	li r4, 0x6
	bl GXSetTevKAlphaSel
	mr r3, r26
	mr r4, r25
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	subfic r0, r31, 0x3
	mr r3, r26
	cntlzw r0, r0
	li r4, 0x0
	srwi r8, r0, 5
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	bl GXSetTevColorOp
	subfic r0, r31, 0x3
	mr r3, r26
	cntlzw r0, r0
	li r4, 0x0
	srwi r8, r0, 5
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	bl GXSetTevAlphaOp
	cntlzw r0, r31
	li r7, 0x0
	srwi. r27, r0, 5
	beq @13
	li r7, 0xf
	@13:
	mr r3, r26
	li r4, 0xf
	li r5, 0x8
	li r6, 0xe
	bl GXSetTevColorIn
	cmpwi r27, 0x0
	mr r3, r26
	li r4, 0x7
	li r5, 0x4
	li r6, 0x6
	li r7, 0x0
	beq @14
	li r7, 0x7
	@14:
	bl GXSetTevAlphaIn
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	addi r31, r31, 0x1
	addi r30, r30, 0x4
	cmpwi r31, 0x4
	addi r26, r26, 0x1
	addi r25, r25, 0x1
	blt @4
	lbz r5, 0x2(r29)
	li r0, 0xff
	stb r0, 0x17(r1)
	addi r4, r1, 0x10
	li r3, 0x0
	stb r5, 0x14(r1)
	lwz r0, 0x14(r1)
	stw r0, 0x10(r1)
	bl GXSetTevKColor
	mr r3, r25
	li r4, 0x1
	li r5, 0x4
	li r6, 0x3c
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	mr r27, r25
	mr r3, r26
	li r4, 0xc
	addi r25, r25, 0x1
	bl GXSetTevKColorSel
	mr r3, r26
	li r4, 0x1c
	bl GXSetTevKAlphaSel
	mr r3, r26
	mr r4, r27
	li r5, 0x1
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r26
	li r4, 0x8
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r26
	li r4, 0x8
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r26
	li r4, 0x8
	li r5, 0xe
	li r6, 0x2
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r26
	li r4, 0x4
	li r5, 0x6
	li r6, 0x1
	li r7, 0x7
	bl GXSetTevAlphaIn
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	clrlwi r3, r25, 24
	addi r26, r26, 0x1
	bl GXSetNumTexGens
	clrlwi r3, r26, 24
	bl GXSetNumTevStages
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	lwz r8, gp(r13)
	lis r5, 0x4330
	lis r3, double_to_int_802f93a0@ha
	lis r4, double_to_int_mask_802f93a8@ha
	lhz r0, 0x170(r8)
	addi r6, r4, double_to_int_mask_802f93a8@l
	lhz r7, 0x172(r8)
	lis r4, 0xcc01
	neg r0, r0
	stw r5, 0x80(r1)
	xoris r0, r0, 0x8000
	lfd f2, double_to_int_802f93a0@l(r3)
	stw r0, 0x84(r1)
	lfd f4, 0x0(r6)
	lfd f0, 0x80(r1)
	stw r7, 0x7c(r1)
	fsubs f0, f0, f2
	lfs f3, float_0p5_8041e538(r2)
	stw r5, 0x78(r1)
	lfd f1, 0x78(r1)
	fmuls f0, f0, f3
	stw r5, 0x90(r1)
	fsubs f1, f1, f4
	stfs f0, -0x8000(r4)
	fmuls f0, f1, f3
	stw r5, 0x88(r1)
	stw r5, 0xa0(r1)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stw r5, 0x98(r1)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stw r5, 0xb0(r1)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stw r5, 0xa8(r1)
	stfs f0, -0x8000(r4)
	lhz r0, 0x170(r8)
	lhz r3, 0x172(r8)
	stw r0, 0x94(r1)
	stw r3, 0x8c(r1)
	lfd f0, 0x90(r1)
	lfd f1, 0x88(r1)
	fsubs f0, f0, f4
	fsubs f1, f1, f4
	fmuls f0, f0, f3
	fmuls f1, f1, f3
	stfs f0, -0x8000(r4)
	stfs f1, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041e574(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r4)
	lhz r3, 0x172(r8)
	lhz r0, 0x170(r8)
	neg r3, r3
	stw r0, 0xa4(r1)
	xoris r0, r3, 0x8000
	stw r0, 0x9c(r1)
	lfd f0, 0xa0(r1)
	lfd f1, 0x98(r1)
	fsubs f0, f0, f4
	fsubs f1, f1, f2
	fmuls f0, f0, f3
	fmuls f1, f1, f3
	stfs f0, -0x8000(r4)
	stfs f1, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041e574(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041e574(r2)
	stfs f0, -0x8000(r4)
	lhz r0, 0x170(r8)
	lhz r3, 0x172(r8)
	neg r0, r0
	xoris r0, r0, 0x8000
	neg r3, r3
	stw r0, 0xb4(r1)
	xoris r0, r3, 0x8000
	stw r0, 0xac(r1)
	lfd f0, 0xb0(r1)
	lfd f1, 0xa8(r1)
	fsubs f0, f0, f2
	fsubs f1, f1, f2
	fmuls f0, f0, f3
	fmuls f1, f1, f3
	stfs f0, -0x8000(r4)
	stfs f1, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041e574(r2)
	stfs f0, -0x8000(r4)
	@3:
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 30, 30
	beq @2
	lfs f1, 0x8(r29)
	lfs f0, float_0_8041e53c(r2)
	fcmpu cr0, f1, f0
	beq @2
	lis r3, double_to_int_802f93a0@ha
	li r31, 0x0
	lis r4, dat_802f9338@ha
	lfs f28, float_6p2832_8041e558(r2)
	lfd f29, double_to_int_802f93a0@l(r3)
	addi r26, r4, dat_802f9338@l
	lfs f30, float_0p25_8041e57c(r2)
	mr r30, r31
	lfs f26, float_0p16605_8041e5b8(r2)
	mr r25, r31
	lfs f25, float_1_8041e574(r2)
	lis r27, 0x4330
	lfs f31, float_3p1416_8041e580(r2)
	lfs f27, float_0p4967_8041e5a8(r2)
	lfs f24, float_100_8041e5bc(r2)
	@15:
	xoris r0, r25, 0x8000
	stw r27, 0xb0(r1)
	lfs f2, float_0p00761_8041e5b4(r2)
	stw r0, 0xb4(r1)
	lfd f0, 0xb0(r1)
	fsubs f0, f0, f29
	fmuls f0, f28, f0
	fmuls f3, f0, f30
	fcmpo cr0, f3, f31
	cror eq, lt, eq
	bne @16
	lfs f1, float_1p5708_8041e5ac(r2)
	fcmpo cr0, f3, f1
	cror eq, lt, eq
	bne @17
	fmuls f0, f3, f3
	fmsubs f2, f2, f0, f26
	fmadds f2, f2, f0, f25
	fmuls f2, f2, f3
	b @18
	@17:
	fsubs f0, f3, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f2, f2, f0, f26
	fmadds f2, f2, f0, f25
	fmuls f2, f2, f1
	b @18
	@16:
	lfs f0, float_4p7124_8041e5b0(r2)
	fcmpo cr0, f3, f0
	bge @19
	fsubs f1, f3, f31
	fmuls f0, f1, f1
	fmsubs f2, f2, f0, f26
	fmadds f2, f2, f0, f25
	fmuls f2, f2, f1
	fneg f2, f2
	b @18
	@19:
	fsubs f0, f3, f0
	lfs f1, float_1p5708_8041e5ac(r2)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f2, f2, f0, f26
	fmadds f2, f2, f0, f25
	fmuls f2, f2, f1
	fneg f2, f2
	@18:
	fcmpo cr0, f3, f31
	lfs f4, float_0p03705_8041e5a4(r2)
	cror eq, lt, eq
	bne @20
	lfs f1, float_1p5708_8041e5ac(r2)
	fcmpo cr0, f3, f1
	cror eq, lt, eq
	bne @21
	fmuls f0, f3, f3
	fmsubs f4, f4, f0, f27
	fmadds f4, f4, f0, f25
	b @22
	@21:
	fsubs f0, f3, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f27
	fmadds f4, f4, f0, f25
	fneg f4, f4
	b @22
	@20:
	lfs f0, float_4p7124_8041e5b0(r2)
	fcmpo cr0, f3, f0
	bge @23
	fsubs f0, f3, f31
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f27
	fmadds f4, f4, f0, f25
	fneg f4, f4
	b @22
	@23:
	fsubs f0, f3, f0
	lfs f1, float_1p5708_8041e5ac(r2)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f27
	fmadds f4, f4, f0, f25
	@22:
	lfs f0, 0x8(r29)
	addi r3, r1, 0x18
	lfs f3, float_0_8041e53c(r2)
	fmuls f1, f0, f2
	fmuls f0, f0, f4
	fdivs f1, f1, f24
	fdivs f2, f0, f24
	bl PSMTXTrans
	lwz r4, 0x0(r26)
	addi r3, r1, 0x18
	li r5, 0x1
	bl GXLoadTexMtxImm
	lwz r6, 0x0(r26)
	mr r3, r31
	li r4, 0x1
	li r5, 0x4
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	mr r3, r30
	li r4, 0x6
	bl GXSetTevKColorSel
	mr r3, r30
	li r4, 0x6
	bl GXSetTevKAlphaSel
	mr r3, r30
	mr r4, r31
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	subfic r0, r25, 0x3
	mr r3, r30
	cntlzw r0, r0
	li r4, 0x0
	srwi r8, r0, 5
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	bl GXSetTevColorOp
	subfic r0, r25, 0x3
	mr r3, r30
	cntlzw r0, r0
	li r4, 0x0
	srwi r8, r0, 5
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	bl GXSetTevAlphaOp
	cntlzw r0, r25
	li r7, 0x0
	srwi. r28, r0, 5
	beq @24
	li r7, 0xf
	@24:
	mr r3, r30
	li r4, 0xf
	li r5, 0x8
	li r6, 0xe
	bl GXSetTevColorIn
	cmpwi r28, 0x0
	mr r3, r30
	li r4, 0x7
	li r5, 0x4
	li r6, 0x6
	li r7, 0x0
	beq @25
	li r7, 0x7
	@25:
	bl GXSetTevAlphaIn
	mr r3, r30
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	addi r25, r25, 0x1
	addi r26, r26, 0x4
	cmpwi r25, 0x4
	addi r30, r30, 0x1
	addi r31, r31, 0x1
	blt @15
	lbz r5, 0x3(r29)
	li r0, 0xff
	stb r0, 0x17(r1)
	addi r4, r1, 0xc
	li r3, 0x0
	stb r5, 0x14(r1)
	lwz r0, 0x14(r1)
	stw r0, 0xc(r1)
	bl GXSetTevKColor
	mr r3, r31
	li r4, 0x1
	li r5, 0x4
	li r6, 0x3c
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwz r0, dat_8041e510(r2)
	mr r25, r31
	addi r4, r1, 0x8
	li r3, 0x2
	stw r0, 0x8(r1)
	addi r31, r31, 0x1
	bl GXSetTevColor
	mr r3, r30
	li r4, 0xc
	bl GXSetTevKColorSel
	mr r3, r30
	li r4, 0x1c
	bl GXSetTevKAlphaSel
	mr r3, r30
	mr r4, r25
	li r5, 0x1
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r30
	li r4, 0x8
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r30
	li r4, 0x8
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r30
	li r4, 0x8
	li r5, 0xe
	li r6, 0xc
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r30
	li r4, 0x4
	li r5, 0x6
	li r6, 0x2
	li r7, 0x7
	bl GXSetTevAlphaIn
	mr r3, r30
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	addi r26, r30, 0x1
	li r4, 0xff
	mr r3, r26
	li r5, 0xff
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r26
	li r4, 0x2
	li r5, 0xf
	li r6, 0x1
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r26
	li r4, 0x1
	li r5, 0x7
	li r6, 0x0
	li r7, 0x7
	bl GXSetTevAlphaIn
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	clrlwi r3, r31, 24
	addi r30, r30, 0x2
	bl GXSetNumTexGens
	clrlwi r3, r30, 24
	bl GXSetNumTevStages
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	lwz r8, gp(r13)
	lis r5, 0x4330
	lis r3, double_to_int_802f93a0@ha
	lis r4, double_to_int_mask_802f93a8@ha
	lhz r0, 0x170(r8)
	addi r6, r4, double_to_int_mask_802f93a8@l
	lhz r7, 0x172(r8)
	lis r4, 0xcc01
	neg r0, r0
	stw r5, 0xa8(r1)
	xoris r0, r0, 0x8000
	lfd f2, double_to_int_802f93a0@l(r3)
	stw r0, 0xac(r1)
	lfd f4, 0x0(r6)
	lfd f0, 0xa8(r1)
	stw r7, 0xb4(r1)
	fsubs f0, f0, f2
	lfs f3, float_0p5_8041e538(r2)
	stw r5, 0xb0(r1)
	lfd f1, 0xb0(r1)
	fmuls f0, f0, f3
	stw r5, 0x98(r1)
	fsubs f1, f1, f4
	stfs f0, -0x8000(r4)
	fmuls f0, f1, f3
	stw r5, 0xa0(r1)
	stw r5, 0x88(r1)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stw r5, 0x90(r1)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stw r5, 0x78(r1)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stw r5, 0x80(r1)
	stfs f0, -0x8000(r4)
	lhz r0, 0x170(r8)
	lhz r3, 0x172(r8)
	stw r0, 0x9c(r1)
	stw r3, 0xa4(r1)
	lfd f0, 0x98(r1)
	lfd f1, 0xa0(r1)
	fsubs f0, f0, f4
	fsubs f1, f1, f4
	fmuls f0, f0, f3
	fmuls f1, f1, f3
	stfs f0, -0x8000(r4)
	stfs f1, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041e574(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r4)
	lhz r3, 0x172(r8)
	lhz r0, 0x170(r8)
	neg r3, r3
	stw r0, 0x8c(r1)
	xoris r0, r3, 0x8000
	stw r0, 0x94(r1)
	lfd f0, 0x88(r1)
	lfd f1, 0x90(r1)
	fsubs f0, f0, f4
	fsubs f1, f1, f2
	fmuls f0, f0, f3
	fmuls f1, f1, f3
	stfs f0, -0x8000(r4)
	stfs f1, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041e574(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041e574(r2)
	stfs f0, -0x8000(r4)
	lhz r0, 0x170(r8)
	lhz r3, 0x172(r8)
	neg r0, r0
	xoris r0, r0, 0x8000
	neg r3, r3
	stw r0, 0x7c(r1)
	xoris r0, r3, 0x8000
	stw r0, 0x84(r1)
	lfd f0, 0x78(r1)
	lfd f1, 0x80(r1)
	fsubs f0, f0, f2
	fsubs f1, f1, f2
	fmuls f0, f0, f3
	fmuls f1, f1, f3
	stfs f0, -0x8000(r4)
	stfs f1, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041e53c(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041e574(r2)
	stfs f0, -0x8000(r4)
	@2:
	psq_l f31, 0x158(r1), 0, 0
	lfd f31, 0x150(r1)
	psq_l f30, 0x148(r1), 0, 0
	lfd f30, 0x140(r1)
	psq_l f29, 0x138(r1), 0, 0
	lfd f29, 0x130(r1)
	psq_l f28, 0x128(r1), 0, 0
	lfd f28, 0x120(r1)
	psq_l f27, 0x118(r1), 0, 0
	lfd f27, 0x110(r1)
	psq_l f26, 0x108(r1), 0, 0
	lfd f26, 0x100(r1)
	psq_l f25, 0xf8(r1), 0, 0
	lfd f25, 0xf0(r1)
	psq_l f24, 0xe8(r1), 0, 0
	lfd f24, 0xe0(r1)
	lmw r25, 0xc4(r1)
	lwz r0, 0x164(r1)
	mtlr r0
	addi r1, r1, 0x160
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_05_80398D1C_data[1] = {0};
