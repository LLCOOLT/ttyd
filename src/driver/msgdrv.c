#include "driver/msgdrv.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/icondrv.h"
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

#define WIN_STATE(w) (*(u16*)(w)->field_0x0)

typedef struct MsgWinData {
	const char* tag; //0x0
	u32 flags; //0x4
	u8 field_0x8[0xA - 0x8]; //0x8
	s16 field_0xA; //0xA
	u8 field_0xC[0x10 - 0xC]; //0xC
	s32 field_0x10; //0x10
	u8 field_0x14[0x18 - 0x14]; //0x14
	OSTime time18; //0x18
	s32 field_0x20; //0x20
	s32 field_0x24; //0x24
	s32 field_0x28; //0x28
	u8 field_0x2C[0x30 - 0x2C]; //0x2C
	OSTime time30; //0x30
	s32 count; //0x38
	u8 field_0x3C[0x783C - 0x3C]; //0x3C
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

typedef struct MsgLookupEntry {
	u32 startaddr; //0x0
	u32 endaddr; //0x4
} MsgLookupEntry;

typedef struct MsgIcon {
	const char* name; //0x0
	s32 value; //0x4
} MsgIcon;

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
u16 active; //TODO: re-type
void* msgSortDvdData; //TODO: re-type
BOOL msgSEflag; //msgSEInit and related functions are unused
MessageWork msgWork;

//.sdata
MessageWork* msgw = &msgWork;
const char* ErrMessage[2] = {
	"<col ff0000ff>\x83\x81\x83\x62\x83\x5A\x81\x5B\x83\x57\x82\xAA\x82\xA0\x82\xE8\x82\xDC\x82\xB9\x82\xF1</col>\n<key>", /*"メッセージがありません"*/
	"<col ff0000ff>No messages.<col>\n<key>"
};
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
	msgLoad("global", 1);
}

void msgLoad(const char* filename, s32 index) {
	MessageEntry* entry;
	u32 r30;
	MsgLookupEntry* lookup;
	char* msgptr;
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
		msgptr = entry->address;
		msgcount = 0;
		while (*(s8*)msgptr) {
			msgptr += strlen(msgptr);
			msgcount++;
			msgptr++;
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

//s32 msgMain(void* somearray)

#pragma dont_inline on
BOOL msgDisp(smartEntry* smart, u8 alpha, f32 x, f32 y) {

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

void msgAnalize(smartEntry* smart, char* msg) {
	MessageData* data;
	MsgDataEntry* entry;
	WindowEntry* window;
	s32 smth_7A30;
	char check;
	BOOL checkkanji;
	u16 glyph, width;
	u32 r23;

	data = smart->address;
	window = data->window;
	r23 = 0;
	//r1+0x50 = 1.0f;
	entry = &data->entries[data->entryId];
	if (window->type < 0) {
		window->type = 0;
	}
	smth_7A30 = data->field_0x7A30;
	//s16 r1+0x234 = 0;
	//s16 r1+0x232 = 0;
	//s16 r1+0x230 = 0;
	//s32 r1+0x54 = 0;
	switch (window->type) {
	case 3:
	case 8:
		switch (window->type) {
		case 3:
			entry->field_0x0 = 0xDCC8DCFF; //(GXColor){0xDC, 0xC8, 0xDC, 0xFF};
			break;
		case 8:
			entry->field_0x0 = 0x00D914FF;//(GXColor){0x00, 0xD9, 0x14, 0xFF};
			break;
		}
		entry->glyph = 0xFFF7;
		entry->field_0xC = smth_7A30;
		entry++; //next entry
		data->entryId++; //next entry
		break;

	default:
		break;
	}

	check = *msg;
	if ((check < 0x81 && check <= 0x9F) || (check < 0xE0 && check > 0xFC)) {
		checkkanji = TRUE;
	}
	else {
		checkkanji = FALSE;
	}
	if (checkkanji) {
		glyph = kanjiSearch(*(u16*)msg);
		width = kanjiGetWidth(glyph);
		entry->glyph = glyph;


		entry->field_0x0 = r23;
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

	for (i = 0, icon = msgIcon; i < 18; i++, icon++) {
		if (!strcmp(icon->name, str)) {
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
	d->page++;
	if (d->field_0x7840 - 1 < d->page) {
		d->page = d->field_0x7840 - 1;
	}
}

#pragma opt_common_subs off
void msgWindow_Main(WindowEntry* window) {
	smartEntry* smart = window->userdata;
	MsgWinData* data = smart->address;
	s32 se;
	s32 target;

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
		if (keyGetButtonTrg(0) & (target | 0x200)) {
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
		if (keyGetButtonTrg(0) & target) {
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
	WindowEntry* window = param; //cast to correct type
	CameraEntry* camera = camGetCurPtr();
	s32 type;

	GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0, 0, 0, 0});
	type = window->type;

	switch (type) {
	case 0:
	case 1:
	case 6:
	case 8:
	case 9:
		break;
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
	{
		GXColor color = {0xFF, 0xFF, 0xFF, 0x00};
		color.a = window->alpha;
		windowDispGX_Waku_col(0, color, window->x, window->y, window->height, window->width, 30.0f);
	}
	msgDisp(window->userdata, window->alpha, 40.0f + window->x, window->y - 25.0f);
	pos.x = 2.0f + window->x;
	data->cursorY += 0.3f * (window->y - (f32)(data->sel * 31 + 58) - data->cursorY);
	pos.y = data->cursorY;
	pos.z = 0.0f;
	iconDispGxAlpha(&pos, 0x14, 0x1F0, window->alpha, 1.0f);
}
