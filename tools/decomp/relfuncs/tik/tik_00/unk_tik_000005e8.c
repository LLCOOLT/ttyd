// include: manager/evtmgr_cmd.h
// include: driver/mapdrv.h
// proto: USER_FUNC(unk_tik_000005e8);
USER_FUNC(unk_tik_000005e8) {
    MapObject* obj = mapGetMapObj("supotto");

    obj->field_0x4[0] = 10;
    return EVT_RETURN_DONE;
}
