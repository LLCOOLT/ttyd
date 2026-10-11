// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// decl: typedef struct YuuRankingWork { EventEntry* event; u16 flags; u32 dispFlags; f32 x; f32 y; s32 type; s32 mode; s32 score; s32 bonus; s32 mul; s32 rank; s32 max; s32 phase; s32 monte; s32 dispScore; s32 timer; } YuuRankingWork;
// decl: typedef struct YuuParlorRank { u8 pad[0x14]; s32 used[4][6]; s32 score[4][6]; s32 pts[4][6]; } YuuParlorRank;
// decl: extern YuuParlorRank* yuwp;
// decl: static YuuRankingWork* _wp;
// decl: s32 psndSFXOn(const char* name);
// decl: void psndSFXOff(s32 id);
// proto: USER_FUNC(evt_yuuranking_main_func);
USER_FUNC(evt_yuuranking_main_func) {
    YuuRankingWork* wp = (YuuRankingWork*)event->lwData[0];
    static s32 snd_id;

    if (wp->flags & 1) {
        wp->flags |= 2;
        return EVT_RETURN_DONE;
    }
    dispEntry(CAMERA_2D, 1000.0f, 0, evt_yuuranking_disp_func, wp);
    if (wp->mode == 0) {
        switch (wp->phase) {
            case 0:
                wp->timer = 30;
                wp->phase++;
                break;
            case 1:
                if (wp->timer != 0) {
                    wp->timer--;
                    break;
                }
                wp->phase++;
                if (wp->score != 0) {
                    snd_id = psndSFXOn((const char*)0x8D7);
                }
                break;
            case 2:
                switch (wp->type) {
                    case 0:
                        wp->dispScore += 5590;
                        if (wp->dispScore > wp->score) {
                            wp->dispScore = wp->score;
                        }
                        break;
                    case 3:
                        wp->dispScore += 1090;
                        if (wp->dispScore > wp->score) {
                            wp->dispScore = wp->score;
                        }
                        break;
                    case 2:
                        wp->dispScore += 1090;
                        if (wp->dispScore > wp->score) {
                            wp->dispScore = wp->score;
                        }
                        break;
                    case 1:
                        wp->dispScore -= 11;
                        if (wp->dispScore < wp->score) {
                            wp->dispScore = wp->score;
                        }
                        break;
                }
                wp->monte = yuu_kesan(wp->type, wp->dispScore, 0, 0, wp->max);
                if (wp->dispScore == wp->score) {
                    if (wp->score != 0) {
                        psndSFXOff(snd_id);
                    }
                    switch (wp->type) {
                        case 0:
                        case 3:
                        case 2:
                            if (wp->score > 0) {
                                wp->timer = 48;
                                wp->phase++;
                            } else {
                                wp->timer = 30;
                                wp->phase = 9;
                            }
                            break;
                        case 1:
                            if (wp->mul > 1 || wp->mul < 0) {
                                if (wp->score < wp->max) {
                                    wp->timer = 48;
                                    wp->phase = 6;
                                } else {
                                    wp->timer = 30;
                                    wp->phase = 9;
                                }
                            } else {
                                wp->timer = 30;
                                wp->phase = 9;
                            }
                            break;
                    }
                }
                break;
            case 3:
                if (wp->timer != 0) {
                    wp->timer--;
                    break;
                }
                wp->timer = 48;
                wp->phase++;
                break;
            case 4:
                if (wp->timer != 0) {
                    wp->timer--;
                    break;
                }
                wp->phase++;
                break;
            case 5: {
                s32 target;

                switch (wp->type) {
                    case 0:
                    case 3:
                    case 2:
                        target = yuu_kesan(wp->type, wp->dispScore, wp->bonus, 0, wp->max);
                        if (wp->monte < target) {
                            wp->monte++;
                            psndSFXOn((const char*)0x8CA);
                        } else if (wp->monte > target) {
                            wp->monte--;
                        } else if (wp->score > 0 && (wp->mul > 1 || wp->mul < 0)) {
                            wp->timer = 48;
                            wp->phase++;
                        } else {
                            wp->timer = 30;
                            wp->phase = 9;
                        }
                        break;
                }
                break;
            }
            case 6:
                if (wp->timer != 0) {
                    wp->timer--;
                    break;
                }
                wp->timer = 48;
                wp->phase++;
                break;
            case 7:
                if (wp->timer != 0) {
                    wp->timer--;
                    break;
                }
                wp->phase++;
                break;
            case 8: {
                s32 target;

                switch (wp->type) {
                    case 0:
                    case 3:
                    case 2:
                    case 1:
                        target = yuu_kesan(wp->type, wp->dispScore, wp->bonus, wp->mul, wp->max);
                        if (wp->monte < target) {
                            wp->monte++;
                            psndSFXOn((const char*)0x8CA);
                        } else if (wp->monte > target) {
                            wp->monte--;
                        } else {
                            wp->timer = 30;
                            wp->phase++;
                        }
                        break;
                }
                break;
            }
            case 9:
                wp->dispFlags &= ~4;
                break;
        }
    }
    return EVT_RETURN_BLOCK;
}
