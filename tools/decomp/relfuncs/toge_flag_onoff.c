// decl: u16 toge_flag;
// proto: USER_FUNC(toge_flag_onoff);
USER_FUNC(toge_flag_onoff) {
    s32* args = event->args;
    s32 bit = evtGetValue(event, args[0]);
    s32 on = evtGetValue(event, args[1]);

    if (on) {
        toge_flag |= (1 << bit);
    } else {
        toge_flag &= ~(1 << bit);
    }
    return EVT_RETURN_DONE;
}
