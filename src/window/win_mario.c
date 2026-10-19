#include "win/win_main.h"
#include "data/item_data.h"
#include "driver/animdrv.h"
#include "mario/mario.h"
#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "driver/msgdrv.h"
#include "manager/fontmgr.h"
#include "pmario_sound.h"
#include <dolphin/gx.h>
#include <string.h>
#ifndef NONMATCHING
__declspec(section ".rodata") extern const u32 jumptable_802F57D4[20];
__declspec(section ".rodata") extern const f32 vec3_802f5824[3];
__declspec(section ".rodata") extern const f32 vec3_802f5830[3];
__declspec(section ".rodata") extern const f32 vec3_802f583c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5848[3];
__declspec(section ".rodata") extern const f32 vec3_802f5854[3];
__declspec(section ".rodata") extern const f32 vec3_802f5860[3];
__declspec(section ".rodata") extern const f32 vec3_802f586c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5878[3];
__declspec(section ".rodata") extern const f32 vec3_802f5884[3];
__declspec(section ".rodata") extern const f32 vec3_802f5890[3];
__declspec(section ".rodata") extern const f32 vec3_802f589c[3];
__declspec(section ".rodata") extern const f32 vec3_802f58a8[3];
__declspec(section ".rodata") extern const f32 vec3_802f58b4[3];
__declspec(section ".rodata") extern const f32 vec3_802f58c0[3];
__declspec(section ".rodata") extern const f32 vec3_802f58cc[3];
__declspec(section ".rodata") extern const f32 vec3_802f58d8[3];
__declspec(section ".rodata") extern const f32 vec3_802f58e4[3];
__declspec(section ".rodata") extern const f32 vec3_802f58f0[3];
__declspec(section ".rodata") extern const f32 vec3_802f58fc[3];
__declspec(section ".rodata") extern const f32 vec3_802f5908[3];
__declspec(section ".rodata") extern const f32 vec3_802f5914[3];
__declspec(section ".rodata") extern const f32 vec3_802f5920[3];
__declspec(section ".rodata") extern const f32 vec3_802f592c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5938[3];
__declspec(section ".rodata") extern const u32 dat_802f5944[3];
__declspec(section ".rodata") extern const u32 dat_802f5950[3];
__declspec(section ".rodata") extern const char str_802F5968[];
__declspec(section ".rodata") extern const char str_802F5980[];
__declspec(section ".rodata") extern const char str_802F5998[];
__declspec(section ".rodata") extern const u32 jumptable_802F59B0[3];
__declspec(section ".rodata") extern const f32 vec3_802f59bc[3];
__declspec(section ".rodata") extern const f32 vec3_802f59c8[3];
__declspec(section ".rodata") extern const f32 vec3_802f59d4[3];
__declspec(section ".rodata") extern const f32 vec3_802f59e0[3];
__declspec(section ".rodata") extern const f32 vec3_802f59ec[3];
__declspec(section ".rodata") extern const f32 vec3_802f59f8[3];
__declspec(section ".rodata") extern const f32 vec3_802f5a04[3];
__declspec(section ".rodata") extern const f32 vec3_802f5a10[3];
__declspec(section ".rodata") extern const f32 vec3_802f5a1c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5a28[3];
__declspec(section ".rodata") extern const f32 vec3_802f5a34[3];
__declspec(section ".rodata") extern const f32 vec3_802f5a40[3];
__declspec(section ".rodata") extern const f32 vec3_802f5a4c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5a58[3];
__declspec(section ".rodata") extern const f32 vec3_802f5a64[3];
__declspec(section ".rodata") extern const f32 vec3_802f5a70[3];
__declspec(section ".rodata") extern const f32 vec3_802f5a7c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5a88[3];
__declspec(section ".rodata") extern const f32 vec3_802f5a94[3];
__declspec(section ".rodata") extern const f32 vec3_802f5aa0[3];
__declspec(section ".rodata") extern const f32 vec3_802f5aac[3];
__declspec(section ".rodata") extern const f32 vec3_802f5ab8[3];
__declspec(section ".rodata") extern const f32 vec3_802f5ac4[3];
__declspec(section ".rodata") extern const f32 vec3_802f5ad0[3];
__declspec(section ".rodata") extern const f32 vec3_802f5adc[3];
__declspec(section ".rodata") extern const f32 vec3_802f5ae8[3];
__declspec(section ".rodata") extern const f32 vec3_802f5af4[3];
__declspec(section ".rodata") extern const f32 vec3_802f5b00[3];
__declspec(section ".rodata") extern const f32 vec3_802f5b0c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5b18[3];
__declspec(section ".rodata") extern const f32 vec3_802f5b24[3];
__declspec(section ".rodata") extern const f32 vec3_802f5b30[3];
__declspec(section ".rodata") extern const f32 vec3_802f5b3c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5b48[3];
__declspec(section ".rodata") extern const f32 vec3_802f5b54[3];
__declspec(section ".rodata") extern const f32 vec3_802f5b60[3];
__declspec(section ".rodata") extern const f32 vec3_802f5b6c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5b78[3];
__declspec(section ".rodata") extern const f32 vec3_802f5b84[3];
__declspec(section ".rodata") extern const f32 vec3_802f5b90[3];
__declspec(section ".rodata") extern const f32 vec3_802f5b9c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5ba8[3];
__declspec(section ".rodata") extern const f32 vec3_802f5bb4[3];
__declspec(section ".rodata") extern const f32 vec3_802f5bc0[3];
__declspec(section ".rodata") extern const f32 vec3_802f5bcc[3];
__declspec(section ".rodata") extern const f32 vec3_802f5bd8[3];
__declspec(section ".rodata") extern const f32 vec3_802f5be4[3];
__declspec(section ".rodata") extern const f32 vec3_802f5bf0[3];
__declspec(section ".rodata") extern const f32 vec3_802f5bfc[3];
__declspec(section ".rodata") extern const f32 vec3_802f5c08[3];
__declspec(section ".rodata") extern const f32 vec3_802f5c14[3];
__declspec(section ".rodata") extern const f32 vec3_802f5c20[3];
__declspec(section ".rodata") extern const f32 vec3_802f5c2c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5c38[3];
__declspec(section ".rodata") extern const f32 vec3_802f5c44[3];
__declspec(section ".rodata") extern const f32 vec3_802f5c50[3];
__declspec(section ".rodata") extern const f32 vec3_802f5c5c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5c68[3];
__declspec(section ".rodata") extern const f32 vec3_802f5c74[3];
__declspec(section ".rodata") extern const f32 vec3_802f5c80[3];
__declspec(section ".rodata") extern const f32 vec3_802f5c8c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5c98[3];
__declspec(section ".rodata") extern const f32 vec3_802f5ca4[3];
__declspec(section ".rodata") extern const f32 vec3_802f5cb0[3];
__declspec(section ".rodata") extern const f32 vec3_802f5cbc[3];
__declspec(section ".rodata") extern const f32 vec3_802f5cc8[3];
__declspec(section ".rodata") extern const f32 vec3_802f5cd4[3];
__declspec(section ".rodata") extern const f32 vec3_802f5ce0[3];
__declspec(section ".rodata") extern const f32 vec3_802f5cec[3];
__declspec(section ".rodata") extern const f32 vec3_802f5cf8[3];
__declspec(section ".rodata") extern const f32 vec3_802f5d04[3];
__declspec(section ".rodata") extern const f32 vec3_802f5d10[3];
__declspec(section ".rodata") extern const f32 vec3_802f5d1c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5d28[3];
__declspec(section ".rodata") extern const f32 vec3_802f5d34[3];
__declspec(section ".rodata") extern const f32 vec3_802f5d40[3];
__declspec(section ".rodata") extern const f32 vec3_802f5d4c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5d58[3];
__declspec(section ".rodata") extern const f32 vec3_802f5d64[3];
__declspec(section ".rodata") extern const f32 vec3_802f5d70[3];
__declspec(section ".rodata") extern const f32 vec3_802f5d7c[3];
__declspec(section ".rodata") extern const f32 vec3_802f5d88[3];
__declspec(section ".rodata") extern const char str_802F5D94[];
__declspec(section ".rodata") extern const char str_802F5DA0[];
__declspec(section ".rodata") extern const char str_802F5DB8[];
__declspec(section ".rodata") extern const char str_802F5DD0[];
__declspec(section ".rodata") extern const char str_802F5DE8[];
__declspec(section ".rodata") extern const char str_802F5E00[];
__declspec(section ".rodata") extern const char str_802F5E1C[];
__declspec(section ".rodata") extern const char str_802F5E3C[];
__declspec(section ".rodata") extern const char str_802F5E58[];
__declspec(section ".rodata") extern const f64 double_to_int_mask_802f5e70;
__declspec(section ".rodata") extern const f64 double_to_int_802f5e78;
__declspec(section ".rodata") extern const char str_802F5E80[];
__declspec(section ".rodata") extern const char str_802F5E88[];
__declspec(section ".rodata") extern const char str_802F5E90[];
__declspec(section ".rodata") extern const char str_802F5E9C[];
__declspec(section ".rodata") extern const char str_802F5EA8[];
__declspec(section ".rodata") extern const u32 gap_04_802F5EB4_rodata;
__declspec(section ".sdata2") extern const char str_8041D5A8[];
__declspec(section ".sdata2") extern const char str_8041D5AC[];
__declspec(section ".sdata2") extern const char str_8041D5B0[];
__declspec(section ".sdata2") extern const char str_8041D5B4[];
__declspec(section ".sdata2") extern const char str_8041D5B8[];
__declspec(section ".sdata2") extern const char str_8041D5BC[];
__declspec(section ".sdata2") extern const char str_8041D5C0[];
__declspec(section ".sdata2") extern const char str_8041D5C4[];
__declspec(section ".sdata2") extern const char str_8041D5C8[];
__declspec(section ".sdata2") extern const char str_8041D5CC[];
__declspec(section ".sdata2") extern const u32 dat_8041d5d0;
__declspec(section ".sdata2") extern const u32 dat_8041d5d4;
__declspec(section ".sdata2") extern const u32 dat_8041d5d8;
__declspec(section ".sdata2") extern const u32 dat_8041d5dc;
__declspec(section ".sdata2") extern const u32 dat_8041d5e0;
__declspec(section ".sdata2") extern const u32 dat_8041d5e4;
__declspec(section ".sdata2") extern const u32 dat_8041d5e8;
__declspec(section ".sdata2") extern const u32 dat_8041d5ec;
__declspec(section ".sdata2") extern const char str_8041D5F0[];
__declspec(section ".sdata2") extern const char str_8041D5F8[];
__declspec(section ".sdata2") extern const char str_8041D600[];
__declspec(section ".sdata2") extern const u32 dat_8041d608;
__declspec(section ".sdata2") extern const f32 float_265_8041d60c;
__declspec(section ".sdata2") extern const f32 float_154_8041d610;
__declspec(section ".sdata2") extern const f32 float_190_8041d614;
__declspec(section ".sdata2") extern const f32 float_24_8041d618;
__declspec(section ".sdata2") extern const f32 float_10_8041d61c;
__declspec(section ".sdata2") extern const f32 float_152_8041d620;
__declspec(section ".sdata2") extern const f32 float_0p8_8041d624;
__declspec(section ".sdata2") extern const f32 float_20_8041d628;
__declspec(section ".sdata2") extern const f32 float_142_8041d62c;
__declspec(section ".sdata2") extern const char str_8041D630[];
__declspec(section ".sdata2") extern const f32 float_0_8041d634;
__declspec(section ".sdata2") extern const char str_8041D638[];
__declspec(section ".sdata2") extern const char str_8041D63C[];
__declspec(section ".sdata2") extern const f32 float_255_8041d640;
__declspec(section ".sdata2") extern const f32 float_112_8041d644;
__declspec(section ".sdata2") extern const f32 float_240_8041d648;
__declspec(section ".sdata2") extern const f32 float_124_8041d64c;
__declspec(section ".sdata2") extern const f32 float_270_8041d650;
__declspec(section ".sdata2") extern const f32 float_264_8041d654;
__declspec(section ".sdata2") extern const f32 float_110_8041d658;
__declspec(section ".sdata2") extern const f32 float_50_8041d65c;
__declspec(section ".sdata2") extern const f32 float_2_8041d660;
__declspec(section ".sdata2") extern const f32 float_0p5_8041d664;
__declspec(section ".sdata2") extern const f32 float_38_8041d668;
__declspec(section ".sdata2") extern const f32 float_4_8041d66c;
__declspec(section ".sdata2") extern const f32 float_12_8041d670;
__declspec(section ".sdata2") extern const f32 float_21_8041d674;
__declspec(section ".sdata2") extern const f32 float_34_8041d678;
__declspec(section ".sdata2") extern const f32 float_68_8041d67c;
__declspec(section ".sdata2") extern const f32 float_130_8041d680;
__declspec(section ".sdata2") extern const f32 float_200_8041d684;
__declspec(section ".sdata2") extern const f32 float_260_8041d688;
__declspec(section ".sdata2") extern const f32 float_80_8041d68c;
__declspec(section ".sdata2") extern const f32 float_40_8041d690;
__declspec(section ".sdata2") extern const f32 float_106_8041d694;
__declspec(section ".sdata2") extern const f32 float_70_8041d698;
__declspec(section ".sdata2") extern const f32 float_150_8041d69c;
__declspec(section ".sdata2") extern const f32 float_28_8041d6a0;
__declspec(section ".sdata2") extern const f32 float_56_8041d6a4;
__declspec(section ".sdata2") extern const f32 float_84_8041d6a8;
__declspec(section ".sdata2") extern const f32 float_35_8041d6ac;
__declspec(section ".sdata2") extern const f32 float_8_8041d6b0;
__declspec(section ".sdata2") extern const f32 float_205_8041d6b4;
__declspec(section ".sdata2") extern const f32 float_172_8041d6b8;
__declspec(section ".sdata2") extern const f32 float_16_8041d6bc;
__declspec(section ".sdata2") extern const f32 float_220_8041d6c0;
__declspec(section ".sdata2") extern const f32 float_0_8041d6c4;
__declspec(section ".sdata2") extern const f32 float_1_8041d6c8;
__declspec(section ".sdata2") extern const f32 float_5_8041d6cc;
__declspec(section ".sdata2") extern const f32 float_160_8041d6d0;
__declspec(section ".sdata2") extern const f32 float_254_8041d6d4;
__declspec(section ".sdata2") extern const f32 float_90_8041d6d8;
__declspec(section ".sdata2") extern const char str_8041D6DC[];
__declspec(section ".sdata2") extern const f32 float_228_8041d6e4;
__declspec(section ".sdata2") extern const f32 float_17_8041d6e8;
__declspec(section ".sdata2") extern const f32 float_230_8041d6ec;
__declspec(section ".sdata2") extern const f32 float_72_8041d6f0;
__declspec(section ".sdata2") extern const f32 float_6_8041d6f4;
__declspec(section ".sdata2") extern const f32 float_210_8041d6f8;
__declspec(section ".sdata2") extern const f32 float_30_8041d6fc;
__declspec(section ".sdata2") extern const f32 float_60_8041d700;
__declspec(section ".sdata2") extern const char str_8041D704[];
__declspec(section ".sdata2") extern const char str_8041D708[];
__declspec(section ".sdata2") extern const char str_8041D70C[];
__declspec(section ".sdata2") extern const char str_8041D710[];
__declspec(section ".sdata2") extern const char str_8041D718[];
__declspec(section ".sdata2") extern const char str_8041D720[];
__declspec(section ".sdata2") extern const f32 float_0p89_8041d728;
__declspec(section ".sdata2") extern const f32 float_neg280_8041d72c;
__declspec(section ".sdata2") extern const f32 float_120_8041d730;
__declspec(section ".sdata2") extern const f32 float_26_8041d734;
#define EXT_LIT(sym, val) (sym)
__declspec(section ".rodata") extern const u32 N_stat_name_tbl[3];
#endif
extern const char str_802F5650[];
extern const char str_802F5664[];
extern const char str_802F567C[];
extern const char str_802F5690[];
extern const char str_802F56A4[];
extern const char str_802F56B8[];
extern const char str_802F56C4[];
extern const char str_802F56D0[];
extern const char str_802F56DC[];
extern const char str_802F56E8[];
extern const char str_802F56FC[];
extern const char str_802F5710[];
extern const char str_802F5728[];
extern const char str_802F573C[];
extern const char str_802F5754[];
extern const char str_802F576C[];
extern const char str_802F5780[];
extern const char str_802F5790[];
extern const char str_802F57A0[];
extern const char str_802F57B0[];
extern const char str_802F57BC[];
extern const char str_802F57C8[];
extern const char str_8041D578[];
extern const char str_8041D580[];
extern const char str_8041D584[];
extern const char str_8041D58C[];
extern const char str_8041D590[];
extern const char str_8041D598[];
extern const char str_8041D5A0[];

extern ItemData itemDataTable[];
extern int sprintf(char* str, const char* format, ...);
void winMsgEntry(void* wp, s32 a, const char* msg, s32 b);
void winIconInit(void);
void winIconSet(u32 id, Vec translate, Vec scale, GXColor color);

typedef struct WinMarioWork {
    u16 flags;                    // 0x0
    u8 pad_2[2];                  // 0x2
    u32 buttonTrg;                // 0x4
    u32 buttonRep;                // 0x8
    u32 dirTrg;                   // 0xC
    u32 dirRep;                   // 0x10
    u8 pad_14[0x28 - 0x14];       // 0x14
    struct { u8 pad[0xA0]; void** data; }* file; // 0x28
    u8 pad_2C[0xC0 - 0x2C];       // 0x2C
    struct { s32 field_0x0; f32 x; f32 y; f32 w; f32 h; } pos[2]; // 0xC0
    u8 pad_E8[0x158 - 0xE8];      // 0xE8
    f32 msgX;                     // 0x158
    f32 msgY;                     // 0x15C
    s32 idx;                      // 0x160
    u8 pad_164[0x188 - 0x164];    // 0x164
    s32 poseId;                   // 0x188
    s32 f18C;                     // 0x18C
    s32 f190;                     // 0x190
    s32 f194;                     // 0x194
    s32 f198;                     // 0x198
} WinMarioWork;

typedef struct LinkDt {
    s16 x;              // 0x0
    s16 y;              // 0x2
    const char* pose0;  // 0x4
    const char* pose1;  // 0x8
    const char* pose2;  // 0xC
    u16 item;           // 0x10
    u16 f12;            // 0x12
    const char* msg;    // 0x14
    u8 links[4];        // 0x18
} LinkDt;

typedef struct SuperAction {
    const char* name;  // 0x0
    u8 pad_4[0xC - 0x4];
    const char* desc;  // 0xC
    u8 pad_10[2];
    u8 cost;           // 0x12
} SuperAction;
extern SuperAction* superActionTable[];

LinkDt linkDt[18] = {
    {-268, 142, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F5650), {6, 1, 11, 9}},
    {-268, 118, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F5664), {0, 2, 11, 7}},
    {-272, 68, ((char*)str_8041D584), NULL, ((char*)str_8041D58C), 9, 0, NULL, {1, 3, 11, 7}},
    {-242, 24, ((char*)str_8041D590), NULL, ((char*)str_8041D58C), 6, 0, NULL, {2, 4, 11, 8}},
    {-270, -34, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F567C), {3, 5, 13, 13}},
    {-270, -68, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F5690), {4, 6, 13, 13}},
    {-270, -102, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F56A4), {5, 0, 13, 13}},
    {-100, 90, ((char*)str_8041D578), ((char*)str_8041D578), ((char*)str_8041D580), 2, 0, ((char*)str_802F56B8), {9, 10, 2, 9}},
    {-100, 20, ((char*)str_8041D578), ((char*)str_8041D578), ((char*)str_8041D580), 4, 0, ((char*)str_802F56C4), {10, 4, 3, 10}},
    {-50, 130, ((char*)str_8041D578), ((char*)str_8041D578), ((char*)str_8041D580), 5, 0, ((char*)str_802F56D0), {0, 7, 0, 11}},
    {-50, 60, ((char*)str_8041D578), ((char*)str_8041D578), ((char*)str_8041D580), 3, 0, ((char*)str_802F56DC), {7, 8, 8, 12}},
    {20, 106, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F56E8), {17, 12, 9, 0}},
    {20, 70, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F56FC), {11, 13, 10, 0}},
    {3, 10, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F5710), {12, 14, 4, 4}},
    {3, -18, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F5728), {13, 15, 4, 4}},
    {3, -46, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F573C), {14, 16, 4, 4}},
    {3, -74, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F5754), {15, 17, 4, 4}},
    {3, -102, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F576C), {16, 11, 4, 4}},
};
#ifdef NONMATCHING
const char* hammer_help[] = {NULL, ((char*)str_802F5780), ((char*)str_802F5790), ((char*)str_802F57A0)};
const char* boots_help[] = {NULL, ((char*)str_802F57B0), ((char*)str_802F57BC), ((char*)str_802F57C8)};
const char* hammer_pose[] = {NULL, ((char*)str_8041D584), ((char*)str_8041D598), ((char*)str_8041D5A0)};
#endif
#ifndef NONMATCHING
__declspec(section ".sdata") const char* hammer_help[] = {NULL, ((char*)str_802F5780), ((char*)str_802F5790), ((char*)str_802F57A0)};
__declspec(section ".sdata") const char* boots_help[] = {NULL, ((char*)str_802F57B0), ((char*)str_802F57BC), ((char*)str_802F57C8)};
__declspec(section ".sdata") const char* hammer_pose[] = {NULL, ((char*)str_8041D584), ((char*)str_8041D598), ((char*)str_8041D5A0)};
#endif

#ifdef NONMATCHING
void winMarioInit(WinMarioWork* w) {
    PouchData* pouch;
    const char* name;
    s32 i;

    pouch = pouchGetPtr();
    if (w->flags & 0x2000) {
        name = "S_1";
        switch (marioGetColor()) {
            case 0:
                name = "S_1";
                break;
            case 1:
                name = "S_2";
                break;
            case 2:
                name = "S_3";
                break;
            case 3:
                name = "S_4";
                break;
        }
        w->poseId = animPoseEntry("d_mario", 0);
        animPoseSetAnim(w->poseId, name, 1);
    } else {
        name = "a_mario";
        switch (marioGetColor()) {
            case 0: name = "a_mario"; break;
            case 1: name = "a_mario_l"; break;
            case 2: name = "a_mario_w"; break;
            case 3: name = "a_mario_wl\0\0\0\0\0"; break;
        }
        w->poseId = animPoseEntry(name, 0);
        animPoseSetAnim(w->poseId, "M_S_1", 1);
    }
    animPoseSetMaterialFlagOn(w->poseId, 0x1800);
    if (marioGetPtr()->flags & 0x40000000) {
        animPoseSetMaterialFlagOn(w->poseId, 0x0A000000);
    }
    w->f18C = 0;
    w->f190 = 0;
    w->f194 = 0;
    w->f198 = 0;
    for (i = 0; i < 8; i++) {
        if (*(u16*)&pouch->mStarPowersObtained & (1 << i)) {
            w->f198++;
        }
    }
}
#endif
#ifndef NONMATCHING
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
int __div2i();
int __div2u();
int __mod2u();
int strcat();
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
size_t strlen(const char *s);
const char* BattleGetRankNameLabel(s32 level);
void fukidashi(WinMarioWork* w, u32 idx, f32 x, f32 y);
void winBgGX(WinMarioWork* w, s32 a, f32 x, f32 y);
void winFontInit(void);
void winFontSet(Vec pos, Vec scale, GXColor color, const char* fmt, ...);
void winFontSetEdge(Vec pos, Vec scale, GXColor color, const char* fmt, ...);
void winFontSetLabel(Vec pos, Vec scale, GXColor color, const char* msg);
void winFontSetR(Vec pos, Vec scale, GXColor color, const char* fmt, ...);
void winKageGX(WinMarioWork* w, GXColor color, f32 x, f32 y, f32 z, f32 scale);
void winKirinukiGX(WinMarioWork* w, s32 a, f32 x, f32 y, f32 w_, f32 h);
void winNameGX(WinMarioWork* w, s32 a, f32 x, f32 y, f32 w_, f32 h);
void winWazaGX(WinMarioWork* w, s32 a, f32 x, f32 y, f32 w_, f32 h);
void winZClear(void);
void winMarioInit(WinMarioWork* w);
#endif


#ifdef NONMATCHING
void winMarioInit2(WinMarioWork* w) {
    w->idx = 0;
    w->msgX = w->msgX = linkDt[w->idx].x;
    w->msgY = w->msgY = linkDt[w->idx].y;
    switch (w->idx) {
    case 2:
        winMsgEntry(w, 0, hammer_help[pouchGetHammerLv()], 0);
        break;
    case 3:
        winMsgEntry(w, 0, boots_help[pouchGetJumpLv()], 0);
        break;
    default:
        winMsgEntry(w, 0, linkDt[w->idx].msg, 0);
        break;
    }
    w->f18C = 0;
    w->f190 = 0;
    w->f194 = 0;
}
#endif
#ifndef NONMATCHING
void winMarioInit2(WinMarioWork* w);
#endif

#ifdef NONMATCHING
void winMarioExit(WinMarioWork* w) {
    animPoseRelease(w->poseId);
}
#endif
#ifndef NONMATCHING
void winMarioExit(WinMarioWork* w);
#endif

#ifdef NONMATCHING
#define COLOR_ANIM(var, base)                         \
    if (strcmp(base, "S_1") == 0) {                   \
        switch (marioGetColor()) {                    \
            case 0: var = "S_1"; break;               \
            case 1: var = "S_2"; break;               \
            case 2: var = "S_3"; break;               \
            case 3: var = "S_4"; break;               \
        }                                             \
    } else {                                          \
        switch (marioGetColor()) {                    \
            case 0: var = "R_1"; break;               \
            case 1: var = "R_15"; break;              \
            case 2: var = "R_17"; break;              \
            case 3: var = "R_18"; break;              \
        }                                             \
    }
#endif
#ifndef NONMATCHING
#define COLOR_ANIM(var, base)                         \
    if (strcmp(base, EXT_LIT((char*)str_8041D580, "S_1")) == 0) {                   \
        switch (marioGetColor()) {                    \
            case 0: var = EXT_LIT((char*)str_8041D580, "S_1"); break;               \
            case 1: var = EXT_LIT((char*)str_8041D704, "S_2"); break;               \
            case 2: var = EXT_LIT((char*)str_8041D708, "S_3"); break;               \
            case 3: var = EXT_LIT((char*)str_8041D70C, "S_4"); break;               \
        }                                             \
    } else {                                          \
        switch (marioGetColor()) {                    \
            case 0: var = EXT_LIT((char*)str_8041D58C, "R_1"); break;               \
            case 1: var = EXT_LIT((char*)str_8041D710, "R_15"); break;              \
            case 2: var = EXT_LIT((char*)str_8041D718, "R_17"); break;              \
            case 3: var = EXT_LIT((char*)str_8041D720, "R_18"); break;              \
        }                                             \
    }
#endif

#define NAV(n)                                                        \
    w->idx = linkDt[w->idx].links[n];                                 \
    p = &linkDt[w->idx];                                              \
    while (1) {                                                       \
        if (w->idx == 11 || w->idx == 12) {                           \
            if (w->f198 != 0) break;                                  \
        } else if (p->item == 0 || ((s32(*)(u32))pouchCheckItem)(p->item) != 0) {    \
            break;                                                    \
        }                                                             \
        w->idx = p->links[n];                                         \
        p = &linkDt[w->idx];                                          \
    }                                                                 \
    psndSFXOn((const char*)0x20005);

#ifdef NONMATCHING
s32 winMarioMain(WinMarioWork* w) {
    const char* anims[2];
    LinkDt* lp;
    LinkDt* p;
#endif
#ifndef NONMATCHING
s32 winMarioMain(WinMarioWork* w);
#endif

#ifdef NONMATCHING
    switch (w->f190) {
        case 0:
            if (w->buttonTrg & 0x100) {
                if (w->idx == 12) {
                    w->f190 = 1;
                    w->f194 = 0;
                    psndSFXOn((const char*)0x20012);
                }
            } else if (w->buttonTrg & 0x200) {
                psndSFXOn((const char*)0x20013);
                if (w->flags & 0x2000) {
                    COLOR_ANIM(anims[1], "S_1")
                } else {
                    anims[1] = "M_S_1";
                }
                animPoseSetAnim(w->poseId, anims[1], 0);
                return -1;
            } else if (w->buttonTrg & 0x1000) {
                return -2;
            } else if (w->dirRep & 0x1000) {
                NAV(0)
            } else if (w->dirRep & 0x2000) {
                NAV(1)
            } else if (w->dirRep & 0x4000) {
                NAV(2)
            } else if (w->dirRep & 0x8000) {
                NAV(3)
            }
            lp = &linkDt[w->idx];
            w->msgX = lp->x;
            w->msgY = lp->y;
            switch (w->idx) {
            case 2:
                if (w->flags & 0x2000) {
                    COLOR_ANIM(anims[0], lp->pose2)
                } else {
                    anims[0] = hammer_pose[pouchGetHammerLv()];
                }
                animPoseSetAnim(w->poseId, anims[0], 0);
                if (w->f18C == 0) {
                    if (animPoseGetLoopTimes(w->poseId) >= 0.89f) {
                        w->f18C = 30;
                    }
                } else {
                    w->f18C--;
                }
                if (w->flags & 0x2000) {
                    w->f18C = 0;
                }
                break;
            default:
                w->f18C = 0;
                if (w->flags & 0x2000) {
                    COLOR_ANIM(anims[0], lp->pose2)
                } else {
                    anims[0] = lp->pose0;
                }
                animPoseSetAnim(w->poseId, anims[0], 0);
                break;
            }
            switch (w->idx) {
                case 2:
                    winMsgEntry(w, 0, hammer_help[pouchGetHammerLv()], 0);
                    break;
                case 3:
                    winMsgEntry(w, 0, boots_help[pouchGetJumpLv()], 0);
                    break;
                default:
                    winMsgEntry(w, 0, lp->msg, 0);
                    break;
            }
            break;
        case 1:
            if (w->dirRep & 0x1000) {
                w->f194--;
                if (w->f194 < 0) {
                    w->f194 = w->f198 - 1;
                }
                psndSFXOn((const char*)0x20005);
            } else if (w->dirRep & 0x2000) {
                w->f194++;
                if (w->f194 >= w->f198) {
                    w->f194 = 0;
                }
                psndSFXOn((const char*)0x20005);
            } else if (w->buttonTrg & 0x200) {
                w->f190 = 0;
                psndSFXOn((const char*)0x20013);
            } else if (w->buttonTrg & 0x1000) {
                return -2;
            }
            w->msgX = -280.0f;
            w->msgY = 10.0f + (120.0f - 26.0f * w->f194 - 12.0f);
            winMsgEntry(w, 0, superActionTable[w->f194]->desc, 0);
            break;
    }
    return 0;
}
#endif
#ifndef NONMATCHING
void winMarioMain2(void);
#endif

#ifdef NONMATCHING
void winMarioMain2(void) {
}

const char* winZenkakuStr(s32 n) {
    const char* tbl[10] = {"\x82\x4f", "\x82\x50", "\x82\x51", "\x82\x52", "\x82\x53",
                           "\x82\x54", "\x82\x55", "\x82\x56", "\x82\x57", "\x82\x58"};
    static char tmp2[0x100];
    char buf[0x100];
    u32 i;
    if (n < 0) {
        strcpy(tmp2, "\x81\x7c");
        n = -n;
    } else {
        strcpy(tmp2, "");
    }
    sprintf(buf, "%d", n);
    for (i = 0; i < strlen(buf); i++) {
        strcat(tmp2, tbl[(s8)buf[i] - '0']);
    }
    return tmp2;
}
#endif
#ifndef NONMATCHING
extern char unk_803dfbf8[];
const char* winZenkakuStr(s32 n);
#endif

// FAKE: tmp2 (target local static, .bss after unk_803dfbf8) folded in as unk_803dfbf8+0x100; MWCC would not emit them in target order
char unk_803dfbf8[0x200];

#ifdef NONMATCHING
char* unk_8016af5c(s32 n, s32 digits) {
    const char* tbl[10] = {"\x82\x4f", "\x82\x50", "\x82\x51", "\x82\x52", "\x82\x53",
                           "\x82\x54", "\x82\x55", "\x82\x56", "\x82\x57", "\x82\x58"};
    char buf[0x100];
    s32 i;
    if (n < 0) {
        strcpy(unk_803dfbf8, "\x81\x7c");
        n = -n;
    } else {
        strcpy(unk_803dfbf8, "");
    }
    sprintf(buf, "%d", n);
    for (i = 0; i < digits; i++) {
        if ((u32)i < (u32)(digits - strlen(buf))) {
            strcat(unk_803dfbf8, "\x82\x4f");
        } else {
            strcat(unk_803dfbf8, tbl[(s8)buf[i - (digits - strlen(buf))] - '0']);
        }
    }
    return unk_803dfbf8;
}
#endif
#ifndef NONMATCHING
char* unk_8016af5c(s32 n, s32 digits);
#endif


#ifdef NONMATCHING
static inline void fukiKey(WinMarioWork* w, u16 icon, f32 x, f32 y) {
    winTexInit(*w->file->data);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
    winTexSet(0xB1, (Vec){x + 5.0f, y - 5.0f, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, (GXColor){0x00, 0x00, 0x00, 0x80});
    winTexSet(0xB1, (Vec){x, y, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, (GXColor){0xE1, 0xE1, 0xE1, 0xFE});
    winIconInit();
    winIconSet(icon, (Vec){x + 6.0f, y, 0.0f}, (Vec){0.7f, 0.7f, 0.7f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
}
#endif

#ifdef NONMATCHING
static inline void fukiTool(WinMarioWork* w, u16 icon, f32 x, f32 y) {
    winTexInit(*w->file->data);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
    winTexSet(0xB1, (Vec){x + 5.0f, y - 5.0f, 0.0f}, (Vec){-0.8f, 0.8f, 0.8f}, (GXColor){0x00, 0x00, 0x00, 0x80});
    winTexSet(0xB1, (Vec){x, y, 0.0f}, (Vec){-0.8f, 0.8f, 0.8f}, (GXColor){0xE1, 0xE1, 0xE1, 0xFE});
    winIconInit();
    winIconSet(icon, (Vec){x - 6.0f, y, 0.0f}, (Vec){0.7f, 0.7f, 0.7f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
}
#endif

#ifdef NONMATCHING
void fukidashi(WinMarioWork* w, u32 idx, f32 x, f32 y) {
    switch (idx) {
        case 2:
            if (pouchGetHammerLv() > 0) {
                fukiTool(w, itemDataTable[pouchGetHammerLv() + 8].icon_id, x - 230.0f, y + 72.0f);
            }
            break;
        case 3:
            if (pouchGetJumpLv() > 0) {
                fukiTool(w, itemDataTable[pouchGetJumpLv() + 5].icon_id, x - 210.0f, y + 20.0f);
            }
            break;
        case 7:
            if (((s32(*)(u32))pouchCheckItem)(2)) {
                fukiKey(w, itemDataTable[2].icon_id, x - 80.0f, y + 90.0f);
            }
            break;
        case 8:
            if (((s32(*)(u32))pouchCheckItem)(4)) {
                fukiKey(w, itemDataTable[4].icon_id, x - 80.0f, y + 20.0f);
            }
            break;
        case 9:
            if (((s32(*)(u32))pouchCheckItem)(5)) {
                fukiKey(w, itemDataTable[5].icon_id, x - 30.0f, y + 130.0f);
            }
            break;
        case 10:
            if (((s32(*)(u32))pouchCheckItem)(3)) {
                fukiKey(w, itemDataTable[3].icon_id, x - 30.0f, y + 60.0f);
            }
            break;
    }
}
#endif
#ifndef NONMATCHING
void fukidashi(WinMarioWork* w, u32 idx, f32 x, f32 y);
extern void* jumptable_80374F08[];
void fukidashi(WinMarioWork* w, u32 idx, f32 x, f32 y);
#endif

void winBgGX(WinMarioWork* w, s32 a, f32 x, f32 y);
void winNameGX(WinMarioWork* w, s32 a, f32 x, f32 y, f32 w_, f32 h);
void winKirinukiGX(WinMarioWork* w, s32 a, f32 x, f32 y, f32 w_, f32 h);
void winWazaGX(WinMarioWork* w, s32 a, f32 x, f32 y, f32 w_, f32 h);
void winKageGX(WinMarioWork* w, GXColor color, f32 x, f32 y, f32 z, f32 scale);
void winZClear(void);
void winFontInit(void);
void winFontSet(Vec pos, Vec scale, GXColor color, const char* fmt, ...);
void winFontSetR(Vec pos, Vec scale, GXColor color, const char* fmt, ...);
void winFontSetEdge(Vec pos, Vec scale, GXColor color, const char* fmt, ...);
void winFontSetLabel(Vec pos, Vec scale, GXColor color, const char* msg);
const char* BattleGetRankNameLabel(s32 level);



#ifndef NONMATCHING
__declspec(section ".sdata") u32 g5_pri_s896[6] = {0x00000003, 0x00000002, 0x00000008, 0x0000000A, 0x00000007, 0x00000009};
void winMarioDisp(s32 camId, void* param, s32 idx);

#pragma force_active on
#pragma explicit_zero_data on
#pragma explicit_zero_data reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
char* unk_8016af5c(s32 n, s32 digits) {
	asm volatile {
		opword 0x9421FEC0
		opword 0x7C0802A6
		lis r5, jumptable_802F57D4+0x28@ha
		opword 0x90010144
		addi r12, r5, jumptable_802F57D4+0x28@l
		opword 0x93E1013C
		opword 0x7C9F2378
		opword 0x93C10138
		opword 0x7C7E1B79
		opword 0x816C0000
		opword 0x814C0004
		opword 0x812C0008
		opword 0x810C000C
		opword 0x80EC0010
		opword 0x80CC0014
		opword 0x80AC0018
		opword 0x808C001C
		opword 0x806C0020
		opword 0x800C0024
		opword 0x91610008
		opword 0x9141000C
		opword 0x91210010
		opword 0x91010014
		opword 0x90E10018
		opword 0x90C1001C
		opword 0x90A10020
		opword 0x90810024
		opword 0x90610028
		opword 0x9001002C
		opword 0x4080001C
		lis r3, unk_803dfbf8@ha
		la r4, str_8041D630(r2)
		addi r3, r3, unk_803dfbf8@l
		bl strcpy
		opword 0x7FDE00D0
		opword 0x48000014
		lis r3, unk_803dfbf8@ha
		la r4, float_0_8041d634(r2)
		addi r3, r3, unk_803dfbf8@l
		bl strcpy
		opword 0x7FC5F378
		opword 0x38610030
		la r4, str_8041D638(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x3BC00000
		opword 0x48000068
		opword 0x38610030
		bl strlen
		opword 0x7C03F850
		opword 0x7C1E0040
		opword 0x40800018
		lis r3, unk_803dfbf8@ha
		la r4, str_8041D5A8(r2)
		addi r3, r3, unk_803dfbf8@l
		bl strcat
		opword 0x4800003C
		opword 0x38610030
		bl strlen
		opword 0x7C03F850
		lis r3, unk_803dfbf8@ha
		opword 0x7C00F050
		opword 0x38810030
		opword 0x7C0400AE
		opword 0x38810008
		addi r3, r3, unk_803dfbf8@l
		opword 0x7C000774
		opword 0x5405103A
		opword 0x3805FF40
		opword 0x7C84002E
		bl strcat
		opword 0x3BDE0001
		opword 0x7C1EF800
		opword 0x4180FF98
		opword 0x80010144
		lis r3, unk_803dfbf8@ha
		opword 0x83E1013C
		addi r3, r3, unk_803dfbf8@l
		opword 0x83C10138
		opword 0x7C0803A6
		opword 0x38210140
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void fukidashi(WinMarioWork* w, u32 idx, f32 x, f32 y) {
	char _af_pad[712];
	asm volatile {
		fmr f30, f1
		opword 0x2804000A
		lis r5, str_802F5650@ha
		opword 0xFFE01090
		opword 0x7C7E1B78
		addi r31, r5, str_802F5650@l
		opword 0x41810B08
		lis r3, jumptable_80374F08@ha
		opword 0x5480103A
		addi r3, r3, jumptable_80374F08@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		bl pouchGetHammerLv
		opword 0x2C030000
		opword 0x40810AE4
		bl pouchGetHammerLv
		opword 0x809E0028
		opword 0x1CC30028
		lis r5, itemDataTable@ha
		opword 0x806400A0
		addi r0, r5, itemDataTable@l
		opword 0x7C803214
		opword 0x80630000
		lhz r30, 0x160(r4)
		bl winTexInit
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00002
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		lfs f1, float_230_8041d6ec(r2)
		la r4, _af_pad+612
		lfs f0, float_72_8041d6f0(r2)
		opword 0x38A10284
		opword 0xEC3E0828
		opword 0x811F0224
		lfs f2, float_5_8041d6cc(r2)
		opword 0xEFE0F82A
		opword 0x807F021C
		opword 0x38C10044
		opword 0x801F0220
		opword 0xEC22082A
		opword 0x90610278
		opword 0xEC1F1028
		lwz r12, dat_8041d5dc(r2)
		opword 0x386000B1
		opword 0x9001027C
		opword 0x817F0228
		opword 0xD0210278
		opword 0x815F022C
		opword 0xD001027C
		opword 0x813F0230
		opword 0x80E10278
		opword 0x8001027C
		opword 0x91810044
		opword 0x91610284
		opword 0x91410288
		opword 0x9121028C
		opword 0x91010280
		opword 0x90E1026C
		opword 0x90010270
		opword 0x91010274
		bl winTexSet
		lfs f0, float_230_8041d6ec(r2)
		opword 0x38810290
		opword 0x807F0234
		opword 0x38A102A8
		opword 0x801F0238
		opword 0xEC1E0028
		opword 0x9061029C
		opword 0x38C10048
		opword 0x811F023C
		opword 0x386000B1
		opword 0x900102A0
		lwz r12, dat_8041d5e0(r2)
		opword 0xD001029C
		opword 0x817F0240
		opword 0xD3E102A0
		opword 0x815F0244
		opword 0x813F0248
		opword 0x80E1029C
		opword 0x800102A0
		opword 0x91810048
		opword 0x916102A8
		opword 0x914102AC
		opword 0x912102B0
		opword 0x910102A4
		opword 0x90E10290
		opword 0x90010294
		opword 0x91010298
		bl winTexSet
		bl winIconInit
		lfs f0, float_230_8041d6ec(r2)
		opword 0x7FC3F378
		opword 0x811F0254
		opword 0x388102B4
		opword 0xEC3E0028
		lfs f0, float_6_8041d6f4(r2)
		opword 0x80FF024C
		opword 0x38A102CC
		opword 0x801F0250
		opword 0x38C1004C
		opword 0x900102C4
		opword 0xEC010028
		lwz r12, dat_8041d5e4(r2)
		opword 0x90E102C0
		opword 0x817F0258
		opword 0xD00102C0
		opword 0x815F025C
		opword 0xD3E102C4
		opword 0x813F0260
		opword 0x80E102C0
		opword 0x800102C4
		opword 0x9181004C
		opword 0x916102CC
		opword 0x914102D0
		opword 0x912102D4
		opword 0x910102C8
		opword 0x90E102B4
		opword 0x900102B8
		opword 0x910102BC
		bl winIconSet
		opword 0x48000918
		bl pouchGetJumpLv
		opword 0x2C030000
		opword 0x4081090C
		bl pouchGetJumpLv
		opword 0x809E0028
		opword 0x1CC30028
		lis r5, itemDataTable@ha
		opword 0x806400A0
		addi r0, r5, itemDataTable@l
		opword 0x7C803214
		opword 0x80630000
		opword 0xA3C400E8
		bl winTexInit
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00002
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		lfs f1, float_210_8041d6f8(r2)
		opword 0x38810200
		lfs f0, float_20_8041d628(r2)
		opword 0x38A10218
		opword 0xEC3E0828
		opword 0x811F0224
		lfs f2, float_5_8041d6cc(r2)
		opword 0xEFE0F82A
		opword 0x807F021C
		opword 0x38C10038
		opword 0x801F0220
		opword 0xEC22082A
		opword 0x9061020C
		opword 0xEC1F1028
		lwz r12, dat_8041d5dc(r2)
		opword 0x386000B1
		opword 0x90010210
		opword 0x817F0228
		opword 0xD021020C
		opword 0x815F022C
		opword 0xD0010210
		opword 0x813F0230
		opword 0x80E1020C
		opword 0x80010210
		opword 0x91810038
		opword 0x91610218
		opword 0x9141021C
		opword 0x91210220
		opword 0x91010214
		opword 0x90E10200
		opword 0x90010204
		opword 0x91010208
		bl winTexSet
		lfs f0, float_210_8041d6f8(r2)
		opword 0x38810224
		opword 0x807F0234
		opword 0x38A1023C
		opword 0x801F0238
		opword 0xEC1E0028
		opword 0x90610230
		opword 0x38C1003C
		opword 0x811F023C
		opword 0x386000B1
		opword 0x90010234
		lwz r12, dat_8041d5e0(r2)
		opword 0xD0010230
		opword 0x817F0240
		opword 0xD3E10234
		opword 0x815F0244
		opword 0x813F0248
		opword 0x80E10230
		opword 0x80010234
		opword 0x9181003C
		opword 0x9161023C
		opword 0x91410240
		opword 0x91210244
		opword 0x91010238
		opword 0x90E10224
		opword 0x90010228
		opword 0x9101022C
		bl winTexSet
		bl winIconInit
		lfs f0, float_210_8041d6f8(r2)
		opword 0x7FC3F378
		opword 0x811F0254
		opword 0x38810248
		opword 0xEC3E0028
		lfs f0, float_6_8041d6f4(r2)
		opword 0x80FF024C
		opword 0x38A10260
		opword 0x801F0250
		opword 0x38C10040
		opword 0x90010258
		opword 0xEC010028
		lwz r12, dat_8041d5e4(r2)
		opword 0x90E10254
		opword 0x817F0258
		opword 0xD0010254
		opword 0x815F025C
		opword 0xD3E10258
		opword 0x813F0260
		opword 0x80E10254
		opword 0x80010258
		opword 0x91810040
		opword 0x91610260
		opword 0x91410264
		opword 0x91210268
		opword 0x9101025C
		opword 0x90E10248
		opword 0x9001024C
		opword 0x91010250
		bl winIconSet
		opword 0x48000740
		opword 0x38600002
		bl pouchCheckItem
		opword 0x2C030000
		opword 0x41820730
		opword 0x807E0028
		lis r4, itemDataTable@ha
		addi r4, r4, itemDataTable@l
		opword 0x806300A0
		opword 0xA3C40070
		opword 0x80630000
		bl winTexInit
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00002
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		lfs f1, float_80_8041d68c(r2)
		opword 0x38810194
		lfs f0, float_90_8041d6d8(r2)
		opword 0x38A101AC
		opword 0xEC3E0828
		opword 0x811F01DC
		lfs f2, float_5_8041d6cc(r2)
		opword 0xEFE0F82A
		opword 0x807F01D4
		opword 0x38C1002C
		opword 0x801F01D8
		opword 0xEC22082A
		opword 0x906101A0
		opword 0xEC1F1028
		lwz r12, dat_8041d5d0(r2)
		opword 0x386000B1
		opword 0x900101A4
		opword 0x817F01E0
		opword 0xD02101A0
		opword 0x815F01E4
		opword 0xD00101A4
		opword 0x813F01E8
		opword 0x80E101A0
		opword 0x800101A4
		opword 0x9181002C
		opword 0x916101AC
		opword 0x914101B0
		opword 0x912101B4
		opword 0x910101A8
		opword 0x90E10194
		opword 0x90010198
		opword 0x9101019C
		bl winTexSet
		lfs f0, float_80_8041d68c(r2)
		opword 0x388101B8
		opword 0x807F01EC
		opword 0x38A101D0
		opword 0x801F01F0
		opword 0xEC1E0028
		opword 0x906101C4
		opword 0x38C10030
		opword 0x811F01F4
		opword 0x386000B1
		opword 0x900101C8
		lwz r12, dat_8041d5d4(r2)
		opword 0xD00101C4
		opword 0x817F01F8
		opword 0xD3E101C8
		opword 0x815F01FC
		opword 0x813F0200
		opword 0x80E101C4
		opword 0x800101C8
		opword 0x91810030
		opword 0x916101D0
		opword 0x914101D4
		opword 0x912101D8
		opword 0x910101CC
		opword 0x90E101B8
		opword 0x900101BC
		opword 0x910101C0
		bl winTexSet
		bl winIconInit
		lfs f0, float_80_8041d68c(r2)
		opword 0x7FC3F378
		opword 0x811F020C
		opword 0x388101DC
		opword 0xEC1E0028
		lfs f1, float_6_8041d6f4(r2)
		opword 0x80FF0204
		opword 0x38A101F4
		opword 0x801F0208
		opword 0x38C10034
		opword 0x900101EC
		opword 0xEC01002A
		lwz r12, dat_8041d5d8(r2)
		opword 0x90E101E8
		opword 0x817F0210
		opword 0xD00101E8
		opword 0x815F0214
		opword 0xD3E101EC
		opword 0x813F0218
		opword 0x80E101E8
		opword 0x800101EC
		opword 0x91810034
		opword 0x916101F4
		opword 0x914101F8
		opword 0x912101FC
		opword 0x910101F0
		opword 0x90E101DC
		opword 0x900101E0
		opword 0x910101E4
		bl winIconSet
		opword 0x48000570
		opword 0x38600004
		bl pouchCheckItem
		opword 0x2C030000
		opword 0x41820560
		opword 0x807E0028
		lis r4, itemDataTable@ha
		addi r4, r4, itemDataTable@l
		opword 0x806300A0
		opword 0xA3C400C0
		opword 0x80630000
		bl winTexInit
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00002
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		lfs f1, float_80_8041d68c(r2)
		opword 0x38810128
		lfs f0, float_20_8041d628(r2)
		opword 0x38A10140
		opword 0xEC3E0828
		opword 0x811F01DC
		lfs f2, float_5_8041d6cc(r2)
		opword 0xEFE0F82A
		opword 0x807F01D4
		opword 0x38C10020
		opword 0x801F01D8
		opword 0xEC22082A
		opword 0x90610134
		opword 0xEC1F1028
		lwz r12, dat_8041d5d0(r2)
		opword 0x386000B1
		opword 0x90010138
		opword 0x817F01E0
		opword 0xD0210134
		opword 0x815F01E4
		opword 0xD0010138
		opword 0x813F01E8
		opword 0x80E10134
		opword 0x80010138
		opword 0x91810020
		opword 0x91610140
		opword 0x91410144
		opword 0x91210148
		opword 0x9101013C
		opword 0x90E10128
		opword 0x9001012C
		opword 0x91010130
		bl winTexSet
		lfs f0, float_80_8041d68c(r2)
		opword 0x3881014C
		opword 0x807F01EC
		opword 0x38A10164
		opword 0x801F01F0
		opword 0xEC1E0028
		opword 0x90610158
		opword 0x38C10024
		opword 0x811F01F4
		opword 0x386000B1
		opword 0x9001015C
		lwz r12, dat_8041d5d4(r2)
		opword 0xD0010158
		opword 0x817F01F8
		opword 0xD3E1015C
		opword 0x815F01FC
		opword 0x813F0200
		opword 0x80E10158
		opword 0x8001015C
		opword 0x91810024
		opword 0x91610164
		opword 0x91410168
		opword 0x9121016C
		opword 0x91010160
		opword 0x90E1014C
		opword 0x90010150
		opword 0x91010154
		bl winTexSet
		bl winIconInit
		lfs f0, float_80_8041d68c(r2)
		opword 0x7FC3F378
		opword 0x811F020C
		opword 0x38810170
		opword 0xEC1E0028
		lfs f1, float_6_8041d6f4(r2)
		opword 0x80FF0204
		opword 0x38A10188
		opword 0x801F0208
		opword 0x38C10028
		opword 0x90010180
		opword 0xEC01002A
		lwz r12, dat_8041d5d8(r2)
		opword 0x90E1017C
		opword 0x817F0210
		opword 0xD001017C
		opword 0x815F0214
		opword 0xD3E10180
		opword 0x813F0218
		opword 0x80E1017C
		opword 0x80010180
		opword 0x91810028
		opword 0x91610188
		opword 0x9141018C
		opword 0x91210190
		opword 0x91010184
		opword 0x90E10170
		opword 0x90010174
		opword 0x91010178
		bl winIconSet
		opword 0x480003A0
		opword 0x38600005
		bl pouchCheckItem
		opword 0x2C030000
		opword 0x41820390
		opword 0x807E0028
		lis r4, itemDataTable@ha
		addi r4, r4, itemDataTable@l
		opword 0x806300A0
		opword 0xA3C400E8
		opword 0x80630000
		bl winTexInit
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00002
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		lfs f1, float_30_8041d6fc(r2)
		opword 0x388100BC
		lfs f0, float_130_8041d680(r2)
		opword 0x38A100D4
		opword 0xEC3E0828
		opword 0x811F01DC
		lfs f2, float_5_8041d6cc(r2)
		opword 0xEFE0F82A
		opword 0x807F01D4
		opword 0x38C10014
		opword 0x801F01D8
		opword 0xEC22082A
		opword 0x906100C8
		opword 0xEC1F1028
		lwz r12, dat_8041d5d0(r2)
		opword 0x386000B1
		opword 0x900100CC
		opword 0x817F01E0
		opword 0xD02100C8
		opword 0x815F01E4
		opword 0xD00100CC
		opword 0x813F01E8
		opword 0x80E100C8
		opword 0x800100CC
		opword 0x91810014
		opword 0x916100D4
		opword 0x914100D8
		opword 0x912100DC
		opword 0x910100D0
		opword 0x90E100BC
		opword 0x900100C0
		opword 0x910100C4
		bl winTexSet
		lfs f0, float_30_8041d6fc(r2)
		opword 0x388100E0
		opword 0x807F01EC
		opword 0x38A100F8
		opword 0x801F01F0
		opword 0xEC1E0028
		opword 0x906100EC
		opword 0x38C10018
		opword 0x811F01F4
		opword 0x386000B1
		opword 0x900100F0
		lwz r12, dat_8041d5d4(r2)
		opword 0xD00100EC
		opword 0x817F01F8
		opword 0xD3E100F0
		opword 0x815F01FC
		opword 0x813F0200
		opword 0x80E100EC
		opword 0x800100F0
		opword 0x91810018
		opword 0x916100F8
		opword 0x914100FC
		opword 0x91210100
		opword 0x910100F4
		opword 0x90E100E0
		opword 0x900100E4
		opword 0x910100E8
		bl winTexSet
		bl winIconInit
		lfs f0, float_30_8041d6fc(r2)
		opword 0x7FC3F378
		opword 0x811F020C
		opword 0x38810104
		opword 0xEC1E0028
		lfs f1, float_6_8041d6f4(r2)
		opword 0x80FF0204
		opword 0x38A1011C
		opword 0x801F0208
		opword 0x38C1001C
		opword 0x90010114
		opword 0xEC01002A
		lwz r12, dat_8041d5d8(r2)
		opword 0x90E10110
		opword 0x817F0210
		opword 0xD0010110
		opword 0x815F0214
		opword 0xD3E10114
		opword 0x813F0218
		opword 0x80E10110
		opword 0x80010114
		opword 0x9181001C
		opword 0x9161011C
		opword 0x91410120
		opword 0x91210124
		opword 0x91010118
		opword 0x90E10104
		opword 0x90010108
		opword 0x9101010C
		bl winIconSet
		opword 0x480001D0
		opword 0x38600003
		bl pouchCheckItem
		opword 0x2C030000
		opword 0x418201C0
		opword 0x807E0028
		lis r4, itemDataTable@ha
		addi r4, r4, itemDataTable@l
		opword 0x806300A0
		opword 0xA3C40098
		opword 0x80630000
		bl winTexInit
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00002
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		lfs f1, float_30_8041d6fc(r2)
		opword 0x38810050
		lfs f0, float_60_8041d700(r2)
		opword 0x38A10068
		opword 0xEC3E0828
		opword 0x811F01DC
		lfs f2, float_5_8041d6cc(r2)
		opword 0xEFE0F82A
		opword 0x807F01D4
		opword 0x38C10008
		opword 0x801F01D8
		opword 0xEC22082A
		opword 0x9061005C
		opword 0xEC1F1028
		lwz r12, dat_8041d5d0(r2)
		opword 0x386000B1
		opword 0x90010060
		opword 0x817F01E0
		opword 0xD021005C
		opword 0x815F01E4
		opword 0xD0010060
		opword 0x813F01E8
		opword 0x80E1005C
		opword 0x80010060
		opword 0x91810008
		opword 0x91610068
		opword 0x9141006C
		opword 0x91210070
		opword 0x91010064
		opword 0x90E10050
		opword 0x90010054
		opword 0x91010058
		bl winTexSet
		lfs f0, float_30_8041d6fc(r2)
		opword 0x38810074
		opword 0x807F01EC
		opword 0x38A1008C
		opword 0x801F01F0
		opword 0xEC1E0028
		opword 0x90610080
		opword 0x38C1000C
		opword 0x811F01F4
		opword 0x386000B1
		opword 0x90010084
		lwz r12, dat_8041d5d4(r2)
		opword 0xD0010080
		opword 0x817F01F8
		opword 0xD3E10084
		opword 0x815F01FC
		opword 0x813F0200
		opword 0x80E10080
		opword 0x80010084
		opword 0x9181000C
		opword 0x9161008C
		opword 0x91410090
		opword 0x91210094
		opword 0x91010088
		opword 0x90E10074
		opword 0x90010078
		opword 0x9101007C
		bl winTexSet
		bl winIconInit
		lfs f0, float_30_8041d6fc(r2)
		opword 0x7FC3F378
		opword 0x811F020C
		opword 0x38810098
		opword 0xEC1E0028
		lfs f1, float_6_8041d6f4(r2)
		opword 0x80FF0204
		opword 0x38A100B0
		opword 0x801F0208
		opword 0x38C10010
		opword 0x900100A8
		opword 0xEC01002A
		lwz r12, dat_8041d5d8(r2)
		opword 0x90E100A4
		opword 0x817F0210
		opword 0xD00100A4
		opword 0x815F0214
		opword 0xD3E100A8
		opword 0x813F0218
		opword 0x80E100A4
		opword 0x800100A8
		opword 0x91810010
		opword 0x916100B0
		opword 0x914100B4
		opword 0x912100B8
		opword 0x910100AC
		opword 0x90E10098
		opword 0x9001009C
		opword 0x910100A0
		bl winIconSet
	}
}
#pragma pop

#pragma defer_codegen off
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void winMarioDisp(s32 camId, void* param, s32 idx) {
#ifdef NONMATCHING
    static s32 pri[6] = {3, 2, 8, 10, 7, 9};
    WinMarioWork* w;
    GXColor white;
    GXColor black;
    PouchData* pouch;
    f32 x;
    f32 y;
    f32 statX;
    f32 rowA;
    f32 rowB;
    f32 cx;
    f32 col;
    f32 nameW;
    f32 row2;
    f32 left;
    f32 row0;
    f32 row1;
    f32 numX;
    f32 costX;
    f32 row3;
    f32 rubyW;
    s32 i;
    s64 secs;
    u64 tsecs;
    s32 hour;
    s32 min;
    AnimData* anim;
    Mtx mtx;
    char buf[0x100];
#endif
#ifndef NONMATCHING
	char _af_pad[6172];
	asm volatile {
		lis r3, str_802F5650@ha
		opword 0x7CB32B78
		opword 0x7C9E2378
		addi r31, r3, str_802F5650@l
		bl pouchGetPtr
		opword 0x1C930014
		lwz r6, dat_8041d5e8(r2)
		lwz r0, dat_8041d5ec(r2)
		opword 0x7C7D1B78
		stw r6, _af_pad+4(r1)
		opword 0x7FC3F378
		opword 0x7CBE2214
		opword 0x90C100D4
		opword 0xC3E500C4
		opword 0x38800000
		opword 0xC3C500C8
		opword 0xFC20F890
		opword 0x90C100DC
		opword 0xFC40F090
		opword 0x90010008
		opword 0x900100D0
		opword 0x900100D8
		bl winBgGX
		lfs f1, float_265_8041d60c(r2)
		opword 0x7FC3F378
		lfs f0, float_154_8041d610(r2)
		opword 0x38800002
		opword 0xEC3F0828
		lfs f3, float_190_8041d614(r2)
		opword 0xEC40F02A
		lfs f4, float_24_8041d618(r2)
		bl winNameGX
		lfs f0, float_265_8041d60c(r2)
		lfs f1, float_10_8041d61c(r2)
		opword 0xEC1F0028
		fadds f18, f1, f0
		bl winFontInit
		lfs f0, float_152_8041d620(r2)
		opword 0x387F0744
		opword 0x809F0264
		opword 0x801F0268
		opword 0xEF20F02A
		opword 0x90810764
		opword 0x80BF026C
		opword 0x90010768
		opword 0x812100D4
		opword 0xD2410764
		opword 0x811F0270
		opword 0xD3210768
		opword 0x80FF0274
		opword 0x80DF0278
		opword 0x80810764
		opword 0x80010768
		opword 0x912100CC
		opword 0x91010758
		opword 0x90E1075C
		opword 0x90C10760
		opword 0x90A1076C
		opword 0x90810770
		opword 0x90010774
		opword 0x90A10778
		bl msgSearch
		opword 0x7C661B78
		opword 0x38610770
		opword 0x38810758
		opword 0x38A100CC
		opword 0x4CC63182
		bl winFontSetEdge
		opword 0x387F0744
		bl msgSearch
		bl FontGetMessageWidth
		opword 0x5463043E
		opword 0x3C004330
		opword 0x9061180C
		opword 0xC87F0820
		opword 0x90011808
		lfs f1, float_0p8_8041d624(r2)
		opword 0xC8411808
		lfs f0, float_20_8041d628(r2)
		opword 0xEC421828
		opword 0xEE4190BA
		opword 0xEE52002A
		bl winIconInit
		lfs f0, float_142_8041d62c(r2)
		opword 0x3881074C
		opword 0x807F027C
		opword 0x38A10734
		opword 0x801F0280
		opword 0xEC00F02A
		opword 0x90610740
		opword 0x38C100C8
		opword 0x811F0284
		opword 0x3860019E
		opword 0x90010744
		opword 0x818100D4
		opword 0xD2410740
		opword 0x817F0288
		opword 0xD0010744
		opword 0x815F028C
		opword 0x813F0290
		opword 0x80E10740
		opword 0x80010744
		opword 0x918100C8
		opword 0x91610734
		opword 0x91410738
		opword 0x9121073C
		opword 0x91010748
		opword 0x90E1074C
		opword 0x90010750
		opword 0x91010754
		bl winIconSet
		lfs f0, float_20_8041d628(r2)
		opword 0xEE52002A
		bl winFontInit
		opword 0x809F0294
		opword 0x387F0750
		opword 0x801F0298
		opword 0x9081071C
		opword 0x80BF029C
		opword 0x90010720
		opword 0x812100D4
		opword 0xD241071C
		opword 0x811F02A0
		opword 0xD3210720
		opword 0x80FF02A4
		opword 0x80DF02A8
		opword 0x8081071C
		opword 0x80010720
		opword 0x912100C4
		opword 0x91010710
		opword 0x90E10714
		opword 0x90C10718
		opword 0x90A10724
		opword 0x90810728
		opword 0x9001072C
		opword 0x90A10730
		bl msgSearch
		opword 0x7C661B78
		opword 0x38610728
		opword 0x38810710
		opword 0x38A100C4
		opword 0x4CC63182
		bl winFontSetEdge
		opword 0xAB5D008A
		opword 0x817F0184
		opword 0x815F0188
		opword 0x2C1A0000
		opword 0x813F018C
		opword 0x811F0190
		opword 0x80FF0194
		opword 0x80DF0198
		opword 0x80BF019C
		opword 0x809F01A0
		opword 0x807F01A4
		opword 0x801F01A8
		opword 0x916109AC
		opword 0x914109B0
		opword 0x912109B4
		opword 0x910109B8
		opword 0x90E109BC
		opword 0x90C109C0
		opword 0x90A109C4
		opword 0x908109C8
		opword 0x906109CC
		opword 0x900109D0
		opword 0x4080001C
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, str_8041D630(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F5A00D0
		opword 0x48000014
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, float_0_8041d634(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F45D378
		opword 0x38611604
		la r4, str_8041D638(r2)
		opword 0x4CC63182
		bl sprintf
		lis r3, (unk_803dfbf8+0x100)@ha
		opword 0x3AC11604
		addi r20, r3, (unk_803dfbf8+0x100)@l
		opword 0x3A6109AC
		opword 0x3AA00000
		opword 0x48000028
		opword 0x88160000
		opword 0x7E83A378
		opword 0x7C000774
		opword 0x5404103A
		opword 0x3804FF40
		opword 0x7C93002E
		bl strcat
		opword 0x3AD60001
		opword 0x3AB50001
		opword 0x38611604
		bl strlen
		opword 0x7C151840
		opword 0x4180FFD0
		lis r4, (unk_803dfbf8+0x100)@ha
		opword 0x38611704
		addi r5, r4, (unk_803dfbf8+0x100)@l
		la r4, str_8041D63C(r2)
		opword 0x4CC63182
		bl sprintf
		bl winFontInit
		opword 0x812100D4
		opword 0x38611704
		opword 0x811F02B8
		opword 0x80FF02BC
		opword 0x80DF02C0
		opword 0x80BF02AC
		opword 0x809F02B0
		opword 0x801F02B4
		opword 0x912100C0
		opword 0x910106EC
		opword 0x90E106F0
		opword 0x90C106F4
		opword 0x90A106F8
		opword 0x908106FC
		opword 0x90010700
		bl FontGetMessageWidth
		opword 0x5463043E
		lfs f0, float_265_8041d60c(r2)
		opword 0x3C004330
		opword 0x9061180C
		opword 0xEC1F0028
		lfs f1, float_190_8041d614(r2)
		opword 0x90011808
		opword 0x38610704
		opword 0xC89F0820
		opword 0x388106EC
		opword 0xC8611808
		opword 0xEC21002A
		lfs f2, float_0p8_8041d624(r2)
		opword 0x38A100C0
		opword 0xEC632028
		opword 0xD32106FC
		lfs f0, float_10_8041d61c(r2)
		opword 0x80E106FC
		opword 0x38C11704
		opword 0xEC2208FC
		opword 0x80010700
		opword 0x90E10708
		opword 0xEC010028
		opword 0x9001070C
		opword 0xD00106F8
		opword 0x800106F8
		opword 0x90010704
		opword 0x4CC63182
		bl winFontSetEdge
		opword 0x807E0028
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit
		lfs f1, float_255_8041d640(r2)
		opword 0x388106E0
		lfs f0, float_112_8041d644(r2)
		opword 0x38A106C8
		opword 0x807F02C4
		opword 0xEC3F0828
		opword 0x801F02C8
		opword 0xEC00F02A
		opword 0x906106D4
		opword 0x38C100BC
		opword 0x811F02CC
		opword 0x900106D8
		opword 0x386000B0
		opword 0x818100D4
		opword 0xD02106D4
		opword 0x817F02D0
		opword 0xD00106D8
		opword 0x815F02D4
		opword 0x813F02D8
		opword 0x80E106D4
		opword 0x800106D8
		opword 0x918100BC
		opword 0x916106C8
		opword 0x914106CC
		opword 0x912106D0
		opword 0x910106DC
		opword 0x90E106E0
		opword 0x900106E4
		opword 0x910106E8
		bl winTexSet
		bl winFontInit
		lfs f1, float_240_8041d648(r2)
		lfs f0, float_124_8041d64c(r2)
		opword 0x807F02DC
		opword 0xEC3F0828
		opword 0x801F02E0
		opword 0xEC00F02A
		opword 0x906106B0
		opword 0x809F02E4
		opword 0x900106B4
		opword 0x810100D0
		opword 0xD02106B0
		opword 0x80FF02E8
		opword 0xD00106B4
		opword 0x80DF02EC
		opword 0x80BF02F0
		opword 0x806106B0
		opword 0x800106B4
		opword 0x910100B8
		opword 0x90E106A4
		opword 0x90C106A8
		opword 0x90A106AC
		opword 0x906106BC
		opword 0x900106C0
		opword 0x908106C4
		opword 0x908106B8
		opword 0xA87D008A
		bl BattleGetRankNameLabel
		bl msgSearch
		opword 0x7C661B78
		opword 0x386106BC
		opword 0x388106A4
		opword 0x38A100B8
		opword 0x4CC63182
		bl winFontSet
		opword 0x3A800000
		la r19, g5_pri_s896(r13)
		opword 0x801E0160
		opword 0x80930000
		opword 0x7C002000
		opword 0x41820014
		opword 0xFC20F890
		opword 0x7FC3F378
		opword 0xFC40F090
		bl fukidashi
		opword 0x3A940001
		opword 0x3A730004
		opword 0x2C140006
		opword 0x4180FFD4
		opword 0xFC20F890
		opword 0x809E0160
		opword 0xFC40F090
		opword 0x7FC3F378
		bl fukidashi
		lfs f1, float_270_8041d650(r2)
		opword 0x7FC3F378
		lfs f0, float_10_8041d61c(r2)
		opword 0x38800000
		opword 0xEC3F0828
		lfs f3, float_264_8041d654(r2)
		opword 0xEC5E0028
		lfs f4, float_110_8041d658(r2)
		bl winKirinukiGX
		lfs f1, float_270_8041d650(r2)
		opword 0x3A800000
		lfs f0, float_38_8041d668(r2)
		opword 0x7E96A378
		opword 0xEC5F0828
		lfs f3, float_50_8041d65c(r2)
		lfs f1, float_2_8041d660(r2)
		opword 0xEF9E0028
		opword 0xCB5F0820
		opword 0x3B210788
		opword 0xEF03102A
		lfs f27, float_0p5_8041d664(r2)
		opword 0xCBBF0828
		opword 0x3B01077C
		lfs f19, float_4_8041d66c(r2)
		opword 0x3AE107A0
		opword 0xEF380828
		opword 0x834100D8
		lfs f20, float_12_8041d670(r2)
		opword 0x3AA10794
		lfs f21, float_21_8041d674(r2)
		opword 0x3F604330
		opword 0x80FF030C
		opword 0x80DF0310
		opword 0x807F0314
		opword 0x827F02F4
		opword 0x819F02F8
		opword 0x817F02FC
		opword 0x815F0300
		opword 0x813F0304
		opword 0x811F0308
		opword 0x80BF0360
		opword 0x809F0364
		opword 0x801F0368
		opword 0x90E10788
		opword 0x90C1078C
		opword 0x90610790
		opword 0x926107A0
		opword 0x80790000
		opword 0x918107A4
		opword 0x916107A8
		opword 0x91410794
		opword 0x91210798
		opword 0x9101079C
		opword 0x90A1077C
		opword 0x90810780
		opword 0x90010784
		bl FontGetMessageWidth
		opword 0x5460043E
		opword 0x93611808
		opword 0x80780000
		opword 0x9001180C
		opword 0xC8011808
		opword 0xEEE0D028
		bl msgSearch
		bl FontGetMessageWidth
		opword 0x5460043E
		opword 0x807E0028
		opword 0x90011814
		opword 0x806300A0
		opword 0x93611810
		opword 0x80630000
		opword 0xC8011810
		opword 0xEC00D028
		opword 0xEEDB0032
		bl winTexInit
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00002
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x6EC08000
		opword 0x811F0374
		opword 0x9001181C
		opword 0x38810698
		opword 0x80FF036C
		opword 0x38A10680
		opword 0x93611818
		opword 0x38C100B4
		opword 0x801F0370
		opword 0x386000AF
		opword 0xC8011818
		opword 0x90E1068C
		opword 0xEC00E828
		opword 0x81970000
		opword 0xD321068C
		opword 0x817F0378
		opword 0xEE5C0028
		opword 0x815F037C
		opword 0x813F0380
		opword 0x90010690
		opword 0xEC129828
		opword 0x80E1068C
		opword 0x918100B4
		opword 0xD0010690
		opword 0x80010690
		opword 0x91610680
		opword 0x91410684
		opword 0x91210688
		opword 0x91010694
		opword 0x90E10698
		opword 0x9001069C
		opword 0x910106A0
		bl winTexSet
		bl winFontInit
		opword 0x807F0384
		opword 0xEC37C6FC
		opword 0x801F0388
		opword 0xEC14902A
		opword 0x90610668
		opword 0x38610674
		opword 0x811F038C
		opword 0x9001066C
		opword 0x3881065C
		opword 0x817F0390
		opword 0x38A100B0
		opword 0xD0210668
		opword 0x815F0394
		opword 0xD001066C
		opword 0x813F0398
		opword 0x80E10668
		opword 0x8001066C
		opword 0x934100B0
		opword 0x80D90000
		opword 0x9161065C
		opword 0x91410660
		opword 0x91210664
		opword 0x91010670
		opword 0x90E10674
		opword 0x90010678
		opword 0x9101067C
		opword 0x4CC63182
		bl winFontSet
		opword 0x807F039C
		opword 0xEC36C6FC
		opword 0x801F03A0
		opword 0xEC15902A
		opword 0x90610644
		opword 0x80BF03A4
		opword 0x90010648
		opword 0x80750000
		opword 0xD0210644
		opword 0x811F03A8
		opword 0xD0010648
		opword 0x80FF03AC
		opword 0x80DF03B0
		opword 0x80810644
		opword 0x80010648
		opword 0x906100AC
		opword 0x80780000
		opword 0x91010638
		opword 0x90E1063C
		opword 0x90C10640
		opword 0x90A1064C
		opword 0x90810650
		opword 0x90010654
		opword 0x90A10658
		bl msgSearch
		opword 0x7C661B78
		opword 0x38610650
		opword 0x38810638
		opword 0x38A100AC
		opword 0x4CC63182
		bl winFontSet
		opword 0x3A940001
		opword 0x3B180004
		opword 0x2C140003
		opword 0x3AF70004
		opword 0x3AD60022
		opword 0x3AB50004
		opword 0x3B390004
		opword 0x4180FD90
		bl winIconInit
		lfs f1, float_270_8041d650(r2)
		opword 0x3881062C
		lfs f0, float_38_8041d668(r2)
		opword 0x38A10614
		opword 0xEC5F0828
		opword 0x811F03BC
		lfs f3, float_110_8041d658(r2)
		opword 0xEC1E0028
		lfs f1, float_4_8041d66c(r2)
		opword 0x38C100A8
		opword 0x807F03B4
		opword 0xEE43102A
		opword 0x801F03B8
		opword 0xEF41002A
		opword 0x90610620
		opword 0x3860019F
		opword 0x818100D4
		opword 0x90010624
		opword 0x817F03C0
		opword 0xD2410620
		opword 0x815F03C4
		opword 0xD3410624
		opword 0x813F03C8
		opword 0x80E10620
		opword 0x80010624
		opword 0x918100A8
		opword 0x91610614
		opword 0x91410618
		opword 0x9121061C
		opword 0x91010628
		opword 0x90E1062C
		opword 0x90010630
		opword 0x91010634
		bl winIconSet
		lfs f0, float_38_8041d668(r2)
		opword 0x38810608
		opword 0x811F03D4
		opword 0x38A105F0
		opword 0xEC3E0028
		lfs f0, float_34_8041d678(r2)
		opword 0x80FF03CC
		opword 0x38C100A4
		opword 0x801F03D0
		opword 0x386001A0
		opword 0xEF010028
		lfs f0, float_4_8041d66c(r2)
		opword 0x90E105FC
		opword 0x818100D4
		opword 0xEF60C02A
		opword 0x90010600
		opword 0x817F03D8
		opword 0xD24105FC
		opword 0x815F03DC
		opword 0xD3610600
		opword 0x813F03E0
		opword 0x80E105FC
		opword 0x80010600
		opword 0x918100A4
		opword 0x916105F0
		opword 0x914105F4
		opword 0x912105F8
		opword 0x91010604
		opword 0x90E10608
		opword 0x9001060C
		opword 0x91010610
		bl winIconSet
		lfs f0, float_38_8041d668(r2)
		opword 0x388105E4
		opword 0x811F03EC
		opword 0x38A105CC
		opword 0xEC3E0028
		lfs f0, float_68_8041d67c(r2)
		opword 0x80FF03E4
		opword 0x38C100A0
		opword 0x801F03E8
		opword 0x386001A1
		opword 0xEF210028
		lfs f0, float_4_8041d66c(r2)
		opword 0x90E105D8
		opword 0x818100D4
		opword 0xEC00C82A
		opword 0x900105DC
		opword 0x817F03F0
		opword 0xD24105D8
		opword 0x815F03F4
		opword 0xD00105DC
		opword 0x813F03F8
		opword 0x80E105D8
		opword 0x800105DC
		opword 0x918100A0
		opword 0x916105CC
		opword 0x914105D0
		opword 0x912105D4
		opword 0x910105E0
		opword 0x90E105E4
		opword 0x900105E8
		opword 0x910105EC
		bl winIconSet
		bl winFontInit
		lfs f0, float_38_8041d668(r2)
		opword 0x833F0404
		opword 0xEC1E0028
		lfs f2, float_270_8041d650(r2)
		lfs f1, float_12_8041d670(r2)
		opword 0x807F03FC
		opword 0xEC5F1028
		opword 0xEC01002A
		lfs f3, float_130_8041d680(r2)
		lfs f1, float_4_8041d66c(r2)
		opword 0x801F0400
		opword 0xEE43102A
		opword 0x906105B4
		opword 0xEF81002A
		opword 0x82DF0408
		opword 0x900105B8
		opword 0x82BF040C
		opword 0xD24105B4
		opword 0x829F0410
		opword 0xD38105B8
		opword 0x830105B4
		opword 0x82E105B8
		opword 0x818100D0
		opword 0x817F0184
		opword 0x815F0188
		opword 0x813F018C
		opword 0x811F0190
		opword 0x80FF0194
		opword 0x80DF0198
		opword 0x80BF019C
		opword 0x809F01A0
		opword 0x807F01A4
		opword 0x801F01A8
		opword 0x930105C0
		opword 0x92E105C4
		opword 0x932105C8
		opword 0x92C105A8
		opword 0x92A105AC
		opword 0x928105B0
		opword 0x9181009C
		opword 0xAB5D0070
		opword 0x932105BC
		opword 0x2C1A0000
		opword 0x91610984
		opword 0x91410988
		opword 0x9121098C
		opword 0x91010990
		opword 0x90E10994
		opword 0x90C10998
		opword 0x90A1099C
		opword 0x908109A0
		opword 0x906109A4
		opword 0x900109A8
		opword 0x4080001C
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, str_8041D630(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F5A00D0
		opword 0x48000014
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, float_0_8041d634(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F45D378
		opword 0x38611504
		la r4, str_8041D638(r2)
		opword 0x4CC63182
		bl sprintf
		lis r3, (unk_803dfbf8+0x100)@ha
		opword 0x3AC11504
		addi r21, r3, (unk_803dfbf8+0x100)@l
		opword 0x3A810984
		opword 0x3A600000
		opword 0x48000028
		opword 0x88160000
		opword 0x7EA3AB78
		opword 0x7C000774
		opword 0x5404103A
		opword 0x3804FF40
		opword 0x7C94002E
		bl strcat
		opword 0x3AD60001
		opword 0x3A730001
		opword 0x38611504
		bl strlen
		opword 0x7C131840
		opword 0x4180FFD0
		lis r4, (unk_803dfbf8+0x100)@ha
		opword 0x386105C0
		addi r7, r4, (unk_803dfbf8+0x100)@l
		opword 0x38A1009C
		opword 0x388105A8
		la r6, str_8041D63C(r2)
		opword 0x4CC63182
		bl winFontSetR
		lfs f0, float_12_8041d670(r2)
		opword 0x833F041C
		opword 0xEC00C02A
		lfs f1, float_4_8041d66c(r2)
		opword 0x807F0414
		opword 0x801F0418
		opword 0xEF01002A
		opword 0x90610590
		opword 0x82DF0420
		opword 0x90010594
		opword 0x82BF0424
		opword 0xD2410590
		opword 0x829F0428
		opword 0xD3010594
		opword 0x83010590
		opword 0x82E10594
		opword 0x818100D0
		opword 0x817F0184
		opword 0x815F0188
		opword 0x813F018C
		opword 0x811F0190
		opword 0x80FF0194
		opword 0x80DF0198
		opword 0x80BF019C
		opword 0x809F01A0
		opword 0x807F01A4
		opword 0x801F01A8
		opword 0x9301059C
		opword 0x92E105A0
		opword 0x932105A4
		opword 0x92C10584
		opword 0x92A10588
		opword 0x9281058C
		opword 0x91810098
		opword 0xAB5D0074
		opword 0x93210598
		opword 0x2C1A0000
		opword 0x9161095C
		opword 0x91410960
		opword 0x91210964
		opword 0x91010968
		opword 0x90E1096C
		opword 0x90C10970
		opword 0x90A10974
		opword 0x90810978
		opword 0x9061097C
		opword 0x90010980
		opword 0x4080001C
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, str_8041D630(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F5A00D0
		opword 0x48000014
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, float_0_8041d634(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F45D378
		opword 0x38611404
		la r4, str_8041D638(r2)
		opword 0x4CC63182
		bl sprintf
		lis r3, (unk_803dfbf8+0x100)@ha
		opword 0x3AC11404
		addi r21, r3, (unk_803dfbf8+0x100)@l
		opword 0x3A81095C
		opword 0x3A600000
		opword 0x48000028
		opword 0x88160000
		opword 0x7EA3AB78
		opword 0x7C000774
		opword 0x5404103A
		opword 0x3804FF40
		opword 0x7C94002E
		bl strcat
		opword 0x3AD60001
		opword 0x3A730001
		opword 0x38611404
		bl strlen
		opword 0x7C131840
		opword 0x4180FFD0
		lis r4, (unk_803dfbf8+0x100)@ha
		opword 0x3861059C
		addi r7, r4, (unk_803dfbf8+0x100)@l
		opword 0x38A10098
		opword 0x38810584
		la r6, str_8041D63C(r2)
		opword 0x4CC63182
		bl winFontSetR
		lfs f0, float_12_8041d670(r2)
		opword 0x833F0434
		opword 0xEC00C82A
		lfs f1, float_4_8041d66c(r2)
		opword 0x807F042C
		opword 0x801F0430
		opword 0xEC01002A
		opword 0x9061056C
		opword 0x82DF0438
		opword 0x90010570
		opword 0x82BF043C
		opword 0xD241056C
		opword 0x829F0440
		opword 0xD0010570
		opword 0x8301056C
		opword 0x82E10570
		opword 0x818100D0
		opword 0x817F0184
		opword 0x815F0188
		opword 0x813F018C
		opword 0x811F0190
		opword 0x80FF0194
		opword 0x80DF0198
		opword 0x80BF019C
		opword 0x809F01A0
		opword 0x807F01A4
		opword 0x801F01A8
		opword 0x93010578
		opword 0x92E1057C
		opword 0x93210580
		opword 0x92C10560
		opword 0x92A10564
		opword 0x92810568
		opword 0x91810094
		opword 0xAB5D0094
		opword 0x93210574
		opword 0x2C1A0000
		opword 0x91610934
		opword 0x91410938
		opword 0x9121093C
		opword 0x91010940
		opword 0x90E10944
		opword 0x90C10948
		opword 0x90A1094C
		opword 0x90810950
		opword 0x90610954
		opword 0x90010958
		opword 0x4080001C
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, str_8041D630(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F5A00D0
		opword 0x48000014
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, float_0_8041d634(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F45D378
		opword 0x38611304
		la r4, str_8041D638(r2)
		opword 0x4CC63182
		bl sprintf
		lis r3, (unk_803dfbf8+0x100)@ha
		opword 0x3AC11304
		addi r21, r3, (unk_803dfbf8+0x100)@l
		opword 0x3A810934
		opword 0x3A600000
		opword 0x48000028
		opword 0x88160000
		opword 0x7EA3AB78
		opword 0x7C000774
		opword 0x5404103A
		opword 0x3804FF40
		opword 0x7C94002E
		bl strcat
		opword 0x3AD60001
		opword 0x3A730001
		opword 0x38611304
		bl strlen
		opword 0x7C131840
		opword 0x4180FFD0
		lis r4, (unk_803dfbf8+0x100)@ha
		opword 0x38610578
		addi r7, r4, (unk_803dfbf8+0x100)@l
		opword 0x38A10094
		opword 0x38810560
		la r6, str_8041D63C(r2)
		opword 0x4CC63182
		bl winFontSetR
		opword 0x807E0028
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit
		lfs f0, float_270_8041d650(r2)
		opword 0x38810554
		opword 0x811F044C
		opword 0x38A1053C
		opword 0xEC1F0028
		lfs f1, float_190_8041d614(r2)
		opword 0x80FF0444
		opword 0x38C10090
		opword 0x801F0448
		opword 0x38600010
		opword 0x9001054C
		opword 0xEE41002A
		opword 0x818100D4
		opword 0x90E10548
		opword 0x817F0450
		opword 0xD2410548
		opword 0x815F0454
		opword 0xD341054C
		opword 0x813F0458
		opword 0x80E10548
		opword 0x8001054C
		opword 0x91810090
		opword 0x9161053C
		opword 0x91410540
		opword 0x91210544
		opword 0x91010550
		opword 0x90E10554
		opword 0x90010558
		opword 0x9101055C
		bl winTexSet
		opword 0x807F045C
		opword 0x38810530
		opword 0x801F0460
		opword 0x38A10518
		opword 0x90610524
		opword 0x38C1008C
		opword 0x811F0464
		opword 0x38600010
		opword 0x90010528
		opword 0x818100D4
		opword 0xD2410524
		opword 0x817F0468
		opword 0xD3610528
		opword 0x815F046C
		opword 0x813F0470
		opword 0x80E10524
		opword 0x80010528
		opword 0x9181008C
		opword 0x91610518
		opword 0x9141051C
		opword 0x91210520
		opword 0x9101052C
		opword 0x90E10530
		opword 0x90010534
		opword 0x91010538
		bl winTexSet
		bl winFontInit
		lfs f0, float_270_8041d650(r2)
		opword 0x833F047C
		opword 0xEC1F0028
		lfs f1, float_200_8041d684(r2)
		opword 0x807F0474
		opword 0x801F0478
		opword 0xEE41002A
		opword 0x90610500
		opword 0x82DF0480
		opword 0x90010504
		opword 0x82BF0484
		opword 0xD2410500
		opword 0x829F0488
		opword 0xD3810504
		opword 0x83010500
		opword 0x82E10504
		opword 0x818100D0
		opword 0x817F0184
		opword 0x815F0188
		opword 0x813F018C
		opword 0x811F0190
		opword 0x80FF0194
		opword 0x80DF0198
		opword 0x80BF019C
		opword 0x809F01A0
		opword 0x807F01A4
		opword 0x801F01A8
		opword 0x9301050C
		opword 0x92E10510
		opword 0x93210514
		opword 0x92C104F4
		opword 0x92A104F8
		opword 0x928104FC
		opword 0x91810088
		opword 0xAB5D0072
		opword 0x93210508
		opword 0x2C1A0000
		opword 0x9161090C
		opword 0x91410910
		opword 0x91210914
		opword 0x91010918
		opword 0x90E1091C
		opword 0x90C10920
		opword 0x90A10924
		opword 0x90810928
		opword 0x9061092C
		opword 0x90010930
		opword 0x4080001C
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, str_8041D630(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F5A00D0
		opword 0x48000014
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, float_0_8041d634(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F45D378
		opword 0x38611204
		la r4, str_8041D638(r2)
		opword 0x4CC63182
		bl sprintf
		lis r3, (unk_803dfbf8+0x100)@ha
		opword 0x3AC11204
		addi r21, r3, (unk_803dfbf8+0x100)@l
		opword 0x3A81090C
		opword 0x3A600000
		opword 0x48000028
		opword 0x88160000
		opword 0x7EA3AB78
		opword 0x7C000774
		opword 0x5404103A
		opword 0x3804FF40
		opword 0x7C94002E
		bl strcat
		opword 0x3AD60001
		opword 0x3A730001
		opword 0x38611204
		bl strlen
		opword 0x7C131840
		opword 0x4180FFD0
		lis r4, (unk_803dfbf8+0x100)@ha
		opword 0x3861050C
		addi r7, r4, (unk_803dfbf8+0x100)@l
		opword 0x38A10088
		opword 0x388104F4
		la r6, str_8041D63C(r2)
		opword 0x4CC63182
		bl winFontSet
		opword 0x807F048C
		opword 0x801F0490
		opword 0x906104DC
		opword 0x833F0494
		opword 0x900104E0
		opword 0x82DF0498
		opword 0xD24104DC
		opword 0x82BF049C
		opword 0xD30104E0
		opword 0x830104DC
		opword 0x82E104E0
		opword 0x829F04A0
		opword 0x818100D0
		opword 0x817F0184
		opword 0x815F0188
		opword 0x813F018C
		opword 0x811F0190
		opword 0x80FF0194
		opword 0x80DF0198
		opword 0x80BF019C
		opword 0x809F01A0
		opword 0x807F01A4
		opword 0x801F01A8
		opword 0x930104E8
		opword 0x92E104EC
		opword 0x932104F0
		opword 0x92C104D0
		opword 0x92A104D4
		opword 0x928104D8
		opword 0x91810084
		opword 0xAB5D0076
		opword 0x932104E4
		opword 0x2C1A0000
		opword 0x916108E4
		opword 0x914108E8
		opword 0x912108EC
		opword 0x910108F0
		opword 0x90E108F4
		opword 0x90C108F8
		opword 0x90A108FC
		opword 0x90810900
		opword 0x90610904
		opword 0x90010908
		opword 0x4080001C
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, str_8041D630(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F5A00D0
		opword 0x48000014
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, float_0_8041d634(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F45D378
		opword 0x38611104
		la r4, str_8041D638(r2)
		opword 0x4CC63182
		bl sprintf
		lis r3, (unk_803dfbf8+0x100)@ha
		opword 0x3AC11104
		addi r21, r3, (unk_803dfbf8+0x100)@l
		opword 0x3A8108E4
		opword 0x3A600000
		opword 0x48000028
		opword 0x88160000
		opword 0x7EA3AB78
		opword 0x7C000774
		opword 0x5404103A
		opword 0x3804FF40
		opword 0x7C94002E
		bl strcat
		opword 0x3AD60001
		opword 0x3A730001
		opword 0x38611104
		bl strlen
		opword 0x7C131840
		opword 0x4180FFD0
		lis r4, (unk_803dfbf8+0x100)@ha
		opword 0x386104E8
		addi r7, r4, (unk_803dfbf8+0x100)@l
		opword 0x38A10084
		opword 0x388104D0
		la r6, str_8041D63C(r2)
		opword 0x4CC63182
		bl winFontSet
		opword 0x801E0198
		opword 0x2C000000
		opword 0x40810320
		lfs f0, float_130_8041d680(r2)
		opword 0x7FC3F378
		lfs f1, float_10_8041d61c(r2)
		opword 0x38800000
		opword 0xEC00F02A
		lfs f2, float_20_8041d628(r2)
		opword 0xEC21F82A
		lfs f3, float_260_8041d688(r2)
		lfs f4, float_80_8041d68c(r2)
		opword 0xEC02002A
		opword 0xEC401028
		bl winKirinukiGX
		bl winIconInit
		lfs f0, float_40_8041d690(r2)
		opword 0x388104C4
		opword 0x811F04AC
		opword 0x38A104AC
		opword 0xEC20F82A
		lfs f2, float_10_8041d61c(r2)
		lfs f0, float_106_8041d694(r2)
		opword 0x38C10080
		opword 0x80FF04A4
		opword 0x3860020F
		opword 0x801F04A8
		opword 0xEE42082A
		opword 0x90E104B8
		opword 0xEF00F02A
		opword 0x818100D4
		opword 0x900104BC
		opword 0x817F04B0
		opword 0xD24104B8
		opword 0x815F04B4
		opword 0xD30104BC
		opword 0x813F04B8
		opword 0x80E104B8
		opword 0x800104BC
		opword 0x91810080
		opword 0x916104AC
		opword 0x914104B0
		opword 0x912104B4
		opword 0x910104C0
		opword 0x90E104C4
		opword 0x900104C8
		opword 0x910104CC
		bl winIconSet
		lfs f0, float_70_8041d698(r2)
		opword 0x388104A0
		opword 0x807F04BC
		opword 0x38A10488
		opword 0x801F04C0
		opword 0xEE60F02A
		opword 0x90610494
		opword 0x38C1007C
		opword 0x811F04C4
		opword 0x38600197
		opword 0x90010498
		opword 0x818100D4
		opword 0xD2410494
		opword 0x817F04C8
		opword 0xD2610498
		opword 0x815F04CC
		opword 0x813F04D0
		opword 0x80E10494
		opword 0x80010498
		opword 0x9181007C
		opword 0x91610488
		opword 0x9141048C
		opword 0x91210490
		opword 0x9101049C
		opword 0x90E104A0
		opword 0x900104A4
		opword 0x910104A8
		bl winIconSet
		bl winFontInit
		lfs f0, float_70_8041d698(r2)
		opword 0x387F0768
		opword 0x80BF04DC
		opword 0xEC20F82A
		lfs f2, float_10_8041d61c(r2)
		opword 0x809F04D4
		opword 0x801F04D8
		opword 0xEC02982A
		opword 0xEC22082A
		opword 0x90810470
		opword 0x812100D0
		opword 0x90010474
		opword 0x811F04E0
		opword 0xD0210470
		opword 0x80FF04E4
		opword 0xD0010474
		opword 0x80DF04E8
		opword 0x80810470
		opword 0x80010474
		opword 0x91210078
		opword 0x91010464
		opword 0x90E10468
		opword 0x90C1046C
		opword 0x90A10478
		opword 0x9081047C
		opword 0x90010480
		opword 0x90A10484
		bl msgSearch
		opword 0x7C661B78
		opword 0x3861047C
		opword 0x38810464
		opword 0x38A10078
		opword 0x4CC63182
		bl winFontSet
		bl winIconInit
		lfs f0, float_80_8041d68c(r2)
		opword 0x3AC00000
		opword 0x3C6051EC
		lfs f1, float_10_8041d61c(r2)
		opword 0xEC00F82A
		opword 0x7ED5B378
		opword 0x3B43851F
		opword 0xEE61002A
		opword 0x4800013C
		opword 0xA81D007A
		opword 0x7C1A0096
		opword 0x7C002E70
		opword 0x54030FFE
		opword 0x7C001A14
		opword 0x7C160000
		opword 0x40800090
		opword 0x6EA38000
		opword 0x3C004330
		opword 0x9061181C
		opword 0x387601B7
		opword 0x811F04F4
		opword 0x38810458
		opword 0x90011818
		opword 0x38A10440
		opword 0xC83F0828
		opword 0x38C10074
		opword 0xC8011818
		opword 0x80FF04EC
		opword 0xEC000828
		opword 0x801F04F0
		opword 0x818100DC
		opword 0x90010450
		opword 0xEC13002A
		opword 0x817F04F8
		opword 0x90E1044C
		opword 0x815F04FC
		opword 0xD001044C
		opword 0x813F0500
		opword 0xD3010450
		opword 0x80E1044C
		opword 0x80010450
		opword 0x91810074
		opword 0x91610440
		opword 0x91410444
		opword 0x91210448
		opword 0x91010454
		opword 0x90E10458
		opword 0x9001045C
		opword 0x91010460
		bl winIconSet
		opword 0x4800008C
		opword 0x6EA38000
		opword 0x3C004330
		opword 0x9061181C
		opword 0x38810434
		opword 0x811F050C
		opword 0x38A1041C
		opword 0x90011818
		opword 0x38C10070
		opword 0xC83F0828
		opword 0x386001BF
		opword 0xC8011818
		opword 0x80FF0504
		opword 0xEC000828
		opword 0x801F0508
		opword 0x818100DC
		opword 0x9001042C
		opword 0xEC13002A
		opword 0x817F0510
		opword 0x90E10428
		opword 0x815F0514
		opword 0xD0010428
		opword 0x813F0518
		opword 0xD301042C
		opword 0x80E10428
		opword 0x8001042C
		opword 0x91810070
		opword 0x9161041C
		opword 0x91410420
		opword 0x91210424
		opword 0x91010430
		opword 0x90E10434
		opword 0x90010438
		opword 0x9101043C
		bl winIconSet
		opword 0x3AB50016
		opword 0x3AD60001
		opword 0x801E0198
		opword 0x7C160000
		opword 0x4180FEC0
		lfs f2, float_10_8041d61c(r2)
		opword 0x7FC3F378
		lfs f0, float_20_8041d628(r2)
		opword 0x38800000
		opword 0xEEE2F82A
		lfs f3, float_260_8041d688(r2)
		opword 0xEC00F02A
		lfs f4, float_150_8041d69c(r2)
		opword 0xFC20B890
		opword 0xEC42002A
		bl winKirinukiGX
		bl winIconInit
		lfs f0, float_20_8041d628(r2)
		opword 0x38810410
		opword 0x811F0524
		opword 0x38A103F8
		opword 0xEC20F82A
		lfs f2, float_10_8041d61c(r2)
		opword 0x80FF051C
		opword 0x38C1006C
		opword 0x801F0520
		opword 0xEC02F02A
		opword 0x90010408
		opword 0xEF02082A
		opword 0x818100D4
		opword 0x3860018C
		opword 0x90E10404
		opword 0x817F0528
		opword 0xD3010404
		opword 0x815F052C
		opword 0xD0010408
		opword 0x813F0530
		opword 0x80E10404
		opword 0x80010408
		opword 0x9181006C
		opword 0x916103F8
		opword 0x914103FC
		opword 0x91210400
		opword 0x9101040C
		opword 0x90E10410
		opword 0x90010414
		opword 0x91010418
		bl winIconSet
		lfs f0, float_28_8041d6a0(r2)
		opword 0x388103EC
		opword 0x811F053C
		opword 0x38A103D4
		opword 0xEC1E0028
		lfs f1, float_10_8041d61c(r2)
		opword 0x80FF0534
		opword 0x38C10068
		opword 0x801F0538
		opword 0x3860018B
		opword 0x90E103E0
		opword 0xEC01002A
		opword 0x818100D4
		opword 0x900103E4
		opword 0x817F0540
		opword 0xD30103E0
		opword 0x815F0544
		opword 0xD00103E4
		opword 0x813F0548
		opword 0x80E103E0
		opword 0x800103E4
		opword 0x91810068
		opword 0x916103D4
		opword 0x914103D8
		opword 0x912103DC
		opword 0x910103E8
		opword 0x90E103EC
		opword 0x900103F0
		opword 0x910103F4
		bl winIconSet
		lfs f0, float_56_8041d6a4(r2)
		opword 0x388103C8
		opword 0x811F0554
		opword 0x38A103B0
		opword 0xEC1E0028
		lfs f1, float_10_8041d61c(r2)
		opword 0x80FF054C
		opword 0x38C10064
		opword 0x801F0550
		opword 0x3860018D
		opword 0x90E103BC
		opword 0xEC01002A
		opword 0x818100D4
		opword 0x900103C0
		opword 0x817F0558
		opword 0xD30103BC
		opword 0x815F055C
		opword 0xD00103C0
		opword 0x813F0560
		opword 0x80E103BC
		opword 0x800103C0
		opword 0x91810064
		opword 0x916103B0
		opword 0x914103B4
		opword 0x912103B8
		opword 0x910103C4
		opword 0x90E103C8
		opword 0x900103CC
		opword 0x910103D0
		bl winIconSet
		lfs f0, float_84_8041d6a8(r2)
		opword 0x388103A4
		opword 0x811F056C
		opword 0x38A1038C
		opword 0xEC1E0028
		lfs f1, float_10_8041d61c(r2)
		opword 0x80FF0564
		opword 0x38C10060
		opword 0x801F0568
		opword 0x38600102
		opword 0x90E10398
		opword 0xEC01002A
		opword 0x818100D4
		opword 0x9001039C
		opword 0x817F0570
		opword 0xD3010398
		opword 0x815F0574
		opword 0xD001039C
		opword 0x813F0578
		opword 0x80E10398
		opword 0x8001039C
		opword 0x91810060
		opword 0x9161038C
		opword 0x91410390
		opword 0x91210394
		opword 0x910103A0
		opword 0x90E103A4
		opword 0x900103A8
		opword 0x910103AC
		bl winIconSet
		lfs f0, float_112_8041d644(r2)
		opword 0x38810380
		opword 0x811F0584
		opword 0x38A10368
		opword 0xEC1E0028
		lfs f1, float_10_8041d61c(r2)
		opword 0x80FF057C
		opword 0x38C1005C
		opword 0x801F0580
		opword 0x386001A2
		opword 0x90E10374
		opword 0xEC01002A
		opword 0x818100D4
		opword 0x90010378
		opword 0x817F0588
		opword 0xD3010374
		opword 0x815F058C
		opword 0xD0010378
		opword 0x813F0590
		opword 0x80E10374
		opword 0x80010378
		opword 0x9181005C
		opword 0x91610368
		opword 0x9141036C
		opword 0x91210370
		opword 0x9101037C
		opword 0x90E10380
		opword 0x90010384
		opword 0x91010388
		bl winIconSet
		bl winFontInit
		lfs f1, float_35_8041d6ac(r2)
		opword 0x387F0780
		lfs f0, float_12_8041d670(r2)
		opword 0xEC21F82A
		opword 0x80BF059C
		lfs f2, float_10_8041d61c(r2)
		opword 0xEF20F02A
		opword 0x809F0594
		opword 0x801F0598
		opword 0xEF02082A
		opword 0x90810350
		opword 0xEF42C82A
		opword 0x812100D0
		opword 0x90010354
		opword 0x811F05A0
		opword 0xD3010350
		opword 0x80FF05A4
		opword 0xD3410354
		opword 0x80DF05A8
		opword 0x80810350
		opword 0x80010354
		opword 0x91210058
		opword 0x91010344
		opword 0x90E10348
		opword 0x90C1034C
		opword 0x90A10358
		opword 0x9081035C
		opword 0x90010360
		opword 0x90A10364
		bl msgSearch
		opword 0x7C661B78
		opword 0x3861035C
		opword 0x38810344
		opword 0x38A10058
		opword 0x4CC63182
		bl winFontSet
		lfs f0, float_28_8041d6a0(r2)
		opword 0x387F0798
		opword 0x80BF05B4
		opword 0xEC190028
		lfs f1, float_10_8041d61c(r2)
		opword 0x809F05AC
		opword 0x801F05B0
		opword 0xEF61002A
		opword 0x9081032C
		opword 0x812100D0
		opword 0x90010330
		opword 0x811F05B8
		opword 0xD301032C
		opword 0x80FF05BC
		opword 0xD3610330
		opword 0x80DF05C0
		opword 0x8081032C
		opword 0x80010330
		opword 0x91210054
		opword 0x91010320
		opword 0x90E10324
		opword 0x90C10328
		opword 0x90A10334
		opword 0x90810338
		opword 0x9001033C
		opword 0x90A10340
		bl msgSearch
		opword 0x7C661B78
		opword 0x38610338
		opword 0x38810320
		opword 0x38A10054
		opword 0x4CC63182
		bl winFontSet
		lfs f0, float_56_8041d6a4(r2)
		opword 0x387F07B0
		opword 0x80BF05CC
		opword 0xEC190028
		lfs f1, float_10_8041d61c(r2)
		opword 0x809F05C4
		opword 0x801F05C8
		opword 0xEF81002A
		opword 0x90810308
		opword 0x812100D0
		opword 0x9001030C
		opword 0x811F05D0
		opword 0xD3010308
		opword 0x80FF05D4
		opword 0xD381030C
		opword 0x80DF05D8
		opword 0x80810308
		opword 0x8001030C
		opword 0x91210050
		opword 0x910102FC
		opword 0x90E10300
		opword 0x90C10304
		opword 0x90A10310
		opword 0x90810314
		opword 0x90010318
		opword 0x90A1031C
		bl msgSearch
		opword 0x7C661B78
		opword 0x38610314
		opword 0x388102FC
		opword 0x38A10050
		opword 0x4CC63182
		bl winFontSet
		lfs f0, float_84_8041d6a8(r2)
		opword 0x387F07CC
		opword 0x80BF05E4
		opword 0xEC190028
		lfs f1, float_10_8041d61c(r2)
		opword 0x809F05DC
		opword 0x801F05E0
		opword 0xEFA1002A
		opword 0x908102E4
		opword 0x812100D0
		opword 0x900102E8
		opword 0x811F05E8
		opword 0xD30102E4
		opword 0x80FF05EC
		opword 0xD3A102E8
		opword 0x80DF05F0
		opword 0x808102E4
		opword 0x800102E8
		opword 0x9121004C
		opword 0x910102D8
		opword 0x90E102DC
		opword 0x90C102E0
		opword 0x90A102EC
		opword 0x908102F0
		opword 0x900102F4
		opword 0x90A102F8
		bl msgSearch
		opword 0x7C661B78
		opword 0x386102F0
		opword 0x388102D8
		opword 0x38A1004C
		opword 0x4CC63182
		bl winFontSet
		lfs f0, float_112_8041d644(r2)
		opword 0x387F07EC
		opword 0x80BF05FC
		opword 0xEC190028
		lfs f1, float_10_8041d61c(r2)
		opword 0x809F05F4
		opword 0x801F05F8
		opword 0xEF21002A
		opword 0x908102C0
		opword 0x812100D0
		opword 0x900102C4
		opword 0x811F0600
		opword 0xD30102C0
		opword 0x80FF0604
		opword 0xD32102C4
		opword 0x80DF0608
		opword 0x808102C0
		opword 0x800102C4
		opword 0x91210048
		opword 0x910102B4
		opword 0x90E102B8
		opword 0x90C102BC
		opword 0x90A102C8
		opword 0x908102CC
		opword 0x900102D0
		opword 0x90A102D4
		bl msgSearch
		opword 0x7C661B78
		opword 0x386102CC
		opword 0x388102B4
		opword 0x38A10048
		opword 0x4CC63182
		bl winFontSet
		lfs f0, float_205_8041d6b4(r2)
		opword 0x831F0614
		opword 0xEC00F82A
		lfs f1, float_8_8041d6b0(r2)
		opword 0x807F060C
		opword 0x801F0610
		opword 0xEC01002A
		lfs f1, float_2_8041d660(r2)
		opword 0x900102A0
		opword 0x82DF0618
		opword 0xEE41002A
		opword 0x9061029C
		opword 0x82BF061C
		opword 0xD34102A0
		opword 0x829F0620
		opword 0xD241029C
		opword 0x82E102A0
		opword 0x8001029C
		opword 0x818100D0
		opword 0x900102A8
		opword 0x817F0184
		opword 0x815F0188
		opword 0x813F018C
		opword 0x811F0190
		opword 0x80FF0194
		opword 0x80DF0198
		opword 0x80BF019C
		opword 0x809F01A0
		opword 0x807F01A4
		opword 0x801F01A8
		opword 0x92E102AC
		opword 0x930102B0
		opword 0x92C10290
		opword 0x92A10294
		opword 0x92810298
		opword 0x91810044
		opword 0xAB5D0096
		opword 0x930102A4
		opword 0x2C1A0000
		opword 0x916108BC
		opword 0x914108C0
		opword 0x912108C4
		opword 0x910108C8
		opword 0x90E108CC
		opword 0x90C108D0
		opword 0x90A108D4
		opword 0x908108D8
		opword 0x906108DC
		opword 0x900108E0
		opword 0x4080001C
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, str_8041D630(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F5A00D0
		opword 0x48000014
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, float_0_8041d634(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F45D378
		opword 0x38611004
		la r4, str_8041D638(r2)
		opword 0x4CC63182
		bl sprintf
		lis r3, (unk_803dfbf8+0x100)@ha
		opword 0x3AC11004
		addi r21, r3, (unk_803dfbf8+0x100)@l
		opword 0x3A8108BC
		opword 0x3A600000
		opword 0x48000028
		opword 0x88160000
		opword 0x7EA3AB78
		opword 0x7C000774
		opword 0x5404103A
		opword 0x3804FF40
		opword 0x7C94002E
		bl strcat
		opword 0x3AD60001
		opword 0x3A730001
		opword 0x38611004
		bl strlen
		opword 0x7C131840
		opword 0x4180FFD0
		lis r4, (unk_803dfbf8+0x100)@ha
		opword 0x386102A8
		addi r7, r4, (unk_803dfbf8+0x100)@l
		opword 0x38A10044
		opword 0x38810290
		la r6, str_8041D63C(r2)
		opword 0x4CC63182
		bl winFontSetR
		opword 0x807F0624
		opword 0x801F0628
		opword 0x90610278
		opword 0x833F062C
		opword 0x9001027C
		opword 0x82DF0630
		opword 0xD2410278
		opword 0x82BF0634
		opword 0xD361027C
		opword 0x83010278
		opword 0x82E1027C
		opword 0x829F0638
		opword 0x818100D0
		opword 0x817F0184
		opword 0x815F0188
		opword 0x813F018C
		opword 0x811F0190
		opword 0x80FF0194
		opword 0x80DF0198
		opword 0x80BF019C
		opword 0x809F01A0
		opword 0x807F01A4
		opword 0x801F01A8
		opword 0x93010284
		opword 0x92E10288
		opword 0x9321028C
		opword 0x92C1026C
		opword 0x92A10270
		opword 0x92810274
		opword 0x91810040
		opword 0xAB5D0078
		opword 0x93210280
		opword 0x2C1A0000
		opword 0x91610894
		opword 0x91410898
		opword 0x9121089C
		opword 0x910108A0
		opword 0x90E108A4
		opword 0x90C108A8
		opword 0x90A108AC
		opword 0x908108B0
		opword 0x906108B4
		opword 0x900108B8
		opword 0x4080001C
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, str_8041D630(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F5A00D0
		opword 0x48000014
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, float_0_8041d634(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F45D378
		opword 0x38610F04
		la r4, str_8041D638(r2)
		opword 0x4CC63182
		bl sprintf
		lis r3, (unk_803dfbf8+0x100)@ha
		opword 0x3AC10F04
		addi r21, r3, (unk_803dfbf8+0x100)@l
		opword 0x3A810894
		opword 0x3A600000
		opword 0x48000028
		opword 0x88160000
		opword 0x7EA3AB78
		opword 0x7C000774
		opword 0x5404103A
		opword 0x3804FF40
		opword 0x7C94002E
		bl strcat
		opword 0x3AD60001
		opword 0x3A730001
		opword 0x38610F04
		bl strlen
		opword 0x7C131840
		opword 0x4180FFD0
		lis r4, (unk_803dfbf8+0x100)@ha
		opword 0x38610284
		addi r7, r4, (unk_803dfbf8+0x100)@l
		opword 0x38A10040
		opword 0x3881026C
		la r6, str_8041D63C(r2)
		opword 0x4CC63182
		bl winFontSetR
		opword 0x807F063C
		opword 0x801F0640
		opword 0x90610254
		opword 0x833F0644
		opword 0x90010258
		opword 0x82DF0648
		opword 0xD2410254
		opword 0x82BF064C
		opword 0xD3810258
		opword 0x83010254
		opword 0x82E10258
		opword 0x829F0650
		opword 0x818100D0
		opword 0x817F0184
		opword 0x815F0188
		opword 0x813F018C
		opword 0x811F0190
		opword 0x80FF0194
		opword 0x80DF0198
		opword 0x80BF019C
		opword 0x809F01A0
		opword 0x807F01A4
		opword 0x801F01A8
		opword 0x93010260
		opword 0x92E10264
		opword 0x93210268
		opword 0x92C10248
		opword 0x92A1024C
		opword 0x92810250
		opword 0x9181003C
		opword 0xAB5D009A
		opword 0x9321025C
		opword 0x2C1A0000
		opword 0x9161086C
		opword 0x91410870
		opword 0x91210874
		opword 0x91010878
		opword 0x90E1087C
		opword 0x90C10880
		opword 0x90A10884
		opword 0x90810888
		opword 0x9061088C
		opword 0x90010890
		opword 0x4080001C
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, str_8041D630(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F5A00D0
		opword 0x48000014
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, float_0_8041d634(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F45D378
		opword 0x38610E04
		la r4, str_8041D638(r2)
		opword 0x4CC63182
		bl sprintf
		lis r3, (unk_803dfbf8+0x100)@ha
		opword 0x3AC10E04
		addi r21, r3, (unk_803dfbf8+0x100)@l
		opword 0x3A81086C
		opword 0x3A600000
		opword 0x48000028
		opword 0x88160000
		opword 0x7EA3AB78
		opword 0x7C000774
		opword 0x5404103A
		opword 0x3804FF40
		opword 0x7C94002E
		bl strcat
		opword 0x3AD60001
		opword 0x3A730001
		opword 0x38610E04
		bl strlen
		opword 0x7C131840
		opword 0x4180FFD0
		lis r4, (unk_803dfbf8+0x100)@ha
		opword 0x38610260
		addi r7, r4, (unk_803dfbf8+0x100)@l
		opword 0x38A1003C
		opword 0x38810248
		la r6, str_8041D63C(r2)
		opword 0x4CC63182
		bl winFontSetR
		opword 0x807F0654
		opword 0x801F0658
		opword 0x90610230
		opword 0x833F065C
		opword 0x90010234
		opword 0x82DF0660
		opword 0xD2410230
		opword 0x82BF0664
		opword 0xD3A10234
		opword 0x83010230
		opword 0x82E10234
		opword 0x829F0668
		opword 0x818100D0
		opword 0x817F0184
		opword 0x815F0188
		opword 0x813F018C
		opword 0x811F0190
		opword 0x80FF0194
		opword 0x80DF0198
		opword 0x80BF019C
		opword 0x809F01A0
		opword 0x807F01A4
		opword 0x801F01A8
		opword 0x9301023C
		opword 0x92E10240
		opword 0x93210244
		opword 0x92C10224
		opword 0x92A10228
		opword 0x9281022C
		opword 0x91810038
		opword 0xAB5D009C
		opword 0x93210238
		opword 0x2C1A0000
		opword 0x91610844
		opword 0x91410848
		opword 0x9121084C
		opword 0x91010850
		opword 0x90E10854
		opword 0x90C10858
		opword 0x90A1085C
		opword 0x90810860
		opword 0x90610864
		opword 0x90010868
		opword 0x4080001C
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, str_8041D630(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F5A00D0
		opword 0x48000014
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, float_0_8041d634(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F45D378
		opword 0x38610D04
		la r4, str_8041D638(r2)
		opword 0x4CC63182
		bl sprintf
		lis r3, (unk_803dfbf8+0x100)@ha
		opword 0x3AC10D04
		addi r21, r3, (unk_803dfbf8+0x100)@l
		opword 0x3A810844
		opword 0x3A600000
		opword 0x48000028
		opword 0x88160000
		opword 0x7EA3AB78
		opword 0x7C000774
		opword 0x5404103A
		opword 0x3804FF40
		opword 0x7C94002E
		bl strcat
		opword 0x3AD60001
		opword 0x3A730001
		opword 0x38610D04
		bl strlen
		opword 0x7C131840
		opword 0x4180FFD0
		lis r4, (unk_803dfbf8+0x100)@ha
		opword 0x3861023C
		addi r7, r4, (unk_803dfbf8+0x100)@l
		opword 0x38A10038
		opword 0x38810224
		la r6, str_8041D63C(r2)
		opword 0x4CC63182
		bl winFontSetR
		opword 0x3C608000
		lwz r4, gp(r13)
		opword 0x800300F8
		opword 0x38A00000
		opword 0x80640020
		opword 0x80840024
		opword 0x5406F0BE
		bl __div2i
		opword 0x3CA00005
		opword 0x7C872378
		opword 0x38057E3F
		opword 0x38C00000
		opword 0x7C651B78
		opword 0x7C070010
		opword 0x7C053110
		opword 0x7C1CE110
		opword 0x7C0000D1
		opword 0x41820010
		opword 0x3A800063
		opword 0x3AA0003B
		opword 0x48000040
		opword 0x7CF53B78
		opword 0x7CB32B78
		opword 0x38A00000
		opword 0x38C00E10
		bl __div2u
		opword 0x7C942378
		opword 0x7E639B78
		opword 0x7EA4AB78
		opword 0x38A00000
		opword 0x38C00E10
		bl __mod2u
		opword 0x38A00000
		opword 0x38C0003C
		bl __div2u
		opword 0x7C952378
		lfs f0, float_172_8041d6b8(r2)
		opword 0x2C140000
		opword 0x839F0674
		opword 0x7E9AA378
		opword 0xEC00F82A
		lfs f1, float_8_8041d6b0(r2)
		opword 0x807F066C
		opword 0x801F0670
		opword 0xEC21002A
		lfs f0, float_16_8041d6bc(r2)
		opword 0x90010210
		opword 0x831F0678
		opword 0xEC010028
		lfs f1, float_2_8041d660(r2)
		opword 0xD3210210
		opword 0x82FF067C
		opword 0xEC01002A
		opword 0x83210210
		opword 0x82DF0680
		opword 0x818100D0
		opword 0xEC01002A
		opword 0x9061020C
		opword 0x817F01AC
		opword 0x815F01B0
		opword 0xD001020C
		opword 0x813F01B4
		opword 0x8361020C
		opword 0x811F01B8
		opword 0x80FF01BC
		opword 0x80DF01C0
		opword 0x80BF01C4
		opword 0x809F01C8
		opword 0x807F01CC
		opword 0x801F01D0
		opword 0x93810214
		opword 0x93610218
		opword 0x9321021C
		opword 0x93810220
		opword 0x93010200
		opword 0x92E10204
		opword 0x92C10208
		opword 0x91810034
		opword 0x9161081C
		opword 0x91410820
		opword 0x91210824
		opword 0x91010828
		opword 0x90E1082C
		opword 0x90C10830
		opword 0x90A10834
		opword 0x90810838
		opword 0x9061083C
		opword 0x90010840
		opword 0x4080001C
		lis r3, unk_803dfbf8@ha
		la r4, str_8041D630(r2)
		addi r3, r3, unk_803dfbf8@l
		bl strcpy
		opword 0x7F5400D0
		opword 0x48000014
		lis r3, unk_803dfbf8@ha
		la r4, float_0_8041d634(r2)
		addi r3, r3, unk_803dfbf8@l
		bl strcpy
		opword 0x7F45D378
		opword 0x38610C04
		la r4, str_8041D638(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x3A600000
		opword 0x38610C04
		bl strlen
		opword 0x20030002
		opword 0x7C130040
		opword 0x40800018
		lis r3, unk_803dfbf8@ha
		la r4, str_8041D5A8(r2)
		addi r3, r3, unk_803dfbf8@l
		bl strcat
		opword 0x4800003C
		opword 0x38610C04
		bl strlen
		opword 0x20030002
		lis r3, unk_803dfbf8@ha
		opword 0x7C009850
		opword 0x38810C04
		opword 0x7C0400AE
		opword 0x3881081C
		addi r3, r3, unk_803dfbf8@l
		opword 0x7C000774
		opword 0x5405103A
		opword 0x3805FF40
		opword 0x7C84002E
		bl strcat
		opword 0x3A730001
		opword 0x2C130002
		opword 0x4180FF98
		lis r4, unk_803dfbf8@ha
		opword 0x38610218
		addi r7, r4, unk_803dfbf8@l
		opword 0x38A10034
		opword 0x38810200
		la r6, str_8041D63C(r2)
		opword 0x4CC63182
		bl winFontSetR
		opword 0x807F0684
		opword 0x2C150000
		opword 0x801F0688
		opword 0x7EBAAB78
		opword 0x906101E8
		opword 0x837F068C
		opword 0x900101EC
		opword 0x82FF0690
		opword 0xD24101E8
		opword 0x82DF0694
		opword 0xD32101EC
		opword 0x832101E8
		opword 0x830101EC
		opword 0x829F0698
		opword 0x818100D0
		opword 0x817F01AC
		opword 0x815F01B0
		opword 0x813F01B4
		opword 0x811F01B8
		opword 0x80FF01BC
		opword 0x80DF01C0
		opword 0x80BF01C4
		opword 0x809F01C8
		opword 0x807F01CC
		opword 0x801F01D0
		opword 0x936101F0
		opword 0x932101F4
		opword 0x930101F8
		opword 0x936101FC
		opword 0x92E101DC
		opword 0x92C101E0
		opword 0x928101E4
		opword 0x91810030
		opword 0x916107F4
		opword 0x914107F8
		opword 0x912107FC
		opword 0x91010800
		opword 0x90E10804
		opword 0x90C10808
		opword 0x90A1080C
		opword 0x90810810
		opword 0x90610814
		opword 0x90010818
		opword 0x4080001C
		lis r3, unk_803dfbf8@ha
		la r4, str_8041D630(r2)
		addi r3, r3, unk_803dfbf8@l
		bl strcpy
		opword 0x7F5500D0
		opword 0x48000014
		lis r3, unk_803dfbf8@ha
		la r4, float_0_8041d634(r2)
		addi r3, r3, unk_803dfbf8@l
		bl strcpy
		opword 0x7F45D378
		opword 0x38610B04
		la r4, str_8041D638(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x3A600000
		opword 0x38610B04
		bl strlen
		opword 0x20030002
		opword 0x7C130040
		opword 0x40800018
		lis r3, unk_803dfbf8@ha
		la r4, str_8041D5A8(r2)
		addi r3, r3, unk_803dfbf8@l
		bl strcat
		opword 0x4800003C
		opword 0x38610B04
		bl strlen
		opword 0x20030002
		lis r3, unk_803dfbf8@ha
		opword 0x7C009850
		opword 0x38810B04
		opword 0x7C0400AE
		opword 0x388107F4
		addi r3, r3, unk_803dfbf8@l
		opword 0x7C000774
		opword 0x5405103A
		opword 0x3805FF40
		opword 0x7C84002E
		bl strcat
		opword 0x3A730001
		opword 0x2C130002
		opword 0x4180FF98
		lis r4, unk_803dfbf8@ha
		opword 0x386101F4
		addi r7, r4, unk_803dfbf8@l
		opword 0x38A10030
		opword 0x388101DC
		la r6, str_8041D63C(r2)
		opword 0x4CC63182
		bl winFontSetR
		opword 0x807E0028
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit
		lfs f0, float_190_8041d614(r2)
		opword 0x3AC00000
		lfs f24, float_10_8041d61c(r2)
		opword 0x7ED3B378
		opword 0xEC00F82A
		opword 0x82A100DC
		opword 0xCADF0828
		opword 0x3E804330
		opword 0xEE78002A
		opword 0x6E608000
		opword 0x811F06A4
		opword 0x9001181C
		opword 0x388101D0
		opword 0x80FF069C
		opword 0x38A101B8
		opword 0x92811818
		opword 0x38C1002C
		opword 0x801F06A0
		opword 0x38600011
		opword 0xC8011818
		opword 0x90E101C4
		opword 0xEC00B028
		opword 0x817F06A8
		opword 0xD26101C4
		opword 0x815F06AC
		opword 0xEC1E0028
		opword 0x813F06B0
		opword 0x80E101C4
		opword 0x900101C8
		opword 0xEC18002A
		opword 0x92A1002C
		opword 0xD00101C8
		opword 0x800101C8
		opword 0x916101B8
		opword 0x914101BC
		opword 0x912101C0
		opword 0x910101CC
		opword 0x90E101D0
		opword 0x900101D4
		opword 0x910101D8
		bl winTexSet
		opword 0x3AD60001
		opword 0x3A73001C
		opword 0x2C160004
		opword 0x4180FF74
		lfs f0, float_112_8041d644(r2)
		opword 0x388101AC
		opword 0x811F06BC
		opword 0x38A10194
		opword 0xEC1E0028
		lfs f1, float_2_8041d660(r2)
		lfs f3, float_220_8041d6c0(r2)
		opword 0x38C10028
		opword 0x80FF06B4
		opword 0x38600012
		opword 0xEC01002A
		lfs f2, float_10_8041d61c(r2)
		opword 0x801F06B8
		opword 0xEF03F82A
		opword 0x90E101A0
		opword 0xEC02002A
		opword 0xD30101A0
		opword 0x818100D4
		opword 0xEC000828
		opword 0x900101A4
		opword 0x817F06C0
		opword 0x815F06C4
		opword 0xD00101A4
		opword 0x813F06C8
		opword 0x80E101A0
		opword 0x800101A4
		opword 0x91810028
		opword 0x91610194
		opword 0x91410198
		opword 0x9121019C
		opword 0x910101A8
		opword 0x90E101AC
		opword 0x900101B0
		opword 0x910101B4
		bl winTexSet
		opword 0x807E0188
		bl animPoseGetAnimPosePtr
		opword 0x807E0188
		bl animPoseGetAnimDataPtr
		opword 0x801E018C
		opword 0x2C000000
		opword 0x4082004C
		opword 0x80630024
		opword 0x3C004330
		lwz r4, gp(r13)
		opword 0xC0030008
		opword 0x80A4001C
		opword 0xFC00001E
		opword 0x90011810
		opword 0xC83F0820
		opword 0x807E0188
		opword 0xD8011818
		opword 0x8081181C
		opword 0x7C052396
		opword 0x7C0021D6
		opword 0x7C002850
		opword 0x90011814
		opword 0xC8011810
		opword 0xEC200828
		bl animPoseSetLocalTime
		opword 0x807E0188
		bl animPoseMain
		lfs f0, float_150_8041d69c(r2)
		opword 0xFC40F090
		lwz r0, dat_8041d608(r2)
		opword 0x7FC3F378
		opword 0xEC3F0028
		lfs f3, float_0_8041d6c4(r2)
		opword 0x90010024
		lfs f4, float_1_8041d6c8(r2)
		opword 0x38810024
		bl winKageGX
		lfs f0, float_150_8041d69c(r2)
		opword 0xFC40F090
		lfs f3, float_0_8041d6c4(r2)
		opword 0x386109D4
		opword 0xEC3F0028
		bl PSMTXTrans
		bl winZClear
		opword 0x807E0188
		opword 0x388109D4
		lfs f1, float_0_8041d6c4(r2)
		opword 0x38A00002
		lfs f2, float_5_8041d6cc(r2)
		bl animPoseDrawMtx
		opword 0x801E0190
		opword 0x2C000000
		opword 0x41820414
		lfs f3, float_270_8041d650(r2)
		opword 0x7FC3F378
		lfs f2, float_160_8041d6d0(r2)
		opword 0x38800000
		opword 0xEC3F1828
		lfs f4, float_254_8041d6d4(r2)
		bl winWazaGX
		bl winFontInit
		lfs f0, float_90_8041d6d8(r2)
		opword 0x387F0808
		opword 0x80BF06D0
		opword 0xEC20F82A
		opword 0x809F06D4
		lfs f0, float_270_8041d650(r2)
		opword 0x801F06CC
		opword 0xEC010028
		opword 0x812100D4
		opword 0x9001017C
		opword 0x811F06D8
		opword 0xD001017C
		opword 0x80FF06DC
		opword 0x80DF06E0
		opword 0x8001017C
		opword 0x91210020
		opword 0x91010170
		opword 0x90E10174
		opword 0x90C10178
		opword 0x90A10180
		opword 0x90810184
		opword 0x90010188
		opword 0x90A1018C
		opword 0x90810190
		bl msgSearch
		opword 0x7C661B78
		opword 0x38610188
		opword 0x38810170
		opword 0x38A10020
		opword 0x4CC63182
		bl winFontSetEdge
		lfs f0, float_270_8041d650(r2)
		opword 0x38610164
		opword 0x801F06E4
		opword 0x3881014C
		opword 0xEC180028
		opword 0x811F06E8
		opword 0x90010158
		opword 0x38A1001C
		opword 0x80FF06EC
		la r6, str_8041D6DC(r2)
		opword 0xD0010158
		opword 0x818100D4
		opword 0x817F06F0
		opword 0x815F06F4
		opword 0x813F06F8
		opword 0x80010158
		opword 0x9181001C
		opword 0x9161014C
		opword 0x91410150
		opword 0x91210154
		opword 0x9101015C
		opword 0x90E10160
		opword 0x90010164
		opword 0x91010168
		opword 0x90E1016C
		opword 0x4CC63182
		bl winFontSetEdge
		lfs f0, float_17_8041d6e8(r2)
		lis r4, superActionTable@ha
		lfs f4, float_270_8041d650(r2)
		lis r3, (unk_803dfbf8+0x100)@ha
		opword 0xEC00C02A
		lfs f1, float_228_8041d6e4(r2)
		opword 0x3B000000
		opword 0xEC772028
		opword 0xEC41F82A
		lfs f5, float_10_8041d61c(r2)
		opword 0xEC002028
		lfs f1, float_4_8041d66c(r2)
		opword 0xEE822028
		opword 0x834100D8
		opword 0xEE65182A
		opword 0xCADF0828
		opword 0xEEA1002A
		addi r22, r4, superActionTable@l
		addi r29, r3, (unk_803dfbf8+0x100)@l
		opword 0x7F15C378
		opword 0x3B8107CC
		opword 0x3F604330
		opword 0x480002A4
		opword 0x22F50082
		opword 0x811F0704
		opword 0x6EE08000
		opword 0x80DF06FC
		opword 0x9001181C
		opword 0x38610140
		opword 0x801F0700
		opword 0x38810128
		opword 0x93611818
		opword 0x38A10018
		opword 0x817F0708
		opword 0xC8011818
		opword 0x90C10134
		opword 0xEC00B028
		opword 0x815F070C
		opword 0x90010138
		opword 0x813F0710
		opword 0xD2610134
		opword 0x80D60000
		opword 0xD0010138
		opword 0x80E10134
		opword 0x80010138
		opword 0x93410018
		opword 0x91610128
		opword 0x9141012C
		opword 0x91210130
		opword 0x90E10140
		opword 0x90010144
		opword 0x91010148
		opword 0x9101013C
		opword 0x80C60000
		bl winFontSetLabel
		opword 0x80760000
		opword 0x817F0184
		opword 0x8B230012
		opword 0x815F0188
		opword 0x813F018C
		opword 0x2C190000
		opword 0x811F0190
		opword 0x80FF0194
		opword 0x80DF0198
		opword 0x80BF019C
		opword 0x809F01A0
		opword 0x807F01A4
		opword 0x801F01A8
		opword 0x916107CC
		opword 0x914107D0
		opword 0x912107D4
		opword 0x910107D8
		opword 0x90E107DC
		opword 0x90C107E0
		opword 0x90A107E4
		opword 0x908107E8
		opword 0x906107EC
		opword 0x900107F0
		opword 0x4080001C
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, str_8041D630(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F3900D0
		opword 0x48000014
		lis r3, (unk_803dfbf8+0x100)@ha
		la r4, float_0_8041d634(r2)
		addi r3, r3, (unk_803dfbf8+0x100)@l
		bl strcpy
		opword 0x7F25CB78
		opword 0x38610A04
		la r4, str_8041D638(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x3A810A04
		opword 0x3A600000
		opword 0x48000028
		opword 0x88140000
		opword 0x7FA3EB78
		opword 0x7C000774
		opword 0x5404103A
		opword 0x3804FF40
		opword 0x7C9C002E
		bl strcat
		opword 0x3A940001
		opword 0x3A730001
		opword 0x38610A04
		bl strlen
		opword 0x7C131840
		opword 0x4180FFD0
		opword 0x7FA5EB78
		opword 0x386107AC
		la r4, str_8041D63C(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x811F0720
		opword 0x386107AC
		opword 0x80FF0724
		opword 0x80DF0728
		opword 0x80BF0714
		opword 0x809F0718
		opword 0x801F071C
		opword 0x93410014
		opword 0x91010104
		opword 0x90E10108
		opword 0x90C1010C
		opword 0x90A10110
		opword 0x90810114
		opword 0x90010118
		bl FontGetMessageWidth
		opword 0x5460FC7E
		opword 0x6EE78000
		opword 0x6C038000
		opword 0x80010118
		opword 0x9061181C
		opword 0x3861011C
		opword 0x38810104
		opword 0x38A10014
		opword 0x93611818
		opword 0x38C107AC
		opword 0xC8011818
		opword 0x90E11814
		opword 0xEC20B028
		opword 0x93611810
		opword 0xC8011810
		opword 0xEC340828
		opword 0x90010124
		opword 0xEC00B028
		opword 0xD0210110
		opword 0xD0010114
		opword 0x80E10110
		opword 0x80010114
		opword 0x90E1011C
		opword 0x90010120
		opword 0x4CC63182
		bl winFontSet
		opword 0x20150078
		opword 0x811F0734
		opword 0x6C008000
		opword 0x80FF072C
		opword 0x9001180C
		opword 0x386100F8
		opword 0x801F0730
		opword 0x388100E0
		opword 0x93611808
		opword 0x38A10010
		opword 0x817F0738
		la r6, str_8041D6DC(r2)
		opword 0xC8011808
		opword 0x90E100EC
		opword 0xEC00B028
		opword 0x815F073C
		opword 0x900100F0
		opword 0x813F0740
		opword 0xD2A100EC
		opword 0xD00100F0
		opword 0x80E100EC
		opword 0x800100F0
		opword 0x93410010
		opword 0x916100E0
		opword 0x914100E4
		opword 0x912100E8
		opword 0x910100F4
		opword 0x90E100F8
		opword 0x900100FC
		opword 0x91010100
		opword 0x4CC63182
		bl winFontSet
		opword 0x3AB5001A
		opword 0x3AD60004
		opword 0x3B180001
		opword 0x801E0198
		opword 0x7C180000
		opword 0x4180FD58
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    w = param;
    pouch = pouchGetPtr();
    white = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
    black = (GXColor){0x00, 0x00, 0x00, 0xFF};
    x = w->pos[idx].x;
    y = w->pos[idx].y;
    winBgGX(w, 0, x, y);
    winNameGX(w, 2, x - 265.0f, 154.0f + y, 190.0f, 24.0f);
    cx = 10.0f + (x - 265.0f);
    winFontInit();
    rowA = 152.0f + y;
    winFontSetEdge((Vec){cx, rowA, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white, msgSearch("name_mario"));
    cx += 0.8f * FontGetMessageWidth(msgSearch("name_mario"));
    cx += 20.0f;
    winIconInit();
    winIconSet(0x19E, (Vec){cx, 142.0f + y, 0.0f}, (Vec){0.6f, 0.6f, 0.6f}, white);
    cx += 20.0f;
    winFontInit();
    winFontSetEdge((Vec){cx, rowA, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white, msgSearch("msg_menu_mario_level"));
    sprintf(buf, "%s", winZenkakuStr(pouch->level));
    winFontInit();
    winFontSetEdge((Vec){(190.0f + (x - 265.0f)) - 0.8f * FontGetMessageWidth(buf) - 10.0f, rowA, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white, buf);
    winTexInit(*w->file->data);
    winTexSet(0xB0, (Vec){x - 255.0f, 112.0f + y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    winFontInit();
    winFontSet((Vec){x - 240.0f, 124.0f + y, 0.0f}, (Vec){0.7f, 0.7f, 0.7f}, black, msgSearch(BattleGetRankNameLabel(pouch->level)));
#endif
#ifndef NONMATCHING
#pragma defer_codegen reset
#endif

#ifdef NONMATCHING
    for (i = 0; i < 6; i++) {
        if (w->idx != pri[i]) {
            fukidashi(w, pri[i], x, y);
        }
    }
    fukidashi(w, w->idx, x, y);

    winKirinukiGX(w, 0, x - 270.0f, y - 10.0f, 264.0f, 110.0f);
    rowA = 50.0f + (x - 270.0f) - 2.0f;
    statX = 50.0f + (x - 270.0f);
    for (i = 0; i < 3; i++) {
        GXColor cols[3] = {{0xCB, 0x8C, 0xA2, 0xFE}, {0xCB, 0xBE, 0x89, 0xFE}, {0x94, 0xB9, 0xC7, 0xFE}};
        GXColor reds[3] = {{0xA7, 0x3C, 0x3C, 0xFF}, {0x37, 0x69, 0x1E, 0xFF}, {0x0F, 0x21, 0x7A, 0xFF}};
        const char* const N_stat_name_tbl[3] = {"\x82\x67\x82\x6F", "\x82\x65\x82\x6F", "\x82\x61\x82\x6F"};
        const char* ruby[3] = {"msg_menu_mario_ruby_hp", "msg_menu_mario_ruby_fp", "msg_menu_mario_ruby_bp"};

        nameW = FontGetMessageWidth(N_stat_name_tbl[i]);
        rubyW = 0.5f * FontGetMessageWidth(msgSearch(ruby[i]));
        winTexInit(*w->file->data);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
        winTexSet(0xAF, (Vec){rowA, (cx = (y - 38.0f) - (f32)(i * 34)) - 4.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, cols[i]);
        winFontInit();
        winFontSet((Vec){statX - nameW / 2.0f, 12.0f + cx, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, N_stat_name_tbl[i]);
        winFontSet((Vec){statX - rubyW / 2.0f, 21.0f + cx, 0.0f}, (Vec){0.5f, 0.5f, 0.5f}, reds[i], msgSearch(ruby[i]));
    }

    winIconInit();
    col = 110.0f + (x - 270.0f);
    row0 = 4.0f + (y - 38.0f);
    winIconSet(0x19F, (Vec){col, row0, 0.0f}, (Vec){0.82f, 0.82f, 0.82f}, white);
    rowB = (y - 38.0f) - 34.0f;
    row1 = 4.0f + rowB;
    winIconSet(0x1A0, (Vec){col, row1, 0.0f}, (Vec){0.82f, 0.82f, 0.82f}, white);
    rowA = (y - 38.0f) - 68.0f;
    winIconSet(0x1A1, (Vec){col, 4.0f + rowA, 0.0f}, (Vec){0.82f, 0.82f, 0.82f}, white);
    winFontInit();
    col = 130.0f + (x - 270.0f);
    row2 = 4.0f + (12.0f + (y - 38.0f));
    winFontSetR((Vec){col, row2, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, "%s", winZenkakuStr(pouch->currentHP));
    rowB = 4.0f + (12.0f + rowB);
    winFontSetR((Vec){col, rowB, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, "%s", winZenkakuStr(pouch->currentFP));
    winFontSetR((Vec){col, 4.0f + (12.0f + rowA), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, "%s", winZenkakuStr(pouch->maximumBP));
    winTexInit(*w->file->data);
    col = 190.0f + (x - 270.0f);
    winTexSet(0x10, (Vec){col, row0, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    winTexSet(0x10, (Vec){col, row1, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    winFontInit();
    col = 200.0f + (x - 270.0f);
    winFontSet((Vec){col, row2, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, "%s", winZenkakuStr(pouch->maximumHP));
    winFontSet((Vec){col, rowB, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, "%s", winZenkakuStr(pouch->maximumFP));

    if (w->f198 > 0) {
        winKirinukiGX(w, 0, 10.0f + x, (20.0f + (130.0f + y)) - 20.0f, 260.0f, 80.0f);
        winIconInit();
        col = 10.0f + (40.0f + x);
        rowB = 106.0f + y;
        winIconSet(0x20F, (Vec){col, rowB, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white);
        cx = 70.0f + y;
        winIconSet(0x197, (Vec){col, cx, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white);
        winFontInit();
        winFontSet((Vec){10.0f + (70.0f + x), 10.0f + cx, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, msgSearch("msg_menu_mario_special"));
        winIconInit();
        cx = 10.0f + (80.0f + x);
        for (i = 0; i < w->f198; i++) {
            if (i < pouch->currentSP / 100) {
                winIconSet(0x1B7 + i, (Vec){cx + (f32)(i * 22), rowB, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white);
            } else {
                winIconSet(0x1BF, (Vec){cx + (f32)(i * 22), rowB, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white);
            }
        }
    }

    left = 10.0f + x;
    winKirinukiGX(w, 0, left, 10.0f + (20.0f + y), 260.0f, 150.0f);
    winIconInit();
    rowB = 10.0f + (20.0f + x);
    winIconSet(0x18C, (Vec){rowB, 10.0f + y, 0.0f}, (Vec){0.62f, 0.62f, 0.62f}, white);
    winIconSet(0x18B, (Vec){rowB, 10.0f + (y - 28.0f), 0.0f}, (Vec){0.62f, 0.62f, 0.62f}, white);
    winIconSet(0x18D, (Vec){rowB, 10.0f + (y - 56.0f), 0.0f}, (Vec){0.62f, 0.62f, 0.62f}, white);
    winIconSet(0x102, (Vec){rowB, 10.0f + (y - 84.0f), 0.0f}, (Vec){0.62f, 0.62f, 0.62f}, white);
    winIconSet(0x1A2, (Vec){rowB, 10.0f + (y - 112.0f), 0.0f}, (Vec){0.62f, 0.62f, 0.62f}, white);
    winFontInit();
    col = 10.0f + (35.0f + x);
    rowA = 12.0f + y;
    row0 = 10.0f + rowA;
    winFontSet((Vec){col, row0, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, msgSearch("msg_menu_mario_num_sp"));
    row1 = 10.0f + (rowA - 28.0f);
    winFontSet((Vec){col, row1, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, msgSearch("msg_menu_mario_num_coin"));
    row2 = 10.0f + (rowA - 56.0f);
    winFontSet((Vec){col, row2, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, msgSearch("msg_menu_mario_num_hoshi"));
    row3 = 10.0f + (rowA - 84.0f);
    winFontSet((Vec){col, row3, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, msgSearch("msg_menu_mario_num_super_coin"));
    rowA = 10.0f + (rowA - 112.0f);
    winFontSet((Vec){col, rowA, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, msgSearch("msg_menu_mario_num_playtime"));
    numX = 2.0f + (8.0f + (205.0f + x));
    winFontSetR((Vec){numX, row0, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", winZenkakuStr(pouch->mStarPoints));
    winFontSetR((Vec){numX, row1, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", winZenkakuStr(pouch->coins));
    winFontSetR((Vec){numX, row2, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", winZenkakuStr(pouch->mStarPieceCount));
    winFontSetR((Vec){numX, row3, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", winZenkakuStr(pouch->mShineSpriteCount));

    tsecs = gp->retraceLocalTime / OS_TIMER_CLOCK;
    if (tsecs > 359999) {
        hour = 99;
        min = 59;
    } else {
        secs = tsecs;
        hour = (u64)secs / 3600;
        min = (u64)secs % 3600 / 60;
    }
    winFontSetR((Vec){2.0f + (2.0f + ((8.0f + (172.0f + x)) - 16.0f)), rowA, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", unk_8016af5c(hour, 2));
    winFontSetR((Vec){numX, rowA, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", unk_8016af5c(min, 2));

    winTexInit(*w->file->data);
    cx = 10.0f + (190.0f + x);
    for (i = 0; i < 4; i++) {
        winTexSet(0x11, (Vec){cx, 10.0f + (y - (f32)(i * 28)), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    }
    rowB = 220.0f + x;
    winTexSet(0x12, (Vec){rowB, (10.0f + (2.0f + (y - 112.0f))) - 2.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);

    animPoseGetAnimPosePtr(w->poseId);
    anim = animPoseGetAnimDataPtr(w->poseId);
    if (w->f18C == 0) {
        animPoseSetLocalTime(w->poseId, (f32)(gp->retraceCount % (s32)(*(f32*)(*(u8**)((u8*)anim + 0x24) + 8))));
    }
    animPoseMain(w->poseId);
    winKageGX(w, (GXColor){0x00, 0x00, 0x00, 0x80}, x - 150.0f, y, 0.0f, 1.0f);
    PSMTXTrans(mtx, x - 150.0f, y, 0.0f);
    winZClear();
    animPoseDrawMtx(w->poseId, mtx, 2, 0.0f, 5.0f);

    if (w->f190) {
        winWazaGX(w, 0, x - 270.0f, 160.0f, 270.0f, 254.0f);
        winFontInit();
        winFontSetEdge((Vec){(90.0f + x) - 270.0f, 155.0f, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white, msgSearch("msg_menu_mario_sac_waza"));
        winFontSetEdge((Vec){rowB - 270.0f, 155.0f, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white, "\x82\x72\x82\x6F");
        cx = 10.0f + (left - 270.0f);
        costX = (228.0f + x) - 270.0f;
        rowA = 4.0f + ((17.0f + rowB) - 270.0f);
        for (i = 0; i < w->f198; i++) {
            char sbuf[0x20];

            winFontSetLabel((Vec){cx, (f32)(130 - i * 26), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, superActionTable[i]->name);
            sprintf(sbuf, "%s", winZenkakuStr(superActionTable[i]->cost));
            winFontSet((Vec){costX - (f32)(FontGetMessageWidth(sbuf) / 2), (f32)(130 - i * 26), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, sbuf);
            winFontSet((Vec){rowA, (f32)(120 - i * 26), 0.0f}, (Vec){0.5f, 0.5f, 0.5f}, black, "\x82\x72\x82\x6F");
        }
    }
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
asm const char* winZenkakuStr(s32 n) {
	nofralloc
	stwu r1, -0x140(r1)
	mflr r0
	lis r4, jumptable_802F57D4@ha
	stw r0, 0x144(r1)
	addi r12, r4, jumptable_802F57D4@l
	stw r31, 0x13c(r1)
	stw r30, 0x138(r1)
	stw r29, 0x134(r1)
	stw r28, 0x130(r1)
	mr. r28, r3
	lwz r11, 0x0(r12)
	lwz r10, 0x4(r12)
	lwz r9, 0x8(r12)
	lwz r8, 0xc(r12)
	lwz r7, 0x10(r12)
	lwz r6, 0x14(r12)
	lwz r5, 0x18(r12)
	lwz r4, 0x1c(r12)
	lwz r3, 0x20(r12)
	lwz r0, 0x24(r12)
	stw r11, 0x8(r1)
	stw r10, 0xc(r1)
	stw r9, 0x10(r1)
	stw r8, 0x14(r1)
	stw r7, 0x18(r1)
	stw r6, 0x1c(r1)
	stw r5, 0x20(r1)
	stw r4, 0x24(r1)
	stw r3, 0x28(r1)
	stw r0, 0x2c(r1)
	bge L_af_1
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, str_8041D630(r2)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	neg r28, r28
	b L_af_2
L_af_1:
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, float_0_8041d634(r2)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
L_af_2:
	mr r5, r28
	addi r3, r1, 0x30
	la r4, str_8041D638(r2)
	crclr 6
	bl sprintf
	lis r3, (unk_803dfbf8+0x100)@ha
	addi r29, r1, 0x30
	addi r30, r3, (unk_803dfbf8+0x100)@l
	addi r31, r1, 0x8
	li r28, 0x0
	b L_af_3
L_af_4:
	lbz r0, 0x0(r29)
	mr r3, r30
	extsb r0, r0
	slwi r4, r0, 2
	subi r0, r4, 0xc0
	lwzx r4, r31, r0
	bl strcat
	addi r29, r29, 0x1
	addi r28, r28, 0x1
L_af_3:
	addi r3, r1, 0x30
	bl strlen
	cmplw r28, r3
	blt L_af_4
	lwz r0, 0x144(r1)
	lis r3, (unk_803dfbf8+0x100)@ha
	lwz r31, 0x13c(r1)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	lwz r30, 0x138(r1)
	lwz r29, 0x134(r1)
	lwz r28, 0x130(r1)
	mtlr r0
	addi r1, r1, 0x140
	blr
#endif
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void winMarioInit(WinMarioWork* w) {
	asm {
		lis r4, str_802F5650@ha
		addi r30, r4, str_802F5650@l
	}
	asm volatile {
		mr r28, r3
		bl pouchGetPtr
		opword 0xA01C0000
		opword 0x7C7F1B78
		opword 0x540004A5
		opword 0x41820074
		la r29, str_8041D580(r2)
		bl marioGetColor
		opword 0x2C030002
		opword 0x41820034
		opword 0x40800014
		opword 0x2C030000
		opword 0x41820018
		opword 0x4080001C
		opword 0x4800002C
		opword 0x2C030004
		opword 0x40800024
		opword 0x4800001C
		la r29, str_8041D580(r2)
		opword 0x48000018
		la r29, str_8041D704(r2)
		opword 0x48000010
		la r29, str_8041D708(r2)
		opword 0x48000008
		la r29, str_8041D70C(r2)
		opword 0x387E0830
		opword 0x38800000
		bl animPoseEntry
		opword 0x907C0188
		opword 0x7FA4EB78
		opword 0x38A00001
		opword 0x807C0188
		bl animPoseSetAnim
		opword 0x4800006C
		opword 0x3BBE0838
		bl marioGetColor
		opword 0x2C030002
		opword 0x41820030
		opword 0x40800014
		opword 0x2C030000
		opword 0x41820030
		opword 0x40800018
		opword 0x48000028
		opword 0x2C030004
		opword 0x40800020
		opword 0x48000018
		opword 0x48000018
		opword 0x3BBE0840
		opword 0x48000010
		opword 0x3BBE084C
		opword 0x48000008
		opword 0x3BBE0858
		opword 0x7FA3EB78
		opword 0x38800000
		bl animPoseEntry
		opword 0x907C0188
		la r4, str_8041D578(r2)
		opword 0x38A00001
		opword 0x807C0188
		bl animPoseSetAnim
		opword 0x807C0188
		opword 0x38801800
		bl animPoseSetMaterialFlagOn
		bl marioGetPtr
		opword 0x80030000
		opword 0x54000043
		opword 0x41820010
		opword 0x807C0188
		opword 0x3C800A00
		bl animPoseSetMaterialFlagOn
		opword 0x38600000
		opword 0x38000000
		opword 0x907C018C
		opword 0x38800001
		opword 0x7C800030
		opword 0x907C0190
		opword 0x907C0194
		opword 0x907C0198
		opword 0xA07F008C
		opword 0x7C600039
		opword 0x41820010
		opword 0x807C0198
		opword 0x38030001
		opword 0x901C0198
		opword 0x38000001
		opword 0xA07F008C
		opword 0x7C800030
		opword 0x7C600039
		opword 0x41820010
		opword 0x807C0198
		opword 0x38030001
		opword 0x901C0198
		opword 0x38000002
		opword 0xA07F008C
		opword 0x7C800030
		opword 0x7C600039
		opword 0x41820010
		opword 0x807C0198
		opword 0x38030001
		opword 0x901C0198
		opword 0x38000003
		opword 0xA07F008C
		opword 0x7C800030
		opword 0x7C600039
		opword 0x41820010
		opword 0x807C0198
		opword 0x38030001
		opword 0x901C0198
		opword 0x38000004
		opword 0xA07F008C
		opword 0x7C800030
		opword 0x7C600039
		opword 0x41820010
		opword 0x807C0198
		opword 0x38030001
		opword 0x901C0198
		opword 0x38000005
		opword 0xA07F008C
		opword 0x7C800030
		opword 0x7C600039
		opword 0x41820010
		opword 0x807C0198
		opword 0x38030001
		opword 0x901C0198
		opword 0x38000006
		opword 0xA07F008C
		opword 0x7C800030
		opword 0x7C600039
		opword 0x41820010
		opword 0x807C0198
		opword 0x38030001
		opword 0x901C0198
		opword 0x38000007
		opword 0xA07F008C
		opword 0x7C800030
		opword 0x7C600039
		opword 0x41820010
		opword 0x807C0198
		opword 0x38030001
		opword 0x901C0198
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void winMarioInit2(WinMarioWork* w) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		lis r4, linkDt@ha
		opword 0x90010024
		opword 0x38000000
		addi r4, r4, linkDt@l
		opword 0x93E1001C
		opword 0x7C7F1B78
		opword 0x90030160
		opword 0x3C004330
		lis r3, double_to_int_802f5e78@ha
		opword 0x80BF0160
		opword 0x90010008
		opword 0x1CA5001C
		lfd f1, double_to_int_802f5e78@l(r3)
		opword 0x90010010
		opword 0x7C042AAE
		opword 0x6C008000
		opword 0x9001000C
		opword 0xC8010008
		opword 0xEC000828
		opword 0xD01F0158
		opword 0xD01F0158
		opword 0x801F0160
		opword 0x1C00001C
		opword 0x7C640214
		opword 0xA8030002
		opword 0x6C008000
		opword 0x90010014
		opword 0xC8010010
		opword 0xEC000828
		opword 0xD01F015C
		opword 0xD01F015C
		opword 0x801F0160
		opword 0x2C000003
		opword 0x41820038
		opword 0x40800058
		opword 0x2C000002
		opword 0x40800008
		opword 0x4800004C
		bl pouchGetHammerLv
		opword 0x5460103A
		la r3, hammer_help(r13)
		opword 0x7CA3002E
		opword 0x7FE3FB78
		opword 0x38800000
		opword 0x38C00000
		bl winMsgEntry
		opword 0x4800004C
		bl pouchGetJumpLv
		opword 0x5460103A
		la r3, boots_help(r13)
		opword 0x7CA3002E
		opword 0x7FE3FB78
		opword 0x38800000
		opword 0x38C00000
		bl winMsgEntry
		opword 0x48000028
		opword 0x1C00001C
		lis r4, linkDt@ha
		opword 0x7FE3FB78
		addi r4, r4, linkDt@l
		opword 0x7CA40214
		opword 0x38800000
		opword 0x80A50014
		opword 0x38C00000
		bl winMsgEntry
		opword 0x38000000
		opword 0x901F018C
		opword 0x901F0190
		opword 0x901F0194
		opword 0x83E1001C
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop

void winMarioExit(WinMarioWork* w) {
    animPoseRelease(w->poseId);
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
s32 winMarioMain(WinMarioWork* w) {
	char _af_pad[16];
	asm {
		mr r29, r3
	}
	asm volatile {
		opword 0x80030190
		opword 0x2C000001
		opword 0x41820674
		opword 0x40800794
		opword 0x2C000000
		opword 0x40800008
		opword 0x48000788
		opword 0x807D0004
		opword 0x546005EF
		opword 0x41820030
		opword 0x801D0160
		opword 0x2C00000C
		opword 0x4082036C
		opword 0x38000001
		opword 0x3C600002
		opword 0x901D0190
		opword 0x38000000
		opword 0x38630012
		opword 0x901D0194
		bl psndSFXOn
		opword 0x4800034C
		opword 0x546005AD
		opword 0x418200E4
		opword 0x3C600002
		opword 0x38630013
		bl psndSFXOn
		opword 0xA01D0000
		opword 0x540004A5
		opword 0x418200B0
		la r3, str_8041D580(r2)
		la r4, str_8041D580(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820050
		bl marioGetColor
		opword 0x2C030002
		opword 0x41820034
		opword 0x40800014
		opword 0x2C030000
		opword 0x41820018
		opword 0x4080001C
		opword 0x48000080
		opword 0x2C030004
		opword 0x40800078
		opword 0x4800001C
		la r30, str_8041D580(r2)
		opword 0x4800006C
		la r30, str_8041D704(r2)
		opword 0x48000064
		la r30, str_8041D708(r2)
		opword 0x4800005C
		la r30, str_8041D70C(r2)
		opword 0x48000054
		bl marioGetColor
		opword 0x2C030002
		opword 0x41820034
		opword 0x40800014
		opword 0x2C030000
		opword 0x41820018
		opword 0x4080001C
		opword 0x48000034
		opword 0x2C030004
		opword 0x4080002C
		opword 0x4800001C
		la r30, str_8041D58C(r2)
		opword 0x48000020
		la r30, str_8041D710(r2)
		opword 0x48000018
		la r30, str_8041D718(r2)
		opword 0x48000010
		la r30, str_8041D720(r2)
		opword 0x48000008
		la r30, str_8041D578(r2)
		opword 0x807D0188
		opword 0x7FC4F378
		opword 0x38A00000
		bl animPoseSetAnim
		opword 0x3860FFFF
		opword 0x4800066C
		opword 0x546004E7
		opword 0x4182000C
		opword 0x3860FFFE
		opword 0x4800065C
		opword 0x807D0010
		opword 0x546004E7
		opword 0x41820090
		opword 0x801D0160
		lis r3, linkDt@ha
		addi r30, r3, linkDt@l
		opword 0x1C00001C
		opword 0x7C7E0214
		opword 0x88030018
		opword 0x901D0160
		opword 0x801D0160
		opword 0x1C00001C
		add r28, r30, r0
		opword 0x801D0160
		opword 0x2C00000B
		opword 0x4182000C
		opword 0x2C00000C
		opword 0x40820014
		opword 0x801D0198
		opword 0x2C000000
		opword 0x40820038
		opword 0x4800001C
		opword 0xA07C0010
		opword 0x28030000
		opword 0x41820028
		bl pouchCheckItem
		opword 0x2C030000
		opword 0x4082001C
		opword 0x881C0018
		opword 0x901D0160
		opword 0x801D0160
		opword 0x1C00001C
		opword 0x7F9E0214
		opword 0x4BFFFFB0
		opword 0x3C600002
		opword 0x38630005
		bl psndSFXOn
		opword 0x480001BC
		opword 0x546004A5
		opword 0x41820090
		opword 0x801D0160
		lis r3, linkDt@ha
		addi r30, r3, linkDt@l
		opword 0x1C00001C
		opword 0x7C7E0214
		opword 0x88030019
		opword 0x901D0160
		opword 0x801D0160
		opword 0x1C00001C
		opword 0x7F9E0214
		opword 0x801D0160
		opword 0x2C00000B
		opword 0x4182000C
		opword 0x2C00000C
		opword 0x40820014
		opword 0x801D0198
		opword 0x2C000000
		opword 0x40820038
		opword 0x4800001C
		opword 0xA07C0010
		opword 0x28030000
		opword 0x41820028
		bl pouchCheckItem
		opword 0x2C030000
		opword 0x4082001C
		opword 0x881C0019
		opword 0x901D0160
		opword 0x801D0160
		opword 0x1C00001C
		opword 0x7F9E0214
		opword 0x4BFFFFB0
		opword 0x3C600002
		opword 0x38630005
		bl psndSFXOn
		opword 0x48000128
		opword 0x54600463
		opword 0x41820090
		opword 0x801D0160
		lis r3, linkDt@ha
		addi r30, r3, linkDt@l
		opword 0x1C00001C
		opword 0x7C7E0214
		opword 0x8803001A
		opword 0x901D0160
		opword 0x801D0160
		opword 0x1C00001C
		opword 0x7F9E0214
		opword 0x801D0160
		opword 0x2C00000B
		opword 0x4182000C
		opword 0x2C00000C
		opword 0x40820014
		opword 0x801D0198
		opword 0x2C000000
		opword 0x40820038
		opword 0x4800001C
		opword 0xA07C0010
		opword 0x28030000
		opword 0x41820028
		bl pouchCheckItem
		opword 0x2C030000
		opword 0x4082001C
		opword 0x881C001A
		opword 0x901D0160
		opword 0x801D0160
		opword 0x1C00001C
		opword 0x7F9E0214
		opword 0x4BFFFFB0
		opword 0x3C600002
		opword 0x38630005
		bl psndSFXOn
		opword 0x48000094
		opword 0x54600421
		opword 0x4182008C
		opword 0x801D0160
		lis r3, linkDt@ha
		addi r30, r3, linkDt@l
		opword 0x1C00001C
		opword 0x7C7E0214
		opword 0x8803001B
		opword 0x901D0160
		opword 0x801D0160
		opword 0x1C00001C
		opword 0x7F9E0214
		opword 0x801D0160
		opword 0x2C00000B
		opword 0x4182000C
		opword 0x2C00000C
		opword 0x40820014
		opword 0x801D0198
		opword 0x2C000000
		opword 0x40820038
		opword 0x4800001C
		opword 0xA07C0010
		opword 0x28030000
		opword 0x41820028
		bl pouchCheckItem
		opword 0x2C030000
		opword 0x4082001C
		opword 0x881C001B
		opword 0x901D0160
		opword 0x801D0160
		opword 0x1C00001C
		opword 0x7F9E0214
		opword 0x4BFFFFB0
		opword 0x3C600002
		opword 0x38630005
		bl psndSFXOn
		opword 0x80BD0160
		opword 0x3C004330
		lis r4, linkDt@ha
		lis r3, double_to_int_802f5e78@ha
		opword 0x1CA5001C
		stw r0, _af_pad+0(r1)
		addi r4, r4, linkDt@l
		lfd f1, double_to_int_802f5e78@l(r3)
		opword 0x90010010
		opword 0x7FC42A14
		opword 0xA81E0000
		opword 0x6C008000
		opword 0x9001000C
		opword 0xC8010008
		opword 0xEC000828
		opword 0xD01D0158
		opword 0xA81E0002
		opword 0x6C008000
		opword 0x90010014
		opword 0xC8010010
		opword 0xEC000828
		opword 0xD01D015C
		opword 0x801D0160
		opword 0x2C000002
		opword 0x41820008
		opword 0x4800012C
		opword 0xA01D0000
		opword 0x540004A5
		opword 0x418200B0
		opword 0x807E000C
		la r4, str_8041D580(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820050
		bl marioGetColor
		opword 0x2C030002
		opword 0x41820034
		opword 0x40800014
		opword 0x2C030000
		opword 0x41820018
		opword 0x4080001C
		opword 0x4800008C
		opword 0x2C030004
		opword 0x40800084
		opword 0x4800001C
		la r31, str_8041D580(r2)
		opword 0x48000078
		la r31, str_8041D704(r2)
		opword 0x48000070
		la r31, str_8041D708(r2)
		opword 0x48000068
		la r31, str_8041D70C(r2)
		opword 0x48000060
		bl marioGetColor
		opword 0x2C030002
		opword 0x41820034
		opword 0x40800014
		opword 0x2C030000
		opword 0x41820018
		opword 0x4080001C
		opword 0x48000040
		opword 0x2C030004
		opword 0x40800038
		opword 0x4800001C
		la r31, str_8041D58C(r2)
		opword 0x4800002C
		la r31, str_8041D710(r2)
		opword 0x48000024
		la r31, str_8041D718(r2)
		opword 0x4800001C
		la r31, str_8041D720(r2)
		opword 0x48000014
		bl pouchGetHammerLv
		opword 0x5460103A
		la r3, hammer_pose(r13)
		opword 0x7FE3002E
		opword 0x807D0188
		opword 0x7FE4FB78
		opword 0x38A00000
		bl animPoseSetAnim
		opword 0x807D018C
		opword 0x2C030000
		opword 0x40820028
		opword 0x807D0188
		bl animPoseGetLoopTimes
		lfs f0, float_0p89_8041d728(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820018
		opword 0x3800001E
		opword 0x901D018C
		opword 0x4800000C
		opword 0x3803FFFF
		opword 0x901D018C
		opword 0xA01D0000
		opword 0x540004A5
		opword 0x418200E4
		opword 0x38000000
		opword 0x901D018C
		opword 0x480000D8
		opword 0x38000000
		opword 0x901D018C
		opword 0xA01D0000
		opword 0x540004A5
		opword 0x418200B0
		opword 0x807E000C
		la r4, str_8041D580(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820050
		bl marioGetColor
		opword 0x2C030002
		opword 0x41820034
		opword 0x40800014
		opword 0x2C030000
		opword 0x41820018
		opword 0x4080001C
		opword 0x48000080
		opword 0x2C030004
		opword 0x40800078
		opword 0x4800001C
		la r31, str_8041D580(r2)
		opword 0x4800006C
		la r31, str_8041D704(r2)
		opword 0x48000064
		la r31, str_8041D708(r2)
		opword 0x4800005C
		la r31, str_8041D70C(r2)
		opword 0x48000054
		bl marioGetColor
		opword 0x2C030002
		opword 0x41820034
		opword 0x40800014
		opword 0x2C030000
		opword 0x41820018
		opword 0x4080001C
		opword 0x48000034
		opword 0x2C030004
		opword 0x4080002C
		opword 0x4800001C
		la r31, str_8041D58C(r2)
		opword 0x48000020
		la r31, str_8041D710(r2)
		opword 0x48000018
		la r31, str_8041D718(r2)
		opword 0x48000010
		la r31, str_8041D720(r2)
		opword 0x48000008
		opword 0x83FE0004
		opword 0x807D0188
		opword 0x7FE4FB78
		opword 0x38A00000
		bl animPoseSetAnim
		opword 0x801D0160
		opword 0x2C000003
		opword 0x41820038
		opword 0x40800058
		opword 0x2C000002
		opword 0x40800008
		opword 0x4800004C
		bl pouchGetHammerLv
		opword 0x5460103A
		la r3, hammer_help(r13)
		opword 0x7CA3002E
		opword 0x7FA3EB78
		opword 0x38800000
		opword 0x38C00000
		bl winMsgEntry
		opword 0x48000164
		bl pouchGetJumpLv
		opword 0x5460103A
		la r3, boots_help(r13)
		opword 0x7CA3002E
		opword 0x7FA3EB78
		opword 0x38800000
		opword 0x38C00000
		bl winMsgEntry
		opword 0x48000140
		opword 0x80BE0014
		opword 0x7FA3EB78
		opword 0x38800000
		opword 0x38C00000
		bl winMsgEntry
		opword 0x48000128
		opword 0x807D0010
		opword 0x546004E7
		opword 0x41820038
		opword 0x807D0194
		opword 0x3803FFFF
		opword 0x901D0194
		opword 0x801D0194
		opword 0x2C000000
		opword 0x40800010
		opword 0x807D0198
		opword 0x3803FFFF
		opword 0x901D0194
		opword 0x3C600002
		opword 0x38630005
		bl psndSFXOn
		opword 0x48000074
		opword 0x546004A5
		opword 0x41820038
		opword 0x807D0194
		opword 0x38030001
		opword 0x901D0194
		opword 0x807D0194
		opword 0x801D0198
		opword 0x7C030000
		opword 0x4180000C
		opword 0x38000000
		opword 0x901D0194
		opword 0x3C600002
		opword 0x38630005
		bl psndSFXOn
		opword 0x48000038
		opword 0x807D0004
		opword 0x546005AD
		opword 0x4182001C
		opword 0x38000000
		opword 0x3C600002
		opword 0x901D0190
		opword 0x38630013
		bl psndSFXOn
		opword 0x48000014
		opword 0x546004E7
		opword 0x4182000C
		opword 0x3860FFFE
		opword 0x4800007C
		lfs f0, float_neg280_8041d72c(r2)
		opword 0x3C004330
		lis r4, double_to_int_802f5e78@ha
		lis r3, superActionTable@ha
		opword 0xD01D0158
		addi r5, r3, superActionTable@l
		lfd f3, double_to_int_802f5e78@l(r4)
		opword 0x7FA3EB78
		opword 0x80DD0194
		opword 0x38800000
		opword 0x90010010
		opword 0x6CC08000
		lfs f4, float_26_8041d734(r2)
		opword 0x90010014
		opword 0x38C00000
		lfs f1, float_120_8041d730(r2)
		opword 0xC8410010
		lfs f0, float_12_8041d670(r2)
		opword 0xEC421828
		lfs f3, float_10_8041d61c(r2)
		opword 0xEC2408BC
		opword 0xEC010028
		opword 0xEC03002A
		opword 0xD01D015C
		opword 0x801D0194
		opword 0x5400103A
		opword 0x7CA5002E
		opword 0x80A5000C
		bl winMsgEntry
		opword 0x38600000
	}
}
#pragma pop

void winMarioMain2(void) {
}


// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const char str_802F5650[20] = "msg_menu_mario_lv\0\0";
__declspec(section ".rodata") const char str_802F5664[24] = "msg_menu_mario_star_r\0\0";
__declspec(section ".rodata") const char str_802F567C[20] = "msg_menu_mario_hp\0\0";
__declspec(section ".rodata") const char str_802F5690[20] = "msg_menu_mario_fp\0\0";
__declspec(section ".rodata") const char str_802F56A4[20] = "msg_menu_mario_bp\0\0";
__declspec(section ".rodata") const char str_802F56B8[12] = "msg_slit\0\0\0";
__declspec(section ".rodata") const char str_802F56C4[12] = "msg_plane\0\0";
__declspec(section ".rodata") const char str_802F56D0[12] = "msg_ship\0\0\0";
__declspec(section ".rodata") const char str_802F56DC[12] = "msg_roll\0\0\0";
__declspec(section ".rodata") const char str_802F56E8[20] = "msg_menu_star_power";
__declspec(section ".rodata") const char str_802F56FC[20] = "msg_menu_mario_waza";
__declspec(section ".rodata") const char str_802F5710[24] = "msg_menu_mario_star_p\0\0";
__declspec(section ".rodata") const char str_802F5728[20] = "msg_menu_mario_coin";
__declspec(section ".rodata") const char str_802F573C[24] = "msg_menu_mario_kakera\0\0";
__declspec(section ".rodata") const char str_802F5754[24] = "msg_menu_mario_scoin\0\0\0";
__declspec(section ".rodata") const char str_802F576C[20] = "msg_menu_mario_time";
__declspec(section ".rodata") const char str_802F5780[16] = "msg_hammer_1\0\0\0";
__declspec(section ".rodata") const char str_802F5790[16] = "msg_hammer_2\0\0\0";
__declspec(section ".rodata") const char str_802F57A0[16] = "msg_hammer_3\0\0\0";
__declspec(section ".rodata") const char str_802F57B0[12] = "msg_boots_1";
__declspec(section ".rodata") const char str_802F57BC[12] = "msg_boots_2";
__declspec(section ".rodata") const char str_802F57C8[12] = "msg_boots_3";
__declspec(section ".rodata") const u32 jumptable_802F57D4[20] = {(u32)(char*)&str_8041D5A8, (u32)(char*)&str_8041D5AC, (u32)(char*)&str_8041D5B0, (u32)(char*)&str_8041D5B4, (u32)(char*)&str_8041D5B8, (u32)(char*)&str_8041D5BC, (u32)(char*)&str_8041D5C0, (u32)(char*)&str_8041D5C4, (u32)(char*)&str_8041D5C8, (u32)(char*)&str_8041D5CC, (u32)(char*)&str_8041D5A8, (u32)(char*)&str_8041D5AC, (u32)(char*)&str_8041D5B0, (u32)(char*)&str_8041D5B4, (u32)(char*)&str_8041D5B8, (u32)(char*)&str_8041D5BC, (u32)(char*)&str_8041D5C0, (u32)(char*)&str_8041D5C4, (u32)(char*)&str_8041D5C8, (u32)(char*)&str_8041D5CC};
__declspec(section ".rodata") const f32 vec3_802f5824[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5830[3] = {0.8f, 0.8f, 0.8f};
__declspec(section ".rodata") const f32 vec3_802f583c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5848[3] = {0.8f, 0.8f, 0.8f};
__declspec(section ".rodata") const f32 vec3_802f5854[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5860[3] = {0.7f, 0.7f, 0.7f};
__declspec(section ".rodata") const f32 vec3_802f586c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5878[3] = {-0.8f, 0.8f, 0.8f};
__declspec(section ".rodata") const f32 vec3_802f5884[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5890[3] = {-0.8f, 0.8f, 0.8f};
__declspec(section ".rodata") const f32 vec3_802f589c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f58a8[3] = {0.7f, 0.7f, 0.7f};
__declspec(section ".rodata") const f32 vec3_802f58b4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f58c0[3] = {0.8f, 0.8f, 0.8f};
__declspec(section ".rodata") const f32 vec3_802f58cc[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f58d8[3] = {0.6f, 0.6f, 0.6f};
__declspec(section ".rodata") const f32 vec3_802f58e4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f58f0[3] = {0.8f, 0.8f, 0.8f};
__declspec(section ".rodata") const f32 vec3_802f58fc[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5908[3] = {0.8f, 0.8f, 0.8f};
__declspec(section ".rodata") const f32 vec3_802f5914[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5920[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f592c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5938[3] = {0.7f, 0.7f, 0.7f};
__declspec(section ".rodata") const u32 dat_802f5944[3] = {0xCB8CA2FE, 0xCBBE89FE, 0x94B9C7FE};
__declspec(section ".rodata") const u32 dat_802f5950[3] = {0xA73C3CFF, 0x37691EFF, 0x0F217AFF};
__declspec(section ".rodata") const u32 N_stat_name_tbl[3] = {(u32)(char*)&str_8041D5F0, (u32)(char*)&str_8041D5F8, (u32)(char*)&str_8041D600};
__declspec(section ".rodata") const char str_802F5968[24] = "msg_menu_mario_ruby_hp\0";
__declspec(section ".rodata") const char str_802F5980[24] = "msg_menu_mario_ruby_fp\0";
__declspec(section ".rodata") const char str_802F5998[24] = "msg_menu_mario_ruby_bp\0";
__declspec(section ".rodata") const u32 jumptable_802F59B0[3] = {(u32)(char*)&str_802F5968, (u32)(char*)&str_802F5980, (u32)(char*)&str_802F5998};
__declspec(section ".rodata") const f32 vec3_802f59bc[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f59c8[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f59d4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f59e0[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f59ec[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f59f8[3] = {0.5f, 0.5f, 0.5f};
__declspec(section ".rodata") const f32 vec3_802f5a04[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5a10[3] = {0.82f, 0.82f, 0.82f};
__declspec(section ".rodata") const f32 vec3_802f5a1c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5a28[3] = {0.82f, 0.82f, 0.82f};
__declspec(section ".rodata") const f32 vec3_802f5a34[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5a40[3] = {0.82f, 0.82f, 0.82f};
__declspec(section ".rodata") const f32 vec3_802f5a4c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5a58[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f5a64[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5a70[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f5a7c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5a88[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f5a94[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5aa0[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f5aac[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5ab8[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f5ac4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5ad0[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f5adc[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5ae8[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f5af4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5b00[3] = {0.8f, 0.8f, 0.8f};
__declspec(section ".rodata") const f32 vec3_802f5b0c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5b18[3] = {0.8f, 0.8f, 0.8f};
__declspec(section ".rodata") const f32 vec3_802f5b24[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5b30[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f5b3c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5b48[3] = {0.8f, 0.8f, 0.8f};
__declspec(section ".rodata") const f32 vec3_802f5b54[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5b60[3] = {0.8f, 0.8f, 0.8f};
__declspec(section ".rodata") const f32 vec3_802f5b6c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5b78[3] = {0.62f, 0.62f, 0.62f};
__declspec(section ".rodata") const f32 vec3_802f5b84[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5b90[3] = {0.62f, 0.62f, 0.62f};
__declspec(section ".rodata") const f32 vec3_802f5b9c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5ba8[3] = {0.62f, 0.62f, 0.62f};
__declspec(section ".rodata") const f32 vec3_802f5bb4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5bc0[3] = {0.62f, 0.62f, 0.62f};
__declspec(section ".rodata") const f32 vec3_802f5bcc[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5bd8[3] = {0.62f, 0.62f, 0.62f};
__declspec(section ".rodata") const f32 vec3_802f5be4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5bf0[3] = {0.9f, 0.9f, 0.9f};
__declspec(section ".rodata") const f32 vec3_802f5bfc[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5c08[3] = {0.9f, 0.9f, 0.9f};
__declspec(section ".rodata") const f32 vec3_802f5c14[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5c20[3] = {0.9f, 0.9f, 0.9f};
__declspec(section ".rodata") const f32 vec3_802f5c2c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5c38[3] = {0.9f, 0.9f, 0.9f};
__declspec(section ".rodata") const f32 vec3_802f5c44[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5c50[3] = {0.9f, 0.9f, 0.9f};
__declspec(section ".rodata") const f32 vec3_802f5c5c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5c68[3] = {0.9f, 0.9f, 0.9f};
__declspec(section ".rodata") const f32 vec3_802f5c74[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5c80[3] = {0.9f, 0.9f, 0.9f};
__declspec(section ".rodata") const f32 vec3_802f5c8c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5c98[3] = {0.9f, 0.9f, 0.9f};
__declspec(section ".rodata") const f32 vec3_802f5ca4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5cb0[3] = {0.9f, 0.9f, 0.9f};
__declspec(section ".rodata") const f32 vec3_802f5cbc[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5cc8[3] = {0.9f, 0.9f, 0.9f};
__declspec(section ".rodata") const f32 vec3_802f5cd4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5ce0[3] = {0.9f, 0.9f, 0.9f};
__declspec(section ".rodata") const f32 vec3_802f5cec[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5cf8[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f5d04[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5d10[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f5d1c[3] = {0.0f, 155.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5d28[3] = {0.8f, 0.8f, 0.8f};
__declspec(section ".rodata") const f32 vec3_802f5d34[3] = {0.0f, 155.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5d40[3] = {0.8f, 0.8f, 0.8f};
__declspec(section ".rodata") const f32 vec3_802f5d4c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5d58[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f5d64[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5d70[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f5d7c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f5d88[3] = {0.5f, 0.5f, 0.5f};
__declspec(section ".rodata") const char str_802F5D94[12] = "name_mario\0";
__declspec(section ".rodata") const char str_802F5DA0[24] = "msg_menu_mario_level\0\0\0";
__declspec(section ".rodata") const char str_802F5DB8[24] = "msg_menu_mario_special\0";
__declspec(section ".rodata") const char str_802F5DD0[24] = "msg_menu_mario_num_sp\0\0";
__declspec(section ".rodata") const char str_802F5DE8[24] = "msg_menu_mario_num_coin";
__declspec(section ".rodata") const char str_802F5E00[28] = "msg_menu_mario_num_hoshi\0\0\0";
__declspec(section ".rodata") const char str_802F5E1C[32] = "msg_menu_mario_num_super_coin\0\0";
__declspec(section ".rodata") const char str_802F5E3C[28] = "msg_menu_mario_num_playtime";
__declspec(section ".rodata") const char str_802F5E58[24] = "msg_menu_mario_sac_waza";
__declspec(section ".rodata") const f64 double_to_int_mask_802f5e70 = 4503599627370496.0;
__declspec(section ".rodata") const f64 double_to_int_802f5e78 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802F5E80[8] = "d_mario";
__declspec(section ".rodata") const char str_802F5E88[8] = "a_mario";
__declspec(section ".rodata") const char str_802F5E90[12] = "a_mario_l\0\0";
__declspec(section ".rodata") const char str_802F5E9C[12] = "a_mario_w\0\0";
__declspec(section ".rodata") const char str_802F5EA8[12] = "a_mario_wl\0";
__declspec(section ".rodata") const u32 gap_04_802F5EB4_rodata = 0x00000000;
__declspec(section ".sdata2") const char str_8041D578[8] = "M_S_1\0\0";
__declspec(section ".sdata2") const char str_8041D580[4] = "S_1";
__declspec(section ".sdata2") const char str_8041D584[8] = "M_H_1\0\0";
__declspec(section ".sdata2") const char str_8041D58C[4] = "R_1";
__declspec(section ".sdata2") const char str_8041D590[8] = "M_R_1\0\0";
__declspec(section ".sdata2") const char str_8041D598[8] = "M_H_4\0\0";
__declspec(section ".sdata2") const char str_8041D5A0[8] = "M_H_7\0\0";
__declspec(section ".sdata2") const char str_8041D5A8[4] = "\x82O\0";
__declspec(section ".sdata2") const char str_8041D5AC[4] = "\x82P\0";
__declspec(section ".sdata2") const char str_8041D5B0[4] = "\x82Q\0";
__declspec(section ".sdata2") const char str_8041D5B4[4] = "\x82R\0";
__declspec(section ".sdata2") const char str_8041D5B8[4] = "\x82S\0";
__declspec(section ".sdata2") const char str_8041D5BC[4] = "\x82T\0";
__declspec(section ".sdata2") const char str_8041D5C0[4] = "\x82U\0";
__declspec(section ".sdata2") const char str_8041D5C4[4] = "\x82V\0";
__declspec(section ".sdata2") const char str_8041D5C8[4] = "\x82W\0";
__declspec(section ".sdata2") const char str_8041D5CC[4] = "\x82X\0";
__declspec(section ".sdata2") const u32 dat_8041d5d0 = 0x00000080;
__declspec(section ".sdata2") const u32 dat_8041d5d4 = 0xE1E1E1FE;
__declspec(section ".sdata2") const u32 dat_8041d5d8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d5dc = 0x00000080;
__declspec(section ".sdata2") const u32 dat_8041d5e0 = 0xE1E1E1FE;
__declspec(section ".sdata2") const u32 dat_8041d5e4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d5e8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d5ec = 0x000000FF;
__declspec(section ".sdata2") const char str_8041D5F0[8] = "\x82g\x82o\0\0\0";
__declspec(section ".sdata2") const char str_8041D5F8[8] = "\x82" "e\x82o\0\0\0";
__declspec(section ".sdata2") const char str_8041D600[8] = "\x82" "a\x82o\0\0\0";
__declspec(section ".sdata2") const u32 dat_8041d608 = 0x00000080;
__declspec(section ".sdata2") const f32 float_265_8041d60c = 265.0f;
__declspec(section ".sdata2") const f32 float_154_8041d610 = 154.0f;
__declspec(section ".sdata2") const f32 float_190_8041d614 = 190.0f;
__declspec(section ".sdata2") const f32 float_24_8041d618 = 24.0f;
__declspec(section ".sdata2") const f32 float_10_8041d61c = 10.0f;
__declspec(section ".sdata2") const f32 float_152_8041d620 = 152.0f;
__declspec(section ".sdata2") const f32 float_0p8_8041d624 = 0.8f;
__declspec(section ".sdata2") const f32 float_20_8041d628 = 20.0f;
__declspec(section ".sdata2") const f32 float_142_8041d62c = 142.0f;
__declspec(section ".sdata2") const char str_8041D630[4] = "\x81|\0";
__declspec(section ".sdata2") const f32 float_0_8041d634 = 0.0f;
__declspec(section ".sdata2") const char str_8041D638[4] = "%d\0";
__declspec(section ".sdata2") const char str_8041D63C[4] = "%s\0";
__declspec(section ".sdata2") const f32 float_255_8041d640 = 255.0f;
__declspec(section ".sdata2") const f32 float_112_8041d644 = 112.0f;
__declspec(section ".sdata2") const f32 float_240_8041d648 = 240.0f;
__declspec(section ".sdata2") const f32 float_124_8041d64c = 124.0f;
__declspec(section ".sdata2") const f32 float_270_8041d650 = 270.0f;
__declspec(section ".sdata2") const f32 float_264_8041d654 = 264.0f;
__declspec(section ".sdata2") const f32 float_110_8041d658 = 110.0f;
__declspec(section ".sdata2") const f32 float_50_8041d65c = 50.0f;
__declspec(section ".sdata2") const f32 float_2_8041d660 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041d664 = 0.5f;
__declspec(section ".sdata2") const f32 float_38_8041d668 = 38.0f;
__declspec(section ".sdata2") const f32 float_4_8041d66c = 4.0f;
__declspec(section ".sdata2") const f32 float_12_8041d670 = 12.0f;
__declspec(section ".sdata2") const f32 float_21_8041d674 = 21.0f;
__declspec(section ".sdata2") const f32 float_34_8041d678 = 34.0f;
__declspec(section ".sdata2") const f32 float_68_8041d67c = 68.0f;
__declspec(section ".sdata2") const f32 float_130_8041d680 = 130.0f;
__declspec(section ".sdata2") const f32 float_200_8041d684 = 200.0f;
__declspec(section ".sdata2") const f32 float_260_8041d688 = 260.0f;
__declspec(section ".sdata2") const f32 float_80_8041d68c = 80.0f;
__declspec(section ".sdata2") const f32 float_40_8041d690 = 40.0f;
__declspec(section ".sdata2") const f32 float_106_8041d694 = 106.0f;
__declspec(section ".sdata2") const f32 float_70_8041d698 = 70.0f;
__declspec(section ".sdata2") const f32 float_150_8041d69c = 150.0f;
__declspec(section ".sdata2") const f32 float_28_8041d6a0 = 28.0f;
__declspec(section ".sdata2") const f32 float_56_8041d6a4 = 56.0f;
__declspec(section ".sdata2") const f32 float_84_8041d6a8 = 84.0f;
__declspec(section ".sdata2") const f32 float_35_8041d6ac = 35.0f;
__declspec(section ".sdata2") const f32 float_8_8041d6b0 = 8.0f;
__declspec(section ".sdata2") const f32 float_205_8041d6b4 = 205.0f;
__declspec(section ".sdata2") const f32 float_172_8041d6b8 = 172.0f;
__declspec(section ".sdata2") const f32 float_16_8041d6bc = 16.0f;
__declspec(section ".sdata2") const f32 float_220_8041d6c0 = 220.0f;
__declspec(section ".sdata2") const f32 float_0_8041d6c4 = 0.0f;
__declspec(section ".sdata2") const f32 float_1_8041d6c8 = 1.0f;
__declspec(section ".sdata2") const f32 float_5_8041d6cc = 5.0f;
__declspec(section ".sdata2") const f32 float_160_8041d6d0 = 160.0f;
__declspec(section ".sdata2") const f32 float_254_8041d6d4 = 254.0f;
__declspec(section ".sdata2") const f32 float_90_8041d6d8 = 90.0f;
__declspec(section ".sdata2") const char str_8041D6DC[8] = "\x82r\x82o\0\0\0";
__declspec(section ".sdata2") const f32 float_228_8041d6e4 = 228.0f;
__declspec(section ".sdata2") const f32 float_17_8041d6e8 = 17.0f;
__declspec(section ".sdata2") const f32 float_230_8041d6ec = 230.0f;
__declspec(section ".sdata2") const f32 float_72_8041d6f0 = 72.0f;
__declspec(section ".sdata2") const f32 float_6_8041d6f4 = 6.0f;
__declspec(section ".sdata2") const f32 float_210_8041d6f8 = 210.0f;
__declspec(section ".sdata2") const f32 float_30_8041d6fc = 30.0f;
__declspec(section ".sdata2") const f32 float_60_8041d700 = 60.0f;
__declspec(section ".sdata2") const char str_8041D704[4] = "S_2";
__declspec(section ".sdata2") const char str_8041D708[4] = "S_3";
__declspec(section ".sdata2") const char str_8041D70C[4] = "S_4";
__declspec(section ".sdata2") const char str_8041D710[8] = "R_15\0\0\0";
__declspec(section ".sdata2") const char str_8041D718[8] = "R_17\0\0\0";
__declspec(section ".sdata2") const char str_8041D720[8] = "R_18\0\0\0";
__declspec(section ".sdata2") const f32 float_0p89_8041d728 = 0.89f;
__declspec(section ".sdata2") const f32 float_neg280_8041d72c = -280.0f;
__declspec(section ".sdata2") const f32 float_120_8041d730 = 120.0f;
__declspec(section ".sdata2") const f32 float_26_8041d734 = 26.0f;

// jumptables last, as the target emitted them with their functions
__declspec(section ".data") void* jumptable_80374F08[] = {
    (char*)fukidashi + 0xB44,
    (char*)fukidashi + 0xB44,
    (char*)fukidashi + 0x58,
    (char*)fukidashi + 0x230,
    (char*)fukidashi + 0xB44,
    (char*)fukidashi + 0xB44,
    (char*)fukidashi + 0xB44,
    (char*)fukidashi + 0x408,
    (char*)fukidashi + 0x5D8,
    (char*)fukidashi + 0x7A8,
    (char*)fukidashi + 0x978,
};
#endif
#pragma force_active on
#pragma explicit_zero_data on
__declspec(section ".data") u32 gap_05_80374F34_data[1] = {0};
#pragma explicit_zero_data reset
#ifndef NONMATCHING
#pragma force_active reset
#endif
