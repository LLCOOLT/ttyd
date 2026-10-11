// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// decl: void rankingInit(void);
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
// include: driver/swdrv.h
// include: memory.h
// decl: typedef struct RankEntry { u16 flags; s32 id; union { s16 score; u8 sw[2]; }; } RankEntry;
// decl: typedef struct RankWork { s32 num; RankEntry* entries; } RankWork;
// decl: static __declspec(section ".data") RankWork* rank_wp;
// decl: static void rankingExit(void);
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    rankingExit();
    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
