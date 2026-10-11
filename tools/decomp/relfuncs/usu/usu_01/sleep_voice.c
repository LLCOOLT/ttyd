// include: mario/mario.h
// include: driver/animdrv.h
// include: pmario_sound.h
// include: string.h
// proto: USER_FUNC(sleep_voice);
USER_FUNC(sleep_voice) {
    MarioWork* mario = marioGetPtr();
    s32 loops;

    if (isFirstCall) {
        event->userdata[0] = -1;
    }
    if (strcmp(mario->animName, "M_N_5A") == 0) {
        loops = animPoseGetLoopTimes(mario->paperAnimGroupId[marioAnimeId()]);
        if (loops != event->userdata[0]) {
            event->userdata[0] = loops;
            evtSetValue(event, GW(10), psndSFXOn_3D("SFX_VOICE_MARIO_SLEEP1", &mario->position));
        }
    }
    return EVT_RETURN_BLOCK;
}
