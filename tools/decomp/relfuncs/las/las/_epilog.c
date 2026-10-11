// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_las_setup_no_tbl[];
// decl: extern s32 btlsetup_las_tbl[];
// decl: extern s32 las_00_init_evt[];
// decl: extern s32 las_01_init_evt[];
// decl: extern s32 las_02_init_evt[];
// decl: extern s32 las_03_init_evt[];
// decl: extern s32 las_04_init_evt[];
// decl: extern s32 las_05_init_evt[];
// decl: extern s32 las_06_init_evt[];
// decl: extern s32 las_07_init_evt[];
// decl: extern s32 las_08_init_evt[];
// decl: extern s32 las_09_init_evt[];
// decl: extern s32 las_10_init_evt[];
// decl: extern s32 las_11_init_evt[];
// decl: extern s32 las_12_init_evt[];
// decl: extern s32 las_13_init_evt[];
// decl: extern s32 las_14_init_evt[];
// decl: extern s32 las_15_init_evt[];
// decl: extern s32 las_16_init_evt[];
// decl: extern s32 las_17_init_evt[];
// decl: extern s32 las_18_init_evt[];
// decl: extern s32 las_19_init_evt[];
// decl: extern s32 las_20_init_evt[];
// decl: extern s32 las_21_init_evt[];
// decl: extern s32 las_22_init_evt[];
// decl: extern s32 las_23_init_evt[];
// decl: extern s32 las_24_init_evt[];
// decl: extern s32 las_25_init_evt[];
// decl: extern s32 las_26_init_evt[];
// decl: extern s32 las_27_init_evt[];
// decl: extern s32 las_28_init_evt[];
// decl: extern s32 las_29_init_evt[];
// decl: extern s32 las_30_init_evt[];
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
