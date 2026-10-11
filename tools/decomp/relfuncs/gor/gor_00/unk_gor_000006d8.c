// include: driver/npcdrv.h
// proto: USER_FUNC(unk_gor_000006d8);
USER_FUNC(unk_gor_000006d8) {
    NpcWork* wp = npcGetWorkPtr();
    s32 i;
    s32 total = wp->total;
    NpcEntry* npc = wp->entries;

    for (i = 0; i < total; i++, npc++) {
        if (npc->flags & 1) {
            if (npc->moveEvent != NULL) {
                if (npc->regularEvtId != 0) {
                    evtDeleteID(npc->regularEvtId);
                }
                npc->regularEvtId = 0;
                npc->moveEvent = NULL;
            }
            npcDelete(npc);
        }
    }
    return EVT_RETURN_DONE;
}
