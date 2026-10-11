// include: driver/mobjdrv.h
// include: driver/animdrv.h
// proto: USER_FUNC(anim_tevcallback_mobj);
USER_FUNC(anim_tevcallback_mobj) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 flag = evtGetValue(event, args[1]);
    MapObjectEntry* mobj = mobjNameToPtrNoAssert(name);

    if (mobj == NULL) {
        return EVT_RETURN_DONE;
    }
    animPoseSetMaterialFlagOn(mobj->poseId, (flag & 0xF) << 24);
    return EVT_RETURN_DONE;
}
