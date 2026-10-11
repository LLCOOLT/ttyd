// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: memory.h
// include: string.h
// decl: typedef struct PosterWork { u32 flags; s32 group; s32 shape; } PosterWork;
// decl: PosterWork* poster;
// decl: void draw_poster(void* userdata, s32 group);
// decl: void animPoseDrawShape(s32 poseId, s32 shapeIdx);
// decl: void animPoseSetDispCallBack(s32 poseId, void (*callback)(void*, s32), void* userdata);
// proto: USER_FUNC(pposter_init);
USER_FUNC(pposter_init) {
    NpcEntry* npc;

    poster = _mapAlloc(sizeof(PosterWork));
    memset(poster, 0, sizeof(PosterWork));
    poster->shape = animPoseGetShapeIdx(npcNameToPtr("poster")->poseId, "pPlaneShape2");
    // ノコノコA
    npc = npcNameToPtr("\x83\x6D\x83\x52\x83\x6D\x83\x52\x41");
    poster->group = animPoseGetGroupIdx(npc->poseId, "locator7");
    animPoseSetDispCallBack(npc->poseId, draw_poster, NULL);
    return EVT_RETURN_DONE;
}
