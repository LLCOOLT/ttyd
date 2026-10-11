// include: data/mapdata.h
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
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("gor_00", gor_00_init_evt);
    relSetEvtAddr("gor_01", gor_01_init_evt);
    relSetEvtAddr("gor_02", gor_02_init_evt);
    relSetEvtAddr("gor_03", gor_03_init_evt);
    relSetEvtAddr("gor_04", gor_04_init_evt);
    relSetEvtAddr("gor_10", gor_10_init_evt);
    relSetEvtAddr("gor_11", gor_11_init_evt);
    relSetEvtAddr("gor_12", gor_12_init_evt);
    relSetBtlAddr("gor", btlsetup_gor_tbl, btl_gor_setup_no_tbl);
}
