// include: manager/evtmgr_cmd.h
// decl: typedef struct YuuRankingWork { EventEntry* event; u16 flags; u32 dispFlags; f32 x; f32 y; s32 type; s32 mode; s32 score; s32 bonus; s32 mul; s32 rank; s32 max; s32 phase; s32 monte; s32 dispScore; s32 timer; } YuuRankingWork;
// decl: typedef struct YuuParlorRank { u8 pad[0x14]; s32 used[4][6]; s32 score[4][6]; s32 pts[4][6]; } YuuParlorRank;
// decl: extern YuuParlorRank* yuwp;
// decl: static YuuRankingWork* _wp;
// proto: USER_FUNC(yuuranking_get_monte_31_text_51C0);
USER_FUNC(yuuranking_get_monte_31_text_51C0) {
    evtSetValue(event, event->args[0], _wp->monte);
    return EVT_RETURN_DONE;
}
