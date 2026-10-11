// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// proto: USER_FUNC(get_ac_result);
USER_FUNC(get_ac_result) {
    evtSetValue(event, event->args[0], _battleWorkPointer->field_19064[0]);
    return EVT_RETURN_DONE;
}
