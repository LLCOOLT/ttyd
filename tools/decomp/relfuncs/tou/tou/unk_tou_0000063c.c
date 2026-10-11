// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// proto: USER_FUNC(unk_tou_0000063c);
USER_FUNC(unk_tou_0000063c) {
    MarioWork* mario = marioGetPtr();

    if (isFirstCall) {
        event->userdata[0] = 0;
    }
    if (!marioKeyOffChk() && !marioCtrlOffChk() && (mario->currMotionId == 0 || mario->currMotionId == 1 || mario->currMotionId == 2)) {
        event->userdata[0]++;
        if (event->userdata[0] > 240) {
            event->userdata[0] = 240;
            return EVT_RETURN_DONE;
        }
    }
    return EVT_RETURN_BLOCK;
}
