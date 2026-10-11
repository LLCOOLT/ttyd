// include: mario/mario.h
// proto: USER_FUNC(get_mario_dispReqDir);
USER_FUNC(get_mario_dispReqDir) {
    s32* args = event->args;
    MarioWork* mario = marioGetPtr();

    evtSetValue(event, args[0], mario->unk1AC);
    return EVT_RETURN_DONE;
}
