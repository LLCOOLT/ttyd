// decl: s32 xlw2[16];
// proto: USER_FUNC(enzan_lw_save2);
USER_FUNC(enzan_lw_save2) {
    s32 i;

    for (i = 0; i < 16; i++) {
        xlw2[i] = event->lwData[i];
    }
    return EVT_RETURN_DONE;
}
