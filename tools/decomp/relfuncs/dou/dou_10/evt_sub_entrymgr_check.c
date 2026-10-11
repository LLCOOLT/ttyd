// decl: typedef struct EntryMgrEntry { s32 used; s32 id; f32 reg[3]; } EntryMgrEntry;
// decl: typedef struct EntryMgr { s32 count; EntryMgrEntry* entries; } EntryMgr;
// proto: USER_FUNC(evt_sub_entrymgr_check);
USER_FUNC(evt_sub_entrymgr_check) {
    s32* args = event->args;
    EntryMgr* mgr = (EntryMgr*)evtGetValue(event, args[0]);
    EntryMgrEntry* e = mgr->entries;
    s32 id = evtGetValue(event, args[1]);
    BOOL ok = FALSE;
    s32 i;

    for (i = 0; i < mgr->count; i++) {
        if (e->used) {
            if (e->id == id) {
                ok = TRUE;
                break;
            }
            e++;
        }
    }
    evtSetValue(event, args[2], ok);
    return EVT_RETURN_DONE;
}
