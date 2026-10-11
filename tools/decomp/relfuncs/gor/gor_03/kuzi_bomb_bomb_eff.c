// include: driver/npcdrv.h
// decl: void* effBombEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
// proto: USER_FUNC(kuzi_bomb_bomb_eff);
USER_FUNC(kuzi_bomb_bomb_eff) {
    s32* args = event->args;
    s32 type = evtGetValue(event, args[0]);
    s32 phase = evtGetValue(event, args[1]);
    NpcEntry* npc = npcNameToPtr("\203O\203\213\203\201\203{\203\200\225\272");

    if (type == 2 || type == 3) {
        return EVT_RETURN_DONE;
    }
    switch (phase) {
        case 0:
            if (npc->position.y > 25.0f) {
                effBombEntry(0, npc->position.x - 30.0f, npc->position.y, npc->position.z, 1.0f);
                if (type == 0) {
                    phase = 1;
                } else {
                    phase = 2;
                }
            }
            break;
        case 1:
            if (npc->position.y > 50.0f) {
                effBombEntry(0, 30.0f + npc->position.x, npc->position.y, npc->position.z, 1.0f);
                phase = 2;
            }
            break;
        case 2:
            if (npc->position.y > 75.0f) {
                effBombEntry(0, npc->position.x - 30.0f, npc->position.y, npc->position.z, 1.0f);
                phase = 3;
            }
            break;
        case 3:
            if (npc->position.y > 100.0f) {
                effBombEntry(0, 30.0f + npc->position.x, npc->position.y, npc->position.z, 1.0f);
                phase = 4;
            }
            break;
    }
    evtSetValue(event, args[2], phase);
    return EVT_RETURN_DONE;
}
