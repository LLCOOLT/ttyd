// include: manager/evtmgr_cmd.h
// decl: void BattleAudienceAddAudienceNum(s32 num);
// proto: USER_FUNC(aud_dec);
USER_FUNC(aud_dec) {
    BattleAudienceAddAudienceNum(-5);
    return EVT_RETURN_DONE;
}
