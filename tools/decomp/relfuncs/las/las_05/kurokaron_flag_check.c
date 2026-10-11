// include: manager/evtmgr_cmd.h
// decl: extern u8 kurokaron_move_flag;
// proto: USER_FUNC(kurokaron_flag_check);
USER_FUNC(kurokaron_flag_check) {
    s32* args = event->args;
    s32 mask = evtGetValue(event, args[0]);

    evtSetValue(event, args[1], kurokaron_move_flag & mask);
    return EVT_RETURN_DONE;
}
