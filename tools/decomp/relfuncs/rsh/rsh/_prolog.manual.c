// include: driver/swdrv.h
// decl: extern s32 btl_rsh_setup_no_tbl[];
// decl: extern s32 btlsetup_rsh_tbl[];
// decl: extern s32 rsh_00_a_init_evt[];
// decl: extern s32 rsh_00_a_init_evt_nidome[];
// decl: extern s32 rsh_00_b_init_evt[];
// decl: extern s32 rsh_00_b_init_evt_nidome[];
// decl: extern s32 rsh_00_c_init_evt[];
// decl: extern s32 rsh_00_c_init_evt_nidome[];
// decl: extern s32 rsh_01_a_init_evt[];
// decl: extern s32 rsh_01_a_init_evt_nidome[];
// decl: extern s32 rsh_01_b_init_evt[];
// decl: extern s32 rsh_01_b_init_evt_nidome[];
// decl: extern s32 rsh_01_c_init_evt[];
// decl: extern s32 rsh_01_c_init_evt_nidome[];
// decl: extern s32 rsh_02_a_init_evt[];
// decl: extern s32 rsh_02_a_init_evt_nidome[];
// decl: extern s32 rsh_02_b_init_evt[];
// decl: extern s32 rsh_02_b_init_evt_nidome[];
// decl: extern s32 rsh_02_c_init_evt[];
// decl: extern s32 rsh_02_c_init_evt_nidome[];
// decl: extern s32 rsh_03_a_init_evt[];
// decl: extern s32 rsh_03_a_init_evt_nidome[];
// decl: extern s32 rsh_03_b_init_evt[];
// decl: extern s32 rsh_03_b_init_evt_nidome[];
// decl: extern s32 rsh_03_c_init_evt[];
// decl: extern s32 rsh_03_c_init_evt_nidome[];
// decl: extern s32 rsh_04_a_init_evt[];
// decl: extern s32 rsh_04_a_init_evt_nidome[];
// decl: extern s32 rsh_04_b_init_evt[];
// decl: extern s32 rsh_04_b_init_evt_nidome[];
// decl: extern s32 rsh_04_c_init_evt[];
// decl: extern s32 rsh_04_c_init_evt_nidome[];
// decl: extern s32 rsh_05_a_init_evt[];
// decl: extern s32 rsh_05_a_init_evt_nidome[];
// decl: extern s32 rsh_06_a_init_evt[];
// decl: extern s32 rsh_06_a_init_evt_nidome[];
// decl: extern s32 rsh_07_a_init_evt[];
// decl: extern s32 rsh_07_b_init_evt[];
// decl: extern s32 rsh_07_c_init_evt[];
// decl: extern s32 rsh_08_a_init_evt[];
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    if (swByteGet(0) < 0x153) {
        relSetEvtAddr("rsh_00_a", rsh_00_a_init_evt);
        relSetEvtAddr("rsh_00_b", rsh_00_b_init_evt);
        relSetEvtAddr("rsh_00_c", rsh_00_c_init_evt);
        relSetEvtAddr("rsh_01_a", rsh_01_a_init_evt);
        relSetEvtAddr("rsh_01_b", rsh_01_b_init_evt);
        relSetEvtAddr("rsh_01_c", rsh_01_c_init_evt);
        relSetEvtAddr("rsh_02_a", rsh_02_a_init_evt);
        relSetEvtAddr("rsh_02_b", rsh_02_b_init_evt);
        relSetEvtAddr("rsh_02_c", rsh_02_c_init_evt);
        relSetEvtAddr("rsh_03_a", rsh_03_a_init_evt);
        relSetEvtAddr("rsh_03_b", rsh_03_b_init_evt);
        relSetEvtAddr("rsh_03_c", rsh_03_c_init_evt);
        relSetEvtAddr("rsh_04_a", rsh_04_a_init_evt);
        relSetEvtAddr("rsh_04_b", rsh_04_b_init_evt);
        relSetEvtAddr("rsh_04_c", rsh_04_c_init_evt);
        relSetEvtAddr("rsh_05_a", rsh_05_a_init_evt);
        relSetEvtAddr("rsh_06_a", rsh_06_a_init_evt);
        relSetEvtAddr("rsh_07_a", rsh_07_a_init_evt);
        relSetEvtAddr("rsh_07_b", rsh_07_b_init_evt);
        relSetEvtAddr("rsh_07_c", rsh_07_c_init_evt);
        relSetEvtAddr("rsh_08_a", rsh_08_a_init_evt);
    } else {
        relSetEvtAddr("rsh_00_a", rsh_00_a_init_evt_nidome);
        relSetEvtAddr("rsh_00_b", rsh_00_b_init_evt_nidome);
        relSetEvtAddr("rsh_00_c", rsh_00_c_init_evt_nidome);
        relSetEvtAddr("rsh_01_a", rsh_01_a_init_evt_nidome);
        relSetEvtAddr("rsh_01_b", rsh_01_b_init_evt_nidome);
        relSetEvtAddr("rsh_01_c", rsh_01_c_init_evt_nidome);
        relSetEvtAddr("rsh_02_a", rsh_02_a_init_evt_nidome);
        relSetEvtAddr("rsh_02_b", rsh_02_b_init_evt_nidome);
        relSetEvtAddr("rsh_02_c", rsh_02_c_init_evt_nidome);
        relSetEvtAddr("rsh_03_a", rsh_03_a_init_evt_nidome);
        relSetEvtAddr("rsh_03_b", rsh_03_b_init_evt_nidome);
        relSetEvtAddr("rsh_03_c", rsh_03_c_init_evt_nidome);
        relSetEvtAddr("rsh_04_a", rsh_04_a_init_evt_nidome);
        relSetEvtAddr("rsh_04_b", rsh_04_b_init_evt_nidome);
        relSetEvtAddr("rsh_04_c", rsh_04_c_init_evt_nidome);
        relSetEvtAddr("rsh_05_a", rsh_05_a_init_evt_nidome);
        relSetEvtAddr("rsh_06_a", rsh_06_a_init_evt_nidome);
        relSetEvtAddr("rsh_07_a", rsh_07_a_init_evt);
        relSetEvtAddr("rsh_07_b", rsh_07_b_init_evt);
        relSetEvtAddr("rsh_07_c", rsh_07_c_init_evt);
        relSetEvtAddr("rsh_08_a", rsh_08_a_init_evt);
    }
    relSetBtlAddr("rsh", btlsetup_rsh_tbl, btl_rsh_setup_no_tbl);
}
