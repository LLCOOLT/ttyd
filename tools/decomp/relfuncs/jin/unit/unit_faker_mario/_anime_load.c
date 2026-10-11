// proto: static USER_FUNC(_anime_load);
static USER_FUNC(_anime_load) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    s32 anime;

    switch (unit->currentKind) {
        case 0x50:
            anime = 0xE0;
            break;
        case 0x51:
            anime = 0xE1;
            break;
        case 0x53:
            anime = 0xE3;
            break;
        case 0x52:
        default:
            anime = 0xE2;
            break;
    }
    BattlePartyAnimeLoad(anime);
    return EVT_RETURN_DONE;
}
