// include: manager/evtmgr_cmd.h
// decl: void statusWinForceOff(void);
// proto: static USER_FUNC(evt_StatusClose);
static USER_FUNC(evt_StatusClose) {
    statusWinForceOff();
    return EVT_RETURN_DONE;
}
