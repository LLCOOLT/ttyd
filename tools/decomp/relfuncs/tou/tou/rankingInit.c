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
// include: string.h
// decl: static s32 fighterDt_raw[161];
// decl: #define fighterDt ((FighterData*)fighterDt_raw)
// decl: static s32 fighterDt_re_raw[147];
// decl: #define fighterDt_re ((FighterData*)fighterDt_re_raw)
// decl: static void rankingControll(void);
// proto: static void rankingInit(void);
static void rankingInit(void) {
    s32 i;
    s32 j;
    RankEntry* entry;

    memset(rank_wp, 0, sizeof(RankWork));
    rank_wp->num = evtGetValue(NULL, GSW(0)) < 0xAC ? 23 : 21;
    rank_wp->entries = _mapAlloc(rank_wp->num * sizeof(RankEntry));
    memset(rank_wp->entries, 0, rank_wp->num * sizeof(RankEntry));
    entry = rank_wp->entries;
    for (i = 0; i < rank_wp->num; i++, entry++) {
        entry->flags = 0;
        entry->id = i;
        if (swGet(entry->id + 0x9A1)) {
            entry->flags |= 1;
        }
        if (swGet(0x9E1)) {
            for (j = 0; j < 2; j++) {
                entry->sw[j] = swByteGet(j + (entry->id * 2 + 0x207));
            }
        } else {
            entry->score = fighterDt[entry->id].score;
        }
        if (entry->id == 20) {
            entry->flags |= 4;
        }
    }
    swSet(0x9E1);
    if (evtGetValue(NULL, GSW(0)) < 0xAC) {
        rank_wp->entries[21].flags |= 2;
        rank_wp->entries[22].flags |= 2;
        if (evtGetValue(NULL, GSWF(2412))) {
            rank_wp->entries[18].flags |= 2;
        }
        if (evtGetValue(NULL, GSWF(2413))) {
            rank_wp->entries[21].flags &= ~2;
            if (!evtGetValue(NULL, GSWF(2530))) {
                rank_wp->entries[21].flags |= 1;
            }
            evtSetValue(NULL, GSWF(2530), 1);
        }
        if (evtGetValue(NULL, GSWF(2421))) {
            rank_wp->entries[11].flags |= 2;
            rank_wp->entries[22].flags &= ~2;
            if (!evtGetValue(NULL, GSWF(2531))) {
                rank_wp->entries[22].flags |= 1;
            }
            evtSetValue(NULL, GSWF(2531), 1);
        }
    }
    rankingControll();
}
