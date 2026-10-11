// include: driver/npcdrv.h
// include: evt/evt_npc.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(setup_npc_ex_para);
USER_FUNC(setup_npc_ex_para) {
    const char* name = (const char*)evtGetValue(event, event->args[0]);
    NpcEntry* npc = evtNpcNameToPtr(event, name);

    npc->territoryLoiter.y = 50.0f;
    npc->territoryHoming.y = 180.0f;
    return EVT_RETURN_DONE;
}
