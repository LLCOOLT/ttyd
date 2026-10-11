// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_mri_setup_no_tbl[];
// decl: extern s32 btlsetup_mri_tbl[];
// decl: extern s32 mri_00_init_evt[];
// decl: extern s32 mri_01_init_evt[];
// decl: extern s32 mri_02_init_evt[];
// decl: extern s32 mri_03_init_evt[];
// decl: extern s32 mri_04_init_evt[];
// decl: extern s32 mri_05_init_evt[];
// decl: extern s32 mri_06_init_evt[];
// decl: extern s32 mri_07_init_evt[];
// decl: extern s32 mri_08_init_evt[];
// decl: extern s32 mri_09_init_evt[];
// decl: extern s32 mri_10_init_evt[];
// decl: extern s32 mri_11_init_evt[];
// decl: extern s32 mri_12_init_evt[];
// decl: extern s32 mri_13_init_evt[];
// decl: extern s32 mri_14_init_evt[];
// decl: extern s32 mri_15_init_evt[];
// decl: extern s32 mri_16_init_evt[];
// decl: extern s32 mri_17_init_evt[];
// decl: extern s32 mri_18_init_evt[];
// decl: extern s32 mri_19_init_evt[];
// decl: extern s32 mri_20_init_evt[];
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
