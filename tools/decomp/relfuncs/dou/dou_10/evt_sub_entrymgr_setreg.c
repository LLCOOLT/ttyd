// include: manager/evtmgr_cmd.h
// decl: typedef struct EntryMgrEntry { s32 used; s32 id; f32 reg[3]; } EntryMgrEntry;
// decl: typedef struct EntryMgr { s32 count; EntryMgrEntry* entries; } EntryMgr;
// proto: USER_FUNC(evt_sub_entrymgr_setreg);
USER_FUNC(evt_sub_entrymgr_setreg) {
    s32* args = event->args;
    EntryMgr* mgr = (EntryMgr*)evtGetValue(event, args[0]);
    EntryMgrEntry* e = mgr->entries;
    s32 id = evtGetValue(event, args[1]);
    s32 i;

    for (i = 0; i < mgr->count; i++, e++) {
        if (e->id == id) {
            break;
        }
    }
    e->reg[0] = evtGetFloat(event, args[2]);
    e->reg[1] = evtGetFloat(event, args[3]);
    e->reg[2] = evtGetFloat(event, args[4]);
    return EVT_RETURN_DONE;
}
