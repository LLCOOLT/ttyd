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
// decl: #define GET_RANK(rank, i) rank = 0; for (i = 0; i < rank_wp->num; i++) { if (!(rank_wp->entries[i].flags & 2)) { if (rank_wp->entries[i].flags & 4) { break; } rank++; } }
// decl: static void printRanking(void);
// proto: USER_FUNC(evt_tou_get_next_match);
USER_FUNC(evt_tou_get_next_match) {
    s32* args = event->args;
    s32 flag = evtGetValue(event, GSWF(2443));
    s32 rank;
    RankEntry* entry;
    s32 i;
    s32 n = 0;
    s32 list[32];

    for (i = 0; i < rank_wp->num; i++) {
        entry = &rank_wp->entries[i];
        if (!(entry->flags & 2)) {
            list[n++] = entry->id;
        }
    }
    GET_RANK(rank, i);
    if (rank > 0) {
        if (flag) {
            evtSetValue(event, args[0], list[rank - 1]);
        } else if (rank + 1 < n) {
            evtSetValue(event, args[0], list[rank + 1]);
        } else {
            evtSetValue(event, args[0], list[rank - 1]);
        }
    } else {
        evtSetValue(event, args[0], list[1]);
    }
    printRanking();
    return EVT_RETURN_DONE;
}
