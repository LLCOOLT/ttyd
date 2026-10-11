// include: manager/evtmgr_cmd.h
// decl: extern s32 irai_msg_kakunin[];
// proto: USER_FUNC(irai_check_func);
USER_FUNC(irai_check_func) {
    if (event->lwData[0] != -1) {
        event->lwData[12] = irai_msg_kakunin[event->lwData[0] - 1];
        event->lwData[11] = event->lwData[0];
    } else {
        event->lwData[12] = 0;
        event->lwData[11] = -1;
    }
    return EVT_RETURN_DONE;
}
