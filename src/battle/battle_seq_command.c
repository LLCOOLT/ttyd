#pragma optimize_for_size on
#include "battle/battle_seq_command.h"
#include "battle/battle.h"
#include "battle/battle_monosiri.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/msgdrv.h"
#include "driver/npcdrv.h"
#include "mario/mario_pouch.h"
#include "data/item_data.h"

//TODO: move into battle/seq/?

//local prototypes
extern ItemData itemDataTable[];
extern BattleWeapon badgeWeapon_2KaiItem;
extern BattleWeapon badgeWeapon_3KaiItem;
extern BattleWeapon marioDefaultWeapon_Jump;
extern BattleWeapon marioWeapon_KururinJump;
extern BattleWeapon marioWeapon_JyabaraJump;
extern BattleWeapon marioDefaultWeapon_Hammer;
extern BattleWeapon marioWeapon_KaitenHammer;
extern BattleWeapon marioWeapon_UltraHammer;
extern BattleWeapon ItemWeaponData_CookingItem;
extern BattleWeapon* superActionTable[];
extern BattleWeapon badgeWeapon_Charge;
extern BattleWeapon badgeWeapon_ChargeP;
extern BattleWeapon badgeWeapon_SuperCharge;
extern BattleWeapon badgeWeapon_SuperChargeP;
BOOL BtlUnit_CanActStatus(BattleUnit* unit);
s32 BtlUnit_GetWeaponCost(BattleUnit* unit, BattleWeapon* weapon);
s32 BtlUnit_CheckWeaponCost(BattleUnit* unit, BattleWeapon* weapon);
void BattleSamplingEnemy(BattleWorkWeaponTargets* targets, BattleWeapon* weapon, s32 unitId, s8 belong, u32 classFlags, u32 propFlags, s8 direction);
void BattleDrawEnemyHP(CameraId camId, void* param);
s32 _btlcmd_CheckWeaponTargetNum(BattleWork* wp, BattleUnit* unit, BattleWeapon* weapon);

typedef struct BattleCheckPartyEntry {
	s32 kind;          // 0x0
	const char* name;  // 0x4
	u16 icon;          // 0x8
	const char* help;  // 0xC
} BattleCheckPartyEntry;

BattleCheckPartyEntry _checkPartyTable[8] = {
	{0, NULL, 0, NULL},
	{UNIT_GOOMBELLA, "btl_cmd_pt_christine", 0x155, "btl_hlp_cmd_operation_party1"},
	{UNIT_KOOPS, "btl_cmd_pt_nokotarou", 0x156, "btl_hlp_cmd_operation_party2"},
	{UNIT_FLURRIE, "btl_cmd_pt_clauda", 0x15F, "btl_hlp_cmd_operation_party3"},
	{UNIT_YOSHI, "btl_cmd_pt_yoshi", 0x158, "btl_hlp_cmd_operation_party4"},
	{UNIT_VIVIAN, "btl_cmd_pt_vivian", 0x160, "btl_hlp_cmd_operation_party5"},
	{UNIT_BOBBERY, "btl_cmd_pt_sanders", 0x157, "btl_hlp_cmd_operation_party6"},
	{UNIT_MS_MOWZ, "btl_cmd_pt_chuchurina", 0x161, "btl_hlp_cmd_operation_party7"},
};

void _btlcmd_GetCursorPtr(BattleCommand* cmd, u32 type, BattleCursor** out);
u16 _battleGetPartyIcon(s32 kind);
s32 _btlcmd_MakePartyTable(BattleWork* wp);
s32 _btlcmd_MakeSelectWeaponTable(BattleWork* wp, s32 type);
void _btlcmd_UpdateSelectWeaponTable(BattleWork* wp, s32 type);
s32 _getJumpIconId(void);
s32 _getHammerIconId(void);

s32 _jump_badge_table[8] = {0xF0, 0xF1, 0xF4, 0xF5, 0xF6, 0xF3, 0xF2, 0x14C};
s32 _hammer_badge_table[9] = {0xF7, 0xFA, 0xF9, 0xFB, 0xFD, 0xFC, 0xF8, 0x14D, 0x14E};

void BattleCommandInit(BattleWork* wp) {
	wp->commandMenu.unk0 = 0;
	wp->flags |= 0x80;
}

void _btlcmd_MakeActClassTable(BattleWork* wp) {
	PouchData* pouch;
	BattleUnit* unit;
	BattleCommand* cmd;
	BattleCursor* cursor;
	s32 num;
	NpcBattleInfo* info;

	unit = BattleGetUnitPtr(wp, wp->activeUnitId);
	cmd = &wp->commandMenu;
	pouch = pouchGetPtr();
	info = wp->fbatInfo->setup;
	if (cmd == NULL) {
		return;
	}
	if (unit->currentKind == UNIT_MARIO) {
		cursor = &cmd->cursor[0];
	} else {
		cursor = &cmd->cursor[1];
	}
	num = 0;
	if (unit->currentKind == UNIT_MARIO) {
		cmd->act[0].type = 0;
		cmd->act[0].enabled = 1;
		cmd->act[0].disableReason = 0;
		if (unit->mAttributeFlags & 0x10) {
			cmd->act[0].enabled = 0;
			cmd->act[0].disableReason = 3;
		}
		if (pouch->jumpLevel < 1) {
			cmd->act[0].enabled = 0;
		}
		if (unit->badgesEquipped.Hammerman) {
			cmd->act[0].enabled = 0;
			cmd->act[0].disableReason = 3;
		}
		if (wp->commandDisabled[0] > 0) {
			cmd->act[0].enabled = 0;
			cmd->act[0].disableReason = 3;
		}
		if (info->field_4 & 0x1000000) {
			cmd->act[0].enabled = 0;
			cmd->act[0].disableReason = 3;
		}
		if (wp->flags & 0x6800000) {
			cmd->act[0].enabled = 0;
			cmd->act[0].disableReason = 3;
		}
		cmd->act[0].name = msgSearch("btl_cmd_act_jump");
		switch (pouch->jumpLevel) {
			case 1:
				cmd->act[0].icon = 0x146;
				break;
			case 2:
				cmd->act[0].icon = 0x147;
				break;
			default:
				cmd->act[0].icon = 0x148;
				break;
		}
		num = 1;
	}
	if (unit->currentKind >= TYPE_PARTNER_MIN && unit->currentKind < TYPE_PARTNER_MAX) {
		cmd->act[num].type = 6;
		if (unit->flippedTurns) {
			cmd->act[num].enabled = 0;
			cmd->act[num].disableReason = 3;
		} else {
			cmd->act[num].enabled = 1;
			cmd->act[num].disableReason = 0;
		}
		if (wp->commandDisabled[3] > 0) {
			cmd->act[num].enabled = 0;
			cmd->act[num].disableReason = 3;
		}
		if (wp->flags & 0x4800000) {
			cmd->act[num].enabled = 0;
			cmd->act[num].disableReason = 3;
		}
		cmd->act[num].name = msgSearch("btl_cmd_act_tech_party");
		cmd->act[num].icon = 0x14F;
		num++;
	}
	if (unit->currentKind == UNIT_MARIO && pouch->hammerLevel >= 1) {
		cmd->act[num].type = 1;
		cmd->act[num].enabled = 1;
		cmd->act[num].disableReason = 0;
		if (unit->mAttributeFlags & 0x10) {
			cmd->act[num].enabled = 0;
			cmd->act[num].disableReason = 3;
		}
		if (pouch->hammerLevel < 1) {
			cmd->act[num].enabled = 0;
		}
		if (unit->badgesEquipped.Jumpman) {
			cmd->act[num].enabled = 0;
			cmd->act[num].disableReason = 3;
		}
		if (wp->commandDisabled[1] > 0) {
			cmd->act[num].enabled = 0;
			cmd->act[num].disableReason = 3;
		}
		if (info->field_4 & 0x2000000) {
			cmd->act[num].enabled = 0;
			cmd->act[num].disableReason = 3;
		}
		if (wp->flags & 0x5800000) {
			cmd->act[num].enabled = 0;
			cmd->act[num].disableReason = 3;
		}
		cmd->act[num].name = msgSearch("btl_cmd_act_hammer");
		switch (pouch->hammerLevel) {
			case 1:
				cmd->act[num].icon = 0x149;
				break;
			case 2:
				cmd->act[num].icon = 0x14A;
				break;
			default:
				cmd->act[num].icon = 0x14B;
				break;
		}
		num++;
	}
	if (unit->currentKind == UNIT_MARIO || (unit->currentKind >= TYPE_PARTNER_MIN && unit->currentKind < TYPE_PARTNER_MAX)) {
		cmd->act[num].type = 2;
		if (unit->flippedTurns) {
			cmd->act[num].enabled = 0;
			cmd->act[num].disableReason = 3;
		} else {
			cmd->act[num].enabled = 1;
			cmd->act[num].disableReason = 0;
		}
		if (unit->currentKind == UNIT_MARIO) {
			if (wp->commandDisabled[2] > 0) {
				cmd->act[num].enabled = 0;
				cmd->act[num].disableReason = 3;
			}
		} else {
			if (wp->commandDisabled[4] > 0) {
				cmd->act[num].enabled = 0;
				cmd->act[num].disableReason = 3;
			}
		}
		if (wp->flags & 0x1F800000) {
			cmd->act[num].enabled = 0;
			cmd->act[num].disableReason = 3;
		}
		cmd->act[num].name = msgSearch("btl_cmd_act_item");
		cmd->act[num].icon = 0x14C;
		num++;
	}
	if (unit->currentKind == UNIT_MARIO && *(u16*)&pouch->mStarPowersObtained != 0) {
		cmd->act[num].type = 4;
		cmd->act[num].enabled = 1;
		cmd->act[num].disableReason = 0;
		if (unit->mAttributeFlags & 0x10) {
			cmd->act[num].enabled = 0;
			cmd->act[num].disableReason = 3;
		}
		if (wp->flags & 0x1B800000) {
			cmd->act[num].enabled = 0;
			cmd->act[num].disableReason = 3;
		}
		cmd->act[num].name = msgSearch("btl_cmd_act_super_action");
		cmd->act[num].icon = 0x14D;
		num++;
	}
	if (!(wp->flags & 0x8000000)) {
		cmd->act[num].type = 5;
		cmd->act[num].enabled = 1;
		cmd->act[num].disableReason = 0;
		if (wp->flags & 0x1F800000) {
			cmd->act[num].enabled = 0;
			cmd->act[num].disableReason = 3;
		}
		cmd->act[num].name = msgSearch("btl_cmd_act_operation");
		cmd->act[num].icon = 0x14E;
		num++;
	}
	if (wp->flags & 0x8000000) {
		cmd->act[num].type = 0xD;
		cmd->act[num].enabled = 1;
		cmd->act[num].disableReason = 0;
		cmd->act[num].name = msgSearch("btl_cmd_act_lecture_end");
		cmd->act[num].icon = 0x14E;
		if (wp->flags & 0x10800000) {
			cmd->act[num].enabled = 0;
			cmd->act[num].disableReason = 3;
		}
		num++;
	}
	cursor->unk8 = num;
	if (cursor->field_0 >= cursor->unk8) {
		cursor->field_0 = cursor->unk8 - 1;
	}
}

void _btlcmd_GetCursorPtr(BattleCommand* cmd, u32 type, BattleCursor** out) {
	BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, _battleWorkPointer->activeUnitId);

	switch (type) {
		case 14:
			if (unit->currentKind == UNIT_MARIO) {
				*out = &cmd->cursor[0];
			} else {
				*out = &cmd->cursor[1];
			}
			break;
		case 0:
			*out = &cmd->cursor[2];
			break;
		case 1:
			*out = &cmd->cursor[3];
			break;
		case 2:
			*out = &cmd->cursor[11];
			break;
		case 3:
			*out = &cmd->cursor[12];
			break;
		case 4:
			*out = &cmd->cursor[7];
			break;
		case 5:
			if (unit->currentKind == UNIT_MARIO) {
				*out = &cmd->cursor[8];
			} else {
				*out = &cmd->cursor[9];
			}
			break;
		case 6:
			*out = &cmd->cursor[4];
			break;
		case 7:
			*out = &cmd->cursor[5];
			break;
		case 8:
			*out = &cmd->cursor[6];
			break;
		case 10:
			*out = &cmd->cursor[10];
			break;
	}
}

#pragma dont_inline on
s32 _getJumpIconId(void) {
	switch (pouchGetPtr()->jumpLevel) {
		case 3:
			return 0xA1;
		case 2:
			return 0xA0;
		default:
			return 0x9F;
	}
}
#pragma dont_inline reset

#pragma dont_inline on
s32 _getHammerIconId(void) {
	switch (pouchGetPtr()->hammerLevel) {
		case 3:
			return 0x9E;
		case 2:
			return 0x9D;
		default:
			return 0x9C;
	}
}
#pragma dont_inline reset

s32 _btlcmd_MakeSelectWeaponTable(BattleWork* wp, s32 type) {
	BattleUnit* unit;
	BattleCommand* cmd;
	PouchData* pouch;
	BattleCursor* cursor;
	s32 num;
	s32 badge;
	u32 i;
	u32 k;
	s32 badge2;
	s32 j;
	s16* items;
	void (*func)(BattleCommand*, s32*);
	static BattleWeapon defaultWeapon_Dummy_NoItem = {
		"btl_wn_dummy_noitem", 0, {0}, 0, "msg_dummy_noitem", 100, 0, 0, 0, 0.0f, 0, 0, 0, 0,
		NULL, {0}, NULL, {0}, 0x01000160, 0x20000002, 0, 0, 3, 2, NULL, 0,
		{0, 0, 0, 0, 0x80, 0x00, 0x20, 0x00}, 0, 0, 0, 0, {0}, 0, {0}, 0, 0, 0, 0, {0}, NULL, {0, 0, 0, 100}
	};

	unit = BattleGetUnitPtr(wp, wp->activeUnitId);
	cmd = &wp->commandMenu;
	pouch = pouchGetPtr();
	if (cmd == NULL) {
		return 0;
	}
	_btlcmd_GetCursorPtr(cmd, type, &cursor);
	num = 0;
	switch (type) {
		case 0:
			if (pouch->jumpLevel >= 1) {
				cmd->weapon[num].index = -1;
				cmd->weapon[num].itemId = 0;
				cmd->weapon[num].weapon = &marioDefaultWeapon_Jump;
				cmd->weapon[num].enabled = 0;
				cmd->weapon[num].disableReason = 0;
				cmd->weapon[num].icon = _getJumpIconId();
				if (cmd->weapon[num].weapon->name) {
					cmd->weapon[num].name = msgSearch(cmd->weapon[num].weapon->name);
				} else {
					cmd->weapon[num].name = msgSearch(itemDataTable[cmd->weapon[num].weapon->itemId].name);
				}
				if (wp->flags & 0x9000000 && wp->field_424 != -1) {
					cmd->weapon[num].weapon = BtlUnit_GetData(BattleGetUnitPtr(wp, wp->field_424), 0x44);
				}
				num++;
			}
			if (pouch->jumpLevel >= 2) {
				cmd->weapon[num].index = -1;
				cmd->weapon[num].itemId = 0;
				cmd->weapon[num].weapon = &marioWeapon_KururinJump;
				cmd->weapon[num].enabled = 0;
				cmd->weapon[num].disableReason = 0;
				cmd->weapon[num].icon = _getJumpIconId();
				if (cmd->weapon[num].weapon->name) {
					cmd->weapon[num].name = msgSearch(cmd->weapon[num].weapon->name);
				} else {
					cmd->weapon[num].name = msgSearch(itemDataTable[cmd->weapon[num].weapon->itemId].name);
				}
				num++;
			}
			if (pouch->jumpLevel >= 3) {
				cmd->weapon[num].index = -1;
				cmd->weapon[num].itemId = 0;
				cmd->weapon[num].weapon = &marioWeapon_JyabaraJump;
				cmd->weapon[num].enabled = 0;
				cmd->weapon[num].disableReason = 0;
				cmd->weapon[num].icon = _getJumpIconId();
				if (cmd->weapon[num].weapon->name) {
					cmd->weapon[num].name = msgSearch(cmd->weapon[num].weapon->name);
				} else {
					cmd->weapon[num].name = msgSearch(itemDataTable[cmd->weapon[num].weapon->itemId].name);
				}
				num++;
			}
			break;
		case 1:
			if (pouch->hammerLevel >= 1) {
				cmd->weapon[num].index = -1;
				cmd->weapon[num].itemId = 0;
				cmd->weapon[num].weapon = &marioDefaultWeapon_Hammer;
				cmd->weapon[num].enabled = 0;
				cmd->weapon[num].disableReason = 0;
				cmd->weapon[num].icon = _getHammerIconId();
				if (cmd->weapon[num].weapon->name) {
					cmd->weapon[num].name = msgSearch(cmd->weapon[num].weapon->name);
				} else {
					cmd->weapon[num].name = msgSearch(itemDataTable[cmd->weapon[num].weapon->itemId].name);
				}
				if (wp->flags & 0xA000000 && wp->field_424 != -1) {
					cmd->weapon[num].weapon = BtlUnit_GetData(BattleGetUnitPtr(wp, wp->field_424), 0x45);
				}
				num++;
			}
			if (pouch->hammerLevel >= 2) {
				cmd->weapon[num].index = -1;
				cmd->weapon[num].itemId = 0;
				cmd->weapon[num].weapon = &marioWeapon_KaitenHammer;
				cmd->weapon[num].enabled = 0;
				cmd->weapon[num].disableReason = 0;
				cmd->weapon[num].icon = _getHammerIconId();
				if (cmd->weapon[num].weapon->name) {
					cmd->weapon[num].name = msgSearch(cmd->weapon[num].weapon->name);
				} else {
					cmd->weapon[num].name = msgSearch(itemDataTable[cmd->weapon[num].weapon->itemId].name);
				}
				num++;
			}
			if (pouch->hammerLevel >= 3) {
				cmd->weapon[num].index = -1;
				cmd->weapon[num].itemId = 0;
				cmd->weapon[num].weapon = &marioWeapon_UltraHammer;
				cmd->weapon[num].enabled = 0;
				cmd->weapon[num].disableReason = 0;
				cmd->weapon[num].icon = _getHammerIconId();
				if (cmd->weapon[num].weapon->name) {
					cmd->weapon[num].name = msgSearch(cmd->weapon[num].weapon->name);
				} else {
					cmd->weapon[num].name = msgSearch(itemDataTable[cmd->weapon[num].weapon->itemId].name);
				}
				num++;
			}
			break;
	}
	switch (type) {
		case 0:
			for (i = 0; i < 8; i++) {
				badge = _jump_badge_table[i];
				if (pouchEquipCheckBadge(badge) > 0) {
					cmd->weapon[num].index = i;
					cmd->weapon[num].itemId = badge;
					cmd->weapon[num].weapon = itemDataTable[badge].battle_params;
					cmd->weapon[num].enabled = 0;
					cmd->weapon[num].disableReason = 0;
					if (cmd->weapon[num].weapon->itemId) {
						cmd->weapon[num].icon = itemDataTable[badge].icon_id;
					} else {
						cmd->weapon[num].icon = cmd->weapon[num].weapon->icon;
					}
					if (cmd->weapon[num].weapon->name) {
						cmd->weapon[num].name = msgSearch(cmd->weapon[num].weapon->name);
					} else {
						cmd->weapon[num].name = msgSearch(itemDataTable[cmd->weapon[num].weapon->itemId].name);
					}
					num++;
				}
			}
			break;
		case 1:
			for (k = 0; k < 9; k++) {
				badge2 = _hammer_badge_table[k];
				if (pouchEquipCheckBadge(badge2) > 0) {
					cmd->weapon[num].index = k;
					cmd->weapon[num].itemId = badge2;
					cmd->weapon[num].weapon = itemDataTable[badge2].battle_params;
					cmd->weapon[num].enabled = 0;
					cmd->weapon[num].disableReason = 0;
					if (cmd->weapon[num].weapon->itemId) {
						cmd->weapon[num].icon = itemDataTable[badge2].icon_id;
					} else {
						cmd->weapon[num].icon = cmd->weapon[num].weapon->icon;
					}
					if (cmd->weapon[num].weapon->name) {
						cmd->weapon[num].name = msgSearch(cmd->weapon[num].weapon->name);
					} else {
						cmd->weapon[num].name = msgSearch(itemDataTable[cmd->weapon[num].weapon->itemId].name);
					}
					num++;
				}
			}
			break;
	}
	switch (type) {
		case 6:
			func = (void (*)(BattleCommand*, s32*))BtlUnit_GetData(unit, 1);
			func(cmd, &num);
			break;
		case 2:
			items = pouch->heldItems;
			for (j = 0; j < 20; j++) {
				s32 id = items[j];
				ItemData* data = &itemDataTable[id];
				if (id != 0 && (*(u16*)&data->usable_locations & 2)) {
					cmd->weapon[num].index = j;
					cmd->weapon[num].itemId = id;
					cmd->weapon[num].weapon = data->battle_params;
					cmd->weapon[num].enabled = 0;
					cmd->weapon[num].disableReason = 0;
					if (cmd->weapon[num].weapon == NULL) {
						cmd->weapon[num].weapon = &ItemWeaponData_CookingItem;
						cmd->weapon[num].name = msgSearch(data->name);
						cmd->weapon[num].icon = data->icon_id;
					} else {
						cmd->weapon[num].icon = data->icon_id;
						if (cmd->weapon[num].weapon->name) {
							cmd->weapon[num].name = msgSearch(cmd->weapon[num].weapon->name);
						} else {
							cmd->weapon[num].name = msgSearch(itemDataTable[cmd->weapon[num].weapon->itemId].name);
						}
					}
					if (++num >= 21) {
						break;
					}
				}
			}
			if (num == 0) {
				cmd->weapon[num].index = -1;
				cmd->weapon[num].itemId = 0;
				cmd->weapon[num].index = 0;
				cmd->weapon[num].weapon = &defaultWeapon_Dummy_NoItem;
				cmd->weapon[num].enabled = 0;
				cmd->weapon[num].disableReason = 0;
				cmd->weapon[num].icon = 0x162;
				if (cmd->weapon[num].weapon->name) {
					cmd->weapon[num].name = msgSearch(cmd->weapon[num].weapon->name);
				} else {
					cmd->weapon[num].name = msgSearch(itemDataTable[cmd->weapon[num].weapon->itemId].name);
				}
				num++;
			}
			break;
		case 4: {
			u16 starPowers = *(u16*)&pouch->mStarPowersObtained;
			for (j = 0; j < 16; j++) {
				if ((starPowers & (1 << j)) && superActionTable[j]) {
					cmd->weapon[num].index = -1;
					cmd->weapon[num].itemId = 0;
					cmd->weapon[num].weapon = superActionTable[j];
					cmd->weapon[num].enabled = 0;
					cmd->weapon[num].icon = superActionTable[j]->icon;
					cmd->weapon[num].disableReason = 0;
					if (cmd->weapon[num].weapon->name) {
						cmd->weapon[num].name = msgSearch(cmd->weapon[num].weapon->name);
					} else {
						cmd->weapon[num].name = msgSearch(itemDataTable[cmd->weapon[num].weapon->itemId].name);
					}
					if (++num >= 21) {
						break;
					}
				}
			}
			break;
		}
	}
	if (num <= 0) {
		return 0;
	}
	cursor->unk8 = num;
	if (cursor->field_0 >= cursor->unk8) {
		cursor->field_0 = cursor->unk8 - 1;
	}
	while (cursor->unk8 < cursor->field_4 + 6) { if (cursor->field_4 <= 0) break; cursor->field_4--; }
	_btlcmd_UpdateSelectWeaponTable(wp, type);
	return num;
}

void _btlcmd_UpdateSelectWeaponTable(BattleWork* wp, s32 type) {
	BattleUnit* unit;
	BattleCommand* cmd;
	BattleCursor* cursor;
	s32 i;
	s32 n;
	s32 result;
	BattleWeapon* weapon;

	unit = BattleGetUnitPtr(wp, wp->activeUnitId);
	cmd = &wp->commandMenu;
	_btlcmd_GetCursorPtr(cmd, type, &cursor);
	n = cursor->unk8;
	for (i = 0; i < n; i++) {
		weapon = cmd->weapon[i].weapon;
		cmd->weapon[i].enabled = 0;
		cmd->weapon[i].disableReason = 0;
		if (weapon) {
			result = _btlcmd_CheckWeaponTargetNum(wp, unit, weapon);
			if (result <= 0) {
				if (result == 0) {
					switch (type) {
						case 0:
							cmd->weapon[i].disableReason = 4;
							break;
						case 1:
							cmd->weapon[i].disableReason = 5;
							break;
						default:
							cmd->weapon[i].disableReason = 3;
							break;
					}
				} else if (type != 4) {
					cmd->weapon[i].disableReason = 1;
				} else {
					cmd->weapon[i].disableReason = 2;
				}
			} else {
				cmd->weapon[i].enabled = 1;
				cmd->weapon[i].disableReason = 0;
			}
		}
	}
}

s32 _btlcmd_CheckWeaponTargetNum(BattleWork* wp, BattleUnit* unit, BattleWeapon* weapon) {
	BattleWorkWeaponTargets targets;

	if (weapon == NULL) {
		return 0;
	}
	if (weapon->mAttackEvtScript == NULL) {
		return 0;
	}
	if (!BtlUnit_CheckWeaponCost(unit, weapon)) {
		return -1;
	}
	{
		s32 belong = BtlUnit_GetEnemyBelong(unit);
		BattleSamplingEnemy(&targets, weapon, unit->unitId, belong, weapon->targetClassFlags,
			weapon->targetPropertyFlags, -wp->alliances[belong].attackDirection);
	}
	return targets.numTargets;
}

void _btlcmd_MakeOperationTable(BattleWork* wp) {
	PouchData* pouch;
	NpcBattleInfo* info;
	BattleUnit* unit;
	BattleCommand* cmd;
	s32 num;
	BattleUnit* party;
	BattleCursor* cursor;
	BattleWeapon* weapon;
	s32 idx;

	unit = BattleGetUnitPtr(wp, wp->activeUnitId);
	info = wp->fbatInfo->setup;
	cmd = &wp->commandMenu;
	pouch = pouchGetPtr();
	if (cmd == NULL) {
		return;
	}
	_btlcmd_GetCursorPtr(cmd, 5, &cursor);
	num = 0;
	if (_btlcmd_MakePartyTable(wp) >= 2) {
		cmd->operation[0].type = 0;
		if (unit->flippedTurns) {
			cmd->operation[0].enabled = 0;
			cmd->operation[0].disableReason = 3;
		} else {
			cmd->operation[0].enabled = 1;
			cmd->operation[0].disableReason = 0;
		}
		cmd->operation[0].name = msgSearch("btl_cmd_op_chg_party");
		party = unit;
		if (!(unit->currentKind >= TYPE_PARTNER_MIN && unit->currentKind < TYPE_PARTNER_MAX)) {
			party = BattleGetPartnerPtr(wp, unit);
		}
		BtlUnit_CanActStatus(party);
		cmd->operation[0].icon = _battleGetPartyIcon(party->currentKind);
		cmd->operation[0].help = "btl_hlp_cmd_operation_changeparty";
		if (unit->mAttributeFlags & 0x10) {
			cmd->operation[0].enabled = 0;
			cmd->operation[0].disableReason = 3;
		}
		if (info->field_4 & 0x4000000) {
			cmd->operation[0].enabled = 0;
			cmd->operation[0].disableReason = 3;
		}
		cmd->operation[0].cost = 0;
		num = 1;
	}
	if (*(u16*)&pouch->mStarPowersObtained != 0) {
		cmd->operation[num].type = 5;
		cmd->operation[num].enabled = 1;
		cmd->operation[num].name = msgSearch("btl_cmd_op_appeal");
		cmd->operation[num].icon = 0x164;
		cmd->operation[num].disableReason = 0;
		cmd->operation[num].cost = 0;
		cmd->operation[num].help = "btl_hlp_cmd_operation_appeal";
		num++;
	}
	if (unit->badgesEquipped.Charge) {
		weapon = &badgeWeapon_ChargeP;
		if (unit->currentKind == UNIT_MARIO) {
			weapon = &badgeWeapon_Charge;
		}
		cmd->operation[num].type = 1;
		cmd->operation[num].enabled = BtlUnit_CheckWeaponCost(unit, weapon);
		cmd->operation[num].cost = BtlUnit_GetWeaponCost(unit, weapon);
		if (cmd->operation[num].enabled) {
			cmd->operation[num].disableReason = 0;
		} else {
			cmd->operation[num].disableReason = 1;
		}
		cmd->operation[num].name = msgSearch(weapon->name);
		cmd->operation[num].icon = 0x166;
		cmd->operation[num].help = weapon->description;
		if (unit->mAttributeFlags & 0x10) {
			cmd->operation[num].enabled = 0;
			cmd->operation[num].disableReason = 3;
		}
		num++;
	}
	if (unit->badgesEquipped.SuperCharge) {
		weapon = &badgeWeapon_SuperChargeP;
		if (unit->currentKind == UNIT_MARIO) {
			weapon = &badgeWeapon_SuperCharge;
		}
		cmd->operation[num].type = 2;
		cmd->operation[num].enabled = BtlUnit_CheckWeaponCost(unit, weapon);
		cmd->operation[num].cost = BtlUnit_GetWeaponCost(unit, weapon);
		if (cmd->operation[num].enabled) {
			cmd->operation[num].disableReason = 0;
		} else {
			cmd->operation[num].disableReason = 1;
		}
		cmd->operation[num].name = msgSearch(weapon->name);
		cmd->operation[num].icon = 0x167;
		cmd->operation[num].help = weapon->description;
		if (unit->mAttributeFlags & 0x10) {
			cmd->operation[num].enabled = 0;
			cmd->operation[num].disableReason = 3;
		}
		num++;
	}
	cmd->operation[num].type = 6;
	cmd->operation[num].enabled = 1;
	cmd->operation[num].name = msgSearch("btl_cmd_op_defend");
	cmd->operation[num].icon = 0x165;
	cmd->operation[num].disableReason = 0;
	cmd->operation[num].cost = 0;
	cmd->operation[num].help = "btl_hlp_cmd_operation_defend";
	if (unit->mAttributeFlags & 0x10) {
		cmd->operation[num].enabled = 0;
		cmd->operation[num].disableReason = 3;
	}
	idx = num + 1;
	cmd->operation[idx].type = 3;
	cmd->operation[idx].enabled = BtlUnit_CanActStatus(unit);
	cmd->operation[idx].name = msgSearch("btl_cmd_op_escape");
	cmd->operation[idx].icon = 0x163;
	cmd->operation[idx].cost = 0;
	if (cmd->operation[idx].enabled) {
		cmd->operation[idx].disableReason = 0;
	} else {
		cmd->operation[idx].disableReason = 1;
	}
	cmd->operation[idx].help = "btl_hlp_cmd_operation_escape";
	if (unit->mAttributeFlags & 0x10) {
		cmd->operation[idx].enabled = 0;
		cmd->operation[idx].disableReason = 3;
	}
	if (wp->fbatInfo->setup->field_4 & 0x10) {
		cmd->operation[idx].enabled = 0;
		cmd->operation[idx].disableReason = 3;
	}
	cursor->unk8 = num + 2;
	if (cursor->field_0 >= cursor->unk8) {
		cursor->field_0 = cursor->unk8 - 1;
	}
}

#pragma opt_propagation off
void _btlcmd_MakeMultiItemTable(BattleWork* wp) {
	BattleUnit* unit;
	BattleCommand* cmd;
	BattleCursor* cursor;
	s32 num;

	unit = BattleGetUnitPtr(wp, wp->activeUnitId);
	cmd = &wp->commandMenu;
	if (cmd == NULL) {
		return;
	}
	_btlcmd_GetCursorPtr(cmd, 3, &cursor);
	cmd->multiItem[0].padE[0] = 1;
	cmd->multiItem[0].enabled = 1;
	cmd->multiItem[0].name = msgSearch("btl_cmd_act_item");
	cmd->multiItem[0].icon = 0x14C;
	cmd->multiItem[0].help = NULL;
	cmd->multiItem[0].cost = 0;
	num = 1;
	if (unit->badgesEquipped.DoubleDip) {
		cmd->multiItem[num].padE[0] = 2;
		if (unit->currentKind == UNIT_MARIO) {
			cmd->multiItem[num].enabled = BtlUnit_CheckWeaponCost(unit, &badgeWeapon_2KaiItem);
			cmd->multiItem[num].name = msgSearch(itemDataTable[ITEM_DOUBLE_DIP].name);
			cmd->multiItem[num].icon = itemDataTable[ITEM_DOUBLE_DIP].icon_id;
			cmd->multiItem[num].help = itemDataTable[ITEM_DOUBLE_DIP].description;
			cmd->multiItem[num].cost = (u8)BtlUnit_GetWeaponCost(unit, &badgeWeapon_2KaiItem);
		} else {
			cmd->multiItem[num].enabled = BtlUnit_CheckWeaponCost(unit, &badgeWeapon_2KaiItem);
			cmd->multiItem[num].name = msgSearch(itemDataTable[ITEM_DOUBLE_DIP_P].name);
			cmd->multiItem[num].icon = itemDataTable[ITEM_DOUBLE_DIP_P].icon_id;
			cmd->multiItem[num].help = itemDataTable[ITEM_DOUBLE_DIP_P].description;
			cmd->multiItem[num].cost = (u8)BtlUnit_GetWeaponCost(unit, &badgeWeapon_2KaiItem);
		}
		if (cmd->multiItem[num].enabled == 0) {
			cmd->multiItem[num].disableReason = 1;
		} else {
			cmd->multiItem[num].disableReason = 0;
		}
		num++;
	}
	if (unit->badgesEquipped.TripleDip) {
		cmd->multiItem[num].padE[0] = 3;
		if (unit->currentKind == UNIT_MARIO) {
			cmd->multiItem[num].enabled = BtlUnit_CheckWeaponCost(unit, &badgeWeapon_3KaiItem);
			cmd->multiItem[num].name = msgSearch(itemDataTable[ITEM_TRIPLE_DIP].name);
			cmd->multiItem[num].icon = itemDataTable[ITEM_TRIPLE_DIP].icon_id;
			cmd->multiItem[num].help = itemDataTable[ITEM_TRIPLE_DIP].description;
			cmd->multiItem[num].cost = (u8)BtlUnit_GetWeaponCost(unit, &badgeWeapon_3KaiItem);
		} else {
			cmd->multiItem[num].enabled = BtlUnit_CheckWeaponCost(unit, &badgeWeapon_3KaiItem);
			cmd->multiItem[num].name = msgSearch("in_3kai_item_p");
			cmd->multiItem[num].icon = 0x62;
			cmd->multiItem[num].help = "msg_3kai_item_p";
			cmd->multiItem[num].cost = (u8)BtlUnit_GetWeaponCost(unit, &badgeWeapon_3KaiItem);
		}
		if (cmd->multiItem[num].enabled == 0) {
			cmd->multiItem[num].disableReason = 1;
		} else {
			cmd->multiItem[num].disableReason = 0;
		}
		num++;
	}
	cursor->unk8 = num;
	if (cursor->field_0 >= cursor->unk8) {
		cursor->field_0 = cursor->unk8 - 1;
	}
}
#pragma opt_propagation reset

#pragma dont_inline on
u16 _battleGetPartyIcon(s32 kind) {
	BattleCheckPartyEntry* entry;
	s32 i;

	for (i = 0; i < 8; i++) {
		entry = &_checkPartyTable[i + 1];
		if (entry->kind == kind) {
			if (entry->kind == UNIT_YOSHI) {
				switch (pouchGetPartyColor(4)) {
					case 1:
						return 0x159;
					case 2:
						return 0x15A;
					case 3:
						return 0x15B;
					case 4:
						return 0x15C;
					case 5:
						return 0x15D;
					case 6:
						return 0x15E;
					case 0:
					default:
						return 0x158;
				}
			}
			return entry->icon;
		}
	}
	return 0;
}
#pragma dont_inline reset

s32 _btlcmd_MakePartyTable(BattleWork* wp) {
	BattleUnit* unit;
	BattleUnit* partner;
	BattleCommand* cmd;
	s32 num;
	s32 selected;
	PouchData* pouch;
	BattleCursor* cursor;
	PouchPartyData* party;
	s32 i;
	s32 kind;

	unit = BattleGetUnitPtr(wp, wp->activeUnitId);
	partner = BattleGetPartnerPtr(wp, unit);
	cmd = &wp->commandMenu;
	num = 0;
	selected = 0;
	pouch = pouchGetPtr();
	if (cmd == NULL) {
		return 0;
	}
	if (partner == NULL) {
		return 0;
	}
	_btlcmd_GetCursorPtr(cmd, 10, &cursor);
	for (i = 0; i < 8; i++) {
		kind = _checkPartyTable[i].kind;
		if (kind == 0) {
			continue;
		}
		party = &pouch->partyData[BattleTransPartyId(kind)];
		if (!(party->flags & 1)) {
			continue;
		}
		cmd->party[num].kind = kind;
		cmd->party[num].enabled = 1;
		cmd->party[num].name = (kind == UNIT_YOSHI) ? pouchGetYoshiName() : msgSearch(_checkPartyTable[i].name);
		cmd->party[num].icon = _battleGetPartyIcon(kind);
		cmd->party[num].help = _checkPartyTable[i].help;
		cmd->party[num].hp = party->currentHP;
		cmd->party[num].maxHp = party->maximumHP;
		if (unit->currentKind == kind || kind == BattleGetPartnerPtr(wp, unit)->currentKind) {
			cmd->party[num].enabled = 0;
			selected = num;
			if (unit->currentKind == kind) {
				cmd->party[num].hp = unit->currentHp;
			} else {
				cmd->party[num].hp = partner->currentHp;
			}
		} else if (party->currentHP <= 0) {
			cmd->party[num].enabled = 0;
		}
		if (party->flags & 2) {
			cmd->party[num].enabled = 0;
		}
		num++;
	}
	cursor->unk8 = num;
	cursor->field_0 = selected;
	return num;
}

s32 _btlcmd_SelectWeaponDecide(BattleWork* wp, s32 type, s32 index) {
	BattleWorkWeaponTargets* targets;
	BattleWeapon* weapon;
	BattleUnit* unit;
	s32 selected;
	BattleWorkTarget* target;

	targets = &wp->weaponTargets;
	unit = BattleGetUnitPtr(wp, wp->activeUnitId);
	_btlcmd_MakeSelectWeaponTable(wp, type);
	weapon = wp->commandMenu.weapon[index].weapon;
	BattleSamplingEnemy(targets, weapon, wp->activeUnitId, BtlUnit_GetEnemyBelong(unit), weapon->targetClassFlags,
		weapon->targetPropertyFlags, (s32)wp->alliances[unit->mAlliance].attackDirection);
	targets->currentTarget = 0;
	if (weapon->targetPropertyFlags & 0x30000000) {
		selected = -1;
		index = BtlUnit_GetBelong(unit);
		for (type = 0; type < targets->numTargets; type++) {
			target = &targets->targets[targets->targetIndices[type]];
			if (weapon->targetPropertyFlags & 0x10000000) {
				if (index == BtlUnit_GetBelong(BattleGetUnitPtr(wp, target->unitIdx))) {
					selected = type;
				}
			} else {
				if (index != BtlUnit_GetBelong(BattleGetUnitPtr(wp, target->unitIdx))) {
					selected = type;
					break;
				}
			}
		}
		if (selected >= 0) {
			targets->currentTarget = selected;
		}
	}
	return 0;
}

void BattleDrawEnemyHP(CameraId camId, void* param) {
	BattleWork* wp = param;
	BattleUnit* unit;
	Vec position;
	int i;

	camGetPtr(CAMERA_2D); //unused, probably just stored

	for (i = 0; i < 64; i++) {
		unit = wp->units[i];
		if (unit) {
			if (!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL)) {
				if (battleCheckUnitMonosiriFlag(unit)) {
					if (!unit->mAttributeFlags & 0x2000000) {
						if (wp->commandMenu.field_4 & 0x1000000) {
							if (unit->flags & 1) {
								position.x = unit->mPosition.x;
								position.y = unit->mPosition.y;
								position.z = unit->mPosition.z;
								if (wp->flags & 0x80) {
									position.x = unit->mHomePosition.x;
									position.y = unit->mHomePosition.y;
									position.z = unit->mHomePosition.z;
								}
								position.x += (f32)unit->mHpGaugeOffset[0];
								position.y += (f32)unit->mHpGaugeOffset[1];
							}
						}
					}
				}
			}
		}
	}
}
