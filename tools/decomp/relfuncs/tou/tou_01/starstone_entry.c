// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// decl: EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
// proto: static USER_FUNC(starstone_entry);
static USER_FUNC(starstone_entry) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);

    effSetName(effStarStoneEntry(2, x, y, z, 1.0f), name);
    return EVT_RETURN_DONE;
}
