// include: data/mapdata.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 yuu_00_init_evt[];
// decl: extern s32 yuu_01_init_evt[];
// decl: extern s32 yuu_02_init_evt[];
// decl: extern s32 yuu_03_init_evt[];
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("yuu_00", yuu_00_init_evt);
    relSetEvtAddr("yuu_01", yuu_01_init_evt);
    relSetEvtAddr("yuu_02", yuu_02_init_evt);
    relSetEvtAddr("yuu_03", yuu_03_init_evt);
}
