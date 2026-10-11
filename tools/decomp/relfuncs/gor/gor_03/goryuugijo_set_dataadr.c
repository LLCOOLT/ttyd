// decl: static s32 dataadr[8];
// proto: USER_FUNC(goryuugijo_set_dataadr);
USER_FUNC(goryuugijo_set_dataadr) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);

    if (idx < 8) {
        dataadr[idx] = evtGetValue(event, args[1]);
    }
    return EVT_RETURN_DONE;
}
