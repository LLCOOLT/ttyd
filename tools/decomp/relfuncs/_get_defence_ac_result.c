// include: battle/battle.h
// proto: USER_FUNC(_get_defence_ac_result);
USER_FUNC(_get_defence_ac_result) {
    s32* args = event->args;
    s32 result = 0;
    BattleWork* wp = _battleWorkPointer;

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
    evtSetValue(event, args[0], result);
    return EVT_RETURN_DONE;
}
