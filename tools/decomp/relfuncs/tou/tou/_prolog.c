// include: data/mapdata.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: static void rankingInit(void);
// decl: extern s32 tou_00_init_evt[];
// decl: extern s32 tou_01_init_evt[];
// decl: extern s32 tou_02_init_evt[];
// decl: extern s32 tou_04_init_evt[];
// decl: extern s32 tou_05_init_evt[];
// decl: extern s32 tou_06_init_evt[];
// decl: extern s32 tou_07_init_evt[];
// decl: extern s32 tou_08_init_evt[];
// decl: extern s32 tou_09_init_evt[];
// decl: extern s32 tou_10_init_evt[];
// decl: extern s32 tou_11_init_evt[];
// decl: extern s32 tou_12_init_evt[];
// decl: extern s32 tou_13_init_evt[];
// decl: extern s32 tou_20_init_evt[];
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("tou_00", tou_00_init_evt);
    relSetEvtAddr("tou_01", tou_01_init_evt);
    relSetEvtAddr("tou_02", tou_02_init_evt);
    relSetEvtAddr("tou_04", tou_04_init_evt);
    relSetEvtAddr("tou_05", tou_05_init_evt);
    relSetEvtAddr("tou_06", tou_06_init_evt);
    relSetEvtAddr("tou_07", tou_07_init_evt);
    relSetEvtAddr("tou_08", tou_08_init_evt);
    relSetEvtAddr("tou_09", tou_09_init_evt);
    relSetEvtAddr("tou_10", tou_10_init_evt);
    relSetEvtAddr("tou_11", tou_11_init_evt);
    relSetEvtAddr("tou_12", tou_12_init_evt);
    relSetEvtAddr("tou_13", tou_13_init_evt);
    relSetEvtAddr("tou_20", tou_20_init_evt);
    rankingInit();
}
