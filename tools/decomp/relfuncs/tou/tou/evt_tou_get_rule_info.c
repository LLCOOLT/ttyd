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
// decl: static inline s32 getRank(void) { s32 i; s32 rank = 0; for (i = 0; i < rank_wp->num; i++) { if (!(rank_wp->entries[i].flags & 2)) { if (rank_wp->entries[i].flags & 4) { break; } else { rank++; } } } return rank; }
// decl: static s32 ruleDt_2bu_raw[50];
// decl: #define ruleDt_2bu ((RuleData*)ruleDt_2bu_raw)
// decl: static s32 ruleDt_1bu_raw[70];
// decl: #define ruleDt_1bu ((RuleData*)ruleDt_1bu_raw)
// decl: static s32 ruleDt_re_raw[70];
// decl: #define ruleDt_re ((RuleData*)ruleDt_re_raw)
// proto: USER_FUNC(evt_tou_get_rule_info);
USER_FUNC(evt_tou_get_rule_info) {
    s32* args = event->args;
    s32 mode = evtGetValue(event, args[0]);
    RuleData* dt;
    s32 num;
    s32 i;

    if (evtGetValue(NULL, GSW(0)) < 0xAC) {
        if (getRank() > 10) {
            num = 10;
            dt = ruleDt_2bu;
        } else {
            num = 14;
            dt = ruleDt_1bu;
        }
    } else {
        num = 14;
        dt = ruleDt_re;
    }
    if (mode == 0) {
        for (i = 0; i < num; i++) {
            if (dt[i].id == 6) {
                break;
            }
        }
    } else if (mode == 10) {
        do {
            i = rand() % num;
        } while (dt[i].id == 0x30 || dt[i].id == 0x20 || dt[i].id == 0x40);
    } else {
        i = rand() % num;
    }
    evtSetValue(event, args[1], dt[i].name);
    evtSetValue(event, args[2], dt[i].id);
    evtSetValue(event, args[3], dt[i].a);
    evtSetValue(event, args[4], dt[i].b);
    return EVT_RETURN_DONE;
}
