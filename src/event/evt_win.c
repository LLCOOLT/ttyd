#include "evt/evt_cmd.h"
#include "driver/icondrv.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/hitdrv.h"
#include "driver/mapdrv.h"
#include "driver/msgdrv.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "manager/fontmgr.h"
#include "manager/winmgr.h"
#include "mario/mario.h"
#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "data/item_data.h"
#include "memory.h"
#include "party.h"
#include "system.h"
#include <dolphin/mtx.h>
#include <stdio.h>
#include <string.h>

extern ItemData itemDataTable[];
extern GlobalWork* gp;

void mapObjGetPos(const char* name, Vec* pos);
void mapObjFlagOn(const char* name, u32 flags);
void mapObjFlagOff(const char* name, u32 flags);
void FontDrawString(f32 x, f32 y, const char* str);
void FontDrawEdge(void);
void FontDrawEdgeOff(void);
BOOL winGhostDiaryChk(void);
BOOL N_itemPickUpFromFieldCheck(void);
s32 marioKeyOn(void);

typedef struct UnitWinEntry {
	const char* mapObj; // 0x0
	const char* hitName; // 0x4
	void* evt;          // 0x8
} UnitWinEntry;

typedef struct UnitWinWork {
	u16 flags;             // 0x0
	u16 pad2;              // 0x2
	UnitWinEntry* entries; // 0x4
	s32* goods;            // 0x8
	u16 itemFlags[6];      // 0xC
	s32 goodsMax;          // 0x18
	EventEntry* evt;       // 0x1C
	EventEntry* childEvt;  // 0x20
	s32 goodsIdx;          // 0x24
	s32 timer;             // 0x28
	s32 coin;              // 0x2C
	s32 coinDisp;          // 0x30
	u8 pad34[0x50 - 0x34]; // 0x34
	s32 field_0x50;        // 0x50
	u16 flags2;            // 0x54
	u8 pad56[0x5C - 0x56]; // 0x56
	s32 field_0x5C;        // 0x5C
	s32 winId[3];          // 0x60
	u8 pad6C[0xE0 - 0x6C]; // 0x6C
	s32 selected;          // 0xE0
	s32 bought;            // 0xE4
} UnitWinWork;

static UnitWinWork* _wp;
s32 unk_804189fc;
static s16* mario_status_point_table[3];

USER_FUNC(evt_unitwin_main_func);
USER_FUNC(unk_80174e98);
void evt_unitwin_disp_func(CameraId cameraId, void* param);
void unk_8017597c(WinMgrEntry* entry);
void unk_801758fc(WinMgrEntry* entry);
void unk_80175710(WinMgrEntry* entry);
void unk_8017599c(WinMgrEntry* entry);

WinMgrDesc unk_80375478[3] = {
	{0, 0, 8, -150, 120, 300, 50, {0x2B, 0xA4, 0xFF, 0xFF}, NULL, unk_8017599c},
	{0, 0, 8, -240, -130, 500, 80, {0xF0, 0xF0, 0xF0, 0xFF}, unk_8017597c, unk_801758fc},
	{2, 0, 8, -250, -130, 150, 45, {0xF0, 0xF0, 0xF0, 0xFF}, NULL, unk_80175710},
};

static s32 party_id_table[8] = {1, 2, 5, 4, 6, 3, 7, 0};
static s32 party_icon_table[7] = {0x155, 0x156, 0x15F, 0x158, 0x160, 0x157, 0x161};
static const char* party_labelname_table[7] = {"_kur", "_nok", "_win", "_yos", "_viv", "_bom", "_chu"};
static s32 mario_status_icon_table[3] = {0x19F, 0x1A0, 0x1A1};
static const char* mario_status_labelname_table[3] = {"_hp", "_fp", "_bp"};
static const char* mario_status_name_table[3] = {"\x82\x67\x82\x6F", "\x82\x65\x82\x6F", "\x82\x61\x82\x6F"};
static s32 mario_status_henka_table[3] = {5, 5, 3};

static EVT_BEGIN(main_evt)
	CALL(evt_unitwin_main_func)
	RETURN
EVT_END()

EVT_BEGIN(select_evt)
	CALL(unk_80174e98)
	RETURN
EVT_END()

void unk_8017599c(WinMgrEntry* entry) {
	UnitWinWork* wp = _wp;
	const char* msg = msgSearch(itemDataTable[wp->goods[wp->goodsIdx]].name);
	s32 i;
	if (!winMgrAction(wp->winId[0])) {
		FontDrawStart();
		FontDrawEdge();
		FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
		FontDrawString(-FontGetMessageWidth(msg) / 2, 108.0f, msg);
		FontDrawEdgeOff();
	}
	for (i = 0; i < wp->goodsMax; i++) {
		if (!(wp->itemFlags[i] & 1)) {
			Mtx mtx;
			char buf[64];
			Vec pos;
			mapObjGetPos(wp->entries[i].mapObj, &pos);
			pos.y += 30.0f;
			PSMTXMultVec(camGetPtr(4)->view, &pos, &pos);
			PSMTX44MultVec(camGetPtr(4)->projection, &pos, &pos);
			pos.x *= gp->fbWidth / 2.0f;
			pos.y *= gp->efbHeight / 2.0f;
			sprintf(buf, "%d", itemDataTable[wp->goods[i]].discount_price);
			PSMTXTrans(mtx, 12.0f * (strlen(buf) - 1) + pos.x, pos.y, pos.z);
			iconNumberDispGx(mtx, itemDataTable[wp->goods[i]].discount_price, 0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
		}
	}
}

void unk_8017597c(WinMgrEntry* entry) {
	winMgrHelpMain(entry);
}

void unk_801758fc(WinMgrEntry* entry) {
	UnitWinWork* wp = _wp;
	s32 idx = wp->goodsIdx * 4;
	s32* goods = wp->goods;
	if (!winMgrAction(wp->winId[1])) {
		entry->msg = msgSearch(itemDataTable[*(s32*)((u8*)goods + idx)].description);
		winMgrHelpDraw(entry);
	}
}

void unk_80175710(WinMgrEntry* entry) {
	UnitWinWork* wp = _wp;
	PouchData* pouch = pouchGetPtr();
	Mtx trans;
	Mtx scale;
	s32 d;
	if (!(entry->flags & 4)) {
		PSMTXTrans(trans, 10.0f + (30.0f + entry->x), entry->y - 36.0f, 0.0f);
		if ((u32)gp->language == 0) {
			PSMTXScale(scale, 1.1f, 1.1f, 1.1f);
			PSMTXConcat(trans, scale, trans);
			iconDispGx2(trans, 0x10, 0x1F1);
		} else {
			PSMTXScale(scale, 0.8f, 1.1f, 1.1f);
			PSMTXConcat(trans, scale, trans);
			iconDispGx2(trans, 0x10, 0x20A);
		}
		PSMTXTrans(trans, 124.0f + entry->x, entry->y - 38.0f, 0.0f);
		{
			GXColor c = {0xFF, 0xFF, 0xFF, 0xFF};
			iconNumberDispGx(trans, wp->coinDisp, 0, c);
		}
		d = *(s16*)&pouch->mShopPoints - wp->coinDisp;
		if (d) {
			d /= 10;
			if (!d) {
				d = *(s16*)&pouch->mShopPoints > wp->coinDisp ? 1 : -1;
			}
			wp->coinDisp += d;
		}
	}
}

USER_FUNC(evt_unitwin_alloc) {
	s32 arg = evtGetValue(event, event->args[0]);
	UnitWinWork* wp = _mapAlloc(sizeof(UnitWinWork));
	memset(wp, 0, sizeof(UnitWinWork));
	wp->field_0x50 = 0;
	_wp = wp;
	if (arg) {
		wp->flags |= 0x80;
	} else {
		wp->flags &= ~0x80;
	}
	iconEntry2D("yubicursor_2", 0x1F0);
	iconFlagOn("yubicursor_2", 2);
	iconFlagOn("yubicursor_2", 4);
	if (!(wp->flags & 0x80)) {
		wp->evt = evtEntry(main_evt, 0, 0);
		wp->evt->lwData[0] = (s32)wp;
	}
	mario_status_point_table[0] = &pouchGetPtr()->baseMaxHP;
	mario_status_point_table[1] = &pouchGetPtr()->baseMaxFP;
	mario_status_point_table[2] = &pouchGetPtr()->maximumBP;
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_unitwin_free) {
	UnitWinWork* wp = _wp;
	s32 i;
	char name[32];
	if (wp == NULL) {
		return EVT_RETURN_DONE;
	}
	if (isFirstCall) {
		wp->flags2 |= 1;
	}
	if (!(wp->flags2 & 2)) {
		return EVT_RETURN_BLOCK;
	}
	for (i = 0; i < wp->goodsMax; i++) {
		mapObjFlagOff(wp->entries[i].mapObj, 0x4000);
		sprintf(name, "uwn%d", i);
		iconDelete(name);
	}
	if (wp->flags & 0x80) {
		for (i = 0; i < 3; i++) {
			winMgrDelete(wp->winId[i]);
		}
	}
	iconDelete("yubicursor_2");
	_mapFree(_wp);
	_wp = NULL;
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_unitwin_selltable_setup) {
	s32 i;
	s32* args = event->args;
	UnitWinEntry* tbl = (UnitWinEntry*)evtGetValue(event, args[0]);
	s32* goods = (s32*)evtGetValue(event, args[1]);
	UnitWinWork* wp = _wp;
	char name[32];
	Vec pos;
	wp->entries = tbl;
	wp->goods = goods;
	wp->goodsMax = 0;
	for (i = 0; wp->entries[i].mapObj != NULL; i++) {
		wp->goodsMax++;
		mapObjGetPos(wp->entries[i].mapObj, &pos);
		mapObjFlagOn(wp->entries[i].mapObj, 0x4000);
		if (wp->goods[i] != 0) {
			sprintf(name, "uwn%d", i);
			((void (*)(const char*, u16))iconEntry)(name, itemDataTable[wp->goods[i]].icon_id);
			iconSetPos(name, pos.x, pos.y + 6.0f, pos.z);
			iconFlagOn(name, 0x40);
		} else {
			wp->itemFlags[i] |= 1;
		}
	}
	wp->evt = evtEntryType(select_evt, 0, 0x20, 0);
	wp->evt->lwData[0] = (s32)wp;
	for (i = 0; i < 3; i++) {
		wp->winId[i] = winMgrEntry(&unk_80375478[i]);
	}
	wp->selected = -1;
	return EVT_RETURN_DONE;
}

USER_FUNC(unitwincoin_disp_onoff) {
	s32 on = evtGetValue(event, event->args[0]);
	UnitWinWork* wp;
	pouchGetPtr();
	wp = _wp;
	wp->coin = pouchGetCoin();
	wp->field_0x5C = 0;
	if (on) {
		wp->flags |= 0x1000;
	} else {
		wp->flags &= ~0x1000;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(unitwincoin_wait) {
	UnitWinWork* wp = _wp;
	pouchGetPtr();
	if (wp->coin != pouchGetCoin()) {
		return EVT_RETURN_BLOCK;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(unk_8017524c) {
	s32 on = evtGetValue(event, event->args[0]);
	UnitWinWork* wp = _wp;
	if (on) {
		wp->flags |= 0x100;
	} else {
		wp->flags &= ~0x100;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(unk_801751f8) {
	s32* args = event->args;
	UnitWinWork* wp = (UnitWinWork*)evtGetValue(event, args[0]);
	wp->bought = evtGetValue(event, args[1]);
	return EVT_RETURN_DONE;
}

#define UNITWIN_CLOSE(wp)                \
	if ((wp)->selected != -1) {          \
		(wp)->selected = -1;             \
		winMgrClose((wp)->winId[0]);     \
		winMgrClose((wp)->winId[1]);     \
	}

USER_FUNC(unk_80174e98) {
	UnitWinWork* wp = (UnitWinWork*)event->lwData[0];
	s32 found = FALSE;
	MarioWork* mario = marioGetPtr();
	PartyEntry* party = partyGetPtr(0);
	HitEntry* hit = mario->hitobjStandOn;
	u32 btn;
	s32 i;
	char name[32];
	MapObject* obj;
	if (wp->flags2 & 1) {
		wp->flags2 |= 2;
		return EVT_RETURN_DONE;
	}
	wp->flags &= ~1;
	btn = keyGetButtonTrg(0);
	if ((marioChkCtrl() ? FALSE : TRUE) || (marioChkKey() ? FALSE : TRUE)) {
		btn = 0;
	}
	if (party != NULL && (party->flags & 0x100)) {
		UNITWIN_CLOSE(wp);
		return EVT_RETURN_BLOCK;
	}
	if (winGhostDiaryChk() || N_itemPickUpFromFieldCheck()) {
		UNITWIN_CLOSE(wp);
		return EVT_RETURN_BLOCK;
	}
	if (!(wp->flags & 2)) {
		if (hit != NULL) {
			for (i = 0; i < wp->goodsMax; i++) {
				const char* hitName = hitGetName(hit);
				if (!strcmp(wp->entries[i].hitName, hitName)) {
					break;
				}
			}
			if (!(wp->itemFlags[i] & 1) && i < wp->goodsMax) {
				if (wp->selected != i) {
					if (wp->selected == -1) {
						winMgrOpen(wp->winId[0]);
						winMgrOpen(wp->winId[1]);
					}
					wp->selected = i;
					wp->goodsIdx = i;
					winMgrHelpInit(winMgrGetPtr(wp->winId[1]));
				}
				found = TRUE;
			}
		}
		if (!found) {
			UNITWIN_CLOSE(wp);
		}
		if (wp->selected != -1) {
			wp->flags |= 1;
			if (btn & 0x100) {
				marioKeyOff();
				wp->childEvt = evtEntry(wp->entries[wp->goodsIdx].evt, 0, 0);
				wp->childEvt->lwData[0] = (s32)wp;
				wp->flags |= 2;
				winMgrClose(wp->winId[0]);
				winMgrClose(wp->winId[1]);
				wp->selected = -1;
				wp->bought = 0;
			}
		}
	} else if (!evtCheckID(wp->childEvt->eventId)) {
		wp->flags &= ~2;
		marioKeyOn();
		if (wp->bought) {
			wp->itemFlags[wp->goodsIdx] |= 1;
		}
	}
	for (i = 0; i < wp->goodsMax; i++) {
		obj = mapGetMapObj(wp->entries[i].mapObj);
		if (obj != NULL) {
			sprintf(name, "uwn%d", i);
			if (wp->itemFlags[i] & 1) {
				iconFlagOn(name, 2);
			} else if (obj->flags & 1) {
				iconFlagOn(name, 2);
			} else {
				iconFlagOff(name, 2);
			}
		}
	}
	return EVT_RETURN_BLOCK;
}

USER_FUNC(evt_unitwin_main_func) {
	UnitWinWork* wp = (UnitWinWork*)event->lwData[0];
	if (wp->flags2 & 1) {
		wp->flags2 |= 2;
		return EVT_RETURN_DONE;
	}
	if (wp->timer > 0) {
		wp->timer--;
	} else {
		wp->flags &= ~1;
	}
	dispEntry((CameraId)8, 1000.0f, 0, evt_unitwin_disp_func, wp);
	return EVT_RETURN_BLOCK;
}

USER_FUNC(set_new_goods_list) {
	s32* args = event->args;
	UnitWinWork* wp = (UnitWinWork*)evtGetValue(event, args[0]);
	s32 item = evtGetValue(event, args[1]);
	char name[32];
	wp->goods[wp->goodsIdx] = item;
	if (wp->goodsIdx < wp->goodsMax) {
		sprintf(name, "uwn%d", wp->goodsIdx);
		if (item != 0) {
			((void (*)(char*, u16))iconChange)(name, itemDataTable[item].icon_id);
		} else {
			iconDelete(name);
		}
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(unitwin_get_work_ptr) {
	evtSetValue(event, event->args[0], (s32)_wp);
	return EVT_RETURN_DONE;
}

USER_FUNC(unitwin_getpartylank) {
	s32* args = event->args;
	PouchData* pouch = pouchGetPtr();
	s32 idx = evtGetValue(event, args[0]);
	evtSetValue(event, args[1], pouch->partyData[idx].techLevel);
	return EVT_RETURN_DONE;
}

#define PP ((PouchPartyData*)((u8*)pouch + idx))
USER_FUNC(unitwin_setpartylank) {
	s32 idx;
	s16 v;
	s32* args = event->args;
	PouchData* pouch = pouchGetPtr();
	idx = evtGetValue(event, args[0]) * 14;
	v = evtGetValue(event, args[1]);
	PP->techLevel = PP->attackLevel = PP->HPLevel = v;
	pouchRevisePartyParam();
	PP->currentHP = PP->maximumHP;
	return EVT_RETURN_DONE;
}
#undef PP

USER_FUNC(unitwin_setmariolevel) {
	s32* args = event->args;
	PouchData* pouch = pouchGetPtr();
	s32 i;
	BOOL r;
	pouch->baseMaxHP = evtGetValue(event, args[0]);
	pouch->baseMaxFP = evtGetValue(event, args[1]);
	pouch->maximumBP = evtGetValue(event, args[2]);
	pouchReviseMarioParam();
	pouch->currentHP = pouch->maximumHP;
	pouch->currentFP = pouch->maximumFP;
	if (pouch->availableBP < 0) {
		for (i = 0; i < 200; i++) {
			if (pouchEquipCheckBadgeIndex(i)) {
				pouchUnEquipBadgeIndex(i);
			}
		}
		pouchReviseMarioParam();
		r = TRUE;
	} else {
		r = FALSE;
	}
	evtSetValue(event, args[3], r);
	return EVT_RETURN_DONE;
}
