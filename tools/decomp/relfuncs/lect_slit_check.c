// include: mario/mario.h
// proto: static USER_FUNC(lect_slit_check);
static USER_FUNC(lect_slit_check) {
    s32* args = event->args;

    if (marioGetPtr()->flags & 0x100000) {
        evtSetValue(event, args[0], TRUE);
    } else {
        evtSetValue(event, args[0], FALSE);
    }
    return EVT_RETURN_DONE;
}
