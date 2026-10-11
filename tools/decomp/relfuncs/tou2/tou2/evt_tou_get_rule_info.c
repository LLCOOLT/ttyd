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
// proto: static USER_FUNC(evt_tou_get_rule_info);
static USER_FUNC(evt_tou_get_rule_info) {
    s32* args = event->args;
    s32 type = evtGetValue(event, args[0]);
    s32 num;
    RuleData* rules;
    s32 i;
    s32 rank;

    if (evtGetValue(NULL, GSW(0)) < 172) {
        rank = 0;
        for (i = 0; i < rank_wp->count; i++) {
            if (!(rank_wp->entries[i].flags & RANK_HIDDEN)) {
                if (rank_wp->entries[i].flags & RANK_PLAYER) {
                    break;
                }
                rank++;
            }
        }
        if (rank > 10) {
            rules = ruleDt_2bu;
            num = 10;
        } else {
            rules = ruleDt_1bu;
            num = 14;
        }
    } else {
        rules = ruleDt_re;
        num = 14;
    }
    if (type == 0) {
        for (i = 0; i < num; i++) {
            if (rules[i].id == 6) {
                break;
            }
        }
    } else if (type == 10) {
        while (TRUE) {
            i = rand() % num;
            if (rules[i].id != 48 && rules[i].id != 32 && rules[i].id != 64) {
                break;
            }
        }
    } else {
        i = rand() % num;
    }
    evtSetValue(event, args[1], (s32)rules[i].name);
    evtSetValue(event, args[2], rules[i].id);
    evtSetValue(event, args[3], rules[i].field_C);
    evtSetValue(event, args[4], rules[i].field_10);
    return EVT_RETURN_DONE;
}
