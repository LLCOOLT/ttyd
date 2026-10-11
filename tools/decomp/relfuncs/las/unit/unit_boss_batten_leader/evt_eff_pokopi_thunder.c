// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// decl: EffectEntry* effPokopiThunderN64Entry(s32 type, s32 time, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, f32 scale);
// proto: USER_FUNC(evt_eff_pokopi_thunder);
USER_FUNC(evt_eff_pokopi_thunder) {
    f32 top;
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    top = 250.0f + y;

    effPokopiThunderN64Entry(0, 30, x, top, z, x, y, z, 1.0f);
    effPokopiThunderN64Entry(1, 30, x, top, z, x, y, z, 1.0f);
    effPokopiThunderN64Entry(1, 30, x, top, z, x, y, z, 1.0f);
    return EVT_RETURN_DONE;
}
