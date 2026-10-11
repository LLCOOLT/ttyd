// include: data/mapdata.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_jon_setup_no_tbl[];
// decl: extern s32 btlsetup_jon_tbl[];
// decl: extern s32 jon_init_evt[];
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("jon_00", jon_init_evt);
    relSetEvtAddr("jon_01", jon_init_evt);
    relSetEvtAddr("jon_02", jon_init_evt);
    relSetEvtAddr("jon_03", jon_init_evt);
    relSetEvtAddr("jon_04", jon_init_evt);
    relSetEvtAddr("jon_05", jon_init_evt);
    relSetEvtAddr("jon_06", jon_init_evt);
    relSetBtlAddr("jon", btlsetup_jon_tbl, btl_jon_setup_no_tbl);
}
