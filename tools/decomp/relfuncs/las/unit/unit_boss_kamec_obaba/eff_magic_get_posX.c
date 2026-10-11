// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(eff_magic_get_posX);
USER_FUNC(eff_magic_get_posX) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);

    evtSetFloat(event, args[1], ((f32*)((EffectEntry*)unit->work[4])->userdata)[4]);
    return EVT_RETURN_DONE;
}
