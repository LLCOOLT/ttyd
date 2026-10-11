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
// proto: static USER_FUNC(evt_tou_get_next_match);
static USER_FUNC(evt_tou_get_next_match) {
    s32* args = event->args;
    BOOL reverse = evtGetValue(event, GSWF(2443));
    s32 list[32];
    s32 num;
    s32 rank;
    s32 i;

    num = 0;
    for (i = 0; i < rank_wp->count; i++) {
        RankEntry* entry = &rank_wp->entries[i];
        if (!(entry->flags & RANK_HIDDEN)) {
            list[num++] = entry->id;
        }
    }
    rank = 0;
    for (i = 0; i < rank_wp->count; i++) {
        if (!(rank_wp->entries[i].flags & RANK_HIDDEN)) {
            if (rank_wp->entries[i].flags & RANK_PLAYER) {
                break;
            }
            rank++;
        }
    }
    if (rank > 0) {
        if (reverse) {
            evtSetValue(event, args[0], list[rank - 1]);
        } else if (rank + 1 < num) {
            evtSetValue(event, args[0], list[rank + 1]);
        } else {
            evtSetValue(event, args[0], list[rank - 1]);
        }
    } else {
        evtSetValue(event, args[0], list[1]);
    }
    printRanking();
    return EVT_RETURN_DONE;
}
