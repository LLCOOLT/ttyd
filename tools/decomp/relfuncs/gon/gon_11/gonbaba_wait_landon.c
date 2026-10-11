// include: driver/npcdrv.h
// proto: USER_FUNC(gonbaba_wait_landon);
USER_FUNC(gonbaba_wait_landon) {
    // ゴンババ
    return npcNameToPtr("\203S\203\223\203o\203o")->field_0x300 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
