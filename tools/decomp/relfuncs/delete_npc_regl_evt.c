// include: driver/npcdrv.h
// proto: static USER_FUNC(delete_npc_regl_evt);
static USER_FUNC(delete_npc_regl_evt) {
    NpcEntry* npc = npcNameToPtr((const char*)evtGetValue(event, event->args[0]));

    if (npc->regularEvtId != 0) {
        evtDeleteID(npc->regularEvtId);
        npc->moveEvent = NULL;
        npc->regularEvtId = 0;
    }
    return EVT_RETURN_DONE;
}
