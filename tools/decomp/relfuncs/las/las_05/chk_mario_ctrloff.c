// include: mario/mario.h
// proto: USER_FUNC(chk_mario_ctrloff);
USER_FUNC(chk_mario_ctrloff) {
    s32* args = event->args;

    evtSetValue(event, args[0], marioCtrlOffChk());
    return EVT_RETURN_DONE;
}
