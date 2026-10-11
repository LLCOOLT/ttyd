// include: manager/evtmgr_cmd.h
// decl: typedef struct KpaWork { u8 stage; u8 lives; u8 time; } KpaWork;
// decl: KpaWork* kwp;
// include: memory.h
// decl: extern s32 kpa_status_main_evt[];
// proto: USER_FUNC(kpa_status_init);
USER_FUNC(kpa_status_init) {
    s32* args = event->args;
    s32 stage = evtGetValue(event, args[0]);
    s32 lives = evtGetValue(event, args[1]);
    s32 time = evtGetValue(event, args[2]);
    EventEntry* evt = evtEntryType(kpa_status_main_evt, event->priority, 0, event->type);
    s32 i;

    evt->unitId = event->unitId;
    evt->ownerNPC = event->ownerNPC;
    for (i = 0; i < 16; i++) {
        evt->lwData[i] = event->lwData[i];
    }
    for (i = 0; i < 3; i++) {
        evt->lfData[i] = event->lfData[i];
    }
    evt->uwBase = event->uwBase;
    evt->ufBase = event->ufBase;
    kwp = _mapAlloc(sizeof(KpaWork));
    kwp->stage = stage;
    kwp->lives = lives;
    kwp->time = time;
    return EVT_RETURN_DONE;
}
