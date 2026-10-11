// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// proto: USER_FUNC(get_npc_color);
USER_FUNC(get_npc_color) {
    s32* args = event->args;
    NpcEntry* npc = npcNameToPtr((const char*)evtGetValue(event, args[0]));

    evtSetValue(event, args[1], npc->color.r);
    evtSetValue(event, args[2], npc->color.g);
    evtSetValue(event, args[3], npc->color.b);
    evtSetValue(event, args[4], npc->color.a);
    return EVT_RETURN_DONE;
}
