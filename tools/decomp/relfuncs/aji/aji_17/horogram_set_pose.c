// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: mario/mario.h
// include: string.h
// proto: USER_FUNC(horogram_set_pose);
USER_FUNC(horogram_set_pose) {
    char name[24];
    const char* pose = (const char*)evtGetValue(event, event->args[0]);
    NpcEntry* npc = npcNameToPtr("\203z\203\215\203O\203\211\203\200");
    NpcEntry* npc2 = npcNameToPtr("\203z\203\215\203O\203\211\203\2002");
    MarioWork* mario = marioGetPtr();

    animPoseSetAnim(npc->poseId, pose, TRUE);
    strcpy(name, pose);
    strcat(name, "R");
    animPoseSetAnim(npc2->poseId, name, TRUE);
    return EVT_RETURN_DONE;
}
