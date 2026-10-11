// decl: void statusWinForceCloseClear(void);
// proto: static USER_FUNC(lect_status_off);
static USER_FUNC(lect_status_off) {
    statusWinForceCloseClear();
    return EVT_RETURN_DONE;
}
