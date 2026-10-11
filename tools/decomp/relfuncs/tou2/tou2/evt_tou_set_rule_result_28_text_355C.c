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
// proto: USER_FUNC(evt_tou_set_rule_result_28_text_355C);
USER_FUNC(evt_tou_set_rule_result_28_text_355C) {
    s32 result = evtGetValue(event, event->args[0]);

    if (result & 4) {
        swSet(2443);
    } else if (result & 2) {
        swClear(2443);
    } else if (result & 1) {
        swClear(2443);
    }
    return EVT_RETURN_DONE;
}
