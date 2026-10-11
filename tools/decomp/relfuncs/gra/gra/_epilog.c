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
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
    memcpy(partyPoseTbl[6], pose_buf, sizeof(partyPoseTbl[6]));
    _mapFree(pose_buf);
}
