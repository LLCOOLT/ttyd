// decl: typedef struct IwaMoveWork { s32 init; s32 timer; s32 state; EventEntry* event; s32* script; } IwaMoveWork;
// decl: IwaMoveWork iwamove;
// proto: USER_FUNC(evt_iwamove_ent);
USER_FUNC(evt_iwamove_ent) {
    IwaMoveWork* wk = &iwamove;

    wk->script = (s32*)event->args[0];
    wk->state = 0;
    wk->event = evtEntry(evt_iwamove_main_evt, 0, 0);
    wk->event->lwData[0] = (s32)&iwamove;
    return EVT_RETURN_DONE;
}
