// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: memory.h
// decl: typedef struct RyushiWork { s32 flag; s32 mode; Vec base; Vec pos; s32 alpha; s32 count; f32 scale; s32 r; s32 g; s32 b; s32 r2; s32 g2; s32 b2; } RyushiWork;
// decl: RyushiWork* xwp;
// decl: s32 ryuwp;
// proto: USER_FUNC(evt_ryushi_init);
USER_FUNC(evt_ryushi_init) {
    RyushiWork* p;
    RyushiWork* q;
    s32 i;

    ryuwp = 241;
    xwp = p = _mapAlloc(ryuwp * sizeof(RyushiWork));
    p->mode = 0;
    p->count = 0;
    p->alpha = 0;
    p->pos.x = 0.0f;
    p->pos.y = 0.0f;
    p->pos.z = 0.0f;
    p->scale = 1.0f;
    p->r = 255;
    p->g = 0;
    p->b = 255;
    p->r2 = 255;
    p->g2 = 128;
    p->b2 = 255;
    for (i = 1, q = p + 1; i < 241; i++, q++) {
        q->flag = 0;
    }
    return EVT_RETURN_DONE;
}
