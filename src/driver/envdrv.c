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
#include "memory.h"
#include "sdk/texPalette.h"
#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
extern const u32 dat_8041e510;
extern const u32 dat_8041e514;
extern const u32 dat_8041e518;
extern const u32 dat_8041e51c;
extern const f32 float_0p004_8041e520;
extern const f32 float_10_8041e524;
extern const f32 float_72_8041e528;
extern const f32 float_neg72_8041e52c;
extern const f32 float_neg96_8041e530;
extern const f32 float_96_8041e534;
extern const f32 float_0p5_8041e538;
extern const f32 float_0_8041e53c;
extern const f32 float_1000_8041e540;
extern const f32 float_127_8041e544;
extern const f32 float_18p85_8041e548;
extern const f32 float_0p015625_8041e54c;
extern const f32 float_0p6_8041e550;
extern const f32 float_128_8041e554;
extern const f32 float_6p2832_8041e558;
extern const f32 float_360_8041e55c;
extern const f32 float_45_8041e560;
extern const f32 float_0p15_8041e564;
extern const f32 float_90_8041e568;
extern const f32 float_0p3_8041e56c;
extern const f32 float_deg2rad_8041e570;
extern const f32 float_1_8041e574;
extern const f32 float_neg1p5708_8041e578;
extern const f32 float_0p25_8041e57c;
extern const f32 float_3p1416_8041e580;
extern const f32 float_180_8041e584;
extern const f32 float_20_8041e588;
extern const f32 float_neg1_8041e58c;
extern const f32 float_2_8041e590;
extern const f32 float_0p0001_8041e594;
extern const f32 float_neg32_8041e598;
extern const f32 float_32_8041e59c;
extern const f32 float_300_8041e5a0;
extern const f32 float_0p03705_8041e5a4;
extern const f32 float_0p4967_8041e5a8;
extern const f32 float_1p5708_8041e5ac;
extern const f32 float_4p7124_8041e5b0;
extern const f32 float_0p00761_8041e5b4;
extern const f32 float_0p16605_8041e5b8;
extern const f32 float_100_8041e5bc;
extern const f32 float_neg32767_8041e5c0;
extern const f32 float_255_8041e5c4;
extern const f32 float_120_8041e5c8;
extern const f32 float_5000_8041e5cc;
#define texmtx_tbl ((const s32*)dat_802f9338)
#define white (*(const GXColor*)&dat_8041e510)
#endif
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
        GXInitTexObjLOD(&wp->captureObj, GX_LINEAR, GX_LINEAR, EXT_LIT(float_0_8041e53c, EXT_LIT(float_0_8041e53c, 0.0f)), EXT_LIT(float_0_8041e53c, EXT_LIT(float_0_8041e53c, 0.0f)), EXT_LIT(float_0_8041e53c, EXT_LIT(float_0_8041e53c, 0.0f)), GX_FALSE, GX_FALSE, GX_ANISO_1);
    }
    if (wp->flags & 2) {
        GXSetTexCopySrc(0, 0, var0, var1);
        GXSetTexCopyDst(var2, var3, GX_CTF_Z8M, GX_TRUE);
        size = GXGetTexBufferSize(var2, var3, GX_CTF_Z8M, GX_FALSE, 0);
        wp->capture2 = smartAlloc(size, 3);
        GXCopyTex(wp->capture2->address, 0);
        GXPixModeSync();
        GXInitTexObj(&wp->captureObj2, wp->capture2->address, var2, var3, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&wp->captureObj2, GX_LINEAR, GX_LINEAR, EXT_LIT(float_0_8041e53c, EXT_LIT(float_0_8041e53c, 0.0f)), EXT_LIT(float_0_8041e53c, EXT_LIT(float_0_8041e53c, 0.0f)), EXT_LIT(float_0_8041e53c, EXT_LIT(float_0_8041e53c, 0.0f)), GX_FALSE, GX_FALSE, GX_ANISO_1);
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
        GXInitTexObjLOD(&wp->envBlurObj, GX_LINEAR, GX_LINEAR, EXT_LIT(float_0_8041e53c, EXT_LIT(float_0_8041e53c, 0.0f)), EXT_LIT(float_0_8041e53c, EXT_LIT(float_0_8041e53c, 0.0f)), EXT_LIT(float_0_8041e53c, EXT_LIT(float_0_8041e53c, 0.0f)), GX_FALSE, GX_FALSE, GX_ANISO_1);
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
    dispEntry(CAMERA_3D, EXT_LIT(float_10_8041e524, EXT_LIT(float_10_8041e524, 10.0f)), 7, envDisp, NULL);
    dispEntry(CAMERA_3D, EXT_LIT(float_0_8041e53c, EXT_LIT(float_0_8041e53c, 0.0f)), 7, envCapture2, NULL);
    dispEntry(CAMERA_3D, EXT_LIT(float_5000_8041e5cc, EXT_LIT(float_5000_8041e5cc, 5000.0f)), 8, envDisp2, NULL);
}







#define PI 3.141592653589793f
#define TWO_PI 6.283185307179586f
#ifdef NONMATCHING
static const s32 texmtx_tbl[] = {30, 33, 36, 39, 42, 45, 48, 51, 54, 57};
#endif

static inline f32
env_sin(f32 x) {
    f32 a = 0.00761f;
    f32 b = EXT_LIT(float_0p16605_8041e5b8, 0.16605f);
    f32 c = EXT_LIT(float_1_8041e574, 1.0f);
    f32 y;
    f32 x2;

    if (x <= EXT_LIT(float_3p1416_8041e580, 3.1415927f)) {
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
    else if (x < EXT_LIT(float_4p7124_8041e5b0, 4.712389f)) {
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
    f32 b = EXT_LIT(float_0p4967_8041e5a8, 0.4967f);
    f32 c = EXT_LIT(float_1_8041e574, 1.0f);
    f32 y;
    f32 x2;

    if (x <= EXT_LIT(float_3p1416_8041e580, 3.1415927f)) {
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
    else if (x < EXT_LIT(float_4p7124_8041e5b0, 4.712389f)) {
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
    GXPosition3f32(-(s32)(g)->fbWidth / (half), (g)->efbHeight / (half), (0.0f));         \
    GXTexCoord2f32((0.0f), (0.0f));                                                         \
    GXPosition3f32((g)->fbWidth / (half), (g)->efbHeight / (half), (0.0f));               \
    GXTexCoord2f32((1.0f), (0.0f));                                                         \
    GXPosition3f32((g)->fbWidth / (half), -(s32)(g)->efbHeight / (half), (0.0f));         \
    GXTexCoord2f32((1.0f), (1.0f));                                                         \
    GXPosition3f32(-(s32)(g)->fbWidth / (half), -(s32)(g)->efbHeight / (half), (0.0f));   \
    GXTexCoord2f32((0.0f), (1.0f))

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
            DOF_QUAD(gp, EXT_LIT(float_2_8041e590, 2.0f));
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
            DOF_QUAD(gp, EXT_LIT(float_2_8041e590, 2.0f));
        }
    }
}
#else
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
int __cvt_ull_flt();
int __div2u();
CameraEntry* camGetCurPtr(void);
CameraEntry* camGetPtr(CameraId cameraId);
double acos(double);
double cos(double);
void envTevLoadTexMtxImm(s32 type, GXTexMtx id, GXTexMtx id2, GXTexMtxType mtxType);
int rand(void);
double sin(double);
double tan(double);
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void envDisp_DepthOfField(void) {
	char _af_pad[180];
	asm volatile {
		lwz r4, gp(r13)
		lis r3, work@ha
		addi r28, r3, work@l
		opword 0x80040014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3B9C00F0
		opword 0x801C0000
		opword 0x3BBC0088
		opword 0x54000001
		opword 0x41820C84
		opword 0x38600008
		bl camGetPtr
		opword 0x7C7B1B78
		opword 0x38600008
		bl camGetPtr
		opword 0x809B019C
		opword 0x3863015C
		bl GXSetProjection
		opword 0x38600008
		bl camGetPtr
		opword 0x38800000
		opword 0x3863011C
		bl GXLoadPosMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		opword 0x809C0004
		opword 0x387C000C
		bl smartTexObj
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x809C0008
		opword 0x387C002C
		bl smartTexObj
		opword 0x38800001
		bl GXLoadTexObj
		opword 0x38600000
		bl GXSetNumChans
		opword 0x38600004
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0x39000002
		opword 0x39200002
		bl GXSetChanCtrl
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00000
		opword 0x38C00007
		bl GXSetBlendMode
		opword 0x38600000
		bl GXSetZCompLoc
		opword 0x38600006
		opword 0x38800080
		opword 0x38A00001
		opword 0x38C00000
		opword 0x38E00000
		bl GXSetAlphaCompare
		opword 0x38600000
		opword 0x38800003
		opword 0x38A00000
		bl GXSetZMode
		bl GXClearVtxDesc
		opword 0x38600009
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x3860000D
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x38800009
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x38600000
		opword 0x3880000D
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x38600000
		bl GXSetCullMode
		opword 0xA01D0000
		opword 0x540007FF
		opword 0x41820554
		opword 0xC03D0004
		lfs f0, float_0_8041e53c(r2)
		opword 0xFC010000
		opword 0x41820544
		lis r3, double_to_int_802f93a0@ha
		lis r4, dat_802f9338@ha
		lfs f31, float_6p2832_8041e558(r2)
		addi r30, r4, dat_802f9338@l
		lfd f30, double_to_int_802f93a0@l(r3)
		li r25, 0x0
		lfs f29, float_0p25_8041e57c(r2)
		opword 0x3B400000
		lfs f26, float_0p16605_8041e5b8(r2)
		opword 0x3BE00000
		lfs f27, float_1_8041e574(r2)
		opword 0x3F804330
		lfs f28, float_3p1416_8041e580(r2)
		lfs f25, float_0p4967_8041e5a8(r2)
		lfs f24, float_100_8041e5bc(r2)
		opword 0x6FE08000
		stw r28, _af_pad+112(r1)
		lfs f2, float_0p00761_8041e5b4(r2)
		opword 0x9001007C
		opword 0xC8010078
		opword 0xEC00F028
		opword 0xEC1F0032
		opword 0xEC600772
		opword 0xFC03E040
		opword 0x4C401382
		opword 0x40820044
		lfs f1, float_1p5708_8041e5ac(r2)
		opword 0xFC030840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC0300F2
		opword 0xEC42D038
		opword 0xEC42D83A
		opword 0xEC4200F2
		opword 0x48000068
		opword 0xEC030828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC42D038
		opword 0xEC42D83A
		opword 0xEC420072
		opword 0x4800004C
		lfs f0, float_4p7124_8041e5b0(r2)
		opword 0xFC030040
		opword 0x40800020
		opword 0xEC23E028
		opword 0xEC010072
		opword 0xEC42D038
		opword 0xEC42D83A
		opword 0xEC420072
		opword 0xFC401050
		opword 0x48000024
		opword 0xEC030028
		lfs f1, float_1p5708_8041e5ac(r2)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC42D038
		opword 0xEC42D83A
		opword 0xEC420072
		opword 0xFC401050
		opword 0xFC03E040
		lfs f4, float_0p03705_8041e5a4(r2)
		opword 0x4C401382
		opword 0x40820040
		lfs f1, float_1p5708_8041e5ac(r2)
		opword 0xFC030840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC0300F2
		opword 0xEC84C838
		opword 0xEC84D83A
		opword 0x4800005C
		opword 0xEC030828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC84C838
		opword 0xEC84D83A
		opword 0xFC802050
		opword 0x48000040
		lfs f0, float_4p7124_8041e5b0(r2)
		opword 0xFC030040
		opword 0x4080001C
		opword 0xEC03E028
		opword 0xEC000032
		opword 0xEC84C838
		opword 0xEC84D83A
		opword 0xFC802050
		opword 0x4800001C
		opword 0xEC030028
		lfs f1, float_1p5708_8041e5ac(r2)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC84C838
		opword 0xEC84D83A
		opword 0xC01D0004
		opword 0x38610048
		lfs f3, float_0_8041e53c(r2)
		opword 0xEC2000B2
		opword 0xEC000132
		opword 0xEC21C024
		opword 0xEC40C024
		bl PSMTXTrans
		opword 0x809E0000
		opword 0x38610048
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x80DE0000
		opword 0x7F23CB78
		opword 0x38800001
		opword 0x38A00004
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7F43D378
		opword 0x38800006
		bl GXSetTevKColorSel
		opword 0x7F43D378
		opword 0x38800006
		bl GXSetTevKAlphaSel
		opword 0x7F43D378
		opword 0x7F24CB78
		opword 0x38A00000
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x201F0003
		opword 0x7F43D378
		opword 0x7C000034
		opword 0x38800000
		opword 0x5408D97E
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		bl GXSetTevColorOp
		opword 0x201F0003
		opword 0x7F43D378
		opword 0x7C000034
		opword 0x38800000
		opword 0x5408D97E
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		bl GXSetTevAlphaOp
		opword 0x7FE00034
		opword 0x38E00000
		opword 0x541BD97F
		opword 0x41820008
		opword 0x38E0000F
		opword 0x7F43D378
		opword 0x3880000F
		opword 0x38A00008
		opword 0x38C0000E
		bl GXSetTevColorIn
		opword 0x2C1B0000
		opword 0x7F43D378
		opword 0x38800007
		opword 0x38A00004
		opword 0x38C00006
		opword 0x38E00000
		opword 0x41820008
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3BFF0001
		opword 0x3BDE0004
		opword 0x2C1F0004
		opword 0x3B5A0001
		opword 0x3B390001
		opword 0x4180FD94
		opword 0x88BD0002
		opword 0x380000FF
		opword 0x98010017
		opword 0x38810010
		opword 0x38600000
		opword 0x98A10014
		opword 0x80010014
		opword 0x90010010
		bl GXSetTevKColor
		opword 0x7F23CB78
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0003C
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7F3BCB78
		opword 0x7F43D378
		opword 0x3880000C
		opword 0x3B390001
		bl GXSetTevKColorSel
		opword 0x7F43D378
		opword 0x3880001C
		bl GXSetTevKAlphaSel
		opword 0x7F43D378
		opword 0x7F64DB78
		opword 0x38A00001
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F43D378
		opword 0x38800008
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F43D378
		opword 0x38800008
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F43D378
		opword 0x38800008
		opword 0x38A0000E
		opword 0x38C00002
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7F43D378
		opword 0x38800004
		opword 0x38A00006
		opword 0x38C00001
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x5723063E
		opword 0x3B5A0001
		bl GXSetNumTexGens
		opword 0x5743063E
		bl GXSetNumTevStages
		opword 0x38600080
		opword 0x38800000
		opword 0x38A00004
		bl GXBegin
		lwz r8, gp(r13)
		opword 0x3CA04330
		lis r3, double_to_int_802f93a0@ha
		lis r4, double_to_int_mask_802f93a8@ha
		opword 0xA0080170
		addi r6, r4, double_to_int_mask_802f93a8@l
		opword 0xA0E80172
		opword 0x3C80CC01
		opword 0x7C0000D0
		opword 0x90A10080
		opword 0x6C008000
		lfd f2, double_to_int_802f93a0@l(r3)
		opword 0x90010084
		opword 0xC8860000
		opword 0xC8010080
		opword 0x90E1007C
		opword 0xEC001028
		lfs f3, float_0p5_8041e538(r2)
		opword 0x90A10078
		opword 0xC8210078
		opword 0xEC0000F2
		opword 0x90A10090
		opword 0xEC212028
		opword 0xD0048000
		opword 0xEC0100F2
		opword 0x90A10088
		opword 0x90A100A0
		opword 0xD0048000
		lfs f0, float_0_8041e53c(r2)
		opword 0x90A10098
		opword 0xD0048000
		lfs f0, float_0_8041e53c(r2)
		opword 0x90A100B0
		opword 0xD0048000
		lfs f0, float_0_8041e53c(r2)
		opword 0x90A100A8
		opword 0xD0048000
		opword 0xA0080170
		opword 0xA0680172
		opword 0x90010094
		opword 0x9061008C
		opword 0xC8010090
		opword 0xC8210088
		opword 0xEC002028
		opword 0xEC212028
		opword 0xEC0000F2
		opword 0xEC2100F2
		opword 0xD0048000
		opword 0xD0248000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD0048000
		lfs f0, float_1_8041e574(r2)
		opword 0xD0048000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD0048000
		opword 0xA0680172
		opword 0xA0080170
		opword 0x7C6300D0
		opword 0x900100A4
		opword 0x6C608000
		opword 0x9001009C
		opword 0xC80100A0
		opword 0xC8210098
		opword 0xEC002028
		opword 0xEC211028
		opword 0xEC0000F2
		opword 0xEC2100F2
		opword 0xD0048000
		opword 0xD0248000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD0048000
		lfs f0, float_1_8041e574(r2)
		opword 0xD0048000
		lfs f0, float_1_8041e574(r2)
		opword 0xD0048000
		opword 0xA0080170
		opword 0xA0680172
		opword 0x7C0000D0
		opword 0x6C008000
		opword 0x7C6300D0
		opword 0x900100B4
		opword 0x6C608000
		opword 0x900100AC
		opword 0xC80100B0
		opword 0xC82100A8
		opword 0xEC001028
		opword 0xEC211028
		opword 0xEC0000F2
		opword 0xEC2100F2
		opword 0xD0048000
		opword 0xD0248000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD0048000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD0048000
		lfs f0, float_1_8041e574(r2)
		opword 0xD0048000
		opword 0xA01D0000
		opword 0x540007BD
		opword 0x418205F8
		opword 0xC03D0008
		lfs f0, float_0_8041e53c(r2)
		opword 0xFC010000
		opword 0x418205E8
		lis r3, double_to_int_802f93a0@ha
		opword 0x3BE00000
		lis r4, dat_802f9338@ha
		lfs f28, float_6p2832_8041e558(r2)
		lfd f29, double_to_int_802f93a0@l(r3)
		addi r26, r4, dat_802f9338@l
		lfs f30, float_0p25_8041e57c(r2)
		opword 0x7FFEFB78
		lfs f26, float_0p16605_8041e5b8(r2)
		opword 0x7FF9FB78
		lfs f25, float_1_8041e574(r2)
		opword 0x3F604330
		lfs f31, float_3p1416_8041e580(r2)
		lfs f27, float_0p4967_8041e5a8(r2)
		lfs f24, float_100_8041e5bc(r2)
		opword 0x6F208000
		opword 0x936100B0
		lfs f2, float_0p00761_8041e5b4(r2)
		opword 0x900100B4
		opword 0xC80100B0
		opword 0xEC00E828
		opword 0xEC1C0032
		opword 0xEC6007B2
		opword 0xFC03F840
		opword 0x4C401382
		opword 0x40820044
		lfs f1, float_1p5708_8041e5ac(r2)
		opword 0xFC030840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC0300F2
		opword 0xEC42D038
		opword 0xEC42C83A
		opword 0xEC4200F2
		opword 0x48000068
		opword 0xEC030828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC42D038
		opword 0xEC42C83A
		opword 0xEC420072
		opword 0x4800004C
		lfs f0, float_4p7124_8041e5b0(r2)
		opword 0xFC030040
		opword 0x40800020
		opword 0xEC23F828
		opword 0xEC010072
		opword 0xEC42D038
		opword 0xEC42C83A
		opword 0xEC420072
		opword 0xFC401050
		opword 0x48000024
		opword 0xEC030028
		lfs f1, float_1p5708_8041e5ac(r2)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC42D038
		opword 0xEC42C83A
		opword 0xEC420072
		opword 0xFC401050
		opword 0xFC03F840
		lfs f4, float_0p03705_8041e5a4(r2)
		opword 0x4C401382
		opword 0x40820040
		lfs f1, float_1p5708_8041e5ac(r2)
		opword 0xFC030840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC0300F2
		opword 0xEC84D838
		opword 0xEC84C83A
		opword 0x4800005C
		opword 0xEC030828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC84D838
		opword 0xEC84C83A
		opword 0xFC802050
		opword 0x48000040
		lfs f0, float_4p7124_8041e5b0(r2)
		opword 0xFC030040
		opword 0x4080001C
		opword 0xEC03F828
		opword 0xEC000032
		opword 0xEC84D838
		opword 0xEC84C83A
		opword 0xFC802050
		opword 0x4800001C
		opword 0xEC030028
		lfs f1, float_1p5708_8041e5ac(r2)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC84D838
		opword 0xEC84C83A
		opword 0xC01D0008
		opword 0x38610018
		lfs f3, float_0_8041e53c(r2)
		opword 0xEC2000B2
		opword 0xEC000132
		opword 0xEC21C024
		opword 0xEC40C024
		bl PSMTXTrans
		opword 0x809A0000
		opword 0x38610018
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x80DA0000
		opword 0x7FE3FB78
		opword 0x38800001
		opword 0x38A00004
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7FC3F378
		opword 0x38800006
		bl GXSetTevKColorSel
		opword 0x7FC3F378
		opword 0x38800006
		bl GXSetTevKAlphaSel
		opword 0x7FC3F378
		opword 0x7FE4FB78
		opword 0x38A00000
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x20190003
		opword 0x7FC3F378
		opword 0x7C000034
		opword 0x38800000
		opword 0x5408D97E
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		bl GXSetTevColorOp
		opword 0x20190003
		opword 0x7FC3F378
		opword 0x7C000034
		opword 0x38800000
		opword 0x5408D97E
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		bl GXSetTevAlphaOp
		opword 0x7F200034
		opword 0x38E00000
		opword 0x541CD97F
		opword 0x41820008
		opword 0x38E0000F
		opword 0x7FC3F378
		opword 0x3880000F
		opword 0x38A00008
		opword 0x38C0000E
		bl GXSetTevColorIn
		opword 0x2C1C0000
		opword 0x7FC3F378
		opword 0x38800007
		opword 0x38A00004
		opword 0x38C00006
		opword 0x38E00000
		opword 0x41820008
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B390001
		opword 0x3B5A0004
		opword 0x2C190004
		opword 0x3BDE0001
		opword 0x3BFF0001
		opword 0x4180FD94
		opword 0x88BD0003
		opword 0x380000FF
		opword 0x98010017
		opword 0x3881000C
		opword 0x38600000
		opword 0x98A10014
		opword 0x80010014
		opword 0x9001000C
		bl GXSetTevKColor
		opword 0x7FE3FB78
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0003C
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		lwz r0, dat_8041e510(r2)
		opword 0x7FF9FB78
		opword 0x38810008
		opword 0x38600002
		opword 0x90010008
		opword 0x3BFF0001
		bl GXSetTevColor
		opword 0x7FC3F378
		opword 0x3880000C
		bl GXSetTevKColorSel
		opword 0x7FC3F378
		opword 0x3880001C
		bl GXSetTevKAlphaSel
		opword 0x7FC3F378
		opword 0x7F24CB78
		opword 0x38A00001
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7FC3F378
		opword 0x38800008
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7FC3F378
		opword 0x38800008
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7FC3F378
		opword 0x38800008
		opword 0x38A0000E
		opword 0x38C0000C
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7FC3F378
		opword 0x38800004
		opword 0x38A00006
		opword 0x38C00002
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B5E0001
		opword 0x388000FF
		opword 0x7F43D378
		opword 0x38A000FF
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F43D378
		opword 0x38800002
		opword 0x38A0000F
		opword 0x38C00001
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7F43D378
		opword 0x38800001
		opword 0x38A00007
		opword 0x38C00000
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x57E3063E
		opword 0x3BDE0002
		bl GXSetNumTexGens
		opword 0x57C3063E
		bl GXSetNumTevStages
		opword 0x38600080
		opword 0x38800000
		opword 0x38A00004
		bl GXBegin
		lwz r8, gp(r13)
		opword 0x3CA04330
		lis r3, double_to_int_802f93a0@ha
		lis r4, double_to_int_mask_802f93a8@ha
		opword 0xA0080170
		addi r6, r4, double_to_int_mask_802f93a8@l
		opword 0xA0E80172
		opword 0x3C80CC01
		opword 0x7C0000D0
		opword 0x90A100A8
		opword 0x6C008000
		lfd f2, double_to_int_802f93a0@l(r3)
		opword 0x900100AC
		opword 0xC8860000
		opword 0xC80100A8
		opword 0x90E100B4
		opword 0xEC001028
		lfs f3, float_0p5_8041e538(r2)
		opword 0x90A100B0
		opword 0xC82100B0
		opword 0xEC0000F2
		opword 0x90A10098
		opword 0xEC212028
		opword 0xD0048000
		opword 0xEC0100F2
		opword 0x90A100A0
		opword 0x90A10088
		opword 0xD0048000
		lfs f0, float_0_8041e53c(r2)
		opword 0x90A10090
		opword 0xD0048000
		lfs f0, float_0_8041e53c(r2)
		opword 0x90A10078
		opword 0xD0048000
		lfs f0, float_0_8041e53c(r2)
		opword 0x90A10080
		opword 0xD0048000
		opword 0xA0080170
		opword 0xA0680172
		opword 0x9001009C
		opword 0x906100A4
		opword 0xC8010098
		opword 0xC82100A0
		opword 0xEC002028
		opword 0xEC212028
		opword 0xEC0000F2
		opword 0xEC2100F2
		opword 0xD0048000
		opword 0xD0248000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD0048000
		lfs f0, float_1_8041e574(r2)
		opword 0xD0048000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD0048000
		opword 0xA0680172
		opword 0xA0080170
		opword 0x7C6300D0
		opword 0x9001008C
		opword 0x6C608000
		opword 0x90010094
		opword 0xC8010088
		opword 0xC8210090
		opword 0xEC002028
		opword 0xEC211028
		opword 0xEC0000F2
		opword 0xEC2100F2
		opword 0xD0048000
		opword 0xD0248000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD0048000
		lfs f0, float_1_8041e574(r2)
		opword 0xD0048000
		lfs f0, float_1_8041e574(r2)
		opword 0xD0048000
		opword 0xA0080170
		opword 0xA0680172
		opword 0x7C0000D0
		opword 0x6C008000
		opword 0x7C6300D0
		opword 0x9001007C
		opword 0x6C608000
		opword 0x90010084
		opword 0xC8010078
		opword 0xC8210080
		opword 0xEC001028
		opword 0xEC211028
		opword 0xEC0000F2
		opword 0xEC2100F2
		opword 0xD0048000
		opword 0xD0248000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD0048000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD0048000
		lfs f0, float_1_8041e574(r2)
		opword 0xD0048000
	}
}
#pragma pop
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
            if (t > EXT_LIT(float_1_8041e574, 1.0f)) {
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
        DOF_QUAD(gp, EXT_LIT(float_2_8041e590, 2.0f));
    }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void envDisp_Blur(void) {
	char _af_pad[84];
	asm {
		lis r3, work@ha
		addi r31, r3, work@l
	}
	asm volatile {
		lwz r4, gp(r13)
		opword 0x80040014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3BFF00F0
		opword 0x807F0000
		opword 0x3BDF0098
		opword 0x54600043
		opword 0x41820478
		opword 0x54600739
		opword 0x41820470
		opword 0x38600008
		bl camGetPtr
		opword 0x7C7D1B78
		opword 0x38600008
		bl camGetPtr
		opword 0x809D019C
		opword 0x3863015C
		bl GXSetProjection
		opword 0x38600008
		bl camGetPtr
		opword 0x38800000
		opword 0x3863011C
		bl GXLoadPosMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		opword 0x38600000
		bl GXSetNumChans
		opword 0x38600004
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0x39000002
		opword 0x39200002
		bl GXSetChanCtrl
		opword 0x38600001
		bl GXSetNumTexGens
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0003C
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x38600001
		bl GXSetNumTevStages
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00006
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x38600000
		opword 0x3880000C
		bl GXSetTevKColorSel
		opword 0x38600000
		opword 0x3880001C
		bl GXSetTevKAlphaSel
		lwz r29, 0x10(r30)
		opword 0x2C1D0000
		opword 0x418200EC
		opword 0x3C608000
		lwz r6, gp(r13)
		opword 0x800300F8
		opword 0x3C601062
		opword 0x80A6003C
		opword 0x38634DD3
		opword 0x5400F0BE
		opword 0x809E000C
		opword 0x7C030016
		opword 0x80C60038
		opword 0x7C842810
		opword 0x807E0008
		opword 0x38A00000
		opword 0x7C633110
		opword 0x5406D1BE
		bl __div2u
		bl __cvt_ull_flt
		opword 0x6FA38000
		opword 0x3C004330
		stw r3, _af_pad+20(r1)
		lis r4, double_to_int_802f93a0@ha
		lfd f3, double_to_int_802f93a0@l(r4)
		opword 0x90010018
		lfs f0, float_1_8041e574(r2)
		opword 0xC8410018
		opword 0xEC421828
		opword 0xEC611024
		opword 0xFC030040
		opword 0x40810008
		opword 0xFC600090
		opword 0xA01E0000
		opword 0x540007FF
		opword 0x41820024
		lfs f0, float_1_8041e574(r2)
		lfs f1, float_255_8041e5c4(r2)
		opword 0xEC001828
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010020
		opword 0x80A10024
		opword 0x48000024
		lfs f0, float_1_8041e574(r2)
		lfs f2, float_120_8041e5c8(r2)
		opword 0xEC201828
		lfs f0, float_128_8041e554(r2)
		opword 0xEC02007A
		opword 0xFC00001E
		opword 0xD8010028
		opword 0x80A1002C
		lwz r0, dat_8041e514(r2)
		opword 0x38810010
		opword 0x38600000
		opword 0x9001000C
		opword 0x98A1000F
		opword 0x8001000C
		opword 0x90010010
		bl GXSetTevKColor
		opword 0x48000018
		lwz r0, dat_8041e518(r2)
		opword 0x38810008
		opword 0x38600000
		opword 0x90010008
		bl GXSetTevKColor
		opword 0x387F0050
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x38600001
		opword 0x38800004
		opword 0x38A00005
		opword 0x38C00000
		bl GXSetBlendMode
		opword 0x38600001
		bl GXSetZCompLoc
		opword 0x38600007
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetAlphaCompare
		opword 0x38600000
		opword 0x38800003
		opword 0x38A00000
		bl GXSetZMode
		bl GXClearVtxDesc
		opword 0x38600009
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x3860000D
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x38800009
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x38600000
		opword 0x3880000D
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x38600080
		opword 0x38800000
		opword 0x38A00004
		bl GXBegin
		lwz r8, gp(r13)
		opword 0x3CA04330
		lis r3, double_to_int_802f93a0@ha
		lis r4, double_to_int_mask_802f93a8@ha
		opword 0xA0080170
		addi r6, r4, double_to_int_mask_802f93a8@l
		opword 0xA0E80172
		opword 0x3C80CC01
		opword 0x7C0000D0
		opword 0x90A10020
		opword 0x6C008000
		lfd f2, double_to_int_802f93a0@l(r3)
		opword 0x90010024
		opword 0xC8860000
		opword 0xC8010020
		opword 0x90E1002C
		opword 0xEC001028
		lfs f3, float_0p5_8041e538(r2)
		opword 0x90A10028
		opword 0xC8210028
		opword 0xEC0000F2
		opword 0x90A10030
		opword 0xEC212028
		opword 0xD0048000
		opword 0xEC0100F2
		opword 0x90A10018
		opword 0x90A10040
		opword 0xD0048000
		lfs f0, float_0_8041e53c(r2)
		opword 0x90A10038
		opword 0xD0048000
		lfs f0, float_0_8041e53c(r2)
		opword 0x90A10050
		opword 0xD0048000
		lfs f0, float_0_8041e53c(r2)
		opword 0x90A10048
		opword 0xD0048000
		opword 0xA0080170
		opword 0xA0680172
		opword 0x90010034
		opword 0x9061001C
		opword 0xC8010030
		opword 0xC8210018
		opword 0xEC002028
		opword 0xEC212028
		opword 0xEC0000F2
		opword 0xEC2100F2
		opword 0xD0048000
		opword 0xD0248000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD0048000
		lfs f0, float_1_8041e574(r2)
		opword 0xD0048000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD0048000
		opword 0xA0680172
		opword 0xA0080170
		opword 0x7C6300D0
		opword 0x90010044
		opword 0x6C608000
		opword 0x9001003C
		opword 0xC8010040
		opword 0xC8210038
		opword 0xEC002028
		opword 0xEC211028
		opword 0xEC0000F2
		opword 0xEC2100F2
		opword 0xD0048000
		opword 0xD0248000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD0048000
		lfs f0, float_1_8041e574(r2)
		opword 0xD0048000
		lfs f0, float_1_8041e574(r2)
		opword 0xD0048000
		opword 0xA0080170
		opword 0xA0680172
		opword 0x7C0000D0
		opword 0x6C008000
		opword 0x7C6300D0
		opword 0x90010054
		opword 0x6C608000
		opword 0x9001004C
		opword 0xC8010050
		opword 0xC8210048
		opword 0xEC001028
		opword 0xEC211028
		opword 0xEC0000F2
		opword 0xEC2100F2
		opword 0xD0048000
		opword 0xD0248000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD0048000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD0048000
		lfs f0, float_1_8041e574(r2)
		opword 0xD0048000
	}
}
#pragma pop
#endif

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

void envBlurOff(void) {
    EnvironmentWork* wp = envGetWork();

    wp->flags &= ~4;
    wp->flags &= ~0x40000000;
    _mapFree(wp->envBlur);
}


//almost 1:1, needs some regalloc work and type changes
static u8 gap_08_80418A8C_sbss[4];  // .sbss pad after v_count_761
__declspec(section ".sdata") u32 g5_v_count_s761;
__declspec(section ".sdata") u32 g5_u2_s760;
__declspec(section ".sdata") u32 g5_u1_s759;
__declspec(section ".sdata") u32 g5_a_s655;
__declspec(section ".sdata") u32 g5_frame_cnt_s541;
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

    frame_cnt += EXT_LIT(float_1_8041e574, 1.0f);
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
    GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f), GX_FALSE, GX_FALSE, GX_ANISO_1);
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
    GXSetViewport(EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f), (f32)gp->fbWidth, (f32)gp->efbHeight, EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_1_8041e574, 1.0f));
    GXSetScissor(0, 0, gp->fbWidth, gp->efbHeight);
    MTXOrtho(proj, EXT_LIT(float_0_8041e53c, 0.0f), (f32)gp->efbHeight, EXT_LIT(float_0_8041e53c, 0.0f), (f32)gp->fbWidth, EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_neg32767_8041e5c0, -32767.0f));
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
    GXSetZScaleOffset(EXT_LIT(float_1_8041e574, 1.0f), filter->zscale);
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void envGlare(EnvironmentGlare* glare) {
	char _af_pad[220];
	asm volatile {
		lwz r5, gp(r13)
		lis r4, work@ha
		addi r4, r4, work@l
		opword 0x7C781B78
		opword 0x80050014
		opword 0x2C000000
		opword 0x41820008
		opword 0x388400F0
		lfs f1, g5_frame_cnt_s541(r13)
		opword 0x3BC400B0
		lfs f0, float_1_8041e574(r2)
		opword 0x38A00004
		opword 0xA36400B4
		opword 0x38C00000
		opword 0xEC01002A
		opword 0xA00400B6
		opword 0xA34400B8
		opword 0x38E00000
		opword 0x7C1B0050
		opword 0xA06400BA
		opword 0x7D1A1850
		opword 0x5414FC7E
		opword 0x5515FC7E
		stfs f0, g5_frame_cnt_s541(r13)
		opword 0x7EA3AB78
		opword 0x7E84A378
		opword 0x551F043E
		opword 0x5419043E
		bl GXGetTexBufferSize
		opword 0x38800003
		bl smartAlloc
		lwz r19, 0x0(r3)
		opword 0x7F43D378
		opword 0x7F64DB78
		opword 0x7FE5FB78
		opword 0x7F26CB78
		bl GXSetTexCopySrc
		opword 0x56A3043E
		opword 0x5684043E
		opword 0x38A00004
		opword 0x38C00001
		bl GXSetTexCopyDst
		opword 0x7E639B78
		opword 0x38800000
		bl GXCopyTex
		bl GXPixModeSync
		opword 0x7E649B78
		la r3, _af_pad+0
		opword 0x56A5043E
		opword 0x5686043E
		opword 0x38E00004
		opword 0x39000000
		opword 0x39200000
		opword 0x39400000
		bl GXInitTexObj
		lfs f1, float_0_8041e53c(r2)
		opword 0x38610008
		opword 0x38800001
		opword 0x38A00001
		opword 0xFC400890
		opword 0x38C00000
		opword 0xFC600890
		opword 0x38E00000
		opword 0x39000000
		bl GXInitTexObjLOD
		opword 0x38610008
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x83B80018
		opword 0x3B800000
		opword 0x8298000C
		opword 0x38600000
		opword 0x82B80010
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000002
		bl GXSetTevColorOp
		opword 0x38600000
		opword 0x3880000E
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x7E84A378
		opword 0x38600000
		bl GXSetTevKColorSel
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x38600001
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600001
		opword 0x3880000F
		opword 0x38A00004
		opword 0x38C0000E
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7EA4AB78
		opword 0x38600001
		bl GXSetTevKColorSel
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3A600000
		opword 0x3AE00002
		opword 0x3AC00003
		opword 0x7EE3BB78
		opword 0x38930001
		opword 0x38A00000
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7EE3BB78
		opword 0x38800001
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000002
		bl GXSetTevColorOp
		opword 0x7EE3BB78
		opword 0x3880000E
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x7EE3BB78
		opword 0x7E84A378
		bl GXSetTevKColorSel
		opword 0x7EE3BB78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x7EC3B378
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7EC3B378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7EC3B378
		opword 0x3880000F
		opword 0x38A00004
		opword 0x38C0000E
		opword 0x38E00000
		bl GXSetTevColorIn
		opword 0x7EC3B378
		opword 0x7EA4AB78
		bl GXSetTevKColorSel
		opword 0x7EC3B378
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3A730001
		opword 0x3AD60002
		opword 0x2C130007
		opword 0x3AF70002
		opword 0x4180FF28
		opword 0x3A600000
		opword 0x3AC0001E
		opword 0x7E639B78
		opword 0x7EC6B378
		opword 0x38800001
		opword 0x38A00004
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x3A730001
		opword 0x3AD60003
		opword 0x2C130008
		opword 0x4180FFD8
		opword 0xA01E0000
		opword 0x540007FF
		opword 0x41820018
		opword 0x38600001
		opword 0x38800003
		opword 0x38A00000
		bl GXSetZMode
		opword 0x48000014
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00000
		bl GXSetZMode
		opword 0x80780000
		opword 0x38C00000
		opword 0x80980004
		opword 0x80B80008
		bl GXSetBlendMode
		opword 0x38600000
		bl GXSetNumChans
		opword 0x38600004
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0x39000002
		opword 0x39200002
		bl GXSetChanCtrl
		lwz r6, gp(r13)
		opword 0x3C604330
		lfs f1, float_0_8041e53c(r2)
		lis r4, double_to_int_mask_802f93a8@ha
		opword 0xA0A60170
		opword 0xA0060172
		opword 0xFC400890
		opword 0x90A100CC
		opword 0xFCA00890
		lfd f4, double_to_int_mask_802f93a8@l(r4)
		opword 0x906100C8
		lfs f6, float_1_8041e574(r2)
		opword 0xC80100C8
		opword 0x900100D4
		opword 0xEC602028
		opword 0x906100D0
		opword 0xC80100D0
		opword 0xEC802028
		bl GXSetViewport
		lwz r6, gp(r13)
		opword 0x38600000
		opword 0x38800000
		opword 0xA0A60170
		opword 0xA0C60172
		bl GXSetScissor
		lwz r6, gp(r13)
		opword 0x3C804330
		lfs f1, float_0_8041e53c(r2)
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0xA0A60172
		opword 0xA0060170
		opword 0xFC600890
		opword 0x90A100DC
		opword 0xFCA00890
		lfd f4, double_to_int_mask_802f93a8@l(r3)
		opword 0x38610088
		opword 0x908100D8
		lfs f6, float_neg32767_8041e5c0(r2)
		opword 0xC80100D8
		opword 0x900100E4
		opword 0xEC402028
		opword 0x908100E0
		opword 0xC80100E0
		opword 0xEC802028
		bl C_MTXOrtho
		opword 0x38610088
		opword 0x38800001
		bl GXSetProjection
		opword 0x38610058
		bl PSMTXIdentity
		opword 0x38610058
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		bl GXClearVtxDesc
		opword 0x38600009
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x3860000D
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x38600007
		opword 0x38800009
		opword 0x38A00001
		opword 0x38C00003
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x38600007
		opword 0x3880000D
		opword 0x38A00001
		opword 0x38C00002
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x38600002
		bl GXSetCullMode
		lfs f1, float_1_8041e574(r2)
		opword 0xC05E000C
		bl GXSetZScaleOffset
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x7FDBCA14
		lfd f31, double_to_int_mask_802f93a8@l(r3)
		opword 0x7FFAFA14
		opword 0x7F540734
		opword 0x7F15C378
		opword 0x7F7B0734
		opword 0x3F404330
		opword 0x3F20CC01
		opword 0x48000114
		opword 0x7EB6AB78
		opword 0x3A600000
		opword 0x3AE0001E
		opword 0x4800007C
		lwz r5, gp(r13)
		opword 0x38610028
		opword 0x934100E0
		opword 0xA0850170
		opword 0xA0050172
		opword 0x908100E4
		opword 0xC0780014
		opword 0xC056001C
		opword 0xC82100E0
		opword 0xC0160020
		opword 0xEC8300B2
		opword 0xEC21F828
		opword 0x900100DC
		opword 0xEC430032
		lfs f3, float_0_8041e53c(r2)
		opword 0x934100D8
		opword 0xEC240824
		opword 0xC80100D8
		opword 0xEC00F828
		opword 0xEC420024
		bl PSMTXTrans
		opword 0x7EE4BB78
		opword 0x38610028
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x3AF70003
		opword 0x3A730001
		opword 0x3AD60008
		opword 0x3AB50008
		opword 0x3B9C0001
		opword 0x2C130008
		opword 0x4080000C
		opword 0x7C1CE800
		opword 0x4180FF7C
		opword 0x56630E3C
		bl GXSetNumTevStages
		opword 0x5663063E
		bl GXSetNumTexGens
		opword 0x38600080
		opword 0x38800007
		opword 0x38A00004
		bl GXBegin
		opword 0xB2998000
		opword 0x38600000
		opword 0x38000001
		opword 0xB3798000
		opword 0xB0798000
		opword 0xB0798000
		opword 0xB0798000
		opword 0xB3F98000
		opword 0xB3798000
		opword 0xB0798000
		opword 0xB0198000
		opword 0xB0798000
		opword 0xB3F98000
		opword 0xB3D98000
		opword 0xB0798000
		opword 0xB0198000
		opword 0xB0198000
		opword 0xB2998000
		opword 0xB3D98000
		opword 0xB0798000
		opword 0xB0798000
		opword 0xB0198000
		opword 0x7C1CE800
		opword 0x4180FEEC
	}
}
#pragma pop
#endif


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
    f->zscale = EXT_LIT(float_0_8041e53c, 0.0f);
    f->flags &= ~1;
    wp->flags |= 0x20000000;
}

void envGlareFilterZ(f32 zscale) {
    EnvironmentWork* wp = envGetWork();
    EnvironmentGlareFilter* f = &wp->filter;

    f->zscale = zscale;
    f->flags |= 1;
}

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
            ofs = (rand() % 10) / EXT_LIT(float_100_8041e5bc, 100.0f);
            GXPosition3f32(s * r, c * r, EXT_LIT(float_0_8041e53c, 0.0f));
            GXTexCoord2f32(s / EXT_LIT(float_2_8041e590, 2.0f) + EXT_LIT(float_0p5_8041e538, 0.5f) + ofs, -c / EXT_LIT(float_2_8041e590, 2.0f) + EXT_LIT(float_0p5_8041e538, 0.5f) + ofs);
            GXPosition3f32(EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f));
            GXTexCoord2f32(EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0p5_8041e538, 0.5f));
        }
    }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void envDisp_FF(void) {
	char _af_pad[16];
	asm volatile {
		lwz r4, gp(r13)
		lis r3, work@ha
		addi r29, r3, work@l
		opword 0x80040014
		lis r3, dat_802f9338@ha
		addi r31, r3, dat_802f9338@l
		opword 0x2C000000
		opword 0x41820008
		opword 0x3BBD00F0
		opword 0x801D0000
		opword 0x540000C7
		opword 0x41820498
		opword 0x38600000
		bl GXSetNumChans
		opword 0x38600004
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0x39000002
		opword 0x39200002
		bl GXSetChanCtrl
		opword 0x38600001
		bl GXSetNumTexGens
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0003C
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x38600001
		bl GXSetNumTevStages
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x38600000
		opword 0x38800003
		bl GXSetTevOp
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x387D000C
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x38600001
		opword 0x38800004
		opword 0x38A00005
		opword 0x38C00000
		bl GXSetBlendMode
		opword 0x38600001
		bl GXSetZCompLoc
		opword 0x38600007
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetAlphaCompare
		opword 0x38600000
		opword 0x38800003
		opword 0x38A00000
		bl GXSetZMode
		opword 0x38600010
		opword 0x38800000
		bl GXSetLineWidth
		opword 0x38600008
		bl camGetPtr
		opword 0x38800000
		opword 0x3863011C
		bl GXLoadPosMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		bl GXClearVtxDesc
		opword 0x38600009
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x3860000D
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x38800009
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x38600000
		opword 0x3880000D
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		lwz r3, gp(r13)
		opword 0x3C004330
		stw r0, _af_pad+8(r1)
		opword 0xA0830170
		opword 0xA0630172
		opword 0x5480FC7E
		opword 0xC85F0068
		opword 0x7C8021D6
		opword 0x5460FC7E
		lfs f0, float_0_8041e53c(r2)
		opword 0x7C6019D6
		opword 0x54800FFE
		opword 0x7C802214
		opword 0x54600FFE
		opword 0x7C840E70
		opword 0x7C001A14
		opword 0x7C000E70
		opword 0x7C040214
		opword 0x6C008000
		opword 0x90010014
		opword 0xC8210010
		opword 0xEF211028
		opword 0xFC190040
		opword 0x4081004C
		opword 0xFC20C834
		opword 0xC87F0078
		opword 0xC85F0080
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC19103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC19103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC19103C
		opword 0xFC010032
		opword 0xFF390032
		opword 0xFF20C818
		opword 0x48000088
		opword 0xC81F0088
		opword 0xFC190040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f25, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD3210008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f25, __float_nan@l(r3)
		opword 0x386000A8
		opword 0x38800000
		opword 0x38A007D0
		bl GXBegin
		opword 0x3C606666
		lfs f26, float_6p2832_8041e558(r2)
		opword 0xCB7F0068
		opword 0x3BC36667
		lfs f28, float_1000_8041e540(r2)
		li r28, 0x0
		lfs f23, float_0p4967_8041e5a8(r2)
		opword 0x3FA04330
		lfs f24, float_1_8041e574(r2)
		opword 0x3FE0CC01
		lfs f29, float_3p1416_8041e580(r2)
		lfs f21, float_0p16605_8041e5b8(r2)
		lfs f30, float_100_8041e5bc(r2)
		lfs f31, float_0p5_8041e538(r2)
		opword 0x6F808000
		opword 0x93A10010
		lfs f22, float_0p03705_8041e5a4(r2)
		opword 0x90010014
		opword 0xC8010010
		opword 0xEC00D828
		opword 0xEC1A0032
		opword 0xEC40E024
		opword 0xFC02E840
		opword 0x4C401382
		opword 0x40820040
		lfs f1, float_1p5708_8041e5ac(r2)
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC0200B2
		opword 0xEED6B838
		opword 0xEED6C03A
		opword 0x4800005C
		opword 0xEC020828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEED6B838
		opword 0xEED6C03A
		opword 0xFEC0B050
		opword 0x48000040
		lfs f0, float_4p7124_8041e5b0(r2)
		opword 0xFC020040
		opword 0x4080001C
		opword 0xEC02E828
		opword 0xEC000032
		opword 0xEED6B838
		opword 0xEED6C03A
		opword 0xFEC0B050
		opword 0x4800001C
		opword 0xEC020028
		lfs f1, float_1p5708_8041e5ac(r2)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEED6B838
		opword 0xEED6C03A
		opword 0xFC02E840
		lfs f20, float_0p00761_8041e5b4(r2)
		opword 0x4C401382
		opword 0x40820044
		lfs f1, float_1p5708_8041e5ac(r2)
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC0200B2
		opword 0xEE94A838
		opword 0xEE94C03A
		opword 0xEE9400B2
		opword 0x48000068
		opword 0xEC020828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEE94A838
		opword 0xEE94C03A
		opword 0xEE940072
		opword 0x4800004C
		lfs f0, float_4p7124_8041e5b0(r2)
		opword 0xFC020040
		opword 0x40800020
		opword 0xEC22E828
		opword 0xEC010072
		opword 0xEE94A838
		opword 0xEE94C03A
		opword 0xEE940072
		opword 0xFE80A050
		opword 0x48000024
		opword 0xEC020028
		lfs f1, float_1p5708_8041e5ac(r2)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEE94A838
		opword 0xEE94C03A
		opword 0xEE940072
		opword 0xFE80A050
		bl rand
		opword 0x7C1E1896
		opword 0xEC340672
		opword 0xFC00B050
		opword 0x3B9C0001
		opword 0xEC560672
		opword 0x93A10010
		opword 0x7C001670
		opword 0xD03F8000
		opword 0x54040FFE
		opword 0xEC34FFFA
		opword 0x7C002214
		opword 0xD05F8000
		opword 0x1C00000A
		lfs f2, float_0_8041e53c(r2)
		opword 0xEC00FFFA
		opword 0xD05F8000
		opword 0x2C1C03E8
		opword 0x7C001850
		opword 0x6C008000
		opword 0x90010014
		opword 0xC8410010
		opword 0xEC42D828
		opword 0xEC42F024
		opword 0xEC21102A
		opword 0xEC00102A
		opword 0xD03F8000
		opword 0xD01F8000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD01F8000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD01F8000
		lfs f0, float_0_8041e53c(r2)
		opword 0xD01F8000
		lfs f0, float_0p5_8041e538(r2)
		opword 0xD01F8000
		lfs f0, float_0p5_8041e538(r2)
		opword 0xD01F8000
		opword 0x4180FE2C
	}
}
#pragma pop
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
            PSMTXRotRad(m0, 'Y', EXT_LIT(float_deg2rad_8041e570, 0.017453292f) * tw->rotY);
            PSMTXRotRad(m1, 'Z', EXT_LIT(float_deg2rad_8041e570, 0.017453292f) * -tw->rotX);
            PSMTXConcat(m0, m1, m0);
            PSMTXInvXpose(m0, m0);
            PSVECNormalize((Vec*)m0[0], (Vec*)m0[0]);
            PSVECNormalize((Vec*)m0[1], (Vec*)m0[1]);
            PSVECNormalize((Vec*)m0[2], (Vec*)m0[2]);
            PSMTXScale(m2, EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_1_8041e574, 1.0f));
            PSMTXConcat(m2, m0, m0);
            PSMTXTrans(m2, EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0_8041e53c, 0.0f));
            PSMTXConcat(m2, m0, m0);
            GXLoadTexMtxImm(m0, id, mtxType);
            break;
        case 1:
            PSMTXRotRad(m0, 'Y', EXT_LIT(float_neg1p5708_8041e578, -1.5707964f));
            PSMTXConcat(m0, tw->model, m0);
            PSMTXInvXpose(m0, m0);
            PSVECNormalize((Vec*)m0[0], (Vec*)m0[0]);
            PSVECNormalize((Vec*)m0[1], (Vec*)m0[1]);
            PSVECNormalize((Vec*)m0[2], (Vec*)m0[2]);
            PSMTXScale(m3, EXT_LIT(float_0p5_8041e538, 0.5f) - 0.25f * tw->scale, EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_1_8041e574, 1.0f));
            PSMTXConcat(m3, m0, m0);
            PSMTXTrans(m3, EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0_8041e53c, 0.0f));
            PSMTXConcat(m3, m0, m0);
            GXLoadTexMtxImm(m0, id, mtxType);
            break;
        case 2: {
            Vec v = {0.0f, 0.0f, -1.0f};
            Vec light;
            Vec half;
            f32 ry2, rx2, s2;

            ry2 = EXT_LIT(float_3p1416_8041e580, 3.1415927f) * tw->rotY / EXT_LIT(float_180_8041e584, 180.0f);
            rx2 = EXT_LIT(float_3p1416_8041e580, 3.1415927f) * tw->rotX / EXT_LIT(float_180_8041e584, 180.0f);
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
            s2 = EXT_LIT(float_20_8041e588, 20.0f) * tw->scale;
            PSMTXScale(m4, s2, EXT_LIT(float_1_8041e574, 1.0f), EXT_LIT(float_1_8041e574, 1.0f));
            PSMTXConcat(m4, m0, m0);
            PSMTXTrans(m4, EXT_LIT(float_1_8041e574, 1.0f) - s2, EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f));
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

            ry = EXT_LIT(float_3p1416_8041e580, 3.1415927f) * tw->rotY / EXT_LIT(float_180_8041e584, 180.0f);
            rx = EXT_LIT(float_3p1416_8041e580, 3.1415927f) * tw->rotX / EXT_LIT(float_180_8041e584, 180.0f);
            light2.x = (f32)cos(rx) * (f32)sin(ry);
            light2.y = (f32)sin(rx);
            light2.z = (f32)cos(rx) * (f32)cos(ry);
            PSMTXMultVecSR(tw->view, &light2, &light2);
            dot = PSVECDotProduct(&light2, &v2);
            if (dot == EXT_LIT(float_neg1_8041e58c, -1.0f)) {
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
            if (dot == EXT_LIT(float_1_8041e574, 1.0f)) {
                PSMTXIdentity(m6);
            }
            else {
                PSVECCrossProduct(&h, &v2, &axis);
                PSMTXRotAxisRad(m6, &axis, (f32)acos(PSVECDotProduct(&v2, &h)));
            }
            PSMTXConcat(m6, m5, m0);
            PSMTXScale(m6, EXT_LIT(float_2_8041e590, 2.0f) * tw->scale, EXT_LIT(float_2_8041e590, 2.0f) * tw->scale, EXT_LIT(float_1_8041e574, 1.0f));
            PSMTXConcat(m6, m0, m0);
            PSMTXTrans(m6, EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0_8041e53c, 0.0f));
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
            PSMTXScale(m7, EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0_8041e53c, 0.0f));
            PSMTXTrans(m0, EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_1_8041e574, 1.0f));
            PSMTXConcat(m0, m7, m0);
            GXLoadTexMtxImm(m0, id2, mtxType);
            break;
        case 5: {
            Vec camPos;
            Vec target;
            Vec up;

            a += EXT_LIT(float_0p0001_8041e594, 0.0001f);
            camPos = (Vec){EXT_LIT(float_10_8041e524, 10.0f) * (f32)sin(a), EXT_LIT(float_100_8041e5bc, 100.0f), EXT_LIT(float_10_8041e524, 10.0f) * (f32)cos(a)};
            target = (Vec){EXT_LIT(float_10_8041e524, 10.0f) * (f32)sin(a), EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_10_8041e524, 10.0f) * (f32)cos(a)};
            up = (Vec){EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_neg1_8041e58c, -1.0f)};
            C_MTXLookAt(m8, &camPos, &up, &target);
            C_MTXLightFrustum((MtxPtr)m9, EXT_LIT(float_neg32_8041e598, -32.0f), EXT_LIT(float_32_8041e59c, 32.0f), EXT_LIT(float_neg32_8041e598, -32.0f), EXT_LIT(float_32_8041e59c, 32.0f), EXT_LIT(float_300_8041e5a0, 300.0f), EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0p5_8041e538, 0.5f));
            PSMTXInverse(tw->view, m10);
            PSMTXConcat(m8, m10, m11);
            PSMTXConcat((MtxPtr)m9, m11, m0);
            GXLoadTexMtxImm(m0, id2, mtxType);
            break;
        }
    }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void envTevLoadTexMtxImm(s32 type, GXTexMtx id, GXTexMtx id2, GXTexMtxType mtxType) {
	char _af_pad[748];
	asm volatile {
		lwz r8, gp(r13)
		lis r7, work@ha
		addi r31, r7, work@l
		mr r27, r4
		opword 0x80080014
		lis r7, dat_802f9338@ha
		opword 0x7CBC2B78
		opword 0x7CDD3378
		opword 0x2C000000
		addi r30, r7, dat_802f9338@l
		opword 0x41820008
		opword 0x3BFF00F0
		opword 0x2C030003
		opword 0x41820334
		opword 0x4080001C
		opword 0x2C030001
		opword 0x418200F4
		opword 0x408001A4
		opword 0x2C030000
		opword 0x40800018
		opword 0x48000700
		opword 0x2C030005
		opword 0x41820598
		opword 0x408006F4
		opword 0x48000504
		lfs f1, float_deg2rad_8041e570(r2)
		la r3, _af_pad+696
		opword 0xC01F0080
		opword 0x38800059
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0xC01F0084
		opword 0x38610260
		lfs f1, float_deg2rad_8041e570(r2)
		opword 0x3880005A
		opword 0xFC000050
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x386102C0
		opword 0x38810260
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386102C0
		opword 0x7C641B78
		bl PSMTXInvXpose
		opword 0x386102C0
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0x386102D0
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0x386102E0
		opword 0x7C641B78
		bl PSVECNormalize
		lfs f1, float_0p5_8041e538(r2)
		opword 0x38610290
		lfs f3, float_1_8041e574(r2)
		opword 0xFC400890
		bl PSMTXScale
		opword 0x388102C0
		opword 0x38610290
		opword 0x7C852378
		bl PSMTXConcat
		lfs f1, float_0p5_8041e538(r2)
		opword 0x38610290
		lfs f3, float_0_8041e53c(r2)
		opword 0xFC400890
		bl PSMTXTrans
		opword 0x388102C0
		opword 0x38610290
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x7F64DB78
		opword 0x7FA5EB78
		opword 0x386102C0
		bl GXLoadTexMtxImm
		opword 0x48000620
		lfs f1, float_neg1p5708_8041e578(r2)
		opword 0x386102C0
		opword 0x38800059
		bl PSMTXRotRad
		opword 0x386102C0
		opword 0x809F0078
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386102C0
		opword 0x7C641B78
		bl PSMTXInvXpose
		opword 0x386102C0
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0x386102D0
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0x386102E0
		opword 0x7C641B78
		bl PSVECNormalize
		lfs f2, float_0p5_8041e538(r2)
		opword 0x38610230
		lfs f1, float_0p25_8041e57c(r2)
		opword 0xC01F007C
		lfs f3, float_1_8041e574(r2)
		opword 0xEC21103C
		bl PSMTXScale
		opword 0x388102C0
		opword 0x38610230
		opword 0x7C852378
		bl PSMTXConcat
		lfs f1, float_0p5_8041e538(r2)
		opword 0x38610230
		lfs f3, float_0_8041e53c(r2)
		opword 0xFC400890
		bl PSMTXTrans
		opword 0x388102C0
		opword 0x38610230
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x7F64DB78
		opword 0x7FA5EB78
		opword 0x386102C0
		bl GXLoadTexMtxImm
		opword 0x4800056C
		lfs f3, float_3p1416_8041e580(r2)
		opword 0xC03F0080
		opword 0xC01F0084
		opword 0xEC430072
		lfs f1, float_180_8041e584(r2)
		opword 0xEC030032
		opword 0x809E0028
		opword 0x807E002C
		opword 0xEFC20824
		opword 0x801E0030
		opword 0x90810094
		opword 0x90610098
		opword 0x9001009C
		fdivs f29, f0, f1
		opword 0xFC20F090
		bl sin
		opword 0xFFE00818
		opword 0xFC20E890
		bl cos
		opword 0xFC000818
		opword 0xFC20E890
		opword 0xFC000050
		opword 0xEC0007F2
		opword 0xD0010088
		bl sin
		opword 0xFC000818
		opword 0xFC20F090
		opword 0xFC000050
		opword 0xD001008C
		bl cos
		opword 0xFFE00818
		opword 0xFC20E890
		bl cos
		opword 0xFC000818
		opword 0x38810088
		opword 0x807F0070
		opword 0x7C852378
		opword 0xFC000050
		opword 0xEC0007F2
		opword 0xD0010090
		bl PSMTXMultVecSR
		opword 0x38610088
		opword 0x38810094
		opword 0x38A1007C
		bl C_VECHalfAngle
		opword 0x807F0078
		opword 0x388102C0
		bl PSMTXInvXpose
		opword 0x386102C0
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0x386102D0
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0x386102E0
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0x38610200
		bl PSMTXIdentity
		opword 0xC041007C
		opword 0x388102C0
		opword 0xC0210080
		opword 0x7C852378
		opword 0xC0010084
		opword 0x38610200
		opword 0xD0410200
		opword 0xD0210204
		opword 0xD0010208
		bl PSMTXConcat
		lfs f1, float_20_8041e588(r2)
		opword 0x38610200
		opword 0xC01F007C
		lfs f2, float_1_8041e574(r2)
		opword 0xEFA10032
		opword 0xFC601090
		opword 0xFC20E890
		bl PSMTXScale
		opword 0x388102C0
		opword 0x38610200
		opword 0x7C852378
		bl PSMTXConcat
		lfs f0, float_1_8041e574(r2)
		opword 0x38610200
		lfs f2, float_0_8041e53c(r2)
		opword 0xEC20E828
		opword 0xFC601090
		bl PSMTXTrans
		opword 0x388102C0
		opword 0x38610200
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x7F64DB78
		opword 0x7FA5EB78
		opword 0x386102C0
		bl GXLoadTexMtxImm
		opword 0x480003EC
		lfs f3, float_3p1416_8041e580(r2)
		opword 0xC03F0080
		opword 0xC01F0084
		opword 0xEC430072
		lfs f1, float_180_8041e584(r2)
		opword 0xEC030032
		opword 0x809E0034
		opword 0x807E0038
		opword 0xEFA20824
		opword 0x801E003C
		opword 0x9081004C
		opword 0x90610050
		opword 0x90010054
		opword 0xEFC00824
		opword 0xFC20E890
		bl sin
		opword 0xFFE00818
		opword 0xFC20F090
		bl cos
		opword 0xFC000818
		opword 0xFC20F090
		opword 0xEC0007F2
		opword 0xD0010070
		bl sin
		opword 0xFC000818
		opword 0xFC20E890
		opword 0xD0010074
		bl cos
		opword 0xFFE00818
		opword 0xFC20F090
		bl cos
		opword 0xFC000818
		opword 0x38810070
		opword 0x807F0070
		opword 0x7C852378
		opword 0xEC0007F2
		opword 0xD0010078
		bl PSMTXMultVecSR
		opword 0x38610070
		opword 0x3881004C
		bl PSVECDotProduct
		opword 0xFFE00890
		lfs f0, float_neg1_8041e58c(r2)
		opword 0xFC00F800
		opword 0x4082002C
		lfs f1, float_0_8041e53c(r2)
		opword 0x386102C0
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x7F64DB78
		opword 0x386102C0
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x48000310
		opword 0x38610070
		opword 0x3881004C
		opword 0x38A10064
		bl C_VECHalfAngle
		opword 0xC0410064
		opword 0x388101D0
		opword 0xC0210068
		opword 0xC001006C
		opword 0xFC401050
		opword 0xFC200850
		opword 0x807F0078
		opword 0xFC000050
		opword 0xD0410064
		opword 0xD0210068
		opword 0xD001006C
		bl PSMTXInvXpose
		opword 0x386101D0
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0x386101E0
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0x386101F0
		opword 0x7C641B78
		bl PSVECNormalize
		lfs f0, float_1_8041e574(r2)
		opword 0xFC00F800
		opword 0x40820010
		opword 0x386101A0
		bl PSMTXIdentity
		opword 0x48000034
		opword 0x38610064
		opword 0x3881004C
		opword 0x38A10058
		bl PSVECCrossProduct
		opword 0x3861004C
		opword 0x38810064
		bl PSVECDotProduct
		bl acos
		opword 0xFC200818
		opword 0x386101A0
		opword 0x38810058
		bl PSMTXRotAxisRad
		opword 0x386101A0
		opword 0x388101D0
		opword 0x38A102C0
		bl PSMTXConcat
		lfs f1, float_2_8041e590(r2)
		opword 0x386101A0
		opword 0xC01F007C
		lfs f3, float_1_8041e574(r2)
		opword 0xEC210032
		opword 0xFC400890
		bl PSMTXScale
		opword 0x388102C0
		opword 0x386101A0
		opword 0x7C852378
		bl PSMTXConcat
		lfs f1, float_0p5_8041e538(r2)
		opword 0x386101A0
		lfs f3, float_0_8041e53c(r2)
		opword 0xFC400890
		bl PSMTXTrans
		opword 0x388102C0
		opword 0x386101A0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x7F64DB78
		opword 0x7FA5EB78
		opword 0x386102C0
		bl GXLoadTexMtxImm
		opword 0x480001F0
		opword 0x807F0078
		opword 0x388102C0
		bl PSMTXInvXpose
		opword 0x386102C0
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0x386102D0
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0x386102E0
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0x7F64DB78
		opword 0x386102C0
		opword 0x38A00001
		bl GXLoadTexMtxImm
		lfs f1, float_0p5_8041e538(r2)
		opword 0x38610170
		lfs f3, float_0_8041e53c(r2)
		opword 0xFC400890
		bl PSMTXScale
		lfs f1, float_0p5_8041e538(r2)
		opword 0x386102C0
		lfs f3, float_1_8041e574(r2)
		opword 0xFC400890
		bl PSMTXTrans
		opword 0x386102C0
		opword 0x38810170
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x7F84E378
		opword 0x7FA5EB78
		opword 0x386102C0
		bl GXLoadTexMtxImm
		opword 0x48000164
		lfs f1, g5_a_s655(r13)
		lfs f0, float_0p0001_8041e594(r2)
		opword 0x809E0040
		opword 0xEC21002A
		opword 0x807E0044
		opword 0x801E0048
		opword 0x9081001C
		stfs f1, g5_a_s655(r13)
		opword 0x90610020
		opword 0x90010024
		bl sin
		opword 0xFC400818
		lfs f0, float_10_8041e524(r2)
		lfs f1, g5_a_s655(r13)
		opword 0xEC0000B2
		opword 0xD001001C
		bl cos
		opword 0xFC200818
		lfs f0, float_10_8041e524(r2)
		opword 0x80E1001C
		opword 0x80C10020
		opword 0xEC000072
		opword 0x809E004C
		opword 0x807E0050
		opword 0x801E0054
		opword 0xD0010024
		lfs f1, g5_a_s655(r13)
		opword 0x80A10024
		opword 0x90E10040
		opword 0x90C10044
		opword 0x90A10048
		opword 0x90810010
		opword 0x90610014
		opword 0x90010018
		bl sin
		opword 0xFC400818
		lfs f0, float_10_8041e524(r2)
		lfs f1, g5_a_s655(r13)
		opword 0xEC0000B2
		opword 0xD0010010
		bl cos
		opword 0xFC200818
		lfs f0, float_10_8041e524(r2)
		opword 0x81610010
		opword 0x386100A0
		opword 0x81410014
		opword 0x38810040
		opword 0xEC000072
		opword 0x811E0058
		opword 0x80FE005C
		opword 0x38A10028
		opword 0x801E0060
		opword 0x38C10034
		opword 0xD0010018
		opword 0x81210018
		opword 0x91610034
		opword 0x91410038
		opword 0x9121003C
		opword 0x91010028
		opword 0x90E1002C
		opword 0x90010030
		bl C_MTXLookAt
		lfs f6, float_0p5_8041e538(r2)
		opword 0x38610130
		lfs f1, float_neg32_8041e598(r2)
		lfs f2, float_32_8041e59c(r2)
		opword 0xFCE03090
		opword 0xFC600890
		opword 0xD0C10008
		opword 0xFC801090
		lfs f5, float_300_8041e5a0(r2)
		opword 0xFD003090
		bl C_MTXLightFrustum
		opword 0x807F0070
		opword 0x38810100
		bl PSMTXInverse
		opword 0x386100A0
		opword 0x38810100
		opword 0x38A100D0
		bl PSMTXConcat
		opword 0x38610130
		opword 0x388100D0
		opword 0x38A102C0
		bl PSMTXConcat
		opword 0x7F84E378
		opword 0x7FA5EB78
		opword 0x386102C0
		bl GXLoadTexMtxImm
	}
}
#pragma pop
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
      ((EnvTexMtxWork *) wp->unk70)->rotY = EXT_LIT(float_10_8041e524, 10.0f);
      ((EnvTexMtxWork *) wp->unk70)->rotX = gp->retraceCount + 45;
      ((EnvTexMtxWork *) wp->unk70)->scale = EXT_LIT(float_0p5_8041e538, 0.5f);
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
      ((EnvTexMtxWork *) wp->unk70)->rotY = EXT_LIT(float_10_8041e524, 10.0f);
      ((EnvTexMtxWork *) wp->unk70)->rotX = gp->retraceCount + 45;
      ((EnvTexMtxWork *) wp->unk70)->scale = EXT_LIT(float_0p5_8041e538, 0.5f);
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
      ((EnvTexMtxWork *) wp->unk70)->scale = EXT_LIT(float_0p5_8041e538, 0.5f);
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
      ((EnvTexMtxWork *) wp->unk70)->scale = (0, EXT_LIT(float_0p5_8041e538, 0.5f));
      ((EnvTexMtxWork *) wp->unk70)->rotY = EXT_LIT(float_45_8041e560, 45.0f);
      ((EnvTexMtxWork *) wp->unk70)->rotX = EXT_LIT(float_45_8041e560, 45.0f);
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
      ((EnvTexMtxWork *) wp->unk70)->scale = EXT_LIT(float_0p5_8041e538, 0.5f);
      ((EnvTexMtxWork *) wp->unk70)->rotY = EXT_LIT(float_45_8041e560, 45.0f);
      ((EnvTexMtxWork *) wp->unk70)->rotX = EXT_LIT(float_45_8041e560, 45.0f);
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
      ((EnvTexMtxWork *) wp->unk70)->scale = EXT_LIT(float_0p15_8041e564, 0.15f);
      ((EnvTexMtxWork *) wp->unk70)->rotY = EXT_LIT(float_0_8041e53c, 0.0f);
      ((EnvTexMtxWork *) wp->unk70)->rotX = EXT_LIT(float_90_8041e568, 90.0f);
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
      ((EnvTexMtxWork *) wp->unk70)->scale = EXT_LIT(float_0p3_8041e56c, 0.3f);
      ((EnvTexMtxWork *) wp->unk70)->rotY = EXT_LIT(float_0_8041e53c, 0.0f);
      ((EnvTexMtxWork *) wp->unk70)->rotX = EXT_LIT(float_90_8041e568, 90.0f);
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
      ((EnvTexMtxWork *) wp->unk70)->scale = EXT_LIT(float_0p5_8041e538, 0.5f);
      ((EnvTexMtxWork *) wp->unk70)->rotY = EXT_LIT(float_10_8041e524, 10.0f);
      ((EnvTexMtxWork *) wp->unk70)->rotX = EXT_LIT(float_45_8041e560, 45.0f);
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void envAddTev(s32 type, MapTevCallbackInfo *info) {
	char _af_pad[468];
	asm {
		lis r5, work@ha
	}
	asm volatile {
		addi r31, r5, work@l
		opword 0x7C791B78
		opword 0x7C9A2378
		lwz r6, gp(r13)
		opword 0x80060014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3BFF00F0
		opword 0x2C190000
		opword 0x83DA000C
		opword 0x83BA0010
		opword 0x839A0014
		opword 0x837A0018
		opword 0x418215E8
		bl camGetCurPtr
		opword 0x809A0004
		la r5, _af_pad+408
		opword 0x3863011C
		bl PSMTXConcat
		bl camGetCurPtr
		opword 0x3863011C
		opword 0x380101A0
		opword 0x907F0070
		opword 0x7FC3F378
		opword 0x7F84E378
		opword 0x7FA5EB78
		opword 0x80FA0004
		opword 0x38C000FF
		opword 0x90FF0074
		opword 0x901F0078
		bl GXSetTevOrder
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x2819000A
		opword 0x41811544
		lis r3, jumptable_80398CF0@ha
		opword 0x5720103A
		addi r3, r3, jumptable_80398CF0@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x7FC3F378
		opword 0x3880000F
		opword 0x38A00000
		opword 0x38C00008
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7FC3F378
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		lfs f0, float_10_8041e524(r2)
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x3C004330
		lwz r5, gp(r13)
		opword 0xD01F0080
		opword 0x38800006
		lfd f2, double_to_int_mask_802f93a8@l(r3)
		opword 0x8065001C
		opword 0x900101D0
		opword 0x3803002D
		lfs f0, float_0p5_8041e538(r2)
		opword 0x900101D4
		lwz r3, env_tpl(r13)
		opword 0xC82101D0
		opword 0xEC211028
		opword 0xD03F0084
		opword 0xD01F007C
		bl TEXGet
		opword 0x80030004
		opword 0x28000000
		opword 0x418200F4
		lwz r3, env_tpl(r13)
		opword 0x38800006
		bl TEXGet
		opword 0x7C791B78
		opword 0x80830000
		opword 0x88640021
		opword 0x88040022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x3BE00000
		opword 0x48000008
		opword 0x3BE00001
		opword 0x80D90004
		opword 0x38610074
		opword 0x80860008
		opword 0x80A60004
		opword 0xA0C60000
		bl GXInitTlutObj
		opword 0x80F90000
		opword 0x38000000
		opword 0x7FEAFB78
		opword 0x38610180
		opword 0x90010008
		opword 0x39000000
		opword 0x39200000
		opword 0x80870008
		opword 0xA0A70002
		opword 0xA0C70000
		opword 0x80E70004
		bl GXInitTexObjCI
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D0
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x38610180
		opword 0x90C101D4
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D0
		opword 0x900101DC
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D8
		opword 0x80A70018
		opword 0xC80101D8
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x38610074
		opword 0x38800000
		bl GXLoadTlut
		opword 0x7FA4EB78
		opword 0x38610180
		bl GXLoadTexObj
		opword 0x480000BC
		lwz r3, env_tpl(r13)
		opword 0x38800006
		bl TEXGet
		opword 0x7C791B78
		opword 0x80E30000
		opword 0x88670021
		opword 0x88070022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x39400000
		opword 0x48000008
		opword 0x39400001
		opword 0x80870008
		opword 0x38610180
		opword 0xA0A70002
		opword 0x39000000
		opword 0xA0C70000
		opword 0x39200000
		opword 0x80E70004
		bl GXInitTexObj
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x38610180
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x7FA4EB78
		opword 0x38610180
		bl GXLoadTexObj
		lis r3, dat_802f9338@ha
		opword 0x57BF103A
		addi r25, r3, dat_802f9338@l
		opword 0x7F83E378
		opword 0x7CD9F82E
		opword 0x38800001
		opword 0x38A00001
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7C99F82E
		opword 0x38600000
		opword 0x38A00040
		opword 0x38C00001
		bl envTevLoadTexMtxImm
		opword 0x3BDE0001
		opword 0x3B9C0001
		opword 0x3BBD0001
		opword 0x480012B4
		opword 0x7FC3F378
		opword 0x3880000F
		opword 0x38A00000
		opword 0x38C00008
		opword 0x38E00009
		bl GXSetTevColorIn
		opword 0x7FC3F378
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		lfs f0, float_10_8041e524(r2)
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x3C004330
		lwz r5, gp(r13)
		opword 0xD01F0080
		opword 0x38800008
		lfd f2, double_to_int_mask_802f93a8@l(r3)
		opword 0x8065001C
		opword 0x900101D8
		opword 0x3803002D
		lfs f0, float_0p5_8041e538(r2)
		opword 0x900101DC
		lwz r3, env_tpl(r13)
		opword 0xC82101D8
		opword 0xEC211028
		opword 0xD03F0084
		opword 0xD01F007C
		bl TEXGet
		opword 0x80030004
		opword 0x28000000
		opword 0x418200F4
		lwz r3, env_tpl(r13)
		opword 0x38800008
		bl TEXGet
		opword 0x7C791B78
		opword 0x80830000
		opword 0x88640021
		opword 0x88040022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x3BE00000
		opword 0x48000008
		opword 0x3BE00001
		opword 0x80D90004
		opword 0x38610068
		opword 0x80860008
		opword 0x80A60004
		opword 0xA0C60000
		bl GXInitTlutObj
		opword 0x80F90000
		opword 0x38000000
		opword 0x7FEAFB78
		opword 0x38610160
		opword 0x90010008
		opword 0x39000000
		opword 0x39200000
		opword 0x80870008
		opword 0xA0A70002
		opword 0xA0C70000
		opword 0x80E70004
		bl GXInitTexObjCI
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x38610160
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x38610068
		opword 0x38800000
		bl GXLoadTlut
		opword 0x7FA4EB78
		opword 0x38610160
		bl GXLoadTexObj
		opword 0x480000BC
		lwz r3, env_tpl(r13)
		opword 0x38800008
		bl TEXGet
		opword 0x7C791B78
		opword 0x80E30000
		opword 0x88670021
		opword 0x88070022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x39400000
		opword 0x48000008
		opword 0x39400001
		opword 0x80870008
		opword 0x38610160
		opword 0xA0A70002
		opword 0x39000000
		opword 0xA0C70000
		opword 0x39200000
		opword 0x80E70004
		bl GXInitTexObj
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x38610160
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x7FA4EB78
		opword 0x38610160
		bl GXLoadTexObj
		lis r3, dat_802f9338@ha
		opword 0x57BF103A
		addi r25, r3, dat_802f9338@l
		opword 0x7F83E378
		opword 0x7CD9F82E
		opword 0x38800001
		opword 0x38A00001
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7C99F82E
		opword 0x38600000
		opword 0x38A00040
		opword 0x38C00001
		bl envTevLoadTexMtxImm
		opword 0x3BDE0001
		opword 0x3B9C0001
		opword 0x3BBD0001
		opword 0x4800103C
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x38A0000F
		opword 0x38C00008
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7FC3F378
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		lfs f0, float_0p5_8041e538(r2)
		opword 0x38800000
		lwz r3, env_tpl(r13)
		opword 0xD01F007C
		bl TEXGet
		opword 0x80030004
		opword 0x28000000
		opword 0x418200F4
		lwz r3, env_tpl(r13)
		opword 0x38800000
		bl TEXGet
		opword 0x7C791B78
		opword 0x80830000
		opword 0x88640021
		opword 0x88040022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x3BE00000
		opword 0x48000008
		opword 0x3BE00001
		opword 0x80D90004
		opword 0x3861005C
		opword 0x80860008
		opword 0x80A60004
		opword 0xA0C60000
		bl GXInitTlutObj
		opword 0x80F90000
		opword 0x38000000
		opword 0x7FEAFB78
		opword 0x38610140
		opword 0x90010008
		opword 0x39000000
		opword 0x39200000
		opword 0x80870008
		opword 0xA0A70002
		opword 0xA0C70000
		opword 0x80E70004
		bl GXInitTexObjCI
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x38610140
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x3861005C
		opword 0x38800000
		bl GXLoadTlut
		opword 0x7FA4EB78
		opword 0x38610140
		bl GXLoadTexObj
		opword 0x480000BC
		lwz r3, env_tpl(r13)
		opword 0x38800000
		bl TEXGet
		opword 0x7C791B78
		opword 0x80E30000
		opword 0x88670021
		opword 0x88070022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x39400000
		opword 0x48000008
		opword 0x39400001
		opword 0x80870008
		opword 0x38610140
		opword 0xA0A70002
		opword 0x39000000
		opword 0xA0C70000
		opword 0x39200000
		opword 0x80E70004
		bl GXInitTexObj
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x38610140
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x7FA4EB78
		opword 0x38610140
		bl GXLoadTexObj
		lis r3, dat_802f9338@ha
		opword 0x57BF103A
		addi r25, r3, dat_802f9338@l
		opword 0x7F83E378
		opword 0x7CD9F82E
		opword 0x38800001
		opword 0x38A00001
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7C99F82E
		opword 0x38600001
		opword 0x38A00040
		opword 0x38C00001
		bl envTevLoadTexMtxImm
		opword 0x3BDE0001
		opword 0x3BBD0001
		opword 0x3B9C0001
		opword 0x48000DF8
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x7FC3F378
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		lfs f1, float_0p5_8041e538(r2)
		opword 0x38800001
		lfs f0, float_45_8041e560(r2)
		opword 0xD03F007C
		lwz r3, env_tpl(r13)
		opword 0xD01F0080
		opword 0xD01F0084
		bl TEXGet
		opword 0x80030004
		opword 0x28000000
		opword 0x418200F4
		lwz r3, env_tpl(r13)
		opword 0x38800001
		bl TEXGet
		opword 0x7C791B78
		opword 0x80830000
		opword 0x88640021
		opword 0x88040022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x3BE00000
		opword 0x48000008
		opword 0x3BE00001
		opword 0x80D90004
		opword 0x38610050
		opword 0x80860008
		opword 0x80A60004
		opword 0xA0C60000
		bl GXInitTlutObj
		opword 0x80F90000
		opword 0x38000000
		opword 0x7FEAFB78
		opword 0x38610120
		opword 0x90010008
		opword 0x39000000
		opword 0x39200000
		opword 0x80870008
		opword 0xA0A70002
		opword 0xA0C70000
		opword 0x80E70004
		bl GXInitTexObjCI
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x38610120
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x38610050
		opword 0x38800000
		bl GXLoadTlut
		opword 0x7FA4EB78
		opword 0x38610120
		bl GXLoadTexObj
		opword 0x480000BC
		lwz r3, env_tpl(r13)
		opword 0x38800001
		bl TEXGet
		opword 0x7C791B78
		opword 0x80E30000
		opword 0x88670021
		opword 0x88070022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x39400000
		opword 0x48000008
		opword 0x39400001
		opword 0x80870008
		opword 0x38610120
		opword 0xA0A70002
		opword 0x39000000
		opword 0xA0C70000
		opword 0x39200000
		opword 0x80E70004
		bl GXInitTexObj
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x38610120
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x7FA4EB78
		opword 0x38610120
		bl GXLoadTexObj
		lis r3, dat_802f9338@ha
		opword 0x57BF103A
		addi r25, r3, dat_802f9338@l
		opword 0x7F83E378
		opword 0x7CD9F82E
		opword 0x38800001
		opword 0x38A00001
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7C99F82E
		opword 0x38600002
		opword 0x38A00040
		opword 0x38C00001
		bl envTevLoadTexMtxImm
		opword 0x3BDE0001
		opword 0x3BBD0001
		opword 0x3B9C0001
		opword 0x48000BA8
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x7FC3F378
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		lfs f1, float_0p5_8041e538(r2)
		opword 0x38800002
		lfs f0, float_45_8041e560(r2)
		opword 0xD03F007C
		lwz r3, env_tpl(r13)
		opword 0xD01F0080
		opword 0xD01F0084
		bl TEXGet
		opword 0x80030004
		opword 0x28000000
		opword 0x418200F4
		lwz r3, env_tpl(r13)
		opword 0x38800002
		bl TEXGet
		opword 0x7C791B78
		opword 0x80830000
		opword 0x88640021
		opword 0x88040022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x3BE00000
		opword 0x48000008
		opword 0x3BE00001
		opword 0x80D90004
		opword 0x38610044
		opword 0x80860008
		opword 0x80A60004
		opword 0xA0C60000
		bl GXInitTlutObj
		opword 0x80F90000
		opword 0x38000000
		opword 0x7FEAFB78
		opword 0x38610100
		opword 0x90010008
		opword 0x39000000
		opword 0x39200000
		opword 0x80870008
		opword 0xA0A70002
		opword 0xA0C70000
		opword 0x80E70004
		bl GXInitTexObjCI
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x38610100
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x38610044
		opword 0x38800000
		bl GXLoadTlut
		opword 0x7FA4EB78
		opword 0x38610100
		bl GXLoadTexObj
		opword 0x480000BC
		lwz r3, env_tpl(r13)
		opword 0x38800002
		bl TEXGet
		opword 0x7C791B78
		opword 0x80E30000
		opword 0x88670021
		opword 0x88070022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x39400000
		opword 0x48000008
		opword 0x39400001
		opword 0x80870008
		opword 0x38610100
		opword 0xA0A70002
		opword 0x39000000
		opword 0xA0C70000
		opword 0x39200000
		opword 0x80E70004
		bl GXInitTexObj
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x38610100
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x7FA4EB78
		opword 0x38610100
		bl GXLoadTexObj
		lis r3, dat_802f9338@ha
		opword 0x57BF103A
		addi r25, r3, dat_802f9338@l
		opword 0x7F83E378
		opword 0x7CD9F82E
		opword 0x38800001
		opword 0x38A00001
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7C99F82E
		opword 0x38600003
		opword 0x38A00040
		opword 0x38C00001
		bl envTevLoadTexMtxImm
		opword 0x3BDE0001
		opword 0x3BBD0001
		opword 0x3B9C0001
		opword 0x48000958
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x7FC3F378
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		lfs f0, float_0p15_8041e564(r2)
		opword 0x38800004
		lfs f1, float_0_8041e53c(r2)
		opword 0xD01F007C
		lfs f0, float_90_8041e568(r2)
		opword 0xD03F0080
		lwz r3, env_tpl(r13)
		opword 0xD01F0084
		bl TEXGet
		opword 0x80030004
		opword 0x28000000
		opword 0x418200F4
		lwz r3, env_tpl(r13)
		opword 0x38800004
		bl TEXGet
		opword 0x7C791B78
		opword 0x80830000
		opword 0x88640021
		opword 0x88040022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x3BE00000
		opword 0x48000008
		opword 0x3BE00001
		opword 0x80D90004
		opword 0x38610038
		opword 0x80860008
		opword 0x80A60004
		opword 0xA0C60000
		bl GXInitTlutObj
		opword 0x80F90000
		opword 0x38000000
		opword 0x7FEAFB78
		opword 0x386100E0
		opword 0x90010008
		opword 0x39000000
		opword 0x39200000
		opword 0x80870008
		opword 0xA0A70002
		opword 0xA0C70000
		opword 0x80E70004
		bl GXInitTexObjCI
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x386100E0
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x38610038
		opword 0x38800000
		bl GXLoadTlut
		opword 0x7FA4EB78
		opword 0x386100E0
		bl GXLoadTexObj
		opword 0x480000BC
		lwz r3, env_tpl(r13)
		opword 0x38800004
		bl TEXGet
		opword 0x7C791B78
		opword 0x80E30000
		opword 0x88670021
		opword 0x88070022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x39400000
		opword 0x48000008
		opword 0x39400001
		opword 0x80870008
		opword 0x386100E0
		opword 0xA0A70002
		opword 0x39000000
		opword 0xA0C70000
		opword 0x39200000
		opword 0x80E70004
		bl GXInitTexObj
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x386100E0
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x7FA4EB78
		opword 0x386100E0
		bl GXLoadTexObj
		lis r3, dat_802f9338@ha
		opword 0x57BF103A
		addi r25, r3, dat_802f9338@l
		opword 0x7F83E378
		opword 0x7CD9F82E
		opword 0x38800001
		opword 0x38A00001
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7C99F82E
		opword 0x38600002
		opword 0x38A00040
		opword 0x38C00001
		bl envTevLoadTexMtxImm
		opword 0x3BDE0001
		opword 0x3BBD0001
		opword 0x3B9C0001
		opword 0x48000704
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x7FC3F378
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		lfs f0, float_0p3_8041e56c(r2)
		opword 0x38800005
		lfs f1, float_0_8041e53c(r2)
		opword 0xD01F007C
		lfs f0, float_90_8041e568(r2)
		opword 0xD03F0080
		lwz r3, env_tpl(r13)
		opword 0xD01F0084
		bl TEXGet
		opword 0x80030004
		opword 0x28000000
		opword 0x418200F4
		lwz r3, env_tpl(r13)
		opword 0x38800005
		bl TEXGet
		opword 0x7C791B78
		opword 0x80830000
		opword 0x88640021
		opword 0x88040022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x3BE00000
		opword 0x48000008
		opword 0x3BE00001
		opword 0x80D90004
		opword 0x3861002C
		opword 0x80860008
		opword 0x80A60004
		opword 0xA0C60000
		bl GXInitTlutObj
		opword 0x80F90000
		opword 0x38000000
		opword 0x7FEAFB78
		opword 0x386100C0
		opword 0x90010008
		opword 0x39000000
		opword 0x39200000
		opword 0x80870008
		opword 0xA0A70002
		opword 0xA0C70000
		opword 0x80E70004
		bl GXInitTexObjCI
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x386100C0
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x3861002C
		opword 0x38800000
		bl GXLoadTlut
		opword 0x7FA4EB78
		opword 0x386100C0
		bl GXLoadTexObj
		opword 0x480000BC
		lwz r3, env_tpl(r13)
		opword 0x38800005
		bl TEXGet
		opword 0x7C791B78
		opword 0x80E30000
		opword 0x88670021
		opword 0x88070022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x39400000
		opword 0x48000008
		opword 0x39400001
		opword 0x80870008
		opword 0x386100C0
		opword 0xA0A70002
		opword 0x39000000
		opword 0xA0C70000
		opword 0x39200000
		opword 0x80E70004
		bl GXInitTexObj
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x386100C0
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x7FA4EB78
		opword 0x386100C0
		bl GXLoadTexObj
		lis r3, dat_802f9338@ha
		opword 0x57BF103A
		addi r25, r3, dat_802f9338@l
		opword 0x7F83E378
		opword 0x7CD9F82E
		opword 0x38800001
		opword 0x38A00001
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7C99F82E
		opword 0x38600003
		opword 0x38A00040
		opword 0x38C00001
		bl envTevLoadTexMtxImm
		opword 0x3BDE0001
		opword 0x3BBD0001
		opword 0x3B9C0001
		opword 0x480004B0
		opword 0x7FC3F378
		opword 0x3880000F
		opword 0x38A00000
		opword 0x38C00008
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7FC3F378
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		lfs f0, float_0p5_8041e538(r2)
		opword 0x3880000A
		lfs f1, float_10_8041e524(r2)
		opword 0xD01F007C
		lfs f0, float_45_8041e560(r2)
		opword 0xD03F0080
		lwz r3, env_tpl(r13)
		opword 0xD01F0084
		bl TEXGet
		opword 0x80030004
		opword 0x28000000
		opword 0x418200F4
		lwz r3, env_tpl(r13)
		opword 0x3880000A
		bl TEXGet
		opword 0x7C791B78
		opword 0x80830000
		opword 0x88640021
		opword 0x88040022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x3BE00000
		opword 0x48000008
		opword 0x3BE00001
		opword 0x80D90004
		opword 0x38610020
		opword 0x80860008
		opword 0x80A60004
		opword 0xA0C60000
		bl GXInitTlutObj
		opword 0x80F90000
		opword 0x38000000
		opword 0x7FEAFB78
		opword 0x386100A0
		opword 0x90010008
		opword 0x39000000
		opword 0x39200000
		opword 0x80870008
		opword 0xA0A70002
		opword 0xA0C70000
		opword 0x80E70004
		bl GXInitTexObjCI
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x386100A0
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x38610020
		opword 0x38800000
		bl GXLoadTlut
		opword 0x7FA4EB78
		opword 0x386100A0
		bl GXLoadTexObj
		opword 0x480000BC
		lwz r3, env_tpl(r13)
		opword 0x3880000A
		bl TEXGet
		opword 0x7C791B78
		opword 0x80E30000
		opword 0x88670021
		opword 0x88070022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x39400000
		opword 0x48000008
		opword 0x39400001
		opword 0x80870008
		opword 0x386100A0
		opword 0xA0A70002
		opword 0x39000000
		opword 0xA0C70000
		opword 0x39200000
		opword 0x80E70004
		bl GXInitTexObj
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x386100A0
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x7FA4EB78
		opword 0x386100A0
		bl GXLoadTexObj
		lis r3, dat_802f9338@ha
		opword 0x57BF103A
		addi r25, r3, dat_802f9338@l
		opword 0x7F83E378
		opword 0x7CD9F82E
		opword 0x38800001
		opword 0x38A00001
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7C99F82E
		opword 0x38600000
		opword 0x38A00040
		opword 0x38C00001
		bl envTevLoadTexMtxImm
		opword 0x3BDE0001
		opword 0x3BBD0001
		opword 0x3B9C0001
		opword 0x4800025C
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x38A00008
		opword 0x38C0000E
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7FC3F378
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		opword 0x7FC3F378
		opword 0x3880000D
		bl GXSetTevKColorSel
		lwz r0, dat_8041e51c(r2)
		opword 0x38810010
		opword 0x38600001
		opword 0x90010010
		bl GXSetTevKColor
		lwz r3, env_tpl(r13)
		opword 0x38800009
		bl TEXGet
		opword 0x80030004
		opword 0x28000000
		opword 0x418200F4
		lwz r3, env_tpl(r13)
		opword 0x38800009
		bl TEXGet
		opword 0x7C791B78
		opword 0x80830000
		opword 0x88640021
		opword 0x88040022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x3BE00000
		opword 0x48000008
		opword 0x3BE00001
		opword 0x80D90004
		opword 0x38610014
		opword 0x80860008
		opword 0x80A60004
		opword 0xA0C60000
		bl GXInitTlutObj
		opword 0x80F90000
		opword 0x38000000
		opword 0x7FEAFB78
		opword 0x38610080
		opword 0x90010008
		opword 0x39000000
		opword 0x39200000
		opword 0x80870008
		opword 0xA0A70002
		opword 0xA0C70000
		opword 0x80E70004
		bl GXInitTexObjCI
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x38610080
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x38610014
		opword 0x38800000
		bl GXLoadTlut
		opword 0x7FA4EB78
		opword 0x38610080
		bl GXLoadTexObj
		opword 0x480000BC
		lwz r3, env_tpl(r13)
		opword 0x38800009
		bl TEXGet
		opword 0x7C791B78
		opword 0x80E30000
		opword 0x88670021
		opword 0x88070022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x39400000
		opword 0x48000008
		opword 0x39400001
		opword 0x80870008
		opword 0x38610080
		opword 0xA0A70002
		opword 0x39000000
		opword 0xA0C70000
		opword 0x39200000
		opword 0x80E70004
		bl GXInitTexObj
		opword 0x80F90000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0x90A101D8
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802f93a8@l
		opword 0x88070022
		opword 0x38610080
		opword 0x90C101DC
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC80101D8
		opword 0x900101D4
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A101D0
		opword 0x80A70018
		opword 0xC80101D0
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x7FA4EB78
		opword 0x38610080
		bl GXLoadTexObj
		lis r3, dat_802f9338@ha
		opword 0x57B9103A
		addi r31, r3, dat_802f9338@l
		opword 0x7F83E378
		opword 0x7CDFC82E
		opword 0x38800000
		opword 0x38A00001
		opword 0x38E00000
		opword 0x39000040
		bl GXSetTexCoordGen2
		opword 0x7C9FC82E
		opword 0x38600004
		opword 0x38A00040
		opword 0x38C00000
		bl envTevLoadTexMtxImm
		opword 0x3BDE0001
		opword 0x3BBD0001
		opword 0x3B9C0001
		opword 0x93DA000C
		opword 0x939A0014
		opword 0x937A0018
		opword 0x93BA0010
	}
}
#pragma pop
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
    GXInitTexObjLOD(&obj1, GX_NEAR, GX_NEAR, EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f), GX_FALSE, GX_FALSE, GX_ANISO_1);
    PSMTXMultVec(info->mtx, &(*(MapObject**)info->field_0x0)->center, &pos);
    scale = EXT_LIT(float_1000_8041e540, 1000.0f) / PSVECDistance(&camGetCurPtr()->cameraPos, &pos);
    if (scale < EXT_LIT(float_0_8041e53c, 0.0f)) {
        scale = 0.0f;
    }
    if (scale > EXT_LIT(float_127_8041e544, 127.0f)) {
        scale = 127.0f;
    }
    buf2 = smartAlloc(GXGetTexBufferSize(64, 64, GX_TF_IA8, GX_FALSE, 0), 3)->address;
    for (i = 0; i < 64; i++) {
        for (j = 0; j < 64; j++) {
            f32 s = sin((f32)gp->retraceCount / 10.0f + (18.849552f * j) / 64.0f);
            u8* p = buf2 + ((i / 4) * 32 + (j / 4) * 512) + ((i % 4) + (j % 4) * 4) * 2;
            p[0] = EXT_LIT(float_0p6_8041e550, 0.6f) + (scale * s + EXT_LIT(float_128_8041e554, 128.0f));
            p[1] = 0x80;
        }
    }
    DCFlushRange(buf2, 0x2000);
    GXInitTexObj(&obj2, buf2, 64, 64, GX_TF_IA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(&obj2, GX_LINEAR, GX_LINEAR, EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f), EXT_LIT(float_0_8041e53c, 0.0f), GX_FALSE, GX_FALSE, GX_ANISO_1);
    t = tan(EXT_LIT(float_6p2832_8041e558, 6.2831855f) * (camGetPtr(4)->fovY / EXT_LIT(float_2_8041e590, 2.0f)) / EXT_LIT(float_360_8041e55c, 360.0f));
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
    indMtx[0][0] = EXT_LIT(float_0p5_8041e538, 0.5f);
    indMtx[0][1] = EXT_LIT(float_0_8041e53c, 0.0f);
    indMtx[0][2] = EXT_LIT(float_0_8041e53c, 0.0f);
    indMtx[1][0] = EXT_LIT(float_0_8041e53c, 0.0f);
    indMtx[1][1] = EXT_LIT(float_0p5_8041e538, 0.5f);
    indMtx[1][2] = EXT_LIT(float_0_8041e53c, 0.0f);
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void envSetWater(MapTevCallbackInfo* info) {
	char _af_pad[196];
	asm volatile {
		mr r17, r3
		opword 0x80630000
		opword 0x8391000C
		opword 0x80830000
		opword 0x83710010
		opword 0x548006B5
		opword 0x83510014
		opword 0x83310018
		opword 0x4182004C
		opword 0x48000038
		opword 0x80830000
		opword 0x548006F7
		opword 0x4182002C
		opword 0x54800085
		opword 0x40820010
		opword 0x64802000
		opword 0x90030000
		opword 0x480005F0
		opword 0xA2A300EC
		opword 0xA28300EE
		opword 0xA26300F0
		opword 0xA24300F2
		opword 0x48000038
		opword 0x806300E0
		opword 0x28030000
		opword 0x4082FFC4
		opword 0x48000028
		opword 0x54800085
		opword 0x40820010
		opword 0x64802000
		opword 0x90030000
		opword 0x480005B8
		opword 0xA2A300EC
		opword 0xA28300EE
		opword 0xA26300F0
		opword 0xA24300F2
		opword 0x2C1503FF
		opword 0x418205A0
		opword 0x2C1403FF
		opword 0x41820598
		opword 0x2C1303FF
		opword 0x41820590
		opword 0x2C1203FF
		opword 0x40820008
		opword 0x48000584
		opword 0x2C150000
		opword 0x4082001C
		opword 0x2C140000
		opword 0x40820014
		opword 0x2C130000
		opword 0x4082000C
		opword 0x2C120000
		opword 0x41820564
		opword 0x56A007FE
		opword 0x568407FE
		opword 0x7EA0A851
		opword 0x566307FE
		opword 0x564007FE
		opword 0x7E84A050
		opword 0x7E731A14
		opword 0x7E520214
		opword 0x40800008
		opword 0x3AA00000
		opword 0x2C140000
		opword 0x40800008
		opword 0x3A800000
		lwz r3, gp(r13)
		opword 0xA0030170
		opword 0x7C130000
		opword 0x40810008
		opword 0x7C130378
		opword 0xA0030172
		opword 0x7C120000
		opword 0x40810008
		opword 0x7C120378
		opword 0x7EF59850
		opword 0x7ED49050
		opword 0x56E00FFE
		opword 0x38A00004
		opword 0x7C60BA14
		opword 0x56C00FFE
		opword 0x7C7D0E70
		opword 0x38C00000
		opword 0x7C00B214
		opword 0x38E00000
		opword 0x7C180E70
		opword 0x57A3043E
		opword 0x5704043E
		bl GXGetTexBufferSize
		opword 0x38800003
		bl smartAlloc
		opword 0x83C30000
		opword 0x56A3043E
		opword 0x5684043E
		opword 0x56E5043E
		opword 0x56C6043E
		bl GXSetTexCopySrc
		opword 0x57A3043E
		opword 0x5704043E
		opword 0x38A00004
		opword 0x38C00001
		bl GXSetTexCopyDst
		opword 0x7FC3F378
		opword 0x38800000
		bl GXCopyTex
		bl GXPixModeSync
		bl GXTexModeSync
		opword 0x7FC4F378
		la r3, _af_pad+76
		opword 0x57A5043E
		opword 0x5706043E
		opword 0x38E00004
		opword 0x39000000
		opword 0x39200000
		opword 0x39400000
		bl GXInitTexObj
		lfs f1, float_0_8041e53c(r2)
		opword 0x38610054
		opword 0x38800000
		opword 0x38A00000
		opword 0xFC400890
		opword 0x38C00000
		opword 0xFC600890
		opword 0x38E00000
		opword 0x39000000
		bl GXInitTexObjLOD
		opword 0x80910000
		opword 0x38A10010
		opword 0x80710004
		opword 0x38840010
		bl PSMTXMultVec
		bl camGetCurPtr
		opword 0x3863000C
		opword 0x38810010
		bl PSVECDistance
		lfs f2, float_1000_8041e540(r2)
		lfs f0, float_0_8041e53c(r2)
		opword 0xEFE20824
		opword 0xFC1F0040
		opword 0x40800008
		opword 0xFFE00090
		lfs f0, float_127_8041e544(r2)
		opword 0xFC1F0040
		opword 0x40810008
		opword 0xFFE00090
		opword 0x38600040
		opword 0x38800040
		opword 0x38A00003
		opword 0x38C00000
		opword 0x38E00000
		bl GXGetTexBufferSize
		opword 0x38800003
		bl smartAlloc
		lis r5, double_to_int_802f93a0@ha
		lis r4, double_to_int_mask_802f93a8@ha
		opword 0x83030000
		opword 0x3AE00000
		lfs f24, float_18p85_8041e548(r2)
		opword 0x3FC04330
		lfd f25, double_to_int_802f93a0@l(r5)
		lfs f26, float_0p015625_8041e54c(r2)
		lfd f27, double_to_int_mask_802f93a8@l(r4)
		lfs f28, float_10_8041e524(r2)
		lfs f29, float_0p6_8041e550(r2)
		lfs f30, float_128_8041e554(r2)
		opword 0x56E0F002
		opword 0x56E30FFE
		opword 0x7EE41670
		opword 0x3AC00000
		opword 0x7C030050
		opword 0x7C840194
		opword 0x5400103E
		opword 0x7FA01A14
		opword 0x549F2834
		lwz r3, gp(r13)
		opword 0x6EC48000
		opword 0x93C100B0
		opword 0x8003001C
		opword 0x908100AC
		opword 0x900100B4
		opword 0xC80100B0
		opword 0x93C100A8
		opword 0xEC00D828
		opword 0xC82100A8
		opword 0xEC00E024
		opword 0xEC21C828
		opword 0xEC380072
		opword 0xEC2106BA
		bl sin
		opword 0xFC000818
		opword 0x7EC01670
		opword 0x7C800194
		opword 0x56C30FFE
		opword 0x56C0F002
		opword 0x3AD60001
		opword 0xEC1FF03A
		opword 0x7C030050
		opword 0x5400103E
		opword 0x5484482C
		opword 0x7C001A14
		opword 0x2C160040
		opword 0xEC1D002A
		opword 0x5400103A
		opword 0x7C1D0214
		opword 0x7C9F2214
		opword 0x5403083C
		opword 0xFC00001E
		opword 0x7C841A14
		opword 0x38000080
		opword 0x7C982214
		opword 0xD80100B8
		opword 0x806100BC
		opword 0x98640000
		opword 0x98040001
		opword 0x4180FF60
		opword 0x3AF70001
		opword 0x2C170040
		opword 0x4180FF30
		opword 0x7F03C378
		opword 0x38802000
		bl DCFlushRange
		opword 0x7F04C378
		opword 0x38610034
		opword 0x38A00040
		opword 0x38C00040
		opword 0x38E00003
		opword 0x39000001
		opword 0x39200001
		opword 0x39400000
		bl GXInitTexObj
		lfs f1, float_0_8041e53c(r2)
		opword 0x38610034
		opword 0x38800001
		opword 0x38A00001
		opword 0xFC400890
		opword 0x38C00000
		opword 0xFC600890
		opword 0x38E00000
		opword 0x39000000
		bl GXInitTexObjLOD
		opword 0x38600004
		bl camGetPtr
		opword 0xC0430038
		lfs f0, float_0p5_8041e538(r2)
		lfs f1, float_6p2832_8041e558(r2)
		opword 0xEC420032
		lfs f0, float_360_8041e55c(r2)
		opword 0xEC2100B2
		opword 0xEC210024
		bl tan
		lwz r4, gp(r13)
		opword 0x3CC04330
		lfs f6, float_0p5_8041e538(r2)
		lis r3, double_to_int_mask_802f93a8@ha
		opword 0xA0A40172
		opword 0xA0040170
		lis r4, double_to_int_802f93a0@ha
		opword 0x90A100CC
		opword 0x54A7FC7E
		addi r8, r4, double_to_int_802f93a0@l
		lfd f2, double_to_int_mask_802f93a8@l(r3)
		opword 0x90C100C8
		opword 0x5400F87E
		opword 0x7C60A850
		opword 0x7CB23850
		opword 0xC80100C8
		opword 0x7C943850
		opword 0x6CA78000
		opword 0x7C009850
		opword 0xEC001028
		opword 0x6C858000
		opword 0xFC400818
		opword 0x6C648000
		opword 0x6C008000
		opword 0x908100AC
		opword 0xEC0001B2
		opword 0x90C100A8
		opword 0xC8880000
		opword 0xFCE03090
		opword 0x90E100BC
		opword 0xFD003090
		opword 0xECA01024
		opword 0x90C100B8
		opword 0xC80100A8
		opword 0x38610074
		opword 0xC82100B8
		opword 0x90A100B4
		opword 0x90C100B0
		opword 0xEC602028
		opword 0xEC212028
		opword 0xC84100B0
		opword 0x900100C4
		opword 0xEC422028
		opword 0x90C100C0
		opword 0xC80100C0
		opword 0xD0C10008
		opword 0xEC802028
		bl C_MTXLightFrustum
		bl camGetCurPtr
		opword 0x7C641B78
		opword 0x38610074
		opword 0x7C651B78
		opword 0x3884011C
		bl PSMTXConcat
		opword 0x38610074
		opword 0x80910004
		opword 0x7C651B78
		bl PSMTXConcat
		lis r3, dat_802f9338@ha
		opword 0x5773103A
		addi r18, r3, dat_802f9338@l
		opword 0x7F43D378
		opword 0x7CD2982E
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7C92982E
		opword 0x38610074
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x7F64DB78
		opword 0x38610054
		bl GXLoadTexObj
		opword 0x38610034
		opword 0x389B0001
		bl GXLoadTexObj
		opword 0x7F83E378
		opword 0x7F44D378
		opword 0x7F65DB78
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F83E378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F83E378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F83E378
		opword 0x38800008
		opword 0x38A00000
		opword 0x38C00001
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7F83E378
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x7F83E378
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		lfs f0, float_0_8041e53c(r2)
		opword 0x3881001C
		lfs f1, float_0p5_8041e538(r2)
		opword 0x38600001
		opword 0xD0010020
		opword 0x38A00001
		opword 0xD021001C
		opword 0xD0010024
		opword 0xD0010028
		opword 0xD021002C
		opword 0xD0010030
		bl GXSetIndTexMtx
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x38BB0001
		bl GXSetIndTexOrder
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetIndTexCoordScale
		opword 0x7F83E378
		opword 0x7F24CB78
		opword 0x38A00001
		opword 0x38C00000
		opword 0x38E00001
		bl GXSetTevIndWarp
		opword 0x3B9C0001
		opword 0x3B5A0001
		opword 0x9391000C
		opword 0x3B390001
		opword 0x3B7B0002
		opword 0x93510014
		opword 0x93310018
		opword 0x93710010
	}
}
#pragma pop
#endif

void envSetYamiView(Mtx view) {
    EnvironmentWork* wp = envGetWork();

    PSMTXCopy(view, (MtxPtr)((u8*)wp + 0xC0));
}

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
        u2 -= EXT_LIT(float_0p004_8041e520, 0.004f);
        v_count = rc;
        if (u1 > EXT_LIT(float_10_8041e524, 10.0f)) {
            u1 -= 10.0f;
        }
        if (u2 < EXT_LIT(float_10_8041e524, 10.0f)) {
            u2 += 10.0f;
        }
    }
    GXSetTevColorOp(stage - 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    GXSetTevAlphaOp(stage - 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    C_MTXLightOrtho(mtx, EXT_LIT(float_72_8041e528, 72.0f), EXT_LIT(float_neg72_8041e52c, -72.0f), EXT_LIT(float_neg96_8041e530, -96.0f), EXT_LIT(float_96_8041e534, 96.0f), EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0p5_8041e538, 0.5f), u1, EXT_LIT(float_0p5_8041e538, 0.5f));
    PSMTXConcat(mtx, (MtxPtr)wp->unkC0, mtx);
    PSMTXConcat(mtx, info->mtx, mtx);
    GXLoadTexMtxImm(mtx, texmtx_tbl[map], GX_MTX3x4);
    GXSetTexCoordGen2(coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
    C_MTXLightOrtho(mtx, EXT_LIT(float_72_8041e528, 72.0f), EXT_LIT(float_neg72_8041e52c, -72.0f), EXT_LIT(float_neg96_8041e530, -96.0f), EXT_LIT(float_96_8041e534, 96.0f), EXT_LIT(float_0p5_8041e538, 0.5f), EXT_LIT(float_0p5_8041e538, 0.5f), u2, EXT_LIT(float_0p5_8041e538, 0.5f));
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void envSetYami(MapTevCallbackInfo* info) {
	char _af_pad[80];
	asm {
		lis r4, work@ha
	}
	asm volatile {
		addi r30, r4, work@l
		mr r24, r3
		lwz r5, gp(r13)
		opword 0x80050014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3BDE00F0
		lwz r0, g5_v_count_s761(r13)
		opword 0x8065001C
		opword 0x8398000C
		opword 0x7C001840
		opword 0x83780010
		opword 0x83580014
		opword 0x83380018
		opword 0x41820050
		lfs f0, g5_u1_s759(r13)
		lfs f3, float_0p004_8041e520(r2)
		lfs f1, g5_u2_s760(r13)
		opword 0xEC40182A
		lfs f0, float_10_8041e524(r2)
		opword 0xEC211828
		stw r3, g5_v_count_s761(r13)
		opword 0xFC020040
		stfs f2, g5_u1_s759(r13)
		stfs f1, g5_u2_s760(r13)
		opword 0x4081000C
		opword 0xEC020028
		stfs f0, g5_u1_s759(r13)
		lfs f1, g5_u2_s760(r13)
		lfs f0, float_10_8041e524(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0xEC01002A
		stfs f0, g5_u2_s760(r13)
		opword 0x387CFFFF
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000001
		bl GXSetTevColorOp
		opword 0x387CFFFF
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000001
		bl GXSetTevAlphaOp
		lfs f5, float_0p5_8041e538(r2)
		la r3, _af_pad+32
		lfs f1, float_72_8041e528(r2)
		opword 0xFCC02890
		lfs f2, float_neg72_8041e52c(r2)
		opword 0xFD002890
		lfs f3, float_neg96_8041e530(r2)
		lfs f4, float_96_8041e534(r2)
		lfs f7, g5_u1_s759(r13)
		bl C_MTXLightOrtho
		opword 0x38610028
		opword 0x389E00C0
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x38610028
		opword 0x80980004
		opword 0x7C651B78
		bl PSMTXConcat
		lis r3, dat_802f9338@ha
		opword 0x577D103A
		addi r31, r3, dat_802f9338@l
		opword 0x38610028
		opword 0x7C9FE82E
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x7CDFE82E
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		lfs f5, float_0p5_8041e538(r2)
		opword 0x38610028
		lfs f1, float_72_8041e528(r2)
		opword 0xFCC02890
		lfs f2, float_neg72_8041e52c(r2)
		opword 0xFD002890
		lfs f3, float_neg96_8041e530(r2)
		lfs f4, float_96_8041e534(r2)
		lfs f7, g5_u2_s760(r13)
		bl C_MTXLightOrtho
		opword 0x38610028
		opword 0x389E00C0
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x38610028
		opword 0x80980004
		opword 0x7C651B78
		bl PSMTXConcat
		lis r4, dat_802f9338@ha
		opword 0x38610028
		addi r0, r4, dat_802f9338@l
		opword 0x38A00000
		opword 0x7FA0EA14
		opword 0x849D0004
		bl GXLoadTexMtxImm
		opword 0x80DD0000
		opword 0x387A0001
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		lwz r3, env_tpl(r13)
		opword 0x38810008
		opword 0x38A00009
		bl TEXGetGXTexObjFromPalette
		opword 0x7F64DB78
		opword 0x38610008
		bl GXLoadTexObj
		lwz r3, env_tpl(r13)
		opword 0x38810008
		opword 0x38A0000A
		bl TEXGetGXTexObjFromPalette
		opword 0x38610008
		opword 0x389B0001
		bl GXLoadTexObj
		opword 0x7F83E378
		opword 0x7F44D378
		opword 0x7F65DB78
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F83E378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F83E378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F83E378
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x7F83E378
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x7F83E378
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x387C0001
		opword 0x389A0001
		opword 0x38BB0001
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x387C0001
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x387C0001
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x387C0001
		opword 0x3880000F
		opword 0x38A00000
		opword 0x38C00009
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x387C0001
		opword 0x38800007
		opword 0x38A00000
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x387C0001
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x387C0002
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x387C0002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x387C0002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x387C0002
		opword 0x38800002
		opword 0x38A0000F
		opword 0x38C00001
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x387C0002
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00001
		bl GXSetTevAlphaIn
		opword 0x387C0002
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B9C0003
		opword 0x3B5A0002
		opword 0x9398000C
		opword 0x3B7B0002
		opword 0x93580014
		opword 0x93380018
		opword 0x93780010
	}
}
#pragma pop
#endif


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_05_80398D1C_data[1] = {0};

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
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
#endif
