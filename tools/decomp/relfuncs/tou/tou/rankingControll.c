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
// decl: static inline s32 getRank(void) { s32 i; s32 rank = 0; for (i = 0; i < rank_wp->num; i++) { if (!(rank_wp->entries[i].flags & 2)) { if (rank_wp->entries[i].flags & 4) { break; } else { rank++; } } } return rank; }
// decl: static s32 fighterDt_raw[161];
// decl: #define fighterDt ((FighterData*)fighterDt_raw)
// decl: static void insert(s32* list, s32 num, s32 from, s32 to);
// decl: static inline void sortScore(s32* list, s32 num) { s32 i; s32 j; s32 a; s32 b; for (i = 0; i < num - 1; i++) { for (j = i + 1; j < num; j++) { a = list[i]; b = list[j]; if (rank_wp->entries[a].score < rank_wp->entries[b].score) { list[i] = b; list[j] = a; } } } }
// decl: static inline void sortFlag(s32* list, s32 num) { s32 i; s32 j; s32 a; s32 b; for (i = 0; i < num - 1; i++) { for (j = i + 1; j < num; j++) { b = list[j]; a = list[i]; if ((fighterDt[rank_wp->entries[b].id].flags & 5) && (fighterDt[rank_wp->entries[a].id].flags & 2)) { list[i] = b; list[j] = a; } } } }
// decl: static inline s32 findFlag(s32* list, s32 num, u16 flag) { s32 i; for (i = 0; i < num; i++) { if (fighterDt[rank_wp->entries[list[i]].id].flags & flag) { break; } } return i; }
// decl: static inline void moveFlag(s32* list, s32 num, u16 flag, s32 pos) { s32 i = findFlag(list, num, flag); if (i < num) { insert(list, num, i, pos); } }
// proto: static void rankingControll(void);
static void rankingControll(void) {
    s32 lose[32];
    s32 win[32];
    s32 nwin = 0;
    s32 nlose = 0;
    s32 i;
    s32 j;
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
        sortScore(win, nwin);
        sortFlag(win, nwin);
        if (nwin > 0) {
            moveFlag(win, nwin, 0x4, 0);
        }
        if (nwin > 1) {
            moveFlag(win, nwin, 0x1000, 1);
        }
        if (nwin > 10) {
            moveFlag(win, nwin, 0x800, 10);
        }
        if (nwin > 18) {
            moveFlag(win, nwin, 0x200, 18);
        }
        if (nwin > 19) {
            moveFlag(win, nwin, 0x400, 19);
        }
        if (nwin > 16) {
            moveFlag(win, nwin, 0x100, 14);
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
        sortScore(lose, nlose);
        sortFlag(lose, nlose);
        if (nlose > 0) {
            moveFlag(lose, nlose, 0x4, 0);
        }
        if (nlose > 0) {
            i = findFlag(lose, nlose, 0x800);
            if (i < nlose) {
                j = findFlag(lose, nlose, 0x2);
                if (j < nlose && j > 0) {
                    insert(lose, nlose, i, j - 1);
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
        work[nwin + i + 1] = rank_wp->entries[lose[i]];
    }
    memcpy(rank_wp->entries, work, rank_wp->num * sizeof(RankEntry));
    __memFree(HEAP_DEFAULT, work);
    swByteSet(0x244, getRank());
}
