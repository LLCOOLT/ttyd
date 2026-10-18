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
extern const char str_802CE170[];

#define CHECK_ITEM(id) ((s32 (*)(s32))pouchCheckItem)(id)

extern PiantaParlorWork* yuwp;
extern BadgeShopWork* bdsw;
extern ItemData itemDataTable[];

PouchData* mpp_gap;
static PouchData* mpp;
extern void qqsort(void* array, s32 num, s32 size, void* compare);
s32 comp_aiueo(const void* a, const void* b);
s32 comp_kind(s16* a, s16* b);

s16 _party_max_hp_table[8][4] = {
	{0, 0, 0, 0},
	{10, 20, 30, 200},
	{10, 15, 25, 200},
	{20, 30, 40, 200},
	{10, 20, 30, 200},
	{15, 25, 35, 200},
	{15, 20, 30, 200},
	{15, 20, 25, 200}
};
s32 comp_aiueo_r(const void* a, const void* b);
s32 comp_kind_r(s16* a, s16* b);

#ifdef NONMATCHING
PouchData* pouchGetPtr(void) {
	return mpp;
}
#endif

#ifdef NONMATCHING
void pouchInit(void) {
	int i;

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
	mpp->field_0x7E = 0;
	mpp->maximumSP = 0;
	mpp->field_0x80 = 0;
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
	strcpy(mpp->yoshiName, "チビヨッシー\0\0\0"); //TODO: US
}
#endif

#ifdef NONMATCHING
ItemType pouchKeyItem(s32 id) {
	return mpp->keyItems[id];
}
#endif

#ifdef NONMATCHING
ItemType pouchHaveItem(s32 id) {
	return mpp->heldItems[id];
}
#endif

#ifdef NONMATCHING
ItemType pouchKeepItem(s32 id) {
	return mpp->storedItems[id];
}
#endif

#ifdef NONMATCHING
ItemType pouchHaveBadge(s32 id) {
	return mpp->badges[id];
}
#endif

#ifdef NONMATCHING
s32 pouchGetHaveItemCnt(void) {
	s32 i, count;

	for (count = 0, i = 0; i < MAX_HELD_ITEMS; i++) {
		if (mpp->heldItems[i] != ITEM_NULL) {
			count++;
		}
	}
	return count;
}
#endif

#ifdef NONMATCHING
s32 pouchGetKeepItemCnt(void) {
	s32 i, count;

	for (count = 0, i = 0; i < MAX_STORED_ITEMS; i++) {
		if (mpp->storedItems[i] != ITEM_NULL) {
			count++;
		}
	}
	return count;
}
#endif

#ifdef NONMATCHING
s32 pouchGetHaveBadgeCnt(void) {
	s32 i, count;

	for (count = 0, i = 0; i < MAX_BADGES; i++) {
		if (mpp->badges[i] != ITEM_NULL) {
			count++;
		}
	}
	return count;
}
#endif

#ifdef NONMATCHING
s32 pouchGetEquipBadgeCnt(void) {
	s32 i, count;

	for (count = 0, i = 0; i < MAX_BADGES; i++) {
		if (mpp->equippedBadges[i] != ITEM_NULL) {
			count++;
		}
	}
	return count;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
s32 pouchGetEmptyKeepItemCnt(void) {
	s32 i, count;

	for (count = 0, i = 0; i < MAX_STORED_ITEMS; i++) {
		if (mpp->storedItems[i] == ITEM_NULL) {
			count++;
		}
	}
	return count;
}
#endif

//we have obtained an item, update the appropriate data
#ifdef NONMATCHING
BOOL pouchGetItem(ItemType type)
{
  s16 *new_var[2];
  s32 size;
  s32 j;
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
    if (yuwp->tokens < 99999)
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
      mpp->currentFP++; new_var [1] = (void *) 0 ;
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
  new_var[1] = (void *) 0;
  new_var[0] = (void *) 0;
  size = 0;
  if ((type >= 0x79) && (type < 0xEC))
  {
    new_var[0] = mpp->heldItems;
    size = (((s32 (*)(s32)) pouchCheckItem)(1)) ? (20) : (10);
    ok = 1;
  }
  else
    if ((type >= 1) && (type < 0x79))
  {
    new_var[1] = (void *) 0;
    size = 0x79;
    ok = 1;
    new_var[0] = mpp->keyItems;
  }
  else
    if ((type >= 0xF0) && (type < 0x153))
  {
    size = 200;
    ok = 1;
    new_var[0] = mpp->badges;
    new_var[1] = mpp->equippedBadges;
  }
  else
  {
    ok = 0;
  }
  if (!ok)
  {
    return 0;
  }
  for (size--; size >= 0; size--)
  {
    if (new_var[0][size] == 0)
    {
      for (j = size; j > 0; j--)
      {
        new_var[0][j] = new_var[0][j - 1];
        if (new_var[1])
        {
          new_var[1][j] = new_var[1][j - 1];
        }
      }

      new_var[0][0] = type;
      if (new_var[1])
      {
        new_var[1][0] = 0;
      }
      return 1;
    }
  }

  return 0;
}
#endif

#ifdef NONMATCHING
u32 pouchCheckItem(u32 itemId) {
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
#endif

#ifdef NONMATCHING
BOOL pouchRemoveItem(ItemType type)
{
  s16 *table1;
  s16 *table2;
  BOOL valid;
  s32 maximum;
  int i;
  int j;
  int temp;
  maximum = 0;
  table1 = (void *) 0;
  table2 = (void *) 0;
  if ((type >= ITEM_COIN) && (type < (ITEM_FRESH_JUICE + 1)))
  {
    table1 = mpp->heldItems;
    table2 = (void *) 0;
    maximum = (((s32 (*)(s32)) pouchCheckItem)(ITEM_STRANGE_SACK)) ? (20) : (10);
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
      table1[i] = ITEM_NULL;
      if (table2 != 0)
      {
        table2[i] = ITEM_NULL;
      }
      j = i;
      temp = maximum;
      temp = temp - 1;
      for (; j < temp; j++)
      {
        table1[j] = table1[j + 1];
        table1[j + 1] = ITEM_NULL;
        if (table2 != 0)
        {
          table2[j] = table2[j + 1];
          table2[j + 1] = ITEM_NULL;
        }
      }

      return 1;
    }
  }

  return 0;
}
#endif

#ifdef NONMATCHING
BOOL pouchRemoveItemIndex(ItemType type, s32 index) {
	s16* table1, * table2, * p;
	BOOL valid;
	s32 maximum;
	int i, j, temp;

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
			table1[i] = ITEM_NULL;
			if (table2) {
				table2[i] = ITEM_NULL;
			}
			temp = maximum - 1;
			for (j = i; j < temp; j++) {
				table1[j] = table1[j + 1];
				table1[j + 1] = ITEM_NULL;
				if (table2) {
					table2[j] = table2[j + 1];
					table2[j + 1] = ITEM_NULL;
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}
#endif

#ifdef NONMATCHING
void unk_800d06b4(const char* src, char* dst) {
	u16 c;
	s32 len = strlen(src) / 2;
	u16* s = (u16*)src;
	u16* d = (u16*)dst;
	s32 i;
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

#ifdef NONMATCHING
static inline void pouchAiueoConv(const char* src, char* dst) {
	u16* s = (u16*)src;
	s32 len = strlen(src) / 2;
	u16* d = (u16*)dst;
	u16 c;
	s32 i;
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

#ifdef NONMATCHING
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

#ifdef NONMATCHING
s32 comp_kind(s16* a, s16* b) {
	s16 x = itemDataTable[*a].type_sort_order;
	s16 y = itemDataTable[*b].type_sort_order;
	if (x > y) return 1;
	return -(x < y);
}
#endif

#ifdef NONMATCHING
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

#ifdef NONMATCHING
s32 comp_kind_r(s16* a, s16* b) {
	s16 x = itemDataTable[*a].type_sort_order;
	s16 y = itemDataTable[*b].type_sort_order;
	if (x < y) return 1;
	return -(x > y);
}
#endif

#ifdef NONMATCHING
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
				} else if (mode == 6) {
					if (ca > cb) swap = TRUE;
					else if (ca == cb && a->type_sort_order > b->type_sort_order) swap = TRUE;
				} else if (mode == 13) {
					if (ca < cb) swap = TRUE;
					else if (ca == cb && a->type_sort_order < b->type_sort_order) swap = TRUE;
				}
				if (swap) {
					t1 = badges[n];
					t2 = equipped[n];
					badges[n] = badges[j];
					equipped[n] = equipped[j];
					badges[j] = t1;
					equipped[j] = t2;
				}
			}
		}
		memcpy(pp[0]->badges, badges, sizeof(badges));
		memcpy(pp[0]->equippedBadges, equipped, sizeof(equipped));
	}
}
#endif

#ifdef NONMATCHING
s32 pouchGetCoin(void) {
	return mpp->coins;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
s16 pouchGetSuperCoin(void) {
	return mpp->mShineSpriteCount;
}
#endif

#ifdef NONMATCHING
s16 pouchSetSuperCoin(s16 count) {
	mpp->mShineSpriteCount = count;
	return mpp->mShineSpriteCount;
}
#endif

#ifdef NONMATCHING
s16 pouchGetStarPiece(void) {
	return mpp->mStarPieceCount;
}
#endif

#ifdef NONMATCHING
s16 pouchAddStarPiece(s16 count) {
	mpp->mStarPieceCount += count;
	return mpp->mStarPieceCount;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
s16 pouchGetHP(void) {
	return mpp->currentHP;
}
#endif

#ifdef NONMATCHING
s16 pouchGetMaxHP(void) {
	return mpp->maximumHP;
}
#endif

#ifdef NONMATCHING
void pouchSetHP(s16 points) {
	mpp->currentHP = points;
	if (mpp->currentHP > mpp->maximumHP) {
		mpp->currentHP = mpp->maximumHP;
	}
}
#endif

#ifdef NONMATCHING
void pouchSetMaxHP(s16 points) {
	mpp->maximumHP = points;
	mpp->baseMaxHP = mpp->maximumHP;
}
#endif

#ifdef NONMATCHING
s16 pouchGetPartyHP(PartyId partnerId) {
	return mpp->partyData[partnerId].currentHP;
}
#endif

#ifdef NONMATCHING
void pouchSetPartyHP(PartyId partnerId, s16 points) {
	PouchPartyData* party;

	mpp->partyData[partnerId].currentHP = points;
	party = &mpp->partyData[partnerId];
	if (party->currentHP > party->maximumHP) {
		party->currentHP = party->maximumHP;
	}
}
#endif

#ifdef NONMATCHING
s16 pouchGetFP(void) {
	return mpp->currentFP;
}
#endif

#ifdef NONMATCHING
s16 pouchGetMaxFP(void) {
	return mpp->maximumFP;
}
#endif

#ifdef NONMATCHING
void pouchSetFP(s16 points) {
	mpp->currentFP = points;
	if (mpp->currentFP > mpp->maximumFP) {
		mpp->currentFP = mpp->maximumFP;
	}
}
#endif

#ifdef NONMATCHING
void pouchSetMaxFP(s16 points) {
	mpp->maximumFP = points;
	mpp->baseMaxFP = mpp->maximumFP;
}
#endif

#ifdef NONMATCHING
s16 pouchGetAP(void) {
	return mpp->currentSP;
}
#endif

#ifdef NONMATCHING
void pouchAddAP(s16 points) {
	mpp->currentSP += points;
	if (mpp->currentSP < 0) {
		mpp->currentSP = 0;
	}
	if (mpp->currentSP > mpp->maximumSP) {
		mpp->currentSP = mpp->maximumSP;
	}
}
#endif

#ifdef NONMATCHING
void pouchSetAP(s16 points) {
	mpp->currentSP = points;
	if (mpp->currentSP < 0) {
		mpp->currentSP = 0;
	}
	if (mpp->currentSP > mpp->maximumSP) {
		mpp->currentSP = mpp->maximumSP;
	}
}
#endif

#ifdef NONMATCHING
s16 pouchGetMaxAP(void) {
	return mpp->maximumSP;
}
#endif

#ifdef NONMATCHING
f32 pouchGetAudienceNum(void) {
	return mpp->audienceCount;
}
#endif

#ifdef NONMATCHING
void pouchSetAudienceNum(f32 num) {
	mpp->audienceCount = num;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
s32 pouchGetPartyAttackLv(PartyId partyId) {
	return *(s16*)((u8*)mpp + partyId * 14 + 0xA);
}
#endif

//TODO: this function
#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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

#ifdef NONMATCHING
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
#endif

#pragma push
#ifdef NONMATCHING
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
#endif
#pragma pop

#ifdef NONMATCHING
s16 pouchGetStarPoint(void) {
	return mpp->mStarPoints;
}
#endif

#ifdef NONMATCHING
BOOL pouchEquipBadgeIndex(s32 index) {
	if (mpp->badges[index] == 0) {
		return FALSE;
	}
	mpp->equippedBadges[index] = mpp->badges[index];
	return TRUE;
}
#endif

#ifdef NONMATCHING
BOOL pouchUnEquipBadgeIndex(s32 index) {
	if (mpp->equippedBadges[index] == 0) {
		return FALSE;
	}
	mpp->equippedBadges[index] = 0;
	return TRUE;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
BOOL pouchEquipCheckBadgeIndex(s32 index) {
	return mpp->equippedBadges[index] != 0;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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

#ifdef NONMATCHING
s32 pouchArriveBadge(s32 id) {
	return badgeShop_add(bdsw->special_table, (s16)id, 1);
}
#endif

#ifdef NONMATCHING
void pouchMajinaiInit(s32 curseCount) {
	if (mpp->mMerleeCurseUsesRemaining < curseCount) {
		mpp->mMerleeCurseUsesRemaining = (u8)curseCount;
		mpp->mTurnsUntilMerleeActivation = -1;
		mpp->mMerleeNextCurseType = 0;
	}
}
#endif

#ifdef NONMATCHING
s32 pouchGetKpaCoin(void) {
	return mpp->mSuperBowserCoins;
}
#endif

#ifdef NONMATCHING
BOOL pouchAddKpaCoin(u8 coins) {
	BOOL ret = FALSE;
	mpp->mSuperBowserCoins += coins;
	if (mpp->mSuperBowserCoins >= 100) {
		mpp->mSuperBowserCoins -= 100;
		ret = TRUE;
	}
	return ret;
}
#endif

#ifdef NONMATCHING
u32 pouchGetKpaScore(void) {
	return mpp->mSuperBowserScore;
}
#endif

#ifdef NONMATCHING
void pouchAddKpaScore(u32 score) {
	mpp->mSuperBowserScore += score;
	if (mpp->mSuperBowserScore > 999999)
	{
		mpp->mSuperBowserScore = 999999;
	}
}
#endif

#ifdef NONMATCHING
void pouchGetStarStone(u32 id) {
	u16* sp = (u16*)&mpp->mStarPowersObtained;
	if (!*sp) {
		mpp->audienceCount = 2.0f;
	}
	*(u16*)&mpp->mStarPowersObtained |= 1 << id;
	mpp->maximumSP = (s16)(100 * (id + 1));
	if (mpp->maximumSP < 0) {
		mpp->maximumSP = 0;
	}
	if (mpp->maximumSP > 800) {
		mpp->maximumSP = 800;
	}
}
#endif

#ifdef NONMATCHING
s32 pouchReceiveMailCount(void) {
	s32 i, count;

	for (count = 0, i = 0; i < 99; i++) {
		if (mpp->mEmailReceivedFlags[i / 32] & (1 << (i % 32))) {
			count++;
		}
	}
	return count;
}
#endif

#ifdef NONMATCHING
void pouchReceiveMail(s32 mailId) {
	s32 count;
	s32 index, shift;

	index = mailId / 32;
	shift = mailId % 32;
	count = pouchReceiveMailCount();
	mpp->mEmailReceivedFlags[index] |= (1 << shift);
	mpp->mEmailIds[count] = (u8)mailId;
}
#endif

#ifdef NONMATCHING
void pouchOpenMail(s32 mailId) {
	mpp->mEmailReadFlags[mailId / 32] |= (1 << (mailId % 32));
}
#endif

#ifdef NONMATCHING
u32 pouchCheckMail(s32 mailId) {
	s32 mask = (1 << (mailId % 32));
	if (mpp->mEmailReadFlags[mailId / 32] & mask) {
		return 2;
	}
	else {
		return (mpp->mEmailReceivedFlags[mailId / 32] & mask) != 0;
	}
}
#endif

#ifdef NONMATCHING
s32 pouchGetPartyColor(PartyId partnerId) {
	return mpp->partyData[partnerId].flags >> 13;
}
#endif

#ifdef NONMATCHING
void pouchSetPartyColor(PartyId partnerId, s32 color) {
	mpp->partyData[partnerId].flags = (mpp->partyData[partnerId].flags & 0x1FFF) | (u16)(color << 13);
}
#endif

#ifdef NONMATCHING
void pouchSetYoshiName(char* name) {
	strcpy(mpp->yoshiName, name);
}
#endif

#ifdef NONMATCHING
char* pouchGetYoshiName(void) {
	if (strlen(mpp->yoshiName) < 1) {
		return (char*)msgSearch((char*)str_802CE170);
	}
	return mpp->yoshiName;
}
#endif
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
BOOL pouchRemoveKeepItem(s32 id, s32 index);
BOOL pouchAddKeepItem(s16 id);
s32 pouchGetPartyAttackLv(PartyId partyId);
s32 pouchGetHammerLv(void);
s32 pouchGetJumpLv(void);
void pouchSetAudienceNum(f32 num);
f32 pouchGetAudienceNum(void);
s16 pouchGetMaxAP(void);
void pouchSetAP(s16 points);
void pouchAddAP(s16 points);
s16 pouchGetAP(void);
void pouchSetMaxFP(s16 points);
void pouchSetFP(s16 points);
s16 pouchGetMaxFP(void);
s16 pouchGetFP(void);
void pouchSetPartyHP(PartyId partnerId, s16 points);
s16 pouchGetPartyHP(PartyId partnerId);
void pouchSetMaxHP(s16 points);
void pouchSetHP(s16 points);
s16 pouchGetMaxHP(void);
s16 pouchGetHP(void);
s16 pouchAddHP(s32 points);
s16 pouchAddStarPiece(s16 count);
s16 pouchGetStarPiece(void);
s16 pouchSetSuperCoin(s16 count);
s16 pouchGetSuperCoin(void);
s32 pouchSetCoin(s32 coins);
s16 pouchAddCoin(s16 coins);
s32 pouchGetCoin(void);
void pouchSortItem(s32 mode);
s32 comp_kind_r(s16* a, s16* b);
s32 comp_aiueo_r(const void* a, const void* b);
s32 comp_kind(s16* a, s16* b);
s32 comp_aiueo(const void* a, const void* b);
void unk_800d06b4(const char* src, char* dst);
BOOL pouchRemoveItemIndex(ItemType type, s32 index);
BOOL pouchRemoveItem(ItemType type);
u32 pouchCheckItem(u32 itemId);
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
#ifndef NONMATCHING
// ASM-STOPGAP: pouchGetPtr (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const char str_802CE170[] = "name_party3";
#pragma force_active on
__declspec(section ".rodata") const char str_802CE17C[] = "\203`\203r\203\210\203b\203V\201[\000\000\000";
#pragma force_active reset
#pragma force_active on
__declspec(section ".sdata2") const f32 float_2_8041b648 = 2.0f;
__declspec(section ".sdata2") const f32 float_0_8041b64c = 0.0f;

void* __memAlloc(HEAP_TYPE heap, u32 size);
s32 badgeShop_add(u8* table, s16 id, s32 val);
s32 marioGetParty(void);
void *memcpy(void *dest, const void *src, size_t num);
void *memset(void *dest, int ch, size_t count);
const char* msgSearch(const char* tag);
u32 pouchCheckItem(u32 itemId);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
size_t strlen(const char *s);
void swSet(s32 index);
asm char* pouchGetYoshiName(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r3, mpp(r13)
	addi r3, r3, 0x5c0
	bl strlen
	cmplwi r3, 0x1
	bge @1
	lis r3, str_802CE170@ha
	addi r3, r3, str_802CE170@l
	bl msgSearch
	b @2
	@1:
	lwz r3, mpp(r13)
	addi r3, r3, 0x5c0
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void pouchSetYoshiName(char* name) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	mr r4, r3
	stw r0, 0x14(r1)
	lwz r5, mpp(r13)
	addi r3, r5, 0x5c0
	bl strcpy
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void pouchSetPartyColor(PartyId partnerId, s32 color) {
	nofralloc
	mulli r3, r3, 0xe
	lwz r5, mpp(r13)
	lhzx r0, r5, r3
	clrlwi r0, r0, 19
	rlwimi r0, r4, 13, 16, 18
	sthx r0, r5, r3
	blr
}

asm s32 pouchGetPartyColor(PartyId partnerId) {
	nofralloc
	mulli r0, r3, 0xe
	lwz r3, mpp(r13)
	lhzx r0, r3, r0
	srawi r3, r0, 13
	blr
}

asm u32 pouchCheckMail(s32 mailId) {
	nofralloc
	srawi r4, r3, 5
	slwi r0, r3, 27
	addze r4, r4
	srwi r3, r3, 31
	subf r0, r3, r0
	lwz r6, mpp(r13)
	slwi r5, r4, 2
	li r4, 0x1
	add r5, r6, r5
	rotlwi r0, r0, 5
	add r0, r0, r3
	lwz r3, 0x590(r5)
	slw r4, r4, r0
	and. r0, r3, r4
	beq @1
	li r3, 0x2
	blr
	@1:
	lwz r0, 0x580(r5)
	and r3, r0, r4
	neg r0, r3
	or r0, r0, r3
	srwi r3, r0, 31
	blr
}

asm void pouchOpenMail(s32 mailId) {
	nofralloc
	srawi r4, r3, 5
	slwi r0, r3, 27
	addze r4, r4
	srwi r3, r3, 31
	subf r0, r3, r0
	lwz r6, mpp(r13)
	slwi r5, r4, 2
	li r4, 0x1
	add r5, r6, r5
	rotlwi r0, r0, 5
	add r0, r0, r3
	lwz r3, 0x590(r5)
	slw r0, r4, r0
	or r0, r3, r0
	stw r0, 0x590(r5)
	blr
}

asm void pouchReceiveMail(s32 mailId) {
	nofralloc
	slwi r0, r3, 27
	srwi r5, r3, 31
	subf r0, r5, r0
	srawi r6, r3, 5
	rotlwi r4, r0, 5
	li r7, 0x0
	li r0, 0x21
	addze r10, r6
	mr r8, r7
	add r11, r4, r5
	lwz r9, mpp(r13)
	li r5, 0x1
	mtctr r0
	@1:
	srawi r4, r8, 5
	slwi r0, r8, 27
	addze r6, r4
	srwi r4, r8, 31
	slwi r6, r6, 2
	subf r0, r4, r0
	addi r6, r6, 0x580
	rotlwi r0, r0, 5
	lwzx r6, r9, r6
	add r0, r0, r4
	slw r0, r5, r0
	and. r0, r6, r0
	beq @2
	addi r7, r7, 0x1
	@2:
	addi r8, r8, 0x1
	srawi r4, r8, 5
	addze r6, r4
	slwi r0, r8, 27
	srwi r4, r8, 31
	slwi r6, r6, 2
	subf r0, r4, r0
	addi r6, r6, 0x580
	rotlwi r0, r0, 5
	lwzx r6, r9, r6
	add r0, r0, r4
	slw r0, r5, r0
	and. r0, r6, r0
	beq @3
	addi r7, r7, 0x1
	@3:
	addi r8, r8, 0x1
	srawi r4, r8, 5
	addze r6, r4
	slwi r0, r8, 27
	srwi r4, r8, 31
	slwi r6, r6, 2
	subf r0, r4, r0
	addi r6, r6, 0x580
	rotlwi r0, r0, 5
	lwzx r6, r9, r6
	add r0, r0, r4
	slw r0, r5, r0
	and. r0, r6, r0
	beq @4
	addi r7, r7, 0x1
	@4:
	addi r8, r8, 0x1
	bdnz @1
	slwi r4, r10, 2
	li r0, 0x1
	add r5, r9, r4
	lwz r4, 0x580(r5)
	slw r0, r0, r11
	or r0, r4, r0
	stw r0, 0x580(r5)
	lwz r0, mpp(r13)
	add r4, r0, r7
	stb r3, 0x51a(r4)
	blr
}

asm s32 pouchReceiveMailCount(void) {
	nofralloc
	li r0, 0x21
	lwz r7, mpp(r13)
	li r3, 0x0
	li r8, 0x0
	li r5, 0x1
	mtctr r0
	@1:
	srawi r4, r8, 5
	slwi r0, r8, 27
	addze r6, r4
	srwi r4, r8, 31
	slwi r6, r6, 2
	subf r0, r4, r0
	addi r6, r6, 0x580
	rotlwi r0, r0, 5
	lwzx r6, r7, r6
	add r0, r0, r4
	slw r0, r5, r0
	and. r0, r6, r0
	beq @2
	addi r3, r3, 0x1
	@2:
	addi r8, r8, 0x1
	srawi r4, r8, 5
	addze r6, r4
	slwi r0, r8, 27
	srwi r4, r8, 31
	slwi r6, r6, 2
	subf r0, r4, r0
	addi r6, r6, 0x580
	rotlwi r0, r0, 5
	lwzx r6, r7, r6
	add r0, r0, r4
	slw r0, r5, r0
	and. r0, r6, r0
	beq @3
	addi r3, r3, 0x1
	@3:
	addi r8, r8, 0x1
	srawi r4, r8, 5
	addze r6, r4
	slwi r0, r8, 27
	srwi r4, r8, 31
	slwi r6, r6, 2
	subf r0, r4, r0
	addi r6, r6, 0x580
	rotlwi r0, r0, 5
	lwzx r6, r7, r6
	add r0, r0, r4
	slw r0, r5, r0
	and. r0, r6, r0
	beq @4
	addi r3, r3, 0x1
	@4:
	addi r8, r8, 0x1
	bdnz @1
	blr
}

asm void pouchGetStarStone(u32 id) {
	nofralloc
	lwz r4, mpp(r13)
	lhz r0, 0x8c(r4)
	cmplwi r0, 0x0
	bne @1
	lfs f0, float_2_8041b648(r2)
	stfs f0, 0x84(r4)
	@1:
	lwz r6, mpp(r13)
	addi r0, r3, 0x1
	li r4, 0x1
	lhz r5, 0x8c(r6)
	slw r3, r4, r3
	mulli r0, r0, 0x64
	or r3, r5, r3
	sth r3, 0x8c(r6)
	lwz r3, mpp(r13)
	sth r0, 0x7c(r3)
	lwz r3, mpp(r13)
	lha r0, 0x7c(r3)
	cmpwi r0, 0x0
	bge @2
	li r0, 0x0
	sth r0, 0x7c(r3)
	@2:
	lwz r3, mpp(r13)
	lha r0, 0x7c(r3)
	cmpwi r0, 0x320
	blelr
	li r0, 0x320
	sth r0, 0x7c(r3)
	blr
}

asm void pouchAddKpaScore(u32 score) {
	nofralloc
	lwz r5, mpp(r13)
	lis r4, 0xf
	addi r0, r4, 0x423f
	lwz r4, 0x5bc(r5)
	add r3, r4, r3
	stw r3, 0x5bc(r5)
	lwz r4, mpp(r13)
	lwz r3, 0x5bc(r4)
	cmplw r3, r0
	blelr
	stw r0, 0x5bc(r4)
	blr
}

asm u32 pouchGetKpaScore(void) {
	nofralloc
	lwz r3, mpp(r13)
	lwz r3, 0x5bc(r3)
	blr
}

asm BOOL pouchAddKpaCoin(u8 coins) {
	nofralloc
	lwz r4, mpp(r13)
	li r5, 0x0
	lbz r0, 0x5bb(r4)
	add r0, r0, r3
	stb r0, 0x5bb(r4)
	lwz r4, mpp(r13)
	lbz r3, 0x5bb(r4)
	cmplwi r3, 0x64
	blt @1
	subi r0, r3, 0x64
	li r5, 0x1
	stb r0, 0x5bb(r4)
	@1:
	mr r3, r5
	blr
}

asm s32 pouchGetKpaCoin(void) {
	nofralloc
	lwz r3, mpp(r13)
	lbz r3, 0x5bb(r3)
	blr
}

asm void pouchMajinaiInit(s32 curseCount) {
	nofralloc
	lwz r4, mpp(r13)
	lbz r0, 0x5b8(r4)
	cmpw r0, r3
	bgelr
	stb r3, 0x5b8(r4)
	li r4, -0x1
	li r0, 0x0
	lwz r3, mpp(r13)
	stb r4, 0x5b9(r3)
	lwz r3, mpp(r13)
	stb r0, 0x5ba(r3)
	blr
}

asm s32 pouchArriveBadge(s32 id) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r5, 0x1
	stw r0, 0x14(r1)
	mr r0, r3
	extsh r4, r0
	lwz r3, bdsw(r13)
	bl badgeShop_add
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BOOL N_pouchUnEquipBadgeID(s32 badgeId) {
	nofralloc
	lwz r5, mpp(r13)
	li r0, 0xc8
	li r6, 0x0
	mr r4, r5
	mtctr r0
	@1:
	lha r0, 0x38a(r4)
	cmpw r0, r3
	bne @2
	slwi r0, r6, 1
	add r3, r5, r0
	lha r0, 0x38a(r3)
	cmpwi r0, 0x0
	beq @3
	li r0, 0x0
	sth r0, 0x38a(r3)
	@3:
	li r3, 0x1
	blr
	@2:
	addi r4, r4, 0x2
	addi r6, r6, 0x1
	bdnz @1
	li r3, 0x0
	blr
}

asm BOOL pouchEquipBadgeID(s32 badgeId) {
	nofralloc
	lwz r5, mpp(r13)
	li r0, 0xc8
	li r6, 0x0
	mr r4, r5
	mtctr r0
	@1:
	lha r0, 0x1fa(r4)
	cmpw r0, r3
	bne @2
	slwi r0, r6, 1
	add r3, r5, r0
	lha r4, 0x1fa(r3)
	extsh. r0, r4
	beq @3
	sth r4, 0x38a(r3)
	@3:
	li r3, 0x1
	blr
	@2:
	addi r4, r4, 0x2
	addi r6, r6, 0x1
	bdnz @1
	li r3, 0x0
	blr
}

asm BOOL pouchEquipCheckBadgeIndex(s32 index) {
	nofralloc
	lwz r4, mpp(r13)
	slwi r0, r3, 1
	add r3, r4, r0
	lha r3, 0x38a(r3)
	neg r0, r3
	or r0, r0, r3
	srwi r3, r0, 31
	blr
}

asm s32 pouchEquipCheckBadge(s32 badgeId) {
	nofralloc
	li r0, 0x14
	lwz r4, mpp(r13)
	li r6, 0x0
	li r5, 0x0
	mtctr r0
	@1:
	lha r0, 0x38a(r4)
	cmpw r3, r0
	bne @2
	addi r6, r6, 0x1
	@2:
	lha r0, 0x38c(r4)
	cmpw r3, r0
	bne @3
	addi r6, r6, 0x1
	@3:
	lha r0, 0x38e(r4)
	cmpw r3, r0
	bne @4
	addi r6, r6, 0x1
	@4:
	lha r0, 0x390(r4)
	cmpw r3, r0
	bne @5
	addi r6, r6, 0x1
	@5:
	lha r0, 0x392(r4)
	cmpw r3, r0
	bne @6
	addi r6, r6, 0x1
	@6:
	lha r0, 0x394(r4)
	cmpw r3, r0
	bne @7
	addi r6, r6, 0x1
	@7:
	lha r0, 0x396(r4)
	cmpw r3, r0
	bne @8
	addi r6, r6, 0x1
	@8:
	lha r0, 0x398(r4)
	cmpw r3, r0
	bne @9
	addi r6, r6, 0x1
	@9:
	lha r0, 0x39a(r4)
	cmpw r3, r0
	bne @10
	addi r6, r6, 0x1
	@10:
	lha r0, 0x39c(r4)
	cmpw r3, r0
	bne @11
	addi r6, r6, 0x1
	@11:
	addi r4, r4, 0x14
	addi r5, r5, 0x9
	bdnz @1
	mr r3, r6
	blr
}

asm BOOL pouchUnEquipBadgeIndex(s32 index) {
	nofralloc
	lwz r4, mpp(r13)
	slwi r0, r3, 1
	add r4, r4, r0
	lha r0, 0x38a(r4)
	cmpwi r0, 0x0
	bne @1
	li r3, 0x0
	blr
	@1:
	li r0, 0x0
	li r3, 0x1
	sth r0, 0x38a(r4)
	blr
}

asm BOOL pouchEquipBadgeIndex(s32 index) {
	nofralloc
	lwz r4, mpp(r13)
	slwi r0, r3, 1
	add r3, r4, r0
	lha r4, 0x1fa(r3)
	extsh. r0, r4
	bne @1
	li r3, 0x0
	blr
	@1:
	sth r4, 0x38a(r3)
	li r3, 0x1
	blr
}

asm s16 pouchGetStarPoint(void) {
	nofralloc
	lwz r3, mpp(r13)
	lha r3, 0x96(r3)
	blr
}

asm void pouchRevisePartyParam(void) {
	nofralloc
	li r4, 0x0
	li r0, 0x14
	mr r3, r4
	lwz r5, mpp(r13)
	mtctr r0
	@1:
	lha r0, 0x38a(r5)
	cmpwi r0, 0x117
	bne @2
	addi r4, r4, 0x1
	@2:
	lha r0, 0x38c(r5)
	cmpwi r0, 0x117
	bne @3
	addi r4, r4, 0x1
	@3:
	lha r0, 0x38e(r5)
	cmpwi r0, 0x117
	bne @4
	addi r4, r4, 0x1
	@4:
	lha r0, 0x390(r5)
	cmpwi r0, 0x117
	bne @5
	addi r4, r4, 0x1
	@5:
	lha r0, 0x392(r5)
	cmpwi r0, 0x117
	bne @6
	addi r4, r4, 0x1
	@6:
	lha r0, 0x394(r5)
	cmpwi r0, 0x117
	bne @7
	addi r4, r4, 0x1
	@7:
	lha r0, 0x396(r5)
	cmpwi r0, 0x117
	bne @8
	addi r4, r4, 0x1
	@8:
	lha r0, 0x398(r5)
	cmpwi r0, 0x117
	bne @9
	addi r4, r4, 0x1
	@9:
	lha r0, 0x39a(r5)
	cmpwi r0, 0x117
	bne @10
	addi r4, r4, 0x1
	@10:
	lha r0, 0x39c(r5)
	cmpwi r0, 0x117
	bne @11
	addi r4, r4, 0x1
	@11:
	addi r5, r5, 0x14
	addi r3, r3, 0x9
	bdnz @1
	lis r3, _party_max_hp_table@ha
	li r0, 0x4
	addi r5, r3, _party_max_hp_table@l
	li r8, 0x0
	mulli r4, r4, 0x5
	li r3, 0x0
	mtctr r0
	@12:
	cmpwi r8, 0x0
	beq @13
	lwz r0, mpp(r13)
	add r7, r0, r3
	lha r0, 0x8(r7)
	slwi r0, r0, 1
	lhax r0, r5, r0
	sth r0, 0x4(r7)
	lha r0, 0x4(r7)
	add r0, r0, r4
	sth r0, 0x2(r7)
	lha r0, 0x6(r7)
	lha r6, 0x2(r7)
	cmpw r0, r6
	ble @13
	sth r6, 0x6(r7)
	@13:
	addic. r8, r8, 0x1
	addi r5, r5, 0x8
	addi r3, r3, 0xe
	beq @14
	lwz r0, mpp(r13)
	add r7, r0, r3
	lha r0, 0x8(r7)
	slwi r0, r0, 1
	lhax r0, r5, r0
	sth r0, 0x4(r7)
	lha r0, 0x4(r7)
	add r0, r0, r4
	sth r0, 0x2(r7)
	lha r0, 0x6(r7)
	lha r6, 0x2(r7)
	cmpw r0, r6
	ble @14
	sth r6, 0x6(r7)
	@14:
	addi r3, r3, 0xe
	addi r5, r5, 0x8
	addi r8, r8, 0x1
	bdnz @12
	blr
}

asm void pouchReviseMarioParam(void) {
	nofralloc
	stwu r1, -0x10(r1)
	li r0, 0x64
	li r6, 0x0
	li r4, 0x0
	stw r31, 0xc(r1)
	lwz r5, mpp(r13)
	lha r3, 0x8e(r5)
	sth r3, 0x72(r5)
	lwz r5, mpp(r13)
	lha r3, 0x90(r5)
	sth r3, 0x76(r5)
	mtctr r0
	@1:
	lwz r5, mpp(r13)
	addi r0, r4, 0x38a
	lhax r3, r5, r0
	extsh. r0, r3
	beq @2
	cmpwi r3, 0x117
	beq @2
	bge @3
	cmpwi r3, 0x116
	bge @4
	b @2
	@3:
	cmpwi r3, 0x119
	bge @2
	b @5
	@4:
	lha r3, 0x72(r5)
	addi r0, r3, 0x5
	sth r0, 0x72(r5)
	b @2
	@5:
	lha r3, 0x76(r5)
	addi r0, r3, 0x5
	sth r0, 0x76(r5)
	@2:
	lwz r5, mpp(r13)
	addi r0, r4, 0x38c
	lhax r3, r5, r0
	extsh. r0, r3
	beq @6
	cmpwi r3, 0x117
	beq @6
	bge @7
	cmpwi r3, 0x116
	bge @8
	b @6
	@7:
	cmpwi r3, 0x119
	bge @6
	b @9
	@8:
	lha r3, 0x72(r5)
	addi r0, r3, 0x5
	sth r0, 0x72(r5)
	b @6
	@9:
	lha r3, 0x76(r5)
	addi r0, r3, 0x5
	sth r0, 0x76(r5)
	@6:
	addi r4, r4, 0x4
	addi r6, r6, 0x1
	bdnz @1
	lwz r3, mpp(r13)
	lha r0, 0x70(r3)
	lha r4, 0x72(r3)
	cmpw r0, r4
	ble @10
	sth r4, 0x70(r3)
	@10:
	lwz r3, mpp(r13)
	lha r0, 0x74(r3)
	lha r4, 0x76(r3)
	cmpw r0, r4
	ble @11
	sth r4, 0x74(r3)
	@11:
	lwz r7, mpp(r13)
	lis r5, itemDataTable@ha
	li r4, 0x19
	li r3, 0x0
	lha r6, 0x94(r7)
	addi r0, r5, itemDataTable@l
	sth r6, 0x92(r7)
	mtctr r4
	@12:
	lwz r31, mpp(r13)
	addi r4, r3, 0x38a
	addi r10, r3, 0x38c
	addi r9, r3, 0x38e
	lhax r4, r31, r4
	addi r8, r3, 0x390
	lha r11, 0x92(r31)
	addi r7, r3, 0x392
	mulli r12, r4, 0x28
	addi r6, r3, 0x394
	addi r5, r3, 0x396
	addi r4, r3, 0x398
	add r12, r0, r12
	addi r3, r3, 0x10
	lbz r12, 0x1c(r12)
	extsb r12, r12
	subf r11, r12, r11
	sth r11, 0x92(r31)
	lwz r12, mpp(r13)
	lhax r11, r12, r10
	lha r10, 0x92(r12)
	mulli r11, r11, 0x28
	add r11, r0, r11
	lbz r11, 0x1c(r11)
	extsb r11, r11
	subf r10, r11, r10
	sth r10, 0x92(r12)
	lwz r11, mpp(r13)
	lhax r10, r11, r9
	lha r9, 0x92(r11)
	mulli r10, r10, 0x28
	add r10, r0, r10
	lbz r10, 0x1c(r10)
	extsb r10, r10
	subf r9, r10, r9
	sth r9, 0x92(r11)
	lwz r10, mpp(r13)
	lhax r9, r10, r8
	lha r8, 0x92(r10)
	mulli r9, r9, 0x28
	add r9, r0, r9
	lbz r9, 0x1c(r9)
	extsb r9, r9
	subf r8, r9, r8
	sth r8, 0x92(r10)
	lwz r9, mpp(r13)
	lhax r8, r9, r7
	lha r7, 0x92(r9)
	mulli r8, r8, 0x28
	add r8, r0, r8
	lbz r8, 0x1c(r8)
	extsb r8, r8
	subf r7, r8, r7
	sth r7, 0x92(r9)
	lwz r8, mpp(r13)
	lhax r7, r8, r6
	lha r6, 0x92(r8)
	mulli r7, r7, 0x28
	add r7, r0, r7
	lbz r7, 0x1c(r7)
	extsb r7, r7
	subf r6, r7, r6
	sth r6, 0x92(r8)
	lwz r7, mpp(r13)
	lhax r6, r7, r5
	lha r5, 0x92(r7)
	mulli r6, r6, 0x28
	add r6, r0, r6
	lbz r6, 0x1c(r6)
	extsb r6, r6
	subf r5, r6, r5
	sth r5, 0x92(r7)
	lwz r6, mpp(r13)
	lhax r5, r6, r4
	lha r4, 0x92(r6)
	mulli r5, r5, 0x28
	add r5, r0, r5
	lbz r5, 0x1c(r5)
	extsb r5, r5
	subf r4, r5, r4
	sth r4, 0x92(r6)
	bdnz @12
	lwz r31, 0xc(r1)
	addi r1, r1, 0x10
	blr
}

asm BOOL pouchRemoveKeepItem(s32 id, s32 index) {
	nofralloc
	lwz r5, mpp(r13)
	slwi r7, r4, 1
	addi r6, r5, 0x1ba
	lhax r0, r6, r7
	cmpw r0, r3
	beq @1
	li r3, 0x0
	blr
	@1:
	subfic r0, r4, 0x20
	add r5, r5, r7
	mtctr r0
	cmpwi r4, 0x20
	bge @2
	@3:
	lha r0, 0x1ba(r5)
	cmpw r0, r3
	bne @4
	slwi r7, r4, 1
	li r5, 0x0
	cmpwi r4, 0x1f
	sthx r5, r6, r7
	subfic r3, r4, 0x1f
	bge @5
	srwi. r0, r3, 2
	mtctr r0
	beq @6
	@7:
	lwz r4, mpp(r13)
	addi r0, r7, 0x1bc
	add r6, r4, r7
	lha r4, 0x1bc(r6)
	sth r4, 0x1ba(r6)
	lwz r4, mpp(r13)
	sthx r5, r4, r0
	addi r0, r7, 0x1be
	addi r7, r7, 0x2
	lwz r4, mpp(r13)
	add r6, r4, r7
	lha r4, 0x1bc(r6)
	sth r4, 0x1ba(r6)
	lwz r4, mpp(r13)
	sthx r5, r4, r0
	addi r0, r7, 0x1be
	addi r7, r7, 0x2
	lwz r4, mpp(r13)
	add r6, r4, r7
	lha r4, 0x1bc(r6)
	sth r4, 0x1ba(r6)
	lwz r4, mpp(r13)
	sthx r5, r4, r0
	addi r0, r7, 0x1be
	addi r7, r7, 0x2
	lwz r4, mpp(r13)
	add r6, r4, r7
	addi r7, r7, 0x2
	lha r4, 0x1bc(r6)
	sth r4, 0x1ba(r6)
	lwz r4, mpp(r13)
	sthx r5, r4, r0
	bdnz @7
	andi. r3, r3, 0x3
	beq @5
	@6:
	mtctr r3
	@8:
	lwz r4, mpp(r13)
	addi r0, r7, 0x1bc
	add r6, r4, r7
	addi r7, r7, 0x2
	lha r4, 0x1bc(r6)
	sth r4, 0x1ba(r6)
	lwz r4, mpp(r13)
	sthx r5, r4, r0
	bdnz @8
	@5:
	li r3, 0x1
	blr
	@4:
	addi r5, r5, 0x2
	addi r4, r4, 0x1
	bdnz @3
	@2:
	li r3, 0x0
	blr
}

asm BOOL pouchAddKeepItem(s16 id) {
	nofralloc
	lwz r4, mpp(r13)
	li r0, 0x20
	li r6, 0x1f
	addi r4, r4, 0x3e
	mtctr r0
	@1:
	lha r0, 0x1ba(r4)
	cmpwi r0, 0x0
	bne @2
	cmpwi r6, 0x0
	mr r4, r6
	slwi r5, r6, 1
	ble @3
	srwi. r0, r6, 3
	mtctr r0
	beq @4
	@5:
	lwz r0, mpp(r13)
	add r6, r0, r5
	subi r5, r5, 0x2
	lha r0, 0x1b8(r6)
	sth r0, 0x1ba(r6)
	lwz r0, mpp(r13)
	add r6, r0, r5
	subi r5, r5, 0x2
	lha r0, 0x1b8(r6)
	sth r0, 0x1ba(r6)
	lwz r0, mpp(r13)
	add r6, r0, r5
	subi r5, r5, 0x2
	lha r0, 0x1b8(r6)
	sth r0, 0x1ba(r6)
	lwz r0, mpp(r13)
	add r6, r0, r5
	subi r5, r5, 0x2
	lha r0, 0x1b8(r6)
	sth r0, 0x1ba(r6)
	lwz r0, mpp(r13)
	add r6, r0, r5
	subi r5, r5, 0x2
	lha r0, 0x1b8(r6)
	sth r0, 0x1ba(r6)
	lwz r0, mpp(r13)
	add r6, r0, r5
	subi r5, r5, 0x2
	lha r0, 0x1b8(r6)
	sth r0, 0x1ba(r6)
	lwz r0, mpp(r13)
	add r6, r0, r5
	subi r5, r5, 0x2
	lha r0, 0x1b8(r6)
	sth r0, 0x1ba(r6)
	lwz r0, mpp(r13)
	add r6, r0, r5
	subi r5, r5, 0x2
	lha r0, 0x1b8(r6)
	sth r0, 0x1ba(r6)
	bdnz @5
	andi. r4, r4, 0x7
	beq @3
	@4:
	mtctr r4
	@6:
	lwz r0, mpp(r13)
	add r6, r0, r5
	subi r5, r5, 0x2
	lha r0, 0x1b8(r6)
	sth r0, 0x1ba(r6)
	bdnz @6
	@3:
	lwz r4, mpp(r13)
	sth r3, 0x1ba(r4)
	li r3, 0x1
	blr
	@2:
	subi r4, r4, 0x2
	subi r6, r6, 0x1
	bdnz @1
	li r3, 0x0
	blr
}

asm s32 pouchGetPartyAttackLv(PartyId partyId) {
	nofralloc
	mulli r3, r3, 0xe
	lwz r4, mpp(r13)
	addi r0, r3, 0xa
	lhax r3, r4, r0
	blr
}

asm s32 pouchGetHammerLv(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0xb
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	li r31, 0x0
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq @1
	li r31, 0x3
	b @2
	@1:
	li r3, 0xa
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq @3
	li r31, 0x2
	b @2
	@3:
	li r3, 0x9
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq @2
	li r31, 0x1
	@2:
	lwz r3, mpp(r13)
	stb r31, 0x99(r3)
	lwz r3, mpp(r13)
	lwz r0, 0x14(r1)
	lbz r3, 0x99(r3)
	lwz r31, 0xc(r1)
	extsb r3, r3
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 pouchGetJumpLv(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x8
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	li r31, 0x0
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq @1
	li r31, 0x3
	b @2
	@1:
	li r3, 0x7
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq @3
	li r31, 0x2
	b @2
	@3:
	li r3, 0x6
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq @2
	li r31, 0x1
	@2:
	lwz r3, mpp(r13)
	stb r31, 0x98(r3)
	lwz r3, mpp(r13)
	lwz r0, 0x14(r1)
	lbz r3, 0x98(r3)
	lwz r31, 0xc(r1)
	extsb r3, r3
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void pouchSetAudienceNum(f32 num) {
	nofralloc
	lwz r3, mpp(r13)
	stfs f1, 0x84(r3)
	blr
}

asm f32 pouchGetAudienceNum(void) {
	nofralloc
	lwz r3, mpp(r13)
	lfs f1, 0x84(r3)
	blr
}

asm s16 pouchGetMaxAP(void) {
	nofralloc
	lwz r3, mpp(r13)
	lha r3, 0x7c(r3)
	blr
}

asm void pouchSetAP(s16 points) {
	nofralloc
	lwz r4, mpp(r13)
	sth r3, 0x7a(r4)
	lwz r3, mpp(r13)
	lha r0, 0x7a(r3)
	cmpwi r0, 0x0
	bge @1
	li r0, 0x0
	sth r0, 0x7a(r3)
	@1:
	lwz r3, mpp(r13)
	lha r0, 0x7a(r3)
	lha r4, 0x7c(r3)
	cmpw r0, r4
	blelr
	sth r4, 0x7a(r3)
	blr
}

asm void pouchAddAP(s16 points) {
	nofralloc
	lwz r4, mpp(r13)
	lha r0, 0x7a(r4)
	add r0, r0, r3
	sth r0, 0x7a(r4)
	lwz r3, mpp(r13)
	lha r0, 0x7a(r3)
	cmpwi r0, 0x0
	bge @1
	li r0, 0x0
	sth r0, 0x7a(r3)
	@1:
	lwz r3, mpp(r13)
	lha r0, 0x7a(r3)
	lha r4, 0x7c(r3)
	cmpw r0, r4
	blelr
	sth r4, 0x7a(r3)
	blr
}

asm s16 pouchGetAP(void) {
	nofralloc
	lwz r3, mpp(r13)
	lha r3, 0x7a(r3)
	blr
}

asm void pouchSetMaxFP(s16 points) {
	nofralloc
	lwz r4, mpp(r13)
	sth r3, 0x76(r4)
	lwz r3, mpp(r13)
	lha r0, 0x76(r3)
	sth r0, 0x90(r3)
	blr
}

asm void pouchSetFP(s16 points) {
	nofralloc
	lwz r4, mpp(r13)
	sth r3, 0x74(r4)
	lwz r3, mpp(r13)
	lha r0, 0x74(r3)
	lha r4, 0x76(r3)
	cmpw r0, r4
	blelr
	sth r4, 0x74(r3)
	blr
}

asm s16 pouchGetMaxFP(void) {
	nofralloc
	lwz r3, mpp(r13)
	lha r3, 0x76(r3)
	blr
}

asm s16 pouchGetFP(void) {
	nofralloc
	lwz r3, mpp(r13)
	lha r3, 0x74(r3)
	blr
}

asm void pouchSetPartyHP(PartyId partnerId, s16 points) {
	nofralloc
	mulli r5, r3, 0xe
	lwz r0, mpp(r13)
	add r3, r0, r5
	sth r4, 0x6(r3)
	lwz r0, mpp(r13)
	add r4, r0, r5
	lha r0, 0x6(r4)
	lha r3, 0x2(r4)
	cmpw r0, r3
	blelr
	sth r3, 0x6(r4)
	blr
}

asm s16 pouchGetPartyHP(PartyId partnerId) {
	nofralloc
	mulli r0, r3, 0xe
	lwz r3, mpp(r13)
	add r3, r3, r0
	lha r3, 0x6(r3)
	blr
}

asm void pouchSetMaxHP(s16 points) {
	nofralloc
	lwz r4, mpp(r13)
	sth r3, 0x72(r4)
	lwz r3, mpp(r13)
	lha r0, 0x72(r3)
	sth r0, 0x8e(r3)
	blr
}

asm void pouchSetHP(s16 points) {
	nofralloc
	lwz r4, mpp(r13)
	sth r3, 0x70(r4)
	lwz r3, mpp(r13)
	lha r0, 0x70(r3)
	lha r4, 0x72(r3)
	cmpw r0, r4
	blelr
	sth r4, 0x70(r3)
	blr
}

asm s16 pouchGetMaxHP(void) {
	nofralloc
	lwz r3, mpp(r13)
	lha r3, 0x72(r3)
	blr
}

asm s16 pouchGetHP(void) {
	nofralloc
	lwz r3, mpp(r13)
	lha r3, 0x70(r3)
	blr
}

asm s16 pouchAddHP(s32 points) {
	nofralloc
	lwz r4, mpp(r13)
	extsh r0, r3
	lha r3, 0x70(r4)
	add r0, r3, r0
	sth r0, 0x70(r4)
	lwz r3, mpp(r13)
	lha r0, 0x70(r3)
	cmpwi r0, 0x0
	bge @1
	li r0, 0x0
	sth r0, 0x70(r3)
	@1:
	lwz r3, mpp(r13)
	lha r0, 0x70(r3)
	lha r4, 0x72(r3)
	cmpw r0, r4
	ble @2
	sth r4, 0x70(r3)
	@2:
	lwz r3, mpp(r13)
	lha r3, 0x70(r3)
	blr
}

asm s16 pouchAddStarPiece(s16 count) {
	nofralloc
	lwz r4, mpp(r13)
	lha r0, 0x9a(r4)
	add r0, r0, r3
	sth r0, 0x9a(r4)
	lwz r3, mpp(r13)
	lha r3, 0x9a(r3)
	blr
}

asm s16 pouchGetStarPiece(void) {
	nofralloc
	lwz r3, mpp(r13)
	lha r3, 0x9a(r3)
	blr
}

asm s16 pouchSetSuperCoin(s16 count) {
	nofralloc
	lwz r4, mpp(r13)
	sth r3, 0x9c(r4)
	lwz r3, mpp(r13)
	lha r3, 0x9c(r3)
	blr
}

asm s16 pouchGetSuperCoin(void) {
	nofralloc
	lwz r3, mpp(r13)
	lha r3, 0x9c(r3)
	blr
}

asm s32 pouchSetCoin(s32 coins) {
	nofralloc
	lwz r4, mpp(r13)
	sth r3, 0x78(r4)
	lwz r3, mpp(r13)
	lha r0, 0x78(r3)
	cmpwi r0, 0x0
	bge @1
	li r0, 0x0
	sth r0, 0x78(r3)
	@1:
	lwz r3, mpp(r13)
	lha r0, 0x78(r3)
	cmpwi r0, 0x3e7
	ble @2
	li r0, 0x3e7
	sth r0, 0x78(r3)
	@2:
	lwz r3, mpp(r13)
	lha r3, 0x78(r3)
	blr
}

asm s16 pouchAddCoin(s16 coins) {
	nofralloc
	lwz r4, mpp(r13)
	lha r0, 0x78(r4)
	add r0, r0, r3
	sth r0, 0x78(r4)
	lwz r3, mpp(r13)
	lha r0, 0x78(r3)
	cmpwi r0, 0x0
	bge @1
	li r0, 0x0
	sth r0, 0x78(r3)
	@1:
	lwz r3, mpp(r13)
	lha r0, 0x78(r3)
	cmpwi r0, 0x3e7
	ble @2
	li r0, 0x3e7
	sth r0, 0x78(r3)
	@2:
	lwz r3, mpp(r13)
	lha r3, 0x78(r3)
	blr
}

asm s32 pouchGetCoin(void) {
	nofralloc
	lwz r3, mpp(r13)
	lha r3, 0x78(r3)
	blr
}

asm void pouchSortItem(s32 mode) {
	nofralloc
	stwu r1, -0x480(r1)
	mflr r0
	stw r0, 0x484(r1)
	stmw r20, 0x450(r1)
	mr r31, r3
	cmplwi r31, 0x1
	lwz r29, mpp(r13)
	ble @1
	cmpwi r31, 0x7
	beq @1
	cmpwi r31, 0x8
	bne @2
	@1:
	li r0, 0x4
	mr r6, r29
	addi r5, r1, 0x8
	li r4, 0x0
	li r3, 0x0
	li r8, 0x0
	mtctr r0
	@3:
	lha r7, 0x192(r6)
	extsh. r0, r7
	beq @4
	sthx r7, r5, r3
	addi r4, r4, 0x1
	addi r3, r3, 0x2
	@4:
	lha r7, 0x194(r6)
	extsh. r0, r7
	beq @5
	sthx r7, r5, r3
	addi r4, r4, 0x1
	addi r3, r3, 0x2
	@5:
	lha r7, 0x196(r6)
	extsh. r0, r7
	beq @6
	sthx r7, r5, r3
	addi r4, r4, 0x1
	addi r3, r3, 0x2
	@6:
	lha r7, 0x198(r6)
	extsh. r0, r7
	beq @7
	sthx r7, r5, r3
	addi r4, r4, 0x1
	addi r3, r3, 0x2
	@7:
	lha r7, 0x19a(r6)
	extsh. r0, r7
	beq @8
	sthx r7, r5, r3
	addi r4, r4, 0x1
	addi r3, r3, 0x2
	@8:
	addi r6, r6, 0xa
	addi r8, r8, 0x4
	bdnz @3
	cmpwi r4, 0x14
	slwi r0, r4, 1
	addi r6, r1, 0x8
	subfic r3, r4, 0x14
	add r6, r6, r0
	li r5, 0x0
	bge @9
	srwi. r0, r3, 3
	mtctr r0
	beq @10
	@11:
	sth r5, 0x0(r6)
	sth r5, 0x2(r6)
	sth r5, 0x4(r6)
	sth r5, 0x6(r6)
	sth r5, 0x8(r6)
	sth r5, 0xa(r6)
	sth r5, 0xc(r6)
	sth r5, 0xe(r6)
	addi r6, r6, 0x10
	bdnz @11
	andi. r3, r3, 0x7
	beq @9
	@10:
	mtctr r3
	@12:
	sth r5, 0x0(r6)
	addi r6, r6, 0x2
	bdnz @12
	@9:
	cmpwi r31, 0x0
	bne @13
	lis r3, comp_aiueo@ha
	li r5, 0x2
	addi r6, r3, comp_aiueo@l
	addi r3, r1, 0x8
	bl qqsort
	b @14
	@13:
	cmpwi r31, 0x1
	bne @15
	lis r3, comp_kind@ha
	li r5, 0x2
	addi r6, r3, comp_kind@l
	addi r3, r1, 0x8
	bl qqsort
	b @14
	@15:
	cmpwi r31, 0x7
	bne @16
	lis r3, comp_aiueo_r@ha
	li r5, 0x2
	addi r6, r3, comp_aiueo_r@l
	addi r3, r1, 0x8
	bl qqsort
	b @14
	@16:
	cmpwi r31, 0x8
	bne @14
	lis r3, comp_kind_r@ha
	li r5, 0x2
	addi r6, r3, comp_kind_r@l
	addi r3, r1, 0x8
	bl qqsort
	@14:
	addi r3, r29, 0x192
	addi r4, r1, 0x8
	li r5, 0x28
	bl memcpy
	@2:
	subi r0, r31, 0x2
	cmplwi r0, 0x1
	ble @17
	cmpwi r31, 0x9
	beq @17
	cmpwi r31, 0xa
	bne @18
	@17:
	li r0, 0x79
	mr r6, r29
	addi r5, r1, 0x30
	li r4, 0x0
	li r3, 0x0
	mtctr r0
	@19:
	lha r7, 0xa0(r6)
	extsh. r0, r7
	beq @20
	sthx r7, r5, r3
	addi r4, r4, 0x1
	addi r3, r3, 0x2
	@20:
	addi r6, r6, 0x2
	bdnz @19
	cmpwi r4, 0x79
	slwi r0, r4, 1
	addi r6, r1, 0x30
	subfic r3, r4, 0x79
	add r6, r6, r0
	li r5, 0x0
	bge @21
	srwi. r0, r3, 3
	mtctr r0
	beq @22
	@23:
	sth r5, 0x0(r6)
	sth r5, 0x2(r6)
	sth r5, 0x4(r6)
	sth r5, 0x6(r6)
	sth r5, 0x8(r6)
	sth r5, 0xa(r6)
	sth r5, 0xc(r6)
	sth r5, 0xe(r6)
	addi r6, r6, 0x10
	bdnz @23
	andi. r3, r3, 0x7
	beq @21
	@22:
	mtctr r3
	@24:
	sth r5, 0x0(r6)
	addi r6, r6, 0x2
	bdnz @24
	@21:
	cmpwi r31, 0x2
	bne @25
	lis r3, comp_aiueo@ha
	li r5, 0x2
	addi r6, r3, comp_aiueo@l
	addi r3, r1, 0x30
	bl qqsort
	b @26
	@25:
	cmpwi r31, 0x3
	bne @27
	lis r3, comp_kind@ha
	li r5, 0x2
	addi r6, r3, comp_kind@l
	addi r3, r1, 0x30
	bl qqsort
	b @26
	@27:
	cmpwi r31, 0x9
	bne @28
	lis r3, comp_aiueo_r@ha
	li r5, 0x2
	addi r6, r3, comp_aiueo_r@l
	addi r3, r1, 0x30
	bl qqsort
	b @26
	@28:
	cmpwi r31, 0xa
	bne @26
	lis r3, comp_kind_r@ha
	li r5, 0x2
	addi r6, r3, comp_kind_r@l
	addi r3, r1, 0x30
	bl qqsort
	@26:
	addi r3, r29, 0xa0
	addi r4, r1, 0x30
	li r5, 0xf2
	bl memcpy
	@18:
	subi r0, r31, 0x4
	cmplwi r0, 0x2
	ble @29
	subi r0, r31, 0xb
	cmplwi r0, 0x1
	ble @29
	cmpwi r31, 0xd
	bne @30
	@29:
	addi r26, r1, 0x2b4
	addi r25, r1, 0x124
	li r0, 0x28
	mr r3, r29
	mr r4, r26
	mr r5, r25
	li r22, 0x0
	li r7, 0x0
	mtctr r0
	@31:
	lha r6, 0x1fa(r3)
	extsh. r0, r6
	beq @32
	sth r6, 0x0(r4)
	addi r4, r4, 0x2
	addi r22, r22, 0x1
	lha r0, 0x38a(r3)
	sth r0, 0x0(r5)
	addi r5, r5, 0x2
	@32:
	lha r6, 0x1fc(r3)
	extsh. r0, r6
	beq @33
	sth r6, 0x0(r4)
	addi r4, r4, 0x2
	addi r22, r22, 0x1
	lha r0, 0x38c(r3)
	sth r0, 0x0(r5)
	addi r5, r5, 0x2
	@33:
	lha r6, 0x1fe(r3)
	extsh. r0, r6
	beq @34
	sth r6, 0x0(r4)
	addi r4, r4, 0x2
	addi r22, r22, 0x1
	lha r0, 0x38e(r3)
	sth r0, 0x0(r5)
	addi r5, r5, 0x2
	@34:
	lha r6, 0x200(r3)
	extsh. r0, r6
	beq @35
	sth r6, 0x0(r4)
	addi r4, r4, 0x2
	addi r22, r22, 0x1
	lha r0, 0x390(r3)
	sth r0, 0x0(r5)
	addi r5, r5, 0x2
	@35:
	lha r6, 0x202(r3)
	extsh. r0, r6
	beq @36
	sth r6, 0x0(r4)
	addi r4, r4, 0x2
	addi r22, r22, 0x1
	lha r0, 0x392(r3)
	sth r0, 0x0(r5)
	addi r5, r5, 0x2
	@36:
	addi r3, r3, 0xa
	addi r7, r7, 0x4
	bdnz @31
	cmpwi r22, 0xc8
	slwi r0, r22, 1
	addi r5, r1, 0x2b4
	addi r6, r1, 0x124
	add r5, r5, r0
	subfic r3, r22, 0xc8
	add r6, r6, r0
	li r4, 0x0
	bge @37
	srwi. r0, r3, 3
	mtctr r0
	beq @38
	@39:
	sth r4, 0x0(r5)
	sth r4, 0x0(r6)
	sth r4, 0x2(r5)
	sth r4, 0x2(r6)
	sth r4, 0x4(r5)
	sth r4, 0x4(r6)
	sth r4, 0x6(r5)
	sth r4, 0x6(r6)
	sth r4, 0x8(r5)
	sth r4, 0x8(r6)
	sth r4, 0xa(r5)
	sth r4, 0xa(r6)
	sth r4, 0xc(r5)
	sth r4, 0xc(r6)
	sth r4, 0xe(r5)
	addi r5, r5, 0x10
	sth r4, 0xe(r6)
	addi r6, r6, 0x10
	bdnz @39
	andi. r3, r3, 0x7
	beq @37
	@38:
	mtctr r3
	@40:
	sth r4, 0x0(r5)
	addi r5, r5, 0x2
	sth r4, 0x0(r6)
	addi r6, r6, 0x2
	bdnz @40
	@37:
	lis r3, itemDataTable@ha
	subi r20, r22, 0x1
	addi r30, r3, itemDataTable@l
	li r24, 0x0
	b @41
	@42:
	addi r23, r24, 0x1
	addi r28, r1, 0x2b4
	slwi r0, r23, 1
	addi r27, r1, 0x124
	add r28, r28, r0
	add r27, r27, r0
	b @43
	@44:
	lha r3, 0x0(r26)
	cmpwi r31, 0x4
	lha r0, 0x0(r28)
	li r21, 0x0
	mulli r3, r3, 0x28
	add r5, r30, r3
	mulli r0, r0, 0x28
	lbz r7, 0x1c(r5)
	lwz r3, 0x0(r5)
	extsb r7, r7
	add r6, r30, r0
	lbz r0, 0x1c(r6)
	lwz r4, 0x0(r6)
	extsb r0, r0
	bne @45
	bl strcmp
	cmpwi r3, 0x0
	ble @46
	li r21, 0x1
	b @46
	@45:
	cmpwi r31, 0xb
	bne @47
	bl strcmp
	cmpwi r3, 0x0
	bge @46
	li r21, 0x1
	b @46
	@47:
	cmpwi r31, 0x5
	bne @48
	lha r3, 0x12(r5)
	lha r0, 0x12(r6)
	cmpw r3, r0
	ble @46
	li r21, 0x1
	b @46
	@48:
	cmpwi r31, 0xc
	bne @49
	lha r3, 0x12(r5)
	lha r0, 0x12(r6)
	cmpw r3, r0
	bge @46
	li r21, 0x1
	b @46
	@49:
	cmpwi r31, 0x6
	bne @50
	cmpw r7, r0
	ble @51
	li r21, 0x1
	b @46
	@51:
	bne @46
	lha r3, 0x12(r5)
	lha r0, 0x12(r6)
	cmpw r3, r0
	ble @46
	li r21, 0x1
	b @46
	@50:
	cmpwi r31, 0xd
	bne @46
	cmpw r7, r0
	bge @52
	li r21, 0x1
	b @46
	@52:
	bne @46
	lha r3, 0x12(r5)
	lha r0, 0x12(r6)
	cmpw r3, r0
	bge @46
	li r21, 0x1
	@46:
	cmpwi r21, 0x0
	beq @53
	lha r5, 0x0(r26)
	lha r3, 0x0(r28)
	lha r4, 0x0(r25)
	lha r0, 0x0(r27)
	sth r3, 0x0(r26)
	sth r0, 0x0(r25)
	sth r5, 0x0(r28)
	sth r4, 0x0(r27)
	@53:
	addi r28, r28, 0x2
	addi r27, r27, 0x2
	addi r23, r23, 0x1
	@43:
	cmpw r23, r22
	blt @44
	addi r26, r26, 0x2
	addi r25, r25, 0x2
	addi r24, r24, 0x1
	@41:
	cmpw r24, r20
	blt @42
	addi r3, r29, 0x1fa
	addi r4, r1, 0x2b4
	li r5, 0x190
	bl memcpy
	addi r3, r29, 0x38a
	addi r4, r1, 0x124
	li r5, 0x190
	bl memcpy
	@30:
	lmw r20, 0x450(r1)
	lwz r0, 0x484(r1)
	mtlr r0
	addi r1, r1, 0x480
	blr
}

asm s32 comp_kind_r(s16* a, s16* b) {
	nofralloc
	lha r3, 0x0(r3)
	lis r5, itemDataTable@ha
	lha r0, 0x0(r4)
	addi r4, r5, itemDataTable@l
	mulli r3, r3, 0x28
	addi r4, r4, 0x12
	mulli r0, r0, 0x28
	lhax r3, r4, r3
	lhax r4, r4, r0
	cmpw r3, r4
	bge @1
	li r3, 0x1
	blr
	@1:
	subfc r0, r3, r4
	srwi r3, r3, 31
	srwi r0, r4, 31
	subfe r3, r0, r3
	blr
}

asm s32 comp_aiueo_r(const void* a, const void* b) {
	nofralloc
	stwu r1, -0x120(r1)
	mflr r0
	stw r0, 0x124(r1)
	lha r0, 0x0(r3)
	lis r3, itemDataTable@ha
	stw r31, 0x11c(r1)
	addi r3, r3, itemDataTable@l
	mulli r0, r0, 0x28
	stw r30, 0x118(r1)
	addi r30, r3, 0x4
	stw r29, 0x114(r1)
	lha r29, 0x0(r4)
	lwzx r3, r30, r0
	bl msgSearch
	mr r31, r3
	bl strlen
	srwi. r0, r3, 1
	addi r5, r1, 0x88
	li r3, 0x0
	mtctr r0
	ble @1
	@2:
	lhz r4, 0x0(r31)
	cmplwi r4, 0x829f
	blt @3
	cmplwi r4, 0x82de
	bge @3
	addi r4, r4, 0xa1
	b @4
	@3:
	cmplwi r4, 0x82de
	blt @4
	cmplwi r4, 0x82f1
	bgt @4
	addi r4, r4, 0xa2
	@4:
	sth r4, 0x0(r5)
	addi r31, r31, 0x2
	addi r5, r5, 0x2
	addi r3, r3, 0x1
	bdnz @2
	@1:
	mulli r0, r29, 0x28
	slwi r4, r3, 1
	addi r3, r1, 0x88
	li r5, 0x0
	stbx r5, r3, r4
	lwzx r3, r30, r0
	bl msgSearch
	mr r31, r3
	bl strlen
	srwi. r0, r3, 1
	addi r5, r1, 0x8
	li r4, 0x0
	mtctr r0
	ble @5
	@6:
	lhz r3, 0x0(r31)
	cmplwi r3, 0x829f
	blt @7
	cmplwi r3, 0x82de
	bge @7
	addi r3, r3, 0xa1
	b @8
	@7:
	cmplwi r3, 0x82de
	blt @8
	cmplwi r3, 0x82f1
	bgt @8
	addi r3, r3, 0xa2
	@8:
	sth r3, 0x0(r5)
	addi r31, r31, 0x2
	addi r5, r5, 0x2
	addi r4, r4, 0x1
	bdnz @6
	@5:
	slwi r0, r4, 1
	addi r3, r1, 0x8
	li r5, 0x0
	addi r4, r1, 0x88
	stbx r5, r3, r0
	bl strcmp
	lwz r0, 0x124(r1)
	lwz r31, 0x11c(r1)
	lwz r30, 0x118(r1)
	lwz r29, 0x114(r1)
	mtlr r0
	addi r1, r1, 0x120
	blr
}

asm s32 comp_kind(s16* a, s16* b) {
	nofralloc
	lha r3, 0x0(r3)
	lis r5, itemDataTable@ha
	lha r0, 0x0(r4)
	addi r4, r5, itemDataTable@l
	mulli r3, r3, 0x28
	addi r4, r4, 0x12
	mulli r0, r0, 0x28
	lhax r5, r4, r3
	lhax r3, r4, r0
	cmpw r5, r3
	ble @1
	li r3, 0x1
	blr
	@1:
	subfc r0, r3, r5
	srwi r3, r3, 31
	srwi r0, r5, 31
	subfe r3, r0, r3
	blr
}

asm s32 comp_aiueo(const void* a, const void* b) {
	nofralloc
	stwu r1, -0x120(r1)
	mflr r0
	stw r0, 0x124(r1)
	lha r0, 0x0(r3)
	lis r3, itemDataTable@ha
	stw r31, 0x11c(r1)
	addi r3, r3, itemDataTable@l
	mulli r0, r0, 0x28
	stw r30, 0x118(r1)
	addi r30, r3, 0x4
	stw r29, 0x114(r1)
	lha r29, 0x0(r4)
	lwzx r3, r30, r0
	bl msgSearch
	mr r31, r3
	bl strlen
	srwi. r0, r3, 1
	addi r5, r1, 0x88
	li r3, 0x0
	mtctr r0
	ble @1
	@2:
	lhz r4, 0x0(r31)
	cmplwi r4, 0x829f
	blt @3
	cmplwi r4, 0x82de
	bge @3
	addi r4, r4, 0xa1
	b @4
	@3:
	cmplwi r4, 0x82de
	blt @4
	cmplwi r4, 0x82f1
	bgt @4
	addi r4, r4, 0xa2
	@4:
	sth r4, 0x0(r5)
	addi r31, r31, 0x2
	addi r5, r5, 0x2
	addi r3, r3, 0x1
	bdnz @2
	@1:
	mulli r0, r29, 0x28
	slwi r4, r3, 1
	addi r3, r1, 0x88
	li r5, 0x0
	stbx r5, r3, r4
	lwzx r3, r30, r0
	bl msgSearch
	mr r31, r3
	bl strlen
	srwi. r0, r3, 1
	addi r5, r1, 0x8
	li r3, 0x0
	mtctr r0
	ble @5
	@6:
	lhz r4, 0x0(r31)
	cmplwi r4, 0x829f
	blt @7
	cmplwi r4, 0x82de
	bge @7
	addi r4, r4, 0xa1
	b @8
	@7:
	cmplwi r4, 0x82de
	blt @8
	cmplwi r4, 0x82f1
	bgt @8
	addi r4, r4, 0xa2
	@8:
	sth r4, 0x0(r5)
	addi r31, r31, 0x2
	addi r5, r5, 0x2
	addi r3, r3, 0x1
	bdnz @6
	@5:
	slwi r0, r3, 1
	addi r4, r1, 0x8
	li r5, 0x0
	addi r3, r1, 0x88
	stbx r5, r4, r0
	bl strcmp
	lwz r0, 0x124(r1)
	lwz r31, 0x11c(r1)
	lwz r30, 0x118(r1)
	lwz r29, 0x114(r1)
	mtlr r0
	addi r1, r1, 0x120
	blr
}

asm void unk_800d06b4(const char* src, char* dst) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r4
	stw r30, 0x8(r1)
	mr r30, r3
	bl strlen
	srwi. r0, r3, 1
	mr r4, r30
	mr r5, r31
	li r6, 0x0
	mtctr r0
	ble @1
	@2:
	lhz r3, 0x0(r4)
	cmplwi r3, 0x829f
	blt @3
	cmplwi r3, 0x82de
	bge @3
	addi r3, r3, 0xa1
	b @4
	@3:
	cmplwi r3, 0x82de
	blt @4
	cmplwi r3, 0x82f1
	bgt @4
	addi r3, r3, 0xa2
	@4:
	sth r3, 0x0(r5)
	addi r4, r4, 0x2
	addi r5, r5, 0x2
	addi r6, r6, 0x1
	bdnz @2
	@1:
	slwi r0, r6, 1
	li r3, 0x0
	stbx r3, r31, r0
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BOOL pouchRemoveItemIndex(ItemType type, s32 index) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	li r31, 0x0
	stw r30, 0x18(r1)
	li r30, 0x0
	stw r29, 0x14(r1)
	mr r29, r4
	li r4, 0x0
	stw r28, 0x10(r1)
	mr r28, r3
	cmpwi r28, 0x79
	blt @1
	cmpwi r28, 0xec
	bge @1
	lwz r4, mpp(r13)
	li r30, 0x0
	li r3, 0x1
	addi r31, r4, 0x192
	bl pouchCheckItem
	cmpwi r3, 0x0
	li r0, 0xa
	beq @2
	li r0, 0x14
	@2:
	mr r4, r0
	li r0, 0x1
	b @3
	@1:
	cmpwi r28, 0x1
	blt @4
	cmpwi r28, 0x79
	bge @4
	lwz r3, mpp(r13)
	li r30, 0x0
	li r4, 0x79
	li r0, 0x1
	addi r31, r3, 0xa0
	b @3
	@4:
	cmpwi r28, 0xf0
	blt @5
	cmpwi r28, 0x153
	bge @5
	lwz r3, mpp(r13)
	li r4, 0xc8
	li r0, 0x1
	addi r31, r3, 0x1fa
	addi r30, r3, 0x38a
	b @3
	@5:
	li r0, 0x0
	@3:
	cmpwi r0, 0x0
	bne @6
	li r3, 0x0
	b @7
	@6:
	slwi r0, r29, 1
	add r3, r31, r0
	lha r0, 0x0(r3)
	cmpw r28, r0
	beq @8
	li r3, 0x0
	b @7
	@8:
	subf r0, r29, r4
	mr r7, r29
	mtctr r0
	cmpw r29, r4
	bge @9
	@10:
	lha r0, 0x0(r3)
	cmpw r28, r0
	bne @11
	cmplwi r30, 0x0
	slwi r3, r7, 1
	li r0, 0x0
	sthx r0, r31, r3
	beq @12
	sthx r0, r30, r3
	b @12
	@13:
	cmplwi r30, 0x0
	subi r0, r4, 0x1
	li r4, 0x0
	beq @14
	cmpw r7, r0
	subf r3, r7, r0
	bge @15
	srwi. r0, r3, 2
	mtctr r0
	beq @16
	@17:
	lha r0, 0x2(r5)
	sth r0, 0x0(r5)
	sth r4, 0x2(r5)
	lha r0, 0x2(r6)
	sth r0, 0x0(r6)
	sth r4, 0x2(r6)
	lha r0, 0x4(r5)
	sth r0, 0x2(r5)
	sth r4, 0x4(r5)
	lha r0, 0x4(r6)
	sth r0, 0x2(r6)
	sth r4, 0x4(r6)
	lha r0, 0x6(r5)
	sth r0, 0x4(r5)
	sth r4, 0x6(r5)
	lha r0, 0x6(r6)
	sth r0, 0x4(r6)
	sth r4, 0x6(r6)
	lha r0, 0x8(r5)
	sth r0, 0x6(r5)
	sthu r4, 0x8(r5)
	lha r0, 0x8(r6)
	sth r0, 0x6(r6)
	sthu r4, 0x8(r6)
	bdnz @17
	andi. r3, r3, 0x3
	beq @15
	@16:
	mtctr r3
	@18:
	lha r0, 0x2(r5)
	sth r0, 0x0(r5)
	sthu r4, 0x2(r5)
	lha r0, 0x2(r6)
	sth r0, 0x0(r6)
	sthu r4, 0x2(r6)
	bdnz @18
	b @15
	@14:
	cmpw r7, r0
	subf r3, r7, r0
	bge @15
	srwi. r0, r3, 3
	mtctr r0
	beq @19
	@20:
	lha r0, 0x2(r5)
	sth r0, 0x0(r5)
	sth r4, 0x2(r5)
	lha r0, 0x4(r5)
	sth r0, 0x2(r5)
	sth r4, 0x4(r5)
	lha r0, 0x6(r5)
	sth r0, 0x4(r5)
	sth r4, 0x6(r5)
	lha r0, 0x8(r5)
	sth r0, 0x6(r5)
	sth r4, 0x8(r5)
	lha r0, 0xa(r5)
	sth r0, 0x8(r5)
	sth r4, 0xa(r5)
	lha r0, 0xc(r5)
	sth r0, 0xa(r5)
	sth r4, 0xc(r5)
	lha r0, 0xe(r5)
	sth r0, 0xc(r5)
	sth r4, 0xe(r5)
	lha r0, 0x10(r5)
	sth r0, 0xe(r5)
	sthu r4, 0x10(r5)
	bdnz @20
	andi. r3, r3, 0x7
	beq @15
	@19:
	mtctr r3
	@21:
	lha r0, 0x2(r5)
	sth r0, 0x0(r5)
	sthu r4, 0x2(r5)
	bdnz @21
	@15:
	li r3, 0x1
	b @7
	@11:
	addi r3, r3, 0x2
	addi r7, r7, 0x1
	bdnz @10
	@9:
	li r3, 0x0
	b @7
	@12:
	add r5, r31, r3
	add r6, r30, r3
	b @13
	@7:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm BOOL pouchRemoveItem(ItemType type) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	li r4, 0x0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	li r31, 0x0
	stw r30, 0x18(r1)
	li r30, 0x0
	stw r29, 0x14(r1)
	mr r29, r3
	cmpwi r29, 0x79
	blt @1
	cmpwi r29, 0xec
	bge @1
	lwz r4, mpp(r13)
	li r30, 0x0
	li r3, 0x1
	addi r31, r4, 0x192
	bl pouchCheckItem
	cmpwi r3, 0x0
	li r0, 0xa
	beq @2
	li r0, 0x14
	@2:
	mr r4, r0
	li r0, 0x1
	b @3
	@1:
	cmpwi r29, 0x1
	blt @4
	cmpwi r29, 0x79
	bge @4
	lwz r3, mpp(r13)
	li r30, 0x0
	li r4, 0x79
	li r0, 0x1
	addi r31, r3, 0xa0
	b @3
	@4:
	cmpwi r29, 0xf0
	blt @5
	cmpwi r29, 0x153
	bge @5
	lwz r3, mpp(r13)
	li r4, 0xc8
	li r0, 0x1
	addi r31, r3, 0x1fa
	addi r30, r3, 0x38a
	b @3
	@5:
	li r0, 0x0
	@3:
	cmpwi r0, 0x0
	bne @6
	li r3, 0x0
	b @7
	@6:
	mr r3, r31
	li r7, 0x0
	mtctr r4
	cmpwi r4, 0x0
	ble @8
	@9:
	lha r0, 0x0(r3)
	cmpw r29, r0
	bne @10
	cmplwi r30, 0x0
	slwi r3, r7, 1
	li r0, 0x0
	sthx r0, r31, r3
	beq @11
	sthx r0, r30, r3
	b @11
	@12:
	cmplwi r30, 0x0
	subi r0, r4, 0x1
	li r4, 0x0
	beq @13
	cmpw r7, r0
	subf r3, r7, r0
	bge @14
	srwi. r0, r3, 2
	mtctr r0
	beq @15
	@16:
	lha r0, 0x2(r5)
	sth r0, 0x0(r5)
	sth r4, 0x2(r5)
	lha r0, 0x2(r6)
	sth r0, 0x0(r6)
	sth r4, 0x2(r6)
	lha r0, 0x4(r5)
	sth r0, 0x2(r5)
	sth r4, 0x4(r5)
	lha r0, 0x4(r6)
	sth r0, 0x2(r6)
	sth r4, 0x4(r6)
	lha r0, 0x6(r5)
	sth r0, 0x4(r5)
	sth r4, 0x6(r5)
	lha r0, 0x6(r6)
	sth r0, 0x4(r6)
	sth r4, 0x6(r6)
	lha r0, 0x8(r5)
	sth r0, 0x6(r5)
	sthu r4, 0x8(r5)
	lha r0, 0x8(r6)
	sth r0, 0x6(r6)
	sthu r4, 0x8(r6)
	bdnz @16
	andi. r3, r3, 0x3
	beq @14
	@15:
	mtctr r3
	@17:
	lha r0, 0x2(r5)
	sth r0, 0x0(r5)
	sthu r4, 0x2(r5)
	lha r0, 0x2(r6)
	sth r0, 0x0(r6)
	sthu r4, 0x2(r6)
	bdnz @17
	b @14
	@13:
	cmpw r7, r0
	subf r3, r7, r0
	bge @14
	srwi. r0, r3, 3
	mtctr r0
	beq @18
	@19:
	lha r0, 0x2(r5)
	sth r0, 0x0(r5)
	sth r4, 0x2(r5)
	lha r0, 0x4(r5)
	sth r0, 0x2(r5)
	sth r4, 0x4(r5)
	lha r0, 0x6(r5)
	sth r0, 0x4(r5)
	sth r4, 0x6(r5)
	lha r0, 0x8(r5)
	sth r0, 0x6(r5)
	sth r4, 0x8(r5)
	lha r0, 0xa(r5)
	sth r0, 0x8(r5)
	sth r4, 0xa(r5)
	lha r0, 0xc(r5)
	sth r0, 0xa(r5)
	sth r4, 0xc(r5)
	lha r0, 0xe(r5)
	sth r0, 0xc(r5)
	sth r4, 0xe(r5)
	lha r0, 0x10(r5)
	sth r0, 0xe(r5)
	sthu r4, 0x10(r5)
	bdnz @19
	andi. r3, r3, 0x7
	beq @14
	@18:
	mtctr r3
	@20:
	lha r0, 0x2(r5)
	sth r0, 0x0(r5)
	sthu r4, 0x2(r5)
	bdnz @20
	@14:
	li r3, 0x1
	b @7
	@10:
	addi r3, r3, 0x2
	addi r7, r7, 0x1
	bdnz @9
	@8:
	li r3, 0x0
	b @7
	@11:
	add r5, r31, r3
	add r6, r30, r3
	b @12
	@7:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm u32 pouchCheckItem(u32 itemId) {
	nofralloc
	cmpwi r3, 0x79
	blt @1
	cmpwi r3, 0xec
	bge @1
	li r0, 0x2
	lwz r4, mpp(r13)
	li r6, 0x0
	li r5, 0x0
	mtctr r0
	@2:
	lha r0, 0x192(r4)
	cmpw r3, r0
	bne @3
	addi r6, r6, 0x1
	@3:
	lha r0, 0x194(r4)
	cmpw r3, r0
	bne @4
	addi r6, r6, 0x1
	@4:
	lha r0, 0x196(r4)
	cmpw r3, r0
	bne @5
	addi r6, r6, 0x1
	@5:
	lha r0, 0x198(r4)
	cmpw r3, r0
	bne @6
	addi r6, r6, 0x1
	@6:
	lha r0, 0x19a(r4)
	cmpw r3, r0
	bne @7
	addi r6, r6, 0x1
	@7:
	lha r0, 0x19c(r4)
	cmpw r3, r0
	bne @8
	addi r6, r6, 0x1
	@8:
	lha r0, 0x19e(r4)
	cmpw r3, r0
	bne @9
	addi r6, r6, 0x1
	@9:
	lha r0, 0x1a0(r4)
	cmpw r3, r0
	bne @10
	addi r6, r6, 0x1
	@10:
	lha r0, 0x1a2(r4)
	cmpw r3, r0
	bne @11
	addi r6, r6, 0x1
	@11:
	lha r0, 0x1a4(r4)
	cmpw r3, r0
	bne @12
	addi r6, r6, 0x1
	@12:
	addi r4, r4, 0x14
	addi r5, r5, 0x9
	bdnz @2
	mr r3, r6
	blr
	@1:
	cmpwi r3, 0x1
	blt @13
	cmpwi r3, 0x79
	bge @13
	li r0, 0x79
	lwz r4, mpp(r13)
	li r5, 0x0
	mtctr r0
	@14:
	lha r0, 0xa0(r4)
	cmpw r3, r0
	bne @15
	addi r5, r5, 0x1
	@15:
	addi r4, r4, 0x2
	bdnz @14
	mr r3, r5
	blr
	@13:
	cmpwi r3, 0xf0
	blt @16
	cmpwi r3, 0x153
	bge @16
	li r5, 0x0
	li r0, 0x14
	mr r6, r5
	lwz r4, mpp(r13)
	mtctr r0
	@17:
	lha r0, 0x1fa(r4)
	cmpw r3, r0
	bne @18
	addi r5, r5, 0x1
	@18:
	lha r0, 0x1fc(r4)
	cmpw r3, r0
	bne @19
	addi r5, r5, 0x1
	@19:
	lha r0, 0x1fe(r4)
	cmpw r3, r0
	bne @20
	addi r5, r5, 0x1
	@20:
	lha r0, 0x200(r4)
	cmpw r3, r0
	bne @21
	addi r5, r5, 0x1
	@21:
	lha r0, 0x202(r4)
	cmpw r3, r0
	bne @22
	addi r5, r5, 0x1
	@22:
	lha r0, 0x204(r4)
	cmpw r3, r0
	bne @23
	addi r5, r5, 0x1
	@23:
	lha r0, 0x206(r4)
	cmpw r3, r0
	bne @24
	addi r5, r5, 0x1
	@24:
	lha r0, 0x208(r4)
	cmpw r3, r0
	bne @25
	addi r5, r5, 0x1
	@25:
	lha r0, 0x20a(r4)
	cmpw r3, r0
	bne @26
	addi r5, r5, 0x1
	@26:
	lha r0, 0x20c(r4)
	cmpw r3, r0
	bne @27
	addi r5, r5, 0x1
	@27:
	addi r4, r4, 0x14
	addi r6, r6, 0x9
	bdnz @17
	mr r3, r5
	blr
	@16:
	li r3, 0x0
	blr
}

asm BOOL pouchGetItem(ItemType type) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	cmpwi r31, 0x79
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	bne @1
	lwz r4, mpp(r13)
	lha r3, 0x78(r4)
	cmpwi r3, 0x3e7
	bge @2
	addi r0, r3, 0x1
	sth r0, 0x78(r4)
	@2:
	li r3, 0x1
	b @3
	@1:
	cmpwi r31, 0x7a
	bne @4
	lwz r4, yuwp(r13)
	lis r3, 0x2
	subi r0, r3, 0x7961
	lwz r3, 0x8(r4)
	cmpw r3, r0
	bge @5
	addi r0, r3, 0x1
	stw r0, 0x8(r4)
	@5:
	li r3, 0x1
	b @3
	@4:
	cmpwi r31, 0x7b
	bne @6
	bl marioGetParty
	lwz r5, mpp(r13)
	lha r4, 0x70(r5)
	lha r0, 0x72(r5)
	cmpw r4, r0
	bge @7
	addi r0, r4, 0x1
	sth r0, 0x70(r5)
	@7:
	cmpwi r3, 0x0
	beq @8
	mulli r0, r3, 0xe
	lwz r3, mpp(r13)
	add r4, r3, r0
	lha r3, 0x6(r4)
	lha r0, 0x2(r4)
	cmpw r3, r0
	bge @8
	addi r0, r3, 0x1
	sth r0, 0x6(r4)
	@8:
	li r3, 0x1
	b @3
	@6:
	cmpwi r31, 0x7c
	bne @9
	lwz r4, mpp(r13)
	lha r3, 0x74(r4)
	lha r0, 0x76(r4)
	cmpw r3, r0
	bge @10
	addi r0, r3, 0x1
	sth r0, 0x74(r4)
	@10:
	li r3, 0x1
	b @3
	@9:
	cmpwi r31, 0x7d
	bne @11
	lwz r5, mpp(r13)
	li r3, 0x1
	lha r4, 0x9a(r5)
	addi r0, r4, 0x1
	sth r0, 0x9a(r5)
	b @3
	@11:
	cmpwi r31, 0x57
	bne @12
	lwz r5, mpp(r13)
	li r3, 0x1
	lha r4, 0x9c(r5)
	addi r0, r4, 0x1
	sth r0, 0x9c(r5)
	b @3
	@12:
	subi r0, r31, 0x6
	cmplwi r0, 0x1
	ble @13
	cmpwi r31, 0x8
	bne @14
	@13:
	cmpwi r31, 0x7
	beq @15
	bge @16
	cmpwi r31, 0x6
	bge @17
	b @18
	@16:
	cmpwi r31, 0x9
	bge @18
	b @19
	@17:
	lwz r3, mpp(r13)
	li r0, 0x1
	stb r0, 0x98(r3)
	b @18
	@15:
	lwz r3, mpp(r13)
	li r0, 0x2
	stb r0, 0x98(r3)
	b @18
	@19:
	lwz r3, mpp(r13)
	li r0, 0x3
	stb r0, 0x98(r3)
	b @18
	@14:
	subi r0, r31, 0x9
	cmplwi r0, 0x1
	ble @20
	cmpwi r31, 0xb
	bne @21
	@20:
	cmpwi r31, 0xa
	beq @22
	bge @23
	cmpwi r31, 0x9
	bge @24
	b @18
	@23:
	cmpwi r31, 0xc
	bge @18
	b @25
	@24:
	lwz r3, mpp(r13)
	li r0, 0x1
	stb r0, 0x99(r3)
	b @18
	@22:
	lwz r3, mpp(r13)
	li r0, 0x2
	stb r0, 0x99(r3)
	b @18
	@25:
	lwz r3, mpp(r13)
	li r0, 0x3
	stb r0, 0x99(r3)
	b @18
	@21:
	cmpwi r31, 0x59
	bne @26
	li r3, 0x1
	b @3
	@26:
	cmpwi r31, 0xf0
	blt @18
	cmpwi r31, 0x153
	bge @18
	subi r3, r31, 0x70
	bl swSet
	@18:
	cmpwi r31, 0x79
	li r4, 0x0
	mr r29, r4
	mr r30, r4
	blt @27
	cmpwi r31, 0xec
	bge @27
	lwz r4, mpp(r13)
	li r3, 0x1
	addi r29, r4, 0x192
	bl pouchCheckItem
	cmpwi r3, 0x0
	li r4, 0xa
	beq @28
	li r4, 0x14
	@28:
	li r0, 0x1
	b @29
	@27:
	cmpwi r31, 0x1
	blt @30
	cmpwi r31, 0x79
	bge @30
	lwz r3, mpp(r13)
	li r30, 0x0
	li r4, 0x79
	li r0, 0x1
	addi r29, r3, 0xa0
	b @29
	@30:
	cmpwi r31, 0xf0
	blt @31
	cmpwi r31, 0x153
	bge @31
	lwz r3, mpp(r13)
	li r4, 0xc8
	li r0, 0x1
	addi r29, r3, 0x1fa
	addi r30, r3, 0x38a
	b @29
	@31:
	li r0, 0x0
	@29:
	cmpwi r0, 0x0
	bne @32
	li r3, 0x0
	b @3
	@32:
	subic. r4, r4, 0x1
	slwi r3, r4, 1
	addi r0, r4, 0x1
	add r3, r29, r3
	mtctr r0
	blt @33
	@34:
	lha r0, 0x0(r3)
	cmpwi r0, 0x0
	bne @35
	cmplwi r30, 0x0
	slwi r0, r4, 1
	add r5, r29, r0
	add r3, r30, r0
	beq @36
	cmpwi r4, 0x0
	ble @37
	srwi. r0, r4, 3
	mtctr r0
	beq @38
	@39:
	lha r0, -0x2(r5)
	sth r0, 0x0(r5)
	lha r0, -0x2(r3)
	sth r0, 0x0(r3)
	lha r0, -0x4(r5)
	sth r0, -0x2(r5)
	lha r0, -0x4(r3)
	sth r0, -0x2(r3)
	lha r0, -0x6(r5)
	sth r0, -0x4(r5)
	lha r0, -0x6(r3)
	sth r0, -0x4(r3)
	lha r0, -0x8(r5)
	sth r0, -0x6(r5)
	lha r0, -0x8(r3)
	sth r0, -0x6(r3)
	lha r0, -0xa(r5)
	sth r0, -0x8(r5)
	lha r0, -0xa(r3)
	sth r0, -0x8(r3)
	lha r0, -0xc(r5)
	sth r0, -0xa(r5)
	lha r0, -0xc(r3)
	sth r0, -0xa(r3)
	lha r0, -0xe(r5)
	sth r0, -0xc(r5)
	lha r0, -0xe(r3)
	sth r0, -0xc(r3)
	lha r0, -0x10(r5)
	sth r0, -0xe(r5)
	subi r5, r5, 0x10
	lha r0, -0x10(r3)
	sth r0, -0xe(r3)
	subi r3, r3, 0x10
	bdnz @39
	andi. r4, r4, 0x7
	beq @37
	@38:
	mtctr r4
	@40:
	lha r0, -0x2(r5)
	sth r0, 0x0(r5)
	subi r5, r5, 0x2
	lha r0, -0x2(r3)
	sth r0, 0x0(r3)
	subi r3, r3, 0x2
	bdnz @40
	b @37
	@36:
	cmpwi r4, 0x0
	mr r3, r4
	ble @37
	srwi. r0, r4, 3
	mtctr r0
	beq @41
	@42:
	lha r0, -0x2(r5)
	sth r0, 0x0(r5)
	lha r0, -0x4(r5)
	sth r0, -0x2(r5)
	lha r0, -0x6(r5)
	sth r0, -0x4(r5)
	lha r0, -0x8(r5)
	sth r0, -0x6(r5)
	lha r0, -0xa(r5)
	sth r0, -0x8(r5)
	lha r0, -0xc(r5)
	sth r0, -0xa(r5)
	lha r0, -0xe(r5)
	sth r0, -0xc(r5)
	lha r0, -0x10(r5)
	sth r0, -0xe(r5)
	subi r5, r5, 0x10
	bdnz @42
	andi. r3, r3, 0x7
	beq @37
	@41:
	mtctr r3
	@43:
	lha r0, -0x2(r5)
	sth r0, 0x0(r5)
	subi r5, r5, 0x2
	bdnz @43
	@37:
	cmplwi r30, 0x0
	sth r31, 0x0(r29)
	beq @44
	li r0, 0x0
	sth r0, 0x0(r30)
	@44:
	li r3, 0x1
	b @3
	@35:
	subi r3, r3, 0x2
	subi r4, r4, 0x1
	bdnz @34
	@33:
	li r3, 0x0
	@3:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 pouchGetEmptyKeepItemCnt(void) {
	nofralloc
	li r0, 0x4
	lwz r4, mpp(r13)
	li r3, 0x0
	li r5, 0x0
	mtctr r0
	@1:
	lha r0, 0x1ba(r4)
	cmpwi r0, 0x0
	bne @2
	addi r3, r3, 0x1
	@2:
	lha r0, 0x1bc(r4)
	cmpwi r0, 0x0
	bne @3
	addi r3, r3, 0x1
	@3:
	lha r0, 0x1be(r4)
	cmpwi r0, 0x0
	bne @4
	addi r3, r3, 0x1
	@4:
	lha r0, 0x1c0(r4)
	cmpwi r0, 0x0
	bne @5
	addi r3, r3, 0x1
	@5:
	lha r0, 0x1c2(r4)
	cmpwi r0, 0x0
	bne @6
	addi r3, r3, 0x1
	@6:
	lha r0, 0x1c4(r4)
	cmpwi r0, 0x0
	bne @7
	addi r3, r3, 0x1
	@7:
	lha r0, 0x1c6(r4)
	cmpwi r0, 0x0
	bne @8
	addi r3, r3, 0x1
	@8:
	lha r0, 0x1c8(r4)
	cmpwi r0, 0x0
	bne @9
	addi r3, r3, 0x1
	@9:
	addi r4, r4, 0x10
	addi r5, r5, 0x7
	bdnz @1
	blr
}

asm s32 pouchGetEmptyHaveItemCnt(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x1
	stw r0, 0x14(r1)
	bl pouchCheckItem
	cmpwi r3, 0x0
	li r0, 0xa
	beq @1
	li r0, 0x14
	@1:
	lwz r4, mpp(r13)
	li r3, 0x0
	mtctr r0
	cmpwi r0, 0x0
	ble @2
	@3:
	lha r0, 0x192(r4)
	cmpwi r0, 0x0
	bne @4
	addi r3, r3, 0x1
	@4:
	addi r4, r4, 0x2
	bdnz @3
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 pouchGetEquipBadgeCnt(void) {
	nofralloc
	li r0, 0x14
	lwz r4, mpp(r13)
	li r3, 0x0
	li r5, 0x0
	mtctr r0
	@1:
	lha r0, 0x38a(r4)
	cmpwi r0, 0x0
	beq @2
	addi r3, r3, 0x1
	@2:
	lha r0, 0x38c(r4)
	cmpwi r0, 0x0
	beq @3
	addi r3, r3, 0x1
	@3:
	lha r0, 0x38e(r4)
	cmpwi r0, 0x0
	beq @4
	addi r3, r3, 0x1
	@4:
	lha r0, 0x390(r4)
	cmpwi r0, 0x0
	beq @5
	addi r3, r3, 0x1
	@5:
	lha r0, 0x392(r4)
	cmpwi r0, 0x0
	beq @6
	addi r3, r3, 0x1
	@6:
	lha r0, 0x394(r4)
	cmpwi r0, 0x0
	beq @7
	addi r3, r3, 0x1
	@7:
	lha r0, 0x396(r4)
	cmpwi r0, 0x0
	beq @8
	addi r3, r3, 0x1
	@8:
	lha r0, 0x398(r4)
	cmpwi r0, 0x0
	beq @9
	addi r3, r3, 0x1
	@9:
	lha r0, 0x39a(r4)
	cmpwi r0, 0x0
	beq @10
	addi r3, r3, 0x1
	@10:
	lha r0, 0x39c(r4)
	cmpwi r0, 0x0
	beq @11
	addi r3, r3, 0x1
	@11:
	addi r4, r4, 0x14
	addi r5, r5, 0x9
	bdnz @1
	blr
}

asm s32 pouchGetHaveBadgeCnt(void) {
	nofralloc
	li r0, 0x14
	lwz r4, mpp(r13)
	li r3, 0x0
	li r5, 0x0
	mtctr r0
	@1:
	lha r0, 0x1fa(r4)
	cmpwi r0, 0x0
	beq @2
	addi r3, r3, 0x1
	@2:
	lha r0, 0x1fc(r4)
	cmpwi r0, 0x0
	beq @3
	addi r3, r3, 0x1
	@3:
	lha r0, 0x1fe(r4)
	cmpwi r0, 0x0
	beq @4
	addi r3, r3, 0x1
	@4:
	lha r0, 0x200(r4)
	cmpwi r0, 0x0
	beq @5
	addi r3, r3, 0x1
	@5:
	lha r0, 0x202(r4)
	cmpwi r0, 0x0
	beq @6
	addi r3, r3, 0x1
	@6:
	lha r0, 0x204(r4)
	cmpwi r0, 0x0
	beq @7
	addi r3, r3, 0x1
	@7:
	lha r0, 0x206(r4)
	cmpwi r0, 0x0
	beq @8
	addi r3, r3, 0x1
	@8:
	lha r0, 0x208(r4)
	cmpwi r0, 0x0
	beq @9
	addi r3, r3, 0x1
	@9:
	lha r0, 0x20a(r4)
	cmpwi r0, 0x0
	beq @10
	addi r3, r3, 0x1
	@10:
	lha r0, 0x20c(r4)
	cmpwi r0, 0x0
	beq @11
	addi r3, r3, 0x1
	@11:
	addi r4, r4, 0x14
	addi r5, r5, 0x9
	bdnz @1
	blr
}

asm s32 pouchGetKeepItemCnt(void) {
	nofralloc
	li r0, 0x4
	lwz r4, mpp(r13)
	li r3, 0x0
	li r5, 0x0
	mtctr r0
	@1:
	lha r0, 0x1ba(r4)
	cmpwi r0, 0x0
	beq @2
	addi r3, r3, 0x1
	@2:
	lha r0, 0x1bc(r4)
	cmpwi r0, 0x0
	beq @3
	addi r3, r3, 0x1
	@3:
	lha r0, 0x1be(r4)
	cmpwi r0, 0x0
	beq @4
	addi r3, r3, 0x1
	@4:
	lha r0, 0x1c0(r4)
	cmpwi r0, 0x0
	beq @5
	addi r3, r3, 0x1
	@5:
	lha r0, 0x1c2(r4)
	cmpwi r0, 0x0
	beq @6
	addi r3, r3, 0x1
	@6:
	lha r0, 0x1c4(r4)
	cmpwi r0, 0x0
	beq @7
	addi r3, r3, 0x1
	@7:
	lha r0, 0x1c6(r4)
	cmpwi r0, 0x0
	beq @8
	addi r3, r3, 0x1
	@8:
	lha r0, 0x1c8(r4)
	cmpwi r0, 0x0
	beq @9
	addi r3, r3, 0x1
	@9:
	addi r4, r4, 0x10
	addi r5, r5, 0x7
	bdnz @1
	blr
}

asm s32 pouchGetHaveItemCnt(void) {
	nofralloc
	li r0, 0x2
	lwz r4, mpp(r13)
	li r3, 0x0
	li r5, 0x0
	mtctr r0
	@1:
	lha r0, 0x192(r4)
	cmpwi r0, 0x0
	beq @2
	addi r3, r3, 0x1
	@2:
	lha r0, 0x194(r4)
	cmpwi r0, 0x0
	beq @3
	addi r3, r3, 0x1
	@3:
	lha r0, 0x196(r4)
	cmpwi r0, 0x0
	beq @4
	addi r3, r3, 0x1
	@4:
	lha r0, 0x198(r4)
	cmpwi r0, 0x0
	beq @5
	addi r3, r3, 0x1
	@5:
	lha r0, 0x19a(r4)
	cmpwi r0, 0x0
	beq @6
	addi r3, r3, 0x1
	@6:
	lha r0, 0x19c(r4)
	cmpwi r0, 0x0
	beq @7
	addi r3, r3, 0x1
	@7:
	lha r0, 0x19e(r4)
	cmpwi r0, 0x0
	beq @8
	addi r3, r3, 0x1
	@8:
	lha r0, 0x1a0(r4)
	cmpwi r0, 0x0
	beq @9
	addi r3, r3, 0x1
	@9:
	lha r0, 0x1a2(r4)
	cmpwi r0, 0x0
	beq @10
	addi r3, r3, 0x1
	@10:
	lha r0, 0x1a4(r4)
	cmpwi r0, 0x0
	beq @11
	addi r3, r3, 0x1
	@11:
	addi r4, r4, 0x14
	addi r5, r5, 0x9
	bdnz @1
	blr
}

asm ItemType pouchHaveBadge(s32 id) {
	nofralloc
	lwz r4, mpp(r13)
	slwi r0, r3, 1
	add r3, r4, r0
	lha r3, 0x1fa(r3)
	blr
}

asm ItemType pouchKeepItem(s32 id) {
	nofralloc
	lwz r4, mpp(r13)
	slwi r0, r3, 1
	add r3, r4, r0
	lha r3, 0x1ba(r3)
	blr
}

asm ItemType pouchHaveItem(s32 id) {
	nofralloc
	lwz r4, mpp(r13)
	slwi r0, r3, 1
	add r3, r4, r0
	lha r3, 0x192(r3)
	blr
}

asm ItemType pouchKeyItem(s32 id) {
	nofralloc
	lwz r4, mpp(r13)
	slwi r0, r3, 1
	add r3, r4, r0
	lha r3, 0xa0(r3)
	blr
}

asm void pouchInit(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x0
	li r4, 0x5d4
	stw r0, 0x14(r1)
	bl __memAlloc
	stw r3, mpp(r13)
	li r4, 0x0
	li r5, 0x5d4
	bl memset
	li r0, 0xf
	li r12, 0x0
	li r11, 0x0
	mtctr r0
	@1:
	lwz r3, mpp(r13)
	addi r0, r11, 0xa0
	li r10, 0x0
	addi r8, r11, 0xa2
	sthx r10, r3, r0
	addi r7, r11, 0xa4
	addi r6, r11, 0xa6
	addi r5, r11, 0xa8
	lwz r9, mpp(r13)
	addi r4, r11, 0xaa
	addi r3, r11, 0xac
	addi r0, r11, 0xae
	sthx r10, r9, r8
	addi r11, r11, 0x10
	addi r12, r12, 0x8
	lwz r8, mpp(r13)
	sthx r10, r8, r7
	lwz r7, mpp(r13)
	sthx r10, r7, r6
	lwz r6, mpp(r13)
	sthx r10, r6, r5
	lwz r5, mpp(r13)
	sthx r10, r5, r4
	lwz r4, mpp(r13)
	sthx r10, r4, r3
	lwz r3, mpp(r13)
	sthx r10, r3, r0
	bdnz @1
	subfic r0, r12, 0x79
	slwi r4, r12, 1
	mtctr r0
	cmpwi r12, 0x79
	bge @2
	@3:
	lwz r3, mpp(r13)
	addi r0, r4, 0xa0
	addi r4, r4, 0x2
	sthx r10, r3, r0
	bdnz @3
	@2:
	lwz r3, mpp(r13)
	li r12, 0x0
	li r0, 0x2
	sth r12, 0x192(r3)
	lwz r3, mpp(r13)
	sth r12, 0x194(r3)
	lwz r3, mpp(r13)
	sth r12, 0x196(r3)
	lwz r3, mpp(r13)
	sth r12, 0x198(r3)
	lwz r3, mpp(r13)
	sth r12, 0x19a(r3)
	lwz r3, mpp(r13)
	sth r12, 0x19c(r3)
	lwz r3, mpp(r13)
	sth r12, 0x19e(r3)
	lwz r3, mpp(r13)
	sth r12, 0x1a0(r3)
	lwz r3, mpp(r13)
	sth r12, 0x1a2(r3)
	lwz r3, mpp(r13)
	sth r12, 0x1a4(r3)
	lwz r3, mpp(r13)
	sth r12, 0x1a6(r3)
	lwz r3, mpp(r13)
	sth r12, 0x1a8(r3)
	lwz r3, mpp(r13)
	sth r12, 0x1aa(r3)
	lwz r3, mpp(r13)
	sth r12, 0x1ac(r3)
	lwz r3, mpp(r13)
	sth r12, 0x1ae(r3)
	lwz r3, mpp(r13)
	sth r12, 0x1b0(r3)
	lwz r3, mpp(r13)
	sth r12, 0x1b2(r3)
	lwz r3, mpp(r13)
	sth r12, 0x1b4(r3)
	lwz r3, mpp(r13)
	sth r12, 0x1b6(r3)
	lwz r3, mpp(r13)
	sth r12, 0x1b8(r3)
	mtctr r0
	@4:
	lwz r4, mpp(r13)
	addi r11, r12, 0x1ba
	li r3, 0x0
	addi r10, r12, 0x1bc
	sthx r3, r4, r11
	addi r9, r12, 0x1be
	addi r8, r12, 0x1c0
	addi r7, r12, 0x1c2
	lwz r4, mpp(r13)
	addi r6, r12, 0x1c4
	addi r5, r12, 0x1c6
	addi r0, r12, 0x1c8
	sthx r3, r4, r10
	addi r11, r12, 0x1ca
	addi r10, r12, 0x1cc
	lwz r4, mpp(r13)
	sthx r3, r4, r9
	addi r9, r12, 0x1ce
	lwz r4, mpp(r13)
	sthx r3, r4, r8
	addi r8, r12, 0x1d0
	lwz r4, mpp(r13)
	sthx r3, r4, r7
	addi r7, r12, 0x1d2
	lwz r4, mpp(r13)
	sthx r3, r4, r6
	addi r6, r12, 0x1d4
	lwz r4, mpp(r13)
	sthx r3, r4, r5
	addi r5, r12, 0x1d6
	lwz r4, mpp(r13)
	sthx r3, r4, r0
	addi r0, r12, 0x1d8
	addi r12, r12, 0x20
	lwz r4, mpp(r13)
	sthx r3, r4, r11
	lwz r4, mpp(r13)
	sthx r3, r4, r10
	lwz r4, mpp(r13)
	sthx r3, r4, r9
	lwz r4, mpp(r13)
	sthx r3, r4, r8
	lwz r4, mpp(r13)
	sthx r3, r4, r7
	lwz r4, mpp(r13)
	sthx r3, r4, r6
	lwz r4, mpp(r13)
	sthx r3, r4, r5
	lwz r4, mpp(r13)
	sthx r3, r4, r0
	bdnz @4
	li r0, 0x19
	mtctr r0
	@5:
	lwz r5, mpp(r13)
	addi r0, r3, 0x1fa
	li r4, 0x0
	addi r10, r3, 0x1fc
	sthx r4, r5, r0
	addi r9, r3, 0x1fe
	addi r8, r3, 0x200
	addi r7, r3, 0x202
	lwz r11, mpp(r13)
	addi r6, r3, 0x204
	addi r5, r3, 0x206
	addi r0, r3, 0x208
	sthx r4, r11, r10
	addi r3, r3, 0x10
	lwz r10, mpp(r13)
	sthx r4, r10, r9
	lwz r9, mpp(r13)
	sthx r4, r9, r8
	lwz r8, mpp(r13)
	sthx r4, r8, r7
	lwz r7, mpp(r13)
	sthx r4, r7, r6
	lwz r6, mpp(r13)
	sthx r4, r6, r5
	lwz r5, mpp(r13)
	sthx r4, r5, r0
	bdnz @5
	li r0, 0x19
	mtctr r0
	@6:
	lwz r5, mpp(r13)
	addi r3, r4, 0x38a
	li r0, 0x0
	addi r10, r4, 0x38c
	sthx r0, r5, r3
	addi r9, r4, 0x38e
	addi r8, r4, 0x390
	addi r7, r4, 0x392
	lwz r11, mpp(r13)
	addi r6, r4, 0x394
	addi r5, r4, 0x396
	addi r3, r4, 0x398
	sthx r0, r11, r10
	addi r4, r4, 0x10
	lwz r10, mpp(r13)
	sthx r0, r10, r9
	lwz r9, mpp(r13)
	sthx r0, r9, r8
	lwz r8, mpp(r13)
	sthx r0, r8, r7
	lwz r7, mpp(r13)
	sthx r0, r7, r6
	lwz r6, mpp(r13)
	sthx r0, r6, r5
	lwz r5, mpp(r13)
	sthx r0, r5, r3
	bdnz @6
	lwz r3, mpp(r13)
	li r9, 0xa
	li r8, 0x5
	li r7, 0x3
	sth r9, 0x72(r3)
	li r6, 0x1
	lfs f0, float_0_8041b64c(r2)
	li r4, 0x2
	lwz r5, mpp(r13)
	mr r3, r0
	mr r10, r0
	sth r9, 0x8e(r5)
	lwz r5, mpp(r13)
	sth r8, 0x76(r5)
	lwz r5, mpp(r13)
	sth r8, 0x90(r5)
	lwz r5, mpp(r13)
	sth r7, 0x92(r5)
	lwz r5, mpp(r13)
	sth r7, 0x94(r5)
	lwz r7, mpp(r13)
	lha r5, 0x72(r7)
	sth r5, 0x70(r7)
	lwz r7, mpp(r13)
	lha r5, 0x76(r7)
	sth r5, 0x74(r7)
	lwz r5, mpp(r13)
	sth r0, 0x7a(r5)
	lwz r5, mpp(r13)
	sth r0, 0x7e(r5)
	lwz r5, mpp(r13)
	sth r0, 0x7c(r5)
	lwz r5, mpp(r13)
	sth r0, 0x80(r5)
	lwz r5, mpp(r13)
	stfs f0, 0x84(r5)
	lwz r5, mpp(r13)
	sth r0, 0x88(r5)
	lwz r5, mpp(r13)
	sth r6, 0x8a(r5)
	lwz r5, mpp(r13)
	stb r0, 0x98(r5)
	lwz r5, mpp(r13)
	stb r0, 0x99(r5)
	mtctr r4
	@7:
	lwz r4, mpp(r13)
	cmpwi r3, 0x0
	add r5, r4, r10
	beq @8
	sth r0, 0x0(r5)
	sth r9, 0x4(r5)
	lha r4, 0x4(r5)
	sth r4, 0x2(r5)
	lha r4, 0x4(r5)
	sth r4, 0x6(r5)
	sth r0, 0xa(r5)
	sth r0, 0xc(r5)
	@8:
	lwz r4, mpp(r13)
	addic. r3, r3, 0x1
	addi r10, r10, 0xe
	add r5, r4, r10
	beq @9
	sth r0, 0x0(r5)
	sth r9, 0x4(r5)
	lha r4, 0x4(r5)
	sth r4, 0x2(r5)
	lha r4, 0x4(r5)
	sth r4, 0x6(r5)
	sth r0, 0xa(r5)
	sth r0, 0xc(r5)
	@9:
	lwz r4, mpp(r13)
	addic. r3, r3, 0x1
	addi r10, r10, 0xe
	add r5, r4, r10
	beq @10
	sth r0, 0x0(r5)
	sth r9, 0x4(r5)
	lha r4, 0x4(r5)
	sth r4, 0x2(r5)
	lha r4, 0x4(r5)
	sth r4, 0x6(r5)
	sth r0, 0xa(r5)
	sth r0, 0xc(r5)
	@10:
	lwz r4, mpp(r13)
	addic. r3, r3, 0x1
	addi r10, r10, 0xe
	add r5, r4, r10
	beq @11
	sth r0, 0x0(r5)
	sth r9, 0x4(r5)
	lha r4, 0x4(r5)
	sth r4, 0x2(r5)
	lha r4, 0x4(r5)
	sth r4, 0x6(r5)
	sth r0, 0xa(r5)
	sth r0, 0xc(r5)
	@11:
	addi r10, r10, 0xe
	addi r3, r3, 0x1
	bdnz @7
	lwz r5, mpp(r13)
	lis r3, str_802CE17C@ha
	addi r4, r3, str_802CE17C@l
	addi r3, r5, 0x5c0
	bl strcpy
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm PouchData* pouchGetPtr(void) {
	nofralloc
	lwz r3, mpp(r13)
	blr
}
// clang-format on
#endif
