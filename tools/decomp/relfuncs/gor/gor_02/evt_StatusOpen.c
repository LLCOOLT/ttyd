// include: manager/evtmgr_cmd.h
// decl: void statusWinForceOpen(void);
// proto: static USER_FUNC(evt_StatusOpen);
static USER_FUNC(evt_StatusOpen) {
    statusWinForceOpen();
    return EVT_RETURN_DONE;
}
