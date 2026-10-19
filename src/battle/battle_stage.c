#pragma optimize_for_size on
#include "battle/battle_stage.h"
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "memory.h"
#include "system.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>
#ifndef NONMATCHING
__declspec(section ".sdata2") const u32 unk_8042302c;
__declspec(section ".sdata2") const u32 unk_80423028;
__declspec(section ".sdata2") u32 unk_80423024;
__declspec(section ".sdata2") u32 unk_80423020;
__declspec(section ".sdata2") u32 unk_8042301c;
__declspec(section ".sdata2") u32 unk_80423018;
__declspec(section ".rodata") extern const f32 vec3_802f31a8[3];
__declspec(section ".rodata") extern const f32 vec3_802f31b4[3];
__declspec(section ".rodata") extern const f32 vec3_802f31c0[3];
__declspec(section ".rodata") extern const f32 vec3_802f31cc[3];
__declspec(section ".rodata") extern const f32 vec3_802f31d8[3];
__declspec(section ".rodata") extern const f32 vec3_802f31e4[3];
__declspec(section ".rodata") extern const f32 vec3_802f31f0[3];
__declspec(section ".rodata") extern const f32 vec3_802f31fc[3];
__declspec(section ".rodata") extern const f32 vec3_802f3208[3];
__declspec(section ".rodata") extern const f32 vec3_802f3214[3];
__declspec(section ".rodata") extern const f64 double_to_int_802f3220;
__declspec(section ".rodata") extern const f64 double_to_int_mask_802f3228;
__declspec(section ".sdata2") extern const u32 dat_8041c7e8;
__declspec(section ".sdata2") extern const u32 dat_8041c7ec;
__declspec(section ".sdata2") extern const f32 float_0_8041c7f0;
__declspec(section ".sdata2") extern const f32 float_1_8041c7f4;
__declspec(section ".sdata2") extern const f32 float_0p25_8041c7f8;
__declspec(section ".sdata2") extern const f32 float_60_8041c7fc;
__declspec(section ".sdata2") extern const f32 float_4p75_8041c800;
__declspec(section ".sdata2") extern const f32 float_3p75_8041c804;
__declspec(section ".sdata2") extern const f32 float_16_8041c808;
__declspec(section ".sdata2") extern const f32 float_6_8041c80c;
__declspec(section ".sdata2") extern const f32 float_100_8041c810;
__declspec(section ".sdata2") extern const f32 float_1000_8041c814;
__declspec(section ".sdata2") extern const f32 float_neg1_8041c818;
__declspec(section ".sdata2") extern const f32 float_32767_8041c81c;
__declspec(section ".sdata2") extern const f32 float_deg2rad_8041c820;
__declspec(section ".sdata2") extern const f32 float_6p2832_8041c824;
__declspec(section ".sdata2") extern const f32 float_30_8041c828;
__declspec(section ".sdata2") extern const f32 float_neg1000_8041c82c;
__declspec(section ".sdata2") extern const f32 float_neg100_8041c830;
__declspec(section ".sdata2") extern const f32 float_50_8041c834;
__declspec(section ".sdata2") extern const f32 float_2_8041c838;
__declspec(section ".sdata2") extern const f32 float_0p34907_8041c83c;
__declspec(section ".sdata2") extern const f32 float_neg640_8041c840;
__declspec(section ".sdata2") extern const f32 float_640_8041c844;
__declspec(section ".sdata2") extern const f32 float_105_8041c848;
__declspec(section ".sdata2") extern const f32 float_5000_8041c84c;
__declspec(section ".sdata2") extern const f32 float_6000_8041c850;
__declspec(section ".sdata2") extern const f32 float_290_8041c854;
__declspec(section ".sdata2") extern const f32 float_200_8041c858;
__declspec(section ".sdata2") extern const f32 float_90_8041c85c;
__declspec(section ".sdata2") extern const f32 float_neg50_8041c860;
#define EXT_LIT(sym, val) (sym)

#endif
// G5 keepall: asm stopgap reaches data via section-relative relocs; keep it from being stripped
#pragma force_active on

extern int rand(void);

typedef struct StageLight {
	u32 flags;              // 0x0
	char name[0x20];        // 0x4
	GXColor color;          // 0x24
	GXColor colorStart;     // 0x28
	GXColor colorTarget;    // 0x2C
	s32 colorTime;          // 0x30
	s32 colorMax;           // 0x34
	u8 colorMode;           // 0x38
	f32 width;              // 0x3C
	f32 widthStart;         // 0x40
	f32 widthTarget;        // 0x44
	s32 widthTime;          // 0x48
	s32 widthMax;           // 0x4C
	u8 widthMode;           // 0x50
	Vec pos;                // 0x54
	Vec posStart;           // 0x60
	Vec posTarget;          // 0x6C
	s32 posTime;            // 0x78
	s32 posMax;             // 0x7C
	u8 posMode;             // 0x80
	Vec target;             // 0x84
	Vec targetStart;        // 0x90
	Vec targetTarget;       // 0x9C
	s32 targetTime;         // 0xA8
	s32 targetMax;          // 0xAC
	u8 targetMode;          // 0xB0
	Vec up;                 // 0xB4
	Vec upStart;            // 0xC0
	Vec upTarget;           // 0xCC
	s32 upTime;             // 0xD8
	s32 upMax;              // 0xDC
	u8 upMode;              // 0xE0
	void* data;             // 0xE4
} StageLight;

typedef struct StageDark {
	s32 flags;      // 0x0
	u8 cur;         // 0x4
	u8 base;        // 0x5
	u8 start;       // 0x6
	u8 baseStart;   // 0x7
	u8 target;      // 0x8
	u8 baseTarget;  // 0x9
	u8 pad_a[2];    // 0xA
	s32 time;       // 0xC
	s32 baseTime;   // 0x10
	s32 max;        // 0x14
	s32 baseMax;    // 0x18
	u8 mode;        // 0x1C
	u8 baseMode;    // 0x1D
} StageDark;

typedef struct StageWork {
	s32 field_0;            // 0x0
	StageLight lights[12];  // 0x4
	StageDark stgDark;      // 0xAE4
	StageDark audDark;      // 0xB04
	f32 stageSizeX;          // 0xB24
	f32 stageSizeY;          // 0xB28
	f32 stageSizeZ;          // 0xB2C
	f32 audienceSizeX;          // 0xB30
	f32 audienceSizeY;          // 0xB34
	f32 audienceSizeZ;          // 0xB38
} StageWork;

#define STG ((StageWork*)BattleStageGetPtr())

typedef struct ScreenWork {
	void* tex;      // 0x0
	s32 captured;   // 0x4
	f32 field_8;    // 0x8
	f32 field_C;    // 0xC
	f32 field_10;   // 0x10
	f32 field_14;   // 0x14
	f32 field_18;   // 0x18
	f32 field_1C;   // 0x1C
	s32 field_20;   // 0x20
	s32 field_24;   // 0x24
	f32 field_28;   // 0x28
} ScreenWork;

//.sbss
static BattleSpotWork work;
static ScreenWork* screen_wp;


//.sdata
static BattleSpotWork* wp = &work;


__declspec(section ".sdata") u32 gap_07_804117E4_sdata[7] = {0};
static u8 inta_tex[32] = {0xFF,0xFF,0xFF,0xFF,0,0,0,0,0xFF,0xFF,0xFF,0xFF,0,0,0,0,0xFF,0xFF,0xFF,0xFF,0,0,0,0,0xFF,0xFF,0xFF,0xFF,0,0,0,0};

#ifdef NONMATCHING
USER_FUNC(screen_evt_func);
#endif
#ifndef NONMATCHING
s32 screen_evt_func(EventEntry* event, BOOL isFirstCall);
#endif

__declspec(section ".sdata") EVT_BEGIN(screen_evt)
	BEGIN_INLINE_EVENT
		CALL(screen_evt_func, LW(0))
	END_INLINE_EVENT
	RETURN
EVT_END()


__declspec(section ".sdata") u32 gap_07_8041183C_sdata[1] = {0};

// forward declarations
void batSpotDisp(CameraId camId, void* param);
BattleSpotEntry* batSpotEntry(void);
void BattleStageDispDark(CameraId camId, void* param);
void BattleStageDispLight(CameraId camId, void* param);
void DarkByPoint(u8 alpha, f32 x, f32 y, f32 z);
void DarkBySquare(f32 x0, f32 y0, f32 x1, f32 y1, f32 z, u8 alpha);
void BattleStageSetDark(StageDark* d, u8 v, s32 time, u8 mode);
void BattleStageSetDarkBase(StageDark* d, u8 v, s32 time, u8 mode);
void BattleStageLightSetTarget(s32 idx, f32 x, f32 y, f32 z, s32 time, u8 mode);
void batSpotInit(void);
f32 getSpline(f32* a, f32* b, f32* c, f32* d, s32* t, s32 n, s32 x);
void batSpotMain();
void drawCone(CameraId camId, BattleSpotEntry* e);
double sin(double);
double cos(double);

#ifndef NONMATCHING
BattleStage* BattleStageGetPtr(void);

void BattleStageInit(void);

typedef struct LightSpline {
	s32 n;          // 0x0
	s32 t[8];       // 0x4
	f32 x[4][8];    // 0x24
	f32 y[4][8];    // 0xA4
	f32 z[4][8];    // 0x124
} LightSpline;

void DCFlushRange(void* addr, u32 nBytes);
void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXClearVtxDesc(void);
void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap);
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
void GXSetNumChans(u8 nChans);
void GXSetNumTevStages(u8 nStages);
void GXSetNumTexGens(u8 nTexGens);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx);
void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac);
void GXSetVtxDesc(GXAttr attr, GXAttrType type);
void GXSetZCompLoc(GXBool before_tex);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXRotAxisRad(Mtx m, const Vec* axis, f32 rad);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void PSVECNormalize(const Vec* src, Vec* dst);
void *memset(void *dest, int ch, size_t count);
static f32 randf(f32 min, f32 max);
void BattleStageMain(void);

void BattleStageEnd(void);

void BattleStageDisp(void);

void DarkByPoint(u8 alpha, f32 x, f32 y, f32 z);

void DarkBySquare(f32 x0, f32 y0, f32 x1, f32 y1, f32 z, u8 alpha);

void BattleStageDispDark(CameraId camId, void* param);

void BattleStageDispLight(CameraId camId, void* param);

void BattleStageOnLightInCommand(void);

void BattleStageOffLightInCommand(void);

void BattleStageOnLightFriendInCommand(void);

void BattleStageOffLightFriendInCommand(void);

void BattleStageOnLightEnemyInCommand(void);

void BattleStageOffLightEnemyInCommand(void);

s32 BattleStageGetLightNumberByName(const char* name);

s32 BattleStageSysLightEntry(const char* name);

#pragma opt_propagation off
void BattleStageLightRelease(s32 idx, s32 time, u8 mode);
#pragma opt_propagation reset

#pragma opt_propagation off
void BattleStageLightSetLightColor(s32 idx, u8 r, u8 g, u8 b, s32 time, u8 mode);
#pragma opt_propagation reset

#pragma opt_propagation off
void BattleStageLightSetWidth(s32 idx, s32 width, s32 time, u8 mode);
#pragma opt_propagation reset

#pragma opt_propagation off
void BattleStageLightSetPosition(s32 idx, f32 x, f32 y, f32 z, s32 time, u8 mode);
#pragma opt_propagation reset

#pragma dont_inline on
#pragma opt_propagation off
void BattleStageLightSetTarget(s32 idx, f32 x, f32 y, f32 z, s32 time, u8 mode);
#pragma opt_propagation reset
#pragma dont_inline reset

void BattleStageLightSetTargetByUnit(s32 idx, s32 unitId, f32 x, f32 y, f32 z, s32 time, u8 mode);

#pragma opt_propagation off
void BattleStageLightSetUpVec(s32 idx, f32 x, f32 y, f32 z, s32 time, u8 mode);
#pragma opt_propagation reset

void BattleStageSetDark(StageDark* d, u8 v, s32 time, u8 mode);

void BattleStageSetDarkBase(StageDark* d, u8 v, s32 time, u8 mode);

void BattleStageSetStgDark(u8 v, s32 time, u8 mode);

void BattleStageSetStgDarkBase(u8 v, s32 time, u8 mode);

void BattleStageReturnStgDarkBase(s32 time, u8 mode);

void BattleStageSetAudDark(u8 v, s32 time, u8 mode);

void BattleStageSetAudDarkBase(u8 v, s32 time, u8 mode);

void BattleStageReturnAudDarkBase(s32 time, u8 mode);

f32 getSpline(f32* a, f32* b, f32* c, f32* d, s32* t, s32 n, s32 x);
BattleSpotWork* BatSpotGetPtr(void);

void batSpotInit(void);

void batSpotMain();

void batSpotDisp(CameraId camId, void* param);

void drawCone(CameraId camId, BattleSpotEntry* e);

// TODO: get this to not inline into batSpotInit
BattleSpotEntry* batSpotEntry(void);

static f32 randf(f32 min, f32 max);

static void screen_capture(CameraId camId, void* param);

s32 screen_evt_func(EventEntry* event, BOOL isFirstCall);

s32 tou_gamen_screen_tev_init(EventEntry* event, BOOL isFirstCall);

typedef struct TevCbWork {
	u8 pad_0[0xC];
	s32 field_C;
	s32 field_10;
	s32 field_14;
} TevCbWork;

void tou_gamen_screen_tev(TevCbWork* p);


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
#pragma force_active reset
#pragma force_active reset

#pragma dont_inline on
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
static f32 randf(f32 min, f32 max) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0xDBE10020
		opword 0xF3E10028
		opword 0xDBC10010
		opword 0xF3C10018
		opword 0xFFC00890
		opword 0xFFE01090
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061000C
		lis r4, double_to_int_802f3220@ha
		lfd f3, double_to_int_802f3220@l(r4)
		opword 0xEC1FF028
		opword 0x90010008
		lfs f1, float_32767_8041c81c(r2)
		opword 0xC8410008
		opword 0xEC421828
		opword 0xEC220824
		opword 0xEC21F03A
		opword 0xE3E10028
		opword 0xCBE10020
		opword 0xE3C10018
		opword 0x80010034
		opword 0xCBC10010
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop
#pragma dont_inline reset

static void screen_capture(CameraId camId, void* param) {
	GXSetTexCopySrc(0, 0, 608, 480);
	GXSetTexCopyDst(304, 240, GX_TF_RGB565, GX_TRUE);
	GXCopyTex(screen_wp->tex, GX_FALSE);
	GXPixModeSync();
	screen_wp->captured = 1;
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 screen_evt_func(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, screen_capture@ha
		lfs f1, float_1000_8041c814(r2)
		opword 0x90010014
		addi r5, r3, screen_capture@l
		opword 0x38600008
		opword 0x38800000
		opword 0x38C00000
		bl dispEntry
		opword 0x80010014
		opword 0x38600000
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

s32 tou_gamen_screen_tev_init(EventEntry* event, BOOL isFirstCall) {
	u32 size = GXGetTexBufferSize(608, 480, GX_TF_I4, GX_FALSE, 0);

	screen_wp = _mapAlloc(sizeof(ScreenWork));
	screen_wp->tex = _mapAlloc(size);
	screen_wp->captured = 0;
	screen_wp->field_8 = screen_wp->field_C = EXT_LIT(float_1_8041c7f4, 1.0f);
	screen_wp->field_10 = screen_wp->field_14 = EXT_LIT(float_0_8041c7f0, 0.0f);
	screen_wp->field_18 = screen_wp->field_1C = EXT_LIT(float_0_8041c7f0, 0.0f);
	screen_wp->field_20 = 0;
	screen_wp->field_28 = EXT_LIT(float_neg1_8041c818, -1.0f);
	if (evtGetValue(event, GSW(0)) == 163) {
		screen_wp->field_24 = 1;
	}
	evtEntry(screen_evt, 0, 0);
	return 2;
}

#pragma defer_codegen off
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void tou_gamen_screen_tev(TevCbWork* p) {
	asm volatile {
		opword 0x9421FF20
		opword 0x7C0802A6
		opword 0x900100E4
		opword 0xBEE100BC
		opword 0x7C7B1B78
		lwz r4, screen_wp(r13)
		opword 0x80040004
		opword 0x2C000000
		opword 0x418205C8
		opword 0x80040024
		opword 0x2C000000
		opword 0x418201CC
		opword 0x83A40000
		opword 0x3B800000
		opword 0x5780F002
		opword 0x57840FFE
		opword 0x7C040050
		opword 0x7F851670
		opword 0x5403103E
		opword 0x38000040
		opword 0x7FE50194
		opword 0x578907FE
		opword 0x7FC32214
		opword 0x39400000
		opword 0x57E4402E
		opword 0x38A000FF
		opword 0x57C31838
		opword 0x7C0903A6
		opword 0x7D461E70
		opword 0x5540E804
		opword 0x55480FFE
		opword 0x394A0001
		opword 0x7D660194
		opword 0x7C080050
		opword 0x20C90000
		opword 0x5407183E
		opword 0x55602834
		opword 0x7CC63110
		opword 0x7CE74214
		opword 0x7C002214
		opword 0x7CA63038
		opword 0x7C003A14
		opword 0x7C001A14
		opword 0x7CDD01AE
		opword 0x4200FFC0
		bl rand
		opword 0x38800064
		opword 0x57F9402E
		opword 0x7C0323D6
		opword 0x57DA1838
		opword 0x3BC00000
		opword 0x7C0021D6
		opword 0x7C601850
		opword 0x3BE30064
		opword 0x480000A4
		bl rand
		opword 0x5460F002
		opword 0x54630FFE
		opword 0x7C030050
		opword 0x5400103E
		opword 0x7C601A14
		opword 0x3B030002
		bl rand
		opword 0x20980041
		opword 0x7C0323D6
		opword 0x7C0021D6
		opword 0x7EE01850
		bl rand
		opword 0x5460C00E
		opword 0x54630FFE
		opword 0x7C030050
		opword 0x7C97C214
		opword 0x5400403E
		opword 0x7EE5BB78
		opword 0x7C601A14
		opword 0x7C172050
		opword 0x5466063E
		opword 0x7C0903A6
		opword 0x7C172000
		opword 0x4080003C
		opword 0x7CA41E70
		opword 0x54A0E804
		opword 0x54A30FFE
		opword 0x38A50001
		opword 0x7C840194
		opword 0x7C030050
		opword 0x54842834
		opword 0x5400183E
		opword 0x7C84CA14
		opword 0x7C001A14
		opword 0x7C040214
		opword 0x7C00D214
		opword 0x7CDD01AE
		opword 0x4200FFCC
		opword 0x3BDE0001
		opword 0x7C1EF800
		opword 0x4180FF5C
		opword 0x3B9C0001
		opword 0x2C1C0040
		opword 0x4180FEAC
		opword 0x7FA3EB78
		opword 0x38801000
		bl DCFlushRange
		opword 0x7FA4EB78
		opword 0x38610008
		opword 0x38A00040
		opword 0x38C00040
		opword 0x38E00001
		opword 0x39000001
		opword 0x39200001
		opword 0x39400000
		bl GXInitTexObj
		lfs f1, float_0_8041c7f0(r2)
		opword 0x38610008
		opword 0x38800000
		opword 0x38A00000
		opword 0xFC400890
		opword 0x38C00000
		opword 0xFC600890
		opword 0x38E00000
		opword 0x39000000
		bl GXInitTexObjLOD
		opword 0x38610008
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x48000050
		opword 0x80840000
		opword 0x38610008
		opword 0x38A00130
		opword 0x38C000F0
		opword 0x38E00004
		opword 0x39000000
		opword 0x39200000
		opword 0x39400000
		bl GXInitTexObj
		lfs f1, float_0_8041c7f0(r2)
		opword 0x38610008
		opword 0x38800000
		opword 0x38A00000
		opword 0xFC400890
		opword 0x38C00000
		opword 0xFC600890
		opword 0x38E00000
		opword 0x39000000
		bl GXInitTexObjLOD
		opword 0x38610008
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x38610008
		la r4, inta_tex(r13)
		opword 0x38A00004
		opword 0x38C00008
		opword 0x38E00000
		opword 0x39000001
		opword 0x39200001
		opword 0x39400000
		bl GXInitTexObj
		lfs f1, float_0_8041c7f0(r2)
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
		opword 0x38800001
		bl GXLoadTexObj
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
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600001
		opword 0x38800001
		opword 0x38A00001
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
		opword 0x38A00008
		opword 0x38C00000
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00006
		bl GXSetTevAlphaIn
		lwz r5, screen_wp(r13)
		opword 0x80050024
		opword 0x2C000000
		opword 0x40820184
		opword 0x80850020
		opword 0x386000C8
		opword 0x38040001
		opword 0x90050020
		lwz r4, screen_wp(r13)
		opword 0x80840020
		opword 0x7C041BD6
		opword 0x7C0019D6
		opword 0x7C002051
		opword 0x40820094
		bl rand
		opword 0x38800003
		opword 0x7C0323D6
		opword 0x7C0021D6
		opword 0x7C001850
		opword 0x2C000001
		opword 0x41820064
		opword 0x40800074
		opword 0x2C000000
		opword 0x4080000C
		opword 0x48000068
		opword 0x48000064
		lwz r3, screen_wp(r13)
		lfs f0, float_1_8041c7f4(r2)
		opword 0xC0430008
		lfs f1, float_0_8041c7f0(r2)
		opword 0xEC001028
		opword 0xEC401024
		bl randf
		lwz r3, screen_wp(r13)
		lfs f0, float_1_8041c7f4(r2)
		opword 0xD0230014
		lfs f1, float_0_8041c7f0(r2)
		lwz r3, screen_wp(r13)
		opword 0xC0430008
		opword 0xEC001028
		opword 0xEC401024
		bl randf
		lwz r3, screen_wp(r13)
		opword 0xD023001C
		opword 0x48000018
		lfs f1, float_1_8041c7f4(r2)
		lfs f2, float_0p25_8041c7f8(r2)
		bl randf
		lwz r3, screen_wp(r13)
		opword 0xD023000C
		lwz r4, screen_wp(r13)
		opword 0x38610058
		lfs f2, float_60_8041c7fc(r2)
		opword 0xC0240008
		opword 0xC004000C
		lfs f3, float_1_8041c7f4(r2)
		opword 0xEC000828
		opword 0xEC001024
		opword 0xEC01002A
		opword 0xD0040008
		lwz r4, screen_wp(r13)
		opword 0xC0240010
		opword 0xC0040014
		opword 0xEC000828
		opword 0xEC001024
		opword 0xEC01002A
		opword 0xD0040010
		lwz r4, screen_wp(r13)
		opword 0xC0240018
		opword 0xC004001C
		opword 0xEC000828
		opword 0xEC001024
		opword 0xEC01002A
		opword 0xD0040018
		lwz r4, screen_wp(r13)
		opword 0xC0240008
		opword 0xFC400890
		bl PSMTXScale
		lwz r3, screen_wp(r13)
		lfs f0, float_1_8041c7f4(r2)
		opword 0xC0230008
		opword 0xC0430018
		opword 0xEC000828
		opword 0xEC200824
		opword 0xFC020840
		opword 0x40810008
		opword 0xFC400890
		opword 0xC0030010
		opword 0xFC000840
		opword 0x40810008
		opword 0x48000008
		opword 0xFC200090
		lfs f3, float_0_8041c7f0(r2)
		opword 0x38610028
		bl PSMTXTrans
		opword 0x38610058
		opword 0x38810028
		opword 0x38A10088
		bl PSMTXConcat
		opword 0x48000018
		lfs f1, float_4p75_8041c800(r2)
		opword 0x38610088
		lfs f2, float_3p75_8041c804(r2)
		lfs f3, float_0_8041c7f0(r2)
		bl PSMTXScale
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0001E
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x38610088
		opword 0x3880001E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x38600004
		bl camGetPtr
		opword 0x7C641B78
		lfs f1, float_1_8041c7f4(r2)
		lfs f4, float_100_8041c810(r2)
		opword 0x38610088
		opword 0xC0040014
		opword 0xFC600890
		lfs f2, float_1000_8041c814(r2)
		opword 0xEC840028
		lfs f5, float_6_8041c80c(r2)
		lfs f0, float_16_8041c808(r2)
		opword 0xEC441024
		opword 0xEC4500BA
		bl PSMTXScale
		opword 0x38600001
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C00021
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x38610088
		opword 0x38800021
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x38000002
		opword 0x901B000C
		opword 0x901B0014
		opword 0x901B0010
		opword 0xBAE100BC
		opword 0x800100E4
		opword 0x7C0803A6
		opword 0x382100E0
	}
}
#pragma pop

#pragma defer_codegen reset

asm BattleSpotEntry* batSpotEntry(void) {
	nofralloc
	lwz r4, wp(r13)
	lis r3, vec3_802f31a8@ha
	addi r5, r3, vec3_802f31a8@l
	lwz r0, 0x0(r4)
	lwz r3, 0x4(r4)
	mtctr r0
	cmpwi r0, 0x0
	ble L_af_1
L_af_2:
	lhz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq L_af_1
	addi r3, r3, 0x2c
	bdnz L_af_2
L_af_1:
	lwz r4, 0x54(r5)
	lwz r0, 0x58(r5)
	stw r4, 0x4(r3)
	stw r0, 0x8(r3)
	lwz r0, 0x5c(r5)
	stw r0, 0xc(r3)
	lwz r4, 0x60(r5)
	lwz r0, 0x64(r5)
	stw r4, 0x1c(r3)
	stw r0, 0x20(r3)
	lwz r0, 0x68(r5)
	stw r0, 0x24(r3)
	lwz r4, 0x6c(r5)
	lwz r0, 0x70(r5)
	stw r4, 0x10(r3)
	stw r0, 0x14(r3)
	lwz r0, 0x74(r5)
	stw r0, 0x18(r3)
	lwz r0, unk_8042302c(r2)
	stw r0, 0x28(r3)
	lhz r0, 0x0(r3)
	ori r0, r0, 0x1
	sth r0, 0x0(r3)
	blr
}

#pragma defer_codegen off
#pragma dont_inline on
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void drawCone(CameraId camId, BattleSpotEntry* e) {
	char _af_pad[292];
	asm volatile {
		mr r29, r4
		bl camGetPtr
		opword 0xC03D0004
		opword 0x7C7F1B78
		opword 0xC05D0008
		la r3, _af_pad+240
		opword 0xC07D000C
		bl PSMTXTrans
		opword 0xC03D001C
		opword 0x386100C8
		opword 0xC05D0020
		opword 0xC07D0024
		bl PSMTXScale
		lfs f1, float_deg2rad_8041c820(r2)
		opword 0x38610068
		opword 0xC01D0010
		opword 0x38800078
		opword 0xEC210032
		bl PSMTXRotRad
		lfs f1, float_deg2rad_8041c820(r2)
		opword 0x38610038
		opword 0xC01D0014
		opword 0x38800079
		opword 0xEC210032
		bl PSMTXRotRad
		lfs f1, float_deg2rad_8041c820(r2)
		opword 0x38610008
		opword 0xC01D0018
		opword 0x3880007A
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x38810038
		opword 0x38610008
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38610038
		opword 0x38810068
		opword 0x38A10098
		bl PSMTXConcat
		opword 0x388100F8
		opword 0x387F011C
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810098
		opword 0x386100F8
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38610098
		opword 0x388100C8
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x38610098
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		opword 0x386000A0
		opword 0x38800000
		opword 0x38A00020
		bl GXBegin
		lfs f0, float_0_8041c7f0(r2)
		opword 0x3FE0CC01
		opword 0x38000000
		opword 0x3BC00000
		opword 0xD01F8000
		lfs f0, float_0_8041c7f0(r2)
		opword 0xD01F8000
		lfs f0, float_0_8041c7f0(r2)
		opword 0xD01F8000
		opword 0x887D002B
		opword 0x981F8000
		opword 0x981F8000
		opword 0x981F8000
		opword 0x987F8000
		opword 0x2C1E001E
		opword 0x4082000C
		lfs f31, float_0_8041c7f0(r2)
		opword 0x48000038
		opword 0x7C7E00D0
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802f3220@ha
		opword 0x9061012C
		lfd f2, double_to_int_802f3220@l(r4)
		opword 0x90010128
		lfs f3, float_6p2832_8041c824(r2)
		opword 0xC8210128
		lfs f0, float_30_8041c828(r2)
		opword 0xEC211028
		opword 0xEC230072
		opword 0xEFE10024
		opword 0xFC20F890
		bl sin
		frsp f30, f1
		opword 0xFC20F890
		bl cos
		opword 0xFC000818
		opword 0x3BDE0001
		opword 0x38600003
		opword 0x38000000
		opword 0x2C1E001F
		opword 0xD01F8000
		opword 0xD3DF8000
		lfs f0, float_neg1_8041c818(r2)
		opword 0xD01F8000
		opword 0x889D002B
		opword 0x7C641BD6
		opword 0x981F8000
		opword 0x981F8000
		opword 0x981F8000
		opword 0x987F8000
		opword 0x4180FF6C
	}
}
#pragma pop
#pragma dont_inline reset

#pragma defer_codegen reset

asm void batSpotDisp(CameraId camId, void* param) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r29, 0x14(r1)
	mr r29, r3
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xb
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xb
	li r5, 0x1
	li r6, 0x5
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	bl GXSetNumTexGens
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
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
	li r7, 0xa
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x5
	bl GXSetTevAlphaIn
	li r3, 0x1
	bl GXSetZCompLoc
	li r3, 0x7
	li r4, 0x0
	li r5, 0x0
	li r6, 0x7
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x1
	bl GXSetNumChans
	lwz r3, wp(r13)
	li r31, 0x0
	lwz r30, 0x4(r3)
	b L_af_1
L_af_2:
	lhz r3, 0x0(r30)
	clrlwi. r0, r3, 31
	beq L_af_3
	rlwinm. r0, r3, 0, 30, 30
	beq L_af_3
	li r3, 0x2
	bl GXSetCullMode
	li r3, 0x1
	bl GXSetAlphaUpdate
	li r3, 0x0
	bl GXSetColorUpdate
	li r3, 0x1
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	li r3, 0x0
	li r4, 0x4
	li r5, 0x5
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x1
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	mr r3, r29
	mr r4, r30
	bl drawCone
	li r3, 0x1
	bl GXSetCullMode
	li r3, 0x1
	bl GXSetAlphaUpdate
	li r3, 0x0
	bl GXSetColorUpdate
	li r3, 0x1
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	li r3, 0x0
	li r4, 0x4
	li r5, 0x5
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	lwz r0, unk_80423028(r2)
	addi r4, r1, 0xc
	li r3, 0x4
	stw r0, 0xc(r1)
	bl GXSetChanMatColor
	mr r3, r29
	mr r4, r30
	bl drawCone
	li r3, 0x2
	bl GXSetCullMode
	li r3, 0x0
	bl GXSetAlphaUpdate
	li r3, 0x1
	bl GXSetColorUpdate
	li r3, 0x1
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	li r3, 0x1
	li r4, 0x6
	li r5, 0x7
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	lwz r0, 0x28(r30)
	addi r4, r1, 0x8
	li r3, 0x4
	stw r0, 0x8(r1)
	bl GXSetChanMatColor
	mr r3, r29
	mr r4, r30
	bl drawCone
L_af_3:
	addi r31, r31, 0x1
	addi r30, r30, 0x2c
L_af_1:
	lwz r3, wp(r13)
	lwz r0, 0x0(r3)
	cmpw r31, r0
	blt L_af_2
	lmw r29, 0x14(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

#pragma defer_codegen off
#pragma dont_inline on
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void batSpotMain() {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		lwz r3, wp(r13)
		opword 0x80030000
		opword 0x7C0903A6
		opword 0x2C000000
		opword 0x40810008
		opword 0x42000000
		opword 0x80030008
		opword 0x2C000000
		opword 0x40810020
		lis r3, batSpotDisp@ha
		lfs f1, float_neg1000_8041c82c(r2)
		addi r5, r3, batSpotDisp@l
		opword 0x38800000
		opword 0x38600006
		opword 0x38C00000
		bl dispEntry
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop
#pragma dont_inline reset

#pragma defer_codegen reset

#pragma dont_inline on
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
asm void batSpotInit(void) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stfd f30, 0x40(r1)
	psq_st f30, 0x48(r1), 0, 0
	stfd f29, 0x30(r1)
	psq_st f29, 0x38(r1), 0, 0
	stmw r29, 0x24(r1)
	lwz r4, wp(r13)
	li r0, 0x5
	lis r5, vec3_802f31a8@ha
	li r3, 0x4
	stw r0, 0x0(r4)
	addi r31, r5, vec3_802f31a8@l
	lwz r4, wp(r13)
	lwz r0, 0x0(r4)
	mulli r4, r0, 0x2c
	bl __memAlloc
	lwz r5, wp(r13)
	li r4, 0x0
	stw r3, 0x4(r5)
	lwz r3, wp(r13)
	lwz r0, 0x0(r3)
	lwz r3, 0x4(r3)
	mulli r5, r0, 0x2c
	bl memset
	lfs f29, float_50_8041c834(r2)
	li r29, 0x0
	lfd f30, 0x78(r31)
	lis r30, 0x4330
	lfs f31, float_neg100_8041c830(r2)
L_af_1:
	bl batSpotEntry
	xoris r0, r29, 0x8000
	lwz r6, 0x30(r31)
	stw r0, 0x1c(r1)
	addi r29, r29, 0x1
	lwz r5, 0x34(r31)
	cmpwi r29, 0x5
	stw r30, 0x18(r1)
	lwz r4, 0x38(r31)
	lfd f0, 0x18(r1)
	stw r6, 0x8(r1)
	fsubs f0, f0, f30
	stw r4, 0x10(r1)
	fmadds f0, f29, f0, f31
	stw r5, 0xc(r1)
	stfs f0, 0x8(r1)
	lwz r0, 0x8(r1)
	stw r0, 0x4(r3)
	stw r5, 0x8(r3)
	stw r4, 0xc(r3)
	lwz r4, 0x3c(r31)
	lwz r0, 0x40(r31)
	stw r4, 0x10(r3)
	stw r0, 0x14(r3)
	lwz r0, 0x44(r31)
	stw r0, 0x18(r3)
	lwz r4, 0x48(r31)
	lwz r0, 0x4c(r31)
	stw r4, 0x1c(r3)
	stw r0, 0x20(r3)
	lwz r0, 0x50(r31)
	stw r0, 0x24(r3)
	lwz r0, dat_8041c7ec(r2)
	stw r0, 0x28(r3)
	blt L_af_1
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	psq_l f29, 0x38(r1), 0, 0
	lfd f29, 0x30(r1)
	lmw r29, 0x24(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}
#pragma dont_inline reset

#endif
BattleStage* BattleStageGetPtr(void) {
    return &_battleWorkPointer->stage;
}

#ifndef NONMATCHING
#pragma dont_inline on
#endif
void BattleStageInit(void) {
	StageWork* s = STG;
	s32 i;

	memset(s, 0, sizeof(StageWork));
	s->field_0 = 0;
	for (i = 0; i < 12; i++) {
		StageLight* l = &s->lights[i];
		l->flags = 0;
		l->data = NULL;
	}
	s->stgDark.flags = 1;
	s->stgDark.cur = s->stgDark.base = 0;
	s->stgDark.start = 0;
	s->stgDark.target = 0;
	s->stgDark.time = 0;
	s->stgDark.max = 0;
	s->audDark.flags = 1;
	s->audDark.cur = s->audDark.base = 0x8C;
	s->audDark.start = 0;
	s->audDark.target = 0;
	s->audDark.time = 0;
	s->audDark.max = 0;
#ifdef NONMATCHING
	s->stageSizeX = 290.0f;
	s->stageSizeY = 200.0f;
	s->stageSizeZ = 90.0f;
#endif
#ifndef NONMATCHING
	s->stageSizeX = EXT_LIT(float_290_8041c854, 290.0f);
	s->stageSizeY = EXT_LIT(float_200_8041c858, 200.0f);
	s->stageSizeZ = EXT_LIT(float_90_8041c85c, 90.0f);
#endif
	s->audienceSizeX = s->stageSizeX;
#ifdef NONMATCHING
	s->audienceSizeY = -50.0f;
	s->audienceSizeZ = 200.0f;
#endif
#ifndef NONMATCHING
	s->audienceSizeY = EXT_LIT(float_neg50_8041c860, -50.0f);
	s->audienceSizeZ = EXT_LIT(float_200_8041c858, 200.0f);
#endif
	BattleStageObjectInit();
	batSpotInit();
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifdef NONMATCHING
typedef struct LightSpline {
	s32 n;          // 0x0
	s32 t[8];       // 0x4
	f32 x[4][8];    // 0x24
	f32 y[4][8];    // 0xA4
	f32 z[4][8];    // 0x124
} LightSpline;

#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void BattleStageMain(void) {
#ifdef NONMATCHING
	StageLight* l;
	s32 i;
	LightSpline* sp;
	StageWork* s = STG;

	batSpotMain();
	for (i = 0; i < 12; i++) {
		l = &s->lights[i];
		if (l->flags & 1) {
			if (l->colorTime > 0) {
				l->colorTime--;
				l->color.r = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->colorMode, l->colorStart.r, l->colorTarget.r, l->colorMax - l->colorTime, l->colorMax);
				l->color.g = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->colorMode, l->colorStart.g, l->colorTarget.g, l->colorMax - l->colorTime, l->colorMax);
				l->color.b = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->colorMode, l->colorStart.b, l->colorTarget.b, l->colorMax - l->colorTime, l->colorMax);
				if ((l->flags & 2) && l->color.r == 0 && l->color.g == 0 && l->color.b == 0) {
					l->flags = 0;
					continue;
				}
			}
			if (l->widthTime > 0) {
				l->widthTime--;
				l->width = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->widthMode, l->widthStart, l->widthTarget, l->widthMax - l->widthTime, l->widthMax);
			}
			if (l->posTime > 0) {
				l->posTime--;
				l->pos.x = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->posMode, l->posStart.x, l->posTarget.x, l->posMax - l->posTime, l->posMax);
				l->pos.y = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->posMode, l->posStart.y, l->posTarget.y, l->posMax - l->posTime, l->posMax);
				l->pos.z = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->posMode, l->posStart.z, l->posTarget.z, l->posMax - l->posTime, l->posMax);
			}
			if (l->flags & 4) {
				sp = l->data;
				l->target.x = getSpline(sp->x[0], sp->x[1], sp->x[2], sp->x[3], sp->t, sp->n, l->targetTime);
				l->target.y = getSpline(sp->y[0], sp->y[1], sp->y[2], sp->y[3], sp->t, sp->n, l->targetTime);
				l->target.z = getSpline(sp->z[0], sp->z[1], sp->z[2], sp->z[3], sp->t, sp->n, l->targetTime);
				l->targetTime++;
				if (l->targetTime >= sp->t[sp->n - 1]) {
					if (l->flags & 8) {
						l->targetTime -= sp->t[sp->n - 1];
					} else {
						l->targetTime = sp->t[sp->n - 1];
					}
				}
			} else {
				if (l->targetTime > 0) {
					l->targetTime--;
					l->target.x = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->targetMode, l->targetStart.x, l->targetTarget.x, l->targetMax - l->targetTime, l->targetMax);
					l->target.y = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->targetMode, l->targetStart.y, l->targetTarget.y, l->targetMax - l->targetTime, l->targetMax);
					l->target.z = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->targetMode, l->targetStart.z, l->targetTarget.z, l->targetMax - l->targetTime, l->targetMax);
				}
				if (l->data != NULL) {
					__memFree(HEAP_BATTLE, l->data);
					l->data = NULL;
				}
			}
			if (l->upTime > 0) {
				l->upTime--;
				l->up.x = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->upMode, l->upStart.x, l->upTarget.x, l->upMax - l->upTime, l->upMax);
				l->up.y = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->upMode, l->upStart.y, l->upTarget.y, l->upMax - l->upTime, l->upMax);
				l->up.z = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->upMode, l->upStart.z, l->upTarget.z, l->upMax - l->upTime, l->upMax);
			}
		} else {
			if (l->data != NULL) {
				__memFree(HEAP_BATTLE, l->data);
				l->data = NULL;
			}
		}
	}
	if (s->stgDark.time > 0) {
		s->stgDark.time--;
		s->stgDark.cur = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&s->stgDark.mode, s->stgDark.start, s->stgDark.target, s->stgDark.max - s->stgDark.time, s->stgDark.max);
	}
	if (s->stgDark.baseTime > 0) {
		s->stgDark.baseTime--;
		s->stgDark.base = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&s->stgDark.baseMode, s->stgDark.baseStart, s->stgDark.baseTarget, s->stgDark.baseMax - s->stgDark.baseTime, s->stgDark.baseMax);
	}
	if (s->audDark.time > 0) {
		s->audDark.time--;
		s->audDark.cur = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&s->audDark.mode, s->audDark.start, s->audDark.target, s->audDark.max - s->audDark.time, s->audDark.max);
	}
	if (s->audDark.baseTime > 0) {
		s->audDark.baseTime--;
		s->audDark.base = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&s->audDark.baseMode, s->audDark.baseStart, s->audDark.baseTarget, s->audDark.baseMax - s->audDark.baseTime, s->audDark.baseMax);
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FF90
		opword 0x7C0802A6
		opword 0x90010074
		opword 0xBF61005C
		lwz r3, _battleWorkPointer(r13)
		opword 0x3FE30001
		opword 0x3BFF63E0
		bl batSpotMain
		opword 0x3BA00000
		opword 0x3B800000
		opword 0x3BDC0004
		opword 0x7FDFF214
		opword 0x801E0000
		opword 0x540007FF
		opword 0x41820400
		opword 0x807E0030
		opword 0x2C030000
		opword 0x4081015C
		opword 0x3803FFFF
		opword 0x3CC04330
		opword 0x901E0030
		lis r3, double_to_int_mask_802f3228@ha
		lfd f2, double_to_int_mask_802f3228@l(r3)
		opword 0x881E0028
		opword 0x889E002C
		opword 0x9001000C
		opword 0x887E0038
		opword 0x90C10008
		opword 0x80BE0034
		opword 0x7C630774
		opword 0xC8010008
		opword 0x90810014
		opword 0x801E0030
		opword 0xEC201028
		opword 0x90C10010
		opword 0x7C802850
		opword 0xC8010010
		opword 0xEC401028
		bl intplGetValue
		opword 0xFC00081E
		opword 0x3C004330
		lis r3, double_to_int_mask_802f3228@ha
		opword 0x90010020
		lfd f2, double_to_int_mask_802f3228@l(r3)
		opword 0xD8010018
		opword 0x8061001C
		opword 0x90010028
		opword 0x987E0024
		opword 0x887E0029
		opword 0x881E002D
		opword 0x90610024
		opword 0x887E0038
		opword 0x9001002C
		opword 0xC8210020
		opword 0x7C630774
		opword 0xC8010028
		opword 0xEC211028
		opword 0x80BE0034
		opword 0x801E0030
		opword 0xEC401028
		opword 0x7C802850
		bl intplGetValue
		opword 0xFC00081E
		opword 0x3C004330
		lis r3, double_to_int_mask_802f3228@ha
		opword 0x90010038
		lfd f2, double_to_int_mask_802f3228@l(r3)
		opword 0xD8010030
		opword 0x80610034
		opword 0x90010040
		opword 0x987E0025
		opword 0x887E002A
		opword 0x881E002E
		opword 0x9061003C
		opword 0x887E0038
		opword 0x90010044
		opword 0xC8210038
		opword 0x7C630774
		opword 0xC8010040
		opword 0xEC211028
		opword 0x80BE0034
		opword 0x801E0030
		opword 0xEC401028
		opword 0x7C802850
		bl intplGetValue
		opword 0xFC00081E
		opword 0xD8010048
		opword 0x8001004C
		opword 0x981E0026
		opword 0x801E0000
		opword 0x540007BD
		opword 0x41820034
		opword 0x881E0024
		opword 0x28000000
		opword 0x40820028
		opword 0x881E0025
		opword 0x28000000
		opword 0x4082001C
		opword 0x881E0026
		opword 0x28000000
		opword 0x40820010
		opword 0x38000000
		opword 0x901E0000
		opword 0x480002B8
		opword 0x807E0048
		opword 0x2C030000
		opword 0x40810030
		opword 0x3803FFFF
		opword 0x901E0048
		opword 0x887E0050
		opword 0x80BE004C
		opword 0x801E0048
		opword 0x7C630774
		opword 0xC03E0040
		opword 0xC05E0044
		opword 0x7C802850
		bl intplGetValue
		opword 0xD03E003C
		opword 0x807E0078
		opword 0x2C030000
		opword 0x40810078
		opword 0x3803FFFF
		opword 0x901E0078
		opword 0x887E0080
		opword 0x80BE007C
		opword 0x801E0078
		opword 0x7C630774
		opword 0xC03E0060
		opword 0xC05E006C
		opword 0x7C802850
		bl intplGetValue
		opword 0xD03E0054
		opword 0x887E0080
		opword 0x80BE007C
		opword 0x801E0078
		opword 0x7C630774
		opword 0xC03E0064
		opword 0xC05E0070
		opword 0x7C802850
		bl intplGetValue
		opword 0xD03E0058
		opword 0x887E0080
		opword 0x80BE007C
		opword 0x801E0078
		opword 0x7C630774
		opword 0xC03E0068
		opword 0xC05E0074
		opword 0x7C802850
		bl intplGetValue
		opword 0xD03E005C
		opword 0x801E0000
		opword 0x5400077B
		opword 0x418200B8
		opword 0x837E00E4
		opword 0x813E00A8
		opword 0x811B0000
		opword 0x387B0024
		opword 0x389B0044
		opword 0x38BB0064
		opword 0x38DB0084
		opword 0x38FB0004
		bl getSpline
		opword 0xD03E0084
		opword 0x387B00A4
		opword 0x389B00C4
		opword 0x38BB00E4
		opword 0x811B0000
		opword 0x38DB0104
		opword 0x813E00A8
		opword 0x38FB0004
		bl getSpline
		opword 0xD03E0088
		opword 0x387B0124
		opword 0x389B0144
		opword 0x38BB0164
		opword 0x811B0000
		opword 0x38DB0184
		opword 0x813E00A8
		opword 0x38FB0004
		bl getSpline
		opword 0xD03E008C
		opword 0x807E00A8
		opword 0x38030001
		opword 0x901E00A8
		opword 0x801B0000
		opword 0x807E00A8
		opword 0x5400103A
		opword 0x7C9B002E
		opword 0x7C032000
		opword 0x418000C0
		opword 0x801E0000
		opword 0x54000739
		opword 0x41820010
		opword 0x7C041850
		opword 0x901E00A8
		opword 0x480000A8
		opword 0x909E00A8
		opword 0x480000A0
		opword 0x807E00A8
		opword 0x2C030000
		opword 0x40810078
		opword 0x3803FFFF
		opword 0x901E00A8
		opword 0x887E00B0
		opword 0x80BE00AC
		opword 0x801E00A8
		opword 0x7C630774
		opword 0xC03E0090
		opword 0xC05E009C
		opword 0x7C802850
		bl intplGetValue
		opword 0xD03E0084
		opword 0x887E00B0
		opword 0x80BE00AC
		opword 0x801E00A8
		opword 0x7C630774
		opword 0xC03E0094
		opword 0xC05E00A0
		opword 0x7C802850
		bl intplGetValue
		opword 0xD03E0088
		opword 0x887E00B0
		opword 0x80BE00AC
		opword 0x801E00A8
		opword 0x7C630774
		opword 0xC03E0098
		opword 0xC05E00A4
		opword 0x7C802850
		bl intplGetValue
		opword 0xD03E008C
		opword 0x809E00E4
		opword 0x28040000
		opword 0x41820014
		opword 0x38600004
		bl __memFree
		opword 0x38000000
		opword 0x901E00E4
		opword 0x807E00D8
		opword 0x2C030000
		opword 0x40810098
		opword 0x3803FFFF
		opword 0x901E00D8
		opword 0x887E00E0
		opword 0x80BE00DC
		opword 0x801E00D8
		opword 0x7C630774
		opword 0xC03E00C0
		opword 0xC05E00CC
		opword 0x7C802850
		bl intplGetValue
		opword 0xD03E00B4
		opword 0x887E00E0
		opword 0x80BE00DC
		opword 0x801E00D8
		opword 0x7C630774
		opword 0xC03E00C4
		opword 0xC05E00D0
		opword 0x7C802850
		bl intplGetValue
		opword 0xD03E00B8
		opword 0x887E00E0
		opword 0x80BE00DC
		opword 0x801E00D8
		opword 0x7C630774
		opword 0xC03E00C8
		opword 0xC05E00D4
		opword 0x7C802850
		bl intplGetValue
		opword 0xD03E00BC
		opword 0x48000020
		opword 0x809E00E4
		opword 0x28040000
		opword 0x41820014
		opword 0x38600004
		bl __memFree
		opword 0x38000000
		opword 0x901E00E4
		opword 0x3BBD0001
		opword 0x3B9C00E8
		opword 0x2C1D000C
		opword 0x4180FBC8
		opword 0x807F0AF0
		opword 0x2C030000
		opword 0x40810068
		opword 0x3803FFFF
		opword 0x3CC04330
		opword 0x901F0AF0
		lis r3, double_to_int_mask_802f3228@ha
		lfd f2, double_to_int_mask_802f3228@l(r3)
		opword 0x881F0AEA
		opword 0x889F0AEC
		opword 0x9001004C
		opword 0x887F0B00
		opword 0x90C10048
		opword 0x80BF0AF8
		opword 0x7C630774
		opword 0xC8010048
		opword 0x90810044
		opword 0x801F0AF0
		opword 0xEC201028
		opword 0x90C10040
		opword 0x7C802850
		opword 0xC8010040
		opword 0xEC401028
		bl intplGetValue
		opword 0xFC00081E
		opword 0xD8010038
		opword 0x8001003C
		opword 0x981F0AE8
		opword 0x807F0AF4
		opword 0x2C030000
		opword 0x40810068
		opword 0x3803FFFF
		opword 0x3CC04330
		opword 0x901F0AF4
		lis r3, double_to_int_mask_802f3228@ha
		lfd f2, double_to_int_mask_802f3228@l(r3)
		opword 0x881F0AEB
		opword 0x889F0AED
		opword 0x9001004C
		opword 0x887F0B01
		opword 0x90C10048
		opword 0x80BF0AFC
		opword 0x7C630774
		opword 0xC8010048
		opword 0x90810044
		opword 0x801F0AF4
		opword 0xEC201028
		opword 0x90C10040
		opword 0x7C802850
		opword 0xC8010040
		opword 0xEC401028
		bl intplGetValue
		opword 0xFC00081E
		opword 0xD8010038
		opword 0x8001003C
		opword 0x981F0AE9
		opword 0x807F0B10
		opword 0x2C030000
		opword 0x40810068
		opword 0x3803FFFF
		opword 0x3CC04330
		opword 0x901F0B10
		lis r3, double_to_int_mask_802f3228@ha
		lfd f2, double_to_int_mask_802f3228@l(r3)
		opword 0x881F0B0A
		opword 0x889F0B0C
		opword 0x9001004C
		opword 0x887F0B20
		opword 0x90C10048
		opword 0x80BF0B18
		opword 0x7C630774
		opword 0xC8010048
		opword 0x90810044
		opword 0x801F0B10
		opword 0xEC201028
		opword 0x90C10040
		opword 0x7C802850
		opword 0xC8010040
		opword 0xEC401028
		bl intplGetValue
		opword 0xFC00081E
		opword 0xD8010038
		opword 0x8001003C
		opword 0x981F0B08
		opword 0x807F0B14
		opword 0x2C030000
		opword 0x40810068
		opword 0x3803FFFF
		opword 0x3CC04330
		opword 0x901F0B14
		lis r3, double_to_int_mask_802f3228@ha
		lfd f2, double_to_int_mask_802f3228@l(r3)
		opword 0x881F0B0B
		opword 0x889F0B0D
		opword 0x9001004C
		opword 0x887F0B21
		opword 0x90C10048
		opword 0x80BF0B1C
		opword 0x7C630774
		opword 0xC8010048
		opword 0x90810044
		opword 0x801F0B14
		opword 0xEC201028
		opword 0x90C10040
		opword 0x7C802850
		opword 0xC8010040
		opword 0xEC401028
		bl intplGetValue
		opword 0xFC00081E
		opword 0xD8010038
		opword 0x8001003C
		opword 0x981F0B09
		opword 0xBB61005C
		opword 0x80010074
		opword 0x7C0803A6
		opword 0x38210070
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

void BattleStageEnd(void) {
	s32 i;
	StageWork* s = STG;

	for (i = 0; i < 12; i++) {
		StageLight* l = &s->lights[i];
		if (l->data != NULL) {
			__memFree(HEAP_BATTLE, l->data);
			l->data = NULL;
		}
	}
}

void BattleStageDisp(void) {
	BattleGetUnitPtr(_battleWorkPointer, _battleWorkPointer->activeUnitId);
#ifdef NONMATCHING
	dispEntry(CAMERA_3D, 5000.0f, 2, BattleStageDispDark, NULL);
	dispEntry(CAMERA_3D, 6000.0f, 2, BattleStageDispLight, NULL);
#endif
#ifndef NONMATCHING
	dispEntry(CAMERA_3D, EXT_LIT(float_5000_8041c84c, 5000.0f), 2, BattleStageDispDark, NULL);
	dispEntry(CAMERA_3D, EXT_LIT(float_6000_8041c850, 6000.0f), 2, BattleStageDispLight, NULL);
#endif
}

#pragma dont_inline on
void DarkByPoint(u8 alpha, f32 x, f32 y, f32 z) {
	GXPosition3f32(x, y, z);
	GXColor4u8(0, 0, 0, alpha);
}
#pragma dont_inline reset

#pragma dont_inline on
#ifndef NONMATCHING
#pragma dont_inline on
#endif
void DarkBySquare(f32 x0, f32 y0, f32 x1, f32 y1, f32 z, u8 alpha) {
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	DarkByPoint(alpha, x0, y0, z);
	DarkByPoint(alpha, x1, y0, z);
	DarkByPoint(alpha, x1, y1, z);
	DarkByPoint(alpha, x0, y1, z);
}
#pragma dont_inline reset
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void BattleStageDispDark(CameraId camId, void* param) {
#ifdef NONMATCHING
	StageWork* s = STG;
	CameraEntry* cam = camGetPtr(CAMERA_3D);
	StageDark* aud;

	GXSetCullMode(GX_CULL_BACK);
	GXSetZCompLoc(GX_TRUE);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
	GXSetNumTexGens(0);
	GXLoadPosMtxImm(cam->view, GX_PNMTX0);
	GXSetNumTevStages(1);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	aud = &s->audDark;
	GXSetZMode(GX_TRUE, GX_GEQUAL, GX_FALSE);
	DarkBySquare(-640.0f, 640.0f, 640.0f, -640.0f, 105.0f, aud->cur);
	GXSetZMode(GX_TRUE, GX_LESS, GX_FALSE);
	DarkBySquare(640.0f, 640.0f, -640.0f, -640.0f, 105.0f, aud->cur);
	GXSetZMode(GX_TRUE, GX_LESS, GX_FALSE);
	DarkBySquare(-640.0f, 640.0f, 640.0f, -640.0f, 105.0f, s->stgDark.cur);
}

void BattleStageDispLight(CameraId camId, void* param) {
	s32 i, j;
	f32 width;
	StageWork* s = STG;
	CameraEntry* cam = camGetPtr(CAMERA_3D);

	GXSetCullMode(GX_CULL_BACK);
	GXSetZCompLoc(GX_TRUE);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCCLR, GX_BL_ONE, GX_LO_NOOP);
	GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
	GXSetNumTexGens(0);
	GXSetNumTevStages(1);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GXLoadPosMtxImm(cam->view, GX_PNMTX0);
	for (i = 0; i < 12; i++) {
		if (s->lights[i].flags & 1) {
			Mtx m;
			Vec v;
			Vec axis;

			axis = (Vec){s->lights[i].target.x - s->lights[i].pos.x, s->lights[i].target.y - s->lights[i].pos.y, s->lights[i].target.z - s->lights[i].pos.z};
			width = s->lights[i].width;
			v = s->lights[i].up;
			for (j = 0; j < 18; j++) {
				f32 px = s->lights[i].pos.x;
				f32 py = s->lights[i].pos.y;
				f32 pz = s->lights[i].pos.z;
				f32 ex = (s->lights[i].target.x - px) * 2.0f + px;
				f32 ey = (s->lights[i].target.y - py) * 2.0f + py;
				f32 ez = (s->lights[i].target.z - pz) * 2.0f + pz;
				f32 ax = v.x * width + ex;
				f32 ay = v.y * width + ey;
				f32 az = v.z * width + ez;
				f32 bx, by, bz;
				u8 r, g, b;

				PSMTXRotAxisRad(m, &axis, 0.34906584f);
				PSMTXMultVec(m, &v, &v);
				PSVECNormalize(&v, &v);
				bx = v.x * width + ex;
				by = v.y * width + ey;
				bz = v.z * width + ez;
				r = s->lights[i].color.r;
				g = s->lights[i].color.g;
				b = s->lights[i].color.b;
				GXBegin(GX_TRIANGLES, GX_VTXFMT0, 3);
				GXPosition3f32(px, py, pz);
				GXColor4u8(r, g, b, 0);
				GXPosition3f32(ax, ay, az);
				GXColor4u8(r, g, b, 0);
				GXPosition3f32(bx, by, bz);
				GXColor4u8(r, g, b, 0);
			}
		}
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x38600004
		opword 0x90010014
		opword 0xBFC10008
		lwz r4, _battleWorkPointer(r13)
		opword 0x3FC40001
		bl camGetPtr
		opword 0x7C7F1B78
		opword 0x38600002
		bl GXSetCullMode
		opword 0x38600001
		bl GXSetZCompLoc
		opword 0x38600007
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetAlphaCompare
		opword 0x38600001
		opword 0x38800004
		opword 0x38A00005
		opword 0x38C00005
		bl GXSetBlendMode
		bl GXClearVtxDesc
		opword 0x38600009
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x3860000B
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
		opword 0x38600001
		bl GXSetNumChans
		opword 0x38600004
		opword 0x38800000
		opword 0x38A00001
		opword 0x38C00001
		opword 0x38E00000
		opword 0x39000002
		opword 0x39200002
		bl GXSetChanCtrl
		opword 0x38600000
		bl GXSetNumTexGens
		opword 0x387F011C
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x38600001
		bl GXSetNumTevStages
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E0000A
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00005
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x3BFE6EE4
		opword 0x38600001
		opword 0x38800006
		opword 0x38A00000
		bl GXSetZMode
		lfs f1, float_neg640_8041c840(r2)
		lfs f2, float_640_8041c844(r2)
		opword 0xFC800890
		lfs f5, float_105_8041c848(r2)
		opword 0xFC601090
		opword 0x887F0004
		bl DarkBySquare
		opword 0x38600001
		opword 0x38800001
		opword 0x38A00000
		bl GXSetZMode
		lfs f1, float_640_8041c844(r2)
		lfs f3, float_neg640_8041c840(r2)
		opword 0xFC400890
		lfs f5, float_105_8041c848(r2)
		opword 0xFC801890
		opword 0x887F0004
		bl DarkBySquare
		opword 0x38600001
		opword 0x38800001
		opword 0x38A00000
		bl GXSetZMode
		lfs f1, float_neg640_8041c840(r2)
		lfs f2, float_640_8041c844(r2)
		opword 0xFC800890
		lfs f5, float_105_8041c848(r2)
		opword 0xFC601090
		opword 0x887E6EC8
		bl DarkBySquare
		opword 0xBBC10008
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
#endif
	}
}
#ifndef NONMATCHING
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void BattleStageDispLight(CameraId camId, void* param) {
	char _af_pad[92];
	asm volatile {
		lwz r4, _battleWorkPointer(r13)
		opword 0x38600004
		opword 0x3FA40001
		opword 0x3BBD63E0
		bl camGetPtr
		opword 0x7C7B1B78
		opword 0x38600002
		bl GXSetCullMode
		opword 0x38600001
		bl GXSetZCompLoc
		opword 0x38600007
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetAlphaCompare
		opword 0x38600001
		opword 0x38800002
		opword 0x38A00001
		opword 0x38C00005
		bl GXSetBlendMode
		opword 0x38600001
		opword 0x38800003
		opword 0x38A00000
		bl GXSetZMode
		bl GXClearVtxDesc
		opword 0x38600009
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x3860000B
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
		opword 0x38600001
		bl GXSetNumChans
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00001
		opword 0x38C00001
		opword 0x38E00000
		opword 0x39000002
		opword 0x39200002
		bl GXSetChanCtrl
		opword 0x38600000
		bl GXSetNumTexGens
		opword 0x38600001
		bl GXSetNumTevStages
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E0000A
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x387B011C
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x3BC00000
		opword 0x3B800000
		opword 0x7FFDE214
		opword 0x801F0004
		opword 0x540007FF
		opword 0x418201A0
		lis r3, vec3_802f31a8@ha
		opword 0xC03F0088
		addi r5, r3, vec3_802f31a8@l
		opword 0xC01F0058
		opword 0x80850000
		opword 0x3B400000
		opword 0x80650004
		opword 0xEC210028
		opword 0x80050008
		opword 0x3F60CC01
		stw r4, _af_pad+0(r1)
		opword 0xC05F008C
		opword 0xC01F005C
		opword 0xD0210008
		opword 0xC03F0090
		opword 0xEC420028
		opword 0xC01F0060
		opword 0x9061000C
		opword 0x80810008
		opword 0xEC010028
		opword 0x90010010
		lfs f30, float_2_8041c838(r2)
		opword 0xD041000C
		opword 0xD0010010
		opword 0x8061000C
		opword 0x80010010
		opword 0x90810014
		opword 0x90610018
		opword 0x9001001C
		opword 0xC3FF0040
		opword 0x807F00B8
		opword 0x801F00BC
		opword 0x90610020
		opword 0x90010024
		opword 0x801F00C0
		opword 0x90010028
		opword 0xC3BF0058
		opword 0x3861002C
		opword 0xC01F0088
		opword 0x38810014
		opword 0xC39F005C
		opword 0xC03F008C
		opword 0xEC40E828
		opword 0xC37F0060
		opword 0xC01F0090
		opword 0xEC81E028
		opword 0xEF5EE8BA
		opword 0xC0610020
		opword 0xEC20D828
		opword 0xC0410024
		opword 0xEF3EE13A
		opword 0xC0010028
		opword 0xEF1ED87A
		lfs f1, float_0p34907_8041c83c(r2)
		opword 0xEEE3D7FA
		opword 0xEEC2CFFA
		fmadds f21, f0, f31, f24
		bl PSMTXRotAxisRad
		opword 0x38810020
		opword 0x3861002C
		opword 0x7C852378
		bl PSMTXMultVec
		opword 0x38610020
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0xC0410020
		opword 0x38600090
		opword 0xC0210024
		opword 0x38800000
		opword 0xC0010028
		opword 0xEF42D7FA
		opword 0xEF21CFFA
		opword 0x8B3F0028
		opword 0xEF00C7FA
		opword 0x8B1F0029
		lbz r23, 0x2a(r31)
		opword 0x38A00003
		bl GXBegin
		opword 0xD3BB8000
		opword 0x3B5A0001
		opword 0x38000000
		opword 0xD39B8000
		opword 0x2C1A0012
		opword 0xD37B8000
		opword 0x9B3B8000
		opword 0x9B1B8000
		opword 0x9AFB8000
		opword 0x981B8000
		opword 0xD2FB8000
		opword 0xD2DB8000
		opword 0xD2BB8000
		opword 0x9B3B8000
		opword 0x9B1B8000
		opword 0x9AFB8000
		opword 0x981B8000
		opword 0xD35B8000
		opword 0xD33B8000
		opword 0xD31B8000
		opword 0x9B3B8000
		opword 0x9B1B8000
		opword 0x9AFB8000
		opword 0x981B8000
		opword 0x4180FEF8
		opword 0x3BDE0001
		opword 0x3B9C00E8
		opword 0x2C1E000C
		opword 0x4180FE48
	}
}
#pragma pop
#endif

void BattleStageOnLightInCommand(void) {
}

void BattleStageOffLightInCommand(void) {
}

void BattleStageOnLightFriendInCommand(void) {
}

void BattleStageOffLightFriendInCommand(void) {
}

void BattleStageOnLightEnemyInCommand(void) {
}

void BattleStageOffLightEnemyInCommand(void) {
}

s32 BattleStageGetLightNumberByName(const char* name) {
	StageWork* s = STG;
	s32 i;

	for (i = 0; i < 12; i++) {
		StageLight* l = &s->lights[i];
		if ((l->flags & 1) && !strcmp(l->name, name)) {
			return i;
		}
	}
	return -1;
}

s32 BattleStageSysLightEntry(const char* name) {
	StageWork* s = STG;
	s32 i;

	for (i = 0; i <= 6; i++) {
		StageLight* l = &s->lights[i];
		if ((l->flags & 1) && !strcmp(l->name, name)) {
		}
	}
	for (i = 0; i < 7; i++) {
		StageLight* l = &s->lights[i];
		if (!(l->flags & 1)) {
			l->flags = 1;
			strcpy(l->name, name);
			break;
		}
	}
	return i;
}

#ifdef NONMATCHING
#pragma opt_propagation off
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void BattleStageLightRelease(s32 idx, s32 time, u8 mode) {
#ifdef NONMATCHING
	StageLight* l = &STG->lights[idx];

	if (l->flags & 1) {
		if (time == 0) {
			l->flags = 0;
		} else {
			l->flags |= 2;
			l->colorStart = (GXColor){l->color.r, l->color.g, l->color.b};
			{ GXColor z = {0, 0, 0}; l->colorTarget = z; }
			l->colorTime = time;
			l->colorMax = time;
			l->colorMode = mode;
		}
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFF0
		opword 0x1C6300E8
		lwz r6, _battleWorkPointer(r13)
		opword 0x38E30004
		opword 0x3CC60001
		opword 0x38C663E0
		opword 0x7CE63A14
		opword 0x80670000
		opword 0x546007FF
		opword 0x4182005C
		opword 0x2C040000
		opword 0x40820010
		opword 0x38000000
		opword 0x90070000
		opword 0x48000048
		opword 0x60600002
		opword 0x90070000
		lwz r0, unk_80423018(r2)
		opword 0x88C70024
		opword 0x90010008
		opword 0x88670025
		opword 0x88070026
		opword 0x98C10008
		opword 0x98610009
		opword 0x9801000A
		opword 0x80010008
		opword 0x90070028
		lwz r0, unk_8042301c(r2)
		opword 0x9007002C
		opword 0x90870030
		opword 0x90870034
		opword 0x98A70038
		opword 0x38210010
#endif
	}
}
#ifdef NONMATCHING
#pragma opt_propagation reset
#endif
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
#pragma opt_propagation off
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void BattleStageLightSetLightColor(s32 idx, u8 r, u8 g, u8 b, s32 time, u8 mode) {
#ifdef NONMATCHING
	StageLight* l = &STG->lights[idx];

	l->colorStart = (GXColor){l->color.r, l->color.g, l->color.b};
	l->colorTarget = (GXColor){r, g, b};
	l->colorTime = time;
	l->colorMax = time;
	l->colorMode = mode;
	if (time == 0) {
		l->color = (GXColor){l->color.r, l->color.g, l->color.b, 0xFF};
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFE0
		opword 0x1C6300E8
		opword 0x2C070000
		lwz r9, _battleWorkPointer(r13)
		lwz r0, unk_80423020(r2)
		opword 0x39430004
		opword 0x3D290001
		opword 0x392963E0
		opword 0x90010010
		opword 0x7D495214
		opword 0x892A0024
		opword 0x886A0025
		opword 0x880A0026
		opword 0x99210010
		opword 0x98610011
		opword 0x98010012
		opword 0x80010010
		opword 0x900A0028
		lwz r0, unk_80423024(r2)
		opword 0x9001000C
		opword 0x9881000C
		opword 0x98A1000D
		opword 0x98C1000E
		opword 0x8001000C
		opword 0x900A002C
		opword 0x90EA0030
		opword 0x90EA0034
		opword 0x990A0038
		opword 0x4082002C
		lwz r0, dat_8041c7e8(r2)
		opword 0x888A0024
		opword 0x90010008
		opword 0x886A0025
		opword 0x880A0026
		opword 0x98810008
		opword 0x98610009
		opword 0x9801000A
		opword 0x80010008
		opword 0x900A0024
		opword 0x38210020
#endif
	}
}
#ifdef NONMATCHING
#pragma opt_propagation reset
#endif
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
#pragma opt_propagation off
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void BattleStageLightSetWidth(s32 idx, s32 width, s32 time, u8 mode) {
#ifdef NONMATCHING
	StageLight* l = &STG->lights[idx];

	l->widthStart = l->width;
	l->widthTarget = width;
	l->widthTime = time;
	l->widthMax = time;
	l->widthMode = mode;
	if (time == 0) {
		l->width = width;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFF0
		opword 0x1CE300E8
		opword 0x6C838000
		lwz r8, _battleWorkPointer(r13)
		opword 0x3C004330
		lis r4, double_to_int_802f3220@ha
		opword 0x9061000C
		opword 0x3D080001
		opword 0x38E70004
		opword 0x90010008
		opword 0x390863E0
		opword 0x7CE83A14
		lfd f1, double_to_int_802f3220@l(r4)
		opword 0xC8010008
		opword 0x2C050000
		opword 0xC047003C
		opword 0xEC000828
		opword 0xD0470040
		opword 0xD0070044
		opword 0x90A70048
		opword 0x90A7004C
		opword 0x98C70050
		opword 0x40820018
		opword 0x9061000C
		opword 0x90010008
		opword 0xC8010008
		opword 0xEC000828
		opword 0xD007003C
		opword 0x38210010
#endif
	}
}
#ifdef NONMATCHING
#pragma opt_propagation reset
#endif
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
#pragma opt_propagation off
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void BattleStageLightSetPosition(s32 idx, f32 x, f32 y, f32 z, s32 time, u8 mode) {
#ifdef NONMATCHING
	StageLight* l = &STG->lights[idx];

	l->posStart.x = l->pos.x;
	l->posStart.y = l->pos.y;
	l->posStart.z = l->pos.z;
	l->posTarget.x = x;
	l->posTarget.y = y;
	l->posTarget.z = z;
	l->posTime = time;
	l->posMax = time;
	l->posMode = mode;
	if (time == 0) {
		l->pos = (Vec){x, y, z};
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFE0
		opword 0x1C6300E8
		opword 0x2C040000
		lwz r6, _battleWorkPointer(r13)
		opword 0x38E30004
		opword 0x3CC60001
		opword 0x38C663E0
		opword 0x7CE63A14
		opword 0xC0070054
		opword 0xD0070060
		opword 0xC0070058
		opword 0xD0070064
		opword 0xC007005C
		opword 0xD0070068
		opword 0xD027006C
		opword 0xD0470070
		opword 0xD0670074
		opword 0x90870078
		opword 0x9087007C
		opword 0x98A70080
		opword 0x40820048
		lis r3, vec3_802f31b4@ha
		addi r4, r3, vec3_802f31b4@l
		opword 0x80040000
		opword 0x80640004
		opword 0x90010008
		opword 0x80040008
		opword 0x9061000C
		opword 0xD0210008
		opword 0x90010010
		opword 0x80010008
		opword 0xD041000C
		opword 0xD0610010
		opword 0x8061000C
		opword 0x90070054
		opword 0x80010010
		opword 0x90670058
		opword 0x9007005C
		opword 0x38210020
#endif
	}
}
#ifdef NONMATCHING
#pragma opt_propagation reset
#endif
#ifndef NONMATCHING
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void BattleStageLightSetTarget(s32 idx, f32 x, f32 y, f32 z, s32 time, u8 mode) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x1C6300E8
		opword 0x2C040000
		lwz r6, _battleWorkPointer(r13)
		opword 0x38E30004
		opword 0x3CC60001
		opword 0x38C663E0
		opword 0x7CE63A14
		opword 0xC0070084
		opword 0xD0070090
		opword 0xC0070088
		opword 0xD0070094
		opword 0xC007008C
		opword 0xD0070098
		opword 0xD027009C
		opword 0xD04700A0
		opword 0xD06700A4
		opword 0x908700A8
		opword 0x908700AC
		opword 0x98A700B0
		opword 0x80070000
		opword 0x540007B8
		opword 0x90070000
		opword 0x40820048
		lis r3, vec3_802f31c0@ha
		addi r4, r3, vec3_802f31c0@l
		opword 0x80040000
		opword 0x80640004
		opword 0x90010008
		opword 0x80040008
		opword 0x9061000C
		opword 0xD0210008
		opword 0x90010010
		opword 0x80010008
		opword 0xD041000C
		opword 0xD0610010
		opword 0x8061000C
		opword 0x90070084
		opword 0x80010010
		opword 0x90670088
		opword 0x9007008C
		opword 0x38210020
	}
}
#pragma pop
#endif

#pragma dont_inline on
#ifdef NONMATCHING
#pragma opt_propagation off
void BattleStageLightSetTarget(s32 idx, f32 x, f32 y, f32 z, s32 time, u8 mode) {
	StageLight* l = &STG->lights[idx];

	l->targetStart.x = l->target.x;
	l->targetStart.y = l->target.y;
	l->targetStart.z = l->target.z;
	l->targetTarget.x = x;
	l->targetTarget.y = y;
	l->targetTarget.z = z;
	l->targetTime = time;
	l->targetMax = time;
	l->targetMode = mode;
	l->flags &= ~4;
	if (time == 0) {
		l->target = (Vec){x, y, z};
	}
}
#pragma opt_propagation reset
#pragma dont_inline reset

#endif
void BattleStageLightSetTargetByUnit(s32 idx, s32 unitId, f32 x, f32 y, f32 z, s32 time, u8 mode) {
	f32 px, py, pz;
	BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, unitId);

	BtlUnit_GetPos(unit, &px, &py, &pz);
	px += x;
	py += y;
	pz += z;
	BattleStageLightSetTarget(idx, px, py, pz, time, mode);
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifdef NONMATCHING
#pragma opt_propagation off
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void BattleStageLightSetUpVec(s32 idx, f32 x, f32 y, f32 z, s32 time, u8 mode) {
#ifdef NONMATCHING
	StageLight* l = &STG->lights[idx];

	l->upStart.x = l->up.x;
	l->upStart.y = l->up.y;
	l->upStart.z = l->up.z;
	l->upTarget.x = x;
	l->upTarget.y = y;
	l->upTarget.z = z;
	l->upTime = time;
	l->upMax = time;
	l->upMode = mode;
	if (time == 0) {
		l->up = (Vec){x, y, z};
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFE0
		opword 0x1C6300E8
		opword 0x2C040000
		lwz r6, _battleWorkPointer(r13)
		opword 0x38E30004
		opword 0x3CC60001
		opword 0x38C663E0
		opword 0x7CE63A14
		opword 0xC00700B4
		opword 0xD00700C0
		opword 0xC00700B8
		opword 0xD00700C4
		opword 0xC00700BC
		opword 0xD00700C8
		opword 0xD02700CC
		opword 0xD04700D0
		opword 0xD06700D4
		opword 0x908700D8
		opword 0x908700DC
		opword 0x98A700E0
		opword 0x40820048
		lis r3, vec3_802f31cc@ha
		addi r4, r3, vec3_802f31cc@l
		opword 0x80040000
		opword 0x80640004
		opword 0x90010008
		opword 0x80040008
		opword 0x9061000C
		opword 0xD0210008
		opword 0x90010010
		opword 0x80010008
		opword 0xD041000C
		opword 0xD0610010
		opword 0x8061000C
		opword 0x900700B4
		opword 0x80010010
		opword 0x906700B8
		opword 0x900700BC
		opword 0x38210020
#endif
	}
}
#ifdef NONMATCHING
#pragma opt_propagation reset
#endif
#ifndef NONMATCHING
#pragma pop
#endif

#pragma dont_inline on
void BattleStageSetDark(StageDark* d, u8 v, s32 time, u8 mode) {
	d->start = d->cur;
	d->target = v;
	d->time = time;
	d->max = time;
	d->mode = mode;
	if (time == 0) {
		d->cur = v;
	}
}
#pragma dont_inline reset

#pragma dont_inline on
void BattleStageSetDarkBase(StageDark* d, u8 v, s32 time, u8 mode) {
	d->baseStart = d->base;
	d->baseTarget = v;
	d->baseTime = time;
	d->baseMax = time;
	d->baseMode = mode;
	if (time == 0) {
		d->base = v;
	}
}
#pragma dont_inline reset

#ifndef NONMATCHING
#pragma dont_inline on
#endif
void BattleStageSetStgDark(u8 v, s32 time, u8 mode) {
	BattleStageSetDark(&STG->stgDark, v, time, mode);
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifndef NONMATCHING
#pragma dont_inline on
#endif
void BattleStageSetStgDarkBase(u8 v, s32 time, u8 mode) {
	BattleStageSetDarkBase(&STG->stgDark, v, time, mode);
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifndef NONMATCHING
#pragma dont_inline on
#endif
void BattleStageReturnStgDarkBase(s32 time, u8 mode) {
	StageDark* d = &STG->stgDark;
	BattleStageSetDark(d, d->base, time, mode);
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifndef NONMATCHING
#pragma dont_inline on
#endif
void BattleStageSetAudDark(u8 v, s32 time, u8 mode) {
	BattleStageSetDark(&STG->audDark, v, time, mode);
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifndef NONMATCHING
#pragma dont_inline on
#endif
void BattleStageSetAudDarkBase(u8 v, s32 time, u8 mode) {
	BattleStageSetDarkBase(&STG->audDark, v, time, mode);
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifndef NONMATCHING
#pragma dont_inline on
#endif
void BattleStageReturnAudDarkBase(s32 time, u8 mode) {
	StageDark* d = &STG->audDark;
	BattleStageSetDark(d, d->base, time, mode);
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#pragma dont_inline on
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
f32 getSpline(f32* a, f32* b, f32* c, f32* d, s32* t, s32 n, s32 x) {
#ifdef NONMATCHING
	s32 i;
	f32 f;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x3568FFFF
		lis r8, double_to_int_802f3220@ha
		addi r10, r8, double_to_int_802f3220@l
		opword 0x9421FFF0
		opword 0xC84A0000
		opword 0x3D404330
		opword 0x380B0001
		lfs f0, float_0_8041c7f0(r2)
		opword 0x5568103A
		opword 0x7C0903A6
		opword 0x41800038
		opword 0x7C07402E
		opword 0x91410008
		opword 0x7C004850
		opword 0x6C008000
		opword 0x9001000C
		opword 0xC8210008
		opword 0xEC211028
		opword 0xFC010040
		opword 0x4C411382
		opword 0x41820010
		opword 0x396BFFFF
		opword 0x3908FFFC
		opword 0x4200FFD0
		opword 0x556A103A
		opword 0x3C004330
		opword 0x7D07502E
		lis r7, double_to_int_802f3220@ha
		opword 0x90010008
		opword 0x7C084850
		lfd f4, double_to_int_802f3220@l(r7)
		opword 0x6C008000
		opword 0x7C66542E
		opword 0x9001000C
		opword 0x7C45542E
		opword 0xC8010008
		opword 0x7C24542E
		opword 0xEC802028
		opword 0x7C03542E
		opword 0xEC4410FA
		opword 0xEC2408BA
		opword 0xEC24007A
		opword 0x38210010
	}
}
#pragma pop
#pragma dont_inline reset
#endif

#ifdef NONMATCHING
	for (i = n - 1; i >= 0; i--) {
		if ((f32)(x - t[i]) >= 0.0f) {
			break;
		}
	}
	f = x - t[i];
	return f * (f * (f * d[i] + c[i]) + b[i]) + a[i];
}
#pragma dont_inline reset
#endif
BattleSpotWork* BatSpotGetPtr(void) {
    return wp;
}

#ifdef NONMATCHING
#pragma dont_inline on
void batSpotInit(void) {
	int i;
	BattleSpotEntry* entry;
#endif

#ifdef NONMATCHING
	wp->count = 5;
	wp->entries = __memAlloc(HEAP_BATTLE, sizeof(BattleSpotEntry) * wp->count);
	memset(wp->entries, 0, sizeof(BattleSpotEntry) * wp->count);
#endif
#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802f31a8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f31b4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f31c0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f31cc[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f31d8[3] = {0.0f, 0.0f, -50.0f};
__declspec(section ".rodata") const f32 vec3_802f31e4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f31f0[3] = {20.0f, 20.0f, 150.0f};
__declspec(section ".rodata") const f32 vec3_802f31fc[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f3208[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802f3214[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f64 double_to_int_802f3220 = 4503601774854144.0;
__declspec(section ".rodata") const f64 double_to_int_mask_802f3228 = 4503599627370496.0;
__declspec(section ".sdata2") const u32 dat_8041c7e8 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041c7ec = 0xFFFFFFFF;
__declspec(section ".sdata2") const f32 float_0_8041c7f0 = 0.0f;
__declspec(section ".sdata2") const f32 float_1_8041c7f4 = 1.0f;
__declspec(section ".sdata2") const f32 float_0p25_8041c7f8 = 0.25f;
__declspec(section ".sdata2") const f32 float_60_8041c7fc = 60.0f;
__declspec(section ".sdata2") const f32 float_4p75_8041c800 = 4.75f;
__declspec(section ".sdata2") const f32 float_3p75_8041c804 = 3.75f;
__declspec(section ".sdata2") const f32 float_16_8041c808 = 16.0f;
__declspec(section ".sdata2") const f32 float_6_8041c80c = 6.0f;
__declspec(section ".sdata2") const f32 float_100_8041c810 = 100.0f;
__declspec(section ".sdata2") const f32 float_1000_8041c814 = 1000.0f;
__declspec(section ".sdata2") const f32 float_neg1_8041c818 = -1.0f;
__declspec(section ".sdata2") const f32 float_32767_8041c81c = 32767.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_8041c820 = 0.017453292f;
__declspec(section ".sdata2") const f32 float_6p2832_8041c824 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_30_8041c828 = 30.0f;
__declspec(section ".sdata2") const f32 float_neg1000_8041c82c = -1000.0f;
__declspec(section ".sdata2") const f32 float_neg100_8041c830 = -100.0f;
__declspec(section ".sdata2") const f32 float_50_8041c834 = 50.0f;
__declspec(section ".sdata2") const f32 float_2_8041c838 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p34907_8041c83c = 0.34906584f;
__declspec(section ".sdata2") const f32 float_neg640_8041c840 = -640.0f;
__declspec(section ".sdata2") const f32 float_640_8041c844 = 640.0f;
__declspec(section ".sdata2") const f32 float_105_8041c848 = 105.0f;
__declspec(section ".sdata2") const f32 float_5000_8041c84c = 5000.0f;
__declspec(section ".sdata2") const f32 float_6000_8041c850 = 6000.0f;
__declspec(section ".sdata2") const f32 float_290_8041c854 = 290.0f;
__declspec(section ".sdata2") const f32 float_200_8041c858 = 200.0f;
__declspec(section ".sdata2") const f32 float_90_8041c85c = 90.0f;
__declspec(section ".sdata2") const f32 float_neg50_8041c860 = -50.0f;
__declspec(section ".sdata2") const u32 gap_09_8041C864_sdata2[1] = {0};
#endif

#ifdef NONMATCHING
	for (i = 0; i < 5; i++) {
		entry = batSpotEntry();
		entry->field_4 = (Vec){50.0f * i + -100.0f, 0.0f, -50.0f};
		entry->field_10 = (Vec){0.0f, 0.0f, 0.0f};
		entry->field_1C = (Vec){20.0f, 20.0f, 150.0f};
		*(GXColor*)&entry->field_28 = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
	}
}
#pragma dont_inline reset

#pragma dont_inline on
void batSpotMain() {
    s32 count = wp->count;

    while (count-- > 0) {}
    if (wp->skipRender > 0) {
        dispEntry(CAMERA_3D_IMAGE, -1000.0f, 0, batSpotDisp, NULL);
    }
}
#pragma dont_inline reset

void batSpotDisp(CameraId camId, void* param) {
	int i;
	BattleSpotEntry* e;

	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GXSetNumTexGens(0);
	GXSetNumTevStages(1);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
	GXSetZCompLoc(GX_TRUE);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetNumChans(1);
	for (i = 0, e = wp->entries; i < wp->count; i++, e++) {
		if ((e->flags & 1) && (e->flags & 2)) {
			GXSetCullMode(GX_CULL_BACK);
			GXSetAlphaUpdate(GX_TRUE);
			GXSetColorUpdate(GX_FALSE);
			GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
			GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
			GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
			drawCone(camId, e);
			GXSetCullMode(GX_CULL_FRONT);
			GXSetAlphaUpdate(GX_TRUE);
			GXSetColorUpdate(GX_FALSE);
			GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
			GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
			GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
			GXSetChanMatColor(GX_COLOR0A0, (GXColor){0, 0, 0, 0});
			drawCone(camId, e);
			GXSetCullMode(GX_CULL_BACK);
			GXSetAlphaUpdate(GX_FALSE);
			GXSetColorUpdate(GX_TRUE);
			GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
			GXSetBlendMode(GX_BM_BLEND, GX_BL_DSTALPHA, GX_BL_INVDSTALPHA, GX_LO_CLEAR);
			GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
			GXSetChanMatColor(GX_COLOR0A0, *(GXColor*)&e->field_28);
			drawCone(camId, e);
		}
	}
}

#pragma dont_inline on
void drawCone(CameraId camId, BattleSpotEntry* e) {
	Mtx trans, scale, m, rx, ry, rz;
	CameraEntry* cam;
	s32 i;
	f32 a, s, c;

	cam = camGetPtr(camId);
	PSMTXTrans(trans, e->field_4.x, e->field_4.y, e->field_4.z);
	PSMTXScale(scale, e->field_1C.x, e->field_1C.y, e->field_1C.z);
	PSMTXRotRad(rx, 'x', 0.017453292f * e->field_10.x);
	PSMTXRotRad(ry, 'y', 0.017453292f * e->field_10.y);
	PSMTXRotRad(rz, 'z', 0.017453292f * e->field_10.z);
	PSMTXConcat(rz, ry, ry);
	PSMTXConcat(ry, rx, m);
	PSMTXConcat(cam->view, trans, trans);
	PSMTXConcat(trans, m, m);
	PSMTXConcat(m, scale, m);
	GXLoadPosMtxImm(m, GX_PNMTX0);
	GXSetCurrentMtx(GX_PNMTX0);
	GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 32);
	GXPosition3f32(0.0f, 0.0f, 0.0f);
	GXColor4u8(0, 0, 0, ((GXColor*)&e->field_28)->a);
	for (i = 0; i < 31; i++) {
		if (i == 30) {
			a = 0.0f;
		} else {
			a = 6.2831855f * (f32)-i / 30.0f;
		}
		s = (f32)sin(a);
		c = (f32)cos(a);
		GXPosition3f32(c, s, -1.0f);
		GXColor4u8(0, 0, 0, ((GXColor*)&e->field_28)->a / 3);
	}
}
#pragma dont_inline reset

// TODO: get this to not inline into batSpotInit
#pragma dont_inline on
BattleSpotEntry* batSpotEntry(void) {
	int i;
	BattleSpotEntry* entry = wp->entries;

	for (i = 0; i < wp->count; i++, entry++) {
		if (!(entry->flags & 1)) {
			break;
		}
	}

	entry->field_4 = (Vec){0.0, 0.0, 0.0};
	entry->field_1C = (Vec){1.0, 1.0, 1.0};
	entry->field_10 = (Vec){0.0, 0.0, 0.0};
	*(GXColor*)&entry->field_28 = (GXColor){0, 0, 0, 0};
	entry->flags |= 1;

	return entry;
}
#pragma dont_inline reset

#pragma dont_inline on
static f32 randf(f32 min, f32 max) {
	f32 r = (f32)rand() / 32767.0f;
	f32 d = max - min;
	return r * d + min;
}
#pragma dont_inline reset

static void screen_capture(CameraId camId, void* param) {
	GXSetTexCopySrc(0, 0, 608, 480);
	GXSetTexCopyDst(304, 240, GX_TF_RGB565, GX_TRUE);
	GXCopyTex(screen_wp->tex, GX_FALSE);
	GXPixModeSync();
	screen_wp->captured = 1;
}

USER_FUNC(screen_evt_func) {
	dispEntry(CAMERA_2D, 1000.0f, 0, screen_capture, NULL);
	return 0;
}

USER_FUNC(tou_gamen_screen_tev_init) {
	u32 size = GXGetTexBufferSize(608, 480, GX_TF_I4, GX_FALSE, 0);

	screen_wp = _mapAlloc(sizeof(ScreenWork));
	screen_wp->tex = _mapAlloc(size);
	screen_wp->captured = 0;
	screen_wp->field_8 = screen_wp->field_C = 1.0f;
	screen_wp->field_10 = screen_wp->field_14 = 0.0f;
	screen_wp->field_18 = screen_wp->field_1C = 0.0f;
	screen_wp->field_20 = 0;
	screen_wp->field_28 = -1.0f;
	if (evtGetValue(event, GSW(0)) == 163) {
		screen_wp->field_24 = 1;
	}
	evtEntry(screen_evt, 0, 0);
	return 2;
}

typedef struct TevCbWork {
	u8 pad_0[0xC];
	s32 field_C;
	s32 field_10;
	s32 field_14;
} TevCbWork;

void tou_gamen_screen_tev(TevCbWork* p) {
	GXTexObj obj;
	Mtx m;
	Mtx m1;
	Mtx m2;
	u8* tex;
	s32 i, j, n, w, s, k, idx;
	s32 rc[2];
	u8 c;
	f32 lim;
	f32 x, y;
	f32* camf;

	if (screen_wp->captured == 0) {
		return;
	}
	if (screen_wp->field_24 != 0) {
		tex = screen_wp->tex;
		for (i = 0; i < 64; i++) {
			rc[1] = i / 4;
			rc[0] = i % 4;
			for (j = 0; j < 64; j++) {
				idx = (j / 8) * 32 + (rc[1] << 8); idx += j % 8; idx += rc[0] << 3; tex[idx] = (i & 1) ? 0xFF : 0;
			}
			n = rand() % 100 + 100;
			rc[1] = rc[1] * 256;
			k = rc[0] * 8;
			for (rc[0] = 0; rc[0] < n; rc[0]++) {
				w = rand() % 4 + 2;
				s = rand() % (65 - w);
				c = rand() % 256;
				for (j = s; j < s + w; j++) {
					idx = j / 8 * 32; idx = idx + rc[1]; idx += j % 8; idx += k; tex[idx] = c;
				}
			}
		}
		DCFlushRange(tex, 0x1000);
		GXInitTexObj(&obj, tex, 64, 64, GX_TF_I8, GX_REPEAT, GX_REPEAT, GX_FALSE);
		GXInitTexObjLOD(&obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
		GXLoadTexObj(&obj, GX_TEXMAP0);
	} else {
		GXInitTexObj(&obj, screen_wp->tex, 304, 240, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
		GXInitTexObjLOD(&obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
	}
	GXLoadTexObj(&obj, GX_TEXMAP0);
	GXInitTexObj(&obj, inta_tex, 4, 8, GX_TF_I4, GX_REPEAT, GX_REPEAT, GX_FALSE);
	GXInitTexObjLOD(&obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
	GXLoadTexObj(&obj, GX_TEXMAP1);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
	GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
	GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_CPREV, GX_CC_ZERO);
	GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
	if (screen_wp->field_24 == 0) {
		screen_wp->field_20++;
		if (screen_wp->field_20 % 200 == 0) {
			switch (rand() % 3) {
				case 0:
					screen_wp->field_14 = randf(0.0f, (1.0f - screen_wp->field_8) / screen_wp->field_8);
					screen_wp->field_1C = randf(0.0f, (1.0f - screen_wp->field_8) / screen_wp->field_8);
					break;
				case 1:
					screen_wp->field_C = randf(1.0f, 0.25f);
					break;
				case 2:
					break;
			}
		}
		screen_wp->field_8 += (screen_wp->field_C - screen_wp->field_8) / 60.0f;
		screen_wp->field_10 += (screen_wp->field_14 - screen_wp->field_10) / 60.0f;
		screen_wp->field_18 += (screen_wp->field_1C - screen_wp->field_18) / 60.0f;
		PSMTXScale(m1, screen_wp->field_8, screen_wp->field_8, 1.0f);
		lim = (1.0f - screen_wp->field_8) / screen_wp->field_8;
		y = screen_wp->field_18 > lim ? lim : screen_wp->field_18;
		if (screen_wp->field_10 > lim) {
			x = lim;
		} else {
			x = screen_wp->field_10;
		}
		PSMTXTrans(m2, x, y, 0.0f);
		PSMTXConcat(m1, m2, m);
	} else {
		PSMTXScale(m, 4.75f, 3.75f, 0.0f);
	}
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
	GXLoadTexMtxImm(m, GX_TEXMTX0, GX_MTX2x4);
	camf = (f32*)camGetPtr(CAMERA_3D);
	PSMTXScale(m, 1.0f, 16.0f + 6.0f * ((100.0f - camf[5]) / 1000.0f), 1.0f);
	GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
	GXLoadTexMtxImm(m, GX_TEXMTX1, GX_MTX2x4);
	p->field_C = 2;
	p->field_14 = 2;
	p->field_10 = 2;
}


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".sdata2") const u32 gap_09_8041C864_sdata2[1] = {0};
#pragma force_active reset
#pragma force_active reset

#endif