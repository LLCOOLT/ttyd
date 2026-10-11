// include: manager/evtmgr_cmd.h
// proto: static USER_FUNC(disp_off);
static USER_FUNC(disp_off) {
    *(u16*)evtGetValue(event, event->args[0]) &= ~1;
    return EVT_RETURN_DONE;
}
