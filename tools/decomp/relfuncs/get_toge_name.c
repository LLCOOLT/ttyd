// proto: USER_FUNC(get_toge_name);
USER_FUNC(get_toge_name) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    evtSetValue(event, args[1], toge_data[idx * 2]);
    evtSetValue(event, args[2], toge_data[idx * 2 + 1]);
    return EVT_RETURN_DONE;
}
