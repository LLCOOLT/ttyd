// include: memory.h
// include: driver/effdrv.h
// include: driver/npcdrv.h
// decl: static EffectEntry* eff;
// decl: NpcEntry* npc;
// proto: USER_FUNC(desk_talk_init_func);
USER_FUNC(desk_talk_init_func) {
    npc = _mapAlloc(sizeof(NpcEntry));
    eff = _mapAlloc(sizeof(EffectEntry));
    return EVT_RETURN_DONE;
}
