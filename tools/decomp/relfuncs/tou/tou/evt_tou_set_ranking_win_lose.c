// include: manager/evtmgr_cmd.h
// include: driver/swdrv.h
// include: memory.h
// decl: typedef struct RankEntry { u16 flags; s32 id; union { s16 score; u8 sw[2]; }; } RankEntry;
// decl: typedef struct RankWork { s32 num; RankEntry* entries; } RankWork;
// decl: typedef struct DispWork { f32 y; f32 targetY; s32 page; } DispWork;
// decl: typedef struct FighterData { u16 flags; const char* name; const char* name2; s32 info; s32 msg1; s32 msg2; s16 score; } FighterData;
// decl: typedef struct RuleData { s32 name; const char* msg; s32 id; s32 a; s32 b; } RuleData;
// decl: static __declspec(section ".data") RankWork* rank_wp;
// decl: static __declspec(section ".data") DispWork* dwp;
// include: stdlib.h
// decl: static void rankingControll(void);
// proto: USER_FUNC(evt_tou_set_ranking_win_lose);
USER_FUNC(evt_tou_set_ranking_win_lose) {
    s32* args = event->args;
    s32 lose = evtGetValue(event, args[0]);
    s32 id = evtGetValue(event, args[1]);
    s32 i;
    s16 min;
    s16 max;
    s32 r;

    if (lose == 0) {
        for (i = 0; i < rank_wp->num; i++) {
            if (id == rank_wp->entries[i].id) {
                rank_wp->entries[i].flags |= 1;
                break;
            }
        }
        swSet(0x98A);
    } else {
        for (i = 0; i < rank_wp->num; i++) {
            if (id == rank_wp->entries[i].id) {
                rank_wp->entries[i].flags &= ~1;
                break;
            }
        }
        swClear(0x98A);
    }
    min = 1000;
    max = -1000;
    for (i = 0; i < rank_wp->num; i++) {
        if (!(rank_wp->entries[i].flags & 2)) {
            r = rand() % 4;
            rank_wp->entries[i].score += r + rand() % 4 - 3;
            if (rank_wp->entries[i].score < min) {
                min = rank_wp->entries[i].score;
            }
            if (rank_wp->entries[i].score > max) {
                max = rank_wp->entries[i].score;
            }
        }
    }
    swByteSet(0x1FB, id);
    swSet(0x9E4);
    rankingControll();
    return EVT_RETURN_DONE;
}
