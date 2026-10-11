// include: data/mapdata.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_eki_setup_no_tbl[];
// decl: extern s32 btlsetup_eki_tbl[];
// decl: extern s32 eki_00_init_evt[];
// decl: extern s32 eki_01_init_evt[];
// decl: extern s32 eki_02_init_evt[];
// decl: extern s32 eki_03_init_evt[];
// decl: extern s32 eki_04_init_evt[];
// decl: extern s32 eki_05_init_evt[];
// decl: extern s32 eki_06_init_evt[];
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("eki_00", eki_00_init_evt);
    relSetEvtAddr("eki_01", eki_01_init_evt);
    relSetEvtAddr("eki_02", eki_02_init_evt);
    relSetEvtAddr("eki_03", eki_03_init_evt);
    relSetEvtAddr("eki_04", eki_04_init_evt);
    relSetEvtAddr("eki_05", eki_05_init_evt);
    relSetEvtAddr("eki_06", eki_06_init_evt);
    relSetBtlAddr("eki", btlsetup_eki_tbl, btl_eki_setup_no_tbl);
}
