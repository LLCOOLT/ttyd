// FAKE: whole unit as G5 asm stopgap (force_active + fixbase); C under #ifdef NONMATCHING.
#include "manager/fontmgr.h"
#include "manager/dvdmgr.h"
#include "driver/camdrv.h"
#include "driver/msgdrv.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
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
GXColor fontColTbl[3] = {
	{0x1E, 0x14, 0x14, 0xFF},
	{0xDC, 0xDC, 0xDC, 0xFF},
	{0xB4, 0x78, 0x14, 0xFF}
};
s32 charspace[2] = {4, 2};
const char* fontname[2] = {str_802C48A0, str_802C48B4};

//.sbss
#ifndef NONMATCHING
__declspec(section ".sdata") u32 gap_08_8041879C_sbss[1]; // FAKE: .sbss pad after fontScale (reverse emit order)
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

#ifdef NONMATCHING
void fontmgrInit(void) {
	; //stubbed in retail
}
#endif

#ifdef NONMATCHING
void fontmgrTexSetup(void) {
	JUTFontSetup(0);
}
#endif

#ifdef NONMATCHING
void FontDrawStart(void) {
	FontDrawStart_alpha(0xFF);
}
#endif

#ifdef NONMATCHING
void FontDrawStart_alpha(u8 alpha) {
	GXColor start;

	fontColor = start = fontColTbl[0];
	fontAlpha = alpha;
	start.a = (start.a * alpha) / 255;
	fontScale = (Vec){1.0f, 1.0f, 1.0f};
	fontEdge = FALSE;
	JUTFont_DrawStart(start);
}
#endif

#ifdef NONMATCHING
void FontDrawEdge(void) {
	fontEdge = TRUE;
}
#endif

#ifdef NONMATCHING
void FontDrawEdgeOff(void) {
	fontEdge = FALSE;
}
#endif

#ifdef NONMATCHING
void FontDrawRainbowColor(void) {
	GXSetNumTevStages(2);
	GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
	GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
}
#endif

#ifdef NONMATCHING
void FontDrawRainbowColorOff(void) {
	GXSetNumTevStages(1);
}
#endif

#ifdef NONMATCHING
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
	PSMTXScale(mtx, 0.015625f, 0.015625f, 1.0f);
	GXLoadTexMtxImm(mtx, GX_TEXMTX1, GX_MTX2x4);
	GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
}
#endif

#ifdef NONMATCHING
void FontDrawNoiseOff(void) {
	GXSetNumTexGens(1);
	GXSetNumTevStages(1);
}
#endif

#ifdef NONMATCHING
void FontDrawColorIDX(s32 idx) {
	FontDrawColor(fontColTbl[idx]);
}
#endif

#ifdef NONMATCHING
void FontDrawColor(GXColor color) {
	fontColor = color;
	color.a = (color.a * fontAlpha) / 255;
	GXSetTevColor(GX_TEVREG0, color);
}
#endif

#ifdef NONMATCHING
void FontDrawColor_(void) {
	FontDrawColor(fontColor);
}
#endif

#ifdef NONMATCHING
GXColor FontGetDrawColor(void) {
	return fontColor;
}
#endif

#ifdef NONMATCHING
void FontDrawScale(f32 scale) {
	fontScale.x = scale;
	fontScale.y = scale;
	fontScale.z = scale;
}
#endif

#ifdef NONMATCHING
void FontDrawScaleVec(Vec scale) {
	fontScale = scale;
}
#endif

#ifdef NONMATCHING
void FontDrawCode(f32 x, f32 y, u16 code) {
	Mtx mtx;

	PSMTXScale(mtx, fontScale.x, fontScale.y, fontScale.z);
	PSMTXTransApply(mtx, mtx, x, y, 0.0f);
	PSMTXConcat(camGetCurPtr()->view, mtx, mtx);
	GXLoadPosMtxImm(mtx, 0);
	GXSetCurrentMtx(0);
	fontDrawCodeEdge(code);
}
#endif

#ifdef NONMATCHING
void FontDrawCodeMtx(Mtx mtx, u16 code) {
	PSMTXConcat(camGetCurPtr()->view, mtx, mtx);
	GXLoadPosMtxImm(mtx, 0);
	GXSetCurrentMtx(0);
	fontDrawCodeEdge(code);
}
#endif

static inline void FontDrawStringVec(Vec pos, const s8* str) {
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
		PSMTXTransApply(scale, trans, x, pos.y, pos.z);
		PSMTXConcat(camera->view, trans, trans);
		GXLoadPosMtxImm(trans, 0);
		fontDrawCodeEdge(code);
		x += fontScale.x * (width + charspace[gp->language]);
	}
}

#ifdef NONMATCHING
void FontDrawString(f32 x, f32 y, const char* msg) {
	FontDrawStringVec((Vec){x, y, 0.0f}, (const s8*)msg);
}
#endif

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
	}
}

#ifdef NONMATCHING
void FontDrawStringPitch(f32 x, f32 y, f32 pitch, const char* msg) {
	fontDrawStringVecPitch((Vec){x, y, 0.0f}, pitch, (const s8*)msg);
}
#endif

#ifdef NONMATCHING
void FontDrawStringVecPitch(Vec pos, f32 pitch, const s8* msg) {
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
	}
}
#endif
extern char* msgGetCommand(char* msg, char* cmd, char* arg);
static inline void fontDrawPairXI(u16 code, s16 x, s16 y) {
	s16 iy = y;
	s16 ix = x;
	_JUTFont_DrawPos(code, ix - 2, (s16)iy);
	_JUTFont_DrawPos(code, ix + 2, (s16)iy);
}

static inline void fontDrawPairYI(u16 code, s16 x, s16 y) {
	s16 iy = y;
	s16 ix = x;
	_JUTFont_DrawPos(code, ix, iy - 2);
	_JUTFont_DrawPos(code, ix, iy + 2);
}

static inline void fontDrawPairX(u16 code, f32 x, f32 y) {
	s16 ix = x;
	s16 iy = y;
	_JUTFont_DrawPos(code, ix - 2, (s16)iy);
	_JUTFont_DrawPos(code, ix + 2, (s16)iy);
}

static inline void fontDrawPairY(u16 code, f32 x, f32 y) {
	s16 ix = x;
	s16 iy = y;
	_JUTFont_DrawPos(code, (s16)ix, iy - 2);
	_JUTFont_DrawPos(code, (s16)ix, iy + 2);
}

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

#ifdef NONMATCHING
void FontDrawStringMtx(Mtx mtx, const char* msg) {
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
	}
}
#endif


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

#ifdef NONMATCHING
void FontDrawStringCenterMtx(Mtx mtx, const s8* msg) {
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
	}
}
#endif

inline u8 fontGetGlyphWidth(u16 code) {
	return fontGetWidth(code)->width;
}

#ifdef NONMATCHING
void FontDrawStringShake(f32 x, f32 y, const s8* msg) {
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
	}
}
#endif
extern int strcmp(const char* a, const char* b);
extern int sscanf(const char* s, const char* format, ...);
extern s32 msgIconStr2ID(const char* str);
extern void iconGetWidthHight(u16* width, u16* height, u16 id);
extern void iconDispGxAlpha(Vec* position, s16 flags, u16 iconId, u8 alpha, f32 scale);

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

#ifdef NONMATCHING
void FontDrawMessage(s32 x, s32 y, const char* msg) {
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
	}
}
#endif


#ifdef NONMATCHING
void FontDrawMessageMtx(Mtx mtx, const char* msg) {
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
	}
}
#endif

#ifdef NONMATCHING
void hankakuSearch(s8 c) {
	JUTFont_CodeToGlyph(c);
}
#endif

#ifdef NONMATCHING
u16 kanjiSearch(u32 code) {
	return JUTFont_CodeToGlyph(code);
}
#endif

#ifdef NONMATCHING
u16 kanjiGetWidth(u16 code) {
	return fontGetWidth(code)->width;
}
#endif


#ifdef NONMATCHING
u16 FontGetMessageWidthLine(const char* msg, u16* lines) {
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
	}
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
}
#endif

#ifdef NONMATCHING
u16 FontGetMessageWidth(const char* message) {
	return FontGetMessageWidthLine(message, NULL);
}
#endif

#ifdef NONMATCHING
GXColor HSV2RGB(GXColor hsv) {
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
	}
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
}
#endif

#ifdef NONMATCHING
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
		GXInitTexObjLOD(&fgTexObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
		fontGetWidth(JUTFont_CodeToGlyph(' '))->width = 7;
		fontGetWidth(JUTFont_CodeToGlyph(0x8140))->width = 9;
	}
}
#endif

#ifdef NONMATCHING
void JUTFont_Free(void) {
	if (pfh) {
		__memFree(HEAP_DEFAULT, pfh);
		pfh = NULL;
	}
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
	PSMTXScale(mtx, 0.001953125f, 0.0009765625f, 1.0f);
	GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
	GXLoadPosMtxImm(camera->view, 0);
	GXSetCurrentMtx(0);
	GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0, 0, 0, 0});
}
#endif




#pragma opt_lifetimes off
#ifdef NONMATCHING
void _JUTFont_DrawPos(u16 code, s16 x, s16 y) {
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
}
#endif

#pragma opt_lifetimes reset
#pragma opt_common_subs reset

#ifndef NONMATCHING
// ASM-STOPGAP: fontmgrInit (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
#pragma force_active on // FAKE: keep asm-only-referenced data from being dead-stripped
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

__declspec(section ".sdata2") u32 gap_10_80422FDC_sbss2[1]; // FAKE: .sbss2 pad after unk_80422fd8 (reverse emit order)
__declspec(section ".sdata2") const u32 unk_80422fd8;
void DVDMgrClose(DVDEntry* entry);
u32 DVDMgrGetLength(DVDEntry* entry);
DVDEntry* DVDMgrOpen(const char* path, u8 priority, u16 unknown);
s32 DVDMgrRead(DVDEntry* entry, void* address, u32 size, s32 offset);
u16 FontGetMessageWidthLine(const char* msg, u16* lines);
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
void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color);
void GXSetNumChans(u8 nChans);
void GXSetNumTevStages(u8 nStages);
void GXSetNumTexGens(u8 nTexGens);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColor(GXTevRegID id, GXColor color);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel sel);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx);
void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac);
void GXSetVtxDesc(GXAttr attr, GXAttrType type);
void GXSetZCompLoc(GXBool before_tex);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void PSMTXTransApply(const Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
void __GXSetIndirectMask(u32 mask);
void* __memAlloc(HEAP_TYPE heap, u32 size);
void __memFree(HEAP_TYPE heap, void* ptr);
BOOL _ismbblead(u32 a1);
CameraEntry* camGetCurPtr(void);
const char* getMarioStDvdRoot(void);
s32 irand(s32 scalar);
asm void _JUTFont_DrawPos(u16 code, s16 x, s16 y) {
	nofralloc
	stwu r1, -0x140(r1)
	mflr r0
	stw r0, 0x144(r1)
	stfd f31, 0x130(r1)
	psq_st f31, 0x138(r1), 0, 0
	stfd f30, 0x120(r1)
	psq_st f30, 0x128(r1), 0, 0
	stfd f29, 0x110(r1)
	psq_st f29, 0x118(r1), 0, 0
	stfd f28, 0x100(r1)
	psq_st f28, 0x108(r1), 0, 0
	stfd f27, 0xf0(r1)
	psq_st f27, 0xf8(r1), 0, 0
	stmw r21, 0xc4(r1)
	lwz r7, pfh(r13)
	lis r6, 0x5749
	mr r26, r4
	mr r21, r5
	lwz r0, 0xc(r7)
	addi r8, r7, 0x20
	addi r5, r6, 0x4431
	clrlwi r4, r3, 16
	mtctr r0
	cmplwi r0, 0x0
	ble @1
	@2:
	lwz r0, 0x0(r8)
	cmpw r0, r5
	beq @3
	b @4
	@3:
	lhz r6, 0x8(r8)
	cmplw r4, r6
	blt @4
	lhz r0, 0xa(r8)
	cmplw r4, r0
	bgt @4
	subf r0, r6, r4
	slwi r4, r0, 1
	addi r7, r4, 0xc
	add r7, r8, r7
	b @5
	@4:
	lwz r0, 0x4(r8)
	add r8, r8, r0
	bdnz @2
	@1:
	li r7, 0x0
	@5:
	lwz r6, blockGlyph(r13)
	lis r9, 0x4330
	lbz r23, 0x1(r7)
	clrlwi r0, r3, 16
	lhz r5, 0x8(r6)
	lis r4, double_to_int_mask_802c48e8@ha
	lhz r22, 0x16(r6)
	lis r3, double_to_int_802c48f0@ha
	subf r12, r5, r0
	lbz r0, 0x0(r7)
	divw r25, r12, r22
	addi r7, r3, double_to_int_802c48f0@l
	lhz r11, 0x18(r6)
	li r3, 0x80
	lhz r5, 0xe(r6)
	lhz r6, 0xc(r6)
	divw r10, r25, r11
	lfd f5, double_to_int_mask_802c48e8@l(r4)
	stw r5, 0x24(r1)
	mr r8, r25
	lfd f2, 0x0(r7)
	li r4, 0x0
	stw r9, 0x20(r1)
	mullw r7, r8, r22
	li r5, 0x4
	stw r6, 0x34(r1)
	lfd f0, 0x20(r1)
	stw r9, 0x30(r1)
	subf r6, r7, r12
	xoris r6, r6, 0x8000
	lfd f1, 0x30(r1)
	stw r6, 0x2c(r1)
	fsubs f31, f0, f5
	mullw r6, r10, r11
	lfs f0, float_1_8041a2f4(r2)
	stw r9, 0x28(r1)
	fsubs f3, f1, f5
	fmuls f28, f31, f0
	lfd f1, 0x28(r1)
	stw r0, 0x3c(r1)
	fsubs f4, f1, f2
	subf r25, r6, r25
	stw r9, 0x38(r1)
	lfd f1, 0x38(r1)
	stw r23, 0x4c(r1)
	fsubs f2, f1, f5
	stw r9, 0x48(r1)
	lfd f1, 0x48(r1)
	fmadds f30, f4, f3, f2
	stw r23, 0x44(r1)
	fsubs f1, f1, f5
	stw r9, 0x40(r1)
	lfd f2, 0x40(r1)
	fmuls f29, f1, f0
	fsubs f27, f2, f5
	bl GXBegin
	li r3, 0x40
	bl irand
	clrlwi r24, r3, 24
	li r3, 0x40
	bl irand
	lis r5, 0x4330
	xoris r0, r25, 0x8000
	stw r0, 0x64(r1)
	lis r6, double_to_int_802c48f0@ha
	extsh r22, r26
	lfd f3, double_to_int_802c48f0@l(r6)
	stw r5, 0x60(r1)
	xoris r0, r22, 0x8000
	subi r6, r21, 0x1
	lwz r4, gp(r13)
	lfd f0, 0x60(r1)
	clrlwi r23, r3, 24
	stw r0, 0x54(r1)
	extsh r28, r6
	fsubs f0, f0, f3
	lwz r0, 0x1c(r4)
	stw r5, 0x50(r1)
	lis r5, 0xcc01
	lfs f1, float_1_8041a2f4(r2)
	clrlslwi r3, r0, 24, 1
	lwz r0, dat_8041a2f0(r2)
	fmuls f0, f0, f31
	lfd f2, 0x50(r1)
	subf r3, r3, r22
	sth r26, -0x8000(r5)
	clrlwi r25, r3, 24
	fadds f0, f1, f0
	fsubs f2, f2, f3
	stw r0, 0x1c(r1)
	add r26, r22, r25
	li r4, 0x0
	fctiwz f0, f0
	fadds f1, f2, f29
	sth r6, -0x8000(r5)
	addi r3, r1, 0x14
	fctiwz f1, f1
	stb r26, 0x1c(r1)
	stfd f0, 0x68(r1)
	lwz r0, 0x1c(r1)
	stfd f1, 0x58(r1)
	lwz r21, 0x6c(r1)
	sth r4, -0x8000(r5)
	lwz r27, 0x5c(r1)
	stw r0, 0x14(r1)
	bl HSV2RGB
	stw r3, 0x18(r1)
	fctiwz f0, f30
	extsh r30, r27
	lis r6, 0xcc01
	lbz r4, 0x18(r1)
	add r29, r30, r25
	lbz r3, 0x19(r1)
	stb r4, -0x8000(r6)
	li r0, 0x0
	lbz r4, 0x1a(r1)
	clrlwi r31, r21, 16
	stb r3, -0x8000(r6)
	addi r3, r1, 0x10
	lbz r5, 0x1b(r1)
	stb r4, -0x8000(r6)
	stfd f0, 0x70(r1)
	lwz r4, 0x74(r1)
	stb r5, -0x8000(r6)
	clrlwi r25, r4, 16
	sth r4, -0x8000(r6)
	sth r21, -0x8000(r6)
	stb r24, -0x8000(r6)
	stb r23, -0x8000(r6)
	sth r27, -0x8000(r6)
	sth r28, -0x8000(r6)
	stb r29, 0x1c(r1)
	sth r0, -0x8000(r6)
	lwz r0, 0x1c(r1)
	stw r0, 0x10(r1)
	bl HSV2RGB
	lis r5, 0x4330
	stw r3, 0x18(r1)
	lis r3, double_to_int_mask_802c48e8@ha
	fadds f2, f30, f27
	stw r24, 0x84(r1)
	lis r9, 0xcc01
	lfd f1, double_to_int_mask_802c48e8@l(r3)
	xoris r3, r28, 0x8000
	stw r5, 0x80(r1)
	lbz r0, 0x18(r1)
	fctiwz f2, f2
	lfd f0, 0x80(r1)
	lis r4, double_to_int_802c48f0@ha
	stb r0, -0x8000(r9)
	li r0, 0x0
	fsubs f0, f0, f1
	lbz r8, 0x19(r1)
	stw r3, 0x94(r1)
	addi r3, r1, 0xc
	fadds f0, f0, f29
	lbz r7, 0x1a(r1)
	stfd f2, 0x78(r1)
	lfd f1, double_to_int_802c48f0@l(r4)
	stw r5, 0x90(r1)
	fctiwz f2, f0
	lwz r6, 0x7c(r1)
	stb r8, -0x8000(r9)
	lfd f0, 0x90(r1)
	clrlwi r28, r6, 16
	stfd f2, 0x88(r1)
	fsubs f0, f0, f1
	lbz r5, 0x1b(r1)
	stb r7, -0x8000(r9)
	lwz r4, 0x8c(r1)
	stb r5, -0x8000(r9)
	fsubs f0, f0, f28
	clrlwi r27, r4, 24
	sth r6, -0x8000(r9)
	fctiwz f0, f0
	sth r31, -0x8000(r9)
	stb r4, -0x8000(r9)
	stb r23, -0x8000(r9)
	stfd f0, 0x98(r1)
	lwz r4, 0x9c(r1)
	sth r30, -0x8000(r9)
	extsh r30, r4
	sth r4, -0x8000(r9)
	stb r29, 0x1c(r1)
	sth r0, -0x8000(r9)
	lwz r0, 0x1c(r1)
	stw r0, 0xc(r1)
	bl HSV2RGB
	lis r4, 0x4330
	mr r0, r31
	stw r0, 0xa4(r1)
	lis r5, double_to_int_mask_802c48e8@ha
	lfd f2, double_to_int_mask_802c48e8@l(r5)
	lis r7, 0xcc01
	stw r4, 0xa0(r1)
	li r0, 0x0
	stw r3, 0x18(r1)
	addi r3, r1, 0x8
	lfd f0, 0xa0(r1)
	stw r4, 0xb0(r1)
	fsubs f0, f0, f2
	lbz r8, 0x18(r1)
	stw r23, 0xb4(r1)
	lbz r6, 0x19(r1)
	fadds f1, f0, f31
	lfd f0, 0xb0(r1)
	stb r8, -0x8000(r7)
	fsubs f0, f0, f2
	lbz r5, 0x1a(r1)
	stb r6, -0x8000(r7)
	fctiwz f1, f1
	lbz r4, 0x1b(r1)
	stb r5, -0x8000(r7)
	fadds f0, f0, f28
	stb r4, -0x8000(r7)
	stfd f1, 0xa8(r1)
	fctiwz f0, f0
	lwz r4, 0xac(r1)
	sth r28, -0x8000(r7)
	clrlwi r21, r4, 16
	sth r4, -0x8000(r7)
	stfd f0, 0xb8(r1)
	lwz r4, 0xbc(r1)
	stb r27, -0x8000(r7)
	clrlwi r23, r4, 24
	stb r4, -0x8000(r7)
	sth r22, -0x8000(r7)
	sth r30, -0x8000(r7)
	stb r26, 0x1c(r1)
	sth r0, -0x8000(r7)
	lwz r0, 0x1c(r1)
	stw r0, 0x8(r1)
	bl HSV2RGB
	stw r3, 0x18(r1)
	lis r4, 0xcc01
	lbz r3, 0x18(r1)
	lbz r0, 0x19(r1)
	stb r3, -0x8000(r4)
	lbz r3, 0x1a(r1)
	stb r0, -0x8000(r4)
	lbz r0, 0x1b(r1)
	stb r3, -0x8000(r4)
	stb r0, -0x8000(r4)
	sth r25, -0x8000(r4)
	sth r21, -0x8000(r4)
	stb r24, -0x8000(r4)
	stb r23, -0x8000(r4)
	psq_l f31, 0x138(r1), 0, 0
	lfd f31, 0x130(r1)
	psq_l f30, 0x128(r1), 0, 0
	lfd f30, 0x120(r1)
	psq_l f29, 0x118(r1), 0, 0
	lfd f29, 0x110(r1)
	psq_l f28, 0x108(r1), 0, 0
	lfd f28, 0x100(r1)
	psq_l f27, 0xf8(r1), 0, 0
	lfd f27, 0xf0(r1)
	lmw r21, 0xc4(r1)
	lwz r0, 0x144(r1)
	mtlr r0
	addi r1, r1, 0x140
	blr
}

asm void JUTFont_DrawStart(GXColor color) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stw r31, 0x4c(r1)
	stw r30, 0x48(r1)
	mr r30, r3
	bl camGetCurPtr
	mr r31, r3
	li r3, 0x0
	bl __GXSetIndirectMask
	li r3, 0x0
	bl GXSetCullMode
	li r3, 0x1
	bl GXSetZCompLoc
	li r3, 0x7
	li r4, 0x0
	li r5, 0x0
	li r6, 0x7
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x1
	li r4, 0x4
	li r5, 0x5
	li r6, 0x7
	bl GXSetBlendMode
	li r3, 0x1
	li r4, 0x7
	li r5, 0x0
	bl GXSetZMode
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xb
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xd
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xe
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x3
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xb
	li r5, 0x1
	li r6, 0x5
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x2
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xe
	li r5, 0x1
	li r6, 0x0
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x4
	li r4, 0x0
	li r5, 0x1
	li r6, 0x1
	li r7, 0x0
	li r8, 0x0
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x1
	bl GXSetNumChans
	li r3, 0x1
	bl GXSetNumTexGens
	lwz r0, 0x0(r30)
	addi r4, r1, 0xc
	li r3, 0x1
	stw r0, 0xc(r1)
	bl GXSetTevColor
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
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
	li r5, 0x2
	li r6, 0xc
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x1
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	la r3, fgTexObj(r13)
	li r4, 0x0
	bl GXLoadTexObj
	lfs f1, float_0p0019531_8041a2f8(r2)
	addi r3, r1, 0x10
	lfs f2, float_0p00097656_8041a2fc(r2)
	lfs f3, float_1_8041a2f4(r2)
	bl PSMTXScale
	addi r3, r1, 0x10
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x1e
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	addi r3, r31, 0x11c
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	lfs f1, float_0_8041a300(r2)
	addi r4, r1, 0x8
	lwz r0, unk_80422fd8(r2)
	li r3, 0x0
	fmr f2, f1
	fmr f3, f1
	stw r0, 0x8(r1)
	fmr f4, f1
	bl GXSetFog
	lwz r0, 0x54(r1)
	lwz r31, 0x4c(r1)
	lwz r30, 0x48(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm u16 JUTFont_CodeToGlyph(u32 code) {
	nofralloc
	stwu r1, -0x10(r1)
	clrlwi r4, r3, 16
	lwz r6, pfh(r13)
	lwz r5, pfi(r13)
	lwz r0, 0xc(r6)
	addi r6, r6, 0x20
	lhz r7, 0x12(r5)
	mtctr r0
	cmplwi r0, 0x0
	ble @1
	@2:
	lwz r5, 0x0(r6)
	subis r0, r5, 0x4d41
	cmplwi r0, 0x5031
	bne @3
	lhz r5, 0xa(r6)
	cmplw r4, r5
	blt @3
	lhz r0, 0xc(r6)
	cmplw r4, r0
	bgt @3
	lhz r0, 0x8(r6)
	cmpwi r0, 0x2
	beq @4
	bge @5
	cmpwi r0, 0x0
	beq @6
	bge @7
	b @1
	@5:
	cmpwi r0, 0x4
	bge @1
	b @8
	@6:
	subf r0, r5, r3
	clrlwi r7, r0, 16
	b @1
	@7:
	sth r3, 0x8(r1)
	lbz r3, 0x9(r1)
	lbz r4, 0x8(r1)
	cmplwi r3, 0x80
	blt @9
	subi r5, r3, 0x41
	b @10
	@9:
	subi r5, r3, 0x40
	@10:
	lhz r0, 0xe(r6)
	cmplwi r0, 0x0
	bne @11
	subi r0, r4, 0x88
	mulli r3, r0, 0xbc
	addi r0, r3, 0x2be
	add r0, r5, r0
	clrlwi r7, r0, 16
	b @1
	@11:
	subi r0, r4, 0x88
	lhz r4, 0x10(r6)
	mulli r3, r0, 0xbc
	subi r0, r3, 0x5e
	add r0, r0, r4
	add r0, r5, r0
	clrlwi r7, r0, 16
	b @1
	@4:
	subf r0, r5, r4
	slwi r0, r0, 1
	add r3, r6, r0
	lhz r7, 0x10(r3)
	b @1
	@8:
	lhz r5, 0xe(r6)
	clrlwi r3, r3, 16
	li r8, 0x0
	b @12
	@13:
	add r4, r8, r5
	srwi r0, r4, 31
	add r0, r0, r4
	srawi r9, r0, 1
	slwi r4, r9, 2
	addi r0, r4, 0x10
	lhzx r0, r6, r0
	cmplw r3, r0
	bne @14
	add r3, r6, r4
	lhz r7, 0x12(r3)
	b @1
	@14:
	bge @15
	subi r5, r9, 0x1
	b @12
	@15:
	addi r8, r9, 0x1
	@12:
	cmpw r5, r8
	bge @13
	b @1
	@3:
	lwz r0, 0x4(r6)
	add r6, r6, r0
	bdnz @2
	@1:
	mr r3, r7
	addi r1, r1, 0x10
	blr
}

asm void JUTFont_Free(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, pfh(r13)
	cmplwi r4, 0x0
	beq @1
	li r3, 0x0
	bl __memFree
	li r0, 0x0
	stw r0, pfh(r13)
	@1:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void JUTFontSetup(u16 font) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	stw r0, 0x94(r1)
	stw r31, 0x8c(r1)
	stw r30, 0x88(r1)
	mr r30, r3
	lwz r0, pfh(r13)
	cmplwi r0, 0x0
	bne @1
	bl getMarioStDvdRoot
	clrlslwi r0, r30, 16, 2
	la r5, fontname(r13)
	lis r4, str_802C48F8@ha
	lwzx r6, r5, r0
	mr r5, r3
	addi r3, r1, 0x8
	addi r4, r4, str_802C48F8@l
	crclr 6
	bl sprintf
	addi r3, r1, 0x8
	li r4, 0x2
	li r5, 0x0
	bl DVDMgrOpen
	mr r30, r3
	bl DVDMgrGetLength
	mr r4, r3
	li r3, 0x0
	addi r0, r4, 0x1f
	clrrwi r31, r0, 5
	mr r4, r31
	bl __memAlloc
	mr r4, r3
	mr r3, r30
	stw r4, pfh(r13)
	mr r5, r31
	li r6, 0x0
	bl DVDMgrRead
	mr r3, r30
	bl DVDMgrClose
	lwz r6, pfh(r13)
	lis r3, 0x4d41
	addi r4, r3, 0x5031
	li r8, 0x0
	addi r7, r6, 0x20
	b @2
	@3:
	lwz r5, 0x0(r7)
	cmpw r5, r4
	beq @4
	bge @5
	lis r3, 0x494e
	addi r0, r3, 0x4631
	cmpw r5, r0
	beq @6
	bge @4
	lis r3, 0x474c
	addi r0, r3, 0x5931
	cmpw r5, r0
	beq @7
	b @4
	@5:
	lis r3, 0x5749
	addi r0, r3, 0x4431
	cmpw r5, r0
	beq @4
	b @4
	@6:
	stw r7, pfi(r13)
	b @4
	@7:
	stw r7, blockGlyph(r13)
	@4:
	lwz r0, 0x4(r7)
	addi r8, r8, 0x1
	add r7, r7, r0
	@2:
	lwz r0, 0xc(r6)
	cmplw r8, r0
	blt @3
	lwz r6, blockGlyph(r13)
	la r3, fgTexObj(r13)
	li r7, 0x0
	li r8, 0x0
	lhz r5, 0x1a(r6)
	addi r4, r6, 0x20
	lhz r6, 0x1c(r6)
	li r9, 0x0
	li r10, 0x0
	bl GXInitTexObj
	lfs f1, float_0_8041a300(r2)
	la r3, fgTexObj(r13)
	li r4, 0x1
	li r5, 0x1
	fmr f2, f1
	li r6, 0x0
	fmr f3, f1
	li r7, 0x0
	li r8, 0x0
	bl GXInitTexObjLOD
	li r3, 0x20
	bl JUTFont_CodeToGlyph
	lwz r5, pfh(r13)
	lis r4, 0x5749
	addi r4, r4, 0x4431
	clrlwi r3, r3, 16
	lwz r0, 0xc(r5)
	addi r5, r5, 0x20
	mtctr r0
	cmplwi r0, 0x0
	ble @8
	@9:
	lwz r0, 0x0(r5)
	cmpw r0, r4
	beq @10
	b @11
	@10:
	lhz r6, 0x8(r5)
	cmplw r3, r6
	blt @11
	lhz r0, 0xa(r5)
	cmplw r3, r0
	bgt @11
	subf r0, r6, r3
	slwi r3, r0, 1
	addi r4, r3, 0xc
	add r4, r5, r4
	b @12
	@11:
	lwz r0, 0x4(r5)
	add r5, r5, r0
	bdnz @9
	@8:
	li r4, 0x0
	@12:
	li r0, 0x7
	lis r3, 0x1
	stb r0, 0x1(r4)
	subi r3, r3, 0x7ec0
	bl JUTFont_CodeToGlyph
	lwz r5, pfh(r13)
	lis r4, 0x5749
	addi r4, r4, 0x4431
	clrlwi r3, r3, 16
	lwz r0, 0xc(r5)
	addi r5, r5, 0x20
	mtctr r0
	cmplwi r0, 0x0
	ble @13
	@14:
	lwz r0, 0x0(r5)
	cmpw r0, r4
	beq @15
	b @16
	@15:
	lhz r6, 0x8(r5)
	cmplw r3, r6
	blt @16
	lhz r0, 0xa(r5)
	cmplw r3, r0
	bgt @16
	subf r0, r6, r3
	slwi r3, r0, 1
	addi r3, r3, 0xc
	add r3, r5, r3
	b @17
	@16:
	lwz r0, 0x4(r5)
	add r5, r5, r0
	bdnz @14
	@13:
	li r3, 0x0
	@17:
	li r0, 0x9
	stb r0, 0x1(r3)
	@1:
	lwz r0, 0x94(r1)
	lwz r31, 0x8c(r1)
	lwz r30, 0x88(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm GXColor HSV2RGB(GXColor hsv) {
	nofralloc
	stwu r1, -0xa0(r1)
	mflr r0
	stw r0, 0xa4(r1)
	stfd f31, 0x90(r1)
	psq_st f31, 0x98(r1), 0, 0
	stfd f30, 0x80(r1)
	psq_st f30, 0x88(r1), 0, 0
	stfd f29, 0x70(r1)
	psq_st f29, 0x78(r1), 0, 0
	stfd f28, 0x60(r1)
	psq_st f28, 0x68(r1), 0, 0
	stfd f27, 0x50(r1)
	psq_st f27, 0x58(r1), 0, 0
	stfd f26, 0x40(r1)
	psq_st f26, 0x48(r1), 0, 0
	stw r31, 0x3c(r1)
	mr r31, r3
	lis r3, 0x4330
	lbz r0, 0x0(r31)
	lis r4, double_to_int_mask_802c48e8@ha
	lbz r5, 0x1(r31)
	stw r0, 0x24(r1)
	lbz r0, 0x2(r31)
	stw r3, 0x20(r1)
	lfd f5, double_to_int_mask_802c48e8@l(r4)
	lfd f0, 0x20(r1)
	lfs f3, float_360_8041a308(r2)
	fsubs f2, f0, f5
	lfs f1, float_0p0039062_8041a30c(r2)
	stw r5, 0x14(r1)
	lfs f0, float_60_8041a310(r2)
	fmuls f2, f3, f2
	stw r3, 0x10(r1)
	lfs f3, float_255_8041a304(r2)
	stw r0, 0x1c(r1)
	fmuls f1, f2, f1
	lfd f4, 0x10(r1)
	stw r3, 0x18(r1)
	fsubs f2, f4, f5
	fdivs f28, f1, f0
	lfd f0, 0x18(r1)
	fsubs f0, f0, f5
	fdivs f27, f2, f3
	fdivs f26, f0, f3
	fmr f1, f28
	bl floor
	fctiwz f0, f1
	lis r3, double_to_int_802c48f0@ha
	lis r0, 0x4330
	lfd f1, double_to_int_802c48f0@l(r3)
	stw r0, 0x30(r1)
	stfd f0, 0x28(r1)
	lwz r4, 0x2c(r1)
	xoris r3, r4, 0x8000
	clrlwi. r0, r4, 31
	stw r3, 0x34(r1)
	lfd f0, 0x30(r1)
	fsubs f0, f0, f1
	fsubs f2, f28, f0
	bne @1
	lfs f0, float_1_8041a2f4(r2)
	fsubs f2, f0, f2
	@1:
	lfs f0, float_1_8041a2f4(r2)
	cmpwi r4, 0x3
	fsubs f1, f0, f27
	fnmsubs f0, f27, f2, f0
	fmuls f1, f26, f1
	fmuls f0, f26, f0
	beq @2
	bge @3
	cmpwi r4, 0x1
	beq @4
	bge @5
	cmpwi r4, 0x0
	bge @6
	b @7
	@3:
	cmpwi r4, 0x5
	beq @8
	bge @7
	b @9
	@6:
	fmr f31, f26
	fmr f30, f0
	fmr f29, f1
	b @7
	@4:
	fmr f31, f0
	fmr f30, f26
	fmr f29, f1
	b @7
	@5:
	fmr f31, f1
	fmr f30, f26
	fmr f29, f0
	b @7
	@2:
	fmr f31, f1
	fmr f30, f0
	fmr f29, f26
	b @7
	@9:
	fmr f31, f0
	fmr f30, f1
	fmr f29, f26
	b @7
	@8:
	fmr f31, f26
	fmr f30, f1
	fmr f29, f0
	@7:
	lfs f0, float_255_8041a304(r2)
	lbz r0, 0x3(r31)
	fmuls f2, f0, f31
	fmuls f1, f0, f30
	stb r0, 0xb(r1)
	fmuls f0, f0, f29
	fctiwz f2, f2
	fctiwz f1, f1
	fctiwz f0, f0
	stfd f2, 0x30(r1)
	stfd f1, 0x28(r1)
	lwz r4, 0x34(r1)
	stfd f0, 0x20(r1)
	lwz r3, 0x2c(r1)
	lwz r0, 0x24(r1)
	stb r4, 0x8(r1)
	stb r3, 0x9(r1)
	stb r0, 0xa(r1)
	lwz r3, 0x8(r1)
	psq_l f31, 0x98(r1), 0, 0
	lfd f31, 0x90(r1)
	psq_l f30, 0x88(r1), 0, 0
	lfd f30, 0x80(r1)
	psq_l f29, 0x78(r1), 0, 0
	lfd f29, 0x70(r1)
	psq_l f28, 0x68(r1), 0, 0
	lfd f28, 0x60(r1)
	psq_l f27, 0x58(r1), 0, 0
	lfd f27, 0x50(r1)
	psq_l f26, 0x48(r1), 0, 0
	lfd f26, 0x40(r1)
	lwz r0, 0xa4(r1)
	lwz r31, 0x3c(r1)
	mtlr r0
	addi r1, r1, 0xa0
	blr
}

asm u16 FontGetMessageWidth(const char* message) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r4, 0x0
	stw r0, 0x14(r1)
	bl FontGetMessageWidthLine
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm u16 FontGetMessageWidthLine(const char* msg, u16* lines) {
	nofralloc
	stwu r1, -0x180(r1)
	mflr r0
	stw r0, 0x184(r1)
	stmw r25, 0x164(r1)
	mr r25, r3
	mr r26, r4
	li r29, 0x0
	li r28, 0x0
	li r27, 0x0
	lis r31, 0x1
	b @1
	@2:
	subi r30, r31, 0x1
	extsb r3, r3
	bl _ismbblead
	cmpwi r3, 0x0
	beq @3
	lhz r3, 0x0(r25)
	bl JUTFont_CodeToGlyph
	mr r30, r3
	addi r25, r25, 0x2
	b @4
	@3:
	lbz r0, 0x0(r25)
	extsb r0, r0
	cmpwi r0, 0x3c
	beq @5
	bge @6
	cmpwi r0, 0xa
	beq @7
	b @6
	@7:
	clrlwi r3, r29, 16
	clrlwi r0, r28, 16
	cmplw r3, r0
	bge @8
	mr r29, r28
	@8:
	li r28, 0x0
	addi r27, r27, 0x1
	addi r25, r25, 0x1
	b @4
	@5:
	addi r3, r25, 0x1
	addi r4, r1, 0xc0
	addi r5, r1, 0x40
	bl msgGetCommand
	mr r0, r3
	addi r3, r1, 0xc0
	mr r25, r0
	la r4, str_8041A314(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @9
	bl camGetCurPtr
	lbz r0, 0x40(r1)
	extsb r0, r0
	cmpwi r0, 0x30
	blt @10
	cmpwi r0, 0x39
	bgt @10
	lis r4, str_802C4904@ha
	addi r3, r1, 0x40
	addi r4, r4, str_802C4904@l
	addi r5, r1, 0x1c
	addi r6, r1, 0xc
	addi r7, r1, 0x18
	addi r8, r1, 0x14
	addi r9, r1, 0x10
	crclr 6
	bl sscanf
	b @11
	@10:
	lis r4, str_802C4910@ha
	addi r3, r1, 0x40
	addi r4, r4, str_802C4910@l
	addi r5, r1, 0x20
	addi r6, r1, 0xc
	addi r7, r1, 0x18
	addi r8, r1, 0x14
	addi r9, r1, 0x10
	crclr 6
	bl sscanf
	addi r3, r1, 0x20
	bl msgIconStr2ID
	cmpwi r3, 0x0
	stw r3, 0x1c(r1)
	bge @11
	li r0, 0x0
	stw r0, 0x1c(r1)
	@11:
	lwz r0, 0x1c(r1)
	addi r3, r1, 0xa
	addi r4, r1, 0x8
	clrlwi r5, r0, 16
	bl iconGetWidthHight
	lhz r4, 0xa(r1)
	lis r5, 0x4330
	lwz r0, 0x10(r1)
	lis r3, double_to_int_802c48f0@ha
	lis r6, double_to_int_mask_802c48e8@ha
	stw r4, 0x14c(r1)
	addi r4, r6, double_to_int_mask_802c48e8@l
	xoris r0, r0, 0x8000
	stw r5, 0x148(r1)
	clrlwi r6, r28, 16
	lfd f4, 0x0(r4)
	lfd f0, 0x148(r1)
	stw r0, 0x154(r1)
	lfd f1, double_to_int_802c48f0@l(r3)
	fsubs f3, f0, f4
	stw r5, 0x150(r1)
	lfs f2, 0xc(r1)
	lfd f0, 0x150(r1)
	stw r6, 0x144(r1)
	fsubs f0, f0, f1
	stw r5, 0x140(r1)
	lfd f1, 0x140(r1)
	fmadds f0, f3, f2, f0
	fsubs f1, f1, f4
	fadds f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x158(r1)
	lwz r28, 0x15c(r1)
	b @12
	@9:
	lbz r0, 0xc0(r1)
	extsb r0, r0
	cmpwi r0, 0x52
	beq @4
	cmpwi r0, 0x2f
	bne @12
	cmplwi r0, 0x2f72
	beq @4
	@12:
	lbz r0, 0x0(r25)
	cmpwi r0, 0xa
	bne @4
	addi r25, r25, 0x1
	b @4
	@6:
	lbz r0, 0x0(r25)
	addi r25, r25, 0x1
	extsb r3, r0
	bl JUTFont_CodeToGlyph
	mr r30, r3
	@4:
	clrlwi r4, r30, 16
	cmplwi r4, 0xffff
	beq @1
	lwz r5, pfh(r13)
	lis r3, 0x5749
	addi r3, r3, 0x4431
	lwz r0, 0xc(r5)
	addi r6, r5, 0x20
	mtctr r0
	cmplwi r0, 0x0
	ble @13
	@14:
	lwz r0, 0x0(r6)
	cmpw r0, r3
	beq @15
	b @16
	@15:
	lhz r5, 0x8(r6)
	cmplw r4, r5
	blt @16
	lhz r0, 0xa(r6)
	cmplw r4, r0
	bgt @16
	subf r0, r5, r4
	slwi r3, r0, 1
	addi r5, r3, 0xc
	add r5, r6, r5
	b @17
	@16:
	lwz r0, 0x4(r6)
	add r6, r6, r0
	bdnz @14
	@13:
	li r5, 0x0
	@17:
	lwz r4, gp(r13)
	la r3, charspace(r13)
	lbz r0, 0x1(r5)
	lwz r4, 0x16c(r4)
	add r0, r0, r28
	slwi r4, r4, 2
	lwzx r3, r3, r4
	add r0, r3, r0
	clrlwi r28, r0, 16
	@1:
	lbz r3, 0x0(r25)
	extsb. r0, r3
	bne @2
	clrlwi r3, r29, 16
	clrlwi r0, r28, 16
	cmplw r3, r0
	bge @18
	mr r29, r28
	@18:
	clrlwi. r0, r29, 16
	beq @19
	lwz r4, gp(r13)
	la r3, charspace(r13)
	lwz r0, 0x16c(r4)
	slwi r0, r0, 2
	lwzx r0, r3, r0
	subf r0, r0, r29
	clrlwi r29, r0, 16
	@19:
	cmplwi r26, 0x0
	beq @20
	sth r27, 0x0(r26)
	@20:
	mr r3, r29
	lmw r25, 0x164(r1)
	lwz r0, 0x184(r1)
	mtlr r0
	addi r1, r1, 0x180
	blr
}

asm u16 kanjiGetWidth(u16 code) {
	nofralloc
	lwz r5, pfh(r13)
	lis r4, 0x5749
	addi r4, r4, 0x4431
	clrlwi r3, r3, 16
	lwz r0, 0xc(r5)
	addi r5, r5, 0x20
	mtctr r0
	cmplwi r0, 0x0
	ble @1
	@2:
	lwz r0, 0x0(r5)
	cmpw r0, r4
	beq @3
	b @4
	@3:
	lhz r6, 0x8(r5)
	cmplw r3, r6
	blt @4
	lhz r0, 0xa(r5)
	cmplw r3, r0
	bgt @4
	subf r0, r6, r3
	slwi r3, r0, 1
	addi r3, r3, 0xc
	add r3, r5, r3
	b @5
	@4:
	lwz r0, 0x4(r5)
	add r5, r5, r0
	bdnz @2
	@1:
	li r3, 0x0
	@5:
	lbz r3, 0x1(r3)
	blr
}

asm u16 kanjiSearch(u32 code) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl JUTFont_CodeToGlyph
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void hankakuSearch(s8 c) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	extsb r3, r3
	stw r0, 0x14(r1)
	bl JUTFont_CodeToGlyph
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void FontDrawMessageMtx(Mtx mtx, const char* msg) {
	nofralloc
	stwu r1, -0x270(r1)
	mflr r0
	lis r5, str_802C48A0@ha
	stw r0, 0x274(r1)
	stmw r23, 0x24c(r1)
	mr r23, r3
	mr r24, r4
	addi r29, r5, str_802C48A0@l
	bl camGetCurPtr
	lfs f0, float_0_8041a300(r2)
	mr r30, r3
	li r26, 0x0
	li r25, 0x0
	fctiwz f0, f0
	lis r31, 0x1
	stfd f0, 0x1f0(r1)
	lwz r28, 0x1f4(r1)
	b @1
	@2:
	subi r27, r31, 0x1
	extsb r3, r3
	bl _ismbblead
	cmpwi r3, 0x0
	beq @3
	lhz r3, 0x0(r24)
	bl JUTFont_CodeToGlyph
	mr r27, r3
	addi r24, r24, 0x2
	b @4
	@3:
	lbz r0, 0x0(r24)
	extsb r0, r0
	cmpwi r0, 0x3c
	beq @5
	bge @6
	cmpwi r0, 0xa
	beq @7
	b @6
	@7:
	mr r26, r28
	subi r25, r25, 0x1c
	addi r24, r24, 0x1
	b @4
	@5:
	addi r3, r24, 0x1
	addi r4, r1, 0x170
	addi r5, r1, 0xf0
	bl msgGetCommand
	mr r0, r3
	addi r3, r1, 0x170
	mr r24, r0
	la r4, str_8041A31C(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @8
	lwz r7, dat_8041a2ec(r2)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x4c(r1)
	addi r4, r1, 0x40
	li r3, 0x1
	lbz r5, 0x4f(r1)
	stw r7, 0xc(r1)
	mullw r0, r5, r0
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x4f(r1)
	lwz r0, 0x4c(r1)
	stw r0, 0x40(r1)
	bl GXSetTevColor
	b @9
	@8:
	addi r3, r1, 0x170
	la r4, str_8041A320(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @10
	lwz r7, fontColTbl(r13)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x48(r1)
	addi r4, r1, 0x3c
	li r3, 0x1
	lbz r5, 0x4b(r1)
	stw r7, 0x18(r1)
	mullw r0, r5, r0
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x4b(r1)
	lwz r0, 0x48(r1)
	stw r0, 0x3c(r1)
	bl GXSetTevColor
	b @9
	@10:
	addi r3, r1, 0x170
	la r4, str_8041A314(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @11
	bl camGetCurPtr
	lbz r0, 0xf0(r1)
	extsb r0, r0
	cmpwi r0, 0x30
	blt @12
	cmpwi r0, 0x39
	bgt @12
	addi r3, r1, 0xf0
	addi r4, r29, 0x64
	addi r5, r1, 0x60
	addi r6, r1, 0x50
	addi r7, r1, 0x5c
	addi r8, r1, 0x58
	addi r9, r1, 0x54
	crclr 6
	bl sscanf
	b @13
	@12:
	addi r3, r1, 0xf0
	addi r4, r29, 0x70
	addi r5, r1, 0x70
	addi r6, r1, 0x50
	addi r7, r1, 0x5c
	addi r8, r1, 0x58
	addi r9, r1, 0x54
	crclr 6
	bl sscanf
	addi r3, r1, 0x70
	bl msgIconStr2ID
	cmpwi r3, 0x0
	stw r3, 0x60(r1)
	bge @13
	li r0, 0x0
	stw r0, 0x60(r1)
	@13:
	lwz r0, 0x60(r1)
	addi r3, r1, 0xa
	addi r4, r1, 0x8
	clrlwi r5, r0, 16
	bl iconGetWidthHight
	lhz r0, 0xa(r1)
	lis r9, 0x4330
	lhz r6, 0x8(r1)
	xoris r8, r26, 0x8000
	stw r0, 0x1fc(r1)
	xoris r0, r25, 0x8000
	lwz r5, 0x5c(r1)
	addi r4, r1, 0x64
	stw r9, 0x1f8(r1)
	mr r3, r23
	lwz r7, 0x58(r1)
	xoris r10, r5, 0x8000
	lfd f4, 0x48(r29)
	mr r5, r4
	lfd f0, 0x1f8(r1)
	xoris r7, r7, 0x8000
	stw r8, 0x204(r1)
	fsubs f1, f0, f4
	lfs f2, float_0p5_8041a328(r2)
	stw r9, 0x200(r1)
	lfd f5, 0x50(r29)
	lfd f0, 0x200(r1)
	fmuls f3, f2, f1
	stw r6, 0x214(r1)
	fsubs f2, f0, f5
	lfs f6, 0x50(r1)
	stw r9, 0x210(r1)
	lfs f0, float_0_8041a300(r2)
	lfd f1, 0x210(r1)
	fmadds f3, f3, f6, f2
	stw r0, 0x21c(r1)
	fsubs f2, f1, f4
	stw r9, 0x218(r1)
	lfd f1, 0x218(r1)
	stw r10, 0x1f4(r1)
	fsubs f1, f1, f5
	stw r9, 0x1f0(r1)
	lfd f4, 0x1f0(r1)
	fnmsubs f1, f2, f6, f1
	stw r7, 0x20c(r1)
	fsubs f4, f4, f5
	stw r9, 0x208(r1)
	lfd f2, 0x208(r1)
	fadds f3, f4, f3
	stfs f0, 0x6c(r1)
	fsubs f0, f2, f5
	stfs f3, 0x64(r1)
	fadds f0, f0, f1
	stfs f0, 0x68(r1)
	bl PSMTXMultVec
	lwz r0, 0x60(r1)
	addi r3, r1, 0x64
	lfs f1, 0x50(r1)
	li r4, 0x10
	lbz r6, fontAlpha(r13)
	clrlwi r5, r0, 16
	bl iconDispGxAlpha
	lwz r9, fontColTbl(r13)
	lis r3, 0x8081
	lbz r10, fontAlpha(r13)
	subi r8, r3, 0x7f7f
	stw r9, 0x34(r1)
	li r0, 0x0
	lwz r6, 0x20(r29)
	addi r3, r1, 0x38
	lbz r4, 0x37(r1)
	lwz r5, 0x24(r29)
	mullw r7, r4, r10
	lwz r4, 0x28(r29)
	stw r0, fontEdge(r13)
	stw r4, fontScale+0x8(r13)
	mulhw r8, r8, r7
	stw r9, fontColor(r13)
	stb r10, fontAlpha(r13)
	stw r6, fontScale(r13)
	add r4, r8, r7
	srawi r4, r4, 7
	stw r5, fontScale+0x4(r13)
	srwi r0, r4, 31
	add r0, r4, r0
	stb r0, 0x37(r1)
	lwz r0, 0x34(r1)
	stw r0, 0x38(r1)
	bl JUTFont_DrawStart
	lwz r7, fontColor(r13)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x44(r1)
	addi r4, r1, 0x30
	li r3, 0x1
	lbz r5, 0x47(r1)
	stw r7, 0x14(r1)
	mullw r0, r5, r0
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x47(r1)
	lwz r0, 0x44(r1)
	stw r0, 0x30(r1)
	bl GXSetTevColor
	lwz r0, 0x54(r1)
	lis r4, 0x4330
	lhz r3, 0xa(r1)
	xoris r5, r26, 0x8000
	xoris r0, r0, 0x8000
	stw r4, 0x228(r1)
	lfd f4, 0x50(r29)
	stw r3, 0x22c(r1)
	lfd f1, 0x48(r29)
	lfd f0, 0x228(r1)
	stw r0, 0x234(r1)
	fsubs f2, f0, f1
	lfs f1, 0x50(r1)
	stw r4, 0x230(r1)
	lfd f0, 0x230(r1)
	stw r5, 0x224(r1)
	fsubs f0, f0, f4
	stw r4, 0x220(r1)
	lfd f3, 0x220(r1)
	fmadds f0, f2, f1, f0
	fsubs f1, f3, f4
	fadds f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x238(r1)
	lwz r26, 0x23c(r1)
	b @9
	@11:
	lbz r0, 0x170(r1)
	extsb r0, r0
	cmpwi r0, 0x52
	beq @4
	cmpwi r0, 0x2f
	bne @9
	cmplwi r0, 0x2f72
	beq @4
	@9:
	lbz r0, 0x0(r24)
	cmpwi r0, 0xa
	bne @4
	addi r24, r24, 0x1
	b @4
	@6:
	lbz r0, 0x0(r24)
	addi r24, r24, 0x1
	extsb r3, r0
	bl JUTFont_CodeToGlyph
	mr r27, r3
	@4:
	clrlwi r0, r27, 16
	cmplwi r0, 0xffff
	beq @1
	lis r4, 0x4330
	xoris r3, r26, 0x8000
	xoris r0, r25, 0x8000
	stw r3, 0x23c(r1)
	lfd f2, 0x50(r29)
	addi r3, r1, 0x90
	stw r4, 0x238(r1)
	lfs f3, float_0_8041a300(r2)
	lfd f0, 0x238(r1)
	stw r0, 0x234(r1)
	fsubs f1, f0, f2
	stw r4, 0x230(r1)
	lfd f0, 0x230(r1)
	fsubs f2, f0, f2
	bl PSMTXTrans
	mr r4, r23
	addi r3, r30, 0x11c
	addi r5, r1, 0xc0
	bl PSMTXConcat
	addi r3, r1, 0xc0
	addi r4, r1, 0x90
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0xc0
	li r4, 0x0
	bl GXLoadPosMtxImm
	lwz r0, fontEdge(r13)
	cmpwi r0, 0x0
	beq @14
	lwz r7, fontColTbl(r13)
	lis r3, 0x8081
	lwz r8, fontColor(r13)
	subi r6, r3, 0x7f7f
	stw r7, 0x24(r1)
	addi r4, r1, 0x1c
	lbz r0, fontAlpha(r13)
	li r3, 0x1
	lbz r5, 0x27(r1)
	stw r8, 0x28(r1)
	mullw r0, r5, r0
	stw r7, 0x10(r1)
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x27(r1)
	lwz r0, 0x24(r1)
	stw r0, 0x1c(r1)
	bl GXSetTevColor
	mr r3, r27
	li r4, -0x2
	li r5, 0x0
	bl _JUTFont_DrawPos
	mr r3, r27
	li r4, 0x2
	li r5, 0x0
	bl _JUTFont_DrawPos
	mr r3, r27
	li r4, 0x0
	li r5, -0x2
	bl _JUTFont_DrawPos
	mr r3, r27
	li r4, 0x0
	li r5, 0x2
	bl _JUTFont_DrawPos
	lwz r7, 0x28(r1)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x2c(r1)
	addi r4, r1, 0x20
	li r3, 0x1
	lbz r5, 0x2f(r1)
	stw r7, fontColor(r13)
	mullw r0, r5, r0
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x2f(r1)
	lwz r0, 0x2c(r1)
	stw r0, 0x20(r1)
	bl GXSetTevColor
	@14:
	mr r3, r27
	li r4, 0x0
	li r5, 0x0
	bl _JUTFont_DrawPos
	lwz r5, pfh(r13)
	lis r3, 0x5749
	addi r4, r3, 0x4431
	clrlwi r3, r27, 16
	lwz r0, 0xc(r5)
	addi r6, r5, 0x20
	mtctr r0
	cmplwi r0, 0x0
	ble @15
	@16:
	lwz r0, 0x0(r6)
	cmpw r0, r4
	beq @17
	b @18
	@17:
	lhz r5, 0x8(r6)
	cmplw r3, r5
	blt @18
	lhz r0, 0xa(r6)
	cmplw r3, r0
	bgt @18
	subf r0, r5, r3
	slwi r3, r0, 1
	addi r5, r3, 0xc
	add r5, r6, r5
	b @19
	@18:
	lwz r0, 0x4(r6)
	add r6, r6, r0
	bdnz @16
	@15:
	li r5, 0x0
	@19:
	lwz r4, gp(r13)
	la r3, charspace(r13)
	lbz r0, 0x1(r5)
	lwz r4, 0x16c(r4)
	add r26, r0, r26
	slwi r0, r4, 2
	lwzx r0, r3, r0
	add r26, r0, r26
	@1:
	lbz r3, 0x0(r24)
	extsb. r0, r3
	bne @2
	lmw r23, 0x24c(r1)
	lwz r0, 0x274(r1)
	mtlr r0
	addi r1, r1, 0x270
	blr
}

asm void FontDrawMessage(s32 x, s32 y, const char* msg) {
	nofralloc
	stwu r1, -0x230(r1)
	mflr r0
	stw r0, 0x234(r1)
	stmw r23, 0x20c(r1)
	mr r25, r3
	lis r3, str_802C48A0@ha
	mr r26, r5
	mr r29, r25
	mr r28, r4
	addi r30, r3, str_802C48A0@l
	lis r31, 0x1
	b @1
	@2:
	subi r27, r31, 0x1
	extsb r3, r3
	bl _ismbblead
	cmpwi r3, 0x0
	beq @3
	lhz r3, 0x0(r26)
	bl JUTFont_CodeToGlyph
	mr r27, r3
	addi r26, r26, 0x2
	b @4
	@3:
	lbz r0, 0x0(r26)
	extsb r0, r0
	cmpwi r0, 0x3c
	beq @5
	bge @6
	cmpwi r0, 0xa
	beq @7
	b @6
	@7:
	mr r29, r25
	subi r28, r28, 0x1c
	addi r26, r26, 0x1
	b @4
	@5:
	addi r3, r26, 0x1
	addi r4, r1, 0x12c
	addi r5, r1, 0xac
	bl msgGetCommand
	mr r0, r3
	addi r3, r1, 0x12c
	mr r26, r0
	la r4, str_8041A31C(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @8
	lwz r7, dat_8041a2e8(r2)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x64(r1)
	addi r4, r1, 0x50
	li r3, 0x1
	lbz r5, 0x67(r1)
	stw r7, 0xc(r1)
	mullw r0, r5, r0
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x67(r1)
	lwz r0, 0x64(r1)
	stw r0, 0x50(r1)
	bl GXSetTevColor
	b @9
	@8:
	addi r3, r1, 0x12c
	la r4, str_8041A320(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @10
	lwz r7, fontColTbl(r13)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x60(r1)
	addi r4, r1, 0x4c
	li r3, 0x1
	lbz r5, 0x63(r1)
	stw r7, 0x20(r1)
	mullw r0, r5, r0
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x63(r1)
	lwz r0, 0x60(r1)
	stw r0, 0x4c(r1)
	bl GXSetTevColor
	b @9
	@10:
	addi r3, r1, 0x12c
	la r4, str_8041A32C(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @11
	addi r3, r1, 0xac
	addi r5, r1, 0x7c
	la r4, str_8041A330(r2)
	crclr 6
	bl sscanf
	lwz r7, 0x7c(r1)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x5c(r1)
	addi r4, r1, 0x48
	li r3, 0x1
	lbz r5, 0x5f(r1)
	stw r7, 0x1c(r1)
	mullw r0, r5, r0
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x5f(r1)
	lwz r0, 0x5c(r1)
	stw r0, 0x48(r1)
	bl GXSetTevColor
	b @9
	@11:
	addi r3, r1, 0x12c
	la r4, str_8041A334(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @12
	lwz r7, fontColTbl(r13)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x58(r1)
	addi r4, r1, 0x44
	li r3, 0x1
	lbz r5, 0x5b(r1)
	stw r7, 0x18(r1)
	mullw r0, r5, r0
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x5b(r1)
	lwz r0, 0x58(r1)
	stw r0, 0x44(r1)
	bl GXSetTevColor
	b @9
	@12:
	addi r3, r1, 0x12c
	la r4, str_8041A314(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @13
	bl camGetCurPtr
	lbz r0, 0xac(r1)
	extsb r0, r0
	cmpwi r0, 0x30
	blt @14
	cmpwi r0, 0x39
	bgt @14
	addi r3, r1, 0xac
	addi r4, r30, 0x64
	addi r5, r1, 0x78
	addi r6, r1, 0x68
	addi r7, r1, 0x74
	addi r8, r1, 0x70
	addi r9, r1, 0x6c
	crclr 6
	bl sscanf
	b @15
	@14:
	addi r3, r1, 0xac
	addi r4, r30, 0x70
	addi r5, r1, 0x8c
	addi r6, r1, 0x68
	addi r7, r1, 0x74
	addi r8, r1, 0x70
	addi r9, r1, 0x6c
	crclr 6
	bl sscanf
	addi r3, r1, 0x8c
	bl msgIconStr2ID
	cmpwi r3, 0x0
	stw r3, 0x78(r1)
	bge @15
	li r0, 0x0
	stw r0, 0x78(r1)
	@15:
	lwz r0, 0x78(r1)
	addi r3, r1, 0xa
	addi r4, r1, 0x8
	clrlwi r5, r0, 16
	bl iconGetWidthHight
	lhz r3, 0xa(r1)
	lis r9, 0x4330
	lhz r0, 0x8(r1)
	xoris r8, r29, 0x8000
	stw r3, 0x1bc(r1)
	xoris r5, r28, 0x8000
	lwz r7, 0x74(r1)
	addi r3, r1, 0x80
	stw r9, 0x1b8(r1)
	li r4, 0x10
	lfd f3, 0x48(r30)
	xoris r10, r7, 0x8000
	lfd f0, 0x1b8(r1)
	stw r0, 0x1d4(r1)
	fsubs f0, f0, f3
	lfs f2, float_0p5_8041a328(r2)
	stw r9, 0x1d0(r1)
	lwz r6, 0x70(r1)
	fmuls f5, f2, f0
	lfd f2, 0x1d0(r1)
	stw r8, 0x1c4(r1)
	xoris r7, r6, 0x8000
	lfd f6, 0x50(r30)
	fsubs f3, f2, f3
	stw r9, 0x1c0(r1)
	lfs f1, 0x68(r1)
	lfd f0, 0x1c0(r1)
	stw r5, 0x1dc(r1)
	fsubs f4, f0, f6
	lfs f0, float_0_8041a300(r2)
	stw r9, 0x1d8(r1)
	lwz r0, 0x78(r1)
	lfd f2, 0x1d8(r1)
	fmadds f4, f5, f1, f4
	stw r10, 0x1b4(r1)
	clrlwi r5, r0, 16
	fsubs f2, f2, f6
	lbz r6, fontAlpha(r13)
	stw r9, 0x1b0(r1)
	lfd f5, 0x1b0(r1)
	fnmsubs f2, f3, f1, f2
	stw r7, 0x1cc(r1)
	fsubs f5, f5, f6
	stw r9, 0x1c8(r1)
	fadds f4, f5, f4
	lfd f3, 0x1c8(r1)
	stfs f0, 0x88(r1)
	fsubs f0, f3, f6
	stfs f4, 0x80(r1)
	fadds f0, f0, f2
	stfs f0, 0x84(r1)
	bl iconDispGxAlpha
	lwz r9, fontColTbl(r13)
	lis r3, 0x8081
	lbz r10, fontAlpha(r13)
	subi r8, r3, 0x7f7f
	stw r9, 0x3c(r1)
	li r0, 0x0
	lwz r6, 0x20(r30)
	addi r3, r1, 0x40
	lbz r4, 0x3f(r1)
	lwz r5, 0x24(r30)
	mullw r7, r4, r10
	lwz r4, 0x28(r30)
	stw r0, fontEdge(r13)
	stw r4, fontScale+0x8(r13)
	mulhw r8, r8, r7
	stw r9, fontColor(r13)
	stb r10, fontAlpha(r13)
	stw r6, fontScale(r13)
	add r4, r8, r7
	srawi r4, r4, 7
	stw r5, fontScale+0x4(r13)
	srwi r0, r4, 31
	add r0, r4, r0
	stb r0, 0x3f(r1)
	lwz r0, 0x3c(r1)
	stw r0, 0x40(r1)
	bl JUTFont_DrawStart
	lwz r7, fontColor(r13)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x54(r1)
	addi r4, r1, 0x38
	li r3, 0x1
	lbz r5, 0x57(r1)
	stw r7, 0x14(r1)
	mullw r0, r5, r0
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x57(r1)
	lwz r0, 0x54(r1)
	stw r0, 0x38(r1)
	bl GXSetTevColor
	lwz r0, 0x6c(r1)
	lis r4, 0x4330
	lhz r3, 0xa(r1)
	xoris r5, r29, 0x8000
	xoris r0, r0, 0x8000
	stw r4, 0x1e8(r1)
	lfd f4, 0x50(r30)
	stw r3, 0x1ec(r1)
	lfd f1, 0x48(r30)
	lfd f0, 0x1e8(r1)
	stw r0, 0x1f4(r1)
	fsubs f2, f0, f1
	lfs f1, 0x68(r1)
	stw r4, 0x1f0(r1)
	lfd f0, 0x1f0(r1)
	stw r5, 0x1e4(r1)
	fsubs f0, f0, f4
	stw r4, 0x1e0(r1)
	lfd f3, 0x1e0(r1)
	fmadds f0, f2, f1, f0
	fsubs f1, f3, f4
	fadds f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x1f8(r1)
	lwz r29, 0x1fc(r1)
	b @9
	@13:
	lbz r0, 0x12c(r1)
	extsb r0, r0
	cmpwi r0, 0x52
	beq @4
	cmpwi r0, 0x2f
	bne @9
	cmplwi r0, 0x2f72
	beq @4
	@9:
	lbz r0, 0x0(r26)
	cmpwi r0, 0xa
	bne @4
	addi r26, r26, 0x1
	b @4
	@6:
	lbz r0, 0x0(r26)
	addi r26, r26, 0x1
	extsb r3, r0
	bl JUTFont_CodeToGlyph
	mr r27, r3
	@4:
	clrlwi r0, r27, 16
	cmplwi r0, 0xffff
	beq @1
	lwz r0, fontEdge(r13)
	cmpwi r0, 0x0
	beq @16
	lwz r7, fontColTbl(r13)
	lis r3, 0x8081
	lwz r8, fontColor(r13)
	subi r6, r3, 0x7f7f
	stw r7, 0x2c(r1)
	addi r4, r1, 0x24
	lbz r0, fontAlpha(r13)
	li r3, 0x1
	lbz r5, 0x2f(r1)
	stw r8, 0x30(r1)
	mullw r0, r5, r0
	stw r7, 0x10(r1)
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x2f(r1)
	lwz r0, 0x2c(r1)
	stw r0, 0x24(r1)
	bl GXSetTevColor
	extsh r24, r29
	extsh r23, r28
	subi r0, r24, 0x2
	mr r3, r27
	mr r5, r23
	extsh r4, r0
	bl _JUTFont_DrawPos
	addi r0, r24, 0x2
	mr r3, r27
	mr r5, r23
	extsh r4, r0
	bl _JUTFont_DrawPos
	mr r24, r23
	extsh r23, r29
	subi r0, r24, 0x2
	mr r3, r27
	mr r4, r23
	extsh r5, r0
	bl _JUTFont_DrawPos
	addi r0, r24, 0x2
	mr r3, r27
	mr r4, r23
	extsh r5, r0
	bl _JUTFont_DrawPos
	lwz r7, 0x30(r1)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x34(r1)
	addi r4, r1, 0x28
	li r3, 0x1
	lbz r5, 0x37(r1)
	stw r7, fontColor(r13)
	mullw r0, r5, r0
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x37(r1)
	lwz r0, 0x34(r1)
	stw r0, 0x28(r1)
	bl GXSetTevColor
	@16:
	mr r3, r27
	extsh r4, r29
	extsh r5, r28
	bl _JUTFont_DrawPos
	lwz r5, pfh(r13)
	lis r3, 0x5749
	addi r4, r3, 0x4431
	clrlwi r3, r27, 16
	lwz r0, 0xc(r5)
	addi r6, r5, 0x20
	mtctr r0
	cmplwi r0, 0x0
	ble @17
	@18:
	lwz r0, 0x0(r6)
	cmpw r0, r4
	beq @19
	b @20
	@19:
	lhz r5, 0x8(r6)
	cmplw r3, r5
	blt @20
	lhz r0, 0xa(r6)
	cmplw r3, r0
	bgt @20
	subf r0, r5, r3
	slwi r3, r0, 1
	addi r5, r3, 0xc
	add r5, r6, r5
	b @21
	@20:
	lwz r0, 0x4(r6)
	add r6, r6, r0
	bdnz @18
	@17:
	li r5, 0x0
	@21:
	lwz r4, gp(r13)
	la r3, charspace(r13)
	lbz r0, 0x1(r5)
	lwz r4, 0x16c(r4)
	add r29, r0, r29
	slwi r0, r4, 2
	lwzx r0, r3, r0
	add r29, r0, r29
	@1:
	lbz r3, 0x0(r26)
	extsb. r0, r3
	bne @2
	lmw r23, 0x20c(r1)
	lwz r0, 0x234(r1)
	mtlr r0
	addi r1, r1, 0x230
	blr
}

asm void FontDrawStringShake(f32 x, f32 y, const s8* msg) {
	nofralloc
	stwu r1, -0xf0(r1)
	mflr r0
	stw r0, 0xf4(r1)
	stfd f31, 0xe0(r1)
	psq_st f31, 0xe8(r1), 0, 0
	stfd f30, 0xd0(r1)
	psq_st f30, 0xd8(r1), 0, 0
	stfd f29, 0xc0(r1)
	psq_st f29, 0xc8(r1), 0, 0
	stfd f28, 0xb0(r1)
	psq_st f28, 0xb8(r1), 0, 0
	stmw r24, 0x90(r1)
	fmr f28, f1
	mr r24, r3
	fmr f29, f2
	bl camGetCurPtr
	la r26, fontScale(r13)
	mr r28, r3
	lfs f1, fontScale(r13)
	addi r3, r1, 0x20
	lfs f2, 0x4(r26)
	lfs f3, 0x8(r26)
	bl PSMTXScale
	lis r4, double_to_int_802c48f0@ha
	lis r3, 0x5749
	lis r5, 0x5555
	lfd f31, double_to_int_802c48f0@l(r4)
	addi r31, r3, 0x4431
	lis r30, 0x4330
	addi r29, r5, 0x5556
	b @1
	@2:
	extsb r3, r3
	bl _ismbblead
	cmpwi r3, 0x0
	beq @3
	lhz r3, 0x0(r24)
	bl JUTFont_CodeToGlyph
	mr r25, r3
	addi r24, r24, 0x2
	b @4
	@3:
	lbz r0, 0x0(r24)
	addi r24, r24, 0x1
	extsb r3, r0
	bl JUTFont_CodeToGlyph
	mr r25, r3
	@4:
	li r3, 0x2710
	bl irand
	mulhw r4, r29, r3
	stw r30, 0x80(r1)
	lfs f0, fontScale(r13)
	srwi r0, r4, 31
	add r0, r4, r0
	mulli r0, r0, 0x3
	subf r0, r0, r3
	li r3, 0x2710
	xoris r0, r0, 0x8000
	stw r0, 0x84(r1)
	lfd f1, 0x80(r1)
	fsubs f1, f1, f31
	fmadds f30, f0, f1, f28
	bl irand
	mulhw r5, r29, r3
	lwz r7, pfh(r13)
	stw r30, 0x88(r1)
	clrlwi r4, r25, 16
	lfs f0, 0x4(r26)
	addi r6, r7, 0x20
	srwi r0, r5, 31
	lwz r7, 0xc(r7)
	add r0, r5, r0
	mulli r0, r0, 0x3
	subf r0, r0, r3
	xoris r0, r0, 0x8000
	stw r0, 0x8c(r1)
	lfd f1, 0x88(r1)
	fsubs f1, f1, f31
	fmadds f2, f0, f1, f29
	mtctr r7
	cmplwi r7, 0x0
	ble @5
	@6:
	lwz r0, 0x0(r6)
	cmpw r0, r31
	beq @7
	b @8
	@7:
	lhz r3, 0x8(r6)
	cmplw r4, r3
	blt @8
	lhz r0, 0xa(r6)
	cmplw r4, r0
	bgt @8
	subf r0, r3, r4
	slwi r3, r0, 1
	addi r3, r3, 0xc
	add r3, r6, r3
	b @9
	@8:
	lwz r0, 0x4(r6)
	add r6, r6, r0
	bdnz @6
	@5:
	li r3, 0x0
	@9:
	fmr f1, f30
	lbz r27, 0x1(r3)
	lfs f3, float_0_8041a300(r2)
	addi r3, r1, 0x20
	addi r4, r1, 0x50
	bl PSMTXTransApply
	addi r4, r1, 0x50
	addi r3, r28, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x50
	li r4, 0x0
	bl GXLoadPosMtxImm
	lwz r0, fontEdge(r13)
	cmpwi r0, 0x0
	beq @10
	lwz r7, fontColTbl(r13)
	lis r3, 0x8081
	lwz r8, fontColor(r13)
	subi r6, r3, 0x7f7f
	stw r7, 0x14(r1)
	addi r4, r1, 0xc
	lbz r0, fontAlpha(r13)
	li r3, 0x1
	lbz r5, 0x17(r1)
	stw r8, 0x18(r1)
	mullw r0, r5, r0
	stw r7, 0x8(r1)
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x17(r1)
	lwz r0, 0x14(r1)
	stw r0, 0xc(r1)
	bl GXSetTevColor
	mr r3, r25
	li r4, -0x2
	li r5, 0x0
	bl _JUTFont_DrawPos
	mr r3, r25
	li r4, 0x2
	li r5, 0x0
	bl _JUTFont_DrawPos
	mr r3, r25
	li r4, 0x0
	li r5, -0x2
	bl _JUTFont_DrawPos
	mr r3, r25
	li r4, 0x0
	li r5, 0x2
	bl _JUTFont_DrawPos
	lwz r7, 0x18(r1)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x1c(r1)
	addi r4, r1, 0x10
	li r3, 0x1
	lbz r5, 0x1f(r1)
	stw r7, fontColor(r13)
	mullw r0, r5, r0
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x1f(r1)
	lwz r0, 0x1c(r1)
	stw r0, 0x10(r1)
	bl GXSetTevColor
	@10:
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	bl _JUTFont_DrawPos
	lwz r4, gp(r13)
	la r3, charspace(r13)
	stw r30, 0x88(r1)
	lwz r0, 0x16c(r4)
	lfs f1, fontScale(r13)
	slwi r0, r0, 2
	lwzx r0, r3, r0
	add r0, r27, r0
	xoris r0, r0, 0x8000
	stw r0, 0x8c(r1)
	lfd f0, 0x88(r1)
	fsubs f0, f0, f31
	fmadds f28, f1, f0, f28
	@1:
	lbz r3, 0x0(r24)
	extsb. r0, r3
	bne @2
	psq_l f31, 0xe8(r1), 0, 0
	lfd f31, 0xe0(r1)
	psq_l f30, 0xd8(r1), 0, 0
	lfd f30, 0xd0(r1)
	psq_l f29, 0xc8(r1), 0, 0
	lfd f29, 0xc0(r1)
	psq_l f28, 0xb8(r1), 0, 0
	lfd f28, 0xb0(r1)
	lmw r24, 0x90(r1)
	lwz r0, 0xf4(r1)
	mtlr r0
	addi r1, r1, 0xf0
	blr
}

asm void FontDrawStringCenterMtx(Mtx mtx, const s8* msg) {
	nofralloc
	stwu r1, -0xa0(r1)
	mflr r0
	stw r0, 0xa4(r1)
	stfd f31, 0x90(r1)
	psq_st f31, 0x98(r1), 0, 0
	stfd f30, 0x80(r1)
	psq_st f30, 0x88(r1), 0, 0
	stmw r27, 0x6c(r1)
	mr r27, r3
	mr r29, r4
	bl camGetCurPtr
	mr r28, r3
	mr r3, r29
	li r4, 0x0
	bl FontGetMessageWidthLine
	clrlwi r4, r3, 16
	lis r0, 0x4330
	stw r4, 0x54(r1)
	lis r3, double_to_int_mask_802c48e8@ha
	lfd f2, double_to_int_mask_802c48e8@l(r3)
	mr r4, r27
	stw r0, 0x50(r1)
	addi r3, r28, 0x11c
	lfs f0, float_0p5_8041a328(r2)
	addi r5, r1, 0x20
	lfd f1, 0x50(r1)
	fsubs f1, f1, f2
	fneg f1, f1
	fmuls f30, f0, f1
	bl PSMTXConcat
	addi r3, r1, 0x20
	li r4, 0x0
	bl GXLoadPosMtxImm
	lis r3, double_to_int_802c48f0@ha
	lis r4, 0x5749
	lfd f31, double_to_int_802c48f0@l(r3)
	lis r28, 0x4330
	addi r31, r4, 0x4431
	b @1
	@2:
	extsb r3, r3
	bl _ismbblead
	cmpwi r3, 0x0
	beq @3
	lhz r3, 0x0(r29)
	bl JUTFont_CodeToGlyph
	mr r30, r3
	addi r29, r29, 0x2
	b @4
	@3:
	lbz r0, 0x0(r29)
	addi r29, r29, 0x1
	extsb r3, r0
	bl JUTFont_CodeToGlyph
	mr r30, r3
	@4:
	lwz r0, fontEdge(r13)
	cmpwi r0, 0x0
	beq @5
	lwz r7, fontColTbl(r13)
	lis r3, 0x8081
	lwz r8, fontColor(r13)
	subi r6, r3, 0x7f7f
	stw r7, 0x14(r1)
	addi r4, r1, 0xc
	lbz r0, fontAlpha(r13)
	li r3, 0x1
	lbz r5, 0x17(r1)
	stw r8, 0x18(r1)
	mullw r0, r5, r0
	stw r7, 0x8(r1)
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x17(r1)
	lwz r0, 0x14(r1)
	stw r0, 0xc(r1)
	bl GXSetTevColor
	fctiwz f0, f30
	mr r3, r30
	li r5, 0x0
	stfd f0, 0x50(r1)
	lwz r0, 0x54(r1)
	extsh r27, r0
	subi r0, r27, 0x2
	extsh r4, r0
	bl _JUTFont_DrawPos
	addi r0, r27, 0x2
	mr r3, r30
	extsh r4, r0
	li r5, 0x0
	bl _JUTFont_DrawPos
	fctiwz f0, f30
	mr r3, r30
	li r5, -0x2
	stfd f0, 0x58(r1)
	lwz r0, 0x5c(r1)
	extsh r27, r0
	mr r4, r27
	bl _JUTFont_DrawPos
	mr r3, r30
	mr r4, r27
	li r5, 0x2
	bl _JUTFont_DrawPos
	lwz r7, 0x18(r1)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x1c(r1)
	addi r4, r1, 0x10
	li r3, 0x1
	lbz r5, 0x1f(r1)
	stw r7, fontColor(r13)
	mullw r0, r5, r0
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x1f(r1)
	lwz r0, 0x1c(r1)
	stw r0, 0x10(r1)
	bl GXSetTevColor
	@5:
	fctiwz f0, f30
	mr r3, r30
	li r5, 0x0
	stfd f0, 0x58(r1)
	lwz r4, 0x5c(r1)
	bl _JUTFont_DrawPos
	lwz r4, pfh(r13)
	clrlwi r3, r30, 16
	lwz r0, 0xc(r4)
	addi r4, r4, 0x20
	mtctr r0
	cmplwi r0, 0x0
	ble @6
	@7:
	lwz r0, 0x0(r4)
	cmpw r0, r31
	beq @8
	b @9
	@8:
	lhz r5, 0x8(r4)
	cmplw r3, r5
	blt @9
	lhz r0, 0xa(r4)
	cmplw r3, r0
	bgt @9
	subf r0, r5, r3
	slwi r3, r0, 1
	addi r5, r3, 0xc
	add r5, r4, r5
	b @10
	@9:
	lwz r0, 0x4(r4)
	add r4, r4, r0
	bdnz @7
	@6:
	li r5, 0x0
	@10:
	lwz r4, gp(r13)
	la r3, charspace(r13)
	lbz r0, 0x1(r5)
	lwz r4, 0x16c(r4)
	stw r28, 0x58(r1)
	slwi r4, r4, 2
	lwzx r3, r3, r4
	add r0, r3, r0
	xoris r0, r0, 0x8000
	stw r0, 0x5c(r1)
	lfd f0, 0x58(r1)
	fsubs f0, f0, f31
	fadds f30, f30, f0
	@1:
	lbz r3, 0x0(r29)
	extsb. r0, r3
	bne @2
	psq_l f31, 0x98(r1), 0, 0
	lfd f31, 0x90(r1)
	psq_l f30, 0x88(r1), 0, 0
	lfd f30, 0x80(r1)
	lmw r27, 0x6c(r1)
	lwz r0, 0xa4(r1)
	mtlr r0
	addi r1, r1, 0xa0
	blr
}

asm void FontDrawStringMtx(Mtx mtx, const char* msg) {
	nofralloc
	stwu r1, -0x1b0(r1)
	mflr r0
	stw r0, 0x1b4(r1)
	stfd f31, 0x1a0(r1)
	psq_st f31, 0x1a8(r1), 0, 0
	stfd f30, 0x190(r1)
	psq_st f30, 0x198(r1), 0, 0
	stmw r27, 0x17c(r1)
	mr r27, r3
	mr r29, r4
	bl camGetCurPtr
	lfs f31, float_0_8041a300(r2)
	mr r4, r27
	addi r5, r1, 0x20
	addi r3, r3, 0x11c
	fmr f30, f31
	bl PSMTXConcat
	addi r3, r1, 0x20
	li r4, 0x0
	bl GXLoadPosMtxImm
	lis r31, 0x1
	b @1
	@2:
	subi r30, r31, 0x1
	extsb r3, r3
	bl _ismbblead
	cmpwi r3, 0x0
	beq @3
	lhz r3, 0x0(r29)
	bl JUTFont_CodeToGlyph
	mr r30, r3
	addi r29, r29, 0x2
	b @4
	@3:
	lbz r0, 0x0(r29)
	extsb r0, r0
	cmpwi r0, 0x3c
	beq @5
	bge @6
	cmpwi r0, 0xa
	beq @7
	b @6
	@7:
	lfs f0, float_28_8041a33c(r2)
	addi r29, r29, 0x1
	lfs f31, float_0_8041a300(r2)
	fsubs f30, f30, f0
	b @4
	@5:
	addi r3, r29, 0x1
	addi r4, r1, 0xd0
	addi r5, r1, 0x50
	bl msgGetCommand
	lbz r0, 0xd0(r1)
	mr r29, r3
	extsb r0, r0
	cmpwi r0, 0x52
	beq @4
	cmpwi r0, 0x2f
	bne @8
	cmplwi r0, 0x2f72
	beq @4
	@8:
	lbz r0, 0x0(r29)
	cmpwi r0, 0xa
	bne @4
	addi r29, r29, 0x1
	b @4
	@6:
	lbz r0, 0x0(r29)
	addi r29, r29, 0x1
	extsb r3, r0
	bl JUTFont_CodeToGlyph
	mr r30, r3
	@4:
	clrlwi r0, r30, 16
	cmplwi r0, 0xffff
	beq @1
	lwz r0, fontEdge(r13)
	cmpwi r0, 0x0
	beq @9
	lwz r7, fontColTbl(r13)
	lis r3, 0x8081
	lwz r8, fontColor(r13)
	subi r6, r3, 0x7f7f
	stw r7, 0x14(r1)
	addi r4, r1, 0xc
	lbz r0, fontAlpha(r13)
	li r3, 0x1
	lbz r5, 0x17(r1)
	stw r8, 0x18(r1)
	mullw r0, r5, r0
	stw r7, 0x8(r1)
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x17(r1)
	lwz r0, 0x14(r1)
	stw r0, 0xc(r1)
	bl GXSetTevColor
	fctiwz f1, f31
	mr r3, r30
	fctiwz f0, f30
	stfd f1, 0x150(r1)
	stfd f0, 0x158(r1)
	lwz r4, 0x154(r1)
	lwz r0, 0x15c(r1)
	extsh r27, r4
	subi r4, r27, 0x2
	extsh r28, r0
	mr r5, r28
	extsh r4, r4
	bl _JUTFont_DrawPos
	addi r0, r27, 0x2
	mr r3, r30
	mr r5, r28
	extsh r4, r0
	bl _JUTFont_DrawPos
	fctiwz f0, f30
	mr r3, r30
	fctiwz f1, f31
	stfd f0, 0x168(r1)
	stfd f1, 0x160(r1)
	lwz r0, 0x16c(r1)
	lwz r4, 0x164(r1)
	extsh r27, r0
	extsh r28, r4
	subi r0, r27, 0x2
	mr r4, r28
	extsh r5, r0
	bl _JUTFont_DrawPos
	addi r0, r27, 0x2
	mr r3, r30
	mr r4, r28
	extsh r5, r0
	bl _JUTFont_DrawPos
	lwz r7, 0x18(r1)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x1c(r1)
	addi r4, r1, 0x10
	li r3, 0x1
	lbz r5, 0x1f(r1)
	stw r7, fontColor(r13)
	mullw r0, r5, r0
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x1f(r1)
	lwz r0, 0x1c(r1)
	stw r0, 0x10(r1)
	bl GXSetTevColor
	@9:
	fctiwz f1, f31
	mr r3, r30
	fctiwz f0, f30
	stfd f1, 0x168(r1)
	stfd f0, 0x160(r1)
	lwz r4, 0x16c(r1)
	lwz r5, 0x164(r1)
	bl _JUTFont_DrawPos
	lwz r5, pfh(r13)
	lis r3, 0x5749
	addi r4, r3, 0x4431
	clrlwi r3, r30, 16
	lwz r0, 0xc(r5)
	addi r5, r5, 0x20
	mtctr r0
	cmplwi r0, 0x0
	ble @10
	@11:
	lwz r0, 0x0(r5)
	cmpw r0, r4
	beq @12
	b @13
	@12:
	lhz r6, 0x8(r5)
	cmplw r3, r6
	blt @13
	lhz r0, 0xa(r5)
	cmplw r3, r0
	bgt @13
	subf r0, r6, r3
	slwi r3, r0, 1
	addi r7, r3, 0xc
	add r7, r5, r7
	b @14
	@13:
	lwz r0, 0x4(r5)
	add r5, r5, r0
	bdnz @11
	@10:
	li r7, 0x0
	@14:
	lwz r4, gp(r13)
	lis r0, 0x4330
	lis r3, double_to_int_802c48f0@ha
	la r5, charspace(r13)
	lwz r6, 0x16c(r4)
	lbz r4, 0x1(r7)
	slwi r6, r6, 2
	stw r0, 0x168(r1)
	lwzx r0, r5, r6
	lfd f1, double_to_int_802c48f0@l(r3)
	add r0, r0, r4
	xoris r0, r0, 0x8000
	stw r0, 0x16c(r1)
	lfd f0, 0x168(r1)
	fsubs f0, f0, f1
	fadds f31, f31, f0
	@1:
	lbz r3, 0x0(r29)
	extsb. r0, r3
	bne @2
	psq_l f31, 0x1a8(r1), 0, 0
	lfd f31, 0x1a0(r1)
	psq_l f30, 0x198(r1), 0, 0
	lfd f30, 0x190(r1)
	lmw r27, 0x17c(r1)
	lwz r0, 0x1b4(r1)
	mtlr r0
	addi r1, r1, 0x1b0
	blr
}

asm void FontDrawStringVecPitch(Vec pos, f32 pitch, const s8* msg) {
	nofralloc
	stwu r1, -0xd0(r1)
	mflr r0
	stw r0, 0xd4(r1)
	stfd f31, 0xc0(r1)
	psq_st f31, 0xc8(r1), 0, 0
	stfd f30, 0xb0(r1)
	psq_st f30, 0xb8(r1), 0, 0
	stfd f29, 0xa0(r1)
	psq_st f29, 0xa8(r1), 0, 0
	stmw r26, 0x88(r1)
	fmr f29, f1
	mr r26, r3
	mr r27, r4
	bl camGetCurPtr
	la r4, fontScale(r13)
	mr r30, r3
	lfs f30, 0x0(r26)
	addi r3, r1, 0x20
	lfs f1, fontScale(r13)
	lfs f2, 0x4(r4)
	lfs f3, 0x8(r4)
	bl PSMTXScale
	lis r3, 0x5749
	lfs f31, float_0_8041a300(r2)
	addi r31, r3, 0x4431
	b @1
	@2:
	extsb r3, r3
	bl _ismbblead
	cmpwi r3, 0x0
	beq @3
	lhz r3, 0x0(r27)
	bl JUTFont_CodeToGlyph
	mr r28, r3
	addi r27, r27, 0x2
	b @4
	@3:
	lbz r0, 0x0(r27)
	addi r27, r27, 0x1
	extsb r3, r0
	bl JUTFont_CodeToGlyph
	mr r28, r3
	@4:
	lwz r4, pfh(r13)
	clrlwi r3, r28, 16
	lwz r0, 0xc(r4)
	addi r4, r4, 0x20
	mtctr r0
	cmplwi r0, 0x0
	ble @5
	@6:
	lwz r0, 0x0(r4)
	cmpw r0, r31
	beq @7
	b @8
	@7:
	lhz r5, 0x8(r4)
	cmplw r3, r5
	blt @8
	lhz r0, 0xa(r4)
	cmplw r3, r0
	bgt @8
	subf r0, r5, r3
	slwi r3, r0, 1
	addi r3, r3, 0xc
	add r3, r4, r3
	b @9
	@8:
	lwz r0, 0x4(r4)
	add r4, r4, r0
	bdnz @6
	@5:
	li r3, 0x0
	@9:
	fcmpo cr0, f29, f31
	lbz r29, 0x1(r3)
	addi r3, r1, 0x20
	addi r4, r1, 0x50
	bge @10
	fmr f1, f30
	b @11
	@10:
	lis r0, 0x4330
	lis r5, double_to_int_mask_802c48e8@ha
	stw r29, 0x84(r1)
	lfd f1, double_to_int_mask_802c48e8@l(r5)
	stw r0, 0x80(r1)
	lfs f2, float_0p5_8041a328(r2)
	lfd f0, 0x80(r1)
	lfs f3, fontScale(r13)
	fsubs f0, f0, f1
	fsubs f0, f29, f0
	fmuls f0, f2, f0
	fmadds f1, f3, f0, f30
	@11:
	lfs f2, 0x4(r26)
	lfs f3, 0x8(r26)
	bl PSMTXTransApply
	addi r4, r1, 0x50
	addi r3, r30, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x50
	li r4, 0x0
	bl GXLoadPosMtxImm
	lwz r0, fontEdge(r13)
	cmpwi r0, 0x0
	beq @12
	lwz r7, fontColTbl(r13)
	lis r3, 0x8081
	lwz r8, fontColor(r13)
	subi r6, r3, 0x7f7f
	stw r7, 0x14(r1)
	addi r4, r1, 0xc
	lbz r0, fontAlpha(r13)
	li r3, 0x1
	lbz r5, 0x17(r1)
	stw r8, 0x18(r1)
	mullw r0, r5, r0
	stw r7, 0x8(r1)
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x17(r1)
	lwz r0, 0x14(r1)
	stw r0, 0xc(r1)
	bl GXSetTevColor
	mr r3, r28
	li r4, -0x2
	li r5, 0x0
	bl _JUTFont_DrawPos
	mr r3, r28
	li r4, 0x2
	li r5, 0x0
	bl _JUTFont_DrawPos
	mr r3, r28
	li r4, 0x0
	li r5, -0x2
	bl _JUTFont_DrawPos
	mr r3, r28
	li r4, 0x0
	li r5, 0x2
	bl _JUTFont_DrawPos
	lwz r7, 0x18(r1)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x1c(r1)
	addi r4, r1, 0x10
	li r3, 0x1
	lbz r5, 0x1f(r1)
	stw r7, fontColor(r13)
	mullw r0, r5, r0
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x1f(r1)
	lwz r0, 0x1c(r1)
	stw r0, 0x10(r1)
	bl GXSetTevColor
	@12:
	mr r3, r28
	li r4, 0x0
	li r5, 0x0
	bl _JUTFont_DrawPos
	fcmpo cr0, f29, f31
	bge @13
	lwz r5, gp(r13)
	lis r0, 0x4330
	lis r3, double_to_int_802c48f0@ha
	la r4, charspace(r13)
	lwz r5, 0x16c(r5)
	stw r0, 0x80(r1)
	slwi r0, r5, 2
	lfd f1, double_to_int_802c48f0@l(r3)
	lwzx r0, r4, r0
	lfs f2, fontScale(r13)
	add r0, r29, r0
	xoris r0, r0, 0x8000
	stw r0, 0x84(r1)
	lfd f0, 0x80(r1)
	fsubs f0, f0, f1
	fmadds f30, f2, f0, f30
	b @1
	@13:
	lfs f0, fontScale(r13)
	fmadds f30, f29, f0, f30
	@1:
	lbz r3, 0x0(r27)
	extsb. r0, r3
	bne @2
	psq_l f31, 0xc8(r1), 0, 0
	lfd f31, 0xc0(r1)
	psq_l f30, 0xb8(r1), 0, 0
	lfd f30, 0xb0(r1)
	psq_l f29, 0xa8(r1), 0, 0
	lfd f29, 0xa0(r1)
	lmw r26, 0x88(r1)
	lwz r0, 0xd4(r1)
	mtlr r0
	addi r1, r1, 0xd0
	blr
}

asm void FontDrawStringPitch(f32 x, f32 y, f32 pitch, const char* msg) {
	nofralloc
	stwu r1, -0x110(r1)
	mflr r0
	stw r0, 0x114(r1)
	stfd f31, 0x100(r1)
	psq_st f31, 0x108(r1), 0, 0
	stfd f30, 0xf0(r1)
	psq_st f30, 0xf8(r1), 0, 0
	stfd f29, 0xe0(r1)
	psq_st f29, 0xe8(r1), 0, 0
	stfd f28, 0xd0(r1)
	psq_st f28, 0xd8(r1), 0, 0
	stfd f27, 0xc0(r1)
	psq_st f27, 0xc8(r1), 0, 0
	stmw r27, 0xac(r1)
	lis r4, vec3_802c48d8@ha
	mr r28, r3
	addi r5, r4, vec3_802c48d8@l
	fmr f27, f3
	lwz r4, 0x0(r5)
	lwz r0, 0x4(r5)
	stw r4, 0x20(r1)
	lwz r4, 0x8(r5)
	stw r0, 0x24(r1)
	stfs f1, 0x20(r1)
	stfs f2, 0x24(r1)
	lwz r3, 0x20(r1)
	lwz r0, 0x24(r1)
	stw r4, 0x28(r1)
	stw r3, 0x2c(r1)
	stw r0, 0x30(r1)
	stw r4, 0x34(r1)
	bl camGetCurPtr
	la r4, fontScale(r13)
	mr r30, r3
	lfs f30, 0x2c(r1)
	addi r3, r1, 0x68
	lfs f1, fontScale(r13)
	lfs f2, 0x4(r4)
	lfs f3, 0x8(r4)
	bl PSMTXScale
	lis r3, 0x5749
	lfs f29, 0x34(r1)
	lfs f28, 0x30(r1)
	addi r31, r3, 0x4431
	lfs f31, float_0_8041a300(r2)
	b @1
	@2:
	extsb r3, r3
	bl _ismbblead
	cmpwi r3, 0x0
	beq @3
	lhz r3, 0x0(r28)
	bl JUTFont_CodeToGlyph
	mr r29, r3
	addi r28, r28, 0x2
	b @4
	@3:
	lbz r0, 0x0(r28)
	addi r28, r28, 0x1
	extsb r3, r0
	bl JUTFont_CodeToGlyph
	mr r29, r3
	@4:
	lwz r4, pfh(r13)
	clrlwi r3, r29, 16
	lwz r0, 0xc(r4)
	addi r4, r4, 0x20
	mtctr r0
	cmplwi r0, 0x0
	ble @5
	@6:
	lwz r0, 0x0(r4)
	cmpw r0, r31
	beq @7
	b @8
	@7:
	lhz r5, 0x8(r4)
	cmplw r3, r5
	blt @8
	lhz r0, 0xa(r4)
	cmplw r3, r0
	bgt @8
	subf r0, r5, r3
	slwi r3, r0, 1
	addi r3, r3, 0xc
	add r3, r4, r3
	b @9
	@8:
	lwz r0, 0x4(r4)
	add r4, r4, r0
	bdnz @6
	@5:
	li r3, 0x0
	@9:
	fcmpo cr0, f27, f31
	lbz r27, 0x1(r3)
	addi r3, r1, 0x68
	addi r4, r1, 0x38
	bge @10
	fmr f1, f30
	b @11
	@10:
	lis r0, 0x4330
	lis r5, double_to_int_mask_802c48e8@ha
	stw r27, 0x9c(r1)
	lfd f1, double_to_int_mask_802c48e8@l(r5)
	stw r0, 0x98(r1)
	lfs f2, float_0p5_8041a328(r2)
	lfd f0, 0x98(r1)
	lfs f3, fontScale(r13)
	fsubs f0, f0, f1
	fsubs f0, f27, f0
	fmuls f0, f2, f0
	fmadds f1, f3, f0, f30
	@11:
	fmr f2, f28
	fmr f3, f29
	bl PSMTXTransApply
	addi r4, r1, 0x38
	addi r3, r30, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x38
	li r4, 0x0
	bl GXLoadPosMtxImm
	lwz r0, fontEdge(r13)
	cmpwi r0, 0x0
	beq @12
	lwz r7, fontColTbl(r13)
	lis r3, 0x8081
	lwz r8, fontColor(r13)
	subi r6, r3, 0x7f7f
	stw r7, 0x14(r1)
	addi r4, r1, 0xc
	lbz r0, fontAlpha(r13)
	li r3, 0x1
	lbz r5, 0x17(r1)
	stw r8, 0x18(r1)
	mullw r0, r5, r0
	stw r7, 0x8(r1)
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x17(r1)
	lwz r0, 0x14(r1)
	stw r0, 0xc(r1)
	bl GXSetTevColor
	mr r3, r29
	li r4, -0x2
	li r5, 0x0
	bl _JUTFont_DrawPos
	mr r3, r29
	li r4, 0x2
	li r5, 0x0
	bl _JUTFont_DrawPos
	mr r3, r29
	li r4, 0x0
	li r5, -0x2
	bl _JUTFont_DrawPos
	mr r3, r29
	li r4, 0x0
	li r5, 0x2
	bl _JUTFont_DrawPos
	lwz r7, 0x18(r1)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x1c(r1)
	addi r4, r1, 0x10
	li r3, 0x1
	lbz r5, 0x1f(r1)
	stw r7, fontColor(r13)
	mullw r0, r5, r0
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x1f(r1)
	lwz r0, 0x1c(r1)
	stw r0, 0x10(r1)
	bl GXSetTevColor
	@12:
	mr r3, r29
	li r4, 0x0
	li r5, 0x0
	bl _JUTFont_DrawPos
	fcmpo cr0, f27, f31
	bge @13
	lwz r5, gp(r13)
	lis r0, 0x4330
	lis r3, double_to_int_802c48f0@ha
	la r4, charspace(r13)
	lwz r5, 0x16c(r5)
	stw r0, 0x98(r1)
	slwi r0, r5, 2
	lfd f1, double_to_int_802c48f0@l(r3)
	lwzx r0, r4, r0
	lfs f2, fontScale(r13)
	add r0, r27, r0
	xoris r0, r0, 0x8000
	stw r0, 0x9c(r1)
	lfd f0, 0x98(r1)
	fsubs f0, f0, f1
	fmadds f30, f2, f0, f30
	b @1
	@13:
	lfs f0, fontScale(r13)
	fmadds f30, f27, f0, f30
	@1:
	lbz r3, 0x0(r28)
	extsb. r0, r3
	bne @2
	psq_l f31, 0x108(r1), 0, 0
	lfd f31, 0x100(r1)
	psq_l f30, 0xf8(r1), 0, 0
	lfd f30, 0xf0(r1)
	psq_l f29, 0xe8(r1), 0, 0
	lfd f29, 0xe0(r1)
	psq_l f28, 0xd8(r1), 0, 0
	lfd f28, 0xd0(r1)
	psq_l f27, 0xc8(r1), 0, 0
	lfd f27, 0xc0(r1)
	lmw r27, 0xac(r1)
	lwz r0, 0x114(r1)
	mtlr r0
	addi r1, r1, 0x110
	blr
}

asm void FontDrawString(f32 x, f32 y, const char* msg) {
	nofralloc
	stwu r1, -0x100(r1)
	mflr r0
	stw r0, 0x104(r1)
	stfd f31, 0xf0(r1)
	psq_st f31, 0xf8(r1), 0, 0
	stfd f30, 0xe0(r1)
	psq_st f30, 0xe8(r1), 0, 0
	stfd f29, 0xd0(r1)
	psq_st f29, 0xd8(r1), 0, 0
	stfd f28, 0xc0(r1)
	psq_st f28, 0xc8(r1), 0, 0
	stmw r26, 0xa8(r1)
	lis r4, vec3_802c48cc@ha
	mr r28, r3
	addi r5, r4, vec3_802c48cc@l
	lwz r4, 0x0(r5)
	lwz r0, 0x4(r5)
	stw r4, 0x20(r1)
	lwz r4, 0x8(r5)
	stw r0, 0x24(r1)
	stfs f1, 0x20(r1)
	stfs f2, 0x24(r1)
	lwz r3, 0x20(r1)
	lwz r0, 0x24(r1)
	stw r4, 0x28(r1)
	stw r3, 0x2c(r1)
	stw r0, 0x30(r1)
	stw r4, 0x34(r1)
	bl camGetCurPtr
	la r4, fontScale(r13)
	mr r30, r3
	lfs f30, 0x2c(r1)
	addi r3, r1, 0x68
	lfs f1, fontScale(r13)
	lfs f2, 0x4(r4)
	lfs f3, 0x8(r4)
	bl PSMTXScale
	lis r3, double_to_int_802c48f0@ha
	lis r4, 0x5749
	lfs f29, 0x34(r1)
	addi r31, r4, 0x4431
	lfs f28, 0x30(r1)
	lis r26, 0x4330
	lfd f31, double_to_int_802c48f0@l(r3)
	b @1
	@2:
	extsb r3, r3
	bl _ismbblead
	cmpwi r3, 0x0
	beq @3
	lhz r3, 0x0(r28)
	bl JUTFont_CodeToGlyph
	mr r29, r3
	addi r28, r28, 0x2
	b @4
	@3:
	lbz r0, 0x0(r28)
	addi r28, r28, 0x1
	extsb r3, r0
	bl JUTFont_CodeToGlyph
	mr r29, r3
	@4:
	lwz r4, pfh(r13)
	clrlwi r3, r29, 16
	lwz r0, 0xc(r4)
	addi r4, r4, 0x20
	mtctr r0
	cmplwi r0, 0x0
	ble @5
	@6:
	lwz r0, 0x0(r4)
	cmpw r0, r31
	beq @7
	b @8
	@7:
	lhz r5, 0x8(r4)
	cmplw r3, r5
	blt @8
	lhz r0, 0xa(r4)
	cmplw r3, r0
	bgt @8
	subf r0, r5, r3
	slwi r3, r0, 1
	addi r3, r3, 0xc
	add r3, r4, r3
	b @9
	@8:
	lwz r0, 0x4(r4)
	add r4, r4, r0
	bdnz @6
	@5:
	li r3, 0x0
	@9:
	fmr f1, f30
	lbz r27, 0x1(r3)
	fmr f2, f28
	addi r3, r1, 0x68
	fmr f3, f29
	addi r4, r1, 0x38
	bl PSMTXTransApply
	addi r4, r1, 0x38
	addi r3, r30, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x38
	li r4, 0x0
	bl GXLoadPosMtxImm
	lwz r0, fontEdge(r13)
	cmpwi r0, 0x0
	beq @10
	lwz r7, fontColTbl(r13)
	lis r3, 0x8081
	lwz r8, fontColor(r13)
	subi r6, r3, 0x7f7f
	stw r7, 0x14(r1)
	addi r4, r1, 0xc
	lbz r0, fontAlpha(r13)
	li r3, 0x1
	lbz r5, 0x17(r1)
	stw r8, 0x18(r1)
	mullw r0, r5, r0
	stw r7, 0x8(r1)
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x17(r1)
	lwz r0, 0x14(r1)
	stw r0, 0xc(r1)
	bl GXSetTevColor
	mr r3, r29
	li r4, -0x2
	li r5, 0x0
	bl _JUTFont_DrawPos
	mr r3, r29
	li r4, 0x2
	li r5, 0x0
	bl _JUTFont_DrawPos
	mr r3, r29
	li r4, 0x0
	li r5, -0x2
	bl _JUTFont_DrawPos
	mr r3, r29
	li r4, 0x0
	li r5, 0x2
	bl _JUTFont_DrawPos
	lwz r7, 0x18(r1)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x1c(r1)
	addi r4, r1, 0x10
	li r3, 0x1
	lbz r5, 0x1f(r1)
	stw r7, fontColor(r13)
	mullw r0, r5, r0
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x1f(r1)
	lwz r0, 0x1c(r1)
	stw r0, 0x10(r1)
	bl GXSetTevColor
	@10:
	mr r3, r29
	li r4, 0x0
	li r5, 0x0
	bl _JUTFont_DrawPos
	lwz r4, gp(r13)
	la r3, charspace(r13)
	stw r26, 0x98(r1)
	lwz r0, 0x16c(r4)
	lfs f1, fontScale(r13)
	slwi r0, r0, 2
	lwzx r0, r3, r0
	add r0, r27, r0
	xoris r0, r0, 0x8000
	stw r0, 0x9c(r1)
	lfd f0, 0x98(r1)
	fsubs f0, f0, f31
	fmadds f30, f1, f0, f30
	@1:
	lbz r3, 0x0(r28)
	extsb. r0, r3
	bne @2
	psq_l f31, 0xf8(r1), 0, 0
	lfd f31, 0xf0(r1)
	psq_l f30, 0xe8(r1), 0, 0
	lfd f30, 0xe0(r1)
	psq_l f29, 0xd8(r1), 0, 0
	lfd f29, 0xd0(r1)
	psq_l f28, 0xc8(r1), 0, 0
	lfd f28, 0xc0(r1)
	lmw r26, 0xa8(r1)
	lwz r0, 0x104(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}

asm void FontDrawCodeMtx(Mtx mtx, u16 code) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	mr r31, r4
	stw r30, 0x28(r1)
	mr r30, r3
	bl camGetCurPtr
	mr r4, r30
	mr r5, r30
	addi r3, r3, 0x11c
	bl PSMTXConcat
	mr r3, r30
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	lwz r0, fontEdge(r13)
	cmpwi r0, 0x0
	beq @1
	lwz r7, fontColTbl(r13)
	lis r3, 0x8081
	lwz r8, fontColor(r13)
	subi r6, r3, 0x7f7f
	stw r7, 0x14(r1)
	addi r4, r1, 0xc
	lbz r0, fontAlpha(r13)
	li r3, 0x1
	lbz r5, 0x17(r1)
	stw r8, 0x18(r1)
	mullw r0, r5, r0
	stw r7, 0x8(r1)
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x17(r1)
	lwz r0, 0x14(r1)
	stw r0, 0xc(r1)
	bl GXSetTevColor
	mr r3, r31
	li r4, -0x2
	li r5, 0x0
	bl _JUTFont_DrawPos
	mr r3, r31
	li r4, 0x2
	li r5, 0x0
	bl _JUTFont_DrawPos
	mr r3, r31
	li r4, 0x0
	li r5, -0x2
	bl _JUTFont_DrawPos
	mr r3, r31
	li r4, 0x0
	li r5, 0x2
	bl _JUTFont_DrawPos
	lwz r7, 0x18(r1)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x1c(r1)
	addi r4, r1, 0x10
	li r3, 0x1
	lbz r5, 0x1f(r1)
	stw r7, fontColor(r13)
	mullw r0, r5, r0
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x1f(r1)
	lwz r0, 0x1c(r1)
	stw r0, 0x10(r1)
	bl GXSetTevColor
	@1:
	mr r3, r31
	li r4, 0x0
	li r5, 0x0
	bl _JUTFont_DrawPos
	lwz r0, 0x34(r1)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void FontDrawCode(f32 x, f32 y, u16 code) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	stw r0, 0x84(r1)
	stfd f31, 0x70(r1)
	psq_st f31, 0x78(r1), 0, 0
	stfd f30, 0x60(r1)
	psq_st f30, 0x68(r1), 0, 0
	stw r31, 0x5c(r1)
	fmr f30, f1
	la r4, fontScale(r13)
	fmr f31, f2
	lfs f1, fontScale(r13)
	mr r31, r3
	lfs f2, 0x4(r4)
	lfs f3, 0x8(r4)
	addi r3, r1, 0x20
	bl PSMTXScale
	fmr f1, f30
	addi r3, r1, 0x20
	fmr f2, f31
	lfs f3, float_0_8041a300(r2)
	mr r4, r3
	bl PSMTXTransApply
	bl camGetCurPtr
	addi r4, r1, 0x20
	addi r3, r3, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x20
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	lwz r0, fontEdge(r13)
	cmpwi r0, 0x0
	beq @1
	lwz r7, fontColTbl(r13)
	lis r3, 0x8081
	lwz r8, fontColor(r13)
	subi r6, r3, 0x7f7f
	stw r7, 0x14(r1)
	addi r4, r1, 0xc
	lbz r0, fontAlpha(r13)
	li r3, 0x1
	lbz r5, 0x17(r1)
	stw r8, 0x18(r1)
	mullw r0, r5, r0
	stw r7, 0x8(r1)
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x17(r1)
	lwz r0, 0x14(r1)
	stw r0, 0xc(r1)
	bl GXSetTevColor
	mr r3, r31
	li r4, -0x2
	li r5, 0x0
	bl _JUTFont_DrawPos
	mr r3, r31
	li r4, 0x2
	li r5, 0x0
	bl _JUTFont_DrawPos
	mr r3, r31
	li r4, 0x0
	li r5, -0x2
	bl _JUTFont_DrawPos
	mr r3, r31
	li r4, 0x0
	li r5, 0x2
	bl _JUTFont_DrawPos
	lwz r7, 0x18(r1)
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0x1c(r1)
	addi r4, r1, 0x10
	li r3, 0x1
	lbz r5, 0x1f(r1)
	stw r7, fontColor(r13)
	mullw r0, r5, r0
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x1f(r1)
	lwz r0, 0x1c(r1)
	stw r0, 0x10(r1)
	bl GXSetTevColor
	@1:
	mr r3, r31
	li r4, 0x0
	li r5, 0x0
	bl _JUTFont_DrawPos
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	lwz r0, 0x84(r1)
	lwz r31, 0x5c(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm void FontDrawScaleVec(Vec scale) {
	nofralloc
	lwz r5, 0x0(r3)
	lwz r4, 0x4(r3)
	lwz r0, 0x8(r3)
	stw r5, fontScale(r13)
	stw r4, fontScale+0x4(r13)
	stw r0, fontScale+0x8(r13)
	blr
}

asm void FontDrawScale(f32 scale) {
	nofralloc
	la r3, fontScale(r13)
	stfs f1, fontScale(r13)
	stfs f1, 0x4(r3)
	stfs f1, 0x8(r3)
	blr
}

asm GXColor FontGetDrawColor(void) {
	nofralloc
	lwz r3, fontColor(r13)
	blr
}

asm void FontDrawColor_(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r3, 0x8081
	stw r0, 0x24(r1)
	subi r6, r3, 0x7f7f
	addi r4, r1, 0xc
	li r3, 0x1
	lwz r7, fontColor(r13)
	lbz r0, fontAlpha(r13)
	stw r7, 0x10(r1)
	lbz r5, 0x13(r1)
	stw r7, 0x8(r1)
	mullw r0, r5, r0
	stw r7, fontColor(r13)
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x13(r1)
	lwz r0, 0x10(r1)
	stw r0, 0xc(r1)
	bl GXSetTevColor
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void FontDrawColor(GXColor color) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, 0x8081
	lbz r5, 0x3(r3)
	stw r0, 0x14(r1)
	subi r6, r4, 0x7f7f
	lwz r7, 0x0(r3)
	addi r4, r1, 0x8
	lbz r0, fontAlpha(r13)
	stw r7, fontColor(r13)
	mullw r0, r5, r0
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x3(r3)
	lwz r0, 0x0(r3)
	li r3, 0x1
	stw r0, 0x8(r1)
	bl GXSetTevColor
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void FontDrawColorIDX(s32 idx) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	slwi r0, r3, 2
	la r3, fontColTbl(r13)
	addi r4, r1, 0x8
	lwzx r7, r3, r0
	lis r3, 0x8081
	subi r6, r3, 0x7f7f
	lbz r0, fontAlpha(r13)
	stw r7, 0xc(r1)
	li r3, 0x1
	lbz r5, 0xf(r1)
	stw r7, fontColor(r13)
	mullw r0, r5, r0
	mulhw r5, r6, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0xf(r1)
	lwz r0, 0xc(r1)
	stw r0, 0x8(r1)
	bl GXSetTevColor
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void FontDrawNoiseOff(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x1
	stw r0, 0x14(r1)
	bl GXSetNumTexGens
	li r3, 0x1
	bl GXSetNumTevStages
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void FontDrawNoise(void) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	li r3, 0x2
	stw r0, 0x44(r1)
	bl GXSetNumTexGens
	li r3, 0x2
	bl GXSetNumTevStages
	li r3, 0x1
	li r4, 0x0
	bl GXSetTevKAlphaSel
	li r3, 0x1
	li r4, 0x1
	li r5, 0x2
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x0
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x7
	li r5, 0x0
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	lwz r3, wakuTexObj(r13)
	li r4, 0x2
	addi r3, r3, 0x640
	bl GXLoadTexObj
	lfs f1, float_0p015625_8041a340(r2)
	addi r3, r1, 0x8
	lfs f3, float_1_8041a2f4(r2)
	fmr f2, f1
	bl PSMTXScale
	addi r3, r1, 0x8
	li r4, 0x21
	li r5, 0x1
	bl GXLoadTexMtxImm
	li r3, 0x1
	li r4, 0x1
	li r5, 0x5
	li r6, 0x21
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void FontDrawRainbowColorOff(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x1
	stw r0, 0x14(r1)
	bl GXSetNumTevStages
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void FontDrawRainbowColor(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x2
	stw r0, 0x14(r1)
	bl GXSetNumTevStages
	li r3, 0x1
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0xf
	li r5, 0x0
	li r6, 0xa
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x7
	li r5, 0x0
	li r6, 0x5
	li r7, 0x7
	bl GXSetTevAlphaIn
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void FontDrawEdgeOff(void) {
	nofralloc
	li r0, 0x0
	stw r0, fontEdge(r13)
	blr
}

asm void FontDrawEdge(void) {
	nofralloc
	li r0, 0x1
	stw r0, fontEdge(r13)
	blr
}

asm void FontDrawStart_alpha(u8 alpha) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r5, 0x8081
	clrlwi r7, r3, 24
	stw r0, 0x14(r1)
	lis r4, vec3_802c48c0@ha
	li r0, 0x0
	subi r9, r5, 0x7f7f
	lwz r10, fontColTbl(r13)
	lwzu r6, vec3_802c48c0@l(r4)
	stw r10, 0xc(r1)
	lwz r5, 0x4(r4)
	lbz r8, 0xf(r1)
	lwz r4, 0x8(r4)
	mullw r7, r8, r7
	stb r3, fontAlpha(r13)
	addi r3, r1, 0x8
	stw r5, fontScale+0x4(r13)
	stw r4, fontScale+0x8(r13)
	mulhw r8, r9, r7
	stw r0, fontEdge(r13)
	stw r10, fontColor(r13)
	add r5, r8, r7
	stw r6, fontScale(r13)
	srawi r4, r5, 7
	srwi r5, r4, 31
	add r0, r4, r5
	stb r0, 0xf(r1)
	lwz r0, 0xc(r1)
	stw r0, 0x8(r1)
	bl JUTFont_DrawStart
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void FontDrawStart(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r5, 0x8081
	lis r3, vec3_802c48c0@ha
	stw r0, 0x14(r1)
	addi r4, r3, vec3_802c48c0@l
	subi r8, r5, 0x7f7f
	li r0, 0x0
	lwz r10, fontColTbl(r13)
	li r9, 0xff
	lwz r5, 0x4(r4)
	addi r3, r1, 0xc
	stw r10, 0x8(r1)
	lwz r6, 0x0(r4)
	lbz r7, 0xb(r1)
	lwz r4, 0x8(r4)
	mulli r7, r7, 0xff
	stw r5, fontScale+0x4(r13)
	stw r4, fontScale+0x8(r13)
	mulhw r8, r8, r7
	stw r0, fontEdge(r13)
	stw r10, fontColor(r13)
	add r5, r8, r7
	stb r9, fontAlpha(r13)
	srawi r5, r5, 7
	srwi r4, r5, 31
	stw r6, fontScale(r13)
	add r4, r5, r4
	stb r4, 0xb(r1)
	lwz r0, 0x8(r1)
	stw r0, 0xc(r1)
	bl JUTFont_DrawStart
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void fontmgrTexSetup(void) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	stw r0, 0x94(r1)
	stw r31, 0x8c(r1)
	stw r30, 0x88(r1)
	lwz r0, pfh(r13)
	cmplwi r0, 0x0
	bne @1
	bl getMarioStDvdRoot
	lis r4, str_802C48F8@ha
	lwz r6, fontname(r13)
	mr r5, r3
	addi r3, r1, 0x8
	addi r4, r4, str_802C48F8@l
	crclr 6
	bl sprintf
	addi r3, r1, 0x8
	li r4, 0x2
	li r5, 0x0
	bl DVDMgrOpen
	mr r31, r3
	bl DVDMgrGetLength
	mr r4, r3
	li r3, 0x0
	addi r0, r4, 0x1f
	clrrwi r30, r0, 5
	mr r4, r30
	bl __memAlloc
	mr r4, r3
	mr r3, r31
	stw r4, pfh(r13)
	mr r5, r30
	li r6, 0x0
	bl DVDMgrRead
	mr r3, r31
	bl DVDMgrClose
	lwz r8, pfh(r13)
	lis r3, 0x4d41
	addi r4, r3, 0x5031
	li r6, 0x0
	addi r7, r8, 0x20
	b @2
	@3:
	lwz r5, 0x0(r7)
	cmpw r5, r4
	beq @4
	bge @5
	lis r3, 0x494e
	addi r0, r3, 0x4631
	cmpw r5, r0
	beq @6
	bge @4
	lis r3, 0x474c
	addi r0, r3, 0x5931
	cmpw r5, r0
	beq @7
	b @4
	@5:
	lis r3, 0x5749
	addi r0, r3, 0x4431
	cmpw r5, r0
	beq @4
	b @4
	@6:
	stw r7, pfi(r13)
	b @4
	@7:
	stw r7, blockGlyph(r13)
	@4:
	lwz r0, 0x4(r7)
	addi r6, r6, 0x1
	add r7, r7, r0
	@2:
	lwz r0, 0xc(r8)
	cmplw r6, r0
	blt @3
	lwz r6, blockGlyph(r13)
	la r3, fgTexObj(r13)
	li r7, 0x0
	li r8, 0x0
	lhz r5, 0x1a(r6)
	addi r4, r6, 0x20
	lhz r6, 0x1c(r6)
	li r9, 0x0
	li r10, 0x0
	bl GXInitTexObj
	lfs f1, float_0_8041a300(r2)
	la r3, fgTexObj(r13)
	li r4, 0x1
	li r5, 0x1
	fmr f2, f1
	li r6, 0x0
	fmr f3, f1
	li r7, 0x0
	li r8, 0x0
	bl GXInitTexObjLOD
	li r3, 0x20
	bl JUTFont_CodeToGlyph
	lwz r5, pfh(r13)
	lis r4, 0x5749
	addi r4, r4, 0x4431
	clrlwi r3, r3, 16
	lwz r0, 0xc(r5)
	addi r5, r5, 0x20
	mtctr r0
	cmplwi r0, 0x0
	ble @8
	@9:
	lwz r0, 0x0(r5)
	cmpw r0, r4
	beq @10
	b @11
	@10:
	lhz r6, 0x8(r5)
	cmplw r3, r6
	blt @11
	lhz r0, 0xa(r5)
	cmplw r3, r0
	bgt @11
	subf r0, r6, r3
	slwi r3, r0, 1
	addi r4, r3, 0xc
	add r4, r5, r4
	b @12
	@11:
	lwz r0, 0x4(r5)
	add r5, r5, r0
	bdnz @9
	@8:
	li r4, 0x0
	@12:
	li r0, 0x7
	lis r3, 0x1
	stb r0, 0x1(r4)
	subi r3, r3, 0x7ec0
	bl JUTFont_CodeToGlyph
	lwz r5, pfh(r13)
	lis r4, 0x5749
	addi r4, r4, 0x4431
	clrlwi r3, r3, 16
	lwz r0, 0xc(r5)
	addi r5, r5, 0x20
	mtctr r0
	cmplwi r0, 0x0
	ble @13
	@14:
	lwz r0, 0x0(r5)
	cmpw r0, r4
	beq @15
	b @16
	@15:
	lhz r6, 0x8(r5)
	cmplw r3, r6
	blt @16
	lhz r0, 0xa(r5)
	cmplw r3, r0
	bgt @16
	subf r0, r6, r3
	slwi r3, r0, 1
	addi r3, r3, 0xc
	add r3, r5, r3
	b @17
	@16:
	lwz r0, 0x4(r5)
	add r5, r5, r0
	bdnz @14
	@13:
	li r3, 0x0
	@17:
	li r0, 0x9
	stb r0, 0x1(r3)
	@1:
	lwz r0, 0x94(r1)
	lwz r31, 0x8c(r1)
	lwz r30, 0x88(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm void fontmgrInit(void) {
	nofralloc
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".sdata") u32 gap_07_8041036C_sdata[1] = {0};
__declspec(section ".sdata2") const u32 gap_09_8041A344_sdata2[1] = {0};
