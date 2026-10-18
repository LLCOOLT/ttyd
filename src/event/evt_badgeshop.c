/* "evt_badgeshop" - Badge Shop Script Functions
 * Status: Complete, not 1:1 (see comments throughout files, mostly
 * regalloc, along with bargainGeneration cleanup
 *
 * Function: part of the backend for various shops
 */
#include "evt/evt_badgeshop.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_pouch.h"
#include "system.h"
#include <string.h>

//.data
s32 badge_starmaniac_table[] = { //Dazzle
	ITEM_ATTACK_FX_Y, ITEM_CHILL_OUT, ITEM_PRETTY_LUCKY, ITEM_HAPPY_HEART,
	ITEM_HAPPY_FLOWER, ITEM_HAPPY_HEART_P, ITEM_ITEM_HOG, ITEM_HEART_FINDER,
	ITEM_FLOWER_FINDER, ITEM_PEEKABOO, ITEM_QUICK_CHANGE, ITEM_FLOWER_SAVER,
	ITEM_FLOWER_SAVER_P, ITEM_POWER_PLUS, ITEM_POWER_PLUS_P, ITEM_NULL
};

s32 badge_bottakuru_table[] = { //Charlieton Rogueport
	ITEM_SHOOTING_STAR, ITEM_EARTH_QUAKE, ITEM_BOOS_SHEET, ITEM_REPEL_CAPE,
	ITEM_STOPWATCH, ITEM_ULTRA_SHROOM, ITEM_JAMMIN_JELLY, ITEM_DRIED_SHROOM,
	ITEM_DOUBLE_PAIN, ITEM_JUMPMAN, ITEM_HAMMERMAN, ITEM_ATTACK_FX_G,
	ITEM_SLOW_GO, ITEM_MEGA_RUSH, ITEM_TIMING_TUTOR, ITEM_W_EMBLEM, ITEM_NULL
};
#pragma force_active on
__declspec(section ".data") u32 gap_05_803AA21C_data[1] = {0};
#pragma force_active reset

//.sdata
s32 badge_special_table[] = { //Lovely Howz of Badges
	ITEM_PIERCING_BLOW, ITEM_POWER_JUMP, ITEM_SIMPLIFIER, ITEM_UNSIMPLIFIER,
	ITEM_FP_DRAIN, ITEM_LAST_STAND, ITEM_LAST_STAND_P, ITEM_HAPPY_FLOWER,
	ITEM_SUPER_APPEAL, ITEM_NULL
};

s32 badge_special_table_stage_1_clear[] = { //Hooktail Castle
	ITEM_CLOSE_CALL, ITEM_CLOSE_CALL_P, ITEM_SLEEPY_STOMP, ITEM_NULL
};

s32 badge_special_table_stage_2_clear[] = { //Boggly Tree
	ITEM_FIRST_ATTACK, ITEM_PRETTY_LUCKY_P, ITEM_POWER_RUSH, ITEM_NULL
};

s32 badge_special_table_stage_3_clear[] = { //Glitz Pit
	ITEM_SHRINK_STOMP, ITEM_ICE_SMASH, ITEM_POWER_RUSH_P, ITEM_NULL
};

s32 badge_special_table_stage_4_clear[] = { //Creepy Steeple
	ITEM_SOFT_STOMP, ITEM_HEAD_RATTLE, ITEM_DAMAGE_DODGE, ITEM_NULL
};

s32 badge_special_table_stage_5_clear[] = { //Keelhaul Key
	ITEM_SUPER_APPEAL_P, ITEM_DAMAGE_DODGE_P, ITEM_FIRE_DRIVE, ITEM_NULL
};

s32 badge_special_table_stage_6_clear[] = { //Poshley Heights
	ITEM_SIMPLIFIER, ITEM_UNSIMPLIFIER, ITEM_ATTACK_FX_P, ITEM_NULL
};

s32 badge_bottakuru100_table[] = { //Charlieton Pit of 100 Trials
	ITEM_MUSHROOM, ITEM_SUPER_SHROOM, ITEM_HONEY_SYRUP, ITEM_MAPLE_SYRUP,
	ITEM_FIRE_FLOWER, ITEM_THUNDER_RAGE, ITEM_NULL
};

s32 badge_bteresa_table[] = { //Pianta Parlor
	ITEM_SUPER_SHROOM, ITEM_CAKE_MIX, ITEM_SUPER_APPEAL, ITEM_REFUND, ITEM_NULL
};

s32 badge_bteresa_table_card_special[] = { //Pianta Parlor Special Card
	ITEM_MAPLE_SYRUP, ITEM_POWER_JUMP, ITEM_HP_PLUS, ITEM_FP_PLUS, ITEM_NULL
};

s32 badge_bteresa_table_card_silver[] = { //Pianta Parlor Silver Card
	ITEM_GOLD_BAR_X3, ITEM_POWER_SMASH, ITEM_HP_PLUS_P, ITEM_NULL
};

s32 badge_bteresa_table_card_gold[] = { //Pianta Parlor Gold Card
	ITEM_HAMMER_THROW, ITEM_POWER_RUSH, ITEM_TORNADO_JUMP, ITEM_MULTIBOUNCE,
	ITEM_POWER_RUSH_P, ITEM_NULL
};

s32 badge_bteresa_table_card_platinum[] = { //Pianta Parlor Platinum Card
	ITEM_QUAKE_HAMMER, ITEM_MONEY_MONEY, ITEM_ULTRA_SHROOM, ITEM_JAMMIN_JELLY, ITEM_NULL
};

//.bss
#pragma force_active on
__declspec(section ".data") u32 gap_06_803E1894_bss[1];
#pragma force_active reset
BadgeShopWork badgeshopwork;


//.sbss
#pragma force_active on
__declspec(section ".sdata") u32 gap_08_80418B1C_sbss[1];
#pragma force_active reset
BadgeShopWork* bdsw;

//local prototypes
s32 bottakuruComp(const void** sortA, const void** sortB);

s32 getBadgeBottakuru100TableMaxCount(void) {
	return (sizeof(badge_bottakuru100_table) / sizeof(s32)) - 1;
}

s32 getBadgeStarmaniacTableMaxCount(void) {
	return (sizeof(badge_starmaniac_table) / sizeof(s32)) - 1;
}

s32 getBadgeBteresaTableMaxCount(void) {
	return ((sizeof(badge_bteresa_table) / sizeof(s32)) - 1) +
		((sizeof(badge_bteresa_table_card_special) / sizeof(s32)) - 1) +
		((sizeof(badge_bteresa_table_card_silver) / sizeof(s32)) - 1) +
		((sizeof(badge_bteresa_table_card_gold) / sizeof(s32)) - 1) +
		((sizeof(badge_bteresa_table_card_platinum) / sizeof(s32)) - 1);
}

void badgeShop_init(void) {
	s32* ptr;

	bdsw = &badgeshopwork;
	memset(bdsw->special_table, 0, sizeof(bdsw->special_table));
	memset(bdsw->bargain_table, 0, sizeof(bdsw->bargain_table));
	memset(bdsw->starmaniac_table, 0, sizeof(bdsw->starmaniac_table));
	memset(bdsw->bottakuru_table, 0, sizeof(bdsw->bottakuru_table));
	memset(bdsw->bteresa_table, 0, sizeof(bdsw->bteresa_table));
	bdsw->restockFlags = 1;

	for (ptr = badge_special_table; *ptr; ++ptr) {
		badgeShop_add(bdsw->special_table, (s16)*ptr, 1);
	}
	for (ptr = badge_starmaniac_table; *ptr; ++ptr) {
		badgeShop_add(bdsw->starmaniac_table, (s16)*ptr, 1);
	}
	for (ptr = badge_bottakuru_table; *ptr; ++ptr) {
		badgeShop_add(bdsw->bottakuru_table, (s16)*ptr, 1);
	}

	badgeShop_bottakuruGeneration();

	for (ptr = badge_bteresa_table; *ptr; ++ptr) {
		badgeShop_add(bdsw->bteresa_table, (s16)*ptr, 1);
	}
}

s32 bottakuruComp(const void** sortA, const void** sortB) {
	s32 a, b;

	a = (s32)sortA[1];
	b = (s32)sortB[1];
	if (a < b) {
		return -1;
	}
	return a > b;
}

#ifdef NONMATCHING
void badgeShop_bottakuruGeneration(void) {
	s32 table[0x11][2];
	s32* p;
	s32 i;
	s32 k;
	s32 count;
	s32 j;
	s32 m;

	for (m = 0; m < sizeof(table) / sizeof(table[0]); m++) {
		table[m][1] = 200;
		table[m][0] = 0;
	}

	i = 0;
	p = (s32*)table;
	k = 0;
	for (; i < BADGE_MAX - 1; i++) {
		count = (s16)badgeShop_get(bdsw->bottakuru_table, (s16)(i + 1));
		for (j = 0; j < count; j++) {
			table[k][1] = irand(100);
			table[k++][0] = i + 1;
			if (k >= 0x10u) break;
		}
		if (k >= 0x10u) {
			break;
		}
	}

	qqsort(table, 0x11, 8, bottakuruComp);

	i = 0;
	do {
		for (m = 0; m < sizeof(badge_bottakuru_table) / sizeof(badge_bottakuru_table[0]); m++) {
			if (p[0] == badge_bottakuru_table[m]) {
				evtSetValue(NULL, i + GSW(118), m);
			}
		}
		p += 2;
	} while (++i < 4);
}
#endif

#ifdef NONMATCHING
void badgeShop_bteresaGeneration(void) {
	s32* ptr;
	s32 has;

	has = pouchCheckItem(ITEM_SPECIAL_CARD);
	if (has) {
		if (!evtGetValue(NULL, GSWF(246))) {
			evtSetValue(NULL, GSWF(246), 1);
			for (ptr = badge_bteresa_table_card_special; *ptr; ptr++) {
				badgeShop_add(bdsw->bteresa_table, (s16)*ptr, 1);
			}
		}
	}

	has = pouchCheckItem(ITEM_SILVER_CARD);
	if (has) {
		if (!evtGetValue(NULL, GSWF(247))) {
			evtSetValue(NULL, GSWF(247), 1);
			for (ptr = badge_bteresa_table_card_silver; *ptr; ptr++) {
				badgeShop_add(bdsw->bteresa_table, (s16)*ptr, 1);
			}
		}
	}

	has = pouchCheckItem(ITEM_GOLD_CARD);
	if (has) {
		if (!evtGetValue(NULL, GSWF(248))) {
			evtSetValue(NULL, GSWF(248), 1);
			for (ptr = badge_bteresa_table_card_gold; *ptr; ptr++) {
				badgeShop_add(bdsw->bteresa_table, (s16)*ptr, 1);
			}
		}
	}

	has = pouchCheckItem(ITEM_PLATINUM_CARD);
	if (has) {
		if (!evtGetValue(NULL, GSWF(249))) {
			evtSetValue(NULL, GSWF(249), 1);
			for (ptr = badge_bteresa_table_card_platinum; *ptr; ptr++) {
				badgeShop_add(bdsw->bteresa_table, (s16)*ptr, 1);
			}
		}
	}
}
#endif

#ifdef NONMATCHING
void badgeShop_bargainGeneration(void) { //finished, needs cleanup and probably fixes
	s16 stopcount;
	u8 table[0x19];
	s16 has;
	s32 badge;
	s16 value;
	int i;
	s32 item;
	s32 v28;
	s32 count2;
	s32 count3;
	s16 count4;
	s32* ptr;
	s32 count;
	s32 v7;

	if (evtGetValue(NULL, GSW(0)) >= 55 && !evtGetValue(0, GSWF(238))) {
		evtSetValue(NULL, GSWF(238), 1);
		for (ptr = badge_special_table_stage_1_clear; *ptr; ptr++) {
			badgeShop_add(bdsw->special_table, (s16)*ptr, 1);
		}
	}

	if (evtGetValue(NULL, GSW(0)) >= 112 && !evtGetValue(0, GSWF(239))) {
		evtSetValue(NULL, GSWF(239), 1);
		for (ptr = badge_special_table_stage_2_clear; *ptr; ptr++) {
			badgeShop_add(bdsw->special_table, (s16)*ptr, 1);
		}
	}

	if (evtGetValue(NULL, GSW(0)) >= 164 && !evtGetValue(0, GSWF(240))) {
		evtSetValue(NULL, GSWF(240), 1);
		for (ptr = badge_special_table_stage_3_clear; *ptr; ptr++) {
			badgeShop_add(bdsw->special_table, (s16)*ptr, 1);
		}
	}

	if (evtGetValue(NULL, GSW(0)) >= 212 && !evtGetValue(0, GSWF(241))) {
		evtSetValue(NULL, GSWF(241), 1);
		for (ptr = badge_special_table_stage_4_clear; *ptr; ptr++) {
			badgeShop_add(bdsw->special_table, (s16)*ptr, 1);
		}
	}

	if (evtGetValue(NULL, GSW(0)) >= 253 && !evtGetValue(0, GSWF(242))) {
		evtSetValue(NULL, GSWF(242), 1);
		for (ptr = badge_special_table_stage_5_clear; *ptr; ptr++) {
			badgeShop_add(bdsw->special_table, (s16)*ptr, 1);
		}
	}

	if (evtGetValue(NULL, GSW(0)) >= 338 && !evtGetValue(0, GSWF(243))) {
		evtSetValue(NULL, GSWF(243), 1);
		for (ptr = badge_special_table_stage_6_clear; *ptr; ptr++) {
			badgeShop_add(bdsw->special_table, (s16)*ptr, 1);
		}
	}

	if (evtGetValue(NULL, GSW(0)) >= 373 && !evtGetValue(0, GSWF(244))) {
		evtSetValue(NULL, GSWF(244), 1);
	}

	if (evtGetValue(NULL, GSW(0)) >= 401 && !evtGetValue(0, GSWF(245))) {
		evtSetValue(NULL, GSWF(245), 1);
	}

	memset(table, 0, sizeof(table));
	count2 = count = v7 = i = 0;
	bdsw->bargainBadges[0] = count;
	bdsw->bargainBadges[1] = count;
	bdsw->bargainBadges[2] = count;
	bdsw->bargainBadges[3] = count;
	bdsw->bargainBadges[4] = count;
	bdsw->bargainNum = count;
	bdsw->field_0x110 = count;

	for (; i < 99; i++) {
		value = 0;
		has = badgeShop_get(bdsw->special_table, (s16)(i + BADGE_MIN)); //inline
		if (has) {
			count++;
			value |= 1;
		}
		if (value) {
			badgeShop_set(table, (s16)(i + BADGE_MIN), value);
			count2++;
		}
	}
	if (count2 > 5) {
		count3 = 5;
	} else {
		count3 = count2;
	}
	irand(0x100); //unused
	while (bdsw->bargainNum + bdsw->field_0x110 < count3) {
		v28 = bdsw->bargainNum;
		if (v28 < 3 || !v7) {
			stopcount = irand(count);
			count4 = 0;
			for (i = 0; i < 99; i++) {
				badge = badgeShop_get(table, (s16)(i + BADGE_MIN)); //inline
				if (badge & 1) {
					if (count4 == stopcount) {
						break;
					}
					count4++;
				}
			}
			if (i < 99) {
				bdsw->bargainBadges[bdsw->bargainNum] = i + BADGE_MIN;
				bdsw->bargainNum++;
				badgeShop_set(table, (s16)(i + BADGE_MIN), 0);
				if ((s16)badge & 1) {
					count--;
				}
				if ((s16)badge & 2) {
					v7--;
				}
			}
		}
	}
	for (i = 0; i < sizeof(bdsw->special_table); i++) {
		bdsw->bargain_table[i] = bdsw->special_table[i];
	}
	for (i = 0; i < 5; i++) {
		item = bdsw->bargainBadges[i];
		if (item) {
			badgeShop_add(bdsw->bargain_table, (s16)item, -1);
		}
	}
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
s16 badgeShop_set(u8* table, s16 id, s16 val) { //TODO: regalloc, otherwise 1:1
	s32 bound;
	s16 index;
	u8 mask;
	s32 shift;
	s32 pos;

	if (table == bdsw->bottakuru_table || table == bdsw->bteresa_table) {
		bound = KEY_ITEM_MIN;
	}
	else {
		bound = BADGE_MIN;
	}
	if (id < bound || id >= BADGE_MAX) return 0;
	index = (s16)(id - bound);
	switch (index & 3) {
		case 0:
			mask = (u8)~(3 << 0);
			shift = 0;
			break;
		case 1:
			mask = (u8)~(3 << 2);
			shift = 2;
			break;
		case 2:
			mask = (u8)~(3 << 4);
			shift = 4;
			break;
		case 3:
			mask = (u8)~(3 << 6);
			shift = 6;
			break;
	}
	pos = index / 4;
	if (val < 0) {
		val = 0;
	}
	else if (val > 3) {
		val = 3;
	}
	table[pos] = (u8)((u8)(mask & table[pos]) + (u8)(val << shift));
	return val;
}
#endif

#pragma dont_inline reset
#ifdef NONMATCHING
s32 badgeShop_get(u8* table, s16 id) { //1:1
	s32 bound;
	s16 index;
	u8 mask;
	s32 shift;

	if (table == bdsw->bottakuru_table || table == bdsw->bteresa_table) {
		bound = KEY_ITEM_MIN;
	}
	else {
		bound = BADGE_MIN;
	}
	if (id < bound || id >= BADGE_MAX) return 0;
	index = (s16)(id - bound);
	switch (index & 3) {
		case 0:
			mask = 3 << 0;
			shift = 0;
			break;
		case 1:
			mask = 3 << 2;
			shift = 2;
			break;
		case 2:
			mask = 3 << 4;
			shift = 4;
			break;
		case 3:
			mask = 3 << 6;
			shift = 6;
			break;
	}
	return (s16)((mask & table[index / 4]) >> shift);
}
#endif

#ifdef NONMATCHING
s32 badgeShop_add(u8* table, s16 id, s32 value) { // 1:1, can blow up in your face
    s32 temp;
	s32 mask;
	s32 shift;
    s32 bound;
    int curr;
    int data;

    if (table == bdsw->bottakuru_table || table == bdsw->bteresa_table) {
        bound = KEY_ITEM_MIN;
    } else {
        bound = BADGE_MIN;
    }
    temp = (s16)id;
    if (temp < bound || temp >= BADGE_MAX) return 0;

    id = (s16)(temp - bound);
    switch (id & 3) {
        case 0:
            mask = 3 << 0;
            shift = 0;
            break;
        case 1:
            mask = 3 << 2;
            shift = 2;
            break;
        case 2:
            mask = 3 << 4;
            shift = 4;
            break;
        case 3:
            mask = 3 << 6;
            shift = 6;
            break;
    }
    data = value;
    mask &= 0xFF;
    curr = (mask & table[id / 4]) >> shift;
    data = (s16)((s16)curr + data);
    if (data < 0) {
        data = 0;
    }
    else if (data > 3) {
        data = 3;
    }
    table[id / 4] = (u8)(table[id / 4] & ~mask) + (u8)((s16)data << shift);
    return data;
}
#endif

#ifdef NONMATCHING
USER_FUNC(badgeShop_getBargainTable) {
	evtSetValue(event, *event->args, (s32)&bdsw->bargainBadges);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_badgeShop_throw_inc) {
	s32 value;

	value = evtGetValue(event, *event->args);
	badgeShop_add(bdsw->bargain_table, (s16)value, 1);
	badgeShop_add(bdsw->special_table, (s16)value, 1);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_badgeShop_throw_dec) {
	s32 value;

	value = evtGetValue(event, *event->args);
	badgeShop_add(bdsw->bargain_table, (s16)value, -1);
	badgeShop_add(bdsw->special_table, (s16)value, -1);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_badgeShop_special_dec) {
	s32 value;

	value = evtGetValue(event, *event->args);
	badgeShop_add(bdsw->special_table, (s16)value, -1);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_badgeShop_starmaniac_dec) {
	s32 value;

	value = (s16)evtGetValue(event, *event->args);
	badgeShop_add(bdsw->starmaniac_table, (s16)value, -1);
	return EVT_RETURN_DONE;
}
#endif

#pragma opt_common_subs off
#ifdef NONMATCHING
USER_FUNC(evt_badgeShop_bottakuru_dec) {
	s32 value;
	int i;

	value = evtGetValue(event, *event->args);
	badgeShop_add(bdsw->bottakuru_table, (s16)value, -1);
	for (i = 0; i < 4; i++) {
		if (value == badge_bottakuru_table[evtGetValue(event, i + GSW(118))]) {
			evtSetValue(event, GSW(118 + i), (sizeof(badge_bottakuru_table) / sizeof(s32)) - 1); //last entry aka kNullItem
		}
	}
	return EVT_RETURN_DONE;
}
#endif

#pragma opt_common_subs reset
#ifdef NONMATCHING
USER_FUNC(evt_badgeShop_throw_get_kind_cnt) {
	s32* args = event->args;
	s16 badge;
	s32 count;
	int i;

	for (count = 0, i = 0; i < 99; i++) {
		badge = badgeShop_get(bdsw->bargain_table, (s16)(i + BADGE_MIN)); //inline
		if (badge > 0) {
			count++;
		}
	}
	evtSetValue(event, *args, count);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_badgeShop_starmaniac_get_kind_cnt) {
	s32* args = event->args;
	s16 badge;
	s32 count;
	int i;

	for (count = 0, i = 0; i < 99; i++) {
		badge = badgeShop_get(bdsw->starmaniac_table, (s16)(i + BADGE_MIN)); //inline
		if (badge > 0) {
			count++;
		}
	}
	evtSetValue(event, *args, count);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_badgeShop_bottakuru_get_kind_cnt) {
	s32* args = event->args;
	s32 count;
	int i;

	for (count = 0, i = 0; i < 4; i++) {
		if (badge_bottakuru_table[evtGetValue(event, i + GSW(118))]) {
			count++;
		}
	}
	evtSetValue(event, *args, count);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(U_evt_badgeShop_get_special_zaiko) {
	s32* args = event->args;
	s16 badge;
	s32 count;
	int i;

	for (count = 0, i = 0; i < BADGE_MAX - 1; i++) {
		badge = badgeShop_get(bdsw->bottakuru_table, (s16)(i + KEY_ITEM_MIN));
		if (!(badge <= 0)) {
			count++;
		}
	}
	evtSetValue(event, *args, count);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_badgeShop_bteresa_get_kind_cnt) {
	s32* args = event->args;
	s16 badge;
	s32 count;
	int i;

	for (count = 0, i = 0; i < BADGE_MAX - 1; i++) {
		badge = badgeShop_get(bdsw->bteresa_table, (s16)(i + KEY_ITEM_MIN));
		if (badge > 0) { //TODO: wonky cntlzw
			count++;
		}
	}
	evtSetValue(event, *args, count);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 badgeShop_ThrowCheck(s32 itemId) {
	int i;
	s32 count;

	for (count = 0, i = 0; i < bdsw->bargainNum; i++) {
		if (itemId == bdsw->bargainBadges[i + bdsw->bargainNum]) {
			count++;
		}
	}
	return count;
}
#endif

#ifdef NONMATCHING
s32 U_badgeShop_SpecialCheck(void) {
	s32 count;
	int i;

	for (count = 0, i = 0; i < 5; i++) {
		if (bdsw->bargainBadges[i]) {
			count++;
		}
	}
	return count;
}
#endif

#ifndef NONMATCHING
// FAKE (asm stopgap): badgeShop_bottakuruGeneration (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off


asm s32 U_badgeShop_SpecialCheck(void) {
	nofralloc
	lwz r4, bdsw(r13)
	li r3, 0x0
	lwz r0, 0xf8(r4)
	cmpwi r0, 0x0
	beq @1
	li r3, 0x1
	@1:
	lwz r0, 0xfc(r4)
	cmpwi r0, 0x0
	beq @2
	addi r3, r3, 0x1
	@2:
	lwz r0, 0x100(r4)
	cmpwi r0, 0x0
	beq @3
	addi r3, r3, 0x1
	@3:
	lwz r0, 0x104(r4)
	cmpwi r0, 0x0
	beq @4
	addi r3, r3, 0x1
	@4:
	lwz r0, 0x108(r4)
	cmpwi r0, 0x0
	beqlr
	addi r3, r3, 0x1
	blr
}

asm s32 badgeShop_ThrowCheck(s32 itemId) {
	nofralloc
	lwz r5, bdsw(r13)
	li r7, 0x0
	li r6, 0x0
	lwz r0, 0x10c(r5)
	mtctr r0
	cmpwi r0, 0x0
	ble @1
	@2:
	lwz r0, 0x10c(r5)
	add r0, r6, r0
	slwi r4, r0, 2
	addi r0, r4, 0xf8
	lwzx r0, r5, r0
	cmpw r3, r0
	bne @3
	addi r7, r7, 0x1
	@3:
	addi r6, r6, 0x1
	bdnz @2
	@1:
	mr r3, r7
	blr
}

asm s32 evt_badgeShop_bteresa_get_kind_cnt(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r5, 0x0
	li r10, 0x0
	stw r0, 0x14(r1)
	li r0, 0x152
	lwz r4, bdsw(r13)
	lwz r9, 0x18(r3)
	addi r8, r4, 0xa0
	mtctr r0
	@1:
	addi r0, r10, 0x1
	extsh r4, r0
	cmpwi r4, 0x1
	blt @2
	cmpwi r4, 0x153
	blt @3
	@2:
	li r0, 0x0
	b @4
	@3:
	subi r0, r4, 0x1
	extsh r4, r0
	clrlwi r0, r4, 30
	cmpwi r0, 0x2
	beq @5
	bge @6
	cmpwi r0, 0x0
	beq @7
	bge @8
	b @9
	@6:
	cmpwi r0, 0x4
	bge @9
	b @10
	@7:
	li r7, 0x3
	li r6, 0x0
	b @9
	@8:
	li r7, 0xc
	li r6, 0x2
	b @9
	@5:
	li r7, 0x30
	li r6, 0x4
	b @9
	@10:
	li r7, 0xc0
	li r6, 0x6
	@9:
	srawi r0, r4, 2
	clrlwi r4, r7, 24
	addze r0, r0
	lbzx r0, r8, r0
	and r0, r4, r0
	sraw r0, r0, r6
	extsh r0, r0
	@4:
	extsh. r0, r0
	ble @11
	addi r5, r5, 0x1
	@11:
	addi r10, r10, 0x1
	bdnz @1
	lwz r4, 0x0(r9)
	bl evtSetValue
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 U_evt_badgeShop_get_special_zaiko(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r5, 0x0
	li r10, 0x0
	stw r0, 0x14(r1)
	li r0, 0x152
	lwz r4, bdsw(r13)
	lwz r9, 0x18(r3)
	addi r8, r4, 0x4b
	mtctr r0
	@1:
	addi r0, r10, 0x1
	extsh r4, r0
	cmpwi r4, 0x1
	blt @2
	cmpwi r4, 0x153
	blt @3
	@2:
	li r0, 0x0
	b @4
	@3:
	subi r0, r4, 0x1
	extsh r4, r0
	clrlwi r0, r4, 30
	cmpwi r0, 0x2
	beq @5
	bge @6
	cmpwi r0, 0x0
	beq @7
	bge @8
	b @9
	@6:
	cmpwi r0, 0x4
	bge @9
	b @10
	@7:
	li r7, 0x3
	li r6, 0x0
	b @9
	@8:
	li r7, 0xc
	li r6, 0x2
	b @9
	@5:
	li r7, 0x30
	li r6, 0x4
	b @9
	@10:
	li r7, 0xc0
	li r6, 0x6
	@9:
	srawi r0, r4, 2
	clrlwi r4, r7, 24
	addze r0, r0
	lbzx r0, r8, r0
	and r0, r4, r0
	sraw r0, r0, r6
	extsh r0, r0
	@4:
	extsh r0, r0
	li r4, 0x1
	cntlzw r0, r0
	rlwnm. r0, r4, r0, 31, 31
	bne @11
	addi r5, r5, 0x1
	@11:
	addi r10, r10, 0x1
	bdnz @1
	lwz r4, 0x0(r9)
	bl evtSetValue
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_badgeShop_bottakuru_get_kind_cnt(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r27, r3
	lis r3, badge_bottakuru_table@ha
	li r29, 0x0
	addi r31, r3, badge_bottakuru_table@l
	li r28, 0x0
	lwz r30, 0x18(r27)
	@1:
	subis r4, r28, 0xa22
	mr r3, r27
	addi r4, r4, 0x1f6
	bl evtGetValue
	slwi r0, r3, 2
	lwzx r0, r31, r0
	cmpwi r0, 0x0
	beq @2
	addi r29, r29, 0x1
	@2:
	addi r28, r28, 0x1
	cmpwi r28, 0x4
	blt @1
	lwz r4, 0x0(r30)
	mr r3, r27
	mr r5, r29
	bl evtSetValue
	lmw r27, 0xc(r1)
	li r3, 0x2
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_badgeShop_starmaniac_get_kind_cnt(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r5, 0x0
	li r12, 0x0
	stw r0, 0x14(r1)
	li r0, 0x63
	lwz r4, bdsw(r13)
	lwz r11, 0x18(r3)
	addi r8, r4, 0x32
	addi r9, r4, 0x4b
	addi r10, r4, 0xa0
	mtctr r0
	@1:
	cmplw r8, r9
	beq @2
	cmplw r8, r10
	bne @3
	@2:
	li r4, 0x1
	b @4
	@3:
	li r4, 0xf0
	@4:
	addi r0, r12, 0xf0
	extsh r0, r0
	cmpw r0, r4
	blt @5
	cmpwi r0, 0x153
	blt @6
	@5:
	li r0, 0x0
	b @7
	@6:
	subf r0, r4, r0
	extsh r4, r0
	clrlwi r0, r4, 30
	cmpwi r0, 0x2
	beq @8
	bge @9
	cmpwi r0, 0x0
	beq @10
	bge @11
	b @12
	@9:
	cmpwi r0, 0x4
	bge @12
	b @13
	@10:
	li r7, 0x3
	li r6, 0x0
	b @12
	@11:
	li r7, 0xc
	li r6, 0x2
	b @12
	@8:
	li r7, 0x30
	li r6, 0x4
	b @12
	@13:
	li r7, 0xc0
	li r6, 0x6
	@12:
	srawi r0, r4, 2
	clrlwi r4, r7, 24
	addze r0, r0
	lbzx r0, r8, r0
	and r0, r4, r0
	sraw r0, r0, r6
	extsh r0, r0
	@7:
	extsh. r0, r0
	ble @14
	addi r5, r5, 0x1
	@14:
	addi r12, r12, 0x1
	bdnz @1
	lwz r4, 0x0(r11)
	bl evtSetValue
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_badgeShop_throw_get_kind_cnt(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r5, 0x0
	li r12, 0x0
	stw r0, 0x14(r1)
	li r0, 0x63
	lwz r4, bdsw(r13)
	lwz r11, 0x18(r3)
	addi r8, r4, 0x19
	addi r9, r4, 0x4b
	addi r10, r4, 0xa0
	mtctr r0
	@1:
	cmplw r8, r9
	beq @2
	cmplw r8, r10
	bne @3
	@2:
	li r4, 0x1
	b @4
	@3:
	li r4, 0xf0
	@4:
	addi r0, r12, 0xf0
	extsh r0, r0
	cmpw r0, r4
	blt @5
	cmpwi r0, 0x153
	blt @6
	@5:
	li r0, 0x0
	b @7
	@6:
	subf r0, r4, r0
	extsh r4, r0
	clrlwi r0, r4, 30
	cmpwi r0, 0x2
	beq @8
	bge @9
	cmpwi r0, 0x0
	beq @10
	bge @11
	b @12
	@9:
	cmpwi r0, 0x4
	bge @12
	b @13
	@10:
	li r7, 0x3
	li r6, 0x0
	b @12
	@11:
	li r7, 0xc
	li r6, 0x2
	b @12
	@8:
	li r7, 0x30
	li r6, 0x4
	b @12
	@13:
	li r7, 0xc0
	li r6, 0x6
	@12:
	srawi r0, r4, 2
	clrlwi r4, r7, 24
	addze r0, r0
	lbzx r0, r8, r0
	and r0, r4, r0
	sraw r0, r0, r6
	extsh r0, r0
	@7:
	extsh. r0, r0
	ble @14
	addi r5, r5, 0x1
	@14:
	addi r12, r12, 0x1
	bdnz @1
	lwz r4, 0x0(r11)
	bl evtSetValue
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_badgeShop_bottakuru_dec(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	lwz r6, bdsw(r13)
	mr r30, r3
	extsh r4, r30
	li r5, -0x1
	addi r3, r6, 0x4b
	bl badgeShop_add
	lis r3, badge_bottakuru_table@ha
	li r29, 0x0
	addi r31, r3, badge_bottakuru_table@l
	@1:
	subis r4, r29, 0xa22
	mr r3, r28
	addi r4, r4, 0x1f6
	bl evtGetValue
	slwi r0, r3, 2
	lwzx r0, r31, r0
	cmpw r30, r0
	bne @2
	subis r4, r29, 0xa22
	mr r3, r28
	li r5, 0x10
	addi r4, r4, 0x1f6
	bl evtSetValue
	@2:
	addi r29, r29, 0x1
	cmpwi r29, 0x4
	blt @1
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_badgeShop_starmaniac_dec(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	lwz r6, bdsw(r13)
	extsh r4, r3
	li r5, -0x1
	addi r3, r6, 0x32
	bl badgeShop_add
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_badgeShop_special_dec(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	mr r0, r3
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, -0x1
	bl badgeShop_add
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_badgeShop_throw_dec(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	lwz r6, bdsw(r13)
	mr r31, r3
	extsh r4, r31
	li r5, -0x1
	addi r3, r6, 0x19
	bl badgeShop_add
	lwz r3, bdsw(r13)
	extsh r4, r31
	li r5, -0x1
	bl badgeShop_add
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_badgeShop_throw_inc(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	lwz r6, bdsw(r13)
	mr r31, r3
	extsh r4, r31
	li r5, 0x1
	addi r3, r6, 0x19
	bl badgeShop_add
	lwz r3, bdsw(r13)
	extsh r4, r31
	li r5, 0x1
	bl badgeShop_add
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 badgeShop_getBargainTable(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r5, bdsw(r13)
	lwz r4, 0x0(r4)
	addi r5, r5, 0xf8
	bl evtSetValue
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 badgeShop_add(u8* table, s16 id, s32 value) {
	nofralloc
	lwz r6, bdsw(r13)
	addi r0, r6, 0x4b
	cmplw r3, r0
	beq @1
	addi r0, r6, 0xa0
	cmplw r3, r0
	bne @2
	@1:
	li r6, 0x1
	b @3
	@2:
	li r6, 0xf0
	@3:
	extsh r0, r4
	cmpw r0, r6
	blt @4
	cmpwi r0, 0x153
	blt @5
	@4:
	li r3, 0x0
	blr
	@5:
	subf r0, r6, r0
	extsh r4, r0
	clrlwi r0, r4, 30
	cmpwi r0, 0x2
	beq @6
	bge @7
	cmpwi r0, 0x0
	beq @8
	bge @9
	b @10
	@7:
	cmpwi r0, 0x4
	bge @10
	b @11
	@8:
	li r7, 0x3
	li r8, 0x0
	b @10
	@9:
	li r7, 0xc
	li r8, 0x2
	b @10
	@6:
	li r7, 0x30
	li r8, 0x4
	b @10
	@11:
	li r7, 0xc0
	li r8, 0x6
	@10:
	srawi r0, r4, 2
	clrlwi r7, r7, 24
	addze r6, r0
	lbzx r4, r3, r6
	and r0, r7, r4
	sraw r0, r0, r8
	extsh r0, r0
	add r0, r0, r5
	extsh. r5, r0
	bge @12
	li r5, 0x0
	b @13
	@12:
	cmpwi r5, 0x3
	ble @13
	li r5, 0x3
	@13:
	extsh r0, r5
	andc r4, r4, r7
	slw r0, r0, r8
	clrlwi r4, r4, 24
	clrlwi r0, r0, 24
	add r0, r4, r0
	stbx r0, r3, r6
	mr r3, r5
	blr
}

asm s32 badgeShop_get(u8* table, s16 id) {
	nofralloc
	lwz r5, bdsw(r13)
	addi r0, r5, 0x4b
	cmplw r3, r0
	beq @1
	addi r0, r5, 0xa0
	cmplw r3, r0
	bne @2
	@1:
	li r5, 0x1
	b @3
	@2:
	li r5, 0xf0
	@3:
	extsh r0, r4
	cmpw r0, r5
	blt @4
	cmpwi r0, 0x153
	blt @5
	@4:
	li r3, 0x0
	blr
	@5:
	subf r0, r5, r0
	extsh r4, r0
	clrlwi r0, r4, 30
	cmpwi r0, 0x2
	beq @6
	bge @7
	cmpwi r0, 0x0
	beq @8
	bge @9
	b @10
	@7:
	cmpwi r0, 0x4
	bge @10
	b @11
	@8:
	li r6, 0x3
	li r7, 0x0
	b @10
	@9:
	li r6, 0xc
	li r7, 0x2
	b @10
	@6:
	li r6, 0x30
	li r7, 0x4
	b @10
	@11:
	li r6, 0xc0
	li r7, 0x6
	@10:
	srawi r0, r4, 2
	clrlwi r4, r6, 24
	addze r0, r0
	lbzx r0, r3, r0
	and r0, r4, r0
	sraw r0, r0, r7
	extsh r3, r0
	blr
}

asm s16 badgeShop_set(u8* table, s16 id, s16 val) {
	nofralloc
	lwz r6, bdsw(r13)
	addi r0, r6, 0x4b
	cmplw r3, r0
	beq @1
	addi r0, r6, 0xa0
	cmplw r3, r0
	bne @2
	@1:
	li r6, 0x1
	b @3
	@2:
	li r6, 0xf0
	@3:
	extsh r0, r4
	cmpw r0, r6
	blt @4
	cmpwi r0, 0x153
	blt @5
	@4:
	li r3, 0x0
	blr
	@5:
	subf r0, r6, r0
	extsh r4, r0
	clrlwi r0, r4, 30
	cmpwi r0, 0x2
	beq @6
	bge @7
	cmpwi r0, 0x0
	beq @8
	bge @9
	b @10
	@7:
	cmpwi r0, 0x4
	bge @10
	b @11
	@8:
	li r7, 0xfc
	li r8, 0x0
	b @10
	@9:
	li r7, 0xf3
	li r8, 0x2
	b @10
	@6:
	li r7, 0xcf
	li r8, 0x4
	b @10
	@11:
	li r7, 0x3f
	li r8, 0x6
	@10:
	extsh. r0, r5
	srawi r0, r4, 2
	addze r6, r0
	bge @12
	li r5, 0x0
	b @13
	@12:
	extsh r0, r5
	cmpwi r0, 0x3
	ble @13
	li r5, 0x3
	@13:
	lbzx r4, r3, r6
	extsh r0, r5
	slw r0, r0, r8
	and r4, r7, r4
	clrlwi r4, r4, 24
	clrlwi r0, r0, 24
	add r0, r4, r0
	stbx r0, r3, r6
	mr r3, r5
	blr
}

void qqsort(void*, s32, s32, void*);
asm void badgeShop_bargainGeneration(void) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	lis r4, 0xf5de
	li r3, 0x0
	stw r0, 0x54(r1)
	addi r4, r4, 0x180
	stmw r24, 0x30(r1)
	bl evtGetValue
	cmpwi r3, 0x37
	blt @1
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c6e
	bl evtGetValue
	cmpwi r3, 0x0
	bne @1
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c6e
	li r5, 0x1
	bl evtSetValue
	la r24, badge_special_table_stage_1_clear(r13)
	b @2
	@3:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	bl badgeShop_add
	addi r24, r24, 0x4
	@2:
	lwz r0, 0x0(r24)
	cmpwi r0, 0x0
	bne @3
	@1:
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x180
	bl evtGetValue
	cmpwi r3, 0x70
	blt @4
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c6f
	bl evtGetValue
	cmpwi r3, 0x0
	bne @4
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c6f
	li r5, 0x1
	bl evtSetValue
	la r24, badge_special_table_stage_2_clear(r13)
	b @5
	@6:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	bl badgeShop_add
	addi r24, r24, 0x4
	@5:
	lwz r0, 0x0(r24)
	cmpwi r0, 0x0
	bne @6
	@4:
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x180
	bl evtGetValue
	cmpwi r3, 0xa4
	blt @7
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c70
	bl evtGetValue
	cmpwi r3, 0x0
	bne @7
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c70
	li r5, 0x1
	bl evtSetValue
	la r24, badge_special_table_stage_3_clear(r13)
	b @8
	@9:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	bl badgeShop_add
	addi r24, r24, 0x4
	@8:
	lwz r0, 0x0(r24)
	cmpwi r0, 0x0
	bne @9
	@7:
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x180
	bl evtGetValue
	cmpwi r3, 0xd4
	blt @10
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c71
	bl evtGetValue
	cmpwi r3, 0x0
	bne @10
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c71
	li r5, 0x1
	bl evtSetValue
	la r24, badge_special_table_stage_4_clear(r13)
	b @11
	@12:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	bl badgeShop_add
	addi r24, r24, 0x4
	@11:
	lwz r0, 0x0(r24)
	cmpwi r0, 0x0
	bne @12
	@10:
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x180
	bl evtGetValue
	cmpwi r3, 0xfd
	blt @13
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c72
	bl evtGetValue
	cmpwi r3, 0x0
	bne @13
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c72
	li r5, 0x1
	bl evtSetValue
	la r24, badge_special_table_stage_5_clear(r13)
	b @14
	@15:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	bl badgeShop_add
	addi r24, r24, 0x4
	@14:
	lwz r0, 0x0(r24)
	cmpwi r0, 0x0
	bne @15
	@13:
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x180
	bl evtGetValue
	cmpwi r3, 0x152
	blt @16
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c73
	bl evtGetValue
	cmpwi r3, 0x0
	bne @16
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c73
	li r5, 0x1
	bl evtSetValue
	la r24, badge_special_table_stage_6_clear(r13)
	b @17
	@18:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	bl badgeShop_add
	addi r24, r24, 0x4
	@17:
	lwz r0, 0x0(r24)
	cmpwi r0, 0x0
	bne @18
	@16:
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x180
	bl evtGetValue
	cmpwi r3, 0x175
	blt @19
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c74
	bl evtGetValue
	cmpwi r3, 0x0
	bne @19
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c74
	li r5, 0x1
	bl evtSetValue
	@19:
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x180
	bl evtGetValue
	cmpwi r3, 0x191
	blt @20
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c75
	bl evtGetValue
	cmpwi r3, 0x0
	bne @20
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c75
	li r5, 0x1
	bl evtSetValue
	@20:
	addi r3, r1, 0x8
	li r4, 0x0
	li r5, 0x19
	bl memset
	lwz r3, bdsw(r13)
	li r25, 0x0
	li r30, 0x0
	li r31, 0x0
	stw r25, 0xf8(r3)
	li r24, 0x0
	lwz r3, bdsw(r13)
	stw r25, 0xfc(r3)
	lwz r3, bdsw(r13)
	stw r25, 0x100(r3)
	lwz r3, bdsw(r13)
	stw r25, 0x104(r3)
	lwz r3, bdsw(r13)
	stw r25, 0x108(r3)
	lwz r3, bdsw(r13)
	stw r25, 0x10c(r3)
	lwz r3, bdsw(r13)
	stw r25, 0x110(r3)
	@21:
	lwz r4, bdsw(r13)
	li r5, 0x0
	li r3, 0xf0
	addi r0, r4, 0xa0
	cmplw r4, r0
	bne @22
	li r3, 0x1
	@22:
	addi r0, r25, 0xf0
	extsh r0, r0
	cmpw r0, r3
	blt @23
	cmpwi r0, 0x153
	blt @24
	@23:
	li r0, 0x0
	b @25
	@24:
	subf r0, r3, r0
	extsh r3, r0
	clrlwi r0, r3, 30
	cmpwi r0, 0x2
	beq @26
	bge @27
	cmpwi r0, 0x0
	beq @28
	bge @29
	b @30
	@27:
	cmpwi r0, 0x4
	bge @30
	b @31
	@28:
	li r28, 0x3
	li r29, 0x0
	b @30
	@29:
	li r28, 0xc
	li r29, 0x2
	b @30
	@26:
	li r28, 0x30
	li r29, 0x4
	b @30
	@31:
	li r28, 0xc0
	li r29, 0x6
	@30:
	srawi r0, r3, 2
	clrlwi r3, r28, 24
	addze r0, r0
	lbzx r0, r4, r0
	and r0, r3, r0
	sraw r0, r0, r29
	extsh r0, r0
	@25:
	extsh. r0, r0
	beq @32
	ori r0, r5, 0x1
	addi r31, r31, 0x1
	extsh r5, r0
	@32:
	extsh. r0, r5
	beq @33
	addi r0, r25, 0xf0
	addi r3, r1, 0x8
	extsh r4, r0
	bl badgeShop_set
	addi r24, r24, 0x1
	@33:
	addi r25, r25, 0x1
	cmpwi r25, 0x63
	blt @21
	cmpwi r24, 0x5
	li r29, 0x5
	bgt @34
	mr r29, r24
	@34:
	li r3, 0x100
	bl irand
	b @35
	@36:
	cmpwi r3, 0x3
	blt @37
	cmpwi r30, 0x0
	bne @35
	@37:
	mr r3, r31
	bl irand
	lwz r6, bdsw(r13)
	li r9, 0x63
	extsh r7, r3
	addi r0, r1, 0x8
	addi r3, r6, 0x4b
	addi r4, r6, 0xa0
	li r8, 0x0
	li r5, 0x0
	mtctr r9
	@38:
	cmplw r0, r3
	beq @39
	cmplw r0, r4
	bne @40
	@39:
	li r10, 0x1
	b @41
	@40:
	li r10, 0xf0
	@41:
	addi r9, r5, 0xf0
	extsh r9, r9
	cmpw r9, r10
	blt @42
	cmpwi r9, 0x153
	blt @43
	@42:
	li r28, 0x0
	b @44
	@43:
	subf r9, r10, r9
	extsh r10, r9
	clrlwi r9, r10, 30
	cmpwi r9, 0x2
	beq @45
	bge @46
	cmpwi r9, 0x0
	beq @47
	bge @48
	b @49
	@46:
	cmpwi r9, 0x4
	bge @49
	b @50
	@47:
	li r26, 0x3
	li r27, 0x0
	b @49
	@48:
	li r26, 0xc
	li r27, 0x2
	b @49
	@45:
	li r26, 0x30
	li r27, 0x4
	b @49
	@50:
	li r26, 0xc0
	li r27, 0x6
	@49:
	srawi r10, r10, 2
	addi r9, r1, 0x8
	addze r10, r10
	clrlwi r11, r26, 24
	lbzx r9, r9, r10
	and r9, r11, r9
	sraw r9, r9, r27
	extsh r28, r9
	@44:
	clrlwi. r9, r28, 31
	beq @51
	extsh r9, r8
	cmpw r9, r7
	beq @52
	addi r8, r8, 0x1
	@51:
	addi r5, r5, 0x1
	bdnz @38
	@52:
	cmpwi r5, 0x63
	bge @35
	lwz r0, 0x10c(r6)
	addi r8, r5, 0xf0
	addi r3, r1, 0x8
	li r5, 0x0
	slwi r7, r0, 2
	extsh r4, r8
	addi r0, r7, 0xf8
	stwx r8, r6, r0
	lwz r7, bdsw(r13)
	lwz r6, 0x10c(r7)
	addi r0, r6, 0x1
	stw r0, 0x10c(r7)
	bl badgeShop_set
	extsh r3, r28
	clrlwi. r0, r3, 31
	beq @53
	subi r31, r31, 0x1
	@53:
	rlwinm. r0, r3, 0, 30, 30
	beq @35
	subi r30, r30, 0x1
	@35:
	lwz r4, bdsw(r13)
	lwz r3, 0x10c(r4)
	lwz r0, 0x110(r4)
	add r0, r3, r0
	cmpw r0, r29
	blt @36
	li r0, 0x5
	li r4, 0x0
	mtctr r0
	@54:
	lwz r0, bdsw(r13)
	add r3, r0, r4
	lbz r0, 0x0(r3)
	stb r0, 0x19(r3)
	lwz r0, bdsw(r13)
	add r3, r0, r4
	lbz r0, 0x1(r3)
	stb r0, 0x1a(r3)
	lwz r0, bdsw(r13)
	add r3, r0, r4
	lbz r0, 0x2(r3)
	stb r0, 0x1b(r3)
	lwz r0, bdsw(r13)
	add r3, r0, r4
	lbz r0, 0x3(r3)
	stb r0, 0x1c(r3)
	lwz r0, bdsw(r13)
	add r3, r0, r4
	addi r4, r4, 0x5
	lbz r0, 0x4(r3)
	stb r0, 0x1d(r3)
	bdnz @54
	li r25, 0x0
	mr r24, r25
	@55:
	lwz r3, bdsw(r13)
	addi r0, r24, 0xf8
	lwzx r0, r3, r0
	cmpwi r0, 0x0
	beq @56
	addi r3, r3, 0x19
	extsh r4, r0
	li r5, -0x1
	bl badgeShop_add
	@56:
	addi r25, r25, 0x1
	addi r24, r24, 0x4
	cmpwi r25, 0x5
	blt @55
	lmw r24, 0x30(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void badgeShop_bteresaGeneration(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x5b
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq @1
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c76
	bl evtGetValue
	cmpwi r3, 0x0
	bne @1
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c76
	li r5, 0x1
	bl evtSetValue
	la r31, badge_bteresa_table_card_special(r13)
	b @2
	@3:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	addi r3, r3, 0xa0
	bl badgeShop_add
	addi r31, r31, 0x4
	@2:
	lwz r0, 0x0(r31)
	cmpwi r0, 0x0
	bne @3
	@1:
	li r3, 0x5e
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq @4
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c77
	bl evtGetValue
	cmpwi r3, 0x0
	bne @4
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c77
	li r5, 0x1
	bl evtSetValue
	la r31, badge_bteresa_table_card_silver(r13)
	b @5
	@6:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	addi r3, r3, 0xa0
	bl badgeShop_add
	addi r31, r31, 0x4
	@5:
	lwz r0, 0x0(r31)
	cmpwi r0, 0x0
	bne @6
	@4:
	li r3, 0x5d
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq @7
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c78
	bl evtGetValue
	cmpwi r3, 0x0
	bne @7
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c78
	li r5, 0x1
	bl evtSetValue
	la r31, badge_bteresa_table_card_gold(r13)
	b @8
	@9:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	addi r3, r3, 0xa0
	bl badgeShop_add
	addi r31, r31, 0x4
	@8:
	lwz r0, 0x0(r31)
	cmpwi r0, 0x0
	bne @9
	@7:
	li r3, 0x5c
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq @10
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c79
	bl evtGetValue
	cmpwi r3, 0x0
	bne @10
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c79
	li r5, 0x1
	bl evtSetValue
	la r31, badge_bteresa_table_card_platinum(r13)
	b @11
	@12:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	addi r3, r3, 0xa0
	bl badgeShop_add
	addi r31, r31, 0x4
	@11:
	lwz r0, 0x0(r31)
	cmpwi r0, 0x0
	bne @12
	@10:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void badgeShop_bottakuruGeneration(void) {
	nofralloc
	stwu r1, -0xc0(r1)
	mflr r0
	li r7, 0x10
	li r5, 0xc8
	stw r0, 0xc4(r1)
	li r4, 0x0
	addi r6, r1, 0x8
	slwi r3, r7, 3
	stmw r21, 0x94(r1)
	subfic r0, r7, 0x11
	add r6, r6, r3
	stw r5, 0xc(r1)
	stw r4, 0x8(r1)
	stw r5, 0x14(r1)
	stw r4, 0x10(r1)
	stw r5, 0x1c(r1)
	stw r4, 0x18(r1)
	stw r5, 0x24(r1)
	stw r4, 0x20(r1)
	stw r5, 0x2c(r1)
	stw r4, 0x28(r1)
	stw r5, 0x34(r1)
	stw r4, 0x30(r1)
	stw r5, 0x3c(r1)
	stw r4, 0x38(r1)
	stw r5, 0x44(r1)
	stw r4, 0x40(r1)
	stw r5, 0x4c(r1)
	stw r4, 0x48(r1)
	stw r5, 0x54(r1)
	stw r4, 0x50(r1)
	stw r5, 0x5c(r1)
	stw r4, 0x58(r1)
	stw r5, 0x64(r1)
	stw r4, 0x60(r1)
	stw r5, 0x6c(r1)
	stw r4, 0x68(r1)
	stw r5, 0x74(r1)
	stw r4, 0x70(r1)
	stw r5, 0x7c(r1)
	stw r4, 0x78(r1)
	stw r5, 0x84(r1)
	stw r4, 0x80(r1)
	mtctr r0
	cmplwi r7, 0x11
	bge @1
	@2:
	stw r5, 0x4(r6)
	stw r4, 0x0(r6)
	addi r6, r6, 0x8
	bdnz @2
	@1:
	addi r28, r1, 0x8
	li r25, 0x0
	mr r27, r25
	li r26, 0x0
	mr r29, r28
	@3:
	lwz r3, bdsw(r13)
	addi r4, r3, 0x4b
	cmplw r4, r4
	beq @4
	addi r0, r3, 0xa0
	cmplw r4, r0
	bne @5
	@4:
	li r3, 0x1
	b @6
	@5:
	li r3, 0xf0
	@6:
	addi r0, r27, 0x1
	extsh r0, r0
	cmpw r0, r3
	blt @7
	cmpwi r0, 0x153
	blt @8
	@7:
	li r0, 0x0
	b @9
	@8:
	subf r0, r3, r0
	extsh r3, r0
	clrlwi r0, r3, 30
	cmpwi r0, 0x2
	beq @10
	bge @11
	cmpwi r0, 0x0
	beq @12
	bge @13
	b @14
	@11:
	cmpwi r0, 0x4
	bge @14
	b @15
	@12:
	li r30, 0x3
	li r31, 0x0
	b @14
	@13:
	li r30, 0xc
	li r31, 0x2
	b @14
	@10:
	li r30, 0x30
	li r31, 0x4
	b @14
	@15:
	li r30, 0xc0
	li r31, 0x6
	@14:
	srawi r0, r3, 2
	clrlwi r3, r30, 24
	addze r0, r0
	lbzx r0, r4, r0
	and r0, r3, r0
	sraw r0, r0, r31
	extsh r0, r0
	@9:
	mr r23, r29
	extsh r21, r0
	addi r24, r27, 0x1
	li r22, 0x0
	b @16
	@17:
	li r3, 0x64
	bl irand
	stw r3, 0x4(r23)
	addi r26, r26, 0x1
	cmplwi r26, 0x10
	addi r23, r23, 0x8
	stwx r24, r28, r25
	addi r25, r25, 0x8
	addi r29, r29, 0x8
	bge @18
	addi r22, r22, 0x1
	@16:
	cmpw r22, r21
	blt @17
	@18:
	cmplwi r26, 0x10
	bge @19
	addi r27, r27, 0x1
	cmpwi r27, 0x152
	blt @3
	@19:
	lis r4, bottakuruComp@ha
	addi r3, r1, 0x8
	addi r6, r4, bottakuruComp@l
	li r5, 0x8
	li r4, 0x11
	bl qqsort
	lis r3, badge_bottakuru_table@ha
	li r24, 0x0
	addi r25, r3, badge_bottakuru_table@l
	@20:
	li r26, 0x0
	mr r23, r25
	@21:
	lwz r3, 0x0(r28)
	lwz r0, 0x0(r23)
	cmpw r3, r0
	bne @22
	subis r4, r24, 0xa22
	mr r5, r26
	li r3, 0x0
	addi r4, r4, 0x1f6
	bl evtSetValue
	@22:
	addi r26, r26, 0x1
	addi r23, r23, 0x4
	cmplwi r26, 0x11
	blt @21
	addi r24, r24, 0x1
	addi r28, r28, 0x8
	cmpwi r24, 0x4
	blt @20
	lmw r21, 0x94(r1)
	lwz r0, 0xc4(r1)
	mtlr r0
	addi r1, r1, 0xc0
	blr
}
// clang-format on
#endif
