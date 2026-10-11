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
// include: system.h
// include: pmario_sound.h
// include: driver/dispdrv.h
// include: string.h
// decl: #define GET_RANK(rank, i) rank = 0; for (i = 0; i < rank_wp->num; i++) { if (!(rank_wp->entries[i].flags & 2)) { if (rank_wp->entries[i].flags & 4) { break; } rank++; } }
// decl: static void printRanking(void);
// decl: static void disp_proc(CameraId cameraId, void* param);
// proto: USER_FUNC(evt_tou_print_ranking);
USER_FUNC(evt_tou_print_ranking) {
    s32 rank;
    s32 i;

    if (isFirstCall) {
        memset(dwp, 0, sizeof(DispWork));
        GET_RANK(rank, i);
        dwp->page = rank / 11;
        dwp->y = dwp->targetY = dwp->page * 220;
        printRanking();
        return EVT_RETURN_BLOCK;
    }
    if (keyGetButtonTrg(0) & 0x200) {
        psndSFXOn((const char*)0x13);
        return EVT_RETURN_YIELD;
    }
    if (dwp->page > 0 && (keyGetButtonTrg(0) & 0x40)) {
        psndSFXOn((const char*)5);
        dwp->page--;
    }
    if (dwp->page < 1 && (keyGetButtonTrg(0) & 0x20)) {
        dwp->page++;
        psndSFXOn((const char*)5);
    }
    dwp->targetY = dwp->page * 220;
    dwp->y += (dwp->targetY - dwp->y) / 8.0f;
    dispEntry(CAMERA_2D, 300.0f, 0, disp_proc, NULL);
    return EVT_RETURN_BLOCK;
}
