// include: manager/fontmgr.h
// include: driver/msgdrv.h
// include: driver/windowdrv.h
// include: driver/icondrv.h
// include: driver/camdrv.h
// include: dolphin/mtx.h
// include: stdio.h
// decl: typedef struct YuuRankingWork { EventEntry* event; u16 flags; u32 dispFlags; f32 x; f32 y; s32 type; s32 mode; s32 score; s32 bonus; s32 mul; s32 rank; s32 max; s32 phase; s32 monte; s32 dispScore; s32 timer; } YuuRankingWork;
// decl: typedef struct YuuParlorRank { u8 pad[0x14]; s32 used[4][6]; s32 score[4][6]; s32 pts[4][6]; } YuuParlorRank;
// decl: extern YuuParlorRank* yuwp;
// decl: static YuuRankingWork* _wp;
// decl: void FontDrawMessageMtx(Mtx mtx, const char* msg);
// decl: void FontDrawStringPitch(f32 x, f32 y, f32 pitch, const char* str);
// decl: void FontDrawScale(f32 scale);
// proto: void evt_yuuranking_disp_func(CameraId camera, void* param);
void evt_yuuranking_disp_func(CameraId camera, void* param) {
    YuuRankingWork* wp = param;
    const char* titles[4] = {"menu_title_minigame1", "menu_title_minigame4", "menu_title_minigame3", "menu_title_minigame2"};
    const char* scoreTitles[4] = {"menu_title_score", "menu_title_score", "menu_title_score", "menu_title_score"};
    const char* ranks[6] = {"\x81\x40\x82\x50", "\x81\x40\x82\x51", "\x81\x40\x82\x52", "\x81\x40\x82\x53", "\x81\x40\x82\x54", "menu_subtitle2_rankgai"};
    char buf[32];
    const char* title;
    const char* str;
    const u8* rk;
    const char* msg;
    s32 score;
    s32 sec;
    s32 min;
    s32 rscore;
    s32 rsec;
    s32 rmin;
    s32 i;
    f32 ofs;
    s32 ix;
    s32 iy;
    Mtx mtx;
    f32 scale;

    windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -196.0f + wp->x, 112.0f + wp->y, 392.0f, 224.0f, 20.0f);
    switch (wp->mode) {
        case 0:
            title = msgSearch(scoreTitles[wp->type]);
            break;
        case 1:
        case 2:
            title = msgSearch(titles[wp->type]);
            break;
    }
    scale = 1.0f;
    windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA3, 0xFF, 0xFF}, wp->x + -(scale * FontGetMessageWidth(title) + 50.0f) / 2.0f, scale + (128.0f + wp->y), scale * FontGetMessageWidth(title) + 50.0f, 28.0f, 8.0f);
    FontDrawStart();
    FontDrawScale(1.0f);
    FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
    FontDrawMessage(wp->x + scale * -FontGetMessageWidth(title) / 2.0f, 128.0f + wp->y, title);
    if (wp->mode == 0) {
        switch (wp->type) {
            case 0:
                FontDrawStart();
                FontDrawScale(1.0f);
                FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
                unk_gor_0000dfc4(-150.4f + wp->x, 56.0f + wp->y, 1.0f, msgSearch("menu_subtitle1_minigame1"), 165);
                if (wp->dispScore >= 0) {
                    sprintf(buf, "%3d%s%02d", wp->dispScore / 1000, msgSearch("menu_decimal_point"), (wp->dispScore % 1000) / 10);
                    msg = buf;
                    FontDrawStringPitch(wp->x + (150.4f - fontlenpitch(buf, 18)), 56.0f + wp->y, 18.0f, msg);
                    if (wp->phase >= 4) {
                        FontDrawStart();
                        FontDrawScale(1.0f);
                        FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
                        unk_gor_0000dfc4(-150.4f + wp->x, 32.0f + wp->y, 1.0f, msgSearch("menu_subtitle4_getmonte"), 165);
                        sprintf(buf, "%4d", wp->bonus);
                        msg = buf;
                        FontDrawStringPitch(wp->x + (150.4f - fontlenpitch(buf, 18)), 32.0f + wp->y, 18.0f, msg);
                    }
                    if (wp->phase >= 7) {
                        FontDrawStart();
                        FontDrawScale(1.0f);
                        FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
                        if (wp->mul > 1) {
                            unk_gor_0000dfc4(-150.4f + wp->x, 8.0f + wp->y, 1.0f, msgSearch("menu_subtitle2_minigame1"), 165);
                            if (wp->mul < 0x100) {
                                sprintf(buf, msgSearch("menu_subtitle4_minigame1"), wp->mul);
                            } else {
                                sprintf(buf, "%2d", wp->mul - 0x100);
                            }
                            msg = buf;
                            FontDrawStringPitch(wp->x + (150.4f - fontlenpitch(buf, 18)), 8.0f + wp->y, 18.0f, msg);
                        } else if (wp->mul < 0) {
                            unk_gor_0000dfc4(-150.4f + wp->x, 8.0f + wp->y, 1.0f, msgSearch("menu_subtitle5_minigame1"), 165);
                            sprintf(buf, msgSearch("menu_subtitle6_minigame1"), -wp->mul);
                            msg = buf;
                            FontDrawStringPitch(wp->x + (150.4f - fontlenpitch(buf, 18)), 8.0f + wp->y, 18.0f, msg);
                        }
                    }
                } else {
                    FontDrawColor((GXColor){0xFF, 0x3F, 0x3F, 0xFF});
                    sprintf(buf, msgSearch("menu_error_minigame1"));
                    msg = buf;
                    FontDrawStringPitch(wp->x + (150.4f - fontlenpitch(buf, 18)), 56.0f + wp->y, 18.0f, msg);
                }
                break;
            case 3:
            case 2:
                FontDrawStart();
                FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
                switch (wp->type) {
                    case 3:
                        str = msgSearch("menu_subtitle1_minigame2");
                        break;
                    case 2:
                        str = msgSearch("menu_subtitle1_minigame3");
                        break;
                }
                unk_gor_0000dfc4(-150.4f + wp->x, 56.0f + wp->y, 1.0f, str, 165);
                FontDrawScale(1.0f);
                score = wp->dispScore;
                if (score >= 0) {
                    sec = score / 1000;
                    min = sec / 60;
                    sec = sec % 60;
                    sprintf(buf, "%1d%s%02d%s%02d", min, msgSearch("menu_colon"), sec, msgSearch("menu_colon"), (score % 1000) / 10);
                    msg = buf;
                    FontDrawStringPitch(wp->x + (150.4f - fontlenpitch(buf, 18)), 56.0f + wp->y, 18.0f, msg);
                    if (wp->phase >= 4) {
                        FontDrawStart();
                        FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
                        switch (wp->type) {
                            case 3:
                                str = msgSearch("menu_subtitle4_getmonte");
                                break;
                            case 2:
                                str = msgSearch("menu_subtitle4_getmonte");
                                break;
                        }
                        unk_gor_0000dfc4(-150.4f + wp->x, 32.0f + wp->y, 1.0f, str, 165);
                        FontDrawScale(1.0f);
                        sprintf(buf, "%4d", wp->bonus);
                        msg = buf;
                        FontDrawStringPitch(wp->x + (150.4f - fontlenpitch(buf, 18)), 32.0f + wp->y, 18.0f, msg);
                    }
                    if (wp->phase >= 7) {
                        FontDrawStart();
                        FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
                        if (wp->mul > 1) {
                            switch (wp->type) {
                                case 3:
                                    str = msgSearch("menu_subtitle2_minigame2");
                                    break;
                                case 2:
                                    str = msgSearch("menu_subtitle2_minigame3");
                                    break;
                            }
                            unk_gor_0000dfc4(-150.4f + wp->x, 8.0f + wp->y, 1.0f, str, 165);
                            FontDrawScale(1.0f);
                            if (wp->mul < 0x100) {
                                sprintf(buf, msgSearch("menu_subtitle4_minigame1"), wp->mul);
                            } else {
                                sprintf(buf, "%2d", wp->mul - 0x100);
                            }
                            FontDrawStringPitch(wp->x + (150.4f - fontlenpitch(buf, 18)), 8.0f + wp->y, 18.0f, buf);
                        } else if (wp->mul < 0) {
                            unk_gor_0000dfc4(-150.4f + wp->x, 8.0f + wp->y, 1.0f, msgSearch("menu_subtitle5_minigame1"), 165);
                            FontDrawScale(1.0f);
                            sprintf(buf, msgSearch("menu_subtitle6_minigame1"), -wp->mul);
                            msg = buf;
                            FontDrawStringPitch(wp->x + (150.4f - fontlenpitch(buf, 18)), 8.0f + wp->y, 18.0f, msg);
                        }
                    }
                } else {
                    FontDrawColor((GXColor){0xFF, 0x3F, 0x3F, 0xFF});
                    if (wp->type == 3) {
                        sprintf(buf, msgSearch("menu_error_minigame2"));
                    } else {
                        sprintf(buf, msgSearch("menu_error_minigame3"));
                    }
                    FontDrawStringPitch(wp->x + (150.4f - fontlenpitch(buf, 18)), 56.0f + wp->y, 18.0f, buf);
                }
                break;
            case 1:
                FontDrawStart();
                FontDrawScale(1.0f);
                FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
                unk_gor_0000dfc4(-150.4f + wp->x, 56.0f + wp->y, 1.0f, msgSearch("menu_subtitle1_minigame4"), 165);
                if (wp->dispScore < wp->max) {
                    sprintf(buf, "%4d", wp->dispScore + 1);
                    FontDrawStringPitch(wp->x + (150.4f - fontlenpitch(buf, 18)), 56.0f + wp->y, 18.0f, buf);
                    if (wp->phase >= 7) {
                        FontDrawStart();
                        FontDrawScale(1.0f);
                        FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
                        if (wp->mul > 1) {
                            unk_gor_0000dfc4(-150.4f + wp->x, 8.0f + wp->y, 1.0f, msgSearch("menu_subtitle2_minigame4"), 165);
                            if (wp->mul < 0x100) {
                                sprintf(buf, msgSearch("menu_subtitle4_minigame1"), wp->mul);
                            } else {
                                sprintf(buf, "%2d", wp->mul - 0x100);
                            }
                            msg = buf;
                            FontDrawStringPitch(wp->x + (150.4f - fontlenpitch(buf, 18)), 8.0f + wp->y, 18.0f, msg);
                        } else if (wp->mul < 0) {
                            unk_gor_0000dfc4(-150.4f + wp->x, 8.0f + wp->y, 1.0f, msgSearch("menu_subtitle5_minigame1"), 165);
                            sprintf(buf, msgSearch("menu_subtitle6_minigame1"), -wp->mul);
                            msg = buf;
                            FontDrawStringPitch(wp->x + (150.4f - fontlenpitch(buf, 18)), 8.0f + wp->y, 18.0f, msg);
                        }
                    }
                } else {
                    FontDrawColor((GXColor){0xFF, 0x3F, 0x3F, 0xFF});
                    sprintf(buf, msgSearch("menu_error_minigame4"));
                    msg = buf;
                    FontDrawStringPitch(wp->x + (150.4f - fontlenpitch(buf, 18)), 56.0f + wp->y, 18.0f, msg);
                }
                break;
        }
        FontDrawStart();
        FontDrawScale(1.0f);
        FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
        unk_gor_0000dfc4(-150.4f + wp->x, -40.0f + wp->y, 1.0f, msgSearch("menu_subtitle3_totalmonte"), 165);
        ix = 70.0f + (10.4f + wp->x);
        iy = (-40.0f + wp->y) - 24.0f;
        PSMTXTrans(mtx, ix - 10, iy + 2, 0.0f);
        iconDispGxCol(mtx, 0x10, 0x13F, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
        PSMTXTrans(mtx, ix + 60, iy + 2, 0.0f);
        iconNumberDispGx(mtx, wp->monte, FALSE, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
    } else {
        FontDrawStart();
        FontDrawScale(1.0f);
        FontDrawMessage(-150.4f + wp->x, 80.0f + wp->y, msgSearch("menu_subtitle5_rank"));
        FontDrawMessage(75.2f + wp->x, 80.0f + wp->y, msgSearch("menu_subtitle1_monte"));
        FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
        switch (wp->type) {
            case 0:
                FontDrawMessage(-75.2f + wp->x, 80.0f + wp->y, msgSearch("menu_subtitle1_minigame1"));
                break;
            case 3:
                FontDrawMessage(-75.2f + wp->x, 80.0f + wp->y, msgSearch("menu_subtitle1_minigame2"));
                break;
            case 2:
                FontDrawMessage(-75.2f + wp->x, 80.0f + wp->y, msgSearch("menu_subtitle1_minigame3"));
                break;
            case 1:
                FontDrawMessage(-75.2f + wp->x, 80.0f + wp->y, msgSearch("menu_subtitle1_minigame4"));
                break;
        }
        for (i = 0; i < 6; i++) {
            if (yuwp->used[wp->type][i] == 0) {
                continue;
            }
            ofs = 2.0f + i;
            if (i == 5) {
                ofs += 0.5f;
            }
            FontDrawStart();
            FontDrawScale(1.0f);
            if (i != wp->rank) {
                FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
            } else {
                FontDrawColor((GXColor){0xFF, 0x3F, 0x3F, 0xFF});
            }
            rk = (const u8*)ranks[i];
            if ((s32)rk[0] == 'm' && (s32)rk[1] == 'e' && (s32)rk[2] == 'n' && (s32)rk[3] == 'u' && (s32)rk[4] == '_') {
                rk = (const u8*)msgSearch((const char*)rk);
            }
            if (i == 5) {
                FontDrawMessage(18.8f + (-188.0f + wp->x), wp->y + (104.0f - 24.0f * ofs), (const char*)rk);
            } else {
                FontDrawStringPitch(-150.4f + wp->x, wp->y + (104.0f - 24.0f * ofs), 18.0f, str);
            }
            switch (wp->type) {
                case 0:
                    rscore = yuwp->score[wp->type][i];
                    if (rscore >= 0) {
                        sprintf(buf, "%3d%s%02d", yuwp->score[wp->type][i] / 1000, msgSearch("menu_decimal_point"), (rscore % 1000) / 10);
                        FontDrawStringPitch(-75.2f + wp->x, wp->y + (104.0f - 24.0f * ofs), 18.0f, buf);
                        sprintf(buf, "%4d", yuwp->pts[wp->type][i]);
                        FontDrawStringPitch(75.2f + wp->x, wp->y + (104.0f - 24.0f * ofs), 18.0f, buf);
                    } else {
                        sprintf(buf, msgSearch("menu_error_minigame1"));
                        FontDrawMessage(-75.2f + wp->x, wp->y + (104.0f - 24.0f * ofs), buf);
                    }
                    break;
                case 3:
                case 2:
                    rscore = yuwp->score[wp->type][i];
                    if (rscore >= 0) {
                        rsec = rscore / 1000;
                        rmin = rsec / 60;
                        rsec = rsec % 60;
                        sprintf(buf, "%1d%s%02d%s%02d", rmin, msgSearch("menu_colon"), rsec, msgSearch("menu_colon"), (rscore % 1000) / 10);
                        FontDrawStringPitch(-75.2f + wp->x, wp->y + (104.0f - 24.0f * ofs), 18.0f, buf);
                        sprintf(buf, "%4d", yuwp->pts[wp->type][i]);
                        FontDrawStringPitch(75.2f + wp->x, wp->y + (104.0f - 24.0f * ofs), 18.0f, buf);
                    } else {
                        if (wp->type == 3) {
                            sprintf(buf, msgSearch("menu_error_minigame2"));
                        } else {
                            sprintf(buf, msgSearch("menu_error_minigame3"));
                        }
                        FontDrawMessage(-75.2f + wp->x, wp->y + (104.0f - 24.0f * ofs), buf);
                    }
                    break;
                case 1:
                    if (yuwp->score[wp->type][i] < wp->max) {
                        sprintf(buf, "%4d", yuwp->score[wp->type][i] + 1);
                        FontDrawStringPitch(-37.6f + wp->x, wp->y + (104.0f - 24.0f * ofs), 18.0f, buf);
                        sprintf(buf, "%4d", yuwp->pts[wp->type][i]);
                        FontDrawStringPitch(75.2f + wp->x, wp->y + (104.0f - 24.0f * ofs), 18.0f, buf);
                    } else {
                        sprintf(buf, msgSearch("menu_error_minigame4"));
                        FontDrawMessage(-75.2f + wp->x, wp->y + (104.0f - 24.0f * ofs), buf);
                    }
                    break;
            }
        }
    }
}
