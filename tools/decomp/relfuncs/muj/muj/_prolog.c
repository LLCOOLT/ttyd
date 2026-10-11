// include: data/mapdata.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_muj_setup_no_tbl[];
// decl: extern s32 btlsetup_muj_tbl[];
// decl: extern s32 muj_00_init_evt[];
// decl: extern s32 muj_01_init_evt[];
// decl: extern s32 muj_02_init_evt[];
// decl: extern s32 muj_03_init_evt[];
// decl: extern s32 muj_04_init_evt[];
// decl: extern s32 muj_05_init_evt[];
// decl: extern s32 muj_10_init_evt[];
// decl: extern s32 muj_11_init_evt[];
// decl: extern s32 muj_12_init_evt[];
// decl: extern s32 muj_20_init_evt[];
// decl: extern s32 muj_21_init_evt[];
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("muj_00", muj_00_init_evt);
    relSetEvtAddr("muj_01", muj_01_init_evt);
    relSetEvtAddr("muj_02", muj_02_init_evt);
    relSetEvtAddr("muj_03", muj_03_init_evt);
    relSetEvtAddr("muj_04", muj_04_init_evt);
    relSetEvtAddr("muj_05", muj_05_init_evt);
    relSetEvtAddr("muj_10", muj_10_init_evt);
    relSetEvtAddr("muj_11", muj_11_init_evt);
    relSetEvtAddr("muj_12", muj_12_init_evt);
    relSetEvtAddr("muj_20", muj_20_init_evt);
    relSetEvtAddr("muj_21", muj_21_init_evt);
    relSetBtlAddr("muj", btlsetup_muj_tbl, btl_muj_setup_no_tbl);
}
