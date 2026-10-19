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
__declspec(section ".sdata2") u32 unk_80422fe4;
__declspec(section ".sdata2") u32 unk_80422fe0;
#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
extern const char str_8041A4B0[8];
extern const char str_8041A4B8[8];
extern const char str_8041A4C0[8];
extern const char str_8041A4C8[8];
extern const char str_8041A4D0[4];
extern const char str_8041A4D4[8];
extern const char str_8041A4DC[8];
extern const char str_8041A4E4[4];
extern const char str_8041A4E8[8];
extern const u32 dat_8041a4f0;
extern const u32 dat_8041a4f4;
extern const u32 dat_8041a4f8;
extern const u32 dat_8041a4fc;
extern const u32 dat_8041a500;
extern const u32 dat_8041a504;
extern const u32 dat_8041a508;
extern const u32 dat_8041a50c;
extern const u32 dat_8041a510;
extern const f32 float_0_8041a514;
extern const f32 float_30_8041a518;
extern const f32 float_40_8041a51c;
extern const f32 float_25_8041a520;
extern const f32 float_2_8041a524;
extern const f32 float_0p3_8041a528;
extern const f32 float_1_8041a52c;
extern const f32 float_400_8041a530;
extern const f32 float_0p5_8041a534;
extern const f32 float_10_8041a538;
extern const f32 float_240_8041a53c;
extern const f32 float_36_8041a540;
extern const f32 float_62_8041a544;
extern const f32 float_80_8041a548;
extern const f32 float_60_8041a54c;
extern const f32 float_28_8041a550;
extern const f32 float_6_8041a554;
extern const f32 float_8_8041a558;
extern const f32 float_50_8041a55c;
extern const f32 float_52_8041a560;
extern const f32 float_31_8041a564;
extern const f32 float_180_8041a568;
extern const f32 float_5_8041a56c;
extern const f32 float_0p6_8041a570;
extern const f32 float_neg280_8041a574;
extern const f32 float_225_8041a578;
extern const f32 float_560_8041a57c;
extern const f32 float_176_8041a580;
extern const f32 float_0p7_8041a584;
extern const f32 float_32_8041a588;
extern const char str_8041A58C[4];
extern const char str_8041A590[4];
extern const char str_8041A594[4];
extern const char str_8041A598[4];
extern const char str_8041A59C[4];
extern const char str_8041A5A0[8];
extern const char str_8041A5A8[8];
extern const char str_8041A5B0[4];
extern const char str_8041A5B4[8];
extern const char str_8041A5BC[4];
extern const char str_8041A5C0[8];
extern const char str_8041A5C8[8];
extern const char str_8041A5D0[8];
extern const char str_8041A5D8[8];
extern const char str_8041A5E0[4];
extern const char str_8041A5E4[4];
extern const char str_8041A5E8[8];
extern const char str_8041A5F0[8];
extern const char str_8041A5F8[8];
extern const char str_8041A600[8];
extern const char str_8041A608[8];
extern const char str_8041A610[4];
extern const char str_8041A614[8];
extern const char str_8041A61C[8];
extern const char str_8041A624[8];
extern const char str_8041A62C[8];
extern const char str_8041A634[8];
extern const char str_8041A63C[8];
extern const char str_8041A644[4];
extern const char str_8041A648[4];
extern const char str_8041A64C[8];
extern const char str_8041A654[8];
extern const char str_8041A65C[8];
extern const char str_8041A664[8];
extern const char str_8041A66C[4];
extern const char str_8041A670[4];
extern const char str_8041A674[4];
extern const f32 float_0p55_8041a678;
extern const f32 float_4_8041a67c;
extern const f32 float_90_8041a680;
extern const f32 float_270_8041a684;
extern const f32 float_neg1_8041a688;
extern const f32 float_12_8041a68c;
extern const f32 float_neg12_8041a690;
extern const f32 float_0p01_8041a694;
extern const f32 float_0p02_8041a698;
extern const f32 float_3p2_8041a69c;
extern const f32 float_0p36_8041a6a0;
extern const char str_8041A6A4[8];
extern const u32 gap_09_8041A6AC_sdata2;
#endif
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
__declspec(section ".sdata") u16 g5_active_s772;

//.sdata
MessageWork* msgw = &msgWork;
const char* ErrMessage[2] = {R_no_messages_JP, R_no_messages_US};
__declspec(section ".sdata") const char* paperPoseTbl[6] = {
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

#ifdef NONMATCHING
static inline void msgAddPage(smartEntry* smart, s32 y) {
	MsgWinData* d = smart->address;
	if (!(d->flags & 0x200) && d->pageCount < 110) {
		if (d->pageCount == 0 || d->pageY[d->pageCount - 1] != y) {
			d->pageY[d->pageCount++] = y;
		}
	}
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
static inline void msgVoiceSE(smartEntry* smart) {
	MsgWinData* d = smart->address;
	if (d->window->type != 1 && !msgSEflag) {
		psndSFXOnVol((const char*)0x20044, d->sfxVolume);
		msgSEflag = 1;
	}
}
#endif

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
#else
void FontDrawColor(GXColor color);
void FontDrawStart_alpha(u8 alpha);
u16 GXGetTexObjHeight(const GXTexObj* to);
u16 GXGetTexObjWidth(const GXTexObj* to);
void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color);
void GXSetScissor(u32 left, u32 top, u32 wd, u32 ht);
void GXSetTevColor(GXTevRegID id, GXColor color);
void PSMTXIdentity(Mtx m);
void PSMTXScaleApply(const Mtx src, Mtx dst, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void PSMTXTransApply(const Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
int __cvt_fp2unsigned();
int __cvt_sll_flt();
int __div2i();
void* __memAlloc(HEAP_TYPE heap, u32 size);
void __memFree(HEAP_TYPE heap, void* ptr);
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
int hankakuSearch();
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
NpcEntry* npcNameToPtr(const char* name);
void psndSFXOn(const char* name);
smartEntry* smartAlloc(u32 size, u8 type);
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
void FontDrawCode(f32 x, f32 y, u16 code);
void FontDrawCodeMtx(Mtx mtx, u16 code);
void FontDrawColorIDX(s32 idx);
void FontDrawColor_(void);
void FontDrawEdge(void);
void FontDrawEdgeOff(void);
void FontDrawNoise(void);
void FontDrawNoiseOff(void);
void FontDrawRainbowColor(void);
void FontDrawRainbowColorOff(void);
void FontDrawScale(f32 scale);
GXColor FontGetDrawColor(void);
double cos(double);
void msgAnalize(smartEntry* smart, char* msg);
BOOL msgDisp(smartEntry* smart, u8 alpha, f32 x, f32 y);
double sin(double);
extern void* jumptable_8030DC00[];
extern void* jumptable_8030DBD0[];
extern void* jumptable_8030DBA0[];
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 msgMain(smartEntry* smart) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0x38000000
		opword 0xBF61001C
		opword 0x7C7E1B78
		opword 0x83E30000
		stw r0, msgSEflag(r13)
		opword 0x801F0004
		opword 0x540007BD
		opword 0x41820080
		opword 0x819F79FC
		opword 0x280C0000
		opword 0x41820014
		opword 0x7FC4F378
		opword 0x38600000
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x801F0004
		opword 0x540007FA
		opword 0x901F0004
		opword 0x80DE0000
		opword 0x80060004
		opword 0x540005AD
		opword 0x40820048
		opword 0x80067840
		opword 0x2C00006E
		opword 0x4080003C
		opword 0x2C000000
		opword 0x41820018
		opword 0x5400103A
		opword 0x7C660214
		opword 0x80037840
		opword 0x2C000000
		opword 0x41820020
		opword 0x80867840
		opword 0x38A00000
		opword 0x38640001
		opword 0x5480103A
		opword 0x90667840
		opword 0x7C660214
		opword 0x90A37844
		opword 0x807F0024
		opword 0x801F0028
		opword 0x7C030000
		opword 0x4081018C
		opword 0x3C608000
		lwz r6, gp(r13)
		opword 0x800300F8
		opword 0x3C601062
		opword 0x80A6003C
		opword 0x38634DD3
		opword 0x5400F0BE
		opword 0x809F0034
		opword 0x7C030016
		opword 0x80C60038
		opword 0x7C842810
		opword 0x807F0030
		opword 0x38A00000
		opword 0x7C633110
		opword 0x5406D1BE
		bl __div2i
		bl __cvt_sll_flt
		opword 0x809F0028
		opword 0x3C004330
		opword 0x90010008
		lis r3, double_to_int_802c4f08@ha
		opword 0x6C808000
		lfd f2, double_to_int_802c4f08@l(r3)
		opword 0x9001000C
		lfs f3, float_0p36_8041a6a0(r2)
		opword 0xC8010008
		opword 0xEC001028
		opword 0xEC03007A
		opword 0xFC00001E
		opword 0xD8010010
		opword 0x80010014
		opword 0x901F0028
		opword 0x801F0004
		opword 0x54000631
		opword 0x4082003C
		opword 0x807E0000
		opword 0x3B800100
		opword 0x80030004
		opword 0x540005EF
		opword 0x41820008
		opword 0x3B800500
		opword 0x38600000
		bl keyGetButtonTrg
		opword 0x63800200
		opword 0x7C600039
		opword 0x41820010
		opword 0x801F0004
		opword 0x60000004
		opword 0x901F0004
		opword 0x807F0004
		opword 0x546006F7
		opword 0x4082008C
		opword 0x5460077B
		opword 0x41820084
		opword 0x3C608000
		lwz r6, gp(r13)
		opword 0x800300F8
		opword 0x3C601062
		opword 0x80A6003C
		opword 0x38634DD3
		opword 0x5400F0BE
		opword 0x809F0034
		opword 0x7C030016
		opword 0x80C60038
		opword 0x7C842810
		opword 0x807F0030
		opword 0x38A00000
		opword 0x7C633110
		opword 0x5406D1BE
		bl __div2i
		bl __cvt_sll_flt
		opword 0x809F0028
		opword 0x3C004330
		opword 0x90010010
		lis r3, double_to_int_802c4f08@ha
		opword 0x6C808000
		lfd f2, double_to_int_802c4f08@l(r3)
		opword 0x90010014
		lfs f3, float_0p36_8041a6a0(r2)
		opword 0xC8010010
		opword 0xEC001028
		opword 0xEC03007A
		opword 0xFC00001E
		opword 0xD8010008
		opword 0x8001000C
		opword 0x901F0028
		opword 0x807F0024
		opword 0x801F0028
		opword 0x7C030000
		opword 0x40800008
		opword 0x907F0028
		lwz r4, gp(r13)
		opword 0x38600003
		opword 0x80040038
		opword 0x8084003C
		opword 0x909F0034
		opword 0x901F0030
		opword 0x4800048C
		opword 0xA01F000A
		opword 0x2C000002
		opword 0x4182001C
		opword 0x4080006C
		opword 0x2C000001
		opword 0x40800008
		opword 0x48000060
		opword 0x38600002
		opword 0x48000468
		opword 0x38000001
		opword 0x3C600002
		opword 0xB01F000C
		opword 0x38000000
		opword 0x3863003D
		opword 0xA09F0008
		opword 0x38840001
		opword 0xB09F0008
		opword 0xB01F000A
		bl psndSFXOn
		opword 0x807F0020
		opword 0x38030064
		opword 0x901F0020
		opword 0x819F79FC
		opword 0x280C0000
		opword 0x418200C4
		opword 0x7FC4F378
		opword 0x38600003
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x480000B0
		opword 0x3C608000
		lwz r6, gp(r13)
		opword 0x800300F8
		opword 0x3C601062
		opword 0x80A6003C
		opword 0x38634DD3
		opword 0x5400F0BE
		opword 0x809F0034
		opword 0x7C030016
		opword 0x80C60038
		opword 0x7C842810
		opword 0x807F0030
		opword 0x38A00000
		opword 0x7C633110
		opword 0x5406D1BE
		bl __div2i
		opword 0x801F0004
		opword 0x7C9D2378
		opword 0x54000631
		opword 0x4082003C
		opword 0x807E0000
		opword 0x3B800100
		opword 0x80030004
		opword 0x540005EF
		opword 0x41820008
		opword 0x3B800500
		opword 0x38600000
		bl keyGetButtonTrg
		opword 0x63800200
		opword 0x7C600039
		opword 0x41820010
		opword 0x801F0004
		opword 0x60000004
		opword 0x901F0004
		opword 0x807F0004
		opword 0x546006F7
		opword 0x40820010
		opword 0x5460077B
		opword 0x41820008
		opword 0x1FBD0064
		opword 0x801F0020
		opword 0x7C00EA14
		opword 0x901F0020
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F0034
		opword 0x901F0030
		opword 0x801F0010
		opword 0x1C600018
		opword 0x7C1C0378
		opword 0x3BA3003C
		opword 0x7FBFEA14
		opword 0x48000318
		opword 0x807D000C
		opword 0x801F0020
		opword 0x7C030040
		opword 0x41810310
		opword 0xA07D0004
		opword 0x3C83FFFF
		opword 0x3884000E
		opword 0x2804000D
		opword 0x4181022C
		lis r3, jumptable_8030DC00@ha
		opword 0x5484103A
		addi r3, r3, jumptable_8030DC00@l
		opword 0x7C03202E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x819F79FC
		opword 0x280C0000
		opword 0x41820014
		opword 0x7FC4F378
		opword 0x38600001
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x939F0010
		opword 0x38600000
		opword 0x480002D8
		opword 0xA87D0006
		opword 0xA01F0008
		opword 0x7C030000
		opword 0x4082029C
		opword 0x38000001
		opword 0xB01F000A
		opword 0x801D000C
		opword 0x901F0020
		opword 0x801F0004
		opword 0x540007B8
		opword 0x901F0004
		opword 0x819F79FC
		opword 0x280C0000
		opword 0x41820274
		opword 0x7FC4F378
		opword 0x38600002
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x48000260
		opword 0xA87D0008
		opword 0x801F0024
		opword 0x7C030050
		opword 0x901F0024
		opword 0x801D000C
		opword 0x901F0020
		opword 0x809E0000
		opword 0x80BF0024
		opword 0x80040004
		opword 0x540005AD
		opword 0x40820234
		opword 0x80047840
		opword 0x2C00006E
		opword 0x40800228
		opword 0x2C000000
		opword 0x41820018
		opword 0x5403103A
		opword 0x38037840
		opword 0x7C04002E
		opword 0x7C002800
		opword 0x4182020C
		opword 0x80647840
		opword 0x38030001
		opword 0x5463103A
		opword 0x90047840
		opword 0x38037844
		opword 0x7CA4012E
		opword 0x480001F0
		opword 0x381C0001
		opword 0x38600001
		opword 0x901F0010
		opword 0x801D000C
		opword 0x901F0020
		opword 0x801F0004
		opword 0x540007B8
		opword 0x901F0004
		opword 0x480001F8
		opword 0x819F79FC
		opword 0x280C0000
		opword 0x418201C0
		opword 0x7FC4F378
		opword 0x38600004
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x480001AC
		opword 0x801D0000
		opword 0x901F7A28
		opword 0x480001A0
		opword 0x801D0000
		opword 0x981F7A2C
		opword 0x48000194
		opword 0x801D0000
		opword 0x28000000
		opword 0x41820028
		opword 0x801F0004
		opword 0x60000080
		opword 0x901F0004
		opword 0x801F0004
		opword 0x540007B8
		opword 0x901F0004
		opword 0x801D000C
		opword 0x901F0020
		opword 0x48000164
		opword 0x801F0004
		opword 0x5400066E
		opword 0x901F0004
		opword 0x48000154
		opword 0x837D0000
		opword 0x281B0000
		opword 0x40820010
		opword 0x387F7A04
		bl npcNameToPtr
		opword 0x7C7B1B78
		lis r4, str_802C4FE4@ha
		opword 0x807B0104
		addi r4, r4, str_802C4FE4@l
		opword 0x38A00001
		bl animPoseSetPaperAnimGroup
		opword 0x807B0104
		bl animPosePaperPeraOn
		opword 0x801D000C
		la r4, paperPoseTbl(r13)
		opword 0x807B0104
		opword 0x38A00001
		opword 0x5400103A
		opword 0x7C84002E
		bl animPoseSetPaperAnim
		opword 0x48000100
		opword 0xA01F000A
		opword 0x807D0000
		opword 0x28000000
		opword 0x4182000C
		opword 0x3B9CFFFF
		opword 0x480000E8
		opword 0x28030000
		opword 0x4082000C
		opword 0x387F7A04
		bl npcNameToPtr
		opword 0x80630104
		opword 0x38800000
		opword 0x38A00001
		bl animPoseSetPaperAnimGroup
		opword 0x480000C4
		opword 0x819F79FC
		opword 0x280C0000
		opword 0x41820014
		opword 0x7FC4F378
		opword 0x38600005
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x807D0000
		opword 0x546006F7
		opword 0x41820040
		opword 0x809E0000
		opword 0x80647A4C
		opword 0x80030008
		opword 0x2C000001
		opword 0x41820088
		lwz r0, msgSEflag(r13)
		opword 0x2C000000
		opword 0x4082007C
		opword 0x3C600002
		opword 0x88847A2C
		opword 0x38630044
		bl psndSFXOnVol
		opword 0x38000001
		stw r0, msgSEflag(r13)
		opword 0x48000060
		opword 0x54600739
		opword 0x41820058
		opword 0x809E0000
		opword 0x80647A4C
		opword 0x80030008
		opword 0x2C000003
		opword 0x4182000C
		opword 0x3800000F
		opword 0x90047A50
		opword 0x809E0000
		opword 0x80647A4C
		opword 0x80030008
		opword 0x2C000001
		opword 0x41820028
		lwz r0, msgSEflag(r13)
		opword 0x2C000000
		opword 0x4082001C
		opword 0x3C600002
		opword 0x88847A2C
		opword 0x38630044
		bl psndSFXOnVol
		opword 0x38000001
		stw r0, msgSEflag(r13)
		opword 0x3B9C0001
		opword 0x3BBD0018
		opword 0x2C1C0500
		opword 0x4180FCE8
		opword 0x939F0010
		opword 0xA01F000A
		opword 0x28000000
		opword 0x4182000C
		opword 0x38600002
		opword 0x48000008
		opword 0x38600003
		opword 0xBB61001C
		opword 0x80010034
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop
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
BOOL msgDisp(smartEntry* smart, u8 alpha, f32 x, f32 y);
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
				if (c->rot >= EXT_LIT(float_90_8041a680, 90.0f) && c->rot <= EXT_LIT(float_270_8041a684, 270.0f)) {
					PSMTXScaleApply(m, m, 1.0f, 1.0f, -1.0f);
				}
				PSMTXTransApply(m, m, x + c->x, c->y + (y + data->scrollPos) - 40.0f, EXT_LIT(float_0_8041a514, 0.0f));
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
					pos.x = EXT_LIT(float_28_8041a550, 20.0f) + (x + c->x);
					pos.y = c->iconY + (c->y + (y + data->scrollPos) - 40.0f);
					pos.z = EXT_LIT(float_0_8041a514, 0.0f);
					iconDispGxAlpha(&pos, 0x10, (u16)c->value, a * al / 255, c->scale);
					FontDrawStart_alpha(alpha);
					FontDrawColor(col4);
					break;
				}
				if ((f32)(c->y + data->scrollPos) >= EXT_LIT(float_32_8041a588, 32.0f) * c->scale - 10.0f) {
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
					PSMTXTrans(m2, -w, EXT_LIT(float_12_8041a68c, 12.0f), EXT_LIT(float_0_8041a514, 0.0f));
					PSMTXScaleApply(m2, m2, c->rot, c->rot, c->rot);
					PSMTXTransApply(m2, m2, (u32)w, EXT_LIT(float_neg12_8041a690, -12.0f), EXT_LIT(float_0_8041a514, 0.0f));
					PSMTXScaleApply(m2, m2, c->scale, c->scale, c->scale);
					PSMTXTransApply(m2, m2, hx, hy, EXT_LIT(float_0_8041a514, 0.0f));
					FontDrawCodeMtx(m2, c->glyph);
					c->rot = EXT_LIT(float_1_8041a52c, 1.0f) + EXT_LIT(float_0p5_8041a534, 0.5f) * (c->rot - 1.0f);
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
					FontDrawCode(sx + EXT_LIT(float_3p2_8041a69c, 3.2f) * hx, sy - 3.2f * hy, c->glyph);
				}
				else if (c->value & (0x100 << data->sel)) {
					f32 hx2;
					t = EXT_LIT(float_0p01_8041a694, 0.01f) * OSTicksToMilliseconds(gp->renderTime - data->time18) - 0.02f * sx;
					hx2 = sx + EXT_LIT(float_3p2_8041a69c, 3.2f) * (f32)cos(t);
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
					FontDrawCode(hx2 - 4.0f, EXT_LIT(float_4_8041a67c, 4.0f) + hy, c->glyph);
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
BOOL msgDisp(smartEntry* smart, u8 alpha, f32 x, f32 y) {
	asm volatile {
		opword 0x9421FEB0
		opword 0x7C0802A6
		opword 0x90010154
		opword 0xDBE10140
		opword 0xF3E10148
		opword 0xDBC10130
		opword 0xF3C10138
		opword 0xDBA10120
		opword 0xF3A10128
		opword 0xDB810110
		opword 0xF3810118
		opword 0xDB610100
		opword 0xF3610108
		opword 0xDB4100F0
		opword 0xF34100F8
		opword 0xBF0100D0
		opword 0x83830000
		opword 0xFF800890
		opword 0x7C9F2378
		opword 0xFFA01090
		opword 0x7FE3FB78
		opword 0x3B7C003C
		opword 0x3B200000
		bl FontDrawStart_alpha
		opword 0x57FD063E
		opword 0x3B400000
		opword 0x4800093C
		opword 0xA07B0004
		opword 0x3C83FFFF
		opword 0x3884000C
		opword 0x2804000B
		opword 0x4181016C
		lis r3, jumptable_8030DBD0@ha
		opword 0x5484103A
		addi r3, r3, jumptable_8030DBD0@l
		opword 0x7C03202E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x38600000
		opword 0x48000918
		opword 0xA07C0008
		opword 0xA81B0006
		opword 0x7C030000
		opword 0x408208F0
		opword 0x3B200001
		opword 0x480008E8
		opword 0x801B0000
		opword 0x38610024
		opword 0x90010024
		bl FontDrawColor
		opword 0x480008D4
		opword 0x801B0000
		opword 0x28000000
		opword 0x4182000C
		bl FontDrawNoise
		opword 0x480008C0
		bl FontDrawNoiseOff
		opword 0x480008B8
		bl FontGetDrawColor
		opword 0x90610034
		opword 0x38610074
		bl PSMTXIdentity
		opword 0xC03B0014
		lfs f0, float_90_8041a680(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082002C
		lfs f0, float_270_8041a684(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x4082001C
		lfs f1, float_1_8041a52c(r2)
		opword 0x38610074
		lfs f3, float_neg1_8041a688(r2)
		opword 0x7C641B78
		opword 0xFC400890
		bl PSMTXScaleApply
		opword 0x801C0028
		opword 0x3CA04330
		lis r4, double_to_int_802c4f08@ha
		opword 0xA8DB0006
		opword 0x6C008000
		opword 0xA87B0008
		opword 0x900100BC
		opword 0x6CC68000
		opword 0x6C608000
		lfd f5, double_to_int_802c4f08@l(r4)
		opword 0x90A100B8
		opword 0x38610074
		lfs f3, float_0_8041a514(r2)
		opword 0x7C641B78
		opword 0xC80100B8
		opword 0x900100B4
		opword 0xEC202828
		lfs f0, float_40_8041a51c(r2)
		opword 0x90A100B0
		opword 0xC84100B0
		opword 0xEC3D082A
		opword 0x90C100AC
		opword 0xEC422828
		opword 0x90A100A8
		opword 0xC88100A8
		opword 0xEC22082A
		opword 0xEC842828
		opword 0xEC410028
		opword 0xEC3C202A
		bl PSMTXTransApply
		opword 0x807B0000
		bl animPoseMain
		opword 0x807B0000
		opword 0x38810074
		opword 0xC03B0014
		opword 0x38A00002
		opword 0xC05B0010
		bl animPoseDrawMtx
		opword 0x7FE3FB78
		bl FontDrawStart_alpha
		opword 0x80010034
		opword 0x38610020
		opword 0x90010020
		bl FontDrawColor
		opword 0x480007B8
		opword 0x811C0028
		opword 0x3CA04330
		opword 0xA8FB0006
		lis r4, double_to_int_802c4f08@ha
		opword 0x6D038000
		opword 0xA81B0008
		opword 0x906100AC
		opword 0x6CE38000
		addi r6, r4, double_to_int_802c4f08@l
		opword 0x6C048000
		opword 0x90A100A8
		opword 0x3BC00000
		opword 0xC8660000
		opword 0x3B0000FF
		opword 0x906100BC
		opword 0xC80100A8
		opword 0x90A100B8
		opword 0xEC001828
		opword 0x807C0004
		opword 0xC82100B8
		opword 0x908100B4
		opword 0x54630673
		opword 0xEC411828
		opword 0x90A100B0
		opword 0xEC1D002A
		opword 0xC82100B0
		opword 0xEFFC102A
		opword 0xEC211828
		opword 0xEFC1002A
		opword 0x41820190
		opword 0x809C783C
		opword 0x5483103A
		opword 0x7C7C1A14
		opword 0x80C37844
		opword 0x7C083000
		opword 0x40820018
		opword 0x80637848
		opword 0x7C001A15
		opword 0x4081071C
		opword 0x3BC00001
		opword 0x48000164
		opword 0x408000B4
		opword 0x7CA03215
		opword 0x4081000C
		opword 0x3BC00001
		opword 0x48000150
		opword 0x7CA83050
		opword 0x2C050064
		opword 0x40810008
		opword 0x38A00064
		opword 0x20A50064
		opword 0x3CC051EC
		opword 0x1CE500FF
		opword 0x80BC7840
		opword 0x38C6851F
		opword 0x38A5FFFF
		opword 0x7CC63896
		opword 0x7C042800
		opword 0x7CC42E70
		opword 0x54850FFE
		opword 0x7C842A14
		opword 0x5498063E
		opword 0x41820018
		opword 0x80637848
		opword 0x7C001A15
		opword 0x408106B0
		opword 0x3BC00001
		opword 0x480000F8
		bl FontGetDrawColor
		opword 0x90610030
		opword 0x3C608081
		opword 0x38A38081
		opword 0x3881001C
		opword 0x88010033
		opword 0x38600001
		opword 0x7C00C1D6
		opword 0x7CA50096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010033
		opword 0x80010030
		opword 0x9001001C
		bl GXSetTevColor
		opword 0x480000B0
		opword 0x80A37848
		opword 0x7CA02A15
		opword 0x4081000C
		opword 0x3BC00001
		opword 0x4800009C
		opword 0x7CA64050
		opword 0x2C050064
		opword 0x40810008
		opword 0x38A00064
		opword 0x1CE500FF
		opword 0x3CC051EC
		opword 0x80BC7840
		opword 0x38C6851F
		opword 0x7CC63896
		opword 0x38A5FFFE
		opword 0x7C042800
		opword 0x7CC42E70
		opword 0x54850FFE
		opword 0x7C842A14
		opword 0x5498063E
		opword 0x41820018
		opword 0x8063784C
		opword 0x7C001A15
		opword 0x40810600
		opword 0x3BC00001
		opword 0x48000048
		bl FontGetDrawColor
		opword 0x90610030
		opword 0x3C608081
		opword 0x38A38081
		opword 0x38810018
		opword 0x88010033
		opword 0x38600001
		opword 0x7C00C1D6
		opword 0x7CA50096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010033
		opword 0x80010030
		opword 0x90010018
		bl GXSetTevColor
		opword 0xA07B0004
		opword 0x2803FFF8
		opword 0x40820104
		bl FontGetDrawColor
		opword 0xA89B0006
		opword 0x3D004330
		opword 0x5700063E
		lis r6, double_to_int_802c4f08@ha
		opword 0x6C858000
		opword 0x9061002C
		opword 0x7C00E9D6
		lfd f5, double_to_int_802c4f08@l(r6)
		opword 0x90A100BC
		opword 0x3C808081
		lfs f2, float_28_8041a550(r2)
		opword 0x38610038
		opword 0x38A48081
		opword 0x910100B8
		opword 0x7CA50096
		lfs f1, float_40_8041a51c(r2)
		opword 0xC80100B8
		opword 0x38800010
		opword 0x910100C0
		opword 0xEC002828
		opword 0xEC1C002A
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x910100A8
		opword 0x54050FFE
		opword 0xEC42002A
		opword 0x7C002A14
		opword 0x910100B0
		opword 0x5406063E
		lfs f0, float_0_8041a514(r2)
		opword 0xD0410038
		opword 0x801C0028
		opword 0xA8BB0008
		opword 0x6C008000
		opword 0xA8FB000A
		opword 0x900100C4
		opword 0x6CA08000
		opword 0x6CE58000
		opword 0xC84100C0
		opword 0x900100AC
		opword 0xEC422828
		opword 0xC86100A8
		opword 0x90A100B4
		opword 0xEC632828
		opword 0xEC5D102A
		opword 0xC88100B0
		opword 0xD0010040
		opword 0xEC43102A
		opword 0xEC642828
		opword 0xEC020828
		opword 0xEC03002A
		opword 0xD001003C
		opword 0x801B0000
		opword 0xC03B0010
		opword 0x5405043E
		bl iconDispGxAlpha
		opword 0x7FE3FB78
		bl FontDrawStart_alpha
		opword 0x8001002C
		opword 0x38610014
		opword 0x90010014
		bl FontDrawColor
		opword 0x480004A8
		opword 0xA8DB0008
		opword 0x3C004330
		opword 0x80BC0028
		lis r4, double_to_int_802c4f08@ha
		opword 0x900100C0
		opword 0x7C062A14
		lfd f4, double_to_int_802c4f08@l(r4)
		opword 0x6C008000
		lfs f2, float_32_8041a588(r2)
		opword 0x900100C4
		opword 0xC03B0010
		opword 0xC86100C0
		lfs f0, float_10_8041a538(r2)
		opword 0xEC632028
		opword 0xEC020078
		opword 0xFC030040
		opword 0x4C411382
		opword 0x41820460
		opword 0x2C1E0000
		opword 0x41820070
		opword 0x807C7A4C
		lwz r4, dat_8041a4f0(r2)
		opword 0x80030008
		opword 0x90810028
		opword 0x2C000008
		opword 0x40800010
		opword 0x2C000003
		opword 0x41820010
		opword 0x48000014
		opword 0x2C00000A
		opword 0x4080000C
		lwz r0, dat_8041a4f4(r2)
		opword 0x90010028
		opword 0x9B01002B
		opword 0x38810010
		opword 0x38600001
		opword 0x80010028
		opword 0x90010010
		bl GXSetTevColor
		opword 0xC03B0010
		bl FontDrawScale
		opword 0xFC20F890
		opword 0xA07B0004
		opword 0xFC40F090
		bl FontDrawCode
		bl FontDrawColor_
		opword 0x480003EC
		opword 0x809B0000
		opword 0x548007FF
		opword 0x41820188
		bl kanjiGetWidth
		opword 0x801B0000
		opword 0xFF40F890
		opword 0xFF60F090
		opword 0x547EFC7E
		opword 0x540007BD
		opword 0x41820094
		opword 0x38602710
		bl irand
		opword 0x3C805555
		opword 0x3C004330
		opword 0x38A45556
		opword 0x900100C0
		opword 0x7CA51896
		lis r4, double_to_int_802c4f08@ha
		lfd f1, double_to_int_802c4f08@l(r4)
		opword 0x54A00FFE
		opword 0x7C050214
		opword 0x1C000003
		opword 0x7C001850
		opword 0x38602710
		opword 0x6C008000
		opword 0x900100C4
		opword 0xC80100C0
		opword 0xEC000828
		opword 0xEF5F002A
		bl irand
		opword 0x3C805555
		opword 0x3C004330
		opword 0x38A45556
		opword 0x900100B8
		opword 0x7CA51896
		lis r4, double_to_int_802c4f08@ha
		lfd f1, double_to_int_802c4f08@l(r4)
		opword 0x54A00FFE
		opword 0x7C050214
		opword 0x1C000003
		opword 0x7C001850
		opword 0x6C008000
		opword 0x900100BC
		opword 0xC80100B8
		opword 0xEC000828
		opword 0xEF7E002A
		opword 0x7C7E00D0
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802c4f08@ha
		opword 0x906100C4
		opword 0x38610044
		lfd f1, double_to_int_802c4f08@l(r4)
		opword 0x900100C0
		lfs f2, float_12_8041a68c(r2)
		opword 0xC80100C0
		lfs f3, float_0_8041a514(r2)
		opword 0xEC200828
		bl PSMTXTrans
		opword 0xC03B0014
		opword 0x38610044
		opword 0x7C641B78
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScaleApply
		opword 0x3C004330
		lis r3, double_to_int_mask_802c4f10@ha
		opword 0x93C100BC
		addi r4, r3, double_to_int_mask_802c4f10@l
		opword 0x38610044
		opword 0xC8240000
		opword 0x900100B8
		opword 0x7C641B78
		lfs f2, float_neg12_8041a690(r2)
		opword 0xC80100B8
		lfs f3, float_0_8041a514(r2)
		opword 0xEC200828
		bl PSMTXTransApply
		opword 0xC03B0010
		opword 0x38610044
		opword 0x7C641B78
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScaleApply
		opword 0xFC20D090
		opword 0x38610044
		opword 0xFC40D890
		lfs f3, float_0_8041a514(r2)
		opword 0x7C641B78
		bl PSMTXTransApply
		opword 0xA09B0004
		opword 0x38610044
		bl FontDrawCodeMtx
		opword 0xC01B0014
		lfs f1, float_1_8041a52c(r2)
		lfs f2, float_0p5_8041a534(r2)
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01B0014
		opword 0x4800025C
		opword 0x548007BD
		opword 0x418200B0
		opword 0x38602710
		bl irand
		opword 0x3C805555
		opword 0x3C004330
		opword 0x38A45556
		opword 0x900100C0
		opword 0x7CA51896
		lis r4, double_to_int_802c4f08@ha
		lfd f1, double_to_int_802c4f08@l(r4)
		opword 0x54A00FFE
		opword 0x7C050214
		opword 0x1C000003
		opword 0x7C001850
		opword 0x38602710
		opword 0x6C008000
		opword 0x900100C4
		opword 0xC80100C0
		opword 0xEC000828
		opword 0xEF5F002A
		bl irand
		opword 0x3C805555
		opword 0x3C004330
		opword 0x38A45556
		opword 0x900100B8
		opword 0x7CA51896
		lis r4, double_to_int_802c4f08@ha
		lfd f2, double_to_int_802c4f08@l(r4)
		opword 0xC03B0010
		opword 0x54A00FFE
		opword 0x7C050214
		opword 0x1C000003
		opword 0x7C001850
		opword 0x6C008000
		opword 0x900100BC
		opword 0xC80100B8
		opword 0xEC001028
		opword 0xEF7E002A
		bl FontDrawScale
		opword 0xFC20D090
		opword 0xA07B0004
		opword 0xFC40D890
		bl FontDrawCode
		opword 0x480001A8
		opword 0x5480077B
		opword 0x41820090
		opword 0x3C608000
		lwz r6, gp(r13)
		opword 0x800300F8
		opword 0x3C601062
		opword 0x80A6003C
		opword 0x38634DD3
		opword 0x5400F0BE
		opword 0x809C001C
		opword 0x7C030016
		opword 0x80C60038
		opword 0x7C842810
		opword 0x807C0018
		opword 0x38A00000
		opword 0x7C633110
		opword 0x5406D1BE
		bl __div2i
		bl __cvt_sll_flt
		lfs f0, float_0p02_8041a698(r2)
		lfs f2, float_0p01_8041a694(r2)
		opword 0xEC0007F2
		opword 0xEF420078
		opword 0xFC20D090
		bl cos
		opword 0xFF600818
		opword 0xFC20D090
		bl sin
		opword 0xFF400818
		opword 0xC03B0010
		bl FontDrawScale
		lfs f0, float_3p2_8041a69c(r2)
		opword 0xA07B0004
		opword 0xEC20FEFA
		opword 0xEC40F6BC
		bl FontDrawCode
		opword 0x48000114
		opword 0x881C7A43
		opword 0x38600100
		opword 0x7C000774
		opword 0x7C600030
		opword 0x7C800039
		opword 0x418200E8
		opword 0x3C608000
		lwz r6, gp(r13)
		opword 0x800300F8
		opword 0x3C601062
		opword 0x80A6003C
		opword 0x38634DD3
		opword 0x5400F0BE
		opword 0x809C001C
		opword 0x7C030016
		opword 0x80C60038
		opword 0x7C842810
		opword 0x807C0018
		opword 0x38A00000
		opword 0x7C633110
		opword 0x5406D1BE
		bl __div2i
		bl __cvt_sll_flt
		lfs f0, float_0p02_8041a698(r2)
		lfs f2, float_0p01_8041a694(r2)
		opword 0xEC0007F2
		opword 0xEF420078
		opword 0xFC20D090
		bl cos
		opword 0xFC400818
		lfs f0, float_3p2_8041a69c(r2)
		opword 0xFC20D090
		opword 0xEF40F8BA
		bl sin
		opword 0xFC400818
		lfs f0, float_3p2_8041a69c(r2)
		opword 0xC03B0010
		opword 0xEF60F0BC
		bl FontDrawScale
		lwz r0, dat_8041a4f8(r2)
		opword 0x3861000C
		opword 0x9001000C
		bl FontDrawColor
		opword 0xFC20D090
		opword 0xA07B0004
		opword 0xFC40D890
		bl FontDrawCode
		bl FontDrawEdge
		bl FontDrawRainbowColor
		lwz r0, dat_8041a4fc(r2)
		opword 0x38610008
		opword 0x90010008
		bl FontDrawColor
		lfs f0, float_4_8041a67c(r2)
		opword 0xA07B0004
		opword 0xEC3A0028
		opword 0xEC40D82A
		bl FontDrawCode
		bl FontDrawEdgeOff
		bl FontDrawRainbowColorOff
		opword 0x38600000
		bl FontDrawColorIDX
		opword 0x48000018
		bl FontDrawScale
		opword 0xFC20F890
		opword 0xA07B0004
		opword 0xFC40F090
		bl FontDrawCode
		opword 0x3B5A0001
		opword 0x3B7B0018
		opword 0x801C0010
		opword 0x7C1A0000
		opword 0x4180F6C0
		opword 0x7F23CB78
		opword 0xE3E10148
		opword 0xCBE10140
		opword 0xE3C10138
		opword 0xCBC10130
		opword 0xE3A10128
		opword 0xCBA10120
		opword 0xE3810118
		opword 0xCB810110
		opword 0xE3610108
		opword 0xCB610100
		opword 0xE34100F8
		opword 0xCB4100F0
		opword 0xBB0100D0
		opword 0x80010154
		opword 0x7C0803A6
		opword 0x38210150
	}
}
#pragma pop
#endif
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
	maxScale = EXT_LIT(float_0_8041a514, 0.0f);
	scale = EXT_LIT(float_1_8041a52c, 1.0f);
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
			entry->y = y - (( s32)(EXT_LIT(float_10_8041a538, 10.0f) * scale) );
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
			if (EXT_LIT(float_0_8041a514, 0.0f) == maxScale) {
				maxScale = 1.0f;
			}
			y -= EXT_LIT(float_32_8041a588, 32.0f) * maxScale;
			s230 -= EXT_LIT(float_32_8041a588, 32.0f) * maxScale;
			msg++;
			entry++;
			time += step;
			data->count++;
			maxScale = EXT_LIT(float_0_8041a514, 0.0f);
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
					entry->x = (x + (( EXT_LIT(float_0p5_8041a534, 0.5f) * iw ) * iconScale) ) + i38;
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
					entry->y = y - (( s32)(EXT_LIT(float_10_8041a538, 10.0f) * scale) );
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
				entry->dyn = (i20 == 0) ? ( EXT_LIT(float_0_8041a514, 0.0f) ) : ( EXT_LIT(float_180_8041a568, 180.0f)) ;
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
					total += (s32)(EXT_LIT(float_0p55_8041a678, 0.55f) * (scale * (( f32)(width + 4) )));
					p += 2;
					j += 2;
				}
				rubyW = (u16)total; rubyW = rubyW - ( EXT_LIT(float_0p55_8041a678, 0.55f) * (EXT_LIT(float_4_8041a67c, 4.0f) * scale)) ;
				rubyX = (( ((f32)(rubyX + x) ) - ( EXT_LIT(float_4_8041a67c, 4.0f) * scale )) - ( (f32)rubyW) ) * EXT_LIT(float_0p5_8041a534, 0.5f);
				p = tag; p = p + i;
				for (k = 0; ( k - 1) < ( half- 1) ; k++) {
					glyph = kanjiSearch(*(( u16*)p) );
					width = kanjiGetWidth((u16)(glyph + 0));
					ww = EXT_LIT(float_0p55_8041a678, 0.55f) * (scale * (( f32)(width + 4) ));
					entry->glyph = glyph;
					entry->x = rubyX;
					s230 = y;
					entry->y = s230;
					entry->scale = EXT_LIT(float_0p55_8041a678, 0.55f) * scale;
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
			entry->y = y - (( s32)(EXT_LIT(float_10_8041a538, 10.0f) * scale) );
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void msgAnalize(smartEntry* smart, char* msg) {
	char _af_pad[552];
	asm volatile {
		opword 0x83C30000
		lis r3, R_no_messages_JP@ha
		lfs f0, float_1_8041a52c(r2)
		opword 0x7C952378
		opword 0x801E0038
		addi r18, r3, R_no_messages_JP@l
		opword 0x83BE7A4C
		opword 0x3AE00000
		opword 0x1C600018
		lfs f29, float_0_8041a514(r2)
		stfs f0, _af_pad+72(r1)
		opword 0x801D0008
		opword 0x3B83003C
		opword 0x7F9EE214
		opword 0x2C000000
		opword 0x4080000C
		opword 0x38000000
		opword 0x901D0008
		opword 0x38000000
		opword 0x831E7A30
		opword 0xB0010234
		opword 0xA81E7A38
		opword 0xAB7E7A34
		opword 0xB0010232
		opword 0xA81E7A3A
		opword 0xAB5E7A36
		opword 0xB0010230
		opword 0x801E7A3C
		opword 0x90010054
		opword 0x801D0008
		opword 0x2C000008
		opword 0x41820014
		opword 0x4080005C
		opword 0x2C000003
		opword 0x41820008
		opword 0x48000050
		opword 0x2C000008
		opword 0x41820020
		opword 0x40800024
		opword 0x2C000003
		opword 0x41820008
		opword 0x48000018
		lwz r0, dat_8041a500(r2)
		opword 0x901C0000
		opword 0x4800000C
		lwz r0, dat_8041a504(r2)
		opword 0x901C0000
		opword 0x3C600001
		opword 0x3803FFF7
		opword 0xB01C0004
		opword 0x931C000C
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x38030001
		opword 0x901E0038
		opword 0x88750000
		opword 0x5460063E
		opword 0x28000081
		opword 0x4180000C
		opword 0x2800009F
		opword 0x40810014
		opword 0x280000E0
		opword 0x41800014
		opword 0x280000FC
		opword 0x4181000C
		opword 0x38000001
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x41820108
		opword 0xA0750000
		bl kanjiSearch
		opword 0x7C6E1B78
		opword 0x5463043E
		bl kanjiGetWidth
		opword 0xC0410050
		opword 0x5463043E
		opword 0x38630004
		opword 0x3C004330
		opword 0xB1DC0004
		opword 0x6C638000
		lfs f1, float_10_8041a538(r2)
		opword 0xB37C0006
		opword 0xC8720118
		opword 0xC0010050
		opword 0x906101FC
		opword 0xEC010032
		opword 0x900101F8
		opword 0xFC00001E
		opword 0xC82101F8
		opword 0xEC211828
		opword 0xD8010208
		opword 0x8001020C
		opword 0xEC020072
		opword 0x7C00D050
		opword 0xB01C0008
		opword 0xFC20001E
		opword 0xC0010050
		opword 0xD8210200
		opword 0xD01C0010
		opword 0x80610204
		opword 0x92FC0000
		opword 0xA0150000
		opword 0x28008145
		opword 0x40820014
		opword 0x801C0000
		opword 0x60000010
		opword 0x901C0000
		opword 0x48000020
		opword 0x28008140
		opword 0x41820018
		opword 0x28008151
		opword 0x41820010
		opword 0x801C0000
		opword 0x60000008
		opword 0x901C0000
		opword 0x56E007FF
		opword 0x4182000C
		opword 0xC001004C
		opword 0xD01C0014
		opword 0xC0010050
		opword 0xFC1D0040
		opword 0x40800008
		opword 0xFFA00090
		opword 0x931C000C
		opword 0x7C1B1A14
		opword 0x7C1B0734
		opword 0x3AB50002
		opword 0x807E0038
		opword 0x3B9C0018
		opword 0x80810054
		opword 0x38030001
		opword 0x901E0038
		opword 0x7F182214
		opword 0x4BFFFEC4
		opword 0x7C600774
		opword 0x2C00000A
		opword 0x41820050
		opword 0x40800010
		opword 0x2C000000
		opword 0x41820014
		opword 0x48001158
		opword 0x2C00003C
		opword 0x41820110
		opword 0x4800114C
		opword 0x3C600001
		opword 0x3803FFFF
		opword 0xB01C0004
		opword 0xA8010232
		opword 0x931C000C
		opword 0x931E7A30
		opword 0xB37E7A34
		opword 0xB35E7A36
		opword 0xB01E7A38
		opword 0xA8010230
		opword 0xB01E7A3A
		opword 0x48001238
		opword 0x3C600001
		lfs f0, float_0_8041a514(r2)
		opword 0x3803FFFB
		opword 0x3B600000
		opword 0xB01C0004
		opword 0xFC00E800
		opword 0x931C000C
		opword 0x40820008
		lfs f29, float_1_8041a52c(r2)
		opword 0x7F430734
		opword 0x3C804330
		opword 0xA8010230
		opword 0x6C638000
		lfs f0, float_32_8041a588(r2)
		opword 0x3AB50001
		opword 0x9061020C
		opword 0x6C008000
		opword 0xEC600772
		opword 0xC8520118
		opword 0x90810208
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0xC8010208
		opword 0x900101FC
		opword 0x38030001
		opword 0xEC201028
		opword 0x80610054
		opword 0x908101F8
		lfs f29, float_0_8041a514(r2)
		opword 0x7F181A14
		opword 0xC80101F8
		opword 0xEC211828
		opword 0x901E0038
		opword 0xEC001028
		opword 0x801E0004
		opword 0xFC20081E
		opword 0xEC001828
		opword 0x540006B5
		opword 0xD8210200
		opword 0xFC00001E
		opword 0x83410204
		opword 0xD8010210
		opword 0x80010214
		opword 0xB0010230
		opword 0x4182FDB8
		opword 0x889E7A40
		opword 0x38A00100
		opword 0x56F7061E
		opword 0x7C830774
		opword 0x38040001
		opword 0x7CA31830
		opword 0x981E7A40
		opword 0x7EF71B78
		opword 0x4BFFFD94
		opword 0x38000080
		opword 0x38B50001
		opword 0x38810178
		opword 0x386100F8
		opword 0x38C00000
		opword 0x7C0903A6
		opword 0x88E50000
		opword 0x7CE00774
		opword 0x2C00003E
		opword 0x41820014
		opword 0x40800058
		opword 0x2C000020
		opword 0x4182002C
		opword 0x4800004C
		opword 0x2C060000
		opword 0x40820010
		opword 0x38000000
		opword 0x98040000
		opword 0x4800000C
		opword 0x38000000
		opword 0x98030000
		opword 0x39E50001
		opword 0x48000050
		opword 0x2C060000
		opword 0x40820014
		opword 0x38000000
		opword 0x38C00001
		opword 0x98040000
		opword 0x4800002C
		opword 0x98E30000
		opword 0x38630001
		opword 0x48000020
		opword 0x2C060000
		opword 0x40820010
		opword 0x98E40000
		opword 0x38840001
		opword 0x4800000C
		opword 0x98E30000
		opword 0x38630001
		opword 0x38A50001
		opword 0x4200FF78
		opword 0x39E00000
		opword 0x7DF57B78
		opword 0x38610178
		la r4, str_8041A58C(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x38610178
		la r4, str_8041A590(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820040
		opword 0x3C600001
		opword 0x3803FFFE
		opword 0xB01C0004
		opword 0xA8010232
		opword 0xB01C0006
		opword 0x931C000C
		opword 0x3B180064
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x38030001
		opword 0xA8610232
		opword 0x901E0038
		opword 0x38630001
		opword 0xB0610232
		opword 0x48000F20
		opword 0x38610178
		opword 0x38920128
		bl strcmp
		opword 0x2C030000
		opword 0x40820014
		opword 0x801E0004
		opword 0x60000100
		opword 0x901E0004
		opword 0x48000EFC
		opword 0x38610178
		la r4, str_8041A594(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x38610178
		opword 0x38920130
		bl strcmp
		opword 0x2C030000
		opword 0x4082005C
		opword 0xA8010230
		opword 0x7C000735
		opword 0x41820EC8
		opword 0x3C800001
		opword 0x381AFFFA
		opword 0xA8610230
		opword 0x3884FFFD
		opword 0xB09C0004
		opword 0x7C000734
		opword 0x3863FFFD
		opword 0x3B5AFFFD
		opword 0xB07C0008
		opword 0x931C000C
		opword 0x3B180032
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0xB0010234
		opword 0x38000000
		opword 0xB0010230
		opword 0x38030001
		opword 0x901E0038
		opword 0x48000E7C
		opword 0x38610178
		la r4, str_8041A598(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x38610178
		opword 0x3892013C
		bl strcmp
		opword 0x2C030000
		opword 0x4082002C
		opword 0x3C600001
		opword 0x3803FFFC
		opword 0xB01C0004
		opword 0x931C000C
		opword 0x3B180032
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x38030001
		opword 0x901E0038
		opword 0x48000E2C
		opword 0x38610178
		la r4, str_8041A59C(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x4082004C
		opword 0x386100F8
		opword 0x38A10048
		opword 0x38C10044
		la r4, str_8041A5A0(r2)
		opword 0x4CC63182
		bl sscanf
		opword 0x80610044
		opword 0x80010048
		opword 0x2C0303E7
		opword 0x7C1B0734
		opword 0x41820010
		opword 0xA8010234
		opword 0x7C030050
		opword 0x7C1A0734
		opword 0x7C0300D0
		opword 0x7C000734
		opword 0xB0010230
		opword 0x48000DD0
		opword 0x38610178
		la r4, str_8041A5A8(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x386100F8
		opword 0x38A10050
		la r4, str_8041A5B0(r2)
		opword 0x4CC63182
		bl sscanf
		opword 0x48000DA4
		opword 0x38610178
		opword 0x38920148
		bl strcmp
		opword 0x2C030000
		opword 0x40820010
		lfs f0, float_1_8041a52c(r2)
		opword 0xD0010050
		opword 0x48000D84
		opword 0x38610178
		la r4, str_8041A5B4(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820024
		opword 0x386100F8
		opword 0x38A10040
		la r4, str_8041A5BC(r2)
		opword 0x4CC63182
		bl sscanf
		opword 0x80010040
		opword 0x7F180214
		opword 0x48000D50
		opword 0x38610178
		la r4, str_8041A5C0(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x386100F8
		opword 0x38A10054
		la r4, str_8041A5BC(r2)
		opword 0x4CC63182
		bl sscanf
		opword 0x48000D24
		opword 0x38610178
		opword 0x38920150
		bl strcmp
		opword 0x2C030000
		opword 0x40820010
		opword 0x801E7A3C
		opword 0x90010054
		opword 0x48000D04
		opword 0x38610178
		opword 0x38920158
		bl strcmp
		opword 0x2C030000
		opword 0x40820020
		opword 0x386100F8
		opword 0x38A1004C
		la r4, str_8041A5B0(r2)
		opword 0x4CC63182
		bl sscanf
		opword 0x62F70001
		opword 0x48000CD4
		opword 0x38610178
		opword 0x38920160
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x56F7003C
		opword 0x48000CB8
		opword 0x38610178
		la r4, str_8041A5C8(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x62F70002
		opword 0x48000C9C
		opword 0x38610178
		opword 0x3892016C
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x56F707FA
		opword 0x48000C80
		opword 0x38610178
		la r4, str_8041A5D0(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x62F70004
		opword 0x48000C64
		opword 0x38610178
		la r4, str_8041A5D8(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x56F707B8
		opword 0x48000C48
		opword 0x38610178
		la r4, str_8041A5E0(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x4082003C
		opword 0x7F85E378
		opword 0x386100F8
		la r4, str_8041A5E4(r2)
		opword 0x4CC63182
		bl sscanf
		opword 0x3C600001
		opword 0x3803FFF7
		opword 0xB01C0004
		opword 0x931C000C
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x38030001
		opword 0x901E0038
		opword 0x48000BFC
		opword 0x38610178
		la r4, str_8041A5E8(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820030
		opword 0x380000FF
		opword 0x3C600001
		opword 0x901C0000
		opword 0x3803FFF7
		opword 0xB01C0004
		opword 0x931C000C
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x38030001
		opword 0x901E0038
		opword 0x48000BBC
		opword 0x38610178
		la r4, str_8041A5F0(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820030
		opword 0x38000001
		opword 0x3C600001
		opword 0x901C0000
		opword 0x3803FFF6
		opword 0xB01C0004
		opword 0x931C000C
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x38030001
		opword 0x901E0038
		opword 0x48000B7C
		opword 0x38610178
		opword 0x38920174
		bl strcmp
		opword 0x2C030000
		opword 0x4082002C
		opword 0x38000000
		opword 0x3C600001
		opword 0x901C0000
		opword 0x3803FFF6
		opword 0xB01C0004
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x38030001
		opword 0x901E0038
		opword 0x48000B40
		opword 0x38610178
		la r4, str_8041A5F8(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820030
		opword 0x38000001
		opword 0x3C600001
		opword 0x901C0000
		opword 0x3803FFF5
		opword 0xB01C0004
		opword 0x931C000C
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x38030001
		opword 0x901E0038
		opword 0x48000B00
		opword 0x38610178
		la r4, str_8041A600(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820030
		opword 0x38000000
		opword 0x3C600001
		opword 0x901C0000
		opword 0x3803FFF5
		opword 0xB01C0004
		opword 0x931C000C
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x38030001
		opword 0x901E0038
		opword 0x48000AC0
		opword 0x38610178
		la r4, str_8041A608(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x38600002
		opword 0x38000000
		opword 0x907D0008
		opword 0x90010054
		opword 0x901E7A3C
		opword 0x48000A94
		opword 0x38610178
		opword 0x3892017C
		bl strcmp
		opword 0x2C030000
		opword 0x40820038
		opword 0x38000003
		opword 0x3C600001
		opword 0x901D0008
		opword 0x3803FFF7
		lwz r3, dat_8041a508(r2)
		opword 0x907C0000
		opword 0xB01C0004
		opword 0x931C000C
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x38030001
		opword 0x901E0038
		opword 0x48000A4C
		opword 0x38610178
		la r4, str_8041A610(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820038
		opword 0x38000008
		opword 0x3C600001
		opword 0x901D0008
		opword 0x3803FFF7
		lwz r3, dat_8041a50c(r2)
		opword 0x907C0000
		opword 0xB01C0004
		opword 0x931C000C
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x38030001
		opword 0x901E0038
		opword 0x48000A04
		opword 0x38610178
		la r4, str_8041A614(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820010
		opword 0x38000009
		opword 0x901D0008
		opword 0x480009E4
		opword 0x38610178
		la r4, str_8041A61C(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820010
		opword 0x38000007
		opword 0x901D0008
		opword 0x480009C4
		opword 0x38610178
		opword 0x38920184
		bl strcmp
		opword 0x2C030000
		opword 0x40820010
		opword 0x3800000A
		opword 0x901D0008
		opword 0x480009A4
		opword 0x38610178
		la r4, str_8041A624(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820010
		opword 0x38000006
		opword 0x901D0008
		opword 0x48000984
		opword 0x38610178
		opword 0x3892018C
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x38600004
		opword 0x38000000
		opword 0x907D0008
		opword 0x90010054
		opword 0x901E7A3C
		opword 0x48000958
		opword 0x38610178
		la r4, str_8041A62C(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x38000001
		opword 0x901D0008
		opword 0x801E0004
		opword 0x60000010
		opword 0x901E0004
		opword 0x4800092C
		opword 0x38610178
		la r4, str_8041A634(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820010
		opword 0x3800000B
		opword 0x901D0008
		opword 0x4800090C
		opword 0x38610178
		la r4, str_8041A63C(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x408200AC
		opword 0x386100F8
		opword 0x38920194
		opword 0x38A10016
		opword 0x38C10014
		opword 0x38E10012
		opword 0x39010010
		opword 0x4CC63182
		bl sscanf
		opword 0xA07D0002
		opword 0x3C004330
		opword 0x90010210
		opword 0x60630004
		opword 0xC8320118
		opword 0xB07D0002
		opword 0xA8610016
		opword 0x90010208
		opword 0x6C638000
		opword 0x90610214
		opword 0xC8010210
		opword 0x90010200
		opword 0xEC000828
		opword 0x900101F8
		opword 0xD01D000C
		opword 0xA8010014
		opword 0x6C008000
		opword 0x9001020C
		opword 0xC8010208
		opword 0xEC000828
		opword 0xD01D0010
		opword 0xA8010012
		opword 0x6C008000
		opword 0x90010204
		opword 0xC8010200
		opword 0xEC000828
		opword 0xD01D0014
		opword 0xA8010010
		opword 0x6C008000
		opword 0x900101FC
		opword 0xC80101F8
		opword 0xEC000828
		opword 0xD01D0018
		opword 0x48000850
		opword 0x38610178
		opword 0x389201A4
		bl strcmp
		opword 0x2C030000
		opword 0x40820060
		opword 0x38000005
		opword 0x386100F8
		opword 0x901D0008
		opword 0x389201AC
		opword 0x38A1000E
		opword 0x38C1000C
		opword 0x801E0004
		opword 0x38FE7A44
		opword 0x391E7A46
		opword 0x60000020
		opword 0x901E0004
		opword 0x4CC63182
		bl sscanf
		opword 0xA881000E
		opword 0x38600001
		opword 0x38000000
		opword 0x62F70100
		opword 0x989E7A41
		opword 0xA881000C
		opword 0x989E7A42
		opword 0x987E7A40
		opword 0x90010054
		opword 0x480007E0
		opword 0x38610178
		la r4, str_8041A644(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820038
		opword 0x7F85E378
		opword 0x386100F8
		la r4, str_8041A5BC(r2)
		opword 0x4CC63182
		bl sscanf
		opword 0x3C600001
		opword 0x3803FFFA
		opword 0xB01C0004
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x38030001
		opword 0x901E0038
		opword 0x48000798
		opword 0x38610178
		la r4, str_8041A648(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820038
		opword 0x7F85E378
		opword 0x386100F8
		la r4, str_8041A5BC(r2)
		opword 0x4CC63182
		bl sscanf
		opword 0x3C600001
		opword 0x3803FFF9
		opword 0xB01C0004
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x38030001
		opword 0x901E0038
		opword 0x48000750
		opword 0x38610178
		opword 0x389201BC
		bl strcmp
		opword 0x2C030000
		opword 0x40820014
		opword 0xA01D0002
		opword 0x60000008
		opword 0xB01D0002
		opword 0x4800072C
		opword 0x38610178
		la r4, str_8041A64C(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x408202E0
		opword 0x880100F8
		li r14, 0x0
		opword 0x7C000774
		opword 0x2C000030
		opword 0x41800034
		opword 0x2C000039
		opword 0x4181002C
		opword 0x386100F8
		opword 0x389201C4
		opword 0x38A1003C
		opword 0x38C1002C
		opword 0x38E10038
		opword 0x39010034
		opword 0x39210030
		opword 0x4CC63182
		bl sscanf
		opword 0x480000A0
		opword 0x386100F8
		opword 0x389201D0
		opword 0x38A100D8
		opword 0x38C1002C
		opword 0x38E10038
		opword 0x39010034
		opword 0x39210030
		opword 0x4CC63182
		bl sscanf
		opword 0x386100D8
		la r4, str_8041A4D0(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x39C00001
		lis r3, msgIcon@ha
		opword 0x3A000000
		addi r17, r3, msgIcon@l
		opword 0x80710000
		opword 0x388100D8
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		lis r3, msgIcon@ha
		opword 0x56041838
		addi r0, r3, msgIcon@l
		opword 0x7C602214
		opword 0x80030004
		opword 0x48000018
		opword 0x3A100001
		opword 0x3A310008
		opword 0x28100012
		opword 0x4180FFC8
		opword 0x3800FFFF
		opword 0x2C000000
		opword 0x9001003C
		opword 0x4080000C
		opword 0x38000000
		opword 0x9001003C
		opword 0x2C0E0000
		opword 0x40820118
		opword 0x8001003C
		opword 0x3861000A
		opword 0x38810008
		opword 0x901C0000
		opword 0x8001003C
		opword 0x5405043E
		bl iconGetWidthHight
		opword 0x3C600001
		opword 0x3CA04330
		opword 0x3863FFF8
		opword 0x7F600734
		opword 0xB07C0004
		opword 0x6C038000
		opword 0x7F400734
		opword 0xC8720120
		opword 0xA081000A
		opword 0x6C008000
		opword 0x90A10208
		opword 0x3B7B0028
		opword 0x80C10038
		opword 0x9081020C
		opword 0x6CC48000
		opword 0xC8B20118
		opword 0xC8010208
		opword 0x90610204
		opword 0xEC401828
		lfs f4, float_0p5_8041a534(r2)
		opword 0x90A10200
		opword 0xC021002C
		opword 0xC8010200
		opword 0xEC4400B2
		opword 0x90810214
		opword 0xEC002828
		opword 0x90A10210
		opword 0xC8810210
		opword 0xEC02007A
		opword 0x90010224
		opword 0xEC242828
		opword 0x90A10218
		opword 0xEC21002A
		opword 0x90A10220
		opword 0xC8010220
		opword 0xFC20081E
		opword 0xEC002828
		opword 0xD82101F8
		opword 0x800101FC
		opword 0xB01C0006
		opword 0xA0010008
		opword 0xC021002C
		opword 0x9001021C
		opword 0xC8410218
		opword 0xEC421828
		opword 0xEC02007C
		opword 0xFC00001E
		opword 0xD8010228
		opword 0x8001022C
		opword 0xB01C0008
		opword 0x80010034
		opword 0xB01C000A
		opword 0xC001002C
		opword 0xD01C0010
		opword 0x931C000C
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x80810054
		opword 0x38030001
		opword 0x901E0038
		opword 0x7F182214
		opword 0x4800051C
		opword 0x3C600001
		opword 0x386394B5
		bl kanjiSearch
		opword 0x7C6E1B78
		opword 0x5463043E
		bl kanjiGetWidth
		opword 0x5464043E
		opword 0x3C604330
		opword 0x38840004
		opword 0x90610228
		opword 0x6C848000
		opword 0xC8720118
		opword 0x9081022C
		opword 0x56E007FF
		opword 0xC0010050
		opword 0xC8410228
		lfs f1, float_10_8041a538(r2)
		opword 0xEC421828
		opword 0xEC0000B2
		opword 0xFC00001E
		opword 0xD8010220
		opword 0x80010224
		opword 0xB001000A
		opword 0xB1DC0004
		opword 0xB37C0006
		opword 0xC0010050
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010218
		opword 0x8001021C
		opword 0x7C00D050
		opword 0xB01C0008
		opword 0xC0010050
		opword 0xD01C0010
		opword 0x92FC0000
		opword 0x801C0000
		opword 0x60000008
		opword 0x901C0000
		opword 0x4182000C
		opword 0xC001004C
		opword 0xD01C0014
		opword 0xC0010050
		opword 0xFC1D0040
		opword 0x40800008
		opword 0xFFA00090
		opword 0x931C000C
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x80810054
		opword 0xA0A1000A
		opword 0x38030001
		opword 0x7F182214
		opword 0x7C7B2A14
		opword 0x901E0038
		opword 0x7C7B0734
		opword 0x4800043C
		opword 0x38610178
		la r4, str_8041A654(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x408200E0
		opword 0x386100F8
		opword 0x389201DC
		opword 0x38A100B8
		opword 0x38C10098
		opword 0x38E10028
		opword 0x39010024
		opword 0x3921001C
		opword 0x39410020
		opword 0x4CC63182
		bl sscanf
		opword 0x386100B8
		opword 0x38800002
		bl animPoseEntry
		opword 0x907C0000
		opword 0x38810098
		opword 0x38A00001
		opword 0x807C0000
		bl animPoseSetAnim
		opword 0x807C0000
		opword 0x38801800
		bl animPoseSetMaterialFlagOn
		opword 0x807C0000
		opword 0x38800040
		bl animPoseSetMaterialFlagOff
		lwz r6, msgw(r13)
		lis r3, msgDispKeyWait_render@ha
		addi r4, r3, msgDispKeyWait_render@l
		opword 0x38A00000
		opword 0x80660020
		bl animPoseSetGXFunc
		opword 0x3C600001
		opword 0x3803FFF4
		opword 0xB01C0004
		opword 0x80010028
		opword 0xB01C0006
		opword 0xA8010234
		opword 0x80610024
		opword 0x7C030050
		opword 0xB01C0008
		opword 0xC001001C
		opword 0xD01C0010
		opword 0x80010020
		opword 0x2C000000
		opword 0x4082000C
		lfs f0, float_0_8041a514(r2)
		opword 0x48000008
		lfs f0, float_180_8041a568(r2)
		opword 0xD01C0014
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x80810054
		opword 0x38030001
		opword 0x901E0038
		opword 0x7F182214
		opword 0x4800034C
		opword 0x38610178
		la r4, str_8041A65C(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x4082006C
		opword 0x386100F8
		opword 0x38A10078
		opword 0x38C10018
		la r4, str_8041A664(r2)
		opword 0x4CC63182
		bl sscanf
		opword 0x38610078
		la r4, str_8041A66C(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x41820010
		opword 0x38610078
		bl npcNameToPtr
		opword 0x48000008
		opword 0x38600000
		opword 0x3C800001
		opword 0x907C0000
		opword 0x3804FFF3
		opword 0xB01C0004
		opword 0x80010018
		opword 0x901C000C
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x38030001
		opword 0x901E0038
		opword 0x480002D0
		opword 0x38610178
		opword 0x389201EC
		bl strcmp
		opword 0x2C030000
		opword 0x40820060
		opword 0x386100F8
		opword 0x38A10058
		la r4, str_8041A670(r2)
		opword 0x4CC63182
		bl sscanf
		opword 0x38610058
		la r4, str_8041A66C(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x41820010
		opword 0x38610058
		bl npcNameToPtr
		opword 0x48000008
		opword 0x38600000
		opword 0x3C800001
		opword 0x907C0000
		opword 0x3804FFF2
		opword 0xB01C0004
		opword 0x3B9C0018
		opword 0x807E0038
		opword 0x38030001
		opword 0x901E0038
		opword 0x48000260
		opword 0x38610178
		la r4, str_8041A674(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x807E7A4C
		opword 0x80030008
		opword 0x2C000001
		opword 0x4182023C
		opword 0x7F79DB78
		opword 0x48000234
		opword 0x88610178
		opword 0x7C600774
		opword 0x2C000052
		opword 0x41820014
		opword 0x2C00002F
		opword 0x4082021C
		opword 0x28002F72
		opword 0x40820214
		opword 0x7C600774
		opword 0x3A200001
		opword 0x2C000052
		opword 0x41820008
		opword 0x3A200002
		opword 0x807E7A4C
		opword 0x80030008
		opword 0x2C000001
		opword 0x4182EF54
		opword 0x38610178
		opword 0x7C638A14
		bl strlen
		opword 0x54640FFE
		opword 0x38010178
		opword 0x7C641A14
		opword 0xCBF20118
		lfs f30, float_0p55_8041a678(r2)
		opword 0x7E2F8B78
		opword 0x7C760E70
		opword 0x7E808A14
		opword 0x3A600000
		opword 0x3A000000
		opword 0x3DC04330
		opword 0x48000058
		opword 0xA0740000
		bl kanjiSearch
		opword 0x5463043E
		bl kanjiGetWidth
		opword 0x5463043E
		opword 0x91C10228
		opword 0x38030004
		opword 0xC0010050
		opword 0x6C008000
		opword 0x39EF0002
		opword 0x9001022C
		opword 0x3A940002
		opword 0x3A100001
		opword 0xC8210228
		opword 0xEC21F828
		opword 0xEC000072
		opword 0xEC1E0032
		opword 0xFC00001E
		opword 0xD8010220
		opword 0x80010224
		opword 0x7E730214
		opword 0x7C10B000
		opword 0x4180FFA8
		opword 0x3DC04330
		opword 0x5660043E
		opword 0x9001022C
		opword 0x38010178
		lfs f2, float_4_8041a67c(r2)
		opword 0x7F240734
		opword 0x91C10228
		opword 0x7F630734
		opword 0xC0210050
		opword 0x7C641A14
		opword 0xC8720120
		opword 0x6C638000
		opword 0xC8010228
		opword 0xEC820072
		lfs f30, float_0p55_8041a678(r2)
		opword 0x7E808A14
		opword 0xEC001828
		opword 0x9061021C
		opword 0xCBF20118
		opword 0x91C10218
		opword 0x7F500734
		opword 0xEC3E013C
		opword 0xC8010218
		opword 0x56EF07FE
		opword 0x91C10210
		opword 0x3BE00000
		opword 0xFC40081E
		opword 0xEC20F828
		lfs f0, float_0p5_8041a534(r2)
		opword 0xD8410220
		opword 0xEC412028
		opword 0x82610224
		opword 0x5660043E
		opword 0x90010214
		opword 0xC8210210
		opword 0xEC211828
		opword 0xEC220828
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010208
		opword 0x8321020C
		opword 0x480000A4
		opword 0xA0740000
		bl kanjiSearch
		opword 0x7C731B78
		opword 0x5463043E
		bl kanjiGetWidth
		opword 0x5463043E
		opword 0xC0010050
		opword 0x38030004
		opword 0x91C10228
		opword 0x6C008000
		opword 0x280F0000
		opword 0x9001022C
		opword 0xC8210228
		opword 0xB27C0004
		opword 0xEC21F828
		opword 0xB33C0006
		opword 0xEC200072
		opword 0xB21C0008
		opword 0xC0010050
		opword 0xEC3E0072
		opword 0xEC1E0032
		opword 0xFC20081E
		opword 0xD01C0010
		opword 0xD8210220
		opword 0x92FC0000
		opword 0x80010224
		opword 0x4182000C
		opword 0xC001004C
		opword 0xD01C0014
		opword 0x38600000
		opword 0x7C190214
		opword 0x907C000C
		opword 0x7C190734
		opword 0x3A310002
		opword 0x3A940002
		opword 0x807E0038
		opword 0x3BFF0001
		opword 0x3B9C0018
		opword 0x38030001
		opword 0x901E0038
		opword 0x7C1FB000
		opword 0x4180FF5C
		opword 0x4BFFED68
		opword 0x880F0000
		opword 0x2C00000A
		opword 0x4082ED5C
		opword 0x3AB50001
		opword 0x4BFFED54
		lwz r4, gp(r13)
		opword 0x8004016C
		opword 0x28000000
		opword 0x40820030
		opword 0x7C600774
		opword 0x2C000030
		opword 0x41800024
		opword 0x2C000039
		opword 0x4181001C
		opword 0x3C630001
		opword 0x3803821F
		opword 0x5403043E
		bl kanjiSearch
		opword 0x7C6E1B78
		opword 0x4800000C
		bl hankakuSearch
		opword 0x7C6E1B78
		opword 0x55C3043E
		bl kanjiGetWidth
		opword 0xC0410050
		opword 0x5463043E
		opword 0x38630002
		opword 0x3C004330
		opword 0xB1DC0004
		opword 0x6C638000
		lfs f1, float_10_8041a538(r2)
		opword 0xB37C0006
		opword 0xC8720118
		opword 0xC0010050
		opword 0x9061022C
		opword 0xEC010032
		opword 0x90010228
		opword 0xFC00001E
		opword 0xC8210228
		opword 0xEC211828
		opword 0xD8010218
		opword 0x8001021C
		opword 0xEC020072
		opword 0x7C00D050
		opword 0xB01C0008
		opword 0xFC20001E
		opword 0xC0010050
		opword 0xD8210220
		opword 0xD01C0010
		opword 0x80610224
		opword 0x92FC0000
		opword 0x88150000
		opword 0x2C000020
		opword 0x41820010
		opword 0x801C0000
		opword 0x60000008
		opword 0x901C0000
		opword 0x56E007FF
		opword 0x4182000C
		opword 0xC001004C
		opword 0xD01C0014
		opword 0xC0010050
		opword 0xFC1D0040
		opword 0x40800008
		opword 0xFFA00090
		opword 0x931C000C
		opword 0x7C1B1A14
		opword 0x7C1B0734
		opword 0x3AB50001
		opword 0x807E0038
		opword 0x3B9C0018
		opword 0x80810054
		opword 0x38030001
		opword 0x901E0038
		opword 0x7F182214
		opword 0x4BFFEC38
	}
}
#pragma pop
#endif

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
	a1 = (u8)a1;
	if ((a1 >= 0x81 && a1 <= 0x9F) || (a1 >= 0xE0 && a1 <= 0xFC)) {
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
			window->y = EXT_LIT(float_225_8041a578, 225.0f);
			window->height = EXT_LIT(float_560_8041a57c, 560.0f);
			window->width = EXT_LIT(float_176_8041a580, 176.0f);
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
		window->height = EXT_LIT(float_0p7_8041a584, 0.7f) * GXGetTexObjWidth(getWakuTexObj(3));
		window->width = EXT_LIT(float_0p7_8041a584, 0.7f) * GXGetTexObjHeight(getWakuTexObj(3));
		break;
	}
	return id;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 msgWindow_Entry(const char* msg, s32 field_0x79FC, u16 priority) {
	asm volatile {
		opword 0x9421FFB0
		opword 0x7C0802A6
		opword 0x90010054
		opword 0xBF410038
		opword 0x7C7C1B78
		opword 0x7C9A2378
		opword 0x7CA32B78
		bl windowEntry
		opword 0x7C7B1B78
		bl windowGetPointer
		lis r4, msgWindow_Main@ha
		opword 0x7C7F1B78
		addi r0, r4, msgWindow_Main@l
		lis r3, msgWindow_Delete@ha
		opword 0x901F003C
		addi r3, r3, msgWindow_Delete@l
		opword 0x38800005
		opword 0x3800FFFF
		opword 0x907F0040
		opword 0x7F83E378
		opword 0xB09F0000
		opword 0x901F0008
		opword 0xA01F0002
		opword 0x60000002
		opword 0xB01F0002
		bl strlen
		opword 0x7C641B78
		opword 0x38600000
		bl __memAlloc
		opword 0x7F84E378
		opword 0x7C7E1B78
		bl strcpy
		opword 0x38607A58
		opword 0x38800001
		bl smartAlloc
		opword 0x83A30000
		opword 0x7C7C1B78
		opword 0x38800000
		opword 0x38A07A58
		opword 0x7FA3EB78
		bl memset
		opword 0x93FD7A4C
		opword 0x38000003
		opword 0x38C00000
		opword 0x38A0007F
		opword 0x901D0004
		opword 0x38000019
		opword 0x7F83E378
		opword 0x7FC4F378
		opword 0x935D79FC
		lwz r8, gp(r13)
		opword 0x80E80038
		opword 0x8108003C
		opword 0x911D0034
		opword 0x90FD0030
		lwz r8, gp(r13)
		opword 0x80E80038
		opword 0x8108003C
		opword 0x911D001C
		opword 0x90FD0018
		opword 0x90DD7A28
		opword 0x98BD7A2C
		opword 0x90DD7A30
		opword 0xB0DD7A34
		opword 0xB0DD7A36
		opword 0xB0DD7A38
		opword 0xB0DD7A3A
		opword 0x901D7A3C
		opword 0x90DD7840
		bl msgAnalize
		opword 0x801F0008
		opword 0x2C000001
		opword 0x40820010
		opword 0x801D0004
		opword 0x60000200
		opword 0x901D0004
		opword 0x7FC4F378
		opword 0x38600000
		bl __memFree
		opword 0x939F0028
		opword 0x38000000
		opword 0x807F0028
		opword 0x80630000
		opword 0x90037A50
		opword 0x90037A54
		opword 0x801F0008
		opword 0x2C000005
		opword 0x4182006C
		opword 0x4080001C
		opword 0x2C000001
		opword 0x41820170
		opword 0x4080002C
		opword 0x2C000000
		opword 0x40800024
		opword 0x480001DC
		opword 0x2C00000B
		opword 0x4182000C
		opword 0x408001D0
		opword 0x48000010
		lis r3, msgWindow_Clear_Main@ha
		addi r0, r3, msgWindow_Clear_Main@l
		opword 0x901F003C
		opword 0xA01F0002
		opword 0x5400077B
		opword 0x408201B4
		lfs f1, float_neg280_8041a574(r2)
		lfs f0, float_225_8041a578(r2)
		opword 0xD03F000C
		lfs f1, float_560_8041a57c(r2)
		opword 0xD01F0010
		lfs f0, float_176_8041a580(r2)
		opword 0xD03F0014
		opword 0xD01F0018
		opword 0x48000190
		lis r4, selectWindow_Main@ha
		opword 0x3C004330
		addi r5, r4, selectWindow_Main@l
		opword 0x90010008
		lis r4, double_to_int_802c4f08@ha
		opword 0x90BF003C
		lfd f2, double_to_int_802c4f08@l(r4)
		opword 0x809F0028
		opword 0x90010010
		opword 0x80840000
		opword 0x90010018
		opword 0xA8847A44
		opword 0x90010020
		opword 0x7CA400D0
		opword 0x54A40FFE
		opword 0x90010028
		opword 0x7C842A14
		opword 0x7C840E70
		opword 0x7C800734
		opword 0x6C008000
		opword 0x9001000C
		opword 0xC8010008
		opword 0xEC001028
		opword 0xD01F000C
		opword 0x809F0028
		opword 0x80840000
		opword 0xA8047A46
		opword 0x6C008000
		opword 0x90010014
		opword 0xC8010010
		opword 0xEC001028
		opword 0xD01F0010
		opword 0x809F0028
		opword 0x80840000
		opword 0xA8047A44
		opword 0x6C008000
		opword 0x9001001C
		opword 0xC8010018
		opword 0xEC001028
		opword 0xD01F0014
		opword 0x809F0028
		opword 0x80840000
		opword 0x88047A40
		opword 0x7C000774
		opword 0x1C800024
		opword 0x38040028
		opword 0x7C000734
		opword 0x6C008000
		opword 0x90010024
		opword 0xC8010020
		opword 0xEC001028
		opword 0xD01F0018
		opword 0x809F0028
		opword 0x80840000
		opword 0x88047A41
		opword 0x98047A43
		opword 0x88037A43
		opword 0xC03F0010
		opword 0x7C000774
		opword 0x1C80001F
		opword 0x3804003A
		opword 0x6C008000
		opword 0x9001002C
		opword 0xC8010028
		opword 0xEC001028
		opword 0xEC010028
		opword 0xD0037A48
		opword 0x48000080
		opword 0x3800000A
		opword 0x38600003
		opword 0xB01F0004
		bl getWakuTexObj
		bl GXGetTexObjWidth
		opword 0x5464043E
		opword 0x3C004330
		lis r3, double_to_int_mask_802c4f10@ha
		opword 0x9081002C
		addi r4, r3, double_to_int_mask_802c4f10@l
		lfs f0, float_0p7_8041a584(r2)
		opword 0x90010028
		opword 0x38600003
		opword 0xC8440000
		opword 0xC8210028
		opword 0xEC211028
		opword 0xEC000072
		opword 0xD01F0014
		bl getWakuTexObj
		bl GXGetTexObjHeight
		opword 0x5464043E
		opword 0x3C004330
		opword 0x90810024
		lis r3, double_to_int_mask_802c4f10@ha
		lfd f2, double_to_int_mask_802c4f10@l(r3)
		opword 0x90010020
		lfs f0, float_0p7_8041a584(r2)
		opword 0xC8210020
		opword 0xEC211028
		opword 0xEC000072
		opword 0xD01F0018
		opword 0x7F63DB78
		opword 0xBB410038
		opword 0x80010054
		opword 0x7C0803A6
		opword 0x38210050
	}
}
#pragma pop
#endif

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
	data->playTime = 0;
	data->scrollTarget = 0;
	data->scrollPos = 0;
	data->nextEntry = 0;
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

#ifdef NONMATCHING
static inline BOOL msgWinPrevPage(WindowEntry* window) {
	MsgWinData* d = WIN_DATA(window);
	d->page--;
	if (d->page < 0) {
		d->page = 0;
		return FALSE;
	}
	return TRUE;
}
#endif

#ifdef NONMATCHING
static inline void msgWinNextPage(WindowEntry* window) {
	MsgWinData* d = WIN_DATA(window);
	s32 max;
	d->page++;
	max = d->pageCount - 1;
	if (d->page > max) {
		d->page = max;
	}
}
#endif

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
	dispEntry(CAMERA_2D, EXT_LIT(float_400_8041a530, 400.0f) - *(s16*)&window->field_0x4, 0, msgWindow_Disp, window);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void msgWindow_Main(WindowEntry* window) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0x93E1002C
		opword 0x7C7F1B78
		opword 0x93C10028
		opword 0x93A10024
		opword 0x83C30028
		opword 0x83BE0000
		opword 0x801D7A50
		opword 0x2C000000
		opword 0x4182007C
		opword 0x801D7A54
		opword 0x2C000000
		opword 0x4082002C
		opword 0x801D0004
		opword 0x54000739
		opword 0x41820010
		opword 0x807D7A24
		bl BtlUnit_ChangeTalkAnim
		opword 0x4800000C
		opword 0x387D7A04
		bl npcSetTalkPose
		opword 0x38000001
		opword 0x901D7A54
		opword 0x807D7A50
		opword 0x3803FFFF
		opword 0x901D7A50
		opword 0x801D7A50
		opword 0x2C000000
		opword 0x40820030
		opword 0x807E0000
		opword 0x80030004
		opword 0x54000739
		opword 0x41820010
		opword 0x80637A24
		bl BtlUnit_ChangeStayAnim
		opword 0x4800000C
		opword 0x38637A04
		bl npcSetStayPose
		opword 0x38000000
		opword 0x901D7A54
		opword 0xA01F0000
		opword 0x2800000B
		opword 0x4181069C
		lis r3, jumptable_8030DBA0@ha
		opword 0x5400103A
		addi r3, r3, jumptable_8030DBA0@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0xA01F0002
		opword 0x54000739
		opword 0x40820028
		opword 0x801F0008
		lis r3, msgWindowOpen_SE_Data@ha
		addi r3, r3, msgWindowOpen_SE_Data@l
		opword 0x54001838
		opword 0x7C03002E
		opword 0x2C000000
		opword 0x4180000C
		opword 0x64030002
		bl psndSFXOn
		lwz r4, gp(r13)
		opword 0x38000006
		opword 0x80640038
		opword 0x8084003C
		opword 0x909F0024
		opword 0x907F0020
		opword 0xB01F0000
		opword 0xA01F0002
		opword 0x3C601062
		opword 0x3C808000
		opword 0x38A00000
		opword 0x60000002
		opword 0x38634DD3
		opword 0xB01F0002
		opword 0x800400F8
		lwz r6, gp(r13)
		opword 0x5400F0BE
		opword 0x809F0024
		opword 0x7C030016
		opword 0x8066003C
		opword 0x80C60038
		opword 0x7C841810
		opword 0x807F0020
		opword 0x7C633110
		opword 0x5406D1BE
		bl __div2i
		opword 0x38E000FF
		opword 0x38A00000
		opword 0x7C043816
		opword 0x38C000C8
		opword 0x7C6339D6
		opword 0x1C8400FF
		opword 0x7C601A14
		bl __div2i
		opword 0xB09F0006
		opword 0xA81F0006
		opword 0x2C0000FF
		opword 0x408105BC
		opword 0x386000FF
		opword 0x38000001
		opword 0xB07F0006
		opword 0xB01F0000
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907D001C
		opword 0x901D0018
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907D0034
		opword 0x901D0030
		opword 0x48000580
		opword 0xA01F0002
		opword 0x54000739
		opword 0x4082002C
		opword 0x801F0008
		lis r3, msgWindowOpen_SE_Data@ha
		addi r3, r3, msgWindowOpen_SE_Data@l
		opword 0x54001838
		opword 0x7C630214
		opword 0x80030004
		opword 0x2C000000
		opword 0x4180000C
		opword 0x64030002
		bl psndSFXOn
		lwz r4, gp(r13)
		opword 0x38000008
		opword 0x80640038
		opword 0x8084003C
		opword 0x909F0024
		opword 0x907F0020
		opword 0xB01F0000
		opword 0xA81F0006
		opword 0x2C000000
		opword 0x40820010
		opword 0x7FE3FB78
		bl windowDelete
		opword 0x48000560
		opword 0x3C608000
		lwz r6, gp(r13)
		opword 0x800300F8
		opword 0x3C601062
		opword 0x80A6003C
		opword 0x38634DD3
		opword 0x5400F0BE
		opword 0x809F0024
		opword 0x7C030016
		opword 0x80C60038
		opword 0x7C842810
		opword 0x807F0020
		opword 0x38A00000
		opword 0x7C633110
		opword 0x5406D1BE
		bl __div2i
		opword 0x38E000FF
		opword 0x38A00000
		opword 0x7C043816
		opword 0x38C000C8
		opword 0x7C6339D6
		opword 0x1C8400FF
		opword 0x7C601A14
		bl __div2i
		opword 0x380000FF
		opword 0x38A00000
		opword 0x7C040010
		opword 0xB01F0006
		opword 0xA81F0006
		opword 0x2C000000
		opword 0x4181049C
		opword 0xB0BF0006
		opword 0x48000494
		opword 0x807F0028
		bl msgMain
		opword 0x2C030002
		opword 0x41820090
		opword 0x40800480
		opword 0x2C030000
		opword 0x41820010
		opword 0x40800040
		opword 0x48000470
		opword 0x4800046C
		opword 0x38000007
		opword 0xB01F0000
		opword 0x807F0028
		opword 0x80630000
		opword 0x80030004
		opword 0x54000739
		opword 0x41820010
		opword 0x80637A24
		bl BtlUnit_ChangeStayAnim
		opword 0x48000444
		opword 0x38637A04
		bl npcSetStayPose
		opword 0x48000438
		opword 0x38000002
		opword 0xB01F0000
		opword 0xA01F0002
		opword 0x540007FA
		opword 0xB01F0002
		opword 0x807F0028
		opword 0x80630000
		opword 0x80030004
		opword 0x54000739
		opword 0x41820010
		opword 0x80637A24
		bl BtlUnit_ChangeStayAnim
		opword 0x48000404
		opword 0x38637A04
		bl npcSetStayPose
		opword 0x480003F8
		opword 0x38000003
		opword 0xB01F0000
		opword 0x480003EC
		opword 0x807F0028
		opword 0x3BC00100
		opword 0x80630000
		opword 0x80030004
		opword 0x540005EF
		opword 0x41820008
		opword 0x3BC00500
		opword 0x38600000
		bl keyGetButtonTrg
		opword 0x63C00200
		opword 0x7C600039
		opword 0x41820038
		opword 0x38600001
		opword 0x38000002
		opword 0xB07F0000
		opword 0x38600000
		opword 0xB01D000A
		bl keyGetButtonTrg
		opword 0x546005AD
		opword 0x41820018
		opword 0x807D0004
		opword 0x54600631
		opword 0x4082000C
		opword 0x60600004
		opword 0x901D0004
		opword 0x38600000
		bl keyGetButtonTrg
		opword 0x546006F7
		opword 0x41820378
		opword 0x807D7840
		opword 0x3803FFFF
		opword 0x901D783C
		opword 0x807F0028
		opword 0x80830000
		opword 0x8064783C
		opword 0x3803FFFF
		opword 0x9004783C
		opword 0x8004783C
		opword 0x2C000000
		opword 0x40800010
		opword 0x38000000
		opword 0x9004783C
		opword 0x48000008
		opword 0x38000001
		opword 0x28000000
		opword 0x41820334
		opword 0x38000009
		opword 0x3C600002
		opword 0xB01F0000
		opword 0x38630041
		lwz r4, gp(r13)
		opword 0x80040038
		opword 0x8084003C
		opword 0x909F0024
		opword 0x901F0020
		bl psndSFXOn
		opword 0x801D0004
		opword 0x60000040
		opword 0x901D0004
		opword 0x480002FC
		opword 0x807D783C
		opword 0x801D0028
		opword 0x5463103A
		opword 0x7C7D1A14
		opword 0x83C37844
		opword 0x7C00F000
		opword 0x418002E0
		opword 0x3C608000
		lwz r6, gp(r13)
		opword 0x800300F8
		opword 0x3C601062
		opword 0x80A6003C
		opword 0x38634DD3
		opword 0x5400F0BE
		opword 0x809F0024
		opword 0x7C030016
		opword 0x80C60038
		opword 0x7C842810
		opword 0x807F0020
		opword 0x38A00000
		opword 0x7C633110
		opword 0x5406D1BE
		bl __div2i
		bl __cvt_sll_flt
		opword 0x809D0028
		opword 0x3C004330
		opword 0x90010008
		lis r3, double_to_int_802c4f08@ha
		opword 0x6C808000
		lfd f2, double_to_int_802c4f08@l(r3)
		opword 0x9001000C
		lfs f3, float_0p6_8041a570(r2)
		opword 0xC8010008
		opword 0xEC001028
		opword 0xEC03007C
		opword 0xFC00001E
		opword 0xD8010010
		opword 0x80010014
		opword 0x901D0028
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F0024
		opword 0x901F0020
		opword 0x801D0028
		opword 0x7C00F000
		opword 0x41810240
		opword 0x93DD0028
		opword 0x3800000B
		opword 0xB01F0000
		opword 0x48000230
		opword 0x807D783C
		opword 0x801D0028
		opword 0x5463103A
		opword 0x7C7D1A14
		opword 0x83C37844
		opword 0x7C00F000
		opword 0x41810214
		opword 0x3C608000
		lwz r6, gp(r13)
		opword 0x800300F8
		opword 0x3C601062
		opword 0x80A6003C
		opword 0x38634DD3
		opword 0x5400F0BE
		opword 0x809F0024
		opword 0x7C030016
		opword 0x80C60038
		opword 0x7C842810
		opword 0x807F0020
		opword 0x38A00000
		opword 0x7C633110
		opword 0x5406D1BE
		bl __div2i
		bl __cvt_sll_flt
		opword 0x809D0028
		opword 0x3C004330
		opword 0x90010010
		lis r3, double_to_int_802c4f08@ha
		opword 0x6C808000
		lfd f2, double_to_int_802c4f08@l(r3)
		opword 0x90010014
		lfs f3, float_0p6_8041a570(r2)
		opword 0xC8010010
		opword 0xEC001028
		opword 0xEC03007A
		opword 0xFC00001E
		opword 0xD8010008
		opword 0x8001000C
		opword 0x901D0028
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F0024
		opword 0x901F0020
		opword 0x801D0028
		opword 0x7C00F000
		opword 0x41800174
		opword 0x93DD0028
		opword 0x807D7840
		opword 0x809D783C
		opword 0x3803FFFF
		opword 0x7C040000
		opword 0x4082001C
		opword 0x38000003
		opword 0xB01F0000
		opword 0x801D0004
		opword 0x540006B0
		opword 0x901D0004
		opword 0x48000144
		opword 0x3800000B
		opword 0xB01F0000
		opword 0x48000138
		opword 0x807F0028
		opword 0x3BC00100
		opword 0x80630000
		opword 0x80030004
		opword 0x540005EF
		opword 0x41820008
		opword 0x3BC00500
		opword 0x38600000
		bl keyGetButtonTrg
		opword 0x7C60F039
		opword 0x41820058
		opword 0x3800000A
		opword 0xB01F0000
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F0024
		opword 0x901F0020
		opword 0x807F0028
		opword 0x80830000
		opword 0x8064783C
		opword 0x38030001
		opword 0x9004783C
		opword 0x80647840
		opword 0x8004783C
		opword 0x3863FFFF
		opword 0x7C001800
		opword 0x40810008
		opword 0x9064783C
		opword 0x3C600002
		opword 0x38630041
		bl psndSFXOn
		opword 0x38600000
		bl keyGetButtonTrg
		opword 0x546005AD
		opword 0x41820038
		opword 0x3800000A
		opword 0x3C600002
		opword 0xB01F0000
		opword 0x38630041
		lwz r4, gp(r13)
		opword 0x80040038
		opword 0x8084003C
		opword 0x909F0024
		opword 0x901F0020
		opword 0x809D7840
		opword 0x3804FFFF
		opword 0x901D783C
		bl psndSFXOn
		opword 0x38600000
		bl keyGetButtonTrg
		opword 0x546006F7
		opword 0x41820064
		opword 0x38000009
		opword 0xB01F0000
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F0024
		opword 0x901F0020
		opword 0x807F0028
		opword 0x80830000
		opword 0x8064783C
		opword 0x3803FFFF
		opword 0x9004783C
		opword 0x8004783C
		opword 0x2C000000
		opword 0x40800010
		opword 0x38000000
		opword 0x9004783C
		opword 0x48000008
		opword 0x38000001
		opword 0x28000000
		opword 0x41820010
		opword 0x3C600002
		opword 0x38630041
		bl psndSFXOn
		opword 0xA89F0004
		opword 0x3C004330
		lis r5, double_to_int_802c4f08@ha
		opword 0x90010010
		opword 0x6C848000
		lfs f2, float_400_8041a530(r2)
		opword 0x90810014
		addi r6, r5, double_to_int_802c4f08@l
		opword 0xC8260000
		lis r3, msgWindow_Disp@ha
		opword 0xC8010010
		addi r5, r3, msgWindow_Disp@l
		opword 0x7FE6FB78
		opword 0x38600008
		opword 0xEC000828
		opword 0x38800000
		opword 0xEC220028
		bl dispEntry
		opword 0x80010034
		opword 0x83E1002C
		opword 0x83C10028
		opword 0x83A10024
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop
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
	dispEntry(CAMERA_2D, EXT_LIT(float_400_8041a530, 400.0f) - *(s16*)&window->field_0x4, 0, msgWindow_Disp, window);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void msgWindow_Clear_Main(WindowEntry* window) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		opword 0x7C7F1B78
		opword 0xA0030000
		opword 0x80830028
		opword 0x2C000005
		opword 0x80840000
		opword 0x41820024
		opword 0x40800010
		opword 0x2C000001
		opword 0x4182005C
		opword 0x48000244
		opword 0x2C000007
		opword 0x418201A8
		opword 0x40800238
		opword 0x48000048
		opword 0x38000001
		opword 0xB01F0000
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F0024
		opword 0x901F0020
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x9064001C
		opword 0x90040018
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x90640034
		opword 0x90040030
		opword 0xA01F0002
		opword 0x60000002
		opword 0xB01F0002
		opword 0xA81F0006
		opword 0x2C0000FF
		opword 0x4080007C
		opword 0x3C608000
		lwz r6, gp(r13)
		opword 0x800300F8
		opword 0x3C601062
		opword 0x80A6003C
		opword 0x38634DD3
		opword 0x5400F0BE
		opword 0x809F0024
		opword 0x7C030016
		opword 0x80C60038
		opword 0x7C842810
		opword 0x807F0020
		opword 0x38A00000
		opword 0x7C633110
		opword 0x5406D1BE
		bl __div2i
		opword 0x38E000FF
		opword 0x38A00000
		opword 0x7C043816
		opword 0x38C000C8
		opword 0x7C6339D6
		opword 0x1C8400FF
		opword 0x7C601A14
		bl __div2i
		opword 0xB09F0006
		opword 0xA81F0006
		opword 0x2C0000FF
		opword 0x4081000C
		opword 0x380000FF
		opword 0xB01F0006
		opword 0xA01F0000
		opword 0x28000002
		opword 0x41820154
		opword 0x807F0028
		bl msgMain
		opword 0x2C030002
		opword 0x418200A4
		opword 0x40800140
		opword 0x2C030000
		opword 0x41820010
		opword 0x40800054
		opword 0x48000130
		opword 0x4800012C
		opword 0x38000007
		opword 0xB01F0000
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F0024
		opword 0x901F0020
		opword 0x807F0028
		opword 0x80630000
		opword 0x80030004
		opword 0x54000739
		opword 0x41820010
		opword 0x80637A24
		bl BtlUnit_ChangeStayAnim
		opword 0x480000F0
		opword 0x38637A04
		bl npcSetStayPose
		opword 0x480000E4
		opword 0x38000002
		opword 0xB01F0000
		opword 0xA01F0002
		opword 0x540007FA
		opword 0xB01F0002
		opword 0x807F0028
		opword 0x80630000
		opword 0x80030004
		opword 0x54000739
		opword 0x41820010
		opword 0x80637A24
		bl BtlUnit_ChangeStayAnim
		opword 0x480000B0
		opword 0x38637A04
		bl npcSetStayPose
		opword 0x480000A4
		opword 0x38000003
		opword 0xB01F0000
		opword 0x48000098
		opword 0xA81F0006
		opword 0x2C000000
		opword 0x4082000C
		bl windowDelete
		opword 0x480000CC
		opword 0x3C608000
		lwz r6, gp(r13)
		opword 0x800300F8
		opword 0x3C601062
		opword 0x80A6003C
		opword 0x38634DD3
		opword 0x5400F0BE
		opword 0x809F0024
		opword 0x7C030016
		opword 0x80C60038
		opword 0x7C842810
		opword 0x807F0020
		opword 0x38A00000
		opword 0x7C633110
		opword 0x5406D1BE
		bl __div2i
		opword 0x38E000FF
		opword 0x38A00000
		opword 0x7C043816
		opword 0x38C000C8
		opword 0x7C6339D6
		opword 0x1C8400FF
		opword 0x7C601A14
		bl __div2i
		opword 0x380000FF
		opword 0x38A00000
		opword 0x7C040010
		opword 0xB01F0006
		opword 0xA81F0006
		opword 0x2C000000
		opword 0x41810008
		opword 0xB0BF0006
		opword 0xA89F0004
		opword 0x3C004330
		lis r5, double_to_int_802c4f08@ha
		opword 0x90010008
		opword 0x6C848000
		lfs f2, float_400_8041a530(r2)
		opword 0x9081000C
		addi r6, r5, double_to_int_802c4f08@l
		opword 0xC8260000
		lis r3, msgWindow_Disp@ha
		opword 0xC8010008
		addi r5, r3, msgWindow_Disp@l
		opword 0x7FE6FB78
		opword 0x38600008
		opword 0xEC000828
		opword 0x38800000
		opword 0xEC220028
		bl dispEntry
		opword 0x80010024
		opword 0x83E1001C
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop
#endif

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
__declspec(section ".data") void* jumptable_8030DBA0[] = {
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
__declspec(section ".data") void* jumptable_8030DBD0[] = {
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
__declspec(section ".data") void* jumptable_8030DC00[] = {
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

	GXSetFog(GX_FOG_NONE, EXT_LIT(float_0_8041a514, 0.0f), EXT_LIT(float_0_8041a514, 0.0f), EXT_LIT(float_0_8041a514, 0.0f), EXT_LIT(float_0_8041a514, 0.0f), (GXColor){0, 0, 0, 0});

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
				ex = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(pos.x, ( window->height / EXT_LIT(float_2_8041a524, 2.0f) ) + window->x, 0, window->alpha, 255);
				ey = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(pos.y, window->y - ( window->width / EXT_LIT(float_2_8041a524, 2.0f) ), 0, window->alpha, 255);
				w = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(EXT_LIT(float_10_8041a538, 10.0f), window->height, 0, window->alpha, 255);
				h = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(EXT_LIT(float_10_8041a538, 10.0f), window->width, 0, window->alpha, 255);
				windowDispGX_Message(window->type, window->field_0x2C, window->alpha, ex - ( w / EXT_LIT(float_2_8041a524, 2.0f) ), ey + ( h / EXT_LIT(float_2_8041a524, 2.0f) ), w, h, pos.x, pos.y);
				if (window->alpha == 255) {
					GXSetScissor(camera->scissor[0], 240.0f - (window->y - 36.0f), camera->scissor[2], 100);
					ret = msgDisp(window->userdata, window->alpha, EXT_LIT(float_62_8041a544, 62.0f) + window->x, window->y - 36.0f);
				}
				break;
			case 1:
				window->x = pos.x - ( window->height / EXT_LIT(float_2_8041a524, 2.0f)) ;
				if (window->field_0x2C & 8) {
					window->y = pos.y - 80.0f;
				} else {
					window->y = 60.0f + pos.y;
				}
				ex = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(pos.x, ( window->height / EXT_LIT(float_2_8041a524, 2.0f) ) + window->x, 0, window->alpha, 255);
				ey = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(pos.y, window->y - ( window->width / EXT_LIT(float_2_8041a524, 2.0f) ), 0, window->alpha, 255);
				w = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(EXT_LIT(float_10_8041a538, 10.0f), window->height, 0, window->alpha, 255);
				h = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(EXT_LIT(float_10_8041a538, 10.0f), window->width, 0, window->alpha, 255);
				windowDispGX_Message(window->type, window->field_0x2C, window->alpha, ex - ( w / EXT_LIT(float_2_8041a524, 2.0f) ), ey + ( h / EXT_LIT(float_2_8041a524, 2.0f) ), w, h, pos.x, pos.y);
				if (window->alpha == 255) {
					sy = 240 - ((( s32)window->y ) - 10);
					if (sy < 0) { sy = 0;
					}
					if (sy > 480) { sy = 480;
					}
					GXSetScissor(camera->scissor[0], sy, camera->scissor[2], 0x7E);
					msgDisp(window->userdata, window->alpha, EXT_LIT(float_28_8041a550, 20.0f) + window->x, window->y - 7.0f);
				}
				break;
			}
		} else {
			windowDispGX_Message(window->type, 0, window->alpha, window->x, window->y, window->height, window->width, 0.0f, 0.0f);
			GXSetScissor(camera->scissor[0], ( EXT_LIT(float_240_8041a53c, 240.0f) - (window->y - 36.0f) ) - 8.0f, camera->scissor[2], 0x7E);
			ret = msgDisp(window->userdata, window->alpha, EXT_LIT(float_62_8041a544, 62.0f) + window->x, window->y - 36.0f);
		}
		break;
	case 2:
	case 4:
	case 10:
		windowDispGX_Kanban(window->type, window->alpha, window->x, window->y, window->height, window->width);
		GXSetScissor(camera->scissor[0], ( EXT_LIT(float_240_8041a53c, 240.0f) - (window->y - 36.0f) ) - 2.0f, camera->scissor[2], 0x68);
		ret = msgDisp(window->userdata, window->alpha, EXT_LIT(float_62_8041a544, 62.0f) + window->x, window->y - 36.0f);
		break;
	case 7:
		windowDispGX_Kanban(window->type, window->alpha, window->x, window->y, window->height, window->width);
		GXSetScissor(camera->scissor[0], ( EXT_LIT(float_240_8041a53c, 240.0f) - (window->y - 36.0f) ) - 8.0f, camera->scissor[2], 0x7E);
		ret = msgDisp(window->userdata, window->alpha, EXT_LIT(float_62_8041a544, 62.0f) + window->x, window->y - 36.0f);
		break;
	case 3:
		windowDispGX_System(window->type, window->alpha, window->x, window->y, window->height, window->width);
		GXSetScissor(camera->scissor[0], ( EXT_LIT(float_240_8041a53c, 240.0f) - (window->y - 36.0f) ) - 8.0f, camera->scissor[2], window->width - 50.0f);
		ret = msgDisp(window->userdata, window->alpha, EXT_LIT(float_62_8041a544, 62.0f) + window->x, window->y - 36.0f);
		break;
	case 11:
		GXSetScissor(camera->scissor[0], ( EXT_LIT(float_240_8041a53c, 240.0f) - (window->y - 36.0f) ) - 8.0f, camera->scissor[2], window->width - 50.0f);
		ret = msgDisp(window->userdata, window->alpha, EXT_LIT(float_62_8041a544, 62.0f) + window->x, window->y - 36.0f);
		break;
	case 5:
		break;
	}

	GXSetScissor(camera->scissor[0], camera->scissor[1], camera->scissor[2], camera->scissor[3]);
	if (ret) {
		if (active == 0) { active = 1;
		}
		animPoseMain(msgw->poseId);
		animPoseDraw(msgw->poseId, ( window->x + window->height ) - 52.0f, EXT_LIT(float_31_8041a564, 31.0f) + (window->y - window->width), EXT_LIT(float_0_8041a514, 0.0f), EXT_LIT(float_180_8041a568, 180.0f), EXT_LIT(float_5_8041a56c, 5.0f), 2);
	}
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void msgWindow_Disp(CameraId camId, void* param) {
	asm volatile {
		opword 0x9421FFA0
		opword 0x7C0802A6
		opword 0x90010064
		opword 0xDBE10050
		opword 0xF3E10058
		opword 0xDBC10040
		opword 0xF3C10048
		opword 0xDBA10030
		opword 0xF3A10038
		opword 0x93E1002C
		opword 0x93C10028
		opword 0x93A10024
		opword 0x7C9D2378
		bl camGetCurPtr
		lfs f1, float_0_8041a514(r2)
		opword 0x7C7F1B78
		lwz r0, unk_80422fe0(r2)
		opword 0x38810008
		opword 0xFC400890
		opword 0x3BC00000
		opword 0xFC600890
		opword 0x90010008
		opword 0xFC800890
		opword 0x38600000
		bl GXSetFog
		opword 0x807D0008
		opword 0x2803000B
		opword 0x418105BC
		lis r4, jumptable_8030DB70@ha
		opword 0x5460103A
		addi r4, r4, jumptable_8030DB70@l
		opword 0x7C04002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0xA89D002C
		opword 0x7C800735
		opword 0x41820304
		opword 0x548006F7
		opword 0x41820020
		opword 0x807D0030
		opword 0x801D0034
		opword 0x9061000C
		opword 0x90010010
		opword 0x801D0038
		opword 0x90010014
		opword 0x48000010
		opword 0x387D0030
		opword 0x3881000C
		bl getScreenPoint
		opword 0x801D0008
		opword 0x2C000006
		opword 0x41820034
		opword 0x4080001C
		opword 0x2C000001
		opword 0x4182014C
		opword 0x4080054C
		opword 0x2C000000
		opword 0x4080001C
		opword 0x48000540
		opword 0x2C00000A
		opword 0x40800538
		opword 0x2C000008
		opword 0x40800008
		opword 0x4800052C
		opword 0xC07D0014
		opword 0x38600000
		lfs f2, float_0p5_8041a534(r2)
		opword 0x38A000FF
		opword 0xC01D000C
		opword 0xC021000C
		opword 0xEC4300BA
		opword 0xA89D0006
		bl intplGetValue
		opword 0xC07D0018
		opword 0xFFE00890
		lfs f2, float_0p5_8041a534(r2)
		opword 0x38600000
		opword 0xC01D0010
		opword 0x38A000FF
		opword 0xC0210010
		opword 0xEC4300BC
		opword 0xA89D0006
		bl intplGetValue
		opword 0xFFC00890
		lfs f1, float_10_8041a538(r2)
		opword 0xC05D0014
		opword 0x38600000
		opword 0xA89D0006
		opword 0x38A000FF
		bl intplGetValue
		opword 0xFC000890
		lfs f1, float_10_8041a538(r2)
		opword 0xC05D0018
		opword 0x38600000
		opword 0xA89D0006
		opword 0x38A000FF
		opword 0xFFA00090
		bl intplGetValue
		opword 0xFC400890
		lfs f0, float_0p5_8041a534(r2)
		opword 0xA81D0006
		opword 0xFC60E890
		opword 0xEC3DF83C
		opword 0x807D0008
		opword 0xFC801090
		opword 0xA89D002C
		opword 0xC0A1000C
		opword 0x5405063E
		opword 0xC0C10010
		opword 0xEC44F03A
		bl windowDispGX_Message
		opword 0xA81D0006
		opword 0x2C0000FF
		opword 0x40820464
		opword 0xC03D0010
		lfs f0, float_36_8041a540(r2)
		lfs f2, float_240_8041a53c(r2)
		opword 0xEC010028
		opword 0xEC220028
		bl __cvt_fp2unsigned
		opword 0x7C641B78
		opword 0xA07F00F4
		opword 0xA0BF00F8
		opword 0x38C00064
		bl GXSetScissor
		lfs f1, float_62_8041a544(r2)
		opword 0xC01D000C
		opword 0xA81D0006
		opword 0xC05D0010
		opword 0xEC21002A
		lfs f0, float_36_8041a540(r2)
		opword 0x5404063E
		opword 0x807D0028
		opword 0xEC420028
		bl msgDisp
		opword 0x7C7E1B78
		opword 0x48000408
		opword 0xC05D0014
		lfs f1, float_0p5_8041a534(r2)
		opword 0xC001000C
		opword 0xEC02007C
		opword 0xD01D000C
		opword 0xA81D002C
		opword 0x54000739
		opword 0x41820018
		opword 0xC0210010
		lfs f0, float_80_8041a548(r2)
		opword 0xEC010028
		opword 0xD01D0010
		opword 0x48000014
		lfs f1, float_60_8041a54c(r2)
		opword 0xC0010010
		opword 0xEC01002A
		opword 0xD01D0010
		opword 0xC07D0014
		opword 0x38600000
		lfs f2, float_0p5_8041a534(r2)
		opword 0x38A000FF
		opword 0xC01D000C
		opword 0xC021000C
		opword 0xEC4300BA
		opword 0xA89D0006
		bl intplGetValue
		opword 0xC07D0018
		opword 0xFFC00890
		lfs f2, float_0p5_8041a534(r2)
		opword 0x38600000
		opword 0xC01D0010
		opword 0x38A000FF
		opword 0xC0210010
		opword 0xEC4300BC
		opword 0xA89D0006
		bl intplGetValue
		opword 0xFFE00890
		lfs f1, float_10_8041a538(r2)
		opword 0xC05D0014
		opword 0x38600000
		opword 0xA89D0006
		opword 0x38A000FF
		bl intplGetValue
		opword 0xFFA00890
		lfs f1, float_10_8041a538(r2)
		opword 0xC05D0018
		opword 0x38600000
		opword 0xA89D0006
		opword 0x38A000FF
		bl intplGetValue
		opword 0xFC800890
		lfs f0, float_0p5_8041a534(r2)
		opword 0xA81D0006
		opword 0xFC60E890
		opword 0xEC3DF03C
		opword 0x807D0008
		opword 0xEC44F83A
		opword 0xA89D002C
		opword 0xC0A1000C
		opword 0x5405063E
		opword 0xC0C10010
		bl windowDispGX_Message
		opword 0xA81D0006
		opword 0x2C0000FF
		opword 0x40820304
		opword 0xC01D0010
		opword 0xFC00001E
		opword 0xD8010018
		opword 0x8061001C
		opword 0x3803FFF6
		opword 0x208000F0
		opword 0x2C040000
		opword 0x40800008
		opword 0x38800000
		opword 0x2C0401E0
		opword 0x40810008
		opword 0x388001E0
		opword 0xA07F00F4
		opword 0x38C0007E
		opword 0xA0BF00F8
		bl GXSetScissor
		lfs f1, float_28_8041a550(r2)
		opword 0xC01D000C
		opword 0xA81D0006
		opword 0xC05D0010
		opword 0xEC21002A
		lfs f0, float_6_8041a554(r2)
		opword 0x5404063E
		opword 0x807D0028
		opword 0xEC420028
		bl msgDisp
		opword 0x48000298
		lfs f5, float_0_8041a514(r2)
		opword 0x38800000
		opword 0xA81D0006
		opword 0xFCC02890
		opword 0xC03D000C
		opword 0xC05D0010
		opword 0x5405063E
		opword 0xC07D0014
		opword 0xC09D0018
		bl windowDispGX_Message
		opword 0xC03D0010
		lfs f0, float_36_8041a540(r2)
		lfs f2, float_240_8041a53c(r2)
		opword 0xEC210028
		lfs f0, float_8_8041a558(r2)
		opword 0xEC220828
		opword 0xEC210028
		bl __cvt_fp2unsigned
		opword 0x7C641B78
		opword 0xA07F00F4
		opword 0xA0BF00F8
		opword 0x38C0007E
		bl GXSetScissor
		lfs f1, float_62_8041a544(r2)
		opword 0xC01D000C
		opword 0xA81D0006
		opword 0xC05D0010
		opword 0xEC21002A
		lfs f0, float_36_8041a540(r2)
		opword 0x5404063E
		opword 0x807D0028
		opword 0xEC420028
		bl msgDisp
		opword 0x7C7E1B78
		opword 0x4800020C
		opword 0xA81D0006
		opword 0xC03D000C
		opword 0xC05D0010
		opword 0x5404063E
		opword 0xC07D0014
		opword 0xC09D0018
		bl windowDispGX_Kanban
		opword 0xC03D0010
		lfs f0, float_36_8041a540(r2)
		lfs f2, float_240_8041a53c(r2)
		opword 0xEC210028
		lfs f0, float_2_8041a524(r2)
		opword 0xEC220828
		opword 0xEC210028
		bl __cvt_fp2unsigned
		opword 0x7C641B78
		opword 0xA07F00F4
		opword 0xA0BF00F8
		opword 0x38C00068
		bl GXSetScissor
		lfs f1, float_62_8041a544(r2)
		opword 0xC01D000C
		opword 0xA81D0006
		opword 0xC05D0010
		opword 0xEC21002A
		lfs f0, float_36_8041a540(r2)
		opword 0x5404063E
		opword 0x807D0028
		opword 0xEC420028
		bl msgDisp
		opword 0x7C7E1B78
		opword 0x4800018C
		opword 0xA81D0006
		opword 0xC03D000C
		opword 0xC05D0010
		opword 0x5404063E
		opword 0xC07D0014
		opword 0xC09D0018
		bl windowDispGX_Kanban
		opword 0xC03D0010
		lfs f0, float_36_8041a540(r2)
		lfs f2, float_240_8041a53c(r2)
		opword 0xEC210028
		lfs f0, float_8_8041a558(r2)
		opword 0xEC220828
		opword 0xEC210028
		bl __cvt_fp2unsigned
		opword 0x7C641B78
		opword 0xA07F00F4
		opword 0xA0BF00F8
		opword 0x38C0007E
		bl GXSetScissor
		lfs f1, float_62_8041a544(r2)
		opword 0xC01D000C
		opword 0xA81D0006
		opword 0xC05D0010
		opword 0xEC21002A
		lfs f0, float_36_8041a540(r2)
		opword 0x5404063E
		opword 0x807D0028
		opword 0xEC420028
		bl msgDisp
		opword 0x7C7E1B78
		opword 0x4800010C
		opword 0xA81D0006
		opword 0xC03D000C
		opword 0xC05D0010
		opword 0x5404063E
		opword 0xC07D0014
		opword 0xC09D0018
		bl windowDispGX_System
		opword 0xC03D0018
		lfs f0, float_50_8041a55c(r2)
		opword 0xEC210028
		bl __cvt_fp2unsigned
		opword 0xC03D0010
		opword 0x7C7E1B78
		lfs f0, float_36_8041a540(r2)
		lfs f2, float_240_8041a53c(r2)
		opword 0xEC210028
		lfs f0, float_8_8041a558(r2)
		opword 0xEC220828
		opword 0xEC210028
		bl __cvt_fp2unsigned
		opword 0x7C641B78
		opword 0xA07F00F4
		opword 0xA0BF00F8
		opword 0x7FC6F378
		bl GXSetScissor
		lfs f1, float_62_8041a544(r2)
		opword 0xC01D000C
		opword 0xA81D0006
		opword 0xC05D0010
		opword 0xEC21002A
		lfs f0, float_36_8041a540(r2)
		opword 0x5404063E
		opword 0x807D0028
		opword 0xEC420028
		bl msgDisp
		opword 0x7C7E1B78
		opword 0x48000078
		opword 0xC03D0018
		lfs f0, float_50_8041a55c(r2)
		opword 0xEC210028
		bl __cvt_fp2unsigned
		opword 0xC03D0010
		opword 0x7C7E1B78
		lfs f0, float_36_8041a540(r2)
		lfs f2, float_240_8041a53c(r2)
		opword 0xEC210028
		lfs f0, float_8_8041a558(r2)
		opword 0xEC220828
		opword 0xEC210028
		bl __cvt_fp2unsigned
		opword 0x7C641B78
		opword 0xA07F00F4
		opword 0xA0BF00F8
		opword 0x7FC6F378
		bl GXSetScissor
		lfs f1, float_62_8041a544(r2)
		opword 0xC01D000C
		opword 0xA81D0006
		opword 0xC05D0010
		opword 0xEC21002A
		lfs f0, float_36_8041a540(r2)
		opword 0x5404063E
		opword 0x807D0028
		opword 0xEC420028
		bl msgDisp
		opword 0x7C7E1B78
		opword 0xA07F00F4
		opword 0xA09F00F6
		opword 0xA0BF00F8
		opword 0xA0DF00FA
		bl GXSetScissor
		opword 0x2C1E0000
		opword 0x41820068
		lhz r0, g5_active_s772(r13)
		opword 0x28000000
		opword 0x4082000C
		opword 0x38000001
		sth r0, g5_active_s772(r13)
		lwz r3, msgw(r13)
		opword 0x80630020
		bl animPoseMain
		opword 0xC07D000C
		opword 0x38800002
		opword 0xC05D0014
		opword 0xC03D0010
		opword 0xC01D0018
		opword 0xEC83102A
		lfs f3, float_52_8041a560(r2)
		lwz r3, msgw(r13)
		opword 0xEC010028
		lfs f2, float_31_8041a564(r2)
		opword 0xEC241828
		opword 0x80630020
		opword 0xEC42002A
		lfs f3, float_0_8041a514(r2)
		lfs f4, float_180_8041a568(r2)
		lfs f5, float_5_8041a56c(r2)
		bl animPoseDraw
		opword 0xE3E10058
		opword 0xCBE10050
		opword 0xE3C10048
		opword 0xCBC10040
		opword 0xE3A10038
		opword 0xCBA10030
		opword 0x83E1002C
		opword 0x83C10028
		opword 0x80010064
		opword 0x83A10024
		opword 0x7C0803A6
		opword 0x38210060
	}
}
#pragma pop
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
	dispEntry(CAMERA_2D, EXT_LIT(float_400_8041a530, 400.0f) - *(s16*)&window->field_0x4, 0, selectWindow_Disp, window);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void selectWindow_Main(WindowEntry* window) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		opword 0x93C10018
		opword 0x93A10014
		opword 0x7C7D1B78
		opword 0x80630028
		opword 0x83E30000
		bl msgMain
		opword 0xA01D0000
		opword 0x2C000005
		opword 0x4182002C
		opword 0x4080001C
		opword 0x2C000001
		opword 0x4182004C
		opword 0x41800258
		opword 0x2C000004
		opword 0x40800298
		opword 0x4800024C
		opword 0x2C000007
		opword 0x418201FC
		opword 0x48000240
		opword 0xA87D0006
		opword 0x38030019
		opword 0xB01D0006
		opword 0xA81D0006
		opword 0x2C0000FF
		opword 0x40810228
		opword 0x386000FF
		opword 0x38000001
		opword 0xB07D0006
		opword 0xB01D0000
		opword 0x48000214
		opword 0x8BDF7A43
		opword 0x38600000
		bl keyGetButtonTrg
		opword 0x54600739
		opword 0x40820014
		opword 0x38600000
		bl keyGetDirTrg
		opword 0x546004E7
		opword 0x41820014
		opword 0x887F7A43
		opword 0x3803FFFF
		opword 0x981F7A43
		opword 0x48000038
		opword 0x38600000
		bl keyGetButtonRep
		opword 0x54600739
		opword 0x40820014
		opword 0x38600000
		bl keyGetDirRep
		opword 0x546004E7
		opword 0x41820018
		opword 0x887F7A43
		opword 0x7C600775
		opword 0x4182000C
		opword 0x3803FFFF
		opword 0x981F7A43
		opword 0x38600000
		bl keyGetButtonTrg
		opword 0x5460077B
		opword 0x40820014
		opword 0x38600000
		bl keyGetDirTrg
		opword 0x546004A5
		opword 0x41820014
		opword 0x887F7A43
		opword 0x38030001
		opword 0x981F7A43
		opword 0x48000048
		opword 0x38600000
		bl keyGetButtonRep
		opword 0x5460077B
		opword 0x40820014
		opword 0x38600000
		bl keyGetDirRep
		opword 0x546004A5
		opword 0x41820028
		opword 0x881F7A40
		opword 0x88BF7A43
		opword 0x7C030774
		opword 0x7CA40774
		opword 0x3803FFFF
		opword 0x7C040000
		opword 0x4080000C
		opword 0x38050001
		opword 0x981F7A43
		opword 0x881F7A43
		opword 0x7C000775
		opword 0x40800010
		opword 0x887F7A40
		opword 0x3803FFFF
		opword 0x981F7A43
		opword 0x887F7A43
		opword 0x881F7A40
		opword 0x7C630774
		opword 0x7C000774
		opword 0x7C030000
		opword 0x4180000C
		opword 0x38000000
		opword 0x981F7A43
		opword 0x881F7A43
		opword 0x7FC30774
		opword 0x7C000774
		opword 0x7C030000
		opword 0x41820010
		opword 0x3C600002
		opword 0x38630005
		bl psndSFXOn
		opword 0x38600000
		bl keyGetButtonTrg
		opword 0x546005AD
		opword 0x41820060
		opword 0x887F7A42
		opword 0x7C600774
		opword 0x2C00FFFF
		opword 0x418200C0
		opword 0x40800030
		opword 0x2C00FFFE
		opword 0x40800008
		opword 0x48000024
		opword 0x3800FFFF
		opword 0x3C600002
		opword 0x981F7A43
		opword 0x38000007
		opword 0x38630013
		opword 0xB01D0000
		bl psndSFXOn
		opword 0x48000090
		opword 0x987F7A43
		opword 0x38000007
		opword 0x3C600002
		opword 0xB01D0000
		opword 0x38630013
		bl psndSFXOn
		opword 0x48000074
		opword 0x38600000
		bl keyGetButtonTrg
		opword 0x546005EF
		opword 0x41820064
		opword 0x38000007
		opword 0x3C600002
		opword 0xB01D0000
		opword 0x38630012
		bl psndSFXOn
		opword 0x4800004C
		opword 0xA87D0006
		opword 0x2C030000
		opword 0x4082001C
		opword 0x38000004
		opword 0xB01D0000
		opword 0xA01D0002
		opword 0x540007FA
		opword 0xB01D0002
		opword 0x48000070
		opword 0x3803FFE7
		opword 0xB01D0006
		opword 0xA81D0006
		opword 0x2C000000
		opword 0x41810014
		opword 0x38000000
		opword 0xB01D0006
		opword 0x48000008
		opword 0x4800004C
		opword 0xA89D0004
		opword 0x3C004330
		lis r5, double_to_int_802c4f08@ha
		opword 0x90010008
		opword 0x6C848000
		lfs f2, float_400_8041a530(r2)
		opword 0x9081000C
		addi r6, r5, double_to_int_802c4f08@l
		opword 0xC8260000
		lis r3, selectWindow_Disp@ha
		opword 0xC8010008
		addi r5, r3, selectWindow_Disp@l
		opword 0x7FA6EB78
		opword 0x38600008
		opword 0xEC000828
		opword 0x38800000
		opword 0xEC220028
		bl dispEntry
		opword 0x80010024
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x83A10014
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
void selectWindow_Disp(CameraId camId, void* param) {
	WindowEntry* window = param; //cast to correct type
	MsgWinData* data = window->userdata->address;
	Vec pos;

	GXSetFog(GX_FOG_NONE, EXT_LIT(float_0_8041a514, 0.0f), EXT_LIT(float_0_8041a514, 0.0f), EXT_LIT(float_0_8041a514, 0.0f), EXT_LIT(float_0_8041a514, 0.0f), (GXColor){0, 0, 0, 0});
	windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, window->alpha}, window->x, window->y, window->height, window->width, EXT_LIT(float_30_8041a518, 30.0f));
	msgDisp(window->userdata, window->alpha, EXT_LIT(float_40_8041a51c, 40.0f) + window->x, window->y - 25.0f);
	pos.x = EXT_LIT(float_2_8041a524, 2.0f) + window->x;
	data->cursorY += EXT_LIT(float_0p3_8041a528, 0.3f) * (window->y - (f32)(data->sel * 31 + 58) - data->cursorY);
	pos.y = data->cursorY;
	pos.z = EXT_LIT(float_0_8041a514, 0.0f);
	iconDispGxAlpha(&pos, 0x14, 0x1F0, window->alpha, EXT_LIT(float_1_8041a52c, 1.0f));
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void selectWindow_Disp(CameraId camId, void* param) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		lfs f1, float_0_8041a514(r2)
		opword 0x90010034
		opword 0xFC400890
		opword 0x93E1002C
		opword 0xFC600890
		opword 0xFC800890
		opword 0x93C10028
		opword 0x7C9E2378
		opword 0x80640028
		opword 0x38810010
		lwz r0, unk_80422fe4(r2)
		opword 0x83E30000
		opword 0x38600000
		opword 0x90010010
		bl GXSetFog
		lwz r5, dat_8041a510(r2)
		opword 0x3881000C
		opword 0xA81E0006
		opword 0x38600000
		opword 0x90A10008
		lfs f5, float_30_8041a518(r2)
		opword 0x9801000B
		opword 0x80010008
		opword 0x9001000C
		opword 0xC03E000C
		opword 0xC05E0010
		opword 0xC07E0014
		opword 0xC09E0018
		bl windowDispGX_Waku_col
		lfs f1, float_40_8041a51c(r2)
		opword 0xC01E000C
		opword 0xA81E0006
		opword 0xC05E0010
		opword 0xEC21002A
		lfs f0, float_25_8041a520(r2)
		opword 0x5404063E
		opword 0x807E0028
		opword 0xEC420028
		bl msgDisp
		lfs f1, float_2_8041a524(r2)
		opword 0x3C004330
		opword 0xC01E000C
		lis r3, double_to_int_802c4f08@ha
		lfd f4, double_to_int_802c4f08@l(r3)
		opword 0x38610014
		opword 0xEC21002A
		opword 0x90010020
		lfs f6, float_0p3_8041a528(r2)
		opword 0x38800014
		lfs f0, float_0_8041a514(r2)
		opword 0x38A001F0
		opword 0xD0210014
		lfs f1, float_1_8041a52c(r2)
		opword 0x881F7A43
		opword 0xC0BE0010
		opword 0x7C000774
		opword 0xC07F7A48
		opword 0x1CC0001F
		opword 0x3806003A
		opword 0x6C008000
		opword 0x90010024
		opword 0xC8410020
		opword 0xEC422028
		opword 0xEC451028
		opword 0xEC421828
		opword 0xEC4618BA
		opword 0xD05F7A48
		opword 0xC05F7A48
		opword 0xD0410018
		opword 0xD001001C
		opword 0xA81E0006
		opword 0x5406063E
		bl iconDispGxAlpha
		opword 0x80010034
		opword 0x83E1002C
		opword 0x83C10028
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop
#endif


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".sdata") u32 gap_07_804103F4_sdata[1] = {0};

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".sdata2") const char str_8041A4B0[8] = "PAD_A\0\0";
__declspec(section ".sdata2") const char str_8041A4B8[8] = "PAD_B\0\0";
__declspec(section ".sdata2") const char str_8041A4C0[8] = "STICK\0\0";
__declspec(section ".sdata2") const char str_8041A4C8[8] = "AC_ON\0\0";
__declspec(section ".sdata2") const char str_8041A4D0[4] = "HM\0";
__declspec(section ".sdata2") const char str_8041A4D4[8] = "PAD_X\0\0";
__declspec(section ".sdata2") const char str_8041A4DC[8] = "PAD_Y\0\0";
__declspec(section ".sdata2") const char str_8041A4E4[4] = "msg";
__declspec(section ".sdata2") const char str_8041A4E8[8] = "emsg\0\0\0";
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
__declspec(section ".sdata2") const char str_8041A6A4[8] = "%s/%s\0\0";
__declspec(section ".sdata2") const u32 gap_09_8041A6AC_sdata2 = 0x00000000;
#endif
