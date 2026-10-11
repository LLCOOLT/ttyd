// include: mario/mario.h
// include: system.h
// proto: USER_FUNC(dou_mario_pos_osreport_func);
USER_FUNC(dou_mario_pos_osreport_func) {
    MarioWork* mario = marioGetPtr();

    keyGetButtonTrg(0);
    return EVT_RETURN_BLOCK;
}
