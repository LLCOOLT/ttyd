// include: driver/mobjdrv.h
// include: driver/animdrv.h
// proto: USER_FUNC(switch_set_alpha);
USER_FUNC(switch_set_alpha) {
    s32 alpha = evtGetValue(event, event->args[0]);
    MapObjectEntry* mobj = mobjNameToPtrNoAssert("switch");

    if (mobj == NULL) {
        return EVT_RETURN_DONE;
    }
    if (alpha > 0x24) {
        mobj->flags &= ~2;
    } else {
        mobj->flags |= 2;
    }
    animPoseSetMaterialEvtColor(mobj->poseId, (GXColor){255, 255, 255, alpha});
    animPoseSetMaterialFlagOn(mobj->poseId, 0x40);
    return EVT_RETURN_DONE;
}
