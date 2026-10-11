// include: driver/camdrv.h
// include: manager/filemgr.h
// include: win/win_main.h
// decl: typedef struct TegamiWork { s32 alpha; FileEntry* tpl; } TegamiWork;
// decl: static TegamiWork* wp;
// proto: static void draw(CameraId camera, void* param);
static void draw(CameraId camera, void* param) {
    winTexInit(*(TEXPalette**)wp->tpl->data);
    winTexSet(4, (Vec){0.0f, -74.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0xFF, 0xFF, 0xFF, wp->alpha});
}
