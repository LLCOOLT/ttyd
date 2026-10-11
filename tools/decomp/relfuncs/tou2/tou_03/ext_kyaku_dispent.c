// include: driver/dispdrv.h
// decl: void kyaku_disp(CameraId camera, void* param);
// proto: void ext_kyaku_dispent(void);
void ext_kyaku_dispent(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, kyaku_disp, NULL);
}
