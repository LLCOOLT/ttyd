// include: manager/evtmgr_cmd.h
// include: driver/mapdrv.h
// decl: void mapGrpSetColor(const char* name, GXColor color);
// proto: USER_FUNC(card_xlu);
USER_FUNC(card_xlu) {
    const char* name = (const char*)evtGetValue(event, LW(2));

    if (isFirstCall) {
        event->userdata[0] = 255;
    }
    mapGrpSetColor(name, (GXColor){0xFF, 0xFF, 0xFF, event->userdata[0]});
    event->userdata[0] -= 8;
    if (event->userdata[0] < 0) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
