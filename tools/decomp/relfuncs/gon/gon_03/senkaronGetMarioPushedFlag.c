// include: manager/evtmgr_cmd.h
// decl: s32 marioPushedFlag;
// proto: USER_FUNC(senkaronGetMarioPushedFlag);
USER_FUNC(senkaronGetMarioPushedFlag) {
    evtSetValue(event, event->args[0], marioPushedFlag);
    return EVT_RETURN_DONE;
}
