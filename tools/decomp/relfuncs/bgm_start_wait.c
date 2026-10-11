// proto: USER_FUNC(bgm_start_wait);
BOOL psndBGMStartCheck(s32 id);

USER_FUNC(bgm_start_wait) {
    return psndBGMStartCheck(1) ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
