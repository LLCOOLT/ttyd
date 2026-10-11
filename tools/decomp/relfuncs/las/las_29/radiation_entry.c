// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// decl: EffectEntry* effRadiationN64Entry(s32 type, f32 x, f32 y, f32 z, f32 scale);
// proto: USER_FUNC(radiation_entry);
USER_FUNC(radiation_entry) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    f32 scale = evtGetFloat(event, args[4]);

    effSetName(effRadiationN64Entry(2, x, y, z, scale), name);
    return EVT_RETURN_DONE;
}
