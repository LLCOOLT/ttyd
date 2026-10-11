// include: mario/mario.h
// proto: USER_FUNC(mario_reset);
USER_FUNC(mario_reset) {
    MarioWork* mario = marioGetPtr();

    mario->scale.x = mario->scale.y = mario->scale.z = 1.0f;
    mario->field_0xB4 = 0.0f;
    mario->field_0xC4 = 0.0f;
    return EVT_RETURN_DONE;
}
