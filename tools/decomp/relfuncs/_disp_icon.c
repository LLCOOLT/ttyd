// include: driver/icondrv.h
// include: driver/camdrv.h
// proto: void _disp_icon(CameraId camera, void* param);
void _disp_icon(CameraId camera, void* param) {
    EventEntry* event = param;

    iconDispGx((Vec*)((u8*)event->userdatap[0] + 0xC), 0, event->userdata[1], 1.0f);
}
