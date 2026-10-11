// include: stdio.h
// proto: USER_FUNC(make_name);
USER_FUNC(make_name) {
    s32* args = event->args;
    static char name[16];

    sprintf(name, "S_shan_rou_0%d", evtGetValue(event, args[0]));
    evtSetValue(event, args[1], (s32)name);
    return EVT_RETURN_DONE;
}
