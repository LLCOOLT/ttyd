// include: driver/swdrv.h
// include: memory.h
// decl: typedef struct RankEntry { u16 flags; s32 id; union { s16 score; u8 sw[2]; }; } RankEntry;
// decl: typedef struct RankWork { s32 num; RankEntry* entries; } RankWork;
// decl: static __declspec(section ".data") RankWork* rank_wp;
// decl: static void rankingExit(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    rankingExit();
    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
