// include: data/mapdata.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_dou_setup_no_tbl[];
// decl: extern s32 btlsetup_dou_tbl[];
// decl: extern s32 dou_00_init_evt[];
// decl: extern s32 dou_01_init_evt[];
// decl: extern s32 dou_02_init_evt[];
// decl: extern s32 dou_03_init_evt[];
// decl: extern s32 dou_04_init_evt[];
// decl: extern s32 dou_05_init_evt[];
// decl: extern s32 dou_06_init_evt[];
// decl: extern s32 dou_07_init_evt[];
// decl: extern s32 dou_08_init_evt[];
// decl: extern s32 dou_09_init_evt[];
// decl: extern s32 dou_10_init_evt[];
// decl: extern s32 dou_11_init_evt[];
// decl: extern s32 dou_12_init_evt[];
// decl: extern s32 dou_13_init_evt[];
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("dou_00", dou_00_init_evt);
    relSetEvtAddr("dou_01", dou_01_init_evt);
    relSetEvtAddr("dou_02", dou_02_init_evt);
    relSetEvtAddr("dou_03", dou_03_init_evt);
    relSetEvtAddr("dou_04", dou_04_init_evt);
    relSetEvtAddr("dou_05", dou_05_init_evt);
    relSetEvtAddr("dou_06", dou_06_init_evt);
    relSetEvtAddr("dou_07", dou_07_init_evt);
    relSetEvtAddr("dou_08", dou_08_init_evt);
    relSetEvtAddr("dou_09", dou_09_init_evt);
    relSetEvtAddr("dou_10", dou_10_init_evt);
    relSetEvtAddr("dou_11", dou_11_init_evt);
    relSetEvtAddr("dou_12", dou_12_init_evt);
    relSetEvtAddr("dou_13", dou_13_init_evt);
    relSetBtlAddr("dou", btlsetup_dou_tbl, btl_dou_setup_no_tbl);
}
