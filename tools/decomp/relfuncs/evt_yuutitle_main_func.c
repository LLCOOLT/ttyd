// include: driver/dispdrv.h
// include: driver/camdrv.h
// decl: void evt_yuutitle_disp_func(CameraId camera, void* param);
// proto: USER_FUNC(evt_yuutitle_main_func);
USER_FUNC(evt_yuutitle_main_func) {
    YuuTitleWork* wp = (YuuTitleWork*)event->lwData[0];

    if (wp->flags & 1) {
        wp->flags |= 2;
        return EVT_RETURN_DONE;
    }
    dispEntry(CAMERA_2D, 1000.0f, 0, evt_yuutitle_disp_func, wp);
    return EVT_RETURN_BLOCK;
}
