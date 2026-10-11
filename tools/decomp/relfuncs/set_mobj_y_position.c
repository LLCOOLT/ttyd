// include: driver/mobjdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(set_mobj_y_position);
USER_FUNC(set_mobj_y_position) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    MapObjectEntry* mobj = mobjNameToPtr(name);

    mobj->position.y = y;
    mobjCalcMtx(mobj);
    return EVT_RETURN_DONE;
}
