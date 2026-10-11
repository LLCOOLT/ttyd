// include: data/mapdata.h
// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: extern s32 kpa_00_init_evt[];
// decl: extern s32 kpa_01_init_evt[];
// decl: extern s32 kpa_02_init_evt[];
// decl: extern s32 kpa_03_init_evt[];
// decl: extern s32 kpa_04_init_evt[];
// decl: extern s32 kpa_05_init_evt[];
// decl: extern s32 kpa_06_init_evt[];
// decl: extern s32 kpa_07_init_evt[];
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("kpa_00", kpa_00_init_evt);
    relSetEvtAddr("kpa_01", kpa_01_init_evt);
    relSetEvtAddr("kpa_02", kpa_02_init_evt);
    relSetEvtAddr("kpa_03", kpa_03_init_evt);
    relSetEvtAddr("kpa_04", kpa_04_init_evt);
    relSetEvtAddr("kpa_05", kpa_05_init_evt);
    relSetEvtAddr("kpa_06", kpa_06_init_evt);
    relSetEvtAddr("kpa_07", kpa_07_init_evt);
}
