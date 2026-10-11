// decl: void statusWinForceClose(void);
// proto: static USER_FUNC(lect_status_off);
static USER_FUNC(lect_status_off) {
    statusWinForceClose();
    return EVT_RETURN_DONE;
}
