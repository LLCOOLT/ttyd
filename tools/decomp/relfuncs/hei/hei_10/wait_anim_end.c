// include: driver/npcdrv.h
// include: driver/animdrv.h
// proto: USER_FUNC(wait_anim_end);
USER_FUNC(wait_anim_end) {
    NpcEntry* npc = npcNameToPtr("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223");

    if (isFirstCall) {
        event->lwData[15] = animPoseGetLoopTimes(npc->poseId);
    }
    if (event->lwData[15] == (s32)animPoseGetLoopTimes(npc->poseId)) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
