// include: manager/evtmgr.h
// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// include: driver/effdrv.h
// include: eff/eff_peach_fukidashi.h
// include: string.h
// proto: USER_FUNC(evt_fuki_btn);
USER_FUNC(evt_fuki_btn) {
    s32* args = event->args;
    s32 type = evtGetValue(event, args[0]);
    const char* name = (const char*)evtGetValue(event, args[1]);
    const char* npcName = (const char*)evtGetValue(event, args[2]);
    f32 x = evtGetFloat(event, args[3]);
    f32 y = evtGetFloat(event, args[4]);
    f32 z = evtGetFloat(event, args[5]);
    f32 size = evtGetFloat(event, args[6]);
    f32 angle = evtGetFloat(event, args[7]);
    f32 unk = evtGetFloat(event, args[8]);
    NpcEntry* npc;
    EffectEntry* eff;

    if (strcmp(npcName, "me") == 0) {
        npc = event->ownerNPC;
    } else {
        npc = npcNameToPtr(npcName);
    }
    eff = effPeachFukidashiEntry(type, npc, 10000, 0.0f, 0.0f, 0.0f, 0.0f, angle);
    if (name != NULL && strcmp(name, "") != 0) {
        effSetName(eff, name);
    }
    return EVT_RETURN_DONE;
}
