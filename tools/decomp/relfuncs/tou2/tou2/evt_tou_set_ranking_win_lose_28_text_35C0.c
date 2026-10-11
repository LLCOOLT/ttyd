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
// proto: USER_FUNC(evt_tou_set_ranking_win_lose_28_text_35C0);
USER_FUNC(evt_tou_set_ranking_win_lose_28_text_35C0) {
    s32* args = event->args;
    s32 lose = evtGetValue(event, args[0]);
    s32 id = evtGetValue(event, args[1]);
    s16 min;
    s16 max;
    s32 i;

    if (lose == 0) {
        for (i = 0; i < rank_wp->count; i++) {
            if (id == rank_wp->entries[i].id) {
                rank_wp->entries[i].flags |= RANK_BELOW;
                break;
            }
        }
        swSet(2442);
    } else {
        for (i = 0; i < rank_wp->count; i++) {
            if (id == rank_wp->entries[i].id) {
                rank_wp->entries[i].flags &= ~RANK_BELOW;
                break;
            }
        }
        swClear(2442);
    }

    min = 1000;
    max = -1000;
    for (i = 0; i < rank_wp->count; i++) {
        if (!(rank_wp->entries[i].flags & RANK_HIDDEN)) {
            s32 a = rand() % 4;
            a += rand() % 4;
            rank_wp->entries[i].points.total = a + rank_wp->entries[i].points.total - 3;
            if (rank_wp->entries[i].points.total < min) {
                min = rank_wp->entries[i].points.total;
            }
            if (rank_wp->entries[i].points.total > max) {
                max = rank_wp->entries[i].points.total;
            }
        }
    }
    swByteSet(507, id);
    swSet(2532);
    rankingControll();
    return EVT_RETURN_DONE;
}
