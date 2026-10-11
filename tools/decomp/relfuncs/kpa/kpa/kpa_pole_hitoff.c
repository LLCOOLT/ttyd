// include: manager/evtmgr_cmd.h
// include: driver/mobjdrv.h
// proto: USER_FUNC(kpa_pole_hitoff);
USER_FUNC(kpa_pole_hitoff) {
    MapObjectEntry* mobj = mobjNameToPtrNoAssert("pole");

    if (mobj != NULL) {
        mobj->flags |= 0x100;
    }
    return EVT_RETURN_DONE;
}
