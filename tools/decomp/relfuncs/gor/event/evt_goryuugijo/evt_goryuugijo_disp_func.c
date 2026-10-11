// proto: void evt_goryuugijo_disp_func(CameraId camera, void* param);
void evt_goryuugijo_disp_func(CameraId camera, void* param) {
    ((GoryuuWork*)param)->disp(camera, param);
}
