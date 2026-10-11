// include: manager/evtmgr_cmd.h
// include: driver/mapdrv.h
// proto: USER_FUNC(card_camid);
USER_FUNC(card_camid) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 camId = evtGetValue(event, args[1]);

    if (mapGetMapObj(name) != NULL) {
        mapGetMapObj(name)->field_0x4[1] = camId;
    }
    return EVT_RETURN_DONE;
}
