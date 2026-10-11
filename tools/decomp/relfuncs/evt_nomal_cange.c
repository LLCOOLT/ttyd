// include: mario/mario.h
// decl: void unk_8009f9c8(void);
// decl: void motSlitCancel3(void);
// decl: BOOL marioRollKeyDisable(void);
// proto: static USER_FUNC(evt_nomal_cange);
static USER_FUNC(evt_nomal_cange) {
    MarioWork* mario = marioGetPtr();

    if (isFirstCall) {
        unk_8009f9c8();
        if (mario->flags & 0x100000) {
            motSlitCancel3();
        }
    }
    if (!marioRollKeyDisable()) {
        return EVT_RETURN_BLOCK;
    }
    return (mario->dispFlags & 0x1000000) ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}
