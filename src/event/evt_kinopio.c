#include "evt/evt_cmd.h"
#include "evt/evt_cam.h"
#include "evt/evt_fade.h"
#include "evt/evt_npc.h"
#include "evt/evt_snd.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "driver/itemdrv.h"
#include "driver/npcdrv.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "pmario_sound.h"
#include <string.h>

extern double sin(double x);
extern double cos(double x);
extern GlobalWork* gp;
extern ItemEntry* itemEntry(const char* name, s32 itemId, s32 type, s32 evtId, s32 a5, f32 x, f32 y, f32 z);

extern USER_FUNC(evt_eff);
extern USER_FUNC(evt_eff_fukidashi);
extern USER_FUNC(evt_fade_end_wait);
extern USER_FUNC(evt_fade_set_spot_pos);
extern USER_FUNC(evt_mario_adjust_dir);
extern USER_FUNC(evt_mario_dispflag_onoff);
extern USER_FUNC(evt_mario_flag_onoff);
extern USER_FUNC(evt_mario_get_exparty);
extern USER_FUNC(evt_mario_get_party);
extern USER_FUNC(evt_mario_get_pos);
extern USER_FUNC(evt_mario_goodbye_party);
extern USER_FUNC(evt_mario_jump_pos);
extern USER_FUNC(evt_mario_key_onoff);
extern USER_FUNC(evt_mario_mov_pos2);
extern USER_FUNC(evt_mario_set_dir_npc);
extern USER_FUNC(evt_mario_set_party_pos);
extern USER_FUNC(evt_mario_set_pos);
extern USER_FUNC(evt_msg_print);
extern USER_FUNC(evt_msg_print_add);
extern USER_FUNC(evt_msg_print_insert);
extern USER_FUNC(evt_msg_select);
extern USER_FUNC(evt_npc_set_tribe);
extern USER_FUNC(evt_party_run);
extern USER_FUNC(evt_party_set_dir_npc);
extern USER_FUNC(evt_party_set_pos);
extern USER_FUNC(evt_pouch_add_coin);
extern USER_FUNC(evt_pouch_all_party_recovery);
extern USER_FUNC(evt_pouch_check_item);
extern USER_FUNC(evt_pouch_mario_recovery);
extern USER_FUNC(evt_pouch_remove_item);
extern USER_FUNC(evt_set_dir_to_target);
extern USER_FUNC(evt_snd_bgmoff);
extern USER_FUNC(evt_snd_sfxon);
extern USER_FUNC(evt_sub_get_coin);
extern USER_FUNC(evt_sub_get_mapname);
extern USER_FUNC(evt_win_coin_off);
extern USER_FUNC(evt_win_coin_on);

typedef struct KinopioParty {
	u16 flags;
	s16 maximumHP;
	s16 pad4;
	s16 currentHP;
	s16 pad8[3];
} KinopioParty;

typedef s32 (*KinopioGetter)(void);

typedef struct KinopioWork {
	s32 breakfastItem; // 0x0
	Vec breakfastPos;  // 0x4
	s32 ryoukin;       // 0x10
	Vec bed;           // 0x14
	Vec bedside;       // 0x20
	f32 cam[6];        // 0x2C
	f32 bedDeg;        // 0x44
	Vec npcTalk;       // 0x48
	char* npcName;     // 0x54
	s32 msg[14];       // 0x58
	s32 toBedEvt;      // 0x90
	s32 fromBedEvt;    // 0x94
} KinopioWork;

USER_FUNC(N_cameraman_on);
USER_FUNC(snd_on);
USER_FUNC(snd_off);
USER_FUNC(breakfast);
USER_FUNC(offset);
static USER_FUNC(paper_off);
static USER_FUNC(paper_on);
USER_FUNC(get_from_bed_evt);
USER_FUNC(get_to_bed_evt);
USER_FUNC(get_cam);
USER_FUNC(get_npctalk);
USER_FUNC(get_beddeg);
USER_FUNC(get_bedside);
USER_FUNC(get_bed);
USER_FUNC(get_npcname);
USER_FUNC(get_ryoukin);
USER_FUNC(coin_chk);
USER_FUNC(power_chk);
USER_FUNC(msg_no);
USER_FUNC(evt_kinopio_setup);
extern s32 evt_50[];
extern s32 kinopio_house_talk_evt[];

//.sbss
static KinopioWork* work;

//.sdata
static KinopioWork** wp = &work;

USER_FUNC(evt_kinopio_setup) {
	KinopioWork* w = (KinopioWork*)evtGetValue(event, event->args[0]);
	NpcEntry* npc = npcNameToPtr(w->npcName);
	if (!animGroupBaseAsync("p_slit", 0, NULL)) {
		return 0;
	}
	npc->talkEvt = kinopio_house_talk_evt;
	*wp = w;
	return 2;
}

USER_FUNC(msg_no) {
	s32* args = event->args;
	s32 idx = evtGetValue(event, args[0]);
	evtSetValue(event, args[1], (*wp)->msg[idx]);
	return 2;
}

USER_FUNC(power_chk) {
	s32* args = event->args;
	s32 ok;
	s32 i;
	KinopioParty* pouch = (KinopioParty*)pouchGetPtr();
	ok = 1;
	for (i = 0; i < 8; i++) {
		if ((pouch[i].flags & 1) && pouch[i].currentHP != pouch[i].maximumHP) {
			ok = 0;
			break;
		}
	}
	if (((KinopioGetter)pouchGetHP)() == ((KinopioGetter)pouchGetMaxHP)() && ((KinopioGetter)pouchGetFP)() == ((KinopioGetter)pouchGetMaxFP)() && ((KinopioGetter)pouchGetAP)() == ((KinopioGetter)pouchGetMaxAP)() && ok) {
		evtSetValue(event, args[0], 1);
	} else {
		evtSetValue(event, args[0], 0);
	}
	return 2;
}

USER_FUNC(coin_chk) {
	s32* args = event->args;
	if (pouchGetCoin() < (*wp)->ryoukin) {
		evtSetValue(event, args[0], 1);
	} else {
		evtSetValue(event, args[0], 0);
	}
	return 2;
}

USER_FUNC(get_ryoukin) {
	evtSetValue(event, event->args[0], (*wp)->ryoukin);
	return 2;
}

USER_FUNC(get_npcname) {
	evtSetValue(event, event->args[0], (s32)(*wp)->npcName);
	return 2;
}

USER_FUNC(get_bed) {
	s32* args = event->args;
	evtSetFloat(event, args[0], (*wp)->bed.x);
	evtSetFloat(event, args[1], (*wp)->bed.y);
	evtSetFloat(event, args[2], (*wp)->bed.z);
	return 2;
}

USER_FUNC(get_bedside) {
	s32* args = event->args;
	evtSetFloat(event, args[0], (*wp)->bedside.x);
	evtSetFloat(event, args[1], (*wp)->bedside.y);
	evtSetFloat(event, args[2], (*wp)->bedside.z);
	return 2;
}

USER_FUNC(get_beddeg) {
	evtSetFloat(event, event->args[0], (*wp)->bedDeg);
	return 2;
}

USER_FUNC(get_npctalk) {
	s32* args = event->args;
	evtSetFloat(event, args[0], (*wp)->npcTalk.x);
	evtSetFloat(event, args[1], (*wp)->npcTalk.y);
	evtSetFloat(event, args[2], (*wp)->npcTalk.z);
	return 2;
}

USER_FUNC(get_cam) {
	s32* args = event->args;
	evtSetFloat(event, args[0], (*wp)->cam[0]);
	evtSetFloat(event, args[1], (*wp)->cam[1]);
	evtSetFloat(event, args[2], (*wp)->cam[2]);
	evtSetFloat(event, args[3], (*wp)->cam[3]);
	evtSetFloat(event, args[4], (*wp)->cam[4]);
	evtSetFloat(event, args[5], (*wp)->cam[5]);
	return 2;
}

USER_FUNC(get_to_bed_evt) {
	evtSetValue(event, event->args[0], (*wp)->toBedEvt);
	return 2;
}

USER_FUNC(get_from_bed_evt) {
	evtSetValue(event, event->args[0], (*wp)->fromBedEvt);
	return 2;
}

static USER_FUNC(paper_on) {
	s32* args = event->args;
	f32 amount = evtGetFloat(event, *args++);
	MarioWork* mario = marioGetPtr();
	if (isFirstCall) {
		marioPaperOn("p_slit");
		marioChgPose("M_S_1");
		marioChgPaper("PM_S_3A");
		event->userdata[0] = 0;
	}
	if (event->userdata[0] < 30) {
		f32 ang;
		if (strcmp(gp->currentMapName, "pik_04") == 0) {
			ang = 6.2831855f * amount / 360.0f;
			mario->position.x -= 0.2f * (f32)cos(ang);
			mario->position.z -= 0.2f * (f32)sin(ang);
		} else {
			ang = 6.2831855f * amount / 360.0f;
			mario->position.x += 0.2f * (f32)cos(ang);
			mario->position.z += 0.2f * (f32)sin(ang);
		}
		event->userdata[0]++;
	}
	mario->displayDirectionTarget = amount;
	mario->displayDirection = amount;
	return 0;
}

static USER_FUNC(paper_off) {
	marioPaperOff();
	return 2;
}

USER_FUNC(offset) {
	s32* args = event->args;
	f32 dist = evtGetFloat(event, args[0]);
	f32 ang = 6.2831855f * (90.0f + camGetPtr(CAMERA_3D)->viewYaw) / 360.0f;
	evtSetFloat(event, args[1], dist * -(f32)sin(ang));
	evtSetFloat(event, args[2], dist * (f32)cos(ang));
	return 2;
}

USER_FUNC(breakfast) {
	ItemEntry* item = itemNameToPtr("breakfast");
	if (item == NULL || !(item->flags & 1)) {
		KinopioWork* w = *wp;
		if (w->breakfastItem != 0) {
			itemEntry("breakfast", w->breakfastItem, 0x10, -1, 0, w->breakfastPos.x, w->breakfastPos.y,
			          w->breakfastPos.z);
		}
	}
	return 2;
}

USER_FUNC(snd_off) {
	psndSetFlag(0x80);
	return 2;
}

USER_FUNC(snd_on) {
	psndClearFlag(0x80);
	return 2;
}

USER_FUNC(N_cameraman_on) {
	NpcEntry* npc = npcNameToPtr("\217h\211\256\202\314\203J\203\201\203\211\203}\203\223");
	animPoseSetMaterialFlagOn(npc->poseId, 0x1800);
	return 2;
}

//.data
s32 kinopio_house_talk_evt[] = {
	0x0002005B, (s32)evt_mario_key_onoff, 0x00000000,
	0x0002005B, (s32)get_ryoukin, 0xFE363C8A,
	0x0002005B, (s32)get_npcname, 0xFE363C8B,
	0x0003005B, (s32)evt_win_coin_on, 0x00000000, 0xFE363C8C,
	0x0003005B, (s32)msg_no, 0x00000000, 0xFE363C80,
	0x0006005B, (s32)evt_msg_print_insert, 0x00000000, 0xFE363C80, 0x00000000, 0xFE363C8B, 0xFE363C8A,
	0x0003005B, (s32)msg_no, 0x00000006, 0xFE363C80,
	0x0003005B, (s32)evt_msg_select, 0x00000000, 0xFE363C80,
	0x00020018, 0xFE363C80, 0x00000001,
	0x0003005B, (s32)msg_no, 0x00000002, 0xFE363C80,
	0x0003005B, (s32)evt_msg_print_add, 0x00000000, 0xFE363C80,
	0x0002005B, (s32)evt_mario_key_onoff, 0x00000001,
	0x0002005B, (s32)evt_win_coin_off, 0xFE363C8C,
	0x00000002,
	0x00000021,
	0x0002005B, (s32)power_chk, 0xFE363C80,
	0x00020018, 0xFE363C80, 0x00000001,
	0x0003005B, (s32)msg_no, 0x00000001, 0xFE363C80,
	0x0003005B, (s32)evt_msg_print_add, 0x00000000, 0xFE363C80,
	0x0003005B, (s32)msg_no, 0x00000006, 0xFE363C80,
	0x0003005B, (s32)evt_msg_select, 0x00000000, 0xFE363C80,
	0x00020018, 0xFE363C80, 0x00000001,
	0x0003005B, (s32)msg_no, 0x00000002, 0xFE363C80,
	0x0003005B, (s32)evt_msg_print_add, 0x00000000, 0xFE363C80,
	0x0002005B, (s32)evt_mario_key_onoff, 0x00000001,
	0x0002005B, (s32)evt_win_coin_off, 0xFE363C8C,
	0x00000002,
	0x00000021,
	0x00000021,
	0x00020032, 0xFBD3E280, 0x00000000,
	0x0003005B, (s32)evt_pouch_check_item, 0x000000A4, 0xFE363C80,
	0x0002001B, 0xFE363C80, 0x00000000,
	0x0003005B, (s32)msg_no, 0x00000007, 0xFE363C80,
	0x0003005B, (s32)evt_msg_print_add, 0x00000000, 0xFE363C80,
	0x0003005B, (s32)msg_no, 0x00000008, 0xFE363C80,
	0x0003005B, (s32)evt_msg_select, 0x00000000, 0xFE363C80,
	0x00020018, 0xFE363C80, 0x00000000,
	0x00020032, 0xFBD3E280, 0x00000001,
	0x0003005B, (s32)evt_pouch_remove_item, 0x000000A4, 0xFE363C80,
	0x00000021,
	0x00000021,
	0x00020018, 0xFBD3E280, 0x00000000,
	0x0002005B, (s32)coin_chk, 0xFE363C80,
	0x00020018, 0xFE363C80, 0x00000001,
	0x0003005B, (s32)msg_no, 0x00000004, 0xFE363C80,
	0x0003005B, (s32)evt_msg_print_add, 0x00000000, 0xFE363C80,
	0x0002005B, (s32)evt_mario_key_onoff, 0x00000001,
	0x0002005B, (s32)evt_win_coin_off, 0xFE363C8C,
	0x00000002,
	0x00000021,
	0x0002005B, (s32)get_ryoukin, 0xFE363C8A,
	0x00020037, 0xFE363C8A, 0xFFFFFFFF,
	0x0002005B, (s32)evt_pouch_add_coin, 0xFE363C8A,
	0x0001000A, 0x000003E8,
	0x00000021,
	0x0002005B, (s32)evt_win_coin_off, 0xFE363C8C,
	0x0003005B, (s32)msg_no, 0x00000003, 0xFE363C80,
	0x0003005B, (s32)evt_msg_print_add, 0x00000000, 0xFE363C80,
	0x0002005B, (s32)get_npcname, 0xFE363C80,
	0x0004005B, (s32)evt_npc_flag_onoff, 0x00000001, 0xFE363C80, 0x00000020,
	0x0002005B, (s32)evt_mario_get_party, 0xFE363C8B,
	0x0002005B, (s32)evt_mario_get_exparty, 0xFE363C8C,
	0x0005005B, (s32)evt_mario_get_pos, 0x00000000, 0xFE363C8D, 0xFE363C8E, 0xFE363C8F,
	0x0002005B, (s32)evt_mario_goodbye_party, 0x00000001,
	0x0002005B, (s32)evt_mario_goodbye_party, 0x00000000,
	0x0002005B, (s32)get_to_bed_evt, 0xFE363C80,
	0x00020018, 0xFE363C80, 0x00000000,
	0x0000006B,
	0x0001000A, 0x000003E8,
	0x0007005B, (s32)get_cam, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0xFE363C83, 0xFE363C84, 0xFE363C85,
	0x0009005B, (s32)evt_cam3d_evt_set, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0xFE363C83, 0xFE363C84, 0xFE363C85, 0x00000000, 0x0000000B,
	0x0000006D,
	0x0004005B, (s32)get_bedside, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0004005B, (s32)evt_mario_mov_pos2, 0xFE363C80, 0xFE363C82, 0xF24BE280,
	0x00000020,
	0x0001006C, 0xFE363C80,
	0x0001005E, 0xFE363C80,
	0x0000006D,
	0x00010005, 0x00000000,
	0x0002006A, 0xFE363C80, 0xFE363C81,
	0x00020018, 0xFE363C81, 0x00000000,
	0x00000007,
	0x00000021,
	0x00010009, 0x00000001,
	0x00000006,
	0x0007005B, (s32)get_cam, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0xFE363C83, 0xFE363C84, 0xFE363C85,
	0x0009005B, (s32)evt_cam3d_evt_set, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0xFE363C83, 0xFE363C84, 0xFE363C85, 0x00000000, 0x0000000B,
	0x0001000A, 0x000001F4,
	0x00000021,
	0x0005005B, (s32)evt_mario_get_pos, 0x00000000, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0006005B, (s32)evt_snd_sfxon_3d, 0x0002009E, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0x00000000,
	0x0003005B, (s32)evt_mario_flag_onoff, 0x00000001, 0x00000700,
	0x0004005B, (s32)get_bed, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0007005B, (s32)evt_mario_jump_pos, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0xF250BA80, 0x00000000, 0xFFFFFC18,
	0x0004005B, (s32)evt_mario_set_pos, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0001005B, (s32)evt_mario_adjust_dir,
	0x0001000A, 0x000000C8,
	0x0003005B, (s32)evt_mario_dispflag_onoff, 0x00000001, 0x00001000,
	0x0001006C, 0xFE363C8A,
	0x0002005B, (s32)get_beddeg, 0xFE363C80,
	0x0002005B, (s32)paper_on, 0xFE363C80,
	0x0000006D,
	0x0000006B,
	0x0005005B, (s32)evt_mario_get_pos, 0x00000000, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0006005B, (s32)evt_snd_sfxon_3d, 0x000203BA, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0x00000000,
	0x0001000A, 0x000000C8,
	0x0006005B, (s32)evt_snd_sfxon_3d, 0x000203BB, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0x00000000,
	0x0000006D,
	0x0001005B, (s32)snd_off,
	0x0002005B, (s32)evt_snd_bgmoff, 0x00000400,
	0x0003005B, (s32)evt_snd_bgmon, 0x00000001, (s32)"BGM_FF_GO_SLEEPING1",
	0x0006005B, (s32)evt_fade_entry, 0x00000004, 0x00000BB8, 0x00000000, 0x00000000, 0x00000000,
	0x0005005B, (s32)evt_mario_get_pos, 0x00000000, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0004005B, (s32)evt_fade_set_spot_pos, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0001005B, (s32)evt_fade_end_wait,
	0x0006005B, (s32)evt_fade_entry, 0x0000000C, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x0001005B, (s32)evt_fade_end_wait,
	0x0001005B, (s32)evt_pouch_mario_recovery,
	0x0001005B, (s32)evt_pouch_all_party_recovery,
	0x0001005B, (s32)breakfast,
	0x0001000A, 0x00000BB8,
	0x0001005F, 0xFE363C8A,
	0x0001005B, (s32)paper_off,
	0x0003005B, (s32)evt_mario_dispflag_onoff, 0x00000000, 0x00001000,
	0x00020019, 0xFE363C8B, 0x00000000,
	0x0004005B, (s32)get_bed, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0006005B, (s32)evt_mario_set_party_pos, 0x00000000, 0xFE363C8B, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x00000021,
	0x00020019, 0xFE363C8C, 0x00000000,
	0x0004005B, (s32)get_bed, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0004005B, (s32)offset, 0xF24AF280, 0xFE363C83, 0xFE363C84,
	0x0002003A, 0xFE363C80, 0xFE363C83,
	0x0002003A, 0xFE363C82, 0xFE363C84,
	0x0006005B, (s32)evt_mario_set_party_pos, 0x00000001, 0xFE363C8C, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x00000021,
	0x0003005B, (s32)evt_mario_flag_onoff, 0x00000000, 0x00000700,
	0x0004005B, (s32)get_bedside, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0004005B, (s32)evt_mario_set_pos, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0002005B, (s32)get_npcname, 0xFE363C80,
	0x0003005B, (s32)evt_set_dir_to_target, 0xFE363C80, (s32)"mario",
	0x0002005B, (s32)evt_mario_set_dir_npc, 0xFE363C80,
	0x0003005B, (s32)evt_party_set_dir_npc, 0x00000000, 0xFE363C80,
	0x0003005B, (s32)evt_party_set_dir_npc, 0x00000001, 0xFE363C80,
	0x0004005B, (s32)evt_npc_flag_onoff, 0x00000001, 0xFE363C80, 0x00008000,
	0x0003005B, (s32)evt_cam3d_evt_off, 0x00000000, 0x0000000B,
	0x00010009, 0x00000001,
	0x0004005B, (s32)evt_npc_flag_onoff, 0x00000000, 0xFE363C80, 0x00008000,
	0x0002005B, (s32)evt_snd_bgmoff, 0x00000201,
	0x0003005B, (s32)evt_snd_bgmon, 0x00000120, 0x00000000,
	0x0001005B, (s32)snd_on,
	0x00020035, 0xF5DE0181, 0x00000001,
	0x0002001B, 0xF5DE0181, 0x00000064,
	0x00020032, 0xF5DE0181, 0x00000064,
	0x00000021,
	0x00020018, 0xF5DE0181, 0x00000032,
	0x0001005E, (s32)evt_50,
	0x0002005B, (s32)get_npcname, 0xFE363C80,
	0x0004005B, (s32)evt_npc_flag_onoff, 0x00000000, 0xFE363C80, 0x00000020,
	0x00000002,
	0x00000021,
	0x0001005B, (s32)evt_mario_adjust_dir,
	0x0006005B, (s32)evt_fade_entry, 0x0000000B, 0x000003E8, 0x00000000, 0x00000000, 0x00000000,
	0x0001005B, (s32)evt_fade_end_wait,
	0x0002005B, (s32)get_from_bed_evt, 0xFE363C80,
	0x00020019, 0xFE363C80, 0x00000000,
	0x0001006C, 0xFE363C8A,
	0x0001005E, 0xFE363C80,
	0x0000006D,
	0x00010005, 0x00000000,
	0x0002006A, 0xFE363C8A, 0xFE363C8B,
	0x00020018, 0xFE363C8B, 0x00000000,
	0x00000007,
	0x00000021,
	0x00010009, 0x00000001,
	0x00000006,
	0x00000021,
	0x0002005B, (s32)evt_party_run, 0x00000000,
	0x0002005B, (s32)evt_party_run, 0x00000001,
	0x0004005B, (s32)get_npctalk, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0004005B, (s32)evt_mario_mov_pos2, 0xFE363C80, 0xFE363C82, 0xF24BE280,
	0x0001005B, (s32)evt_fade_end_wait,
	0x0002005B, (s32)get_npcname, 0xFE363C8B,
	0x0002005B, (s32)evt_mario_set_dir_npc, 0xFE363C8B,
	0x0003005B, (s32)evt_party_set_dir_npc, 0x00000000, 0xFE363C8B,
	0x0002005B, (s32)get_npcname, 0xFE363C8B,
	0x0003005B, (s32)msg_no, 0x00000005, 0xFE363C80,
	0x0005005B, (s32)evt_msg_print, 0x00000000, 0xFE363C80, 0x00000000, 0xFE363C8B,
	0x0002005B, (s32)get_npcname, 0xFE363C80,
	0x0004005B, (s32)evt_npc_flag_onoff, 0x00000000, 0xFE363C80, 0x00000020,
	0x0002005B, (s32)evt_mario_key_onoff, 0x00000001,
	0x00000002,
	0x00000001,
};

s32 evt_50[] = {
	0x0002005B, (s32)get_npcname, 0xFE363C8A,
	0x0005005B, (s32)evt_npc_get_position, 0xFE363C8A, 0xFE363C8D, 0xFE363C8E, 0xFE363C8F,
	0x0003005B, (s32)evt_npc_entry, (s32)"\217h\211\256\202\314\203J\203\201\203\211\203}\203\223", (s32)"c_jugem_c",
	0x0003005B, (s32)evt_npc_set_tribe, (s32)"\217h\211\256\202\314\203J\203\201\203\211\203}\203\223", (s32)"\203J\203\201\203\211\203}\203\223",
	0x0001005B, (s32)N_cameraman_on,
	0x0004005B, (s32)evt_npc_flag_onoff, 0x00000001, (s32)"\217h\211\256\202\314\203J\203\201\203\211\203}\203\223", 0x00008000,
	0x0002005B, (s32)evt_sub_get_mapname, 0xFE363C80,
	0x0002000C, 0xFE363C80, (s32)"bom_02",
	0x0005005B, (s32)evt_npc_set_position, (s32)"\217h\211\256\202\314\203J\203\201\203\211\203}\203\223", 0xFFFFFE93, 0x0000001E, 0xFFFFFF56,
	0x00000021,
	0x0002000C, 0xFE363C80, (s32)"gor_01",
	0x0005005B, (s32)evt_npc_set_position, (s32)"\217h\211\256\202\314\203J\203\201\203\211\203}\203\223", 0x000000A8, 0x0000009A, 0xFFFFFF1B,
	0x00000021,
	0x0002000C, 0xFE363C80, (s32)"muj_01",
	0x0005005B, (s32)evt_npc_set_position, (s32)"\217h\211\256\202\314\203J\203\201\203\211\203}\203\223", 0x0000010E, 0x00000014, 0xFFFFFF6F,
	0x00000021,
	0x0002000C, 0xFE363C80, (s32)"nok_00",
	0x0005005B, (s32)evt_npc_set_position, (s32)"\217h\211\256\202\314\203J\203\201\203\211\203}\203\223", 0xFFFFFE7F, 0x00000019, 0xFFFFFF6F,
	0x00000021,
	0x0002000C, 0xFE363C80, (s32)"pik_04",
	0x0005005B, (s32)evt_npc_set_position, (s32)"\217h\211\256\202\314\203J\203\201\203\211\203}\203\223", 0x00000136, 0x00000531, 0xFFFFFF9C,
	0x0005005B, (s32)evt_npc_set_position, 0xFE363C8A, 0x00000136, 0x00000531, 0xFFFFFFBF,
	0x00000021,
	0x0002000C, 0xFE363C80, (s32)"usu_00",
	0x0005005B, (s32)evt_npc_set_position, (s32)"\217h\211\256\202\314\203J\203\201\203\211\203}\203\223", 0x0000010C, 0x00000000, 0xFFFFFF2E,
	0x00000021,
	0x0003005B, (s32)evt_set_dir_to_target, (s32)"\217h\211\256\202\314\203J\203\201\203\211\203}\203\223", (s32)"mario",
	0x0003005B, (s32)evt_set_dir_to_target, 0xFE363C8A, (s32)"mario",
	0x0002005B, (s32)evt_mario_set_dir_npc, (s32)"\217h\211\256\202\314\203J\203\201\203\211\203}\203\223",
	0x0003005B, (s32)evt_party_set_dir_npc, 0x00000000, (s32)"\217h\211\256\202\314\203J\203\201\203\211\203}\203\223",
	0x0003005B, (s32)msg_no, 0x00000009, 0xFE363C80,
	0x0005005B, (s32)evt_msg_print, 0x00000000, 0xFE363C80, 0x00000000, 0xFE363C8A,
	0x0004005B, (s32)get_bed, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0004005B, (s32)evt_mario_set_pos, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x00020035, 0xFE363C82, 0x00000005,
	0x0005005B, (s32)evt_party_set_pos, 0x00000000, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0006005B, (s32)evt_fade_entry, 0x00000009, 0x000003E8, 0x00000000, 0x00000000, 0x00000000,
	0x0001005B, (s32)evt_fade_end_wait,
	0x0001000A, 0x000001F4,
	0x0005005B, (s32)evt_mario_get_pos, 0x00000000, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x00020035, 0xFE363C81, 0x00000064,
	0x000F005B, (s32)evt_eff, 0x00000000, (s32)"confetti", 0x00000003, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0x00000258, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x0000006B,
	0x0005005B, (s32)evt_mario_get_pos, 0x00000000, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0006005B, (s32)evt_snd_sfxon_3d, (s32)"SFX_VOICE_MARIO_FIND1", 0xFE363C80, 0xFE363C81, 0xFE363C82, 0x00000000,
	0x0000006D,
	0x000C005B, (s32)evt_eff_fukidashi, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x000C005B, (s32)evt_eff_fukidashi, 0x00000003, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x0001000A, 0x000003E8,
	0x0003005B, (s32)msg_no, 0x0000000A, 0xFE363C80,
	0x0005005B, (s32)evt_msg_print, 0x00000000, 0xFE363C80, 0x00000000, 0xFE363C8A,
	0x0004005B, (s32)get_bedside, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0004005B, (s32)evt_mario_mov_pos2, 0xFE363C80, 0xFE363C82, 0xF24BE280,
	0x0004005B, (s32)get_npctalk, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0004005B, (s32)evt_mario_mov_pos2, 0xFE363C80, 0xFE363C82, 0xF24BE280,
	0x0002005B, (s32)evt_mario_set_dir_npc, 0xFE363C8A,
	0x0003005B, (s32)msg_no, 0x0000000B, 0xFE363C80,
	0x0005005B, (s32)evt_msg_print, 0x00000000, 0xFE363C80, 0x00000000, 0xFE363C8A,
	0x0002005B, (s32)evt_mario_set_dir_npc, (s32)"\217h\211\256\202\314\203J\203\201\203\211\203}\203\223",
	0x0003005B, (s32)evt_party_set_dir_npc, 0x00000000, (s32)"\217h\211\256\202\314\203J\203\201\203\211\203}\203\223",
	0x0001000A, 0x0000012C,
	0x0003005B, (s32)evt_snd_sfxon, (s32)"SFX_EVT_50_HOTEL_SHUTTER1", 0x00000000,
	0x0006005B, (s32)evt_fade_entry, 0x00000008, 0x00000096, 0x000000FF, 0x000000FF, 0x000000FF,
	0x0005005B, (s32)evt_mario_get_pos, 0x00000000, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x00020035, 0xFE363C81, 0x00000028,
	0x0004005B, (s32)evt_fade_set_spot_pos, 0xFE363C80, 0xFE363C81, 0xFE363C82,
	0x0001005B, (s32)evt_fade_end_wait,
	0x0006005B, (s32)evt_fade_entry, 0x00000007, 0x00000096, 0x000000FF, 0x000000FF, 0x000000FF,
	0x0001005B, (s32)evt_fade_end_wait,
	0x0003005B, (s32)msg_no, 0x0000000C, 0xFE363C80,
	0x0005005B, (s32)evt_msg_print, 0x00000000, 0xFE363C80, 0x00000000, 0xFE363C8A,
	0x0002005B, (s32)evt_mario_set_dir_npc, 0xFE363C8A,
	0x0003005B, (s32)evt_party_set_dir_npc, 0x00000000, 0xFE363C8A,
	0x0001000A, 0x0000012C,
	0x0002005B, (s32)evt_sub_get_coin, 0x000000C8,
	0x0003005B, (s32)msg_no, 0x0000000D, 0xFE363C80,
	0x0005005B, (s32)evt_msg_print, 0x00000000, 0xFE363C80, 0x00000000, 0xFE363C8A,
	0x0006005B, (s32)evt_fade_entry, 0x0000000A, 0x000003E8, 0x00000000, 0x00000000, 0x00000000,
	0x0001005B, (s32)evt_fade_end_wait,
	0x0002005B, (s32)evt_npc_check_delete, (s32)"\217h\211\256\202\314\203J\203\201\203\211\203}\203\223",
	0x0005005B, (s32)evt_npc_set_position, 0xFE363C8A, 0xFE363C8D, 0xFE363C8E, 0xFE363C8F,
	0x0003005B, (s32)evt_set_dir_to_target, 0xFE363C8A, (s32)"mario",
	0x0006005B, (s32)evt_fade_entry, 0x00000009, 0x000003E8, 0x00000000, 0x00000000, 0x00000000,
	0x0001005B, (s32)evt_fade_end_wait,
	0x0002005B, (s32)evt_party_run, 0x00000000,
	0x0002005B, (s32)evt_mario_key_onoff, 0x00000001,
	0x00000002,
	0x00000001,
};

