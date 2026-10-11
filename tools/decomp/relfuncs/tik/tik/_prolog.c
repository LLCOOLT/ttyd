// include: data/mapdata.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_tik_setup_no_tbl[];
// decl: extern s32 btlsetup_tik_tbl[];
// decl: extern s32 tik_00_init_evt[];
// decl: extern s32 tik_01_init_evt[];
// decl: extern s32 tik_02_init_evt[];
// decl: extern s32 tik_03_init_evt[];
// decl: extern s32 tik_04_init_evt[];
// decl: extern s32 tik_05_init_evt[];
// decl: extern s32 tik_06_init_evt[];
// decl: extern s32 tik_07_init_evt[];
// decl: extern s32 tik_08_init_evt[];
// decl: extern s32 tik_09_init_evt[];
// decl: extern s32 tik_10_init_evt[];
// decl: extern s32 tik_11_init_evt[];
// decl: extern s32 tik_12_init_evt[];
// decl: extern s32 tik_13_init_evt[];
// decl: extern s32 tik_14_init_evt[];
// decl: extern s32 tik_15_init_evt[];
// decl: extern s32 tik_16_init_evt[];
// decl: extern s32 tik_17_init_evt[];
// decl: extern s32 tik_18_init_evt[];
// decl: extern s32 tik_19_init_evt[];
// decl: extern s32 tik_20_init_evt[];
// decl: extern s32 tik_21_init_evt[];
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("tik_00", tik_00_init_evt);
    relSetEvtAddr("tik_01", tik_01_init_evt);
    relSetEvtAddr("tik_02", tik_02_init_evt);
    relSetEvtAddr("tik_03", tik_03_init_evt);
    relSetEvtAddr("tik_04", tik_04_init_evt);
    relSetEvtAddr("tik_05", tik_05_init_evt);
    relSetEvtAddr("tik_06", tik_06_init_evt);
    relSetEvtAddr("tik_07", tik_07_init_evt);
    relSetEvtAddr("tik_08", tik_08_init_evt);
    relSetEvtAddr("tik_09", tik_09_init_evt);
    relSetEvtAddr("tik_10", tik_10_init_evt);
    relSetEvtAddr("tik_11", tik_11_init_evt);
    relSetEvtAddr("tik_12", tik_12_init_evt);
    relSetEvtAddr("tik_13", tik_13_init_evt);
    relSetEvtAddr("tik_14", tik_14_init_evt);
    relSetEvtAddr("tik_15", tik_15_init_evt);
    relSetEvtAddr("tik_16", tik_16_init_evt);
    relSetEvtAddr("tik_17", tik_17_init_evt);
    relSetEvtAddr("tik_18", tik_18_init_evt);
    relSetEvtAddr("tik_19", tik_19_init_evt);
    relSetEvtAddr("tik_20", tik_20_init_evt);
    relSetEvtAddr("tik_21", tik_21_init_evt);
    relSetBtlAddr("tik", btlsetup_tik_tbl, btl_tik_setup_no_tbl);
}
