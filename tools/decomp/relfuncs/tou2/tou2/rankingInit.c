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
// proto: static void rankingInit(void);
static void rankingInit(void) {
    s32 temp;
    s32 count;
    int i;
    RankEntry* entry;

    memset(rank_wp, 0, sizeof(RankData));
    // We need to handle the excluded entries if we're doing rematches
    temp = evtGetValue(NULL, GSW(0));
    count = 21;
    if (temp < 172) {
        count = 23;
    }
    rank_wp->count = count;
    rank_wp->entries = _mapAlloc(rank_wp->count * sizeof(RankEntry));
    memset(rank_wp->entries, 0, rank_wp->count * sizeof(RankEntry));

    for (i = 0, entry = rank_wp->entries; i < rank_wp->count; i++, entry++) {
        entry->flags = 0;
        entry->id = i;
        if (swGet(entry->id + 2465)) {
            entry->flags |= RANK_BELOW;
        }
        if (swGet(2529)) {
            int j;
            for (j = 0; j < 2; j++) {
                entry->points.bytes[j] = swByteGet(2 * entry->id + 519 + j);
            }
        } else {
            entry->points.total = fighterDt[entry->id].field_18;
        }
        if (entry->id == FIGHTER_PLAYER) {
            entry->flags |= RANK_PLAYER;
        }
    }

    swSet(2529);

    // Set up the initial run-through
    if (evtGetValue(NULL, GSW(0)) < 172) {
        rank_wp->entries[FIGHTER_SWOOPS].flags |= RANK_HIDDEN;
        rank_wp->entries[FIGHTER_SPINIA].flags |= RANK_HIDDEN;

        // If we're past this point in the story, hide King K
        if (evtGetValue(NULL, GSWF(2412))) {
            rank_wp->entries[FIGHTER_KP_KOOPAS].flags |= RANK_HIDDEN;
        }

        // If we're past this story, Sir Swoop has been introduced
        if (evtGetValue(NULL, GSWF(2413))) {
            rank_wp->entries[FIGHTER_SWOOPS].flags &= ~RANK_HIDDEN;

            if (!evtGetValue(NULL, GSWF(2530))) {
                rank_wp->entries[FIGHTER_SWOOPS].flags |= RANK_BELOW;
            }
            evtSetValue(NULL, GSWF(2530), TRUE);
        }

        // If we're past this point in the story, Bandy Andy got "retired" and The Destructors were added.
        if (evtGetValue(NULL, GSWF(2421))) {
            rank_wp->entries[FIGHTER_BANDITS].flags |= RANK_HIDDEN;
            rank_wp->entries[FIGHTER_SPINIA].flags &= ~RANK_HIDDEN;

            if (!evtGetValue(NULL, GSWF(2531))) {
                rank_wp->entries[FIGHTER_SPINIA].flags |= RANK_BELOW;
            }
            evtSetValue(NULL, GSWF(2531), TRUE);
        }
    }
    rankingControll();
}
