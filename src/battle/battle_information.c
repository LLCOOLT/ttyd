#include "battle/battle_information.h"
#include "battle/battle.h"
#include "evt/evt_cmd.h"
#include "evt/evt_lottery.h"
#include "mario/mario_pouch.h"
#include "system.h"

void BattleInformationSetMode(FieldBattleInfo* info, u32 mode) {
	info->mode = mode;
}

void BattleInformationSetParty(FieldBattleInfo* info, BattleUnitType party) {
	info->party = party;
}

void BattleInformationSetFirstAttack(FieldBattleInfo* info, u32 partyId) {
	info->partyId = partyId;
}

void BattleInformationInit(FieldBattleInfo* info) {
	BattleInformationSetMode(info, 0);
	BattleInformationSetParty(info, 0);
	BattleInformationSetFirstAttack(info, 0);
	BattleInformationSetResult(info, 0);
	info->setup = NULL;
	info->field_0x14 = 0;
	info->field_0x18 = 0;
	info->ruleKeepResult = 0;
	info->field_0x1A = 0;
	info->field_0x1B = 0;
}

void BattleInfomationSetBattleSetupInfo(FieldBattleInfo* info, NpcBattleInfo* setup) {
	info->setup = setup;
}

void BattleInformationSetResult(FieldBattleInfo* info, u32 result) {
	info->result = result;
}

s32 BattleInformationGetResult(FieldBattleInfo* info) {
	return info->result;
}
typedef struct ItemHogTable {
	ItemType items[20];
} ItemHogTable;

const ItemHogTable N_item_hog_table = {
	{0x98, 0x98, 0x98, 0xA2, 0x94, 0x9A, 0x99, 0x84, 0x87, 0x8B}
};

void BattleInformationSetDropMaterial(FieldBattleInfo* info) {
	NpcBattleInfo* setup = info->setup;
	BattleGroupSetup* group = setup->groupSetup;
	PointDropData* hp = group->hpDropTable;
	PointDropData* fp = group->fpDropTable;
	BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);
	s32 pct;
	s32 n;
	s32 held, random, none;
	s32 type;
	s32 r;
	s32 i;
	ItemDropData* drop;
	ItemHogTable hog;

	pct = mario->currentHp * 100 / mario->maxHp;
	if (pct > 100) {
		pct = 100;
	}
	setup->heartsDropped = 0;
	for (; hp->maxStatPercent; hp++) {
		if (pct <= hp->maxStatPercent) {
			if (irand(100) < hp->overallDropChance) {
				for (n = hp->numDrops; n != 0; n--) {
					if (irand(100) < hp->dropChance) {
						setup->heartsDropped++;
					}
				}
			}
			break;
		}
	}

	pct = mario->currentFp * 100 / mario->maxFp;
	if (pct > 100) {
		pct = 100;
	}
	setup->flowersDropped = 0;
	for (; fp->maxStatPercent; fp++) {
		if (pct <= fp->maxStatPercent) {
			if (irand(100) < fp->overallDropChance) {
				for (n = fp->numDrops; n != 0; n--) {
					if (irand(100) < fp->dropChance) {
						setup->flowersDropped++;
					}
				}
			}
			break;
		}
	}

	held = group->heldItemWeight;
	random = group->randomItemWeight;
	none = group->noItemWeight;
	type = 0;
	if (evtGetValue(NULL, GSW(0)) < 20) {
		random = 0;
		held = 0;
		none = 100;
	}
	n = pouchEquipCheckBadge(ITEM_ITEM_HOG);
	if (n >= 1) {
		held *= n + 1;
		random *= n + 1;
	}
	r = irand(random + (held + none));
	if ((r -= random) < 0) {
		type = 1;
	} else if ((r -= held) < 0) {
		type = 2;
	}
	setup->itemDropped = 0;
	switch (type) {
		case 1:
			drop = group->enemyData->itemDropTable;
			if (drop) {
				r = 0;
				for (i = 0; drop[i].dropWeight > 0 || drop[i].type != 0; i++) {
					r += drop[i].dropWeight;
				}
				if (r > 0) {
					r = irand(r);
					for (;; drop++) {
						if ((r -= drop->dropWeight) < 0) {
							setup->itemDropped = drop->type;
							break;
						}
					}
				}
			}
			break;
		case 2:
			n = 0;
			for (i = 0; i < 8; i++) {
				if (setup->heldItems[i]) {
					n++;
				}
			}
			if (n > 0) {
				r = irand(n);
				for (i = 0; i < 8; i++) {
					if (setup->heldItems[i] && --r < 0) {
						setup->itemDropped = setup->heldItems[i];
						break;
					}
				}
				if (i >= 8) {
					setup->itemDropped = 0;
				}
			} else if (pouchEquipCheckBadge(ITEM_ITEM_HOG) >= 1) {
				hog = N_item_hog_table;
				setup->itemDropped = hog.items[irand(20)];
			}
			break;
	}
}
