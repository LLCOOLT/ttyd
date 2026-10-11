// include: driver/effdrv.h
// include: driver/npcdrv.h
// decl: EffectEntry* effMarioBalloonEntry(s32 type, NpcEntry* npc);
// decl: static EffectEntry* eff;
// decl: NpcEntry* npc;
// proto: USER_FUNC(desk_talk_func);
USER_FUNC(desk_talk_func) {
    s32* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    s32 prev = evtGetValue(event, args[1]);
    s32 x = evtGetValue(event, args[2]);
    s32 y = evtGetValue(event, args[3]);
    s32 z = evtGetValue(event, args[4]);

    if (on == 1 && prev == 0) {
        eff = effMarioBalloonEntry(1, npc);
    }
    if (on == 0 && prev == 1) {
        effDelete(eff);
    }
    npc->position.x = x;
    npc->position.y = y;
    npc->position.z = z;
    return EVT_RETURN_DONE;
}
