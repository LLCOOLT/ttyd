// FAKE: whole unit as G5 asm stopgap; C under #ifdef NONMATCHING. Best pure C: 3/6 (effFallMain 99.15, effFallDispWater 99.35, effFallEntry 99.93).
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
__declspec(section ".rodata") extern const f32 vec3_802fe418[3];
__declspec(section ".rodata") extern const f32 vec3_802fe424[3];
__declspec(section ".rodata") extern const u32 dat_802fe430[12];
__declspec(section ".rodata") extern const f32 vec3_802fe460[3];
__declspec(section ".rodata") extern const f32 vec3_802fe46c[3];
__declspec(section ".rodata") extern const f64 double_to_int_mask_802fe478;
__declspec(section ".rodata") extern const f64 double_to_int_802fe480;
__declspec(section ".rodata") extern const char str_802FE488[24];
__declspec(section ".rodata") extern const char str_802FE4A0[24];
__declspec(section ".rodata") extern const char str_802FE4B8[28];
__declspec(section ".rodata") extern const char str_802FE4D4[28];
__declspec(section ".rodata") extern const char str_802FE4F0[28];
__declspec(section ".rodata") extern const char str_802FE50C[32];
__declspec(section ".rodata") extern const char str_802FE52C[28];
__declspec(section ".rodata") extern const char str_802FE548[12];
__declspec(section ".rodata") extern const char str_802FE554[12];
__declspec(section ".rodata") extern const char str_802FE560[12];
__declspec(section ".rodata") extern const char str_802FE56C[12];
__declspec(section ".rodata") extern const char str_802FE578[12];
__declspec(section ".rodata") extern const char str_802FE584[28];
__declspec(section ".sdata2") extern const u32 dat_80420f48;
__declspec(section ".sdata2") extern const u32 dat_80420f4c;
__declspec(section ".sdata2") extern const u32 dat_80420f50;
__declspec(section ".sdata2") extern const u32 dat_80420f54;
__declspec(section ".sdata2") extern const u32 dat_80420f58;
__declspec(section ".sdata2") extern const u32 dat_80420f5c;
__declspec(section ".sdata2") extern const u32 dat_80420f60;
__declspec(section ".sdata2") extern const u32 dat_80420f64;
__declspec(section ".sdata2") extern const u32 dat_80420f68;
__declspec(section ".sdata2") extern const u32 dat_80420f6c;
__declspec(section ".sdata2") extern const f32 float_deg2rad_80420f70;
__declspec(section ".sdata2") extern const f32 float_64_80420f74;
__declspec(section ".sdata2") extern const f32 float_704_80420f78;
__declspec(section ".sdata2") extern const f32 float_0p5_80420f7c;
__declspec(section ".sdata2") extern const f32 float_1_80420f80;
__declspec(section ".sdata2") extern const f32 float_0_80420f84;
__declspec(section ".sdata2") extern const f32 float_2_80420f88;
__declspec(section ".sdata2") extern const f32 float_0p56_80420f8c;
__declspec(section ".sdata2") extern const f32 float_0p4_80420f90;
__declspec(section ".sdata2") extern const f32 float_0p8_80420f94;
__declspec(section ".sdata2") extern const f32 float_0p125_80420f98;
__declspec(section ".sdata2") extern const f32 float_0p7_80420f9c;
__declspec(section ".sdata2") extern const f32 float_0p25_80420fa0;
__declspec(section ".sdata2") extern const f32 float_6p2832_80420fa4;
__declspec(section ".sdata2") extern const f32 float_360_80420fa8;
__declspec(section ".sdata2") extern const f32 float_2p05_80420fac;
__declspec(section ".sdata2") extern const f32 float_10_80420fb0;
__declspec(section ".sdata2") extern const f32 float_2p1_80420fb4;
__declspec(section ".sdata2") extern const f32 float_42p667_80420fb8;
__declspec(section ".sdata2") extern const f32 float_0p33333_80420fbc;
__declspec(section ".sdata2") extern const f32 float_180_80420fc0;
__declspec(section ".sdata2") extern const f32 float_neg200_80420fc4;
__declspec(section ".sdata2") extern const f32 float_200_80420fc8;
__declspec(section ".sdata2") extern const f32 float_neg82p655_80420fcc;
__declspec(section ".sdata2") extern const f32 float_88p8_80420fd0;
__declspec(section ".sdata2") extern const f32 float_1p03_80420fd4;
__declspec(section ".sdata2") extern const f32 float_82p655_80420fd8;
__declspec(section ".sdata2") extern const f32 float_neg88p8_80420fdc;
__declspec(section ".sdata2") extern const f32 float_30_80420fe0;
__declspec(section ".sdata2") extern const f32 float_neg0p3_80420fe4;
__declspec(section ".sdata2") extern const f32 float_35_80420fe8;
__declspec(section ".sdata2") extern const f32 float_62p832_80420fec;
__declspec(section ".sdata2") extern const f32 float_60_80420ff0;
__declspec(section ".sdata2") extern const f32 float_16_80420ff4;
__declspec(section ".sdata2") extern const f32 float_neg16_80420ff8;
__declspec(section ".sdata2") extern const f32 float_128_80420ffc;
__declspec(section ".sdata2") extern const f32 float_8p5333_80421000;
__declspec(section ".sdata2") extern const f32 float_0p066667_80421004;
__declspec(section ".sdata2") extern const f32 float_600_80421008;
__declspec(section ".sdata2") extern const f32 float_0p9_8042100c;
__declspec(section ".sdata2") extern const f32 float_0p01_80421010;
__declspec(section ".sdata2") extern const f32 float_0p2_80421014;
__declspec(section ".sdata2") extern const char str_80421018[4];
__declspec(section ".sdata2") extern const f32 float_neg0p5_8042101c;
__declspec(section ".sdata2") extern const f32 float_430_80421020;
__declspec(section ".sdata2") extern const f32 float_neg27_80421024;
__declspec(section ".sdata2") extern const f32 float_80_80421028;
__declspec(section ".sdata2") extern const char str_8042102C[4];
__declspec(section ".sdata2") extern const f32 float_5_80421030;
__declspec(section ".sdata2") extern const f32 float_0p00761_80421034;
__declspec(section ".sdata2") extern const f32 float_0p16605_80421038;
__declspec(section ".sdata2") extern const f32 float_3p1416_8042103c;
__declspec(section ".sdata2") extern const f32 float_1p5708_80421040;
__declspec(section ".sdata2") extern const f32 float_4p7124_80421044;
__declspec(section ".sdata2") extern const f32 float_0p03705_80421048;
__declspec(section ".sdata2") extern const f32 float_0p4967_8042104c;
__declspec(section ".sdata2") extern const f32 float_40_80421050;
__declspec(section ".sdata2") extern const char str_80421054[4];
__declspec(section ".sdata2") extern const char str_80421058[8];
__declspec(section ".sdata2") extern const f32 float_300_80421060;
__declspec(section ".sdata2") extern const f32 float_1p2_80421064;
__declspec(section ".sdata2") extern const f32 float_1p6_80421068;
__declspec(section ".sdata2") extern const f32 float_0p1_8042106c;
__declspec(section ".sdata2") extern const f32 float_0p6_80421070;
__declspec(section ".sdata2") extern const f32 float_1p3_80421074;
__declspec(section ".sdata2") extern const f32 float_400_80421078;
#define white255 (*(const GXColor*)&dat_80420f54)
#endif

extern double sin(double);
extern double cos(double);

typedef struct EffFallWork {
    s32 type;       // 0x0
    Vec position;   // 0x4
    u8 pad10[0x6C - 0x10];
    Vec pos2;       // 0x6C
    u8 pad78[0x80 - 0x78];
    f32 angle;      // 0x80
    u8 pad84[0x8C - 0x84];
    s32 timer;      // 0x8C
    u8 pad90[0x94 - 0x90];
    f32 scale;      // 0x94
    u8 pad98[0xA0 - 0x98];
    s32 state;      // 0xA0
    u32 alpha;      // 0xA4
    u8 padA8[0xB0 - 0xA8];
    f32 rotation;   // 0xB0
    u8 padB4[0xB8 - 0xB4];
    Vec pos3;       // 0xB8
    s32 pose0;      // 0xC4
    s32 pose1;      // 0xC8
} EffFallWork;

typedef struct EffFallVtx {
    f32 x, y, z;
    f32 u, v;
} EffFallVtx;

typedef struct EffFallElem {
    s32 type;         // 0x0
    Vec pos;          // 0x4
    f32 arg4;         // 0x10
    f32 arg5;         // 0x14
    f32 rotY;         // 0x18
    s32 arg7;         // 0x1C
    s32 arg8;         // 0x20
    s32 timer;        // 0x24
    s32 scroll;       // 0x28
    f32 scale;        // 0x2C
    f32 f30;          // 0x30
    f32 f34;          // 0x34
    s32 state;        // 0x38
    s32 alpha;        // 0x3C
    EffFallVtx** vtx; // 0x40
    f32 f44;          // 0x44
    f32 rot2;         // 0x48
    f32 rot3;         // 0x4C
    Vec vel;          // 0x50
    s32 pose0;        // 0x5C
    s32 pose1;        // 0x60
    s32 sfx;          // 0x64
} EffFallElem;

#pragma force_active on // FAKE: keep asm-only-referenced data from being dead-stripped
__declspec(section ".data") f32 lbl_803ADD20[] = { -1.0f, 1.0f };
__declspec(section ".data") static f32 negone_one_374[] = { -1.0f, 1.0f };
__declspec(section ".data") f32 lbl_803ADD30[] = { 1.0f, -1.0f };
__declspec(section ".data") static f32 one_negone_373[] = { 1.0f, -1.0f };
__declspec(section ".data") f32 lbl_803ADD40[] = { -1.0f, 1.0f };
__declspec(section ".data") static f32 negone_one_360[] = { -1.0f, 1.0f };
__declspec(section ".data") f32 lbl_803ADD50[] = { 1.0f, -1.0f };
__declspec(section ".data") static f32 one_negone_359[] = { 1.0f, -1.0f };
static s16 shibuki_vertex_tbl[] = { -14012, 946, -2560, -7355, 946, -2560, -697, 946, -2560, 5959, 946, -2560, 12617, 946, -2560, -17337, 7417, -2560, -8130, 10717, -2560, -697, 12271, -2560, 6734, 10717, -2560, 15942, 7417, -2560, -23097, 11535, -2560, -11577, 18594, -2560, -697, 20431, -2560, 10822, 18594, -2560, 21702, 11535, -2560, -14777, 3888, -2560, -7591, 3922, -2560, -697, 3922, -2560, 6195, 3922, -2560, 13262, 3922, -2560, -19292, 8815, -2560, -9810, 14556, -2560, -697, 16241, -2560, 8831, 14757, -2560, 17896, 8815, -2560, -12537, 0, -3520, 262, 0, -3520, 13062, 0, -3520, -12537, 1702, -3520, 262, 4006, -3520, 13062, 1702, -3520, -12537, 4940, -3520, 262, 8012, -3520, 13062, 4940, -3520, 10533, 5964, -3520, 10439, 2726, -3520, 10468, 0, -3520, -10037, 5964, -3520, -10021, 2726, -3520, -10006, 0, -3520, 0, 0, 0, 0, 0, 0, 0, 0 };
static s16 shibuki_texcoord0_tbl[] = { 0, 12018, 4096, 12749, 4096, 14745, 0, 14745, 8192, 13023, 8192, 14745, 12288, 12749, 12288, 14745, 16384, 12018, 16384, 14745, 0, 1638, 4096, 1638, 4096, 4997, 0, 5968, 8192, 1638, 8192, 5003, 12288, 1638, 12288, 4830, 16384, 1638, 16384, 5968, 0, 8192, 4096, 8192, 8192, 8192, 12288, 8192, 16384, 8192, -3220, 8192, -16384, 8192, -16384, 16384, -3240, 16384, 13026, 8192, 16384, 16384, 13064, 16384, -3200, 0, -16384, 0, 13147, 0, 16384, 0, 0, 0, 0, 16384, 0, 0, 0, 0 };
static u8 shibuki_dl_0_0[] = { 0x98, 0x00, 0x0A, 0x0A, 0x00, 0x00, 0x0A, 0x0B, 0x00, 0x00, 0x0B, 0x14, 0x00, 0x00, 0x0D, 0x15, 0x00, 0x02, 0x0C, 0x05, 0x00, 0x00, 0x14, 0x06, 0x00, 0x03, 0x15, 0x0F, 0x00, 0x00, 0x00, 0x10, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static u8 shibuki_dl_0_1[] = { 0x98, 0x00, 0x0A, 0x0B, 0x00, 0x00, 0x0B, 0x0C, 0x00, 0x00, 0x0E, 0x15, 0x00, 0x02, 0x0C, 0x16, 0x00, 0x02, 0x0F, 0x06, 0x00, 0x03, 0x15, 0x07, 0x00, 0x03, 0x16, 0x10, 0x00, 0x01, 0x01, 0x11, 0x00, 0x01, 0x04, 0x01, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static u8 shibuki_dl_0_2[] = { 0x98, 0x00, 0x0A, 0x0C, 0x00, 0x00, 0x0E, 0x0D, 0x00, 0x00, 0x10, 0x16, 0x00, 0x02, 0x0F, 0x17, 0x00, 0x02, 0x11, 0x07, 0x00, 0x03, 0x16, 0x08, 0x00, 0x03, 0x17, 0x11, 0x00, 0x01, 0x04, 0x12, 0x00, 0x01, 0x06, 0x02, 0x00, 0x00, 0x05, 0x03, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static u8 shibuki_dl_0_3[] = { 0x98, 0x00, 0x0A, 0x0D, 0x00, 0x00, 0x10, 0x0E, 0x00, 0x00, 0x12, 0x17, 0x00, 0x02, 0x11, 0x18, 0x00, 0x00, 0x13, 0x08, 0x00, 0x03, 0x17, 0x09, 0x00, 0x00, 0x18, 0x12, 0x00, 0x01, 0x06, 0x13, 0x00, 0x00, 0x08, 0x03, 0x00, 0x00, 0x07, 0x04, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static s8 shibuki_normal_tbl[] = { 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static u8 shibuki_color0_tbl[] = { 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0x19, 0xFF, 0xFF, 0xFF, 0x4C, 0xB6, 0xCC, 0xCB, 0x33, 0xB6, 0xCC, 0xCB, 0x4C, 0xB6, 0xCC, 0xCB, 0x99, 0xB6, 0xCC, 0xCB, 0x00 };
static u8 shibuki_dl_1_0[] = { 0x98, 0x00, 0x06, 0x1F, 0x00, 0x07, 0x24, 0x25, 0x00, 0x04, 0x20, 0x1C, 0x00, 0x07, 0x14, 0x26, 0x00, 0x04, 0x19, 0x19, 0x00, 0x07, 0x25, 0x27, 0x00, 0x06, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00 };
static u8 shibuki_dl_1_1[] = { 0x98, 0x00, 0x06, 0x20, 0x00, 0x04, 0x24, 0x22, 0x00, 0x04, 0x22, 0x1D, 0x00, 0x05, 0x14, 0x23, 0x00, 0x04, 0x1D, 0x1A, 0x00, 0x06, 0x25, 0x24, 0x00, 0x06, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00 };
static u8 shibuki_dl_1_2[] = { 0x98, 0x00, 0x06, 0x22, 0x00, 0x04, 0x22, 0x21, 0x00, 0x07, 0x23, 0x23, 0x00, 0x04, 0x1D, 0x1E, 0x00, 0x07, 0x18, 0x24, 0x00, 0x06, 0x1F, 0x1B, 0x00, 0x07, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00 };
static u8 shibuki_dl_1_3[] = { 0x98, 0x00, 0x06, 0x25, 0x00, 0x04, 0x20, 0x20, 0x00, 0x04, 0x21, 0x26, 0x00, 0x04, 0x19, 0x1D, 0x00, 0x05, 0x1A, 0x27, 0x00, 0x06, 0x1C, 0x1A, 0x00, 0x06, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00 };

s32 evt_cam_shake(EventEntry* event, BOOL isFirstCall);

static EVT_BEGIN(evt_shake)
    CALL(evt_cam_shake, 4, FLOAT(0.009765625f), FLOAT(0.009765625f), 300)
    RETURN
EVT_END()

s32 psndSFXOn_3D(const char* name, Vec* position);
void psndSFXOff(s32 id);
extern EffectEntry* effWaterDamageN64Entry(s32 type, s32 count, f32 x, f32 y, f32 z, f32 scale);
EffectEntry* effKemuri1N64Entry(s32 type, f32 a2, f32 a3, f32 a4, f32 a5);
void effFallMain(EffectEntry* effect);
void effFallDisp(CameraId cameraId, EffectEntry* effect);
void effFallDispInseki(CameraId cameraId, EffectEntry* effect);
void effFallDispWater(CameraId cameraId, EffectEntry* effect);

#ifdef NONMATCHING
static inline f32 fall_sinf(f32 x) {
    f32 a = 0.00761f;
    f32 b = EXT_LIT(float_0p16605_80421038, 0.16605f);
    f32 c = EXT_LIT(float_1_80420f80, 1.0f);
    f32 y;
    f32 x2;

    if (x <= EXT_LIT(float_3p1416_8042103c, 3.1415927f)) {
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
    else if (x < EXT_LIT(float_4p7124_80421044, 4.712389f)) {
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
#endif

#ifdef NONMATCHING
static inline f32 fall_cosf(f32 x) {
    f32 a = 0.03705f;
    f32 b = EXT_LIT(float_0p4967_8042104c, 0.4967f);
    f32 c = EXT_LIT(float_1_80420f80, 1.0f);
    f32 y;
    f32 x2;

    if (x <= EXT_LIT(float_3p1416_8042103c, 3.1415927f)) {
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
    else if (x < EXT_LIT(float_4p7124_80421044, 4.712389f)) {
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
#endif

EffectEntry* effFallEntry(s32 type, f32 x, f32 y, f32 z, f32 arg4, f32 arg5, f32 arg6, s32 arg7, s32 arg8);
void DCFlushRange(void* addr, u32 nBytes);
void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXCallDisplayList(void* list, u32 nbytes);
void GXClearVtxDesc(void);
u16 GXGetTexObjHeight(const GXTexObj* to);
void GXLoadPosMtxImm(const f32 mtx[3][4], u32 id);
void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXSetArray(GXAttr attr, void* base_ptr, u8 stride);
void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn);
void GXSetChanMatColor(GXChannelID chan, GXColor mat_color);
void GXSetCullMode(GXCullMode mode);
void GXSetCurrentMtx(u32 id);
void GXSetNumChans(u8 nChans);
void GXSetNumTevStages(u8 nStages);
void GXSetNumTexGens(u8 nTexGens);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColor(GXTevRegID id, GXColor color);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevOp(GXTevStageID id, GXTevMode mode);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx);
void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac);
void GXSetVtxDesc(GXAttr attr, GXAttrType type);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXIdentity(Mtx m);
void PSMTXRotAxisRad(Mtx m, const Vec* axis, f32 rad);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
extern void* jumptable_803AE070[];
extern void* jumptable_803AE04C[];
extern void* jumptable_803AE024[];
#ifdef NONMATCHING
EffectEntry* effFallEntry(s32 type, f32 x, f32 y, f32 z, f32 arg4, f32 arg5, f32 arg6, s32 arg7, s32 arg8) {
    const char* sfxName;
    EffectEntry* effect;
    EffFallElem* e;
    s32 i;
    EffFallElem* w;
    s32 count;
    f32 a;
    f32 r;

    effect = effEntry();
    count = arg7 + 1;
    switch (type) {
    case 0:
        count = arg7 + 1;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        arg7 = 1;
        count = 2;
        break;
    }
    effect->type = "Fall";
    effect->count = count;
    w = __memAlloc(HEAP_EFFECT, effect->count * sizeof(EffFallElem));
    effect->userdata = w;
    effect->callback = effFallMain;
    effect->flags |= 2;
    sfxName = (0, "SFX_BTL_STAGE_FALL_WATER1\0\0");
    w->type = type;
    w->pos.x = x;
    w->pos.y = y;
    w->pos.z = z;
    w->arg4 = arg4;
    w->arg5 = arg5;
    w->rotY = arg6;
    w->arg7 = arg7;
    w->timer = 0;
    w->scroll = 0;
    w->arg8 = arg8;
    w->pose0 = -1;
    w->pose1 = -1;
    for (i = 1, e = w + 1; i < effect->count; i++, e++) {
        a = 3.1415927f * irand(360) / 180.0f;
        r = irand((s32)arg4);
        e->pos.x = r * (f32)sin(a);
        e->pos.y = EXT_LIT(float_300_80421060, 300.0f) + irand(effect->count);
        e->pos.z = r * (f32)cos(a);
        e->timer = 0;
        e->scroll = 0;
        e->alpha = 255;
        e->rot2 = EXT_LIT(float_0_80420f84, 0.0f);
        e->rotY = irand(100) > 50 ? 0 : 180;
        e->state = 0;
        e->pose0 = -1;
        e->pose1 = -1;
        switch (type) {
            case 0:
            case 1:
                e->f34 = EXT_LIT(float_0_80420f84, 0.0f);
                e->f30 = EXT_LIT(float_0p2_80421014, 0.2f);
                if (i == 1) {
                    e->pos.x = 0.0f;
                    e->pos.z = EXT_LIT(float_0_80420f84, 0.0f);
                    e->timer = 0;
                } else {
                    e->timer = irand(effect->count) + 60;
                }
                e->scale = type == 0 ? EXT_LIT(float_0p5_80420f7c, 0.5f) : EXT_LIT(float_1p2_80421064, 1.2f);
                break;
            case 2:
                e->f34 = EXT_LIT(float_0_80420f84, 0.0f);
                e->f30 = EXT_LIT(float_1p6_80421068, 1.6f);
                e->pos.x = EXT_LIT(float_0_80420f84, 0.0f);
                e->pos.z = EXT_LIT(float_0_80420f84, 0.0f);
                e->timer = 0;
                e->f44 = EXT_LIT(float_0_80420f84, 0.0f);
                e->scale = EXT_LIT(float_0p5_80420f7c, 0.5f);
                break;
            case 3: {
                e->f34 = 0.0f;
                e->f30 = EXT_LIT(float_0p1_8042106c, 0.1f);
                e->pos.x = EXT_LIT(float_0_80420f84, 0.0f);
                e->pos.y = EXT_LIT(float_200_80420fc8, 200.0f);
                e->pos.z = EXT_LIT(float_0_80420f84, 0.0f);
                e->vel.x = EXT_LIT(float_0_80420f84, 0.0f);
                e->vel.y = EXT_LIT(float_0_80420f84, 0.0f);
                e->vel.z = EXT_LIT(float_0_80420f84, 0.0f);
                e->scale = EXT_LIT(float_1_80420f80, 1.0f);
                {
                    Vec v = { 0.0f, 0.0f, 0.0f };
                    v.x = x;
                    v.y = y;
                    v.z = z;
                    e->sfx = psndSFXOn_3D(sfxName, &v);
                }
                break;
            }
            case 4:
            case 5:
                e->f34 = EXT_LIT(float_0_80420f84, 0.0f);
                e->f30 = EXT_LIT(float_0p6_80421070, 0.6f);
                e->pos.x = EXT_LIT(float_0_80420f84, 0.0f);
                e->pos.z = EXT_LIT(float_0_80420f84, 0.0f);
                e->timer = 0;
                e->scale = EXT_LIT(float_1_80420f80, 1.0f);
                break;
            case 6:
                e->pos.x = EXT_LIT(float_0_80420f84, 0.0f);
                e->pos.y = EXT_LIT(float_200_80420fc8, 200.0f);
                e->pos.z = EXT_LIT(float_0_80420f84, 0.0f);
                e->vel.x = -e->pos.x / EXT_LIT(float_30_80420fe0, 30.0f);
                e->vel.y = -e->pos.y / EXT_LIT(float_30_80420fe0, 30.0f);
                e->vel.z = -e->pos.z / EXT_LIT(float_30_80420fe0, 30.0f);
                e->scale = EXT_LIT(float_1p3_80421074, 1.3f);
                e->rot2 = EXT_LIT(float_30_80420fe0, 30.0f);
                e->rot3 = EXT_LIT(float_0_80420f84, 0.0f);
                break;
            case 7:
                e->pos.x = EXT_LIT(float_400_80421078, 400.0f);
                e->pos.y = EXT_LIT(float_200_80420fc8, 200.0f);
                e->pos.z = EXT_LIT(float_0_80420f84, 0.0f);
                e->scale = EXT_LIT(float_0p5_80420f7c, 0.5f);
                break;
            case 8:
                e->f34 = EXT_LIT(float_0_80420f84, 0.0f);
                e->f30 = EXT_LIT(float_0p25_80420fa0, 0.25f);
                e->pos.x = EXT_LIT(float_0_80420f84, 0.0f);
                e->pos.y = EXT_LIT(float_400_80421078, 400.0f);
                e->pos.z = EXT_LIT(float_0_80420f84, 0.0f);
                e->scale = EXT_LIT(float_1_80420f80, 1.0f);
                break;
        }
    }
    return effect;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
EffectEntry* effFallEntry(s32 type, f32 x, f32 y, f32 z, f32 arg4, f32 arg5, f32 arg6, s32 arg7, s32 arg8) {
	char _af_pad[44];
	asm volatile {
		opword 0xFF000890
		mr r23, r3
		opword 0xFF201090
		opword 0x7C982378
		opword 0xFF401890
		opword 0x7CB92B78
		opword 0xFFE02090
		opword 0xFEE02890
		opword 0xFEC03090
		bl effEntry
		opword 0x2C170000
		opword 0x7C7C1B78
		opword 0x38980001
		opword 0x41820020
		opword 0x4180001C
		opword 0x2C170009
		opword 0x40800014
		opword 0x48000008
		opword 0x4800000C
		opword 0x3B000001
		opword 0x38800002
		la r0, str_80421058(r2)
		opword 0x38600003
		opword 0x901C0014
		opword 0x909C0008
		opword 0x801C0008
		opword 0x1C800068
		bl __memAlloc
		lis r4, effFallMain@ha
		opword 0x907C000C
		addi r0, r4, effFallMain@l
		lis r5, str_802FE584@ha
		opword 0x901C0010
		addi r29, r5, str_802FE584@l
		opword 0xFC00F81E
		lis r4, double_to_int_802fe480@ha
		opword 0x801C0000
		opword 0x38A00000
		lfd f27, double_to_int_802fe480@l(r4)
		opword 0x3B630068
		opword 0x60000002
		stfd f0, _af_pad+16(r1)
		lfs f28, float_3p1416_8042103c(r2)
		opword 0x3B400001
		opword 0x901C0000
		opword 0x3800FFFF
		opword 0x83C1001C
		opword 0x3FE04330
		opword 0x92E30000
		lfs f29, float_180_80420fc0(r2)
		opword 0xD3030004
		lfs f30, float_300_80421060(r2)
		opword 0xD3230008
		opword 0xD343000C
		opword 0xD3E30010
		lfs f31, float_0_80420f84(r2)
		opword 0xD2E30014
		opword 0xD2C30018
		opword 0x9303001C
		opword 0x90A30024
		opword 0x90A30028
		opword 0x93230020
		opword 0x9003005C
		opword 0x90030060
		opword 0x480002EC
		opword 0x38600168
		bl irand
		opword 0x6C608000
		opword 0x93E10018
		opword 0x7FC3F378
		opword 0x9001001C
		opword 0xC8010018
		opword 0xEC00D828
		opword 0xEC1C0032
		opword 0xEEE0E824
		bl irand
		opword 0x6C608000
		opword 0x93E10020
		opword 0xFC20B890
		opword 0x90010024
		opword 0xC8010020
		fsubs f22, f0, f27
		bl sin
		opword 0xFC000818
		opword 0xEC160032
		opword 0xD01B0004
		opword 0x807C0008
		bl irand
		opword 0x6C608000
		opword 0x93E10028
		opword 0xFC20B890
		opword 0x9001002C
		opword 0xC8010028
		opword 0xEC00D828
		opword 0xEC1E002A
		opword 0xD01B0008
		bl cos
		opword 0xFC000818
		opword 0x38800000
		opword 0x380000FF
		opword 0x38600064
		opword 0xEC160032
		opword 0xD01B000C
		opword 0x909B0024
		opword 0x909B0028
		opword 0x901B003C
		opword 0xD3FB0048
		bl irand
		opword 0x38A00032
		opword 0x54640FFE
		opword 0x7C032810
		opword 0x380000B4
		opword 0x54A30FFE
		opword 0x93E10030
		opword 0x7C632110
		opword 0x38800000
		opword 0x7C031878
		opword 0x3800FFFF
		opword 0x6C638000
		opword 0x28170008
		opword 0x90610034
		opword 0xC8010030
		opword 0xEC00D828
		opword 0xD01B0018
		opword 0x909B0038
		opword 0x901B005C
		opword 0x901B0060
		opword 0x418101E8
		lis r3, jumptable_803AE070@ha
		opword 0x56E0103A
		addi r3, r3, jumptable_803AE070@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		lfs f1, float_0_80420f84(r2)
		opword 0x2C1A0001
		lfs f0, float_0p2_80421014(r2)
		opword 0xD03B0034
		opword 0xD01B0030
		opword 0x40820018
		opword 0xD03B0004
		opword 0x38000000
		opword 0xD03B000C
		opword 0x901B0024
		opword 0x48000014
		opword 0x807C0008
		bl irand
		opword 0x3803003C
		opword 0x901B0024
		opword 0x2C170000
		opword 0x4082000C
		lfs f0, float_0p5_80420f7c(r2)
		opword 0x48000008
		lfs f0, float_1p2_80421064(r2)
		opword 0xD01B002C
		opword 0x48000178
		lfs f2, float_0_80420f84(r2)
		lfs f1, float_1p6_80421068(r2)
		opword 0xD05B0034
		lfs f0, float_0p5_80420f7c(r2)
		opword 0xD03B0030
		opword 0xD05B0004
		opword 0xD05B000C
		opword 0x909B0024
		opword 0xD05B0044
		opword 0xD01B002C
		opword 0x4800014C
		lfs f2, float_0_80420f84(r2)
		lis r3, vec3_802fe418@ha
		lfs f0, float_0p1_8042106c(r2)
		addi r7, r3, vec3_802fe418@l
		opword 0xD05B0034
		opword 0x7FA3EB78
		lfs f1, float_200_80420fc8(r2)
		opword 0x38810008
		opword 0xD01B0030
		lfs f0, float_1_80420f80(r2)
		opword 0xD05B0004
		opword 0xD03B0008
		opword 0xD05B000C
		opword 0xD05B0050
		opword 0xD05B0054
		opword 0xD05B0058
		opword 0xD01B002C
		opword 0x80C70000
		opword 0x80A70004
		opword 0x80070008
		opword 0x90C10008
		opword 0x90A1000C
		opword 0x90010010
		opword 0xD3010008
		opword 0xD321000C
		opword 0xD3410010
		bl psndSFXOn_3D
		opword 0x907B0064
		opword 0x480000D8
		lfs f2, float_0_80420f84(r2)
		opword 0x38000000
		lfs f1, float_0p6_80421070(r2)
		opword 0xD05B0034
		lfs f0, float_1_80420f80(r2)
		opword 0xD03B0030
		opword 0xD05B0004
		opword 0xD05B000C
		opword 0x901B0024
		opword 0xD01B002C
		opword 0x480000AC
		lfs f3, float_0_80420f84(r2)
		lfs f0, float_200_80420fc8(r2)
		opword 0xD07B0004
		lfs f2, float_30_80420fe0(r2)
		opword 0xD01B0008
		lfs f0, float_1p3_80421074(r2)
		opword 0xD07B000C
		opword 0xC03B0004
		opword 0xFC200850
		opword 0xEC211024
		opword 0xD03B0050
		opword 0xC03B0008
		opword 0xFC200850
		opword 0xEC211024
		opword 0xD03B0054
		opword 0xC03B000C
		opword 0xFC200850
		opword 0xEC211024
		opword 0xD03B0058
		opword 0xD01B002C
		opword 0xD05B0048
		opword 0xD07B004C
		opword 0x48000050
		lfs f1, float_400_80421078(r2)
		lfs f0, float_200_80420fc8(r2)
		opword 0xD03B0004
		lfs f1, float_0_80420f84(r2)
		opword 0xD01B0008
		lfs f0, float_0p5_80420f7c(r2)
		opword 0xD03B000C
		opword 0xD01B002C
		opword 0x4800002C
		lfs f2, float_0_80420f84(r2)
		lfs f0, float_0p25_80420fa0(r2)
		opword 0xD05B0034
		lfs f1, float_400_80421078(r2)
		opword 0xD01B0030
		lfs f0, float_1_80420f80(r2)
		opword 0xD05B0004
		opword 0xD03B0008
		opword 0xD05B000C
		opword 0xD01B002C
		opword 0x3B5A0001
		opword 0x3B7B0068
		opword 0x801C0008
		opword 0x7C1A0000
		opword 0x4180FD10
		opword 0x7F83E378
	}
}
#pragma pop
#endif
#pragma opt_propagation off

#ifdef NONMATCHING
static inline void effFallRelease(EffectEntry* effect) {
    EffFallElem* e;
    s32 i;
    for (i = 0, e = effect->userdata; i < effect->count; i++, e++) {
        if (e->pose0 != -1) {
            animPoseRelease(e->pose0);
        }
        if (e->pose1 != -1) {
            animPoseRelease(e->pose1);
        }
        psndSFXOff(e->sfx);
    }
}
#endif
#ifdef NONMATCHING
void effFallMain(EffectEntry* effect) {
    Vec sndPos;
    const char* bug[2];
    const char* fork1;
    s32 i;
    const char* meteor1;
    const char* light1;

    EffFallElem* e;
    const char* koopa1;
    s32 type;
    s32 arg8;
    s32 played;
    s32 done;
    s32 group;
    const char* meteor2;
    f32 y;
    f32 angle;
    f32 top;
    f32 arg4;
    f32 ground;
    f32 a;
    s32 j;
    f32 rotY;

    e = effect->userdata;
    {
        Vec v = { 0.0f, 0.0f, 0.0f };
        v.x = e->pos.x;
        v.y = (y = e->pos.y);
        v.z = e->pos.z;
        sndPos = v;
    }
    played = 0;
    ground = y + e->arg5;
    type = e->type;
    arg4 = e->arg4;
    rotY = e->rotY;
    arg8 = e->arg8;
    group = gp->inBattle != 0;
    if (effect->flags & 4) {
        effect->flags &= ~4;
        effFallRelease(effect);
        effDelete(effect);
        return;
    }
    bug[1] = "SFX_BTL_STAGE_FALL_BUG1";
    bug[0] = "SFX_BTL_STAGE_FALL_BUG2";
    fork1 = "SFX_BTL_STAGE_DAMAGE_FORK1\0";
    koopa1 = "SFX_BTL_STAGE_FALL_KOOPA1\0\0";
    meteor1 = "SFX_BTL_STAGE_FALL_METEOR1\0";
    meteor2 = "SFX_BTL_STAGE_DAMAGE_METEOR2\0\0\0";
    light1 = "SFX_BTL_STAGE_DAMAGE_LIGHT1";
    angle = EXT_LIT(float_6p2832_80420fa4, 6.2831855f) * rotY;
    top = EXT_LIT(float_30_80420fe0, 30.0f) + y;
    done = 0;
    for (i = 1, e++; i < effect->count; i++, e++) {
        switch (type) {
            case 0:
            case 1:
                switch (e->state) {
                    case 0:
                        if (e->timer) {
                            e->timer--;
                        }
                        if (e->timer == 0) {
                            e->state++;
                            if (type == 1) {
                                psndSFXOn_3D(bug[1], &sndPos);
                            } else if (i == 1) {
                                psndSFXOn_3D(bug[0], &sndPos);
                            }
                        }
                        break;
                    case 1:
                        if (type == 0 && i > 1 && !played && gp->retraceCount % 6 == 0) {
                            psndSFXOn_3D(bug[0], &sndPos);
                            played = 1;
                        }
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        if (distABf(e->pos.x, e->pos.z, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_0_80420f84, 0.0f)) < arg4 / EXT_LIT(float_2_80420f88, 2.0f)) {
                            if (e->pos.y < ground) {
                                e->pos.y = ground;
                                e->f34 *= EXT_LIT(float_neg0p3_80420fe4, -0.3f);
                                e->state++;
                            }
                        } else if (e->pos.y < y) {
                            e->pos.y = y;
                            e->f34 *= EXT_LIT(float_neg0p3_80420fe4, -0.3f);
                            e->state++;
                        }
                        break;
                    case 2:
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        a = (EXT_LIT(float_6p2832_80420fa4, 6.2831855f) * angleABf(EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_0_80420f84, 0.0f), e->pos.x, e->pos.z)) / EXT_LIT(float_360_80420fa8, 360.0f);
                        if (i == 1) {
                            a = angle / 360.0f;
                        }
                        e->pos.x += EXT_LIT(float_0p5_80420f7c, 0.5f) * (f32)sin(a);
                        e->pos.z += EXT_LIT(float_0p5_80420f7c, 0.5f) * -(f32)cos(a);
                        if (e->pos.y < y) {
                            e->pos.y = y;
                            e->timer = 0;
                            e->state++;
                        }
                        break;
                    case 3:
                        e->timer++;
                        if (e->timer > 30) {
                            e->state++;
                        }
                        break;
                    case 4:
                        e->alpha -= 10;
                        if (e->alpha < 0) {
                            e->alpha = 0;
                            e->state++;
                        }
                        break;
                    case 5:
                        done++;
                        break;
                }
                if (((gp->retraceCount >> 1) >> 1) & 1) {
                    e->scroll++;
                }
                if (e->scroll >= 3) {
                    e->scroll = 0;
                }
                e->rot2 = EXT_LIT(float_35_80420fe8, 35.0f) * (f32)sin(gp->retraceCount / EXT_LIT(float_2_80420f88, 2.0f) + i);
                break;
            case 2:
                switch (e->state) {
                    case 0:
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        if (e->pos.y < y) {
                            e->pos.y = y;
                            e->timer = 0;
                            e->state++;
                            psndSFXOn_3D(fork1, &sndPos);
                        }
                        break;
                    case 1:
                        a = (f32)sin((EXT_LIT(float_62p832_80420fec, 62.831856f) * e->timer) / EXT_LIT(float_60_80420ff0, 60.0f));
                        e->f44 = ((EXT_LIT(float_60_80420ff0, 60.0f) - e->timer) * a) / EXT_LIT(float_60_80420ff0, 60.0f);
                        e->timer++;
                        if (e->timer > 60) {
                            e->state++;
                        }
                        break;
                    case 2:
                        e->timer++;
                        if (e->timer > 30) {
                            e->state++;
                        }
                        break;
                    case 3:
                        e->alpha -= 10;
                        if (e->alpha < 0) {
                            e->alpha = 0;
                            e->state++;
                        }
                        break;
                    case 4:
                        done++;
                        break;
                }
                e->vtx = (EffFallVtx**)smartAlloc(0x280, 3);
                {
                    EffFallVtx* v = *e->vtx;
                    for (j = 0; j < 32; j++, v++) {
                        v->x = (j & 1) ? 16.0f : -16.0f;
                        v->y = EXT_LIT(float_128_80420ffc, 128.0f) - 8.533334f * (j / 2);
                        v->z = EXT_LIT(float_0_80420f84, 0.0f);
                        v->u = (j & 1) ? EXT_LIT(float_2_80420f88, 2.0f) : EXT_LIT(float_0_80420f84, 0.0f);
                        v->v = EXT_LIT(float_0p066667_80421004, 0.06666667f) * (j / 2);
                    }
                }
                {
                    EffFallVtx* v = *e->vtx;
                    for (i = 0; i < 32; i++, v++) {
                        v->x += e->f44 * ((v->y * v->y) / 600.0f);
                    }
                }
                DCFlushRange(*e->vtx, 0x280);
                break;
            case 3:
                switch (e->state) {
                    case 0:
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        if (e->pos.y < y) {
                            e->pos.y = y;
                            e->timer = 0;
                            e->state++;
                        }
                        break;
                    case 1:
                        if (e->timer % 10 == 0) {
                            effWaterDamageN64Entry(4, 20, sndPos.x, sndPos.y, sndPos.z, 1.0f);
                        }
                        e->timer++;
                        if (e->timer > arg8) {
                            e->state++;
                        }
                        break;
                    case 2:
                        e->alpha *= EXT_LIT(float_0p9_8042100c, 0.9f);
                        e->scale *= EXT_LIT(float_0p9_8042100c, 0.9f);
                        if (e->scale < EXT_LIT(float_0p01_80421010, 0.01f)) {
                            psndSFXOff(e->sfx);
                            effDelete(effect);
                            return;
                        }
                        break;
                }
                e->vel.y -= EXT_LIT(float_0p2_80421014, 0.2f);
                break;
            case 4:
            case 5:
                switch (e->state) {
                    case 0:
                        if (type == 5) {
                            if (!animGroupBaseAsync("EFF_Baketu\0", group, 0)) {
                                break;
                            }
                            if (e->pose0 == -1) {
                                e->pose0 = animPoseEntry("EFF_Baketu\0", group);
                                animPoseSetAnim(e->pose0, "Z_1", 1);
                            }
                        } else {
                            if (!animGroupBaseAsync("EFF_Tarai\0\0", group, 0)) {
                                break;
                            }
                            if (e->pose0 == -1) {
                                e->pose0 = animPoseEntry("EFF_Tarai\0\0", group);
                                animPoseSetAnim(e->pose0, "Z_1", 1);
                            }
                        }
                        if (e->timer) {
                            e->timer--;
                        }
                        if (e->timer == 0) {
                            e->state++;
                        }
                        break;
                    case 1:
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        if (distABf(e->pos.x, e->pos.z, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_0_80420f84, 0.0f)) < arg4 / EXT_LIT(float_2_80420f88, 2.0f)) {
                            if (e->pos.y < ground) {
                                e->pos.y = ground;
                                e->f34 *= EXT_LIT(float_neg0p3_80420fe4, -0.3f);
                                e->state++;
                            }
                        } else if (e->pos.y < y) {
                            e->pos.y = y;
                            e->f34 *= EXT_LIT(float_neg0p3_80420fe4, -0.3f);
                            e->state++;
                        }
                        break;
                    case 2:
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        a = (EXT_LIT(float_6p2832_80420fa4, 6.2831855f) * angleABf(EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_0_80420f84, 0.0f), e->pos.x, e->pos.z)) / EXT_LIT(float_360_80420fa8, 360.0f);
                        if (i == 1) {
                            a = angle / 360.0f;
                        }
                        e->pos.x += EXT_LIT(float_2_80420f88, 2.0f) * (f32)sin(a);
                        e->pos.z += EXT_LIT(float_2_80420f88, 2.0f) * -(f32)cos(a);
                        if (e->pos.y < y) {
                            e->pos.y = y;
                            e->f34 *= EXT_LIT(float_neg0p5_8042101c, -0.5f);
                            e->pos.y = y;
                            e->timer = 0;
                            if (e->f34 < EXT_LIT(float_1_80420f80, 1.0f)) {
                                e->state++;
                            }
                        }
                        break;
                    case 3:
                        e->timer++;
                        if (e->timer > 30) {
                            e->state++;
                        }
                        break;
                    case 4:
                        e->alpha -= 10;
                        if (e->alpha < 0) {
                            e->alpha = 0;
                            e->state++;
                            animPoseRelease(e->pose0);
                            e->pose0 = -1;
                        }
                        break;
                    case 5:
                        done++;
                        break;
                }
                switch (type) {
                    case 4:
                        if (e->state > 1) {
                            e->rot2 += (360.0f - e->rot2) / 10.0f;
                        }
                        break;
                    case 5:
                        if (e->state > 1) {
                            e->rot2 += (430.0f - e->rot2) / 10.0f;
                        }
                        break;
                }
                if (e->pose0 != -1) {
                    animPoseMain(e->pose0);
                }
                break;
            case 6:
                switch (e->state) {
                    case 0:
                        if (!animGroupBaseAsync("EFF_koopa\0\0", group, 0)) {
                            break;
                        }
                        if (e->pose0 == -1) {
                            e->pose0 = animPoseEntry("EFF_koopa\0\0", group);
                            animPoseSetAnim(e->pose0, "Z_1", 1);
                            psndSFXOn_3D(koopa1, &sndPos);
                        }
                        e->pos.x += e->vel.x;
                        e->pos.y += e->vel.y;
                        e->pos.z += e->vel.z;
                        e->timer++;
                        if (e->timer > 30) {
                            e->timer = 0;
                            e->state++;
                            effKemuri1N64Entry(4, sndPos.x + e->pos.x, sndPos.y + e->pos.y, sndPos.z + e->pos.z, EXT_LIT(float_0_80420f84, 0.0f));
                            evtEntry(evt_shake, 0, 0);
                        }
                        break;
                    case 1:
                        e->rot2 = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(EXT_LIT(float_30_80420fe0, 30.0f), EXT_LIT(float_neg27_80421024, -27.0f), 11, e->timer, 180);
                        if (e->rot2 < EXT_LIT(float_0_80420f84, 0.0f)) {
                            e->rot3 = e->rot2;
                            e->rot2 = EXT_LIT(float_0_80420f84, 0.0f);
                        }
                        e->timer++;
                        if (e->timer > 180) {
                            e->timer = 0;
                            e->state++;
                        }
                        if (e->timer == 100) {
                            psndSFXOn_3D(koopa1, &sndPos);
                        }
                        break;
                    case 2:
                        e->rot2 = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(EXT_LIT(float_neg27_80421024, -27.0f), EXT_LIT(float_80_80421028, 80.0f), 11, e->timer, 200);
                        if (e->rot2 < EXT_LIT(float_0_80420f84, 0.0f)) {
                            e->rot3 = e->rot2;
                            e->rot2 = EXT_LIT(float_0_80420f84, 0.0f);
                        }
                        e->timer++;
                        if (e->timer > 200) {
                            animPoseRelease(e->pose0);
                            e->pose0 = -1;
                            done++;
                        }
                        if (e->timer == 70) {
                            psndSFXOn_3D(koopa1, &sndPos);
                        }
                        break;
                }
                if (e->pose0 != -1) {
                    animPoseMain(e->pose0);
                }
                break;
            case 7:
                switch (e->state) {
                    case 0:
                        if (!animGroupBaseAsync("EFF_inseki\0", group, 0)) {
                            break;
                        }
                        psndSFXOn_3D(meteor1, &sndPos);
                        if (e->pose0 == -1) {
                            e->pose0 = animPoseEntry("EFF_inseki\0", group);
                            animPoseSetAnim(e->pose0, "Z_1", 1);
                        }
                        if (e->pose1 == -1) {
                            e->pose1 = animPoseEntry("EFF_inseki\0", group);
                            animPoseSetAnim(e->pose1, "Z_2", 1);
                        }
                    case 2:
                    case 4:
                    case 6: {
                        f32 tbl[4][3] = {
                            { 140.0f, 40.0f, -10.0f },
                            { 0.0f, 40.0f, -40.0f },
                            { -140.0f, 40.0f, -10.0f },
                            { -400.0f, 40.0f, -40.0f }
                        };
                        e->vel.x = tbl[e->state / 2][0];
                        e->vel.y = tbl[e->state / 2][1];
                        e->vel.z = tbl[e->state / 2][2];
                        e->f30 = EXT_LIT(float_0p4_80420f90, 0.4f);
                        e->timer = distABf(e->vel.x, e->vel.z, e->pos.x, e->pos.z) / EXT_LIT(float_5_80421030, 5.0f);
                        e->f34 = ((e->vel.y - e->pos.y) / e->timer) + (e->f30 * e->timer) / EXT_LIT(float_2_80420f88, 2.0f);
                        e->rotY = angleABf(e->pos.x, e->pos.z, e->vel.x, e->vel.z);
                        e->rot2 = EXT_LIT(float_0_80420f84, 0.0f);
                        e->state++;
                        break;
                    }
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        e->pos.x += EXT_LIT(float_5_80421030, 5.0f) * fall_sinf((EXT_LIT(float_6p2832_80420fa4, 6.2831855f) * e->rotY) / EXT_LIT(float_360_80420fa8, 360.0f));
                        e->pos.z += EXT_LIT(float_5_80421030, 5.0f) * -fall_cosf((EXT_LIT(float_6p2832_80420fa4, 6.2831855f) * e->rotY) / EXT_LIT(float_360_80420fa8, 360.0f));
                        if ((--e->timer) < 0) {
                            e->pos.x = e->vel.x;
                            e->pos.y = e->vel.y;
                            e->pos.z = e->vel.z;
                            e->state++;
                            if (e->state == 2) {
                                e->sfx = psndSFXOn_3D(meteor2, &sndPos);
                            }
                            if (e->state != 8) {
                                effKemuri1N64Entry(4, sndPos.x + e->pos.x, sndPos.y + e->pos.y - 40.0f, sndPos.z + e->pos.z, 0.0f);
                                evtEntry(evt_shake, 0, 0);
                            }
                        }
                        e->rot2 += (EXT_LIT(float_360_80420fa8, 360.0f) - e->rot2) / EXT_LIT(float_30_80420fe0, 30.0f);
                        break;
                    case 8:
                        psndSFXOff(e->sfx);
                        animPoseRelease(e->pose0);
                        animPoseRelease(e->pose1);
                        e->pose0 = -1;
                        e->pose1 = -1;
                        e->state++;
                        break;
                    case 9:
                        done++;
                        break;
                }
                if (e->pose0 != -1) {
                    animPoseMain(e->pose0);
                }
                if (e->pose1 != -1) {
                    animPoseMain(e->pose1);
                }
                break;
            case 8:
                switch (e->state) {
                    case 0:
                        if (!animGroupBaseAsync("EFF_light\0\0", group, 0)) {
                            break;
                        }
                        e->pose0 = animPoseEntry("EFF_light\0\0", group);
                        animPoseSetAnim(e->pose0, "Z_1", 1);
                        e->state++;
                        break;
                    case 1:
                    case 2:
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        if (e->pos.y < y) {
                            e->pos.y = y;
                            e->timer = 0;
                            e->state++;
                        }
                        if (1 == e->state && e->pos.y < top) {
                            effKemuri1N64Entry(4, sndPos.x + e->pos.x, sndPos.y + y, sndPos.z + e->pos.z, 0.0f);
                            evtEntry(evt_shake, 0, 0);
                            animPoseSetAnim(e->pose0, "A_1", 1);
                            e->state++;
                            psndSFXOn_3D(light1, &sndPos);
                        }
                        break;
                    case 3:
                        if (animPoseGetLoopTimes(e->pose0) < EXT_LIT(float_1_80420f80, 1.0f)) {
                            break;
                        }
                        e->timer++;
                        if (e->timer > e->arg8) {
                            e->state++;
                        }
                        break;
                    case 4:
                        e->alpha -= 10;
                        if (e->alpha < 0) {
                            e->alpha = 0;
                            e->state++;
                        }
                        break;
                    case 5:
                        animPoseRelease(e->pose0);
                        e->pose0 = -1;
                        e->state++;
                        break;
                    case 6:
                        done++;
                        break;
                }
                if (e->pose0 != -1) {
                    animPoseMain(e->pose0);
                }
                break;
        }
    }
    if (done >= effect->count - 1) {
        effDelete(effect);
        return;
    }
    switch (type) {
        case 3:
            dispEntry(CAMERA_3D, dispCalcZ(&sndPos), 2, (DispCallback)effFallDispWater, effect);
            break;
        case 4:
        case 5:
            dispEntry(CAMERA_3D, dispCalcZ(&sndPos), 0, (DispCallback)effFallDisp, effect);
            break;
        case 7:
            dispEntry(CAMERA_3D, dispCalcZ(&sndPos), 2, (DispCallback)effFallDispInseki, effect);
            break;
        case 6:
        default:
            dispEntry(CAMERA_3D, dispCalcZ(&sndPos), 2, (DispCallback)effFallDisp, effect);
            break;
    }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void effFallMain(EffectEntry* effect) {
	char _af_pad[108];
	asm volatile {
		lis r4, vec3_802fe418@ha
		opword 0x8343000C
		addi r31, r4, vec3_802fe418@l
		opword 0x7C731B78
		opword 0x809F000C
		opword 0x3AC00000
		opword 0x807F0010
		opword 0x801F0014
		stw r4, _af_pad+0(r1)
		opword 0xC01A0004
		opword 0x9061000C
		opword 0xC3FA0008
		opword 0xD0010008
		opword 0xC01A000C
		opword 0x90010010
		opword 0x80A10008
		opword 0xD3E1000C
		lwz r4, gp(r13)
		opword 0xD0010010
		opword 0x8061000C
		opword 0x80010010
		opword 0x90A10014
		opword 0x90610018
		opword 0x9001001C
		opword 0x80730000
		opword 0xC01A0014
		opword 0x80840014
		opword 0x5460077B
		opword 0xEF7F002A
		opword 0x831A0000
		opword 0x7C0400D0
		opword 0xC39A0010
		opword 0x7C002378
		opword 0xC05A0018
		opword 0x82FA0020
		opword 0x54140FFE
		opword 0x41820060
		opword 0x546007B8
		opword 0x3A000000
		opword 0x90130000
		lwz r15, 0xc(r19)
		opword 0x48000034
		opword 0x806F005C
		opword 0x2C03FFFF
		opword 0x41820008
		bl animPoseRelease
		opword 0x806F0060
		opword 0x2C03FFFF
		opword 0x41820008
		bl animPoseRelease
		opword 0x806F0064
		bl psndSFXOff
		opword 0x3A100001
		opword 0x39EF0068
		opword 0x80130008
		opword 0x7C100000
		opword 0x4180FFC8
		opword 0x7E639B78
		bl effDelete
		opword 0x4800155C
		lfs f1, float_6p2832_80420fa4(r2)
		opword 0x381F0070
		lfs f0, float_30_80420fe0(r2)
		opword 0x3BBF00BC
		opword 0x9001006C
		opword 0x381F00A0
		opword 0xEFC100B2
		opword 0x3BDF0088
		opword 0xEFA0F82A
		opword 0x90010068
		opword 0x39FF00D8
		opword 0x3B9F00F4
		opword 0x3B7F0114
		opword 0x3AA00000
		opword 0x3B200001
		opword 0x3B5A0068
		opword 0x48001440
		opword 0x28180008
		opword 0x41811430
		lis r3, jumptable_803AE04C@ha
		opword 0x5700103A
		addi r3, r3, jumptable_803AE04C@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x801A0038
		opword 0x2C000003
		opword 0x41820230
		opword 0x4080001C
		opword 0x2C000001
		opword 0x41820080
		opword 0x4080016C
		opword 0x2C000000
		opword 0x40800018
		opword 0x48000270
		opword 0x2C000005
		opword 0x41820264
		opword 0x40800264
		opword 0x4800022C
		opword 0x807A0024
		opword 0x2C030000
		opword 0x4182000C
		opword 0x3803FFFF
		opword 0x901A0024
		opword 0x801A0024
		opword 0x2C000000
		opword 0x40820240
		opword 0x807A0038
		opword 0x2C180001
		opword 0x38030001
		opword 0x901A0038
		opword 0x40820014
		opword 0x8061006C
		opword 0x38810014
		bl psndSFXOn_3D
		opword 0x4800021C
		opword 0x2C190001
		opword 0x40820214
		opword 0x7FC3F378
		opword 0x38810014
		bl psndSFXOn_3D
		opword 0x48000204
		opword 0x2C180000
		opword 0x40820048
		opword 0x2C190001
		opword 0x40810040
		opword 0x2C160000
		opword 0x40820038
		lwz r4, gp(r13)
		opword 0x3C60AAAB
		opword 0x3803AAAB
		opword 0x8064001C
		opword 0x7C001816
		opword 0x5400F0BE
		opword 0x1C000006
		opword 0x7C001851
		opword 0x40820014
		opword 0x7FC3F378
		opword 0x38810014
		bl psndSFXOn_3D
		opword 0x3AC00001
		opword 0xC03A0008
		opword 0xC01A0034
		lfs f3, float_0_80420f84(r2)
		opword 0xEC01002A
		opword 0xFC801890
		opword 0xD01A0008
		opword 0xC03A0034
		opword 0xC01A0030
		opword 0xEC010028
		opword 0xD01A0034
		opword 0xC03A0004
		opword 0xC05A000C
		bl distABf
		lfs f0, float_0p5_80420f7c(r2)
		opword 0xEC1C0032
		opword 0xFC010040
		opword 0x40800034
		opword 0xC01A0008
		opword 0xFC00D840
		opword 0x40800168
		opword 0xD37A0008
		lfs f0, float_neg0p3_80420fe4(r2)
		opword 0xC03A0034
		opword 0xEC010032
		opword 0xD01A0034
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000144
		opword 0xC01A0008
		opword 0xFC00F840
		opword 0x40800138
		opword 0xD3FA0008
		lfs f0, float_neg0p3_80420fe4(r2)
		opword 0xC03A0034
		opword 0xEC010032
		opword 0xD01A0034
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000114
		opword 0xC05A0008
		opword 0xC01A0034
		lfs f1, float_0_80420f84(r2)
		opword 0xEC02002A
		opword 0xFC400890
		opword 0xD01A0008
		opword 0xC07A0034
		opword 0xC01A0030
		opword 0xEC030028
		opword 0xD01A0034
		opword 0xC07A0004
		opword 0xC09A000C
		bl angleABf
		lfs f2, float_6p2832_80420fa4(r2)
		opword 0x2C190001
		lfs f0, float_360_80420fa8(r2)
		opword 0xEC220072
		fdivs f26, f1, f0
		opword 0x40820008
		opword 0xEF5E0024
		opword 0xFC20D090
		bl sin
		opword 0xFC600818
		lfs f2, float_0p5_80420f7c(r2)
		opword 0xC01A0004
		opword 0xFC20D090
		opword 0xEC0200FA
		opword 0xD01A0004
		bl cos
		opword 0xFC200818
		lfs f2, float_0p5_80420f7c(r2)
		opword 0xC01A000C
		opword 0xFC200850
		opword 0xEC02007A
		opword 0xD01A000C
		opword 0xC01A0008
		opword 0xFC00F840
		opword 0x4080007C
		opword 0xD3FA0008
		opword 0x38000000
		opword 0x901A0024
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000060
		opword 0x807A0024
		opword 0x38030001
		opword 0x901A0024
		opword 0x801A0024
		opword 0x2C00001E
		opword 0x40810048
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000038
		opword 0x807A003C
		opword 0x3803FFF6
		opword 0x901A003C
		opword 0x801A003C
		opword 0x2C000000
		opword 0x40800020
		opword 0x38000000
		opword 0x901A003C
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000008
		opword 0x3AB50001
		lwz r3, gp(r13)
		opword 0x8003001C
		opword 0x5400F7FF
		opword 0x41820010
		opword 0x807A0028
		opword 0x38030001
		opword 0x901A0028
		opword 0x801A0028
		opword 0x2C000003
		opword 0x4180000C
		opword 0x38000000
		opword 0x901A0028
		lwz r4, gp(r13)
		opword 0x3C604330
		opword 0x6F208000
		opword 0x90610050
		opword 0x8084001C
		opword 0x9001005C
		opword 0xC87F0060
		opword 0x90810054
		opword 0xC83F0068
		opword 0x90610058
		opword 0xC8410050
		opword 0xC8010058
		opword 0xEC621828
		lfs f2, float_0p5_80420f7c(r2)
		opword 0xEC000828
		opword 0xEC2300BA
		bl sin
		opword 0xFC200818
		lfs f0, float_35_80420fe8(r2)
		opword 0xEC000072
		opword 0xD01A0048
		opword 0x480010FC
		opword 0x801A0038
		opword 0x2C000002
		opword 0x41820110
		opword 0x40800014
		opword 0x2C000000
		opword 0x4182001C
		opword 0x4080006C
		opword 0x48000158
		opword 0x2C000004
		opword 0x4182014C
		opword 0x4080014C
		opword 0x48000114
		opword 0xC03A0008
		opword 0xC01A0034
		opword 0xEC01002A
		opword 0xD01A0008
		opword 0xC03A0034
		opword 0xC01A0030
		opword 0xEC010028
		opword 0xD01A0034
		opword 0xC01A0008
		opword 0xFC00F840
		opword 0x4080011C
		opword 0xD3FA0008
		opword 0x38000000
		opword 0x80610068
		opword 0x38810014
		opword 0x901A0024
		opword 0x80BA0038
		opword 0x38050001
		opword 0x901A0038
		bl psndSFXOn_3D
		opword 0x480000F4
		opword 0x807A0024
		opword 0x3C004330
		opword 0x90010058
		opword 0x6C608000
		opword 0xC85F0068
		opword 0x9001005C
		lfs f3, float_62p832_80420fec(r2)
		opword 0xC8210058
		lfs f0, float_60_80420ff0(r2)
		opword 0xEC211028
		opword 0xEC230072
		opword 0xEC210024
		bl sin
		opword 0x807A0024
		opword 0x3C004330
		opword 0x90010050
		opword 0xFC600818
		opword 0x6C608000
		opword 0xC83F0068
		opword 0x90010054
		lfs f2, float_60_80420ff0(r2)
		opword 0xC8010050
		opword 0xEC000828
		opword 0xEC020028
		opword 0xEC0000F2
		opword 0xEC001024
		opword 0xD01A0044
		opword 0x807A0024
		opword 0x38030001
		opword 0x901A0024
		opword 0x801A0024
		opword 0x2C00003C
		opword 0x40810070
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000060
		opword 0x807A0024
		opword 0x38030001
		opword 0x901A0024
		opword 0x801A0024
		opword 0x2C00001E
		opword 0x40810048
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000038
		opword 0x807A003C
		opword 0x3803FFF6
		opword 0x901A003C
		opword 0x801A003C
		opword 0x2C000000
		opword 0x40800020
		opword 0x38000000
		opword 0x901A003C
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000008
		opword 0x3AB50001
		opword 0x38600280
		opword 0x38800003
		bl smartAlloc
		opword 0x907A0040
		opword 0x38000010
		lfs f6, float_8p5333_80421000(r2)
		opword 0x38A00000
		opword 0x809A0040
		opword 0x3C604330
		opword 0xC8BF0068
		opword 0x80C40000
		lfs f4, float_128_80420ffc(r2)
		lfs f3, float_0_80420f84(r2)
		lfs f1, float_0p066667_80421004(r2)
		opword 0x7C0903A6
		opword 0x54A407FF
		opword 0x4182000C
		lfs f0, float_16_80420ff4(r2)
		opword 0x48000008
		lfs f0, float_neg16_80420ff8(r2)
		opword 0x54A00FFE
		opword 0x90610058
		opword 0x7C002A14
		opword 0x2C040000
		opword 0x7C040E70
		opword 0xD0060000
		opword 0x6C808000
		opword 0x9001005C
		opword 0xC8010058
		opword 0xEC002828
		opword 0xEC06203C
		opword 0xD0060004
		opword 0xD0660008
		opword 0x4182000C
		lfs f2, float_2_80420f88(r2)
		opword 0x48000008
		opword 0xFC401890
		opword 0x6C808000
		opword 0x38A50001
		opword 0x90010054
		opword 0x54A407FF
		opword 0x90610050
		opword 0xC8010050
		opword 0xD046000C
		opword 0xEC002828
		opword 0xEC010032
		opword 0xD0060010
		opword 0x4182000C
		lfs f0, float_16_80420ff4(r2)
		opword 0x48000008
		lfs f0, float_neg16_80420ff8(r2)
		opword 0x54A00FFE
		opword 0x90610058
		opword 0x7C002A14
		opword 0x2C040000
		opword 0x7C040E70
		opword 0xD0060014
		opword 0x6C808000
		opword 0x9001005C
		opword 0xC8010058
		opword 0xEC002828
		opword 0xEC06203C
		opword 0xD0060018
		opword 0xD066001C
		opword 0x4182000C
		lfs f2, float_2_80420f88(r2)
		opword 0x48000008
		opword 0xFC401890
		opword 0x6C808000
		opword 0x90610050
		opword 0x38A50001
		opword 0x90010054
		opword 0xC8010050
		opword 0xD0460020
		opword 0xEC002828
		opword 0xEC010032
		opword 0xD0060024
		opword 0x38C60028
		opword 0x4200FF04
		opword 0x807A0040
		opword 0x38000008
		lfs f2, float_600_80421008(r2)
		opword 0x3B200000
		opword 0x80630000
		opword 0x7C0903A6
		opword 0xC0030004
		opword 0x3B390004
		opword 0xC07A0044
		opword 0xEC200032
		opword 0xC0030000
		opword 0xEC211024
		opword 0xEC03007A
		opword 0xD0030000
		opword 0xC0030018
		opword 0xC07A0044
		opword 0xEC200032
		opword 0xC0030014
		opword 0xEC211024
		opword 0xEC03007A
		opword 0xD0030014
		opword 0xC003002C
		opword 0xC07A0044
		opword 0xEC200032
		opword 0xC0030028
		opword 0xEC211024
		opword 0xEC03007A
		opword 0xD0030028
		opword 0xC0030040
		opword 0xC07A0044
		opword 0xEC200032
		opword 0xC003003C
		opword 0xEC211024
		opword 0xEC03007A
		opword 0xD003003C
		opword 0x38630050
		opword 0x4200FF88
		opword 0x807A0040
		opword 0x38800280
		opword 0x80630000
		bl DCFlushRange
		opword 0x48000DA4
		opword 0x801A0038
		opword 0x2C000001
		opword 0x41820068
		opword 0x40800010
		opword 0x2C000000
		opword 0x40800014
		opword 0x4800012C
		opword 0x2C000003
		opword 0x40800124
		opword 0x480000B8
		opword 0xC03A0008
		opword 0xC01A0034
		opword 0xEC01002A
		opword 0xD01A0008
		opword 0xC03A0034
		opword 0xC01A0030
		opword 0xEC010028
		opword 0xD01A0034
		opword 0xC01A0008
		opword 0xFC00F840
		opword 0x408000F4
		opword 0xD3FA0008
		opword 0x38000000
		opword 0x901A0024
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x480000D8
		opword 0x3C606666
		opword 0x809A0024
		opword 0x38036667
		opword 0x7C002096
		opword 0x7C001670
		opword 0x54030FFE
		opword 0x7C001A14
		opword 0x1C00000A
		opword 0x7C002051
		opword 0x40820020
		opword 0xC0210014
		opword 0x38600004
		opword 0xC0410018
		opword 0x38800014
		opword 0xC061001C
		lfs f4, float_1_80420f80(r2)
		bl effWaterDamageN64Entry
		opword 0x807A0024
		opword 0x38030001
		opword 0x901A0024
		opword 0x801A0024
		opword 0x7C00B800
		opword 0x4081007C
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x4800006C
		opword 0x807A003C
		opword 0x3C004330
		opword 0x90010058
		opword 0x6C608000
		opword 0xC87F0068
		opword 0x9001005C
		lfs f2, float_0p9_8042100c(r2)
		opword 0xC8210058
		lfs f0, float_0p01_80421010(r2)
		opword 0xEC211828
		opword 0xEC2100B2
		opword 0xFC20081E
		opword 0xD8210050
		opword 0x80010054
		opword 0x901A003C
		opword 0xC03A002C
		opword 0xEC2100B2
		opword 0xD03A002C
		opword 0xC03A002C
		opword 0xFC010040
		opword 0x40800018
		opword 0x807A0064
		bl psndSFXOff
		opword 0x7E639B78
		bl effDelete
		opword 0x48000D40
		opword 0xC03A0054
		lfs f0, float_0p2_80421014(r2)
		opword 0xEC010028
		opword 0xD01A0054
		opword 0x48000C4C
		opword 0x801A0038
		opword 0x2C000003
		opword 0x41820270
		opword 0x4080001C
		opword 0x2C000001
		opword 0x418200E8
		opword 0x40800188
		opword 0x2C000000
		opword 0x40800018
		opword 0x480002C0
		opword 0x2C000005
		opword 0x418202B4
		opword 0x408002B4
		opword 0x4800026C
		opword 0x2C180005
		opword 0x4082004C
		opword 0x7E84A378
		opword 0x387F0130
		opword 0x38A00000
		bl animGroupBaseAsync
		opword 0x2C030000
		opword 0x41820290
		opword 0x801A005C
		opword 0x2C00FFFF
		opword 0x4082006C
		opword 0x7E84A378
		opword 0x387F0130
		bl animPoseEntry
		opword 0x907A005C
		la r4, str_80421018(r2)
		opword 0x38A00001
		opword 0x807A005C
		bl animPoseSetAnim
		opword 0x48000048
		opword 0x7E84A378
		opword 0x387F013C
		opword 0x38A00000
		bl animGroupBaseAsync
		opword 0x2C030000
		opword 0x41820248
		opword 0x801A005C
		opword 0x2C00FFFF
		opword 0x40820024
		opword 0x7E84A378
		opword 0x387F013C
		bl animPoseEntry
		opword 0x907A005C
		la r4, str_80421018(r2)
		opword 0x38A00001
		opword 0x807A005C
		bl animPoseSetAnim
		opword 0x807A0024
		opword 0x2C030000
		opword 0x4182000C
		opword 0x3803FFFF
		opword 0x901A0024
		opword 0x801A0024
		opword 0x2C000000
		opword 0x408201FC
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x480001EC
		opword 0xC03A0008
		opword 0xC01A0034
		lfs f3, float_0_80420f84(r2)
		opword 0xEC01002A
		opword 0xFC801890
		opword 0xD01A0008
		opword 0xC03A0034
		opword 0xC01A0030
		opword 0xEC010028
		opword 0xD01A0034
		opword 0xC03A0004
		opword 0xC05A000C
		bl distABf
		lfs f0, float_0p5_80420f7c(r2)
		opword 0xEC1C0032
		opword 0xFC010040
		opword 0x40800034
		opword 0xC01A0008
		opword 0xFC00D840
		opword 0x4080019C
		opword 0xD37A0008
		lfs f0, float_neg0p3_80420fe4(r2)
		opword 0xC03A0034
		opword 0xEC010032
		opword 0xD01A0034
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000178
		opword 0xC01A0008
		opword 0xFC00F840
		opword 0x4080016C
		opword 0xD3FA0008
		lfs f0, float_neg0p3_80420fe4(r2)
		opword 0xC03A0034
		opword 0xEC010032
		opword 0xD01A0034
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000148
		opword 0xC05A0008
		opword 0xC01A0034
		lfs f1, float_0_80420f84(r2)
		opword 0xEC02002A
		opword 0xFC400890
		opword 0xD01A0008
		opword 0xC07A0034
		opword 0xC01A0030
		opword 0xEC030028
		opword 0xD01A0034
		opword 0xC07A0004
		opword 0xC09A000C
		bl angleABf
		lfs f2, float_6p2832_80420fa4(r2)
		opword 0x2C190001
		lfs f0, float_360_80420fa8(r2)
		opword 0xEC220072
		opword 0xEF410024
		opword 0x40820008
		opword 0xEF5E0024
		opword 0xFC20D090
		bl sin
		opword 0xFC600818
		lfs f2, float_2_80420f88(r2)
		opword 0xC01A0004
		opword 0xFC20D090
		opword 0xEC0200FA
		opword 0xD01A0004
		bl cos
		opword 0xFC200818
		lfs f2, float_2_80420f88(r2)
		opword 0xC01A000C
		opword 0xFC200850
		opword 0xEC02007A
		opword 0xD01A000C
		opword 0xC01A0008
		opword 0xFC00F840
		opword 0x408000B0
		opword 0xD3FA0008
		opword 0x38000000
		lfs f1, float_neg0p5_8042101c(r2)
		opword 0xC05A0034
		lfs f0, float_1_80420f80(r2)
		opword 0xEC220072
		opword 0xD03A0034
		opword 0xD3FA0008
		opword 0x901A0024
		opword 0xC03A0034
		opword 0xFC010040
		opword 0x40800080
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000070
		opword 0x807A0024
		opword 0x38030001
		opword 0x901A0024
		opword 0x801A0024
		opword 0x2C00001E
		opword 0x40810058
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000048
		opword 0x807A003C
		opword 0x3803FFF6
		opword 0x901A003C
		opword 0x801A003C
		opword 0x2C000000
		opword 0x40800030
		opword 0x38000000
		opword 0x901A003C
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x807A005C
		bl animPoseRelease
		opword 0x3800FFFF
		opword 0x901A005C
		opword 0x48000008
		opword 0x3AB50001
		opword 0x2C180005
		opword 0x41820040
		opword 0x40800064
		opword 0x2C180004
		opword 0x40800008
		opword 0x48000058
		opword 0x801A0038
		opword 0x2C000001
		opword 0x4081004C
		opword 0xC05A0048
		lfs f1, float_360_80420fa8(r2)
		lfs f0, float_10_80420fb0(r2)
		opword 0xEC211028
		opword 0xEC010024
		opword 0xEC02002A
		opword 0xD01A0048
		opword 0x4800002C
		opword 0x801A0038
		opword 0x2C000001
		opword 0x40810020
		opword 0xC05A0048
		lfs f1, float_430_80421020(r2)
		lfs f0, float_10_80420fb0(r2)
		opword 0xEC211028
		opword 0xEC010024
		opword 0xEC02002A
		opword 0xD01A0048
		opword 0x807A005C
		opword 0x2C03FFFF
		opword 0x418208F0
		bl animPoseMain
		opword 0x480008E8
		opword 0x801A0038
		opword 0x2C000001
		opword 0x41820110
		opword 0x40800010
		opword 0x2C000000
		opword 0x40800014
		opword 0x480001F4
		opword 0x2C000003
		opword 0x408001EC
		opword 0x48000170
		opword 0x7E84A378
		opword 0x387F0148
		opword 0x38A00000
		bl animGroupBaseAsync
		opword 0x2C030000
		opword 0x418201D0
		opword 0x801A005C
		opword 0x2C00FFFF
		opword 0x40820030
		opword 0x7E84A378
		opword 0x387F0148
		bl animPoseEntry
		opword 0x907A005C
		la r4, str_80421018(r2)
		opword 0x38A00001
		opword 0x807A005C
		bl animPoseSetAnim
		opword 0x7FA3EB78
		opword 0x38810014
		bl psndSFXOn_3D
		opword 0xC03A0004
		opword 0xC01A0050
		opword 0xEC01002A
		opword 0xD01A0004
		opword 0xC03A0008
		opword 0xC01A0054
		opword 0xEC01002A
		opword 0xD01A0008
		opword 0xC03A000C
		opword 0xC01A0058
		opword 0xEC01002A
		opword 0xD01A000C
		opword 0x807A0024
		opword 0x38030001
		opword 0x901A0024
		opword 0x801A0024
		opword 0x2C00001E
		opword 0x40810150
		opword 0x38000000
		lfs f4, float_0_80420f84(r2)
		opword 0x901A0024
		opword 0x38600004
		opword 0x809A0038
		opword 0x38040001
		opword 0x901A0038
		opword 0xC0210014
		opword 0xC01A0004
		opword 0xC0A10018
		opword 0xC05A0008
		opword 0xEC21002A
		opword 0xC061001C
		opword 0xC01A000C
		opword 0xEC45102A
		opword 0xEC63002A
		bl effKemuri1N64Entry
		la r3, evt_shake(r13)
		opword 0x38800000
		opword 0x38A00000
		bl evtEntry
		opword 0x480000F8
		lfs f1, float_30_80420fe0(r2)
		opword 0x3860000B
		lfs f2, float_neg27_80421024(r2)
		opword 0x38A000B4
		opword 0x809A0024
		bl intplGetValue
		opword 0xD03A0048
		lfs f0, float_0_80420f84(r2)
		opword 0xC03A0048
		opword 0xFC010040
		opword 0x4080000C
		opword 0xD03A004C
		opword 0xD01A0048
		opword 0x807A0024
		opword 0x38030001
		opword 0x901A0024
		opword 0x801A0024
		opword 0x2C0000B4
		opword 0x40810018
		opword 0x38000000
		opword 0x901A0024
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x801A0024
		opword 0x2C000064
		opword 0x4082008C
		opword 0x7FA3EB78
		opword 0x38810014
		bl psndSFXOn_3D
		opword 0x4800007C
		lfs f1, float_neg27_80421024(r2)
		opword 0x3860000B
		lfs f2, float_80_80421028(r2)
		opword 0x38A000C8
		opword 0x809A0024
		bl intplGetValue
		opword 0xD03A0048
		lfs f0, float_0_80420f84(r2)
		opword 0xC03A0048
		opword 0xFC010040
		opword 0x4080000C
		opword 0xD03A004C
		opword 0xD01A0048
		opword 0x807A0024
		opword 0x38030001
		opword 0x901A0024
		opword 0x801A0024
		opword 0x2C0000C8
		opword 0x40810018
		opword 0x807A005C
		bl animPoseRelease
		opword 0x3800FFFF
		opword 0x3AB50001
		opword 0x901A005C
		opword 0x801A0024
		opword 0x2C000046
		opword 0x40820010
		opword 0x7FA3EB78
		opword 0x38810014
		bl psndSFXOn_3D
		opword 0x807A005C
		opword 0x2C03FFFF
		opword 0x418206D0
		bl animPoseMain
		opword 0x480006C8
		opword 0x801A0038
		opword 0x28000009
		opword 0x418104B0
		lis r3, jumptable_803AE024@ha
		opword 0x5400103A
		addi r3, r3, jumptable_803AE024@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x7E84A378
		opword 0x387F0154
		opword 0x38A00000
		bl animGroupBaseAsync
		opword 0x2C030000
		opword 0x41820480
		opword 0x7DE37B78
		opword 0x38810014
		bl psndSFXOn_3D
		opword 0x801A005C
		opword 0x2C00FFFF
		opword 0x40820024
		opword 0x7E84A378
		opword 0x387F0154
		bl animPoseEntry
		opword 0x907A005C
		la r4, str_80421018(r2)
		opword 0x38A00001
		opword 0x807A005C
		bl animPoseSetAnim
		opword 0x801A0060
		opword 0x2C00FFFF
		opword 0x40820024
		opword 0x7E84A378
		opword 0x387F0154
		bl animPoseEntry
		opword 0x907A0060
		la r4, str_8042102C(r2)
		opword 0x38A00001
		opword 0x807A0060
		bl animPoseSetAnim
		opword 0x809A0038
		opword 0x38610020
		opword 0x821F0018
		opword 0x54800FFE
		opword 0x823F001C
		opword 0x7C002214
		opword 0x825F0020
		opword 0x7C000E70
		opword 0x819F0024
		opword 0x817F0028
		opword 0x1C00000C
		opword 0x815F002C
		opword 0x813F0030
		opword 0x811F0034
		opword 0x80FF0038
		opword 0x80DF003C
		opword 0x80BF0040
		opword 0x809F0044
		opword 0x92010020
		lfs f0, float_0p4_80420f90(r2)
		opword 0x92210024
		opword 0x92410028
		opword 0x9181002C
		opword 0x91610030
		opword 0x91410034
		opword 0x91210038
		opword 0x9101003C
		opword 0x90E10040
		opword 0x90C10044
		opword 0x90A10048
		opword 0x9081004C
		opword 0x7C23042E
		opword 0xD03A0050
		opword 0x809A0038
		opword 0x54800FFE
		opword 0x7C002214
		opword 0x7C000E70
		opword 0x1C80000C
		opword 0x38040004
		opword 0x7C23042E
		opword 0xD03A0054
		opword 0x809A0038
		opword 0x54800FFE
		opword 0x7C002214
		opword 0x7C000E70
		opword 0x1C80000C
		opword 0x38040008
		opword 0x7C23042E
		opword 0xD03A0058
		opword 0xD01A0030
		opword 0xC03A0050
		opword 0xC05A0058
		opword 0xC07A0004
		opword 0xC09A000C
		bl distABf
		lfs f0, float_5_80421030(r2)
		opword 0x3C004330
		opword 0x90010060
		opword 0xEC010024
		opword 0xC89F0068
		opword 0x90010050
		lfs f2, float_0p5_80420f7c(r2)
		opword 0xFC00001E
		opword 0xD8010058
		opword 0x8001005C
		opword 0x901A0024
		opword 0x801A0024
		opword 0xC03A0054
		opword 0x6C008000
		opword 0xC01A0008
		opword 0x90010064
		opword 0xEC210028
		opword 0xC0BA0030
		opword 0xC8010060
		opword 0x90010054
		opword 0xEC002028
		opword 0xC8610050
		opword 0xEC010024
		opword 0xEC232028
		opword 0xEC250072
		opword 0xEC0100BA
		opword 0xD01A0034
		opword 0xC03A0004
		opword 0xC05A000C
		opword 0xC07A0050
		opword 0xC09A0058
		bl angleABf
		opword 0xD03A0018
		lfs f0, float_0_80420f84(r2)
		opword 0xD01A0048
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x480002A4
		opword 0xC03A0008
		opword 0xC01A0034
		lfs f3, float_6p2832_80420fa4(r2)
		opword 0xEC41002A
		lfs f0, float_360_80420fa8(r2)
		lfs f1, float_3p1416_8042103c(r2)
		lfs f7, float_0p00761_80421034(r2)
		opword 0xD05A0008
		lfs f6, float_0p16605_80421038(r2)
		opword 0xC09A0034
		opword 0xC05A0030
		lfs f5, float_1_80420f80(r2)
		opword 0xEC441028
		opword 0xD05A0034
		opword 0xC05A0018
		opword 0xEC4300B2
		opword 0xEC420024
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820044
		lfs f1, float_1p5708_80421040(r2)
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC0200B2
		opword 0xECE73038
		opword 0xECE7283A
		opword 0xECE700B2
		opword 0x48000068
		opword 0xEC020828
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECE73038
		opword 0xECE7283A
		opword 0xECE700B2
		opword 0x4800004C
		lfs f0, float_4p7124_80421044(r2)
		opword 0xFC020040
		opword 0x40800020
		opword 0xEC420828
		opword 0xEC0200B2
		opword 0xECE73038
		opword 0xECE7283A
		opword 0xECE700B2
		opword 0xFCE03850
		opword 0x48000024
		opword 0xEC020028
		lfs f1, float_1p5708_80421040(r2)
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECE73038
		opword 0xECE7283A
		opword 0xECE700B2
		opword 0xFCE03850
		lfs f1, float_5_80421030(r2)
		opword 0xC01A0004
		lfs f3, float_6p2832_80420fa4(r2)
		opword 0xEC4101FA
		lfs f0, float_360_80420fa8(r2)
		lfs f1, float_3p1416_8042103c(r2)
		lfs f6, float_0p03705_80421048(r2)
		opword 0xD05A0004
		lfs f5, float_0p4967_8042104c(r2)
		opword 0xC05A0018
		lfs f4, float_1_80420f80(r2)
		opword 0xEC4300B2
		opword 0xEC420024
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820040
		lfs f1, float_1p5708_80421040(r2)
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC0200B2
		opword 0xECC62838
		opword 0xECC6203A
		opword 0x4800005C
		opword 0xEC020828
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECC62838
		opword 0xECC6203A
		opword 0xFCC03050
		opword 0x48000040
		lfs f0, float_4p7124_80421044(r2)
		opword 0xFC020040
		opword 0x4080001C
		opword 0xEC420828
		opword 0xEC0200B2
		opword 0xECC62838
		opword 0xECC6203A
		opword 0xFCC03050
		opword 0x4800001C
		opword 0xEC020028
		lfs f1, float_1p5708_80421040(r2)
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECC62838
		opword 0xECC6203A
		opword 0xFC203050
		lfs f2, float_5_80421030(r2)
		opword 0xC01A000C
		opword 0xEC02007A
		opword 0xD01A000C
		opword 0x807A0024
		opword 0x3403FFFF
		opword 0x901A0024
		opword 0x40800098
		opword 0xC01A0050
		opword 0xD01A0004
		opword 0xC01A0054
		opword 0xD01A0008
		opword 0xC01A0058
		opword 0xD01A000C
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x801A0038
		opword 0x2C000002
		opword 0x40820014
		opword 0x7F83E378
		opword 0x38810014
		bl psndSFXOn_3D
		opword 0x907A0064
		opword 0x801A0038
		opword 0x2C000008
		opword 0x4182004C
		opword 0xC0210018
		opword 0x38600004
		opword 0xC01A0008
		opword 0xC0C10014
		opword 0xC0BA0004
		opword 0xEC81002A
		lfs f2, float_40_80421050(r2)
		opword 0xC061001C
		opword 0xEC26282A
		opword 0xC01A000C
		opword 0xEC441028
		lfs f4, float_0_80420f84(r2)
		opword 0xEC63002A
		bl effKemuri1N64Entry
		la r3, evt_shake(r13)
		opword 0x38800000
		opword 0x38A00000
		bl evtEntry
		opword 0xC05A0048
		lfs f1, float_360_80420fa8(r2)
		lfs f0, float_30_80420fe0(r2)
		opword 0xEC211028
		opword 0xEC010024
		opword 0xEC02002A
		opword 0xD01A0048
		opword 0x4800003C
		opword 0x807A0064
		bl psndSFXOff
		opword 0x807A005C
		bl animPoseRelease
		opword 0x807A0060
		bl animPoseRelease
		opword 0x3800FFFF
		opword 0x901A005C
		opword 0x901A0060
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000008
		opword 0x3AB50001
		opword 0x807A005C
		opword 0x2C03FFFF
		opword 0x41820008
		bl animPoseMain
		opword 0x807A0060
		opword 0x2C03FFFF
		opword 0x418201F4
		bl animPoseMain
		opword 0x480001EC
		opword 0x801A0038
		opword 0x2C000004
		opword 0x4182017C
		opword 0x4080001C
		opword 0x2C000000
		opword 0x41820024
		opword 0x418001C0
		opword 0x2C000003
		opword 0x40800124
		opword 0x4800005C
		opword 0x2C000006
		opword 0x418201A8
		opword 0x408001A8
		opword 0x48000180
		opword 0x7E84A378
		opword 0x387F0160
		opword 0x38A00000
		bl animGroupBaseAsync
		opword 0x2C030000
		opword 0x4182018C
		opword 0x7E84A378
		opword 0x387F0160
		bl animPoseEntry
		opword 0x907A005C
		la r4, str_80421018(r2)
		opword 0x38A00001
		opword 0x807A005C
		bl animPoseSetAnim
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x4800015C
		opword 0xC03A0008
		opword 0xC01A0034
		opword 0xEC01002A
		opword 0xD01A0008
		opword 0xC03A0034
		opword 0xC01A0030
		opword 0xEC010028
		opword 0xD01A0034
		opword 0xC01A0008
		opword 0xFC00F840
		opword 0x4080001C
		opword 0xD3FA0008
		opword 0x38000000
		opword 0x901A0024
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x801A0038
		opword 0x2C000001
		opword 0x4082010C
		opword 0xC01A0008
		opword 0xFC00E840
		opword 0x40800100
		opword 0xC0010018
		opword 0x38600004
		opword 0xC0810014
		opword 0xC03A0004
		opword 0xEC40F82A
		opword 0xC061001C
		opword 0xC01A000C
		opword 0xEC24082A
		lfs f4, float_0_80420f84(r2)
		opword 0xEC63002A
		bl effKemuri1N64Entry
		la r3, evt_shake(r13)
		opword 0x38800000
		opword 0x38A00000
		bl evtEntry
		opword 0x807A005C
		la r4, str_80421054(r2)
		opword 0x38A00001
		bl animPoseSetAnim
		opword 0x80BA0038
		opword 0x7F63DB78
		opword 0x38810014
		opword 0x38050001
		opword 0x901A0038
		bl psndSFXOn_3D
		opword 0x48000098
		opword 0x807A005C
		bl animPoseGetLoopTimes
		lfs f0, float_1_80420f80(r2)
		opword 0xFC010040
		opword 0x41800084
		opword 0x807A0024
		opword 0x38030001
		opword 0x901A0024
		opword 0x807A0024
		opword 0x801A0020
		opword 0x7C030000
		opword 0x40810068
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000058
		opword 0x807A003C
		opword 0x3803FFF6
		opword 0x901A003C
		opword 0x801A003C
		opword 0x2C000000
		opword 0x40800040
		opword 0x38000000
		opword 0x901A003C
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000028
		opword 0x807A005C
		bl animPoseRelease
		opword 0x3800FFFF
		opword 0x901A005C
		opword 0x807A0038
		opword 0x38030001
		opword 0x901A0038
		opword 0x48000008
		opword 0x3AB50001
		opword 0x807A005C
		opword 0x2C03FFFF
		opword 0x41820008
		bl animPoseMain
		opword 0x3B390001
		opword 0x3B5A0068
		opword 0x80730008
		opword 0x7C191800
		opword 0x4180EBBC
		opword 0x3803FFFF
		opword 0x7C150000
		opword 0x41800010
		opword 0x7E639B78
		bl effDelete
		opword 0x480000B8
		opword 0x2C180006
		opword 0x41820090
		opword 0x40800014
		opword 0x2C180003
		opword 0x41820018
		opword 0x40800038
		opword 0x4800007C
		opword 0x2C180008
		opword 0x40800074
		opword 0x4800004C
		opword 0x38610014
		bl dispCalcZ
		lis r3, effFallDispWater@ha
		opword 0x7E669B78
		addi r5, r3, effFallDispWater@l
		opword 0x38800002
		opword 0x38600004
		bl dispEntry
		opword 0x4800006C
		opword 0x38610014
		bl dispCalcZ
		lis r3, effFallDisp@ha
		opword 0x7E669B78
		addi r5, r3, effFallDisp@l
		opword 0x38800000
		opword 0x38600004
		bl dispEntry
		opword 0x48000048
		opword 0x38610014
		bl dispCalcZ
		lis r3, effFallDispInseki@ha
		opword 0x7E669B78
		addi r5, r3, effFallDispInseki@l
		opword 0x38800002
		opword 0x38600004
		bl dispEntry
		opword 0x48000024
		opword 0x38610014
		bl dispCalcZ
		lis r3, effFallDisp@ha
		opword 0x7E669B78
		addi r5, r3, effFallDisp@l
		opword 0x38800002
		opword 0x38600004
		bl dispEntry
	}
}
#pragma pop
#endif

#pragma opt_propagation reset
__declspec(section ".data") static void* jumptable_803AE000[] = {
    (char*)effFallDisp + 0x214,
    (char*)effFallDisp + 0x214,
    (char*)effFallDisp + 0x484,
    (char*)effFallDisp + 0xB04,
    (char*)effFallDisp + 0x608,
    (char*)effFallDisp + 0x608,
    (char*)effFallDisp + 0x7D4,
    (char*)effFallDisp + 0xB04,
    (char*)effFallDisp + 0xA38,
};
__declspec(section ".data") void* jumptable_803AE024[] = {
    (char*)effFallMain + 0xF08,
    (char*)effFallMain + 0x10FC,
    (char*)effFallMain + 0xF84,
    (char*)effFallMain + 0x10FC,
    (char*)effFallMain + 0xF84,
    (char*)effFallMain + 0x10FC,
    (char*)effFallMain + 0xF84,
    (char*)effFallMain + 0x10FC,
    (char*)effFallMain + 0x1364,
    (char*)effFallMain + 0x1398,
};
__declspec(section ".data") void* jumptable_803AE04C[] = {
    (char*)effFallMain + 0x194,
    (char*)effFallMain + 0x194,
    (char*)effFallMain + 0x4B0,
    (char*)effFallMain + 0x808,
    (char*)effFallMain + 0x960,
    (char*)effFallMain + 0x960,
    (char*)effFallMain + 0xCC4,
    (char*)effFallMain + 0xEE4,
    (char*)effFallMain + 0x13C0,
};
__declspec(section ".data") void* jumptable_803AE070[] = {
    (char*)effFallEntry + 0x278,
    (char*)effFallEntry + 0x278,
    (char*)effFallEntry + 0x2D0,
    (char*)effFallEntry + 0x2FC,
    (char*)effFallEntry + 0x370,
    (char*)effFallEntry + 0x370,
    (char*)effFallEntry + 0x39C,
    (char*)effFallEntry + 0x3F8,
    (char*)effFallEntry + 0x41C,
};
#ifdef NONMATCHING
void effFallDisp(CameraId cameraId, EffectEntry* effect) {
    Mtx trans;
    Mtx scl;
    Mtx rot;
    Mtx mtx;
    GXTexObj tex;
    Vec axis;
    CameraEntry* cam;
    EffFallElem* e;
    s32 i;
    s32 type;
    f32 angle;
    s32 j;
    f32 hw, hh, s;

    e = effect->userdata;
    cam = camGetPtr(cameraId);
    type = e->type;
    angle = e->rotY;
    PSMTXTrans(trans, e->pos.x, e->pos.y, e->pos.z);
    PSMTXRotRad(rot, 'y', -camGetPtr(cameraId)->viewYaw * EXT_LIT(float_deg2rad_80420f70, 0.017453292f));
    PSMTXConcat(trans, rot, mtx);
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
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    switch (type) {
        case 0:
        case 1:
            effGetTexObj(0x32, &tex);
            GXLoadTexObj(&tex, GX_TEXMAP0);
            break;
        case 2:
            effGetTexObj(0x33, &tex);
            GXLoadTexObj(&tex, GX_TEXMAP0);
            break;
    }
    for (i = 1, e++; i < effect->count; i++, e++) {
        switch (type) {
            case 0:
            case 1:
                hw = EXT_LIT(float_64_80420f74, 64.0f);
                hh = EXT_LIT(float_42p667_80420fb8, 42.666668f);
                hw /= EXT_LIT(float_2_80420f88, 2.0f);
                hh /= EXT_LIT(float_2_80420f88, 2.0f);
                PSMTXTrans(trans, e->pos.x, e->pos.y, e->pos.z);
                PSMTXRotRad(rot, 'y', e->rotY * EXT_LIT(float_deg2rad_80420f70, 0.017453292f));
                PSMTXConcat(trans, rot, trans);
                PSMTXTrans(rot, EXT_LIT(float_0_80420f84, 0.0f), hh / EXT_LIT(float_2_80420f88, 2.0f) * e->scale, EXT_LIT(float_0_80420f84, 0.0f));
                PSMTXConcat(trans, rot, trans);
                PSMTXRotRad(rot, 'z', e->rot2 * EXT_LIT(float_deg2rad_80420f70, 0.017453292f));
                PSMTXConcat(trans, rot, trans);
                PSMTXTrans(rot, EXT_LIT(float_0_80420f84, 0.0f), -hh / EXT_LIT(float_2_80420f88, 2.0f) * e->scale, EXT_LIT(float_0_80420f84, 0.0f));
                PSMTXConcat(trans, rot, trans);
                PSMTXScale(scl, e->scale, e->scale, e->scale);
                PSMTXConcat(trans, scl, trans);
                PSMTXConcat(mtx, trans, trans);
                PSMTXConcat(cam->view, trans, trans);
                GXLoadPosMtxImm(trans, 0);
                GXSetCurrentMtx(0);
                GXSetChanMatColor(GX_COLOR0A0, (GXColor){ 255, 255, 255, e->alpha });
                PSMTXScale(scl, EXT_LIT(float_1_80420f80, 1.0f), EXT_LIT(float_0p33333_80420fbc, 0.33333334f), EXT_LIT(float_1_80420f80, 1.0f));
                PSMTXTrans(trans, EXT_LIT(float_0_80420f84, 0.0f), (f32)e->scroll, EXT_LIT(float_0_80420f84, 0.0f));
                PSMTXConcat(scl, trans, trans);
                GXLoadTexMtxImm(trans, GX_TEXMTX0, GX_MTX2x4);
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition3f32(-hw / EXT_LIT(float_2_80420f88, 2.0f), hh, EXT_LIT(float_0_80420f84, 0.0f));
                GXTexCoord2f32(EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_0_80420f84, 0.0f));
                GXPosition3f32(hw / EXT_LIT(float_2_80420f88, 2.0f), hh, EXT_LIT(float_0_80420f84, 0.0f));
                GXTexCoord2f32(EXT_LIT(float_1_80420f80, 1.0f), EXT_LIT(float_0_80420f84, 0.0f));
                GXPosition3f32(hw / EXT_LIT(float_2_80420f88, 2.0f), EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_0_80420f84, 0.0f));
                GXTexCoord2f32(EXT_LIT(float_1_80420f80, 1.0f), EXT_LIT(float_1_80420f80, 1.0f));
                GXPosition3f32(-hw / EXT_LIT(float_2_80420f88, 2.0f), EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_0_80420f84, 0.0f));
                GXTexCoord2f32(EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_1_80420f80, 1.0f));
                break;
            case 2:
                PSMTXTrans(trans, e->pos.x, e->pos.y, e->pos.z);
                PSMTXScale(scl, e->scale, e->scale, e->scale);
                PSMTXConcat(trans, scl, trans);
                PSMTXConcat(mtx, trans, trans);
                PSMTXConcat(cam->view, trans, trans);
                GXLoadPosMtxImm(trans, 0);
                GXSetCurrentMtx(0);
                GXSetChanMatColor(GX_COLOR0A0, (GXColor){ 255, 255, 255, e->alpha });
                PSMTXIdentity(trans);
                GXLoadTexMtxImm(trans, GX_TEXMTX0, GX_MTX2x4);
                for (j = 0; j < 30; j += 2) {
                    EffFallVtx* v = &(*e->vtx)[j];
                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    GXPosition3f32(v[0].x, v[0].y, v[0].z);
                    GXTexCoord2f32(v[0].u, v[0].v);
                    GXPosition3f32(v[2].x, v[2].y, v[2].z);
                    GXTexCoord2f32(v[2].u, v[2].v);
                    GXPosition3f32(v[3].x, v[3].y, v[3].z);
                    GXTexCoord2f32(v[3].u, v[3].v);
                    GXPosition3f32(v[1].x, v[1].y, v[1].z);
                    GXTexCoord2f32(v[1].u, v[1].v);
                }
                break;
            case 4:
            case 5: {
                Vec v = { 0.0f, 0.0f, 0.0f };
                v.x = (f32)cos(EXT_LIT(float_6p2832_80420fa4, 6.2831855f) * angle / EXT_LIT(float_360_80420fa8, 360.0f));
                v.z = (f32)sin(EXT_LIT(float_6p2832_80420fa4, 6.2831855f) * angle / EXT_LIT(float_360_80420fa8, 360.0f));
                axis = v;
                PSMTXTrans(trans, e->pos.x, e->pos.y, e->pos.z);
                PSMTXScale(scl, e->scale, e->scale, e->scale);
                PSMTXConcat(trans, scl, trans);
                PSMTXTrans(scl, EXT_LIT(float_0_80420f84, 0.0f), (f32)(type == 4 ? 8 : 16), EXT_LIT(float_0_80420f84, 0.0f));
                PSMTXConcat(trans, scl, trans);
                PSMTXRotAxisRad(rot, &axis, -e->rot2 * EXT_LIT(float_deg2rad_80420f70, 0.017453292f));
                PSMTXConcat(trans, rot, trans);
                PSMTXTrans(scl, EXT_LIT(float_0_80420f84, 0.0f), (f32)-(type == 4 ? 8 : 16), EXT_LIT(float_0_80420f84, 0.0f));
                PSMTXConcat(trans, scl, trans);
                PSMTXConcat(mtx, trans, trans);
                if (e->pose0 != -1) {
                    animPoseDrawMtx(e->pose0, trans, 1, 0.0f, 10.0f);
                    animPoseDrawMtx(e->pose0, trans, 2, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
                    animPoseDrawMtx(e->pose0, trans, 3, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
                }
                break;
            }
            case 6:
                if (e->pose0 == -1) {
                    break;
                }
                PSMTXTrans(trans, e->pos.x, e->pos.y, e->pos.z);
                if (angle < EXT_LIT(float_180_80420fc0, 180.0f)) {
                    PSMTXScale(scl, e->scale, e->scale, e->scale);
                } else {
                    PSMTXScale(scl, -e->scale, e->scale, e->scale);
                }
                PSMTXConcat(trans, scl, trans);
                if (e->rot2) {
                    PSMTXRotRad(rot, 'z', -e->rot2 * 0.017453292f);
                    PSMTXConcat(trans, rot, trans);
                } else {
                    PSMTXTrans(scl, -200.0f, 0.0f, 0.0f);
                    PSMTXConcat(trans, scl, trans);
                    PSMTXRotRad(rot, 'z', -e->rot3 * EXT_LIT(float_deg2rad_80420f70, 0.017453292f));
                    PSMTXConcat(trans, rot, trans);
                    PSMTXTrans(scl, EXT_LIT(float_200_80420fc8, 200.0f), EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_0_80420f84, 0.0f));
                    PSMTXConcat(trans, scl, trans);
                }
                PSMTXConcat(mtx, trans, trans);
                PSMTXTrans(scl, EXT_LIT(float_neg82p655_80420fcc, -82.655f), EXT_LIT(float_88p8_80420fd0, 88.8f), EXT_LIT(float_0_80420f84, 0.0f));
                PSMTXConcat(trans, scl, scl);
                PSMTXScale(rot, EXT_LIT(float_1p03_80420fd4, 1.03f), EXT_LIT(float_1p03_80420fd4, 1.03f), EXT_LIT(float_1p03_80420fd4, 1.03f));
                PSMTXConcat(scl, rot, rot);
                PSMTXTrans(scl, EXT_LIT(float_82p655_80420fd8, 82.655f), EXT_LIT(float_neg88p8_80420fdc, -88.8f), EXT_LIT(float_0_80420f84, 0.0f));
                PSMTXConcat(rot, scl, scl);
                animPoseSetMaterialFlagOn(e->pose0, 0x40);
                animPoseSetMaterialEvtColor(e->pose0, (GXColor){ 0, 0, 0, 255 });
                animPoseDrawMtx(e->pose0, scl, 1, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
                animPoseDrawMtx(e->pose0, scl, 2, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
                animPoseDrawMtx(e->pose0, scl, 3, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
                animPoseSetMaterialFlagOn(e->pose0, 0x40);
                animPoseSetMaterialEvtColor(e->pose0, (GXColor){ 255, 255, 255, 255 });
                animPoseDrawMtx(e->pose0, trans, 1, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
                animPoseDrawMtx(e->pose0, trans, 2, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
                animPoseDrawMtx(e->pose0, trans, 3, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
                break;
            case 8:
                if (e->pose0 == -1) {
                    break;
                }
                PSMTXTrans(trans, e->pos.x, e->pos.y, e->pos.z);
                PSMTXScale(scl, e->scale, e->scale, e->scale);
                PSMTXConcat(trans, scl, trans);
                PSMTXConcat(mtx, trans, trans);
                animPoseSetMaterialFlagOn(e->pose0, 0x40);
                animPoseSetMaterialEvtColor(e->pose0, (GXColor){ 255, 255, 255, e->alpha });
                animPoseDrawMtx(e->pose0, trans, 1, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
                animPoseDrawMtx(e->pose0, trans, 2, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
                animPoseDrawMtx(e->pose0, trans, 3, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
                break;
        }
    }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void effFallDisp(CameraId cameraId, EffectEntry* effect) {
	char _af_pad[300];
	asm volatile {
		opword 0x7C9B2378
		opword 0x7C771B78
		opword 0x83C4000C
		bl camGetPtr
		opword 0x839E0000
		opword 0x7C7F1B78
		opword 0xC3DE0018
		la r3, _af_pad+232
		opword 0xC03E0004
		opword 0xC05E0008
		opword 0xC07E000C
		bl PSMTXTrans
		opword 0x7EE3BB78
		bl camGetPtr
		opword 0xC0230114
		opword 0x38610090
		lfs f0, float_deg2rad_80420f70(r2)
		opword 0x38800079
		opword 0xFC200850
		opword 0xEC200072
		bl PSMTXRotRad
		opword 0x386100F0
		opword 0x38810090
		opword 0x38A10060
		bl PSMTXConcat
		opword 0x38600001
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
		opword 0x38C00004
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
		opword 0x38800000
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
		opword 0x38600001
		bl GXSetNumTexGens
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0001E
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x2C1C0002
		opword 0x41820030
		opword 0x40800044
		opword 0x2C1C0000
		opword 0x40800008
		opword 0x48000038
		opword 0x38810040
		opword 0x38600032
		bl effGetTexObj
		opword 0x38610040
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x4800001C
		opword 0x38810040
		opword 0x38600033
		bl effGetTexObj
		opword 0x38610040
		opword 0x38800000
		bl GXLoadTexObj
		lfs f0, float_6p2832_80420fa4(r2)
		opword 0x3BA00001
		opword 0x3BDE0068
		opword 0xEFE007B2
		opword 0x4800091C
		opword 0x281C0008
		opword 0x4181090C
		lis r3, jumptable_803AE000@ha
		opword 0x5780103A
		addi r3, r3, jumptable_803AE000@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		lfs f29, float_64_80420f74(r2)
		opword 0x386100F0
		lfs f0, float_0p5_80420f7c(r2)
		lfs f28, float_42p667_80420fb8(r2)
		opword 0xEFBD0032
		opword 0xC03E0004
		opword 0xEF9C0032
		opword 0xC05E0008
		opword 0xC07E000C
		bl PSMTXTrans
		lfs f1, float_deg2rad_80420f70(r2)
		opword 0x38610090
		opword 0xC01E0018
		opword 0x38800079
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x386100F0
		opword 0x38810090
		opword 0x7C651B78
		bl PSMTXConcat
		lfs f0, float_0p5_80420f7c(r2)
		opword 0x38610090
		lfs f1, float_0_80420f84(r2)
		opword 0xEC5C0032
		opword 0xC01E002C
		opword 0xFC600890
		opword 0xEC420032
		bl PSMTXTrans
		opword 0x386100F0
		opword 0x38810090
		opword 0x7C651B78
		bl PSMTXConcat
		lfs f1, float_deg2rad_80420f70(r2)
		opword 0x38610090
		opword 0xC01E0048
		opword 0x3880007A
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x386100F0
		opword 0x38810090
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0xFC60E050
		lfs f2, float_0p5_80420f7c(r2)
		lfs f1, float_0_80420f84(r2)
		opword 0x38610090
		opword 0xC01E002C
		opword 0xEC4300B2
		opword 0xFC600890
		opword 0xEC420032
		bl PSMTXTrans
		opword 0x386100F0
		opword 0x38810090
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0xC03E002C
		opword 0x386100C0
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x386100F0
		opword 0x388100C0
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x388100F0
		opword 0x38610060
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x388100F0
		opword 0x387F011C
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x386100F0
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		lwz r5, dat_80420f48(r2)
		opword 0x38810024
		opword 0x801E003C
		opword 0x38600004
		opword 0x90A10020
		opword 0x98010023
		opword 0x80010020
		opword 0x90010024
		bl GXSetChanMatColor
		lfs f1, float_1_80420f80(r2)
		opword 0x386100C0
		lfs f2, float_0p33333_80420fbc(r2)
		opword 0xFC600890
		bl PSMTXScale
		opword 0x807E0028
		opword 0x3C004330
		lis r4, double_to_int_802fe480@ha
		lfs f1, float_0_80420f84(r2)
		opword 0x6C638000
		opword 0x90010120
		lfd f2, double_to_int_802fe480@l(r4)
		opword 0xFC600890
		opword 0x90610124
		opword 0x386100F0
		opword 0xC8010120
		opword 0xEC401028
		bl PSMTXTrans
		opword 0x388100F0
		opword 0x386100C0
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x386100F0
		opword 0x3880001E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x38600080
		opword 0x38800000
		opword 0x38A00004
		bl GXBegin
		opword 0xFC20E850
		lfs f0, float_0p5_80420f7c(r2)
		opword 0x3C60CC01
		opword 0xEC5D0032
		opword 0xEC210032
		opword 0xD0238000
		opword 0xD3838000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0038000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0038000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0038000
		opword 0xD0438000
		opword 0xD3838000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0038000
		lfs f0, float_1_80420f80(r2)
		opword 0xD0038000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0038000
		opword 0xD0438000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0038000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0038000
		lfs f0, float_1_80420f80(r2)
		opword 0xD0038000
		lfs f0, float_1_80420f80(r2)
		opword 0xD0038000
		opword 0xD0238000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0038000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0038000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0038000
		lfs f0, float_1_80420f80(r2)
		opword 0xD0038000
		opword 0x48000684
		opword 0xC03E0004
		opword 0x386100F0
		opword 0xC05E0008
		opword 0xC07E000C
		bl PSMTXTrans
		opword 0xC03E002C
		opword 0x386100C0
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x386100F0
		opword 0x388100C0
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x388100F0
		opword 0x38610060
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x388100F0
		opword 0x387F011C
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x386100F0
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		lwz r5, dat_80420f4c(r2)
		opword 0x3881001C
		opword 0x801E003C
		opword 0x38600004
		opword 0x90A10018
		opword 0x9801001B
		opword 0x80010018
		opword 0x9001001C
		bl GXSetChanMatColor
		opword 0x386100F0
		bl PSMTXIdentity
		opword 0x386100F0
		opword 0x3880001E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x3B000000
		opword 0x3B200000
		opword 0x3F40CC01
		opword 0x80DE0040
		opword 0x38600080
		opword 0x38800000
		opword 0x38A00004
		opword 0x80060000
		add r23, r0, r25
		bl GXBegin
		opword 0xC0570008
		opword 0x3B180002
		opword 0xC0370004
		opword 0x2C18001E
		opword 0xC0170000
		opword 0x3B390028
		opword 0xD01A8000
		opword 0xD03A8000
		opword 0xD05A8000
		opword 0xC0370010
		opword 0xC017000C
		opword 0xD01A8000
		opword 0xD03A8000
		opword 0xC0570030
		opword 0xC037002C
		opword 0xC0170028
		opword 0xD01A8000
		opword 0xD03A8000
		opword 0xD05A8000
		opword 0xC0370038
		opword 0xC0170034
		opword 0xD01A8000
		opword 0xD03A8000
		opword 0xC0570044
		opword 0xC0370040
		opword 0xC017003C
		opword 0xD01A8000
		opword 0xD03A8000
		opword 0xD05A8000
		opword 0xC037004C
		opword 0xC0170048
		opword 0xD01A8000
		opword 0xD03A8000
		opword 0xC057001C
		opword 0xC0370018
		opword 0xC0170014
		opword 0xD01A8000
		opword 0xD03A8000
		opword 0xD05A8000
		opword 0xC0370024
		opword 0xC0170020
		opword 0xD01A8000
		opword 0xD03A8000
		opword 0x4180FF38
		opword 0x48000500
		lfs f0, float_360_80420fa8(r2)
		lis r3, vec3_802fe460@ha
		addi r5, r3, vec3_802fe460@l
		opword 0xEF9F0024
		opword 0x80850000
		opword 0x80650004
		opword 0x80050008
		opword 0x90810028
		opword 0x9061002C
		opword 0xFC20E090
		opword 0x90010030
		bl cos
		opword 0xFC000818
		opword 0xFC20E090
		opword 0xD0010028
		bl sin
		opword 0xFC000818
		opword 0x80010028
		opword 0x8081002C
		opword 0x386100F0
		opword 0x90010034
		opword 0xD0010030
		opword 0x80010030
		opword 0x90810038
		opword 0x9001003C
		opword 0xC03E0004
		opword 0xC05E0008
		opword 0xC07E000C
		bl PSMTXTrans
		opword 0xC03E002C
		opword 0x386100C0
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x386100F0
		opword 0x388100C0
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x2C1C0004
		lfs f1, float_0_80420f84(r2)
		opword 0x386100C0
		opword 0x38000010
		opword 0x40820008
		opword 0x38000008
		opword 0x6C048000
		opword 0x3C004330
		opword 0x90810124
		lis r5, double_to_int_802fe480@ha
		lfd f2, double_to_int_802fe480@l(r5)
		opword 0x90010120
		lfs f3, float_0_80420f84(r2)
		opword 0xC8010120
		opword 0xEC401028
		bl PSMTXTrans
		opword 0x386100F0
		opword 0x388100C0
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0xC01E0048
		opword 0x38610090
		lfs f1, float_deg2rad_80420f70(r2)
		opword 0x38810034
		opword 0xFC000050
		opword 0xEC210032
		bl PSMTXRotAxisRad
		opword 0x386100F0
		opword 0x38810090
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x2C1C0004
		lfs f1, float_0_80420f84(r2)
		opword 0x386100C0
		opword 0x38000010
		opword 0x40820008
		opword 0x38000008
		opword 0x7C8000D0
		opword 0x3C004330
		opword 0x6C848000
		lis r5, double_to_int_802fe480@ha
		opword 0x9081012C
		lfd f2, double_to_int_802fe480@l(r5)
		opword 0x90010128
		lfs f3, float_0_80420f84(r2)
		opword 0xC8010128
		opword 0xEC401028
		bl PSMTXTrans
		opword 0x386100F0
		opword 0x388100C0
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x388100F0
		opword 0x38610060
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x807E005C
		opword 0x2C03FFFF
		opword 0x4182037C
		lfs f1, float_0_80420f84(r2)
		opword 0x388100F0
		lfs f2, float_10_80420fb0(r2)
		opword 0x38A00001
		bl animPoseDrawMtx
		opword 0x807E005C
		opword 0x388100F0
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00002
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x807E005C
		opword 0x388100F0
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00003
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x48000334
		opword 0x801E005C
		opword 0x2C00FFFF
		opword 0x41820328
		opword 0xC03E0004
		opword 0x386100F0
		opword 0xC05E0008
		opword 0xC07E000C
		bl PSMTXTrans
		lfs f0, float_180_80420fc0(r2)
		opword 0xFC1E0040
		opword 0x4080001C
		opword 0xC03E002C
		opword 0x386100C0
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x48000018
		opword 0xC05E002C
		opword 0x386100C0
		opword 0xFC601090
		opword 0xFC201050
		bl PSMTXScale
		opword 0x386100F0
		opword 0x388100C0
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0xC01E0048
		lfs f2, float_0_80420f84(r2)
		opword 0xFC001000
		opword 0x41820030
		opword 0xFC000050
		lfs f1, float_deg2rad_80420f70(r2)
		opword 0x38610090
		opword 0x3880007A
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x386100F0
		opword 0x38810090
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x48000074
		opword 0xFC601090
		lfs f1, float_neg200_80420fc4(r2)
		opword 0x386100C0
		bl PSMTXTrans
		opword 0x386100F0
		opword 0x388100C0
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0xC01E004C
		opword 0x38610090
		lfs f1, float_deg2rad_80420f70(r2)
		opword 0x3880007A
		opword 0xFC000050
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x386100F0
		opword 0x38810090
		opword 0x7C651B78
		bl PSMTXConcat
		lfs f2, float_0_80420f84(r2)
		opword 0x386100C0
		lfs f1, float_200_80420fc8(r2)
		opword 0xFC601090
		bl PSMTXTrans
		opword 0x386100F0
		opword 0x388100C0
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x388100F0
		opword 0x38610060
		opword 0x7C852378
		bl PSMTXConcat
		lfs f1, float_neg82p655_80420fcc(r2)
		opword 0x386100C0
		lfs f2, float_88p8_80420fd0(r2)
		lfs f3, float_0_80420f84(r2)
		bl PSMTXTrans
		opword 0x388100C0
		opword 0x386100F0
		opword 0x7C852378
		bl PSMTXConcat
		lfs f1, float_1p03_80420fd4(r2)
		opword 0x38610090
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x38810090
		opword 0x386100C0
		opword 0x7C852378
		bl PSMTXConcat
		lfs f1, float_82p655_80420fd8(r2)
		opword 0x386100C0
		lfs f2, float_neg88p8_80420fdc(r2)
		lfs f3, float_0_80420f84(r2)
		bl PSMTXTrans
		opword 0x388100C0
		opword 0x38610090
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x807E005C
		opword 0x38800040
		bl animPoseSetMaterialFlagOn
		lwz r0, dat_80420f50(r2)
		opword 0x38810014
		opword 0x90010014
		opword 0x807E005C
		bl animPoseSetMaterialEvtColor
		opword 0x807E005C
		opword 0x388100C0
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00001
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x807E005C
		opword 0x388100C0
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00002
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x807E005C
		opword 0x388100C0
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00003
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x807E005C
		opword 0x38800040
		bl animPoseSetMaterialFlagOn
		lwz r0, dat_80420f54(r2)
		opword 0x38810010
		opword 0x90010010
		opword 0x807E005C
		bl animPoseSetMaterialEvtColor
		opword 0x807E005C
		opword 0x388100F0
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00001
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x807E005C
		opword 0x388100F0
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00002
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x807E005C
		opword 0x388100F0
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00003
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x480000D0
		opword 0x801E005C
		opword 0x2C00FFFF
		opword 0x418200C4
		opword 0xC03E0004
		opword 0x386100F0
		opword 0xC05E0008
		opword 0xC07E000C
		bl PSMTXTrans
		opword 0xC03E002C
		opword 0x386100C0
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x386100F0
		opword 0x388100C0
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x388100F0
		opword 0x38610060
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x807E005C
		opword 0x38800040
		bl animPoseSetMaterialFlagOn
		lwz r3, dat_80420f58(r2)
		opword 0x3881000C
		opword 0x801E003C
		opword 0x90610008
		opword 0x9801000B
		opword 0x80010008
		opword 0x9001000C
		opword 0x807E005C
		bl animPoseSetMaterialEvtColor
		opword 0x807E005C
		opword 0x388100F0
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00001
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x807E005C
		opword 0x388100F0
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00002
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x807E005C
		opword 0x388100F0
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00003
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x3BBD0001
		opword 0x3BDE0068
		opword 0x801B0008
		opword 0x7C1D0000
		opword 0x4180F6E0
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
void effFallDispInseki(CameraId cameraId, EffectEntry* effect) {
    Mtx trans;
    Mtx scl;
    Mtx rot;
    Mtx mtx;
    Vec axis;
    EffFallWork* w;
    s32 i;

    w = effect->userdata;
    camGetPtr(cameraId);
    PSMTXTrans(trans, w->position.x, w->position.y, w->position.z);
    PSMTXRotRad(rot, 'y', -camGetPtr(cameraId)->viewYaw * EXT_LIT(float_deg2rad_80420f70, 0.017453292f));
    PSMTXConcat(trans, rot, mtx);
    if (w->pose0 != -1 && w->pose1 != -1) {
        Vec v = { 0.0f, 0.0f, 0.0f };
        v.x = (f32)cos(EXT_LIT(float_6p2832_80420fa4, 6.2831855f) * w->angle / EXT_LIT(float_360_80420fa8, 360.0f));
        v.z = (f32)sin(EXT_LIT(float_6p2832_80420fa4, 6.2831855f) * w->angle / EXT_LIT(float_360_80420fa8, 360.0f));
        axis = v;
        for (i = 0; i < 2; i++) {
            if (i == 0) {
                PSMTXTrans(trans, w->pos2.x, w->pos2.y, w->pos2.z);
                PSMTXRotAxisRad(rot, &axis, -w->rotation * EXT_LIT(float_deg2rad_80420f70, 0.017453292f));
                PSMTXScale(scl, EXT_LIT(float_2p05_80420fac, 2.05f) * w->scale, EXT_LIT(float_2p05_80420fac, 2.05f) * w->scale, EXT_LIT(float_2p05_80420fac, 2.05f) * w->scale);
                PSMTXConcat(mtx, trans, trans);
                PSMTXConcat(trans, rot, trans);
                PSMTXConcat(trans, scl, trans);
                animPoseSetMaterialFlagOn(w->pose0, 0x40);
                animPoseSetMaterialEvtColor(w->pose0, (GXColor){ 0, 0, 0, 255 });
            } else {
                PSMTXTrans(trans, w->pos2.x, w->pos2.y, w->pos2.z);
                PSMTXRotAxisRad(rot, &axis, -w->rotation * EXT_LIT(float_deg2rad_80420f70, 0.017453292f));
                PSMTXScale(scl, EXT_LIT(float_2_80420f88, 2.0f) * w->scale, EXT_LIT(float_2_80420f88, 2.0f) * w->scale, EXT_LIT(float_2_80420f88, 2.0f) * w->scale);
                PSMTXConcat(mtx, trans, trans);
                PSMTXConcat(trans, rot, trans);
                PSMTXConcat(trans, scl, trans);
                animPoseSetMaterialFlagOn(w->pose0, 0x40);
                animPoseSetMaterialEvtColor(w->pose0, (GXColor){ 255, 255, 255, 255 });
            }
            animPoseDrawMtx(w->pose0, trans, 1, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
            animPoseDrawMtx(w->pose0, trans, 2, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
            animPoseDrawMtx(w->pose0, trans, 3, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
        }
        PSMTXTrans(trans, w->pos2.x, w->pos2.y, w->pos2.z);
        PSMTXScale(scl, EXT_LIT(float_2p1_80420fb4, 2.1f) * w->scale, EXT_LIT(float_2p1_80420fb4, 2.1f) * w->scale, EXT_LIT(float_2p1_80420fb4, 2.1f) * w->scale);
        PSMTXConcat(mtx, trans, trans);
        PSMTXConcat(trans, scl, trans);
        animPoseDrawMtx(w->pose1, trans, 1, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
        animPoseDrawMtx(w->pose1, trans, 2, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
        animPoseDrawMtx(w->pose1, trans, 3, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_10_80420fb0, 10.0f));
    }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void effFallDispInseki(CameraId cameraId, EffectEntry* effect) {
	asm volatile {
		opword 0x9421FF10
		opword 0x7C0802A6
		opword 0x900100F4
		opword 0x93E100EC
		opword 0x93C100E8
		opword 0x7C7E1B78
		opword 0x83E4000C
		bl camGetPtr
		opword 0xC03F0004
		opword 0x386100B8
		opword 0xC05F0008
		opword 0xC07F000C
		bl PSMTXTrans
		opword 0x7FC3F378
		bl camGetPtr
		opword 0xC0230114
		opword 0x38610058
		lfs f0, float_deg2rad_80420f70(r2)
		opword 0x38800079
		opword 0xFC200850
		opword 0xEC200072
		bl PSMTXRotRad
		opword 0x386100B8
		opword 0x38810058
		opword 0x38A10028
		bl PSMTXConcat
		opword 0x801F00C4
		opword 0x2C00FFFF
		opword 0x418202BC
		opword 0x801F00C8
		opword 0x2C00FFFF
		opword 0x418202B0
		lfs f1, float_6p2832_80420fa4(r2)
		lis r3, vec3_802fe46c@ha
		opword 0xC01F0080
		addi r5, r3, vec3_802fe46c@l
		opword 0x80850000
		opword 0xEC210032
		lfs f0, float_360_80420fa8(r2)
		opword 0x80650004
		opword 0x80050008
		opword 0xEC210024
		opword 0x90810010
		opword 0x90610014
		opword 0x90010018
		bl cos
		lfs f2, float_6p2832_80420fa4(r2)
		opword 0xFC600818
		opword 0xC03F0080
		lfs f0, float_360_80420fa8(r2)
		opword 0xEC220072
		opword 0xD0610010
		opword 0xEC210024
		bl sin
		opword 0xFC000818
		opword 0x80010010
		opword 0x80610014
		opword 0x3BC00000
		opword 0x9001001C
		opword 0xD0010018
		opword 0x80010018
		opword 0x90610020
		opword 0x90010024
		opword 0x2C1E0000
		opword 0x408200A4
		opword 0xC03F006C
		opword 0x386100B8
		opword 0xC05F0070
		opword 0xC07F0074
		bl PSMTXTrans
		opword 0xC01F00B0
		opword 0x38610058
		lfs f1, float_deg2rad_80420f70(r2)
		opword 0x3881001C
		opword 0xFC000050
		opword 0xEC210032
		bl PSMTXRotAxisRad
		lfs f1, float_2p05_80420fac(r2)
		opword 0x38610088
		opword 0xC01F0094
		opword 0xEC210032
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x388100B8
		opword 0x38610028
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x386100B8
		opword 0x38810058
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386100B8
		opword 0x38810088
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x807F00C4
		opword 0x38800040
		bl animPoseSetMaterialFlagOn
		lwz r0, dat_80420f5c(r2)
		opword 0x3881000C
		opword 0x9001000C
		opword 0x807F00C4
		bl animPoseSetMaterialEvtColor
		opword 0x480000A0
		opword 0xC03F006C
		opword 0x386100B8
		opword 0xC05F0070
		opword 0xC07F0074
		bl PSMTXTrans
		opword 0xC01F00B0
		opword 0x38610058
		lfs f1, float_deg2rad_80420f70(r2)
		opword 0x3881001C
		opword 0xFC000050
		opword 0xEC210032
		bl PSMTXRotAxisRad
		lfs f1, float_2_80420f88(r2)
		opword 0x38610088
		opword 0xC01F0094
		opword 0xEC210032
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x388100B8
		opword 0x38610028
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x386100B8
		opword 0x38810058
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386100B8
		opword 0x38810088
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x807F00C4
		opword 0x38800040
		bl animPoseSetMaterialFlagOn
		lwz r0, dat_80420f60(r2)
		opword 0x38810008
		opword 0x90010008
		opword 0x807F00C4
		bl animPoseSetMaterialEvtColor
		opword 0x807F00C4
		opword 0x388100B8
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00001
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x807F00C4
		opword 0x388100B8
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00002
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x807F00C4
		opword 0x388100B8
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00003
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x3BDE0001
		opword 0x2C1E0002
		opword 0x4180FE6C
		opword 0xC03F006C
		opword 0x386100B8
		opword 0xC05F0070
		opword 0xC07F0074
		bl PSMTXTrans
		lfs f1, float_2p1_80420fb4(r2)
		opword 0x38610088
		opword 0xC01F0094
		opword 0xEC210032
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x388100B8
		opword 0x38610028
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x386100B8
		opword 0x38810088
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x807F00C8
		opword 0x388100B8
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00001
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x807F00C8
		opword 0x388100B8
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00002
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x807F00C8
		opword 0x388100B8
		lfs f1, float_0_80420f84(r2)
		opword 0x38A00003
		lfs f2, float_10_80420fb0(r2)
		bl animPoseDrawMtx
		opword 0x800100F4
		opword 0x83E100EC
		opword 0x83C100E8
		opword 0x7C0803A6
		opword 0x382100F0
	}
}
#pragma pop
#endif

#pragma opt_propagation off
#ifdef NONMATCHING
static const GXColor white255 = { 255, 255, 255, 255 };
#endif
#ifdef NONMATCHING
void effFallDispWater(CameraId cameraId, EffectEntry *effect) {
    Mtx trans;
    Mtx scl;
    Mtx rot;
    Mtx mtx;
    GXTexObj tex;
    GXColor color;
    CameraEntry *cam;
    EffFallWork *w;
    f32 hw;
    f32 hh;
    f32 s;
    w = effect->userdata;
    cam = camGetPtr(cameraId);
    PSMTXTrans(trans, w->position.x, w->position.y, w->position.z);
    PSMTXRotRad(rot, 'y', (-camGetPtr(cameraId)->viewYaw) * EXT_LIT(float_deg2rad_80420f70, 0.017453292f));
    PSMTXConcat(trans, rot, mtx);
    PSMTXConcat(cam->view, mtx, mtx);
    GXSetNumTevStages(2);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_C0, GX_CC_CPREV, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_A0, GX_CA_APREV, GX_CA_ZERO);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetCullMode(GX_CULL_BACK);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    effGetTexObj(0x35, &tex);
    GXLoadTexObj(&tex, GX_TEXMAP0);
    hw = EXT_LIT(float_64_80420f74, 64.0f);
    hh = EXT_LIT(float_704_80420f78, 704.0f);
    hw /= EXT_LIT(float_2_80420f88, 2.0f);
    hh /= EXT_LIT(float_2_80420f88, 2.0f);
    PSMTXTrans(trans, w->pos3.x, w->pos3.y, w->pos3.z);
    PSMTXScale(scl, EXT_LIT(float_1_80420f80, 1.0f), hh / ((f32) GXGetTexObjHeight(&tex)), EXT_LIT(float_1_80420f80, 1.0f));
    PSMTXConcat(trans, scl, trans);
    GXLoadTexMtxImm(trans, GX_TEXMTX0, GX_MTX2x4);
    PSMTXTrans(trans, w->pos2.x, w->pos2.y, w->pos2.z);
    PSMTXScale(scl, w->scale, EXT_LIT(float_1_80420f80, 1.0f), EXT_LIT(float_1_80420f80, 1.0f));
    PSMTXConcat(trans, scl, trans);
    PSMTXConcat(mtx, trans, trans);
    GXLoadPosMtxImm(trans, 0);
    GXSetTevColor(GX_TEVREG0, white255);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32((-hw) / EXT_LIT(float_2_80420f88, 2.0f), hh, EXT_LIT(float_0_80420f84, 0.0f));
    GXColor4u8(255, 255, 255, 255);
    GXTexCoord2f32(EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_0_80420f84, 0.0f));
    GXPosition3f32(hw / EXT_LIT(float_2_80420f88, 2.0f), hh, EXT_LIT(float_0_80420f84, 0.0f));
    GXColor4u8(255, 255, 255, 255);
    GXTexCoord2f32(EXT_LIT(float_2_80420f88, 2.0f), EXT_LIT(float_0_80420f84, 0.0f));
    GXPosition3f32(hw / EXT_LIT(float_2_80420f88, 2.0f), EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_0_80420f84, 0.0f));
    GXColor4u8(255, 255, 255, 0);
    GXTexCoord2f32(EXT_LIT(float_2_80420f88, 2.0f), EXT_LIT(float_1_80420f80, 1.0f));
    GXPosition3f32((-hw) / EXT_LIT(float_2_80420f88, 2.0f), EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_0_80420f84, 0.0f));
    GXColor4u8(255, 255, 255, 0);
    GXTexCoord2f32(EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_1_80420f80, 1.0f));
    {
        EffFallWork *w2 = effect->userdata;
        if (w2->state > 0) {
            PSMTXTrans(trans, w2->pos2.x, w2->pos2.y, w2->pos2.z);
            PSMTXScale(scl, EXT_LIT(float_0p56_80420f8c, 0.56f), EXT_LIT(float_0p4_80420f90, 0.4f), EXT_LIT(float_0p8_80420f94, 0.8f));
            PSMTXConcat(mtx, trans, trans);
            PSMTXConcat(trans, scl, trans);
            GXLoadPosMtxImm(trans, 0);
            PSMTXTrans(trans, w2->pos3.y / 8.0f, EXT_LIT(float_0_80420f84, 0.0f), EXT_LIT(float_0_80420f84, 0.0f));
            GXLoadTexMtxImm(trans, GX_TEXMTX0, GX_MTX2x4);
            GXSetTevColor(GX_TEVREG0, (GXColor){255, 255, 255, w2->alpha});
            effGetTexObj(0x37, &tex);
            GXLoadTexObj(&tex, GX_TEXMAP0);
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 8);
            GXSetArray(GX_VA_POS, shibuki_vertex_tbl, 6);
            GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 6);
            GXSetArray(GX_VA_NRM, shibuki_normal_tbl, 3);
            GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
            GXSetArray(GX_VA_CLR0, shibuki_color0_tbl, 4);
            GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 14);
            GXSetArray(GX_VA_TEX0, shibuki_texcoord0_tbl, 4);
            GXCallDisplayList(shibuki_dl_1_0, 0x20);
            GXCallDisplayList(shibuki_dl_1_1, 0x20);
            GXCallDisplayList(shibuki_dl_1_2, 0x20);
            GXCallDisplayList(shibuki_dl_1_3, 0x20);
            PSMTXTrans(trans, w2->pos2.x, w2->pos2.y, w2->pos2.z);
            s = w2->scale;
            s = s * EXT_LIT(float_0p8_80420f94, 0.8f);
            PSMTXScale(scl, EXT_LIT(float_0p7_80420f9c, 0.7f) * s, EXT_LIT(float_0p5_80420f7c, 0.5f) * s, s);
            PSMTXConcat(mtx, trans, trans);
            PSMTXConcat(trans, scl, trans);
            GXLoadPosMtxImm(trans, 0);
            PSMTXTrans(trans, EXT_LIT(float_0_80420f84, 0.0f), (-w2->pos3.y) / 4.0f, EXT_LIT(float_0_80420f84, 0.0f));
            GXLoadTexMtxImm(trans, GX_TEXMTX0, GX_MTX2x4);
            {
                static const GXColor white255b = {255, 255, 255, 255};
                GXSetTevColor(GX_TEVREG0, white255b);
            }
            effGetTexObj(0x36, &tex);
            GXLoadTexObj(&tex, GX_TEXMAP0);
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 8);
            GXSetArray(GX_VA_POS, shibuki_vertex_tbl, 6);
            GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 6);
            GXSetArray(GX_VA_NRM, shibuki_normal_tbl, 3);
            GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
            GXSetArray(GX_VA_CLR0, shibuki_color0_tbl, 4);
            GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 14);
            GXSetArray(GX_VA_TEX0, shibuki_texcoord0_tbl, 4);
            GXCallDisplayList(shibuki_dl_0_0, 0x40);
            GXCallDisplayList(shibuki_dl_0_1, 0x40);
            GXCallDisplayList(shibuki_dl_0_2, 0x40);
            GXCallDisplayList(shibuki_dl_0_3, 0x40);
        }
    }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void effFallDispWater(CameraId cameraId, EffectEntry *effect) {
	char _af_pad[252];
	asm volatile {
		opword 0x7C9C2378
		lis r4, lbl_803ADD20@ha
		opword 0x83BC000C
		mr r27, r3
		addi r30, r4, lbl_803ADD20@l
		bl camGetPtr
		opword 0xC03D0004
		opword 0x7C7F1B78
		opword 0xC05D0008
		la r3, _af_pad+192
		opword 0xC07D000C
		bl PSMTXTrans
		opword 0x7F63DB78
		bl camGetPtr
		opword 0xC0230114
		opword 0x38610068
		lfs f0, float_deg2rad_80420f70(r2)
		opword 0x38800079
		opword 0xFC200850
		opword 0xEC200072
		bl PSMTXRotRad
		opword 0x386100C8
		opword 0x38810068
		opword 0x38A10038
		bl PSMTXConcat
		opword 0x38810038
		opword 0x387F011C
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38600002
		bl GXSetNumTevStages
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00004
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
		opword 0x38800000
		bl GXSetTevOp
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
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600001
		opword 0x3880000F
		opword 0x38A00002
		opword 0x38C00000
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800007
		opword 0x38A00001
		opword 0x38C00000
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600001
		bl GXSetNumTexGens
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0001E
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x38600001
		bl GXSetNumChans
		opword 0x38600004
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00001
		opword 0x38E00000
		opword 0x39000000
		opword 0x39200002
		bl GXSetChanCtrl
		opword 0x38600002
		bl GXSetCullMode
		bl GXClearVtxDesc
		opword 0x38600009
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x3860000B
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
		opword 0x3880000B
		opword 0x38A00001
		opword 0x38C00005
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x38600000
		opword 0x3880000D
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x38810018
		opword 0x38600035
		bl effGetTexObj
		opword 0x38610018
		opword 0x38800000
		bl GXLoadTexObj
		lfs f31, float_64_80420f74(r2)
		opword 0x386100C8
		lfs f0, float_0p5_80420f7c(r2)
		lfs f30, float_704_80420f78(r2)
		opword 0xEFFF0032
		opword 0xC03D00B8
		opword 0xEFDE0032
		opword 0xC05D00BC
		opword 0xC07D00C0
		bl PSMTXTrans
		opword 0x38610018
		bl GXGetTexObjHeight
		opword 0x5464043E
		opword 0x3C004330
		lis r3, double_to_int_mask_802fe478@ha
		opword 0x908100FC
		addi r4, r3, double_to_int_mask_802fe478@l
		lfs f1, float_1_80420f80(r2)
		opword 0x900100F8
		opword 0x38610098
		opword 0xC8440000
		opword 0xFC600890
		opword 0xC80100F8
		opword 0xEC001028
		opword 0xEC5E0024
		bl PSMTXScale
		opword 0x386100C8
		opword 0x38810098
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386100C8
		opword 0x3880001E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0xC03D006C
		opword 0x386100C8
		opword 0xC05D0070
		opword 0xC07D0074
		bl PSMTXTrans
		lfs f2, float_1_80420f80(r2)
		opword 0x38610098
		opword 0xC03D0094
		opword 0xFC601090
		bl PSMTXScale
		opword 0x386100C8
		opword 0x38810098
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x388100C8
		opword 0x38610038
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x386100C8
		opword 0x38800000
		bl GXLoadPosMtxImm
		lwz r0, dat_80420f64(r2)
		opword 0x38810014
		opword 0x38600001
		opword 0x90010014
		bl GXSetTevColor
		opword 0x38600080
		opword 0x38800000
		opword 0x38A00004
		bl GXBegin
		opword 0xFC20F850
		lfs f0, float_0p5_80420f7c(r2)
		opword 0x3C80CC01
		opword 0x386000FF
		opword 0xEC5F0032
		opword 0x38000000
		opword 0xEC210032
		opword 0xD0248000
		opword 0xD3C48000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0048000
		opword 0x98648000
		opword 0x98648000
		opword 0x98648000
		opword 0x98648000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0048000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0048000
		opword 0xD0448000
		opword 0xD3C48000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0048000
		opword 0x98648000
		opword 0x98648000
		opword 0x98648000
		opword 0x98648000
		lfs f0, float_2_80420f88(r2)
		opword 0xD0048000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0048000
		opword 0xD0448000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0048000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0048000
		opword 0x98648000
		opword 0x98648000
		opword 0x98648000
		opword 0x98048000
		lfs f0, float_2_80420f88(r2)
		opword 0xD0048000
		lfs f0, float_1_80420f80(r2)
		opword 0xD0048000
		opword 0xD0248000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0048000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0048000
		opword 0x98648000
		opword 0x98648000
		opword 0x98648000
		opword 0x98048000
		lfs f0, float_0_80420f84(r2)
		opword 0xD0048000
		lfs f0, float_1_80420f80(r2)
		opword 0xD0048000
		opword 0x83FC000C
		opword 0x801F00A0
		opword 0x2C000000
		opword 0x40810388
		opword 0xC03F006C
		opword 0x386100C8
		opword 0xC05F0070
		opword 0xC07F0074
		bl PSMTXTrans
		lfs f1, float_0p56_80420f8c(r2)
		opword 0x38610098
		lfs f2, float_0p4_80420f90(r2)
		lfs f3, float_0p8_80420f94(r2)
		bl PSMTXScale
		opword 0x388100C8
		opword 0x38610038
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x386100C8
		opword 0x38810098
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386100C8
		opword 0x38800000
		bl GXLoadPosMtxImm
		lfs f2, float_0_80420f84(r2)
		opword 0x386100C8
		opword 0xC03F00BC
		lfs f0, float_0p125_80420f98(r2)
		opword 0xFC601090
		opword 0xEC210032
		bl PSMTXTrans
		opword 0x386100C8
		opword 0x3880001E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		lwz r5, dat_80420f68(r2)
		opword 0x38810010
		opword 0x801F00A4
		opword 0x38600001
		opword 0x90A1000C
		opword 0x9801000F
		opword 0x8001000C
		opword 0x90010010
		bl GXSetTevColor
		opword 0x38810018
		opword 0x38600037
		bl effGetTexObj
		opword 0x38610018
		opword 0x38800000
		bl GXLoadTexObj
		bl GXClearVtxDesc
		opword 0x38600009
		opword 0x38800002
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x38800009
		opword 0x38A00001
		opword 0x38C00003
		opword 0x38E00008
		bl GXSetVtxAttrFmt
		opword 0x389E0040
		opword 0x38600009
		opword 0x38A00006
		bl GXSetArray
		opword 0x3860000A
		opword 0x38800002
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x3880000A
		opword 0x38A00000
		opword 0x38C00001
		opword 0x38E00006
		bl GXSetVtxAttrFmt
		opword 0x3860000A
		la r4, shibuki_normal_tbl(r13)
		opword 0x38A00003
		bl GXSetArray
		opword 0x3860000B
		opword 0x38800002
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x3880000B
		opword 0x38A00001
		opword 0x38C00005
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x3860000B
		la r4, shibuki_color0_tbl(r13)
		opword 0x38A00004
		bl GXSetArray
		opword 0x3860000D
		opword 0x38800002
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x3880000D
		opword 0x38A00001
		opword 0x38C00003
		opword 0x38E0000E
		bl GXSetVtxAttrFmt
		opword 0x389E0140
		opword 0x3860000D
		opword 0x38A00004
		bl GXSetArray
		la r3, shibuki_dl_1_0(r13)
		opword 0x38800020
		bl GXCallDisplayList
		la r3, shibuki_dl_1_1(r13)
		opword 0x38800020
		bl GXCallDisplayList
		la r3, shibuki_dl_1_2(r13)
		opword 0x38800020
		bl GXCallDisplayList
		la r3, shibuki_dl_1_3(r13)
		opword 0x38800020
		bl GXCallDisplayList
		opword 0xC03F006C
		opword 0x386100C8
		opword 0xC05F0070
		opword 0xC07F0074
		bl PSMTXTrans
		opword 0xC05F0094
		opword 0x38610098
		lfs f0, float_0p8_80420f94(r2)
		lfs f1, float_0p7_80420f9c(r2)
		opword 0xEC620032
		lfs f0, float_0p5_80420f7c(r2)
		opword 0xEC2100F2
		opword 0xEC4000F2
		bl PSMTXScale
		opword 0x388100C8
		opword 0x38610038
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x386100C8
		opword 0x38810098
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386100C8
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0xC01F00BC
		opword 0x386100C8
		lfs f1, float_0_80420f84(r2)
		opword 0xFC400050
		lfs f0, float_0p25_80420fa0(r2)
		opword 0xFC600890
		opword 0xEC420032
		bl PSMTXTrans
		opword 0x386100C8
		opword 0x3880001E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		lwz r0, dat_80420f6c(r2)
		opword 0x38810008
		opword 0x38600001
		opword 0x90010008
		bl GXSetTevColor
		opword 0x38810018
		opword 0x38600036
		bl effGetTexObj
		opword 0x38610018
		opword 0x38800000
		bl GXLoadTexObj
		bl GXClearVtxDesc
		opword 0x38600009
		opword 0x38800002
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x38800009
		opword 0x38A00001
		opword 0x38C00003
		opword 0x38E00008
		bl GXSetVtxAttrFmt
		opword 0x389E0040
		opword 0x38600009
		opword 0x38A00006
		bl GXSetArray
		opword 0x3860000A
		opword 0x38800002
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x3880000A
		opword 0x38A00000
		opword 0x38C00001
		opword 0x38E00006
		bl GXSetVtxAttrFmt
		opword 0x3860000A
		la r4, shibuki_normal_tbl(r13)
		opword 0x38A00003
		bl GXSetArray
		opword 0x3860000B
		opword 0x38800002
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x3880000B
		opword 0x38A00001
		opword 0x38C00005
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x3860000B
		la r4, shibuki_color0_tbl(r13)
		opword 0x38A00004
		bl GXSetArray
		opword 0x3860000D
		opword 0x38800002
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x3880000D
		opword 0x38A00001
		opword 0x38C00003
		opword 0x38E0000E
		bl GXSetVtxAttrFmt
		opword 0x389E0140
		opword 0x3860000D
		opword 0x38A00004
		bl GXSetArray
		opword 0x387E01E0
		opword 0x38800040
		bl GXCallDisplayList
		opword 0x387E0220
		opword 0x38800040
		bl GXCallDisplayList
		opword 0x387E0260
		opword 0x38800040
		bl GXCallDisplayList
		opword 0x387E02A0
		opword 0x38800040
		bl GXCallDisplayList
	}
}
#pragma pop
#endif

s32 effFallCheckHit(EffectEntry* effect) {
    EffFallWork* w = effect->userdata;
    switch (w->type) {
        case 0:
        case 1:
        case 4:
        case 5:
            if (w->state >= 2) return 1;
            break;
        case 2:
        case 3:
            if (w->state >= 1) return 1;
            break;
        case 6:
            if (w->state >= 2 || (w->state == 1 && w->timer > 90)) return 1;
            break;
        case 7:
            if (w->state >= 4) return 1;
            break;
        case 8:
            if (w->state >= 3) return 1;
            break;
    }
    return 0;
}


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_05_803AE094_data[1] = {0};

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802fe418[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fe424[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const u32 dat_802fe430[12] = {0x430C0000, 0x42200000, 0xC1200000, 0x00000000, 0x42200000, 0xC2200000, 0xC30C0000, 0x42200000, 0xC1200000, 0xC3C80000, 0x42200000, 0xC2200000};
__declspec(section ".rodata") const f32 vec3_802fe460[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fe46c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f64 double_to_int_mask_802fe478 = 4503599627370496.0;
__declspec(section ".rodata") const f64 double_to_int_802fe480 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802FE488[24] = "SFX_BTL_STAGE_FALL_BUG1";
__declspec(section ".rodata") const char str_802FE4A0[24] = "SFX_BTL_STAGE_FALL_BUG2";
__declspec(section ".rodata") const char str_802FE4B8[28] = "SFX_BTL_STAGE_DAMAGE_FORK1\0";
__declspec(section ".rodata") const char str_802FE4D4[28] = "SFX_BTL_STAGE_FALL_KOOPA1\0\0";
__declspec(section ".rodata") const char str_802FE4F0[28] = "SFX_BTL_STAGE_FALL_METEOR1\0";
__declspec(section ".rodata") const char str_802FE50C[32] = "SFX_BTL_STAGE_DAMAGE_METEOR2\0\0\0";
__declspec(section ".rodata") const char str_802FE52C[28] = "SFX_BTL_STAGE_DAMAGE_LIGHT1";
__declspec(section ".rodata") const char str_802FE548[12] = "EFF_Baketu\0";
__declspec(section ".rodata") const char str_802FE554[12] = "EFF_Tarai\0\0";
__declspec(section ".rodata") const char str_802FE560[12] = "EFF_koopa\0\0";
__declspec(section ".rodata") const char str_802FE56C[12] = "EFF_inseki\0";
__declspec(section ".rodata") const char str_802FE578[12] = "EFF_light\0\0";
__declspec(section ".rodata") const char str_802FE584[28] = "SFX_BTL_STAGE_FALL_WATER1\0\0";
__declspec(section ".sdata2") const u32 dat_80420f48 = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_80420f4c = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_80420f50 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_80420f54 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80420f58 = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_80420f5c = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_80420f60 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80420f64 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80420f68 = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_80420f6c = 0xFFFFFFFF;
__declspec(section ".sdata2") const f32 float_deg2rad_80420f70 = 0.017453292f;
__declspec(section ".sdata2") const f32 float_64_80420f74 = 64.0f;
__declspec(section ".sdata2") const f32 float_704_80420f78 = 704.0f;
__declspec(section ".sdata2") const f32 float_0p5_80420f7c = 0.5f;
__declspec(section ".sdata2") const f32 float_1_80420f80 = 1.0f;
__declspec(section ".sdata2") const f32 float_0_80420f84 = 0.0f;
__declspec(section ".sdata2") const f32 float_2_80420f88 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p56_80420f8c = 0.56f;
__declspec(section ".sdata2") const f32 float_0p4_80420f90 = 0.4f;
__declspec(section ".sdata2") const f32 float_0p8_80420f94 = 0.8f;
__declspec(section ".sdata2") const f32 float_0p125_80420f98 = 0.125f;
__declspec(section ".sdata2") const f32 float_0p7_80420f9c = 0.7f;
__declspec(section ".sdata2") const f32 float_0p25_80420fa0 = 0.25f;
__declspec(section ".sdata2") const f32 float_6p2832_80420fa4 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_360_80420fa8 = 360.0f;
__declspec(section ".sdata2") const f32 float_2p05_80420fac = 2.05f;
__declspec(section ".sdata2") const f32 float_10_80420fb0 = 10.0f;
__declspec(section ".sdata2") const f32 float_2p1_80420fb4 = 2.1f;
__declspec(section ".sdata2") const f32 float_42p667_80420fb8 = 42.666668f;
__declspec(section ".sdata2") const f32 float_0p33333_80420fbc = 0.33333334f;
__declspec(section ".sdata2") const f32 float_180_80420fc0 = 180.0f;
__declspec(section ".sdata2") const f32 float_neg200_80420fc4 = -200.0f;
__declspec(section ".sdata2") const f32 float_200_80420fc8 = 200.0f;
__declspec(section ".sdata2") const f32 float_neg82p655_80420fcc = -82.655f;
__declspec(section ".sdata2") const f32 float_88p8_80420fd0 = 88.8f;
__declspec(section ".sdata2") const f32 float_1p03_80420fd4 = 1.03f;
__declspec(section ".sdata2") const f32 float_82p655_80420fd8 = 82.655f;
__declspec(section ".sdata2") const f32 float_neg88p8_80420fdc = -88.8f;
__declspec(section ".sdata2") const f32 float_30_80420fe0 = 30.0f;
__declspec(section ".sdata2") const f32 float_neg0p3_80420fe4 = -0.3f;
__declspec(section ".sdata2") const f32 float_35_80420fe8 = 35.0f;
__declspec(section ".sdata2") const f32 float_62p832_80420fec = 62.831856f;
__declspec(section ".sdata2") const f32 float_60_80420ff0 = 60.0f;
__declspec(section ".sdata2") const f32 float_16_80420ff4 = 16.0f;
__declspec(section ".sdata2") const f32 float_neg16_80420ff8 = -16.0f;
__declspec(section ".sdata2") const f32 float_128_80420ffc = 128.0f;
__declspec(section ".sdata2") const f32 float_8p5333_80421000 = 8.533334f;
__declspec(section ".sdata2") const f32 float_0p066667_80421004 = 0.06666667f;
__declspec(section ".sdata2") const f32 float_600_80421008 = 600.0f;
__declspec(section ".sdata2") const f32 float_0p9_8042100c = 0.9f;
__declspec(section ".sdata2") const f32 float_0p01_80421010 = 0.01f;
__declspec(section ".sdata2") const f32 float_0p2_80421014 = 0.2f;
__declspec(section ".sdata2") const char str_80421018[4] = "Z_1";
__declspec(section ".sdata2") const f32 float_neg0p5_8042101c = -0.5f;
__declspec(section ".sdata2") const f32 float_430_80421020 = 430.0f;
__declspec(section ".sdata2") const f32 float_neg27_80421024 = -27.0f;
__declspec(section ".sdata2") const f32 float_80_80421028 = 80.0f;
__declspec(section ".sdata2") const char str_8042102C[4] = "Z_2";
__declspec(section ".sdata2") const f32 float_5_80421030 = 5.0f;
__declspec(section ".sdata2") const f32 float_0p00761_80421034 = 0.00761f;
__declspec(section ".sdata2") const f32 float_0p16605_80421038 = 0.16605f;
__declspec(section ".sdata2") const f32 float_3p1416_8042103c = 3.1415927f;
__declspec(section ".sdata2") const f32 float_1p5708_80421040 = 1.5707964f;
__declspec(section ".sdata2") const f32 float_4p7124_80421044 = 4.712389f;
__declspec(section ".sdata2") const f32 float_0p03705_80421048 = 0.03705f;
__declspec(section ".sdata2") const f32 float_0p4967_8042104c = 0.4967f;
__declspec(section ".sdata2") const f32 float_40_80421050 = 40.0f;
__declspec(section ".sdata2") const char str_80421054[4] = "A_1";
__declspec(section ".sdata2") const char str_80421058[8] = "Fall\0\0\0";
__declspec(section ".sdata2") const f32 float_300_80421060 = 300.0f;
__declspec(section ".sdata2") const f32 float_1p2_80421064 = 1.2f;
__declspec(section ".sdata2") const f32 float_1p6_80421068 = 1.6f;
__declspec(section ".sdata2") const f32 float_0p1_8042106c = 0.1f;
__declspec(section ".sdata2") const f32 float_0p6_80421070 = 0.6f;
__declspec(section ".sdata2") const f32 float_1p3_80421074 = 1.3f;
__declspec(section ".sdata2") const f32 float_400_80421078 = 400.0f;
__declspec(section ".sdata2") const u32 gap_09_8042107C_sdata2[1] = {0};
#endif
