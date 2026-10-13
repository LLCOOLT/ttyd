#include "eff/eff_n64.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "memory.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

double sin(double);
double cos(double);
double fmod(double, double);
s32 irand(s32);

typedef struct EffKumokumoN64Particle {
    s32 type;       // 0x0
    f32 x;          // 0x4
    f32 y;          // 0x8
    f32 z;          // 0xC
    s32 delay;      // 0x10
    s32 frame;      // 0x14
    s32 r1;         // 0x18
    s32 g1;         // 0x1C
    s32 b1;         // 0x20
    s32 alpha;      // 0x24
    s32 r2;         // 0x28
    s32 g2;         // 0x2C
    s32 b2;         // 0x30
    s32 a2;         // 0x34
    f32 s1;         // 0x38
    f32 ds1;        // 0x3C
    f32 t1;         // 0x40
    f32 dt1;        // 0x44
    f32 s2;         // 0x48
    f32 ds2;        // 0x4C
    f32 t2;         // 0x50
    f32 dt2;        // 0x54
    f32 rot;        // 0x58
    f32 scale;      // 0x5C
    s32 camera;     // 0x60
} EffKumokumoN64Particle;

#ifdef __MWERKS__
__declspec(section ".data") u64 lbl_803A2280 = 0xBF8000003F800000;
__declspec(section ".data") u64 negone_one_374 = 0xBF8000003F800000;
__declspec(section ".data") u64 lbl_803A2290 = 0x3F800000BF800000;
__declspec(section ".data") u64 one_negone_373 = 0x3F800000BF800000;
__declspec(section ".data") u64 lbl_803A22A0 = 0xBF8000003F800000;
__declspec(section ".data") u64 negone_one_360 = 0xBF8000003F800000;
__declspec(section ".data") u64 lbl_803A22B0 = 0x3F800000BF800000;
__declspec(section ".data") u64 one_negone_359 = 0x3F800000BF800000;
#endif

__declspec(section ".data") u32 cloud_vertex_tbl[] = {0x61BF081C, 0x00006A40, 0x19CD0000, 0x6C5F3000, 0x0000670F, 0x406A0000, 0x60AF4515, 0x0000571F, 0xFDF60000, 0x571F0D58, 0x0000571F, 0x20150000, 0x571F32D2, 0x0000571F, 0x42350000, 0x4400F9C8, 0x00004400, 0x05DA0000, 0x440013D5, 0x00004400, 0x21D00000, 0x44002DE3, 0x00002FD0, 0xF8860000, 0x2FD00123, 0x00002FD0, 0x0A7F0000, 0x2FD013DC, 0x00002FD0, 0x1C7A0000, 0x1CB0F845, 0x00001CB0, 0xFDAA0000, 0x1CB00300, 0x00001CB0, 0x08560000, 0x1CB00DBB, 0x00000DCF, 0xF9E80000, 0x0DCFFD27, 0x00000DD0, 0x00000000, 0x0DD002D9, 0x00000DD0, 0x06180000, 0x0000FCEC, 0x00000000, 0xFEA10000, 0x00000000, 0x00000000, 0x015F0000, 0x00000314, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".data") u32 cloud_texcoord0_tbl[] = {0x0000CCCD, 0x1000CCCD, 0x1000C001, 0x0000C001, 0x2000CCCD, 0x2000C001, 0x3000CCCD, 0x3000C001, 0x4000CCCD, 0x4000C001, 0x0000D667, 0x1000D667, 0x2000D667, 0x3000D667, 0x4000D667, 0x0000E000, 0x1000E000, 0x2000E000, 0x3000E000, 0x4000E000, 0x0000E99A, 0x1000E99A, 0x2000E99A, 0x3000E99A, 0x4000E99A, 0x0000F334, 0x1000F334, 0x2000F334, 0x3000F334, 0x4000F334, 0x00000000, 0x10000000, 0x20000000, 0x30000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".data") u32 cloud_texcoord1_tbl[] = {0x0000CCCD, 0x1000CCCD, 0x1000C001, 0x0000C001, 0x2000CCCD, 0x2000C001, 0x3000CCCD, 0x3000C001, 0x4000CCCD, 0x4000C001, 0x0000D667, 0x1000D667, 0x2000D667, 0x3000D667, 0x4000D667, 0x0000E000, 0x1000E000, 0x2000E000, 0x3000E000, 0x4000E000, 0x0000E99A, 0x1000E99A, 0x2000E99A, 0x3000E99A, 0x4000E99A, 0x0000F334, 0x1000F334, 0x2000F334, 0x3000F334, 0x4000F334, 0x00000000, 0x10000000, 0x20000000, 0x30000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".data") u32 cloud_dl_0_0[] = {0x98000E1E, 0x00001E1E, 0x1F00001F, 0x1F190001, 0x19191A00, 0x031A1A14, 0x00011414, 0x15000315, 0x150F0001, 0x0F0F1000, 0x0310100A, 0x00010A0A, 0x0B00030B, 0x0B050000, 0x00000600, 0x01010100, 0x00000303, 0x01000002, 0x02000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".data") u32 cloud_dl_0_1[] = {0x98000E1F, 0x00001F1F, 0x20000020, 0x201A0003, 0x1A1A1B00, 0x041B1B15, 0x00031515, 0x16000416, 0x16100003, 0x10101100, 0x0411110B, 0x00030B0B, 0x0C00040C, 0x0C060001, 0x01010700, 0x02040401, 0x00000202, 0x02000005, 0x05000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".data") u32 cloud_dl_0_2[] = {0x98000E20, 0x00002020, 0x21000021, 0x211B0004, 0x1B1B1C00, 0x031C1C16, 0x00041616, 0x17000317, 0x17110004, 0x11111200, 0x0312120C, 0x00040C0C, 0x0D00030D, 0x0D070002, 0x04040800, 0x01060602, 0x00000505, 0x03000007, 0x07000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".data") u32 cloud_dl_0_3[] = {0x98000E21, 0x00002121, 0x22000022, 0x221C0003, 0x1C1C1D00, 0x011D1D17, 0x00031717, 0x18000118, 0x18120003, 0x12121300, 0x0113130D, 0x00030D0D, 0x0E00010E, 0x0E080001, 0x06060900, 0x00080803, 0x00000707, 0x04000009, 0x09000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".data") u32 batten_vertex_tbl[] = {0xC890C3A1, 0x0000DEBD, 0xC1000000, 0x0000BE60, 0x00002143, 0xC1000000, 0x3770C3A1, 0x0000D58E, 0xCE200000, 0xE689CE20, 0x00000000, 0xCE200000, 0x1977CE20, 0x00002A72, 0xCE200000, 0xDEC0D8A0, 0x0000EC0D, 0xD8A00000, 0x0000D8A0, 0x000013F3, 0xD8A00000, 0x2140D8A0, 0x0000E393, 0xE0800000, 0xEEF2E080, 0x00000000, 0xE0800000, 0x110EE080, 0x00001C6D, 0xE0800000, 0xE7C3E860, 0x0000F175, 0xE8600000, 0x0000E860, 0x00000E8B, 0xE8600000, 0x183DE860, 0x0000ED67, 0xF5800000, 0xF4D7F580, 0x00000000, 0xF5800000, 0x0B29F580, 0x00001299, 0xF5800000, 0xEF430000, 0x0000F5F5, 0x00000000, 0x00000000, 0x00000A0B, 0x00000000, 0x10BD0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".data") u32 batten_texcoord0_tbl[] = {0x00002AAA, 0x10002AAA, 0x10003000, 0x00003000, 0x20002AAA, 0x20003000, 0x30002AAA, 0x30003000, 0x40002AAA, 0x40003000, 0x00002555, 0x10002555, 0x20002555, 0x30002555, 0x40002555, 0x00002000, 0x10002000, 0x20002000, 0x30002000, 0x40002000, 0x00001AAA, 0x10001AAA, 0x20001AAA, 0x30001AAA, 0x40001AAA, 0x00001555, 0x10001555, 0x20001555, 0x30001555, 0x40001555, 0x00001000, 0x10001000, 0x20001000, 0x30001000, 0x40001000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".data") u32 batten_texcoord1_tbl[] = {0x00002AAA, 0x10002AAA, 0x10003000, 0x00003000, 0x20002AAA, 0x20003000, 0x30002AAA, 0x30003000, 0x40002AAA, 0x40003000, 0x00002555, 0x10002555, 0x20002555, 0x30002555, 0x40002555, 0x00002000, 0x10002000, 0x20002000, 0x30002000, 0x40002000, 0x00001AAA, 0x10001AAA, 0x20001AAA, 0x30001AAA, 0x40001AAA, 0x00001555, 0x10001555, 0x20001555, 0x30001555, 0x40001555, 0x00001000, 0x10001000, 0x20001000, 0x30001000, 0x40001000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".data") u32 batten_dl_0_0[] = {0x98000E1E, 0x00021E1E, 0x1F00021F, 0x1F190000, 0x19191A00, 0x041A1A14, 0x00001414, 0x15000415, 0x150F0000, 0x0F0F1000, 0x0410100A, 0x00000A0A, 0x0B00040B, 0x0B050000, 0x00000600, 0x01010100, 0x00020303, 0x01000202, 0x02000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".data") u32 batten_dl_0_1[] = {0x98000E1F, 0x00021F1F, 0x20000220, 0x201A0004, 0x1A1A1B00, 0x051B1B15, 0x00041515, 0x16000516, 0x16100004, 0x10101100, 0x0511110B, 0x00040B0B, 0x0C00050C, 0x0C060001, 0x01010700, 0x03040401, 0x00020202, 0x02000205, 0x05000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".data") u32 batten_dl_0_2[] = {0x98000E20, 0x00022020, 0x21000221, 0x211B0005, 0x1B1B1C00, 0x041C1C16, 0x00051616, 0x17000417, 0x17110005, 0x11111200, 0x0412120C, 0x00050C0C, 0x0D00040D, 0x0D070003, 0x04040800, 0x01060602, 0x00020505, 0x03000207, 0x07000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".data") u32 batten_dl_0_3[] = {0x98000E21, 0x00022121, 0x22000222, 0x221C0004, 0x1C1C1D00, 0x001D1D17, 0x00041717, 0x18000018, 0x18120004, 0x12121300, 0x0013130D, 0x00040D0D, 0x0E00000E, 0x0E080001, 0x06060900, 0x00080803, 0x00020707, 0x04000209, 0x09000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".sdata") u32 cloud_normal_tbl[] = {0x00004000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".sdata") u32 cloud_color0_tbl[] = {0xFFFFFF00, 0xFFFFFF33, 0xFFFFFF66, 0xFFFFFF7F, 0xFFFFFFCC};
__declspec(section ".sdata") void* cloud_dl_0_tbl[] = {cloud_dl_0_0, cloud_dl_0_1, cloud_dl_0_2, cloud_dl_0_3};
__declspec(section ".sdata") u8 cloud_dl_0_size_tbl[] = {0x03, 0x03, 0x03, 0x03};
__declspec(section ".sdata") u32 batten_normal_tbl[] __attribute__((aligned(32))) = {0x00004000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".sdata") u32 batten_color0_tbl[] = {0xFFFFFF33, 0xFFFFFF66, 0xFFFFFF00, 0xFFFFFF99, 0xFFFFFF7F, 0xFFFFFFCC};
__declspec(section ".sdata") void* batten_dl_0_tbl[] = {batten_dl_0_0, batten_dl_0_1, batten_dl_0_2, batten_dl_0_3};
__declspec(section ".sdata") u8 batten_dl_0_size_tbl[] = {0x03, 0x03, 0x03, 0x03};
__declspec(section ".sdata") u8 rz_tbl[] = {0x00, 0x09, 0x12, 0x1C, 0x25, 0x2F, 0x39, 0x43, 0x4D, 0x57, 0x61, 0x6B, 0x74, 0x7D, 0x86, 0x8F, 0x97, 0x9F, 0xA6, 0xAD, 0xB4, 0xB8, 0xB9, 0xB9, 0xB6, 0xB4, 0xB1, 0xAE, 0xAE, 0xAF, 0xB4, 0x00};

#define KK_ARRAYS(vtx, tex0, tex1, norm, clr)                                                              \
    GXClearVtxDesc();                                                                                      \
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);                                                                    \
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 6);                                         \
    GXSetArray(GX_VA_POS, vtx, 6);                                                                         \
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);                                                                    \
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 6);                                          \
    GXSetArray(GX_VA_NRM, norm, 3);                                                                        \
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);                                                                   \
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);                                     \
    GXSetArray(GX_VA_CLR0, clr, 4);                                                                        \
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);                                                                   \
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 14);                                        \
    GXSetArray(GX_VA_TEX0, tex0, 4);                                                                       \
    GXSetVtxDesc(GX_VA_TEX1, GX_INDEX8);                                                                   \
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_TEX_ST, GX_S16, 14);                                        \
    GXSetArray(GX_VA_TEX1, tex1, 4);

void effKumokumoMain(EffectEntry* effect);
void effKumokumoDisp(CameraId cameraId, EffectEntry* effect);

EffectEntry* effKumokumoN64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 rot, f32 arg6, f32 scale) {
    EffectEntry* effect;
    EffKumokumoN64Particle* work;
    EffKumokumoN64Particle* p;
    s32 count;
    s32 i;

    effect = effEntry();
    count = 11;
    if (type == 1) {
        count = 1;
    }
    if (type == 2) {
        rot = 0.0f;
    }
    effect->type = "KumokumoN64";
    effect->count = count;
    work = __memAlloc(HEAP_EFFECT, count * sizeof(EffKumokumoN64Particle));
    effect->userdata = work;
    effect->callback = effKumokumoMain;
    effect->flags |= 2;
    work->type = type;
    work->frame = 0;
    if (time <= 0) {
        work->delay = 1000;
    } else {
        work->delay = time;
    }
    work->alpha = 0;
    work->x = x;
    work->y = y;
    work->z = z;
    work->scale = scale;
    work->a2 = 255;
    work->rot = rot;
    work->camera = 4;
    work->s1 = 0.0f;
    work->t1 = 0.0f;
    work->s2 = 0.0f;
    work->t2 = 0.0f;
    work->ds1 = 0.0f;
    work->dt1 = 0.018181818f;
    work->ds2 = 0.0f;
    work->dt2 = 0.04f;
    if (type == 1 || type == 3) {
        work->ds1 *= -1.0f;
        work->dt1 *= -1.0f;
        work->ds2 *= -1.0f;
        work->dt2 *= -1.0f;
    }
    switch (type) {
    case 0:
        work->r1 = 255;
        work->g1 = 255;
        work->b1 = 150;
        work->r2 = 215;
        work->g2 = 210;
        work->b2 = 10;
        break;
    case 1:
        work->r1 = 230;
        work->g1 = 97;
        work->b1 = 44;
        work->r2 = 104;
        work->g2 = 47;
        work->b2 = 149;
        break;
    case 2:
        work->r1 = 255;
        work->g1 = 255;
        work->b1 = 255;
        work->r2 = 255;
        work->g2 = 255;
        work->b2 = 255;
        break;
    case 3:
    case 4:
    default:
        work->r1 = 0;
        work->g1 = 153;
        work->b1 = 255;
        work->r2 = 0;
        work->g2 = 0;
        work->b2 = 0;
        break;
    }
    p = work + 1;
    for (i = 1; i < effect->count; i++, p++) {
        switch (type) {
        case 0:
        case 1:
            p->x = 0.0f;
            p->y = 3.0f;
            p->z = 0.0f;
            p->scale = 0.0f;
            p->alpha = 204;
            p->delay = i * 30;
            p->rot = (f32)-irand(20);
            p->s1 = 8.0f;
            break;
        case 2:
            p->x = (f32)(200 - irand(400));
            p->y = -(f32)(irand(50) + 200);
            p->z = 0.0f;
            p->scale = 1.0f;
            p->alpha = 0;
            p->delay = i * 15;
            p->rot = 0.0f;
            break;
        case 3:
            rot = (f32)irand(360);
            scale = 200.0f + (f32)irand(200);
            rot = 6.2831855f * rot / 360.0f;
            p->x = scale * (f32)sin(rot);
            p->y = scale * (f32)cos(rot);
            p->z = 0.0f;
            p->scale = 2.0f;
            p->alpha = 0;
            p->delay = i * 15;
            p->rot = 0.0f;
            break;
        case 4:
        default:
            p->x = 0.0f;
            p->y = 3.0f;
            p->z = 0.0f;
            p->scale = 0.0f;
            p->alpha = 204;
            p->delay = i * 30;
            p->rot = (f32)-irand(20);
            p->s1 = 8.0f;
            break;
        }
    }
    return effect;
}

void effKumokumoMain(EffectEntry* effect) {
    EffKumokumoN64Particle* work = effect->userdata;
    Vec position;
    Vec tmp = {0.0f, 0.0f, 0.0f};
    s32 i;
    s32 type;
    CameraId camera;
    s32 fr;
    f32 ang;
    f32 rad;
    f32 tmp2;

    tmp.x = work->x;
    tmp.y = work->y;
    tmp.z = work->z;
    position = tmp;
    camera = work->camera;
    type = work->type;
    if (effect->flags & 4) {
        effect->flags &= ~4;
        work->delay = 16;
    }
    if (work->delay < 1000) {
        work->delay--;
    }
    work->frame++;
    if (work->delay < 0) {
        effDelete(effect);
        return;
    }
    fr = work->frame;
    if (work->delay < 16) {
        work->alpha = work->delay * 16;
    }
    if (fr < 16) {
        work->alpha = fr * 16 + 15;
    }
    work->s1 += work->ds1;
    work->t1 += work->dt1;
    work->s2 += work->ds2;
    work->t2 += work->dt2;
    if (type == 3) {
        work->rot -= 2.0f;
    }
    work++;
    for (i = 1; i < effect->count; i++, work++) {
        if (work->delay != 0) {
            work->delay--;
            continue;
        }
        switch (type) {
        case 0:
            work->alpha -= 2;
            if (work->alpha < 0) {
                work->x = 0.0f;
                work->y = 3.0f;
                work->z = 0.0f;
                work->scale = 0.0f;
                work->alpha = 204;
                work->delay = i * 30;
                work->rot = (f32)-irand(20);
                work->s1 = 8.0f;
            } else {
                work->scale += (1.5f - work->scale) / 30.0f;
                work->rot += (30.0f - work->rot) / 30.0f;
                work->x += work->s1 * (f32)cos(6.2831855f * work->rot / 360.0f);
                tmp2 = 2.0f * (f32)sin(6.2831855f * work->rot / 360.0f);
                work->y = work->y + tmp2 * work->s1;
                work->s1 += (2.0f - work->s1) / 30.0f;
            }
            break;
        case 2:
            work->alpha += (255 - work->alpha) / 4;
            work->scale += -work->scale / 32.0f;
            work->x += -work->x / 32.0f;
            work->y += -work->y / 32.0f;
            work->z += -work->z / 32.0f;
            if (work->scale < 0.1f) {
                work->x = (f32)(200 - irand(400));
                work->y = -(f32)(irand(50) + 200);
                work->z = 0.0f;
                work->scale = 1.0f;
                work->alpha = 0;
                work->delay = i * 15;
                work->rot = 0.0f;
            }
            work->rot = (f32)(u32)(rz_tbl[(u32)work->frame % 31] + (u32)(work->frame * 180) / 31);
            work->rot = fmod(work->rot, 360.0);
            break;
        case 3:
            work->alpha += (192 - work->alpha) / 4;
            work->scale += -work->scale / 32.0f;
            work->x += -work->x / 32.0f;
            work->y += -work->y / 32.0f;
            work->z += -work->z / 32.0f;
            if (work->scale < 0.1f) {
                ang = (f32)irand(360);
                rad = 200.0f + (f32)irand(200);
                ang = 6.2831855f * ang / 360.0f;
                work->x = rad * (f32)sin(ang);
                work->y = rad * (f32)cos(ang);
                work->z = 0.0f;
                work->scale = 3.0f;
                work->alpha = 0;
                work->delay = i * 15;
                work->rot = 0.0f;
            }
            break;
        case 4:
            work->alpha -= 2;
            if (work->alpha < 0) {
                work->x = 0.0f;
                work->y = 3.0f;
                work->z = 0.0f;
                work->scale = 0.0f;
                work->alpha = 204;
                work->delay = i * 30;
                work->rot = (f32)-irand(20);
                work->s1 = 8.0f;
            } else {
                work->scale += (1.0f - work->scale) / 30.0f;
                work->rot += (30.0f - work->rot) / 30.0f;
                work->x += work->s1 * (f32)cos(6.2831855f * work->rot / 360.0f);
                tmp2 = 2.0f * (f32)sin(6.2831855f * work->rot / 360.0f);
                work->y = work->y + tmp2 * work->s1;
                work->s1 += (2.0f - work->s1) / 30.0f;
            }
            break;
        }
        work->frame++;
    }
    dispEntry(camera, dispCalcZ(&position), 2, (DispCallback)effKumokumoDisp, effect);
}

void effKumokumoDisp(CameraId cameraId, EffectEntry* effect) {
    EffKumokumoN64Particle* work;
    s32 alpha;
    s32 type;
    CameraEntry* camera;
    EffKumokumoN64Particle* p;
    u32 i;
    s32 k;
    s32 j;
    f32 w;
    f32 h;
    f32 tmax;
    Mtx mtx;
    Mtx scl;
    Mtx rot;
    Mtx mtx2;
    GXTexObj texObj;

    work = effect->userdata;
    camera = camGetPtr(cameraId);
    alpha = work->alpha;
    type = work->type;
    PSMTXTrans(mtx, work->x, work->y, work->z);
    PSMTXRotRad(rot, 'y', 0.017453292f * -camGetPtr(cameraId)->viewYaw);
    PSMTXConcat(mtx, rot, mtx);
    PSMTXRotRad(rot, 'z', 0.017453292f * work->rot);
    PSMTXConcat(mtx, rot, mtx);
    if (type != 3) {
        if (work->rot < 90.0f) {
            PSMTXScale(scl, work->scale, work->scale, work->scale);
        } else {
            PSMTXScale(scl, work->scale, -1.0f * work->scale, work->scale);
        }
        PSMTXConcat(mtx, scl, mtx);
        PSMTXScale(scl, 0.4f, 0.4f, 0.4f);
        PSMTXConcat(mtx, scl, mtx);
    } else {
        PSMTXScale(scl, work->scale, work->scale, work->scale);
        PSMTXConcat(mtx, scl, mtx);
        PSMTXScale(scl, 0.1f, 0.1f, 0.1f);
        PSMTXConcat(mtx, scl, mtx);
    }
    PSMTXConcat(camera->view, mtx, mtx2);
    GXLoadPosMtxImm(mtx2, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetTevColor(GX_TEVREG0, (GXColor){work->r1, work->g1, work->b1, alpha});
    GXSetTevColor(GX_TEVREG1, (GXColor){work->r2, work->g2, work->b2, work->a2});
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(3);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C1, GX_CC_C0, GX_CC_TEXA, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXA, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
    effGetTexObj(0x84, &texObj);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    effGetTexObj(0x85, &texObj);
    GXLoadTexObj(&texObj, GX_TEXMAP1);
    PSMTXTrans(mtx, work->s1, work->t1, 0.0f);
    GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
    PSMTXTrans(mtx, work->s2, work->t2, 0.0f);
    GXLoadTexMtxImm(mtx, GX_TEXMTX1, GX_MTX2x4);
    GXSetCullMode(GX_CULL_NONE);
    switch (type) {
    case 0:
    case 1:
        KK_ARRAYS(cloud_vertex_tbl, cloud_texcoord0_tbl, cloud_texcoord1_tbl, cloud_normal_tbl, cloud_color0_tbl)
        for (i = 0; i < 4; i++) {
            GXCallDisplayList(cloud_dl_0_tbl[i], cloud_dl_0_size_tbl[i] << 5);
        }
        break;
    case 2:
        KK_ARRAYS(batten_vertex_tbl, batten_texcoord0_tbl, batten_texcoord1_tbl, batten_normal_tbl, batten_color0_tbl)
        for (i = 0; i < 4; i++) {
            GXCallDisplayList(batten_dl_0_tbl[i], batten_dl_0_size_tbl[i] << 5);
        }
        break;
    case 3:
        for (j = 0; j < 5; j++) {
            PSMTXRotRad(rot, 'z', 0.017453292f * (360.0f * j / 5.0f));
            PSMTXConcat(mtx2, rot, rot);
            GXLoadPosMtxImm(rot, GX_PNMTX0);
            GXSetCurrentMtx(GX_PNMTX0);
            KK_ARRAYS(cloud_vertex_tbl, cloud_texcoord0_tbl, cloud_texcoord1_tbl, cloud_normal_tbl, cloud_color0_tbl)
            for (i = 0; i < 4; i++) {
                GXCallDisplayList(cloud_dl_0_tbl[i], cloud_dl_0_size_tbl[i] << 5);
            }
        }
        break;
    case 4:
    default:
        KK_ARRAYS(cloud_vertex_tbl, cloud_texcoord0_tbl, cloud_texcoord1_tbl, cloud_normal_tbl, cloud_color0_tbl)
        for (i = 0; i < 4; i++) {
            GXCallDisplayList(cloud_dl_0_tbl[i], cloud_dl_0_size_tbl[i] << 5);
        }
        break;
    }
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    switch (type) {
    case 0:
    case 1:
        effGetTexObj(0x34, &texObj);
        GXLoadTexObj(&texObj, GX_TEXMAP0);
        break;
    case 2:
        effGetTexObj(0xB, &texObj);
        GXLoadTexObj(&texObj, GX_TEXMAP0);
        break;
    case 3:
    case 4:
    default:
        effGetTexObjN64(7, &texObj);
        GXLoadTexObj(&texObj, GX_TEXMAP0);
        break;
    }
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    for (k = 1, p = work + 1; k < effect->count; k++, p++) {
        if (p->delay == 0) {
            if (type != 3 && type != 4) {
                GXSetChanMatColor(GX_COLOR0A0, (GXColor){0xDB, 0xDF, 0xE7, p->alpha * alpha / 255});
            } else {
                GXSetChanMatColor(GX_COLOR0A0, (GXColor){0xFF, 0xFF, 0xFF, p->alpha * alpha / 255});
            }
            PSMTXTrans(mtx, p->x, p->y, p->z);
            PSMTXRotRad(rot, 'z', 0.017453292f * p->rot);
            PSMTXScale(scl, p->scale, p->scale, p->scale);
            PSMTXConcat(mtx2, mtx, mtx);
            PSMTXConcat(mtx, rot, mtx);
            PSMTXConcat(mtx, scl, mtx);
            GXLoadPosMtxImm(mtx, GX_PNMTX0);
            GXSetCurrentMtx(GX_PNMTX0);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            w = (u16)GXGetTexObjWidth(&texObj);
            h = (u16)GXGetTexObjHeight(&texObj);
            tmax = 1.0f;
            if (type == 3 || type == 4) {
                tmax = 2.0f;
            }
            GXPosition3f32(-w * 0.5f, h * 0.5f, 0.0f);
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(w * 0.5f, h * 0.5f, 0.0f);
            GXTexCoord2f32(tmax, 0.0f);
            GXPosition3f32(w * 0.5f, -h * 0.5f, 0.0f);
            GXTexCoord2f32(tmax, tmax);
            GXPosition3f32(-w * 0.5f, -h * 0.5f, 0.0f);
            GXTexCoord2f32(0.0f, tmax);
        }
    }
}

