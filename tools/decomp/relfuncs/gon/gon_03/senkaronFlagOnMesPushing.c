// include: manager/evtmgr_cmd.h
// decl: s32 senkaronMesPushingFlag;
// proto: USER_FUNC(senkaronFlagOnMesPushing);
USER_FUNC(senkaronFlagOnMesPushing) {
    senkaronMesPushingFlag = 1;
    return EVT_RETURN_DONE;
}
