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
#ifndef NONMATCHING
#define EXT_LIT(sym, val) (sym)

#endif

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

#ifdef NONMATCHING
s32 getBadgeBottakuru100TableMaxCount(void) {
	return (sizeof(badge_bottakuru100_table) / sizeof(s32)) - 1;
#endif
#ifndef NONMATCHING
s32 getBadgeBottakuru100TableMaxCount(void);

s32 getBadgeStarmaniacTableMaxCount(void);

s32 getBadgeBteresaTableMaxCount(void);

void badgeShop_init(void);

s32 bottakuruComp(const void** sortA, const void** sortB);

int qqsort();
void badgeShop_bottakuruGeneration(void);

void badgeShop_bteresaGeneration(void);

void badgeShop_bargainGeneration(void);

s16 badgeShop_set(u8* table, s16 id, s16 val);
s32 badgeShop_get(u8* table, s16 id);

s32 badgeShop_add(u8* table, s16 id, s32 value);

s32 badgeShop_getBargainTable(EventEntry* event, BOOL isFirstCall);

s32 evt_badgeShop_throw_inc(EventEntry* event, BOOL isFirstCall);

s32 evt_badgeShop_throw_dec(EventEntry* event, BOOL isFirstCall);

s32 evt_badgeShop_special_dec(EventEntry* event, BOOL isFirstCall);

s32 evt_badgeShop_starmaniac_dec(EventEntry* event, BOOL isFirstCall);

#pragma opt_common_subs off
s32 evt_badgeShop_bottakuru_dec(EventEntry* event, BOOL isFirstCall);

#pragma opt_common_subs reset
s32 evt_badgeShop_throw_get_kind_cnt(EventEntry* event, BOOL isFirstCall);

s32 evt_badgeShop_starmaniac_get_kind_cnt(EventEntry* event, BOOL isFirstCall);

s32 evt_badgeShop_bottakuru_get_kind_cnt(EventEntry* event, BOOL isFirstCall);

s32 U_evt_badgeShop_get_special_zaiko(EventEntry* event, BOOL isFirstCall);

s32 evt_badgeShop_bteresa_get_kind_cnt(EventEntry* event, BOOL isFirstCall);

s32 badgeShop_ThrowCheck(s32 itemId);

s32 U_badgeShop_SpecialCheck(void);

static inline s32 badgeShop_get__af_inl(u8* table, s16 id) { //1:1
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
#endif
}

#ifdef NONMATCHING
s32 getBadgeStarmaniacTableMaxCount(void) {
	return (sizeof(badge_starmaniac_table) / sizeof(s32)) - 1;
#endif
#ifndef NONMATCHING
#define badgeShop_get badgeShop_get__af_inl
s32 evt_badgeShop_throw_get_kind_cnt(EventEntry* event, BOOL isFirstCall) {
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
#endif
}

#ifdef NONMATCHING
s32 getBadgeBteresaTableMaxCount(void) {
	return ((sizeof(badge_bteresa_table) / sizeof(s32)) - 1) +
		((sizeof(badge_bteresa_table_card_special) / sizeof(s32)) - 1) +
		((sizeof(badge_bteresa_table_card_silver) / sizeof(s32)) - 1) +
		((sizeof(badge_bteresa_table_card_gold) / sizeof(s32)) - 1) +
		((sizeof(badge_bteresa_table_card_platinum) / sizeof(s32)) - 1);
#endif
#ifndef NONMATCHING
#undef badgeShop_get

#define badgeShop_get badgeShop_get__af_inl
s32 evt_badgeShop_starmaniac_get_kind_cnt(EventEntry* event, BOOL isFirstCall) {
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
#endif
}

#ifdef NONMATCHING
void badgeShop_init(void) {
	s32* ptr;
#endif
#ifndef NONMATCHING
#undef badgeShop_get
#endif

#ifdef NONMATCHING
	bdsw = &badgeshopwork;
	memset(bdsw->special_table, 0, sizeof(bdsw->special_table));
	memset(bdsw->bargain_table, 0, sizeof(bdsw->bargain_table));
	memset(bdsw->starmaniac_table, 0, sizeof(bdsw->starmaniac_table));
	memset(bdsw->bottakuru_table, 0, sizeof(bdsw->bottakuru_table));
	memset(bdsw->bteresa_table, 0, sizeof(bdsw->bteresa_table));
	bdsw->restockFlags = 1;
#endif
#ifndef NONMATCHING
s32 evt_badgeShop_bottakuru_get_kind_cnt(EventEntry* event, BOOL isFirstCall) {
	s32* args = event->args;
	s32 count;
	int i;
#endif

#ifdef NONMATCHING
	for (ptr = badge_special_table; *ptr; ++ptr) {
		badgeShop_add(bdsw->special_table, (s16)*ptr, 1);
#endif
#ifndef NONMATCHING
	for (count = 0, i = 0; i < 4; i++) {
		if (badge_bottakuru_table[evtGetValue(event, i + GSW(118))]) {
			count++;
		}
#endif
	}
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	evtSetValue(event, *args, count);
	return EVT_RETURN_DONE;
#endif
}

#ifdef NONMATCHING
s32 bottakuruComp(const void** sortA, const void** sortB) {
	s32 a, b;
#endif
#ifndef NONMATCHING
#define badgeShop_get badgeShop_get__af_inl
s32 U_evt_badgeShop_get_special_zaiko(EventEntry* event, BOOL isFirstCall) {
	s32* args = event->args;
	s16 badge;
	s32 count;
	int i;
#endif

#ifdef NONMATCHING
	a = (s32)sortA[1];
	b = (s32)sortB[1];
	if (a < b) {
		return -1;
#endif
#ifndef NONMATCHING
	for (count = 0, i = 0; i < BADGE_MAX - 1; i++) {
		badge = badgeShop_get(bdsw->bottakuru_table, (s16)(i + KEY_ITEM_MIN));
		if (!(badge <= 0)) {
			count++;
		}
#endif
	}
#ifdef NONMATCHING
	return a > b;
#endif
#ifndef NONMATCHING
	evtSetValue(event, *args, count);
	return EVT_RETURN_DONE;
#endif
}

#ifdef NONMATCHING
void badgeShop_bottakuruGeneration(void) {
	s32 table[0x11][2];
	s32* p;
	s32 i;
	s32 k;
#endif
#ifndef NONMATCHING
#undef badgeShop_get

#define badgeShop_get badgeShop_get__af_inl
s32 evt_badgeShop_bteresa_get_kind_cnt(EventEntry* event, BOOL isFirstCall) {
	s32* args = event->args;
	s16 badge;
#endif
	s32 count;
#ifdef NONMATCHING
	s32 j;
	s32 m;
#endif
#ifndef NONMATCHING
	int i;
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	for (count = 0, i = 0; i < BADGE_MAX - 1; i++) {
		badge = badgeShop_get(bdsw->bteresa_table, (s16)(i + KEY_ITEM_MIN));
		if (badge > 0) { //TODO: wonky cntlzw
			count++;
#endif
		}
	}
#ifdef NONMATCHING

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
#endif
#ifndef NONMATCHING
	evtSetValue(event, *args, count);
	return EVT_RETURN_DONE;
#endif
}

#ifdef NONMATCHING
void badgeShop_bteresaGeneration(void) {
	s32* ptr;
	s32 has;
#endif
#ifndef NONMATCHING
#undef badgeShop_get
#endif

#ifdef NONMATCHING
	has = pouchCheckItem(ITEM_SPECIAL_CARD);
	if (has) {
		if (!evtGetValue(NULL, GSWF(246))) {
			evtSetValue(NULL, GSWF(246), 1);
			for (ptr = badge_bteresa_table_card_special; *ptr; ptr++) {
				badgeShop_add(bdsw->bteresa_table, (s16)*ptr, 1);
			}
#endif
#ifndef NONMATCHING
s32 badgeShop_ThrowCheck(s32 itemId) {
	int i;
	s32 count;

	for (count = 0, i = 0; i < bdsw->bargainNum; i++) {
		if (itemId == bdsw->bargainBadges[i + bdsw->bargainNum]) {
			count++;
#endif
		}
	}
#ifndef NONMATCHING
	return count;
}
#endif

#ifdef NONMATCHING
	has = pouchCheckItem(ITEM_SILVER_CARD);
	if (has) {
		if (!evtGetValue(NULL, GSWF(247))) {
			evtSetValue(NULL, GSWF(247), 1);
			for (ptr = badge_bteresa_table_card_silver; *ptr; ptr++) {
				badgeShop_add(bdsw->bteresa_table, (s16)*ptr, 1);
			}
#endif
#ifndef NONMATCHING
#pragma defer_codegen off
s32 U_badgeShop_SpecialCheck(void) {
	s32 count;
	int i;

	for (count = 0, i = 0; i < 5; i++) {
		if (bdsw->bargainBadges[i]) {
			count++;
#endif
		}
	}
#ifdef NONMATCHING

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
#endif
#ifndef NONMATCHING
	return count;
#endif
}

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
#endif
#ifndef NONMATCHING
#pragma defer_codegen reset
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
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
L_af_1:
	subis r4, r29, 0xa22
	mr r3, r28
	addi r4, r4, 0x1f6
	bl evtGetValue
	slwi r0, r3, 2
	lwzx r0, r31, r0
	cmpw r30, r0
	bne L_af_2
	subis r4, r29, 0xa22
	mr r3, r28
	li r5, 0x10
	addi r4, r4, 0x1f6
	bl evtSetValue
L_af_2:
	addi r29, r29, 0x1
	cmpwi r29, 0x4
	blt L_af_1
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
#endif
}

#pragma dont_inline on
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

#pragma dont_inline reset
#ifndef NONMATCHING

#endif
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

#ifdef NONMATCHING
USER_FUNC(badgeShop_getBargainTable) {
#endif
#ifndef NONMATCHING
s32 badgeShop_getBargainTable(EventEntry* event, BOOL isFirstCall) {
#endif
	evtSetValue(event, *event->args, (s32)&bdsw->bargainBadges);
	return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_badgeShop_throw_inc) {
#endif
#ifndef NONMATCHING
#pragma dont_inline on
s32 evt_badgeShop_throw_inc(EventEntry* event, BOOL isFirstCall) {
#endif
	s32 value;

	value = evtGetValue(event, *event->args);
	badgeShop_add(bdsw->bargain_table, (s16)value, 1);
	badgeShop_add(bdsw->special_table, (s16)value, 1);
	return EVT_RETURN_DONE;
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifdef NONMATCHING
USER_FUNC(evt_badgeShop_throw_dec) {
#endif
#ifndef NONMATCHING
#pragma dont_inline on
s32 evt_badgeShop_throw_dec(EventEntry* event, BOOL isFirstCall) {
#endif
	s32 value;

	value = evtGetValue(event, *event->args);
	badgeShop_add(bdsw->bargain_table, (s16)value, -1);
	badgeShop_add(bdsw->special_table, (s16)value, -1);
	return EVT_RETURN_DONE;
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifdef NONMATCHING
USER_FUNC(evt_badgeShop_special_dec) {
#endif
#ifndef NONMATCHING
#pragma dont_inline on
s32 evt_badgeShop_special_dec(EventEntry* event, BOOL isFirstCall) {
#endif
	s32 value;

	value = evtGetValue(event, *event->args);
	badgeShop_add(bdsw->special_table, (s16)value, -1);
	return EVT_RETURN_DONE;
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifdef NONMATCHING
USER_FUNC(evt_badgeShop_starmaniac_dec) {
#endif
#ifndef NONMATCHING
#pragma dont_inline on
#pragma defer_codegen off
s32 evt_badgeShop_starmaniac_dec(EventEntry* event, BOOL isFirstCall) {
#endif
	s32 value;

	value = (s16)evtGetValue(event, *event->args);
	badgeShop_add(bdsw->starmaniac_table, (s16)value, -1);
	return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
#pragma opt_common_subs off
USER_FUNC(evt_badgeShop_bottakuru_dec) {
	s32 value;
	int i;
#endif
#ifndef NONMATCHING
#pragma defer_codegen reset
#pragma dont_inline reset
#endif

#ifdef NONMATCHING
	value = evtGetValue(event, *event->args);
	badgeShop_add(bdsw->bottakuru_table, (s16)value, -1);
	for (i = 0; i < 4; i++) {
		if (value == badge_bottakuru_table[evtGetValue(event, i + GSW(118))]) {
			evtSetValue(event, GSW(118 + i), (sizeof(badge_bottakuru_table) / sizeof(s32)) - 1); //last entry aka kNullItem
#endif
#ifndef NONMATCHING
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
	blt L_af_1
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c6e
	bl evtGetValue
	cmpwi r3, 0x0
	bne L_af_1
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c6e
	li r5, 0x1
	bl evtSetValue
	la r24, badge_special_table_stage_1_clear(r13)
	b L_af_2
L_af_3:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	bl badgeShop_add
	addi r24, r24, 0x4
L_af_2:
	lwz r0, 0x0(r24)
	cmpwi r0, 0x0
	bne L_af_3
L_af_1:
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x180
	bl evtGetValue
	cmpwi r3, 0x70
	blt L_af_4
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c6f
	bl evtGetValue
	cmpwi r3, 0x0
	bne L_af_4
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c6f
	li r5, 0x1
	bl evtSetValue
	la r24, badge_special_table_stage_2_clear(r13)
	b L_af_5
L_af_6:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	bl badgeShop_add
	addi r24, r24, 0x4
L_af_5:
	lwz r0, 0x0(r24)
	cmpwi r0, 0x0
	bne L_af_6
L_af_4:
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x180
	bl evtGetValue
	cmpwi r3, 0xa4
	blt L_af_7
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c70
	bl evtGetValue
	cmpwi r3, 0x0
	bne L_af_7
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c70
	li r5, 0x1
	bl evtSetValue
	la r24, badge_special_table_stage_3_clear(r13)
	b L_af_8
L_af_9:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	bl badgeShop_add
	addi r24, r24, 0x4
L_af_8:
	lwz r0, 0x0(r24)
	cmpwi r0, 0x0
	bne L_af_9
L_af_7:
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x180
	bl evtGetValue
	cmpwi r3, 0xd4
	blt L_af_10
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c71
	bl evtGetValue
	cmpwi r3, 0x0
	bne L_af_10
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c71
	li r5, 0x1
	bl evtSetValue
	la r24, badge_special_table_stage_4_clear(r13)
	b L_af_11
L_af_12:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	bl badgeShop_add
	addi r24, r24, 0x4
L_af_11:
	lwz r0, 0x0(r24)
	cmpwi r0, 0x0
	bne L_af_12
L_af_10:
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x180
	bl evtGetValue
	cmpwi r3, 0xfd
	blt L_af_13
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c72
	bl evtGetValue
	cmpwi r3, 0x0
	bne L_af_13
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c72
	li r5, 0x1
	bl evtSetValue
	la r24, badge_special_table_stage_5_clear(r13)
	b L_af_14
L_af_15:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	bl badgeShop_add
	addi r24, r24, 0x4
L_af_14:
	lwz r0, 0x0(r24)
	cmpwi r0, 0x0
	bne L_af_15
L_af_13:
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x180
	bl evtGetValue
	cmpwi r3, 0x152
	blt L_af_16
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c73
	bl evtGetValue
	cmpwi r3, 0x0
	bne L_af_16
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c73
	li r5, 0x1
	bl evtSetValue
	la r24, badge_special_table_stage_6_clear(r13)
	b L_af_17
L_af_18:
	lwz r3, bdsw(r13)
	extsh r4, r0
	li r5, 0x1
	bl badgeShop_add
	addi r24, r24, 0x4
L_af_17:
	lwz r0, 0x0(r24)
	cmpwi r0, 0x0
	bne L_af_18
L_af_16:
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x180
	bl evtGetValue
	cmpwi r3, 0x175
	blt L_af_19
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c74
	bl evtGetValue
	cmpwi r3, 0x0
	bne L_af_19
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c74
	li r5, 0x1
	bl evtSetValue
L_af_19:
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x180
	bl evtGetValue
	cmpwi r3, 0x191
	blt L_af_20
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c75
	bl evtGetValue
	cmpwi r3, 0x0
	bne L_af_20
	lis r4, 0xf840
	li r3, 0x0
	addi r4, r4, 0x5c75
	li r5, 0x1
	bl evtSetValue
L_af_20:
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
L_af_21:
	lwz r4, bdsw(r13)
	li r5, 0x0
	li r3, 0xf0
	addi r0, r4, 0xa0
	cmplw r4, r0
	bne L_af_22
	li r3, 0x1
L_af_22:
	addi r0, r25, 0xf0
	extsh r0, r0
	cmpw r0, r3
	blt L_af_23
	cmpwi r0, 0x153
	blt L_af_24
L_af_23:
	li r0, 0x0
	b L_af_25
L_af_24:
	subf r0, r3, r0
	extsh r3, r0
	clrlwi r0, r3, 30
	cmpwi r0, 0x2
	beq L_af_26
	bge L_af_27
	cmpwi r0, 0x0
	beq L_af_28
	bge L_af_29
	b L_af_30
L_af_27:
	cmpwi r0, 0x4
	bge L_af_30
	b L_af_31
L_af_28:
	li r28, 0x3
	li r29, 0x0
	b L_af_30
L_af_29:
	li r28, 0xc
	li r29, 0x2
	b L_af_30
L_af_26:
	li r28, 0x30
	li r29, 0x4
	b L_af_30
L_af_31:
	li r28, 0xc0
	li r29, 0x6
L_af_30:
	srawi r0, r3, 2
	clrlwi r3, r28, 24
	addze r0, r0
	lbzx r0, r4, r0
	and r0, r3, r0
	sraw r0, r0, r29
	extsh r0, r0
L_af_25:
	extsh. r0, r0
	beq L_af_32
	ori r0, r5, 0x1
	addi r31, r31, 0x1
	extsh r5, r0
L_af_32:
	extsh. r0, r5
	beq L_af_33
	addi r0, r25, 0xf0
	addi r3, r1, 0x8
	extsh r4, r0
	bl badgeShop_set
	addi r24, r24, 0x1
L_af_33:
	addi r25, r25, 0x1
	cmpwi r25, 0x63
	blt L_af_21
	cmpwi r24, 0x5
	li r29, 0x5
	bgt L_af_34
	mr r29, r24
L_af_34:
	li r3, 0x100
	bl irand
	b L_af_35
L_af_36:
	cmpwi r3, 0x3
	blt L_af_37
	cmpwi r30, 0x0
	bne L_af_35
L_af_37:
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
L_af_38:
	cmplw r0, r3
	beq L_af_39
	cmplw r0, r4
	bne L_af_40
L_af_39:
	li r10, 0x1
	b L_af_41
L_af_40:
	li r10, 0xf0
L_af_41:
	addi r9, r5, 0xf0
	extsh r9, r9
	cmpw r9, r10
	blt L_af_42
	cmpwi r9, 0x153
	blt L_af_43
L_af_42:
	li r28, 0x0
	b L_af_44
L_af_43:
	subf r9, r10, r9
	extsh r10, r9
	clrlwi r9, r10, 30
	cmpwi r9, 0x2
	beq L_af_45
	bge L_af_46
	cmpwi r9, 0x0
	beq L_af_47
	bge L_af_48
	b L_af_49
L_af_46:
	cmpwi r9, 0x4
	bge L_af_49
	b L_af_50
L_af_47:
	li r26, 0x3
	li r27, 0x0
	b L_af_49
L_af_48:
	li r26, 0xc
	li r27, 0x2
	b L_af_49
L_af_45:
	li r26, 0x30
	li r27, 0x4
	b L_af_49
L_af_50:
	li r26, 0xc0
	li r27, 0x6
L_af_49:
	srawi r10, r10, 2
	addi r9, r1, 0x8
	addze r10, r10
	clrlwi r11, r26, 24
	lbzx r9, r9, r10
	and r9, r11, r9
	sraw r9, r9, r27
	extsh r28, r9
L_af_44:
	clrlwi. r9, r28, 31
	beq L_af_51
	extsh r9, r8
	cmpw r9, r7
	beq L_af_52
	addi r8, r8, 0x1
L_af_51:
	addi r5, r5, 0x1
	bdnz L_af_38
L_af_52:
	cmpwi r5, 0x63
	bge L_af_35
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
	beq L_af_53
	subi r31, r31, 0x1
L_af_53:
	rlwinm. r0, r3, 0, 30, 30
	beq L_af_35
	subi r30, r30, 0x1
L_af_35:
	lwz r4, bdsw(r13)
	lwz r3, 0x10c(r4)
	lwz r0, 0x110(r4)
	add r0, r3, r0
	cmpw r0, r29
	blt L_af_36
	li r0, 0x5
	li r4, 0x0
	mtctr r0
L_af_54:
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
	bdnz L_af_54
	li r25, 0x0
	mr r24, r25
L_af_55:
	lwz r3, bdsw(r13)
	addi r0, r24, 0xf8
	lwzx r0, r3, r0
	cmpwi r0, 0x0
	beq L_af_56
	addi r3, r3, 0x19
	extsh r4, r0
	li r5, -0x1
	bl badgeShop_add
L_af_56:
	addi r25, r25, 0x1
	addi r24, r24, 0x4
	cmpwi r25, 0x5
	blt L_af_55
	lmw r24, 0x30(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

#pragma dont_inline on
#pragma defer_codegen off
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
#endif
		}
	}
#ifdef NONMATCHING
	return EVT_RETURN_DONE;
#endif
#ifndef NONMATCHING

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
#endif
}

#ifdef NONMATCHING
#pragma opt_common_subs reset
USER_FUNC(evt_badgeShop_throw_get_kind_cnt) {
	s32* args = event->args;
	s16 badge;
	s32 count;
	int i;
#endif
#ifndef NONMATCHING
#pragma defer_codegen reset
#pragma dont_inline reset
#endif

#ifdef NONMATCHING
	for (count = 0, i = 0; i < 99; i++) {
		badge = badgeShop_get(bdsw->bargain_table, (s16)(i + BADGE_MIN)); //inline
		if (badge > 0) {
			count++;
		}
	}
	evtSetValue(event, *args, count);
	return EVT_RETURN_DONE;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
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
	bge L_af_1
L_af_2:
	stw r5, 0x4(r6)
	stw r4, 0x0(r6)
	addi r6, r6, 0x8
	bdnz L_af_2
L_af_1:
	addi r28, r1, 0x8
	li r25, 0x0
	mr r27, r25
	li r26, 0x0
	mr r29, r28
L_af_3:
	lwz r3, bdsw(r13)
	addi r4, r3, 0x4b
	cmplw r4, r4
	beq L_af_4
	addi r0, r3, 0xa0
	cmplw r4, r0
	bne L_af_5
L_af_4:
	li r3, 0x1
	b L_af_6
L_af_5:
	li r3, 0xf0
L_af_6:
	addi r0, r27, 0x1
	extsh r0, r0
	cmpw r0, r3
	blt L_af_7
	cmpwi r0, 0x153
	blt L_af_8
L_af_7:
	li r0, 0x0
	b L_af_9
L_af_8:
	subf r0, r3, r0
	extsh r3, r0
	clrlwi r0, r3, 30
	cmpwi r0, 0x2
	beq L_af_10
	bge L_af_11
	cmpwi r0, 0x0
	beq L_af_12
	bge L_af_13
	b L_af_14
L_af_11:
	cmpwi r0, 0x4
	bge L_af_14
	b L_af_15
L_af_12:
	li r30, 0x3
	li r31, 0x0
	b L_af_14
L_af_13:
	li r30, 0xc
	li r31, 0x2
	b L_af_14
L_af_10:
	li r30, 0x30
	li r31, 0x4
	b L_af_14
L_af_15:
	li r30, 0xc0
	li r31, 0x6
L_af_14:
	srawi r0, r3, 2
	clrlwi r3, r30, 24
	addze r0, r0
	lbzx r0, r4, r0
	and r0, r3, r0
	sraw r0, r0, r31
	extsh r0, r0
L_af_9:
	mr r23, r29
	extsh r21, r0
	addi r24, r27, 0x1
	li r22, 0x0
	b L_af_16
L_af_17:
	li r3, 0x64
	bl irand
	stw r3, 0x4(r23)
	addi r26, r26, 0x1
	cmplwi r26, 0x10
	addi r23, r23, 0x8
	stwx r24, r28, r25
	addi r25, r25, 0x8
	addi r29, r29, 0x8
	bge L_af_18
	addi r22, r22, 0x1
L_af_16:
	cmpw r22, r21
	blt L_af_17
L_af_18:
	cmplwi r26, 0x10
	bge L_af_19
	addi r27, r27, 0x1
	cmpwi r27, 0x152
	blt L_af_3
L_af_19:
	lis r4, bottakuruComp@ha
	addi r3, r1, 0x8
	addi r6, r4, bottakuruComp@l
	li r5, 0x8
	li r4, 0x11
	bl qqsort
	lis r3, badge_bottakuru_table@ha
	li r24, 0x0
	addi r25, r3, badge_bottakuru_table@l
L_af_20:
	li r26, 0x0
	mr r23, r25
L_af_21:
	lwz r3, 0x0(r28)
	lwz r0, 0x0(r23)
	cmpw r3, r0
	bne L_af_22
	subis r4, r24, 0xa22
	mr r5, r26
	li r3, 0x0
	addi r4, r4, 0x1f6
	bl evtSetValue
L_af_22:
	addi r26, r26, 0x1
	addi r23, r23, 0x4
	cmplwi r26, 0x11
	blt L_af_21
	addi r24, r24, 0x1
	addi r28, r28, 0x8
	cmpwi r24, 0x4
	blt L_af_20
	lmw r21, 0x94(r1)
	lwz r0, 0xc4(r1)
	mtlr r0
	addi r1, r1, 0xc0
	blr
#endif
}

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
#endif
#ifndef NONMATCHING
s32 getBadgeBottakuru100TableMaxCount(void) {
	return (sizeof(badge_bottakuru100_table) / sizeof(s32)) - 1;
#endif
}

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
#endif
#ifndef NONMATCHING
s32 getBadgeStarmaniacTableMaxCount(void) {
	return (sizeof(badge_starmaniac_table) / sizeof(s32)) - 1;
#endif
}

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
#endif
#ifndef NONMATCHING
s32 getBadgeBteresaTableMaxCount(void) {
	return ((sizeof(badge_bteresa_table) / sizeof(s32)) - 1) +
		((sizeof(badge_bteresa_table_card_special) / sizeof(s32)) - 1) +
		((sizeof(badge_bteresa_table_card_silver) / sizeof(s32)) - 1) +
		((sizeof(badge_bteresa_table_card_gold) / sizeof(s32)) - 1) +
		((sizeof(badge_bteresa_table_card_platinum) / sizeof(s32)) - 1);
#endif
}

#ifdef NONMATCHING
USER_FUNC(evt_badgeShop_bteresa_get_kind_cnt) {
	s32* args = event->args;
	s16 badge;
	s32 count;
	int i;
#endif
#ifndef NONMATCHING
#pragma dont_inline on
void badgeShop_init(void) {
	s32* ptr;
#endif

#ifdef NONMATCHING
	for (count = 0, i = 0; i < BADGE_MAX - 1; i++) {
		badge = badgeShop_get(bdsw->bteresa_table, (s16)(i + KEY_ITEM_MIN));
		if (badge > 0) { //TODO: wonky cntlzw
			count++;
		}
#endif
#ifndef NONMATCHING
	bdsw = &badgeshopwork;
	memset(bdsw->special_table, 0, sizeof(bdsw->special_table));
	memset(bdsw->bargain_table, 0, sizeof(bdsw->bargain_table));
	memset(bdsw->starmaniac_table, 0, sizeof(bdsw->starmaniac_table));
	memset(bdsw->bottakuru_table, 0, sizeof(bdsw->bottakuru_table));
	memset(bdsw->bteresa_table, 0, sizeof(bdsw->bteresa_table));
	bdsw->restockFlags = 1;

	for (ptr = badge_special_table; *ptr; ++ptr) {
		badgeShop_add(bdsw->special_table, (s16)*ptr, 1);
#endif
	}
#ifdef NONMATCHING
	evtSetValue(event, *args, count);
	return EVT_RETURN_DONE;
#endif
#ifndef NONMATCHING
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
#endif
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifdef NONMATCHING
s32 badgeShop_ThrowCheck(s32 itemId) {
	int i;
	s32 count;
#endif
#ifndef NONMATCHING
s32 bottakuruComp(const void** sortA, const void** sortB) {
	s32 a, b;
#endif

#ifdef NONMATCHING
	for (count = 0, i = 0; i < bdsw->bargainNum; i++) {
		if (itemId == bdsw->bargainBadges[i + bdsw->bargainNum]) {
			count++;
		}
#endif
#ifndef NONMATCHING
	a = (s32)sortA[1];
	b = (s32)sortB[1];
	if (a < b) {
		return -1;
#endif
	}
#ifdef NONMATCHING
	return count;
}

s32 U_badgeShop_SpecialCheck(void) {
	s32 count;
	int i;

	for (count = 0, i = 0; i < 5; i++) {
		if (bdsw->bargainBadges[i]) {
			count++;
		}
	}
	return count;
#endif
#ifndef NONMATCHING
	return a > b;
#endif
}


#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on


#endif