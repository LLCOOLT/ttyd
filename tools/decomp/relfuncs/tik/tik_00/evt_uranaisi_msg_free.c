// include: manager/evtmgr_cmd.h
// include: memory.h
// decl: char* uranaisi_msgp;
// proto: USER_FUNC(evt_uranaisi_msg_free);
USER_FUNC(evt_uranaisi_msg_free) {
    if (uranaisi_msgp == NULL) {
        return EVT_RETURN_DONE;
    }
    _mapFree(uranaisi_msgp);
    uranaisi_msgp = NULL;
    return EVT_RETURN_DONE;
}
