// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// proto: USER_FUNC(peach_dance_after_fail);
USER_FUNC(peach_dance_after_fail) {
    marioChgPoseTime("P_O_F_1", 20);
    return EVT_RETURN_DONE;
}
