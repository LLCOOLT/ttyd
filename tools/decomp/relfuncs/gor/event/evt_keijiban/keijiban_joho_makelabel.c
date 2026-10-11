// include: stdio.h
// proto: USER_FUNC(keijiban_joho_makelabel);
USER_FUNC(keijiban_joho_makelabel) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    KeijibanData* kj = KJDT;

    if (idx >= 0 && idx < kj->count) {
        sprintf(kj->label, "%s_%04d", kj->prefix, kj->entries[idx].index);
        evtSetValue(event, args[1], (s32)kj->label);
        kj->current = idx;
        return EVT_RETURN_DONE;
    }
    kj->label[0] = '\0';
    evtSetValue(event, args[1], (s32)kj->label);
    return EVT_RETURN_DONE;
}
