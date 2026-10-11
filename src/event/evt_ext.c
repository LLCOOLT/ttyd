#include "evt/evt_ext.h"
#include "manager/evtmgr_cmd.h"
#include "driver/extdrv.h"

// s32 count, void* data, void* data2, s32 arg3, s32 arg4
USER_FUNC(evt_ext_entry) {
    s32* args = event->args;
    s32 count, arg3, arg4;
    void* data;
    void* data2;

    count = evtGetValue(event, args[0]);
    data = (void*)evtGetValue(event, args[1]);
    data2 = (void*)evtGetValue(event, args[2]);
    arg3 = evtGetValue(event, args[3]);
    arg4 = evtGetValue(event, args[4]);
    extEntry(count, data, data2, arg3, arg4);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_ext_reset) {
    extReset();
    return EVT_RETURN_DONE;
}
