// include: mario/mario.h
// include: system.h
// proto: USER_FUNC(muj_mario_pos_osreport_func);
USER_FUNC(muj_mario_pos_osreport_func) {
    marioGetPtr();
    keyGetButtonTrg(0);
    return EVT_RETURN_BLOCK;
}
