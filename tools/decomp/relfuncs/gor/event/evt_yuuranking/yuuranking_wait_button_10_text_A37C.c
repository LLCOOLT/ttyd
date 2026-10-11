// include: manager/evtmgr_cmd.h
// include: system.h
// decl: typedef struct YuuRankingWork { EventEntry* event; u16 flags; u32 dispFlags; f32 x; f32 y; s32 type; s32 mode; s32 score; s32 bonus; s32 mul; s32 rank; s32 max; s32 phase; s32 monte; s32 dispScore; s32 timer; } YuuRankingWork;
// decl: typedef struct YuuParlorRank { u8 pad[0x14]; s32 used[4][6]; s32 score[4][6]; s32 pts[4][6]; } YuuParlorRank;
// decl: extern YuuParlorRank* yuwp;
// decl: static YuuRankingWork* _wp;
// decl: s32 psndSFXOn(const char* name);
// proto: USER_FUNC(yuuranking_wait_button_10_text_A37C);
USER_FUNC(yuuranking_wait_button_10_text_A37C) {
    YuuRankingWork* wp = _wp;

    if (isFirstCall) {
        wp->dispFlags |= 2;
    }
    if (!(wp->dispFlags & 4) && (keyGetButtonTrg(0) & 0x300)) {
        wp->dispFlags &= ~2;
        psndSFXOn((const char*)0x12);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
