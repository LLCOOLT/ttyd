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
s32 gap_08_80418B5C_sbss;
PiantaParlorWork* yuwp;
s32 unk_80418b54;

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
	s32 t;
	yuwp = &yuugijouwork;
	memset(yuwp, 0, sizeof(PiantaParlorWork));

	yuwp->recordOn[0][0] = 1;
	yuwp->recordOn[0][1] = 1;
	yuwp->recordOn[0][2] = 1;
	yuwp->recordOn[0][3] = 1;
	yuwp->recordOn[0][4] = 1;

	yuwp->recordScore[0][0] = 0x5B964;
	yuwp->recordScore[0][1] = 0x5825A;
	yuwp->recordScore[0][2] = 0x4F826;
	yuwp->recordScore[0][3] = 0x4C3D8;
	yuwp->recordScore[0][4] = 0x4237E;

	yuwp->recordParam[0][0] = 0xE;
	yuwp->recordParam[0][1] = 0xC;
	yuwp->recordParam[0][2] = 0xF;
	yuwp->recordParam[0][3] = 0xB;
	yuwp->recordParam[0][4] = 0xA;

	yuwp->recordOn[1][0] = 1;
	yuwp->recordOn[1][1] = 1;
	yuwp->recordOn[1][2] = 1;
	yuwp->recordOn[1][3] = 1;
	yuwp->recordOn[1][4] = 1;

	yuwp->recordScore[1][0] = 2;
	yuwp->recordScore[1][1] = 5;
	yuwp->recordScore[1][2] = 0x12;
	yuwp->recordScore[1][3] = 0x1B;
	yuwp->recordScore[1][4] = 0x8A;

	yuwp->recordParam[1][0] = MAX0(((700 - (s32)yuwp->recordScore[1][0]) * 15) / 700) + 1;
	t = (700 - (s32)yuwp->recordScore[1][1]) * 15;
	yuwp->recordParam[1][1] = MAX0(t / 700);
	t = (700 - (s32)yuwp->recordScore[1][2]) * 15;
	yuwp->recordParam[1][2] = MAX0(t / 700);
	t = (700 - (s32)yuwp->recordScore[1][3]) * 15;
	yuwp->recordParam[1][3] = MAX0(t / 700);
	t = (700 - (s32)yuwp->recordScore[1][4]) * 15;
	yuwp->recordParam[1][4] = MAX0(t / 700);

	yuwp->recordOn[2][0] = 1;
	yuwp->recordOn[2][1] = 1;
	yuwp->recordOn[2][2] = 1;
	yuwp->recordOn[2][3] = 1;
	yuwp->recordOn[2][4] = 1;

	yuwp->recordScore[2][0] = 0x20850;
	yuwp->recordScore[2][1] = 0x20436;
	yuwp->recordScore[2][2] = 0x20184;
	yuwp->recordScore[2][3] = 0x1F91E;
	yuwp->recordScore[2][4] = 0x1E3AC;

	yuwp->recordParam[2][0] = MAX0(((s32)yuwp->recordScore[2][0] - 109000) / 2000) + 7;
	t = (s32)yuwp->recordScore[2][1] - 109000;
	yuwp->recordParam[2][1] = MAX0(t / 2000) + 6;
	yuwp->recordParam[2][2] = MAX0(((s32)yuwp->recordScore[2][2] - 109000) / 2000) + 4;
	t = (s32)yuwp->recordScore[2][3] - 109000;
	yuwp->recordParam[2][3] = MAX0(t / 2000) + 4;
	yuwp->recordParam[2][4] = MAX0(((s32)yuwp->recordScore[2][4] - 109000) / 2000) + 1;

	yuwp->recordOn[3][0] = 1;
	yuwp->recordOn[3][1] = 1;
	yuwp->recordOn[3][2] = 1;
	yuwp->recordOn[3][3] = 1;
	yuwp->recordOn[3][4] = 1;

	yuwp->recordScore[3][0] = 0x16BDE;
	yuwp->recordScore[3][1] = 0x16968;
	yuwp->recordScore[3][2] = 0x16382;
	yuwp->recordScore[3][3] = 0x1627E;
	yuwp->recordScore[3][4] = 0x15950;

	t = (s32)yuwp->recordScore[3][0] - 74000;
	yuwp->recordParam[3][0] = MAX0(t / 2000) + 7;
	t = (s32)yuwp->recordScore[3][1] - 74000;
	yuwp->recordParam[3][1] = MAX0(t / 2000) + 6;
	yuwp->recordParam[3][2] = MAX0(((s32)yuwp->recordScore[3][2] - 74000) / 2000) + 4;
	t = (s32)yuwp->recordScore[3][3] - 74000;
	yuwp->recordParam[3][3] = MAX0(t / 2000) + 3;
	yuwp->recordParam[3][4] = MAX0(((s32)yuwp->recordScore[3][4] - 74000) / 2000) + 4;
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
	u32 flags = yuwp->flags;
	Mtx mtx;
	GXColor c1, c2, c3, c4;
	if (flags & 4) y = -0x78;
	if (!(flags & 1) || !(flags & 2)) return;
	{
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
		iconNumberDispGx(mtx, yuwp->dispTokens, 0, c4);
		yuwp->dispTick++;
		if ((yuwp->dispTick & 3) == 0) {
			y = yuwp->tokens - yuwp->dispTokens;
			yuwp->dispTick = 0;
			if (monte_snd_flag == 0 && y != 0) {
				psndSFXOn(0x8CA);
				monte_snd_flag = 8;
			}
			if (y != 0) {
				y = y / 10;
				if (y == 0) {
					s32 sg;
					if ((s32)yuwp->tokens > (s32)yuwp->dispTokens) sg = 1; else sg = -1;
					y = sg;
				}
				yuwp->dispTokens += y;
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
	if (a != 0) yuwp->dispTokens = yuwp->tokens;
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_get_montemedal) {
	evtSetValue(event, event->args[0], yuwp->tokens);
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_get_montemedal_keep) {
	s32* args = event->args;
	if (yuwp->flags & 2) {
		evtSetValue(event, args[0], 0);
	} else {
		evtSetValue(event, args[0], yuwp->keptTokens);
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_add_montemedal_moto) {
	s32* args = event->args;
	evtGetValue(event, args[0]);
	if (yuwp->flags & 2) {
		yuwp->keptTokens += evtGetValue(event, args[1]);
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_montemedal_disp_onoff) {
	if (evtGetValue(event, event->args[0]) != 0) {
		yuwp->flags |= 1;
		yuwp->dispTokens = yuwp->tokens;
	} else {
		yuwp->flags &= ~1;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_montemedal_wait) {
	if ((s32)yuwp->dispTokens != yuwp->tokens) return EVT_RETURN_BLOCK;
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_montemedal_keep) {
	if (yuwp->flags & 2) {
		yuwp->keptTokens = yuwp->tokens;
		yuwp->tokens = 0;
		yuwp->dispTokens = 0;
		yuwp->flags &= ~2;
		yuwp->flags &= ~1;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_montemedal_return) {
	if (!(yuwp->flags & 2)) {
		yuwp->dispTokens = yuwp->tokens = yuwp->keptTokens;
		yuwp->flags |= 2;
		yuwp->flags |= 1;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_get_takeoutflag) {
	s32* args = event->args;
	if (yuwp->flags & 2) {
		evtSetValue(event, args[0], 1);
	} else {
		evtSetValue(event, args[0], 0);
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(yuugijou_set_yupflag) {
	if (evtGetValue(event, event->args[0]) != 0) {
		yuwp->flags |= 4;
	} else {
		yuwp->flags &= ~4;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(yuuminigame_window_end) {
	yuwp->flags |= 8;
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
	yuwp->flags &= ~8;
	evtEntryType(window_open, 0, 0, 0);
}

s32 evtYuuWindowEndChk(void) {
	return (yuwp->flags >> 3) & 1;
}
