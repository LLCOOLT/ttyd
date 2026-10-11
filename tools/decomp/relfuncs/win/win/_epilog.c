// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_win_setup_no_tbl[];
// decl: extern s32 btlsetup_win_tbl[];
// decl: extern s32 win_00_init_evt[];
// decl: extern s32 win_01_init_evt[];
// decl: extern s32 win_02_init_evt[];
// decl: extern s32 win_03_init_evt[];
// decl: extern s32 win_04_init_evt[];
// decl: extern s32 win_05_init_evt[];
// decl: extern s32 win_06_init_evt[];
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
