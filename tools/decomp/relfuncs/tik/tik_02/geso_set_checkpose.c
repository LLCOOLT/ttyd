// include: evt/evt_npc.h
// proto: USER_FUNC(geso_set_checkpose);
USER_FUNC(geso_set_checkpose) {
    const char* name = (const char*)evtGetValue(event, event->args[0]);
    NpcEntry* npc = evtNpcNameToPtr(event, name);

    npc->field_10C = (const char*)geso_checkpose;
    return EVT_RETURN_DONE;
}
