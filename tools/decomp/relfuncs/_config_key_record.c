// include: battle/battle.h
// include: battle/battle_pad.h
// proto: USER_FUNC(_config_key_record);
USER_FUNC(_config_key_record) {
    s32 record = event->args[0];
    BattleWork* wp = _battleWorkPointer;
    BattleWorkPad* pad = &wp->actionCommands.pad;

    wp->actionCommands.mDefenseResult = 4;
    BtlPad_WorkInit(pad);
    pad->mButtonsPressedHistory[0] = record;
    return EVT_RETURN_DONE;
}
