// include: driver/mobjdrv.h
// include: driver/animdrv.h
// proto: USER_FUNC(mobj_set_color);
USER_FUNC(mobj_set_color) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 r = evtGetValue(event, args[1]);
    s32 g = evtGetValue(event, args[2]);
    s32 b = evtGetValue(event, args[3]);
    MapObjectEntry* mobj = mobjNameToPtr(name);

    animPoseSetMaterialEvtColor(mobj->poseId, (GXColor){r, g, b, 255});
    animPoseSetMaterialFlagOn(mobj->poseId, 0x40);
    return EVT_RETURN_DONE;
}
