// include: battle/battle.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// proto: USER_FUNC(eff_ice_barrier_end);
USER_FUNC(eff_ice_barrier_end) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);

    if (unit->work[1] != 0) {
        effDelete((EffectEntry*)unit->work[1]);
        unit->work[1] = 0;
    }
    return EVT_RETURN_DONE;
}
