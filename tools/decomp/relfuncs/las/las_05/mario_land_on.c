// include: mario/mario.h
// proto: USER_FUNC(mario_land_on);
USER_FUNC(mario_land_on) {
    MarioWork* mario = marioGetPtr();

    if (mario->position.y < 0.0f) {
        mario->position.y = 0.0f;
    }
    return EVT_RETURN_DONE;
}
