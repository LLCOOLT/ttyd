#include "driver/msgdrv.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/icondrv.h"
#include "driver/npcdrv.h"
#include "driver/windowdrv.h"
#include "manager/dvdmgr.h"
#include "manager/fontmgr.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include <string.h>
#include <stdlib.h>

extern GlobalWork* gp;
extern int sprintf(char* str, const char* format, ...);
extern int sscanf(const char* str, const char* format, ...);

#define WIN_STATE(w) (*(u16*)(w)->field_0x0)

typedef struct MsgChar {
	u32 value; //0x0
	u16 glyph; //0x4
	s16 field_0x6; //0x6
	s16 field_0x8; //0x8
	u8 field_0xA[0xC - 0xA]; //0xA
	u32 time; //0xC
	u8 field_0x10[0x18 - 0x10]; //0x10
} MsgChar;

typedef struct MsgWinData {
	const char* tag; //0x0
	u32 flags; //0x4
	u16 field_0x8; //0x8
	u16 field_0xA; //0xA
	u16 field_0xC; //0xC
	u8 field_0xE[0x10 - 0xE]; //0xE
	s32 field_0x10; //0x10
	u8 field_0x14[0x18 - 0x14]; //0x14
	OSTime time18; //0x18
	s32 field_0x20; //0x20
	s32 field_0x24; //0x24
	s32 field_0x28; //0x28
	u8 field_0x2C[0x30 - 0x2C]; //0x2C
	OSTime time30; //0x30
	s32 count; //0x38
	MsgChar entries[0x500]; //0x3C
	s32 page; //0x783C
	s32 field_0x7840; //0x7840
	s32 pageY[(0x79FC - 0x7844) / 4]; //0x7844
	s32 field_0x79FC; //0x79FC
	u8 field_0x7A00[0x7A04 - 0x7A00]; //0x7A00
	char stayPose[0x20]; //0x7A04
	s32 unitId; //0x7A24
	s32 field_0x7A28; //0x7A28
	u8 field_0x7A2C; //0x7A2C
	u8 field_0x7A2D[0x7A30 - 0x7A2D]; //0x7A2D
	s32 field_0x7A30; //0x7A30
	s16 field_0x7A34; //0x7A34
	s16 field_0x7A36; //0x7A36
	s16 field_0x7A38; //0x7A38
	s16 field_0x7A3A; //0x7A3A
	s32 field_0x7A3C; //0x7A3C
	s8 numSel; //0x7A40
	s8 defSel; //0x7A41
	s8 cancel; //0x7A42
	s8 sel; //0x7A43
	s16 selWidth; //0x7A44
	s16 selY; //0x7A46
	f32 cursorY; //0x7A48
	WindowEntry* window; //0x7A4C
	s32 field_0x7A50; //0x7A50
	s32 field_0x7A54; //0x7A54
} MsgWinData;

#define MSG_CB(d) (*(void (**)(s32, smartEntry*))&(d)->field_0x79FC)
#define WIN_DATA(w) ((MsgWinData*)(w)->userdata->address)
#define WIN_TIME(w) (*(OSTime*)((u8*)(w) + 0x20))
void msgWindow_Disp(CameraId camId, void* param);
void msgWindow_Main(WindowEntry* window);
void msgWindow_Clear_Main(WindowEntry* window);
void msgWindow_Delete(WindowEntry* window);
void selectWindow_Main(WindowEntry* window);

s32 msgMain(smartEntry* smart);
void selectWindow_Disp(CameraId camId, void* param);

void BtlUnit_ChangeStayAnim(s32 unitId);
void npcSetStayPose(const char* name);
void BtlUnit_ChangeTalkAnim(s32 unitId);
void npcSetTalkPose(const char* name);
s32 psndSFXOnVol(const char* name, u8 vol);

typedef struct MsgLookupEntry {
	u32 startaddr; //0x0
	u32 endaddr; //0x4
} MsgLookupEntry;

typedef struct MsgIcon {
	const char* name; //0x0
	s32 value; //0x4
} MsgIcon;

const char R_no_messages_JP[] = "<col ff0000ff>\x83\x81\x83\x62\x83\x5A\x81\x5B\x83\x57\x82\xAA\x82\xA0\x82\xE8\x82\xDC\x82\xB9\x82\xF1</col>\n<key>";
const char R_no_messages_US[] = "<col ff0000ff>No messages.<col>\n<key>";
//.data
MsgIcon msgIcon[] = {
	{"PAD_A", 0x64},
	{"PAD_B", 0x66},
	{"STICK_LEFT", 0x78},
	{"STICK", 0x79},
	{"AC_ON", 0x95},
	{"BUTTON_L", 0x7E},
	{"BUTTON_R", 0x80},
	{"HM", 0x19F},
	{"PAD_X", 0x68},
	{"PAD_X_ON", 0x69},
	{"PAD_Y", 0x6A},
	{"PAD_Y_ON", 0x6B},
	{"PAD_Z_OFF", 0x82},
	{"PAD_ST_OFF", 0x84},
	{"black_key", 0x130},
	{"ANM_PAD_A", 0x20B},
	{"ANM_STICK_RIGHT", 0x20C},
	{"ANM_PAD_START", 0x20D}
};

s32 msgWindowOpen_SE_Data[] = {
	0x16, 0x17, 0x1A, 0x1B, 0x20, 0x21, 0x1C, 0x1D,
	0x20, 0x21, 0x1C, 0x1D, 0x18, 0x19, 0x22, 0x23,
	0x24, 0x25, 0x26, 0x27, 0x1E, 0x1F, -1, -1
};

//.sbss
MessageWork msgWork;
BOOL msgSEflag; //msgSEInit and related functions are unused
void* msgSortDvdData; //TODO: re-type

//.sdata
MessageWork* msgw = &msgWork;
const char* ErrMessage[2] = {R_no_messages_JP, R_no_messages_US};
const char* paperPoseTbl[6] = {
	"PM_Y_1B", "PM_Y_2B", "PM_F_1B",
	"PM_F_3B", "PM_C_1B", "PM_C_2B"
};
const char* language_dir[2] = {"msg", "emsg"};





//local prototypes
int msg_compare(const void* a, const void* b);
void msgDispKeyWait_render(s32 wXluStage);

void msgInit(void) {
	msgw->poseId = animPoseEntry("hoshi_2", 2);
	animPoseSetAnim(msgw->poseId, "HOS_C_1", TRUE);
	animPoseSetMaterialFlagOn(msgw->poseId, 0x1800);
	animPoseSetMaterialFlagOff(msgw->poseId, 0x40);
	animPoseSetGXFunc(msgw->poseId, msgDispKeyWait_render, 0);
	msgw->entries[0].address = NULL;
	msgw->entries[0].lookup = NULL;
	msgw->entries[1].address = NULL;
	msgw->entries[1].lookup = NULL;
	msgLoad("global\0", 1);
}

void msgLoad(const char* filename, s32 index) {
	MessageEntry* entry;
	u32 r30;
	MsgLookupEntry* lookup;
	u32 msgptr;
	int i;
	DVDEntry* dvd;
	s32 msgcount;
	u32 r27;
	char filepath[64];
	char dvdpath[128]; //TODO: double check size

	entry = &msgw->entries[index];
	sprintf(filepath, "./%s/%s.txt", language_dir[gp->language], filename);
	
	if (entry->address) {
		if (index == 1) {
			__memFree(HEAP_DEFAULT, entry->address);
		}
		entry->address = NULL;
	}
	entry->length = 0;

	if (!entry->address) {
		sprintf(dvdpath, "%s/%s", getMarioStDvdRoot(), filepath);
		dvd = DVDMgrOpen(dvdpath, 2, 0);
		if (dvd) {
			entry->length = DVDMgrGetLength(dvd);
			switch (index) {
				case 0:
					entry->address = _mapAlloc(OSRoundUp32B(entry->length));
					break;
				case 1:
					entry->address = __memAlloc(HEAP_DEFAULT, OSRoundUp32B(entry->length));
					break;
			}
			DVDMgrRead(dvd, entry->address, OSRoundUp32B(entry->length), 0);
			DVDMgrClose(dvd);
		}
	}

	if (!entry->address) {
		entry->length = 0;
		entry->count = 0;
	}
	else {
		msgptr = (u32)entry->address;
		msgcount = 0;
		while (*(s8*)msgptr) {
			msgptr += strlen((const char*)msgptr) + 1;
			msgcount++;
		}
		entry->count = (u32)(msgcount / 2); //tag, message
	}

	if (entry->lookup) {
		smartFree(entry->lookup);
	}
	if (!*(s32*)&entry->count) {
		entry->lookup = NULL;
	}
	else {
		r27 = 0;
		entry->lookup = smartAlloc(entry->count * sizeof(MsgLookupEntry), 0);
		r30 = (u32)entry->address;
		lookup = entry->lookup->address;
		for (i = 0; i < (s32)entry->count; i++, lookup++) {
			lookup->startaddr = r27;
			r27 += strlen((const char*)r30) + 1;
			r30 += strlen((const char*)r30) + 1;
			lookup->endaddr = r27;
			r27 += strlen((const char*)r30) + 1;
			r30 += strlen((const char*)r30) + 1;
		}
		msgSortDvdData = entry->address;
		qsort(entry->lookup->address, entry->count, sizeof(MsgLookupEntry), msg_compare);
	}
}

static inline void msgAddPage(smartEntry* smart, s32 y) {
	MsgWinData* d = smart->address;
	if (!(d->flags & 0x200) && d->field_0x7840 < 110) {
		if (d->field_0x7840 == 0 || d->pageY[d->field_0x7840 - 1] != y) {
			d->pageY[d->field_0x7840++] = y;
		}
	}
}

static inline void msgCheckSkip(smartEntry* smart, MsgWinData* data) {
	s32 btn, trgv;
	if (!(data->flags & 0x80)) {
		btn = 0x100;
		if (((MsgWinData*)smart->address)->flags & 0x100) {
			btn = 0x500;
		}
		trgv = keyGetButtonTrg(0);
		if (trgv & (btn | 0x200)) {
			data->flags |= 4;
		}
	}
}

static inline void msgVoiceSE(smartEntry* smart) {
	MsgWinData* d = smart->address;
	if (d->window->type != 1 && !msgSEflag) {
		psndSFXOnVol((const char*)0x20044, d->field_0x7A2C);
		msgSEflag = 1;
	}
}

s32 msgMain(smartEntry* smart) {
	MsgWinData* data = smart->address;
	MsgChar* entry;
	s32 i;
	s32 ms;
	NpcEntry* npc;

	msgSEflag = 0;
	if (data->flags & 2) {
		if (MSG_CB(data)) {
			MSG_CB(data)(0, smart);
		}
		data->flags &= ~2;
		msgAddPage(smart, 0);
	}
	if (data->field_0x24 > data->field_0x28) {
		data->field_0x28 += 0.36f * OSTicksToMilliseconds(gp->renderTime - data->time30);
		msgCheckSkip(smart, data);
		if (!(data->flags & 0x10) && (data->flags & 4)) {
			data->field_0x28 += 0.36f * OSTicksToMilliseconds(gp->renderTime - data->time30);
		}
		if (data->field_0x24 < data->field_0x28) {
			data->field_0x28 = data->field_0x24;
		}
		data->time30 = gp->renderTime;
		return 3;
	}
	switch (data->field_0xA) {
	case 1:
		return 2;
	case 2:
		data->field_0xC = 1;
		data->field_0x8++;
		data->field_0xA = 0;
		psndSFXOn((const char*)0x2003D);
		data->field_0x20 += 100;
		if (MSG_CB(data)) {
			MSG_CB(data)(3, smart);
		}
		break;
	default:
		ms = OSTicksToMilliseconds(gp->renderTime - data->time30);
		msgCheckSkip(smart, data);
		if (!(data->flags & 0x10) && (data->flags & 4)) {
			ms *= 100;
		}
		data->field_0x20 += ms;
		break;
	}
	data->time30 = gp->renderTime;
	entry = &data->entries[data->field_0x10];
	for (i = data->field_0x10; i < 0x500; i++, entry++) {
		if (entry->time > data->field_0x20) {
			break;
		}
		switch (entry->glyph) {
		case 0xFFFF:
			if (MSG_CB(data)) {
				MSG_CB(data)(1, smart);
			}
			data->field_0x10 = i;
			return 0;
		case 0xFFFE:
			if (entry->field_0x6 == data->field_0x8) {
				data->field_0xA = 1;
				data->field_0x20 = entry->time;
				data->flags &= ~4;
				if (MSG_CB(data)) {
					MSG_CB(data)(2, smart);
				}
			}
			break;
		case 0xFFFD:
			data->field_0x24 -= entry->field_0x8;
			data->field_0x20 = entry->time;
			msgAddPage(smart, data->field_0x24);
			break;
		case 0xFFFC:
			data->field_0x10 = i + 1;
			data->field_0x20 = entry->time;
			data->flags &= ~4;
			return 1;
		case 0xFFFB:
			if (MSG_CB(data)) {
				MSG_CB(data)(4, smart);
			}
			break;
		case 0xFFFA:
			data->field_0x7A28 = entry->value;
			break;
		case 0xFFF9:
			data->field_0x7A2C = entry->value;
			break;
		case 0xFFF5:
			if (entry->value) {
				data->flags |= 0x80;
				data->flags &= ~4;
				data->field_0x20 = entry->time;
			}
			else {
				data->flags &= ~0x80;
			}
			break;
		case 0xFFF3:
			npc = (NpcEntry*)entry->value;
			if (!npc) {
				npc = npcNameToPtr(data->stayPose);
			}
			animPoseSetPaperAnimGroup(npc->poseId, "p_b_st", 1);
			animPosePaperPeraOn(npc->poseId);
			animPoseSetPaperAnim(npc->poseId, paperPoseTbl[entry->time], 1);
			break;
		case 0xFFF2:
			npc = (NpcEntry*)entry->value;
			if (data->field_0xA) {
				i--;
				break;
			}
			if (!npc) {
				npc = npcNameToPtr(data->stayPose);
			}
			animPoseSetPaperAnimGroup(npc->poseId, NULL, 1);
			break;
		case 0xFFF4:
		case 0xFFF8:
			break;
		default:
			if (MSG_CB(data)) {
				MSG_CB(data)(5, smart);
			}
			if (entry->value & 0x10) {
				msgVoiceSE(smart);
			}
			else if (entry->value & 8) {
				if (((MsgWinData*)smart->address)->window->type != 3) {
					((MsgWinData*)smart->address)->field_0x7A50 = 15;
				}
				msgVoiceSE(smart);
			}
			break;
		}
	}
	data->field_0x10 = i;
	if (data->field_0xA) {
		return 2;
	}
	return 3;
}


typedef struct MsgDispChar {
	u32 value; //0x0
	u16 glyph; //0x4
	s16 x; //0x6
	s16 y; //0x8
	s16 iconY; //0xA
	u32 time; //0xC
	f32 scale; //0x10
	f32 rot; //0x14
} MsgDispChar;

double cos(double);
double sin(double);
void FontDrawNoise(void);
void FontDrawNoiseOff(void);
void FontDrawEdge(void);
void FontDrawEdgeOff(void);
void FontDrawRainbowColor(void);
void FontDrawRainbowColorOff(void);
void FontDrawColorIDX(s32 idx);
void FontDrawColor_(void);
GXColor FontGetDrawColor(void);
void FontDrawScale(f32 scale);
void FontDrawCode(f32 x, f32 y, u16 code);
void FontDrawCodeMtx(Mtx mtx, u16 code);

#pragma dont_inline on
BOOL msgDisp(smartEntry* smart, u8 alpha, f32 x, f32 y) {
	s32 hide;
	s32 al;
	s32 w;
	MsgWinData* data = smart->address;
	MsgDispChar* c = (MsgDispChar*)data->entries;
	s32 i;
	BOOL ret = FALSE;
	u8 a;
	f32 sx, sy, hx, hy, t;
	s32 page, py, d;
	GXColor col, col2, col4;
	Mtx m;
	Mtx m2;
	Vec pos;

	FontDrawStart_alpha(alpha);
	al = alpha;
	for (i = 0; i < data->field_0x10; i++, c++) {
		switch (c->glyph) {
			case 0xFFFF:
				return FALSE;
			case 0xFFFE:
				if (data->field_0x8 == c->x) {
					ret = TRUE;
				}
				break;
			case 0xFFF7:
				FontDrawColor(*(GXColor*)&c->value);
				break;
			case 0xFFF6:
				if (c->value) {
					FontDrawNoise();
				}
				else {
					FontDrawNoiseOff();
				}
				break;
			case 0xFFF4:
				col = FontGetDrawColor();
				PSMTXIdentity(m);
				if (c->rot >= 90.0f && c->rot <= 270.0f) {
					PSMTXScaleApply(m, m, 1.0f, 1.0f, -1.0f);
				}
				PSMTXTransApply(m, m, x + c->x, c->y + (y + data->field_0x28) - 40.0f, 0.0f);
				animPoseMain((s32)c->value);
				animPoseDrawMtx((s32)c->value, m, 2, c->rot, c->scale);
				FontDrawStart_alpha(alpha);
				FontDrawColor(col);
				break;
			case 0xFFF5:
			case 0xFFF9:
			case 0xFFFA:
			case 0xFFFB:
			case 0xFFFC:
			case 0xFFFD:
				break;
			default:
				hide = 0;
				a = 0xFF;
				sx = x + c->x;
				sy = c->y + (y + data->field_0x28);
				if (data->flags & 0x40) {
					page = data->page;
					py = data->pageY[page];
					if (data->field_0x28 == py) {
						if (c->y + data->pageY[page + 1] <= 0) {
							break;
						}
						hide = 1;
					}
					else if (data->field_0x28 < py) {
						if (c->y + py > 0) {
							hide = 1;
						}
						else {
							d = py - data->field_0x28;
							if (d > 100) {
								d = 100;
							}
							a = (100 - d) * 255 / 100;
							if (page != data->field_0x7840 - 1) {
								if (c->y + data->pageY[page + 1] <= 0) {
									break;
								}
								hide = 1;
							}
							else {
								col2 = FontGetDrawColor();
								col2.a = col2.a * a / 255;
								GXSetTevColor(GX_TEVREG0, col2);
							}
						}
					}
					else {
						if (c->y + data->pageY[page + 1] > 0) {
							hide = 1;
						}
						else {
							d = data->field_0x28 - py;
							if (d > 100) {
								d = 100;
							}
							a = d * 255 / 100;
							if (page != data->field_0x7840 - 2) {
								if (c->y + data->pageY[page + 2] <= 0) {
									break;
								}
								hide = 1;
							}
							else {
								col2 = FontGetDrawColor();
								col2.a = col2.a * a / 255;
								GXSetTevColor(GX_TEVREG0, col2);
							}
						}
					}
				}
				if (c->glyph == 0xFFF8) {
					col4 = FontGetDrawColor();
					pos.x = 20.0f + (x + c->x);
					pos.y = c->iconY + (c->y + (y + data->field_0x28) - 40.0f);
					pos.z = 0.0f;
					iconDispGxAlpha(&pos, 0x10, (u16)c->value, a * al / 255, c->scale);
					FontDrawStart_alpha(alpha);
					FontDrawColor(col4);
					break;
				}
				if ((f32)(c->y + data->field_0x28) >= 32.0f * c->scale - 10.0f) {
					break;
				}
				if (hide) {
					GXColor gray = {0x50, 0x50, 0x50, 0xFF};
					switch (data->window->type) {
						case 3:
						case 8:
						case 9: {
							GXColor gray2 = {0x6E, 0x6E, 0x6E, 0xFF};
							gray = gray2;
							break;
						}
					}
					gray.a = a;
					GXSetTevColor(GX_TEVREG0, gray);
					FontDrawScale(c->scale);
					FontDrawCode(sx, sy, c->glyph);
					FontDrawColor_();
				}
				else if (c->value & 1) {
					w = kanjiGetWidth(c->glyph) / 2;
					hx = sx;
					hy = sy;
					if (c->value & 2) {
						hx = sx + irand(10000) % 3;
						hy = sy + irand(10000) % 3;
					}
					PSMTXTrans(m2, -w, 12.0f, 0.0f);
					PSMTXScaleApply(m2, m2, c->rot, c->rot, c->rot);
					PSMTXTransApply(m2, m2, (u32)w, -12.0f, 0.0f);
					PSMTXScaleApply(m2, m2, c->scale, c->scale, c->scale);
					PSMTXTransApply(m2, m2, hx, hy, 0.0f);
					FontDrawCodeMtx(m2, c->glyph);
					c->rot = 1.0f + 0.5f * (c->rot - 1.0f);
				}
				else if (c->value & 2) {
					hy = sx + irand(10000) % 3;
					hx = sy + irand(10000) % 3;
					FontDrawScale(c->scale);
					FontDrawCode(hy, hx, c->glyph);
				}
				else if (c->value & 4) {
					t = 0.01f * OSTicksToMilliseconds(gp->renderTime - data->time18) - 0.02f * sx;
					hx = cos(t);
					hy = sin(t);
					FontDrawScale(c->scale);
					FontDrawCode(sx + 3.2f * hx, sy - 3.2f * hy, c->glyph);
				}
				else if (c->value & (0x100 << data->sel)) {
					f32 hx2;
					t = 0.01f * OSTicksToMilliseconds(gp->renderTime - data->time18) - 0.02f * sx;
					hx2 = sx + 3.2f * (f32)cos(t);
					hy = sy - 3.2f * (f32)sin(t);
					FontDrawScale(c->scale);
					{
						GXColor shadow = {0x00, 0x00, 0x00, 0x50};
						FontDrawColor(shadow);
					}
					FontDrawCode(hx2, hy, c->glyph);
					FontDrawEdge();
					FontDrawRainbowColor();
					{
						GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
						FontDrawColor(white);
					}
					FontDrawCode(hx2 - 4.0f, 4.0f + hy, c->glyph);
					FontDrawEdgeOff();
					FontDrawRainbowColorOff();
					FontDrawColorIDX(0);
				}
				else {
					FontDrawScale(c->scale);
					FontDrawCode(sx, sy, c->glyph);
				}
				break;
		}
	}
	return ret;
}
#pragma dont_inline reset

void msgDispKeyWait_render(s32 wXluStage) {
	AnimationWork* wp = animGetPtr();

	GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
	GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	GXSetZCompLoc(GX_FALSE);
	GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
	wp->currDispMode = wXluStage;
}

char* msgGetCommand(char* msg, char* cmd, char* arg);
s32 msgIconStr2ID(const char* str);

typedef struct MsgAChar {
	u32 value; //0x0
	u16 glyph; //0x4
	s16 x; //0x6
	s16 y; //0x8
	s16 extra; //0xA
	s32 time; //0xC
	f32 scale; //0x10
	f32 dyn; //0x14
} MsgAChar;

void msgAnalize(smartEntry* smart, char* msg) {
	s16 s230;
	s16 s232;
	s16 s234;

	MsgWinData* data;
	WindowEntry* window;
	MsgAChar* entry;
	s32 check;
	u16 glyph;
	u16 width;
	u32 flags;
	s16 x;
	s32 y;
	s32 time;
	s16 rubyX;
	char tag[0x80];
	char args[0x80];
	char name[0x20];
	char anim1[0x20]; s32 tmpi2;
	char anim2[0x20];
	char paper[0x20];
	char paper2[0x20];
	s32 step;
	f32 scale;
	f32 fv;
	s32 v48;
	s32 v44;
	s32 v40;
	s32 iconId;
	s32 i38;
	s32 i34;
	MsgWinData* data2;
	s32 i30;
	f32 iconScale;
	s32 i28;
	s32 i24;
	s32 i20;
	f32 f1c;
	s32 i18;
	s16 w16;
	s16 w14;
	s16 w12;
	s16 w10;
	s16 sel0;
	s16 sel1;
	u16 iw;
	u16 ih;
	f32 maxScale;
	char* next;
	BOOL isHM;
	s32 i;
	s32 k;
	s32 half;
	s32 j;
	s32 total;
	u16 rubyW;
	char* p;
	s32 ww;

	data = smart->address;
	window = data->window;
	entry = (MsgAChar*)(&data->entries[data->count]);
	flags = 0;
	maxScale = 0.0f;
	scale = 1.0f;
	if (window->type < 0) {
		window->type = 0;
	}
	time = data->field_0x7A30;
	s234 = 0;
	s232 = data->field_0x7A38;
	x = data->field_0x7A34;
	s230 = data->field_0x7A3A;
	y = data->field_0x7A36;
	step = data->field_0x7A3C;
	switch (window->type) {
	case 3:
	case 8:
		switch (window->type) {
		case 3: {
			static const GXColor c = {0xDC, 0xC8, 0xDC, 0xFF};
			entry->value = *(( u32*)(&c) );
			break;
		}
		case 8: {
			static const GXColor c = {0x00, 0xD9, 0x14, 0xFF};
			entry->value = *(( u32*)(&c) );
			break;
		}
		}
		entry->glyph = 0xFFF7;
		entry->time = time;
		entry++;
		data->count++;
		break;
	default:
		break;
	}

	while (TRUE) {
		check = *(( u8*)msg) ;
		if (_ismbblead((u8)check)) {
			glyph = kanjiSearch(*(( u16*)msg) );
			width = kanjiGetWidth((u16)(glyph + 0));
			ww = scale * (( f32)(width + 4) );
			entry->glyph = glyph;
			entry->x = x;
			entry->y = y - (( s32)(10.0f * scale) );
			entry->scale = scale;
			entry->value = flags;
			if (( *( (u16*)msg )) == 0x8145) {
				entry->value |= 0x10;
			} else if ((( *( (u16*)msg )) != 0x8140 ) && (( *( (u16*)msg )) != 0x8151) ) {
				entry->value |= 8;
			}
			if (( flags & 1) != 0 ) {
				entry->dyn = fv;
			}
			if (maxScale < scale) {
				maxScale = scale;
			}
			entry->time = time;
			x += ww;
			msg += 2;
			time += step;
			entry++;
			data->count++;
			continue;
		}
		switch ((s8)check) {
		case 0:
			entry->glyph = 0xFFFF;
			entry->time = time;
			data->field_0x7A30 = time;
			data->field_0x7A34 = x;
			data->field_0x7A36 = y;
			data->field_0x7A38 = s232;
			data->field_0x7A3A = s230;
			return;
		case '\n':
			entry->glyph = 0xFFFB;
			entry->time = time;
			x = 0;
			if (0.0f == maxScale) {
				maxScale = 1.0f;
			}
			y -= 32.0f * maxScale;
			s230 -= 32.0f * maxScale;
			msg++;
			entry++;
			time += step;
			data->count++;
			maxScale = 0.0f;
			if (data->flags & 0x20) {
				flags = (flags & (~0xFF00)) | (0x100 << data->numSel);
				data->numSel++;
			}
			continue; tmpi2 = gp->language;
		case '<':
			next = msgGetCommand(msg + 1, tag, args);
			msg = next;
			if (( strcmp(tag, "k") == 0 ) || ( strcmp(tag, "key") == 0) ) {
				entry->glyph = 0xFFFE;
				entry->x = s232;
				entry->time = time;
				time += 100;
				entry++;
				data->count++;
				s232++;
			} else if (strcmp(tag, "keyxon") == 0) {
				data->flags |= 0x100;
			} else if (( strcmp(tag, "p") == 0 ) || ( strcmp(tag, "scrl_auto") == 0) ) {
				if (s230 != 0) {
					entry->glyph = 0xFFFD;
					entry->y = s230 - 3;
					s234 = y - 6;
					y -= 3;
					entry->time = time;
					time += 0x32;
					entry++;
					s230 = 0;
					data->count++;
				}
			} else if (( strcmp(tag, "o") == 0 ) || ( strcmp(tag, "once_stop") == 0) ) {
				entry->glyph = 0xFFFC;
				entry->time = time;
				time += 0x32;
				entry++;
				data->count++;
			} else if (strcmp(tag, "pos") == 0) {
				sscanf(args, "%d%d", &v48, &v44);
				x = v48;
				if (v44 != 999) {
					y = s234 - v44;
				}
				s230 = -v44;
			} else if (strcmp(tag, "scale") == 0) {
				sscanf(args, "%f", &scale);
			} else if (strcmp(tag, "/scale") == 0) {
				scale = 1.0f;
			} else if (strcmp(tag, "wait") == 0) {
				sscanf(args, "%d", &v40);
				time += v40;
			} else if (strcmp(tag, "speed") == 0) {
				sscanf(args, "%d", &step);
			} else if (strcmp(tag, "/speed") == 0) {
				step = data->field_0x7A3C;
			} else if (strcmp(tag, "dynamic") == 0) {
				sscanf(args, "%f", &fv);
				flags |= 1;
			} else if (strcmp(tag, "/dynamic") == 0) {
				flags &= ~1;
			} else if (strcmp(tag, "shake") == 0) {
				flags |= 2;
			} else if (strcmp(tag, "/shake") == 0) {
				flags &= ~2;
			} else if (strcmp(tag, "wave") == 0) {
				flags |= 4;
			} else if (strcmp(tag, "/wave") == 0) {
				flags &= ~4;
			} else if (strcmp(tag, "col") == 0) {
				sscanf(args, "%x", &entry->value);
				entry->glyph = 0xFFF7;
				entry->time = time;
				entry++;
				data->count++;
			} else if (strcmp(tag, "/col") == 0) {
				entry->value = 0xFF;
				entry->glyph = 0xFFF7;
				entry->time = time;
				entry++;
				data->count++;
			} else if (strcmp(tag, "noise") == 0) {
				entry->value = 1;
				entry->glyph = 0xFFF6;
				entry->time = time;
				entry++;
				data->count++;
			} else if (strcmp(tag, "/noise") == 0) {
				entry->value = 0;
				entry->glyph = 0xFFF6;
				entry++;
				data->count++;
			} else if (strcmp(tag, "dkey") == 0) {
				entry->value = 1;
				entry->glyph = 0xFFF5;
				entry->time = time;
				entry++;
				data->count++;
			} else if (strcmp(tag, "/dkey") == 0) {
				entry->value = 0;
				entry->glyph = 0xFFF5;
				entry->time = time;
				entry++;
				data->count++;
			} else if (strcmp(tag, "plate") == 0) {
				window->type = 2;
				step = 0;
				data->field_0x7A3C = 0;
			} else if (strcmp(tag, "system") == 0) {
				static const GXColor c = {0xDC, 0xC8, 0xDC, 0xFF};
				window->type = 3;
				entry->value = *(( u32*)(&c) );
				entry->glyph = 0xFFF7;
				entry->time = time;
				entry++;
				data->count++;
			} else if (strcmp(tag, "tec") == 0) {
				static const GXColor c = {0x00, 0xD9, 0x14, 0xFF};
				window->type = 8;
				entry->value = *(( u32*)(&c) );
				entry->glyph = 0xFFF7;
				entry->time = time;
				entry++;
				data->count++;
			} else if (strcmp(tag, "majo") == 0) {
				window->type = 9;
			} else if (strcmp(tag, "diary") == 0) {
				window->type = 7;
			} else if (strcmp(tag, "housou") == 0) {
				window->type = 10;
			} else if (strcmp(tag, "boss") == 0) {
				window->type = 6;
			} else if (strcmp(tag, "kanban") == 0) {
				window->type = 4;
				step = 0;
				data->field_0x7A3C = 0;
			} else if (strcmp(tag, "small") == 0) {
				window->type = 1;
				data->flags |= 0x10;
			} else if (strcmp(tag, "clear") == 0) {
				window->type = 11;
			} else if (strcmp(tag, "wpos") == 0) {
				sscanf(args, "%hd%hd%hd%hd", &w16, &w14, &w12, &w10);
				window->flags |= 4;
				window->x = w16;
				window->y = w14;
				window->height = w12;
				window->width = w10;
			} else if (strcmp(tag, "select") == 0) {
				window->type = 5;
				data->flags |= 0x20;
				sscanf(args, "%hd%hd%hd%hd%hd", &sel0, &sel1, &data->selWidth, &data->selY);
				flags |= 0x100;
				data->defSel = sel0;
				data->cancel = sel1;
				data->numSel = 1;
				step = 0;
			} else if (strcmp(tag, "se") == 0) {
				sscanf(args, "%d", &entry->value);
				entry->glyph = 0xFFFA;
				entry++;
				data->count++;
			} else if (strcmp(tag, "vol") == 0) {
				sscanf(args, "%d", &entry->value);
				entry->glyph = 0xFFF9;
				entry++;
				data->count++;
			} else if (strcmp(tag, "nowinse") == 0) {
				window->flags |= 8;
			} else if (strcmp(tag, "icon") == 0) {
				isHM =(unsigned long long)  FALSE;
				if ((( (s8) args [0] ) >= '0') && (((s8) args [0]) <= '9') ) {
					sscanf(args, "%d%f%d%d%d", &iconId, &iconScale, &i38, &i34, &i30);
				} else {
					sscanf(args, "%s%f%d%d%d", name, &iconScale, &i38, &i34, &i30);
					if (strcmp(name, "HM") == 0) {
						isHM = TRUE;
					}
					iconId = msgIconStr2ID(name);
					if (iconId < 0) {
						iconId = 0;
					}
				}
				if (!isHM) {
					entry->value = iconId;
					iconGetWidthHight(&iw, &ih, (u16)iconId);
					entry->glyph = 0xFFF8;
					entry->x = (x + (( 0.5f * iw ) * iconScale) ) + i38;
					x += 0x28;
					entry->y = y - ( ih * iconScale) ;
					entry->extra = i34;
					entry->scale = iconScale;
					entry->time = time;
					entry++;
					time += step;
					data->count++;
				} else {
					glyph = kanjiSearch(0x94B5);
					width = kanjiGetWidth((u16)(glyph + 0));
					iw = scale * (( f32)(width + 4) );
					entry->glyph = glyph;
					entry->x = x;
					entry->y = y - (( s32)(10.0f * scale) );
					entry->scale = scale;
					entry->value = flags;
					entry->value |= 8;
					if (flags & 1) {

						entry->dyn = fv;
					}
					if (maxScale < scale) {
						maxScale = scale;
					}
					entry->time = time;
					entry++;
					time += step;
					x += iw;
					data->count++;
				}
			} else if (strcmp(tag, "anim") == 0) {
				sscanf(args, "%s%s%d%d%f%d", anim1, anim2, &i28, &i24, &f1c, &i20);
				entry->value = animPoseEntry(anim1, 2);
				animPoseSetAnim(entry->value, anim2, 1);
				animPoseSetMaterialFlagOn(entry->value, 0x1800);
				animPoseSetMaterialFlagOff(entry->value, 0x40);
				animPoseSetGXFunc(msgw->poseId, msgDispKeyWait_render, 0);
				entry->glyph = 0xFFF4;
				entry->x = i28;
				entry->y = s234 - i24;
				entry->scale = f1c;
				entry->dyn = (i20 == 0) ? ( 0.0f ) : ( 180.0f) ;
				entry++;
				time += step;
				data->count++;
			} else if (strcmp(tag, "paper") == 0) {
				sscanf(args, "%s%d", paper, &i18);
				entry->value = (strcmp(paper, "me") != 0) ? (( u32)npcNameToPtr(paper) ) : ( 0) ;
				entry->glyph = 0xFFF3;
				entry->time = i18;
				entry++;
				data->count++;
			} else if (strcmp(tag, "/paper") == 0) {
				sscanf(args, "%s", paper2);
				entry->value = (strcmp(paper2, "me") != 0) ? (( u32)npcNameToPtr(paper2) ) : ( 0) ;
				entry->glyph = 0xFFF2;
				entry++;
				data->count++;
			} else if (strcmp(tag, "r") == 0) {
				data2 = data;
				if (data2->window->type != 1) {
					rubyX = x;
				}
			} else if (((( s8*)tag)[0] == 'R' ) || ( (((s8*)tag)[0] == '/' ) && (( (u32)((s8*)tag)[0] ) == 0x2F72) )) {
				i = 1;
				if (((s8*)tag)[0] != 'R') { i = 2;
				}
				if (data2->window->type == 1) {
					continue;
				}
				half = ((s32)strlen(tag + i)) / 2;
				total = 0;
				j = i;
				isHM = i;
				p = tag + isHM;
				for (k = 0; k < half; k++) {
					glyph = kanjiSearch(*(( u16*)p) );
					width = kanjiGetWidth((u16)(glyph + 0));
					total += (s32)(0.55f * (scale * (( f32)(width + 4) )));
					p += 2;
					j += 2;
				}
				rubyW = (u16)total; rubyW = rubyW - ( 0.55f * (4.0f * scale)) ;
				rubyX = (( ((f32)(rubyX + x) ) - ( 4.0f * scale )) - ( (f32)rubyW) ) * 0.5f;
				p = tag; p = p + i;
				for (k = 0; ( k - 1) < ( half- 1) ; k++) {
					glyph = kanjiSearch(*(( u16*)p) );
					width = kanjiGetWidth((u16)(glyph + 0));
					ww = 0.55f * (scale * (( f32)(width + 4) ));
					entry->glyph = glyph;
					entry->x = rubyX;
					s230 = y;
					entry->y = s230;
					entry->scale = 0.55f * scale;
					entry->value = flags;
					if (flags & 1) {
						entry->dyn = fv;
					}
					entry->time = 0;
					rubyX += ww;
					p += 2;
					i += 2;
					data->count++;
					entry++;
				}
				continue;
			}
			if (( *( (s8*)next )) == '\n') {
				msg++;
			}
			continue;
		default:
			if ((((( u32)tmpi2 ) == 0 ) && (( (s8)check ) >= '0' )) && (( (s8)check ) <= '9') ) {
				glyph = kanjiSearch((u16)(check + 0x821F));
			} else {
				glyph = hankakuSearch(check);
			}
			width = kanjiGetWidth((u16)(glyph + 0));
			ww = scale * (( f32)(width + 2) );
			entry->glyph = glyph;
			entry->x = x;
			entry->y = y - (( s32)(10.0f * scale) );
			entry->scale = scale;
			entry->value = flags;
			if (( *( (s8*)msg )) != ' ') {
				entry->value |= 8;
			}
			if (flags & 1) {
				entry->dyn = fv;
			}
			if (maxScale < scale) {
				maxScale = scale;
			}
			entry->time = time;
			x += ww;
			msg++;
			time += step;
			entry++;
			data2->count++;
			continue;
		}
	}
}

MessageWork* L_msgGetWork(void) {
	return &msgWork;
}

int msg_compare(const void* a, const void* b) {
	s32 result = strcmp((char*)msgSortDvdData + *(u32*)a, (char*)msgSortDvdData + *(u32*)b);
	if (result > 0) {
		return 1;
	}
	if (result < 0) {
		return -1;
	}
	return 0;
}

const char* msgSearch(const char* tag) {
	MessageEntry* entry;
	MsgLookupEntry* lookup;
	smartEntry* smart;
	s32 i, max, j, index;
	s32 result;

	for (i = 0; i < 2; i++) { //check both entries
		entry = &msgw->entries[i];
		smart = entry->lookup;
		if (smart) {
			lookup = smart->address;
			j = 0;
			max = entry->count;
			while (max >= j) {
				index = (j + max) / 2; //tag, message
				if (index >= (s32)entry->count) {
					break;
				}
				result = strcmp(tag, (const char*)((u32)entry->address + lookup[index].startaddr));
				if (!result) {
					return (const char*)((u32)entry->address + lookup[index].endaddr);
				}
				if (result < 0) {
					max = index - 1;
				}
				else {
					j = index + 1;
				}
			}
		}
	}
	return ErrMessage[gp->language];
}

BOOL _ismbblead(u32 a1) {
	u8 check = (u8)a1;
	if ((check >= 0x81 && check <= 0x9F) || (check >= 0xE0 && check <= 0xFC)) {
		return TRUE;
	}
	return FALSE;
}

char* msgGetCommand(char* msg, char* cmd, char* arg) {
	s32 i;
	BOOL inArg = FALSE;

	for (i = 0; i < 0x80; i++, msg++) {
		switch ((s8)*msg) {
		case '>':
			if (!inArg) {
				*cmd = 0;
			}
			else {
				*arg = 0;
			}
			return msg + 1;
		case ' ':
			if (!inArg) {
				*cmd = 0;
				inArg = TRUE;
			}
			else {
				*arg++ = *msg;
			}
			break;
		default:
			if (!inArg) {
				*cmd++ = *msg;
			}
			else {
				*arg++ = *msg;
			}
			break;
		}
	}
	return NULL;
}

s32 msgIconStr2ID(const char* str) {
	MsgIcon* icon;
	u32 i;

	for (i = 0; i < 18; i++) {
		if (!strcmp(msgIcon[i].name, str)) {
			return msgIcon[i].value;
		}
	}
	return -1;
}

s32 msgWindow_Entry(const char* msg, s32 field_0x79FC, u16 priority) {
	WindowEntry* window;
	char* copy;
	MsgWinData* data;
	smartEntry* smart;
	s32 id;

	id = windowEntry(priority);
	window = windowGetPointer(id);
	window->main = msgWindow_Main;
	window->delete = msgWindow_Delete;
	WIN_STATE(window) = 5;
	window->type = -1;
	window->flags |= 2;
	copy = __memAlloc(HEAP_DEFAULT, strlen(msg));
	strcpy(copy, msg);
	smart = smartAlloc(0x7A58, 1);
	data = smart->address;
	memset(data, 0, 0x7A58);
	data->window = window;
	data->flags = 3;
	data->field_0x79FC = field_0x79FC;
	data->time30 = gp->renderTime;
	data->time18 = gp->renderTime;
	data->field_0x7A28 = 0;
	data->field_0x7A2C = 0x7F;
	data->field_0x7A30 = 0;
	data->field_0x7A34 = 0;
	data->field_0x7A36 = 0;
	data->field_0x7A38 = 0;
	data->field_0x7A3A = 0;
	data->field_0x7A3C = 25;
	data->field_0x7840 = 0;
	msgAnalize(smart, copy);
	if (window->type == 1) {
		data->flags |= 0x200;
	}
	__memFree(HEAP_DEFAULT, copy);
	window->userdata = smart;
	data = window->userdata->address;
	data->field_0x7A50 = 0;
	data->field_0x7A54 = 0;
	switch (window->type) {
	case 11:
		window->main = msgWindow_Clear_Main;
	case 0:
	case 2:
	case 3:
	case 4:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		if (!(window->flags & 4)) {
			window->x = -280.0f;
			window->y = 225.0f;
			window->height = 560.0f;
			window->width = 176.0f;
		}
		break;
	case 5:
		window->main = selectWindow_Main;
		window->x = (s16)(-WIN_DATA(window)->selWidth / 2);
		window->y = WIN_DATA(window)->selY;
		window->height = WIN_DATA(window)->selWidth;
		window->width = (s16)(WIN_DATA(window)->numSel * 36 + 40);
		WIN_DATA(window)->sel = WIN_DATA(window)->defSel;
		data->cursorY = window->y - (data->sel * 31 + 58);
		break;
	case 1:
		window->field_0x4 = 10;
		window->height = 0.7f * GXGetTexObjWidth(getWakuTexObj(3));
		window->width = 0.7f * GXGetTexObjHeight(getWakuTexObj(3));
		break;
	}
	return id;
}

#pragma optimize_for_size on
void msgWindow_Delete(WindowEntry* window) {
	MsgWinData* data;
	s32 i;

	if (window->userdata) {
		data = window->userdata->address;
		for (i = 0; i < data->count; i++) {
		}
		smartFree(window->userdata);
		window->userdata = NULL;
	}
}

#pragma optimize_for_size reset

void msgWindow_Add(char* msg, s32 id) {
	WindowEntry* window = windowGetPointer(id);
	smartEntry* smart = window->userdata;

	((MsgWinData*)smart->address)->time30 = gp->renderTime;
	msgAnalize(smart, msg);
	WIN_STATE(window) = 1;
	window->flags |= 2;
}

void msgWindow_Continue(s32 id) {
	WindowEntry* window = windowGetPointer(id);
	MsgWinData* data;

	WIN_STATE(window) = 1;
	window->flags |= 2;
	data = window->userdata->address;
	data->time30 = gp->renderTime;
}

void msgWindow_Repeat(s32 id) {
	WindowEntry* window = windowGetPointer(id);
	MsgWinData* data;

	WIN_STATE(window) = 1;
	window->flags |= 2;
	data = window->userdata->address;
	data->time30 = gp->renderTime;
	data->time18 = gp->renderTime;
	data->field_0x20 = 0;
	data->field_0x24 = 0;
	data->field_0x28 = 0;
	data->field_0x10 = 0;
}

void msgWindow_ForceClose(const char* name) {
	WindowEntry* window;
	MsgWinData* data;
	s32 i;

	for (i = 0; i < 7; i++) {
		window = windowGetPointer(i);
		if (window->flags && WIN_STATE(window) && window->userdata &&
			((MsgWinData*)window->userdata->address)->tag &&
			!strcmp(((MsgWinData*)window->userdata->address)->tag, name)) {
			WIN_STATE(window) = 7;
			data = window->userdata->address;
			if (data->flags & 8) {
				BtlUnit_ChangeStayAnim(data->unitId);
			}
			else {
				npcSetStayPose(data->stayPose);
			}
		}
	}
}

static inline BOOL msgWinPrevPage(WindowEntry* window) {
	MsgWinData* d = WIN_DATA(window);
	d->page--;
	if (d->page < 0) {
		d->page = 0;
		return FALSE;
	}
	return TRUE;
}

static inline void msgWinNextPage(WindowEntry* window) {
	MsgWinData* d = WIN_DATA(window);
	s32 max;
	d->page++;
	max = d->field_0x7840 - 1;
	if (d->page > max) {
		d->page = max;
	}
}

#pragma opt_common_subs off
void msgWindow_Main(WindowEntry* window) {
	smartEntry* smart = window->userdata;
	MsgWinData* data = smart->address;
	s32 se;
	s32 target;
	u32 trg;

	if (data->field_0x7A50) {
		if (!data->field_0x7A54) {
			if (data->flags & 8) {
				BtlUnit_ChangeTalkAnim(data->unitId);
			}
			else {
				npcSetTalkPose(data->stayPose);
			}
			data->field_0x7A54 = 1;
		}
		data->field_0x7A50--;
		if (data->field_0x7A50 == 0) {
			MsgWinData* d2 = smart->address;
			if (d2->flags & 8) {
				BtlUnit_ChangeStayAnim(d2->unitId);
			}
			else {
				npcSetStayPose(d2->stayPose);
			}
			data->field_0x7A54 = 0;
		}
	}

	switch (WIN_STATE(window)) {
	case 5:
		if (!(window->flags & 8)) {
			se = msgWindowOpen_SE_Data[window->type * 2];
			if (se >= 0) {
				psndSFXOn((const char*)(se | 0x20000));
			}
		}
		WIN_TIME(window) = gp->renderTime;
		WIN_STATE(window) = 6;
	case 6:
		window->flags |= 2;
		window->alpha = OSTicksToMilliseconds(gp->renderTime - WIN_TIME(window)) * 255 / 200;
		if (window->alpha > 255) {
			window->alpha = 255;
			WIN_STATE(window) = 1;
			data->time18 = gp->renderTime;
			data->time30 = gp->renderTime;
		}
		break;
	case 7:
		if (!(window->flags & 8)) {
			se = msgWindowOpen_SE_Data[window->type * 2 + 1];
			if (se >= 0) {
				psndSFXOn((const char*)(se | 0x20000));
			}
		}
		WIN_TIME(window) = gp->renderTime;
		WIN_STATE(window) = 8;
	case 8:
		if (window->alpha == 0) {
			windowDelete(window);
			return;
		}
		window->alpha = 255 - OSTicksToMilliseconds(gp->renderTime - WIN_TIME(window)) * 255 / 200;
		if (window->alpha <= 0) {
			window->alpha = 0;
		}
		break;
	case 1:
		switch (msgMain(window->userdata)) {
		case 0:
			WIN_STATE(window) = 7;
			if (WIN_DATA(window)->flags & 8) {
				BtlUnit_ChangeStayAnim(WIN_DATA(window)->unitId);
			}
			else {
				npcSetStayPose(WIN_DATA(window)->stayPose);
			}
			break;
		case 1:
			WIN_STATE(window) = 2;
			window->flags &= ~2;
			if (WIN_DATA(window)->flags & 8) {
				BtlUnit_ChangeStayAnim(WIN_DATA(window)->unitId);
			}
			else {
				npcSetStayPose(WIN_DATA(window)->stayPose);
			}
			break;
		case 2:
			WIN_STATE(window) = 3;
			break;
		case 3:
			break;
		}
		break;
	case 3:
		target = 0x100;
		if (WIN_DATA(window)->flags & 0x100) {
			target = 0x500;
		}
		trg = keyGetButtonTrg(0);
		if (trg & (target | 0x200)) {
			WIN_STATE(window) = 1;
			data->field_0xA = 2;
			if (keyGetButtonTrg(0) & 0x200) {
				if (!(data->flags & 0x80)) {
					data->flags |= 4;
				}
			}
		}
		if (keyGetButtonTrg(0) & 0x10) {
			data->page = data->field_0x7840 - 1;
			if (msgWinPrevPage(window) != 0U) {
				WIN_STATE(window) = 9;
				WIN_TIME(window) = gp->renderTime;
				psndSFXOn((const char*)0x20041);
				data->flags |= 0x40;
			}
		}
		break;
	case 9:
		target = data->pageY[data->page];
		if (data->field_0x28 >= target) {
			data->field_0x28 = data->field_0x28 - 0.6f * OSTicksToMilliseconds(gp->renderTime - WIN_TIME(window));
			WIN_TIME(window) = gp->renderTime;
			if (data->field_0x28 <= target) {
				data->field_0x28 = target;
				WIN_STATE(window) = 11;
			}
		}
		break;
	case 10:
		target = data->pageY[data->page];
		if (data->field_0x28 <= target) {
			data->field_0x28 = data->field_0x28 + 0.6f * OSTicksToMilliseconds(gp->renderTime - WIN_TIME(window));
			WIN_TIME(window) = gp->renderTime;
			if (data->field_0x28 >= target) {
				data->field_0x28 = target;
				if (data->page == data->field_0x7840 - 1) {
					WIN_STATE(window) = 3;
					data->flags &= ~0x40;
				}
				else {
					WIN_STATE(window) = 11;
				}
			}
		}
		break;
	case 11:
		target = 0x100;
		if (WIN_DATA(window)->flags & 0x100) {
			target = 0x500;
		}
		trg = keyGetButtonTrg(0);
		if (trg & target) {
			WIN_STATE(window) = 10;
			WIN_TIME(window) = gp->renderTime;
			msgWinNextPage(window);
			psndSFXOn((const char*)0x20041);
		}
		if (keyGetButtonTrg(0) & 0x200) {
			WIN_STATE(window) = 10;
			WIN_TIME(window) = gp->renderTime;
			data->page = data->field_0x7840 - 1;
			psndSFXOn((const char*)0x20041);
		}
		if (keyGetButtonTrg(0) & 0x10) {
			WIN_STATE(window) = 9;
			WIN_TIME(window) = gp->renderTime;
			if (msgWinPrevPage(window) != 0U) {
				psndSFXOn((const char*)0x20041);
			}
		}
		break;
	}
	dispEntry(CAMERA_2D, 400.0f - *(s16*)&window->field_0x4, 0, msgWindow_Disp, window);
}

#pragma opt_common_subs reset
void msgWindow_Clear_Main(WindowEntry* window) {
	MsgWinData* data = WIN_DATA(window);

	switch (WIN_STATE(window)) {
	case 5:
		WIN_STATE(window) = 1;
		WIN_TIME(window) = gp->renderTime;
		data->time18 = gp->renderTime;
		data->time30 = gp->renderTime;
	case 1:
	case 6:
		window->flags |= 2;
		if (window->alpha < 255) {
			window->alpha = OSTicksToMilliseconds(gp->renderTime - WIN_TIME(window)) * 255 / 200;
			if (window->alpha > 255) {
				window->alpha = 255;
			}
		}
		if (WIN_STATE(window) != 2) {
			switch (msgMain(window->userdata)) {
			case 0:
				WIN_STATE(window) = 7;
				WIN_TIME(window) = gp->renderTime;
				if (WIN_DATA(window)->flags & 8) {
					BtlUnit_ChangeStayAnim(WIN_DATA(window)->unitId);
				}
				else {
					npcSetStayPose(WIN_DATA(window)->stayPose);
				}
				break;
			case 1:
				WIN_STATE(window) = 2;
				window->flags &= ~2;
				if (WIN_DATA(window)->flags & 8) {
					BtlUnit_ChangeStayAnim(WIN_DATA(window)->unitId);
				}
				else {
					npcSetStayPose(WIN_DATA(window)->stayPose);
				}
				break;
			case 2:
				WIN_STATE(window) = 3;
				break;
			case 3:
				break;
			}
		}
		break;
	case 7:
		if (window->alpha == 0) {
			windowDelete(window);
			return;
		}
		window->alpha = 255 - OSTicksToMilliseconds(gp->renderTime - WIN_TIME(window)) * 255 / 200;
		if (window->alpha <= 0) {
			window->alpha = 0;
		}
		break;
	}
	dispEntry(CAMERA_2D, 400.0f - *(s16*)&window->field_0x4, 0, msgWindow_Disp, window);
}

void msgWindow_Disp(CameraId camId, void* param) {
	f32 new_var;
	CameraEntry* camera = camGetCurPtr();
	BOOL ret = FALSE;
	WindowEntry* window = param;
	Vec pos;
	f32  y; f32 w; f32 h;
	f32 ex; f32 ey;
	s32 sy;
	static u16 active;

	GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0, 0, 0, 0});

	switch (window->type) {
	case 0:
	case 1:
	case 6:
	case 8:
	case 9:
		if (window->field_0x2C != 0) {
			if (window->field_0x2C & 0x10) {
				pos = *(( Vec*)( ((u8*)window ) + 0x30) );
			} else {
				getScreenPoint((Vec*)((( u8*)window ) + 0x30), &pos);
			}
			switch (window->type) {
			case 0:
			case 6:
			case 8:
			case 9:
				ret = window->alpha;
				ret = window->alpha;
				ex = ( window->height / 2.0f ) + window->x;
				ey = intplGetValue(0, ret, 255, pos.x, ex);
				ey = window->y - ( window->width / 2.0f) ;
				y = intplGetValue(0, ret, 255, pos.y, ey);
				w = intplGetValue(0, ret, 255, 10.0f, window->height);
				h = intplGetValue(0, ret, 255, 10.0f, window->width);
				windowDispGX_Message(window->type, window->field_0x2C, window->alpha, ey - ( w / 2.0f) , y + ( h / 2.0f) , w, h, pos.x, pos.y);
				if (window->alpha == 255) {
					GXSetScissor(camera->scissor[0], 240.0f - (window->y - 36.0f), camera->scissor[2], 100);
					ret = msgDisp(window->userdata, window->alpha, 62.0f + window->x, window->y - 36.0f);
				}
				break;
			case 1:
				window->x = pos.x - ( window->height / 2.0f) ;
				if (window->field_0x2C & 8) {
					window->y = pos.y - 80.0f;
				} else {
					window->y = 60.0f + pos.y;
				}
				ret = window->alpha;
				ex = ( window->height / 2.0f ) + window->x;
				ey = intplGetValue(0, ret, 255, pos.x, ex);
				ey = window->y ; ey = ey - ( window->width / 2.0f) ;
				y = intplGetValue(0, ret, 255, pos.y, ey);
				w = intplGetValue(0, ret, 255, 10.0f, window->height);
				h = intplGetValue(0, ret, 255, 10.0f, window->width); new_var = h ;
				windowDispGX_Message(window->type, window->field_0x2C, window->alpha, ey - ( w / 2.0f) , y + ( h / 2.0f) , w, new_var, pos.x, pos.y);
				if (window->alpha == 255) {
					sy = 240 - ((( s32)window->y ) - 10);
					if (sy < 0) { sy = 0;
					}
					if (sy > 480) { sy = 480;
					}
					GXSetScissor(camera->scissor[0], sy, camera->scissor[2], 0x7E);
					msgDisp(window->userdata, window->alpha, 20.0f + window->x, window->y - 7.0f);
				}
				break;
			}
		} else {
			windowDispGX_Message(window->type, 0, window->alpha, window->x, window->y, window->height, window->width, 0.0f, 0.0f);
			GXSetScissor(camera->scissor[0], ( 240.0f - (window->y - 36.0f) ) - 8.0f, camera->scissor[2], 0x7E);
			ret = msgDisp(window->userdata, window->alpha, 62.0f + window->x, window->y - 36.0f);
		}
		break;
	case 2:
	case 4:
	case 10:
		windowDispGX_Kanban(window->type, window->alpha, window->x, window->y, window->height, window->width);
		GXSetScissor(camera->scissor[0], ( 240.0f - (window->y - 36.0f) ) - 2.0f, camera->scissor[2], 0x68);
		ret = msgDisp(window->userdata, window->alpha, 62.0f + window->x, window->y - 36.0f);
		break;
	case 7:
		windowDispGX_Kanban(window->type, window->alpha, window->x, window->y, window->height, window->width);
		GXSetScissor(camera->scissor[0], ( 240.0f - (window->y - 36.0f) ) - 8.0f, camera->scissor[2], 0x7E);
		ret = msgDisp(window->userdata, window->alpha, 62.0f + window->x, window->y - 36.0f);
		break;
	case 3:
		windowDispGX_System(window->type, window->alpha, window->x, window->y, window->height, window->width);
		GXSetScissor(camera->scissor[0], ( 240.0f - (window->y - 36.0f) ) - 8.0f, camera->scissor[2], window->width - 50.0f);
		ret = msgDisp(window->userdata, window->alpha, 62.0f + window->x, window->y - 36.0f);
		break;
	case 11:
		GXSetScissor(camera->scissor[0], ( 240.0f - (window->y - 36.0f) ) - 8.0f, camera->scissor[2], window->width - 50.0f);
		ret = msgDisp(window->userdata, window->alpha, 62.0f + window->x, window->y - 36.0f);
		break;
	case 5:
		break;
	}

	GXSetScissor(camera->scissor[0], camera->scissor[1], camera->scissor[2], camera->scissor[3]);
	if (ret) {
		if (active == 0) { active = 1;
		}
		animPoseMain(msgw->poseId);
		animPoseDraw(msgw->poseId, ( window->x + window->height ) - 52.0f, 31.0f + (window->y - window->width), 0.0f, 180.0f, 5.0f, 2);
	}
}

void selectWindow_Main(WindowEntry* window) {
	MsgWinData* data = window->userdata->address;
	s8 prev;

	msgMain(window->userdata);
	switch (WIN_STATE(window)) {
	case 5:
		window->alpha += 25;
		if (window->alpha > 255) {
			window->alpha = 255;
			WIN_STATE(window) = 1;
		}
		break;
	case 1:
		prev = data->sel;
		if ((keyGetButtonTrg(0) & 8) || (keyGetDirTrg(0) & 0x1000)) {
			data->sel--;
		}
		else if ((keyGetButtonRep(0) & 8) || (keyGetDirRep(0) & 0x1000)) {
			if (data->sel) {
				data->sel--;
			}
		}
		if ((keyGetButtonTrg(0) & 4) || (keyGetDirTrg(0) & 0x2000)) {
			data->sel++;
		}
		else if ((keyGetButtonRep(0) & 4) || (keyGetDirRep(0) & 0x2000)) {
			if (data->sel < data->numSel - 1) {
				data->sel++;
			}
		}
		if (data->sel < 0) {
			data->sel = data->numSel - 1;
		}
		if (data->sel >= data->numSel) {
			data->sel = 0;
		}
		if (prev != data->sel) {
			psndSFXOn((const char*)0x20005);
		}
		if (keyGetButtonTrg(0) & 0x200) {
			switch (data->cancel) {
			case -1:
				break;
			case -2:
				data->sel = -1;
				WIN_STATE(window) = 7;
				psndSFXOn((const char*)0x20013);
				break;
			default:
				data->sel = data->cancel;
				WIN_STATE(window) = 7;
				psndSFXOn((const char*)0x20013);
				break;
			}
		}
		else if (keyGetButtonTrg(0) & 0x100) {
			WIN_STATE(window) = 7;
			psndSFXOn((const char*)0x20012);
		}
		break;
	case 7:
		if (window->alpha == 0) {
			WIN_STATE(window) = 4;
			window->flags &= ~2;
			return;
		}
		window->alpha -= 25;
		if (window->alpha <= 0) {
			window->alpha = 0;
		}
		break;
	case 4:
		return;
	}
	dispEntry(CAMERA_2D, 400.0f - *(s16*)&window->field_0x4, 0, selectWindow_Disp, window);
}

void selectWindow_Disp(CameraId camId, void* param) {
	WindowEntry* window = param; //cast to correct type
	MsgWinData* data = window->userdata->address;
	Vec pos;

	GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0, 0, 0, 0});
	windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, window->alpha}, window->x, window->y, window->height, window->width, 30.0f);
	msgDisp(window->userdata, window->alpha, 40.0f + window->x, window->y - 25.0f);
	pos.x = 2.0f + window->x;
	data->cursorY += 0.3f * (window->y - (f32)(data->sel * 31 + 58) - data->cursorY);
	pos.y = data->cursorY;
	pos.z = 0.0f;
	iconDispGxAlpha(&pos, 0x14, 0x1F0, window->alpha, 1.0f);
}
