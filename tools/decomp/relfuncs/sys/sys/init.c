// include: memory.h
// include: string.h
// include: mario/mariost.h
// include: manager/filemgr.h
// include: driver/camdrv.h
// include: driver/dispdrv.h
// include: driver/effdrv.h
// include: system.h
// decl: typedef struct SysChar { f32 x; f32 y; f32 z; f32 rot; s32 timer; s32 state; s32 texid; } SysChar;
// decl: typedef struct SysWork { s32 state; FileEntry* file; f32 rot; s32 frame; s32 scroll; s32 type; s32 alpha; f32 angle; s32 count; SysChar chars[8]; } SysWork;
// decl: SysWork* g_wp;
// proto: USER_FUNC(init);
USER_FUNC(init) {
    return EVT_RETURN_DONE;
}
