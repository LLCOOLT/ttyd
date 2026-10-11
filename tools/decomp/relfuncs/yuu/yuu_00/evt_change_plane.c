// include: manager/evtmgr_cmd.h
// include: mario/mario_motion.h
// proto: USER_FUNC(evt_change_plane);
USER_FUNC(evt_change_plane) {
    marioChgMot(0x18);
    return EVT_RETURN_DONE;
}
