// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(senteresa_okure_move_init);
USER_FUNC(senteresa_okure_move_init) {
    s32* args = event->args;

    event->lwData[10] = evtGetValue(event, args[0]);
    event->lwData[11] = evtGetValue(event, args[1]);
    event->lwData[12] = evtGetValue(event, args[2]);
    event->lwData[13] = evtGetValue(event, args[3]);
    event->lwData[14] = evtGetValue(event, args[4]);
    event->lwData[15] = evtGetValue(event, args[5]);
    return EVT_RETURN_DONE;
}
