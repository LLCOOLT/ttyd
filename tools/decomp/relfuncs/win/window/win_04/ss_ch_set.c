// decl: static s32 ssf[3];
// proto: USER_FUNC(ss_ch_set);
USER_FUNC(ss_ch_set) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    ssf[index] = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}
