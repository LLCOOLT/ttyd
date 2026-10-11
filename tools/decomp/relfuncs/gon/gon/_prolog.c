// include: data/mapdata.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_gon_setup_no_tbl[];
// decl: extern s32 btlsetup_gon_tbl[];
// decl: extern s32 gon_00_init_evt[];
// decl: extern s32 gon_01_init_evt[];
// decl: extern s32 gon_02_init_evt[];
// decl: extern s32 gon_03_init_evt[];
// decl: extern s32 gon_04_init_evt[];
// decl: extern s32 gon_05_init_evt[];
// decl: extern s32 gon_06_init_evt[];
// decl: extern s32 gon_07_init_evt[];
// decl: extern s32 gon_08_init_evt[];
// decl: extern s32 gon_09_init_evt[];
// decl: extern s32 gon_10_init_evt[];
// decl: extern s32 gon_11_init_evt[];
// decl: extern s32 gon_12_init_evt[];
// decl: extern s32 gon_13_init_evt[];
// decl: extern s32 gon_bt00_init_evt[];
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("gon_00", gon_00_init_evt);
    relSetEvtAddr("gon_01", gon_01_init_evt);
    relSetEvtAddr("gon_02", gon_02_init_evt);
    relSetEvtAddr("gon_03", gon_03_init_evt);
    relSetEvtAddr("gon_04", gon_04_init_evt);
    relSetEvtAddr("gon_05", gon_05_init_evt);
    relSetEvtAddr("gon_06", gon_06_init_evt);
    relSetEvtAddr("gon_07", gon_07_init_evt);
    relSetEvtAddr("gon_08", gon_08_init_evt);
    relSetEvtAddr("gon_09", gon_09_init_evt);
    relSetEvtAddr("gon_10", gon_10_init_evt);
    relSetEvtAddr("gon_11", gon_11_init_evt);
    relSetEvtAddr("gon_12", gon_12_init_evt);
    relSetEvtAddr("gon_13", gon_13_init_evt);
    relSetEvtAddr("gon_bt00", gon_bt00_init_evt);
    relSetBtlAddr("gon", btlsetup_gon_tbl, btl_gon_setup_no_tbl);
}
