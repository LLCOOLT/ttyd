// include: battle/battle.h
// include: system.h
// proto: USER_FUNC(mario_cannot_use_command);
USER_FUNC(mario_cannot_use_command) {
    BattleWork* wp = _battleWorkPointer;
    s32 r = irand(2);
    s32 var = event->args[0];
    s32 weapon = 0;

    switch (r) {
        case 0:
            wp->commandDisabled[0] = 3;
            weapon = 326;
            break;
        case 1:
            wp->commandDisabled[1] = 3;
            weapon = 329;
            break;
        case 2:
            wp->commandDisabled[2] = 3;
            weapon = 332;
            break;
    }
    event->lwData[0] = (s32)cmd_disable_string[r];
    evtSetValue(event, var, weapon);
    return EVT_RETURN_DONE;
}
