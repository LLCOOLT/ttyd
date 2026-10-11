// include: memory.h
// include: string.h
// include: stdlib.h
// include: system.h
// include: manager/filemgr.h
// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// include: driver/camdrv.h
// decl: typedef struct SightWork { FileEntry* tpl; s32 level[5]; f32 rot; s32 dir; s32 count1; s32 count2; } SightWork;
// decl: SightWork* sight_wp;
// proto: USER_FUNC(sight_dir);
USER_FUNC(sight_dir) {
    sight_wp->dir = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}
