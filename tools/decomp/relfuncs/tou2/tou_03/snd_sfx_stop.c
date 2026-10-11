// decl: void psndMapChange(void);
// proto: USER_FUNC(snd_sfx_stop);
USER_FUNC(snd_sfx_stop) {
    psndMapChange();
    return EVT_RETURN_DONE;
}
