// include: driver/dispdrv.h
// decl: static void senteresa_ext_disp(CameraId camera, void* param);
// proto: static void senteresa_ext_dispent(void);
static void senteresa_ext_dispent(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, senteresa_ext_disp, NULL);
}
