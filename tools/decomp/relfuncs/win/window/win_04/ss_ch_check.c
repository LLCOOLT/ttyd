// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(ss_ch_check);
USER_FUNC(ss_ch_check) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    evtSetFloat(event, args[1], ssf[index]);
    return EVT_RETURN_DONE;
}
