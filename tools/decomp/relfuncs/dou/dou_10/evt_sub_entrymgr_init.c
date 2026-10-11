// include: memory.h
// include: string.h
// decl: typedef struct EntryMgrEntry { s32 used; s32 id; f32 reg[3]; } EntryMgrEntry;
// decl: typedef struct EntryMgr { s32 count; EntryMgrEntry* entries; } EntryMgr;
// proto: USER_FUNC(evt_sub_entrymgr_init);
USER_FUNC(evt_sub_entrymgr_init) {
    s32* args = event->args;
    EntryMgr* mgr = _mapAlloc(sizeof(EntryMgr));

    evtSetValue(event, args[0], (s32)mgr);
    mgr->count = evtGetValue(event, args[1]);
    mgr->entries = _mapAlloc(mgr->count * sizeof(EntryMgrEntry));
    memset(mgr->entries, 0, mgr->count * sizeof(EntryMgrEntry));
    return EVT_RETURN_DONE;
}
