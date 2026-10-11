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
// proto: USER_FUNC(evt_tou_get_fighter_rank);
USER_FUNC(evt_tou_get_fighter_rank) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 rank = 0;
    s32 i;
    RankEntry* entry;

    for (i = 0; i < rank_wp->num; i++) {
        entry = &rank_wp->entries[i];
        if (!(entry->flags & 2)) {
            if (id == entry->id) {
                break;
            }
            rank++;
        }
    }
    evtSetValue(event, args[1], rank);
    return EVT_RETURN_DONE;
}
