// include: driver/mobjdrv.h
// include: driver/animdrv.h
// include: string.h
// proto: static USER_FUNC(lect_mobj_set_nosysblend);
static USER_FUNC(lect_mobj_set_nosysblend) {
    const char* name = (const char*)evtGetValue(event, event->args[0]);
    MapObjectEntry* mobj;

    if (strcmp(name, "me") != 0) {
        mobj = mobjNameToPtr(name);
    } else {
        mobj = event->thisMapObj;
    }
    animPoseSetMaterialFlagOn(mobj->poseId, 0x1800);
    return EVT_RETURN_DONE;
}
