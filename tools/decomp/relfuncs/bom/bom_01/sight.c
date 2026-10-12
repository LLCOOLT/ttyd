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
// decl: void disp_sight(CameraId camera, void* param);
// proto: USER_FUNC(sight);
USER_FUNC(sight) {
    s32 i;

    if (isFirstCall) {
        sight_wp = _mapAlloc(sizeof(SightWork));
        memset(sight_wp, 0, sizeof(SightWork));
        for (i = 0; i < 5; i++) {
            sight_wp->level[i] = 0;
        }
        sight_wp->count1 = rand();
        sight_wp->count2 = rand();
        sight_wp->dir = 5;
    }
    if (sight_wp->tpl == NULL) {
        if (fileAsyncf(4, NULL, "%s/%s", getMarioStDvdRoot(), "taihou.tpl") == 0U) {
            return EVT_RETURN_BLOCK;
        }
        sight_wp->tpl = fileAllocf(4, "%s/%s", getMarioStDvdRoot(), "taihou.tpl");
    }
    if (sight_wp->dir == 6) {
        fileFree(sight_wp->tpl);
        _mapFree(sight_wp);
        return EVT_RETURN_DONE;
    }
    if (sight_wp->dir != 5) {
        dispEntry(CAMERA_2D, 800.0f, 0, disp_sight, NULL);
    }
    return EVT_RETURN_BLOCK;
}
