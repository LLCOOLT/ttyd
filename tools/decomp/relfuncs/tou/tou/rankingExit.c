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
// proto: static void rankingExit(void);
static void rankingExit(void) {
    s32 i;
    s32 j;
    RankEntry* entry = rank_wp->entries;

    for (i = 0; i < rank_wp->num; i++, entry++) {
        if (entry->flags & 1) {
            swSet(entry->id + 0x9A1);
        } else {
            swClear(entry->id + 0x9A1);
        }
        for (j = 0; j < 2; j++) {
            swByteSet(entry->id * 2 + j + 0x207, entry->sw[j]);
        }
    }
    _mapFree(rank_wp->entries);
}
