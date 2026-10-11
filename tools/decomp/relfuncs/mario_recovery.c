// include: mario/mario_pouch.h
// proto: USER_FUNC(mario_recovery);
USER_FUNC(mario_recovery) {
    pouchSetHP(pouchGetMaxHP());
    pouchSetFP(pouchGetMaxFP());
    return EVT_RETURN_DONE;
}
