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
// proto: USER_FUNC(unk_tou2_00004b50);
USER_FUNC(unk_tou2_00004b50) {
    s32 i;

    rankingExit();
    pouchRemoveItem(0x41);
    for (i = 0; i < 20; i++) {
        swClear(i + 2465);
    }
    swClear(2392);
    swClear(2399);
    swClear(2400);
    swClear(2383);
    swClear(2529);
    swClear(2532);
    swClear(2403);
    rankingInit();
    return EVT_RETURN_DONE;
}
