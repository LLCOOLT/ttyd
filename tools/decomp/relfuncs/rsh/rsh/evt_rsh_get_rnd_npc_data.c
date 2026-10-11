// proto: USER_FUNC(evt_rsh_get_rnd_npc_data);
USER_FUNC(evt_rsh_get_rnd_npc_data) {
    s32* args = event->args;
    s32 room = evtGetValue(event, args[0]);
    s32 group = evtGetValue(event, args[1]);
    s32 index = evtGetValue(event, args[2]);
    RshRndNpc* data = _get_rnd_npc_data(room, group, index);

    evtSetValue(event, args[3], (s32)data->name);
    evtSetValue(event, args[4], (s32)data->model);
    return EVT_RETURN_DONE;
}
