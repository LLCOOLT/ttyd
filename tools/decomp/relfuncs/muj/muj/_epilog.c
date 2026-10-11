// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_muj_setup_no_tbl[];
// decl: extern s32 btlsetup_muj_tbl[];
// decl: extern s32 muj_00_init_evt[];
// decl: extern s32 muj_01_init_evt[];
// decl: extern s32 muj_02_init_evt[];
// decl: extern s32 muj_03_init_evt[];
// decl: extern s32 muj_04_init_evt[];
// decl: extern s32 muj_05_init_evt[];
// decl: extern s32 muj_10_init_evt[];
// decl: extern s32 muj_11_init_evt[];
// decl: extern s32 muj_12_init_evt[];
// decl: extern s32 muj_20_init_evt[];
// decl: extern s32 muj_21_init_evt[];
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
