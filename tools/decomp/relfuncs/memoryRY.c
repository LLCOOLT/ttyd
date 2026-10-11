// include: evt/evt_npc.h
// proto: USER_FUNC(memoryRY);
USER_FUNC(memoryRY) {
    NpcEntry* npc = evtNpcNameToPtr(event, "me");

    npc->field_148 = npc->direction;
    return EVT_RETURN_DONE;
}
