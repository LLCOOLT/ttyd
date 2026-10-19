// G5 keepall: asm stopgap reaches data via section-relative relocs; keep it from being stripped
#pragma force_active on
/*
 * Warning, inlining hell
 */
#include "driver/animdrv.h"
#include "driver/dispdrv.h"
#include "driver/mapdrv.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"

#include <stdio.h>

#include <string.h>
#include "driver/camdrv.h"
#include "manager/filemgr.h"
#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
__declspec(section ".rodata") extern const f32 vec3_802c2db0[3];
__declspec(section ".rodata") extern const f32 vec3_802c2dbc[3];
__declspec(section ".rodata") extern const f32 vec3_802c2dc8[3];
__declspec(section ".rodata") extern const f32 vec3_802c2dd4[3];
__declspec(section ".rodata") extern const f64 double_to_int_mask_802c2de0;
__declspec(section ".rodata") extern const char str_802C2DE8[8];
__declspec(section ".rodata") extern const f64 double_to_int_802c2df0;
__declspec(section ".rodata") extern const char str_802C2DF8[];
__declspec(section ".rodata") extern const char str_802C2E44[];
__declspec(section ".rodata") extern const f64 double_10_802c2f20;
__declspec(section ".rodata") extern const char str_802C2F28[12];
__declspec(section ".rodata") extern const char str_802C2F34[12];
__declspec(section ".rodata") extern const char str_802C2F40[12];
__declspec(section ".rodata") extern const char str_802C2F4C[12];
__declspec(section ".rodata") extern const char str_802C2F58[16];
__declspec(section ".rodata") extern const char str_802C2F68[12];
__declspec(section ".rodata") extern const u32 gap_04_802C2F74_rodata;
__declspec(section ".sdata2") extern const u32 dat_80419a28;
__declspec(section ".sdata2") extern const u32 dat_80419a2c;
__declspec(section ".sdata2") extern const u32 dat_80419a30;
__declspec(section ".sdata2") extern const u32 dat_80419a34;
__declspec(section ".sdata2") extern const u32 dat_80419a38;
__declspec(section ".sdata2") extern const u32 dat_80419a3c;
__declspec(section ".sdata2") extern const u32 dat_80419a40;
__declspec(section ".sdata2") extern const f32 float_1_80419a44;
__declspec(section ".sdata2") extern const f32 float_0_80419a48;
__declspec(section ".sdata2") extern const f32 float_deg2rad_80419a4c;
__declspec(section ".sdata2") extern const u32 zero_80419a50;
__declspec(section ".sdata2") extern const char str_80419A54[8];
__declspec(section ".sdata2") extern const char str_80419A5C[4];
__declspec(section ".sdata2") extern const f32 float_16p667_80419a60;
__declspec(section ".sdata2") extern const f32 float_0p5_80419a64;
__declspec(section ".sdata2") extern const f32 float_0p75_80419a68;
__declspec(section ".sdata2") extern const f32 float_0p25_80419a6c;
__declspec(section ".sdata2") extern const f32 float_8_80419a70;
__declspec(section ".sdata2") extern const f32 float_25p74_80419a74;
__declspec(section ".sdata2") extern const f32 float_0p14881_80419a78;
__declspec(section ".sdata2") extern const f32 float_150_80419a7c;
__declspec(section ".sdata2") extern const f32 float_215_80419a80;
__declspec(section ".sdata2") extern const f32 float_2_80419a84;
__declspec(section ".sdata2") extern const f32 float_neg0p5_80419a88;
__declspec(section ".sdata2") extern const f32 float_neg1_80419a8c;
__declspec(section ".sdata2") extern const f32 float_neg90_80419a90;
__declspec(section ".sdata2") extern const f32 float_rad2deg_80419a94;
__declspec(section ".sdata2") extern const f32 float_360_80419a98;
__declspec(section ".sdata2") extern const f32 float_neg360_80419a9c;
__declspec(section ".sdata2") extern const f32 float_90_80419aa0;
__declspec(section ".sdata2") extern const f32 float_270_80419aa4;
__declspec(section ".sdata2") extern const f32 float_neg270_80419aa8;
__declspec(section ".sdata2") extern const f32 float_180_80419aac;
__declspec(section ".sdata2") extern const f32 float_neg180_80419ab0;
__declspec(section ".sdata2") extern const f32 float_0p1_80419ab4;
__declspec(section ".sdata2") extern const f32 float_neg2_80419ab8;
__declspec(section ".sdata2") extern const f32 float_neg3_80419abc;
__declspec(section ".sdata2") extern const f32 float_0p04_80419ac0;
__declspec(section ".sdata2") extern const f32 float_60_80419ac4;
__declspec(section ".sdata2") extern const f32 float_1000_80419ac8;
__declspec(section ".sdata2") extern const f32 float_0p0625_80419acc;
__declspec(section ".sdata2") extern const f32 float_3_80419ad0;
__declspec(section ".sdata2") extern const f32 float_deg2rad_80419ad4;
#endif
extern const char str_802C2A98[];
extern const char str_802C2AA4[];
extern const char str_802C2AB4[];
extern const char str_802C2AC4[];
extern const char str_802C2AD4[];
extern const char str_802C2AE4[];
extern const char str_802C2AF4[];
extern const char str_802C2B04[];
extern const char str_802C2B14[];
extern const char str_802C2B24[];
extern const char str_802C2B34[];
extern const char str_802C2B44[];
extern const char str_802C2B54[];
extern const char str_802C2B64[];
extern const char str_802C2B74[];
extern const char str_802C2B84[];
extern const char str_802C2B94[];
extern const char str_802C2BA4[];
extern const char str_802C2BB4[];
extern const char str_802C2BC4[];
extern const char str_802C2BD4[];
extern const char str_802C2BE4[];
extern const char str_802C2BF4[];
extern const char str_802C2C04[];
extern const char str_802C2C18[];
extern const char str_802C2C2C[];
extern const char str_802C2C40[];
extern const char str_802C2C54[];
extern const char str_802C2C68[];
extern const char str_802C2C7C[];
extern const char str_802C2C90[];
extern const char str_802C2CA4[];
extern const char str_802C2CB4[];
extern const char str_802C2CC4[];
extern const char str_802C2CD4[];
extern const char str_802C2CE4[];
extern const char str_802C2CF4[];
extern const char str_802C2D04[];
extern const char str_802C2D14[];
extern const char str_802C2D24[];
extern const char str_802C2D34[];
extern const char str_802C2D44[];
extern const char str_802C2D54[];
extern const char str_802C2D64[];
extern const char str_802C2D74[];
extern const char str_802C2D84[];
extern const char str_802C2D94[];
extern const char str_802C2DA4[];

#define TESTHEAP_SIZE (u32)(1.5 * 1024 * 1024)
#define PI 3.14159265358979323846264338327950288419716939937510f

extern GlobalWork* gp;
extern int sprintf(char* str, const char* format, ...);
extern double tan(double arg);

//.data
u8 _vivihimoData[0xC00] ATTRIBUTE_ALIGN(32) = {  // G5: target .data is 32-aligned
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD, 0x3F, 0x99, 0x99, 0x9A, 0x3F, 0x4C, 0xCC, 0xCD,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD, 0x3F, 0x33, 0x33, 0x33,
    0x3F, 0x00, 0x00, 0x00, 0x3F, 0x33, 0x33, 0x33, 0x3E, 0xCC, 0xCC, 0xCD, 0x3F, 0x33, 0x33, 0x33,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3E, 0x4C, 0xCC, 0xCD, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3E, 0x4C, 0xCC, 0xCD, 0x3F, 0x4C, 0xCC, 0xCD, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD,
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD,
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD, 0x3F, 0x66, 0x66, 0x66, 0x3F, 0x33, 0x33, 0x33,
    0x3F, 0x19, 0x99, 0x9A, 0x3F, 0x33, 0x33, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
};

typedef struct MoaChain {
    const char* a;
    const char* b;
} MoaChain;
#ifdef NONMATCHING
const s32 dat_80419a28 = 0x2F;
#endif
MoaChain g_moamoa_chain_tbl[47] = {
    { str_802C2A98, str_802C2AA4 },
    { str_802C2AA4, str_802C2AB4 },
    { str_802C2AB4, str_802C2AC4 },
    { str_802C2AC4, str_802C2AD4 },
    { str_802C2AD4, str_802C2AE4 },
    { str_802C2A98, str_802C2AF4 },
    { str_802C2AF4, str_802C2B04 },
    { str_802C2B04, str_802C2B14 },
    { str_802C2B14, str_802C2B24 },
    { str_802C2B24, str_802C2B34 },
    { str_802C2A98, str_802C2B44 },
    { str_802C2B44, str_802C2B54 },
    { str_802C2B54, str_802C2B64 },
    { str_802C2B64, str_802C2B74 },
    { str_802C2B74, str_802C2B84 },
    { str_802C2A98, str_802C2B94 },
    { str_802C2B94, str_802C2BA4 },
    { str_802C2BA4, str_802C2BB4 },
    { str_802C2BB4, str_802C2BC4 },
    { str_802C2BC4, str_802C2BD4 },
    { str_802C2BD4, str_802C2BE4 },
    { str_802C2BE4, str_802C2BF4 },
    { str_802C2BF4, str_802C2C04 },
    { str_802C2C04, str_802C2C18 },
    { str_802C2C18, str_802C2C2C },
    { str_802C2C2C, str_802C2C40 },
    { str_802C2BF4, str_802C2C54 },
    { str_802C2C54, str_802C2C68 },
    { str_802C2C68, str_802C2C7C },
    { str_802C2C7C, str_802C2C90 },
    { str_802C2A98, str_802C2CA4 },
    { str_802C2CA4, str_802C2CB4 },
    { str_802C2CB4, str_802C2CC4 },
    { str_802C2CC4, str_802C2CD4 },
    { str_802C2A98, str_802C2CE4 },
    { str_802C2CE4, str_802C2CF4 },
    { str_802C2CF4, str_802C2D04 },
    { str_802C2D04, str_802C2D14 },
    { str_802C2A98, str_802C2D24 },
    { str_802C2D24, str_802C2D34 },
    { str_802C2D34, str_802C2D44 },
    { str_802C2D44, str_802C2D54 },
    { str_802C2A98, str_802C2D64 },
    { str_802C2D64, str_802C2D74 },
    { str_802C2D74, str_802C2D84 },
    { str_802C2D84, str_802C2D94 },
    { str_802C2A98, str_802C2DA4 },
};

//.bss
extern Mtx g_modeling_mtx_stack[32];
extern AnimationWork work;
extern f32 tanfTbl[0xB2];

//.sdata
s32 vivihimoTailGroupNo[4] ATTRIBUTE_ALIGN(32) = { 0, 2, -1, -1 };  // G5: target .sdata is 32-aligned
__declspec(section ".sdata") void* vivihimoData[4] = {
    NULL,
    (u8*)&_vivihimoData,
    (u8*)&_vivihimoData + 0x400,
    (u8*)&_vivihimoData + 0x800,
};
static AnimationWork* wp = &work;

//.sbss
#ifdef NONMATCHING
s32 anim_unused_sbss;
#endif
static u8 gap_08_8041868C_sbss[4];  // .sbss pad after g_modeling_mtx
Mtx* g_modeling_mtx;
s32 g_modeling_mtx_lv;
static u32 g5_mtx_s1454[12];  // target g5_mtx_s1454 (function-local static of an asm function)

// local declarations
void animPoseRefresh(void);
void animPaperPoseDisp(CameraId camId, void* param);
void animPoseDrawMtx(s32 poseId, Mtx matrix, s32 xluMode, f32 rotY, f32 scale);
void animPaperPoseDispSub(s32 unused, AnimationPose* pose);
void renderProc(s32 shapeId, s32 unused);
void pushGXModelMtx_JointNode__(AnimPoseNode* node, f32 sx, f32 sy, f32 sz);
void pushGXModelMtx_TransformNode__(AnimPoseNode* node);
void evalProc(s32 parentId, s32 groupId);


AnimationWork* animGetPtr(void) {
    return wp;
}

OSTime animTimeGetTime(BOOL globalTime) {
    if (globalTime == FALSE) {
        return OSTicksToMilliseconds(gp->renderFieldTime);
    }
    return OSTicksToMilliseconds(gp->renderTime);
}

void initTestHeap(void) {
    if (!wp->testHeap) { // allocate 1.5MiB test heap
        wp->testHeap = __memAlloc(HEAP_DEFAULT, TESTHEAP_SIZE);
    }
    wp->testAlloc = (u32)wp->testHeap;
}

// heavily inlined
void* testAlloc(u32 size) {
    void* alloc = (void*)wp->testAlloc;

    if (size & 31) {
        size += 32 - (size & 31);
    }
    wp->testAlloc += size;
    if ((u32)wp->testAlloc >= (u32)wp->testHeap + TESTHEAP_SIZE) { // need to allocate more
        animPoseRefresh();
        alloc = testAlloc(size);
    }
    return alloc;
}

void DCFlushRange(void* addr, u32 nBytes);
GXRenderModeObj* DEMOGetRenderModeObj(void);
void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXClearBoundingBox(void);
void GXClearVtxDesc(void);
void GXCopyTex(void* dest, GXBool clear);
u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, u8 mipmap, u8 max_lod);
void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap);
void GXInitTexObjCI(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXCITexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap, u32 tlut_name);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
    f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
    GXBool do_edge_lod, GXAnisotropy max_aniso);
void GXInitTlutObj(GXTlutObj* tlut_obj, void* lut, GXTlutFmt fmt, u16 n_entries);
void GXInvalidateVtxCache(void);
void GXLoadNrmMtxImm(const f32 mtx[3][4], u32 id);
void GXLoadPosMtxImm(const f32 mtx[3][4], u32 id);
void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXLoadTlut(GXTlutObj* tlut_obj, u32 tlut_name);
void GXPixModeSync(void);
void GXReadBoundingBox(u16* left, u16* top, u16* right, u16* bottom);
void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
void GXSetArray(GXAttr attr, void* base_ptr, u8 stride);
void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op);
void GXSetCullMode(GXCullMode mode);
void GXSetCurrentMtx(u32 id);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx);
void GXSetTexCopyDst(u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap);
void GXSetTexCopySrc(u16 left, u16 top, u16 wd, u16 ht);
void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac);
void GXSetVtxDesc(GXAttr attr, GXAttrType type);
void GXSetZCompLoc(GXBool before_tex);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXCopy(const Mtx src, Mtx dst);
void PSMTXIdentity(Mtx m);
u32 PSMTXInvXpose(const Mtx src, Mtx invX);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
TEXDescriptor* TEXGet(TEXPalette* pal, u32 id);
int __cvt_dbl_usll();
int __cvt_ull_flt();
int __div2i();
FileEntry* fileAlloc(const char* filename, s32 type);
FileEntry* fileAllocf(s32 type, const char* format, ...);
void fileFree(FileEntry* handle);
void fileSetCurrentArchiveType(s32 type);
void *memcpy(void *dest, const void *src, size_t num);
int printf(const char *, ...);
int strcmp(const char *s1, const char *s2);
void _animPoseDrawMtx(AnimationPose* pose, Mtx matrix, s32 xluMode, f32 rotY, f32 scale);
void animPose_AllocBuffer(AnimationPose* pose);
void animSetMaterial_Texture(s32 texCount, s32 *texIdRemap, AnimPoseTexEntry *pTexEntries, AnimTexMtx *animEntries, s32 texBindsCapacity, AnimTexBind *texBinds, AnimationTextureFile *texFile);
extern double atan2(double y, double x);
void dispProc(s32 parentId, s32 groupId, s32 xluStage, s32 arg3, f32 arg4);
extern BOOL mapTestXLU(u32 flags, GXColor* color, GXColor* matColor);
void materialProc(s32 shapeId, s32 xluStage);
void vivihimo(Mtx a, Mtx b, f32 speed, f32 scale, f32 offA, f32 offB);
extern void* jumptable_80305118[];
extern void* jumptable_803050D8[];
#ifdef NONMATCHING
void animInit(void) {
    int i;
    FileEntry* file;

    wp->totalFiles = 64; // TODO: #define these?
    wp->totalTextures = 64;
    wp->totalPoses = 256;
    wp->mFloatScratchRP = 1024;
    wp->mFloatScratchWP = 0;
    wp->files = __memAlloc(HEAP_DEFAULT, sizeof(AnimationPoseFile) * wp->totalFiles);
    wp->textures = __memAlloc(HEAP_DEFAULT, sizeof(AnimationTextureFile) * wp->totalTextures);
    wp->poses = __memAlloc(HEAP_DEFAULT, sizeof(AnimationPose) * wp->totalPoses);
    wp->mbUseFloatScratch = 0;
    wp->mpFloatScratch = __memAlloc(HEAP_DEFAULT, sizeof(Vec) * wp->mFloatScratchRP);

    wp->mpTexObjs[0] = NULL;
    wp->mpTexObjs[1] = NULL;
    wp->mpCurTexObj = NULL;

    wp->mpTexDatas[0] = NULL;
    wp->mpTexDatas[1] = NULL;
    wp->mpCurTexData = NULL;

    wp->paperMtxPtr[0] = NULL;
    wp->paperMtxPtr[1] = NULL;
    wp->paperMtxPtr[2] = NULL;

    wp->field_0xD8 = 1;
    wp->field_0xDC = 1;

    wp->testHeap = NULL;
    wp->inBattle = FALSE;
    initTestHeap(); // inlined

    for (i = 0; i < 0xB2; i++) {
        tanfTbl[i] = (f32)tan((i - 0x59) * 0.017453289f);
    }
    file = fileAllocf(0, "a/vivian.bin");
    if (file) {
        memcpy_as4(vivihimoData[1], *file->data, sizeof(_vivihimoData));
        memcpy_as4(vivihimoTailGroupNo, (void*)((u32)*file->data + sizeof(_vivihimoData)), sizeof(vivihimoTailGroupNo));
        fileFree(file);
    }
    fileSetCurrentArchiveType(0);
    wp->mp_ag2tg = fileAllocf(0, "a/ag2tg.bin");
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void animInit(void) {
	char _af_pad[4];
	asm volatile {
		lwz r3, wp(r13)
		opword 0x38E00040
		opword 0x38C00100
		opword 0x38A00400
		opword 0x90E30004
		opword 0x38000000
		opword 0x38600000
		lwz r4, wp(r13)
		opword 0x90E4000C
		lwz r4, wp(r13)
		opword 0x90C40014
		lwz r4, wp(r13)
		opword 0x90A400F0
		lwz r4, wp(r13)
		opword 0x900400F4
		lwz r4, wp(r13)
		opword 0x80040004
		opword 0x54042036
		bl __memAlloc
		lwz r4, wp(r13)
		opword 0x90640000
		opword 0x38600000
		lwz r4, wp(r13)
		opword 0x8004000C
		opword 0x1C80000C
		bl __memAlloc
		lwz r4, wp(r13)
		opword 0x90640008
		opword 0x38600000
		lwz r4, wp(r13)
		opword 0x80040014
		opword 0x1C800170
		bl __memAlloc
		lwz r4, wp(r13)
		opword 0x38000000
		opword 0x90640010
		opword 0x38600000
		lwz r4, wp(r13)
		opword 0x900400E8
		lwz r4, wp(r13)
		opword 0x800400F0
		opword 0x1C80000C
		bl __memAlloc
		lwz r5, wp(r13)
		opword 0x38800000
		opword 0x38000001
		opword 0x906500EC
		lwz r3, wp(r13)
		opword 0x90830030
		lwz r3, wp(r13)
		opword 0x90830034
		lwz r3, wp(r13)
		opword 0x90830038
		lwz r3, wp(r13)
		opword 0x90830024
		lwz r3, wp(r13)
		opword 0x90830028
		lwz r3, wp(r13)
		opword 0x9083002C
		lwz r3, wp(r13)
		opword 0x908300CC
		lwz r3, wp(r13)
		opword 0x908300D0
		lwz r3, wp(r13)
		opword 0x908300D4
		lwz r3, wp(r13)
		opword 0x900300D8
		lwz r3, wp(r13)
		opword 0x900300DC
		lwz r3, wp(r13)
		opword 0x90830104
		lwz r3, wp(r13)
		opword 0x9083010C
		lwz r3, wp(r13)
		opword 0x80030104
		opword 0x28000000
		opword 0x40820018
		opword 0x38600000
		opword 0x3C800018
		bl __memAlloc
		lwz r4, wp(r13)
		opword 0x90640104
		lwz r5, wp(r13)
		lis r3, double_to_int_802c2df0@ha
		lis r4, tanfTbl@ha
		lfs f30, float_deg2rad_80419ad4(r2)
		opword 0x80050104
		addi r30, r4, tanfTbl@l
		lfd f31, double_to_int_802c2df0@l(r3)
		li r29, 0x0
		opword 0x90050108
		opword 0x3FE04330
		opword 0x381DFFA7
		stw r31, _af_pad+0(r1)
		opword 0x6C008000
		opword 0x9001000C
		opword 0xC8010008
		opword 0xEC00F828
		opword 0xEC3E0032
		bl tan
		opword 0xFC000818
		opword 0x3BBD0001
		opword 0x2C1D00B2
		opword 0xD01E0000
		opword 0x3BDE0004
		opword 0x4180FFCC
		lis r4, str_802C2F58@ha
		opword 0x38600000
		addi r4, r4, str_802C2F58@l
		opword 0x4CC63182
		bl fileAllocf
		opword 0x7C7D1B79
		opword 0x4182003C
		opword 0x809D00A0
		la r3, vivihimoData(r13)
		opword 0x80630004
		opword 0x38A00C00
		opword 0x80840000
		bl memcpy_as4
		opword 0x809D00A0
		la r3, vivihimoTailGroupNo(r13)
		opword 0x38A00010
		opword 0x80840000
		opword 0x38840C00
		bl memcpy_as4
		opword 0x7FA3EB78
		bl fileFree
		opword 0x38600000
		bl fileSetCurrentArchiveType
		lis r4, str_802C2F68@ha
		opword 0x38600000
		addi r4, r4, str_802C2F68@l
		opword 0x4CC63182
		bl fileAllocf
		lwz r4, wp(r13)
		opword 0x90640100
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
void animMain(void) {
    dispEntry(CAMERA_OFFSCREEN, 0.0f, 1, animPaperPoseDisp, NULL);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void animMain(void) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, animPaperPoseDisp@ha
		lfs f1, float_0_80419a48(r2)
		opword 0x90010014
		addi r5, r3, animPaperPoseDisp@l
		opword 0x38600000
		opword 0x38800001
		opword 0x38C00000
		bl dispEntry
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop
#endif

inline AnimationPoseData* animPoseGetBaseData(AnimationPose* pose) {
    return *wp->files[pose->fileId].handle->data;
}

#define animPoseGetBaseData(pose) (*(AnimationPoseData**)(wp->files[(pose)->fileId].handle->data))

// heavily inlined, TODO helper function for that AnimPoseData* data, copy of animPoseGetAnimBaseDataPtr with AnimPose*
// arg
void animPose_AllocBuffer(AnimationPose* pose) {
    pose->mpBufferVtxPos = testAlloc(sizeof(Vec) * animPoseGetBaseData(pose)->mBufferPosNum);
    pose->mpVtxArrayPos = testAlloc(sizeof(Vec) * animPoseGetBaseData(pose)->mBufferPosNum);

    pose->mpBufferVtxNrm = testAlloc(sizeof(Vec) * animPoseGetBaseData(pose)->mBufferNrmNum);
    pose->mpVtxArrayNrm = testAlloc(sizeof(Vec) * animPoseGetBaseData(pose)->mBufferNrmNum);

    pose->mpBufferGroupVisibility = testAlloc(sizeof(u8) * animPoseGetBaseData(pose)->mBufferVisibilityNum);
    pose->mpGroupVisibility = pose->mpBufferGroupVisibility;

    pose->mpBufferNode = testAlloc(sizeof(AnimPoseNode*) * animPoseGetBaseData(pose)->mBufferNodeNum);
    pose->mpNodes = testAlloc(sizeof(AnimPoseNode*) * animPoseGetBaseData(pose)->mBufferNodeNum);

    pose->mpBufferTexAnimEntries = testAlloc(sizeof(AnimTexMtx) * animPoseGetBaseData(pose)->mBufferTexAnimNum);
    pose->mpTexAnimEntries = pose->mpBufferTexAnimEntries;

    pose->lastFrameZero = -1;
}

// heavily inlined
void animPoseRefresh(void) {
    int i;

    initTestHeap(); // inline
    for (i = 0; i < wp->totalPoses; i++) {
        AnimationPose* pose = &wp->poses[i]; // inline
        if (pose->flags) {
            // TODO: cleanup in rewrite?
            if ((!wp->inBattle || pose->type != 0) && (wp->inBattle || pose->type != 1)) {
                animPose_AllocBuffer(pose);
                pose->lastFrameZero = -1; // TODO: redundant?
            }
        }
    }
}

void animPoseBattleInit(void) {
    wp->inBattle = TRUE;
    animPoseRefresh();
}

__declspec(section ".sdata") u32 g5__dummy_s614 = 0xFFFFFFFF;
#ifdef NONMATCHING
s32 animPoseEntry(const char *animName, s32 type)
{
  static s32 _dummy = -1;
  AnimationTextureFile *new_var3[2];
  AnimationPoseFile *file;
  AnimationPoseFile *tempfile;
  AnimationPose *pose;
  AnimationPose *temp;
  AnimationPoseData *data;
  s32 texId;
  s32 fileId;
  FileEntry *new_var2;
  s32 poseId;
  AnimationPoseFile *new_var;
  s32 i;
  char textureName[256];
  switch (type)
  {
    case 0:
      fileSetCurrentArchiveType(1);
      break;

    case 1:
      fileSetCurrentArchiveType(2);
      break;

    case 2:
      fileSetCurrentArchiveType(0);
      break;

  }

  for (poseId = 0, i = 0; i < wp->totalPoses; poseId++, i++)
  {
    temp = &wp->poses[poseId];
    if (!temp->flags)
    {
      pose = temp;
      goto label_1;
    }
  }

  pose = (void *) 0;
  poseId = -1;
  label_1:
  pose->flags |= 1;

  pose->typeFlags = 0;
  pose->references = 0;
  texId = wp->totalFiles;
  for (i = 0; i < texId; i++)
  {
    file = &wp->files[i];
    if (file->active)
    {
      data = *file->handle->data;
      if (!strcmp(data->fileName, animName))
      {
        file->references++;
        goto label_5;
      }
    }
  }

  for (i = 0, fileId = 0; i < wp->totalFiles; i++, fileId++)
  {
    tempfile = &wp->files[fileId];
    if (!tempfile->active)
    {
      file = tempfile;
      goto label_2;
    }
  }

  file = (void *) 0;
  fileId = -1;
  label_2:
  file->active = 1;

  file->references++;
  file->handle = fileAllocf(5, "%s/%s", "a", animName);
  new_var2 = file->handle;
  if (!file->handle)
  {
    fileId = -2;
    file->active = 0;
    file->references--;
  }
  else
  {
    data = *file->handle->data;
    if (!data)
    {
      fileFree(new_var2);
      fileId = -2;
      file->active = 0;
      new_var = file;
      new_var->references--;
    }
    else
    {
      sprintf(textureName, "%s/%s-", "a", data->textureName);
      texId = wp->totalTextures;
      for (i = 0; i < texId; i++)
      {
        new_var3[0] = &wp->textures[i];
        if (*((u32 *) (&new_var3[0]->active)))
        {
          if (new_var3[0]->handle)
          {
            if (!strcmp(new_var3[0]->handle->filename, textureName))
            {
              new_var3[0]->references++;
              goto label_4;
            }
          }
        }
      }

      for (i = 0, texId = 0; i < wp->totalTextures; i++, texId++)
      {
        new_var3[1] = &wp->textures[texId];
        if (!(*((u32 *) (&new_var3[1]->active))))
        {
          new_var3[0] = new_var3[1];
          goto label_3;
        }
      }

      new_var3[0] = (void *) 0;
      texId = -1;
      label_3:
      new_var3[0]->active = 1;

      new_var3[0]->references++;
      new_var3[0]->handle = fileAlloc(textureName, 4);
      label_4:
      new_var->textureId = texId;

    }
  }
  label_5:
  pose->fileId = fileId;

  if (pose->fileId == (-2))
  {
    pose->flags = 0;
    return -2;
  }
  pose->animId = 0;
  pose->localTime = animTimeGetTime(type);
  pose->lastFrameZero = -1;
  pose->lastFrameTime = EXT_LIT(float_0_80419a48, 0.0f);
  pose->field_0x80 = 0;
  pose->loopTime = EXT_LIT(float_0_80419a48, 0.0f);
  pose->peraRotY = EXT_LIT(float_0_80419a48, 0.0f);
  pose->rotationY = EXT_LIT(float_0_80419a48, 0.0f);
  pose->peraTargetRotY = EXT_LIT(float_0_80419a48, 0.0f);
  pose->type = type;
  pose->paperId = -1;
  animPose_AllocBuffer(pose);
  pose->gxCallback = (void *) 0;
  pose->disableDraw = 0;
  pose->materialFlag = 0;
  pose->materialLightFlag = 0;
  pose->materialColor = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
  pose->materialColor2 = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
  pose->paperScaleXZ = (pose->paperScaleY = EXT_LIT(float_1_80419a44, 1.0f));
  pose->paperOfsY = EXT_LIT(float_0_80419a48, 0.0f);
  pose->localTimeRate = EXT_LIT(float_1_80419a44, 1.0f);
  PSMTXIdentity(pose->matrix);
  if (!strcmp(animName, "tst_vivi"))
  {
    pose->vivianType = 1;
    pose->vivianGroupNo = &vivihimoTailGroupNo[0];
  }
  else
    if (!strcmp(animName, "c_vivian"))
  {
    pose->vivianType = 1;
    pose->vivianGroupNo = &vivihimoTailGroupNo[1];
  }
  else
    if (!strcmp(animName, "c_maririn"))
  {
    pose->vivianType = 2;
    pose->vivianGroupNo = &vivihimoTailGroupNo[2];
  }
  else
    if (!strcmp(animName, "c_majyorin"))
  {
    pose->vivianType = 3;
    pose->vivianGroupNo = &vivihimoTailGroupNo[3];
  }
  else
  {
    pose->vivianType = 0;
    pose->vivianGroupNo = &_dummy;
  }
  pose->dispCallback = (void *) 0;
  pose->dispUserDataCallback = (void *) 0;
  return poseId;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 animPoseEntry(const char *animName, s32 type) {
	char _af_pad[260];
	asm volatile {
		opword 0x7C9C2378
		lis r4, str_802C2A98@ha
		opword 0x7C7D1B78
		opword 0x2C1C0001
		addi r27, r4, str_802C2A98@l
		opword 0x4182002C
		opword 0x40800010
		opword 0x2C1C0000
		opword 0x40800014
		opword 0x48000030
		opword 0x2C1C0003
		opword 0x40800028
		opword 0x4800001C
		opword 0x38600001
		bl fileSetCurrentArchiveType
		opword 0x48000018
		opword 0x38600002
		bl fileSetCurrentArchiveType
		opword 0x4800000C
		opword 0x38600000
		bl fileSetCurrentArchiveType
		lwz r5, wp(r13)
		opword 0x3BC00000
		opword 0x7FC4F378
		opword 0x80050014
		opword 0x7C0903A6
		opword 0x2C000000
		opword 0x4081002C
		opword 0x80050010
		opword 0x7C602214
		opword 0x80030000
		opword 0x28000000
		opword 0x4082000C
		opword 0x7C7F1B78
		opword 0x48000018
		opword 0x38840170
		opword 0x3BDE0001
		opword 0x4200FFDC
		opword 0x3BE00000
		opword 0x3BC0FFFF
		opword 0x801F0000
		opword 0x3B200000
		opword 0x7F36CB78
		opword 0x60000001
		opword 0x901F0000
		opword 0x933F0004
		opword 0x933F0008
		lwz r3, wp(r13)
		opword 0x82E30004
		opword 0x48000054
		lwz r3, wp(r13)
		opword 0x80030000
		add r21, r0, r22
		opword 0x80150000
		opword 0x28000000
		opword 0x41820034
		opword 0x80750008
		opword 0x7FA4EB78
		opword 0x806300A0
		opword 0x80630000
		opword 0x38630004
		bl strcmp
		opword 0x2C030000
		opword 0x40820014
		opword 0x80750004
		opword 0x38030001
		opword 0x90150004
		opword 0x480001D8
		opword 0x3AD60010
		opword 0x3B390001
		opword 0x7C19B800
		opword 0x4180FFAC
		lwz r4, wp(r13)
		opword 0x3B200000
		opword 0x7F23CB78
		opword 0x80040004
		opword 0x7C0903A6
		opword 0x2C000000
		opword 0x40810028
		opword 0x80040000
		opword 0x7F401A14
		opword 0x801A0000
		opword 0x28000000
		opword 0x40820008
		opword 0x48000018
		opword 0x38630010
		opword 0x3B390001
		opword 0x4200FFE0
		opword 0x3B400000
		opword 0x3B20FFFF
		opword 0x38000001
		opword 0x7FA6EB78
		opword 0x901A0000
		opword 0x38600005
		la r4, str_80419A54(r2)
		la r5, str_80419A5C(r2)
		opword 0x80FA0004
		opword 0x38070001
		opword 0x901A0004
		opword 0x4CC63182
		bl fileAllocf
		opword 0x907A0008
		opword 0x807A0008
		opword 0x28030000
		opword 0x40820020
		opword 0x38000000
		opword 0x3B20FFFE
		opword 0x901A0000
		opword 0x807A0004
		opword 0x3803FFFF
		opword 0x901A0004
		opword 0x48000128
		opword 0x808300A0
		opword 0x80A40000
		opword 0x28050000
		opword 0x40820024
		bl fileFree
		opword 0x38000000
		opword 0x3B20FFFE
		opword 0x901A0000
		opword 0x807A0004
		opword 0x3803FFFF
		opword 0x901A0004
		opword 0x480000F8
		la r3, _af_pad+0
		opword 0x389B0350
		opword 0x38C50044
		la r5, str_80419A5C(r2)
		opword 0x4CC63182
		bl sprintf
		lwz r3, wp(r13)
		opword 0x3AC00000
		opword 0x7ED5B378
		opword 0x82E3000C
		opword 0x48000054
		lwz r3, wp(r13)
		opword 0x80030008
		opword 0x7F00AA14
		opword 0x80180000
		opword 0x28000000
		opword 0x41820034
		opword 0x80780008
		opword 0x28030000
		opword 0x41820028
		opword 0x38630020
		opword 0x38810008
		bl strcmp
		opword 0x2C030000
		opword 0x40820014
		opword 0x80780004
		opword 0x38030001
		opword 0x90180004
		opword 0x48000080
		opword 0x3AB5000C
		opword 0x3AD60001
		opword 0x7C16B800
		opword 0x4180FFAC
		lwz r4, wp(r13)
		opword 0x3AC00000
		opword 0x7EC3B378
		opword 0x8004000C
		opword 0x7C0903A6
		opword 0x2C000000
		opword 0x40810028
		opword 0x80040008
		opword 0x7EA01A14
		opword 0x80150000
		opword 0x28000000
		opword 0x40820008
		opword 0x48000018
		opword 0x3863000C
		opword 0x3AD60001
		opword 0x4200FFE0
		opword 0x3AA00000
		opword 0x3AC0FFFF
		opword 0x38000001
		opword 0x38610008
		opword 0x90150000
		opword 0x38800004
		opword 0x80B50004
		opword 0x38050001
		opword 0x90150004
		bl fileAlloc
		opword 0x90750008
		opword 0x92DA000C
		opword 0x933F0010
		opword 0x801F0010
		opword 0x2C00FFFE
		opword 0x40820014
		opword 0x38000000
		opword 0x3860FFFE
		opword 0x901F0000
		opword 0x480001C8
		opword 0x38000000
		opword 0x2C1C0000
		opword 0x901F0014
		opword 0x40820038
		opword 0x3C608000
		opword 0x3C801062
		opword 0x800300F8
		opword 0x38A44DD3
		lwz r6, gp(r13)
		opword 0x5400F0BE
		opword 0x7C050016
		opword 0x80660040
		opword 0x80860044
		opword 0x38A00000
		opword 0x5406D1BE
		bl __div2i
		opword 0x48000034
		opword 0x3C608000
		opword 0x3C801062
		opword 0x800300F8
		opword 0x38A44DD3
		lwz r6, gp(r13)
		opword 0x5400F0BE
		opword 0x7C050016
		opword 0x80660038
		opword 0x8086003C
		opword 0x38A00000
		opword 0x5406D1BE
		bl __div2i
		opword 0x909F001C
		opword 0x3880FFFF
		lfs f0, float_0_80419a48(r2)
		opword 0x38000000
		opword 0x907F0018
		opword 0x7FE3FB78
		opword 0x909F003C
		opword 0xD01F0040
		opword 0x901F0080
		opword 0xD01F0084
		opword 0xD01F0070
		opword 0xD01F0074
		opword 0xD01F007C
		opword 0x939F000C
		opword 0x909F0090
		bl animPose_AllocBuffer
		opword 0x38000000
		lfs f1, float_1_80419a44(r2)
		opword 0x901F00E0
		opword 0x387F0124
		lfs f0, float_0_80419a48(r2)
		opword 0x901F00E4
		opword 0x901F00E8
		opword 0x901F00EC
		lwz r0, dat_80419a2c(r2)
		opword 0x901F00F0
		lwz r0, dat_80419a30(r2)
		opword 0x901F00F4
		opword 0xD03F00FC
		opword 0xD03F00F8
		opword 0xD01F0100
		opword 0xD03F0044
		bl PSMTXIdentity
		opword 0x7FA3EB78
		opword 0x389B0490
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x38600001
		la r0, vivihimoTailGroupNo(r13)
		opword 0x907F011C
		opword 0x901F0120
		opword 0x48000098
		opword 0x7FA3EB78
		opword 0x389B049C
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x38000001
		la r3, vivihimoTailGroupNo(r13)
		opword 0x901F011C
		opword 0x38030004
		opword 0x901F0120
		opword 0x4800006C
		opword 0x7FA3EB78
		opword 0x389B04A8
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x38000002
		la r3, vivihimoTailGroupNo(r13)
		opword 0x901F011C
		opword 0x38030008
		opword 0x901F0120
		opword 0x48000040
		opword 0x7FA3EB78
		opword 0x389B04B4
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x38000003
		la r3, vivihimoTailGroupNo(r13)
		opword 0x901F011C
		opword 0x3803000C
		opword 0x901F0120
		opword 0x48000014
		opword 0x38600000
		la r0, g5__dummy_s614(r13)
		opword 0x907F011C
		opword 0x901F0120
		opword 0x38000000
		opword 0x7FC3F378
		opword 0x901F0154
		opword 0x901F0158
	}
}
#pragma pop
#endif

s32 animPaperPoseEntry(const char* animName, s32 group) {
    s32 i;
    AnimationPose* pose;

    i = animPaperPoseGetId(animName, group);
    if (i >= 0) {
        pose = animPoseGetAnimPosePtr(i);
        pose->references++;
        return i;
    }
    i = animPoseEntry(animName, group);
    if (i == -2) {
        return i;
    }
    pose = animPoseGetAnimPosePtr(i);
    pose->typeFlags = 3;
    pose->references = 0;
    pose->flags |= 1;
    return i;
}

const char* animGetTexName(const char* name);

#ifdef NONMATCHING
BOOL animEffectAsync(const char* animName, u32 group) {
    s32 model, anim;
    BOOL ret;

    switch (group) {
        case 0:
            fileSetCurrentArchiveType(1);
            break;
        case 1:
            fileSetCurrentArchiveType(2);
            break;
        case 2:
            fileSetCurrentArchiveType(0);
            break;
    }
    model = fileAsyncf(5, NULL, "%s/%s", "a", animName);
    anim = fileAsyncf(4, NULL, "%s/%s-", "a", animGetTexName(animName));
    if (model == -1) {
        ret = TRUE;
    } else if ((u32)model == 0) {
        ret = FALSE;
    } else if (anim == -1) {
        ret = TRUE;
    } else if ((u32)anim == 0) {
        ret = FALSE;
    } else {
        ret = TRUE;
    }
    return ret;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
BOOL animEffectAsync(const char* animName, u32 group) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x2C040001
		opword 0x90010024
		opword 0xBF61000C
		opword 0x7C7B1B78
		opword 0x4182002C
		opword 0x40800010
		opword 0x2C040000
		opword 0x40800014
		opword 0x48000030
		opword 0x2C040003
		opword 0x40800028
		opword 0x4800001C
		opword 0x38600001
		bl fileSetCurrentArchiveType
		opword 0x48000018
		opword 0x38600002
		bl fileSetCurrentArchiveType
		opword 0x4800000C
		opword 0x38600000
		bl fileSetCurrentArchiveType
		opword 0x7F67DB78
		opword 0x38600005
		opword 0x38800000
		la r5, str_80419A54(r2)
		la r6, str_80419A5C(r2)
		opword 0x4CC63182
		bl fileAsyncf
		lwz r4, wp(r13)
		opword 0x7C7F1B78
		opword 0x3BA00000
		opword 0x80640100
		opword 0x806300A0
		opword 0x83830004
		opword 0x83C30000
		opword 0x48000028
		opword 0x7FC3F378
		opword 0x7F64DB78
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x38FE0020
		opword 0x48000018
		opword 0x3BDE0020
		opword 0x3BBD0020
		opword 0x7C1DE000
		opword 0x4180FFD8
		la r7, zero_80419a50(r2)
		lis r3, str_802C2DE8@ha
		opword 0x38800000
		addi r5, r3, str_802C2DE8@l
		la r6, str_80419A5C(r2)
		opword 0x38600004
		opword 0x4CC63182
		bl fileAsyncf
		opword 0x2C1FFFFF
		opword 0x4082000C
		opword 0x38600001
		opword 0x48000038
		opword 0x281F0000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000028
		opword 0x2C03FFFF
		opword 0x4082000C
		opword 0x38600001
		opword 0x48000018
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000008
		opword 0x38600001
		opword 0xBB61000C
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop
#endif

void animPosePeraOn(s32 poseId) {
    wp->poses[poseId].flags |= 8;
}

void animPosePeraOff(s32 poseId) {
    wp->poses[poseId].flags &= ~8;
}

void animPosePaperPeraOn(s32 poseId) {
    AnimationPose* dst = &wp->poses[wp->poses[poseId].paperId];
    AnimationPose* src = &wp->poses[poseId];

    dst->flags |= 8;
    dst->peraRotY = src->peraRotY;
    dst->rotationY = src->rotationY;
    dst->peraTargetRotY = src->peraTargetRotY;
}

void animPosePaperPeraOff(s32 poseId) {
    wp->poses[wp->poses[poseId].paperId].flags &= ~8;
}

void animPoseSetLocalTimeRate(s32 poseId, f32 localTimeRate) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->localTimeRate = localTimeRate;
}

void animPoseSetLocalTime(s32 poseId, f32 localTimeFrames) {
    AnimationPose *pose, *pera;

    pose = &wp->poses[poseId];
    pose->localTime = animTimeGetTime(pose->type) - (u64)(EXT_LIT(float_16p667_80419a60, 16.666666f) * localTimeFrames);
    pose->mLocalTimeInit = pose->localTime;
    if (pose->paperId != -1) {
        pera = &wp->poses[pose->paperId];
        if (!(pera->typeFlags & 2)) {
            pera->localTime = pose->localTime;
        }
    }
}

void animPoseSetStartTime(s32 poseId, OSTime startTime) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->localTime = startTime;
}

#define animPosePaperAnimId(pose) (*(s32*)(pose)->field_0x94)
#define animPoseGetBaseDataId(id) (*(AnimationPoseData**)(wp->files[wp->poses[id].fileId].handle->data))

inline s32 animPoseGetAnimIdx(AnimationPoseData* data, const char* name) {
    s32 i = (s32)name;
    s32 count = data->mAnimCount;

    if (i < 0) {
        for (i = 0; i < count; i++) {
            if (!strcmp(data->mpAnims[i].name, name)) {
                return i;
            }
        }
    }
    else if (i < count) {
        return i;
    }
    return 0;
}

void animPoseSetAnim(s32 poseId, const char* animName, BOOL reset) {
    AnimationPose* pose;
    s32 animId;

    pose = &wp->poses[poseId];
    animId = animPoseGetAnimIdx(animPoseGetBaseData(pose), animName);
    if (reset || animId != pose->animId) {
        pose->animId = animId;
        if (pose->paperId != -1 && pose->flags & 2) {
            pose->flags |= 4;
        }
        pose->localTime = animTimeGetTime(pose->type);
        pose->lastFrameZero = -1;
        pose->lastFrameTime = EXT_LIT(float_0_80419a48, 0.0f);
        pose->field_0x80 = 0;
        pose->loopTime = EXT_LIT(float_0_80419a48, 0.0f);
    }
}

s32 animPaperPoseGetId(const char* animName, s32 group) {
    AnimationPose* pose;
    s32 i;

    for (i = 0; i < wp->totalPoses; i++) {
        pose = &wp->poses[i];
        if (pose->flags & 1 && pose->typeFlags & 1 && pose->typeFlags & 2 && pose->type == group &&
            !strcmp(animPoseGetBaseData(pose)->fileName, animName)) {
            break;
        }
    }
    if (i == wp->totalPoses) {
        i = -1;
    }
    return i;
}

void animPoseSetPaperAnimGroup(s32 poseId, const char* animName, BOOL someflag) {
    AnimationPose* pose = animPoseGetAnimPosePtr(poseId);

    if (!animName) {
        pose->paperId = -1;
        animPoseSetMaterialLightFlagOff(poseId, 1);
        return;
    }
    pose->paperId = animPaperPoseGetId(animName, pose->type);
    if (pose->paperId < 0) {
        pose->paperId = animPaperPoseGetId(animName, 2);
    }
    animPosePaperAnimId(pose) = -1;
    pose->mLocalTimeInit = animTimeGetTime(pose->type);
    if (someflag) {
        pose->flags |= 2;
        pose->flags |= 4;
    }
    else {
        pose->flags &= ~2;
        pose->flags &= ~4;
    }
    animPoseSetMaterialLightFlagOn(poseId, 1);
}

void animPoseSetPaperAnim(s32 poseId, const char* animName, BOOL reset) {
    AnimationPose* pose = animPoseGetAnimPosePtr(poseId);
    AnimationPoseData* data;
    s32 id;
    s32 idx;

    data = animPoseGetAnimBaseDataPtr(pose->paperId);
    idx = animPoseGetAnimIdx(data, animName);
    animPosePaperAnimId(pose) = idx;
    pose->mLocalTimeInit = animTimeGetTime(pose->type);
    id = pose->paperId;
    if (id != -1 && !(*(u32*)((u8*)wp->poses + id * sizeof(AnimationPose) + 4) & 2)) {
        animPoseMain(pose->paperId);
    }
}

void animPoseFileRelease(s32 fileId);

inline s32 animEffectPoseEntry(const char* animName, s32 group) {
    s32 i;
    AnimationPose* pose;

    i = animPoseEntry(animName, group);
    if (i == -2) {
        return i;
    }
    pose = animPoseGetAnimPosePtr(i);
    pose->typeFlags = 1;
    pose->references = 0;
    pose->flags |= 1;
    return i;
}

void animPoseSetEffect(s32 poseId, const char* animName, BOOL someflag) {
    AnimationPose* paper;
    AnimationPose* pose = animPoseGetAnimPosePtr(poseId);

    if (pose->paperId != -1) {
        if (animName && !strcmp((*(AnimationPoseData**)(((AnimationPoseFile*)((u8*)wp->files + animPoseGetAnimPosePtr(pose->paperId)->fileId * 16))->handle->data))->fileName, animName) &&
            (s32)((pose->flags >> 1) & 1) == someflag) {
            return;
        }
        paper = &wp->poses[pose->paperId];
        paper->references--;
        if (paper->references < 0) {
            animPoseFileRelease(paper->fileId);
            paper->flags = 0;
        }
    }
    if (!animName) {
        pose->paperId = -1;
        animPoseSetMaterialLightFlagOff(poseId, 1);
        return;
    }
    pose->paperId = animEffectPoseEntry(animName, pose->type);
    animPosePaperAnimId(pose) = -1;
    pose->mLocalTimeInit = animTimeGetTime(pose->type);
    if (someflag) {
        pose->flags |= 2;
        pose->flags |= 4;
    }
    else {
        pose->flags &= ~2;
    }
    animPoseSetMaterialLightFlagOn(poseId, 1);
}

void animPoseSetEffectAnim(s32 poseId, const char* animName, BOOL reset) {
    AnimationPose* pose = &wp->poses[poseId];

    if (pose->paperId != -1) {
        animPoseSetAnim(pose->paperId, animName, reset);
    }
}

void animPoseSetGXFunc(s32 poseId, void (*callback)(s32 wXluStage), BOOL disableDraw) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->gxCallback = callback;
    pose->disableDraw = disableDraw;
}

#ifdef NONMATCHING
f32 animPoseGetRadius(s32 poseId) {
    return 2.0f * animPoseGetAnimBaseDataPtr(poseId)->radius;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
f32 animPoseGetRadius(s32 poseId) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x1C830170
		opword 0x3C004330
		lfs f2, float_2_80419a84(r2)
		lwz r5, wp(r13)
		lis r3, double_to_int_802c2df0@ha
		opword 0x90010008
		opword 0x80C50010
		opword 0x80A50000
		opword 0x7C862214
		lfd f1, double_to_int_802c2df0@l(r3)
		opword 0x80840010
		opword 0x54802036
		opword 0x7C650214
		opword 0x80630008
		opword 0x806300A0
		opword 0x80630000
		opword 0x800300C8
		opword 0x6C008000
		opword 0x9001000C
		opword 0xC8010008
		opword 0xEC000828
		opword 0xEC220032
		opword 0x38210010
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
f32 animPoseGetHeight(s32 poseId) {
    return 2.0f * animPoseGetAnimBaseDataPtr(poseId)->height;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
f32 animPoseGetHeight(s32 poseId) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x1C830170
		opword 0x3C004330
		lfs f2, float_2_80419a84(r2)
		lwz r5, wp(r13)
		lis r3, double_to_int_802c2df0@ha
		opword 0x90010008
		opword 0x80C50010
		opword 0x80A50000
		opword 0x7C862214
		lfd f1, double_to_int_802c2df0@l(r3)
		opword 0x80840010
		opword 0x54802036
		opword 0x7C650214
		opword 0x80630008
		opword 0x806300A0
		opword 0x80630000
		opword 0x800300CC
		opword 0x6C008000
		opword 0x9001000C
		opword 0xC8010008
		opword 0xEC000828
		opword 0xEC220032
		opword 0x38210010
	}
}
#pragma pop
#endif

f32 animPoseGetLoopTimes(s32 id) {
    AnimationPose* pose = &wp->poses[id];
    return pose->loopTime;
}

BOOL animPoseGetPeraEnd(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];

    if (!(pose->flags & 8)) {
        return TRUE;
    }
    if (__fabs(pose->peraTargetRotY - pose->rotationY) < EXT_LIT(double_10_802c2f20, 10.0)) {
        return TRUE;
    }
    return FALSE;
}

void animPoseSetMaterialFlagOn(s32 poseId, u32 mask) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->materialFlag |= mask;
}

void animPoseSetMaterialFlagOff(s32 poseId, u32 mask) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->materialFlag &= ~mask;
}

void animPoseSetMaterialLightFlagOn(s32 poseId, u32 mask) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->materialLightFlag |= mask;
}

void animPoseSetMaterialLightFlagOff(s32 poseId, u32 mask) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->materialLightFlag &= ~mask;
}

void animPoseSetMaterialEvtColor(s32 poseId, GXColor color) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->materialColor = color;
}

u32 animPoseGetMaterialFlag(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    return pose->materialFlag;
}

u32 animPoseGetMaterialLightFlag(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    return pose->materialLightFlag;
}

GXColor animPoseGetMaterialEvtColor(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    return pose->materialColor;
}

extern double atan2(double y, double x);
#define APM_U(p, o) (*(u32*)((u8*)(p) + (o)))
#define APM_S(p, o) (*(s32*)((u8*)(p) + (o)))
#define APM_F(p, o) (*(f32*)((u8*)(p) + (o)))
#define APM_P(p, o) (*(u8**)((u8*)(p) + (o)))
#define APM_S8(dst, p, off) asm { psq_l dst, off(p), 1, 4 }
#ifdef NONMATCHING
static inline void animInitFastCast_(void) {
    asm {
        li r3, 4
        oris r3, r3, 4
        mtspr GQR2, r3
        li r3, 5
        oris r3, r3, 5
        mtspr GQR3, r3
        li r3, 6
        oris r3, r3, 6
        mtspr GQR4, r3
        li r3, 7
        oris r3, r3, 7
        mtspr GQR5, r3
    }
}
#endif
#ifdef NONMATCHING
static inline f32 animS8a_(register u8* p) { register f32 r; asm { psq_l r, 1(p), 1, 4 } return r; }
#endif
#ifdef NONMATCHING
static inline f32 animS8b_(register u8* p) { register f32 r; asm { psq_l r, 2(p), 1, 4 } return r; }
#endif
#ifdef NONMATCHING
static inline f32 animS8c_(register u8* p) { register f32 r; asm { psq_l r, 3(p), 1, 4 } return r; }
#endif
#ifdef NONMATCHING
void animPoseMain(s32 poseId) {
    s32 nextFrame;
    u8* pose;
    u8* file;
    u8* anim;
    u8* poses;
    u8* grpB;
    u8* grpA;
    u8* q;
    f32 key;
    u8* kf;
    u8* kfEnd;
    u8* v;
    u8* d;
    u8* e;
    f32 x;
    f32 y;
    f32 z;
    s32 loop;
    s32 nD;
    s32 frame;
    s32 cnt;
    s32 i;
    s32 b;
    s32 nA;
    s32 nB;
    s32 nC;
    s32 nE;
    f32 t;
    f32 f;
    f32 cur;
    f32 start;
    f32 len;
    f32 tm;
    f32 dt;
    f32 s;
    f32 t2;
    f32 t3;
    u8* p;
    s64 ms;
    struct APMG { u8 pad[8]; u8* p; u8 pad2[4]; };
    struct APMA { u8 pad[0x3c]; u8* p; };
    struct APMA* aa;
    struct APMK { s32 a; s32 b; };
    struct APMF { u8 pad[0x2c]; };
    struct APMD { u8 pad[0x28]; struct APMF* f; u8 pad2[0x40 - 0x2c]; struct APMK* k; };

    poses = APM_P(wp, 0x10);
    pose = poses + poseId * 0x170;
    file = (u8*)animPoseGetBaseData((AnimationPose*)pose);
    anim = (u8*)((AnimationPoseData*)file)->mpAnims[((AnimationPose*)pose)->animId].data;
    animInitFastCast_();
    if (APM_S(wp, 0xe8) != 0) {
        grpA = APM_P(wp, 0xf8);
        grpB = APM_P(wp, 0xfc);
    } else {
        grpA = APM_P(pose, 0x4c);
        grpB = APM_P(pose, 0x54);
    }
    if (APM_S(pose, 0x90) != -1 && !(APM_U(poses + APM_S(pose, 0x90) * 0x170, 4) & 2)) {
        animPoseMain(APM_S(pose, 0x90));
    }
    if (anim == NULL) return;
    loop = *(s32*)APM_P(anim, 0x24);
    if (APM_S(pose, 0xc) == 0) {
        ms = OSTicksToMilliseconds(gp->renderFieldTime);
    } else {
        ms = OSTicksToMilliseconds(gp->renderTime);
    }
    tm = (f32)(u64)(ms - *(s64*)(pose + 0x18));
    APM_F(pose, 0x20) = EXT_LIT(float_60_80419ac4, 60.0f) * tm / EXT_LIT(float_1000_80419ac8, 1000.0f);
    APM_F(pose, 0x20) *= APM_F(pose, 0x44);
    cur = APM_F(pose, 0x20);
    f = APM_F(APM_P(anim, 0x24), 8);
    start = APM_F(APM_P(anim, 0x24), 4);
    len = f - start;
    if (EXT_LIT(float_0_80419a48, 0.0f) == len) {
        APM_F(pose, 0x84) = cur - start;
    } else if (loop != 0) {
        tm = cur - start;
        if (tm < EXT_LIT(float_0_80419a48, 0.0f)) {
            APM_F(pose, 0x84) = 0.0f;
        } else {
            APM_F(pose, 0x84) = tm / len;
            start = cur - (f32)(s32)APM_F(pose, 0x84) * len;
        }
    } else if (cur < start) {
        APM_F(pose, 0x84) = 0.0f;
    } else if (cur > f) {
        APM_F(pose, 0x84) = (cur - start) / len;
        start = f;
    } else {
        APM_F(pose, 0x84) = (cur - start) / len;
        start = cur;
    }
    APM_F(pose, 0x24) = start;
    key = APM_F(pose, 0x24);
    cnt = APM_S(anim, 8);
    q = APM_P(anim, 0x28);
    for (i = 0; i < cnt; i++, q += 0x2c) {
        if (*(f32*)q > key) break;
    }
    APM_S(pose, 0x28) = i - 1;
    APM_S(pose, 0x2c) = APM_S(pose, 0x28) + 1;
    key = APM_F(pose, 0x24);
    q = APM_P(anim, 0x40);
    cnt = APM_S(anim, 0x20);
    for (i = 0; i < cnt; q += 8, i++) {
        if (*(f32*)q > key) break;
    }
    APM_S(pose, 0x34) = i - 1;
    APM_S(pose, 0x38) = APM_S(pose, 0x34) + 1;
    if (loop == 0) {
        if (APM_S(pose, 0x2c) >= APM_S(anim, 8)) APM_S(pose, 0x2c) = APM_S(pose, 0x28);
        if (APM_S(pose, 0x38) >= APM_S(anim, 0x20)) APM_S(pose, 0x38) = APM_S(pose, 0x34);
    }
    APM_S(pose, 0x80) = ((struct APMD*)anim)->k[APM_S(pose, 0x34)].b;
    start = *(f32*)(APM_P(anim, 0x28) + APM_S(pose, 0x28) * 0x2c);
    tm = APM_F(pose, 0x24) - start;
    if (loop != 0) {
        if (APM_S(pose, 0x2c) >= APM_S(anim, 8)) {
            APM_S(pose, 0x2c) = 0;
            len = APM_F(APM_P(anim, 0x24), 8) - *(f32*)(APM_P(anim, 0x28) + APM_S(pose, 0x28) * 0x2c);
        } else {
            len = *(f32*)(APM_P(anim, 0x28) + APM_S(pose, 0x2c) * 0x2c) - start;
        }
    } else {
        len = *(f32*)(APM_P(anim, 0x28) + APM_S(pose, 0x2c) * 0x2c) - start;
    }
    if (EXT_LIT(float_0_80419a48, 0.0f) == len) {
        APM_F(pose, 0x30) = 0.0f;
    } else {
        APM_F(pose, 0x30) = tm / len;
    }
    frame = APM_S(pose, 0x28);
    nextFrame = APM_S(pose, 0x2c);
    t = APM_F(pose, 0x30);
    nA = APM_S(file, 0xf0);
    nB = APM_S(file, 0xf8);
    nC = APM_S(file, 0x13c);
    nD = APM_S(file, 0x140);
    nE = APM_S(file, 0x12c);
    if (APM_S(pose, 0x3c) != frame) {
        if (APM_S(pose, 0x3c) == -1 || APM_S(pose, 0x3c) > frame) {
            kfEnd = (u8*)((struct APMD*)anim)->f + frame * 0x2c + 0x2c;
            kf = (u8*)((struct APMD*)anim)->f;
            if (nA != 0) memcpy_as4(APM_P(pose, 0x48), APM_P(file, 0x154), nA * 0xc);
            if (nB != 0) memcpy_as4(APM_P(pose, 0x50), APM_P(file, 0x15c), nB * 0xc);
            if (nC != 0) memcpy(APM_P(pose, 0x58), APM_P(file, 0x1a0), nC);
            if (nD != 0) memcpy_as4(APM_P(pose, 0x60), APM_P(file, 0x1a4), nD * 4);
            if (nE != 0) memcpy_as4(APM_P(pose, 0x68), APM_P(file, 0x190), nE * 0x18);
            if (APM_S(pose, 0x3c) == -1) APM_S(pose, 0x3c) = 0;
            s = EXT_LIT(float_0p0625_80419acc, 0.0625f);
            for (; kf < kfEnd; kf += 0x2c) {
                { u8* d; u8* e;
                v = APM_P(pose, 0x48);
                d = APM_P(anim, 0x2c) + APM_S(kf, 4) * 4;
                e = d + APM_S(kf, 8) * 4;
                for (; d < e; d += 4) {
                    v += d[0] * 0xc;
                    x = animS8a_(d);
                    y = animS8b_(d);
                    z = animS8c_(d);
                    ((f32*)v)[0] += s * x;
                    ((f32*)v)[1] += s * y;
                    ((f32*)v)[2] += s * z;
                }
                }
                { u8* d; u8* e;
                v = APM_P(pose, 0x50);
                d = APM_P(anim, 0x30) + APM_S(kf, 0xc) * 4;
                e = d + APM_S(kf, 0x10) * 4;
                for (; d < e; d += 4) {
                    v += d[0] * 0xc;
                    x = animS8a_(d);
                    y = animS8b_(d);
                    z = animS8c_(d);
                    ((f32*)v)[0] += s * x;
                    ((f32*)v)[1] += s * y;
                    ((f32*)v)[2] += s * z;
                }
                }
                { u8* d; u8* e; u8* v;
                v = APM_P(pose, 0x58);
                d = APM_P(anim, 0x38) + APM_S(kf, 0x1c) * 2;
                e = d + APM_S(kf, 0x20) * 2;
                for (; d < e; d += 2) {
                    v += d[0];
                    v[0] += d[1];
                }
                }
                { u8* d; u8* e;
                v = APM_P(pose, 0x60);
                d = APM_P(anim, 0x3c) + APM_S(kf, 0x24) * 4;
                e = d + APM_S(kf, 0x28) * 4;
                for (; d < e; d += 4) {
                    v += d[0] * 4;
                    x = animS8a_(d);
                    ((f32*)v)[0] += s * x;
                }
                }
                { u8* d; u8* e;
                v = APM_P(pose, 0x68);
                d = APM_P(anim, 0x34) + APM_S(kf, 0x14) * 0xc;
                e = d + APM_S(kf, 0x18) * 0xc;
                for (; d < e; d += 0xc) {
                    v += d[0] * 0x18;
                    v[0] += d[1];
                    APM_F(v, 4) += APM_F(d, 4);
                    APM_F(v, 8) += APM_F(d, 8);
                }
                }
            }
        } else if (APM_S(pose, 0x3c) < frame) {
            kf = APM_P(anim, 0x28) + (APM_S(pose, 0x3c) + 1) * 0x2c;
            kfEnd = APM_P(anim, 0x28) + (frame + 1) * 0x2c;
            s = EXT_LIT(float_0p0625_80419acc, 0.0625f);
            for (; kf < kfEnd; kf += 0x2c) {
                { u8* d; u8* e;
                v = APM_P(pose, 0x48);
                d = APM_P(anim, 0x2c) + APM_S(kf, 4) * 4;
                e = d + APM_S(kf, 8) * 4;
                for (; d < e; d += 4) {
                    v += d[0] * 0xc;
                    x = animS8a_(d);
                    y = animS8b_(d);
                    z = animS8c_(d);
                    ((f32*)v)[0] += s * x;
                    ((f32*)v)[1] += s * y;
                    ((f32*)v)[2] += s * z;
                }
                }
                { u8* d; u8* e;
                v = APM_P(pose, 0x50);
                d = APM_P(anim, 0x30) + APM_S(kf, 0xc) * 4;
                e = d + APM_S(kf, 0x10) * 4;
                for (; d < e; d += 4) {
                    v += d[0] * 0xc;
                    x = animS8a_(d);
                    y = animS8b_(d);
                    z = animS8c_(d);
                    ((f32*)v)[0] += s * x;
                    ((f32*)v)[1] += s * y;
                    ((f32*)v)[2] += s * z;
                }
                }
                { u8* d; u8* e; u8* v;
                v = APM_P(pose, 0x58);
                d = APM_P(anim, 0x38) + APM_S(kf, 0x1c) * 2;
                e = d + APM_S(kf, 0x20) * 2;
                for (; d < e; d += 2) {
                    v += d[0];
                    v[0] += d[1];
                }
                }
                { u8* d; u8* e;
                v = APM_P(pose, 0x60);
                d = APM_P(anim, 0x3c) + APM_S(kf, 0x24) * 4;
                e = d + APM_S(kf, 0x28) * 4;
                for (; d < e; d += 4) {
                    v += d[0] * 4;
                    x = animS8a_(d);
                    ((f32*)v)[0] += s * x;
                }
                }
                { u8* d; u8* e;
                v = APM_P(pose, 0x68);
                d = APM_P(anim, 0x34) + APM_S(kf, 0x14) * 0xc;
                e = d + APM_S(kf, 0x18) * 0xc;
                for (; d < e; d += 0xc) {
                    v += d[0] * 0x18;
                    v[0] += d[1];
                    APM_F(v, 4) += APM_F(d, 4);
                    APM_F(v, 8) += APM_F(d, 8);
                }
                }
            }
        }
    } else {
        if (APM_F(pose, 0x40) > t) APM_F(pose, 0x40) = 0.0f;
    }
    if (frame == nextFrame) {
        if (nA != 0) memcpy_as4(grpA, APM_P(pose, 0x48), nA * 0xc);
        if (nB != 0) memcpy_as4(grpB, APM_P(pose, 0x50), nB * 0xc);
        if (nD != 0) memcpy_as4(APM_P(pose, 0x64), APM_P(pose, 0x60), nD * 4);
    } else if (frame <= nextFrame) {
        kf = APM_P(anim, 0x28) + nextFrame * 0x2c;
        { u8* d; u8* e;
        s = EXT_LIT(float_0p0625_80419acc, 0.0625f) * t;
        v = grpA;
        d = APM_P(anim, 0x2c) + APM_S(kf, 4) * 4;
        e = d + APM_S(kf, 8) * 4;
        p = APM_P(pose, 0x48);
        if (nA != 0) memcpy_as4(grpA, p, nA * 0xc);
        for (; d < e; d += 4) {
            v += d[0] * 0xc;
            x = animS8a_(d);
            y = animS8b_(d);
            z = animS8c_(d);
            ((f32*)v)[0] += x * s;
            ((f32*)v)[1] += y * s;
            ((f32*)v)[2] += z * s;
        }
        }
        { u8* d; u8* e;
        v = grpB;
        d = APM_P(anim, 0x30) + APM_S(kf, 0xc) * 4;
        e = d + APM_S(kf, 0x10) * 4;
        p = APM_P(pose, 0x50);
        if (nB != 0) memcpy_as4(grpB, p, nB * 0xc);
        for (; d < e; d += 4) {
            v += d[0] * 0xc;
            x = animS8a_(d);
            y = animS8b_(d);
            z = animS8c_(d);
            ((f32*)v)[0] += x * s;
            ((f32*)v)[1] += y * s;
            ((f32*)v)[2] += z * s;
        }
        }
        { u8* d; u8* e; u8* v;
        dt = *(f32*)(APM_P(anim, 0x28) + nextFrame * 0x2c) - *(f32*)(APM_P(anim, 0x28) + frame * 0x2c);
        d = APM_P(anim, 0x3c) + APM_S(kf, 0x24) * 4;
        e = d + APM_S(kf, 0x28) * 4;
        v = APM_P(pose, 0x64);
        p = APM_P(pose, 0x60);
        if (nD != 0) memcpy_as4(v, p, nD * 4);
        for (; d < e; d += 4) {
            b = (s8)d[3];
            v += d[0] * 4;
            if (b < 0x59 && b > -0x59) {
                x = animS8a_(d);
                t2 = t * t;
                t3 = t * t2;
                ((f32*)v)[0] = ((f32*)v)[0] + ((t + (t3 - 2.0f * t2)) * (dt * tanfTbl[(s8)d[2] + 0x59]) +
                                (EXT_LIT(float_neg2_80419ab8, -2.0f) * t3 + EXT_LIT(float_3_80419ad0, 3.0f) * t2) * (EXT_LIT(float_0p0625_80419acc, 0.0625f) * x) +
                                (t3 - t2) * (dt * tanfTbl[b + 0x59]));
            }
        }
        }
    }
    APM_S(pose, 0x3c) = frame;
    APM_F(pose, 0x40) = t;
    if (APM_U(pose, 0) & 8) {
        CameraEntry* cam = camGetPtr(CAMERA_3D);
        f = EXT_LIT(float_rad2deg_80419a94, 57.29579f) * (f32)atan2(-(cam->cameraAt.x - cam->cameraPos.x), -(cam->cameraAt.z - cam->cameraPos.z));
        while (f < EXT_LIT(float_neg360_80419a9c, -360.0f)) f += EXT_LIT(float_360_80419a98, 360.0f);
        while (f >= EXT_LIT(float_360_80419a98, 360.0f)) f -= EXT_LIT(float_360_80419a98, 360.0f);
        if (f < EXT_LIT(float_0_80419a48, 0.0f)) f += EXT_LIT(float_360_80419a98, 360.0f);
        f -= APM_F(pose, 0x74);
        while (f < EXT_LIT(float_neg360_80419a9c, -360.0f)) f += EXT_LIT(float_360_80419a98, 360.0f);
        while (f >= EXT_LIT(float_360_80419a98, 360.0f)) f -= EXT_LIT(float_360_80419a98, 360.0f);
        if ((f > EXT_LIT(float_90_80419aa0, 90.0f) && f <= EXT_LIT(float_270_80419aa4, 270.0f)) || (f < EXT_LIT(float_neg90_80419a90, -90.0f) && f >= EXT_LIT(float_neg270_80419aa8, -270.0f))) {
            APM_F(pose, 0x78) = -1.0f;
        } else {
            APM_F(pose, 0x78) = 1.0f;
        }
    }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void animPoseMain(s32 poseId) {
	asm volatile {
		opword 0x9421FF90
		opword 0x7C0802A6
		opword 0x90010074
		opword 0xDBE10060
		opword 0xF3E10068
		opword 0xDBC10050
		opword 0xF3C10058
		opword 0xBE410018
		lwz r6, wp(r13)
		opword 0x1C030170
		opword 0x38600004
		opword 0x80E60010
		opword 0x80A60000
		opword 0x64630004
		opword 0x7FE70214
		opword 0x809F0010
		opword 0x801F0014
		opword 0x54842036
		opword 0x7C852214
		opword 0x54003032
		opword 0x80840008
		opword 0x808400A0
		opword 0x83A40000
		opword 0x809D01AC
		opword 0x7C840214
		opword 0x83C4003C
		opword 0x7C72E3A6
		opword 0x38600005
		opword 0x64630005
		opword 0x7C73E3A6
		opword 0x38600006
		opword 0x64630006
		opword 0x7C74E3A6
		opword 0x38600007
		opword 0x64630007
		opword 0x7C75E3A6
		opword 0x800600E8
		opword 0x2C000000
		opword 0x41820010
		opword 0x838600F8
		opword 0x836600FC
		opword 0x4800000C
		opword 0x839F004C
		opword 0x837F0054
		opword 0x807F0090
		opword 0x2C03FFFF
		opword 0x4182001C
		opword 0x1C830170
		opword 0x38040004
		opword 0x7C07002E
		opword 0x540007BD
		opword 0x40820008
		bl animPoseMain
		opword 0x281E0000
		opword 0x41821844
		opword 0x801F000C
		opword 0x809E0024
		opword 0x2C000000
		opword 0x83440000
		opword 0x40820038
		opword 0x3C808000
		lwz r6, gp(r13)
		opword 0x800400F8
		opword 0x3C801062
		opword 0x38A44DD3
		opword 0x80660040
		opword 0x5400F0BE
		opword 0x80860044
		opword 0x7C050016
		opword 0x38A00000
		opword 0x5406D1BE
		bl __div2i
		opword 0x48000034
		opword 0x3C808000
		lwz r6, gp(r13)
		opword 0x800400F8
		opword 0x3C801062
		opword 0x38A44DD3
		opword 0x80660038
		opword 0x5400F0BE
		opword 0x8086003C
		opword 0x7C050016
		opword 0x38A00000
		opword 0x5406D1BE
		bl __div2i
		opword 0x80BF001C
		opword 0x801F0018
		opword 0x7C852010
		opword 0x7C601910
		bl __cvt_ull_flt
		lfs f0, float_60_80419ac4(r2)
		lfs f2, float_1000_80419ac8(r2)
		opword 0xEC200072
		lfs f0, float_0_80419a48(r2)
		opword 0xEC211024
		opword 0xD03F0020
		opword 0xC05F0020
		opword 0xC03F0044
		opword 0xEC220072
		opword 0xD03F0020
		opword 0x809E0024
		opword 0xC05F0020
		opword 0xC0240008
		opword 0xC0640004
		opword 0xEC811828
		opword 0xFC002000
		opword 0x40820010
		opword 0xEC021828
		opword 0xD01F0084
		opword 0x4800009C
		opword 0x2C1A0000
		opword 0x41820058
		opword 0xEC221828
		opword 0xFC010040
		opword 0x4080000C
		opword 0xD01F0084
		opword 0x48000080
		opword 0xEC012024
		opword 0x3C004330
		lis r4, double_to_int_802c2df0@ha
		opword 0x90010010
		lfd f1, double_to_int_802c2df0@l(r4)
		opword 0xD01F0084
		opword 0xC01F0084
		opword 0xFC00001E
		opword 0xD8010008
		opword 0x8001000C
		opword 0x6C008000
		opword 0x90010014
		opword 0xC8010010
		opword 0xEC000828
		opword 0xEC60113C
		opword 0x48000040
		opword 0xFC021840
		opword 0x4080000C
		opword 0xD01F0084
		opword 0x48000030
		opword 0xFC020840
		opword 0x40810018
		opword 0xEC021828
		opword 0xFC600890
		opword 0xEC002024
		opword 0xD01F0084
		opword 0x48000014
		opword 0xEC021828
		opword 0xFC601090
		opword 0xEC002024
		opword 0xD01F0084
		opword 0xD07F0024
		opword 0x38800000
		opword 0x801E0008
		opword 0xC03F0024
		opword 0x80BE0028
		opword 0x7C0903A6
		opword 0x2C000000
		opword 0x4081001C
		opword 0xC0050000
		opword 0xFC000840
		opword 0x41810010
		opword 0x38A5002C
		opword 0x38840001
		opword 0x4200FFEC
		opword 0x3804FFFF
		opword 0x38A00000
		opword 0x901F0028
		opword 0x809F0028
		opword 0x38040001
		opword 0x901F002C
		opword 0x801E0020
		opword 0xC03F0024
		opword 0x809E0040
		opword 0x7C0903A6
		opword 0x2C000000
		opword 0x4081001C
		opword 0xC0040000
		opword 0xFC000840
		opword 0x41810010
		opword 0x38840008
		opword 0x38A50001
		opword 0x4200FFEC
		opword 0x3805FFFF
		opword 0x2C1A0000
		opword 0x901F0034
		opword 0x809F0034
		opword 0x38040001
		opword 0x901F0038
		opword 0x40820034
		opword 0x809F002C
		opword 0x801E0008
		opword 0x7C040000
		opword 0x4180000C
		opword 0x801F0028
		opword 0x901F002C
		opword 0x809F0038
		opword 0x801E0020
		opword 0x7C040000
		opword 0x4180000C
		opword 0x801F0034
		opword 0x901F0038
		opword 0x801F0034
		opword 0x2C1A0000
		opword 0x809E0040
		opword 0x54001838
		opword 0x7C840214
		opword 0x80040004
		opword 0x901F0080
		opword 0x801F0028
		opword 0x80BE0028
		opword 0x1C00002C
		opword 0xC01F0024
		opword 0x7C25042E
		opword 0xEC400828
		opword 0x4182004C
		opword 0x809F002C
		opword 0x801E0008
		opword 0x7C040000
		opword 0x4180002C
		opword 0x38000000
		opword 0x901F002C
		opword 0x801F0028
		opword 0x80BE0024
		opword 0x1C00002C
		opword 0x809E0028
		opword 0xC0250008
		opword 0x7C04042E
		opword 0xEC210028
		opword 0x48000024
		opword 0x1C04002C
		opword 0x7C05042E
		opword 0xEC200828
		opword 0x48000014
		opword 0x801F002C
		opword 0x1C00002C
		opword 0x7C05042E
		opword 0xEC200828
		lfs f0, float_0_80419a48(r2)
		opword 0xFC000800
		opword 0x4082000C
		opword 0xD01F0030
		opword 0x4800000C
		opword 0xEC020824
		opword 0xD01F0030
		opword 0x833F0028
		opword 0x809F003C
		opword 0x835F002C
		opword 0x7C04C800
		opword 0xC3FF0030
		opword 0x831D00F0
		opword 0x82FD00F8
		opword 0x827D013C
		opword 0x82DD0140
		opword 0x825D012C
		opword 0x41820F54
		opword 0x2C04FFFF
		opword 0x4182000C
		opword 0x7C04C800
		opword 0x408107E4
		opword 0x1C99002C
		opword 0x801E0028
		opword 0x2C180000
		opword 0x7C150378
		opword 0x3A84002C
		opword 0x7E80A214
		opword 0x41820014
		opword 0x1CB8000C
		opword 0x807F0048
		opword 0x809D0154
		bl memcpy_as4
		opword 0x2C170000
		opword 0x41820014
		opword 0x1CB7000C
		opword 0x807F0050
		opword 0x809D015C
		bl memcpy_as4
		opword 0x2C130000
		opword 0x41820014
		opword 0x807F0058
		opword 0x7E659B78
		opword 0x809D01A0
		bl memcpy
		opword 0x2C160000
		opword 0x41820014
		opword 0x807F0060
		opword 0x56C5103A
		opword 0x809D01A4
		bl memcpy_as4
		opword 0x2C120000
		opword 0x41820014
		opword 0x1CB20018
		opword 0x807F0068
		opword 0x809D0190
		bl memcpy_as4
		opword 0x801F003C
		opword 0x2C00FFFF
		opword 0x4082000C
		opword 0x38000000
		opword 0x901F003C
		lfs f2, float_0p0625_80419acc(r2)
		opword 0x48000730
		opword 0x80950004
		opword 0x80150008
		opword 0x80BE002C
		opword 0x5484103A
		opword 0x5400103A
		opword 0x80DF0048
		opword 0x7CA52214
		opword 0x7CE50214
		opword 0x38870003
		opword 0x7C852050
		opword 0x7C053840
		opword 0x5484F0BE
		opword 0x40800158
		opword 0x5480F0BF
		opword 0x7C0903A6
		opword 0x41820104
		opword 0x88050000
		opword 0x1C00000C
		opword 0x7CC60214
		opword 0xE025C001
		opword 0xE065C002
		opword 0xE085C003
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0xC0060004
		opword 0xEC0200FA
		opword 0xD0060004
		opword 0xC0060008
		opword 0xEC02013A
		opword 0xD0060008
		opword 0x88050004
		opword 0x1C00000C
		opword 0x7CC60214
		opword 0xE025C005
		opword 0xE065C006
		opword 0xE085C007
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0xC0060004
		opword 0xEC0200FA
		opword 0xD0060004
		opword 0xC0060008
		opword 0xEC02013A
		opword 0xD0060008
		opword 0x88050008
		opword 0x1C00000C
		opword 0x7CC60214
		opword 0xE025C009
		opword 0xE065C00A
		opword 0xE085C00B
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0xC0060004
		opword 0xEC0200FA
		opword 0xD0060004
		opword 0xC0060008
		opword 0xEC02013A
		opword 0xD0060008
		opword 0x8805000C
		opword 0x1C00000C
		opword 0x7CC60214
		opword 0xE025C00D
		opword 0xE065C00E
		opword 0xE085C00F
		opword 0x38A50010
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0xC0060004
		opword 0xEC0200FA
		opword 0xD0060004
		opword 0xC0060008
		opword 0xEC02013A
		opword 0xD0060008
		opword 0x4200FF0C
		opword 0x70840003
		opword 0x4182004C
		opword 0x7C8903A6
		opword 0x88050000
		opword 0x1C00000C
		opword 0x7CC60214
		opword 0xE025C001
		opword 0xE065C002
		opword 0xE085C003
		opword 0x38A50004
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0xC0060004
		opword 0xEC0200FA
		opword 0xD0060004
		opword 0xC0060008
		opword 0xEC02013A
		opword 0xD0060008
		opword 0x4200FFC0
		opword 0x8095000C
		opword 0x80150010
		opword 0x80BE0030
		opword 0x5484103A
		opword 0x5400103A
		opword 0x80DF0050
		opword 0x7CA52214
		opword 0x7CE50214
		opword 0x38870003
		opword 0x7C852050
		opword 0x7C053840
		opword 0x5484F0BE
		opword 0x40800158
		opword 0x5480F0BF
		opword 0x7C0903A6
		opword 0x41820104
		opword 0x88050000
		opword 0x1C00000C
		opword 0x7CC60214
		opword 0xE025C001
		opword 0xE065C002
		opword 0xE085C003
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0xC0060004
		opword 0xEC0200FA
		opword 0xD0060004
		opword 0xC0060008
		opword 0xEC02013A
		opword 0xD0060008
		opword 0x88050004
		opword 0x1C00000C
		opword 0x7CC60214
		opword 0xE025C005
		opword 0xE065C006
		opword 0xE085C007
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0xC0060004
		opword 0xEC0200FA
		opword 0xD0060004
		opword 0xC0060008
		opword 0xEC02013A
		opword 0xD0060008
		opword 0x88050008
		opword 0x1C00000C
		opword 0x7CC60214
		opword 0xE025C009
		opword 0xE065C00A
		opword 0xE085C00B
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0xC0060004
		opword 0xEC0200FA
		opword 0xD0060004
		opword 0xC0060008
		opword 0xEC02013A
		opword 0xD0060008
		opword 0x8805000C
		opword 0x1C00000C
		opword 0x7CC60214
		opword 0xE025C00D
		opword 0xE065C00E
		opword 0xE085C00F
		opword 0x38A50010
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0xC0060004
		opword 0xEC0200FA
		opword 0xD0060004
		opword 0xC0060008
		opword 0xEC02013A
		opword 0xD0060008
		opword 0x4200FF0C
		opword 0x70840003
		opword 0x4182004C
		opword 0x7C8903A6
		opword 0x88050000
		opword 0x1C00000C
		opword 0x7CC60214
		opword 0xE025C001
		opword 0xE065C002
		opword 0xE085C003
		opword 0x38A50004
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0xC0060004
		opword 0xEC0200FA
		opword 0xD0060004
		opword 0xC0060008
		opword 0xEC02013A
		opword 0xD0060008
		opword 0x4200FFC0
		opword 0x8095001C
		opword 0x80150020
		opword 0x80BE0038
		opword 0x5484083C
		opword 0x5400083C
		opword 0x80FF0058
		opword 0x7CC52214
		opword 0x7CA60214
		opword 0x38850001
		opword 0x7C862050
		opword 0x7C062840
		opword 0x5484F87E
		opword 0x40800104
		opword 0x5480E8FF
		opword 0x7C0903A6
		opword 0x418200D4
		opword 0x88A60000
		opword 0x88060001
		opword 0x7CE72A14
		opword 0x88A70000
		opword 0x7C050214
		opword 0x98070000
		opword 0x88A60002
		opword 0x88060003
		opword 0x7CE72A14
		opword 0x88A70000
		opword 0x7C050214
		opword 0x98070000
		opword 0x88A60004
		opword 0x88060005
		opword 0x7CE72A14
		opword 0x88A70000
		opword 0x7C050214
		opword 0x98070000
		opword 0x88A60006
		opword 0x88060007
		opword 0x7CE72A14
		opword 0x88A70000
		opword 0x7C050214
		opword 0x98070000
		opword 0x88A60008
		opword 0x88060009
		opword 0x7CE72A14
		opword 0x88A70000
		opword 0x7C050214
		opword 0x98070000
		opword 0x88A6000A
		opword 0x8806000B
		opword 0x7CE72A14
		opword 0x88A70000
		opword 0x7C050214
		opword 0x98070000
		opword 0x88A6000C
		opword 0x8806000D
		opword 0x7CE72A14
		opword 0x88A70000
		opword 0x7C050214
		opword 0x98070000
		opword 0x88A6000E
		opword 0x8806000F
		opword 0x38C60010
		opword 0x7CE72A14
		opword 0x88A70000
		opword 0x7C050214
		opword 0x98070000
		opword 0x4200FF3C
		opword 0x70840007
		opword 0x41820028
		opword 0x7C8903A6
		opword 0x88A60000
		opword 0x88060001
		opword 0x38C60002
		opword 0x7CE72A14
		opword 0x88A70000
		opword 0x7C050214
		opword 0x98070000
		opword 0x4200FFE4
		opword 0x80950024
		opword 0x80150028
		opword 0x80BE003C
		opword 0x5484103A
		opword 0x5400103A
		opword 0x80DF0060
		opword 0x7CA52214
		opword 0x7CE50214
		opword 0x38870003
		opword 0x7C852050
		opword 0x7C053840
		opword 0x5484F0BE
		opword 0x40800128
		opword 0x5480E8FF
		opword 0x7C0903A6
		opword 0x418200F4
		opword 0x88050000
		opword 0x5400103A
		opword 0x7CC60214
		opword 0xE025C001
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0x88050004
		opword 0x5400103A
		opword 0x7CC60214
		opword 0xE025C005
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0x88050008
		opword 0x5400103A
		opword 0x7CC60214
		opword 0xE025C009
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0x8805000C
		opword 0x5400103A
		opword 0x7CC60214
		opword 0xE025C00D
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0x88050010
		opword 0x5400103A
		opword 0x7CC60214
		opword 0xE025C011
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0x88050014
		opword 0x5400103A
		opword 0x7CC60214
		opword 0xE025C015
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0x88050018
		opword 0x5400103A
		opword 0x7CC60214
		opword 0xE025C019
		opword 0xC0060000
		opword 0xEC02007A
		opword 0xD0060000
		opword 0x8805001C
		opword 0x5400103A
		opword 0x7CC60214
		opword 0xE025C01D
		opword 0xC0060000
		opword 0x38A50020
		opword 0xEC02007A
		opword 0xD0060000
		opword 0x4200FF1C
		opword 0x70840007
		opword 0x4182002C
		opword 0x7C8903A6
		opword 0x88050000
		opword 0x5400103A
		opword 0x7CC60214
		opword 0xE025C001
		opword 0xC0060000
		opword 0x38A50004
		opword 0xEC02007A
		opword 0xD0060000
		opword 0x4200FFE0
		opword 0x80B50014
		opword 0x3800000C
		opword 0x80950018
		opword 0x1CA5000C
		opword 0x80DE0034
		opword 0x80FF0068
		opword 0x1C84000C
		opword 0x7CC62A14
		opword 0x7CA62214
		opword 0x3885000B
		opword 0x7C862050
		opword 0x7C062840
		opword 0x7C840396
		opword 0x40800158
		opword 0x5480F0BF
		opword 0x7C0903A6
		opword 0x41820104
		opword 0x88A60000
		opword 0x88060001
		opword 0x1CA50018
		opword 0x7CE72A14
		opword 0x88A70000
		opword 0x7C050214
		opword 0x98070000
		opword 0xC0270004
		opword 0xC0060004
		opword 0xEC01002A
		opword 0xD0070004
		opword 0xC0270008
		opword 0xC0060008
		opword 0xEC01002A
		opword 0xD0070008
		opword 0x88A6000C
		opword 0x8806000D
		opword 0x1CA50018
		opword 0x7CE72A14
		opword 0x88A70000
		opword 0x7C050214
		opword 0x98070000
		opword 0xC0270004
		opword 0xC0060010
		opword 0xEC01002A
		opword 0xD0070004
		opword 0xC0270008
		opword 0xC0060014
		opword 0xEC01002A
		opword 0xD0070008
		opword 0x88A60018
		opword 0x88060019
		opword 0x1CA50018
		opword 0x7CE72A14
		opword 0x88A70000
		opword 0x7C050214
		opword 0x98070000
		opword 0xC0270004
		opword 0xC006001C
		opword 0xEC01002A
		opword 0xD0070004
		opword 0xC0270008
		opword 0xC0060020
		opword 0xEC01002A
		opword 0xD0070008
		opword 0x88A60024
		opword 0x88060025
		opword 0x1CA50018
		opword 0x7CE72A14
		opword 0x88A70000
		opword 0x7C050214
		opword 0x98070000
		opword 0xC0270004
		opword 0xC0060028
		opword 0xEC01002A
		opword 0xD0070004
		opword 0xC006002C
		opword 0x38C60030
		opword 0xC0270008
		opword 0xEC01002A
		opword 0xD0070008
		opword 0x4200FF0C
		opword 0x70840003
		opword 0x4182004C
		opword 0x7C8903A6
		opword 0x88A60000
		opword 0x88060001
		opword 0x1CA50018
		opword 0x7CE72A14
		opword 0x88A70000
		opword 0x7C050214
		opword 0x98070000
		opword 0xC0270004
		opword 0xC0060004
		opword 0xEC01002A
		opword 0xD0070004
		opword 0xC0060008
		opword 0x38C6000C
		opword 0xC0270008
		opword 0xEC01002A
		opword 0xD0070008
		opword 0x4200FFC0
		opword 0x3AB5002C
		opword 0x7C15A040
		opword 0x4180F8D0
		opword 0x48000778
		opword 0x40800774
		opword 0x38840001
		opword 0x38190001
		opword 0x1C84002C
		opword 0x80BE0028
		lfs f2, float_0p0625_80419acc(r2)
		opword 0x1C00002C
		opword 0x7C852214
		opword 0x7C050214
		opword 0x48000730
		opword 0x80C40004
		opword 0x80A40008
		opword 0x80FE002C
		opword 0x54C6103A
		opword 0x54A5103A
		opword 0x811F0048
		opword 0x7CE73214
		opword 0x7CA72A14
		opword 0x38C50003
		opword 0x7CC73050
		opword 0x7C072840
		opword 0x54C6F0BE
		opword 0x40800158
		opword 0x54C5F0BF
		opword 0x7CA903A6
		opword 0x41820104
		opword 0x88A70000
		opword 0x1CA5000C
		opword 0x7D082A14
		opword 0xE027C001
		opword 0xE067C002
		opword 0xE087C003
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0xC0080004
		opword 0xEC0200FA
		opword 0xD0080004
		opword 0xC0080008
		opword 0xEC02013A
		opword 0xD0080008
		opword 0x88A70004
		opword 0x1CA5000C
		opword 0x7D082A14
		opword 0xE027C005
		opword 0xE067C006
		opword 0xE087C007
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0xC0080004
		opword 0xEC0200FA
		opword 0xD0080004
		opword 0xC0080008
		opword 0xEC02013A
		opword 0xD0080008
		opword 0x88A70008
		opword 0x1CA5000C
		opword 0x7D082A14
		opword 0xE027C009
		opword 0xE067C00A
		opword 0xE087C00B
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0xC0080004
		opword 0xEC0200FA
		opword 0xD0080004
		opword 0xC0080008
		opword 0xEC02013A
		opword 0xD0080008
		opword 0x88A7000C
		opword 0x1CA5000C
		opword 0x7D082A14
		opword 0xE027C00D
		opword 0xE067C00E
		opword 0xE087C00F
		opword 0x38E70010
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0xC0080004
		opword 0xEC0200FA
		opword 0xD0080004
		opword 0xC0080008
		opword 0xEC02013A
		opword 0xD0080008
		opword 0x4200FF0C
		opword 0x70C60003
		opword 0x4182004C
		opword 0x7CC903A6
		opword 0x88A70000
		opword 0x1CA5000C
		opword 0x7D082A14
		opword 0xE027C001
		opword 0xE067C002
		opword 0xE087C003
		opword 0x38E70004
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0xC0080004
		opword 0xEC0200FA
		opword 0xD0080004
		opword 0xC0080008
		opword 0xEC02013A
		opword 0xD0080008
		opword 0x4200FFC0
		opword 0x80C4000C
		opword 0x80A40010
		opword 0x80FE0030
		opword 0x54C6103A
		opword 0x54A5103A
		opword 0x811F0050
		opword 0x7CE73214
		opword 0x7CA72A14
		opword 0x38C50003
		opword 0x7CC73050
		opword 0x7C072840
		opword 0x54C6F0BE
		opword 0x40800158
		opword 0x54C5F0BF
		opword 0x7CA903A6
		opword 0x41820104
		opword 0x88A70000
		opword 0x1CA5000C
		opword 0x7D082A14
		opword 0xE027C001
		opword 0xE067C002
		opword 0xE087C003
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0xC0080004
		opword 0xEC0200FA
		opword 0xD0080004
		opword 0xC0080008
		opword 0xEC02013A
		opword 0xD0080008
		opword 0x88A70004
		opword 0x1CA5000C
		opword 0x7D082A14
		opword 0xE027C005
		opword 0xE067C006
		opword 0xE087C007
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0xC0080004
		opword 0xEC0200FA
		opword 0xD0080004
		opword 0xC0080008
		opword 0xEC02013A
		opword 0xD0080008
		opword 0x88A70008
		opword 0x1CA5000C
		opword 0x7D082A14
		opword 0xE027C009
		opword 0xE067C00A
		opword 0xE087C00B
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0xC0080004
		opword 0xEC0200FA
		opword 0xD0080004
		opword 0xC0080008
		opword 0xEC02013A
		opword 0xD0080008
		opword 0x88A7000C
		opword 0x1CA5000C
		opword 0x7D082A14
		opword 0xE027C00D
		opword 0xE067C00E
		opword 0xE087C00F
		opword 0x38E70010
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0xC0080004
		opword 0xEC0200FA
		opword 0xD0080004
		opword 0xC0080008
		opword 0xEC02013A
		opword 0xD0080008
		opword 0x4200FF0C
		opword 0x70C60003
		opword 0x4182004C
		opword 0x7CC903A6
		opword 0x88A70000
		opword 0x1CA5000C
		opword 0x7D082A14
		opword 0xE027C001
		opword 0xE067C002
		opword 0xE087C003
		opword 0x38E70004
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0xC0080004
		opword 0xEC0200FA
		opword 0xD0080004
		opword 0xC0080008
		opword 0xEC02013A
		opword 0xD0080008
		opword 0x4200FFC0
		opword 0x80C4001C
		opword 0x80A40020
		opword 0x80FE0038
		opword 0x54C6083C
		opword 0x54A5083C
		opword 0x813F0058
		opword 0x7D073214
		opword 0x7CA82A14
		opword 0x38C50001
		opword 0x7CC83050
		opword 0x7C082840
		opword 0x54C6F87E
		opword 0x40800104
		opword 0x54C5E8FF
		opword 0x7CA903A6
		opword 0x418200D4
		opword 0x88E80000
		opword 0x88A80001
		opword 0x7D293A14
		opword 0x88E90000
		opword 0x7CA72A14
		opword 0x98A90000
		opword 0x88E80002
		opword 0x88A80003
		opword 0x7D293A14
		opword 0x88E90000
		opword 0x7CA72A14
		opword 0x98A90000
		opword 0x88E80004
		opword 0x88A80005
		opword 0x7D293A14
		opword 0x88E90000
		opword 0x7CA72A14
		opword 0x98A90000
		opword 0x88E80006
		opword 0x88A80007
		opword 0x7D293A14
		opword 0x88E90000
		opword 0x7CA72A14
		opword 0x98A90000
		opword 0x88E80008
		opword 0x88A80009
		opword 0x7D293A14
		opword 0x88E90000
		opword 0x7CA72A14
		opword 0x98A90000
		opword 0x88E8000A
		opword 0x88A8000B
		opword 0x7D293A14
		opword 0x88E90000
		opword 0x7CA72A14
		opword 0x98A90000
		opword 0x88E8000C
		opword 0x88A8000D
		opword 0x7D293A14
		opword 0x88E90000
		opword 0x7CA72A14
		opword 0x98A90000
		opword 0x88E8000E
		opword 0x88A8000F
		opword 0x39080010
		opword 0x7D293A14
		opword 0x88E90000
		opword 0x7CA72A14
		opword 0x98A90000
		opword 0x4200FF3C
		opword 0x70C60007
		opword 0x41820028
		opword 0x7CC903A6
		opword 0x88E80000
		opword 0x88A80001
		opword 0x39080002
		opword 0x7D293A14
		opword 0x88E90000
		opword 0x7CA72A14
		opword 0x98A90000
		opword 0x4200FFE4
		opword 0x80C40024
		opword 0x80A40028
		opword 0x80FE003C
		opword 0x54C6103A
		opword 0x54A5103A
		opword 0x811F0060
		opword 0x7CE73214
		opword 0x7CA72A14
		opword 0x38C50003
		opword 0x7CC73050
		opword 0x7C072840
		opword 0x54C6F0BE
		opword 0x40800128
		opword 0x54C5E8FF
		opword 0x7CA903A6
		opword 0x418200F4
		opword 0x88A70000
		opword 0x54A5103A
		opword 0x7D082A14
		opword 0xE027C001
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0x88A70004
		opword 0x54A5103A
		opword 0x7D082A14
		opword 0xE027C005
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0x88A70008
		opword 0x54A5103A
		opword 0x7D082A14
		opword 0xE027C009
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0x88A7000C
		opword 0x54A5103A
		opword 0x7D082A14
		opword 0xE027C00D
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0x88A70010
		opword 0x54A5103A
		opword 0x7D082A14
		opword 0xE027C011
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0x88A70014
		opword 0x54A5103A
		opword 0x7D082A14
		opword 0xE027C015
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0x88A70018
		opword 0x54A5103A
		opword 0x7D082A14
		opword 0xE027C019
		opword 0xC0080000
		opword 0xEC02007A
		opword 0xD0080000
		opword 0x88A7001C
		opword 0x54A5103A
		opword 0x7D082A14
		opword 0xE027C01D
		opword 0xC0080000
		opword 0x38E70020
		opword 0xEC02007A
		opword 0xD0080000
		opword 0x4200FF1C
		opword 0x70C60007
		opword 0x4182002C
		opword 0x7CC903A6
		opword 0x88A70000
		opword 0x54A5103A
		opword 0x7D082A14
		opword 0xE027C001
		opword 0xC0080000
		opword 0x38E70004
		opword 0xEC02007A
		opword 0xD0080000
		opword 0x4200FFE0
		opword 0x80E40014
		opword 0x38A0000C
		opword 0x80C40018
		opword 0x1CE7000C
		opword 0x811E0034
		opword 0x813F0068
		opword 0x1CC6000C
		opword 0x7D083A14
		opword 0x7CE83214
		opword 0x38C7000B
		opword 0x7CC83050
		opword 0x7C083840
		opword 0x7CC62B96
		opword 0x40800158
		opword 0x54C5F0BF
		opword 0x7CA903A6
		opword 0x41820104
		opword 0x88E80000
		opword 0x88A80001
		opword 0x1CE70018
		opword 0x7D293A14
		opword 0x88E90000
		opword 0x7CA72A14
		opword 0x98A90000
		opword 0xC0290004
		opword 0xC0080004
		opword 0xEC01002A
		opword 0xD0090004
		opword 0xC0290008
		opword 0xC0080008
		opword 0xEC01002A
		opword 0xD0090008
		opword 0x88E8000C
		opword 0x88A8000D
		opword 0x1CE70018
		opword 0x7D293A14
		opword 0x88E90000
		opword 0x7CA72A14
		opword 0x98A90000
		opword 0xC0290004
		opword 0xC0080010
		opword 0xEC01002A
		opword 0xD0090004
		opword 0xC0290008
		opword 0xC0080014
		opword 0xEC01002A
		opword 0xD0090008
		opword 0x88E80018
		opword 0x88A80019
		opword 0x1CE70018
		opword 0x7D293A14
		opword 0x88E90000
		opword 0x7CA72A14
		opword 0x98A90000
		opword 0xC0290004
		opword 0xC008001C
		opword 0xEC01002A
		opword 0xD0090004
		opword 0xC0290008
		opword 0xC0080020
		opword 0xEC01002A
		opword 0xD0090008
		opword 0x88E80024
		opword 0x88A80025
		opword 0x1CE70018
		opword 0x7D293A14
		opword 0x88E90000
		opword 0x7CA72A14
		opword 0x98A90000
		opword 0xC0290004
		opword 0xC0080028
		opword 0xEC01002A
		opword 0xD0090004
		opword 0xC008002C
		opword 0x39080030
		opword 0xC0290008
		opword 0xEC01002A
		opword 0xD0090008
		opword 0x4200FF0C
		opword 0x70C60003
		opword 0x4182004C
		opword 0x7CC903A6
		opword 0x88E80000
		opword 0x88A80001
		opword 0x1CE70018
		opword 0x7D293A14
		opword 0x88E90000
		opword 0x7CA72A14
		opword 0x98A90000
		opword 0xC0290004
		opword 0xC0080004
		opword 0xEC01002A
		opword 0xD0090004
		opword 0xC0080008
		opword 0x3908000C
		opword 0xC0290008
		opword 0xEC01002A
		opword 0xD0090008
		opword 0x4200FFC0
		opword 0x3884002C
		opword 0x7C040040
		opword 0x4180F8D0
		opword 0x48000018
		opword 0xC01F0040
		opword 0xFC00F840
		opword 0x4081000C
		lfs f0, float_0_80419a48(r2)
		opword 0xD01F0040
		opword 0x7C19D000
		opword 0x40820050
		opword 0x2C180000
		opword 0x41820014
		opword 0x1CB8000C
		opword 0x809F0048
		opword 0x7F83E378
		bl memcpy_as4
		opword 0x2C170000
		opword 0x41820014
		opword 0x1CB7000C
		opword 0x809F0050
		opword 0x7F63DB78
		bl memcpy_as4
		opword 0x2C160000
		opword 0x41820478
		opword 0x807F0064
		opword 0x56C5103A
		opword 0x809F0060
		bl memcpy_as4
		opword 0x48000464
		opword 0x41810460
		opword 0x1F5A002C
		opword 0x801E0028
		lfs f0, float_0p0625_80419acc(r2)
		opword 0x2C180000
		opword 0x80DE002C
		opword 0x7E80D214
		opword 0x80940004
		opword 0xEFC007F2
		opword 0x80140008
		opword 0x5485103A
		opword 0x809F0048
		opword 0x7EA62A14
		opword 0x5400103A
		opword 0x7E550214
		opword 0x41820010
		opword 0x1CB8000C
		opword 0x7F83E378
		bl memcpy_as4
		opword 0x38920003
		opword 0x7C159040
		opword 0x7C952050
		opword 0x5484F0BE
		opword 0x40800158
		opword 0x5480F0BF
		opword 0x7C0903A6
		opword 0x41820104
		opword 0x88150000
		opword 0x1C00000C
		opword 0x7F9C0214
		opword 0xE035C001
		opword 0xE055C002
		opword 0xE075C003
		opword 0xC01C0000
		opword 0xEC0107BA
		opword 0xD01C0000
		opword 0xC01C0004
		opword 0xEC0207BA
		opword 0xD01C0004
		opword 0xC01C0008
		opword 0xEC0307BA
		opword 0xD01C0008
		opword 0x88150004
		opword 0x1C00000C
		opword 0x7F9C0214
		opword 0xE035C005
		opword 0xE055C006
		opword 0xE075C007
		opword 0xC01C0000
		opword 0xEC0107BA
		opword 0xD01C0000
		opword 0xC01C0004
		opword 0xEC0207BA
		opword 0xD01C0004
		opword 0xC01C0008
		opword 0xEC0307BA
		opword 0xD01C0008
		opword 0x88150008
		opword 0x1C00000C
		opword 0x7F9C0214
		opword 0xE035C009
		opword 0xE055C00A
		opword 0xE075C00B
		opword 0xC01C0000
		opword 0xEC0107BA
		opword 0xD01C0000
		opword 0xC01C0004
		opword 0xEC0207BA
		opword 0xD01C0004
		opword 0xC01C0008
		opword 0xEC0307BA
		opword 0xD01C0008
		opword 0x8815000C
		opword 0x1C00000C
		opword 0x7F9C0214
		opword 0xE035C00D
		opword 0xE055C00E
		opword 0xE075C00F
		opword 0x3AB50010
		opword 0xC01C0000
		opword 0xEC0107BA
		opword 0xD01C0000
		opword 0xC01C0004
		opword 0xEC0207BA
		opword 0xD01C0004
		opword 0xC01C0008
		opword 0xEC0307BA
		opword 0xD01C0008
		opword 0x4200FF0C
		opword 0x70840003
		opword 0x4182004C
		opword 0x7C8903A6
		opword 0x88150000
		opword 0x1C00000C
		opword 0x7F9C0214
		opword 0xE035C001
		opword 0xE055C002
		opword 0xE075C003
		opword 0x3AB50004
		opword 0xC01C0000
		opword 0xEC0107BA
		opword 0xD01C0000
		opword 0xC01C0004
		opword 0xEC0207BA
		opword 0xD01C0004
		opword 0xC01C0008
		opword 0xEC0307BA
		opword 0xD01C0008
		opword 0x4200FFC0
		opword 0x8094000C
		opword 0x2C170000
		opword 0x80140010
		opword 0x7F75DB78
		opword 0x80DE0030
		opword 0x5485103A
		opword 0x5400103A
		opword 0x809F0050
		opword 0x7E462A14
		opword 0x7E720214
		opword 0x41820010
		opword 0x1CB7000C
		opword 0x7F63DB78
		bl memcpy_as4
		opword 0x38930003
		opword 0x7C129840
		opword 0x7C922050
		opword 0x5484F0BE
		opword 0x40800158
		opword 0x5480F0BF
		opword 0x7C0903A6
		opword 0x41820104
		opword 0x88120000
		opword 0x1C00000C
		opword 0x7EB50214
		opword 0xE032C001
		opword 0xE052C002
		opword 0xE072C003
		opword 0xC0150000
		opword 0xEC0107BA
		opword 0xD0150000
		opword 0xC0150004
		opword 0xEC0207BA
		opword 0xD0150004
		opword 0xC0150008
		opword 0xEC0307BA
		opword 0xD0150008
		opword 0x88120004
		opword 0x1C00000C
		opword 0x7EB50214
		opword 0xE032C005
		opword 0xE052C006
		opword 0xE072C007
		opword 0xC0150000
		opword 0xEC0107BA
		opword 0xD0150000
		opword 0xC0150004
		opword 0xEC0207BA
		opword 0xD0150004
		opword 0xC0150008
		opword 0xEC0307BA
		opword 0xD0150008
		opword 0x88120008
		opword 0x1C00000C
		opword 0x7EB50214
		opword 0xE032C009
		opword 0xE052C00A
		opword 0xE072C00B
		opword 0xC0150000
		opword 0xEC0107BA
		opword 0xD0150000
		opword 0xC0150004
		opword 0xEC0207BA
		opword 0xD0150004
		opword 0xC0150008
		opword 0xEC0307BA
		opword 0xD0150008
		opword 0x8812000C
		opword 0x1C00000C
		opword 0x7EB50214
		opword 0xE032C00D
		opword 0xE052C00E
		opword 0xE072C00F
		opword 0x3A520010
		opword 0xC0150000
		opword 0xEC0107BA
		opword 0xD0150000
		opword 0xC0150004
		opword 0xEC0207BA
		opword 0xD0150004
		opword 0xC0150008
		opword 0xEC0307BA
		opword 0xD0150008
		opword 0x4200FF0C
		opword 0x70840003
		opword 0x4182004C
		opword 0x7C8903A6
		opword 0x88120000
		opword 0x1C00000C
		opword 0x7EB50214
		opword 0xE032C001
		opword 0xE052C002
		opword 0xE072C003
		opword 0x3A520004
		opword 0xC0150000
		opword 0xEC0107BA
		opword 0xD0150000
		opword 0xC0150004
		opword 0xEC0207BA
		opword 0xD0150004
		opword 0xC0150008
		opword 0xEC0307BA
		opword 0xD0150008
		opword 0x4200FFC0
		opword 0x1C19002C
		opword 0x80DE0028
		opword 0x80B40024
		opword 0x2C160000
		opword 0x80940028
		opword 0x7C26D42E
		opword 0x7C06042E
		opword 0x54A5103A
		opword 0x80DE003C
		opword 0x5480103A
		opword 0xEFC10028
		opword 0x809F0060
		opword 0x7E862A14
		opword 0x82BF0064
		opword 0x7E540214
		opword 0x41820010
		opword 0x7EA3AB78
		opword 0x56C5103A
		bl memcpy_as4
		opword 0x38120003
		opword 0xED1F07F2
		opword 0x7C140050
		opword 0x5400F0BE
		opword 0x7C0903A6
		opword 0x7C149040
		opword 0x408000A8
		opword 0x88940003
		opword 0x88140000
		opword 0x7C860774
		opword 0x2C060059
		opword 0x5400103A
		opword 0x7EB50214
		opword 0x40800084
		opword 0x2C06FFA7
		opword 0x4081007C
		opword 0xE0D4C001
		opword 0xECFF0232
		opword 0x88140002
		lis r4, tanfTbl@ha
		lfs f0, float_2_80419a84(r2)
		addi r5, r4, tanfTbl@l
		opword 0x7C000774
		opword 0x5400103A
		opword 0xEC203A3C
		opword 0x7C850214
		lfs f2, float_3_80419ad0(r2)
		opword 0xC0040164
		opword 0x54C0103A
		opword 0xEC620232
		lfs f4, float_neg2_80419ab8(r2)
		opword 0xEC3F082A
		opword 0xEC1E0032
		lfs f2, float_0p0625_80419acc(r2)
		opword 0x7C850214
		opword 0xC0A40164
		opword 0xEC6419FA
		opword 0xEC4201B2
		opword 0xEC010032
		opword 0xC0D50000
		opword 0xEC874028
		opword 0xEC3E0172
		opword 0xEC0300BA
		opword 0xEC04007A
		opword 0xEC06002A
		opword 0xD0150000
		opword 0x3A940004
		opword 0x4200FF60
		opword 0x933F003C
		opword 0xD3FF0040
		opword 0x801F0000
		opword 0x54000739
		opword 0x41820100
		opword 0x38600004
		bl camGetPtr
		opword 0xC0630018
		opword 0xC043000C
		opword 0xC0230020
		opword 0xC0030014
		opword 0xEC431028
		opword 0xEC010028
		opword 0xFC201050
		opword 0xFC400050
		bl atan2
		opword 0xFC600818
		lfs f2, float_rad2deg_80419a94(r2)
		lfs f1, float_360_80419a98(r2)
		lfs f0, float_neg360_80419a9c(r2)
		opword 0xEC4200F2
		opword 0x48000008
		opword 0xEC42082A
		opword 0xFC020040
		opword 0x4180FFF8
		lfs f1, float_360_80419a98(r2)
		opword 0x48000008
		opword 0xEC420828
		opword 0xFC020840
		opword 0x4C411382
		opword 0x4182FFF4
		lfs f0, float_0_80419a48(r2)
		opword 0xFC020040
		opword 0x40800008
		opword 0xEC42082A
		opword 0xC01F0074
		lfs f1, float_360_80419a98(r2)
		opword 0xEC420028
		lfs f0, float_neg360_80419a9c(r2)
		opword 0x48000008
		opword 0xEC42082A
		opword 0xFC020040
		opword 0x4180FFF8
		lfs f0, float_360_80419a98(r2)
		opword 0x48000008
		opword 0xEC420028
		opword 0xFC020040
		opword 0x4C411382
		opword 0x4182FFF4
		lfs f0, float_90_80419aa0(r2)
		opword 0xFC020040
		opword 0x40810014
		lfs f0, float_270_80419aa4(r2)
		opword 0xFC020040
		opword 0x4C401382
		opword 0x41820020
		lfs f0, float_neg90_80419a90(r2)
		opword 0xFC020040
		opword 0x40800020
		lfs f0, float_neg270_80419aa8(r2)
		opword 0xFC020040
		opword 0x4C411382
		opword 0x40820010
		lfs f0, float_neg1_80419a8c(r2)
		opword 0xD01F0078
		opword 0x4800000C
		lfs f0, float_1_80419a44(r2)
		opword 0xD01F0078
		opword 0xE3E10068
		opword 0xCBE10060
		opword 0xE3C10058
		opword 0xCBC10050
		opword 0xBA410018
		opword 0x80010074
		opword 0x7C0803A6
		opword 0x38210070
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
void pushGXModelMtx_TransformNode__(AnimPoseNode* node) {
    Mtx trans, scale, rot, tmp;
    Mtx sc1, sc2, sc3;
    Mtx rc1, rc2, rc3;
    MtxPtr p;
    u32 flags;
    f32 sx, sy, sz;
    f32 rx, ry, rz;
    f32 rcx, rcy, rcz;
    f32 scx, scy, scz;
    f32 rtx, rty, rtz;
    f32 stx, sty, stz;
    f32 tx, ty, tz;

    flags = 0;
    tx = node->mTranslation.x;
    ty = node->mTranslation.y;
    tz = node->mTranslation.z;
    sx = node->mScale.x;
    sy = node->mScale.y;
    sz = node->mScale.z;
    rx = EXT_LIT(float_2_80419a84, 2.0f) * node->mRot1.x;
    ry = EXT_LIT(float_2_80419a84, 2.0f) * node->mRot1.y;
    rz = EXT_LIT(float_2_80419a84, 2.0f) * node->mRot1.z;
    rcx = node->mRotationCenter.x;
    rcy = node->mRotationCenter.y;
    rcz = node->mRotationCenter.z;
    scx = node->mScaleCenter.x;
    scy = node->mScaleCenter.y;
    scz = node->mScaleCenter.z;
    rtx = node->mRotationTranslation.x;
    rty = node->mRotationTranslation.y;
    rtz = node->mRotationTranslation.z;
    stx = node->mScaleTranslation.x;
    sty = node->mScaleTranslation.y;
    stz = node->mScaleTranslation.z;

    if (tx || ty || tz) {
        PSMTXTrans(trans, tx, ty, tz);
        flags |= 1;
    }
    if (sx != EXT_LIT(float_1_80419a44, 1.0f) || sy != EXT_LIT(float_1_80419a44, 1.0f) || sz != EXT_LIT(float_1_80419a44, 1.0f)) {
        PSMTXScale(scale, sx, sy, sz);
        flags |= 2;
    }
    if (scx != EXT_LIT(float_0_80419a48, 0.0f) || scy != EXT_LIT(float_0_80419a48, 0.0f) || scz != EXT_LIT(float_0_80419a48, 0.0f)) {
        if (flags & 2) {
            PSMTXTrans(sc2, -scx, -scy, -scz);
            PSMTXTrans(sc1, scx, scy, scz);
            PSMTXTrans(sc3, stx, sty, stz);
            PSMTXConcat(sc3, sc1, tmp);
            PSMTXConcat(tmp, scale, tmp);
            PSMTXConcat(tmp, sc2, scale);
        }
        else if (stx || sty || stz) {
            PSMTXTrans(scale, stx, sty, stz);
            flags |= 2;
        }
    }
    PSMTXIdentity(rot);
    if (rz) {
        PSMTXRotRad(tmp, 'z', 0.017453292f * rz);
        PSMTXConcat(rot, tmp, rot);
        flags |= 4;
    }
    if (ry) {
        PSMTXRotRad(tmp, 'y', 0.017453292f * ry);
        PSMTXConcat(rot, tmp, rot);
        flags |= 4;
    }
    if (rx) {
        PSMTXRotRad(tmp, 'x', 0.017453292f * rx);
        PSMTXConcat(rot, tmp, rot);
        flags |= 4;
    }
    if (rcx != EXT_LIT(float_0_80419a48, 0.0f) || rcy != EXT_LIT(float_0_80419a48, 0.0f) || rcz != EXT_LIT(float_0_80419a48, 0.0f)) {
        if (flags & 4) {
            PSMTXTrans(rc2, -rcx, -rcy, -rcz);
            PSMTXTrans(rc1, rcx, rcy, rcz);
            PSMTXTrans(rc3, rtx, rty, rtz);
            PSMTXConcat(rc3, rc1, tmp);
            PSMTXConcat(tmp, rot, rot);
            PSMTXConcat(rot, rc2, rot);
        }
        else if (rtx || rty || rtz) {
            PSMTXTrans(rot, rtx, rty, rtz);
            flags |= 4;
        }
    }
    g_modeling_mtx_lv++;
    g_modeling_mtx = &g_modeling_mtx_stack[g_modeling_mtx_lv];
    switch (flags) {
        case 0:
            PSMTXIdentity(tmp);
            p = tmp;
            break;
        case 1:
            p = trans;
            break;
        case 2:
            p = scale;
            break;
        case 3:
            PSMTXConcat(trans, scale, tmp);
            p = tmp;
            break;
        case 4:
            p = rot;
            break;
        case 5:
            PSMTXConcat(trans, rot, tmp);
            p = tmp;
            break;
        case 6:
            PSMTXConcat(rot, scale, tmp);
            p = tmp;
            break;
        case 7:
            PSMTXConcat(trans, rot, tmp);
            PSMTXConcat(tmp, scale, trans);
            p = trans;
            break;
    }
    PSMTXConcat(g_modeling_mtx_stack[g_modeling_mtx_lv - 1], p, g_modeling_mtx_stack[g_modeling_mtx_lv]);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void pushGXModelMtx_TransformNode__(AnimPoseNode* node) {
	asm volatile {
		opword 0x9421FCF0
		opword 0x7C0802A6
		opword 0x90010314
		opword 0xDBE10300
		opword 0xF3E10308
		opword 0xDBC102F0
		opword 0xF3C102F8
		opword 0xDBA102E0
		opword 0xF3A102E8
		opword 0xDB8102D0
		opword 0xF38102D8
		opword 0xDB6102C0
		opword 0xF36102C8
		opword 0xDB4102B0
		opword 0xF34102B8
		opword 0xDB2102A0
		opword 0xF32102A8
		opword 0xDB010290
		opword 0xF3010298
		opword 0xDAE10280
		opword 0xF2E10288
		opword 0xDAC10270
		opword 0xF2C10278
		opword 0xDAA10260
		opword 0xF2A10268
		opword 0xDA810250
		opword 0xF2810258
		opword 0xDA610240
		opword 0xF2610248
		opword 0xDA410230
		opword 0xF2410238
		opword 0xDA210220
		opword 0xF2210228
		opword 0xDA010210
		opword 0xF2010218
		opword 0xD9E10200
		opword 0xF1E10208
		opword 0xD9C101F0
		opword 0xF1C101F8
		opword 0x93E101EC
		opword 0x93C101E8
		opword 0xC0230000
		opword 0x3BC00000
		lfs f0, float_0_80419a48(r2)
		lfs f5, float_2_80419a84(r2)
		opword 0xC0830018
		opword 0xFC010000
		opword 0xC043001C
		opword 0xC0630020
		opword 0xEFE50132
		opword 0xEFC500B2
		opword 0xC0430004
		opword 0xEFA500F2
		opword 0xC0630008
		opword 0xC1C3000C
		opword 0xC1E30010
		opword 0xC2030014
		opword 0xC3830030
		opword 0xC3630034
		opword 0xC3430038
		opword 0xC323003C
		opword 0xC3030040
		opword 0xC2E30044
		opword 0xC2C30048
		opword 0xC2A3004C
		opword 0xC2830050
		opword 0xC2630054
		opword 0xC2430058
		opword 0xC223005C
		opword 0x40820014
		opword 0xFC020000
		opword 0x4082000C
		opword 0xFC030000
		opword 0x41820010
		opword 0x386101B8
		bl PSMTXTrans
		opword 0x63DE0001
		lfs f0, float_1_80419a44(r2)
		opword 0xFC007000
		opword 0x40820014
		opword 0xFC007800
		opword 0x4082000C
		opword 0xFC008000
		opword 0x4182001C
		opword 0xFC207090
		opword 0x38610188
		opword 0xFC407890
		opword 0xFC608090
		bl PSMTXScale
		opword 0x63DE0002
		lfs f0, float_0_80419a48(r2)
		opword 0xFC00C800
		opword 0x40820014
		opword 0xFC00C000
		opword 0x4082000C
		opword 0xFC00B800
		opword 0x418200B0
		opword 0x57C007BD
		opword 0x41820074
		opword 0xFC20C850
		opword 0x386100C8
		opword 0xFC40C050
		opword 0xFC60B850
		bl PSMTXTrans
		opword 0xFC20C890
		opword 0x386100F8
		opword 0xFC40C090
		opword 0xFC60B890
		bl PSMTXTrans
		opword 0xFC209890
		opword 0x38610098
		opword 0xFC409090
		opword 0xFC608890
		bl PSMTXTrans
		opword 0x38610098
		opword 0x388100F8
		opword 0x38A10128
		bl PSMTXConcat
		opword 0x38610128
		opword 0x38810188
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x38610128
		opword 0x388100C8
		opword 0x38A10188
		bl PSMTXConcat
		opword 0x48000038
		lfs f0, float_0_80419a48(r2)
		opword 0xFC130000
		opword 0x40820014
		opword 0xFC120000
		opword 0x4082000C
		opword 0xFC110000
		opword 0x4182001C
		opword 0xFC209890
		opword 0x38610188
		opword 0xFC409090
		opword 0xFC608890
		bl PSMTXTrans
		opword 0x63DE0002
		opword 0x38610158
		bl PSMTXIdentity
		lfs f0, float_0_80419a48(r2)
		opword 0xFC1D0000
		opword 0x4182002C
		lfs f0, float_deg2rad_80419a4c(r2)
		opword 0x38610128
		opword 0x3880007A
		opword 0xEC200772
		bl PSMTXRotRad
		opword 0x38610158
		opword 0x38810128
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x63DE0004
		lfs f0, float_0_80419a48(r2)
		opword 0xFC1E0000
		opword 0x4182002C
		lfs f0, float_deg2rad_80419a4c(r2)
		opword 0x38610128
		opword 0x38800079
		opword 0xEC2007B2
		bl PSMTXRotRad
		opword 0x38610158
		opword 0x38810128
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x63DE0004
		lfs f0, float_0_80419a48(r2)
		opword 0xFC1F0000
		opword 0x4182002C
		lfs f0, float_deg2rad_80419a4c(r2)
		opword 0x38610128
		opword 0x38800078
		opword 0xEC2007F2
		bl PSMTXRotRad
		opword 0x38610158
		opword 0x38810128
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x63DE0004
		lfs f0, float_0_80419a48(r2)
		opword 0xFC00E000
		opword 0x40820014
		opword 0xFC00D800
		opword 0x4082000C
		opword 0xFC00D000
		opword 0x418200B0
		opword 0x57C0077B
		opword 0x41820074
		opword 0xFC20E050
		opword 0x38610038
		opword 0xFC40D850
		opword 0xFC60D050
		bl PSMTXTrans
		opword 0xFC20E090
		opword 0x38610068
		opword 0xFC40D890
		opword 0xFC60D090
		bl PSMTXTrans
		opword 0xFC20B090
		opword 0x38610008
		opword 0xFC40A890
		opword 0xFC60A090
		bl PSMTXTrans
		opword 0x38610008
		opword 0x38810068
		opword 0x38A10128
		bl PSMTXConcat
		opword 0x38810158
		opword 0x38610128
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38610158
		opword 0x38810038
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x48000038
		lfs f0, float_0_80419a48(r2)
		opword 0xFC160000
		opword 0x40820014
		opword 0xFC150000
		opword 0x4082000C
		opword 0xFC140000
		opword 0x4182001C
		opword 0xFC20B090
		opword 0x38610158
		opword 0xFC40A890
		opword 0xFC60A090
		bl PSMTXTrans
		opword 0x63DE0004
		lwz r4, g_modeling_mtx_lv(r13)
		lis r3, g_modeling_mtx_stack@ha
		addi r0, r3, g_modeling_mtx_stack@l
		opword 0x281E0007
		opword 0x38840001
		opword 0x1C640030
		stw r4, g_modeling_mtx_lv(r13)
		opword 0x7C001A14
		stw r0, g_modeling_mtx(r13)
		opword 0x418100B0
		lis r3, jumptable_80305118@ha
		opword 0x57C0103A
		addi r3, r3, jumptable_80305118@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x38610128
		bl PSMTXIdentity
		opword 0x3BE10128
		opword 0x48000088
		opword 0x3BE101B8
		opword 0x48000080
		opword 0x3BE10188
		opword 0x48000078
		opword 0x386101B8
		opword 0x38810188
		opword 0x38A10128
		bl PSMTXConcat
		opword 0x3BE10128
		opword 0x48000060
		opword 0x3BE10158
		opword 0x48000058
		opword 0x386101B8
		opword 0x38810158
		opword 0x38A10128
		bl PSMTXConcat
		opword 0x3BE10128
		opword 0x48000040
		opword 0x38610158
		opword 0x38810188
		opword 0x38A10128
		bl PSMTXConcat
		opword 0x3BE10128
		opword 0x48000028
		opword 0x386101B8
		opword 0x38810158
		opword 0x38A10128
		bl PSMTXConcat
		opword 0x38610128
		opword 0x38810188
		opword 0x38A101B8
		bl PSMTXConcat
		opword 0x3BE101B8
		lwz r6, g_modeling_mtx_lv(r13)
		lis r3, g_modeling_mtx_stack@ha
		addi r5, r3, g_modeling_mtx_stack@l
		opword 0x7FE4FB78
		opword 0x3806FFFF
		opword 0x1C600030
		opword 0x1C060030
		opword 0x7C651A14
		opword 0x7CA50214
		bl PSMTXConcat
		opword 0xE3E10308
		opword 0xCBE10300
		opword 0xE3C102F8
		opword 0xCBC102F0
		opword 0xE3A102E8
		opword 0xCBA102E0
		opword 0xE38102D8
		opword 0xCB8102D0
		opword 0xE36102C8
		opword 0xCB6102C0
		opword 0xE34102B8
		opword 0xCB4102B0
		opword 0xE32102A8
		opword 0xCB2102A0
		opword 0xE3010298
		opword 0xCB010290
		opword 0xE2E10288
		opword 0xCAE10280
		opword 0xE2C10278
		opword 0xCAC10270
		opword 0xE2A10268
		opword 0xCAA10260
		opword 0xE2810258
		opword 0xCA810250
		opword 0xE2610248
		opword 0xCA610240
		opword 0xE2410238
		opword 0xCA410230
		opword 0xE2210228
		opword 0xCA210220
		opword 0xE2010218
		opword 0xCA010210
		opword 0xE1E10208
		opword 0xC9E10200
		opword 0xE1C101F8
		opword 0xC9C101F0
		opword 0x83E101EC
		opword 0x80010314
		opword 0x83C101E8
		opword 0x7C0803A6
		opword 0x38210310
	}
}
#pragma pop
#endif
#ifdef NONMATCHING
void pushGXModelMtx_JointNode__(AnimPoseNode* node, f32 sx, f32 sy, f32 sz) {
    Mtx trans, scale, iscale, rot, tmp;
    MtxPtr p;
    u32 flags;
    f32 tx, ty, tz;
    f32 nsx, nsy, nsz;
    f32 r1x, r1y, r1z;
    f32 r2x, r2y, r2z;

    tx = node->mTranslation.x;
    ty = node->mTranslation.y;
    tz = node->mTranslation.z;
    nsx = node->mScale.x;
    nsy = node->mScale.y;
    nsz = node->mScale.z;
    r1x = EXT_LIT(float_2_80419a84, 2.0f) * node->mRot1.x;
    r1y = EXT_LIT(float_2_80419a84, 2.0f) * node->mRot1.y;
    r1z = EXT_LIT(float_2_80419a84, 2.0f) * node->mRot1.z;
    r2x = node->mRot2.x;
    r2y = node->mRot2.y;
    r2z = node->mRot2.z;
    flags = 0;

    if (tx || ty || tz) {
        PSMTXTrans(trans, tx, ty, tz);
        flags |= 1;
    }
    if (EXT_LIT(float_1_80419a44, 1.0f) != sx || EXT_LIT(float_1_80419a44, 1.0f) != sy || EXT_LIT(float_1_80419a44, 1.0f) == sz) {
        if (sx && sy && sz) {
            PSMTXScale(iscale, 1.0f / sx, 1.0f / sy, 1.0f / sz);
        } else {
            PSMTXScale(iscale, 1.0f, 1.0f, 1.0f);
        }
        flags |= 2;
    }
    if (EXT_LIT(float_1_80419a44, 1.0f) != nsx || EXT_LIT(float_1_80419a44, 1.0f) != nsy || EXT_LIT(float_1_80419a44, 1.0f) == nsz) {
        PSMTXScale(scale, nsx, nsy, nsz);
        flags |= 4;
    }
    PSMTXIdentity(rot);
    if (r2z) {
        PSMTXRotRad(tmp, 'z', 0.017453292f * r2z);
        PSMTXConcat(rot, tmp, rot);
        flags |= 8;
    }
    if (r2y) {
        PSMTXRotRad(tmp, 'y', 0.017453292f * r2y);
        PSMTXConcat(rot, tmp, rot);
        flags |= 8;
    }
    if (r2x) {
        PSMTXRotRad(tmp, 'x', 0.017453292f * r2x);
        PSMTXConcat(rot, tmp, rot);
        flags |= 8;
    }
    if (r1z) {
        PSMTXRotRad(tmp, 'z', 0.017453292f * r1z);
        PSMTXConcat(rot, tmp, rot);
        flags |= 8;
    }
    if (r1y) {
        PSMTXRotRad(tmp, 'y', 0.017453292f * r1y);
        PSMTXConcat(rot, tmp, rot);
        flags |= 8;
    }
    if (r1x) {
        PSMTXRotRad(tmp, 'x', 0.017453292f * r1x);
        PSMTXConcat(rot, tmp, rot);
        flags |= 8;
    }
    g_modeling_mtx_lv++;
    g_modeling_mtx = &g_modeling_mtx_stack[g_modeling_mtx_lv];
    switch (flags) {
        case 0: PSMTXIdentity(tmp); p = tmp; break;
        case 1: p = trans; break;
        case 2: p = iscale; break;
        case 3: PSMTXConcat(trans, iscale, tmp); p = tmp; break;
        case 4: p = scale; break;
        case 5: PSMTXConcat(trans, scale, tmp); p = tmp; break;
        case 6: PSMTXConcat(iscale, scale, tmp); p = tmp; break;
        case 7: PSMTXConcat(trans, iscale, tmp); PSMTXConcat(tmp, scale, trans); p = trans; break;
        case 8: p = rot; break;
        case 9: PSMTXConcat(trans, rot, tmp); p = tmp; break;
        case 10: PSMTXConcat(iscale, rot, tmp); p = tmp; break;
        case 11: PSMTXConcat(trans, iscale, tmp); PSMTXConcat(tmp, rot, trans); p = trans; break;
        case 12: PSMTXConcat(rot, scale, tmp); p = tmp; break;
        case 13: PSMTXConcat(trans, rot, tmp); PSMTXConcat(tmp, scale, trans); p = trans; break;
        case 14: PSMTXConcat(iscale, rot, tmp); PSMTXConcat(tmp, scale, trans); p = trans; break;
        case 15: PSMTXConcat(trans, iscale, tmp); PSMTXConcat(tmp, rot, trans); PSMTXConcat(trans, scale, tmp); p = tmp; break;
    }
    PSMTXConcat(g_modeling_mtx_stack[g_modeling_mtx_lv - 1], p, g_modeling_mtx_stack[g_modeling_mtx_lv]);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void pushGXModelMtx_JointNode__(AnimPoseNode* node, f32 sx, f32 sy, f32 sz) {
	asm volatile {
		opword 0x9421FE40
		opword 0x7C0802A6
		opword 0x900101C4
		opword 0xDBE101B0
		opword 0xF3E101B8
		opword 0xDBC101A0
		opword 0xF3C101A8
		opword 0xDBA10190
		opword 0xF3A10198
		opword 0xDB810180
		opword 0xF3810188
		opword 0xDB610170
		opword 0xF3610178
		opword 0xDB410160
		opword 0xF3410168
		opword 0xDB210150
		opword 0xF3210158
		opword 0xDB010140
		opword 0xF3010148
		opword 0xDAE10130
		opword 0xF2E10138
		opword 0xDAC10120
		opword 0xF2C10128
		opword 0xDAA10110
		opword 0xF2A10118
		opword 0xDA810100
		opword 0xF2810108
		opword 0x93E100FC
		opword 0x93C100F8
		opword 0xC0A30000
		opword 0xFE800890
		lfs f0, float_0_80419a48(r2)
		opword 0xFEA01090
		lfs f4, float_2_80419a84(r2)
		opword 0xFEC01890
		opword 0xC0630018
		opword 0xC043001C
		opword 0xFC050000
		opword 0xC0230020
		opword 0xEF8400F2
		opword 0xEF6400B2
		opword 0xC0430004
		opword 0xEF440072
		opword 0xC0630008
		opword 0x3BC00000
		opword 0xC3E3000C
		opword 0xC3C30010
		opword 0xC3A30014
		opword 0xC3230024
		opword 0xC3030028
		opword 0xC2E3002C
		opword 0x40820014
		opword 0xFC020000
		opword 0x4082000C
		opword 0xFC030000
		opword 0x41820014
		opword 0xFC202890
		opword 0x386100C8
		bl PSMTXTrans
		opword 0x63DE0001
		lfs f0, float_1_80419a44(r2)
		opword 0xFC00A000
		opword 0x40820014
		opword 0xFC00A800
		opword 0x4082000C
		opword 0xFC00B000
		opword 0x40820054
		lfs f0, float_0_80419a48(r2)
		opword 0xFC140000
		opword 0x41820030
		opword 0xFC150000
		opword 0x41820028
		opword 0xFC160000
		opword 0x41820020
		lfs f0, float_1_80419a44(r2)
		opword 0x38610068
		opword 0xEC20A024
		opword 0xEC40A824
		opword 0xEC60B024
		bl PSMTXScale
		opword 0x48000018
		lfs f1, float_1_80419a44(r2)
		opword 0x38610068
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x63DE0002
		lfs f0, float_1_80419a44(r2)
		opword 0xFC00F800
		opword 0x40820014
		opword 0xFC00F000
		opword 0x4082000C
		opword 0xFC00E800
		opword 0x4082001C
		opword 0xFC20F890
		opword 0x38610098
		opword 0xFC40F090
		opword 0xFC60E890
		bl PSMTXScale
		opword 0x63DE0004
		opword 0x38610038
		bl PSMTXIdentity
		lfs f0, float_0_80419a48(r2)
		opword 0xFC170000
		opword 0x4182002C
		lfs f0, float_deg2rad_80419a4c(r2)
		opword 0x38610008
		opword 0x3880007A
		opword 0xEC2005F2
		bl PSMTXRotRad
		opword 0x38610038
		opword 0x38810008
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x63DE0008
		lfs f0, float_0_80419a48(r2)
		opword 0xFC180000
		opword 0x4182002C
		lfs f0, float_deg2rad_80419a4c(r2)
		opword 0x38610008
		opword 0x38800079
		opword 0xEC200632
		bl PSMTXRotRad
		opword 0x38610038
		opword 0x38810008
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x63DE0008
		lfs f0, float_0_80419a48(r2)
		opword 0xFC190000
		opword 0x4182002C
		lfs f0, float_deg2rad_80419a4c(r2)
		opword 0x38610008
		opword 0x38800078
		opword 0xEC200672
		bl PSMTXRotRad
		opword 0x38610038
		opword 0x38810008
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x63DE0008
		lfs f0, float_0_80419a48(r2)
		opword 0xFC1A0000
		opword 0x4182002C
		lfs f0, float_deg2rad_80419a4c(r2)
		opword 0x38610008
		opword 0x3880007A
		opword 0xEC2006B2
		bl PSMTXRotRad
		opword 0x38610038
		opword 0x38810008
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x63DE0008
		lfs f0, float_0_80419a48(r2)
		opword 0xFC1B0000
		opword 0x4182002C
		lfs f0, float_deg2rad_80419a4c(r2)
		opword 0x38610008
		opword 0x38800079
		opword 0xEC2006F2
		bl PSMTXRotRad
		opword 0x38610038
		opword 0x38810008
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x63DE0008
		lfs f0, float_0_80419a48(r2)
		opword 0xFC1C0000
		opword 0x4182002C
		lfs f0, float_deg2rad_80419a4c(r2)
		opword 0x38610008
		opword 0x38800078
		opword 0xEC200732
		bl PSMTXRotRad
		opword 0x38610038
		opword 0x38810008
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x63DE0008
		lwz r4, g_modeling_mtx_lv(r13)
		lis r3, g_modeling_mtx_stack@ha
		addi r0, r3, g_modeling_mtx_stack@l
		opword 0x281E000F
		opword 0x38840001
		opword 0x1C640030
		stw r4, g_modeling_mtx_lv(r13)
		opword 0x7C001A14
		stw r0, g_modeling_mtx(r13)
		opword 0x418101B0
		lis r3, jumptable_803050D8@ha
		opword 0x57C0103A
		addi r3, r3, jumptable_803050D8@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x38610008
		bl PSMTXIdentity
		opword 0x3BE10008
		opword 0x48000188
		opword 0x3BE100C8
		opword 0x48000180
		opword 0x3BE10068
		opword 0x48000178
		opword 0x386100C8
		opword 0x38810068
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x3BE10008
		opword 0x48000160
		opword 0x3BE10098
		opword 0x48000158
		opword 0x386100C8
		opword 0x38810098
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x3BE10008
		opword 0x48000140
		opword 0x38610068
		opword 0x38810098
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x3BE10008
		opword 0x48000128
		opword 0x386100C8
		opword 0x38810068
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x38610008
		opword 0x38810098
		opword 0x38A100C8
		bl PSMTXConcat
		opword 0x3BE100C8
		opword 0x48000100
		opword 0x3BE10038
		opword 0x480000F8
		opword 0x386100C8
		opword 0x38810038
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x3BE10008
		opword 0x480000E0
		opword 0x38610068
		opword 0x38810038
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x3BE10008
		opword 0x480000C8
		opword 0x386100C8
		opword 0x38810068
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x38610008
		opword 0x38810038
		opword 0x38A100C8
		bl PSMTXConcat
		opword 0x3BE100C8
		opword 0x480000A0
		opword 0x38610038
		opword 0x38810098
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x3BE10008
		opword 0x48000088
		opword 0x386100C8
		opword 0x38810038
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x38610008
		opword 0x38810098
		opword 0x38A100C8
		bl PSMTXConcat
		opword 0x3BE100C8
		opword 0x48000060
		opword 0x38610068
		opword 0x38810038
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x38610008
		opword 0x38810098
		opword 0x38A100C8
		bl PSMTXConcat
		opword 0x3BE100C8
		opword 0x48000038
		opword 0x386100C8
		opword 0x38810068
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x38610008
		opword 0x38810038
		opword 0x38A100C8
		bl PSMTXConcat
		opword 0x386100C8
		opword 0x38810098
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x3BE10008
		lwz r6, g_modeling_mtx_lv(r13)
		lis r3, g_modeling_mtx_stack@ha
		addi r5, r3, g_modeling_mtx_stack@l
		opword 0x7FE4FB78
		opword 0x3806FFFF
		opword 0x1C600030
		opword 0x1C060030
		opword 0x7C651A14
		opword 0x7CA50214
		bl PSMTXConcat
		opword 0xE3E101B8
		opword 0xCBE101B0
		opword 0xE3C101A8
		opword 0xCBC101A0
		opword 0xE3A10198
		opword 0xCBA10190
		opword 0xE3810188
		opword 0xCB810180
		opword 0xE3610178
		opword 0xCB610170
		opword 0xE3410168
		opword 0xCB410160
		opword 0xE3210158
		opword 0xCB210150
		opword 0xE3010148
		opword 0xCB010140
		opword 0xE2E10138
		opword 0xCAE10130
		opword 0xE2C10128
		opword 0xCAC10120
		opword 0xE2A10118
		opword 0xCAA10110
		opword 0xE2810108
		opword 0xCA810100
		opword 0x83E100FC
		opword 0x800101C4
		opword 0x83C100F8
		opword 0x7C0803A6
		opword 0x382101C0
	}
}
#pragma pop
#endif

#include "sdk/texPalette.h"

void animSetMaterial_Texture(s32 texCount, s32 *texIdRemap, AnimPoseTexEntry *pTexEntries, AnimTexMtx *animEntries, s32 texBindsCapacity, AnimTexBind *texBinds, AnimationTextureFile *texFile);
__declspec(section ".data") static void* jumptable_803050B8[] = {
    (char*)animSetMaterial_Texture + 0x47C,
    (char*)animSetMaterial_Texture + 0x49C,
    (char*)animSetMaterial_Texture + 0x4A4,
    (char*)animSetMaterial_Texture + 0x4AC,
    (char*)animSetMaterial_Texture + 0x4C4,
    (char*)animSetMaterial_Texture + 0x4CC,
    (char*)animSetMaterial_Texture + 0x4E4,
    (char*)animSetMaterial_Texture + 0x4FC,
};
__declspec(section ".data") void* jumptable_803050D8[] = {
    (char*)pushGXModelMtx_JointNode__ + 0x310,
    (char*)pushGXModelMtx_JointNode__ + 0x320,
    (char*)pushGXModelMtx_JointNode__ + 0x328,
    (char*)pushGXModelMtx_JointNode__ + 0x330,
    (char*)pushGXModelMtx_JointNode__ + 0x348,
    (char*)pushGXModelMtx_JointNode__ + 0x350,
    (char*)pushGXModelMtx_JointNode__ + 0x368,
    (char*)pushGXModelMtx_JointNode__ + 0x380,
    (char*)pushGXModelMtx_JointNode__ + 0x3A8,
    (char*)pushGXModelMtx_JointNode__ + 0x3B0,
    (char*)pushGXModelMtx_JointNode__ + 0x3C8,
    (char*)pushGXModelMtx_JointNode__ + 0x3E0,
    (char*)pushGXModelMtx_JointNode__ + 0x408,
    (char*)pushGXModelMtx_JointNode__ + 0x420,
    (char*)pushGXModelMtx_JointNode__ + 0x448,
    (char*)pushGXModelMtx_JointNode__ + 0x470,
};
__declspec(section ".data") void* jumptable_80305118[] = {
    (char*)pushGXModelMtx_TransformNode__ + 0x3DC,
    (char*)pushGXModelMtx_TransformNode__ + 0x3EC,
    (char*)pushGXModelMtx_TransformNode__ + 0x3F4,
    (char*)pushGXModelMtx_TransformNode__ + 0x3FC,
    (char*)pushGXModelMtx_TransformNode__ + 0x414,
    (char*)pushGXModelMtx_TransformNode__ + 0x41C,
    (char*)pushGXModelMtx_TransformNode__ + 0x434,
    (char*)pushGXModelMtx_TransformNode__ + 0x44C,
};
__declspec(section ".sdata") u32 g5_tbl_s1109[4] = {0x00000002, 0x00000001, 0x00000003, 0x00000000};
#ifdef NONMATCHING
void animSetMaterial_Texture(s32 texCount, s32 *texIdRemap, AnimPoseTexEntry *pTexEntries, AnimTexMtx *animEntries, s32 texBindsCapacity, AnimTexBind *texBinds, AnimationTextureFile *texFile)
{
  int i;
  s32 wrapFlags;
  s32 bindId;
  u32 texId;
  AnimPoseTexEntry *entry;
  TEXDescriptor *desc;
  TEXHeader *hdr;
  s32 wrapS;
  s32 wrapT;
  u32 mipmap;
  GXTlutObj tlut;
  GXTexObj obj;
  Mtx rot;
  Mtx trans;
  Mtx scale;
  Mtx tmp;
  MtxPtr m;
  AnimTexMtx *anim;
  f32 scaleS;
  f32 scaleT;
  f32 transS;
  f32 transT;
  f32 rotate;
  u32 flags;
  s32 texMtx;
  u32 j;
  for (i = 0; i < texCount; i++)
  {
    s32 id = texIdRemap[(u32) ((texCount - i) - 1)];
    entry = &pTexEntries[id];
    bindId = entry->bindId + animEntries[id].mTexBindIdx;
    if ((bindId < 0) || (bindId >= texBindsCapacity))
    {
      bindId = 0;
            printf("Error: dispSetTevMode: \203x\201[\203X\203\202\203f\203\213%s \203A\203j\203\201 %s \223\340\202\305 \203t\203\214\201[\203\200\203G\203N\203X\203e\203\223\203V\203\207\203\223\202\314\220\335\222\350\202\252\215s\202\355\202\352\202\304\202\242\202\334\202\267\202\252\201A\212Y\223\226\202\267\202\351\203e\203N\203X\203`\203\203\202\252\202\240\202\350\202\334\202\271\202\361 \nframeExt\224\324\215\206 %d? \202\252\226\263\202\242\202\346\202\244\202\305\202\267\201B\203\202\203f\203\213\202\334\202\275\202\315\203A\203j\203\201\202\311\217C\220\263\202\252\225K\227v\202\305\202\267\201BtextureIdx=%d\n",
                   animPoseGetBaseData(wp->mpCurPose)->fileName,
                   animPoseGetBaseData(wp->mpCurPose)->mpAnims[wp->mpCurPose->animId].name);
    }
    wrapFlags = entry->wrapFlags;
    texId = *((u32 *) (((u8 *) (&texBinds[bindId])) + 4));
    if ((*((s32 *) (((u8 *) (&texBinds[bindId])) + 8))) != 0)
    {
      continue;
    }
    if (TEXGet(*((TEXPalette **) texFile->handle->data), texId)->CLUTHeader)
    {
      desc = TEXGet(*((TEXPalette **) texFile->handle->data), texId);
      hdr = desc->textureHeader;
      wrapS = hdr->wrapS;
      wrapT = hdr->wrapT;
      if (wrapFlags >= 0)
      {
        if (wrapFlags & 4)
        {
          wrapS = GX_MIRROR;
        }
        else
        {
          wrapS = wrapFlags;
          wrapS = wrapS & 1;
        }
        if (wrapFlags & 8)
        {
          wrapT = GX_MIRROR;
        }
        else
        {
          wrapT = (wrapFlags >> 1) & 1;
        }
      }
      mipmap = hdr->minLOD != hdr->maxLOD;
      GXInitTlutObj(&tlut, desc->CLUTHeader->data, desc->CLUTHeader->format, desc->CLUTHeader->numEntries);
      GXInitTexObjCI(&obj, desc->textureHeader->data, desc->textureHeader->width, desc->textureHeader->height, (GXCITexFmt) desc->textureHeader->format, wrapS, wrapT, mipmap, 0);
      hdr = desc->textureHeader;
      GXInitTexObjLOD(&obj, hdr->minFilter, hdr->magFilter, hdr->minLOD, hdr->maxLOD, hdr->LODBias, (GXBool) 0, hdr->edgeLODEnable, GX_ANISO_1);
      GXLoadTlut(&tlut, 0);
      GXLoadTexObj(&obj, (GXTexMapID) i);
    }
    else
    {
      desc = TEXGet(*((TEXPalette **) texFile->handle->data), texId);
      hdr = desc->textureHeader;
      wrapS = hdr->wrapS;
      wrapT = hdr->wrapT;
      if (wrapFlags >= 0)
      {
        if (wrapFlags & 4)
        {
          wrapS = GX_MIRROR;
        }
        else
        {
          wrapS = wrapFlags;
          wrapS = wrapS & 1;
        }
        if (wrapFlags & 8)
        {
          wrapT = GX_MIRROR;
        }
        else
        {
          wrapT = (wrapFlags >> 1) & 1;
        }
      }
      GXInitTexObj(&obj, hdr->data, hdr->width, hdr->height, (GXTexFmt) hdr->format, wrapS, wrapT, hdr->minLOD != hdr->maxLOD);
      hdr = desc->textureHeader;
      GXInitTexObjLOD(&obj, hdr->minFilter, hdr->magFilter, hdr->minLOD, hdr->maxLOD, hdr->LODBias, (GXBool) 0, hdr->edgeLODEnable, GX_ANISO_1);
      GXLoadTexObj(&obj, (GXTexMapID) i);
    }
  }

  for (i = 0; i < texCount; i++)
  {
    flags = 0;
    anim = &animEntries[texIdRemap[(u32) ((texCount - i) - 1)]];
    rotate = anim->mRotate;
    scaleS = anim->mScaleS;
    scaleT = anim->mScaleT;
    transS = anim->mTransS;
    transT = anim->mTransT;
    if (rotate != EXT_LIT(float_0_80419a48, 0.0f))
    {
      flags |= 1;
      PSMTXTrans(tmp, EXT_LIT(float_0p5_80419a64, 0.5f), EXT_LIT(float_0p5_80419a64, 0.5f), EXT_LIT(float_0_80419a48, 0.0f));
      PSMTXRotRad(rot, 'z', EXT_LIT(float_deg2rad_80419a4c, 0.017453292f) * (-rotate));
      PSMTXConcat(tmp, rot, trans);
      PSMTXTrans(tmp, EXT_LIT(float_neg0p5_80419a88, -0.5f), EXT_LIT(float_neg0p5_80419a88, -0.5f), EXT_LIT(float_0_80419a48, 0.0f));
      PSMTXConcat(trans, tmp, rot);
    }
    if (((transS != EXT_LIT(float_0_80419a48, 0.0f)) || (transT != EXT_LIT(float_0_80419a48, 0.0f))) || (scaleT != EXT_LIT(float_0_80419a48, 0.0f)))
    {
      flags |= 2;
      PSMTXTrans(trans, transS, (EXT_LIT(float_1_80419a44, 1.0f) - transT) - scaleT, EXT_LIT(float_0_80419a48, 0.0f));
    }
    if ((scaleS != EXT_LIT(float_1_80419a44, 1.0f)) || (scaleT != EXT_LIT(float_1_80419a44, 1.0f)))
    {
      flags |= 4;
      PSMTXScale(scale, scaleS, scaleT, EXT_LIT(float_1_80419a44, 1.0f));
    }
    switch (flags)
    {
      case 0:
        GXSetTexCoordGen2((GXTexCoordID) i, GX_TG_MTX2x4, (GXTexGenSrc) (GX_TG_TEX0 + i), GX_IDENTITY, (GXBool) 0, GX_PTIDENTITY);
        continue;

      case 1:
        m = rot;
        break;

      case 2:
        m = trans;
        break;

      case 3:
        PSMTXConcat(rot, trans, tmp);
        m = tmp;
        break;

      case 4:
        m = scale;
        break;

      case 5:
        PSMTXConcat(rot, scale, tmp);
        m = tmp;
        break;

      case 6:
        PSMTXConcat(trans, scale, tmp);
        m = tmp;
        break;

      case 7:
        PSMTXConcat(rot, trans, tmp);
        PSMTXConcat(tmp, scale, trans);
        m = trans;
        break;

    }

    j = i * 3;
    texMtx = GX_TEXMTX0 + j;
    GXSetTexCoordGen2((GXTexCoordID) i, GX_TG_MTX2x4, (GXTexGenSrc) (GX_TG_TEX0 + i), texMtx, (GXBool) 0, GX_PTIDENTITY);
    GXLoadTexMtxImm(m, texMtx, GX_MTX2x4);
  }

}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void animSetMaterial_Texture(s32 texCount, s32 *texIdRemap, AnimPoseTexEntry *pTexEntries, AnimTexMtx *animEntries, s32 texBindsCapacity, AnimTexBind *texBinds, AnimationTextureFile *texFile) {
	char _af_pad[268];
	asm volatile {
		opword 0x7C781B78
		opword 0x7C992378
		opword 0x7CBA2B78
		opword 0x7CDB3378
		opword 0x7CFC3B78
		opword 0x7D1D4378
		opword 0x7D3E4B78
		opword 0x3AE00000
		opword 0x480002DC
		opword 0x7C77C050
		opword 0x3803FFFF
		opword 0x5400103A
		opword 0x7C79002E
		opword 0x1C030018
		opword 0x54631838
		add r19, r26, r3
		opword 0x80F30000
		opword 0x7CDB00AE
		opword 0x7E873215
		opword 0x4180000C
		opword 0x7C14E000
		opword 0x41800050
		lwz r4, wp(r13)
		lis r3, str_802C2E44@ha
		addi r3, r3, str_802C2E44@l
		opword 0x3A800000
		opword 0x81040018
		opword 0x80A40000
		opword 0x80880010
		opword 0x80080014
		opword 0x54842036
		opword 0x38840008
		opword 0x54003032
		opword 0x7C85202E
		opword 0x808400A0
		opword 0x80840000
		opword 0x80A401AC
		opword 0x38840004
		opword 0x7CA50214
		opword 0x4CC63182
		bl printf
		opword 0x56803032
		opword 0x82D30004
		opword 0x7C7D0214
		opword 0x80030008
		opword 0x80830004
		opword 0x2C000000
		opword 0x4082023C
		opword 0x807E0008
		opword 0x7C932378
		opword 0x806300A0
		opword 0x80630000
		bl TEXGet
		opword 0x80030004
		opword 0x28000000
		opword 0x41820130
		opword 0x807E0008
		opword 0x7E649B78
		opword 0x806300A0
		opword 0x80630000
		bl TEXGet
		opword 0x7C751B78
		opword 0x2C160000
		opword 0x80830000
		opword 0x8264000C
		opword 0x82840010
		opword 0x4180002C
		opword 0x56C0077B
		opword 0x4182000C
		opword 0x3A600002
		opword 0x48000008
		opword 0x56D307FE
		opword 0x56C00739
		opword 0x4182000C
		opword 0x3A800002
		opword 0x48000008
		opword 0x56D4FFFE
		opword 0x88C40021
		la r3, _af_pad+8
		opword 0x80F50004
		opword 0x88040022
		opword 0x80870008
		opword 0x7CA60050
		opword 0x7C003050
		opword 0x7CA00378
		opword 0x80A70004
		opword 0xA0C70000
		opword 0x54160FFE
		bl GXInitTlutObj
		opword 0x80F50000
		opword 0x38000000
		opword 0x7E689B78
		opword 0x7E89A378
		opword 0x90010008
		opword 0x7ECAB378
		opword 0x3861001C
		opword 0x80870008
		opword 0xA0A70002
		opword 0xA0C70000
		opword 0x80E70004
		bl GXInitTexObjCI
		opword 0x80F50000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802c2de0@ha
		opword 0x90A10100
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802c2de0@l
		opword 0x88070022
		opword 0x3861001C
		opword 0x90C10104
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC8010100
		opword 0x9001010C
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A10108
		opword 0x80A70018
		opword 0xC8010108
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x38610010
		opword 0x38800000
		bl GXLoadTlut
		opword 0x7EE4BB78
		opword 0x3861001C
		bl GXLoadTexObj
		opword 0x480000F0
		opword 0x807E0008
		opword 0x7E649B78
		opword 0x806300A0
		opword 0x80630000
		bl TEXGet
		opword 0x7C751B78
		opword 0x2C160000
		opword 0x80E30000
		opword 0x8107000C
		opword 0x81270010
		opword 0x4180002C
		opword 0x56C0077B
		opword 0x4182000C
		opword 0x39000002
		opword 0x48000008
		opword 0x56C807FE
		opword 0x56C00739
		opword 0x4182000C
		opword 0x39200002
		opword 0x48000008
		opword 0x56C9FFFE
		opword 0x88C70021
		opword 0x3861001C
		opword 0x88070022
		opword 0x80870008
		opword 0x7CA60050
		opword 0x7C003050
		opword 0x7CA00378
		opword 0xA0A70002
		opword 0xA0C70000
		opword 0x540A0FFE
		opword 0x80E70004
		bl GXInitTexObj
		opword 0x80F50000
		opword 0x3CA04330
		lis r3, double_to_int_mask_802c2de0@ha
		opword 0x90A10108
		opword 0x88C70021
		addi r4, r3, double_to_int_mask_802c2de0@l
		opword 0x88070022
		opword 0x3861001C
		opword 0x90C1010C
		opword 0x38C00000
		opword 0xC8440000
		opword 0x39000000
		opword 0xC8010108
		opword 0x90010104
		opword 0xEC201028
		opword 0x80870014
		opword 0x90A10100
		opword 0x80A70018
		opword 0xC8010100
		opword 0xC067001C
		opword 0xEC401028
		opword 0x88E70020
		bl GXInitTexObjLOD
		opword 0x7EE4BB78
		opword 0x3861001C
		bl GXLoadTexObj
		opword 0x3AF70001
		opword 0x7C17C000
		opword 0x4180FD24
		opword 0x3AA00000
		lfs f30, float_0_80419a48(r2)
		lfs f31, float_1_80419a44(r2)
		opword 0x7EB3AB78
		opword 0x480001FC
		opword 0x7C75C050
		opword 0x3A800000
		opword 0x3803FFFF
		opword 0x5400103A
		opword 0x7C19002E
		opword 0x1C000018
		opword 0x7C7B0214
		lfs f25, 0x14(r3)
		opword 0xC3A3000C
		opword 0xFC1EC800
		opword 0xC3830010
		opword 0xC3630004
		opword 0xC3430008
		opword 0x41820068
		lfs f1, float_0p5_80419a64(r2)
		opword 0xFC60F090
		opword 0x62940001
		opword 0x3861003C
		opword 0xFC400890
		bl PSMTXTrans
		opword 0xFC00C850
		lfs f1, float_deg2rad_80419a4c(r2)
		opword 0x386100CC
		opword 0x3880007A
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x3861003C
		opword 0x388100CC
		opword 0x38A1009C
		bl PSMTXConcat
		lfs f1, float_neg0p5_80419a88(r2)
		opword 0x3861003C
		lfs f3, float_0_80419a48(r2)
		opword 0xFC400890
		bl PSMTXTrans
		opword 0x3861009C
		opword 0x3881003C
		opword 0x38A100CC
		bl PSMTXConcat
		opword 0xFC1ED800
		opword 0x40820014
		opword 0xFC1ED000
		opword 0x4082000C
		opword 0xFC1EE000
		opword 0x41820024
		lfs f0, float_1_80419a44(r2)
		opword 0xFC20D890
		lfs f3, float_0_80419a48(r2)
		opword 0x62940002
		opword 0xEC00D028
		opword 0x3861009C
		opword 0xEC40E028
		bl PSMTXTrans
		opword 0xFC1FE800
		opword 0x4082000C
		opword 0xFC1FE000
		opword 0x4182001C
		opword 0xFC20E890
		lfs f3, float_1_80419a44(r2)
		opword 0xFC40E090
		opword 0x62940004
		opword 0x3861006C
		bl PSMTXScale
		opword 0x28140007
		opword 0x418100C0
		lis r3, jumptable_803050B8@ha
		opword 0x5680103A
		addi r3, r3, jumptable_803050B8@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x7EA3AB78
		opword 0x38B50004
		opword 0x38800001
		opword 0x38C0003C
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x480000B8
		opword 0x3BE100CC
		opword 0x48000080
		opword 0x3BE1009C
		opword 0x48000078
		opword 0x386100CC
		opword 0x3881009C
		opword 0x38A1003C
		bl PSMTXConcat
		opword 0x3BE1003C
		opword 0x48000060
		opword 0x3BE1006C
		opword 0x48000058
		opword 0x386100CC
		opword 0x3881006C
		opword 0x38A1003C
		bl PSMTXConcat
		opword 0x3BE1003C
		opword 0x48000040
		opword 0x3861009C
		opword 0x3881006C
		opword 0x38A1003C
		bl PSMTXConcat
		opword 0x3BE1003C
		opword 0x48000028
		opword 0x386100CC
		opword 0x3881009C
		opword 0x38A1003C
		bl PSMTXConcat
		opword 0x3861003C
		opword 0x3881006C
		opword 0x38A1009C
		bl PSMTXConcat
		opword 0x3BE1009C
		opword 0x3A93001E
		opword 0x7EA3AB78
		opword 0x7E86A378
		opword 0x38B50004
		opword 0x38800001
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7FE3FB78
		opword 0x7E84A378
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x3AB50001
		opword 0x3A730003
		opword 0x7C15C000
		opword 0x4180FE04
	}
}
#pragma pop
#endif

inline BOOL animSetMaterial_ChangeTexture(AnimationPoseData* data, AnimPoseShapeDraw* draw, AnimationPose* pose, GXTexObj* texObj, void** texData, Mtx mtx, s32 texType) {
    AnimTexBind* bind;
    s32 bindCount;
    AnimTexMtx* texAnim;
    AnimPoseTexEntry* texEntry;
    s32 texCount;
    s32 dataId, bindId, frameExt;
    GXTexObj* smartObj;
    int i;

    bind = data->texBinds;
    bindCount = data->texBindCount;
    texAnim = pose->mpTexAnimEntries;
    texEntry = data->texData;
    texCount = draw->texCount;

    for (i = 0; i < texCount; i++) {
        dataId = texCount - i - 1;
        dataId = draw->texDataIds[dataId];
        frameExt = texAnim[dataId].mTexBindIdx;
        bindId = texEntry[dataId].bindId + frameExt;
        if (bindId < 0 || bindId >= bindCount) {
            bindId = 0;
            //"Error: animSetMaterial_ChangeTexture: テクスチャがありません frameExt=%d\n"
            printf("Error: animSetMaterial_ChangeTexture: "
                   "\x83\x65\x83\x4E\x83\x58\x83\x60\x83\x83\x82\xAA\x82\xA0\x82\xE8\x82\xDC\x82\xB9\x82\xF1 "
                   "frameExt=%d\n",
                   frameExt);
        }
        if (bind[bindId].texType == texType) {
            if (texObj) {
                smartObj = smartTexObj(texObj, texData);
                GXLoadTexObj(smartObj, i);
                if (mtx) {
                    GXLoadTexMtxImm(mtx, GX_TEXMTX0 + (u32)(i * 3), GX_MTX2x4);
                    GXSetTexCoordGen(i, GX_TG_MTX2x4, GX_TG_TEX0 + i, GX_TEXMTX0 + (u32)(i * 3));
                } else {
                    GXSetTexCoordGen(i, GX_TG_MTX2x4, GX_TG_TEX0 + i, GX_IDENTITY);
                }
            }
            return TRUE;
        }
    }
    return FALSE;
}

#ifdef NONMATCHING
static s32 tbl[4] = { 2, 1, 3, 0 };  // target g5_tbl_s1109 (g5_tbl_s1109 in the stopgap)
#else
#define tbl g5_tbl_s1109
#endif

#ifdef NONMATCHING
void materialProc(s32 shapeId, s32 xluStage)
{
  int i;
  s32 drawCount;
  AnimPoseShapeDraw *draw;
  CameraEntry *camera;
  AnimationPose *pose;
  GXTexObj *texObj;
  GXTexObj *currTexObj;
  BOOL texChange1;
  BOOL check1;
  s32 dispMode;
  AnimPoseShape *shape;
  Mtx camMtx;
  Mtx invCamMtx;
  Vec lightPos;
  if (shapeId != (-1))
  {
    camera = camGetCurPtr();
    PSMTXConcat(camera->view, *g_modeling_mtx, camMtx);
    GXLoadPosMtxImm(camMtx, 0);
    PSMTXInvXpose(camMtx, invCamMtx);
    GXLoadNrmMtxImm(invCamMtx, 0);
    GXSetCurrentMtx(0);
    shape = &wp->mpCurPoseData->shapes[shapeId];
    dispMode = shape->dispMode;
    drawCount = shape->shapeDrawCount;
    draw = &wp->mpCurPoseData->draws[shape->shapeDrawStart];
    if ((dispMode == 0 && wp->currDispMode == 2) || dispMode == wp->currDispMode || wp->mpCurPose->materialColor.a != 0xFF || wp->mpCurPose->materialColor2.a != 0xFF)
    {
      GXSetCullMode(tbl[shape->cullMode]);
      for (i = 0; i < drawCount; i++, draw++)
      {
        s32 texCount = draw->texCount;
        if ((u32)wp->mpCurPose->disableDraw == 0)
        {
          lightPos = (Vec){0.0f, 0.0f, 0.0f};
          PSMTXMultVec(*g_modeling_mtx, &lightPos, &lightPos);
          mapSetMaterialLight(wp->mpCurPose->materialLightFlag, lightPos);
          animSetMaterial_Texture(draw->texCount, draw->texDataIds, wp->mpCurPoseData->texData, wp->mpCurPose->mpTexAnimEntries, wp->mpCurPoseData->texBindCount, wp->mpCurPoseData->texBinds, &wp->textures[wp->files[wp->mpCurPose->fileId].textureId]);
          mapSetMaterialLastStageBlend(wp->mpCurPose->materialFlag, wp->mpCurPose->materialColor, wp->mpCurPose->materialColor2);
          camera = camGetPtr(CAMERA_3D);
          if (camGetCurPtr() == camera)
          {
            mapSetMaterialFog();
          }
          mapSetMaterialTev(texCount, draw->drawMode, wp->mpCurPose->materialFlag, *g_modeling_mtx);
        }
        pose = wp->mpCurPose;
        if ((u32)pose->typeFlags != 0)
        {
          texChange1 = animSetMaterial_ChangeTexture(wp->mpCurPoseData, draw, pose, wp->mpTexObjs[0], wp->mpTexDatas[0], *wp->paperMtxPtr[0], 1);
          check1 = texChange1;
          if (!texChange1)
          {
            check1 = animSetMaterial_ChangeTexture(wp->mpCurPoseData, draw, wp->mpCurPose, wp->mpTexObjs[1], wp->mpTexDatas[1], *wp->paperMtxPtr[1], 2);
          }
          if (check1 && (!draw->drawMode))
          {
            currTexObj = wp->mpCurTexObj;
            if (currTexObj)
            {
              smartTexObj(currTexObj, wp->mpCurTexData);
              if (wp->currDispMode != 3)
              {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
                GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                GXSetZCompLoc(GX_FALSE);
                GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
              }
              texObj = wp->mpTexObjs[texChange1 == 0];
              if (texObj)
              {
                GXLoadTexObj(texObj, GX_TEXMAP0);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                GXLoadTexMtxImm(*wp->paperMtxPtr[!texChange1], GX_TEXMTX0, GX_MTX2x4);
              }
              GXLoadTexObj(currTexObj, GX_TEXMAP1);
              GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
              GXLoadTexMtxImm(*wp->paperMtxPtr[2], GX_TEXMTX1, GX_MTX2x4);
              mapSetMaterialTev(2, 12, wp->mpCurPose->materialFlag, *g_modeling_mtx);
            }
          }
        }
        pose = wp->mpCurPose;
        if (pose->flags & 0x10)
        {
          texObj = wp->mpTexObjs[0];
          if (texObj)
          {
            if (wp->paperMtxPtr[0])
            {
              animSetMaterial_ChangeTexture(wp->mpCurPoseData, draw, pose, texObj, wp->mpTexDatas[0], *wp->paperMtxPtr[0], 1);
            }
          }
        }
      }

    }
  }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void materialProc(s32 shapeId, s32 xluStage) {
	asm volatile {
		opword 0x9421FF40
		opword 0x7C0802A6
		opword 0x900100C4
		opword 0xBE410088
		opword 0x7C721B78
		opword 0x2C12FFFF
		opword 0x418206C4
		bl camGetCurPtr
		lwz r4, g_modeling_mtx(r13)
		opword 0x38A10058
		opword 0x3863011C
		bl PSMTXConcat
		opword 0x38610058
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x38610058
		opword 0x38810028
		bl PSMTXInvXpose
		opword 0x38610028
		opword 0x38800000
		bl GXLoadNrmMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		lwz r5, wp(r13)
		opword 0x1C1200A8
		opword 0x80650020
		opword 0x8083014C
		opword 0x8063019C
		opword 0x7CC40214
		opword 0x80060098
		opword 0x808600A0
		opword 0x1C00006C
		opword 0x83C6009C
		opword 0x2C040000
		opword 0x7FA30214
		opword 0x40820010
		opword 0x800500E0
		opword 0x2C000002
		opword 0x4182002C
		opword 0x800500E0
		opword 0x7C040000
		opword 0x41820020
		opword 0x80650018
		opword 0x880300F3
		opword 0x280000FF
		opword 0x40820010
		opword 0x880300F7
		opword 0x280000FF
		opword 0x4182061C
		opword 0x800600A4
		la r3, g5_tbl_s1109(r13)
		opword 0x5400103A
		opword 0x7C63002E
		bl GXSetCullMode
		opword 0x3BE00000
		opword 0x480005F8
		lwz r3, wp(r13)
		opword 0x827D0000
		opword 0x80630018
		opword 0x800300E4
		opword 0x28000000
		opword 0x40820110
		lis r3, vec3_802c2db0@ha
		opword 0x3881001C
		addi r8, r3, vec3_802c2db0@l
		lwz r3, g_modeling_mtx(r13)
		opword 0x80E80000
		opword 0x7C852378
		opword 0x80C80004
		opword 0x80080008
		opword 0x90E1001C
		opword 0x90C10020
		opword 0x90010024
		bl PSMTXMultVec
		opword 0x8061001C
		opword 0x38810010
		opword 0x80A10020
		opword 0x80010024
		opword 0x90610010
		lwz r3, wp(r13)
		opword 0x90A10014
		opword 0x90010018
		opword 0x80630018
		opword 0x806300EC
		bl mapSetMaterialLight
		lwz r7, wp(r13)
		opword 0x389D0010
		opword 0x807D0000
		opword 0x81470018
		opword 0x81070020
		opword 0x800A0010
		opword 0x80C70000
		opword 0x54052036
		opword 0x81270008
		opword 0x3805000C
		opword 0x80A80194
		opword 0x7C06002E
		opword 0x80CA006C
		opword 0x1C00000C
		opword 0x80E80134
		opword 0x81080198
		opword 0x7D290214
		bl animSetMaterial_Texture
		lwz r6, wp(r13)
		opword 0x3881000C
		opword 0x38A10008
		opword 0x80660018
		opword 0x800300F4
		opword 0x90010008
		opword 0x80660018
		opword 0x800300F0
		opword 0x9001000C
		opword 0x80660018
		opword 0x806300E8
		bl mapSetMaterialLastStageBlend
		opword 0x38600004
		bl camGetPtr
		opword 0x7C741B78
		bl camGetCurPtr
		opword 0x7C03A040
		opword 0x40820008
		bl mapSetMaterialFog
		lwz r5, wp(r13)
		opword 0x7E639B78
		opword 0x809D0008
		opword 0x80A50018
		lwz r6, g_modeling_mtx(r13)
		opword 0x80A500E8
		bl mapSetMaterialTev
		lwz r3, wp(r13)
		opword 0x80A30018
		opword 0x80050004
		opword 0x28000000
		opword 0x41820384
		opword 0x80830020
		opword 0x3B800000
		opword 0x828300CC
		opword 0x82A30024
		opword 0x82C30030
		opword 0x82E40198
		opword 0x83040134
		opword 0x8325006C
		opword 0x83440194
		opword 0x837D0000
		opword 0x480000E4
		opword 0x7C7CD850
		opword 0x3803FFFF
		opword 0x5403103A
		opword 0x38030010
		opword 0x7C1D002E
		opword 0x1C600018
		opword 0x54001838
		opword 0x7C1A002E
		opword 0x7C9918AE
		opword 0x7E602215
		opword 0x4180000C
		opword 0x7C13C000
		opword 0x41800018
		lis r3, str_802C2DF8@ha
		opword 0x3A600000
		addi r3, r3, str_802C2DF8@l
		opword 0x4CC63182
		bl printf
		opword 0x56633032
		opword 0x38030008
		opword 0x7C17002E
		opword 0x2C000001
		opword 0x40820084
		opword 0x28160000
		opword 0x41820074
		opword 0x7EC3B378
		opword 0x7EA4AB78
		bl smartTexObj
		opword 0x7F84E378
		bl GXLoadTexObj
		opword 0x28140000
		opword 0x4182003C
		opword 0x1C9C0003
		opword 0x7E83A378
		opword 0x38A00001
		opword 0x3A44001E
		opword 0x7E449378
		bl GXLoadTexMtxImm
		opword 0x7F83E378
		opword 0x7E469378
		opword 0x38BC0004
		opword 0x38800001
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x48000020
		opword 0x7F83E378
		opword 0x38BC0004
		opword 0x38800001
		opword 0x38C0003C
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x3B800001
		opword 0x48000014
		opword 0x3B9C0001
		opword 0x7C1CD800
		opword 0x4180FF1C
		opword 0x3B800000
		opword 0x2C1C0000
		opword 0x7F80E378
		opword 0x40820124
		lwz r4, wp(r13)
		opword 0x3A800000
		opword 0x82BD0000
		opword 0x80A40020
		opword 0x80640018
		opword 0x826400D0
		opword 0x83640028
		opword 0x83440034
		opword 0x83250198
		opword 0x83050134
		opword 0x82E3006C
		opword 0x82C50194
		opword 0x480000E4
		opword 0x7C74A850
		opword 0x3803FFFF
		opword 0x5403103A
		opword 0x38030010
		opword 0x7C1D002E
		opword 0x1C600018
		opword 0x54001838
		opword 0x7C16002E
		opword 0x7C9718AE
		opword 0x7E402215
		opword 0x4180000C
		opword 0x7C12C000
		opword 0x41800018
		lis r3, str_802C2DF8@ha
		opword 0x3A400000
		addi r3, r3, str_802C2DF8@l
		opword 0x4CC63182
		bl printf
		opword 0x56433032
		opword 0x38030008
		opword 0x7C19002E
		opword 0x2C000002
		opword 0x40820084
		opword 0x281A0000
		opword 0x41820074
		opword 0x7F43D378
		opword 0x7F64DB78
		bl smartTexObj
		opword 0x7E84A378
		bl GXLoadTexObj
		opword 0x28130000
		opword 0x4182003C
		opword 0x1C940003
		opword 0x7E639B78
		opword 0x38A00001
		opword 0x3A44001E
		opword 0x7E449378
		bl GXLoadTexMtxImm
		opword 0x7E83A378
		opword 0x7E469378
		opword 0x38B40004
		opword 0x38800001
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x48000020
		opword 0x7E83A378
		opword 0x38B40004
		opword 0x38800001
		opword 0x38C0003C
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x38000001
		opword 0x48000014
		opword 0x3A940001
		opword 0x7C14A800
		opword 0x4180FF1C
		opword 0x38000000
		opword 0x2C000000
		opword 0x41820138
		opword 0x801D0008
		opword 0x2C000000
		opword 0x4082012C
		lwz r3, wp(r13)
		opword 0x82430038
		opword 0x28120000
		opword 0x4182011C
		opword 0x8083002C
		opword 0x7E439378
		bl smartTexObj
		lwz r3, wp(r13)
		opword 0x800300E0
		opword 0x2C000003
		opword 0x41820048
		opword 0x38600001
		opword 0x38800003
		opword 0x38A00001
		bl GXSetZMode
		opword 0x38600000
		opword 0x38800004
		opword 0x38A00005
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
		opword 0x7F800034
		lwz r4, wp(r13)
		opword 0x5403E8FA
		opword 0x38030030
		opword 0x7C64002E
		opword 0x28030000
		opword 0x41820048
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0001E
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7F800034
		lwz r5, wp(r13)
		opword 0x5403E8FA
		opword 0x3880001E
		opword 0x380300CC
		opword 0x7C65002E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x7E439378
		opword 0x38800001
		bl GXLoadTexObj
		opword 0x38600001
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C00021
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		lwz r3, wp(r13)
		opword 0x38800021
		opword 0x38A00001
		opword 0x806300D4
		bl GXLoadTexMtxImm
		lwz r5, wp(r13)
		opword 0x38600002
		lwz r6, g_modeling_mtx(r13)
		opword 0x3880000C
		opword 0x80A50018
		opword 0x80A500E8
		bl mapSetMaterialTev
		lwz r3, wp(r13)
		opword 0x80A30018
		opword 0x80050000
		opword 0x540006F7
		opword 0x41820124
		opword 0x83630030
		opword 0x281B0000
		opword 0x41820118
		opword 0x834300CC
		opword 0x281A0000
		opword 0x4182010C
		opword 0x80830020
		opword 0x3A600000
		opword 0x83230024
		opword 0x83040198
		opword 0x82E40134
		opword 0x82C5006C
		opword 0x82A40194
		opword 0x829D0000
		opword 0x480000E0
		opword 0x7C73A050
		opword 0x3803FFFF
		opword 0x5403103A
		opword 0x38030010
		opword 0x7C1D002E
		opword 0x1C600018
		opword 0x54001838
		opword 0x7C15002E
		opword 0x7C9618AE
		opword 0x7E402215
		opword 0x4180000C
		opword 0x7C12B800
		opword 0x41800018
		lis r3, str_802C2DF8@ha
		opword 0x3A400000
		addi r3, r3, str_802C2DF8@l
		opword 0x4CC63182
		bl printf
		opword 0x56433032
		opword 0x38030008
		opword 0x7C18002E
		opword 0x2C000001
		opword 0x40820080
		opword 0x281B0000
		opword 0x41820084
		opword 0x7F63DB78
		opword 0x7F24CB78
		bl smartTexObj
		opword 0x7E649B78
		bl GXLoadTexObj
		opword 0x281A0000
		opword 0x4182003C
		opword 0x1C930003
		opword 0x7F43D378
		opword 0x38A00001
		opword 0x3A44001E
		opword 0x7E449378
		bl GXLoadTexMtxImm
		opword 0x7E639B78
		opword 0x7E469378
		opword 0x38B30004
		opword 0x38800001
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x48000030
		opword 0x7E639B78
		opword 0x38B30004
		opword 0x38800001
		opword 0x38C0003C
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x48000010
		opword 0x3A730001
		opword 0x7C13A000
		opword 0x4180FF20
		opword 0x3BFF0001
		opword 0x3BBD006C
		opword 0x7C1FF000
		opword 0x4180FA08
		opword 0xBA410088
		opword 0x800100C4
		opword 0x7C0803A6
		opword 0x382100C0
	}
}
#pragma pop
#endif


// I'm so sorry, whoever gets tasked with matching this function
// note: I detect at least 8 inlined functions here, good luck finding the separation
#ifdef NONMATCHING
void renderProc(s32 shapeId, s32 unused) {
    int i;
    CameraEntry* camera;
    AnimationPoseData* data;
    AnimPoseShape *shapes, *shape;
    AnimPoseShapeDraw *draws, *draw;
    s32 dispMode, drawId;
    s32 posFirstVtx, nrmFirstVtx, clr0FirstVtx;

    f32* buffer;
    s32 nrmVtxSize;
    s32 texCount;
    AnimationPose* pose;
    Mtx* mtx;
    GXTexObj* texObj;
    BOOL texChange1, check1, texChange2, check2;
    GXTexObj* currTexObj;
    s8* texIds;
    s32* firstId;
    AnimDrawCallEntry* drawCall;
    s32 drawCallCount;
    GXColor* clr0VtxPtr;
    s32 posFirstId, nrmFirstId, clr0FirstId;
    Vec *nrmVtxPtr, *posVtxPtr;

    s32 count;
    u16 *posIndexPtr, *nrmIndexPtr, *clr0IndexPtr, *texIndexPtr;
    s32 firstDrawId;
    s32 index;
    s32 texIndex;

    int j, k, l, k2;

    // stack variables
    s32 clr0VtxSize, posVtxSize; // TODO: make sure stack, +0xB0, +0xAC
    s32 drawCount;               // TODO: make sure stack, +0xA8
    Mtx camMtx, invCamMtx;
    f32* texVtxIndices[8];
    Vec lightPos, lightPos2; // TODO: rename? 2 is probably implicit stack copy

    if (shapeId != -1) {
        camera = camGetCurPtr();
        MTXConcat(camera->view, *g_modeling_mtx, camMtx);
        GXLoadPosMtxImm(camMtx, 0);
        MTXInvXpose(camMtx, invCamMtx);
        GXLoadNrmMtxImm(invCamMtx, 0);
        GXSetCurrentMtx(0);

        data = wp->mpCurPoseData;
        shapes = data->shapes;
        draws = data->draws;
        shape = &shapes[shapeId];
        dispMode = shape->dispMode;
        drawId = shape->shapeDrawStart;
        posFirstVtx = shape->vtxPos.first;
        nrmFirstVtx = shape->vtxNrm.first;
        clr0FirstVtx = shape->vtxClr0.first;
        drawCount = shape->shapeDrawCount;
        draw = &draws[drawId];

        if ((dispMode == 0 && wp->currDispMode == 2) || dispMode == wp->currDispMode ||
            wp->mpCurPose->materialColor.a != 0xFF || wp->mpCurPose->materialColor2.a != 0xFF) {
            GXSetCullMode(tbl[shape->cullMode]);
            data = wp->mpCurPoseData;
            clr0VtxSize = (s32)sizeof(GXColor) * clr0FirstVtx;
            buffer = data->texVtxBuffer;
            texVtxIndices[0] = &buffer[2 * shape->vtxTex[0].first];
            texVtxIndices[1] = &buffer[2 * shape->vtxTex[1].first];
            texVtxIndices[2] = &buffer[2 * shape->vtxTex[2].first];
            texVtxIndices[3] = &buffer[2 * shape->vtxTex[3].first];
            texVtxIndices[4] = &buffer[2 * shape->vtxTex[4].first];
            texVtxIndices[5] = &buffer[2 * shape->vtxTex[5].first];
            texVtxIndices[6] = &buffer[2 * shape->vtxTex[6].first];
            texVtxIndices[7] = &buffer[2 * shape->vtxTex[7].first];
            nrmVtxSize = (s32)sizeof(Vec) * nrmFirstVtx;
            posVtxSize = (s32)sizeof(Vec) * posFirstVtx;

            for (i = 0; i < drawCount; i++, draw++) {
                texCount = draw->texCount;
                if ((u32)wp->mpCurPose->disableDraw == 0) {
                    lightPos = (Vec){ 0.0f, 0.0f, 0.0f };
                    MTXMultVec(*g_modeling_mtx, &lightPos, &lightPos);
                    lightPos2 = lightPos;
                    mapSetMaterialLight(wp->mpCurPose->materialLightFlag, lightPos2);
                    animSetMaterial_Texture(draw->texCount, draw->texDataIds, wp->mpCurPoseData->texData,
                                            wp->mpCurPose->mpTexAnimEntries, wp->mpCurPoseData->texBindCount,
                                            wp->mpCurPoseData->texBinds,
                                            &wp->textures[wp->files[wp->mpCurPose->fileId].textureId]);
                    mapSetMaterialLastStageBlend(wp->mpCurPose->materialFlag, wp->mpCurPose->materialColor,
                                                 wp->mpCurPose->materialColor2);
                    camera = camGetPtr(CAMERA_3D);
                    if (camGetCurPtr() == camera) {
                        mapSetMaterialFog();
                    }
                    mapSetMaterialTev(texCount, draw->drawMode, wp->mpCurPose->materialFlag, *g_modeling_mtx);
                }
                pose = wp->mpCurPose;
                if ((u32)pose->typeFlags != 0) {
                    texChange1 = animSetMaterial_ChangeTexture(wp->mpCurPoseData, draw, pose, wp->mpTexObjs[0], wp->mpTexDatas[0], *wp->paperMtxPtr[0], 1);
                    check1 = texChange1;
                    if (!texChange1) {
                        pose = wp->mpCurPose;
                        texChange2 = animSetMaterial_ChangeTexture(wp->mpCurPoseData, draw, pose, wp->mpTexObjs[1], wp->mpTexDatas[1], *wp->paperMtxPtr[1], 2);
                        check1 = texChange2;
                        check2 = texChange2;
                    } else {
                        check2 = FALSE;
                    }

                    if (check1 && (texChange1 && (s32)wp->field_0xD8 == 0 || check2 && (s32)wp->field_0xDC == 0) && !draw->drawMode) {
                        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
                    }
                    if (check1 && !draw->drawMode) {
                        currTexObj = wp->mpCurTexObj;
                        if (currTexObj) {
                            smartTexObj(currTexObj, wp->mpCurTexData);
                            if (wp->currDispMode != 3) {
                                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
                                GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                                GXSetZCompLoc(GX_FALSE);
                                GXSetAlphaCompare(GX_GEQUAL, 0x80u, GX_AOP_OR, GX_NEVER, 0);
                            }
                            texObj = wp->mpTexObjs[texChange1 == 0];
                            if (texObj) {
                                GXLoadTexObj(texObj, GX_TEXMAP0);
                                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE,
                                                  GX_PTIDENTITY);
                                GXLoadTexMtxImm(*wp->paperMtxPtr[!texChange1], GX_TEXMTX0, GX_MTX2x4);
                            }
                            GXLoadTexObj(currTexObj, GX_TEXMAP1);
                            GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE,
                                              GX_PTIDENTITY);
                            GXLoadTexMtxImm(*wp->paperMtxPtr[2], GX_TEXMTX1, GX_MTX2x4);
                            mapSetMaterialTev(2, 12, wp->mpCurPose->materialFlag, *g_modeling_mtx);
                        }
                    }
                }

                pose = wp->mpCurPose;
                if (pose->flags & 0x10) {
                    texObj = wp->mpTexObjs[0];
                    if (texObj) {
                        mtx = wp->paperMtxPtr[0];
                        if (mtx) {
                            animSetMaterial_ChangeTexture(wp->mpCurPoseData, draw, pose, texObj, wp->mpTexDatas[0], *mtx, 1);
                        }
                    }
                }

                texIds = (s8*)draw->texArrayIds;
                firstId = draw->firstIdTex;
                data = wp->mpCurPoseData; // inlined function here
                drawCall = &data->drawCalls[draw->firstDrawCall];
                texCount = draw->texCount;
                drawCallCount = draw->drawCallCount;
                clr0VtxPtr = (GXColor*)((u8*)data->clr0VtxBuffer + clr0VtxSize);
                posFirstId = draw->firstIdPos;
                nrmFirstId = draw->firstIdNrm;
                clr0FirstId = draw->firstIdClr0;

                if ((s32)wp->mbUseFloatScratch != 0) {
                    nrmVtxPtr = (Vec*)((u8*)wp->vtxArrayNrm + nrmVtxSize);
                    posVtxPtr = (Vec*)((u8*)wp->vtxArrayPos + posVtxSize);
                } else {
                    pose = wp->mpCurPose;
                    nrmVtxPtr = (Vec*)((u8*)pose->mpVtxArrayNrm + nrmVtxSize);
                    posVtxPtr = (Vec*)((u8*)pose->mpVtxArrayPos + posVtxSize);
                }
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
                GXSetArray(GX_VA_POS, posVtxPtr, sizeof(Vec));
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
                GXSetArray(GX_VA_NRM, nrmVtxPtr, sizeof(Vec));
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
                GXSetArray(GX_VA_CLR0, clr0VtxPtr, sizeof(GXColor));

                if (texCount == 1) { // just use texIndex[0]
                    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
                    GXSetArray(GX_VA_TEX0, texVtxIndices[texIds[0]], sizeof(f32) * 2);
                    for (j = 0; j < drawCallCount; j++, drawCall++) {
                        firstDrawId = drawCall->first;
                        data = wp->mpCurPoseData;
                        posIndexPtr = (u16*)((u32*)data->posIndex + (firstDrawId + posFirstId)) + 1;
                        nrmIndexPtr = (u16*)((u32*)data->nrmIndex + (firstDrawId + nrmFirstId)) + 1;
                        clr0IndexPtr = (u16*)((u32*)data->clr0Index + (firstDrawId + clr0FirstId)) + 1;
                        texIndexPtr = (u16*)((u32*)data->texIndex[texIds[0]] + (firstDrawId + firstId[texIds[0]])) + 1;
                        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, count = (u16)drawCall->count);
                        for (k = count; k > 0; k--) {
                            GXPosition1x16(*posIndexPtr);
                            posIndexPtr += 2;
                            GXNormal1x16(*nrmIndexPtr);
                            nrmIndexPtr += 2;
                            GXColor1x16(*clr0IndexPtr);
                            clr0IndexPtr += 2;
                            GXTexCoord1x16(*texIndexPtr);
                            texIndexPtr += 2;
                        }
                    }
                } else { // enumerate texIndex
                    for (j = 0; j < texCount; j++) {
                        GXSetVtxDesc(GX_VA_TEX0 + j, GX_INDEX16);
                        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0 + j, GX_TEX_ST, GX_F32, 0);
                        GXSetArray(GX_VA_TEX0 + j, texVtxIndices[texIds[texCount - j - 1]], sizeof(f32) * 2);
                    }
                    for (j = 0; j < drawCallCount; j++, drawCall++) {
                        firstDrawId = drawCall->first;
                        data = wp->mpCurPoseData;
                        count = (u16)drawCall->count;
                        posIndexPtr = (u16*)((u32*)data->posIndex + (firstDrawId + posFirstId)) + 1;
                        nrmIndexPtr = (u16*)((u32*)data->nrmIndex + (firstDrawId + nrmFirstId)) + 1;
                        clr0IndexPtr = (u16*)((u32*)data->clr0Index + (firstDrawId + clr0FirstId)) + 1;
                        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, count);
                        for (k2 = 0; k2 < count; k2++) {
                            GXPosition1x16(*posIndexPtr);
                            GXNormal1x16(*nrmIndexPtr);
                            GXColor1x16(*clr0IndexPtr);
                            for (l = texCount, index = 0; l > 0; l--, index++) {
                                texIndex = texIds[(u32)(texCount - index - 1)];
                                GXTexCoord1x16((&((u32*)wp->mpCurPoseData->texIndex[texIndex])[firstDrawId + firstId[texIndex]])[k2]);
                            }
                            posIndexPtr += 2;
                            nrmIndexPtr += 2;
                            clr0IndexPtr += 2;
                        }
                    }
                }
            }
        }
    }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void renderProc(s32 shapeId, s32 unused) {
	asm volatile {
		opword 0x9421FF00
		opword 0x7C0802A6
		opword 0x90010104
		opword 0xBDC100B8
		opword 0x7C6E1B78
		opword 0x2C0EFFFF
		opword 0x41820D5C
		bl camGetCurPtr
		lwz r4, g_modeling_mtx(r13)
		opword 0x38A10078
		opword 0x3863011C
		bl PSMTXConcat
		opword 0x38610078
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x38610078
		opword 0x38810048
		bl PSMTXInvXpose
		opword 0x38610048
		opword 0x38800000
		bl GXLoadNrmMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		lwz r5, wp(r13)
		opword 0x1C0E00A8
		opword 0x80850020
		opword 0x8064014C
		opword 0x8084019C
		opword 0x7DC30214
		opword 0x800E0098
		opword 0x80CE00A0
		opword 0x1C60006C
		opword 0x800E009C
		opword 0x2C060000
		opword 0x81EE0040
		opword 0x820E0048
		opword 0x822E0050
		opword 0x900100A8
		opword 0x7F841A14
		opword 0x40820010
		opword 0x800500E0
		opword 0x2C000002
		opword 0x4182002C
		opword 0x800500E0
		opword 0x7C060000
		opword 0x41820020
		opword 0x80650018
		opword 0x880300F3
		opword 0x280000FF
		opword 0x40820010
		opword 0x880300F7
		opword 0x280000FF
		opword 0x41820CA4
		opword 0x800E00A4
		la r3, g5_tbl_s1109(r13)
		opword 0x5400103A
		opword 0x7C63002E
		bl GXSetCullMode
		opword 0x1C0F000C
		lwz r4, wp(r13)
		opword 0x806E0058
		opword 0x3BA00000
		opword 0x80C40020
		opword 0x900100AC
		opword 0x5620103A
		opword 0x808E0060
		opword 0x900100B0
		opword 0x54651838
		opword 0x800E0068
		opword 0x54881838
		opword 0x8146018C
		opword 0x54071838
		opword 0x806E0070
		opword 0x808E0080
		opword 0x7D2A2A14
		opword 0x54661838
		opword 0x800E0078
		opword 0x806E0088
		opword 0x54841838
		opword 0x54051838
		opword 0x800E0090
		opword 0x54631838
		opword 0x7D0A4214
		opword 0x54001838
		opword 0x7CEA3A14
		opword 0x7CCA3214
		opword 0x7CAA2A14
		opword 0x7C8A2214
		opword 0x7C6A1A14
		opword 0x7C0A0214
		opword 0x91210028
		opword 0x1DD0000C
		opword 0x9101002C
		opword 0x90E10030
		opword 0x90C10034
		opword 0x90A10038
		opword 0x9081003C
		opword 0x90610040
		opword 0x90010044
		opword 0x48000BDC
		lwz r3, wp(r13)
		opword 0x81FC0000
		opword 0x80630018
		opword 0x800300E4
		opword 0x28000000
		opword 0x40820110
		lis r3, vec3_802c2dbc@ha
		opword 0x3881001C
		addi r8, r3, vec3_802c2dbc@l
		lwz r3, g_modeling_mtx(r13)
		opword 0x80E80000
		opword 0x7C852378
		opword 0x80C80004
		opword 0x80080008
		opword 0x90E1001C
		opword 0x90C10020
		opword 0x90010024
		bl PSMTXMultVec
		opword 0x8061001C
		opword 0x38810010
		opword 0x80A10020
		opword 0x80010024
		opword 0x90610010
		lwz r3, wp(r13)
		opword 0x90A10014
		opword 0x90010018
		opword 0x80630018
		opword 0x806300EC
		bl mapSetMaterialLight
		lwz r7, wp(r13)
		opword 0x389C0010
		opword 0x807C0000
		opword 0x81470018
		opword 0x81070020
		opword 0x800A0010
		opword 0x80C70000
		opword 0x54052036
		opword 0x81270008
		opword 0x3805000C
		opword 0x80A80194
		opword 0x7C06002E
		opword 0x80CA006C
		opword 0x1C00000C
		opword 0x80E80134
		opword 0x81080198
		opword 0x7D290214
		bl animSetMaterial_Texture
		lwz r6, wp(r13)
		opword 0x3881000C
		opword 0x38A10008
		opword 0x80660018
		opword 0x800300F4
		opword 0x90010008
		opword 0x80660018
		opword 0x800300F0
		opword 0x9001000C
		opword 0x80660018
		opword 0x806300E8
		bl mapSetMaterialLastStageBlend
		opword 0x38600004
		bl camGetPtr
		opword 0x7C701B78
		bl camGetCurPtr
		opword 0x7C038040
		opword 0x40820008
		bl mapSetMaterialFog
		lwz r5, wp(r13)
		opword 0x7DE37B78
		opword 0x809C0008
		opword 0x80A50018
		lwz r6, g_modeling_mtx(r13)
		opword 0x80A500E8
		bl mapSetMaterialTev
		lwz r3, wp(r13)
		opword 0x80A30018
		opword 0x80050004
		opword 0x28000000
		opword 0x418203F0
		opword 0x80830020
		opword 0x39E00000
		opword 0x82E300CC
		opword 0x82C30024
		opword 0x82A30030
		opword 0x82840198
		opword 0x82640134
		opword 0x8245006C
		opword 0x82240194
		opword 0x821C0000
		opword 0x480000E4
		opword 0x7C6F8050
		opword 0x3803FFFF
		opword 0x5403103A
		opword 0x38030010
		opword 0x7C1C002E
		opword 0x1C600018
		opword 0x54001838
		opword 0x7C11002E
		opword 0x7C9218AE
		opword 0x7F002215
		opword 0x4180000C
		opword 0x7C189800
		opword 0x41800018
		lis r3, str_802C2DF8@ha
		opword 0x3B000000
		addi r3, r3, str_802C2DF8@l
		opword 0x4CC63182
		bl printf
		opword 0x57033032
		opword 0x38030008
		opword 0x7C14002E
		opword 0x2C000001
		opword 0x40820084
		opword 0x28150000
		opword 0x41820074
		opword 0x7EA3AB78
		opword 0x7EC4B378
		bl smartTexObj
		opword 0x7DE47B78
		bl GXLoadTexObj
		opword 0x28170000
		opword 0x4182003C
		opword 0x1C8F0003
		opword 0x7EE3BB78
		opword 0x38A00001
		opword 0x3A04001E
		opword 0x7E048378
		bl GXLoadTexMtxImm
		opword 0x7DE37B78
		opword 0x7E068378
		opword 0x38AF0004
		opword 0x38800001
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x48000020
		opword 0x7DE37B78
		opword 0x38AF0004
		opword 0x38800001
		opword 0x38C0003C
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x39E00001
		opword 0x48000014
		opword 0x39EF0001
		opword 0x7C0F8000
		opword 0x4180FF1C
		opword 0x39E00000
		opword 0x2C0F0000
		opword 0x7DF07B78
		opword 0x40820130
		lwz r4, wp(r13)
		opword 0x3A000000
		opword 0x823C0000
		opword 0x80A40020
		opword 0x80640018
		opword 0x830400D0
		opword 0x82E40028
		opword 0x82C40034
		opword 0x82A50198
		opword 0x82850134
		opword 0x8263006C
		opword 0x82450194
		opword 0x480000E4
		opword 0x7C708850
		opword 0x3803FFFF
		opword 0x5403103A
		opword 0x38030010
		opword 0x7C1C002E
		opword 0x1C600018
		opword 0x54001838
		opword 0x7C12002E
		opword 0x7C9318AE
		opword 0x7F202215
		opword 0x4180000C
		opword 0x7C19A000
		opword 0x41800018
		lis r3, str_802C2DF8@ha
		opword 0x3B200000
		addi r3, r3, str_802C2DF8@l
		opword 0x4CC63182
		bl printf
		opword 0x57233032
		opword 0x38030008
		opword 0x7C15002E
		opword 0x2C000002
		opword 0x40820084
		opword 0x28160000
		opword 0x41820074
		opword 0x7EC3B378
		opword 0x7EE4BB78
		bl smartTexObj
		opword 0x7E048378
		bl GXLoadTexObj
		opword 0x28180000
		opword 0x4182003C
		opword 0x1C900003
		opword 0x7F03C378
		opword 0x38A00001
		opword 0x3A24001E
		opword 0x7E248B78
		bl GXLoadTexMtxImm
		opword 0x7E038378
		opword 0x7E268B78
		opword 0x38B00004
		opword 0x38800001
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x48000020
		opword 0x7E038378
		opword 0x38B00004
		opword 0x38800001
		opword 0x38C0003C
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x38000001
		opword 0x48000014
		opword 0x3A100001
		opword 0x7C108800
		opword 0x4180FF1C
		opword 0x38000000
		opword 0x7C100378
		opword 0x7C040378
		opword 0x48000008
		opword 0x38800000
		opword 0x2C100000
		opword 0x41820058
		opword 0x2C0F0000
		opword 0x41820014
		lwz r3, wp(r13)
		opword 0x800300D8
		opword 0x2C000000
		opword 0x4182001C
		opword 0x2C040000
		opword 0x41820038
		lwz r3, wp(r13)
		opword 0x800300DC
		opword 0x2C000000
		opword 0x40820028
		opword 0x801C0008
		opword 0x2C000000
		opword 0x4082001C
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00005
		bl GXSetTevAlphaIn
		opword 0x2C100000
		opword 0x41820138
		opword 0x801C0008
		opword 0x2C000000
		opword 0x4082012C
		lwz r3, wp(r13)
		opword 0x82030038
		opword 0x28100000
		opword 0x4182011C
		opword 0x8083002C
		opword 0x7E038378
		bl smartTexObj
		lwz r3, wp(r13)
		opword 0x800300E0
		opword 0x2C000003
		opword 0x41820048
		opword 0x38600001
		opword 0x38800003
		opword 0x38A00001
		bl GXSetZMode
		opword 0x38600000
		opword 0x38800004
		opword 0x38A00005
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
		opword 0x7DE00034
		lwz r4, wp(r13)
		opword 0x5403E8FA
		opword 0x38030030
		opword 0x7C64002E
		opword 0x28030000
		opword 0x41820048
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0001E
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7DE00034
		lwz r5, wp(r13)
		opword 0x5403E8FA
		opword 0x3880001E
		opword 0x380300CC
		opword 0x7C65002E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x7E038378
		opword 0x38800001
		bl GXLoadTexObj
		opword 0x38600001
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C00021
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		lwz r3, wp(r13)
		opword 0x38800021
		opword 0x38A00001
		opword 0x806300D4
		bl GXLoadTexMtxImm
		lwz r5, wp(r13)
		opword 0x38600002
		lwz r6, g_modeling_mtx(r13)
		opword 0x3880000C
		opword 0x80A50018
		opword 0x80A500E8
		bl mapSetMaterialTev
		lwz r3, wp(r13)
		opword 0x80A30018
		opword 0x80050000
		opword 0x540006F7
		opword 0x41820124
		opword 0x82E30030
		opword 0x28170000
		opword 0x41820118
		opword 0x82C300CC
		opword 0x28160000
		opword 0x4182010C
		opword 0x80830020
		opword 0x39E00000
		opword 0x82A30024
		opword 0x82840198
		opword 0x82640134
		opword 0x8245006C
		opword 0x82240194
		opword 0x821C0000
		opword 0x480000E0
		opword 0x7C6F8050
		opword 0x3803FFFF
		opword 0x5403103A
		opword 0x38030010
		opword 0x7C1C002E
		opword 0x1C600018
		opword 0x54001838
		opword 0x7C11002E
		opword 0x7C9218AE
		opword 0x7F002215
		opword 0x4180000C
		opword 0x7C189800
		opword 0x41800018
		lis r3, str_802C2DF8@ha
		opword 0x3B000000
		addi r3, r3, str_802C2DF8@l
		opword 0x4CC63182
		bl printf
		opword 0x57033032
		opword 0x38030008
		opword 0x7C14002E
		opword 0x2C000001
		opword 0x40820080
		opword 0x28170000
		opword 0x41820084
		opword 0x7EE3BB78
		opword 0x7EA4AB78
		bl smartTexObj
		opword 0x7DE47B78
		bl GXLoadTexObj
		opword 0x28160000
		opword 0x4182003C
		opword 0x1C8F0003
		opword 0x7EC3B378
		opword 0x38A00001
		opword 0x3A04001E
		opword 0x7E048378
		bl GXLoadTexMtxImm
		opword 0x7DE37B78
		opword 0x7E068378
		opword 0x38AF0004
		opword 0x38800001
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x48000030
		opword 0x7DE37B78
		opword 0x38AF0004
		opword 0x38800001
		opword 0x38C0003C
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x48000010
		opword 0x39EF0001
		opword 0x7C0F8000
		opword 0x4180FF20
		lwz r7, wp(r13)
		opword 0x3B5C0030
		opword 0x807C0038
		opword 0x3ABC004C
		opword 0x80C70020
		opword 0x800700E8
		opword 0x54641838
		opword 0x80A60150
		opword 0x2C000000
		opword 0x80660164
		opword 0x800100B0
		opword 0x7E852214
		opword 0x837C0000
		opword 0x833C003C
		opword 0x7DE30214
		opword 0x831C0040
		opword 0x82FC0044
		opword 0x82DC0048
		opword 0x4182001C
		opword 0x806700FC
		opword 0x808700F8
		opword 0x800100AC
		opword 0x7E237214
		opword 0x7E040214
		opword 0x4800001C
		opword 0x80670018
		opword 0x800100AC
		opword 0x8083004C
		opword 0x80630054
		opword 0x7E040214
		opword 0x7E237214
		bl GXClearVtxDesc
		opword 0x38600009
		opword 0x38800003
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x38800009
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x7E048378
		opword 0x38600009
		opword 0x38A0000C
		bl GXSetArray
		opword 0x3860000A
		opword 0x38800003
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x3880000A
		opword 0x38A00000
		opword 0x38C00004
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x7E248B78
		opword 0x3860000A
		opword 0x38A0000C
		bl GXSetArray
		opword 0x3860000B
		opword 0x38800003
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x3880000B
		opword 0x38A00001
		opword 0x38C00005
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x7DE47B78
		opword 0x3860000B
		opword 0x38A00004
		bl GXSetArray
		opword 0x2C1B0001
		opword 0x408201DC
		opword 0x3860000D
		opword 0x38800003
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x3880000D
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x881A0000
		opword 0x38810028
		opword 0x3860000D
		opword 0x38A00008
		opword 0x7C000774
		opword 0x5400103A
		opword 0x7C84002E
		bl GXSetArray
		opword 0x39E00000
		opword 0x3FC0CC01
		opword 0x48000180
		opword 0x881A0000
		opword 0x386000A0
		opword 0x81540000
		opword 0x38800000
		opword 0x7C000774
		lwz r5, wp(r13)
		opword 0x5408103A
		opword 0x7D2AC214
		opword 0x7C15402E
		opword 0x7CEABA14
		opword 0x80A50020
		opword 0x7CCAB214
		opword 0x3908016C
		opword 0x7C0A0214
		opword 0x81940004
		opword 0x552B103A
		opword 0x54EA103A
		opword 0x54C9103A
		opword 0x5407103A
		opword 0x5590043E
		opword 0x80C50158
		opword 0x3A2B0002
		opword 0x80050160
		opword 0x3A4A0002
		opword 0x81450168
		opword 0x3A690002
		opword 0x7D05402E
		opword 0x3B670002
		opword 0x7E058378
		opword 0x7E268A14
		opword 0x7E409214
		opword 0x7E6A9A14
		opword 0x7F68DA14
		bl GXBegin
		opword 0x2C100000
		opword 0x7E038378
		opword 0x408100E4
		opword 0x5600F0BF
		opword 0x7C0903A6
		opword 0x418200A0
		opword 0xA0110000
		opword 0xB01E8000
		opword 0xA0120000
		opword 0xB01E8000
		opword 0xA0130000
		opword 0xB01E8000
		opword 0xA01B0000
		opword 0xB01E8000
		opword 0xA0110004
		opword 0xB01E8000
		opword 0xA0120004
		opword 0xB01E8000
		opword 0xA0130004
		opword 0xB01E8000
		opword 0xA01B0004
		opword 0xB01E8000
		opword 0xA0110008
		opword 0xB01E8000
		opword 0xA0120008
		opword 0xB01E8000
		opword 0xA0130008
		opword 0xB01E8000
		opword 0xA01B0008
		opword 0xB01E8000
		opword 0xA011000C
		opword 0x3A310010
		opword 0xB01E8000
		opword 0xA012000C
		opword 0x3A520010
		opword 0xB01E8000
		opword 0xA013000C
		opword 0x3A730010
		opword 0xB01E8000
		opword 0xA01B000C
		opword 0x3B7B0010
		opword 0xB01E8000
		opword 0x4200FF70
		opword 0x70630003
		opword 0x4182003C
		opword 0x7C6903A6
		opword 0xA0110000
		opword 0x3A310004
		opword 0xB01E8000
		opword 0xA0120000
		opword 0x3A520004
		opword 0xB01E8000
		opword 0xA0130000
		opword 0x3A730004
		opword 0xB01E8000
		opword 0xA01B0000
		opword 0x3B7B0004
		opword 0xB01E8000
		opword 0x4200FFD0
		opword 0x39EF0001
		opword 0x3A940008
		opword 0x7C0FC800
		opword 0x4180FE80
		opword 0x48000280
		opword 0x3A010028
		opword 0x39E00000
		opword 0x48000050
		opword 0x386F000D
		opword 0x38800003
		bl GXSetVtxDesc
		opword 0x388F000D
		opword 0x38600000
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x7C8FD850
		opword 0x386F000D
		opword 0x3804FFFF
		opword 0x38A00008
		opword 0x7C1A00AE
		opword 0x7C000774
		opword 0x5400103A
		opword 0x7C90002E
		bl GXSetArray
		opword 0x39EF0001
		opword 0x7C0FD800
		opword 0x4180FFB0
		opword 0x3BC00000
		opword 0x3FE0CC01
		opword 0x4800020C
		lwz r5, wp(r13)
		opword 0x386000A0
		opword 0x82740000
		opword 0x38800000
		opword 0x80A50020
		opword 0x7CF3C214
		opword 0x7CD3BA14
		opword 0x7C13B214
		opword 0x81340004
		opword 0x54E8103A
		opword 0x54C7103A
		opword 0x5406103A
		opword 0x5532043E
		opword 0x81250158
		opword 0x3A280002
		opword 0x81050160
		opword 0x3A070002
		opword 0x80050168
		opword 0x39E60002
		opword 0x7E459378
		opword 0x7E298A14
		opword 0x7E088214
		opword 0x7DE07A14
		bl GXBegin
		lwz r5, wp(r13)
		opword 0x39000000
		opword 0x38C00000
		opword 0x4800018C
		opword 0xA0110000
		opword 0x2C1B0000
		opword 0x7F6ADB78
		opword 0x39200000
		opword 0xB01F8000
		opword 0xA0100000
		opword 0xB01F8000
		opword 0xA00F0000
		opword 0xB01F8000
		opword 0x40810150
		opword 0x5760F0BF
		opword 0x7C0903A6
		opword 0x41820100
		opword 0x7C09D850
		opword 0x80650020
		opword 0x7C80D214
		opword 0x39290001
		opword 0x88E4FFFF
		opword 0x7C09D850
		opword 0x7C80D214
		opword 0x39290001
		opword 0x7CE70774
		opword 0x54E7103A
		opword 0x7C09D850
		opword 0x7D75382E
		opword 0x38E7016C
		opword 0x7C63382E
		opword 0x39290001
		opword 0x7CF35A14
		opword 0x54E7103A
		opword 0x7C633A14
		opword 0x7C66182E
		opword 0xB07F8000
		opword 0x88E4FFFF
		opword 0x7C80D214
		opword 0x7C09D850
		opword 0x80650020
		opword 0x7CE70774
		opword 0x39290001
		opword 0x54E7103A
		opword 0x7D75382E
		opword 0x38E7016C
		opword 0x7C63382E
		opword 0x7CF35A14
		opword 0x54E7103A
		opword 0x7C633A14
		opword 0x7C66182E
		opword 0xB07F8000
		opword 0x88E4FFFF
		opword 0x7C80D214
		opword 0x80650020
		opword 0x7CE70774
		opword 0x54E7103A
		opword 0x7D75382E
		opword 0x38E7016C
		opword 0x7C63382E
		opword 0x7CF35A14
		opword 0x54E7103A
		opword 0x7C633A14
		opword 0x7C66182E
		opword 0xB07F8000
		opword 0x88E4FFFF
		opword 0x80650020
		opword 0x7CE70774
		opword 0x54E7103A
		opword 0x7D75382E
		opword 0x38E7016C
		opword 0x7C63382E
		opword 0x7CF35A14
		opword 0x54E7103A
		opword 0x7C633A14
		opword 0x7C66182E
		opword 0xB07F8000
		opword 0x4200FF10
		opword 0x714A0003
		opword 0x41820048
		opword 0x7D4903A6
		opword 0x7C09D850
		opword 0x80650020
		opword 0x7C80D214
		opword 0x39290001
		opword 0x88E4FFFF
		opword 0x7CE70774
		opword 0x54E7103A
		opword 0x7D75382E
		opword 0x38E7016C
		opword 0x7C63382E
		opword 0x7CF35A14
		opword 0x54E7103A
		opword 0x7C633A14
		opword 0x7C66182E
		opword 0xB07F8000
		opword 0x4200FFC4
		opword 0x38C60004
		opword 0x39080001
		opword 0x3A310004
		opword 0x3A100004
		opword 0x39EF0004
		opword 0x7C089000
		opword 0x4180FE74
		opword 0x3BDE0001
		opword 0x3A940008
		opword 0x7C1EC800
		opword 0x4180FDF4
		opword 0x3BBD0001
		opword 0x3B9C006C
		opword 0x800100A8
		opword 0x7C1D0000
		opword 0x4180F420
		opword 0xB9C100B8
		opword 0x80010104
		opword 0x7C0803A6
		opword 0x38210100
	}
}
#pragma pop
#endif

// dispProc

void materialProc(s32 shapeId, s32 xluStage);
void vivihimo(Mtx a, Mtx b, f32 speed, f32 scale, f32 offA, f32 offB);

#ifdef NONMATCHING
void dispProc(s32 parentId, s32 groupId, s32 xluStage, s32 arg3, f32 arg4) {
    AnimPoseGroup* group;
    AnimPoseGroup* parent;
    AnimPoseNode* node;
    AnimationPose* pose;
    AnimationPoseData* data;
    f32 sx, sy, sz;

    if (groupId == -1) {
        return;
    }
    pose = wp->mpCurPose;
    data = wp->mpCurPoseData;
    group = &data->groups[groupId];
    if (*(s8*)&pose->mpGroupVisibility[group->visibilityId]) {
        pose = wp->mpCurPose;
        node = (AnimPoseNode*)((u32*)pose->mpNodes + group->nodeId);
        if (group->useSSC) {
            if (parentId == -1) {
                sx = sy = sz = 1.0f;
            }
            else {
                parent = &data->groups[parentId];
                if (!parent->useSSC) {
                    sx = sy = sz = 1.0f;
                }
                else {
                    AnimPoseNode* pnode = (AnimPoseNode*)((u32*)pose->mpNodes + parent->nodeId);
                    sx = pnode->mScale.x;
                    sy = pnode->mScale.y;
                    sz = pnode->mScale.z;
                }
            }
            pushGXModelMtx_JointNode__(node, sx, sy, sz);
        }
        else {
            pushGXModelMtx_TransformNode__(node);
        }
        if (wp->mpCurPose->flags & 0x40) {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = (*g_modeling_mtx)[0][3];
            pos.y = (*g_modeling_mtx)[1][3];
            pos.z = (*g_modeling_mtx)[2][3];
            (*wp->mpCurPose->worldPositions)[groupId] = pos;
        }
        if (wp->mpCurPose->flags & 0x80) {
            PSMTXCopy(*g_modeling_mtx, (*wp->mpCurPose->worldMatrices)[groupId]);
        }
        pose = wp->mpCurPose;
        if (pose->flags & 0x20 && groupId == pose->vivianGroupNo[0]) {
            Mtx* m;
            MtxPtr mat;
            f32* speed;
            f32 offA, offB;
            int i, j;
            s32 type;

            offB = offA = EXT_LIT(float_0_80419a48, 0.0f);
            type = pose->vivianType;
            speed = (f32*)vivihimoData[type] + pose->animId * 2;
            m = g_modeling_mtx;
            mat = pose->matrix;
            switch (type) {
                case 1:
                    offA = EXT_LIT(float_neg2_80419ab8, -2.0f);
                    offB = EXT_LIT(float_0p5_80419a64, 0.5f);
                    break;
                case 2:
                    offA = EXT_LIT(float_neg3_80419abc, -3.0f);
                    offB = EXT_LIT(float_0p5_80419a64, 0.5f);
                    break;
                case 3:
                    offA = EXT_LIT(float_neg1_80419a8c, -1.0f);
                    offB = EXT_LIT(float_0p5_80419a64, 0.5f);
                    break;
            }
            materialProc(group->shapeId, xluStage);
            vivihimo(*m, mat, speed[0], speed[1], offA, offB);
            wp->mpCurPose->flags &= ~0x20;
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    mat[i][j] += 0.04f * ((*m)[i][j] - mat[i][j]);
                }
            }
        }
        else {
            if (pose->dispCallback) {
                ((void (*)(void*, s32, Mtx*))pose->dispCallback)(pose->dispUserDataCallback, groupId, g_modeling_mtx);
            }
            renderProc(group->shapeId, xluStage);
            dispProc(groupId, group->childGroupId, xluStage, arg3, arg4);
        }
        g_modeling_mtx_lv--;
        g_modeling_mtx = &g_modeling_mtx_stack[g_modeling_mtx_lv];
    }
    dispProc(groupId, group->brotherGroupId, xluStage, arg3, arg4);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void dispProc(s32 parentId, s32 groupId, s32 xluStage, s32 arg3, f32 arg4) {
	char _af_pad[20];
	asm volatile {
		opword 0x7C9C2378
		opword 0xFFE00890
		opword 0x2C1CFFFF
		opword 0x7CBD2B78
		opword 0x7CDE3378
		opword 0x41820360
		lwz r5, wp(r13)
		opword 0x1C1C0058
		opword 0x80850020
		opword 0x80A50018
		opword 0x80C401A8
		opword 0x8085005C
		opword 0x7FE60214
		opword 0x801F004C
		opword 0x7C0400AE
		opword 0x7C000775
		opword 0x4182031C
		opword 0x801F0054
		opword 0x809F0050
		opword 0x2C000000
		opword 0x80A50064
		opword 0x5480103A
		opword 0x7C850214
		opword 0x41820064
		opword 0x2C03FFFF
		opword 0x40820014
		lfs f3, float_1_80419a44(r2)
		opword 0xFC401890
		opword 0xFC201890
		opword 0x48000040
		opword 0x1C030058
		opword 0x7C660214
		opword 0x80030054
		opword 0x2C000000
		opword 0x40820014
		lfs f3, float_1_80419a44(r2)
		opword 0xFC401890
		opword 0xFC201890
		opword 0x4800001C
		opword 0x80030050
		opword 0x5400103A
		opword 0x7C650214
		opword 0xC023000C
		opword 0xC0430010
		opword 0xC0630014
		opword 0x7C832378
		bl pushGXModelMtx_JointNode__
		opword 0x4800000C
		opword 0x7C832378
		bl pushGXModelMtx_TransformNode__
		lwz r3, wp(r13)
		opword 0x80830018
		opword 0x80040000
		opword 0x54000673
		opword 0x41820068
		lis r3, vec3_802c2dc8@ha
		lwz r7, g_modeling_mtx(r13)
		addi r6, r3, vec3_802c2dc8@l
		opword 0x8064015C
		opword 0x80A60000
		opword 0x1C1C000C
		opword 0x80860004
		stw r5, _af_pad+0(r1)
		opword 0xC007000C
		opword 0x80A60008
		opword 0xD0010008
		opword 0x80630000
		opword 0x9081000C
		opword 0xC027001C
		opword 0x7C830214
		opword 0x90A10010
		opword 0xC007002C
		opword 0xD021000C
		opword 0x80010008
		opword 0xD0010010
		opword 0x8061000C
		opword 0x90040000
		opword 0x80010010
		opword 0x90640004
		opword 0x90040008
		lwz r3, wp(r13)
		opword 0x80630018
		opword 0x80030000
		opword 0x54000631
		opword 0x4182001C
		opword 0x80830164
		opword 0x1C1C0030
		lwz r3, g_modeling_mtx(r13)
		opword 0x80840000
		opword 0x7C840214
		bl PSMTXCopy
		lwz r3, wp(r13)
		opword 0x80A30018
		opword 0x80050000
		opword 0x540006B5
		opword 0x4182017C
		opword 0x80650120
		opword 0x80030000
		opword 0x7C1C0000
		opword 0x4082016C
		opword 0x80C5011C
		la r3, vivihimoData(r13)
		lfs f30, float_0_80419a48(r2)
		opword 0x3B450124
		opword 0x54C4103A
		opword 0x80050014
		opword 0xFFA0F090
		opword 0x2C060002
		opword 0x7C63202E
		opword 0x54001838
		lwz r27, g_modeling_mtx(r13)
		add r25, r3, r0
		opword 0x4182002C
		opword 0x40800010
		opword 0x2C060001
		opword 0x40800014
		opword 0x48000030
		opword 0x2C060004
		opword 0x40800028
		opword 0x4800001C
		lfs f30, float_neg2_80419ab8(r2)
		lfs f29, float_0p5_80419a64(r2)
		opword 0x48000018
		lfs f30, float_neg3_80419abc(r2)
		lfs f29, float_0p5_80419a64(r2)
		opword 0x4800000C
		lfs f30, float_neg1_80419a8c(r2)
		lfs f29, float_0p5_80419a64(r2)
		opword 0x807F0048
		opword 0x7FA4EB78
		bl materialProc
		opword 0xFC60F090
		opword 0xC0390000
		opword 0xFC80E890
		opword 0xC0590004
		opword 0x7F63DB78
		opword 0x7F44D378
		bl vivihimo
		lwz r3, wp(r13)
		lfs f2, float_0p04_80419ac0(r2)
		opword 0x80630018
		opword 0x80030000
		opword 0x540006F2
		opword 0x90030000
		opword 0xC01B0000
		opword 0xC03A0000
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01A0000
		opword 0xC01B0004
		opword 0xC03A0004
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01A0004
		opword 0xC01B0008
		opword 0xC03A0008
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01A0008
		opword 0xC01B0010
		opword 0xC03A0010
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01A0010
		opword 0xC01B0014
		opword 0xC03A0014
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01A0014
		opword 0xC01B0018
		opword 0xC03A0018
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01A0018
		opword 0xC01B0020
		opword 0xC03A0020
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01A0020
		opword 0xC01B0024
		opword 0xC03A0024
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01A0024
		opword 0xC01B0028
		opword 0xC03A0028
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01A0028
		opword 0x48000048
		opword 0x81850154
		opword 0x280C0000
		opword 0x41820018
		opword 0x80650158
		opword 0x7F84E378
		lwz r5, g_modeling_mtx(r13)
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x807F0048
		opword 0x7FA4EB78
		bl renderProc
		opword 0xFC20F890
		opword 0x809F0044
		opword 0x7F83E378
		opword 0x7FA5EB78
		opword 0x7FC6F378
		bl dispProc
		lwz r4, g_modeling_mtx_lv(r13)
		lis r3, g_modeling_mtx_stack@ha
		addi r0, r3, g_modeling_mtx_stack@l
		opword 0x3884FFFF
		opword 0x1C640030
		stw r4, g_modeling_mtx_lv(r13)
		opword 0x7C001A14
		stw r0, g_modeling_mtx(r13)
		opword 0xFC20F890
		opword 0x809F0040
		opword 0x7F83E378
		opword 0x7FA5EB78
		opword 0x7FC6F378
		bl dispProc
	}
}
#pragma pop
#endif


void animPoseDraw(s32 poseId, f32 x, f32 y, f32 z, f32 rotY, f32 scale, s32 xluMode) {
    Mtx matrix;

    MTXTrans(matrix, x, y, z);
    animPoseDrawMtx(poseId, matrix, xluMode, rotY, scale);
}

// _animPoseDrawMtx
extern BOOL mapTestXLU(u32 flags, GXColor* color, GXColor* matColor);
extern double atan2(double y, double x);
void animPoseMainSub(AnimationPose* pose);

#ifdef NONMATCHING
static inline f32 _animClampAngle(f32 a) {
    while (a < -360.0f) a += 360.0f;
    while (a >= EXT_LIT(float_360_80419a98, 360.0f)) a -= EXT_LIT(float_360_80419a98, 360.0f);
    if (a < EXT_LIT(float_0_80419a48, 0.0f)) a += EXT_LIT(float_360_80419a98, 360.0f);
    return a;
}
#endif

#ifdef NONMATCHING
static inline f32 _animClampAngle2(f32 a) {
    while (a < -360.0f) a += 360.0f;
    while (a >= EXT_LIT(float_360_80419a98, 360.0f)) a -= EXT_LIT(float_360_80419a98, 360.0f);
    return a;
}
#endif

#ifdef NONMATCHING
static inline f32 _animCamAngle(void) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    return _animClampAngle(EXT_LIT(float_rad2deg_80419a94, 57.29579f) * (f32)atan2(-(cam->cameraAt.x - cam->cameraPos.x), -(cam->cameraAt.z - cam->cameraPos.z)));
}
#endif

#ifdef NONMATCHING
void _animPoseDrawMtx(AnimationPose* pose, Mtx matrix, s32 xluMode, f32 rotY, f32 scale) {
    Mtx result;
    Mtx tmp2;
    Mtx tmp1;
    Mtx tmp3;
    GXColor col1;
    GXColor col2;
    AnimationPoseData* data;
    AnimData* anim;
    s32 arg3, arg4;
    f32 argf;
    f32 diff;
    s32 mode;

    data = animPoseGetBaseData(pose);
    arg3 = *(s32*)((u8*)pose + 0x28);
    arg4 = *(s32*)((u8*)pose + 0x2C);
    argf = *(f32*)((u8*)pose + 0x30);
    anim = data->mpAnims[pose->animId].data;
    if (anim == NULL) {
        return;
    }
    if (wp->inBattle && pose->type == 0) {
        return;
    }
    if (!wp->inBattle && pose->type == 1) {
        return;
    }
    if (!(xluMode == 2 && (data->flags & 1)) && !(data->flags & (1 << xluMode))) {
        return;
    }
    mode = xluMode;
    col2 = pose->materialColor2;
    col1 = pose->materialColor;
    if (mapTestXLU(pose->materialFlag, &col1, &col2)) {
        mode = 3;
    }
    if (pose->gxCallback != NULL) {
        pose->gxCallback(mode);
    }
    else {
        switch (mode) {
            case 1:
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
                GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                GXSetZCompLoc(GX_TRUE);
                GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
                break;
            case 0:
            case 2:
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
                GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                GXSetZCompLoc(GX_FALSE);
                GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
                break;
            case 3:
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                GXSetZCompLoc(GX_TRUE);
                GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
                break;
        }
        wp->currDispMode = mode;
    }
    if (pose->flags & 8) {
        rotY += -90.0f;
        pose->peraRotY = rotY;
        diff = _animClampAngle2(_animCamAngle() - pose->peraRotY);
        if ((diff > EXT_LIT(float_90_80419aa0, 90.0f) && diff <= EXT_LIT(float_270_80419aa4, 270.0f)) || (diff < EXT_LIT(float_neg90_80419a90, -90.0f) && diff >= EXT_LIT(float_neg270_80419aa8, -270.0f))) {
            pose->peraTargetRotY = _animClampAngle2(180.0f + _animCamAngle());
        }
        else {
            pose->peraTargetRotY = _animCamAngle();
        }
        while (pose->peraTargetRotY - pose->rotationY > EXT_LIT(float_180_80419aac, 180.0f)) {
            pose->rotationY += 360.0f;
        }
        while (pose->peraTargetRotY - pose->rotationY < EXT_LIT(float_neg180_80419ab0, -180.0f)) {
            pose->rotationY -= 360.0f;
        }
        if (pose->flags & 0x100) {
            pose->rotationY = pose->peraTargetRotY;
        }
        else {
            pose->rotationY += 0.1f * (pose->peraTargetRotY - pose->rotationY);
        }
        rotY = pose->rotationY;
        if (rotY != EXT_LIT(float_0_80419a48, 0.0f)) {
            PSMTXRotRad(tmp2, 'y', 0.017453292f * rotY);
            PSMTXConcat(matrix, tmp2, result);
            matrix = result;
        }
        if (pose->field_0x78 == EXT_LIT(float_neg1_80419a8c, -1.0f)) {
            PSMTXScale(tmp2, 1.0f, 1.0f, -1.0f);
            PSMTXConcat(matrix, tmp2, result);
            matrix = result;
        }
    }
    else if (rotY) {
        PSMTXRotRad(tmp1, 'y', 0.017453292f * rotY);
        PSMTXConcat(matrix, tmp1, result);
        matrix = result;
    }
    if (scale != EXT_LIT(float_1_80419a44, 1.0f)) {
        PSMTXScale(tmp3, scale, scale, scale);
        PSMTXConcat(matrix, tmp3, result);
        matrix = result;
    }
    if (pose->lastFrameZero == -1) {
        animPoseMainSub(pose);
    }
    g_modeling_mtx_lv = 0;
    g_modeling_mtx = &g_modeling_mtx_stack[0];
    PSMTXCopy(matrix, *g_modeling_mtx);
    wp->mpCurPose = pose;
    wp->mpCurAnimData = anim;
    wp->mpCurPoseData = data;
    if ((s32)wp->mbUseFloatScratch != 0) {
        DCFlushRange(wp->vtxArrayPos, animPoseGetBaseData(pose)->mBufferPosNum * sizeof(Vec));
        DCFlushRange(wp->vtxArrayNrm, animPoseGetBaseData(pose)->mBufferNrmNum * sizeof(Vec));
    }
    else {
        DCFlushRange(pose->mpVtxArrayPos, animPoseGetBaseData(pose)->mBufferPosNum * sizeof(Vec));
        DCFlushRange(pose->mpVtxArrayNrm, animPoseGetBaseData(pose)->mBufferNrmNum * sizeof(Vec));
    }
    GXInvalidateVtxCache();
    dispProc(-1, data->groupCount - 1, arg3, arg4, argf);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void _animPoseDrawMtx(AnimationPose* pose, Mtx matrix, s32 xluMode, f32 rotY, f32 scale) {
	asm volatile {
		opword 0x9421FEE0
		opword 0x7C0802A6
		opword 0x90010124
		opword 0xDBE10110
		opword 0xF3E10118
		opword 0xDBC10100
		opword 0xF3C10108
		opword 0xDBA100F0
		opword 0xF3A100F8
		opword 0xBF2100D4
		lwz r7, wp(r13)
		opword 0x7C7A1B78
		opword 0x80030010
		opword 0xFFA00890
		opword 0x80C70000
		opword 0xFFC01090
		opword 0x54032036
		opword 0x801A0014
		opword 0x7C661A14
		opword 0x80630008
		opword 0x54003032
		opword 0x83BA0028
		opword 0x7C9B2378
		opword 0x806300A0
		opword 0x839A002C
		opword 0x83E30000
		opword 0xC3FA0030
		opword 0x807F01AC
		opword 0x7C630214
		opword 0x83C3003C
		opword 0x281E0000
		opword 0x41820740
		opword 0x8067010C
		opword 0x2C030000
		opword 0x41820010
		opword 0x801A000C
		opword 0x2C000000
		opword 0x41820728
		opword 0x2C030000
		opword 0x40820010
		opword 0x801A000C
		opword 0x2C000001
		opword 0x41820714
		opword 0x2C050002
		opword 0x40820010
		opword 0x801F00C4
		opword 0x540007FF
		opword 0x40820018
		opword 0x38000001
		opword 0x807F00C4
		opword 0x7C002830
		opword 0x7C600039
		opword 0x418206EC
		opword 0x801A00F4
		opword 0x7CB92B78
		opword 0x3881000C
		opword 0x38A10008
		opword 0x90010008
		opword 0x801A00F0
		opword 0x9001000C
		opword 0x807A00E8
		bl mapTestXLU
		opword 0x2C030000
		opword 0x41820008
		opword 0x3B200003
		opword 0x819A00E0
		opword 0x280C0000
		opword 0x41820014
		opword 0x7F23CB78
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x48000108
		opword 0x2C190002
		opword 0x4182006C
		opword 0x40800014
		opword 0x2C190000
		opword 0x41820060
		opword 0x40800014
		opword 0x480000E4
		opword 0x2C190004
		opword 0x408000DC
		opword 0x48000094
		opword 0x38600001
		opword 0x38800003
		opword 0x38A00001
		bl GXSetZMode
		opword 0x38600000
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
		opword 0x48000090
		opword 0x38600001
		opword 0x38800003
		opword 0x38A00001
		bl GXSetZMode
		opword 0x38600000
		opword 0x38800004
		opword 0x38A00005
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
		opword 0x48000048
		opword 0x38600001
		opword 0x38800003
		opword 0x38A00000
		bl GXSetZMode
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
		lwz r3, wp(r13)
		opword 0x932300E0
		opword 0x801A0000
		opword 0x54000739
		opword 0x41820314
		lfs f0, float_neg90_80419a90(r2)
		opword 0x38600004
		opword 0xEFBD002A
		opword 0xD3BA0070
		bl camGetPtr
		opword 0xC0630018
		opword 0xC043000C
		opword 0xC0230020
		opword 0xC0030014
		opword 0xEC431028
		opword 0xEC010028
		opword 0xFC201050
		opword 0xFC400050
		bl atan2
		opword 0xFC600818
		lfs f2, float_rad2deg_80419a94(r2)
		lfs f1, float_360_80419a98(r2)
		lfs f0, float_neg360_80419a9c(r2)
		opword 0xEC4200F2
		opword 0x48000008
		opword 0xEC42082A
		opword 0xFC020040
		opword 0x4180FFF8
		lfs f1, float_360_80419a98(r2)
		opword 0x48000008
		opword 0xEC420828
		opword 0xFC020840
		opword 0x4C411382
		opword 0x4182FFF4
		lfs f0, float_0_80419a48(r2)
		opword 0xFC020040
		opword 0x40800008
		opword 0xEC42082A
		opword 0xC01A0070
		lfs f1, float_360_80419a98(r2)
		opword 0xEC420028
		lfs f0, float_neg360_80419a9c(r2)
		opword 0x48000008
		opword 0xEC42082A
		opword 0xFC020040
		opword 0x4180FFF8
		lfs f0, float_360_80419a98(r2)
		opword 0x48000008
		opword 0xEC420028
		opword 0xFC020040
		opword 0x4C411382
		opword 0x4182FFF4
		lfs f0, float_90_80419aa0(r2)
		opword 0xFC020040
		opword 0x40810014
		lfs f0, float_270_80419aa4(r2)
		opword 0xFC020040
		opword 0x4C401382
		opword 0x41820020
		lfs f0, float_neg90_80419a90(r2)
		opword 0xFC020040
		opword 0x408000CC
		lfs f0, float_neg270_80419aa8(r2)
		opword 0xFC020040
		opword 0x4C411382
		opword 0x408200BC
		opword 0x38600004
		bl camGetPtr
		opword 0xC0630018
		opword 0xC043000C
		opword 0xC0230020
		opword 0xC0030014
		opword 0xEC431028
		opword 0xEC010028
		opword 0xFC201050
		opword 0xFC400050
		bl atan2
		opword 0xFC600818
		lfs f2, float_rad2deg_80419a94(r2)
		lfs f1, float_360_80419a98(r2)
		lfs f0, float_neg360_80419a9c(r2)
		opword 0xEC4200F2
		opword 0x48000008
		opword 0xEC42082A
		opword 0xFC020040
		opword 0x4180FFF8
		lfs f1, float_360_80419a98(r2)
		opword 0x48000008
		opword 0xEC420828
		opword 0xFC020840
		opword 0x4C411382
		opword 0x4182FFF4
		lfs f0, float_0_80419a48(r2)
		opword 0xFC020040
		opword 0x40800008
		opword 0xEC42082A
		lfs f0, float_180_80419aac(r2)
		lfs f1, float_360_80419a98(r2)
		opword 0xEC40102A
		lfs f0, float_neg360_80419a9c(r2)
		opword 0x48000008
		opword 0xEC42082A
		opword 0xFC020040
		opword 0x4180FFF8
		lfs f0, float_360_80419a98(r2)
		opword 0x48000008
		opword 0xEC420028
		opword 0xFC020040
		opword 0x4C411382
		opword 0x4182FFF4
		opword 0xD05A007C
		opword 0x48000080
		opword 0x38600004
		bl camGetPtr
		opword 0xC0630018
		opword 0xC043000C
		opword 0xC0230020
		opword 0xC0030014
		opword 0xEC431028
		opword 0xEC010028
		opword 0xFC201050
		opword 0xFC400050
		bl atan2
		opword 0xFC600818
		lfs f2, float_rad2deg_80419a94(r2)
		lfs f1, float_360_80419a98(r2)
		lfs f0, float_neg360_80419a9c(r2)
		opword 0xEC4200F2
		opword 0x48000008
		opword 0xEC42082A
		opword 0xFC020040
		opword 0x4180FFF8
		lfs f1, float_360_80419a98(r2)
		opword 0x48000008
		opword 0xEC420828
		opword 0xFC020840
		opword 0x4C411382
		opword 0x4182FFF4
		lfs f0, float_0_80419a48(r2)
		opword 0xFC020040
		opword 0x40800008
		opword 0xEC42082A
		opword 0xD05A007C
		lfs f3, float_360_80419a98(r2)
		lfs f0, float_180_80419aac(r2)
		opword 0x48000010
		opword 0xC03A0074
		opword 0xEC21182A
		opword 0xD03A0074
		opword 0xC05A007C
		opword 0xC03A0074
		opword 0xEC220828
		opword 0xFC010040
		opword 0x4181FFE4
		lfs f2, float_360_80419a98(r2)
		lfs f0, float_neg180_80419ab0(r2)
		opword 0x48000010
		opword 0xC03A0074
		opword 0xEC211028
		opword 0xD03A0074
		opword 0xC07A007C
		opword 0xC03A0074
		opword 0xEC830828
		opword 0xFC040040
		opword 0x4180FFE4
		opword 0x801A0000
		opword 0x540005EF
		opword 0x4182000C
		opword 0xD07A0074
		opword 0x48000010
		lfs f0, float_0p1_80419ab4(r2)
		opword 0xEC00093A
		opword 0xD01A0074
		opword 0xC3BA0074
		lfs f0, float_0_80419a48(r2)
		opword 0xFC00E800
		opword 0x4182002C
		lfs f0, float_deg2rad_80419a4c(r2)
		opword 0x38610070
		opword 0x38800079
		opword 0xEC200772
		bl PSMTXRotRad
		opword 0x7F63DB78
		opword 0x38810070
		opword 0x38A100A0
		bl PSMTXConcat
		opword 0x3B6100A0
		lfs f3, float_neg1_80419a8c(r2)
		opword 0xC01A0078
		opword 0xFC030000
		opword 0x40820060
		lfs f1, float_1_80419a44(r2)
		opword 0x38610070
		opword 0xFC400890
		bl PSMTXScale
		opword 0x7F63DB78
		opword 0x38810070
		opword 0x38A100A0
		bl PSMTXConcat
		opword 0x3B6100A0
		opword 0x48000038
		lfs f0, float_0_80419a48(r2)
		opword 0xFC1D0000
		opword 0x4182002C
		lfs f0, float_deg2rad_80419a4c(r2)
		opword 0x38610040
		opword 0x38800079
		opword 0xEC200772
		bl PSMTXRotRad
		opword 0x7F63DB78
		opword 0x38810040
		opword 0x38A100A0
		bl PSMTXConcat
		opword 0x3B6100A0
		lfs f0, float_1_80419a44(r2)
		opword 0xFC00F000
		opword 0x4182002C
		opword 0xFC20F090
		opword 0x38610010
		opword 0xFC40F090
		opword 0xFC60F090
		bl PSMTXScale
		opword 0x7F63DB78
		opword 0x38810010
		opword 0x38A100A0
		bl PSMTXConcat
		opword 0x3B6100A0
		opword 0x801A003C
		opword 0x2C00FFFF
		opword 0x408200EC
		lwz r7, wp(r13)
		opword 0x3C60B216
		opword 0x388342C9
		opword 0x801A0004
		opword 0x80670010
		opword 0x540007BD
		opword 0x7C63D050
		opword 0x7C641816
		opword 0x5463C23E
		opword 0x418200C0
		opword 0x801A0010
		opword 0x80870000
		opword 0x54002036
		opword 0x810700F0
		opword 0x7C840214
		opword 0x80840008
		opword 0x808400A0
		opword 0x80840000
		opword 0x80C400F0
		opword 0x80A400F8
		opword 0x7C862A14
		opword 0x7C044000
		opword 0x41810078
		opword 0x800700F4
		opword 0x7C002214
		opword 0x7C004000
		opword 0x4081000C
		opword 0x38000000
		opword 0x900700F4
		lwz r4, wp(r13)
		opword 0x38000001
		opword 0x900400E8
		lwz r7, wp(r13)
		opword 0x800700F4
		opword 0x808700EC
		opword 0x1C00000C
		opword 0x7C040214
		opword 0x900700F8
		lwz r4, wp(r13)
		opword 0x800400F4
		opword 0x7C003214
		opword 0x900400F4
		lwz r6, wp(r13)
		opword 0x800600F4
		opword 0x808600EC
		opword 0x1C00000C
		opword 0x7C040214
		opword 0x900600FC
		lwz r4, wp(r13)
		opword 0x800400F4
		opword 0x7C002A14
		opword 0x900400F4
		bl animPoseMain
		lwz r3, wp(r13)
		opword 0x38000000
		opword 0x900300E8
		opword 0x48000008
		bl animPoseMain
		lis r3, g_modeling_mtx_stack@ha
		opword 0x38000000
		addi r4, r3, g_modeling_mtx_stack@l
		stw r0, g_modeling_mtx_lv(r13)
		opword 0x7F63DB78
		stw r4, g_modeling_mtx(r13)
		bl PSMTXCopy
		lwz r3, wp(r13)
		opword 0x93430018
		lwz r3, wp(r13)
		opword 0x93C3001C
		lwz r3, wp(r13)
		opword 0x93E30020
		lwz r3, wp(r13)
		opword 0x800300E8
		opword 0x2C000000
		opword 0x41820064
		opword 0x801A0010
		opword 0x80830000
		opword 0x54002036
		opword 0x806300F8
		opword 0x7C840214
		opword 0x80840008
		opword 0x808400A0
		opword 0x80840000
		opword 0x800400F0
		opword 0x1C80000C
		bl DCFlushRange
		lwz r3, wp(r13)
		opword 0x801A0010
		opword 0x80830000
		opword 0x54002036
		opword 0x806300FC
		opword 0x7C840214
		opword 0x80840008
		opword 0x808400A0
		opword 0x80840000
		opword 0x800400F8
		opword 0x1C80000C
		bl DCFlushRange
		opword 0x48000060
		opword 0x801A0010
		opword 0x80830000
		opword 0x54002036
		opword 0x807A004C
		opword 0x7C840214
		opword 0x80840008
		opword 0x808400A0
		opword 0x80840000
		opword 0x800400F0
		opword 0x1C80000C
		bl DCFlushRange
		lwz r3, wp(r13)
		opword 0x801A0010
		opword 0x80830000
		opword 0x54002036
		opword 0x807A0054
		opword 0x7C840214
		opword 0x80840008
		opword 0x808400A0
		opword 0x80840000
		opword 0x800400F8
		opword 0x1C80000C
		bl DCFlushRange
		bl GXInvalidateVtxCache
		opword 0x807F0144
		opword 0xFC20F890
		opword 0x7FA5EB78
		opword 0x7F86E378
		opword 0x3883FFFF
		opword 0x3860FFFF
		bl dispProc
		opword 0xE3E10118
		opword 0xCBE10110
		opword 0xE3C10108
		opword 0xCBC10100
		opword 0xE3A100F8
		opword 0xCBA100F0
		opword 0xBB2100D4
		opword 0x80010124
		opword 0x7C0803A6
		opword 0x38210120
	}
}
#pragma pop
#endif



#define PDM_F(p, off) (*(f32*)((u8*)(p) + (off)))

#ifdef NONMATCHING
inline void animSetPaperMtx(Mtx m0, Mtx* m1, Mtx* m2) {
    if (m0 == NULL) {
        wp->paperMtxPtr[0] = NULL;
    }
    else {
        PSMTXCopy(m0, wp->paperMtx[0]);
        wp->paperMtxPtr[0] = &wp->paperMtx[0];
    }
    wp->paperMtxPtr[1] = m1;
    wp->paperMtxPtr[2] = m2;
}
#endif

#ifdef NONMATCHING
void animPoseDrawMtx(s32 poseId, Mtx matrix, s32 xluMode, f32 rotY, f32 scale)
{
  Mtx m1;
  static Mtx mtx;
  Mtx m2;
  Mtx scl;
  Mtx rot;
  Mtx tmp;
  AnimationPose *pose;
  AnimationPose *paper;
  AnimationPose *p2;
  AnimationPoseData *data;
  const char *name;
  s32 animId;
  s32 new_var[2];
  pose = &wp->poses[poseId];
  if (pose->paperId != (-1))
  {
    if (pose->flags & 0xC0)
    {
      Mtx *m;
      data = *((AnimationPoseData **) wp->files[pose->fileId].handle->data);
      m = (Mtx *) matrix;
      if ((!(pose->flags & 8)) && rotY)
      {
        PSMTXRotRad(rot, 'y', 0.017453292f * rotY);
        PSMTXConcat(matrix, rot, tmp);
        m = &tmp;
      }
      if (EXT_LIT(float_1_80419a44, 1.0f) != scale)
      {
        PSMTXScale(scl, scale, scale, scale);
        PSMTXConcat(*m, scl, tmp);
        m = &tmp;
      }
      g_modeling_mtx_lv = 0;
      g_modeling_mtx = &g_modeling_mtx_stack[0];
      PSMTXCopy(*m, *g_modeling_mtx);
      wp->mpCurPose = pose;
      wp->mpCurPoseData = data;
      evalProc(-1, data->groupCount - 1);
    }
    paper = &wp->poses[pose->paperId];
    data = *((AnimationPoseData **) wp->files[paper->fileId].handle->data);
    if (((xluMode != 2) || (!(data->flags & 1))) && (!(data->flags & (1 << xluMode))))
    {
      return;
    }
    if (paper->typeFlags & 2)
    {
      new_var[1] = data->mBufferPosNum;
      new_var[0] = data->mBufferNrmNum;
      if ((new_var[1] + new_var[0]) <= wp->mFloatScratchRP)
      {
        if ((wp->mFloatScratchWP + (new_var[1] + new_var[0])) > wp->mFloatScratchRP)
        {
          wp->mFloatScratchWP = 0;
        }
        wp->mbUseFloatScratch = 1;
        wp->vtxArrayPos = &wp->mpFloatScratch[wp->mFloatScratchWP];
        wp->mFloatScratchWP += new_var[1];
        wp->vtxArrayNrm = &wp->mpFloatScratch[wp->mFloatScratchWP];
        wp->mFloatScratchWP += new_var[0];
      }
      name = (const char *) (*((s32 *) pose->field_0x94));
      if (name != ((const char *) (-1)))
      {
        p2 = &wp->poses[pose->paperId];
        animId = animPoseGetAnimIdx(*((AnimationPoseData **) wp->files[p2->fileId].handle->data), name);
        if (animId != p2->animId)
        {
          p2->animId = animId;
          if ((p2->paperId != (-1)) && (p2->flags & 2))
          {
            p2->flags |= 4;
          }
          p2->localTime = animTimeGetTime(p2->type);
          p2->lastFrameZero = -1;
          p2->lastFrameTime = EXT_LIT(float_0_80419a48, 0.0f);
          p2->field_0x80 = 0;
          p2->loopTime = EXT_LIT(float_0_80419a48, 0.0f);
        }
      }
      paper->localTime = animTimeGetTime(paper->type);
      paper->lastFrameZero = -1;
      paper->lastFrameTime = EXT_LIT(float_0_80419a48, 0.0f);
      paper->field_0x80 = 0;
      paper->loopTime = EXT_LIT(float_0_80419a48, 0.0f);
      paper->localTime = pose->mLocalTimeInit;
      animPoseMain(pose->paperId);
    }
    {
      void *t0 = *((void **) (((u8 *) pose) + 0x98));
      void *t1 = *((void **) (((u8 *) pose) + 0x9C));
      wp->mpTexObjs[0] = (t0) ? ((GXTexObj *) (((u8 *) pose) + 0xA0)) : ((void *) 0);
      wp->mpTexObjs[1] = (t1) ? ((GXTexObj *) (((u8 *) pose) + 0xC0)) : ((void *) 0);
      wp->mpCurTexObj = (void *) 0;
      wp->mpTexDatas[0] = t0;
      wp->mpTexDatas[1] = t1;
      wp->mpCurTexData = (void *) 0;
      wp->field_0xD8 = 1;
      p2->field_0x80 = 0;
      wp->field_0xDC = 1;
    }
    paper->materialFlag = pose->materialFlag;
    paper->materialLightFlag = pose->materialLightFlag;
    paper->materialColor = pose->materialColor;
    paper->materialColor2 = pose->materialColor2;
    if (pose->flags & 2)
    {
      PSMTXScale(m1, *((f32 *) (((u8 *) pose) + 0x10C)), *((f32 *) (((u8 *) pose) + 0x110)), 1.0f);
      PSMTXTrans(m2, *((f32 *) (0x104 + ((u8 *) pose))), *((f32 *) (((u8 *) pose) + 0x108)), EXT_LIT(float_0_80419a48, 0.0f));
      PSMTXConcat(m1, m2, m1);
      animSetPaperMtx(m1, (void *) 0, (void *) 0);
      PSMTXScale(m1, pose->paperScaleXZ, pose->paperScaleY, pose->paperScaleXZ);
      if (wp->inBattle)
      {
        PSMTXTrans(m2, 0.0f, 2.0f * pose->paperOfsY, 0.0f);
      }
      else
      {
        PSMTXTrans(m2, 0.0f, pose->paperOfsY, 0.0f);
      }
      PSMTXConcat(m2, m1, m1);
      PSMTXConcat(matrix, m1, mtx);
      matrix = mtx;
    }
    else
    {
      PSMTXScale(m1, *((f32 *) (((u8 *) pose) + 0x10C)), *((f32 *) (((u8 *) pose) + 0x110)), 1.0f);
      PSMTXTrans(m2, *((f32 *) (((u8 *) pose) + 0x104)), *((f32 *) (((u8 *) pose) + 0x108)), EXT_LIT(float_0_80419a48, 0.0f));
      PSMTXConcat(m1, m2, m1);
      PSMTXTrans(m2, EXT_LIT(float_0p5_80419a64, 0.5f), EXT_LIT(float_1_80419a44, 1.0f), EXT_LIT(float_0_80419a48, 0.0f));
      PSMTXConcat(m1, m2, m1);
      PSMTXScale(m2, EXT_LIT(float_1_80419a44, 1.0f) / pose->paperScaleXZ, EXT_LIT(float_1_80419a44, 1.0f) / pose->paperScaleY, EXT_LIT(float_1_80419a44, 1.0f));
      PSMTXConcat(m1, m2, m1);
      PSMTXTrans(m2, EXT_LIT(float_neg0p5_80419a88, -0.5f), EXT_LIT(float_neg1_80419a8c, -1.0f), EXT_LIT(float_0_80419a48, 0.0f));
      PSMTXConcat(m1, m2, m1);
      animSetPaperMtx(m1, (void *) 0, (void *) 0);
    }
  }
  else
  {
    data = *((AnimationPoseData **) wp->files[pose->fileId].handle->data);
    if (((xluMode != 2) || (!(data->flags & 1))) && (!(data->flags & (1 << xluMode))))
    {
      return;
    }
  }
  if (pose->paperId != (-1))
  {
    _animPoseDrawMtx(paper, matrix, xluMode, rotY, scale);
    wp->paperMtxPtr[0] = (void *) 0;
    wp->paperMtxPtr[1] = (void *) 0;
    wp->paperMtxPtr[2] = (void *) 0;
    if (paper->typeFlags & 2)
    {
      wp->mbUseFloatScratch = 0;
    }
  }
  else
  {
    _animPoseDrawMtx(pose, matrix, xluMode, rotY, scale);
  }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void animPoseDrawMtx(s32 poseId, Mtx matrix, s32 xluMode, f32 rotY, f32 scale) {
	char _af_pad[232];
	asm volatile {
		lwz r6, wp(r13)
		opword 0x1C030170
		fmr f30, f1
		opword 0x7C9B2378
		opword 0x80660010
		opword 0xFFE01090
		opword 0x7CBC2B78
		opword 0x7FE30214
		opword 0x801F0090
		opword 0x2C00FFFF
		opword 0x41820670
		opword 0x809F0000
		opword 0x54800633
		opword 0x418200D0
		opword 0x54800739
		opword 0x807F0010
		opword 0x80860000
		opword 0x7F7DDB78
		opword 0x54602036
		opword 0x7C640214
		opword 0x80630008
		opword 0x806300A0
		opword 0x83430000
		opword 0x40820038
		lfs f0, float_0_80419a48(r2)
		opword 0xFC1E0000
		opword 0x4182002C
		lfs f0, float_deg2rad_80419a4c(r2)
		la r3, _af_pad+48
		opword 0x38800079
		opword 0xEC2007B2
		bl PSMTXRotRad
		opword 0x7F63DB78
		opword 0x38810038
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x3BA10008
		lfs f0, float_1_80419a44(r2)
		opword 0xFC00F800
		opword 0x4182002C
		opword 0xFC20F890
		opword 0x38610068
		opword 0xFC40F890
		opword 0xFC60F890
		bl PSMTXScale
		opword 0x7FA3EB78
		opword 0x38810068
		opword 0x38A10008
		bl PSMTXConcat
		opword 0x3BA10008
		lis r3, g_modeling_mtx_stack@ha
		opword 0x38000000
		addi r4, r3, g_modeling_mtx_stack@l
		stw r0, g_modeling_mtx_lv(r13)
		opword 0x7FA3EB78
		stw r4, g_modeling_mtx(r13)
		bl PSMTXCopy
		lwz r4, wp(r13)
		opword 0x3860FFFF
		opword 0x93E40018
		lwz r4, wp(r13)
		opword 0x93440020
		opword 0x809A0144
		opword 0x3884FFFF
		bl evalProc
		opword 0x801F0090
		opword 0x2C1C0002
		lwz r3, wp(r13)
		opword 0x1C000170
		opword 0x80A30010
		opword 0x80830000
		opword 0x7FC50214
		opword 0x801E0010
		opword 0x54002036
		opword 0x7C840214
		opword 0x80840008
		opword 0x808400A0
		opword 0x80A40000
		opword 0x40820010
		opword 0x800500C4
		opword 0x540007FF
		opword 0x40820018
		opword 0x38000001
		opword 0x808500C4
		opword 0x7C00E030
		opword 0x7C800039
		opword 0x418205F4
		opword 0x801E0004
		opword 0x540007BD
		opword 0x41820298
		opword 0x80C500F0
		opword 0x80A500F8
		opword 0x80E300F0
		opword 0x7C862A14
		opword 0x7C043800
		opword 0x41810078
		opword 0x800300F4
		opword 0x7C002214
		opword 0x7C003800
		opword 0x4081000C
		opword 0x38000000
		opword 0x900300F4
		lwz r3, wp(r13)
		opword 0x38000001
		opword 0x900300E8
		lwz r4, wp(r13)
		opword 0x800400F4
		opword 0x806400EC
		opword 0x1C00000C
		opword 0x7C030214
		opword 0x900400F8
		lwz r3, wp(r13)
		opword 0x800300F4
		opword 0x7C003214
		opword 0x900300F4
		lwz r4, wp(r13)
		opword 0x800400F4
		opword 0x806400EC
		opword 0x1C00000C
		opword 0x7C030214
		opword 0x900400FC
		lwz r3, wp(r13)
		opword 0x800300F4
		opword 0x7C002A14
		opword 0x900300F4
		opword 0x835F0094
		opword 0x2C1AFFFF
		opword 0x41820154
		opword 0x801F0090
		opword 0x2C1A0000
		lwz r3, wp(r13)
		opword 0x1C000170
		opword 0x80830010
		opword 0x80630000
		opword 0x7FA40214
		opword 0x801D0010
		opword 0x54002036
		opword 0x7C630214
		opword 0x80630008
		opword 0x806300A0
		opword 0x82E30000
		opword 0x83370148
		opword 0x40800040
		opword 0x3B000000
		mr r22, r24
		opword 0x48000028
		opword 0x801701AC
		opword 0x7F44D378
		opword 0x7C60B214
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x4800002C
		opword 0x3AD60040
		opword 0x3B180001
		opword 0x7C18C800
		opword 0x4180FFD8
		opword 0x48000014
		opword 0x7C1AC800
		opword 0x4080000C
		opword 0x7F58D378
		opword 0x48000008
		opword 0x3B000000
		opword 0x801D0014
		opword 0x7C180000
		opword 0x418200BC
		opword 0x931D0014
		opword 0x801D0090
		opword 0x2C00FFFF
		opword 0x41820018
		opword 0x807D0000
		opword 0x546007BD
		opword 0x4182000C
		opword 0x60600004
		opword 0x901D0000
		opword 0x801D000C
		opword 0x2C000000
		opword 0x40820038
		opword 0x3C608000
		opword 0x3C801062
		opword 0x800300F8
		opword 0x38A44DD3
		lwz r6, gp(r13)
		opword 0x5400F0BE
		opword 0x7C050016
		opword 0x80660040
		opword 0x80860044
		opword 0x38A00000
		opword 0x5406D1BE
		bl __div2i
		opword 0x48000034
		opword 0x3C608000
		opword 0x3C801062
		opword 0x800300F8
		opword 0x38A44DD3
		lwz r6, gp(r13)
		opword 0x5400F0BE
		opword 0x7C050016
		opword 0x80660038
		opword 0x8086003C
		opword 0x38A00000
		opword 0x5406D1BE
		bl __div2i
		opword 0x909D001C
		opword 0x3880FFFF
		lfs f0, float_0_80419a48(r2)
		opword 0x38000000
		opword 0x907D0018
		opword 0x909D003C
		opword 0xD01D0040
		opword 0x901D0080
		opword 0xD01D0084
		opword 0x801E000C
		opword 0x2C000000
		opword 0x40820038
		opword 0x3C608000
		opword 0x3C801062
		opword 0x800300F8
		opword 0x38A44DD3
		lwz r6, gp(r13)
		opword 0x5400F0BE
		opword 0x7C050016
		opword 0x80660040
		opword 0x80860044
		opword 0x38A00000
		opword 0x5406D1BE
		bl __div2i
		opword 0x48000034
		opword 0x3C608000
		opword 0x3C801062
		opword 0x800300F8
		opword 0x38A44DD3
		lwz r6, gp(r13)
		opword 0x5400F0BE
		opword 0x7C050016
		opword 0x80660038
		opword 0x8086003C
		opword 0x38A00000
		opword 0x5406D1BE
		bl __div2i
		opword 0x909E001C
		opword 0x3880FFFF
		lfs f0, float_0_80419a48(r2)
		opword 0x38000000
		opword 0x907E0018
		opword 0x909E003C
		opword 0xD01E0040
		opword 0x901E0080
		opword 0xD01E0084
		opword 0x801F0088
		opword 0x807F008C
		opword 0x907E001C
		opword 0x901E0018
		opword 0x807F0090
		bl animPoseMain
		opword 0x80DF0098
		opword 0x80FF009C
		opword 0x28060000
		opword 0x4182000C
		opword 0x381F00A0
		opword 0x48000008
		opword 0x38000000
		lwz r3, wp(r13)
		opword 0x28070000
		opword 0x90030030
		opword 0x4182000C
		opword 0x38BF00C0
		opword 0x48000008
		opword 0x38A00000
		lwz r3, wp(r13)
		opword 0x38800000
		opword 0x38000001
		opword 0x90A30034
		lwz r3, wp(r13)
		opword 0x90830038
		lwz r3, wp(r13)
		opword 0x90C30024
		lwz r3, wp(r13)
		opword 0x90E30028
		lwz r3, wp(r13)
		opword 0x9083002C
		lwz r3, wp(r13)
		opword 0x900300D8
		lwz r3, wp(r13)
		opword 0x900300DC
		opword 0x801F00E8
		opword 0x901E00E8
		opword 0x801F00EC
		opword 0x901E00EC
		opword 0x801F00F0
		opword 0x901E00F0
		opword 0x801F00F4
		opword 0x901E00F4
		opword 0x801F0000
		opword 0x540007BD
		opword 0x41820104
		opword 0xC03F010C
		opword 0x386100C8
		opword 0xC05F0110
		lfs f3, float_1_80419a44(r2)
		bl PSMTXScale
		opword 0xC03F0104
		opword 0x38610098
		opword 0xC05F0108
		lfs f3, float_0_80419a48(r2)
		bl PSMTXTrans
		opword 0x386100C8
		opword 0x38810098
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x340100C8
		opword 0x40820014
		lwz r3, wp(r13)
		opword 0x38000000
		opword 0x900300CC
		opword 0x48000020
		lwz r4, wp(r13)
		opword 0x386100C8
		opword 0x3884003C
		bl PSMTXCopy
		lwz r3, wp(r13)
		opword 0x3803003C
		opword 0x900300CC
		lwz r4, wp(r13)
		opword 0x38000000
		opword 0x386100C8
		opword 0x900400D0
		lwz r4, wp(r13)
		opword 0x900400D4
		opword 0xC03F00F8
		opword 0xC05F00FC
		opword 0xFC600890
		bl PSMTXScale
		lwz r3, wp(r13)
		opword 0x8003010C
		opword 0x2C000000
		opword 0x41820024
		lfs f1, float_0_80419a48(r2)
		opword 0x38610098
		lfs f2, float_2_80419a84(r2)
		opword 0xC01F0100
		opword 0xFC600890
		opword 0xEC420032
		bl PSMTXTrans
		opword 0x48000018
		lfs f1, float_0_80419a48(r2)
		opword 0x38610098
		opword 0xC05F0100
		opword 0xFC600890
		bl PSMTXTrans
		opword 0x388100C8
		opword 0x38610098
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x7F63DB78
		opword 0x388100C8
		la r5, g5_mtx_s1454(r13)
		bl PSMTXConcat
		la r27, g5_mtx_s1454(r13)
		opword 0x48000140
		opword 0xC03F010C
		opword 0x386100C8
		opword 0xC05F0110
		lfs f3, float_1_80419a44(r2)
		bl PSMTXScale
		opword 0xC03F0104
		opword 0x38610098
		opword 0xC05F0108
		lfs f3, float_0_80419a48(r2)
		bl PSMTXTrans
		opword 0x386100C8
		opword 0x38810098
		opword 0x7C651B78
		bl PSMTXConcat
		lfs f1, float_0p5_80419a64(r2)
		opword 0x38610098
		lfs f2, float_1_80419a44(r2)
		lfs f3, float_0_80419a48(r2)
		bl PSMTXTrans
		opword 0x386100C8
		opword 0x38810098
		opword 0x7C651B78
		bl PSMTXConcat
		lfs f3, float_1_80419a44(r2)
		opword 0x38610098
		opword 0xC03F00F8
		opword 0xC01F00FC
		opword 0xEC230824
		opword 0xEC430024
		bl PSMTXScale
		opword 0x386100C8
		opword 0x38810098
		opword 0x7C651B78
		bl PSMTXConcat
		lfs f1, float_neg0p5_80419a88(r2)
		opword 0x38610098
		lfs f2, float_neg1_80419a8c(r2)
		lfs f3, float_0_80419a48(r2)
		bl PSMTXTrans
		opword 0x386100C8
		opword 0x38810098
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x340100C8
		opword 0x40820014
		lwz r3, wp(r13)
		opword 0x38000000
		opword 0x900300CC
		opword 0x48000020
		lwz r4, wp(r13)
		opword 0x386100C8
		opword 0x3884003C
		bl PSMTXCopy
		lwz r3, wp(r13)
		opword 0x3803003C
		opword 0x900300CC
		lwz r3, wp(r13)
		opword 0x38000000
		opword 0x900300D0
		lwz r3, wp(r13)
		opword 0x900300D4
		opword 0x48000048
		opword 0x801F0010
		opword 0x2C1C0002
		opword 0x80660000
		opword 0x54002036
		opword 0x7C630214
		opword 0x80630008
		opword 0x806300A0
		opword 0x80630000
		opword 0x40820010
		opword 0x800300C4
		opword 0x540007FF
		opword 0x40820018
		opword 0x38000001
		opword 0x806300C4
		opword 0x7C00E030
		opword 0x7C600039
		opword 0x41820074
		opword 0x801F0090
		opword 0x2C00FFFF
		opword 0x41820050
		opword 0xFC20F090
		opword 0x7FC3F378
		opword 0xFC40F890
		opword 0x7F64DB78
		opword 0x7F85E378
		bl _animPoseDrawMtx
		lwz r3, wp(r13)
		opword 0x38800000
		opword 0x908300CC
		lwz r3, wp(r13)
		opword 0x908300D0
		lwz r3, wp(r13)
		opword 0x908300D4
		opword 0x801E0004
		opword 0x540007BD
		opword 0x41820028
		lwz r3, wp(r13)
		opword 0x908300E8
		opword 0x4800001C
		opword 0xFC20F090
		opword 0x7FE3FB78
		opword 0xFC40F890
		opword 0x7F64DB78
		opword 0x7F85E378
		bl _animPoseDrawMtx
	}
}
#pragma pop
#endif

u32 anim_ext_tex_size;

void animSetPaperTexObj(GXTexObj* obj1, GXTexObj* obj2, GXTexObj* obj3, void* data1, void* data2, void* data3, s32 a7, s32 a8) {
    wp->mpTexObjs[0] = data1 ? obj1 : NULL;
    wp->mpTexObjs[1] = data2 ? obj2 : NULL;
    wp->mpCurTexObj = data3 ? obj3 : NULL;
    wp->mpTexDatas[0] = data1;
    wp->mpTexDatas[1] = data2;
    wp->mpCurTexData = data3;
    wp->field_0xD8 = a7;
    wp->field_0xDC = a7;
}

inline void animPoseFileRelease(s32 fileId) {
    AnimationPoseFile* file = &wp->files[fileId];
    AnimationTextureFile* tex;

    file->references--;
    if (file->references <= 0) {
        file->active = 0;
        tex = &wp->textures[file->textureId];
        tex->references--;
        if (tex->references <= 0) {
            fileFree(tex->handle);
            tex->active = FALSE;
        }
        fileFree(file->handle);
    }
}

void animPoseRelease(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];

    if ((u32)pose->typeFlags != 0) {
        animPaperPoseRelease(poseId);
    }
    else {
        if (pose->flags & 0x40) {
            smartFree((smartEntry*)pose->worldPositions);
        }
        if (pose->flags & 0x80) {
            smartFree((smartEntry*)pose->worldMatrices);
        }
        animPoseFileRelease(pose->fileId);
        pose->flags = 0;
    }
}

void animPaperPoseRelease(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];

    pose->references--;
    if (pose->references < 0) {
        animPoseFileRelease(pose->fileId);
        pose->flags = 0;
    }
}

void animPoseAutoRelease(s32 type) {
    int i;
    AnimationPose* pose;

    for (i = 0; i < wp->totalPoses; i++) {
        pose = animPoseGetAnimPosePtr(i);
        if (pose->flags & 1 && pose->type == type) {
            animPoseRelease(i);
        }
    }
    if (type == 1) {
        wp->inBattle = FALSE;
    }
    animPoseRefresh();
}

#pragma dont_inline on
void animPaperPoseDisp(CameraId camId, void* param) {
    int i;
    AnimationPose* pose;

    for (i = 0, pose = wp->poses; i < wp->totalPoses; i++, pose++) {
        if (pose->flags & 1 && pose->paperId != -1) {
            animPaperPoseDispSub(0, pose);
        }
    }
}
#pragma dont_inline reset

#include "sdk/DEMOInit.h"
void _animPoseDrawMtx(AnimationPose* pose, Mtx matrix, s32 xluMode, f32 rotY, f32 scale);
typedef struct PaperAnimData {
    u8 pad[0x44];
    f32 x44, x48, x4C, x50, x54;
} PaperAnimData;
#define PP_ENT(p) (*(smartEntry**)((u8*)(p) + 0x98))
#define PP_9C(p) (*(s32*)((u8*)(p) + 0x9C))
#define PP_F(p, o) (*(f32*)((u8*)(p) + (o)))
#define PP_S(p, o) (*(s16*)((u8*)(p) + (o)))

#ifdef NONMATCHING
void animPaperPoseDispSub(s32 unused, AnimationPose* pose) {
    PaperAnimData* d;
    Mtx m, save;
    GXColor col1;
    u16 h;
    GXColor col2;
    s32 lightFlag;
    u32 flags;
    s32 matFlag;
    u16 left, top, right, bottom;
    u16 w;
    f32 scale, hh;
    s32 t, e, b, a, x1, y0, y1;

    scale = EXT_LIT(float_8_80419a70, 8.0f);
    if (!(pose->flags & 1)) {
        return;
    }
    d = (PaperAnimData*)animPoseGetBaseData(pose)->mpAnims[pose->animId].data;
    scale *= EXT_LIT(float_25p74_80419a74, 25.74f) / (d->x54 - d->x48);
    hh = EXT_LIT(float_0p75_80419a68, 0.75f) * DEMOGetRenderModeObj()->efbHeight;
    sysWaitDrawSync();
    GXClearBoundingBox();
    MTXTrans(m, EXT_LIT(float_0_80419a48, 0.0f), EXT_LIT(float_0p25_80419a6c, 0.25f) * -(f32)DEMOGetRenderModeObj()->efbHeight - d->x48 * scale, EXT_LIT(float_0_80419a48, 0.0f));
    flags = pose->flags;
    matFlag = pose->materialFlag;
    lightFlag = pose->materialLightFlag;
    col1 = pose->materialColor;
    col2 = pose->materialColor2;
    pose->flags = flags & ~8;
    pose->materialColor = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
    pose->materialColor2 = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
    pose->materialLightFlag = 0;
    if (pose->vivianType) {
        PSMTXCopy(pose->matrix, save);
        PSMTXCopy(m, pose->matrix);
    }
    _animPoseDrawMtx(pose, m, 2, EXT_LIT(float_0_80419a48, 0.0f), scale);
    pose->flags = flags;
    pose->materialFlag = matFlag;
    pose->materialColor = col1;
    pose->materialColor2 = col2;
    pose->materialLightFlag = lightFlag;
    if (pose->vivianType) {
        PSMTXCopy(save, pose->matrix);
    }
    sysWaitDrawSync();
    GXReadBoundingBox(&left, &top, &right, &bottom);
    if (left > right) {
        left = 0;
        top = 0;
        right = 16;
        bottom = 16;
    }
    if (pose->flags & 2 && pose->flags & 4 && gp->inBattle) {
        a = d->x44 * scale + (s32)(DEMOGetRenderModeObj()->fbWidth / 2);
        x1 = d->x50 * scale + (s32)(DEMOGetRenderModeObj()->fbWidth / 2);
        y0 = hh - scale * (d->x54 - d->x48);
        y1 = hh;
        if (a <= left && x1 >= right && y0 <= top && y1 >= bottom) {
            left = a;
            right = x1;
            top = y0;
            bottom = y1;
        }
    }
    if (left < 2) {
        left = 2;
    }
    if (top < 2) {
        top = 2;
    }
    if (right > DEMOGetRenderModeObj()->fbWidth - 2) {
        right = DEMOGetRenderModeObj()->fbWidth - 2;
    }
    if (bottom > DEMOGetRenderModeObj()->efbHeight - 2) {
        bottom = DEMOGetRenderModeObj()->efbHeight - 2;
    }
    if (pose->flags & 2) {
        if (pose->flags & 4) {
            a = DEMOGetRenderModeObj()->fbWidth / 2 - left;
            t = right - DEMOGetRenderModeObj()->fbWidth / 2;
            b = a;
            if (a < t) {
                b = t;
            }
            a = EXT_LIT(float_0p5_80419a64, 0.5f) * b;
            e = EXT_LIT(float_0p14881_80419a78, 0.14881f) * (bottom - top);
            PP_S(pose, 0x114) = DEMOGetRenderModeObj()->fbWidth / 2 - b - a;
            PP_S(pose, 0x116) = DEMOGetRenderModeObj()->fbWidth / 2 + b + a;
            PP_S(pose, 0x118) = top - e;
            PP_S(pose, 0x11A) = bottom + e;
            PP_F(pose, 0xF8) = (EXT_LIT(float_8_80419a70, 8.0f) / scale) * ((f32)(PP_S(pose, 0x116) - PP_S(pose, 0x114)) / EXT_LIT(float_150_80419a7c, 150.0f));
            PP_F(pose, 0xFC) = (EXT_LIT(float_8_80419a70, 8.0f) / scale) * ((f32)(PP_S(pose, 0x11A) - PP_S(pose, 0x118)) / EXT_LIT(float_215_80419a80, 215.0f));
            PP_F(pose, 0x100) = d->x48 + (hh - bottom) / scale;
            pose->flags &= ~4;
        }
    } else {
        s32 a;
        a = DEMOGetRenderModeObj()->fbWidth / 2 - left;
        t = right - DEMOGetRenderModeObj()->fbWidth / 2;
        b = a;
        if (a < t) {
            b = t;
        }
        a = EXT_LIT(float_0p5_80419a64, 0.5f) * b;
        e = EXT_LIT(float_0p14881_80419a78, 0.14881f) * (bottom - top);
        PP_S(pose, 0x114) = DEMOGetRenderModeObj()->fbWidth / 2 - b - a;
        PP_S(pose, 0x116) = DEMOGetRenderModeObj()->fbWidth / 2 + b + a;
        PP_S(pose, 0x118) = top - e;
        PP_S(pose, 0x11A) = bottom + e;
        PP_F(pose, 0xF8) = (EXT_LIT(float_8_80419a70, 8.0f) / scale) * ((f32)(PP_S(pose, 0x116) - PP_S(pose, 0x114)) / EXT_LIT(float_150_80419a7c, 150.0f));
        PP_F(pose, 0xFC) = (EXT_LIT(float_8_80419a70, 8.0f) / scale) * ((f32)(PP_S(pose, 0x11A) - PP_S(pose, 0x118)) / EXT_LIT(float_215_80419a80, 215.0f));
        PP_F(pose, 0x100) = d->x48 + (hh - bottom) / scale;
    }
    left -= 2;
    top -= 2;
    right += 2;
    bottom += 2;
    left -= left & 1;
    top -= top & 1;
    right += right & 1;
    bottom += bottom & 1;
    w = right - left;
    h = bottom - top;
    PP_F(pose, 0x104) = -((f32)left - PP_S(pose, 0x114)) / (f32)(PP_S(pose, 0x116) - PP_S(pose, 0x114));
    PP_F(pose, 0x108) = -((f32)top - PP_S(pose, 0x118)) / (f32)(PP_S(pose, 0x11A) - PP_S(pose, 0x118));
    PP_F(pose, 0x10C) = (f32)(PP_S(pose, 0x116) - PP_S(pose, 0x114)) / (f32)w;
    PP_F(pose, 0x110) = (f32)(PP_S(pose, 0x11A) - PP_S(pose, 0x118)) / (f32)h;
    GXSetTexCopySrc(left, top, w, h);
    GXSetTexCopyDst(w, h, GX_TF_RGB5A3, GX_FALSE);
    PP_ENT(pose) = smartAlloc(GXGetTexBufferSize(w, h, GX_TF_RGB5A3, GX_FALSE, 0), 3);
    GXCopyTex(PP_ENT(pose)->address, GX_TRUE);
    GXPixModeSync();
    GXInitTexObj((GXTexObj*)((u8*)pose + 0xA0), PP_ENT(pose)->address, w, h, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
    PP_9C(pose) = 0;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void animPaperPoseDispSub(s32 unused, AnimationPose* pose) {
	char _af_pad[188];
	asm volatile {
		opword 0x80040000
		opword 0x7C9E2378
		lfs f31, float_8_80419a70(r2)
		opword 0x540007FF
		opword 0x418208CC
		lwz r3, wp(r13)
		opword 0x801E0010
		opword 0x80830000
		opword 0x54032036
		opword 0x801E0014
		opword 0x7C641A14
		lfs f2, float_25p74_80419a74(r2)
		opword 0x80630008
		opword 0x54003032
		opword 0x806300A0
		opword 0x80630000
		opword 0x806301AC
		opword 0x7C630214
		opword 0x83A3003C
		opword 0xC03D0054
		opword 0xC01D0048
		opword 0xEC010028
		opword 0xEC020024
		opword 0xEFFF0032
		bl DEMOGetRenderModeObj
		opword 0xA0830006
		opword 0x3C004330
		lis r3, double_to_int_mask_802c2de0@ha
		stw r0, _af_pad+112(r1)
		lfd f2, double_to_int_mask_802c2de0@l(r3)
		opword 0x9081007C
		lfs f0, float_0p75_80419a68(r2)
		opword 0xC8210078
		opword 0xEC211028
		fmuls f30, f0, f1
		bl sysWaitDrawSync
		bl GXClearBoundingBox
		bl DEMOGetRenderModeObj
		opword 0xA0830006
		opword 0x3C004330
		opword 0xC01D0048
		lis r3, double_to_int_mask_802c2de0@ha
		opword 0x90810084
		addi r4, r3, double_to_int_mask_802c2de0@l
		lfs f1, float_0_80419a48(r2)
		opword 0xEC0007F2
		opword 0x90010080
		opword 0x38610048
		opword 0xC8A40000
		opword 0xFC600890
		opword 0xC8810080
		lfs f2, float_0p25_80419a6c(r2)
		opword 0xEC842828
		opword 0xFC802050
		opword 0xEC420138
		bl PSMTXTrans
		opword 0x839E0000
		opword 0x38000000
		opword 0x80BE00F0
		opword 0x809E00F4
		opword 0x57830776
		opword 0x83FE00E8
		lwz r27, 0xec(r30)
		opword 0x90A10014
		opword 0x907E0000
		lwz r3, dat_80419a34(r2)
		opword 0x90810010
		opword 0x907E00F0
		lwz r3, dat_80419a38(r2)
		opword 0x907E00F4
		opword 0x901E00EC
		opword 0x801E011C
		opword 0x2C000000
		opword 0x4182001C
		opword 0x387E0124
		opword 0x38810018
		bl PSMTXCopy
		opword 0x38610048
		opword 0x389E0124
		bl PSMTXCopy
		opword 0xFC40F890
		lfs f1, float_0_80419a48(r2)
		opword 0x7FC3F378
		opword 0x38810048
		opword 0x38A00002
		bl _animPoseDrawMtx
		opword 0x939E0000
		opword 0x80610014
		opword 0x93FE00E8
		opword 0x80010010
		opword 0x907E00F0
		opword 0x901E00F4
		opword 0x937E00EC
		opword 0x801E011C
		opword 0x2C000000
		opword 0x41820010
		opword 0x38610018
		opword 0x389E0124
		bl PSMTXCopy
		bl sysWaitDrawSync
		opword 0x3861000E
		opword 0x3881000C
		opword 0x38A1000A
		opword 0x38C10008
		bl GXReadBoundingBox
		opword 0xA061000E
		opword 0xA001000A
		opword 0x7C030040
		opword 0x4081001C
		opword 0x38600000
		opword 0x38000010
		opword 0xB061000E
		opword 0xB061000C
		opword 0xB001000A
		opword 0xB0010008
		opword 0x807E0000
		opword 0x546007BD
		opword 0x41820104
		opword 0x5460077B
		opword 0x418200FC
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x418200EC
		bl DEMOGetRenderModeObj
		opword 0xA0830004
		opword 0x3C004330
		opword 0x90010080
		lis r3, double_to_int_802c2df0@ha
		opword 0x5480F87E
		lfd f2, double_to_int_802c2df0@l(r3)
		opword 0x6C008000
		opword 0xC01D0044
		opword 0x90010084
		opword 0xC8210080
		opword 0xEC211028
		opword 0xEC000FFA
		opword 0xFC00001E
		opword 0xD8010078
		opword 0x8361007C
		bl DEMOGetRenderModeObj
		opword 0xA0030004
		opword 0x3C604330
		lis r5, double_to_int_802c2df0@ha
		opword 0xFC00F01E
		opword 0x5404F87E
		opword 0xA001000E
		opword 0x6C848000
		opword 0x90610088
		lfd f4, double_to_int_802c2df0@l(r5)
		opword 0x9081008C
		opword 0x7C1B0000
		opword 0xC05D0054
		opword 0xC8610088
		opword 0xC03D0048
		opword 0xEC832028
		opword 0xC07D0050
		opword 0xEC220828
		opword 0xD80100A0
		opword 0xEC4327FA
		opword 0x80A100A4
		opword 0xEC1FF07C
		opword 0xFC20101E
		opword 0xFC00001E
		opword 0xD8210090
		opword 0xD8010098
		opword 0x80610094
		opword 0x8081009C
		opword 0x41810038
		opword 0xA001000A
		opword 0x7C030000
		opword 0x4180002C
		opword 0xA001000C
		opword 0x7C040000
		opword 0x41810020
		opword 0xA0010008
		opword 0x7C050000
		opword 0x41800014
		opword 0xB361000E
		opword 0xB061000A
		opword 0xB081000C
		opword 0xB0A10008
		opword 0xA001000E
		opword 0x28000002
		opword 0x4080000C
		opword 0x38000002
		opword 0xB001000E
		opword 0xA001000C
		opword 0x28000002
		opword 0x4080000C
		opword 0x38000002
		opword 0xB001000C
		bl DEMOGetRenderModeObj
		opword 0xA0630004
		opword 0xA001000A
		opword 0x3863FFFE
		opword 0x7C001800
		opword 0x40810014
		bl DEMOGetRenderModeObj
		opword 0xA0630004
		opword 0x3803FFFE
		opword 0xB001000A
		bl DEMOGetRenderModeObj
		opword 0xA0630006
		opword 0xA0010008
		opword 0x3863FFFE
		opword 0x7C001800
		opword 0x40810014
		bl DEMOGetRenderModeObj
		opword 0xA0630006
		opword 0x3803FFFE
		opword 0xB0010008
		opword 0x807E0000
		opword 0x546007BD
		opword 0x418201A8
		opword 0x5460077B
		opword 0x4182032C
		bl DEMOGetRenderModeObj
		opword 0xA0630004
		opword 0xA001000E
		opword 0x5463F87E
		opword 0x7F601850
		bl DEMOGetRenderModeObj
		opword 0xA0630004
		opword 0x7F7FDB78
		opword 0xA001000A
		opword 0x5463F87E
		opword 0x7C030050
		opword 0x7C1B0000
		opword 0x40800008
		opword 0x7C1F0378
		opword 0xA061000C
		opword 0x3C804330
		opword 0xA0010008
		opword 0x6FE58000
		lis r6, double_to_int_802c2df0@ha
		opword 0x90A100A4
		opword 0x7C030050
		lfd f3, double_to_int_802c2df0@l(r6)
		opword 0x6C008000
		opword 0x908100A0
		lfs f4, float_0p5_80419a64(r2)
		opword 0xC84100A0
		opword 0x90010094
		opword 0xEC421828
		lfs f1, float_0p14881_80419a78(r2)
		opword 0x90810090
		opword 0xC8010090
		opword 0xEC4400B2
		opword 0xEC001828
		opword 0xEC010032
		opword 0xFC20101E
		opword 0xFC00001E
		opword 0xD8210098
		opword 0xD8010088
		opword 0x8361009C
		opword 0x8381008C
		bl DEMOGetRenderModeObj
		opword 0xA0030004
		opword 0x5400F87E
		opword 0x7C1F0050
		opword 0x7C1B0050
		opword 0xB01E0114
		bl DEMOGetRenderModeObj
		opword 0xA0630004
		opword 0x3C004330
		lis r4, double_to_int_802c2df0@ha
		lfs f0, float_8_80419a70(r2)
		opword 0x5465F87E
		lis r3, double_to_int_mask_802c2de0@ha
		opword 0x7CA5DA14
		opword 0xECA0F824
		opword 0x7CBF2A14
		lfd f4, double_to_int_802c2df0@l(r4)
		opword 0xB0BE0116
		lfd f1, double_to_int_mask_802c2de0@l(r3)
		opword 0xA081000C
		opword 0x7C9C2050
		opword 0x90010080
		lfs f2, float_150_80419a7c(r2)
		opword 0xB09E0118
		lfs f0, float_215_80419a80(r2)
		opword 0xA0810008
		opword 0x90010078
		opword 0x7C84E214
		opword 0xB09E011A
		opword 0xA89E0114
		opword 0xA87E0116
		opword 0x900100A8
		opword 0x7C041850
		opword 0x6C008000
		opword 0x90010084
		opword 0xC8610080
		opword 0xEC632028
		opword 0xEC431024
		opword 0xEC4500B2
		opword 0xD05E00F8
		opword 0xA87E0118
		opword 0xA81E011A
		opword 0x7C030050
		opword 0x6C008000
		opword 0x9001007C
		opword 0xC8410078
		opword 0xEC422028
		opword 0xEC020024
		opword 0xEC050032
		opword 0xD01E00FC
		opword 0xA0010008
		opword 0xC05D0048
		opword 0x900100AC
		opword 0xC80100A8
		opword 0xEC000828
		opword 0xEC1E0028
		opword 0xEC00F824
		opword 0xEC02002A
		opword 0xD01E0100
		opword 0x801E0000
		opword 0x540007B8
		opword 0x901E0000
		opword 0x48000190
		bl DEMOGetRenderModeObj
		opword 0xA0630004
		opword 0xA001000E
		opword 0x5463F87E
		opword 0x7F601850
		bl DEMOGetRenderModeObj
		opword 0xA0630004
		opword 0x7F7FDB78
		opword 0xA001000A
		opword 0x5463F87E
		opword 0x7C030050
		opword 0x7C1B0000
		opword 0x40800008
		opword 0x7C1F0378
		opword 0xA061000C
		opword 0x3C804330
		opword 0xA0010008
		opword 0x6FE58000
		lis r6, double_to_int_802c2df0@ha
		opword 0x90A100AC
		opword 0x7C030050
		lfd f3, double_to_int_802c2df0@l(r6)
		opword 0x6C008000
		opword 0x908100A8
		lfs f4, float_0p5_80419a64(r2)
		opword 0xC84100A8
		opword 0x9001009C
		opword 0xEC421828
		lfs f1, float_0p14881_80419a78(r2)
		opword 0x90810098
		opword 0xC8010098
		opword 0xEC4400B2
		opword 0xEC001828
		opword 0xEC010032
		opword 0xFC20101E
		opword 0xFC00001E
		opword 0xD82100A0
		opword 0xD8010090
		opword 0x836100A4
		opword 0x83810094
		bl DEMOGetRenderModeObj
		opword 0xA0030004
		opword 0x5400F87E
		opword 0x7C1F0050
		opword 0x7C1B0050
		opword 0xB01E0114
		bl DEMOGetRenderModeObj
		opword 0xA0630004
		opword 0x3C004330
		lis r4, double_to_int_802c2df0@ha
		lfs f0, float_8_80419a70(r2)
		opword 0x5465F87E
		lis r3, double_to_int_mask_802c2de0@ha
		opword 0x7CA5DA14
		opword 0xECA0F824
		opword 0x7CBF2A14
		lfd f4, double_to_int_802c2df0@l(r4)
		opword 0xB0BE0116
		lfd f1, double_to_int_mask_802c2de0@l(r3)
		opword 0xA081000C
		opword 0x7C9C2050
		opword 0x90010088
		lfs f2, float_150_80419a7c(r2)
		opword 0xB09E0118
		lfs f0, float_215_80419a80(r2)
		opword 0xA0810008
		opword 0x90010080
		opword 0x7C84E214
		opword 0xB09E011A
		opword 0xA89E0114
		opword 0xA87E0116
		opword 0x90010078
		opword 0x7C041850
		opword 0x6C008000
		opword 0x9001008C
		opword 0xC8610088
		opword 0xEC632028
		opword 0xEC431024
		opword 0xEC4500B2
		opword 0xD05E00F8
		opword 0xA87E0118
		opword 0xA81E011A
		opword 0x7C030050
		opword 0x6C008000
		opword 0x90010084
		opword 0xC8410080
		opword 0xEC422028
		opword 0xEC020024
		opword 0xEC050032
		opword 0xD01E00FC
		opword 0xA0010008
		opword 0xC05D0048
		opword 0x9001007C
		opword 0xC8010078
		opword 0xEC000828
		opword 0xEC1E0028
		opword 0xEC00F824
		opword 0xEC02002A
		opword 0xD01E0100
		opword 0xA061000C
		opword 0x3CE04330
		opword 0xA0A1000E
		lis r4, double_to_int_mask_802c2de0@ha
		opword 0x3903FFFE
		opword 0xA0610008
		opword 0x3805FFFE
		opword 0xA0A1000A
		opword 0x39630002
		opword 0xB001000E
		opword 0x38C50002
		opword 0x5403043E
		opword 0x540007FE
		opword 0xB101000C
		opword 0x7D401850
		opword 0x5503043E
		opword 0x550007FE
		opword 0x54C5043E
		opword 0x7D001850
		opword 0x5549043E
		lis r3, double_to_int_802c2df0@ha
		lfd f4, double_to_int_mask_802c2de0@l(r4)
		opword 0x54C007FE
		opword 0xB0C1000A
		opword 0x7CC50214
		opword 0x5565043E
		opword 0x556007FE
		opword 0xB1610008
		opword 0x7CA50214
		lfd f3, double_to_int_802c2df0@l(r3)
		opword 0x54C0043E
		opword 0xB141000E
		opword 0x7C090050
		opword 0x5504043E
		opword 0xB101000C
		opword 0x54A3043E
		opword 0x541C043E
		opword 0x7C041850
		opword 0xB0C1000A
		opword 0x541D043E
		opword 0xB0A10008
		opword 0xA89E0114
		opword 0xA81E0116
		opword 0x6C838000
		opword 0x912100AC
		opword 0x7C040050
		opword 0x90E100A8
		opword 0x6C008000
		opword 0xC80100A8
		opword 0x906100A4
		opword 0xEC202028
		opword 0x90E100A0
		opword 0xC80100A0
		opword 0x9001009C
		opword 0xEC001828
		opword 0x90E10098
		opword 0xEC210028
		opword 0xC8010098
		opword 0x90E10090
		opword 0xEC001828
		opword 0xFC200850
		opword 0x90E10088
		opword 0x90E10080
		opword 0xEC010024
		opword 0xD01E0104
		opword 0xA8BE0118
		opword 0xA081000C
		opword 0x6CA38000
		opword 0xA81E011A
		opword 0x90810094
		opword 0x7C050050
		opword 0x9061008C
		opword 0x6C008000
		opword 0xC8210090
		opword 0xC8010088
		opword 0xEC412028
		opword 0x90010084
		opword 0xEC201828
		opword 0xC8010080
		opword 0xEC220828
		opword 0xEC001828
		opword 0xFC200850
		opword 0xEC010024
		opword 0xD01E0108
		opword 0xA87E0114
		opword 0x7F85E378
		opword 0xA81E0116
		opword 0x7FA6EB78
		opword 0x90E10078
		opword 0x7C030050
		opword 0x6C008000
		opword 0x938100B4
		opword 0x9001007C
		opword 0x90E100B0
		opword 0xC8210078
		opword 0xC80100B0
		opword 0xEC211828
		opword 0x90E100B8
		opword 0xEC002028
		opword 0x93A100C4
		opword 0xEC210024
		opword 0x90E100C0
		opword 0xC80100C0
		opword 0xD03E010C
		opword 0xEC002028
		opword 0xA87E0118
		opword 0xA81E011A
		opword 0x7C030050
		opword 0x6C008000
		opword 0x900100BC
		opword 0xC82100B8
		opword 0xEC211828
		opword 0xEC010024
		opword 0xD01E0110
		opword 0xA061000E
		opword 0xA081000C
		bl GXSetTexCopySrc
		opword 0x7F83E378
		opword 0x7FA4EB78
		opword 0x38A00005
		opword 0x38C00000
		bl GXSetTexCopyDst
		opword 0x7F83E378
		opword 0x7FA4EB78
		opword 0x38A00005
		opword 0x38C00000
		opword 0x38E00000
		bl GXGetTexBufferSize
		opword 0x38800003
		bl smartAlloc
		opword 0x907E0098
		opword 0x38800001
		opword 0x807E0098
		opword 0x80630000
		bl GXCopyTex
		bl GXPixModeSync
		opword 0x809E0098
		opword 0x7F85E378
		opword 0x7FA6EB78
		opword 0x387E00A0
		opword 0x80840000
		opword 0x38E00005
		opword 0x39000000
		opword 0x39200000
		opword 0x39400000
		bl GXInitTexObj
		opword 0x38000000
		opword 0x901E009C
	}
}
#pragma pop
#endif

void _animPoseDrawMtx(AnimationPose* pose, Mtx matrix, s32 xluMode, f32 rotY, f32 scale);
#include "sdk/DEMOInit.h"
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on

#ifdef NONMATCHING
inline s32 animPoseSearchName(const char* name, s32 type) {
    AnimationPose* pose;
    s32 i;

    for (i = 0; i < wp->totalPoses; i++) {
        pose = &wp->poses[i];
        if (pose->flags & 1 && pose->type == type && !strcmp(animPoseGetBaseData(pose)->fileName, name)) {
            break;
        }
    }
    if (i == wp->totalPoses) {
        i = -1;
    }
    return i;
}
#endif

#pragma push
#pragma opt_lifetimes off
#ifdef NONMATCHING
void animPoseDisp_MakeExtTexture(const char* group, const char* anim, f32 frame, f32 scale, GXTexObj* obj,
                                 smartEntry** image, s32* x0, s32* y0, s32* x1, s32* y1) {
    AnimationPose* pose;
    AnimationPose* pera;
    AnimationPose backup;
    Mtx m;
    GXColor col1, col2;
    u32 flags;
    s32 matFlag;
    u16 left, top, right, bottom;
    u16 w, h;
    f32 hw, hh;
    s32 i;

    i = animPoseSearchName(group, gp->inBattle != 0);
    if (i < 0) {
        return;
    }
    pose = &wp->poses[i];
    backup = *pose;
    pose->paperId = -1;
    animPoseSetAnim(i, anim, FALSE);
    pose->localTime = animTimeGetTime(pose->type);
    pose->lastFrameZero = -1;
    pose->lastFrameTime = EXT_LIT(float_0_80419a48, 0.0f);
    pose->field_0x80 = 0;
    pose->loopTime = EXT_LIT(float_0_80419a48, 0.0f);
    animPoseSetLocalTime(i, frame);
    animPoseMain(i);

    hw = EXT_LIT(float_0p5_80419a64, 0.5f) * DEMOGetRenderModeObj()->fbWidth;
    hh = EXT_LIT(float_0p75_80419a68, 0.75f) * DEMOGetRenderModeObj()->efbHeight;
    sysWaitDrawSync();
    GXClearBoundingBox();
    MTXTrans(m, EXT_LIT(float_0_80419a48, 0.0f), EXT_LIT(float_0p25_80419a6c, 0.25f) * -(f32)DEMOGetRenderModeObj()->efbHeight, EXT_LIT(float_0_80419a48, 0.0f));
    flags = pose->flags;
    matFlag = pose->materialFlag;
    col1 = pose->materialColor;
    col2 = pose->materialColor2;
    pose->flags = flags & ~8;
    pose->materialFlag = 0;
    pose->materialColor = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
    pose->materialColor2 = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
    _animPoseDrawMtx(pose, m, 1, EXT_LIT(float_0_80419a48, 0.0f), scale);
    _animPoseDrawMtx(pose, m, 2, EXT_LIT(float_0_80419a48, 0.0f), scale);
    _animPoseDrawMtx(pose, m, 3, EXT_LIT(float_0_80419a48, 0.0f), scale);
    pose->materialColor = col1;
    pose->materialColor2 = col2;
    pose->flags = flags;
    pose->materialFlag = matFlag;
    sysWaitDrawSync();
    GXReadBoundingBox(&left, &top, &right, &bottom);
    if (left > right) {
        top = left = 0;
        bottom = right = 16;
    }
    if (left < 2) {
        left = 2;
    }
    if (top < 2) {
        top = 2;
    }
    if (right > DEMOGetRenderModeObj()->fbWidth - 2) {
        right = DEMOGetRenderModeObj()->fbWidth - 2;
    }
    if (top > DEMOGetRenderModeObj()->efbHeight - 2) {
        top = DEMOGetRenderModeObj()->efbHeight - 2;
    }
    left -= left & 1;
    top -= top & 1;
    right += right & 1;
    bottom += bottom & 1;
    w = right - left;
    h = bottom - top;
    GXSetTexCopySrc(left, top, w, h);
    GXSetTexCopyDst(w, h, GX_TF_RGB5A3, GX_FALSE);
    anim_ext_tex_size += GXGetTexBufferSize(w, h, GX_TF_RGB5A3, GX_FALSE, 0);
    *image = smartAlloc(GXGetTexBufferSize(w, h, GX_TF_RGB5A3, GX_FALSE, 0), 1);
    GXCopyTex((*image)->address, GX_TRUE);
    GXPixModeSync();
    GXInitTexObj(obj, (*image)->address, w, h, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
    *x0 = left - (s32)hw;
    *y0 = top - (s32)hh;
    *x1 = right - (s32)hw;
    *y1 = bottom - (s32)hh;
    *pose = backup;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void animPoseDisp_MakeExtTexture(const char* group, const char* anim, f32 frame, f32 scale, GXTexObj* obj,
                                 smartEntry** image, s32* x0, s32* y0, s32* x1, s32* y1) {
	asm volatile {
		opword 0x9421FDC0
		opword 0x7C0802A6
		opword 0x90010244
		opword 0xDBE10230
		opword 0xF3E10238
		opword 0xDBC10220
		opword 0xF3C10228
		opword 0xDBA10210
		opword 0xF3A10218
		opword 0xBE2101D4
		lwz r11, gp(r13)
		opword 0x3BE00000
		opword 0xFFA00890
		opword 0x7C7D1B78
		opword 0x806B0014
		opword 0xFFE01090
		opword 0x7C942378
		opword 0x7CB92B78
		opword 0x7C0300D0
		opword 0x7CDB3378
		opword 0x7C001B78
		opword 0x7CF83B78
		opword 0x7D174378
		opword 0x7D364B78
		opword 0x7D555378
		opword 0x7FFCFB78
		opword 0x541A0FFE
		opword 0x4800005C
		opword 0x80050010
		opword 0x7C60E214
		opword 0x80030000
		opword 0x540007FF
		opword 0x41820040
		opword 0x8003000C
		opword 0x7C00D000
		opword 0x40820034
		opword 0x80030010
		opword 0x7FA4EB78
		opword 0x80A50000
		opword 0x54032036
		opword 0x38030008
		opword 0x7C65002E
		opword 0x806300A0
		opword 0x80630000
		opword 0x38630004
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3B9C0170
		opword 0x3BFF0001
		lwz r5, wp(r13)
		opword 0x80050014
		opword 0x7C1F0000
		opword 0x4180FF9C
		lwz r3, wp(r13)
		opword 0x80030014
		opword 0x7C1F0000
		opword 0x40820008
		opword 0x3BE0FFFF
		opword 0x2C1F0000
		opword 0x41800668
		opword 0x1FBF0170
		opword 0x80630010
		opword 0x3800002E
		opword 0x38A10044
		opword 0x7FC3EA14
		opword 0x389EFFFC
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		opword 0x3800FFFF
		opword 0x2C140000
		opword 0x901E0090
		lwz r3, wp(r13)
		opword 0x80030010
		opword 0x80630000
		opword 0x7F80EA14
		opword 0x801C0010
		opword 0x54002036
		opword 0x7C630214
		opword 0x80630008
		opword 0x806300A0
		opword 0x82430000
		opword 0x83520148
		opword 0x40800040
		opword 0x3A600000
		opword 0x7E719B78
		opword 0x48000028
		opword 0x801201AC
		opword 0x7E84A378
		opword 0x7C608A14
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x4800002C
		opword 0x3A310040
		opword 0x3A730001
		opword 0x7C13D000
		opword 0x4180FFD8
		opword 0x48000014
		opword 0x7C14D000
		opword 0x4080000C
		opword 0x7E93A378
		opword 0x48000008
		opword 0x3A600000
		opword 0x801C0014
		opword 0x7C130000
		opword 0x418200BC
		opword 0x927C0014
		opword 0x801C0090
		opword 0x2C00FFFF
		opword 0x41820018
		opword 0x807C0000
		opword 0x546007BD
		opword 0x4182000C
		opword 0x60600004
		opword 0x901C0000
		opword 0x801C000C
		opword 0x2C000000
		opword 0x40820038
		opword 0x3C608000
		opword 0x3C801062
		opword 0x800300F8
		opword 0x38A44DD3
		lwz r6, gp(r13)
		opword 0x5400F0BE
		opword 0x7C050016
		opword 0x80660040
		opword 0x80860044
		opword 0x38A00000
		opword 0x5406D1BE
		bl __div2i
		opword 0x48000034
		opword 0x3C608000
		opword 0x3C801062
		opword 0x800300F8
		opword 0x38A44DD3
		lwz r6, gp(r13)
		opword 0x5400F0BE
		opword 0x7C050016
		opword 0x80660038
		opword 0x8086003C
		opword 0x38A00000
		opword 0x5406D1BE
		bl __div2i
		opword 0x909C001C
		opword 0x3880FFFF
		lfs f0, float_0_80419a48(r2)
		opword 0x38000000
		opword 0x907C0018
		opword 0x909C003C
		opword 0xD01C0040
		opword 0x901C0080
		opword 0xD01C0084
		opword 0x801E000C
		opword 0x2C000000
		opword 0x40820038
		opword 0x3C608000
		opword 0x3C801062
		opword 0x800300F8
		opword 0x38A44DD3
		lwz r6, gp(r13)
		opword 0x5400F0BE
		opword 0x7C050016
		opword 0x80660040
		opword 0x80860044
		opword 0x38A00000
		opword 0x5406D1BE
		bl __div2i
		opword 0x48000034
		opword 0x3C608000
		opword 0x3C801062
		opword 0x800300F8
		opword 0x38A44DD3
		lwz r6, gp(r13)
		opword 0x5400F0BE
		opword 0x7C050016
		opword 0x80660038
		opword 0x8086003C
		opword 0x38A00000
		opword 0x5406D1BE
		bl __div2i
		opword 0x909E001C
		opword 0x3880FFFF
		lfs f0, float_16p667_80419a60(r2)
		opword 0x38000000
		opword 0x907E0018
		opword 0xEC200772
		lfs f0, float_0_80419a48(r2)
		opword 0x909E003C
		opword 0xD01E0040
		opword 0x901E0080
		opword 0xD01E0084
		lwz r3, wp(r13)
		opword 0x80030010
		opword 0x7FA0EA14
		bl __cvt_dbl_usll
		opword 0x801D000C
		opword 0x7C9C2378
		opword 0x7C7A1B78
		opword 0x2C000000
		opword 0x40820038
		opword 0x3C608000
		opword 0x3C801062
		opword 0x800300F8
		opword 0x38A44DD3
		lwz r6, gp(r13)
		opword 0x5400F0BE
		opword 0x7C050016
		opword 0x80660040
		opword 0x80860044
		opword 0x38A00000
		opword 0x5406D1BE
		bl __div2i
		opword 0x48000034
		opword 0x3C608000
		opword 0x3C801062
		opword 0x800300F8
		opword 0x38A44DD3
		lwz r6, gp(r13)
		opword 0x5400F0BE
		opword 0x7C050016
		opword 0x80660038
		opword 0x8086003C
		opword 0x38A00000
		opword 0x5406D1BE
		bl __div2i
		opword 0x7C1C2010
		opword 0x901D001C
		opword 0x7C1A1910
		opword 0x901D0018
		opword 0x801D0018
		opword 0x807D001C
		opword 0x907D008C
		opword 0x901D0088
		opword 0x801D0090
		opword 0x2C00FFFF
		opword 0x41820030
		lwz r3, wp(r13)
		opword 0x1C000170
		opword 0x80630010
		opword 0x7C830214
		opword 0x80040004
		opword 0x540007BD
		opword 0x40820014
		opword 0x801D0018
		opword 0x807D001C
		opword 0x9064001C
		opword 0x90040018
		opword 0x7FE3FB78
		bl animPoseMain
		bl DEMOGetRenderModeObj
		opword 0xA0830004
		opword 0x3C004330
		lis r3, double_to_int_mask_802c2de0@ha
		opword 0x900101B8
		lfd f2, double_to_int_mask_802c2de0@l(r3)
		opword 0x908101BC
		lfs f0, float_0p5_80419a64(r2)
		opword 0xC82101B8
		opword 0xEC211028
		opword 0xEFC00072
		bl DEMOGetRenderModeObj
		opword 0xA0830006
		opword 0x3C004330
		lis r3, double_to_int_mask_802c2de0@ha
		opword 0x900101C0
		lfd f2, double_to_int_mask_802c2de0@l(r3)
		opword 0x908101C4
		lfs f0, float_0p75_80419a68(r2)
		opword 0xC82101C0
		opword 0xEC211028
		opword 0xEFA00072
		bl sysWaitDrawSync
		bl GXClearBoundingBox
		bl DEMOGetRenderModeObj
		opword 0xA0830006
		opword 0x3C004330
		lis r3, double_to_int_mask_802c2de0@ha
		lfs f1, float_0_80419a48(r2)
		opword 0x908101CC
		lfd f4, double_to_int_mask_802c2de0@l(r3)
		opword 0xFC600890
		opword 0x900101C8
		opword 0x38610018
		lfs f0, float_0p25_80419a6c(r2)
		opword 0xC84101C8
		opword 0xEC422028
		opword 0xFC401050
		opword 0xEC4000B2
		bl PSMTXTrans
		opword 0x823E0000
		opword 0x38000000
		opword 0x809E00F0
		opword 0xFC40F890
		opword 0x80DE00F4
		opword 0x56250776
		opword 0x825E00E8
		opword 0x7FC3F378
		opword 0x90810014
		lfs f1, float_0_80419a48(r2)
		opword 0x38810018
		opword 0x90BE0000
		opword 0x38A00001
		opword 0x901E00E8
		lwz r0, dat_80419a3c(r2)
		opword 0x90C10010
		opword 0x901E00F0
		lwz r0, dat_80419a40(r2)
		opword 0x901E00F4
		bl _animPoseDrawMtx
		opword 0xFC40F890
		lfs f1, float_0_80419a48(r2)
		opword 0x7FC3F378
		opword 0x38810018
		opword 0x38A00002
		bl _animPoseDrawMtx
		opword 0xFC40F890
		lfs f1, float_0_80419a48(r2)
		opword 0x7FC3F378
		opword 0x38810018
		opword 0x38A00003
		bl _animPoseDrawMtx
		opword 0x80610014
		opword 0x80010010
		opword 0x907E00F0
		opword 0x901E00F4
		opword 0x923E0000
		opword 0x925E00E8
		bl sysWaitDrawSync
		opword 0x3861000E
		opword 0x3881000C
		opword 0x38A1000A
		opword 0x38C10008
		bl GXReadBoundingBox
		opword 0xA061000E
		opword 0xA001000A
		opword 0x7C030040
		opword 0x4081001C
		opword 0x38600000
		opword 0x38000010
		opword 0xB061000E
		opword 0xB061000C
		opword 0xB001000A
		opword 0xB0010008
		opword 0xA001000E
		opword 0x28000002
		opword 0x4080000C
		opword 0x38000002
		opword 0xB001000E
		opword 0xA001000C
		opword 0x28000002
		opword 0x4080000C
		opword 0x38000002
		opword 0xB001000C
		bl DEMOGetRenderModeObj
		opword 0xA0630004
		opword 0xA001000A
		opword 0x3863FFFE
		opword 0x7C001800
		opword 0x40810014
		bl DEMOGetRenderModeObj
		opword 0xA0630004
		opword 0x3803FFFE
		opword 0xB001000A
		bl DEMOGetRenderModeObj
		opword 0xA0630006
		opword 0xA001000C
		opword 0x3863FFFE
		opword 0x7C001800
		opword 0x40810014
		bl DEMOGetRenderModeObj
		opword 0xA0630006
		opword 0x3803FFFE
		opword 0xB001000C
		opword 0xA061000E
		opword 0xA0C1000C
		opword 0x546007FE
		opword 0xA0A1000A
		opword 0x7D201850
		opword 0xA0810008
		opword 0x54C007FE
		opword 0x54A307FE
		opword 0x7CE51A14
		opword 0xB121000E
		opword 0x7D003050
		opword 0x548007FE
		opword 0x7CC40214
		opword 0x5523043E
		opword 0x54E5043E
		opword 0x5504043E
		opword 0x54C0043E
		opword 0xB101000C
		opword 0x7CA32850
		opword 0x7C040050
		opword 0xB0E1000A
		opword 0x54B1043E
		opword 0x5412043E
		opword 0xB0C10008
		opword 0x7E258B78
		opword 0x7E469378
		bl GXSetTexCopySrc
		opword 0x7E238B78
		opword 0x7E449378
		opword 0x38A00005
		opword 0x38C00000
		bl GXSetTexCopyDst
		opword 0x7E238B78
		opword 0x7E449378
		opword 0x38A00005
		opword 0x38C00000
		opword 0x38E00000
		bl GXGetTexBufferSize
		lwz r0, anim_ext_tex_size(r13)
		opword 0x7E449378
		opword 0x38A00005
		opword 0x38C00000
		opword 0x7C001A14
		opword 0x7E238B78
		stw r0, anim_ext_tex_size(r13)
		opword 0x38E00000
		bl GXGetTexBufferSize
		opword 0x38800001
		bl smartAlloc
		opword 0x907B0000
		opword 0x38800001
		opword 0x807B0000
		opword 0x80630000
		bl GXCopyTex
		bl GXPixModeSync
		opword 0x809B0000
		opword 0x7F23CB78
		opword 0x7E258B78
		opword 0x7E469378
		opword 0x80840000
		opword 0x38E00005
		opword 0x39000000
		opword 0x39200000
		opword 0x39400000
		bl GXInitTexObj
		opword 0xFC20F01E
		opword 0xA061000E
		opword 0xFC00E81E
		opword 0x3800002E
		opword 0x38BEFFFC
		opword 0x38810044
		opword 0xD82101C8
		opword 0x80C101CC
		opword 0xD80101C0
		opword 0x7C661850
		opword 0x90780000
		opword 0x80E101C4
		opword 0xA061000C
		opword 0x7C671850
		opword 0x90770000
		opword 0xA061000A
		opword 0x7C661850
		opword 0x90760000
		opword 0xA0610008
		opword 0x7C671850
		opword 0x90750000
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		opword 0xE3E10238
		opword 0xCBE10230
		opword 0xE3C10228
		opword 0xCBC10220
		opword 0xE3A10218
		opword 0xCBA10210
		opword 0xBA2101D4
		opword 0x80010244
		opword 0x7C0803A6
		opword 0x38210240
	}
}
#pragma pop
#endif
#pragma pop


void animSetPaperTexMtx(Mtx mtx1, Mtx mtx2, Mtx mtx3) {
    if (mtx1 == NULL) {
        wp->paperMtxPtr[0] = NULL;
    }
    else {
        PSMTXCopy(mtx1, wp->paperMtx[0]);
        wp->paperMtxPtr[0] = &wp->paperMtx[0];
    }
    if (mtx2 == NULL) {
        wp->paperMtxPtr[1] = NULL;
    }
    else {
        PSMTXCopy(mtx2, wp->paperMtx[1]);
        wp->paperMtxPtr[1] = &wp->paperMtx[1];
    }
    if (mtx3 == NULL) {
        wp->paperMtxPtr[2] = NULL;
    }
    else {
        PSMTXCopy(mtx3, wp->paperMtx[2]);
        wp->paperMtxPtr[2] = &wp->paperMtx[2];
    }
}

#ifdef NONMATCHING
BOOL animGroupBaseAsync(const char* name, s32 group, void* callback) {
    s32 model, anim;

    switch (group) {
        case 0:
            fileSetCurrentArchiveType(1);
            break;
        case 1:
            fileSetCurrentArchiveType(2);
            break;
        case 2:
            fileSetCurrentArchiveType(0);
            break;
    }
    model = fileAsyncf(5, callback, "%s/%s", "a", name);
    anim = fileAsyncf(4, NULL, "%s/%s-", "a", animGetTexName(name));
    if (model == -1) {
        return TRUE;
    }
    if ((u32)model == 0) {
        return FALSE;
    }
    if (anim == -1) {
        return TRUE;
    }
    return anim != 0;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
BOOL animGroupBaseAsync(const char* name, s32 group, void* callback) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x2C040001
		opword 0x90010024
		opword 0xBF61000C
		opword 0x7C7B1B78
		opword 0x7CBC2B78
		opword 0x4182002C
		opword 0x40800010
		opword 0x2C040000
		opword 0x40800014
		opword 0x48000030
		opword 0x2C040003
		opword 0x40800028
		opword 0x4800001C
		opword 0x38600001
		bl fileSetCurrentArchiveType
		opword 0x48000018
		opword 0x38600002
		bl fileSetCurrentArchiveType
		opword 0x4800000C
		opword 0x38600000
		bl fileSetCurrentArchiveType
		opword 0x7F84E378
		opword 0x7F67DB78
		opword 0x38600005
		la r5, str_80419A54(r2)
		la r6, str_80419A5C(r2)
		opword 0x4CC63182
		bl fileAsyncf
		lwz r4, wp(r13)
		opword 0x7C7F1B78
		opword 0x3BA00000
		opword 0x80640100
		opword 0x806300A0
		opword 0x83830004
		opword 0x83C30000
		opword 0x48000028
		opword 0x7FC3F378
		opword 0x7F64DB78
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x38FE0020
		opword 0x48000018
		opword 0x3BDE0020
		opword 0x3BBD0020
		opword 0x7C1DE000
		opword 0x4180FFD8
		la r7, zero_80419a50(r2)
		lis r3, str_802C2DE8@ha
		opword 0x38800000
		addi r5, r3, str_802C2DE8@l
		la r6, str_80419A5C(r2)
		opword 0x38600004
		opword 0x4CC63182
		bl fileAsyncf
		opword 0x2C1FFFFF
		opword 0x4082000C
		opword 0x38600001
		opword 0x48000030
		opword 0x281F0000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000020
		opword 0x2C03FFFF
		opword 0x4082000C
		opword 0x38600001
		opword 0x48000010
		opword 0x7C0300D0
		opword 0x7C001B78
		opword 0x54030FFE
		opword 0xBB61000C
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
const char* animGetTexName(const char* name) {
    void** data = wp->mp_ag2tg->data;
    s32 size;
    s32 i;
    char* entry;

    size = (s32)data[1];
    entry = data[0];

    for (i = 0; i < size; entry += 0x20, i += 0x20) {
        if (!strcmp(entry, name)) {
            return entry + 0x20;
        }
    }
    return "";
}
#endif

#ifdef NONMATCHING
void animStrippedPool(f32* p, u32 n) {
    p[0] = 0.0f;
    p[1] = EXT_LIT(float_deg2rad_80419a4c, 0.017453292f) * p[1];
    p[2] = n;
}
#endif

AnimationPose* animPoseGetAnimPosePtr(s32 poseId) {
    return &wp->poses[poseId];
}

AnimData* animPoseGetAnimDataPtr(s32 poseId) {
    AnimationPose* pose = animPoseGetAnimPosePtr(poseId);
    return animPoseGetAnimBaseDataPtr(poseId)->mpAnims[pose->animId].data;
}

AnimationPoseData* animPoseGetAnimBaseDataPtr(s32 poseId) {
    AnimationPose* pose = animPoseGetAnimPosePtr(poseId);
    return *wp->files[pose->fileId].handle->data;
}

AnimTableEntry* animPoseGetCurrentAnim(s32 poseId) {
    AnimationPoseData* data = animPoseGetAnimBaseDataPtr(poseId);
    return &data->mpAnims[animPoseGetAnimPosePtr(poseId)->animId];
}

BOOL animPoseTestXLU(s32 poseId) {
    return (animPoseGetAnimBaseDataPtr(poseId)->flags >> 3) & 1;
}

#ifdef NONMATCHING
void evalProc(s32 parentId, s32 groupId) {
    AnimPoseGroup* group;
    AnimPoseGroup* parent;
    AnimPoseNode* node;
    AnimationPose* pose;
    AnimationPoseData* data;
    f32 sx, sy, sz;

    if (groupId == -1) {
        return;
    }
    pose = wp->mpCurPose;
    data = wp->mpCurPoseData;
    group = &data->groups[groupId];
    if (*(s8*)&pose->mpGroupVisibility[group->visibilityId]) {
        pose = wp->mpCurPose;
        node = (AnimPoseNode*)((u32*)pose->mpNodes + group->nodeId);
        if (group->useSSC) {
            if (parentId == -1) {
                sx = sy = sz = 1.0f;
            }
            else {
                parent = &data->groups[parentId];
                if (!parent->useSSC) {
                    sx = sy = sz = 1.0f;
                }
                else {
                    AnimPoseNode* pnode = (AnimPoseNode*)((u32*)pose->mpNodes + parent->nodeId);
                    sx = pnode->mScale.x;
                    sy = pnode->mScale.y;
                    sz = pnode->mScale.z;
                }
            }
            pushGXModelMtx_JointNode__(node, sx, sy, sz);
        }
        else {
            pushGXModelMtx_TransformNode__(node);
        }
        if (wp->mpCurPose->flags & 0x40) {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = (*g_modeling_mtx)[0][3];
            pos.y = (*g_modeling_mtx)[1][3];
            pos.z = (*g_modeling_mtx)[2][3];
            (*wp->mpCurPose->worldPositions)[groupId] = pos;
        }
        if (wp->mpCurPose->flags & 0x80) {
            PSMTXCopy(*g_modeling_mtx, (*wp->mpCurPose->worldMatrices)[groupId]);
        }
        if (!(wp->mpCurPose->flags & 0x20) || groupId != wp->mpCurPose->vivianGroupNo[0]) {
            evalProc(groupId, group->childGroupId);
        }
        g_modeling_mtx_lv--;
        g_modeling_mtx = &g_modeling_mtx_stack[g_modeling_mtx_lv];
    }
    evalProc(groupId, group->brotherGroupId);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void evalProc(s32 parentId, s32 groupId) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		opword 0x93C10018
		opword 0x7C9E2378
		opword 0x2C1EFFFF
		opword 0x418201B4
		lwz r5, wp(r13)
		opword 0x1C1E0058
		opword 0x80850020
		opword 0x80A50018
		opword 0x80C401A8
		opword 0x8085005C
		opword 0x7FE60214
		opword 0x801F004C
		opword 0x7C0400AE
		opword 0x7C000775
		opword 0x4182017C
		opword 0x801F0054
		opword 0x809F0050
		opword 0x2C000000
		opword 0x80A50064
		opword 0x5480103A
		opword 0x7C850214
		opword 0x41820064
		opword 0x2C03FFFF
		opword 0x40820014
		lfs f3, float_1_80419a44(r2)
		opword 0xFC401890
		opword 0xFC201890
		opword 0x48000040
		opword 0x1C030058
		opword 0x7C660214
		opword 0x80030054
		opword 0x2C000000
		opword 0x40820014
		lfs f3, float_1_80419a44(r2)
		opword 0xFC401890
		opword 0xFC201890
		opword 0x4800001C
		opword 0x80030050
		opword 0x5400103A
		opword 0x7C650214
		opword 0xC023000C
		opword 0xC0430010
		opword 0xC0630014
		opword 0x7C832378
		bl pushGXModelMtx_JointNode__
		opword 0x4800000C
		opword 0x7C832378
		bl pushGXModelMtx_TransformNode__
		lwz r3, wp(r13)
		opword 0x80830018
		opword 0x80040000
		opword 0x54000673
		opword 0x41820068
		lis r3, vec3_802c2dd4@ha
		lwz r7, g_modeling_mtx(r13)
		addi r6, r3, vec3_802c2dd4@l
		opword 0x8064015C
		opword 0x80A60000
		opword 0x1C1E000C
		opword 0x80860004
		opword 0x90A10008
		opword 0xC007000C
		opword 0x80A60008
		opword 0xD0010008
		opword 0x80630000
		opword 0x9081000C
		opword 0xC027001C
		opword 0x7C830214
		opword 0x90A10010
		opword 0xC007002C
		opword 0xD021000C
		opword 0x80010008
		opword 0xD0010010
		opword 0x8061000C
		opword 0x90040000
		opword 0x80010010
		opword 0x90640004
		opword 0x90040008
		lwz r3, wp(r13)
		opword 0x80630018
		opword 0x80030000
		opword 0x54000631
		opword 0x4182001C
		opword 0x80830164
		opword 0x1C1E0030
		lwz r3, g_modeling_mtx(r13)
		opword 0x80840000
		opword 0x7C840214
		bl PSMTXCopy
		lwz r3, wp(r13)
		opword 0x80630018
		opword 0x80030000
		opword 0x540006B5
		opword 0x41820014
		opword 0x80630120
		opword 0x80030000
		opword 0x7C1E0000
		opword 0x41820010
		opword 0x809F0044
		opword 0x7FC3F378
		bl evalProc
		lwz r4, g_modeling_mtx_lv(r13)
		lis r3, g_modeling_mtx_stack@ha
		addi r0, r3, g_modeling_mtx_stack@l
		opword 0x3884FFFF
		opword 0x1C640030
		stw r4, g_modeling_mtx_lv(r13)
		opword 0x7C001A14
		stw r0, g_modeling_mtx(r13)
		opword 0x809F0040
		opword 0x7FC3F378
		bl evalProc
		opword 0x80010024
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop
#endif

void animPoseWorldPositionEvalOn(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    AnimationPoseData* data = animPoseGetBaseData(pose);
    u8 heap;

    if (!(pose->flags & 0x40)) {
        pose->flags |= 0x40;
        switch (pose->type) {
            case 0:
                heap = 1;
                break;
            case 1:
                heap = 2;
                break;
            case 2:
                heap = 0;
                break;
        }
        pose->numWorldPositions = data->groupCount;
        pose->worldPositions = (Vec**)smartAlloc(sizeof(Vec) * data->groupCount, heap);
    }
}

void L_animPoseWorldPositionEvalOff(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];

    if (pose->flags & 0x40) {
        pose->flags &= ~0x40;
        smartFree((smartEntry*)pose->worldPositions);
        pose->worldPositions = NULL;
    }
}

void animPoseWorldMatrixEvalOn(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    AnimationPoseData* data = animPoseGetBaseData(pose);
    u8 heap;

    if (!(pose->flags & 0x80)) {
        pose->flags |= 0x80;
        switch (pose->type) {
            case 0:
                heap = 1;
                break;
            case 1:
                heap = 2;
                break;
            case 2:
                heap = 0;
                break;
        }
        pose->numWorldMatrices = data->groupCount;
        pose->worldMatrices = (Mtx**)smartAlloc(sizeof(Mtx) * data->groupCount, heap);
    }
}

void animPoseVivianMain(s32 poseId, Vec* pos) {
    AnimationPose* pose = &wp->poses[poseId];

    pose->flags |= 0x20;
    pose->matrix[0][3] = pos->x;
    pose->matrix[1][3] = pos->y;
    pose->matrix[2][3] = pos->z;
}

s32 animPoseGetVivianType(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    return pose->vivianType;
}

void animPoseSetDispCallBack(s32 poseId, void* callback, void* userData) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->dispCallback = callback;
    pose->dispUserDataCallback = userData;
}

inline void animPoseMainSub(AnimationPose* pose) {
    s32 id = ((u32)pose - (u32)wp->poses) / sizeof(AnimationPose);
    if (pose->typeFlags & 2) {
        AnimationPoseData* data = animPoseGetBaseData(pose);
        s32 posNum = data->mBufferPosNum;
        s32 nrmNum = data->mBufferNrmNum;
        if (posNum + nrmNum <= wp->mFloatScratchRP) {
            if (wp->mFloatScratchWP + (posNum + nrmNum) > wp->mFloatScratchRP) {
                wp->mFloatScratchWP = 0;
            }
            wp->mbUseFloatScratch = 1;
            wp->vtxArrayPos = &wp->mpFloatScratch[wp->mFloatScratchWP];
            wp->mFloatScratchWP += posNum;
            wp->vtxArrayNrm = &wp->mpFloatScratch[wp->mFloatScratchWP];
            wp->mFloatScratchWP += nrmNum;
        }
        animPoseMain(id);
        wp->mbUseFloatScratch = 0;
    }
    else {
        animPoseMain(id);
    }
}

void animPoseDrawShape(s32 poseId, s32 shapeId) {
    AnimationPose* pose;
    GXTexObj* texObj0;
    GXTexObj* texObj1;
    GXTexObj* curTexObj;
    void* texData0;
    void* texData1;
    void* curTexData;
    Mtx* paperMtx0;
    Mtx* paperMtx1;
    Mtx* paperMtx2;
    AnimationPose* curPose;
    AnimData* curAnimData;
    AnimationPoseData* curPoseData;
    u32 d8;
    u32 dc;
    s32 id;

    pose = &wp->poses[poseId];
    curPose = wp->mpCurPose;
    curAnimData = wp->mpCurAnimData;
    curPoseData = wp->mpCurPoseData;
    texObj0 = wp->mpTexObjs[0];
    texObj1 = wp->mpTexObjs[1];
    curTexObj = wp->mpCurTexObj;
    texData0 = wp->mpTexDatas[0];
    texData1 = wp->mpTexDatas[1];
    curTexData = wp->mpCurTexData;
    paperMtx0 = wp->paperMtxPtr[0];
    paperMtx1 = wp->paperMtxPtr[1];
    paperMtx2 = wp->paperMtxPtr[2];
    d8 = wp->field_0xD8;
    dc = wp->field_0xDC;

    wp->mpCurPose = pose;
    wp->mpCurAnimData = animPoseGetBaseData(pose)->mpAnims[pose->animId].data;
    wp->mpCurPoseData = animPoseGetBaseData(pose);
    wp->mpTexObjs[0] = NULL;
    wp->mpTexObjs[1] = NULL;
    wp->mpCurTexObj = NULL;
    wp->mpTexDatas[0] = NULL;
    wp->mpTexDatas[1] = NULL;
    wp->mpCurTexData = NULL;
    wp->paperMtxPtr[0] = NULL;
    wp->paperMtxPtr[1] = NULL;
    wp->paperMtxPtr[2] = NULL;
    wp->field_0xD8 = 0;
    wp->field_0xDC = 0;

    if (pose->lastFrameZero == -1) {
        animPoseMainSub(pose);
    }
    renderProc(shapeId, pose->field_0x28);

    wp->mpCurPose = curPose;
    wp->mpCurAnimData = curAnimData;
    wp->mpCurPoseData = curPoseData;
    wp->mpTexObjs[0] = texObj0;
    wp->mpTexObjs[1] = texObj1;
    wp->mpCurTexObj = curTexObj;
    wp->mpTexDatas[0] = texData0;
    wp->mpTexDatas[1] = texData1;
    wp->mpCurTexData = curTexData;
    wp->paperMtxPtr[0] = paperMtx0;
    wp->paperMtxPtr[1] = paperMtx1;
    wp->paperMtxPtr[2] = paperMtx2;
    wp->field_0xD8 = d8;
    wp->field_0xDC = dc;
}

s32 animPoseGetShapeIdx(s32 poseId, const char* name) {
    AnimationPoseData* data;
    AnimPoseShape* shape;
    s32 i;

    data = animPoseGetAnimBaseDataPtr(poseId);
    shape = data->shapes;
    for (i = 0; i < data->shapeCount; i++, shape++) {
        if (!strcmp(shape->name, name)) {
            return i;
        }
    }
    return -1;
}

s32 animPoseGetGroupIdx(s32 poseId, const char* name) {
    AnimationPoseData* data;
    AnimPoseGroup* group;
    s32 i;

    data = animPoseGetAnimBaseDataPtr(poseId);
    group = data->groups;
    for (i = 0; i < data->groupCount; i++, group++) {
        if (!strcmp(group->name, name)) {
            return i;
        }
    }
    return -1;
}

const char* animPoseGetGroupName(s32 poseId, s32 group) {
    return animPoseGetAnimBaseDataPtr(poseId)->groups[group].name;
}

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const char str_802C2A98[12] = "joint_00\0\0\0";
__declspec(section ".rodata") const char str_802C2AA4[16] = "jointdai1_A01\0\0";
__declspec(section ".rodata") const char str_802C2AB4[16] = "jointdai1_A02\0\0";
__declspec(section ".rodata") const char str_802C2AC4[16] = "jointdai1_A03\0\0";
__declspec(section ".rodata") const char str_802C2AD4[16] = "jointdai1_A04\0\0";
__declspec(section ".rodata") const char str_802C2AE4[16] = "jointdai1_A05\0\0";
__declspec(section ".rodata") const char str_802C2AF4[16] = "jointdai1_B01\0\0";
__declspec(section ".rodata") const char str_802C2B04[16] = "jointdai1_B02\0\0";
__declspec(section ".rodata") const char str_802C2B14[16] = "jointdai1_B03\0\0";
__declspec(section ".rodata") const char str_802C2B24[16] = "jointdai1_B04\0\0";
__declspec(section ".rodata") const char str_802C2B34[16] = "jointdai1_B05\0\0";
__declspec(section ".rodata") const char str_802C2B44[16] = "jointdai1_C01\0\0";
__declspec(section ".rodata") const char str_802C2B54[16] = "jointdai1_C02\0\0";
__declspec(section ".rodata") const char str_802C2B64[16] = "jointdai1_C03\0\0";
__declspec(section ".rodata") const char str_802C2B74[16] = "jointdai1_C04\0\0";
__declspec(section ".rodata") const char str_802C2B84[16] = "jointdai1_C05\0\0";
__declspec(section ".rodata") const char str_802C2B94[16] = "jointdai2_01\0\0\0";
__declspec(section ".rodata") const char str_802C2BA4[16] = "jointdai2_02\0\0\0";
__declspec(section ".rodata") const char str_802C2BB4[16] = "jointdai2_03\0\0\0";
__declspec(section ".rodata") const char str_802C2BC4[16] = "jointdai2_04\0\0\0";
__declspec(section ".rodata") const char str_802C2BD4[16] = "jointdai2_05\0\0\0";
__declspec(section ".rodata") const char str_802C2BE4[16] = "jointdai2_06\0\0\0";
__declspec(section ".rodata") const char str_802C2BF4[16] = "jointdai2_07\0\0\0";
__declspec(section ".rodata") const char str_802C2C04[20] = "jointdai2_upper01\0\0";
__declspec(section ".rodata") const char str_802C2C18[20] = "jointdai2_upper02\0\0";
__declspec(section ".rodata") const char str_802C2C2C[20] = "jointdai2_upper03\0\0";
__declspec(section ".rodata") const char str_802C2C40[20] = "jointdai2_upper04\0\0";
__declspec(section ".rodata") const char str_802C2C54[20] = "jointdai2_lower01\0\0";
__declspec(section ".rodata") const char str_802C2C68[20] = "jointdai2_lower02\0\0";
__declspec(section ".rodata") const char str_802C2C7C[20] = "jointdai2_lower03\0\0";
__declspec(section ".rodata") const char str_802C2C90[20] = "jointdai2_lower04\0\0";
__declspec(section ".rodata") const char str_802C2CA4[16] = "jointasi_A01\0\0\0";
__declspec(section ".rodata") const char str_802C2CB4[16] = "jointasi_A02\0\0\0";
__declspec(section ".rodata") const char str_802C2CC4[16] = "jointasi_A03\0\0\0";
__declspec(section ".rodata") const char str_802C2CD4[16] = "jointasi_A04\0\0\0";
__declspec(section ".rodata") const char str_802C2CE4[16] = "jointasi_B01\0\0\0";
__declspec(section ".rodata") const char str_802C2CF4[16] = "jointasi_B02\0\0\0";
__declspec(section ".rodata") const char str_802C2D04[16] = "jointasi_B03\0\0\0";
__declspec(section ".rodata") const char str_802C2D14[16] = "jointasi_B04\0\0\0";
__declspec(section ".rodata") const char str_802C2D24[16] = "jointasi_C01\0\0\0";
__declspec(section ".rodata") const char str_802C2D34[16] = "jointasi_C02\0\0\0";
__declspec(section ".rodata") const char str_802C2D44[16] = "jointasi_C03\0\0\0";
__declspec(section ".rodata") const char str_802C2D54[16] = "jointasi_C04\0\0\0";
__declspec(section ".rodata") const char str_802C2D64[16] = "jointasi_D01\0\0\0";
__declspec(section ".rodata") const char str_802C2D74[16] = "jointasi_D02\0\0\0";
__declspec(section ".rodata") const char str_802C2D84[16] = "jointasi_D03\0\0\0";
__declspec(section ".rodata") const char str_802C2D94[16] = "jointasi_D04\0\0\0";
__declspec(section ".rodata") const char str_802C2DA4[12] = "joint_core\0";
__declspec(section ".rodata") const f32 vec3_802c2db0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c2dbc[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c2dc8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c2dd4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f64 double_to_int_mask_802c2de0 = 4503599627370496.0;
__declspec(section ".rodata") const char str_802C2DE8[8] = "%s/%s-\0";
__declspec(section ".rodata") const f64 double_to_int_802c2df0 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802C2DF8[] = "Error: animSetMaterial_ChangeTexture: \x83" "e\x83N\x83X\x83`\x83\x83\x82\xaa\x82\xa0\x82\xe8\x82\xdc\x82\xb9\x82\xf1 frameExt=%d\n\0\0";
__declspec(section ".rodata") const char str_802C2E44[] = "Error: dispSetTevMode: \x83x\x81[\x83X\x83\x82\x83" "f\x83\x8b%s \x83" "A\x83j\x83\x81 %s \x93\xe0\x82\xc5 \x83t\x83\x8c\x81[\x83\x80\x83G\x83N\x83X\x83" "e\x83\x93\x83V\x83\x87\x83\x93\x82\xcc\x90\xdd\x92\xe8\x82\xaa\x8ds\x82\xed\x82\xea\x82\xc4\x82\xa2\x82\xdc\x82\xb7\x82\xaa\x81" "A\x8aY\x93\x96\x82\xb7\x82\xe9\x83" "e\x83N\x83X\x83`\x83\x83\x82\xaa\x82\xa0\x82\xe8\x82\xdc\x82\xb9\x82\xf1 \nframeExt\x94\xd4\x8d\x86 %d? \x82\xaa\x96\xb3\x82\xa2\x82\xe6\x82\xa4\x82\xc5\x82\xb7\x81" "B\x83\x82\x83" "f\x83\x8b\x82\xdc\x82\xbd\x82\xcd\x83" "A\x83j\x83\x81\x82\xc9\x8f" "C\x90\xb3\x82\xaa\x95K\x97v\x82\xc5\x82\xb7\x81" "BtextureIdx=%d\n\0";
__declspec(section ".rodata") const f64 double_10_802c2f20 = 10.0;
__declspec(section ".rodata") const char str_802C2F28[12] = "tst_vivi\0\0\0";
__declspec(section ".rodata") const char str_802C2F34[12] = "c_vivian\0\0\0";
__declspec(section ".rodata") const char str_802C2F40[12] = "c_maririn\0\0";
__declspec(section ".rodata") const char str_802C2F4C[12] = "c_majyorin\0";
__declspec(section ".rodata") const char str_802C2F58[16] = "a/vivian.bin\0\0\0";
__declspec(section ".rodata") const char str_802C2F68[12] = "a/ag2tg.bin";
__declspec(section ".rodata") const u32 gap_04_802C2F74_rodata = 0x00000000;
__declspec(section ".sdata2") const u32 dat_80419a28 = 0x0000002F;
__declspec(section ".sdata2") const u32 dat_80419a2c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419a30 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419a34 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419a38 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419a3c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419a40 = 0xFFFFFFFF;
__declspec(section ".sdata2") const f32 float_1_80419a44 = 1.0f;
__declspec(section ".sdata2") const f32 float_0_80419a48 = 0.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_80419a4c = 0.017453292f;
__declspec(section ".sdata2") const u32 zero_80419a50 = 0x00000000;
__declspec(section ".sdata2") const char str_80419A54[8] = "%s/%s\0\0";
__declspec(section ".sdata2") const char str_80419A5C[4] = "a\0\0";
__declspec(section ".sdata2") const f32 float_16p667_80419a60 = 16.666666f;
__declspec(section ".sdata2") const f32 float_0p5_80419a64 = 0.5f;
__declspec(section ".sdata2") const f32 float_0p75_80419a68 = 0.75f;
__declspec(section ".sdata2") const f32 float_0p25_80419a6c = 0.25f;
__declspec(section ".sdata2") const f32 float_8_80419a70 = 8.0f;
__declspec(section ".sdata2") const f32 float_25p74_80419a74 = 25.74f;
__declspec(section ".sdata2") const f32 float_0p14881_80419a78 = 0.14881f;
__declspec(section ".sdata2") const f32 float_150_80419a7c = 150.0f;
__declspec(section ".sdata2") const f32 float_215_80419a80 = 215.0f;
__declspec(section ".sdata2") const f32 float_2_80419a84 = 2.0f;
__declspec(section ".sdata2") const f32 float_neg0p5_80419a88 = -0.5f;
__declspec(section ".sdata2") const f32 float_neg1_80419a8c = -1.0f;
__declspec(section ".sdata2") const f32 float_neg90_80419a90 = -90.0f;
__declspec(section ".sdata2") const f32 float_rad2deg_80419a94 = 57.29579f;
__declspec(section ".sdata2") const f32 float_360_80419a98 = 360.0f;
__declspec(section ".sdata2") const f32 float_neg360_80419a9c = -360.0f;
__declspec(section ".sdata2") const f32 float_90_80419aa0 = 90.0f;
__declspec(section ".sdata2") const f32 float_270_80419aa4 = 270.0f;
__declspec(section ".sdata2") const f32 float_neg270_80419aa8 = -270.0f;
__declspec(section ".sdata2") const f32 float_180_80419aac = 180.0f;
__declspec(section ".sdata2") const f32 float_neg180_80419ab0 = -180.0f;
__declspec(section ".sdata2") const f32 float_0p1_80419ab4 = 0.1f;
__declspec(section ".sdata2") const f32 float_neg2_80419ab8 = -2.0f;
__declspec(section ".sdata2") const f32 float_neg3_80419abc = -3.0f;
__declspec(section ".sdata2") const f32 float_0p04_80419ac0 = 0.04f;
__declspec(section ".sdata2") const f32 float_60_80419ac4 = 60.0f;
__declspec(section ".sdata2") const f32 float_1000_80419ac8 = 1000.0f;
__declspec(section ".sdata2") const f32 float_0p0625_80419acc = 0.0625f;
__declspec(section ".sdata2") const f32 float_3_80419ad0 = 3.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_80419ad4 = 0.017453289f;
#endif

// .bss definitions last, reverse target order: emitted g_modeling_mtx_stack, work, tanfTbl as in the target
// (asm references alone would order them by first use)
f32 tanfTbl[0xB2];
AnimationWork work;
Mtx g_modeling_mtx_stack[32];
