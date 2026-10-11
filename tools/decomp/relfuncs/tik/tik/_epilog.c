// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_tik_setup_no_tbl[];
// decl: extern s32 btlsetup_tik_tbl[];
// decl: extern s32 tik_00_init_evt[];
// decl: extern s32 tik_01_init_evt[];
// decl: extern s32 tik_02_init_evt[];
// decl: extern s32 tik_03_init_evt[];
// decl: extern s32 tik_04_init_evt[];
// decl: extern s32 tik_05_init_evt[];
// decl: extern s32 tik_06_init_evt[];
// decl: extern s32 tik_07_init_evt[];
// decl: extern s32 tik_08_init_evt[];
// decl: extern s32 tik_09_init_evt[];
// decl: extern s32 tik_10_init_evt[];
// decl: extern s32 tik_11_init_evt[];
// decl: extern s32 tik_12_init_evt[];
// decl: extern s32 tik_13_init_evt[];
// decl: extern s32 tik_14_init_evt[];
// decl: extern s32 tik_15_init_evt[];
// decl: extern s32 tik_16_init_evt[];
// decl: extern s32 tik_17_init_evt[];
// decl: extern s32 tik_18_init_evt[];
// decl: extern s32 tik_19_init_evt[];
// decl: extern s32 tik_20_init_evt[];
// decl: extern s32 tik_21_init_evt[];
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
