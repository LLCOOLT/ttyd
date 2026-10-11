// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(setPuniWeight);
USER_FUNC(setPuniWeight) {
    mri02switch.weight = evtGetFloat(event, event->args[0]);
    return EVT_RETURN_DONE;
}
