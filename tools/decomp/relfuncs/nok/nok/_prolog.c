// include: data/mapdata.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_nok_setup_no_tbl[];
// decl: extern s32 btlsetup_nok_tbl[];
// decl: extern s32 nok_00_init_evt[];
// decl: extern s32 nok_01_init_evt[];
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("nok_00", nok_00_init_evt);
    relSetEvtAddr("nok_01", nok_01_init_evt);
    relSetBtlAddr("nok", btlsetup_nok_tbl, btl_nok_setup_no_tbl);
}
