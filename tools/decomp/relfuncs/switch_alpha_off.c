// include: driver/mobjdrv.h
// include: driver/animdrv.h
// proto: USER_FUNC(switch_alpha_off);
USER_FUNC(switch_alpha_off) {
    MapObjectEntry* mobj = mobjNameToPtrNoAssert("switch");

    if (mobj == NULL) {
        return EVT_RETURN_DONE;
    }
    mobj->flags &= ~2;
    animPoseSetMaterialEvtColor(mobj->poseId, (GXColor){255, 255, 255, 255});
    animPoseSetMaterialFlagOff(mobj->poseId, 0x40);
    return EVT_RETURN_DONE;
}
