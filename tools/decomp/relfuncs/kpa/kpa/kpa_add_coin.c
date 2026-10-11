// include: manager/evtmgr_cmd.h
// include: mario/mario_pouch.h
// decl: void kpaAddCoinPos(s32 num, Vec* pos);
// proto: USER_FUNC(kpa_add_coin);
USER_FUNC(kpa_add_coin) {
    s32* args = event->args;

    kpaAddCoinPos(1, &(Vec){evtGetFloat(event, args[0]), evtGetFloat(event, args[1]), evtGetFloat(event, args[2])});
    pouchAddCoin(-1);
    return EVT_RETURN_DONE;
}
