// include: driver/dispdrv.h
// include: driver/camdrv.h
// decl: void ext_disp_minnnanokoe(CameraId camera, void* param);
// proto: void ext_dispent_minnnanokoe(void);
void ext_dispent_minnnanokoe(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, ext_disp_minnnanokoe, NULL);
}
