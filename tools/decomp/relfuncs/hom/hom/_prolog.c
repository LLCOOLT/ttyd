// include: data/mapdata.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 hom_00_init_evt[];
// decl: extern s32 hom_10_init_evt_13_data_3954[];
// decl: extern s32 hom_11_init_evt[];
// decl: extern s32 hom_12_init_evt[];
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("hom_00", hom_00_init_evt);
    relSetEvtAddr("hom_10", hom_10_init_evt_13_data_3954);
    relSetEvtAddr("hom_11", hom_11_init_evt);
    relSetEvtAddr("hom_12", hom_12_init_evt);
}
