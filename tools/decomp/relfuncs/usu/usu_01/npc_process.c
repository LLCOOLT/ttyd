// include: driver/npcdrv.h
// proto: static USER_FUNC(npc_process);
static USER_FUNC(npc_process) {
    NpcWork* wp = npcGetWorkPtr();
    NpcEntry* npc = wp->entries;
    s32 i;

    for (i = 0; i < wp->total; i++, npc++) {
        if (npc->flags & 1) {
            if (npc->position.y <= -1000.0f) {
                npc->flags |= 0x800;
            } else {
                npc->flags &= ~0x800;
            }
        }
    }
    return EVT_RETURN_BLOCK;
}
