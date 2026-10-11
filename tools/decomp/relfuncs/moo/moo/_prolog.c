// include: data/mapdata.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_moo_setup_no_tbl[];
// decl: extern s32 btlsetup_moo_tbl[];
// decl: extern s32 moo_00_init_evt[];
// decl: extern s32 moo_01_init_evt[];
// decl: extern s32 moo_02_init_evt[];
// decl: extern s32 moo_03_init_evt[];
// decl: extern s32 moo_04_init_evt[];
// decl: extern s32 moo_05_init_evt[];
// decl: extern s32 moo_06_init_evt[];
// decl: extern s32 moo_07_init_evt[];
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("moo_00", moo_00_init_evt);
    relSetEvtAddr("moo_01", moo_01_init_evt);
    relSetEvtAddr("moo_02", moo_02_init_evt);
    relSetEvtAddr("moo_03", moo_03_init_evt);
    relSetEvtAddr("moo_04", moo_04_init_evt);
    relSetEvtAddr("moo_05", moo_05_init_evt);
    relSetEvtAddr("moo_06", moo_06_init_evt);
    relSetEvtAddr("moo_07", moo_07_init_evt);
    relSetBtlAddr("moo", btlsetup_moo_tbl, btl_moo_setup_no_tbl);
}
