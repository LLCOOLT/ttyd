// include: battle/battle.h
// proto: USER_FUNC(target_id_set);
USER_FUNC(target_id_set) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 parts = evtGetValue(event, args[1]);

    target_unit_id[0] = BattleTransID(event, id);
    target_parts_id[0] = parts;
    return EVT_RETURN_DONE;
}
