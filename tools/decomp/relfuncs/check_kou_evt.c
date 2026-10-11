// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(check_kou_evt);
USER_FUNC(check_kou_evt) {
    s32* args = event->args;
    s32 value;
    s32 result;

    evtGetValue(event, args[0]);
    value = evtGetValue(event, args[1]);
    result = 0;
    if (evtGetValue(NULL, GSW(0)) == 0xA6 && evtGetValue(NULL, GSWF(4203)) == 1) {
        result = 1;
    }
    if (evtGetValue(NULL, GSW(0)) == 0xA8 && evtGetValue(NULL, GSWF(4206)) == 0 &&
        value == evtGetValue(NULL, GSWF(4205))) {
        result = 1;
    }
    evtSetValue(event, args[2], result);
    return EVT_RETURN_DONE;
}
