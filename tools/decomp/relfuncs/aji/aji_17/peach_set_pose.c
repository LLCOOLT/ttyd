// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// proto: static USER_FUNC(peach_set_pose);
static USER_FUNC(peach_set_pose) {
    const char* pose = (const char*)evtGetValue(event, event->args[0]);
    MarioWork* mario = marioGetPtr();
    marioChgPose(pose);
    return EVT_RETURN_DONE;
}
