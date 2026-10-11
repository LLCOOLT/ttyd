// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// include: evt/evt_npc.h
// proto: USER_FUNC(nancy_block_init_func);
USER_FUNC(nancy_block_init_func) {
    NpcEntry* npc = evtNpcNameToPtr(event, "\203i\203\223\203V\201[");
    f32 z;

    z = npc->position.z;
    ((f32*)event->lwData)[10] = z;
    ((f32*)event->lwData)[11] = z;
    npc->flags |= 0x400000;
    return EVT_RETURN_DONE;
}
