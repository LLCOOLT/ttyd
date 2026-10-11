// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// proto: USER_FUNC(aud_attack_init);
USER_FUNC(aud_attack_init) {
    BattleWork* wp = _battleWorkPointer;

    *(u32*)&wp->field_19064[0x1C] |= 1;
    *(s32*)&wp->field_19064[0x20] = event->printWindowId;
    return EVT_RETURN_DONE;
}
