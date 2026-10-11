// include: manager/evtmgr_cmd.h
// proto: static USER_FUNC(evt_shuryolight_get_anim_time);
static USER_FUNC(evt_shuryolight_get_anim_time) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    ShuryoLight* light = &slhp->lights[index];
    u8* data = (u8*)animPoseGetAnimDataPtr(light->npc->poseId);

    evtSetValue(event, args[1], 1000.0f * ((*(f32**)(data + 0x24))[2] - (*(f32**)(data + 0x24))[1]) / 60.0f);
    return EVT_RETURN_DONE;
}
