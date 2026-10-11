// decl: typedef struct YuuRankingWork { EventEntry* event; u16 flags; u32 dispFlags; f32 x; f32 y; s32 type; s32 mode; s32 score; s32 bonus; s32 mul; s32 rank; s32 max; s32 phase; s32 monte; s32 dispScore; s32 timer; } YuuRankingWork;
// decl: typedef struct YuuParlorRank { u8 pad[0x14]; s32 used[4][6]; s32 score[4][6]; s32 pts[4][6]; } YuuParlorRank;
// decl: extern YuuParlorRank* yuwp;
// decl: static YuuRankingWork* _wp;
// proto: s32 yuu_kesan(s32 type, s32 score, s32 bonus, s32 mul, s32 max);
s32 yuu_kesan(s32 type, s32 score, s32 bonus, s32 mul, s32 max) {
    s32 ret;

    if (score < 0) {
        return 0;
    }
    switch (type) {
        case 0:
            ret = score / 30000;
            break;
        case 3:
            ret = (score - 74000) / 2000;
            break;
        case 2:
            ret = (score - 109000) / 2000;
            break;
        case 1:
            ret = ((max - score) * 15) / max;
            break;
    }
    if (ret < 0) {
        ret = 0;
    }
    ret += bonus;
    if (mul > 0) {
        if (mul < 0x100) {
            ret *= mul;
        } else {
            ret += mul - 0x100;
        }
    } else {
        ret += mul;
        if (ret < 0) {
            ret = 0;
        }
    }
    if (ret < 0) {
        ret = 0;
    }
    return ret;
}
