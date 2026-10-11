// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(fight_money);
USER_FUNC(fight_money) {
    s32* args = event->args;
    s32 rank = evtGetValue(event, args[0]);
    s32 win = evtGetValue(event, args[1]);
    s32 money;

    if (win) {
        if (rank > 10) {
            money = (s32)(0.99f + (2.0f + (21 - rank) / 2.0f));
        } else if (rank > 0) {
            money = (s32)(0.99f + (5.0f + (21 - rank) / 2.0f));
        } else {
            money = 20;
        }
    } else {
        money = 1;
    }
    evtSetValue(event, args[2], money);
    return EVT_RETURN_DONE;
}
