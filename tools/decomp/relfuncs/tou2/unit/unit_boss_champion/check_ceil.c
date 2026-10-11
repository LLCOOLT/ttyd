// include: battle/battle.h
// proto: USER_FUNC(check_ceil);
USER_FUNC(check_ceil) {
    event->lwData[1] = _battleWorkPointer->field_180DC & 0x20;
    return EVT_RETURN_DONE;
}
