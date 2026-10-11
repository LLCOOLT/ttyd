// include: mario/mario.h
// proto: USER_FUNC(unk_tou_00006ec8);
USER_FUNC(unk_tou_00006ec8) {
    MarioWork* mario = marioGetPtr();

    if (isFirstCall) {
        event->userdata[0] = 0;
    }
    if (!marioKeyOffChk() && !marioCtrlOffChk() &&
        (mario->currMotionId == 0 || mario->currMotionId == 1 || mario->currMotionId == 2)) {
        event->userdata[0]++;
        if (event->userdata[0] > 240) {
            event->userdata[0] = 240;
            return EVT_RETURN_DONE;
        }
    }
    return EVT_RETURN_BLOCK;
}
