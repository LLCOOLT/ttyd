// include: manager/evtmgr_cmd.h
// decl: void statusWinForceOff(void);
// proto: USER_FUNC(status_gauge_force_off);
USER_FUNC(status_gauge_force_off) {
    statusWinForceOff();
    return EVT_RETURN_DONE;
}
