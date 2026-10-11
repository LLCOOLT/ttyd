// include: driver/npcdrv.h
// include: string.h
// proto: USER_FUNC(unk_rsh_00002634);
USER_FUNC(unk_rsh_00002634) {
    s32 alpha = evtGetValue(event, event->args[0]);
    NpcWork* wp = npcGetWorkPtr();
    s32 i;
    NpcEntry* npc;

    for (i = 0, npc = wp->entries; i < wp->total; i++, npc++) {
        // 店員
        if ((npc->flags & 1) && (npc->flags & 2) && strcmp(npc->description, "\x93\x58\x88\xF5") != 0) {
            npcSetColor(npc->description, (GXColor){0xFF, 0xFF, 0xFF, alpha});
        }
    }
    return EVT_RETURN_DONE;
}
