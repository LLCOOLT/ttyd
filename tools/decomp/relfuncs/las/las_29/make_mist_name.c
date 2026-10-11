// include: manager/evtmgr_cmd.h
// include: stdio.h
// proto: USER_FUNC(make_mist_name);
USER_FUNC(make_mist_name) {
    static char name[8];
    s32* args = event->args;

    sprintf(name, "mist%d", evtGetValue(event, args[0]));
    evtSetValue(event, args[1], (s32)name);
    return EVT_RETURN_DONE;
}
