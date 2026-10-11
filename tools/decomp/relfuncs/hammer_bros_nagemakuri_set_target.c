// include: battle/battle.h
// include: system.h
// proto: USER_FUNC(hammer_bros_nagemakuri_set_target);
USER_FUNC(hammer_bros_nagemakuri_set_target) {
    s32* args = event->args;
    s32 unitIdx[20];
    s32 partIdx[20];
    s32 i;
    s32 num;

    i = 0;
    _battleWorkPointer->weaponTargets.currentTarget = 0;
    hammer_bros_get_target(&unitIdx[0], &partIdx[0]);
    while (TRUE) {
        if (unitIdx[i] == -1) {
            num = i;
            break;
        }
        i++;
        hammer_bros_get_next_target(&unitIdx[i], &partIdx[i]);
    }
    for (i = 0; i < 5; i++) {
        s32 r = irand(num);
        evtSetValue(event, *args++, unitIdx[r]);
        evtSetValue(event, *args++, partIdx[r]);
    }
    return EVT_RETURN_DONE;
}
