// proto: static USER_FUNC(evt_shuryolight_wait_anim_end);
static USER_FUNC(evt_shuryolight_wait_anim_end) {
    s32 index = evtGetValue(event, event->args[0]);
    ShuryoLight* light = &slhp->lights[index];

    if (animPoseGetLoopTimes(light->npc->poseId) < 1.0f) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
