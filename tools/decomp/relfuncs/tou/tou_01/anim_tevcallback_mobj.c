// include: driver/mobjdrv.h
// include: driver/animdrv.h
// proto: static USER_FUNC(anim_tevcallback_mobj);
static USER_FUNC(anim_tevcallback_mobj) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 index = evtGetValue(event, args[1]);
    MapObjectEntry* obj = mobjNameToPtrNoAssert(name);

    if (obj == NULL) {
        return EVT_RETURN_DONE;
    }
    animPoseSetMaterialFlagOn(obj->poseId, (index & 0xF) << 24);
    return EVT_RETURN_DONE;
}
