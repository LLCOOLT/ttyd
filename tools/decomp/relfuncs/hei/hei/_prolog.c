// include: data/mapdata.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_hei_setup_no_tbl[];
// decl: extern s32 btlsetup_hei_tbl[];
// decl: extern s32 hei_00_init_evt[];
// decl: extern s32 hei_01_init_evt[];
// decl: extern s32 hei_02_init_evt[];
// decl: extern s32 hei_03_init_evt[];
// decl: extern s32 hei_04_init_evt[];
// decl: extern s32 hei_05_init_evt[];
// decl: extern s32 hei_06_init_evt[];
// decl: extern s32 hei_07_init_evt[];
// decl: extern s32 hei_08_init_evt[];
// decl: extern s32 hei_09_init_evt[];
// decl: extern s32 hei_10_init_evt[];
// decl: extern s32 hei_11_init_evt[];
// decl: extern s32 hei_12_init_evt[];
// decl: extern s32 hei_13_init_evt[];
// decl: extern s32 hei_bt00_init_evt[];
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("hei_00", hei_00_init_evt);
    relSetEvtAddr("hei_01", hei_01_init_evt);
    relSetEvtAddr("hei_02", hei_02_init_evt);
    relSetEvtAddr("hei_03", hei_03_init_evt);
    relSetEvtAddr("hei_04", hei_04_init_evt);
    relSetEvtAddr("hei_05", hei_05_init_evt);
    relSetEvtAddr("hei_06", hei_06_init_evt);
    relSetEvtAddr("hei_07", hei_07_init_evt);
    relSetEvtAddr("hei_08", hei_08_init_evt);
    relSetEvtAddr("hei_09", hei_09_init_evt);
    relSetEvtAddr("hei_10", hei_10_init_evt);
    relSetEvtAddr("hei_11", hei_11_init_evt);
    relSetEvtAddr("hei_12", hei_12_init_evt);
    relSetEvtAddr("hei_13", hei_13_init_evt);
    relSetEvtAddr("hei_bt00", hei_bt00_init_evt);
    relSetBtlAddr("hei", btlsetup_hei_tbl, btl_hei_setup_no_tbl);
}
