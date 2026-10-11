// decl: s32 xlw2[16];
// proto: USER_FUNC(enzan_lw_load2);
USER_FUNC(enzan_lw_load2) {
    s32 i;

    for (i = 0; i < 16; i++) {
        event->lwData[i] = xlw2[i];
    }
    return EVT_RETURN_DONE;
}
