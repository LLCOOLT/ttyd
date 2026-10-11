// include: manager/fontmgr.h
// include: driver/camdrv.h
// decl: void FontDrawScale(f32 scale);
// decl: void FontDrawEdge(void);
// decl: void FontDrawEdgeOff(void);
// decl: void FontDrawString(f32 x, f32 y, const char* str);
// proto: void evt_yuutitle_disp_func(CameraId camera, void* param);
void evt_yuutitle_disp_func(CameraId camera, void* param) {
    YuuTitleWork* wp = param;
    f32 scale = 2.0f;
    f32 halfWidth;

    if (wp->alpha < 255) {
        f32 t;

        wp->alpha += 6;
        if (wp->alpha > 255) {
            wp->alpha = 255;
        }
        t = wp->alpha / 255.0f;
        wp->x = wp->targetX * t + wp->startX * (1.0f - t);
        wp->y = wp->targetY * t + wp->startY * (1.0f - t);
        t = 0.2f + 0.8f * t;
        scale *= t;
    }
    halfWidth = scale * FontGetMessageWidth(wp->msg) / 2;
    FontDrawStart();
    FontDrawScale(scale);
    FontDrawEdge();
    FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, wp->alpha});
    FontDrawString(wp->x - halfWidth, wp->y, wp->msg);
    FontDrawEdgeOff();
}
