// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// decl: void marioSlitForceCancel(void);
// proto: USER_FUNC(evt_slit_cancel);
USER_FUNC(evt_slit_cancel) {
    MarioWork* mario = marioGetPtr();

    if (mario->trigFlags & 1) {
        mario->trigFlags &= ~1;
        marioSlitForceCancel();
    }
    return EVT_RETURN_DONE;
}
