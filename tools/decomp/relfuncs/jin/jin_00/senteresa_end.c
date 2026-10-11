// include: manager/evtmgr_cmd.h
// include: driver/extdrv.h
// proto: USER_FUNC(senteresa_end);
USER_FUNC(senteresa_end) {
    extReset();
    return EVT_RETURN_DONE;
}
