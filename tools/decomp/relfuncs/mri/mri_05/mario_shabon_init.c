// include: mario/mario.h
// include: mario/mario_motion.h
// proto: USER_FUNC(mario_shabon_init);
USER_FUNC(mario_shabon_init) {
    MarioWork* mario = marioGetPtr();

    mario->hitobjStandOn = NULL;
    mario->airTimer = 1;
    marioChgMot(8);
    return EVT_RETURN_DONE;
}
