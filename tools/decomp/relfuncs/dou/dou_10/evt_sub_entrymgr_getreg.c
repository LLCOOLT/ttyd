// include: manager/evtmgr_cmd.h
// decl: typedef struct EntryMgrEntry { s32 used; s32 id; f32 reg[3]; } EntryMgrEntry;
// decl: typedef struct EntryMgr { s32 count; EntryMgrEntry* entries; } EntryMgr;
// proto: USER_FUNC(evt_sub_entrymgr_getreg);
USER_FUNC(evt_sub_entrymgr_getreg) {
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
    evtSetFloat(event, args[2], e->reg[0]);
    evtSetFloat(event, args[3], e->reg[1]);
    evtSetFloat(event, args[4], e->reg[2]);
    return EVT_RETURN_DONE;
}
