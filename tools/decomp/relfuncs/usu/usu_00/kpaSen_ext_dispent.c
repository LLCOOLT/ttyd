// include: driver/dispdrv.h
// decl: void kpaSen_ext_disp(CameraId camera, void* param);
// decl: void kpaSen_ext_shadow_disp(CameraId camera, void* param);
// proto: void kpaSen_ext_dispent(void);
void kpaSen_ext_dispent(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, kpaSen_ext_disp, NULL);
    dispEntry(CAMERA_3D, 0.0f, 2, kpaSen_ext_shadow_disp, NULL);
}
