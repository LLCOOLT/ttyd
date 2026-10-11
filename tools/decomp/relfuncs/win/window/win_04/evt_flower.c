// include: driver/dispdrv.h
// include: stdlib.h
// proto: USER_FUNC(evt_flower);
USER_FUNC(evt_flower) {
    FlowerWork* wp = (FlowerWork*)event->lwData[10];
    Flower* fl = wp->flowers;
    s32 i;

    for (i = 0; i < wp->count; i++, fl++) {
        switch (fl->state) {
            case 0:
                fl->timer = rand() % 100;
                fl->state++;
                break;
            case 1:
                if (--fl->timer < 0) {
                    fl->x = ((Vec*)rose_table_direct)[i].x;
                    fl->y = ((Vec*)rose_table_direct)[i].y;
                    fl->targetScale = ((Vec*)rose_table_direct)[i].z;
                    fl->scale = 0.0f;
                    fl->state++;
                }
                break;
            case 2:
                if (fl->scale < fl->targetScale) {
                    fl->scale += 0.08f;
                } else {
                    fl->timer = 0;
                    fl->state++;
                }
                fl->alpha += 20;
                if (fl->alpha > 255) {
                    fl->alpha = 255;
                }
                break;
        }
    }
    dispEntry(CAMERA_2D, 1000.0f, 0, flower_disp, wp);
    return EVT_RETURN_DONE;
}
