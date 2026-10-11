// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_gon_setup_no_tbl[];
// decl: extern s32 btlsetup_gon_tbl[];
// decl: extern s32 gon_00_init_evt[];
// decl: extern s32 gon_01_init_evt[];
// decl: extern s32 gon_02_init_evt[];
// decl: extern s32 gon_03_init_evt[];
// decl: extern s32 gon_04_init_evt[];
// decl: extern s32 gon_05_init_evt[];
// decl: extern s32 gon_06_init_evt[];
// decl: extern s32 gon_07_init_evt[];
// decl: extern s32 gon_08_init_evt[];
// decl: extern s32 gon_09_init_evt[];
// decl: extern s32 gon_10_init_evt[];
// decl: extern s32 gon_11_init_evt[];
// decl: extern s32 gon_12_init_evt[];
// decl: extern s32 gon_13_init_evt[];
// decl: extern s32 gon_bt00_init_evt[];
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
