// decl: static s32 xlw[16];
// proto: USER_FUNC(enzan_lw_save);
USER_FUNC(enzan_lw_save) {
    s32 i;

    for (i = 0; i < 16; i++) {
        xlw[i] = event->lwData[i];
    }
    return EVT_RETURN_DONE;
}
