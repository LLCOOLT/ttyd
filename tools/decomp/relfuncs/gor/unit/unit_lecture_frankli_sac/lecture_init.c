// include: manager/evtmgr_cmd.h
// include: battle/battle_audience.h
// decl: s32* BattleBreakSlotGetPtr(void);
// proto: static USER_FUNC(lecture_init);
static USER_FUNC(lecture_init) {
    s32* slot = BattleBreakSlotGetPtr();
    BattleAudience* aud = BattleAudienceBaseGetPtr();
    s32 seats[11] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 48};
    s32 seat;
    s32 i;

    *slot |= 1;
    aud->flags |= 0x40000;
    for (i = 0; i < 200; i++) {
        BattleAudience_Delete(i);
    }
    for (i = 0; i < 11; i++) {
        if ((seat = seats[i]) != 48) {
            BattleAudience_Entry(seat, 0, 0);
        } else {
            BattleAudience_Entry(seat, 3, 0);
            BattleAudienceGetPtr(seats[i])->flags |= 0x200;
        }
    }
    return EVT_RETURN_DONE;
}
