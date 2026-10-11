// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_moo_setup_no_tbl[];
// decl: extern s32 btlsetup_moo_tbl[];
// decl: extern s32 moo_00_init_evt[];
// decl: extern s32 moo_01_init_evt[];
// decl: extern s32 moo_02_init_evt[];
// decl: extern s32 moo_03_init_evt[];
// decl: extern s32 moo_04_init_evt[];
// decl: extern s32 moo_05_init_evt[];
// decl: extern s32 moo_06_init_evt[];
// decl: extern s32 moo_07_init_evt[];
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
