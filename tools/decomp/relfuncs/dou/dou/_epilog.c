// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_dou_setup_no_tbl[];
// decl: extern s32 btlsetup_dou_tbl[];
// decl: extern s32 dou_00_init_evt[];
// decl: extern s32 dou_01_init_evt[];
// decl: extern s32 dou_02_init_evt[];
// decl: extern s32 dou_03_init_evt[];
// decl: extern s32 dou_04_init_evt[];
// decl: extern s32 dou_05_init_evt[];
// decl: extern s32 dou_06_init_evt[];
// decl: extern s32 dou_07_init_evt[];
// decl: extern s32 dou_08_init_evt[];
// decl: extern s32 dou_09_init_evt[];
// decl: extern s32 dou_10_init_evt[];
// decl: extern s32 dou_11_init_evt[];
// decl: extern s32 dou_12_init_evt[];
// decl: extern s32 dou_13_init_evt[];
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
