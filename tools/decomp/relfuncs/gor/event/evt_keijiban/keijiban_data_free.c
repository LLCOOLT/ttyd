// include: memory.h
// proto: USER_FUNC(keijiban_data_free);
USER_FUNC(keijiban_data_free) {
    KeijibanData* kj = KJDT;

    if (kj->entries == NULL) {
        return EVT_RETURN_DONE;
    }
    _mapFree(kj->entries);
    kj->entries = NULL;
    kj->count = 0;
    kj->prefix = NULL;
    kj->label = NULL;
    kj->current = 0;
    return EVT_RETURN_DONE;
}
