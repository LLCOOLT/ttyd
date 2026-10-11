// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 hom_00_init_evt[];
// decl: extern s32 hom_10_init_evt_13_data_3954[];
// decl: extern s32 hom_11_init_evt[];
// decl: extern s32 hom_12_init_evt[];
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
