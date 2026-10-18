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
#include "driver/windowdrv.h"
#include "evt/evt_badgeshop.h"
#include "evt/evt_johoya.h"
#include "evt/evt_lottery.h"
#include "pmario_sound.h"
#include "memory.h"
#include "party.h"
#include "system.h"
#include <dolphin/mtx.h>
#include <stdio.h>
#include <string.h>
extern const char str_802F68B0[];
extern const char str_8041D958[];
extern const char str_8041D960[];
extern const char str_8041D968[];
extern const char str_8041D970[];
extern const char str_8041D978[];
extern const char str_8041D980[];
extern const char str_8041D988[];
extern const char str_8041D990[];
extern const char str_8041D994[];
extern const char str_8041D998[];
extern const char str_8041D99C[];
extern const char str_8041D9A4[];
extern const char str_8041D9AC[];

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
void statusWinForceUpdateCoin(void);
void FontDrawScale(f32 scale);
s16 johoya_get(u8* table, s16 id);
extern BadgeShopWork* bdsw;
extern s32 badge_bottakuru100_table[];
extern InformantWork _jdt;
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
	f32 cursor;            // 0x34
	u8 pad38[4];           // 0x38
	f32 cursorX;           // 0x3C
	f32 cursorY;           // 0x40
	f32 scroll;            // 0x44
	u8 pad48[4];           // 0x48
	s32 field_0x4C;        // 0x4C
	s32 field_0x50;        // 0x50
	u16 flags2;            // 0x54
	u8 pad56[2];           // 0x56
	s32 count;             // 0x58
	s32 field_0x5C;        // 0x5C
	s32 winId[3];          // 0x60
	u8 pad6C[0xE0 - 0x6C]; // 0x6C
	s32 selected;          // 0xE0
	s32 bought;            // 0xE4
} UnitWinWork;

#pragma force_active on
__declspec(section ".sdata") u32 gap_08_80418A0C_sbss[1];
static s16* mario_status_point_table[3];
s32 unk_804189fc;
static UnitWinWork* _wp;

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
static const char* party_labelname_table[7] = {((char*)str_8041D958), ((char*)str_8041D960), ((char*)str_8041D968), ((char*)str_8041D970), ((char*)str_8041D978), ((char*)str_8041D980), ((char*)str_8041D988)};
static s32 mario_status_icon_table[3] = {0x19F, 0x1A0, 0x1A1};
static const char* mario_status_labelname_table[3] = {((char*)str_8041D990), ((char*)str_8041D994), ((char*)str_8041D998)};
static const char* mario_status_name_table[3] = {((char*)str_8041D99C), ((char*)str_8041D9A4), ((char*)str_8041D9AC)};
static s32 mario_status_henka_table[3] = {5, 5, 3};

static EVT_BEGIN(main_evt)
	CALL(evt_unitwin_main_func)
	RETURN
EVT_END()

EVT_BEGIN(select_evt)
	CALL(unk_80174e98)
	RETURN
EVT_END()

#ifdef NONMATCHING
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
#endif


#ifdef NONMATCHING
#define UNITWIN_UNUSED_INLINE(fn) static void fn(char* buf, const char* name, s32 n) { sprintf(buf, ((char*)str_802F68B0), name, n); }
UNITWIN_UNUSED_INLINE(unitwin_fmt)
#endif

#ifdef NONMATCHING
void unk_8017597c(WinMgrEntry* entry) {
	winMgrHelpMain(entry);
}
#endif

#ifdef NONMATCHING
void unk_801758fc(WinMgrEntry* entry) {
	UnitWinWork* wp = _wp;
	s32 idx = wp->goodsIdx * 4;
	s32* goods = wp->goods;
	if (!winMgrAction(wp->winId[1])) {
		entry->msg = msgSearch(itemDataTable[*(s32*)((u8*)goods + idx)].description);
		winMgrHelpDraw(entry);
	}
}
#endif

#ifdef NONMATCHING
void unk_80175710(WinMgrEntry* entry) {
	UnitWinWork* wp = _wp;
	PouchData* pouch = pouchGetPtr();
	s32 mode;
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
USER_FUNC(unitwincoin_wait) {
	UnitWinWork* wp = _wp;
	pouchGetPtr();
	if (wp->coin != pouchGetCoin()) {
		return EVT_RETURN_BLOCK;
	}
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
USER_FUNC(unk_801751f8) {
	s32* args = event->args;
	UnitWinWork* wp = (UnitWinWork*)evtGetValue(event, args[0]);
	wp->bought = evtGetValue(event, args[1]);
	return EVT_RETURN_DONE;
}
#endif

#define UNITWIN_CLOSE(wp)                \
	if ((wp)->selected != -1) {          \
		(wp)->selected = -1;             \
		winMgrClose((wp)->winId[0]);     \
		winMgrClose((wp)->winId[1]);     \
	}

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
static inline s32 unitwin_party_icon(s32 icon) {
	if (icon == 0x158) {
		switch (pouchGetPartyColor(4)) {
			case 0:
				icon = 0x158;
				break;
			case 1:
				icon = 0x159;
				break;
			case 2:
				icon = 0x15A;
				break;
			case 3:
				icon = 0x15B;
				break;
			case 4:
				icon = 0x15C;
				break;
			case 5:
				icon = 0x15D;
				break;
			case 6:
			default:
				icon = 0x15E;
				break;
		}
	}
	return icon;
}
#endif

#define ICONGX ((void (*)(Vec*, u16, u16, f32))iconDispGx)
#define ICONGX2 ((void (*)(Vec*, u16, f32, u16))iconDispGx)

#ifdef NONMATCHING
void evt_unitwin_disp_func(CameraId cameraId, void* param) {
	PouchData* pouch = pouchGetPtr();
	UnitWinWork* wp = (UnitWinWork*)param;
	s32 mode;
	s32 row;
	s32 i;
	char fbuf[64];

	if (wp->flags & 1) {
		const char* desc = itemDataTable[wp->goods[wp->goodsIdx]].description;
		const char* name = itemDataTable[wp->goods[wp->goodsIdx]].id;

		windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, -150.0f, 120.0f, 300.0f, 50.0f, 20.0f);
		FontDrawStart();
		FontDrawEdge();
		FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
		FontDrawString((s32)(strlen(name) * 24 / 4) * -1, 108.0f, name);
		FontDrawEdgeOff();
		windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -240.0f, -130.0f, 480.0f, 70.0f, 20.0f);
		FontDrawStart();
		FontDrawMessage(-220, -138, msgSearch(desc));

		for (i = 0; i < wp->goodsMax; i++) {
			if (wp->goods[i] != 0) {
				Vec pos;
				f32 proj[7];
				f32 vp[6];
				f32 sx, sy, sz;
				Mtx mtx;
				CameraEntry* cam;
				s32 id;
				u8 price;

				mapObjGetPos(wp->entries[i].mapObj, &pos);
				cam = camGetPtr(4);
				GXSetProjection(cam->projection, cam->projType);
				GXGetProjectionv(proj);
				GXGetViewportv(vp);
				GXProject(pos.x, pos.y, pos.z, cam->view, proj, vp, &sx, &sy, &sz);
				cam = camGetPtr(cameraId);
				GXSetProjection(cam->projection, cam->projType);
				id = wp->goods[i];
				if (id >= 0xF0 && id < 0x153) {
					price = itemDataTable[id].discount_price;
				} else {
					price = itemDataTable[id].buy_price;
				}
				PSMTXTrans(mtx, 8.0f + (-304.0f + sx), 240.0f - (sy - 60.0f), 0.0f);
				iconNumberDispGx(mtx, price, 1, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			}
		}
	}

	if (wp->flags & 0xD000) {
		Mtx mtx;
		Mtx scale;
		s32 coin;
		s32 delta;

		windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -250.0f, -75.0f, 150.0f, 45.0f, 20.0f);
		PSMTXTrans(mtx, -220.0f, -113.0f, 0.0f);
		PSMTXScale(scale, 0.7f, 0.7f, 0.7f);
		PSMTXConcat(mtx, scale, mtx);
		if (wp->flags & 0x1000) {
			iconDispGx2(mtx, 0x10, 0x18B);
			coin = pouchGetCoin();
		} else if (wp->flags & 0x4000) {
			iconDispGx2(mtx, 0x10, 0x102);
			coin = ((s32 (*)(void))pouchGetSuperCoin)();
		} else {
			iconDispGx2(mtx, 0x10, 0x18D);
			coin = ((s32 (*)(void))pouchGetStarPiece)();
		}
		PSMTXTrans(mtx, -192.0f, -113.0f, 0.0f);
		iconDispGx2(mtx, 0x10, 0x1D6);
		PSMTXTrans(mtx, -126.0f, -113.0f, 0.0f);
		iconNumberDispGx(mtx, wp->coin, 0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
		if ((delta = coin - wp->coin)) {
			delta /= 10;
			if (!delta) {
				delta = coin > wp->coin ? 1 : -1;
			}
			if (wp->field_0x5C & 1) {
				wp->coin += delta;
				statusWinForceUpdateCoin();
			}
			wp->field_0x5C++;
			wp->field_0x5C %= 1200;
			if (!unk_804189fc) {
				psndSFXOn("SFX_COUNT_COIN1");
				unk_804189fc = 7;
			}
		}
		if (unk_804189fc > 0) {
			unk_804189fc--;
		}
	}

	if (wp->flags & 0x2000) {
		Mtx mtx;
		Mtx scale;
		s32 delta;

		windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -250.0f, -130.0f, 150.0f, 45.0f, 20.0f);
		PSMTXTrans(mtx, -210.0f, -166.0f, 0.0f);
		PSMTXScale(scale, 1.1f, 1.1f, 1.1f);
		PSMTXConcat(mtx, scale, mtx);
		iconDispGx2(mtx, 0x10, 0x1F1);
		PSMTXTrans(mtx, -126.0f, -168.0f, 0.0f);
		iconNumberDispGx(mtx, wp->coinDisp, 0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
		if (!(gp->retraceCount & 3)) {
			if ((delta = pouch->mShineSpriteCount - wp->coinDisp)) {
				delta /= 10;
				if (!delta) {
					delta = pouch->mShineSpriteCount > wp->coinDisp ? 1 : -1;
				}
				wp->coinDisp += delta;
			}
		}
	}

	if ((wp->flags & 0x100) && (lotteryGetPtr()->mFlags & 2)) {
		Mtx mtx;
		char buf[32];

		windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -250.0f, -130.0f, 150.0f, 45.0f, 20.0f);
		PSMTXTrans(mtx, -220.0f, -172.0f, 0.0f);
		iconDispGx2(mtx, 0x10, 0x140);
		sprintf(buf, "%04d", *(s16*)((u8*)lotteryGetPtr() + 0x20));
		for (i = 0; i < 4; i++) {
			PSMTXTrans(mtx, 20.0f * i + -126.0f - 60.0f, -168.0f, 0.0f);
			iconNumberDispGx(mtx, ((s8*)buf)[i] - '0', 0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
		}
	}

	switch (mode = wp->field_0x50) {
		case 0:
		case 1:
			break;
		case 4: {
			const char* desc;
			s32 h;
			u32 sl, st, sw, sh;

			row = 0;
			desc = NULL;

			h = (8 - pouchGetKeepItemCnt() > 0 ? 8 - pouchGetKeepItemCnt() : 0) * 24;
			windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -24.0f, 100.0f, 300.0f, 220 - h, 20.0f);
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 51.0f, 114.0f, 150.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(81.0f, 111.0f, msgSearch("msg_window_title_1"));
			FontDrawEdgeOff();
			GXGetScissor(&sl, &st, &sw, &sh);
			GXSetScissor(0x120, 0xA2, 0x11C, 0xBE - h);
			for (i = 0; i < 32; i++) {
				s32 id = pouchKeepItem(i);
				ItemData* item = &itemDataTable[id];
				if (id) {
					ICONGX2(&(Vec){11.0f, wp->scroll + (56 - row * 24), 0.0f}, 0x10, 0.5f, item->icon_id);
					FontDrawStart();
					FontDrawString(36.0f, wp->scroll + (80 - row * 24), item->id);
					if (row == wp->cursor) {
						desc = item->description;
					}
					row++;
				}
			}
			GXSetScissor(sl, st, sw, sh);
			if (desc) {
				windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -240.0f, -130.0f, 480.0f, 70.0f, 20.0f);
				FontDrawStart();
				FontDrawMessage(-220, -138, msgSearch(desc));
			}
			break;
		}
		case 2:
		case 3:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16: {
			s32 h;
			s32* tbl;
			const char* title;
			s32 titleX;
			s32 i;
			const char* desc;
			s32 max;
			s32 flag;
			u32 sl, st, sw, sh;

			desc = NULL;
			i = 0;
			if (mode == 2 || mode == 3) {
				h = (8 - pouchGetHaveItemCnt() > 0 ? 8 - pouchGetHaveItemCnt() : 0) * 24;
				max = 20;
				title = msgSearch("msg_window_title_1");
				titleX = 30;
			} else if (mode == 12) {
				h = (8 - pouchGetHaveBadgeCnt() > 0 ? 8 - pouchGetHaveBadgeCnt() : 0) * 24;
				max = 200;
				title = msgSearch("msg_window_title_2");
				titleX = 40;
			} else if (mode == 14) {
				h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
				max = 0x152;
				title = msgSearch("msg_window_title_3");
				titleX = 20;
			} else if (mode == 15) {
				h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
				max = wp->count;
				title = msgSearch("msg_window_title_3");
				titleX = 20;
			} else if (mode == 16) {
				h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
				max = 0x152;
				title = msgSearch("msg_window_title_4");
				titleX = 30;
			} else {
				h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
				max = 99;
				title = msgSearch("msg_window_title_2");
				titleX = 40;
			}
			windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -24.0f, 100.0f, 300.0f, 220 - h, 20.0f);
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 51.0f, 114.0f, 150.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(titleX + 51, 111.0f, title);
			FontDrawEdgeOff();
			if (wp->field_0x50 != 3) {
				Mtx mtx;
				Mtx scale;
				s32 icon;
				PSMTXTrans(mtx, 244.0f, 82.0f, 0.0f);
				PSMTXScale(scale, 0.6f, 0.6f, 0.6f);
				PSMTXConcat(mtx, scale, mtx);
				iconDispGxCol(mtx, 0x10, 0x211, (GXColor){0xF0, 0xF0, 0xF0, 0xFF});
				if (wp->field_0x50 == 13) {
					icon = 0x18D;
				} else if (wp->field_0x50 == 16) {
					icon = 0x13F;
				} else {
					icon = 0x18B;
				}
				{
					iconDispGx(&(Vec){244.0f, 86.0f, 0.0f}, 0x10, icon, 0.6f);
				}
			}
			GXGetScissor(&sl, &st, &sw, &sh);
			GXSetScissor(0x120, 0xA2, 0x11C, 0xBE - h);
			for (tbl = badge_bottakuru100_table, row = i; i < max; i++) {
				
				GXColor color = {0x00, 0x00, 0x00, 0xFF};
				s32 id;
				ItemData* item;
				flag = 0;
				switch (wp->field_0x50) {
					case 2:
					case 3:
						id = pouchHaveItem(i);
						break;
					case 12:
						id = pouchHaveBadge(i);
						break;
					case 11:
						id = (s16)badgeShop_get(bdsw->bargain_table, i + 0xF0);
						if (id - badgeShop_ThrowCheck(i + 0xF0) > 0) {
							id = i + 0xF0;
						} else {
							id = 0;
						}
						break;
					case 13:
						if ((s16)badgeShop_get(bdsw->starmaniac_table, i + 0xF0) > 0) {
							id = i + 0xF0;
						} else {
							id = 0;
						}
						break;
					case 14:
						if ((s16)badgeShop_get(bdsw->bottakuru_table, i + 1) > 0) {
							id = i + 1;
						} else {
							id = 0;
						}
						break;
					case 15:
						id = tbl[i];
						break;
					case 16:
						if ((s16)badgeShop_get(bdsw->bteresa_table, i + 1) > 0) {
							id = i + 1;
						} else {
							id = 0;
						}
						break;
				}
				item = &itemDataTable[id];
				if (id) {
					s32 ty;
					if (wp->field_0x50 == 13 && item->star_piece_price > ((s32 (*)(void))pouchGetStarPiece)()) {
						color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
						flag = 0x20;
					}
					{
						ICONGX2(&(Vec){11.0f, wp->scroll + (56 - row * 24), 0.0f}, flag | 0x10, 0.5f, item->icon_id);
					}
					FontDrawStart();
					FontDrawScale(0.8f);
					FontDrawColor(color);
					FontDrawString(36.0f, wp->scroll + (80 - row * 24) - 2.0f, item->id);
					if (wp->field_0x50 != 3) {
						char buf[32];
						f32 sc;
						s32 xoff;
						switch (wp->field_0x50) {
							case 14:
								sprintf(buf, "%2d", item->buy_price * 12 / 10);
								sc = 1.0f;
								xoff = 0;
								break;
							case 15:
								sprintf(buf, "%3d", item->buy_price * (evtGetValue(NULL, 0xF5DE06A9) + 11) / 10);
								sc = 1.0f;
								xoff = -14;
								break;
							case 16:
								sprintf(buf, "%4d", (item->buy_price * 2 + 2) / 3);
								sc = 0.8f;
								xoff = -20;
								break;
							case 11:
								sprintf(buf, "%2d", item->buy_price);
								sc = 1.0f;
								xoff = 0;
								break;
							case 13:
								sprintf(buf, "%2d", item->star_piece_price);
								sc = 1.0f;
								xoff = 0;
								break;
							case 12:
							default:
								sprintf(buf, "%2d", item->sell_price);
								xoff = 0;
								sc = 1.0f;
								break;
						}
						FontDrawStart();
						FontDrawScale(sc);
						FontDrawColor(color);
						FontDrawString(xoff + 226, wp->scroll + (80 - row * 24), buf);
					}
					if (row == wp->cursor) {
						desc = item->description;
					}
					row++;
				}
			}
			GXSetScissor(sl, st, sw, sh);
			if (desc) {
				windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -240.0f, -130.0f, 480.0f, 70.0f, 20.0f);
				FontDrawStart();
				FontDrawMessage(-220, -138, msgSearch(desc));
			}
			break;
		}
		case 17:
		case 18: {
			InformantWork* jdt = &_jdt;
			InformantInfo* info;
			s32 h;
			u8* tbl;
			const char* title;
			u32 sl, st, sw, sh;


			h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
			if (mode == 17) {
				title = msgSearch("msg_window_title_5");
				tbl = jdt->readFlags.perfectRead;
			} else {
				title = msgSearch("msg_window_title_6");
				tbl = jdt->readFlags.luigiRead;
			}
			windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -24.0f, 100.0f, 300.0f, 220 - h, 20.0f);
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 51.0f, 114.0f, 150.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(71.0f, 111.0f, title);
			FontDrawEdgeOff();
			if (wp->field_0x50 == 17) {
				Mtx mtx;
				Mtx scale;
				PSMTXTrans(mtx, 244.0f, 82.0f, 0.0f);
				PSMTXScale(scale, 0.6f, 0.6f, 0.6f);
				PSMTXConcat(mtx, scale, mtx);
				iconDispGxCol(mtx, 0x10, 0x211, (GXColor){0xF0, 0xF0, 0xF0, 0xFF});
				{
					iconDispGx(&(Vec){244.0f, 86.0f, 0.0f}, 0x10, 0x18B, 0.6f);
				}
			}
			GXGetScissor(&sl, &st, &sw, &sh);
			GXSetScissor(0x120, 0xA2, 0x11C, 0xBE - h);
			for (i = 0, info = jdt->info; i < wp->count; i++, info++) {
				char buf[32];
				GXColor color;
				char c;
				s32 ty;
				if (johoya_get(tbl, info->storyId)) {
					sprintf(buf, "");
					color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
				} else {
					sprintf(buf, "%3d", info->unkA);
					color = (GXColor){0x00, 0x00, 0x00, 0xFF};
				}
				FontDrawStart();
				c = ((char*)info->initEndPos)[info->tagEndPos];
				((char*)info->initEndPos)[info->tagEndPos] = 0;
				FontDrawColor(color);
				FontDrawScale(0.8f);
				FontDrawString(1.0f, wp->scroll + (80 - i * 24), (char*)info->initEndPos);
				((char*)info->initEndPos)[info->tagEndPos] = c;
				if (wp->field_0x50 == 17) {
					FontDrawStart();
					FontDrawColor(color);
					FontDrawString(221.0f, wp->scroll + (80 - i * 24), buf);
				}
			}
			GXSetScissor(sl, st, sw, sh);
			break;
		}
		case 5:
		case 6:
		case 7: {
			const char* name;
			char msgName[64] = {0};
			s32 row = 0;
			s32 h;
			u32 sl, st, sw, sh;
			
			s32 lv;
			s32 flag;
			GXColor color;

			h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
			windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -24.0f, 100.0f, 300.0f, 220 - h, 20.0f);
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 16.0f, 114.0f, 120.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(41.0f, 111.0f, msgSearch("msg_window_title_7"));
			FontDrawEdgeOff();
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 167.0f, 114.0f, 85.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(177.0f, 111.0f, msgSearch("msg_window_title_8"));
			FontDrawEdgeOff();
			GXGetScissor(&sl, &st, &sw, &sh);
			GXSetScissor(0x120, 0xA2, 0x11C, 0xBE - h);
			for (i = 0; party_id_table[i]; i++) {
				s32 icon;
				s32 ty;
				char buf[32];
				char help[16];
				char dir[16];
				if (wp->field_0x50 == 5 || wp->field_0x50 == 6) {
					if (!partyChkJoin(party_id_table[i])) {
						continue;
					}
					if (evtGetValue(NULL, 0xF8406022) == 0) {
						if (pouch->partyData[party_id_table[i]].techLevel < 1) {
							color = (GXColor){0x00, 0x00, 0x00, 0xFF};
							lv = 0;
							flag = 0;
						} else {
							color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
							lv = 1;
							flag = 0x20;
						}
					} else {
						if (pouch->partyData[party_id_table[i]].techLevel < 2) {
							color = (GXColor){0x00, 0x00, 0x00, 0xFF};
							lv = 0;
							flag = 0;
						} else {
							color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
							lv = 2;
							flag = 0x20;
						}
					}
				} else {
					if (!partyChkJoin(party_id_table[i])) {
						continue;
					}
					if (wp->field_0x4C == party_id_table[i]) {
						continue;
					}
					if (pouch->partyData[party_id_table[i]].techLevel > 0) {
						color = (GXColor){0x00, 0x00, 0x00, 0xFF};
						lv = 0;
						flag = 0;
					} else {
						color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
						lv = 1;
						flag = 0x20;
					}
				}
				ICONGX2(&(Vec){11.0f, wp->scroll + (56 - row * 24), 0.0f}, flag | 0x10, 0.5f, unitwin_party_icon(party_icon_table[i]));
				FontDrawStart();
				FontDrawColor(color);
				switch (i) {
					case 0:
						name = msgSearch("name_party0");
						break;
					case 1:
						name = msgSearch("name_party1");
						break;
					case 2:
						name = msgSearch("name_party4");
						break;
					case 3:
						name = pouchGetYoshiName();
						break;
					case 4:
						name = msgSearch("name_party5");
						break;
					case 5:
						name = msgSearch("name_party2");
						break;
					case 6:
						name = msgSearch("name_party6");
						break;
				}
				ty = 80 - row * 24;
				FontDrawString(36.0f, wp->scroll + ty, name);
				sprintf(buf, "%d", pouch->partyData[party_id_table[i]].techLevel);
				FontDrawStart();
				FontDrawString(236.0f, wp->scroll + ty, buf);
				if (row == wp->cursor) {
					if (lv == 0) {
						sprintf(help, "help");
					} else {
						sprintf(help, "helperr");
					}
					if (wp->field_0x50 == 5 || wp->field_0x50 == 6) {
						sprintf(dir, "lankup");
					} else {
						sprintf(dir, "lankdown");
					}
					sprintf(msgName, "%s_%s_lank%d%s", help, dir, pouch->partyData[party_id_table[i]].techLevel + 1, party_labelname_table[i]);
				}
				row++;
			}
			GXSetScissor(sl, st, sw, sh);
			if (*(s8*)msgName) {
				windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -240.0f, -130.0f, 480.0f, 70.0f, 20.0f);
				FontDrawStart();
				FontDrawMessage(-220, -138, msgSearch(msgName));
			}
			break;
		}
		case 8: {
			char msgName[64] = {0};
			s32 row = 0;
			s32 h;
			u32 sl, st, sw, sh;
			
			s32 j;
			s32 flag;
			s32 lv;
			s32 bob;
			s32 iy;
			s32 iflag;
			s32 v;
			s32 ty;
			GXColor color;
			s32 icon;

			h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
			windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -24.0f, 100.0f, 300.0f, 220 - h, 20.0f);
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 16.0f, 114.0f, 120.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(21.0f, 111.0f, msgSearch("msg_window_title_9"));
			FontDrawEdgeOff();
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 167.0f, 114.0f, 85.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(177.0f, 111.0f, msgSearch("msg_window_title_10"));
			FontDrawEdgeOff();
			GXGetScissor(&sl, &st, &sw, &sh);
			GXSetScissor(0x120, 0xA2, 0x11C, 0xBE - h);
			for (i = 0; i < wp->count; i++) {
				char buf[32];
				char help[16];
				flag = 0;
				for (j = 0; j < wp->count; j++) {
					if (j != wp->cursor && *mario_status_point_table[j] - mario_status_henka_table[j] <= 0) {
						flag = 1;
					}
				}
				if (!flag) {
					color = (GXColor){0x00, 0x00, 0x00, 0xFF};
					lv = 0;
					flag = 0;
				} else {
					color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
					lv = 1;
					flag = 0x20;
				}
				{
					ICONGX2(&(Vec){11.0f, wp->scroll + (56 - i * 24), 0.0f}, iflag = flag | 0x10, 0.5f, mario_status_icon_table[i]);
				}
				FontDrawStart();
				FontDrawColor(color);
				sprintf(buf, "%s%3d", mario_status_name_table[i], *mario_status_point_table[i]);
				FontDrawString(36.0f, wp->scroll + (80 - i * 24), buf);
				bob = (gp->retraceCount & 0xF) > 7 ? 0 : 2;
				if (row == wp->cursor) {
					if (lv == 0) {
						sprintf(help, "help");
					} else {
						sprintf(help, "helperr");
					}
					sprintf(msgName, "%s_levelup%s", help, mario_status_labelname_table[i]);
					v = *mario_status_point_table[i] + mario_status_henka_table[i] * 2;
					if (v > 0) {
						icon = 0x1B5;
					} else {
						icon = 0x162;
						bob = 0;
					}
					{
						ICONGX2(&(Vec){166.0f, bob + (wp->scroll + (56 - i * 24)), 0.0f}, iflag, 0.5f, icon);
					}
					{
						ICONGX2(&(Vec){186.0f, bob + (wp->scroll + (56 - i * 24)), 0.0f}, iflag, 0.5f, icon);
					}
				} else {
					v = *mario_status_point_table[i] - mario_status_henka_table[i];
					if (v > 0) {
						icon = 0x1B6;
					} else {
						icon = 0x162;
						bob = 0;
					}
					{
						ICONGX2(&(Vec){176.0f, (wp->scroll + (56 - i * 24)) - bob, 0.0f}, iflag, 0.5f, icon);
					}
				}
				if (v > 0) {
					sprintf(buf, "%3d", v);
				} else {
					sprintf(buf, "  \x81\x48", v);
				}
				FontDrawStart();
				FontDrawString(206.0f, wp->scroll + (80 - i * 24), buf);
				row++;
			}
			GXSetScissor(sl, st, sw, sh);
			if (*(s8*)msgName) {
				windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -240.0f, -130.0f, 480.0f, 70.0f, 20.0f);
				FontDrawStart();
				FontDrawMessage(-220, -138, msgSearch(msgName));
			}
			break;
		}
		case 9: {
			char msgName[64] = {0};
			s32 row = 0;
			s32 h;
			u32 sl, st, sw, sh;
			
			s32 j;
			s32 cnt;
			s32 lv;
			s32 v;
			s32 ty;
			GXColor color;

			h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
			windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -24.0f, 100.0f, 300.0f, 220 - h, 20.0f);
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 16.0f, 114.0f, 120.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(21.0f, 111.0f, msgSearch("msg_window_title_9"));
			FontDrawEdgeOff();
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 167.0f, 114.0f, 85.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(177.0f, 111.0f, msgSearch("msg_window_title_10"));
			FontDrawEdgeOff();
			GXGetScissor(&sl, &st, &sw, &sh);
			GXSetScissor(0x120, 0xA2, 0x11C, 0xBE - h);
			for (i = 0; i < wp->count; i++) {
				char buf[32];
				char help[16];
				cnt = 0;
				for (j = 0; j < wp->count; j++) {
					if (j != wp->cursor && *mario_status_point_table[j] - mario_status_henka_table[j] <= 0) {
						cnt++;
					}
				}
				if (cnt < 2) {
					color = (GXColor){0x00, 0x00, 0x00, 0xFF};
					lv = 0;
					j = 0;
				} else {
					color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
					lv = 1;
					j = 0x20;
				}
				{
					ICONGX2(&(Vec){11.0f, wp->scroll + (56 - i * 24), 0.0f}, j | 0x10, 0.5f, mario_status_icon_table[i]);
				}
				FontDrawStart();
				FontDrawColor(color);
				sprintf(buf, "%s%3d", mario_status_name_table[i], *mario_status_point_table[i]);
				FontDrawString(36.0f, wp->scroll + (80 - i * 24), buf);
				if (row == wp->cursor) {
					if (lv == 0) {
						sprintf(help, "help");
					} else {
						sprintf(help, "helperr");
					}
					sprintf(msgName, "%s_levelup%s", help, mario_status_labelname_table[i]);
					v = *mario_status_point_table[i] + mario_status_henka_table[i];
					if (v > 0) {
						sprintf(buf, "%3d", v);
					} else {
						sprintf(buf, "  \x81\x48", v);
					}
					FontDrawStart();
					FontDrawString(206.0f, wp->scroll + (80 - i * 24), buf);
				}
				row++;
			}
			GXSetScissor(sl, st, sw, sh);
			if (*(s8*)msgName) {
				windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -240.0f, -130.0f, 480.0f, 70.0f, 20.0f);
				FontDrawStart();
				FontDrawMessage(-220, -138, msgSearch(msgName));
			}
			break;
		}
		case 10: {
			char msgName[64] = {0};
			s32 row = 0;
			s32 h;
			u32 sl, st, sw, sh;
			
			s32 v;
			s32 ty;
			s32 flag;
			GXColor color;
			s32 lv;

			h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
			windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -24.0f, 100.0f, 300.0f, 220 - h, 20.0f);
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 16.0f, 114.0f, 120.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(21.0f, 111.0f, msgSearch("msg_window_title_9"));
			FontDrawEdgeOff();
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 167.0f, 114.0f, 85.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(177.0f, 111.0f, msgSearch("msg_window_title_10"));
			FontDrawEdgeOff();
			GXGetScissor(&sl, &st, &sw, &sh);
			GXSetScissor(0x120, 0xA2, 0x11C, 0xBE - h);
			for (i = 0; i < 3; i++) {
				char buf[32];
				char help[16];
				if (i == wp->field_0x4C) {
					continue;
				}
				if (*mario_status_point_table[i] - mario_status_henka_table[i] > 0) {
					color = (GXColor){0x00, 0x00, 0x00, 0xFF};
					lv = 0;
					flag = 0;
				} else {
					color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
					lv = 1;
					flag = 0x20;
				}
				{
					ICONGX2(&(Vec){11.0f, wp->scroll + (56 - row * 24), 0.0f}, flag | 0x10, 0.5f, mario_status_icon_table[i]);
				}
				FontDrawStart();
				FontDrawColor(color);
				sprintf(buf, "%s%3d", mario_status_name_table[i], *mario_status_point_table[i]);
				FontDrawString(36.0f, wp->scroll + (80 - row * 24), buf);
				if (row == wp->cursor) {
					if (lv == 0) {
						sprintf(help, "help");
					} else {
						sprintf(help, "helperr");
					}
					sprintf(msgName, "%s_leveldown%s", help, mario_status_labelname_table[i]);
					v = *mario_status_point_table[i] - mario_status_henka_table[i];
					if (v > 0) {
						sprintf(buf, "%3d", v);
					} else {
						sprintf(buf, "  \x81\x48", v);
					}
					FontDrawStart();
					FontDrawString(206.0f, wp->scroll + (80 - row * 24), buf);
				}
				row++;
			}
			GXSetScissor(sl, st, sw, sh);
			if (*(s8*)msgName) {
				windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -240.0f, -130.0f, 480.0f, 70.0f, 20.0f);
				FontDrawStart();
				FontDrawMessage(-220, -138, msgSearch(msgName));
			}
			break;
		}
	}

	if (wp->field_0x50 != 0 && wp->field_0x50 != 1) {
		char text[136];
		char* line1;
		char* line2 = NULL;
		s8* p;
		s32 k;
		s32 lines;
		s32 w2;

		switch (wp->field_0x50) {
			case 0:
			case 1:
				break;
			case 11:
			case 14:
			case 15:
				strcpy(text, msgSearch("msg_window_select_6"));
				break;
			case 17:
				strcpy(text, msgSearch("msg_window_select_8"));
				break;
			case 18:
				strcpy(text, msgSearch("msg_window_select_7"));
				break;
			case 13:
			case 16:
				strcpy(text, msgSearch("msg_window_select_10"));
				break;
			case 2:
			case 12:
				strcpy(text, msgSearch("msg_window_select_2"));
				break;
			case 3:
				strcpy(text, msgSearch("msg_window_select_3"));
				break;
			case 4:
				strcpy(text, msgSearch("msg_window_select_4"));
				break;
			case 5:
				strcpy(text, msgSearch("msg_window_select_11"));
				break;
			case 6:
				strcpy(text, msgSearch("msg_window_select_11"));
				break;
			case 7:
				strcpy(text, msgSearch("msg_window_select_12"));
				break;
			case 8:
			case 9:
				strcpy(text, msgSearch("msg_window_select_9"));
				break;
			case 10:
				strcpy(text, msgSearch("msg_window_select_9_1"));
				break;
		}
		line1 = text;
		lines = 1;
		for (p = (s8*)line1, k = 0; *p; p++, k++) {
			if (*p == '\n') {
				text[k] = 0;
				lines = 2;
				line2 = &text[k] + 1;
				break;
			}
		}
		windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -280.0f, 100.0f, 240.0f, (lines - 1) * 24 + 45, 20.0f);
		FontDrawStart();
		k = line1 ? FontGetMessageWidth(line1) : 0;
		if (line2) {
			w2 = FontGetMessageWidth(line2);
		} else {
			w2 = 0;
		}
		if (w2 > k) {
			k = w2;
		}
		if (k <= 228) {
			k = (228 - k) / 2;
		} else {
			FontDrawScale(228.0f / k);
			k = 0;
		}
		FontDrawString(k - 274, 90.0f, line1);
		if (line2) {
			FontDrawString(k - 274, 66.0f, line2);
		}
		iconFlagOff("yubicursor_2", 2);
		iconSetPos("yubicursor_2", wp->cursorX, wp->cursorY, 0.0f);
	} else {
		iconFlagOn("yubicursor_2", 2);
	}
}
#endif


#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
USER_FUNC(unitwin_get_work_ptr) {
	evtSetValue(event, event->args[0], (s32)_wp);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(unitwin_getpartylank) {
	s32* args = event->args;
	PouchData* pouch = pouchGetPtr();
	s32 idx = evtGetValue(event, args[0]);
	evtSetValue(event, args[1], pouch->partyData[idx].techLevel);
	return EVT_RETURN_DONE;
}
#endif

#define PP ((PouchPartyData*)((u8*)pouch + idx))
#ifdef NONMATCHING
USER_FUNC(unitwin_setpartylank) {
	PouchPartyData* new_var2;
	unsigned int idx;
	s16 v;
	s32 new_var;
	s32* args = event->args;
	PouchData* pouch = pouchGetPtr();
	idx = evtGetValue(event, args[0]) * 14;
	v = evtGetValue(event, args[1]);
	new_var = idx;
	new_var2 = (PouchPartyData*)((u8*)pouch + new_var);
	new_var2->HPLevel = ((PouchPartyData*)((u8*)pouch + new_var))->attackLevel = ((PouchPartyData*)((u8*)pouch + new_var))->techLevel = v;
	pouchRevisePartyParam();
	PP->currentHP = PP->maximumHP;
	return EVT_RETURN_DONE;
}
#endif
#undef PP

#ifdef NONMATCHING
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
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: unk_8017599c (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802f64b8[3] = { 11.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f64c4[3] = { 244.0f, 86.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f64d0[3] = { 11.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f64dc[3] = { 244.0f, 86.0f, 0.0f };
__declspec(section ".rodata") const u32 zero_802f64e8[16] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
__declspec(section ".rodata") const f32 vec3_802f6528[3] = { 11.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const u32 zero_802f6534[16] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
__declspec(section ".rodata") const f32 vec3_802f6574[3] = { 11.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f6580[3] = { 166.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f658c[3] = { 186.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f6598[3] = { 176.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const u32 zero_802f65a4[16] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
__declspec(section ".rodata") const f32 vec3_802f65e4[3] = { 11.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const u32 zero_802f65f0[16] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
__declspec(section ".rodata") const f32 vec3_802f6630[3] = { 11.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const char str_802F663C[] = "SFX_COUNT_COIN1";
__declspec(section ".rodata") const char str_802F664C[] = "msg_window_title_1\000";
__declspec(section ".rodata") const char str_802F6660[] = "msg_window_title_2\000";
__declspec(section ".rodata") const char str_802F6674[] = "msg_window_title_3\000";
__declspec(section ".rodata") const char str_802F6688[] = "msg_window_title_4\000";
__declspec(section ".rodata") const char str_802F669C[] = "msg_window_title_5\000";
__declspec(section ".rodata") const char str_802F66B0[] = "msg_window_title_6\000";
__declspec(section ".rodata") const char str_802F66C4[] = "msg_window_title_7\000";
__declspec(section ".rodata") const char str_802F66D8[] = "msg_window_title_8\000";
__declspec(section ".rodata") const char str_802F66EC[] = "name_party0";
__declspec(section ".rodata") const char str_802F66F8[] = "name_party1";
__declspec(section ".rodata") const char str_802F6704[] = "name_party4";
__declspec(section ".rodata") const char str_802F6710[] = "name_party5";
__declspec(section ".rodata") const char str_802F671C[] = "name_party2";
__declspec(section ".rodata") const char str_802F6728[] = "name_party6";
__declspec(section ".rodata") const char str_802F6734[] = "helperr";
__declspec(section ".rodata") const char str_802F673C[] = "lankup\000";
__declspec(section ".rodata") const char str_802F6744[] = "lankdown\000\000\000";
__declspec(section ".rodata") const char str_802F6750[] = "%s_%s_lank%d%s\000";
__declspec(section ".rodata") const char str_802F6760[] = "msg_window_title_9\000";
__declspec(section ".rodata") const char str_802F6774[] = "msg_window_title_10";
__declspec(section ".rodata") const char str_802F6788[] = "%s_levelup%s\000\000\000";
__declspec(section ".rodata") const char str_802F6798[] = "%s_leveldown%s\000";
__declspec(section ".rodata") const char str_802F67A8[] = "msg_window_select_6";
__declspec(section ".rodata") const char str_802F67BC[] = "msg_window_select_8";
__declspec(section ".rodata") const char str_802F67D0[] = "msg_window_select_7";
__declspec(section ".rodata") const char str_802F67E4[] = "msg_window_select_10\000\000\000";
__declspec(section ".rodata") const char str_802F67FC[] = "msg_window_select_2";
__declspec(section ".rodata") const char str_802F6810[] = "msg_window_select_3";
__declspec(section ".rodata") const char str_802F6824[] = "msg_window_select_4";
__declspec(section ".rodata") const char str_802F6838[] = "msg_window_select_11\000\000\000";
__declspec(section ".rodata") const char str_802F6850[] = "msg_window_select_12\000\000\000";
__declspec(section ".rodata") const char str_802F6868[] = "msg_window_select_9";
__declspec(section ".rodata") const char str_802F687C[] = "msg_window_select_9_1\000\000";
__declspec(section ".rodata") const char str_802F6894[] = "yubicursor_2\000\000\000";
__declspec(section ".rodata") const f64 double_to_int_802f68a8 = 4503601774854144;
__declspec(section ".rodata") const char str_802F68B0[] = "%s_%04d";
__declspec(section ".rodata") const f64 double_to_int_mask_802f68b8 = 4503599627370496;
__declspec(section ".sdata2") const char str_8041D958[8] = "_kur\000\000\000";
__declspec(section ".sdata2") const char str_8041D960[8] = "_nok\000\000\000";
__declspec(section ".sdata2") const char str_8041D968[8] = "_win\000\000\000";
__declspec(section ".sdata2") const char str_8041D970[8] = "_yos\000\000\000";
__declspec(section ".sdata2") const char str_8041D978[8] = "_viv\000\000\000";
__declspec(section ".sdata2") const char str_8041D980[8] = "_bom\000\000\000";
__declspec(section ".sdata2") const char str_8041D988[8] = "_chu\000\000\000";
__declspec(section ".sdata2") const char str_8041D990[4] = "_hp";
__declspec(section ".sdata2") const char str_8041D994[4] = "_fp";
__declspec(section ".sdata2") const char str_8041D998[4] = "_bp";
__declspec(section ".sdata2") const char str_8041D99C[8] = "\202g\202o\000\000\000";
__declspec(section ".sdata2") const char str_8041D9A4[8] = "\202e\202o\000\000\000";
__declspec(section ".sdata2") const char str_8041D9AC[8] = "\202a\202o\000\000\000";
__declspec(section ".sdata2") const u32 dat_8041d9b4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9b8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9bc = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9c0 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041d9c4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9c8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9cc = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9d0 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9d4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9d8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9dc = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9e0 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9e4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9e8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9ec = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041d9f0 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9f4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9f8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9fc = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da00 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da04 = 0xF0F0F0FF;
__declspec(section ".sdata2") const u32 dat_8041da08 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041da0c = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041da10 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da14 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da18 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da1c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da20 = 0xF0F0F0FF;
__declspec(section ".sdata2") const u32 dat_8041da24 = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041da28 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041da2c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da30 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da34 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da38 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da3c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da40 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041da44 = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041da48 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041da4c = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041da50 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041da54 = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041da58 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da5c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da60 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da64 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da68 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da6c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da70 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041da74 = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041da78 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da7c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da80 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da84 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da88 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da8c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da90 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041da94 = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041da98 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da9c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041daa0 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041daa4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041daa8 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041daac = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041dab0 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041dab4 = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041dab8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041dabc = 0xFFFFFFFF;
__declspec(section ".sdata2") const char str_8041DAC0[8] = "uwn%d\0\0";
__declspec(section ".sdata2") const f32 float_neg150_8041dac8 = -150.0f;
__declspec(section ".sdata2") const f32 float_120_8041dacc = 120.0f;
__declspec(section ".sdata2") const f32 float_300_8041dad0 = 300.0f;
__declspec(section ".sdata2") const f32 float_50_8041dad4 = 50.0f;
__declspec(section ".sdata2") const f32 float_20_8041dad8 = 20.0f;
__declspec(section ".sdata2") const f32 float_108_8041dadc = 108.0f;
__declspec(section ".sdata2") const f32 float_neg240_8041dae0 = -240.0f;
__declspec(section ".sdata2") const f32 float_neg130_8041dae4 = -130.0f;
__declspec(section ".sdata2") const f32 float_480_8041dae8 = 480.0f;
__declspec(section ".sdata2") const f32 float_70_8041daec = 70.0f;
__declspec(section ".sdata2") const f32 float_8_8041daf0 = 8.0f;
__declspec(section ".sdata2") const f32 float_neg304_8041daf4 = -304.0f;
__declspec(section ".sdata2") const f32 float_240_8041daf8 = 240.0f;
__declspec(section ".sdata2") const f32 float_60_8041dafc = 60.0f;
__declspec(section ".sdata2") const f32 float_0_8041db00 = 0.0f;
__declspec(section ".sdata2") const f32 float_neg250_8041db04 = -250.0f;
__declspec(section ".sdata2") const f32 float_neg75_8041db08 = -75.0f;
__declspec(section ".sdata2") const f32 float_150_8041db0c = 150.0f;
__declspec(section ".sdata2") const f32 float_45_8041db10 = 45.0f;
__declspec(section ".sdata2") const f32 float_neg220_8041db14 = -220.0f;
__declspec(section ".sdata2") const f32 float_neg113_8041db18 = -113.0f;
__declspec(section ".sdata2") const f32 float_0p7_8041db1c = 0.7f;
__declspec(section ".sdata2") const f32 float_neg192_8041db20 = -192.0f;
__declspec(section ".sdata2") const f32 float_neg126_8041db24 = -126.0f;
__declspec(section ".sdata2") const f32 float_neg210_8041db28 = -210.0f;
__declspec(section ".sdata2") const f32 float_neg166_8041db2c = -166.0f;
__declspec(section ".sdata2") const f32 float_1p1_8041db30 = 1.1f;
__declspec(section ".sdata2") const f32 float_neg168_8041db34 = -168.0f;
__declspec(section ".sdata2") const f32 float_neg172_8041db38 = -172.0f;
__declspec(section ".sdata2") const char str_8041DB3C[8] = "%04d\0\0\0";
__declspec(section ".sdata2") const f32 float_neg24_8041db44 = -24.0f;
__declspec(section ".sdata2") const f32 float_100_8041db48 = 100.0f;
__declspec(section ".sdata2") const f32 float_51_8041db4c = 51.0f;
__declspec(section ".sdata2") const f32 float_114_8041db50 = 114.0f;
__declspec(section ".sdata2") const f32 float_28_8041db54 = 28.0f;
__declspec(section ".sdata2") const f32 float_81_8041db58 = 81.0f;
__declspec(section ".sdata2") const f32 float_111_8041db5c = 111.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041db60 = 0.5f;
__declspec(section ".sdata2") const f32 float_36_8041db64 = 36.0f;
__declspec(section ".sdata2") const f32 float_244_8041db68 = 244.0f;
__declspec(section ".sdata2") const f32 float_82_8041db6c = 82.0f;
__declspec(section ".sdata2") const f32 float_0p6_8041db70 = 0.6f;
__declspec(section ".sdata2") const f32 float_0p8_8041db74 = 0.8f;
__declspec(section ".sdata2") const f32 float_2_8041db78 = 2.0f;
__declspec(section ".sdata2") const char str_8041DB7C[4] = "%2d";
__declspec(section ".sdata2") const f32 float_1_8041db80 = 1.0f;
__declspec(section ".sdata2") const char str_8041DB84[4] = "%3d";
__declspec(section ".sdata2") const char str_8041DB88[4] = "%4d";
__declspec(section ".sdata2") const f32 float_71_8041db8c = 71.0f;
__declspec(section ".sdata2") const f32 float_0_8041db90 = 0.0f;
__declspec(section ".sdata2") const f32 float_221_8041db94 = 221.0f;
__declspec(section ".sdata2") const f32 float_16_8041db98 = 16.0f;
__declspec(section ".sdata2") const f32 float_41_8041db9c = 41.0f;
__declspec(section ".sdata2") const f32 float_167_8041dba0 = 167.0f;
__declspec(section ".sdata2") const f32 float_85_8041dba4 = 85.0f;
__declspec(section ".sdata2") const f32 float_177_8041dba8 = 177.0f;
__declspec(section ".sdata2") const char str_8041DBAC[4] = "%d\0";
__declspec(section ".sdata2") const f32 float_236_8041dbb0 = 236.0f;
__declspec(section ".sdata2") const char str_8041DBB4[8] = "help\0\0\0";
__declspec(section ".sdata2") const f32 float_21_8041dbbc = 21.0f;
__declspec(section ".sdata2") const char str_8041DBC0[8] = "%s%3d\0\0";
__declspec(section ".sdata2") const char str_8041DBC8[8] = "  \x81H\0\0\0";
__declspec(section ".sdata2") const f32 float_206_8041dbd0 = 206.0f;
__declspec(section ".sdata2") const f32 float_neg280_8041dbd4 = -280.0f;
__declspec(section ".sdata2") const f32 float_228_8041dbd8 = 228.0f;
__declspec(section ".sdata2") const f32 float_90_8041dbdc = 90.0f;
__declspec(section ".sdata2") const f32 float_66_8041dbe0 = 66.0f;
__declspec(section ".sdata2") const f32 float_1000_8041dbe4 = 1000.0f;
__declspec(section ".sdata2") const f32 float_6_8041dbe8 = 6.0f;
__declspec(section ".sdata2") const f32 float_10_8041dbec = 10.0f;
__declspec(section ".sdata2") const f32 float_30_8041dbf0 = 30.0f;
__declspec(section ".sdata2") const f32 float_124_8041dbf4 = 124.0f;
__declspec(section ".sdata2") const f32 float_38_8041dbf8 = 38.0f;
__declspec(section ".sdata2") const f32 float_12_8041dbfc = 12.0f;

extern void partyChkJoin();
// FAKE: whole-unit asm stopgap (C under NONMATCHING); data in target order, force_active, gaps
asm s32 unitwin_setmariolevel(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	bl pouchGetPtr
	lwz r4, 0x0(r30)
	mr r31, r3
	mr r3, r29
	bl evtGetValue
	sth r3, 0x8e(r31)
	mr r3, r29
	lwz r4, 0x4(r30)
	bl evtGetValue
	sth r3, 0x90(r31)
	mr r3, r29
	lwz r4, 0x8(r30)
	bl evtGetValue
	sth r3, 0x94(r31)
	bl pouchReviseMarioParam
	lha r0, 0x72(r31)
	sth r0, 0x70(r31)
	lha r0, 0x76(r31)
	sth r0, 0x74(r31)
	lha r0, 0x92(r31)
	cmpwi r0, 0x0
	bge L_at1
	li r31, 0x0
	L_at2:
	mr r3, r31
	bl pouchEquipCheckBadgeIndex
	cmpwi r3, 0x0
	beq L_at3
	mr r3, r31
	bl pouchUnEquipBadgeIndex
	L_at3:
	addi r31, r31, 0x1
	cmpwi r31, 0xc8
	blt L_at2
	bl pouchReviseMarioParam
	li r5, 0x1
	b L_at4
	L_at1:
	li r5, 0x0
	L_at4:
	lwz r4, 0xc(r30)
	mr r3, r29
	bl evtSetValue
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 unitwin_setpartylank(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	lwz r29, 0x18(r3)
	bl pouchGetPtr
	lwz r4, 0x0(r29)
	mr r31, r3
	mr r3, r28
	bl evtGetValue
	mulli r30, r3, 0xe
	lwz r4, 0x4(r29)
	mr r3, r28
	bl evtGetValue
	add r4, r31, r30
	sth r3, 0xc(r4)
	sth r3, 0xa(r4)
	sth r3, 0x8(r4)
	bl pouchRevisePartyParam
	add r4, r31, r30
	li r3, 0x2
	lha r0, 0x2(r4)
	sth r0, 0x6(r4)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 unitwin_getpartylank(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	bl pouchGetPtr
	lwz r4, 0x0(r30)
	mr r31, r3
	mr r3, r29
	bl evtGetValue
	mulli r0, r3, 0xe
	lwz r4, 0x4(r30)
	mr r3, r29
	add r5, r31, r0
	lha r5, 0xc(r5)
	bl evtSetValue
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 unitwin_get_work_ptr(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r5, _wp(r0)
	lwz r4, 0x0(r4)
	bl evtSetValue
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 set_new_goods_list(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	mr r31, r3
	stw r30, 0x28(r1)
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lwz r4, 0x4(r30)
	mr r30, r3
	mr r3, r31
	bl evtGetValue
	lwz r0, 0x24(r30)
	mr r31, r3
	lwz r3, 0x8(r30)
	slwi r0, r0, 2
	stwx r31, r3, r0
	lwz r5, 0x24(r30)
	lwz r0, 0x18(r30)
	cmpw r5, r0
	bge L_at1
	addi r3, r1, 0x8
	la r4, str_8041DAC0(r0)
	crclr 6
	bl sprintf
	cmpwi r31, 0x0
	beq L_at2
	mulli r0, r31, 0x28
	lis r4, itemDataTable@ha
	addi r3, r1, 0x8
	addi r4, r4, itemDataTable@l
	add r4, r4, r0
	lhz r4, 0x20(r4)
	bl iconChange
	b L_at1
	L_at2:
	addi r3, r1, 0x8
	bl iconDelete
	L_at1:
	lwz r0, 0x34(r1)
	li r3, 0x2
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

void evt_unitwin_disp_func(CameraId cameraId, void* param);
__declspec(section ".data") static void* jumptable_803754F0[] = {
    (char*)evt_unitwin_disp_func + 0x29CC,
    (char*)evt_unitwin_disp_func + 0x29CC,
    (char*)evt_unitwin_disp_func + 0x2910,
    (char*)evt_unitwin_disp_func + 0x2928,
    (char*)evt_unitwin_disp_func + 0x2940,
    (char*)evt_unitwin_disp_func + 0x2958,
    (char*)evt_unitwin_disp_func + 0x2970,
    (char*)evt_unitwin_disp_func + 0x2988,
    (char*)evt_unitwin_disp_func + 0x29A0,
    (char*)evt_unitwin_disp_func + 0x29A0,
    (char*)evt_unitwin_disp_func + 0x29B8,
    (char*)evt_unitwin_disp_func + 0x28B0,
    (char*)evt_unitwin_disp_func + 0x2910,
    (char*)evt_unitwin_disp_func + 0x28F8,
    (char*)evt_unitwin_disp_func + 0x28B0,
    (char*)evt_unitwin_disp_func + 0x28B0,
    (char*)evt_unitwin_disp_func + 0x28F8,
    (char*)evt_unitwin_disp_func + 0x28C8,
    (char*)evt_unitwin_disp_func + 0x28E0,
};
void evt_unitwin_disp_func(CameraId cameraId, void* param);
__declspec(section ".data") static void* jumptable_8037553C[] = {
    (char*)evt_unitwin_disp_func + 0x172C,
    (char*)evt_unitwin_disp_func + 0x173C,
    (char*)evt_unitwin_disp_func + 0x174C,
    (char*)evt_unitwin_disp_func + 0x175C,
    (char*)evt_unitwin_disp_func + 0x1768,
    (char*)evt_unitwin_disp_func + 0x1778,
    (char*)evt_unitwin_disp_func + 0x1788,
};
void evt_unitwin_disp_func(CameraId cameraId, void* param);
__declspec(section ".data") static void* jumptable_80375558[] = {
    (char*)evt_unitwin_disp_func + 0x16B0,
    (char*)evt_unitwin_disp_func + 0x16B8,
    (char*)evt_unitwin_disp_func + 0x16C0,
    (char*)evt_unitwin_disp_func + 0x16C8,
    (char*)evt_unitwin_disp_func + 0x16D0,
    (char*)evt_unitwin_disp_func + 0x16D8,
    (char*)evt_unitwin_disp_func + 0x16E0,
};
void evt_unitwin_disp_func(CameraId cameraId, void* param);
__declspec(section ".data") static void* jumptable_80375574[] = {
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xC34,
    (char*)evt_unitwin_disp_func + 0xC34,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xC54,
    (char*)evt_unitwin_disp_func + 0xC44,
    (char*)evt_unitwin_disp_func + 0xC8C,
    (char*)evt_unitwin_disp_func + 0xCB8,
    (char*)evt_unitwin_disp_func + 0xCE4,
    (char*)evt_unitwin_disp_func + 0xCEC,
};
void evt_unitwin_disp_func(CameraId cameraId, void* param);
__declspec(section ".data") static void* jumptable_803755B8[] = {
    (char*)evt_unitwin_disp_func + 0x2878,
    (char*)evt_unitwin_disp_func + 0x2878,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x690,
    (char*)evt_unitwin_disp_func + 0x1354,
    (char*)evt_unitwin_disp_func + 0x1354,
    (char*)evt_unitwin_disp_func + 0x1354,
    (char*)evt_unitwin_disp_func + 0x1968,
    (char*)evt_unitwin_disp_func + 0x1FA0,
    (char*)evt_unitwin_disp_func + 0x2434,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x106C,
    (char*)evt_unitwin_disp_func + 0x106C,
};
asm void evt_unitwin_disp_func(CameraId cameraId, void* param) {
	nofralloc
	stwu r1, -0x780(r1)
	mflr r0
	stw r0, 0x784(r1)
	stfd f31, 0x770(r1)
	psq_st f31, 0x778(r1), 0, 0
	stfd f30, 0x760(r1)
	psq_st f30, 0x768(r1), 0, 0
	stfd f29, 0x750(r1)
	psq_st f29, 0x758(r1), 0, 0
	stfd f28, 0x740(r1)
	psq_st f28, 0x748(r1), 0, 0
	stmw r14, 0x6f8(r1)
	lis r5, vec3_802f64b8@ha
	mr r20, r3
	mr r15, r4
	addi r30, r5, vec3_802f64b8@l
	bl pouchGetPtr
	lhz r0, 0x0(r15)
	mr r14, r3
	clrlwi. r0, r0, 31
	beq L_at1
	lwz r0, 0x24(r15)
	lis r3, itemDataTable@ha
	lwz r4, 0x8(r15)
	addi r6, r3, itemDataTable@l
	slwi r3, r0, 2
	lwz r0, dat_8041d9c0(r0)
	lwzx r5, r4, r3
	addi r4, r1, 0xe4
	lfs f1, float_neg150_8041dac8(r0)
	li r3, 0x0
	mulli r7, r5, 0x28
	stw r0, 0xe4(r1)
	lfs f2, float_120_8041dacc(r0)
	lfs f3, float_300_8041dad0(r0)
	add r5, r6, r7
	lwzx r17, r6, r7
	lwz r18, 0x8(r5)
	lfs f4, float_50_8041dad4(r0)
	lfs f5, float_20_8041dad8(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	bl FontDrawEdge
	lwz r0, dat_8041d9c4(r0)
	addi r3, r1, 0xe0
	stw r0, 0xe0(r1)
	bl FontDrawColor
	mr r3, r17
	bl strlen
	mulli r4, r3, 0x18
	lis r0, 0x4330
	stw r0, 0x6d8(r1)
	mr r3, r17
	lfd f1, 0x3f0(r30)
	srwi r0, r4, 2
	mulli r0, r0, -0x1
	lfs f2, float_108_8041dadc(r0)
	xoris r0, r0, 0x8000
	stw r0, 0x6dc(r1)
	lfd f0, 0x6d8(r1)
	fsubs f1, f0, f1
	bl FontDrawString
	bl FontDrawEdgeOff
	lwz r0, dat_8041d9c8(r0)
	addi r4, r1, 0xdc
	lfs f1, float_neg240_8041dae0(r0)
	li r3, 0x0
	stw r0, 0xdc(r1)
	lfs f2, float_neg130_8041dae4(r0)
	lfs f3, float_480_8041dae8(r0)
	lfs f4, float_70_8041daec(r0)
	lfs f5, float_20_8041dad8(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	mr r3, r18
	bl msgSearch
	mr r5, r3
	li r3, -0xdc
	li r4, -0x8a
	bl FontDrawMessage
	li r17, 0x0
	li r19, 0x0
	mr r18, r17
	b L_at2
	L_at3:
	lwz r3, 0x8(r15)
	lwzx r0, r3, r17
	cmpwi r0, 0x0
	beq L_at4
	lwz r3, 0x4(r15)
	addi r4, r1, 0x250
	lwzx r3, r3, r18
	bl mapObjGetPos
	li r3, 0x4
	bl camGetPtr
	mr r21, r3
	lwz r4, 0x19c(r3)
	addi r3, r21, 0x15c
	bl GXSetProjection
	addi r3, r1, 0x354
	bl GXGetProjectionv
	addi r3, r1, 0x33c
	bl GXGetViewportv
	lfs f1, 0x250(r1)
	addi r3, r21, 0x11c
	lfs f2, 0x254(r1)
	addi r4, r1, 0x354
	lfs f3, 0x258(r1)
	addi r5, r1, 0x33c
	addi r6, r1, 0x178
	addi r7, r1, 0x174
	addi r8, r1, 0x170
	bl GXProject
	mr r3, r20
	bl camGetPtr
	lwz r4, 0x19c(r3)
	addi r3, r3, 0x15c
	bl GXSetProjection
	lwz r3, 0x8(r15)
	lwzx r0, r3, r17
	cmpwi r0, 0xf0
	blt L_at5
	cmpwi r0, 0x153
	bge L_at5
	mulli r4, r0, 0x28
	lis r3, itemDataTable@ha
	addi r0, r3, itemDataTable@l
	add r3, r0, r4
	lhz r0, 0x16(r3)
	clrlwi r21, r0, 24
	b L_at6
	L_at5:
	mulli r4, r0, 0x28
	lis r3, itemDataTable@ha
	addi r0, r3, itemDataTable@l
	add r3, r0, r4
	lhz r0, 0x14(r3)
	clrlwi r21, r0, 24
	L_at6:
	lfs f3, float_neg304_8041daf4(r0)
	addi r3, r1, 0x620
	lfs f2, 0x178(r1)
	lfs f1, 0x174(r1)
	lfs f0, float_60_8041dafc(r0)
	fadds f3, f3, f2
	lfs f4, float_8_8041daf0(r0)
	fsubs f0, f1, f0
	lfs f2, float_240_8041daf8(r0)
	fadds f1, f4, f3
	lfs f3, float_0_8041db00(r0)
	fsubs f2, f2, f0
	bl PSMTXTrans
	lwz r0, dat_8041d9cc(r0)
	addi r3, r1, 0x620
	clrlwi r4, r21, 24
	addi r6, r1, 0xd8
	stw r0, 0xd8(r1)
	li r5, 0x1
	bl iconNumberDispGx
	L_at4:
	addi r17, r17, 0x4
	addi r18, r18, 0xc
	addi r19, r19, 0x1
	L_at2:
	lwz r0, 0x18(r15)
	cmpw r19, r0
	blt L_at3
	L_at1:
	lhz r0, 0x0(r15)
	andi. r0, r0, 0xd000
	beq L_at7
	lwz r0, dat_8041d9d0(r0)
	addi r4, r1, 0xd4
	lfs f1, float_neg250_8041db04(r0)
	li r3, 0x0
	stw r0, 0xd4(r1)
	lfs f2, float_neg75_8041db08(r0)
	lfs f3, float_150_8041db0c(r0)
	lfs f4, float_45_8041db10(r0)
	lfs f5, float_20_8041dad8(r0)
	bl windowDispGX_Waku_col
	lfs f1, float_neg220_8041db14(r0)
	addi r3, r1, 0x5f0
	lfs f2, float_neg113_8041db18(r0)
	lfs f3, float_0_8041db00(r0)
	bl PSMTXTrans
	lfs f1, float_0p7_8041db1c(r0)
	addi r3, r1, 0x5c0
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0x5f0
	addi r4, r1, 0x5c0
	mr r5, r3
	bl PSMTXConcat
	lhz r3, 0x0(r15)
	rlwinm. r0, r3, 0, 19, 19
	beq L_at8
	addi r3, r1, 0x5f0
	li r4, 0x10
	li r5, 0x18b
	bl iconDispGx2
	bl pouchGetCoin
	mr r17, r3
	b L_at9
	L_at8:
	rlwinm. r0, r3, 0, 17, 17
	beq L_at10
	addi r3, r1, 0x5f0
	li r4, 0x10
	li r5, 0x102
	bl iconDispGx2
	bl pouchGetSuperCoin
	mr r17, r3
	b L_at9
	L_at10:
	addi r3, r1, 0x5f0
	li r4, 0x10
	li r5, 0x18d
	bl iconDispGx2
	bl pouchGetStarPiece
	mr r17, r3
	L_at9:
	lfs f1, float_neg192_8041db20(r0)
	addi r3, r1, 0x5f0
	lfs f2, float_neg113_8041db18(r0)
	lfs f3, float_0_8041db00(r0)
	bl PSMTXTrans
	addi r3, r1, 0x5f0
	li r4, 0x10
	li r5, 0x1d6
	bl iconDispGx2
	lfs f1, float_neg126_8041db24(r0)
	addi r3, r1, 0x5f0
	lfs f2, float_neg113_8041db18(r0)
	lfs f3, float_0_8041db00(r0)
	bl PSMTXTrans
	lwz r0, dat_8041d9d4(r0)
	addi r3, r1, 0x5f0
	addi r6, r1, 0xd0
	li r5, 0x0
	stw r0, 0xd0(r1)
	lwz r4, 0x2c(r15)
	bl iconNumberDispGx
	lwz r4, 0x2c(r15)
	subf. r5, r4, r17
	beq L_at11
	lis r3, 0x6666
	addi r0, r3, 0x6667
	mulhw r0, r0, r5
	srawi r0, r0, 2
	srwi r3, r0, 31
	add. r5, r0, r3
	bne L_at12
	cmpw r17, r4
	li r0, -0x1
	ble L_at13
	li r0, 0x1
	L_at13:
	mr r5, r0
	L_at12:
	lwz r0, 0x5c(r15)
	clrlwi. r0, r0, 31
	beq L_at14
	lwz r0, 0x2c(r15)
	add r0, r0, r5
	stw r0, 0x2c(r15)
	bl statusWinForceUpdateCoin
	L_at14:
	lwz r4, 0x5c(r15)
	lis r3, 0x1b4f
	subi r0, r3, 0x7e4b
	addi r3, r4, 0x1
	stw r3, 0x5c(r15)
	lwz r4, 0x5c(r15)
	mulhw r0, r0, r4
	srawi r0, r0, 7
	srwi r3, r0, 31
	add r0, r0, r3
	mulli r0, r0, 0x4b0
	subf r0, r0, r4
	stw r0, 0x5c(r15)
	lwz r0, unk_804189fc(r0)
	cmpwi r0, 0x0
	bne L_at11
	addi r3, r30, 0x184
	bl psndSFXOn
	li r0, 0x7
	stw r0, unk_804189fc(r0)
	L_at11:
	lwz r3, unk_804189fc(r0)
	cmpwi r3, 0x0
	ble L_at7
	subi r0, r3, 0x1
	stw r0, unk_804189fc(r0)
	L_at7:
	lhz r0, 0x0(r15)
	rlwinm. r0, r0, 0, 18, 18
	beq L_at15
	lwz r0, dat_8041d9d8(r0)
	addi r4, r1, 0xcc
	lfs f1, float_neg250_8041db04(r0)
	li r3, 0x0
	stw r0, 0xcc(r1)
	lfs f2, float_neg130_8041dae4(r0)
	lfs f3, float_150_8041db0c(r0)
	lfs f4, float_45_8041db10(r0)
	lfs f5, float_20_8041dad8(r0)
	bl windowDispGX_Waku_col
	lfs f1, float_neg210_8041db28(r0)
	addi r3, r1, 0x590
	lfs f2, float_neg166_8041db2c(r0)
	lfs f3, float_0_8041db00(r0)
	bl PSMTXTrans
	lfs f1, float_1p1_8041db30(r0)
	addi r3, r1, 0x560
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0x590
	addi r4, r1, 0x560
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x590
	li r4, 0x10
	li r5, 0x1f1
	bl iconDispGx2
	lfs f1, float_neg126_8041db24(r0)
	addi r3, r1, 0x590
	lfs f2, float_neg168_8041db34(r0)
	lfs f3, float_0_8041db00(r0)
	bl PSMTXTrans
	lwz r0, dat_8041d9dc(r0)
	addi r3, r1, 0x590
	addi r6, r1, 0xc8
	li r5, 0x0
	stw r0, 0xc8(r1)
	lwz r4, 0x30(r15)
	bl iconNumberDispGx
	lwz r3, gp(r0)
	lwz r0, 0x1c(r3)
	clrlwi. r0, r0, 30
	bne L_at15
	lwz r4, 0x30(r15)
	lha r5, 0x9c(r14)
	subf. r6, r4, r5
	beq L_at15
	lis r3, 0x6666
	addi r0, r3, 0x6667
	mulhw r0, r0, r6
	srawi r0, r0, 2
	srwi r3, r0, 31
	add. r6, r0, r3
	bne L_at16
	cmpw r5, r4
	li r0, -0x1
	ble L_at17
	li r0, 0x1
	L_at17:
	mr r6, r0
	L_at16:
	lwz r0, 0x30(r15)
	add r0, r0, r6
	stw r0, 0x30(r15)
	L_at15:
	lhz r0, 0x0(r15)
	rlwinm. r0, r0, 0, 23, 23
	beq L_at18
	bl lotteryGetPtr
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 30, 30
	beq L_at18
	lwz r0, dat_8041d9e0(r0)
	addi r4, r1, 0xc4
	lfs f1, float_neg250_8041db04(r0)
	li r3, 0x0
	stw r0, 0xc4(r1)
	lfs f2, float_neg130_8041dae4(r0)
	lfs f3, float_150_8041db0c(r0)
	lfs f4, float_45_8041db10(r0)
	lfs f5, float_20_8041dad8(r0)
	bl windowDispGX_Waku_col
	lfs f1, float_neg220_8041db14(r0)
	addi r3, r1, 0x530
	lfs f2, float_neg172_8041db38(r0)
	lfs f3, float_0_8041db00(r0)
	bl PSMTXTrans
	addi r3, r1, 0x530
	li r4, 0x10
	li r5, 0x140
	bl iconDispGx2
	bl lotteryGetPtr
	lha r5, 0x20(r3)
	addi r3, r1, 0x31c
	la r4, str_8041DB3C(r0)
	crclr 6
	bl sprintf
	lfs f28, float_20_8041dad8(r0)
	addi r18, r1, 0x31c
	lfd f29, 0x3f0(r30)
	li r19, 0x0
	lfs f30, float_neg126_8041db24(r0)
	lis r17, 0x4330
	lfs f31, float_60_8041dafc(r0)
	L_at19:
	xoris r0, r19, 0x8000
	stw r17, 0x6d8(r1)
	lfs f2, float_neg168_8041db34(r0)
	addi r3, r1, 0x530
	stw r0, 0x6dc(r1)
	lfs f3, float_0_8041db00(r0)
	lfd f0, 0x6d8(r1)
	fsubs f0, f0, f29
	fmadds f0, f28, f0, f30
	fsubs f1, f0, f31
	bl PSMTXTrans
	lwz r4, dat_8041d9e4(r0)
	addi r3, r1, 0x530
	lbz r0, 0x0(r18)
	addi r6, r1, 0xc0
	stw r4, 0xc0(r1)
	li r5, 0x0
	extsb r4, r0
	subi r4, r4, 0x30
	bl iconNumberDispGx
	addi r19, r19, 0x1
	addi r18, r18, 0x1
	cmpwi r19, 0x4
	blt L_at19
	L_at18:
	lwz r4, 0x50(r15)
	cmplwi r4, 0x12
	bgt L_at20
	lis r3, jumptable_803755B8@ha
	slwi r0, r4, 2
	addi r3, r3, jumptable_803755B8@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	L_at21:
	li r18, 0x0
	li r19, 0x0
	bl pouchGetKeepItemCnt
	subfic r0, r3, 0x8
	cmpwi r0, 0x0
	ble L_at22
	bl pouchGetKeepItemCnt
	subfic r0, r3, 0x8
	b L_at23
	L_at22:
	li r0, 0x0
	L_at23:
	mulli r14, r0, 0x18
	lis r0, 0x4330
	lwz r5, dat_8041d9e8(r0)
	addi r4, r1, 0xbc
	stw r0, 0x6d8(r1)
	li r3, 0x0
	subfic r0, r14, 0xdc
	lfd f4, 0x3f0(r30)
	xoris r0, r0, 0x8000
	stw r5, 0xbc(r1)
	lfs f1, float_neg24_8041db44(r0)
	stw r0, 0x6dc(r1)
	lfs f2, float_100_8041db48(r0)
	lfd f0, 0x6d8(r1)
	lfs f3, float_300_8041dad0(r0)
	fsubs f4, f0, f4
	lfs f5, float_20_8041dad8(r0)
	bl windowDispGX_Waku_col
	lwz r0, dat_8041d9ec(r0)
	addi r4, r1, 0xb8
	lfs f1, float_51_8041db4c(r0)
	li r3, 0x0
	stw r0, 0xb8(r1)
	lfs f2, float_114_8041db50(r0)
	lfs f3, float_150_8041db0c(r0)
	lfs f4, float_28_8041db54(r0)
	lfs f5, float_8_8041daf0(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	bl FontDrawEdge
	lwz r0, dat_8041d9f0(r0)
	addi r3, r1, 0xb4
	stw r0, 0xb4(r1)
	bl FontDrawColor
	addi r3, r30, 0x194
	bl msgSearch
	lfs f1, float_81_8041db58(r0)
	lfs f2, float_111_8041db5c(r0)
	bl FontDrawString
	bl FontDrawEdgeOff
	addi r3, r1, 0x16c
	addi r4, r1, 0x168
	addi r5, r1, 0x164
	addi r6, r1, 0x160
	bl GXGetScissor
	subfic r6, r14, 0xbe
	li r3, 0x120
	li r4, 0xa2
	li r5, 0x11c
	bl GXSetScissor
	li r17, 0x0
	lis r3, itemDataTable@ha
	mr r16, r17
	addi r14, r3, itemDataTable@l
	L_at24:
	mr r3, r17
	bl pouchKeepItem
	mulli r0, r3, 0x28
	cmpwi r3, 0x0
	add r20, r14, r0
	beq L_at25
	subfic r3, r16, 0x38
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lwz r6, 0x0(r30)
	stw r3, 0x6dc(r1)
	addi r3, r1, 0x1f4
	lwz r5, 0x4(r30)
	li r4, 0x10
	stw r0, 0x6d8(r1)
	lwz r0, 0x8(r30)
	lfd f1, 0x3f0(r30)
	lfd f0, 0x6d8(r1)
	stw r6, 0x1f4(r1)
	fsubs f0, f0, f1
	lfs f1, float_0p5_8041db60(r0)
	stw r5, 0x1f8(r1)
	lhz r5, 0x20(r20)
	stw r0, 0x1fc(r1)
	lfs f2, 0x44(r15)
	fadds f0, f2, f0
	stfs f0, 0x1f8(r1)
	bl iconDispGx
	bl FontDrawStart
	subfic r3, r16, 0x50
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	stw r0, 0x6e0(r1)
	lfd f2, 0x3f0(r30)
	stw r3, 0x6e4(r1)
	lfs f3, 0x44(r15)
	lfd f0, 0x6e0(r1)
	lfs f1, float_36_8041db64(r0)
	fsubs f0, f0, f2
	lwz r3, 0x0(r20)
	fadds f2, f3, f0
	bl FontDrawString
	xoris r3, r18, 0x8000
	lis r0, 0x4330
	stw r3, 0x6ec(r1)
	lfd f2, 0x3f0(r30)
	stw r0, 0x6e8(r1)
	lfs f0, 0x34(r15)
	lfd f1, 0x6e8(r1)
	fsubs f1, f1, f2
	fcmpu cr0, f1, f0
	bne L_at26
	lwz r19, 0x8(r20)
	L_at26:
	addi r16, r16, 0x18
	addi r18, r18, 0x1
	L_at25:
	addi r17, r17, 0x1
	cmpwi r17, 0x20
	blt L_at24
	lwz r3, 0x16c(r1)
	lwz r4, 0x168(r1)
	lwz r5, 0x164(r1)
	lwz r6, 0x160(r1)
	bl GXSetScissor
	cmplwi r19, 0x0
	beq L_at20
	lwz r0, dat_8041d9f4(r0)
	addi r4, r1, 0xb0
	lfs f1, float_neg240_8041dae0(r0)
	li r3, 0x0
	stw r0, 0xb0(r1)
	lfs f2, float_neg130_8041dae4(r0)
	lfs f3, float_480_8041dae8(r0)
	lfs f4, float_70_8041daec(r0)
	lfs f5, float_20_8041dad8(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	mr r3, r19
	bl msgSearch
	mr r5, r3
	li r3, -0xdc
	li r4, -0x8a
	bl FontDrawMessage
	b L_at20
	L_at27:
	cmpwi r4, 0x2
	li r20, 0x0
	li r21, 0x0
	beq L_at28
	cmpwi r4, 0x3
	bne L_at29
	L_at28:
	bl pouchGetHaveItemCnt
	subfic r0, r3, 0x8
	cmpwi r0, 0x0
	ble L_at30
	bl pouchGetHaveItemCnt
	subfic r0, r3, 0x8
	b L_at31
	L_at30:
	li r0, 0x0
	L_at31:
	mulli r14, r0, 0x18
	addi r3, r30, 0x194
	li r22, 0x14
	bl msgSearch
	li r17, 0x1e
	mr r16, r3
	b L_at32
	L_at29:
	cmpwi r4, 0xc
	bne L_at33
	bl pouchGetHaveBadgeCnt
	subfic r0, r3, 0x8
	cmpwi r0, 0x0
	ble L_at34
	bl pouchGetHaveBadgeCnt
	subfic r0, r3, 0x8
	b L_at35
	L_at34:
	li r0, 0x0
	L_at35:
	mulli r14, r0, 0x18
	addi r3, r30, 0x1a8
	li r22, 0xc8
	bl msgSearch
	li r17, 0x28
	mr r16, r3
	b L_at32
	L_at33:
	cmpwi r4, 0xe
	bne L_at36
	lwz r0, 0x58(r15)
	addi r3, r30, 0x1bc
	li r22, 0x152
	subfic r4, r0, 0x8
	neg r0, r4
	andc r0, r0, r4
	srawi r0, r0, 31
	and r0, r4, r0
	mulli r14, r0, 0x18
	bl msgSearch
	li r17, 0x14
	mr r16, r3
	b L_at32
	L_at36:
	cmpwi r4, 0xf
	bne L_at37
	lwz r0, 0x58(r15)
	addi r3, r30, 0x1bc
	subfic r4, r0, 0x8
	mr r22, r0
	neg r0, r4
	andc r0, r0, r4
	srawi r0, r0, 31
	and r0, r4, r0
	mulli r14, r0, 0x18
	bl msgSearch
	li r17, 0x14
	mr r16, r3
	b L_at32
	L_at37:
	cmpwi r4, 0x10
	bne L_at38
	lwz r0, 0x58(r15)
	addi r3, r30, 0x1d0
	li r22, 0x152
	subfic r4, r0, 0x8
	neg r0, r4
	andc r0, r0, r4
	srawi r0, r0, 31
	and r0, r4, r0
	mulli r14, r0, 0x18
	bl msgSearch
	li r17, 0x1e
	mr r16, r3
	b L_at32
	L_at38:
	lwz r0, 0x58(r15)
	addi r3, r30, 0x1a8
	li r22, 0x63
	subfic r4, r0, 0x8
	neg r0, r4
	andc r0, r0, r4
	srawi r0, r0, 31
	and r0, r4, r0
	mulli r14, r0, 0x18
	bl msgSearch
	li r17, 0x28
	mr r16, r3
	L_at32:
	subfic r3, r14, 0xdc
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lwz r5, dat_8041d9f8(r0)
	stw r3, 0x6ec(r1)
	addi r4, r1, 0xac
	lfd f2, 0x3f0(r30)
	li r3, 0x0
	stw r0, 0x6e8(r1)
	lfs f1, float_neg24_8041db44(r0)
	lfd f0, 0x6e8(r1)
	stw r5, 0xac(r1)
	fsubs f4, f0, f2
	lfs f2, float_100_8041db48(r0)
	lfs f3, float_300_8041dad0(r0)
	lfs f5, float_20_8041dad8(r0)
	bl windowDispGX_Waku_col
	lwz r0, dat_8041d9fc(r0)
	addi r4, r1, 0xa8
	lfs f1, float_51_8041db4c(r0)
	li r3, 0x0
	stw r0, 0xa8(r1)
	lfs f2, float_114_8041db50(r0)
	lfs f3, float_150_8041db0c(r0)
	lfs f4, float_28_8041db54(r0)
	lfs f5, float_8_8041daf0(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	bl FontDrawEdge
	lwz r0, dat_8041da00(r0)
	addi r3, r1, 0xa4
	stw r0, 0xa4(r1)
	bl FontDrawColor
	addi r3, r17, 0x33
	lis r0, 0x4330
	xoris r4, r3, 0x8000
	stw r0, 0x6e0(r1)
	lfd f1, 0x3f0(r30)
	mr r3, r16
	stw r4, 0x6e4(r1)
	lfs f2, float_111_8041db5c(r0)
	lfd f0, 0x6e0(r1)
	fsubs f1, f0, f1
	bl FontDrawString
	bl FontDrawEdgeOff
	lwz r0, 0x50(r15)
	cmpwi r0, 0x3
	beq L_at39
	lfs f1, float_244_8041db68(r0)
	addi r3, r1, 0x500
	lfs f2, float_82_8041db6c(r0)
	lfs f3, float_0_8041db00(r0)
	bl PSMTXTrans
	lfs f1, float_0p6_8041db70(r0)
	addi r3, r1, 0x4d0
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0x500
	addi r4, r1, 0x4d0
	mr r5, r3
	bl PSMTXConcat
	lwz r0, dat_8041da04(r0)
	addi r3, r1, 0x500
	addi r6, r1, 0xa0
	li r4, 0x10
	stw r0, 0xa0(r1)
	li r5, 0x211
	bl iconDispGxCol
	lwz r0, 0x50(r15)
	cmpwi r0, 0xd
	bne L_at40
	li r0, 0x18d
	b L_at41
	L_at40:
	cmpwi r0, 0x10
	bne L_at42
	li r0, 0x13f
	b L_at41
	L_at42:
	li r0, 0x18b
	L_at41:
	lwz r7, 0xc(r30)
	addi r3, r1, 0x1e8
	lwz r6, 0x10(r30)
	clrlwi r5, r0, 16
	lwz r0, 0x14(r30)
	li r4, 0x10
	stw r7, 0x1e8(r1)
	lfs f1, float_0p6_8041db70(r0)
	stw r6, 0x1ec(r1)
	stw r0, 0x1f0(r1)
	bl iconDispGx
	L_at39:
	addi r3, r1, 0x15c
	addi r4, r1, 0x158
	addi r5, r1, 0x154
	addi r6, r1, 0x150
	bl GXGetScissor
	subfic r6, r14, 0xbe
	li r3, 0x120
	li r4, 0xa2
	li r5, 0x11c
	bl GXSetScissor
	lis r3, badge_bottakuru100_table@ha
	li r19, 0x0
	addi r16, r3, badge_bottakuru100_table@l
	lis r3, itemDataTable@ha
	mr r17, r19
	addi r14, r3, itemDataTable@l
	b L_at43
	L_at44:
	lwz r0, 0x50(r15)
	li r18, 0x0
	lwz r3, dat_8041da08(r0)
	cmplwi r0, 0x10
	stw r3, 0x14c(r1)
	bgt L_at45
	lis r3, jumptable_80375574@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_80375574@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	L_at46:
	mr r3, r19
	bl pouchHaveItem
	mr r23, r3
	b L_at45
	L_at47:
	mr r3, r19
	bl pouchHaveBadge
	mr r23, r3
	b L_at45
	L_at48:
	lwz r3, bdsw(r0)
	addi r0, r19, 0xf0
	extsh r4, r0
	addi r3, r3, 0x19
	bl badgeShop_get
	extsh r23, r3
	addi r3, r19, 0xf0
	bl badgeShop_ThrowCheck
	subf. r0, r3, r23
	ble L_at49
	addi r23, r19, 0xf0
	b L_at45
	L_at49:
	li r23, 0x0
	b L_at45
	L_at50:
	lwz r3, bdsw(r0)
	addi r0, r19, 0xf0
	extsh r4, r0
	addi r3, r3, 0x32
	bl badgeShop_get
	extsh. r0, r3
	ble L_at51
	addi r23, r19, 0xf0
	b L_at45
	L_at51:
	li r23, 0x0
	b L_at45
	L_at52:
	lwz r3, bdsw(r0)
	addi r0, r19, 0x1
	extsh r4, r0
	addi r3, r3, 0x4b
	bl badgeShop_get
	extsh. r0, r3
	ble L_at53
	addi r23, r19, 0x1
	b L_at45
	L_at53:
	li r23, 0x0
	b L_at45
	L_at54:
	lwz r23, 0x0(r16)
	b L_at45
	L_at55:
	lwz r3, bdsw(r0)
	addi r0, r19, 0x1
	extsh r4, r0
	addi r3, r3, 0xa0
	bl badgeShop_get
	extsh. r0, r3
	ble L_at56
	addi r23, r19, 0x1
	b L_at45
	L_at56:
	li r23, 0x0
	L_at45:
	mulli r0, r23, 0x28
	cmpwi r23, 0x0
	add r24, r14, r0
	beq L_at57
	lwz r0, 0x50(r15)
	cmpwi r0, 0xd
	bne L_at58
	bl pouchGetStarPiece
	lhz r0, 0x18(r24)
	cmpw r0, r3
	ble L_at58
	lwz r0, dat_8041da0c(r0)
	li r18, 0x20
	stw r0, 0x14c(r1)
	L_at58:
	subfic r0, r17, 0x38
	lis r4, 0x4330
	xoris r0, r0, 0x8000
	lwz r6, 0x18(r30)
	stw r0, 0x6ec(r1)
	ori r0, r18, 0x10
	lwz r5, 0x1c(r30)
	addi r3, r1, 0x1dc
	stw r4, 0x6e8(r1)
	clrlwi r4, r0, 16
	lwz r0, 0x20(r30)
	lfd f1, 0x3f0(r30)
	lfd f0, 0x6e8(r1)
	stw r6, 0x1dc(r1)
	fsubs f0, f0, f1
	lfs f1, float_0p5_8041db60(r0)
	stw r5, 0x1e0(r1)
	lhz r5, 0x20(r24)
	stw r0, 0x1e4(r1)
	lfs f2, 0x44(r15)
	fadds f0, f2, f0
	stfs f0, 0x1e0(r1)
	bl iconDispGx
	bl FontDrawStart
	lfs f1, float_0p8_8041db74(r0)
	bl FontDrawScale
	lwz r0, 0x14c(r1)
	addi r3, r1, 0x9c
	stw r0, 0x9c(r1)
	bl FontDrawColor
	subfic r18, r17, 0x50
	lis r0, 0x4330
	xoris r3, r18, 0x8000
	stw r0, 0x6e0(r1)
	lfd f2, 0x3f0(r30)
	stw r3, 0x6e4(r1)
	lfs f3, 0x44(r15)
	lfd f1, 0x6e0(r1)
	lfs f0, float_2_8041db78(r0)
	fsubs f2, f1, f2
	lfs f1, float_36_8041db64(r0)
	lwz r3, 0x0(r24)
	fadds f2, f3, f2
	fsubs f2, f2, f0
	bl FontDrawString
	lwz r0, 0x50(r15)
	cmpwi r0, 0x3
	beq L_at59
	cmpwi r0, 0xe
	beq L_at60
	bge L_at61
	cmpwi r0, 0xc
	beq L_at62
	bge L_at63
	cmpwi r0, 0xb
	bge L_at64
	b L_at62
	L_at61:
	cmpwi r0, 0x10
	beq L_at65
	bge L_at62
	b L_at66
	L_at60:
	lhz r0, 0x14(r24)
	lis r3, 0x6666
	addi r5, r3, 0x6667
	addi r3, r1, 0x2fc
	mulli r0, r0, 0xc
	la r4, str_8041DB7C(r0)
	mulhw r0, r5, r0
	srawi r0, r0, 2
	srwi r5, r0, 31
	add r5, r0, r5
	crclr 6
	bl sprintf
	lfs f28, float_1_8041db80(r0)
	li r25, 0x0
	b L_at67
	L_at66:
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x6a9
	bl evtGetValue
	lhz r0, 0x14(r24)
	addi r4, r3, 0xb
	lis r5, 0x6666
	addi r3, r1, 0x2fc
	mullw r0, r0, r4
	la r4, str_8041DB84(r0)
	addi r5, r5, 0x6667
	mulhw r0, r5, r0
	srawi r0, r0, 2
	srwi r5, r0, 31
	add r5, r0, r5
	crclr 6
	bl sprintf
	lfs f28, float_1_8041db80(r0)
	li r25, -0xe
	b L_at67
	L_at65:
	lhz r0, 0x14(r24)
	lis r3, 0x5555
	addi r6, r3, 0x5556
	addi r3, r1, 0x2fc
	slwi r5, r0, 1
	la r4, str_8041DB88(r0)
	addi r0, r5, 0x2
	mulhw r5, r6, r0
	srwi r0, r5, 31
	add r5, r5, r0
	crclr 6
	bl sprintf
	lfs f28, float_0p8_8041db74(r0)
	li r25, -0x14
	b L_at67
	L_at64:
	lhz r5, 0x14(r24)
	addi r3, r1, 0x2fc
	la r4, str_8041DB7C(r0)
	crclr 6
	bl sprintf
	lfs f28, float_1_8041db80(r0)
	li r25, 0x0
	b L_at67
	L_at63:
	lhz r5, 0x18(r24)
	addi r3, r1, 0x2fc
	la r4, str_8041DB7C(r0)
	crclr 6
	bl sprintf
	lfs f28, float_1_8041db80(r0)
	li r25, 0x0
	b L_at67
	L_at62:
	lhz r5, 0x1a(r24)
	addi r3, r1, 0x2fc
	la r4, str_8041DB7C(r0)
	crclr 6
	bl sprintf
	li r25, 0x0
	lfs f28, float_1_8041db80(r0)
	L_at67:
	bl FontDrawStart
	fmr f1, f28
	bl FontDrawScale
	lwz r0, 0x14c(r1)
	addi r3, r1, 0x98
	stw r0, 0x98(r1)
	bl FontDrawColor
	lis r4, 0x4330
	xoris r0, r18, 0x8000
	stw r0, 0x6e4(r1)
	addi r0, r25, 0xe2
	xoris r0, r0, 0x8000
	lfd f4, 0x3f0(r30)
	stw r4, 0x6e0(r1)
	addi r3, r1, 0x2fc
	lfs f1, 0x44(r15)
	lfd f0, 0x6e0(r1)
	stw r0, 0x6ec(r1)
	fsubs f0, f0, f4
	stw r4, 0x6e8(r1)
	lfd f3, 0x6e8(r1)
	fadds f2, f1, f0
	fsubs f1, f3, f4
	bl FontDrawString
	L_at59:
	xoris r3, r20, 0x8000
	lis r0, 0x4330
	stw r3, 0x6ec(r1)
	lfd f2, 0x3f0(r30)
	stw r0, 0x6e8(r1)
	lfs f0, 0x34(r15)
	lfd f1, 0x6e8(r1)
	fsubs f1, f1, f2
	fcmpu cr0, f1, f0
	bne L_at68
	lwz r21, 0x8(r24)
	L_at68:
	addi r17, r17, 0x18
	addi r20, r20, 0x1
	L_at57:
	addi r16, r16, 0x4
	addi r19, r19, 0x1
	L_at43:
	cmpw r19, r22
	blt L_at44
	lwz r3, 0x15c(r1)
	lwz r4, 0x158(r1)
	lwz r5, 0x154(r1)
	lwz r6, 0x150(r1)
	bl GXSetScissor
	cmplwi r21, 0x0
	beq L_at20
	lwz r0, dat_8041da10(r0)
	addi r4, r1, 0x94
	lfs f1, float_neg240_8041dae0(r0)
	li r3, 0x0
	stw r0, 0x94(r1)
	lfs f2, float_neg130_8041dae4(r0)
	lfs f3, float_480_8041dae8(r0)
	lfs f4, float_70_8041daec(r0)
	lfs f5, float_20_8041dad8(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	mr r3, r21
	bl msgSearch
	mr r5, r3
	li r3, -0xdc
	li r4, -0x8a
	bl FontDrawMessage
	b L_at20
	L_at69:
	lwz r0, 0x58(r15)
	lis r3, _jdt@ha
	cmpwi r4, 0x11
	subfic r4, r0, 0x8
	addi r14, r3, _jdt@l
	neg r0, r4
	andc r0, r0, r4
	srawi r0, r0, 31
	and r0, r4, r0
	mulli r17, r0, 0x18
	bne L_at70
	addi r3, r30, 0x1e4
	bl msgSearch
	addi r18, r14, 0x21
	mr r16, r3
	b L_at71
	L_at70:
	addi r3, r30, 0x1f8
	bl msgSearch
	addi r18, r14, 0x2e
	mr r16, r3
	L_at71:
	subfic r3, r17, 0xdc
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lwz r5, dat_8041da14(r0)
	stw r3, 0x6ec(r1)
	addi r4, r1, 0x90
	lfd f2, 0x3f0(r30)
	li r3, 0x0
	stw r0, 0x6e8(r1)
	lfs f1, float_neg24_8041db44(r0)
	lfd f0, 0x6e8(r1)
	stw r5, 0x90(r1)
	fsubs f4, f0, f2
	lfs f2, float_100_8041db48(r0)
	lfs f3, float_300_8041dad0(r0)
	lfs f5, float_20_8041dad8(r0)
	bl windowDispGX_Waku_col
	lwz r0, dat_8041da18(r0)
	addi r4, r1, 0x8c
	lfs f1, float_51_8041db4c(r0)
	li r3, 0x0
	stw r0, 0x8c(r1)
	lfs f2, float_114_8041db50(r0)
	lfs f3, float_150_8041db0c(r0)
	lfs f4, float_28_8041db54(r0)
	lfs f5, float_8_8041daf0(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	bl FontDrawEdge
	lwz r0, dat_8041da1c(r0)
	addi r3, r1, 0x88
	stw r0, 0x88(r1)
	bl FontDrawColor
	lfs f1, float_71_8041db8c(r0)
	mr r3, r16
	lfs f2, float_111_8041db5c(r0)
	bl FontDrawString
	bl FontDrawEdgeOff
	lwz r0, 0x50(r15)
	cmpwi r0, 0x11
	bne L_at72
	lfs f1, float_244_8041db68(r0)
	addi r3, r1, 0x4a0
	lfs f2, float_82_8041db6c(r0)
	lfs f3, float_0_8041db00(r0)
	bl PSMTXTrans
	lfs f1, float_0p6_8041db70(r0)
	addi r3, r1, 0x470
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0x4a0
	addi r4, r1, 0x470
	mr r5, r3
	bl PSMTXConcat
	lwz r0, dat_8041da20(r0)
	addi r3, r1, 0x4a0
	addi r6, r1, 0x84
	li r4, 0x10
	stw r0, 0x84(r1)
	li r5, 0x211
	bl iconDispGxCol
	lwz r7, 0x24(r30)
	addi r3, r1, 0x1d0
	lwz r6, 0x28(r30)
	li r4, 0x10
	lwz r0, 0x2c(r30)
	li r5, 0x18b
	stw r7, 0x1d0(r1)
	lfs f1, float_0p6_8041db70(r0)
	stw r6, 0x1d4(r1)
	stw r0, 0x1d8(r1)
	bl iconDispGx
	L_at72:
	addi r3, r1, 0x148
	addi r4, r1, 0x144
	addi r5, r1, 0x140
	addi r6, r1, 0x13c
	bl GXGetScissor
	subfic r6, r17, 0xbe
	li r3, 0x120
	li r4, 0xa2
	li r5, 0x11c
	bl GXSetScissor
	li r16, 0x0
	lwz r17, 0x0(r14)
	lfd f31, 0x3f0(r30)
	mr r14, r16
	lis r19, 0x4330
	b L_at73
	L_at74:
	lha r4, 0xc(r17)
	mr r3, r18
	bl johoya_get
	extsh. r0, r3
	beq L_at75
	addi r3, r1, 0x2dc
	la r4, float_0_8041db90(r0)
	crclr 6
	bl sprintf
	lwz r0, dat_8041da24(r0)
	stw r0, 0x138(r1)
	b L_at76
	L_at75:
	lha r5, 0xa(r17)
	addi r3, r1, 0x2dc
	la r4, str_8041DB84(r0)
	crclr 6
	bl sprintf
	lwz r0, dat_8041da28(r0)
	stw r0, 0x138(r1)
	L_at76:
	bl FontDrawStart
	lwz r6, 0x4(r17)
	li r4, 0x0
	lha r5, 0x8(r17)
	addi r3, r1, 0x80
	lwz r0, 0x138(r1)
	lbzx r21, r6, r5
	stbx r4, r6, r5
	stw r0, 0x80(r1)
	bl FontDrawColor
	lfs f1, float_0p8_8041db74(r0)
	bl FontDrawScale
	subfic r20, r14, 0x50
	stw r19, 0x6e8(r1)
	xoris r0, r20, 0x8000
	lfs f2, 0x44(r15)
	stw r0, 0x6ec(r1)
	lfs f1, float_1_8041db80(r0)
	lfd f0, 0x6e8(r1)
	lwz r3, 0x4(r17)
	fsubs f0, f0, f31
	fadds f2, f2, f0
	bl FontDrawString
	lwz r3, 0x4(r17)
	lha r0, 0x8(r17)
	stbx r21, r3, r0
	lwz r0, 0x50(r15)
	cmpwi r0, 0x11
	bne L_at77
	bl FontDrawStart
	lwz r0, 0x138(r1)
	addi r3, r1, 0x7c
	stw r0, 0x7c(r1)
	bl FontDrawColor
	xoris r3, r20, 0x8000
	lis r0, 0x4330
	stw r3, 0x6ec(r1)
	addi r3, r1, 0x2dc
	lfd f2, 0x3f0(r30)
	stw r0, 0x6e8(r1)
	lfs f3, 0x44(r15)
	lfd f0, 0x6e8(r1)
	lfs f1, float_221_8041db94(r0)
	fsubs f0, f0, f2
	fadds f2, f3, f0
	bl FontDrawString
	L_at77:
	addi r14, r14, 0x18
	addi r16, r16, 0x1
	addi r17, r17, 0x10
	L_at73:
	lwz r0, 0x58(r15)
	cmpw r16, r0
	blt L_at74
	lwz r3, 0x148(r1)
	lwz r4, 0x144(r1)
	lwz r5, 0x140(r1)
	lwz r6, 0x13c(r1)
	bl GXSetScissor
	b L_at20
	L_at78:
	lwz r25, 0x30(r30)
	lis r0, 0x4330
	lwz r5, 0x34(r30)
	addi r4, r1, 0x78
	lwz r23, 0x38(r30)
	li r24, 0x0
	lwz r22, 0x3c(r30)
	li r3, 0x0
	lwz r21, 0x40(r30)
	lwz r20, 0x44(r30)
	lwz r19, 0x48(r30)
	lwz r18, 0x4c(r30)
	lwz r17, 0x50(r30)
	lwz r12, 0x54(r30)
	lwz r11, 0x58(r30)
	lwz r10, 0x5c(r30)
	lwz r9, 0x60(r30)
	lwz r8, 0x64(r30)
	lwz r7, 0x68(r30)
	lwz r6, 0x6c(r30)
	stw r25, 0x430(r1)
	lfd f4, 0x3f0(r30)
	stw r5, 0x434(r1)
	lwz r5, dat_8041da2c(r0)
	stw r23, 0x438(r1)
	lfs f1, float_neg24_8041db44(r0)
	stw r22, 0x43c(r1)
	lfs f2, float_100_8041db48(r0)
	stw r21, 0x440(r1)
	lfs f3, float_300_8041dad0(r0)
	stw r20, 0x444(r1)
	lfs f5, float_20_8041dad8(r0)
	stw r19, 0x448(r1)
	stw r18, 0x44c(r1)
	stw r17, 0x450(r1)
	stw r12, 0x454(r1)
	stw r11, 0x458(r1)
	stw r10, 0x45c(r1)
	stw r9, 0x460(r1)
	stw r8, 0x464(r1)
	stw r7, 0x468(r1)
	stw r6, 0x46c(r1)
	lwz r6, 0x58(r15)
	stw r0, 0x6e8(r1)
	subfic r6, r6, 0x8
	neg r0, r6
	stw r5, 0x78(r1)
	andc r0, r0, r6
	srawi r0, r0, 31
	and r0, r6, r0
	mulli r17, r0, 0x18
	subfic r0, r17, 0xdc
	xoris r0, r0, 0x8000
	stw r0, 0x6ec(r1)
	lfd f0, 0x6e8(r1)
	fsubs f4, f0, f4
	bl windowDispGX_Waku_col
	lwz r0, dat_8041da30(r0)
	addi r4, r1, 0x74
	lfs f1, float_16_8041db98(r0)
	li r3, 0x0
	stw r0, 0x74(r1)
	lfs f2, float_114_8041db50(r0)
	lfs f3, float_120_8041dacc(r0)
	lfs f4, float_28_8041db54(r0)
	lfs f5, float_8_8041daf0(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	bl FontDrawEdge
	lwz r0, dat_8041da34(r0)
	addi r3, r1, 0x70
	stw r0, 0x70(r1)
	bl FontDrawColor
	addi r3, r30, 0x20c
	bl msgSearch
	lfs f1, float_41_8041db9c(r0)
	lfs f2, float_111_8041db5c(r0)
	bl FontDrawString
	bl FontDrawEdgeOff
	lwz r0, dat_8041da38(r0)
	addi r4, r1, 0x6c
	lfs f1, float_167_8041dba0(r0)
	li r3, 0x0
	stw r0, 0x6c(r1)
	lfs f2, float_114_8041db50(r0)
	lfs f3, float_85_8041dba4(r0)
	lfs f4, float_28_8041db54(r0)
	lfs f5, float_8_8041daf0(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	bl FontDrawEdge
	lwz r0, dat_8041da3c(r0)
	addi r3, r1, 0x68
	stw r0, 0x68(r1)
	bl FontDrawColor
	addi r3, r30, 0x220
	bl msgSearch
	lfs f1, float_177_8041dba8(r0)
	lfs f2, float_111_8041db5c(r0)
	bl FontDrawString
	bl FontDrawEdgeOff
	addi r3, r1, 0x134
	addi r4, r1, 0x130
	addi r5, r1, 0x12c
	addi r6, r1, 0x128
	bl GXGetScissor
	subfic r6, r17, 0xbe
	li r3, 0x120
	li r4, 0xa2
	li r5, 0x11c
	bl GXSetScissor
	li r22, 0x0
	la r17, party_id_table(r0)
	mr r25, r22
	la r19, party_icon_table(r0)
	mr r18, r22
	la r20, party_labelname_table(r0)
	b L_at79
	L_at80:
	lwz r0, 0x50(r15)
	cmpwi r0, 0x5
	beq L_at81
	cmpwi r0, 0x6
	bne L_at82
	L_at81:
	bl partyChkJoin
	cmpwi r3, 0x0
	beq L_at83
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x6022
	bl evtGetValue
	cmpwi r3, 0x0
	bne L_at84
	lwz r0, 0x0(r17)
	mulli r3, r0, 0xe
	addi r0, r3, 0xc
	lhax r0, r14, r0
	cmpwi r0, 0x1
	bge L_at85
	lwz r0, dat_8041da40(r0)
	li r23, 0x0
	li r21, 0x0
	stw r0, 0x124(r1)
	b L_at86
	L_at85:
	lwz r0, dat_8041da44(r0)
	li r23, 0x1
	li r21, 0x20
	stw r0, 0x124(r1)
	b L_at86
	L_at84:
	lwz r0, 0x0(r17)
	mulli r3, r0, 0xe
	addi r0, r3, 0xc
	lhax r0, r14, r0
	cmpwi r0, 0x2
	bge L_at87
	lwz r0, dat_8041da48(r0)
	li r23, 0x0
	li r21, 0x0
	stw r0, 0x124(r1)
	b L_at86
	L_at87:
	lwz r0, dat_8041da4c(r0)
	li r23, 0x2
	li r21, 0x20
	stw r0, 0x124(r1)
	b L_at86
	L_at82:
	bl partyChkJoin
	cmpwi r3, 0x0
	beq L_at83
	lwz r0, 0x4c(r15)
	lwz r3, 0x0(r17)
	cmpw r0, r3
	beq L_at83
	mulli r3, r3, 0xe
	addi r0, r3, 0xc
	lhax r0, r14, r0
	cmpwi r0, 0x0
	ble L_at88
	lwz r0, dat_8041da50(r0)
	li r23, 0x0
	li r21, 0x0
	stw r0, 0x124(r1)
	b L_at86
	L_at88:
	lwz r0, dat_8041da54(r0)
	li r23, 0x1
	li r21, 0x20
	stw r0, 0x124(r1)
	L_at86:
	subfic r3, r18, 0x38
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lwz r4, 0x70(r30)
	stw r3, 0x6ec(r1)
	lwz r3, 0x74(r30)
	stw r0, 0x6e8(r1)
	lwz r0, 0x78(r30)
	lfd f1, 0x3f0(r30)
	lfd f0, 0x6e8(r1)
	stw r4, 0x1c4(r1)
	lwz r4, 0x0(r19)
	fsubs f0, f0, f1
	stw r3, 0x1c8(r1)
	cmpwi r4, 0x158
	stw r0, 0x1cc(r1)
	lfs f1, 0x44(r15)
	fadds f0, f1, f0
	stfs f0, 0x1c8(r1)
	bne L_at89
	li r3, 0x4
	bl pouchGetPartyColor
	cmplwi r3, 0x6
	bgt L_at90
	lis r4, jumptable_80375558@ha
	slwi r0, r3, 2
	addi r3, r4, jumptable_80375558@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	L_at91:
	li r4, 0x158
	b L_at89
	L_at92:
	li r4, 0x159
	b L_at89
	L_at93:
	li r4, 0x15a
	b L_at89
	L_at94:
	li r4, 0x15b
	b L_at89
	L_at95:
	li r4, 0x15c
	b L_at89
	L_at96:
	li r4, 0x15d
	b L_at89
	L_at90:
	li r4, 0x15e
	L_at89:
	ori r0, r21, 0x10
	lfs f1, float_0p5_8041db60(r0)
	addi r3, r1, 0x1c4
	clrlwi r5, r4, 16
	clrlwi r4, r0, 16
	bl iconDispGx
	bl FontDrawStart
	lwz r0, 0x124(r1)
	addi r3, r1, 0x64
	stw r0, 0x64(r1)
	bl FontDrawColor
	cmplwi r22, 0x6
	bgt L_at97
	lis r3, jumptable_8037553C@ha
	addi r3, r3, jumptable_8037553C@l
	lwzx r0, r3, r25
	mtctr r0
	bctr
	L_at98:
	addi r3, r30, 0x234
	bl msgSearch
	mr r16, r3
	b L_at97
	L_at99:
	addi r3, r30, 0x240
	bl msgSearch
	mr r16, r3
	b L_at97
	L_at100:
	addi r3, r30, 0x24c
	bl msgSearch
	mr r16, r3
	b L_at97
	L_at101:
	bl pouchGetYoshiName
	mr r16, r3
	b L_at97
	L_at102:
	addi r3, r30, 0x258
	bl msgSearch
	mr r16, r3
	b L_at97
	L_at103:
	addi r3, r30, 0x264
	bl msgSearch
	mr r16, r3
	b L_at97
	L_at104:
	addi r3, r30, 0x270
	bl msgSearch
	mr r16, r3
	L_at97:
	subfic r21, r18, 0x50
	lis r0, 0x4330
	xoris r4, r21, 0x8000
	stw r0, 0x6e8(r1)
	lfd f2, 0x3f0(r30)
	mr r3, r16
	stw r4, 0x6ec(r1)
	lfs f3, 0x44(r15)
	lfd f0, 0x6e8(r1)
	lfs f1, float_36_8041db64(r0)
	fsubs f0, f0, f2
	fadds f2, f3, f0
	bl FontDrawString
	lwz r0, 0x0(r17)
	addi r3, r1, 0x2bc
	la r4, str_8041DBAC(r0)
	mulli r5, r0, 0xe
	addi r0, r5, 0xc
	lhax r5, r14, r0
	crclr 6
	bl sprintf
	bl FontDrawStart
	xoris r3, r21, 0x8000
	lis r0, 0x4330
	stw r3, 0x6e4(r1)
	addi r3, r1, 0x2bc
	lfd f2, 0x3f0(r30)
	stw r0, 0x6e0(r1)
	lfs f3, 0x44(r15)
	lfd f0, 0x6e0(r1)
	lfs f1, float_236_8041dbb0(r0)
	fsubs f0, f0, f2
	fadds f2, f3, f0
	bl FontDrawString
	xoris r3, r24, 0x8000
	lis r0, 0x4330
	stw r3, 0x6dc(r1)
	lfd f2, 0x3f0(r30)
	stw r0, 0x6d8(r1)
	lfs f0, 0x34(r15)
	lfd f1, 0x6d8(r1)
	fsubs f1, f1, f2
	fcmpu cr0, f1, f0
	bne L_at105
	cmpwi r23, 0x0
	bne L_at106
	addi r3, r1, 0x240
	la r4, str_8041DBB4(r0)
	crclr 6
	bl sprintf
	b L_at107
	L_at106:
	addi r3, r1, 0x240
	addi r4, r30, 0x27c
	crclr 6
	bl sprintf
	L_at107:
	lwz r0, 0x50(r15)
	cmpwi r0, 0x5
	beq L_at108
	cmpwi r0, 0x6
	bne L_at109
	L_at108:
	addi r3, r1, 0x230
	addi r4, r30, 0x284
	crclr 6
	bl sprintf
	b L_at110
	L_at109:
	addi r3, r1, 0x230
	addi r4, r30, 0x28c
	crclr 6
	bl sprintf
	L_at110:
	lwz r0, 0x0(r17)
	addi r3, r1, 0x430
	lwz r8, 0x0(r20)
	addi r4, r30, 0x298
	mulli r7, r0, 0xe
	addi r5, r1, 0x240
	addi r6, r1, 0x230
	addi r0, r7, 0xc
	lhax r7, r14, r0
	addi r7, r7, 0x1
	crclr 6
	bl sprintf
	L_at105:
	addi r18, r18, 0x18
	addi r24, r24, 0x1
	L_at83:
	addi r17, r17, 0x4
	addi r19, r19, 0x4
	addi r20, r20, 0x4
	addi r22, r22, 0x1
	addi r25, r25, 0x4
	L_at79:
	lwz r3, 0x0(r17)
	cmpwi r3, 0x0
	bne L_at80
	lwz r3, 0x134(r1)
	lwz r4, 0x130(r1)
	lwz r5, 0x12c(r1)
	lwz r6, 0x128(r1)
	bl GXSetScissor
	lbz r0, 0x430(r1)
	extsb. r0, r0
	beq L_at20
	lwz r0, dat_8041da58(r0)
	addi r4, r1, 0x60
	lfs f1, float_neg240_8041dae0(r0)
	li r3, 0x0
	stw r0, 0x60(r1)
	lfs f2, float_neg130_8041dae4(r0)
	lfs f3, float_480_8041dae8(r0)
	lfs f4, float_70_8041daec(r0)
	lfs f5, float_20_8041dad8(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	addi r3, r1, 0x430
	bl msgSearch
	mr r5, r3
	li r3, -0xdc
	li r4, -0x8a
	bl FontDrawMessage
	b L_at20
	L_at111:
	lwz r23, 0x7c(r30)
	lis r0, 0x4330
	lwz r5, 0x80(r30)
	addi r4, r1, 0x5c
	lwz r22, 0x84(r30)
	li r18, 0x0
	lwz r21, 0x88(r30)
	li r3, 0x0
	lwz r20, 0x8c(r30)
	lwz r19, 0x90(r30)
	lwz r17, 0x94(r30)
	lwz r16, 0x98(r30)
	lwz r14, 0x9c(r30)
	lwz r12, 0xa0(r30)
	lwz r11, 0xa4(r30)
	lwz r10, 0xa8(r30)
	lwz r9, 0xac(r30)
	lwz r8, 0xb0(r30)
	lwz r7, 0xb4(r30)
	lwz r6, 0xb8(r30)
	stw r23, 0x3f0(r1)
	lfd f4, 0x3f0(r30)
	stw r5, 0x3f4(r1)
	lwz r5, dat_8041da5c(r0)
	stw r22, 0x3f8(r1)
	lfs f1, float_neg24_8041db44(r0)
	stw r21, 0x3fc(r1)
	lfs f2, float_100_8041db48(r0)
	stw r20, 0x400(r1)
	lfs f3, float_300_8041dad0(r0)
	stw r19, 0x404(r1)
	lfs f5, float_20_8041dad8(r0)
	stw r17, 0x408(r1)
	stw r16, 0x40c(r1)
	stw r14, 0x410(r1)
	stw r12, 0x414(r1)
	stw r11, 0x418(r1)
	stw r10, 0x41c(r1)
	stw r9, 0x420(r1)
	stw r8, 0x424(r1)
	stw r7, 0x428(r1)
	stw r6, 0x42c(r1)
	lwz r6, 0x58(r15)
	stw r0, 0x6e8(r1)
	subfic r6, r6, 0x8
	neg r0, r6
	stw r5, 0x5c(r1)
	andc r0, r0, r6
	srawi r0, r0, 31
	and r0, r6, r0
	mulli r14, r0, 0x18
	subfic r0, r14, 0xdc
	xoris r0, r0, 0x8000
	stw r0, 0x6ec(r1)
	lfd f0, 0x6e8(r1)
	fsubs f4, f0, f4
	bl windowDispGX_Waku_col
	lwz r0, dat_8041da60(r0)
	addi r4, r1, 0x58
	lfs f1, float_16_8041db98(r0)
	li r3, 0x0
	stw r0, 0x58(r1)
	lfs f2, float_114_8041db50(r0)
	lfs f3, float_120_8041dacc(r0)
	lfs f4, float_28_8041db54(r0)
	lfs f5, float_8_8041daf0(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	bl FontDrawEdge
	lwz r0, dat_8041da64(r0)
	addi r3, r1, 0x54
	stw r0, 0x54(r1)
	bl FontDrawColor
	addi r3, r30, 0x2a8
	bl msgSearch
	lfs f1, float_21_8041dbbc(r0)
	lfs f2, float_111_8041db5c(r0)
	bl FontDrawString
	bl FontDrawEdgeOff
	lwz r0, dat_8041da68(r0)
	addi r4, r1, 0x50
	lfs f1, float_167_8041dba0(r0)
	li r3, 0x0
	stw r0, 0x50(r1)
	lfs f2, float_114_8041db50(r0)
	lfs f3, float_85_8041dba4(r0)
	lfs f4, float_28_8041db54(r0)
	lfs f5, float_8_8041daf0(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	bl FontDrawEdge
	lwz r0, dat_8041da6c(r0)
	addi r3, r1, 0x4c
	stw r0, 0x4c(r1)
	bl FontDrawColor
	addi r3, r30, 0x2bc
	bl msgSearch
	lfs f1, float_177_8041dba8(r0)
	lfs f2, float_111_8041db5c(r0)
	bl FontDrawString
	bl FontDrawEdgeOff
	addi r3, r1, 0x120
	addi r4, r1, 0x11c
	addi r5, r1, 0x118
	addi r6, r1, 0x114
	bl GXGetScissor
	subfic r6, r14, 0xbe
	li r3, 0x120
	li r4, 0xa2
	li r5, 0x11c
	bl GXSetScissor
	li r20, 0x0
	la r14, mario_status_point_table(r0)
	lfd f31, 0x3f0(r30)
	mr r29, r20
	mr r27, r14
	la r24, mario_status_henka_table(r0)
	la r28, mario_status_icon_table(r0)
	la r26, mario_status_name_table(r0)
	la r25, mario_status_labelname_table(r0)
	lis r31, 0x4330
	b L_at112
	L_at113:
	la r5, mario_status_henka_table(r0)
	mr r6, r14
	li r8, 0x0
	li r7, 0x0
	mtctr r0
	cmpwi r0, 0x0
	ble L_at114
	L_at115:
	xoris r0, r7, 0x8000
	stw r31, 0x6e8(r1)
	lfs f0, 0x34(r15)
	stw r0, 0x6ec(r1)
	lfd f1, 0x6e8(r1)
	fsubs f1, f1, f31
	fcmpu cr0, f1, f0
	beq L_at116
	lwz r3, 0x0(r6)
	lwz r4, 0x0(r5)
	lha r0, 0x0(r3)
	subf. r0, r4, r0
	bgt L_at116
	li r8, 0x1
	L_at116:
	addi r5, r5, 0x4
	addi r6, r6, 0x4
	addi r7, r7, 0x1
	bdnz L_at115
	L_at114:
	cmpwi r8, 0x0
	bne L_at117
	lwz r0, dat_8041da70(r0)
	li r16, 0x0
	li r3, 0x0
	stw r0, 0x110(r1)
	b L_at118
	L_at117:
	lwz r0, dat_8041da74(r0)
	li r16, 0x1
	li r3, 0x20
	stw r0, 0x110(r1)
	L_at118:
	subfic r23, r29, 0x38
	lwz r5, 0xbc(r30)
	xoris r0, r23, 0x8000
	lwz r7, 0xc0(r30)
	stw r0, 0x6ec(r1)
	ori r22, r3, 0x10
	lwz r6, 0xc4(r30)
	addi r3, r1, 0x1b8
	stw r31, 0x6e8(r1)
	clrlwi r4, r22, 16
	lwz r0, 0x0(r28)
	lfd f0, 0x6e8(r1)
	stw r5, 0x1b8(r1)
	clrlwi r5, r0, 16
	fsubs f0, f0, f31
	lfs f1, float_0p5_8041db60(r0)
	stw r7, 0x1bc(r1)
	stw r6, 0x1c0(r1)
	lfs f2, 0x44(r15)
	fadds f0, f2, f0
	stfs f0, 0x1bc(r1)
	bl iconDispGx
	bl FontDrawStart
	lwz r0, 0x110(r1)
	addi r3, r1, 0x48
	stw r0, 0x48(r1)
	bl FontDrawColor
	lwz r6, 0x0(r27)
	addi r3, r1, 0x29c
	lwz r5, 0x0(r26)
	la r4, str_8041DBC0(r0)
	lha r6, 0x0(r6)
	crclr 6
	bl sprintf
	subfic r21, r29, 0x50
	stw r31, 0x6e0(r1)
	xoris r0, r21, 0x8000
	lfs f2, 0x44(r15)
	stw r0, 0x6e4(r1)
	addi r3, r1, 0x29c
	lfs f1, float_36_8041db64(r0)
	lfd f0, 0x6e0(r1)
	fsubs f0, f0, f31
	fadds f2, f2, f0
	bl FontDrawString
	xoris r0, r18, 0x8000
	lwz r4, gp(r0)
	stw r0, 0x6dc(r1)
	li r3, 0x7
	lwz r4, 0x1c(r4)
	li r0, 0x2
	stw r31, 0x6d8(r1)
	clrlwi r4, r4, 28
	lfs f0, 0x34(r15)
	lfd f1, 0x6d8(r1)
	subfc r3, r4, r3
	subfe r3, r3, r3
	fsubs f1, f1, f31
	andc r19, r0, r3
	fcmpu cr0, f1, f0
	bne L_at119
	cmpwi r16, 0x0
	bne L_at120
	addi r3, r1, 0x220
	la r4, str_8041DBB4(r0)
	crclr 6
	bl sprintf
	b L_at121
	L_at120:
	addi r3, r1, 0x220
	addi r4, r30, 0x27c
	crclr 6
	bl sprintf
	L_at121:
	lwz r6, 0x0(r25)
	addi r3, r1, 0x3f0
	addi r4, r30, 0x2d0
	addi r5, r1, 0x220
	crclr 6
	bl sprintf
	lwz r3, 0x0(r27)
	lwz r0, 0x0(r24)
	lha r3, 0x0(r3)
	slwi r0, r0, 1
	add. r17, r3, r0
	ble L_at122
	li r16, 0x1b5
	b L_at123
	L_at122:
	li r16, 0x162
	li r19, 0x0
	L_at123:
	lis r6, 0x4330
	xoris r0, r23, 0x8000
	stw r0, 0x6e4(r1)
	xoris r0, r19, 0x8000
	lwz r9, 0xc8(r30)
	addi r3, r1, 0x1ac
	stw r6, 0x6e0(r1)
	clrlwi r4, r22, 16
	lwz r8, 0xcc(r30)
	clrlwi r5, r16, 16
	lwz r7, 0xd0(r30)
	lfd f3, 0x3f0(r30)
	lfd f0, 0x6e0(r1)
	stw r9, 0x1ac(r1)
	fsubs f0, f0, f3
	lfs f1, float_0p5_8041db60(r0)
	stw r8, 0x1b0(r1)
	stw r7, 0x1b4(r1)
	lfs f2, 0x44(r15)
	stw r0, 0x6ec(r1)
	fadds f0, f2, f0
	stw r6, 0x6e8(r1)
	lfd f2, 0x6e8(r1)
	fsubs f2, f2, f3
	fadds f0, f2, f0
	stfs f0, 0x1b0(r1)
	bl iconDispGx
	lis r6, 0x4330
	xoris r0, r23, 0x8000
	stw r0, 0x6f4(r1)
	xoris r0, r19, 0x8000
	lwz r9, 0xd4(r30)
	addi r3, r1, 0x1a0
	stw r6, 0x6f0(r1)
	clrlwi r4, r22, 16
	lwz r8, 0xd8(r30)
	clrlwi r5, r16, 16
	lwz r7, 0xdc(r30)
	lfd f3, 0x3f0(r30)
	lfd f0, 0x6f0(r1)
	stw r9, 0x1a0(r1)
	fsubs f0, f0, f3
	lfs f1, float_0p5_8041db60(r0)
	stw r8, 0x1a4(r1)
	stw r7, 0x1a8(r1)
	lfs f2, 0x44(r15)
	stw r0, 0x6dc(r1)
	fadds f0, f2, f0
	stw r6, 0x6d8(r1)
	lfd f2, 0x6d8(r1)
	fsubs f2, f2, f3
	fadds f0, f2, f0
	stfs f0, 0x1a4(r1)
	bl iconDispGx
	b L_at124
	L_at119:
	lwz r3, 0x0(r27)
	lwz r4, 0x0(r24)
	lha r0, 0x0(r3)
	subf. r17, r4, r0
	ble L_at125
	li r5, 0x1b6
	b L_at126
	L_at125:
	li r5, 0x162
	li r19, 0x0
	L_at126:
	lis r6, 0x4330
	xoris r0, r23, 0x8000
	stw r0, 0x6f4(r1)
	xoris r0, r19, 0x8000
	lwz r9, 0xe0(r30)
	addi r3, r1, 0x194
	stw r6, 0x6f0(r1)
	clrlwi r4, r22, 16
	lwz r8, 0xe4(r30)
	clrlwi r5, r5, 16
	lwz r7, 0xe8(r30)
	lfd f3, 0x3f0(r30)
	lfd f0, 0x6f0(r1)
	stw r9, 0x194(r1)
	fsubs f0, f0, f3
	lfs f1, float_0p5_8041db60(r0)
	stw r8, 0x198(r1)
	stw r7, 0x19c(r1)
	lfs f2, 0x44(r15)
	stw r0, 0x6ec(r1)
	fadds f2, f2, f0
	stw r6, 0x6e8(r1)
	lfd f0, 0x6e8(r1)
	fsubs f0, f0, f3
	fsubs f0, f2, f0
	stfs f0, 0x198(r1)
	bl iconDispGx
	L_at124:
	cmpwi r17, 0x0
	ble L_at127
	mr r5, r17
	addi r3, r1, 0x29c
	la r4, str_8041DB84(r0)
	crclr 6
	bl sprintf
	b L_at128
	L_at127:
	mr r5, r17
	addi r3, r1, 0x29c
	la r4, str_8041DBC8(r0)
	crclr 6
	bl sprintf
	L_at128:
	bl FontDrawStart
	xoris r0, r21, 0x8000
	stw r31, 0x6f0(r1)
	lfs f2, 0x44(r15)
	addi r3, r1, 0x29c
	stw r0, 0x6f4(r1)
	lfs f1, float_206_8041dbd0(r0)
	lfd f0, 0x6f0(r1)
	fsubs f0, f0, f31
	fadds f2, f2, f0
	bl FontDrawString
	addi r29, r29, 0x18
	addi r18, r18, 0x1
	addi r28, r28, 0x4
	addi r27, r27, 0x4
	addi r26, r26, 0x4
	addi r25, r25, 0x4
	addi r24, r24, 0x4
	addi r20, r20, 0x1
	L_at112:
	lwz r0, 0x58(r15)
	cmpw r20, r0
	blt L_at113
	lwz r3, 0x120(r1)
	lwz r4, 0x11c(r1)
	lwz r5, 0x118(r1)
	lwz r6, 0x114(r1)
	bl GXSetScissor
	lbz r0, 0x3f0(r1)
	extsb. r0, r0
	beq L_at20
	lwz r0, dat_8041da78(r0)
	addi r4, r1, 0x44
	lfs f1, float_neg240_8041dae0(r0)
	li r3, 0x0
	stw r0, 0x44(r1)
	lfs f2, float_neg130_8041dae4(r0)
	lfs f3, float_480_8041dae8(r0)
	lfs f4, float_70_8041daec(r0)
	lfs f5, float_20_8041dad8(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	addi r3, r1, 0x3f0
	bl msgSearch
	mr r5, r3
	li r3, -0xdc
	li r4, -0x8a
	bl FontDrawMessage
	b L_at20
	L_at129:
	lwz r22, 0xec(r30)
	lis r0, 0x4330
	lwz r5, 0xf0(r30)
	addi r4, r1, 0x40
	lwz r21, 0xf4(r30)
	li r27, 0x0
	lwz r20, 0xf8(r30)
	li r3, 0x0
	lwz r19, 0xfc(r30)
	lwz r18, 0x100(r30)
	lwz r17, 0x104(r30)
	lwz r16, 0x108(r30)
	lwz r14, 0x10c(r30)
	lwz r12, 0x110(r30)
	lwz r11, 0x114(r30)
	lwz r10, 0x118(r30)
	lwz r9, 0x11c(r30)
	lwz r8, 0x120(r30)
	lwz r7, 0x124(r30)
	lwz r6, 0x128(r30)
	stw r22, 0x3b0(r1)
	lfd f4, 0x3f0(r30)
	stw r5, 0x3b4(r1)
	lwz r5, dat_8041da7c(r0)
	stw r21, 0x3b8(r1)
	lfs f1, float_neg24_8041db44(r0)
	stw r20, 0x3bc(r1)
	lfs f2, float_100_8041db48(r0)
	stw r19, 0x3c0(r1)
	lfs f3, float_300_8041dad0(r0)
	stw r18, 0x3c4(r1)
	lfs f5, float_20_8041dad8(r0)
	stw r17, 0x3c8(r1)
	stw r16, 0x3cc(r1)
	stw r14, 0x3d0(r1)
	stw r12, 0x3d4(r1)
	stw r11, 0x3d8(r1)
	stw r10, 0x3dc(r1)
	stw r9, 0x3e0(r1)
	stw r8, 0x3e4(r1)
	stw r7, 0x3e8(r1)
	stw r6, 0x3ec(r1)
	lwz r6, 0x58(r15)
	stw r0, 0x6f0(r1)
	subfic r6, r6, 0x8
	neg r0, r6
	stw r5, 0x40(r1)
	andc r0, r0, r6
	srawi r0, r0, 31
	and r0, r6, r0
	mulli r14, r0, 0x18
	subfic r0, r14, 0xdc
	xoris r0, r0, 0x8000
	stw r0, 0x6f4(r1)
	lfd f0, 0x6f0(r1)
	fsubs f4, f0, f4
	bl windowDispGX_Waku_col
	lwz r0, dat_8041da80(r0)
	addi r4, r1, 0x3c
	lfs f1, float_16_8041db98(r0)
	li r3, 0x0
	stw r0, 0x3c(r1)
	lfs f2, float_114_8041db50(r0)
	lfs f3, float_120_8041dacc(r0)
	lfs f4, float_28_8041db54(r0)
	lfs f5, float_8_8041daf0(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	bl FontDrawEdge
	lwz r0, dat_8041da84(r0)
	addi r3, r1, 0x38
	stw r0, 0x38(r1)
	bl FontDrawColor
	addi r3, r30, 0x2a8
	bl msgSearch
	lfs f1, float_21_8041dbbc(r0)
	lfs f2, float_111_8041db5c(r0)
	bl FontDrawString
	bl FontDrawEdgeOff
	lwz r0, dat_8041da88(r0)
	addi r4, r1, 0x34
	lfs f1, float_167_8041dba0(r0)
	li r3, 0x0
	stw r0, 0x34(r1)
	lfs f2, float_114_8041db50(r0)
	lfs f3, float_85_8041dba4(r0)
	lfs f4, float_28_8041db54(r0)
	lfs f5, float_8_8041daf0(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	bl FontDrawEdge
	lwz r0, dat_8041da8c(r0)
	addi r3, r1, 0x30
	stw r0, 0x30(r1)
	bl FontDrawColor
	addi r3, r30, 0x2bc
	bl msgSearch
	lfs f1, float_177_8041dba8(r0)
	lfs f2, float_111_8041db5c(r0)
	bl FontDrawString
	bl FontDrawEdgeOff
	addi r3, r1, 0x10c
	addi r4, r1, 0x108
	addi r5, r1, 0x104
	addi r6, r1, 0x100
	bl GXGetScissor
	subfic r6, r14, 0xbe
	li r3, 0x120
	li r4, 0xa2
	li r5, 0x11c
	bl GXSetScissor
	li r25, 0x0
	la r23, mario_status_point_table(r0)
	la r22, mario_status_henka_table(r0)
	lfd f31, 0x3f0(r30)
	mr r16, r25
	mr r18, r23
	mr r21, r22
	la r17, mario_status_icon_table(r0)
	la r19, mario_status_name_table(r0)
	la r20, mario_status_labelname_table(r0)
	lis r14, 0x4330
	b L_at130
	L_at131:
	mr r5, r22
	mr r6, r23
	li r8, 0x0
	li r7, 0x0
	mtctr r0
	cmpwi r0, 0x0
	ble L_at132
	L_at133:
	xoris r0, r7, 0x8000
	stw r14, 0x6f0(r1)
	lfs f0, 0x34(r15)
	stw r0, 0x6f4(r1)
	lfd f1, 0x6f0(r1)
	fsubs f1, f1, f31
	fcmpu cr0, f1, f0
	beq L_at134
	lwz r3, 0x0(r6)
	lwz r4, 0x0(r5)
	lha r0, 0x0(r3)
	subf. r0, r4, r0
	bgt L_at134
	addi r8, r8, 0x1
	L_at134:
	addi r5, r5, 0x4
	addi r6, r6, 0x4
	addi r7, r7, 0x1
	bdnz L_at133
	L_at132:
	cmpwi r8, 0x2
	bge L_at135
	lwz r0, dat_8041da90(r0)
	li r26, 0x0
	li r3, 0x0
	stw r0, 0xfc(r1)
	b L_at136
	L_at135:
	lwz r0, dat_8041da94(r0)
	li r26, 0x1
	li r3, 0x20
	stw r0, 0xfc(r1)
	L_at136:
	subfic r0, r16, 0x38
	lwz r5, 0x12c(r30)
	xoris r0, r0, 0x8000
	lwz r7, 0x130(r30)
	stw r0, 0x6f4(r1)
	ori r0, r3, 0x10
	lwz r6, 0x134(r30)
	addi r3, r1, 0x188
	stw r14, 0x6f0(r1)
	clrlwi r4, r0, 16
	lwz r0, 0x0(r17)
	lfd f0, 0x6f0(r1)
	stw r5, 0x188(r1)
	clrlwi r5, r0, 16
	fsubs f0, f0, f31
	lfs f1, float_0p5_8041db60(r0)
	stw r7, 0x18c(r1)
	stw r6, 0x190(r1)
	lfs f2, 0x44(r15)
	fadds f0, f2, f0
	stfs f0, 0x18c(r1)
	bl iconDispGx
	bl FontDrawStart
	lwz r0, 0xfc(r1)
	addi r3, r1, 0x2c
	stw r0, 0x2c(r1)
	bl FontDrawColor
	lwz r6, 0x0(r18)
	addi r3, r1, 0x27c
	lwz r5, 0x0(r19)
	la r4, str_8041DBC0(r0)
	lha r6, 0x0(r6)
	crclr 6
	bl sprintf
	subfic r24, r16, 0x50
	stw r14, 0x6e8(r1)
	xoris r0, r24, 0x8000
	lfs f2, 0x44(r15)
	stw r0, 0x6ec(r1)
	addi r3, r1, 0x27c
	lfs f1, float_36_8041db64(r0)
	lfd f0, 0x6e8(r1)
	fsubs f0, f0, f31
	fadds f2, f2, f0
	bl FontDrawString
	xoris r0, r27, 0x8000
	stw r14, 0x6e0(r1)
	lfs f0, 0x34(r15)
	stw r0, 0x6e4(r1)
	lfd f1, 0x6e0(r1)
	fsubs f1, f1, f31
	fcmpu cr0, f1, f0
	bne L_at137
	cmpwi r26, 0x0
	bne L_at138
	addi r3, r1, 0x210
	la r4, str_8041DBB4(r0)
	crclr 6
	bl sprintf
	b L_at139
	L_at138:
	addi r3, r1, 0x210
	addi r4, r30, 0x27c
	crclr 6
	bl sprintf
	L_at139:
	lwz r6, 0x0(r20)
	addi r3, r1, 0x3b0
	addi r4, r30, 0x2d0
	addi r5, r1, 0x210
	crclr 6
	bl sprintf
	lwz r3, 0x0(r18)
	lwz r0, 0x0(r21)
	lha r3, 0x0(r3)
	add. r5, r3, r0
	ble L_at140
	addi r3, r1, 0x27c
	la r4, str_8041DB84(r0)
	crclr 6
	bl sprintf
	b L_at141
	L_at140:
	addi r3, r1, 0x27c
	la r4, str_8041DBC8(r0)
	crclr 6
	bl sprintf
	L_at141:
	bl FontDrawStart
	xoris r3, r24, 0x8000
	lis r0, 0x4330
	stw r3, 0x6f4(r1)
	addi r3, r1, 0x27c
	lfd f2, 0x3f0(r30)
	stw r0, 0x6f0(r1)
	lfs f3, 0x44(r15)
	lfd f0, 0x6f0(r1)
	lfs f1, float_206_8041dbd0(r0)
	fsubs f0, f0, f2
	fadds f2, f3, f0
	bl FontDrawString
	L_at137:
	addi r16, r16, 0x18
	addi r27, r27, 0x1
	addi r17, r17, 0x4
	addi r18, r18, 0x4
	addi r19, r19, 0x4
	addi r20, r20, 0x4
	addi r21, r21, 0x4
	addi r25, r25, 0x1
	L_at130:
	lwz r0, 0x58(r15)
	cmpw r25, r0
	blt L_at131
	lwz r3, 0x10c(r1)
	lwz r4, 0x108(r1)
	lwz r5, 0x104(r1)
	lwz r6, 0x100(r1)
	bl GXSetScissor
	lbz r0, 0x3b0(r1)
	extsb. r0, r0
	beq L_at20
	lwz r0, dat_8041da98(r0)
	addi r4, r1, 0x28
	lfs f1, float_neg240_8041dae0(r0)
	li r3, 0x0
	stw r0, 0x28(r1)
	lfs f2, float_neg130_8041dae4(r0)
	lfs f3, float_480_8041dae8(r0)
	lfs f4, float_70_8041daec(r0)
	lfs f5, float_20_8041dad8(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	addi r3, r1, 0x3b0
	bl msgSearch
	mr r5, r3
	li r3, -0xdc
	li r4, -0x8a
	bl FontDrawMessage
	b L_at20
	L_at142:
	lwz r22, 0x138(r30)
	lis r0, 0x4330
	lwz r5, 0x13c(r30)
	addi r4, r1, 0x24
	lwz r21, 0x140(r30)
	li r23, 0x0
	lwz r20, 0x144(r30)
	li r3, 0x0
	lwz r19, 0x148(r30)
	lwz r18, 0x14c(r30)
	lwz r17, 0x150(r30)
	lwz r16, 0x154(r30)
	lwz r14, 0x158(r30)
	lwz r12, 0x15c(r30)
	lwz r11, 0x160(r30)
	lwz r10, 0x164(r30)
	lwz r9, 0x168(r30)
	lwz r8, 0x16c(r30)
	lwz r7, 0x170(r30)
	lwz r6, 0x174(r30)
	stw r22, 0x370(r1)
	lfd f4, 0x3f0(r30)
	stw r5, 0x374(r1)
	lwz r5, dat_8041da9c(r0)
	stw r21, 0x378(r1)
	lfs f1, float_neg24_8041db44(r0)
	stw r20, 0x37c(r1)
	lfs f2, float_100_8041db48(r0)
	stw r19, 0x380(r1)
	lfs f3, float_300_8041dad0(r0)
	stw r18, 0x384(r1)
	lfs f5, float_20_8041dad8(r0)
	stw r17, 0x388(r1)
	stw r16, 0x38c(r1)
	stw r14, 0x390(r1)
	stw r12, 0x394(r1)
	stw r11, 0x398(r1)
	stw r10, 0x39c(r1)
	stw r9, 0x3a0(r1)
	stw r8, 0x3a4(r1)
	stw r7, 0x3a8(r1)
	stw r6, 0x3ac(r1)
	lwz r6, 0x58(r15)
	stw r0, 0x6f0(r1)
	subfic r6, r6, 0x8
	neg r0, r6
	stw r5, 0x24(r1)
	andc r0, r0, r6
	srawi r0, r0, 31
	and r0, r6, r0
	mulli r14, r0, 0x18
	subfic r0, r14, 0xdc
	xoris r0, r0, 0x8000
	stw r0, 0x6f4(r1)
	lfd f0, 0x6f0(r1)
	fsubs f4, f0, f4
	bl windowDispGX_Waku_col
	lwz r0, dat_8041daa0(r0)
	addi r4, r1, 0x20
	lfs f1, float_16_8041db98(r0)
	li r3, 0x0
	stw r0, 0x20(r1)
	lfs f2, float_114_8041db50(r0)
	lfs f3, float_120_8041dacc(r0)
	lfs f4, float_28_8041db54(r0)
	lfs f5, float_8_8041daf0(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	bl FontDrawEdge
	lwz r0, dat_8041daa4(r0)
	addi r3, r1, 0x1c
	stw r0, 0x1c(r1)
	bl FontDrawColor
	addi r3, r30, 0x2a8
	bl msgSearch
	lfs f1, float_21_8041dbbc(r0)
	lfs f2, float_111_8041db5c(r0)
	bl FontDrawString
	bl FontDrawEdgeOff
	lwz r0, dat_8041daa8(r0)
	addi r4, r1, 0x18
	lfs f1, float_167_8041dba0(r0)
	li r3, 0x0
	stw r0, 0x18(r1)
	lfs f2, float_114_8041db50(r0)
	lfs f3, float_85_8041dba4(r0)
	lfs f4, float_28_8041db54(r0)
	lfs f5, float_8_8041daf0(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	bl FontDrawEdge
	lwz r0, dat_8041daac(r0)
	addi r3, r1, 0x14
	stw r0, 0x14(r1)
	bl FontDrawColor
	addi r3, r30, 0x2bc
	bl msgSearch
	lfs f1, float_177_8041dba8(r0)
	lfs f2, float_111_8041db5c(r0)
	bl FontDrawString
	bl FontDrawEdgeOff
	addi r3, r1, 0xf8
	addi r4, r1, 0xf4
	addi r5, r1, 0xf0
	addi r6, r1, 0xec
	bl GXGetScissor
	subfic r6, r14, 0xbe
	li r3, 0x120
	li r4, 0xa2
	li r5, 0x11c
	bl GXSetScissor
	li r22, 0x0
	la r14, mario_status_henka_table(r0)
	mr r17, r22
	la r16, mario_status_point_table(r0)
	la r18, mario_status_icon_table(r0)
	la r19, mario_status_name_table(r0)
	la r20, mario_status_labelname_table(r0)
	L_at143:
	lwz r0, 0x4c(r15)
	cmpw r22, r0
	beq L_at144
	lwz r3, 0x0(r16)
	lwz r4, 0x0(r14)
	lha r0, 0x0(r3)
	subf. r0, r4, r0
	ble L_at145
	lwz r0, dat_8041dab0(r0)
	li r24, 0x0
	li r3, 0x0
	stw r0, 0xe8(r1)
	b L_at146
	L_at145:
	lwz r0, dat_8041dab4(r0)
	li r24, 0x1
	li r3, 0x20
	stw r0, 0xe8(r1)
	L_at146:
	subfic r0, r17, 0x38
	lis r4, 0x4330
	xoris r0, r0, 0x8000
	lwz r7, 0x178(r30)
	stw r0, 0x6f4(r1)
	ori r0, r3, 0x10
	lwz r5, 0x17c(r30)
	addi r3, r1, 0x17c
	stw r4, 0x6f0(r1)
	clrlwi r4, r0, 16
	lwz r6, 0x180(r30)
	lfd f1, 0x3f0(r30)
	lfd f0, 0x6f0(r1)
	stw r7, 0x17c(r1)
	fsubs f0, f0, f1
	lwz r0, 0x0(r18)
	stw r5, 0x180(r1)
	lfs f1, float_0p5_8041db60(r0)
	clrlwi r5, r0, 16
	stw r6, 0x184(r1)
	lfs f2, 0x44(r15)
	fadds f0, f2, f0
	stfs f0, 0x180(r1)
	bl iconDispGx
	bl FontDrawStart
	lwz r0, 0xe8(r1)
	addi r3, r1, 0x10
	stw r0, 0x10(r1)
	bl FontDrawColor
	lwz r6, 0x0(r16)
	addi r3, r1, 0x25c
	lwz r5, 0x0(r19)
	la r4, str_8041DBC0(r0)
	lha r6, 0x0(r6)
	crclr 6
	bl sprintf
	subfic r21, r17, 0x50
	lis r0, 0x4330
	xoris r4, r21, 0x8000
	stw r0, 0x6e8(r1)
	lfd f2, 0x3f0(r30)
	addi r3, r1, 0x25c
	stw r4, 0x6ec(r1)
	lfs f3, 0x44(r15)
	lfd f0, 0x6e8(r1)
	lfs f1, float_36_8041db64(r0)
	fsubs f0, f0, f2
	fadds f2, f3, f0
	bl FontDrawString
	xoris r3, r23, 0x8000
	lis r0, 0x4330
	stw r3, 0x6e4(r1)
	lfd f2, 0x3f0(r30)
	stw r0, 0x6e0(r1)
	lfs f0, 0x34(r15)
	lfd f1, 0x6e0(r1)
	fsubs f1, f1, f2
	fcmpu cr0, f1, f0
	bne L_at147
	cmpwi r24, 0x0
	bne L_at148
	addi r3, r1, 0x200
	la r4, str_8041DBB4(r0)
	crclr 6
	bl sprintf
	b L_at149
	L_at148:
	addi r3, r1, 0x200
	addi r4, r30, 0x27c
	crclr 6
	bl sprintf
	L_at149:
	lwz r6, 0x0(r20)
	addi r3, r1, 0x370
	addi r4, r30, 0x2e0
	addi r5, r1, 0x200
	crclr 6
	bl sprintf
	lwz r3, 0x0(r16)
	lwz r4, 0x0(r14)
	lha r0, 0x0(r3)
	subf. r5, r4, r0
	ble L_at150
	addi r3, r1, 0x25c
	la r4, str_8041DB84(r0)
	crclr 6
	bl sprintf
	b L_at151
	L_at150:
	addi r3, r1, 0x25c
	la r4, str_8041DBC8(r0)
	crclr 6
	bl sprintf
	L_at151:
	bl FontDrawStart
	xoris r3, r21, 0x8000
	lis r0, 0x4330
	stw r3, 0x6f4(r1)
	addi r3, r1, 0x25c
	lfd f2, 0x3f0(r30)
	stw r0, 0x6f0(r1)
	lfs f3, 0x44(r15)
	lfd f0, 0x6f0(r1)
	lfs f1, float_206_8041dbd0(r0)
	fsubs f0, f0, f2
	fadds f2, f3, f0
	bl FontDrawString
	L_at147:
	addi r17, r17, 0x18
	addi r23, r23, 0x1
	L_at144:
	addi r22, r22, 0x1
	addi r16, r16, 0x4
	cmpwi r22, 0x3
	addi r18, r18, 0x4
	addi r19, r19, 0x4
	addi r20, r20, 0x4
	addi r14, r14, 0x4
	blt L_at143
	lwz r3, 0xf8(r1)
	lwz r4, 0xf4(r1)
	lwz r5, 0xf0(r1)
	lwz r6, 0xec(r1)
	bl GXSetScissor
	lbz r0, 0x370(r1)
	extsb. r0, r0
	beq L_at20
	lwz r0, dat_8041dab8(r0)
	addi r4, r1, 0xc
	lfs f1, float_neg240_8041dae0(r0)
	li r3, 0x0
	stw r0, 0xc(r1)
	lfs f2, float_neg130_8041dae4(r0)
	lfs f3, float_480_8041dae8(r0)
	lfs f4, float_70_8041daec(r0)
	lfs f5, float_20_8041dad8(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	addi r3, r1, 0x370
	bl msgSearch
	mr r5, r3
	li r3, -0xdc
	li r4, -0x8a
	bl FontDrawMessage
	L_at20:
	lwz r0, 0x50(r15)
	cmpwi r0, 0x0
	beq L_at152
	cmpwi r0, 0x1
	beq L_at152
	cmplwi r0, 0x12
	li r16, 0x0
	bgt L_at153
	lis r3, jumptable_803754F0@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_803754F0@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	L_at154:
	addi r3, r30, 0x2f0
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x650
	bl strcpy
	b L_at153
	L_at155:
	addi r3, r30, 0x304
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x650
	bl strcpy
	b L_at153
	L_at156:
	addi r3, r30, 0x318
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x650
	bl strcpy
	b L_at153
	L_at157:
	addi r3, r30, 0x32c
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x650
	bl strcpy
	b L_at153
	L_at158:
	addi r3, r30, 0x344
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x650
	bl strcpy
	b L_at153
	L_at159:
	addi r3, r30, 0x358
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x650
	bl strcpy
	b L_at153
	L_at160:
	addi r3, r30, 0x36c
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x650
	bl strcpy
	b L_at153
	L_at161:
	addi r3, r30, 0x380
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x650
	bl strcpy
	b L_at153
	L_at162:
	addi r3, r30, 0x380
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x650
	bl strcpy
	b L_at153
	L_at163:
	addi r3, r30, 0x398
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x650
	bl strcpy
	b L_at153
	L_at164:
	addi r3, r30, 0x3b0
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x650
	bl strcpy
	b L_at153
	L_at165:
	addi r3, r30, 0x3c4
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x650
	bl strcpy
	L_at153:
	addi r14, r1, 0x650
	li r6, 0x1
	mr r3, r14
	li r5, 0x0
	b L_at166
	L_at167:
	extsb r0, r4
	cmpwi r0, 0xa
	bne L_at168
	addi r3, r1, 0x650
	li r0, 0x0
	add r3, r3, r5
	li r6, 0x2
	stb r0, 0x0(r3)
	addi r16, r3, 0x1
	b L_at169
	L_at168:
	addi r3, r3, 0x1
	addi r5, r5, 0x1
	L_at166:
	lbz r4, 0x0(r3)
	extsb. r0, r4
	bne L_at167
	L_at169:
	subi r3, r6, 0x1
	lis r0, 0x4330
	mulli r5, r3, 0x18
	lwz r6, dat_8041dabc(r0)
	stw r0, 0x6f0(r1)
	addi r4, r1, 0x8
	lfd f4, 0x3f0(r30)
	li r3, 0x0
	addi r0, r5, 0x2d
	stw r6, 0x8(r1)
	xoris r0, r0, 0x8000
	lfs f1, float_neg280_8041dbd4(r0)
	stw r0, 0x6f4(r1)
	lfs f2, float_100_8041db48(r0)
	lfd f0, 0x6f0(r1)
	lfs f3, float_240_8041daf8(r0)
	fsubs f4, f0, f4
	lfs f5, float_20_8041dad8(r0)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	cmplwi r14, 0x0
	beq L_at170
	mr r3, r14
	bl FontGetMessageWidth
	clrlwi r17, r3, 16
	b L_at171
	L_at170:
	li r17, 0x0
	L_at171:
	cmplwi r16, 0x0
	beq L_at172
	mr r3, r16
	bl FontGetMessageWidth
	clrlwi r0, r3, 16
	b L_at173
	L_at172:
	li r0, 0x0
	L_at173:
	cmpw r0, r17
	ble L_at174
	mr r17, r0
	L_at174:
	cmpwi r17, 0xe4
	bgt L_at175
	subfic r3, r17, 0xe4
	srwi r0, r3, 31
	add r0, r0, r3
	srawi r17, r0, 1
	b L_at176
	L_at175:
	xoris r3, r17, 0x8000
	lis r0, 0x4330
	stw r3, 0x6f4(r1)
	lfd f1, 0x3f0(r30)
	stw r0, 0x6f0(r1)
	lfs f2, float_228_8041dbd8(r0)
	lfd f0, 0x6f0(r1)
	fsubs f0, f0, f1
	fdivs f1, f2, f0
	bl FontDrawScale
	li r17, 0x0
	L_at176:
	subi r3, r17, 0x112
	lis r0, 0x4330
	xoris r4, r3, 0x8000
	stw r0, 0x6f0(r1)
	lfd f1, 0x3f0(r30)
	mr r3, r14
	stw r4, 0x6f4(r1)
	lfs f2, float_90_8041dbdc(r0)
	lfd f0, 0x6f0(r1)
	fsubs f1, f0, f1
	bl FontDrawString
	cmplwi r16, 0x0
	beq L_at177
	subi r3, r17, 0x112
	lis r0, 0x4330
	xoris r4, r3, 0x8000
	stw r0, 0x6f0(r1)
	lfd f1, 0x3f0(r30)
	mr r3, r16
	stw r4, 0x6f4(r1)
	lfs f2, float_66_8041dbe0(r0)
	lfd f0, 0x6f0(r1)
	fsubs f1, f0, f1
	bl FontDrawString
	L_at177:
	addi r3, r30, 0x3dc
	li r4, 0x2
	bl iconFlagOff
	lfs f1, 0x3c(r15)
	addi r3, r30, 0x3dc
	lfs f2, 0x40(r15)
	lfs f3, float_0_8041db00(r0)
	bl iconSetPos
	b L_at178
	L_at152:
	addi r3, r30, 0x3dc
	li r4, 0x2
	bl iconFlagOn
	L_at178:
	psq_l f31, 0x778(r1), 0, 0
	lfd f31, 0x770(r1)
	psq_l f30, 0x768(r1), 0, 0
	lfd f30, 0x760(r1)
	psq_l f29, 0x758(r1), 0, 0
	lfd f29, 0x750(r1)
	psq_l f28, 0x748(r1), 0, 0
	lfd f28, 0x740(r1)
	lmw r14, 0x6f8(r1)
	lwz r0, 0x784(r1)
	mtlr r0
	addi r1, r1, 0x780
	blr
}

asm s32 evt_unitwin_main_func(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r6, 0x9c(r3)
	lhz r3, 0x54(r6)
	clrlwi. r0, r3, 31
	beq L_at1
	ori r0, r3, 0x2
	li r3, 0x2
	sth r0, 0x54(r6)
	b L_at2
	L_at1:
	lwz r3, 0x28(r6)
	cmpwi r3, 0x0
	ble L_at3
	subi r0, r3, 0x1
	stw r0, 0x28(r6)
	b L_at4
	L_at3:
	lhz r0, 0x0(r6)
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r6)
	L_at4:
	lis r3, evt_unitwin_disp_func@ha
	lfs f1, float_1000_8041dbe4(r0)
	addi r5, r3, evt_unitwin_disp_func@l
	li r4, 0x0
	li r3, 0x8
	bl dispEntry
	li r3, 0x0
	L_at2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 unk_80174e98(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stmw r26, 0x28(r1)
	li r30, 0x0
	lwz r31, 0x9c(r3)
	bl marioGetPtr
	mr r28, r3
	li r3, 0x0
	bl partyGetPtr
	lhz r4, 0x54(r31)
	mr r27, r3
	lwz r29, 0x1e4(r28)
	clrlwi. r0, r4, 31
	beq L_at1
	ori r0, r4, 0x2
	li r3, 0x2
	sth r0, 0x54(r31)
	b L_at2
	L_at1:
	lhz r0, 0x0(r31)
	li r3, 0x0
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r31)
	bl keyGetButtonTrg
	mr r28, r3
	bl marioChkCtrl
	cntlzw r0, r3
	srwi. r0, r0, 5
	bne L_at3
	bl marioChkKey
	cntlzw r0, r3
	srwi. r0, r0, 5
	beq L_at4
	L_at3:
	li r28, 0x0
	L_at4:
	cmplwi r27, 0x0
	beq L_at5
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 23, 23
	beq L_at5
	lwz r0, 0xe0(r31)
	cmpwi r0, -0x1
	beq L_at6
	li r0, -0x1
	stw r0, 0xe0(r31)
	lwz r3, 0x60(r31)
	bl winMgrClose
	lwz r3, 0x64(r31)
	bl winMgrClose
	L_at6:
	li r3, 0x0
	b L_at2
	L_at5:
	bl winGhostDiaryChk
	cmpwi r3, 0x0
	bne L_at7
	bl N_itemPickUpFromFieldCheck
	cmpwi r3, 0x0
	beq L_at8
	L_at7:
	lwz r0, 0xe0(r31)
	cmpwi r0, -0x1
	beq L_at9
	li r0, -0x1
	stw r0, 0xe0(r31)
	lwz r3, 0x60(r31)
	bl winMgrClose
	lwz r3, 0x64(r31)
	bl winMgrClose
	L_at9:
	li r3, 0x0
	b L_at2
	L_at8:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 30, 30
	bne L_at10
	cmplwi r29, 0x0
	beq L_at11
	li r26, 0x0
	li r27, 0x0
	b L_at12
	L_at13:
	mr r3, r29
	bl hitGetName
	lwz r5, 0x4(r31)
	addi r0, r27, 0x4
	mr r4, r3
	lwzx r3, r5, r0
	bl strcmp
	cmpwi r3, 0x0
	beq L_at14
	addi r27, r27, 0xc
	addi r26, r26, 0x1
	L_at12:
	lwz r0, 0x18(r31)
	cmpw r26, r0
	blt L_at13
	L_at14:
	slwi r0, r26, 1
	add r3, r31, r0
	lhz r0, 0xc(r3)
	clrlwi. r0, r0, 31
	bne L_at11
	lwz r0, 0x18(r31)
	cmpw r26, r0
	bge L_at11
	lwz r0, 0xe0(r31)
	cmpw r0, r26
	beq L_at15
	cmpwi r0, -0x1
	bne L_at16
	lwz r3, 0x60(r31)
	bl winMgrOpen
	lwz r3, 0x64(r31)
	bl winMgrOpen
	L_at16:
	stw r26, 0xe0(r31)
	stw r26, 0x24(r31)
	lwz r3, 0x64(r31)
	bl winMgrGetPtr
	bl winMgrHelpInit
	L_at15:
	li r30, 0x1
	L_at11:
	cmpwi r30, 0x0
	bne L_at17
	lwz r0, 0xe0(r31)
	cmpwi r0, -0x1
	beq L_at17
	li r0, -0x1
	stw r0, 0xe0(r31)
	lwz r3, 0x60(r31)
	bl winMgrClose
	lwz r3, 0x64(r31)
	bl winMgrClose
	L_at17:
	lwz r0, 0xe0(r31)
	cmpwi r0, -0x1
	beq L_at18
	lhz r3, 0x0(r31)
	rlwinm. r0, r28, 0, 23, 23
	ori r0, r3, 0x1
	sth r0, 0x0(r31)
	beq L_at18
	bl marioKeyOff
	lwz r0, 0x24(r31)
	li r4, 0x0
	lwz r3, 0x4(r31)
	li r5, 0x0
	mulli r0, r0, 0xc
	add r3, r3, r0
	lwz r3, 0x8(r3)
	bl evtEntry
	stw r3, 0x20(r31)
	lwz r3, 0x20(r31)
	stw r31, 0x9c(r3)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x2
	sth r0, 0x0(r31)
	lwz r3, 0x60(r31)
	bl winMgrClose
	lwz r3, 0x64(r31)
	bl winMgrClose
	li r3, -0x1
	li r0, 0x0
	stw r3, 0xe0(r31)
	stw r0, 0xe4(r31)
	b L_at18
	L_at10:
	lwz r3, 0x20(r31)
	lwz r3, 0x15c(r3)
	bl evtCheckID
	cmpwi r3, 0x0
	bne L_at18
	lhz r0, 0x0(r31)
	rlwinm r0, r0, 0, 31, 29
	sth r0, 0x0(r31)
	bl marioKeyOn
	lwz r0, 0xe4(r31)
	cmpwi r0, 0x0
	beq L_at18
	lwz r0, 0x24(r31)
	slwi r0, r0, 1
	add r3, r31, r0
	lhz r0, 0xc(r3)
	ori r0, r0, 0x1
	sth r0, 0xc(r3)
	L_at18:
	li r30, 0x0
	mr r29, r31
	mr r27, r30
	b L_at19
	L_at20:
	lwz r3, 0x4(r31)
	lwzx r3, r3, r27
	bl mapGetMapObj
	mr. r28, r3
	beq L_at21
	mr r5, r30
	addi r3, r1, 0x8
	la r4, str_8041DAC0(r0)
	crclr 6
	bl sprintf
	lhz r0, 0xc(r29)
	clrlwi. r0, r0, 31
	beq L_at22
	addi r3, r1, 0x8
	li r4, 0x2
	bl iconFlagOn
	b L_at21
	L_at22:
	lwz r0, 0x0(r28)
	clrlwi. r0, r0, 31
	beq L_at23
	addi r3, r1, 0x8
	li r4, 0x2
	bl iconFlagOn
	b L_at21
	L_at23:
	addi r3, r1, 0x8
	li r4, 0x2
	bl iconFlagOff
	L_at21:
	addi r27, r27, 0xc
	addi r29, r29, 0x2
	addi r30, r30, 0x1
	L_at19:
	lwz r0, 0x18(r31)
	cmpw r30, r0
	blt L_at20
	li r3, 0x0
	L_at2:
	lmw r26, 0x28(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 unk_801751f8(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r30
	bl evtGetValue
	stw r3, 0xe4(r31)
	li r3, 0x2
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 unk_8017524c(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	cmpwi r3, 0x0
	lwz r3, _wp(r0)
	beq L_at1
	lhz r0, 0x0(r3)
	ori r0, r0, 0x100
	sth r0, 0x0(r3)
	b L_at2
	L_at1:
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 24, 22
	sth r0, 0x0(r3)
	L_at2:
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 unitwincoin_wait(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r31, _wp(r0)
	bl pouchGetPtr
	bl pouchGetCoin
	lwz r5, 0x2c(r31)
	li r0, 0x2
	subf r4, r3, r5
	subf r3, r5, r3
	or r3, r4, r3
	srawi r3, r3, 31
	andc r3, r0, r3
	lwz r31, 0xc(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 unitwincoin_disp_onoff(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	mr r31, r3
	bl pouchGetPtr
	lwz r30, _wp(r0)
	bl pouchGetCoin
	stw r3, 0x2c(r30)
	li r0, 0x0
	cmpwi r31, 0x0
	stw r0, 0x5c(r30)
	beq L_at1
	lhz r0, 0x0(r30)
	ori r0, r0, 0x1000
	sth r0, 0x0(r30)
	b L_at2
	L_at1:
	lhz r0, 0x0(r30)
	rlwinm r0, r0, 0, 20, 18
	sth r0, 0x0(r30)
	L_at2:
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_unitwin_selltable_setup(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stmw r27, 0x3c(r1)
	mr r28, r3
	lwz r27, 0x18(r3)
	lwz r4, 0x0(r27)
	bl evtGetValue
	lwz r4, 0x4(r27)
	mr r27, r3
	mr r3, r28
	bl evtGetValue
	lwz r29, _wp(r0)
	li r31, 0x0
	li r28, 0x0
	stw r27, 0x4(r29)
	mr r27, r29
	mr r30, r31
	stw r3, 0x8(r29)
	stw r31, 0x18(r29)
	b L_at1
	L_at2:
	lwz r3, 0x18(r27)
	addi r4, r1, 0x8
	addi r0, r3, 0x1
	stw r0, 0x18(r27)
	lwz r3, 0x4(r27)
	lwzx r3, r3, r31
	bl mapObjGetPos
	lwz r3, 0x4(r27)
	li r4, 0x4000
	lwzx r3, r3, r31
	bl mapObjFlagOn
	lwz r3, 0x8(r27)
	lwzx r0, r3, r30
	cmpwi r0, 0x0
	beq L_at3
	mr r5, r28
	addi r3, r1, 0x14
	la r4, str_8041DAC0(r0)
	crclr 6
	bl sprintf
	lwz r4, 0x8(r27)
	lis r3, itemDataTable@ha
	addi r0, r3, itemDataTable@l
	addi r3, r1, 0x14
	lwzx r4, r4, r30
	mulli r4, r4, 0x28
	add r4, r0, r4
	lhz r4, 0x20(r4)
	bl iconEntry
	lfs f2, float_6_8041dbe8(r0)
	addi r3, r1, 0x14
	lfs f0, 0xc(r1)
	lfs f1, 0x8(r1)
	fadds f2, f2, f0
	lfs f3, 0x10(r1)
	bl iconSetPos
	addi r3, r1, 0x14
	li r4, 0x40
	bl iconFlagOn
	b L_at4
	L_at3:
	lhz r0, 0xc(r29)
	ori r0, r0, 0x1
	sth r0, 0xc(r29)
	L_at4:
	addi r31, r31, 0xc
	addi r30, r30, 0x4
	addi r29, r29, 0x2
	addi r28, r28, 0x1
	L_at1:
	lwz r3, 0x4(r27)
	lwzx r0, r3, r31
	cmplwi r0, 0x0
	bne L_at2
	la r3, select_evt(r0)
	li r4, 0x0
	li r5, 0x20
	li r6, 0x0
	bl evtEntryType
	stw r3, 0x1c(r27)
	lis r3, unk_80375478@ha
	addi r28, r3, unk_80375478@l
	mr r29, r27
	lwz r3, 0x1c(r27)
	li r30, 0x0
	stw r27, 0x9c(r3)
	L_at5:
	mr r3, r28
	bl winMgrEntry
	addi r30, r30, 0x1
	stw r3, 0x60(r29)
	cmpwi r30, 0x3
	addi r28, r28, 0x28
	addi r29, r29, 0x4
	blt L_at5
	li r0, -0x1
	li r3, 0x2
	stw r0, 0xe0(r27)
	lmw r27, 0x3c(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm s32 evt_unitwin_free(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stw r31, 0x3c(r1)
	stw r30, 0x38(r1)
	stw r29, 0x34(r1)
	lwz r3, _wp(r0)
	cmplwi r3, 0x0
	mr r29, r3
	bne L_at1
	li r3, 0x2
	b L_at2
	L_at1:
	cmpwi r4, 0x0
	beq L_at3
	lhz r0, 0x54(r3)
	ori r0, r0, 0x1
	sth r0, 0x54(r3)
	L_at3:
	lhz r0, 0x54(r29)
	rlwinm. r0, r0, 0, 30, 30
	bne L_at4
	li r3, 0x0
	b L_at2
	L_at4:
	li r30, 0x0
	li r31, 0x0
	b L_at5
	L_at6:
	lwz r3, 0x4(r29)
	li r4, 0x4000
	lwzx r3, r3, r31
	bl mapObjFlagOff
	mr r5, r30
	addi r3, r1, 0x8
	la r4, str_8041DAC0(r0)
	crclr 6
	bl sprintf
	addi r3, r1, 0x8
	bl iconDelete
	addi r31, r31, 0xc
	addi r30, r30, 0x1
	L_at5:
	lwz r0, 0x18(r29)
	cmpw r30, r0
	blt L_at6
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 24, 24
	beq L_at7
	li r30, 0x0
	mr r31, r29
	L_at8:
	lwz r3, 0x60(r31)
	bl winMgrDelete
	addi r30, r30, 0x1
	addi r31, r31, 0x4
	cmpwi r30, 0x3
	blt L_at8
	L_at7:
	lis r3, str_802F6894@ha
	addi r3, r3, str_802F6894@l
	bl iconDelete
	lwz r3, _wp(r0)
	bl _mapFree
	li r0, 0x0
	li r3, 0x2
	stw r0, _wp(r0)
	L_at2:
	lwz r0, 0x44(r1)
	lwz r31, 0x3c(r1)
	lwz r30, 0x38(r1)
	lwz r29, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 evt_unitwin_alloc(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	mr r30, r3
	li r3, 0xe8
	bl _mapAlloc
	mr r31, r3
	li r4, 0x0
	li r5, 0xe8
	bl memset
	li r0, 0x0
	cmpwi r30, 0x0
	stw r0, 0x50(r31)
	stw r31, _wp(r0)
	beq L_at1
	lhz r0, 0x0(r31)
	ori r0, r0, 0x80
	sth r0, 0x0(r31)
	b L_at2
	L_at1:
	lhz r0, 0x0(r31)
	rlwinm r0, r0, 0, 25, 23
	sth r0, 0x0(r31)
	L_at2:
	lis r3, str_802F6894@ha
	li r4, 0x1f0
	addi r3, r3, str_802F6894@l
	bl iconEntry2D
	lis r3, str_802F6894@ha
	li r4, 0x2
	addi r3, r3, str_802F6894@l
	bl iconFlagOn
	lis r3, str_802F6894@ha
	li r4, 0x4
	addi r3, r3, str_802F6894@l
	bl iconFlagOn
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 24, 24
	bne L_at3
	la r3, main_evt(r0)
	li r4, 0x0
	li r5, 0x0
	bl evtEntry
	stw r3, 0x1c(r31)
	lwz r3, 0x1c(r31)
	stw r31, 0x9c(r3)
	L_at3:
	bl pouchGetPtr
	addi r0, r3, 0x8e
	stw r0, mario_status_point_table(r0)
	bl pouchGetPtr
	addi r0, r3, 0x90
	la r3, mario_status_point_table(r0)
	stw r0, 0x4(r3)
	bl pouchGetPtr
	addi r0, r3, 0x94
	la r3, mario_status_point_table(r0)
	stw r0, 0x8(r3)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void unk_80175710(WinMgrEntry* entry) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	stw r0, 0x94(r1)
	stw r31, 0x8c(r1)
	stw r30, 0x88(r1)
	stw r29, 0x84(r1)
	mr r29, r3
	lwz r30, _wp(r0)
	bl pouchGetPtr
	lwz r0, 0x0(r29)
	mr r31, r3
	rlwinm. r0, r0, 0, 29, 29
	bne L_at1
	lwz r3, 0x18(r29)
	lis r4, 0x4330
	lwz r0, 0x1c(r29)
	lis r5, double_to_int_802f68a8@ha
	xoris r3, r3, 0x8000
	stw r4, 0x70(r1)
	xoris r0, r0, 0x8000
	lfd f2, double_to_int_802f68a8@l(r5)
	stw r3, 0x74(r1)
	addi r3, r1, 0x3c
	lfs f3, float_30_8041dbf0(r0)
	lfd f0, 0x70(r1)
	stw r0, 0x7c(r1)
	fsubs f0, f0, f2
	lfs f5, float_10_8041dbec(r0)
	stw r4, 0x78(r1)
	fadds f4, f3, f0
	lfd f1, 0x78(r1)
	lfs f0, float_36_8041db64(r0)
	fsubs f2, f1, f2
	lfs f3, float_0_8041db00(r0)
	fadds f1, f5, f4
	fsubs f2, f2, f0
	bl PSMTXTrans
	lwz r3, gp(r0)
	lwz r0, 0x16c(r3)
	cmplwi r0, 0x0
	bne L_at2
	lfs f1, float_1p1_8041db30(r0)
	addi r3, r1, 0xc
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0x3c
	addi r4, r1, 0xc
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x3c
	li r4, 0x10
	li r5, 0x1f1
	bl iconDispGx2
	b L_at3
	L_at2:
	lfs f2, float_1p1_8041db30(r0)
	addi r3, r1, 0xc
	lfs f1, float_0p8_8041db74(r0)
	fmr f3, f2
	bl PSMTXScale
	addi r3, r1, 0x3c
	addi r4, r1, 0xc
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x3c
	li r4, 0x10
	li r5, 0x20a
	bl iconDispGx2
	L_at3:
	lwz r3, 0x18(r29)
	lis r4, 0x4330
	lwz r0, 0x1c(r29)
	lis r5, double_to_int_802f68a8@ha
	xoris r3, r3, 0x8000
	stw r4, 0x78(r1)
	xoris r0, r0, 0x8000
	lfd f4, double_to_int_802f68a8@l(r5)
	stw r3, 0x7c(r1)
	addi r3, r1, 0x3c
	lfs f3, float_124_8041dbf4(r0)
	lfd f0, 0x78(r1)
	stw r0, 0x74(r1)
	fsubs f1, f0, f4
	lfs f0, float_38_8041dbf8(r0)
	stw r4, 0x70(r1)
	lfd f2, 0x70(r1)
	fadds f1, f3, f1
	lfs f3, float_0_8041db00(r0)
	fsubs f2, f2, f4
	fsubs f2, f2, f0
	bl PSMTXTrans
	lwz r0, dat_8041d9bc(r0)
	addi r3, r1, 0x3c
	addi r6, r1, 0x8
	li r5, 0x0
	stw r0, 0x8(r1)
	lwz r4, 0x30(r30)
	bl iconNumberDispGx
	lwz r4, 0x30(r30)
	lha r5, 0x5b0(r31)
	subf. r6, r4, r5
	beq L_at1
	lis r3, 0x6666
	addi r0, r3, 0x6667
	mulhw r0, r0, r6
	srawi r0, r0, 2
	srwi r3, r0, 31
	add. r6, r0, r3
	bne L_at4
	cmpw r5, r4
	li r0, -0x1
	ble L_at5
	li r0, 0x1
	L_at5:
	mr r6, r0
	L_at4:
	lwz r0, 0x30(r30)
	add r0, r0, r6
	stw r0, 0x30(r30)
	L_at1:
	lwz r0, 0x94(r1)
	lwz r31, 0x8c(r1)
	lwz r30, 0x88(r1)
	lwz r29, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm void unk_801758fc(WinMgrEntry* entry) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r4, _wp(r0)
	lwz r0, 0x24(r4)
	lwz r30, 0x8(r4)
	lwz r3, 0x64(r4)
	slwi r31, r0, 2
	bl winMgrAction
	cmpwi r3, 0x0
	bne L_at1
	lwzx r0, r30, r31
	lis r3, itemDataTable@ha
	addi r3, r3, itemDataTable@l
	mulli r0, r0, 0x28
	add r3, r3, r0
	lwz r3, 0x8(r3)
	bl msgSearch
	stw r3, 0x34(r29)
	mr r3, r29
	bl winMgrHelpDraw
	L_at1:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void unk_8017597c(WinMgrEntry* entry) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl winMgrHelpMain
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void unk_8017599c(WinMgrEntry* entry) {
	nofralloc
	stwu r1, -0xc0(r1)
	mflr r0
	lis r3, itemDataTable@ha
	stw r0, 0xc4(r1)
	addi r4, r3, itemDataTable@l
	stmw r27, 0xac(r1)
	lwz r5, _wp(r0)
	lwz r0, 0x24(r5)
	mr r28, r5
	lwz r3, 0x8(r5)
	slwi r0, r0, 2
	lwzx r0, r3, r0
	mulli r0, r0, 0x28
	add r3, r4, r0
	lwz r3, 0x4(r3)
	bl msgSearch
	mr r0, r3
	lwz r3, 0x60(r28)
	mr r27, r0
	bl winMgrAction
	cmpwi r3, 0x0
	bne L_at1
	bl FontDrawStart
	bl FontDrawEdge
	lwz r0, dat_8041d9b4(r0)
	addi r3, r1, 0xc
	stw r0, 0xc(r1)
	bl FontDrawColor
	mr r3, r27
	bl FontGetMessageWidth
	clrlwi r3, r3, 16
	lis r0, 0x4330
	neg r5, r3
	stw r0, 0x90(r1)
	srwi r4, r5, 31
	lis r3, double_to_int_802f68a8@ha
	add r0, r4, r5
	lfd f1, double_to_int_802f68a8@l(r3)
	srawi r0, r0, 1
	lfs f2, float_108_8041dadc(r0)
	xoris r0, r0, 0x8000
	mr r3, r27
	stw r0, 0x94(r1)
	lfd f0, 0x90(r1)
	fsubs f1, f0, f1
	bl FontDrawString
	bl FontDrawEdgeOff
	L_at1:
	li r30, 0x0
	mr r31, r28
	mr r29, r30
	li r27, 0x0
	b L_at2
	L_at3:
	lhz r0, 0xc(r31)
	clrlwi. r0, r0, 31
	bne L_at4
	lwz r3, 0x4(r28)
	addi r4, r1, 0x10
	lwzx r3, r3, r30
	bl mapObjGetPos
	lfs f1, 0x14(r1)
	li r3, 0x4
	lfs f0, float_30_8041dbf0(r0)
	fadds f0, f1, f0
	stfs f0, 0x14(r1)
	bl camGetPtr
	addi r4, r1, 0x10
	addi r3, r3, 0x11c
	mr r5, r4
	bl PSMTXMultVec
	li r3, 0x4
	bl camGetPtr
	addi r4, r1, 0x10
	addi r3, r3, 0x15c
	mr r5, r4
	bl PSMTX44MultVec
	lwz r7, gp(r0)
	lis r5, 0x4330
	lis r4, double_to_int_mask_802f68b8@ha
	lis r3, itemDataTable@ha
	lhz r6, 0x170(r7)
	addi r0, r3, itemDataTable@l
	lfd f3, double_to_int_mask_802f68b8@l(r4)
	addi r3, r1, 0x1c
	stw r5, 0x90(r1)
	la r4, str_8041DBAC(r0)
	lfs f2, float_0p5_8041db60(r0)
	stw r6, 0x94(r1)
	lfs f4, 0x10(r1)
	lfd f0, 0x90(r1)
	stw r5, 0x98(r1)
	fsubs f0, f0, f3
	lfs f1, 0x14(r1)
	fmuls f0, f0, f2
	fmuls f0, f4, f0
	stfs f0, 0x10(r1)
	lhz r5, 0x172(r7)
	stw r5, 0x9c(r1)
	lfd f0, 0x98(r1)
	fsubs f0, f0, f3
	fmuls f0, f0, f2
	fmuls f0, f1, f0
	stfs f0, 0x14(r1)
	lwz r5, 0x8(r28)
	lwzx r5, r5, r29
	mulli r5, r5, 0x28
	add r5, r0, r5
	lhz r5, 0x16(r5)
	crclr 6
	bl sprintf
	addi r3, r1, 0x1c
	bl strlen
	subi r4, r3, 0x1
	lis r0, 0x4330
	lis r3, double_to_int_mask_802f68b8@ha
	stw r4, 0xa4(r1)
	addi r4, r3, double_to_int_mask_802f68b8@l
	lfs f1, float_12_8041dbfc(r0)
	stw r0, 0xa0(r1)
	addi r3, r1, 0x5c
	lfd f3, 0x0(r4)
	lfd f2, 0xa0(r1)
	lfs f0, 0x10(r1)
	fsubs f4, f2, f3
	lfs f2, 0x14(r1)
	lfs f3, 0x18(r1)
	fmadds f1, f1, f4, f0
	bl PSMTXTrans
	lwz r4, dat_8041d9b8(r0)
	lis r3, itemDataTable@ha
	addi r0, r3, itemDataTable@l
	addi r3, r1, 0x5c
	stw r4, 0x8(r1)
	addi r6, r1, 0x8
	li r5, 0x0
	lwz r4, 0x8(r28)
	lwzx r4, r4, r29
	mulli r4, r4, 0x28
	add r4, r0, r4
	lhz r4, 0x16(r4)
	bl iconNumberDispGx
	L_at4:
	addi r31, r31, 0x2
	addi r30, r30, 0xc
	addi r29, r29, 0x4
	addi r27, r27, 0x1
	L_at2:
	lwz r0, 0x18(r28)
	cmpw r27, r0
	blt L_at3
	lmw r27, 0xac(r1)
	lwz r0, 0xc4(r1)
	mtlr r0
	addi r1, r1, 0xc0
	blr
}
// clang-format on
#endif
#pragma force_active on
#pragma explicit_zero_data on
__declspec(section ".data") u32 gap_05_80375604_data[1] = {0};
#pragma explicit_zero_data reset
