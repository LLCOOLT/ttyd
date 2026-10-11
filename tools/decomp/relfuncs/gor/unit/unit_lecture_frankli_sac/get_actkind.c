// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// proto: USER_FUNC(get_actkind);
USER_FUNC(get_actkind) {
    evtSetValue(event, event->args[0], *(s32*)&_battleWorkPointer->commandMenu.unk540[0]);
    return EVT_RETURN_DONE;
}
