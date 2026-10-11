// include: system.h
// proto: static USER_FUNC(lect_push_a_check);
static USER_FUNC(lect_push_a_check) {
    s32* args = event->args;

    if (keyGetButton(0) & 0x100) {
        evtSetValue(event, args[0], TRUE);
    } else {
        evtSetValue(event, args[0], FALSE);
    }
    return EVT_RETURN_DONE;
}
