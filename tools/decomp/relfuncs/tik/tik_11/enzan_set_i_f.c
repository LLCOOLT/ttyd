// include: manager/evtmgr_cmd.h
// proto: static USER_FUNC(enzan_set_i_f);
static USER_FUNC(enzan_set_i_f) {
    s32* args = event->args;
    s32 var = args[0];

    evtSetValue(event, var, evtGetFloat(event, args[1]));
    return EVT_RETURN_DONE;
}
