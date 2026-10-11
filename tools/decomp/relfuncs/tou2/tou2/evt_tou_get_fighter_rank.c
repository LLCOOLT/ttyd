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
// proto: static USER_FUNC(evt_tou_get_fighter_rank);
static USER_FUNC(evt_tou_get_fighter_rank) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 rank = 0;
    s32 i;

    for (i = 0; i < rank_wp->count; i++) {
        RankEntry* entry = &rank_wp->entries[i];
        if (!(entry->flags & RANK_HIDDEN)) {
            if (id == entry->id) {
                break;
            }
            rank++;
        }
    }
    evtSetValue(event, args[1], rank);
    return EVT_RETURN_DONE;
}
