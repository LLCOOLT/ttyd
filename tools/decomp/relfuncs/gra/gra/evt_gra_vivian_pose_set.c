// proto: USER_FUNC(evt_gra_vivian_pose_set);
USER_FUNC(evt_gra_vivian_pose_set) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    partyPoseTbl[6][index] = (char*)evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}
