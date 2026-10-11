// include: manager/evtmgr_cmd.h
// include: memory.h
// include: string.h
// decl: char* uranaisi_msgp;
// proto: USER_FUNC(evt_uranaisi_msg_alloc);
USER_FUNC(evt_uranaisi_msg_alloc) {
    uranaisi_msgp = _mapAlloc(0x100);
    memset(uranaisi_msgp, 0, 0x100);
    return EVT_RETURN_DONE;
}
