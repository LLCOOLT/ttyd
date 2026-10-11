// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// proto: USER_FUNC(peach_chg_pose);
USER_FUNC(peach_chg_pose) {
    marioChgPose((const char*)evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}
