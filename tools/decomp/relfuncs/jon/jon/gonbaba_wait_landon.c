// include: driver/npcdrv.h
// proto: static USER_FUNC(gonbaba_wait_landon);
static USER_FUNC(gonbaba_wait_landon) {
    // 敵
    return npcNameToPtr("\223G")->field_0x300 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
