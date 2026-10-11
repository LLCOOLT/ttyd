// include: battle/battle.h
// decl: s32 irand(s32 scalar);
// proto: static USER_FUNC(barriern_wawawa_set_target);
static USER_FUNC(barriern_wawawa_set_target) {
    s32* args = event->args;
    s32 unitIdx[10];
    s32 partIdx[10];
    s32 i;
    s32 num;

    i = 0;
    _battleWorkPointer->weaponTargets.currentTarget = 0;
    barriern_wawawa_get_target(&unitIdx[0], &partIdx[0]);
    while (TRUE) {
        if (unitIdx[i] == -1) {
            num = i;
            break;
        }
        i++;
        barriern_wawawa_get_next_target(&unitIdx[i], &partIdx[i]);
    }
    for (i = 0; i < 5; i++) {
        s32 r = irand(num);
        evtSetValue(event, *args++, unitIdx[r]);
        evtSetValue(event, *args++, partIdx[r]);
    }
    return EVT_RETURN_DONE;
}
