// include: data/mapdata.h
// include: memory.h
// include: string.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 usu_00_init_evt[];
// decl: extern s32 usu_01_init_evt[];
// decl: extern char* partyPoseTbl[20][15];
// decl: static void* pose_buf;
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("usu_00", usu_00_init_evt);
    relSetEvtAddr("usu_01", usu_01_init_evt);
    pose_buf = _mapAlloc(sizeof(partyPoseTbl[6]));
    memcpy(pose_buf, partyPoseTbl[6], sizeof(partyPoseTbl[6]));
}
