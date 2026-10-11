// include: manager/evtmgr_cmd.h
// include: memory.h
// include: string.h
// include: dolphin/gx.h
// decl: typedef struct UranaiWork { s32 lwData[16]; s32 gwData[32]; smartEntry* buf; GXTexObj tex; s32 ready; EventEntry* capEvent; s32 x; s32 y; s32 w; s32 h; } UranaiWork;
// decl: UranaiWork* uranai_wp;
// proto: USER_FUNC(uranai_exit_func);
USER_FUNC(uranai_exit_func) {
    memcpy(event->lwData, uranai_wp->lwData, sizeof(uranai_wp->lwData));
    memcpy(evtGetWork()->gwData, uranai_wp->gwData, sizeof(uranai_wp->gwData));
    evtDelete(uranai_wp->capEvent);
    _mapFree(uranai_wp);
    return EVT_RETURN_DONE;
}
