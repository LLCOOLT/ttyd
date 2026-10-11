#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "data/mapdata.h"
#include "pmario_sound.h"
#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "sdk/texPalette.h"
#include "manager/fontmgr.h"
#include "driver/msgdrv.h"
#include "memory.h"
#include "string.h"
#include "mario/mariost.h"
#include "manager/filemgr.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "system.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];
double tan(double x);
double fmod(double x, double y);
EffectEntry* effStardustN64Entry(s32 type, f32 x, f32 y, f32 z, f32 size);
void effStardustN64SetDrawCam(EffectEntry* eff, s32 camera);
void display_func(CameraId cameraId, void* param);
EffectEntry* effItemGetEntry(s32 type, f32 x, f32 y, f32 z);
typedef struct SysChar { f32 x; f32 y; f32 z; f32 rot; s32 timer; s32 state; s32 texid; } SysChar;
typedef struct SysWork { s32 state; FileEntry* file; f32 rot; s32 frame; s32 scroll; s32 type; s32 alpha; f32 angle; s32 count; SysChar chars[8]; } SysWork;
SysWork* g_wp;

USER_FUNC(bg);
USER_FUNC(display);
USER_FUNC(evt_bero_get_entername);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_fade_end_wait);
USER_FUNC(evt_fade_entry);
USER_FUNC(evt_fade_set_mapchange_type);
USER_FUNC(evt_key_get_buttontrg);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(init);
USER_FUNC(start);
void display_func(CameraId cameraId, void* param);
s32 getLightColor(f32 angle);
void sys_01_release(void);
static void _unresolved(void);
static void _epilog(void);
void _prolog(void);

__declspec(section ".data") u64 fd_sys_negone_one_374;
__declspec(section ".data") s32 fd_sys_neg_one_382[1];
__declspec(section ".data") s32 fd_sys___local_PI_383[1];
__declspec(section ".data") s32 fd_sys___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_sys_one_negone_373;
__declspec(section ".data") s32 fd_sys___local_PIO2_384[1];
__declspec(section ".data") s32 fd_sys_one_381[1];
__declspec(section ".data") u64 fd_sys_negone_one_360;
__declspec(section ".data") s32 fd_sys_neg_one_365[1];
__declspec(section ".data") s32 fd_sys___local_PI_366[1];
__declspec(section ".data") s32 fd_sys___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_sys_one_negone_359;
__declspec(section ".data") s32 fd_sys___local_PIO2_367[1];
__declspec(section ".data") s32 fd_sys_one_364[1];
__declspec(section ".data") s32 fd_sys__three_localstatic4_sqrtf[2];
__declspec(section ".data") s32 fd_sys__half_localstatic3_sqrtf[2];
__declspec(section ".data") s32 dummy_evt[2];
static __declspec(section ".data") s32 niji_tbl[2];
static __declspec(section ".data") const char* msg_tbl[9];
__declspec(section ".data") s8 prologue_jp_tbl[8];
__declspec(section ".data") s8 stage1_jp_tbl[8];
__declspec(section ".data") s8 stage2_jp_tbl[8];
__declspec(section ".data") s8 stage3_jp_tbl[8];
__declspec(section ".data") s8 stage4_jp_tbl[8];
__declspec(section ".data") s8 stage5_jp_tbl[8];
__declspec(section ".data") s8 stage6_jp_tbl[8];
__declspec(section ".data") s8 stage7_jp_tbl[8];
__declspec(section ".data") s8 stage8_jp_tbl[8];
__declspec(section ".data") s8* texid_jp_tbl[9];
__declspec(section ".data") s8 prologue_us_tbl[12];
__declspec(section ".data") s8 stage1_us_tbl[8];
__declspec(section ".data") s8 stage2_us_tbl[8];
__declspec(section ".data") s8 stage3_us_tbl[8];
__declspec(section ".data") s8 stage4_us_tbl[8];
__declspec(section ".data") s8 stage5_us_tbl[8];
__declspec(section ".data") s8 stage6_us_tbl[8];
__declspec(section ".data") s8 stage7_us_tbl[8];
__declspec(section ".data") s8 stage8_us_tbl[8];
__declspec(section ".data") s8* texid_us_tbl[9];
__declspec(section ".data") s8** lang_tbl[2];
__declspec(section ".data") const char* lang_prefix[2];
s32 sys_01_init_evt[135];
s32 evt_start[189];

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("sys_00", dummy_evt);
    relSetEvtAddr("sys_01", sys_01_init_evt);
    if (evtGetValue(NULL, GSW(0)) != 2 && evtGetValue(NULL, GSW(0)) != 125 && evtGetValue(NULL, GSW(0)) != 229 &&
        evtGetValue(NULL, GSW(0)) != 280) {
        psndStopAllFadeOut();
    }
    camGetPtr(CAMERA_2D)->flags |= 0x200;
    camGetPtr(CAMERA_2D)->flags &= ~0x100;
    camGetPtr(CAMERA_2D)->flags |= 0x400;
}

__declspec(section ".data") u64 fd_sys_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_sys_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_sys___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_sys___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_sys_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_sys___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_sys_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_sys_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_sys_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_sys___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_sys___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_sys_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_sys___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_sys_one_364[] = {
    1065353216,
};

__declspec(section ".data") s32 fd_sys__three_localstatic4_sqrtf[] = {
    1074266112, 0,
};

__declspec(section ".data") s32 fd_sys__half_localstatic3_sqrtf[] = {
    1071644672, 0,
};

__declspec(section ".data") EVT_BEGIN(dummy_evt)
    RETURN
EVT_END()

static __declspec(section ".data") s32 niji_tbl[] = {
    19, 22,
};

static __declspec(section ".data") const char* msg_tbl[] = {
    "msg_stg_seq_prolouge", "msg_stg_seq_stg1", "msg_stg_seq_stg2", "msg_stg_seq_stg3", "msg_stg_seq_stg4", "msg_stg_seq_stg5", "msg_stg_seq_stg6", "msg_stg_seq_stg7",
    "msg_stg_seq_stg8",
};

static void _epilog(void) {
    voidfunctionptr* dtor;

    if (strcmp(gp->currentMapName, "sys_01") == 0) {
        sys_01_release();
    }
    camGetPtr(CAMERA_2D)->flags &= ~0x200;
    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}

static void _unresolved(void) {
}

void sys_01_release(void) {
    if (g_wp->file != NULL) {
        fileFree(g_wp->file);
    }
    g_wp = NULL;
}

s32 getLightColor(f32 angle) {
    f32 a = fmod(angle, 360.0);
    s32 c;

    if (a >= 270.0f) {
        c = 360.0f - a;
    } else if (a >= 180.0f) {
        c = a - 180.0f;
    } else if (a >= 90.0f) {
        c = 180.0f - a;
    } else {
        c = a;
    }
    return 255 - c * 2;
}

static inline void setTevColor(GXColor init) {
    GXColor color = init;

    GXSetTevColor(GX_TEVREG0, color);
}

static inline void setChanMatColor(GXColor init, s32 c) {
    GXColor color = init;

    color.r = c;
    color.g = c;
    color.b = c;
    GXSetChanMatColor(GX_COLOR0A0, color);
}

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

__declspec(section ".data") s8 prologue_jp_tbl[8] = {
    16, 17, 17, 6, 18, -1,
};

__declspec(section ".data") s8 stage1_jp_tbl[8] = {
    4, 5, 6, 7, 8, -1,
};

__declspec(section ".data") s8 stage2_jp_tbl[8] = {
    4, 5, 6, 7, 9, -1,
};

__declspec(section ".data") s8 stage3_jp_tbl[8] = {
    4, 5, 6, 7, 10, -1,
};

__declspec(section ".data") s8 stage4_jp_tbl[8] = {
    4, 5, 6, 7, 11, -1,
};

__declspec(section ".data") s8 stage5_jp_tbl[8] = {
    4, 5, 6, 7, 12, -1,
};

__declspec(section ".data") s8 stage6_jp_tbl[8] = {
    4, 5, 6, 7, 13, -1,
};

__declspec(section ".data") s8 stage7_jp_tbl[8] = {
    4, 5, 6, 7, 14, -1,
};

__declspec(section ".data") s8 stage8_jp_tbl[8] = {
    4, 5, 6, 7, 15, -1,
};

__declspec(section ".data") s8* texid_jp_tbl[] = {
    prologue_jp_tbl, stage1_jp_tbl, stage2_jp_tbl, stage3_jp_tbl, stage4_jp_tbl, stage5_jp_tbl, stage6_jp_tbl, stage7_jp_tbl, stage8_jp_tbl,
};

__declspec(section ".data") s8 prologue_us_tbl[12] = {
    17, 18, 19, 20, 19, 7, 21, 8, -1,
};

__declspec(section ".data") s8 stage1_us_tbl[8] = {
    4, 5, 6, 7, 8, 9, -1,
};

__declspec(section ".data") s8 stage2_us_tbl[8] = {
    4, 5, 6, 7, 8, 10, -1,
};

__declspec(section ".data") s8 stage3_us_tbl[8] = {
    4, 5, 6, 7, 8, 11, -1,
};

__declspec(section ".data") s8 stage4_us_tbl[8] = {
    4, 5, 6, 7, 8, 12, -1,
};

__declspec(section ".data") s8 stage5_us_tbl[8] = {
    4, 5, 6, 7, 8, 13, -1,
};

__declspec(section ".data") s8 stage6_us_tbl[8] = {
    4, 5, 6, 7, 8, 14, -1,
};

__declspec(section ".data") s8 stage7_us_tbl[8] = {
    4, 5, 6, 7, 8, 15, -1,
};

__declspec(section ".data") s8 stage8_us_tbl[8] = {
    4, 5, 6, 7, 8, 16, -1,
};

__declspec(section ".data") s8* texid_us_tbl[] = {
    prologue_us_tbl, stage1_us_tbl, stage2_us_tbl, stage3_us_tbl, stage4_us_tbl, stage5_us_tbl, stage6_us_tbl, stage7_us_tbl, stage8_us_tbl,
};

__declspec(section ".data") s8** lang_tbl[] = {
    texid_jp_tbl, texid_us_tbl,
};

__declspec(section ".data") const char* lang_prefix[] = {
    "jp", "us",
};

EVT_BEGIN(sys_01_init_evt)
    CALL(init)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_set_pos, 0, 0, 0)
    CALL(evt_party_set_pos, 0, 0, 0, 0)
    CALL(evt_cam3d_evt_set, 0, 0, 500, 0, 0, 0, 0, 11)
    CALL(bg)
    CALL(evt_fade_entry, 32, 0, 0, 0, 0)
    CALL(evt_fade_end_wait)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), 0)
        CALL(evt_bero_get_entername, LW(1))
        IF_STR_EQUAL(LW(1), STRING("prologue"))
            SET_VALUE(LW(0), 0)
        END_IF
        IF_STR_EQUAL(LW(1), STRING("stg_1"))
            SET_VALUE(LW(0), 1)
        END_IF
        IF_STR_EQUAL(LW(1), STRING("stg_2"))
            SET_VALUE(LW(0), 2)
        END_IF
        IF_STR_EQUAL(LW(1), STRING("stg_3"))
            SET_VALUE(LW(0), 3)
        END_IF
        IF_STR_EQUAL(LW(1), STRING("stg_4"))
            SET_VALUE(LW(0), 4)
        END_IF
        IF_STR_EQUAL(LW(1), STRING("stg_5"))
            SET_VALUE(LW(0), 5)
        END_IF
        IF_STR_EQUAL(LW(1), STRING("stg_6"))
            SET_VALUE(LW(0), 6)
        END_IF
        IF_STR_EQUAL(LW(1), STRING("stg_7"))
            SET_VALUE(LW(0), 7)
        END_IF
        IF_STR_EQUAL(LW(1), STRING("stg_8"))
            SET_VALUE(LW(0), 8)
        END_IF
        CALL(display, LW(0))
    END_INLINE_EVENT
    WAIT_MS(3000)
    CALL(evt_fade_set_mapchange_type, 0, 17, 1800, 16, 1800)
    CALL(evt_fade_set_mapchange_type, 1, 17, 1800, 16, 1800)
    SPAWN_EVENT(PTR(evt_start))
    RETURN
EVT_END()

EVT_BEGIN(evt_start)
    CALL(evt_fade_end_wait)
    WAIT_MS(2000)
    CALL(evt_bero_get_entername, LW(1))
    IF_STR_NOT_EQUAL(LW(1), STRING("stg_3"))
        IF_STR_NOT_EQUAL(LW(1), STRING("stg_5"))
            IF_STR_NOT_EQUAL(LW(1), STRING("stg_6"))
                CALL(evt_snd_bgmon, 512, STRING("BGM_FF_STG_START1"))
            END_IF
        END_IF
    END_IF
    CALL(evt_fade_entry, 35, 0, 0, 0, 0)
    CALL(evt_fade_end_wait)
    CALL(start)
    WAIT_MS(5000)
    LOOP(0)
        CALL(evt_key_get_buttontrg, 0, LW(0))
        IF_BITS_SET(LW(0), 4864)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_fade_set_mapchange_type, 0, 19, 500, 18, 500)
    CALL(evt_fade_set_mapchange_type, 1, 19, 500, 18, 500)
    CALL(evt_bero_get_entername, LW(1))
    IF_STR_EQUAL(LW(1), STRING("prologue"))
        SET_VALUE(LW(0), 0)
    END_IF
    IF_STR_EQUAL(LW(1), STRING("stg_1"))
        SET_VALUE(LW(0), 1)
    END_IF
    IF_STR_EQUAL(LW(1), STRING("stg_2"))
        SET_VALUE(LW(0), 2)
    END_IF
    IF_STR_EQUAL(LW(1), STRING("stg_3"))
        SET_VALUE(LW(0), 3)
    END_IF
    IF_STR_EQUAL(LW(1), STRING("stg_4"))
        SET_VALUE(LW(0), 4)
    END_IF
    IF_STR_EQUAL(LW(1), STRING("stg_5"))
        SET_VALUE(LW(0), 5)
    END_IF
    IF_STR_EQUAL(LW(1), STRING("stg_6"))
        SET_VALUE(LW(0), 6)
    END_IF
    IF_STR_EQUAL(LW(1), STRING("stg_7"))
        SET_VALUE(LW(0), 7)
    END_IF
    IF_STR_EQUAL(LW(1), STRING("stg_8"))
        SET_VALUE(LW(0), 8)
    END_IF
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(evt_bero_mapchange, STRING("gor_10"), 0)
        CASE_EQUAL(1)
        CALL(evt_bero_mapchange, STRING("hei_00"), STRING("dokan_2"))
        CASE_EQUAL(2)
        CALL(evt_bero_mapchange, STRING("win_06"), STRING("dokan1"))
        CASE_EQUAL(3)
        CALL(evt_bero_mapchange, STRING("tou_20"), 0)
        CASE_EQUAL(4)
        CALL(evt_bero_mapchange, STRING("usu_00"), STRING("dokan_1"))
        CASE_EQUAL(5)
        CALL(evt_bero_mapchange, STRING("muj_20"), 0)
        CASE_EQUAL(6)
        CALL(evt_bero_mapchange, STRING("rsh_02_a"), 0)
        CASE_EQUAL(7)
        CALL(evt_bero_mapchange, STRING("bom_00"), STRING("dokan"))
        CASE_EQUAL(8)
        CALL(evt_bero_mapchange, STRING("las_00"), STRING("w_bero"))
    END_SWITCH
    RETURN
EVT_END()

USER_FUNC(display) {
    SysWork* wp;
    SysChar* chr;
    s32 type = evtGetValue(event, event->args[0]);
    s32 i;

    if (isFirstCall) {
        wp = _mapAlloc(sizeof(SysWork));
        event->userdatap[0] = wp;
        memset(wp, 0, sizeof(SysWork));
        wp->type = type;
        wp->angle = 0.0f;
        wp->count = 0;
        while (lang_tbl[gp->language][type][wp->count] != -1) {
            wp->count++;
        }
        for (i = 0; i < wp->count; i++) {
            wp->chars[i].x = 36.0f * i - (f32)((wp->count - 1) * 36) / 2;
            wp->chars[i].y = 40.0f;
            wp->chars[i].z = 0.0f;
            wp->chars[i].rot = 90.0f;
            wp->chars[i].timer = i * 20 + 1;
            wp->chars[i].state = 0;
            wp->chars[i].texid = lang_tbl[gp->language][type][i];
        }
    }
    wp = event->userdatap[0];
    g_wp = wp;
    switch (wp->state) {
        case 0:
            if ((void*)fileAsyncf(4, NULL, "%s/e/%s/effect_sys.tpl", getMarioStDvdRoot(), lang_prefix[gp->language]) != NULL) {
                wp->file = fileAllocf(4, "%s/e/%s/effect_sys.tpl", getMarioStDvdRoot(), lang_prefix[gp->language]);
                wp->state++;
            }
            break;
        case 2:
            for (i = 0; i < wp->count; i++) {
                chr = &wp->chars[i];
                switch (chr->state) {
                    case 0:
                        chr->timer--;
                        if (chr->timer < 0) {
                            chr->timer = 0;
                            chr->state++;
                            effStardustN64SetDrawCam(effStardustN64Entry(4, chr->x, chr->y, chr->z, 40.0f), 5);
                        }
                        break;
                    case 1:
                        chr->rot = intplGetValue(5, chr->timer, 90, 90.0f, 1800.0f);
                        chr->timer++;
                        if (chr->timer > 90) {
                            chr->state++;
                        }
                        break;
                    case 2:
                        if (i == wp->count - 1) {
                            wp->angle += 0.8f;
                            if (wp->angle > 360.0f) {
                                wp->angle -= 360.0f;
                            }
                            wp->alpha += 0x30;
                            if (wp->alpha > 10000) {
                                wp->alpha = 10000;
                            }
                        }
                        break;
                }
            }
            break;
        case 3:
            break;
    }
    if (wp->state != 0) {
        dispEntry(CAMERA_3D_EFFECTA, 0.0f, 2, display_func, wp);
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(start) {
    SysWork* wp = g_wp;

    gp->flags |= 0x10;
    if (wp->state < 1) {
        return EVT_RETURN_BLOCK;
    }
    wp->state++;
    return EVT_RETURN_DONE;
}

USER_FUNC(bg) {
    EffectEntry* eff = effItemGetEntry(0, 0.0f, 0.0f, 0.0f);

    ((s32*)eff->userdata)[8] = 1;
    ((s32*)eff->userdata)[14] = 5;
    return EVT_RETURN_DONE;
}

USER_FUNC(init) {
    return EVT_RETURN_DONE;
}

