// include: manager/evtmgr_cmd.h
// include: driver/swdrv.h
// proto: USER_FUNC(cooking_flag);
USER_FUNC(cooking_flag) {
    swSet(evtGetValue(event, event->args[0]) - 114);
    return EVT_RETURN_DONE;
}
