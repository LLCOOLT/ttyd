// include: battle/battle_unit.h
// include: driver/animdrv.h
// include: string.h
// decl: void animPoseDrawShape(s32 poseId, s32 shapeIdx);
// proto: void _light_point_callback(BattleUnitPart* part, s32 group);
void _light_point_callback(BattleUnitPart* part, s32 group) {
    BattleUnit* unit;
    s32 poseId;
    s32 idx;
    s32 shape;


    poseId = part->poseId;
    unit = part->mOwner;


    if (strcmp("locator6", animPoseGetGroupName(poseId, group)) == 0) {
        idx = 0;
    } else if (strcmp("locator9", animPoseGetGroupName(poseId, group)) == 0) {
        idx = 1;
    } else if (strcmp("locator8", animPoseGetGroupName(poseId, group)) == 0) {
        idx = 2;
    } else if (strcmp("locator7", animPoseGetGroupName(poseId, group)) == 0) {
        idx = 3;
    } else if (strcmp("locator5", animPoseGetGroupName(poseId, group)) == 0) {
        idx = 4;
    } else {
        idx = -1;
    }
    switch (idx) {
        case 0:
            {
                s32 pose = BtlUnit_GetPartsPtr(unit, 3)->poseId;
                s32 sh = animPoseGetShapeIdx(pose, "pPlaneShape34");
                animPoseDrawShape(pose, sh);
            }
            break;
        case 1:
            {
                s32 pose = BtlUnit_GetPartsPtr(unit, 4)->poseId;
                s32 sh = animPoseGetShapeIdx(pose, "pPlaneShape37");
                animPoseDrawShape(pose, sh);
            }
            break;
        case 2:
            {
                s32 pose = BtlUnit_GetPartsPtr(unit, 5)->poseId;
                s32 sh = animPoseGetShapeIdx(pose, "pPlaneShape36");
                animPoseDrawShape(pose, sh);
            }
            break;
        case 3:
            {
                s32 pose = BtlUnit_GetPartsPtr(unit, 6)->poseId;
                s32 sh = animPoseGetShapeIdx(pose, "pPlaneShape35");
                animPoseDrawShape(pose, sh);
            }
            break;
        case 4:
            {
                s32 pose = BtlUnit_GetPartsPtr(unit, 7)->poseId;
                s32 sh = animPoseGetShapeIdx(pose, "pPlaneShape36");
                animPoseDrawShape(pose, sh);
            }
            break;
    }
}
