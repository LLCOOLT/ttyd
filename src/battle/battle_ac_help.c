#include "battle/battle_ac_help.h"
#include "battle/battle.h"
#include "battle/battle_audience.h"
#include "driver/dispdrv.h"
#include "driver/msgdrv.h"
#include "driver/windowdrv.h"
#include "manager/fontmgr.h"

void BattleAcHelpSetHelp(const char* msg) {
	_battleWorkPointer->acHelpMsg = msg;
}

void BattleAcHelpSetDispType(s32 type) {
	_battleWorkPointer->acHelpDispType = type;
	switch (type) {
		case 0:
			BattleAudience_WinSetActive(TRUE);
			break;
		default:
			BattleAudience_WinSetActive(FALSE);
			break;
	}
}

void BattleAcHelpInit(void) {
	//stubbed in retail
}

void _ac_help_disp(CameraId cameraId, void* param);

void BattleAcHelpMain(void) {
	BattleWork* wp = _battleWorkPointer;
	s32* type = &wp->acHelpDispType;

	if (wp->acHelpMsg && *type && !(wp->flags & 2)) {
		dispEntry(CAMERA_2D, 498.0f, 1, _ac_help_disp, NULL);
	}
}

void _ac_help_disp(CameraId cameraId, void* param) {
	static const GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
	BattleWork* wp = _battleWorkPointer;
	u16 lines;
	GXColor col;
	const char* msg;
	s32 width;
	u8 alpha;
	f32 x;
	f32 y;
	const char** help = &wp->acHelpMsg;

	alpha = 0xFF;
	if (wp->acHelpDispType == 1) {
		alpha = 0x80;
	}
	msg = msgSearch(*help);
	if (!msg) {
		msg = (0, "めっせーじがみつかりません");
	}
	width = FontGetMessageWidthLine(msg, &lines);
	lines++;
	col = color;
	col.a = alpha;
	y = 0.0f;
	x = y - width / 2;
	y = -148.0f;
	windowDispGX_Waku_col(0, col, x - 20.0f, -145.0f + (lines - 1) * 29, width + 40, lines * 29 + 1, 10.0f);
	FontDrawStart_alpha(alpha);
	FontDrawMessage(x, (s32)y + (lines - 1) * 29, msg);
}
