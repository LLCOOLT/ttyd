// include: driver/mobjdrv.h
// include: driver/animdrv.h
// proto: USER_FUNC(mobj_color_off);
USER_FUNC(mobj_color_off) {
    MapObjectEntry* mobj = mobjNameToPtr((const char*)evtGetValue(event, event->args[0]));

    animPoseSetMaterialFlagOff(mobj->poseId, 0x40);
    return EVT_RETURN_DONE;
}
