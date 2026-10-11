// decl: static s32 dataadr[32];
// decl: s32 stackt[4];
// decl: s32 stackp;
// proto: USER_FUNC(yuu_atai_init);
USER_FUNC(yuu_atai_init) {
    stackp = 0;
    return EVT_RETURN_DONE;
}
