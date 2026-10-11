// include: manager/evtmgr_cmd.h
// include: eff/n64/eff_akari_charge_n64.h
// decl: static EffectEntry* eff_charge;
// proto: static USER_FUNC(eff_dead);
static USER_FUNC(eff_dead) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    eff_charge = effAkariChargeN64Entry(0, 1000, x, y, z, 1.5f);
    return EVT_RETURN_DONE;
}
