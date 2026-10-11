// include: manager/evtmgr_cmd.h
// include: memory.h
// decl: typedef struct GansWork { smartEntry* buf; GXTexObj tex; s32 onoff; s32 alpha; s32 ready; } GansWork;
// decl: GansWork* gans_wp;
// proto: USER_FUNC(onoff);
USER_FUNC(onoff) {
    gans_wp->onoff = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}
