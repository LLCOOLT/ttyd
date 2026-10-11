// include: eff/n64/eff_akari_charge_n64.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(akari_charge_entry);
USER_FUNC(akari_charge_entry) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    s32 a = evtGetValue(event, args[3]);
    s32 b = evtGetValue(event, args[4]);
    s32 c = evtGetValue(event, args[5]);
    f32 scale = evtGetFloat(event, args[6]);
    EffectEntry* eff = effAkariChargeN64Entry(0, evtGetValue(event, args[7]), x, y, z, scale);

    ((s32*)eff->userdata)[6] = a;
    ((s32*)eff->userdata)[7] = b;
    ((s32*)eff->userdata)[8] = c;
    return EVT_RETURN_DONE;
}
