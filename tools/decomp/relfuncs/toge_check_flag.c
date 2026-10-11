// decl: u16 toge_flag;
// proto: USER_FUNC(toge_check_flag);
USER_FUNC(toge_check_flag) {
    s32* args = event->args;
    s32 bit = evtGetValue(event, args[0]);

    evtSetValue(event, args[1], toge_flag & (1 << bit));
    return EVT_RETURN_DONE;
}
