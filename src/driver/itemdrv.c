#include "driver/itemdrv.h"
#include "driver/swdrv.h"
#define iconEntry iconEntry_hidden
#define iconChange iconChange_hidden
#include "driver/icondrv.h"
#undef iconEntry
#undef iconChange
#include "driver/windowdrv.h"
#include "manager/evtmgr.h"
#include "driver/camdrv.h"
#include "driver/mobjdrv.h"
#include "eff/eff_stardust.h"
#include "pmario_sound.h"
#include "driver/effdrv.h"
#include "driver/hitdrv.h"
#include "driver/msgdrv.h"
#include "driver/seqdrv.h"
#include "data/item_data.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr_cmd.h"
#include "manager/fontmgr.h"
#include "manager/winmgr.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "party.h"
#include "party/party_vivian.h"
#include "memory.h"
#include "system.h"
#include <string.h>


#ifdef NONMATCHING
inline Vec unknownVec0(void) {
    return (Vec){ 0.0f, 0.0f, 0.0f };
}

inline Vec makeVecByValue2(f32 x, f32 y, f32 z) {
    Vec v = (Vec){ 0.0f, 0.0f, 0.0f };
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

inline Vec makeVecByValue(f32 x, f32 y, f32 z) {
    Vec v = (Vec){ 0.0f, 0.0f, 0.0f };
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}
#endif

extern int __float_nan[];
static inline s32 item_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 item_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (item_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }

extern GlobalWork* gp;
extern int sprintf(char* str, const char* format, ...);
extern ItemData itemDataTable[];
void iconEntry(const char* name, u16 iconId);
void iconChange(const char* name, u16 iconId);
BOOL marioChkItemGetMotion(void);
void marioChgGetItemMotion(void);
void marioChgStayMotion(void);
void marioSetCamId(s32 camId);
EffectEntry* effItemGetEntry(s32 type, f32 x, f32 y, f32 z);
u32 psndBGMChkSilent(s32 a1);
BOOL psndBGMChk(s32 a1);
BOOL psndBGMOff(u32 flags);
s32 msgWindow_Entry(const char* msg, s32 a2, s32 a3);
extern s32 all_juyoitem_lecture[];
BOOL nokonoko_holdItem(void);
BOOL N_fbatPreventMarioEventChk(void);
s32 marioGetJabaraState(void);
EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
EffectEntry* effSplashEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
MapObjectEntry* mobjHitObjPtrToPtr(HitEntry* hit);
double sin(double);
double cos(double);
EffectEntry* effHagetakaFlushN64Entry(s32 a1, s32 a2, f32 x, f32 y, f32 z, f32 scale);

BOOL itemGetNokoCheck(ItemEntry* entry);
void winNameDisp(WinMgrEntry* win);
void winNameDisp2(WinMgrEntry* win);
void winHelpMain(WinMgrEntry* win);
void winHelpDisp(WinMgrEntry* win);
void winFullDisp(WinMgrEntry* win);
BOOL N_itemPickUpFromFieldCheck(void);

ItemEntry* itemHitCheck(f32 x, f32 y, f32 z, f32 range);
HitEntry* itemHitCheckY(ItemEntry* entry, f32 z, f32 y, f32 x, f32 vy);
HitEntry* itemHitCheckUp(ItemEntry* entry, f32 vy);


HitEntry* itemHitCheckSide(ItemEntry* entry, f32* outX, f32 dx, f32* outZ, f32 dz, s32* angle);
void itemseq_GetItem(ItemEntry* entry);
void itemDelete(const char* name);
void itemModeChange(ItemEntry* entry, s32 mode);
ItemEntry* itemEntry(const char* name, s32 itemId, s32 type, s32 evtId, s32 a5, f32 x, f32 y, f32 z);

//.bss
static ItemWork work[2];



//.data
WinMgrDesc itemdrv_window_desc[4] = {
	{0, 0, 8, -175, 120, 350, 42, {0xE1, 0xD7, 0x9B, 0xFF}, NULL, winNameDisp},
	{0, 0, 8, -240, -130, 500, 80, {0xF0, 0xF0, 0xF0, 0xFF}, winHelpMain, winHelpDisp},
	{0, 0, 8, -175, 200, 350, 75, {0x2B, 0xA4, 0xFF, 0xFF}, NULL, winFullDisp},
	{0, 0, 8, -175, 120, 350, 42, {0xE1, 0xD7, 0x9B, 0xFF}, NULL, winNameDisp2},
};

//TODO: inline function? I see nothing in the symbol map
#define itemGetWork() (gp->inBattle ? &work[1] : &work[0])

inline void itemCheckBadge(ItemEntry* entry) {
    if (!gp->inBattle) {
        if (BADGE_MIN <= entry->itemId && entry->itemId < BADGE_MAX) {
            if (entry->flags & 0x100) {
                pouchArriveBadge(entry->itemId);
            }
        }
    }
}

void itemseq_Bound(ItemEntry* entry);
static inline BOOL itemGetPouch(ItemEntry* entry) {
	EventEntry* evt;

	if (!pouchGetItem(entry->itemId)) {
		return FALSE;
	}
	if (entry->flags & 0x20) {
		swSet(entry->evtId);
	}
	else if (entry->flags & 0x40) {
		_swSet(entry->evtId);
	}
	if ((u32)entry->evtCode != 0) {
		evt = evtEntry((void*)entry->evtCode, 0, 0x20);
		evt->lwData[0] = FLOAT(entry->position.x);
		evt->lwData[1] = FLOAT(entry->position.y);
		evt->lwData[2] = FLOAT(entry->position.z);
	}
	entry->flags2 |= 1;
	return TRUE;
}

static inline void itemGetEnd(ItemEntry* entry) {
	marioStSystemLevel(0);
	psndClearFlag(0x80);
	if (entry->flags2 & 0x1000000) {
		entry->flags2 &= ~0x1000000;
		marioCtrlOn();
	}
	marioKeyOn();
	marioChgStayMotion();
	camGetPtr(8)->flags &= ~0x200;
}

void itemGetSound(ItemEntry* entry);

#ifdef NONMATCHING
void itemInit(void) { // 1:1
    ItemWork* wp;

    wp = &work[0];
    wp->count = 32;
    wp->entries = __memAlloc(HEAP_DEFAULT, sizeof(ItemEntry) * wp->count);
    memset(wp->entries, 0, sizeof(ItemEntry) * wp->count);
    wp->currId = 0;

    wp = &work[1];
    wp->count = 32;
    wp->entries = __memAlloc(HEAP_DEFAULT, sizeof(ItemEntry) * wp->count);
    memset(wp->entries, 0, sizeof(ItemEntry) * wp->count);
    wp->currId = 0;
}
#endif

#ifdef NONMATCHING
void itemReInit(void) {
    ItemWork* wp = itemGetWork();
    ItemEntry* entry;
    int i;

    if (!gp->inBattle) {
        for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
            if (entry->flags & 1) { //flush all current badges
                itemCheckBadge(entry);
            }
        }
    }

    //clear all existing entries
    for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
        iconDelete(entry->name);
        entry->flags &= ~1;
        memset(entry->name, 0, sizeof(entry->name));
    }
}
#endif

#ifdef NONMATCHING
void itemCoinDrop(Vec* position) {
	ItemEntry* entry;

	if (pouchGetCoin() > 0) {
		pouchAddCoin(-1);
		entry = itemEntry(NULL, 0x79, 8, -1, 0, position->x, position->y, position->z);
		if (entry) {
			entry->flags2 |= 0x40;
		}
	}
}
#endif

#ifdef NONMATCHING
BOOL itemGetCheck(ItemEntry* entry) {
	MarioWork* mario = marioGetPtr();

	if (!entry) return FALSE;
	if (entry->flags2 & 0x100000) return FALSE;
	if (mario->characterId == 2) {
		if (!(*(s32*)mario->field_0x14 & 1)) {
			if (marioStGetSystemLevel() != 0U) return FALSE;
			if (mario->flags & 0xA) return FALSE;
		}
	}
	else {
		if (marioStGetSystemLevel() != 0U) return FALSE;
		if (mario->flags & 0xA) return FALSE;
	}
	if (*(s32*)&gp->mapEventId) return FALSE;
	if (seqGetSeq() != 2) return FALSE;
	if (mario->currMotionId == 0x19) return FALSE;
	if (mario->currMotionId == 0x18) return FALSE;
	if (vivianGetStatus()) return FALSE;
	if (mario->currMotionId == 0x1F || mario->currMotionId == 0x20) return FALSE;
	if (nokonoko_holdItem()) return FALSE;
	{
		ItemWork* wp = itemGetWork();
		ItemEntry* item;
		int i;
		for (item = wp->entries, i = 0; i < wp->count; i++, item++) {
			if (item->flags & 1 && item->mode == 2) {
				return FALSE;
			}
		}
	}
	if (N_fbatPreventMarioEventChk()) return FALSE;
	switch (entry->mode) {
		case 5:
		case 6:
			if (!entry->subState) break;
			if (entry->flags2 & 4) break;
			if (entry->flags2 & 8) break;
			return TRUE;
		case 3:
		case 4:
			if (entry->flags2 & 8) break;
			return TRUE;
		case 1:
		case 7:
			return TRUE;
	}
	return FALSE;
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
BOOL itemGetNokoCheck(ItemEntry* entry) {
	MarioWork* mario = marioGetPtr();

	if (!entry) return FALSE;
	if (entry->flags2 & 0x100000) return FALSE;
	if (marioStGetSystemLevel() != 0U) return FALSE;
	if (mario->flags & 0xA) return FALSE;
	if (entry->flags2 & 0x2000000) return FALSE;
	if (*(s32*)&gp->mapEventId) return FALSE;
	if (seqGetSeq() != 2) return FALSE;
	if (mario->currMotionId == 0x19) return FALSE;
	if (vivianGetStatus()) return FALSE;
	if (mario->currMotionId == 0x1F || mario->currMotionId == 0x20) return FALSE;
	if ((u16)(mario->currMotionId - 5) <= 3 || mario->currMotionId == 0xF || mario->currMotionId == 0xE) return FALSE;
	{
		ItemWork* wp = itemGetWork();
		ItemEntry* item;
		int i;
		for (item = wp->entries, i = 0; i < wp->count; i++, item++) {
			if (item->flags & 1 && item->mode == 2) {
				return FALSE;
			}
		}
	}
	return !N_fbatPreventMarioEventChk();
}
#endif
#pragma dont_inline reset

#ifdef NONMATCHING
BOOL N_itemPickUpFromFieldCheck(void) {
	ItemWork* wp = itemGetWork();
	ItemEntry* entry;
	int i;

	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (entry->flags & 1 && entry->mode == 2) {
			return TRUE;
		}
	}
	return FALSE;
}
#endif

typedef struct ItemEffPos {
	u8 pad[8];
	Vec position;
} ItemEffPos;


#ifdef NONMATCHING
void itemMain(void) {
	ItemWork* wp = itemGetWork();
	MarioWork* mario;
	ItemEntry* entry;
	PartyEntry* party;
	HitEntry* hit;
	BOOL active;
	u16 mode;
	int i;
	f32 newY;
	f32 y;
	s32 dx, dy;

	mario = marioGetPtr();
	entry = itemHitCheck(mario->position.x, mario->position.y, mario->position.z, mario->wPlayerCollisionBox.x * 0.5f + 12.0f);
	if (itemGetCheck(entry)) {
		itemModeChange(entry, 2);
	}

	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (!(entry->flags & 1)) continue;
		mode = entry->mode;
		active = TRUE;
		switch (mode) {
			case 2:
			case 7:
			case 8:
			case 10:
				break;
			default:
				if (gp->systemLevelFlags & 0xF) {
					active = FALSE;
				}
				break;
		}
		if (!active) {
			entry->baseTime = gp->renderTime;
			continue;
		}
		if (mode != 2) {
			if (entry->timer == 0) {
				entry->flags2 &= ~0x100;
			}
			else if (entry->flags2 & 0x4000) {
				entry->flags2 &= ~0x100;
			}
			else {
				entry->timer -= (f32)OSTicksToMicroseconds(gp->renderTime - entry->baseTime) / 1000.0f;
				if (entry->timer <= 0) {
					itemModeChange(entry, 9);
				}
				else if (entry->timer <= 3000) {
					if ((entry->timer >> 4) & 1) {
						entry->flags2 ^= 0x100;
					}
				}
			}
		}
		else {
			entry->flags2 &= ~0x100;
		}

		switch (entry->mode) {
			case 5:
			case 6:
			case 10:
				itemseq_Bound(entry);
				break;
			case 3:
			case 4:
				itemseq_Bound(entry);
				break;
			case 1:
				y = entry->position.y; { f32 dirY = -1.0f;
				if (entry->flags2 & 0x100000) {
					hit = NULL;
					newY = y + dirY;
				}
				else {
					f32 hitNZ, hitNY, hitNX, hitDist, hitZ, hitY, hitX;
					f32 px = entry->position.x, py = entry->position.y + 20.0f, pz = entry->position.z;
					{ f64 d = __fabs(-1.0); hitDist = 20.0 + d; }
					hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, px, py, pz, 0.0f, -1.0f, 0.0f);
					if (hit) {
						newY = hitY;
					}
					else {
						hit = NULL;
						newY = y + dirY;
					}
				} }
				if (!hit) {
					itemModeChange(entry, 3);
				}
				else {
					entry->position.y = newY;
				}
				break;
			case 2:
				itemseq_GetItem(entry);
				break;
			case 8:
				party = partyGetPtr(marioGetPartyId());
				if (party) {
					f32 px = party->position.x, py = 15.0f + party->position.y, pz = party->position.z;
					entry->position.x = px;
					entry->position.y = py;
					entry->position.z = pz;
				}
				else {
					itemModeChange(entry, 3);
					entry->flags2 &= ~0x1000;
				}
				break;
			case 9:
				itemDelete(entry->name);
				break;
		}

		if (entry->flags & 1) {
			switch (entry->itemId) {
				case 0x72: case 0x73: case 0x74: case 0x75: case 0x76: case 0x77: case 0x78:
					if (!(entry->flags2 & 0x100)) {
						((ItemEffPos*)entry->effect->userdata)->position.x = entry->position.x;
						((ItemEffPos*)entry->effect->userdata)->position.y = 16.0f + entry->position.y;
						((ItemEffPos*)entry->effect->userdata)->position.z = entry->position.z;
					}
					else {
						((ItemEffPos*)entry->effect->userdata)->position.x = entry->position.x;
						((ItemEffPos*)entry->effect->userdata)->position.y = -1000.0f;
						((ItemEffPos*)entry->effect->userdata)->position.z = entry->position.z;
					}
					break;
				default:
					if (!(entry->flags2 & 0x100)) {
						iconSetPos(entry->name, entry->position.x, entry->position.y, entry->position.z);
						iconSetScale(entry->name, entry->scale);
						iconSetAlpha(entry->name, entry->alpha);
					}
					else {
						iconSetPos(entry->name, entry->position.x, -1000.0f, entry->position.z);
					}
					break;
			}
			entry->baseTime = gp->renderTime;
			if (entry->itemId == 0x79 || entry->itemId == 0x7A) {
				if (irand(1000) < 30) {
					dx = 10 - irand(20);
					dy = irand(20) + 10;
					effHagetakaFlushN64Entry(0, 10, entry->position.x + dx, entry->position.y + dy, entry->position.z, 1.0f);
				}
			}
		}
	}

	wp = gp->inBattle ? &work[0] : &work[1];
	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (entry->flags & 1) {
			entry->baseTime = gp->renderTime;
		}
	}
}
#endif

#ifdef NONMATCHING
void itemModeChange(ItemEntry* entry, s32 mode) {
	entry->mode = mode;
	entry->subState = 0;
}
#endif

#ifdef NONMATCHING
ItemEntry* itemEntry(const char* name, s32 itemId, s32 type, s32 evtId, s32 a5, f32 x, f32 y, f32 z) {
	ItemWork* wp = itemGetWork();
	int i;
	ItemEntry* entry;
	BOOL isGswf, isLswf;
	char itemName[8];

	isGswf = FALSE;
	isLswf = FALSE;
	if (evtId != -1) {
		if (evtId >= GSWF(0) && evtId <= EVTDAT_GSWF_MAX) {
			evtId += EVTDAT_GSWF_BASE;
			isGswf = TRUE;
			if (swGet(evtId)) {
				return NULL;
			}
		}
		else if (evtId >= LSWF(0) && evtId <= EVTDAT_LSWF_MAX) {
			evtId += EVTDAT_LSWF_BASE;
			isLswf = TRUE;
			if (_swGet(evtId)) {
				return NULL;
			}
		}
	}

	if (name == NULL) {
		wp->currId++;
		if (wp->currId >= 0xFFFFF) {
			wp->currId = 1;
		}
		sprintf(itemName, "_i%05x", wp->currId);
		name = itemName;
	}

	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (entry->flags & 1 && !strcmp(entry->name, name)) {
			break;
		}
	}

	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (!(entry->flags & 1)) {
			break;
		}
	}

	if (i >= wp->count) {
		entry = wp->entries;
		if (entry->flags & 1 && entry->itemId == 0x79 && entry->flags & 0x400) {
			itemDelete(entry->name);
		}
		else {
			entry = wp->entries;
			if (entry->flags & 1 && entry->itemId == 0x7C && entry->flags & 0x400) {
				itemDelete(entry->name);
			}
			else {
				entry = wp->entries;
				if (entry->flags & 1 && entry->itemId == 0x7B && entry->flags & 0x400) {
					itemDelete(entry->name);
				}
				else {
					entry = NULL;
				}
			}
		}
		if (entry == NULL) {
			return NULL;
		}
	}

	memset(entry, 0, sizeof(ItemEntry));
	strcpy(entry->name, name);
	entry->position.x = x;
	entry->position.y = y;
	entry->position.z = z;
	entry->itemId = itemId;
	entry->type = type;
	entry->evtCode = a5;
	entry->flags |= 1;
	entry->scale = 1.0f;
	entry->alpha = 0xFF;
	if (evtId != -1) {
		if (isGswf) {
			entry->evtId = evtId;
			entry->flags |= 0x20;
		}
		else if (isLswf) {
			entry->evtId = evtId;
			entry->flags |= 0x40;
		}
	}
	else {
		entry->evtId = -1;
	}

	switch (entry->itemId) {
	case 0x72: case 0x73: case 0x74: case 0x75: case 0x76: case 0x77: case 0x78:
		entry->effect = effStarStoneEntry(entry->itemId - 0x72, x, 16.0f + y, z, 1.0f);
		break;
	default:
		entry->effect = NULL;
		iconEntry(entry->name, itemDataTable[itemId].icon_id);
		{ char* nm = ((ItemEntry*)entry)->name; iconSetPos(nm, x, y, z); }
		iconSetScale(entry->name, entry->scale);
		iconSetAlpha(entry->name, entry->alpha);
		break;
	}
	entry->bounceFactor = entry->gravityScale = 1.0f;
	entry->baseTime = gp->renderTime;
	switch (entry->itemId) {
	case 0x79: case 0x7A: case 0x7B: case 0x7C:
		entry->flags |= 4;
		break;
	}

	switch ((u16)type) {
		case 17:
			entry->flags |= 2;
		case 16:
			itemModeChange(entry, 7);
			break;
		case 0:
			itemModeChange(entry, 1);
			break;
		case 1:
			itemModeChange(entry, 1);
			entry->flags |= 2;
			break;
		case 4:
			itemModeChange(entry, 6);
			break;
		case 3:
			entry->timer = 5000;
			itemModeChange(entry, 5);
			break;
		case 11:
			entry->flags2 |= 0x4000;
			entry->timer = 20000;
			itemModeChange(entry, 6);
			break;
		case 12:
			entry->flags2 |= 0x4000;
			entry->timer = 20000;
			itemModeChange(entry, 6);
			entry->flags |= 0x400;
			break;
		case 9:
			entry->flags |= 0x100;
		case 8:
			entry->flags2 |= 0x4000;
			entry->timer = 8000;
			itemModeChange(entry, 6);
			break;
		case 10:
			entry->flags2 |= 0x4000;
			entry->timer = 8000;
			itemModeChange(entry, 6);
			entry->flags |= 0x400;
			break;
		case 7:
			entry->flags2 |= 0x4000;
		case 5:
			entry->timer = 5000;
			itemModeChange(entry, 6);
			break;
		case 6:
			entry->timer = 5000;
			entry->flags2 |= 0x40;
			itemModeChange(entry, 6);
			break;
		case 2:
			itemModeChange(entry, 5);
			break;
		case 13:
			itemModeChange(entry, 3);
			break;
		case 14:
			itemModeChange(entry, 4);
			break;
		case 15:
			itemModeChange(entry, 10);
			break;
	}
	return entry;
}
#endif

#ifdef NONMATCHING
void itemDelete(const char* name) {
	ItemWork* wp = itemGetWork();
	ItemEntry* entry;
	int i;

	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (!strcmp(entry->name, name)) {
			itemCheckBadge(entry);
			switch (entry->itemId) {
				case 0x72: case 0x73: case 0x74: case 0x75: case 0x76: case 0x77: case 0x78:
					effSoftDelete(entry->effect);
					break;
				default:
					iconDelete(entry->name);
					break;
			}
			entry->flags &= ~1;
		}
	}
}
#endif

#ifdef NONMATCHING
ItemEntry* itemNameToPtr(char* name) {
	ItemWork* wp = itemGetWork();
	ItemEntry* entry;
	int i;

	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (!strcmp(entry->name, name)) {
			return entry;
		}
	}
	return NULL;
}
#endif

#ifdef NONMATCHING
ItemEntry* itemHitCheck(f32 x, f32 y, f32 z, f32 range) {
	ItemWork* wp = itemGetWork();
	ItemEntry* entry;
	int i;
	MarioWork* mario;
	ItemEntry* found;
	f32 dx, dy, dz, xzdist, dist;
	f32 hitX, hitY, hitZ, hitDist, hitNX, hitNY, hitNZ;
	HitEntry* hit;

	mario = marioGetPtr();
	found = NULL;
	for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
		if (!(entry->flags & 1)) continue;
			if (entry->flags & 2) { do { } while (0); continue; }
		if (entry->flags2 & 0x1000) continue;
		if (entry->mode == 2) continue;
		dx = x - entry->position.x; dy = y - entry->position.y;
		dz = z - entry->position.z;
		xzdist = item_sqrtf(dx * dx + dz * dz);
		dist = item_sqrtf(dx * dx + dy * dy + dz * dz);
		if (xzdist < range && marioItemGetOk() && marioGetJabaraState() != 1 &&
			marioGetJabaraState() != 4 && marioGetJabaraState() != 5)
		{
			if (__fabs((y + mario->wPlayerCollisionBox.y * 0.5f) - entry->position.y) < mario->wPlayerCollisionBox.y * 0.5f + 10.0f) {
				hit = NULL;
				if (y < entry->position.y) {
					hitDist = 10.0f + (entry->position.y - y);
					if (hitDist > 0.0f) {
						hit = hitCheckAttr(0x80000000, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, 0.0f, 1.0f, 0.0f);
					}
				}
				if (!hit) {
					found = entry;
					range = dist;
				}
			}
		}
	}
	return found;
}
#endif

#ifdef NONMATCHING
ItemEntry* itemNearDistCheck(f32 x, f32 y, f32 z, f32 range) {
	MarioWork* mario = marioGetPtr();
	ItemWork* wp = itemGetWork();
	ItemEntry* entry;
	ItemEntry* found;
	int i;
	Vec itemPos, diff, pos;
	f32 dist;

	entry = wp->entries;
	found = NULL;
	i = 0;
	pos = makeVecByValue2(x, y, z);
	for (; i < wp->count; i++, entry++) {
		if (!(entry->flags & 1)) continue;
		if (entry->flags2 & 0x1000) continue;
		if (entry->flags2 & 0x100000) continue;
		if (entry->mode == 2) continue;
		if (entry->flags2 & 0x2000000) continue;
		{ f32 iz, iy, ix; ix = entry->position.x; iy = entry->position.y; iz = entry->position.z; itemPos = makeVecByValue(ix, iy, iz); }
		PSVECSubtract(&itemPos, &pos, &diff);
		dist = PSVECMag(&diff);
		if (dist < range) {
			found = entry;
			range = dist;
		}
	}
	return found;
}
#endif

#ifdef NONMATCHING
void winNameDisp(WinMgrEntry* win) {
	ItemEntry* entry = win->param;
	const char* name;
	u16 width;
	char buffer[1024];

	name = msgSearch(itemDataTable[entry->itemId].name);
	if (entry->itemId >= 0xF0 && entry->itemId < 0x153) {
		sprintf(buffer, msgSearch("msg_window_badge_get"), name);
	}
	else {
		sprintf(buffer, msgSearch("msg_window_item_get"), name);
	}
	width = FontGetMessageWidth(buffer);
	if (width + 20 > win->width) {
		win->width = width + 20;
		win->x = -win->width / 2;
	}
	if (!winMgrAction(entry->winId[0])) {
		FontDrawStart();
		FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
		FontDrawMessage(-width / 2, win->y - 8, buffer);
	}
}
#endif

#ifdef NONMATCHING
void winNameDisp2(WinMgrEntry* win) {
	ItemEntry* entry = win->param;
	const char* name;
	u16 width;
	char buffer[1024];

	name = msgSearch(itemDataTable[entry->itemId].name);
	sprintf(buffer, msgSearch("msg_window_item_release"), name);
	width = FontGetMessageWidth(buffer);
	if (width + 20 > win->width) {
		win->width = width + 20;
		win->x = -win->width / 2;
	}
	if (!winMgrAction(entry->winId[0])) {
		FontDrawStart();
		FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
		FontDrawMessage(-width / 2, win->y - 8, buffer);
	}
}
#endif

#ifdef NONMATCHING
void winHelpMain(WinMgrEntry* win) {
	winMgrHelpMain(win);
}
#endif

#ifdef NONMATCHING
void winHelpDisp(WinMgrEntry* win) {
	ItemEntry* entry = win->param;

	if (!winMgrAction(entry->winId[1])) {
		win->msg = msgSearch(itemDataTable[entry->itemId].description);
		winMgrHelpDraw(win);
	}
}
#endif

#ifdef NONMATCHING
void winFullDisp(WinMgrEntry* win) {
	ItemEntry* entry = win->param;
	BOOL isBadge = FALSE;
	u16 width;
	const char* msg;


	if (entry->itemId >= 0xF0 && entry->itemId < 0x153) {
		isBadge = TRUE;
	}
	msg = isBadge ? msgSearch("msg_window_badge_full") : msgSearch("msg_window_item_full");
	width = FontGetMessageWidth(msg);
	if (width + 20 > win->width) {
		win->width = width + 20;
		win->x = -win->width / 2;
	}
	if (!winMgrAction(entry->winId[2])) {
		FontDrawStart();
		FontDrawEdge();
		FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
		FontDrawMessage(-width / 2, win->y - 10, msg);
		FontDrawEdgeOff();
	}
}
#endif


#ifdef NONMATCHING
void itemseq_GetItem(ItemEntry* entry) {
	ItemWork* wp = itemGetWork();
	MarioWork* mario;
	s32 type, bgm;
	s32 select;

	mario = marioGetPtr();
	switch (entry->subState) {
		case 0:
			entry->flags2 &= ~0x10000;
			if (entry->flags & 0x100) {
				entry->flags2 |= 0x4000000;
			}
			else {
				entry->flags2 &= ~0x4000000;
			}
			entry->flags &= ~0x100;
			if (entry->flags & 4) {
				if (itemGetPouch(entry)) {
					entry->timer = 0;
					itemGetSound(entry);
					itemDelete(entry->name);
				}
				else {
					itemModeChange(entry, 4);
				}
				break;
			}
			entry->subState = 1;
			entry->timer = 0;
			camGetPtr(8)->flags |= 0x200;
			marioKeyOff();
			marioStSystemLevel(2);
			psndSetFlag(0x80);
			mario->unk174.x = 0.0f;
			mario->unk174.z = 0.0f;
			mario->baseSpeed = 0.0f;
			*(f32*)mario->unk18C = 0.0f;
			if (entry->itemId == 7 || entry->itemId == 8 || entry->itemId == 10 || entry->itemId == 11) {
				entry->flags2 |= 0x2000;
			}
		case 1:
			if (!(entry->flags & 0x1000) || entry->flags & 0x4000) {
				if (!marioChkItemGetMotion()) {
					if (mario->currMotionId == 5 || (u16)(mario->currMotionId - 6) <= 2 ||
						mario->currMotionId == 0xF || mario->currMotionId == 0xE)
					{
						entry->subState = 8;
					}
					break;
				}
			}
			entry->subState = 2;
			marioChgGetItemMotion();
			{
				f32 y = 50.0f + mario->position.y, z = mario->position.z;
				entry->position.x = mario->position.x;
				entry->position.y = y;
				entry->position.z = z;
			}
			type = 7;
			bgm = -1;
			if (entry->itemId == 0x57) {
				type = 4;
				bgm = -1;
			}
			else if (entry->itemId == 0x7D) {
				type = 8;
				bgm = 0;
			}
			else if (entry->itemId < 0xC) {
				type = 3;
				bgm = 3;
			}
			else if (entry->itemId < 0x72) {
				type = 6;
				bgm = 1;
			}
			else if (entry->itemId < 0x79) {
				type = 0;
				bgm = -1;
			}
			else if (entry->itemId < 0xEC) {
				type = 7;
				bgm = -1;
			}
			else if (entry->itemId < 0x153) {
				type = 5;
				bgm = 2;
			}
			wp->effect = effItemGetEntry(type, mario->position.x, 62.0f + mario->position.y, mario->position.z);
			if (entry->flags2 & 0x2000) {
				((s32*)wp->effect->userdata)[14] = 5;
				iconFlagOn(entry->name, 0x200);
				marioSetCamId(7);
			}
			else {
				((s32*)wp->effect->userdata)[14] = 5;
				iconFlagOn(entry->name, 0x100);
				if (type == 0 || type == 3) {
					marioSetCamId(5);
				}
			}
			if (!(entry->flags & 0x8000)) {
				if (psndBGMChkSilent(0)) {
					entry->flags |= 8;
				}
				switch (bgm) {
					case 0:
						if (!(entry->flags & 8)) {
							psndBGMOff(0x3800);
						}
						psndBGMOn(0x211, "BGM_FF_GET_STARPIECE1");
						break;
					case 1:
						if (!(entry->flags & 8)) {
							psndBGMOff(0x3800);
						}
						psndBGMOn(0x211, "BGM_FF_GET_KEYITEM1");
						break;
					case 2:
						if (!(entry->flags & 8)) {
							psndBGMOff(0x3800);
						}
						psndBGMOn(0x211, "BGM_FF_GET_BADGE1");
						break;
					case 3:
						if (!(entry->flags & 8)) {
							psndBGMOff(0x3800);
						}
						psndBGMOn(0x211, "BGM_FF_GET_IMPORTANT_ITEM1");
						break;
					default:
						if (!(entry->flags & 8)) {
							psndBGMOff(0x3800);
						}
						psndBGMOn(0x211, "BGM_FF_GET_ITEM1");
						break;
				}
			}
			if (type == 8) {
				evtSetValue(NULL, 0xF5DE01A2, evtGetValue(NULL, 0xF5DE01A2) + 1);
			}
			entry->flags &= ~0x2000;
			itemGetSound(entry);
			entry->winId[0] = winMgrEntry(&itemdrv_window_desc[0]);
			winMgrOpen(entry->winId[0]);
			winMgrSetParam(entry->winId[0], entry);
			if (!(entry->flags2 & 0x2000)) {
				entry->winId[1] = winMgrEntry(&itemdrv_window_desc[1]);
				winMgrOpen(entry->winId[1]);
				winMgrSetParam(entry->winId[1], entry);
			}
			if (!itemGetPouch(entry)) {
				entry->winId[2] = winMgrEntry(&itemdrv_window_desc[2]);
				winMgrOpen(entry->winId[2]);
				winMgrSetParam(entry->winId[2], entry);
			}
			if (entry->itemId == 0x49) {
				iconChange(entry->name, 0x114);
			}
			if (!entry->effect) {
				iconNameToPtr(entry->name)->uflags |= 0x80;
			}
			break;
		case 2:
			if (!(entry->flags2 & 0x2000)) {
				marioCtrlOff();
				entry->flags2 |= 0x1000000;
			}
			entry->subState = 3;
		case 3:
			if (!(entry->flags & 0x8000) && !(entry->flags & 0x2000)) {
				if (psndBGMChk(1)) {
					entry->flags |= 0x2000;
					psndBGMOff(0x201);
					if (!(entry->flags & 8)) {
						psndBGMOn(0xA0, NULL);
					}
				}
			}
			if (winMgrAction(entry->winId[0])) {
				break;
			}
			if (!(keyGetButtonTrg(0) & 0x300)) {
				break;
			}
			winMgrCloseAutoDelete(entry->winId[0]);
			if (!(entry->flags2 & 0x2000)) {
				winMgrCloseAutoDelete(entry->winId[1]);
			}
			if (!(entry->flags & 0x8000) && !(entry->flags & 0x2000)) {
				psndBGMOff(0x201);
				if (!(entry->flags & 8)) {
					psndBGMOn(0xA0, NULL);
				}
			}
			if (entry->flags2 & 0x2000) {
				entry->subState = 6;
				break;
			}
			if (entry->itemId >= 0x79 && entry->itemId < 0xEC && entry->itemId != 0x7D && !swGet(0xEB) && !(gp->flags & 0x1000)) {
				swSet(0xEB);
				entry->subState = 4;
				wp->msgWindowId = msgWindow_Entry(msgSearch("item_first_hit"), 0, 0);
				break;
			}
			effSoftDelete(wp->effect);
			marioSetCamId(4);
			iconFlagOff(entry->name, 0x100);
			if (entry->itemId == 0x49) {
				iconChange(entry->name, 0x115);
			}
			if (!entry->effect) {
				iconNameToPtr(entry->name)->uflags &= ~0x80;
			}
			if (entry->flags2 & 1) {
				itemGetEnd(entry);
				itemDelete(entry->name);
				break;
			}
			entry->subState = 5;
			winMgrCloseAutoDelete(entry->winId[2]);
			marioChgStayMotion();
			iconFlagOn(entry->name, 2);
			{
				s32 id = entry->itemId;
				if (id >= 0xF0 && id < 0x153) {
					wp->select = winMgrSelectEntry(2, id, 1);
				}
				else {
					wp->select = winMgrSelectEntry(1, id, 1);
				}
			}
			break;
		case 4:
			if (windowCheckID(wp->msgWindowId)) {
				break;
			}
			effSoftDelete(wp->effect);
			marioSetCamId(4);
			iconFlagOff(entry->name, 0x100);
			itemGetEnd(entry);
			itemDelete(entry->name);
			break;
		case 5:
			select = winMgrSelect(wp->select);
			if (!select) {
				break;
			}
			winMgrSelectDelete(wp->select);
			if (select < 0) {
				if (entry->flags2 & 0x4000000) {
					entry->flags |= 0x100;
				}
			}
			else {
				pouchRemoveItem(select);
				itemGetPouch(entry);
				entry->flags2 &= ~1;
				entry->itemId = select;
				entry->evtCode = 0;
				entry->evtId = 0;
				entry->flags &= ~0x60;
				iconChange(entry->name, itemDataTable[entry->itemId].icon_id);
				wp->currId++;
				sprintf(iconNameToPtr(entry->name)->name, "_i%05x", wp->currId);
				sprintf(entry->name, "_i%05x", wp->currId);
				entry->flags |= 0x100;
			}
			entry->flags &= ~0x1000;
			entry->speed = 85.0f;
			entry->velocityY = 120.0f;
			entry->bounceFactor = 0.7f;
			entry->gravityScale = 1.0f;
			entry->winId[0] = winMgrEntry(&itemdrv_window_desc[3]);
			winMgrOpen(entry->winId[0]);
			winMgrSetParam(entry->winId[0], entry);
			marioChgGetItemMotion();
			iconFlagOff(entry->name, 2);
			if (mario->flags & 0x2000000) {
				entry->flags2 |= 0x8000;
			}
			entry->subState = 9;
			break;
		case 6:
			wp->lectureEvt = evtEntryType(all_juyoitem_lecture, 0, 0, 0);
			wp->lectureEvt->lwData[8] = (s32)entry;
			wp->lectureEvt->lwData[9] = (s32)wp->effect;
			psndClearFlag(0x80);
			entry->subState = 7;
			break;
		case 7:
			if (evtCheckID(wp->lectureEvt->eventId)) {
				break;
			}
			itemGetEnd(entry);
			itemDelete(entry->name);
			break;
		case 9:
			if (!(keyGetButtonTrg(0) & 0x100)) {
				break;
			}
			winMgrCloseAutoDelete(entry->winId[0]);
			entry->flags2 |= 8;
			itemModeChange(entry, 6);
			entry->flags &= ~0x10;
			if (entry->itemId >= 1 && entry->itemId < 0x79) {
				entry->timer = 0;
			}
			else if (entry->itemId >= 0xF0 && entry->itemId < 0x153) {
				entry->timer = 0;
			}
			else {
				entry->timer = 20000;
			}
			entry->flags2 |= 0x10000;
			entry->flags2 &= ~0x1000;
			entry->flags &= ~2;
			itemGetEnd(entry);
			break;
		case 8:
			if (mario->flags & 0x2000000) {
				entry->flags2 |= 0x8000;
			}
			entry->timer = 0;
			if (entry->flags2 & 0x1000) {
				itemModeChange(entry, 1);
				entry->flags2 &= ~4;
				entry->flags2 &= ~8;
				entry->flags2 &= ~0x4000;
				entry->flags2 &= ~0x1000;
				entry->flags &= ~0x1000;
			}
			else {
				entry->speed = 85.0f;
				entry->velocityY = 120.0f;
				entry->bounceFactor = 0.7f;
				entry->gravityScale = 1.0f;
				entry->flags2 |= 8;
				itemModeChange(entry, 6);
				entry->flags &= ~0x10;
				entry->flags2 &= ~0x1000;
				entry->flags &= ~2;
				entry->flags &= ~0x1000;
			}
			marioStSystemLevel(0);
			psndClearFlag(0x80);
			if (entry->flags2 & 0x1000000) {
				entry->flags2 &= ~0x1000000;
				marioCtrlOn();
			}
			marioKeyOn();
			break;
	}
}
#endif

static s32 _move_dir_1090;
#ifdef NONMATCHING
void itemseq_Bound(ItemEntry* entry) {
	static s32 _move_dir;
	MarioWork* mario;
	CameraEntry* camera;
	HitEntry* hit;
	MapObjectEntry* mobj;
	BOOL isFloor, bounce;
	s64 delta;
	f32 t2sq, dt, dy, t2, dx, t1;
	f32 dz, v, peak, height;
	f32 newX, newZ;
	s32 newDir;
	Vec pos;
	s32 itemId;

	mario = marioGetPtr();
	camera = camGetPtr(4);
	switch (entry->subState) {
		case 0:
			entry->subState = 1;
			entry->airTime = 0;
			entry->baseTime = gp->renderTime;
			entry->curTime = gp->renderTime;
			entry->bounceCount = 0;
			if (entry->flags2 & 0x10) {
				break;
			}
			switch (entry->mode) {
				case 6:
					entry->flags2 |= 4;
				case 5:
					if (!(entry->flags & 0x10)) {
						entry->bounceFactor = 1.0f;
						entry->gravityScale = 1.0f;
						entry->maxBounces = 0;
						entry->velocityY = 500.0f;
					}
					if (!(entry->flags2 & 0x40)) {
						switch (entry->itemId) {
							case 0x79:
							case 0x7B:
							case 0x7C:
								entry->speed = irand(30) + 45;
								if (irand(100) < 50) {
									entry->direction = 90.0f + camera->viewYaw + irand(60) - 30.0f;
								}
								else {
									entry->direction = camera->viewYaw - 90.0f + irand(60) - 30.0f;
								}
								break;
							default:
								entry->speed = 100.0f;
								if (irand(100) < 50) {
									entry->direction = 90.0f + camera->viewYaw + irand(30) - 15.0f;
								}
								else {
									entry->direction = camera->viewYaw - 90.0f + irand(30) - 15.0f;
								}
								break;
						}
					}
					else {
						entry->direction = _move_dir;
						_move_dir += 132;
						if (_move_dir >= 360) {
							_move_dir -= 360;
						}
						entry->speed = 0.67f * (irand(30) + 65);
					}
					break;
				case 4:
					entry->flags2 |= 8;
				case 3:
					if (!(entry->flags & 0x10)) {
						entry->bounceFactor = 1.0f;
						entry->gravityScale = 1.0f;
						entry->maxBounces = 0;
					}
					entry->speed = 0.0f;
					entry->direction = 0;
					entry->velocityY = 0.0f;
					break;
				case 10:
					entry->bounceFactor = 1.0f;
					entry->gravityScale = 1.0f;
					entry->maxBounces = 0;
					entry->velocityY = 500.0f;
					entry->speed = 0.0f;
					entry->direction = 0;
					entry->flags2 |= 0x20;
					entry->flags2 |= 4;
					break;
			}
			break;
		case 1:
			entry->curTime = gp->renderTime;
			delta = entry->curTime - entry->baseTime;
			dt = OSTicksToMicroseconds(delta) / 1000000.0f;
			t1 = OSTicksToMicroseconds(entry->airTime) / 1000000.0f;
			t2 = OSTicksToMicroseconds(entry->airTime + delta) / 1000000.0f;
			dx = dt * (entry->speed * (f32)sin(6.2831855f * entry->direction / 360.0f));
			dz = dt * (entry->speed * -(f32)cos(6.2831855f * entry->direction / 360.0f));
			if (entry->flags2 & 0x8000) {
				dz = 0.0f;
			}
			t2sq = t2 * t2;
			dy = entry->velocityY * dt + (-980.0f * entry->gravityScale) * (t2sq - t1 * t1);
			if (entry->flags2 & 4) {
				if (entry->bounceCount != 0 || dy < 0.0f) {
					entry->flags2 &= ~4;
				}
			}
			if (entry->flags2 & 8 && entry->bounceCount != 0) {
				entry->flags2 &= ~8;
			}
			if (entry->flags2 & 0x20 && dy < 0.0f) {
				effStardustEntry(1, 3, 30, entry->position.x, entry->position.y, entry->position.z, 16.0f, 16.0f);
				itemDelete(entry->name);
				return;
			}
			newDir = entry->direction;
			hit = itemHitCheckSide(entry, &newX, dx, &newZ, dz, &newDir);
			entry->position.x = newX;
			entry->position.z = newZ;
			entry->direction = newDir;
			if (hit) {
				entry->speed *= 0.25f;
			}
			if (!(entry->flags2 & 0x20) && !(entry->flags & 0x800)) {
				hit = itemHitCheckUp(entry, dy);
				if (hit) {
					entry->velocityY = -entry->velocityY * 0.25f;
					dy = 0.0f;
					entry->airTime = 0;
					entry->baseTime = entry->curTime;
				}
			}
			if (entry->flags2 & 0x100000 && entry->position.y <= -1000.0f) {
				itemModeChange(entry, 7);
				entry->flags2 &= ~4;
				entry->flags2 &= ~8;
				entry->flags2 &= ~0x4000;
				if (entry->itemId >= 1 && entry->itemId < 0x79) {
					entry->timer = 0;
				}
				else if (entry->itemId >= 0xF0 && entry->itemId < 0x153) {
					entry->timer = 0;
				}
				else {
					entry->timer = 20000;
				}
				entry->flags2 |= 0x10000;
				entry->flags2 &= ~0x1000;
				entry->flags |= 0x100;
				break;
			}
			if (dy >= 0.0f) {
				hit = NULL;
				entry->position.y += dy;
			}
			else if (entry->flags2 & 0x100000) {
				hit = NULL;
				entry->position.y += dy;
			}
			else {
				hit = itemHitCheckY(entry, entry->position.z, 20.0f + entry->position.y, entry->position.x, dy);
			}
			if (hit) {
				if (hitGetAttr(hit) & 0x600) {
					entry->flags2 |= 0x100000;
					{
						Vec sndPos = (Vec){0.0f, 0.0f, 0.0f};
						sndPos.x = entry->position.x;
						sndPos.y = entry->position.y;
						sndPos.z = entry->position.z;
						psndSFXOn_3D((const char*)0x194, &sndPos);
					}
					effSplashEntry(0, entry->position.x, entry->position.y, entry->position.z, 0.7f);
					entry->flags |= 2;
				}
				else {
					entry->bounceCount++;
					if (!(hitGetAttr(hit) & 0x80000000) && entry->maxBounces != 0 && entry->bounceCount >= entry->maxBounces) {
						itemModeChange(entry, 1);
						entry->flags2 &= ~4;
						entry->flags2 &= ~8;
						entry->flags2 &= ~0x4000;
						break;
					}
					{
					pos = (Vec){entry->position.x, entry->position.y, entry->position.z};
					switch (itemId = entry->itemId) {
						case 0x79:
							psndSFXOn_3D("SFX_COIN_LEAPED1", &pos);
							break;
						case 0x7A:
							psndSFXOn_3D("SFX_EVT_GAME_MONTE_LEAPED1", &pos);
							break;
						case 0x7B:
							psndSFXOn_3D("SFX_HEART_LEAPED1", &pos);
							break;
						case 0x7C:
							psndSFXOn_3D("SFX_FLOWER_LEAPED1", &pos);
							break;
						case 0x7D:
							psndSFXOn_3D("SFX_STAR_PIECE_LEAPED1", &pos);
							break;
						case 0x72: case 0x73: case 0x74: case 0x75: case 0x76: case 0x77: case 0x78:
							psndSFXOn_3D("SFX_EVT_STARSTONE_JUMP1", &pos);
							break;
						default:
							if (itemId >= 0xF0 && itemId < 0x153) {
								psndSFXOn_3D("SFX_BADGE_LEAPED1", &pos);
							}
							else {
								psndSFXOn_3D("SFX_ITEM_LEAPED1", &pos);
							}
							break;
					}
					}
					isFloor = FALSE;
					if (entry->flags & 0x80 && entry->velocityY != 0.0f) {
						bounce = TRUE;
					}
					else if (hitGetAttr(hit) & 0x80000000 && entry->velocityY != 0.0f) {
						mobj = mobjHitObjPtrToPtr(hit);
						if (mario->characterId == 2) {
							bounce = FALSE;
						}
						else if (mobj && strcmp(mobj->animName, "MOBJ_KururinFloor")) {
							bounce = TRUE;
							isFloor = TRUE;
						}
						else {
							goto no_bounce;
						}
					}
					else {
					no_bounce:
						bounce = FALSE;
					}
					if (!bounce) {
						v = entry->velocityY * dt + (-980.0f * entry->gravityScale) * ((t2 + dt) * (t2 + dt) - t2sq);
						entry->velocityY = 0.7f * (entry->bounceFactor * (-v / dt));
					}
					peak = __fabs(0.5f * (entry->velocityY / (-980.0f * entry->gravityScale)));
					height = entry->velocityY * peak + peak * ((-980.0f * entry->gravityScale) * peak);
					if (!isFloor && height <= 8.0f) {
						itemModeChange(entry, 1);
						entry->flags2 &= ~4;
						entry->flags2 &= ~8;
						entry->flags2 &= ~0x4000;
					}
					if (entry->flags & 0x200 && entry->bounceCount <= 1) {
						entry->direction = entry->savedDirection;
						entry->speed = entry->savedSpeed;
						entry->flags &= ~0x200;
					}
					entry->airTime = 0;
					entry->baseTime = gp->renderTime;
					break;
				}
			}
			entry->airTime += delta;
			entry->baseTime = entry->curTime;
			break;
	}
	entry->flags2 &= ~0x10;
}
#endif

#ifdef NONMATCHING
void itemSetPosition(ItemEntry* entry, f32 x, f32 y, f32 z) {
	entry->position.x = x;
	entry->position.y = y;
	entry->position.z = z;
}
#endif





#ifdef NONMATCHING
void itemGetSound(ItemEntry* entry) {
	Vec pos;

	pos = (Vec){entry->position.x, entry->position.y, entry->position.z};
	switch (entry->itemId) {
		case 0x79:
			effStardustEntry(1, 3, 30, entry->position.x, 35.0f + entry->position.y, entry->position.z, 16.0f, 16.0f);
			psndSFXOn_3D("SFX_COIN_GET1", &pos);
			break;
		case 0x7A:
			effStardustEntry(1, 3, 30, entry->position.x, 35.0f + entry->position.y, entry->position.z, 16.0f, 16.0f);
			psndSFXOn_3D("SFX_EVT_GAME_MONTE_COUNT1", &pos);
			break;
		case 0x7B:
			psndSFXOn_3D("SFX_HEART_GET1", &pos);
			break;
		case 0x7C:
			psndSFXOn_3D("SFX_FLOWER_GET1", &pos);
			break;
		case 0x7D:
			break;
	}
}
#endif

#ifdef NONMATCHING
HitEntry* itemHitCheckSide(ItemEntry* entry, f32* outX, f32 dx, f32* outZ, f32 dz, s32* angle) {
	HitEntry* hit;
	f32 a, b;
	f32 hitX, hitY, hitZ, hitDist, hitNX, hitNY, hitNZ;
	f32 sin, cos;
	f32 dot, ox, oz;

	*outX = entry->position.x;
	*outZ = entry->position.z;
	if (dx == 0.0f && dz == 0.0f) {
		return NULL;
	}
	sincosf(&sin, &cos, angleABf(0.0f, 0.0f, dx, dz));
	hitDist = 10.0f + item_sqrtf(dx * dx + dz * dz);
	hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ,
		entry->position.x, 15.0f + entry->position.y, entry->position.z, sin, 0.0f, cos);
	if (hit) {
		dot = dx * hitNX + dz * hitNZ;
		ox = 0.5f * (dx - dot * hitNX);
		oz = 0.5f * (dz - dot * hitNZ);
		*outX += ox;
		*outZ += oz;
		a = reviseAngle(180.0f + *angle);
		b = reviseAngle(angleABf(0.0f, 0.0f, 100.0f * hitNX, 100.0f * hitNZ));
		*angle = reviseAngle(b + reviseAngle(b - a));
		return hit;
	}
	hitDist = 10.0f + item_sqrtf(dx * dx + dz * dz);
	hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ,
		entry->position.x, 15.0f + entry->position.y, entry->position.z, sin, 0.0f, cos);
	if (hit) {
		dot = dx * hitNX + dz * hitNZ;
		ox = 0.5f * (dx - dot * hitNX);
		oz = 0.5f * (dz - dot * hitNZ);
		*outX += ox;
		*outZ += oz;
		a = reviseAngle(180.0f + *angle);
		b = reviseAngle(angleABf(0.0f, 0.0f, 100.0f * hitNX, 100.0f * hitNZ));
		*angle = reviseAngle(b + reviseAngle(b - a));
		return hit;
	}
	*outX += dx;
	*outZ += dz;
	return NULL;
}
#endif

#ifdef NONMATCHING
HitEntry*
itemHitCheckY(ItemEntry* entry, f32 z, f32 y, f32 x, f32 vy) {
	HitEntry* hit;
	f32 hitX, hitY, hitZ, hitDist, hitNX, hitNY, hitNZ;

	hitDist = 20.0f + __fabs(vy);
	if (hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, 0.0f, -1.0f, 0.0f)) {
		entry->position.y = hitY;
	}
	else {
		hit = NULL;
		entry->position.y += vy;
	}
	return hit;
}
#endif

#ifdef NONMATCHING
HitEntry*
itemHitCheckUp(ItemEntry* entry, f32 vy) {
	HitEntry* hit;
	f32 hitX, hitY, hitZ, hitDist, hitNX, hitNY, hitNZ;
	f32 x, y, z;

	if (vy <= 0.0f) {
		return NULL;
	}
	x = entry->position.x; y = 20.0f + entry->position.y; z = entry->position.z;
	hitDist = 20.0f + __fabs(vy);
	if (hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, 0.0f, 1.0f, 0.0f)) {
		entry->position.y = hitY - 20.0f - 4.0f;
		return hit;
	}
	x = entry->position.x; y = entry->position.y; z = entry->position.z;
	hitDist = 20.0f + __fabs(vy);
	if (hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, 0.0f, 1.0f, 0.0f)) {
		entry->position.y = hitY - 20.0f;
		return hit;
	}
	return NULL;
}
#endif

#ifdef NONMATCHING
void itemForceGet(ItemEntry* entry) {
	entry->timer = 0;
	itemModeChange(entry, 2);
	entry->flags |= 0x1000;
	entry->flags2 &= ~0x10000;
}
#endif

#ifdef NONMATCHING
void itemNokoForceGet(ItemEntry* entry) {
	if (itemGetNokoCheck(entry)) {
		entry->timer = 0;
		itemModeChange(entry, 2);
		entry->flags |= 0x5000;
		entry->flags2 &= ~0x10000;
	}
	else {
		entry->timer = 0;
		itemModeChange(entry, 1);
		entry->flags2 &= ~4;
		entry->flags2 &= ~8;
		entry->flags2 &= ~0x4000;
		entry->flags2 &= ~0x1000;
	}
}
#endif

#ifdef NONMATCHING
void itemFlagOn(ItemEntry* entry, u16 flags) {
	entry->flags |= flags;
}
#endif

#ifdef NONMATCHING
void itemFlagOff(ItemEntry* entry, u16 flags) {
	entry->flags &= ~flags;
}
#endif

#ifdef NONMATCHING
u16 itemFlag(ItemEntry* entry, u16 flags) {
	return entry->flags & flags;
}
#endif

#ifdef NONMATCHING
void itemStatusOn(ItemEntry* entry, u32 flags) {
	entry->flags2 |= flags;
}
#endif

#ifdef NONMATCHING
u32 itemStatus(ItemEntry* entry, u32 flags) {
	return entry->flags2 & flags;
}
#endif

#ifdef NONMATCHING
void itemPickUp(ItemEntry* entry) {
	entry->flags2 |= 0x1000;
	itemModeChange(entry, 8);
	entry->timer = 0;
	entry->flags2 &= ~0x100;
}
#endif


// prototypes for asm stopgap forward references
void itemPickUp(ItemEntry* entry);
u32 itemStatus(ItemEntry* entry, u32 flags);
void itemStatusOn(ItemEntry* entry, u32 flags);
u16 itemFlag(ItemEntry* entry, u16 flags);
void itemFlagOff(ItemEntry* entry, u16 flags);
void itemFlagOn(ItemEntry* entry, u16 flags);
void itemNokoForceGet(ItemEntry* entry);
void itemForceGet(ItemEntry* entry);
HitEntry* itemHitCheckSide(ItemEntry* entry, f32* outX, f32 dx, f32* outZ, f32 dz, s32* angle);
void itemSetPosition(ItemEntry* entry, f32 x, f32 y, f32 z);
void itemseq_Bound(ItemEntry* entry);
void itemseq_GetItem(ItemEntry* entry);
void winFullDisp(WinMgrEntry* win);
void winHelpDisp(WinMgrEntry* win);
void winHelpMain(WinMgrEntry* win);
void winNameDisp2(WinMgrEntry* win);
void winNameDisp(WinMgrEntry* win);
ItemEntry* itemNearDistCheck(f32 x, f32 y, f32 z, f32 range);
ItemEntry* itemHitCheck(f32 x, f32 y, f32 z, f32 range);
ItemEntry* itemNameToPtr(char* name);
void itemDelete(const char* name);
ItemEntry* itemEntry(const char* name, s32 itemId, s32 type, s32 evtId, s32 a5, f32 x, f32 y, f32 z);
void itemModeChange(ItemEntry* entry, s32 mode);
void itemMain(void);
BOOL N_itemPickUpFromFieldCheck(void);
BOOL itemGetNokoCheck(ItemEntry* entry);
BOOL itemGetCheck(ItemEntry* entry);
void itemCoinDrop(Vec* position);
void itemReInit(void);
void itemInit(void);
#ifndef NONMATCHING
void FontDrawEdgeOff();
#endif
#ifndef NONMATCHING
void FontDrawEdge();
#endif
#ifndef NONMATCHING
// ASM-STOPGAP: itemInit (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802cabe0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cabec[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cabf8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cac04[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cac10[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cac1c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f64 double_20_802cac28 = 20;
__declspec(section ".rodata") const f64 double_0p5_802cac30 = 0.5;
__declspec(section ".rodata") const f64 double_3_802cac38 = 3;
__declspec(section ".rodata") const f64 double_0_802cac40 = 0;
__declspec(section ".rodata") const f64 double_to_int_802cac48 = 4503601774854144;
__declspec(section ".rodata") const char str_802CAC50[] = "SFX_COIN_GET1\000\000";
__declspec(section ".rodata") const char str_802CAC60[] = "SFX_EVT_GAME_MONTE_COUNT1\000\000";
__declspec(section ".rodata") const char str_802CAC7C[] = "SFX_HEART_GET1\000";
__declspec(section ".rodata") const char str_802CAC8C[] = "SFX_FLOWER_GET1";
__declspec(section ".rodata") const char str_802CAC9C[] = "SFX_COIN_LEAPED1\000\000\000";
__declspec(section ".rodata") const char str_802CACB0[] = "SFX_EVT_GAME_MONTE_LEAPED1\000";
__declspec(section ".rodata") const char str_802CACCC[] = "SFX_HEART_LEAPED1\000\000";
__declspec(section ".rodata") const char str_802CACE0[] = "SFX_FLOWER_LEAPED1\000";
__declspec(section ".rodata") const char str_802CACF4[] = "SFX_STAR_PIECE_LEAPED1\000";
__declspec(section ".rodata") const char str_802CAD0C[] = "SFX_EVT_STARSTONE_JUMP1";
__declspec(section ".rodata") const char str_802CAD24[] = "SFX_BADGE_LEAPED1\000\000";
__declspec(section ".rodata") const char str_802CAD38[] = "SFX_ITEM_LEAPED1\000\000\000";
__declspec(section ".rodata") const char str_802CAD4C[] = "MOBJ_KururinFloor\000\000";
__declspec(section ".rodata") const char str_802CAD60[] = "BGM_FF_GET_STARPIECE1\000\000";
__declspec(section ".rodata") const char str_802CAD78[] = "BGM_FF_GET_KEYITEM1";
__declspec(section ".rodata") const char str_802CAD8C[] = "BGM_FF_GET_BADGE1\000\000";
__declspec(section ".rodata") const char str_802CADA0[] = "BGM_FF_GET_IMPORTANT_ITEM1\000";
__declspec(section ".rodata") const char str_802CADBC[] = "BGM_FF_GET_ITEM1\000\000\000";
__declspec(section ".rodata") const char str_802CADD0[] = "item_first_hit\000";
__declspec(section ".rodata") const char str_802CADE0[] = "_i%05x\000";
__declspec(section ".rodata") const char str_802CADE8[] = "msg_window_badge_full\000\000";
__declspec(section ".rodata") const char str_802CAE00[] = "msg_window_item_full\000\000\000";
__declspec(section ".rodata") const char str_802CAE18[] = "msg_window_item_release";
__declspec(section ".rodata") const char str_802CAE30[] = "msg_window_badge_get\000\000\000";
__declspec(section ".rodata") const char str_802CAE48[] = "msg_window_item_get";
__declspec(section ".rodata") const f64 double_neg1_802cae60 = -1;
__declspec(section ".rodata") const u32 gap_04_802CAE68_rodata[6] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
__declspec(section ".sdata2") const u32 dat_8041af90 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041af94 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041af98 = 0xFFFFFFFF;
__declspec(section ".sdata2") const f32 float_0_8041af9c = 0.0f;
__declspec(section ".sdata2") const f32 float_20_8041afa0 = 20.0f;
__declspec(section ".sdata2") const f32 float_1_8041afa4 = 1.0f;
__declspec(section ".sdata2") const f32 float_4_8041afa8 = 4.0f;
__declspec(section ".sdata2") const f32 float_neg1_8041afac = -1.0f;
__declspec(section ".sdata2") const f32 float_10_8041afb0 = 10.0f;
__declspec(section ".sdata2") const f32 float_15_8041afb4 = 15.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041afb8 = 0.5f;
__declspec(section ".sdata2") const f32 float_180_8041afbc = 180.0f;
__declspec(section ".sdata2") const f32 float_100_8041afc0 = 100.0f;
__declspec(section ".sdata2") const f32 float_35_8041afc4 = 35.0f;
__declspec(section ".sdata2") const f32 float_16_8041afc8 = 16.0f;
__declspec(section ".sdata2") const f32 float_500_8041afcc = 500.0f;
__declspec(section ".sdata2") const f32 float_90_8041afd0 = 90.0f;
__declspec(section ".sdata2") const f32 float_30_8041afd4 = 30.0f;
__declspec(section ".sdata2") const f32 float_0p67_8041afd8 = 0.67f;
__declspec(section ".sdata2") const f32 float_1E06_8041afdc = 1000000.0f;
__declspec(section ".sdata2") const f32 float_6p2832_8041afe0 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_360_8041afe4 = 360.0f;
__declspec(section ".sdata2") const f32 float_neg980_8041afe8 = -980.0f;
__declspec(section ".sdata2") const f32 float_0p25_8041afec = 0.25f;
__declspec(section ".sdata2") const f32 float_neg1000_8041aff0 = -1000.0f;
__declspec(section ".sdata2") const f32 float_0p7_8041aff4 = 0.7f;
__declspec(section ".sdata2") const f32 float_8_8041aff8 = 8.0f;
__declspec(section ".sdata2") const f32 float_1024_8041affc = 1024.0f;
__declspec(section ".sdata2") const f32 float_50_8041b000 = 50.0f;
__declspec(section ".sdata2") const f32 float_62_8041b004 = 62.0f;
__declspec(section ".sdata2") const f32 float_85_8041b008 = 85.0f;
__declspec(section ".sdata2") const f32 float_120_8041b00c = 120.0f;
__declspec(section ".sdata2") const f32 float_12_8041b010 = 12.0f;
__declspec(section ".sdata2") const f32 float_1000_8041b014 = 1000.0f;

void itemseq_GetItem(ItemEntry* entry);
#pragma force_active on
__declspec(section ".data") static void* jumptable_80312418[] = {
    (char*)itemseq_GetItem + 0x64,
    (char*)itemseq_GetItem + 0x3D8,
    (char*)itemseq_GetItem + 0x938,
    (char*)itemseq_GetItem + 0x95C,
    (char*)itemseq_GetItem + 0xC5C,
    (char*)itemseq_GetItem + 0xD8C,
    (char*)itemseq_GetItem + 0xFA8,
    (char*)itemseq_GetItem + 0xFEC,
    (char*)itemseq_GetItem + 0x1200,
    (char*)itemseq_GetItem + 0x1104,
};
ItemEntry* itemEntry(const char* name, s32 itemId, s32 type, s32 evtId, s32 a5, f32 x, f32 y, f32 z);
#pragma force_active on
__declspec(section ".data") static void* jumptable_80312440[] = {
    (char*)itemEntry + 0x628,
    (char*)itemEntry + 0x63C,
    (char*)itemEntry + 0x7BC,
    (char*)itemEntry + 0x670,
    (char*)itemEntry + 0x65C,
    (char*)itemEntry + 0x770,
    (char*)itemEntry + 0x790,
    (char*)itemEntry + 0x764,
    (char*)itemEntry + 0x700,
    (char*)itemEntry + 0x6F4,
    (char*)itemEntry + 0x72C,
    (char*)itemEntry + 0x690,
    (char*)itemEntry + 0x6BC,
    (char*)itemEntry + 0x7D0,
    (char*)itemEntry + 0x7E4,
    (char*)itemEntry + 0x7F8,
    (char*)itemEntry + 0x614,
    (char*)itemEntry + 0x608,
};
void itemMain(void);
#pragma force_active on
__declspec(section ".data") static void* jumptable_80312488[] = {
    (char*)itemMain + 0x47C,
    (char*)itemMain + 0x29C,
    (char*)itemMain + 0x35C,
    (char*)itemMain + 0x290,
    (char*)itemMain + 0x290,
    (char*)itemMain + 0x284,
    (char*)itemMain + 0x284,
    (char*)itemMain + 0x47C,
    (char*)itemMain + 0x368,
    (char*)itemMain + 0x3BC,
    (char*)itemMain + 0x284,
};
void __cvt_dbl_usll();
void __cvt_sll_flt();
void __div2i();
asm void itemPickUp(ItemEntry* entry) {
	nofralloc
	lwz r5, 0x38(r3)
	li r4, 0x8
	li r0, 0x0
	ori r5, r5, 0x1000
	stw r5, 0x38(r3)
	sth r4, 0x24(r3)
	sth r0, 0x26(r3)
	stw r0, 0x7c(r3)
	stw r0, 0x78(r3)
	lwz r0, 0x38(r3)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x38(r3)
	blr
}

asm u32 itemStatus(ItemEntry* entry, u32 flags) {
	nofralloc
	lwz r0, 0x38(r3)
	and r3, r0, r4
	blr
}

asm void itemStatusOn(ItemEntry* entry, u32 flags) {
	nofralloc
	lwz r0, 0x38(r3)
	or r0, r0, r4
	stw r0, 0x38(r3)
	blr
}

asm u16 itemFlag(ItemEntry* entry, u16 flags) {
	nofralloc
	lhz r0, 0x0(r3)
	and r0, r0, r4
	clrlwi r3, r0, 16
	blr
}

asm void itemFlagOff(ItemEntry* entry, u16 flags) {
	nofralloc
	lhz r0, 0x0(r3)
	andc r0, r0, r4
	sth r0, 0x0(r3)
	blr
}

asm void itemFlagOn(ItemEntry* entry, u16 flags) {
	nofralloc
	lhz r0, 0x0(r3)
	or r0, r0, r4
	sth r0, 0x0(r3)
	blr
}

asm void itemNokoForceGet(ItemEntry* entry) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	bl itemGetNokoCheck
	cmpwi r3, 0x0
	beq @1
	li r3, 0x0
	li r0, 0x2
	stw r3, 0x7c(r31)
	stw r3, 0x78(r31)
	sth r0, 0x24(r31)
	sth r3, 0x26(r31)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x5000
	sth r0, 0x0(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 16, 14
	stw r0, 0x38(r31)
	b @2
	@1:
	li r3, 0x0
	li r0, 0x1
	stw r3, 0x7c(r31)
	stw r3, 0x78(r31)
	sth r0, 0x24(r31)
	sth r3, 0x26(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x38(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x38(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 18, 16
	stw r0, 0x38(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 20, 18
	stw r0, 0x38(r31)
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void itemForceGet(ItemEntry* entry) {
	nofralloc
	li r4, 0x0
	li r0, 0x2
	stw r4, 0x7c(r3)
	stw r4, 0x78(r3)
	sth r0, 0x24(r3)
	sth r4, 0x26(r3)
	lhz r0, 0x0(r3)
	ori r0, r0, 0x1000
	sth r0, 0x0(r3)
	lwz r0, 0x38(r3)
	rlwinm r0, r0, 0, 16, 14
	stw r0, 0x38(r3)
	blr
}

asm HitEntry* itemHitCheckSide(ItemEntry* entry, f32* outX, f32 dx, f32* outZ, f32 dz, s32* angle) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	stw r0, 0x94(r1)
	stfd f31, 0x80(r1)
	psq_st f31, 0x88(r1), 0, 0
	stfd f30, 0x70(r1)
	psq_st f30, 0x78(r1), 0, 0
	stfd f29, 0x60(r1)
	psq_st f29, 0x68(r1), 0, 0
	stmw r26, 0x48(r1)
	mr r27, r3
	lis r3, vec3_802cabe0@ha
	lfs f3, 0x3c(r27)
	mr r28, r4
	fmr f29, f1
	lfs f0, float_0_8041af9c(r2)
	stfs f3, 0x0(r4)
	mr r29, r5
	fmr f30, f2
	mr r30, r6
	lfs f1, 0x44(r27)
	fcmpu cr0, f0, f29
	addi r31, r3, vec3_802cabe0@l
	stfs f1, 0x0(r5)
	bne @1
	fcmpu cr0, f0, f30
	bne @1
	li r3, 0x0
	b @2
	@1:
	lfs f1, float_0_8041af9c(r2)
	fmr f3, f29
	fmr f4, f30
	fmr f2, f1
	bl angleABf
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	bl sincosf
	fmuls f1, f30, f30
	lfs f0, float_0_8041af9c(r2)
	fmadds f31, f29, f29, f1
	fcmpo cr0, f31, f0
	ble @3
	frsqrte f1, f31
	lfd f3, 0x50(r31)
	lfd f2, 0x58(r31)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f31, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f31, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f31, f0, f2
	fmul f0, f1, f0
	fmul f2, f31, f0
	frsp f2, f2
	b @4
	@3:
	lfd f0, 0x60(r31)
	fcmpo cr0, f31, f0
	bge @5
	lis r3, __float_nan@ha
	lfs f2, __float_nan@l(r3)
	b @4
	@5:
	stfs f31, 0xc(r1)
	lis r0, 0x7f80
	lwz r4, 0xc(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @6
	bge @7
	cmpwi r3, 0x0
	beq @8
	b @7
	@6:
	clrlwi. r0, r4, 9
	beq @9
	li r0, 0x1
	b @10
	@9:
	li r0, 0x2
	b @10
	@8:
	clrlwi. r0, r4, 9
	beq @11
	li r0, 0x5
	b @10
	@11:
	li r0, 0x3
	b @10
	@7:
	li r0, 0x4
	@10:
	cmpwi r0, 0x1
	bne @12
	lis r3, __float_nan@ha
	lfs f2, __float_nan@l(r3)
	b @4
	@12:
	fmr f2, f31
	@4:
	lfs f1, float_10_8041afb0(r2)
	addi r4, r1, 0x30
	lfs f0, float_15_8041afb4(r2)
	addi r5, r1, 0x2c
	fadds f1, f1, f2
	lfs f4, 0x14(r1)
	lfs f5, float_0_8041af9c(r2)
	addi r6, r1, 0x28
	lfs f6, 0x10(r1)
	addi r7, r1, 0x24
	stfs f1, 0x24(r1)
	addi r8, r1, 0x20
	addi r9, r1, 0x1c
	addi r10, r1, 0x18
	lfs f2, 0x40(r27)
	li r3, 0x0
	lfs f1, 0x3c(r27)
	fadds f2, f2, f0
	lfs f3, 0x44(r27)
	bl hitCheckFilter
	mr. r26, r3
	beq @13
	lfs f6, 0x18(r1)
	lis r0, 0x4330
	lfs f3, 0x20(r1)
	fmuls f0, f30, f6
	lfs f4, float_0p5_8041afb8(r2)
	lfs f5, 0x0(r28)
	stw r0, 0x38(r1)
	fmadds f0, f29, f3, f0
	lfd f1, 0x68(r31)
	lfs f2, float_180_8041afbc(r2)
	fnmsubs f3, f0, f3, f29
	fnmsubs f0, f0, f6, f30
	fmuls f3, f4, f3
	fmuls f0, f4, f0
	fadds f3, f5, f3
	stfs f3, 0x0(r28)
	lfs f3, 0x0(r29)
	fadds f0, f3, f0
	stfs f0, 0x0(r29)
	lwz r0, 0x0(r30)
	xoris r0, r0, 0x8000
	stw r0, 0x3c(r1)
	lfd f0, 0x38(r1)
	fsubs f0, f0, f1
	fadds f1, f2, f0
	bl reviseAngle
	fmr f30, f1
	lfs f1, float_0_8041af9c(r2)
	lfs f4, float_100_8041afc0(r2)
	lfs f3, 0x20(r1)
	fmr f2, f1
	lfs f0, 0x18(r1)
	fmuls f3, f4, f3
	fmuls f4, f4, f0
	bl angleABf
	bl reviseAngle
	fmr f29, f1
	fsubs f1, f29, f30
	bl reviseAngle
	fadds f1, f29, f1
	bl reviseAngle
	fctiwz f0, f1
	mr r3, r26
	stfd f0, 0x40(r1)
	lwz r0, 0x44(r1)
	stw r0, 0x0(r30)
	b @2
	@13:
	lfs f0, float_0_8041af9c(r2)
	fcmpo cr0, f31, f0
	ble @14
	frsqrte f1, f31
	lfd f3, 0x50(r31)
	lfd f2, 0x58(r31)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f31, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f31, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f31, f0, f2
	fmul f0, f1, f0
	fmul f31, f31, f0
	frsp f31, f31
	b @15
	@14:
	lfd f0, 0x60(r31)
	fcmpo cr0, f31, f0
	bge @16
	lis r3, __float_nan@ha
	lfs f31, __float_nan@l(r3)
	b @15
	@16:
	stfs f31, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @17
	bge @18
	cmpwi r3, 0x0
	beq @19
	b @18
	@17:
	clrlwi. r0, r4, 9
	beq @20
	li r0, 0x1
	b @21
	@20:
	li r0, 0x2
	b @21
	@19:
	clrlwi. r0, r4, 9
	beq @22
	li r0, 0x5
	b @21
	@22:
	li r0, 0x3
	b @21
	@18:
	li r0, 0x4
	@21:
	cmpwi r0, 0x1
	bne @15
	lis r3, __float_nan@ha
	lfs f31, __float_nan@l(r3)
	@15:
	lfs f1, float_10_8041afb0(r2)
	addi r4, r1, 0x30
	lfs f0, float_15_8041afb4(r2)
	addi r5, r1, 0x2c
	fadds f1, f1, f31
	lfs f4, 0x14(r1)
	lfs f5, float_0_8041af9c(r2)
	addi r6, r1, 0x28
	lfs f6, 0x10(r1)
	addi r7, r1, 0x24
	stfs f1, 0x24(r1)
	addi r8, r1, 0x20
	addi r9, r1, 0x1c
	addi r10, r1, 0x18
	lfs f2, 0x40(r27)
	li r3, 0x0
	lfs f1, 0x3c(r27)
	fadds f2, f2, f0
	lfs f3, 0x44(r27)
	bl hitCheckFilter
	mr. r27, r3
	beq @23
	lfs f6, 0x18(r1)
	lis r0, 0x4330
	lfs f3, 0x20(r1)
	fmuls f0, f30, f6
	lfs f4, float_0p5_8041afb8(r2)
	lfs f5, 0x0(r28)
	stw r0, 0x40(r1)
	fmadds f0, f29, f3, f0
	lfd f1, 0x68(r31)
	lfs f2, float_180_8041afbc(r2)
	fnmsubs f3, f0, f3, f29
	fnmsubs f0, f0, f6, f30
	fmuls f3, f4, f3
	fmuls f0, f4, f0
	fadds f3, f5, f3
	stfs f3, 0x0(r28)
	lfs f3, 0x0(r29)
	fadds f0, f3, f0
	stfs f0, 0x0(r29)
	lwz r0, 0x0(r30)
	xoris r0, r0, 0x8000
	stw r0, 0x44(r1)
	lfd f0, 0x40(r1)
	fsubs f0, f0, f1
	fadds f1, f2, f0
	bl reviseAngle
	fmr f30, f1
	lfs f1, float_0_8041af9c(r2)
	lfs f4, float_100_8041afc0(r2)
	lfs f3, 0x20(r1)
	fmr f2, f1
	lfs f0, 0x18(r1)
	fmuls f3, f4, f3
	fmuls f4, f4, f0
	bl angleABf
	bl reviseAngle
	fmr f29, f1
	fsubs f1, f29, f30
	bl reviseAngle
	fadds f1, f29, f1
	bl reviseAngle
	fctiwz f0, f1
	mr r3, r27
	stfd f0, 0x38(r1)
	lwz r0, 0x3c(r1)
	stw r0, 0x0(r30)
	b @2
	@23:
	lfs f0, 0x0(r28)
	li r3, 0x0
	fadds f0, f0, f29
	stfs f0, 0x0(r28)
	lfs f0, 0x0(r29)
	fadds f0, f0, f30
	stfs f0, 0x0(r29)
	@2:
	psq_l f31, 0x88(r1), 0, 0
	lfd f31, 0x80(r1)
	psq_l f30, 0x78(r1), 0, 0
	lfd f30, 0x70(r1)
	psq_l f29, 0x68(r1), 0, 0
	lfd f29, 0x60(r1)
	lmw r26, 0x48(r1)
	lwz r0, 0x94(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm void itemSetPosition(ItemEntry* entry, f32 x, f32 y, f32 z) {
	nofralloc
	stfs f1, 0x3c(r3)
	stfs f2, 0x40(r3)
	stfs f3, 0x44(r3)
	blr
}

asm void itemseq_Bound(ItemEntry* entry) {
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
	stfd f27, 0xa0(r1)
	psq_st f27, 0xa8(r1), 0, 0
	stmw r24, 0x80(r1)
	lis r4, vec3_802cabe0@ha
	mr r31, r3
	addi r30, r4, vec3_802cabe0@l
	bl marioGetPtr
	mr r27, r3
	li r3, 0x4
	bl camGetPtr
	lhz r0, 0x26(r31)
	mr r28, r3
	cmpwi r0, 0x1
	beq @1
	bge @2
	cmpwi r0, 0x0
	bge @3
	b @2
	@3:
	li r0, 0x1
	li r4, 0x0
	sth r0, 0x26(r31)
	stw r4, 0x64(r31)
	stw r4, 0x60(r31)
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x6c(r31)
	stw r0, 0x68(r31)
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x74(r31)
	stw r0, 0x70(r31)
	stw r4, 0x8c(r31)
	lwz r3, 0x38(r31)
	rlwinm. r0, r3, 0, 27, 27
	bne @2
	lhz r0, 0x24(r31)
	cmpwi r0, 0x6
	beq @4
	bge @5
	cmpwi r0, 0x4
	beq @6
	bge @7
	cmpwi r0, 0x3
	bge @8
	b @2
	@5:
	cmpwi r0, 0xa
	beq @9
	b @2
	@4:
	ori r0, r3, 0x4
	stw r0, 0x38(r31)
	@7:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 27, 27
	bne @10
	lfs f1, float_1_8041afa4(r2)
	li r0, 0x0
	lfs f0, float_500_8041afcc(r2)
	stfs f1, 0x80(r31)
	stfs f1, 0x84(r31)
	stw r0, 0x88(r31)
	stfs f0, 0x58(r31)
	@10:
	lwz r0, 0x38(r31)
	rlwinm. r0, r0, 0, 25, 25
	bne @11
	lwz r0, 0x4(r31)
	cmpwi r0, 0x7a
	beq @12
	bge @13
	cmpwi r0, 0x79
	bge @14
	b @12
	@13:
	cmpwi r0, 0x7d
	bge @12
	@14:
	li r3, 0x1e
	bl irand
	addi r3, r3, 0x2d
	lis r0, 0x4330
	xoris r4, r3, 0x8000
	stw r0, 0x70(r1)
	lfd f1, 0x68(r30)
	li r3, 0x64
	stw r4, 0x74(r1)
	lfd f0, 0x70(r1)
	fsubs f0, f0, f1
	stfs f0, 0x50(r31)
	bl irand
	cmpwi r3, 0x32
	bge @15
	li r3, 0x3c
	bl irand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x74(r1)
	lfd f3, 0x68(r30)
	stw r0, 0x70(r1)
	lfs f2, float_90_8041afd0(r2)
	lfd f0, 0x70(r1)
	lfs f1, 0x114(r28)
	fsubs f3, f0, f3
	lfs f0, float_30_8041afd4(r2)
	fadds f1, f2, f1
	fadds f1, f1, f3
	fsubs f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x78(r1)
	lwz r0, 0x7c(r1)
	stw r0, 0x54(r31)
	b @2
	@15:
	li r3, 0x3c
	bl irand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x7c(r1)
	lfd f3, 0x68(r30)
	stw r0, 0x78(r1)
	lfs f2, 0x114(r28)
	lfd f0, 0x78(r1)
	lfs f1, float_90_8041afd0(r2)
	fsubs f3, f0, f3
	lfs f0, float_30_8041afd4(r2)
	fsubs f1, f2, f1
	fadds f1, f1, f3
	fsubs f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x70(r1)
	lwz r0, 0x74(r1)
	stw r0, 0x54(r31)
	b @2
	@12:
	lfs f0, float_100_8041afc0(r2)
	li r3, 0x64
	stfs f0, 0x50(r31)
	bl irand
	cmpwi r3, 0x32
	bge @16
	li r3, 0x1e
	bl irand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x7c(r1)
	lfd f3, 0x68(r30)
	stw r0, 0x78(r1)
	lfs f2, float_90_8041afd0(r2)
	lfd f0, 0x78(r1)
	lfs f1, 0x114(r28)
	fsubs f3, f0, f3
	lfs f0, float_15_8041afb4(r2)
	fadds f1, f2, f1
	fadds f1, f1, f3
	fsubs f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x70(r1)
	lwz r0, 0x74(r1)
	stw r0, 0x54(r31)
	b @2
	@16:
	li r3, 0x1e
	bl irand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x7c(r1)
	lfd f3, 0x68(r30)
	stw r0, 0x78(r1)
	lfs f2, 0x114(r28)
	lfd f0, 0x78(r1)
	lfs f1, float_90_8041afd0(r2)
	fsubs f3, f0, f3
	lfs f0, float_15_8041afb4(r2)
	fsubs f1, f2, f1
	fadds f1, f1, f3
	fsubs f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x70(r1)
	lwz r0, 0x74(r1)
	stw r0, 0x54(r31)
	b @2
	@11:
	lwz r0, _move_dir_1090(r13)
	stw r0, 0x54(r31)
	lwz r3, _move_dir_1090(r13)
	addi r3, r3, 0x84
	cmpwi r3, 0x168
	stw r3, _move_dir_1090(r13)
	blt @17
	subi r0, r3, 0x168
	stw r0, _move_dir_1090(r13)
	@17:
	li r3, 0x1e
	bl irand
	addi r3, r3, 0x41
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	stw r0, 0x78(r1)
	lfd f2, 0x68(r30)
	stw r3, 0x7c(r1)
	lfs f0, float_0p67_8041afd8(r2)
	lfd f1, 0x78(r1)
	fsubs f1, f1, f2
	fmuls f0, f0, f1
	stfs f0, 0x50(r31)
	b @2
	@6:
	ori r0, r3, 0x8
	stw r0, 0x38(r31)
	@8:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 27, 27
	bne @18
	lfs f0, float_1_8041afa4(r2)
	li r0, 0x0
	stfs f0, 0x80(r31)
	stfs f0, 0x84(r31)
	stw r0, 0x88(r31)
	@18:
	lfs f0, float_0_8041af9c(r2)
	li r0, 0x0
	stfs f0, 0x50(r31)
	stw r0, 0x54(r31)
	stfs f0, 0x58(r31)
	b @2
	@9:
	lfs f2, float_1_8041afa4(r2)
	lfs f1, float_500_8041afcc(r2)
	stfs f2, 0x80(r31)
	lfs f0, float_0_8041af9c(r2)
	stfs f2, 0x84(r31)
	stw r4, 0x88(r31)
	stfs f1, 0x58(r31)
	stfs f0, 0x50(r31)
	stw r4, 0x54(r31)
	lwz r0, 0x38(r31)
	ori r0, r0, 0x20
	stw r0, 0x38(r31)
	lwz r0, 0x38(r31)
	ori r0, r0, 0x4
	stw r0, 0x38(r31)
	b @2
	@1:
	lwz r6, gp(r13)
	lis r3, 0x431c
	lis r4, 0x8000
	li r5, 0x0
	lwz r0, 0x38(r6)
	subi r3, r3, 0x217d
	lwz r6, 0x3c(r6)
	stw r6, 0x74(r31)
	stw r0, 0x70(r31)
	lwz r0, 0xf8(r4)
	lwz r7, 0x74(r31)
	srwi r0, r0, 2
	lwz r4, 0x6c(r31)
	mulhwu r0, r3, r0
	lwz r6, 0x70(r31)
	subfc r29, r4, r7
	lwz r3, 0x68(r31)
	subfe r28, r3, r6
	slwi r4, r29, 3
	srwi r26, r0, 15
	slwi r3, r28, 3
	rlwimi r3, r29, 3, 29, 31
	mr r6, r26
	bl __div2i
	bl __cvt_sll_flt
	lfs f0, float_1E06_8041afdc(r2)
	mr r6, r26
	lwz r25, 0x60(r31)
	li r5, 0x0
	fdivs f30, f1, f0
	lwz r24, 0x64(r31)
	slwi r3, r25, 3
	slwi r4, r24, 3
	rlwimi r3, r24, 3, 29, 31
	bl __div2i
	bl __cvt_sll_flt
	lfs f0, float_1E06_8041afdc(r2)
	addc r7, r24, r29
	adde r0, r25, r28
	mr r6, r26
	fdivs f29, f1, f0
	slwi r3, r0, 3
	slwi r4, r7, 3
	li r5, 0x0
	rlwimi r3, r7, 3, 29, 31
	bl __div2i
	bl __cvt_sll_flt
	lwz r3, 0x54(r31)
	lis r0, 0x4330
	lfs f0, float_1E06_8041afdc(r2)
	xoris r3, r3, 0x8000
	stw r0, 0x78(r1)
	lfd f2, 0x68(r30)
	fdivs f28, f1, f0
	stw r3, 0x7c(r1)
	lfs f3, float_6p2832_8041afe0(r2)
	lfd f1, 0x78(r1)
	lfs f0, float_360_8041afe4(r2)
	fsubs f1, f1, f2
	fmuls f1, f3, f1
	fdivs f1, f1, f0
	bl sin
	lwz r3, 0x54(r31)
	lis r0, 0x4330
	stw r0, 0x70(r1)
	frsp f1, f1
	xoris r0, r3, 0x8000
	lfs f0, 0x50(r31)
	stw r0, 0x74(r1)
	fmuls f3, f0, f1
	lfd f1, 0x68(r30)
	lfd f0, 0x70(r1)
	lfs f2, float_6p2832_8041afe0(r2)
	fsubs f1, f0, f1
	lfs f0, float_360_8041afe4(r2)
	fmuls f27, f30, f3
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl cos
	frsp f0, f1
	lwz r3, 0x38(r31)
	lfs f1, 0x50(r31)
	rlwinm. r0, r3, 0, 16, 16
	fneg f0, f0
	fmuls f0, f1, f0
	fmuls f2, f30, f0
	beq @19
	lfs f2, float_0_8041af9c(r2)
	@19:
	fmuls f31, f28, f28
	lfs f3, float_neg980_8041afe8(r2)
	lfs f1, 0x84(r31)
	rlwinm. r0, r3, 0, 29, 29
	fmuls f1, f3, f1
	lfs f3, 0x58(r31)
	fnmsubs f0, f29, f29, f31
	fmuls f0, f1, f0
	fmadds f29, f3, f30, f0
	beq @20
	lwz r0, 0x8c(r31)
	cmpwi r0, 0x0
	bne @21
	lfs f0, float_0_8041af9c(r2)
	fcmpo cr0, f29, f0
	bge @20
	@21:
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x38(r31)
	@20:
	lwz r3, 0x38(r31)
	rlwinm. r0, r3, 0, 28, 28
	beq @22
	lwz r0, 0x8c(r31)
	cmpwi r0, 0x0
	beq @22
	rlwinm r0, r3, 0, 29, 27
	stw r0, 0x38(r31)
	@22:
	lwz r0, 0x38(r31)
	rlwinm. r0, r0, 0, 26, 26
	beq @23
	lfs f0, float_0_8041af9c(r2)
	fcmpo cr0, f29, f0
	bge @23
	lfs f4, float_16_8041afc8(r2)
	li r3, 0x1
	lfs f1, 0x3c(r31)
	li r4, 0x3
	fmr f5, f4
	lfs f2, 0x40(r31)
	lfs f3, 0x44(r31)
	li r5, 0x1e
	bl effStardustEntry
	lwz r4, gp(r13)
	lis r3, work@ha
	addi r26, r3, work@l
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @24
	addi r26, r26, 0x1c
	@24:
	lwz r28, 0x4(r26)
	li r27, 0x0
	b @25
	@26:
	addi r3, r28, 0xc
	addi r4, r31, 0xc
	bl strcmp
	cmpwi r3, 0x0
	bne @27
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	bne @28
	lwz r3, 0x4(r28)
	cmpwi r3, 0xf0
	blt @28
	cmpwi r3, 0x153
	bge @28
	lhz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 23, 23
	beq @28
	bl pouchArriveBadge
	@28:
	lwz r0, 0x4(r28)
	cmpwi r0, 0x79
	bge @29
	cmpwi r0, 0x72
	bge @30
	b @29
	@30:
	lwz r3, 0x1c(r28)
	bl effSoftDelete
	b @31
	@29:
	addi r3, r28, 0xc
	bl iconDelete
	@31:
	lhz r0, 0x0(r28)
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r28)
	@27:
	addi r27, r27, 0x1
	addi r28, r28, 0x98
	@25:
	lwz r0, 0x0(r26)
	cmpw r27, r0
	blt @26
	b @32
	@23:
	lwz r0, 0x54(r31)
	fmr f1, f27
	mr r3, r31
	addi r4, r1, 0x48
	stw r0, 0x40(r1)
	addi r5, r1, 0x44
	addi r6, r1, 0x40
	bl itemHitCheckSide
	lfs f0, 0x48(r1)
	cmplwi r3, 0x0
	stfs f0, 0x3c(r31)
	lfs f0, 0x44(r1)
	stfs f0, 0x44(r31)
	lwz r0, 0x40(r1)
	stw r0, 0x54(r31)
	beq @33
	lfs f1, 0x50(r31)
	lfs f0, float_0p25_8041afec(r2)
	fmuls f0, f1, f0
	stfs f0, 0x50(r31)
	@33:
	lwz r0, 0x38(r31)
	rlwinm. r0, r0, 0, 26, 26
	bne @34
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 20, 20
	bne @34
	lfs f4, float_0_8041af9c(r2)
	fcmpo cr0, f29, f4
	cror eq, lt, eq
	bne @35
	li r3, 0x0
	b @36
	@35:
	fabs f2, f29
	lfd f0, 0x48(r30)
	lfs f7, float_20_8041afa0(r2)
	fmr f6, f4
	lfs f1, 0x3c(r31)
	addi r4, r1, 0x24
	fadd f0, f0, f2
	lfs f2, 0x40(r31)
	lfs f3, 0x44(r31)
	addi r5, r1, 0x28
	fadds f2, f7, f2
	lfs f5, float_1_8041afa4(r2)
	frsp f0, f0
	addi r6, r1, 0x2c
	addi r7, r1, 0x30
	addi r8, r1, 0x34
	addi r9, r1, 0x38
	addi r10, r1, 0x3c
	stfs f0, 0x30(r1)
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @37
	lfs f2, 0x28(r1)
	lfs f1, float_20_8041afa0(r2)
	lfs f0, float_4_8041afa8(r2)
	fsubs f1, f2, f1
	fsubs f0, f1, f0
	stfs f0, 0x40(r31)
	b @36
	@37:
	fabs f3, f29
	lfd f0, 0x48(r30)
	lfs f4, float_0_8041af9c(r2)
	addi r4, r1, 0x24
	lfs f1, 0x3c(r31)
	addi r5, r1, 0x28
	fadd f0, f0, f3
	lfs f2, 0x40(r31)
	lfs f3, 0x44(r31)
	fmr f6, f4
	lfs f5, float_1_8041afa4(r2)
	addi r6, r1, 0x2c
	frsp f0, f0
	addi r7, r1, 0x30
	addi r8, r1, 0x34
	addi r9, r1, 0x38
	addi r10, r1, 0x3c
	li r3, 0x0
	stfs f0, 0x30(r1)
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @38
	lfs f1, 0x28(r1)
	lfs f0, float_20_8041afa0(r2)
	fsubs f0, f1, f0
	stfs f0, 0x40(r31)
	b @36
	@38:
	li r3, 0x0
	@36:
	cmplwi r3, 0x0
	beq @34
	lfs f1, 0x58(r31)
	li r0, 0x0
	lfs f0, float_0p25_8041afec(r2)
	fneg f1, f1
	lfs f29, float_0_8041af9c(r2)
	fmuls f0, f1, f0
	stfs f0, 0x58(r31)
	stw r0, 0x64(r31)
	stw r0, 0x60(r31)
	lwz r0, 0x70(r31)
	lwz r3, 0x74(r31)
	stw r3, 0x6c(r31)
	stw r0, 0x68(r31)
	@34:
	lwz r0, 0x38(r31)
	rlwinm. r0, r0, 0, 11, 11
	beq @39
	lfs f1, 0x40(r31)
	lfs f0, float_neg1000_8041aff0(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @39
	li r0, 0x7
	li r3, 0x0
	sth r0, 0x24(r31)
	sth r3, 0x26(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x38(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x38(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 18, 16
	stw r0, 0x38(r31)
	lwz r0, 0x4(r31)
	cmpwi r0, 0x1
	blt @40
	cmpwi r0, 0x79
	bge @40
	stw r3, 0x7c(r31)
	stw r3, 0x78(r31)
	b @41
	@40:
	cmpwi r0, 0xf0
	blt @42
	cmpwi r0, 0x153
	bge @42
	li r0, 0x0
	stw r0, 0x7c(r31)
	stw r0, 0x78(r31)
	b @41
	@42:
	li r3, 0x4e20
	li r0, 0x0
	stw r3, 0x7c(r31)
	stw r0, 0x78(r31)
	@41:
	lwz r0, 0x38(r31)
	oris r0, r0, 0x1
	stw r0, 0x38(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 20, 18
	stw r0, 0x38(r31)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x100
	sth r0, 0x0(r31)
	b @2
	@39:
	lfs f4, float_0_8041af9c(r2)
	fcmpo cr0, f29, f4
	cror eq, gt, eq
	bne @43
	lfs f0, 0x40(r31)
	li r26, 0x0
	fadds f0, f0, f29
	stfs f0, 0x40(r31)
	b @44
	@43:
	lwz r0, 0x38(r31)
	rlwinm. r0, r0, 0, 11, 11
	beq @45
	lfs f0, 0x40(r31)
	li r26, 0x0
	fadds f0, f0, f29
	stfs f0, 0x40(r31)
	b @44
	@45:
	fabs f2, f29
	lfd f0, 0x48(r30)
	lfs f7, float_20_8041afa0(r2)
	fmr f6, f4
	lfs f1, 0x3c(r31)
	addi r4, r1, 0x8
	fadd f0, f0, f2
	lfs f2, 0x40(r31)
	lfs f3, 0x44(r31)
	addi r5, r1, 0xc
	fadds f2, f7, f2
	lfs f5, float_neg1_8041afac(r2)
	frsp f0, f0
	addi r6, r1, 0x10
	addi r7, r1, 0x14
	addi r8, r1, 0x18
	addi r9, r1, 0x1c
	addi r10, r1, 0x20
	stfs f0, 0x14(r1)
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @46
	lfs f0, 0xc(r1)
	mr r26, r3
	stfs f0, 0x40(r31)
	b @44
	@46:
	lfs f0, 0x40(r31)
	li r26, 0x0
	fadds f0, f0, f29
	stfs f0, 0x40(r31)
	@44:
	cmplwi r26, 0x0
	beq @47
	mr r3, r26
	bl hitGetAttr
	rlwinm. r0, r3, 0, 21, 22
	beq @48
	lwz r0, 0x38(r31)
	addi r4, r1, 0x58
	li r3, 0x194
	oris r0, r0, 0x10
	stw r0, 0x38(r31)
	lwz r6, 0x24(r30)
	lwz r5, 0x28(r30)
	lwz r0, 0x2c(r30)
	stw r6, 0x58(r1)
	stw r5, 0x5c(r1)
	stw r0, 0x60(r1)
	lfs f0, 0x3c(r31)
	stfs f0, 0x58(r1)
	lfs f0, 0x40(r31)
	stfs f0, 0x5c(r1)
	lfs f0, 0x44(r31)
	stfs f0, 0x60(r1)
	bl psndSFXOn_3D
	lfs f1, 0x3c(r31)
	li r3, 0x0
	lfs f2, 0x40(r31)
	lfs f3, 0x44(r31)
	lfs f4, float_0p7_8041aff4(r2)
	bl effSplashEntry
	lhz r0, 0x0(r31)
	ori r0, r0, 0x2
	sth r0, 0x0(r31)
	b @47
	@48:
	lwz r4, 0x8c(r31)
	mr r3, r26
	addi r0, r4, 0x1
	stw r0, 0x8c(r31)
	bl hitGetAttr
	clrrwi. r0, r3, 31
	bne @49
	lwz r3, 0x88(r31)
	cmpwi r3, 0x0
	beq @49
	lwz r0, 0x8c(r31)
	cmpw r0, r3
	blt @49
	li r3, 0x1
	li r0, 0x0
	sth r3, 0x24(r31)
	sth r0, 0x26(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x38(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x38(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 18, 16
	stw r0, 0x38(r31)
	b @2
	@49:
	lwz r4, 0x30(r30)
	lwz r3, 0x34(r30)
	lwz r0, 0x38(r30)
	stw r4, 0x4c(r1)
	lfs f0, 0x3c(r31)
	stw r3, 0x50(r1)
	lfs f1, 0x40(r31)
	stfs f0, 0x4c(r1)
	lfs f0, 0x44(r31)
	stw r0, 0x54(r1)
	lwz r4, 0x4c(r1)
	stfs f1, 0x50(r1)
	stfs f0, 0x54(r1)
	lwz r3, 0x50(r1)
	lwz r0, 0x54(r1)
	stw r4, 0x64(r1)
	stw r3, 0x68(r1)
	stw r0, 0x6c(r1)
	lwz r0, 0x4(r31)
	cmpwi r0, 0x7b
	beq @50
	bge @51
	cmpwi r0, 0x79
	beq @52
	bge @53
	cmpwi r0, 0x72
	bge @54
	b @55
	@51:
	cmpwi r0, 0x7d
	beq @56
	bge @55
	b @57
	@52:
	addi r3, r30, 0xbc
	addi r4, r1, 0x64
	bl psndSFXOn_3D
	b @58
	@53:
	addi r3, r30, 0xd0
	addi r4, r1, 0x64
	bl psndSFXOn_3D
	b @58
	@50:
	addi r3, r30, 0xec
	addi r4, r1, 0x64
	bl psndSFXOn_3D
	b @58
	@57:
	addi r3, r30, 0x100
	addi r4, r1, 0x64
	bl psndSFXOn_3D
	b @58
	@56:
	addi r3, r30, 0x114
	addi r4, r1, 0x64
	bl psndSFXOn_3D
	b @58
	@54:
	addi r3, r30, 0x12c
	addi r4, r1, 0x64
	bl psndSFXOn_3D
	b @58
	@55:
	cmpwi r0, 0xf0
	blt @59
	cmpwi r0, 0x153
	bge @59
	addi r3, r30, 0x144
	addi r4, r1, 0x64
	bl psndSFXOn_3D
	b @58
	@59:
	addi r3, r30, 0x158
	addi r4, r1, 0x64
	bl psndSFXOn_3D
	@58:
	lhz r0, 0x0(r31)
	li r24, 0x0
	rlwinm. r0, r0, 0, 24, 24
	beq @60
	lfs f1, float_0_8041af9c(r2)
	lfs f0, 0x58(r31)
	fcmpu cr0, f1, f0
	beq @60
	li r0, 0x1
	b @61
	@60:
	mr r3, r26
	bl hitGetAttr
	clrrwi. r0, r3, 31
	beq @62
	lfs f1, float_0_8041af9c(r2)
	lfs f0, 0x58(r31)
	fcmpu cr0, f1, f0
	beq @62
	mr r3, r26
	bl mobjHitObjPtrToPtr
	lbz r0, 0x3c(r27)
	cmpwi r0, 0x2
	bne @63
	li r0, 0x0
	b @61
	@63:
	cmplwi r3, 0x0
	beq @62
	addi r3, r3, 0x15
	addi r4, r30, 0x16c
	bl strcmp
	cmpwi r3, 0x0
	beq @62
	li r0, 0x1
	li r24, 0x1
	b @61
	@62:
	li r0, 0x0
	@61:
	cmpwi r0, 0x0
	bne @64
	fadds f0, f28, f30
	lfs f2, float_neg980_8041afe8(r2)
	lfs f1, 0x84(r31)
	lfs f3, 0x58(r31)
	fmuls f0, f0, f0
	lfs f4, 0x80(r31)
	fmuls f1, f2, f1
	lfs f2, float_0p7_8041aff4(r2)
	fsubs f0, f0, f31
	fmuls f0, f1, f0
	fmadds f0, f3, f30, f0
	fneg f0, f0
	fdivs f0, f0, f30
	fmuls f0, f4, f0
	fmuls f0, f2, f0
	stfs f0, 0x58(r31)
	@64:
	lfs f1, float_neg980_8041afe8(r2)
	cmpwi r24, 0x0
	lfs f0, 0x84(r31)
	lfs f2, 0x58(r31)
	fmuls f1, f1, f0
	lfs f3, float_0p5_8041afb8(r2)
	fdivs f0, f2, f1
	fmuls f0, f3, f0
	fabs f0, f0
	frsp f3, f0
	fmuls f0, f1, f3
	fmuls f0, f3, f0
	fmadds f1, f2, f3, f0
	bne @65
	lfs f0, float_8_8041aff8(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @65
	li r3, 0x1
	li r0, 0x0
	sth r3, 0x24(r31)
	sth r0, 0x26(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x38(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x38(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 18, 16
	stw r0, 0x38(r31)
	@65:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 22, 22
	beq @66
	lwz r0, 0x8c(r31)
	cmpwi r0, 0x1
	bgt @66
	lwz r0, 0x90(r31)
	stw r0, 0x54(r31)
	lfs f0, 0x94(r31)
	stfs f0, 0x50(r31)
	lhz r0, 0x0(r31)
	rlwinm r0, r0, 0, 23, 21
	sth r0, 0x0(r31)
	@66:
	li r0, 0x0
	stw r0, 0x64(r31)
	stw r0, 0x60(r31)
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x6c(r31)
	stw r0, 0x68(r31)
	b @2
	@47:
	lwz r0, 0x64(r31)
	lwz r3, 0x60(r31)
	addc r0, r0, r29
	stw r0, 0x64(r31)
	adde r0, r3, r28
	stw r0, 0x60(r31)
	lwz r0, 0x70(r31)
	lwz r3, 0x74(r31)
	stw r3, 0x6c(r31)
	stw r0, 0x68(r31)
	@2:
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x38(r31)
	@32:
	psq_l f31, 0xe8(r1), 0, 0
	lfd f31, 0xe0(r1)
	psq_l f30, 0xd8(r1), 0, 0
	lfd f30, 0xd0(r1)
	psq_l f29, 0xc8(r1), 0, 0
	lfd f29, 0xc0(r1)
	psq_l f28, 0xb8(r1), 0, 0
	lfd f28, 0xb0(r1)
	psq_l f27, 0xa8(r1), 0, 0
	lfd f27, 0xa0(r1)
	lmw r24, 0x80(r1)
	lwz r0, 0xf4(r1)
	mtlr r0
	addi r1, r1, 0xf0
	blr
}

asm void itemseq_GetItem(ItemEntry* entry) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	lis r4, work@ha
	stw r0, 0x74(r1)
	stmw r26, 0x58(r1)
	addi r29, r4, work@l
	lis r4, vec3_802cabe0@ha
	mr r31, r3
	addi r28, r4, vec3_802cabe0@l
	lwz r5, gp(r13)
	lwz r0, 0x14(r5)
	cmpwi r0, 0x0
	beq @1
	addi r29, r29, 0x1c
	@1:
	bl marioGetPtr
	lhz r0, 0x26(r31)
	mr r30, r3
	cmplwi r0, 0x9
	bgt @2
	lis r3, jumptable_80312418@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_80312418@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@3:
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 16, 14
	stw r0, 0x38(r31)
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 23, 23
	beq @4
	lwz r0, 0x38(r31)
	oris r0, r0, 0x400
	stw r0, 0x38(r31)
	b @5
	@4:
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 6, 4
	stw r0, 0x38(r31)
	@5:
	lhz r0, 0x0(r31)
	rlwinm r0, r0, 0, 24, 22
	sth r0, 0x0(r31)
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 29, 29
	beq @6
	lwz r3, 0x4(r31)
	bl pouchGetItem
	cmpwi r3, 0x0
	bne @7
	li r3, 0x0
	b @8
	@7:
	lhz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 26, 26
	beq @9
	lwz r3, 0x8(r31)
	bl swSet
	b @10
	@9:
	rlwinm. r0, r3, 0, 25, 25
	beq @10
	lwz r3, 0x8(r31)
	bl _swSet
	@10:
	lwz r3, 0x20(r31)
	cmplwi r3, 0x0
	beq @11
	li r4, 0x0
	li r5, 0x20
	bl evtEntry
	lfs f1, float_1024_8041affc(r2)
	lfs f0, 0x3c(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x38(r1)
	lwz r4, 0x3c(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0x9c(r3)
	lfs f0, 0x40(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x40(r1)
	lwz r4, 0x44(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa0(r3)
	lfs f0, 0x44(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x48(r1)
	lwz r4, 0x4c(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa4(r3)
	@11:
	lwz r0, 0x38(r31)
	li r3, 0x1
	ori r0, r0, 0x1
	stw r0, 0x38(r31)
	@8:
	cmpwi r3, 0x0
	beq @12
	li r0, 0x0
	stw r0, 0x7c(r31)
	stw r0, 0x78(r31)
	lwz r4, 0x3c(r28)
	lwz r3, 0x40(r28)
	lwz r0, 0x44(r28)
	stw r4, 0x2c(r1)
	lfs f1, 0x3c(r31)
	stw r3, 0x30(r1)
	lfs f2, 0x40(r31)
	stfs f1, 0x2c(r1)
	lfs f3, 0x44(r31)
	stw r0, 0x34(r1)
	lwz r4, 0x2c(r1)
	stfs f2, 0x30(r1)
	stfs f3, 0x34(r1)
	lwz r3, 0x30(r1)
	lwz r0, 0x34(r1)
	stw r4, 0x20(r1)
	stw r3, 0x24(r1)
	stw r0, 0x28(r1)
	lwz r0, 0x4(r31)
	cmpwi r0, 0x7b
	beq @13
	bge @14
	cmpwi r0, 0x79
	beq @15
	bge @16
	b @17
	@14:
	cmpwi r0, 0x7d
	beq @17
	bge @17
	b @18
	@15:
	lfs f0, float_35_8041afc4(r2)
	li r3, 0x1
	lfs f4, float_16_8041afc8(r2)
	li r4, 0x3
	fadds f2, f0, f2
	li r5, 0x1e
	fmr f5, f4
	bl effStardustEntry
	addi r3, r28, 0x70
	addi r4, r1, 0x20
	bl psndSFXOn_3D
	b @17
	@16:
	lfs f0, float_35_8041afc4(r2)
	li r3, 0x1
	lfs f4, float_16_8041afc8(r2)
	li r4, 0x3
	fadds f2, f0, f2
	li r5, 0x1e
	fmr f5, f4
	bl effStardustEntry
	addi r3, r28, 0x80
	addi r4, r1, 0x20
	bl psndSFXOn_3D
	b @17
	@13:
	addi r3, r28, 0x9c
	addi r4, r1, 0x20
	bl psndSFXOn_3D
	b @17
	@18:
	addi r3, r28, 0xac
	addi r4, r1, 0x20
	bl psndSFXOn_3D
	@17:
	lwz r4, gp(r13)
	lis r3, work@ha
	addi r26, r3, work@l
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @19
	addi r26, r26, 0x1c
	@19:
	lwz r28, 0x4(r26)
	li r27, 0x0
	b @20
	@21:
	addi r3, r28, 0xc
	addi r4, r31, 0xc
	bl strcmp
	cmpwi r3, 0x0
	bne @22
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	bne @23
	lwz r3, 0x4(r28)
	cmpwi r3, 0xf0
	blt @23
	cmpwi r3, 0x153
	bge @23
	lhz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 23, 23
	beq @23
	bl pouchArriveBadge
	@23:
	lwz r0, 0x4(r28)
	cmpwi r0, 0x79
	bge @24
	cmpwi r0, 0x72
	bge @25
	b @24
	@25:
	lwz r3, 0x1c(r28)
	bl effSoftDelete
	b @26
	@24:
	addi r3, r28, 0xc
	bl iconDelete
	@26:
	lhz r0, 0x0(r28)
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r28)
	@22:
	addi r27, r27, 0x1
	addi r28, r28, 0x98
	@20:
	lwz r0, 0x0(r26)
	cmpw r27, r0
	blt @21
	b @2
	@12:
	li r3, 0x4
	li r0, 0x0
	sth r3, 0x24(r31)
	sth r0, 0x26(r31)
	b @2
	@6:
	li r3, 0x1
	li r0, 0x0
	sth r3, 0x26(r31)
	li r3, 0x8
	stw r0, 0x7c(r31)
	stw r0, 0x78(r31)
	bl camGetPtr
	lhz r0, 0x0(r3)
	ori r0, r0, 0x200
	sth r0, 0x0(r3)
	bl marioKeyOff
	li r3, 0x2
	bl marioStSystemLevel
	li r3, 0x80
	bl psndSetFlag
	lfs f0, float_0_8041af9c(r2)
	stfs f0, 0x174(r30)
	stfs f0, 0x17c(r30)
	stfs f0, 0x180(r30)
	stfs f0, 0x18c(r30)
	lwz r0, 0x4(r31)
	cmpwi r0, 0x7
	beq @27
	cmpwi r0, 0x8
	beq @27
	cmpwi r0, 0xa
	beq @27
	cmpwi r0, 0xb
	bne @28
	@27:
	lwz r0, 0x38(r31)
	ori r0, r0, 0x2000
	stw r0, 0x38(r31)
	@28:
	lhz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 19, 19
	beq @29
	rlwinm. r0, r3, 0, 17, 17
	beq @30
	@29:
	bl marioChkItemGetMotion
	cmpwi r3, 0x0
	bne @30
	lhz r3, 0x2e(r30)
	cmplwi r3, 0x5
	beq @31
	subi r0, r3, 0x6
	clrlwi r0, r0, 16
	cmplwi r0, 0x2
	ble @31
	cmplwi r3, 0xf
	beq @31
	cmplwi r3, 0xe
	bne @2
	@31:
	li r0, 0x8
	sth r0, 0x26(r31)
	b @2
	@30:
	li r0, 0x2
	sth r0, 0x26(r31)
	bl marioChgGetItemMotion
	lfs f2, float_50_8041b000(r2)
	li r27, 0x7
	lfs f1, 0x90(r30)
	li r26, -0x1
	lfs f3, 0x94(r30)
	lfs f0, 0x8c(r30)
	fadds f1, f2, f1
	stfs f0, 0x3c(r31)
	stfs f1, 0x40(r31)
	stfs f3, 0x44(r31)
	lwz r0, 0x4(r31)
	cmpwi r0, 0x57
	bne @32
	li r27, 0x4
	li r26, -0x1
	b @33
	@32:
	cmpwi r0, 0x7d
	bne @34
	li r27, 0x8
	li r26, 0x0
	b @33
	@34:
	cmpwi r0, 0xc
	bge @35
	li r27, 0x3
	li r26, 0x3
	b @33
	@35:
	cmpwi r0, 0x72
	bge @36
	li r27, 0x6
	li r26, 0x1
	b @33
	@36:
	cmpwi r0, 0x79
	bge @37
	li r27, 0x0
	li r26, -0x1
	b @33
	@37:
	cmpwi r0, 0xec
	bge @38
	li r27, 0x7
	li r26, -0x1
	b @33
	@38:
	cmpwi r0, 0x153
	bge @33
	li r27, 0x5
	li r26, 0x2
	@33:
	lfs f2, float_62_8041b004(r2)
	mr r3, r27
	lfs f0, 0x90(r30)
	lfs f1, 0x8c(r30)
	fadds f2, f2, f0
	lfs f3, 0x94(r30)
	bl effItemGetEntry
	stw r3, 0xc(r29)
	lwz r0, 0x38(r31)
	rlwinm. r0, r0, 0, 18, 18
	beq @39
	lwz r5, 0xc(r29)
	li r0, 0x5
	addi r3, r31, 0xc
	li r4, 0x200
	lwz r5, 0xc(r5)
	stw r0, 0x38(r5)
	bl iconFlagOn
	li r3, 0x7
	bl marioSetCamId
	b @40
	@39:
	lwz r5, 0xc(r29)
	li r0, 0x5
	addi r3, r31, 0xc
	li r4, 0x100
	lwz r5, 0xc(r5)
	stw r0, 0x38(r5)
	bl iconFlagOn
	cmpwi r27, 0x0
	beq @41
	cmpwi r27, 0x3
	bne @40
	@41:
	li r3, 0x5
	bl marioSetCamId
	@40:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @42
	li r3, 0x0
	bl psndBGMChkSilent
	cmplwi r3, 0x0
	beq @43
	lhz r0, 0x0(r31)
	ori r0, r0, 0x8
	sth r0, 0x0(r31)
	@43:
	cmpwi r26, 0x2
	beq @44
	bge @45
	cmpwi r26, 0x0
	beq @46
	bge @47
	b @48
	@45:
	cmpwi r26, 0x4
	bge @48
	b @49
	@46:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	bne @50
	li r3, 0x3800
	bl psndBGMOff
	@50:
	addi r4, r28, 0x180
	li r3, 0x211
	bl psndBGMOn
	b @42
	@47:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	bne @51
	li r3, 0x3800
	bl psndBGMOff
	@51:
	addi r4, r28, 0x198
	li r3, 0x211
	bl psndBGMOn
	b @42
	@44:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	bne @52
	li r3, 0x3800
	bl psndBGMOff
	@52:
	addi r4, r28, 0x1ac
	li r3, 0x211
	bl psndBGMOn
	b @42
	@49:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	bne @53
	li r3, 0x3800
	bl psndBGMOff
	@53:
	addi r4, r28, 0x1c0
	li r3, 0x211
	bl psndBGMOn
	b @42
	@48:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	bne @54
	li r3, 0x3800
	bl psndBGMOff
	@54:
	addi r4, r28, 0x1dc
	li r3, 0x211
	bl psndBGMOn
	@42:
	cmpwi r27, 0x8
	bne @55
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x1a2
	bl evtGetValue
	mr r5, r3
	lis r3, 0xf5de
	addi r4, r3, 0x1a2
	li r3, 0x0
	addi r5, r5, 0x1
	bl evtSetValue
	@55:
	lhz r0, 0x0(r31)
	rlwinm r0, r0, 0, 19, 17
	sth r0, 0x0(r31)
	lwz r4, 0x3c(r28)
	lwz r3, 0x40(r28)
	lwz r0, 0x44(r28)
	stw r4, 0x14(r1)
	lfs f1, 0x3c(r31)
	stw r3, 0x18(r1)
	lfs f2, 0x40(r31)
	stfs f1, 0x14(r1)
	lfs f3, 0x44(r31)
	stw r0, 0x1c(r1)
	lwz r4, 0x14(r1)
	stfs f2, 0x18(r1)
	stfs f3, 0x1c(r1)
	lwz r3, 0x18(r1)
	lwz r0, 0x1c(r1)
	stw r4, 0x8(r1)
	stw r3, 0xc(r1)
	stw r0, 0x10(r1)
	lwz r0, 0x4(r31)
	cmpwi r0, 0x7b
	beq @56
	bge @57
	cmpwi r0, 0x79
	beq @58
	bge @59
	b @60
	@57:
	cmpwi r0, 0x7d
	beq @60
	bge @60
	b @61
	@58:
	lfs f0, float_35_8041afc4(r2)
	li r3, 0x1
	lfs f4, float_16_8041afc8(r2)
	li r4, 0x3
	fadds f2, f0, f2
	li r5, 0x1e
	fmr f5, f4
	bl effStardustEntry
	addi r3, r28, 0x70
	addi r4, r1, 0x8
	bl psndSFXOn_3D
	b @60
	@59:
	lfs f0, float_35_8041afc4(r2)
	li r3, 0x1
	lfs f4, float_16_8041afc8(r2)
	li r4, 0x3
	fadds f2, f0, f2
	li r5, 0x1e
	fmr f5, f4
	bl effStardustEntry
	addi r3, r28, 0x80
	addi r4, r1, 0x8
	bl psndSFXOn_3D
	b @60
	@56:
	addi r3, r28, 0x9c
	addi r4, r1, 0x8
	bl psndSFXOn_3D
	b @60
	@61:
	addi r3, r28, 0xac
	addi r4, r1, 0x8
	bl psndSFXOn_3D
	@60:
	lis r3, itemdrv_window_desc@ha
	addi r3, r3, itemdrv_window_desc@l
	bl winMgrEntry
	stw r3, 0x28(r31)
	lwz r3, 0x28(r31)
	bl winMgrOpen
	lwz r3, 0x28(r31)
	mr r4, r31
	bl winMgrSetParam
	lwz r0, 0x38(r31)
	rlwinm. r0, r0, 0, 18, 18
	bne @62
	lis r3, itemdrv_window_desc@ha
	addi r3, r3, itemdrv_window_desc@l
	addi r3, r3, 0x28
	bl winMgrEntry
	stw r3, 0x2c(r31)
	lwz r3, 0x2c(r31)
	bl winMgrOpen
	lwz r3, 0x2c(r31)
	mr r4, r31
	bl winMgrSetParam
	@62:
	lwz r3, 0x4(r31)
	bl pouchGetItem
	cmpwi r3, 0x0
	bne @63
	li r3, 0x0
	b @64
	@63:
	lhz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 26, 26
	beq @65
	lwz r3, 0x8(r31)
	bl swSet
	b @66
	@65:
	rlwinm. r0, r3, 0, 25, 25
	beq @66
	lwz r3, 0x8(r31)
	bl _swSet
	@66:
	lwz r3, 0x20(r31)
	cmplwi r3, 0x0
	beq @67
	li r4, 0x0
	li r5, 0x20
	bl evtEntry
	lfs f1, float_1024_8041affc(r2)
	lfs f0, 0x3c(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x48(r1)
	lwz r4, 0x4c(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0x9c(r3)
	lfs f0, 0x40(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x40(r1)
	lwz r4, 0x44(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa0(r3)
	lfs f0, 0x44(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x38(r1)
	lwz r4, 0x3c(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa4(r3)
	@67:
	lwz r0, 0x38(r31)
	li r3, 0x1
	ori r0, r0, 0x1
	stw r0, 0x38(r31)
	@64:
	cmpwi r3, 0x0
	bne @68
	lis r3, itemdrv_window_desc@ha
	addi r3, r3, itemdrv_window_desc@l
	addi r3, r3, 0x50
	bl winMgrEntry
	stw r3, 0x30(r31)
	lwz r3, 0x30(r31)
	bl winMgrOpen
	lwz r3, 0x30(r31)
	mr r4, r31
	bl winMgrSetParam
	@68:
	lwz r0, 0x4(r31)
	cmpwi r0, 0x49
	bne @69
	addi r3, r31, 0xc
	li r4, 0x114
	bl iconChange
	@69:
	lwz r0, 0x1c(r31)
	cmplwi r0, 0x0
	bne @2
	addi r3, r31, 0xc
	bl iconNameToPtr
	lhz r0, 0x0(r3)
	ori r0, r0, 0x80
	sth r0, 0x0(r3)
	b @2
	@70:
	lwz r0, 0x38(r31)
	rlwinm. r0, r0, 0, 18, 18
	bne @71
	bl marioCtrlOff
	lwz r0, 0x38(r31)
	oris r0, r0, 0x100
	stw r0, 0x38(r31)
	@71:
	li r0, 0x3
	sth r0, 0x26(r31)
	@72:
	lhz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 16, 16
	bne @73
	rlwinm. r0, r3, 0, 18, 18
	bne @73
	li r3, 0x1
	bl psndBGMChk
	cmpwi r3, 0x0
	beq @73
	lhz r0, 0x0(r31)
	li r3, 0x201
	ori r0, r0, 0x2000
	sth r0, 0x0(r31)
	bl psndBGMOff
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	bne @73
	li r3, 0xa0
	li r4, 0x0
	bl psndBGMOn
	@73:
	lwz r3, 0x28(r31)
	bl winMgrAction
	cmpwi r3, 0x0
	bne @2
	li r3, 0x0
	bl keyGetButtonTrg
	rlwinm. r0, r3, 0, 22, 23
	beq @2
	lwz r3, 0x28(r31)
	bl winMgrCloseAutoDelete
	lwz r0, 0x38(r31)
	rlwinm. r0, r0, 0, 18, 18
	bne @74
	lwz r3, 0x2c(r31)
	bl winMgrCloseAutoDelete
	@74:
	lhz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 16, 16
	bne @75
	rlwinm. r0, r3, 0, 18, 18
	bne @75
	li r3, 0x201
	bl psndBGMOff
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	bne @75
	li r3, 0xa0
	li r4, 0x0
	bl psndBGMOn
	@75:
	lwz r0, 0x38(r31)
	rlwinm. r0, r0, 0, 18, 18
	beq @76
	li r0, 0x6
	sth r0, 0x26(r31)
	b @2
	@76:
	lwz r0, 0x4(r31)
	cmpwi r0, 0x79
	blt @77
	cmpwi r0, 0xec
	bge @77
	cmpwi r0, 0x7d
	beq @77
	li r3, 0xeb
	bl swGet
	cmpwi r3, 0x0
	bne @77
	lwz r3, gp(r13)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 19, 19
	bne @77
	li r3, 0xeb
	bl swSet
	li r0, 0x4
	addi r3, r28, 0x1f0
	sth r0, 0x26(r31)
	bl msgSearch
	li r4, 0x0
	li r5, 0x0
	bl msgWindow_Entry
	stw r3, 0x18(r29)
	b @2
	@77:
	lwz r3, 0xc(r29)
	bl effSoftDelete
	li r3, 0x4
	bl marioSetCamId
	addi r3, r31, 0xc
	li r4, 0x100
	bl iconFlagOff
	lwz r0, 0x4(r31)
	cmpwi r0, 0x49
	bne @78
	addi r3, r31, 0xc
	li r4, 0x115
	bl iconChange
	@78:
	lwz r0, 0x1c(r31)
	cmplwi r0, 0x0
	bne @79
	addi r3, r31, 0xc
	bl iconNameToPtr
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 25, 23
	sth r0, 0x0(r3)
	@79:
	lwz r0, 0x38(r31)
	clrlwi. r0, r0, 31
	beq @80
	li r3, 0x0
	bl marioStSystemLevel
	li r3, 0x80
	bl psndClearFlag
	lwz r3, 0x38(r31)
	rlwinm. r0, r3, 0, 7, 7
	beq @81
	rlwinm r0, r3, 0, 8, 6
	stw r0, 0x38(r31)
	bl marioCtrlOn
	@81:
	bl marioKeyOn
	bl marioChgStayMotion
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	lis r4, work@ha
	addi r26, r4, work@l
	rlwinm r0, r0, 0, 23, 21
	sth r0, 0x0(r3)
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq @82
	addi r26, r26, 0x1c
	@82:
	lwz r28, 0x4(r26)
	li r27, 0x0
	b @83
	@84:
	addi r3, r28, 0xc
	addi r4, r31, 0xc
	bl strcmp
	cmpwi r3, 0x0
	bne @85
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	bne @86
	lwz r3, 0x4(r28)
	cmpwi r3, 0xf0
	blt @86
	cmpwi r3, 0x153
	bge @86
	lhz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 23, 23
	beq @86
	bl pouchArriveBadge
	@86:
	lwz r0, 0x4(r28)
	cmpwi r0, 0x79
	bge @87
	cmpwi r0, 0x72
	bge @88
	b @87
	@88:
	lwz r3, 0x1c(r28)
	bl effSoftDelete
	b @89
	@87:
	addi r3, r28, 0xc
	bl iconDelete
	@89:
	lhz r0, 0x0(r28)
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r28)
	@85:
	addi r27, r27, 0x1
	addi r28, r28, 0x98
	@83:
	lwz r0, 0x0(r26)
	cmpw r27, r0
	blt @84
	b @2
	@80:
	li r0, 0x5
	sth r0, 0x26(r31)
	lwz r3, 0x30(r31)
	bl winMgrCloseAutoDelete
	bl marioChgStayMotion
	addi r3, r31, 0xc
	li r4, 0x2
	bl iconFlagOn
	lwz r4, 0x4(r31)
	cmpwi r4, 0xf0
	blt @90
	cmpwi r4, 0x153
	bge @90
	li r3, 0x2
	li r5, 0x1
	bl winMgrSelectEntry
	stw r3, 0x10(r29)
	b @2
	@90:
	li r3, 0x1
	li r5, 0x1
	bl winMgrSelectEntry
	stw r3, 0x10(r29)
	b @2
	@91:
	lwz r3, 0x18(r29)
	bl windowCheckID
	cmpwi r3, 0x0
	bne @2
	lwz r3, 0xc(r29)
	bl effSoftDelete
	li r3, 0x4
	bl marioSetCamId
	addi r3, r31, 0xc
	li r4, 0x100
	bl iconFlagOff
	li r3, 0x0
	bl marioStSystemLevel
	li r3, 0x80
	bl psndClearFlag
	lwz r3, 0x38(r31)
	rlwinm. r0, r3, 0, 7, 7
	beq @92
	rlwinm r0, r3, 0, 8, 6
	stw r0, 0x38(r31)
	bl marioCtrlOn
	@92:
	bl marioKeyOn
	bl marioChgStayMotion
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	lis r4, work@ha
	addi r26, r4, work@l
	rlwinm r0, r0, 0, 23, 21
	sth r0, 0x0(r3)
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq @93
	addi r26, r26, 0x1c
	@93:
	lwz r28, 0x4(r26)
	li r27, 0x0
	b @94
	@95:
	addi r3, r28, 0xc
	addi r4, r31, 0xc
	bl strcmp
	cmpwi r3, 0x0
	bne @96
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	bne @97
	lwz r3, 0x4(r28)
	cmpwi r3, 0xf0
	blt @97
	cmpwi r3, 0x153
	bge @97
	lhz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 23, 23
	beq @97
	bl pouchArriveBadge
	@97:
	lwz r0, 0x4(r28)
	cmpwi r0, 0x79
	bge @98
	cmpwi r0, 0x72
	bge @99
	b @98
	@99:
	lwz r3, 0x1c(r28)
	bl effSoftDelete
	b @100
	@98:
	addi r3, r28, 0xc
	bl iconDelete
	@100:
	lhz r0, 0x0(r28)
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r28)
	@96:
	addi r27, r27, 0x1
	addi r28, r28, 0x98
	@94:
	lwz r0, 0x0(r26)
	cmpw r27, r0
	blt @95
	b @2
	@101:
	lwz r3, 0x10(r29)
	bl winMgrSelect
	mr. r26, r3
	beq @2
	lwz r3, 0x10(r29)
	bl winMgrSelectDelete
	cmpwi r26, 0x0
	bge @102
	lwz r0, 0x38(r31)
	rlwinm. r0, r0, 0, 5, 5
	beq @103
	lhz r0, 0x0(r31)
	ori r0, r0, 0x100
	sth r0, 0x0(r31)
	b @103
	@102:
	mr r3, r26
	bl pouchRemoveItem
	lwz r3, 0x4(r31)
	bl pouchGetItem
	cmpwi r3, 0x0
	beq @104
	lhz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 26, 26
	beq @105
	lwz r3, 0x8(r31)
	bl swSet
	b @106
	@105:
	rlwinm. r0, r3, 0, 25, 25
	beq @106
	lwz r3, 0x8(r31)
	bl _swSet
	@106:
	lwz r3, 0x20(r31)
	cmplwi r3, 0x0
	beq @107
	li r4, 0x0
	li r5, 0x20
	bl evtEntry
	lfs f1, float_1024_8041affc(r2)
	lfs f0, 0x3c(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x48(r1)
	lwz r4, 0x4c(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0x9c(r3)
	lfs f0, 0x40(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x40(r1)
	lwz r4, 0x44(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa0(r3)
	lfs f0, 0x44(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x38(r1)
	lwz r4, 0x3c(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa4(r3)
	@107:
	lwz r0, 0x38(r31)
	ori r0, r0, 0x1
	stw r0, 0x38(r31)
	@104:
	lwz r5, 0x38(r31)
	lis r4, itemDataTable@ha
	li r0, 0x0
	addi r3, r31, 0xc
	clrrwi r5, r5, 1
	addi r4, r4, itemDataTable@l
	stw r5, 0x38(r31)
	stw r26, 0x4(r31)
	stw r0, 0x20(r31)
	stw r0, 0x8(r31)
	lhz r0, 0x0(r31)
	rlwinm r0, r0, 0, 27, 24
	sth r0, 0x0(r31)
	lwz r0, 0x4(r31)
	mulli r0, r0, 0x28
	add r4, r4, r0
	lhz r4, 0x20(r4)
	bl iconChange
	lwz r4, 0x8(r29)
	addi r3, r31, 0xc
	addi r0, r4, 0x1
	stw r0, 0x8(r29)
	bl iconNameToPtr
	lwz r5, 0x8(r29)
	addi r4, r28, 0x200
	crclr 6
	addi r3, r3, 0x18
	bl sprintf
	lwz r5, 0x8(r29)
	addi r3, r31, 0xc
	addi r4, r28, 0x200
	crclr 6
	bl sprintf
	lhz r0, 0x0(r31)
	ori r0, r0, 0x100
	sth r0, 0x0(r31)
	@103:
	lhz r0, 0x0(r31)
	lis r3, itemdrv_window_desc@ha
	addi r3, r3, itemdrv_window_desc@l
	lfs f0, float_85_8041b008(r2)
	rlwinm r0, r0, 0, 20, 18
	lfs f2, float_120_8041b00c(r2)
	sth r0, 0x0(r31)
	addi r3, r3, 0x78
	lfs f1, float_0p7_8041aff4(r2)
	stfs f0, 0x50(r31)
	lfs f0, float_1_8041afa4(r2)
	stfs f2, 0x58(r31)
	stfs f1, 0x80(r31)
	stfs f0, 0x84(r31)
	bl winMgrEntry
	stw r3, 0x28(r31)
	lwz r3, 0x28(r31)
	bl winMgrOpen
	lwz r3, 0x28(r31)
	mr r4, r31
	bl winMgrSetParam
	bl marioChgGetItemMotion
	addi r3, r31, 0xc
	li r4, 0x2
	bl iconFlagOff
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 6, 6
	beq @108
	lwz r0, 0x38(r31)
	ori r0, r0, 0x8000
	stw r0, 0x38(r31)
	@108:
	li r0, 0x9
	sth r0, 0x26(r31)
	b @2
	@109:
	lis r3, all_juyoitem_lecture@ha
	li r4, 0x0
	addi r3, r3, all_juyoitem_lecture@l
	li r5, 0x0
	li r6, 0x0
	bl evtEntryType
	stw r3, 0x14(r29)
	li r3, 0x80
	lwz r4, 0x14(r29)
	stw r31, 0xbc(r4)
	lwz r0, 0xc(r29)
	lwz r4, 0x14(r29)
	stw r0, 0xc0(r4)
	bl psndClearFlag
	li r0, 0x7
	sth r0, 0x26(r31)
	b @2
	@110:
	lwz r3, 0x14(r29)
	lwz r3, 0x15c(r3)
	bl evtCheckID
	cmpwi r3, 0x0
	bne @2
	li r3, 0x0
	bl marioStSystemLevel
	li r3, 0x80
	bl psndClearFlag
	lwz r3, 0x38(r31)
	rlwinm. r0, r3, 0, 7, 7
	beq @111
	rlwinm r0, r3, 0, 8, 6
	stw r0, 0x38(r31)
	bl marioCtrlOn
	@111:
	bl marioKeyOn
	bl marioChgStayMotion
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	lis r4, work@ha
	addi r26, r4, work@l
	rlwinm r0, r0, 0, 23, 21
	sth r0, 0x0(r3)
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq @112
	addi r26, r26, 0x1c
	@112:
	lwz r28, 0x4(r26)
	li r27, 0x0
	b @113
	@114:
	addi r3, r28, 0xc
	addi r4, r31, 0xc
	bl strcmp
	cmpwi r3, 0x0
	bne @115
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	bne @116
	lwz r3, 0x4(r28)
	cmpwi r3, 0xf0
	blt @116
	cmpwi r3, 0x153
	bge @116
	lhz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 23, 23
	beq @116
	bl pouchArriveBadge
	@116:
	lwz r0, 0x4(r28)
	cmpwi r0, 0x79
	bge @117
	cmpwi r0, 0x72
	bge @118
	b @117
	@118:
	lwz r3, 0x1c(r28)
	bl effSoftDelete
	b @119
	@117:
	addi r3, r28, 0xc
	bl iconDelete
	@119:
	lhz r0, 0x0(r28)
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r28)
	@115:
	addi r27, r27, 0x1
	addi r28, r28, 0x98
	@113:
	lwz r0, 0x0(r26)
	cmpw r27, r0
	blt @114
	b @2
	@120:
	li r3, 0x0
	bl keyGetButtonTrg
	rlwinm. r0, r3, 0, 23, 23
	beq @2
	lwz r3, 0x28(r31)
	bl winMgrCloseAutoDelete
	lwz r4, 0x38(r31)
	li r0, 0x6
	li r3, 0x0
	ori r4, r4, 0x8
	stw r4, 0x38(r31)
	sth r0, 0x24(r31)
	sth r3, 0x26(r31)
	lhz r0, 0x0(r31)
	rlwinm r0, r0, 0, 28, 26
	sth r0, 0x0(r31)
	lwz r0, 0x4(r31)
	cmpwi r0, 0x1
	blt @121
	cmpwi r0, 0x79
	bge @121
	stw r3, 0x7c(r31)
	stw r3, 0x78(r31)
	b @122
	@121:
	cmpwi r0, 0xf0
	blt @123
	cmpwi r0, 0x153
	bge @123
	li r0, 0x0
	stw r0, 0x7c(r31)
	stw r0, 0x78(r31)
	b @122
	@123:
	li r3, 0x4e20
	li r0, 0x0
	stw r3, 0x7c(r31)
	stw r0, 0x78(r31)
	@122:
	lwz r0, 0x38(r31)
	li r3, 0x0
	oris r0, r0, 0x1
	stw r0, 0x38(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 20, 18
	stw r0, 0x38(r31)
	lhz r0, 0x0(r31)
	rlwinm r0, r0, 0, 31, 29
	sth r0, 0x0(r31)
	bl marioStSystemLevel
	li r3, 0x80
	bl psndClearFlag
	lwz r3, 0x38(r31)
	rlwinm. r0, r3, 0, 7, 7
	beq @124
	rlwinm r0, r3, 0, 8, 6
	stw r0, 0x38(r31)
	bl marioCtrlOn
	@124:
	bl marioKeyOn
	bl marioChgStayMotion
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 23, 21
	sth r0, 0x0(r3)
	b @2
	@125:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 6, 6
	beq @126
	lwz r0, 0x38(r31)
	ori r0, r0, 0x8000
	stw r0, 0x38(r31)
	@126:
	li r4, 0x0
	stw r4, 0x7c(r31)
	stw r4, 0x78(r31)
	lwz r0, 0x38(r31)
	rlwinm. r0, r0, 0, 19, 19
	beq @127
	li r0, 0x1
	sth r0, 0x24(r31)
	sth r4, 0x26(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x38(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x38(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 18, 16
	stw r0, 0x38(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 20, 18
	stw r0, 0x38(r31)
	lhz r0, 0x0(r31)
	rlwinm r0, r0, 0, 20, 18
	sth r0, 0x0(r31)
	b @128
	@127:
	lfs f1, float_85_8041b008(r2)
	li r0, 0x6
	lfs f0, float_120_8041b00c(r2)
	stfs f1, 0x50(r31)
	lfs f1, float_0p7_8041aff4(r2)
	stfs f0, 0x58(r31)
	lfs f0, float_1_8041afa4(r2)
	stfs f1, 0x80(r31)
	stfs f0, 0x84(r31)
	lwz r3, 0x38(r31)
	ori r3, r3, 0x8
	stw r3, 0x38(r31)
	sth r0, 0x24(r31)
	sth r4, 0x26(r31)
	lhz r0, 0x0(r31)
	rlwinm r0, r0, 0, 28, 26
	sth r0, 0x0(r31)
	lwz r0, 0x38(r31)
	rlwinm r0, r0, 0, 20, 18
	stw r0, 0x38(r31)
	lhz r0, 0x0(r31)
	rlwinm r0, r0, 0, 31, 29
	sth r0, 0x0(r31)
	lhz r0, 0x0(r31)
	rlwinm r0, r0, 0, 20, 18
	sth r0, 0x0(r31)
	@128:
	li r3, 0x0
	bl marioStSystemLevel
	li r3, 0x80
	bl psndClearFlag
	lwz r3, 0x38(r31)
	rlwinm. r0, r3, 0, 7, 7
	beq @129
	rlwinm r0, r3, 0, 8, 6
	stw r0, 0x38(r31)
	bl marioCtrlOn
	@129:
	bl marioKeyOn
	@2:
	lmw r26, 0x58(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void winFullDisp(WinMgrEntry* win) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	li r0, 0x0
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	mr r30, r3
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	lwz r31, 0x2c(r3)
	lwz r3, 0x4(r31)
	cmpwi r3, 0xf0
	blt @1
	cmpwi r3, 0x153
	bge @1
	li r0, 0x1
	@1:
	cmpwi r0, 0x0
	beq @2
	lis r3, str_802CADE8@ha
	addi r3, r3, str_802CADE8@l
	bl msgSearch
	b @3
	@2:
	lis r3, str_802CAE00@ha
	addi r3, r3, str_802CAE00@l
	bl msgSearch
	@3:
	mr r29, r3
	bl FontGetMessageWidth
	clrlwi r28, r3, 16
	lwz r0, 0x20(r30)
	addi r3, r28, 0x14
	cmpw r3, r0
	ble @4
	stw r3, 0x20(r30)
	lwz r0, 0x20(r30)
	neg r3, r0
	srwi r0, r3, 31
	add r0, r0, r3
	srawi r0, r0, 1
	stw r0, 0x18(r30)
	@4:
	lwz r3, 0x30(r31)
	bl winMgrAction
	cmpwi r3, 0x0
	bne @5
	bl FontDrawStart
	bl FontDrawEdge
	lwz r0, dat_8041af98(r2)
	addi r3, r1, 0x8
	stw r0, 0x8(r1)
	bl FontDrawColor
	neg r4, r28
	lwz r3, 0x1c(r30)
	srwi r0, r4, 31
	mr r5, r29
	add r0, r0, r4
	subi r4, r3, 0xa
	srawi r3, r0, 1
	bl FontDrawMessage
	bl FontDrawEdgeOff
	@5:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void winHelpDisp(WinMgrEntry* win) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x2c(r3)
	lwz r3, 0x2c(r31)
	bl winMgrAction
	cmpwi r3, 0x0
	bne @1
	lwz r0, 0x4(r31)
	lis r3, itemDataTable@ha
	addi r3, r3, itemDataTable@l
	mulli r0, r0, 0x28
	add r3, r3, r0
	lwz r3, 0x8(r3)
	bl msgSearch
	stw r3, 0x34(r30)
	mr r3, r30
	bl winMgrHelpDraw
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void winHelpMain(WinMgrEntry* win) {
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

asm void winNameDisp2(WinMgrEntry* win) {
	nofralloc
	stwu r1, -0x420(r1)
	mflr r0
	stw r0, 0x424(r1)
	stw r31, 0x41c(r1)
	stw r30, 0x418(r1)
	mr r30, r3
	lis r3, itemDataTable@ha
	stw r29, 0x414(r1)
	addi r3, r3, itemDataTable@l
	lwz r31, 0x2c(r30)
	lwz r0, 0x4(r31)
	mulli r0, r0, 0x28
	add r3, r3, r0
	lwz r3, 0x4(r3)
	bl msgSearch
	lis r4, str_802CAE18@ha
	mr r29, r3
	addi r0, r4, str_802CAE18@l
	mr r3, r0
	bl msgSearch
	mr r4, r3
	mr r5, r29
	addi r3, r1, 0xc
	crclr 6
	bl sprintf
	addi r3, r1, 0xc
	bl FontGetMessageWidth
	clrlwi r29, r3, 16
	lwz r0, 0x20(r30)
	addi r3, r29, 0x14
	cmpw r3, r0
	ble @1
	stw r3, 0x20(r30)
	lwz r0, 0x20(r30)
	neg r3, r0
	srwi r0, r3, 31
	add r0, r0, r3
	srawi r0, r0, 1
	stw r0, 0x18(r30)
	@1:
	lwz r3, 0x28(r31)
	bl winMgrAction
	cmpwi r3, 0x0
	bne @2
	bl FontDrawStart
	lwz r0, dat_8041af94(r2)
	addi r3, r1, 0x8
	stw r0, 0x8(r1)
	bl FontDrawColor
	neg r4, r29
	lwz r3, 0x1c(r30)
	srwi r0, r4, 31
	addi r5, r1, 0xc
	add r0, r0, r4
	subi r4, r3, 0x8
	srawi r3, r0, 1
	bl FontDrawMessage
	@2:
	lwz r0, 0x424(r1)
	lwz r31, 0x41c(r1)
	lwz r30, 0x418(r1)
	lwz r29, 0x414(r1)
	mtlr r0
	addi r1, r1, 0x420
	blr
}

asm void winNameDisp(WinMgrEntry* win) {
	nofralloc
	stwu r1, -0x420(r1)
	mflr r0
	stw r0, 0x424(r1)
	stw r31, 0x41c(r1)
	stw r30, 0x418(r1)
	mr r30, r3
	lis r3, itemDataTable@ha
	stw r29, 0x414(r1)
	addi r3, r3, itemDataTable@l
	lwz r31, 0x2c(r30)
	lwz r0, 0x4(r31)
	mulli r0, r0, 0x28
	add r3, r3, r0
	lwz r3, 0x4(r3)
	bl msgSearch
	lwz r0, 0x4(r31)
	mr r29, r3
	cmpwi r0, 0xf0
	blt @1
	cmpwi r0, 0x153
	bge @1
	lis r3, str_802CAE30@ha
	addi r3, r3, str_802CAE30@l
	bl msgSearch
	mr r4, r3
	mr r5, r29
	addi r3, r1, 0xc
	crclr 6
	bl sprintf
	b @2
	@1:
	lis r3, str_802CAE48@ha
	addi r3, r3, str_802CAE48@l
	bl msgSearch
	mr r4, r3
	mr r5, r29
	addi r3, r1, 0xc
	crclr 6
	bl sprintf
	@2:
	addi r3, r1, 0xc
	bl FontGetMessageWidth
	clrlwi r29, r3, 16
	lwz r0, 0x20(r30)
	addi r3, r29, 0x14
	cmpw r3, r0
	ble @3
	stw r3, 0x20(r30)
	lwz r0, 0x20(r30)
	neg r3, r0
	srwi r0, r3, 31
	add r0, r0, r3
	srawi r0, r0, 1
	stw r0, 0x18(r30)
	@3:
	lwz r3, 0x28(r31)
	bl winMgrAction
	cmpwi r3, 0x0
	bne @4
	bl FontDrawStart
	lwz r0, dat_8041af90(r2)
	addi r3, r1, 0x8
	stw r0, 0x8(r1)
	bl FontDrawColor
	neg r4, r29
	lwz r3, 0x1c(r30)
	srwi r0, r4, 31
	addi r5, r1, 0xc
	add r0, r0, r4
	subi r4, r3, 0x8
	srawi r3, r0, 1
	bl FontDrawMessage
	@4:
	lwz r0, 0x424(r1)
	lwz r31, 0x41c(r1)
	lwz r30, 0x418(r1)
	lwz r29, 0x414(r1)
	mtlr r0
	addi r1, r1, 0x420
	blr
}

asm ItemEntry* itemNearDistCheck(f32 x, f32 y, f32 z, f32 range) {
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
	stw r31, 0x5c(r1)
	stw r30, 0x58(r1)
	stw r29, 0x54(r1)
	stw r28, 0x50(r1)
	fmr f28, f1
	fmr f29, f2
	fmr f30, f3
	fmr f31, f4
	bl marioGetPtr
	lwz r4, gp(r13)
	lis r3, work@ha
	addi r31, r3, work@l
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @1
	addi r31, r31, 0x1c
	@1:
	lis r3, vec3_802cabec@ha
	lwz r30, 0x4(r31)
	addi r5, r3, vec3_802cabec@l
	li r29, 0x0
	lwz r4, 0x0(r5)
	li r28, 0x0
	lwz r3, 0x4(r5)
	lwz r0, 0x8(r5)
	stw r4, 0x14(r1)
	stw r3, 0x18(r1)
	stw r0, 0x1c(r1)
	stfs f28, 0x14(r1)
	stfs f29, 0x18(r1)
	lwz r4, 0x14(r1)
	stfs f30, 0x1c(r1)
	lwz r3, 0x18(r1)
	lwz r0, 0x1c(r1)
	stw r4, 0x20(r1)
	stw r3, 0x24(r1)
	stw r0, 0x28(r1)
	b @2
	@3:
	lhz r0, 0x0(r30)
	clrlwi. r0, r0, 31
	beq @4
	lwz r3, 0x38(r30)
	rlwinm. r0, r3, 0, 19, 19
	bne @4
	rlwinm. r0, r3, 0, 11, 11
	bne @4
	lhz r0, 0x24(r30)
	cmplwi r0, 0x2
	beq @4
	rlwinm. r0, r3, 0, 6, 6
	bne @4
	lis r3, vec3_802cabf8@ha
	lfs f2, 0x3c(r30)
	addi r5, r3, vec3_802cabf8@l
	lfs f1, 0x40(r30)
	lwz r7, 0x0(r5)
	addi r3, r1, 0x38
	lwz r6, 0x4(r5)
	addi r4, r1, 0x20
	lwz r0, 0x8(r5)
	addi r5, r1, 0x2c
	stw r7, 0x8(r1)
	lfs f0, 0x44(r30)
	stw r6, 0xc(r1)
	stw r0, 0x10(r1)
	stfs f2, 0x8(r1)
	stfs f1, 0xc(r1)
	lwz r7, 0x8(r1)
	stfs f0, 0x10(r1)
	lwz r6, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r7, 0x38(r1)
	stw r6, 0x3c(r1)
	stw r0, 0x40(r1)
	bl PSVECSubtract
	addi r3, r1, 0x2c
	bl PSVECMag
	fcmpo cr0, f1, f31
	bge @4
	mr r29, r30
	fmr f31, f1
	@4:
	addi r28, r28, 0x1
	addi r30, r30, 0x98
	@2:
	lwz r0, 0x0(r31)
	cmpw r28, r0
	blt @3
	mr r3, r29
	psq_l f31, 0x98(r1), 0, 0
	lfd f31, 0x90(r1)
	psq_l f30, 0x88(r1), 0, 0
	lfd f30, 0x80(r1)
	psq_l f29, 0x78(r1), 0, 0
	lfd f29, 0x70(r1)
	psq_l f28, 0x68(r1), 0, 0
	lfd f28, 0x60(r1)
	lwz r31, 0x5c(r1)
	lwz r30, 0x58(r1)
	lwz r29, 0x54(r1)
	lwz r0, 0xa4(r1)
	lwz r28, 0x50(r1)
	mtlr r0
	addi r1, r1, 0xa0
	blr
}

asm ItemEntry* itemHitCheck(f32 x, f32 y, f32 z, f32 range) {
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
	stmw r26, 0x38(r1)
	lwz r4, gp(r13)
	lis r3, work@ha
	addi r30, r3, work@l
	fmr f27, f1
	lwz r0, 0x14(r4)
	lis r3, vec3_802cabe0@ha
	fmr f28, f2
	addi r29, r3, vec3_802cabe0@l
	fmr f29, f3
	cmpwi r0, 0x0
	fmr f30, f4
	beq @1
	addi r30, r30, 0x1c
	@1:
	bl marioGetPtr
	lwz r28, 0x4(r30)
	mr r31, r3
	li r26, 0x0
	li r27, 0x0
	b @2
	@3:
	lhz r3, 0x0(r28)
	clrlwi. r0, r3, 31
	beq @4
	rlwinm. r0, r3, 0, 30, 30
	bne @4
	lwz r0, 0x38(r28)
	rlwinm. r0, r0, 0, 19, 19
	bne @4
	lhz r0, 0x24(r28)
	cmplwi r0, 0x2
	beq @4
	lfs f1, 0x3c(r28)
	lfs f0, 0x44(r28)
	fsubs f3, f27, f1
	lfs f2, 0x40(r28)
	fsubs f0, f29, f0
	lfs f1, float_0_8041af9c(r2)
	fsubs f7, f28, f2
	fmuls f5, f3, f3
	fmuls f6, f0, f0
	fadds f0, f5, f6
	fcmpo cr0, f0, f1
	ble @5
	frsqrte f2, f0
	lfd f4, 0x50(r29)
	lfd f3, 0x58(r29)
	fmul f1, f2, f2
	fmul f2, f4, f2
	fnmsub f1, f0, f1, f3
	fmul f2, f2, f1
	fmul f1, f2, f2
	fmul f2, f4, f2
	fnmsub f1, f0, f1, f3
	fmul f2, f2, f1
	fmul f1, f2, f2
	fmul f2, f4, f2
	fnmsub f1, f0, f1, f3
	fmul f1, f2, f1
	fmul f0, f0, f1
	frsp f0, f0
	b @6
	@5:
	lfd f1, 0x60(r29)
	fcmpo cr0, f0, f1
	bge @7
	lis r3, __float_nan@ha
	lfs f0, __float_nan@l(r3)
	b @6
	@7:
	stfs f0, 0xc(r1)
	lis r0, 0x7f80
	lwz r4, 0xc(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @8
	bge @9
	cmpwi r3, 0x0
	beq @10
	b @9
	@8:
	clrlwi. r0, r4, 9
	beq @11
	li r0, 0x1
	b @12
	@11:
	li r0, 0x2
	b @12
	@10:
	clrlwi. r0, r4, 9
	beq @13
	li r0, 0x5
	b @12
	@13:
	li r0, 0x3
	b @12
	@9:
	li r0, 0x4
	@12:
	cmpwi r0, 0x1
	bne @6
	lis r3, __float_nan@ha
	lfs f0, __float_nan@l(r3)
	@6:
	fmadds f2, f7, f7, f5
	lfs f1, float_0_8041af9c(r2)
	fadds f31, f6, f2
	fcmpo cr0, f31, f1
	ble @14
	frsqrte f2, f31
	lfd f4, 0x50(r29)
	lfd f3, 0x58(r29)
	fmul f1, f2, f2
	fmul f2, f4, f2
	fnmsub f1, f31, f1, f3
	fmul f2, f2, f1
	fmul f1, f2, f2
	fmul f2, f4, f2
	fnmsub f1, f31, f1, f3
	fmul f2, f2, f1
	fmul f1, f2, f2
	fmul f2, f4, f2
	fnmsub f1, f31, f1, f3
	fmul f1, f2, f1
	fmul f31, f31, f1
	frsp f31, f31
	b @15
	@14:
	lfd f1, 0x60(r29)
	fcmpo cr0, f31, f1
	bge @16
	lis r3, __float_nan@ha
	lfs f31, __float_nan@l(r3)
	b @15
	@16:
	stfs f31, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @17
	bge @18
	cmpwi r3, 0x0
	beq @19
	b @18
	@17:
	clrlwi. r0, r4, 9
	beq @20
	li r0, 0x1
	b @21
	@20:
	li r0, 0x2
	b @21
	@19:
	clrlwi. r0, r4, 9
	beq @22
	li r0, 0x5
	b @21
	@22:
	li r0, 0x3
	b @21
	@18:
	li r0, 0x4
	@21:
	cmpwi r0, 0x1
	bne @15
	lis r3, __float_nan@ha
	lfs f31, __float_nan@l(r3)
	@15:
	fcmpo cr0, f0, f30
	bge @4
	bl marioItemGetOk
	cmpwi r3, 0x0
	beq @4
	bl marioGetJabaraState
	cmpwi r3, 0x1
	beq @4
	bl marioGetJabaraState
	cmpwi r3, 0x4
	beq @4
	bl marioGetJabaraState
	cmpwi r3, 0x5
	beq @4
	lfs f4, float_0p5_8041afb8(r2)
	lfs f0, 0x1b8(r31)
	lfs f1, float_10_8041afb0(r2)
	fmadds f2, f4, f0, f28
	lfs f3, 0x40(r28)
	fmadds f0, f4, f0, f1
	fsubs f2, f2, f3
	fabs f2, f2
	fcmpo cr0, f2, f0
	bge @4
	fcmpo cr0, f28, f3
	li r3, 0x0
	bge @23
	fsubs f0, f3, f28
	lfs f4, float_0_8041af9c(r2)
	fadds f0, f1, f0
	fcmpo cr0, f0, f4
	stfs f0, 0x1c(r1)
	ble @23
	fmr f1, f27
	lfs f5, float_1_8041afa4(r2)
	fmr f2, f28
	addi r4, r1, 0x28
	fmr f3, f29
	addi r5, r1, 0x24
	fmr f6, f4
	addi r6, r1, 0x20
	addi r7, r1, 0x1c
	addi r8, r1, 0x18
	addi r9, r1, 0x14
	addi r10, r1, 0x10
	lis r3, 0x8000
	bl hitCheckAttr
	@23:
	cmplwi r3, 0x0
	bne @4
	mr r26, r28
	fmr f30, f31
	@4:
	addi r27, r27, 0x1
	addi r28, r28, 0x98
	@2:
	lwz r0, 0x0(r30)
	cmpw r27, r0
	blt @3
	mr r3, r26
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
	lmw r26, 0x38(r1)
	lwz r0, 0xa4(r1)
	mtlr r0
	addi r1, r1, 0xa0
	blr
}

asm ItemEntry* itemNameToPtr(char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, work@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	addi r31, r4, work@l
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	lwz r5, gp(r13)
	lwz r0, 0x14(r5)
	cmpwi r0, 0x0
	beq @1
	addi r31, r31, 0x1c
	@1:
	lwz r30, 0x4(r31)
	li r29, 0x0
	b @2
	@3:
	mr r4, r28
	addi r3, r30, 0xc
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	mr r3, r30
	b @5
	@4:
	addi r29, r29, 0x1
	addi r30, r30, 0x98
	@2:
	lwz r0, 0x0(r31)
	cmpw r29, r0
	blt @3
	li r3, 0x0
	@5:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void itemDelete(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, work@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	addi r31, r4, work@l
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	lwz r5, gp(r13)
	lwz r0, 0x14(r5)
	cmpwi r0, 0x0
	beq @1
	addi r31, r31, 0x1c
	@1:
	lwz r30, 0x4(r31)
	li r29, 0x0
	b @2
	@3:
	mr r4, r28
	addi r3, r30, 0xc
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	bne @5
	lwz r3, 0x4(r30)
	cmpwi r3, 0xf0
	blt @5
	cmpwi r3, 0x153
	bge @5
	lhz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 23, 23
	beq @5
	bl pouchArriveBadge
	@5:
	lwz r0, 0x4(r30)
	cmpwi r0, 0x79
	bge @6
	cmpwi r0, 0x72
	bge @7
	b @6
	@7:
	lwz r3, 0x1c(r30)
	bl effSoftDelete
	b @8
	@6:
	addi r3, r30, 0xc
	bl iconDelete
	@8:
	lhz r0, 0x0(r30)
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r30)
	@4:
	addi r29, r29, 0x1
	addi r30, r30, 0x98
	@2:
	lwz r0, 0x0(r31)
	cmpw r29, r0
	blt @3
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm ItemEntry* itemEntry(const char* name, s32 itemId, s32 type, s32 evtId, s32 a5, f32 x, f32 y, f32 z) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stfd f30, 0x50(r1)
	psq_st f30, 0x58(r1), 0, 0
	stfd f29, 0x40(r1)
	psq_st f29, 0x48(r1), 0, 0
	stmw r21, 0x14(r1)
	lwz r9, gp(r13)
	lis r8, work@ha
	fmr f29, f1
	addi r23, r8, work@l
	lwz r0, 0x14(r9)
	fmr f30, f2
	fmr f31, f3
	mr r24, r3
	cmpwi r0, 0x0
	mr r25, r4
	mr r26, r5
	mr r27, r6
	mr r28, r7
	beq @1
	addi r23, r23, 0x1c
	@1:
	cmpwi r27, -0x1
	li r30, 0x0
	li r29, 0x0
	beq @2
	lis r3, 0xf840
	addi r0, r3, 0x5b80
	cmpw r27, r0
	blt @3
	lis r3, 0xf8d9
	subi r0, r3, 0xe00
	cmpw r27, r0
	bgt @3
	addis r27, r27, 0x7c0
	li r30, 0x1
	subi r27, r27, 0x5b80
	mr r3, r27
	bl swGet
	cmpwi r3, 0x0
	beq @2
	li r3, 0x0
	b @4
	@3:
	lis r3, 0xf972
	subi r0, r3, 0x7780
	cmpw r27, r0
	blt @2
	lis r3, 0xfa0a
	addi r0, r3, 0x1f00
	cmpw r27, r0
	bgt @2
	addis r27, r27, 0x68e
	li r29, 0x1
	addi r27, r27, 0x7780
	mr r3, r27
	bl _swGet
	cmpwi r3, 0x0
	beq @2
	li r3, 0x0
	b @4
	@2:
	cmplwi r24, 0x0
	bne @5
	lwz r4, 0x8(r23)
	lis r3, 0x10
	subi r0, r3, 0x1
	addi r3, r4, 0x1
	stw r3, 0x8(r23)
	lwz r3, 0x8(r23)
	cmplw r3, r0
	blt @6
	li r0, 0x1
	stw r0, 0x8(r23)
	@6:
	lis r3, str_802CADE0@ha
	lwz r5, 0x8(r23)
	addi r4, r3, str_802CADE0@l
	addi r3, r1, 0x8
	crclr 6
	bl sprintf
	addi r24, r1, 0x8
	@5:
	lwz r22, 0x4(r23)
	li r21, 0x0
	b @7
	@8:
	lhz r0, 0x0(r22)
	clrlwi. r0, r0, 31
	beq @9
	mr r4, r24
	addi r3, r22, 0xc
	bl strcmp
	cmpwi r3, 0x0
	beq @10
	@9:
	addi r21, r21, 0x1
	addi r22, r22, 0x98
	@7:
	lwz r0, 0x0(r23)
	cmpw r21, r0
	blt @8
	@10:
	lwz r4, 0x4(r23)
	li r5, 0x0
	lwz r3, 0x0(r23)
	mr r31, r4
	mtctr r3
	cmpwi r3, 0x0
	ble @11
	@12:
	lhz r0, 0x0(r31)
	clrlwi. r0, r0, 31
	beq @11
	addi r5, r5, 0x1
	addi r31, r31, 0x98
	bdnz @12
	@11:
	cmpw r5, r3
	blt @13
	lhz r3, 0x0(r4)
	mr r31, r4
	clrlwi. r0, r3, 31
	beq @14
	lwz r0, 0x4(r4)
	cmpwi r0, 0x79
	bne @14
	rlwinm. r0, r3, 0, 21, 21
	beq @14
	lwz r4, gp(r13)
	lis r3, work@ha
	addi r23, r3, work@l
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @15
	addi r23, r23, 0x1c
	@15:
	lwz r21, 0x4(r23)
	li r22, 0x0
	b @16
	@17:
	addi r3, r21, 0xc
	addi r4, r31, 0xc
	bl strcmp
	cmpwi r3, 0x0
	bne @18
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	bne @19
	lwz r3, 0x4(r21)
	cmpwi r3, 0xf0
	blt @19
	cmpwi r3, 0x153
	bge @19
	lhz r0, 0x0(r21)
	rlwinm. r0, r0, 0, 23, 23
	beq @19
	bl pouchArriveBadge
	@19:
	lwz r0, 0x4(r21)
	cmpwi r0, 0x79
	bge @20
	cmpwi r0, 0x72
	bge @21
	b @20
	@21:
	lwz r3, 0x1c(r21)
	bl effSoftDelete
	b @22
	@20:
	addi r3, r21, 0xc
	bl iconDelete
	@22:
	lhz r0, 0x0(r21)
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r21)
	@18:
	addi r22, r22, 0x1
	addi r21, r21, 0x98
	@16:
	lwz r0, 0x0(r23)
	cmpw r22, r0
	blt @17
	b @23
	@14:
	clrlwi. r0, r3, 31
	mr r31, r4
	beq @24
	lwz r0, 0x4(r4)
	cmpwi r0, 0x7c
	bne @24
	rlwinm. r0, r3, 0, 21, 21
	beq @24
	lwz r4, gp(r13)
	lis r3, work@ha
	addi r23, r3, work@l
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @25
	addi r23, r23, 0x1c
	@25:
	lwz r22, 0x4(r23)
	li r21, 0x0
	b @26
	@27:
	addi r3, r22, 0xc
	addi r4, r31, 0xc
	bl strcmp
	cmpwi r3, 0x0
	bne @28
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	bne @29
	lwz r3, 0x4(r22)
	cmpwi r3, 0xf0
	blt @29
	cmpwi r3, 0x153
	bge @29
	lhz r0, 0x0(r22)
	rlwinm. r0, r0, 0, 23, 23
	beq @29
	bl pouchArriveBadge
	@29:
	lwz r0, 0x4(r22)
	cmpwi r0, 0x79
	bge @30
	cmpwi r0, 0x72
	bge @31
	b @30
	@31:
	lwz r3, 0x1c(r22)
	bl effSoftDelete
	b @32
	@30:
	addi r3, r22, 0xc
	bl iconDelete
	@32:
	lhz r0, 0x0(r22)
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r22)
	@28:
	addi r21, r21, 0x1
	addi r22, r22, 0x98
	@26:
	lwz r0, 0x0(r23)
	cmpw r21, r0
	blt @27
	b @23
	@24:
	clrlwi. r0, r3, 31
	mr r31, r4
	beq @33
	lwz r0, 0x4(r4)
	cmpwi r0, 0x7b
	bne @33
	rlwinm. r0, r3, 0, 21, 21
	beq @33
	lwz r4, gp(r13)
	lis r3, work@ha
	addi r23, r3, work@l
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @34
	addi r23, r23, 0x1c
	@34:
	lwz r22, 0x4(r23)
	li r21, 0x0
	b @35
	@36:
	addi r3, r22, 0xc
	addi r4, r31, 0xc
	bl strcmp
	cmpwi r3, 0x0
	bne @37
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	bne @38
	lwz r3, 0x4(r22)
	cmpwi r3, 0xf0
	blt @38
	cmpwi r3, 0x153
	bge @38
	lhz r0, 0x0(r22)
	rlwinm. r0, r0, 0, 23, 23
	beq @38
	bl pouchArriveBadge
	@38:
	lwz r0, 0x4(r22)
	cmpwi r0, 0x79
	bge @39
	cmpwi r0, 0x72
	bge @40
	b @39
	@40:
	lwz r3, 0x1c(r22)
	bl effSoftDelete
	b @41
	@39:
	addi r3, r22, 0xc
	bl iconDelete
	@41:
	lhz r0, 0x0(r22)
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r22)
	@37:
	addi r21, r21, 0x1
	addi r22, r22, 0x98
	@35:
	lwz r0, 0x0(r23)
	cmpw r21, r0
	blt @36
	b @23
	@33:
	li r31, 0x0
	@23:
	cmplwi r31, 0x0
	bne @13
	li r3, 0x0
	b @4
	@13:
	mr r3, r31
	li r4, 0x0
	li r5, 0x98
	bl memset
	mr r4, r24
	addi r3, r31, 0xc
	bl strcpy
	stfs f29, 0x3c(r31)
	cmpwi r27, -0x1
	lfs f0, float_1_8041afa4(r2)
	li r0, 0xff
	stfs f30, 0x40(r31)
	stfs f31, 0x44(r31)
	stw r25, 0x4(r31)
	sth r26, 0x2(r31)
	stw r28, 0x20(r31)
	lhz r3, 0x0(r31)
	ori r3, r3, 0x1
	sth r3, 0x0(r31)
	stfs f0, 0x48(r31)
	stb r0, 0x4c(r31)
	beq @42
	cmpwi r30, 0x0
	beq @43
	stw r27, 0x8(r31)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x20
	sth r0, 0x0(r31)
	b @44
	@43:
	cmpwi r29, 0x0
	beq @44
	stw r27, 0x8(r31)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x40
	sth r0, 0x0(r31)
	b @44
	@42:
	li r0, -0x1
	stw r0, 0x8(r31)
	@44:
	lwz r3, 0x4(r31)
	cmpwi r3, 0x79
	bge @45
	cmpwi r3, 0x72
	bge @46
	b @45
	@46:
	lfs f0, float_16_8041afc8(r2)
	fmr f1, f29
	fmr f3, f31
	lfs f4, float_1_8041afa4(r2)
	fadds f2, f0, f30
	subi r3, r3, 0x72
	bl effStarStoneEntry
	stw r3, 0x1c(r31)
	b @47
	@45:
	mulli r0, r25, 0x28
	li r3, 0x0
	lis r4, itemDataTable@ha
	stw r3, 0x1c(r31)
	addi r3, r31, 0xc
	addi r4, r4, itemDataTable@l
	add r4, r4, r0
	lhz r4, 0x20(r4)
	bl iconEntry
	fmr f1, f29
	addi r3, r31, 0xc
	fmr f2, f30
	fmr f3, f31
	bl iconSetPos
	lfs f1, 0x48(r31)
	addi r3, r31, 0xc
	bl iconSetScale
	lbz r4, 0x4c(r31)
	addi r3, r31, 0xc
	bl iconSetAlpha
	@47:
	lfs f0, float_1_8041afa4(r2)
	stfs f0, 0x84(r31)
	stfs f0, 0x80(r31)
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x6c(r31)
	stw r0, 0x68(r31)
	lwz r0, 0x4(r31)
	cmpwi r0, 0x7d
	bge @48
	cmpwi r0, 0x79
	bge @49
	b @48
	@49:
	lhz r0, 0x0(r31)
	ori r0, r0, 0x4
	sth r0, 0x0(r31)
	@48:
	clrlwi r0, r26, 16
	cmplwi r0, 0x11
	bgt @50
	lis r3, jumptable_80312440@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_80312440@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@51:
	lhz r0, 0x0(r31)
	ori r0, r0, 0x2
	sth r0, 0x0(r31)
	@52:
	li r3, 0x7
	li r0, 0x0
	sth r3, 0x24(r31)
	sth r0, 0x26(r31)
	b @50
	@53:
	li r3, 0x1
	li r0, 0x0
	sth r3, 0x24(r31)
	sth r0, 0x26(r31)
	b @50
	@54:
	li r3, 0x1
	li r0, 0x0
	sth r3, 0x24(r31)
	sth r0, 0x26(r31)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x2
	sth r0, 0x0(r31)
	b @50
	@55:
	li r3, 0x6
	li r0, 0x0
	sth r3, 0x24(r31)
	sth r0, 0x26(r31)
	b @50
	@56:
	li r0, 0x1388
	li r3, 0x0
	stw r0, 0x7c(r31)
	li r0, 0x5
	stw r3, 0x78(r31)
	sth r0, 0x24(r31)
	sth r3, 0x26(r31)
	b @50
	@57:
	lwz r5, 0x38(r31)
	li r4, 0x4e20
	li r3, 0x0
	li r0, 0x6
	ori r5, r5, 0x4000
	stw r5, 0x38(r31)
	stw r4, 0x7c(r31)
	stw r3, 0x78(r31)
	sth r0, 0x24(r31)
	sth r3, 0x26(r31)
	b @50
	@58:
	lwz r5, 0x38(r31)
	li r4, 0x4e20
	li r3, 0x0
	li r0, 0x6
	ori r5, r5, 0x4000
	stw r5, 0x38(r31)
	stw r4, 0x7c(r31)
	stw r3, 0x78(r31)
	sth r0, 0x24(r31)
	sth r3, 0x26(r31)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x400
	sth r0, 0x0(r31)
	b @50
	@59:
	lhz r0, 0x0(r31)
	ori r0, r0, 0x100
	sth r0, 0x0(r31)
	@60:
	lwz r5, 0x38(r31)
	li r4, 0x1f40
	li r3, 0x0
	li r0, 0x6
	ori r5, r5, 0x4000
	stw r5, 0x38(r31)
	stw r4, 0x7c(r31)
	stw r3, 0x78(r31)
	sth r0, 0x24(r31)
	sth r3, 0x26(r31)
	b @50
	@61:
	lwz r5, 0x38(r31)
	li r4, 0x1f40
	li r3, 0x0
	li r0, 0x6
	ori r5, r5, 0x4000
	stw r5, 0x38(r31)
	stw r4, 0x7c(r31)
	stw r3, 0x78(r31)
	sth r0, 0x24(r31)
	sth r3, 0x26(r31)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x400
	sth r0, 0x0(r31)
	b @50
	@62:
	lwz r0, 0x38(r31)
	ori r0, r0, 0x4000
	stw r0, 0x38(r31)
	@63:
	li r0, 0x1388
	li r3, 0x0
	stw r0, 0x7c(r31)
	li r0, 0x6
	stw r3, 0x78(r31)
	sth r0, 0x24(r31)
	sth r3, 0x26(r31)
	b @50
	@64:
	li r0, 0x1388
	li r4, 0x0
	stw r0, 0x7c(r31)
	li r0, 0x6
	stw r4, 0x78(r31)
	lwz r3, 0x38(r31)
	ori r3, r3, 0x40
	stw r3, 0x38(r31)
	sth r0, 0x24(r31)
	sth r4, 0x26(r31)
	b @50
	@65:
	li r3, 0x5
	li r0, 0x0
	sth r3, 0x24(r31)
	sth r0, 0x26(r31)
	b @50
	@66:
	li r3, 0x3
	li r0, 0x0
	sth r3, 0x24(r31)
	sth r0, 0x26(r31)
	b @50
	@67:
	li r3, 0x4
	li r0, 0x0
	sth r3, 0x24(r31)
	sth r0, 0x26(r31)
	b @50
	@68:
	li r3, 0xa
	li r0, 0x0
	sth r3, 0x24(r31)
	sth r0, 0x26(r31)
	@50:
	mr r3, r31
	@4:
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	psq_l f30, 0x58(r1), 0, 0
	lfd f30, 0x50(r1)
	psq_l f29, 0x48(r1), 0, 0
	lfd f29, 0x40(r1)
	lmw r21, 0x14(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void itemModeChange(ItemEntry* entry, s32 mode) {
	nofralloc
	sth r4, 0x24(r3)
	li r0, 0x0
	sth r0, 0x26(r3)
	blr
}

asm void itemMain(void) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stmw r25, 0x44(r1)
	lwz r4, gp(r13)
	lis r3, work@ha
	addi r31, r3, work@l
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @1
	addi r31, r31, 0x1c
	@1:
	bl marioGetPtr
	lfs f3, float_0p5_8041afb8(r2)
	lfs f2, 0x1b4(r3)
	lfs f0, float_12_8041b010(r2)
	lfs f1, 0x8c(r3)
	fmadds f4, f3, f2, f0
	lfs f2, 0x90(r3)
	lfs f3, 0x94(r3)
	bl itemHitCheck
	mr r28, r3
	bl itemGetCheck
	cmpwi r3, 0x0
	beq @2
	li r3, 0x2
	li r0, 0x0
	sth r3, 0x24(r28)
	sth r0, 0x26(r28)
	@2:
	lis r3, work@ha
	lwz r29, 0x4(r31)
	addi r3, r3, work@l
	li r28, 0x0
	addi r30, r3, 0x1c
	b @3
	@4:
	lhz r0, 0x0(r29)
	clrlwi. r0, r0, 31
	beq @5
	lhz r5, 0x24(r29)
	li r4, 0x1
	cmpwi r5, 0x9
	beq @6
	bge @7
	cmpwi r5, 0x2
	beq @8
	blt @6
	cmpwi r5, 0x7
	bge @8
	b @6
	@7:
	cmpwi r5, 0xb
	bge @6
	b @8
	@6:
	lwz r3, gp(r13)
	lwz r0, 0x18(r3)
	clrlwi. r0, r0, 28
	beq @8
	li r4, 0x0
	@8:
	cmpwi r4, 0x0
	bne @9
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x6c(r29)
	stw r0, 0x68(r29)
	b @5
	@9:
	cmplwi r5, 0x2
	beq @10
	lwz r0, 0x78(r29)
	li r3, 0x0
	lwz r4, 0x7c(r29)
	xor r0, r0, r3
	xor r3, r4, r3
	or. r0, r3, r0
	bne @11
	lwz r0, 0x38(r29)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x38(r29)
	b @12
	@11:
	lwz r3, 0x38(r29)
	rlwinm. r0, r3, 0, 17, 17
	beq @13
	rlwinm r0, r3, 0, 24, 22
	stw r0, 0x38(r29)
	b @12
	@13:
	lis r3, 0x8000
	lwz r6, gp(r13)
	lwz r0, 0xf8(r3)
	lis r3, 0x431c
	subi r3, r3, 0x217d
	lwz r5, 0x3c(r6)
	srwi r0, r0, 2
	lwz r4, 0x6c(r29)
	mulhwu r0, r3, r0
	lwz r7, 0x38(r6)
	subfc r6, r4, r5
	lwz r3, 0x68(r29)
	li r5, 0x0
	subfe r3, r3, r7
	slwi r3, r3, 3
	slwi r4, r6, 3
	rlwimi r3, r6, 3, 29, 31
	srwi r6, r0, 15
	bl __div2i
	bl __cvt_sll_flt
	lfs f0, float_1000_8041b014(r2)
	lwz r3, 0x78(r29)
	fdivs f31, f1, f0
	lwz r4, 0x7c(r29)
	bl __cvt_sll_flt
	fsubs f1, f1, f31
	bl __cvt_dbl_usll
	stw r4, 0x7c(r29)
	li r5, 0x0
	xoris r4, r5, 0x8000
	stw r3, 0x78(r29)
	lwz r6, 0x78(r29)
	lwz r7, 0x7c(r29)
	xoris r3, r6, 0x8000
	subfc r0, r7, r5
	subfe r3, r3, r4
	subfe r3, r4, r4
	neg. r3, r3
	bne @14
	li r0, 0x9
	sth r0, 0x24(r29)
	sth r5, 0x26(r29)
	b @12
	@14:
	li r0, 0xbb8
	xoris r3, r6, 0x8000
	subfc r0, r7, r0
	subfe r3, r3, r4
	subfe r3, r4, r4
	neg. r3, r3
	bne @12
	rotrwi r4, r7, 4
	srawi r0, r6, 4
	and r0, r0, r5
	li r3, 0x1
	rlwimi r4, r6, 28, 0, 3
	and r3, r4, r3
	xor r0, r0, r5
	xor r3, r3, r5
	or. r0, r3, r0
	beq @12
	lwz r0, 0x38(r29)
	xori r0, r0, 0x100
	stw r0, 0x38(r29)
	b @12
	@10:
	lwz r0, 0x38(r29)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x38(r29)
	@12:
	lhz r0, 0x24(r29)
	cmplwi r0, 0xa
	bgt @15
	lis r3, jumptable_80312488@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_80312488@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@16:
	mr r3, r29
	bl itemseq_Bound
	b @15
	@17:
	mr r3, r29
	bl itemseq_Bound
	b @15
	@18:
	lwz r0, 0x38(r29)
	lfs f31, 0x40(r29)
	rlwinm. r0, r0, 0, 11, 11
	beq @19
	lfs f0, float_neg1_8041afac(r2)
	li r3, 0x0
	fadds f0, f31, f0
	b @20
	@19:
	lis r4, double_neg1_802cae60@ha
	lis r3, double_20_802cac28@ha
	lfd f0, double_neg1_802cae60@l(r4)
	addi r4, r1, 0x8
	lfd f2, double_20_802cac28@l(r3)
	addi r5, r1, 0xc
	fabs f5, f0
	lfs f4, float_0_8041af9c(r2)
	lfs f0, float_20_8041afa0(r2)
	addi r6, r1, 0x10
	lfs f1, 0x3c(r29)
	fmr f6, f4
	fadd f7, f2, f5
	lfs f3, 0x44(r29)
	fadds f2, f0, f31
	lfs f5, float_neg1_8041afac(r2)
	addi r7, r1, 0x14
	addi r8, r1, 0x18
	frsp f0, f7
	addi r9, r1, 0x1c
	addi r10, r1, 0x20
	li r3, 0x0
	stfs f0, 0x14(r1)
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @21
	lfs f0, 0xc(r1)
	b @20
	@21:
	lfs f0, float_neg1_8041afac(r2)
	li r3, 0x0
	fadds f0, f31, f0
	@20:
	cmplwi r3, 0x0
	bne @22
	li r3, 0x3
	li r0, 0x0
	sth r3, 0x24(r29)
	sth r0, 0x26(r29)
	b @15
	@22:
	stfs f0, 0x40(r29)
	b @15
	@23:
	mr r3, r29
	bl itemseq_GetItem
	b @15
	@24:
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @25
	lfs f2, float_15_8041afb4(r2)
	lfs f1, 0x5c(r3)
	lfs f3, 0x60(r3)
	lfs f0, 0x58(r3)
	fadds f1, f2, f1
	stfs f0, 0x3c(r29)
	stfs f1, 0x40(r29)
	stfs f3, 0x44(r29)
	b @15
	@25:
	li r3, 0x3
	li r0, 0x0
	sth r3, 0x24(r29)
	sth r0, 0x26(r29)
	lwz r0, 0x38(r29)
	rlwinm r0, r0, 0, 20, 18
	stw r0, 0x38(r29)
	b @15
	@26:
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq @27
	mr r25, r30
	b @28
	@27:
	lis r3, work@ha
	addi r25, r3, work@l
	@28:
	lwz r26, 0x4(r25)
	li r27, 0x0
	b @29
	@30:
	addi r3, r26, 0xc
	addi r4, r29, 0xc
	bl strcmp
	cmpwi r3, 0x0
	bne @31
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	bne @32
	lwz r3, 0x4(r26)
	cmpwi r3, 0xf0
	blt @32
	cmpwi r3, 0x153
	bge @32
	lhz r0, 0x0(r26)
	rlwinm. r0, r0, 0, 23, 23
	beq @32
	bl pouchArriveBadge
	@32:
	lwz r0, 0x4(r26)
	cmpwi r0, 0x79
	bge @33
	cmpwi r0, 0x72
	bge @34
	b @33
	@34:
	lwz r3, 0x1c(r26)
	bl effSoftDelete
	b @35
	@33:
	addi r3, r26, 0xc
	bl iconDelete
	@35:
	lhz r0, 0x0(r26)
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r26)
	@31:
	addi r27, r27, 0x1
	addi r26, r26, 0x98
	@29:
	lwz r0, 0x0(r25)
	cmpw r27, r0
	blt @30
	@15:
	lhz r0, 0x0(r29)
	clrlwi. r0, r0, 31
	beq @5
	lwz r0, 0x4(r29)
	cmpwi r0, 0x79
	bge @36
	cmpwi r0, 0x72
	bge @37
	b @36
	@37:
	lwz r0, 0x38(r29)
	rlwinm. r0, r0, 0, 23, 23
	bne @38
	lwz r3, 0x1c(r29)
	lfs f0, 0x3c(r29)
	lwz r3, 0xc(r3)
	lfs f1, float_16_8041afc8(r2)
	stfs f0, 0x8(r3)
	lfs f0, 0x40(r29)
	lwz r3, 0x1c(r29)
	fadds f0, f1, f0
	lwz r3, 0xc(r3)
	stfs f0, 0xc(r3)
	lwz r3, 0x1c(r29)
	lfs f0, 0x44(r29)
	lwz r3, 0xc(r3)
	stfs f0, 0x10(r3)
	b @39
	@38:
	lwz r3, 0x1c(r29)
	lfs f1, 0x3c(r29)
	lwz r3, 0xc(r3)
	lfs f0, float_neg1000_8041aff0(r2)
	stfs f1, 0x8(r3)
	lwz r3, 0x1c(r29)
	lwz r3, 0xc(r3)
	stfs f0, 0xc(r3)
	lwz r3, 0x1c(r29)
	lfs f0, 0x44(r29)
	lwz r3, 0xc(r3)
	stfs f0, 0x10(r3)
	b @39
	@36:
	lwz r0, 0x38(r29)
	rlwinm. r0, r0, 0, 23, 23
	bne @40
	lfs f1, 0x3c(r29)
	addi r3, r29, 0xc
	lfs f2, 0x40(r29)
	lfs f3, 0x44(r29)
	bl iconSetPos
	lfs f1, 0x48(r29)
	addi r3, r29, 0xc
	bl iconSetScale
	lbz r4, 0x4c(r29)
	addi r3, r29, 0xc
	bl iconSetAlpha
	b @39
	@40:
	lfs f1, 0x3c(r29)
	addi r3, r29, 0xc
	lfs f2, float_neg1000_8041aff0(r2)
	lfs f3, 0x44(r29)
	bl iconSetPos
	@39:
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x6c(r29)
	stw r0, 0x68(r29)
	lwz r0, 0x4(r29)
	cmpwi r0, 0x79
	beq @41
	cmpwi r0, 0x7a
	bne @5
	@41:
	li r3, 0x3e8
	bl irand
	cmpwi r3, 0x1e
	bge @5
	li r3, 0x14
	bl irand
	subfic r25, r3, 0xa
	li r3, 0x14
	bl irand
	addi r0, r3, 0xa
	lis r5, 0x4330
	xoris r3, r25, 0x8000
	stw r5, 0x28(r1)
	lis r4, double_to_int_802cac48@ha
	xoris r0, r0, 0x8000
	stw r3, 0x2c(r1)
	li r3, 0x0
	lfd f5, double_to_int_802cac48@l(r4)
	li r4, 0xa
	lfd f0, 0x28(r1)
	stw r0, 0x34(r1)
	fsubs f1, f0, f5
	lfs f4, 0x3c(r29)
	stw r5, 0x30(r1)
	lfs f2, 0x40(r29)
	lfd f0, 0x30(r1)
	fadds f1, f4, f1
	lfs f3, 0x44(r29)
	fsubs f0, f0, f5
	lfs f4, float_1_8041afa4(r2)
	fadds f2, f2, f0
	bl effHagetakaFlushN64Entry
	@5:
	addi r28, r28, 0x1
	addi r29, r29, 0x98
	@3:
	lwz r0, 0x0(r31)
	cmpw r28, r0
	blt @4
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq @42
	lis r3, work@ha
	addi r30, r3, work@l
	@42:
	lwz r4, 0x4(r30)
	li r5, 0x0
	b @43
	@44:
	lhz r0, 0x0(r4)
	clrlwi. r0, r0, 31
	beq @45
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x6c(r4)
	stw r0, 0x68(r4)
	@45:
	addi r5, r5, 0x1
	addi r4, r4, 0x98
	@43:
	lwz r0, 0x0(r30)
	cmpw r5, r0
	blt @44
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	lmw r25, 0x44(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm BOOL N_itemPickUpFromFieldCheck(void) {
	nofralloc
	lwz r4, gp(r13)
	lis r3, work@ha
	addi r3, r3, work@l
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @1
	addi r3, r3, 0x1c
	@1:
	lwz r0, 0x0(r3)
	lwz r3, 0x4(r3)
	mtctr r0
	cmpwi r0, 0x0
	ble @2
	@3:
	lhz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @4
	lhz r0, 0x24(r3)
	cmplwi r0, 0x2
	bne @4
	li r3, 0x1
	blr
	@4:
	addi r3, r3, 0x98
	bdnz @3
	@2:
	li r3, 0x0
	blr
}

asm BOOL itemGetNokoCheck(ItemEntry* entry) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	bl marioGetPtr
	cmplwi r30, 0x0
	mr r31, r3
	bne @1
	li r3, 0x0
	b @2
	@1:
	lwz r0, 0x38(r30)
	rlwinm. r0, r0, 0, 11, 11
	beq @3
	li r3, 0x0
	b @2
	@3:
	bl marioStGetSystemLevel
	cmplwi r3, 0x0
	beq @4
	li r3, 0x0
	b @2
	@4:
	lwz r0, 0x0(r31)
	andi. r0, r0, 0xa
	beq @5
	li r3, 0x0
	b @2
	@5:
	lwz r0, 0x38(r30)
	rlwinm. r0, r0, 0, 6, 6
	beq @6
	li r3, 0x0
	b @2
	@6:
	lwz r3, gp(r13)
	lwz r0, 0x164(r3)
	cmpwi r0, 0x0
	beq @7
	li r3, 0x0
	b @2
	@7:
	bl seqGetSeq
	cmpwi r3, 0x2
	beq @8
	li r3, 0x0
	b @2
	@8:
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x19
	bne @9
	li r3, 0x0
	b @2
	@9:
	bl vivianGetStatus
	cmpwi r3, 0x0
	beq @10
	li r3, 0x0
	b @2
	@10:
	lhz r3, 0x2e(r31)
	cmplwi r3, 0x1f
	beq @11
	cmplwi r3, 0x20
	bne @12
	@11:
	li r3, 0x0
	b @2
	@12:
	subi r0, r3, 0x5
	clrlwi r0, r0, 16
	cmplwi r0, 0x3
	ble @13
	cmplwi r3, 0xf
	beq @13
	cmplwi r3, 0xe
	bne @14
	@13:
	li r3, 0x0
	b @2
	@14:
	lwz r4, gp(r13)
	lis r3, work@ha
	addi r3, r3, work@l
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @15
	addi r3, r3, 0x1c
	@15:
	lwz r0, 0x0(r3)
	lwz r3, 0x4(r3)
	mtctr r0
	cmpwi r0, 0x0
	ble @16
	@17:
	lhz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @18
	lhz r0, 0x24(r3)
	cmplwi r0, 0x2
	bne @18
	li r3, 0x0
	b @2
	@18:
	addi r3, r3, 0x98
	bdnz @17
	@16:
	bl N_fbatPreventMarioEventChk
	cntlzw r0, r3
	srwi r3, r0, 5
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BOOL itemGetCheck(ItemEntry* entry) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	stw r30, 0x8(r1)
	bl marioGetPtr
	cmplwi r31, 0x0
	mr r30, r3
	bne @1
	li r3, 0x0
	b @2
	@1:
	lwz r0, 0x38(r31)
	rlwinm. r0, r0, 0, 11, 11
	beq @3
	li r3, 0x0
	b @2
	@3:
	lbz r0, 0x3c(r30)
	cmpwi r0, 0x2
	bne @4
	lwz r0, 0x14(r30)
	clrlwi. r0, r0, 31
	bne @5
	bl marioStGetSystemLevel
	cmplwi r3, 0x0
	beq @6
	li r3, 0x0
	b @2
	@6:
	lwz r0, 0x0(r30)
	andi. r0, r0, 0xa
	beq @5
	li r3, 0x0
	b @2
	@4:
	bl marioStGetSystemLevel
	cmplwi r3, 0x0
	beq @7
	li r3, 0x0
	b @2
	@7:
	lwz r0, 0x0(r30)
	andi. r0, r0, 0xa
	beq @5
	li r3, 0x0
	b @2
	@5:
	lwz r3, gp(r13)
	lwz r0, 0x164(r3)
	cmpwi r0, 0x0
	beq @8
	li r3, 0x0
	b @2
	@8:
	bl seqGetSeq
	cmpwi r3, 0x2
	beq @9
	li r3, 0x0
	b @2
	@9:
	lhz r0, 0x2e(r30)
	cmplwi r0, 0x19
	bne @10
	li r3, 0x0
	b @2
	@10:
	cmplwi r0, 0x18
	bne @11
	li r3, 0x0
	b @2
	@11:
	bl vivianGetStatus
	cmpwi r3, 0x0
	beq @12
	li r3, 0x0
	b @2
	@12:
	lhz r0, 0x2e(r30)
	cmplwi r0, 0x1f
	beq @13
	cmplwi r0, 0x20
	bne @14
	@13:
	li r3, 0x0
	b @2
	@14:
	bl nokonoko_holdItem
	cmpwi r3, 0x0
	beq @15
	li r3, 0x0
	b @2
	@15:
	lwz r4, gp(r13)
	lis r3, work@ha
	addi r3, r3, work@l
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @16
	addi r3, r3, 0x1c
	@16:
	lwz r0, 0x0(r3)
	lwz r3, 0x4(r3)
	mtctr r0
	cmpwi r0, 0x0
	ble @17
	@18:
	lhz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @19
	lhz r0, 0x24(r3)
	cmplwi r0, 0x2
	bne @19
	li r3, 0x0
	b @2
	@19:
	addi r3, r3, 0x98
	bdnz @18
	@17:
	bl N_fbatPreventMarioEventChk
	cmpwi r3, 0x0
	beq @20
	li r3, 0x0
	b @2
	@20:
	lhz r0, 0x24(r31)
	cmpwi r0, 0x5
	bge @21
	cmpwi r0, 0x2
	beq @22
	bge @23
	cmpwi r0, 0x1
	bge @24
	b @22
	@21:
	cmpwi r0, 0x7
	beq @24
	bge @22
	lhz r0, 0x26(r31)
	cmplwi r0, 0x0
	beq @22
	lwz r3, 0x38(r31)
	rlwinm. r0, r3, 0, 29, 29
	bne @22
	rlwinm. r0, r3, 0, 28, 28
	bne @22
	li r3, 0x1
	b @2
	@23:
	lwz r0, 0x38(r31)
	rlwinm. r0, r0, 0, 28, 28
	bne @22
	li r3, 0x1
	b @2
	@24:
	li r3, 0x1
	b @2
	@22:
	li r3, 0x0
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void itemCoinDrop(Vec* position) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	bl pouchGetCoin
	cmpwi r3, 0x0
	ble @1
	li r3, -0x1
	bl pouchAddCoin
	lfs f1, 0x0(r31)
	li r3, 0x0
	lfs f2, 0x4(r31)
	li r4, 0x79
	lfs f3, 0x8(r31)
	li r5, 0x8
	li r6, -0x1
	li r7, 0x0
	bl itemEntry
	cmplwi r3, 0x0
	beq @1
	lwz r0, 0x38(r3)
	ori r0, r0, 0x40
	stw r0, 0x38(r3)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void itemReInit(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r3, work@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	addi r31, r3, work@l
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r4, gp(r13)
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq @1
	addi r31, r31, 0x1c
	@1:
	cmpwi r0, 0x0
	bne @2
	lwz r29, 0x4(r31)
	li r30, 0x0
	b @3
	@4:
	lhz r4, 0x0(r29)
	clrlwi. r0, r4, 31
	beq @5
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	bne @5
	lwz r3, 0x4(r29)
	cmpwi r3, 0xf0
	blt @5
	cmpwi r3, 0x153
	bge @5
	rlwinm. r0, r4, 0, 23, 23
	beq @5
	bl pouchArriveBadge
	@5:
	addi r30, r30, 0x1
	addi r29, r29, 0x98
	@3:
	lwz r0, 0x0(r31)
	cmpw r30, r0
	blt @4
	@2:
	lwz r30, 0x4(r31)
	li r29, 0x0
	b @6
	@7:
	addi r3, r30, 0xc
	bl iconDelete
	lhz r0, 0x0(r30)
	addi r3, r30, 0xc
	li r4, 0x0
	li r5, 0x10
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r30)
	bl memset
	addi r29, r29, 0x1
	addi r30, r30, 0x98
	@6:
	lwz r0, 0x0(r31)
	cmpw r29, r0
	blt @7
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void itemInit(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, work@ha
	stw r0, 0x14(r1)
	li r0, 0x20
	addi r5, r3, work@l
	li r3, 0x0
	stw r31, 0xc(r1)
	mulli r4, r0, 0x98
	stw r0, 0x0(r5)
	bl __memAlloc
	lis r5, work@ha
	lwzu r0, work@l(r5)
	li r4, 0x0
	stw r3, 0x4(r5)
	mulli r5, r0, 0x98
	bl memset
	lis r3, work@ha
	li r0, 0x20
	addi r31, r3, work@l
	li r3, 0x0
	mulli r4, r0, 0x98
	stw r3, 0x8(r31)
	li r3, 0x0
	stw r0, 0x1c(r31)
	bl __memAlloc
	lwz r0, 0x1c(r31)
	li r4, 0x0
	stw r3, 0x20(r31)
	mulli r5, r0, 0x98
	bl memset
	li r0, 0x0
	stw r0, 0x24(r31)
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}
// clang-format on
#endif
