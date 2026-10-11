// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 aji_00_init_evt[];
// decl: extern s32 aji_01_init_evt[];
// decl: extern s32 aji_02_init_evt[];
// decl: extern s32 aji_03_init_evt[];
// decl: extern s32 aji_04_init_evt[];
// decl: extern s32 aji_05_init_evt[];
// decl: extern s32 aji_06_init_evt[];
// decl: extern s32 aji_07_init_evt[];
// decl: extern s32 aji_08_init_evt[];
// decl: extern s32 aji_09_init_evt[];
// decl: extern s32 aji_10_init_evt[];
// decl: extern s32 aji_11_init_evt[];
// decl: extern s32 aji_12_init_evt[];
// decl: extern s32 aji_13_init_evt[];
// decl: extern s32 aji_14_init_evt[];
// decl: extern s32 aji_15_init_evt[];
// decl: extern s32 aji_16_init_evt[];
// decl: extern s32 aji_17_init_evt[];
// decl: extern s32 aji_18_init_evt[];
// decl: extern s32 aji_19_init_evt[];
// decl: extern s32 btl_aji_setup_no_tbl[];
// decl: extern s32 btlsetup_aji_tbl[];
// include: mario/mario.h
// include: party.h
// include: driver/swdrv.h
// include: mario/mario_party.h
// decl: void partySetFamicomMode(PartyEntry* party, s32 mode);
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    if (swGet(0x1079)) {
        marioSetFamicomMode(0);
        partySetFamicomMode(partyGetPtr(marioGetPartyId()), 0);
        swClear(0x1079);
    }
    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
