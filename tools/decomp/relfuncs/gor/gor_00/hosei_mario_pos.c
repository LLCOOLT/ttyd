// include: mario/mario.h
// proto: USER_FUNC(hosei_mario_pos);
USER_FUNC(hosei_mario_pos) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    MarioWork* mario = marioGetPtr();

    mario->position.x += x;
    mario->position.y += y;
    mario->position.z += z;
    return EVT_RETURN_DONE;
}
