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
// decl: #define GET_RANK(rank, i) rank = 0; for (i = 0; i < rank_wp->num; i++) { if (!(rank_wp->entries[i].flags & 2)) { if (rank_wp->entries[i].flags & 4) { break; } rank++; } }
// decl: static s32 fighterDt_raw[161];
// decl: #define fighterDt ((FighterData*)fighterDt_raw)
// decl: static void insert(s32* list, s32 num, s32 from, s32 to);
// decl: #define SORT_SCORE(list, n) for (i = 0; i < n - 1; i++) { for (j = i + 1; j < n; j++) { if (rank_wp->entries[list[i]].score < rank_wp->entries[list[j]].score) { tmp = list[i]; list[i] = list[j]; list[j] = tmp; } } }
// decl: #define SORT_FLAG(list, n) for (i = 0; i < n - 1; i++) { for (j = i + 1; j < n; j++) { pb = &fighterDt[rank_wp->entries[list[i]].id]; if ((fighterDt[rank_wp->entries[list[j]].id].flags & 5) && (pb->flags & 2)) { tmp = list[i]; list[i] = list[j]; list[j] = tmp; } } }
// decl: #define FIND_FLAG(k, list, n, flag) for (k = 0; k < n; k++) { if (fighterDt[rank_wp->entries[list[k]].id].flags & flag) { break; } }
// decl: #define MOVE_FLAG(list, n, flag, pos) FIND_FLAG(k, list, n, flag); if (k < n) { insert(list, n, k, pos); }
// proto: static void rankingControll(void);
static void rankingControll(void) {
    s32 win[32];
    s32 lose[32];
    s32 nwin = 0;
    s32 nlose = 0;
    s32 i;
    s32 j;
    s32 m;
    s32 k;
    s32 tmp;
    FighterData* pb;
    RankEntry* entry;
    RankEntry* work;

    entry = rank_wp->entries;
    for (i = 0; i < rank_wp->num; i++, entry++) {
        if (!(entry->flags & 4)) {
            if (entry->flags & 1) {
                lose[nlose++] = i;
            } else {
                win[nwin++] = i;
            }
        }
    }
    if (nwin > 0) {
        SORT_SCORE(win, nwin);
        SORT_FLAG(win, nwin);
        if (nwin > 0) {
            MOVE_FLAG(win, nwin, 0x4, 0);
        }
        if (nwin > 1) {
            MOVE_FLAG(win, nwin, 0x1000, 1);
        }
        if (nwin > 10) {
            MOVE_FLAG(win, nwin, 0x800, 10);
        }
        if (nwin > 18) {
            MOVE_FLAG(win, nwin, 0x200, 18);
        }
        if (nwin > 19) {
            MOVE_FLAG(win, nwin, 0x400, 19);
        }
        if (nwin > 16) {
            MOVE_FLAG(win, nwin, 0x100, 14);
        }
        if (swGet(0x9E4)) {
            for (i = 0; i < nwin; i++) {
                if (win[i] == swByteGet(0x1FB)) {
                    break;
                }
            }
            if (i < nwin) {
                insert(win, nwin, i, nwin - 1);
            }
        }
    }
    if (nlose > 0) {
        SORT_SCORE(lose, nlose);
        SORT_FLAG(lose, nlose);
        if (nlose > 0) {
            MOVE_FLAG(lose, nlose, 0x4, 0);
        }
        if (nlose > 0) {
            FIND_FLAG(m, lose, nlose, 0x800);
            if (m < nlose) {
                FIND_FLAG(k, lose, nlose, 0x2);
                if (k < nlose && k > 0) {
                    insert(lose, nlose, m, k - 1);
                }
            }
        }
        if (swGet(0x9E4)) {
            for (i = 0; i < nlose; i++) {
                if (lose[i] == swByteGet(0x1FB)) {
                    break;
                }
            }
            if (i < nlose) {
                insert(lose, nlose, i, 0);
            }
        }
    }
    work = __memAlloc(HEAP_DEFAULT, rank_wp->num * sizeof(RankEntry));
    for (i = 0; i < nwin; i++) {
        work[i] = rank_wp->entries[win[i]];
    }
    work[nwin].flags = 4;
    work[nwin].id = 20;
    work[nwin].score = 0;
    for (i = 0; i < nlose; i++) {
        work[nwin + 1 + i] = rank_wp->entries[lose[i]];
    }
    memcpy(rank_wp->entries, work, rank_wp->num * sizeof(RankEntry));
    __memFree(HEAP_DEFAULT, work);
    GET_RANK(j, i);
    swByteSet(0x244, j);
}
