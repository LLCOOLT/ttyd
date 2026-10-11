// include: mario/mario.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(get_pos);
USER_FUNC(get_pos) {
    s32* args = event->args;
    MarioWork* mario = marioGetPtr();

    evtSetFloat(event, args[0], mario->position.x);
    evtSetFloat(event, args[1], mario->position.y);
    evtSetFloat(event, args[2], mario->position.z);
    return EVT_RETURN_DONE;
}
