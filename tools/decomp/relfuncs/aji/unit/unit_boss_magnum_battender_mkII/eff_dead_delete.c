// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// decl: static EffectEntry* eff_charge;
// proto: static USER_FUNC(eff_dead_delete);
static USER_FUNC(eff_dead_delete) {
    effDelete(eff_charge);
    return EVT_RETURN_DONE;
}
