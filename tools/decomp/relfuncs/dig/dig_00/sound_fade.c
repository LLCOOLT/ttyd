// include: seq/seq_demo.h
// proto: USER_FUNC(sound_fade);
USER_FUNC(sound_fade) {
    THPSimpleSetVolume(0, 2000);
    return EVT_RETURN_DONE;
}
