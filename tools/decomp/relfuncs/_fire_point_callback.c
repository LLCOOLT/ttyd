// include: battle/battle_unit.h
// include: driver/animdrv.h
// include: string.h
// proto: void _fire_point_callback(BattleUnitPart* part, s32 group);
void animPoseDrawShape(s32 poseId, s32 shapeIdx);

void _fire_point_callback(BattleUnitPart* part, s32 group) {
    BattleUnit* unit = part->mOwner;
    const char* name;
    s32 poseId;

    if (unit->work[0] == 0) {
        return;
    }
    poseId = part->poseId;
    switch (unit->work[1]) {
        case 0:
            name = "locator11";
            break;
        case 1:
            name = "locator10";
            break;
        case 2:
            name = "locator9";
            break;
        case 3:
        default:
            name = "locator8";
            break;
    }
    if (strcmp(name, animPoseGetGroupName(poseId, group)) == 0) {
        s32 shapePose = BtlUnit_GetPartsPtr(unit, 2)->poseId;
        s32 shape = animPoseGetShapeIdx(shapePose, "pPlaneShape3");
        animPoseDrawShape(shapePose, shape);
    }
}
