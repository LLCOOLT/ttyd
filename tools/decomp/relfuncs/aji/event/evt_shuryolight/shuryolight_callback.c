// decl: void animPoseDrawShape(s32 poseId, s32 shapeIdx);
// decl: void animPoseSetDispCallBack(s32 poseId, void (*callback)(void* param, s32 group), void* param);
// proto: static void shuryolight_callback(void* param, s32 group);
static void shuryolight_callback(void* param, s32 group) {
    ShuryoLight* lights = param;
    s32 i;

    for (i = 0; i < 5; i++) {
        if (group == lights[i].group) {
            break;
        }
    }
    if (i != 5) {
        animPoseMain(lights[i].npc->poseId);
        animPoseDrawShape(lights[i].npc->poseId, lights[i].shape);
    }
}
