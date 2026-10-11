// include: driver/effdrv.h
// proto: USER_FUNC(eff_sleep_off);
USER_FUNC(eff_sleep_off) {
    EffectEntry* eff = effNameToPtr("eff_sleep");

    if (eff != NULL) {
        effSoftDelete(eff);
    }
    return EVT_RETURN_DONE;
}
