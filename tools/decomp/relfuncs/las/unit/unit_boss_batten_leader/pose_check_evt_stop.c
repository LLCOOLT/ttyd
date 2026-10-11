// decl: EventEntry* xevt;
// proto: USER_FUNC(pose_check_evt_stop);
USER_FUNC(pose_check_evt_stop) {
    evtDeleteID(xevt->eventId);
    return EVT_RETURN_DONE;
}
