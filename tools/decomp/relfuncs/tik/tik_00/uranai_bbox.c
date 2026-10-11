// include: manager/evtmgr_cmd.h
// include: memory.h
// include: dolphin/gx.h
// decl: typedef struct UranaiWork { s32 lwData[16]; s32 gwData[32]; smartEntry* buf; GXTexObj tex; s32 ready; EventEntry* capEvent; s32 x; s32 y; s32 w; s32 h; } UranaiWork;
// decl: UranaiWork* uranai_wp;
// proto: USER_FUNC(uranai_bbox);
USER_FUNC(uranai_bbox) {
    s32* args = event->args;
    s32 x = evtGetValue(event, args[0]);
    s32 y = evtGetValue(event, args[1]);
    s32 w = evtGetValue(event, args[2]);
    s32 h = evtGetValue(event, args[3]);

    uranai_wp->x = x;
    uranai_wp->y = x;
    uranai_wp->w = x;
    uranai_wp->h = x;
    return EVT_RETURN_DONE;
}
