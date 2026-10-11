// include: driver/npcdrv.h
// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// include: stdio.h
// proto: USER_FUNC(burst_chain);
USER_FUNC(burst_chain) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 id = evtGetValue(event, args[1]);
    NpcEntry* npc = npcNameToPtr(name);
    NpcEntry* a;
    NpcEntry* b;
    char buf[32];
    s32 i;
    f32 t;
    f32 dist;

    sprintf(buf, "\215\275%d_%d", id, 0);
    npcNameToPtr(buf)->position = npc->position;
    for (i = 0; i < 4; i++) {
        sprintf(buf, "\215\275%d_%d", id, i);
        a = npcNameToPtr(buf);
        sprintf(buf, "\215\275%d_%d", id, i + 1);
        b = npcNameToPtr(buf);
        b->position.y -= 3.0f;
        dist = PSVECDistance(&a->position, &b->position);
        t = 1.0f - 10.0f / dist;
        b->position.x += t * (a->position.x - b->position.x);
        b->position.y += t * (a->position.y - b->position.y);
        b->position.z += t * (a->position.z - b->position.z);
        if (b->position.x > 210.0f || b->position.x < -210.0f) {
            if (b->position.y < 0.0f) {
                b->position.y = 0.0f;
            }
        } else {
            if (b->position.y < 60.0f) {
                b->position.y = 60.0f;
            }
        }
    }
    return EVT_RETURN_BLOCK;
}
