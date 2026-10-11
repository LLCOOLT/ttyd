// include: driver/npcdrv.h
// proto: USER_FUNC(bonbaba_wait_landon);
USER_FUNC(bonbaba_wait_landon) {
    // ボンババ
    return npcNameToPtr("\x83\x7B\x83\x93\x83\x6F\x83\x6F")->field_0x300 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
