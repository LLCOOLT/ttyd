// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// include: evt/evt_npc.h
// include: mario/mario.h
// include: system.h
// proto: USER_FUNC(nancy_block_func);
USER_FUNC(nancy_block_func) {
    MarioWork* mario = marioGetPtr();
    NpcEntry* npc = evtNpcNameToPtr(event, "\203i\203\223\203V\201[");
    f32 z;
    f32 base;
    f32 limit;

    ((f32*)event->lwData)[10] = npc->position.z;
    if (distABf(npc->position.x, npc->position.z, mario->position.x, mario->position.z) < 30.0f) {
        return EVT_RETURN_DONE;
    }
    if (distABf(npc->position.x, npc->position.z, mario->position.x, mario->position.z) > 130.0f) {
        return EVT_RETURN_DONE;
    }
    z = mario->position.z;
    base = ((f32*)event->lwData)[11];
    limit = z;
    if (z > 40.0f + base) {
        limit = 40.0f + base;
    }
    if (z < base - 40.0f) {
        limit = base - 40.0f;
    }
    if (npc->position.z <= limit) {
        npc->position.z += 4.0f;
        if (npc->position.z > limit) {
            npc->position.z = limit;
        }
    }
    if (npc->position.z > limit) {
        npc->position.z -= 4.0f;
        if (npc->position.z <= limit) {
            npc->position.z = limit;
        }
    }
    return EVT_RETURN_DONE;
}
