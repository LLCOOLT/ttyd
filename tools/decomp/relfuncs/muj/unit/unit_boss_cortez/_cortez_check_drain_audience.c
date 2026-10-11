// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_audience.h
// include: system.h
// decl: typedef struct CortezWork { s16 state; s16 count; s16 audienceId[100]; s16 wait[100]; s16 timer[100]; s16 seq[100]; void* eff[100]; Vec srcPos[100]; Vec dstPos[100]; } CortezWork;
// proto: USER_FUNC(_cortez_check_drain_audience);
USER_FUNC(_cortez_check_drain_audience) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];
    s32 seat;
    CortezWork* work;
    s32 i;

    id = BattleTransID(event, id);
    work = (CortezWork*)BattleGetUnitPtr(wp, id)->countersetWeapon;
    work->count = 0;
    for (i = 0; i < 100; i++) {
        work->audienceId[i] = -1;
        work->eff[i] = NULL;
        work->seq[i] = 0;
        seat = 10 + (i / 10) * 20 + i % 10;
        if ((u8)BattleAudience_GetExist(seat)) {
            work->audienceId[i] = seat;
            work->count++;
        }
    }
    evtSetValue(event, out, work->count);
    return EVT_RETURN_DONE;
}
