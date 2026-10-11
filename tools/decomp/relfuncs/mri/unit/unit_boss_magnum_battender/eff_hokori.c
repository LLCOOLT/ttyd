// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// decl: EffectEntry* effHokoriN64Entry(s32 type, s32 arg1, f32 x, f32 y, f32 z);
// proto: USER_FUNC(eff_hokori);
USER_FUNC(eff_hokori) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    EffectEntry* eff = effHokoriN64Entry(0, evtGetValue(event, args[3]), x, y, z);

    ((s32*)eff->userdata)[12] = 255;
    ((s32*)eff->userdata)[13] = 255;
    ((s32*)eff->userdata)[14] = 255;
    ((s32*)eff->userdata)[15] = 0;
    ((s32*)eff->userdata)[16] = 0;
    ((s32*)eff->userdata)[17] = 0;
    return EVT_RETURN_DONE;
}
