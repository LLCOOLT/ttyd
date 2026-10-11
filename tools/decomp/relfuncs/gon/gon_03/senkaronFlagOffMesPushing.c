// include: manager/evtmgr_cmd.h
// decl: s32 senkaronMesPushingFlag;
// proto: USER_FUNC(senkaronFlagOffMesPushing);
USER_FUNC(senkaronFlagOffMesPushing) {
    senkaronMesPushingFlag = 0;
    return EVT_RETURN_DONE;
}
