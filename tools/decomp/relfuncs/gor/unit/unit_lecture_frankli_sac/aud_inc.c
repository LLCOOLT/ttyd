// include: manager/evtmgr_cmd.h
// decl: void BattleAudienceAddAudienceNum(s32 num);
// proto: USER_FUNC(aud_inc);
USER_FUNC(aud_inc) {
    BattleAudienceAddAudienceNum(5);
    return EVT_RETURN_DONE;
}
