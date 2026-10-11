// include: battle/battle.h
// include: system.h
// proto: USER_FUNC(party_cannot_use_command);
USER_FUNC(party_cannot_use_command) {
    BattleWork* wp = _battleWorkPointer;
    s32 r = irand(1);
    s32 var = event->args[0];
    s32 weapon = 0;

    switch (r) {
        case 0:
            wp->commandDisabled[3] = 3;
            weapon = 336;
            break;
        case 1:
            wp->commandDisabled[4] = 3;
            weapon = 332;
            break;
    }
    event->lwData[0] = (s32)cmd_disable_string[r + 3];
    evtSetValue(event, var, weapon);
    return EVT_RETURN_DONE;
}
