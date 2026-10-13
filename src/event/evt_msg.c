#include "evt/evt_msg.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "driver/windowdrv.h"
#include "driver/msgdrv.h"
#include "manager/evtmgr_cmd.h"
#include <string.h>
#include <stdio.h>

void evt_msg_init(void) {
	//stubbed in retail
}


s32 _evt_msg_print(EventEntry* event, BOOL isFirstCall, s32 a, s32 b, s32 c, s32 d);
void msgWindow_Add(const char* msg, s32 id);

#include "evt/evt_npc.h"
#include "driver/camdrv.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "party.h"
extern float __fabsf(float);

s32 msgWindow_Entry(const char* msg, s32 a2, s32 a3);
s32 BattleTransID(EventEntry* event, s32 type);
void BtlUnit_GetTalkTogePos(s32 unit, f32* x, f32* y, f32* z);

typedef struct MsgWinWork {
	u8 pad0[0x8];
	s32 type; //0x8
	u8 padC[0x28 - 0xC];
	u8** msg; //0x28
	s16 toge; //0x2C
	u8 pad2E[2];
	Vec pos; //0x30
} MsgWinWork;

s32 _evt_msg_print(EventEntry* event, BOOL isFirstCall, s32 flags, s32 msg, s32 a3, s32 name) {
	NpcEntry* npc = NULL;
	MsgWinWork* win;
	const char* m;
	if (isFirstCall) {
		if (!(flags & 1)) {
			m = msgSearch((const char*)msg);
		} else {
			m = (const char*)msg;
			msg = (s32)"DIRECT\0";
		}
		event->printWindowId = msgWindow_Entry(m, a3, (s16)event->msgPriority);
		event->msgPriority = 0;
		win = (MsgWinWork*)windowGetPointer(event->printWindowId);
		*(s32*)*win->msg = msg;
		*(EventEntry**)(*win->msg + 0x7A00) = event;
		if (!(flags & 2)) {
			if (event->wNpcEventType == 6) {
				npc = event->ownerNPC;
			}
			if ((const char*)name) {
				npc = evtNpcNameToPtr(event, (const char*)name);
			}
			if (npc == (NpcEntry*)-1) {
				if (!(event->printWindowFlags & 0x1EFFFFFF)) {
					u8* p = (u8*)partyGetPtr(marioGetPartyId());
					if (!p) {
						win->pos = *(Vec*)((u8*)marioGetPtr() + 0x8C);
						win->pos.y += *(f32*)((u8*)marioGetPtr() + 0x1B8);
					} else {
						win->pos = *(Vec*)(p + 0x58);
						win->pos.y += *(f32*)(p + 0xF0);
					}
				}
				strcpy((char*)*win->msg + 0x7A04, (const char*)name);
			} else if (npc == (NpcEntry*)-2) {
				if (!(event->printWindowFlags & 0x1EFFFFFF)) {
					u8* p = (u8*)partyGetPtr(marioGetExtraPartyId());
					if (!p) {
						win->pos = *(Vec*)((u8*)marioGetPtr() + 0x8C);
						win->pos.y += *(f32*)((u8*)marioGetPtr() + 0x1B8);
					} else {
						win->pos = *(Vec*)(p + 0x58);
						win->pos.y += *(f32*)(p + 0xF0);
					}
				}
				strcpy((char*)*win->msg + 0x7A04, (const char*)name);
			} else if (npc == (NpcEntry*)-3) {
				if (!(event->printWindowFlags & 0x1EFFFFFF)) {
					win->pos = *(Vec*)((u8*)marioGetPtr() + 0x8C);
					win->pos.y += *(f32*)((u8*)marioGetPtr() + 0x1B8);
				}
				strcpy((char*)*win->msg + 0x7A04, (const char*)name);
			} else if (npc) {
				if (!(event->printWindowFlags & 0x1EFFFFFF)) {
					win->pos = *(Vec*)((u8*)npc + 0x8C);
					win->pos.y += *(f32*)((u8*)npc + 0x150);
				}
				strcpy((char*)*win->msg + 0x7A04, (char*)npc + 8);
			}
		} else {
			*(u32*)(*win->msg + 4) |= 8;
			*(s32*)(*win->msg + 0x7A24) = BattleTransID(event, name);
			BtlUnit_GetTalkTogePos(*(s32*)(*win->msg + 0x7A24), &win->pos.x, &win->pos.y, &win->pos.z);
			win->toge = 3;
		}
		switch (event->printWindowFlags & 0x1EFFFFFF) {
			case 0:
				if (npc) {
					Vec scr, mscr;
					marioGetPtr();
					getScreenPoint(&win->pos, &scr);
					if (win->type == 1) {
						win->toge = 7;
					} else if (__fabsf(scr.x) >= 300.0f) {
						win->toge = 2;
					} else {
						getScreenPoint((Vec*)((u8*)marioGetPtr() + 0x8C), &mscr);
						if (scr.x < mscr.x) {
							win->toge = 3;
						} else {
							win->toge = 7;
						}
					}
				}
				break;
			case 1:
				win->toge = 0;
				break;
			case 2:
				win->toge = 7;
				win->pos = *(Vec*)&event->unk184;
				break;
			case 3:
				win->toge = 2;
				win->pos = *(Vec*)&event->unk184;
				break;
		}
		if (event->printWindowFlags & 0x80000000) {
			win->toge = 3;
			if (event->printWindowFlags & 0x40000000) {
				win->toge |= 4;
			}
			if (event->printWindowFlags & 0x20000000) {
				win->toge |= 8;
			}
		}
		if (event->printWindowFlags & 0x01000000) {
			win->toge |= 0x10;
		}
		event->printWindowFlags = 0;
	}
	if (windowCheckID(event->printWindowId)) {
		return EVT_RETURN_BLOCK;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_msg_print) {
	s32* args = event->args;
	s32 a = evtGetValue(event, args[0]);
	s32 b = evtGetValue(event, args[1]);
	s32 c = evtGetValue(event, args[2]);
	s32 d = evtGetValue(event, args[3]);
	return _evt_msg_print(event, isFirstCall, a, b, c, d);
}

#include "party.h"
#include "mario/mario_party.h"
#include "battle/battle.h"
#include "battle/battle_sub.h"

s32 msgWindow_Entry(const char* msg, s32 a2, s32 a3);

const char* partyMsgStr[] = {"", "_kur", "_nok", "_bom", "_yos", "_win", "_viv", "_chu", "_jug", "_tel", "_lui"};
const char* battlePartyMsgStr[] = {"_kur", "_nok", "_yos", "_win", "_viv", "_bom", "_chu"};
static const char* battlePartyMsgPad[6] = {0};

USER_FUNC(evt_msg_print_party) {
	static char partyLabel[0x40];
	s32 id;
	const char* msg = (const char*)evtGetValue(event, *event->args);
	PartyEntry* party = partyGetPtr(marioGetPartyId());
	if (party) {
		id = party->currentMemberId;
	} else {
		id = 0;
	}
	strcpy(partyLabel, msg);
	strcat(partyLabel, partyMsgStr[id]);
	return _evt_msg_print(event, isFirstCall, 0, (s32)partyLabel, 0, (s32)"party");
}

USER_FUNC(evt_msg_print_party_add) {
	static char partyLabel[0x40];
	s32 id;
	const char* msg = (const char*)evtGetValue(event, *event->args);
	PartyEntry* party = partyGetPtr(marioGetPartyId());
	if (party) {
		id = party->currentMemberId;
	} else {
		id = 0;
	}
	if (isFirstCall) {
		strcpy(partyLabel, msg);
		strcat(partyLabel, partyMsgStr[id]);
		msgWindow_Add(msgSearch(partyLabel), event->printWindowId);
	}
	if (windowCheckID(event->printWindowId)) {
		return EVT_RETURN_BLOCK;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_msg_print_battle_party) {
	static char partyLabel[0x40];
	const char* msg = (const char*)evtGetValue(event, *event->args);
	BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, BattleTransID(event, -4));
	if (!unit) {
		return EVT_RETURN_DONE;
	}
	strcpy(partyLabel, msg);
	strcat(partyLabel, battlePartyMsgStr[*(s32*)((u8*)unit + 8) - 0xE0]);
	return _evt_msg_print(event, isFirstCall, 2, (s32)partyLabel, 0, -4);
}

USER_FUNC(evt_msg_print_insert) {
	char buf[0x500];
	s32 vals[4];
	s32* p;
	s32* args = event->args;
	s32 n = (args[-2] >> 16) - 5;
	s32 flags = evtGetValue(event, *args++);
	const char* msg = (const char*)evtGetValue(event, *args++);
	s32 c, d;
	s32 i;
	c = evtGetValue(event, *args++);
	d = evtGetValue(event, *args++);
	for (i = 0, p = vals; i < n; i++) {
		*p++ = evtGetValue(event, *args++);
	}
	if (isFirstCall) {
		const char* m;
		if (flags & 1) {
			m = msg;
		} else {
			m = msgSearch(msg);
		}
		switch (n) {
			case 0: break;
			case 1: sprintf(buf, m, vals[0]); break;
			case 2: sprintf(buf, m, vals[0], vals[1]); break;
			case 3: sprintf(buf, m, vals[0], vals[1], vals[2]); break;
			case 4: sprintf(buf, m, vals[0], vals[1], vals[2], vals[3]); break;
		}
	}
	return _evt_msg_print(event, isFirstCall, flags | 1, (s32)buf, c, d);
}

USER_FUNC(evt_msg_print_add) {
	s32* args = event->args;
	s32 flags = evtGetValue(event, args[0]);
	const char* msg = (const char*)evtGetValue(event, args[1]);
	if (isFirstCall) {
		if (!(flags & 1)) {
			msgWindow_Add(msgSearch(msg), event->printWindowId);
		} else {
			msgWindow_Add(msg, event->printWindowId);
		}
	}
	if (windowCheckID(event->printWindowId)) {
		return EVT_RETURN_BLOCK;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_msg_print_add_insert) {
	char buf[0x500];
	s32 vals[4];
	s32* p;
	s32* args = event->args;
	s32 n = (args[-2] >> 16) - 3;
	s32 flags = evtGetValue(event, *args++);
	const char* msg = (const char*)evtGetValue(event, *args++);
	s32 i;
	for (i = 0, p = vals; i < n; i++) {
		*p++ = evtGetValue(event, *args++);
	}
	if (isFirstCall) {
		const char* m;
		if (flags & 1) {
			m = msg;
		} else {
			m = msgSearch(msg);
		}
		switch (n) {
			case 0: break;
			case 1: sprintf(buf, m, vals[0]); break;
			case 2: sprintf(buf, m, vals[0], vals[1]); break;
			case 3: sprintf(buf, m, vals[0], vals[1], vals[2]); break;
			case 4: sprintf(buf, m, vals[0], vals[1], vals[2], vals[3]); break;
		}
		msgWindow_Add(buf, event->printWindowId);
	}
	if (windowCheckID(event->printWindowId)) {
		return EVT_RETURN_BLOCK;
	}
	return EVT_RETURN_DONE;
}

void msgWindow_ForceClose(s32 id);
void msgWindow_Repeat(s32 id);
void msgWindow_Continue(s32 id);

USER_FUNC(evt_msg_continue) {
	if (isFirstCall) {
		msgWindow_Continue(event->printWindowId);
	}
	if (windowCheckID(event->printWindowId)) {
		return EVT_RETURN_BLOCK;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_msg_repeat) {
	if (isFirstCall) {
		msgWindow_Repeat(event->printWindowId);
	}
	if (windowCheckID(event->printWindowId)) {
		return EVT_RETURN_BLOCK;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_msg_close) {
	msgWindow_ForceClose(evtGetValue(event, *event->args));
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_msg_select) {
	s32* args = event->args;
	s32 flags = evtGetValue(event, args[0]);
	const char* msg = (const char*)evtGetValue(event, args[1]);
	if (isFirstCall) {
		const char* m;
		if (!(flags & 1)) {
			m = msgSearch(msg);
		} else {
			m = msg;
			msg = "DIRECT\0";
		}
		event->selectWindowId = msgWindow_Entry(m, 0, 0x14);
		***(const char****)((u8*)windowGetPointer(event->selectWindowId) + 0x28) = msg;
	}
	if (windowCheckID(event->selectWindowId)) {
		return EVT_RETURN_BLOCK;
	}
	event->lwData[0] = *(s8*)(**(u8***)((u8*)windowGetPointer(event->selectWindowId) + 0x28) + 0x7a43);
	windowDeleteID(event->selectWindowId);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_msg_toge) {
	s32* args = event->args;
	s32 v = evtGetValue(event, args[0]);
	event->printWindowFlags &= 0xE1000000;
	event->printWindowFlags |= v;
	event->unk184.field_0x0 = evtGetFloat(event, args[1]);
	event->unk184.field_0x4 = evtGetFloat(event, args[2]);
	*(f32*)&event->unk18C = evtGetFloat(event, args[3]);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_msg_togelr) {
	s32 v = evtGetValue(event, *event->args);
	event->printWindowFlags |= 0x80000000;
	switch (v) {
		case 0:
			break;
		case 1:
			event->printWindowFlags |= 0x40000000;
			break;
		case 2:
			event->printWindowFlags |= 0x20000000;
			break;
		case 3:
			event->printWindowFlags |= 0x60000000;
			break;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_msg_pri) {
	event->msgPriority = evtGetValue(event, *event->args);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_msg_npc) {
	const char* name = (const char*)evtGetValue(event, *event->args);
	strcpy(**(char***)((u8*)windowGetPointer(event->printWindowId) + 0x28) + 0x7a04, name);
	return EVT_RETURN_DONE;
}
