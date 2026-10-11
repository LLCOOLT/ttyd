// include: data/mapdata.h
// include: memory.h
// include: string.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_gra_setup_no_tbl[];
// decl: extern s32 btlsetup_gra_tbl[];
// decl: extern s32 gra_00_init_evt[];
// decl: extern s32 gra_01_init_evt[];
// decl: extern s32 gra_02_init_evt[];
// decl: extern s32 gra_03_init_evt[];
// decl: extern s32 gra_04_init_evt[];
// decl: extern s32 gra_05_init_evt[];
// decl: extern s32 gra_06_init_evt[];
// decl: extern char* partyPoseTbl[20][15];
// decl: static void* pose_buf;
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("gra_00", gra_00_init_evt);
    relSetEvtAddr("gra_01", gra_01_init_evt);
    relSetEvtAddr("gra_02", gra_02_init_evt);
    relSetEvtAddr("gra_03", gra_03_init_evt);
    relSetEvtAddr("gra_04", gra_04_init_evt);
    relSetEvtAddr("gra_05", gra_05_init_evt);
    relSetEvtAddr("gra_06", gra_06_init_evt);
    relSetBtlAddr("gra", btlsetup_gra_tbl, btl_gra_setup_no_tbl);
    pose_buf = _mapAlloc(sizeof(partyPoseTbl[6]));
    memcpy(pose_buf, partyPoseTbl[6], sizeof(partyPoseTbl[6]));
}
