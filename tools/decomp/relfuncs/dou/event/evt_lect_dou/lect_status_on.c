// decl: void statusWinForceClose(void);
// proto: static USER_FUNC(lect_status_on);
static USER_FUNC(lect_status_on) {
    statusWinForceClose();
    return EVT_RETURN_DONE;
}
