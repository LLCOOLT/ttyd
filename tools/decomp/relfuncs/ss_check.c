// include: manager/evtmgr_cmd.h
// decl: static s32 ssf;
// proto: USER_FUNC(ss_check);
USER_FUNC(ss_check) {
    evtSetFloat(event, event->args[0], ssf);
    return EVT_RETURN_DONE;
}
