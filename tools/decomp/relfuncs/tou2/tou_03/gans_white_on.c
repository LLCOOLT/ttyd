// include: driver/npcdrv.h
// include: driver/mapdrv.h
// include: driver/animdrv.h
// decl: s32 gans_alpha;
// decl: static void callback(MapTevCallbackInfo* info);
// proto: USER_FUNC(gans_white_on);
USER_FUNC(gans_white_on) {
    NpcEntry* npc = npcNameToPtr("\203K\203\223\203X");

    if (isFirstCall) {
        gans_alpha = 0;
        mapSetTevCallback(12, callback);
        animPoseSetMaterialFlagOn(npc->poseId, 0xC000000);
    }
    gans_alpha += 5;
    if (gans_alpha > 255) {
        gans_alpha = 255;
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
