// include: data/mapdata.h
// include: memory.h
// include: string.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 btl_jin_setup_no_tbl[];
// decl: extern s32 btlsetup_jin_tbl[];
// decl: extern s32 jin_00_init_evt[];
// decl: extern s32 jin_01_init_evt[];
// decl: extern s32 jin_02_init_evt[];
// decl: extern s32 jin_03_init_evt[];
// decl: extern s32 jin_04_init_evt[];
// decl: extern s32 jin_05_init_evt[];
// decl: extern s32 jin_06_init_evt[];
// decl: extern s32 jin_07_init_evt[];
// decl: extern s32 jin_08_init_evt[];
// decl: extern s32 jin_09_init_evt[];
// decl: extern s32 jin_10_init_evt[];
// decl: extern s32 jin_11_init_evt[];
// decl: extern char* partyPoseTbl[20][15];
// decl: static void* pose_buf;
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("jin_00", jin_00_init_evt);
    relSetEvtAddr("jin_01", jin_01_init_evt);
    relSetEvtAddr("jin_02", jin_02_init_evt);
    relSetEvtAddr("jin_03", jin_03_init_evt);
    relSetEvtAddr("jin_04", jin_04_init_evt);
    relSetEvtAddr("jin_05", jin_05_init_evt);
    relSetEvtAddr("jin_06", jin_06_init_evt);
    relSetEvtAddr("jin_07", jin_07_init_evt);
    relSetEvtAddr("jin_08", jin_08_init_evt);
    relSetEvtAddr("jin_09", jin_09_init_evt);
    relSetEvtAddr("jin_10", jin_10_init_evt);
    relSetEvtAddr("jin_11", jin_11_init_evt);
    relSetBtlAddr("jin", btlsetup_jin_tbl, btl_jin_setup_no_tbl);
    pose_buf = _mapAlloc(sizeof(partyPoseTbl[6]));
    memcpy(pose_buf, partyPoseTbl[6], sizeof(partyPoseTbl[6]));
}
