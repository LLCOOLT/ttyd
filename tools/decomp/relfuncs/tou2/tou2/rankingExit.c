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
// proto: static void rankingExit(void);
#pragma dont_inline on
static void rankingExit(void) {
    s32 i;
    s32 j;
    RankEntry* entry;

    for (i = 0, entry = rank_wp->entries; i < rank_wp->count; i++, entry++) {
        if (entry->flags & RANK_BELOW) {
            swSet(entry->id + 2465);
        } else {
            swClear(entry->id + 2465);
        }
        for (j = 0; j < 2; j++) {
            swByteSet(2 * entry->id + 519 + j, entry->points.bytes[j]);
        }
    }
    _mapFree(rank_wp->entries);
}
#pragma dont_inline reset
