// include: battle/battle.h
// proto: USER_FUNC(_set_destroy_flag);
USER_FUNC(_set_destroy_flag) {
    _battleWorkPointer->field_180DC |= 8;
    return EVT_RETURN_DONE;
}
