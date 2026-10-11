// include: pmario_sound.h
// proto: USER_FUNC(bgm_wait_stop);
USER_FUNC(bgm_wait_stop) {
    psndSetFlag(0x1000);
    return EVT_RETURN_DONE;
}
