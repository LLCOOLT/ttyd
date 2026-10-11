// include: driver/dispdrv.h
// decl: static void ext_disp(CameraId camera, void* param);
// proto: static void ext_dispent(void);
static void ext_dispent(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, ext_disp, NULL);
}
