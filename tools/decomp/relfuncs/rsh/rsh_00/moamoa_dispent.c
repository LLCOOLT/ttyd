// include: driver/dispdrv.h
// decl: static void ext_disp(CameraId camera, void* param);
// proto: void moamoa_dispent(void);
void moamoa_dispent(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, ext_disp, NULL);
}
