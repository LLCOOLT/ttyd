// decl: s32 bts_x_flag_data;
// proto: USER_FUNC(bts_x_flag_get);
USER_FUNC(bts_x_flag_get) {
    evtSetValue(event, event->args[0], bts_x_flag_data);
    return EVT_RETURN_DONE;
}
