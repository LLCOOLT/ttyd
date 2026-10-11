// include: mario/mario.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(get_mario_y_pos);
USER_FUNC(get_mario_y_pos) {
    s32* args = event->args;

    evtSetFloat(event, args[0], marioGetPtr()->position.y);
    return EVT_RETURN_DONE;
}
