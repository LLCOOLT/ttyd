// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: evt/evt_npc.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(evt_npc_set_anim_localtime);
USER_FUNC(evt_npc_set_anim_localtime) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 time = evtGetFloat(event, args[1]);

    animPoseSetLocalTime(evtNpcNameToPtr(event, name)->poseId, time);
    return EVT_RETURN_DONE;
}
