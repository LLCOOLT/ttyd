// include: data/mapdata.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_mri_setup_no_tbl[];
// decl: extern s32 btlsetup_mri_tbl[];
// decl: extern s32 mri_00_init_evt[];
// decl: extern s32 mri_01_init_evt[];
// decl: extern s32 mri_02_init_evt[];
// decl: extern s32 mri_03_init_evt[];
// decl: extern s32 mri_04_init_evt[];
// decl: extern s32 mri_05_init_evt[];
// decl: extern s32 mri_06_init_evt[];
// decl: extern s32 mri_07_init_evt[];
// decl: extern s32 mri_08_init_evt[];
// decl: extern s32 mri_09_init_evt[];
// decl: extern s32 mri_10_init_evt[];
// decl: extern s32 mri_11_init_evt[];
// decl: extern s32 mri_12_init_evt[];
// decl: extern s32 mri_13_init_evt[];
// decl: extern s32 mri_14_init_evt[];
// decl: extern s32 mri_15_init_evt[];
// decl: extern s32 mri_16_init_evt[];
// decl: extern s32 mri_17_init_evt[];
// decl: extern s32 mri_18_init_evt[];
// decl: extern s32 mri_19_init_evt[];
// decl: extern s32 mri_20_init_evt[];
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("mri_00", mri_00_init_evt);
    relSetEvtAddr("mri_01", mri_01_init_evt);
    relSetEvtAddr("mri_02", mri_02_init_evt);
    relSetEvtAddr("mri_03", mri_03_init_evt);
    relSetEvtAddr("mri_04", mri_04_init_evt);
    relSetEvtAddr("mri_05", mri_05_init_evt);
    relSetEvtAddr("mri_06", mri_06_init_evt);
    relSetEvtAddr("mri_07", mri_07_init_evt);
    relSetEvtAddr("mri_08", mri_08_init_evt);
    relSetEvtAddr("mri_09", mri_09_init_evt);
    relSetEvtAddr("mri_10", mri_10_init_evt);
    relSetEvtAddr("mri_11", mri_11_init_evt);
    relSetEvtAddr("mri_12", mri_12_init_evt);
    relSetEvtAddr("mri_13", mri_13_init_evt);
    relSetEvtAddr("mri_14", mri_14_init_evt);
    relSetEvtAddr("mri_15", mri_15_init_evt);
    relSetEvtAddr("mri_16", mri_16_init_evt);
    relSetEvtAddr("mri_17", mri_17_init_evt);
    relSetEvtAddr("mri_18", mri_18_init_evt);
    relSetEvtAddr("mri_19", mri_19_init_evt);
    relSetEvtAddr("mri_20", mri_20_init_evt);
    relSetBtlAddr("mri", btlsetup_mri_tbl, btl_mri_setup_no_tbl);
}
