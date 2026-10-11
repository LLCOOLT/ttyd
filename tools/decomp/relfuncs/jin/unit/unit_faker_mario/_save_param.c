// decl: typedef struct FakerStatus { s16 data[15]; } FakerStatus;
// decl: typedef struct FakerParam { f32 size; FakerStatus status; s32 statusFlags; s16 currentHp; s16 maxHp; s16 currentFp; s16 maxFp; } FakerParam;
// proto: USER_FUNC(_save_param);
USER_FUNC(_save_param) {
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
    p->size = party->mSizeMultiplier;
    p->statusFlags = party->mStatusFlags;
    p->status = *(FakerStatus*)&party->mSleepTurns;
    p->maxHp = party->maxHp;
    p->currentHp = party->currentHp;
    p->maxFp = party->maxFp;
    p->currentFp = party->currentFp;
    return EVT_RETURN_DONE;
}
