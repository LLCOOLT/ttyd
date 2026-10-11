// include: driver/camdrv.h
// include: manager/fontmgr.h
// decl: void FontDrawScale(f32 scale);
// decl: void FontDrawString(f32 x, f32 y, const char* message);
// proto: void kpa_stageclear_disp(CameraId camera, void* param);
void kpa_stageclear_disp(CameraId camera, void* param) {
    FontDrawStart();
    FontDrawScale(2.0f);
    FontDrawEdge();
    FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
    FontDrawString(-140.0f, 40.0f, "\203S\201[\203\213\203C\203\223\201I\201I");
    FontDrawEdgeOff();
}
