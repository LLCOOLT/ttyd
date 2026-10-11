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
// decl: static s32 fighterDt_raw[161];
// decl: #define fighterDt ((FighterData*)fighterDt_raw)
// decl: static s32 fighterDt_re_raw[147];
// decl: #define fighterDt_re ((FighterData*)fighterDt_re_raw)
// proto: USER_FUNC(evt_tou_get_fighter_battle_msg);
USER_FUNC(evt_tou_get_fighter_battle_msg) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    FighterData* dt;

    if (evtGetValue(NULL, GSW(0)) < 0xAC) {
        dt = fighterDt;
    } else {
        dt = fighterDt_re;
    }
    evtSetValue(event, args[1], dt[id].msg1);
    evtSetValue(event, args[2], dt[id].msg2);
    return EVT_RETURN_DONE;
}
