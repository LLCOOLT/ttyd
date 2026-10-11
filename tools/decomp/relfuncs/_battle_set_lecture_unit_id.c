// include: battle/battle.h
// proto: USER_FUNC(_battle_set_lecture_unit_id);
USER_FUNC(_battle_set_lecture_unit_id) {
    BattleWork* wp = _battleWorkPointer;
    s32 value;

    value = evtGetValue(event, event->args[0]);
    wp->field_424 = value;
    return EVT_RETURN_DONE;
}
