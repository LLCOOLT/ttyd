// include: driver/npcdrv.h
// include: driver/animdrv.h
// proto: USER_FUNC(iri_12_paper_init);
USER_FUNC(iri_12_paper_init) {
    NpcEntry* npc = npcNameToPtr("\203}\203b\203L\203m");

    animPosePaperPeraOff(npc->poseId);
    animPoseSetMaterialLightFlagOff(npc->poseId, 1);
    return EVT_RETURN_DONE;
}
