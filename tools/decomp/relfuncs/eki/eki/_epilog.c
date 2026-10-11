// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_eki_setup_no_tbl[];
// decl: extern s32 btlsetup_eki_tbl[];
// decl: extern s32 eki_00_init_evt[];
// decl: extern s32 eki_01_init_evt[];
// decl: extern s32 eki_02_init_evt[];
// decl: extern s32 eki_03_init_evt[];
// decl: extern s32 eki_04_init_evt[];
// decl: extern s32 eki_05_init_evt[];
// decl: extern s32 eki_06_init_evt[];
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
