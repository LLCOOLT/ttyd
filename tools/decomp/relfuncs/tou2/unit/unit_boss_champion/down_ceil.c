// include: battle/battle.h
// include: battle/battle_stage_object.h
// include: system.h
// proto: USER_FUNC(down_ceil);
USER_FUNC(down_ceil) {
    u8* ceil = &_battleWorkPointer->field_180DC;
    BattleStageObject* body = BattleSearchObjectPtr("if_body");
    BattleStageObject* wire = BattleSearchObjectPtr("if_wire");

    if (isFirstCall) {
        event->userdata[0] = 120;
        *ceil &= ~0x20;
    }
    body->mPosition.y = wire->mPosition.y = intplGetValue(4, 120 - event->userdata[0], 120, 250.0f, 130.0f);
    event->userdata[0]--;
    if (event->userdata[0] < 0) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
