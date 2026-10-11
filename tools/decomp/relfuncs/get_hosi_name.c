// proto: USER_FUNC(get_hosi_name);
USER_FUNC(get_hosi_name) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    evtSetValue(event, args[1], hosi_name[idx * 2]);
    evtSetValue(event, args[2], hosi_name[idx * 2 + 1]);
    return EVT_RETURN_DONE;
}
