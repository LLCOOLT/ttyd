// include: evt/evt_npc.h
// include: driver/npcdrv.h
// proto: USER_FUNC(evt_rsh_set_rnd_npc_talk_evt);
USER_FUNC(evt_rsh_set_rnd_npc_talk_evt) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    void* evt = (void*)evtGetValue(event, args[1]);

    evtNpcNameToPtr(event, name)->talkEvt = evt;
    return EVT_RETURN_DONE;
}
