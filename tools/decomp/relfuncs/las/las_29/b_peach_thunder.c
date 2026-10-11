// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// decl: EffectEntry* effPokopiThunderN64Entry(s32 type, s32 lifetime, f32 x, f32 y, f32 z, f32 tx, f32 ty, f32 tz, f32 scale);
// proto: USER_FUNC(b_peach_thunder);
USER_FUNC(b_peach_thunder) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    EffectEntry* eff = effPokopiThunderN64Entry(0, 150, 35.0f + x, 160.0f + y, z, x, y, z, 2.0f);

    ((s32*)eff->userdata)[12] = 255;
    ((s32*)eff->userdata)[13] = 160;
    ((s32*)eff->userdata)[14] = 192;
    ((s32*)eff->userdata)[16] = 20;
    ((s32*)eff->userdata)[17] = 20;
    ((s32*)eff->userdata)[18] = 20;
    return EVT_RETURN_DONE;
}
