// include: driver/npcdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(confupose);
USER_FUNC(confupose) {
    s32* args = event->args;
    NpcEntry* npc = npcNameToPtr((const char*)evtGetValue(event, args[0]));

    evtSetValue(event, args[1], (s32)npc->tribe->confuseAnimation);
    return EVT_RETURN_DONE;
}
