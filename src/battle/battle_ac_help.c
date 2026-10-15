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
	if (_ac_help_disp) {
	}
}
void _ac_help_disp(CameraId cameraId, void *param)
{
  float new_var;
  u16 lines;
  const char *new_var3[2];
  BattleWork *wp = _battleWorkPointer;
  s32 width;
  u8 alpha;
  f32 x;
  f32 y;
  const char **help = &wp->acHelpMsg;
  alpha = 0xFF;
  if (wp->acHelpDispType == 1)
  {
    alpha = 0x80;
  }
  new_var3[0] = msgSearch(*help);
  if (!new_var3[0])
  {
    new_var3[0] = (0, "めっせーじがみつかりません");
  }
  new_var3[1] = new_var3[0];
  width = FontGetMessageWidthLine(new_var3[1], &lines);
  lines++;
  y = 0.0f;
  windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, alpha}, (x = y - (width / 2)) - 20.0f, (-145.0f) + ((lines - 1) * 29), width + 40, (lines * 29) + 1, 10.0f);
  y = -148.0f;
  FontDrawStart_alpha(alpha);
  FontDrawMessage(x, ((s32) y) + ((lines - 1) * 29), new_var3[1]);
}




























































