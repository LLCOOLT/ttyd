// include: driver/mobjdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(mobj_set_ry);
USER_FUNC(mobj_set_ry) {
    s32* args = event->args;
    MapObjectEntry* mobj = mobjNameToPtr((const char*)evtGetValue(event, args[0]));

    mobj->rotation.y = evtGetFloat(event, args[1]);
    return EVT_RETURN_DONE;
}
