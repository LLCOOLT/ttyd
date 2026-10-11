// decl: static s32 xlw[16];
// proto: static USER_FUNC(enzan_lw_load);
static USER_FUNC(enzan_lw_load) {
    s32 i;

    for (i = 0; i < 16; i++) {
        event->lwData[i] = xlw[i];
    }
    return EVT_RETURN_DONE;
}
