// include: manager/evtmgr_cmd.h
// include: driver/msgdrv.h
// include: stdio.h
// decl: char* uranaisi_msgp;
// decl: s32 uranaisi_ryokin_rtn(s32 type);
// proto: USER_FUNC(evt_uranaisi_msg_set);
USER_FUNC(evt_uranaisi_msg_set) {
    s32* args = event->args;
    const char* msg = msgSearch((const char*)evtGetValue(event, args[0]));

    sprintf(uranaisi_msgp, msg, uranaisi_ryokin_rtn(0), uranaisi_ryokin_rtn(1), uranaisi_ryokin_rtn(2));
    evtSetValue(event, args[1], (s32)uranaisi_msgp);
    return EVT_RETURN_DONE;
}
