// include: driver/npcdrv.h
// include: driver/animdrv.h
// proto: USER_FUNC(anim_tevcallback);
USER_FUNC(anim_tevcallback) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 flag = evtGetValue(event, args[1]);
    NpcEntry* npc = npcNameToPtr_NoAssert(name);

    if (npc == NULL) {
        return EVT_RETURN_DONE;
    }
    animPoseSetMaterialFlagOn(npc->poseId, (flag & 0xF) << 24);
    return EVT_RETURN_DONE;
}
