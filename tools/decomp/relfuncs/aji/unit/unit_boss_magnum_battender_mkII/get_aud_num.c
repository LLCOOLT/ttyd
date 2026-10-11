// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_audience.h
// proto: USER_FUNC(get_aud_num);
USER_FUNC(get_aud_num) {
    s32* args = event->args;

    evtSetValue(event, args[0], BattleAudience_GetAudienceNum());
    return EVT_RETURN_DONE;
}
