// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_gor_setup_no_tbl[];
// decl: extern s32 btlsetup_gor_tbl[];
// decl: extern s32 gor_00_init_evt[];
// decl: extern s32 gor_01_init_evt[];
// decl: extern s32 gor_02_init_evt[];
// decl: extern s32 gor_03_init_evt[];
// decl: extern s32 gor_04_init_evt[];
// decl: extern s32 gor_10_init_evt[];
// decl: extern s32 gor_11_init_evt[];
// decl: extern s32 gor_12_init_evt[];
// include: mario/mariost.h
// include: string.h
// decl: void tegami_delete(void);
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    if (strcmp(gp->currentMapName, "gor_10") == 0) {
        tegami_delete();
    }
    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
