// include: driver/dispdrv.h
// decl: void flower_disp(CameraId camera, void* param);
// proto: USER_FUNC(evt_flower_end_main);
USER_FUNC(evt_flower_end_main) {
    FlowerWork* wp = (FlowerWork*)event->lwData[10];
    Flower* fl = wp->flowers;
    s32 i;

    for (i = 0; i < wp->count; i++, fl++) {
        switch (fl->state) {
            case 0:
                fl->alpha -= 10;
                if (fl->alpha < 0) {
                    fl->alpha = 0;
                    fl->state++;
                }
                break;
            case 1:
                break;
        }
    }
    dispEntry(CAMERA_2D, 1000.0f, 0, flower_disp, wp);
    return EVT_RETURN_DONE;
}
