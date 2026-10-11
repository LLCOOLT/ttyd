// include: mario/mario.h
// proto: USER_FUNC(unk_hei_000002a8);
USER_FUNC(unk_hei_000002a8) {
    s32* args = event->args;

    if (marioKeyOffChk() || marioCtrlOffChk()) {
        evtSetValue(event, args[0], TRUE);
    } else {
        evtSetValue(event, args[0], FALSE);
    }
    return EVT_RETURN_DONE;
}
