// decl: s32 marioShipChanging(void);
// proto: USER_FUNC(funechange_func);
USER_FUNC(funechange_func) {
    s32* args = event->args;
    evtSetValue(event, args[0], marioShipChanging());
    return EVT_RETURN_DONE;
}
