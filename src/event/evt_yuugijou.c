#include "evt/evt_yuugijou.h"
#include "evt/evt_cmd.h"
#include "driver/icondrv.h"
#include "driver/windowdrv.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include <dolphin/mtx.h>
#include <string.h>

extern void psndSFXOn(s32 id);
extern USER_FUNC(evt_mario_set_prev_party_pos);
extern USER_FUNC(evt_mario_set_enable_key);
extern USER_FUNC(evt_bero_mapchange);
extern USER_FUNC(evt_mario_cont_onoff);
extern USER_FUNC(evt_mario_get_pos);
extern USER_FUNC(evt_mario_set_pos);
extern USER_FUNC(evt_msg_print);
extern USER_FUNC(evt_msg_select);
extern USER_FUNC(evt_msg_continue);

USER_FUNC(unk_802243a4);
USER_FUNC(yuuminigame_end);
USER_FUNC(yuuminigame_window_end);

//.bss
PiantaParlorWork yuugijouwork;

//.sbss
s32 unk_80418b54;
PiantaParlorWork* yuwp;

s32 minigame_end[] = {
	0x00020032, 0xFD050F80, 0x00000002,
	0x00020032, 0xF840604D, 0x00000001,
	0x0005005B, (s32)evt_mario_set_prev_party_pos, 0x00000000, 0x00000000, 0xFFFFFC18, 0x00000000,
	0x0005005B, (s32)evt_mario_set_prev_party_pos, 0x00000001, 0x00000000, 0xFFFFFC18, 0x00000000,
	0x0002005B, (s32)evt_mario_set_enable_key, 0x00000000,
	0x0003005B, (s32)evt_bero_mapchange, (s32)"gor_03", (s32)"A_dokan_02",
	0x00000002, 0x00000001
};

s32 window_open[] = {
	0x0002005B, (s32)evt_mario_cont_onoff, 0x00000000,
	0x0000006E,
	0x0005005B, (s32)evt_mario_get_pos, 0x00000000, 0xFE363C81, 0xFE363C82, 0xFE363C83,
	0x00010005, 0x00000000,
	0x00010009, 0x00000001,
	0x0004005B, (s32)evt_mario_set_pos, 0xFE363C81, 0xFE363C82, 0xFE363C83,
	0x00000006,
	0x00000070,
	0x0002005B, (s32)unk_802243a4, 0xFE363C80,
	0x0001005E, 0xFE363C80,
	0x0005005B, (s32)evt_msg_print, 0x00000000, (s32)"sysyuu_all_01", 0x00000000, 0x00000000,
	0x0003005B, (s32)evt_msg_select, 0x00000000, (s32)"sysyuu_all_02",
	0x0001005B, (s32)evt_msg_continue,
	0x00020018, 0xFE363C80, 0x00000000,
	0x0001005B, (s32)yuuminigame_end,
	0x00000021,
	0x0001005B, (s32)yuuminigame_window_end,
	0x0002005B, (s32)evt_mario_cont_onoff, 0x00000001,
	0x00000002,
	0x00000001
};

static inline s32 MAX0(s32 x) {
	return x >= 0 ? x : 0;
}

void yuugijou_init(void) {
	yuwp = &yuugijouwork;
	memset(yuwp, 0, sizeof(PiantaParlorWork));

	yuwp->field_0x14 = 1;
	yuwp->field_0x18 = 1;
	yuwp->field_0x1C = 1;
	yuwp->field_0x20 = 1;
	yuwp->field_0x24 = 1;

	yuwp->field_0x74 = 0x5B964;
	yuwp->field_0x78 = 0x5825A;
	yuwp->field_0x7C = 0x4F826;
	yuwp->field_0x80 = 0x4C3D8;
	yuwp->field_0x84 = 0x4237E;

	yuwp->field_0xD4 = 0xE;
	yuwp->field_0xD8 = 0xC;
	yuwp->field_0xDC = 0xF;
	yuwp->field_0xE0 = 0xB;
	yuwp->field_0xE4 = 0xA;

	yuwp->field_0x2C = 1;
	yuwp->field_0x30 = 1;
	yuwp->field_0x34 = 1;
	yuwp->field_0x38 = 1;
	yuwp->field_0x3C = 1;

	yuwp->field_0x8C = 2;
	yuwp->field_0x90 = 5;
	yuwp->field_0x94 = 0x12;
	yuwp->field_0x98 = 0x1B;
	yuwp->field_0x9C = 0x8A;

	yuwp->field_0xEC = MAX0(((700 - (s32)yuwp->field_0x8C) * 15) / 700) + 1;
	yuwp->field_0xF0 = MAX0(((700 - (s32)yuwp->field_0x90) * 15) / 700);
	yuwp->field_0xF4 = MAX0(((700 - (s32)yuwp->field_0x94) * 15) / 700);
	yuwp->field_0xF8 = MAX0(((700 - (s32)yuwp->field_0x98) * 15) / 700);
	yuwp->field_0xFC = MAX0(((700 - (s32)yuwp->field_0x9C) * 15) / 700);

	yuwp->field_0x44 = 1;
	yuwp->field_0x48 = 1;
	yuwp->field_0x4C = 1;
	yuwp->field_0x50 = 1;
	yuwp->field_0x54 = 1;

	yuwp->field_0xA4 = 0x20850;
	yuwp->field_0xA8 = 0x20436;
	yuwp->field_0xAC = 0x20184;
	yuwp->field_0xB0 = 0x1F91E;
	yuwp->field_0xB4 = 0x1E3AC;

	yuwp->field_0x104 = MAX0(((s32)yuwp->field_0xA4 - 109000) / 2000) + 7;
	yuwp->field_0x108 = MAX0(((s32)yuwp->field_0xA8 - 109000) / 2000) + 6;
	yuwp->field_0x10C = MAX0(((s32)yuwp->field_0xAC - 109000) / 2000) + 4;
	yuwp->field_0x110 = MAX0(((s32)yuwp->field_0xB0 - 109000) / 2000) + 4;
	yuwp->field_0x114 = MAX0(((s32)yuwp->field_0xB4 - 109000) / 2000) + 1;

	yuwp->field_0x5C = 1;
	yuwp->field_0x60 = 1;
	yuwp->field_0x64 = 1;
	yuwp->field_0x68 = 1;
	yuwp->field_0x6C = 1;

	yuwp->field_0xBC = 0x16BDE;
	yuwp->field_0xC0 = 0x16968;
	yuwp->field_0xC4 = 0x16382;
	yuwp->field_0xC8 = 0x1627E;
	yuwp->field_0xCC = 0x15950;

	yuwp->field_0x11C = MAX0(((s32)yuwp->field_0xBC - 74000) / 2000) + 7;
	yuwp->field_0x120 = MAX0(((s32)yuwp->field_0xC0 - 74000) / 2000) + 6;
	yuwp->field_0x124 = MAX0(((s32)yuwp->field_0xC4 - 74000) / 2000) + 4;
	yuwp->field_0x128 = MAX0(((s32)yuwp->field_0xC8 - 74000) / 2000) + 3;
	yuwp->field_0x12C = MAX0(((s32)yuwp->field_0xCC - 74000) / 2000) + 4;
}
static inline s32 cmpSign(s32 a, s32 b) {
	if (a > b) {
		return 1;
	}
	return -1;
}

void monteCountDisp(void) {
	static s32 monte_snd_flag;
	s32 y = -0xB4;
	u32 flags = yuwp->field_0x0;
	Mtx mtx;
	GXColor c1, c2, c3, c4;
	if (flags & 4) y = -0x78;
	if (!(flags & 1)) return;
	if (flags & 2) {
		{
		c1 = (GXColor){255, 255, 255, 153};
		windowDispGX_Waku_col(0, c1, -288.0f, (f32)(y + 0x2C), 200.0f, 44.0f, 16.0f);
		PSMTXTrans(mtx, -260.0f, (f32)(y + 2), 0.0f);
		c2 = (GXColor){255, 255, 255, 255};
		iconDispGxCol(mtx, 0x10, 0x13F, c2);
		PSMTXTrans(mtx, -230.0f, (f32)(y + 2), 0.0f);
		c3 = (GXColor){255, 255, 255, 255};
		iconDispGxCol(mtx, 0x10, 0x1D6, c3);
		PSMTXTrans(mtx, -128.0f, (f32)(y + 2), 0.0f);
		c4 = (GXColor){255, 255, 255, 255};
		iconNumberDispGx(mtx, yuwp->field_0x10, 0, c4);
		yuwp->field_0xC++;
		if ((yuwp->field_0xC & 3) == 0) {
			y = yuwp->tokens - yuwp->field_0x10;
			yuwp->field_0xC = 0;
			if (monte_snd_flag == 0 && y != 0) {
				psndSFXOn(0x8CA);
				monte_snd_flag = 8;
			}
			if (y != 0) {
				y = y / 10;
				if (y == 0) {
					s32 sg;
					if ((s32)yuwp->tokens > (s32)yuwp->field_0x10) sg = 1; else sg = -1;
					y = sg;
				}
				yuwp->field_0x10 += y;
			}
		}
		if (monte_snd_flag != 0) monte_snd_flag--;
		}
	}
}

USER_FUNC(yuugijou_add_montemedal) {
	s32* args = event->args;
	s32 a = evtGetValue(event, args[0]);
	s32 sum = yuwp->tokens + evtGetValue(event, args[1]);
	if (sum < 0x1869F) {
		yuwp->tokens = sum;
	} else {
		yuwp->tokens = 0x1869F;
	}
	if (a != 0) yuwp->field_0x10 = yuwp->tokens;
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_get_montemedal) {
	evtSetValue(event, event->args[0], yuwp->tokens);
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_get_montemedal_keep) {
	s32* args = event->args;
	if (yuwp->field_0x0 & 2) {
		evtSetValue(event, args[0], 0);
	} else {
		evtSetValue(event, args[0], yuwp->field_0x4);
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_add_montemedal_moto) {
	s32* args = event->args;
	evtGetValue(event, args[0]);
	if (yuwp->field_0x0 & 2) {
		yuwp->field_0x4 += evtGetValue(event, args[1]);
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_montemedal_disp_onoff) {
	if (evtGetValue(event, event->args[0]) != 0) {
		yuwp->field_0x0 |= 1;
		yuwp->field_0x10 = yuwp->tokens;
	} else {
		yuwp->field_0x0 &= ~1;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_montemedal_wait) {
	if ((s32)yuwp->field_0x10 != yuwp->tokens) return EVT_RETURN_BLOCK;
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_montemedal_keep) {
	if (yuwp->field_0x0 & 2) {
		yuwp->field_0x4 = yuwp->tokens;
		yuwp->tokens = 0;
		yuwp->field_0x10 = 0;
		yuwp->field_0x0 &= ~2;
		yuwp->field_0x0 &= ~1;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_montemedal_return) {
	if (!(yuwp->field_0x0 & 2)) {
		yuwp->field_0x10 = yuwp->tokens = yuwp->field_0x4;
		yuwp->field_0x0 |= 2;
		yuwp->field_0x0 |= 1;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_get_takeoutflag) {
	s32* args = event->args;
	if (yuwp->field_0x0 & 2) {
		evtSetValue(event, args[0], 1);
	} else {
		evtSetValue(event, args[0], 0);
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_set_yupflag) {
	if (evtGetValue(event, event->args[0]) != 0) {
		yuwp->field_0x0 |= 4;
	} else {
		yuwp->field_0x0 &= ~4;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(yuuminigame_window_end) {
	yuwp->field_0x0 |= 8;
	return EVT_RETURN_DONE;
}

USER_FUNC(yuuminigame_end) {
	evtEntryType(minigame_end, 0, 0, 0xEF);
	return EVT_RETURN_DONE;
}

USER_FUNC(unk_802243a4) {
	evtSetValue(event, event->args[0], unk_80418b54);
	return EVT_RETURN_DONE;
}

void unk_8022439c(s32 value) {
	unk_80418b54 = value;
}

void evtYuuWindow(void) {
	yuwp->field_0x0 &= ~8;
	evtEntryType(window_open, 0, 0, 0);
}

s32 evtYuuWindowEndChk(void) {
	return (yuwp->field_0x0 >> 3) & 1;
}
