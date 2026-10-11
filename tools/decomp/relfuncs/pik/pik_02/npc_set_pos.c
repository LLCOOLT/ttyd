// include: evt/evt_npc.h
// include: manager/evtmgr_cmd.h
// proto: static USER_FUNC(npc_set_pos);
static USER_FUNC(npc_set_pos) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    NpcEntry* npc = evtNpcNameToPtr(event, name);

    npc->prevPosition = (Vec){x, y, z};
    npc->position = npc->prevPosition;
    return EVT_RETURN_DONE;
}
