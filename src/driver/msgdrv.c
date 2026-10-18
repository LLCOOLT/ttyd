// FAKE: whole unit as G5 asm stopgap (force_active + fixbase); C under #ifdef NONMATCHING.
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
__declspec(section ".rodata") const char R_no_messages_JP[] = "<col ff0000ff>\203\201\203b\203Z\201[\203W\202\252\202\240\202\350\202\334\202\271\202\361</col>\n<key>\000\000\000";
__declspec(section ".rodata") const char R_no_messages_US[] = "<col ff0000ff>No messages.<col>\n<key>\000\000";
__declspec(section ".rodata") const char str_802C4E4C[12] = "\123\124\111\103\113\137\114\105\106\124\000";
__declspec(section ".rodata") const char str_802C4E58[12] = "\102\125\124\124\117\116\137\114\000\000\000";
__declspec(section ".rodata") const char str_802C4E64[12] = "\102\125\124\124\117\116\137\122\000\000\000";
__declspec(section ".rodata") const char str_802C4E70[12] = "\120\101\104\137\130\137\117\116\000\000\000";
__declspec(section ".rodata") const char str_802C4E7C[12] = "\120\101\104\137\131\137\117\116\000\000\000";
__declspec(section ".rodata") const char str_802C4E88[12] = "\120\101\104\137\132\137\117\106\106\000\000";
__declspec(section ".rodata") const char str_802C4E94[12] = "\120\101\104\137\123\124\137\117\106\106\000";
__declspec(section ".rodata") const char str_802C4EA0[12] = "\142\154\141\143\153\137\153\145\171\000\000";
__declspec(section ".rodata") const char str_802C4EAC[12] = "\101\116\115\137\120\101\104\137\101\000\000";
__declspec(section ".rodata") const char str_802C4EB8[16] = "\101\116\115\137\123\124\111\103\113\137\122\111\107\110\124";
__declspec(section ".rodata") const char str_802C4EC8[16] = "\101\116\115\137\120\101\104\137\123\124\101\122\124\000\000";
__declspec(section ".rodata") const char str_802C4ED8[8] = "\120\115\137\131\137\061\102";
__declspec(section ".rodata") const char str_802C4EE0[8] = "\120\115\137\131\137\062\102";
__declspec(section ".rodata") const char str_802C4EE8[8] = "\120\115\137\106\137\061\102";
__declspec(section ".rodata") const char str_802C4EF0[8] = "\120\115\137\106\137\063\102";
__declspec(section ".rodata") const char str_802C4EF8[8] = "\120\115\137\103\137\061\102";
__declspec(section ".rodata") const char str_802C4F00[8] = "\120\115\137\103\137\062\102";
__declspec(section ".rodata") const f64 double_to_int_802c4f08 = 4503601774854144;
__declspec(section ".rodata") const f64 double_to_int_mask_802c4f10 = 4503599627370496;
__declspec(section ".rodata") const char str_802C4F18[8] = "\153\145\171\170\157\156\000";
__declspec(section ".rodata") const char str_802C4F20[12] = "\163\143\162\154\137\141\165\164\157\000\000";
__declspec(section ".rodata") const char str_802C4F2C[12] = "\157\156\143\145\137\163\164\157\160\000\000";
__declspec(section ".rodata") const char str_802C4F38[8] = "\057\163\143\141\154\145\000";
__declspec(section ".rodata") const char str_802C4F40[8] = "\057\163\160\145\145\144\000";
__declspec(section ".rodata") const char str_802C4F48[8] = "\144\171\156\141\155\151\143";
__declspec(section ".rodata") const char str_802C4F50[12] = "\057\144\171\156\141\155\151\143\000\000\000";
__declspec(section ".rodata") const char str_802C4F5C[8] = "\057\163\150\141\153\145\000";
__declspec(section ".rodata") const char str_802C4F64[8] = "\057\156\157\151\163\145\000";
__declspec(section ".rodata") const char str_802C4F6C[8] = "\163\171\163\164\145\155\000";
__declspec(section ".rodata") const char str_802C4F74[8] = "\150\157\165\163\157\165\000";
__declspec(section ".rodata") const char str_802C4F7C[8] = "\153\141\156\142\141\156\000";
__declspec(section ".rodata") const char str_802C4F84[16] = "\045\150\144\045\150\144\045\150\144\045\150\144\000\000\000";
__declspec(section ".rodata") const char str_802C4F94[8] = "\163\145\154\145\143\164\000";
__declspec(section ".rodata") const char str_802C4F9C[16] = "\045\150\144\045\150\144\045\150\144\045\150\144\045\150\144";
__declspec(section ".rodata") const char str_802C4FAC[8] = "\156\157\167\151\156\163\145";
__declspec(section ".rodata") const char str_802C4FB4[12] = "\045\144\045\146\045\144\045\144\045\144\000";
__declspec(section ".rodata") const char str_802C4FC0[12] = "\045\163\045\146\045\144\045\144\045\144\000";
__declspec(section ".rodata") const char str_802C4FCC[16] = "\045\163\045\163\045\144\045\144\045\146\045\144\000\000\000";
__declspec(section ".rodata") const char str_802C4FDC[8] = "\057\160\141\160\145\162\000";
__declspec(section ".rodata") const char str_802C4FE4[8] = "\160\137\142\137\163\164\000";
__declspec(section ".rodata") const char str_802C4FEC[12] = "\056\057\045\163\057\045\163\056\164\170\164";
__declspec(section ".rodata") const char str_802C4FF8[8] = "\150\157\163\150\151\137\062";
__declspec(section ".rodata") const char str_802C5000[8] = "\110\117\123\137\103\137\061";
__declspec(section ".rodata") const char str_802C5008[8] = "\147\154\157\142\141\154\000";

extern const char R_no_messages_JP[];
extern const char R_no_messages_US[];
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on

extern GlobalWork* gp;
extern int sprintf(char* str, const char* format, ...);
extern int sscanf(const char* str, const char* format, ...);

#define WIN_STATE(w) (*(u16*)(w)->field_0x0)

typedef struct MsgChar {
	u32 value; //0x0
	u16 glyph; //0x4
	s16 x; //0x6 (page-break entries: page number)
	s16 y; //0x8 (page-scroll entries: scroll amount)
	u8 field_0xA[0xC - 0xA]; //0xA
	u32 time; //0xC
	u8 field_0x10[0x18 - 0x10]; //0x10
} MsgChar;

typedef struct MsgWinData {
	const char* tag; //0x0
	u32 flags; //0x4
	u16 curPage; //0x8, page being shown (page-break entries carry their page number)
	u16 pageState; //0xA, 1: waiting for the key, 2: advance to the next page
	u16 pageAdvanced; //0xC
	u8 field_0xE[0x10 - 0xE]; //0xE
	s32 nextEntry; //0x10, index into entries
	u8 field_0x14[0x18 - 0x14]; //0x14
	OSTime time18; //0x18
	s32 playTime; //0x20, playback clock (ms) compared with entries[].time
	s32 scrollTarget; //0x24
	s32 scrollPos; //0x28, eases toward scrollTarget
	u8 field_0x2C[0x30 - 0x2C]; //0x2C
	OSTime time30; //0x30
	s32 count; //0x38
	MsgChar entries[0x500]; //0x3C
	s32 page; //0x783C
	s32 pageCount; //0x7840, number of pageY entries
	s32 pageY[(0x79FC - 0x7844) / 4]; //0x7844
	s32 callback; //0x79FC, void (*)(s32 event, smartEntry*), see MSG_CB
	u8 field_0x7A00[0x7A04 - 0x7A00]; //0x7A00
	char stayPose[0x20]; //0x7A04
	s32 unitId; //0x7A24
	s32 field_0x7A28; //0x7A28
	u8 sfxVolume; //0x7A2C, default 0x7F
	u8 field_0x7A2D[0x7A30 - 0x7A2D]; //0x7A2D
	s32 parseTime; //0x7A30, msgAnalize state
	s16 parseX; //0x7A34
	s16 parseY; //0x7A36
	s16 field_0x7A38; //0x7A38
	s16 field_0x7A3A; //0x7A3A
	s32 parseSpeed; //0x7A3C, text speed (default 25)
	s8 numSel; //0x7A40
	s8 defSel; //0x7A41
	s8 cancel; //0x7A42
	s8 sel; //0x7A43
	s16 selWidth; //0x7A44
	s16 selY; //0x7A46
	f32 cursorY; //0x7A48
	WindowEntry* window; //0x7A4C
	s32 talkTimer; //0x7A50, frames until the talk pose is set
	s32 talkPoseSet; //0x7A54
} MsgWinData;

#define MSG_CB(d) (*(void (**)(s32, smartEntry*))&(d)->callback)
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

//.data
#ifdef NONMATCHING
#define STR(sym, lit) lit
#else
#define STR(sym, lit) sym
extern const char str_8041A6A4[];
// FAKE: .sdata2 strings named so the asm can reference them
__declspec(section ".sdata2") const char str_8041A4B0[8] = "PAD_A";
__declspec(section ".sdata2") const char str_8041A4B8[8] = "PAD_B";
__declspec(section ".sdata2") const char str_8041A4C0[8] = "STICK";
__declspec(section ".sdata2") const char str_8041A4C8[8] = "AC_ON";
__declspec(section ".sdata2") const char str_8041A4D0[4] = "HM";
__declspec(section ".sdata2") const char str_8041A4D4[8] = "PAD_X";
__declspec(section ".sdata2") const char str_8041A4DC[8] = "PAD_Y";
__declspec(section ".sdata2") const char str_8041A4E4[4] = "msg";
__declspec(section ".sdata2") const char str_8041A4E8[8] = "emsg";
#endif
MsgIcon msgIcon[] = {
	{STR(str_8041A4B0, "PAD_A"), 0x64},
	{STR(str_8041A4B8, "PAD_B"), 0x66},
	{str_802C4E4C, 0x78},
	{STR(str_8041A4C0, "STICK"), 0x79},
	{STR(str_8041A4C8, "AC_ON"), 0x95},
	{str_802C4E58, 0x7E},
	{str_802C4E64, 0x80},
	{STR(str_8041A4D0, "HM"), 0x19F},
	{STR(str_8041A4D4, "PAD_X"), 0x68},
	{str_802C4E70, 0x69},
	{STR(str_8041A4DC, "PAD_Y"), 0x6A},
	{str_802C4E7C, 0x6B},
	{str_802C4E88, 0x82},
	{str_802C4E94, 0x84},
	{str_802C4EA0, 0x130},
	{str_802C4EAC, 0x20B},
	{str_802C4EB8, 0x20C},
	{str_802C4EC8, 0x20D}
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
	str_802C4ED8, str_802C4EE0, str_802C4EE8,
	str_802C4EF0, str_802C4EF8, str_802C4F00
};
const char* language_dir[2] = {STR(str_8041A4E4, "msg"), STR(str_8041A4E8, "emsg")};





//local prototypes
int msg_compare(const void* a, const void* b);
void msgDispKeyWait_render(s32 wXluStage);

void msgInit(void) {
	msgw->poseId = animPoseEntry(str_802C4FF8, 2);
	animPoseSetAnim(msgw->poseId, str_802C5000, TRUE);
	animPoseSetMaterialFlagOn(msgw->poseId, 0x1800);
	animPoseSetMaterialFlagOff(msgw->poseId, 0x40);
	animPoseSetGXFunc(msgw->poseId, msgDispKeyWait_render, 0);
	msgw->entries[0].address = NULL;
	msgw->entries[0].lookup = NULL;
	msgw->entries[1].address = NULL;
	msgw->entries[1].lookup = NULL;
	msgLoad(STR(str_802C5008, "global\0"), 1);
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
	sprintf(filepath, str_802C4FEC, language_dir[gp->language], filename);
	
	if (entry->address) {
		if (index == 1) {
			__memFree(HEAP_DEFAULT, entry->address);
		}
		entry->address = NULL;
	}
	entry->length = 0;

	if (!entry->address) {
		sprintf(dvdpath, STR(str_8041A6A4, "%s/%s"), getMarioStDvdRoot(), filepath);
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
	if (!(d->flags & 0x200) && d->pageCount < 110) {
		if (d->pageCount == 0 || d->pageY[d->pageCount - 1] != y) {
			d->pageY[d->pageCount++] = y;
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
		psndSFXOnVol((const char*)0x20044, d->sfxVolume);
		msgSEflag = 1;
	}
}

#ifdef NONMATCHING
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
	if (data->scrollTarget > data->scrollPos) {
		data->scrollPos += 0.36f * OSTicksToMilliseconds(gp->renderTime - data->time30);
		msgCheckSkip(smart, data);
		if (!(data->flags & 0x10) && (data->flags & 4)) {
			data->scrollPos += 0.36f * OSTicksToMilliseconds(gp->renderTime - data->time30);
		}
		if (data->scrollTarget < data->scrollPos) {
			data->scrollPos = data->scrollTarget;
		}
		data->time30 = gp->renderTime;
		return 3;
	}
	switch (data->pageState) {
	case 1:
		return 2;
	case 2:
		data->pageAdvanced = 1;
		data->curPage++;
		data->pageState = 0;
		psndSFXOn((const char*)0x2003D);
		data->playTime += 100;
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
		data->playTime += ms;
		break;
	}
	data->time30 = gp->renderTime;
	entry = &data->entries[data->nextEntry];
	for (i = data->nextEntry; i < 0x500; i++, entry++) {
		if (entry->time > data->playTime) {
			break;
		}
		switch (entry->glyph) {
		case 0xFFFF:
			if (MSG_CB(data)) {
				MSG_CB(data)(1, smart);
			}
			data->nextEntry = i;
			return 0;
		case 0xFFFE:
			if (entry->x == data->curPage) {
				data->pageState = 1;
				data->playTime = entry->time;
				data->flags &= ~4;
				if (MSG_CB(data)) {
					MSG_CB(data)(2, smart);
				}
			}
			break;
		case 0xFFFD:
			data->scrollTarget -= entry->y;
			data->playTime = entry->time;
			msgAddPage(smart, data->scrollTarget);
			break;
		case 0xFFFC:
			data->nextEntry = i + 1;
			data->playTime = entry->time;
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
			data->sfxVolume = entry->value;
			break;
		case 0xFFF5:
			if (entry->value) {
				data->flags |= 0x80;
				data->flags &= ~4;
				data->playTime = entry->time;
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
			animPoseSetPaperAnimGroup(npc->poseId, str_802C4FE4, 1);
			animPosePaperPeraOn(npc->poseId);
			animPoseSetPaperAnim(npc->poseId, paperPoseTbl[entry->time], 1);
			break;
		case 0xFFF2:
			npc = (NpcEntry*)entry->value;
			if (data->pageState) {
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
					((MsgWinData*)smart->address)->talkTimer = 15;
				}
				msgVoiceSE(smart);
			}
			break;
		}
	}
	data->nextEntry = i;
	if (data->pageState) {
		return 2;
	}
	return 3;
}
#endif


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
#ifdef NONMATCHING
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
	for (i = 0; i < data->nextEntry; i++, c++) {
		switch (c->glyph) {
			case 0xFFFF:
				return FALSE;
			case 0xFFFE:
				if (data->curPage == c->x) {
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
				PSMTXTransApply(m, m, x + c->x, c->y + (y + data->scrollPos) - 40.0f, 0.0f);
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
				sy = c->y + (y + data->scrollPos);
				if (data->flags & 0x40) {
					page = data->page;
					py = data->pageY[page];
					if (data->scrollPos == py) {
						if (c->y + data->pageY[page + 1] <= 0) {
							break;
						}
						hide = 1;
					}
					else if (data->scrollPos < py) {
						if (c->y + py > 0) {
							hide = 1;
						}
						else {
							d = py - data->scrollPos;
							if (d > 100) {
								d = 100;
							}
							a = (100 - d) * 255 / 100;
							if (page != data->pageCount - 1) {
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
							d = data->scrollPos - py;
							if (d > 100) {
								d = 100;
							}
							a = d * 255 / 100;
							if (page != data->pageCount - 2) {
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
					pos.y = c->iconY + (c->y + (y + data->scrollPos) - 40.0f);
					pos.z = 0.0f;
					iconDispGxAlpha(&pos, 0x10, (u16)c->value, a * al / 255, c->scale);
					FontDrawStart_alpha(alpha);
					FontDrawColor(col4);
					break;
				}
				if ((f32)(c->y + data->scrollPos) >= 32.0f * c->scale - 10.0f) {
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
#endif
#pragma dont_inline reset

#ifdef NONMATCHING
void msgDispKeyWait_render(s32 wXluStage) {
	AnimationWork* wp = animGetPtr();

	GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
	GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	GXSetZCompLoc(GX_FALSE);
	GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
	wp->currDispMode = wXluStage;
}
#endif

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

#ifdef NONMATCHING
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
	char anim1[0x20];
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
	s32 i28;
	s32 i24;
	f32 iconScale;
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
	time = data->parseTime;
	s234 = 0;
	s232 = data->field_0x7A38;
	x = data->parseX;
	s230 = data->field_0x7A3A;
	y = data->parseY;
	step = data->parseSpeed;
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
			data->parseTime = time;
			data->parseX = x;
			data->parseY = y;
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
			continue;
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
			} else if (strcmp(tag, str_802C4F18) == 0) {
				data->flags |= 0x100;
			} else if (( strcmp(tag, "p") == 0 ) || ( strcmp(tag, str_802C4F20) == 0) ) {
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
			} else if (( strcmp(tag, "o") == 0 ) || ( strcmp(tag, str_802C4F2C) == 0) ) {
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
			} else if (strcmp(tag, str_802C4F38) == 0) {
				scale = 1.0f;
			} else if (strcmp(tag, "wait") == 0) {
				sscanf(args, "%d", &v40);
				time += v40;
			} else if (strcmp(tag, "speed") == 0) {
				sscanf(args, "%d", &step);
			} else if (strcmp(tag, str_802C4F40) == 0) {
				step = data->parseSpeed;
			} else if (strcmp(tag, str_802C4F48) == 0) {
				sscanf(args, "%f", &fv);
				flags |= 1;
			} else if (strcmp(tag, str_802C4F50) == 0) {
				flags &= ~1;
			} else if (strcmp(tag, "shake") == 0) {
				flags |= 2;
			} else if (strcmp(tag, str_802C4F5C) == 0) {
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
			} else if (strcmp(tag, str_802C4F64) == 0) {
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
				data->parseSpeed = 0;
			} else if (strcmp(tag, str_802C4F6C) == 0) {
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
			} else if (strcmp(tag, str_802C4F74) == 0) {
				window->type = 10;
			} else if (strcmp(tag, "boss") == 0) {
				window->type = 6;
			} else if (strcmp(tag, str_802C4F7C) == 0) {
				window->type = 4;
				step = 0;
				data->parseSpeed = 0;
			} else if (strcmp(tag, "small") == 0) {
				window->type = 1;
				data->flags |= 0x10;
			} else if (strcmp(tag, "clear") == 0) {
				window->type = 11;
			} else if (strcmp(tag, "wpos") == 0) {
				sscanf(args, str_802C4F84, &w16, &w14, &w12, &w10);
				window->flags |= 4;
				window->x = w16;
				window->y = w14;
				window->height = w12;
				window->width = w10;
			} else if (strcmp(tag, str_802C4F94) == 0) {
				window->type = 5;
				data->flags |= 0x20;
				sscanf(args, str_802C4F9C, &sel0, &sel1, &data->selWidth, &data->selY);
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
			} else if (strcmp(tag, str_802C4FAC) == 0) {
				window->flags |= 8;
			} else if (strcmp(tag, "icon") == 0) {
				isHM = FALSE;
				if ((( (s8) args [0] ) >= '0') && (((s8) args [0]) <= '9') ) {
					sscanf(args, str_802C4FB4, &iconId, &iconScale, &i38, &i34, &i30);
				} else {
					sscanf(args, str_802C4FC0, name, &iconScale, &i38, &i34, &i30);
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
				sscanf(args, str_802C4FCC, anim1, anim2, &i28, &i24, &f1c, &i20);
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
			} else if (strcmp(tag, str_802C4FDC) == 0) {
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
				p = tag;
				p = p + i;
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
			if (((( (u32)gp->language ) == 0 ) && (( (s8)check ) >= '0' )) && (( (s8)check ) <= '9') ) {
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
#endif

#ifdef NONMATCHING
MessageWork* L_msgGetWork(void) {
	return &msgWork;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
BOOL _ismbblead(u32 a1) {
	a1 = (u8)a1;
	if ((a1 >= 0x81 && a1 <= 0x9F) || (a1 >= 0xE0 && a1 <= 0xFC)) {
		return TRUE;
	}
	return FALSE;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
	data->callback = field_0x79FC;
	data->time30 = gp->renderTime;
	data->time18 = gp->renderTime;
	data->field_0x7A28 = 0;
	data->sfxVolume = 0x7F;
	data->parseTime = 0;
	data->parseX = 0;
	data->parseY = 0;
	data->field_0x7A38 = 0;
	data->field_0x7A3A = 0;
	data->parseSpeed = 25;
	data->pageCount = 0;
	msgAnalize(smart, copy);
	if (window->type == 1) {
		data->flags |= 0x200;
	}
	__memFree(HEAP_DEFAULT, copy);
	window->userdata = smart;
	data = window->userdata->address;
	data->talkTimer = 0;
	data->talkPoseSet = 0;
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
#endif

#pragma optimize_for_size on
#ifdef NONMATCHING
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
#endif

#pragma optimize_for_size reset

#ifdef NONMATCHING
void msgWindow_Add(char* msg, s32 id) {
	WindowEntry* window = windowGetPointer(id);
	smartEntry* smart = window->userdata;

	((MsgWinData*)smart->address)->time30 = gp->renderTime;
	msgAnalize(smart, msg);
	WIN_STATE(window) = 1;
	window->flags |= 2;
}
#endif

#ifdef NONMATCHING
void msgWindow_Continue(s32 id) {
	WindowEntry* window = windowGetPointer(id);
	MsgWinData* data;

	WIN_STATE(window) = 1;
	window->flags |= 2;
	data = window->userdata->address;
	data->time30 = gp->renderTime;
}
#endif

#ifdef NONMATCHING
void msgWindow_Repeat(s32 id) {
	WindowEntry* window = windowGetPointer(id);
	MsgWinData* data;

	WIN_STATE(window) = 1;
	window->flags |= 2;
	data = window->userdata->address;
	data->time30 = gp->renderTime;
	data->time18 = gp->renderTime;
	data->playTime = 0;
	data->scrollTarget = 0;
	data->scrollPos = 0;
	data->nextEntry = 0;
}
#endif

#ifdef NONMATCHING
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
#endif

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
	max = d->pageCount - 1;
	if (d->page > max) {
		d->page = max;
	}
}

#pragma opt_common_subs off
#ifdef NONMATCHING
void msgWindow_Main(WindowEntry* window) {
	smartEntry* smart = window->userdata;
	MsgWinData* data = smart->address;
	s32 se;
	s32 target;
	u32 trg;

	if (data->talkTimer) {
		if (!data->talkPoseSet) {
			if (data->flags & 8) {
				BtlUnit_ChangeTalkAnim(data->unitId);
			}
			else {
				npcSetTalkPose(data->stayPose);
			}
			data->talkPoseSet = 1;
		}
		data->talkTimer--;
		if (data->talkTimer == 0) {
			MsgWinData* d2 = smart->address;
			if (d2->flags & 8) {
				BtlUnit_ChangeStayAnim(d2->unitId);
			}
			else {
				npcSetStayPose(d2->stayPose);
			}
			data->talkPoseSet = 0;
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
			data->pageState = 2;
			if (keyGetButtonTrg(0) & 0x200) {
				if (!(data->flags & 0x80)) {
					data->flags |= 4;
				}
			}
		}
		if (keyGetButtonTrg(0) & 0x10) {
			data->page = data->pageCount - 1;
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
		if (data->scrollPos >= target) {
			data->scrollPos = data->scrollPos - 0.6f * OSTicksToMilliseconds(gp->renderTime - WIN_TIME(window));
			WIN_TIME(window) = gp->renderTime;
			if (data->scrollPos <= target) {
				data->scrollPos = target;
				WIN_STATE(window) = 11;
			}
		}
		break;
	case 10:
		target = data->pageY[data->page];
		if (data->scrollPos <= target) {
			data->scrollPos = data->scrollPos + 0.6f * OSTicksToMilliseconds(gp->renderTime - WIN_TIME(window));
			WIN_TIME(window) = gp->renderTime;
			if (data->scrollPos >= target) {
				data->scrollPos = target;
				if (data->page == data->pageCount - 1) {
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
			data->page = data->pageCount - 1;
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
#endif

#pragma opt_common_subs reset
#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
void msgWindow_Disp(CameraId camId, void* param) {
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
				ex = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(pos.x, ( window->height / 2.0f ) + window->x, 0, window->alpha, 255);
				ey = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(pos.y, window->y - ( window->width / 2.0f ), 0, window->alpha, 255);
				w = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(10.0f, window->height, 0, window->alpha, 255);
				h = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(10.0f, window->width, 0, window->alpha, 255);
				windowDispGX_Message(window->type, window->field_0x2C, window->alpha, ex - ( w / 2.0f ), ey + ( h / 2.0f ), w, h, pos.x, pos.y);
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
				ex = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(pos.x, ( window->height / 2.0f ) + window->x, 0, window->alpha, 255);
				ey = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(pos.y, window->y - ( window->width / 2.0f ), 0, window->alpha, 255);
				w = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(10.0f, window->height, 0, window->alpha, 255);
				h = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(10.0f, window->width, 0, window->alpha, 255);
				windowDispGX_Message(window->type, window->field_0x2C, window->alpha, ex - ( w / 2.0f ), ey + ( h / 2.0f ), w, h, pos.x, pos.y);
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: msgMain (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
#pragma force_active on // FAKE: keep asm-only-referenced data from being dead-stripped
__declspec(section ".sdata2") const u32 dat_8041a4f0 = 0x505050FF;
__declspec(section ".sdata2") const u32 dat_8041a4f4 = 0x6E6E6EFF;
__declspec(section ".sdata2") const u32 dat_8041a4f8 = 0x00000050;
__declspec(section ".sdata2") const u32 dat_8041a4fc = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041a500 = 0xDCC8DCFF;
__declspec(section ".sdata2") const u32 dat_8041a504 = 0x00D914FF;
__declspec(section ".sdata2") const u32 dat_8041a508 = 0xDCC8DCFF;
__declspec(section ".sdata2") const u32 dat_8041a50c = 0x00D914FF;
__declspec(section ".sdata2") const u32 dat_8041a510 = 0xFFFFFF00;
__declspec(section ".sdata2") const f32 float_0_8041a514 = 0.0f;
__declspec(section ".sdata2") const f32 float_30_8041a518 = 30.0f;
__declspec(section ".sdata2") const f32 float_40_8041a51c = 40.0f;
__declspec(section ".sdata2") const f32 float_25_8041a520 = 25.0f;
__declspec(section ".sdata2") const f32 float_2_8041a524 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p3_8041a528 = 0.3f;
__declspec(section ".sdata2") const f32 float_1_8041a52c = 1.0f;
__declspec(section ".sdata2") const f32 float_400_8041a530 = 400.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041a534 = 0.5f;
__declspec(section ".sdata2") const f32 float_10_8041a538 = 10.0f;
__declspec(section ".sdata2") const f32 float_240_8041a53c = 240.0f;
__declspec(section ".sdata2") const f32 float_36_8041a540 = 36.0f;
__declspec(section ".sdata2") const f32 float_62_8041a544 = 62.0f;
__declspec(section ".sdata2") const f32 float_80_8041a548 = 80.0f;
__declspec(section ".sdata2") const f32 float_60_8041a54c = 60.0f;
__declspec(section ".sdata2") const f32 float_28_8041a550 = 20.0f;
__declspec(section ".sdata2") const f32 float_6_8041a554 = 7.0f;
__declspec(section ".sdata2") const f32 float_8_8041a558 = 8.0f;
__declspec(section ".sdata2") const f32 float_50_8041a55c = 50.0f;
__declspec(section ".sdata2") const f32 float_52_8041a560 = 52.0f;
__declspec(section ".sdata2") const f32 float_31_8041a564 = 31.0f;
__declspec(section ".sdata2") const f32 float_180_8041a568 = 180.0f;
__declspec(section ".sdata2") const f32 float_5_8041a56c = 5.0f;
__declspec(section ".sdata2") const f32 float_0p6_8041a570 = 0.6f;
__declspec(section ".sdata2") const f32 float_neg280_8041a574 = -280.0f;
__declspec(section ".sdata2") const f32 float_225_8041a578 = 225.0f;
__declspec(section ".sdata2") const f32 float_560_8041a57c = 560.0f;
__declspec(section ".sdata2") const f32 float_176_8041a580 = 176.0f;
__declspec(section ".sdata2") const f32 float_0p7_8041a584 = 0.7f;
__declspec(section ".sdata2") const f32 float_32_8041a588 = 32.0f;
__declspec(section ".sdata2") const char str_8041A58C[4] = "k\0\0";
__declspec(section ".sdata2") const char str_8041A590[4] = "key";
__declspec(section ".sdata2") const char str_8041A594[4] = "p\0\0";
__declspec(section ".sdata2") const char str_8041A598[4] = "o\0\0";
__declspec(section ".sdata2") const char str_8041A59C[4] = "pos";
__declspec(section ".sdata2") const char str_8041A5A0[8] = "%d%d\0\0\0";
__declspec(section ".sdata2") const char str_8041A5A8[8] = "scale\0\0";
__declspec(section ".sdata2") const char str_8041A5B0[4] = "%f\0";
__declspec(section ".sdata2") const char str_8041A5B4[8] = "wait\0\0\0";
__declspec(section ".sdata2") const char str_8041A5BC[4] = "%d\0";
__declspec(section ".sdata2") const char str_8041A5C0[8] = "speed\0\0";
__declspec(section ".sdata2") const char str_8041A5C8[8] = "shake\0\0";
__declspec(section ".sdata2") const char str_8041A5D0[8] = "wave\0\0\0";
__declspec(section ".sdata2") const char str_8041A5D8[8] = "/wave\0\0";
__declspec(section ".sdata2") const char str_8041A5E0[4] = "col";
__declspec(section ".sdata2") const char str_8041A5E4[4] = "%x\0";
__declspec(section ".sdata2") const char str_8041A5E8[8] = "/col\0\0\0";
__declspec(section ".sdata2") const char str_8041A5F0[8] = "noise\0\0";
__declspec(section ".sdata2") const char str_8041A5F8[8] = "dkey\0\0\0";
__declspec(section ".sdata2") const char str_8041A600[8] = "/dkey\0\0";
__declspec(section ".sdata2") const char str_8041A608[8] = "plate\0\0";
__declspec(section ".sdata2") const char str_8041A610[4] = "tec";
__declspec(section ".sdata2") const char str_8041A614[8] = "majo\0\0\0";
__declspec(section ".sdata2") const char str_8041A61C[8] = "diary\0\0";
__declspec(section ".sdata2") const char str_8041A624[8] = "boss\0\0\0";
__declspec(section ".sdata2") const char str_8041A62C[8] = "small\0\0";
__declspec(section ".sdata2") const char str_8041A634[8] = "clear\0\0";
__declspec(section ".sdata2") const char str_8041A63C[8] = "wpos\0\0\0";
__declspec(section ".sdata2") const char str_8041A644[4] = "se\0";
__declspec(section ".sdata2") const char str_8041A648[4] = "vol";
__declspec(section ".sdata2") const char str_8041A64C[8] = "icon\0\0\0";
__declspec(section ".sdata2") const char str_8041A654[8] = "anim\0\0\0";
__declspec(section ".sdata2") const char str_8041A65C[8] = "paper\0\0";
__declspec(section ".sdata2") const char str_8041A664[8] = "%s%d\0\0\0";
__declspec(section ".sdata2") const char str_8041A66C[4] = "me\0";
__declspec(section ".sdata2") const char str_8041A670[4] = "%s\0";
__declspec(section ".sdata2") const char str_8041A674[4] = "r\0\0";
__declspec(section ".sdata2") const f32 float_0p55_8041a678 = 0.55f;
__declspec(section ".sdata2") const f32 float_4_8041a67c = 4.0f;
__declspec(section ".sdata2") const f32 float_90_8041a680 = 90.0f;
__declspec(section ".sdata2") const f32 float_270_8041a684 = 270.0f;
__declspec(section ".sdata2") const f32 float_neg1_8041a688 = -1.0f;
__declspec(section ".sdata2") const f32 float_12_8041a68c = 12.0f;
__declspec(section ".sdata2") const f32 float_neg12_8041a690 = -12.0f;
__declspec(section ".sdata2") const f32 float_0p01_8041a694 = 0.01f;
__declspec(section ".sdata2") const f32 float_0p02_8041a698 = 0.02f;
__declspec(section ".sdata2") const f32 float_3p2_8041a69c = 3.2f;
__declspec(section ".sdata2") const f32 float_0p36_8041a6a0 = 0.36f;
__declspec(section ".sdata2") const char str_8041A6A4[8] = "%s/%s";
__declspec(section ".sdata2") const u32 gap_09_8041A6AC_sdata2[1] = {0};

__declspec(section ".sdata2") const u32 unk_80422fe4;
__declspec(section ".sdata2") const u32 unk_80422fe0;
void msgWindow_Disp(CameraId camId, void* param);
__declspec(section ".data") static void* jumptable_8030DB70[] = {
    (char*)msgWindow_Disp + 0x88,
    (char*)msgWindow_Disp + 0x88,
    (char*)msgWindow_Disp + 0x420,
    (char*)msgWindow_Disp + 0x520,
    (char*)msgWindow_Disp + 0x420,
    (char*)msgWindow_Disp + 0x628,
    (char*)msgWindow_Disp + 0x88,
    (char*)msgWindow_Disp + 0x4A0,
    (char*)msgWindow_Disp + 0x88,
    (char*)msgWindow_Disp + 0x88,
    (char*)msgWindow_Disp + 0x420,
    (char*)msgWindow_Disp + 0x5B4,
};
void msgWindow_Main(WindowEntry* window);
__declspec(section ".data") static void* jumptable_8030DBA0[] = {
    (char*)msgWindow_Main + 0x74C,
    (char*)msgWindow_Main + 0x2BC,
    (char*)msgWindow_Main + 0x74C,
    (char*)msgWindow_Main + 0x364,
    (char*)msgWindow_Main + 0x74C,
    (char*)msgWindow_Main + 0xCC,
    (char*)msgWindow_Main + 0x118,
    (char*)msgWindow_Main + 0x1D0,
    (char*)msgWindow_Main + 0x220,
    (char*)msgWindow_Main + 0x454,
    (char*)msgWindow_Main + 0x520,
    (char*)msgWindow_Main + 0x618,
};
BOOL msgDisp(smartEntry* smart, u8 alpha, f32 x, f32 y);
__declspec(section ".data") static void* jumptable_8030DBD0[] = {
    (char*)msgDisp + 0xE8,
    (char*)msgDisp + 0x99C,
    (char*)msgDisp + 0xCC,
    (char*)msgDisp + 0xB8,
    (char*)msgDisp + 0x1E8,
    (char*)msgDisp + 0x99C,
    (char*)msgDisp + 0x99C,
    (char*)msgDisp + 0x99C,
    (char*)msgDisp + 0x99C,
    (char*)msgDisp + 0x99C,
    (char*)msgDisp + 0xA0,
    (char*)msgDisp + 0x98,
};
s32 msgMain(smartEntry* smart);
__declspec(section ".data") static void* jumptable_8030DC00[] = {
    (char*)msgMain + 0x5A0,
    (char*)msgMain + 0x54C,
    (char*)msgMain + 0x69C,
    (char*)msgMain + 0x50C,
    (char*)msgMain + 0x5DC,
    (char*)msgMain + 0x5DC,
    (char*)msgMain + 0x69C,
    (char*)msgMain + 0x500,
    (char*)msgMain + 0x4F4,
    (char*)msgMain + 0x4D4,
    (char*)msgMain + 0x4B0,
    (char*)msgMain + 0x440,
    (char*)msgMain + 0x3F4,
    (char*)msgMain + 0x3CC,
};
void FontDrawColor(GXColor color);
void FontDrawStart_alpha(u8 alpha);
u16 GXGetTexObjHeight(const GXTexObj* to);
u16 GXGetTexObjWidth(const GXTexObj* to);
void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op);
void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color);
void GXSetScissor(u32 left, u32 top, u32 wd, u32 ht);
void GXSetTevColor(GXTevRegID id, GXColor color);
void GXSetZCompLoc(GXBool before_tex);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
void PSMTXIdentity(Mtx m);
void PSMTXScaleApply(const Mtx src, Mtx dst, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void PSMTXTransApply(const Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
void __cvt_fp2unsigned();
void __cvt_sll_flt();
void __div2i();
void* __memAlloc(HEAP_TYPE heap, u32 size);
void __memFree(HEAP_TYPE heap, void* ptr);
AnimationWork* animGetPtr(void);
void animPoseDraw(s32 poseId, f32 x, f32 y, f32 z, f32 rotY, f32 scale, s32 xluMode);
void animPoseDrawMtx(s32 poseId, Mtx matrix, s32 xluMode, f32 rotY, f32 scale);
s32 animPoseEntry(const char* animName, s32 type);
void animPoseMain(s32 poseId);
void animPosePaperPeraOn(s32 poseId);
void animPoseSetAnim(s32 poseId, const char* animName, BOOL reset);
void animPoseSetGXFunc(s32 poseId, void (*callback)(s32 wXluStage), BOOL disableDraw);
void animPoseSetMaterialFlagOff(s32 poseId, u32 mask);
void animPoseSetMaterialFlagOn(s32 poseId, u32 mask);
void animPoseSetPaperAnim(s32 poseId, const char* animName, BOOL reset);
void animPoseSetPaperAnimGroup(s32 poseId, const char* animName, BOOL someflag);
CameraEntry* camGetCurPtr(void);
void dispEntry(CameraId camera, f32 order, s32 renderMode, DispCallback callback, void* param);
void getScreenPoint(Vec* model, Vec* screen);
GXTexObj* getWakuTexObj(s32 id);
void hankakuSearch();
void iconDispGxAlpha(Vec* position, s16 flags, u16 iconId, u8 alpha, f32 scale);
void iconGetWidthHight(u16* width, u16* height, s16 iconId);
f32 intplGetValue(s32 mode, s32 currStep, s32 steps, f32 start, f32 end);
s32 irand(s32 scalar);
u16 kanjiGetWidth(u16 code);
u16 kanjiSearch(u32 code);
u32 keyGetButtonRep(u32 chan);
u32 keyGetButtonTrg(u32 chan);
u32 keyGetDirRep(u32 chan);
u32 keyGetDirTrg(u32 chan);
void *memset(void *dest, int ch, size_t count);
void msgAnalize(smartEntry* smart, char* msg);
NpcEntry* npcNameToPtr(const char* name);
void psndSFXOn(const char* name);
smartEntry* smartAlloc(u32 size, u8 type);
void smartFree(smartEntry* entry);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
size_t strlen(const char *s);
BOOL windowDelete(WindowEntry* entry);
void windowDispGX_Kanban(s32 type, u8 alpha, f32 x, f32 y, f32 height, f32 width);
void windowDispGX_Message(s32 type, s32 a2, u8 alpha, f32 x, f32 y, f32 height, f32 width, f32 a9, f32 a10);
void windowDispGX_System(s32 type, u8 alpha, f32 x, f32 y, f32 height, f32 width);
void windowDispGX_Waku_col(u16 gxTexMapID, GXColor color, f32 x, f32 y, f32 width, f32 height, f32 curve);
s32 windowEntry(u16 a1);
WindowEntry* windowGetPointer(s32 id);
static u8 g5_active_s772[2];
asm void selectWindow_Disp(CameraId camId, void* param) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	lfs f1, float_0_8041a514(r2)
	stw r0, 0x34(r1)
	fmr f2, f1
	stw r31, 0x2c(r1)
	fmr f3, f1
	fmr f4, f1
	stw r30, 0x28(r1)
	mr r30, r4
	lwz r3, 0x28(r4)
	addi r4, r1, 0x10
	lwz r0, unk_80422fe4(r2)
	lwz r31, 0x0(r3)
	li r3, 0x0
	stw r0, 0x10(r1)
	bl GXSetFog
	lwz r5, dat_8041a510(r2)
	addi r4, r1, 0xc
	lha r0, 0x6(r30)
	li r3, 0x0
	stw r5, 0x8(r1)
	lfs f5, float_30_8041a518(r2)
	stb r0, 0xb(r1)
	lwz r0, 0x8(r1)
	stw r0, 0xc(r1)
	lfs f1, 0xc(r30)
	lfs f2, 0x10(r30)
	lfs f3, 0x14(r30)
	lfs f4, 0x18(r30)
	bl windowDispGX_Waku_col
	lfs f1, float_40_8041a51c(r2)
	lfs f0, 0xc(r30)
	lha r0, 0x6(r30)
	lfs f2, 0x10(r30)
	fadds f1, f1, f0
	lfs f0, float_25_8041a520(r2)
	clrlwi r4, r0, 24
	lwz r3, 0x28(r30)
	fsubs f2, f2, f0
	bl msgDisp
	lfs f1, float_2_8041a524(r2)
	lis r0, 0x4330
	lfs f0, 0xc(r30)
	lis r3, double_to_int_802c4f08@ha
	lfd f4, double_to_int_802c4f08@l(r3)
	addi r3, r1, 0x14
	fadds f1, f1, f0
	stw r0, 0x20(r1)
	lfs f6, float_0p3_8041a528(r2)
	li r4, 0x14
	lfs f0, float_0_8041a514(r2)
	li r5, 0x1f0
	stfs f1, 0x14(r1)
	lfs f1, float_1_8041a52c(r2)
	lbz r0, 0x7a43(r31)
	lfs f5, 0x10(r30)
	extsb r0, r0
	lfs f3, 0x7a48(r31)
	mulli r6, r0, 0x1f
	addi r0, r6, 0x3a
	xoris r0, r0, 0x8000
	stw r0, 0x24(r1)
	lfd f2, 0x20(r1)
	fsubs f2, f2, f4
	fsubs f2, f5, f2
	fsubs f2, f2, f3
	fmadds f2, f6, f2, f3
	stfs f2, 0x7a48(r31)
	lfs f2, 0x7a48(r31)
	stfs f2, 0x18(r1)
	stfs f0, 0x1c(r1)
	lha r0, 0x6(r30)
	clrlwi r6, r0, 24
	bl iconDispGxAlpha
	lwz r0, 0x34(r1)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void selectWindow_Main(WindowEntry* window) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r3, 0x28(r3)
	lwz r31, 0x0(r3)
	bl msgMain
	lhz r0, 0x0(r29)
	cmpwi r0, 0x5
	beq @1
	bge @2
	cmpwi r0, 0x1
	beq @3
	blt @4
	cmpwi r0, 0x4
	bge @5
	b @4
	@2:
	cmpwi r0, 0x7
	beq @6
	b @4
	@1:
	lha r3, 0x6(r29)
	addi r0, r3, 0x19
	sth r0, 0x6(r29)
	lha r0, 0x6(r29)
	cmpwi r0, 0xff
	ble @4
	li r3, 0xff
	li r0, 0x1
	sth r3, 0x6(r29)
	sth r0, 0x0(r29)
	b @4
	@3:
	lbz r30, 0x7a43(r31)
	li r3, 0x0
	bl keyGetButtonTrg
	rlwinm. r0, r3, 0, 28, 28
	bne @7
	li r3, 0x0
	bl keyGetDirTrg
	rlwinm. r0, r3, 0, 19, 19
	beq @8
	@7:
	lbz r3, 0x7a43(r31)
	subi r0, r3, 0x1
	stb r0, 0x7a43(r31)
	b @9
	@8:
	li r3, 0x0
	bl keyGetButtonRep
	rlwinm. r0, r3, 0, 28, 28
	bne @10
	li r3, 0x0
	bl keyGetDirRep
	rlwinm. r0, r3, 0, 19, 19
	beq @9
	@10:
	lbz r3, 0x7a43(r31)
	extsb. r0, r3
	beq @9
	subi r0, r3, 0x1
	stb r0, 0x7a43(r31)
	@9:
	li r3, 0x0
	bl keyGetButtonTrg
	rlwinm. r0, r3, 0, 29, 29
	bne @11
	li r3, 0x0
	bl keyGetDirTrg
	rlwinm. r0, r3, 0, 18, 18
	beq @12
	@11:
	lbz r3, 0x7a43(r31)
	addi r0, r3, 0x1
	stb r0, 0x7a43(r31)
	b @13
	@12:
	li r3, 0x0
	bl keyGetButtonRep
	rlwinm. r0, r3, 0, 29, 29
	bne @14
	li r3, 0x0
	bl keyGetDirRep
	rlwinm. r0, r3, 0, 18, 18
	beq @13
	@14:
	lbz r0, 0x7a40(r31)
	lbz r5, 0x7a43(r31)
	extsb r3, r0
	extsb r4, r5
	subi r0, r3, 0x1
	cmpw r4, r0
	bge @13
	addi r0, r5, 0x1
	stb r0, 0x7a43(r31)
	@13:
	lbz r0, 0x7a43(r31)
	extsb. r0, r0
	bge @15
	lbz r3, 0x7a40(r31)
	subi r0, r3, 0x1
	stb r0, 0x7a43(r31)
	@15:
	lbz r3, 0x7a43(r31)
	lbz r0, 0x7a40(r31)
	extsb r3, r3
	extsb r0, r0
	cmpw r3, r0
	blt @16
	li r0, 0x0
	stb r0, 0x7a43(r31)
	@16:
	lbz r0, 0x7a43(r31)
	extsb r3, r30
	extsb r0, r0
	cmpw r3, r0
	beq @17
	lis r3, 0x2
	addi r3, r3, 0x5
	bl psndSFXOn
	@17:
	li r3, 0x0
	bl keyGetButtonTrg
	rlwinm. r0, r3, 0, 22, 22
	beq @18
	lbz r3, 0x7a42(r31)
	extsb r0, r3
	cmpwi r0, -0x1
	beq @4
	bge @19
	cmpwi r0, -0x2
	bge @20
	b @19
	@20:
	li r0, -0x1
	lis r3, 0x2
	stb r0, 0x7a43(r31)
	li r0, 0x7
	addi r3, r3, 0x13
	sth r0, 0x0(r29)
	bl psndSFXOn
	b @4
	@19:
	stb r3, 0x7a43(r31)
	li r0, 0x7
	lis r3, 0x2
	sth r0, 0x0(r29)
	addi r3, r3, 0x13
	bl psndSFXOn
	b @4
	@18:
	li r3, 0x0
	bl keyGetButtonTrg
	rlwinm. r0, r3, 0, 23, 23
	beq @4
	li r0, 0x7
	lis r3, 0x2
	sth r0, 0x0(r29)
	addi r3, r3, 0x12
	bl psndSFXOn
	b @4
	@6:
	lha r3, 0x6(r29)
	cmpwi r3, 0x0
	bne @21
	li r0, 0x4
	sth r0, 0x0(r29)
	lhz r0, 0x2(r29)
	rlwinm r0, r0, 0, 31, 29
	sth r0, 0x2(r29)
	b @5
	@21:
	subi r0, r3, 0x19
	sth r0, 0x6(r29)
	lha r0, 0x6(r29)
	cmpwi r0, 0x0
	bgt @4
	li r0, 0x0
	sth r0, 0x6(r29)
	b @4
	b @5
	@4:
	lha r4, 0x4(r29)
	lis r0, 0x4330
	lis r5, double_to_int_802c4f08@ha
	stw r0, 0x8(r1)
	xoris r4, r4, 0x8000
	lfs f2, float_400_8041a530(r2)
	stw r4, 0xc(r1)
	addi r6, r5, double_to_int_802c4f08@l
	lfd f1, 0x0(r6)
	lis r3, selectWindow_Disp@ha
	lfd f0, 0x8(r1)
	addi r5, r3, selectWindow_Disp@l
	mr r6, r29
	li r3, 0x8
	fsubs f0, f0, f1
	li r4, 0x0
	fsubs f1, f2, f0
	bl dispEntry
	@5:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void msgWindow_Disp(CameraId camId, void* param) {
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
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	stw r29, 0x24(r1)
	mr r29, r4
	bl camGetCurPtr
	lfs f1, float_0_8041a514(r2)
	mr r31, r3
	lwz r0, unk_80422fe0(r2)
	addi r4, r1, 0x8
	fmr f2, f1
	li r30, 0x0
	fmr f3, f1
	stw r0, 0x8(r1)
	fmr f4, f1
	li r3, 0x0
	bl GXSetFog
	lwz r3, 0x8(r29)
	cmplwi r3, 0xb
	bgt @1
	lis r4, jumptable_8030DB70@ha
	slwi r0, r3, 2
	addi r4, r4, jumptable_8030DB70@l
	lwzx r0, r4, r0
	mtctr r0
	bctr
	@2:
	lha r4, 0x2c(r29)
	extsh. r0, r4
	beq @3
	rlwinm. r0, r4, 0, 27, 27
	beq @4
	lwz r3, 0x30(r29)
	lwz r0, 0x34(r29)
	stw r3, 0xc(r1)
	stw r0, 0x10(r1)
	lwz r0, 0x38(r29)
	stw r0, 0x14(r1)
	b @5
	@4:
	addi r3, r29, 0x30
	addi r4, r1, 0xc
	bl getScreenPoint
	@5:
	lwz r0, 0x8(r29)
	cmpwi r0, 0x6
	beq @6
	bge @7
	cmpwi r0, 0x1
	beq @8
	bge @1
	cmpwi r0, 0x0
	bge @6
	b @1
	@7:
	cmpwi r0, 0xa
	bge @1
	cmpwi r0, 0x8
	bge @6
	b @1
	@6:
	lfs f3, 0x14(r29)
	li r3, 0x0
	lfs f2, float_0p5_8041a534(r2)
	li r5, 0xff
	lfs f0, 0xc(r29)
	lfs f1, 0xc(r1)
	fmadds f2, f3, f2, f0
	lha r4, 0x6(r29)
	bl intplGetValue
	lfs f3, 0x18(r29)
	fmr f31, f1
	lfs f2, float_0p5_8041a534(r2)
	li r3, 0x0
	lfs f0, 0x10(r29)
	li r5, 0xff
	lfs f1, 0x10(r1)
	fnmsubs f2, f3, f2, f0
	lha r4, 0x6(r29)
	bl intplGetValue
	fmr f30, f1
	lfs f1, float_10_8041a538(r2)
	lfs f2, 0x14(r29)
	li r3, 0x0
	lha r4, 0x6(r29)
	li r5, 0xff
	bl intplGetValue
	fmr f0, f1
	lfs f1, float_10_8041a538(r2)
	lfs f2, 0x18(r29)
	li r3, 0x0
	lha r4, 0x6(r29)
	li r5, 0xff
	fmr f29, f0
	bl intplGetValue
	fmr f2, f1
	lfs f0, float_0p5_8041a534(r2)
	lha r0, 0x6(r29)
	fmr f3, f29
	fnmsubs f1, f29, f0, f31
	lwz r3, 0x8(r29)
	fmr f4, f2
	lha r4, 0x2c(r29)
	lfs f5, 0xc(r1)
	clrlwi r5, r0, 24
	lfs f6, 0x10(r1)
	fmadds f2, f4, f0, f30
	bl windowDispGX_Message
	lha r0, 0x6(r29)
	cmpwi r0, 0xff
	bne @1
	lfs f1, 0x10(r29)
	lfs f0, float_36_8041a540(r2)
	lfs f2, float_240_8041a53c(r2)
	fsubs f0, f1, f0
	fsubs f1, f2, f0
	bl __cvt_fp2unsigned
	mr r4, r3
	lhz r3, 0xf4(r31)
	lhz r5, 0xf8(r31)
	li r6, 0x64
	bl GXSetScissor
	lfs f1, float_62_8041a544(r2)
	lfs f0, 0xc(r29)
	lha r0, 0x6(r29)
	lfs f2, 0x10(r29)
	fadds f1, f1, f0
	lfs f0, float_36_8041a540(r2)
	clrlwi r4, r0, 24
	lwz r3, 0x28(r29)
	fsubs f2, f2, f0
	bl msgDisp
	mr r30, r3
	b @1
	@8:
	lfs f2, 0x14(r29)
	lfs f1, float_0p5_8041a534(r2)
	lfs f0, 0xc(r1)
	fnmsubs f0, f2, f1, f0
	stfs f0, 0xc(r29)
	lha r0, 0x2c(r29)
	rlwinm. r0, r0, 0, 28, 28
	beq @9
	lfs f1, 0x10(r1)
	lfs f0, float_80_8041a548(r2)
	fsubs f0, f1, f0
	stfs f0, 0x10(r29)
	b @10
	@9:
	lfs f1, float_60_8041a54c(r2)
	lfs f0, 0x10(r1)
	fadds f0, f1, f0
	stfs f0, 0x10(r29)
	@10:
	lfs f3, 0x14(r29)
	li r3, 0x0
	lfs f2, float_0p5_8041a534(r2)
	li r5, 0xff
	lfs f0, 0xc(r29)
	lfs f1, 0xc(r1)
	fmadds f2, f3, f2, f0
	lha r4, 0x6(r29)
	bl intplGetValue
	lfs f3, 0x18(r29)
	fmr f30, f1
	lfs f2, float_0p5_8041a534(r2)
	li r3, 0x0
	lfs f0, 0x10(r29)
	li r5, 0xff
	lfs f1, 0x10(r1)
	fnmsubs f2, f3, f2, f0
	lha r4, 0x6(r29)
	bl intplGetValue
	fmr f31, f1
	lfs f1, float_10_8041a538(r2)
	lfs f2, 0x14(r29)
	li r3, 0x0
	lha r4, 0x6(r29)
	li r5, 0xff
	bl intplGetValue
	fmr f29, f1
	lfs f1, float_10_8041a538(r2)
	lfs f2, 0x18(r29)
	li r3, 0x0
	lha r4, 0x6(r29)
	li r5, 0xff
	bl intplGetValue
	fmr f4, f1
	lfs f0, float_0p5_8041a534(r2)
	lha r0, 0x6(r29)
	fmr f3, f29
	fnmsubs f1, f29, f0, f30
	lwz r3, 0x8(r29)
	fmadds f2, f4, f0, f31
	lha r4, 0x2c(r29)
	lfs f5, 0xc(r1)
	clrlwi r5, r0, 24
	lfs f6, 0x10(r1)
	bl windowDispGX_Message
	lha r0, 0x6(r29)
	cmpwi r0, 0xff
	bne @1
	lfs f0, 0x10(r29)
	fctiwz f0, f0
	stfd f0, 0x18(r1)
	lwz r3, 0x1c(r1)
	subi r0, r3, 0xa
	subfic r4, r0, 0xf0
	cmpwi r4, 0x0
	bge @11
	li r4, 0x0
	@11:
	cmpwi r4, 0x1e0
	ble @12
	li r4, 0x1e0
	@12:
	lhz r3, 0xf4(r31)
	li r6, 0x7e
	lhz r5, 0xf8(r31)
	bl GXSetScissor
	lfs f1, float_28_8041a550(r2)
	lfs f0, 0xc(r29)
	lha r0, 0x6(r29)
	lfs f2, 0x10(r29)
	fadds f1, f1, f0
	lfs f0, float_6_8041a554(r2)
	clrlwi r4, r0, 24
	lwz r3, 0x28(r29)
	fsubs f2, f2, f0
	bl msgDisp
	b @1
	@3:
	lfs f5, float_0_8041a514(r2)
	li r4, 0x0
	lha r0, 0x6(r29)
	fmr f6, f5
	lfs f1, 0xc(r29)
	lfs f2, 0x10(r29)
	clrlwi r5, r0, 24
	lfs f3, 0x14(r29)
	lfs f4, 0x18(r29)
	bl windowDispGX_Message
	lfs f1, 0x10(r29)
	lfs f0, float_36_8041a540(r2)
	lfs f2, float_240_8041a53c(r2)
	fsubs f1, f1, f0
	lfs f0, float_8_8041a558(r2)
	fsubs f1, f2, f1
	fsubs f1, f1, f0
	bl __cvt_fp2unsigned
	mr r4, r3
	lhz r3, 0xf4(r31)
	lhz r5, 0xf8(r31)
	li r6, 0x7e
	bl GXSetScissor
	lfs f1, float_62_8041a544(r2)
	lfs f0, 0xc(r29)
	lha r0, 0x6(r29)
	lfs f2, 0x10(r29)
	fadds f1, f1, f0
	lfs f0, float_36_8041a540(r2)
	clrlwi r4, r0, 24
	lwz r3, 0x28(r29)
	fsubs f2, f2, f0
	bl msgDisp
	mr r30, r3
	b @1
	@13:
	lha r0, 0x6(r29)
	lfs f1, 0xc(r29)
	lfs f2, 0x10(r29)
	clrlwi r4, r0, 24
	lfs f3, 0x14(r29)
	lfs f4, 0x18(r29)
	bl windowDispGX_Kanban
	lfs f1, 0x10(r29)
	lfs f0, float_36_8041a540(r2)
	lfs f2, float_240_8041a53c(r2)
	fsubs f1, f1, f0
	lfs f0, float_2_8041a524(r2)
	fsubs f1, f2, f1
	fsubs f1, f1, f0
	bl __cvt_fp2unsigned
	mr r4, r3
	lhz r3, 0xf4(r31)
	lhz r5, 0xf8(r31)
	li r6, 0x68
	bl GXSetScissor
	lfs f1, float_62_8041a544(r2)
	lfs f0, 0xc(r29)
	lha r0, 0x6(r29)
	lfs f2, 0x10(r29)
	fadds f1, f1, f0
	lfs f0, float_36_8041a540(r2)
	clrlwi r4, r0, 24
	lwz r3, 0x28(r29)
	fsubs f2, f2, f0
	bl msgDisp
	mr r30, r3
	b @1
	@14:
	lha r0, 0x6(r29)
	lfs f1, 0xc(r29)
	lfs f2, 0x10(r29)
	clrlwi r4, r0, 24
	lfs f3, 0x14(r29)
	lfs f4, 0x18(r29)
	bl windowDispGX_Kanban
	lfs f1, 0x10(r29)
	lfs f0, float_36_8041a540(r2)
	lfs f2, float_240_8041a53c(r2)
	fsubs f1, f1, f0
	lfs f0, float_8_8041a558(r2)
	fsubs f1, f2, f1
	fsubs f1, f1, f0
	bl __cvt_fp2unsigned
	mr r4, r3
	lhz r3, 0xf4(r31)
	lhz r5, 0xf8(r31)
	li r6, 0x7e
	bl GXSetScissor
	lfs f1, float_62_8041a544(r2)
	lfs f0, 0xc(r29)
	lha r0, 0x6(r29)
	lfs f2, 0x10(r29)
	fadds f1, f1, f0
	lfs f0, float_36_8041a540(r2)
	clrlwi r4, r0, 24
	lwz r3, 0x28(r29)
	fsubs f2, f2, f0
	bl msgDisp
	mr r30, r3
	b @1
	@15:
	lha r0, 0x6(r29)
	lfs f1, 0xc(r29)
	lfs f2, 0x10(r29)
	clrlwi r4, r0, 24
	lfs f3, 0x14(r29)
	lfs f4, 0x18(r29)
	bl windowDispGX_System
	lfs f1, 0x18(r29)
	lfs f0, float_50_8041a55c(r2)
	fsubs f1, f1, f0
	bl __cvt_fp2unsigned
	lfs f1, 0x10(r29)
	mr r30, r3
	lfs f0, float_36_8041a540(r2)
	lfs f2, float_240_8041a53c(r2)
	fsubs f1, f1, f0
	lfs f0, float_8_8041a558(r2)
	fsubs f1, f2, f1
	fsubs f1, f1, f0
	bl __cvt_fp2unsigned
	mr r4, r3
	lhz r3, 0xf4(r31)
	lhz r5, 0xf8(r31)
	mr r6, r30
	bl GXSetScissor
	lfs f1, float_62_8041a544(r2)
	lfs f0, 0xc(r29)
	lha r0, 0x6(r29)
	lfs f2, 0x10(r29)
	fadds f1, f1, f0
	lfs f0, float_36_8041a540(r2)
	clrlwi r4, r0, 24
	lwz r3, 0x28(r29)
	fsubs f2, f2, f0
	bl msgDisp
	mr r30, r3
	b @1
	@16:
	lfs f1, 0x18(r29)
	lfs f0, float_50_8041a55c(r2)
	fsubs f1, f1, f0
	bl __cvt_fp2unsigned
	lfs f1, 0x10(r29)
	mr r30, r3
	lfs f0, float_36_8041a540(r2)
	lfs f2, float_240_8041a53c(r2)
	fsubs f1, f1, f0
	lfs f0, float_8_8041a558(r2)
	fsubs f1, f2, f1
	fsubs f1, f1, f0
	bl __cvt_fp2unsigned
	mr r4, r3
	lhz r3, 0xf4(r31)
	lhz r5, 0xf8(r31)
	mr r6, r30
	bl GXSetScissor
	lfs f1, float_62_8041a544(r2)
	lfs f0, 0xc(r29)
	lha r0, 0x6(r29)
	lfs f2, 0x10(r29)
	fadds f1, f1, f0
	lfs f0, float_36_8041a540(r2)
	clrlwi r4, r0, 24
	lwz r3, 0x28(r29)
	fsubs f2, f2, f0
	bl msgDisp
	mr r30, r3
	@1:
	lhz r3, 0xf4(r31)
	lhz r4, 0xf6(r31)
	lhz r5, 0xf8(r31)
	lhz r6, 0xfa(r31)
	bl GXSetScissor
	cmpwi r30, 0x0
	beq @17
	lhz r0, g5_active_s772(r13)
	cmplwi r0, 0x0
	bne @18
	li r0, 0x1
	sth r0, g5_active_s772(r13)
	@18:
	lwz r3, msgw(r13)
	lwz r3, 0x20(r3)
	bl animPoseMain
	lfs f3, 0xc(r29)
	li r4, 0x2
	lfs f2, 0x14(r29)
	lfs f1, 0x10(r29)
	lfs f0, 0x18(r29)
	fadds f4, f3, f2
	lfs f3, float_52_8041a560(r2)
	lwz r3, msgw(r13)
	fsubs f0, f1, f0
	lfs f2, float_31_8041a564(r2)
	fsubs f1, f4, f3
	lwz r3, 0x20(r3)
	fadds f2, f2, f0
	lfs f3, float_0_8041a514(r2)
	lfs f4, float_180_8041a568(r2)
	lfs f5, float_5_8041a56c(r2)
	bl animPoseDraw
	@17:
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	psq_l f29, 0x38(r1), 0, 0
	lfd f29, 0x30(r1)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r0, 0x64(r1)
	lwz r29, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm void msgWindow_Clear_Main(WindowEntry* window) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	lhz r0, 0x0(r3)
	lwz r4, 0x28(r3)
	cmpwi r0, 0x5
	lwz r4, 0x0(r4)
	beq @1
	bge @2
	cmpwi r0, 0x1
	beq @3
	b @4
	@2:
	cmpwi r0, 0x7
	beq @5
	bge @4
	b @3
	@1:
	li r0, 0x1
	sth r0, 0x0(r31)
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x24(r31)
	stw r0, 0x20(r31)
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x1c(r4)
	stw r0, 0x18(r4)
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x34(r4)
	stw r0, 0x30(r4)
	@3:
	lhz r0, 0x2(r31)
	ori r0, r0, 0x2
	sth r0, 0x2(r31)
	lha r0, 0x6(r31)
	cmpwi r0, 0xff
	bge @6
	lis r3, 0x8000
	lwz r6, gp(r13)
	lwz r0, 0xf8(r3)
	lis r3, 0x1062
	lwz r5, 0x3c(r6)
	addi r3, r3, 0x4dd3
	srwi r0, r0, 2
	lwz r4, 0x24(r31)
	mulhwu r0, r3, r0
	lwz r6, 0x38(r6)
	subfc r4, r4, r5
	lwz r3, 0x20(r31)
	li r5, 0x0
	subfe r3, r3, r6
	srwi r6, r0, 6
	bl __div2i
	li r7, 0xff
	li r5, 0x0
	mulhwu r0, r4, r7
	li r6, 0xc8
	mullw r3, r3, r7
	mulli r4, r4, 0xff
	add r3, r0, r3
	bl __div2i
	sth r4, 0x6(r31)
	lha r0, 0x6(r31)
	cmpwi r0, 0xff
	ble @6
	li r0, 0xff
	sth r0, 0x6(r31)
	@6:
	lhz r0, 0x0(r31)
	cmplwi r0, 0x2
	beq @4
	lwz r3, 0x28(r31)
	bl msgMain
	cmpwi r3, 0x2
	beq @7
	bge @4
	cmpwi r3, 0x0
	beq @8
	bge @9
	b @4
	b @4
	@8:
	li r0, 0x7
	sth r0, 0x0(r31)
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x24(r31)
	stw r0, 0x20(r31)
	lwz r3, 0x28(r31)
	lwz r3, 0x0(r3)
	lwz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 28, 28
	beq @10
	lwz r3, 0x7a24(r3)
	bl BtlUnit_ChangeStayAnim
	b @4
	@10:
	addi r3, r3, 0x7a04
	bl npcSetStayPose
	b @4
	@9:
	li r0, 0x2
	sth r0, 0x0(r31)
	lhz r0, 0x2(r31)
	rlwinm r0, r0, 0, 31, 29
	sth r0, 0x2(r31)
	lwz r3, 0x28(r31)
	lwz r3, 0x0(r3)
	lwz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 28, 28
	beq @11
	lwz r3, 0x7a24(r3)
	bl BtlUnit_ChangeStayAnim
	b @4
	@11:
	addi r3, r3, 0x7a04
	bl npcSetStayPose
	b @4
	@7:
	li r0, 0x3
	sth r0, 0x0(r31)
	b @4
	@5:
	lha r0, 0x6(r31)
	cmpwi r0, 0x0
	bne @12
	bl windowDelete
	b @13
	@12:
	lis r3, 0x8000
	lwz r6, gp(r13)
	lwz r0, 0xf8(r3)
	lis r3, 0x1062
	lwz r5, 0x3c(r6)
	addi r3, r3, 0x4dd3
	srwi r0, r0, 2
	lwz r4, 0x24(r31)
	mulhwu r0, r3, r0
	lwz r6, 0x38(r6)
	subfc r4, r4, r5
	lwz r3, 0x20(r31)
	li r5, 0x0
	subfe r3, r3, r6
	srwi r6, r0, 6
	bl __div2i
	li r7, 0xff
	li r5, 0x0
	mulhwu r0, r4, r7
	li r6, 0xc8
	mullw r3, r3, r7
	mulli r4, r4, 0xff
	add r3, r0, r3
	bl __div2i
	li r0, 0xff
	li r5, 0x0
	subfc r0, r4, r0
	sth r0, 0x6(r31)
	lha r0, 0x6(r31)
	cmpwi r0, 0x0
	bgt @4
	sth r5, 0x6(r31)
	@4:
	lha r4, 0x4(r31)
	lis r0, 0x4330
	lis r5, double_to_int_802c4f08@ha
	stw r0, 0x8(r1)
	xoris r4, r4, 0x8000
	lfs f2, float_400_8041a530(r2)
	stw r4, 0xc(r1)
	addi r6, r5, double_to_int_802c4f08@l
	lfd f1, 0x0(r6)
	lis r3, msgWindow_Disp@ha
	lfd f0, 0x8(r1)
	addi r5, r3, msgWindow_Disp@l
	mr r6, r31
	li r3, 0x8
	fsubs f0, f0, f1
	li r4, 0x0
	fsubs f1, f2, f0
	bl dispEntry
	@13:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void msgWindow_Main(WindowEntry* window) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	mr r31, r3
	stw r30, 0x28(r1)
	stw r29, 0x24(r1)
	lwz r30, 0x28(r3)
	lwz r29, 0x0(r30)
	lwz r0, 0x7a50(r29)
	cmpwi r0, 0x0
	beq @1
	lwz r0, 0x7a54(r29)
	cmpwi r0, 0x0
	bne @2
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 28, 28
	beq @3
	lwz r3, 0x7a24(r29)
	bl BtlUnit_ChangeTalkAnim
	b @4
	@3:
	addi r3, r29, 0x7a04
	bl npcSetTalkPose
	@4:
	li r0, 0x1
	stw r0, 0x7a54(r29)
	@2:
	lwz r3, 0x7a50(r29)
	subi r0, r3, 0x1
	stw r0, 0x7a50(r29)
	lwz r0, 0x7a50(r29)
	cmpwi r0, 0x0
	bne @1
	lwz r3, 0x0(r30)
	lwz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 28, 28
	beq @5
	lwz r3, 0x7a24(r3)
	bl BtlUnit_ChangeStayAnim
	b @6
	@5:
	addi r3, r3, 0x7a04
	bl npcSetStayPose
	@6:
	li r0, 0x0
	stw r0, 0x7a54(r29)
	@1:
	lhz r0, 0x0(r31)
	cmplwi r0, 0xb
	bgt @7
	lis r3, jumptable_8030DBA0@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_8030DBA0@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@8:
	lhz r0, 0x2(r31)
	rlwinm. r0, r0, 0, 28, 28
	bne @9
	lwz r0, 0x8(r31)
	lis r3, msgWindowOpen_SE_Data@ha
	addi r3, r3, msgWindowOpen_SE_Data@l
	slwi r0, r0, 3
	lwzx r0, r3, r0
	cmpwi r0, 0x0
	blt @9
	oris r3, r0, 0x2
	bl psndSFXOn
	@9:
	lwz r4, gp(r13)
	li r0, 0x6
	lwz r3, 0x38(r4)
	lwz r4, 0x3c(r4)
	stw r4, 0x24(r31)
	stw r3, 0x20(r31)
	sth r0, 0x0(r31)
	@10:
	lhz r0, 0x2(r31)
	lis r3, 0x1062
	lis r4, 0x8000
	li r5, 0x0
	ori r0, r0, 0x2
	addi r3, r3, 0x4dd3
	sth r0, 0x2(r31)
	lwz r0, 0xf8(r4)
	lwz r6, gp(r13)
	srwi r0, r0, 2
	lwz r4, 0x24(r31)
	mulhwu r0, r3, r0
	lwz r3, 0x3c(r6)
	lwz r6, 0x38(r6)
	subfc r4, r4, r3
	lwz r3, 0x20(r31)
	subfe r3, r3, r6
	srwi r6, r0, 6
	bl __div2i
	li r7, 0xff
	li r5, 0x0
	mulhwu r0, r4, r7
	li r6, 0xc8
	mullw r3, r3, r7
	mulli r4, r4, 0xff
	add r3, r0, r3
	bl __div2i
	sth r4, 0x6(r31)
	lha r0, 0x6(r31)
	cmpwi r0, 0xff
	ble @7
	li r3, 0xff
	li r0, 0x1
	sth r3, 0x6(r31)
	sth r0, 0x0(r31)
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x1c(r29)
	stw r0, 0x18(r29)
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x34(r29)
	stw r0, 0x30(r29)
	b @7
	@11:
	lhz r0, 0x2(r31)
	rlwinm. r0, r0, 0, 28, 28
	bne @12
	lwz r0, 0x8(r31)
	lis r3, msgWindowOpen_SE_Data@ha
	addi r3, r3, msgWindowOpen_SE_Data@l
	slwi r0, r0, 3
	add r3, r3, r0
	lwz r0, 0x4(r3)
	cmpwi r0, 0x0
	blt @12
	oris r3, r0, 0x2
	bl psndSFXOn
	@12:
	lwz r4, gp(r13)
	li r0, 0x8
	lwz r3, 0x38(r4)
	lwz r4, 0x3c(r4)
	stw r4, 0x24(r31)
	stw r3, 0x20(r31)
	sth r0, 0x0(r31)
	@13:
	lha r0, 0x6(r31)
	cmpwi r0, 0x0
	bne @14
	mr r3, r31
	bl windowDelete
	b @15
	@14:
	lis r3, 0x8000
	lwz r6, gp(r13)
	lwz r0, 0xf8(r3)
	lis r3, 0x1062
	lwz r5, 0x3c(r6)
	addi r3, r3, 0x4dd3
	srwi r0, r0, 2
	lwz r4, 0x24(r31)
	mulhwu r0, r3, r0
	lwz r6, 0x38(r6)
	subfc r4, r4, r5
	lwz r3, 0x20(r31)
	li r5, 0x0
	subfe r3, r3, r6
	srwi r6, r0, 6
	bl __div2i
	li r7, 0xff
	li r5, 0x0
	mulhwu r0, r4, r7
	li r6, 0xc8
	mullw r3, r3, r7
	mulli r4, r4, 0xff
	add r3, r0, r3
	bl __div2i
	li r0, 0xff
	li r5, 0x0
	subfc r0, r4, r0
	sth r0, 0x6(r31)
	lha r0, 0x6(r31)
	cmpwi r0, 0x0
	bgt @7
	sth r5, 0x6(r31)
	b @7
	@16:
	lwz r3, 0x28(r31)
	bl msgMain
	cmpwi r3, 0x2
	beq @17
	bge @7
	cmpwi r3, 0x0
	beq @18
	bge @19
	b @7
	b @7
	@18:
	li r0, 0x7
	sth r0, 0x0(r31)
	lwz r3, 0x28(r31)
	lwz r3, 0x0(r3)
	lwz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 28, 28
	beq @20
	lwz r3, 0x7a24(r3)
	bl BtlUnit_ChangeStayAnim
	b @7
	@20:
	addi r3, r3, 0x7a04
	bl npcSetStayPose
	b @7
	@19:
	li r0, 0x2
	sth r0, 0x0(r31)
	lhz r0, 0x2(r31)
	rlwinm r0, r0, 0, 31, 29
	sth r0, 0x2(r31)
	lwz r3, 0x28(r31)
	lwz r3, 0x0(r3)
	lwz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 28, 28
	beq @21
	lwz r3, 0x7a24(r3)
	bl BtlUnit_ChangeStayAnim
	b @7
	@21:
	addi r3, r3, 0x7a04
	bl npcSetStayPose
	b @7
	@17:
	li r0, 0x3
	sth r0, 0x0(r31)
	b @7
	@22:
	lwz r3, 0x28(r31)
	li r30, 0x100
	lwz r3, 0x0(r3)
	lwz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 23, 23
	beq @23
	li r30, 0x500
	@23:
	li r3, 0x0
	bl keyGetButtonTrg
	ori r0, r30, 0x200
	and. r0, r3, r0
	beq @24
	li r3, 0x1
	li r0, 0x2
	sth r3, 0x0(r31)
	li r3, 0x0
	sth r0, 0xa(r29)
	bl keyGetButtonTrg
	rlwinm. r0, r3, 0, 22, 22
	beq @24
	lwz r3, 0x4(r29)
	rlwinm. r0, r3, 0, 24, 24
	bne @24
	ori r0, r3, 0x4
	stw r0, 0x4(r29)
	@24:
	li r3, 0x0
	bl keyGetButtonTrg
	rlwinm. r0, r3, 0, 27, 27
	beq @7
	lwz r3, 0x7840(r29)
	subi r0, r3, 0x1
	stw r0, 0x783c(r29)
	lwz r3, 0x28(r31)
	lwz r4, 0x0(r3)
	lwz r3, 0x783c(r4)
	subi r0, r3, 0x1
	stw r0, 0x783c(r4)
	lwz r0, 0x783c(r4)
	cmpwi r0, 0x0
	bge @25
	li r0, 0x0
	stw r0, 0x783c(r4)
	b @26
	@25:
	li r0, 0x1
	@26:
	cmplwi r0, 0x0
	beq @7
	li r0, 0x9
	lis r3, 0x2
	sth r0, 0x0(r31)
	addi r3, r3, 0x41
	lwz r4, gp(r13)
	lwz r0, 0x38(r4)
	lwz r4, 0x3c(r4)
	stw r4, 0x24(r31)
	stw r0, 0x20(r31)
	bl psndSFXOn
	lwz r0, 0x4(r29)
	ori r0, r0, 0x40
	stw r0, 0x4(r29)
	b @7
	@27:
	lwz r3, 0x783c(r29)
	lwz r0, 0x28(r29)
	slwi r3, r3, 2
	add r3, r29, r3
	lwz r30, 0x7844(r3)
	cmpw r0, r30
	blt @7
	lis r3, 0x8000
	lwz r6, gp(r13)
	lwz r0, 0xf8(r3)
	lis r3, 0x1062
	lwz r5, 0x3c(r6)
	addi r3, r3, 0x4dd3
	srwi r0, r0, 2
	lwz r4, 0x24(r31)
	mulhwu r0, r3, r0
	lwz r6, 0x38(r6)
	subfc r4, r4, r5
	lwz r3, 0x20(r31)
	li r5, 0x0
	subfe r3, r3, r6
	srwi r6, r0, 6
	bl __div2i
	bl __cvt_sll_flt
	lwz r4, 0x28(r29)
	lis r0, 0x4330
	stw r0, 0x8(r1)
	lis r3, double_to_int_802c4f08@ha
	xoris r0, r4, 0x8000
	lfd f2, double_to_int_802c4f08@l(r3)
	stw r0, 0xc(r1)
	lfs f3, float_0p6_8041a570(r2)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f2
	fnmsubs f0, f3, f1, f0
	fctiwz f0, f0
	stfd f0, 0x10(r1)
	lwz r0, 0x14(r1)
	stw r0, 0x28(r29)
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x24(r31)
	stw r0, 0x20(r31)
	lwz r0, 0x28(r29)
	cmpw r0, r30
	bgt @7
	stw r30, 0x28(r29)
	li r0, 0xb
	sth r0, 0x0(r31)
	b @7
	@28:
	lwz r3, 0x783c(r29)
	lwz r0, 0x28(r29)
	slwi r3, r3, 2
	add r3, r29, r3
	lwz r30, 0x7844(r3)
	cmpw r0, r30
	bgt @7
	lis r3, 0x8000
	lwz r6, gp(r13)
	lwz r0, 0xf8(r3)
	lis r3, 0x1062
	lwz r5, 0x3c(r6)
	addi r3, r3, 0x4dd3
	srwi r0, r0, 2
	lwz r4, 0x24(r31)
	mulhwu r0, r3, r0
	lwz r6, 0x38(r6)
	subfc r4, r4, r5
	lwz r3, 0x20(r31)
	li r5, 0x0
	subfe r3, r3, r6
	srwi r6, r0, 6
	bl __div2i
	bl __cvt_sll_flt
	lwz r4, 0x28(r29)
	lis r0, 0x4330
	stw r0, 0x10(r1)
	lis r3, double_to_int_802c4f08@ha
	xoris r0, r4, 0x8000
	lfd f2, double_to_int_802c4f08@l(r3)
	stw r0, 0x14(r1)
	lfs f3, float_0p6_8041a570(r2)
	lfd f0, 0x10(r1)
	fsubs f0, f0, f2
	fmadds f0, f3, f1, f0
	fctiwz f0, f0
	stfd f0, 0x8(r1)
	lwz r0, 0xc(r1)
	stw r0, 0x28(r29)
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x24(r31)
	stw r0, 0x20(r31)
	lwz r0, 0x28(r29)
	cmpw r0, r30
	blt @7
	stw r30, 0x28(r29)
	lwz r3, 0x7840(r29)
	lwz r4, 0x783c(r29)
	subi r0, r3, 0x1
	cmpw r4, r0
	bne @29
	li r0, 0x3
	sth r0, 0x0(r31)
	lwz r0, 0x4(r29)
	rlwinm r0, r0, 0, 26, 24
	stw r0, 0x4(r29)
	b @7
	@29:
	li r0, 0xb
	sth r0, 0x0(r31)
	b @7
	@30:
	lwz r3, 0x28(r31)
	li r30, 0x100
	lwz r3, 0x0(r3)
	lwz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 23, 23
	beq @31
	li r30, 0x500
	@31:
	li r3, 0x0
	bl keyGetButtonTrg
	and. r0, r3, r30
	beq @32
	li r0, 0xa
	sth r0, 0x0(r31)
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x24(r31)
	stw r0, 0x20(r31)
	lwz r3, 0x28(r31)
	lwz r4, 0x0(r3)
	lwz r3, 0x783c(r4)
	addi r0, r3, 0x1
	stw r0, 0x783c(r4)
	lwz r3, 0x7840(r4)
	lwz r0, 0x783c(r4)
	subi r3, r3, 0x1
	cmpw r0, r3
	ble @33
	stw r3, 0x783c(r4)
	@33:
	lis r3, 0x2
	addi r3, r3, 0x41
	bl psndSFXOn
	@32:
	li r3, 0x0
	bl keyGetButtonTrg
	rlwinm. r0, r3, 0, 22, 22
	beq @34
	li r0, 0xa
	lis r3, 0x2
	sth r0, 0x0(r31)
	addi r3, r3, 0x41
	lwz r4, gp(r13)
	lwz r0, 0x38(r4)
	lwz r4, 0x3c(r4)
	stw r4, 0x24(r31)
	stw r0, 0x20(r31)
	lwz r4, 0x7840(r29)
	subi r0, r4, 0x1
	stw r0, 0x783c(r29)
	bl psndSFXOn
	@34:
	li r3, 0x0
	bl keyGetButtonTrg
	rlwinm. r0, r3, 0, 27, 27
	beq @7
	li r0, 0x9
	sth r0, 0x0(r31)
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x24(r31)
	stw r0, 0x20(r31)
	lwz r3, 0x28(r31)
	lwz r4, 0x0(r3)
	lwz r3, 0x783c(r4)
	subi r0, r3, 0x1
	stw r0, 0x783c(r4)
	lwz r0, 0x783c(r4)
	cmpwi r0, 0x0
	bge @35
	li r0, 0x0
	stw r0, 0x783c(r4)
	b @36
	@35:
	li r0, 0x1
	@36:
	cmplwi r0, 0x0
	beq @7
	lis r3, 0x2
	addi r3, r3, 0x41
	bl psndSFXOn
	@7:
	lha r4, 0x4(r31)
	lis r0, 0x4330
	lis r5, double_to_int_802c4f08@ha
	stw r0, 0x10(r1)
	xoris r4, r4, 0x8000
	lfs f2, float_400_8041a530(r2)
	stw r4, 0x14(r1)
	addi r6, r5, double_to_int_802c4f08@l
	lfd f1, 0x0(r6)
	lis r3, msgWindow_Disp@ha
	lfd f0, 0x10(r1)
	addi r5, r3, msgWindow_Disp@l
	mr r6, r31
	li r3, 0x8
	fsubs f0, f0, f1
	li r4, 0x0
	fsubs f1, f2, f0
	bl dispEntry
	@15:
	lwz r0, 0x34(r1)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void msgWindow_ForceClose(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	li r30, 0x0
	stw r29, 0x14(r1)
	mr r29, r3
	@1:
	mr r3, r30
	bl windowGetPointer
	mr r31, r3
	lhz r0, 0x2(r3)
	cmplwi r0, 0x0
	beq @2
	lhz r0, 0x0(r31)
	cmplwi r0, 0x0
	beq @2
	lwz r3, 0x28(r31)
	cmplwi r3, 0x0
	beq @2
	lwz r3, 0x0(r3)
	lwz r3, 0x0(r3)
	cmplwi r3, 0x0
	beq @2
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	bne @2
	li r0, 0x7
	sth r0, 0x0(r31)
	lwz r3, 0x28(r31)
	lwz r3, 0x0(r3)
	lwz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 28, 28
	beq @3
	lwz r3, 0x7a24(r3)
	bl BtlUnit_ChangeStayAnim
	b @2
	@3:
	addi r3, r3, 0x7a04
	bl npcSetStayPose
	@2:
	addi r30, r30, 0x1
	cmpwi r30, 0x7
	blt @1
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void msgWindow_Repeat(s32 id) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl windowGetPointer
	li r4, 0x1
	li r0, 0x0
	sth r4, 0x0(r3)
	lhz r4, 0x2(r3)
	ori r4, r4, 0x2
	sth r4, 0x2(r3)
	lwz r5, 0x28(r3)
	lwz r4, gp(r13)
	lwz r5, 0x0(r5)
	lwz r3, 0x38(r4)
	lwz r4, 0x3c(r4)
	stw r4, 0x34(r5)
	stw r3, 0x30(r5)
	lwz r4, gp(r13)
	lwz r3, 0x38(r4)
	lwz r4, 0x3c(r4)
	stw r4, 0x1c(r5)
	stw r3, 0x18(r5)
	stw r0, 0x20(r5)
	stw r0, 0x24(r5)
	stw r0, 0x28(r5)
	stw r0, 0x10(r5)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void msgWindow_Continue(s32 id) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl windowGetPointer
	li r0, 0x1
	sth r0, 0x0(r3)
	lhz r0, 0x2(r3)
	ori r0, r0, 0x2
	sth r0, 0x2(r3)
	lwz r4, gp(r13)
	lwz r3, 0x28(r3)
	lwz r0, 0x38(r4)
	lwz r4, 0x3c(r4)
	lwz r3, 0x0(r3)
	stw r4, 0x34(r3)
	stw r0, 0x30(r3)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void msgWindow_Add(char* msg, s32 id) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	mr r3, r4
	bl windowGetPointer
	lwz r5, gp(r13)
	mr r31, r3
	lwz r3, 0x28(r3)
	mr r4, r30
	lwz r0, 0x38(r5)
	lwz r6, 0x3c(r5)
	lwz r5, 0x0(r3)
	stw r6, 0x34(r5)
	stw r0, 0x30(r5)
	bl msgAnalize
	li r0, 0x1
	sth r0, 0x0(r31)
	lhz r0, 0x2(r31)
	ori r0, r0, 0x2
	sth r0, 0x2(r31)
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void msgWindow_Delete(WindowEntry* window) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r3, 0x28(r3)
	cmplwi r3, 0x0
	beq @1
	lwz r4, 0x0(r3)
	lwz r0, 0x38(r4)
	mtctr r0
	cmpwi r0, 0x0
	ble @2
	@3:
	bdnz @3
	@2:
	bl smartFree
	li r0, 0x0
	stw r0, 0x28(r31)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 msgWindow_Entry(const char* msg, s32 field_0x79FC, u16 priority) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stmw r26, 0x38(r1)
	mr r28, r3
	mr r26, r4
	mr r3, r5
	bl windowEntry
	mr r27, r3
	bl windowGetPointer
	lis r4, msgWindow_Main@ha
	mr r31, r3
	addi r0, r4, msgWindow_Main@l
	lis r3, msgWindow_Delete@ha
	stw r0, 0x3c(r31)
	addi r3, r3, msgWindow_Delete@l
	li r4, 0x5
	li r0, -0x1
	stw r3, 0x40(r31)
	mr r3, r28
	sth r4, 0x0(r31)
	stw r0, 0x8(r31)
	lhz r0, 0x2(r31)
	ori r0, r0, 0x2
	sth r0, 0x2(r31)
	bl strlen
	mr r4, r3
	li r3, 0x0
	bl __memAlloc
	mr r4, r28
	mr r30, r3
	bl strcpy
	li r3, 0x7a58
	li r4, 0x1
	bl smartAlloc
	lwz r29, 0x0(r3)
	mr r28, r3
	li r4, 0x0
	li r5, 0x7a58
	mr r3, r29
	bl memset
	stw r31, 0x7a4c(r29)
	li r0, 0x3
	li r6, 0x0
	li r5, 0x7f
	stw r0, 0x4(r29)
	li r0, 0x19
	mr r3, r28
	mr r4, r30
	stw r26, 0x79fc(r29)
	lwz r8, gp(r13)
	lwz r7, 0x38(r8)
	lwz r8, 0x3c(r8)
	stw r8, 0x34(r29)
	stw r7, 0x30(r29)
	lwz r8, gp(r13)
	lwz r7, 0x38(r8)
	lwz r8, 0x3c(r8)
	stw r8, 0x1c(r29)
	stw r7, 0x18(r29)
	stw r6, 0x7a28(r29)
	stb r5, 0x7a2c(r29)
	stw r6, 0x7a30(r29)
	sth r6, 0x7a34(r29)
	sth r6, 0x7a36(r29)
	sth r6, 0x7a38(r29)
	sth r6, 0x7a3a(r29)
	stw r0, 0x7a3c(r29)
	stw r6, 0x7840(r29)
	bl msgAnalize
	lwz r0, 0x8(r31)
	cmpwi r0, 0x1
	bne @1
	lwz r0, 0x4(r29)
	ori r0, r0, 0x200
	stw r0, 0x4(r29)
	@1:
	mr r4, r30
	li r3, 0x0
	bl __memFree
	stw r28, 0x28(r31)
	li r0, 0x0
	lwz r3, 0x28(r31)
	lwz r3, 0x0(r3)
	stw r0, 0x7a50(r3)
	stw r0, 0x7a54(r3)
	lwz r0, 0x8(r31)
	cmpwi r0, 0x5
	beq @2
	bge @3
	cmpwi r0, 0x1
	beq @4
	bge @5
	cmpwi r0, 0x0
	bge @5
	b @6
	@3:
	cmpwi r0, 0xb
	beq @7
	bge @6
	b @5
	@7:
	lis r3, msgWindow_Clear_Main@ha
	addi r0, r3, msgWindow_Clear_Main@l
	stw r0, 0x3c(r31)
	@5:
	lhz r0, 0x2(r31)
	rlwinm. r0, r0, 0, 29, 29
	bne @6
	lfs f1, float_neg280_8041a574(r2)
	lfs f0, float_225_8041a578(r2)
	stfs f1, 0xc(r31)
	lfs f1, float_560_8041a57c(r2)
	stfs f0, 0x10(r31)
	lfs f0, float_176_8041a580(r2)
	stfs f1, 0x14(r31)
	stfs f0, 0x18(r31)
	b @6
	@2:
	lis r4, selectWindow_Main@ha
	lis r0, 0x4330
	addi r5, r4, selectWindow_Main@l
	stw r0, 0x8(r1)
	lis r4, double_to_int_802c4f08@ha
	stw r5, 0x3c(r31)
	lfd f2, double_to_int_802c4f08@l(r4)
	lwz r4, 0x28(r31)
	stw r0, 0x10(r1)
	lwz r4, 0x0(r4)
	stw r0, 0x18(r1)
	lha r4, 0x7a44(r4)
	stw r0, 0x20(r1)
	neg r5, r4
	srwi r4, r5, 31
	stw r0, 0x28(r1)
	add r4, r4, r5
	srawi r4, r4, 1
	extsh r0, r4
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f2
	stfs f0, 0xc(r31)
	lwz r4, 0x28(r31)
	lwz r4, 0x0(r4)
	lha r0, 0x7a46(r4)
	xoris r0, r0, 0x8000
	stw r0, 0x14(r1)
	lfd f0, 0x10(r1)
	fsubs f0, f0, f2
	stfs f0, 0x10(r31)
	lwz r4, 0x28(r31)
	lwz r4, 0x0(r4)
	lha r0, 0x7a44(r4)
	xoris r0, r0, 0x8000
	stw r0, 0x1c(r1)
	lfd f0, 0x18(r1)
	fsubs f0, f0, f2
	stfs f0, 0x14(r31)
	lwz r4, 0x28(r31)
	lwz r4, 0x0(r4)
	lbz r0, 0x7a40(r4)
	extsb r0, r0
	mulli r4, r0, 0x24
	addi r0, r4, 0x28
	extsh r0, r0
	xoris r0, r0, 0x8000
	stw r0, 0x24(r1)
	lfd f0, 0x20(r1)
	fsubs f0, f0, f2
	stfs f0, 0x18(r31)
	lwz r4, 0x28(r31)
	lwz r4, 0x0(r4)
	lbz r0, 0x7a41(r4)
	stb r0, 0x7a43(r4)
	lbz r0, 0x7a43(r3)
	lfs f1, 0x10(r31)
	extsb r0, r0
	mulli r4, r0, 0x1f
	addi r0, r4, 0x3a
	xoris r0, r0, 0x8000
	stw r0, 0x2c(r1)
	lfd f0, 0x28(r1)
	fsubs f0, f0, f2
	fsubs f0, f1, f0
	stfs f0, 0x7a48(r3)
	b @6
	@4:
	li r0, 0xa
	li r3, 0x3
	sth r0, 0x4(r31)
	bl getWakuTexObj
	bl GXGetTexObjWidth
	clrlwi r4, r3, 16
	lis r0, 0x4330
	lis r3, double_to_int_mask_802c4f10@ha
	stw r4, 0x2c(r1)
	addi r4, r3, double_to_int_mask_802c4f10@l
	lfs f0, float_0p7_8041a584(r2)
	stw r0, 0x28(r1)
	li r3, 0x3
	lfd f2, 0x0(r4)
	lfd f1, 0x28(r1)
	fsubs f1, f1, f2
	fmuls f0, f0, f1
	stfs f0, 0x14(r31)
	bl getWakuTexObj
	bl GXGetTexObjHeight
	clrlwi r4, r3, 16
	lis r0, 0x4330
	stw r4, 0x24(r1)
	lis r3, double_to_int_mask_802c4f10@ha
	lfd f2, double_to_int_mask_802c4f10@l(r3)
	stw r0, 0x20(r1)
	lfs f0, float_0p7_8041a584(r2)
	lfd f1, 0x20(r1)
	fsubs f1, f1, f2
	fmuls f0, f0, f1
	stfs f0, 0x18(r31)
	@6:
	mr r3, r27
	lmw r26, 0x38(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm s32 msgIconStr2ID(const char* str) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, msgIcon@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	addi r31, r4, msgIcon@l
	stw r30, 0x18(r1)
	li r30, 0x0
	stw r29, 0x14(r1)
	mr r29, r3
	@1:
	lwz r3, 0x0(r31)
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	bne @2
	lis r3, msgIcon@ha
	slwi r0, r30, 3
	addi r3, r3, msgIcon@l
	add r3, r3, r0
	lwz r3, 0x4(r3)
	b @3
	@2:
	addi r30, r30, 0x1
	addi r31, r31, 0x8
	cmplwi r30, 0x12
	blt @1
	li r3, -0x1
	@3:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm char* msgGetCommand(char* msg, char* cmd, char* arg) {
	nofralloc
	li r0, 0x80
	li r7, 0x0
	mtctr r0
	@1:
	lbz r6, 0x0(r3)
	extsb r0, r6
	cmpwi r0, 0x3e
	beq @2
	bge @3
	cmpwi r0, 0x20
	beq @4
	b @3
	@2:
	cmpwi r7, 0x0
	bne @5
	li r0, 0x0
	stb r0, 0x0(r4)
	b @6
	@5:
	li r0, 0x0
	stb r0, 0x0(r5)
	@6:
	addi r3, r3, 0x1
	blr
	@4:
	cmpwi r7, 0x0
	bne @7
	li r0, 0x0
	li r7, 0x1
	stb r0, 0x0(r4)
	b @8
	@7:
	stb r6, 0x0(r5)
	addi r5, r5, 0x1
	b @8
	@3:
	cmpwi r7, 0x0
	bne @9
	stb r6, 0x0(r4)
	addi r4, r4, 0x1
	b @8
	@9:
	stb r6, 0x0(r5)
	addi r5, r5, 0x1
	@8:
	addi r3, r3, 0x1
	bdnz @1
	li r3, 0x0
	blr
}

asm BOOL _ismbblead(u32 a1) {
	nofralloc
	clrlwi r0, r3, 24
	cmplwi r0, 0x81
	blt @1
	cmplwi r0, 0x9f
	ble @2
	@1:
	cmplwi r0, 0xe0
	blt @3
	cmplwi r0, 0xfc
	bgt @3
	@2:
	li r3, 0x1
	blr
	@3:
	li r3, 0x0
	blr
}

asm const char* msgSearch(const char* tag) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r23, 0xc(r1)
	mr r23, r3
	li r27, 0x0
	li r31, 0x0
	@1:
	lwz r0, msgw(r13)
	add r29, r0, r31
	lwz r3, 0xc(r29)
	cmplwi r3, 0x0
	beq @2
	lwz r28, 0x0(r3)
	li r25, 0x0
	lwz r26, 0x8(r29)
	b @3
	@4:
	add r4, r25, r26
	lwz r0, 0x8(r29)
	srwi r3, r4, 31
	add r3, r3, r4
	srawi r24, r3, 1
	cmpw r24, r0
	bge @2
	slwi r30, r24, 3
	lwz r4, 0x4(r29)
	lwzx r0, r28, r30
	mr r3, r23
	add r4, r4, r0
	bl strcmp
	cmpwi r3, 0x0
	bne @5
	add r3, r28, r30
	lwz r4, 0x4(r29)
	lwz r0, 0x4(r3)
	add r3, r4, r0
	b @6
	@5:
	bge @7
	subi r26, r24, 0x1
	b @3
	@7:
	addi r25, r24, 0x1
	@3:
	cmpw r26, r25
	bge @4
	@2:
	addi r27, r27, 0x1
	addi r31, r31, 0x10
	cmpwi r27, 0x2
	blt @1
	lwz r4, gp(r13)
	la r3, ErrMessage(r13)
	lwz r0, 0x16c(r4)
	slwi r0, r0, 2
	lwzx r3, r3, r0
	@6:
	lmw r23, 0xc(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm int msg_compare(const void* a, const void* b) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lwz r3, 0x0(r3)
	stw r0, 0x14(r1)
	lwz r0, 0x0(r4)
	lwz r5, msgSortDvdData(r13)
	add r3, r5, r3
	add r4, r5, r0
	bl strcmp
	cmpwi r3, 0x0
	ble @1
	li r3, 0x1
	b @2
	@1:
	srawi r3, r3, 31
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm MessageWork* L_msgGetWork(void) {
	nofralloc
	la r3, msgWork(r13)
	blr
}

asm void msgAnalize(smartEntry* smart, char* msg) {
	nofralloc
	stwu r1, -0x2b0(r1)
	mflr r0
	stw r0, 0x2b4(r1)
	stfd f31, 0x2a0(r1)
	psq_st f31, 0x2a8(r1), 0, 0
	stfd f30, 0x290(r1)
	psq_st f30, 0x298(r1), 0, 0
	stfd f29, 0x280(r1)
	psq_st f29, 0x288(r1), 0, 0
	stmw r14, 0x238(r1)
	lwz r30, 0x0(r3)
	lis r3, R_no_messages_JP@ha
	lfs f0, float_1_8041a52c(r2)
	mr r21, r4
	lwz r0, 0x38(r30)
	addi r18, r3, R_no_messages_JP@l
	lwz r29, 0x7a4c(r30)
	li r23, 0x0
	mulli r3, r0, 0x18
	lfs f29, float_0_8041a514(r2)
	stfs f0, 0x50(r1)
	lwz r0, 0x8(r29)
	addi r28, r3, 0x3c
	add r28, r30, r28
	cmpwi r0, 0x0
	bge @1
	li r0, 0x0
	stw r0, 0x8(r29)
	@1:
	li r0, 0x0
	lwz r24, 0x7a30(r30)
	sth r0, 0x234(r1)
	lha r0, 0x7a38(r30)
	lha r27, 0x7a34(r30)
	sth r0, 0x232(r1)
	lha r0, 0x7a3a(r30)
	lha r26, 0x7a36(r30)
	sth r0, 0x230(r1)
	lwz r0, 0x7a3c(r30)
	stw r0, 0x54(r1)
	lwz r0, 0x8(r29)
	cmpwi r0, 0x8
	beq @2
	bge @3
	cmpwi r0, 0x3
	beq @2
	b @3
	@2:
	cmpwi r0, 0x8
	beq @4
	bge @5
	cmpwi r0, 0x3
	beq @6
	b @5
	@6:
	lwz r0, dat_8041a500(r2)
	stw r0, 0x0(r28)
	b @5
	@4:
	lwz r0, dat_8041a504(r2)
	stw r0, 0x0(r28)
	@5:
	lis r3, 0x1
	subi r0, r3, 0x9
	sth r0, 0x4(r28)
	stw r24, 0xc(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	@3:
	lbz r3, 0x0(r21)
	clrlwi r0, r3, 24
	cmplwi r0, 0x81
	blt @7
	cmplwi r0, 0x9f
	ble @8
	@7:
	cmplwi r0, 0xe0
	blt @9
	cmplwi r0, 0xfc
	bgt @9
	@8:
	li r0, 0x1
	b @10
	@9:
	li r0, 0x0
	@10:
	cmpwi r0, 0x0
	beq @11
	lhz r3, 0x0(r21)
	bl kanjiSearch
	mr r14, r3
	clrlwi r3, r3, 16
	bl kanjiGetWidth
	lfs f2, 0x50(r1)
	clrlwi r3, r3, 16
	addi r3, r3, 0x4
	lis r0, 0x4330
	sth r14, 0x4(r28)
	xoris r3, r3, 0x8000
	lfs f1, float_10_8041a538(r2)
	sth r27, 0x6(r28)
	lfd f3, 0x118(r18)
	lfs f0, 0x50(r1)
	stw r3, 0x1fc(r1)
	fmuls f0, f1, f0
	stw r0, 0x1f8(r1)
	fctiwz f0, f0
	lfd f1, 0x1f8(r1)
	fsubs f1, f1, f3
	stfd f0, 0x208(r1)
	lwz r0, 0x20c(r1)
	fmuls f0, f2, f1
	subf r0, r0, r26
	sth r0, 0x8(r28)
	fctiwz f1, f0
	lfs f0, 0x50(r1)
	stfd f1, 0x200(r1)
	stfs f0, 0x10(r28)
	lwz r3, 0x204(r1)
	stw r23, 0x0(r28)
	lhz r0, 0x0(r21)
	cmplwi r0, 0x8145
	bne @12
	lwz r0, 0x0(r28)
	ori r0, r0, 0x10
	stw r0, 0x0(r28)
	b @13
	@12:
	cmplwi r0, 0x8140
	beq @13
	cmplwi r0, 0x8151
	beq @13
	lwz r0, 0x0(r28)
	ori r0, r0, 0x8
	stw r0, 0x0(r28)
	@13:
	clrlwi. r0, r23, 31
	beq @14
	lfs f0, 0x4c(r1)
	stfs f0, 0x14(r28)
	@14:
	lfs f0, 0x50(r1)
	fcmpo cr0, f29, f0
	bge @15
	fmr f29, f0
	@15:
	stw r24, 0xc(r28)
	add r0, r27, r3
	extsh r27, r0
	addi r21, r21, 0x2
	lwz r3, 0x38(r30)
	addi r28, r28, 0x18
	lwz r4, 0x54(r1)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	add r24, r24, r4
	b @3
	@11:
	extsb r0, r3
	cmpwi r0, 0xa
	beq @16
	bge @17
	cmpwi r0, 0x0
	beq @18
	b @19
	@17:
	cmpwi r0, 0x3c
	beq @20
	b @19
	@18:
	lis r3, 0x1
	subi r0, r3, 0x1
	sth r0, 0x4(r28)
	lha r0, 0x232(r1)
	stw r24, 0xc(r28)
	stw r24, 0x7a30(r30)
	sth r27, 0x7a34(r30)
	sth r26, 0x7a36(r30)
	sth r0, 0x7a38(r30)
	lha r0, 0x230(r1)
	sth r0, 0x7a3a(r30)
	b @21
	@16:
	lis r3, 0x1
	lfs f0, float_0_8041a514(r2)
	subi r0, r3, 0x5
	li r27, 0x0
	sth r0, 0x4(r28)
	fcmpu cr0, f0, f29
	stw r24, 0xc(r28)
	bne @22
	lfs f29, float_1_8041a52c(r2)
	@22:
	extsh r3, r26
	lis r4, 0x4330
	lha r0, 0x230(r1)
	xoris r3, r3, 0x8000
	lfs f0, float_32_8041a588(r2)
	addi r21, r21, 0x1
	stw r3, 0x20c(r1)
	xoris r0, r0, 0x8000
	fmuls f3, f0, f29
	lfd f2, 0x118(r18)
	stw r4, 0x208(r1)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	lfd f0, 0x208(r1)
	stw r0, 0x1fc(r1)
	addi r0, r3, 0x1
	fsubs f1, f0, f2
	lwz r3, 0x54(r1)
	stw r4, 0x1f8(r1)
	lfs f29, float_0_8041a514(r2)
	add r24, r24, r3
	lfd f0, 0x1f8(r1)
	fsubs f1, f1, f3
	stw r0, 0x38(r30)
	fsubs f0, f0, f2
	lwz r0, 0x4(r30)
	fctiwz f1, f1
	fsubs f0, f0, f3
	rlwinm. r0, r0, 0, 26, 26
	stfd f1, 0x200(r1)
	fctiwz f0, f0
	lwz r26, 0x204(r1)
	stfd f0, 0x210(r1)
	lwz r0, 0x214(r1)
	sth r0, 0x230(r1)
	beq @3
	lbz r4, 0x7a40(r30)
	li r5, 0x100
	rlwinm r23, r23, 0, 24, 15
	extsb r3, r4
	addi r0, r4, 0x1
	slw r3, r5, r3
	stb r0, 0x7a40(r30)
	or r23, r23, r3
	b @3
	@20:
	li r0, 0x80
	addi r5, r21, 0x1
	addi r4, r1, 0x178
	addi r3, r1, 0xf8
	li r6, 0x0
	mtctr r0
	@23:
	lbz r7, 0x0(r5)
	extsb r0, r7
	cmpwi r0, 0x3e
	beq @24
	bge @25
	cmpwi r0, 0x20
	beq @26
	b @25
	@24:
	cmpwi r6, 0x0
	bne @27
	li r0, 0x0
	stb r0, 0x0(r4)
	b @28
	@27:
	li r0, 0x0
	stb r0, 0x0(r3)
	@28:
	addi r15, r5, 0x1
	b @29
	@26:
	cmpwi r6, 0x0
	bne @30
	li r0, 0x0
	li r6, 0x1
	stb r0, 0x0(r4)
	b @31
	@30:
	stb r7, 0x0(r3)
	addi r3, r3, 0x1
	b @31
	@25:
	cmpwi r6, 0x0
	bne @32
	stb r7, 0x0(r4)
	addi r4, r4, 0x1
	b @31
	@32:
	stb r7, 0x0(r3)
	addi r3, r3, 0x1
	@31:
	addi r5, r5, 0x1
	bdnz @23
	li r15, 0x0
	@29:
	mr r21, r15
	addi r3, r1, 0x178
	la r4, str_8041A58C(r2)
	bl strcmp
	cmpwi r3, 0x0
	beq @33
	addi r3, r1, 0x178
	la r4, str_8041A590(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @34
	@33:
	lis r3, 0x1
	subi r0, r3, 0x2
	sth r0, 0x4(r28)
	lha r0, 0x232(r1)
	sth r0, 0x6(r28)
	stw r24, 0xc(r28)
	addi r24, r24, 0x64
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	addi r0, r3, 0x1
	lha r3, 0x232(r1)
	stw r0, 0x38(r30)
	addi r3, r3, 0x1
	sth r3, 0x232(r1)
	b @35
	@34:
	addi r3, r1, 0x178
	addi r4, r18, 0x128
	bl strcmp
	cmpwi r3, 0x0
	bne @36
	lwz r0, 0x4(r30)
	ori r0, r0, 0x100
	stw r0, 0x4(r30)
	b @35
	@36:
	addi r3, r1, 0x178
	la r4, str_8041A594(r2)
	bl strcmp
	cmpwi r3, 0x0
	beq @37
	addi r3, r1, 0x178
	addi r4, r18, 0x130
	bl strcmp
	cmpwi r3, 0x0
	bne @38
	@37:
	lha r0, 0x230(r1)
	extsh. r0, r0
	beq @35
	lis r4, 0x1
	subi r0, r26, 0x6
	lha r3, 0x230(r1)
	subi r4, r4, 0x3
	sth r4, 0x4(r28)
	extsh r0, r0
	subi r3, r3, 0x3
	subi r26, r26, 0x3
	sth r3, 0x8(r28)
	stw r24, 0xc(r28)
	addi r24, r24, 0x32
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	sth r0, 0x234(r1)
	li r0, 0x0
	sth r0, 0x230(r1)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	b @35
	@38:
	addi r3, r1, 0x178
	la r4, str_8041A598(r2)
	bl strcmp
	cmpwi r3, 0x0
	beq @39
	addi r3, r1, 0x178
	addi r4, r18, 0x13c
	bl strcmp
	cmpwi r3, 0x0
	bne @40
	@39:
	lis r3, 0x1
	subi r0, r3, 0x4
	sth r0, 0x4(r28)
	stw r24, 0xc(r28)
	addi r24, r24, 0x32
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	b @35
	@40:
	addi r3, r1, 0x178
	la r4, str_8041A59C(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @41
	addi r3, r1, 0xf8
	addi r5, r1, 0x48
	addi r6, r1, 0x44
	la r4, str_8041A5A0(r2)
	crclr 6
	bl sscanf
	lwz r3, 0x44(r1)
	lwz r0, 0x48(r1)
	cmpwi r3, 0x3e7
	extsh r27, r0
	beq @42
	lha r0, 0x234(r1)
	subf r0, r3, r0
	extsh r26, r0
	@42:
	neg r0, r3
	extsh r0, r0
	sth r0, 0x230(r1)
	b @35
	@41:
	addi r3, r1, 0x178
	la r4, str_8041A5A8(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @43
	addi r3, r1, 0xf8
	addi r5, r1, 0x50
	la r4, str_8041A5B0(r2)
	crclr 6
	bl sscanf
	b @35
	@43:
	addi r3, r1, 0x178
	addi r4, r18, 0x148
	bl strcmp
	cmpwi r3, 0x0
	bne @44
	lfs f0, float_1_8041a52c(r2)
	stfs f0, 0x50(r1)
	b @35
	@44:
	addi r3, r1, 0x178
	la r4, str_8041A5B4(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @45
	addi r3, r1, 0xf8
	addi r5, r1, 0x40
	la r4, str_8041A5BC(r2)
	crclr 6
	bl sscanf
	lwz r0, 0x40(r1)
	add r24, r24, r0
	b @35
	@45:
	addi r3, r1, 0x178
	la r4, str_8041A5C0(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @46
	addi r3, r1, 0xf8
	addi r5, r1, 0x54
	la r4, str_8041A5BC(r2)
	crclr 6
	bl sscanf
	b @35
	@46:
	addi r3, r1, 0x178
	addi r4, r18, 0x150
	bl strcmp
	cmpwi r3, 0x0
	bne @47
	lwz r0, 0x7a3c(r30)
	stw r0, 0x54(r1)
	b @35
	@47:
	addi r3, r1, 0x178
	addi r4, r18, 0x158
	bl strcmp
	cmpwi r3, 0x0
	bne @48
	addi r3, r1, 0xf8
	addi r5, r1, 0x4c
	la r4, str_8041A5B0(r2)
	crclr 6
	bl sscanf
	ori r23, r23, 0x1
	b @35
	@48:
	addi r3, r1, 0x178
	addi r4, r18, 0x160
	bl strcmp
	cmpwi r3, 0x0
	bne @49
	clrrwi r23, r23, 1
	b @35
	@49:
	addi r3, r1, 0x178
	la r4, str_8041A5C8(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @50
	ori r23, r23, 0x2
	b @35
	@50:
	addi r3, r1, 0x178
	addi r4, r18, 0x16c
	bl strcmp
	cmpwi r3, 0x0
	bne @51
	rlwinm r23, r23, 0, 31, 29
	b @35
	@51:
	addi r3, r1, 0x178
	la r4, str_8041A5D0(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @52
	ori r23, r23, 0x4
	b @35
	@52:
	addi r3, r1, 0x178
	la r4, str_8041A5D8(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @53
	rlwinm r23, r23, 0, 30, 28
	b @35
	@53:
	addi r3, r1, 0x178
	la r4, str_8041A5E0(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @54
	mr r5, r28
	addi r3, r1, 0xf8
	la r4, str_8041A5E4(r2)
	crclr 6
	bl sscanf
	lis r3, 0x1
	subi r0, r3, 0x9
	sth r0, 0x4(r28)
	stw r24, 0xc(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	b @35
	@54:
	addi r3, r1, 0x178
	la r4, str_8041A5E8(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @55
	li r0, 0xff
	lis r3, 0x1
	stw r0, 0x0(r28)
	subi r0, r3, 0x9
	sth r0, 0x4(r28)
	stw r24, 0xc(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	b @35
	@55:
	addi r3, r1, 0x178
	la r4, str_8041A5F0(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @56
	li r0, 0x1
	lis r3, 0x1
	stw r0, 0x0(r28)
	subi r0, r3, 0xa
	sth r0, 0x4(r28)
	stw r24, 0xc(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	b @35
	@56:
	addi r3, r1, 0x178
	addi r4, r18, 0x174
	bl strcmp
	cmpwi r3, 0x0
	bne @57
	li r0, 0x0
	lis r3, 0x1
	stw r0, 0x0(r28)
	subi r0, r3, 0xa
	sth r0, 0x4(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	b @35
	@57:
	addi r3, r1, 0x178
	la r4, str_8041A5F8(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @58
	li r0, 0x1
	lis r3, 0x1
	stw r0, 0x0(r28)
	subi r0, r3, 0xb
	sth r0, 0x4(r28)
	stw r24, 0xc(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	b @35
	@58:
	addi r3, r1, 0x178
	la r4, str_8041A600(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @59
	li r0, 0x0
	lis r3, 0x1
	stw r0, 0x0(r28)
	subi r0, r3, 0xb
	sth r0, 0x4(r28)
	stw r24, 0xc(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	b @35
	@59:
	addi r3, r1, 0x178
	la r4, str_8041A608(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @60
	li r3, 0x2
	li r0, 0x0
	stw r3, 0x8(r29)
	stw r0, 0x54(r1)
	stw r0, 0x7a3c(r30)
	b @35
	@60:
	addi r3, r1, 0x178
	addi r4, r18, 0x17c
	bl strcmp
	cmpwi r3, 0x0
	bne @61
	li r0, 0x3
	lis r3, 0x1
	stw r0, 0x8(r29)
	subi r0, r3, 0x9
	lwz r3, dat_8041a508(r2)
	stw r3, 0x0(r28)
	sth r0, 0x4(r28)
	stw r24, 0xc(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	b @35
	@61:
	addi r3, r1, 0x178
	la r4, str_8041A610(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @62
	li r0, 0x8
	lis r3, 0x1
	stw r0, 0x8(r29)
	subi r0, r3, 0x9
	lwz r3, dat_8041a50c(r2)
	stw r3, 0x0(r28)
	sth r0, 0x4(r28)
	stw r24, 0xc(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	b @35
	@62:
	addi r3, r1, 0x178
	la r4, str_8041A614(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @63
	li r0, 0x9
	stw r0, 0x8(r29)
	b @35
	@63:
	addi r3, r1, 0x178
	la r4, str_8041A61C(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @64
	li r0, 0x7
	stw r0, 0x8(r29)
	b @35
	@64:
	addi r3, r1, 0x178
	addi r4, r18, 0x184
	bl strcmp
	cmpwi r3, 0x0
	bne @65
	li r0, 0xa
	stw r0, 0x8(r29)
	b @35
	@65:
	addi r3, r1, 0x178
	la r4, str_8041A624(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @66
	li r0, 0x6
	stw r0, 0x8(r29)
	b @35
	@66:
	addi r3, r1, 0x178
	addi r4, r18, 0x18c
	bl strcmp
	cmpwi r3, 0x0
	bne @67
	li r3, 0x4
	li r0, 0x0
	stw r3, 0x8(r29)
	stw r0, 0x54(r1)
	stw r0, 0x7a3c(r30)
	b @35
	@67:
	addi r3, r1, 0x178
	la r4, str_8041A62C(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @68
	li r0, 0x1
	stw r0, 0x8(r29)
	lwz r0, 0x4(r30)
	ori r0, r0, 0x10
	stw r0, 0x4(r30)
	b @35
	@68:
	addi r3, r1, 0x178
	la r4, str_8041A634(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @69
	li r0, 0xb
	stw r0, 0x8(r29)
	b @35
	@69:
	addi r3, r1, 0x178
	la r4, str_8041A63C(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @70
	addi r3, r1, 0xf8
	addi r4, r18, 0x194
	addi r5, r1, 0x16
	addi r6, r1, 0x14
	addi r7, r1, 0x12
	addi r8, r1, 0x10
	crclr 6
	bl sscanf
	lhz r3, 0x2(r29)
	lis r0, 0x4330
	stw r0, 0x210(r1)
	ori r3, r3, 0x4
	lfd f1, 0x118(r18)
	sth r3, 0x2(r29)
	lha r3, 0x16(r1)
	stw r0, 0x208(r1)
	xoris r3, r3, 0x8000
	stw r3, 0x214(r1)
	lfd f0, 0x210(r1)
	stw r0, 0x200(r1)
	fsubs f0, f0, f1
	stw r0, 0x1f8(r1)
	stfs f0, 0xc(r29)
	lha r0, 0x14(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x20c(r1)
	lfd f0, 0x208(r1)
	fsubs f0, f0, f1
	stfs f0, 0x10(r29)
	lha r0, 0x12(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x204(r1)
	lfd f0, 0x200(r1)
	fsubs f0, f0, f1
	stfs f0, 0x14(r29)
	lha r0, 0x10(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x1fc(r1)
	lfd f0, 0x1f8(r1)
	fsubs f0, f0, f1
	stfs f0, 0x18(r29)
	b @35
	@70:
	addi r3, r1, 0x178
	addi r4, r18, 0x1a4
	bl strcmp
	cmpwi r3, 0x0
	bne @71
	li r0, 0x5
	addi r3, r1, 0xf8
	stw r0, 0x8(r29)
	addi r4, r18, 0x1ac
	addi r5, r1, 0xe
	addi r6, r1, 0xc
	lwz r0, 0x4(r30)
	addi r7, r30, 0x7a44
	addi r8, r30, 0x7a46
	ori r0, r0, 0x20
	stw r0, 0x4(r30)
	crclr 6
	bl sscanf
	lha r4, 0xe(r1)
	li r3, 0x1
	li r0, 0x0
	ori r23, r23, 0x100
	stb r4, 0x7a41(r30)
	lha r4, 0xc(r1)
	stb r4, 0x7a42(r30)
	stb r3, 0x7a40(r30)
	stw r0, 0x54(r1)
	b @35
	@71:
	addi r3, r1, 0x178
	la r4, str_8041A644(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @72
	mr r5, r28
	addi r3, r1, 0xf8
	la r4, str_8041A5BC(r2)
	crclr 6
	bl sscanf
	lis r3, 0x1
	subi r0, r3, 0x6
	sth r0, 0x4(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	b @35
	@72:
	addi r3, r1, 0x178
	la r4, str_8041A648(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @73
	mr r5, r28
	addi r3, r1, 0xf8
	la r4, str_8041A5BC(r2)
	crclr 6
	bl sscanf
	lis r3, 0x1
	subi r0, r3, 0x7
	sth r0, 0x4(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	b @35
	@73:
	addi r3, r1, 0x178
	addi r4, r18, 0x1bc
	bl strcmp
	cmpwi r3, 0x0
	bne @74
	lhz r0, 0x2(r29)
	ori r0, r0, 0x8
	sth r0, 0x2(r29)
	b @35
	@74:
	addi r3, r1, 0x178
	la r4, str_8041A64C(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @75
	lbz r0, 0xf8(r1)
	li r14, 0x0
	extsb r0, r0
	cmpwi r0, 0x30
	blt @76
	cmpwi r0, 0x39
	bgt @76
	addi r3, r1, 0xf8
	addi r4, r18, 0x1c4
	addi r5, r1, 0x3c
	addi r6, r1, 0x2c
	addi r7, r1, 0x38
	addi r8, r1, 0x34
	addi r9, r1, 0x30
	crclr 6
	bl sscanf
	b @77
	@76:
	addi r3, r1, 0xf8
	addi r4, r18, 0x1d0
	addi r5, r1, 0xd8
	addi r6, r1, 0x2c
	addi r7, r1, 0x38
	addi r8, r1, 0x34
	addi r9, r1, 0x30
	crclr 6
	bl sscanf
	addi r3, r1, 0xd8
	la r4, str_8041A4D0(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @78
	li r14, 0x1
	@78:
	lis r3, msgIcon@ha
	li r16, 0x0
	addi r17, r3, msgIcon@l
	@79:
	lwz r3, 0x0(r17)
	addi r4, r1, 0xd8
	bl strcmp
	cmpwi r3, 0x0
	bne @80
	lis r3, msgIcon@ha
	slwi r4, r16, 3
	addi r0, r3, msgIcon@l
	add r3, r0, r4
	lwz r0, 0x4(r3)
	b @81
	@80:
	addi r16, r16, 0x1
	addi r17, r17, 0x8
	cmplwi r16, 0x12
	blt @79
	li r0, -0x1
	@81:
	cmpwi r0, 0x0
	stw r0, 0x3c(r1)
	bge @77
	li r0, 0x0
	stw r0, 0x3c(r1)
	@77:
	cmpwi r14, 0x0
	bne @82
	lwz r0, 0x3c(r1)
	addi r3, r1, 0xa
	addi r4, r1, 0x8
	stw r0, 0x0(r28)
	lwz r0, 0x3c(r1)
	clrlwi r5, r0, 16
	bl iconGetWidthHight
	lis r3, 0x1
	lis r5, 0x4330
	subi r3, r3, 0x8
	extsh r0, r27
	sth r3, 0x4(r28)
	xoris r3, r0, 0x8000
	extsh r0, r26
	lfd f3, 0x120(r18)
	lhz r4, 0xa(r1)
	xoris r0, r0, 0x8000
	stw r5, 0x208(r1)
	addi r27, r27, 0x28
	lwz r6, 0x38(r1)
	stw r4, 0x20c(r1)
	xoris r4, r6, 0x8000
	lfd f5, 0x118(r18)
	lfd f0, 0x208(r1)
	stw r3, 0x204(r1)
	fsubs f2, f0, f3
	lfs f4, float_0p5_8041a534(r2)
	stw r5, 0x200(r1)
	lfs f1, 0x2c(r1)
	lfd f0, 0x200(r1)
	fmuls f2, f4, f2
	stw r4, 0x214(r1)
	fsubs f0, f0, f5
	stw r5, 0x210(r1)
	lfd f4, 0x210(r1)
	fmadds f0, f2, f1, f0
	stw r0, 0x224(r1)
	fsubs f1, f4, f5
	stw r5, 0x218(r1)
	fadds f1, f1, f0
	stw r5, 0x220(r1)
	lfd f0, 0x220(r1)
	fctiwz f1, f1
	fsubs f0, f0, f5
	stfd f1, 0x1f8(r1)
	lwz r0, 0x1fc(r1)
	sth r0, 0x6(r28)
	lhz r0, 0x8(r1)
	lfs f1, 0x2c(r1)
	stw r0, 0x21c(r1)
	lfd f2, 0x218(r1)
	fsubs f2, f2, f3
	fnmsubs f0, f2, f1, f0
	fctiwz f0, f0
	stfd f0, 0x228(r1)
	lwz r0, 0x22c(r1)
	sth r0, 0x8(r28)
	lwz r0, 0x34(r1)
	sth r0, 0xa(r28)
	lfs f0, 0x2c(r1)
	stfs f0, 0x10(r28)
	stw r24, 0xc(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	lwz r4, 0x54(r1)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	add r24, r24, r4
	b @35
	@82:
	lis r3, 0x1
	subi r3, r3, 0x6b4b
	bl kanjiSearch
	mr r14, r3
	clrlwi r3, r3, 16
	bl kanjiGetWidth
	clrlwi r4, r3, 16
	lis r3, 0x4330
	addi r4, r4, 0x4
	stw r3, 0x228(r1)
	xoris r4, r4, 0x8000
	lfd f3, 0x118(r18)
	stw r4, 0x22c(r1)
	clrlwi. r0, r23, 31
	lfs f0, 0x50(r1)
	lfd f2, 0x228(r1)
	lfs f1, float_10_8041a538(r2)
	fsubs f2, f2, f3
	fmuls f0, f0, f2
	fctiwz f0, f0
	stfd f0, 0x220(r1)
	lwz r0, 0x224(r1)
	sth r0, 0xa(r1)
	sth r14, 0x4(r28)
	sth r27, 0x6(r28)
	lfs f0, 0x50(r1)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x218(r1)
	lwz r0, 0x21c(r1)
	subf r0, r0, r26
	sth r0, 0x8(r28)
	lfs f0, 0x50(r1)
	stfs f0, 0x10(r28)
	stw r23, 0x0(r28)
	lwz r0, 0x0(r28)
	ori r0, r0, 0x8
	stw r0, 0x0(r28)
	beq @83
	lfs f0, 0x4c(r1)
	stfs f0, 0x14(r28)
	@83:
	lfs f0, 0x50(r1)
	fcmpo cr0, f29, f0
	bge @84
	fmr f29, f0
	@84:
	stw r24, 0xc(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	lwz r4, 0x54(r1)
	lhz r5, 0xa(r1)
	addi r0, r3, 0x1
	add r24, r24, r4
	add r3, r27, r5
	stw r0, 0x38(r30)
	extsh r27, r3
	b @35
	@75:
	addi r3, r1, 0x178
	la r4, str_8041A654(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @85
	addi r3, r1, 0xf8
	addi r4, r18, 0x1dc
	addi r5, r1, 0xb8
	addi r6, r1, 0x98
	addi r7, r1, 0x28
	addi r8, r1, 0x24
	addi r9, r1, 0x1c
	addi r10, r1, 0x20
	crclr 6
	bl sscanf
	addi r3, r1, 0xb8
	li r4, 0x2
	bl animPoseEntry
	stw r3, 0x0(r28)
	addi r4, r1, 0x98
	li r5, 0x1
	lwz r3, 0x0(r28)
	bl animPoseSetAnim
	lwz r3, 0x0(r28)
	li r4, 0x1800
	bl animPoseSetMaterialFlagOn
	lwz r3, 0x0(r28)
	li r4, 0x40
	bl animPoseSetMaterialFlagOff
	lwz r6, msgw(r13)
	lis r3, msgDispKeyWait_render@ha
	addi r4, r3, msgDispKeyWait_render@l
	li r5, 0x0
	lwz r3, 0x20(r6)
	bl animPoseSetGXFunc
	lis r3, 0x1
	subi r0, r3, 0xc
	sth r0, 0x4(r28)
	lwz r0, 0x28(r1)
	sth r0, 0x6(r28)
	lha r0, 0x234(r1)
	lwz r3, 0x24(r1)
	subf r0, r3, r0
	sth r0, 0x8(r28)
	lfs f0, 0x1c(r1)
	stfs f0, 0x10(r28)
	lwz r0, 0x20(r1)
	cmpwi r0, 0x0
	bne @86
	lfs f0, float_0_8041a514(r2)
	b @87
	@86:
	lfs f0, float_180_8041a568(r2)
	@87:
	stfs f0, 0x14(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	lwz r4, 0x54(r1)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	add r24, r24, r4
	b @35
	@85:
	addi r3, r1, 0x178
	la r4, str_8041A65C(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @88
	addi r3, r1, 0xf8
	addi r5, r1, 0x78
	addi r6, r1, 0x18
	la r4, str_8041A664(r2)
	crclr 6
	bl sscanf
	addi r3, r1, 0x78
	la r4, str_8041A66C(r2)
	bl strcmp
	cmpwi r3, 0x0
	beq @89
	addi r3, r1, 0x78
	bl npcNameToPtr
	b @90
	@89:
	li r3, 0x0
	@90:
	lis r4, 0x1
	stw r3, 0x0(r28)
	subi r0, r4, 0xd
	sth r0, 0x4(r28)
	lwz r0, 0x18(r1)
	stw r0, 0xc(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	b @35
	@88:
	addi r3, r1, 0x178
	addi r4, r18, 0x1ec
	bl strcmp
	cmpwi r3, 0x0
	bne @91
	addi r3, r1, 0xf8
	addi r5, r1, 0x58
	la r4, str_8041A670(r2)
	crclr 6
	bl sscanf
	addi r3, r1, 0x58
	la r4, str_8041A66C(r2)
	bl strcmp
	cmpwi r3, 0x0
	beq @92
	addi r3, r1, 0x58
	bl npcNameToPtr
	b @93
	@92:
	li r3, 0x0
	@93:
	lis r4, 0x1
	stw r3, 0x0(r28)
	subi r0, r4, 0xe
	sth r0, 0x4(r28)
	addi r28, r28, 0x18
	lwz r3, 0x38(r30)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	b @35
	@91:
	addi r3, r1, 0x178
	la r4, str_8041A674(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @94
	lwz r3, 0x7a4c(r30)
	lwz r0, 0x8(r3)
	cmpwi r0, 0x1
	beq @35
	mr r25, r27
	b @35
	@94:
	lbz r3, 0x178(r1)
	extsb r0, r3
	cmpwi r0, 0x52
	beq @95
	cmpwi r0, 0x2f
	bne @35
	cmplwi r0, 0x2f72
	bne @35
	@95:
	extsb r0, r3
	li r17, 0x1
	cmpwi r0, 0x52
	beq @96
	li r17, 0x2
	@96:
	lwz r3, 0x7a4c(r30)
	lwz r0, 0x8(r3)
	cmpwi r0, 0x1
	beq @3
	addi r3, r1, 0x178
	add r3, r3, r17
	bl strlen
	srwi r4, r3, 31
	addi r0, r1, 0x178
	add r3, r4, r3
	lfd f31, 0x118(r18)
	lfs f30, float_0p55_8041a678(r2)
	mr r15, r17
	srawi r22, r3, 1
	add r20, r0, r17
	li r19, 0x0
	li r16, 0x0
	lis r14, 0x4330
	b @97
	@98:
	lhz r3, 0x0(r20)
	bl kanjiSearch
	clrlwi r3, r3, 16
	bl kanjiGetWidth
	clrlwi r3, r3, 16
	stw r14, 0x228(r1)
	addi r0, r3, 0x4
	lfs f0, 0x50(r1)
	xoris r0, r0, 0x8000
	addi r15, r15, 0x2
	stw r0, 0x22c(r1)
	addi r20, r20, 0x2
	addi r16, r16, 0x1
	lfd f1, 0x228(r1)
	fsubs f1, f1, f31
	fmuls f0, f0, f1
	fmuls f0, f30, f0
	fctiwz f0, f0
	stfd f0, 0x220(r1)
	lwz r0, 0x224(r1)
	add r19, r19, r0
	@97:
	cmpw r16, r22
	blt @98
	lis r14, 0x4330
	clrlwi r0, r19, 16
	stw r0, 0x22c(r1)
	addi r0, r1, 0x178
	lfs f2, float_4_8041a67c(r2)
	extsh r4, r25
	stw r14, 0x228(r1)
	extsh r3, r27
	lfs f1, 0x50(r1)
	add r3, r4, r3
	lfd f3, 0x120(r18)
	xoris r3, r3, 0x8000
	lfd f0, 0x228(r1)
	fmuls f4, f2, f1
	lfs f30, float_0p55_8041a678(r2)
	add r20, r0, r17
	fsubs f0, f0, f3
	stw r3, 0x21c(r1)
	lfd f31, 0x118(r18)
	stw r14, 0x218(r1)
	extsh r16, r26
	fnmsubs f1, f30, f4, f0
	lfd f0, 0x218(r1)
	clrlwi r15, r23, 31
	stw r14, 0x210(r1)
	li r31, 0x0
	fctiwz f2, f1
	fsubs f1, f0, f31
	lfs f0, float_0p5_8041a534(r2)
	stfd f2, 0x220(r1)
	fsubs f2, f1, f4
	lwz r19, 0x224(r1)
	clrlwi r0, r19, 16
	stw r0, 0x214(r1)
	lfd f1, 0x210(r1)
	fsubs f1, f1, f3
	fsubs f1, f2, f1
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x208(r1)
	lwz r25, 0x20c(r1)
	b @99
	@100:
	lhz r3, 0x0(r20)
	bl kanjiSearch
	mr r19, r3
	clrlwi r3, r3, 16
	bl kanjiGetWidth
	clrlwi r3, r3, 16
	lfs f0, 0x50(r1)
	addi r0, r3, 0x4
	stw r14, 0x228(r1)
	xoris r0, r0, 0x8000
	cmplwi r15, 0x0
	stw r0, 0x22c(r1)
	lfd f1, 0x228(r1)
	sth r19, 0x4(r28)
	fsubs f1, f1, f31
	sth r25, 0x6(r28)
	fmuls f1, f0, f1
	sth r16, 0x8(r28)
	lfs f0, 0x50(r1)
	fmuls f1, f30, f1
	fmuls f0, f30, f0
	fctiwz f1, f1
	stfs f0, 0x10(r28)
	stfd f1, 0x220(r1)
	stw r23, 0x0(r28)
	lwz r0, 0x224(r1)
	beq @101
	lfs f0, 0x4c(r1)
	stfs f0, 0x14(r28)
	@101:
	li r3, 0x0
	add r0, r25, r0
	stw r3, 0xc(r28)
	extsh r25, r0
	addi r17, r17, 0x2
	addi r20, r20, 0x2
	lwz r3, 0x38(r30)
	addi r31, r31, 0x1
	addi r28, r28, 0x18
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	@99:
	cmpw r31, r22
	blt @100
	b @3
	@35:
	lbz r0, 0x0(r15)
	cmpwi r0, 0xa
	bne @3
	addi r21, r21, 0x1
	b @3
	@19:
	lwz r4, gp(r13)
	lwz r0, 0x16c(r4)
	cmplwi r0, 0x0
	bne @102
	extsb r0, r3
	cmpwi r0, 0x30
	blt @102
	cmpwi r0, 0x39
	bgt @102
	addis r3, r3, 0x1
	subi r0, r3, 0x7de1
	clrlwi r3, r0, 16
	bl kanjiSearch
	mr r14, r3
	b @103
	@102:
	bl hankakuSearch
	mr r14, r3
	@103:
	clrlwi r3, r14, 16
	bl kanjiGetWidth
	lfs f2, 0x50(r1)
	clrlwi r3, r3, 16
	addi r3, r3, 0x2
	lis r0, 0x4330
	sth r14, 0x4(r28)
	xoris r3, r3, 0x8000
	lfs f1, float_10_8041a538(r2)
	sth r27, 0x6(r28)
	lfd f3, 0x118(r18)
	lfs f0, 0x50(r1)
	stw r3, 0x22c(r1)
	fmuls f0, f1, f0
	stw r0, 0x228(r1)
	fctiwz f0, f0
	lfd f1, 0x228(r1)
	fsubs f1, f1, f3
	stfd f0, 0x218(r1)
	lwz r0, 0x21c(r1)
	fmuls f0, f2, f1
	subf r0, r0, r26
	sth r0, 0x8(r28)
	fctiwz f1, f0
	lfs f0, 0x50(r1)
	stfd f1, 0x220(r1)
	stfs f0, 0x10(r28)
	lwz r3, 0x224(r1)
	stw r23, 0x0(r28)
	lbz r0, 0x0(r21)
	cmpwi r0, 0x20
	beq @104
	lwz r0, 0x0(r28)
	ori r0, r0, 0x8
	stw r0, 0x0(r28)
	@104:
	clrlwi. r0, r23, 31
	beq @105
	lfs f0, 0x4c(r1)
	stfs f0, 0x14(r28)
	@105:
	lfs f0, 0x50(r1)
	fcmpo cr0, f29, f0
	bge @106
	fmr f29, f0
	@106:
	stw r24, 0xc(r28)
	add r0, r27, r3
	extsh r27, r0
	addi r21, r21, 0x1
	lwz r3, 0x38(r30)
	addi r28, r28, 0x18
	lwz r4, 0x54(r1)
	addi r0, r3, 0x1
	stw r0, 0x38(r30)
	add r24, r24, r4
	b @3
	@21:
	psq_l f31, 0x2a8(r1), 0, 0
	lfd f31, 0x2a0(r1)
	psq_l f30, 0x298(r1), 0, 0
	lfd f30, 0x290(r1)
	psq_l f29, 0x288(r1), 0, 0
	lfd f29, 0x280(r1)
	lmw r14, 0x238(r1)
	lwz r0, 0x2b4(r1)
	mtlr r0
	addi r1, r1, 0x2b0
	blr
}

asm void msgDispKeyWait_render(s32 wXluStage) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	bl animGetPtr
	mr r31, r3
	li r3, 0x1
	li r4, 0x7
	li r5, 0x0
	bl GXSetZMode
	li r3, 0x0
	li r4, 0x4
	li r5, 0x5
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x0
	bl GXSetZCompLoc
	li r3, 0x6
	li r4, 0x80
	li r5, 0x1
	li r6, 0x0
	li r7, 0x0
	bl GXSetAlphaCompare
	stw r30, 0xe0(r31)
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BOOL msgDisp(smartEntry* smart, u8 alpha, f32 x, f32 y) {
	nofralloc
	stwu r1, -0x150(r1)
	mflr r0
	stw r0, 0x154(r1)
	stfd f31, 0x140(r1)
	psq_st f31, 0x148(r1), 0, 0
	stfd f30, 0x130(r1)
	psq_st f30, 0x138(r1), 0, 0
	stfd f29, 0x120(r1)
	psq_st f29, 0x128(r1), 0, 0
	stfd f28, 0x110(r1)
	psq_st f28, 0x118(r1), 0, 0
	stfd f27, 0x100(r1)
	psq_st f27, 0x108(r1), 0, 0
	stfd f26, 0xf0(r1)
	psq_st f26, 0xf8(r1), 0, 0
	stmw r24, 0xd0(r1)
	lwz r28, 0x0(r3)
	fmr f28, f1
	mr r31, r4
	fmr f29, f2
	mr r3, r31
	addi r27, r28, 0x3c
	li r25, 0x0
	bl FontDrawStart_alpha
	clrlwi r29, r31, 24
	li r26, 0x0
	b @1
	@2:
	lhz r3, 0x4(r27)
	subis r4, r3, 0x1
	addi r4, r4, 0xc
	cmplwi r4, 0xb
	bgt @3
	lis r3, jumptable_8030DBD0@ha
	slwi r4, r4, 2
	addi r3, r3, jumptable_8030DBD0@l
	lwzx r0, r3, r4
	mtctr r0
	bctr
	@4:
	li r3, 0x0
	b @5
	@6:
	lhz r3, 0x8(r28)
	lha r0, 0x6(r27)
	cmpw r3, r0
	bne @7
	li r25, 0x1
	b @7
	@8:
	lwz r0, 0x0(r27)
	addi r3, r1, 0x24
	stw r0, 0x24(r1)
	bl FontDrawColor
	b @7
	@9:
	lwz r0, 0x0(r27)
	cmplwi r0, 0x0
	beq @10
	bl FontDrawNoise
	b @7
	@10:
	bl FontDrawNoiseOff
	b @7
	@11:
	bl FontGetDrawColor
	stw r3, 0x34(r1)
	addi r3, r1, 0x74
	bl PSMTXIdentity
	lfs f1, 0x14(r27)
	lfs f0, float_90_8041a680(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @12
	lfs f0, float_270_8041a684(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @12
	lfs f1, float_1_8041a52c(r2)
	addi r3, r1, 0x74
	lfs f3, float_neg1_8041a688(r2)
	mr r4, r3
	fmr f2, f1
	bl PSMTXScaleApply
	@12:
	lwz r0, 0x28(r28)
	lis r5, 0x4330
	lis r4, double_to_int_802c4f08@ha
	lha r6, 0x6(r27)
	xoris r0, r0, 0x8000
	lha r3, 0x8(r27)
	stw r0, 0xbc(r1)
	xoris r6, r6, 0x8000
	xoris r0, r3, 0x8000
	lfd f5, double_to_int_802c4f08@l(r4)
	stw r5, 0xb8(r1)
	addi r3, r1, 0x74
	lfs f3, float_0_8041a514(r2)
	mr r4, r3
	lfd f0, 0xb8(r1)
	stw r0, 0xb4(r1)
	fsubs f1, f0, f5
	lfs f0, float_40_8041a51c(r2)
	stw r5, 0xb0(r1)
	lfd f2, 0xb0(r1)
	fadds f1, f29, f1
	stw r6, 0xac(r1)
	fsubs f2, f2, f5
	stw r5, 0xa8(r1)
	lfd f4, 0xa8(r1)
	fadds f1, f2, f1
	fsubs f4, f4, f5
	fsubs f2, f1, f0
	fadds f1, f28, f4
	bl PSMTXTransApply
	lwz r3, 0x0(r27)
	bl animPoseMain
	lwz r3, 0x0(r27)
	addi r4, r1, 0x74
	lfs f1, 0x14(r27)
	li r5, 0x2
	lfs f2, 0x10(r27)
	bl animPoseDrawMtx
	mr r3, r31
	bl FontDrawStart_alpha
	lwz r0, 0x34(r1)
	addi r3, r1, 0x20
	stw r0, 0x20(r1)
	bl FontDrawColor
	b @7
	@3:
	lwz r8, 0x28(r28)
	lis r5, 0x4330
	lha r7, 0x6(r27)
	lis r4, double_to_int_802c4f08@ha
	xoris r3, r8, 0x8000
	lha r0, 0x8(r27)
	stw r3, 0xac(r1)
	xoris r3, r7, 0x8000
	addi r6, r4, double_to_int_802c4f08@l
	xoris r4, r0, 0x8000
	stw r5, 0xa8(r1)
	li r30, 0x0
	lfd f3, 0x0(r6)
	li r24, 0xff
	stw r3, 0xbc(r1)
	lfd f0, 0xa8(r1)
	stw r5, 0xb8(r1)
	fsubs f0, f0, f3
	lwz r3, 0x4(r28)
	lfd f1, 0xb8(r1)
	stw r4, 0xb4(r1)
	rlwinm. r3, r3, 0, 25, 25
	fsubs f2, f1, f3
	stw r5, 0xb0(r1)
	fadds f0, f29, f0
	lfd f1, 0xb0(r1)
	fadds f31, f28, f2
	fsubs f1, f1, f3
	fadds f30, f1, f0
	beq @13
	lwz r4, 0x783c(r28)
	slwi r3, r4, 2
	add r3, r28, r3
	lwz r6, 0x7844(r3)
	cmpw r8, r6
	bne @14
	lwz r3, 0x7848(r3)
	add. r0, r0, r3
	ble @7
	li r30, 0x1
	b @13
	@14:
	bge @15
	add. r5, r0, r6
	ble @16
	li r30, 0x1
	b @13
	@16:
	subf r5, r8, r6
	cmpwi r5, 0x64
	ble @17
	li r5, 0x64
	@17:
	subfic r5, r5, 0x64
	lis r6, 0x51ec
	mulli r7, r5, 0xff
	lwz r5, 0x7840(r28)
	subi r6, r6, 0x7ae1
	subi r5, r5, 0x1
	mulhw r6, r6, r7
	cmpw r4, r5
	srawi r4, r6, 5
	srwi r5, r4, 31
	add r4, r4, r5
	clrlwi r24, r4, 24
	beq @18
	lwz r3, 0x7848(r3)
	add. r0, r0, r3
	ble @7
	li r30, 0x1
	b @13
	@18:
	bl FontGetDrawColor
	stw r3, 0x30(r1)
	lis r3, 0x8081
	subi r5, r3, 0x7f7f
	addi r4, r1, 0x1c
	lbz r0, 0x33(r1)
	li r3, 0x1
	mullw r0, r0, r24
	mulhw r5, r5, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x33(r1)
	lwz r0, 0x30(r1)
	stw r0, 0x1c(r1)
	bl GXSetTevColor
	b @13
	@15:
	lwz r5, 0x7848(r3)
	add. r5, r0, r5
	ble @19
	li r30, 0x1
	b @13
	@19:
	subf r5, r6, r8
	cmpwi r5, 0x64
	ble @20
	li r5, 0x64
	@20:
	mulli r7, r5, 0xff
	lis r6, 0x51ec
	lwz r5, 0x7840(r28)
	subi r6, r6, 0x7ae1
	mulhw r6, r6, r7
	subi r5, r5, 0x2
	cmpw r4, r5
	srawi r4, r6, 5
	srwi r5, r4, 31
	add r4, r4, r5
	clrlwi r24, r4, 24
	beq @21
	lwz r3, 0x784c(r3)
	add. r0, r0, r3
	ble @7
	li r30, 0x1
	b @13
	@21:
	bl FontGetDrawColor
	stw r3, 0x30(r1)
	lis r3, 0x8081
	subi r5, r3, 0x7f7f
	addi r4, r1, 0x18
	lbz r0, 0x33(r1)
	li r3, 0x1
	mullw r0, r0, r24
	mulhw r5, r5, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x33(r1)
	lwz r0, 0x30(r1)
	stw r0, 0x18(r1)
	bl GXSetTevColor
	@13:
	lhz r3, 0x4(r27)
	cmplwi r3, 0xfff8
	bne @22
	bl FontGetDrawColor
	lha r4, 0x6(r27)
	lis r8, 0x4330
	clrlwi r0, r24, 24
	lis r6, double_to_int_802c4f08@ha
	xoris r5, r4, 0x8000
	stw r3, 0x2c(r1)
	mullw r0, r0, r29
	lfd f5, double_to_int_802c4f08@l(r6)
	stw r5, 0xbc(r1)
	lis r4, 0x8081
	lfs f2, float_28_8041a550(r2)
	addi r3, r1, 0x38
	subi r5, r4, 0x7f7f
	stw r8, 0xb8(r1)
	mulhw r5, r5, r0
	lfs f1, float_40_8041a51c(r2)
	lfd f0, 0xb8(r1)
	li r4, 0x10
	stw r8, 0xc0(r1)
	fsubs f0, f0, f5
	fadds f0, f28, f0
	add r0, r5, r0
	srawi r0, r0, 7
	stw r8, 0xa8(r1)
	srwi r5, r0, 31
	fadds f2, f2, f0
	add r0, r0, r5
	stw r8, 0xb0(r1)
	clrlwi r6, r0, 24
	lfs f0, float_0_8041a514(r2)
	stfs f2, 0x38(r1)
	lwz r0, 0x28(r28)
	lha r5, 0x8(r27)
	xoris r0, r0, 0x8000
	lha r7, 0xa(r27)
	stw r0, 0xc4(r1)
	xoris r0, r5, 0x8000
	xoris r5, r7, 0x8000
	lfd f2, 0xc0(r1)
	stw r0, 0xac(r1)
	fsubs f2, f2, f5
	lfd f3, 0xa8(r1)
	stw r5, 0xb4(r1)
	fsubs f3, f3, f5
	fadds f2, f29, f2
	lfd f4, 0xb0(r1)
	stfs f0, 0x40(r1)
	fadds f2, f3, f2
	fsubs f3, f4, f5
	fsubs f0, f2, f1
	fadds f0, f3, f0
	stfs f0, 0x3c(r1)
	lwz r0, 0x0(r27)
	lfs f1, 0x10(r27)
	clrlwi r5, r0, 16
	bl iconDispGxAlpha
	mr r3, r31
	bl FontDrawStart_alpha
	lwz r0, 0x2c(r1)
	addi r3, r1, 0x14
	stw r0, 0x14(r1)
	bl FontDrawColor
	b @7
	@22:
	lha r6, 0x8(r27)
	lis r0, 0x4330
	lwz r5, 0x28(r28)
	lis r4, double_to_int_802c4f08@ha
	stw r0, 0xc0(r1)
	add r0, r6, r5
	lfd f4, double_to_int_802c4f08@l(r4)
	xoris r0, r0, 0x8000
	lfs f2, float_32_8041a588(r2)
	stw r0, 0xc4(r1)
	lfs f1, 0x10(r27)
	lfd f3, 0xc0(r1)
	lfs f0, float_10_8041a538(r2)
	fsubs f3, f3, f4
	fmsubs f0, f2, f1, f0
	fcmpo cr0, f3, f0
	cror eq, gt, eq
	beq @7
	cmpwi r30, 0x0
	beq @23
	lwz r3, 0x7a4c(r28)
	lwz r4, dat_8041a4f0(r2)
	lwz r0, 0x8(r3)
	stw r4, 0x28(r1)
	cmpwi r0, 0x8
	bge @24
	cmpwi r0, 0x3
	beq @25
	b @26
	@24:
	cmpwi r0, 0xa
	bge @26
	@25:
	lwz r0, dat_8041a4f4(r2)
	stw r0, 0x28(r1)
	@26:
	stb r24, 0x2b(r1)
	addi r4, r1, 0x10
	li r3, 0x1
	lwz r0, 0x28(r1)
	stw r0, 0x10(r1)
	bl GXSetTevColor
	lfs f1, 0x10(r27)
	bl FontDrawScale
	fmr f1, f31
	lhz r3, 0x4(r27)
	fmr f2, f30
	bl FontDrawCode
	bl FontDrawColor_
	b @7
	@23:
	lwz r4, 0x0(r27)
	clrlwi. r0, r4, 31
	beq @27
	bl kanjiGetWidth
	lwz r0, 0x0(r27)
	fmr f26, f31
	fmr f27, f30
	extrwi r30, r3, 15, 16
	rlwinm. r0, r0, 0, 30, 30
	beq @28
	li r3, 0x2710
	bl irand
	lis r4, 0x5555
	lis r0, 0x4330
	addi r5, r4, 0x5556
	stw r0, 0xc0(r1)
	mulhw r5, r5, r3
	lis r4, double_to_int_802c4f08@ha
	lfd f1, double_to_int_802c4f08@l(r4)
	srwi r0, r5, 31
	add r0, r5, r0
	mulli r0, r0, 0x3
	subf r0, r0, r3
	li r3, 0x2710
	xoris r0, r0, 0x8000
	stw r0, 0xc4(r1)
	lfd f0, 0xc0(r1)
	fsubs f0, f0, f1
	fadds f26, f31, f0
	bl irand
	lis r4, 0x5555
	lis r0, 0x4330
	addi r5, r4, 0x5556
	stw r0, 0xb8(r1)
	mulhw r5, r5, r3
	lis r4, double_to_int_802c4f08@ha
	lfd f1, double_to_int_802c4f08@l(r4)
	srwi r0, r5, 31
	add r0, r5, r0
	mulli r0, r0, 0x3
	subf r0, r0, r3
	xoris r0, r0, 0x8000
	stw r0, 0xbc(r1)
	lfd f0, 0xb8(r1)
	fsubs f0, f0, f1
	fadds f27, f30, f0
	@28:
	neg r3, r30
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802c4f08@ha
	stw r3, 0xc4(r1)
	addi r3, r1, 0x44
	lfd f1, double_to_int_802c4f08@l(r4)
	stw r0, 0xc0(r1)
	lfs f2, float_12_8041a68c(r2)
	lfd f0, 0xc0(r1)
	lfs f3, float_0_8041a514(r2)
	fsubs f1, f0, f1
	bl PSMTXTrans
	lfs f1, 0x14(r27)
	addi r3, r1, 0x44
	mr r4, r3
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScaleApply
	lis r0, 0x4330
	lis r3, double_to_int_mask_802c4f10@ha
	stw r30, 0xbc(r1)
	addi r4, r3, double_to_int_mask_802c4f10@l
	addi r3, r1, 0x44
	lfd f1, 0x0(r4)
	stw r0, 0xb8(r1)
	mr r4, r3
	lfs f2, float_neg12_8041a690(r2)
	lfd f0, 0xb8(r1)
	lfs f3, float_0_8041a514(r2)
	fsubs f1, f0, f1
	bl PSMTXTransApply
	lfs f1, 0x10(r27)
	addi r3, r1, 0x44
	mr r4, r3
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScaleApply
	fmr f1, f26
	addi r3, r1, 0x44
	fmr f2, f27
	lfs f3, float_0_8041a514(r2)
	mr r4, r3
	bl PSMTXTransApply
	lhz r4, 0x4(r27)
	addi r3, r1, 0x44
	bl FontDrawCodeMtx
	lfs f0, 0x14(r27)
	lfs f1, float_1_8041a52c(r2)
	lfs f2, float_0p5_8041a534(r2)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x14(r27)
	b @7
	@27:
	rlwinm. r0, r4, 0, 30, 30
	beq @29
	li r3, 0x2710
	bl irand
	lis r4, 0x5555
	lis r0, 0x4330
	addi r5, r4, 0x5556
	stw r0, 0xc0(r1)
	mulhw r5, r5, r3
	lis r4, double_to_int_802c4f08@ha
	lfd f1, double_to_int_802c4f08@l(r4)
	srwi r0, r5, 31
	add r0, r5, r0
	mulli r0, r0, 0x3
	subf r0, r0, r3
	li r3, 0x2710
	xoris r0, r0, 0x8000
	stw r0, 0xc4(r1)
	lfd f0, 0xc0(r1)
	fsubs f0, f0, f1
	fadds f26, f31, f0
	bl irand
	lis r4, 0x5555
	lis r0, 0x4330
	addi r5, r4, 0x5556
	stw r0, 0xb8(r1)
	mulhw r5, r5, r3
	lis r4, double_to_int_802c4f08@ha
	lfd f2, double_to_int_802c4f08@l(r4)
	lfs f1, 0x10(r27)
	srwi r0, r5, 31
	add r0, r5, r0
	mulli r0, r0, 0x3
	subf r0, r0, r3
	xoris r0, r0, 0x8000
	stw r0, 0xbc(r1)
	lfd f0, 0xb8(r1)
	fsubs f0, f0, f2
	fadds f27, f30, f0
	bl FontDrawScale
	fmr f1, f26
	lhz r3, 0x4(r27)
	fmr f2, f27
	bl FontDrawCode
	b @7
	@29:
	rlwinm. r0, r4, 0, 29, 29
	beq @30
	lis r3, 0x8000
	lwz r6, gp(r13)
	lwz r0, 0xf8(r3)
	lis r3, 0x1062
	lwz r5, 0x3c(r6)
	addi r3, r3, 0x4dd3
	srwi r0, r0, 2
	lwz r4, 0x1c(r28)
	mulhwu r0, r3, r0
	lwz r6, 0x38(r6)
	subfc r4, r4, r5
	lwz r3, 0x18(r28)
	li r5, 0x0
	subfe r3, r3, r6
	srwi r6, r0, 6
	bl __div2i
	bl __cvt_sll_flt
	lfs f0, float_0p02_8041a698(r2)
	lfs f2, float_0p01_8041a694(r2)
	fmuls f0, f0, f31
	fmsubs f26, f2, f1, f0
	fmr f1, f26
	bl cos
	frsp f27, f1
	fmr f1, f26
	bl sin
	frsp f26, f1
	lfs f1, 0x10(r27)
	bl FontDrawScale
	lfs f0, float_3p2_8041a69c(r2)
	lhz r3, 0x4(r27)
	fmadds f1, f0, f27, f31
	fnmsubs f2, f0, f26, f30
	bl FontDrawCode
	b @7
	@30:
	lbz r0, 0x7a43(r28)
	li r3, 0x100
	extsb r0, r0
	slw r0, r3, r0
	and. r0, r4, r0
	beq @31
	lis r3, 0x8000
	lwz r6, gp(r13)
	lwz r0, 0xf8(r3)
	lis r3, 0x1062
	lwz r5, 0x3c(r6)
	addi r3, r3, 0x4dd3
	srwi r0, r0, 2
	lwz r4, 0x1c(r28)
	mulhwu r0, r3, r0
	lwz r6, 0x38(r6)
	subfc r4, r4, r5
	lwz r3, 0x18(r28)
	li r5, 0x0
	subfe r3, r3, r6
	srwi r6, r0, 6
	bl __div2i
	bl __cvt_sll_flt
	lfs f0, float_0p02_8041a698(r2)
	lfs f2, float_0p01_8041a694(r2)
	fmuls f0, f0, f31
	fmsubs f26, f2, f1, f0
	fmr f1, f26
	bl cos
	frsp f2, f1
	lfs f0, float_3p2_8041a69c(r2)
	fmr f1, f26
	fmadds f26, f0, f2, f31
	bl sin
	frsp f2, f1
	lfs f0, float_3p2_8041a69c(r2)
	lfs f1, 0x10(r27)
	fnmsubs f27, f0, f2, f30
	bl FontDrawScale
	lwz r0, dat_8041a4f8(r2)
	addi r3, r1, 0xc
	stw r0, 0xc(r1)
	bl FontDrawColor
	fmr f1, f26
	lhz r3, 0x4(r27)
	fmr f2, f27
	bl FontDrawCode
	bl FontDrawEdge
	bl FontDrawRainbowColor
	lwz r0, dat_8041a4fc(r2)
	addi r3, r1, 0x8
	stw r0, 0x8(r1)
	bl FontDrawColor
	lfs f0, float_4_8041a67c(r2)
	lhz r3, 0x4(r27)
	fsubs f1, f26, f0
	fadds f2, f0, f27
	bl FontDrawCode
	bl FontDrawEdgeOff
	bl FontDrawRainbowColorOff
	li r3, 0x0
	bl FontDrawColorIDX
	b @7
	@31:
	bl FontDrawScale
	fmr f1, f31
	lhz r3, 0x4(r27)
	fmr f2, f30
	bl FontDrawCode
	@7:
	addi r26, r26, 0x1
	addi r27, r27, 0x18
	@1:
	lwz r0, 0x10(r28)
	cmpw r26, r0
	blt @2
	mr r3, r25
	@5:
	psq_l f31, 0x148(r1), 0, 0
	lfd f31, 0x140(r1)
	psq_l f30, 0x138(r1), 0, 0
	lfd f30, 0x130(r1)
	psq_l f29, 0x128(r1), 0, 0
	lfd f29, 0x120(r1)
	psq_l f28, 0x118(r1), 0, 0
	lfd f28, 0x110(r1)
	psq_l f27, 0x108(r1), 0, 0
	lfd f27, 0x100(r1)
	psq_l f26, 0xf8(r1), 0, 0
	lfd f26, 0xf0(r1)
	lmw r24, 0xd0(r1)
	lwz r0, 0x154(r1)
	mtlr r0
	addi r1, r1, 0x150
	blr
}

asm s32 msgMain(smartEntry* smart) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	li r0, 0x0
	stmw r27, 0x1c(r1)
	mr r30, r3
	lwz r31, 0x0(r3)
	stw r0, msgSEflag(r13)
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 30, 30
	beq @1
	lwz r12, 0x79fc(r31)
	cmplwi r12, 0x0
	beq @2
	mr r4, r30
	li r3, 0x0
	mtctr r12
	bctrl
	@2:
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x4(r31)
	lwz r6, 0x0(r30)
	lwz r0, 0x4(r6)
	rlwinm. r0, r0, 0, 22, 22
	bne @1
	lwz r0, 0x7840(r6)
	cmpwi r0, 0x6e
	bge @1
	cmpwi r0, 0x0
	beq @3
	slwi r0, r0, 2
	add r3, r6, r0
	lwz r0, 0x7840(r3)
	cmpwi r0, 0x0
	beq @1
	@3:
	lwz r4, 0x7840(r6)
	li r5, 0x0
	addi r3, r4, 0x1
	slwi r0, r4, 2
	stw r3, 0x7840(r6)
	add r3, r6, r0
	stw r5, 0x7844(r3)
	@1:
	lwz r3, 0x24(r31)
	lwz r0, 0x28(r31)
	cmpw r3, r0
	ble @4
	lis r3, 0x8000
	lwz r6, gp(r13)
	lwz r0, 0xf8(r3)
	lis r3, 0x1062
	lwz r5, 0x3c(r6)
	addi r3, r3, 0x4dd3
	srwi r0, r0, 2
	lwz r4, 0x34(r31)
	mulhwu r0, r3, r0
	lwz r6, 0x38(r6)
	subfc r4, r4, r5
	lwz r3, 0x30(r31)
	li r5, 0x0
	subfe r3, r3, r6
	srwi r6, r0, 6
	bl __div2i
	bl __cvt_sll_flt
	lwz r4, 0x28(r31)
	lis r0, 0x4330
	stw r0, 0x8(r1)
	lis r3, double_to_int_802c4f08@ha
	xoris r0, r4, 0x8000
	lfd f2, double_to_int_802c4f08@l(r3)
	stw r0, 0xc(r1)
	lfs f3, float_0p36_8041a6a0(r2)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f2
	fmadds f0, f3, f1, f0
	fctiwz f0, f0
	stfd f0, 0x10(r1)
	lwz r0, 0x14(r1)
	stw r0, 0x28(r31)
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 24, 24
	bne @5
	lwz r3, 0x0(r30)
	li r28, 0x100
	lwz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 23, 23
	beq @6
	li r28, 0x500
	@6:
	li r3, 0x0
	bl keyGetButtonTrg
	ori r0, r28, 0x200
	and. r0, r3, r0
	beq @5
	lwz r0, 0x4(r31)
	ori r0, r0, 0x4
	stw r0, 0x4(r31)
	@5:
	lwz r3, 0x4(r31)
	rlwinm. r0, r3, 0, 27, 27
	bne @7
	rlwinm. r0, r3, 0, 29, 29
	beq @7
	lis r3, 0x8000
	lwz r6, gp(r13)
	lwz r0, 0xf8(r3)
	lis r3, 0x1062
	lwz r5, 0x3c(r6)
	addi r3, r3, 0x4dd3
	srwi r0, r0, 2
	lwz r4, 0x34(r31)
	mulhwu r0, r3, r0
	lwz r6, 0x38(r6)
	subfc r4, r4, r5
	lwz r3, 0x30(r31)
	li r5, 0x0
	subfe r3, r3, r6
	srwi r6, r0, 6
	bl __div2i
	bl __cvt_sll_flt
	lwz r4, 0x28(r31)
	lis r0, 0x4330
	stw r0, 0x10(r1)
	lis r3, double_to_int_802c4f08@ha
	xoris r0, r4, 0x8000
	lfd f2, double_to_int_802c4f08@l(r3)
	stw r0, 0x14(r1)
	lfs f3, float_0p36_8041a6a0(r2)
	lfd f0, 0x10(r1)
	fsubs f0, f0, f2
	fmadds f0, f3, f1, f0
	fctiwz f0, f0
	stfd f0, 0x8(r1)
	lwz r0, 0xc(r1)
	stw r0, 0x28(r31)
	@7:
	lwz r3, 0x24(r31)
	lwz r0, 0x28(r31)
	cmpw r3, r0
	bge @8
	stw r3, 0x28(r31)
	@8:
	lwz r4, gp(r13)
	li r3, 0x3
	lwz r0, 0x38(r4)
	lwz r4, 0x3c(r4)
	stw r4, 0x34(r31)
	stw r0, 0x30(r31)
	b @9
	@4:
	lhz r0, 0xa(r31)
	cmpwi r0, 0x2
	beq @10
	bge @11
	cmpwi r0, 0x1
	bge @12
	b @11
	@12:
	li r3, 0x2
	b @9
	@10:
	li r0, 0x1
	lis r3, 0x2
	sth r0, 0xc(r31)
	li r0, 0x0
	addi r3, r3, 0x3d
	lhz r4, 0x8(r31)
	addi r4, r4, 0x1
	sth r4, 0x8(r31)
	sth r0, 0xa(r31)
	bl psndSFXOn
	lwz r3, 0x20(r31)
	addi r0, r3, 0x64
	stw r0, 0x20(r31)
	lwz r12, 0x79fc(r31)
	cmplwi r12, 0x0
	beq @13
	mr r4, r30
	li r3, 0x3
	mtctr r12
	bctrl
	b @13
	@11:
	lis r3, 0x8000
	lwz r6, gp(r13)
	lwz r0, 0xf8(r3)
	lis r3, 0x1062
	lwz r5, 0x3c(r6)
	addi r3, r3, 0x4dd3
	srwi r0, r0, 2
	lwz r4, 0x34(r31)
	mulhwu r0, r3, r0
	lwz r6, 0x38(r6)
	subfc r4, r4, r5
	lwz r3, 0x30(r31)
	li r5, 0x0
	subfe r3, r3, r6
	srwi r6, r0, 6
	bl __div2i
	lwz r0, 0x4(r31)
	mr r29, r4
	rlwinm. r0, r0, 0, 24, 24
	bne @14
	lwz r3, 0x0(r30)
	li r28, 0x100
	lwz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 23, 23
	beq @15
	li r28, 0x500
	@15:
	li r3, 0x0
	bl keyGetButtonTrg
	ori r0, r28, 0x200
	and. r0, r3, r0
	beq @14
	lwz r0, 0x4(r31)
	ori r0, r0, 0x4
	stw r0, 0x4(r31)
	@14:
	lwz r3, 0x4(r31)
	rlwinm. r0, r3, 0, 27, 27
	bne @16
	rlwinm. r0, r3, 0, 29, 29
	beq @16
	mulli r29, r29, 0x64
	@16:
	lwz r0, 0x20(r31)
	add r0, r0, r29
	stw r0, 0x20(r31)
	@13:
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x34(r31)
	stw r0, 0x30(r31)
	lwz r0, 0x10(r31)
	mulli r3, r0, 0x18
	mr r28, r0
	addi r29, r3, 0x3c
	add r29, r31, r29
	b @17
	@18:
	lwz r3, 0xc(r29)
	lwz r0, 0x20(r31)
	cmplw r3, r0
	bgt @19
	lhz r3, 0x4(r29)
	subis r4, r3, 0x1
	addi r4, r4, 0xe
	cmplwi r4, 0xd
	bgt @20
	lis r3, jumptable_8030DC00@ha
	slwi r4, r4, 2
	addi r3, r3, jumptable_8030DC00@l
	lwzx r0, r3, r4
	mtctr r0
	bctr
	@21:
	lwz r12, 0x79fc(r31)
	cmplwi r12, 0x0
	beq @22
	mr r4, r30
	li r3, 0x1
	mtctr r12
	bctrl
	@22:
	stw r28, 0x10(r31)
	li r3, 0x0
	b @9
	@23:
	lha r3, 0x6(r29)
	lhz r0, 0x8(r31)
	cmpw r3, r0
	bne @24
	li r0, 0x1
	sth r0, 0xa(r31)
	lwz r0, 0xc(r29)
	stw r0, 0x20(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x4(r31)
	lwz r12, 0x79fc(r31)
	cmplwi r12, 0x0
	beq @24
	mr r4, r30
	li r3, 0x2
	mtctr r12
	bctrl
	b @24
	@25:
	lha r3, 0x8(r29)
	lwz r0, 0x24(r31)
	subf r0, r3, r0
	stw r0, 0x24(r31)
	lwz r0, 0xc(r29)
	stw r0, 0x20(r31)
	lwz r4, 0x0(r30)
	lwz r5, 0x24(r31)
	lwz r0, 0x4(r4)
	rlwinm. r0, r0, 0, 22, 22
	bne @24
	lwz r0, 0x7840(r4)
	cmpwi r0, 0x6e
	bge @24
	cmpwi r0, 0x0
	beq @26
	slwi r3, r0, 2
	addi r0, r3, 0x7840
	lwzx r0, r4, r0
	cmpw r0, r5
	beq @24
	@26:
	lwz r3, 0x7840(r4)
	addi r0, r3, 0x1
	slwi r3, r3, 2
	stw r0, 0x7840(r4)
	addi r0, r3, 0x7844
	stwx r5, r4, r0
	b @24
	@27:
	addi r0, r28, 0x1
	li r3, 0x1
	stw r0, 0x10(r31)
	lwz r0, 0xc(r29)
	stw r0, 0x20(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x4(r31)
	b @9
	@28:
	lwz r12, 0x79fc(r31)
	cmplwi r12, 0x0
	beq @24
	mr r4, r30
	li r3, 0x4
	mtctr r12
	bctrl
	b @24
	@29:
	lwz r0, 0x0(r29)
	stw r0, 0x7a28(r31)
	b @24
	@30:
	lwz r0, 0x0(r29)
	stb r0, 0x7a2c(r31)
	b @24
	@31:
	lwz r0, 0x0(r29)
	cmplwi r0, 0x0
	beq @32
	lwz r0, 0x4(r31)
	ori r0, r0, 0x80
	stw r0, 0x4(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x4(r31)
	lwz r0, 0xc(r29)
	stw r0, 0x20(r31)
	b @24
	@32:
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x4(r31)
	b @24
	@33:
	lwz r27, 0x0(r29)
	cmplwi r27, 0x0
	bne @34
	addi r3, r31, 0x7a04
	bl npcNameToPtr
	mr r27, r3
	@34:
	lis r4, str_802C4FE4@ha
	lwz r3, 0x104(r27)
	addi r4, r4, str_802C4FE4@l
	li r5, 0x1
	bl animPoseSetPaperAnimGroup
	lwz r3, 0x104(r27)
	bl animPosePaperPeraOn
	lwz r0, 0xc(r29)
	la r4, paperPoseTbl(r13)
	lwz r3, 0x104(r27)
	li r5, 0x1
	slwi r0, r0, 2
	lwzx r4, r4, r0
	bl animPoseSetPaperAnim
	b @24
	@35:
	lhz r0, 0xa(r31)
	lwz r3, 0x0(r29)
	cmplwi r0, 0x0
	beq @36
	subi r28, r28, 0x1
	b @24
	@36:
	cmplwi r3, 0x0
	bne @37
	addi r3, r31, 0x7a04
	bl npcNameToPtr
	@37:
	lwz r3, 0x104(r3)
	li r4, 0x0
	li r5, 0x1
	bl animPoseSetPaperAnimGroup
	b @24
	@20:
	lwz r12, 0x79fc(r31)
	cmplwi r12, 0x0
	beq @38
	mr r4, r30
	li r3, 0x5
	mtctr r12
	bctrl
	@38:
	lwz r3, 0x0(r29)
	rlwinm. r0, r3, 0, 27, 27
	beq @39
	lwz r4, 0x0(r30)
	lwz r3, 0x7a4c(r4)
	lwz r0, 0x8(r3)
	cmpwi r0, 0x1
	beq @24
	lwz r0, msgSEflag(r13)
	cmpwi r0, 0x0
	bne @24
	lis r3, 0x2
	lbz r4, 0x7a2c(r4)
	addi r3, r3, 0x44
	bl psndSFXOnVol
	li r0, 0x1
	stw r0, msgSEflag(r13)
	b @24
	@39:
	rlwinm. r0, r3, 0, 28, 28
	beq @24
	lwz r4, 0x0(r30)
	lwz r3, 0x7a4c(r4)
	lwz r0, 0x8(r3)
	cmpwi r0, 0x3
	beq @40
	li r0, 0xf
	stw r0, 0x7a50(r4)
	@40:
	lwz r4, 0x0(r30)
	lwz r3, 0x7a4c(r4)
	lwz r0, 0x8(r3)
	cmpwi r0, 0x1
	beq @24
	lwz r0, msgSEflag(r13)
	cmpwi r0, 0x0
	bne @24
	lis r3, 0x2
	lbz r4, 0x7a2c(r4)
	addi r3, r3, 0x44
	bl psndSFXOnVol
	li r0, 0x1
	stw r0, msgSEflag(r13)
	@24:
	addi r28, r28, 0x1
	addi r29, r29, 0x18
	@17:
	cmpwi r28, 0x500
	blt @18
	@19:
	stw r28, 0x10(r31)
	lhz r0, 0xa(r31)
	cmplwi r0, 0x0
	beq @41
	li r3, 0x2
	b @9
	@41:
	li r3, 0x3
	@9:
	lmw r27, 0x1c(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".sdata") u32 gap_07_804103F4_sdata[1] = {0};
