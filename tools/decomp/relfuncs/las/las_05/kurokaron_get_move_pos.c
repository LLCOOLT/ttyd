// include: manager/evtmgr_cmd.h
// decl: extern u8 kurokaron_move_index;
// decl: extern f32 kurokaron_move_list[6][2];
// proto: USER_FUNC(kurokaron_get_move_pos);
USER_FUNC(kurokaron_get_move_pos) {
    s32* args = event->args;

    evtSetFloat(event, args[0], kurokaron_move_list[kurokaron_move_index][0]);
    evtSetFloat(event, args[1], kurokaron_move_list[kurokaron_move_index][1]);
    return EVT_RETURN_DONE;
}
