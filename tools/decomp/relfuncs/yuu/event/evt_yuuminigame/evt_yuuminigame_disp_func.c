// proto: void evt_yuuminigame_disp_func(CameraId camera, void* param);
void evt_yuuminigame_disp_func(CameraId camera, void* param) {
    ((MiniGameWork*)param)->disp(camera, param);
}
