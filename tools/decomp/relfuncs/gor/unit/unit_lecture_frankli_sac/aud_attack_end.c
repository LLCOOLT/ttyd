// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// proto: USER_FUNC(aud_attack_end);
USER_FUNC(aud_attack_end) {
    *(u32*)&_battleWorkPointer->field_19064[0x1C] |= 1;
    return EVT_RETURN_DONE;
}
