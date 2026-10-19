// FAKE: whole unit as G5 asm stopgap (force_active + fixbase); C under #ifdef NONMATCHING.
#include "manager/fontmgr.h"
#include "manager/dvdmgr.h"
#include "driver/camdrv.h"
#include "driver/msgdrv.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#ifndef NONMATCHING
__declspec(section ".sdata2") u32 gap_10_80422FDC_sbss2[1];
__declspec(section ".sdata2") extern const u32 dat_8041a2e8;
__declspec(section ".sdata2") extern const u32 dat_8041a2ec;
__declspec(section ".sdata2") extern const u32 dat_8041a2f0;
__declspec(section ".sdata2") extern const f32 float_1_8041a2f4;
__declspec(section ".sdata2") extern const f32 float_0p0019531_8041a2f8;
__declspec(section ".sdata2") extern const f32 float_0p00097656_8041a2fc;
__declspec(section ".sdata2") extern const f32 float_0_8041a300;
__declspec(section ".sdata2") extern const f32 float_255_8041a304;
__declspec(section ".sdata2") extern const f32 float_360_8041a308;
__declspec(section ".sdata2") extern const f32 float_0p0039062_8041a30c;
__declspec(section ".sdata2") extern const f32 float_60_8041a310;
__declspec(section ".sdata2") extern const char str_8041A314[];
__declspec(section ".sdata2") extern const char str_8041A31C[];
__declspec(section ".sdata2") extern const char str_8041A320[];
__declspec(section ".sdata2") extern const f32 float_0p5_8041a328;
__declspec(section ".sdata2") extern const char str_8041A32C[];
__declspec(section ".sdata2") extern const char str_8041A330[];
__declspec(section ".sdata2") extern const char str_8041A334[];
__declspec(section ".sdata2") extern const f32 float_28_8041a33c;
__declspec(section ".sdata2") extern const f32 float_0p015625_8041a340;
#define EXT_LIT(sym, val) (sym)

#endif
#pragma force_active on // FAKE: keep asm-only-referenced data from being dead-stripped
__declspec(section ".rodata") const char str_802C48A0[20] = "\160\141\160\145\162\155\141\162\151\157\163\145\164\137\112\120\116\000\000";
__declspec(section ".rodata") const char str_802C48B4[12] = "\160\157\160\152\157\171\102\062\062\000\000";
__declspec(section ".rodata") const f32 vec3_802c48c0[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802c48cc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c48d8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f64 double_to_int_mask_802c48e8 = 4503599627370496;
__declspec(section ".rodata") const f64 double_to_int_802c48f0 = 4503601774854144;
__declspec(section ".rodata") const char str_802C48F8[12] = "\045\163\057\146\057\045\163\056\142\146\156";
__declspec(section ".rodata") const char str_802C4904[12] = "\045\144\045\146\045\144\045\144\045\144\000";
__declspec(section ".rodata") const char str_802C4910[12] = "\045\163\045\146\045\144\045\144\045\144\000";
__declspec(section ".rodata") const u32 gap_04_802C491C_rodata[1] = { 0x00000000 };


extern int sprintf(char* str, const char* format, ...);
extern double floor(double);
extern GXTexObj* wakuTexObj;

typedef struct FontWidthEntry {
	u8 kerning; //0x0
	u8 width; //0x1
} FontWidthEntry;

typedef struct FontWidthBlock {
	u32 magic; //0x0, "WID1"
	u32 size; //0x4
	u16 firstcode; //0x8
	u16 lastcode; //0xA
	FontWidthEntry entries[]; //0xC
} FontWidthBlock;

//.sdata
#ifdef NONMATCHING
GXColor fontColTbl[3] = {
#endif
#ifndef NONMATCHING
__declspec(section ".sdata") GXColor fontColTbl[3] = {
#endif
	{0x1E, 0x14, 0x14, 0xFF},
	{0xDC, 0xDC, 0xDC, 0xFF},
	{0xB4, 0x78, 0x14, 0xFF}
};
#ifdef NONMATCHING
s32 charspace[2] = {4, 2};
#endif
#ifndef NONMATCHING
__declspec(section ".sdata") s32 charspace[2] = {4, 2};
#endif
const char* fontname[2] = {str_802C48A0, str_802C48B4};

//.sbss
#ifndef NONMATCHING
static u8 gap_08_8041879C_sbss[4];  // .sbss pad after fontScale
#endif
Vec fontScale;
GXColor fontColor;
u8 fontAlpha;
BOOL fontEdge;
BinaryFontInfo* pfi; //pointer to font info
BinaryFontGlyph* blockGlyph;
GXTexObj fgTexObj;
BinaryFontHeader* pfh; //pointer to font header

//local prototypes
void JUTFont_DrawStart(GXColor color);
void _JUTFont_DrawPos(u16 code, s16 x, s16 y);
u16 JUTFont_CodeToGlyph(u32 code);
void JUTFontSetup(u16 font);
GXColor HSV2RGB(GXColor hsv);
void FontDrawColorIDX(s32 idx);
void FontDrawStart_alpha(u8 alpha);

static inline FontWidthEntry* fontGetWidth(u16 code) {
	FontWidthBlock* block = (FontWidthBlock*)&pfh[1];
	u32 i;

	for (i = 0; i < pfh->blockcount; i++) {
		switch (block->magic) {
			case 'WID1':
				if (code >= block->firstcode && code <= block->lastcode) {
					return &block->entries[code - block->firstcode];
				}
				break;
		}
		block = (FontWidthBlock*)((u32)block + block->size);
	}
	return NULL;
}

static inline void fontDrawCodeEdge(u16 code) {
	if (fontEdge) {
		GXColor save = fontColor;
		FontDrawColorIDX(0);
		_JUTFont_DrawPos(code, -2, 0);
		_JUTFont_DrawPos(code, 2, 0);
		_JUTFont_DrawPos(code, 0, -2);
		_JUTFont_DrawPos(code, 0, 2);
		FontDrawColor(save);
	}
	_JUTFont_DrawPos(code, 0, 0);
}

void fontmgrInit(void) {
	; //stubbed in retail
}

void fontmgrTexSetup(void) {
	JUTFontSetup(0);
}

#ifndef NONMATCHING
void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXLoadPosMtxImm(const f32 mtx[3][4], u32 id);
void GXSetTevColor(GXTevRegID id, GXColor color);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void PSMTXTransApply(const Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
void iconDispGxAlpha(Vec* position, s16 flags, u16 iconId, u8 alpha, f32 scale);
extern void iconGetWidthHight(u16* width, u16* height, u16 id);
extern char* msgGetCommand(char* msg, char* cmd, char* arg);
extern s32 msgIconStr2ID(const char* str);
extern int sscanf(const char* s, const char* format, ...);
extern int strcmp(const char* a, const char* b);
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void FontDrawStart(void) {
#ifdef NONMATCHING
	FontDrawStart_alpha(0xFF);
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x3CA08081
		lis r3, vec3_802c48c0@ha
		opword 0x90010014
		addi r4, r3, vec3_802c48c0@l
		opword 0x39058081
		opword 0x38000000
		lwz r10, fontColTbl(r13)
		opword 0x392000FF
		opword 0x80A40004
		opword 0x3861000C
		opword 0x91410008
		opword 0x80C40000
		opword 0x88E1000B
		opword 0x80840008
		opword 0x1CE700FF
		stw r5, fontScale+0x4(r13)
		stw r4, fontScale+0x8(r13)
		opword 0x7D083896
		stw r0, fontEdge(r13)
		stw r10, fontColor(r13)
		opword 0x7CA83A14
		stb r9, fontAlpha(r13)
		opword 0x7CA53E70
		opword 0x54A40FFE
		stw r6, fontScale(r13)
		opword 0x7C852214
		opword 0x9881000B
		opword 0x80010008
		opword 0x9001000C
		bl JUTFont_DrawStart
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void FontDrawStart_alpha(u8 alpha) {
#ifdef NONMATCHING
	GXColor start;

	fontColor = start = fontColTbl[0];
	fontAlpha = alpha;
	start.a = (start.a * alpha) / 255;
	fontScale = (Vec){1.0f, 1.0f, 1.0f};
	fontEdge = FALSE;
	JUTFont_DrawStart(start);
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x3CA08081
		opword 0x5467063E
		opword 0x90010014
		lis r4, vec3_802c48c0@ha
		opword 0x38000000
		opword 0x39258081
		lwz r10, fontColTbl(r13)
		lwzu r6, vec3_802c48c0@l(r4)
		opword 0x9141000C
		opword 0x80A40004
		opword 0x8901000F
		opword 0x80840008
		opword 0x7CE839D6
		stb r3, fontAlpha(r13)
		opword 0x38610008
		stw r5, fontScale+0x4(r13)
		stw r4, fontScale+0x8(r13)
		opword 0x7D093896
		stw r0, fontEdge(r13)
		stw r10, fontColor(r13)
		opword 0x7CA83A14
		stw r6, fontScale(r13)
		opword 0x7CA43E70
		opword 0x54850FFE
		opword 0x7C042A14
		opword 0x9801000F
		opword 0x8001000C
		opword 0x90010008
		bl JUTFont_DrawStart
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void FontDrawEdge(void) {
	fontEdge = TRUE;
}

void FontDrawEdgeOff(void) {
	fontEdge = FALSE;
}

void FontDrawRainbowColor(void) {
	GXSetNumTevStages(2);
	GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
	GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
}

void FontDrawRainbowColorOff(void) {
	GXSetNumTevStages(1);
}

void FontDrawNoise(void) {
	Mtx mtx;

	GXSetNumTexGens(2);
	GXSetNumTevStages(2);
	GXSetTevKAlphaSel(GX_TEVSTAGE1, GX_TEV_KASEL_1);
	GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP2, GX_COLOR_NULL);
	GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
	GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
	GXLoadTexObj(&wakuTexObj[50], GX_TEXMAP2);
#ifdef NONMATCHING
	PSMTXScale(mtx, 0.015625f, 0.015625f, 1.0f);
#endif
#ifndef NONMATCHING
	PSMTXScale(mtx, EXT_LIT(float_0p015625_8041a340, 0.015625f), EXT_LIT(float_0p015625_8041a340, 0.015625f), EXT_LIT(float_1_8041a2f4, 1.0f));
#endif
	GXLoadTexMtxImm(mtx, GX_TEXMTX1, GX_MTX2x4);
	GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
}

void FontDrawNoiseOff(void) {
	GXSetNumTexGens(1);
	GXSetNumTevStages(1);
}

void FontDrawColorIDX(s32 idx) {
	FontDrawColor(fontColTbl[idx]);
}

void FontDrawColor(GXColor color) {
	fontColor = color;
	color.a = (color.a * fontAlpha) / 255;
	GXSetTevColor(GX_TEVREG0, color);
}

void FontDrawColor_(void) {
	FontDrawColor(fontColor);
}

GXColor FontGetDrawColor(void) {
	return fontColor;
}

void FontDrawScale(f32 scale) {
	fontScale.x = scale;
	fontScale.y = scale;
	fontScale.z = scale;
}

void FontDrawScaleVec(Vec scale) {
	fontScale = scale;
}

void FontDrawCode(f32 x, f32 y, u16 code) {
	Mtx mtx;

	PSMTXScale(mtx, fontScale.x, fontScale.y, fontScale.z);
#ifdef NONMATCHING
	PSMTXTransApply(mtx, mtx, x, y, 0.0f);
#endif
#ifndef NONMATCHING
	PSMTXTransApply(mtx, mtx, x, y, EXT_LIT(float_0_8041a300, 0.0f));
#endif
	PSMTXConcat(camGetCurPtr()->view, mtx, mtx);
	GXLoadPosMtxImm(mtx, 0);
	GXSetCurrentMtx(0);
	fontDrawCodeEdge(code);
}

void FontDrawCodeMtx(Mtx mtx, u16 code) {
	PSMTXConcat(camGetCurPtr()->view, mtx, mtx);
	GXLoadPosMtxImm(mtx, 0);
	GXSetCurrentMtx(0);
	fontDrawCodeEdge(code);
}

#ifdef NONMATCHING
static inline void FontDrawStringVec(Vec pos, const s8* str) {
	CameraEntry* camera;
	Mtx trans, scale;
	u8 width;
	const s8* msg;
	u16 code;
	f32 x;
#endif

#ifdef NONMATCHING
	msg = str;
	camera = camGetCurPtr();
	x = pos.x;
	PSMTXScale(scale, fontScale.x, fontScale.y, fontScale.z);
	while (*msg) {
		if (_ismbblead(*msg)) {
			code = JUTFont_CodeToGlyph(*(u16*)msg);
			msg += 2;
		}
		else {
			code = JUTFont_CodeToGlyph(*msg++);
		}
		width = fontGetWidth(code)->width;
		PSMTXTransApply(scale, trans, x, pos.y, pos.z);
		PSMTXConcat(camera->view, trans, trans);
		GXLoadPosMtxImm(trans, 0);
		fontDrawCodeEdge(code);
		x += fontScale.x * (width + charspace[gp->language]);
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void FontDrawString(f32 x, f32 y, const char* msg) {
	char _af_pad[152];
	asm volatile {
		lis r4, vec3_802c48cc@ha
		opword 0x7C7C1B78
		addi r5, r4, vec3_802c48cc@l
		opword 0x80850000
		opword 0x80050004
		stw r4, _af_pad+24(r1)
		opword 0x80850008
		opword 0x90010024
		opword 0xD0210020
		opword 0xD0410024
		opword 0x80610020
		opword 0x80010024
		opword 0x90810028
		opword 0x9061002C
		opword 0x90010030
		opword 0x90810034
		bl camGetCurPtr
		la r4, fontScale(r13)
		opword 0x7C7E1B78
		opword 0xC3C1002C
		opword 0x38610068
		lfs f1, fontScale(r13)
		opword 0xC0440004
		opword 0xC0640008
		bl PSMTXScale
		lis r3, double_to_int_802c48f0@ha
		opword 0x3C805749
		opword 0xC3A10034
		opword 0x3BE44431
		lfs f28, 0x30(r1)
		lis r26, 0x4330
		lfd f31, double_to_int_802c48f0@l(r3)
		opword 0x48000210
		opword 0x7C630774
		bl _ismbblead
		opword 0x2C030000
		opword 0x41820018
		opword 0xA07C0000
		bl JUTFont_CodeToGlyph
		opword 0x7C7D1B78
		opword 0x3B9C0002
		opword 0x48000018
		opword 0x881C0000
		opword 0x3B9C0001
		opword 0x7C030774
		bl JUTFont_CodeToGlyph
		opword 0x7C7D1B78
		lwz r4, pfh(r13)
		opword 0x57A3043E
		opword 0x8004000C
		opword 0x38840020
		opword 0x7C0903A6
		opword 0x28000000
		opword 0x4081004C
		opword 0x80040000
		opword 0x7C00F800
		opword 0x41820008
		opword 0x48000030
		opword 0xA0A40008
		opword 0x7C032840
		opword 0x41800024
		opword 0xA004000A
		opword 0x7C030040
		opword 0x41810018
		opword 0x7C051850
		opword 0x5403083C
		opword 0x3863000C
		opword 0x7C641A14
		opword 0x48000014
		opword 0x80040004
		opword 0x7C840214
		opword 0x4200FFBC
		opword 0x38600000
		opword 0xFC20F090
		opword 0x8B630001
		opword 0xFC40E090
		opword 0x38610068
		opword 0xFC60E890
		opword 0x38810038
		bl PSMTXTransApply
		opword 0x38810038
		opword 0x387E011C
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38610038
		opword 0x38800000
		bl GXLoadPosMtxImm
		lwz r0, fontEdge(r13)
		opword 0x2C000000
		opword 0x418200E8
		lwz r7, fontColTbl(r13)
		opword 0x3C608081
		lwz r8, fontColor(r13)
		opword 0x38C38081
		opword 0x90E10014
		opword 0x3881000C
		lbz r0, fontAlpha(r13)
		opword 0x38600001
		opword 0x88A10017
		opword 0x91010018
		opword 0x7C0501D6
		opword 0x90E10008
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010017
		opword 0x80010014
		opword 0x9001000C
		bl GXSetTevColor
		opword 0x7FA3EB78
		opword 0x3880FFFE
		opword 0x38A00000
		bl _JUTFont_DrawPos
		opword 0x7FA3EB78
		opword 0x38800002
		opword 0x38A00000
		bl _JUTFont_DrawPos
		opword 0x7FA3EB78
		opword 0x38800000
		opword 0x38A0FFFE
		bl _JUTFont_DrawPos
		opword 0x7FA3EB78
		opword 0x38800000
		opword 0x38A00002
		bl _JUTFont_DrawPos
		opword 0x80E10018
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E1001C
		opword 0x38810010
		opword 0x38600001
		opword 0x88A1001F
		stw r7, fontColor(r13)
		opword 0x7C0501D6
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801001F
		opword 0x8001001C
		opword 0x90010010
		bl GXSetTevColor
		opword 0x7FA3EB78
		opword 0x38800000
		opword 0x38A00000
		bl _JUTFont_DrawPos
		lwz r4, gp(r13)
		la r3, charspace(r13)
		opword 0x93410098
		opword 0x8004016C
		lfs f1, fontScale(r13)
		opword 0x5400103A
		opword 0x7C03002E
		opword 0x7C1B0214
		opword 0x6C008000
		opword 0x9001009C
		opword 0xC8010098
		opword 0xEC00F828
		opword 0xEFC1F03A
		opword 0x887C0000
		opword 0x7C600775
		opword 0x4082FDEC
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
void FontDrawString(f32 x, f32 y, const char* msg) {
	FontDrawStringVec((Vec){x, y, 0.0f}, (const s8*)msg);
}
#endif

#ifdef NONMATCHING
static inline void fontDrawStringVecPitch(Vec pos, f32 pitch, const s8* str) {
	CameraEntry* camera;
	Mtx trans, scale;
	u8 width;
	const s8* msg;
	u16 code;
	f32 x;

	msg = str;
	camera = camGetCurPtr();
	x = pos.x;
	PSMTXScale(scale, fontScale.x, fontScale.y, fontScale.z);
	while (*msg) {
		if (_ismbblead(*msg)) {
			code = JUTFont_CodeToGlyph(*(u16*)msg);
			msg += 2;
		}
		else {
			code = JUTFont_CodeToGlyph(*msg++);
		}
		width = fontGetWidth(code)->width;
		PSMTXTransApply(scale, trans, pitch < 0.0f ? x : x + fontScale.x * ((pitch - width) * 0.5f), pos.y, pos.z);
		PSMTXConcat(camera->view, trans, trans);
		GXLoadPosMtxImm(trans, 0);
		fontDrawCodeEdge(code);
		if (pitch < 0.0f) {
			x += fontScale.x * (width + charspace[gp->language]);
		}
		else {
			x += pitch * fontScale.x;
		}
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void FontDrawStringPitch(f32 x, f32 y, f32 pitch, const char* msg) {
	char _af_pad[156];
	asm volatile {
		lis r4, vec3_802c48d8@ha
		opword 0x7C7C1B78
		addi r5, r4, vec3_802c48d8@l
		fmr f27, f3
		opword 0x80850000
		opword 0x80050004
		stw r4, _af_pad+24(r1)
		opword 0x80850008
		opword 0x90010024
		opword 0xD0210020
		opword 0xD0410024
		opword 0x80610020
		opword 0x80010024
		opword 0x90810028
		opword 0x9061002C
		opword 0x90010030
		opword 0x90810034
		bl camGetCurPtr
		la r4, fontScale(r13)
		opword 0x7C7E1B78
		opword 0xC3C1002C
		opword 0x38610068
		lfs f1, fontScale(r13)
		opword 0xC0440004
		opword 0xC0640008
		bl PSMTXScale
		opword 0x3C605749
		opword 0xC3A10034
		opword 0xC3810030
		opword 0x3BE34431
		lfs f31, float_0_8041a300(r2)
		opword 0x4800026C
		opword 0x7C630774
		bl _ismbblead
		opword 0x2C030000
		opword 0x41820018
		opword 0xA07C0000
		bl JUTFont_CodeToGlyph
		opword 0x7C7D1B78
		opword 0x3B9C0002
		opword 0x48000018
		opword 0x881C0000
		opword 0x3B9C0001
		opword 0x7C030774
		bl JUTFont_CodeToGlyph
		opword 0x7C7D1B78
		lwz r4, pfh(r13)
		opword 0x57A3043E
		opword 0x8004000C
		opword 0x38840020
		opword 0x7C0903A6
		opword 0x28000000
		opword 0x4081004C
		opword 0x80040000
		opword 0x7C00F800
		opword 0x41820008
		opword 0x48000030
		opword 0xA0A40008
		opword 0x7C032840
		opword 0x41800024
		opword 0xA004000A
		opword 0x7C030040
		opword 0x41810018
		opword 0x7C051850
		opword 0x5403083C
		opword 0x3863000C
		opword 0x7C641A14
		opword 0x48000014
		opword 0x80040004
		opword 0x7C840214
		opword 0x4200FFBC
		opword 0x38600000
		opword 0xFC1BF840
		lbz r27, 0x1(r3)
		opword 0x38610068
		opword 0x38810038
		opword 0x4080000C
		opword 0xFC20F090
		opword 0x48000034
		opword 0x3C004330
		lis r5, double_to_int_mask_802c48e8@ha
		opword 0x9361009C
		lfd f1, double_to_int_mask_802c48e8@l(r5)
		opword 0x90010098
		lfs f2, float_0p5_8041a328(r2)
		opword 0xC8010098
		lfs f3, fontScale(r13)
		opword 0xEC000828
		opword 0xEC1B0028
		opword 0xEC020032
		opword 0xEC23F03A
		opword 0xFC40E090
		opword 0xFC60E890
		bl PSMTXTransApply
		opword 0x38810038
		opword 0x387E011C
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38610038
		opword 0x38800000
		bl GXLoadPosMtxImm
		lwz r0, fontEdge(r13)
		opword 0x2C000000
		opword 0x418200E8
		lwz r7, fontColTbl(r13)
		opword 0x3C608081
		lwz r8, fontColor(r13)
		opword 0x38C38081
		opword 0x90E10014
		opword 0x3881000C
		lbz r0, fontAlpha(r13)
		opword 0x38600001
		opword 0x88A10017
		opword 0x91010018
		opword 0x7C0501D6
		opword 0x90E10008
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010017
		opword 0x80010014
		opword 0x9001000C
		bl GXSetTevColor
		opword 0x7FA3EB78
		opword 0x3880FFFE
		opword 0x38A00000
		bl _JUTFont_DrawPos
		opword 0x7FA3EB78
		opword 0x38800002
		opword 0x38A00000
		bl _JUTFont_DrawPos
		opword 0x7FA3EB78
		opword 0x38800000
		opword 0x38A0FFFE
		bl _JUTFont_DrawPos
		opword 0x7FA3EB78
		opword 0x38800000
		opword 0x38A00002
		bl _JUTFont_DrawPos
		opword 0x80E10018
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E1001C
		opword 0x38810010
		opword 0x38600001
		opword 0x88A1001F
		stw r7, fontColor(r13)
		opword 0x7C0501D6
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801001F
		opword 0x8001001C
		opword 0x90010010
		bl GXSetTevColor
		opword 0x7FA3EB78
		opword 0x38800000
		opword 0x38A00000
		bl _JUTFont_DrawPos
		opword 0xFC1BF840
		opword 0x40800048
		lwz r5, gp(r13)
		opword 0x3C004330
		lis r3, double_to_int_802c48f0@ha
		la r4, charspace(r13)
		opword 0x80A5016C
		opword 0x90010098
		opword 0x54A0103A
		lfd f1, double_to_int_802c48f0@l(r3)
		opword 0x7C04002E
		lfs f2, fontScale(r13)
		opword 0x7C1B0214
		opword 0x6C008000
		opword 0x9001009C
		opword 0xC8010098
		opword 0xEC000828
		opword 0xEFC2F03A
		opword 0x4800000C
		lfs f0, fontScale(r13)
		opword 0xEFDBF03A
		opword 0x887C0000
		opword 0x7C600775
		opword 0x4082FD90
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
void FontDrawStringPitch(f32 x, f32 y, f32 pitch, const char* msg) {
	fontDrawStringVecPitch((Vec){x, y, 0.0f}, pitch, (const s8*)msg);
}

#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void FontDrawStringVecPitch(Vec pos, f32 pitch, const s8* msg) {
#ifdef NONMATCHING
	CameraEntry* camera;
	Mtx trans, scale;
	u8 width;
	u16 code;
	f32 x;

	camera = camGetCurPtr();
	x = pos.x;
	PSMTXScale(scale, fontScale.x, fontScale.y, fontScale.z);
	while (*msg) {
		if (_ismbblead(*msg)) {
			code = JUTFont_CodeToGlyph(*(u16*)msg);
			msg += 2;
		}
		else {
			code = JUTFont_CodeToGlyph(*msg++);
		}
		width = fontGetWidth(code)->width;
		PSMTXTransApply(scale, trans, pitch < 0.0f ? x : x + fontScale.x * ((pitch - width) * 0.5f), pos.y, pos.z);
		PSMTXConcat(camera->view, trans, trans);
		GXLoadPosMtxImm(trans, 0);
		fontDrawCodeEdge(code);
		if (pitch < 0.0f) {
			x += fontScale.x * (width + charspace[gp->language]);
		}
		else {
			x += pitch * fontScale.x;
		}
#endif
#ifndef NONMATCHING
	char _af_pad[120];
	asm volatile {
		fmr f29, f1
		mr r26, r3
		opword 0x7C9B2378
		bl camGetCurPtr
		la r4, fontScale(r13)
		opword 0x7C7E1B78
		opword 0xC3DA0000
		la r3, _af_pad+24
		lfs f1, fontScale(r13)
		opword 0xC0440004
		opword 0xC0640008
		bl PSMTXScale
		opword 0x3C605749
		lfs f31, float_0_8041a300(r2)
		opword 0x3BE34431
		opword 0x4800026C
		opword 0x7C630774
		bl _ismbblead
		opword 0x2C030000
		opword 0x41820018
		opword 0xA07B0000
		bl JUTFont_CodeToGlyph
		opword 0x7C7C1B78
		opword 0x3B7B0002
		opword 0x48000018
		opword 0x881B0000
		opword 0x3B7B0001
		opword 0x7C030774
		bl JUTFont_CodeToGlyph
		opword 0x7C7C1B78
		lwz r4, pfh(r13)
		opword 0x5783043E
		opword 0x8004000C
		opword 0x38840020
		opword 0x7C0903A6
		opword 0x28000000
		opword 0x4081004C
		opword 0x80040000
		opword 0x7C00F800
		opword 0x41820008
		opword 0x48000030
		opword 0xA0A40008
		opword 0x7C032840
		opword 0x41800024
		opword 0xA004000A
		opword 0x7C030040
		opword 0x41810018
		opword 0x7C051850
		opword 0x5403083C
		opword 0x3863000C
		opword 0x7C641A14
		opword 0x48000014
		opword 0x80040004
		opword 0x7C840214
		opword 0x4200FFBC
		opword 0x38600000
		opword 0xFC1DF840
		opword 0x8BA30001
		opword 0x38610020
		opword 0x38810050
		opword 0x4080000C
		opword 0xFC20F090
		opword 0x48000034
		opword 0x3C004330
		lis r5, double_to_int_mask_802c48e8@ha
		opword 0x93A10084
		lfd f1, double_to_int_mask_802c48e8@l(r5)
		opword 0x90010080
		lfs f2, float_0p5_8041a328(r2)
		opword 0xC8010080
		lfs f3, fontScale(r13)
		opword 0xEC000828
		opword 0xEC1D0028
		opword 0xEC020032
		opword 0xEC23F03A
		opword 0xC05A0004
		opword 0xC07A0008
		bl PSMTXTransApply
		opword 0x38810050
		opword 0x387E011C
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38610050
		opword 0x38800000
		bl GXLoadPosMtxImm
		lwz r0, fontEdge(r13)
		opword 0x2C000000
		opword 0x418200E8
		lwz r7, fontColTbl(r13)
		opword 0x3C608081
		lwz r8, fontColor(r13)
		opword 0x38C38081
		opword 0x90E10014
		opword 0x3881000C
		lbz r0, fontAlpha(r13)
		opword 0x38600001
		opword 0x88A10017
		opword 0x91010018
		opword 0x7C0501D6
		opword 0x90E10008
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010017
		opword 0x80010014
		opword 0x9001000C
		bl GXSetTevColor
		opword 0x7F83E378
		opword 0x3880FFFE
		opword 0x38A00000
		bl _JUTFont_DrawPos
		opword 0x7F83E378
		opword 0x38800002
		opword 0x38A00000
		bl _JUTFont_DrawPos
		opword 0x7F83E378
		opword 0x38800000
		opword 0x38A0FFFE
		bl _JUTFont_DrawPos
		opword 0x7F83E378
		opword 0x38800000
		opword 0x38A00002
		bl _JUTFont_DrawPos
		opword 0x80E10018
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E1001C
		opword 0x38810010
		opword 0x38600001
		opword 0x88A1001F
		stw r7, fontColor(r13)
		opword 0x7C0501D6
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801001F
		opword 0x8001001C
		opword 0x90010010
		bl GXSetTevColor
		opword 0x7F83E378
		opword 0x38800000
		opword 0x38A00000
		bl _JUTFont_DrawPos
		opword 0xFC1DF840
		opword 0x40800048
		lwz r5, gp(r13)
		opword 0x3C004330
		lis r3, double_to_int_802c48f0@ha
		la r4, charspace(r13)
		opword 0x80A5016C
		opword 0x90010080
		opword 0x54A0103A
		lfd f1, double_to_int_802c48f0@l(r3)
		opword 0x7C04002E
		lfs f2, fontScale(r13)
		opword 0x7C1D0214
		opword 0x6C008000
		opword 0x90010084
		opword 0xC8010080
		opword 0xEC000828
		opword 0xEFC2F03A
		opword 0x4800000C
		lfs f0, fontScale(r13)
		opword 0xEFDDF03A
		opword 0x887B0000
		opword 0x7C600775
		opword 0x4082FD90
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif
extern char* msgGetCommand(char* msg, char* cmd, char* arg);
#ifdef NONMATCHING
static inline void fontDrawPairXI(u16 code, s16 x, s16 y) {
	s16 iy = y;
	s16 ix = x;
	_JUTFont_DrawPos(code, ix - 2, (s16)iy);
	_JUTFont_DrawPos(code, ix + 2, (s16)iy);
}
#endif

#ifdef NONMATCHING
static inline void fontDrawPairYI(u16 code, s16 x, s16 y) {
	s16 iy = y;
	s16 ix = x;
	_JUTFont_DrawPos(code, ix, iy - 2);
	_JUTFont_DrawPos(code, ix, iy + 2);
}
#endif

#ifdef NONMATCHING
static inline void fontDrawPairX(u16 code, f32 x, f32 y) {
	s16 ix = x;
	s16 iy = y;
	_JUTFont_DrawPos(code, ix - 2, (s16)iy);
	_JUTFont_DrawPos(code, ix + 2, (s16)iy);
}
#endif

#ifdef NONMATCHING
static inline void fontDrawPairY(u16 code, f32 x, f32 y) {
	s16 ix = x;
	s16 iy = y;
	_JUTFont_DrawPos(code, (s16)ix, iy - 2);
	_JUTFont_DrawPos(code, (s16)ix, iy + 2);
}
#endif

#ifdef NONMATCHING
static inline void fontDrawCodeEdgeXY(u16 code, f32 x, f32 y) {
	if (fontEdge) {
		GXColor save = fontColor;
		FontDrawColorIDX(0);
		fontDrawPairX(code, x, y);
		fontDrawPairY(code, x, y);
		FontDrawColor(save);
	}
	_JUTFont_DrawPos(code, x, y);
}
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void FontDrawStringMtx(Mtx mtx, const char* msg) {
#ifdef NONMATCHING
	CameraEntry* camera;
	Mtx m;
	s8 tag[0x80];
	s8 value[0x80];
	u16 code;
	f32 x, y;

	camera = camGetCurPtr();
	x = 0.0f;
	y = x;
	PSMTXConcat(camera->view, mtx, m);
	GXLoadPosMtxImm(m, 0);
	while (*(const s8*)msg) {
		code = 0xFFFF;
		if (_ismbblead(*(const s8*)msg)) {
			code = JUTFont_CodeToGlyph(*(u16*)msg);
			msg += 2;
		}
		else {
			switch (*(const s8*)msg) {
				case '\n':
					msg++;
					x = 0.0f;
					y -= 28.0f;
					break;
				case '<':
					msg = msgGetCommand((char*)msg + 1, (char*)tag, (char*)value);
					if (tag[0] == 'R' || (tag[0] == '/' && tag[0] == (u32)'/r')) {
						break;
					}
					if (*(const s8*)msg == '\n') {
						msg++;
					}
					break;
				default:
					code = JUTFont_CodeToGlyph(*((const s8*)msg)++);
					break;
			}
		}
		if (code != 0xFFFF) {
			fontDrawCodeEdgeXY(code, x, y);
			x += fontGetWidth(code)->width + charspace[gp->language];
		}
#endif
#ifndef NONMATCHING
	char _af_pad[364];
	asm volatile {
		opword 0x7C7B1B78
		opword 0x7C9D2378
		bl camGetCurPtr
		lfs f31, float_0_8041a300(r2)
		opword 0x7F64DB78
		la r5, _af_pad+24
		opword 0x3863011C
		opword 0xFFC0F890
		bl PSMTXConcat
		opword 0x38610020
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x3FE00001
		opword 0x480002D8
		opword 0x3BDFFFFF
		opword 0x7C630774
		bl _ismbblead
		opword 0x2C030000
		opword 0x41820018
		opword 0xA07D0000
		bl JUTFont_CodeToGlyph
		opword 0x7C7E1B78
		opword 0x3BBD0002
		opword 0x48000094
		opword 0x881D0000
		opword 0x7C000774
		opword 0x2C00003C
		opword 0x41820028
		opword 0x4080006C
		opword 0x2C00000A
		opword 0x41820008
		opword 0x48000060
		lfs f0, float_28_8041a33c(r2)
		opword 0x3BBD0001
		lfs f31, float_0_8041a300(r2)
		fsubs f30, f30, f0
		opword 0x48000060
		opword 0x387D0001
		opword 0x388100D0
		opword 0x38A10050
		bl msgGetCommand
		opword 0x880100D0
		opword 0x7C7D1B78
		opword 0x7C000774
		opword 0x2C000052
		opword 0x4182003C
		opword 0x2C00002F
		opword 0x4082000C
		opword 0x28002F72
		opword 0x4182002C
		opword 0x881D0000
		opword 0x2C00000A
		opword 0x40820020
		opword 0x3BBD0001
		opword 0x48000018
		opword 0x881D0000
		opword 0x3BBD0001
		opword 0x7C030774
		bl JUTFont_CodeToGlyph
		opword 0x7C7E1B78
		opword 0x57C0043E
		opword 0x2800FFFF
		opword 0x41820214
		lwz r0, fontEdge(r13)
		opword 0x2C000000
		opword 0x41820138
		lwz r7, fontColTbl(r13)
		opword 0x3C608081
		lwz r8, fontColor(r13)
		opword 0x38C38081
		opword 0x90E10014
		opword 0x3881000C
		lbz r0, fontAlpha(r13)
		opword 0x38600001
		opword 0x88A10017
		opword 0x91010018
		opword 0x7C0501D6
		opword 0x90E10008
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010017
		opword 0x80010014
		opword 0x9001000C
		bl GXSetTevColor
		opword 0xFC20F81E
		opword 0x7FC3F378
		opword 0xFC00F01E
		opword 0xD8210150
		opword 0xD8010158
		opword 0x80810154
		opword 0x8001015C
		extsh r27, r4
		opword 0x389BFFFE
		opword 0x7C1C0734
		opword 0x7F85E378
		opword 0x7C840734
		bl _JUTFont_DrawPos
		opword 0x381B0002
		opword 0x7FC3F378
		opword 0x7F85E378
		opword 0x7C040734
		bl _JUTFont_DrawPos
		opword 0xFC00F01E
		opword 0x7FC3F378
		opword 0xFC20F81E
		opword 0xD8010168
		opword 0xD8210160
		opword 0x8001016C
		opword 0x80810164
		opword 0x7C1B0734
		opword 0x7C9C0734
		opword 0x381BFFFE
		opword 0x7F84E378
		opword 0x7C050734
		bl _JUTFont_DrawPos
		opword 0x381B0002
		opword 0x7FC3F378
		opword 0x7F84E378
		opword 0x7C050734
		bl _JUTFont_DrawPos
		opword 0x80E10018
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E1001C
		opword 0x38810010
		opword 0x38600001
		opword 0x88A1001F
		stw r7, fontColor(r13)
		opword 0x7C0501D6
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801001F
		opword 0x8001001C
		opword 0x90010010
		bl GXSetTevColor
		opword 0xFC20F81E
		opword 0x7FC3F378
		opword 0xFC00F01E
		opword 0xD8210168
		opword 0xD8010160
		opword 0x8081016C
		opword 0x80A10164
		bl _JUTFont_DrawPos
		lwz r5, pfh(r13)
		opword 0x3C605749
		opword 0x38834431
		opword 0x57C3043E
		opword 0x8005000C
		opword 0x38A50020
		opword 0x7C0903A6
		opword 0x28000000
		opword 0x4081004C
		opword 0x80050000
		opword 0x7C002000
		opword 0x41820008
		opword 0x48000030
		opword 0xA0C50008
		opword 0x7C033040
		opword 0x41800024
		opword 0xA005000A
		opword 0x7C030040
		opword 0x41810018
		opword 0x7C061850
		opword 0x5403083C
		opword 0x38E3000C
		opword 0x7CE53A14
		opword 0x48000014
		opword 0x80050004
		opword 0x7CA50214
		opword 0x4200FFBC
		opword 0x38E00000
		lwz r4, gp(r13)
		opword 0x3C004330
		lis r3, double_to_int_802c48f0@ha
		la r5, charspace(r13)
		opword 0x80C4016C
		opword 0x88870001
		opword 0x54C6103A
		opword 0x90010168
		opword 0x7C05302E
		lfd f1, double_to_int_802c48f0@l(r3)
		opword 0x7C002214
		opword 0x6C008000
		opword 0x9001016C
		opword 0xC8010168
		opword 0xEC000828
		opword 0xEFFF002A
		opword 0x887D0000
		opword 0x7C600775
		opword 0x4082FD24
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif


#ifdef NONMATCHING
static inline void fontDrawCodeEdgeX(u16 code, f32 x) {
	if (fontEdge) {
		GXColor save = fontColor;
		FontDrawColorIDX(0);
		_JUTFont_DrawPos(code, (s16)x - 2, 0);
		_JUTFont_DrawPos(code, (s16)x + 2, 0);
		_JUTFont_DrawPos(code, x, -2);
		_JUTFont_DrawPos(code, x, 2);
		FontDrawColor(save);
	}
	_JUTFont_DrawPos(code, x, 0);
}
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void FontDrawStringCenterMtx(Mtx mtx, const s8* msg) {
#ifdef NONMATCHING
	f32 x;
	u16 code;
	CameraEntry* camera;
	Mtx m;

	camera = camGetCurPtr();
	x = -(f32)FontGetMessageWidthLine((const char*)msg, NULL) * 0.5f;
	PSMTXConcat(camera->view, mtx, m);
	GXLoadPosMtxImm(m, 0);
	while (*msg) {
		if (_ismbblead(*msg)) {
			code = JUTFont_CodeToGlyph(*(u16*)msg);
			msg += 2;
		}
		else {
			code = JUTFont_CodeToGlyph(*msg++);
		}
		fontDrawCodeEdgeXY(code, x, 0.0f);
		x += fontGetWidth(code)->width + charspace[gp->language];
#endif
#ifndef NONMATCHING
	char _af_pad[92];
	asm volatile {
		opword 0x7C7B1B78
		opword 0x7C9D2378
		bl camGetCurPtr
		opword 0x7C7C1B78
		opword 0x7FA3EB78
		opword 0x38800000
		bl FontGetMessageWidthLine
		opword 0x5464043E
		opword 0x3C004330
		stw r4, _af_pad+76(r1)
		lis r3, double_to_int_mask_802c48e8@ha
		lfd f2, double_to_int_mask_802c48e8@l(r3)
		opword 0x7F64DB78
		opword 0x90010050
		opword 0x387C011C
		lfs f0, float_0p5_8041a328(r2)
		opword 0x38A10020
		opword 0xC8210050
		opword 0xEC211028
		opword 0xFC200850
		fmuls f30, f0, f1
		bl PSMTXConcat
		opword 0x38610020
		opword 0x38800000
		bl GXLoadPosMtxImm
		lis r3, double_to_int_802c48f0@ha
		opword 0x3C805749
		lfd f31, double_to_int_802c48f0@l(r3)
		opword 0x3F804330
		opword 0x3BE44431
		opword 0x48000208
		opword 0x7C630774
		bl _ismbblead
		opword 0x2C030000
		opword 0x41820018
		opword 0xA07D0000
		bl JUTFont_CodeToGlyph
		opword 0x7C7E1B78
		opword 0x3BBD0002
		opword 0x48000018
		opword 0x881D0000
		opword 0x3BBD0001
		opword 0x7C030774
		bl JUTFont_CodeToGlyph
		opword 0x7C7E1B78
		lwz r0, fontEdge(r13)
		opword 0x2C000000
		opword 0x41820110
		lwz r7, fontColTbl(r13)
		opword 0x3C608081
		lwz r8, fontColor(r13)
		opword 0x38C38081
		opword 0x90E10014
		opword 0x3881000C
		lbz r0, fontAlpha(r13)
		opword 0x38600001
		opword 0x88A10017
		opword 0x91010018
		opword 0x7C0501D6
		opword 0x90E10008
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010017
		opword 0x80010014
		opword 0x9001000C
		bl GXSetTevColor
		opword 0xFC00F01E
		opword 0x7FC3F378
		opword 0x38A00000
		opword 0xD8010050
		opword 0x80010054
		extsh r27, r0
		opword 0x381BFFFE
		opword 0x7C040734
		bl _JUTFont_DrawPos
		opword 0x381B0002
		opword 0x7FC3F378
		opword 0x7C040734
		opword 0x38A00000
		bl _JUTFont_DrawPos
		opword 0xFC00F01E
		opword 0x7FC3F378
		opword 0x38A0FFFE
		opword 0xD8010058
		opword 0x8001005C
		opword 0x7C1B0734
		opword 0x7F64DB78
		bl _JUTFont_DrawPos
		opword 0x7FC3F378
		opword 0x7F64DB78
		opword 0x38A00002
		bl _JUTFont_DrawPos
		opword 0x80E10018
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E1001C
		opword 0x38810010
		opword 0x38600001
		opword 0x88A1001F
		stw r7, fontColor(r13)
		opword 0x7C0501D6
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801001F
		opword 0x8001001C
		opword 0x90010010
		bl GXSetTevColor
		opword 0xFC00F01E
		opword 0x7FC3F378
		opword 0x38A00000
		opword 0xD8010058
		opword 0x8081005C
		bl _JUTFont_DrawPos
		lwz r4, pfh(r13)
		opword 0x57C3043E
		opword 0x8004000C
		opword 0x38840020
		opword 0x7C0903A6
		opword 0x28000000
		opword 0x4081004C
		opword 0x80040000
		opword 0x7C00F800
		opword 0x41820008
		opword 0x48000030
		opword 0xA0A40008
		opword 0x7C032840
		opword 0x41800024
		opword 0xA004000A
		opword 0x7C030040
		opword 0x41810018
		opword 0x7C051850
		opword 0x5403083C
		opword 0x38A3000C
		opword 0x7CA42A14
		opword 0x48000014
		opword 0x80040004
		opword 0x7C840214
		opword 0x4200FFBC
		opword 0x38A00000
		lwz r4, gp(r13)
		la r3, charspace(r13)
		opword 0x88050001
		opword 0x8084016C
		opword 0x93810058
		opword 0x5484103A
		opword 0x7C63202E
		opword 0x7C030214
		opword 0x6C008000
		opword 0x9001005C
		opword 0xC8010058
		opword 0xEC00F828
		opword 0xEFDE002A
		opword 0x887D0000
		opword 0x7C600775
		opword 0x4082FDF4
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
inline u8 fontGetGlyphWidth(u16 code) {
	return fontGetWidth(code)->width;
}
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void FontDrawStringShake(f32 x, f32 y, const s8* msg) {
#ifdef NONMATCHING
	CameraEntry* camera;
	Mtx trans, scale;
	u8 width;
	u16 code;
	f32 sx, sy;

	camera = camGetCurPtr();
	PSMTXScale(scale, fontScale.x, fontScale.y, fontScale.z);
	while (*msg) {
		if (_ismbblead(*msg)) {
			code = JUTFont_CodeToGlyph(*(u16*)msg);
			msg += 2;
		}
		else {
			code = JUTFont_CodeToGlyph(*msg++);
		}
		sx = x + fontScale.x * (irand(10000) % 3);
		sy = y + fontScale.y * (irand(10000) % 3);
		width = fontGetGlyphWidth(code);
		PSMTXTransApply(scale, trans, sx, sy, 0.0f);
		PSMTXConcat(camera->view, trans, trans);
		GXLoadPosMtxImm(trans, 0);
		fontDrawCodeEdge(code);
		x += fontScale.x * (width + charspace[gp->language]);
#endif
#ifndef NONMATCHING
	char _af_pad[128];
	asm volatile {
		opword 0xFF800890
		mr r24, r3
		opword 0xFFA01090
		bl camGetCurPtr
		la r26, fontScale(r13)
		opword 0x7C7C1B78
		lfs f1, fontScale(r13)
		la r3, _af_pad+24
		opword 0xC05A0004
		opword 0xC07A0008
		bl PSMTXScale
		lis r4, double_to_int_802c48f0@ha
		opword 0x3C605749
		opword 0x3CA05555
		lfd f31, double_to_int_802c48f0@l(r4)
		opword 0x3BE34431
		opword 0x3FC04330
		opword 0x3BA55556
		opword 0x4800027C
		opword 0x7C630774
		bl _ismbblead
		opword 0x2C030000
		opword 0x41820018
		opword 0xA0780000
		bl JUTFont_CodeToGlyph
		opword 0x7C791B78
		opword 0x3B180002
		opword 0x48000018
		opword 0x88180000
		opword 0x3B180001
		opword 0x7C030774
		bl JUTFont_CodeToGlyph
		opword 0x7C791B78
		opword 0x38602710
		bl irand
		opword 0x7C9D1896
		opword 0x93C10080
		lfs f0, fontScale(r13)
		opword 0x54800FFE
		opword 0x7C040214
		opword 0x1C000003
		opword 0x7C001850
		opword 0x38602710
		opword 0x6C008000
		opword 0x90010084
		opword 0xC8210080
		opword 0xEC21F828
		opword 0xEFC0E07A
		bl irand
		opword 0x7CBD1896
		lwz r7, pfh(r13)
		opword 0x93C10088
		opword 0x5724043E
		opword 0xC01A0004
		opword 0x38C70020
		opword 0x54A00FFE
		opword 0x80E7000C
		opword 0x7C050214
		opword 0x1C000003
		opword 0x7C001850
		opword 0x6C008000
		opword 0x9001008C
		opword 0xC8210088
		opword 0xEC21F828
		opword 0xEC40E87A
		opword 0x7CE903A6
		opword 0x28070000
		opword 0x4081004C
		opword 0x80060000
		opword 0x7C00F800
		opword 0x41820008
		opword 0x48000030
		opword 0xA0660008
		opword 0x7C041840
		opword 0x41800024
		opword 0xA006000A
		opword 0x7C040040
		opword 0x41810018
		opword 0x7C032050
		opword 0x5403083C
		opword 0x3863000C
		opword 0x7C661A14
		opword 0x48000014
		opword 0x80060004
		opword 0x7CC60214
		opword 0x4200FFBC
		opword 0x38600000
		opword 0xFC20F090
		opword 0x8B630001
		lfs f3, float_0_8041a300(r2)
		opword 0x38610020
		opword 0x38810050
		bl PSMTXTransApply
		opword 0x38810050
		opword 0x387C011C
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38610050
		opword 0x38800000
		bl GXLoadPosMtxImm
		lwz r0, fontEdge(r13)
		opword 0x2C000000
		opword 0x418200E8
		lwz r7, fontColTbl(r13)
		opword 0x3C608081
		lwz r8, fontColor(r13)
		opword 0x38C38081
		opword 0x90E10014
		opword 0x3881000C
		lbz r0, fontAlpha(r13)
		opword 0x38600001
		opword 0x88A10017
		opword 0x91010018
		opword 0x7C0501D6
		opword 0x90E10008
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010017
		opword 0x80010014
		opword 0x9001000C
		bl GXSetTevColor
		opword 0x7F23CB78
		opword 0x3880FFFE
		opword 0x38A00000
		bl _JUTFont_DrawPos
		opword 0x7F23CB78
		opword 0x38800002
		opword 0x38A00000
		bl _JUTFont_DrawPos
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A0FFFE
		bl _JUTFont_DrawPos
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00002
		bl _JUTFont_DrawPos
		opword 0x80E10018
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E1001C
		opword 0x38810010
		opword 0x38600001
		opword 0x88A1001F
		stw r7, fontColor(r13)
		opword 0x7C0501D6
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801001F
		opword 0x8001001C
		opword 0x90010010
		bl GXSetTevColor
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		bl _JUTFont_DrawPos
		lwz r4, gp(r13)
		la r3, charspace(r13)
		opword 0x93C10088
		opword 0x8004016C
		lfs f1, fontScale(r13)
		opword 0x5400103A
		opword 0x7C03002E
		opword 0x7C1B0214
		opword 0x6C008000
		opword 0x9001008C
		opword 0xC8010088
		opword 0xEC00F828
		fmadds f28, f1, f0, f28
		opword 0x88780000
		opword 0x7C600775
		opword 0x4082FD80
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif
extern int strcmp(const char* a, const char* b);
extern int sscanf(const char* s, const char* format, ...);
extern s32 msgIconStr2ID(const char* str);
extern void iconGetWidthHight(u16* width, u16* height, u16 id);
extern void iconDispGxAlpha(Vec* position, s16 flags, u16 iconId, u8 alpha, f32 scale);

#ifdef NONMATCHING
static inline void fontDrawCodeEdgeI(u16 code, s16 x, s16 y) {
	if (fontEdge) {
		GXColor save = fontColor;
		FontDrawColorIDX(0);
		fontDrawPairXI(code, x, y);
		fontDrawPairYI(code, x, y);
		FontDrawColor(save);
	}
	_JUTFont_DrawPos(code, x, y);
}
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void FontDrawMessage(s32 x, s32 y, const char* msg) {
#ifdef NONMATCHING
	s32 cx;
	s32 cy;
	u16 code;
	s8 tag[0x80];
	s8 value[0x80];
	char name[0x20];
	Vec pos;
	GXColor color;
	s32 id;
	s32 d1, d2, d3;
	f32 scale;
	u16 w, h;

	cx = x;
	cy = y;
	while (*(const s8*)msg) {
		code = 0xFFFF;
		if (_ismbblead(*(const s8*)msg)) {
			code = JUTFont_CodeToGlyph(*(u16*)msg);
			msg += 2;
		}
		else {
			switch (*(const s8*)msg) {
				case '\n':
					cx = x;
					cy -= 28;
					msg++;
					break;
				case '<':
					msg = msgGetCommand((char*)msg + 1, (char*)tag, (char*)value);
					if (!strcmp((char*)tag, "red")) {
						FontDrawColor((GXColor){0xE0, 0x00, 0x00, 0xFF});
					}
					else if (!strcmp((char*)tag, "/red")) {
						FontDrawColor(fontColTbl[0]);
					}
					else if (!strcmp((char*)tag, "col")) {
						sscanf((char*)value, "%x", &color);
						FontDrawColor(color);
					}
					else if (!strcmp((char*)tag, "/col")) {
						FontDrawColor(fontColTbl[0]);
					}
					else if (!strcmp((char*)tag, "icon")) {
						camGetCurPtr();
						if (value[0] >= '0' && value[0] <= '9') {
							sscanf((char*)value, str_802C4904, &id, &scale, &d1, &d2, &d3);
						}
						else {
							sscanf((char*)value, str_802C4910, name, &scale, &d1, &d2, &d3);
							id = msgIconStr2ID(name);
							if (id < 0) {
								id = 0;
							}
						}
						iconGetWidthHight(&w, &h, id);
						pos.x = d1 + (cx + 0.5f * w * scale);
						pos.y = d2 + (cy - h * scale);
						pos.z = 0.0f;
						iconDispGxAlpha(&pos, 0x10, id, fontAlpha, scale);
						FontDrawStart_alpha(fontAlpha);
						FontDrawColor(fontColor);
						cx += w * scale + d3;
					}
					else if (tag[0] == 'R' || (tag[0] == '/' && tag[0] == (u32)'/r')) {
						break;
					}
					if (*(const s8*)msg == '\n') {
						msg++;
					}
					break;
				default:
					code = JUTFont_CodeToGlyph(*((const s8*)msg)++);
					break;
			}
		}
		if (code != 0xFFFF) {
			fontDrawCodeEdgeI(code, cx, cy);
			cx += fontGetWidth(code)->width + charspace[gp->language];
		}
#endif
#ifndef NONMATCHING
	char _af_pad[508];
	asm volatile {
		opword 0x7C791B78
		lis r3, str_802C48A0@ha
		opword 0x7CBA2B78
		opword 0x7F3DCB78
		opword 0x7C9C2378
		addi r30, r3, str_802C48A0@l
		opword 0x3FE00001
		opword 0x480006CC
		opword 0x3B7FFFFF
		opword 0x7C630774
		bl _ismbblead
		opword 0x2C030000
		opword 0x41820018
		opword 0xA07A0000
		bl JUTFont_CodeToGlyph
		opword 0x7C7B1B78
		opword 0x3B5A0002
		opword 0x480004E8
		opword 0x881A0000
		opword 0x7C000774
		opword 0x2C00003C
		opword 0x41820024
		opword 0x408004C0
		opword 0x2C00000A
		opword 0x41820008
		opword 0x480004B4
		opword 0x7F3DCB78
		opword 0x3B9CFFE4
		opword 0x3B5A0001
		opword 0x480004B8
		opword 0x387A0001
		la r4, _af_pad+292
		opword 0x38A100AC
		bl msgGetCommand
		opword 0x7C601B78
		opword 0x3861012C
		opword 0x7C1A0378
		la r4, str_8041A31C(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820058
		lwz r7, dat_8041a2e8(r2)
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E10064
		opword 0x38810050
		opword 0x38600001
		opword 0x88A10067
		opword 0x90E1000C
		opword 0x7C0501D6
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010067
		opword 0x80010064
		opword 0x90010050
		bl GXSetTevColor
		opword 0x48000410
		opword 0x3861012C
		la r4, str_8041A320(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820058
		lwz r7, fontColTbl(r13)
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E10060
		opword 0x3881004C
		opword 0x38600001
		opword 0x88A10063
		opword 0x90E10020
		opword 0x7C0501D6
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010063
		opword 0x80010060
		opword 0x9001004C
		bl GXSetTevColor
		opword 0x480003A8
		opword 0x3861012C
		la r4, str_8041A32C(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x4082006C
		opword 0x386100AC
		opword 0x38A1007C
		la r4, str_8041A330(r2)
		opword 0x4CC63182
		bl sscanf
		opword 0x80E1007C
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E1005C
		opword 0x38810048
		opword 0x38600001
		opword 0x88A1005F
		opword 0x90E1001C
		opword 0x7C0501D6
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801005F
		opword 0x8001005C
		opword 0x90010048
		bl GXSetTevColor
		opword 0x4800032C
		opword 0x3861012C
		la r4, str_8041A334(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820058
		lwz r7, fontColTbl(r13)
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E10058
		opword 0x38810044
		opword 0x38600001
		opword 0x88A1005B
		opword 0x90E10018
		opword 0x7C0501D6
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801005B
		opword 0x80010058
		opword 0x90010044
		bl GXSetTevColor
		opword 0x480002C4
		opword 0x3861012C
		la r4, str_8041A314(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820290
		bl camGetCurPtr
		opword 0x880100AC
		opword 0x7C000774
		opword 0x2C000030
		opword 0x41800034
		opword 0x2C000039
		opword 0x4181002C
		opword 0x386100AC
		opword 0x389E0064
		opword 0x38A10078
		opword 0x38C10068
		opword 0x38E10074
		opword 0x39010070
		opword 0x3921006C
		opword 0x4CC63182
		bl sscanf
		opword 0x48000044
		opword 0x386100AC
		opword 0x389E0070
		opword 0x38A1008C
		opword 0x38C10068
		opword 0x38E10074
		opword 0x39010070
		opword 0x3921006C
		opword 0x4CC63182
		bl sscanf
		opword 0x3861008C
		bl msgIconStr2ID
		opword 0x2C030000
		opword 0x90610078
		opword 0x4080000C
		opword 0x38000000
		opword 0x90010078
		opword 0x80010078
		opword 0x3861000A
		opword 0x38810008
		opword 0x5405043E
		bl iconGetWidthHight
		opword 0xA061000A
		opword 0x3D204330
		opword 0xA0010008
		opword 0x6FA88000
		opword 0x906101BC
		opword 0x6F858000
		opword 0x80E10074
		opword 0x38610080
		opword 0x912101B8
		opword 0x38800010
		opword 0xC87E0048
		opword 0x6CEA8000
		opword 0xC80101B8
		opword 0x900101D4
		opword 0xEC001828
		lfs f2, float_0p5_8041a328(r2)
		opword 0x912101D0
		opword 0x80C10070
		opword 0xECA20032
		opword 0xC84101D0
		opword 0x910101C4
		opword 0x6CC78000
		opword 0xC8DE0050
		opword 0xEC621828
		opword 0x912101C0
		opword 0xC0210068
		opword 0xC80101C0
		opword 0x90A101DC
		opword 0xEC803028
		lfs f0, float_0_8041a300(r2)
		opword 0x912101D8
		opword 0x80010078
		opword 0xC84101D8
		opword 0xEC85207A
		opword 0x914101B4
		opword 0x5405043E
		opword 0xEC423028
		lbz r6, fontAlpha(r13)
		opword 0x912101B0
		opword 0xC8A101B0
		opword 0xEC43107C
		opword 0x90E101CC
		opword 0xECA53028
		opword 0x912101C8
		opword 0xEC85202A
		opword 0xC86101C8
		opword 0xD0010088
		opword 0xEC033028
		opword 0xD0810080
		opword 0xEC00102A
		opword 0xD0010084
		bl iconDispGxAlpha
		lwz r9, fontColTbl(r13)
		opword 0x3C608081
		lbz r10, fontAlpha(r13)
		opword 0x39038081
		opword 0x9121003C
		opword 0x38000000
		opword 0x80DE0020
		opword 0x38610040
		opword 0x8881003F
		opword 0x80BE0024
		opword 0x7CE451D6
		opword 0x809E0028
		stw r0, fontEdge(r13)
		stw r4, fontScale+0x8(r13)
		opword 0x7D083896
		stw r9, fontColor(r13)
		stb r10, fontAlpha(r13)
		stw r6, fontScale(r13)
		opword 0x7C883A14
		opword 0x7C843E70
		stw r5, fontScale+0x4(r13)
		opword 0x54800FFE
		opword 0x7C040214
		opword 0x9801003F
		opword 0x8001003C
		opword 0x90010040
		bl JUTFont_DrawStart
		lwz r7, fontColor(r13)
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E10054
		opword 0x38810038
		opword 0x38600001
		opword 0x88A10057
		opword 0x90E10014
		opword 0x7C0501D6
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010057
		opword 0x80010054
		opword 0x90010038
		bl GXSetTevColor
		opword 0x8001006C
		opword 0x3C804330
		opword 0xA061000A
		opword 0x6FA58000
		opword 0x6C008000
		opword 0x908101E8
		opword 0xC89E0050
		opword 0x906101EC
		opword 0xC83E0048
		opword 0xC80101E8
		opword 0x900101F4
		opword 0xEC400828
		opword 0xC0210068
		opword 0x908101F0
		opword 0xC80101F0
		opword 0x90A101E4
		opword 0xEC002028
		opword 0x908101E0
		opword 0xC86101E0
		opword 0xEC02007A
		opword 0xEC232028
		opword 0xEC01002A
		opword 0xFC00001E
		opword 0xD80101F8
		opword 0x83A101FC
		opword 0x48000024
		opword 0x8801012C
		opword 0x7C000774
		opword 0x2C000052
		opword 0x4182003C
		opword 0x2C00002F
		opword 0x4082000C
		opword 0x28002F72
		opword 0x4182002C
		opword 0x881A0000
		opword 0x2C00000A
		opword 0x40820020
		opword 0x3B5A0001
		opword 0x48000018
		opword 0x881A0000
		opword 0x3B5A0001
		opword 0x7C030774
		bl JUTFont_CodeToGlyph
		opword 0x7C7B1B78
		opword 0x5760043E
		opword 0x2800FFFF
		opword 0x418201B4
		lwz r0, fontEdge(r13)
		opword 0x2C000000
		opword 0x41820108
		lwz r7, fontColTbl(r13)
		opword 0x3C608081
		lwz r8, fontColor(r13)
		opword 0x38C38081
		opword 0x90E1002C
		opword 0x38810024
		lbz r0, fontAlpha(r13)
		opword 0x38600001
		opword 0x88A1002F
		opword 0x91010030
		opword 0x7C0501D6
		opword 0x90E10010
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801002F
		opword 0x8001002C
		opword 0x90010024
		bl GXSetTevColor
		opword 0x7FB80734
		extsh r23, r28
		opword 0x3818FFFE
		opword 0x7F63DB78
		opword 0x7EE5BB78
		opword 0x7C040734
		bl _JUTFont_DrawPos
		opword 0x38180002
		opword 0x7F63DB78
		opword 0x7EE5BB78
		opword 0x7C040734
		bl _JUTFont_DrawPos
		opword 0x7EF8BB78
		opword 0x7FB70734
		opword 0x3818FFFE
		opword 0x7F63DB78
		opword 0x7EE4BB78
		opword 0x7C050734
		bl _JUTFont_DrawPos
		opword 0x38180002
		opword 0x7F63DB78
		opword 0x7EE4BB78
		opword 0x7C050734
		bl _JUTFont_DrawPos
		opword 0x80E10030
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E10034
		opword 0x38810028
		opword 0x38600001
		opword 0x88A10037
		stw r7, fontColor(r13)
		opword 0x7C0501D6
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010037
		opword 0x80010034
		opword 0x90010028
		bl GXSetTevColor
		opword 0x7F63DB78
		opword 0x7FA40734
		opword 0x7F850734
		bl _JUTFont_DrawPos
		lwz r5, pfh(r13)
		opword 0x3C605749
		opword 0x38834431
		opword 0x5763043E
		opword 0x8005000C
		opword 0x38C50020
		opword 0x7C0903A6
		opword 0x28000000
		opword 0x4081004C
		opword 0x80060000
		opword 0x7C002000
		opword 0x41820008
		opword 0x48000030
		opword 0xA0A60008
		opword 0x7C032840
		opword 0x41800024
		opword 0xA006000A
		opword 0x7C030040
		opword 0x41810018
		opword 0x7C051850
		opword 0x5403083C
		opword 0x38A3000C
		opword 0x7CA62A14
		opword 0x48000014
		opword 0x80060004
		opword 0x7CC60214
		opword 0x4200FFBC
		opword 0x38A00000
		lwz r4, gp(r13)
		la r3, charspace(r13)
		opword 0x88050001
		opword 0x8084016C
		opword 0x7FA0EA14
		opword 0x5480103A
		opword 0x7C03002E
		opword 0x7FA0EA14
		opword 0x887A0000
		opword 0x7C600775
		opword 0x4082F930
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif


#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
#endif
void FontDrawMessageMtx(Mtx mtx, const char* msg) {
#ifdef NONMATCHING
	CameraEntry* camera;
	u16 code;
	s32 cx;
	s32 cy;
	f32 x;
	s8 tag[0x80];
	s8 value[0x80];
	Mtx m2;
	Mtx m;
	char name[0x20];
	Vec pos;
	s32 id;
	s32 d1, d2, d3;
	f32 scale;
	u16 w, h;

	camera = camGetCurPtr();
	cx = 0;
	cy = 0;
	x = 0.0f;
	while (*(const s8*)msg) {
		code = 0xFFFF;
		if (_ismbblead(*(const s8*)msg)) {
			code = JUTFont_CodeToGlyph(*(u16*)msg);
			msg += 2;
		}
		else {
			switch (*(const s8*)msg) {
				case '\n':
					cx = x;
					cy -= 28;
					msg++;
					break;
				case '<':
					msg = msgGetCommand((char*)msg + 1, (char*)tag, (char*)value);
					if (!strcmp((char*)tag, "red")) {
						FontDrawColor((GXColor){0xE0, 0x00, 0x00, 0xFF});
					}
					else if (!strcmp((char*)tag, "/red")) {
						FontDrawColor(fontColTbl[0]);
					}
					else if (!strcmp((char*)tag, "icon")) {
						camGetCurPtr();
						if (value[0] >= '0' && value[0] <= '9') {
							sscanf((char*)value, str_802C4904, &id, &scale, &d1, &d2, &d3);
						}
						else {
							sscanf((char*)value, str_802C4910, name, &scale, &d1, &d2, &d3);
							id = msgIconStr2ID(name);
							if (id < 0) {
								id = 0;
							}
						}
						iconGetWidthHight(&w, &h, id);
						pos.x = d1 + (cx + 0.5f * w * scale);
						pos.y = d2 + (cy - h * scale);
						pos.z = 0.0f;
						PSMTXMultVec(mtx, &pos, &pos);
						scale = scale;
						iconDispGxAlpha(&pos, 0x10, id, fontAlpha, scale);
						FontDrawStart_alpha(fontAlpha);
						FontDrawColor(fontColor);
						cx += w * scale + d3;
					}
					else if (tag[0] == 'R' || (tag[0] == '/' && tag[0] == (u32)'/r')) {
						break;
					}
					if (*(const s8*)msg == '\n') {
						msg++;
					}
					break;
				default:
					code = JUTFont_CodeToGlyph(*((const s8*)msg)++);
					break;
			}
		}
		if (code != 0xFFFF) {
			PSMTXTrans(m, cx, cy, 0.0f);
			PSMTXConcat(camera->view, mtx, m2);
			PSMTXConcat(m2, m, m2);
			GXLoadPosMtxImm(m2, 0);
			fontDrawCodeEdge(code);
			cx += fontGetWidth(code)->width + charspace[gp->language];
		}
#endif
#ifndef NONMATCHING
	char _af_pad[572];
	asm {
		lis r5, str_802C48A0@ha
	}
	asm volatile {
		mr r23, r3
		opword 0x7C982378
		addi r29, r5, str_802C48A0@l
		bl camGetCurPtr
		lfs f0, float_0_8041a300(r2)
		opword 0x7C7E1B78
		opword 0x3B400000
		opword 0x3B200000
		opword 0xFC00001E
		opword 0x3FE00001
		stfd f0, _af_pad+488(r1)
		opword 0x838101F4
		opword 0x48000644
		opword 0x3B7FFFFF
		opword 0x7C630774
		bl _ismbblead
		opword 0x2C030000
		opword 0x41820018
		opword 0xA0780000
		bl JUTFont_CodeToGlyph
		opword 0x7C7B1B78
		opword 0x3B180002
		opword 0x48000418
		opword 0x88180000
		opword 0x7C000774
		opword 0x2C00003C
		opword 0x41820024
		opword 0x408003F0
		opword 0x2C00000A
		opword 0x41820008
		opword 0x480003E4
		opword 0x7F9AE378
		opword 0x3B39FFE4
		opword 0x3B180001
		opword 0x480003E8
		opword 0x38780001
		opword 0x38810170
		opword 0x38A100F0
		bl msgGetCommand
		opword 0x7C601B78
		opword 0x38610170
		opword 0x7C180378
		la r4, str_8041A31C(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820058
		lwz r7, dat_8041a2ec(r2)
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E1004C
		opword 0x38810040
		opword 0x38600001
		opword 0x88A1004F
		opword 0x90E1000C
		opword 0x7C0501D6
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801004F
		opword 0x8001004C
		opword 0x90010040
		bl GXSetTevColor
		opword 0x48000340
		opword 0x38610170
		la r4, str_8041A320(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820058
		lwz r7, fontColTbl(r13)
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E10048
		opword 0x3881003C
		opword 0x38600001
		opword 0x88A1004B
		opword 0x90E10018
		opword 0x7C0501D6
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801004B
		opword 0x80010048
		opword 0x9001003C
		bl GXSetTevColor
		opword 0x480002D8
		opword 0x38610170
		la r4, str_8041A314(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x408202A4
		bl camGetCurPtr
		opword 0x880100F0
		opword 0x7C000774
		opword 0x2C000030
		opword 0x41800034
		opword 0x2C000039
		opword 0x4181002C
		opword 0x386100F0
		opword 0x389D0064
		opword 0x38A10060
		opword 0x38C10050
		opword 0x38E1005C
		opword 0x39010058
		opword 0x39210054
		opword 0x4CC63182
		bl sscanf
		opword 0x48000044
		opword 0x386100F0
		opword 0x389D0070
		opword 0x38A10070
		opword 0x38C10050
		opword 0x38E1005C
		opword 0x39010058
		opword 0x39210054
		opword 0x4CC63182
		bl sscanf
		opword 0x38610070
		bl msgIconStr2ID
		opword 0x2C030000
		opword 0x90610060
		opword 0x4080000C
		opword 0x38000000
		opword 0x90010060
		opword 0x80010060
		opword 0x3861000A
		opword 0x38810008
		opword 0x5405043E
		bl iconGetWidthHight
		opword 0xA001000A
		opword 0x3D204330
		opword 0xA0C10008
		opword 0x6F488000
		opword 0x900101FC
		opword 0x6F208000
		opword 0x80A1005C
		opword 0x38810064
		opword 0x912101F8
		opword 0x7EE3BB78
		opword 0x80E10058
		opword 0x6CAA8000
		opword 0xC89D0048
		opword 0x7C852378
		opword 0xC80101F8
		opword 0x6CE78000
		opword 0x91010204
		opword 0xEC202028
		lfs f2, float_0p5_8041a328(r2)
		opword 0x91210200
		opword 0xC8BD0050
		opword 0xC8010200
		opword 0xEC620072
		opword 0x90C10214
		opword 0xEC402828
		opword 0xC0C10050
		opword 0x91210210
		lfs f0, float_0_8041a300(r2)
		opword 0xC8210210
		opword 0xEC6311BA
		opword 0x9001021C
		opword 0xEC412028
		opword 0x91210218
		opword 0xC8210218
		opword 0x914101F4
		opword 0xEC212828
		opword 0x912101F0
		opword 0xC88101F0
		opword 0xEC2209BC
		opword 0x90E1020C
		opword 0xEC842828
		opword 0x91210208
		opword 0xC8410208
		opword 0xEC64182A
		opword 0xD001006C
		opword 0xEC022828
		opword 0xD0610064
		opword 0xEC00082A
		opword 0xD0010068
		bl PSMTXMultVec
		opword 0x80010060
		opword 0x38610064
		opword 0xC0210050
		opword 0x38800010
		lbz r6, fontAlpha(r13)
		opword 0x5405043E
		bl iconDispGxAlpha
		lwz r9, fontColTbl(r13)
		opword 0x3C608081
		lbz r10, fontAlpha(r13)
		opword 0x39038081
		opword 0x91210034
		opword 0x38000000
		opword 0x80DD0020
		opword 0x38610038
		opword 0x88810037
		opword 0x80BD0024
		opword 0x7CE451D6
		opword 0x809D0028
		stw r0, fontEdge(r13)
		stw r4, fontScale+0x8(r13)
		opword 0x7D083896
		stw r9, fontColor(r13)
		stb r10, fontAlpha(r13)
		stw r6, fontScale(r13)
		opword 0x7C883A14
		opword 0x7C843E70
		stw r5, fontScale+0x4(r13)
		opword 0x54800FFE
		opword 0x7C040214
		opword 0x98010037
		opword 0x80010034
		opword 0x90010038
		bl JUTFont_DrawStart
		lwz r7, fontColor(r13)
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E10044
		opword 0x38810030
		opword 0x38600001
		opword 0x88A10047
		opword 0x90E10014
		opword 0x7C0501D6
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010047
		opword 0x80010044
		opword 0x90010030
		bl GXSetTevColor
		opword 0x80010054
		opword 0x3C804330
		opword 0xA061000A
		opword 0x6F458000
		opword 0x6C008000
		opword 0x90810228
		opword 0xC89D0050
		opword 0x9061022C
		opword 0xC83D0048
		opword 0xC8010228
		opword 0x90010234
		opword 0xEC400828
		opword 0xC0210050
		opword 0x90810230
		opword 0xC8010230
		opword 0x90A10224
		opword 0xEC002028
		opword 0x90810220
		opword 0xC8610220
		opword 0xEC02007A
		opword 0xEC232028
		opword 0xEC01002A
		opword 0xFC00001E
		opword 0xD8010238
		opword 0x8341023C
		opword 0x48000024
		opword 0x88010170
		opword 0x7C000774
		opword 0x2C000052
		opword 0x4182003C
		opword 0x2C00002F
		opword 0x4082000C
		opword 0x28002F72
		opword 0x4182002C
		opword 0x88180000
		opword 0x2C00000A
		opword 0x40820020
		opword 0x3B180001
		opword 0x48000018
		opword 0x88180000
		opword 0x3B180001
		opword 0x7C030774
		bl JUTFont_CodeToGlyph
		opword 0x7C7B1B78
		opword 0x5760043E
		opword 0x2800FFFF
		opword 0x418201FC
		opword 0x3C804330
		opword 0x6F438000
		opword 0x6F208000
		opword 0x9061023C
		opword 0xC85D0050
		opword 0x38610090
		opword 0x90810238
		lfs f3, float_0_8041a300(r2)
		opword 0xC8010238
		opword 0x90010234
		opword 0xEC201028
		opword 0x90810230
		opword 0xC8010230
		opword 0xEC401028
		bl PSMTXTrans
		opword 0x7EE4BB78
		opword 0x387E011C
		opword 0x38A100C0
		bl PSMTXConcat
		opword 0x386100C0
		opword 0x38810090
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386100C0
		opword 0x38800000
		bl GXLoadPosMtxImm
		lwz r0, fontEdge(r13)
		opword 0x2C000000
		opword 0x418200E8
		lwz r7, fontColTbl(r13)
		opword 0x3C608081
		lwz r8, fontColor(r13)
		opword 0x38C38081
		opword 0x90E10024
		opword 0x3881001C
		lbz r0, fontAlpha(r13)
		opword 0x38600001
		opword 0x88A10027
		opword 0x91010028
		opword 0x7C0501D6
		opword 0x90E10010
		stw r7, fontColor(r13)
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010027
		opword 0x80010024
		opword 0x9001001C
		bl GXSetTevColor
		opword 0x7F63DB78
		opword 0x3880FFFE
		opword 0x38A00000
		bl _JUTFont_DrawPos
		opword 0x7F63DB78
		opword 0x38800002
		opword 0x38A00000
		bl _JUTFont_DrawPos
		opword 0x7F63DB78
		opword 0x38800000
		opword 0x38A0FFFE
		bl _JUTFont_DrawPos
		opword 0x7F63DB78
		opword 0x38800000
		opword 0x38A00002
		bl _JUTFont_DrawPos
		opword 0x80E10028
		opword 0x3C608081
		opword 0x38C38081
		lbz r0, fontAlpha(r13)
		opword 0x90E1002C
		opword 0x38810020
		opword 0x38600001
		opword 0x88A1002F
		stw r7, fontColor(r13)
		opword 0x7C0501D6
		opword 0x7CA60096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801002F
		opword 0x8001002C
		opword 0x90010020
		bl GXSetTevColor
		opword 0x7F63DB78
		opword 0x38800000
		opword 0x38A00000
		bl _JUTFont_DrawPos
		lwz r5, pfh(r13)
		opword 0x3C605749
		opword 0x38834431
		opword 0x5763043E
		opword 0x8005000C
		opword 0x38C50020
		opword 0x7C0903A6
		opword 0x28000000
		opword 0x4081004C
		opword 0x80060000
		opword 0x7C002000
		opword 0x41820008
		opword 0x48000030
		opword 0xA0A60008
		opword 0x7C032840
		opword 0x41800024
		opword 0xA006000A
		opword 0x7C030040
		opword 0x41810018
		opword 0x7C051850
		opword 0x5403083C
		opword 0x38A3000C
		opword 0x7CA62A14
		opword 0x48000014
		opword 0x80060004
		opword 0x7CC60214
		opword 0x4200FFBC
		opword 0x38A00000
		lwz r4, gp(r13)
		la r3, charspace(r13)
		opword 0x88050001
		opword 0x8084016C
		opword 0x7F40D214
		opword 0x5480103A
		opword 0x7C03002E
		opword 0x7F40D214
		opword 0x88780000
		opword 0x7C600775
		opword 0x4082F9B8
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

void hankakuSearch(s8 c) {
	JUTFont_CodeToGlyph(c);
}

u16 kanjiSearch(u32 code) {
	return JUTFont_CodeToGlyph(code);
}

u16 kanjiGetWidth(u16 code) {
	return fontGetWidth(code)->width;
}


#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
u16 FontGetMessageWidthLine(const char* msg, u16* lines) {
#ifdef NONMATCHING
	u16 code;
	u16 maxWidth = 0;
	u16 width = 0;
	s32 lineCount = 0;
	s8 tag[0x80];
	s8 value[0x80];
	char name[0x20];
	s32 id;
	s32 d1, d2, d3;
	f32 scale;
	u16 w, h;

	while (*(const s8*)msg) {
		code = 0xFFFF;
		if (_ismbblead(*(const s8*)msg)) {
			code = JUTFont_CodeToGlyph(*(u16*)msg);
			msg += 2;
		}
		else {
			switch (*(const s8*)msg) {
				case '\n':
					if (maxWidth < width) {
						maxWidth = width;
					}
					width = 0;
					lineCount++;
					msg++;
					break;
				case '<':
					msg = msgGetCommand((char*)msg + 1, (char*)tag, (char*)value);
					if (!strcmp((char*)tag, "icon")) {
						camGetCurPtr();
						if (value[0] >= '0' && value[0] <= '9') {
							sscanf((char*)value, str_802C4904, &id, &scale, &d1, &d2, &d3);
						}
						else {
							sscanf((char*)value, str_802C4910, name, &scale, &d1, &d2, &d3);
							id = msgIconStr2ID(name);
							if (id < 0) {
								id = 0;
							}
						}
						iconGetWidthHight(&w, &h, id);
						width += w * scale + d3;
					}
					else if (tag[0] == 'R' || (tag[0] == '/' && tag[0] == (u32)'/r')) {
						break;
					}
					if (*(const s8*)msg == '\n') {
						msg++;
					}
					break;
				default:
					code = JUTFont_CodeToGlyph(*((const s8*)msg)++);
					break;
			}
		}
		if (code != 0xFFFF) {
			width += fontGetWidth(code)->width + charspace[gp->language];
		}
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FE80
		opword 0x7C0802A6
		opword 0x90010184
		opword 0xBF210164
		opword 0x7C791B78
		opword 0x7C9A2378
		opword 0x3BA00000
		opword 0x3B800000
		opword 0x3B600000
		opword 0x3FE00001
		opword 0x48000294
		opword 0x3BDFFFFF
		opword 0x7C630774
		bl _ismbblead
		opword 0x2C030000
		opword 0x41820018
		opword 0xA0790000
		bl JUTFont_CodeToGlyph
		opword 0x7C7E1B78
		opword 0x3B390002
		opword 0x480001D0
		opword 0x88190000
		opword 0x7C000774
		opword 0x2C00003C
		opword 0x41820038
		opword 0x408001A8
		opword 0x2C00000A
		opword 0x41820008
		opword 0x4800019C
		opword 0x57A3043E
		opword 0x5780043E
		opword 0x7C030040
		opword 0x40800008
		opword 0x7F9DE378
		opword 0x3B800000
		opword 0x3B7B0001
		opword 0x3B390001
		opword 0x4800018C
		opword 0x38790001
		opword 0x388100C0
		opword 0x38A10040
		bl msgGetCommand
		opword 0x7C601B78
		opword 0x386100C0
		opword 0x7C190378
		la r4, str_8041A314(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820118
		bl camGetCurPtr
		opword 0x88010040
		opword 0x7C000774
		opword 0x2C000030
		opword 0x41800038
		opword 0x2C000039
		opword 0x41810030
		lis r4, str_802C4904@ha
		opword 0x38610040
		addi r4, r4, str_802C4904@l
		opword 0x38A1001C
		opword 0x38C1000C
		opword 0x38E10018
		opword 0x39010014
		opword 0x39210010
		opword 0x4CC63182
		bl sscanf
		opword 0x48000048
		lis r4, str_802C4910@ha
		opword 0x38610040
		addi r4, r4, str_802C4910@l
		opword 0x38A10020
		opword 0x38C1000C
		opword 0x38E10018
		opword 0x39010014
		opword 0x39210010
		opword 0x4CC63182
		bl sscanf
		opword 0x38610020
		bl msgIconStr2ID
		opword 0x2C030000
		opword 0x9061001C
		opword 0x4080000C
		opword 0x38000000
		opword 0x9001001C
		opword 0x8001001C
		opword 0x3861000A
		opword 0x38810008
		opword 0x5405043E
		bl iconGetWidthHight
		opword 0xA081000A
		opword 0x3CA04330
		opword 0x80010010
		lis r3, double_to_int_802c48f0@ha
		lis r6, double_to_int_mask_802c48e8@ha
		opword 0x9081014C
		addi r4, r6, double_to_int_mask_802c48e8@l
		opword 0x6C008000
		opword 0x90A10148
		opword 0x5786043E
		opword 0xC8840000
		opword 0xC8010148
		opword 0x90010154
		lfd f1, double_to_int_802c48f0@l(r3)
		opword 0xEC602028
		opword 0x90A10150
		opword 0xC041000C
		opword 0xC8010150
		opword 0x90C10144
		opword 0xEC000828
		opword 0x90A10140
		opword 0xC8210140
		opword 0xEC0300BA
		opword 0xEC212028
		opword 0xEC01002A
		opword 0xFC00001E
		opword 0xD8010158
		opword 0x8381015C
		opword 0x48000024
		opword 0x880100C0
		opword 0x7C000774
		opword 0x2C000052
		opword 0x4182003C
		opword 0x2C00002F
		opword 0x4082000C
		opword 0x28002F72
		opword 0x4182002C
		opword 0x88190000
		opword 0x2C00000A
		opword 0x40820020
		opword 0x3B390001
		opword 0x48000018
		opword 0x88190000
		opword 0x3B390001
		opword 0x7C030774
		bl JUTFont_CodeToGlyph
		opword 0x7C7E1B78
		opword 0x57C4043E
		opword 0x2804FFFF
		opword 0x41820094
		lwz r5, pfh(r13)
		opword 0x3C605749
		opword 0x38634431
		opword 0x8005000C
		opword 0x38C50020
		opword 0x7C0903A6
		opword 0x28000000
		opword 0x4081004C
		opword 0x80060000
		opword 0x7C001800
		opword 0x41820008
		opword 0x48000030
		opword 0xA0A60008
		opword 0x7C042840
		opword 0x41800024
		opword 0xA006000A
		opword 0x7C040040
		opword 0x41810018
		opword 0x7C052050
		opword 0x5403083C
		opword 0x38A3000C
		opword 0x7CA62A14
		opword 0x48000014
		opword 0x80060004
		opword 0x7CC60214
		opword 0x4200FFBC
		opword 0x38A00000
		lwz r4, gp(r13)
		la r3, charspace(r13)
		opword 0x88050001
		opword 0x8084016C
		opword 0x7C00E214
		opword 0x5484103A
		opword 0x7C63202E
		opword 0x7C030214
		opword 0x541C043E
		opword 0x88790000
		opword 0x7C600775
		opword 0x4082FD68
		opword 0x57A3043E
		opword 0x5780043E
		opword 0x7C030040
		opword 0x40800008
		opword 0x7F9DE378
		opword 0x57A0043F
		opword 0x41820020
		lwz r4, gp(r13)
		la r3, charspace(r13)
		opword 0x8004016C
		opword 0x5400103A
		opword 0x7C03002E
		opword 0x7C00E850
		opword 0x541D043E
		opword 0x281A0000
		opword 0x41820008
		opword 0xB37A0000
		opword 0x7FA3EB78
		opword 0xBB210164
		opword 0x80010184
		opword 0x7C0803A6
		opword 0x38210180
#endif
	}
#ifdef NONMATCHING
	if (maxWidth < width) {
		maxWidth = width;
	}
	if (maxWidth) {
		if (code && code) {
		}
		maxWidth -= charspace[gp->language];
	}
	if (lines) {
		*lines = lineCount;
	}
	return maxWidth;
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

u16 FontGetMessageWidth(const char* message) {
	return FontGetMessageWidthLine(message, NULL);
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
GXColor HSV2RGB(GXColor hsv) {
#ifdef NONMATCHING
	f32 h, s, v, f, p, q, r, g, b;
	s32 i;
	GXColor out;

	s = hsv.g / 255.0f;
	v = hsv.b / 255.0f;
	h = (360.0f * hsv.r) / 256.0f / 60.0f;
	i = floor(h);
	f = h - i;
	if (!(i & 1)) {
		f = 1.0f - f;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FF60
		opword 0x7C0802A6
		opword 0x900100A4
		opword 0xDBE10090
		opword 0xF3E10098
		opword 0xDBC10080
		opword 0xF3C10088
		opword 0xDBA10070
		opword 0xF3A10078
		opword 0xDB810060
		opword 0xF3810068
		opword 0xDB610050
		opword 0xF3610058
		opword 0xDB410040
		opword 0xF3410048
		opword 0x93E1003C
		opword 0x7C7F1B78
		opword 0x3C604330
		opword 0x881F0000
		lis r4, double_to_int_mask_802c48e8@ha
		opword 0x88BF0001
		opword 0x90010024
		opword 0x881F0002
		opword 0x90610020
		lfd f5, double_to_int_mask_802c48e8@l(r4)
		opword 0xC8010020
		lfs f3, float_360_8041a308(r2)
		opword 0xEC402828
		lfs f1, float_0p0039062_8041a30c(r2)
		opword 0x90A10014
		lfs f0, float_60_8041a310(r2)
		opword 0xEC4300B2
		opword 0x90610010
		lfs f3, float_255_8041a304(r2)
		opword 0x9001001C
		opword 0xEC220072
		opword 0xC8810010
		opword 0x90610018
		opword 0xEC442828
		opword 0xEF810024
		opword 0xC8010018
		opword 0xEC002828
		opword 0xEF621824
		opword 0xEF401824
		opword 0xFC20E090
		bl floor
		opword 0xFC00081E
		lis r3, double_to_int_802c48f0@ha
		opword 0x3C004330
		lfd f1, double_to_int_802c48f0@l(r3)
		opword 0x90010030
		opword 0xD8010028
		opword 0x8081002C
		opword 0x6C838000
		opword 0x548007FF
		opword 0x90610034
		opword 0xC8010030
		opword 0xEC000828
		opword 0xEC5C0028
		opword 0x4082000C
		lfs f0, float_1_8041a2f4(r2)
		opword 0xEC401028
		lfs f0, float_1_8041a2f4(r2)
		opword 0x2C040003
		opword 0xEC20D828
		opword 0xEC1B00BC
		opword 0xEC3A0072
		opword 0xEC1A0032
		opword 0x41820060
		opword 0x4080001C
		opword 0x2C040001
		opword 0x41820034
		opword 0x40800040
		opword 0x2C040000
		opword 0x40800018
		opword 0x48000070
		opword 0x2C040005
		opword 0x4182005C
		opword 0x40800064
		opword 0x48000044
		opword 0xFFE0D090
		opword 0xFFC00090
		opword 0xFFA00890
		opword 0x48000050
		opword 0xFFE00090
		opword 0xFFC0D090
		opword 0xFFA00890
		opword 0x48000040
		opword 0xFFE00890
		opword 0xFFC0D090
		opword 0xFFA00090
		opword 0x48000030
		opword 0xFFE00890
		opword 0xFFC00090
		opword 0xFFA0D090
		opword 0x48000020
		opword 0xFFE00090
		opword 0xFFC00890
		opword 0xFFA0D090
		opword 0x48000010
		opword 0xFFE0D090
		opword 0xFFC00890
		opword 0xFFA00090
		lfs f0, float_255_8041a304(r2)
		opword 0x881F0003
		opword 0xEC4007F2
		opword 0xEC2007B2
		opword 0x9801000B
		opword 0xEC000772
		opword 0xFC40101E
		opword 0xFC20081E
		opword 0xFC00001E
		opword 0xD8410030
		opword 0xD8210028
		opword 0x80810034
		opword 0xD8010020
		opword 0x8061002C
		opword 0x80010024
		opword 0x98810008
		opword 0x98610009
		opword 0x9801000A
		opword 0x80610008
		opword 0xE3E10098
		opword 0xCBE10090
		opword 0xE3C10088
		opword 0xCBC10080
		opword 0xE3A10078
		opword 0xCBA10070
		opword 0xE3810068
		opword 0xCB810060
		opword 0xE3610058
		opword 0xCB610050
		opword 0xE3410048
		opword 0xCB410040
		opword 0x800100A4
		opword 0x83E1003C
		opword 0x7C0803A6
		opword 0x382100A0
#endif
	}
#ifdef NONMATCHING
	p = v * (1.0f - s);
	q = v * (1.0f - s * f);
	switch (i) {
		case 0: if (!v) {} r = v; g = q; b = p; break;
		case 1: r = q; g = v; b = p; break;
		case 2: r = p; g = v; b = q; break;
		case 3: r = p; g = q; b = v; break;
		case 4: r = q; g = p; b = v; break;
		case 5: r = v; g = p; b = q; break;
	}
	out.a = hsv.a;
	out.r = 255.0f * r;
	out.g = 255.0f * g;
	out.b = 255.0f * b;
	return out;
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void JUTFontSetup(u16 font) {
	u32 size;
	DVDEntry* dvd;
	BinaryFontBlock* ptr;
	char path[128];
	u32 i;

	if (!pfh) {
		sprintf(path, str_802C48F8, getMarioStDvdRoot(), fontname[font]);
		dvd = DVDMgrOpen(path, 2, 0);
		size = DVDMgrGetLength(dvd);
		pfh = __memAlloc(HEAP_DEFAULT, size = OSRoundUp32B(size));
		DVDMgrRead(dvd, pfh, size, 0);
		DVDMgrClose(dvd);
		ptr = (BinaryFontBlock*)(pfh + 1);
		for (i = 0; i < pfh->blockcount; i++) {
			switch (ptr->magic) {
				case 'INF1':
					pfi = (BinaryFontInfo*)ptr;
					break;
				case 'GLY1':
					blockGlyph = (BinaryFontGlyph*)ptr;
					break;
				case 'MAP1':
				case 'WID1':
				default:
					break;
			}
			ptr = (BinaryFontBlock*)((u32)ptr + ptr->size);
		}
		GXInitTexObj(&fgTexObj, &blockGlyph[1], blockGlyph->sheetwidth, blockGlyph->sheetheight,
			GX_TF_I4, GX_CLAMP, GX_CLAMP, GX_FALSE);
#ifdef NONMATCHING
		GXInitTexObjLOD(&fgTexObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
#endif
#ifndef NONMATCHING
		GXInitTexObjLOD(&fgTexObj, GX_LINEAR, GX_LINEAR, EXT_LIT(float_0_8041a300, 0.0f), EXT_LIT(float_0_8041a300, 0.0f), EXT_LIT(float_0_8041a300, 0.0f), GX_FALSE, GX_FALSE, GX_ANISO_1);
#endif
		fontGetWidth(JUTFont_CodeToGlyph(' '))->width = 7;
		fontGetWidth(JUTFont_CodeToGlyph(0x8140))->width = 9;
	}
}

void JUTFont_Free(void) {
	if (pfh) {
		__memFree(HEAP_DEFAULT, pfh);
		pfh = NULL;
	}
}

u16 JUTFont_CodeToGlyph(u32 code) {
	BinaryFontMap* map;
	u32 blockcount;
	u16 glyph, basecode;
	u8 sjis[2];
	u32 lead, index;
	s32 max, min;
	u32 i;

	map = (BinaryFontMap*)&pfh[1];
	glyph = pfi->replace;
	blockcount = pfh->blockcount;
	for (i = 0; i < blockcount; i++) {
		if (map->magic == 'MAP1') { //search for a correct mapping
			basecode = map->firstchar;
			if (((u16)code) >= basecode && ((u16)code) <= map->lastchar) {
				switch (map->mapping) {
					case LINEAR_CHARACTER_MAP:
						glyph = (u16)(code - basecode);
						break;

					case SJIS_CHARACTER_MAP:
						*(u16*)sjis = (u16)code;
						lead = sjis[0];
						index = sjis[1];
						if (sjis[1] >= 0x80) {
							index -= 65;
						}
						else {
							index -= 64;
						}

						if (!map->count) {
							glyph = (u16)((((lead - 136) * 188) + index) + 702);
						}
						else {
							glyph = (u16)(((lead - 136) * 188) + index - 94 + map->table[0]);
						}
					break;

					case TABLE_CHARACTER_MAP:
						glyph = map->table[(u16)code - basecode];
						break;

					case MAP_CHARACTER_MAP:
						max = map->count;
						min = 0;

						while (max >= min) {
							s32 index = (min + max) / 2;
							if ((u16)code == map->table[index * 2]) {
								glyph = map->table[2 * index + 1];
								break;
							}
							if ((u16)code < map->table[2 * index]) {
								max = index - 1;
							}
							else {
								min = index + 1;
							}
						}
					break;
				}
				break;
			}
		}
		map = (BinaryFontMap*)((u32)map + map->size);
	}
	return glyph;
}

void JUTFont_DrawStart(GXColor color) {
	CameraEntry* camera;
	Mtx mtx;

	camera = camGetCurPtr();
	__GXSetIndirectMask(0);
	GXSetCullMode(GX_CULL_NONE);
	GXSetZCompLoc(GX_TRUE);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, (GXLogicOp)7);
	GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX1, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_TEX_ST, GX_U8, 0);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
	GXSetNumChans(1);
	GXSetNumTexGens(1);
	GXSetTevColor(GX_TEVREG0, color);
	GXSetNumTevStages(1);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C0, (GXTevColorArg)0xC, GX_CC_ZERO);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
	GXLoadTexObj(&fgTexObj, GX_TEXMAP0);
#ifdef NONMATCHING
	PSMTXScale(mtx, 0.001953125f, 0.0009765625f, 1.0f);
#endif
#ifndef NONMATCHING
	PSMTXScale(mtx, EXT_LIT(float_0p0019531_8041a2f8, 0.001953125f), EXT_LIT(float_0p00097656_8041a2fc, 0.0009765625f), EXT_LIT(float_1_8041a2f4, 1.0f));
#endif
	GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
	GXLoadPosMtxImm(camera->view, 0);
	GXSetCurrentMtx(0);
#ifdef NONMATCHING
	GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0, 0, 0, 0});
#endif
#ifndef NONMATCHING
	GXSetFog(GX_FOG_NONE, EXT_LIT(float_0_8041a300, 0.0f), EXT_LIT(float_0_8041a300, 0.0f), EXT_LIT(float_0_8041a300, 0.0f), EXT_LIT(float_0_8041a300, 0.0f), (GXColor){0, 0, 0, 0});
#endif
}




#pragma opt_lifetimes off
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void _JUTFont_DrawPos(u16 code, s16 x, s16 y) {
#ifdef NONMATCHING
	s16 x0, y0, y1;
	s32 x1;
	GXColor hsv;
	s32 idx, cell, col, row;
	BinaryFontGlyph* glyph;
	f32 cellh, cellw, tu, w, h, tw;
	FontWidthEntry* entry;
	u16 rows;
	GXColor c;
	u16 u0, u1, v1;
	u16 v0;
	s16 x1s;
	u8 t0, t1;
	f32 tv;
	f32 scale;
	u8 n0, n1, hue, ew;
	u8 kern;
	s32 hr0, hr1;
	entry = fontGetWidth(code);
	kern = entry->kerning;
	glyph = blockGlyph;
	rows = glyph->sheetrows;
	row = (code - glyph->firstcode) / rows;
	col = (code - glyph->firstcode) % rows;
	row = row % glyph->sheetcolumns;
	cellh = glyph->cellheight;
	cellw = glyph->cellwidth;
	tu = col * cellw + kern;
	tw = entry->width;
	scale = 1.0f;
	w = entry->width * scale;
	h = cellh * scale;

	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	n0 = irand(64);
	n1 = irand(64);
	x0 = x + 0;
	y0 = y - 1;
	x1 = x0 + w;
	hue = x0 - (u8)gp->retraceCount * 2;
	hsv = (GXColor){0x00, 0xAA, 0xFF, 0xFF};
	tv = row * cellh;
	v0 = 1.0f + tv;
	GXPosition3s16(x, y0, 0);
	hr0 = x0 + hue;
	hsv.r = hr0;
	c = HSV2RGB(hsv);
	u0 = (s32)(tu);
	GXColor4u8(c.r, c.g, c.b, c.a);
	GXTexCoord2u16(u0, v0);
	GXTexCoord2u8(n0, n1);

	x1s = x1;
	hr1 = x1s + hue;
	GXPosition3s16(x1, y0, 0);
	hsv.r = hr1;
	c = HSV2RGB(hsv);
	u1 = (s32)(tu + tw);
	GXColor4u8(c.r, c.g, c.b, c.a);
	t0 = (s32)(n0 + w);
	GXTexCoord2u16(u1, v0);
	GXTexCoord2u8(t0, n1);

	y1 = (s32)(y0 - h);
	GXPosition3s16(x1s, y1, 0);
	hsv.r = hr1;
	c = HSV2RGB(hsv);
	GXColor4u8(c.r, c.g, c.b, c.a);
	v1 = (s32)(v0 + cellh);
	t1 = (s32)(n1 + h);
	GXTexCoord2u16(u1, v1);
	GXTexCoord2u8(t0, t1);

	GXPosition3s16(x0, y1, 0);
	hsv.r = hr0;
	c = HSV2RGB(hsv);
	GXColor4u8(c.r, c.g, c.b, c.a);
	GXTexCoord2u16(u0, v1);
	GXTexCoord2u8(n0, t1);
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FEC0
		opword 0x7C0802A6
		opword 0x90010144
		opword 0xDBE10130
		opword 0xF3E10138
		opword 0xDBC10120
		opword 0xF3C10128
		opword 0xDBA10110
		opword 0xF3A10118
		opword 0xDB810100
		opword 0xF3810108
		opword 0xDB6100F0
		opword 0xF36100F8
		opword 0xBEA100C4
		lwz r7, pfh(r13)
		opword 0x3CC05749
		opword 0x7C9A2378
		opword 0x7CB52B78
		opword 0x8007000C
		opword 0x39070020
		opword 0x38A64431
		opword 0x5464043E
		opword 0x7C0903A6
		opword 0x28000000
		opword 0x4081004C
		opword 0x80080000
		opword 0x7C002800
		opword 0x41820008
		opword 0x48000030
		opword 0xA0C80008
		opword 0x7C043040
		opword 0x41800024
		opword 0xA008000A
		opword 0x7C040040
		opword 0x41810018
		opword 0x7C062050
		opword 0x5404083C
		opword 0x38E4000C
		opword 0x7CE83A14
		opword 0x48000014
		opword 0x80080004
		opword 0x7D080214
		opword 0x4200FFBC
		opword 0x38E00000
		lwz r6, blockGlyph(r13)
		opword 0x3D204330
		opword 0x8AE70001
		opword 0x5460043E
		opword 0xA0A60008
		lis r4, double_to_int_mask_802c48e8@ha
		opword 0xA2C60016
		lis r3, double_to_int_802c48f0@ha
		opword 0x7D850050
		opword 0x88070000
		opword 0x7F2CB3D6
		addi r7, r3, double_to_int_802c48f0@l
		opword 0xA1660018
		opword 0x38600080
		opword 0xA0A6000E
		opword 0xA0C6000C
		opword 0x7D595BD6
		lfd f5, double_to_int_mask_802c48e8@l(r4)
		opword 0x90A10024
		opword 0x7F28CB78
		opword 0xC8470000
		opword 0x38800000
		opword 0x91210020
		opword 0x7CE8B1D6
		opword 0x38A00004
		opword 0x90C10034
		opword 0xC8010020
		opword 0x91210030
		opword 0x7CC76050
		opword 0x6CC68000
		opword 0xC8210030
		opword 0x90C1002C
		opword 0xEFE02828
		opword 0x7CCA59D6
		lfs f0, float_1_8041a2f4(r2)
		opword 0x91210028
		opword 0xEC612828
		opword 0xEF9F0032
		opword 0xC8210028
		opword 0x9001003C
		opword 0xEC811028
		opword 0x7F26C850
		opword 0x91210038
		opword 0xC8210038
		opword 0x92E1004C
		opword 0xEC412828
		opword 0x91210048
		opword 0xC8210048
		opword 0xEFC410FA
		opword 0x92E10044
		opword 0xEC212828
		opword 0x91210040
		opword 0xC8410040
		opword 0xEFA10032
		opword 0xEF622828
		bl GXBegin
		opword 0x38600040
		bl irand
		opword 0x5478063E
		opword 0x38600040
		bl irand
		opword 0x3CA04330
		opword 0x6F208000
		opword 0x90010064
		lis r6, double_to_int_802c48f0@ha
		opword 0x7F560734
		lfd f3, double_to_int_802c48f0@l(r6)
		opword 0x90A10060
		opword 0x6EC08000
		opword 0x38D5FFFF
		lwz r4, gp(r13)
		opword 0xC8010060
		opword 0x5477063E
		opword 0x90010054
		opword 0x7CDC0734
		opword 0xEC001828
		opword 0x8004001C
		opword 0x90A10050
		opword 0x3CA0CC01
		lfs f1, float_1_8041a2f4(r2)
		opword 0x54030DFC
		lwz r0, dat_8041a2f0(r2)
		opword 0xEC0007F2
		opword 0xC8410050
		opword 0x7C63B050
		opword 0xB3458000
		opword 0x5479063E
		opword 0xEC01002A
		opword 0xEC421828
		opword 0x9001001C
		opword 0x7F56CA14
		opword 0x38800000
		opword 0xFC00001E
		opword 0xEC22E82A
		opword 0xB0C58000
		opword 0x38610014
		opword 0xFC20081E
		opword 0x9B41001C
		opword 0xD8010068
		opword 0x8001001C
		opword 0xD8210058
		opword 0x82A1006C
		opword 0xB0858000
		opword 0x8361005C
		opword 0x90010014
		bl HSV2RGB
		opword 0x90610018
		opword 0xFC00F01E
		opword 0x7F7E0734
		opword 0x3CC0CC01
		opword 0x88810018
		opword 0x7FBECA14
		opword 0x88610019
		opword 0x98868000
		opword 0x38000000
		opword 0x8881001A
		opword 0x56BF043E
		opword 0x98668000
		opword 0x38610010
		opword 0x88A1001B
		opword 0x98868000
		opword 0xD8010070
		opword 0x80810074
		opword 0x98A68000
		opword 0x5499043E
		opword 0xB0868000
		opword 0xB2A68000
		opword 0x9B068000
		opword 0x9AE68000
		opword 0xB3668000
		opword 0xB3868000
		opword 0x9BA1001C
		opword 0xB0068000
		opword 0x8001001C
		opword 0x90010010
		bl HSV2RGB
		opword 0x3CA04330
		opword 0x90610018
		lis r3, double_to_int_mask_802c48e8@ha
		opword 0xEC5ED82A
		opword 0x93010084
		opword 0x3D20CC01
		lfd f1, double_to_int_mask_802c48e8@l(r3)
		opword 0x6F838000
		opword 0x90A10080
		opword 0x88010018
		opword 0xFC40101E
		opword 0xC8010080
		lis r4, double_to_int_802c48f0@ha
		opword 0x98098000
		opword 0x38000000
		opword 0xEC000828
		opword 0x89010019
		opword 0x90610094
		opword 0x3861000C
		opword 0xEC00E82A
		opword 0x88E1001A
		opword 0xD8410078
		lfd f1, double_to_int_802c48f0@l(r4)
		opword 0x90A10090
		opword 0xFC40001E
		opword 0x80C1007C
		opword 0x99098000
		opword 0xC8010090
		opword 0x54DC043E
		opword 0xD8410088
		opword 0xEC000828
		opword 0x88A1001B
		opword 0x98E98000
		opword 0x8081008C
		opword 0x98A98000
		opword 0xEC00E028
		opword 0x549B063E
		opword 0xB0C98000
		opword 0xFC00001E
		opword 0xB3E98000
		opword 0x98898000
		opword 0x9AE98000
		opword 0xD8010098
		opword 0x8081009C
		opword 0xB3C98000
		opword 0x7C9E0734
		opword 0xB0898000
		opword 0x9BA1001C
		opword 0xB0098000
		opword 0x8001001C
		opword 0x9001000C
		bl HSV2RGB
		opword 0x3C804330
		opword 0x7FE0FB78
		opword 0x900100A4
		lis r5, double_to_int_mask_802c48e8@ha
		lfd f2, double_to_int_mask_802c48e8@l(r5)
		opword 0x3CE0CC01
		opword 0x908100A0
		opword 0x38000000
		opword 0x90610018
		opword 0x38610008
		opword 0xC80100A0
		opword 0x908100B0
		opword 0xEC001028
		opword 0x89010018
		opword 0x92E100B4
		opword 0x88C10019
		opword 0xEC20F82A
		opword 0xC80100B0
		opword 0x99078000
		opword 0xEC001028
		opword 0x88A1001A
		opword 0x98C78000
		opword 0xFC20081E
		opword 0x8881001B
		opword 0x98A78000
		opword 0xEC00E02A
		opword 0x98878000
		opword 0xD82100A8
		opword 0xFC00001E
		opword 0x808100AC
		opword 0xB3878000
		opword 0x5495043E
		opword 0xB0878000
		opword 0xD80100B8
		opword 0x808100BC
		opword 0x9B678000
		opword 0x5497063E
		opword 0x98878000
		opword 0xB2C78000
		opword 0xB3C78000
		opword 0x9B41001C
		opword 0xB0078000
		opword 0x8001001C
		opword 0x90010008
		bl HSV2RGB
		opword 0x90610018
		opword 0x3C80CC01
		opword 0x88610018
		opword 0x88010019
		opword 0x98648000
		opword 0x8861001A
		opword 0x98048000
		opword 0x8801001B
		opword 0x98648000
		opword 0x98048000
		opword 0xB3248000
		opword 0xB2A48000
		opword 0x9B048000
		opword 0x9AE48000
		opword 0xE3E10138
		opword 0xCBE10130
		opword 0xE3C10128
		opword 0xCBC10120
		opword 0xE3A10118
		opword 0xCBA10110
		opword 0xE3810108
		opword 0xCB810100
		opword 0xE36100F8
		opword 0xCB6100F0
		opword 0xBAA100C4
		opword 0x80010144
		opword 0x7C0803A6
		opword 0x38210140
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#pragma opt_lifetimes reset
#pragma opt_common_subs reset


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".sdata") u32 gap_07_8041036C_sdata[1] = {0};
#ifndef NONMATCHING

// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".sdata2") const u32 dat_8041a2e8 = 0xE00000FF;
__declspec(section ".sdata2") const u32 dat_8041a2ec = 0xE00000FF;
__declspec(section ".sdata2") const u32 dat_8041a2f0 = 0x00AAFFFF;
__declspec(section ".sdata2") const f32 float_1_8041a2f4 = 1.0f;
__declspec(section ".sdata2") const f32 float_0p0019531_8041a2f8 = 0.001953125f;
__declspec(section ".sdata2") const f32 float_0p00097656_8041a2fc = 0.0009765625f;
__declspec(section ".sdata2") const f32 float_0_8041a300 = 0.0f;
__declspec(section ".sdata2") const f32 float_255_8041a304 = 255.0f;
__declspec(section ".sdata2") const f32 float_360_8041a308 = 360.0f;
__declspec(section ".sdata2") const f32 float_0p0039062_8041a30c = 0.00390625f;
__declspec(section ".sdata2") const f32 float_60_8041a310 = 60.0f;
__declspec(section ".sdata2") const char str_8041A314[8] = "icon\0\0\0";
__declspec(section ".sdata2") const char str_8041A31C[4] = "red";
__declspec(section ".sdata2") const char str_8041A320[8] = "/red\0\0\0";
__declspec(section ".sdata2") const f32 float_0p5_8041a328 = 0.5f;
__declspec(section ".sdata2") const char str_8041A32C[4] = "col";
__declspec(section ".sdata2") const char str_8041A330[4] = "%x\0";
__declspec(section ".sdata2") const char str_8041A334[8] = "/col\0\0\0";
__declspec(section ".sdata2") const f32 float_28_8041a33c = 28.0f;
__declspec(section ".sdata2") const f32 float_0p015625_8041a340 = 0.015625f;
#endif
__declspec(section ".sdata2") const u32 gap_09_8041A344_sdata2[1] = {0};
