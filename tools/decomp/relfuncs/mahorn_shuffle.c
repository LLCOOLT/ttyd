// include: battle/battle.h
// include: battle/battle_unit.h
// include: system.h
// proto: static USER_FUNC(mahorn_shuffle);
static USER_FUNC(mahorn_shuffle) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* kamecs[6];
    s32 n = 0;
    s32 i;

    // the real wizzerd and its copies
    for (i = 0; i < 64; i++) {
        kamecs[n] = wp->units[i];
        if (kamecs[n] != NULL && (kamecs[n]->currentKind == 0x80 || kamecs[n]->currentKind == 0x81 || kamecs[n]->currentKind == 0xA9 || kamecs[n]->currentKind == 0xAA)) {
            n++;
        }
    }
    for (i = 0; i < 10; i++) {
        s32 a = irand(n);
        s32 b = irand(n);
        BattleUnit* ua = kamecs[a];
        BattleUnit* ub = kamecs[b];
        f32 tmp;

        tmp = ua->mPosition.x;
        ua->mPosition.x = ub->mPosition.x;
        ub->mPosition.x = tmp;
        tmp = ua->mHomePosition.x;
        ua->mHomePosition.x = ub->mHomePosition.x;
        ub->mHomePosition.x = tmp;
        tmp = ua->mPosition.z;
        ua->mPosition.z = ub->mPosition.z;
        ub->mPosition.z = tmp;
        tmp = ua->mHomePosition.z;
        ua->mHomePosition.z = ub->mHomePosition.z;
        ub->mHomePosition.z = tmp;
    }
    return EVT_RETURN_DONE;
}
