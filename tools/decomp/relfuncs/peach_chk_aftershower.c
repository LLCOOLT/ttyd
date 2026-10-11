// include: mario/mario.h
// proto: USER_FUNC(peach_chk_aftershower);
USER_FUNC(peach_chk_aftershower) {
    s32* args = event->args;

    if (marioGetPtr()->peachFlags & 0x10) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
