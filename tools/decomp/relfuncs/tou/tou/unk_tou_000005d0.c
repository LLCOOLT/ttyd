// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// proto: USER_FUNC(unk_tou_000005d0);
USER_FUNC(unk_tou_000005d0) {
    s32* args = event->args;

    if (marioKeyOffChk() || marioCtrlOffChk()) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
