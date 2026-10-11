// include: stdio.h
// proto: USER_FUNC(make_name);
USER_FUNC(make_name) {
    s32* args = event->args;
    static char name[64];

    sprintf(name, "S_hikari%d", evtGetValue(event, args[0]));
    evtSetValue(event, args[1], (s32)name);
    return EVT_RETURN_DONE;
}
