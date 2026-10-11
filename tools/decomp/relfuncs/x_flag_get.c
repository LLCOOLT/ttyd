// proto: static USER_FUNC(x_flag_get);
static USER_FUNC(x_flag_get) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    evtSetValue(event, args[1], x_flag_data[index]);
    return EVT_RETURN_DONE;
}
