// include: driver/npcdrv.h
// proto: static USER_FUNC(delete_npc_regl_evt);
static USER_FUNC(delete_npc_regl_evt) {
    NpcEntry* npc = npcNameToPtr_NoAssert((const char*)evtGetValue(event, event->args[0]));

    if (npc == NULL) {
        return EVT_RETURN_DONE;
    }
    if (npc->regularEvtId != 0) {
        evtDeleteID(npc->regularEvtId);
        npc->moveEvent = NULL;
        npc->regularEvtId = 0;
    } else if (npc->moveEvent != NULL) {
        npc->moveEvent = NULL;
    }
    return EVT_RETURN_DONE;
}
