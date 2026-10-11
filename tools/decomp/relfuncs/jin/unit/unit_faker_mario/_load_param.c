// proto: USER_FUNC(_load_param);
USER_FUNC(_load_param) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id1 = evtGetValue(event, args[0]);
    s32 id2 = evtGetValue(event, args[1]);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id1));
    BattleUnit* party = BattleGetUnitPtr(wp, BattleTransID(event, id2));
    FakerParam* params = (FakerParam*)unit->countersetWeapon;
    FakerParam* p;

    switch (party->currentKind) {
        case 0x50:
            p = &params[0];
            break;
        case 0x51:
            p = &params[1];
            break;
        case 0x53:
            p = &params[2];
            break;
        case 0x52:
            p = &params[3];
            break;
    }
    party->mSizeMultiplier = p->size;
    party->mStatusFlags = p->statusFlags;
    *(FakerStatus*)&party->mSleepTurns = p->status;
    party->maxHp = p->maxHp;
    party->currentHp = p->currentHp;
    party->maxFp = p->maxFp;
    party->currentFp = p->currentFp;
    return EVT_RETURN_DONE;
}
