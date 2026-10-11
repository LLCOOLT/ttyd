// decl: static u8* _ap;
// proto: USER_FUNC(alpha_set_func);
USER_FUNC(alpha_set_func) {
    *_ap = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}
