// proto: USER_FUNC(get_pos);
USER_FUNC(get_pos) {
    s32* args = event->args;
    s32 n = evtGetValue(event, args[0]);
    s32* t = tbl;
    s32 idx = t[n];

    evtSetValue(event, args[1], list[idx * 3 + 0]);
    evtSetValue(event, args[2], list[idx * 3 + 1]);
    evtSetValue(event, args[3], list[idx * 3 + 2]);
    return EVT_RETURN_DONE;
}
