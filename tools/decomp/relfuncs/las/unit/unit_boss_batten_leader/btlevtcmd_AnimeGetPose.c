// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/animdrv.h
// proto: USER_FUNC(btlevtcmd_AnimeGetPose);
USER_FUNC(btlevtcmd_AnimeGetPose) {
    s32 id;
    s32* args = event->args;
    s32 partNo;
    BattleUnitPart* part;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    partNo = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, partNo);


    evtSetValue(event, args[2], (s32)animPoseGetCurrentAnim(part->poseId));
    return EVT_RETURN_DONE;
}
