// include: manager/evtmgr_cmd.h
// proto: static USER_FUNC(set_fook_evt);
static USER_FUNC(set_fook_evt) {
    s32* args = event->args;
    s32* wp = (s32*)evtGetValue(event, args[0]);

    wp[1] = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}
