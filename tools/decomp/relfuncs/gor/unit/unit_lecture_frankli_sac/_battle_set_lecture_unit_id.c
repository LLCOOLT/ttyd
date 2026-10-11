// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// proto: static USER_FUNC(_battle_set_lecture_unit_id);
static USER_FUNC(_battle_set_lecture_unit_id) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 value;

    value = evtGetValue(event, *args++);
    wp->field_424 = value;
    return EVT_RETURN_DONE;
}
