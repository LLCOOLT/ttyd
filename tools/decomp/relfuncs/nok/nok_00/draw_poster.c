// include: driver/npcdrv.h
// decl: typedef struct PosterWork { u32 flags; s32 group; s32 shape; } PosterWork;
// decl: PosterWork* poster;
// decl: void draw_poster(void* userdata, s32 group);
// decl: void animPoseDrawShape(s32 poseId, s32 shapeIdx);
// proto: void draw_poster(void* userdata, s32 group);
void draw_poster(void* userdata, s32 group) {
    NpcEntry* npc = npcNameToPtr("poster");

    if (group != poster->group || !(poster->flags & 1)) {
        return;
    }
    animPoseDrawShape(npc->poseId, poster->shape);
}
