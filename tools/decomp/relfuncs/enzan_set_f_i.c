// include: manager/evtmgr_cmd.h
// proto: static USER_FUNC(enzan_set_f_i);
static USER_FUNC(enzan_set_f_i) {
    s32* args = event->args;
    s32 var = args[0];

    evtSetFloat(event, var, evtGetValue(event, args[1]));
    return EVT_RETURN_DONE;
}
