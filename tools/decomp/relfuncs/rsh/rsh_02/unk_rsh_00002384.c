// decl: s32 unk_8009fcbc(void);
// decl: s32 U_marioSlitContinueChk(void);
// proto: USER_FUNC(unk_rsh_00002384);
USER_FUNC(unk_rsh_00002384) {
    if (!unk_8009fcbc() && !U_marioSlitContinueChk()) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
