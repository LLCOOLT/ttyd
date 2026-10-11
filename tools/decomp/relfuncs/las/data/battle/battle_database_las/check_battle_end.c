// include: battle/battle.h
// proto: USER_FUNC(check_battle_end);
USER_FUNC(check_battle_end) {
    return battleSeqEndCheck() ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
