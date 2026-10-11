// include: driver/effdrv.h
// include: driver/npcdrv.h
// include: evt/evt_npc.h
// decl: EffectEntry* effMarioBalloonEntry(s32 type, NpcEntry* npc);
// decl: static EffectEntry* eff;
// proto: static USER_FUNC(lect_npc_balloon_on_off);
static USER_FUNC(lect_npc_balloon_on_off) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    NpcEntry* npc = evtNpcNameToPtr(event, name);

    if (evtGetValue(event, args[1])) {
        eff = effMarioBalloonEntry(1, npc);
        ((s32*)eff->userdata)[7] = 7;
    } else {
        effDelete(eff);
    }
    return EVT_RETURN_DONE;
}
