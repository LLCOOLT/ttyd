// decl: void statusWinForceCloseClear(void);
// proto: static USER_FUNC(lect_status_on);
static USER_FUNC(lect_status_on) {
    statusWinForceCloseClear();
    return EVT_RETURN_DONE;
}
