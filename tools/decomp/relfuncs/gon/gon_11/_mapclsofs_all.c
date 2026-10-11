// decl: typedef struct CloudWork { s32 used; s32 state; char animName[0x20]; char imgName[0x20]; char offscreenName[0x20]; char groupNames[8][0x20]; char hitName[0x20]; s32 limit; s32 counter; EventEntry* evt; void* endEvt; s32 timer; s32 x; s32 y; s32 w; s32 h; f32 lastFrame; } CloudWork;
// decl: void mapGrpClearOffScreen(const char* name);
// proto: static void _mapclsofs_all(CloudWork* wp);
static void _mapclsofs_all(CloudWork* wp) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if ((s8)wp->groupNames[i][0] == 0) {
            break;
        }
        mapGrpClearOffScreen(wp->groupNames[i]);
    }
}
