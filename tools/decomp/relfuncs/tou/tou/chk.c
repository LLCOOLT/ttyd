// include: manager/evtmgr_cmd.h
// decl: BOOL partyChkJoin(s32 id);
// proto: USER_FUNC(chk);
USER_FUNC(chk) {
    s32* args = event->args;
    evtSetValue(event, args[0], partyChkJoin(4) != 0);
    return EVT_RETURN_DONE;
}
