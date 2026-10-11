// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: driver/dispdrv.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct SlitWork { u32 flags; s32 phase; s32 coins; s32 result; s32 state; s32 timer; f32 rot1; f32 rot2; s32 monteCount; EventEntry* viewEvent; } SlitWork;
// decl: typedef struct RyushiWork { s32 flag; s32 mode; Vec base; Vec pos; s32 alpha; s32 count; f32 scale; s32 r; s32 g; s32 b; s32 r2; s32 g2; s32 b2; } RyushiWork;
// decl: RyushiWork* xwp;
// decl: s32 ryuwp;
// decl: static f32 randf(f32 min, f32 max);
// decl: void ryushi_disp(CameraId camera, void* param);
// proto: USER_FUNC(evt_ryushi);
USER_FUNC(evt_ryushi) {
    RyushiWork* hdr = xwp;
    Vec pos2;
    Vec pos = {0.0f, 0.0f, 0.0f};
    SlitWork* data;
    RyushiWork* p;
    s32 i;
    s32 n;
    f32 speed;
    f32 alphaScale;
    f32 camX;
    f32 scale;
    f32 w;
    f32 d;

    pos.x = hdr->pos.x;
    pos.y = hdr->pos.y;
    pos.z = hdr->pos.z;
    pos2 = pos;
    speed = 0.0f;
    alphaScale = 0.0f;
    scale = 1.0f;
    data = ((MiniGameWork*)event->lwData[0])->data;
    camX = camGetPtr(CAMERA_3D)->cameraAt.x;
    switch (data->state) {
        case 2:
        case 3:
        case 4:
            speed = 2.9166667f;
            alphaScale = 1.0f;
            break;
        case 6:
        case 7:
        case 8:
            speed = 2.9166667f;
            alphaScale = 1.0f;
            break;
    }
    switch (data->state) {
        case 1:
        case 5:
            alphaScale = (60 - data->timer) / 60.0f;
            scale = alphaScale;
            break;
        case 2:
        case 6:
            speed = speed * (60 - data->timer) / 60.0f;
            break;
        case 4:
        case 8:
            alphaScale = data->timer / 48.0f;
            break;
    }
    hdr->count++;
    n = hdr->count;
    if (n <= 20) {
        hdr->alpha = n * 12;
    } else {
        hdr->alpha = 255;
    }
    if (n & 1) {
        hdr->alpha /= 2;
    }
    scale = 0.5f * scale;
    for (i = 1, p = hdr + 1; i < ryuwp; i++, p++) {
        switch (xwp->mode) {
            case 0:
                p->pos.z -= speed;
                if (p->pos.z < -200.0f) {
                    p->pos.x = p->base.x + randf(0.3f * -xwp->base.x, 0.3f * xwp->base.x);
                    p->pos.y = p->base.y + randf(0.3f * -xwp->base.y, 0.3f * xwp->base.y);
                    p->pos.z = 200.0f + randf(0.3f * -xwp->base.z, 0.3f * xwp->base.z);
                }
                break;
            case 1:
                p->pos.z += speed;
                if (p->pos.z > 200.0f) {
                    p->pos.x = p->base.x + randf(0.3f * -xwp->base.x, 0.3f * xwp->base.x);
                    p->pos.y = p->base.y + randf(0.3f * -xwp->base.y, 0.3f * xwp->base.y);
                    p->pos.z = -200.0f + randf(0.3f * -xwp->base.z, 0.3f * xwp->base.z);
                }
                break;
        }
        n = (p->pos.x - camX) / (10.0f * xwp->base.x / 2.0f);
        if (n != 0) {
            if (n > 0) {
                n++;
            } else {
                n--;
            }
            p->pos.x += (-n / 2) * (10.0f * xwp->base.x);
        }
        if (p->pos.z < 0.0f) {
            d = -p->pos.z;
        } else {
            d = p->pos.z;
        }
        d -= 100.0f;
        if (d < 0.0f) {
            d = 0.0f;
        } else if (d > 100.0f) {
            d = 100.0f;
        }
        p->alpha = 0.7 * (255.0f * ((100.0f - d) / 100.0f) * alphaScale);
        p->scale = scale;
    }
    dispEntry(CAMERA_3D, dispCalcZ(&pos2), 2, ryushi_disp, NULL);
    return EVT_RETURN_DONE;
}
