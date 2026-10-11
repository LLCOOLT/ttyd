// decl: static s32 dataadr[8];
// proto: USER_FUNC(goryuugijo_get_dataadr);
USER_FUNC(goryuugijo_get_dataadr) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);

    if (idx >= 8) {
        evtSetValue(event, args[1], 0);
    } else {
        evtSetValue(event, args[1], dataadr[idx]);
    }
    return EVT_RETURN_DONE;
}
