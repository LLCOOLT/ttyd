// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_audience.h
// include: system.h
// decl: typedef struct CortezWork { s16 state; s16 count; s16 audienceId[100]; s16 wait[100]; s16 timer[100]; s16 seq[100]; void* eff[100]; Vec srcPos[100]; Vec dstPos[100]; } CortezWork;
// decl: void BattleAudienceAddTargetNum(f32 a, f32 b);
// proto: USER_FUNC(_cortez_recovery_audience);
USER_FUNC(_cortez_recovery_audience) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, *args++);
    CortezWork* work;
    BOOL done;
    s32 i;
    s32 aid;

    id = BattleTransID(event, id);
    work = (CortezWork*)BattleGetUnitPtr(wp, id)->countersetWeapon;
    if (isFirstCall) {
        work->state = 0;
    }
    switch (work->state) {
        case 0:
            for (i = 0; i < 100; i++) {
                if (work->audienceId[i] != -1) {
                    work->seq[i] = 0;
                }
            }
            work->state++;
        case 1:
            done = TRUE;
            for (i = 0; i < 100; i++) {
                if (work->audienceId[i] != -1) {
                    switch (work->seq[i]) {
                        case 0:
                            work->seq[i]++;
                            work->timer[i] = 0;
                        case 1:
                            work->timer[i]++;
                            done = TRUE;
                            break;
                    }
                }
            }
            if (!done) {
                break;
            }
            work->state++;
        case 2:
            for (i = 0; i < 100; i++) {
                aid = work->audienceId[i];
                if (aid != -1) {
                    BattleAudience_Delete(aid);
                    BattleAudienceAddTargetNum(0.0f, -1.0f);
                }
            }
            work->state++;
            return EVT_RETURN_DONE;
        default:
            return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
