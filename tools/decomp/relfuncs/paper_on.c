// include: mario/mario.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(paper_on);
USER_FUNC(paper_on) {
    f32 value = evtGetFloat(event, event->args[0]);
    MarioWork* mario = marioGetPtr();

    if (isFirstCall) {
        marioPaperOn("p_slit");
        marioChgPose("M_S_1");
        marioChgPaper("PM_S_3A");
    }
    mario->unk1A8 = mario->unk1AC = value;
    return EVT_RETURN_BLOCK;
}
