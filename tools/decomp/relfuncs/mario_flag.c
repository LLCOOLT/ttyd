// include: mario/mario.h
// include: driver/npcdrv.h
// proto: USER_FUNC(mario_flag);
BOOL winGhostDiaryChk(void);

USER_FUNC(mario_flag) {
    s32* args = event->args;
    MarioWork* mario = marioGetPtr();
    if (fbatGetPointer()->mode == 2 || winGhostDiaryChk()) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
