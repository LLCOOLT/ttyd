// include: manager/evtmgr_cmd.h
// decl: void statusAPBlink(s32 time);
// proto: USER_FUNC(blinkAP);
USER_FUNC(blinkAP) {
    statusAPBlink(160);
    return EVT_RETURN_DONE;
}
