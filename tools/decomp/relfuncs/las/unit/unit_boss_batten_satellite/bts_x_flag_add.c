// decl: s32 bts_x_flag_data;
// proto: USER_FUNC(bts_x_flag_add);
USER_FUNC(bts_x_flag_add) {
    bts_x_flag_data += evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}
