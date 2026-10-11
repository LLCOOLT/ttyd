// include: data/mapdata.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_win_setup_no_tbl[];
// decl: extern s32 btlsetup_win_tbl[];
// decl: extern s32 win_00_init_evt[];
// decl: extern s32 win_01_init_evt[];
// decl: extern s32 win_02_init_evt[];
// decl: extern s32 win_03_init_evt[];
// decl: extern s32 win_04_init_evt[];
// decl: extern s32 win_05_init_evt[];
// decl: extern s32 win_06_init_evt[];
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("win_00", win_00_init_evt);
    relSetEvtAddr("win_01", win_01_init_evt);
    relSetEvtAddr("win_02", win_02_init_evt);
    relSetEvtAddr("win_03", win_03_init_evt);
    relSetEvtAddr("win_04", win_04_init_evt);
    relSetEvtAddr("win_05", win_05_init_evt);
    relSetEvtAddr("win_06", win_06_init_evt);
    relSetBtlAddr("win", btlsetup_win_tbl, btl_win_setup_no_tbl);
}
