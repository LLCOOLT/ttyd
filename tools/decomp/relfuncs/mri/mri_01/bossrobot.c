// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: driver/dispdrv.h
// include: memory.h
// include: dolphin/mtx.h
// decl: static u8* bp;
// proto: USER_FUNC(bossrobot);
USER_FUNC(bossrobot) {
    u8 alpha = evtGetValue(event, event->args[0]);
    NpcEntry* robot = npcNameToPtr("\203{\203X\203\215\203{\203b\203g");
    NpcEntry* batu = npcNameToPtr("\203{\203X\203\215\203{\203b\203g\203o\203c");
    NpcEntry* maru = npcNameToPtr("\203{\203X\203\215\203{\203b\203g\203}\203\213");
    AnimationPose* pose;
    Mtx* mtxs;
    s32 idx;
    s32 i;
    Vec pos;

    if (isFirstCall) {
        bp = _mapAlloc(1);
        animPoseWorldMatrixEvalOn(robot->poseId);
        pose = animPoseGetAnimPosePtr(robot->poseId);
        mtxs = *pose->worldMatrices;
        for (i = 0; i < pose->numWorldMatrices; i++) {
            PSMTXTrans(mtxs[i], 0.0f, -1000.0f, 0.0f);
        }
    }
    mtxs = *animPoseGetAnimPosePtr(robot->poseId)->worldMatrices;
    idx = animPoseGetGroupIdx(robot->poseId, "locator17");
    maru->position = (Vec){mtxs[idx][0][3], mtxs[idx][1][3], mtxs[idx][2][3]};
    pos = (Vec){0.0f, 0.0f, 0.0f};
    *bp = alpha;
    dispEntry(CAMERA_3D, dispCalcZ(&pos), 0, bossrobot_batu, bp);
    dispEntry(CAMERA_3D, dispCalcZ(&pos), 1, bossrobot_batu, bp);
    dispEntry(CAMERA_3D, dispCalcZ(&pos), 2, bossrobot_batu, bp);
    return EVT_RETURN_BLOCK;
}
