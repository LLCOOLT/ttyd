// decl: char xmemo[20];
// proto: USER_FUNC(datastrcopy);
USER_FUNC(datastrcopy) {
    s8* s = (s8*)evtGetValue(event, event->args[0]);
    s32 i;

    for (i = 0; i < 16 && s[i] != 0; i++) {
        xmemo[i] = s[i];
    }
    xmemo[i] = 0;
    return EVT_RETURN_DONE;
}
