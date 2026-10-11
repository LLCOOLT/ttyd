// proto: static USER_FUNC(x_flag_add);
static USER_FUNC(x_flag_add) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    x_flag_data[index] += evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}
