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
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
    memcpy(partyPoseTbl[6], pose_buf, sizeof(partyPoseTbl[6]));
    _mapFree(pose_buf);
}
