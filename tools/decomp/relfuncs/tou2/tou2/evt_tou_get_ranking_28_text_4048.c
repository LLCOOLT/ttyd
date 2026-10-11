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
// proto: USER_FUNC(evt_tou_get_ranking_28_text_4048);
USER_FUNC(evt_tou_get_ranking_28_text_4048) {
    s32* args = event->args;
    s32 i;
    s32 rank;

    rank = 0;
    for (i = 0; i < rank_wp->count; i++) {
        if (!(rank_wp->entries[i].flags & RANK_HIDDEN)) {
            if (rank_wp->entries[i].flags & RANK_PLAYER) {
                break;
            }
            rank++;
        }
    }
    evtSetValue(event, args[0], rank);
    return EVT_RETURN_DONE;
}
