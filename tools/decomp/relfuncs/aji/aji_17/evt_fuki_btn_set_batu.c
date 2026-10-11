// include: manager/evtmgr_cmd.h
// include: eff/eff_peach_fukidashi.h
// proto: USER_FUNC(evt_fuki_btn_set_batu);
USER_FUNC(evt_fuki_btn_set_batu) {
    effSetPeachFukiBatu((const char*)evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}
