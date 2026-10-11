// include: tou2.h
// include: dolphin/types.h
// include: dolphin/mtx.h
// include: dolphin/gx.h
// include: driver/swdrv.h
// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: driver/camdrv.h
// include: driver/effdrv.h
// include: driver/dispdrv.h
// include: driver/windowdrv.h
// include: driver/icondrv.h
// include: driver/msgdrv.h
// include: manager/fontmgr.h
// include: manager/evtmgr_cmd.h
// include: evt/evt_cmd.h
// include: battle/battle_monosiri.h
// include: data/mapdata.h
// include: mario/mario_pouch.h
// include: pmario_sound.h
// include: system.h
// include: memory.h
// include: string.h
// include: stdio.h
// note: tou2.c is hand-maintained (typed data/structs are defined there); this snippet mirrors it
// proto: static USER_FUNC(evt_tou_print_ranking);
static USER_FUNC(evt_tou_print_ranking) {
    s32 i;
    s32 rank;

    if (isFirstCall) {
        memset(dwp, 0, sizeof(DispWork));
        rank = 0;
        for (i = 0; i < rank_wp->count; i++) {
            if (!(rank_wp->entries[i].flags & RANK_HIDDEN)) {
                if (rank_wp->entries[i].flags & RANK_PLAYER) {
                    break;
                }
                rank++;
            }
        }
        dwp->page = rank / 11;
        dwp->scroll = dwp->target = dwp->page * 220;
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
    dwp->target = dwp->page * 220;
    dwp->scroll += (dwp->target - dwp->scroll) / 8.0f;
    dispEntry(CAMERA_2D, 300.0f, 0, disp_proc, NULL);
    return EVT_RETURN_BLOCK;
}
