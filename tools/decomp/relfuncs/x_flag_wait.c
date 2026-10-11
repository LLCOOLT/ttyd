// decl: static s32 x_flag_data[2];
// proto: static USER_FUNC(x_flag_wait);
static USER_FUNC(x_flag_wait) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    s32 value = evtGetValue(event, args[1]);

    if (value == x_flag_data[index]) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
