// include: driver/effdrv.h
// decl: BOOL effFallCheckHit(EffectEntry* effect);
// proto: USER_FUNC(unk_tou2_00002770);
USER_FUNC(unk_tou2_00002770) {
    EffectEntry* eff = (EffectEntry*)evtGetValue(event, event->args[0]);

    if (eff != NULL && !effFallCheckHit(eff)) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
