// include: battle/battle.h
// proto: USER_FUNC(_get_defence_ac_result);
USER_FUNC(_get_defence_ac_result) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 var = args[0];
    s32 result = 0;

    switch (wp->actionCommands.mDefenseResult) {
        case 1:
            result = 2;
            break;
        case 2:
            result = 3;
            break;
        case 4:
            result = 1;
            break;
        case 5:
            result = 0;
            break;
    }
    evtSetValue(event, var, result);
    return EVT_RETURN_DONE;
}
