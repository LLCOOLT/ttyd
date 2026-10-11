// include: stdio.h
// decl: static char name[8];
// proto: USER_FUNC(make_name);
USER_FUNC(make_name) {
    s32* args = event->args;

    sprintf(name, "hi%d", evtGetValue(event, args[0]));
    evtSetValue(event, args[1], (s32)name);
    return EVT_RETURN_DONE;
}
