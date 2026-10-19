// FAKE: whole unit as asm (asm_inline + hand data naming, jump table via `entry` labels); C kept under #ifdef NONMATCHING. Best pure C: 6/7 (loadDraw 99.81).
#include "countdown.h"
#include "driver/fadedrv.h"
#include "driver/seqdrv.h"
#include "driver/swdrv.h"
#include "event.h"
#include "manager/cardmgr.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "manager/filemgr.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "mario/mariost.h"
#include "pmario_sound.h"
#include "system.h"
#include <dolphin/os.h>

#include "driver/dispdrv.h"
#include "driver/msgdrv.h"
#include <string.h>
#include <stdio.h>
#include "driver/camdrv.h"
#include "manager/fontmgr.h"
#include "driver/windowdrv.h"
#include "driver/icondrv.h"
#include "win/win_main.h"
#include "sdk/texPalette.h"
#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
__declspec(section ".sdata2") extern const u32 dat_8041bd68;
__declspec(section ".sdata2") extern const u32 dat_8041bd6c;
__declspec(section ".sdata2") extern const u32 dat_8041bd70;
__declspec(section ".sdata2") extern const u32 dat_8041bd74;
__declspec(section ".sdata2") extern const u32 dat_8041bd78;
__declspec(section ".sdata2") extern const u32 dat_8041bd7c;
__declspec(section ".sdata2") extern const u32 dat_8041bd80;
__declspec(section ".sdata2") extern const u32 dat_8041bd84;
__declspec(section ".sdata2") extern const u32 dat_8041bd88;
__declspec(section ".sdata2") extern const u32 dat_8041bd8c;
__declspec(section ".sdata2") extern const u32 dat_8041bd90;
__declspec(section ".sdata2") extern const u32 dat_8041bd94;
__declspec(section ".sdata2") extern const u32 dat_8041bd98;
__declspec(section ".sdata2") extern const u32 dat_8041bd9c;
__declspec(section ".sdata2") extern const u32 dat_8041bda0;
__declspec(section ".sdata2") extern const u32 dat_8041bda4;
__declspec(section ".sdata2") extern const u32 dat_8041bda8;
__declspec(section ".sdata2") extern const u32 dat_8041bdac;
__declspec(section ".sdata2") extern const u32 dat_8041bdb0;
__declspec(section ".sdata2") extern const u32 dat_8041bdb4;
__declspec(section ".sdata2") extern const u32 dat_8041bdb8;
__declspec(section ".sdata2") extern const u32 dat_8041bdbc;
__declspec(section ".sdata2") extern const u32 dat_8041bdc0;
__declspec(section ".sdata2") extern const u32 dat_8041bdc4;
__declspec(section ".sdata2") extern const u32 dat_8041bdc8;
__declspec(section ".sdata2") extern const u32 dat_8041bdcc;
__declspec(section ".sdata2") extern const u32 dat_8041bdd0;
__declspec(section ".sdata2") extern const u32 dat_8041bdd4;
__declspec(section ".sdata2") extern const u32 dat_8041bdd8;
__declspec(section ".sdata2") extern const char str_8041BDDC[8];
__declspec(section ".sdata2") extern const f32 float_0_8041bde4;
__declspec(section ".sdata2") extern const f32 float_1_8041bde8;
__declspec(section ".sdata2") extern const f32 float_neg304_8041bdec;
__declspec(section ".sdata2") extern const f32 float_240_8041bdf0;
__declspec(section ".sdata2") extern const f32 float_neg240_8041bdf4;
__declspec(section ".sdata2") extern const f32 float_neg272_8041bdf8;
__declspec(section ".sdata2") extern const f32 float_272_8041bdfc;
__declspec(section ".sdata2") extern const f32 float_304_8041be00;
__declspec(section ".sdata2") extern const f32 float_60_8041be04;
__declspec(section ".sdata2") extern const f32 float_neg250_8041be08;
__declspec(section ".sdata2") extern const f32 float_200_8041be0c;
__declspec(section ".sdata2") extern const f32 float_500_8041be10;
__declspec(section ".sdata2") extern const f32 float_40_8041be14;
__declspec(section ".sdata2") extern const f32 float_20_8041be18;
__declspec(section ".sdata2") extern const f32 float_0p6_8041be1c;
__declspec(section ".sdata2") extern const f32 float_100_8041be20;
__declspec(section ".sdata2") extern const f32 float_84_8041be24;
__declspec(section ".sdata2") extern const f32 float_0p5_8041be28;
__declspec(section ".sdata2") extern const f32 float_12_8041be2c;
__declspec(section ".sdata2") extern const f32 float_70_8041be30;
__declspec(section ".sdata2") extern const char str_8041BE34[8];
__declspec(section ".sdata2") extern const f32 float_30_8041be3c;
__declspec(section ".sdata2") extern const char str_8041BE40[4];
__declspec(section ".sdata2") extern const f32 float_8_8041be44;
__declspec(section ".sdata2") extern const f32 float_22_8041be48;
__declspec(section ".sdata2") extern const f32 float_1p5_8041be4c;
__declspec(section ".sdata2") extern const f32 float_106_8041be50;
__declspec(section ".sdata2") extern const f32 float_52_8041be54;
__declspec(section ".sdata2") extern const f32 float_0p05_8041be58;
__declspec(section ".sdata2") extern const f32 float_120_8041be5c;
__declspec(section ".sdata2") extern const f32 float_140_8041be60;
__declspec(section ".sdata2") extern const f32 float_neg150_8041be64;
__declspec(section ".sdata2") extern const f32 float_300_8041be68;
__declspec(section ".sdata2") extern const f32 float_50_8041be6c;
__declspec(section ".sdata2") extern const f32 float_2_8041be70;
__declspec(section ".sdata2") extern const f32 float_neg74_8041be74;
__declspec(section ".sdata2") extern const f32 float_4_8041be78;
__declspec(section ".sdata2") extern const f32 float_0p25_8041be7c;
__declspec(section ".sdata2") extern const f32 float_0p125_8041be80;
__declspec(section ".sdata2") extern const f32 float_1000_8041be84;
#endif
#pragma force_active on // FAKE: keep asm-only-referenced data from being dead-stripped
__declspec(section ".rodata") const f32 vec3_802ed670[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed67c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed688[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed694[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed6a0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed6ac[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed6b8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed6c4[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed6d0[3] = { 0.0f, 100.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed6dc[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed6e8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed6f4[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed700[3] = { -4.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed70c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed718[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed724[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed730[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed73c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed748[3] = { 0.0f, 100.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed754[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed760[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed76c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed778[3] = { -4.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed784[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed790[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed79c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const u32 dat_802ed7a8[16] = { 0x00000000, 0xC2B40000, 0xC3340000, 0xC3070000, 0x42B40000, 0x00000000, 0x43070000, 0x43340000, 0x00000000, 0xC2340000, 0x00000000, 0xC2B40000, 0x42340000, 0x00000000, 0x42B40000, 0x00000000 };
__declspec(section ".rodata") const f32 vec3_802ed7e8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed7f4[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed800[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed80c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed818[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed824[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed830[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed83c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") char str_802ED848[20] = "\117\106\106\137\146\137\151\156\137\157\165\164\137\155\141\162\151\157\000";
__declspec(section ".rodata") char str_802ED85C[20] = "\117\106\106\137\146\137\151\156\137\157\165\164\137\153\165\160\160\141\000";
__declspec(section ".rodata") char str_802ED870[20] = "\117\106\106\137\146\137\151\156\137\157\165\164\137\160\145\141\143\150\000";
__declspec(section ".rodata") char str_802ED884[8] = "\141\152\151\137\061\060\000";
__declspec(section ".rodata") char str_802ED88C[8] = "\153\160\141\137\060\060\000";
__declspec(section ".rodata") char str_802ED894[8] = "\156\157\153\137\060\061\000";
__declspec(section ".rodata") char str_802ED89C[12] = "\156\157\153\157\164\141\162\157\165\000\000";
__declspec(section ".rodata") char str_802ED8A8[8] = "\150\145\151\137\060\060\000";
__declspec(section ".rodata") char str_802ED8B0[8] = "\155\162\151\137\060\060\000";
__declspec(section ".rodata") char str_802ED8B8[8] = "\155\162\151\137\060\061\000";
__declspec(section ".rodata") char str_802ED8C0[8] = "\164\157\165\137\060\062\000";
__declspec(section ".rodata") char str_802ED8C8[8] = "\165\163\165\137\060\060\000";
__declspec(section ".rodata") char str_802ED8D0[8] = "\147\157\162\137\060\064\000";
__declspec(section ".rodata") char str_802ED8D8[8] = "\155\165\152\137\061\062\000";
__declspec(section ".rodata") char str_802ED8E0[8] = "\155\165\152\137\060\060\000";
__declspec(section ".rodata") char str_802ED8E8[8] = "\160\151\153\137\060\063\000";
__declspec(section ".rodata") char str_802ED8F0[8] = "\147\157\162\137\060\061\000";
__declspec(section ".rodata") char str_802ED8F8[16] = "\162\145\163\150\141\137\162\145\164\165\162\156\000\000\000";
__declspec(section ".rodata") char str_802ED908[8] = "\160\151\153\137\060\061\000";
__declspec(section ".rodata") char str_802ED910[8] = "\141\152\151\137\061\070\000";
__declspec(section ".rodata") char str_802ED918[8] = "\145\137\142\145\162\157\000";
__declspec(section ".rodata") char str_802ED920[8] = "\147\157\162\137\060\060\000";
__declspec(section ".rodata") char str_802ED928[8] = "\152\151\156\137\060\064\000";
__declspec(section ".rodata") char str_802ED930[8] = "\141\141\141\137\060\060\000";
__declspec(section ".rodata") char str_802ED938[12] = "\160\162\157\154\157\147\165\145\000\000\000";
__declspec(section ".rodata") const u32 gap_04_802ED944_rodata[1] = { 0x00000000 };
__declspec(section ".rodata") const f64 double_480_802ed948 = 480;
__declspec(section ".rodata") const f64 double_32_802ed950 = 32;
__declspec(section ".rodata") const f64 double_544_802ed958 = 544;
__declspec(section ".rodata") char str_802ED960[12] = "\203\146\201\133\203\136\045\163\000\000\000";
__declspec(section ".rodata") char str_802ED96C[16] = "\202\261\202\355\202\352\202\304\202\242\202\334\202\267\000";
__declspec(section ".rodata") char str_802ED97C[16] = "\203\152\203\205\201\133\203\121\201\133\203\200\000\000\000";
__declspec(section ".rodata") char str_802ED98C[12] = "\202\315\202\266\202\337\202\251\202\347\000";
__declspec(section ".rodata") char str_802ED998[12] = "\203\214\203\170\203\213\201\100\045\163\000";
__declspec(section ".rodata") char str_802ED9A4[16] = "\203\166\203\214\203\103\202\266\202\251\202\361\201\100\000";
__declspec(section ".rodata") const u32 gap_04_802ED9B4_rodata[1] = { 0x00000000 };
__declspec(section ".rodata") const f64 double_90_802ed9b8 = 90;
__declspec(section ".rodata") const f64 double_to_int_mask_802ed9c0 = 4503599627370496;
__declspec(section ".rodata") const f64 double_to_int_802ed9c8 = 4503601774854144;
__declspec(section ".rodata") char str_802ED9D0[20] = "\155\163\147\137\163\141\166\145\146\151\154\145\137\163\145\154\145\143\164";
__declspec(section ".rodata") char str_802ED9E4[28] = "\155\163\147\137\163\141\166\145\146\151\154\145\137\144\145\154\145\164\145\137\163\145\154\145\143\164\000";
__declspec(section ".rodata") char str_802EDA00[28] = "\155\163\147\137\163\141\166\145\146\151\154\145\137\143\157\160\171\137\163\145\154\145\143\164\000\000\000";
__declspec(section ".rodata") char str_802EDA1C[24] = "\155\163\147\137\163\141\166\145\146\151\154\145\137\143\157\160\171\137\160\157\151\156\164";
__declspec(section ".rodata") char str_802EDA34[20] = "\045\163\057\167\057\152\160\057\156\141\155\145\056\164\160\154\000\000\000";


typedef struct LoadWork {
    u16 flags;          // 0x0
    FileEntry* file;    // 0x4
    f32 x;              // 0x8
    f32 y;              // 0xC
    f32 tx;             // 0x10
    f32 ty;             // 0x14
    s32 unk18;          // 0x18
    s32 unk1C;          // 0x1C
    s32 slot;           // 0x20
    s32 unk24;          // 0x24
    s32 unk28;          // 0x28
    f32 alpha;          // 0x2C
    s32 unk30;          // 0x30
    s32 unk34;          // 0x34
    const char* msg;    // 0x38
    EventEntry* evt;    // 0x3C
    s32 unk40;          // 0x40
    s32 unk44;          // 0x44
    s32 unk48;          // 0x48
} LoadWork;

typedef struct WinDt {
    f32 x;      // 0x0
    f32 y;      // 0x4
    f32 ofsX;   // 0x8
    f32 ofsY;   // 0xC
    s32 unk10;  // 0x10
    s32 unk14;  // 0x14
    u8 next[4]; // 0x18
} WinDt;

extern s32 evt_memcard_check[];
extern s32 evt_memcard_start[];
extern s32 evt_memcard_save[];
extern s32 evt_memcard_delete[];
extern s32 evt_memcard_copy[];
extern s32 evt_sub_rumble_onoff(EventEntry* evt, BOOL isFirstCall);
extern s32 evt_sub_animgroup_async(EventEntry* evt, BOOL isFirstCall);
extern void SoundSetOutputMode(s32 mode);
extern void OSSetSoundMode(u32 mode);
extern BOOL psndENVOn(u32 flags, const char* name);
extern BOOL psndBGMOff(u32 flags);
void nameEntOn(s32 type);
void nameEntOff(void);
const char* nameEntGetName(void);
BOOL nameEntWait(void);
BOOL nameEntPrepare(void);
BOOL nameEntIsCancel(void);
double sin(double);
double fmod(double, double);
#ifdef NONMATCHING
static inline float fabsf(float x) { return (float)__fabs(x); }
#endif
void winTexInit_x2(TEXPalette* texture);
void winTexSet_x2(u32 id1, u32 id2, Vec translate, Vec scale, GXColor color);
void winTexSetRot(u32 id, Vec translate, Vec scale, GXColor color, f32 rot);
void nameMaskGX(f32 alpha);
const char* unk_8016af5c(s32 num, s32 digits);
void FontDrawScale(f32 scale);
void FontDrawString(f32 x, f32 y, const char* str);
void FontDrawEdge(void);
void FontDrawEdgeOff(void);
void loadMain(SequenceWork* seq);
void loadDraw(CameraId camera, void* param);
void continueGame(void);


__declspec(section ".data") f32 lbl_80349DE8[] = { -1.0f, 1.0f };
__declspec(section ".data") static f32 negone_one_374[] = { -1.0f, 1.0f };
__declspec(section ".data") f32 lbl_80349DF8[] = { 1.0f, -1.0f };
__declspec(section ".data") static f32 one_negone_373[] = { 1.0f, -1.0f };
__declspec(section ".data") f32 lbl_80349E08[] = { -1.0f, 1.0f };
__declspec(section ".data") static f32 negone_one_360[] = { -1.0f, 1.0f };
__declspec(section ".data") f32 lbl_80349E18[] = { 1.0f, -1.0f };
__declspec(section ".data") static f32 one_negone_359[] = { 1.0f, -1.0f };

WinDt win_dt[9] = {
    {-140.0f, 75.0f, -120.0f, 60.0f, 13, 0, {7, 2, 1, 1}},
    {140.0f, 75.0f, -120.0f, 60.0f, 12, 0, {8, 3, 0, 0}},
    {-140.0f, -65.0f, -120.0f, 60.0f, 11, 0, {0, 4, 3, 3}},
    {140.0f, -65.0f, -120.0f, 60.0f, 10, 0, {1, 5, 2, 2}},
    {-200.0f, -150.0f, -80.0f, 0.0f, 16, 30, {2, 7, 6, 5}},
    {0.0f, -150.0f, -80.0f, 0.0f, 17, 30, {2, 7, 4, 6}},
    {200.0f, -150.0f, -80.0f, 0.0f, 18, 30, {3, 8, 5, 4}},
    {-130.0f, -190.0f, -100.0f, 0.0f, 19, 31, {4, 0, 8, 8}},
    {130.0f, -190.0f, -100.0f, 0.0f, 20, 31, {5, 1, 7, 7}},
};

WinDt win_dt2[7] = {
    {-140.0f, 75.0f, -120.0f, 60.0f, 13, 0, {6, 2, 1, 1}},
    {140.0f, 75.0f, -120.0f, 60.0f, 12, 0, {6, 3, 0, 0}},
    {-140.0f, -65.0f, -120.0f, 60.0f, 11, 0, {0, 6, 3, 3}},
    {140.0f, -65.0f, -120.0f, 60.0f, 10, 0, {1, 6, 2, 2}},
    {-200.0f, -150.0f, -80.0f, 0.0f, 16, 30, {2, 7, 6, 5}},
    {0.0f, -150.0f, -80.0f, 0.0f, 17, 30, {2, 7, 4, 6}},
    {200.0f, -150.0f, -80.0f, 0.0f, 18, 30, {3, 1, 6, 6}},
};

WinDt win_dt3[4] = {
    {-140.0f, 75.0f, -120.0f, 60.0f, 13, 0, {2, 2, 1, 1}},
    {140.0f, 75.0f, -120.0f, 60.0f, 12, 0, {3, 3, 0, 0}},
    {-140.0f, -65.0f, -120.0f, 60.0f, 11, 0, {0, 0, 3, 3}},
    {140.0f, -65.0f, -120.0f, 60.0f, 10, 0, {1, 1, 2, 2}},
};

__declspec(section ".data") static u32 gap_06_803DB834_bss;
static LoadWork work;
static LoadWork* wp = &work;

extern s32 stone_id[];
static s32 evt_shake[12];
extern s32 evt_continue[];

s32 unk_800f2398(EventEntry* evt, BOOL isFirstCall) {
    fadeReset(4);
    wp->unk48 = evt->printWindowId;
    return 2;
}

void seq_loadInit(SequenceWork* seq) {
    memset(wp, 0, sizeof(LoadWork));
}

void seq_loadExit(SequenceWork* seq) {
    if (wp->file != NULL) {
        fileFree(wp->file);
    }
    wp->file = NULL;
}

#ifdef NONMATCHING
static inline BOOL loadStart(void) {
    if (fileAsyncf(4, NULL, "%s/w/jp/name.tpl\0\0\0", getMarioStDvdRoot()) != 0U) {
        wp->file = fileAllocf(4, "%s/w/jp/name.tpl\0\0\0", getMarioStDvdRoot());
        return TRUE;
    }
    return FALSE;
}
#endif

void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXClearVtxDesc(void);
void GXGetProjectionv(f32* ptr);
u16 GXGetTexObjHeight(const GXTexObj* to);
u16 GXGetTexObjWidth(const GXTexObj* to);
void GXGetViewportv(f32* vp);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
    f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
    GXBool do_edge_lod, GXAnisotropy max_aniso);
void GXLoadPosMtxImm(const f32 mtx[3][4], u32 id);
void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op);
void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn);
void GXSetCullMode(GXCullMode mode);
void GXSetCurrentMtx(u32 id);
void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color);
void GXSetNumChans(u8 nChans);
void GXSetNumTevStages(u8 nStages);
void GXSetNumTexGens(u8 nTexGens);
void GXSetProjection(const f32 mtx[4][4], GXProjectionType type);
void GXSetProjectionv(const f32* ptr);
void GXSetTevOp(GXTevStageID id, GXTevMode mode);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx);
void GXSetViewport(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz);
void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac);
void GXSetVtxDesc(GXAttr attr, GXAttrType type);
void GXSetZCompLoc(GXBool before_tex);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
u32 OSGetSoundMode(void);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
int __div2i();
int __div2u();
int __mod2u();
int sprintf(char *s, const char *format, ...);
int strcat();
char *strcpy(char *dest, const char *src);
size_t strlen(const char *s);
int winZenkakuStr();
extern void* jumptable_8034A058[25];
#ifdef NONMATCHING
void seq_loadMain(SequenceWork* seq) {
    switch (seq->state) {
        case 0:
            if (loadStart()) {
                seq->state++;
            }
            break;
        case 1:
            wp->evt = evtEntryType(evt_memcard_check, 0, 0, 0);
            if (wp->flags & 0x80) {
                wp->flags &= ~0x80;
                *(s32*)((u8*)wp->evt + 0xC4) = 1;
                wp->evt->printWindowId = wp->unk48;
            }
            seq->state++;
            break;
        case 2:
            if (evtCheckID(wp->evt->eventId) == 0) {
                if (evtGetValue(NULL, (s32)0xFAA2B580) != 1) {
                    seqSetSeq(SEQ_TITLE, NULL, NULL);
                } else {
                    wp->evt = NULL;
                    seq->state++;
                    wp->unk18 = 0;
                    wp->unk1C = cardGetCode();
                    wp->flags &= ~0x40;
                    if (OSGetSoundMode() == 0) {
                        SoundSetOutputMode(0);
                        gp->unk1274 = 0;
                        wp->unk40 = 0;
                    } else {
                        SoundSetOutputMode(1);
                        if (gp->unk1274 == 0) {
                            wp->unk40 = 1;
                        } else {
                            wp->unk40 = 2;
                        }
                    }
                    wp->unk44 = gp->rumbleEnabled == 0;
                    wp->unk24 = wp->unk40;
                    wp->unk28 = wp->unk44;
                    wp->slot = gp->lastSlot;
                    wp->x = win_dt[wp->slot].x;
                    wp->y = win_dt[wp->slot].y;
                }
            }
            break;
        case 3: {
            GXColor c = {0, 0, 0, 255};
            fadeEntry(0x1c, 0, c);
            seq->state++;
            break;
        }
        case 4:
            loadMain(seq);
            break;
    }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void seq_loadMain(SequenceWork* seq) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		opword 0x7C7F1B78
		opword 0x80030004
		opword 0x2C000002
		opword 0x41820100
		opword 0x40800014
		opword 0x2C000000
		opword 0x4182001C
		opword 0x40800088
		opword 0x48000270
		opword 0x2C000004
		opword 0x41820264
		opword 0x40800264
		opword 0x48000234
		bl getMarioStDvdRoot
		lis r4, str_802EDA34@ha
		opword 0x7C661B78
		addi r5, r4, str_802EDA34@l
		opword 0x38600004
		opword 0x38800000
		opword 0x4CC63182
		bl fileAsyncf
		opword 0x28030000
		opword 0x41820030
		bl getMarioStDvdRoot
		lis r4, str_802EDA34@ha
		opword 0x7C651B78
		addi r4, r4, str_802EDA34@l
		opword 0x38600004
		opword 0x4CC63182
		bl fileAllocf
		lwz r4, wp(r13)
		opword 0x38000001
		opword 0x90640004
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x41820200
		opword 0x807F0004
		opword 0x38030001
		opword 0x901F0004
		opword 0x480001F0
		lis r3, evt_memcard_check@ha
		opword 0x38800000
		addi r3, r3, evt_memcard_check@l
		opword 0x38A00000
		opword 0x38C00000
		bl evtEntryType
		lwz r4, wp(r13)
		opword 0x9064003C
		lwz r4, wp(r13)
		opword 0xA0640000
		opword 0x54600631
		opword 0x4182002C
		opword 0x5463066E
		opword 0x38000001
		opword 0xB0640000
		lwz r3, wp(r13)
		opword 0x8063003C
		opword 0x900300C4
		lwz r3, wp(r13)
		opword 0x80030048
		opword 0x8063003C
		opword 0x90030178
		opword 0x807F0004
		opword 0x38030001
		opword 0x901F0004
		opword 0x48000188
		lwz r3, wp(r13)
		opword 0x8063003C
		opword 0x8063015C
		bl evtCheckID
		opword 0x2C030000
		opword 0x40820170
		opword 0x3C80FAA3
		opword 0x38600000
		opword 0x3884B580
		bl evtGetValue
		opword 0x2C030001
		opword 0x41820018
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		bl seqSetSeq
		opword 0x48000144
		lwz r3, wp(r13)
		opword 0x38800000
		opword 0x9083003C
		opword 0x807F0004
		opword 0x38030001
		opword 0x901F0004
		lwz r3, wp(r13)
		opword 0x90830018
		bl cardGetCode
		lwz r4, wp(r13)
		opword 0x9064001C
		lwz r3, wp(r13)
		opword 0xA0030000
		opword 0x540006B0
		opword 0xB0030000
		bl OSGetSoundMode
		opword 0x28030000
		opword 0x40820024
		opword 0x38600000
		bl SoundSetOutputMode
		lwz r3, gp(r13)
		opword 0x38000000
		opword 0x90031274
		lwz r3, wp(r13)
		opword 0x90030040
		opword 0x48000038
		opword 0x38600001
		bl SoundSetOutputMode
		lwz r3, gp(r13)
		opword 0x80031274
		opword 0x2C000000
		opword 0x40820014
		lwz r3, wp(r13)
		opword 0x38000001
		opword 0x90030040
		opword 0x48000010
		lwz r3, wp(r13)
		opword 0x38000002
		opword 0x90030040
		lwz r5, gp(r13)
		lis r3, win_dt@ha
		lwz r4, wp(r13)
		addi r3, r3, win_dt@l
		opword 0x80051294
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x90040044
		lwz r4, wp(r13)
		opword 0x80040040
		opword 0x90040024
		lwz r4, wp(r13)
		opword 0x80040044
		opword 0x90040028
		lwz r5, gp(r13)
		lwz r4, wp(r13)
		opword 0x800511B8
		opword 0x90040020
		lwz r4, wp(r13)
		opword 0x80040020
		opword 0x1C00001C
		opword 0x7C03042E
		opword 0xD0040008
		lwz r4, wp(r13)
		opword 0x80040020
		opword 0x1C00001C
		opword 0x7C630214
		opword 0xC0030004
		opword 0xD004000C
		opword 0x48000030
		lwz r0, dat_8041bd68(r2)
		opword 0x38A10008
		opword 0x3860001C
		opword 0x38800000
		opword 0x90010008
		bl fadeEntry
		opword 0x807F0004
		opword 0x38030001
		opword 0x901F0004
		opword 0x48000008
		bl loadMain
		opword 0x80010024
		opword 0x83E1001C
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop
#endif

#define SFX(id) psndSFXOn((const char*)(id))
#define SLOTFLAGS(i) (cardGetFilePtr()->saves[(i)].data.flags)

#ifdef NONMATCHING
void loadMain(SequenceWork* seq) {
    u32 trg;
    u32 dir;
    s32 code;
    s32 prev;
    s32 i;
    s32 sound;
    u16 flags;

    trg = keyGetButtonTrg(0);
    keyGetButtonRep(0);
    dir = keyGetDirRep(0);
    code = cardGetCode();
    if (cardIsExec() || !fadeIsFinish()) {
        trg = 0;
        dir = 0;
    }
    if (wp->unk1C != code) {
        trg = 0;
        dir = 0;
    }
    wp->unk1C = code;
    for (i = 0; i < 4; i++) {
        flags = SLOTFLAGS(i);
        if (!(flags & 1) || (flags & 2)) {
            break;
        }
    }
    if (i < 4) {
        wp->flags &= ~0x10;
    } else {
        wp->flags |= 0x10;
    }
    wp->flags &= ~0x20;
    for (i = 0; i < 4; i++) {
        flags = SLOTFLAGS(i);
        if (!(flags & 1) && !(flags & 2)) {
            break;
        }
    }
    if (i >= 4) {
        wp->flags |= 0x20;
    }

    switch (wp->unk18) {
        case 0:
            wp->unk18++;
        case 1:
            wp->msg = msgSearch(str_802ED9D0);
            prev = wp->slot;
            if (dir & 0x1000) {
                wp->slot = win_dt[prev].next[0];
            } else if (dir & 0x2000) {
                wp->slot = win_dt[prev].next[1];
            } else if (dir & 0x4000) {
                wp->slot = win_dt[prev].next[2];
            } else if (dir & 0x8000) {
                wp->slot = win_dt[prev].next[3];
            } else if (trg & 0x100) {
                flags = SLOTFLAGS(wp->slot);
                switch (wp->slot) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        if (flags & 2) {
                            SFX(0x13);
                        } else if (flags & 1) {
                            wp->unk18 = 0x1e;
                            SFX(0x12);
                        } else {
                            wp->unk18 = 0x14;
                            SFX(0x12);
                        }
                        break;
                    case 4:
                        if (!(wp->flags & 0x10)) {
                            for (i = 0; i < 4; i++) {
                                flags = SLOTFLAGS(i);
                                if (!(flags & 1) || (flags & 2)) {
                                    break;
                                }
                            }
                            if (i < 4) {
                                SFX(0x12);
                                wp->slot = 0;
                                wp->unk18 = 0x28;
                            } else {
                                SFX(0x13);
                            }
                        }
                        break;
                    case 5:
                        if (!(wp->flags & 0x20)) {
                            for (i = 0; i < 4; i++) {
                                flags = SLOTFLAGS(i);
                                if (!(flags & 2) && !(flags & 1)) {
                                    break;
                                }
                            }
                            if (i < 4) {
                                SFX(0x12);
                                wp->slot = 0;
                                wp->unk18 = 0x32;
                            } else {
                                SFX(0x13);
                            }
                        }
                        break;
                    case 6:
                        SFX(0x13);
                        wp->unk18 = 0xa;
                        break;
                    case 7:
                        SFX(0x12);
                        psndBGMOff(0x800);
                        wp->unk18 = 0x64;
                        break;
                    case 8:
                        SFX(0x12);
                        wp->unk18 = 0xc8;
                        break;
                }
            } else if (trg & 0x200) {
                SFX(0x13);
                wp->unk18 = 0xa;
            }
            if (prev != wp->slot) {
                if (wp->slot < 4) {
                    SFX(9);
                } else {
                    SFX(5);
                }
            }
            wp->tx = win_dt[wp->slot].x + win_dt[wp->slot].ofsX;
            wp->ty = win_dt[wp->slot].y + win_dt[wp->slot].ofsY;
            break;
        case 0xa:
            fadeEntry(0x1b, 0, (GXColor){0, 0, 0, 255});
            wp->unk18++;
            break;
        case 0xb:
            if (fadeIsFinish()) {
                seqSetSeq(SEQ_TITLE, NULL, NULL);
            }
            break;
        case 0x14:
            wp->flags |= 0x40;
            wp->evt = evtEntryType(evt_memcard_start, 0, 0, 0);
            wp->evt->lwData[0] = wp->slot;
            wp->unk18++;
            break;
        case 0x15:
            if (!evtCheckID(wp->evt->eventId)) {
                wp->flags &= ~0x40;
                if (evtGetValue(NULL, (s32)0xFD050F80) == 1) {
                    wp->unk18++;
                } else {
                    wp->unk18 = 1;
                }
            }
            break;
        case 0x16:
            fadeEntry(0x1b, 0, (GXColor){0, 0, 0, 255});
            psndBGMOff_f_d(0x200, 2000, 0);
            wp->unk18++;
            break;
        case 0x17:
            if (fadeIsFinish()) {
                wp->flags |= 0x40;
                wp->evt = evtEntryType(evt_continue, 0, 0, 0);
                wp->unk18++;
            }
            break;
        case 0x18:
            if (!evtCheckID(wp->evt->eventId)) {
                wp->flags &= ~0x40;
                continueGame();
            }
            break;
        case 0x1e:
            fadeEntry(0x1b, 0, (GXColor){0, 0, 0, 255});
            wp->unk18++;
            break;
        case 0x1f:
            if (fadeIsFinish()) {
                wp->unk18++;
            }
            break;
        case 0x20:
            if (nameEntPrepare()) {
                nameEntOn(0);
                fadeEntry(0x1c, 0, (GXColor){0, 0, 0, 255});
                wp->unk18++;
            }
            break;
        case 0x21:
            if (fadeIsFinish() && !nameEntWait()) {
                fadeEntry(0x18, 0, (GXColor){0, 0, 0, 255});
                if (!nameEntIsCancel()) {
                    psndBGMOff_f_d(0x200, 3000, 0);
                }
                wp->unk18++;
            }
            break;
        case 0x22:
            if (fadeIsFinish()) {
                nameEntOff();
                if (nameEntIsCancel()) {
                    fadeEntry(0x1c, 0, (GXColor){0, 0, 0, 255});
                    wp->unk18 = 1;
                } else {
                    strcpy((char*)gp->field_0x11BC, nameEntGetName());
                    gp->lastSlot = wp->slot;
                    stg0_00_init();
                    gp->saveSlot = wp->slot;
                    marioPartyKill();
                    {
                        MarioWork* m = marioGetPtr();
                        m->prevPartyMemberId[0] = 0;
                        m->prevPartyMemberId[1] = 0;
                    }
                    gp->areaFadeInType = 0;
                    gp->areaFadeOutType = 25;
                    swInit();
                    swByteSet(0, 0);
                    if (code == 0) {
                        gp->saveSlot = wp->slot;
                        wp->evt = evtEntryType(evt_memcard_save, 0, 0, 0);
                        wp->evt->lwData[0] = 0x17;
                        wp->unk18++;
                    } else {
                        seqSetSeq(SEQ_MAP_CHANGE, str_802ED930, str_802ED938);
                    }
                }
            }
            break;
        case 0x23:
            if (!evtCheckID(wp->evt->eventId)) {
                seqSetSeq(SEQ_MAP_CHANGE, str_802ED930, str_802ED938);
            }
            break;
        case 0x28:
            wp->msg = msgSearch(str_802ED9E4);
            prev = wp->slot;
            if (dir & 0x1000) {
                wp->slot = win_dt2[prev].next[0];
            } else if (dir & 0x2000) {
                wp->slot = win_dt2[prev].next[1];
            } else if (dir & 0x4000) {
                wp->slot = win_dt2[prev].next[2];
            } else if (dir & 0x8000) {
                wp->slot = win_dt2[prev].next[3];
            } else if (trg & 0x100) {
                if (prev < 4) {
                    flags = SLOTFLAGS(wp->slot);
                    if ((flags & 2) || !(flags & 1)) {
                        SFX(0x12);
                        wp->unk18++;
                    } else {
                        SFX(0x13);
                    }
                } else {
                    wp->slot = 4;
                    wp->unk18 = 1;
                    SFX(0x13);
                }
            } else if (trg & 0x200) {
                wp->slot = 4;
                wp->unk18 = 1;
                SFX(0x13);
            }
            if (prev != wp->slot && wp->slot < 4) {
                SFX(9);
            }
            wp->tx = win_dt2[wp->slot].x + win_dt2[wp->slot].ofsX;
            wp->ty = win_dt2[wp->slot].y + win_dt2[wp->slot].ofsY;
            break;
        case 0x29:
            wp->flags |= 0x40;
            wp->evt = evtEntryType(evt_memcard_delete, 0, 0, 0);
            wp->evt->lwData[0] = wp->slot;
            wp->unk18++;
            break;
        case 0x2a:
            if (!evtCheckID(wp->evt->eventId)) {
                if (evtGetValue(NULL, (s32)0xFAA2B580) == 0) {
                    wp->flags &= ~0x40;
                    wp->slot = 4;
                    wp->unk18 = 1;
                } else {
                    wp->flags |= 0x80;
                    seq->state = 1;
                    return;
                }
            }
            break;
        case 0x32:
            wp->msg = msgSearch(str_802EDA00);
            prev = wp->slot;
            if (dir & 0x1000) {
                wp->slot = win_dt2[prev].next[0];
            } else if (dir & 0x2000) {
                wp->slot = win_dt2[prev].next[1];
            } else if (dir & 0x4000) {
                wp->slot = win_dt2[prev].next[2];
            } else if (dir & 0x8000) {
                wp->slot = win_dt2[prev].next[3];
            } else if (trg & 0x100) {
                if (prev < 4) {
                    flags = SLOTFLAGS(wp->slot);
                    if (!(flags & 2) && !(flags & 1)) {
                        wp->unk18 = 0x33;
                        wp->unk30 = wp->slot;
                        wp->unk34 = (wp->unk30 + 1) % 4;
                        wp->slot = wp->unk34;
                        SFX(0x12);
                    }
                } else {
                    wp->slot = 5;
                    wp->unk18 = 1;
                    SFX(0x13);
                }
            } else if (trg & 0x200) {
                wp->slot = 5;
                wp->unk18 = 1;
                SFX(0x13);
            }
            if (prev != wp->slot && wp->slot < 4) {
                SFX(9);
            }
            wp->tx = win_dt2[wp->slot].x + win_dt2[wp->slot].ofsX;
            wp->ty = win_dt2[wp->slot].y + win_dt2[wp->slot].ofsY;
            break;
        case 0x33:
            wp->msg = msgSearch(str_802EDA1C);
            prev = wp->slot;
            if (dir & 0x1000) {
                do {
                    wp->slot = win_dt3[wp->slot].next[0];
                } while (wp->slot == wp->unk30);
            } else if (dir & 0x2000) {
                do {
                    wp->slot = win_dt3[wp->slot].next[1];
                } while (wp->slot == wp->unk30);
            } else if (dir & 0x4000) {
                do {
                    wp->slot = win_dt3[wp->slot].next[2];
                } while (wp->slot == wp->unk30);
            } else if (dir & 0x8000) {
                do {
                    wp->slot = win_dt3[wp->slot].next[3];
                } while (wp->slot == wp->unk30);
            } else if (trg & 0x100) {
                wp->unk18 = 0x34;
                wp->unk34 = wp->slot;
                SFX(0x12);
            } else if (trg & 0x200) {
                wp->slot = wp->unk30;
                wp->unk18 = 0x32;
                SFX(0x13);
            }
            if (prev != wp->slot && wp->slot < 4) {
                SFX(9);
            }
            wp->unk34 = wp->slot;
            wp->tx = win_dt2[wp->slot].x + win_dt2[wp->slot].ofsX;
            wp->ty = win_dt2[wp->slot].y + win_dt2[wp->slot].ofsY;
            break;
        case 0x34:
            wp->flags |= 0x40;
            wp->evt = evtEntryType(evt_memcard_copy, 0, 0, 0);
            wp->evt->lwData[0] = wp->unk30;
            wp->evt->lwData[1] = wp->unk34;
            wp->unk18++;
            break;
        case 0x35:
            if (!evtCheckID(wp->evt->eventId)) {
                if (evtGetValue(NULL, (s32)0xFAA2B580) == 0) {
                    wp->flags &= ~0x40;
                    wp->slot = 5;
                    wp->unk18 = 1;
                } else {
                    wp->flags |= 0x80;
                    seq->state = 1;
                    return;
                }
            }
            break;
        case 0x64:
            wp->flags |= 1;
            sound = wp->unk24;
            if (dir & 0x1000) {
                wp->unk24 = wp->unk24 - 1;
                SFX(5);
            } else if (dir & 0x2000) {
                wp->unk24 = wp->unk24 + 1;
                SFX(5);
            } else if (trg & 0x100) {
                switch (sound) {
                    case 0:
                        OSSetSoundMode(0);
                        gp->unk1274 = 0;
                        break;
                    case 1:
                        OSSetSoundMode(1);
                        gp->unk1274 = 0;
                        break;
                    case 2:
                        OSSetSoundMode(1);
                        gp->unk1274 = 1;
                        break;
                }
                if (OSGetSoundMode() == 0) {
                    SoundSetOutputMode(0);
                } else {
                    SoundSetOutputMode(1);
                }
                SFX(0x12);
                psndBGMOn(0xa0, NULL);
                psndENVOff(0x200);
                wp->unk40 = wp->unk24;
                wp->flags &= ~1;
                wp->unk18 = 1;
                break;
            } else if (trg & 0x200) {
                SFX(0x13);
                psndBGMOn(0xa0, NULL);
                psndENVOff(0x200);
                wp->unk24 = wp->unk40;
                if (OSGetSoundMode() == 0) {
                    SoundSetOutputMode(0);
                } else {
                    SoundSetOutputMode(1);
                }
                wp->flags &= ~1;
                wp->unk18 = 1;
                break;
            }
            if (wp->unk24 >= 3) {
                wp->unk24 = 0;
            }
            if (wp->unk24 < 0) {
                wp->unk24 = 2;
            }
            if (wp->unk24 != sound) {
                switch (wp->unk24) {
                    case 0:
                        SoundSetOutputMode(0);
                        break;
                    case 1:
                        SoundSetOutputMode(1);
                        break;
                    case 2:
                        SoundSetOutputMode(2);
                        break;
                }
                psndENVOn(0x110, (const char*)0x75);
            }
            wp->tx = EXT_LIT(float_neg74_8041be74, -74.0f);
            wp->ty = EXT_LIT(float_4_8041be78, 4.0f) + (EXT_LIT(float_50_8041be6c, 50.0f) - 50.0f * wp->unk24);
            break;
        case 0xc8:
            wp->flags |= 1;
            if (dir & 0x1000) {
                wp->unk28--;
                SFX(5);
            } else if (dir & 0x2000) {
                wp->unk28++;
                SFX(5);
            } else if (trg & 0x100) {
                gp->rumbleEnabled = wp->unk28 == 0;
                SFX(0x12);
                wp->unk44 = wp->unk28;
                wp->flags &= ~1;
                wp->unk18 = 1;
                if (gp->rumbleEnabled) {
                    evtEntryType(evt_shake, 0, 0, 0);
                }
            } else if (trg & 0x200) {
                SFX(0x13);
                wp->unk28 = wp->unk44;
                wp->flags &= ~1;
                wp->unk18 = 1;
            }
            if (wp->unk28 >= 2) {
                wp->unk28 = 0;
            }
            if (wp->unk28 < 0) {
                wp->unk28 = 1;
            }
            wp->tx = EXT_LIT(float_neg74_8041be74, -74.0f);
            wp->ty = EXT_LIT(float_4_8041be78, 4.0f) + (EXT_LIT(float_30_8041be3c, 30.0f) - 50.0f * wp->unk28);
            break;
    }
    wp->x += (wp->tx - wp->x) / EXT_LIT(float_4_8041be78, 4.0f);
    wp->y += (wp->ty - wp->y) / EXT_LIT(float_4_8041be78, 4.0f);
    { f32 s = 2.0f * (f32)sin(gp->retraceCount / 8.0f); wp->x += __fabsf(s); }
    dispEntry(CAMERA_3D, EXT_LIT(float_1000_8041be84, 1000.0f), 0, loadDraw, NULL);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void loadMain(SequenceWork* seq) {
	char _af_pad[32];
	asm {
		lis r5, lbl_80349DE8@ha
		lis r4, vec3_802ed670@ha
	}
	asm volatile {
		opword 0x7C7A1B78
		opword 0x38600000
		addi r29, r5, lbl_80349DE8@l
		addi r30, r4, vec3_802ed670@l
		bl keyGetButtonTrg
		opword 0x7C601B78
		opword 0x38600000
		opword 0x7C1C0378
		bl keyGetButtonRep
		opword 0x38600000
		bl keyGetDirRep
		opword 0x7C7B1B78
		bl cardGetCode
		opword 0x7C7F1B78
		bl cardIsExec
		opword 0x2C030000
		opword 0x40820010
		bl fadeIsFinish
		opword 0x2C030000
		opword 0x4082000C
		opword 0x3B800000
		opword 0x3B600000
		lwz r3, wp(r13)
		opword 0x8003001C
		opword 0x7C00F800
		opword 0x4182000C
		opword 0x3B800000
		opword 0x3B600000
		opword 0x93E3001C
		li r24, 0x0
		opword 0x3B200000
		bl cardGetFilePtr
		opword 0x38192000
		opword 0x7C63022E
		opword 0x546007FF
		opword 0x4182001C
		opword 0x546007BD
		opword 0x40820014
		opword 0x3B180001
		opword 0x3B394000
		opword 0x2C180004
		opword 0x4180FFD8
		opword 0x2C180004
		opword 0x40800018
		lwz r3, wp(r13)
		opword 0xA0030000
		opword 0x54000734
		opword 0xB0030000
		opword 0x48000014
		lwz r3, wp(r13)
		opword 0xA0030000
		opword 0x60000010
		opword 0xB0030000
		lwz r3, wp(r13)
		opword 0x3B000000
		opword 0x7F19C378
		opword 0xA0030000
		opword 0x540006F2
		opword 0xB0030000
		bl cardGetFilePtr
		opword 0x38192000
		opword 0x7C63022E
		opword 0x546007FF
		opword 0x4082000C
		opword 0x546007BD
		opword 0x41820014
		opword 0x3B180001
		opword 0x3B394000
		opword 0x2C180004
		opword 0x4180FFD8
		opword 0x2C180004
		opword 0x41800014
		lwz r3, wp(r13)
		opword 0xA0030000
		opword 0x60000020
		opword 0xB0030000
		lwz r6, wp(r13)
		opword 0x80660018
		opword 0x2C030021
		opword 0x4182062C
		opword 0x40800078
		opword 0x2C030015
		opword 0x41820480
		opword 0x4080003C
		opword 0x2C03000A
		opword 0x418203D8
		opword 0x4080001C
		opword 0x2C030001
		opword 0x418200CC
		opword 0x40801268
		opword 0x2C030000
		opword 0x408000B8
		opword 0x4800125C
		opword 0x2C030014
		opword 0x40800400
		opword 0x2C03000C
		opword 0x4080124C
		opword 0x480003D4
		opword 0x2C03001E
		opword 0x41820550
		opword 0x4080001C
		opword 0x2C030018
		opword 0x41820518
		opword 0x40801230
		opword 0x2C030017
		opword 0x408004C0
		opword 0x48000480
		opword 0x2C030020
		opword 0x40800578
		opword 0x48000554
		opword 0x2C030033
		opword 0x41820B8C
		opword 0x4080003C
		opword 0x2C030029
		opword 0x418208F0
		opword 0x4080001C
		opword 0x2C030023
		opword 0x41820718
		opword 0x418005F0
		opword 0x2C030028
		opword 0x40800734
		opword 0x480011E8
		opword 0x2C030032
		opword 0x40800990
		opword 0x2C03002B
		opword 0x408011D8
		opword 0x48000910
		opword 0x2C030064
		opword 0x41820DE4
		opword 0x40800014
		opword 0x2C030035
		opword 0x41820D64
		opword 0x408011BC
		opword 0x48000CFC
		opword 0x2C0300C8
		opword 0x41821034
		opword 0x480011AC
		opword 0x38030001
		opword 0x90060018
		opword 0x387E0360
		bl msgSearch
		lwz r4, wp(r13)
		opword 0x576004E7
		opword 0x90640038
		lwz r4, wp(r13)
		opword 0x83E40020
		opword 0x4182001C
		opword 0x1C1F001C
		opword 0x387D0040
		opword 0x7C630214
		opword 0x88030018
		opword 0x90040020
		opword 0x48000258
		opword 0x576004A5
		opword 0x4182001C
		opword 0x1C1F001C
		opword 0x387D0040
		opword 0x7C630214
		opword 0x88030019
		opword 0x90040020
		opword 0x48000238
		opword 0x57600463
		opword 0x4182001C
		opword 0x1C1F001C
		opword 0x387D0040
		opword 0x7C630214
		opword 0x8803001A
		opword 0x90040020
		opword 0x48000218
		opword 0x57600421
		opword 0x4182001C
		opword 0x1C1F001C
		opword 0x387D0040
		opword 0x7C630214
		opword 0x8803001B
		opword 0x90040020
		opword 0x480001F8
		opword 0x578005EF
		opword 0x418201D4
		bl cardGetFilePtr
		lwz r6, wp(r13)
		opword 0x80A60020
		opword 0x54A47022
		opword 0x2C050006
		opword 0x38042000
		opword 0x7C63022E
		opword 0x41820164
		opword 0x4080001C
		opword 0x2C050004
		opword 0x41820068
		opword 0x408000DC
		opword 0x2C050000
		opword 0x40800018
		opword 0x480001B4
		opword 0x2C050008
		opword 0x41820178
		opword 0x408001A8
		opword 0x48000150
		opword 0x546007BD
		opword 0x41820010
		opword 0x38600013
		bl psndSFXOn
		opword 0x48000190
		opword 0x546007FF
		opword 0x41820018
		opword 0x3800001E
		opword 0x38600012
		opword 0x90060018
		bl psndSFXOn
		opword 0x48000174
		opword 0x38000014
		opword 0x38600012
		opword 0x90060018
		bl psndSFXOn
		opword 0x48000160
		opword 0xA0060000
		opword 0x540006F7
		opword 0x40820154
		opword 0x3B400000
		opword 0x7F59D378
		bl cardGetFilePtr
		opword 0x38192000
		opword 0x7C63022E
		opword 0x546007FF
		opword 0x4182001C
		opword 0x546007BD
		opword 0x40820014
		opword 0x3B5A0001
		opword 0x3B394000
		opword 0x2C1A0004
		opword 0x4180FFD8
		opword 0x2C1A0004
		opword 0x40800028
		opword 0x38600012
		bl psndSFXOn
		lwz r3, wp(r13)
		opword 0x38800000
		opword 0x38000028
		opword 0x90830020
		lwz r3, wp(r13)
		opword 0x90030018
		opword 0x480000F4
		opword 0x38600013
		bl psndSFXOn
		opword 0x480000E8
		opword 0xA0060000
		opword 0x540006B5
		opword 0x408200DC
		opword 0x3B400000
		opword 0x7F59D378
		bl cardGetFilePtr
		opword 0x38192000
		opword 0x7C63022E
		opword 0x546007BD
		opword 0x4082000C
		opword 0x546007FF
		opword 0x41820014
		opword 0x3B5A0001
		opword 0x3B394000
		opword 0x2C1A0004
		opword 0x4180FFD8
		opword 0x2C1A0004
		opword 0x40800028
		opword 0x38600012
		bl psndSFXOn
		lwz r3, wp(r13)
		opword 0x38800000
		opword 0x38000032
		opword 0x90830020
		lwz r3, wp(r13)
		opword 0x90030018
		opword 0x4800007C
		opword 0x38600013
		bl psndSFXOn
		opword 0x48000070
		opword 0x38600013
		bl psndSFXOn
		lwz r3, wp(r13)
		opword 0x3800000A
		opword 0x90030018
		opword 0x48000058
		opword 0x38600012
		bl psndSFXOn
		opword 0x38600800
		bl psndBGMOff
		lwz r3, wp(r13)
		opword 0x38000064
		opword 0x90030018
		opword 0x48000038
		opword 0x38600012
		bl psndSFXOn
		lwz r3, wp(r13)
		opword 0x380000C8
		opword 0x90030018
		opword 0x48000020
		opword 0x578005AD
		opword 0x41820018
		opword 0x38600013
		bl psndSFXOn
		lwz r3, wp(r13)
		opword 0x3800000A
		opword 0x90030018
		lwz r3, wp(r13)
		opword 0x80030020
		opword 0x7C1F0000
		opword 0x41820020
		opword 0x2C000004
		opword 0x40800010
		opword 0x38600009
		bl psndSFXOn
		opword 0x4800000C
		opword 0x38600005
		bl psndSFXOn
		lwz r5, wp(r13)
		opword 0x389D0040
		opword 0x80050020
		opword 0x1C00001C
		opword 0x7C640214
		opword 0x7C24042E
		opword 0xC0030008
		opword 0xEC01002A
		opword 0xD0050010
		lwz r5, wp(r13)
		opword 0x80050020
		opword 0x1C00001C
		opword 0x7C640214
		opword 0xC0230004
		opword 0xC003000C
		opword 0xEC01002A
		opword 0xD0050014
		opword 0x48000EA4
		lwz r0, dat_8041bd6c(r2)
		la r5, _af_pad+20
		opword 0x3860001B
		opword 0x38800000
		opword 0x9001001C
		bl fadeEntry
		lwz r4, wp(r13)
		opword 0x80640018
		opword 0x38030001
		opword 0x90040018
		opword 0x48000E78
		bl fadeIsFinish
		opword 0x2C030000
		opword 0x41820E6C
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		bl seqSetSeq
		opword 0x48000E58
		opword 0xA0060000
		lis r3, evt_memcard_start@ha
		addi r3, r3, evt_memcard_start@l
		opword 0x38800000
		opword 0x60000040
		opword 0x38A00000
		opword 0xB0060000
		opword 0x38C00000
		bl evtEntryType
		lwz r4, wp(r13)
		opword 0x9064003C
		lwz r3, wp(r13)
		opword 0x80030020
		opword 0x8063003C
		opword 0x9003009C
		lwz r4, wp(r13)
		opword 0x80640018
		opword 0x38030001
		opword 0x90040018
		opword 0x48000E08
		opword 0x8066003C
		opword 0x8063015C
		bl evtCheckID
		opword 0x2C030000
		opword 0x40820DF4
		lwz r5, wp(r13)
		opword 0x3C60FD05
		opword 0x38830F80
		opword 0xA0050000
		opword 0x38600000
		opword 0x540006B0
		opword 0xB0050000
		bl evtGetValue
		opword 0x2C030001
		opword 0x40820018
		lwz r4, wp(r13)
		opword 0x80640018
		opword 0x38030001
		opword 0x90040018
		opword 0x48000DB8
		lwz r3, wp(r13)
		opword 0x38000001
		opword 0x90030018
		opword 0x48000DA8
		lwz r0, dat_8041bd70(r2)
		opword 0x38A10018
		opword 0x3860001B
		opword 0x38800000
		opword 0x90010018
		bl fadeEntry
		opword 0x38600200
		opword 0x388007D0
		opword 0x38A00000
		bl psndBGMOff_f_d
		lwz r4, wp(r13)
		opword 0x80640018
		opword 0x38030001
		opword 0x90040018
		opword 0x48000D6C
		bl fadeIsFinish
		opword 0x2C030000
		opword 0x41820D60
		lwz r7, wp(r13)
		la r3, evt_continue(r13)
		opword 0x38800000
		opword 0x38A00000
		opword 0xA0070000
		opword 0x38C00000
		opword 0x60000040
		opword 0xB0070000
		bl evtEntryType
		lwz r4, wp(r13)
		opword 0x9064003C
		lwz r4, wp(r13)
		opword 0x80640018
		opword 0x38030001
		opword 0x90040018
		opword 0x48000D20
		opword 0x8066003C
		opword 0x8063015C
		bl evtCheckID
		opword 0x2C030000
		opword 0x40820D0C
		lwz r3, wp(r13)
		opword 0xA0030000
		opword 0x540006B0
		opword 0xB0030000
		bl continueGame
		opword 0x48000CF4
		lwz r0, dat_8041bd74(r2)
		opword 0x38A10014
		opword 0x3860001B
		opword 0x38800000
		opword 0x90010014
		bl fadeEntry
		lwz r4, wp(r13)
		opword 0x80640018
		opword 0x38030001
		opword 0x90040018
		opword 0x48000CC8
		bl fadeIsFinish
		opword 0x2C030000
		opword 0x41820CBC
		lwz r4, wp(r13)
		opword 0x80640018
		opword 0x38030001
		opword 0x90040018
		opword 0x48000CA8
		bl nameEntPrepare
		opword 0x2C030000
		opword 0x41820C9C
		opword 0x38600000
		bl nameEntOn
		lwz r0, dat_8041bd78(r2)
		opword 0x38A10010
		opword 0x3860001C
		opword 0x38800000
		opword 0x90010010
		bl fadeEntry
		lwz r4, wp(r13)
		opword 0x80640018
		opword 0x38030001
		opword 0x90040018
		opword 0x48000C68
		bl fadeIsFinish
		opword 0x2C030000
		opword 0x41820C5C
		bl nameEntWait
		opword 0x2C030000
		opword 0x40820C50
		lwz r0, dat_8041bd7c(r2)
		opword 0x38A1000C
		opword 0x38600018
		opword 0x38800000
		opword 0x9001000C
		bl fadeEntry
		bl nameEntIsCancel
		opword 0x2C030000
		opword 0x40820014
		opword 0x38600200
		opword 0x38800BB8
		opword 0x38A00000
		bl psndBGMOff_f_d
		lwz r4, wp(r13)
		opword 0x80640018
		opword 0x38030001
		opword 0x90040018
		opword 0x48000C08
		bl fadeIsFinish
		opword 0x2C030000
		opword 0x41820BFC
		bl nameEntOff
		bl nameEntIsCancel
		opword 0x2C030000
		opword 0x4182002C
		lwz r0, dat_8041bd80(r2)
		opword 0x38A10008
		opword 0x3860001C
		opword 0x38800000
		opword 0x90010008
		bl fadeEntry
		lwz r3, wp(r13)
		opword 0x38000001
		opword 0x90030018
		opword 0x48000BC4
		bl nameEntGetName
		lwz r5, gp(r13)
		opword 0x7C641B78
		opword 0x386511BC
		bl strcpy
		lwz r4, wp(r13)
		lwz r3, gp(r13)
		opword 0x80040020
		opword 0x900311B8
		bl stg0_00_init
		lwz r4, wp(r13)
		lwz r3, gp(r13)
		opword 0x80040020
		opword 0x900311D0
		bl marioPartyKill
		bl marioGetPtr
		opword 0x38800000
		opword 0x38000019
		opword 0x98830243
		opword 0x98830244
		lwz r3, gp(r13)
		opword 0x90830110
		lwz r3, gp(r13)
		opword 0x90030108
		bl swInit
		opword 0x38600000
		opword 0x38800000
		bl swByteSet
		opword 0x2C1F0000
		opword 0x40820058
		lwz r4, wp(r13)
		lis r3, evt_memcard_save@ha
		lwz r6, gp(r13)
		addi r3, r3, evt_memcard_save@l
		opword 0x80040020
		opword 0x38800000
		opword 0x38A00000
		opword 0x900611D0
		opword 0x38C00000
		bl evtEntryType
		lwz r4, wp(r13)
		opword 0x38000017
		opword 0x9064003C
		lwz r3, wp(r13)
		opword 0x8063003C
		opword 0x9003009C
		lwz r4, wp(r13)
		opword 0x80640018
		opword 0x38030001
		opword 0x90040018
		opword 0x48000AF8
		opword 0x389E02C0
		opword 0x38BE02C8
		opword 0x38600003
		bl seqSetSeq
		opword 0x48000AE4
		opword 0x8066003C
		opword 0x8063015C
		bl evtCheckID
		opword 0x2C030000
		opword 0x40820AD0
		opword 0x389E02C0
		opword 0x38BE02C8
		opword 0x38600003
		bl seqSetSeq
		opword 0x48000ABC
		opword 0x387E0374
		bl msgSearch
		lwz r4, wp(r13)
		opword 0x576004E7
		opword 0x90640038
		lwz r3, wp(r13)
		opword 0x83E30020
		opword 0x4182001C
		opword 0x1C1F001C
		opword 0x389D013C
		opword 0x7C840214
		opword 0x88040018
		opword 0x90030020
		opword 0x48000108
		opword 0x576004A5
		opword 0x4182001C
		opword 0x1C1F001C
		opword 0x389D013C
		opword 0x7C840214
		opword 0x88040019
		opword 0x90030020
		opword 0x480000E8
		opword 0x57600463
		opword 0x4182001C
		opword 0x1C1F001C
		opword 0x389D013C
		opword 0x7C840214
		opword 0x8804001A
		opword 0x90030020
		opword 0x480000C8
		opword 0x57600421
		opword 0x4182001C
		opword 0x1C1F001C
		opword 0x389D013C
		opword 0x7C840214
		opword 0x8804001B
		opword 0x90030020
		opword 0x480000A8
		opword 0x578005EF
		opword 0x4182007C
		opword 0x2C1F0004
		opword 0x40800054
		bl cardGetFilePtr
		lwz r4, wp(r13)
		opword 0x80040020
		opword 0x54047022
		opword 0x38042000
		opword 0x7C63022E
		opword 0x546007BD
		opword 0x4082000C
		opword 0x546007FF
		opword 0x40820020
		opword 0x38600012
		bl psndSFXOn
		lwz r4, wp(r13)
		opword 0x80640018
		opword 0x38030001
		opword 0x90040018
		opword 0x48000054
		opword 0x38600013
		bl psndSFXOn
		opword 0x48000048
		opword 0x38800004
		opword 0x38000001
		opword 0x90830020
		opword 0x38600013
		lwz r4, wp(r13)
		opword 0x90040018
		bl psndSFXOn
		opword 0x48000028
		opword 0x578005AD
		opword 0x41820020
		opword 0x38800004
		opword 0x38000001
		opword 0x90830020
		opword 0x38600013
		lwz r4, wp(r13)
		opword 0x90040018
		bl psndSFXOn
		lwz r3, wp(r13)
		opword 0x80030020
		opword 0x7C1F0000
		opword 0x41820014
		opword 0x2C000004
		opword 0x4080000C
		opword 0x38600009
		bl psndSFXOn
		lwz r5, wp(r13)
		opword 0x389D013C
		opword 0x80050020
		opword 0x1C00001C
		opword 0x7C640214
		opword 0x7C24042E
		opword 0xC0030008
		opword 0xEC01002A
		opword 0xD0050010
		lwz r5, wp(r13)
		opword 0x80050020
		opword 0x1C00001C
		opword 0x7C640214
		opword 0xC0230004
		opword 0xC003000C
		opword 0xEC01002A
		opword 0xD0050014
		opword 0x48000918
		opword 0xA0060000
		lis r3, evt_memcard_delete@ha
		addi r3, r3, evt_memcard_delete@l
		opword 0x38800000
		opword 0x60000040
		opword 0x38A00000
		opword 0xB0060000
		opword 0x38C00000
		bl evtEntryType
		lwz r4, wp(r13)
		opword 0x9064003C
		lwz r3, wp(r13)
		opword 0x80030020
		opword 0x8063003C
		opword 0x9003009C
		lwz r4, wp(r13)
		opword 0x80640018
		opword 0x38030001
		opword 0x90040018
		opword 0x480008C8
		opword 0x8066003C
		opword 0x8063015C
		bl evtCheckID
		opword 0x2C030000
		opword 0x408208B4
		opword 0x3C80FAA3
		opword 0x38600000
		opword 0x3884B580
		bl evtGetValue
		opword 0x2C030000
		opword 0x40820030
		lwz r5, wp(r13)
		opword 0x38800004
		opword 0x38000001
		opword 0xA0650000
		opword 0x546306B0
		opword 0xB0650000
		lwz r3, wp(r13)
		opword 0x90830020
		lwz r3, wp(r13)
		opword 0x90030018
		opword 0x48000870
		lwz r4, wp(r13)
		opword 0x38000001
		opword 0xA0640000
		opword 0x60630080
		opword 0xB0640000
		opword 0x901A0004
		opword 0x480008F0
		opword 0x387E0390
		bl msgSearch
		lwz r4, wp(r13)
		opword 0x576004E7
		opword 0x90640038
		lwz r3, wp(r13)
		opword 0x83E30020
		opword 0x4182001C
		opword 0x1C1F001C
		opword 0x389D013C
		opword 0x7C840214
		opword 0x88040018
		opword 0x90030020
		opword 0x48000130
		opword 0x576004A5
		opword 0x4182001C
		opword 0x1C1F001C
		opword 0x389D013C
		opword 0x7C840214
		opword 0x88040019
		opword 0x90030020
		opword 0x48000110
		opword 0x57600463
		opword 0x4182001C
		opword 0x1C1F001C
		opword 0x389D013C
		opword 0x7C840214
		opword 0x8804001A
		opword 0x90030020
		opword 0x480000F0
		opword 0x57600421
		opword 0x4182001C
		opword 0x1C1F001C
		opword 0x389D013C
		opword 0x7C840214
		opword 0x8804001B
		opword 0x90030020
		opword 0x480000D0
		opword 0x578005EF
		opword 0x418200A4
		opword 0x2C1F0004
		opword 0x4080007C
		bl cardGetFilePtr
		lwz r5, wp(r13)
		opword 0x80050020
		opword 0x54047022
		opword 0x38042000
		opword 0x7C63022E
		opword 0x546007BD
		opword 0x408200A0
		opword 0x546007FF
		opword 0x40820098
		opword 0x38000033
		opword 0x38600012
		opword 0x90050018
		lwz r4, wp(r13)
		opword 0x80040020
		opword 0x90040030
		lwz r5, wp(r13)
		opword 0x80850030
		opword 0x38840001
		opword 0x5480F002
		opword 0x54840FFE
		opword 0x7C040050
		opword 0x5400103E
		opword 0x7C002214
		opword 0x90050034
		lwz r4, wp(r13)
		opword 0x80040034
		opword 0x90040020
		bl psndSFXOn
		opword 0x48000048
		opword 0x38800005
		opword 0x38000001
		opword 0x90830020
		opword 0x38600013
		lwz r4, wp(r13)
		opword 0x90040018
		bl psndSFXOn
		opword 0x48000028
		opword 0x578005AD
		opword 0x41820020
		opword 0x38800005
		opword 0x38000001
		opword 0x90830020
		opword 0x38600013
		lwz r4, wp(r13)
		opword 0x90040018
		bl psndSFXOn
		lwz r3, wp(r13)
		opword 0x80030020
		opword 0x7C1F0000
		opword 0x41820014
		opword 0x2C000004
		opword 0x4080000C
		opword 0x38600009
		bl psndSFXOn
		lwz r5, wp(r13)
		opword 0x389D013C
		opword 0x80050020
		opword 0x1C00001C
		opword 0x7C640214
		opword 0x7C24042E
		opword 0xC0030008
		opword 0xEC01002A
		opword 0xD0050010
		lwz r5, wp(r13)
		opword 0x80050020
		opword 0x1C00001C
		opword 0x7C640214
		opword 0xC0230004
		opword 0xC003000C
		opword 0xEC01002A
		opword 0xD0050014
		opword 0x48000688
		opword 0x387E03AC
		bl msgSearch
		lwz r4, wp(r13)
		opword 0x576004E7
		opword 0x90640038
		lwz r5, wp(r13)
		opword 0x83E50020
		opword 0x41820038
		opword 0x389D0200
		lwz r5, wp(r13)
		opword 0x80050020
		opword 0x1C60001C
		opword 0x38030018
		opword 0x7C0400AE
		opword 0x90050020
		lwz r5, wp(r13)
		opword 0x80650020
		opword 0x80050030
		opword 0x7C030000
		opword 0x4182FFD8
		opword 0x48000104
		opword 0x576004A5
		opword 0x41820038
		opword 0x389D0200
		lwz r5, wp(r13)
		opword 0x80050020
		opword 0x1C60001C
		opword 0x38030019
		opword 0x7C0400AE
		opword 0x90050020
		lwz r5, wp(r13)
		opword 0x80650020
		opword 0x80050030
		opword 0x7C030000
		opword 0x4182FFD8
		opword 0x480000C8
		opword 0x57600463
		opword 0x41820038
		opword 0x389D0200
		lwz r5, wp(r13)
		opword 0x80050020
		opword 0x1C60001C
		opword 0x3803001A
		opword 0x7C0400AE
		opword 0x90050020
		lwz r5, wp(r13)
		opword 0x80650020
		opword 0x80050030
		opword 0x7C030000
		opword 0x4182FFD8
		opword 0x4800008C
		opword 0x57600421
		opword 0x41820038
		opword 0x389D0200
		lwz r5, wp(r13)
		opword 0x80050020
		opword 0x1C60001C
		opword 0x3803001B
		opword 0x7C0400AE
		opword 0x90050020
		lwz r5, wp(r13)
		opword 0x80650020
		opword 0x80050030
		opword 0x7C030000
		opword 0x4182FFD8
		opword 0x48000050
		opword 0x578005EF
		opword 0x41820024
		opword 0x38000034
		opword 0x38600012
		opword 0x90050018
		lwz r4, wp(r13)
		opword 0x80040020
		opword 0x90040034
		bl psndSFXOn
		opword 0x48000028
		opword 0x578005AD
		opword 0x41820020
		opword 0x80850030
		opword 0x38000032
		opword 0x38600013
		opword 0x90850020
		lwz r4, wp(r13)
		opword 0x90040018
		bl psndSFXOn
		lwz r3, wp(r13)
		opword 0x80030020
		opword 0x7C1F0000
		opword 0x41820014
		opword 0x2C000004
		opword 0x4080000C
		opword 0x38600009
		bl psndSFXOn
		lwz r3, wp(r13)
		opword 0x389D013C
		opword 0x80030020
		opword 0x90030034
		lwz r5, wp(r13)
		opword 0x80050020
		opword 0x1C00001C
		opword 0x7C640214
		opword 0x7C24042E
		opword 0xC0030008
		opword 0xEC01002A
		opword 0xD0050010
		lwz r5, wp(r13)
		opword 0x80050020
		opword 0x1C00001C
		opword 0x7C640214
		opword 0xC0230004
		opword 0xC003000C
		opword 0xEC01002A
		opword 0xD0050014
		opword 0x480004C0
		opword 0xA0060000
		lis r3, evt_memcard_copy@ha
		addi r3, r3, evt_memcard_copy@l
		opword 0x38800000
		opword 0x60000040
		opword 0x38A00000
		opword 0xB0060000
		opword 0x38C00000
		bl evtEntryType
		lwz r4, wp(r13)
		opword 0x9064003C
		lwz r3, wp(r13)
		opword 0x80030030
		opword 0x8063003C
		opword 0x9003009C
		lwz r3, wp(r13)
		opword 0x80030034
		opword 0x8063003C
		opword 0x900300A0
		lwz r4, wp(r13)
		opword 0x80640018
		opword 0x38030001
		opword 0x90040018
		opword 0x48000460
		opword 0x8066003C
		opword 0x8063015C
		bl evtCheckID
		opword 0x2C030000
		opword 0x4082044C
		opword 0x3C80FAA3
		opword 0x38600000
		opword 0x3884B580
		bl evtGetValue
		opword 0x2C030000
		opword 0x40820030
		lwz r5, wp(r13)
		opword 0x38800005
		opword 0x38000001
		opword 0xA0650000
		opword 0x546306B0
		opword 0xB0650000
		lwz r3, wp(r13)
		opword 0x90830020
		lwz r3, wp(r13)
		opword 0x90030018
		opword 0x48000408
		lwz r4, wp(r13)
		opword 0x38000001
		opword 0xA0640000
		opword 0x60630080
		opword 0xB0640000
		opword 0x901A0004
		opword 0x48000488
		opword 0xA0660000
		opword 0x576004E7
		opword 0x60600001
		opword 0xB0060000
		lwz r4, wp(r13)
		opword 0x83240024
		opword 0x41820018
		opword 0x3819FFFF
		opword 0x38600005
		opword 0x90040024
		bl psndSFXOn
		opword 0x48000168
		opword 0x576004A5
		opword 0x41820018
		opword 0x38190001
		opword 0x38600005
		opword 0x90040024
		bl psndSFXOn
		opword 0x4800014C
		opword 0x578005EF
		opword 0x418200D4
		opword 0x2C190001
		opword 0x41820038
		opword 0x40800010
		opword 0x2C190000
		opword 0x40800014
		opword 0x48000054
		opword 0x2C190003
		opword 0x4080004C
		opword 0x48000034
		opword 0x38600000
		bl OSSetSoundMode
		lwz r3, gp(r13)
		opword 0x38000000
		opword 0x90031274
		opword 0x48000030
		opword 0x38600001
		bl OSSetSoundMode
		lwz r3, gp(r13)
		opword 0x38000000
		opword 0x90031274
		opword 0x48000018
		opword 0x38600001
		bl OSSetSoundMode
		lwz r3, gp(r13)
		opword 0x38000001
		opword 0x90031274
		bl OSGetSoundMode
		opword 0x28030000
		opword 0x40820010
		opword 0x38600000
		bl SoundSetOutputMode
		opword 0x4800000C
		opword 0x38600001
		bl SoundSetOutputMode
		opword 0x38600012
		bl psndSFXOn
		opword 0x386000A0
		opword 0x38800000
		bl psndBGMOn
		opword 0x38600200
		bl psndENVOff
		lwz r4, wp(r13)
		opword 0x38000001
		opword 0x80640024
		opword 0x90640040
		lwz r4, wp(r13)
		opword 0xA0640000
		opword 0x5463043C
		opword 0xB0640000
		lwz r3, wp(r13)
		opword 0x90030018
		opword 0x480002C8
		opword 0x578005AD
		opword 0x4182006C
		opword 0x38600013
		bl psndSFXOn
		opword 0x386000A0
		opword 0x38800000
		bl psndBGMOn
		opword 0x38600200
		bl psndENVOff
		lwz r3, wp(r13)
		opword 0x80030040
		opword 0x90030024
		bl OSGetSoundMode
		opword 0x28030000
		opword 0x40820010
		opword 0x38600000
		bl SoundSetOutputMode
		opword 0x4800000C
		opword 0x38600001
		bl SoundSetOutputMode
		lwz r4, wp(r13)
		opword 0x38000001
		opword 0xA0640000
		opword 0x5463043C
		opword 0xB0640000
		lwz r3, wp(r13)
		opword 0x90030018
		opword 0x48000258
		lwz r3, wp(r13)
		opword 0x80030024
		opword 0x2C000003
		opword 0x4180000C
		opword 0x38000000
		opword 0x90030024
		lwz r3, wp(r13)
		opword 0x80030024
		opword 0x2C000000
		opword 0x4080000C
		opword 0x38000002
		opword 0x90030024
		lwz r3, wp(r13)
		opword 0x80030024
		opword 0x7C00C800
		opword 0x41820054
		opword 0x2C000001
		opword 0x4182002C
		opword 0x40800010
		opword 0x2C000000
		opword 0x40800014
		opword 0x48000030
		opword 0x2C000003
		opword 0x40800028
		opword 0x4800001C
		opword 0x38600000
		bl SoundSetOutputMode
		opword 0x48000018
		opword 0x38600001
		bl SoundSetOutputMode
		opword 0x4800000C
		opword 0x38600002
		bl SoundSetOutputMode
		opword 0x38600110
		opword 0x38800075
		bl psndENVOn
		lfs f0, float_neg74_8041be74(r2)
		opword 0x3C004330
		lwz r3, wp(r13)
		opword 0x90010020
		opword 0xC83E0358
		opword 0xD0030010
		lfs f2, float_50_8041be6c(r2)
		lwz r3, wp(r13)
		lfs f3, float_4_8041be78(r2)
		opword 0x80030024
		opword 0x6C008000
		opword 0x90010024
		opword 0xC8010020
		opword 0xEC000828
		opword 0xEC02103C
		opword 0xEC03002A
		opword 0xD0030014
		opword 0x48000180
		opword 0xA0660000
		opword 0x576004E7
		opword 0x60600001
		opword 0xB0060000
		opword 0x41820020
		lwz r5, wp(r13)
		opword 0x38600005
		opword 0x80850028
		opword 0x3804FFFF
		opword 0x90050028
		bl psndSFXOn
		opword 0x480000D8
		opword 0x576004A5
		opword 0x41820020
		lwz r5, wp(r13)
		opword 0x38600005
		opword 0x80850028
		opword 0x38040001
		opword 0x90050028
		bl psndSFXOn
		opword 0x480000B4
		opword 0x578005EF
		opword 0x41820074
		lwz r5, wp(r13)
		opword 0x38600012
		lwz r4, gp(r13)
		opword 0x80050028
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x90041294
		bl psndSFXOn
		lwz r4, wp(r13)
		opword 0x38000001
		opword 0x80640028
		opword 0x90640044
		lwz r4, wp(r13)
		opword 0xA0640000
		opword 0x5463043C
		opword 0xB0640000
		lwz r3, wp(r13)
		opword 0x90030018
		lwz r3, gp(r13)
		opword 0x80031294
		opword 0x2C000000
		opword 0x41820054
		la r3, evt_shake(r13)
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		bl evtEntryType
		opword 0x4800003C
		opword 0x578005AD
		opword 0x41820034
		opword 0x38600013
		bl psndSFXOn
		lwz r4, wp(r13)
		opword 0x38000001
		opword 0x80640044
		opword 0x90640028
		lwz r4, wp(r13)
		opword 0xA0640000
		opword 0x5463043C
		opword 0xB0640000
		lwz r3, wp(r13)
		opword 0x90030018
		lwz r3, wp(r13)
		opword 0x80030028
		opword 0x2C000002
		opword 0x4180000C
		opword 0x38000000
		opword 0x90030028
		lwz r3, wp(r13)
		opword 0x80030028
		opword 0x2C000000
		opword 0x4080000C
		opword 0x38000001
		opword 0x90030028
		lfs f0, float_neg74_8041be74(r2)
		opword 0x3C004330
		lwz r3, wp(r13)
		opword 0x90010020
		opword 0xC85E0358
		opword 0xD0030010
		lfs f3, float_50_8041be6c(r2)
		lwz r3, wp(r13)
		lfs f0, float_30_8041be3c(r2)
		opword 0x80030028
		lfs f4, float_4_8041be78(r2)
		opword 0x6C008000
		opword 0x90010024
		opword 0xC8210020
		opword 0xEC211028
		opword 0xEC03007C
		opword 0xEC04002A
		opword 0xD0030014
		lwz r3, wp(r13)
		opword 0x3C004330
		lfs f4, float_0p25_8041be7c(r2)
		opword 0xC0030010
		opword 0xC0630008
		opword 0x90010020
		opword 0xEC201828
		opword 0xC85E0350
		lfs f0, float_0p125_8041be80(r2)
		opword 0xEC21193A
		opword 0xD0230008
		lwz r3, wp(r13)
		opword 0xC0230014
		opword 0xC063000C
		opword 0xEC211828
		opword 0xEC21193A
		opword 0xD023000C
		lwz r3, gp(r13)
		opword 0x8003001C
		opword 0x90010024
		opword 0xC8210020
		opword 0xEC211028
		opword 0xEC210032
		bl sin
		opword 0xFC400818
		lfs f0, float_2_8041be70(r2)
		lis r3, loadDraw@ha
		lwz r7, wp(r13)
		addi r5, r3, loadDraw@l
		lfs f1, float_1000_8041be84(r2)
		opword 0xEC0000B2
		opword 0xC0470008
		opword 0x38600004
		opword 0x38800000
		opword 0x38C00000
		opword 0xFC000210
		opword 0xEC02002A
		opword 0xD0070008
		bl dispEntry
	}
}
#pragma pop
#endif

#define GXFIFO_F32 (*(volatile f32*)0xCC008000)

#ifdef NONMATCHING
static inline void loadDrawBg(u32 id, f32 x0, f32 y0, f32 x1, f32 y1) {
    GXTexObj obj;
    Mtx m;
    f64 w;
    f64 h;

    TEXGetGXTexObjFromPalette(*wp->file->data, &obj, id);
    GXInitTexObjLOD(&obj, GX_LINEAR, GX_LINEAR, EXT_LIT(float_0_8041bde4, 0.0f), EXT_LIT(float_0_8041bde4, 0.0f), EXT_LIT(float_0_8041bde4, 0.0f), GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    h = __fabs(y0 - y1);
    w = __fabs(x1 - x0);
    PSMTXScale(m, (f32)w / GXGetTexObjWidth(&obj), (f32)h / GXGetTexObjHeight(&obj), EXT_LIT(float_1_8041bde8, 1.0f));
    GXLoadTexMtxImm(m, GX_TEXMTX0, GX_MTX2x4);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXFIFO_F32 = x0;
    GXFIFO_F32 = y0;
    GXFIFO_F32 = EXT_LIT(float_0_8041bde4, 0.0f);
    GXFIFO_F32 = EXT_LIT(float_0_8041bde4, 0.0f);
    GXFIFO_F32 = EXT_LIT(float_0_8041bde4, 0.0f);
    GXFIFO_F32 = x0;
    GXFIFO_F32 = y1;
    GXFIFO_F32 = EXT_LIT(float_0_8041bde4, 0.0f);
    GXFIFO_F32 = EXT_LIT(float_0_8041bde4, 0.0f);
    GXFIFO_F32 = EXT_LIT(float_1_8041bde8, 1.0f);
    GXFIFO_F32 = x1;
    GXFIFO_F32 = y1;
    GXFIFO_F32 = EXT_LIT(float_0_8041bde4, 0.0f);
    GXFIFO_F32 = EXT_LIT(float_1_8041bde8, 1.0f);
    GXFIFO_F32 = EXT_LIT(float_1_8041bde8, 1.0f);
    GXFIFO_F32 = x1;
    GXFIFO_F32 = y0;
    GXFIFO_F32 = EXT_LIT(float_0_8041bde4, 0.0f);
    GXFIFO_F32 = EXT_LIT(float_1_8041bde8, 1.0f);
    GXFIFO_F32 = EXT_LIT(float_0_8041bde4, 0.0f);
}
#endif

#ifdef NONMATCHING
void loadDraw(CameraId camera, void* param) {
    CameraEntry* cam = camGetPtr(CAMERA_2D);
    GXColor white = {255, 255, 255, 255};
    GXColor gray = {160, 160, 160, 255};
    GXColor dark = {128, 128, 128, 128};
    f32 vp[6];
    f32 proj[7];
    CameraEntry saved;
    char buf[0x20];
    char buf2[0x100];
    Mtx m;
    Mtx s;
    f32 x;
    f32 y;
    f32 w;
    f32* py;
    u64 sec;
    WinDt* win;
    WinDt* win1;
    s32 i;
    s32 j;
    s32 k;

    if (wp->unk18 >= 0x20 && wp->unk18 < 0x28) {
        return;
    }
    GXGetViewportv(vp);
    GXGetProjectionv(proj);
    GXSetProjection(cam->projection, cam->projType);
    saved = *camGetCurPtr();
    *camGetCurPtr() = *cam;
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
    GXSetZCompLoc(GX_FALSE);
    GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetFog(GX_FOG_NONE, EXT_LIT(float_0_8041bde4, 0.0f), EXT_LIT(float_0_8041bde4, 0.0f), EXT_LIT(float_0_8041bde4, 0.0f), EXT_LIT(float_0_8041bde4, 0.0f), (GXColor){255, 255, 255, 255});
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    loadDrawBg(0x35, EXT_LIT(float_neg304_8041bdec, -304.0f), EXT_LIT(float_240_8041bdf0, 240.0f), EXT_LIT(float_neg272_8041bdf8, -272.0f), EXT_LIT(float_neg240_8041bdf4, -240.0f));
    loadDrawBg(0x34, EXT_LIT(float_neg272_8041bdf8, -272.0f), EXT_LIT(float_240_8041bdf0, 240.0f), EXT_LIT(float_272_8041bdfc, 272.0f), EXT_LIT(float_neg240_8041bdf4, -240.0f));
    loadDrawBg(0x36, EXT_LIT(float_272_8041bdfc, 272.0f), EXT_LIT(float_240_8041bdf0, 240.0f), EXT_LIT(float_304_8041be00, 304.0f), EXT_LIT(float_neg240_8041bdf4, -240.0f));

    win1 = win = win_dt;
    for (i = 0; i < 9; i++) {
        GXColor col = gray;
        if (i == wp->slot) {
            col = white;
        }
        if (wp->unk18 == 0x33 && (i == wp->unk30 || i == wp->unk34)) {
            col = white;
        }
        if (i == 4 && (wp->flags & 0x10)) {
            col = dark;
        }
        if (i == 5 && (wp->flags & 0x20)) {
            col = dark;
        }
        switch (win[i].unk10) {
            case 10:
            case 11:
            case 12:
            case 13: {
                col.a = 0xfe;
                winTexInit(*wp->file->data);
                winTexSet(0xe, (Vec){win[i].x, win[i].y, EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, col);
                winTexInit(*wp->file->data);
                winTexSet(win[i].unk10, (Vec){win[i].x, EXT_LIT(float_60_8041be04, 60.0f) + win[i].y, EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, col);
                break;
            }
            default: {
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(win[i].unk10, win[i].unk14, (Vec){win[i].x, win[i].y, EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, col);
                break;
            }
        }
    }

    windowDispGX_Waku_col(0, (GXColor){255, 255, 255, 255}, EXT_LIT(float_neg250_8041be08, -250.0f), EXT_LIT(float_200_8041be0c, 200.0f), EXT_LIT(float_500_8041be10, 500.0f), EXT_LIT(float_40_8041be14, 40.0f), EXT_LIT(float_20_8041be18, 20.0f));
    FontDrawStart();
    {
        const char* msg = wp->msg;
        FontDrawMessage(-FontGetMessageWidth(msg) / 2, 192, msg);
    }

    for (i = 0; i < 4; i++, win1++) {
        CardSaveSlot* save = &cardGetFilePtr()->saves[i];
        u16 flags = save->data.flags;
        s16 level = save->data.pouch.level;
        OSTime time = save->data.global.retraceLocalTime;
        u16 stars = *(u16*)&save->data.pouch.mStarPowersObtained;
        s32 gsw0 = save->data.global.mGSW0;
        char* name = (char*)save->data.global.field_0x11BC;
        const char* str;
        s32 hours;
        s32 mins;

        FontDrawStart();
        FontDrawColor((GXColor){192, 192, 192, 255});
        if (i == wp->slot) {
            FontDrawColor((GXColor){255, 255, 255, 255});
        }
        FontDrawScale(EXT_LIT(float_0p6_8041be1c, 0.6f));
        FontDrawEdge();
        sprintf(buf, str_802ED960, winZenkakuStr(i + 1));
        FontDrawString(win1->x - 100.0f, EXT_LIT(float_84_8041be24, 84.0f) + win1->y, buf);
        FontDrawEdgeOff();
        FontDrawScale(EXT_LIT(float_1_8041bde8, 1.0f));
        FontDrawColor((GXColor){32, 32, 32, 255});
        if (i == wp->slot) {
            FontDrawColor((GXColor){0, 0, 0, 255});
        }
        if (flags & 2) {
            str = str_802ED96C;
            FontDrawString(win1->x - FontGetMessageWidth(str) / EXT_LIT(float_2_8041be70, 2.0f), EXT_LIT(float_12_8041be2c, 12.0f) + win1->y, str);
        } else if (flags & 1) {
            str = str_802ED97C;
            FontDrawString(win1->x - FontGetMessageWidth(str) / EXT_LIT(float_2_8041be70, 2.0f), EXT_LIT(float_12_8041be2c, 12.0f) + win1->y, str);
        } else if (gsw0 == 0) {
            str = str_802ED98C;
            FontDrawString(win1->x - FontGetMessageWidth(str) / EXT_LIT(float_2_8041be70, 2.0f), EXT_LIT(float_12_8041be2c, 12.0f) + win1->y, str);
            if (strlen(name) != 0) {
                FontDrawString(win1->x - FontGetMessageWidth(name) / 2, 70.0f + win1->y, name);
            }
        } else {
            FontGetMessageWidth("\x82\x57\x82\x57");
            sec = OSTicksToSeconds(time);
            if (sec > 359999) {
                hours = 99;
                mins = 59;
            } else {
                hours = (u64)sec / 3600;
                mins = ((u64)sec % 3600) / 60;
            }
            if (strlen(name) != 0) {
                FontDrawString(win1->x - FontGetMessageWidth(name) / 2, 70.0f + win1->y, name);
            }
            sprintf(buf2, str_802ED998, winZenkakuStr(level));
            FontDrawString(win1->x - FontGetMessageWidth(buf2) / EXT_LIT(float_2_8041be70, 2.0f), EXT_LIT(float_30_8041be3c, 30.0f) + win1->y, buf2);
            strcpy(buf2, str_802ED9A4);
            strcat(buf2, unk_8016af5c(hours, 2));
            strcat(buf2, " ");
            strcat(buf2, unk_8016af5c(mins, 2));
            w = FontGetMessageWidth(buf2);
            FontDrawString(win1->x - w / EXT_LIT(float_2_8041be70, 2.0f), win1->y, buf2);
            strcpy(buf2, str_802ED9A4);
            strcat(buf2, unk_8016af5c(hours, 2));
            x = FontGetMessageWidth(buf2);
            PSMTXTrans(m, EXT_LIT(float_8_8041be44, 8.0f) + (x + (win1->x - w / EXT_LIT(float_2_8041be70, 2.0f))), EXT_LIT(float_1_8041bde8, 1.0f) + (win1->y - 22.0f), EXT_LIT(float_0_8041bde4, 0.0f));
            PSMTXScale(s, EXT_LIT(float_1p5_8041be4c, 1.5f), EXT_LIT(float_1p5_8041be4c, 1.5f), EXT_LIT(float_1p5_8041be4c, 1.5f));
            PSMTXConcat(m, s, m);
            iconDispGxCol(m, 0, 0x201, (GXColor){0, 0, 0, 255});
            py = &win1->y;
            for (k = 0; k < 7; k++) {
                if (stars & (1 << (k + 1))) {
                    PSMTXTrans(m, (win1->x - 106.0f) + k * 32, *py - 52.0f, 0.0f);
                    iconDispGxCol(m, 0, (u16)stone_id[k], i == wp->slot ? white : gray);
                }
            }
        }
    }

    if (wp->flags & 1) {
        wp->alpha += 0.05f;
    } else {
        wp->alpha -= 0.05f;
    }
    if (wp->alpha < EXT_LIT(float_0_8041bde4, 0.0f)) {
        wp->alpha = 0.0f;
    }
    if (wp->alpha > EXT_LIT(float_1_8041bde8, 1.0f)) {
        wp->alpha = 1.0f;
    }
    nameMaskGX(wp->alpha);

    if (wp->unk18 >= 100 && wp->unk18 < 200) {
        winTexInit(*wp->file->data);
        winTexSet(0xf, (Vec){EXT_LIT(float_0_8041bde4, 0.0f), EXT_LIT(float_0_8041bde4, 0.0f), EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, (GXColor){255, 255, 255, 255});
        winTexInit_x2(*wp->file->data);
        winTexSet_x2(0x13, 0x1f, (Vec){EXT_LIT(float_0_8041bde4, 0.0f), EXT_LIT(float_100_8041be20, 100.0f), EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, (GXColor){255, 255, 255, 255});
        for (i = 0; i < 3; i++) {
            if (i == wp->unk24) {
                winTexInit(*wp->file->data);
                winTexSet(0x33, (Vec){EXT_LIT(float_0_8041bde4, 0.0f), 50 - i * 50, EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, (GXColor){0, 0, 0, 64});
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(i + 0x15, 0x33, (Vec){-4.0f, 54 - i * 50, EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, (GXColor){255, 255, 255, 255});
            } else {
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(i + 0x15, 0x33, (Vec){EXT_LIT(float_0_8041bde4, 0.0f), 50 - i * 50, EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, (GXColor){255, 255, 255, 255});
            }
        }
    }

    if (wp->unk18 >= 200 && wp->unk18 < 300) {
        winTexInit(*wp->file->data);
        winTexSet(0xf, (Vec){EXT_LIT(float_0_8041bde4, 0.0f), EXT_LIT(float_0_8041bde4, 0.0f), EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, (GXColor){255, 255, 255, 255});
        winTexInit_x2(*wp->file->data);
        winTexSet_x2(0x14, 0x1f, (Vec){EXT_LIT(float_0_8041bde4, 0.0f), EXT_LIT(float_100_8041be20, 100.0f), EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, (GXColor){255, 255, 255, 255});
        for (i = 0; i < 2; i++) {
            if (i == wp->unk28) {
                winTexInit(*wp->file->data);
                winTexSet(0x33, (Vec){EXT_LIT(float_0_8041bde4, 0.0f), 30 - i * 50, EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, (GXColor){0, 0, 0, 64});
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(i + 0x18, 0x33, (Vec){-4.0f, 34 - i * 50, EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, (GXColor){255, 255, 255, 255});
            } else {
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(i + 0x18, 0x33, (Vec){EXT_LIT(float_0_8041bde4, 0.0f), 30 - i * 50, EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, (GXColor){255, 255, 255, 255});
            }
        }
    }

    if (wp->unk18 == 0x33 && wp->unk34 < 4) {
        f32 angle[4][4] = {
            {0.0f, -90.0f, -180.0f, -135.0f},
            {90.0f, 0.0f, 135.0f, 180.0f},
            {0.0f, -45.0f, 0.0f, -90.0f},
            {45.0f, 0.0f, 90.0f, 0.0f},
        };
        f32 cx;
        f32 cy;
        if (!(f32)fmod(angle[wp->unk30][wp->unk34], 90.0)) {
            f32 c0 = wp->unk30 % 2;
            f32 r0 = wp->unk30 / 2;
            f32 r1 = wp->unk34 / 2;
            if (r0 == r1) {
                cx = 0.0f;
                cy = EXT_LIT(float_120_8041be5c, 120.0f) - 140.0f * r0;
            } else {
                cx = -150.0f + 300.0f * c0;
                cy = EXT_LIT(float_50_8041be6c, 50.0f);
            }
        } else {
            cx = 0.0f;
            cy = EXT_LIT(float_50_8041be6c, 50.0f);
        }
        cy -= EXT_LIT(float_40_8041be14, 40.0f);
        winTexInit(*wp->file->data);
        winTexSetRot(0x1d, (Vec){EXT_LIT(float_2_8041be70, 2.0f) + cx, cy - 2.0f, EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, (GXColor){0, 0, 0, 128}, angle[wp->unk30][wp->unk34]);
        winTexSetRot(0x1d, (Vec){cx, cy, EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, white, angle[wp->unk30][wp->unk34]);
    }

    if (!(wp->flags & 0x40)) {
        winTexInit(*wp->file->data);
        winTexSet(0, (Vec){EXT_LIT(float_2_8041be70, 2.0f) + wp->x, wp->y - 2.0f, EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, (GXColor){0, 0, 0, 128});
        winTexSet(0, (Vec){wp->x, wp->y, EXT_LIT(float_0_8041bde4, 0.0f)}, (Vec){EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f), EXT_LIT(float_1_8041bde8, 1.0f)}, white);
    }

    GXSetViewport(vp[0], vp[1], vp[2], vp[3], vp[4], vp[5]);
    GXSetProjectionv(proj);
    *camGetCurPtr() = saved;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void loadDraw(CameraId camera, void* param) {
	char _af_pad[2080];
	asm volatile {
		lis r4, vec3_802ed670@ha
		opword 0x38600008
		addi r30, r4, vec3_802ed670@l
		bl camGetPtr
		lwz r4, dat_8041bd84(r2)
		opword 0x7C791B78
		lwz r0, dat_8041bd88(r2)
		stw r4, _af_pad+112(r1)
		lwz r3, wp(r13)
		opword 0x90010074
		lwz r0, dat_8041bd8c(r2)
		opword 0x80630018
		opword 0x90010070
		opword 0x2C030020
		opword 0x4180000C
		opword 0x2C030028
		opword 0x418018E4
		opword 0x3861034C
		bl GXGetViewportv
		opword 0x38610330
		bl GXGetProjectionv
		opword 0x8099019C
		opword 0x3879015C
		bl GXSetProjection
		bl camGetCurPtr
		opword 0x3800004C
		opword 0x38A10594
		opword 0x3883FFFC
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		bl camGetCurPtr
		opword 0x3800004C
		opword 0x38A3FFFC
		opword 0x3899FFFC
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00000
		opword 0x38C00000
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
		opword 0x38800007
		opword 0x38A00000
		bl GXSetZMode
		lfs f1, float_0_8041bde4(r2)
		opword 0x38810068
		lwz r0, dat_8041bd90(r2)
		opword 0x38600000
		opword 0xFC400890
		opword 0xFC600890
		opword 0x90010068
		opword 0xFC800890
		bl GXSetFog
		opword 0x38600000
		bl GXSetNumChans
		opword 0x38600004
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0x39000000
		opword 0x39200002
		bl GXSetChanCtrl
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
		bl GXSetCullMode
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
		opword 0x3879011C
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		lwz r3, wp(r13)
		opword 0x388102F0
		opword 0x38A00035
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl TEXGetGXTexObjFromPalette
		lfs f1, float_0_8041bde4(r2)
		opword 0x386102F0
		opword 0x38800001
		opword 0x38A00001
		opword 0xFC400890
		opword 0x38C00000
		opword 0xFC600890
		opword 0x38E00000
		opword 0x39000000
		bl GXInitTexObjLOD
		opword 0x386102F0
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x38600001
		bl GXSetNumTexGens
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0001E
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0xC83E02D8
		opword 0x386102F0
		opword 0xC81E02E0
		opword 0xFFC00A10
		opword 0xFFE00210
		bl GXGetTexObjHeight
		opword 0x5463043E
		opword 0x3C004330
		opword 0x906107FC
		opword 0xFC00F018
		opword 0xC85E0350
		opword 0x386102F0
		opword 0x900107F8
		opword 0xC82107F8
		opword 0xEC211028
		opword 0xEFC00824
		bl GXGetTexObjWidth
		opword 0x5463043E
		opword 0x3C004330
		opword 0x90610804
		opword 0xFC00F818
		opword 0xC89E0350
		opword 0xFC40F090
		opword 0x90010800
		opword 0x386103C4
		lfs f3, float_1_8041bde8(r2)
		opword 0xC8210800
		opword 0xEC212028
		opword 0xEC200824
		bl PSMTXScale
		opword 0x386103C4
		opword 0x3880001E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x38600080
		opword 0x38800000
		opword 0x38A00004
		bl GXBegin
		lfs f0, float_neg304_8041bdec(r2)
		opword 0x3C60CC01
		opword 0x388102D0
		opword 0x38A00034
		opword 0xD0038000
		lfs f0, float_240_8041bdf0(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lfs f0, float_neg304_8041bdec(r2)
		opword 0xD0038000
		lfs f0, float_neg240_8041bdf4(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lfs f0, float_1_8041bde8(r2)
		opword 0xD0038000
		lfs f0, float_neg272_8041bdf8(r2)
		opword 0xD0038000
		lfs f0, float_neg240_8041bdf4(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lfs f0, float_1_8041bde8(r2)
		opword 0xD0038000
		lfs f0, float_1_8041bde8(r2)
		opword 0xD0038000
		lfs f0, float_neg272_8041bdf8(r2)
		opword 0xD0038000
		lfs f0, float_240_8041bdf0(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lfs f0, float_1_8041bde8(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lwz r3, wp(r13)
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl TEXGetGXTexObjFromPalette
		lfs f1, float_0_8041bde4(r2)
		opword 0x386102D0
		opword 0x38800001
		opword 0x38A00001
		opword 0xFC400890
		opword 0x38C00000
		opword 0xFC600890
		opword 0x38E00000
		opword 0x39000000
		bl GXInitTexObjLOD
		opword 0x386102D0
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x38600001
		bl GXSetNumTexGens
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0001E
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0xC83E02D8
		opword 0x386102D0
		opword 0xC81E02E8
		opword 0xFFC00A10
		opword 0xFFE00210
		bl GXGetTexObjHeight
		opword 0x5463043E
		opword 0x3C004330
		opword 0x9061080C
		opword 0xFC00F018
		opword 0xC85E0350
		opword 0x386102D0
		opword 0x90010808
		opword 0xC8210808
		opword 0xEC211028
		opword 0xEFC00824
		bl GXGetTexObjWidth
		opword 0x5463043E
		opword 0x3C004330
		opword 0x90610814
		opword 0xFC00F818
		opword 0xC89E0350
		opword 0xFC40F090
		opword 0x90010810
		opword 0x38610394
		lfs f3, float_1_8041bde8(r2)
		opword 0xC8210810
		opword 0xEC212028
		opword 0xEC200824
		bl PSMTXScale
		opword 0x38610394
		opword 0x3880001E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x38600080
		opword 0x38800000
		opword 0x38A00004
		bl GXBegin
		lfs f0, float_neg272_8041bdf8(r2)
		opword 0x3C60CC01
		opword 0x388102B0
		opword 0x38A00036
		opword 0xD0038000
		lfs f0, float_240_8041bdf0(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lfs f0, float_neg272_8041bdf8(r2)
		opword 0xD0038000
		lfs f0, float_neg240_8041bdf4(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lfs f0, float_1_8041bde8(r2)
		opword 0xD0038000
		lfs f0, float_272_8041bdfc(r2)
		opword 0xD0038000
		lfs f0, float_neg240_8041bdf4(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lfs f0, float_1_8041bde8(r2)
		opword 0xD0038000
		lfs f0, float_1_8041bde8(r2)
		opword 0xD0038000
		lfs f0, float_272_8041bdfc(r2)
		opword 0xD0038000
		lfs f0, float_240_8041bdf0(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lfs f0, float_1_8041bde8(r2)
		opword 0xD0038000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0038000
		lwz r3, wp(r13)
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl TEXGetGXTexObjFromPalette
		lfs f1, float_0_8041bde4(r2)
		opword 0x386102B0
		opword 0x38800001
		opword 0x38A00001
		opword 0xFC400890
		opword 0x38C00000
		opword 0xFC600890
		opword 0x38E00000
		opword 0x39000000
		bl GXInitTexObjLOD
		opword 0x386102B0
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x38600001
		bl GXSetNumTexGens
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0001E
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0xC83E02D8
		opword 0x386102B0
		opword 0xC81E02E0
		opword 0xFFC00A10
		opword 0xFFE00210
		bl GXGetTexObjHeight
		opword 0x5463043E
		opword 0x3C004330
		opword 0x9061081C
		opword 0xFC00F018
		opword 0xC85E0350
		opword 0x386102B0
		opword 0x90010818
		opword 0xC8210818
		opword 0xEC211028
		opword 0xEFC00824
		bl GXGetTexObjWidth
		opword 0x5463043E
		opword 0x3C004330
		opword 0x90610824
		opword 0xFC00F818
		opword 0xC89E0350
		opword 0xFC40F090
		opword 0x90010820
		opword 0x38610364
		lfs f3, float_1_8041bde8(r2)
		opword 0xC8210820
		opword 0xEC212028
		opword 0xEC200824
		bl PSMTXScale
		opword 0x38610364
		opword 0x3880001E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x38600080
		opword 0x38800000
		opword 0x38A00004
		bl GXBegin
		lfs f0, float_272_8041bdfc(r2)
		opword 0x3C80CC01
		lis r3, win_dt@ha
		opword 0x3AE00000
		opword 0xD0048000
		addi r28, r3, win_dt@l
		lfs f0, float_240_8041bdf0(r2)
		opword 0x7F99E378
		opword 0xD0048000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0048000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0048000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0048000
		lfs f0, float_272_8041bdfc(r2)
		opword 0xD0048000
		lfs f0, float_neg240_8041bdf4(r2)
		opword 0xD0048000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0048000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0048000
		lfs f0, float_1_8041bde8(r2)
		opword 0xD0048000
		lfs f0, float_304_8041be00(r2)
		opword 0xD0048000
		lfs f0, float_neg240_8041bdf4(r2)
		opword 0xD0048000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0048000
		lfs f0, float_1_8041bde8(r2)
		opword 0xD0048000
		lfs f0, float_1_8041bde8(r2)
		opword 0xD0048000
		lfs f0, float_304_8041be00(r2)
		opword 0xD0048000
		lfs f0, float_240_8041bdf0(r2)
		opword 0xD0048000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0048000
		lfs f0, float_1_8041bde8(r2)
		opword 0xD0048000
		lfs f0, float_0_8041bde4(r2)
		opword 0xD0048000
		lwz r4, wp(r13)
		opword 0x80610074
		opword 0x80040020
		opword 0x9061006C
		opword 0x7C170000
		opword 0x4082000C
		opword 0x80010078
		opword 0x9001006C
		opword 0x80040018
		opword 0x2C000033
		opword 0x40820024
		opword 0x80040030
		opword 0x7C170000
		opword 0x41820010
		opword 0x80040034
		opword 0x7C170000
		opword 0x4082000C
		opword 0x80010078
		opword 0x9001006C
		opword 0x2C170004
		opword 0x40820018
		opword 0xA0040000
		opword 0x540006F7
		opword 0x4182000C
		opword 0x80010070
		opword 0x9001006C
		opword 0x2C170005
		opword 0x40820018
		opword 0xA0040000
		opword 0x540006B5
		opword 0x4182000C
		opword 0x80010070
		opword 0x9001006C
		opword 0x80190010
		opword 0x2C00000E
		opword 0x4080012C
		opword 0x2C00000A
		opword 0x40800008
		opword 0x48000120
		lwz r3, wp(r13)
		opword 0x380000FE
		opword 0x9801006F
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit
		opword 0x807E0000
		opword 0x388102A4
		opword 0x801E0004
		opword 0x38A1028C
		opword 0x90610298
		opword 0x38C10064
		opword 0xC0390000
		opword 0x3860000E
		opword 0x9001029C
		opword 0xC0190004
		opword 0x811E0008
		opword 0xD0210298
		opword 0x8181006C
		opword 0xD001029C
		opword 0x817E000C
		opword 0x815E0010
		opword 0x813E0014
		opword 0x80E10298
		opword 0x8001029C
		opword 0x91810064
		opword 0x9161028C
		opword 0x91410290
		opword 0x91210294
		opword 0x910102A0
		opword 0x90E102A4
		opword 0x900102A8
		opword 0x910102AC
		bl winTexSet
		lwz r3, wp(r13)
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit
		lfs f1, float_60_8041be04(r2)
		opword 0x38810280
		opword 0xC0190004
		opword 0x38A10268
		opword 0x807E0018
		opword 0x38C10060
		opword 0x801E001C
		opword 0xEC01002A
		opword 0x90610274
		opword 0xC0390000
		opword 0x90010278
		opword 0x811E0020
		opword 0xD0210274
		opword 0x8061006C
		opword 0xD0010278
		opword 0x817E0024
		opword 0x815E0028
		opword 0x813E002C
		opword 0x80E10274
		opword 0x80010278
		opword 0x90610060
		opword 0x80790010
		opword 0x91610268
		opword 0x9141026C
		opword 0x91210270
		opword 0x9101027C
		opword 0x90E10280
		opword 0x90010284
		opword 0x91010288
		bl winTexSet
		opword 0x48000088
		opword 0x80640004
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit_x2
		opword 0x807E0030
		opword 0x38A1025C
		opword 0x801E0034
		opword 0x38C10244
		opword 0x90610250
		opword 0x38E1005C
		opword 0xC0390000
		opword 0x90010254
		opword 0xC0190004
		opword 0x813E0038
		opword 0xD0210250
		opword 0x8061006C
		opword 0xD0010254
		opword 0x809E003C
		opword 0x817E0040
		opword 0x815E0044
		opword 0x81010250
		opword 0x80010254
		opword 0x9061005C
		opword 0x80790010
		opword 0x90810244
		opword 0x80990014
		opword 0x91610248
		opword 0x9141024C
		opword 0x91210258
		opword 0x9101025C
		opword 0x90010260
		opword 0x91210264
		bl winTexSet_x2
		opword 0x3AF70001
		opword 0x3B39001C
		opword 0x2C170009
		opword 0x4180FDB8
		lwz r0, dat_8041bd94(r2)
		opword 0x38810058
		lfs f1, float_neg250_8041be08(r2)
		opword 0x38600000
		opword 0x90010058
		lfs f2, float_200_8041be0c(r2)
		lfs f3, float_500_8041be10(r2)
		lfs f4, float_40_8041be14(r2)
		lfs f5, float_20_8041be18(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		lwz r3, wp(r13)
		opword 0x82830038
		opword 0x7E83A378
		bl FontGetMessageWidth
		opword 0x5460043E
		opword 0x7E85A378
		opword 0x7C6000D0
		opword 0x388000C0
		opword 0x54600FFE
		opword 0x7C001A14
		opword 0x7C030E70
		bl FontDrawMessage
		opword 0x3B600000
		lfs f30, float_100_8041be20(r2)
		lfs f31, float_84_8041be24(r2)
		opword 0x7F7DDB78
		bl cardGetFilePtr
		opword 0x389D2000
		opword 0x7C832214
		opword 0xA2C40000
		opword 0x3B2411C4
		opword 0xAAE4146A
		opword 0x83040028
		opword 0x82A4002C
		opword 0xA344146C
		opword 0x8284017C
		bl FontDrawStart
		lwz r0, dat_8041bd98(r2)
		opword 0x38610054
		opword 0x90010054
		bl FontDrawColor
		lwz r3, wp(r13)
		opword 0x80030020
		opword 0x7C1B0000
		opword 0x40820014
		lwz r0, dat_8041bd9c(r2)
		opword 0x38610050
		opword 0x90010050
		bl FontDrawColor
		lfs f1, float_0p6_8041be1c(r2)
		bl FontDrawScale
		bl FontDrawEdge
		opword 0x387B0001
		bl winZenkakuStr
		opword 0x7C651B78
		opword 0x38610310
		opword 0x389E02F0
		opword 0x4CC63182
		bl sprintf
		opword 0xC03C0000
		opword 0x38610310
		opword 0xC01C0004
		opword 0xEC21F028
		opword 0xEC5F002A
		bl FontDrawString
		bl FontDrawEdgeOff
		lfs f1, float_1_8041bde8(r2)
		bl FontDrawScale
		lwz r0, dat_8041bda0(r2)
		opword 0x3861004C
		opword 0x9001004C
		bl FontDrawColor
		lwz r3, wp(r13)
		opword 0x80030020
		opword 0x7C1B0000
		opword 0x40820014
		lwz r0, dat_8041bda4(r2)
		opword 0x38610048
		opword 0x90010048
		bl FontDrawColor
		opword 0x56C007BD
		opword 0x41820050
		opword 0x3A9E02FC
		opword 0x7E83A378
		bl FontGetMessageWidth
		opword 0x5463043E
		opword 0x3C004330
		opword 0x90610824
		opword 0x7E83A378
		opword 0xC85E0350
		opword 0x90010820
		lfs f3, float_0p5_8041be28(r2)
		opword 0xC8010820
		opword 0xC03C0000
		opword 0xEC801028
		lfs f2, float_12_8041be2c(r2)
		opword 0xC01C0004
		opword 0xEC2408FC
		opword 0xEC42002A
		bl FontDrawString
		opword 0x48000440
		opword 0x56C007FF
		opword 0x41820050
		opword 0x3A9E030C
		opword 0x7E83A378
		bl FontGetMessageWidth
		opword 0x5463043E
		opword 0x3C004330
		opword 0x90610824
		opword 0x7E83A378
		opword 0xC85E0350
		opword 0x90010820
		lfs f3, float_0p5_8041be28(r2)
		opword 0xC8010820
		opword 0xC03C0000
		opword 0xEC801028
		lfs f2, float_12_8041be2c(r2)
		opword 0xC01C0004
		opword 0xEC2408FC
		opword 0xEC42002A
		bl FontDrawString
		opword 0x480003EC
		opword 0x2C140000
		opword 0x408200A4
		opword 0x3A9E031C
		opword 0x7E83A378
		bl FontGetMessageWidth
		opword 0x5463043E
		opword 0x3C004330
		opword 0x90610824
		opword 0x7E83A378
		opword 0xC85E0350
		opword 0x90010820
		lfs f3, float_0p5_8041be28(r2)
		opword 0xC8010820
		opword 0xC03C0000
		opword 0xEC801028
		lfs f2, float_12_8041be2c(r2)
		opword 0xC01C0004
		opword 0xEC2408FC
		opword 0xEC42002A
		bl FontDrawString
		opword 0x7F23CB78
		bl strlen
		opword 0x28030000
		opword 0x4182038C
		opword 0x7F23CB78
		bl FontGetMessageWidth
		opword 0x5463FC7E
		opword 0x3C004330
		opword 0x6C638000
		opword 0x90010820
		opword 0xC85E0358
		opword 0x90610824
		opword 0x7F23CB78
		opword 0xC07C0000
		opword 0xC8010820
		lfs f1, float_70_8041be30(r2)
		opword 0xEC801028
		opword 0xC01C0004
		opword 0xEC41002A
		opword 0xEC232028
		bl FontDrawString
		opword 0x48000344
		la r3, str_8041BE34(r2)
		bl FontGetMessageWidth
		opword 0x3C808000
		opword 0x7F03C378
		opword 0x800400F8
		opword 0x7EA4AB78
		opword 0x38A00000
		opword 0x5406F0BE
		bl __div2i
		opword 0x3CA00005
		opword 0x7C872378
		opword 0x38057E3F
		opword 0x38C00000
		opword 0x7C651B78
		opword 0x7C070010
		opword 0x7C053110
		opword 0x7C1FF910
		opword 0x7C0000D1
		opword 0x41820010
		opword 0x3A800063
		opword 0x3AA0003B
		opword 0x48000040
		opword 0x7CF53B78
		opword 0x7CB42B78
		opword 0x38A00000
		opword 0x38C00E10
		bl __div2u
		opword 0x7E83A378
		opword 0x7C942378
		opword 0x7EA4AB78
		opword 0x38A00000
		opword 0x38C00E10
		bl __mod2u
		opword 0x38A00000
		opword 0x38C0003C
		bl __div2u
		opword 0x7C952378
		opword 0x7F23CB78
		bl strlen
		opword 0x28030000
		opword 0x41820048
		opword 0x7F23CB78
		bl FontGetMessageWidth
		opword 0x5463FC7E
		opword 0x3C004330
		opword 0x6C638000
		opword 0x90010820
		opword 0xC85E0358
		opword 0x90610824
		opword 0x7F23CB78
		opword 0xC07C0000
		opword 0xC8010820
		lfs f1, float_70_8041be30(r2)
		opword 0xEC801028
		opword 0xC01C0004
		opword 0xEC41002A
		opword 0xEC232028
		bl FontDrawString
		opword 0x7EE3BB78
		bl winZenkakuStr
		opword 0x7C651B78
		opword 0x38610494
		opword 0x389E0328
		opword 0x4CC63182
		bl sprintf
		opword 0x38610494
		bl FontGetMessageWidth
		opword 0x5463043E
		opword 0x3C004330
		opword 0x90610824
		opword 0x38610494
		opword 0xC85E0350
		opword 0x90010820
		lfs f3, float_0p5_8041be28(r2)
		opword 0xC8010820
		opword 0xC03C0000
		opword 0xEC801028
		lfs f2, float_30_8041be3c(r2)
		opword 0xC01C0004
		opword 0xEC2408FC
		opword 0xEC42002A
		bl FontDrawString
		opword 0x38610494
		opword 0x389E0334
		bl strcpy
		opword 0x7E83A378
		opword 0x38800002
		bl unk_8016af5c
		opword 0x7C641B78
		opword 0x38610494
		bl strcat
		opword 0x38610494
		la r4, str_8041BE40(r2)
		bl strcat
		opword 0x7EA3AB78
		opword 0x38800002
		bl unk_8016af5c
		opword 0x7C641B78
		opword 0x38610494
		bl strcat
		opword 0x38610494
		bl FontGetMessageWidth
		opword 0x5463043E
		opword 0x3C004330
		opword 0x9061081C
		opword 0x38610494
		opword 0xC87E0350
		opword 0x90010818
		lfs f0, float_0p5_8041be28(r2)
		opword 0xC8410818
		opword 0xC03C0000
		opword 0xEC621828
		opword 0xC05C0004
		fmuls f29, f3, f0
		opword 0xEC21E828
		bl FontDrawString
		opword 0x38610494
		opword 0x389E0334
		bl strcpy
		opword 0x7E83A378
		opword 0x38800002
		bl unk_8016af5c
		opword 0x7C641B78
		opword 0x38610494
		bl strcat
		opword 0x38610494
		bl FontGetMessageWidth
		opword 0x5463043E
		opword 0x3C004330
		opword 0x90610814
		opword 0x38610464
		opword 0xC01C0000
		opword 0x90010810
		opword 0xC87E0350
		opword 0xEC40E828
		opword 0xC8010810
		opword 0xC03C0004
		opword 0xEC601828
		lfs f0, float_22_8041be48(r2)
		lfs f5, float_8_8041be44(r2)
		opword 0xEC010028
		lfs f1, float_1_8041bde8(r2)
		opword 0xEC83102A
		lfs f3, float_0_8041bde4(r2)
		opword 0xEC41002A
		opword 0xEC25202A
		bl PSMTXTrans
		lfs f1, float_1p5_8041be4c(r2)
		opword 0x38610434
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x38610464
		opword 0x38810434
		opword 0x7C651B78
		bl PSMTXConcat
		lwz r0, dat_8041bda8(r2)
		opword 0x38610464
		opword 0x38C10044
		opword 0x38800000
		opword 0x90010044
		opword 0x38A00201
		bl iconDispGxCol
		opword 0x3AFC0004
		opword 0x3AC00000
		opword 0x3B200000
		la r24, stone_id(r13)
		opword 0x38160001
		opword 0x38600001
		opword 0x7C600030
		opword 0x7F400039
		opword 0x41820080
		opword 0x6F238000
		opword 0x3C004330
		opword 0x90610824
		opword 0x38610464
		opword 0xC07C0000
		opword 0x90010820
		lfs f1, float_106_8041be50(r2)
		opword 0xC85E0358
		opword 0xC8010820
		opword 0xECA30828
		opword 0xC0370000
		opword 0xEC801028
		lfs f0, float_52_8041be54(r2)
		lfs f3, float_0_8041bde4(r2)
		opword 0xEC410028
		opword 0xEC25202A
		bl PSMTXTrans
		lwz r3, wp(r13)
		opword 0x38810074
		opword 0x80030020
		opword 0x7C1B0000
		opword 0x40820008
		opword 0x38810078
		opword 0x80840000
		opword 0x38610464
		opword 0x80180000
		opword 0x38C10040
		opword 0x90810040
		opword 0x38800000
		opword 0x5405043E
		bl iconDispGxCol
		opword 0x3AD60001
		opword 0x3B180004
		opword 0x2C160007
		opword 0x3B390020
		opword 0x4180FF60
		opword 0x3B7B0001
		opword 0x3B9C001C
		opword 0x2C1B0004
		opword 0x3BBD4000
		opword 0x4180FA88
		lwz r3, wp(r13)
		opword 0xA0030000
		opword 0x540007FF
		opword 0x41820018
		opword 0xC023002C
		lfs f0, float_0p05_8041be58(r2)
		opword 0xEC01002A
		opword 0xD003002C
		opword 0x48000014
		opword 0xC023002C
		lfs f0, float_0p05_8041be58(r2)
		opword 0xEC010028
		opword 0xD003002C
		lwz r3, wp(r13)
		lfs f0, float_0_8041bde4(r2)
		opword 0xC023002C
		opword 0xFC010040
		opword 0x40800008
		opword 0xD003002C
		lwz r3, wp(r13)
		lfs f0, float_1_8041bde8(r2)
		opword 0xC023002C
		opword 0xFC010040
		opword 0x40810008
		opword 0xD003002C
		lwz r3, wp(r13)
		opword 0xC023002C
		bl nameMaskGX
		lwz r3, wp(r13)
		opword 0x80030018
		opword 0x2C000064
		opword 0x418002B4
		opword 0x2C0000C8
		opword 0x408002AC
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit
		lwz r12, dat_8041bdac(r2)
		opword 0x38810238
		opword 0x817E0054
		opword 0x38A1022C
		opword 0x815E0058
		opword 0x38C1003C
		opword 0x813E005C
		opword 0x3860000F
		opword 0x811E0048
		opword 0x80FE004C
		opword 0x801E0050
		opword 0x9181003C
		opword 0x9161022C
		opword 0x91410230
		opword 0x91210234
		opword 0x91010238
		opword 0x90E1023C
		opword 0x90010240
		bl winTexSet
		lwz r3, wp(r13)
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit_x2
		lwz r20, dat_8041bdb0(r2)
		opword 0x38A10220
		opword 0x819E006C
		opword 0x38C10214
		opword 0x817E0070
		opword 0x38E10038
		opword 0x815E0074
		opword 0x38600013
		opword 0x813E0060
		opword 0x3880001F
		opword 0x811E0064
		opword 0x801E0068
		opword 0x92810038
		opword 0x91810214
		opword 0x91610218
		opword 0x9141021C
		opword 0x91210220
		opword 0x91010224
		opword 0x90010228
		bl winTexSet_x2
		opword 0x3B000000
		opword 0x7F17C378
		lwz r3, wp(r13)
		opword 0x80030024
		opword 0x7C180000
		opword 0x40820130
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit
		opword 0x20170032
		opword 0x811E0078
		opword 0x6C038000
		opword 0x3C004330
		opword 0x90610824
		opword 0x38810208
		opword 0x80FE0080
		opword 0x38A101F0
		opword 0x90010820
		opword 0x38C10034
		opword 0x801E007C
		opword 0x38600033
		opword 0xC83E0358
		opword 0xC8010820
		opword 0x90010200
		opword 0xEC000828
		lwz r12, dat_8041bdb4(r2)
		opword 0x817E0084
		opword 0x815E0088
		opword 0xD0010200
		opword 0x813E008C
		opword 0x80010200
		opword 0x91810034
		opword 0x916101F0
		opword 0x914101F4
		opword 0x912101F8
		opword 0x910101FC
		opword 0x90E10204
		opword 0x91010208
		opword 0x9001020C
		opword 0x90E10210
		bl winTexSet
		lwz r3, wp(r13)
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit_x2
		opword 0x20170036
		opword 0x813E0090
		opword 0x6C038000
		opword 0x3C004330
		opword 0x9061081C
		opword 0x38780015
		opword 0x811E0098
		opword 0x38A101E4
		opword 0x90010818
		opword 0x38C101CC
		opword 0x801E0094
		opword 0x38E10030
		opword 0xC83E0358
		opword 0x38800033
		opword 0xC8010818
		opword 0x900101DC
		opword 0xEC000828
		lwz r20, dat_8041bdb8(r2)
		opword 0x819E009C
		opword 0x817E00A0
		opword 0xD00101DC
		opword 0x815E00A4
		opword 0x800101DC
		opword 0x92810030
		opword 0x918101CC
		opword 0x916101D0
		opword 0x914101D4
		opword 0x912101D8
		opword 0x910101E0
		opword 0x912101E4
		opword 0x900101E8
		opword 0x910101EC
		bl winTexSet_x2
		opword 0x48000098
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit_x2
		opword 0x20170032
		opword 0x813E00A8
		opword 0x6C038000
		opword 0x3C004330
		opword 0x90610824
		opword 0x38780015
		opword 0x811E00B0
		opword 0x38A101C0
		opword 0x90010820
		opword 0x38C101A8
		opword 0x801E00AC
		opword 0x38E1002C
		opword 0xC83E0358
		opword 0x38800033
		opword 0xC8010820
		opword 0x900101B8
		opword 0xEC000828
		lwz r20, dat_8041bdbc(r2)
		opword 0x819E00B4
		opword 0x817E00B8
		opword 0xD00101B8
		opword 0x815E00BC
		opword 0x800101B8
		opword 0x9281002C
		opword 0x918101A8
		opword 0x916101AC
		opword 0x914101B0
		opword 0x912101B4
		opword 0x910101BC
		opword 0x912101C0
		opword 0x900101C4
		opword 0x910101C8
		bl winTexSet_x2
		opword 0x3B180001
		opword 0x3AF70032
		opword 0x2C180003
		opword 0x4180FE24
		lwz r3, wp(r13)
		opword 0x80030018
		opword 0x2C0000C8
		opword 0x418002B4
		opword 0x2C00012C
		opword 0x408002AC
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit
		lwz r12, dat_8041bdc0(r2)
		opword 0x3881019C
		opword 0x817E00CC
		opword 0x38A10190
		opword 0x815E00D0
		opword 0x38C10028
		opword 0x813E00D4
		opword 0x3860000F
		opword 0x811E00C0
		opword 0x80FE00C4
		opword 0x801E00C8
		opword 0x91810028
		opword 0x91610190
		opword 0x91410194
		opword 0x91210198
		opword 0x9101019C
		opword 0x90E101A0
		opword 0x900101A4
		bl winTexSet
		lwz r3, wp(r13)
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit_x2
		lwz r20, dat_8041bdc4(r2)
		opword 0x38A10184
		opword 0x819E00E4
		opword 0x38C10178
		opword 0x817E00E8
		opword 0x38E10024
		opword 0x815E00EC
		opword 0x38600014
		opword 0x813E00D8
		opword 0x3880001F
		opword 0x811E00DC
		opword 0x801E00E0
		opword 0x92810024
		opword 0x91810178
		opword 0x9161017C
		opword 0x91410180
		opword 0x91210184
		opword 0x91010188
		opword 0x9001018C
		bl winTexSet_x2
		opword 0x3B000000
		opword 0x7F17C378
		lwz r3, wp(r13)
		opword 0x80030028
		opword 0x7C180000
		opword 0x40820130
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit
		opword 0x2017001E
		opword 0x811E00F0
		opword 0x6C038000
		opword 0x3C004330
		opword 0x90610824
		opword 0x3881016C
		opword 0x80FE00F8
		opword 0x38A10154
		opword 0x90010820
		opword 0x38C10020
		opword 0x801E00F4
		opword 0x38600033
		opword 0xC83E0358
		opword 0xC8010820
		opword 0x90010164
		opword 0xEC000828
		lwz r12, dat_8041bdc8(r2)
		opword 0x817E00FC
		opword 0x815E0100
		opword 0xD0010164
		opword 0x813E0104
		opword 0x80010164
		opword 0x91810020
		opword 0x91610154
		opword 0x91410158
		opword 0x9121015C
		opword 0x91010160
		opword 0x90E10168
		opword 0x9101016C
		opword 0x90010170
		opword 0x90E10174
		bl winTexSet
		lwz r3, wp(r13)
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit_x2
		opword 0x20170022
		opword 0x813E0108
		opword 0x6C038000
		opword 0x3C004330
		opword 0x9061081C
		opword 0x38780018
		opword 0x811E0110
		opword 0x38A10148
		opword 0x90010818
		opword 0x38C10130
		opword 0x801E010C
		opword 0x38E1001C
		opword 0xC83E0358
		opword 0x38800033
		opword 0xC8010818
		opword 0x90010140
		opword 0xEC000828
		lwz r20, dat_8041bdcc(r2)
		opword 0x819E0114
		opword 0x817E0118
		opword 0xD0010140
		opword 0x815E011C
		opword 0x80010140
		opword 0x9281001C
		opword 0x91810130
		opword 0x91610134
		opword 0x91410138
		opword 0x9121013C
		opword 0x91010144
		opword 0x91210148
		opword 0x9001014C
		opword 0x91010150
		bl winTexSet_x2
		opword 0x48000098
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit_x2
		opword 0x2017001E
		opword 0x813E0120
		opword 0x6C038000
		opword 0x3C004330
		opword 0x90610824
		opword 0x38780018
		opword 0x811E0128
		opword 0x38A10124
		opword 0x90010820
		opword 0x38C1010C
		opword 0x801E0124
		opword 0x38E10018
		opword 0xC83E0358
		opword 0x38800033
		opword 0xC8010820
		opword 0x9001011C
		opword 0xEC000828
		lwz r20, dat_8041bdd0(r2)
		opword 0x819E012C
		opword 0x817E0130
		opword 0xD001011C
		opword 0x815E0134
		opword 0x8001011C
		opword 0x92810018
		opword 0x9181010C
		opword 0x91610110
		opword 0x91410114
		opword 0x91210118
		opword 0x91010120
		opword 0x91210124
		opword 0x90010128
		opword 0x9101012C
		bl winTexSet_x2
		opword 0x3B180001
		opword 0x3AF70032
		opword 0x2C180002
		opword 0x4180FE24
		lwz r4, wp(r13)
		opword 0x80040018
		opword 0x2C000033
		opword 0x408202A4
		opword 0x80040034
		opword 0x2C000004
		opword 0x40800298
		opword 0x837E0138
		opword 0x5400103A
		opword 0x835E013C
		opword 0x386103F4
		opword 0x833E0140
		opword 0x831E0144
		opword 0x82FE0148
		opword 0x82DE014C
		opword 0x82BE0150
		opword 0x829E0154
		opword 0x819E0158
		opword 0x817E015C
		opword 0x815E0160
		opword 0x813E0164
		opword 0x811E0168
		opword 0x80FE016C
		opword 0x80DE0170
		opword 0x80BE0174
		opword 0x80840030
		opword 0x936103F4
		opword 0x54842036
		opword 0xC85E0348
		opword 0x934103F8
		opword 0x7C040214
		opword 0x932103FC
		opword 0x93010400
		opword 0x92E10404
		opword 0x92C10408
		opword 0x92A1040C
		opword 0x92810410
		opword 0x91810414
		opword 0x91610418
		opword 0x9141041C
		opword 0x91210420
		opword 0x91010424
		opword 0x90E10428
		opword 0x90C1042C
		opword 0x90A10430
		opword 0x7C23042E
		bl fmod
		opword 0xFC000818
		lfs f3, float_0_8041bde4(r2)
		opword 0xFC001800
		opword 0x408200A8
		lwz r3, wp(r13)
		opword 0x3CA04330
		opword 0x90A10818
		opword 0x80030030
		opword 0x80630034
		opword 0x54070FFE
		opword 0x540607FE
		opword 0x7C870214
		opword 0x54600FFE
		opword 0x7C840E70
		opword 0x7CC63A78
		opword 0x7C001A14
		opword 0x90A10810
		opword 0x7C000E70
		opword 0x6C838000
		opword 0x6C008000
		opword 0x9061081C
		opword 0x7C673050
		opword 0xC85E0358
		opword 0x90010814
		opword 0x6C608000
		opword 0xC8210818
		opword 0xC8010810
		opword 0x90010824
		opword 0xEC811028
		opword 0xEC001028
		opword 0x90A10820
		opword 0xC8210820
		opword 0xFC040000
		opword 0xEC411028
		opword 0x40820018
		lfs f1, float_140_8041be60(r2)
		opword 0xFFA01890
		lfs f0, float_120_8041be5c(r2)
		opword 0xEFC1013C
		opword 0x48000020
		lfs f1, float_300_8041be68(r2)
		lfs f0, float_neg150_8041be64(r2)
		lfs f30, float_50_8041be6c(r2)
		opword 0xEFA100BA
		opword 0x4800000C
		opword 0xFFA01890
		lfs f30, float_50_8041be6c(r2)
		lwz r3, wp(r13)
		lfs f0, float_40_8041be14(r2)
		opword 0x80630004
		opword 0xEFDE0028
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit
		lfs f0, float_2_8041be70(r2)
		opword 0x38E103F4
		opword 0x807E0178
		opword 0x38810100
		opword 0x801E017C
		opword 0xEC20E82A
		opword 0x906100F4
		opword 0xEC1E0028
		opword 0x813E0180
		opword 0x38A100E8
		opword 0x900100F8
		lwz r20, dat_8041bdd4(r2)
		opword 0x38C10014
		opword 0xD02100F4
		opword 0x3860001D
		opword 0x819E0184
		opword 0xD00100F8
		opword 0x817E0188
		opword 0x815E018C
		opword 0x810100F4
		opword 0x800100F8
		opword 0x92810014
		lwz r20, wp(r13)
		opword 0x918100E8
		opword 0x916100EC
		opword 0x914100F0
		opword 0x91010100
		opword 0x90010104
		opword 0x91210108
		opword 0x81140030
		opword 0x80140034
		opword 0x55082036
		opword 0x912100FC
		opword 0x5400103A
		opword 0x7C080214
		opword 0x7C27042E
		bl winTexSetRot
		opword 0x807E0190
		opword 0x38E103F4
		opword 0x801E0194
		opword 0x388100DC
		opword 0x906100D0
		opword 0x38A100C4
		opword 0x813E0198
		opword 0x38C10010
		opword 0x900100D4
		opword 0x3860001D
		opword 0x82810078
		opword 0xD3A100D0
		opword 0x819E019C
		opword 0xD3C100D4
		opword 0x817E01A0
		opword 0x815E01A4
		opword 0x810100D0
		opword 0x800100D4
		opword 0x92810010
		lwz r20, wp(r13)
		opword 0x918100C4
		opword 0x916100C8
		opword 0x914100CC
		opword 0x910100DC
		opword 0x900100E0
		opword 0x912100E4
		opword 0x81140030
		opword 0x80140034
		opword 0x55082036
		opword 0x912100D8
		opword 0x5400103A
		opword 0x7C080214
		opword 0x7C27042E
		bl winTexSetRot
		lwz r3, wp(r13)
		opword 0xA0030000
		opword 0x54000673
		opword 0x40820108
		opword 0x80630004
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit
		lwz r0, dat_8041bdd8(r2)
		opword 0x388100B8
		opword 0x815E01B4
		opword 0x38A100A0
		opword 0x813E01B8
		opword 0x38C1000C
		opword 0x811E01BC
		opword 0x38600000
		opword 0x9001000C
		opword 0x80FE01A8
		opword 0x801E01AC
		opword 0x914100A0
		lwz r10, wp(r13)
		opword 0x912100A4
		lfs f2, float_2_8041be70(r2)
		opword 0x910100A8
		opword 0x811E01B0
		opword 0xC02A0008
		opword 0xC00A000C
		opword 0xEC22082A
		opword 0x90E100AC
		opword 0xEC001028
		opword 0x900100B0
		opword 0xD02100AC
		opword 0xD00100B0
		opword 0x80E100AC
		opword 0x800100B0
		opword 0x910100B4
		opword 0x90E100B8
		opword 0x900100BC
		opword 0x910100C0
		bl winTexSet
		opword 0x81010078
		opword 0x38810094
		opword 0x817E01CC
		opword 0x38A1007C
		opword 0x815E01D0
		opword 0x38C10008
		opword 0x813E01D4
		opword 0x38600000
		opword 0x80FE01C0
		opword 0x801E01C4
		opword 0x91010008
		lwz r12, wp(r13)
		opword 0x811E01C8
		opword 0x9161007C
		opword 0x91410080
		opword 0x91210084
		opword 0x90E10088
		opword 0xC02C0008
		opword 0xC00C000C
		opword 0x9001008C
		opword 0xD0210088
		opword 0xD001008C
		opword 0x80E10088
		opword 0x8001008C
		opword 0x91010090
		opword 0x90E10094
		opword 0x90010098
		opword 0x9101009C
		bl winTexSet
		opword 0xC021034C
		opword 0xC0410350
		opword 0xC0610354
		opword 0xC0810358
		opword 0xC0A1035C
		opword 0xC0C10360
		bl GXSetViewport
		opword 0x38610330
		bl GXSetProjectionv
		bl camGetCurPtr
		opword 0x3800004C
		opword 0x38A3FFFC
		opword 0x38810594
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
	}
}
#pragma pop
#endif

__declspec(section ".sdata") s32 stone_id[7] = {0x197, 0x198, 0x19A, 0x19C, 0x19D, 0x199, 0x19B};

__declspec(section ".sdata") static s32 evt_shake[] = {
    0x0003005B, (s32)evt_sub_rumble_onoff, 0, 0,
    0x0001000A, 150,
    0x0003005B, (s32)evt_sub_rumble_onoff, 1, 0,
    0x00000002, 0x00000001,
};

__declspec(section ".sdata") s32 evt_continue[] = {
    0x0002005B, (s32)evt_sub_animgroup_async, (s32)str_802ED848,
    0x0002005B, (s32)evt_sub_animgroup_async, (s32)str_802ED85C,
    0x0002005B, (s32)evt_sub_animgroup_async, (s32)str_802ED870,
    0x00000002, 0x00000001,
};
#pragma force_active on
#pragma force_active on
__declspec(section ".sdata") u32 gap_07_80410C9C_sdata[1] = {0};

#pragma defer_codegen off
#pragma force_active on
#ifdef NONMATCHING
void continueGame(void) {
    cardCopy2Main(wp->slot);
    gp->saveSlot = wp->slot;
    gp->lastSlot = wp->slot;
    marioPartyKill();
    {
        MarioWork* m = marioGetPtr();
        m->prevPartyMemberId[0] = 0;
        m->prevPartyMemberId[1] = 0;
    }
    psndSetFlag(4);
    marioPartyEntry(gp->savePartyId[0]);
    marioPartyEntry(gp->savePartyId[1]);
    psndClearFlag(4);
    countDownSaveReStart();
    gp->flags |= 1;
    switch (swByteGet(4)) {
        case 0:
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 28;
            seqSetSeq(SEQ_MAP_CHANGE, gp->currentMapName, 0);
            break;
        case 1:
            gp->areaFadeInType = 61;
            gp->areaFadeOutType = 56;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED884, 0);
            break;
        case 2:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED88C, 0);
            break;
        case 3:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED894, str_802ED89C);
            break;
        case 4:
            gp->areaFadeInType = 61;
            gp->areaFadeOutType = 56;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED884, 0);
            break;
        case 5:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8A8, 0);
            break;
        case 6:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8B0, 0);
            break;
        case 7:
            gp->areaFadeInType = 61;
            gp->areaFadeOutType = 56;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED884, 0);
            break;
        case 8:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8B8, 0);
            break;
        case 9:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8C0, 0);
            break;
        case 10:
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 28;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8C8, 0);
            break;
        case 11:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8D0, 0);
            break;
        case 12:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8C8, 0);
            break;
        case 13:
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 28;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8D8, 0);
            break;
        case 14:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8C8, 0);
            break;
        case 15:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8E0, 0);
            break;
        case 16:
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 28;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8E8, "next");
            break;
        case 17:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8F0, 0);
            break;
        case 18:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8D0, str_802ED8F8);
            break;
        case 19:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED908, 0);
            break;
        case 20:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED910, str_802ED918);
            break;
        case 21:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED920, 0);
            break;
        case 22:
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 28;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED928, 0);
            break;
        case 23:
            stg0_00_init();
            gp->saveSlot = wp->slot;
            marioPartyKill();
            {
                MarioWork* m = marioGetPtr();
                m->prevPartyMemberId[0] = 0;
                m->prevPartyMemberId[1] = 0;
            }
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 25;
            swInit();
            swByteSet(0, 0);
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED930, str_802ED938);
            break;
        case 24:
            gp->areaFadeInType = 0x3d;
            gp->areaFadeOutType = 0x38;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED884, 0);
            break;
    }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void continueGame(void) {
	asm {
		lis r4, vec3_802ed670@ha
	}
	asm volatile {
		addi r31, r4, vec3_802ed670@l
		lwz r3, wp(r13)
		opword 0x80630020
		bl cardCopy2Main
		lwz r4, wp(r13)
		lwz r3, gp(r13)
		opword 0x80040020
		opword 0x900311D0
		lwz r4, wp(r13)
		lwz r3, gp(r13)
		opword 0x80040020
		opword 0x900311B8
		bl marioPartyKill
		bl marioGetPtr
		opword 0x38000000
		opword 0x98030243
		opword 0x98030244
		opword 0x38600004
		bl psndSetFlag
		lwz r3, gp(r13)
		opword 0x806311E0
		bl marioPartyEntry
		lwz r3, gp(r13)
		opword 0x806311E4
		bl marioPartyEntry
		opword 0x38600004
		bl psndClearFlag
		bl countDownSaveReStart
		lwz r4, gp(r13)
		opword 0x38600004
		opword 0x80040000
		opword 0x60000001
		opword 0x90040000
		bl swByteGet
		opword 0x28030018
		opword 0x4181049C
		lis r4, jumptable_8034A058@ha
		opword 0x5460103A
		addi r3, r4, jumptable_8034A058@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		lwz r4, gp(r13)
		opword 0x38A00000
		opword 0x3800001C
		opword 0x38600003
		opword 0x90A40110
		opword 0x38A00000
		lwz r4, gp(r13)
		opword 0x90040108
		lwz r4, gp(r13)
		opword 0x3884012C
		bl seqSetSeq
		opword 0x48000454
		lwz r3, gp(r13)
		opword 0x38A0003D
		opword 0x38000038
		opword 0x389F0214
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x48000428
		lwz r3, gp(r13)
		opword 0x38A0003E
		opword 0x3800003A
		opword 0x389F021C
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x480003FC
		lwz r3, gp(r13)
		opword 0x38A0003C
		opword 0x38000036
		opword 0x389F0224
		opword 0x90A30110
		opword 0x38BF022C
		opword 0x38600003
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x480003D0
		lwz r3, gp(r13)
		opword 0x38A0003D
		opword 0x38000038
		opword 0x389F0214
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x480003A4
		lwz r3, gp(r13)
		opword 0x38A0003E
		opword 0x3800003A
		opword 0x389F0238
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x48000378
		lwz r3, gp(r13)
		opword 0x38A0003C
		opword 0x38000036
		opword 0x389F0240
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x4800034C
		lwz r3, gp(r13)
		opword 0x38A0003D
		opword 0x38000038
		opword 0x389F0214
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x48000320
		lwz r3, gp(r13)
		opword 0x38A0003E
		opword 0x3800003A
		opword 0x389F0248
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x480002F4
		lwz r3, gp(r13)
		opword 0x38A0003C
		opword 0x38000036
		opword 0x389F0250
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x480002C8
		lwz r3, gp(r13)
		opword 0x38A00000
		opword 0x3800001C
		opword 0x389F0258
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x4800029C
		lwz r3, gp(r13)
		opword 0x38A0003E
		opword 0x3800003A
		opword 0x389F0260
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x48000270
		lwz r3, gp(r13)
		opword 0x38A0003C
		opword 0x38000036
		opword 0x389F0258
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x48000244
		lwz r3, gp(r13)
		opword 0x38A00000
		opword 0x3800001C
		opword 0x389F0268
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x48000218
		lwz r3, gp(r13)
		opword 0x38A0003E
		opword 0x3800003A
		opword 0x389F0258
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x480001EC
		lwz r3, gp(r13)
		opword 0x38A0003C
		opword 0x38000036
		opword 0x389F0270
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x480001C0
		lwz r3, gp(r13)
		opword 0x38A00000
		opword 0x3800001C
		opword 0x389F0278
		opword 0x90A30110
		opword 0x38600003
		la r5, str_8041BDDC(r2)
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x48000194
		lwz r3, gp(r13)
		opword 0x38A0003E
		opword 0x3800003A
		opword 0x389F0280
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x48000168
		lwz r3, gp(r13)
		opword 0x38A0003C
		opword 0x38000036
		opword 0x389F0260
		opword 0x90A30110
		opword 0x38BF0288
		opword 0x38600003
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x4800013C
		lwz r3, gp(r13)
		opword 0x38A0003E
		opword 0x3800003A
		opword 0x389F0298
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x48000110
		lwz r3, gp(r13)
		opword 0x38A0003C
		opword 0x38000036
		opword 0x389F02A0
		opword 0x90A30110
		opword 0x38BF02A8
		opword 0x38600003
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x480000E4
		lwz r3, gp(r13)
		opword 0x38A0003C
		opword 0x38000036
		opword 0x389F02B0
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x480000B8
		lwz r3, gp(r13)
		opword 0x38A00000
		opword 0x3800001C
		opword 0x389F02B8
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
		opword 0x4800008C
		bl stg0_00_init
		lwz r4, wp(r13)
		lwz r3, gp(r13)
		opword 0x80040020
		opword 0x900311D0
		bl marioPartyKill
		bl marioGetPtr
		opword 0x38800000
		opword 0x38000019
		opword 0x98830243
		opword 0x98830244
		lwz r3, gp(r13)
		opword 0x90830110
		lwz r3, gp(r13)
		opword 0x90030108
		bl swInit
		opword 0x38600000
		opword 0x38800000
		bl swByteSet
		opword 0x389F02C0
		opword 0x38BF02C8
		opword 0x38600003
		bl seqSetSeq
		opword 0x4800002C
		lwz r3, gp(r13)
		opword 0x38A0003D
		opword 0x38000038
		opword 0x389F0214
		opword 0x90A30110
		opword 0x38600003
		opword 0x38A00000
		lwz r6, gp(r13)
		opword 0x90060108
		bl seqSetSeq
	}
}
#pragma pop
#endif
#pragma defer_codegen reset


























__declspec(section ".data") void* jumptable_8034A058[25] = { (char*)continueGame + 0xBC, (char*)continueGame + 0xEC, (char*)continueGame + 0x118, (char*)continueGame + 0x144, (char*)continueGame + 0x170, (char*)continueGame + 0x19C, (char*)continueGame + 0x1C8, (char*)continueGame + 0x1F4, (char*)continueGame + 0x220, (char*)continueGame + 0x24C, (char*)continueGame + 0x278, (char*)continueGame + 0x2A4, (char*)continueGame + 0x2D0, (char*)continueGame + 0x2FC, (char*)continueGame + 0x328, (char*)continueGame + 0x354, (char*)continueGame + 0x380, (char*)continueGame + 0x3AC, (char*)continueGame + 0x3D8, (char*)continueGame + 0x404, (char*)continueGame + 0x430, (char*)continueGame + 0x45C, (char*)continueGame + 0x488, (char*)continueGame + 0x4B4, (char*)continueGame + 0x514 };
#pragma force_active on
__declspec(section ".data") u32 gap_05_8034A0BC_data[1] = {0};

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".sdata2") const u32 dat_8041bd68 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bd6c = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bd70 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bd74 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bd78 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bd7c = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bd80 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bd84 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bd88 = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041bd8c = 0x80808080;
__declspec(section ".sdata2") const u32 dat_8041bd90 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bd94 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bd98 = 0xC0C0C0FF;
__declspec(section ".sdata2") const u32 dat_8041bd9c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bda0 = 0x202020FF;
__declspec(section ".sdata2") const u32 dat_8041bda4 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bda8 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bdac = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdb0 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdb4 = 0x00000040;
__declspec(section ".sdata2") const u32 dat_8041bdb8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdbc = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdc0 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdc4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdc8 = 0x00000040;
__declspec(section ".sdata2") const u32 dat_8041bdcc = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdd0 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdd4 = 0x00000080;
__declspec(section ".sdata2") const u32 dat_8041bdd8 = 0x00000080;
__declspec(section ".sdata2") const char str_8041BDDC[8] = "next\0\0\0";
__declspec(section ".sdata2") const f32 float_0_8041bde4 = 0.0f;
__declspec(section ".sdata2") const f32 float_1_8041bde8 = 1.0f;
__declspec(section ".sdata2") const f32 float_neg304_8041bdec = -304.0f;
__declspec(section ".sdata2") const f32 float_240_8041bdf0 = 240.0f;
__declspec(section ".sdata2") const f32 float_neg240_8041bdf4 = -240.0f;
__declspec(section ".sdata2") const f32 float_neg272_8041bdf8 = -272.0f;
__declspec(section ".sdata2") const f32 float_272_8041bdfc = 272.0f;
__declspec(section ".sdata2") const f32 float_304_8041be00 = 304.0f;
__declspec(section ".sdata2") const f32 float_60_8041be04 = 60.0f;
__declspec(section ".sdata2") const f32 float_neg250_8041be08 = -250.0f;
__declspec(section ".sdata2") const f32 float_200_8041be0c = 200.0f;
__declspec(section ".sdata2") const f32 float_500_8041be10 = 500.0f;
__declspec(section ".sdata2") const f32 float_40_8041be14 = 40.0f;
__declspec(section ".sdata2") const f32 float_20_8041be18 = 20.0f;
__declspec(section ".sdata2") const f32 float_0p6_8041be1c = 0.6f;
__declspec(section ".sdata2") const f32 float_100_8041be20 = 100.0f;
__declspec(section ".sdata2") const f32 float_84_8041be24 = 84.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041be28 = 0.5f;
__declspec(section ".sdata2") const f32 float_12_8041be2c = 12.0f;
__declspec(section ".sdata2") const f32 float_70_8041be30 = 70.0f;
__declspec(section ".sdata2") const char str_8041BE34[8] = "\x82W\x82W\0\0\0";
__declspec(section ".sdata2") const f32 float_30_8041be3c = 30.0f;
__declspec(section ".sdata2") const char str_8041BE40[4] = " \0\0";
__declspec(section ".sdata2") const f32 float_8_8041be44 = 8.0f;
__declspec(section ".sdata2") const f32 float_22_8041be48 = 22.0f;
__declspec(section ".sdata2") const f32 float_1p5_8041be4c = 1.5f;
__declspec(section ".sdata2") const f32 float_106_8041be50 = 106.0f;
__declspec(section ".sdata2") const f32 float_52_8041be54 = 52.0f;
__declspec(section ".sdata2") const f32 float_0p05_8041be58 = 0.05f;
__declspec(section ".sdata2") const f32 float_120_8041be5c = 120.0f;
__declspec(section ".sdata2") const f32 float_140_8041be60 = 140.0f;
__declspec(section ".sdata2") const f32 float_neg150_8041be64 = -150.0f;
__declspec(section ".sdata2") const f32 float_300_8041be68 = 300.0f;
__declspec(section ".sdata2") const f32 float_50_8041be6c = 50.0f;
__declspec(section ".sdata2") const f32 float_2_8041be70 = 2.0f;
__declspec(section ".sdata2") const f32 float_neg74_8041be74 = -74.0f;
__declspec(section ".sdata2") const f32 float_4_8041be78 = 4.0f;
__declspec(section ".sdata2") const f32 float_0p25_8041be7c = 0.25f;
__declspec(section ".sdata2") const f32 float_0p125_8041be80 = 0.125f;
__declspec(section ".sdata2") const f32 float_1000_8041be84 = 1000.0f;
#endif
