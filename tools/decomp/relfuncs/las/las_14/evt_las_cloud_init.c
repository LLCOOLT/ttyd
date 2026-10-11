// include: memory.h
// include: stdio.h
// decl: typedef struct CloudWork { s32 used; s32 state; char animName[0x20]; char imgName[0x20]; char offscreenName[0x20]; char groupNames[8][0x20]; char hitName[0x20]; s32 limit; s32 counter; EventEntry* evt; void* endEvt; s32 timer; s32 x; s32 y; s32 w; s32 h; f32 lastFrame; } CloudWork;
// decl: static CloudWork* cloud;
// decl: static u8 cloud_once_flag;
// proto: USER_FUNC(evt_las_cloud_init);
USER_FUNC(evt_las_cloud_init) {
    s32 i;

    cloud = _mapAlloc(sizeof(CloudWork) * 16);
    for (i = 0; i < 16; i++) {
        cloud[i].used = 0;
        sprintf(cloud[i].imgName, "i_name_%1d", i);
        sprintf(cloud[i].offscreenName, "o_name_%1d", i);
    }
    cloud_once_flag = 0;
    return EVT_RETURN_DONE;
}
