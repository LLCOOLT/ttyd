// include: battle/battle.h
// proto: USER_FUNC(ceil_exist);
USER_FUNC(ceil_exist) {
    s32* args = event->args;

    if (_battleWorkPointer->field_180DC & 0x20) {
        evtSetValue(event, args[0], 0);
    } else {
        evtSetValue(event, args[0], 1);
    }
    return EVT_RETURN_DONE;
}
