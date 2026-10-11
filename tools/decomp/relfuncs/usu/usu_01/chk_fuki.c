// include: driver/npcdrv.h
// include: string.h
// proto: USER_FUNC(chk_fuki);
USER_FUNC(chk_fuki) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    NpcEntry* npc = npcGetWorkPtr()->field_0x10;

    if (npc != NULL && strcmp(npc->description, name) == 0) {
        evtSetValue(event, args[1], TRUE);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[1], FALSE);
    return EVT_RETURN_DONE;
}
