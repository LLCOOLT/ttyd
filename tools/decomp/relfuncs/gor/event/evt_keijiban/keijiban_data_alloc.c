// include: memory.h
// include: string.h
// proto: USER_FUNC(keijiban_data_alloc);
USER_FUNC(keijiban_data_alloc) {
    KJDT->prefix = (const char*)evtGetValue(event, event->args[0]);
    KJDT->count = keijiban_data_make(KJDT->prefix, FALSE);
    KJDT->entries = _mapAlloc(KJDT->count * sizeof(KeijibanEntry) + 0x40);
    memset(KJDT->entries, 0, KJDT->count * sizeof(KeijibanEntry) + 0x40);
    KJDT->label = (char*)&KJDT->entries[KJDT->count];
    keijiban_data_make(KJDT->prefix, TRUE);
    return EVT_RETURN_DONE;
}
