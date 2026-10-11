// include: driver/dispdrv.h
// decl: static void senkaron_ext_disp(CameraId camera, void* param);
// decl: static void senkaron_ext_shadow_disp(CameraId camera, void* param);
// proto: static void senkaron_ext_dispent(void);
static void senkaron_ext_dispent(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, senkaron_ext_disp, NULL);
    dispEntry(CAMERA_3D, 0.0f, 2, senkaron_ext_shadow_disp, NULL);
}
