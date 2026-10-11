// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 yuu_00_init_evt[];
// decl: extern s32 yuu_01_init_evt[];
// decl: extern s32 yuu_02_init_evt[];
// decl: extern s32 yuu_03_init_evt[];
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
