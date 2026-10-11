// include: mario/mario.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(set_mario_y_pos);
USER_FUNC(set_mario_y_pos) {
    s32* args = event->args;
    f32 y = evtGetFloat(event, args[0]);

    marioGetPtr()->position.y = y;
    return EVT_RETURN_DONE;
}
