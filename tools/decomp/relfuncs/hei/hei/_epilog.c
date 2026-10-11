// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_hei_setup_no_tbl[];
// decl: extern s32 btlsetup_hei_tbl[];
// decl: extern s32 hei_00_init_evt[];
// decl: extern s32 hei_01_init_evt[];
// decl: extern s32 hei_02_init_evt[];
// decl: extern s32 hei_03_init_evt[];
// decl: extern s32 hei_04_init_evt[];
// decl: extern s32 hei_05_init_evt[];
// decl: extern s32 hei_06_init_evt[];
// decl: extern s32 hei_07_init_evt[];
// decl: extern s32 hei_08_init_evt[];
// decl: extern s32 hei_09_init_evt[];
// decl: extern s32 hei_10_init_evt[];
// decl: extern s32 hei_11_init_evt[];
// decl: extern s32 hei_12_init_evt[];
// decl: extern s32 hei_13_init_evt[];
// decl: extern s32 hei_bt00_init_evt[];
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
