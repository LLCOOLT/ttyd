// include: manager/evtmgr_cmd.h
// include: memory.h
// include: string.h
// decl: typedef struct YuuRankingWork { EventEntry* event; u16 flags; u32 dispFlags; f32 x; f32 y; s32 type; s32 mode; s32 score; s32 bonus; s32 mul; s32 rank; s32 max; s32 phase; s32 monte; s32 dispScore; s32 timer; } YuuRankingWork;
// decl: typedef struct YuuParlorRank { u8 pad[0x14]; s32 used[4][6]; s32 score[4][6]; s32 pts[4][6]; } YuuParlorRank;
// decl: extern YuuParlorRank* yuwp;
// decl: static YuuRankingWork* _wp;
// proto: USER_FUNC(evt_yuuranking_alloc_31_text_52F8);
USER_FUNC(evt_yuuranking_alloc_31_text_52F8) {
    s32* args = event->args;
    YuuRankingWork* wp = _mapAlloc(sizeof(YuuRankingWork));
    s32 i;
    s32 j;
    s32 score;

    memset(wp, 0, sizeof(YuuRankingWork));
    _wp = wp;
    wp->x = evtGetFloat(event, args[0]);
    wp->y = evtGetFloat(event, args[1]);
    wp->type = evtGetValue(event, args[2]);
    wp->mode = evtGetValue(event, args[3]);
    wp->score = evtGetValue(event, args[4]);
    wp->bonus = evtGetValue(event, args[5]);
    wp->mul = evtGetValue(event, args[6]);
    switch (wp->type) {
        case 0:
            yuwp->used[wp->type][5] = 0;
            yuwp->score[wp->type][5] = 0;
            yuwp->pts[wp->type][5] = 0;
            wp->rank = -1;
            if (wp->mode == 1) {
                score = wp->score;
                if (score >= 0) {
                    for (i = 0; i < 6; i++) {
                        if (yuwp->used[wp->type][i] == 0) {
                            yuwp->used[wp->type][i] = 1;
                            yuwp->score[wp->type][i] = wp->score;
                            yuwp->pts[wp->type][i] = yuu_kesan(wp->type, wp->score, wp->bonus, wp->mul, wp->max);
                            wp->rank = i;
                            break;
                        }
                        if (score >= yuwp->score[wp->type][i]) {
                            for (j = 4; j > i; j--) {
                                yuwp->used[wp->type][j] = yuwp->used[wp->type][j - 1];
                                yuwp->score[wp->type][j] = yuwp->score[wp->type][j - 1];
                                yuwp->pts[wp->type][j] = yuwp->pts[wp->type][j - 1];
                            }
                            yuwp->used[wp->type][i] = 1;
                            yuwp->score[wp->type][i] = wp->score;
                            yuwp->pts[wp->type][i] = yuu_kesan(wp->type, wp->score, wp->bonus, wp->mul, wp->max);
                            wp->rank = i;
                            if (i == 0) {
                                evtSetValue(NULL, GSWF(1240), TRUE);
                            }
                            break;
                        }
                    }
                } else {
                    yuwp->used[wp->type][5] = 1;
                    yuwp->score[wp->type][5] = wp->score;
                    yuwp->pts[wp->type][5] = 0;
                    wp->rank = 5;
                }
            } else if (wp->mode == 0) {
                wp->dispScore = 0;
                if (wp->score < wp->dispScore) {
                    wp->dispScore = wp->score;
                }
            }
            break;
        case 3:
        case 2:
            yuwp->used[wp->type][5] = 0;
            yuwp->score[wp->type][5] = 0;
            yuwp->pts[wp->type][5] = 0;
            wp->rank = -1;
            if (wp->mode == 1) {
                score = wp->score;
                if (score >= 0) {
                    for (i = 0; i < 6; i++) {
                        if (yuwp->used[wp->type][i] == 0) {
                            yuwp->used[wp->type][i] = 1;
                            yuwp->score[wp->type][i] = wp->score;
                            yuwp->pts[wp->type][i] = yuu_kesan(wp->type, wp->score, wp->bonus, wp->mul, wp->max);
                            wp->rank = i;
                            break;
                        }
                        if (score >= yuwp->score[wp->type][i]) {
                            for (j = 4; j > i; j--) {
                                yuwp->used[wp->type][j] = yuwp->used[wp->type][j - 1];
                                yuwp->score[wp->type][j] = yuwp->score[wp->type][j - 1];
                                yuwp->pts[wp->type][j] = yuwp->pts[wp->type][j - 1];
                            }
                            yuwp->used[wp->type][i] = 1;
                            yuwp->score[wp->type][i] = wp->score;
                            yuwp->pts[wp->type][i] = yuu_kesan(wp->type, wp->score, wp->bonus, wp->mul, wp->max);
                            wp->rank = i;
                            if (i == 0) {
                                if (wp->type == 3) {
                                    evtSetValue(NULL, GSWF(1241), TRUE);
                                } else {
                                    evtSetValue(NULL, GSWF(1242), TRUE);
                                }
                            }
                            break;
                        }
                    }
                } else {
                    yuwp->used[wp->type][5] = 1;
                    yuwp->score[wp->type][5] = wp->score;
                    yuwp->pts[wp->type][5] = 0;
                    wp->rank = 5;
                }
            } else if (wp->mode == 0) {
                wp->dispScore = 0;
                if (wp->score < wp->dispScore) {
                    wp->dispScore = wp->score;
                }
            }
            break;
        case 1:
            wp->max = evtGetValue(event, args[7]);
            yuwp->used[wp->type][5] = 0;
            yuwp->score[wp->type][5] = 0;
            yuwp->pts[wp->type][5] = 0;
            wp->rank = -1;
            if (wp->mode == 1) {
                score = wp->score;
                if (score < wp->max) {
                    for (i = 0; i < 6; i++) {
                        if (yuwp->used[wp->type][i] == 0) {
                            yuwp->used[wp->type][i] = 1;
                            yuwp->score[wp->type][i] = wp->score;
                            yuwp->pts[wp->type][i] = yuu_kesan(wp->type, wp->score, wp->bonus, wp->mul, wp->max);
                            wp->rank = i;
                            break;
                        }
                        if (score <= yuwp->score[wp->type][i]) {
                            for (j = 4; j > i; j--) {
                                yuwp->used[wp->type][j] = yuwp->used[wp->type][j - 1];
                                yuwp->score[wp->type][j] = yuwp->score[wp->type][j - 1];
                                yuwp->pts[wp->type][j] = yuwp->pts[wp->type][j - 1];
                            }
                            yuwp->used[wp->type][i] = 1;
                            yuwp->score[wp->type][i] = wp->score;
                            yuwp->pts[wp->type][i] = yuu_kesan(wp->type, wp->score, wp->bonus, wp->mul, wp->max);
                            wp->rank = i;
                            if (i == 0) {
                                evtSetValue(NULL, GSWF(1243), TRUE);
                            }
                            break;
                        }
                    }
                } else {
                    yuwp->used[wp->type][5] = 1;
                    yuwp->score[wp->type][5] = wp->score;
                    yuwp->pts[wp->type][5] = 0;
                    wp->rank = 5;
                }
            } else {
                if (wp->mode == 2) {
                    wp->max = 10000;
                }
                if (wp->mode == 0) {
                    wp->dispScore = wp->max - 1;
                    if (wp->score > wp->dispScore) {
                        wp->dispScore = wp->score;
                    }
                }
            }
            break;
    }
    if (wp->mode == 0) {
        wp->dispFlags |= 4;
    }
    wp->event = evtEntry(main_evt, 0, 0);
    wp->event->lwData[0] = (s32)wp;
    return EVT_RETURN_DONE;
}
