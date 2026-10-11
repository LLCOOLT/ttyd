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
// proto: static void rankingControll(void);
static void rankingControll(void) {
    s32 above[32];
    s32 below[32];
    s32 nBelow;
    s32 i;
    s32 tmp;
    s32 idx2;
    s32 idx;

    s32 rank;
    s32 nAbove;
    s32 j;
    RankEntry* entry;
    nAbove = 0;
    nBelow = 0;
    for (i = 0, entry = rank_wp->entries; i < rank_wp->count; i++, entry++) {
        if (!(entry->flags & RANK_PLAYER)) {
            if (entry->flags & RANK_BELOW) {
                below[nBelow] = i;
                nBelow++;
            } else {
                above[nAbove] = i;
                nAbove++;
            }
        }
    }

    if (nAbove > 0) {
        for (i = 0; i < nAbove - 1; i++) {
            for (j = i + 1; j < nAbove; j++) {
                if (rank_wp->entries[above[i]].points.total < rank_wp->entries[above[j]].points.total) {
                    tmp = above[i];
                    above[i] = above[j];
                    above[j] = tmp;
                }
            }
        }

        for (i = 0; i < nAbove - 1; i++) {
            for (j = i + 1; j < nAbove; j++) {
                FighterData* fj = &fighterDt[rank_wp->entries[above[j]].id];
                FighterData* fi = &fighterDt[rank_wp->entries[above[i]].id];
                if ((fj->flags & 5) && (fi->flags & 2)) {
                    tmp = above[i];
                    above[i] = above[j];
                    above[j] = tmp;
                }
            }
        }

        if (nAbove > 0) {
            for (idx = 0; idx < nAbove; idx++) {
                if (fighterDt[rank_wp->entries[above[idx]].id].flags & 4) {
                    break;
                }
            }
            if (idx < nAbove) {
                insert(above, nAbove, idx, 0);
            }
        }

        if (nAbove > 1) {
            for (idx = 0; idx < nAbove; idx++) {
                if (fighterDt[rank_wp->entries[above[idx]].id].flags & 0x1000) {
                    break;
                }
            }
            if (idx < nAbove) {
                insert(above, nAbove, idx, 1);
            }
        }

        if (nAbove > 10) {
            for (idx = 0; idx < nAbove; idx++) {
                if (fighterDt[rank_wp->entries[above[idx]].id].flags & 0x800) {
                    break;
                }
            }
            if (idx < nAbove) {
                insert(above, nAbove, idx, 10);
            }
        }

        if (nAbove > 18) {
            for (idx = 0; idx < nAbove; idx++) {
                if (fighterDt[rank_wp->entries[above[idx]].id].flags & 0x200) {
                    break;
                }
            }
            if (idx < nAbove) {
                insert(above, nAbove, idx, 18);
            }
        }

        if (nAbove > 19) {
            for (idx = 0; idx < nAbove; idx++) {
                if (fighterDt[rank_wp->entries[above[idx]].id].flags & 0x400) {
                    break;
                }
            }
            if (idx < nAbove) {
                insert(above, nAbove, idx, 19);
            }
        }

        if (nAbove > 16) {
            for (idx = 0; idx < nAbove; idx++) {
                if (fighterDt[rank_wp->entries[above[idx]].id].flags & 0x100) {
                    break;
                }
            }
            if (idx < nAbove) {
                insert(above, nAbove, idx, 14);
            }
        }

        // Check if a match is booked (2532), and move our opponent (507) to above us for the fight. 
        if (swGet(2532)) {
            for (idx = 0; idx < nAbove; idx++) {
                if (above[idx] == swByteGet(507)) {
                    break;
                }
            }
            if (idx < nAbove) {
                insert(above, nAbove, idx, nAbove - 1);
            }
        }
    }

    if (nBelow > 0) {
        for (i = 0; i < nBelow - 1; i++) {
            for (j = i + 1; j < nBelow; j++) {
                if (rank_wp->entries[below[i]].points.total < rank_wp->entries[below[j]].points.total) {
                    tmp = below[i];
                    below[i] = below[j];
                    below[j] = tmp;
                }
            }
        }

        for (i = 0; i < nBelow - 1; i++) {
            for (j = i + 1; j < nBelow; j++) {
                FighterData* fj = &fighterDt[rank_wp->entries[below[j]].id];
                FighterData* fi = &fighterDt[rank_wp->entries[below[i]].id];
                if ((fj->flags & 5) && (fi->flags & 2)) {
                    tmp = below[i];
                    below[i] = below[j];
                    below[j] = tmp;
                }
            }
        }

        if (nBelow > 0) {
            for (idx = 0; idx < nBelow; idx++) {
                if (fighterDt[rank_wp->entries[below[idx]].id].flags & 4) {
                    break;
                }
            }
            if (idx < nBelow) {
                insert(below, nBelow, idx, 0);
            }
        }
        
        if (nBelow > 0) {
            for (idx = 0; idx < nBelow; idx++) {
                if (fighterDt[rank_wp->entries[below[idx]].id].flags & 0x800) {
                    break;
                }
            }
            if (idx < nBelow) {
                for (idx2 = 0; idx2 < nBelow; idx2++) {
                    if (fighterDt[rank_wp->entries[below[idx2]].id].flags & 2) {
                        break;
                    }
                }
                if (idx2 < nBelow && idx2 > 0) {
                    insert(below, nBelow, idx, idx2 - 1);
                }
            }
        }

        // Check if a match is booked (2532), and move our opponent (507) to above us for the fight.
        if (swGet(2532)) {
            for (idx = 0; idx < nBelow; idx++) {
                if (below[idx] == swByteGet(507)) {
                    break;
                }
            }
            if (idx < nBelow) {
                insert(below, nBelow, idx, 0);
            }
        }
    }

    entry = (RankEntry*)__memAlloc(0, sizeof(RankEntry) * rank_wp->count);
    for (i = 0; i < nAbove; i++) {
        entry[i] = rank_wp->entries[above[i]];
    }
    // TODO: fixup
    entry[nAbove].flags = RANK_PLAYER;
    entry[nAbove].id = FIGHTER_PLAYER;
    entry[nAbove].points.total = 0;
    for (i = 0; i < nBelow; i++) {
        j = nAbove + 1 + i;
        entry[j] = rank_wp->entries[below[i]];
    }
    memcpy(rank_wp->entries, entry, sizeof(RankEntry) * rank_wp->count);
    __memFree(0, entry);

    // Calculate our current rank and store it in 580.
    rank = 0;
    for (i = 0; i < rank_wp->count; i++) {
        if (!(rank_wp->entries[i].flags & RANK_HIDDEN)) {
            if (rank_wp->entries[i].flags & RANK_PLAYER) {
                break;
            }
            rank++;
        }
    }
    swByteSet(580, rank);
}
