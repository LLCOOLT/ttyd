// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// proto: USER_FUNC(set_npc_pos);
USER_FUNC(set_npc_pos) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    NpcEntry* npc = npcNameToPtr(name);

    npc->position.x = npc->prevPosition.x = x;
    npc->position.y = npc->prevPosition.y = y;
    npc->position.z = npc->prevPosition.z = z;
    return EVT_RETURN_DONE;
}
