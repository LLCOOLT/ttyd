// include: battle/battle.h
// include: battle/battle_stage_object.h
// proto: USER_FUNC(init_ceil);
USER_FUNC(init_ceil) {
    u8* ceil = &_battleWorkPointer->field_180DC;
    BattleStageObject* body = BattleSearchObjectPtr("if_body");
    BattleStageObject* wire = BattleSearchObjectPtr("if_wire");

    wire->mPosition = (Vec){0.0f, 250.0f, 0.0f};
    body->mPosition = wire->mPosition;
    *ceil |= 0x20;
    return EVT_RETURN_DONE;
}
