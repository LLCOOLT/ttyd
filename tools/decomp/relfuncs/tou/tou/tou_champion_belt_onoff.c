// include: manager/evtmgr_cmd.h
// decl: static s32 champion_belt_onoff;
// proto: USER_FUNC(tou_champion_belt_onoff);
USER_FUNC(tou_champion_belt_onoff) {
    champion_belt_onoff = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}
