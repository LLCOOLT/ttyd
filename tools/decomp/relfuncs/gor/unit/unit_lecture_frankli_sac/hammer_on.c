// include: manager/evtmgr_cmd.h
// include: battle/battle_audience.h
// decl: BOOL BattleAudienceItemOn(s32 index, u16 itemId, s32 numItems);
// proto: USER_FUNC(hammer_on);
USER_FUNC(hammer_on) {
    BattleAudience* aud = BattleAudienceBaseGetPtr();
    BattleAudienceMember* member = BattleAudienceGetPtr(48);

    aud->flags &= ~0x40000;
    if (BattleAudienceItemOn(48, 0xEF, 1) == TRUE) {
        member->flags &= ~0x200;
        aud->flags |= 0x40000;
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
