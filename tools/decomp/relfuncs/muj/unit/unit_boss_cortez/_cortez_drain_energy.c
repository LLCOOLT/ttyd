// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_audience.h
// include: system.h
// decl: typedef struct CortezWork { s16 state; s16 count; s16 audienceId[100]; s16 wait[100]; s16 timer[100]; s16 seq[100]; void* eff[100]; Vec srcPos[100]; Vec dstPos[100]; } CortezWork;
// include: driver/effdrv.h
// proto: USER_FUNC(_cortez_drain_energy);
USER_FUNC(_cortez_drain_energy) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];
    CortezWork* work;
    s32 i;

    id = BattleTransID(event, id);
    work = (CortezWork*)BattleGetUnitPtr(wp, id)->countersetWeapon;
    for (i = 0; i < 100; i++) {
        if (work->eff[i] != NULL) {
            effDelete(work->eff[i]);
            work->eff[i] = NULL;
        }
    }
    evtSetValue(event, out, work->count);
    return EVT_RETURN_DONE;
}
