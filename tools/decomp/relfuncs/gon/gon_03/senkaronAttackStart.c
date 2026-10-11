// include: manager/evtmgr_cmd.h
// decl: s32 senkaronAttackStartFlag;
// proto: USER_FUNC(senkaronAttackStart);
USER_FUNC(senkaronAttackStart) {
    senkaronAttackStartFlag = 1;
    return EVT_RETURN_DONE;
}
