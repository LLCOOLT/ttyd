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
// proto: USER_FUNC(evt_tou_get_fighter_battle_msg_28_text_3CB4);
USER_FUNC(evt_tou_get_fighter_battle_msg_28_text_3CB4) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    FighterData* fighters = evtGetValue(NULL, GSW(0)) < 172 ? fighterDt : fighterDt_re;

    evtSetValue(event, args[1], (s32)fighters[id].taunt);
    evtSetValue(event, args[2], (s32)fighters[id].victory);
    return EVT_RETURN_DONE;
}
