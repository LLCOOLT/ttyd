// include: manager/evtmgr_cmd.h
// include: memory.h
// include: string.h
// include: stdio.h
// include: driver/mapdrv.h
// include: dolphin/gx.h
// decl: typedef struct UranaiWork { s32 lwData[16]; s32 gwData[32]; smartEntry* buf; GXTexObj tex; s32 ready; EventEntry* capEvent; s32 x; s32 y; s32 w; s32 h; } UranaiWork;
// decl: UranaiWork* uranai_wp;
// decl: extern s32 evt_uranai_cap[];
// proto: USER_FUNC(uranai_init_func);
USER_FUNC(uranai_init_func) {
    char name[64];
    s32 i;

    uranai_wp = _mapAlloc(sizeof(UranaiWork));
    memset(uranai_wp, 0, sizeof(UranaiWork));
    memcpy(uranai_wp->lwData, event->lwData, sizeof(uranai_wp->lwData));
    memcpy(uranai_wp->gwData, evtGetWork()->gwData, sizeof(uranai_wp->gwData));
    for (i = 0; i < 9; i++) {
        sprintf(name, "card_omote_%d", i + 1);
        if (mapGetMapObj(name) != NULL) {
            mapGetMapObj(name)->field_0x4[1] = 5;
        }
        sprintf(name, "card_ura_%d", i + 1);
        if (mapGetMapObj(name) != NULL) {
            mapGetMapObj(name)->field_0x4[1] = 5;
        }
    }
    uranai_wp->capEvent = evtEntry(evt_uranai_cap, 0, 0);
    return EVT_RETURN_DONE;
}
