// include: mario/mario_pouch.h
// include: string.h
// proto: USER_FUNC(_gullible_party_info_init);
USER_FUNC(_gullible_party_info_init) {
    PouchData* pouch = pouchGetPtr();
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    FakerParam* params = BattleAlloc(sizeof(FakerParam) * 4);
    s32 i;
    FakerParam* p;

    unit->countersetWeapon = (struct BattleWeapon*)params;
    memset(params, 0, sizeof(FakerParam) * 4);
    for (i = 0; i < 4; i++) {
        p = &params[i];
        p->size = 1.0f;
        p->statusFlags = 0;
        memset(&p->status, 0, sizeof(FakerStatus));
        switch (i) {
            case 0:
                p->maxHp = p->currentHp = pouch->partyData[1].baseMaxHP;
                break;
            case 1:
                p->maxHp = p->currentHp = pouch->partyData[2].baseMaxHP;
                break;
            case 2:
                p->maxHp = p->currentHp = pouch->partyData[5].baseMaxHP;
                break;
            default:
                p->maxHp = p->currentHp = pouch->partyData[4].baseMaxHP;
                break;
        }
        p->maxFp = p->currentFp = pouch->baseMaxFP;
    }
    return EVT_RETURN_DONE;
}
