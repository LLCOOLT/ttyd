#ifndef NONMATCHING
void swSet();
#endif
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
#ifndef NONMATCHING
#define EXT_LIT(sym, val) (sym)
extern const f32 float_2_8041b648;
extern const f32 float_0_8041b64c;
#endif
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

PouchData* pouchGetPtr(void) {
	return mpp;
}

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
#ifdef NONMATCHING
	mpp->audienceCount = 0.0f;
#endif
#ifndef NONMATCHING
	mpp->audienceCount = EXT_LIT(float_0_8041b64c, 0.0f);
#endif
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
BOOL pouchGetItem(ItemType type) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		opword 0x7C7F1B78
		opword 0x2C1F0079
		opword 0x93C10018
		opword 0x93A10014
		opword 0x40820024
		lwz r4, mpp(r13)
		opword 0xA8640078
		opword 0x2C0303E7
		opword 0x4080000C
		opword 0x38030001
		opword 0xB0040078
		opword 0x38600001
		opword 0x48000448
		opword 0x2C1F007A
		opword 0x4082002C
		lwz r4, yuwp(r13)
		opword 0x3C600002
		opword 0x3803869F
		opword 0x80640008
		opword 0x7C030000
		opword 0x4080000C
		opword 0x38030001
		opword 0x90040008
		opword 0x38600001
		opword 0x48000418
		opword 0x2C1F007B
		opword 0x40820058
		bl marioGetParty
		lwz r5, mpp(r13)
		opword 0xA8850070
		opword 0xA8050072
		opword 0x7C040000
		opword 0x4080000C
		opword 0x38040001
		opword 0xB0050070
		opword 0x2C030000
		opword 0x41820028
		opword 0x1C03000E
		lwz r3, mpp(r13)
		opword 0x7C830214
		opword 0xA8640006
		opword 0xA8040002
		opword 0x7C030000
		opword 0x4080000C
		opword 0x38030001
		opword 0xB0040006
		opword 0x38600001
		opword 0x480003BC
		opword 0x2C1F007C
		opword 0x40820028
		lwz r4, mpp(r13)
		opword 0xA8640074
		opword 0xA8040076
		opword 0x7C030000
		opword 0x4080000C
		opword 0x38030001
		opword 0xB0040074
		opword 0x38600001
		opword 0x48000390
		opword 0x2C1F007D
		opword 0x4082001C
		lwz r5, mpp(r13)
		opword 0x38600001
		opword 0xA885009A
		opword 0x38040001
		opword 0xB005009A
		opword 0x48000370
		opword 0x2C1F0057
		opword 0x4082001C
		lwz r5, mpp(r13)
		opword 0x38600001
		opword 0xA885009C
		opword 0x38040001
		opword 0xB005009C
		opword 0x48000350
		opword 0x381FFFFA
		opword 0x28000001
		opword 0x4081000C
		opword 0x2C1F0008
		opword 0x40820058
		opword 0x2C1F0007
		opword 0x41820030
		opword 0x40800010
		opword 0x2C1F0006
		opword 0x40800014
		opword 0x480000D0
		opword 0x2C1F0009
		opword 0x408000C8
		opword 0x48000024
		lwz r3, mpp(r13)
		opword 0x38000001
		opword 0x98030098
		opword 0x480000B4
		lwz r3, mpp(r13)
		opword 0x38000002
		opword 0x98030098
		opword 0x480000A4
		lwz r3, mpp(r13)
		opword 0x38000003
		opword 0x98030098
		opword 0x48000094
		opword 0x381FFFF7
		opword 0x28000001
		opword 0x4081000C
		opword 0x2C1F000B
		opword 0x40820058
		opword 0x2C1F000A
		opword 0x41820030
		opword 0x40800010
		opword 0x2C1F0009
		opword 0x40800014
		opword 0x48000068
		opword 0x2C1F000C
		opword 0x40800060
		opword 0x48000024
		lwz r3, mpp(r13)
		opword 0x38000001
		opword 0x98030099
		opword 0x4800004C
		lwz r3, mpp(r13)
		opword 0x38000002
		opword 0x98030099
		opword 0x4800003C
		lwz r3, mpp(r13)
		opword 0x38000003
		opword 0x98030099
		opword 0x4800002C
		opword 0x2C1F0059
		opword 0x4082000C
		opword 0x38600001
		opword 0x48000270
		opword 0x2C1F00F0
		opword 0x41800014
		opword 0x2C1F0153
		opword 0x4080000C
		opword 0x387FFF90
		bl swSet
		opword 0x2C1F0079
		opword 0x38800000
		opword 0x7C9D2378
		opword 0x7C9E2378
		opword 0x41800034
		opword 0x2C1F00EC
		opword 0x4080002C
		lwz r4, mpp(r13)
		opword 0x38600001
		opword 0x3BA40192
		bl pouchCheckItem
		opword 0x2C030000
		opword 0x3880000A
		opword 0x41820008
		opword 0x38800014
		opword 0x38000001
		opword 0x48000058
		opword 0x2C1F0001
		opword 0x41800024
		opword 0x2C1F0079
		opword 0x4080001C
		lwz r3, mpp(r13)
		opword 0x3BC00000
		opword 0x38800079
		opword 0x38000001
		opword 0x3BA300A0
		opword 0x48000030
		opword 0x2C1F00F0
		opword 0x41800024
		opword 0x2C1F0153
		opword 0x4080001C
		lwz r3, mpp(r13)
		opword 0x388000C8
		opword 0x38000001
		opword 0x3BA301FA
		opword 0x3BC3038A
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x4082000C
		opword 0x38600000
		opword 0x480001B0
		opword 0x3484FFFF
		opword 0x5483083C
		opword 0x38040001
		opword 0x7C7D1A14
		opword 0x7C0903A6
		opword 0x41800194
		opword 0xA8030000
		opword 0x2C000000
		opword 0x4082017C
		opword 0x281E0000
		opword 0x5480083C
		opword 0x7CBD0214
		opword 0x7C7E0214
		opword 0x418200D0
		opword 0x2C040000
		opword 0x40810144
		opword 0x5480E8FF
		opword 0x7C0903A6
		opword 0x41820098
		opword 0xA805FFFE
		opword 0xB0050000
		opword 0xA803FFFE
		opword 0xB0030000
		opword 0xA805FFFC
		opword 0xB005FFFE
		opword 0xA803FFFC
		opword 0xB003FFFE
		opword 0xA805FFFA
		opword 0xB005FFFC
		opword 0xA803FFFA
		opword 0xB003FFFC
		opword 0xA805FFF8
		opword 0xB005FFFA
		opword 0xA803FFF8
		opword 0xB003FFFA
		opword 0xA805FFF6
		opword 0xB005FFF8
		opword 0xA803FFF6
		opword 0xB003FFF8
		opword 0xA805FFF4
		opword 0xB005FFF6
		opword 0xA803FFF4
		opword 0xB003FFF6
		opword 0xA805FFF2
		opword 0xB005FFF4
		opword 0xA803FFF2
		opword 0xB003FFF4
		opword 0xA805FFF0
		opword 0xB005FFF2
		opword 0x38A5FFF0
		opword 0xA803FFF0
		opword 0xB003FFF2
		opword 0x3863FFF0
		opword 0x4200FF78
		opword 0x70840007
		opword 0x418200A4
		opword 0x7C8903A6
		opword 0xA805FFFE
		opword 0xB0050000
		opword 0x38A5FFFE
		opword 0xA803FFFE
		opword 0xB0030000
		opword 0x3863FFFE
		opword 0x4200FFE8
		opword 0x48000080
		opword 0x2C040000
		opword 0x7C832378
		opword 0x40810074
		opword 0x5480E8FF
		opword 0x7C0903A6
		opword 0x41820054
		opword 0xA805FFFE
		opword 0xB0050000
		opword 0xA805FFFC
		opword 0xB005FFFE
		opword 0xA805FFFA
		opword 0xB005FFFC
		opword 0xA805FFF8
		opword 0xB005FFFA
		opword 0xA805FFF6
		opword 0xB005FFF8
		opword 0xA805FFF4
		opword 0xB005FFF6
		opword 0xA805FFF2
		opword 0xB005FFF4
		opword 0xA805FFF0
		opword 0xB005FFF2
		opword 0x38A5FFF0
		opword 0x4200FFBC
		opword 0x70630007
		opword 0x41820018
		opword 0x7C6903A6
		opword 0xA805FFFE
		opword 0xB0050000
		opword 0x38A5FFFE
		opword 0x4200FFF4
		opword 0x281E0000
		opword 0xB3FD0000
		opword 0x4182000C
		opword 0x38000000
		opword 0xB01E0000
		opword 0x38600001
		opword 0x48000014
		opword 0x3863FFFE
		opword 0x3884FFFF
		opword 0x4200FE74
		opword 0x38600000
		opword 0x80010024
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x83A10014
		opword 0x7C0803A6
		opword 0x38210020
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
BOOL pouchRemoveItem(ItemType type) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x38800000
		opword 0x90010024
		opword 0x93E1001C
		opword 0x3BE00000
		opword 0x93C10018
		opword 0x3BC00000
		opword 0x93A10014
		opword 0x7C7D1B78
		opword 0x2C1D0079
		opword 0x4180003C
		opword 0x2C1D00EC
		opword 0x40800034
		lwz r4, mpp(r13)
		opword 0x3BC00000
		opword 0x38600001
		opword 0x3BE40192
		bl pouchCheckItem
		opword 0x2C030000
		opword 0x3800000A
		opword 0x41820008
		opword 0x38000014
		opword 0x7C040378
		opword 0x38000001
		opword 0x48000058
		opword 0x2C1D0001
		opword 0x41800024
		opword 0x2C1D0079
		opword 0x4080001C
		lwz r3, mpp(r13)
		opword 0x3BC00000
		opword 0x38800079
		opword 0x38000001
		opword 0x3BE300A0
		opword 0x48000030
		opword 0x2C1D00F0
		opword 0x41800024
		opword 0x2C1D0153
		opword 0x4080001C
		lwz r3, mpp(r13)
		opword 0x388000C8
		opword 0x38000001
		opword 0x3BE301FA
		opword 0x3BC3038A
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x4082000C
		opword 0x38600000
		opword 0x480001B8
		opword 0x7FE3FB78
		opword 0x38E00000
		opword 0x7C8903A6
		opword 0x2C040000
		opword 0x40810190
		opword 0xA8030000
		opword 0x7C1D0000
		opword 0x40820178
		opword 0x281E0000
		opword 0x54E3083C
		opword 0x38000000
		opword 0x7C1F1B2E
		opword 0x41820178
		opword 0x7C1E1B2E
		opword 0x48000170
		opword 0x281E0000
		opword 0x3804FFFF
		opword 0x38800000
		opword 0x418200AC
		opword 0x7C070000
		opword 0x7C670050
		opword 0x40800138
		opword 0x5460F0BF
		opword 0x7C0903A6
		opword 0x41820070
		opword 0xA8050002
		opword 0xB0050000
		opword 0xB0850002
		opword 0xA8060002
		opword 0xB0060000
		opword 0xB0860002
		opword 0xA8050004
		opword 0xB0050002
		opword 0xB0850004
		opword 0xA8060004
		opword 0xB0060002
		opword 0xB0860004
		opword 0xA8050006
		opword 0xB0050004
		opword 0xB0850006
		opword 0xA8060006
		opword 0xB0060004
		opword 0xB0860006
		opword 0xA8050008
		opword 0xB0050006
		opword 0xB4850008
		opword 0xA8060008
		opword 0xB0060006
		opword 0xB4860008
		opword 0x4200FFA0
		opword 0x70630003
		opword 0x418200C0
		opword 0x7C6903A6
		opword 0xA8050002
		opword 0xB0050000
		opword 0xB4850002
		opword 0xA8060002
		opword 0xB0060000
		opword 0xB4860002
		opword 0x4200FFE8
		opword 0x4800009C
		opword 0x7C070000
		opword 0x7C670050
		opword 0x40800090
		opword 0x5460E8FF
		opword 0x7C0903A6
		opword 0x41820070
		opword 0xA8050002
		opword 0xB0050000
		opword 0xB0850002
		opword 0xA8050004
		opword 0xB0050002
		opword 0xB0850004
		opword 0xA8050006
		opword 0xB0050004
		opword 0xB0850006
		opword 0xA8050008
		opword 0xB0050006
		opword 0xB0850008
		opword 0xA805000A
		opword 0xB0050008
		opword 0xB085000A
		opword 0xA805000C
		opword 0xB005000A
		opword 0xB085000C
		opword 0xA805000E
		opword 0xB005000C
		opword 0xB085000E
		opword 0xA8050010
		opword 0xB005000E
		opword 0xB4850010
		opword 0x4200FFA0
		opword 0x70630007
		opword 0x41820018
		opword 0x7C6903A6
		opword 0xA8050002
		opword 0xB0050000
		opword 0xB4850002
		opword 0x4200FFF4
		opword 0x38600001
		opword 0x48000024
		opword 0x38630002
		opword 0x38E70001
		opword 0x4200FE78
		opword 0x38600000
		opword 0x48000010
		opword 0x7CBF1A14
		opword 0x7CDE1A14
		opword 0x4BFFFE8C
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
      return 1;
    }
  }

  return 0;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
BOOL pouchRemoveItemIndex(ItemType type, s32 index) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		opword 0x3BE00000
		opword 0x93C10018
		opword 0x3BC00000
		opword 0x93A10014
		opword 0x7C9D2378
		opword 0x38800000
		opword 0x93810010
		opword 0x7C7C1B78
		opword 0x2C1C0079
		opword 0x4180003C
		opword 0x2C1C00EC
		opword 0x40800034
		lwz r4, mpp(r13)
		opword 0x3BC00000
		opword 0x38600001
		opword 0x3BE40192
		bl pouchCheckItem
		opword 0x2C030000
		opword 0x3800000A
		opword 0x41820008
		opword 0x38000014
		opword 0x7C040378
		opword 0x38000001
		opword 0x48000058
		opword 0x2C1C0001
		opword 0x41800024
		opword 0x2C1C0079
		opword 0x4080001C
		lwz r3, mpp(r13)
		opword 0x3BC00000
		opword 0x38800079
		opword 0x38000001
		opword 0x3BE300A0
		opword 0x48000030
		opword 0x2C1C00F0
		opword 0x41800024
		opword 0x2C1C0153
		opword 0x4080001C
		lwz r3, mpp(r13)
		opword 0x388000C8
		opword 0x38000001
		opword 0x3BE301FA
		opword 0x3BC3038A
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x4082000C
		opword 0x38600000
		opword 0x480001D4
		opword 0x57A0083C
		opword 0x7C7F0214
		opword 0xA8030000
		opword 0x7C1C0000
		opword 0x4182000C
		opword 0x38600000
		opword 0x480001B8
		opword 0x7C1D2050
		opword 0x7FA7EB78
		opword 0x7C0903A6
		opword 0x7C1D2000
		opword 0x40800190
		opword 0xA8030000
		opword 0x7C1C0000
		opword 0x40820178
		opword 0x281E0000
		opword 0x54E3083C
		opword 0x38000000
		opword 0x7C1F1B2E
		opword 0x41820178
		opword 0x7C1E1B2E
		opword 0x48000170
		opword 0x281E0000
		opword 0x3804FFFF
		opword 0x38800000
		opword 0x418200AC
		opword 0x7C070000
		opword 0x7C670050
		opword 0x40800138
		opword 0x5460F0BF
		opword 0x7C0903A6
		opword 0x41820070
		opword 0xA8050002
		opword 0xB0050000
		opword 0xB0850002
		opword 0xA8060002
		opword 0xB0060000
		opword 0xB0860002
		opword 0xA8050004
		opword 0xB0050002
		opword 0xB0850004
		opword 0xA8060004
		opword 0xB0060002
		opword 0xB0860004
		opword 0xA8050006
		opword 0xB0050004
		opword 0xB0850006
		opword 0xA8060006
		opword 0xB0060004
		opword 0xB0860006
		opword 0xA8050008
		opword 0xB0050006
		opword 0xB4850008
		opword 0xA8060008
		opword 0xB0060006
		opword 0xB4860008
		opword 0x4200FFA0
		opword 0x70630003
		opword 0x418200C0
		opword 0x7C6903A6
		opword 0xA8050002
		opword 0xB0050000
		opword 0xB4850002
		opword 0xA8060002
		opword 0xB0060000
		opword 0xB4860002
		opword 0x4200FFE8
		opword 0x4800009C
		opword 0x7C070000
		opword 0x7C670050
		opword 0x40800090
		opword 0x5460E8FF
		opword 0x7C0903A6
		opword 0x41820070
		opword 0xA8050002
		opword 0xB0050000
		opword 0xB0850002
		opword 0xA8050004
		opword 0xB0050002
		opword 0xB0850004
		opword 0xA8050006
		opword 0xB0050004
		opword 0xB0850006
		opword 0xA8050008
		opword 0xB0050006
		opword 0xB0850008
		opword 0xA805000A
		opword 0xB0050008
		opword 0xB085000A
		opword 0xA805000C
		opword 0xB005000A
		opword 0xB085000C
		opword 0xA805000E
		opword 0xB005000C
		opword 0xB085000E
		opword 0xA8050010
		opword 0xB005000E
		opword 0xB4850010
		opword 0x4200FFA0
		opword 0x70630007
		opword 0x41820018
		opword 0x7C6903A6
		opword 0xA8050002
		opword 0xB0050000
		opword 0xB4850002
		opword 0x4200FFF4
		opword 0x38600001
		opword 0x48000024
		opword 0x38630002
		opword 0x38E70001
		opword 0x4200FE78
		opword 0x38600000
		opword 0x48000010
		opword 0x7CBF1A14
		opword 0x7CDE1A14
		opword 0x4BFFFE8C
		opword 0x80010024
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x83A10014
		opword 0x83810010
		opword 0x7C0803A6
		opword 0x38210020
	}
#endif
}
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
#ifndef NONMATCHING
#pragma pop
#endif

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

s32 comp_aiueo(const void* a, const void* b) {
	char bufA[0x80];
	char bufB[0x80];
	s16 ia = *(s16*)a;
	s16 ib = *(s16*)b;

	pouchAiueoConv(msgSearch(itemDataTable[ia].name), bufA);
	pouchAiueoConv(msgSearch(itemDataTable[ib].name), bufB);
	return strcmp(bufA, bufB);
}

s32 comp_kind(s16* a, s16* b) {
	s16 x = itemDataTable[*a].type_sort_order;
	s16 y = itemDataTable[*b].type_sort_order;
	if (x > y) return 1;
	return -(x < y);
}

s32 comp_aiueo_r(const void* a, const void* b) {
	char bufA[0x80];
	char bufB[0x80];
	s16 ia = *(s16*)a;
	s16 ib = *(s16*)b;

	pouchAiueoConv(msgSearch(itemDataTable[ia].name), bufA);
	pouchAiueoConv(msgSearch(itemDataTable[ib].name), bufB);
	return strcmp(bufB, bufA);
}

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

s16 pouchGetSuperCoin(void) {
	return mpp->mShineSpriteCount;
}

s16 pouchSetSuperCoin(s16 count) {
	mpp->mShineSpriteCount = count;
	return mpp->mShineSpriteCount;
}

s16 pouchGetStarPiece(void) {
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

s16 pouchGetHP(void) {
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

s16 pouchGetPartyHP(PartyId partnerId) {
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

s16 pouchGetFP(void) {
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

s16 pouchGetAP(void) {
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
	return *(s16*)((u8*)mpp + partyId * 14 + 0xA);
}

//TODO: this function
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

s32 pouchArriveBadge(s32 id) {
	return badgeShop_add(bdsw->special_table, (s16)id, 1);
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
	u16* sp = (u16*)&mpp->mStarPowersObtained;
	if (!*sp) {
#ifdef NONMATCHING
		mpp->audienceCount = 2.0f;
#endif
#ifndef NONMATCHING
		mpp->audienceCount = EXT_LIT(float_2_8041b648, 2.0f);
#endif
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
		return (char*)msgSearch((char*)str_802CE170);
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
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const char str_802CE170[12] = "name_party3";
__declspec(section ".sdata2") const f32 float_2_8041b648 = 2.0f;
__declspec(section ".sdata2") const f32 float_0_8041b64c = 0.0f;

#endif