// include: mario/mario.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(set_pos);
USER_FUNC(set_pos) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    MarioWork* mario = marioGetPtr();

    mario->position = (Vec){x, y, z};
    return EVT_RETURN_DONE;
}
