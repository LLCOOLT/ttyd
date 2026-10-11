// include: driver/dispdrv.h
// decl: void evt_goryuugijo_disp_func(CameraId camera, void* param);
// proto: USER_FUNC(evt_goryuugijo_main_func);
USER_FUNC(evt_goryuugijo_main_func) {
    GoryuuWork* wp = (GoryuuWork*)event->lwData[0];

    if (wp->flags & 1) {
        wp->flags |= 2;
        return EVT_RETURN_DONE;
    }
    if (wp->subEvent != NULL) {
        if (evtCheckID(wp->subEvent->eventId)) {
            goto disp;
        }
        wp->subEvent = NULL;
    }
    wp->main(event, isFirstCall);
disp:
    dispEntry(CAMERA_2D, 1000.0f, 0, evt_goryuugijo_disp_func, wp);
    return EVT_RETURN_BLOCK;
}
