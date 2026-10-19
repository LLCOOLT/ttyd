#include "system.h"
#include "driver/arcdrv.h"
#include "driver/mapdrv.h"
#include "manager/dvdmgr.h"
#include "memory.h"
#include "mario/mariost.h"
#ifndef NONMATCHING
__declspec(section ".rodata") extern const f32 vec3_802c12d0[3];
__declspec(section ".rodata") extern const f32 vec3_802c12dc[3];
__declspec(section ".rodata") extern const f32 vec3_802c12e8[3];
__declspec(section ".rodata") extern const f32 vec3_802c12f4[3];
__declspec(section ".rodata") extern const f64 double_1_802c1300;
__declspec(section ".rodata") extern const f64 double_0p5_802c1308;
__declspec(section ".rodata") extern const f64 double_3_802c1310;
__declspec(section ".rodata") extern const f64 double_0_802c1318;
__declspec(section ".rodata") extern const f64 double_to_int_802c1320;
__declspec(section ".rodata") extern const f64 double_0p0001_802c1328;
__declspec(section ".rodata") extern const f64 double_0p01_802c1330;
__declspec(section ".rodata") extern const f64 double_neg1Eneg07_802c1338;
__declspec(section ".rodata") extern const f64 double_1_802c1340;
__declspec(section ".rodata") extern const char str_802C1348[];
__declspec(section ".rodata") extern const char str_802C1354[];
__declspec(section ".rodata") extern const u32 gap_04_802C1364_rodata;
__declspec(section ".sdata2") extern const f32 float_0p005_80419548;
__declspec(section ".sdata2") extern const f32 float_0_8041954c;
__declspec(section ".sdata2") extern const f32 float_0p004_80419550;
__declspec(section ".sdata2") extern const f32 float_0p008_80419554;
__declspec(section ".sdata2") extern const f32 float_1_80419558;
__declspec(section ".sdata2") extern const f32 float_2_8041955c;
__declspec(section ".sdata2") extern const f32 float_3_80419560;
__declspec(section ".sdata2") extern const f32 float_10_80419564;
__declspec(section ".sdata2") extern const f32 float_3p1416_80419568;
__declspec(section ".sdata2") extern const f32 float_0p5_8041956c;
__declspec(section ".sdata2") extern const f32 float_0p5_80419570;
__declspec(section ".sdata2") extern const f32 float_6p2832_80419574;
__declspec(section ".sdata2") extern const f32 float_3p1416_80419578;
__declspec(section ".sdata2") extern const f32 float_neg3p1416_8041957c;
__declspec(section ".sdata2") extern const f32 float_rad2deg_80419580;
__declspec(section ".sdata2") extern const f32 float_360_80419584;
__declspec(section ".sdata2") extern const f32 float_180_80419588;
__declspec(section ".sdata2") extern const f32 float_0p01_8041958c;
__declspec(section ".sdata2") extern const f32 float_0p3_80419590;
__declspec(section ".sdata2") extern const f32 float_90_80419594;
__declspec(section ".sdata2") extern const f32 float_20_80419598;
__declspec(section ".sdata2") extern const f32 dat_8041959c;
__declspec(section ".sdata2") extern const f32 float_neg1E06_804195a0;
__declspec(section ".sdata2") extern const f32 float_neg1_804195a4;
__declspec(section ".sdata2") extern const f32 dat_804195a8;
__declspec(section ".sdata2") extern const f32 float_640_804195ac;
__declspec(section ".sdata2") extern const f32 float_480_804195b0;
__declspec(section ".sdata2") extern const f32 float_1E06_804195b4;
__declspec(section ".sdata2") extern const f32 float_100_804195b8;
__declspec(section ".sdata2") extern const f32 float_deg2rad_804195bc;
__declspec(section ".sdata2") extern const char str_804195C0[];
__declspec(section ".sdata2") extern const char str_804195C8[];
#define EXT_LIT(sym, val) (sym)
#define unk_vec0 (*(const Vec*)&vec3_802c12d0)
#define unk_vec1 (*(const Vec*)&vec3_802c12dc)
#define unk_vec2 (*(const Vec*)&vec3_802c12e8)
#endif
extern void camShiftInit(void);
typedef struct CamRoadCurve {
    char name[0x28];
    s32 off;               // 0x28
    u8 pad[0xb8 - 0x2c];
} CamRoadCurve;
typedef struct CamRoadCam {
    u8 pad0[0x20];
    u32 f_20;              // 0x20
    u8 pad1[0x40 - 0x24];
    s32 f_40;              // 0x40
    s32 f_44;              // 0x44
    u8 pad2[0x7c - 0x48];
    f32 f_7c;              // 0x7c
} CamRoadCam;
typedef struct CamRoadMap {
    u8 pad0[0x44];
    char version[0x84];    // 0x44
    s32 curveNum;          // 0xc8
    u8 pad1[0xe8 - 0xcc];
    Vec* f_e8;             // 0xe8
    CamRoadCurve* curves;  // 0xec
    void* f_f0;
    void* f_f4;
    void* f_f8;
    void* f_fc;
    void* f_100;
    void* f_104;
    void* f_108;
} CamRoadMap;
typedef struct CamRoadState {
    s32 on;                // 0x00
    s32 f_04;              // 0x04
    s32 f_08;              // 0x08
    f32 in[6];             // 0x0c
    CamRoadCam* cam;       // 0x24
    Vec pos;               // 0x28
    Vec dir;               // 0x34
    f32 dist;              // 0x40
    f32 angle;             // 0x44
    f32 rot;               // 0x48
    f32 f_4c;              // 0x4c
    OSTime time;           // 0x50
    f32 f_58;              // 0x58
    f32 shiftXRate;        // 0x5c
} CamRoadState;
typedef struct CamRoadOut {
    Vec f_0;
    Vec pos;               // 0xc
    Vec at;                // 0x18
} CamRoadOut;
typedef struct CamRoadWork {
    CamRoadMap* map;       // 0x0
    u8 pad0[4];
    CamRoadState cur;      // 0x8
    CamRoadState next;     // 0x68
    s32 f_c8;              // 0xc8
    s32 hokanType;         // 0xcc
    f32 hokanT;            // 0xd0
    f32 hokanSpeed;        // 0xd4
    CamRoadState prev;     // 0xd8
    CamRoadState start;    // 0x138
    u32 cmpFlags;          // 0x198
    f32 f_19c[11];         // 0x19c
    OSTime time;           // 0x1c8
    u32 state;             // 0x1d0
    u8 pad5[0x1ec - 0x1d4];
    f32 in[6];             // 0x1ec
    s32 f_204;
    s32 f_208;
    u8 pad6[0x210 - 0x20c];
} CamRoadWork;
typedef struct CamRoadCurveX {
    u8 pad0[0x20];
    u32 f_20;              // 0x20
    f32 f_24;              // 0x24
    u32 off;               // 0x28
    u8 pad1[0x58 - 0x2c];
    f32 f_58;              // 0x58
    u8 pad2[0x64 - 0x5c];
    f32 f_64;              // 0x64
    u8 pad3[0x70 - 0x68];
    f32 f_70;              // 0x70
    u8 pad4[0x7c - 0x74];
    f32 f_7c;              // 0x7c
    u8 pad5[0x8c - 0x80];
    f32 height;            // 0x8c
    u8 pad6[0xa8 - 0x90];
    s32 grpOfs;            // 0xa8
    s32 grpNum;            // 0xac
    s32 f_b0;              // 0xb0
    s32 f_b4;              // 0xb4
} CamRoadCurveX;
typedef struct CamRoadGroup {
    u8 pad0[0x58];
    s32 vtxOfs;            // 0x58
    u8 pad1[4];
    s32 stripOfs;          // 0x60
    s32 stripNum;          // 0x64
} CamRoadGroup;
typedef struct CamRoadStrip {
    s32 idxOfs;
    s32 num;
} CamRoadStrip;
typedef struct CamRoadHit {
    f32 t;                 // 0x00
    f32 f_04;              // 0x04
    f32 y;                 // 0x08
    Vec pos;               // 0x0c
    Vec dir;               // 0x18
    s32 f_24;              // 0x24
    u32 flags;             // 0x28
} CamRoadHit;
extern int strcmp(const char*, const char*);
extern void* memset(void*, int, unsigned long);
extern int sprintf(char*, const char*, ...);
double sin(double);
double cos(double);
double acos(double);
double atan2(double, double);
extern int __float_nan[];
static inline s32 cr_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 cr_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (cr_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
#ifdef NONMATCHING
static const Vec unk_vec0 = {0.0f, 1.0f, 0.0f};
static const Vec unk_vec1 = {90.0f, 110.0f, 13.0f};
static const Vec unk_vec2 = {-110.0f, -70.0f, -190.0f};
#endif
static CamRoadWork work;
static CamRoadWork* wp = &work;
void OSReport(const char* msg, ...);
void calcCurrentCamState(CamRoadOut* out);
void calcCamRoad(CamRoadState* out, CamRoadState* prev, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
u32 compareCamRoad(CamRoadState* a, CamRoadState* b, f32* speed);
void calcHokanCamRoad(s32 type, CamRoadState* from, CamRoadState* to, CamRoadState* unused, CamRoadState* out, f32 t);
static inline void crCheck(BOOL b) {}

#ifdef NONMATCHING
void camRoadStrippedReport(const char* p, s32 a, s32 b) {
    OSReport("%scam = %d\n", p, a);
    OSReport("%scurve = %d\n", p, b);
#endif
#ifndef NONMATCHING

s32 camRoadSetup(const char* name);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXRotAxisRad(Mtx m, const Vec* axis, f32 rad);
f32 PSVECMag(const Vec* v);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
s32 collisionCurve(s32 mode, void* curve, Vec pos, CamRoadHit* hit);
s32 collisionTri_simple(Vec P, Vec A, Vec B, Vec C, f32* dist);
void calcCurrentCamState(CamRoadOut* out);
#pragma dont_inline on
s32 collisionTri_simple(Vec P, Vec A, Vec B, Vec C, f32* dist);
// CC_BEGIN
typedef struct CamRoadCC {
    u8 pad0[0x40];
    s32 idxA;              // 0x40
    s32 idxB;              // 0x44
    f32 limA;              // 0x48
    f32 limB;              // 0x4c
    u8 pad1[0x84 - 0x50];
    s32 flag;              // 0x84
    u8 pad2[0xa0 - 0x88];
    s32 vtxOfs;            // 0xa0
    s32 vtxNum;            // 0xa4
} CamRoadCC;
 static inline f32 crLen2(f32 x, f32 z) {
    f32 l = x * x + z * z;
    if (l != EXT_LIT(double_0_802c1318, 0.0)) {
        l = cr_sqrtf(l);
    }
    return l;
}
s32 collisionCurve(s32 mode, void* curve, Vec pos, CamRoadHit* hit);
// CC_END
void calcCamRoad(CamRoadState* out, CamRoadState* prev, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
#pragma dont_inline reset
u32 compareCamRoad(CamRoadState* a, CamRoadState* b, f32* outSpeed);
void calcHokanCamRoad(s32 type, CamRoadState* from, CamRoadState* to, CamRoadState* unused, CamRoadState* out, f32 t);
#define CAMROAD_HOKAN_START(src, flags)                                                                     \
    {                                                                                                         \
        wp->cmpFlags = flags;                                                                                 \
        wp->f_c8 = 1;                                                                                         \
        wp->time = gp->renderFieldTime;                                                                       \
        wp->hokanT = EXT_LIT(float_0_8041954c, 0.0f);                                                                                    \
        wp->start = src;                                                                                      \
        wp->prev = wp->next;                                                                                  \
        if (wp->prev.f_08 || wp->start.f_08 ||                                                                \
            (wp->state == 0x65 &&                                                                             \
             ((wp->prev.cam && wp->prev.cam->f_20) || (wp->start.cam && wp->start.cam->f_20))) ||             \
            (wp->prev.cam && wp->prev.cam->f_7c) || (wp->start.cam && wp->start.cam->f_7c)) {                 \
            wp->hokanType = 1;                                                                                \
        } else {                                                                                              \
            wp->hokanType = 0;                                                                                \
        }                                                                                                     \
    }
void camRoadMain(CamRoadOut* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
void* camRoadGetWorkPtr(void);
f32 camRoadGetCurrentShiftXRate(void);
void camRoadReset(void);
void camRoadCurveOn(const char* name);
void camRoadCurveOff(const char* name);


// prototypes for asm stopgap forward references
void camRoadCurveOff(const char* name);
void camRoadCurveOn(const char* name);
void camRoadReset(void);
f32 camRoadGetCurrentShiftXRate(void);
void* camRoadGetWorkPtr(void);
void camRoadMain(CamRoadOut* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
void calcHokanCamRoad(s32 type, CamRoadState* from, CamRoadState* to, CamRoadState* unused, CamRoadState* out, f32 t);
u32 compareCamRoad(CamRoadState* a, CamRoadState* b, f32* outSpeed);
void calcCamRoad(CamRoadState* out, CamRoadState* prev, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
s32 collisionCurve(s32 mode, void* curve, Vec pos, CamRoadHit* hit);
s32 collisionTri_simple(Vec P, Vec A, Vec B, Vec C, f32* dist);
void calcCurrentCamState(CamRoadOut* out);
s32 camRoadSetup(const char* name);

#pragma dont_inline on
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void calcHokanCamRoad(s32 type, CamRoadState* from, CamRoadState* to, CamRoadState* unused, CamRoadState* out, f32 t) {
	asm volatile {
		opword 0x9421FFB0
		opword 0x7C0802A6
		opword 0x90010054
		opword 0xDBE10040
		opword 0xF3E10048
		opword 0xDBC10030
		opword 0xF3C10038
		opword 0xDBA10020
		opword 0xF3A10028
		opword 0x93E1001C
		opword 0x93C10018
		opword 0x93A10014
		opword 0x93810010
		opword 0xFFA00890
		lfs f1, float_0_8041954c(r2)
		opword 0x7C7C1B78
		opword 0x7C9D2378
		opword 0x7CBE2B78
		opword 0x7CFF3B78
		bl cos
		opword 0xFFE00818
		lfs f1, float_0_8041954c(r2)
		bl cos
		lfs f0, float_3p1416_80419568(r2)
		opword 0xFFC00818
		lfs f1, float_1_80419558(r2)
		opword 0xEC400772
		lfs f0, float_0_8041954c(r2)
		opword 0xEC22007A
		bl cos
		lfs f4, float_1_80419558(r2)
		opword 0xFCC00818
		lfs f5, float_2_8041955c(r2)
		opword 0xEC64F82A
		lfs f2, float_0p5_8041956c(r2)
		opword 0xEC04F028
		lfs f1, float_0p5_80419570(r2)
		opword 0xEC651824
		opword 0xEC02303A
		opword 0xEC030032
		opword 0xEC04002A
		opword 0xEC050028
		opword 0xEFE10032
		opword 0xFC1F2040
		opword 0x40810008
		opword 0xFFE02090
		opword 0x2C1C0000
		opword 0x41820044
		opword 0xC03D0028
		opword 0xC01E0028
		opword 0xEC000828
		opword 0xEC1F083A
		opword 0xD01F0028
		opword 0xC03D002C
		opword 0xC01E002C
		opword 0xEC000828
		opword 0xEC1F083A
		opword 0xD01F002C
		opword 0xC03D0030
		opword 0xC01E0030
		opword 0xEC000828
		opword 0xEC1F083A
		opword 0xD01F0030
		opword 0x4800001C
		opword 0xC01E0028
		opword 0xD01F0028
		opword 0xC01E002C
		opword 0xD01F002C
		opword 0xC01E0030
		opword 0xD01F0030
		opword 0xC03D0034
		opword 0xC05D003C
		bl atan2
		opword 0xFC000818
		opword 0xC03E0034
		opword 0xC05E003C
		opword 0xFFC00090
		bl atan2
		opword 0xFC600818
		lfs f2, float_6p2832_80419574(r2)
		lfs f0, float_3p1416_80419578(r2)
		opword 0x48000008
		opword 0xEFDE1028
		opword 0xEC3E1828
		opword 0xFC010040
		opword 0x4181FFF4
		lfs f2, float_6p2832_80419574(r2)
		lfs f0, float_neg3p1416_8041957c(r2)
		opword 0x48000008
		opword 0xEFDE102A
		opword 0xEC3E1828
		opword 0xFC010040
		opword 0x4180FFF4
		opword 0xEC03F028
		opword 0xEFDFF03A
		opword 0xFC20F090
		bl sin
		opword 0xFC000818
		opword 0xFC20F090
		opword 0xD01F0034
		bl cos
		opword 0xFC000818
		opword 0xD01F003C
		opword 0xC03D0038
		opword 0xC01E0038
		opword 0xEC000828
		opword 0xEC1F083A
		opword 0xD01F0038
		opword 0xC03D0040
		opword 0xC01E0040
		opword 0xEC000828
		opword 0xEC1F083A
		opword 0xD01F0040
		opword 0xC03D0044
		opword 0xC01E0044
		opword 0xEC000828
		opword 0xEC1F083A
		opword 0xD01F0044
		opword 0xC03D0048
		opword 0xC01E0048
		opword 0xEC000828
		opword 0xEC1F083A
		opword 0xD01F0048
		opword 0xC03D005C
		opword 0xC01E005C
		opword 0xEC000828
		opword 0xEC1F083A
		opword 0xD01F005C
		opword 0xE3E10048
		opword 0xCBE10040
		opword 0xE3C10038
		opword 0xCBC10030
		opword 0xE3A10028
		opword 0xCBA10020
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x83A10014
		opword 0x80010054
		opword 0x83810010
		opword 0x7C0803A6
		opword 0x38210050
	}
}
#pragma pop
#pragma dont_inline reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void camRoadMain(CamRoadOut* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lfs f0, float_10_80419564(r2)
		opword 0x90010014
		opword 0x93E1000C
		opword 0x7C7F1B78
		lwz r4, wp(r13)
		opword 0xD02401EC
		opword 0xEC210024
		lwz r3, wp(r13)
		opword 0xD04301F0
		lwz r3, wp(r13)
		opword 0xD06301F4
		lwz r3, wp(r13)
		opword 0xD08301F8
		opword 0xEC420024
		lwz r3, wp(r13)
		opword 0xD0A301FC
		lwz r3, wp(r13)
		opword 0xD0C30200
		lwz r4, wp(r13)
		opword 0x38640068
		opword 0xEC630024
		opword 0x388400D8
		opword 0xEC840024
		opword 0xECA50024
		opword 0xECC60024
		bl calcCamRoad
		lwz r5, wp(r13)
		opword 0x800500C8
		opword 0x2C000000
		opword 0x41820174
		opword 0x386500D8
		opword 0x38850068
		opword 0x38A500D4
		bl compareCamRoad
		opword 0x28030000
		opword 0x41820134
		lwz r5, wp(r13)
		opword 0x38800001
		lfs f0, float_0_8041954c(r2)
		opword 0x3800000C
		opword 0x90650198
		lwz r3, wp(r13)
		opword 0x908300C8
		lwz r5, gp(r13)
		lwz r3, wp(r13)
		opword 0x80850040
		opword 0x80A50044
		opword 0x90A301CC
		opword 0x908301C8
		lwz r3, wp(r13)
		opword 0xD00300D0
		lwz r3, wp(r13)
		opword 0x38A30134
		opword 0x38830004
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		lwz r3, wp(r13)
		opword 0x3800000C
		opword 0x38A300D4
		opword 0x38830064
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		lwz r3, wp(r13)
		opword 0x800300E0
		opword 0x2C000000
		opword 0x40820084
		opword 0x80030140
		opword 0x2C000000
		opword 0x40820078
		opword 0x800301D0
		opword 0x28000065
		opword 0x40820034
		opword 0x808300FC
		opword 0x28040000
		opword 0x41820010
		opword 0x80040020
		opword 0x28000000
		opword 0x40820054
		opword 0x8083015C
		opword 0x28040000
		opword 0x41820010
		opword 0x80040020
		opword 0x28000000
		opword 0x4082003C
		opword 0x808300FC
		opword 0x28040000
		opword 0x41820014
		opword 0xC024007C
		lfs f0, float_0_8041954c(r2)
		opword 0xFC010000
		opword 0x40820020
		opword 0x8083015C
		opword 0x28040000
		opword 0x41820020
		opword 0xC024007C
		lfs f0, float_0_8041954c(r2)
		opword 0xFC010000
		opword 0x41820010
		opword 0x38000001
		opword 0x900300CC
		opword 0x48000038
		opword 0x38000000
		opword 0x900300CC
		opword 0x4800002C
		lwz r3, wp(r13)
		opword 0x3800000C
		opword 0x38A300D4
		opword 0x38830064
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		lwz r5, wp(r13)
		opword 0x800500C8
		opword 0x2C000000
		opword 0x40820148
		opword 0x38650068
		opword 0x388500D8
		opword 0x38A500D4
		bl compareCamRoad
		opword 0x28030000
		opword 0x41820130
		lwz r5, wp(r13)
		opword 0x38800001
		lfs f0, float_0_8041954c(r2)
		opword 0x3800000C
		opword 0x90650198
		lwz r3, wp(r13)
		opword 0x908300C8
		lwz r5, gp(r13)
		lwz r3, wp(r13)
		opword 0x80850040
		opword 0x80A50044
		opword 0x90A301CC
		opword 0x908301C8
		lwz r3, wp(r13)
		opword 0xD00300D0
		lwz r3, wp(r13)
		opword 0x38A30134
		opword 0x388300D4
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		lwz r3, wp(r13)
		opword 0x3800000C
		opword 0x38A300D4
		opword 0x38830064
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		lwz r3, wp(r13)
		opword 0x800300E0
		opword 0x2C000000
		opword 0x40820084
		opword 0x80030140
		opword 0x2C000000
		opword 0x40820078
		opword 0x800301D0
		opword 0x28000065
		opword 0x40820034
		opword 0x808300FC
		opword 0x28040000
		opword 0x41820010
		opword 0x80040020
		opword 0x28000000
		opword 0x40820054
		opword 0x8083015C
		opword 0x28040000
		opword 0x41820010
		opword 0x80040020
		opword 0x28000000
		opword 0x4082003C
		opword 0x808300FC
		opword 0x28040000
		opword 0x41820014
		opword 0xC024007C
		lfs f0, float_0_8041954c(r2)
		opword 0xFC010000
		opword 0x40820020
		opword 0x8083015C
		opword 0x28040000
		opword 0x41820020
		opword 0xC024007C
		lfs f0, float_0_8041954c(r2)
		opword 0xFC010000
		opword 0x41820010
		opword 0x38000001
		opword 0x900300CC
		opword 0x4800000C
		opword 0x38000000
		opword 0x900300CC
		lwz r7, wp(r13)
		opword 0x800700C8
		opword 0x2C000000
		opword 0x418200EC
		lwz r6, gp(r13)
		opword 0xC02700D4
		opword 0x806701C8
		opword 0x808701CC
		opword 0x80A60040
		opword 0x80C60044
		bl getV60FPS
		lwz r3, wp(r13)
		lfs f0, float_1_80419558(r2)
		opword 0xC04300D0
		opword 0xEC22082A
		opword 0xD02300D0
		lwz r3, wp(r13)
		opword 0xC02300D0
		opword 0xFC010040
		opword 0x40810008
		opword 0xD00300D0
		lwz r4, gp(r13)
		lwz r3, wp(r13)
		opword 0x80040040
		opword 0x80840044
		opword 0x908301CC
		opword 0x900301C8
		lwz r7, wp(r13)
		opword 0x806700CC
		opword 0x38870138
		opword 0xC02700D0
		opword 0x38A700D8
		opword 0x38C70068
		opword 0x38E70008
		bl calcHokanCamRoad
		lwz r3, wp(r13)
		opword 0x800300CC
		opword 0x2C000000
		opword 0x41820010
		opword 0x38000001
		opword 0x90030010
		opword 0x4800000C
		opword 0x38000000
		opword 0x90030010
		lwz r3, wp(r13)
		lfs f1, float_1_80419558(r2)
		opword 0xC00300D0
		opword 0xFC010000
		opword 0x40820084
		opword 0x3800000C
		opword 0x38A30004
		opword 0x388300D4
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		lwz r3, wp(r13)
		opword 0x38000000
		opword 0x900300C8
		opword 0x48000050
		opword 0x3800000C
		opword 0x38A700D4
		opword 0x38870064
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		lwz r3, wp(r13)
		opword 0x3800000C
		opword 0x388700D4
		opword 0x38A30004
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		opword 0x7FE3FB78
		bl calcCurrentCamState
		opword 0xC01F0018
		lfs f1, float_10_80419564(r2)
		opword 0xEC000072
		opword 0xD01F0018
		opword 0xC01F001C
		opword 0xEC000072
		opword 0xD01F001C
		opword 0xC01F0020
		opword 0xEC000072
		opword 0xD01F0020
		opword 0xC01F000C
		opword 0xEC000072
		opword 0xD01F000C
		opword 0xC01F0010
		opword 0xEC000072
		opword 0xD01F0010
		opword 0xC01F0014
		opword 0xEC000072
		opword 0xD01F0014
		opword 0x83E1000C
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

void* camRoadGetWorkPtr(void) {
    return wp;
}

f32 camRoadGetCurrentShiftXRate(void) {
    if (wp->next.on) {
        return wp->next.shiftXRate;
    }
    return EXT_LIT(float_0_8041954c, 0.0f);
}

void camRoadReset(void) {
    s32 a = wp->f_204;
    CamRoadMap* m = wp->map;
    u32 s = wp->state;
    memset(wp, 0, 0x210);
    wp->f_c8 = 0;
    wp->prev.on = 0;
    wp->prev.on = 0;
    wp->f_19c[0] = EXT_LIT(float_0p005_80419548, 0.005f);
    wp->f_19c[1] = EXT_LIT(float_0_8041954c, 0.0f);
    wp->f_19c[2] = EXT_LIT(float_0p004_80419550, 0.004f);
    wp->f_19c[3] = EXT_LIT(float_0p008_80419554, 0.008f);
    wp->f_19c[4] = EXT_LIT(float_1_80419558, 1.0f);
    wp->f_19c[5] = EXT_LIT(float_1_80419558, 1.0f);
    wp->f_19c[6] = EXT_LIT(float_2_8041955c, 2.0f);
    wp->f_19c[7] = EXT_LIT(float_1_80419558, 1.0f);
    wp->f_19c[8] = EXT_LIT(float_1_80419558, 1.0f);
    wp->f_19c[9] = EXT_LIT(float_3_80419560, 3.0f);
    wp->f_19c[10] = EXT_LIT(float_1_80419558, 1.0f);
    wp->f_204 = -1;
    wp->f_208 = 0;
    wp->f_204 = a;
    wp->map = m;
    wp->state = s;
}

void camRoadCurveOn(const char* name) {
    CamRoadCurve* c = wp->map->curves;
    s32 i;
    if (wp->state == 0x65) {
        for (i = 0; i < wp->map->curveNum; i++, c++) {
            if (strcmp(c->name, name) == 0) {
                c->off = 0;
                break;
            }
        }
    }
}

#pragma defer_codegen off
void camRoadCurveOff(const char* name) {
    CamRoadCurve* c = wp->map->curves;
    s32 i;
    if (wp->state == 0x65) {
        for (i = 0; i < wp->map->curveNum; i++, c++) {
            if (strcmp(c->name, name) == 0) {
                c->off = 1;
                break;
            }
        }
    }
}

#pragma defer_codegen reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
asm u32 compareCamRoad(CamRoadState* a, CamRoadState* b, f32* outSpeed) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stmw r27, 0x2c(r1)
	mr r28, r4
	lis r4, vec3_802c12d0@ha
	mr r27, r3
	mr r29, r5
	li r30, 0x0
	addi r31, r4, vec3_802c12d0@l
	lwz r0, 0x0(r28)
	cmpwi r0, 0x0
	bne L_af_1
	li r3, 0x0
	b L_af_2
L_af_1:
	lwz r3, 0x24(r27)
	lwz r0, 0x24(r28)
	cmplw r3, r0
	bne L_af_3
	lwz r3, 0x4(r27)
	cmpwi r3, 0x1
	bne L_af_4
	lwz r0, 0x4(r28)
	cmpwi r0, 0x0
	beq L_af_3
L_af_4:
	cmpwi r3, 0x0
	bne L_af_5
	lwz r0, 0x8(r28)
	cmpwi r0, 0x1
	beq L_af_3
L_af_5:
	lfs f1, 0x4c(r28)
	lfs f0, 0x4c(r27)
	fctiwz f1, f1
	fctiwz f0, f0
	stfd f1, 0x10(r1)
	stfd f0, 0x18(r1)
	lwz r3, 0x14(r1)
	lwz r0, 0x1c(r1)
	subf r6, r3, r0
	srawi r3, r6, 31
	xor r0, r3, r6
	subf r0, r3, r0
	cmpwi r0, 0x1
	bgt L_af_6
	li r3, 0x0
	b L_af_2
L_af_6:
	lwz r5, 0x24(r27)
	srawi r3, r6, 31
	xor r0, r3, r6
	lwz r4, 0x40(r5)
	subf r0, r3, r0
	lwz r3, 0x44(r5)
	subf r4, r4, r3
	subi r3, r4, 0x1
	cmpw r0, r3
	blt L_af_7
	li r3, 0x0
	b L_af_2
L_af_7:
	srawi r3, r6, 31
	subi r4, r4, 0x2
	xor r0, r3, r6
	subf r0, r3, r0
	cmpw r0, r4
	blt L_af_3
	ori r30, r30, 0x20
L_af_3:
	lwz r3, 0x24(r27)
	lwz r0, 0x24(r28)
	cmplw r3, r0
	beq L_af_8
	ori r30, r30, 0x1
L_af_8:
	lwz r3, 0x4(r27)
	cmpwi r3, 0x1
	bne L_af_9
	lwz r0, 0x4(r28)
	cmpwi r0, 0x0
	bne L_af_9
	ori r30, r30, 0x2
L_af_9:
	cmpwi r3, 0x0
	bne L_af_10
	lwz r0, 0x8(r28)
	cmpwi r0, 0x1
	bne L_af_10
	ori r30, r30, 0x4
L_af_10:
	lfs f2, 0x4c(r27)
	lfs f1, 0x4c(r28)
	lfd f0, 0x30(r31)
	fsubs f1, f2, f1
	fabs f1, f1
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	mfcr r0
	extrwi. r0, r0, 1, 2
	bne L_af_11
	ori r30, r30, 0x8
L_af_11:
	lfs f1, 0x3c(r27)
	lfs f0, 0x3c(r28)
	lfs f3, 0x34(r27)
	fmuls f1, f1, f0
	lfs f2, 0x34(r28)
	lfs f0, float_1_80419558(r2)
	fmadds f1, f3, f2, f1
	fcmpo cr0, f1, f0
	ble L_af_12
	fmr f1, f0
L_af_12:
	bl acos
	frsp f2, f1
	lfs f1, float_rad2deg_80419580(r2)
	lfs f0, float_180_80419588(r2)
	fmuls f1, f1, f2
	fabs f3, f1
	fcmpo cr0, f3, f0
	ble L_af_13
	lfs f0, float_360_80419584(r2)
	fsubs f3, f0, f3
L_af_13:
	lfs f1, float_6p2832_80419574(r2)
	lfs f0, 0x40(r27)
	lwz r3, wp(r13)
	fmuls f2, f1, f0
	lfs f4, float_360_80419584(r2)
	lfs f1, 0x44(r27)
	lfs f0, 0x44(r28)
	fmuls f3, f2, f3
	lfs f2, 0x1b4(r3)
	fsubs f0, f1, f0
	lfs f1, float_180_80419588(r2)
	fdivs f3, f3, f4
	fabs f5, f0
	fmuls f0, f3, f2
	fcmpo cr0, f5, f1
	ble L_af_14
	fsubs f5, f4, f5
L_af_14:
	lfs f2, float_6p2832_80419574(r2)
	lfs f1, 0x40(r27)
	lwz r3, wp(r13)
	fmuls f3, f2, f1
	lfs f2, float_360_80419584(r2)
	lfs f1, 0x1b8(r3)
	fmuls f3, f3, f5
	fdivs f2, f3, f2
	fmuls f2, f2, f1
	fcmpo cr0, f2, f0
	ble L_af_15
	fmr f0, f2
L_af_15:
	lfs f3, 0x48(r27)
	lfs f2, 0x48(r28)
	lfs f1, float_180_80419588(r2)
	fsubs f2, f3, f2
	fabs f5, f2
	fcmpo cr0, f5, f1
	ble L_af_16
	lfs f1, float_360_80419584(r2)
	fsubs f5, f1, f5
L_af_16:
	lfs f1, float_6p2832_80419574(r2)
	lfs f4, 0x40(r27)
	lwz r3, wp(r13)
	fmuls f3, f1, f4
	lfs f2, float_360_80419584(r2)
	lfs f1, 0x1bc(r3)
	fmuls f3, f3, f5
	fdivs f2, f3, f2
	fmuls f2, f2, f1
	fcmpo cr0, f2, f0
	ble L_af_17
	fmr f0, f2
L_af_17:
	lfs f1, 0x40(r28)
	lwz r3, wp(r13)
	fsubs f2, f4, f1
	lfs f1, 0x1c0(r3)
	fabs f2, f2
	fmuls f2, f2, f1
	fcmpo cr0, f2, f0
	ble L_af_18
	fmr f0, f2
L_af_18:
	lfs f4, 0x28(r27)
	lfs f3, 0x28(r28)
	lfs f2, 0x2c(r27)
	lfs f1, 0x2c(r28)
	fsubs f4, f4, f3
	lfs f3, 0x30(r27)
	fsubs f5, f2, f1
	lfs f2, 0x30(r28)
	fmuls f6, f4, f4
	lfs f1, float_0_8041954c(r2)
	fsubs f2, f3, f2
	fmuls f3, f5, f5
	fmuls f2, f2, f2
	fadds f6, f6, f3
	fadds f6, f6, f2
	fcmpu cr0, f6, f1
	beq L_af_19
	fcmpo cr0, f6, f1
	ble L_af_20
	frsqrte f2, f6
	lfd f4, 0x38(r31)
	lfd f3, 0x40(r31)
	fmul f1, f2, f2
	fmul f2, f4, f2
	fnmsub f1, f6, f1, f3
	fmul f2, f2, f1
	fmul f1, f2, f2
	fmul f2, f4, f2
	fnmsub f1, f6, f1, f3
	fmul f2, f2, f1
	fmul f1, f2, f2
	fmul f2, f4, f2
	fnmsub f1, f6, f1, f3
	fmul f1, f2, f1
	fmul f6, f6, f1
	frsp f6, f6
	b L_af_21
L_af_20:
	lfd f1, 0x48(r31)
	fcmpo cr0, f6, f1
	bge L_af_22
	lis r3, __float_nan@ha
	lfs f6, __float_nan@l(r3)
	b L_af_21
L_af_22:
	stfs f6, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq L_af_23
	bge L_af_24
	cmpwi r3, 0x0
	beq L_af_25
	b L_af_24
L_af_23:
	clrlwi. r0, r4, 9
	beq L_af_26
	li r0, 0x1
	b L_af_27
L_af_26:
	li r0, 0x2
	b L_af_27
L_af_25:
	clrlwi. r0, r4, 9
	beq L_af_28
	li r0, 0x5
	b L_af_27
L_af_28:
	li r0, 0x3
	b L_af_27
L_af_24:
	li r0, 0x4
L_af_27:
	cmpwi r0, 0x1
	bne L_af_21
	lis r3, __float_nan@ha
	lfs f6, __float_nan@l(r3)
	b L_af_21
L_af_19:
	fmr f6, f1
L_af_21:
	lfs f1, float_0p01_8041958c(r2)
	fcmpo cr0, f0, f1
	bge L_af_29
	lfs f1, float_0p3_80419590(r2)
	fcmpo cr0, f6, f1
	bge L_af_29
	li r3, 0x0
	b L_af_2
L_af_29:
	lwz r3, wp(r13)
	lfs f1, 0x1c4(r3)
	fmuls f1, f6, f1
	fcmpo cr0, f1, f0
	ble L_af_30
	fmr f0, f1
L_af_30:
	lfs f1, float_90_80419594(r2)
	fcmpo cr0, f0, f1
	ble L_af_31
	fmr f0, f1
L_af_31:
	lfs f1, float_20_80419598(r2)
	fcmpo cr0, f0, f1
	bge L_af_32
	fmr f0, f1
L_af_32:
	lfs f1, float_1_80419558(r2)
	cmplwi r30, 0x0
	fdivs f0, f1, f0
	stfs f0, 0x0(r29)
	bne L_af_33
	ori r30, r30, 0x10
L_af_33:
	mr r3, r30
L_af_2:
	lmw r27, 0x2c(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

#pragma defer_codegen off
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void calcCamRoad(CamRoadState* out, CamRoadState* prev, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g) {
	char _af_pad[440];
	asm volatile {
		lwz r5, wp(r13)
		opword 0xFE000890
		opword 0xFE201090
		lis r6, vec3_802c12d0@ha
		opword 0x80A50000
		opword 0xFE401890
		opword 0xFE602090
		opword 0xFE802890
		opword 0xFEA03090
		addi r0, r6, vec3_802c12d0@l
		opword 0x830500EC
		opword 0xFEC03890
		lfs f0, dat_8041959c(r2)
		stfs f16, _af_pad+252(r1)
		opword 0x7C6F1B78
		opword 0x3AE00000
		opword 0xD0010010
		li r14, 0x0
		opword 0x90810008
		opword 0x900101B8
		opword 0xD2210108
		opword 0xD241010C
		opword 0xD26100F8
		opword 0xD28100FC
		opword 0xD2A10100
		opword 0x480001A8
		opword 0x807800A8
		opword 0x800501D0
		opword 0x1C630068
		opword 0x808400F0
		opword 0x28000065
		opword 0x82D800AC
		opword 0x7EA41A14
		opword 0x40820010
		opword 0x80180028
		opword 0x28000000
		opword 0x40820174
		opword 0x2C160000
		opword 0x40820028
		opword 0xC038008C
		opword 0xFC01A040
		opword 0x41810160
		opword 0xC0010010
		opword 0xFC010040
		opword 0x40810154
		opword 0xD0210010
		opword 0x7F17C378
		opword 0x48000148
		opword 0x838100F8
		opword 0x3B400000
		opword 0x83A100FC
		opword 0x83C10100
		opword 0x4800012C
		lwz r4, wp(r13)
		opword 0x3A200000
		opword 0x80750058
		opword 0x80C40000
		opword 0x80150060
		opword 0x1C83000C
		opword 0x80A600FC
		opword 0x806600F4
		opword 0x54001838
		opword 0x82750064
		opword 0x7E852214
		opword 0x7E430214
		opword 0x480000E8
		lwz r3, wp(r13)
		opword 0x3B200001
		opword 0x80120000
		opword 0x80630000
		opword 0x80920004
		opword 0x5400103A
		opword 0x80630100
		opword 0x3BE4FFFF
		opword 0x7E030214
		opword 0x3B700004
		opword 0x480000AC
		opword 0x801B0004
		opword 0x38610080
		opword 0x38810074
		opword 0x38A10068
		opword 0x1C00000C
		opword 0x38C1005C
		opword 0x38E10010
		opword 0x7D340214
		opword 0x81090000
		opword 0x80090004
		opword 0x9101005C
		opword 0x90010060
		opword 0x80090008
		opword 0x90010064
		opword 0x801B0000
		opword 0x1C00000C
		opword 0x7D340214
		opword 0x81090000
		opword 0x80090004
		opword 0x91010068
		opword 0x9001006C
		opword 0x80090008
		opword 0x90010070
		opword 0x80100000
		opword 0x1C00000C
		opword 0x7D340214
		opword 0x81090000
		opword 0x80090004
		opword 0x91010074
		opword 0x90010078
		opword 0x80090008
		opword 0x9001007C
		opword 0x93810080
		opword 0x93A10084
		opword 0x93C10088
		bl collisionTri_simple
		opword 0x2C030000
		opword 0x4182000C
		opword 0x7F17C378
		opword 0x48000014
		opword 0x3B7B0004
		opword 0x3B390001
		opword 0x7C19F800
		opword 0x4180FF54
		opword 0x3A310001
		opword 0x3A520008
		opword 0x7C119800
		opword 0x4180FF18
		opword 0x3B5A0001
		opword 0x3AB50068
		opword 0x7C1AB000
		opword 0x4180FED4
		opword 0x39CE0001
		opword 0x3B1800B8
		lwz r5, wp(r13)
		opword 0x80850000
		opword 0x800400C8
		opword 0x7C0E0000
		opword 0x4180FE4C
		opword 0x28170000
		opword 0x41820054
		lfs f0, float_0_8041954c(r2)
		opword 0x7EE4BB78
		lfs f1, float_neg1E06_804195a0(r2)
		opword 0x38A10050
		opword 0x81010104
		opword 0x38C10168
		opword 0x80E10108
		opword 0x38600000
		opword 0x8001010C
		opword 0xD0210170
		opword 0xD0010180
		opword 0xD0010184
		opword 0xD0010188
		opword 0x91010050
		opword 0x90E10054
		opword 0x90010058
		bl collisionCurve
		opword 0x2C030000
		opword 0x40820008
		opword 0x3AE00000
		opword 0x28170000
		opword 0x7EEEBB78
		opword 0x408200D4
		opword 0x80610008
		opword 0x80030000
		opword 0x2C000000
		opword 0x4182000C
		opword 0x81C30024
		opword 0x48000008
		opword 0x39C00000
		opword 0x280E0000
		opword 0x40820038
		lwz r3, wp(r13)
		opword 0xD20301D4
		lwz r3, wp(r13)
		opword 0xD22301D8
		lwz r3, wp(r13)
		opword 0xD24301DC
		lwz r3, wp(r13)
		opword 0xD26301E0
		lwz r3, wp(r13)
		opword 0xD28301E4
		lwz r3, wp(r13)
		opword 0xD2A301E8
		opword 0x4800099C
		lwz r3, wp(r13)
		opword 0xFF608090
		opword 0x800301D0
		opword 0x28000065
		opword 0x40820020
		opword 0x280E0000
		opword 0x41820018
		opword 0x800E0020
		opword 0x28000000
		opword 0x4182000C
		opword 0xC34E0024
		opword 0x48000008
		opword 0xFF408890
		opword 0x80610008
		opword 0xFF209090
		opword 0x3A000000
		opword 0xC003003C
		opword 0xC0430034
		opword 0xFFA00050
		opword 0xC0030044
		opword 0xC0230038
		opword 0xFFE01050
		opword 0xD00101B0
		opword 0xC0030048
		opword 0xFFC00850
		opword 0xC3030040
		opword 0xD00101AC
		opword 0xC003004C
		opword 0xD00101A8
		opword 0x480001B4
		opword 0xC0210168
		lfs f0, float_0_8041954c(r2)
		opword 0xFC010040
		opword 0x40800008
		opword 0xD0010168
		opword 0xC0210168
		lfs f0, float_1_80419558(r2)
		opword 0xFC010040
		opword 0x40810008
		opword 0xD0010168
		lwz r3, wp(r13)
		opword 0xC00E0064
		opword 0x800301D0
		opword 0xD00101B0
		opword 0xC00E0070
		opword 0x28000065
		opword 0xC30E0058
		opword 0xD00101AC
		opword 0xC3610174
		opword 0x40820018
		opword 0x800E0020
		opword 0x28000000
		opword 0x4182000C
		opword 0xC34E0024
		opword 0x48000008
		opword 0xFF408890
		opword 0x8061018C
		opword 0x3C004330
		opword 0xC0410180
		opword 0xC0210188
		opword 0x90010198
		opword 0x6C608000
		opword 0x806101B8
		opword 0xEC0200B2
		opword 0xFFE00850
		opword 0x9001019C
		opword 0xC8630050
		opword 0xFFA01090
		opword 0xC8210198
		opword 0xEC1F07FA
		opword 0xC8430048
		opword 0xEC211828
		opword 0xC321017C
		opword 0xFC020000
		opword 0x82010190
		opword 0xD02101A8
		opword 0xC3C10184
		opword 0x418200E4
		lfs f1, float_0_8041954c(r2)
		opword 0xFC000840
		opword 0x4081004C
		opword 0xFC400034
		opword 0xC8830038
		opword 0xC8630040
		opword 0xFC2200B2
		opword 0xFC4400B2
		opword 0xFC20187C
		opword 0xFC420072
		opword 0xFC2200B2
		opword 0xFC4400B2
		opword 0xFC20187C
		opword 0xFC420072
		opword 0xFC2200B2
		opword 0xFC4400B2
		opword 0xFC20187C
		opword 0xFC220072
		opword 0xFC000072
		opword 0xFC000018
		opword 0x48000084
		opword 0xFC001040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f0, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD001000C
		opword 0x3C007F80
		opword 0x8081000C
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
		lfs f0, __float_nan@l(r3)
		opword 0xEFFF0024
		lfs f30, float_0_8041954c(r2)
		opword 0xEFBD0024
		lfs f0, float_neg1_804195a4(r2)
		opword 0xEFFF0032
		opword 0xEFDE0032
		opword 0xEFBD0032
		opword 0x800E00B4
		opword 0x2C000000
		opword 0x41820074
		lwz r4, wp(r13)
		opword 0x38A10044
		opword 0x800E00B0
		opword 0x38C10168
		lfs f0, dat_804195a8(r2)
		opword 0x38600001
		opword 0x80840000
		opword 0x1C000068
		opword 0xD00100F0
		opword 0x80840104
		opword 0xD36100EC
		lfs f0, float_neg1E06_804195a0(r2)
		opword 0x7C840214
		opword 0xD32100F4
		opword 0x810100EC
		opword 0x80E100F0
		opword 0x800100F4
		opword 0xD0010170
		opword 0x91010044
		opword 0x90E10048
		opword 0x9001004C
		bl collisionCurve
		opword 0x2C030000
		opword 0x41820014
		opword 0x80010190
		opword 0xC3610174
		opword 0xC321017C
		opword 0x7E100378
		opword 0x280E0000
		opword 0x41820600
		lwz r3, wp(r13)
		lfs f0, float_0_8041954c(r2)
		opword 0x80630000
		lfs f1, float_0p5_8041956c(r2)
		opword 0xFC160000
		opword 0x806300E8
		lfs f0, float_180_80419588(r2)
		opword 0xC0430000
		lfs f3, float_3p1416_80419568(r2)
		opword 0xEC220072
		opword 0xEC010024
		opword 0xEEE30032
		opword 0x418205CC
		opword 0x28170000
		opword 0x418205C4
		opword 0x80610008
		opword 0x80030000
		opword 0x2C000000
		opword 0x418205B4
		opword 0xFC20B890
		bl cos
		opword 0xFDE00818
		opword 0xFC20B890
		bl sin
		opword 0xFC000818
		opword 0x80610104
		opword 0x8001010C
		opword 0xFF80E850
		opword 0x906100E0
		opword 0x7DC47378
		opword 0xEC180032
		opword 0x80610008
		opword 0x900100E8
		opword 0x38A10038
		opword 0xC0E30058
		opword 0x38C1013C
		opword 0xEC007824
		lfs f1, float_640_804195ac(r2)
		opword 0x80010108
		opword 0x3A000000
		lfs f2, float_480_804195b0(r2)
		opword 0x38600000
		opword 0xEC610032
		lfs f0, float_0_8041954c(r2)
		lfs f1, float_neg1E06_804195a0(r2)
		lfs f6, float_1_80419558(r2)
		opword 0xECA31024
		opword 0xD0210144
		lfs f8, float_0p01_8041958c(r2)
		opword 0x900100E4
		lfs f3, float_1E06_804195b4(r2)
		opword 0xD001015C
		opword 0xEC260172
		opword 0xD06100E4
		opword 0xC08100E0
		opword 0x800100E4
		opword 0xEC270072
		opword 0xD0010158
		opword 0xC04100E8
		opword 0xD0010154
		opword 0xEC680072
		opword 0x9001003C
		opword 0xEC230732
		opword 0xEC0307F2
		opword 0xEC24082A
		opword 0xEC02002A
		opword 0xD02100E0
		opword 0xD00100E8
		opword 0x80E100E0
		opword 0x800100E8
		opword 0x90E10038
		opword 0x90010040
		bl collisionCurve
		opword 0x2C030000
		opword 0x4182001C
		opword 0xC0210148
		opword 0x3A000001
		opword 0xC0010150
		opword 0xD02100E0
		opword 0xD34100E4
		opword 0xD00100E8
		opword 0x800E00B4
		opword 0x2C000000
		opword 0x4182006C
		lwz r3, wp(r13)
		opword 0x38A1002C
		opword 0x800E00B0
		opword 0x38C1013C
		opword 0x80830000
		opword 0x38600001
		opword 0x1C000068
		lfs f0, float_neg1E06_804195a0(r2)
		opword 0x80840104
		opword 0x810100E0
		opword 0x80E100E4
		opword 0x7C840214
		opword 0x800100E8
		opword 0xD0010144
		opword 0x9101002C
		opword 0x90E10030
		opword 0x90010034
		bl collisionCurve
		opword 0x2C030000
		opword 0x4182001C
		opword 0xC0210148
		opword 0x3A000001
		opword 0xC0010150
		opword 0xD02100E0
		opword 0xD34100E4
		opword 0xD00100E8
		opword 0x2C100000
		opword 0x41820010
		opword 0xC1E100E0
		lfs f14, 0xe8(r1)
		opword 0x4800000C
		opword 0xFDE0D890
		opword 0xFDC0C890
		opword 0xFC20B890
		bl cos
		opword 0xFC000818
		opword 0xFC20B890
		opword 0xD00101B4
		bl sin
		opword 0xFC000818
		lfs f1, float_0_8041954c(r2)
		opword 0x80610104
		opword 0x7DC47378
		opword 0x8001010C
		opword 0x38A10020
		opword 0xEC580032
		opword 0xC00101B4
		opword 0x906100D4
		opword 0x38C10110
		opword 0x80E10108
		opword 0x3A200000
		opword 0xEC620024
		lfs f4, float_640_804195ac(r2)
		lfs f0, float_neg1E06_804195a0(r2)
		opword 0x3A000000
		lfs f2, float_480_804195b0(r2)
		opword 0x38600000
		opword 0xEC6400F2
		lfs f6, float_1_80419558(r2)
		opword 0xD0010118
		lfs f7, float_0p01_8041958c(r2)
		opword 0xECA31024
		opword 0x900100DC
		opword 0xC08100D4
		opword 0xD0210130
		opword 0xC04100DC
		opword 0xD021012C
		opword 0xEC060172
		opword 0xD0210128
		lfs f3, float_1E06_804195b4(r2)
		opword 0x90E100D8
		opword 0xEC160032
		opword 0xD06100D8
		opword 0xEC070032
		opword 0x800100D8
		opword 0x90010024
		opword 0xEC200732
		opword 0xEC0007F2
		opword 0xEC24082A
		opword 0xEC02002A
		opword 0xD02100D4
		opword 0xD00100DC
		opword 0x80E100D4
		opword 0x800100DC
		opword 0x90E10020
		opword 0x90010028
		bl collisionCurve
		opword 0x2C030000
		opword 0x41820020
		opword 0xC021011C
		opword 0x3A200001
		opword 0xC0010124
		opword 0x82010138
		opword 0xD02100D4
		opword 0xD34100D8
		opword 0xD00100DC
		opword 0x800E00B4
		opword 0x2C000000
		opword 0x41820070
		lwz r3, wp(r13)
		opword 0x38A10014
		opword 0x800E00B0
		opword 0x38C10110
		opword 0x80830000
		opword 0x38600001
		opword 0x1C000068
		lfs f0, float_neg1E06_804195a0(r2)
		opword 0x80840104
		opword 0x810100D4
		opword 0x80E100D8
		opword 0x7C840214
		opword 0x800100DC
		opword 0xD0010118
		opword 0x91010014
		opword 0x90E10018
		opword 0x9001001C
		bl collisionCurve
		opword 0x2C030000
		opword 0x41820020
		opword 0xC021011C
		opword 0x3A200001
		opword 0xC0010124
		opword 0x80010138
		opword 0xD02100D4
		opword 0x7E100378
		opword 0xD00100DC
		opword 0x2C110000
		opword 0x41820060
		opword 0x80010138
		opword 0xC04100D4
		opword 0x540007FF
		opword 0xC08100DC
		opword 0x40820020
		opword 0x80610008
		opword 0x80030008
		opword 0x540007FF
		opword 0x41820010
		lfs f0, float_0_8041954c(r2)
		lwz r3, wp(r13)
		opword 0xD00301AC
		opword 0x80010138
		opword 0x540007BD
		opword 0x4082002C
		opword 0x80610008
		opword 0x80030008
		opword 0x540007BD
		opword 0x4182001C
		lfs f0, float_0_8041954c(r2)
		lwz r3, wp(r13)
		opword 0xD00301B0
		opword 0x4800000C
		opword 0xFC40D890
		opword 0xFC80C890
		opword 0x80610008
		lfs f3, float_0_8041954c(r2)
		opword 0xC0030028
		opword 0x386100C8
		opword 0x80810008
		opword 0xEC2F0028
		opword 0xD06100CC
		opword 0xEC020028
		opword 0xD02100C8
		opword 0xC0440030
		opword 0xEC2E1028
		opword 0xD00100BC
		opword 0xEC041028
		opword 0xD06100C0
		opword 0xD02100D0
		opword 0xD00100C4
		bl PSVECMag
		opword 0xFDC00890
		opword 0x386100BC
		bl PSVECMag
		lwz r4, wp(r13)
		lwz r6, gp(r13)
		opword 0x80610008
		opword 0xC024019C
		opword 0x80810008
		opword 0x80A60040
		opword 0x80630050
		opword 0x80840054
		opword 0x80C60044
		bl getV60FPS
		lwz r4, wp(r13)
		opword 0xEDCE082A
		lwz r6, gp(r13)
		opword 0x80610008
		opword 0xC02401A0
		opword 0x80810008
		opword 0x80A60040
		opword 0x80630050
		opword 0x80840054
		opword 0x80C60044
		bl getV60FPS
		opword 0xFC40F818
		lwz r3, wp(r13)
		opword 0xFC00E018
		lfs f5, float_0_8041954c(r2)
		opword 0xC0E301AC
		opword 0xFC801210
		opword 0xC10301B0
		opword 0xFC600210
		opword 0xFCC01050
		opword 0xEEEE01F2
		opword 0xD38100B0
		opword 0xFC041840
		opword 0xEC6101F2
		opword 0xD3E100B8
		opword 0xEC210232
		opword 0xEDCE0232
		opword 0xD0C100A4
		opword 0xD06101A4
		opword 0xD02101A0
		opword 0xD00100AC
		opword 0xD0A100B4
		opword 0xD0A100A8
		opword 0xD0A1009C
		opword 0xD0A10090
		opword 0x40810030
		opword 0xC0E100C4
		opword 0xEC601024
		opword 0xC08100BC
		opword 0xECA71024
		opword 0xFC203018
		opword 0xEC80217C
		opword 0xEC2008FC
		opword 0xECA40824
		opword 0xEC05383C
		opword 0xECC01024
		opword 0x4800002C
		opword 0xFCC03018
		opword 0xC0E100BC
		opword 0xC06100C4
		opword 0xEC870024
		opword 0xEC260024
		opword 0xEC62193C
		opword 0xEC22007C
		opword 0xECA30824
		opword 0xEC2539BC
		opword 0xECC10024
		opword 0xC02100B0
		opword 0xC04100B8
		opword 0xC00100A4
		opword 0xEC860072
		opword 0xC02100AC
		opword 0xEC6600B2
		opword 0xEC450032
		lfs f0, float_0_8041954c(r2)
		opword 0xEC250072
		opword 0xFC060040
		opword 0xD0810098
		opword 0xD06100A0
		opword 0xD041008C
		opword 0xD0210094
		opword 0x4080000C
		lfs f15, float_neg1_804195a4(r2)
		opword 0x48000008
		lfs f15, float_1_80419558(r2)
		lfs f0, float_0_8041954c(r2)
		opword 0xFC050040
		opword 0x4080000C
		lfs f28, float_neg1_804195a4(r2)
		opword 0x48000008
		lfs f28, float_1_80419558(r2)
		opword 0x38610098
		bl PSVECMag
		opword 0xFF600890
		opword 0x3861008C
		bl PSVECMag
		opword 0xFF200890
		opword 0xFC1BB840
		opword 0x40810020
		opword 0xC00101A4
		opword 0xFC1B0040
		opword 0x40810014
		opword 0xEC3703F2
		opword 0x386100B0
		opword 0x38810098
		bl PSVECScale
		opword 0xFC197040
		opword 0x40810020
		opword 0xC00101A0
		opword 0xFC190040
		opword 0x40810014
		opword 0xEC2E0732
		opword 0x386100A4
		opword 0x3881008C
		bl PSVECScale
		opword 0xC0610098
		opword 0x80610008
		opword 0xC041008C
		opword 0xC02100A0
		opword 0xC0010094
		opword 0xEC43102A
		opword 0xC3630028
		opword 0xEC01002A
		opword 0xC3230030
		opword 0xEF7B102A
		opword 0xEF39002A
		lwz r3, wp(r13)
		lfs f0, float_1_80419558(r2)
		opword 0xC04301AC
		opword 0xC02301A4
		opword 0xEC22082A
		opword 0xD02301AC
		lwz r3, wp(r13)
		opword 0xC02301AC
		opword 0xFC010040
		opword 0x40810008
		opword 0xD00301AC
		lwz r3, wp(r13)
		lfs f0, float_1_80419558(r2)
		opword 0xC04301B0
		opword 0xC02301A8
		opword 0xEC22082A
		opword 0xD02301B0
		lwz r3, wp(r13)
		opword 0xC02301B0
		opword 0xFC010040
		opword 0x40810008
		opword 0xD00301B0
		opword 0x7C1700D0
		opword 0x38600001
		opword 0x7C00BB78
		opword 0x906F0000
		opword 0x54000FFE
		opword 0xFC40F850
		opword 0x900F0004
		opword 0xFC20F050
		opword 0xFC00E850
		opword 0x920F0008
		opword 0xD20F000C
		opword 0xD22F0010
		opword 0xD24F0014
		opword 0xD26F0018
		opword 0xD28F001C
		opword 0xD2AF0020
		opword 0x91CF0024
		opword 0xD36F0028
		opword 0xD34F002C
		opword 0xD32F0030
		opword 0xD04F0034
		opword 0xD02F0038
		opword 0xD00F003C
		opword 0xC00101B0
		opword 0xD30F0040
		opword 0xD00F0044
		opword 0xC00101AC
		opword 0xD00F0048
		opword 0xC00101A8
		opword 0xD00F004C
		lwz r3, gp(r13)
		opword 0x80030040
		opword 0x80630044
		opword 0x906F0054
		opword 0x900F0050
		opword 0xD2CF0058
		opword 0xC00E007C
		opword 0xD00F005C
	}
}
#pragma pop

#pragma defer_codegen reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
asm s32 collisionCurve(s32 mode, void* curve, Vec pos, CamRoadHit* hit) {
	nofralloc
	stwu r1, -0x1a0(r1)
	mflr r0
	stw r0, 0x1a4(r1)
	stfd f31, 0x190(r1)
	psq_st f31, 0x198(r1), 0, 0
	stfd f30, 0x180(r1)
	psq_st f30, 0x188(r1), 0, 0
	stfd f29, 0x170(r1)
	psq_st f29, 0x178(r1), 0, 0
	stfd f28, 0x160(r1)
	psq_st f28, 0x168(r1), 0, 0
	stfd f27, 0x150(r1)
	psq_st f27, 0x158(r1), 0, 0
	stfd f26, 0x140(r1)
	psq_st f26, 0x148(r1), 0, 0
	stfd f25, 0x130(r1)
	psq_st f25, 0x138(r1), 0, 0
	stfd f24, 0x120(r1)
	psq_st f24, 0x128(r1), 0, 0
	stfd f23, 0x110(r1)
	psq_st f23, 0x118(r1), 0, 0
	stfd f22, 0x100(r1)
	psq_st f22, 0x108(r1), 0, 0
	stfd f21, 0xf0(r1)
	psq_st f21, 0xf8(r1), 0, 0
	stfd f20, 0xe0(r1)
	psq_st f20, 0xe8(r1), 0, 0
	stfd f19, 0xd0(r1)
	psq_st f19, 0xd8(r1), 0, 0
	stfd f18, 0xc0(r1)
	psq_st f18, 0xc8(r1), 0, 0
	stfd f17, 0xb0(r1)
	psq_st f17, 0xb8(r1), 0, 0
	stfd f16, 0xa0(r1)
	psq_st f16, 0xa8(r1), 0, 0
	stfd f15, 0x90(r1)
	psq_st f15, 0x98(r1), 0, 0
	stfd f14, 0x80(r1)
	psq_st f14, 0x88(r1), 0, 0
	stmw r15, 0x3c(r1)
	lfs f0, dat_804195a8(r2)
	cmpwi r3, 0x0
	lis r3, vec3_802c12d0@ha
	mr r16, r5
	stfs f0, 0x20(r1)
	mr r17, r6
	addi r31, r3, vec3_802c12d0@l
	li r24, 0x0
	bne L_af_1
	lwz r5, 0xa4(r4)
	li r19, 0x0
	lwz r3, wp(r13)
	srwi r0, r5, 31
	lwz r6, 0xa0(r4)
	add r0, r0, r5
	lwz r5, 0x0(r3)
	srawi r3, r0, 1
	lfs f27, 0x48(r4)
	add r0, r6, r3
	lwz r7, 0xf8(r5)
	mulli r5, r6, 0xc
	lfs f26, 0x4c(r4)
	lwz r22, 0x40(r4)
	lwz r21, 0x44(r4)
	mulli r0, r0, 0xc
	lwz r20, 0x84(r4)
	add r6, r7, r5
	add r7, r7, r0
	b L_af_2
L_af_1:
	lwz r3, 0x64(r4)
	li r22, 0x0
	lwz r5, wp(r13)
	li r21, 0x1
	srwi r0, r3, 31
	lwz r4, 0x60(r4)
	add r0, r0, r3
	lfs f27, float_0_8041954c(r2)
	srawi r3, r0, 1
	lwz r5, 0x0(r5)
	add r0, r4, r3
	fmr f26, f27
	mulli r4, r4, 0xc
	lwz r5, 0xf8(r5)
	li r20, 0x0
	li r19, 0x1
	mulli r0, r0, 0xc
	add r6, r5, r4
	add r7, r5, r0
L_af_2:
	mulli r0, r22, 0xc
	lfd f2, 0x58(r31)
	add r4, r7, r0
	lfs f0, 0x4(r4)
	mulli r5, r21, 0xc
	stfs f0, 0x28(r1)
	add r4, r7, r5
	lfs f0, 0x4(r4)
	frsp f1, f0
	stfs f0, 0x24(r1)
	lfs f0, 0x28(r1)
	fsubs f0, f1, f0
	fabs f0, f0
	fcmpo cr0, f0, f2
	bge L_af_3
	lfs f0, 0x24(r1)
	stfs f0, 0x28(r1)
L_af_3:
	cmpwi r19, 0x0
	beq L_af_4
	li r20, 0x0
L_af_4:
	lfs f0, float_0_8041954c(r2)
	mr r30, r6
	mr r29, r7
	add r28, r7, r0
	stfd f0, 0x30(r1)
	add r27, r6, r0
	add r26, r7, r5
	add r25, r6, r5
	subi r15, r3, 0x1
	li r23, 0x0
	b L_af_5
L_af_6:
	lfs f23, 0x8(r30)
	li r18, 0x0
	lfs f3, 0x8(r16)
	lfs f1, 0xc(r29)
	fsubs f0, f3, f23
	lfs f5, 0x8(r29)
	lfs f25, 0x0(r30)
	fneg f7, f1
	lfs f4, 0x0(r16)
	fmuls f0, f5, f0
	fsubs f1, f4, f25
	lfs f6, 0x0(r29)
	lfs f2, 0x14(r29)
	lfs f24, 0x4(r30)
	fmadds f1, f6, f1, f0
	lfd f0, 0x30(r1)
	fneg f8, f2
	lfs f22, 0xc(r30)
	lfs f21, 0x14(r30)
	fcmpo cr0, f1, f0
	blt L_af_7
	fsubs f0, f3, f21
	fsubs f1, f4, f22
	fmuls f0, f8, f0
	fmadds f1, f7, f1, f0
	lfd f0, 0x30(r1)
	fcmpo cr0, f1, f0
	blt L_af_7
	fneg f2, f5
	lfd f1, 0x60(r31)
	fmr f3, f6
	fmr f4, f8
	fsubs f0, f2, f8
	fneg f5, f7
	fabs f0, f0
	fcmpo cr0, f0, f1
	bge L_af_8
	fsubs f0, f6, f5
	fabs f0, f0
	fcmpo cr0, f0, f1
	bge L_af_8
	fadds f1, f2, f8
	lfs f2, float_0p5_8041956c(r2)
	fadds f0, f6, f5
	fmuls f4, f2, f1
	fmuls f5, f2, f0
	fmr f2, f4
	fmr f3, f5
L_af_8:
	fcmpu cr0, f2, f4
	bne L_af_9
	fcmpu cr0, f3, f5
	beq L_af_10
L_af_9:
	lfd f0, 0x48(r31)
	lfs f29, float_1_80419558(r2)
	fcmpu cr0, f0, f4
	stfs f29, 0x18(r1)
	beq L_af_11
	fsubs f1, f25, f22
	fdivs f0, f2, f4
	fdivs f1, f1, f4
	fmadds f1, f5, f1, f21
	fnmsubs f0, f5, f0, f3
	fsubs f1, f1, f23
	fdivs f0, f1, f0
	b L_af_12
L_af_11:
	fcmpu cr0, f0, f5
	beq L_af_13
	fsubs f1, f23, f21
	fdivs f0, f3, f5
	fdivs f1, f1, f5
	fmadds f1, f4, f1, f22
	fnmsubs f0, f4, f0, f2
	fsubs f1, f1, f25
	fdivs f0, f1, f0
	b L_af_12
L_af_13:
	lfs f0, float_0_8041954c(r2)
L_af_12:
	fmadds f20, f0, f3, f23
	lfd f1, 0x48(r31)
	fmadds f0, f0, f2, f25
	fsubs f15, f23, f20
	stfs f0, 0x1c(r1)
	frsp f0, f0
	fsubs f16, f25, f0
	fmuls f0, f15, f15
	fmadds f19, f16, f16, f0
	fcmpu cr0, f1, f19
	beq L_af_14
	lfs f0, float_0_8041954c(r2)
	fcmpo cr0, f19, f0
	ble L_af_15
	frsqrte f1, f19
	lfd f3, 0x38(r31)
	lfd f2, 0x40(r31)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f19, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f19, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f19, f0, f2
	fmul f0, f1, f0
	fmul f0, f19, f0
	frsp f0, f0
	b L_af_16
L_af_15:
	fcmpo cr0, f19, f1
	bge L_af_17
	lis r3, __float_nan@ha
	lfs f0, __float_nan@l(r3)
	b L_af_16
L_af_17:
	stfs f19, 0x14(r1)
	lis r0, 0x7f80
	lwz r4, 0x14(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq L_af_18
	bge L_af_19
	cmpwi r3, 0x0
	beq L_af_20
	b L_af_19
L_af_18:
	clrlwi. r0, r4, 9
	beq L_af_21
	li r0, 0x1
	b L_af_22
L_af_21:
	li r0, 0x2
	b L_af_22
L_af_20:
	clrlwi. r0, r4, 9
	beq L_af_23
	li r0, 0x5
	b L_af_22
L_af_23:
	li r0, 0x3
	b L_af_22
L_af_19:
	li r0, 0x4
L_af_22:
	cmpwi r0, 0x1
	bne L_af_24
	lis r3, __float_nan@ha
	lfs f0, __float_nan@l(r3)
	b L_af_16
L_af_24:
	fmr f0, f19
L_af_16:
	fmr f19, f0
L_af_14:
	lfs f0, 0x8(r16)
	lfs f2, 0x0(r16)
	fsubs f30, f0, f20
	lfs f0, 0x1c(r1)
	lfd f1, 0x48(r31)
	fsubs f31, f2, f0
	fmuls f0, f30, f30
	fmadds f17, f31, f31, f0
	fcmpu cr0, f1, f17
	beq L_af_25
	lfs f0, float_0_8041954c(r2)
	fcmpo cr0, f17, f0
	ble L_af_26
	frsqrte f1, f17
	lfd f3, 0x38(r31)
	lfd f2, 0x40(r31)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f17, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f17, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f17, f0, f2
	fmul f0, f1, f0
	fmul f0, f17, f0
	frsp f0, f0
	b L_af_27
L_af_26:
	fcmpo cr0, f17, f1
	bge L_af_28
	lis r3, __float_nan@ha
	lfs f0, __float_nan@l(r3)
	b L_af_27
L_af_28:
	stfs f17, 0x10(r1)
	lis r0, 0x7f80
	lwz r4, 0x10(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq L_af_29
	bge L_af_30
	cmpwi r3, 0x0
	beq L_af_31
	b L_af_30
L_af_29:
	clrlwi. r0, r4, 9
	beq L_af_32
	li r0, 0x1
	b L_af_33
L_af_32:
	li r0, 0x2
	b L_af_33
L_af_31:
	clrlwi. r0, r4, 9
	beq L_af_34
	li r0, 0x5
	b L_af_33
L_af_34:
	li r0, 0x3
	b L_af_33
L_af_30:
	li r0, 0x4
L_af_33:
	cmpwi r0, 0x1
	bne L_af_35
	lis r3, __float_nan@ha
	lfs f0, __float_nan@l(r3)
	b L_af_27
L_af_35:
	fmr f0, f17
L_af_27:
	fmr f17, f0
L_af_25:
	fsubs f1, f21, f20
	lfs f0, 0x1c(r1)
	lfd f3, 0x48(r31)
	fsubs f0, f22, f0
	fmuls f2, f1, f1
	fmadds f18, f0, f0, f2
	fcmpu cr0, f3, f18
	beq L_af_36
	lfs f2, float_0_8041954c(r2)
	fcmpo cr0, f18, f2
	ble L_af_37
	frsqrte f3, f18
	lfd f5, 0x38(r31)
	lfd f4, 0x40(r31)
	fmul f2, f3, f3
	fmul f3, f5, f3
	fnmsub f2, f18, f2, f4
	fmul f3, f3, f2
	fmul f2, f3, f3
	fmul f3, f5, f3
	fnmsub f2, f18, f2, f4
	fmul f3, f3, f2
	fmul f2, f3, f3
	fmul f3, f5, f3
	fnmsub f2, f18, f2, f4
	fmul f2, f3, f2
	fmul f2, f18, f2
	frsp f2, f2
	b L_af_38
L_af_37:
	fcmpo cr0, f18, f3
	bge L_af_39
	lis r3, __float_nan@ha
	lfs f2, __float_nan@l(r3)
	b L_af_38
L_af_39:
	stfs f18, 0xc(r1)
	lis r0, 0x7f80
	lwz r4, 0xc(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq L_af_40
	bge L_af_41
	cmpwi r3, 0x0
	beq L_af_42
	b L_af_41
L_af_40:
	clrlwi. r0, r4, 9
	beq L_af_43
	li r0, 0x1
	b L_af_44
L_af_43:
	li r0, 0x2
	b L_af_44
L_af_42:
	clrlwi. r0, r4, 9
	beq L_af_45
	li r0, 0x5
	b L_af_44
L_af_45:
	li r0, 0x3
	b L_af_44
L_af_41:
	li r0, 0x4
L_af_44:
	cmpwi r0, 0x1
	bne L_af_46
	lis r3, __float_nan@ha
	lfs f2, __float_nan@l(r3)
	b L_af_38
L_af_46:
	fmr f2, f18
L_af_38:
	fmr f18, f2
L_af_36:
	fmuls f3, f15, f30
	lfs f2, float_neg1_804195a4(r2)
	fmuls f1, f1, f30
	fmuls f4, f19, f17
	fmadds f5, f16, f31, f3
	fmadds f3, f0, f31, f1
	fmuls f0, f18, f17
	fdivs f1, f5, f4
	fdivs f14, f3, f0
	fcmpo cr0, f1, f2
	bge L_af_47
	fmr f1, f2
	b L_af_48
L_af_47:
	lfs f0, float_1_80419558(r2)
	fcmpo cr0, f1, f0
	ble L_af_48
	fmr f1, f0
L_af_48:
	lfs f0, float_neg1_804195a4(r2)
	fcmpo cr0, f14, f0
	bge L_af_49
	fmr f14, f0
	b L_af_50
L_af_49:
	lfs f0, float_1_80419558(r2)
	fcmpo cr0, f14, f0
	ble L_af_50
	fmr f14, f0
L_af_50:
	bl acos
	frsp f0, f1
	fmr f1, f14
	stfs f0, 0x2c(r1)
	bl acos
	frsp f3, f1
	lfs f0, 0x2c(r1)
	fsubs f4, f17, f19
	lfs f1, float_0_8041954c(r2)
	fsubs f2, f17, f18
	fadds f3, f0, f3
	fsubs f2, f2, f4
	fdivs f5, f0, f3
	fmadds f0, f5, f2, f4
	fcmpo cr0, f0, f1
	bge L_af_51
	lfs f29, float_neg1_804195a4(r2)
	fneg f0, f0
L_af_51:
	lfs f1, 0x20(r1)
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	beq L_af_7
	fsubs f3, f21, f23
	lfs f4, 0x4(r29)
	fsubs f2, f22, f25
	lfs f1, 0x10(r29)
	cmpwi r20, 0x0
	stfs f0, 0x20(r1)
	fsubs f1, f1, f4
	fneg f3, f3
	fmuls f2, f15, f2
	fmadds f1, f5, f1, f4
	fmadds f3, f16, f3, f2
	beq L_af_52
	lfs f2, 0x28(r1)
	fcmpo cr0, f1, f2
	bge L_af_53
	lfd f1, 0x48(r31)
	fcmpo cr0, f3, f1
	ble L_af_54
	lfs f1, float_0_8041954c(r2)
	fcmpo cr0, f29, f1
	bge L_af_55
	fcmpo cr0, f0, f27
	ble L_af_56
	fmr f0, f27
	ori r18, r18, 0x2
	b L_af_56
L_af_55:
	fcmpo cr0, f0, f26
	ble L_af_57
	fmr f0, f26
	ori r18, r18, 0x2
L_af_57:
	fneg f0, f0
	b L_af_56
L_af_54:
	lfs f1, float_0_8041954c(r2)
	fcmpo cr0, f29, f1
	bge L_af_58
	fcmpo cr0, f0, f26
	ble L_af_59
	fmr f0, f26
	ori r18, r18, 0x2
L_af_59:
	fneg f0, f0
	b L_af_56
L_af_58:
	fcmpo cr0, f0, f27
	ble L_af_56
	fmr f0, f27
	ori r18, r18, 0x2
L_af_56:
	lfs f1, 0x28(r1)
	ori r0, r18, 0x1
	lfs f3, float_0_8041954c(r2)
	li r24, 0x1
	stfs f1, 0x0(r17)
	lfs f2, 0x8(r28)
	lfs f1, 0x0(r27)
	fmadds f1, f0, f2, f1
	stfs f1, 0xc(r17)
	stfs f3, 0x10(r17)
	lfs f2, 0x0(r28)
	lfs f1, 0x8(r27)
	fnmsubs f0, f0, f2, f1
	stfs f0, 0x14(r17)
	lfs f0, 0x0(r28)
	stfs f0, 0x18(r17)
	stfs f3, 0x1c(r17)
	lfs f0, 0x8(r28)
	stfs f0, 0x20(r17)
	stfs f24, 0x8(r17)
	stw r22, 0x24(r17)
	stw r0, 0x28(r17)
	b L_af_7
L_af_53:
	lfs f2, 0x24(r1)
	fcmpo cr0, f1, f2
	ble L_af_60
	lfd f1, 0x48(r31)
	fcmpo cr0, f3, f1
	ble L_af_61
	lfs f1, float_0_8041954c(r2)
	fcmpo cr0, f29, f1
	bge L_af_62
	fcmpo cr0, f0, f27
	ble L_af_63
	fmr f0, f27
	ori r18, r18, 0x2
	b L_af_63
L_af_62:
	fcmpo cr0, f0, f26
	ble L_af_64
	fmr f0, f26
	ori r18, r18, 0x2
L_af_64:
	fneg f0, f0
	b L_af_63
L_af_61:
	lfs f1, float_0_8041954c(r2)
	fcmpo cr0, f29, f1
	bge L_af_65
	fcmpo cr0, f0, f26
	ble L_af_66
	fmr f0, f26
	ori r18, r18, 0x2
L_af_66:
	fneg f0, f0
	b L_af_63
L_af_65:
	fcmpo cr0, f0, f27
	ble L_af_63
	fmr f0, f27
	ori r18, r18, 0x2
L_af_63:
	lfs f1, 0x24(r1)
	ori r0, r18, 0x1
	lfs f3, float_0_8041954c(r2)
	li r24, 0x1
	stfs f1, 0x0(r17)
	lfs f2, 0x8(r26)
	lfs f1, 0x0(r25)
	fmadds f1, f0, f2, f1
	stfs f1, 0xc(r17)
	stfs f3, 0x10(r17)
	lfs f2, 0x0(r26)
	lfs f1, 0x8(r25)
	fnmsubs f0, f0, f2, f1
	stfs f0, 0x14(r17)
	lfs f0, 0x0(r26)
	stfs f0, 0x18(r17)
	stfs f3, 0x1c(r17)
	lfs f0, 0x8(r26)
	stfs f0, 0x20(r17)
	stfs f24, 0x8(r17)
	stw r21, 0x24(r17)
	stw r0, 0x28(r17)
	b L_af_7
L_af_60:
	lfd f2, 0x48(r31)
	fcmpo cr0, f3, f2
	ble L_af_67
	lfs f2, float_0_8041954c(r2)
	fcmpo cr0, f29, f2
	bge L_af_68
	fcmpo cr0, f0, f27
	ble L_af_69
	fdivs f31, f31, f17
	ori r18, r18, 0x2
	fdivs f30, f30, f17
	fsubs f0, f0, f27
	fadds f17, f17, f0
	fmuls f31, f31, f17
	fmuls f30, f30, f17
	b L_af_69
L_af_68:
	fcmpo cr0, f0, f26
	ble L_af_69
	fdivs f31, f31, f17
	ori r18, r18, 0x2
	fdivs f30, f30, f17
	fsubs f0, f0, f26
	fsubs f17, f17, f0
	fmuls f31, f31, f17
	fmuls f30, f30, f17
	b L_af_69
L_af_67:
	lfs f2, float_0_8041954c(r2)
	fcmpo cr0, f29, f2
	bge L_af_70
	fcmpo cr0, f0, f26
	ble L_af_71
	fdivs f31, f31, f17
	ori r18, r18, 0x2
	fdivs f30, f30, f17
	fsubs f0, f0, f26
	fadds f17, f17, f0
	fmuls f31, f31, f17
	fmuls f30, f30, f17
	b L_af_71
L_af_70:
	fcmpo cr0, f0, f27
	ble L_af_71
	fdivs f31, f31, f17
	ori r18, r18, 0x2
	fdivs f30, f30, f17
	fsubs f0, f0, f27
	fsubs f17, f17, f0
	fmuls f31, f31, f17
	fmuls f30, f30, f17
L_af_71:
	lfs f0, float_neg1_804195a4(r2)
	stfs f0, 0x18(r1)
	b L_af_69
L_af_52:
	cmpwi r19, 0x0
	beq L_af_72
	lfd f2, 0x48(r31)
	fcmpo cr0, f3, f2
	ble L_af_73
	lfs f2, float_0_8041954c(r2)
	fcmpo cr0, f29, f2
	blt L_af_69
	fcmpo cr0, f0, f2
	ble L_af_69
	fdivs f31, f31, f17
	li r18, 0x3
	fdivs f30, f30, f17
	fsubs f17, f17, f0
	fmuls f31, f31, f17
	fmuls f30, f30, f17
	b L_af_69
L_af_73:
	lfs f2, float_0_8041954c(r2)
	fcmpo cr0, f29, f2
	bge L_af_74
	fcmpo cr0, f0, f2
	ble L_af_74
	fdivs f31, f31, f17
	li r18, 0x3
	fdivs f30, f30, f17
	fadds f17, f17, f0
	fmuls f31, f31, f17
	fmuls f30, f30, f17
L_af_74:
	lfs f0, float_neg1_804195a4(r2)
	stfs f0, 0x18(r1)
	b L_af_69
L_af_72:
	lfd f0, 0x48(r31)
	fcmpo cr0, f3, f0
	bgt L_af_69
	lfs f0, float_neg1_804195a4(r2)
	stfs f0, 0x18(r1)
L_af_69:
	lfs f0, 0x1c(r1)
	fadds f2, f20, f30
	lfs f3, float_0_8041954c(r2)
	fadds f4, f0, f31
	lfs f0, 0x18(r1)
	fcmpo cr0, f0, f3
	stfs f4, 0xc(r17)
	stfs f3, 0x10(r17)
	stfs f2, 0x14(r17)
	bge L_af_75
	fneg f2, f30
	fdivs f0, f31, f17
	fdivs f2, f2, f17
	stfs f2, 0x18(r17)
	stfs f3, 0x1c(r17)
	stfs f0, 0x20(r17)
	b L_af_76
L_af_75:
	fdivs f2, f30, f17
	fneg f0, f31
	stfs f2, 0x18(r17)
	stfs f3, 0x1c(r17)
	fdivs f0, f0, f17
	stfs f0, 0x20(r17)
L_af_76:
	stfs f1, 0x0(r17)
	li r24, 0x1
	stfs f24, 0x8(r17)
	stw r23, 0x24(r17)
	stw r18, 0x28(r17)
	b L_af_7
L_af_10:
	lfs f0, 0x8(r30)
	lfs f1, 0x14(r30)
	lfs f10, 0x0(r30)
	fsubs f6, f1, f0
	lfs f2, 0xc(r30)
	lfs f1, 0x0(r16)
	fsubs f5, f2, f10
	lfs f2, 0x8(r16)
	fneg f7, f6
	fabs f3, f5
	fabs f4, f7
	fcmpo cr0, f4, f3
	ble L_af_77
	fsubs f4, f10, f1
	fdivs f3, f5, f7
	fdivs f4, f4, f7
	fmadds f4, f5, f4, f2
	fnmsubs f3, f5, f3, f6
	fsubs f4, f4, f0
	fdivs f4, f4, f3
	b L_af_78
L_af_77:
	lfd f3, 0x48(r31)
	fcmpu cr0, f3, f5
	beq L_af_79
	fsubs f4, f0, f2
	fdivs f3, f6, f5
	fdivs f4, f4, f5
	fmadds f4, f7, f4, f1
	fnmsubs f3, f7, f3, f5
	fsubs f4, f4, f10
	fdivs f4, f4, f3
	b L_af_78
L_af_79:
	lfs f4, float_0_8041954c(r2)
L_af_78:
	fabs f9, f5
	fabs f8, f6
	fmadds f3, f4, f5, f10
	fmadds f4, f4, f6, f0
	fcmpo cr0, f9, f8
	ble L_af_80
	fsubs f6, f3, f10
	lfd f0, 0x68(r31)
	fdivs f28, f6, f5
	fcmpo cr0, f28, f0
	blt L_af_81
	b L_af_81
L_af_80:
	lfd f8, 0x48(r31)
	fcmpu cr0, f8, f6
	beq L_af_81
	fsubs f0, f4, f0
	fdivs f28, f0, f6
L_af_81:
	fsubs f6, f2, f4
	lfs f10, 0x4(r29)
	lfs f8, 0x10(r29)
	fsubs f2, f1, f3
	lfd f9, 0x48(r31)
	fmuls f0, f6, f6
	fsubs f8, f8, f10
	fmadds f1, f2, f2, f0
	fmadds f0, f28, f8, f10
	fcmpo cr0, f1, f9
	ble L_af_82
	lfs f8, float_0_8041954c(r2)
	fcmpo cr0, f1, f8
	ble L_af_83
	frsqrte f9, f1
	lfd f11, 0x38(r31)
	lfd f10, 0x40(r31)
	fmul f8, f9, f9
	fmul f9, f11, f9
	fnmsub f8, f1, f8, f10
	fmul f9, f9, f8
	fmul f8, f9, f9
	fmul f9, f11, f9
	fnmsub f8, f1, f8, f10
	fmul f9, f9, f8
	fmul f8, f9, f9
	fmul f9, f11, f9
	fnmsub f8, f1, f8, f10
	fmul f8, f9, f8
	fmul f1, f1, f8
	frsp f1, f1
	b L_af_82
L_af_83:
	fcmpo cr0, f1, f9
	bge L_af_84
	lis r3, __float_nan@ha
	lfs f1, __float_nan@l(r3)
	b L_af_82
L_af_84:
	stfs f1, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq L_af_85
	bge L_af_86
	cmpwi r3, 0x0
	beq L_af_87
	b L_af_86
L_af_85:
	clrlwi. r0, r4, 9
	beq L_af_88
	li r0, 0x1
	b L_af_89
L_af_88:
	li r0, 0x2
	b L_af_89
L_af_87:
	clrlwi. r0, r4, 9
	beq L_af_90
	li r0, 0x5
	b L_af_89
L_af_90:
	li r0, 0x3
	b L_af_89
L_af_86:
	li r0, 0x4
L_af_89:
	cmpwi r0, 0x1
	bne L_af_82
	lis r3, __float_nan@ha
	lfs f1, __float_nan@l(r3)
L_af_82:
	lfs f8, 0x20(r1)
	fcmpo cr0, f1, f8
	cror eq, gt, eq
	beq L_af_7
	cmpwi r20, 0x0
	stfs f1, 0x20(r1)
	beq L_af_91
	lfs f8, 0x28(r1)
	fcmpo cr0, f0, f8
	bge L_af_92
	fmuls f3, f6, f5
	lfs f0, float_0_8041954c(r2)
	fmadds f2, f2, f7, f3
	fcmpo cr0, f2, f0
	bge L_af_93
	fcmpo cr0, f1, f27
	ble L_af_94
	fmr f1, f27
	ori r18, r18, 0x2
	b L_af_94
L_af_93:
	fcmpo cr0, f1, f26
	ble L_af_95
	fmr f1, f26
	ori r18, r18, 0x2
L_af_95:
	fneg f1, f1
L_af_94:
	lfs f0, 0x28(r1)
	ori r0, r18, 0x1
	lfs f3, float_0_8041954c(r2)
	li r24, 0x1
	stfs f0, 0x0(r17)
	lfs f2, 0x8(r28)
	lfs f0, 0x0(r27)
	fmadds f0, f1, f2, f0
	stfs f0, 0xc(r17)
	stfs f3, 0x10(r17)
	lfs f2, 0x0(r28)
	lfs f0, 0x8(r27)
	fnmsubs f0, f1, f2, f0
	stfs f0, 0x14(r17)
	lfs f0, 0x0(r28)
	stfs f0, 0x18(r17)
	stfs f3, 0x1c(r17)
	lfs f0, 0x8(r28)
	stfs f0, 0x20(r17)
	stfs f24, 0x8(r17)
	stw r22, 0x24(r17)
	stw r0, 0x28(r17)
	b L_af_7
L_af_92:
	lfs f8, 0x24(r1)
	fcmpo cr0, f0, f8
	ble L_af_96
	fmuls f3, f6, f5
	lfs f0, float_0_8041954c(r2)
	fmadds f2, f2, f7, f3
	fcmpo cr0, f2, f0
	bge L_af_97
	fcmpo cr0, f1, f27
	ble L_af_98
	fmr f1, f27
	ori r18, r18, 0x2
	b L_af_98
L_af_97:
	fcmpo cr0, f1, f26
	ble L_af_99
	fmr f1, f26
	ori r18, r18, 0x2
L_af_99:
	fneg f1, f1
L_af_98:
	lfs f0, 0x24(r1)
	ori r0, r18, 0x1
	lfs f3, float_0_8041954c(r2)
	li r24, 0x1
	stfs f0, 0x0(r17)
	lfs f2, 0x8(r26)
	lfs f0, 0x0(r25)
	fmadds f0, f1, f2, f0
	stfs f0, 0xc(r17)
	stfs f3, 0x10(r17)
	lfs f2, 0x0(r26)
	lfs f0, 0x8(r25)
	fnmsubs f0, f1, f2, f0
	stfs f0, 0x14(r17)
	lfs f0, 0x0(r26)
	stfs f0, 0x18(r17)
	stfs f3, 0x1c(r17)
	lfs f0, 0x8(r26)
	stfs f0, 0x20(r17)
	stfs f24, 0x8(r17)
	stw r21, 0x24(r17)
	stw r0, 0x28(r17)
	b L_af_7
L_af_96:
	fmuls f8, f6, f5
	lfs f5, float_0_8041954c(r2)
	fmadds f7, f2, f7, f8
	fcmpo cr0, f7, f5
	bge L_af_100
	fcmpo cr0, f1, f27
	ble L_af_91
	fdivs f2, f2, f1
	ori r18, r18, 0x2
	fdivs f1, f6, f1
	fmuls f2, f27, f2
	fmuls f6, f27, f1
	b L_af_91
L_af_100:
	fcmpo cr0, f1, f26
	ble L_af_91
	fdivs f2, f2, f1
	ori r18, r18, 0x2
	fdivs f1, f6, f1
	fmuls f2, f26, f2
	fmuls f6, f26, f1
L_af_91:
	fadds f2, f3, f2
	stfs f0, 0x0(r17)
	lfs f1, float_0_8041954c(r2)
	fadds f0, f4, f6
	li r24, 0x1
	stfs f2, 0xc(r17)
	stfs f1, 0x10(r17)
	stfs f0, 0x14(r17)
	lfs f2, 0x0(r29)
	lfs f0, 0xc(r29)
	fsubs f0, f0, f2
	fmadds f0, f28, f0, f2
	stfs f0, 0x18(r17)
	stfs f1, 0x1c(r17)
	lfs f1, 0x8(r29)
	lfs f0, 0x14(r29)
	fsubs f0, f0, f1
	fmadds f0, f28, f0, f1
	stfs f0, 0x20(r17)
	stfs f24, 0x8(r17)
	stw r23, 0x24(r17)
	stw r18, 0x28(r17)
L_af_7:
	addi r30, r30, 0xc
	addi r29, r29, 0xc
	addi r23, r23, 0x1
L_af_5:
	cmpw r23, r15
	blt L_af_6
	mr r3, r24
	psq_l f31, 0x198(r1), 0, 0
	lfd f31, 0x190(r1)
	psq_l f30, 0x188(r1), 0, 0
	lfd f30, 0x180(r1)
	psq_l f29, 0x178(r1), 0, 0
	lfd f29, 0x170(r1)
	psq_l f28, 0x168(r1), 0, 0
	lfd f28, 0x160(r1)
	psq_l f27, 0x158(r1), 0, 0
	lfd f27, 0x150(r1)
	psq_l f26, 0x148(r1), 0, 0
	lfd f26, 0x140(r1)
	psq_l f25, 0x138(r1), 0, 0
	lfd f25, 0x130(r1)
	psq_l f24, 0x128(r1), 0, 0
	lfd f24, 0x120(r1)
	psq_l f23, 0x118(r1), 0, 0
	lfd f23, 0x110(r1)
	psq_l f22, 0x108(r1), 0, 0
	lfd f22, 0x100(r1)
	psq_l f21, 0xf8(r1), 0, 0
	lfd f21, 0xf0(r1)
	psq_l f20, 0xe8(r1), 0, 0
	lfd f20, 0xe0(r1)
	psq_l f19, 0xd8(r1), 0, 0
	lfd f19, 0xd0(r1)
	psq_l f18, 0xc8(r1), 0, 0
	lfd f18, 0xc0(r1)
	psq_l f17, 0xb8(r1), 0, 0
	lfd f17, 0xb0(r1)
	psq_l f16, 0xa8(r1), 0, 0
	lfd f16, 0xa0(r1)
	psq_l f15, 0x98(r1), 0, 0
	lfd f15, 0x90(r1)
	psq_l f14, 0x88(r1), 0, 0
	lfd f14, 0x80(r1)
	lmw r15, 0x3c(r1)
	lwz r0, 0x1a4(r1)
	mtlr r0
	addi r1, r1, 0x1a0
	blr
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
asm s32 collisionTri_simple(Vec P, Vec A, Vec B, Vec C, f32* dist) {
	nofralloc
	stwu r1, -0x410(r1)
	lis r8, vec3_802c12f4@ha
	lwz r10, 0x0(r5)
	stmw r26, 0x3f8(r1)
	addi r28, r8, vec3_802c12f4@l
	lwz r29, 0x0(r4)
	lwz r31, 0x4(r4)
	lwz r9, 0x4(r5)
	lwz r30, 0x8(r4)
	lwz r8, 0x8(r5)
	lwz r12, 0x0(r6)
	stw r10, 0x398(r1)
	lwz r11, 0x4(r6)
	lwz r6, 0x8(r6)
	stw r29, 0x3a4(r1)
	lfs f0, 0x398(r1)
	lfs f1, 0x3a4(r1)
	stw r12, 0x3bc(r1)
	fsubs f7, f1, f0
	lwz r26, 0x0(r28)
	stw r9, 0x39c(r1)
	lfs f4, 0x3bc(r1)
	stw r31, 0x3a8(r1)
	lfs f0, 0x39c(r1)
	lwz r27, 0x4(r28)
	lfs f1, 0x3a8(r1)
	stw r31, 0x3b4(r1)
	fsubs f6, f1, f0
	lwz r28, 0x8(r28)
	stw r8, 0x3a0(r1)
	lfs f2, 0x3b4(r1)
	stw r30, 0x3ac(r1)
	lfs f0, 0x3a0(r1)
	lfs f1, 0x3ac(r1)
	stw r11, 0x3c0(r1)
	fsubs f5, f1, f0
	stw r29, 0x3b0(r1)
	lfs f3, 0x3c0(r1)
	lfs f1, 0x3b0(r1)
	stw r30, 0x3b8(r1)
	fsubs f9, f3, f2
	fsubs f10, f4, f1
	stw r6, 0x3c4(r1)
	lfs f0, 0x3b8(r1)
	lfs f1, 0x3c4(r1)
	stw r10, 0x38c(r1)
	fsubs f8, f1, f0
	stw r12, 0x380(r1)
	lfs f4, 0x38c(r1)
	stw r11, 0x384(r1)
	lfs f1, 0x380(r1)
	stw r6, 0x388(r1)
	fsubs f4, f4, f1
	lfs f2, 0x384(r1)
	stw r9, 0x390(r1)
	lfs f0, 0x388(r1)
	stw r8, 0x394(r1)
	lfs f3, 0x390(r1)
	lfs f1, 0x394(r1)
	stfs f7, 0x104(r1)
	fsubs f2, f3, f2
	fsubs f0, f1, f0
	stfs f6, 0x108(r1)
	lwz r5, 0x104(r1)
	stfs f5, 0x10c(r1)
	lwz r4, 0x108(r1)
	lwz r0, 0x10c(r1)
	stw r26, 0x3e0(r1)
	stw r27, 0x3e4(r1)
	stw r28, 0x3e8(r1)
	stw r29, 0x2c(r1)
	stw r31, 0x30(r1)
	stw r30, 0x34(r1)
	stw r12, 0x20(r1)
	stw r11, 0x24(r1)
	stw r6, 0x28(r1)
	stfs f10, 0x110(r1)
	stfs f9, 0x114(r1)
	stfs f8, 0x118(r1)
	stw r10, 0x14(r1)
	stw r9, 0x18(r1)
	stw r8, 0x1c(r1)
	stfs f4, 0xf8(r1)
	stfs f2, 0xfc(r1)
	stfs f0, 0x100(r1)
	stw r5, 0x368(r1)
	stw r4, 0x36c(r1)
	stw r0, 0x370(r1)
	lwz r0, 0x118(r1)
	lwz r4, 0x114(r1)
	stw r0, 0x37c(r1)
	lwz r0, 0x110(r1)
	lfs f6, 0x37c(r1)
	lfs f7, 0x36c(r1)
	stw r4, 0x378(r1)
	fmuls f0, f6, f7
	lfs f3, 0x370(r1)
	stw r0, 0x374(r1)
	lfs f1, 0x378(r1)
	lfs f4, 0x368(r1)
	fmsubs f5, f1, f3, f0
	lfs f2, 0x374(r1)
	fmuls f0, f1, f4
	lfs f1, float_0_8041954c(r2)
	fmuls f3, f2, f3
	stfs f5, 0xec(r1)
	fmsubs f2, f2, f7, f0
	fmsubs f0, f6, f4, f3
	lwz r0, 0xec(r1)
	stw r0, 0x3d4(r1)
	stfs f0, 0xf0(r1)
	lfs f0, 0x3d4(r1)
	stfs f2, 0xf4(r1)
	lwz r4, 0xf0(r1)
	fcmpu cr0, f1, f0
	lwz r0, 0xf4(r1)
	stw r4, 0x3d8(r1)
	stw r0, 0x3dc(r1)
	bne L_af_1
	lfs f0, 0x3d8(r1)
	fcmpu cr0, f1, f0
	bne L_af_1
	lfs f0, 0x3dc(r1)
	fcmpu cr0, f1, f0
	bne L_af_1
	li r3, 0x0
	b L_af_2
L_af_1:
	lwz r6, 0x4(r3)
	lwz r10, 0x30(r1)
	stw r6, 0x348(r1)
	lwz r8, 0x0(r3)
	stw r10, 0x33c(r1)
	lwz r11, 0x2c(r1)
	lwz r5, 0x8(r3)
	stw r11, 0x338(r1)
	lwz r9, 0x34(r1)
	stw r8, 0x344(r1)
	lfs f1, 0x348(r1)
	lfs f0, 0x33c(r1)
	stw r9, 0x340(r1)
	fsubs f0, f1, f0
	lwz r0, 0xf0(r1)
	stw r5, 0x34c(r1)
	lwz r30, 0xec(r1)
	stfs f0, 0xe4(r1)
	lwz r31, 0xf4(r1)
	lwz r3, 0xe4(r1)
	stw r0, 0x360(r1)
	lfs f1, 0x344(r1)
	lfs f0, 0x338(r1)
	stw r3, 0x354(r1)
	fsubs f3, f1, f0
	lfs f1, 0x34c(r1)
	lfs f0, 0x340(r1)
	stw r30, 0x35c(r1)
	fsubs f2, f1, f0
	lfs f1, 0x360(r1)
	stfs f3, 0xe0(r1)
	lfs f0, 0x354(r1)
	lwz r3, 0xe0(r1)
	stfs f2, 0xe8(r1)
	fmuls f0, f1, f0
	lfs f2, 0x35c(r1)
	stw r3, 0x350(r1)
	lwz r3, 0xe8(r1)
	lfs f1, 0x350(r1)
	stw r3, 0x358(r1)
	fmadds f1, f2, f1, f0
	lfs f0, float_0_8041954c(r2)
	stw r31, 0x364(r1)
	lfs f2, 0x358(r1)
	lfs f3, 0x364(r1)
	stw r8, 0x8(r1)
	fmadds f1, f3, f2, f1
	stw r6, 0xc(r1)
	fcmpo cr0, f1, f0
	stw r5, 0x10(r1)
	ble L_af_3
	lwz r3, 0x3e4(r1)
	lis r4, double_0_802c1318@ha
	stw r0, 0x330(r1)
	addi r12, r4, double_0_802c1318@l
	lwz r4, 0x3e0(r1)
	stw r3, 0x324(r1)
	lfs f2, 0x330(r1)
	lfs f0, 0x324(r1)
	stw r4, 0x320(r1)
	lwz r0, 0x3e8(r1)
	fmuls f0, f2, f0
	stw r30, 0x32c(r1)
	lfs f2, 0x320(r1)
	lfs f3, 0x32c(r1)
	stw r0, 0x328(r1)
	fmadds f2, f3, f2, f0
	lfd f0, 0x0(r12)
	stw r31, 0x334(r1)
	lfs f3, 0x328(r1)
	lfs f4, 0x334(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	cror eq, gt, eq
	bne L_af_4
	li r3, 0x0
	b L_af_2
L_af_4:
	lwz r31, 0x110(r1)
	stw r0, 0x2e0(r1)
	lwz r12, 0x118(r1)
	stw r31, 0x2e4(r1)
	lfs f9, 0x2e0(r1)
	lfs f6, 0x2e4(r1)
	stw r4, 0x2d8(r1)
	lwz r31, 0x114(r1)
	fmuls f2, f6, f9
	stw r3, 0x2dc(r1)
	lfs f5, 0x2d8(r1)
	stw r12, 0x2ec(r1)
	lfs f10, 0x2dc(r1)
	lfs f3, 0x2ec(r1)
	stw r10, 0x300(r1)
	fmsubs f7, f3, f5, f2
	stw r6, 0x30c(r1)
	fmuls f8, f3, f10
	lfs f2, 0x300(r1)
	lfs f3, 0x30c(r1)
	stw r31, 0x2e8(r1)
	fsubs f4, f3, f2
	lfs f2, 0x2e8(r1)
	stw r11, 0x2fc(r1)
	fmsubs f8, f2, f9, f8
	stw r8, 0x308(r1)
	fmuls f5, f2, f5
	lfs f2, 0x2fc(r1)
	lfs f3, 0x308(r1)
	stw r9, 0x304(r1)
	fmsubs f6, f6, f10, f5
	fsubs f5, f3, f2
	stw r5, 0x310(r1)
	lfs f2, 0x304(r1)
	stfs f7, 0xcc(r1)
	lfs f3, 0x310(r1)
	stfs f4, 0xd8(r1)
	lwz r10, 0xcc(r1)
	fsubs f4, f3, f2
	lwz r9, 0xd8(r1)
	stfs f8, 0xc8(r1)
	stfs f5, 0xd4(r1)
	lwz r12, 0xc8(r1)
	stw r10, 0x2f4(r1)
	lwz r10, 0xd4(r1)
	stw r9, 0x318(r1)
	lfs f2, 0x2f4(r1)
	stfs f6, 0xd0(r1)
	lfs f3, 0x318(r1)
	stfs f4, 0xdc(r1)
	lwz r11, 0xd0(r1)
	fmuls f2, f3, f2
	stw r12, 0x2f0(r1)
	lwz r9, 0xdc(r1)
	stw r10, 0x314(r1)
	lfs f3, 0x2f0(r1)
	lfs f4, 0x314(r1)
	stw r11, 0x2f8(r1)
	fmadds f2, f4, f3, f2
	stw r9, 0x31c(r1)
	lfs f3, 0x2f8(r1)
	lfs f4, 0x31c(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	ble L_af_5
	li r3, 0x0
	b L_af_2
L_af_5:
	lwz r10, 0x104(r1)
	stw r0, 0x298(r1)
	lwz r9, 0x10c(r1)
	stw r10, 0x29c(r1)
	lwz r10, 0x18(r1)
	stw r4, 0x290(r1)
	lwz r12, 0x108(r1)
	stw r3, 0x294(r1)
	lwz r11, 0x14(r1)
	stw r9, 0x2a4(r1)
	lwz r9, 0x1c(r1)
	stw r10, 0x2b8(r1)
	lfs f8, 0x298(r1)
	lfs f6, 0x29c(r1)
	stw r6, 0x2c4(r1)
	fmuls f2, f6, f8
	lfs f3, 0x2a4(r1)
	lfs f10, 0x294(r1)
	lfs f5, 0x290(r1)
	stw r12, 0x2a0(r1)
	fmuls f4, f3, f10
	fmsubs f7, f3, f5, f2
	lfs f3, 0x2c4(r1)
	lfs f9, 0x2a0(r1)
	lfs f2, 0x2b8(r1)
	stw r11, 0x2b4(r1)
	fmsubs f8, f9, f8, f4
	fsubs f4, f3, f2
	stw r8, 0x2c0(r1)
	fmuls f5, f9, f5
	lfs f2, 0x2b4(r1)
	lfs f3, 0x2c0(r1)
	stw r9, 0x2bc(r1)
	fmsubs f6, f6, f10, f5
	fsubs f5, f3, f2
	stw r5, 0x2c8(r1)
	lfs f2, 0x2bc(r1)
	stfs f7, 0xb4(r1)
	lfs f3, 0x2c8(r1)
	stfs f4, 0xc0(r1)
	lwz r10, 0xb4(r1)
	fsubs f4, f3, f2
	lwz r9, 0xc0(r1)
	stfs f8, 0xb0(r1)
	stfs f5, 0xbc(r1)
	lwz r12, 0xb0(r1)
	stw r10, 0x2ac(r1)
	lwz r10, 0xbc(r1)
	stw r9, 0x2d0(r1)
	lfs f2, 0x2ac(r1)
	stfs f6, 0xb8(r1)
	lfs f3, 0x2d0(r1)
	stfs f4, 0xc4(r1)
	lwz r11, 0xb8(r1)
	fmuls f2, f3, f2
	stw r12, 0x2a8(r1)
	lwz r9, 0xc4(r1)
	stw r10, 0x2cc(r1)
	lfs f3, 0x2a8(r1)
	lfs f4, 0x2cc(r1)
	stw r11, 0x2b0(r1)
	fmadds f2, f4, f3, f2
	stw r9, 0x2d4(r1)
	lfs f3, 0x2b0(r1)
	lfs f4, 0x2d4(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	ble L_af_6
	li r3, 0x0
	b L_af_2
L_af_6:
	lwz r9, 0xf8(r1)
	stw r0, 0x250(r1)
	lwz r0, 0x100(r1)
	stw r9, 0x254(r1)
	lwz r9, 0x24(r1)
	stw r4, 0x248(r1)
	lwz r4, 0xfc(r1)
	stw r3, 0x24c(r1)
	lwz r3, 0x20(r1)
	stw r0, 0x25c(r1)
	lwz r0, 0x28(r1)
	stw r9, 0x270(r1)
	lfs f8, 0x250(r1)
	lfs f6, 0x254(r1)
	stw r6, 0x27c(r1)
	fmuls f2, f6, f8
	lfs f3, 0x25c(r1)
	lfs f10, 0x24c(r1)
	lfs f5, 0x248(r1)
	stw r4, 0x258(r1)
	fmuls f4, f3, f10
	fmsubs f7, f3, f5, f2
	lfs f3, 0x27c(r1)
	lfs f9, 0x258(r1)
	lfs f2, 0x270(r1)
	stw r3, 0x26c(r1)
	fmsubs f8, f9, f8, f4
	fsubs f4, f3, f2
	stw r8, 0x278(r1)
	fmuls f5, f9, f5
	lfs f2, 0x26c(r1)
	lfs f3, 0x278(r1)
	stw r0, 0x274(r1)
	fmsubs f6, f6, f10, f5
	fsubs f5, f3, f2
	stw r5, 0x280(r1)
	lfs f2, 0x274(r1)
	stfs f7, 0x9c(r1)
	lfs f3, 0x280(r1)
	stfs f4, 0xa8(r1)
	lwz r3, 0x9c(r1)
	fsubs f4, f3, f2
	lwz r0, 0xa8(r1)
	stfs f8, 0x98(r1)
	stfs f5, 0xa4(r1)
	lwz r5, 0x98(r1)
	stw r3, 0x264(r1)
	lwz r3, 0xa4(r1)
	stw r0, 0x288(r1)
	lfs f2, 0x264(r1)
	stfs f6, 0xa0(r1)
	lfs f3, 0x288(r1)
	stfs f4, 0xac(r1)
	lwz r4, 0xa0(r1)
	fmuls f2, f3, f2
	stw r5, 0x260(r1)
	lwz r0, 0xac(r1)
	stw r3, 0x284(r1)
	lfs f3, 0x260(r1)
	lfs f4, 0x284(r1)
	stw r4, 0x268(r1)
	fmadds f2, f4, f3, f2
	stw r0, 0x28c(r1)
	lfs f3, 0x268(r1)
	lfs f4, 0x28c(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	ble L_af_7
	li r3, 0x0
	b L_af_2
L_af_3:
	lwz r3, 0x3e4(r1)
	lis r4, double_0_802c1318@ha
	stw r0, 0x240(r1)
	addi r12, r4, double_0_802c1318@l
	lwz r4, 0x3e0(r1)
	stw r3, 0x234(r1)
	lfs f2, 0x240(r1)
	lfs f0, 0x234(r1)
	stw r4, 0x230(r1)
	lwz r0, 0x3e8(r1)
	fmuls f0, f2, f0
	stw r30, 0x23c(r1)
	lfs f2, 0x230(r1)
	lfs f3, 0x23c(r1)
	stw r0, 0x238(r1)
	fmadds f2, f3, f2, f0
	lfd f0, 0x0(r12)
	stw r31, 0x244(r1)
	lfs f3, 0x238(r1)
	lfs f4, 0x244(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	bne L_af_8
	li r3, 0x0
	b L_af_2
L_af_8:
	lwz r31, 0x110(r1)
	stw r0, 0x1f0(r1)
	lwz r12, 0x118(r1)
	stw r31, 0x1f4(r1)
	lfs f9, 0x1f0(r1)
	lfs f6, 0x1f4(r1)
	stw r4, 0x1e8(r1)
	lwz r31, 0x114(r1)
	fmuls f2, f6, f9
	stw r3, 0x1ec(r1)
	lfs f5, 0x1e8(r1)
	stw r12, 0x1fc(r1)
	lfs f10, 0x1ec(r1)
	lfs f3, 0x1fc(r1)
	stw r10, 0x210(r1)
	fmsubs f7, f3, f5, f2
	stw r6, 0x21c(r1)
	fmuls f8, f3, f10
	lfs f2, 0x210(r1)
	lfs f3, 0x21c(r1)
	stw r31, 0x1f8(r1)
	fsubs f4, f3, f2
	lfs f2, 0x1f8(r1)
	stw r11, 0x20c(r1)
	fmsubs f8, f2, f9, f8
	stw r8, 0x218(r1)
	fmuls f5, f2, f5
	lfs f2, 0x20c(r1)
	lfs f3, 0x218(r1)
	stw r9, 0x214(r1)
	fmsubs f6, f6, f10, f5
	fsubs f5, f3, f2
	stw r5, 0x220(r1)
	lfs f2, 0x214(r1)
	stfs f7, 0x84(r1)
	lfs f3, 0x220(r1)
	stfs f4, 0x90(r1)
	lwz r10, 0x84(r1)
	fsubs f4, f3, f2
	lwz r9, 0x90(r1)
	stfs f8, 0x80(r1)
	stfs f5, 0x8c(r1)
	lwz r12, 0x80(r1)
	stw r10, 0x204(r1)
	lwz r10, 0x8c(r1)
	stw r9, 0x228(r1)
	lfs f2, 0x204(r1)
	stfs f6, 0x88(r1)
	lfs f3, 0x228(r1)
	stfs f4, 0x94(r1)
	lwz r11, 0x88(r1)
	fmuls f2, f3, f2
	stw r12, 0x200(r1)
	lwz r9, 0x94(r1)
	stw r10, 0x224(r1)
	lfs f3, 0x200(r1)
	lfs f4, 0x224(r1)
	stw r11, 0x208(r1)
	fmadds f2, f4, f3, f2
	stw r9, 0x22c(r1)
	lfs f3, 0x208(r1)
	lfs f4, 0x22c(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	bge L_af_9
	li r3, 0x0
	b L_af_2
L_af_9:
	lwz r10, 0x104(r1)
	stw r0, 0x1a8(r1)
	lwz r9, 0x10c(r1)
	stw r10, 0x1ac(r1)
	lwz r10, 0x18(r1)
	stw r4, 0x1a0(r1)
	lwz r12, 0x108(r1)
	stw r3, 0x1a4(r1)
	lwz r11, 0x14(r1)
	stw r9, 0x1b4(r1)
	lwz r9, 0x1c(r1)
	stw r10, 0x1c8(r1)
	lfs f8, 0x1a8(r1)
	lfs f6, 0x1ac(r1)
	stw r6, 0x1d4(r1)
	fmuls f2, f6, f8
	lfs f3, 0x1b4(r1)
	lfs f10, 0x1a4(r1)
	lfs f5, 0x1a0(r1)
	stw r12, 0x1b0(r1)
	fmuls f4, f3, f10
	fmsubs f7, f3, f5, f2
	lfs f3, 0x1d4(r1)
	lfs f9, 0x1b0(r1)
	lfs f2, 0x1c8(r1)
	stw r11, 0x1c4(r1)
	fmsubs f8, f9, f8, f4
	fsubs f4, f3, f2
	stw r8, 0x1d0(r1)
	fmuls f5, f9, f5
	lfs f2, 0x1c4(r1)
	lfs f3, 0x1d0(r1)
	stw r9, 0x1cc(r1)
	fmsubs f6, f6, f10, f5
	fsubs f5, f3, f2
	stw r5, 0x1d8(r1)
	lfs f2, 0x1cc(r1)
	stfs f7, 0x6c(r1)
	lfs f3, 0x1d8(r1)
	stfs f4, 0x78(r1)
	lwz r10, 0x6c(r1)
	fsubs f4, f3, f2
	lwz r9, 0x78(r1)
	stfs f8, 0x68(r1)
	stfs f5, 0x74(r1)
	lwz r12, 0x68(r1)
	stw r10, 0x1bc(r1)
	lwz r10, 0x74(r1)
	stw r9, 0x1e0(r1)
	lfs f2, 0x1bc(r1)
	stfs f6, 0x70(r1)
	lfs f3, 0x1e0(r1)
	stfs f4, 0x7c(r1)
	lwz r11, 0x70(r1)
	fmuls f2, f3, f2
	stw r12, 0x1b8(r1)
	lwz r9, 0x7c(r1)
	stw r10, 0x1dc(r1)
	lfs f3, 0x1b8(r1)
	lfs f4, 0x1dc(r1)
	stw r11, 0x1c0(r1)
	fmadds f2, f4, f3, f2
	stw r9, 0x1e4(r1)
	lfs f3, 0x1c0(r1)
	lfs f4, 0x1e4(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	bge L_af_10
	li r3, 0x0
	b L_af_2
L_af_10:
	lwz r9, 0xf8(r1)
	stw r0, 0x160(r1)
	lwz r0, 0x100(r1)
	stw r9, 0x164(r1)
	lwz r9, 0x24(r1)
	stw r4, 0x158(r1)
	lwz r4, 0xfc(r1)
	stw r3, 0x15c(r1)
	lwz r3, 0x20(r1)
	stw r0, 0x16c(r1)
	lwz r0, 0x28(r1)
	stw r9, 0x180(r1)
	lfs f8, 0x160(r1)
	lfs f6, 0x164(r1)
	stw r6, 0x18c(r1)
	fmuls f2, f6, f8
	lfs f3, 0x16c(r1)
	lfs f10, 0x15c(r1)
	lfs f5, 0x158(r1)
	stw r4, 0x168(r1)
	fmuls f4, f3, f10
	fmsubs f7, f3, f5, f2
	lfs f3, 0x18c(r1)
	lfs f9, 0x168(r1)
	lfs f2, 0x180(r1)
	stw r3, 0x17c(r1)
	fmsubs f8, f9, f8, f4
	fsubs f4, f3, f2
	stw r8, 0x188(r1)
	fmuls f5, f9, f5
	lfs f2, 0x17c(r1)
	lfs f3, 0x188(r1)
	stw r0, 0x184(r1)
	fmsubs f6, f6, f10, f5
	fsubs f5, f3, f2
	stw r5, 0x190(r1)
	lfs f2, 0x184(r1)
	stfs f7, 0x54(r1)
	lfs f3, 0x190(r1)
	stfs f4, 0x60(r1)
	lwz r3, 0x54(r1)
	fsubs f4, f3, f2
	lwz r0, 0x60(r1)
	stfs f8, 0x50(r1)
	stfs f5, 0x5c(r1)
	lwz r5, 0x50(r1)
	stw r3, 0x174(r1)
	lwz r3, 0x5c(r1)
	stw r0, 0x198(r1)
	lfs f2, 0x174(r1)
	stfs f6, 0x58(r1)
	lfs f3, 0x198(r1)
	stfs f4, 0x64(r1)
	lwz r4, 0x58(r1)
	fmuls f2, f3, f2
	stw r5, 0x170(r1)
	lwz r0, 0x64(r1)
	stw r3, 0x194(r1)
	lfs f3, 0x170(r1)
	lfs f4, 0x194(r1)
	stw r4, 0x178(r1)
	fmadds f2, f4, f3, f2
	stw r0, 0x19c(r1)
	lfs f3, 0x178(r1)
	lfs f4, 0x19c(r1)
	fmadds f2, f4, f3, f2
	fcmpo cr0, f2, f0
	bge L_af_7
	li r3, 0x0
	b L_af_2
L_af_7:
	lwz r5, 0x3e4(r1)
	fneg f3, f1
	lwz r0, 0xf0(r1)
	stw r5, 0x144(r1)
	lwz r6, 0x3e0(r1)
	stw r0, 0x150(r1)
	lwz r3, 0xec(r1)
	lwz r4, 0x3e8(r1)
	stw r6, 0x140(r1)
	lwz r0, 0xf4(r1)
	stw r3, 0x14c(r1)
	lfs f1, 0x150(r1)
	lfs f0, 0x144(r1)
	stw r4, 0x148(r1)
	fmuls f0, f1, f0
	lfs f2, 0x14c(r1)
	lfs f1, 0x140(r1)
	stw r0, 0x154(r1)
	fmadds f0, f2, f1, f0
	lfs f1, 0x148(r1)
	lfs f2, 0x154(r1)
	stw r5, 0x120(r1)
	fmadds f0, f2, f1, f0
	lwz r0, 0xc(r1)
	stw r6, 0x11c(r1)
	lwz r3, 0x8(r1)
	fdivs f5, f3, f0
	lfs f1, 0x120(r1)
	stw r4, 0x124(r1)
	lfs f2, 0x11c(r1)
	lfs f0, 0x124(r1)
	stw r0, 0x138(r1)
	fmuls f3, f1, f5
	lwz r0, 0x10(r1)
	fmuls f4, f2, f5
	lfs f2, 0x138(r1)
	fmuls f1, f0, f5
	stw r3, 0x134(r1)
	stfs f3, 0x48(r1)
	lfs f3, 0x134(r1)
	lwz r3, 0x48(r1)
	stfs f4, 0x44(r1)
	lfs f0, 0x0(r7)
	stw r3, 0x12c(r1)
	lwz r4, 0x44(r1)
	stfs f1, 0x4c(r1)
	lfs f1, 0x12c(r1)
	lwz r3, 0x4c(r1)
	fadds f2, f2, f1
	stw r4, 0x128(r1)
	stw r3, 0x130(r1)
	lfs f1, 0x128(r1)
	stw r0, 0x13c(r1)
	fadds f3, f3, f1
	lfs f1, 0x130(r1)
	stfs f2, 0x3c(r1)
	lfs f2, 0x13c(r1)
	lwz r0, 0x3c(r1)
	fadds f1, f2, f1
	stfs f3, 0x38(r1)
	stw r0, 0x3cc(r1)
	lwz r3, 0x38(r1)
	stfs f1, 0x40(r1)
	lfs f1, 0x3cc(r1)
	lwz r0, 0x40(r1)
	fcmpo cr0, f1, f0
	stw r3, 0x3c8(r1)
	stw r0, 0x3d0(r1)
	bge L_af_11
	li r3, 0x0
	b L_af_2
L_af_11:
	stfs f1, 0x0(r7)
	li r3, 0x1
L_af_2:
	lmw r26, 0x3f8(r1)
	addi r1, r1, 0x410
	blr
#endif
}

s32 camRoadSetup(const char* name) {
    char path[128];
    u32 size;
    DVDEntry* entry;
#ifdef NONMATCHING
    crCheck((BOOL)"%scam = %d\n");
#endif
#ifndef NONMATCHING
    crCheck((BOOL)EXT_LIT((char*)str_802C1348, "%scam = %d\n"));
#endif
    crCheck((BOOL)"%scurve = %d\n\0\0");
    memset(wp, 0, 0x210);
    wp->f_c8 = 0;
    wp->prev.on = 0;
    wp->prev.on = 0;
#ifdef NONMATCHING
    wp->f_19c[0] = 0.005f;
    wp->f_19c[1] = 0.0f;
    wp->f_19c[2] = 0.004f;
    wp->f_19c[3] = 0.008f;
    wp->f_19c[4] = 1.0f;
    wp->f_19c[5] = 1.0f;
    wp->f_19c[6] = 2.0f;
    wp->f_19c[7] = 1.0f;
    wp->f_19c[8] = 1.0f;
    wp->f_19c[9] = 3.0f;
    wp->f_19c[10] = 1.0f;
#endif
#ifndef NONMATCHING
    wp->f_19c[0] = EXT_LIT(float_0p005_80419548, 0.005f);
    wp->f_19c[1] = EXT_LIT(float_0_8041954c, 0.0f);
    wp->f_19c[2] = EXT_LIT(float_0p004_80419550, 0.004f);
    wp->f_19c[3] = EXT_LIT(float_0p008_80419554, 0.008f);
    wp->f_19c[4] = EXT_LIT(float_1_80419558, 1.0f);
    wp->f_19c[5] = EXT_LIT(float_1_80419558, 1.0f);
    wp->f_19c[6] = EXT_LIT(float_2_8041955c, 2.0f);
    wp->f_19c[7] = EXT_LIT(float_1_80419558, 1.0f);
    wp->f_19c[8] = EXT_LIT(float_1_80419558, 1.0f);
    wp->f_19c[9] = EXT_LIT(float_3_80419560, 3.0f);
    wp->f_19c[10] = EXT_LIT(float_1_80419558, 1.0f);
#endif
    wp->f_204 = -1;
    wp->f_208 = 0;
    camShiftInit();
    arcOpen(name, (void**)&wp->map, &size);
    if (!wp->map) {
#ifdef NONMATCHING
        sprintf(path, "%s/%s", getMapDataDvdRoot(), name);
#endif
#ifndef NONMATCHING
        sprintf(path, EXT_LIT((char*)str_804195C0, "%s/%s"), getMapDataDvdRoot(), name);
#endif
        entry = DVDMgrOpen(path, 2, 0);
        if (entry) {
            size = DVDMgrGetLength(entry);
            wp->map = _mapAlloc((size + 0x1f) & ~0x1f);
            DVDMgrRead(entry, wp->map, (size + 0x1f) & ~0x1f, 0);
            DVDMgrClose(entry);
        } else {
            return 0;
        }
    }
    if ((u32)wp->map->f_e8 < (u32)wp->map) {
        wp->map->f_e8 = (Vec*)((u32)wp->map->f_e8 + (u32)wp->map);
        wp->map->curves = (CamRoadCurve*)((u32)wp->map->curves + (u32)wp->map);
        wp->map->f_f0 = (void*)((u32)wp->map->f_f0 + (u32)wp->map);
        wp->map->f_f4 = (void*)((u32)wp->map->f_f4 + (u32)wp->map);
        wp->map->f_f8 = (void*)((u32)wp->map->f_f8 + (u32)wp->map);
        wp->map->f_fc = (void*)((u32)wp->map->f_fc + (u32)wp->map);
        wp->map->f_100 = (void*)((u32)wp->map->f_100 + (u32)wp->map);
        wp->map->f_104 = (void*)((u32)wp->map->f_104 + (u32)wp->map);
        wp->map->f_108 = (void*)((u32)wp->map->f_108 + (u32)wp->map);
    }
#ifdef NONMATCHING
    if (strcmp(wp->map->version, "1.01") == 0) {
#endif
#ifndef NONMATCHING
    if (strcmp(wp->map->version, EXT_LIT((char*)str_804195C8, "1.01")) == 0) {
#endif
        wp->state = 0x65;
    } else {
        wp->state = 0x64;
    }
    return 1;
}
#ifndef NONMATCHING

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void calcCurrentCamState(CamRoadOut* out) {
#ifdef NONMATCHING
    Mtx m;
    Vec v;
    Vec res;
    Vec axis;
    f32 rot, x, y, z, dx, dz, dist, a, ox, oy, oz;
    CamRoadState* s;
    Vec* p;
    p = wp->map->f_e8;
    out->f_0.x = p->x;
    out->f_0.y = p->y;
    out->f_0.z = p->z;
    s = &wp->cur;
    if (!s->on) {
        out->pos.x = 0.0f;
        out->pos.y = 100.0f;
        out->pos.z = 100.0f;
        out->at.x = 0.0f;
        out->at.y = 0.0f;
        out->at.z = 0.0f;
        return;
    }
    a = 3.141592f * s->angle / 180.0f;
    x = s->pos.x;
    y = s->pos.y;
    z = s->pos.z;
    dx = s->dir.x;
    dz = s->dir.z;
    dist = s->dist;
    rot = s->rot;
    ox = dx * dist * (f32)cos(a);
    oy = dist * (f32)sin(a);
    oz = dz * dist * (f32)cos(a);
    out->pos.x = x + ox;
    out->pos.y = y + oy;
    out->pos.z = z + oz;
    axis.x = -dz;
    axis.y = 0.0f;
    axis.z = dx;
    PSMTXRotAxisRad(m, &axis, 0.017453292f * rot);
    v.x = -ox;
    v.y = -oy;
    v.z = -oz;
    PSMTXMultVec(m, &v, &res);
    out->at.x = out->pos.x + res.x;
    out->at.y = out->pos.y + res.y;
    out->at.z = out->pos.z + res.z;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FF00
		opword 0x7C0802A6
		opword 0x90010104
		opword 0xDBE100F0
		opword 0xF3E100F8
		opword 0xDBC100E0
		opword 0xF3C100E8
		opword 0xDBA100D0
		opword 0xF3A100D8
		opword 0xDB8100C0
		opword 0xF38100C8
		opword 0xDB6100B0
		opword 0xF36100B8
		opword 0xDB4100A0
		opword 0xF34100A8
		opword 0xDB210090
		opword 0xF3210098
		opword 0xDB010080
		opword 0xF3010088
		opword 0xDAE10070
		opword 0xF2E10078
		opword 0x93E1006C
		lwz r4, wp(r13)
		opword 0x7C7F1B78
		opword 0x80640000
		opword 0x806300E8
		opword 0xC0030000
		opword 0xD01F0000
		opword 0xC0030004
		opword 0xD01F0004
		opword 0xC0030008
		opword 0xD01F0008
		lwz r3, wp(r13)
		opword 0x80030008
		opword 0x2C000000
		opword 0x40820028
		lfs f1, float_0_8041954c(r2)
		lfs f0, float_100_804195b8(r2)
		opword 0xD03F000C
		opword 0xD01F0010
		opword 0xD01F0014
		opword 0xD03F0018
		opword 0xD03F001C
		opword 0xD03F0020
		opword 0x48000104
		lfs f2, float_3p1416_80419568(r2)
		opword 0xC023004C
		lfs f0, float_180_80419588(r2)
		opword 0xEC220072
		opword 0xC3C30030
		opword 0xC3A30034
		opword 0xC3830038
		opword 0xEF010024
		opword 0xC363003C
		opword 0xC3430044
		opword 0xC3230048
		opword 0xC3E30050
		opword 0xFC20C090
		bl cos
		opword 0xFC400818
		opword 0xEC1B0672
		opword 0xFC20C090
		opword 0xEEE000B2
		bl sin
		opword 0xFC000818
		opword 0xFC20C090
		opword 0xEF190032
		bl cos
		opword 0xFC800818
		lfs f0, float_deg2rad_804195bc(r2)
		opword 0xEC3A0672
		lfs f2, float_0_8041954c(r2)
		opword 0xEC7EB82A
		opword 0x3861002C
		opword 0xEF210132
		opword 0x38810008
		opword 0xEC3DC02A
		opword 0xD07F000C
		opword 0xFC60D050
		opword 0xEC9CC82A
		opword 0xD03F0010
		opword 0xEC2007F2
		opword 0xD09F0014
		opword 0xD0610008
		opword 0xD041000C
		opword 0xD3610010
		bl PSMTXRotAxisRad
		opword 0xFC40B850
		opword 0x3861002C
		opword 0xFC20C050
		opword 0x38810020
		opword 0xFC00C850
		opword 0x38A10014
		opword 0xD0410020
		opword 0xD0210024
		opword 0xD0010028
		bl PSMTXMultVec
		opword 0xC03F000C
		opword 0xC0010014
		opword 0xEC01002A
		opword 0xD01F0018
		opword 0xC03F0010
		opword 0xC0010018
		opword 0xEC01002A
		opword 0xD01F001C
		opword 0xC03F0014
		opword 0xC001001C
		opword 0xEC01002A
		opword 0xD01F0020
		opword 0xE3E100F8
		opword 0xCBE100F0
		opword 0xE3C100E8
		opword 0xCBC100E0
		opword 0xE3A100D8
		opword 0xCBA100D0
		opword 0xE38100C8
		opword 0xCB8100C0
		opword 0xE36100B8
		opword 0xCB6100B0
		opword 0xE34100A8
		opword 0xCB4100A0
		opword 0xE3210098
		opword 0xCB210090
		opword 0xE3010088
		opword 0xCB010080
		opword 0xE2E10078
		opword 0xCAE10070
		opword 0x80010104
		opword 0x83E1006C
		opword 0x7C0803A6
		opword 0x38210100
	}
#endif
}
#ifdef NONMATCHING
static inline Vec crVecSub(Vec a, Vec b) {
    Vec r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}
static inline Vec crVecAdd(Vec a, Vec b) {
    Vec r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}
static inline Vec crVecScale(Vec a, f32 s) {
    Vec r;
    r.x = a.x * s;
    r.y = a.y * s;
    r.z = a.z * s;
    return r;
}
static inline Vec crVecCross(Vec a, Vec b) {
    Vec r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}
static inline f32 crVecDot(Vec a, Vec b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
static inline BOOL crVecIsZero(Vec a) {
    if (a.x == 0.0f && a.y == 0.0f && a.z == 0.0f) {
        return TRUE;
    }
    return FALSE;
}
#pragma dont_inline on
s32 collisionTri_simple(Vec P, Vec A, Vec B, Vec C, f32* dist) {
    Vec dir = {0.0f, -1.0f, 0.0f};
    Vec nz;
    Vec hit;
    Vec e2, e1, e3, n;
    f32 nd, t;
    e2 = crVecSub(C, A);
    e1 = crVecSub(A, B);
    e3 = crVecSub(B, C);
    n = crVecCross(e2, e1);
    nz = n;
    if (nz.x == 0.0f && nz.y == 0.0f && nz.z == 0.0f) {
        return 0;
    }
    nd = crVecDot(n, crVecSub(P, A));
    if (nd > 0.0f) {
        if (crVecDot(n, dir) >= 0.0) {
            return 0;
        }
        if (crVecDot(crVecSub(P, A), crVecCross(e2, dir)) > 0.0) {
            return 0;
        }
        if (crVecDot(crVecSub(P, B), crVecCross(e1, dir)) > 0.0) {
            return 0;
        }
        if (crVecDot(crVecSub(P, C), crVecCross(e3, dir)) > 0.0) {
            return 0;
        }
    } else {
        if (crVecDot(n, dir) <= 0.0) {
            return 0;
        }
        if (crVecDot(crVecSub(P, A), crVecCross(e2, dir)) < 0.0) {
            return 0;
        }
        if (crVecDot(crVecSub(P, B), crVecCross(e1, dir)) < 0.0) {
            return 0;
        }
        if (crVecDot(crVecSub(P, C), crVecCross(e3, dir)) < 0.0) {
            return 0;
        }
    }
    t = -nd / crVecDot(n, dir);
    { Vec h2 = crVecAdd(P, crVecScale(dir, t)); hit = h2; }
    if (hit.y < *dist) {
        return 0;
    }
    *dist = hit.y;
    return 1;
}
// CC_BEGIN
typedef struct CamRoadCC {
    u8 pad0[0x40];
    s32 idxA;              // 0x40
    s32 idxB;              // 0x44
    f32 limA;              // 0x48
    f32 limB;              // 0x4c
    u8 pad1[0x84 - 0x50];
    s32 flag;              // 0x84
    u8 pad2[0xa0 - 0x88];
    s32 vtxOfs;            // 0xa0
    s32 vtxNum;            // 0xa4
} CamRoadCC;
 static inline f32 crLen2(f32 x, f32 z) {
    f32 l = x * x + z * z;
    if (l != 0.0) {
        l = cr_sqrtf(l);
    }
    return l;
}
s32 collisionCurve(s32 mode, void* curve, Vec pos, CamRoadHit* hit) {
    f32 lx0;
    f32 ang0, yA, yB, minDist, cx, side;
    f32 dpx, dpz, sgn, s, limA, limB, x0, y0, z0, x1, z1, cz, r0, r1, rp, r0x, r0z, c1;
    f32 u0x, u0z, u1x, u1z, t, c0, ang1, ratio, d, d0, yy, cross, n1x, n1z;
    f32 r1x, r1z;
    f32 lz0, px, pz, qx, qz, dx, dz, su1x, st, dist, dx2, dz2, cr;
    s32 ret;
    s32 i;
    s32 half;
    s32 idxA, idxB;
    s32 flag, isGrp;
    s32 fl;
    s32 ok;
    Vec* pt;
    Vec* nrm;
    minDist = 100000000.0f;
    ret = 0;
    if (mode == 0) {
        CamRoadCC* c = (CamRoadCC*)curve;
        isGrp = 0;
        half = c->vtxNum / 2;
        pt = &((Vec*)wp->map->f_f8)[c->vtxOfs];
        nrm = &((Vec*)wp->map->f_f8)[c->vtxOfs + half];
        limA = c->limA;
        limB = c->limB;
        idxA = c->idxA;
        idxB = c->idxB;
        flag = c->flag;
    } else {
        CamRoadGroup* g = (CamRoadGroup*)curve;
        idxA = 0;
        idxB = 1;
        half = g->stripNum / 2;
        limB = limA = 0.0f;
        pt = &((Vec*)wp->map->f_f8)[g->stripOfs];
        nrm = &((Vec*)wp->map->f_f8)[g->stripOfs + half];
        flag = 0;
        isGrp = 1;
    }
    yA = nrm[idxA].y;
    yB = nrm[idxB].y;
    if (__fabs(yB - yA) < 0.0001f) {
        yA = yB;
    }
    if (isGrp) {
        flag = 0;
    }
    for (i = 0; i < half - 1; i++) {
        fl = 0;
        x0 = pt[i].x;
        y0 = pt[i].y;
        z0 = pt[i].z;
        x1 = pt[i + 1].x;
        z1 = pt[i + 1].z;
        n1x = -nrm[i + 1].x;
        n1z = -nrm[i + 1].z;
        if (nrm[i].x * (pos.x - x0) + nrm[i].z * (pos.z - z0) < 0.0f) {
            continue;
        }
        if (n1x * (pos.x - x1) + n1z * (pos.z - z1) < 0.0f) {
            continue;
        }
        u0x = -nrm[i].z;
        u0z = nrm[i].x;
        u1x = n1z;
        u1z = -n1x;
        if (__fabs(u0x - u1x) < 0.01f && __fabs(u0z - u1z) < 0.01f) {
            u0x = u1x = 0.5f * (u0x + u1x);
            u0z = u1z = 0.5f * (u0z + u1z);
        }
        if (u0x != u1x || u0z != u1z) {
            side = sgn = 1.0f;
            if (u1x != 0.0) {
                t = (u1z * ((x0 - x1) / u1x) + z1 - z0) / (u0z - u1z * (u0x / u1x));
            } else if (u1z != 0.0) {
                t = (u1x * ((z0 - z1) / u1z) + x1 - x0) / (u0x - u1x * (u0z / u1z));
            } else {
                t = 0.0f;
            }
            cz = t * u0z + z0;
            cx = t * u0x + x0;
            r0z = z0 - cz;
            r0x = x0 - cx;
            r0 = r0x * r0x + r0z * r0z;
            if (r0 != 0.0) {
                r0 = cr_sqrtf(r0);
            }
            dpz = pos.z - cz;
            dpx = pos.x - cx;
            rp = dpx * dpx + dpz * dpz;
            if (rp != 0.0) {
                rp = cr_sqrtf(rp);
            }
            r1z = z1 - cz;
            r1x = x1 - cx;
            r1 = r1x * r1x + r1z * r1z;
            if (r1 != 0.0) {
                r1 = cr_sqrtf(r1);
            }
            c0 = (r0x * dpx + r0z * dpz) / (r0 * rp);
            c1 = (r1x * dpx + r1z * dpz) / (r1 * rp);
            if (c0 < -1.0f) {
                c0 = -1.0f;
            } else if (c0 > 1.0f) {
                c0 = 1.0f;
            }
            if (c1 < -1.0f) {
                c1 = -1.0f;
            } else if (c1 > 1.0f) {
                c1 = 1.0f;
            }
            ang0 = acos(c0);
            ang1 = acos(c1);
            d0 = rp - r0;
            ratio = ang0 / (ang0 + ang1);
            d = ratio * ((rp - r1) - d0) + d0;
            if (d < 0.0f) {
                sgn = -1.0f;
                d = -d;
            }
            if (d >= minDist) {
                continue;
            }
            minDist = d;
            cross = r0x * -(z1 - z0) + r0z * (x1 - x0);
            yy = ratio * (nrm[i + 1].y - nrm[i].y) + nrm[i].y;
            if (flag) {
                if (yy < yA) {
                    if (cross > 0.0) {
                        if (sgn < 0.0f) {
                            if (d > limA) { d = limA; fl |= 2; }
                        } else {
                            if (d > limB) { d = limB; fl |= 2; }
                            d = -d;
                        }
                    } else {
                        if (sgn < 0.0f) {
                            if (d > limB) { d = limB; fl |= 2; }
                            d = -d;
                        } else {
                            if (d > limA) { d = limA; fl |= 2; }
                        }
                    }
                    ret = 1;
                    hit->t = yA;
                    hit->pos.x = pt[idxA].x + d * nrm[idxA].z;
                    hit->pos.y = 0.0f;
                    hit->pos.z = pt[idxA].z - d * nrm[idxA].x;
                    hit->dir.x = nrm[idxA].x;
                    hit->dir.y = 0.0f;
                    hit->dir.z = nrm[idxA].z;
                    hit->y = y0;
                    hit->f_24 = idxA;
                    hit->flags = fl | 1;
                    continue;
                }
                if (yy > yB) {
                    if (cross > 0.0) {
                        if (sgn < 0.0f) {
                            if (d > limA) { d = limA; fl |= 2; }
                        } else {
                            if (d > limB) { d = limB; fl |= 2; }
                            d = -d;
                        }
                    } else {
                        if (sgn < 0.0f) {
                            if (d > limB) { d = limB; fl |= 2; }
                            d = -d;
                        } else {
                            if (d > limA) { d = limA; fl |= 2; }
                        }
                    }
                    ret = 1;
                    hit->t = yB;
                    hit->pos.x = pt[idxB].x + d * nrm[idxB].z;
                    hit->pos.y = 0.0f;
                    hit->pos.z = pt[idxB].z - d * nrm[idxB].x;
                    hit->dir.x = nrm[idxB].x;
                    hit->dir.y = 0.0f;
                    hit->dir.z = nrm[idxB].z;
                    hit->y = y0;
                    hit->f_24 = idxB;
                    hit->flags = fl | 1;
                    continue;
                }
                if (cross > 0.0) {
                    if (sgn < 0.0f) {
                        if (d > limA) {
                            dpx /= rp; dpz /= rp; fl |= 2;
                            rp += d - limA;
                            dpx *= rp; dpz *= rp;
                        }
                    } else {
                        if (d > limB) {
                            dpx /= rp; dpz /= rp; fl |= 2;
                            rp -= d - limB;
                            dpx *= rp; dpz *= rp;
                        }
                    }
                } else {
                    if (sgn < 0.0f) {
                        if (d > limB) {
                            dpx /= rp; dpz /= rp; fl |= 2;
                            rp += d - limB;
                            dpx *= rp; dpz *= rp;
                        }
                    } else {
                        if (d > limA) {
                            dpx /= rp; dpz /= rp; fl |= 2;
                            rp -= d - limA;
                            dpx *= rp; dpz *= rp;
                        }
                    }
                    side = -1.0f;
                }
            } else if (isGrp) {
                if (cross > 0.0) {
                    if (!(sgn < 0.0f) && d > 0.0f) {
                        dpx /= rp; dpz /= rp; fl = 3;
                        rp -= d;
                        dpx *= rp; dpz *= rp;
                    }
                } else {
                    if (sgn < 0.0f && d > 0.0f) {
                        dpx /= rp; dpz /= rp; fl = 3;
                        rp += d;
                        dpx *= rp; dpz *= rp;
                    }
                    side = -1.0f;
                }
            } else {
                if (!(cross > 0.0)) {
                    side = -1.0f;
                }
            }
            hit->pos.x = cx + dpx;
            hit->pos.y = 0.0f;
            hit->pos.z = cz + dpz;
            if (side < 0.0f) {
                hit->dir.x = -dpz / rp;
                hit->dir.y = 0.0f;
                hit->dir.z = dpx / rp;
            } else {
                hit->dir.x = dpz / rp;
                hit->dir.y = 0.0f;
                hit->dir.z = -dpx / rp;
            }
            hit->t = yy;
            ret = 1;
            hit->y = y0;
            hit->f_24 = i;
            hit->flags = fl;
        } else {
            lz0 = pt[i].z;
            dz = pt[i + 1].z - lz0;
            lx0 = pt[i].x;
            dx = pt[i + 1].x - lx0;
            px = pos.x;
            pz = pos.z;
            su1x = -dz;
            if (__fabs(su1x) > __fabs(dx)) {
                st = (dx * ((lx0 - px) / su1x) + pz - lz0) / (dz - dx * (dx / su1x));
            } else if (dx != 0.0) {
                st = (su1x * ((lz0 - pz) / dx) + px - lx0) / (dx - su1x * (dz / dx));
            } else {
                st = 0.0f;
            }
            qx = st * dx + lx0;
            qz = st * dz + lz0;
            if (__fabs(dx) > __fabs(dz)) {
                s = (qx - lx0) / dx;
                ok = (s < -0.0000001 || s > 1.0000001);
            } else if (dz != 0.0) {
                s = (qz - lz0) / dz;
            }
            dz2 = pz - qz;
            dx2 = px - qx;
            yy = s * (nrm[i + 1].y - nrm[i].y) + nrm[i].y;
            dist = dx2 * dx2 + dz2 * dz2;
            if (dist > 0.0) {
                dist = cr_sqrtf(dist);
            }
            if (dist >= minDist) {
                continue;
            }
            minDist = dist;
            if (flag) {
                if (yy < yA) {
                    cr = dx2 * su1x + dz2 * dx;
                    if (cr < 0.0f) {
                        if (dist > limA) { dist = limA; fl |= 2; }
                    } else {
                        if (dist > limB) { dist = limB; fl |= 2; }
                        dist = -dist;
                    }
                    ret = 1;
                    hit->t = yA;
                    hit->pos.x = pt[idxA].x + dist * nrm[idxA].z;
                    hit->pos.y = 0.0f;
                    hit->pos.z = pt[idxA].z - dist * nrm[idxA].x;
                    hit->dir.x = nrm[idxA].x;
                    hit->dir.y = 0.0f;
                    hit->dir.z = nrm[idxA].z;
                    hit->y = y0;
                    hit->f_24 = idxA;
                    hit->flags = fl | 1;
                    continue;
                }
                if (yy > yB) {
                    cr = dx2 * su1x + dz2 * dx;
                    if (cr < 0.0f) {
                        if (dist > limA) { dist = limA; fl |= 2; }
                    } else {
                        if (dist > limB) { dist = limB; fl |= 2; }
                        dist = -dist;
                    }
                    ret = 1;
                    hit->t = yB;
                    hit->pos.x = pt[idxB].x + dist * nrm[idxB].z;
                    hit->pos.y = 0.0f;
                    hit->pos.z = pt[idxB].z - dist * nrm[idxB].x;
                    hit->dir.x = nrm[idxB].x;
                    hit->dir.y = 0.0f;
                    hit->dir.z = nrm[idxB].z;
                    hit->y = y0;
                    hit->f_24 = idxB;
                    hit->flags = fl | 1;
                    continue;
                }
                cr = dx2 * su1x + dz2 * dx;
                if (cr < 0.0f) {
                    if (dist > limA) {
                        dx2 = limA * (dx2 / dist);
                        dz2 = limA * (dz2 / dist);
                        fl |= 2;
                    }
                } else {
                    if (dist > limB) {
                        dx2 = limB * (dx2 / dist);
                        dz2 = limB * (dz2 / dist);
                        fl |= 2;
                    }
                }
            }
            hit->t = yy;
            hit->pos.x = qx + dx2;
            hit->pos.y = 0.0f;
            hit->pos.z = qz + dz2;
            ret = 1;
            hit->dir.x = s * (nrm[i + 1].x - nrm[i].x) + nrm[i].x;
            hit->dir.y = 0.0f;
            hit->dir.z = s * (nrm[i + 1].z - nrm[i].z) + nrm[i].z;
            hit->y = y0;
            hit->f_24 = i;
            hit->flags = fl;
        }
    }
    return ret;
}
// CC_END
void calcCamRoad(CamRoadState* out, CamRoadState* prev, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g) {
    f32 nx;
    f32 ny;
    f32 nz;
    f32 mnz;
    f32 cs, sn, w, ox, oz;
    s32 cnt;
    s32* idxp;
    s32 j;
    s32 l;
    CamRoadCurveX* curve;
    void* hitCurve;
    s32 n;
    CamRoadGroup* grp;
    Vec* verts;
    s32 m;
    CamRoadStrip* strip;
    s32 k;
    s32* idx;
    f32 pz, qz, qx;
    CamRoadState** pp;
    f32 cs2;
    f32 angle;
    f32 rot;
    f32 f4c;
    f32 spd1;
    f32 spd2;
    CamRoadHit hit;
    CamRoadHit hit2;
    CamRoadHit hit3;
    Vec posA;
    Vec posB;
    Vec q;
    Vec p;
    Vec p2;
    Vec v1;
    Vec v2;
    Vec dA;
    Vec dB;
    Vec r1;
    Vec r2;
    f32 best;
    f32 zoom;
    f32 px;
    f32 x;
    f32 y;
    f32 z;
    f32 dist;
    f32 s, t, sgn1, sgn2, len2, len;
    u32 flags;
    s32 found, found2;
    s32 i;
    f32 fov;
    f32 l1, l2, lim2, lim1;
    curve = (CamRoadCurveX*)wp->map->curves;
    best = -100000000.0f;
    hitCurve = NULL;
    posA.x = a;
    posA.y = b;
    posA.z = c;
    posB.x = d;
    posB.y = e;
    posB.z = f;
    for (i = 0; i < wp->map->curveNum; i++, curve++) {
        grp = &((CamRoadGroup*)wp->map->f_f0)[curve->grpOfs];
        n = curve->grpNum;
        if (wp->state == 0x65 && curve->off != 0) {
            continue;
        }
        if (n == 0) {
            if (curve->height > e) {
                continue;
            }
            if (curve->height > best) {
                best = curve->height;
                hitCurve = curve;
            }
            continue;
        }
        for (j = 0; j < n; j++, grp++) {
            verts = &((Vec*)wp->map->f_fc)[grp->vtxOfs];
            m = grp->stripNum;
            strip = &((CamRoadStrip*)wp->map->f_f4)[grp->stripOfs];
            for (k = 0; k < m; k++, strip++) {
                cnt = strip->num;
        cnt = cnt - 1;
                idx = &((s32*)wp->map->f_100)[strip->idxOfs];
                idxp = idx + 1;
                for (l = 1; cnt > l; idxp++, l++) {
                    if (collisionTri_simple(posB, verts[idx[0]], verts[idxp[0]], verts[idxp[1]], &best)) {
                        hitCurve = curve;
                        break;
                    }
                }
            }
        }
    }
    if (hitCurve != NULL) {
        hit.y = -1000000.0f;
        hit.dir.x = 0.0f;
        hit.dir.y = 0.0f;
        hit.dir.z = 0.0f;
        if (!collisionCurve(0, hitCurve, posA, &hit)) {
            hitCurve = NULL;
        }
    }
    curve = (CamRoadCurveX*)hitCurve;
    if (curve == NULL) {
        curve = prev->on ? (CamRoadCurveX*)prev->cam : NULL;
        if (curve == NULL) {
            ((f32*)((u8*)wp + 0x1d4))[0] = a;
            ((f32*)((u8*)wp + 0x1d4))[1] = b;
            ((f32*)((u8*)wp + 0x1d4))[2] = c;
            ((f32*)((u8*)wp + 0x1d4))[3] = d;
            ((f32*)((u8*)wp + 0x1d4))[4] = e;
            ((f32*)((u8*)wp + 0x1d4))[5] = f;
            return;
        }
        x = a;
        if (wp->state == 0x65 && curve != NULL && curve->f_20 != 0) {
            y = curve->f_24;
        } else {
            y = b;
        }
        z = c;
        nx = -prev->dir.x;
        ny = -prev->dir.y;
        nz = -prev->dir.z;
        angle = prev->angle;
        dist = prev->dist;
        rot = prev->rot;
        f4c = prev->f_4c;
        flags = 0;
    } else {
        if (hit.t < 0.0f) {
            hit.t = 0.0f;
        }
        if (hit.t > 1.0f) {
            hit.t = 1.0f;
        }
        angle = curve->f_64;
        rot = curve->f_70;
        dist = curve->f_58;
        x = hit.pos.x;
        if (wp->state == 0x65 && curve->f_20 != 0) {
            y = curve->f_24;
        } else {
            y = b;
        }
        nx = -hit.dir.z;
        len2 = nx * nx + hit.dir.x * hit.dir.x;
        f4c = hit.f_24;
        nz = hit.dir.x;
        z = hit.pos.z;
        flags = hit.flags;
        ny = hit.dir.y;
        if (len2 != 0.0) {
            len = cr_sqrtf(len2);
            nx = nx / len;
            ny = 0.0f;
            nz = nz / len;
        }
        nx *= -1.0f;
        ny *= -1.0f;
        nz *= -1.0f;
    }
    if (curve->f_b4 != 0) {
        grp = &((CamRoadGroup*)wp->map->f_104)[curve->f_b0];
        q.y = 100000000.0f;
        q.x = x;
        q.z = z;
        hit.y = -1000000.0f;
        if (collisionCurve(1, grp, q, &hit)) {
            flags |= hit.flags;
            x = hit.pos.x;
            z = hit.pos.z;
        }
    }
    if (curve != NULL) {
        fov = 3.1415927f * (wp->map->f_e8->x * 0.5f / 180.0f);
        zoom = 1.0f;
        if (g && hitCurve != NULL && prev->on) {
            cs = (f32)cos(fov);
            sn = (f32)sin(fov);
            mnz = -nz;
            w = 0.01f * (prev->f_58 * (zoom * (640.0f * (dist * sn / cs) / 480.0f)));
            found = 0;
            p = posA;
            p.y = 1000000.0f;
            hit2.y = -1000000.0f;
            hit2.dir.z = 0.0f;
            hit2.dir.y = 0.0f;
            hit2.dir.x = 0.0f;
            ox = w * mnz;
            oz = w * nx;
            p.x = p.x + ox;
            p.z = p.z + oz;
            if (collisionCurve(0, curve, p, &hit2)) {
                found = 1;
                p.x = hit2.pos.x;
                p.y = y;
                p.z = hit2.pos.z;
            }
            if (curve->f_b4 != 0) {
                grp = &((CamRoadGroup*)wp->map->f_104)[curve->f_b0];
                hit2.y = -1000000.0f;
                if (collisionCurve(1, grp, p, &hit2)) {
                    found = 1;
                    p.x = hit2.pos.x;
                    p.y = y;
                    p.z = hit2.pos.z;
                }
            }
            if (found) {
                qx = p.x;
                qz = p.z;
            } else {
                qx = x;
                qz = z;
            }
            
            cs2 = (f32)cos(fov);
            sn = (f32)sin(fov);
            w = 0.01f * (g * (zoom * (640.0f * (dist * sn / cs2) / 480.0f)));
            found2 = 0;
            flags = 0;
            p2 = posA;
            p2.y = 1000000.0f;
            hit3.y = -1000000.0f;
            hit3.dir.z = 0.0f;
            hit3.dir.y = 0.0f;
            hit3.dir.x = 0.0f;
            ox = w * mnz;
            oz = w * nx;
            p2.x = p2.x + ox;
            p2.z = p2.z + oz;
            if (collisionCurve(0, curve, p2, &hit3)) {
                found2 = 1;
                flags = hit3.flags;
                p2.x = hit3.pos.x;
                p2.y = y;
                p2.z = hit3.pos.z;
            }
            if (curve->f_b4 != 0) {
                grp = &((CamRoadGroup*)wp->map->f_104)[curve->f_b0];
                hit3.y = -1000000.0f;
                if (collisionCurve(1, grp, p2, &hit3)) {
                    found2 = 1;
                    p2.x = hit3.pos.x;
                    flags |= hit3.flags;
                    p2.z = hit3.pos.z;
                }
            }
            if (found2) {
                px = p2.x;
                pz = p2.z;
                if (!(hit3.flags & 1) && (prev->f_08 & 1)) {
                    wp->f_19c[4] = 0.0f;
                }
                if (!(hit3.flags & 2) && (prev->f_08 & 2)) {
                    wp->f_19c[5] = 0.0f;
                }
            } else {
                px = x;
                pz = z;
            }
            v1.x = qx - prev->pos.x;
            v1.y = 0.0f;
            v1.z = qz - prev->pos.z;
            v2.x = px - prev->pos.x;
            v2.y = 0.0f;
            v2.z = pz - prev->pos.z;
            lim1 = PSVECMag(&v1);
            lim2 = PSVECMag(&v2);
            lim1 += getV60FPS(wp->f_19c[0], prev->time, gp->renderFieldTime);
            lim2 = getV60FPS(wp->f_19c[1], prev->time, gp->renderFieldTime);
            l1 = lim1 * wp->f_19c[4];
            l2 = lim1 * wp->f_19c[5];
            spd1 = lim2 * wp->f_19c[4];
            spd2 = lim2 * wp->f_19c[5];
            dA.x = mnz;
            dA.z = nx;
            dB.x = -dA.z;
            dB.z = dA.x;
            dA.y = 0.0f;
            dB.y = 0.0f;
            r1.y = 0.0f;
            r2.y = 0.0f;
            if (__fabs(dA.z) > __fabs(dA.x)) {
                t = (v2.x - dA.x * (v2.z / dA.z)) / (dB.x - dB.z * (dA.x / dA.z));
                s = (v2.z - t * dB.z) / dA.z;
            } else {
                t = (v2.z - dA.z * (v2.x / dA.x)) / (dB.z - dA.z * (dB.x / dA.x));
                s = (v2.x - t * dB.x) / dA.x;
            }
            r1.x = s * dA.x;
            r1.z = s * dA.z;
            r2.x = t * dB.x;
            r2.z = t * dB.z;
            sgn2 = t < 0.0f ? -1.0f : 1.0f;
            sgn1 = s < 0.0f ? -1.0f : 1.0f;
            lim1 = PSVECMag(&r1);
            lim2 = PSVECMag(&r2);
            if (lim1 > l1 && lim1 > spd1) {
                PSVECScale(&dA, &r1, l1 * sgn1);
            }
            if (lim2 > l2 && lim2 > spd2) {
                PSVECScale(&dB, &r2, l2 * sgn2);
            }
            x = prev->pos.x;
            z = prev->pos.z;
            x += r1.x + r2.x;
            z += r1.z + r2.z;
        }
    }
    wp->f_19c[4] += wp->f_19c[2];
    if (wp->f_19c[4] > 1.0f) {
        wp->f_19c[4] = 1.0f;
    }
    wp->f_19c[5] += wp->f_19c[3];
    if (wp->f_19c[5] > 1.0f) {
        wp->f_19c[5] = 1.0f;
    }
    out->on = 1;
    out->f_04 = hitCurve != NULL;
    out->f_08 = flags;
    out->in[0] = a;
    out->in[1] = b;
    out->in[2] = c;
    out->in[3] = d;
    out->in[4] = e;
    out->in[5] = f;
    out->cam = (CamRoadCam*)curve;
    out->pos.x = x;
    out->pos.y = y;
    out->pos.z = z;
    out->dir.x = -nx;
    out->dir.y = -ny;
    out->dir.z = -nz;
    out->dist = dist;
    out->angle = angle;
    out->rot = rot;
    out->f_4c = f4c;
    out->time = gp->renderFieldTime;
    out->f_58 = g;
    out->shiftXRate = curve->f_7c;
}
#pragma dont_inline reset
static inline f32 crSq(f32 x) { return x * x; }
u32 compareCamRoad(CamRoadState* a, CamRoadState* b, f32* outSpeed) {
    u32 flags = 0;
    s32 d;
    s32 n;
    f32 dot, ang, speed, t, dx, dy, dz, d2, dist;
    if (!b->on) {
        return 0;
    }
    if (a->cam == b->cam && !(a->f_04 == 1 && b->f_04 == 0) && !(a->f_04 == 0 && b->f_08 == 1)) {
        d = (s32)a->f_4c - (s32)b->f_4c;
        if (__abs(d) <= 1) {
            return 0;
        }
        n = a->cam->f_44 - a->cam->f_40;
        if (__abs(d) >= --n) {
            return 0;
        }
        if (__abs(d) >= --n) {
            flags |= 0x20;
        }
    }
    if (a->cam != b->cam) {
        flags |= 1;
    }
    if (a->f_04 == 1 && b->f_04 == 0) {
        flags |= 2;
    }
    if (a->f_04 == 0 && b->f_08 == 1) {
        flags |= 4;
    }
    if (!(__fabs(a->f_4c - b->f_4c) <= 1.0)) {
        flags |= 8;
    }
    dot = a->dir.x * b->dir.x + a->dir.z * b->dir.z;
    if (dot > 1.0f) {
        dot = 1.0f;
    }
    ang = __fabsf(57.29578f * (f32)acos(dot));
    if (ang > 180.0f) {
        ang = 360.0f - ang;
    }
    t = 6.2831855f * a->dist * ang / 360.0f;
    speed = t * wp->f_19c[6];
    ang = __fabsf(a->angle - b->angle);
    if (ang > 180.0f) {
        ang = 360.0f - ang;
    }
    t = 6.2831855f * a->dist * ang / 360.0f;
    t *= wp->f_19c[7];
    if (t > speed) {
        speed = t;
    }
    ang = __fabsf(a->rot - b->rot);
    if (ang > 180.0f) {
        ang = 360.0f - ang;
    }
    t = 6.2831855f * a->dist * ang / 360.0f;
    t *= wp->f_19c[8];
    if (t > speed) {
        speed = t;
    }
    t = __fabsf(a->dist - b->dist);
    t *= wp->f_19c[9];
    if (t > speed) {
        speed = t;
    }
    dx = a->pos.x - b->pos.x;
    dy = a->pos.y - b->pos.y;
    dz = a->pos.z - b->pos.z;
    dist = crSq(dx);
    dist += crSq(dy);
    dist += crSq(dz);
    if (dist) {
        if (dist > 0.0f) {
            f64 guess = __frsqrte(dist);
            guess = 0.5 * guess * (3.0 - guess * guess * dist);
            guess = 0.5 * guess * (3.0 - guess * guess * dist);
            guess = 0.5 * guess * (3.0 - guess * guess * dist);
            dist = dist * guess;
        } else if (dist < 0.0) {
            dist = *(f32*)__float_nan;
        } else if (cr_fpclassifyf(dist) == 1) {
            dist = *(f32*)__float_nan;
        }
    } else {
        dist = 0.0f;
    }
    if (speed < 0.01f && dist < 0.3f) {
        return 0;
    }
    t = dist * wp->f_19c[10];
    if (t > speed) {
        speed = t;
    }
    if (speed > 90.0f) {
        speed = 90.0f;
    }
    if (speed < 20.0f) {
        speed = 20.0f;
    }
    *outSpeed = 1.0f / speed;
    if (!flags) {
        flags |= 0x10;
    }
    return flags;
}
static inline f32 hokanRate(f32 t, f32 a, f32 b, f32 k, f32 o) {
    f32 c1, c0, c2, r;
    c0 = (f32)((double (*)(f32))cos)(a);
    c1 = (f32)((double (*)(f32))cos)(b);
    c2 = (f32)cos(3.141592f * t * k + o);
    r = (2.0f / (1.0f + c0)) * (0.5f * (1.0f - c1) + c2);
    r = 0.500001f * (2.0f - (1.0f + r));
    if (r > 1.0f) {
        r = 1.0f;
    }
    return r;
}
static inline f32 angleLerp(f32 a0, f32 a1, f32 r) {
    while (a0 - a1 > 3.1415927f) {
        a0 -= 6.2831855f;
    }
    while (a0 - a1 < -3.1415927f) {
        a0 += 6.2831855f;
    }
    return r * (a1 - a0) + a0;
}
#pragma dont_inline on
void calcHokanCamRoad(s32 type, CamRoadState* from, CamRoadState* to, CamRoadState* unused, CamRoadState* out, f32 t) {
    f32 r, a0, a1, a2;
    r = hokanRate(t, 0.0f, 0.0f, 1.0f, 0.0f);
    if (type) {
        out->pos.x = r * (to->pos.x - from->pos.x) + from->pos.x;
        out->pos.y = r * (to->pos.y - from->pos.y) + from->pos.y;
        out->pos.z = r * (to->pos.z - from->pos.z) + from->pos.z;
    } else {
        out->pos.x = to->pos.x;
        out->pos.y = to->pos.y;
        out->pos.z = to->pos.z;
    }
    a2 = (f32)atan2(from->dir.x, from->dir.z);
    a0 = a2;
    a1 = (f32)atan2(to->dir.x, to->dir.z);
    while (a0 - a1 > 3.1415927f) {
        a0 -= 6.2831855f;
    }
    while (a0 - a1 < -3.1415927f) {
        a0 += 6.2831855f;
    }
    a0 = r * (a1 - a0) + a0;
    out->dir.x = (f32)sin(a0);
    out->dir.z = (f32)cos(a0);
    out->dir.y = r * (to->dir.y - from->dir.y) + from->dir.y;
    out->dist = r * (to->dist - from->dist) + from->dist;
    out->angle = r * (to->angle - from->angle) + from->angle;
    out->rot = r * (to->rot - from->rot) + from->rot;
    out->shiftXRate = r * (to->shiftXRate - from->shiftXRate) + from->shiftXRate;
}
#pragma dont_inline reset
#define CAMROAD_HOKAN_START(src, flags)                                                                     \
    {                                                                                                         \
        wp->cmpFlags = flags;                                                                                 \
        wp->f_c8 = 1;                                                                                         \
        wp->time = gp->renderFieldTime;                                                                       \
        wp->hokanT = 0.0f;                                                                                    \
        wp->start = src;                                                                                      \
        wp->prev = wp->next;                                                                                  \
        if (wp->prev.f_08 || wp->start.f_08 ||                                                                \
            (wp->state == 0x65 &&                                                                             \
             ((wp->prev.cam && wp->prev.cam->f_20) || (wp->start.cam && wp->start.cam->f_20))) ||             \
            (wp->prev.cam && wp->prev.cam->f_7c) || (wp->start.cam && wp->start.cam->f_7c)) {                 \
            wp->hokanType = 1;                                                                                \
        } else {                                                                                              \
            wp->hokanType = 0;                                                                                \
        }                                                                                                     \
    }
void camRoadMain(CamRoadOut* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g) {
    u32 flags;
    wp->in[0] = a;
    wp->in[1] = b;
    wp->in[2] = c;
    wp->in[3] = d;
    wp->in[4] = e;
    wp->in[5] = f;
    calcCamRoad(&wp->next, &wp->prev, a / 10.0f, b / 10.0f, c / 10.0f, d / 10.0f, e / 10.0f, f / 10.0f, g);
    if (wp->f_c8) {
        flags = compareCamRoad(&wp->prev, &wp->next, &wp->hokanSpeed);
        if (flags) {
            CAMROAD_HOKAN_START(wp->cur, flags)
        } else {
            wp->prev = wp->next;
        }
    }
    if (!wp->f_c8) {
        flags = compareCamRoad(&wp->next, &wp->prev, &wp->hokanSpeed);
        if (flags) {
            CAMROAD_HOKAN_START(wp->prev, flags)
        }
    }
    if (wp->f_c8) {
        wp->hokanT += getV60FPS(wp->hokanSpeed, wp->time, gp->renderFieldTime);
        if (wp->hokanT > 1.0f) {
            wp->hokanT = 1.0f;
        }
        wp->time = gp->renderFieldTime;
        calcHokanCamRoad(wp->hokanType, &wp->start, &wp->prev, &wp->next, &wp->cur, wp->hokanT);
        if (wp->hokanType) {
            wp->cur.f_08 = 1;
        } else {
            wp->cur.f_08 = 0;
        }
        if (1.0f == wp->hokanT) {
            wp->cur = wp->prev;
            wp->f_c8 = 0;
        }
    } else {
        wp->cur = wp->prev = wp->next;
    }
    calcCurrentCamState(out);
    out->at.x *= 10.0f;
    out->at.y *= 10.0f;
    out->at.z *= 10.0f;
    out->pos.x *= 10.0f;
    out->pos.y *= 10.0f;
    out->pos.z *= 10.0f;
}
void* camRoadGetWorkPtr(void) {
    return wp;
}
f32 camRoadGetCurrentShiftXRate(void) {
    if (wp->next.on) {
        return wp->next.shiftXRate;
    }
    return 0.0f;
}
void camRoadReset(void) {
    s32 a = wp->f_204;
    CamRoadMap* m = wp->map;
    u32 s = wp->state;
    memset(wp, 0, 0x210);
    wp->f_c8 = 0;
    wp->prev.on = 0;
    wp->prev.on = 0;
    wp->f_19c[0] = 0.005f;
    wp->f_19c[1] = 0.0f;
    wp->f_19c[2] = 0.004f;
    wp->f_19c[3] = 0.008f;
    wp->f_19c[4] = 1.0f;
    wp->f_19c[5] = 1.0f;
    wp->f_19c[6] = 2.0f;
    wp->f_19c[7] = 1.0f;
    wp->f_19c[8] = 1.0f;
    wp->f_19c[9] = 3.0f;
    wp->f_19c[10] = 1.0f;
    wp->f_204 = -1;
    wp->f_208 = 0;
    wp->f_204 = a;
    wp->map = m;
    wp->state = s;
}
void camRoadCurveOn(const char* name) {
    CamRoadCurve* c = wp->map->curves;
    s32 i;
    if (wp->state == 0x65) {
        for (i = 0; i < wp->map->curveNum; i++, c++) {
            if (strcmp(c->name, name) == 0) {
                c->off = 0;
                break;
            }
        }
    }
}
void camRoadCurveOff(const char* name) {
    CamRoadCurve* c = wp->map->curves;
    s32 i;
    if (wp->state == 0x65) {
        for (i = 0; i < wp->map->curveNum; i++, c++) {
            if (strcmp(c->name, name) == 0) {
                c->off = 1;
                break;
            }
        }
    }
}
#endif
#ifndef NONMATCHING
#pragma pop
#endif


#ifdef NONMATCHING
// prototypes for asm stopgap forward references
void camRoadCurveOff(const char* name);
void camRoadCurveOn(const char* name);
void camRoadReset(void);
f32 camRoadGetCurrentShiftXRate(void);
void* camRoadGetWorkPtr(void);
void camRoadMain(CamRoadOut* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
void calcHokanCamRoad(s32 type, CamRoadState* from, CamRoadState* to, CamRoadState* unused, CamRoadState* out, f32 t);
u32 compareCamRoad(CamRoadState* a, CamRoadState* b, f32* outSpeed);
void calcCamRoad(CamRoadState* out, CamRoadState* prev, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
s32 collisionCurve(s32 mode, void* curve, Vec pos, CamRoadHit* hit);
s32 collisionTri_simple(Vec P, Vec A, Vec B, Vec C, f32* dist);
void calcCurrentCamState(CamRoadOut* out);
s32 camRoadSetup(const char* name);
#endif
#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802c12d0[3] = {0.0f, 1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c12dc[3] = {90.0f, 110.0f, 13.0f};
__declspec(section ".rodata") const f32 vec3_802c12e8[3] = {-110.0f, -70.0f, -190.0f};
__declspec(section ".rodata") const f32 vec3_802c12f4[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f64 double_1_802c1300 = 1.0;
__declspec(section ".rodata") const f64 double_0p5_802c1308 = 0.5;
__declspec(section ".rodata") const f64 double_3_802c1310 = 3.0;
__declspec(section ".rodata") const f64 double_0_802c1318 = 0.0;
__declspec(section ".rodata") const f64 double_to_int_802c1320 = 4503601774854144.0;
__declspec(section ".rodata") const f64 double_0p0001_802c1328 = 0.00009999999747378752;
__declspec(section ".rodata") const f64 double_0p01_802c1330 = 0.009999999776482582;
__declspec(section ".rodata") const f64 double_neg1Eneg07_802c1338 = -0.0000001;
__declspec(section ".rodata") const f64 double_1_802c1340 = 1.0000001;
__declspec(section ".rodata") const char str_802C1348[] = "%scam = %d\n";
__declspec(section ".rodata") const char str_802C1354[] = "%scurve = %d\n\0\0";
__declspec(section ".rodata") const u32 gap_04_802C1364_rodata = 0x00000000;
__declspec(section ".sdata2") const f32 float_0p005_80419548 = 0.005f;
__declspec(section ".sdata2") const f32 float_0_8041954c = 0.0f;
__declspec(section ".sdata2") const f32 float_0p004_80419550 = 0.004f;
__declspec(section ".sdata2") const f32 float_0p008_80419554 = 0.008f;
__declspec(section ".sdata2") const f32 float_1_80419558 = 1.0f;
__declspec(section ".sdata2") const f32 float_2_8041955c = 2.0f;
__declspec(section ".sdata2") const f32 float_3_80419560 = 3.0f;
__declspec(section ".sdata2") const f32 float_10_80419564 = 10.0f;
__declspec(section ".sdata2") const f32 float_3p1416_80419568 = 3.141592f;
__declspec(section ".sdata2") const f32 float_0p5_8041956c = 0.5f;
__declspec(section ".sdata2") const f32 float_0p5_80419570 = 0.500001f;
__declspec(section ".sdata2") const f32 float_6p2832_80419574 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_3p1416_80419578 = 3.1415927f;
__declspec(section ".sdata2") const f32 float_neg3p1416_8041957c = -3.1415927f;
__declspec(section ".sdata2") const f32 float_rad2deg_80419580 = 57.29578f;
__declspec(section ".sdata2") const f32 float_360_80419584 = 360.0f;
__declspec(section ".sdata2") const f32 float_180_80419588 = 180.0f;
__declspec(section ".sdata2") const f32 float_0p01_8041958c = 0.01f;
__declspec(section ".sdata2") const f32 float_0p3_80419590 = 0.3f;
__declspec(section ".sdata2") const f32 float_90_80419594 = 90.0f;
__declspec(section ".sdata2") const f32 float_20_80419598 = 20.0f;
__declspec(section ".sdata2") const f32 dat_8041959c = -100000000.0f;
__declspec(section ".sdata2") const f32 float_neg1E06_804195a0 = -1000000.0f;
__declspec(section ".sdata2") const f32 float_neg1_804195a4 = -1.0f;
__declspec(section ".sdata2") const f32 dat_804195a8 = 100000000.0f;
__declspec(section ".sdata2") const f32 float_640_804195ac = 640.0f;
__declspec(section ".sdata2") const f32 float_480_804195b0 = 480.0f;
__declspec(section ".sdata2") const f32 float_1E06_804195b4 = 1000000.0f;
__declspec(section ".sdata2") const f32 float_100_804195b8 = 100.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_804195bc = 0.017453292f;
__declspec(section ".sdata2") const char str_804195C0[] = "%s/%s\0\0";
__declspec(section ".sdata2") const char str_804195C8[] = "1.01\0\0\0";
#endif
