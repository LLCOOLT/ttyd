// include: stdio.h
// proto: USER_FUNC(make_name);
USER_FUNC(make_name) {
    static char name[20];
    s32* args = event->args;

    s32 a = evtGetValue(event, args[0]);
    s32 b = evtGetValue(event, args[1]);

    sprintf(name, "S_shan_%02d_rou_%02d", a, b);
    evtSetValue(event, args[2], (s32)name);
    return EVT_RETURN_DONE;
}
