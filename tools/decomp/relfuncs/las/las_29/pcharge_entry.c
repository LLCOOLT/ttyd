// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// decl: EffectEntry* effPokopiPchargeN64Entry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
// proto: USER_FUNC(pcharge_entry);
USER_FUNC(pcharge_entry) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);

    effSetName(effPokopiPchargeN64Entry(8, x, y, z, 1.0f, 0), name);
    return EVT_RETURN_DONE;
}
