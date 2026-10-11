// decl: s32 bts_x_flag_data;
// proto: USER_FUNC(bts_x_flag_wait);
USER_FUNC(bts_x_flag_wait) {
    s32 v = evtGetValue(event, event->args[0]);

    if (v == bts_x_flag_data) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
