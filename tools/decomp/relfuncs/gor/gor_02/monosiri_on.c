// include: manager/evtmgr_cmd.h
// include: battle/battle_monosiri.h
// include: driver/msgdrv.h
// include: driver/swdrv.h
// proto: USER_FUNC(monosiri_on);
USER_FUNC(monosiri_on) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    TattleEntry* tattle = battleGetUnitMonosiriPtr(id);

    swSet(id + 0x117A);
    evtSetValue(event, args[1], (s32)msgSearch(tattle->enemyTag));
    return EVT_RETURN_DONE;
}
