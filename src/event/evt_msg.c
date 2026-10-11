#include "evt/evt_msg.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"

void evt_msg_init(void) {
	//stubbed in retail
}

void msgWindow_ForceClose(s32 id);

USER_FUNC(evt_msg_close) {
	msgWindow_ForceClose(evtGetValue(event, *event->args));
	return EVT_RETURN_DONE;
}
