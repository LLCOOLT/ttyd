#define pouchGetStarPoint pouchGetStarPoint_hdr
#define pouchAddKpaCoin pouchAddKpaCoin_hdr
#define pouchMajinaiInit pouchMajinaiInit_hdr
#define pouchAddHP pouchAddHP_hdr
#include "mario/mario_pouch.h"
#undef pouchGetStarPoint
#undef pouchAddKpaCoin
#undef pouchMajinaiInit
#undef pouchAddHP
#include "driver/msgdrv.h"
#include "mario/mario_party.h"
#include "evt/evt_badgeshop.h"
#include "evt/evt_yuugijou.h"
#include "data/item_data.h"
#include "memory.h"
#include <string.h>
#ifdef VERSION_G8ME01
#include "mario/mariost.h"
#endif
#include "driver/swdrv.h"

#define CHECK_ITEM(id) pouchCheckItem(id)

extern ItemData itemDataTable[];

PouchData* mpp_gap;
static PouchData* mpp;
extern void qqsort(void* array, s32 num, s32 size, void* compare);
s32 comp_aiueo(const void* a, const void* b);
s32 comp_kind(s16* a, s16* b);

#ifdef VERSION_G8ME01_DEMO
s16 _party_max_hp_table[9][4] = {
#else
s16 _party_max_hp_table[8][4] = {
#endif
	{0, 0, 0, 0},
	{10, 20, 30, 200},
	{10, 15, 25, 200},
	{20, 30, 40, 200},
	{10, 20, 30, 200},
	{15, 25, 35, 200},
	{15, 20, 30, 200},
	{15, 20, 25, 200},
#ifdef VERSION_G8ME01_DEMO
	{0, 0, 0, 0},
#endif
};
s32 comp_aiueo_r(const void* a, const void* b);
s32 comp_kind_r(s16* a, s16* b);

PouchData* pouchGetPtr(void) {
	return mpp;
}

void pouchInit(void) {
	int i;

	// BUG: allocates a new PouchData without checking for or freeing the old one. pouchInit runs at boot
	// (marioInit) and again when a new file starts (stg0_00_init), so the first block is leaked.
	mpp = __memAlloc(HEAP_DEFAULT, sizeof(PouchData));
	memset(mpp, 0, sizeof(PouchData));
	for (i = 0; i < MAX_KEY_ITEMS; i++) {
		mpp->keyItems[i] = ITEM_NULL;
	}
	for (i = 0; i < MAX_HELD_ITEMS; i++) {
		mpp->heldItems[i] = ITEM_NULL;
	}
	for (i = 0; i < MAX_STORED_ITEMS; i++) {
		mpp->storedItems[i] = ITEM_NULL;
	}
	for (i = 0; i < MAX_BADGES; i++) {
		mpp->badges[i] = ITEM_NULL;
	}
	for (i = 0; i < MAX_BADGES; i++) {
		mpp->equippedBadges[i] = ITEM_NULL;
	}
	mpp->maximumHP = 10;
	mpp->baseMaxHP = 10;
	mpp->maximumFP = 5;
	mpp->baseMaxFP = 5;
	mpp->availableBP = 3;
	mpp->maximumBP = 3;
	mpp->currentHP = mpp->maximumHP;
	mpp->currentFP = mpp->maximumFP;
	mpp->currentSP = 0;
	mpp->reserved_7E = 0;
	mpp->maximumSP = 0;
	mpp->reserved_80 = 0;
	mpp->audienceCount = 0.0f;
	mpp->rank = 0;
	mpp->level = 1;
	mpp->jumpLevel = 0;
	mpp->hammerLevel = 0;
	for (i = 0; i < 8; i++) {
		PouchPartyData* party = &mpp->partyData[i];
		if (i != PARTNER_NONE) {
			party->flags = 0;
			party->baseMaxHP = 10;
			party->maximumHP = party->baseMaxHP;
			party->currentHP = party->baseMaxHP;
			party->attackLevel = 0;
			party->techLevel = 0;
		}
	}
#if defined(VERSION_G8MP01)
	strcpy(mpp->yoshiName, "Yoshi");
#elif defined(VERSION_G8ME01)
	strcpy(mpp->yoshiName, msgSearch("name_party3"));
#else
	strcpy(mpp->yoshiName, "チビヨッシー");
#endif
}

ItemType pouchKeyItem(s32 id) {
	return mpp->keyItems[id];
}

ItemType pouchHaveItem(s32 id) {
	return mpp->heldItems[id];
}

ItemType pouchKeepItem(s32 id) {
	return mpp->storedItems[id];
}

ItemType pouchHaveBadge(s32 id) {
	return mpp->badges[id];
}
#ifdef VERSION_G8ME01
ItemType L_pouchEquipBadge(s32 id) {
	return mpp->equippedBadges[id];
}

#endif

s32 pouchGetHaveItemCnt(void) {
	s32 i, count;

	for (count = 0, i = 0; i < MAX_HELD_ITEMS; i++) {
		if (mpp->heldItems[i] != ITEM_NULL) {
			count++;
		}
	}
	return count;
}

s32 pouchGetKeepItemCnt(void) {
	s32 i, count;

	for (count = 0, i = 0; i < MAX_STORED_ITEMS; i++) {
		if (mpp->storedItems[i] != ITEM_NULL) {
			count++;
		}
	}
	return count;
}

s32 pouchGetHaveBadgeCnt(void) {
	s32 i, count;

	for (count = 0, i = 0; i < MAX_BADGES; i++) {
		if (mpp->badges[i] != ITEM_NULL) {
			count++;
		}
	}
	return count;
}

s32 pouchGetEquipBadgeCnt(void) {
	s32 i, count;

	for (count = 0, i = 0; i < MAX_BADGES; i++) {
		if (mpp->equippedBadges[i] != ITEM_NULL) {
			count++;
		}
	}
	return count;
}

s32 pouchGetEmptyHaveItemCnt(void) {
	s32 i, count, max;

	max = CHECK_ITEM(ITEM_STRANGE_SACK) ? MAX_HELD_ITEMS : HELD_ITEM_COUNT_BASE;
	for (count = 0, i = 0; i < max; i++) {
		if (mpp->heldItems[i] == ITEM_NULL) {
			count++;
		}
	}
	return count;
}

s32 pouchGetEmptyKeepItemCnt(void) {
	s32 i, count;

	for (count = 0, i = 0; i < MAX_STORED_ITEMS; i++) {
		if (mpp->storedItems[i] == ITEM_NULL) {
			count++;
		}
	}
	return count;
}

//we have obtained an item, update the appropriate data
static inline BOOL pouchAdd(s16 *t1, s16 *t2, s32 size, ItemType type)
{
  s32 j;
  for (size--; size >= 0; size--)
  {
    if (t1[size] == 0)
    {
      for (j = size; j > 0; j--)
      {
        t1[j] = t1[j - 1];
        if (t2) t2[j] = t2[j - 1];
      }
      t1[0] = type;
      if (t2) t2[0] = 0;
      return 1;
    }
  }
  return 0;
}
BOOL pouchGetItem(ItemType type)
{
  s16 *itemLists[2];
  s32 size;
  BOOL ok;
  if (type == ITEM_COIN)
  {
    if (mpp->coins < 999)
    {
      mpp->coins++;
    }
    return 1;
  }
  if (type == ITEM_PIANTA_TOKEN)
  {
#ifdef VERSION_G8ME01_DEMO
    if (yuwp->tokens < 0x7FFFFFFF) // the demo has no 99999 cap
#else
    if (yuwp->tokens < 99999)
#endif
    {
      yuwp->tokens++;
    }
    return 1;
  }
  if (type == ITEM_HEART)
  {
    size = marioGetParty();
    if (mpp->currentHP < mpp->maximumHP)
    {
      mpp->currentHP++;
    }
    if (size != 0)
    {
      if (mpp->partyData[size].currentHP < mpp->partyData[size].maximumHP)
      {
        mpp->partyData[size].currentHP++;
      }
    }
    return 1;
  }
  if (type == 0x7C)
  {
    if (mpp->currentFP < mpp->maximumFP)
    {
      mpp->currentFP++;
      // FAKE: dead store (function returns right after); steers register allocation
      itemLists[1] = (void *) 0;
    }
    return 1;
  }
  if (type == 0x7D)
  {
    mpp->mStarPieceCount++;
    return 1;
  }
  if (type == 0x57)
  {
    mpp->mShineSpriteCount++;
    return 1;
  }
  if (((type == 6) || (type == 7)) || (type == 8))
  {
    switch (type)
    {
      case 6:
        mpp->jumpLevel = 1;
        break;

      case 7:
        mpp->jumpLevel = 2;
        break;

      case 8:
        mpp->jumpLevel = 3;
        break;

    }

  }
  else
    if (((type == 9) || (type == 10)) || (type == 11))
  {
    switch (type)
    {
      case 9:
        mpp->hammerLevel = 1;
        break;

      case 10:
        mpp->hammerLevel = 2;
        break;

      case 11:
        mpp->hammerLevel = 3;
        break;

    }

  }
  else
    if (type == 0x59)
  {
    return 1;
  }
  else
    if ((type >= 0xF0) && (type < 0x153))
  {
    swSet(type - 0x70);
  }
  size = 0;
  itemLists[0] = (void *) 0;
  itemLists[1] = (void *) 0;
  if ((type >= 0x79) && (type < 0xEC))
  {
    itemLists[0] = mpp->heldItems;
    size = (pouchCheckItem(1)) ? (20) : (10);
    ok = 1;
  }
  else
    if ((type >= 1) && (type < 0x79))
  {
    itemLists[1] = (void *) 0;
    size = 0x79;
    ok = 1;
    itemLists[0] = mpp->keyItems;
  }
  else
    if ((type >= 0xF0) && (type < 0x153))
  {
    size = 200;
    ok = 1;
    itemLists[0] = mpp->badges;
    itemLists[1] = mpp->equippedBadges;
  }
  else
  {
    ok = 0;
  }
  if (!ok)
  {
    return 0;
  }
  return pouchAdd(itemLists[0], itemLists[1], size, type);
}


s32 pouchCheckItem(u32 itemId) {
	s32 id = itemId;
	s32 i;
	u32 itemCnt;

	if (id >= ITEM_MIN && id < ITEM_MAX) {
		itemCnt = 0;
		for (i = 0; i < MAX_HELD_ITEMS; i++) {
			if (id == mpp->heldItems[i]) {
				itemCnt++;
			}
		}
		return itemCnt;
	}
	if (id >= KEY_ITEM_MIN && id < KEY_ITEM_MAX) {
		itemCnt = 0;
		for (i = 0; i < MAX_KEY_ITEMS; i++) {
			if (id == mpp->keyItems[i]) {
				itemCnt++;
			}
		}
		return itemCnt;
	}
	if (id >= BADGE_MIN && id < BADGE_MAX) {
		itemCnt = 0;
		for (i = 0; i < MAX_BADGES; i++) {
			if (id == mpp->badges[i]) {
				itemCnt++;
			}
		}
		return itemCnt;
	}
	return 0;
}

static inline void pouchShift(s16 *table1, s16 *table2, int i, s32 maximum)
{
  table1[i] = ITEM_NULL;
  if (table2 != 0) table2[i] = ITEM_NULL;
  for (; i < maximum - 1; i++)
  {
    table1[i] = table1[i + 1];
    table1[i + 1] = ITEM_NULL;
    if (table2 != 0)
    {
      table2[i] = table2[i + 1];
      table2[i + 1] = ITEM_NULL;
    }
  }
}

BOOL pouchRemoveItem(ItemType type)
{
  s16 *table1;
  s16 *table2;
  BOOL valid;
  s32 maximum;
  int i;
  maximum = 0;
  table1 = (void *) 0;
  table2 = (void *) 0;
  if ((type >= ITEM_COIN) && (type < (ITEM_FRESH_JUICE + 1)))
  {
    table1 = mpp->heldItems;
    table2 = (void *) 0;
    maximum = (pouchCheckItem(ITEM_STRANGE_SACK)) ? (20) : (10);
    valid = 1;
  }
  else
    if ((type >= ITEM_STRANGE_SACK) && (type < (ITEM_CRYSTAL_STAR + 1)))
  {
    table1 = mpp->keyItems;
    table2 = (void *) 0;
    maximum = 121;
    valid = 1;
  }
  else
    if ((type >= ITEM_POWER_JUMP) && (type < (ITEM_SUPER_CHARGE_P + 1)))
  {
    table1 = mpp->badges;
    table2 = mpp->equippedBadges;
    maximum = 200;
    valid = 1;
  }
  else
  {
    valid = 0;
  }
  if (!valid)
  {
    return 0;
  }
  for (i = 0; i < maximum; i++)
  {
    if (type == table1[i])
    {
      pouchShift(table1, table2, i, maximum);
      return 1;
    }
  }

  return 0;
}

#ifdef VERSION_G8ME01_DEMO
// The demo's pouchRemoveItemIndex shifts the second table wrongly: it clears the slot it has just filled
// instead of the one it moved from.
static inline void pouchShiftIndex(s16* table1, s16* table2, int i, s32 maximum) {
  table1[i] = ITEM_NULL;
  if (table2 != 0) table2[i] = ITEM_NULL;
  for (; i < maximum - 1; i++)
  {
    table1[i] = table1[i + 1];
    table1[i + 1] = ITEM_NULL;
    if (table2 != 0)
    {
      table2[i] = table2[i + 1];
      table2[i] = ITEM_NULL;
    }
  }
}
#else
#define pouchShiftIndex pouchShift
#endif

BOOL pouchRemoveItemIndex(ItemType type, s32 index) {
	s16* table1, * table2, * p;
	BOOL valid;
	s32 maximum;
	int i;

	maximum = 0;
	table1 = NULL;
	table2 = NULL;
	if (type >= ITEM_MIN && type < ITEM_MAX) {
		table1 = mpp->heldItems;
		table2 = NULL;
		maximum = CHECK_ITEM(ITEM_STRANGE_SACK) ? MAX_HELD_ITEMS : HELD_ITEM_COUNT_BASE;
		valid = TRUE;
	}
	else if (type >= KEY_ITEM_MIN && type < KEY_ITEM_MAX) {
		table1 = mpp->keyItems;
		table2 = NULL;
		maximum = 121;
		valid = TRUE;
	}
	else if (type >= BADGE_MIN && type < BADGE_MAX) {
		table1 = mpp->badges;
		table2 = mpp->equippedBadges;
		maximum = 200;
		valid = TRUE;
	}
	else {
		valid = FALSE;
	}
	if (!valid) {
		return FALSE;
	}
	p = &table1[index];
	if (type != *p) {
		return FALSE;
	}
	for (i = index; i < maximum; p++, i++) {
		if (type == *p) {
			pouchShiftIndex(table1, table2, i, maximum);
			return TRUE;
		}
	}
	return FALSE;
}

#ifdef VERSION_G8MP01
char* strupr(char* str);
#endif

#ifndef VERSION_G8ME01_DEMO
void pouchHiraToKata(const char* src, char* dst) {
	u16 c;
	s32 len = strlen(src) / 2;
#ifdef VERSION_G8ME01
	u16* s;
	u16* d;
#else
	u16* s = (u16*)src;
	u16* d = (u16*)dst;
#endif
	s32 i;
#ifdef VERSION_G8ME01
	if ((u32)gp->language == 0) {
		s = (u16*)src;
		d = (u16*)dst;
		for (i = 0; i < len; i++) {
			c = *s;
			if (c >= 0x829F && c < 0x82DE) {
				c += 0xA1;
			}
			else if (c >= 0x82DE && c <= 0x82F1) {
				c += 0xA2;
			}
			*d = c;
			s++;
			d++;
		}
		dst[i * 2] = 0;
	} else {
#ifdef VERSION_G8MP01
		// PAL: sort key of a Latin name: drops <...> message tags, upper-cases, folds accented vowels to
		// A E I O U, spells the OE ligature out and drops C-cedilla
		char buf[0x400];
		char* key = dst;
		BOOL inTag = FALSE;
		s32 n;

		for (; *(s8*)src; src++) {
			switch (*(s8*)src) {
			case '<':
				inTag = TRUE;
				break;
			case '>':
				inTag = FALSE;
				break;
			default:
				if (!inTag) {
					*dst = *(s8*)src;
					*++dst = 0;
				}
				break;
			}
		}
		strupr(key);
		for (i = 0; i < strlen(key); i++) {
			u8 ch = key[i];
			if ((ch >= 0xC0 && ch <= 0xC6) || (ch >= 0xE0 && ch <= 0xE6)) {
				ch = 'A';
			} else if ((ch >= 0xC8 && ch <= 0xCB) || (ch >= 0xE8 && ch <= 0xEB)) {
				ch = 'E';
			} else if ((ch >= 0xCC && ch <= 0xCF) || (ch >= 0xEC && ch <= 0xEF)) {
				ch = 'I';
			} else if ((ch >= 0xD2 && ch <= 0xD6) || (ch >= 0xF2 && ch <= 0xF6)) {
				ch = 'O';
			} else if ((ch >= 0xD9 && ch <= 0xDC) || (ch >= 0xF9 && ch <= 0xFC)) {
				ch = 'U';
			}
			key[i] = ch;
		}
		n = 0;
		for (i = 0; i < strlen(key); i++) {
			u8 ch = key[i];
			if (ch == 0x8C || ch == 0x9C) {
				buf[n++] = 'O';
				buf[n++] = 'E';
			} else if (ch != 0xC7 && ch != 0xE7) {
				buf[n++] = ch;
			}
			buf[n] = 0;
		}
		strcpy(key, buf);
#else
		strcpy(dst, src);
#endif
	}
}
#else
	for (i = 0; i < len; i++) {
		c = *s;
		if (c >= 0x829F && c < 0x82DE) {
			c += 0xA1;
		}
		else if (c >= 0x82DE && c <= 0x82F1) {
			c += 0xA2;
		}
		*d = c;
		s++;
		d++;
	}
	dst[i * 2] = 0;
}
#endif

#endif

#ifdef VERSION_G8MP01
#define pouchAiueoConv pouchHiraToKata
#else
static inline void pouchAiueoConv(const char* src, char* dst) {
#ifdef VERSION_G8ME01
	u16* s;
	u16* d;
	s32 len = strlen(src) / 2;
	u16 c;
	s32 i;
#else
	u16* s = (u16*)src;
	s32 len = strlen(src) / 2;
	u16* d = (u16*)dst;
	u16 c;
	s32 i;
#endif
#ifdef VERSION_G8ME01
	if ((u32)gp->language == 0) {
		s = (u16*)src;
		d = (u16*)dst;
		for (i = 0; i < len; i++) {
			c = *s;
			if (c >= 0x829F && c < 0x82DE) {
				c += 0xA1;
			}
			else if (c >= 0x82DE && c <= 0x82F1) {
				c += 0xA2;
			}
			*d = c;
			s++;
			d++;
		}
		dst[i * 2] = 0;
	} else {
		strcpy(dst, src);
	}
}
#else
	for (i = 0; i < len; i++) {
		c = *s;
		if (c >= 0x829F && c < 0x82DE) {
			c += 0xA1;
		}
		else if (c >= 0x82DE && c <= 0x82F1) {
			c += 0xA2;
		}
		*d = c;
		s++;
		d++;
	}
	dst[i * 2] = 0;
}
#endif
#endif

#ifdef VERSION_G8ME01_DEMO
// The demo compares the item names as they are, without the kana conversion.
s32 comp_aiueo(const void* a, const void* b) {
	s16 ia = *(s16*)a;
	s16 ib = *(s16*)b;
	s32 r = strcmp(msgSearch(itemDataTable[ia].name), msgSearch(itemDataTable[ib].name));
	if (r > 0) return 1;
	return -(r < 0);
}
#else
s32 comp_aiueo(const void* a, const void* b) {
	char bufA[0x80];
	char bufB[0x80];
	s16 ia = *(s16*)a;
	s16 ib = *(s16*)b;

	pouchAiueoConv(msgSearch(itemDataTable[ia].name), bufA);
	pouchAiueoConv(msgSearch(itemDataTable[ib].name), bufB);
	return strcmp(bufA, bufB);
}
#endif

s32 comp_kind(s16* a, s16* b) {
	s16 x = itemDataTable[*a].type_sort_order;
	s16 y = itemDataTable[*b].type_sort_order;
	if (x > y) return 1;
	return -(x < y);
}

#ifdef VERSION_G8ME01_DEMO
s32 comp_aiueo_r(const void* a, const void* b) {
	s16 ia = *(s16*)a;
	s16 ib = *(s16*)b;
	s32 r = strcmp(msgSearch(itemDataTable[ia].name), msgSearch(itemDataTable[ib].name));
	if (r < 0) return 1;
	return -(r > 0);
}
#else
s32 comp_aiueo_r(const void* a, const void* b) {
	char bufA[0x80];
	char bufB[0x80];
	s16 ia = *(s16*)a;
	s16 ib = *(s16*)b;

	pouchAiueoConv(msgSearch(itemDataTable[ia].name), bufA);
	pouchAiueoConv(msgSearch(itemDataTable[ib].name), bufB);
	return strcmp(bufB, bufA);
}
#endif

s32 comp_kind_r(s16* a, s16* b) {
	s16 x = itemDataTable[*a].type_sort_order;
	s16 y = itemDataTable[*b].type_sort_order;
	if (x < y) return 1;
	return -(x > y);
}

void pouchSortItem(s32 mode) {
	s32 k;
	s16 items[20];
	s16 keys[121];
	s16 badges[200];
	s16 equipped[200];
	s32 n, i, j;
	BOOL swap;
	s16 t2, t1;
	PouchData* pp[1];
#if defined(VERSION_G8MP01)
	char keyA[0x80];
	s16 bj;
	s32 l;
	s32 count;
	const char* ida;
	const char* idb;
	s32 ca;
	s32 cb;
	s16 bn;
	char keyB[0x80];
#elif defined(VERSION_G8ME01)
	s16 bn;
	s16 bj;
	const char* idb;
	s32 ca;
	s32 cb;
	ItemData* a;
	ItemData* b;
	s32 m;
	s32 l;
	s32 count;
	const char* ida;
#endif

	pp[0] = mpp;
	if ((u32)mode <= 1 || mode == 7 || mode == 8) {
		n = 0;
		for (j = 0; j < 20; j++) {
			if (pp[0]->heldItems[j] != 0) {
				items[n++] = pp[0]->heldItems[j];
			}
		}
		for (k = n; k < 20; k++) {
			items[k] = 0;
		}
		if (mode == 0) qqsort(items, n, 2, comp_aiueo);
		else if (mode == 1) qqsort(items, n, 2, comp_kind);
		else if (mode == 7) qqsort(items, n, 2, comp_aiueo_r);
		else if (mode == 8) qqsort(items, n, 2, comp_kind_r);
		memcpy(pp[0]->heldItems, items, sizeof(items));
	}
	if ((u32)(mode - 2) <= 1 || mode == 9 || mode == 10) {
		n = 0;
		for (j = 0; j < 121; j++) {
			if (pp[0]->keyItems[j] != 0) {
				keys[n++] = pp[0]->keyItems[j];
			}
		}
		for (k = n; k < 121; k++) {
			keys[k] = 0;
		}
		if (mode == 2) qqsort(keys, n, 2, comp_aiueo);
		else if (mode == 3) qqsort(keys, n, 2, comp_kind);
		else if (mode == 9) qqsort(keys, n, 2, comp_aiueo_r);
		else if (mode == 10) qqsort(keys, n, 2, comp_kind_r);
		memcpy(pp[0]->keyItems, keys, sizeof(keys));
	}
#if defined(VERSION_G8MP01)
	if ((u32)(mode - 4) <= 2 || (u32)(mode - 11) <= 1 || mode == 13) {
		count = 0;
		for (n = 0; n < 200; n++) {
			if (pp[0]->badges[n] != 0) {
				badges[count] = pp[0]->badges[n];
				count++;
				equipped[count - 1] = pp[0]->equippedBadges[n];
			}
		}
		for (n = count; n < 200; n++) {
			badges[n] = 0;
			equipped[n] = 0;
		}
		for (j = 0; j < count - 1; j++) {
			for (l = j + 1; l < count; l++) {
				BOOL swap;
				bn = badges[j];
				bj = badges[l];
				ida = msgSearch(itemDataTable[bn].name);
				idb = msgSearch(itemDataTable[bj].name);
				ca = itemDataTable[bn].bp_cost;
				cb = itemDataTable[bj].bp_cost;
				swap = FALSE;
				pouchHiraToKata(ida, keyA);
				pouchHiraToKata(idb, keyB);
				ida = keyA;
				idb = keyB;
				if (mode == 4) {
					if (strcmp(ida, idb) > 0) swap = TRUE;
				} else if (mode == 11) {
					if (strcmp(ida, idb) < 0) swap = TRUE;
				} else if (mode == 5) {
					if (itemDataTable[bn].type_sort_order > itemDataTable[bj].type_sort_order) swap = TRUE;
				} else if (mode == 12) {
					if (itemDataTable[bn].type_sort_order < itemDataTable[bj].type_sort_order) swap = TRUE;
				} else if (mode == 6) {
					if (ca > cb) swap = TRUE;
					else if (ca == cb && itemDataTable[bn].type_sort_order > itemDataTable[bj].type_sort_order) swap = TRUE;
				} else if (mode == 13) {
					if (ca < cb) swap = TRUE;
					else if (ca == cb && itemDataTable[bn].type_sort_order < itemDataTable[bj].type_sort_order) swap = TRUE;
				}
				if (swap) {
					t1 = badges[j];
					t2 = equipped[j];
					badges[j] = badges[l];
					equipped[j] = equipped[l];
					badges[l] = t1;
					equipped[l] = t2;
				}
			}
		}
		memcpy(pp[0]->badges, badges, sizeof(badges));
		memcpy(pp[0]->equippedBadges, equipped, sizeof(equipped));
	}
#elif defined(VERSION_G8ME01)
	if ((u32)(mode - 4) <= 2 || (u32)(mode - 11) <= 1 || mode == 13) {
		count = 0;
		for (n = 0; n < 200; n++) {
			if (pp[0]->badges[n] != 0) {
				badges[count] = pp[0]->badges[n];
				count++;
				equipped[count - 1] = pp[0]->equippedBadges[n];
			}
		}
		for (n = count; n < 200; n++) {
			badges[n] = 0;
			equipped[n] = 0;
		}
		for (m = 0; m < count - 1; m++) {
			for (l = m + 1; l < count; l++) {
				BOOL swap;
				bn = badges[m];
				bj = badges[l];
				a = &itemDataTable[bn];
				ida = msgSearch(a->name);
				b = &itemDataTable[bj];
				idb = msgSearch(b->name);
				ca = a->bp_cost;
				cb = b->bp_cost;
				swap = FALSE;
				if (mode == 4) {
					if (strcmp(ida, idb) > 0) swap = TRUE;
				} else if (mode == 11) {
					if (strcmp(ida, idb) < 0) swap = TRUE;
				} else if (mode == 5) {
					if (a->type_sort_order > b->type_sort_order) swap = TRUE;
				} else if (mode == 12) {
					if (a->type_sort_order < b->type_sort_order) swap = TRUE;
				} else if (mode == 6) {
					if (ca > cb) swap = TRUE;
					else if (ca == cb && a->type_sort_order > b->type_sort_order) swap = TRUE;
				} else if (mode == 13) {
					if (ca < cb) swap = TRUE;
					else if (ca == cb && a->type_sort_order < b->type_sort_order) swap = TRUE;
				}
				if (swap) {
					t1 = badges[m];
					t2 = equipped[m];
					badges[m] = badges[l];
					equipped[m] = equipped[l];
					badges[l] = t1;
					equipped[l] = t2;
				}
			}
		}
		memcpy(pp[0]->badges, badges, sizeof(badges));
		memcpy(pp[0]->equippedBadges, equipped, sizeof(equipped));
	}
#else
	if ((u32)(mode - 4) <= 2 || (u32)(mode - 11) <= 1 || mode == 13) {
		i = 0;
		for (n = 0; n < 200; n++) {
			if (pp[0]->badges[n] != 0) {
				badges[i] = pp[0]->badges[n];
				i++;
				equipped[i - 1] = pp[0]->equippedBadges[n];
			}
		}
		for (n = i; n < 200; n++) {
			badges[n] = 0;
			equipped[n] = 0;
		}
		for (n = 0; n < i - 1; n++) {
			for (j = n + 1; j < i; j++) {
				ItemData* a = &itemDataTable[badges[n]];
				ItemData* b = &itemDataTable[badges[j]];
				s32 ca = a->bp_cost;
				s32 cb = b->bp_cost;
				const char* ida = a->id;
				const char* idb = b->id;
				swap = FALSE;
				if (mode == 4) {
					if (strcmp(ida, idb) > 0) swap = TRUE;
				} else if (mode == 11) {
					if (strcmp(ida, idb) < 0) swap = TRUE;
				} else if (mode == 5) {
					if (a->type_sort_order > b->type_sort_order) swap = TRUE;
				} else if (mode == 12) {
					if (a->type_sort_order < b->type_sort_order) swap = TRUE;
#ifdef VERSION_G8ME01_DEMO
				// The demo sorts by BP cost alone, with no tie-break on the sort order.
				} else if (mode == 6) {
					if (ca > cb) swap = TRUE;
				} else if (mode == 13) {
					if (ca < cb) swap = TRUE;
				}
#else
				} else if (mode == 6) {
					if (ca > cb) swap = TRUE;
					else if (ca == cb && a->type_sort_order > b->type_sort_order) swap = TRUE;
				} else if (mode == 13) {
					if (ca < cb) swap = TRUE;
					else if (ca == cb && a->type_sort_order < b->type_sort_order) swap = TRUE;
				}
#endif
				if (swap) {
					t1 = badges[n];
					t2 = equipped[n];
					badges[n] = badges[j];
					equipped[n] = equipped[j];
					badges[j] = t1;
					equipped[j] = t2;
				}
			}
#ifdef VERSION_G8ME01_DEMO
			// The demo copies the lists back after every pass of the outer loop.
			memcpy(pp[0]->badges, badges, sizeof(badges));
			memcpy(pp[0]->equippedBadges, equipped, sizeof(equipped));
		}
#else
		}
		memcpy(pp[0]->badges, badges, sizeof(badges));
		memcpy(pp[0]->equippedBadges, equipped, sizeof(equipped));
#endif
	}
#endif
}

s32 pouchGetCoin(void) {
	return mpp->coins;
}

s16 pouchAddCoin(s16 coins) {
	mpp->coins += coins;
	if (mpp->coins < 0) {
		mpp->coins = 0;
	}
	if (mpp->coins > 999) {
		mpp->coins = 999;
	}
	return mpp->coins;
}

s32 pouchSetCoin(s32 coins) {
	mpp->coins = coins;
	if (mpp->coins < 0) {
		mpp->coins = 0;
	}
	if (mpp->coins > 999) {
		mpp->coins = 999;
	}
	return mpp->coins;
}

s32 pouchGetSuperCoin(void) {
	return mpp->mShineSpriteCount;
}

s16 pouchSetSuperCoin(s16 count) {
	mpp->mShineSpriteCount = count;
	return mpp->mShineSpriteCount;
}

s32 pouchGetStarPiece(void) {
	return mpp->mStarPieceCount;
}

s16 pouchAddStarPiece(s16 count) {
	mpp->mStarPieceCount += count;
	return mpp->mStarPieceCount;
}

s16 pouchAddHP(s32 points) {
	mpp->currentHP += (s16)points;
	if (mpp->currentHP < 0) {
		mpp->currentHP = 0;
	}
	if (mpp->currentHP > mpp->maximumHP) {
		mpp->currentHP = mpp->maximumHP;
	}
	return mpp->currentHP;
}

s32 pouchGetHP(void) {
	return mpp->currentHP;
}

s16 pouchGetMaxHP(void) {
	return mpp->maximumHP;
}

void pouchSetHP(s16 points) {
	mpp->currentHP = points;
	if (mpp->currentHP > mpp->maximumHP) {
		mpp->currentHP = mpp->maximumHP;
	}
}

void pouchSetMaxHP(s16 points) {
	mpp->maximumHP = points;
	mpp->baseMaxHP = mpp->maximumHP;
}

s32 pouchGetPartyHP(PartyId partnerId) {
	return mpp->partyData[partnerId].currentHP;
}

void pouchSetPartyHP(PartyId partnerId, s16 points) {
	PouchPartyData* party;

	mpp->partyData[partnerId].currentHP = points;
	party = &mpp->partyData[partnerId];
	if (party->currentHP > party->maximumHP) {
		party->currentHP = party->maximumHP;
	}
}

s32 pouchGetFP(void) {
	return mpp->currentFP;
}

s16 pouchGetMaxFP(void) {
	return mpp->maximumFP;
}

void pouchSetFP(s16 points) {
	mpp->currentFP = points;
	if (mpp->currentFP > mpp->maximumFP) {
		mpp->currentFP = mpp->maximumFP;
	}
}

void pouchSetMaxFP(s16 points) {
	mpp->maximumFP = points;
	mpp->baseMaxFP = mpp->maximumFP;
}

s32 pouchGetAP(void) {
	return mpp->currentSP;
}

void pouchAddAP(s16 points) {
	mpp->currentSP += points;
	if (mpp->currentSP < 0) {
		mpp->currentSP = 0;
	}
	if (mpp->currentSP > mpp->maximumSP) {
		mpp->currentSP = mpp->maximumSP;
	}
}

void pouchSetAP(s16 points) {
	mpp->currentSP = points;
	if (mpp->currentSP < 0) {
		mpp->currentSP = 0;
	}
	if (mpp->currentSP > mpp->maximumSP) {
		mpp->currentSP = mpp->maximumSP;
	}
}

s16 pouchGetMaxAP(void) {
	return mpp->maximumSP;
}

f32 pouchGetAudienceNum(void) {
	return mpp->audienceCount;
}

void pouchSetAudienceNum(f32 num) {
	mpp->audienceCount = num;
}

s32 pouchGetJumpLv(void) {
	s32 level = 0;

	if (CHECK_ITEM(ITEM_ULTRA_BOOTS)) {
		level = 3;
	}
	else if (CHECK_ITEM(ITEM_SUPER_BOOTS)) {
		level = 2;
	}
	else if (CHECK_ITEM(ITEM_BOOTS)) {
		level = 1;
	}
	mpp->jumpLevel = level;
	return mpp->jumpLevel;
}

s32 pouchGetHammerLv(void) {
	s32 level = 0;

	if (CHECK_ITEM(ITEM_ULTRA_HAMMER)) {
		level = 3;
	}
	else if (CHECK_ITEM(ITEM_SUPER_HAMMER)) {
		level = 2;
	}
	else if (CHECK_ITEM(ITEM_HAMMER)) {
		level = 1;
	}
	mpp->hammerLevel = level;
	return mpp->hammerLevel;
}

s32 pouchGetPartyAttackLv(PartyId partyId) {
	PouchPartyData* party = &mpp->partyData[partyId];
	return party->attackLevel;
}

#ifdef VERSION_G8ME01_DEMO
// The demo stores into the first empty slot and removes by id alone, without shifting the list.
BOOL pouchAddKeepItem(s16 id) {
	s32 i;

	for (i = 0; i < MAX_STORED_ITEMS; i++) {
		if (mpp->storedItems[i] == 0) {
			break;
		}
	}
	if (i < MAX_STORED_ITEMS) {
		mpp->storedItems[i] = id;
		return TRUE;
	}
	return FALSE;
}

BOOL pouchRemoveKeepItem(s32 id) {
	s32 i;

	for (i = 0; i < MAX_STORED_ITEMS; i++) {
		if (mpp->storedItems[i] == id) {
			break;
		}
	}
	if (i < MAX_STORED_ITEMS) {
		mpp->storedItems[i] = 0;
		return TRUE;
	}
	return FALSE;
}
#else
BOOL pouchAddKeepItem(s16 id) {
	s32 i, j;

	for (i = MAX_STORED_ITEMS - 1; i >= 0; i--) {
		if (mpp->storedItems[i] == 0) {
			for (j = i; j > 0; j--) {
				mpp->storedItems[j] = mpp->storedItems[j - 1];
			}
			mpp->storedItems[0] = id;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL pouchRemoveKeepItem(s32 id, s32 index) {
	s32 i, j;

	if (mpp->storedItems[index] != id) {
		return FALSE;
	}
	for (i = index; i < MAX_STORED_ITEMS; i++) {
		if (mpp->storedItems[i] == id) {
			mpp->storedItems[i] = 0;
			for (j = i; j < MAX_STORED_ITEMS - 1; j++) {
				mpp->storedItems[j] = mpp->storedItems[j + 1];
				mpp->storedItems[j + 1] = 0;
			}
			return TRUE;
		}
	}
	return FALSE;
}
#endif

void pouchReviseMarioParam(void) {
	int i;

	mpp->maximumHP = mpp->baseMaxHP;
	mpp->maximumFP = mpp->baseMaxFP;

	for (i = 0; i < 200; i++) {
		if (!mpp->equippedBadges[i]) continue;
		switch (mpp->equippedBadges[i]) {
			case ITEM_HP_PLUS:
				mpp->maximumHP += 5;
				break;
			case ITEM_FP_PLUS:
				mpp->maximumFP += 5;
				break;
		}
	}
	if (mpp->currentHP > mpp->maximumHP) {
		mpp->currentHP = mpp->maximumHP;
	}
	if (mpp->currentFP > mpp->maximumFP) {
		mpp->currentFP = mpp->maximumFP;
	}
	mpp->availableBP = mpp->maximumBP;

	for (i = 0; i < 200; i++) {
		mpp->availableBP -= itemDataTable[mpp->equippedBadges[i]].bp_cost;
	}
}

#pragma push
void pouchRevisePartyParam(void) {
	PouchPartyData* party;
	int count, i;

	count = pouchEquipCheckBadge(ITEM_HP_PLUS_P);

	for (i = 0; i < 8; i++) { //TODO: NUM_PARTNERS macro
		if (i != PARTNER_NONE) {
			party = &mpp->partyData[i];
			party->baseMaxHP = _party_max_hp_table[i][party->HPLevel];
			party->maximumHP = (s16)(party->baseMaxHP + (count * 5));
			if (party->currentHP > party->maximumHP) {
				party->currentHP = party->maximumHP;
			}
		}
	}
}
#pragma pop

s16 pouchGetStarPoint(void) {
	return mpp->mStarPoints;
}

BOOL pouchEquipBadgeIndex(s32 index) {
	if (mpp->badges[index] == 0) {
		return FALSE;
	}
	mpp->equippedBadges[index] = mpp->badges[index];
	return TRUE;
}

BOOL pouchUnEquipBadgeIndex(s32 index) {
	if (mpp->equippedBadges[index] == 0) {
		return FALSE;
	}
	mpp->equippedBadges[index] = 0;
	return TRUE;
}

s32 pouchEquipCheckBadge(s32 badgeId) {
	int i, count;

	count = 0;
	for (i = 0; i < 200; i++) {
		if (badgeId == mpp->equippedBadges[i]) {
			count++;
		}
	}
	return count;
}

BOOL pouchEquipCheckBadgeIndex(s32 index) {
	return mpp->equippedBadges[index] != 0;
}

BOOL pouchEquipBadgeID(s32 badgeId) {
	int i;

	for (i = 0; i < 200; i++) {
		if (mpp->badges[i] == badgeId) {
			if (mpp->badges[i]) {
				mpp->equippedBadges[i] = mpp->badges[i];
			}
			return TRUE;
		}
	}
	return FALSE;
}

#ifndef VERSION_G8ME01_DEMO
BOOL N_pouchUnEquipBadgeID(s32 badgeId) {
	int i;

	for (i = 0; i < 200; i++) {
		if (mpp->equippedBadges[i] == badgeId) {
			if (mpp->equippedBadges[i]) {
				mpp->equippedBadges[i] = 0;
			}
			return TRUE;
		}
	}
	return FALSE;
}

#endif

s32 pouchArriveBadge(s32 id) {
#ifdef VERSION_G8ME01_DEMO
	// The demo stocks an arriving badge in the bargain table.
	return badgeShop_add(bdsw->bargain_table, (s16)id, 1);
#else
	return badgeShop_add(bdsw->special_table, (s16)id, 1);
#endif
}

void pouchMajinaiInit(s32 curseCount) {
	if (mpp->mMerleeCurseUsesRemaining < curseCount) {
		mpp->mMerleeCurseUsesRemaining = (u8)curseCount;
		mpp->mTurnsUntilMerleeActivation = -1;
		mpp->mMerleeNextCurseType = 0;
	}
}

s32 pouchGetKpaCoin(void) {
	return mpp->mSuperBowserCoins;
}

BOOL pouchAddKpaCoin(u8 coins) {
	BOOL ret = FALSE;
	mpp->mSuperBowserCoins += coins;
	if (mpp->mSuperBowserCoins >= 100) {
		mpp->mSuperBowserCoins -= 100;
		ret = TRUE;
	}
	return ret;
}

u32 pouchGetKpaScore(void) {
	return mpp->mSuperBowserScore;
}

void pouchAddKpaScore(u32 score) {
	mpp->mSuperBowserScore += score;
	if (mpp->mSuperBowserScore > 999999)
	{
		mpp->mSuperBowserScore = 999999;
	}
}

void pouchGetStarStone(u32 id) {
	u16* sp = &mpp->mStarPowersObtained;
	if (!*sp) {
		mpp->audienceCount = 2.0f;
	}
	mpp->mStarPowersObtained |= 1 << id;
	mpp->maximumSP = (s16)(100 * (id + 1));
	if (mpp->maximumSP < 0) {
		mpp->maximumSP = 0;
	}
	if (mpp->maximumSP > 800) {
		mpp->maximumSP = 800;
	}
}

s32 pouchReceiveMailCount(void) {
	s32 i, count;

	for (count = 0, i = 0; i < 99; i++) {
		if (mpp->mEmailReceivedFlags[i / 32] & (1 << (i % 32))) {
			count++;
		}
	}
	return count;
}

void pouchReceiveMail(s32 mailId) {
	s32 count;
	s32 index, shift;

	index = mailId / 32;
	shift = mailId % 32;
	count = pouchReceiveMailCount();
	mpp->mEmailReceivedFlags[index] |= (1 << shift);
	mpp->mEmailIds[count] = (u8)mailId;
}

void pouchOpenMail(s32 mailId) {
	mpp->mEmailReadFlags[mailId / 32] |= (1 << (mailId % 32));
}

u32 pouchCheckMail(s32 mailId) {
	s32 mask = (1 << (mailId % 32));
	if (mpp->mEmailReadFlags[mailId / 32] & mask) {
		return 2;
	}
	else {
		return (mpp->mEmailReceivedFlags[mailId / 32] & mask) != 0;
	}
}

s32 pouchGetPartyColor(PartyId partnerId) {
	return mpp->partyData[partnerId].flags >> 13;
}

void pouchSetPartyColor(PartyId partnerId, s32 color) {
	mpp->partyData[partnerId].flags = (mpp->partyData[partnerId].flags & 0x1FFF) | (u16)(color << 13);
}

void pouchSetYoshiName(char* name) {
	strcpy(mpp->yoshiName, name);
}

char* pouchGetYoshiName(void) {
	if (strlen(mpp->yoshiName) < 1) {
		return (char*)msgSearch("name_party3");
	}
	return mpp->yoshiName;
}
//
//
//
//

// prototypes for asm stopgap forward references
char* pouchGetYoshiName(void);
void pouchSetYoshiName(char* name);
void pouchSetPartyColor(PartyId partnerId, s32 color);
s32 pouchGetPartyColor(PartyId partnerId);
u32 pouchCheckMail(s32 mailId);
void pouchOpenMail(s32 mailId);
void pouchReceiveMail(s32 mailId);
s32 pouchReceiveMailCount(void);
void pouchGetStarStone(u32 id);
void pouchAddKpaScore(u32 score);
u32 pouchGetKpaScore(void);
BOOL pouchAddKpaCoin(u8 coins);
s32 pouchGetKpaCoin(void);
void pouchMajinaiInit(s32 curseCount);
s32 pouchArriveBadge(s32 id);
BOOL N_pouchUnEquipBadgeID(s32 badgeId);
BOOL pouchEquipBadgeID(s32 badgeId);
BOOL pouchEquipCheckBadgeIndex(s32 index);
s32 pouchEquipCheckBadge(s32 badgeId);
BOOL pouchUnEquipBadgeIndex(s32 index);
BOOL pouchEquipBadgeIndex(s32 index);
s16 pouchGetStarPoint(void);
void pouchRevisePartyParam(void);
void pouchReviseMarioParam(void);
#ifdef VERSION_G8ME01_DEMO
BOOL pouchRemoveKeepItem(s32 id);
#else
BOOL pouchRemoveKeepItem(s32 id, s32 index);
#endif
BOOL pouchAddKeepItem(s16 id);
s32 pouchGetPartyAttackLv(PartyId partyId);
s32 pouchGetHammerLv(void);
s32 pouchGetJumpLv(void);
void pouchSetAudienceNum(f32 num);
f32 pouchGetAudienceNum(void);
s16 pouchGetMaxAP(void);
void pouchSetAP(s16 points);
void pouchAddAP(s16 points);
s32 pouchGetAP(void);
void pouchSetMaxFP(s16 points);
void pouchSetFP(s16 points);
s16 pouchGetMaxFP(void);
s32 pouchGetFP(void);
void pouchSetPartyHP(PartyId partnerId, s16 points);
s32 pouchGetPartyHP(PartyId partnerId);
void pouchSetMaxHP(s16 points);
void pouchSetHP(s16 points);
s16 pouchGetMaxHP(void);
s32 pouchGetHP(void);
s16 pouchAddHP(s32 points);
s16 pouchAddStarPiece(s16 count);
s32 pouchGetStarPiece(void);
s16 pouchSetSuperCoin(s16 count);
s32 pouchGetSuperCoin(void);
s32 pouchSetCoin(s32 coins);
s16 pouchAddCoin(s16 coins);
s32 pouchGetCoin(void);
void pouchSortItem(s32 mode);
s32 comp_kind_r(s16* a, s16* b);
s32 comp_aiueo_r(const void* a, const void* b);
s32 comp_kind(s16* a, s16* b);
s32 comp_aiueo(const void* a, const void* b);
void pouchHiraToKata(const char* src, char* dst);
BOOL pouchRemoveItemIndex(ItemType type, s32 index);
BOOL pouchRemoveItem(ItemType type);
s32 pouchCheckItem(u32 itemId);
BOOL pouchGetItem(ItemType type);
s32 pouchGetEmptyKeepItemCnt(void);
s32 pouchGetEmptyHaveItemCnt(void);
s32 pouchGetEquipBadgeCnt(void);
s32 pouchGetHaveBadgeCnt(void);
s32 pouchGetKeepItemCnt(void);
s32 pouchGetHaveItemCnt(void);
ItemType pouchHaveBadge(s32 id);
ItemType pouchKeepItem(s32 id);
ItemType pouchHaveItem(s32 id);
ItemType pouchKeyItem(s32 id);
void pouchInit(void);
PouchData* pouchGetPtr(void);
