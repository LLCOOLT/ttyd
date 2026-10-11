// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// decl: EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
// proto: USER_FUNC(starstone_entry);
USER_FUNC(starstone_entry) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 type = evtGetValue(event, args[1]);
    f32 x = evtGetFloat(event, args[2]);
    f32 y = evtGetFloat(event, args[3]);
    f32 z = evtGetFloat(event, args[4]);
    f32 scale = evtGetFloat(event, args[5]);
    EffectEntry* eff = effStarStoneEntry(type, x, y, z, scale);

    effSetName(eff, name);
    ((u16*)eff->userdata)[2] |= 0x10;
    return EVT_RETURN_DONE;
}
