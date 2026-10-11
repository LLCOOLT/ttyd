// include: driver/npcdrv.h
// include: driver/mapdrv.h
// include: driver/animdrv.h
// proto: USER_FUNC(gans_white_off);
USER_FUNC(gans_white_off) {
    NpcEntry* npc = npcNameToPtr("\203K\203\223\203X");

    mapSetTevCallback(12, NULL);
    animPoseSetMaterialFlagOff(npc->poseId, 0xC000000);
    return EVT_RETURN_DONE;
}
