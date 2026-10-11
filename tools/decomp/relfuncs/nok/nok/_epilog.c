// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_nok_setup_no_tbl[];
// decl: extern s32 btlsetup_nok_tbl[];
// decl: extern s32 nok_00_init_evt[];
// decl: extern s32 nok_01_init_evt[];
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
