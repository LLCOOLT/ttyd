// include: driver/mobjdrv.h
// include: driver/animdrv.h
// proto: void majin_callback(s32 type);
void majin_callback(s32 type) {
    MapObjectEntry* mobj = mobjNameToPtr("mobj_box00");

    if (type == 0) {
        animPoseSetAnim(mobj->poseId, "A_2", TRUE);
    } else if (type == 5) {
        if (animPoseGetLoopTimes(mobj->poseId) >= 1.0f) {
            animPoseSetAnim(mobj->poseId, "A_2", TRUE);
        }
    } else if (type == 2) {
        animPoseSetAnim(mobj->poseId, "S_1", TRUE);
    }
}
