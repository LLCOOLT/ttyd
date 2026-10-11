// include: driver/npcdrv.h
// include: driver/animdrv.h
// proto: USER_FUNC(waku);
USER_FUNC(waku) {
    NpcEntry* npc;
    AnimationPose* pose;
    s32 i;

    // ロボット
    npc = npcNameToPtr_NoAssert("\x83\x8D\x83\x7B\x83\x62\x83\x67");
    if (npc != NULL) {
        pose = animPoseGetAnimPosePtr(npc->poseId);
        animPoseWorldPositionEvalOn(npc->poseId);
        if (pose->worldPositions != NULL) {
            Vec* positions = *pose->worldPositions;
            s32 idx = animPoseGetGroupIdx(npc->poseId, "locator17");

            if (npc->position.y >= 0.0f) {
                // 腕
                npcNameToPtr("\x98\x67")->position = positions[idx];
            } else {
                Vec hidden = {0.0f, -1000.0f, 0.0f};
                // 腕
                npcNameToPtr("\x98\x67")->position = hidden;
            }
            positions = *pose->worldPositions;
            for (i = 0; i < pose->numWorldPositions; i++) {
                positions[i] = (Vec){0.0f, -1000.0f, 0.0f};
            }
        }
    }

    // ロボット2
    npc = npcNameToPtr_NoAssert("\x83\x8D\x83\x7B\x83\x62\x83\x67\x82\x51");
    if (npc != NULL) {
        pose = animPoseGetAnimPosePtr(npc->poseId);
        animPoseWorldPositionEvalOn(npc->poseId);
        if (pose->worldPositions != NULL) {
            Vec* positions = *pose->worldPositions;
            s32 idx = animPoseGetGroupIdx(npc->poseId, "locator17");

            if (npc->position.y >= 0.0f) {
                // 腕2
                npcNameToPtr("\x98\x67\x82\x51")->position = positions[idx];
            } else {
                Vec hidden = {0.0f, -1000.0f, 0.0f};
                // 腕2
                npcNameToPtr("\x98\x67\x82\x51")->position = hidden;
            }
            positions = *pose->worldPositions;
            for (i = 0; i < pose->numWorldPositions; i++) {
                positions[i] = (Vec){0.0f, -1000.0f, 0.0f};
            }
        }
    }
    return EVT_RETURN_BLOCK;
}
