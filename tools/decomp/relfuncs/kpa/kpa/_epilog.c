// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 kpa_00_init_evt[];
// decl: extern s32 kpa_01_init_evt[];
// decl: extern s32 kpa_02_init_evt[];
// decl: extern s32 kpa_03_init_evt[];
// decl: extern s32 kpa_04_init_evt[];
// decl: extern s32 kpa_05_init_evt[];
// decl: extern s32 kpa_06_init_evt[];
// decl: extern s32 kpa_07_init_evt[];
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
