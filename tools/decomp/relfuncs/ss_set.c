// decl: static s32 ssf;
// proto: USER_FUNC(ss_set);
USER_FUNC(ss_set) {
    ssf = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}
