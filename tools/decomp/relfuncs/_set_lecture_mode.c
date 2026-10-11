// include: battle/battle.h
// include: battle/battle_sub.h
// proto: USER_FUNC(_set_lecture_mode);
USER_FUNC(_set_lecture_mode) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = BattleTransID(event, -3);
    BattleUnit* unit = BattleGetUnitPtr(wp, id);

    unit->mAttributeFlags |= 0x40000000;
    wp->lectureMode = 1;
    return EVT_RETURN_DONE;
}
