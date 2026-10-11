// decl: extern s32 bom_00_init_evt[];
// decl: extern s32 bom_01_init_evt[];
// decl: extern s32 bom_02_init_evt[];
// decl: extern s32 bom_03_init_evt[];
// decl: extern s32 bom_04_init_evt[];
// decl: extern s32 btl_bom_setup_no_tbl[];
// decl: extern s32 btlsetup_bom_tbl[];
// decl: extern s32 evt_bress[];
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("bom_00", bom_00_init_evt);
    relSetEvtAddr("bom_01", bom_01_init_evt);
    relSetEvtAddr("bom_02", bom_02_init_evt);
    relSetEvtAddr("bom_03", bom_03_init_evt);
    relSetEvtAddr("bom_04", bom_04_init_evt);
    relSetBtlAddr("bom", btlsetup_bom_tbl, btl_bom_setup_no_tbl);
    evtEntryType(evt_bress, 0, 0, 0);
}
