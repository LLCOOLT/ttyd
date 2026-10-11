// include: manager/evtmgr_cmd.h
// decl: s32 senkaronEscapeFlag;
// proto: USER_FUNC(senkaronToEscape);
USER_FUNC(senkaronToEscape) {
    senkaronEscapeFlag = 1;
    return EVT_RETURN_DONE;
}
