// include: battle/battle.h
// proto: USER_FUNC(atmic_teresa_id_set);
USER_FUNC(atmic_teresa_id_set) {
    s32 id = evtGetValue(event, event->args[0]);

    atmic_teresa_id[0] = BattleTransID(event, id);
    return EVT_RETURN_DONE;
}
